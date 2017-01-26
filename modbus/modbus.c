//
// Created by delta54 on 10/2/16.
//

#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include "modbus.h"
#include "commands.h"
#include "../rtos/EERTOS.h"
#include "../socket/uart.h"

#define MB_ASCII_DEFAULT_CR     '\r'    /*!< Default CR character for Modbus ASCII. */
#define MB_ASCII_DEFAULT_LF     '\n'    /*!< Default LF character for Modbus ASCII. */
#define MB_SER_PDU_SIZE_MAX     256     /*!< Maximum size of a Modbus ASCII frame. */

typedef enum
{
    STATE_RX_IDLE,              /*!< Receiver is in idle state. */
    STATE_RX_RCV,               /*!< Frame is beeing received. */
    STATE_RX_WAIT_EOF           /*!< Wait for End of Frame. */
} eMBRcvState;

typedef enum
{
    STATE_TX_IDLE,              /*!< Transmitter is in idle state. */
    STATE_TX_START,             /*!< Starting transmission (':' sent). */
    STATE_TX_DATA,              /*!< Sending of data (Address, Data, LRC). */
    STATE_TX_END,               /*!< End of transmission. */
    STATE_TX_NOTIFY             /*!< Notify sender that the frame has been sent. */
} eMBSndState;

typedef enum
{
    BYTE_HIGH_NIBBLE,           /*!< Character for high nibble of byte. */
    BYTE_LOW_NIBBLE             /*!< Character for low nibble of byte. */
} eMBBytePos;

u08 RxBuf[MaxLenghtRxBuf];        // буфер принимаемых данных
u08 TxBuf[MaxLenghtTxBuf];        // буфер передаваемых данных
u08 ucResult;

static eMBRcvState curRxState;
static eMBBytePos curRxBytePos;
static eMBSndState curTxState;
static volatile u08 curTxBufferCount;
static volatile u08 curRxBufferPos;
static volatile u08 *curRxBuffer = RxBuf;
static volatile u08 *curTxBuffer;

void ModbusInit() {
    curRxState = STATE_RX_IDLE;
}

void ModBusCheckPack(u08 NumByte) {

    if (curRxBuffer[0] != DEVICE_ADDRESS && curRxBuffer[0] != 0) //адрес устройства
        return;

    if (LRC((u08 *) curRxBuffer, NumByte) == 0) {         //подсчет LRC в принятой посылке
      errorMessage(ILLEGAL_LRC);
        return;
    }

    // этот пакет адресован нам
    switch (curRxBuffer[1]) {
      case 0x64:  //100
        echo((const u08 *) curRxBuffer, NumByte);
        break;
      case 0x03:
        read_state((const u08 *) curRxBuffer);
        break;
      case 0x04:
        write_state((const u08 *) curRxBuffer);
        break;
      default:
        errorMessage(ILLEGAL_FUNCTION);
        break;
    }
}

void ModBusReceiveFSM(const u08 ucByte) {

//    u08 ucByte = getchar();

    if (ucByte == EOF)
        return;

//    putchar( ucByte ); //

    switch (curRxState) {
        case STATE_RX_RCV:
            if( ucByte == ':' ) {
                curRxBytePos = BYTE_HIGH_NIBBLE;
                curRxBufferPos = 0;
            } else if( ucByte == MB_ASCII_DEFAULT_CR ) {
                curRxState = STATE_RX_WAIT_EOF;
            } else {
                ucResult = char2bin(ucByte);
                switch ( curRxBytePos )
                {
                    case BYTE_HIGH_NIBBLE:
                        if( curRxBufferPos < MB_SER_PDU_SIZE_MAX ) {
                            curRxBuffer[curRxBufferPos] = ( u08 )( ucResult << 4 );
                            curRxBytePos = BYTE_LOW_NIBBLE;
                            break;
                        } else {
                            curRxState = STATE_RX_IDLE;
                        }
                        break;
                    case BYTE_LOW_NIBBLE:
                        curRxBuffer[curRxBufferPos] |= ( u08 )( ucResult & 0xFF );
                        curRxBufferPos++;
                        curRxBytePos = BYTE_HIGH_NIBBLE;
                        break;
                }
            }
            break;
        case STATE_RX_WAIT_EOF:
            if (ucByte == MB_ASCII_DEFAULT_LF) {
                curRxState = STATE_RX_IDLE;
                ModBusCheckPack(curRxBufferPos);
            } else if( ucByte == ':' ) {
                curRxBytePos = BYTE_HIGH_NIBBLE;
                curRxBufferPos = 0;
                curRxState = STATE_RX_RCV;
            } else {
                curRxState = STATE_RX_IDLE;
            }
            break;
        case STATE_RX_IDLE:
            if (ucByte == ':') {
                curRxBufferPos = 0;
                curRxBytePos = BYTE_HIGH_NIBBLE;
                curRxState = STATE_RX_RCV;
            }
            break;
    }
}

void MobBusTransmitFSM() {

    u08 ucByte;

    switch ( curTxState )
    {
        case STATE_TX_START:
            ucByte = ':';
            uart_putc((u08)ucByte);
            curTxState = STATE_TX_DATA;
            curRxBytePos = BYTE_HIGH_NIBBLE;
            MobBusTransmitFSM();
            break;

        case STATE_TX_DATA:
            if( curTxBufferCount > 0 )
            {
                switch ( curRxBytePos )
                {
                    case BYTE_HIGH_NIBBLE:
                        ucByte = bin2char((u08) (*curTxBuffer >> 4));
                        uart_putc((u08)ucByte);
                        curRxBytePos = BYTE_LOW_NIBBLE;
                        break;

                    case BYTE_LOW_NIBBLE:
                        ucByte = bin2char((u08) (*curTxBuffer & 0x0F));
                        uart_putc((u08)ucByte);
                        curTxBuffer++;
                        curRxBytePos = BYTE_HIGH_NIBBLE;
                        curTxBufferCount--;
                        break;
                }
            } else {
                uart_putc((u08)MB_ASCII_DEFAULT_CR);
                curTxState = STATE_TX_END;
            }

            MobBusTransmitFSM();
            break;

        case STATE_TX_END:
            curTxBufferCount = 0;
            uart_putc((u08)MB_ASCII_DEFAULT_LF);
            curTxState = STATE_TX_NOTIFY;
            MobBusTransmitFSM();
            break;

        case STATE_TX_NOTIFY:
            curTxState = STATE_TX_IDLE;
            MobBusTransmitFSM();
            break;

        case STATE_TX_IDLE:
            SetTimerTask(ModbusSetRead, 10);
//            ModbusSetRead();
            break;
    }
}

void MobBusSend(const u08 *frame, const u08 length) {

    ModbusSetWrite();  //rs458

    curTxBuffer = (u08*)TxBuf;
    memcpy((u08*)curTxBuffer + 2, frame, length);
    curTxBufferCount = 2;

    curTxBuffer[0] = DEVICE_ADDRESS;
    curTxBuffer[1] = curRxBuffer[1];    //команда
    curTxBufferCount += length;

    u08 lrc = LRC((u08 *) curTxBuffer, curTxBufferCount);
    curTxBuffer[curTxBufferCount++] = lrc;

    curTxState = STATE_TX_START;
    MobBusTransmitFSM();
}

static u08 LRC(u08 *pucFrame, u08 usLen) {
    u08 lrc = 0;  /* LRC char initialized */

    while( usLen-- )
    {
        lrc += *pucFrame++;   /* Add buffer byte without carry */
    }

    /* Return twos complement */
    lrc = ( u08 ) ( -( ( CHAR ) lrc ) );
    return lrc;
}

static u08 char2bin(u08 ucByte) {
    if( ( ucByte >= '0' ) && ( ucByte <= '9' ) ) {
        return ( u08 )( ucByte - '0' );
    } else if( ( ucByte >= 'A' ) && ( ucByte <= 'F' ) ) {
        return ( u08 )( ucByte - 'A' + 0x0A );
    } else {
        return 0xFF;
    }
}

static u08 bin2char(u08 ucByte) {
    if( ucByte <= 0x09 ) {
        return ( u08 )( '0' + ucByte );
    } else if( ( ucByte >= 0x0A ) && ( ucByte <= 0x0F ) ) {
        return ( u08 )( ucByte - 0x0A + 'A' );
    }

    return '0';
}

// 1 - address        u08
// 2 - function       u08 + error bite
// 3 - error          u08
// 4 - lrc            u08
void errorMessage(u08 error) {

  u08 lrc;
  curTxBuffer[0] = DEVICE_ADDRESS;
  curTxBuffer[1] = (u08) (curRxBuffer[1] | 0x80);
  curTxBuffer[2] = error;

  lrc = LRC((u08 *) curTxBuffer, 3);
  curTxBuffer[3] = lrc;
  curTxBufferCount = 4;

  /* Activate the transmitter. */
  curTxState = STATE_TX_START;
  MobBusTransmitFSM();
}
