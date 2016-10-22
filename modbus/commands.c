//
// Created by delta54 on 08.10.16.
//

#include "commands.h"
#include "modbus.h"
#include "../socket/socket.h"

void echo(const u08* ucASCIIBuf, const u08 NumByte) {
  MobBusSend(ucASCIIBuf, NumByte);
}

void get_status() {

//    printf("temperature %i\r\n", current_temp);

    u08 s[7];
    s[0] = Hi(current_temp);    // температура
    s[1] = LOW(current_temp);
    s[2] = 0;                   // состояние (вкл/выкл)
    s[3] = 0;                   // фаза (есть/нет)
    s[4] = 0;                   // alert
    s[5] = Hi(MAX_TEMP);        // мак. темп. сраб. отключения
    s[6] = LOW(MAX_TEMP);

    // alert
    if (alert)
      s[4] = 1;

    // состояние (вкл/выкл)
    if (line_is_high(DDRD, TOGGLE_PIN))
      s[2] = 1;

    // фаза (есть/нет)
    if (phase)
      s[3] = 1;

  MobBusSend(s, 7);
}

void read_state(const u08* ucASCIIBuf) {

    u16 start_addr, col_nums;

    col_nums = (u16)(ucASCIIBuf[4] << 8) + ucASCIIBuf[5];
    if (col_nums != 5 ) {
      errorMessage(ILLEGAL_DATA_ADDRESS);
        return;
    }

    start_addr = (u16)(ucASCIIBuf[2] << 8) + ucASCIIBuf[3];
    if (start_addr != 0) {
      errorMessage(ILLEGAL_DATA_ADDRESS);
        return;
    }

    get_status();
}

void write_state(const u08* ucASCIIBuf) {

    u16 state;

    state = (u16)(ucASCIIBuf[2] << 8) + ucASCIIBuf[3];
    if (state != 1 && state != 0) {
      errorMessage(ILLEGAL_DATA_VALUE);
      return;
    }

    if ( state == 1 ) {
      EnableSocket();
    } else {
      DisableSocket();
    }

    get_status();
}