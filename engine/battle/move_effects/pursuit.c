#include "../../../constants.h"
#include "pursuit.h"

void BattleCommand_Pursuit(void){
//  pursuit
//  Double damage if the opponent is switching.

    // LD_HL(wEnemyIsSwitching);
    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // IF_Z goto ok;
    // LD_HL(wPlayerIsSwitching);
    uint8_t isSwitching = (hBattleTurn == 0)? wram->wEnemyIsSwitching: wram->wPlayerIsSwitching;

// ok:
    // LD_A_hl;
    // AND_A_A;
    // RET_Z ;
    if(!isSwitching)
        return;

    // LD_HL(wCurDamage + 1);
    // SLA_hl;
    // DEC_HL;
    // RL_hl;
    uint32_t temp = ReverseEndian16(wram->wCurDamage) << 1;
    // RET_NC ;
    if(temp > 0xffff) {
        // LD_A(0xff);
        // LD_hli_A;
        // LD_hl_A;
        wram->wCurDamage = ReverseEndian16(0xffff);
    }
    else {
        wram->wCurDamage = ReverseEndian16((uint16_t)temp);
    }
    // RET;
}
