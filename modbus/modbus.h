//
// Created by delta54 on 10/2/16.
//

#ifndef CMAKE_AVR_MODBUS_H
#define CMAKE_AVR_MODBUS_H

#include "../socket/common.h"
#include "../rtos/avrlibtypes.h"
#include "../config.h"
#include <stdio.h>

#define MaxLenghtRxBuf 25
#define MaxLenghtTxBuf 25

// errors
#define ILLEGAL_FUNCTION        0x01
#define ILLEGAL_DATA_ADDRESS    0x02
#define ILLEGAL_DATA_VALUE      0x03
#define SLAVE_DEVICE_FAILURE    0x04
#define ACKNOWLEDGE             0x05
#define SLAVE_DEVICE_BUSY       0x06
#define NEGATIVE_ACKNOWLEDGE    0x07
#define MEMORY_PARITY_ERROR     0x08
#define ILLEGAL_LRC             0x09

void ModbusInit();
void ModBusCheckPack(const u08 NumByte);
void ModBusReceiveFSM(const u08 ucByte);
void MobBusTransmitFSM();
void errorMessage(u08 error);

static u08 LRC(u08 *pucFrame, u08 usLen);
static u08 char2bin(u08 ucCharacter);
static u08 bin2char(u08 ucByte);
void MobBusSend(const u08 *frame, u08 length);

inline void ModbusSetRead() {
    output_low(MAX485_PORT, MAX485_PIN);
}

inline void ModbusSetWrite() {
    output_high(MAX485_PORT, MAX485_PIN);
}

#endif //CMAKE_AVR_MODBUS_H
