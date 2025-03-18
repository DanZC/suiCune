#include "../../../constants.h"
#include "rollout.h"
#include "../effect_commands.h"
#include "../../../home/battle.h"
#include "../../../home/battle_vars.h"

#define MAX_ROLLOUT_COUNT (5)

void BattleCommand_CheckCurl(void){
//  checkcurl

    // LD_DE(wPlayerRolloutCount);
    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // IF_Z goto ok;
    // LD_DE(wEnemyRolloutCount);
    uint8_t* de = (hram->hBattleTurn == TURN_PLAYER)? &wram->wPlayerRolloutCount: &wram->wEnemyRolloutCount;

// ok:
    // LD_A(BATTLE_VARS_SUBSTATUS1);
    // CALL(aGetBattleVar);
    // BIT_A(SUBSTATUS_ROLLOUT);
    // IF_Z goto reset;
    if(bit_test(GetBattleVar(BATTLE_VARS_SUBSTATUS1), SUBSTATUS_ROLLOUT)) {

        // LD_B(doturn_command);
        // JP(mSkipToBattleCommand);
        return SkipToBattleCommand(doturn_command);
    }

// reset:
    // XOR_A_A;
    // LD_de_A;
    *de = 0;
    // RET;
}

void BattleCommand_RolloutPower(void){
//  rolloutpower

    // LD_A(BATTLE_VARS_STATUS);
    // CALL(aGetBattleVar);
    // AND_A(SLP);
    // RET_NZ ;
    if(GetBattleVar(BATTLE_VARS_STATUS) & SLP)
        return;

    // LD_HL(wPlayerRolloutCount);
    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // IF_Z goto got_rollout_count;
    // LD_HL(wEnemyRolloutCount);
    uint8_t* hl = (hram->hBattleTurn == TURN_PLAYER)? &wram->wPlayerRolloutCount: &wram->wEnemyRolloutCount;

// got_rollout_count:
    // LD_A_hl;
    // AND_A_A;
    // IF_NZ goto skip_set_rampage;
    if(*hl == 0) {
        // LD_A(1);
        // LD_addr_A(wSomeoneIsRampaging);
        wram->wSomeoneIsRampaging = TRUE;
    }

// skip_set_rampage:
    // LD_A_addr(wAttackMissed);
    // AND_A_A;
    // IF_Z goto hit;

    if(wram->wAttackMissed) {
        // LD_A(BATTLE_VARS_SUBSTATUS1);
        // CALL(aGetBattleVarAddr);
        // RES_hl(6);
        bit_reset(*GetBattleVarAddr(BATTLE_VARS_SUBSTATUS1), SUBSTATUS_ROLLOUT);
        // RET;
        return;
    }

// hit:
    // INC_hl;
    // LD_A_hl;
    // LD_B_A;
    uint8_t b = ++*hl;
    // CP_A(MAX_ROLLOUT_COUNT);
    // IF_C goto not_done_with_rollout;

    if(b >= MAX_ROLLOUT_COUNT) {
        // LD_A(BATTLE_VARS_SUBSTATUS1);
        // CALL(aGetBattleVarAddr);
        // RES_hl(SUBSTATUS_ROLLOUT);
        bit_reset(*GetBattleVarAddr(BATTLE_VARS_SUBSTATUS1), SUBSTATUS_ROLLOUT);
        // goto done_with_substatus_flag;
    }
    else {
    // not_done_with_rollout:
        // LD_A(BATTLE_VARS_SUBSTATUS1);
        // CALL(aGetBattleVarAddr);
        // SET_hl(SUBSTATUS_ROLLOUT);
        bit_set(*GetBattleVarAddr(BATTLE_VARS_SUBSTATUS1), SUBSTATUS_ROLLOUT);
    }

// done_with_substatus_flag:
    // LD_A(BATTLE_VARS_SUBSTATUS2);
    // CALL(aGetBattleVar);
    // BIT_A(SUBSTATUS_CURLED);
    // IF_Z goto not_curled;
    if(bit_test(GetBattleVar(BATTLE_VARS_SUBSTATUS2), SUBSTATUS_CURLED)) {
        // INC_B;
        ++b;
    }

// not_curled:
    uint32_t dmg = BigEndianToNative16(wram->wCurDamage);

    while(--b != 0) {
    // loop:
        // DEC_B;
        // IF_Z goto done_damage;

        // LD_HL(wCurDamage + 1);
        // SLA_hl;
        // DEC_HL;
        // RL_hl;
        dmg <<= 1;
        // IF_NC goto loop;
        if(dmg & 0xffff0000) {
            // LD_A(0xff);
            // LD_hli_A;
            // LD_hl_A;
            dmg = 0xffff;
            break;
        }
    }


// done_damage:
    wram->wCurDamage = NativeToBigEndian16((uint16_t)dmg);
    // RET;
}
