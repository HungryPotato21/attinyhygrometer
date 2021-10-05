#define ATTINY_VER 85

#include "ArduFunc.h"
#include "DHT11.h"
#include "FndDigit2.h"

#if ATTINY_VER == 85
#include "DigiKeyboard.h"
#endif

int main() {
  uint8_t data[4];
  static uint8_t clk = 0;

  while (1) {
    ReadDHT(&data[0]);
    while (clk < 65) {
      clk++;
      Digt2FND(data[0]);
    }
    #if ATTINY_VER == 85
      DigiKeyboard.println("Humidity:");
      DigiKeyboard.println(data[0]);
    #endif
  }
}
