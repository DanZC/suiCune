#include "../../../constants.h"
#include "future_sight.h"
#include "../effect_commands.h"
#include "../core.h"
#include "../../../home/battle.h"
#include "../../../home/battle_vars.h"
#include "../../../data/text/battle.h"

void BattleCommand_CheckFutureSight(void){
//  checkfuturesight

    // LD_HL(wPlayerFutureSightCount);
    // LD_DE(wPlayerFutureSightDamage);
    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // IF_Z goto ok;
    // LD_HL(wEnemyFutureSightCount);
    // LD_DE(wEnemyFutureSightDamage);
    uint8_t* hl = (hram.hBattleTurn == TURN_PLAYER)? &wram->wPlayerFutureSightCount: &wram->wEnemyFutureSightCount;
    uint16_t de = (hram.hBattleTurn == TURN_PLAYER)? wram->wPlayerFutureSightDamage: wram->wEnemyFutureSightDamage;

// ok:

    // LD_A_hl;
    // AND_A_A;
    // RET_Z ;
    if(*hl == 0)
        return;
    // CP_A(1);
    // RET_NZ ;
    if(*hl != 1)
        return;

    // LD_hl(0);
    *hl = 0;
    // LD_A_de;
    // INC_DE;
    // LD_addr_A(wCurDamage);
    // LD_A_de;
    // LD_addr_A(wCurDamage + 1);
    wram->wCurDamage = de;
    // LD_B(futuresight_command);
    // JP(mSkipToBattleCommand);
    SkipToBattleCommand(futuresight_command);

}

void BattleCommand_FutureSight(void){
//  futuresight

    // CALL(aCheckUserIsCharging);
    // IF_NZ goto AlreadyChargingFutureSight;
    if(!CheckUserIsCharging()) {
        // LD_A(BATTLE_VARS_MOVE_ANIM);
        // CALL(aGetBattleVar);
        // LD_B_A;
        move_t b = GetBattleVar(BATTLE_VARS_MOVE_ANIM);
        // LD_A(BATTLE_VARS_LAST_COUNTER_MOVE);
        // CALL(aGetBattleVarAddr);
        // LD_hl_B;
        *GetBattleVarAddr(BATTLE_VARS_LAST_COUNTER_MOVE) = b;
        // LD_A(BATTLE_VARS_LAST_MOVE);
        // CALL(aGetBattleVarAddr);
        // LD_hl_B;
        *GetBattleVarAddr(BATTLE_VARS_LAST_MOVE) = b;
    }

// AlreadyChargingFutureSight:
    // LD_HL(wPlayerFutureSightCount);
    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // IF_Z goto GotFutureSightCount;
    // LD_HL(wEnemyFutureSightCount);
    uint8_t* hl = (hram.hBattleTurn == TURN_PLAYER)? &wram->wPlayerFutureSightCount: &wram->wEnemyFutureSightCount;

// GotFutureSightCount:
    // LD_A_hl;
    // AND_A_A;
    // IF_NZ goto failed;
    if(*hl != 0) {
    // failed:
        // POP_BC;
        // CALL(aResetDamage);
        ResetDamage();
        // CALL(aAnimateFailedMove);
        AnimateFailedMove();
        // CALL(aPrintButItFailed);
        PrintButItFailed();
        // JP(mEndMoveEffect);
        return EndMoveEffect();
    }
    // LD_A(4);
    // LD_hl_A;
    *hl = 4;
    // CALL(aBattleCommand_LowerSub);
    BattleCommand_LowerSub();
    // CALL(aBattleCommand_MoveDelay);
    BattleCommand_MoveDelay();
    // LD_HL(mForesawAttackText);
    // CALL(aStdBattleTextbox);
    StdBattleTextbox(ForesawAttackText);
    // CALL(aBattleCommand_RaiseSub);
    BattleCommand_RaiseSub();
    // LD_DE(wPlayerFutureSightDamage);
    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // IF_Z goto StoreDamage;
    // LD_DE(wEnemyFutureSightDamage);
    uint16_t* de = (uint16_t*)((hram.hBattleTurn == TURN_PLAYER)? wram_ptr(wPlayerFutureSightDamage): wram_ptr(wEnemyFutureSightDamage));

// StoreDamage:
    // LD_HL(wCurDamage);
    // LD_A_hl;
    // LD_de_A;
    // LD_hl(0);
    // INC_HL;
    // INC_DE;
    // LD_A_hl;
    // LD_de_A;
    // LD_hl(0);
    *de = wram->wCurDamage;
    wram->wCurDamage = 0;
    // JP(mEndMoveEffect);
    return EndMoveEffect();

}
