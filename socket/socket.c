//
// Created by delta54 on 9/30/16.
//

#include "common.h"
#include "../rtos/EERTOS.h"
#include "socket.h"
#include "ftoa.h"
#include "lm35.h"
#include "ftoa.h"
#include "adc.h"
#include "../modbus/modbus.h"

//============================================================================
//Область задач
//============================================================================

// Каждую секунду проверяем температуру
void CheckTemp(void)
{
    SetTimerTask(CheckTemp,1000);

    float temp = read_temperature_in_C();     //12345
    ftoa(buffer, temp, 1);             //12.3
//    printf("Temperature=%s\n\r", buffer);

    removeSubstring(buffer, ".");       //123
    current_temp = atoi(buffer);
//    printf("Temperature=%i\n\r", current_temp);
    if (current_temp >= MAX_TEMP) {

        if (!alert) {
            //Превышен максимальный температурный предел
            alert = true;
            // подать звуковой сигнал
            AlertBuzzer();
            // и отключить потребителя
            DisableSocket();
        }

    } else {
        if (alert) {
            alert = false;
            EnableSocket();
        }
    }
}

void AlertBuzzer(void)
{
    if (alert) {
        SetTimerTask(AlertBuzzer,300);
        invert(BUZZER_PORT, BUZZER_PIN);
    } else {
        output_low(BUZZER_PORT, BUZZER_PIN);
    }
}

void EnableSocket() {
    output_high(TOGGLE_PORT, TOGGLE_PIN);
}

void DisableSocket() {
    output_low(TOGGLE_PORT, TOGGLE_PIN);
}

void BlinkPwrLed(void) {
    SetTimerTask(BlinkPwrLed,1000);
    invert(PWR_LED_PORT, PWR_LED);
}

ISR(INT0_vect) {
//    InvBit(MCUCR,ISC00);//Каждый раз меняем INT0 то на спадающий то на нарастающий фронт.
//    printf("INT0\n\r");
    phase_counter++;
}

void PhaseCheck(void) {
    SetTimerTask(PhaseCheck, 1000);
    phase = (phase_counter > 40 );
    phase_counter = 0;
}

void SocketInit() {

    set_output(DDRD, BUZZER_PIN);
    set_output(DDRD, TOGGLE_PIN);
    set_output(DDRD, PWR_LED);
    set_output(DDRB, MAX485_PIN);
    set_input(DDRD, PHAZE_PIN);
    set_input(DDRC, TEMPER_PIN);

    output_low(BUZZER_PORT, BUZZER_PIN);
    output_high(TOGGLE_PORT, TOGGLE_PIN);
    ModbusSetRead();

//    printf("Socket console v1.1\n\r");
//    printf("F_CPU: %lu\n\r", F_CPU);
//    printf("BAUD: %lu\n\r", BAUD);

    // Запуск фоновых задач.
    ModbusInit();
    SetTask(CheckTemp);
    SetTask(BlinkPwrLed);
    SetTask(PhaseCheck);
}