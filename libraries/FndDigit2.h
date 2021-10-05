#ifndef	FNDDIGIT2_H
#define	FNDDIGIT2_H

#define REG_DAT PB1
#define SHIFT_CLK PB2
#define LATCH_CLK PB3
#define DIGIT1  PB4
#define DIGIT2  PB5

const uint8_t digit[10] = {     //seven segment digits in bits
  0b00111111, //0
  0b00000110, //1
  0b01011011, //2
  0b01001111, //3
  0b01100110, //4
  0b01101101, //5
  0b01111101, //6
  0b00000111, //7
  0b01111111, //8
  0b01101111  //9
};

uint8_t Byte2ShiftR(uint8_t byteB);
//Function that send a bit in the byte(byteB) form most right to left

uint8_t Digt2FND(uint8_t numb);
//Function that send two digits alternatly to 74HC595

#endif