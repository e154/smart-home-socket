//
// Created by delta54 on 9/30/16.
//

#ifndef CMAKE_AVR_CONFIG_H
#define CMAKE_AVR_CONFIG_H

#include <avr/io.h>

#define BUZZER_PORT         PORTD
#define BUZZER_PIN          PD4
#define TOGGLE_PORT         PORTD
#define TOGGLE_PIN          PD3
#define PHAZE_PIN           PD2

#define TEMPER_PORT         PORTC
#define TEMPER_PIN          PC0

#define PWR_LED_PORT        PORTD
#define PWR_LED             PD5

#define MAX485_PORT         PORTB
#define MAX485_PIN          PB0
#define MAX_TEMP            1089 // 109C^

#define DEVICE_ADDRESS      0x01       /*!< Device address hex format. */

#endif //CMAKE_AVR_CONFIG_H
