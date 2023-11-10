#include <stdint.h>
#include "misc.h"

uint8_t BitReverse8(uint8_t a) {
    uint8_t b = 0;
    for(int i = 0; i < 8; ++i) {
        uint8_t temp = a & 1;
        a >>= 1;
        b = (b << 1) | temp;
    }
    return b;
}

uint8_t SubCarry8(uint8_t a, uint8_t b, uint8_t carryIn, uint8_t* carryOut) {
    uint16_t temp = a - b - carryIn;
    *carryOut = (temp & 0xff00)? 1: 0;
    return (uint8_t)(temp & 0xff);
}

uint8_t AddCarry8(uint8_t a, uint8_t b, uint8_t carryIn, uint8_t* carryOut) {
    uint16_t temp = a + b + carryIn;
    *carryOut = (temp & 0xff00)? 1: 0;
    return (uint8_t)(temp & 0xff);
}
