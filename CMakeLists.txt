CMAKE_MINIMUM_REQUIRED(VERSION 2.8.4)

# find compiler and toolchain programs
find_program(AVRCPP avr-g++)
find_program(AVRC avr-gcc)
find_program(AVRAR avr-ar)
find_program(AVRSTRIP avr-strip)
find_program(OBJCOPY avr-objcopy)
find_program(OBJDUMP avr-objdump)
find_program(AVRSIZE avr-size)
find_program(AVRDUDE avrdude)
find_program(SCREEN screen)

# toolchain settings
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_CXX_COMPILER ${AVRCPP})
set(CMAKE_C_COMPILER ${AVRC})
set(CMAKE_ASM_COMPILER ${AVRC})

PROJECT(socket)

SET(MCU_SPEED "16000000UL")
SET(AVR_MCU "atmega168p")
set(AVR_H_FUSE 0xdf)
set(AVR_L_FUSE 0xf7)
set(AVR_E_FUSE 0x01)

set(AVR_UPLOADTOOL avrdude)
set(AVR_PROGRAMMER stk500v2)
set(AVR_UPLOADTOOL_PORT /dev/tty.usbserial-A100VSX4)

set(CMAKE_BUILD_TYPE Release)

include_directories(
#    modbus/ascii
#    modbus/functions
#    modbus/include
#    modbus/rtu
    smartbus
    port
    rtos
    socket
)

file(GLOB

    SOURCE

    main.c
#    "port/*.h"
#    "port/*.c"
#    "modbus/include/*.h"
#    "modbus/include/*.c"
#    "modbus/ascii/*.h"
#    "modbus/ascii/*.c"
#    "modbus/functions/*.h"
#    "modbus/functions/*.c"
#    "modbus/rtu/*.h"
#    "modbus/rtu/*.c"
#    "modbus/*.h"
#    "modbus/*.c"
        smartbus/*h
        smartbus/*c
        socket/*.h
        socket/*.c
        rtos/*.h
        rtos/*.c
)

SET(SOURCE_EXE

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