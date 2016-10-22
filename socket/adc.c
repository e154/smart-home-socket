//
// Created by delta54 on 9/15/16.
//

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "adc.h"

// read adc value
uint16_t adc_read(uint8_t ch)
{
    // выбор пина ADC0 - ADC7
    // обрезаем число больще 7
    ch &= 0b00000111;
    ADMUX = 0;
    ADMUX = _BV(REFS0) | ch;

    _delay_us(10);

    // Начать измерение
    // Запишем '1' в ADSC
    ADCSRA |= _BV(ADSC);

    // Ждем окончание измерения
    // По окончанию ADSC сбросится в '0'
    while(ADCSRA & _BV(ADSC));

    return ADCW;
}

ISR(ADC_vect)
{
    unsigned char saveState = SREG;
    cli();                      // на время считывания буфера запрещаются прерывания
    value[0] = ADCW;
    SREG = saveState;
    sei();

    // Запуск очередного преобразования
    ADCSRA |= (1<<ADSC);

}
