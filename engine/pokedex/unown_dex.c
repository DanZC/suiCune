#include "../../constants.h"
#include "unown_dex.h"

void UpdateUnownDex(void){
    LD_A_addr(wUnownLetter);
    LD_C_A;
    LD_B(NUM_UNOWN);
    LD_HL(wUnownDex);

loop:
    LD_A_hli;
    AND_A_A;
    IF_Z goto done;
    CP_A_C;
    RET_Z ;
    DEC_B;
    IF_NZ goto loop;
    RET;


done:
    DEC_HL;
    LD_hl_C;
    RET;

}

void UpdateUnownDex_Conv(unown_letter_t letter){
    // LD_A_addr(wUnownLetter);
    // LD_C_A;
    // LD_B(NUM_UNOWN);
    // LD_HL(wUnownDex);
    unown_letter_t* hl = wram->wUnownDex;

    for(uint32_t i = 0; i < NUM_UNOWN; ++i) {
    // loop:
        // LD_A_hli;
        // AND_A_A;
        // IF_Z goto done;
        if(hl[i] == 0) {
        // done:
            // DEC_HL;
            // LD_hl_C;
            hl[i] = letter;
            // RET;
            return;
        }
        // CP_A_C;
        // RET_Z ;
        if(hl[i] == letter)
            return;
        // DEC_B;
        // IF_NZ goto loop;
    }
    // RET;
}

void PrintUnownWord(void){
    hlcoord(4, 15, wTilemap);
    LD_BC(12);
    LD_A(0x7f);
    CALL(aByteFill);
    LD_A_addr(wDexCurUnownIndex);
    LD_E_A;
    LD_D(0);
    LD_HL(wUnownDex);
    ADD_HL_DE;
    LD_A_hl;
    LD_E_A;
    LD_D(0);
    LD_HL(mUnownWords);
    ADD_HL_DE;
    ADD_HL_DE;
    LD_A_hli;
    LD_E_A;
    LD_D_hl;
    hlcoord(4, 15, wTilemap);

loop:
    LD_A_de;
    CP_A(-1);
    RET_Z ;
    INC_DE;
    LD_hli_A;
    goto loop;

// INCLUDE "data/pokemon/unown_words.asm"

}
