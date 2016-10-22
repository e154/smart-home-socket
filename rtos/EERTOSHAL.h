#ifndef EERTOSHAL_H
#define EERTOSHAL_H
#include "HAL.h"

#define STATUS_REG 			SREG
#define Interrupt_Flag		SREG_I
#define Disable_Interrupt	cli();
#define Enable_Interrupt	sei();

//RTOS Config
#if defined(__AVR_ATmega16__)
    #define RTOS_ISR  			TIMER2_COMP_vect
#elif defined(__AVR_ATmega168P__)
    #define RTOS_ISR  			TIMER2_COMPB_vect
#endif

#define	TaskQueueSize		20
#define MainTimerQueueSize	15

extern void RunRTOS (void);

#endif
