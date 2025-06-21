#include <stdint.h>
#include <stddef.h>
#include "misc.h"

// Reverses the bits in a.
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

uint8_t RotateLeft8(uint8_t x, uint8_t carryIn, uint8_t* carryOut) {
    *carryOut = (x >> 7);
    return (x << 1) + (carryIn & 1);
}

uint8_t RotateRight8(uint8_t x, uint8_t carryIn, uint8_t* carryOut) {
    *carryOut = (x & 1);
    return (x >> 1) + (carryIn << 7);
}

uint8_t RotateLeftCarry8(uint8_t x, uint8_t* carryOut) {
    uint8_t carry = (x >> 7);
    *carryOut = carry;
    return (x << 1) + (carry & 1);
}

uint8_t RotateRightCarry8(uint8_t x, uint8_t* carryOut) {
    uint8_t carry = (x & 1);
    *carryOut = carry;
    return (x >> 1) + (carry << 7);
}

uint8_t RotateLeftC8(uint8_t x) {
    uint8_t carry = (x >> 7);
    return (x << 1) + (carry & 1);
}

uint8_t RotateRightC8(uint8_t x) {
    uint8_t carry = (x & 1);
    return (x >> 1) + (carry << 7);
}

_Bool IsLittleEndian(void){
    int n = 1;
    return *(char*)&n == 1;
}

// On little-endian systems, reverses the
// bytes of the 16-bit value.
uint16_t NativeToBigEndian16(uint16_t x) {
    if(IsLittleEndian()) {
        return (x << 8) | ((x >> 8) & 0xff);
    }
    return x;
}

// On little-endian systems, writes a byte-swapped 
// copy of an N-byte number from src to dest.
void NativeToBigEndianN(uint8_t* dest, const uint8_t* src, size_t n) {
    if(IsLittleEndian()) {
        for(size_t i = 0; i < n; ++i){
            dest[i] = src[n-i-1];
        }
    }
    else {
        for(size_t i = 0; i < n; ++i){
            dest[i] = src[i];
        }
    }
}

// Reverses the bytes of a 16-bit value.
uint16_t ReverseEndian16(uint16_t x) {
    return (x << 8) | ((x >> 8) & 0xff);
}

// Swaps size bytes between a and b.
void MemSwap(void* a_, void* b_, size_t size) {
    uint8_t* a = a_;
    uint8_t* b = b_;
    for(size_t i = size; i > 0; --i) {
        uint8_t temp = *a;
        *a = *b;
        *b = temp;
        a++;
        b++;
    }
}
