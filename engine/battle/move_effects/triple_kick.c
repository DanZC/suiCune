#include "../../../constants.h"
#include "triple_kick.h"

void BattleCommand_TripleKick(void){
//  triplekick

    // LD_A_addr(wBattleAnimParam);
    // LD_B_A;
    uint8_t b = wram->wBattleAnimParam + 1;
    // INC_B;
    // LD_HL(wCurDamage + 1);
    // LD_A_hld;
    // LD_E_A;
    // LD_A_hli;
    // LD_D_A;
    uint16_t dmg = ReverseEndian16(wram->wCurDamage);

    uint32_t temp = dmg;
    do {
    // next_kick:
        // DEC_B;
        // RET_Z ;
        if(--b == 0)
            return;
        // LD_A_hl;
        // ADD_A_E;
        // LD_hld_A;
        // LD_A_hl;
        // ADC_A_D;
        // LD_hli_A;
        temp += dmg;

    //  No overflow.
        wram->wCurDamage = ReverseEndian16((uint16_t)temp);
        // IF_NC goto next_kick;
    } while(!(temp & 0xff00));
    // LD_A(0xff);
    // LD_hld_A;
    // LD_hl_A;
    wram->wCurDamage = ReverseEndian16(0xffff);
    // RET;

}

void BattleCommand_KickCounter(void){
//  kickcounter

    // LD_HL(wBattleAnimParam);
    // INC_hl;
    wram->wBattleAnimParam++;
    // RET;
}
