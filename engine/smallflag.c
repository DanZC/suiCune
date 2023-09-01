#include "../constants.h"
#include "smallflag.h"
#include "../home/copy.h"

void SmallFarFlagAction(void){
//  Perform action b on bit c in flag array hl.
//  If checking a flag, check flag array d:hl unless d is 0.

//  For longer flag arrays, see FlagAction.

    PUSH_HL;
    PUSH_BC;

//  Divide by 8 to get the byte we want.
    PUSH_BC;
    SRL_C;
    SRL_C;
    SRL_C;
    LD_B(0);
    ADD_HL_BC;
    POP_BC;

//  Which bit we want from the byte
    LD_A_C;
    AND_A(7);
    LD_C_A;

//  Shift left until we can mask the bit
    LD_A(1);
    IF_Z goto shifted;

shift:
    ADD_A_A;
    DEC_C;
    IF_NZ goto shift;

shifted:
    LD_C_A;

//  What are we doing to this flag?
    DEC_B;
    IF_Z goto set;  // 1 = SET_FLAG
    DEC_B;
    IF_Z goto check;  // 2 = CHECK_FLAG
// 0 = RESET_FLAG

//  reset
    LD_A_C;
    CPL;
    AND_A_hl;
    LD_hl_A;
    goto done;


set:
    LD_A_hl;
    OR_A_C;
    LD_hl_A;
    goto done;


check:
    LD_A_D;
    CP_A(0);
    IF_NZ goto farcheck;

    LD_A_hl;
    AND_A_C;
    goto done;


farcheck:
    CALL(aGetFarByte);
    AND_A_C;


done:
    POP_BC;
    POP_HL;
    LD_C_A;
    RET;

}

//  Perform action b on bit c in flag array hl.
//  If checking a flag, check flag array d:hl unless d is 0.
uint8_t SmallFarFlagAction_Conv(uint8_t* hl, uint8_t c, uint8_t b){
//  For longer flag arrays, see FlagAction.
    // PUSH_HL;
    // PUSH_BC;

//  Divide by 8 to get the byte we want.
    // PUSH_BC;
    // SRL_C;
    // SRL_C;
    // SRL_C;
    // LD_B(0);
    // ADD_HL_BC;
    hl += c >> 3;
    // POP_BC;

//  Which bit we want from the byte
    // LD_A_C;
    // AND_A(7);
    // LD_C_A;

//  Shift left until we can mask the bit
    // LD_A(1);
    // IF_Z goto shifted;

// shift:
    // ADD_A_A;
    // DEC_C;
    // IF_NZ goto shift;

// shifted:
    // LD_C_A;
    c = 1 << (c & 0x7);

//  What are we doing to this flag?
    // DEC_B;
    // IF_Z goto set;  // 1 = SET_FLAG
    // DEC_B;
    // IF_Z goto check;  // 2 = CHECK_FLAG
    switch(b) {
    default:
    // 0 = RESET_FLAG

    //  reset
        // LD_A_C;
        // CPL;
        // AND_A_hl;
        // LD_hl_A;
        // goto done;
        (*hl) &= (c ^ 0xff);
        return *hl;
    case SET_FLAG:
    // set:
        // LD_A_hl;
        // OR_A_C;
        // LD_hl_A;
        (*hl) |= c;
        return *hl;
    case CHECK_FLAG:
    // check:
        // LD_A_D;
        // CP_A(0);
        // IF_NZ goto farcheck;
        // farcheck:
            // CALL(aGetFarByte);
            // AND_A_C;
        // LD_A_hl;
        // AND_A_C;
        return (*hl) & c;
    }
// done:
    // POP_BC;
    // POP_HL;
    // LD_C_A;
    // RET;
    return 0;
}
