//
// Created by delta54 on 08.10.16.
//

#ifndef CMAKE_AVR_COMMANDS_H
#define CMAKE_AVR_COMMANDS_H

#include "../rtos/avrlibtypes.h"

void echo(const u08* ucASCIIBuf, const u08 NumByte);
void read_state(const u08* ucASCIIBuf);
void write_state(const u08* ucASCIIBuf);
void get_status();

#endif //CMAKE_AVR_COMMANDS_H
