#include "../../../constants.h"
#include "fury_cutter.h"

void BattleCommand_FuryCutter(void){
//  furycutter

    // LD_HL(wPlayerFuryCutterCount);
    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // IF_Z goto go;
    // LD_HL(wEnemyFuryCutterCount);
    struct BattleStatus* status = UserBattleStatus();

// go:
    // LD_A_addr(wAttackMissed);
    // AND_A_A;
    // JP_NZ (mResetFuryCutterCount);
    if(gBattle.attackMissed)
        return ResetFuryCutterCount();

    // INC_hl;
    ++status->furyCutterCount;

//  Damage capped at 5 turns' worth (16x).
    // LD_A_hl;
    // LD_B_A;
    uint8_t b = status->furyCutterCount;
    // CP_A(6);
    // IF_C goto checkdouble;
    // LD_B(5);
    if(b >= 6) {
        b = 5;
    }

    uint16_t dmg = BigEndianToNative16(wram->wCurDamage);
    uint8_t carry = 0;

    do {
    // checkdouble:
        // DEC_B;
        // RET_Z ;
        if(--b == 0) {
            wram->wCurDamage = NativeToBigEndian16(dmg);
            return;
        }

    //  Double the damage
        // LD_HL(wCurDamage + 1);
        // SLA_hl;
        // DEC_HL;
        // RL_hl;
        carry = (dmg >> 15);
        dmg <<= 1;
        // IF_NC goto checkdouble;
    } while(!carry);

//  No overflow
    // LD_A(0xff);
    // LD_hli_A;
    // LD_hl_A;
    wram->wCurDamage = NativeToBigEndian16(0xffff);
    // RET;
}

void ResetFuryCutterCount(void){
    // PUSH_HL;

    // LD_HL(wPlayerFuryCutterCount);
    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // IF_Z goto reset;
    // LD_HL(wEnemyFuryCutterCount);
    UserBattleStatus()->furyCutterCount = 0;

// reset:
    // XOR_A_A;
    // LD_hl_A;

    // POP_HL;
    // RET;
}
