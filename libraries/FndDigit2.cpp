#include "ArduFunc.h"
#include "FndDigit2.h"

uint8_t Byte2ShiftR(uint8_t byteB) {
  uint8_t i;
  CLR_BIT(PORT_OUT, LATCH_CLK);
  for (i = 0; i < 8; i++) {
    CLR_BIT(PORT_OUT, SHIFT_CLK);
    if (1 & byteB) {
      SET_BIT(PORT_OUT, REG_DAT);
    }
    else {
      CLR_BIT(PORT_OUT, REG_DAT);
    }
    SET_BIT(PORT_OUT, SHIFT_CLK);
    byteB >> 1;
  }
  SET_BIT(PORT_OUT, LATCH_CLK);
  return 0;
}

uint8_t Digt2FND(uint8_t numb) {
  SET_BIT(PORT_OUT, DIGIT1);
  Byte2ShiftR(digit[numb % 10]);
  _delay_ms(100);
  CLR_BIT(PORT_OUT, DIGIT1);
  SET_BIT(PORT_OUT, DIGIT2);
  Byte2ShiftR(digit[numb >> 3 + numb >> 1]);
  _delay_ms(100);
  CLR_BIT(PORT_OUT, DIGIT2);
  return 0;
}