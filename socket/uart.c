//
// Created by delta54 on 9/21/16.
//

#include <avr/interrupt.h>
#include "uart.h"
#include "../modbus/modbus.h"

ISR( USART_RX_vect )
{
    if  (UCSR0A &(1<<FE0)) return; // FE-ошибка кадра
    ModBusReceiveFSM(UDR0);
}

void uart_putc(char c)
{
  cli();
  loop_until_bit_is_set(UCSR0A, UDRE0); /* Wait until data register empty. */
  UDR0 = c;
  loop_until_bit_is_set(UCSR0A, TXC0); /* Wait until transmission ready. */
  sei();
}
