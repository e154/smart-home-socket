//
// Created by delta54 on 9/15/16.
//

#ifndef UART_ADC_H
#define UART_ADC_H

#define CHANELS 1

volatile uint16_t value[CHANELS];

uint16_t adc_read(uint8_t ch);

#endif //UART_ADC_H
