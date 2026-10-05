#include "../constants.h"
#include "array.h"

//  Find value a for every de bytes in array hl.
//  Return index (b, carry) if found, otherwise 0xffff
uint16_t IsInArray_GB(uint16_t hl, uint16_t de, uint8_t a)
{
    uint8_t b = 0;
    while(1)
    {
        uint8_t byte = gb_read(hl);
        if(byte == 0xFF)
            return 0xFFFF;
        if(byte == a)
            return b;
        b++;
        hl += de;
    }
}

//  Find value a for every de bytes in array hl.
//  Return index if found, otherwise 0xffff
uint16_t IsInArray_Item(const item_t* hl, item_t a) {
    uint16_t b = 0;
    while(1)
    {
        if(*hl == ITEM_NULL)
            return 0xFFFF;
        if(*hl == a)
            return b;
        b++;
        hl++;
    }
}

bool IsInU8Array(const uint8_t* hl, uint8_t a) {
    for(uint32_t i = 0; hl[i] != 0xff; ++i) {
        if(hl[i] == a)
            return true;
    }
    return false;
}

const struct BlockPointer* ArrayFindStructBlockPointer(const struct BlockPointer* hl, uint8_t a) {
    for(uint32_t i = 0; hl[i].tileset != 0xff; ++i) {
        if(hl[i].tileset == a)
            return hl + i;
    }
    return NULL;
}

bool IsInMoveArray(const move_t* hl, size_t count, move_t a) {
    for(uint32_t i = 0; i < count; ++i) {
        if(hl[i] == a)
            return true;
    }
    return false;
}

//  Skip a names.
const uint8_t* SkipNames(const uint8_t* hl, uint8_t a) {
    return hl + (NAME_LENGTH * a);
}

// hl = hl + (bc * a)
uint8_t* AddNTimes(uint8_t* hl, uint16_t bc, uint8_t a)
{
    return hl + (bc * a);
}

//  Add bc * a to hl.
uint16_t AddNTimes_GB(uint16_t bc, uint16_t hl, uint8_t a)
{
    if(a == 0) return hl;
    do {
        hl += bc;
    } while(--a != 0);
    return hl;
}