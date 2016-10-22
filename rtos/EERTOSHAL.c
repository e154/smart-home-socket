#include "EERTOSHAL.h"

//RTOS Запуск системного таймера
inline void RunRTOS (void)
{
#if defined(__AVR_ATmega16__)

    TCCR2 = 1<<WGM21|4<<CS20; 				// Freq = CK/64 - Установить режим и предделитель
    // Автосброс после достижения регистра сравнения
    TCNT2 = 0;								// Установить начальное значение счётчиков
    OCR2  = LO(TimerDivider); 				// Установить значение в регистр сравнения
    TIMSK = 0<<TOIE0|1<<OCIE2;		        // Разрешаем прерывание RTOS - запуск ОС

#elif defined(__AVR_ATmega168P__)

    TCCR2B = 1<<CS22; 				        // Freq = CK/64 - Установить режим и предделитель
    // Автосброс после достижения регистра сравнения
    TCNT2 = 0;								// Установить начальное значение счётчиков
    OCR2B  = LO(TimerDivider); 				// Установить значение в регистр сравнения
    TIMSK2 = 0<<TOIE2|1<<OCIE2B;		    // Разрешаем прерывание RTOS - запуск ОС
#endif

    sei();
}