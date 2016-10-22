//
// Created by delta54 on 9/30/16.
//

#include <stdbool.h>
#include "../config.h"

#ifndef CMAKE_AVR_SOCKET_H
#define CMAKE_AVR_SOCKET_H

char buffer[10];
bool alert;
bool phase;
u16 current_temp;
u08 phase_counter;

void CheckTemp(void);
void AlertBuzzer(void);
void SocketInit();
void EnableSocket();
void DisableSocket();
void BlinkPwrLed(void);
void PhaseCheck(void);

#endif //CMAKE_AVR_SOCKET_H
