#pragma once
uint8_t BitReverse8(uint8_t a);
uint8_t SubCarry8(uint8_t a, uint8_t b, uint8_t carryIn, uint8_t* carryOut);
uint8_t AddCarry8(uint8_t a, uint8_t b, uint8_t carryIn, uint8_t* carryOut);
uint8_t RotateLeft8(uint8_t x, uint8_t carryIn, uint8_t* carryOut);
uint8_t RotateRight8(uint8_t x, uint8_t carryIn, uint8_t* carryOut);
uint8_t RotateLeftCarry8(uint8_t x, uint8_t* carryOut);
uint8_t RotateRightCarry8(uint8_t x, uint8_t* carryOut);
uint8_t RotateLeftC8(uint8_t x);
uint8_t RotateRightC8(uint8_t x);
uint16_t NativeToBigEndian16(uint16_t x);
#define BigEndianToNative16 NativeToBigEndian16
uint16_t ReverseEndian16(uint16_t x);
