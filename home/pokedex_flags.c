#include "../constants.h"
#include "pokedex_flags.h"
#include "../engine/smallflag.h"

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

static unsigned int popcount8(uint8_t x)
{
    unsigned int count;
    for(count = 0; x; count++) {
        x &= x - 1;
    }
    return count;
}

//  Count the number of set bits in b bytes starting from hl.
//  Return in a, c and [wNumSetBits].
uint8_t CountSetBits_Conv(uint16_t hl, uint8_t b){
    // LD_C(0);
    uint8_t c = 0;

// next:
    // LD_A_hli;
    // LD_E_A;
    // LD_D(8);


// count:
    // SRL_E;
    // LD_A(0);
    // ADC_A_C;
    // LD_C_A;
    // DEC_D;
    // IF_NZ goto count;

    // DEC_B;
    // IF_NZ goto next;

    for(uint8_t i = 0; i < b; ++i) {
        c += (uint8_t)popcount8(gb_read(hl + i));
    }

    // LD_A_C;
    // LD_addr_A(wNumSetBits);
    // RET;
    wram->wNumSetBits = c;
    return c;
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
    uint8_t day = wram->wCurDay;
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

void SetSeenAndCaughtMon_Conv(dex_t c){
    // PUSH_AF;
    // LD_C_A;
    // LD_HL(wPokedexCaught);
    // LD_B(SET_FLAG);
    // CALL(aPokedexFlagAction);
    PokedexFlagAction_Conv(wram->wPokedexCaught, c, SET_FLAG);
    // POP_AF;
// fallthrough

    return SetSeenMon_Conv(c);
}

void SetSeenMon(void){
        LD_C_A;
    LD_HL(wPokedexSeen);
    LD_B(SET_FLAG);
    JR(mPokedexFlagAction);

}

void SetSeenMon_Conv(dex_t c){
    // LD_C_A;
    // LD_HL(wPokedexSeen);
    // LD_B(SET_FLAG);
    // JR(mPokedexFlagAction);
    PokedexFlagAction_Conv(wram->wPokedexSeen, c, SET_FLAG);
}

void CheckCaughtMon(void){
        LD_C_A;
    LD_HL(wPokedexCaught);
    LD_B(CHECK_FLAG);
    JR(mPokedexFlagAction);

}

bool CheckCaughtMon_Conv(dex_t c){
    // LD_C_A;
    // LD_HL(wPokedexCaught);
    // LD_B(CHECK_FLAG);
    // JR(mPokedexFlagAction);
    return PokedexFlagAction_Conv(wram->wPokedexCaught, c, CHECK_FLAG);
}

void CheckSeenMon(void){
        LD_C_A;
    LD_HL(wPokedexSeen);
    LD_B(CHECK_FLAG);
// fallthrough

    return PokedexFlagAction();
}

bool CheckSeenMon_Conv(dex_t c){
    // LD_C_A;
    // LD_HL(wPokedexSeen);
    // LD_B(CHECK_FLAG);
// fallthrough
    return PokedexFlagAction_Conv(wram->wPokedexSeen, c, CHECK_FLAG);
}

void PokedexFlagAction(void){
    LD_D(0);
    PREDEF(pSmallFarFlagAction);
    LD_A_C;
    AND_A_A;
    RET;

}

bool PokedexFlagAction_Conv(uint8_t* hl, dex_t c, uint8_t b){
    // LD_D(0);
    // PREDEF(pSmallFarFlagAction);
    // LD_A_C;
    // AND_A_A;
    // RET;
    return SmallFarFlagAction_Conv(hl, (uint8_t)c, b) != 0;
}
