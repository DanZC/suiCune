#include "../../constants.h"
#include "engine_flags.h"
#include "../../data/events/engine_flags.h"

//  Do action b on engine flag de
//
//    b = 0: reset flag
//      = 1: set flag
//      > 1: check flag, result in c
//
//  Setting/resetting does not return a result.
void EngineFlagAction(void){

//  16-bit flag ids are considered invalid, but it's nice
//  to know that the infrastructure is there.

    LD_A_D;
    CP_A(HIGH(NUM_ENGINE_FLAGS));
    IF_Z goto ceiling;
    IF_C goto read;  // cp 0 can't set carry!
    goto invalid;

//  There are only NUM_ENGINE_FLAGS engine flags, so
//  anything beyond that is invalid too.


ceiling:
    LD_A_E;
    CP_A(LOW(NUM_ENGINE_FLAGS));
    IF_C goto read;

//  Invalid flags are treated as flag 00.


invalid:
    XOR_A_A;
    LD_E_A;
    LD_D_A;

//  Get this flag's location.


read:
    LD_HL(mEngineFlags);
//  location
    ADD_HL_DE;
    ADD_HL_DE;
//  bit
    ADD_HL_DE;

//  location
    LD_E_hl;
    INC_HL;
    LD_D_hl;
    INC_HL;
//  bit
    LD_C_hl;

//  What are we doing with this flag?

    LD_A_B;
    CP_A(1);
    IF_C goto reset;  // b = 0
    IF_Z goto set;  // b = 1

//  Return the given flag in c.
//  check
    LD_A_de;
    AND_A_C;
    LD_C_A;
    RET;

//  Set the given flag.

set:
    LD_A_de;
    OR_A_C;
    LD_de_A;
    RET;

//  Reset the given flag.

reset:
    LD_A_C;
    CPL;  // AND all bits except the one in question
    LD_C_A;
    LD_A_de;
    AND_A_C;
    LD_de_A;
    RET;

// INCLUDE "data/events/engine_flags.asm"

}

//  Do action b on engine flag de
//
//    b = 0: reset flag
//      = 1: set flag
//      > 1: check flag, result in c
//
//  Setting/resetting does not return a result.
bool EngineFlagAction_Conv(uint16_t de, uint8_t b){

//  16-bit flag ids are considered invalid, but it's nice
//  to know that the infrastructure is there.

    // LD_A_D;
    // CP_A(HIGH(NUM_ENGINE_FLAGS));
    // IF_Z goto ceiling;
    // ceiling:
        // LD_A_E;
        // CP_A(LOW(NUM_ENGINE_FLAGS));
        // IF_C goto read;
    if(de >= NUM_ENGINE_FLAGS) {
    //  There are only NUM_ENGINE_FLAGS engine flags, so
    //  anything beyond that is invalid too.

    //  Invalid flags are treated as flag 00.


    // invalid:
        // XOR_A_A;
        // LD_E_A;
        // LD_D_A;
        de = 0;
    }
    // IF_C goto read;  // cp 0 can't set carry!
    // goto invalid;

//  Get this flag's location.


// read:
    // LD_HL(mEngineFlags);
//  location
    // ADD_HL_DE;
    // ADD_HL_DE;
//  bit
    // ADD_HL_DE;

//  location
    // LD_E_hl;
    // INC_HL;
    // LD_D_hl;
    // INC_HL;
//  bit
    // LD_C_hl;

//  What are we doing with this flag?

    // LD_A_B;
    // CP_A(1);
    // IF_C goto reset;  // b = 0
    // IF_Z goto set;  // b = 1
    switch(b)
    {
        case 0: 
        //  Reset the given flag.
        // reset:
            // LD_A_C;
            // CPL;  // AND all bits except the one in question
            // LD_C_A;
            // LD_A_de;
            // AND_A_C;
            // LD_de_A;
            // RET;
            *EngineFlags[de].ptr &= (1 << EngineFlags[de].bit) ^ 0xff;
            return false;
        case 1:
        //  Set the given flag.

        // set:
            // LD_A_de;
            // OR_A_C;
            // LD_de_A;
            // RET;
            *EngineFlags[de].ptr |= (1 << EngineFlags[de].bit);
            return true;

        default:
        //  Return the given flag in c.
        //  check
            // LD_A_de;
            // AND_A_C;
            // LD_C_A;
            // RET;
            return *EngineFlags[de].ptr & (1 << EngineFlags[de].bit);
    }

// INCLUDE "data/events/engine_flags.asm"
    return false;
}
