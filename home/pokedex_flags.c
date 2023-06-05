#include "../constants.h"
#include "pokedex_flags.h"

void CountSetBits(void){
    //  Count the number of set bits in b bytes starting from hl.
//  Return in a, c and [wNumSetBits].
    LD_C(0);

next:
        LD_A_hli;
    LD_E_A;
    LD_D(8);


count:
        SRL_E;
    LD_A(0);
    ADC_A_C;
    LD_C_A;
    DEC_D;
    IF_NZ goto count;

    DEC_B;
    IF_NZ goto next;

    LD_A_C;
    LD_addr_A(wNumSetBits);
    RET;

}

void GetWeekday(void){
        LD_A_addr(wCurDay);

mod:
        SUB_A(7);
    IF_NC goto mod;
    ADD_A(7);
    RET;

}

uint8_t GetWeekday_Conv(void){
    // LD_A_addr(wCurDay);
    uint8_t day = gb_read(wCurDay);
// mod:
//         SUB_A(7);
//     IF_NC goto mod;
//     ADD_A(7);
//     RET;
    return day % 7;
}

void SetSeenAndCaughtMon(void){
        PUSH_AF;
    LD_C_A;
    LD_HL(wPokedexCaught);
    LD_B(SET_FLAG);
    CALL(aPokedexFlagAction);
    POP_AF;
// fallthrough

    return SetSeenMon();
}

void SetSeenMon(void){
        LD_C_A;
    LD_HL(wPokedexSeen);
    LD_B(SET_FLAG);
    JR(mPokedexFlagAction);

}

void CheckCaughtMon(void){
        LD_C_A;
    LD_HL(wPokedexCaught);
    LD_B(CHECK_FLAG);
    JR(mPokedexFlagAction);

}

void CheckSeenMon(void){
        LD_C_A;
    LD_HL(wPokedexSeen);
    LD_B(CHECK_FLAG);
// fallthrough

    return PokedexFlagAction();
}

void PokedexFlagAction(void){
        LD_D(0);
    PREDEF(pSmallFarFlagAction);
    LD_A_C;
    AND_A_A;
    RET;

}
