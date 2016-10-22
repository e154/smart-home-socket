CMAKE_MINIMUM_REQUIRED(VERSION 2.8.4)

PROJECT(socket)

SET(MCU_SPEED "16000000UL")
SET(AVR_MCU "atmega168p")
set(AVR_H_FUSE 0xdf)
set(AVR_L_FUSE 0xf7)
set(AVR_E_FUSE 0x01)

set(AVR_UPLOADTOOL avrdude)
set(AVR_PROGRAMMER stk500v2)
set(AVR_UPLOADTOOL_PORT /dev/ttyUSB0)

set(CMAKE_BUILD_TYPE Release)

SET(SOURCE_EXE

        main.c
        rtos/avrlibdefs.h
        rtos/avrlibtypes.h
        rtos/EERTOS.c
        rtos/EERTOS.h
        rtos/EERTOSHAL.h
        rtos/EERTOSHAL.c
        rtos/HAL.c
        rtos/HAL.h
        socket/uart.c
        socket/uart.h
        socket/common.h
        socket/fifo.h
        socket/adc.h
        socket/adc.c
        socket/lm35.h
        socket/lm35.c
        socket/ftoa.h
        socket/ftoa.c
        socket/socket.c
        socket/socket.h
        modbus/tools.h
        modbus/tools.c
        modbus/modbus.h
        modbus/modbus.c
        modbus/commands.h
        modbus/commands.c
        config.h
)

SET(SOURCE_LIB


)

##########################################################################
# compiler options for all build types
##########################################################################
add_definitions("-DF_CPU=${MCU_SPEED}")
#add_definitions("-fpack-struct")
#add_definitions("-fshort-enums")
#add_definitions("-Wall")
#add_definitions("-Werror")
#add_definitions("-pedantic")
#add_definitions("-pedantic-errors")
#add_definitions("-funsigned-char")
#add_definitions("-funsigned-bitfields")
#add_definitions("-ffunction-sections")
#add_definitions("-c")
add_definitions("-std=gnu99")
add_definitions("-mmcu=${AVR_MCU}")

##########################################################################

include(avr-gcc.cmake)