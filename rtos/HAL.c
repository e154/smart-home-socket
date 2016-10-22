#include "HAL.h"
#include "../socket/common.h"
#include "../socket/adc.h"
#include <util/setbaud.h>

inline void InitAll(void)
{
#if defined(__AVR_ATmega16__)

    //InitUSART
    UBRRL = LO(bauddivider);
    UBRRH = HI(bauddivider);
    UCSRA = 0;
    UCSRB = 1<<RXEN|1<<TXEN|0<<RXCIE|0<<TXCIE;
    UCSRC = 1<<URSEL|1<<UCSZ0|1<<UCSZ1;

#elif defined(__AVR_ATmega168P__)

    //InitUSART
    //---------------------------------------------------------------------------
    UBRR0L = LO(bauddivider);
    UBRR0H = HI(bauddivider);
//    UBRR0L = UBRRH_VALUE;
//    UBRR0H = UBRRL_VALUE;
    UCSR0A = 0;
    UCSR0B = _BV(RXEN0) | _BV(TXEN0) | _BV(RXCIE0);
    UCSR0C = _BV(UCSZ00) | _BV(UCSZ01);

    //Init ADC
    //---------------------------------------------------------------------------
    ADMUX = 0;
    ADMUX |= _BV(REFS1) | _BV(REFS0);
    ADCSRA = _BV(ADEN) |  _BV(ADIE) | _BV(ADPS2) | _BV(ADPS1) | _BV(ADPS0);
    ADCSRA |= _BV(ADSC);

    //Init PWM
    //---------------------------------------------------------------------------

    //Init Interrupts
    //---------------------------------------------------------------------------
    EICRA |= _BV(ISC00);
    EIMSK |= _BV(INT0);

    //Init Timers
    //---------------------------------------------------------------------------

    //InitPort
    //---------------------------------------------------------------------------

#endif
}



