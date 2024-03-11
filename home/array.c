#include "../constants.h"
#include "array.h"

void IsInArray(void){
    //  Find value a for every de bytes in array hl.
//  Return index in b and carry if found.

    LD_B(0);
    LD_C_A;

loop:
        LD_A_hl;
    CP_A(-1);
    IF_Z goto NotInArray;
    CP_A_C;
    IF_Z goto InArray;
    INC_B;
    ADD_HL_DE;
    goto loop;


NotInArray:
        AND_A_A;
    RET;


InArray:
        SCF;
    RET;

}

void IsInArray_Conv_Old(void)
{
    REG_B = 0;
    REG_C = REG_A;
    while(1)
    {
        REG_A = gb_read(REG_HL);
        if(REG_A == 0xFF)
        {
            AND_A_A;
            return;
        }
        if(REG_A == REG_C)
        {
            SCF;
            return;
        }
        REG_B++;
        REG_HL += REG_DE;
    }
}

//  Find value a for every de bytes in array hl.
//  Return index if found, otherwise 0xffff
uint16_t IsInArray_Conv(uint16_t hl, uint16_t de, uint8_t a)
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
uint16_t IsInArray_Conv_Item(const item_t* hl, item_t a) {
    uint16_t b = 0;
    while(1)
    {
        if(*hl == (item_t)-1)
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

bool IsInMoveArray(const move_t* hl, uint8_t a) {
    for(uint32_t i = 0; hl[i] != (move_t)-1; ++i) {
        if(hl[i] == a)
            return true;
    }
    return false;
}

void SkipNames(void){
    //  Skip a names.
    LD_BC(NAME_LENGTH);
    AND_A_A;
    RET_Z ;

loop:
        ADD_HL_BC;
    DEC_A;
    IF_NZ goto loop;
    RET;

}

//  Skip a names.
uint16_t SkipNames_Conv(uint16_t hl, uint8_t a)
{
    if(a == 0) return hl;
    do {
        hl += NAME_LENGTH;
    } while(--a != 0);
    return hl;
}

//  Skip a names.
const uint8_t* SkipNames_Conv2(const uint8_t* hl, uint8_t a) {
    return hl + (NAME_LENGTH * a);
}

void AddNTimes(void){
    //  Add bc * a to hl.
    AND_A_A;
    RET_Z ;

loop:
        ADD_HL_BC;
    DEC_A;
    IF_NZ goto loop;
    RET;

}

void AddNTimes_Conv_Old(void)
{
    if(REG_A == 0) return;
    do {
        REG_HL += REG_BC;
        REG_A--;
    } while(REG_A != 0);
}

uint16_t AddNTimes_Conv(uint16_t bc, uint16_t hl, uint8_t a)
{
    if(a == 0) return hl;
    do {
        hl += bc;
    } while(--a != 0);
    return hl;
}

// hl = hl + (bc * a)
uint8_t* AddNTimes_Conv2(uint8_t* hl, uint16_t bc, uint8_t a)
{
    return hl + (bc * a);
}