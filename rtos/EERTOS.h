#ifndef EERTOS_H
#define EERTOS_H

#include "HAL.h"
#include "EERTOSHAL.h"

extern void InitRTOS(void);
extern void Idle(void);

typedef void (*TPTR)(void);

extern void SetTask(TPTR TS);
extern void SetTimerTask(TPTR TS, u16 NewTime);

extern void TaskManager(void);
extern void TimerService(void);

//RTOS Errors Пока не используются.
#define TaskSetOk			 'A'
#define TaskQueueOverflow	 'B'
#define TimerUpdated		 'C'
#define TimerSetOk			 'D'
#define TimerOverflow		 'E'

#endif
