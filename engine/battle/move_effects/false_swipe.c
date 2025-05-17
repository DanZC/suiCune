#include "../../../constants.h"
#include "false_swipe.h"

void BattleCommand_FalseSwipe(void){
//  falseswipe

//  Makes sure wCurDamage < MonHP
    CheckFalseSwipe();
}

bool CheckFalseSwipe(void) {
    // LD_HL(wEnemyMonHP);
    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // IF_Z goto got_hp;
    // LD_HL(wBattleMonHP);
    uint16_t hp = BigEndianToNative16((hram.hBattleTurn == TURN_PLAYER)? wram->wEnemyMon.hp: wram->wBattleMon.hp);

// got_hp:
    // LD_DE(wCurDamage);
    uint16_t dmg = BigEndianToNative16(wram->wCurDamage);
    // LD_C(2);
    // PUSH_HL;
    // PUSH_DE;
    // CALL(aCompareBytes);
    // POP_DE;
    // POP_HL;
    // IF_C goto done;
    if(dmg >= hp) {
        // LD_A_hli;
        // LD_de_A;
        // INC_DE;
        // LD_A_hl;
        // DEC_A;
        // LD_de_A;
        wram->wCurDamage = NativeToBigEndian16(hp - 1);

        // INC_A;
        // IF_NZ goto okay;
        // DEC_DE;
        // LD_A_de;
        // DEC_A;
        // LD_de_A;
    // okay:

        // LD_A_addr(wCriticalHit);
        // CP_A(2);
        // IF_NZ goto carry;
        if(wram->wCriticalHit == 2) {
            // XOR_A_A;
            // LD_addr_A(wCriticalHit);
            wram->wCriticalHit = 0;
        }

    // carry:
        // SCF;
        // RET;
        return true;
    }

// done:
    // AND_A_A;
    // RET;
    return false;
}
