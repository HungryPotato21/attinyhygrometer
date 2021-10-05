#include "ArduFunc.h"
#include "DHT11.h"

uint8_t ReadDHT(uint8_t* d_arr) {
    uint8_t data[5], check;
    static uint8_t cnt;
    uint8_t i, j;
    /********Communication Start *********/
    /*** MCU --(start signal)--> DHT ***/
    /*Send Bus H>L for at least 18ms*/
    PB_OUT(DHT_PIN);
    CLR_BIT(PORT_OUT, DHT_PIN);
    _delay_ms(20);
    /*Pull up V and wait 20~40us for DHT response*/
    PB_OUT(DHT_PIN);
    SET_BIT(PORT_OUT, DHT_PIN);
    _delay_us(30);

    /*** DHT -->(Responses)---> MCU ***/
    /*Wait 80us for DHT H>L Bus*/
    cnt = 0;
    while (IS_SET(PORT_IN, DHT_PIN)) {
        if (cnt > 16) {
            return 0;
        }
        _delay_us(5); cnt++;
    }
    /*DHT pulls up and keep V high for preparing data transmission*/
    cnt = 0;
    while (!IS_SET(PORT_IN, DHT_PIN)) {
        if (cnt > 16) {
            return 0;
        }
        _delay_us(5); cnt++;
    }

    /****Receive Data from DHT *****/
    /*Start to 50us LOW voltage level*/
    for (i = 0; i < 5; i++) {
        for (j = 7; j >= 0; j--) {
            cnt = 0;
            while (!IS_SET(PORT_IN, DHT_PIN)) {
                if (cnt > 10) {
                    return 0;
                }
                _delay_us(5); cnt++;
            }
            cnt = 0;
            while (IS_SET(PORT_IN, DHT_PIN)) {
                if (cnt > 16) {
                    return 0;
                }
                _delay_us(5); cnt++;
            }
            if ((cnt > 6 ? 1 : 0)) {
                SET_BIT(data[i], j);
            }
            else {
                CLR_BIT(data[i], j);
            }
        }
    }
    /******** Communication End *********/
    check = (data[0] + data[1] + data[2] + data[3]) & 0xFF;
    if (check != data[4]) {
        return 0;
    }
    for (i = 0; i < 4; i++) {
        d_arr[i] = data[i];
    }
    return 0;
}