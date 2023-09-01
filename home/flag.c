#include "../constants.h"
#include "flag.h"
#include "../engine/events/engine_flags.h"

void ResetMapBufferEventFlags(void){
        XOR_A_A;
    LD_HL(wEventFlags);
    LD_hli_A;
    RET;

}

void ResetMapBufferEventFlags_Conv(void){
    wram->wEventFlags[0] = 0;
}

void ResetBikeFlags(void){
        XOR_A_A;
    LD_HL(wBikeFlags);
    LD_hli_A;
    LD_hl_A;
    RET;

}

void ResetBikeFlags_Conv(void){
    gb_write(wBikeFlags, 0);
    gb_write(wBikeFlags + 1, 0);
}

void ResetFlashIfOutOfCave(void){
        LD_A_addr(wEnvironment);
    CP_A(ROUTE);
    IF_Z goto outdoors;
    CP_A(TOWN);
    IF_Z goto outdoors;
    RET;


outdoors:
        LD_HL(wStatusFlags);
    RES_hl(STATUSFLAGS_FLASH_F);
    RET;

}

void ResetFlashIfOutOfCave_Conv(void){
    uint8_t env = wram->wEnvironment;
    if(env == ROUTE || env == TOWN)
    {
        wram->wStatusFlags &= ((1 << STATUSFLAGS_FLASH_F) ^ 0xFF);
    }
}

void EventFlagAction(void){
        LD_HL(wEventFlags);
    CALL(aFlagAction);
    RET;

}

void FlagAction(void){
    //  Perform action b on bit de in flag array hl.

//  inputs:
//  b: function
//     0  RESET_FLAG  clear bit
//     1  SET_FLAG    set bit
//     2  CHECK_FLAG  check bit
//  de: bit number
//  hl: pointer to the flag array

// get index within the byte
    LD_A_E;
    AND_A(7);

// shift de right by three bits (get the index within memory)
    for(int rept = 0; rept < 3; rept++){
    SRL_D;
    RR_E;
    }
    ADD_HL_DE;

// implement a decoder
    LD_C(1);
    RRCA;
    IF_NC goto one;
    RLC_C;

one:
        RRCA;
    IF_NC goto two;
    RLC_C;
    RLC_C;

two:
        RRCA;
    IF_NC goto three;
    SWAP_C;

three:
    
// check b's value: 0, 1, 2
    LD_A_B;
    CP_A(SET_FLAG);
    IF_C goto clearbit;  // RESET_FLAG
    IF_Z goto setbit;  // SET_FLAG

// check bit
    LD_A_hl;
    AND_A_C;
    LD_C_A;
    RET;


setbit:
    // set bit
    LD_A_hl;
    OR_A_C;
    LD_hl_A;
    RET;


clearbit:
    // clear bit
    LD_A_C;
    CPL;
    AND_A_hl;
    LD_hl_A;
    RET;

}

void EventFlagAction_Conv(uint16_t bit, uint8_t func){
    FlagAction_Conv(wEventFlags, bit, func);
}

uint8_t EventFlagAction_Conv2(uint16_t bit, uint8_t func){
    return FlagAction_Conv2(wram->wEventFlags, bit, func);
}

//  Perform action b on bit de in flag array hl.
void FlagAction_Conv(uint16_t flag, uint16_t bit, uint8_t func){

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
        gb_write(flag, ((1 << index) ^ 0xFF) & gb_read(flag));
    }
    if(func == SET_FLAG) {
        // set bit
        gb_write(flag, (1 << index) | gb_read(flag));
    }
    else {
        // check bit
        REG_A = gb_read(flag) & (1 << index);
    }
}

//  Perform action b on bit de in flag array hl.
uint8_t FlagAction_Conv2(uint8_t* flag, uint16_t bit, uint8_t func){

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

void CheckReceivedDex(void){
        LD_DE(ENGINE_POKEDEX);
    LD_B(CHECK_FLAG);
    FARCALL(aEngineFlagAction);
    LD_A_C;
    AND_A_A;
    RET;

}

bool CheckReceivedDex_Conv(void){
    return EngineFlagAction_Conv(ENGINE_POKEDEX, CHECK_FLAG);
}

void CheckBPressedDebug(void){
    //  //  unreferenced
//  Used in debug ROMs to walk through walls and avoid encounters.

    LD_A_addr(wDebugFlags);
    BIT_A(DEBUG_FIELD_F);
    RET_Z ;

    LDH_A_addr(hJoyDown);
    BIT_A(B_BUTTON_F);
    RET;

}

//  //  unreferenced
//  Used in debug ROMs to walk through walls and avoid encounters.
bool CheckBPressedDebug_Conv(void){
    // LD_A_addr(wDebugFlags);
    // BIT_A(DEBUG_FIELD_F);
    // RET_Z ;

    // LDH_A_addr(hJoyDown);
    // BIT_A(B_BUTTON_F);
    // RET;
    return bit_test(wram->wDebugFlags, DEBUG_FIELD_F) && bit_test(hram->hJoyDown, B_BUTTON_F);
}

void xor_a(void){
        XOR_A_A;
    RET;

}

uint8_t xor_a_Conv(uint8_t a){
    // XOR_A_A;
    // RET;
    return a ^ a;
}

void xor_a_dec_a(void){
        XOR_A_A;
    DEC_A;
    RET;

}

uint8_t xor_a_dec_a_Conv(uint8_t a){
    // XOR_A_A;
    // DEC_A;
    // RET;
    return (a ^ a) - 1;
}

void CheckFieldDebug(void){
    //  //  unreferenced
    PUSH_HL;
    LD_HL(wDebugFlags);
    BIT_hl(DEBUG_FIELD_F);
    POP_HL;
    RET;

}

bool CheckFieldDebug_Conv(void){
    //  //  unreferenced
    return bit_test(wram->wDebugFlags, DEBUG_FIELD_F);
}
