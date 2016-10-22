//
// Created by delta54 on 9/16/16.
//

#include "lm35.h"
#include "adc.h"

double read_temperature_in_C ()
{
    return  value[0] / 9.34;
}