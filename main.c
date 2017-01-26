#include <stdio.h>
#include "rtos/HAL.h"
#include "rtos/EERTOS.h"
#include "socket/uart.h"
#include "socket/socket.h"

//RTOS Interrupt
ISR(RTOS_ISR)
{
    TimerService();
}

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
//==============================================================================
int main(void)
{
    InitAll();			// Инициализируем периферию
    InitRTOS();			// Инициализируем ядро
    RunRTOS();			// Старт ядра.
    SocketInit();

    while(1) 		    // Главный цикл диспетчера
    {
        wdt_reset();	// Сброс собачьего таймера
        TaskManager();	// Вызов диспетчера
    }
}
#pragma clang diagnostic pop
