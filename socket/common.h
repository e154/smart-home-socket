//
// Created by delta54 on 9/21/16.
//

#ifndef CMAKE_AVR_COMMON_H
#define CMAKE_AVR_COMMON_H

// project/system dependent defines
#include <string.h>
#include "../rtos/avrlibtypes.h"

#define output_low(port, pin) port &= ~(1<<pin)
#define output_high(port, pin) port |= (1<<pin)
#define set_input(portdir, pin) portdir &= ~(1<<pin)
#define set_output(portdir, pin) portdir |= (1<<pin)
#define invert(portdir, pin) portdir ^= (1<<pin)
#define line_is_high(portdir, pin) ((portdir & (1<<pin)) != 0)
#define line_is_low(portdir, pin) ((portdir & (1<<pin)) == 0)
#define soft_reset() do {wdt_enable(WDTO_15MS);for(;;){}} while(0)

inline void removeSubstring(char *s,const char *toremove)
{
    while( s=strstr(s,toremove) )
        memmove(s,s+strlen(toremove),1+strlen(s+strlen(toremove)));
}

#define Hi(Int) (u08) (Int >> 4)
#define LOW(Int) (u08) Int

#endif //CMAKE_AVR_COMMON_H
