//
// Created by delta54 on 9/21/16.
//

#include <avr/interrupt.h>
#include <stdio.h>
#include "uart.h"
#include "../modbus/modbus.h"

FIFO(64) uart_tx_fifo;
FIFO(64) uart_rx_fifo;

ISR( USART_RX_vect )
{
    if  (UCSR0A &(1<<FE0)) return; // FE-ошибка кадра

    u08 rxbyte = UDR0;
    if( !FIFO_IS_FULL( uart_rx_fifo ) ) {
        FIFO_PUSH( uart_rx_fifo, rxbyte );
    }

  ModBusReceiveFSM(rxbyte);
}

// обработчик прерывания по освобождению регистра данных передатчика
ISR( USART_UDRE_vect )
{
    if( FIFO_IS_EMPTY( uart_tx_fifo ) ) {
        //если данных в fifo больше нет то запрещаем это прерывание
        UCSR0B &= ~_BV(UDRIE0);
    } else {
        //иначе передаем следующий байт
        char txbyte = FIFO_FRONT( uart_tx_fifo );
        FIFO_POP( uart_tx_fifo );
        UDR0 = txbyte;

    }
}

int uart_putc(  char c, FILE *file )
{
    int ret;

    cli(); //запрещаем прерывания

    if( !FIFO_IS_FULL( uart_tx_fifo ) ) {
        //если в буфере есть место, то добавляем туда байт
        FIFO_PUSH( uart_tx_fifo, c );
        //и разрешаем прерывание по освобождению передатчика
        UCSR0B |= _BV(UDRIE0);

        ret = 0;
    } else {
        ret = -1; //буфер переполнен
    }

    sei(); //разрешаем прерывания

    return ret;
}


int uart_getc( FILE* file )
{
    int ret;

    cli(); //запрещаем прерывания

    if( !FIFO_IS_EMPTY( uart_rx_fifo ) ) {
        //если в буфере есть данные, то извлекаем их
        ret = FIFO_FRONT( uart_rx_fifo );
        FIFO_POP( uart_rx_fifo );
    } else {
        ret = _FDEV_EOF; //данных нет
    }

    sei(); //разрешаем прерывания

    return ret;
}

FILE uart_stream = FDEV_SETUP_STREAM(uart_putc, _FDEV_SETUP_WRITE, _FDEV_SETUP_RW);