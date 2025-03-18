#include "../../../constants.h"
#include "bide.h"
#include "../effect_commands.h"
#include "../core.h"
#include "../../../home/battle_vars.h"
#include "../../../home/battle.h"
#include "../../../data/text/battle.h"

void BattleCommand_StoreEnergy(void){
//  storeenergy

    // LD_A(BATTLE_VARS_SUBSTATUS3);
    // CALL(aGetBattleVar);
    // BIT_A(SUBSTATUS_BIDE);
    // RET_Z ;
    if(!bit_test(GetBattleVar(BATTLE_VARS_SUBSTATUS3), SUBSTATUS_BIDE))
        return;

    // LD_HL(wPlayerRolloutCount);
    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // IF_Z goto check_still_storing_energy;
    // LD_HL(wEnemyRolloutCount);
    uint8_t* rc = (hram->hBattleTurn == TURN_PLAYER)? &wram->wPlayerRolloutCount: &wram->wEnemyRolloutCount;

// check_still_storing_energy:
    // DEC_hl;
    // IF_NZ goto still_storing;
    if(--*rc != 0) {
    // still_storing:
        // LD_HL(mStoringEnergyText);
        // CALL(aStdBattleTextbox);
        StdBattleTextbox(StoringEnergyText);
        // JP(mEndMoveEffect);
        return EndMoveEffect();
    }

    // LD_A(BATTLE_VARS_SUBSTATUS3);
    // CALL(aGetBattleVarAddr);
    // RES_hl(SUBSTATUS_BIDE);
    bit_reset(*GetBattleVarAddr(BATTLE_VARS_SUBSTATUS3), SUBSTATUS_BIDE);

    // LD_HL(mUnleashedEnergyText);
    // CALL(aStdBattleTextbox);
    StdBattleTextbox(UnleashedEnergyText);

    // LD_A(BATTLE_VARS_MOVE_POWER);
    // CALL(aGetBattleVarAddr);
    // LD_A(1);
    // LD_hl_A;
    *GetBattleVarAddr(BATTLE_VARS_MOVE_POWER) = 1;
    // LD_HL(wPlayerDamageTaken + 1);
    // LD_DE(wPlayerCharging);  // player
    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // IF_Z goto player;
    // LD_HL(wEnemyDamageTaken + 1);
    // LD_DE(wEnemyCharging);  // enemy
    uint16_t* hl = (uint16_t*)((hram->hBattleTurn == TURN_PLAYER)? wram_ptr(wPlayerDamageTaken): wram_ptr(wEnemyDamageTaken));
    uint8_t* de = (hram->hBattleTurn == TURN_PLAYER)? &wram->wPlayerCharging: &wram->wEnemyCharging;

// player:
    // LD_A_hld;
    // ADD_A_A;
    // LD_B_A;
    // LD_addr_A(wCurDamage + 1);
    // LD_A_hl;
    // RL_A;
    // LD_addr_A(wCurDamage);
    uint32_t temp = BigEndianToNative16(*hl) << 1;
    // IF_NC goto not_maxed;
    if(temp > 0xffff) {
        // LD_A(0xff);
        // LD_addr_A(wCurDamage);
        // LD_addr_A(wCurDamage + 1);
        wram->wCurDamage = NativeToBigEndian16(0xffff);
    }
    else {
        wram->wCurDamage = NativeToBigEndian16((uint16_t)temp);
    }

// not_maxed:
    // OR_A_B;
    // IF_NZ goto built_up_something;
    if(temp == 0) {
        // LD_A(1);
        // LD_addr_A(wAttackMissed);
        wram->wAttackMissed = TRUE;
    }

// built_up_something:
    // XOR_A_A;
    // LD_hli_A;
    // LD_hl_A;
    *hl = 0;
    // LD_de_A;
    *de = 0;

    // LD_A(BATTLE_VARS_MOVE_ANIM);
    // CALL(aGetBattleVarAddr);
    // LD_A(BIDE);
    // LD_hl_A;
    *GetBattleVarAddr(BATTLE_VARS_MOVE_ANIM) = BIDE;

    // LD_B(unleashenergy_command);
    // JP(mSkipToBattleCommand);
    SkipToBattleCommand(unleashenergy_command);
}

void BattleCommand_UnleashEnergy(void){
//  unleashenergy

    // LD_DE(wPlayerDamageTaken);
    // LD_BC(wPlayerRolloutCount);
    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // IF_Z goto got_damage;
    // LD_DE(wEnemyDamageTaken);
    // LD_BC(wEnemyRolloutCount);
    uint16_t* de = (uint16_t*)((hram->hBattleTurn == TURN_PLAYER)? wram_ptr(wPlayerDamageTaken): wram_ptr(wEnemyDamageTaken));
    uint8_t* bc = (hram->hBattleTurn == TURN_PLAYER)? &wram->wPlayerRolloutCount: &wram->wEnemyRolloutCount;

// got_damage:
    // LD_A(BATTLE_VARS_SUBSTATUS3);
    // CALL(aGetBattleVarAddr);
    // SET_hl(SUBSTATUS_BIDE);
    bit_set(*GetBattleVarAddr(BATTLE_VARS_SUBSTATUS3), SUBSTATUS_BIDE);
    // XOR_A_A;
    // LD_de_A;
    // INC_DE;
    // LD_de_A;
    *de = 0;
    // LD_addr_A(wPlayerMoveStructEffect);
    wram->wPlayerMoveStruct.effect = 0;
    // LD_addr_A(wEnemyMoveStructEffect);
    wram->wEnemyMoveStruct.effect = 0;
    // CALL(aBattleRandom);
    // AND_A(1);
    // INC_A;
    // INC_A;
    // LD_bc_A;
    *bc = (v_BattleRandom_Conv() & 1) + 2;
    // LD_A(1);
    // LD_addr_A(wBattleAnimParam);
    wram->wBattleAnimParam = 1;
    // CALL(aAnimateCurrentMove);
    AnimateCurrentMove();
    // JP(mEndMoveEffect);
    return EndMoveEffect();

}
