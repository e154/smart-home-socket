//
// Created by delta54 on 9/21/16.
//

#ifndef CMAKE_AVR_UART_H
#define CMAKE_AVR_UART_H

#include "fifo.h"

FILE uart_stream;

int uart_putc(  char c, FILE *file );
//int uart_getc( FILE* file );

#endif //CMAKE_AVR_UART_H
