#ifndef HAL_H
#define HAL_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include "avrlibtypes.h"
#include "avrlibdefs.h"
#include "avr/pgmspace.h"
#include <avr/wdt.h>

//Clock Config
//#define F_CPU 8000000L

//System Timer Config
#define Prescaler	  		64
#define	TimerDivider  		(F_CPU/Prescaler/1000)		// 1 mS

//USART Config
#define BAUD 19200L
#define bauddivider (F_CPU/(16*BAUD)-1)
#define HI(x) ((x)>>8)
#define LO(x) ((x)& 0xFF)


//PORT Defines


extern void InitAll(void);



#endif
