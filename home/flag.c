#include "../constants.h"
#include "flag.h"
#include "../engine/events/engine_flags.h"

void ResetMapBufferEventFlags(void){
    wram->wEventFlags[0] = 0;
}

void ResetBikeFlags(void){
    wram->wBikeFlags = 0;
    wram->skip_119[0] = 0;
}

void ResetFlashIfOutOfCave(void){
    uint8_t env = wram->wEnvironment;
    if(env == ROUTE || env == TOWN)
    {
        bit_reset(wram->wStatusFlags, STATUSFLAGS_FLASH_F);
    }
}

uint8_t EventFlagAction(uint16_t bit, uint8_t func){
    return FlagAction(wram->wEventFlags, bit, func);
}

//  Perform action b on bit de in flag array hl.
uint8_t FlagAction(uint8_t* flag, uint16_t bit, uint8_t func){

//  inputs:
//  b: function
//     0  RESET_FLAG  clear bit
//     1  SET_FLAG    set bit
//     2  CHECK_FLAG  check bit
//  de: bit number
//  hl: pointer to the flag array

// get index within the byte
    uint8_t index = bit & 7;

// shift de right by three bits (get the index within memory)
    flag += bit >> 3;
    
// check b's value: 0, 1, 2
    if(func < SET_FLAG) {
        // clear bit
        *flag &= (1 << index) ^ 0xFF;
        return *flag;
    }
    if(func == SET_FLAG) {
        // set bit
        *flag |= (1 << index);
        return *flag;
    }
    else {
        // check bit
        return (*flag & (1 << index));
    }
}

bool CheckReceivedDex(void){
    return EngineFlagAction(ENGINE_POKEDEX, CHECK_FLAG);
}

//  //  unreferenced
//  Used in debug ROMs to walk through walls and avoid encounters.
bool CheckBPressedDebug(void){
    // LD_A_addr(wDebugFlags);
    // BIT_A(DEBUG_FIELD_F);
    // RET_Z ;

    // LDH_A_addr(hJoyDown);
    // BIT_A(B_BUTTON_F);
    // RET;
    return bit_test(wram->wDebugFlags, DEBUG_FIELD_F) && bit_test(hram.hJoyDown, B_BUTTON_F);
}

//  DEPRECATED: Just return z/0
uint8_t xor_a(uint8_t a){
    // XOR_A_A;
    // RET;
    return a ^ a;
}

//  DEPRECATED: Just return c/0xff
uint8_t xor_a_dec_a(uint8_t a){
    // XOR_A_A;
    // DEC_A;
    // RET;
    return (a ^ a) - 1;
}

//  //  unreferenced
// Return true (nz) or false (z)
bool CheckFieldDebug(void){
    return bit_test(wram->wDebugFlags, DEBUG_FIELD_F);
}
