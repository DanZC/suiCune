#include "../../constants.h"
#include "effect_commands.h"
#include "core.h"
#include "../../data/battle/effect_command_pointers.h"
#include "check_battle_scene.h"
#include "misc.h"
#include "used_move_text.h"
#include "../battle_anims/anim_commands.h"
#include "../../data/items/attributes.h"
#include "../../data/types/type_matchups.h"
#include "../../data/types/type_boost_items.h"
#include "../../data/moves/flail_reversal_power.h"
#include "../../data/moves/critical_hit_moves.h"
#include "../../home/array.h"
#include "../../home/battle_vars.h"
#include "../../home/battle.h"
#include "../../home/copy.h"
#include "../../home/copy_name.h"
#include "../../home/tilemap.h"
#include "../../home/text.h"
#include "../../home/sram.h"
#include "../../data/text/battle.h"
#include "../../data/text/common.h"
#include "../../home/names.h"
#include "../../data/moves/moves.h"
#include "../../data/moves/effects.h"
#include "../../home/delay.h"
#include "../../data/battle/stat_multipliers.h"
#include "../../data/battle/accuracy_multipliers.h"
#include "../../data/battle/stat_names.h"
#include "../../data/battle/critical_hit_chances.h"
#include "../pokemon/health.h"
#include <stddef.h>

struct BattleCmdState gBattleCmdState;

void DoPlayerTurn(void){
    // CALL(aSetPlayerTurn);
    SetPlayerTurn();

    // LD_A_addr(wBattlePlayerAction);
    // AND_A_A;  // BATTLEPLAYERACTION_USEMOVE?
    // RET_NZ ;
    if(wram->wBattlePlayerAction != BATTLEPLAYERACTION_USEMOVE)
        return;

    // JR(mDoTurn);
    return DoTurn();
}

void DoEnemyTurn(void){
    // CALL(aSetEnemyTurn);
    SetEnemyTurn();

    // LD_A_addr(wLinkMode);
    // AND_A_A;
    // JR_Z (mDoTurn);
    if(wram->wLinkMode == LINK_NULL)
        return DoTurn();

    // LD_A_addr(wBattleAction);
    // CP_A(BATTLEACTION_STRUGGLE);
    // JR_Z (mDoTurn);
    if(wram->wBattleAction == BATTLEACTION_STRUGGLE)
        return DoTurn();
    // CP_A(BATTLEACTION_SWITCH1);
    // RET_NC ;
    if(wram->wBattleAction >= BATTLEACTION_SWITCH1)
        return;

// fallthrough

    return DoTurn();
}

void DoTurn(void){
//  Read in and execute the user's move effects for this turn.

    // XOR_A_A;
    // LD_addr_A(wTurnEnded);
    wram->wTurnEnded = FALSE;

// Effect command checkturn is called for every move.
    // CALL(aCheckTurn);
    CheckTurn();

    // LD_A_addr(wTurnEnded);
    // AND_A_A;
    // RET_NZ ;
    if(wram->wTurnEnded)
        return;

    // CALL(aUpdateMoveData);
    UpdateMoveData();

    return DoMove();
}

void DoMove(void){
//  Get the user's move effect.
    // LD_A(BATTLE_VARS_MOVE_EFFECT);
    // CALL(aGetBattleVar);
    // LD_C_A;
    // LD_B(0);
    // LD_HL(mMoveEffectsPointers);
    // ADD_HL_BC;
    // ADD_HL_BC;
    // LD_A(BANK(aMoveEffectsPointers));
    // CALL(aGetFarWord);
    const uint8_t* hl = MoveEffectsPointers[GetBattleVar(BATTLE_VARS_MOVE_EFFECT)];

    // LD_DE(wBattleScriptBuffer);
    uint8_t* de = wram->wBattleScriptBuffer;

    uint8_t a = 0;
    do {
    // GetMoveEffect:
        // LD_A(BANK(aMoveEffects));
        // CALL(aGetFarByte);
        // INC_HL;
        a = *(hl++);
        // LD_de_A;
        // INC_DE;
        *(de++) = a;
        // CP_A(endmove_command);
        // IF_NZ goto GetMoveEffect;
    } while(a != endmove_command);

//  Start at the first command.
    // LD_HL(wBattleScriptBuffer);
    // LD_A_L;
    // LD_addr_A(wBattleScriptBufferAddress);
    // LD_A_H;
    // LD_addr_A(wBattleScriptBufferAddress + 1);
    wram->wBattleScriptBufferAddress = 0;

    while(1) {
    // ReadMoveEffectCommand:
    //  ld a, [wBattleScriptBufferAddress++]
        // LD_A_addr(wBattleScriptBufferAddress);
        // LD_L_A;
        // LD_A_addr(wBattleScriptBufferAddress + 1);
        // LD_H_A;

        // LD_A_hli;
        a = wram->wBattleScriptBuffer[wram->wBattleScriptBufferAddress++];

        // PUSH_AF;
        // LD_A_L;
        // LD_addr_A(wBattleScriptBufferAddress);
        // LD_A_H;
        // LD_addr_A(wBattleScriptBufferAddress + 1);
        // POP_AF;

    //  endturn_command (-2) is used to terminate branches without ending the read cycle.
        // CP_A(endturn_command);
        // RET_NC ;
        if(a >= endturn_command)
            return;

    //  The rest of the commands (01-af) are read from BattleCommandPointers.
        // PUSH_BC;
        // DEC_A;
        // LD_C_A;
        // LD_B(0);
        // LD_HL(mBattleCommandPointers);
        // ADD_HL_BC;
        // ADD_HL_BC;
        // POP_BC;

        // LD_A(BANK(aBattleCommandPointers));
        // CALL(aGetFarWord);

        // CALL_hl;
        BattleCommandPointers[a-1]();
        
        // goto ReadMoveEffectCommand;
    }


// DoMoveEffectCommand:

    // JP_hl;
    // BattleCommandPointers[REG_BC]();
}

void CheckTurn(void){
    return BattleCommand_CheckTurn();
}

void BattleCommand_CheckTurn(void){
//  checkturn

//  Repurposed as hardcoded turn handling. Useless as a command.

//  Move $ff immediately ends the turn.
    PEEK("");
    // LD_A(BATTLE_VARS_MOVE);
    // CALL(aGetBattleVar);
    // INC_A;
    // JP_Z (mEndTurn);
    if(GetBattleVar(BATTLE_VARS_MOVE) == 0xff)
        return EndTurn();

    // XOR_A_A;
    // LD_addr_A(wAttackMissed);
    wram->wAttackMissed = FALSE;
    // LD_addr_A(wEffectFailed);
    wram->wEffectFailed = FALSE;
    // LD_addr_A(wBattleAnimParam);
    wram->wBattleAnimParam = 0;
    // LD_addr_A(wAlreadyDisobeyed);
    wram->wAlreadyDisobeyed = FALSE;
    // LD_addr_A(wAlreadyFailed);
    wram->wAlreadyFailed = FALSE;
    // LD_addr_A(wSomeoneIsRampaging);
    wram->wSomeoneIsRampaging = FALSE;

    // LD_A(EFFECTIVE);
    // LD_addr_A(wTypeModifier);
    wram->wTypeModifier = EFFECTIVE;

    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // JP_NZ (mCheckEnemyTurn);
    if(hram->hBattleTurn != TURN_PLAYER)
        return CheckEnemyTurn();

//  check player turn
    // LD_HL(wPlayerSubStatus4);
    // BIT_hl(SUBSTATUS_RECHARGE);
    // IF_Z goto no_recharge;
    if(bit_test(wram->wPlayerSubStatus4, SUBSTATUS_RECHARGE)) {
        // RES_hl(SUBSTATUS_RECHARGE);
        bit_reset(wram->wPlayerSubStatus4, SUBSTATUS_RECHARGE);
        // LD_HL(mMustRechargeText);
        // CALL(aStdBattleTextbox);
        StdBattleTextbox(MustRechargeText);
        // CALL(aCantMove);
        CantMove();
        // JP(mEndTurn);
        return EndTurn();
    }

// no_recharge:

    // LD_HL(wBattleMonStatus);
    // LD_A_hl;
    // AND_A(SLP);
    // IF_Z goto not_asleep;
    if(wram->wBattleMon.status[0] & SLP) {
        // DEC_A;
        // LD_addr_A(wBattleMonStatus);
        wram->wBattleMon.status[0]--;
        // AND_A(SLP);
        // IF_Z goto woke_up;

        if(wram->wBattleMon.status[0] & SLP) {
            // XOR_A_A;
            // LD_addr_A(wNumHits);
            wram->wNumHits = 0;
            // LD_DE(ANIM_SLP);
            // CALL(aFarPlayBattleAnimation);
            FarPlayBattleAnimation(ANIM_SLP);
            // goto fast_asleep;
        // fast_asleep:
            // LD_HL(mFastAsleepText);
            // CALL(aStdBattleTextbox);
            StdBattleTextbox(FastAsleepText);

        // Snore and Sleep Talk bypass sleep.
            // LD_A_addr(wCurPlayerMove);
            // CP_A(SNORE);
            // IF_Z goto not_asleep;
            // CP_A(SLEEP_TALK);
            // IF_Z goto not_asleep;
            if(wram->wCurPlayerMove != SNORE
            && wram->wCurPlayerMove != SLEEP_TALK) {
                // CALL(aCantMove);
                CantMove();
                // JP(mEndTurn);
                return EndTurn();
            }
        }
        else {

        // woke_up:
            // LD_HL(mWokeUpText);
            // CALL(aStdBattleTextbox);
            StdBattleTextbox(WokeUpText);
            // CALL(aCantMove);
            CantMove();
            // CALL(aUpdateBattleMonInParty);
            UpdateBattleMonInParty();
            // LD_HL(mUpdatePlayerHUD);
            // CALL(aCallBattleCore);
            UpdatePlayerHUD();
            // LD_A(0x1);
            // LDH_addr_A(hBGMapMode);
            hram->hBGMapMode = BGMAPMODE_UPDATE_TILES;
            // LD_HL(wPlayerSubStatus1);
            // RES_hl(SUBSTATUS_NIGHTMARE);
            bit_reset(wram->wPlayerSubStatus1, SUBSTATUS_NIGHTMARE);
            // goto not_asleep;
        }
    }

// not_asleep:

    // LD_HL(wBattleMonStatus);
    // BIT_hl(FRZ);
    // IF_Z goto not_frozen;
    if(bit_test(wram->wBattleMon.status[0], FRZ)) {
    // Flame Wheel and Sacred Fire thaw the user.
        // LD_A_addr(wCurPlayerMove);
        // CP_A(FLAME_WHEEL);
        // IF_Z goto not_frozen;
        // CP_A(SACRED_FIRE);
        // IF_Z goto not_frozen;

        if(wram->wCurPlayerMove != FLAME_WHEEL
        && wram->wCurPlayerMove != SACRED_FIRE) {
            // LD_HL(mFrozenSolidText);
            // CALL(aStdBattleTextbox);
            StdBattleTextbox(FrozenSolidText);

            // CALL(aCantMove);
            CantMove();
            // JP(mEndTurn);
            return EndTurn();
        }
    }

// not_frozen:

    // LD_HL(wPlayerSubStatus3);
    // BIT_hl(SUBSTATUS_FLINCHED);
    // IF_Z goto not_flinched;

    if(bit_test(wram->wPlayerSubStatus3, SUBSTATUS_FLINCHED)) {
        // RES_hl(SUBSTATUS_FLINCHED);
        bit_reset(wram->wPlayerSubStatus3, SUBSTATUS_FLINCHED);
        // LD_HL(mFlinchedText);
        // CALL(aStdBattleTextbox);
        StdBattleTextbox(FlinchedText);

        // CALL(aCantMove);
        CantMove();
        // JP(mEndTurn);
        return EndTurn();
    }

// not_flinched:

    // LD_HL(wPlayerDisableCount);
    // LD_A_hl;
    // AND_A_A;
    // IF_Z goto not_disabled;

    if(wram->wPlayerDisableCount != 0) {
        // DEC_A;
        // LD_hl_A;
        // AND_A(0xf);
        // IF_NZ goto not_disabled;
        if((--wram->wPlayerDisableCount & 0xf) == 0) {
            // LD_hl_A;
            wram->wPlayerDisableCount &= 0xf;
            // LD_addr_A(wDisabledMove);
            wram->wDisabledMove = NO_MOVE;
            // LD_HL(mDisabledNoMoreText);
            // CALL(aStdBattleTextbox);
            StdBattleTextbox(DisabledNoMoreText);
        }
    }

// not_disabled:

    // LD_A_addr(wPlayerSubStatus3);
    // ADD_A_A;
    // IF_NC goto not_confused;
    if(bit_test(wram->wPlayerSubStatus3, SUBSTATUS_CONFUSED)) {
        // LD_HL(wPlayerConfuseCount);
        // DEC_hl;
        // IF_NZ goto confused;
        if(--wram->wPlayerConfuseCount == 0) {
            // LD_HL(wPlayerSubStatus3);
            // RES_hl(SUBSTATUS_CONFUSED);
            bit_reset(wram->wPlayerSubStatus3, SUBSTATUS_CONFUSED);
            // LD_HL(mConfusedNoMoreText);
            // CALL(aStdBattleTextbox);
            StdBattleTextbox(ConfusedNoMoreText);
            // goto not_confused;
        }
        else {
        // confused:
            // LD_HL(mIsConfusedText);
            // CALL(aStdBattleTextbox);
            StdBattleTextbox(IsConfusedText);
            // XOR_A_A;
            // LD_addr_A(wNumHits);
            wram->wNumHits = 0;
            // LD_DE(ANIM_CONFUSED);
            // CALL(aFarPlayBattleAnimation);
            FarPlayBattleAnimation(ANIM_CONFUSED);

        // 50% chance of hitting itself
            // CALL(aBattleRandom);
            // CP_A(50 percent + 1);
            // IF_NC goto not_confused;
            if(v_BattleRandom_Conv() < 50 percent + 1) {
            // clear confusion-dependent substatus
                // LD_HL(wPlayerSubStatus3);
                // LD_A_hl;
                // AND_A(1 << SUBSTATUS_CONFUSED);
                // LD_hl_A;
                wram->wPlayerSubStatus3 &= (1 << SUBSTATUS_CONFUSED);

                // CALL(aHitConfusion);
                HitConfusion();
                // CALL(aCantMove);
                CantMove();
                // JP(mEndTurn);
                return EndTurn();
            }
        }
    }

// not_confused:

    // LD_A_addr(wPlayerSubStatus1);
    // ADD_A_A;  // bit SUBSTATUS_ATTRACT
    // IF_NC goto not_infatuated;

    if(bit_test(wram->wPlayerSubStatus1, SUBSTATUS_IN_LOVE)) {
        // LD_HL(mInLoveWithText);
        // CALL(aStdBattleTextbox);
        StdBattleTextbox(InLoveWithText);
        // XOR_A_A;
        // LD_addr_A(wNumHits);
        wram->wNumHits = 0;
        // LD_DE(ANIM_IN_LOVE);
        // CALL(aFarPlayBattleAnimation);
        FarPlayBattleAnimation(ANIM_IN_LOVE);

    // 50% chance of infatuation
        // CALL(aBattleRandom);
        // CP_A(50 percent + 1);
        // IF_C goto not_infatuated;

        if(v_BattleRandom_Conv() >= 50 percent + 1) {
            // LD_HL(mInfatuationText);
            // CALL(aStdBattleTextbox);
            StdBattleTextbox(InfatuationText);
            // CALL(aCantMove);
            CantMove();
            // JP(mEndTurn);
            return EndTurn();
        }
    }

// not_infatuated:

// We can't disable a move that doesn't exist.
    // LD_A_addr(wDisabledMove);
    // AND_A_A;
    // IF_Z goto no_disabled_move;

// Are we using the disabled move?
    // LD_HL(wCurPlayerMove);
    // CP_A_hl;
    // IF_NZ goto no_disabled_move;
    if(wram->wDisabledMove != NO_MOVE && wram->wCurPlayerMove == wram->wDisabledMove) {
        // CALL(aMoveDisabled);
        MoveDisabled();
        // CALL(aCantMove);
        CantMove();
        // JP(mEndTurn);
        return EndTurn();
    }

// no_disabled_move:

    // LD_HL(wBattleMonStatus);
    // BIT_hl(PAR);
    // RET_Z ;

    if(bit_test(wram->wBattleMon.status[0], PAR)) {
    // 25% chance to be fully paralyzed
        // CALL(aBattleRandom);
        // CP_A(25 percent);
        // RET_NC ;

        if(v_BattleRandom_Conv() < 25 percent) {
            // LD_HL(mFullyParalyzedText);
            // CALL(aStdBattleTextbox);
            StdBattleTextbox(FullyParalyzedText);
            // CALL(aCantMove);
            CantMove();
            // JP(mEndTurn);
            return EndTurn();
        }
    }
}

void CantMove(void){
    // LD_A(BATTLE_VARS_SUBSTATUS1);
    // CALL(aGetBattleVarAddr);
    // RES_hl(SUBSTATUS_ROLLOUT);
    bit_reset(*GetBattleVarAddr(BATTLE_VARS_SUBSTATUS1), SUBSTATUS_ROLLOUT);

    // LD_A(BATTLE_VARS_SUBSTATUS3);
    // CALL(aGetBattleVarAddr);
    uint8_t* hl = GetBattleVarAddr(BATTLE_VARS_SUBSTATUS3);
    // LD_A_hl;
    // AND_A(~(1 << SUBSTATUS_BIDE | 1 << SUBSTATUS_RAMPAGE | 1 << SUBSTATUS_CHARGED));
    // LD_hl_A;
    *hl &= ~(1 << SUBSTATUS_BIDE | 1 << SUBSTATUS_RAMPAGE | 1 << SUBSTATUS_CHARGED);

    // CALL(aResetFuryCutterCount);
    ResetFuryCutterCount();

    // LD_A(BATTLE_VARS_MOVE_ANIM);
    // CALL(aGetBattleVar);
    uint8_t anim = GetBattleVar(BATTLE_VARS_MOVE_ANIM);
    // CP_A(FLY);
    // IF_Z goto fly_dig;
    // CP_A(DIG);
    // RET_NZ ;
    if(anim == FLY || anim == DIG) {
    // fly_dig:
        // RES_hl(SUBSTATUS_UNDERGROUND);
        bit_reset(*hl, SUBSTATUS_UNDERGROUND);
        // RES_hl(SUBSTATUS_FLYING);
        bit_reset(*hl, SUBSTATUS_FLYING);
        // JP(mAppearUserRaiseSub);
        // CALL(aAppearUserRaiseSub);
        AppearUserRaiseSub();
        return;
    }
}

void OpponentCantMove(void){
    // CALL(aBattleCommand_SwitchTurn);
    BattleCommand_SwitchTurn();
    // CALL(aCantMove);
    CantMove();
    // JP(mBattleCommand_SwitchTurn);
    return BattleCommand_SwitchTurn();

}

void CheckEnemyTurn(void){
    // LD_HL(wEnemySubStatus4);
    // BIT_hl(SUBSTATUS_RECHARGE);
    // IF_Z goto no_recharge;

    if(bit_test(wram->wEnemySubStatus4, SUBSTATUS_RECHARGE)) {
        // RES_hl(SUBSTATUS_RECHARGE);
        bit_reset(wram->wEnemySubStatus4, SUBSTATUS_RECHARGE);
        // LD_HL(mMustRechargeText);
        // CALL(aStdBattleTextbox);
        StdBattleTextbox(MustRechargeText);
        // CALL(aCantMove);
        CantMove();
        // JP(mEndTurn);
        return EndTurn();
    }

// no_recharge:

    // LD_HL(wEnemyMonStatus);
    // LD_A_hl;
    // AND_A(SLP);
    // IF_Z goto not_asleep;
    if(wram->wEnemyMon.status[0] & SLP) {
        // DEC_A;
        // LD_addr_A(wEnemyMonStatus);
        // AND_A_A;
        // IF_Z goto woke_up;
        if(--wram->wEnemyMon.status[0] == 0) {
        // woke_up:
            // LD_HL(mWokeUpText);
            // CALL(aStdBattleTextbox);
            StdBattleTextbox(WokeUpText);
            // CALL(aCantMove);
            CantMove();
            // CALL(aUpdateEnemyMonInParty);
            UpdateEnemyMonInParty();
            // LD_HL(mUpdateEnemyHUD);
            UpdateEnemyHUD();
            // CALL(aCallBattleCore);
            // LD_A(0x1);
            // LDH_addr_A(hBGMapMode);
            hram->hBGMapMode = BGMAPMODE_UPDATE_TILES;
            // LD_HL(wEnemySubStatus1);
            // RES_hl(SUBSTATUS_NIGHTMARE);
            bit_reset(wram->wEnemySubStatus1, SUBSTATUS_NIGHTMARE);
            // goto not_asleep;
        }
        else {
            // LD_HL(mFastAsleepText);
            // CALL(aStdBattleTextbox);
            StdBattleTextbox(FastAsleepText);
            // XOR_A_A;
            // LD_addr_A(wNumHits);
            wram->wNumHits = 0;
            // LD_DE(ANIM_SLP);
            // CALL(aFarPlayBattleAnimation);
            FarPlayBattleAnimation(ANIM_SLP);
            // goto fast_asleep;

        // fast_asleep:
        // Snore and Sleep Talk bypass sleep.
            // LD_A_addr(wCurEnemyMove);
            // CP_A(SNORE);
            // IF_Z goto not_asleep;
            // CP_A(SLEEP_TALK);
            // IF_Z goto not_asleep;
            if(wram->wCurEnemyMove != SNORE && wram->wCurEnemyMove != SLEEP_TALK) {
                // CALL(aCantMove);
                CantMove();
                // JP(mEndTurn);
                return EndTurn();
            }
        }
    }

// not_asleep:
    // LD_HL(wEnemyMonStatus);
    // BIT_hl(FRZ);
    // IF_Z goto not_frozen;
    if(bit_test(wram->wEnemyMon.status[0], FRZ)) {
    // Flame Wheel and Sacred Fire thaw the user.
        // LD_A_addr(wCurEnemyMove);
        // CP_A(FLAME_WHEEL);
        // IF_Z goto not_frozen;
        // CP_A(SACRED_FIRE);
        // IF_Z goto not_frozen;

        if(wram->wCurEnemyMove != FLAME_WHEEL && wram->wCurEnemyMove != SACRED_FIRE) {
            // LD_HL(mFrozenSolidText);
            // CALL(aStdBattleTextbox);
            StdBattleTextbox(FrozenSolidText);
            // CALL(aCantMove);
            CantMove();
            // JP(mEndTurn);
            return EndTurn();
        }
    }

// not_frozen:

    // LD_HL(wEnemySubStatus3);
    // BIT_hl(SUBSTATUS_FLINCHED);
    // IF_Z goto not_flinched;

    if(bit_test(wram->wEnemySubStatus3, SUBSTATUS_FLINCHED)) {
        // RES_hl(SUBSTATUS_FLINCHED);
        bit_reset(wram->wEnemySubStatus3, SUBSTATUS_FLINCHED);
        // LD_HL(mFlinchedText);
        // CALL(aStdBattleTextbox);
        StdBattleTextbox(FlinchedText);

        // CALL(aCantMove);
        CantMove();
        // JP(mEndTurn);
        return EndTurn();
    }

// not_flinched:

    // LD_HL(wEnemyDisableCount);
    // LD_A_hl;
    // AND_A_A;
    // IF_Z goto not_disabled;
    if(wram->wEnemyDisableCount != 0) {

        // DEC_A;
        // LD_hl_A;
        // AND_A(0xf);
        // IF_NZ goto not_disabled;
        if((--wram->wEnemyDisableCount & 0xf) == 0) {

            // LD_hl_A;
            wram->wEnemyDisableCount = 0;
            // LD_addr_A(wEnemyDisabledMove);
            wram->wEnemyDisabledMove = NO_MOVE;

            // LD_HL(mDisabledNoMoreText);
            // CALL(aStdBattleTextbox);
            StdBattleTextbox(DisabledNoMoreText);
        }
    }

// not_disabled:

    // LD_A_addr(wEnemySubStatus3);
    // ADD_A_A;  // bit SUBSTATUS_CONFUSED
    // IF_NC goto not_confused;

    if(bit_test(wram->wEnemySubStatus3, SUBSTATUS_CONFUSED)) {
        // LD_HL(wEnemyConfuseCount);
        // DEC_hl;
        // IF_NZ goto confused;
        if(--wram->wEnemyConfuseCount != 0) {
        // confused:
            // LD_HL(mIsConfusedText);
            // CALL(aStdBattleTextbox);
            StdBattleTextbox(IsConfusedText);

            // XOR_A_A;
            // LD_addr_A(wNumHits);
            wram->wNumHits = 0;
            // LD_DE(ANIM_CONFUSED);
            // CALL(aFarPlayBattleAnimation);
            FarPlayBattleAnimation(ANIM_CONFUSED);

        // 50% chance of hitting itself
            // CALL(aBattleRandom);
            // CP_A(50 percent + 1);
            // IF_NC goto not_confused;

            if(v_BattleRandom_Conv() < 50 percent + 1) {
            // clear confusion-dependent substatus
                // LD_HL(wEnemySubStatus3);
                // LD_A_hl;
                // AND_A(1 << SUBSTATUS_CONFUSED);
                // LD_hl_A;
                wram->wEnemySubStatus3 &= (1 << SUBSTATUS_CONFUSED);

                // LD_HL(mHurtItselfText);
                // CALL(aStdBattleTextbox);
                StdBattleTextbox(HurtItselfText);

                // CALL(aHitSelfInConfusion);
                HitSelfInConfusion(&gBattleCmdState);
                // CALL(aBattleCommand_DamageCalc);
                BattleCommand_DamageCalc();
                // CALL(aBattleCommand_LowerSub);
                BattleCommand_LowerSub();

                // XOR_A_A;
                // LD_addr_A(wNumHits);
                wram->wNumHits = 0;

            // Flicker the monster pic unless flying or underground.
                // LD_DE(ANIM_HIT_CONFUSION);
                // LD_A(BATTLE_VARS_SUBSTATUS3_OPP);
                // CALL(aGetBattleVar);
                // AND_A(1 << SUBSTATUS_FLYING | 1 << SUBSTATUS_UNDERGROUND);
                // CALL_Z (aPlayFXAnimID);
                if((GetBattleVar(BATTLE_VARS_SUBSTATUS3_OPP) & (1 << SUBSTATUS_FLYING | 1 << SUBSTATUS_UNDERGROUND)) == 0)
                    PlayFXAnimID(ANIM_HIT_CONFUSION);

                // LD_C(TRUE);
                // CALL(aDoEnemyDamage);
                DoEnemyDamage(true);
                // CALL(aBattleCommand_RaiseSub);
                BattleCommand_RaiseSub();
                // CALL(aCantMove);
                CantMove();
                // JP(mEndTurn);
                return EndTurn();
            }
        }
        else {
            // LD_HL(wEnemySubStatus3);
            // RES_hl(SUBSTATUS_CONFUSED);
            bit_reset(wram->wEnemySubStatus3, SUBSTATUS_CONFUSED);
            // LD_HL(mConfusedNoMoreText);
            // CALL(aStdBattleTextbox);
            StdBattleTextbox(ConfusedNoMoreText);
            // goto not_confused;
        }
    }


// not_confused:

    // LD_A_addr(wEnemySubStatus1);
    // ADD_A_A;  // bit SUBSTATUS_ATTRACT
    // IF_NC goto not_infatuated;

    if(bit_test(wram->wEnemySubStatus1, SUBSTATUS_IN_LOVE)) {
        // LD_HL(mInLoveWithText);
        // CALL(aStdBattleTextbox);
        StdBattleTextbox(InLoveWithText);
        // XOR_A_A;
        // LD_addr_A(wNumHits);
        wram->wNumHits = 0;
        // LD_DE(ANIM_IN_LOVE);
        // CALL(aFarPlayBattleAnimation);
        FarPlayBattleAnimation(ANIM_IN_LOVE);

    // 50% chance of infatuation
        // CALL(aBattleRandom);
        // CP_A(50 percent + 1);
        // IF_C goto not_infatuated;

        if(v_BattleRandom_Conv() >= 50 percent + 1) {
            // LD_HL(mInfatuationText);
            // CALL(aStdBattleTextbox);
            StdBattleTextbox(InfatuationText);
            // CALL(aCantMove);
            CantMove();
            // JP(mEndTurn);
            return EndTurn();
        }
    }

// not_infatuated:

// We can't disable a move that doesn't exist.
    // LD_A_addr(wEnemyDisabledMove);
    // AND_A_A;
    // IF_Z goto no_disabled_move;

    if(wram->wEnemyDisabledMove != NO_MOVE) {
    // Are we using the disabled move?
        // LD_HL(wCurEnemyMove);
        // CP_A_hl;
        // IF_NZ goto no_disabled_move;

        if(wram->wCurEnemyMove == wram->wEnemyDisabledMove) {
            // CALL(aMoveDisabled);
            MoveDisabled();

            // CALL(aCantMove);
            CantMove();
            // JP(mEndTurn);
            return EndTurn();
        }
    }

// no_disabled_move:

    // LD_HL(wEnemyMonStatus);
    // BIT_hl(PAR);
    // RET_Z ;

    if(bit_test(wram->wEnemyMon.status[0], PAR)) {
    // 25% chance to be fully paralyzed
        // CALL(aBattleRandom);
        // CP_A(25 percent);
        // RET_NC ;

        if(v_BattleRandom_Conv() < 25 percent) {
            // LD_HL(mFullyParalyzedText);
            // CALL(aStdBattleTextbox);
            StdBattleTextbox(FullyParalyzedText);
            // CALL(aCantMove);
            CantMove();

        // fallthrough

            return EndTurn();
        }
    }
}

void EndTurn(void){
    // LD_A(0x1);
    // LD_addr_A(wTurnEnded);
    wram->wTurnEnded = 0x1;
    // JP(mResetDamage);
    return ResetDamage();
}

void MoveDisabled(void){
// Make sure any charged moves fail
    // LD_A(BATTLE_VARS_SUBSTATUS3);
    // CALL(aGetBattleVarAddr);
    // RES_hl(SUBSTATUS_CHARGED);
    bit_reset(*GetBattleVarAddr(BATTLE_VARS_SUBSTATUS3), SUBSTATUS_CHARGED);

    // LD_A(BATTLE_VARS_MOVE);
    // CALL(aGetBattleVar);
    // LD_addr_A(wNamedObjectIndex);
    // CALL(aGetMoveName);
    GetMoveName(GetBattleVar(BATTLE_VARS_MOVE));

    // LD_HL(mDisabledMoveText);
    // JP(mStdBattleTextbox);
    return StdBattleTextbox(DisabledMoveText);
}

void HitConfusion(void){
    // LD_HL(mHurtItselfText);
    // CALL(aStdBattleTextbox);
    StdBattleTextbox(HurtItselfText);

    // XOR_A_A;
    // LD_addr_A(wCriticalHit);
    wram->wCriticalHit = FALSE;

    // CALL(aHitSelfInConfusion);
    HitSelfInConfusion(&gBattleCmdState);
    // CALL(aBattleCommand_DamageCalc);
    BattleCommand_DamageCalc();
    // CALL(aBattleCommand_LowerSub);
    BattleCommand_LowerSub();

    // XOR_A_A;
    // LD_addr_A(wNumHits);
    wram->wNumHits = 0;

// Flicker the monster pic unless flying or underground.
    // LD_DE(ANIM_HIT_CONFUSION);
    // LD_A(BATTLE_VARS_SUBSTATUS3_OPP);
    // CALL(aGetBattleVar);
    // AND_A(1 << SUBSTATUS_FLYING | 1 << SUBSTATUS_UNDERGROUND);
    // CALL_Z (aPlayFXAnimID);
    if((GetBattleVar(BATTLE_VARS_SUBSTATUS3_OPP) & (1 << SUBSTATUS_FLYING | 1 << SUBSTATUS_UNDERGROUND)) == 0)
        PlayFXAnimID(ANIM_HIT_CONFUSION);

    // LD_HL(mUpdatePlayerHUD);
    // CALL(aCallBattleCore);
    UpdatePlayerHUD();
    // LD_A(0x1);
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = BGMAPMODE_UPDATE_TILES;
    // LD_C(TRUE);
    // CALL(aDoPlayerDamage);
    DoPlayerDamage(true);
    // JP(mBattleCommand_RaiseSub);
    return BattleCommand_RaiseSub();
}

void BattleCommand_CheckObedience(void){
//  checkobedience

// Enemy can't disobey
    PEEK("");
    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // RET_NZ ;
    if(hram->hBattleTurn != TURN_PLAYER)
        return;

    // CALL(aCheckUserIsCharging);
    // RET_NZ ;
    if(CheckUserIsCharging())
        return;

// If we've already checked this turn
    // LD_A_addr(wAlreadyDisobeyed);
    // AND_A_A;
    // RET_NZ ;
    if(wram->wAlreadyDisobeyed)
        return;

    // XOR_A_A;
    // LD_addr_A(wAlreadyDisobeyed);
    wram->wAlreadyDisobeyed = FALSE;

// No obedience in link battles
// (since no handling exists for enemy)
    // LD_A_addr(wLinkMode);
    // AND_A_A;
    // RET_NZ ;
    if(wram->wLinkMode != LINK_NULL)
        return;

    // LD_A_addr(wInBattleTowerBattle);
    // AND_A_A;
    // RET_NZ ;
    if(wram->wInBattleTowerBattle != 0)
        return;

// If the monster's id doesn't match the player's,
// some conditions need to be met.
    // LD_A(MON_ID);
    // CALL(aBattlePartyAttr);
    struct PartyMon* mon = wram->wPartyMon + wram->wCurPartyMon;

    // LD_A_addr(wPlayerID);
    // CP_A_hl;
    // IF_NZ goto obeylevel;
    // INC_HL;
    // LD_A_addr(wPlayerID + 1);
    // CP_A_hl;
    // RET_Z ;
    if(mon->mon.id == wram->wPlayerID)
        return;

// obeylevel:
// The maximum obedience level is constrained by owned badges:
    // LD_HL(wJohtoBadges);
    uint8_t* hl = wram->wJohtoBadges;
    uint8_t lvl;

// risingbadge
    // BIT_hl(RISINGBADGE);
    // LD_A(MAX_LEVEL + 1);
    // IF_NZ goto getlevel;
    if(bit_test(*hl, RISINGBADGE))
        lvl = MAX_LEVEL + 1;

// stormbadge
    // BIT_hl(STORMBADGE);
    // LD_A(70);
    // IF_NZ goto getlevel;
    else if(bit_test(*hl, STORMBADGE))
        lvl = 70;

// fogbadge
    // BIT_hl(FOGBADGE);
    // LD_A(50);
    // IF_NZ goto getlevel;
    else if(bit_test(*hl, FOGBADGE))
        lvl = 50;

// hivebadge
    // BIT_hl(HIVEBADGE);
    // LD_A(30);
    // IF_NZ goto getlevel;
    else if(bit_test(*hl, HIVEBADGE))
        lvl = 30;

// no badges
    // LD_A(10);
    else
        lvl = 10;


// getlevel:
//  c = obedience level
//  d = monster level
//  b = c + d

    // LD_B_A;
    // LD_C_A;
    uint8_t c = lvl;

    // LD_A_addr(wBattleMonLevel);
    // LD_D_A;
    uint8_t d = wram->wBattleMon.level;

    // ADD_A_B;
    // LD_B_A;
    uint8_t b = c + d;

//  No overflow (this should never happen)
    // IF_NC goto checklevel;
    // LD_B(0xff);

// checklevel:
//  If the monster's level is lower than the obedience level, it will obey.
    // LD_A_C;
    // CP_A_D;
    // RET_NC ;
    if(c >= d)
        return;

//  Random number from 0 to obedience level + monster level

    uint8_t a = 0;
    do {
    // rand1:
        // CALL(aBattleRandom);
        a = v_BattleRandom_Conv();
        // SWAP_A;
        a = (a >> 4) | (a << 4);
        // CP_A_B;
        // IF_NC goto rand1;
    } while(a >= b);

//  The higher above the obedience level the monster is,
//  the more likely it is to disobey.
    // CP_A_C;
    // RET_C ;
    if(a < c)
        return;

//  Sleep-only moves have separate handling, and a higher chance of
//  being ignored. Lazy monsters like their sleep.
    // CALL(aIgnoreSleepOnly);
    // RET_C ;
    if(IgnoreSleepOnly())
        return;

//  Another random number from 0 to obedience level + monster level

    do {
    // rand2:
        // CALL(aBattleRandom);
        a = v_BattleRandom_Conv();
        // CP_A_B;
        // IF_NC goto rand2;
    } while(a >= b);

//  A second chance.
    // CP_A_C;
    // IF_C goto UseInstead;
    if(a < b) {
    // UseInstead:
    //  Can't use another move if the monster only has one!
        // LD_A_addr(wBattleMonMoves + 1);
        // AND_A_A;
        // IF_Z goto DoNothing;
        if(wram->wBattleMon.moves[1] == NO_MOVE)
            goto DoNothing;

    //  Don't bother trying to handle Disable.
        // LD_A_addr(wDisabledMove);
        // AND_A_A;
        // IF_NZ goto DoNothing;
        if(wram->wDisabledMove != NO_MOVE)
            goto DoNothing;

        // LD_HL(wBattleMonPP);
        uint8_t* pp = wram->wBattleMon.pp;
        // LD_DE(wBattleMonMoves);
        move_t* de = wram->wBattleMon.moves;
        // LD_B(0);
        b = 0;
        // LD_C(NUM_MOVES);
        c = NUM_MOVES;

        do {
        // GetTotalPP:
            // LD_A_hli;
            // AND_A(PP_MASK);
            // ADD_A_B;
            // LD_B_A;
            b += *(pp++) & PP_MASK;

            // DEC_C;
            // IF_Z goto CheckMovePP;
            if(--c == 0)
                break;

        //  Stop at undefined moves.
            // INC_DE;
            // LD_A_de;
            // AND_A_A;
            // IF_NZ goto GetTotalPP;
        } while(*(++de) != NO_MOVE);


    // CheckMovePP:
        // LD_HL(wBattleMonPP);
        // LD_A_addr(wCurMoveNum);
        // LD_E_A;
        // LD_D(0);
        // ADD_HL_DE;
        pp = wram->wBattleMon.pp + wram->wCurMoveNum;

    //  Can't use another move if only one move has PP.
        // LD_A_hl;
        // AND_A(PP_MASK);
        // CP_A_B;
        // IF_Z goto DoNothing;
        if(((*pp) & PP_MASK) == b)
            goto DoNothing;

    //  Make sure we can actually use the move once we get there.
        // LD_A(1);
        // LD_addr_A(wAlreadyDisobeyed);
        wram->wAlreadyDisobeyed = TRUE;

        // LD_A_addr(w2DMenuNumRows);
        // LD_B_A;
        b = wram->w2DMenuNumRows;

    //  Save the move we originally picked for afterward.
        // LD_A_addr(wCurMoveNum);
        // LD_C_A;
        // PUSH_AF;
        uint8_t curMove = wram->wCurMoveNum;
        c = curMove;

        while(1) {
        // RandomMove:
            // CALL(aBattleRandom);
            // maskbits(NUM_MOVES, 0);
            a = v_BattleRandom_Conv() & 3;

            // CP_A_B;
            // IF_NC goto RandomMove;
            if(a < b)
                continue;

        //  Not the move we were trying to use.
            // CP_A_C;
            // IF_Z goto RandomMove;
            if(a == c)
                continue;

        //  Make sure it has PP.
            // LD_addr_A(wCurMoveNum);
            // LD_HL(wBattleMonPP);
            // LD_E_A;
            // LD_D(0);
            // ADD_HL_DE;
            // LD_A_hl;
            // AND_A(PP_MASK);
            // IF_Z goto RandomMove;
            if((wram->wBattleMon.pp[a] & PP_MASK) != 0)
                break;
        }

    //  Use it.
        // LD_A_addr(wCurMoveNum);
        // LD_C_A;
        // LD_B(0);
        // LD_HL(wBattleMonMoves);
        // ADD_HL_BC;
        // LD_A_hl;
        // LD_addr_A(wCurPlayerMove);
        wram->wCurPlayerMove = wram->wBattleMon.moves[a];

        // CALL(aSetPlayerTurn);
        SetPlayerTurn();
        // CALL(aUpdateMoveData);
        UpdateMoveData();
        // CALL(aDoMove);
        DoMove();

    //  Restore original move choice.
        // POP_AF;
        // LD_addr_A(wCurMoveNum);
        wram->wCurMoveNum = curMove;
    }
    else {
    //  No hope of using a move now.

    //  b = number of levels the monster is above the obedience level
        // LD_A_D;
        // SUB_A_C;
        // LD_B_A;
        b = d - c;

    //  The chance of napping is the difference out of 256.
        // CALL(aBattleRandom);
        a = v_BattleRandom_Conv();
        // SWAP_A;
        a = (a << 4) | (a >> 4);
        // SUB_A_B;
        uint8_t carry = a < b;
        a -= b;
        // IF_C goto Nap;

        if(!carry) {
        //  The chance of not hitting itself is the same.
            // CP_A_B;
            // IF_NC goto DoNothing;
            if(a >= b) {
            DoNothing:
            // 4 random choices
                // CALL(aBattleRandom);
                // AND_A(0b11);
                a = v_BattleRandom_Conv() & 0b11;

                switch(a) {
                // LD_HL(mLoafingAroundText);
                // AND_A_A;  // 0
                // IF_Z goto Print;
                    case 0:
                        StdBattleTextbox(LoafingAroundText);
                        break;

                // LD_HL(mWontObeyText);
                // DEC_A;  // 1
                // IF_Z goto Print;
                    case 1:
                        StdBattleTextbox(WontObeyText);
                        break;

                // LD_HL(mTurnedAwayText);
                // DEC_A;  // 2
                // IF_Z goto Print;
                    case 2:
                        StdBattleTextbox(TurnedAwayText);
                        break;

                // LD_HL(mIgnoredOrdersText);
                    default:
                    case 3:
                        StdBattleTextbox(IgnoredOrdersText);
                        break;
                }

            // Print:
                // CALL(aStdBattleTextbox);
                // JP(mBattleCommand_CheckObedience_EndDisobedience);
            }
            else {
                // LD_HL(mWontObeyText);
                // CALL(aStdBattleTextbox);
                StdBattleTextbox(WontObeyText);
                // CALL(aHitConfusion);
                HitConfusion();
                // JP(mBattleCommand_CheckObedience_EndDisobedience);
            }
        }
        else {
            do {
            // Nap:
                // CALL(aBattleRandom);
                a = v_BattleRandom_Conv() << 1;
                // ADD_A_A;
                // SWAP_A;
                a = (a >> 4) | (a << 4);
                // AND_A(SLP);
                // IF_Z goto Nap;
            } while((a & SLP) == 0);

            // LD_addr_A(wBattleMonStatus);
            wram->wBattleMon.status[0] = a;

            // LD_HL(mBeganToNapText);
            StdBattleTextbox(BeganToNapText);
            // goto Print;
        }
    }

// EndDisobedience:
    // XOR_A_A;
    // LD_addr_A(wLastPlayerMove);
    wram->wLastPlayerMove = NO_MOVE;
    // LD_addr_A(wLastPlayerCounterMove);
    wram->wLastPlayerCounterMove = NO_MOVE;

// Break Encore too.
    // LD_HL(wPlayerSubStatus5);
    // RES_hl(SUBSTATUS_ENCORED);
    bit_reset(wram->wPlayerSubStatus5, SUBSTATUS_ENCORED);
    // XOR_A_A;
    // LD_addr_A(wPlayerEncoreCount);
    wram->wPlayerEncoreCount = 0;

    // JP(mEndMoveEffect);
    return EndMoveEffect();
}

bool IgnoreSleepOnly(void){
    // LD_A(BATTLE_VARS_MOVE_ANIM);
    // CALL(aGetBattleVar);
    uint8_t anim = GetBattleVar(BATTLE_VARS_MOVE_ANIM);
// Snore and Sleep Talk bypass sleep.
    // CP_A(SNORE);
    // IF_Z goto CheckSleep;
    // CP_A(SLEEP_TALK);
    // IF_Z goto CheckSleep;
    // AND_A_A;
    // RET;
    if(anim != SNORE && anim != SLEEP_TALK)
        return false;

// CheckSleep:
    // LD_A(BATTLE_VARS_STATUS);
    // CALL(aGetBattleVar);
    // AND_A(SLP);
    // RET_Z ;
    if((GetBattleVar(BATTLE_VARS_STATUS) & SLP) == 0)
        return false;

//  'ignored orders…sleeping!'
    // LD_HL(mIgnoredSleepingText);
    // CALL(aStdBattleTextbox);
    StdBattleTextbox(IgnoredSleepingText);

    // CALL(aEndMoveEffect);
    EndMoveEffect();

    // SCF;
    // RET;
    return true;
}

void BattleCommand_UsedMoveText(void){
//  usedmovetext
    PEEK("");
    // FARCALL(aDisplayUsedMoveText);
    DisplayUsedMoveText();
    // RET;
}

//  Return nz (true) if the user is charging.
bool CheckUserIsCharging(void){
    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // LD_A_addr(wPlayerCharging);  // player
    // IF_Z goto end;
    if(hram->hBattleTurn == TURN_PLAYER) {
        return wram->wPlayerCharging != 0;
    }
    // LD_A_addr(wEnemyCharging);  // enemy
    else {
        return wram->wEnemyCharging != 0;
    }
// end:
    // AND_A_A;
    // RET;
}

static uint8_t BattleCommand_DoTurn_consume_pp(uint8_t* hl) {
    static const uint8_t continuousmoves[] = {
        EFFECT_RAZOR_WIND,
        EFFECT_SKY_ATTACK,
        EFFECT_SKULL_BASH,
        EFFECT_SOLARBEAM,
        EFFECT_FLY,
        EFFECT_ROLLOUT,
        EFFECT_BIDE,
        EFFECT_RAMPAGE,
        (uint8_t)-1,
    };
    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // LD_A_addr(wCurMoveNum);
    // IF_Z goto okay;
    // LD_A_addr(wCurEnemyMoveNum);
    uint8_t move = (hram->hBattleTurn == TURN_PLAYER)? wram->wCurMoveNum: wram->wCurEnemyMoveNum;

// okay:
    // LD_C_A;
    // LD_B(0);
    // ADD_HL_BC;
    // LD_A_hl;
    // AND_A(PP_MASK);
    // IF_Z goto out_of_pp;
    if((hl[move] & PP_MASK) == 0) {
    out_of_pp:
        // CALL(aBattleCommand_MoveDelay);
        BattleCommand_MoveDelay();
    //  get move effect
        // LD_A(BATTLE_VARS_MOVE_EFFECT);
        // CALL(aGetBattleVar);
        uint8_t effect = GetBattleVar(BATTLE_VARS_MOVE_EFFECT);
    //  continuous?
        // LD_HL(mBattleCommand_DoTurn_continuousmoves);
        // LD_DE(1);
        // CALL(aIsInArray);
        if(IsInU8Array(continuousmoves, effect)) {

        //  'has no pp left for [move]'
            // LD_HL(mHasNoPPLeftText);
            // IF_C goto print;
            StdBattleTextbox(HasNoPPLeftText);
        }
        else {
        //  'but no pp is left for the move'
            // LD_HL(mNoPPLeftText);
            StdBattleTextbox(NoPPLeftText);
        }

    // print:
        // CALL(aStdBattleTextbox);
        // LD_B(1);
        return 1;
        // RET;
    }
    // DEC_hl;
    hl[move]--;
    // LD_B(0);
    return 0;
    // RET;
}

void BattleCommand_DoTurn(void){
    PEEK("");
    // CALL(aCheckUserIsCharging);
    // RET_NZ ;
    if(CheckUserIsCharging())
        return;

    uint8_t *bc, *de, *hl;
    if(hram->hBattleTurn == TURN_PLAYER) {
        // LD_HL(wBattleMonPP);
        hl = wram->wBattleMon.pp;
        // LD_DE(wPlayerSubStatus3);
        de = &wram->wPlayerSubStatus3;
        // LD_BC(wPlayerTurnsTaken);
        bc = &wram->wPlayerTurnsTaken;

        // LDH_A_addr(hBattleTurn);
        // AND_A_A;
        // IF_Z goto proceed;
    }
    else {
        // LD_HL(wEnemyMonPP);
        hl = wram->wEnemyMon.pp;
        // LD_DE(wEnemySubStatus3);
        de = &wram->wEnemySubStatus3;
        // LD_BC(wEnemyTurnsTaken);
        bc = &wram->wEnemyTurnsTaken;
    }

// proceed:

//  If we've gotten this far, this counts as a turn.
    // LD_A_bc;
    // INC_A;
    // LD_bc_A;
    (*bc)++;

    // LD_A(BATTLE_VARS_MOVE);
    // CALL(aGetBattleVar);
    // CP_A(STRUGGLE);
    // RET_Z ;
    if(GetBattleVar(BATTLE_VARS_MOVE) == STRUGGLE)
        return;

    // LD_A_de;
    // AND_A(1 << SUBSTATUS_IN_LOOP | 1 << SUBSTATUS_RAMPAGE | 1 << SUBSTATUS_BIDE);
    // RET_NZ ;
    if(*de & ((1 << SUBSTATUS_IN_LOOP) | (1 << SUBSTATUS_RAMPAGE) | (1 << SUBSTATUS_BIDE)))
        return;

    // CALL(aBattleCommand_DoTurn_consume_pp);
    // LD_A_B;
    // AND_A_A;
    // JP_NZ (mEndMoveEffect);
    if(BattleCommand_DoTurn_consume_pp(hl) != 0)
        return EndMoveEffect();

// SubStatus5
    // INC_DE;
    // INC_DE;
    de += 2;

    // LD_A_de;
    // BIT_A(SUBSTATUS_TRANSFORMED);
    // RET_NZ ;
    if(bit_test(*de, SUBSTATUS_TRANSFORMED))
        return;

    // LDH_A_addr(hBattleTurn);
    // AND_A_A;

    if(hram->hBattleTurn == TURN_PLAYER) {
        // LD_HL(wPartyMon1PP);
        hl = wram->wPartyMon[wram->wCurBattleMon].mon.PP;
        // LD_A_addr(wCurBattleMon);
        // IF_Z goto player;
    }

//  mimic this part entirely if wildbattle
    // LD_A_addr(wBattleMode);
    // DEC_A;
    // IF_Z goto wild;
    else if(wram->wBattleMode == WILD_BATTLE) {
    // wild:
        // LD_HL(wEnemyMonMoves);
        // LD_A_addr(wCurEnemyMoveNum);
        // LD_C_A;
        // LD_B(0);
        // ADD_HL_BC;
        // LD_A_hl;
        // CP_A(MIMIC);
        // IF_Z goto mimic;
        if(wram->wEnemyMon.moves[wram->wCurEnemyMoveNum] == MIMIC) {
            // LD_HL(wWildMonMoves);
            // ADD_HL_BC;
            // LD_A_hl;
            // CP_A(MIMIC);
            // RET_Z ;
            if(wram->wWildMonMoves[wram->wCurEnemyMoveNum] == MIMIC)
                return;
        }

    // mimic:
        // LD_HL(wWildMonPP);
        // CALL(aBattleCommand_DoTurn_consume_pp);
        gBattleCmdState.b = BattleCommand_DoTurn_consume_pp(wram->wWildMonPP);
        // RET;
        return;
    }

    else {
        // LD_HL(wOTPartyMon1PP);
        // LD_A_addr(wCurOTMon);
        hl = wram->wOTPartyMon[wram->wCurOTMon].mon.PP;
    }


// player:
    // CALL(aGetPartyLocation);
    // PUSH_HL;
    // CALL(aCheckMimicUsed);
    // POP_HL;
    // RET_C ;
    if(!CheckMimicUsed())
        return;
    gBattleCmdState.b = BattleCommand_DoTurn_consume_pp(hl);
    return;

// consume_pp:
    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // LD_A_addr(wCurMoveNum);
    // IF_Z goto okay;
    // LD_A_addr(wCurEnemyMoveNum);


// okay:
    // LD_C_A;
    // LD_B(0);
    // ADD_HL_BC;
    // LD_A_hl;
    // AND_A(PP_MASK);
    // IF_Z goto out_of_pp;
    // DEC_hl;
    // LD_B(0);
    // RET;
}

// Returns true or nc if Mimic was used.
// False or c otherwise.
bool CheckMimicUsed(void){
    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // LD_A_addr(wCurMoveNum);
    // IF_Z goto player;
    // LD_A_addr(wCurEnemyMoveNum);
    uint8_t move = (hram->hBattleTurn == TURN_PLAYER)? wram->wCurMoveNum: wram->wCurEnemyMoveNum;

// player:
    // LD_C_A;
    // LD_A(MON_MOVES);
    // CALL(aUserPartyAttr);
    struct PartyMon* mon = UserPartyMon();

    // LD_A(BATTLE_VARS_MOVE);
    // CALL(aGetBattleVar);
    // CP_A(MIMIC);
    // IF_Z goto mimic;

    // LD_B(0);
    // ADD_HL_BC;
    // LD_A_hl;
    // CP_A(MIMIC);
    // IF_NZ goto mimic;
    if(GetBattleVar(BATTLE_VARS_MOVE) == MIMIC || mon->mon.moves[move] != MIMIC) {
    // mimic:
        // AND_A_A;
        // RET;
        return true;
    }

    // SCF;
    // RET;
    return false;
}

void BattleCommand_Critical(void){
//  critical

//  Determine whether this attack's hit will be critical.

    PEEK("");
    // XOR_A_A;
    // LD_addr_A(wCriticalHit);
    wram->wCriticalHit = FALSE;

    // LD_A(BATTLE_VARS_MOVE_POWER);
    // CALL(aGetBattleVar);
    // AND_A_A;
    // RET_Z ;
    if(GetBattleVar(BATTLE_VARS_MOVE_POWER) == 0)
        return;

    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // LD_HL(wEnemyMonItem);
    // LD_A_addr(wEnemyMonSpecies);
    // IF_NZ goto Item;
    // LD_HL(wBattleMonItem);
    // LD_A_addr(wBattleMonSpecies);
    item_t item = (hram->hBattleTurn != TURN_PLAYER)? wram->wEnemyMon.item: wram->wBattleMon.item;
    species_t species = (hram->hBattleTurn != TURN_PLAYER)? wram->wEnemyMon.species: wram->wBattleMon.species;

    uint8_t c = 0;
// Item:
    // LD_C(0);

    // CP_A(CHANSEY);
    // IF_NZ goto Farfetchd;
    // LD_A_hl;
    // CP_A(LUCKY_PUNCH);
    // IF_NZ goto FocusEnergy;

    if(species == CHANSEY && item == LUCKY_PUNCH) {
    //  +2 critical level
        // LD_C(2);
        c = 2;
        // goto Tally;
    }

// Farfetchd:
    // CP_A(FARFETCH_D);
    // IF_NZ goto FocusEnergy;
    // LD_A_hl;
    // CP_A(STICK);
    // IF_NZ goto FocusEnergy;
    else if(species == FARFETCH_D && item == STICK) {

    //  +2 critical level
        // LD_C(2);
        c = 2;
        // goto Tally;
    }

// FocusEnergy:
    else {
        // LD_A(BATTLE_VARS_SUBSTATUS4);
        // CALL(aGetBattleVar);
        // BIT_A(SUBSTATUS_FOCUS_ENERGY);
        // IF_Z goto CheckCritical;
        if(bit_test(GetBattleVar(BATTLE_VARS_SUBSTATUS4), SUBSTATUS_FOCUS_ENERGY)) {
        //  +1 critical level
            // INC_C;
            ++c;
        }

    // CheckCritical:
        // LD_A(BATTLE_VARS_MOVE_ANIM);
        // CALL(aGetBattleVar);
        // LD_DE(1);
        // LD_HL(mCriticalHitMoves);
        // PUSH_BC;
        // CALL(aIsInArray);
        // POP_BC;
        // IF_NC goto ScopeLens;

        if(IsInMoveArray(CriticalHitMoves, GetBattleVar(BATTLE_VARS_MOVE_ANIM))) {
        //  +2 critical level
            // INC_C;
            // INC_C;
            c += 2;
        }


    // ScopeLens:
        // PUSH_BC;
        // CALL(aGetUserItem);
        // LD_A_B;
        // CP_A(HELD_CRITICAL_UP);  // Increased critical chance. Only Scope Lens has this.
        // POP_BC;
        // IF_NZ goto Tally;
        if(HIGH(GetUserItem(NULL)) == HELD_CRITICAL_UP) {

        //  +1 critical level
            // INC_C;
            c++;
        }
    }


// Tally:
    // LD_HL(mCriticalHitChances);
    // LD_B(0);
    // ADD_HL_BC;
    uint8_t chance = CriticalHitChances[c];
    // CALL(aBattleRandom);
    // CP_A_hl;
    // RET_NC ;
    if(v_BattleRandom_Conv() < chance) {
        // LD_A(1);
        // LD_addr_A(wCriticalHit);
        wram->wCriticalHit = TRUE;
    }
    // RET;

// INCLUDE "data/moves/critical_hit_moves.asm"

// INCLUDE "data/battle/critical_hit_chances.asm"

// INCLUDE "engine/battle/move_effects/triple_kick.asm"

}

void BattleCommand_Stab(void){
//  STAB = Same Type Attack Bonus
    PEEK("");
    // LD_A(BATTLE_VARS_MOVE_ANIM);
    // CALL(aGetBattleVar);
    // CP_A(STRUGGLE);
    // RET_Z ;
    if(GetBattleVar(BATTLE_VARS_MOVE_ANIM) == STRUGGLE)
        return;

    uint8_t b, c, d, e;
    if(hram->hBattleTurn == TURN_PLAYER) {
        // LD_HL(wBattleMonType1);
        // LD_A_hli;
        // LD_B_A;
        b = wram->wBattleMon.types[0];
        // LD_C_hl;
        c = wram->wBattleMon.types[1];
        // LD_HL(wEnemyMonType1);
        // LD_A_hli;
        // LD_D_A;
        d = wram->wEnemyMon.types[0];
        // LD_E_hl;
        e = wram->wEnemyMon.types[1];

        // LDH_A_addr(hBattleTurn);
        // AND_A_A;
        // IF_Z goto go;  // Who Attacks and who Defends
    }
    else {
        // LD_HL(wEnemyMonType1);
        // LD_A_hli;
        // LD_B_A;
        b = wram->wEnemyMon.types[0];
        // LD_C_hl;
        c = wram->wEnemyMon.types[1];
        // LD_HL(wBattleMonType1);
        // LD_A_hli;
        // LD_D_A;
        d = wram->wBattleMon.types[0];
        // LD_E_hl;
        e = wram->wBattleMon.types[1];
    }

// go:
    // LD_A(BATTLE_VARS_MOVE_TYPE);
    // CALL(aGetBattleVarAddr);
    // LD_addr_A(wCurType);
    wram->wCurType = *GetBattleVarAddr(BATTLE_VARS_MOVE_TYPE);

    // PUSH_HL;
    // PUSH_DE;
    // PUSH_BC;
    // FARCALL(aDoWeatherModifiers);
    DoWeatherModifiers();
    // POP_BC;
    // POP_DE;
    // POP_HL;

    // PUSH_DE;
    // PUSH_BC;
    // FARCALL(aDoBadgeTypeBoosts);
    DoBadgeTypeBoosts();
    // POP_BC;
    // POP_DE;

    // LD_A_addr(wCurType);
    // CP_A_B;
    // IF_Z goto stab;
    // CP_A_C;
    // IF_Z goto stab;

    // goto SkipStab;
    if(wram->wCurType == b || wram->wCurType == c) {
    // stab:
        // LD_HL(wCurDamage + 1);
        // LD_A_hld;
        // LD_H_hl;
        // LD_L_A;
        uint16_t dmg = BigEndianToNative16(wram->wCurDamage);

        // LD_B_H;
        // LD_C_L;
        // SRL_B;
        // RR_C;
        // ADD_HL_BC;
        dmg += (dmg >> 1);

        // LD_A_H;
        // LD_addr_A(wCurDamage);
        // LD_A_L;
        // LD_addr_A(wCurDamage + 1);
        wram->wCurDamage = NativeToBigEndian16(dmg);

        // LD_HL(wTypeModifier);
        // SET_hl(7);
        bit_set(wram->wTypeModifier, 7);
    }

// SkipStab:
    // LD_A(BATTLE_VARS_MOVE_TYPE);
    // CALL(aGetBattleVar);
    // LD_B_A;
    b = GetBattleVar(BATTLE_VARS_MOVE_TYPE);
    // LD_HL(mTypeMatchups);
    const uint8_t* matchups = TypeMatchups;

    for(uint32_t i = 0; matchups[i] != 0xff; i += 3) {
    TypesLoop:
        // LD_A_hli;

        // CP_A(-1);
        // IF_Z goto end;

    // foresight
        // CP_A(-2);
        // IF_NZ goto SkipForesightCheck;
        if(matchups[i] != 0xfe) {
        // SkipForesightCheck:
            // CP_A_B;
            // IF_NZ goto SkipType;
            if(matchups[i] != b)
                continue;
            // LD_A_hl;
            // CP_A_D;
            // IF_Z goto GotMatchup;
            // CP_A_E;
            // IF_Z goto GotMatchup;
            // goto SkipType;
            if(matchups[i+1] != d && matchups[i+1] != e)
                continue;

        // GotMatchup:
            // PUSH_HL;
            // PUSH_BC;
            // INC_HL;
            uint8_t n = matchups[i+2];
            // LD_A_addr(wTypeModifier);
            // AND_A(0b10000000);
            // LD_B_A;
            uint8_t b2 = (wram->wTypeModifier & 0b10000000);
        //  If the target is immune to the move, treat it as a miss and calculate the damage as 0
            // LD_A_hl;
            // AND_A_A;
            // IF_NZ goto NotImmune;
            if(n == 0) {
                // INC_A;
                // LD_addr_A(wAttackMissed);
                wram->wAttackMissed = TRUE;
                // XOR_A_A;
            }

        // NotImmune:
            // LDH_addr_A(hMultiplier);
            // ADD_A_B;
            // LD_addr_A(wTypeModifier);
            wram->wTypeModifier = b2 + n;

            // XOR_A_A;
            // LDH_addr_A(hMultiplicand + 0);

            // LD_HL(wCurDamage);
            // LD_A_hli;
            // LDH_addr_A(hMultiplicand + 1);
            // LD_A_hld;
            // LDH_addr_A(hMultiplicand + 2);

            // CALL(aMultiply);
            uint32_t n2 = (n * BigEndianToNative16(wram->wCurDamage));

            // LDH_A_addr(hProduct + 1);
            // LD_B_A;
            // LDH_A_addr(hProduct + 2);
            // OR_A_B;
            // LD_B_A;
            // LDH_A_addr(hProduct + 3);
            // OR_A_B;
            // IF_Z goto ok;  // This is a very convoluted way to get back that we've essentially dealt no damage.
            if((n2 & 0xffffff) != 0) {
            //  Take the product and divide it by 10.
                // LD_A(10);
                // LDH_addr_A(hDivisor);
                // LD_B(4);
                // CALL(aDivide);
                n2 /= 10;
                // LDH_A_addr(hQuotient + 2);
                // LD_B_A;
                // LDH_A_addr(hQuotient + 3);
                // OR_A_B;
                // IF_NZ goto ok;
                if((n2 & 0xffff) == 0) {
                    // LD_A(1);
                    // LDH_addr_A(hMultiplicand + 2);
                    n2 = 1;
                }
            }


        // ok:
            // LDH_A_addr(hMultiplicand + 1);
            // LD_hli_A;
            // LDH_A_addr(hMultiplicand + 2);
            // LD_hl_A;
            wram->wCurDamage = NativeToBigEndian16(n2);
            // POP_BC;
            // POP_HL;
            continue;
        }
        // LD_A(BATTLE_VARS_SUBSTATUS1_OPP);
        // CALL(aGetBattleVar);
        // BIT_A(SUBSTATUS_IDENTIFIED);
        // IF_NZ goto end;
        if(bit_test(GetBattleVar(BATTLE_VARS_SUBSTATUS1_OPP), SUBSTATUS_IDENTIFIED))
            break;

        // goto TypesLoop;
        i += 1;
        goto TypesLoop;


    // SkipType:
        // INC_HL;
        // INC_HL;
        // goto TypesLoop;
    }

// end:
    // CALL(aBattleCheckTypeMatchup);
    // LD_A_addr(wTypeMatchup);
    uint8_t matchup = BattleCheckTypeMatchup();
    // LD_B_A;
    // LD_A_addr(wTypeModifier);
    // AND_A(0b10000000);
    // OR_A_B;
    // LD_addr_A(wTypeModifier);
    wram->wTypeModifier = (wram->wTypeModifier & 0b10000000) | matchup;
    // RET;
    printf("Calculated stab damage: %d.\n", BigEndianToNative16(wram->wCurDamage));
}

uint8_t BattleCheckTypeMatchup(void){
    // LD_HL(wEnemyMonType1);
    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // JR_Z (mCheckTypeMatchup);
    if(hram->hBattleTurn == TURN_PLAYER)
        return CheckTypeMatchup(GetBattleVar(BATTLE_VARS_MOVE_TYPE), wram->wEnemyMon.types);
    // LD_HL(wBattleMonType1);
    // return CheckTypeMatchup();
    return CheckTypeMatchup(GetBattleVar(BATTLE_VARS_MOVE_TYPE), wram->wBattleMon.types);
}

//  There is an incorrect assumption about this function made in the AI related code: when
//  the AI calls CheckTypeMatchup (not BattleCheckTypeMatchup), it assumes that placing the
//  offensive type in a will make this function do the right thing. Since a is overwritten,
//  this assumption is incorrect. A simple fix would be to load the move type for the
//  current move into a in BattleCheckTypeMatchup, before falling through, which is
//  consistent with how the rest of the code assumes this code works like.
uint8_t CheckTypeMatchup(uint8_t d, const uint8_t* hl){
    // PUSH_HL;
    // PUSH_DE;
    // PUSH_BC;
    // LD_A(BATTLE_VARS_MOVE_TYPE);
    // CALL(aGetBattleVar);
    // LD_D_A;
    // LD_B_hl;
    uint8_t b = hl[0];
    // INC_HL;
    // LD_C_hl;
    uint8_t c = hl[1];
    // LD_A(EFFECTIVE);
    // LD_addr_A(wTypeMatchup);
    wram->wTypeMatchup = EFFECTIVE;
    // LD_HL(mTypeMatchups);
    hl = TypeMatchups;

    while(1) {
    // TypesLoop:
        // LD_A_hli;
        uint8_t a = *(hl++);
        // CP_A(-1);
        // IF_Z goto End;
        if(a == 0xff)
            break;
        // CP_A(-2);
        // IF_NZ goto Next;
        if(a == 0xfe) {
            // LD_A(BATTLE_VARS_SUBSTATUS1_OPP);
            // CALL(aGetBattleVar);
            // BIT_A(SUBSTATUS_IDENTIFIED);
            // IF_NZ goto End;
            if(bit_test(GetBattleVar(BATTLE_VARS_SUBSTATUS1_OPP), SUBSTATUS_IDENTIFIED))
                break;
            // goto TypesLoop;
            continue;
        }

    // Next:
        // CP_A_D;
        // IF_NZ goto Nope;
        if(a == d) {
            // LD_A_hli;
            a = *(hl++);
            // CP_A_B;
            // IF_Z goto Yup;
            // CP_A_C;
            // IF_Z goto Yup;
            if(a == b || a == c) {
            // Yup:
                // XOR_A_A;
                // LDH_addr_A(hDividend + 0);
                // LDH_addr_A(hMultiplicand + 0);
                // LDH_addr_A(hMultiplicand + 1);
                // LD_A_hli;
                a = *(hl++);
                // LDH_addr_A(hMultiplicand + 2);
                // LD_A_addr(wTypeMatchup);
                // LDH_addr_A(hMultiplier);
                // CALL(aMultiply);
                // LD_A(10);
                // LDH_addr_A(hDivisor);
                // PUSH_BC;
                // LD_B(4);
                // CALL(aDivide);
                uint32_t m = (wram->wTypeMatchup * a) / 10;
                // POP_BC;
                // LDH_A_addr(hQuotient + 3);
                // LD_addr_A(wTypeMatchup);
                wram->wTypeMatchup = (uint8_t)(m & 0xff);
                // goto TypesLoop;
                continue;
            }
            // goto Nope2;
        }
        else {
        // Nope:
            // INC_HL;
            hl++;
        }

    // Nope2:
        // INC_HL;
        // goto TypesLoop;
        hl++;
    }

// End:
    // POP_BC;
    // POP_DE;
    // POP_HL;
    // RET;
    return wram->wTypeMatchup;
}

void BattleCommand_ResetTypeMatchup(void){
//  Reset the type matchup multiplier to 1.0, if the type matchup is not 0.
//  If there is immunity in play, the move automatically misses.
    PEEK("");
    // CALL(aBattleCheckTypeMatchup);
    uint8_t matchup = BattleCheckTypeMatchup();
    // LD_A_addr(wTypeMatchup);
    // AND_A_A;
    // LD_A(EFFECTIVE);
    // IF_NZ goto reset;
    if(matchup != 0) {
    // reset:
        // LD_addr_A(wTypeMatchup);
        wram->wTypeMatchup = EFFECTIVE;
        // RET;
        return;
    }

    // CALL(aResetDamage);
    ResetDamage();
    // XOR_A_A;
    // LD_addr_A(wTypeModifier);
    wram->wTypeModifier = 0;
    // INC_A;
    // LD_addr_A(wAttackMissed);
    wram->wAttackMissed = TRUE;
    // RET;

// INCLUDE "engine/battle/ai/switch.asm"

// INCLUDE "data/types/type_matchups.asm"

}

void BattleCommand_DamageVariation(void){
//  damagevariation

//  Modify the damage spread between 85% and 100%.

//  Because of the method of division the probability distribution
//  is not consistent. This makes the highest damage multipliers
//  rarer than normal.
    PEEK("");
//  No point in reducing 1 or 0 damage.
    // LD_HL(wCurDamage);
    uint16_t dmg = BigEndianToNative16(wram->wCurDamage);
    // LD_A_hli;
    // AND_A_A;
    // IF_NZ goto go;
    // LD_A_hl;
    // CP_A(2);
    // RET_C ;
    if(dmg < 2)
        return;


// go:
//  Start with the maximum damage.
    // XOR_A_A;
    // LDH_addr_A(hMultiplicand + 0);
    // DEC_HL;
    // LD_A_hli;
    // LDH_addr_A(hMultiplicand + 1);
    // LD_A_hl;
    // LDH_addr_A(hMultiplicand + 2);
    uint32_t n = dmg;

//  Multiply by 85-100%...

    uint8_t a;
    do {
    // loop:
        // CALL(aBattleRandom);
        a = v_BattleRandom_Conv();
        // RRCA;
        a = (a >> 1) | (a << 7);
        // CP_A(85 percent + 1);
        // IF_C goto loop;
    } while(a < 85 percent + 1);

    // LDH_addr_A(hMultiplier);
    // CALL(aMultiply);
    n *= a;

//  ...divide by 100%...
    // LD_A(100 percent);
    // LDH_addr_A(hDivisor);
    // LD_B(0x4);
    // CALL(aDivide);
    n /= 100 percent;

//  ...to get .85-1.00x damage.
    // LDH_A_addr(hQuotient + 2);
    // LD_HL(wCurDamage);
    // LD_hli_A;
    // LDH_A_addr(hQuotient + 3);
    // LD_hl_A;
    wram->wCurDamage = NativeToBigEndian16((uint16_t)n);
    // RET;
    printf("Damage variation: %d.\n", BigEndianToNative16(wram->wCurDamage));
}

static bool BattleCommand_CheckHit_DreamEater(void) {
//  Return z if we're trying to eat the dream of
//  a monster that isn't sleeping.
    // LD_A(BATTLE_VARS_MOVE_EFFECT);
    // CALL(aGetBattleVar);
    // CP_A(EFFECT_DREAM_EATER);
    // RET_NZ ;
    if(GetBattleVar(BATTLE_VARS_MOVE_EFFECT) != EFFECT_DREAM_EATER)
        return true; // Ignore this hit check.

    // LD_A(BATTLE_VARS_STATUS_OPP);
    // CALL(aGetBattleVar);
    // AND_A(SLP);
    // RET;
    return (GetBattleVar(BATTLE_VARS_STATUS_OPP) & SLP) != 0;
}

//  Return nz (true) if the opponent is protected.
static bool BattleCommand_CheckHit_Protect(void) {
    // LD_A(BATTLE_VARS_SUBSTATUS1_OPP);
    // CALL(aGetBattleVar);
    // BIT_A(SUBSTATUS_PROTECT);
    // RET_Z ;
    if(!bit_test(GetBattleVar(BATTLE_VARS_SUBSTATUS1_OPP), SUBSTATUS_PROTECT))
        return false;

    // LD_C(40);
    // CALL(aDelayFrames);
    DelayFrames(40);

//  'protecting itself!'
    // LD_HL(mProtectingItselfText);
    // CALL(aStdBattleTextbox);
    StdBattleTextbox(ProtectingItselfText);

    // LD_C(40);
    // CALL(aDelayFrames);
    DelayFrames(40);

    // LD_A(1);
    // AND_A_A;
    // RET;
    return true;
}

//  Return z (true) if using an HP drain move on a substitute.
static bool BattleCommand_CheckHit_DrainSub(void) {
    // CALL(aCheckSubstituteOpp);
    // IF_Z goto not_draining_sub;
    if(CheckSubstituteOpp()) {

        // LD_A(BATTLE_VARS_MOVE_EFFECT);
        // CALL(aGetBattleVar);
        uint8_t effect = GetBattleVar(BATTLE_VARS_MOVE_EFFECT);

        // CP_A(EFFECT_LEECH_HIT);
        // RET_Z ;
        // CP_A(EFFECT_DREAM_EATER);
        // RET_Z ;
        if(effect == EFFECT_LEECH_HIT || effect == EFFECT_DREAM_EATER)
            return true;
    }

// not_draining_sub:
    // LD_A(1);
    // AND_A_A;
    // RET;
    return false;
}

//  Return nz (true) if we are locked-on and aren't trying to use Earthquake,
//  Fissure or Magnitude on a monster that is flying.
static bool BattleCommand_CheckHit_LockOn(void) {
    // LD_A(BATTLE_VARS_SUBSTATUS5_OPP);
    // CALL(aGetBattleVarAddr);
    uint8_t* hl = GetBattleVarAddr(BATTLE_VARS_SUBSTATUS5_OPP);
    // BIT_hl(SUBSTATUS_LOCK_ON);
    if(!bit_test(*hl, SUBSTATUS_LOCK_ON))
        return false; // bit is already off, so don't reset it.
    // RES_hl(SUBSTATUS_LOCK_ON);
    bit_reset(*hl, SUBSTATUS_LOCK_ON);
    // RET_Z ;

    // LD_A(BATTLE_VARS_SUBSTATUS3_OPP);
    // CALL(aGetBattleVar);
    // BIT_A(SUBSTATUS_FLYING);
    // IF_Z goto LockedOn;
    if(!bit_test(GetBattleVar(BATTLE_VARS_SUBSTATUS3_OPP), SUBSTATUS_FLYING))
        return true;

    // LD_A(BATTLE_VARS_MOVE_ANIM);
    // CALL(aGetBattleVar);
    switch(GetBattleVar(BATTLE_VARS_MOVE_ANIM)) {
        // CP_A(EARTHQUAKE);
        // RET_Z ;
        // CP_A(FISSURE);
        // RET_Z ;
        // CP_A(MAGNITUDE);
        // RET_Z ;
        case EARTHQUAKE:
        case FISSURE: 
        case MAGNITUDE: 
            return false;
        default:
            return true;
    }
// LockedOn:
    // LD_A(1);
    // AND_A_A;
    // RET;
}

//  Check for moves that can hit underground/flying opponents.
//  Return z (true) if the current move can hit the opponent.
static bool BattleCommand_CheckHit_FlyDigMoves(void) {
    // LD_A(BATTLE_VARS_SUBSTATUS3_OPP);
    // CALL(aGetBattleVar);
    uint8_t ss3 = GetBattleVar(BATTLE_VARS_SUBSTATUS3_OPP);
    // AND_A(1 << SUBSTATUS_FLYING | 1 << SUBSTATUS_UNDERGROUND);
    // RET_Z ;
    if(!(ss3 & (1 << SUBSTATUS_FLYING | 1 << SUBSTATUS_UNDERGROUND)))
        return true;

    // BIT_A(SUBSTATUS_FLYING);
    // IF_Z goto DigMoves;
    if(!bit_test(ss3, SUBSTATUS_FLYING)) {
    // DigMoves:
        // LD_A(BATTLE_VARS_MOVE_ANIM);
        // CALL(aGetBattleVar);
        switch(GetBattleVar(BATTLE_VARS_MOVE_ANIM)) {
            // CP_A(EARTHQUAKE);
            // RET_Z ;
            // CP_A(FISSURE);
            // RET_Z ;
            // CP_A(MAGNITUDE);
            case EARTHQUAKE:
            case FISSURE:
            case MAGNITUDE:
                return true;
        }
        return false;
    }

    // LD_A(BATTLE_VARS_MOVE_ANIM);
    // CALL(aGetBattleVar);

    switch(GetBattleVar(BATTLE_VARS_MOVE_ANIM)) {
        // CP_A(GUST);
        // RET_Z ;
        // CP_A(WHIRLWIND);
        // RET_Z ;
        // CP_A(THUNDER);
        // RET_Z ;
        // CP_A(TWISTER);
        case GUST:
        case WHIRLWIND:
        case THUNDER:
        case TWISTER:
            return true;
        // RET;
    }
    return false;
}

static bool BattleCommand_CheckHit_ThunderRain(void) {
//  Return z if the current move always hits in rain, and it is raining.
    // LD_A(BATTLE_VARS_MOVE_EFFECT);
    // CALL(aGetBattleVar);
    // CP_A(EFFECT_THUNDER);
    // RET_NZ ;
    if(GetBattleVar(BATTLE_VARS_MOVE_EFFECT) != EFFECT_THUNDER)
        return false;

    // LD_A_addr(wBattleWeather);
    // CP_A(WEATHER_RAIN);
    // RET;
    return wram->wBattleWeather == WEATHER_RAIN;
}

static bool BattleCommand_CheckHit_XAccuracy(void) {
    // LD_A(BATTLE_VARS_SUBSTATUS4);
    // CALL(aGetBattleVar);
    // BIT_A(SUBSTATUS_X_ACCURACY);
    // RET;
    return bit_test(GetBattleVar(BATTLE_VARS_SUBSTATUS4), SUBSTATUS_X_ACCURACY);
}

static void BattleCommand_CheckHit_StatModifiers(void) {
    // LDH_A_addr(hBattleTurn);
    // AND_A_A;

// load the user's accuracy into b and the opponent's evasion into c.
    uint8_t* acc;
    uint8_t b, c;
    if(hram->hBattleTurn == TURN_PLAYER) {
        // LD_HL(wPlayerMoveStruct + MOVE_ACC);
        acc = &wram->wPlayerMoveStruct.accuracy;
        // LD_A_addr(wPlayerAccLevel);
        // LD_B_A;
        b = wram->wPlayerAccLevel;
        // LD_A_addr(wEnemyEvaLevel);
        // LD_C_A;
        c = wram->wEnemyEvaLevel;

        // IF_Z goto got_acc_eva;
    }
    else {
        // LD_HL(wEnemyMoveStruct + MOVE_ACC);
        acc = &wram->wEnemyMoveStruct.accuracy;
        // LD_A_addr(wEnemyAccLevel);
        // LD_B_A;
        b = wram->wEnemyAccLevel;
        // LD_A_addr(wPlayerEvaLevel);
        // LD_C_A;
        c = wram->wPlayerEvaLevel;
    }

// got_acc_eva:
    // CP_A_B;
    // IF_C goto skip_foresight_check;
    if(c >= b) {
    // if the target's evasion is greater than the user's accuracy,
    // check the target's foresight status
        // LD_A(BATTLE_VARS_SUBSTATUS1_OPP);
        // CALL(aGetBattleVar);
        // BIT_A(SUBSTATUS_IDENTIFIED);
        // RET_NZ ;
        if(bit_test(GetBattleVar(BATTLE_VARS_SUBSTATUS1_OPP), SUBSTATUS_IDENTIFIED))
            return;
    }

    printf("Input accuracy: %d.\n", *acc);
// skip_foresight_check:
// subtract evasion from 14
    // LD_A(MAX_STAT_LEVEL + 1);
    // SUB_A_C;
    // LD_C_A;
    c = (MAX_STAT_LEVEL + 1) - c;
// store the base move accuracy for math ops
    // XOR_A_A;
    // LDH_addr_A(hMultiplicand + 0);
    // LDH_addr_A(hMultiplicand + 1);
    // LD_A_hl;
    // LDH_addr_A(hMultiplicand + 2);
    uint32_t n = *acc;
    // PUSH_HL;
    // LD_D(2);  // do this twice, once for the user's accuracy and once for the target's evasion

    for(uint8_t d = 0; d < 2; ++d) {
    // accuracy_loop:
    // look up the multiplier from the table
        // PUSH_BC;
        // LD_HL(mAccuracyLevelMultipliers);
        // DEC_B;
        // SLA_B;
        // LD_C_B;
        // LD_B(0);
        // ADD_HL_BC;
        // POP_BC;
        const uint8_t* hl = AccuracyLevelMultipliers[b - 1];
    // multiply by the first byte in that row...
        // LD_A_hli;
        // LDH_addr_A(hMultiplier);
        // CALL(aMultiply);
        n *= hl[0];
    // ... and divide by the second byte
        // LD_A_hl;
        // LDH_addr_A(hDivisor);
        // LD_B(4);
        // CALL(aDivide);
        n /= hl[1];
    // minimum accuracy is $0001
        // LDH_A_addr(hQuotient + 3);
        // LD_B_A;
        // LDH_A_addr(hQuotient + 2);
        // OR_A_B;
        // IF_NZ goto min_accuracy;
        if(n == 0) {
            // LDH_addr_A(hQuotient + 2);
            // LD_A(1);
            // LDH_addr_A(hQuotient + 3);
            n = 1;
        }


    // min_accuracy:
    // do the same thing to the target's evasion
        // LD_B_C;
        // DEC_D;
        // IF_NZ goto accuracy_loop;
        b = c;
    }

// if the result is more than 2 bytes, max out at 100%
    // LDH_A_addr(hQuotient + 2);
    // AND_A_A;
    // LDH_A_addr(hQuotient + 3);
    // IF_Z goto finish_accuracy;
    // LD_A(0xff);
    if(n > 0xff)
        n = 0xff;


// finish_accuracy:
    // POP_HL;
    // LD_hl_A;
    *acc = (uint8_t)n;
    printf("Output accuracy: %d.\n", *acc);
    // RET;
}

void BattleCommand_CheckHit(void){
//  checkhit
    PEEK("");
    // CALL(aBattleCommand_CheckHit_DreamEater);
    // JP_Z (mBattleCommand_CheckHit_Miss);
    if(!BattleCommand_CheckHit_DreamEater())
        goto Miss;

    // CALL(aBattleCommand_CheckHit_Protect);
    // JP_NZ (mBattleCommand_CheckHit_Miss);
    if(BattleCommand_CheckHit_Protect())
        goto Miss;

    // CALL(aBattleCommand_CheckHit_DrainSub);
    // JP_Z (mBattleCommand_CheckHit_Miss);
    if(BattleCommand_CheckHit_DrainSub())
        goto Miss;

    // CALL(aBattleCommand_CheckHit_LockOn);
    // RET_NZ ;
    if(BattleCommand_CheckHit_LockOn())
        return;

    // CALL(aBattleCommand_CheckHit_FlyDigMoves);
    // JP_NZ (mBattleCommand_CheckHit_Miss);
    if(!BattleCommand_CheckHit_FlyDigMoves())
        goto Miss;

    // CALL(aBattleCommand_CheckHit_ThunderRain);
    // RET_Z ;
    if(BattleCommand_CheckHit_ThunderRain())
        return;

    // CALL(aBattleCommand_CheckHit_XAccuracy);
    // RET_NZ ;
    if(BattleCommand_CheckHit_XAccuracy())
        return;

// Perfect-accuracy moves
    // LD_A(BATTLE_VARS_MOVE_EFFECT);
    // CALL(aGetBattleVar);
    // CP_A(EFFECT_ALWAYS_HIT);
    // RET_Z ;
    if(GetBattleVar(BATTLE_VARS_MOVE_EFFECT) == EFFECT_ALWAYS_HIT)
        return;

    // CALL(aBattleCommand_CheckHit_StatModifiers);
    BattleCommand_CheckHit_StatModifiers();

    // LD_A_addr(wPlayerMoveStruct + MOVE_ACC);
    // LD_B_A;
    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // IF_Z goto BrightPowder;
    // LD_A_addr(wEnemyMoveStruct + MOVE_ACC);
    // LD_B_A;
    uint8_t b = (hram->hBattleTurn == TURN_PLAYER)? wram->wPlayerMoveStruct.accuracy: wram->wEnemyMoveStruct.accuracy;


// BrightPowder:
    // PUSH_BC;
    // CALL(aGetOpponentItem);
    uint16_t item_effect = GetOpponentItem(NULL);
    // LD_A_B;
    // CP_A(HELD_BRIGHTPOWDER);
    // LD_A_C;  // % miss
    // POP_BC;
    // IF_NZ goto skip_brightpowder;

    if(HIGH(item_effect) == HELD_BRIGHTPOWDER) {
        // LD_C_A;
        // LD_A_B;
        // SUB_A_C;
        uint16_t temp = b - LOW(item_effect);
        // LD_B_A;
        // IF_NC goto skip_brightpowder;
        // LD_B(0);
        b = (temp & 0xff00)? 0: temp & 0xff;
    }

// skip_brightpowder:
    // LD_A_B;
    // CP_A(-1);
    // IF_Z goto Hit;
    if(b == 0xff)
        return;

    // CALL(aBattleRandom);
    // CP_A_B;
    // IF_NC goto Miss;
    if(v_BattleRandom_Conv() < b)
        return;


// Hit:
    // RET;


Miss:
//  Keep the damage value intact if we're using (Hi) Jump Kick.
    // LD_A(BATTLE_VARS_MOVE_EFFECT);
    // CALL(aGetBattleVar);
    // CP_A(EFFECT_JUMP_KICK);
    // IF_Z goto Missed;
    // CALL(aResetDamage);
    if(GetBattleVar(BATTLE_VARS_MOVE_EFFECT) != EFFECT_JUMP_KICK)
        ResetDamage();

// Missed:
    // LD_A(1);
    // LD_addr_A(wAttackMissed);
    wram->wAttackMissed = TRUE;
    // RET;

// INCLUDE "data/battle/accuracy_multipliers.asm"
}

void BattleCommand_EffectChance(void){
//  effectchance
    PEEK("");
    // XOR_A_A;
    // LD_addr_A(wEffectFailed);
    wram->wEffectFailed = FALSE;
    // CALL(aCheckSubstituteOpp);
    // IF_NZ goto failed;
    if(CheckSubstituteOpp())
        return;

    // PUSH_HL;
    // LD_HL(wPlayerMoveStruct + MOVE_CHANCE);
    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // IF_Z goto got_move_chance;
    // LD_HL(wEnemyMoveStruct + MOVE_CHANCE);
    uint8_t chance = (hram->hBattleTurn == TURN_PLAYER)? wram->wPlayerMoveStruct.effectChance: wram->wEnemyMoveStruct.effectChance;

// got_move_chance:

// BUG: 1/256 chance to fail even for a 100% effect chance,
// since carry is not set if BattleRandom == [hl] == 255
    // CALL(aBattleRandom);
    // CP_A_hl;
    // POP_HL;
    // RET_C ;
#if BUGFIX_EFFECTCHANCE
    if(v_BattleRandom_Conv() <= chance)
#else
    if(v_BattleRandom_Conv() <  chance)
#endif
        return;



// failed:
    // LD_A(1);
    // LD_addr_A(wEffectFailed);
    wram->wEffectFailed = TRUE;
    // AND_A_A;
    // RET;
}

static bool BattleCommand_LowerSub_Rampage(void) {
    // LD_A(BATTLE_VARS_MOVE_EFFECT);
    // CALL(aGetBattleVar);
    uint8_t effect = GetBattleVar(BATTLE_VARS_MOVE_EFFECT);
    // CP_A(EFFECT_ROLLOUT);
    // IF_Z goto rollout_rampage;
    // CP_A(EFFECT_RAMPAGE);
    // IF_Z goto rollout_rampage;
    if(effect == EFFECT_ROLLOUT || effect == EFFECT_RAMPAGE) {
    // rollout_rampage:
        // LD_A_addr(wSomeoneIsRampaging);
        // AND_A_A;
        bool res = wram->wSomeoneIsRampaging != 0;
        // LD_A(0);
        // LD_addr_A(wSomeoneIsRampaging);
        wram->wSomeoneIsRampaging = 0;
        // RET;
        return res;
    }

    // LD_A(1);
    // AND_A_A;
    // RET;
    return true;
}

void BattleCommand_LowerSub(void){
//  lowersub
    PEEK("");
    // LD_A(BATTLE_VARS_SUBSTATUS4);
    // CALL(aGetBattleVar);
    // BIT_A(SUBSTATUS_SUBSTITUTE);
    // RET_Z ;
    if(!bit_test(GetBattleVar(BATTLE_VARS_SUBSTATUS4), SUBSTATUS_SUBSTITUTE))
        return;

    // LD_A(BATTLE_VARS_SUBSTATUS3);
    // CALL(aGetBattleVar);
    // BIT_A(SUBSTATUS_CHARGED);
    // IF_NZ goto already_charged;
    if(!bit_test(GetBattleVar(BATTLE_VARS_SUBSTATUS3), SUBSTATUS_CHARGED)) {
        // LD_A(BATTLE_VARS_MOVE_EFFECT);
        // CALL(aGetBattleVar);
        switch(GetBattleVar(BATTLE_VARS_MOVE_EFFECT)) {
            // CP_A(EFFECT_RAZOR_WIND);
            // IF_Z goto charge_turn;
            case EFFECT_RAZOR_WIND:
            // CP_A(EFFECT_SKY_ATTACK);
            // IF_Z goto charge_turn;
            case EFFECT_SKY_ATTACK:
            // CP_A(EFFECT_SKULL_BASH);
            // IF_Z goto charge_turn;
            case EFFECT_SKULL_BASH:
            // CP_A(EFFECT_SOLARBEAM);
            // IF_Z goto charge_turn;
            case EFFECT_SOLARBEAM:
            // CP_A(EFFECT_FLY);
            // IF_Z goto charge_turn;
            case EFFECT_FLY:
                break; // goto charge_turn
            default:
                goto already_charged;
        }
    }
    else {
    already_charged:
        // CALL(aBattleCommand_LowerSub_Rampage);
        // IF_Z goto charge_turn;

        // CALL(aCheckUserIsCharging);
        // RET_NZ ;
        if(BattleCommand_LowerSub_Rampage() && CheckUserIsCharging())
            return;
    }


// charge_turn:
    // CALL(av_CheckBattleScene);
    // IF_C goto mimic_anims;
    if(!CheckBattleScene()) {
    // mimic_anims:
        // CALL(aBattleCommand_LowerSubNoAnim);
        BattleCommand_LowerSubNoAnim();
        // JP(mBattleCommand_MoveDelay);
        return BattleCommand_MoveDelay();
    }

    // XOR_A_A;
    // LD_addr_A(wNumHits);
    wram->wNumHits = 0;
    // LD_addr_A(wFXAnimID + 1);
    wram->wFXAnimID &= 0xff; // Clear high byte
    // INC_A;
    // LD_addr_A(wBattleAnimParam);
    wram->wBattleAnimParam = 1;
    // LD_A(SUBSTITUTE);
    // JP(mLoadAnim);
    return LoadAnim(SUBSTITUTE);


// Rampage:
    // LD_A(BATTLE_VARS_MOVE_EFFECT);
    // CALL(aGetBattleVar);
    // CP_A(EFFECT_ROLLOUT);
    // IF_Z goto rollout_rampage;
    // CP_A(EFFECT_RAMPAGE);
    // IF_Z goto rollout_rampage;

    // LD_A(1);
    // AND_A_A;
    // RET;


// rollout_rampage:
    // LD_A_addr(wSomeoneIsRampaging);
    // AND_A_A;
    // LD_A(0);
    // LD_addr_A(wSomeoneIsRampaging);
    // RET;
}

void BattleCommand_MoveAnim(void){
//  moveanim
    PEEK("");
    // CALL(aBattleCommand_LowerSub);
    BattleCommand_LowerSub();
    // CALL(aBattleCommand_MoveAnimNoSub);
    BattleCommand_MoveAnimNoSub();
    // JP(mBattleCommand_RaiseSub);
    return BattleCommand_RaiseSub();

}

void BattleCommand_MoveAnimNoSub(void){
    // LD_A_addr(wAttackMissed);
    // AND_A_A;
    // JP_NZ (mBattleCommand_MoveDelay);
    if(wram->wAttackMissed)
        return BattleCommand_MoveDelay();

    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // LD_DE(wPlayerRolloutCount);
    // LD_A(BATTLEANIM_ENEMY_DAMAGE);
    // IF_Z goto got_rollout_count;
    // LD_DE(wEnemyRolloutCount);
    // LD_A(BATTLEANIM_PLAYER_DAMAGE);
    uint8_t*  de = (hram->hBattleTurn == TURN_PLAYER)? &wram->wPlayerRolloutCount: &wram->wEnemyRolloutCount;

// got_rollout_count:
    // LD_addr_A(wNumHits);
    wram->wNumHits = (hram->hBattleTurn == TURN_PLAYER)? BATTLEANIM_ENEMY_DAMAGE: BATTLEANIM_PLAYER_DAMAGE;
    // LD_A(BATTLE_VARS_MOVE_EFFECT);
    // CALL(aGetBattleVar);
    uint8_t effect = GetBattleVar(BATTLE_VARS_MOVE_EFFECT);
    switch(effect) {
        // CP_A(EFFECT_MULTI_HIT);
        // IF_Z goto alternate_anim;
        // CP_A(EFFECT_CONVERSION);
        // IF_Z goto alternate_anim;
        // CP_A(EFFECT_DOUBLE_HIT);
        // IF_Z goto alternate_anim;
        // CP_A(EFFECT_POISON_MULTI_HIT);
        // IF_Z goto alternate_anim;
        case EFFECT_MULTI_HIT:
        case EFFECT_CONVERSION:
        case EFFECT_DOUBLE_HIT:
        case EFFECT_POISON_MULTI_HIT:
        {
        // alternate_anim:
            // LD_A_addr(wBattleAnimParam);
            // AND_A(1);
            // XOR_A(1);
            // LD_addr_A(wBattleAnimParam);
            wram->wBattleAnimParam = (wram->wBattleAnimParam & 1) ^ 1;
            // LD_A_de;
            // CP_A(1);
            // PUSH_AF;
            // LD_A(BATTLE_VARS_MOVE_ANIM);
            // CALL(aGetBattleVar);
            // LD_E_A;
            // LD_D(0);
            // POP_AF;
            // JP_Z (mPlayFXAnimID);
            if(*de == 1)
                return PlayFXAnimID(GetBattleVar(BATTLE_VARS_MOVE_ANIM));
            // XOR_A_A;
            // LD_addr_A(wNumHits);
            wram->wNumHits = 0;
            // JP(mPlayFXAnimID);
            return PlayFXAnimID(GetBattleVar(BATTLE_VARS_MOVE_ANIM));
        }

        default:
            // XOR_A_A;
            // LD_addr_A(wBattleAnimParam);
            wram->wBattleAnimParam = 0;
            // fallthrough

        // CP_A(EFFECT_TRIPLE_KICK);
        // IF_Z goto triplekick;
        case EFFECT_TRIPLE_KICK:
            break;
    }

// triplekick:
    // LD_A(BATTLE_VARS_MOVE_ANIM);
    // CALL(aGetBattleVar);
    // LD_E_A;
    // LD_D(0);
    // CALL(aPlayFXAnimID);
    PlayFXAnimID(GetBattleVar(BATTLE_VARS_MOVE_ANIM));

    // LD_A(BATTLE_VARS_MOVE_ANIM);
    // CALL(aGetBattleVar);
    uint8_t anim = GetBattleVar(BATTLE_VARS_MOVE_ANIM);
    // CP_A(FLY);
    // IF_Z goto clear_sprite;
    // CP_A(DIG);
    // RET_NZ ;
    if(anim == FLY || anim == DIG) {
    // clear_sprite:
        // JP(mAppearUserLowerSub);
        return AppearUserLowerSub();
    }
    return;
}

void BattleCommand_StatUpAnim(void){
    // LD_A_addr(wAttackMissed);
    // AND_A_A;
    // JP_NZ (mBattleCommand_MoveDelay);
    if(wram->wAttackMissed)
        return BattleCommand_MoveDelay();

    // XOR_A_A;
    // JR(mBattleCommand_StatUpDownAnim);
    BattleCommand_StatUpDownAnim(0);

}

void BattleCommand_StatDownAnim(void){
    // LD_A_addr(wAttackMissed);
    // AND_A_A;
    // JP_NZ (mBattleCommand_MoveDelay);
    if(wram->wAttackMissed)
        return BattleCommand_MoveDelay();

    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // LD_A(BATTLEANIM_ENEMY_STAT_DOWN);
    // JR_Z (mBattleCommand_StatUpDownAnim);
    if(hram->hBattleTurn == TURN_PLAYER)
        return BattleCommand_StatUpDownAnim(BATTLEANIM_ENEMY_STAT_DOWN);
    // LD_A(BATTLEANIM_WOBBLE);
    else
        return BattleCommand_StatUpDownAnim(BATTLEANIM_WOBBLE);

// fallthrough
}

void BattleCommand_StatUpDownAnim(uint8_t anim){
// Uncomment the following line to turn off the stat up/down animation.
    // REG_A = BATTLEANIM_NONE;
    // LD_addr_A(wNumHits);
    wram->wNumHits = anim;
    // XOR_A_A;
    // LD_addr_A(wBattleAnimParam);
    wram->wBattleAnimParam = 0;
    // LD_A(BATTLE_VARS_MOVE_ANIM);
    // CALL(aGetBattleVar);
    // LD_E_A;
    // LD_D(0);
    // JP(mPlayFXAnimID);
    return PlayFXAnimID(GetBattleVar(BATTLE_VARS_MOVE_ANIM));
}

void BattleCommand_SwitchTurn(void){
//  switchturn
    PEEK("");
    // LDH_A_addr(hBattleTurn);
    // XOR_A(1);
    // LDH_addr_A(hBattleTurn);
    hram->hBattleTurn ^= 1;
    // RET;
}

void BattleCommand_RaiseSub(void){
//  raisesub
    PEEK("");
    // LD_A(BATTLE_VARS_SUBSTATUS4);
    // CALL(aGetBattleVar);
    // BIT_A(SUBSTATUS_SUBSTITUTE);
    // RET_Z ;
    if(!bit_test(GetBattleVar(BATTLE_VARS_SUBSTATUS4), SUBSTATUS_SUBSTITUTE))
        return;

    // CALL(av_CheckBattleScene);
    // JP_C (mBattleCommand_RaiseSubNoAnim);
    if(!CheckBattleScene())
        return BattleCommand_RaiseSubNoAnim();

    // XOR_A_A;
    // LD_addr_A(wNumHits);
    wram->wNumHits = 0;
    // LD_addr_A(wFXAnimID + 1);
    wram->wFXAnimID &= 0xff;
    // LD_A(0x2);
    // LD_addr_A(wBattleAnimParam);
    wram->wBattleAnimParam = 0x2;
    // LD_A(SUBSTITUTE);
    // JP(mLoadAnim);
    return LoadAnim(SUBSTITUTE);
}

void BattleCommand_FailureText(void){
//  failuretext
//  If the move missed or failed, load the appropriate
//  text, and end the effects of multi-turn or multi-
//  hit moves.
    PEEK("");
    // LD_A_addr(wAttackMissed);
    // AND_A_A;
    // RET_Z ;
    if(!wram->wAttackMissed)
        return;

    // CALL(aGetFailureResultText);
    GetFailureResultText();
    // LD_A(BATTLE_VARS_MOVE_ANIM);
    // CALL(aGetBattleVarAddr);
    struct Move* move = (struct Move*)GetBattleVarAddr(BATTLE_VARS_MOVE_ANIM);

    // CP_A(FLY);
    // IF_Z goto fly_dig;
    // CP_A(DIG);
    // IF_Z goto fly_dig;
    if(move->animation == FLY || move->animation == DIG) {
    // fly_dig:
        // LD_A(BATTLE_VARS_SUBSTATUS3);
        // CALL(aGetBattleVarAddr);
        uint8_t* hl = GetBattleVarAddr(BATTLE_VARS_SUBSTATUS3);
        // RES_hl(SUBSTATUS_UNDERGROUND);
        bit_reset(*hl, SUBSTATUS_UNDERGROUND);
        // RES_hl(SUBSTATUS_FLYING);
        bit_reset(*hl, SUBSTATUS_FLYING);
        // CALL(aAppearUserRaiseSub);
        AppearUserRaiseSub();
        // JP(mEndMoveEffect);
        return EndMoveEffect();
    }

//  Move effect:
    // INC_HL;
    // LD_A_hl;

    switch(move->effect) {
        // CP_A(EFFECT_MULTI_HIT);
        // IF_Z goto multihit;
        // CP_A(EFFECT_DOUBLE_HIT);
        // IF_Z goto multihit;
        // CP_A(EFFECT_POISON_MULTI_HIT);
        // IF_Z goto multihit;
        case EFFECT_MULTI_HIT:
        case EFFECT_DOUBLE_HIT:
        case EFFECT_POISON_MULTI_HIT:
        // multihit:
            // CALL(aBattleCommand_RaiseSub);
            BattleCommand_RaiseSub();
            // JP(mEndMoveEffect);
            return EndMoveEffect();

        default:
            // JP(mEndMoveEffect);
            return EndMoveEffect();
    }

}

static void BattleCommand_ApplyDamage_update_damage_taken(void) {
    // LD_A(BATTLE_VARS_SUBSTATUS4_OPP);
    // CALL(aGetBattleVar);
    // BIT_A(SUBSTATUS_SUBSTITUTE);
    // RET_NZ ;
    if(bit_test(GetBattleVar(BATTLE_VARS_SUBSTATUS4_OPP), SUBSTATUS_SUBSTITUTE))
        return;

    // LD_DE(wPlayerDamageTaken + 1);
    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // IF_NZ goto got_damage_taken;
    // LD_DE(wEnemyDamageTaken + 1);
    uint16_t* taken = (uint16_t*)((hram->hBattleTurn != TURN_PLAYER)? wram_ptr(wPlayerDamageTaken): wram_ptr(wEnemyDamageTaken));
    uint16_t dmg = BigEndianToNative16(wram->wCurDamage);

// got_damage_taken:
    // LD_A_addr(wCurDamage + 1);
    // LD_B_A;
    // LD_A_de;
    // ADD_A_B;
    // LD_de_A;
    // DEC_DE;
    // LD_A_addr(wCurDamage);
    // LD_B_A;
    // LD_A_de;
    // ADC_A_B;
    // LD_de_A;
    // RET_NC ;
    uint32_t dmg2 = dmg + BigEndianToNative16(*taken);
    if(dmg2 > 0xffff) {
        // LD_A(0xff);
        // LD_de_A;
        // INC_DE;
        // LD_de_A;
        *taken = NativeToBigEndian16(0xffff);
    }
    else {
        *taken = NativeToBigEndian16((uint16_t)dmg2);
    }
    // RET;
    printf("Damage taken: %d.\n", BigEndianToNative16(*taken));
    return;
}

void BattleCommand_ApplyDamage(void){
//  applydamage
    PEEK("");
    // LD_A(BATTLE_VARS_SUBSTATUS1_OPP);
    // CALL(aGetBattleVar);
    // BIT_A(SUBSTATUS_ENDURE);
    // IF_Z goto focus_band;
    uint8_t b;
    if(bit_test(GetBattleVar(BATTLE_VARS_SUBSTATUS1_OPP), SUBSTATUS_ENDURE)) {
        // CALL(aBattleCommand_FalseSwipe);
        if(!CheckFalseSwipe()) {
            // LD_B(0);
            b = 0;
            // IF_NC goto damage;
        } 
        else {
            // LD_B(1);
            b = 1;
            // goto damage;
        }
    }
    else {
    // focus_band:
        // CALL(aGetOpponentItem);
        uint16_t item_effect = GetOpponentItem(NULL);
        // LD_A_B;
        // CP_A(HELD_FOCUS_BAND);
        // LD_B(0);
        // IF_NZ goto damage;
        if(HIGH(item_effect) == HELD_FOCUS_BAND) {
            // CALL(aBattleRandom);
            // CP_A_C;
            // IF_NC goto damage;
            // CALL(aBattleCommand_FalseSwipe);
            // LD_B(0);
            // IF_NC goto damage;
            if(v_BattleRandom_Conv() < LOW(item_effect) 
            && CheckFalseSwipe()) {
                // LD_B(2);
                b = 2;
            }
            else {
                b = 0;
            }
        }
        else {
            b = 0;
        }
    }

// damage:
    // PUSH_BC;
    // CALL(aBattleCommand_ApplyDamage_update_damage_taken);
    BattleCommand_ApplyDamage_update_damage_taken();
    // LD_C(FALSE);
    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // IF_NZ goto damage_player;
    if(hram->hBattleTurn != TURN_PLAYER)  {
    // damage_player:
        // CALL(aDoPlayerDamage);
        DoPlayerDamage(false);
    }
    else {
        // CALL(aDoEnemyDamage);
        DoEnemyDamage(false);
        // goto done_damage;
    }

// done_damage:
    // POP_BC;
    // LD_A_B;
    // AND_A_A;
    // RET_Z ;
    if(b == 0)
        return;

    // DEC_A;
    // IF_NZ goto focus_band_text;
    else if(b == 1) {
        // LD_HL(mEnduredText);
        // JP(mStdBattleTextbox);
        return StdBattleTextbox(EnduredText);
    }
    else {
    // focus_band_text:
        item_t item;
        // CALL(aGetOpponentItem);
        GetOpponentItem(&item);
        // LD_A_hl;
        // LD_addr_A(wNamedObjectIndex);
        // CALL(aGetItemName);
        GetItemName(item);
        // LD_HL(mHungOnText);
        // JP(mStdBattleTextbox);
        return StdBattleTextbox(HungOnText);
    }
}

void GetFailureResultText(void){
    // LD_HL(mDoesntAffectText);
    // LD_DE(mDoesntAffectText);
    // LD_A_addr(wTypeModifier);
    // AND_A(0x7f);
    // IF_Z goto got_text;
    if((wram->wTypeModifier & 0x7f) == 0) {
        FailText_CheckOpponentProtect(DoesntAffectText, DoesntAffectText);
    }
    // LD_A(BATTLE_VARS_MOVE_EFFECT);
    // CALL(aGetBattleVar);
    // CP_A(EFFECT_FUTURE_SIGHT);
    // LD_HL(mButItFailedText);
    // LD_DE(mItFailedText);
    // IF_Z goto got_text;
    else if(GetBattleVar(BATTLE_VARS_MOVE_EFFECT) == EFFECT_FUTURE_SIGHT) {
        FailText_CheckOpponentProtect(ButItFailedText, ItFailedText);
    }
    // LD_HL(mAttackMissedText);
    // LD_DE(mAttackMissed2Text);
    // LD_A_addr(wCriticalHit);
    // CP_A(-1);
    // IF_NZ goto got_text;
    else if(wram->wCriticalHit != 0xff) {
        FailText_CheckOpponentProtect(AttackMissedText, AttackMissed2Text);
    }
    // LD_HL(mUnaffectedText);
    else {
        FailText_CheckOpponentProtect(UnaffectedText, AttackMissed2Text);
    }

// got_text:
    // CALL(aFailText_CheckOpponentProtect);
    // XOR_A_A;
    // LD_addr_A(wCriticalHit);
    wram->wCriticalHit = 0;

    // LD_A(BATTLE_VARS_MOVE_EFFECT);
    // CALL(aGetBattleVar);
    // CP_A(EFFECT_JUMP_KICK);
    // RET_NZ ;

    if(GetBattleVar(BATTLE_VARS_MOVE_EFFECT) == EFFECT_JUMP_KICK) {
        // LD_A_addr(wTypeModifier);
        // AND_A(0x7f);
        // RET_Z ;
        if((wram->wTypeModifier & 0x7f) == 0)
            return;

        // LD_HL(wCurDamage);
        uint16_t dmg = BigEndianToNative16(wram->wCurDamage);
        // LD_A_hli;
        // LD_B_hl;
        // for(int rept = 0; rept < 3; rept++){
        // SRL_A;
        // RR_B;
        // }
        dmg >>= 3;
        // LD_hl_B;
        // DEC_HL;
        // LD_hli_A;
        // OR_A_B;
        // IF_NZ goto do_at_least_1_damage;
        if(dmg == 0) {
            // INC_A;
            // LD_hl_A;
            dmg = 1;
        }
        wram->wCurDamage = NativeToBigEndian16(dmg);

    // do_at_least_1_damage:
        // LD_HL(mCrashedText);
        // CALL(aStdBattleTextbox);
        StdBattleTextbox(CrashedText);
        // LD_A(0x1);
        // LD_addr_A(wBattleAnimParam);
        wram->wBattleAnimParam = 0x1;
        // CALL(aLoadMoveAnim);
        LoadMoveAnim();
        // LD_C(TRUE);
        // LDH_A_addr(hBattleTurn);
        // AND_A_A;
        // JP_NZ (mDoEnemyDamage);
        if(hram->hBattleTurn != TURN_PLAYER)
            return DoEnemyDamage(true);
        // JP(mDoPlayerDamage);
        return DoPlayerDamage(true);
    }
}

void FailText_CheckOpponentProtect(const struct TextCmd* hl, const struct TextCmd* de){
    // LD_A(BATTLE_VARS_SUBSTATUS1_OPP);
    // CALL(aGetBattleVar);
    // BIT_A(SUBSTATUS_PROTECT);
    // IF_Z goto not_protected;
    if(bit_test(GetBattleVar(BATTLE_VARS_SUBSTATUS1_OPP), SUBSTATUS_PROTECT)) {
        // LD_H_D;
        // LD_L_E;
        return StdBattleTextbox(de);
    }

// not_protected:
    // JP(mStdBattleTextbox);
    return StdBattleTextbox(hl);
}

void BattleCommand_BideFailText(void){
    PEEK("");
    // LD_A_addr(wAttackMissed);
    // AND_A_A;
    // RET_Z ;
    if(!wram->wAttackMissed)
        return;

    // LD_A_addr(wTypeModifier);
    // AND_A(0x7f);
    // JP_Z (mPrintDoesntAffect);
    // JP(mPrintButItFailed);
    if((wram->wTypeModifier & 0x7f) == 0)
        return PrintDoesntAffect();
    return PrintButItFailed();
}

void BattleCommand_CriticalText(void){
//  criticaltext
//  Prints the message for critical hits or one-hit KOs.
    PEEK("");
    static const struct TextCmd* texts[] = {
        CriticalHitText,
        OneHitKOText,
    };

//  If there is no message to be printed, wait 20 frames.
    // LD_A_addr(wCriticalHit);
    // AND_A_A;
    // IF_Z goto wait;

    if(wram->wCriticalHit) {
        // DEC_A;
        // ADD_A_A;
        // LD_HL(mBattleCommand_CriticalText_texts);
        // LD_B(0);
        // LD_C_A;
        // ADD_HL_BC;
        // LD_A_hli;
        // LD_H_hl;
        // LD_L_A;
        // CALL(aStdBattleTextbox);
        StdBattleTextbox(texts[wram->wCriticalHit - 1]);

        // XOR_A_A;
        // LD_addr_A(wCriticalHit);
        wram->wCriticalHit = 0;
    }

// wait:
    // LD_C(20);
    // JP(mDelayFrames);
    return DelayFrames(20);
}

void BattleCommand_StartLoop(void){
//  startloop
    PEEK("");
    // LD_HL(wPlayerRolloutCount);
    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // IF_Z goto ok;
    // LD_HL(wEnemyRolloutCount);
    uint8_t* hl = (hram->hBattleTurn == TURN_PLAYER)? &wram->wPlayerRolloutCount: &wram->wEnemyRolloutCount;

// ok:
    // XOR_A_A;
    // LD_hl_A;
    *hl = 0;
    // RET;

}

void BattleCommand_SuperEffectiveLoopText(void){
//  supereffectivelooptext
    PEEK("");
    // LD_A(BATTLE_VARS_SUBSTATUS3);
    // CALL(aGetBattleVarAddr);
    // BIT_A(SUBSTATUS_IN_LOOP);
    // RET_NZ ;
    if(bit_test(*GetBattleVarAddr(BATTLE_VARS_SUBSTATUS3), SUBSTATUS_IN_LOOP))
        return;

// fallthrough

    return BattleCommand_SuperEffectiveText();
}

void BattleCommand_SuperEffectiveText(void){
//  supereffectivetext
    PEEK("");
    // LD_A_addr(wTypeModifier);
    // AND_A(0x7f);
    // CP_A(EFFECTIVE);
    // RET_Z ;
    if((wram->wTypeModifier & 0x7f) == EFFECTIVE)
        return;
    // LD_HL(mSuperEffectiveText);
    // IF_NC goto print;
    else if((wram->wTypeModifier & 0x7f) > EFFECTIVE) {
        return StdBattleTextbox(SuperEffectiveText);
    }
    else {
        // LD_HL(mNotVeryEffectiveText);
        return StdBattleTextbox(NotVeryEffectiveText);
    }

// print:
    // JP(mStdBattleTextbox);
}

void BattleCommand_CheckFaint(void){
//  checkfaint
    PEEK("");
//  Faint the opponent if its HP reached zero
//   and faint the user along with it if it used Destiny Bond.
//  Ends the move effect if the opponent faints.

    // LD_HL(wEnemyMonHP);
    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // IF_Z goto got_hp;
    // LD_HL(wBattleMonHP);
    uint16_t hp = (hram->hBattleTurn == TURN_PLAYER)? wram->wEnemyMon.hp: wram->wBattleMon.hp;


// got_hp:
    // LD_A_hli;
    // OR_A_hl;
    // RET_NZ ;
    if(hp != 0)
        return;

    // LD_A(BATTLE_VARS_SUBSTATUS5_OPP);
    // CALL(aGetBattleVar);
    // BIT_A(SUBSTATUS_DESTINY_BOND);
    // IF_Z goto no_dbond;
    if(bit_test(GetBattleVar(BATTLE_VARS_SUBSTATUS5_OPP), SUBSTATUS_DESTINY_BOND)) {

        // LD_HL(mTookDownWithItText);
        // CALL(aStdBattleTextbox);
        StdBattleTextbox(TookDownWithItText);

        tile_t* bc;
        uint16_t* maxHP, *HP;
        uint8_t whichHPBar;
        // LDH_A_addr(hBattleTurn);
        // AND_A_A;
        if(hram->hBattleTurn == TURN_PLAYER) {
            // LD_HL(wEnemyMonMaxHP + 1);
            maxHP = (uint16_t*)(((uint8_t*)&wram->wEnemyMon) + offsetof(struct BattleMon, maxHP));
            HP = (uint16_t*)(((uint8_t*)&wram->wEnemyMon) + offsetof(struct BattleMon, hp));
            // bccoord(2, 2, wTilemap);  // hp bar
            bc = coord(2, 2, wram->wTilemap);
            // LD_A(0);
            whichHPBar = 0;
            // IF_NZ goto got_max_hp;
        }
        else {
            // LD_HL(wBattleMonMaxHP + 1);
            maxHP = (uint16_t*)(((uint8_t*)&wram->wBattleMon) + offsetof(struct BattleMon, maxHP));
            HP = (uint16_t*)(((uint8_t*)&wram->wBattleMon) + offsetof(struct BattleMon, hp));
            // bccoord(10, 9, wTilemap);  // hp bar
            bc = coord(10, 9, wram->wTilemap);
            // LD_A(1);
            whichHPBar = 1;
        }


    // got_max_hp:
        // LD_addr_A(wWhichHPBar);
        // LD_A_hld;
        // LD_addr_A(wHPBuffer1);
        // LD_A_hld;
        // LD_addr_A(wHPBuffer1 + 1);
        wram->wHPBuffer1 = BigEndianToNative16(*maxHP);
        // LD_A_hl;
        // LD_addr_A(wHPBuffer2);
        // XOR_A_A;
        // LD_hld_A;
        // LD_A_hl;
        // LD_addr_A(wHPBuffer2 + 1);
        // XOR_A_A;
        // LD_hl_A;
        wram->wHPBuffer2 = BigEndianToNative16(*HP);
        *HP = 0;
        // LD_addr_A(wHPBuffer3);
        // LD_addr_A(wHPBuffer3 + 1);
        wram->wHPBuffer3 = 0;
        // LD_H_B;
        // LD_L_C;
        // PREDEF(pAnimateHPBar);
        AnimateHPBar_Conv(bc, whichHPBar);
        // CALL(aRefreshBattleHuds);
        RefreshBattleHuds();

        // CALL(aBattleCommand_SwitchTurn);
        // XOR_A_A;
        BattleCommand_SwitchTurn();
        // LD_addr_A(wNumHits);
        wram->wNumHits = 0;
        // LD_addr_A(wFXAnimID + 1);
        wram->wFXAnimID &= 0xff;
        // INC_A;
        // LD_addr_A(wBattleAnimParam);
        wram->wBattleAnimParam = 1;
        // LD_A(DESTINY_BOND);
        // CALL(aLoadAnim);
        LoadAnim(DESTINY_BOND);
        // CALL(aBattleCommand_SwitchTurn);
        BattleCommand_SwitchTurn();
        // goto finish;
    }
    else {
    // no_dbond:
        // LD_A(BATTLE_VARS_MOVE_EFFECT);
        // CALL(aGetBattleVar);
        switch(GetBattleVar(BATTLE_VARS_MOVE_EFFECT)) {
            // CP_A(EFFECT_MULTI_HIT);
            // IF_Z goto multiple_hit_raise_sub;
            // CP_A(EFFECT_DOUBLE_HIT);
            // IF_Z goto multiple_hit_raise_sub;
            // CP_A(EFFECT_POISON_MULTI_HIT);
            // IF_Z goto multiple_hit_raise_sub;
            // CP_A(EFFECT_TRIPLE_KICK);
            // IF_Z goto multiple_hit_raise_sub;
            // CP_A(EFFECT_BEAT_UP);
            // IF_NZ goto finish;
            case EFFECT_MULTI_HIT:
            case EFFECT_DOUBLE_HIT:
            case EFFECT_POISON_MULTI_HIT:
            case EFFECT_TRIPLE_KICK:
            case EFFECT_BEAT_UP:
            // multiple_hit_raise_sub:
                // CALL(aBattleCommand_RaiseSub);
                BattleCommand_RaiseSub();
                break;
            
            default:
                break;
        }
    }

// finish:
    // JP(mEndMoveEffect);
    return EndMoveEffect();
}

void BattleCommand_BuildOpponentRage(void){
//  buildopponentrage
    PEEK("");
    //  Useless jump? Just inlining the code here.
    // JP(mBattleCommand_BuildOpponentRage_start);


// start:
    // LD_A_addr(wAttackMissed);
    // AND_A_A;
    // RET_NZ ;
    if(wram->wAttackMissed)
        return;

    // LD_A(BATTLE_VARS_SUBSTATUS4_OPP);
    // CALL(aGetBattleVar);
    // BIT_A(SUBSTATUS_RAGE);
    // RET_Z ;
    if(!bit_test(GetBattleVar(BATTLE_VARS_SUBSTATUS4_OPP), SUBSTATUS_RAGE))
        return;

    // LD_DE(wEnemyRageCounter);
    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // IF_Z goto player;
    // LD_DE(wPlayerRageCounter);
    uint8_t* de = (hram->hBattleTurn == TURN_PLAYER)? &wram->wEnemyRageCounter: &wram->wPlayerRageCounter;

// player:
    // LD_A_de;
    // INC_A;
    // RET_Z ;
    // LD_de_A;
    if(*de == 0xff)
        return;

    (*de)++;
    // CALL(aBattleCommand_SwitchTurn);
    BattleCommand_SwitchTurn();
    // LD_HL(mRageBuildingText);
    // CALL(aStdBattleTextbox);
    StdBattleTextbox(RageBuildingText);
    // JP(mBattleCommand_SwitchTurn);
    BattleCommand_SwitchTurn();
}

void BattleCommand_RageDamage(void){
//  ragedamage
    PEEK("");
    // LD_A_addr(wCurDamage);
    // LD_H_A;
    // LD_B_A;
    // LD_A_addr(wCurDamage + 1);
    // LD_L_A;
    // LD_C_A;
    uint16_t dmg = BigEndianToNative16(wram->wCurDamage);
    uint16_t hl = dmg;
    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // LD_A_addr(wPlayerRageCounter);
    // IF_Z goto rage_loop;
    // LD_A_addr(wEnemyRageCounter);
    uint8_t a = (hram->hBattleTurn == TURN_PLAYER)? wram->wPlayerRageCounter: wram->wEnemyRageCounter;

    while(a != 0) {
    // rage_loop:
        // AND_A_A;
        // IF_Z goto done;
        // DEC_A;
        --a;
        // ADD_HL_BC;
        uint32_t temp = hl + dmg;

        // IF_NC goto rage_loop;
        if(temp < 0xffff) {
            hl = (uint16_t)temp;
            continue;
        }
        else {
            // LD_HL(0xffff);
            hl = 0xffff;
            break;
        }
    }

// done:
    // LD_A_H;
    // LD_addr_A(wCurDamage);
    // LD_A_L;
    // LD_addr_A(wCurDamage + 1);
    wram->wCurDamage = NativeToBigEndian16(hl);
    // RET;
}

void EndMoveEffect(void){
    // LD_A_addr(wBattleScriptBufferAddress);
    // LD_L_A;
    // LD_A_addr(wBattleScriptBufferAddress + 1);
    // LD_H_A;
    uint8_t* hl = wram->wBattleScriptBuffer + wram->wBattleScriptBufferAddress;
    // LD_A(endmove_command);
    // LD_hli_A;
    hl[0] = endmove_command;
    // LD_hli_A;
    hl[1] = endmove_command;
    // LD_hl_A;
    hl[2] = endmove_command;
    // RET;
}

void DittoMetalPowder(uint8_t* b, uint8_t* c){
    // LD_A(MON_SPECIES);
    // CALL(aBattlePartyAttr);
    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // LD_A_hl;
    // IF_NZ goto got_species;
    // LD_A_addr(wTempEnemyMonSpecies);
    species_t species = (hram->hBattleTurn == TURN_PLAYER)? wram->wPartyMon[wram->wCurPartyMon].mon.species: wram->wTempEnemyMonSpecies;


// got_species:
    // CP_A(DITTO);
    // RET_NZ ;
    if(species != DITTO)
        return;

    // PUSH_BC;
    item_t item;
    // CALL(aGetOpponentItem);
    GetOpponentItem(&item);
    // LD_A_hl;
    // CP_A(METAL_POWDER);
    // POP_BC;
    // RET_NZ ;
    if(item != METAL_POWDER)
        return;

    uint8_t carry= 0;
    // LD_A_C;
    // SRL_A;
    // ADD_A_C;
    // LD_C_A;
    *c = AddCarry8((*c >> 1), *c, carry, &carry);
    // RET_NC ;

    // SRL_B;
    *b >>= 1;
    // LD_A_B;
    // AND_A_A;
    // IF_NZ goto done;
    if(*b == 0) {
        // INC_B;
        *b += 1;
    }
// done:
    // SCF;
    // RR_C;
    *c = (*c >> 1) | (1 << 7);
    // RET;
}

void BattleCommand_DamageStats(void){
//  damagestats
    PEEK("");
    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // JP_NZ (mEnemyAttackDamage);
    if(hram->hBattleTurn != TURN_PLAYER)
        return EnemyAttackDamage(&gBattleCmdState);

// fallthrough

    return PlayerAttackDamage(&gBattleCmdState);
}

void PlayerAttackDamage(struct BattleCmdState* state){
//  Return move power d, player level e, enemy defense c and player attack b.

    // CALL(aResetDamage);
    ResetDamage();

    // LD_HL(wPlayerMoveStructPower);
    // LD_A_hli;
    // AND_A_A;
    // LD_D_A;
    // RET_Z ;
    state->d = wram->wPlayerMoveStruct.power;

    if(state->d == 0)
        return;

    // LD_A_hl;
    // CP_A(SPECIAL);
    // IF_NC goto special;
    uint16_t atk, def;
    if(wram->wPlayerMoveStruct.type < SPECIAL) {
    //  physical
        // LD_HL(wEnemyMonDefense);
        // LD_A_hli;
        // LD_B_A;
        // LD_C_hl;
        def = (wram->wEnemyMon.defense[0] << 8) | wram->wEnemyMon.defense[1];

        // LD_A_addr(wEnemyScreens);
        // BIT_A(SCREENS_REFLECT);
        // IF_Z goto physicalcrit;
        if(bit_test(wram->wEnemyScreens, SCREENS_REFLECT)) {
            // SLA_C;
            // RL_B;
            def <<= 1;
        }

    // physicalcrit:
        // LD_HL(wBattleMonAttack);
        atk = (wram->wBattleMon.attack[0] << 8) | wram->wBattleMon.attack[1];
        // CALL(aCheckDamageStatsCritical);
        // IF_C goto thickclub;

        if(!CheckDamageStatsCritical()) {
            // LD_HL(wEnemyDefense);
            // LD_A_hli;
            // LD_B_A;
            // LD_C_hl;
            def = BigEndianToNative16(wram->wEnemyDefense);
            // LD_HL(wPlayerAttack);
            atk = BigEndianToNative16(wram->wPlayerAttack);
            // goto thickclub;
        }

    // thickclub:
    //  Note: Returns player attack at hl in hl.
        // CALL(aThickClubBoost);
        atk = ThickClubBoost(atk);
    }

    else {
    // special:
        // LD_HL(wEnemyMonSpclDef);
        // LD_A_hli;
        // LD_B_A;
        // LD_C_hl;
        def = (wram->wEnemyMon.spclDef[0] << 8) | wram->wEnemyMon.spclDef[1];

        // LD_A_addr(wEnemyScreens);
        // BIT_A(SCREENS_LIGHT_SCREEN);
        // IF_Z goto specialcrit;
        if(bit_test(wram->wEnemyScreens, SCREENS_LIGHT_SCREEN)) {
            // SLA_C;
            // RL_B;
            def <<= 1;
        }


    // specialcrit:
        // LD_HL(wBattleMonSpclAtk);
        atk = (wram->wBattleMon.spclAtk[0] << 8) | wram->wBattleMon.spclAtk[1];
        // CALL(aCheckDamageStatsCritical);
        // IF_C goto lightball;

        if(!CheckDamageStatsCritical()) {
            // LD_HL(wEnemySpDef);
            // LD_A_hli;
            // LD_B_A;
            // LD_C_hl;
            def = BigEndianToNative16(wram->wEnemySpDef);
            // LD_HL(wPlayerSpAtk);
            atk = BigEndianToNative16(wram->wPlayerSpAtk);
        }

    // lightball:
    //  Note: Returns player special attack at hl in hl.
        // CALL(aLightBallBoost);
        atk = LightBallBoost(atk);
        // goto done;
    }


// done:
    // CALL(aTruncateHL_BC);
    uint16_t reg = TruncateHL_BC(atk, def);
    state->b = HIGH(reg);
    state->c = LOW(reg);

    // LD_A_addr(wBattleMonLevel);
    // LD_E_A;
    state->e = wram->wBattleMon.level;
    // CALL(aDittoMetalPowder);
    DittoMetalPowder(&state->b, &state->c);

    // LD_A(1);
    // AND_A_A;
    // RET;
    state->a = 1;

}

//  Truncate 16-bit values hl and bc to 8-bit values b and c respectively.
uint16_t TruncateHL_BC(uint16_t hl, uint16_t bc){
    while(1) {
    // loop:
    //  Truncate 16-bit values hl and bc to 8-bit values b and c respectively.
    //  b = hl, c = bc

        // LD_A_H;
        // OR_A_B;
        // IF_Z goto finish;
        if(hl > 255 || bc > 255) {
            // SRL_B;
            // RR_C;
            // SRL_B;
            // RR_C;
            bc >>= 2;

            // LD_A_C;
            // OR_A_B;
            // IF_NZ goto done_bc;
            // INC_C;
            if(bc == 0) {
                bc = 1;
            }


        // done_bc:
            // SRL_H;
            // RR_L;
            // SRL_H;
            // RR_L;
            hl >>= 2;

            // LD_A_L;
            // OR_A_H;
            // IF_NZ goto finish;
            if(hl == 0) {
                // INC_L;
                hl = 1;
            }
        }

    // finish:
        // LD_A_addr(wLinkMode);
        // CP_A(LINK_COLOSSEUM);
        // IF_Z goto done;
        if(wram->wLinkMode == LINK_COLOSSEUM)
            break;
    //  If we go back to the loop point,
    //  it's the same as doing this exact
    //  same check twice.
        // LD_A_H;
        // OR_A_B;
        // IF_NZ goto loop;
        if(hl <= 255 && bc <= 255)
            break;
    }

// done:
    // LD_B_L;
    // RET;
    return (hl << 8) | ((uint8_t)bc & 0xff);
}

//  Return carry if boosted stats should be used in damage calculations.
//  Unboosted stats should be used if the attack is a critical hit,
//   and the stage of the opponent's defense is higher than the user's attack.
bool CheckDamageStatsCritical(void){
    // LD_A_addr(wCriticalHit);
    // AND_A_A;
    // SCF;
    // RET_Z ;
    if(!wram->wCriticalHit)
        return true;

    // PUSH_HL;
    // PUSH_BC;
    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // IF_NZ goto enemy;

    uint8_t a, b;
    if(hram->hBattleTurn == TURN_PLAYER) {
        // LD_A_addr(wPlayerMoveStructType);
        // CP_A(SPECIAL);
    //  special
        if(wram->wPlayerMoveStruct.type >= SPECIAL) {
            // LD_A_addr(wPlayerSAtkLevel);
            // LD_B_A;
            // LD_A_addr(wEnemySDefLevel);
            // IF_NC goto end;
            a = wram->wPlayerSAtkLevel;
            b = wram->wEnemySDefLevel;
        }
    //  physical
        else {
            // LD_A_addr(wPlayerAtkLevel);
            // LD_B_A;
            // LD_A_addr(wEnemyDefLevel);
            // goto end;
            a = wram->wPlayerAtkLevel;
            b = wram->wEnemyDefLevel;
        }
    }
    else {
    // enemy:
        // LD_A_addr(wEnemyMoveStructType);
        // CP_A(SPECIAL);
    //  special
        if(wram->wEnemyMoveStruct.type >= SPECIAL) {
            // LD_A_addr(wEnemySAtkLevel);
            // LD_B_A;
            // LD_A_addr(wPlayerSDefLevel);
            // IF_NC goto end;
            a = wram->wEnemySAtkLevel;
            b = wram->wPlayerSDefLevel;
        }
    //  physical
        else {
            // LD_A_addr(wEnemyAtkLevel);
            // LD_B_A;
            // LD_A_addr(wPlayerDefLevel);
            a = wram->wEnemyAtkLevel;
            b = wram->wPlayerDefLevel;
        }
    }
// end:
    // CP_A_B;
    // POP_BC;
    // POP_HL;
    // RET;
    return a < b;
}

//  Return in hl the stat value at hl.
uint16_t ThickClubBoost(uint16_t atk){
//  If the attacking monster is Cubone or Marowak and
//  it's holding a Thick Club, double it.
    // PUSH_BC;
    // PUSH_DE;
    // LD_B(CUBONE);
    // LD_C(MAROWAK);
    // LD_D(THICK_CLUB);
    // CALL(aSpeciesItemBoost);
    // POP_DE;
    // POP_BC;
    // RET;
    return SpeciesItemBoost(atk, CUBONE, MAROWAK, THICK_CLUB);
}

//  Return in hl the stat value at hl.
uint16_t LightBallBoost(uint16_t spatk){
//  If the attacking monster is Pikachu and it's
//  holding a Light Ball, double it.
    // PUSH_BC;
    // PUSH_DE;
    // LD_B(PIKACHU);
    // LD_C(PIKACHU);
    // LD_D(LIGHT_BALL);
    // CALL(aSpeciesItemBoost);
    // POP_DE;
    // POP_BC;
    // RET;
    return SpeciesItemBoost(spatk, PIKACHU, PIKACHU, LIGHT_BALL);
}

uint16_t SpeciesItemBoost(uint16_t hl, species_t b, species_t c, item_t d){
//  Return in hl the stat value at hl.

//  If the attacking monster is species b or c and
//  it's holding item d, double it.

    // LD_A_hli;
    // LD_L_hl;
    // LD_H_A;

    // PUSH_HL;
    // LD_A(MON_SPECIES);
    // CALL(aBattlePartyAttr);
    struct PartyMon* mon = wram->wPartyMon + wram->wCurPartyMon;

    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // LD_A_hl;
    // IF_Z goto CompareSpecies;
    // LD_A_addr(wTempEnemyMonSpecies);
    species_t a = (hram->hBattleTurn == TURN_PLAYER)? mon->mon.species: wram->wTempEnemyMonSpecies;

// CompareSpecies:
    // POP_HL;

    // CP_A_B;
    // IF_Z goto GetItemHeldEffect;
    // CP_A_C;
    // RET_NZ ;
    if(a == b || a == c) {
    // GetItemHeldEffect:
        // PUSH_HL;
        // CALL(aGetUserItem);
        item_t tmp;
        GetUserItem(&tmp);
        // LD_A_hl;
        // POP_HL;
        // CP_A_D;
        // RET_NZ ;
        if(tmp != d)
            return hl;

    //  Double the stat
        // SLA_L;
        // RL_H;
        // RET;
        return hl << 1;
    }
    return hl;
}

void EnemyAttackDamage(struct BattleCmdState* state){
    // CALL(aResetDamage);
    ResetDamage();

//  No damage dealt with 0 power.
    // LD_HL(wEnemyMoveStructPower);
    // LD_A_hli;  // hl = wEnemyMoveStructType
    // LD_D_A;
    state->d = wram->wEnemyMoveStruct.power;
    // AND_A_A;
    // RET_Z ;
    if(state->d == 0)
        return;

    // LD_A_hl;
    // CP_A(SPECIAL);
    // IF_NC goto special;
    uint16_t def, atk;
    if(wram->wEnemyMoveStruct.type < SPECIAL) {
    //  physical
        // LD_HL(wBattleMonDefense);
        // LD_A_hli;
        // LD_B_A;
        // LD_C_hl;
        def = (wram->wBattleMon.defense[0] << 8) | (wram->wBattleMon.defense[1]);

        // LD_A_addr(wPlayerScreens);
        // BIT_A(SCREENS_REFLECT);
        // IF_Z goto physicalcrit;
        // SLA_C;
        // RL_B;
        if(bit_test(wram->wPlayerScreens, SCREENS_REFLECT))
            def <<= 1;


    // physicalcrit:
        // LD_HL(wEnemyMonAttack);
        atk = (wram->wEnemyMon.attack[0] << 8) | wram->wEnemyMon.attack[1];
        // CALL(aCheckDamageStatsCritical);
        // IF_C goto thickclub;

        if(!CheckDamageStatsCritical()) {
            // LD_HL(wPlayerDefense);
            // LD_A_hli;
            // LD_B_A;
            // LD_C_hl;
            def = BigEndianToNative16(wram->wPlayerDefense);
            // LD_HL(wEnemyAttack);
            atk = BigEndianToNative16(wram->wEnemyAttack);
            // goto thickclub;
        }
    // thickclub:
        // CALL(aThickClubBoost);
        atk = ThickClubBoost(atk);
    }
    else {
    // special:
        // LD_HL(wBattleMonSpclDef);
        // LD_A_hli;
        // LD_B_A;
        // LD_C_hl;
        def = (wram->wBattleMon.spclDef[0] << 8) | (wram->wBattleMon.spclDef[1]);

        // LD_A_addr(wPlayerScreens);
        // BIT_A(SCREENS_LIGHT_SCREEN);
        // IF_Z goto specialcrit;
        // SLA_C;
        // RL_B;
        if(bit_test(wram->wPlayerScreens, SCREENS_LIGHT_SCREEN))
            def <<= 1;

    // specialcrit:
        // LD_HL(wEnemyMonSpclAtk);
        atk = (wram->wEnemyMon.spclAtk[0] << 8) | (wram->wEnemyMon.spclAtk[1]);
        // CALL(aCheckDamageStatsCritical);
        // IF_C goto lightball;
        if(!CheckDamageStatsCritical()) {
            // LD_HL(wPlayerSpDef);
            // LD_A_hli;
            // LD_B_A;
            // LD_C_hl;
            def = BigEndianToNative16(wram->wPlayerSpDef);
            // LD_HL(wEnemySpAtk);
            atk = BigEndianToNative16(wram->wEnemySpAtk);
        }

    // lightball:
        // CALL(aLightBallBoost);
        atk = LightBallBoost(atk);
        // goto done;
    }


// done:
    // CALL(aTruncateHL_BC);
    uint16_t reg = TruncateHL_BC(atk, def);
    state->b = HIGH(reg);
    state->c = LOW(reg);

    // LD_A_addr(wEnemyMonLevel);
    // LD_E_A;
    state->e = wram->wEnemyMon.level;
    // CALL(aDittoMetalPowder);
    DittoMetalPowder(&state->b, &state->c);

    // LD_A(1);
    // AND_A_A;
    // RET;
    state->a = 1;

// INCLUDE "engine/battle/move_effects/beat_up.asm"

}

void BattleCommand_ClearMissDamage(void){
//  clearmissdamage
    PEEK("");
    // LD_A_addr(wAttackMissed);
    // AND_A_A;
    // RET_Z ;
    if(wram->wAttackMissed) {
        // JP(mResetDamage);
        return ResetDamage();
    }
}

void HitSelfInConfusion(struct BattleCmdState* state){
    // CALL(aResetDamage);
    ResetDamage();
    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // LD_HL(wBattleMonDefense);
    // LD_DE(wPlayerScreens);
    // LD_A_addr(wBattleMonLevel);
    // IF_Z goto got_it;

    // LD_HL(wEnemyMonDefense);
    struct BattleMon* hl = (hram->hBattleTurn == TURN_PLAYER)? &wram->wBattleMon: &wram->wEnemyMon;
    // LD_DE(wEnemyScreens);
    uint8_t* de = (hram->hBattleTurn == TURN_PLAYER)? &wram->wPlayerScreens: &wram->wEnemyScreens;
    // LD_A_addr(wEnemyMonLevel);

// got_it:
    // PUSH_AF;
    uint16_t def = (hl->defense[0] << 8) | hl->defense[1];
    // LD_A_hli;
    // LD_B_A;
    // LD_C_hl;
    // LD_A_de;
    // BIT_A(SCREENS_REFLECT);
    // IF_Z goto mimic_screen;
    if(bit_test(*de, SCREENS_REFLECT)) {
        // SLA_C;
        // RL_B;
        def <<= 1;
    }

// mimic_screen:
    // DEC_HL;
    // DEC_HL;
    // DEC_HL;
    // LD_A_hli;
    // LD_L_hl;
    // LD_H_A;
    uint16_t atk = (hl->attack[0] << 8) | hl->attack[1];
    // CALL(aTruncateHL_BC);
    uint16_t reg = TruncateHL_BC(atk, def);
    state->b = HIGH(reg);
    state->c = LOW(reg);

    // LD_D(40);
    state->d = 40;
    // POP_AF;
    // LD_E_A;
    state->e = hl->level;
    // RET;
}

void BattleCommand_DamageCalc(void){
//  damagecalc
    PEEK("");
//  Return a damage value for move power d, player level e, enemy defense c and player attack b.

//  Return 1 if successful, else 0.

    uint8_t pwr = gBattleCmdState.d;
    uint8_t lvl = gBattleCmdState.e;
    uint8_t def = gBattleCmdState.c;
    uint8_t atk = gBattleCmdState.b;

    gBattleCmdState.a = DamageCalc(pwr, lvl, def, atk);
    printf("Calculated %d damage. (pwr=%d, lvl=%d, def=%d, atk=%d)\n", BigEndianToNative16(wram->wCurDamage),
        pwr, lvl, def, atk);
}

static void DamageCalc_CriticalMultiplier(uint32_t* n) {
    // LD_A_addr(wCriticalHit);
    // AND_A_A;
    // RET_Z ;
    if(!wram->wCriticalHit)
        return;

//  x2
    // LDH_A_addr(hQuotient + 3);
    // ADD_A_A;
    // LDH_addr_A(hQuotient + 3);

    // LDH_A_addr(hQuotient + 2);
    // RL_A;
    // LDH_addr_A(hQuotient + 2);

    *n *= 2;

//  Cap at $ffff.
    // RET_NC ;

    if(*n > 0xffffu) {
        // LD_A(0xff);
        // LDH_addr_A(hQuotient + 2);
        // LDH_addr_A(hQuotient + 3);
        *n = 0xffff;
    }
    // RET;
}

uint8_t DamageCalc(uint8_t pwr, uint8_t lvl, uint8_t def, uint8_t atk) {
    // LD_A(BATTLE_VARS_MOVE_EFFECT);
    // CALL(aGetBattleVar);
    uint8_t effect = GetBattleVar(BATTLE_VARS_MOVE_EFFECT);

//  Selfdestruct and Explosion halve defense.
    // CP_A(EFFECT_SELFDESTRUCT);
    // IF_NZ goto dont_selfdestruct;

    if(effect == EFFECT_SELFDESTRUCT) {
        // SRL_C;
        def >>= 1;
        // IF_NZ goto dont_selfdestruct;
        // INC_C;
        if(def == 0) def = 1;
    }

// dont_selfdestruct:

//  Variable-hit moves and Conversion can have a power of 0.
    // CP_A(EFFECT_MULTI_HIT);
    // IF_Z goto skip_zero_damage_check;

    // CP_A(EFFECT_CONVERSION);
    // IF_Z goto skip_zero_damage_check;

    if(effect != EFFECT_MULTI_HIT && effect != EFFECT_CONVERSION) {
    //  No damage if move power is 0.
        // LD_A_D;
        // AND_A_A;
        // RET_Z ;
        if(pwr == 0)
            return 0;
    }

// skip_zero_damage_check:
//  Minimum defense value is 1.
    // LD_A_C;
    // AND_A_A;
    // IF_NZ goto not_dividing_by_zero;
    // LD_C(1);
    if(def == 0) {
        def = 1;
    }

// not_dividing_by_zero:

    // XOR_A_A;
    // LD_HL(hDividend);
    // LD_hli_A;
    // LD_hli_A;
    // LD_hl_A;

//  Level * 2
    // LD_A_E;
    // ADD_A_A;
    // IF_NC goto level_not_overflowing;
    // LD_hl(1);

// level_not_overflowing:
    // INC_HL;
    // LD_hli_A;
    uint32_t n = lvl * 2;

//  / 5
    // LD_A(5);
    // LD_hld_A;
    // PUSH_BC;
    // LD_B(4);
    // CALL(aDivide);
    // POP_BC;
    n /= 5;

//  + 2
    // INC_hl;
    // INC_hl;
    n += 2;

//  * bp
    // INC_HL;
    // LD_hl_D;
    // CALL(aMultiply);
    n *= pwr;

//  * Attack
    // LD_hl_B;
    // CALL(aMultiply);
    n *= atk;

//  / Defense
    // LD_hl_C;
    // LD_B(4);
    // CALL(aDivide);
    n /= def;

//  / 50
    // LD_hl(50);
    // LD_B(0x4);
    // CALL(aDivide);
    n /= 50;

//  Item boosts
    // CALL(aGetUserItem);
    uint16_t item_effect = GetUserItem(NULL);

    // LD_A_B;
    // AND_A_A;
    // IF_Z goto DoneItem;
    if(item_effect != 0) 
    {
        // LD_HL(mTypeBoostItems);
        const uint8_t* hl = TypeBoostItems;
        uint8_t a;
        uint8_t a2;

        do {
        // NextItem:
            // LD_A_hli;
            a = *(hl++);
            // CP_A(-1);
            // IF_Z goto DoneItem;
            if(a == 0xff)
                goto DoneItem;

        //  Item effect
            // CP_A_B;
            // LD_A_hli;
            a2 = *(hl++);
            // IF_NZ goto NextItem;
        } while(a != HIGH(item_effect));

    //  Type
        // LD_B_A;
        // LD_A(BATTLE_VARS_MOVE_TYPE);
        // CALL(aGetBattleVar);
        // CP_A_B;
        // IF_NZ goto DoneItem;
        if(a2 == GetBattleVar(BATTLE_VARS_MOVE_TYPE)) {
        //  * 100 + item effect amount
            // LD_A_C;
            // ADD_A(100);
            // LDH_addr_A(hMultiplier);
            // CALL(aMultiply);
            n *= 100 + LOW(item_effect);

        //  / 100
            // LD_A(100);
            // LDH_addr_A(hDivisor);
            // LD_B(4);
            // CALL(aDivide);
            n /= 100;
        }
    }

DoneItem:
//  Critical hits
    // CALL(aBattleCommand_DamageCalc_CriticalMultiplier);
    DamageCalc_CriticalMultiplier(&n);

//  Update wCurDamage. Max 999 (capped at 997, then add 2).
#define MAX_DAMAGE (999)
#define MIN_DAMAGE (2)
#define DAMAGE_CAP (MAX_DAMAGE - MIN_DAMAGE)

    // LD_HL(wCurDamage);
    // LD_B_hl;
    // LDH_A_addr(hQuotient + 3);
    // ADD_A_B;
    // LDH_addr_A(hQuotient + 3);
    // IF_NC goto dont_cap_1;

    // LDH_A_addr(hQuotient + 2);
    // INC_A;
    // LDH_addr_A(hQuotient + 2);
    // AND_A_A;
    // IF_Z goto Cap;


// dont_cap_1:
    // LDH_A_addr(hQuotient);
    // LD_B_A;
    // LDH_A_addr(hQuotient + 1);
    // OR_A_A;
    // IF_NZ goto Cap;

    // LDH_A_addr(hQuotient + 2);
    // CP_A(HIGH(DAMAGE_CAP + 1));
    // IF_C goto dont_cap_2;

    // CP_A(HIGH(DAMAGE_CAP + 1) + 1);
    // IF_NC goto Cap;

    // LDH_A_addr(hQuotient + 3);
    // CP_A(LOW(DAMAGE_CAP + 1));
    // IF_NC goto Cap;


// dont_cap_2:
    // INC_HL;

    // LDH_A_addr(hQuotient + 3);
    // LD_B_hl;
    // ADD_A_B;
    // LD_hld_A;

    // LDH_A_addr(hQuotient + 2);
    // LD_B_hl;
    // ADC_A_B;
    // LD_hl_A;
    // IF_C goto Cap;

    // LD_A_hl;
    // CP_A(HIGH(DAMAGE_CAP + 1));
    // IF_C goto dont_cap_3;

    // CP_A(HIGH(DAMAGE_CAP + 1) + 1);
    // IF_NC goto Cap;

    // INC_HL;
    // LD_A_hld;
    // CP_A(LOW(DAMAGE_CAP + 1));
    // IF_C goto dont_cap_3;
    uint16_t dmg = BigEndianToNative16(wram->wCurDamage);
    if(n + dmg >= DAMAGE_CAP) {
    // Cap:
        // LD_A(HIGH(DAMAGE_CAP));
        // LD_hli_A;
        // LD_A(LOW(DAMAGE_CAP));
        // LD_hld_A;
        wram->wCurDamage = NativeToBigEndian16(DAMAGE_CAP);
    }
    else {
        wram->wCurDamage = NativeToBigEndian16(dmg + n + MIN_DAMAGE);
    }


// dont_cap_3:
//  Add back MIN_DAMAGE (capping at 999).
    // INC_HL;
    // LD_A_hl;
    // ADD_A(MIN_DAMAGE);
    // LD_hld_A;
    // IF_NC goto dont_floor;
    // INC_hl;

dont_floor:

//  Returns nz and nc.
    // LD_A(1);
    // AND_A_A;
    // RET;
    return 1;

// INCLUDE "data/types/type_boost_items.asm"
}

void BattleCommand_ConstantDamage(void){
//  constantdamage
    PEEK("");
    // LD_HL(wBattleMonLevel);
    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // IF_Z goto got_turn;
    // LD_HL(wEnemyMonLevel);
    uint8_t b = (hram->hBattleTurn == TURN_PLAYER)? wram->wBattleMon.level: wram->wEnemyMon.level;
    uint8_t a = 0;


// got_turn:
    // LD_A(BATTLE_VARS_MOVE_EFFECT);
    // CALL(aGetBattleVar);
    // CP_A(EFFECT_LEVEL_DAMAGE);
    // LD_B_hl;
    // LD_A(0);
    // IF_Z goto got_power;
    if(GetBattleVar(BATTLE_VARS_MOVE_EFFECT) == EFFECT_LEVEL_DAMAGE) {
    // got_power:
        // LD_HL(wCurDamage);
        // LD_hli_A;
        // LD_hl_B;
        wram->wCurDamage = NativeToBigEndian16(b);
        // RET;
        return;
    }

    // LD_A(BATTLE_VARS_MOVE_EFFECT);
    // CALL(aGetBattleVar);
    uint8_t effect = GetBattleVar(BATTLE_VARS_MOVE_EFFECT);

    switch(effect) {
        // CP_A(EFFECT_PSYWAVE);
        // IF_Z goto psywave;
        case EFFECT_PSYWAVE:
        // psywave:
            // LD_A_B;
            // SRL_A;
            // ADD_A_B;
            // LD_B_A;
            b = (b >> 1) + b;

            do {
            // psywave_loop:
                // CALL(aBattleRandom);
                a = v_BattleRandom_Conv();
                // AND_A_A;
                // IF_Z goto psywave_loop;
                // CP_A_B;
                // IF_NC goto psywave_loop;
            } while(a == 0 || a >= b);
            // LD_B_A;
            // LD_A(0);
            // goto got_power;
        // got_power:
            // LD_HL(wCurDamage);
            // LD_hli_A;
            // LD_hl_B;
            wram->wCurDamage = NativeToBigEndian16(b);
            // RET;
            return;

        // CP_A(EFFECT_SUPER_FANG);
        // IF_Z goto super_fang;
        case EFFECT_SUPER_FANG: {
        // super_fang:
            // LD_HL(wEnemyMonHP);
            // LDH_A_addr(hBattleTurn);
            // AND_A_A;
            // IF_Z goto got_hp;
            // LD_HL(wBattleMonHP);
            uint16_t hp = (hram->hBattleTurn == TURN_PLAYER)
                ? BigEndianToNative16(wram->wEnemyMon.hp)
                : BigEndianToNative16(wram->wBattleMon.hp);

        // got_hp:
            // LD_A_hli;
            // SRL_A;
            // LD_B_A;
            // LD_A_hl;
            // RR_A;
            // PUSH_AF;
            // LD_A_B;
            // POP_BC;
            // AND_A_A;
            // IF_NZ goto got_power;
            hp >>= 1;
            if(hp == 0) {
                // OR_A_B;
                // LD_A(0);
                // IF_NZ goto got_power;
                // LD_B(1);
                hp = 1;
            }
        // got_power:
            // LD_HL(wCurDamage);
            // LD_hli_A;
            // LD_hl_B;
            wram->wCurDamage = NativeToBigEndian16(hp);
            // RET;
            return;
        }

        // CP_A(EFFECT_REVERSAL);
        // IF_Z goto reversal;
        case EFFECT_REVERSAL: {
        // reversal:
            // LD_HL(wBattleMonHP);
            // LDH_A_addr(hBattleTurn);
            // AND_A_A;
            // IF_Z goto reversal_got_hp;
            // LD_HL(wEnemyMonHP);
            uint16_t hp = (hram->hBattleTurn == TURN_PLAYER)
                ? BigEndianToNative16(wram->wBattleMon.hp)
                : BigEndianToNative16(wram->wEnemyMon.hp);
            uint16_t maxHP = (hram->hBattleTurn == TURN_PLAYER)
                ? BigEndianToNative16(wram->wBattleMon.maxHP)
                : BigEndianToNative16(wram->wEnemyMon.maxHP);

        // reversal_got_hp:
            // XOR_A_A;
            // LDH_addr_A(hDividend);
            // LDH_addr_A(hMultiplicand + 0);
            // LD_A_hli;
            // LDH_addr_A(hMultiplicand + 1);
            // LD_A_hli;
            // LDH_addr_A(hMultiplicand + 2);
            // LD_A(48);
            // LDH_addr_A(hMultiplier);
            // CALL(aMultiply);
            uint32_t n = hp * 48;
            // LD_A_hli;
            // LD_B_A;
            // LD_A_hl;
            // LDH_addr_A(hDivisor);
            // LD_A_B;
            // AND_A_A;
            // IF_Z goto skip_to_divide;
            if(HIGH(maxHP) != 0) {
                // LDH_A_addr(hProduct + 4);
                // SRL_B;
                // RR_A;
                // SRL_B;
                // RR_A;
                // LDH_addr_A(hDivisor);
                // LDH_A_addr(hProduct + 2);
                // LD_B_A;
                // SRL_B;
                // LDH_A_addr(hProduct + 3);
                // RR_A;
                // SRL_B;
                // RR_A;
                // LDH_addr_A(hDividend + 3);
                // LD_A_B;
                // LDH_addr_A(hDividend + 2);
                maxHP >>= 2;
                n >>= 2;
            }

        // skip_to_divide:
            // LD_B(4);
            // CALL(aDivide);
            n = n / maxHP;
            // LDH_A_addr(hQuotient + 3);
            // LD_B_A;
            b = LOW(n);
            // LD_HL(mFlailReversalPower);
            const uint8_t* hl = FlailReversalPower;

            while(a = *(hl++), a < b) {
            // reversal_loop:
                // LD_A_hli;
                // CP_A_B;
                // IF_NC goto break_loop;
                // INC_HL;
                hl++;
                // goto reversal_loop;
            }


        // break_loop:
            // LDH_A_addr(hBattleTurn);
            // AND_A_A;
            // LD_A_hl;
            // IF_NZ goto notPlayersTurn;

            a = *hl;
            uint8_t* hl2;
            if(hram->hBattleTurn == TURN_PLAYER) {
                // LD_HL(wPlayerMoveStructPower);
                hl2 = &wram->wPlayerMoveStruct.power;
                // LD_hl_A;
                *hl2 = a;
                // PUSH_HL;
                // CALL(aPlayerAttackDamage);
                PlayerAttackDamage(&gBattleCmdState);
            }
            // goto notEnemysTurn;

            else {
            // notPlayersTurn:
                // LD_HL(wEnemyMoveStructPower);
                hl2 = &wram->wEnemyMoveStruct.power;
                // LD_hl_A;
                *hl2 = a;
                // PUSH_HL;
                // CALL(aEnemyAttackDamage);
                EnemyAttackDamage(&gBattleCmdState);
            }


        // notEnemysTurn:
            // CALL(aBattleCommand_DamageCalc);
            BattleCommand_DamageCalc();
            // POP_HL;
            // LD_hl(1);
            *hl2 = 1;
            // RET;
            return;
        }

        default:
            // LD_A(BATTLE_VARS_MOVE_POWER);
            // CALL(aGetBattleVar);
            // LD_B_A;
            // LD_A(0x0);
            // goto got_power;
        // got_power:
            // LD_HL(wCurDamage);
            // LD_hli_A;
            // LD_hl_B;
            wram->wCurDamage = NativeToBigEndian16(GetBattleVar(BATTLE_VARS_MOVE_POWER));
            // RET;
            return;
    }


// got_power:
    // LD_HL(wCurDamage);
    // LD_hli_A;
    // LD_hl_B;
    // RET;

// INCLUDE "data/moves/flail_reversal_power.asm"

// INCLUDE "engine/battle/move_effects/counter.asm"

// INCLUDE "engine/battle/move_effects/encore.asm"

// INCLUDE "engine/battle/move_effects/pain_split.asm"

// INCLUDE "engine/battle/move_effects/snore.asm"

// INCLUDE "engine/battle/move_effects/conversion2.asm"

// INCLUDE "engine/battle/move_effects/lock_on.asm"

// INCLUDE "engine/battle/move_effects/sketch.asm"

}

void BattleCommand_DefrostOpponent(void){
//  defrostopponent
    PEEK("");
//  Thaw the opponent if frozen, and
//  raise the user's Attack one stage.

    // CALL(aAnimateCurrentMove);
    AnimateCurrentMove();

    // LD_A(BATTLE_VARS_STATUS_OPP);
    // CALL(aGetBattleVarAddr);
    // CALL(aDefrost);
    Defrost(GetBattleVarAddr(BATTLE_VARS_STATUS_OPP));

    // LD_A(BATTLE_VARS_MOVE_EFFECT);
    // CALL(aGetBattleVarAddr);
    uint8_t* effect_ptr = GetBattleVarAddr(BATTLE_VARS_MOVE_EFFECT);
    // LD_A_hl;
    // PUSH_HL;
    // PUSH_AF;
    uint8_t effect = *effect_ptr;

    // LD_A(EFFECT_ATTACK_UP);
    // LD_hl_A;
    *effect_ptr = EFFECT_ATTACK_UP;
    // CALL(aBattleCommand_StatUp);
    BattleCommand_StatUp();

    // POP_AF;
    // POP_HL;
    // LD_hl_A;
    *effect_ptr = effect;
    // RET;

// INCLUDE "engine/battle/move_effects/sleep_talk.asm"

// INCLUDE "engine/battle/move_effects/destiny_bond.asm"

// INCLUDE "engine/battle/move_effects/spite.asm"

// INCLUDE "engine/battle/move_effects/false_swipe.asm"

// INCLUDE "engine/battle/move_effects/heal_bell.asm"

}

void FarPlayBattleAnimation(uint16_t de){
//  play animation de
    // LD_A(BATTLE_VARS_SUBSTATUS3);
    // CALL(aGetBattleVar);
    // AND_A(1 << SUBSTATUS_FLYING | 1 << SUBSTATUS_UNDERGROUND);
    // RET_NZ ;

// fallthrough
    if(GetBattleVar(BATTLE_VARS_SUBSTATUS3) & ((1 << SUBSTATUS_FLYING) | (1 << SUBSTATUS_UNDERGROUND)))
        return;
    return PlayFXAnimID(de);
}

void PlayFXAnimID(uint16_t de){
    // LD_A_E;
    // LD_addr_A(wFXAnimID);
    // LD_A_D;
    // LD_addr_A(wFXAnimID + 1);
    wram->wFXAnimID = de;

    // LD_C(3);
    // CALL(aDelayFrames);
    DelayFrames(3);
    // CALLFAR(aPlayBattleAnim);
    PlayBattleAnim();
    // RET;
}

void DoEnemyDamage(bool ignoreSub){
    // LD_HL(wCurDamage);
    uint16_t dmg = BigEndianToNative16(wram->wCurDamage);
    // LD_A_hli;
    // LD_B_A;
    // LD_A_hl;
    // OR_A_B;
    // IF_Z goto did_no_damage;
    if(dmg != 0) {
        // LD_A_C;
        // AND_A_A;
        // IF_NZ goto ignore_substitute;
        if(!ignoreSub && bit_test(wram->wEnemySubStatus4, SUBSTATUS_SUBSTITUTE)) {
            // LD_A_addr(wEnemySubStatus4);
            // BIT_A(SUBSTATUS_SUBSTITUTE);
            // JP_NZ (mDoSubstituteDamage);
            return DoSubstituteDamage();
        }

    // ignore_substitute:
    // Subtract wCurDamage from wEnemyMonHP.
    //  store original HP in little endian wHPBuffer2
        wram->wHPBuffer2 = BigEndianToNative16(wram->wEnemyMon.hp);
        // LD_A_hld;
        // LD_B_A;
        // LD_A_addr(wEnemyMonHP + 1);
        // LD_addr_A(wHPBuffer2);
        // SUB_A_B;
        // LD_addr_A(wEnemyMonHP + 1);
        // LD_A_hl;
        // LD_B_A;
        // LD_A_addr(wEnemyMonHP);
        // LD_addr_A(wHPBuffer2 + 1);
        // SBC_A_B;
        // LD_addr_A(wEnemyMonHP);
        uint16_t hp = wram->wHPBuffer2 - dmg;
        wram->wEnemyMon.hp = NativeToBigEndian16(hp);
    #if defined(_DEBUG) && !defined(_MSC_VER)
        // PUSH_AF;
        // LD_A(MBANK(asSkipBattle));
        // CALL(aOpenSRAM);
        OpenSRAM(MBANK(asSkipBattle));
        // LD_A_addr(sSkipBattle);
        uint8_t skipBattle = gb_read(sSkipBattle);
        // CALL(aCloseSRAM);
        CloseSRAM();
        // OR_A_A;
    // If [sSkipBattle] is nonzero, skip the "jr nc, .no_underflow" check,
    // so any attack deals maximum damage to the enemy.
        // IF_NZ goto debug_skip;
        if(skipBattle != 0 || wram->wHPBuffer2 < dmg)
        // POP_AF;
        // IF_NC goto no_underflow;
        // PUSH_AF;

    // debug_skip:
        // POP_AF;
    #else
        // IF_NC goto no_underflow;
        if(wram->wHPBuffer2 < dmg)
    #endif
        {
            // LD_A_addr(wHPBuffer2 + 1);
            // LD_hli_A;
            // LD_A_addr(wHPBuffer2);
            // LD_hl_A;
            wram->wCurDamage = NativeToBigEndian16(wram->wHPBuffer2);
            // XOR_A_A;
            // LD_HL(wEnemyMonHP);
            // LD_hli_A;
            // LD_hl_A;
            wram->wEnemyMon.hp = 0;
        }

    // no_underflow:
        // LD_HL(wEnemyMonMaxHP);
        // LD_A_hli;
        // LD_addr_A(wHPBuffer1 + 1);
        // LD_A_hl;
        // LD_addr_A(wHPBuffer1);
        wram->wHPBuffer1 = BigEndianToNative16(wram->wEnemyMon.maxHP);
        // LD_HL(wEnemyMonHP);
        // LD_A_hli;
        // LD_addr_A(wHPBuffer3 + 1);
        // LD_A_hl;
        // LD_addr_A(wHPBuffer3);
        wram->wHPBuffer3 = BigEndianToNative16(wram->wEnemyMon.hp);

        // hlcoord(2, 2, wTilemap);
        // XOR_A_A;
        // LD_addr_A(wWhichHPBar);
        // PREDEF(pAnimateHPBar);
        AnimateHPBar_Conv(coord(2, 2, wram->wTilemap), 0);
    }

// did_no_damage:
    // JP(mRefreshBattleHuds);
    return RefreshBattleHuds();
}

void DoPlayerDamage(bool ignoreSub){
    // LD_HL(wCurDamage);
    uint16_t dmg = BigEndianToNative16(wram->wCurDamage);
    // LD_A_hli;
    // LD_B_A;
    // LD_A_hl;
    // OR_A_B;
    // IF_Z goto did_no_damage;
    if(dmg != 0) {
        // LD_A_C;
        // AND_A_A;
        // IF_NZ goto ignore_substitute;
        // LD_A_addr(wPlayerSubStatus4);
        // BIT_A(SUBSTATUS_SUBSTITUTE);
        if(!ignoreSub && bit_test(wram->wPlayerSubStatus4, SUBSTATUS_SUBSTITUTE)) {
            // JP_NZ (mDoSubstituteDamage);
            return DoSubstituteDamage();
        }

    // ignore_substitute:
    // Subtract wCurDamage from wBattleMonHP.
    //  store original HP in little endian wHPBuffer2
    //  store new HP in little endian wHPBuffer3
        wram->wHPBuffer2 = BigEndianToNative16(wram->wBattleMon.hp);
        // LD_A_hld;
        // LD_B_A;
        // LD_A_addr(wBattleMonHP + 1);
        // LD_addr_A(wHPBuffer2);
        // SUB_A_B;
        // LD_addr_A(wBattleMonHP + 1);
        // LD_addr_A(wHPBuffer3);
        // LD_B_hl;
        // LD_A_addr(wBattleMonHP);
        // LD_addr_A(wHPBuffer2 + 1);
        // SBC_A_B;
        wram->wHPBuffer3 = wram->wHPBuffer2 - dmg;
        wram->wBattleMon.hp = NativeToBigEndian16(wram->wHPBuffer3);
        // LD_addr_A(wBattleMonHP);
        // LD_addr_A(wHPBuffer3 + 1);
        // IF_NC goto no_underflow;
        if(wram->wHPBuffer2 < dmg) {
            // LD_A_addr(wHPBuffer2 + 1);
            // LD_hli_A;
            // LD_A_addr(wHPBuffer2);
            // LD_hl_A;
            wram->wCurDamage = NativeToBigEndian16(wram->wHPBuffer2);
            // XOR_A_A;
            // LD_HL(wBattleMonHP);
            // LD_hli_A;
            // LD_hl_A;
            wram->wBattleMon.hp = 0;
            // LD_HL(wHPBuffer3);
            // LD_hli_A;
            // LD_hl_A;
            wram->wHPBuffer3 = 0;
        }

    // no_underflow:
        // LD_HL(wBattleMonMaxHP);
        // LD_A_hli;
        // LD_addr_A(wHPBuffer1 + 1);
        // LD_A_hl;
        // LD_addr_A(wHPBuffer1);
        wram->wHPBuffer1 = BigEndianToNative16(wram->wBattleMon.maxHP);

        // hlcoord(10, 9, wTilemap);
        // LD_A(1);
        // LD_addr_A(wWhichHPBar);
        // PREDEF(pAnimateHPBar);
        AnimateHPBar_Conv(coord(10, 9, wram->wTilemap), 1);
    }

// did_no_damage:
    // JP(mRefreshBattleHuds);
    return RefreshBattleHuds();
}

void DoSubstituteDamage(void){
    // LD_HL(mSubTookDamageText);
    // CALL(aStdBattleTextbox);
    StdBattleTextbox(SubTookDamageText);

    // LD_DE(wEnemySubstituteHP);
    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // IF_Z goto got_hp;
    // LD_DE(wPlayerSubstituteHP);
    uint8_t* hp = (hram->hBattleTurn == TURN_PLAYER)? &wram->wEnemySubstituteHP: &wram->wPlayerSubstituteHP;

// got_hp:

    uint16_t dmg = BigEndianToNative16(wram->wCurDamage);
    // LD_HL(wCurDamage);
    // LD_A_hli;
    // AND_A_A;
    // IF_NZ goto broke;

    if(dmg < 256) {
        // LD_A_de;
        // SUB_A_hl;
        uint16_t temp = *hp - dmg;
        // LD_de_A;
        *hp = (temp & 0xff);
        // IF_Z goto broke;
        // IF_NC goto done;
        if(temp != 0 && (temp & 0xff00) == 0) {
            return ResetDamage();
        }
    }

// broke:
    // LD_A(BATTLE_VARS_SUBSTATUS4_OPP);
    // CALL(aGetBattleVarAddr);
    // RES_hl(SUBSTATUS_SUBSTITUTE);
    bit_reset(*GetBattleVarAddr(BATTLE_VARS_SUBSTATUS4_OPP), SUBSTATUS_SUBSTITUTE);

    // LD_HL(mSubFadedText);
    // CALL(aStdBattleTextbox);
    StdBattleTextbox(SubFadedText);

    // CALL(aBattleCommand_SwitchTurn);
    BattleCommand_SwitchTurn();
    // CALL(aBattleCommand_LowerSubNoAnim);
    BattleCommand_LowerSubNoAnim();
    // LD_A(BATTLE_VARS_SUBSTATUS3);
    // CALL(aGetBattleVar);
    // AND_A(1 << SUBSTATUS_FLYING | 1 << SUBSTATUS_UNDERGROUND);
    if((GetBattleVar(BATTLE_VARS_SUBSTATUS3) & (1 << SUBSTATUS_FLYING | 1 << SUBSTATUS_UNDERGROUND)) == 0)
        AppearUserLowerSub();
    // CALL_Z (aAppearUserLowerSub);
    // CALL(aBattleCommand_SwitchTurn);
    BattleCommand_SwitchTurn();

    // LD_A(BATTLE_VARS_MOVE_EFFECT);
    // CALL(aGetBattleVarAddr);
    uint8_t* effect = GetBattleVarAddr(BATTLE_VARS_MOVE_EFFECT);
    switch(*effect) {
        default:
            // XOR_A_A;
            // LD_hl_A;
            *effect = 0;
            // fallthrough
        // CP_A(EFFECT_MULTI_HIT);
        // IF_Z goto ok;
        case EFFECT_MULTI_HIT:
        // CP_A(EFFECT_DOUBLE_HIT);
        // IF_Z goto ok;
        case EFFECT_DOUBLE_HIT:
        // CP_A(EFFECT_POISON_MULTI_HIT);
        // IF_Z goto ok;
        case EFFECT_POISON_HIT:
        // CP_A(EFFECT_TRIPLE_KICK);
        // IF_Z goto ok;
        case EFFECT_TRIPLE_KICK:
        // CP_A(EFFECT_BEAT_UP);
        // IF_Z goto ok;
        case EFFECT_BEAT_UP:
        // ok:
            // CALL(aRefreshBattleHuds);
            RefreshBattleHuds();
    }

// done:
    // JP(mResetDamage);
    return ResetDamage();
}

void UpdateMoveData(void){
    // LD_A(BATTLE_VARS_MOVE_ANIM);
    // CALL(aGetBattleVarAddr);
    // LD_D_H;
    // LD_E_L;
    struct Move* de = (struct Move*)GetBattleVarAddr(BATTLE_VARS_MOVE_ANIM);

    // LD_A(BATTLE_VARS_MOVE);
    // CALL(aGetBattleVar);
    move_t move = GetBattleVar(BATTLE_VARS_MOVE);
    // LD_addr_A(wCurSpecies);
    // LD_addr_A(wNamedObjectIndex);

    // DEC_A;
    // CALL(aGetMoveData);
    GetMoveData(de, move);
    // CALL(aGetMoveName);
    uint8_t* hl = GetMoveName(move);
    // JP(mCopyName1);
    CopyName1(hl);
}

static bool BattleCommand_SleepTarget_CheckAIRandomFail(void) {
// Enemy turn
    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // IF_Z goto dont_fail;

// Not in link battle
    // LD_A_addr(wLinkMode);
    // AND_A_A;
    // IF_NZ goto dont_fail;

    // LD_A_addr(wInBattleTowerBattle);
    // AND_A_A;
    // IF_NZ goto dont_fail;

// Not locked-on by the enemy
    // LD_A_addr(wPlayerSubStatus5);
    // BIT_A(SUBSTATUS_LOCK_ON);
    // IF_NZ goto dont_fail;

    // CALL(aBattleRandom);
    // CP_A(25 percent + 1);  // 25% chance AI fails
    // RET_C ;
    if(hram->hBattleTurn != TURN_PLAYER
    && wram->wLinkMode == 0
    && wram->wInBattleTowerBattle == 0
    && !bit_test(wram->wPlayerSubStatus5, SUBSTATUS_LOCK_ON)
    && v_BattleRandom_Conv() < 25 percent + 1) {
        return true;
    }

// dont_fail:
    // XOR_A_A;
    // RET;
    return false;
}

void BattleCommand_SleepTarget(void){
//  sleeptarget
    PEEK("");
    item_t item;
    // CALL(aGetOpponentItem);
    uint16_t effect = GetOpponentItem(&item);
    // LD_A_B;
    // CP_A(HELD_PREVENT_SLEEP);
    // IF_NZ goto not_protected_by_item;

    if(HIGH(effect) == HELD_PREVENT_SLEEP) {
        // LD_A_hl;
        // LD_addr_A(wNamedObjectIndex);
        // CALL(aGetItemName);
        GetItemName(item);
        // LD_HL(mProtectedByText);
        // goto fail;
        AnimateFailedMove();
        return StdBattleTextbox(ProtectedByText);
    }


// not_protected_by_item:
    // LD_A(BATTLE_VARS_STATUS_OPP);
    // CALL(aGetBattleVarAddr);
    // LD_D_H;
    // LD_E_L;
    uint8_t* de = GetBattleVarAddr(BATTLE_VARS_STATUS_OPP);
    // LD_A_de;
    // AND_A(SLP);
    // LD_HL(mAlreadyAsleepText);
    // IF_NZ goto fail;
    if(*de & SLP) {
        AnimateFailedMove();
        return StdBattleTextbox(AlreadyAsleepText);
    }

    // LD_A_addr(wAttackMissed);
    // AND_A_A;
    // JP_NZ (mPrintDidntAffect2);
    if(wram->wAttackMissed)
        return PrintDidntAffect2();

    // LD_HL(mDidntAffect1Text);
    // CALL(aBattleCommand_SleepTarget_CheckAIRandomFail);
    // IF_C goto fail;

    // LD_A_de;
    // AND_A_A;
    // IF_NZ goto fail;

    // CALL(aCheckSubstituteOpp);
    // IF_NZ goto fail;
    if(BattleCommand_SleepTarget_CheckAIRandomFail() 
    || *de != 0
    || CheckSubstituteOpp()) {
        AnimateFailedMove();
        return StdBattleTextbox(DidntAffect1Text);
    }

    // CALL(aAnimateCurrentMove);
    AnimateCurrentMove();
    // LD_B(SLP);
    // LD_A_addr(wInBattleTowerBattle);
    // AND_A_A;
    // IF_Z goto random_loop;
    // LD_B(0b011);
    uint8_t b = (wram->wInBattleTowerBattle == 0)? SLP: 0b011; 

    uint8_t a;
    do {
    // random_loop:
        // CALL(aBattleRandom);
        a = v_BattleRandom_Conv() & b;
        // AND_A_B;
        // IF_Z goto random_loop;
        // CP_A(SLP);
        // IF_Z goto random_loop;
    } while(a == 0 || a == SLP);
    // INC_A;
    // LD_de_A;
    *de = a + 1;
    // CALL(aUpdateOpponentInParty);
    UpdateOpponentInParty();
    // CALL(aRefreshBattleHuds);
    RefreshBattleHuds();

    // LD_HL(mFellAsleepText);
    // CALL(aStdBattleTextbox);
    StdBattleTextbox(FellAsleepText);

    // FARCALL(aUseHeldStatusHealingItem);

    // JP_Z (mOpponentCantMove);
    if(!UseHeldStatusHealingItem())
        return OpponentCantMove();
    // RET;
    return;

// fail:
    // PUSH_HL;
    // CALL(aAnimateFailedMove);
    // POP_HL;
    // JP(mStdBattleTextbox);
}

void BattleCommand_PoisonTarget(void){
//  poisontarget
    PEEK("");
    // CALL(aCheckSubstituteOpp);
    // RET_NZ ;
    if(CheckSubstituteOpp())
        return;
    // LD_A(BATTLE_VARS_STATUS_OPP);
    // CALL(aGetBattleVarAddr);
    // AND_A_A;
    // RET_NZ ;
    if(*GetBattleVarAddr(BATTLE_VARS_STATUS_OPP))
        return;
    // LD_A_addr(wTypeModifier);
    // AND_A(0x7f);
    // RET_Z ;
    if((wram->wTypeModifier & 0x7f) == 0)
        return;
    // CALL(aCheckIfTargetIsPoisonType);
    // RET_Z ;
    if(CheckIfTargetIsPoisonType())
        return;
    // CALL(aGetOpponentItem);
    // LD_A_B;
    // CP_A(HELD_PREVENT_POISON);
    // RET_Z ;
    if(HIGH(GetOpponentItem(NULL)) == HELD_PREVENT_POISON)
        return;
    // LD_A_addr(wEffectFailed);
    // AND_A_A;
    // RET_NZ ;
    // CALL(aSafeCheckSafeguard);
    // RET_NZ ;
    if(wram->wEffectFailed || SafeCheckSafeguard())
        return;

    // CALL(aPoisonOpponent);
    PoisonOpponent();
    // LD_DE(ANIM_PSN);
    // CALL(aPlayOpponentBattleAnim);
    PlayOpponentBattleAnim(ANIM_PSN);
    // CALL(aRefreshBattleHuds);
    RefreshBattleHuds();

    // LD_HL(mWasPoisonedText);
    // CALL(aStdBattleTextbox);
    StdBattleTextbox(WasPoisonedText);

    // FARCALL(aUseHeldStatusHealingItem);
    UseHeldStatusHealingItem();
    // RET;
}

static bool BattleCommand_Poison_check_toxic(uint8_t** hl, uint8_t** de) {
    // LD_A(BATTLE_VARS_SUBSTATUS5_OPP);
    // CALL(aGetBattleVarAddr);
    *hl = GetBattleVarAddr(BATTLE_VARS_SUBSTATUS5_OPP);
    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // LD_DE(wEnemyToxicCount);
    // IF_Z goto ok;
    // LD_DE(wPlayerToxicCount);
    *de = (hram->hBattleTurn == TURN_PLAYER)? &wram->wEnemyToxicCount: &wram->wPlayerToxicCount;

// ok:
    // LD_A(BATTLE_VARS_MOVE_EFFECT);
    // CALL(aGetBattleVar);
    // CP_A(EFFECT_TOXIC);
    // RET;
    return GetBattleVar(BATTLE_VARS_MOVE_EFFECT) == EFFECT_TOXIC;
}

static void BattleCommand_Poison_apply_poison(void) {
    // CALL(aAnimateCurrentMove);
    AnimateCurrentMove();
    // CALL(aPoisonOpponent);
    PoisonOpponent();
    // JP(mRefreshBattleHuds);
    return RefreshBattleHuds();
}

void BattleCommand_Poison(void){
//  poison
    PEEK("");
    // LD_HL(mDoesntAffectText);
    // LD_A_addr(wTypeModifier);
    // AND_A(0x7f);
    // JP_Z (mBattleCommand_Poison_failed);

    // CALL(aCheckIfTargetIsPoisonType);
    // JP_Z (mBattleCommand_Poison_failed);
    if((wram->wTypeModifier & 0x7f) == 0 || CheckIfTargetIsPoisonType()) {
    // failed:
        // PUSH_HL;
        // CALL(aAnimateFailedMove);
        AnimateFailedMove();
        // POP_HL;
        // JP(mStdBattleTextbox);
        return StdBattleTextbox(DoesntAffectText);
    }

    // LD_A(BATTLE_VARS_STATUS_OPP);
    // CALL(aGetBattleVar);
    // LD_B_A;
    // LD_HL(mAlreadyPoisonedText);
    // AND_A(1 << PSN);
    // JP_NZ (mBattleCommand_Poison_failed);
    if(GetBattleVar(BATTLE_VARS_STATUS_OPP) & (1 << PSN)) {
    // failed:
        // PUSH_HL;
        // CALL(aAnimateFailedMove);
        AnimateFailedMove();
        // POP_HL;
        // JP(mStdBattleTextbox);
        return StdBattleTextbox(AlreadyPoisonedText);
    }

    item_t item;
    // CALL(aGetOpponentItem);
    // LD_A_B;
    // CP_A(HELD_PREVENT_POISON);
    // IF_NZ goto do_poison;
    if(HIGH(GetOpponentItem(&item)) == HELD_PREVENT_POISON) {
        // LD_A_hl;
        // LD_addr_A(wNamedObjectIndex);
        // CALL(aGetItemName);
        GetItemName(item);
        // LD_HL(mProtectedByText);
        // goto failed;
    // failed:
        // PUSH_HL;
        // CALL(aAnimateFailedMove);
        AnimateFailedMove();
        // POP_HL;
        // JP(mStdBattleTextbox);
        return StdBattleTextbox(ProtectedByText);
    }

// do_poison:
    // LD_HL(mDidntAffect1Text);
    // LD_A(BATTLE_VARS_STATUS_OPP);
    // CALL(aGetBattleVar);
    // AND_A_A;
    // IF_NZ goto failed;
    if(GetBattleVar(BATTLE_VARS_STATUS_OPP)) {
    // failed:
        // PUSH_HL;
        // CALL(aAnimateFailedMove);
        AnimateFailedMove();
        // POP_HL;
        // JP(mStdBattleTextbox);
        return StdBattleTextbox(DidntAffect1Text);
    }

    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // IF_Z goto dont_sample_failure;

    // LD_A_addr(wLinkMode);
    // AND_A_A;
    // IF_NZ goto dont_sample_failure;

    // LD_A_addr(wInBattleTowerBattle);
    // AND_A_A;
    // IF_NZ goto dont_sample_failure;

    // LD_A_addr(wPlayerSubStatus5);
    // BIT_A(SUBSTATUS_LOCK_ON);
    // IF_NZ goto dont_sample_failure;

    // CALL(aBattleRandom);
    // CP_A(25 percent + 1);  // 25% chance AI fails
    // IF_C goto failed;

    if(hram->hBattleTurn != TURN_PLAYER
    && wram->wLinkMode == 0
    && wram->wInBattleTowerBattle == 0
    && !bit_test(wram->wPlayerSubStatus5, SUBSTATUS_LOCK_ON)
    && v_BattleRandom_Conv() < 25 percent + 1) {
    // failed:
        // PUSH_HL;
        // CALL(aAnimateFailedMove);
        AnimateFailedMove();
        // POP_HL;
        // JP(mStdBattleTextbox);
        return StdBattleTextbox(DidntAffect1Text);
    }

// dont_sample_failure:
    // CALL(aCheckSubstituteOpp);
    // IF_NZ goto failed;
    // LD_A_addr(wAttackMissed);
    // AND_A_A;
    // IF_NZ goto failed;
    if(CheckSubstituteOpp() || wram->wAttackMissed) {
    // failed:
        // PUSH_HL;
        // CALL(aAnimateFailedMove);
        AnimateFailedMove();
        // POP_HL;
        // JP(mStdBattleTextbox);
        return StdBattleTextbox(DidntAffect1Text);
    }
    uint8_t* hl, *de;
    // CALL(aBattleCommand_Poison_check_toxic);
    // IF_Z goto toxic;
    if(BattleCommand_Poison_check_toxic(&hl, &de)) {
    // toxic:
        // SET_hl(SUBSTATUS_TOXIC);
        bit_set(*hl, SUBSTATUS_TOXIC);
        // XOR_A_A;
        // LD_de_A;
        *de = 0;
        // CALL(aBattleCommand_Poison_apply_poison);
        BattleCommand_Poison_apply_poison();
        // LD_HL(mBadlyPoisonedText);
        // CALL(aStdBattleTextbox);
        StdBattleTextbox(BadlyPoisonedText);
    }
    else {
        // CALL(aBattleCommand_Poison_apply_poison);
        BattleCommand_Poison_apply_poison();
        // LD_HL(mWasPoisonedText);
        // CALL(aStdBattleTextbox);
        StdBattleTextbox(WasPoisonedText);
        // goto finished;
    }

// finished:
    // FARCALL(aUseHeldStatusHealingItem);
    UseHeldStatusHealingItem();
    // RET;
    return;

// failed:
    // PUSH_HL;
    // CALL(aAnimateFailedMove);
    // POP_HL;
    // JP(mStdBattleTextbox);
}

bool CheckIfTargetIsPoisonType(void){
    if(hram->hBattleTurn != TURN_PLAYER) {
    // ok:
        // LD_A_de;
        // INC_DE;
        // CP_A(POISON);
        // RET_Z ;
        // LD_A_de;
        // CP_A(POISON);
        // RET;
        return wram->wBattleMon.type1 == POISON || wram->wBattleMon.type2 == POISON;
    }
    else {
    // ok:
        // LD_A_de;
        // INC_DE;
        // CP_A(POISON);
        // RET_Z ;
        // LD_A_de;
        // CP_A(POISON);
        // RET;
        return wram->wEnemyMon.type1 == POISON || wram->wEnemyMon.type2 == POISON;
    }
    // LD_DE(wEnemyMonType1);
    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // IF_Z goto ok;
    // LD_DE(wBattleMonType1);

// ok:
    // LD_A_de;
    // INC_DE;
    // CP_A(POISON);
    // RET_Z ;
    // LD_A_de;
    // CP_A(POISON);
    // RET;

}

void PoisonOpponent(void){
    // LD_A(BATTLE_VARS_STATUS_OPP);
    // CALL(aGetBattleVarAddr);
    // SET_hl(PSN);
    bit_set(*GetBattleVarAddr(BATTLE_VARS_STATUS_OPP), PSN);
    // JP(mUpdateOpponentInParty);
    return UpdateOpponentInParty();
}

void BattleCommand_DrainTarget(void){
//  draintarget
    PEEK("");
    // CALL(aSapHealth);
    SapHealth();
    // LD_HL(mSuckedHealthText);
    // JP(mStdBattleTextbox);
    return StdBattleTextbox(SuckedHealthText);

}

void BattleCommand_EatDream(void){
//  eatdream
    PEEK("");
    // CALL(aSapHealth);
    SapHealth();
    // LD_HL(mDreamEatenText);
    // JP(mStdBattleTextbox);
    return StdBattleTextbox(SuckedHealthText);
}

void SapHealth(void){
// Divide damage by 2, store it in hDividend
    // LD_HL(wCurDamage);
    // LD_A_hli;
    // SRL_A;
    // LDH_addr_A(hDividend);
    // LD_B_A;
    // LD_A_hl;
    // RR_A;
    // LDH_addr_A(hDividend + 1);
    uint16_t dmg = BigEndianToNative16(wram->wCurDamage) >> 1;
    // OR_A_B;
    // IF_NZ goto at_least_one;
    if(dmg == 0) {
        // LD_A(1);
        // LDH_addr_A(hDividend + 1);
        dmg = 1;
    }

// at_least_one:

    // LD_HL(wBattleMonHP);
    // LD_DE(wBattleMonMaxHP);
    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // IF_Z goto battlemonhp;
    // LD_HL(wEnemyMonHP);
    // LD_DE(wEnemyMonMaxHP);
    uint16_t* maxhp = (uint16_t*)((hram->hBattleTurn != TURN_PLAYER)? wram_ptr(wEnemyMonMaxHP): wram_ptr(wBattleMonMaxHP));
    uint16_t*    hp = (uint16_t*)((hram->hBattleTurn != TURN_PLAYER)? wram_ptr(wEnemyMonHP): wram_ptr(wBattleMonHP));

// battlemonhp:

// Store current HP in little endian wHPBuffer2
    // LD_BC(wHPBuffer2 + 1);
    // LD_A_hli;
    // LD_bc_A;
    // LD_A_hl;
    // DEC_BC;
    // LD_bc_A;
    wram->wHPBuffer2 = BigEndianToNative16(*hp);

// Store max HP in little endian wHPBuffer1
    // LD_A_de;
    // DEC_BC;
    // LD_bc_A;
    // INC_DE;
    // LD_A_de;
    // DEC_BC;
    // LD_bc_A;
    wram->wHPBuffer1 = BigEndianToNative16(*maxhp);

// Add hDividend to current HP and copy it to little endian wHPBuffer3
    // LDH_A_addr(hDividend + 1);
    // LD_B_hl;
    // ADD_A_B;
    // LD_hld_A;
    // LD_addr_A(wHPBuffer3);
    // LDH_A_addr(hDividend);
    // LD_B_hl;
    // ADC_A_B;
    // LD_hli_A;
    // LD_addr_A(wHPBuffer3 + 1);
    wram->wHPBuffer3 = dmg + wram->wHPBuffer2;
    *hp = NativeToBigEndian16(wram->wHPBuffer3);
    // IF_C goto max_hp;
    if(dmg + wram->wHPBuffer2 <= 0xffff) {
    // Subtract current HP from max HP (to see if we have more than max HP)
        // LD_A_hld;
        // LD_B_A;
        // LD_A_de;
        // DEC_DE;
        // SUB_A_B;
        // LD_A_hli;
        // LD_B_A;
        // LD_A_de;
        // INC_DE;
        // SBC_A_B;
        // IF_NC goto finish;
        if(wram->wHPBuffer1 >= wram->wHPBuffer2) 
            goto finish;
    }


// max_hp:
// Load max HP into current HP and copy it to little endian wHPBuffer3
    // LD_A_de;
    // LD_hld_A;
    // LD_addr_A(wHPBuffer3);
    // DEC_DE;
    // LD_A_de;
    // LD_hli_A;
    // LD_addr_A(wHPBuffer3 + 1);
    // INC_DE;
    *hp = *maxhp;
    wram->wHPBuffer3 = BigEndianToNative16(*maxhp);

finish:;
    tile_t* hl;
    uint8_t which;
    if(hram->hBattleTurn == TURN_PLAYER) {
        // LDH_A_addr(hBattleTurn);
        // AND_A_A;
        // hlcoord(10, 9, wTilemap);
        // LD_A(0x1);
        // IF_Z goto hp_bar;
        hl = coord(10, 9, wram->wTilemap);
        which = 0x1;
    }
    else {
        // hlcoord(2, 2, wTilemap);
        // XOR_A_A;
        hl = coord(2, 2, wram->wTilemap);
        which = 0;
    }
// hp_bar:
    // LD_addr_A(wWhichHPBar);
    // PREDEF(pAnimateHPBar);
    AnimateHPBar_Conv(hl, which);
    // CALL(aRefreshBattleHuds);
    RefreshBattleHuds();
    // JP(mUpdateBattleMonInParty);
    return UpdateBattleMonInParty();
}

void BattleCommand_BurnTarget(void){
//  burntarget
    PEEK("");
    // XOR_A_A;
    // LD_addr_A(wNumHits);
    wram->wNumHits = 0;
    // CALL(aCheckSubstituteOpp);
    // RET_NZ ;
    if(CheckSubstituteOpp())
        return;
    // LD_A(BATTLE_VARS_STATUS_OPP);
    // CALL(aGetBattleVarAddr);
    uint8_t* status = GetBattleVarAddr(BATTLE_VARS_STATUS_OPP);
    // AND_A_A;
    // JP_NZ (mDefrost);
    if(*status)
        return Defrost(status);
    // LD_A_addr(wTypeModifier);
    // AND_A(0x7f);
    // RET_Z ;
    // CALL(aCheckMoveTypeMatchesTarget);  // Don't burn a Fire-type
    // RET_Z ;
    // CALL(aGetOpponentItem);
    // LD_A_B;
    // CP_A(HELD_PREVENT_BURN);
    // RET_Z ;
    // LD_A_addr(wEffectFailed);
    // AND_A_A;
    // RET_NZ ;
    // CALL(aSafeCheckSafeguard);
    // RET_NZ ;
    if((wram->wTypeModifier & 0x7f) == 0
    || CheckMoveTypeMatchesTarget()
    || HIGH(GetOpponentItem(NULL)) == HELD_PREVENT_BURN
    || wram->wEffectFailed
    || SafeCheckSafeguard())
        return;
    // LD_A(BATTLE_VARS_STATUS_OPP);
    // CALL(aGetBattleVarAddr);
    // SET_hl(BRN);
    bit_set(*GetBattleVarAddr(BATTLE_VARS_STATUS_OPP), BRN);
    // CALL(aUpdateOpponentInParty);
    UpdateOpponentInParty();
    // LD_HL(mApplyBrnEffectOnAttack);
    // CALL(aCallBattleCore);
    ApplyBrnEffectOnAttack_Conv(hram->hBattleTurn);
    // LD_DE(ANIM_BRN);
    // CALL(aPlayOpponentBattleAnim);
    PlayOpponentBattleAnim(ANIM_BRN);
    // CALL(aRefreshBattleHuds);
    RefreshBattleHuds();

    // LD_HL(mWasBurnedText);
    // CALL(aStdBattleTextbox);
    StdBattleTextbox(WasBurnedText);

    // FARCALL(aUseHeldStatusHealingItem);
    UseHeldStatusHealingItem();
    // RET;
}

void Defrost(uint8_t* status){
    // LD_A_hl;
    // AND_A(1 << FRZ);
    // RET_Z ;
    if((*status & (1 << FRZ)) == 0)
        return;

    // XOR_A_A;
    // LD_hl_A;
    *status = 0;

    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // LD_A_addr(wCurOTMon);
    // LD_HL(wOTPartyMon1Status);
    // IF_Z goto ok;
    // LD_HL(wPartyMon1Status);
    // LD_A_addr(wCurBattleMon);
    struct PartyMon* mon = (hram->hBattleTurn == TURN_PLAYER)
        ? wram->wOTPartyMon + wram->wCurOTMon
        : wram->wPartyMon   + wram->wCurBattleMon;

// ok:

    // CALL(aGetPartyLocation);
    // XOR_A_A;
    // LD_hl_A;
    mon->status = 0;
    // CALL(aUpdateOpponentInParty);
    UpdateOpponentInParty();

    // LD_HL(mDefrostedOpponentText);
    // JP(mStdBattleTextbox);
    return StdBattleTextbox(DefrostedOpponentText);
}

void BattleCommand_FreezeTarget(void){
//  freezetarget
    PEEK("");
    // XOR_A_A;
    // LD_addr_A(wNumHits);
    wram->wNumHits = 0;
    // CALL(aCheckSubstituteOpp);
    // RET_NZ ;
    if(CheckSubstituteOpp())
        return;
    // LD_A(BATTLE_VARS_STATUS_OPP);
    // CALL(aGetBattleVarAddr);
    // AND_A_A;
    // RET_NZ ;
    if(*GetBattleVarAddr(BATTLE_VARS_STATUS_OPP) != 0)
        return;
    // LD_A_addr(wTypeModifier);
    // AND_A(0x7f);
    // RET_Z ;
    if((wram->wTypeModifier & 0x7f) == 0)
        return;
    // LD_A_addr(wBattleWeather);
    // CP_A(WEATHER_SUN);
    // RET_Z ;
    if(wram->wBattleWeather == WEATHER_SUN)
        return;
    // CALL(aCheckMoveTypeMatchesTarget);  // Don't freeze an Ice-type
    // RET_Z ;
    if(CheckMoveTypeMatchesTarget())
        return;
    // CALL(aGetOpponentItem);
    // LD_A_B;
    // CP_A(HELD_PREVENT_FREEZE);
    // RET_Z ;
    if(HIGH(GetOpponentItem(NULL)) == HELD_PREVENT_FREEZE)
        return;
    // LD_A_addr(wEffectFailed);
    // AND_A_A;
    // RET_NZ ;
    // CALL(aSafeCheckSafeguard);
    // RET_NZ ;
    if(wram->wEffectFailed || SafeCheckSafeguard())
        return;
    // LD_A(BATTLE_VARS_STATUS_OPP);
    // CALL(aGetBattleVarAddr);
    uint8_t* hl = GetBattleVarAddr(BATTLE_VARS_STATUS_OPP);
    // SET_hl(FRZ);
    bit_set(*hl, FRZ);
    // CALL(aUpdateOpponentInParty);
    UpdateOpponentInParty();
    // LD_DE(ANIM_FRZ);
    // CALL(aPlayOpponentBattleAnim);
    PlayOpponentBattleAnim(ANIM_FRZ);
    // CALL(aRefreshBattleHuds);
    RefreshBattleHuds();

    // LD_HL(mWasFrozenText);
    // CALL(aStdBattleTextbox);
    StdBattleTextbox(WasFrozenText);

    // FARCALL(aUseHeldStatusHealingItem);
    // RET_NZ ;
    if(UseHeldStatusHealingItem())
        return;

    // CALL(aOpponentCantMove);
    OpponentCantMove();
    // CALL(aEndRechargeOpp);
    EndRechargeOpp();
    // LD_HL(wEnemyJustGotFrozen);
    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // IF_Z goto finish;
    if(hram->hBattleTurn == TURN_PLAYER) {
        wram->wEnemyJustGotFrozen = 0x1;
    }
    else {
        // LD_HL(wPlayerJustGotFrozen);

    // finish:
        // LD_hl(0x1);
        wram->wPlayerJustGotFrozen = 0x1;
    }
    // RET;
}

void BattleCommand_ParalyzeTarget(void){
//  paralyzetarget
    PEEK("");
    // XOR_A_A;
    // LD_addr_A(wNumHits);
    wram->wNumHits = 0;
    // CALL(aCheckSubstituteOpp);
    // RET_NZ ;
    if(CheckSubstituteOpp())
        return;
    // LD_A(BATTLE_VARS_STATUS_OPP);
    // CALL(aGetBattleVarAddr);
    // AND_A_A;
    // RET_NZ ;
    if(GetBattleVar(BATTLE_VARS_STATUS_OPP))
        return;
    // LD_A_addr(wTypeModifier);
    // AND_A(0x7f);
    // RET_Z ;
    if((wram->wTypeModifier & 0x7f) == 0)
        return;
    // CALL(aGetOpponentItem);
    // LD_A_B;
    // CP_A(HELD_PREVENT_PARALYZE);
    // RET_Z ;
    if(HIGH(GetOpponentItem(NULL)) == HELD_PREVENT_PARALYZE)
        return;
    // LD_A_addr(wEffectFailed);
    // AND_A_A;
    // RET_NZ ;
    // CALL(aSafeCheckSafeguard);
    // RET_NZ ;
    if(wram->wEffectFailed || SafeCheckSafeguard())
        return;
    // LD_A(BATTLE_VARS_STATUS_OPP);
    // CALL(aGetBattleVarAddr);
    // SET_hl(PAR);
    bit_set(*GetBattleVarAddr(BATTLE_VARS_STATUS_OPP), PAR);
    // CALL(aUpdateOpponentInParty);
    UpdateOpponentInParty();
    // LD_HL(mApplyPrzEffectOnSpeed);
    // CALL(aCallBattleCore);
    ApplyPrzEffectOnSpeed();
    // LD_DE(ANIM_PAR);
    // CALL(aPlayOpponentBattleAnim);
    PlayOpponentBattleAnim(ANIM_PAR);
    // CALL(aRefreshBattleHuds);
    RefreshBattleHuds();
    // CALL(aPrintParalyze);
    PrintParalyze();
    // LD_HL(mUseHeldStatusHealingItem);
    // JP(mCallBattleCore);
    UseHeldStatusHealingItem();
}

void BattleCommand_AttackUp(void){
//  attackup
    // LD_B(ATTACK);
    gBattleCmdState.b = ATTACK;
    // JR(mBattleCommand_StatUp);
    BattleCommand_StatUp();
}

void BattleCommand_DefenseUp(void){
//  defenseup
    // LD_B(DEFENSE);
    gBattleCmdState.b = DEFENSE;
    // JR(mBattleCommand_StatUp);
    BattleCommand_StatUp();
}

void BattleCommand_SpeedUp(void){
//  speedup
    // LD_B(SPEED);
    gBattleCmdState.b = SPEED;
    // JR(mBattleCommand_StatUp);
    BattleCommand_StatUp();

}

void BattleCommand_SpecialAttackUp(void){
//  specialattackup
    // LD_B(SP_ATTACK);
    gBattleCmdState.b = SP_ATTACK;
    // JR(mBattleCommand_StatUp);
    BattleCommand_StatUp();

}

void BattleCommand_SpecialDefenseUp(void){
//  specialdefenseup
    // LD_B(SP_DEFENSE);
    gBattleCmdState.b = SP_DEFENSE;
    // JR(mBattleCommand_StatUp);
    BattleCommand_StatUp();

}

void BattleCommand_AccuracyUp(void){
//  accuracyup
    // LD_B(ACCURACY);
    gBattleCmdState.b = ACCURACY;
    // JR(mBattleCommand_StatUp);
    BattleCommand_StatUp();

}

void BattleCommand_EvasionUp(void){
//  evasionup
    // LD_B(EVASION);
    gBattleCmdState.b = EVASION;
    // JR(mBattleCommand_StatUp);
    BattleCommand_StatUp();

}

void BattleCommand_AttackUp2(void){
//  attackup2
    // LD_B(0x10 | ATTACK);
    gBattleCmdState.b = 0x10 | ATTACK;
    // JR(mBattleCommand_StatUp);
    BattleCommand_StatUp();

}

void BattleCommand_DefenseUp2(void){
//  defenseup2
    // LD_B(0x10 | DEFENSE);
    gBattleCmdState.b = 0x10 | DEFENSE;
    // JR(mBattleCommand_StatUp);
    BattleCommand_StatUp();

}

void BattleCommand_SpeedUp2(void){
//  speedup2
    // LD_B(0x10 | SPEED);
    gBattleCmdState.b = 0x10 | SPEED;
    // JR(mBattleCommand_StatUp);
    BattleCommand_StatUp();

}

void BattleCommand_SpecialAttackUp2(void){
//  specialattackup2
    // LD_B(0x10 | SP_ATTACK);
    gBattleCmdState.b = 0x10 | SP_ATTACK;
    // JR(mBattleCommand_StatUp);
    BattleCommand_StatUp();

}

void BattleCommand_SpecialDefenseUp2(void){
//  specialdefenseup2
    // LD_B(0x10 | SP_DEFENSE);
    gBattleCmdState.b = 0x10 | SP_DEFENSE;
    // JR(mBattleCommand_StatUp);
    BattleCommand_StatUp();

}

void BattleCommand_AccuracyUp2(void){
//  accuracyup2
    // LD_B(0x10 | ACCURACY);
    gBattleCmdState.b = 0x10 | ACCURACY;
    // JR(mBattleCommand_StatUp);
    BattleCommand_StatUp();

}

void BattleCommand_EvasionUp2(void){
//  evasionup2
    // LD_B(0x10 | EVASION);
    gBattleCmdState.b = 0x10 | EVASION;
    // JR(mBattleCommand_StatUp);
    BattleCommand_StatUp();

}

void BattleCommand_StatUp(void){
//  statup
    // CALL(aRaiseStat);
    RaiseStat(gBattleCmdState.b);
    // LD_A_addr(wFailedMessage);
    // AND_A_A;
    // RET_NZ ;
    if(wram->wFailedMessage)
        return;
    // JP(mMinimizeDropSub);
    return MinimizeDropSub();
}

void RaiseStat(uint8_t b){
    // LD_A_B;
    // LD_addr_A(wLoweredStat);
    wram->wLoweredStat = b;
    // LD_HL(wPlayerStatLevels);
    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // IF_Z goto got_stat_levels;
    // LD_HL(wEnemyStatLevels);
    uint8_t* hl = (hram->hBattleTurn == TURN_PLAYER)? wram->wPlayerStatLevels: wram->wEnemyStatLevels;

// got_stat_levels:
    // LD_A_addr(wAttackMissed);
    // AND_A_A;
    // JP_NZ (mRaiseStat_stat_raise_failed);
    // LD_A_addr(wEffectFailed);
    // AND_A_A;
    // JP_NZ (mRaiseStat_stat_raise_failed);
    if(wram->wAttackMissed || wram->wEffectFailed) {
    // stat_raise_failed:
        // LD_A(0x1);
        // LD_addr_A(wFailedMessage);
        wram->wFailedMessage = 0x1;
        // RET;
        return;
    }
    // LD_A_addr(wLoweredStat);
    // AND_A(0xf);
    // LD_C_A;
    uint8_t c = wram->wLoweredStat & 0xf;
    // LD_B(0);
    // ADD_HL_BC;
    // LD_B_hl;
    // INC_B;
    uint8_t stat = hl[c] + 1;
    // LD_A(0xd);
    // CP_A_B;
    // JP_C (mRaiseStat_cant_raise_stat);
    if(stat <= 0xd) {
        // LD_A_addr(wLoweredStat);
        // AND_A(0xf0);
        // IF_Z goto got_num_stages;
        if((wram->wLoweredStat & 0xf0) != 0) {
            // INC_B;
            stat++;
            // LD_A(0xd);
            // CP_A_B;
            // IF_NC goto got_num_stages;
            if(stat > 0xd) {
                // LD_B_A;
                stat = 0xd;
            }
        }

    // got_num_stages:
        // LD_hl_B;
        hl[c] = stat;
        // PUSH_HL;
        // LD_A_C;
        // CP_A(0x5);
        // IF_NC goto done_calcing_stats;
        if(c < 0x5) {
            // LD_HL(wBattleMonStats + 1);
            uint8_t (*hl2)[2] = (hram->hBattleTurn == TURN_PLAYER)? wram->wBattleMon.stats: wram->wEnemyMon.stats;
            // LD_DE(wPlayerStats);
            // uint16_t* de = (hram->hBattleTurn == 0)? wram->wPlayerStats: wram->wEnemyStats;
            // LDH_A_addr(hBattleTurn);
            // AND_A_A;
            // IF_Z goto got_stats_pointer;
            // LD_HL(wEnemyMonStats + 1);
            // LD_DE(wEnemyStats);
            uint16_t hlstat = hl2[c][1] | (hl2[c][0] << 8);

        // got_stats_pointer:
            // PUSH_BC;
            // SLA_C;
            // LD_B(0);
            // ADD_HL_BC;
            // LD_A_C;
            // ADD_A_E;
            // LD_E_A;
            // IF_NC goto no_carry;
            // INC_D;

        // no_carry:
            // POP_BC;
            // LD_A_hld;
            // SUB_A(LOW(MAX_STAT_VALUE));
            // IF_NZ goto not_already_max;
            // LD_A_hl;
            // SBC_A(HIGH(MAX_STAT_VALUE));
            // JP_Z (mRaiseStat_stats_already_max);
            if(hlstat >= MAX_STAT_VALUE) {
                hl[c]--;
                goto cant_raise_stat;
            }

        // not_already_max:
            // LDH_A_addr(hBattleTurn);
            // AND_A_A;
            // IF_Z goto calc_player_stats;
            if(hram->hBattleTurn == TURN_PLAYER)
                CalcPlayerStats();
            else
                // CALL(aCalcEnemyStats);
                CalcEnemyStats();
            // goto done_calcing_stats;


        // calc_player_stats:
            // CALL(aCalcPlayerStats);
        }

    // done_calcing_stats:
        // POP_HL;
        // XOR_A_A;
        // LD_addr_A(wFailedMessage);
        wram->wFailedMessage = 0;
        // RET;
        return;


    // stats_already_max:
        // POP_HL;
        // DEC_hl;
    // fallthrough
    }
    else {
    cant_raise_stat:
        // LD_A(0x2);
        // LD_addr_A(wFailedMessage);
        wram->wFailedMessage = 0x2;
        // LD_A(0x1);
        // LD_addr_A(wAttackMissed);
        wram->wAttackMissed = 0x1;
        // RET;
        return;
    }
}

void MinimizeDropSub(void){
//  Lower the substitute if we're minimizing

    uint8_t* bc;
    void (*hl)(void);
    if(hram->hBattleTurn == TURN_PLAYER) {
        // LD_BC(wPlayerMinimized);
        bc = &wram->wPlayerMinimized;
        // LD_HL(mDropPlayerSub);
        hl = &DropPlayerSub;
        // LDH_A_addr(hBattleTurn);
        // AND_A_A;
        // IF_Z goto do_player;
    }
    else {
        // LD_BC(wEnemyMinimized);
        bc = &wram->wEnemyMinimized;
        // LD_HL(mDropEnemySub);
        hl = &DropEnemySub;
    }

// do_player:
    // LD_A(BATTLE_VARS_MOVE_ANIM);
    // CALL(aGetBattleVar);
    // CP_A(MINIMIZE);
    // RET_NZ ;
    if(GetBattleVar(BATTLE_VARS_MOVE_ANIM) != MINIMIZE)
        return;

    // LD_A(0x1);
    // LD_bc_A;
    *bc = 0x1;
    // CALL(av_CheckBattleScene);
    // RET_NC ;
    if(CheckBattleScene())
        return;

    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = BGMAPMODE_NONE;
    // CALL(aCallBattleCore);
    hl();
    // CALL(aWaitBGMap);
    WaitBGMap();
    // JP(mBattleCommand_MoveDelay);
    return BattleCommand_MoveDelay();
}

void BattleCommand_AttackDown(void){
//  attackdown
    PEEK("");
    // LD_A(ATTACK);
    gBattleCmdState.a = ATTACK;
    // JR(mBattleCommand_StatDown);

    return BattleCommand_StatDown();
}

void BattleCommand_DefenseDown(void){
//  defensedown
    // LD_A(DEFENSE);
    gBattleCmdState.a = DEFENSE;
    // JR(mBattleCommand_StatDown);

    return BattleCommand_StatDown();
}

void BattleCommand_SpeedDown(void){
//  speeddown
    // LD_A(SPEED);
    gBattleCmdState.a = SPEED;
    // JR(mBattleCommand_StatDown);

    return BattleCommand_StatDown();
}

void BattleCommand_SpecialAttackDown(void){
//  specialattackdown
    // LD_A(SP_ATTACK);
    gBattleCmdState.a = SP_ATTACK;
    // JR(mBattleCommand_StatDown);

    return BattleCommand_StatDown();
}

void BattleCommand_SpecialDefenseDown(void){
//  specialdefensedown
    // LD_A(SP_DEFENSE);
    gBattleCmdState.a = SP_DEFENSE;
    // JR(mBattleCommand_StatDown);

    return BattleCommand_StatDown();
}

void BattleCommand_AccuracyDown(void){
//  accuracydown
    // LD_A(ACCURACY);
    gBattleCmdState.a = ACCURACY;
    // JR(mBattleCommand_StatDown);

    return BattleCommand_StatDown();
}

void BattleCommand_EvasionDown(void){
//  evasiondown
    // LD_A(EVASION);
    gBattleCmdState.a = EVASION;
    // JR(mBattleCommand_StatDown);

    return BattleCommand_StatDown();
}

void BattleCommand_AttackDown2(void){
//  attackdown2
    // LD_A(0x10 | ATTACK);
    gBattleCmdState.a = 0x10 | ATTACK;
    // JR(mBattleCommand_StatDown);

    return BattleCommand_StatDown();
}

void BattleCommand_DefenseDown2(void){
//  defensedown2
    // LD_A(0x10 | DEFENSE);
    gBattleCmdState.a = 0x10 | DEFENSE;
    // JR(mBattleCommand_StatDown);

    return BattleCommand_StatDown();
}

void BattleCommand_SpeedDown2(void){
//  speeddown2
    // LD_A(0x10 | SPEED);
    gBattleCmdState.a = 0x10 | SPEED;
    // JR(mBattleCommand_StatDown);

    return BattleCommand_StatDown();
}

void BattleCommand_SpecialAttackDown2(void){
//  specialattackdown2
    // LD_A(0x10 | SP_ATTACK);
    gBattleCmdState.a = 0x10 | SP_ATTACK;
    // JR(mBattleCommand_StatDown);

    return BattleCommand_StatDown();
}

void BattleCommand_SpecialDefenseDown2(void){
//  specialdefensedown2
    // LD_A(0x10 | SP_DEFENSE);
    gBattleCmdState.a = 0x10 | SP_DEFENSE;
    // JR(mBattleCommand_StatDown);
    return BattleCommand_StatDown();

}

void BattleCommand_AccuracyDown2(void){
//  accuracydown2
    // LD_A(0x10 | ACCURACY);
    gBattleCmdState.a = 0x10 | ACCURACY;
    // JR(mBattleCommand_StatDown);

    return BattleCommand_StatDown();
}

void BattleCommand_EvasionDown2(void){
//  evasiondown2
    // LD_A(0x10 | EVASION);
    gBattleCmdState.a = 0x10 | EVASION;

    return BattleCommand_StatDown();
}

void BattleCommand_StatDown(void){
//  statdown

    // LD_addr_A(wLoweredStat);
    wram->wLoweredStat = gBattleCmdState.a;

    // CALL(aCheckMist);
    // JP_NZ (mBattleCommand_StatDown_Mist);
    if(CheckMist()) {
    // Mist:
        // LD_A(2);
        // LD_addr_A(wFailedMessage);
        wram->wFailedMessage = 2;
        // LD_A(1);
        // LD_addr_A(wAttackMissed);
        wram->wAttackMissed = 1;
        // RET;
        return;
    }

    // LD_HL(wEnemyStatLevels);
    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // IF_Z goto GetStatLevel;
    // LD_HL(wPlayerStatLevels);
    uint8_t* statLevels = (hram->hBattleTurn == TURN_PLAYER)? wram->wEnemyStatLevels: wram->wPlayerStatLevels;

// GetStatLevel:
//  Attempt to lower the stat.
    // LD_A_addr(wLoweredStat);
    // AND_A(0xf);
    // LD_C_A;
    uint8_t c = wram->wLoweredStat & 0x7f;
    // LD_B(0);
    // ADD_HL_BC;
    // LD_B_hl;
    uint8_t b = statLevels[c];
    // DEC_B;
    // JP_Z (mBattleCommand_StatDown_CantLower);
    if(--b == 0)
        goto CantLower;

//  Sharply lower the stat if applicable.
    // LD_A_addr(wLoweredStat);
    // AND_A(0xf0);
    // IF_Z goto ComputerMiss;
    // DEC_B;
    // IF_NZ goto ComputerMiss;
    // INC_B;
    if(wram->wLoweredStat & 0xf0) {
        if(--b == 0)
            ++b;
    }

// ComputerMiss:
//  Computer opponents have a 25% chance of failing.
    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // IF_Z goto DidntMiss;

    // LD_A_addr(wLinkMode);
    // AND_A_A;
    // IF_NZ goto DidntMiss;

    // LD_A_addr(wInBattleTowerBattle);
    // AND_A_A;
    // IF_NZ goto DidntMiss;

//  Lock-On still always works.
    // LD_A_addr(wPlayerSubStatus5);
    // BIT_A(SUBSTATUS_LOCK_ON);
    // IF_NZ goto DidntMiss;

//  Attacking moves that also lower accuracy are unaffected.
    // LD_A(BATTLE_VARS_MOVE_EFFECT);
    // CALL(aGetBattleVar);
    // CP_A(EFFECT_ACCURACY_DOWN_HIT);
    // IF_Z goto DidntMiss;

    // CALL(aBattleRandom);
    // CP_A(25 percent + 1);  // 25% chance AI fails
    // IF_C goto Failed;

// DidntMiss:
    // CALL(aCheckSubstituteOpp);
    // IF_NZ goto Failed;

    // LD_A_addr(wAttackMissed);
    // AND_A_A;
    // IF_NZ goto Failed;

    // LD_A_addr(wEffectFailed);
    // AND_A_A;
    // IF_NZ goto Failed;

    // CALL(aCheckHiddenOpponent);
    // IF_NZ goto Failed;
    if((   hram->hBattleTurn != TURN_PLAYER
        && wram->wLinkMode == 0
        && wram->wInBattleTowerBattle == 0
        && !bit_test(wram->wPlayerSubStatus5, SUBSTATUS_LOCK_ON)
        && GetBattleVar(BATTLE_VARS_MOVE_EFFECT) != EFFECT_ACCURACY_DOWN_HIT
        && v_BattleRandom_Conv() < 25 percent + 1)
    || CheckSubstituteOpp()
    || wram->wAttackMissed
    || wram->wEffectFailed) {
    // Failed:
        // LD_A(1);
        // LD_addr_A(wFailedMessage);
        wram->wFailedMessage = 1;
        // LD_addr_A(wAttackMissed);
        wram->wAttackMissed = TRUE;
        // RET;
        return;
    }

//  Accuracy/Evasion reduction don't involve stats.
    // LD_hl_B;
    statLevels[c] = b;
    // LD_A_C;
    // CP_A(ACCURACY);
    // IF_NC goto Hit;

    if(c < ACCURACY) {
        // PUSH_HL;
        // LD_HL(wEnemyMonAttack + 1);
        // LD_DE(wEnemyStats);
        // LDH_A_addr(hBattleTurn);
        // AND_A_A;
        // IF_Z goto do_enemy;
        // LD_HL(wBattleMonAttack + 1);
        // LD_DE(wPlayerStats);
        uint16_t *hl = (uint16_t*)((hram->hBattleTurn == 0)? wram_ptr(wEnemyMonAttack): wram_ptr(wBattleMonAttack));

    // do_enemy:
        // CALL(aTryLowerStat);
        // POP_HL;
        // IF_Z goto CouldntLower;
        if(!TryLowerStat(c, hl)) {
        // CouldntLower:
            // INC_hl;
            statLevels[c]++;
            goto CantLower;
        }
    }

// Hit:
    // XOR_A_A;
    // LD_addr_A(wFailedMessage);
    wram->wFailedMessage = 0;
    // RET;
    return;

CantLower:
    // LD_A(3);
    // LD_addr_A(wFailedMessage);
    wram->wFailedMessage = 3;
    // LD_A(1);
    // LD_addr_A(wAttackMissed);
    wram->wAttackMissed = TRUE;
    // RET;
    return;

}

bool CheckMist(void){
    // LD_A(BATTLE_VARS_MOVE_EFFECT);
    // CALL(aGetBattleVar);
    switch(GetBattleVar(BATTLE_VARS_MOVE_EFFECT)) {
        // CP_A(EFFECT_ATTACK_DOWN);
        // IF_C goto dont_check_mist;
        // CP_A(EFFECT_EVASION_DOWN + 1);
        // IF_C goto check_mist;
        // CP_A(EFFECT_ATTACK_DOWN_2);
        // IF_C goto dont_check_mist;
        // CP_A(EFFECT_EVASION_DOWN_2 + 1);
        // IF_C goto check_mist;
        // CP_A(EFFECT_ATTACK_DOWN_HIT);
        // IF_C goto dont_check_mist;
        // CP_A(EFFECT_EVASION_DOWN_HIT + 1);
        // IF_C goto check_mist;

        case EFFECT_EVASION_DOWN + 1:
        case EFFECT_EVASION_DOWN_2 + 1:
        case EFFECT_EVASION_DOWN_HIT + 1:
        // check_mist:
            // LD_A(BATTLE_VARS_SUBSTATUS4_OPP);
            // CALL(aGetBattleVar);
            // BIT_A(SUBSTATUS_MIST);
            // RET;
            return bit_test(GetBattleVar(BATTLE_VARS_SUBSTATUS4_OPP), SUBSTATUS_MIST);
        
        case EFFECT_ATTACK_DOWN:
        case EFFECT_ATTACK_DOWN_2:
        case EFFECT_ATTACK_DOWN_HIT:
        default:
        // dont_check_mist:
            // XOR_A_A;
            // RET;
            return false;
    }

}

static void BattleCommand_StatUpMessage_Function(struct TextCmdState* state);

void BattleCommand_StatUpMessage(void){
    static const txt_cmd_s stat[] = {
        text_far(v_Text_BattleEffectActivate)
        text_asm(BattleCommand_StatUpMessage_Function)
    };

    // LD_A_addr(wFailedMessage);
    // AND_A_A;
    // RET_NZ ;
    if(wram->wFailedMessage)
        return;
    // LD_A_addr(wLoweredStat);
    // AND_A(0xf);
    // LD_B_A;
    // INC_B;
    // CALL(aGetStatName);
    GetStatName(wram->wLoweredStat & 0xf);
    // LD_HL(mBattleCommand_StatUpMessage_stat);
    // JP(mBattleTextbox);
    return BattleTextbox(stat);
}

static void BattleCommand_StatUpMessage_Function(struct TextCmdState* state) {
    static const txt_cmd_s BattleStatWentWayUpText[] = {
        text_far(v_BattleStatWentWayUpText)
        text_end
    };


    static const txt_cmd_s BattleStatWentUpText[] = {
        text_far(v_BattleStatWentUpText)
        text_end
    };
    // LD_HL(mBattleCommand_StatUpMessage_BattleStatWentUpText);
    if((wram->wLoweredStat & 0xf0) == 0) {
        state->hl = BattleStatWentUpText;
        // LD_A_addr(wLoweredStat);
        // AND_A(0xf0);
        // RET_Z ;
    }
    else {
        // LD_HL(mBattleCommand_StatUpMessage_BattleStatWentWayUpText);
        state->hl = BattleStatWentWayUpText;
    }
    // RET;
}

static void BattleCommand_StatDownMessage_Function(struct TextCmdState* state);

void BattleCommand_StatDownMessage(void){
    static const txt_cmd_s stat[] = {
        text_far(v_Text_BattleFoeEffectActivate)
        text_asm(BattleCommand_StatDownMessage_Function)
    };

    // LD_A_addr(wFailedMessage);
    // AND_A_A;
    // RET_NZ ;
    if(wram->wFailedMessage)
        return;
    // LD_A_addr(wLoweredStat);
    // AND_A(0xf);
    // LD_B_A;
    // INC_B;
    // CALL(aGetStatName);
    GetStatName(wram->wLoweredStat & 0xf);
    // LD_HL(mBattleCommand_StatDownMessage_stat);
    // JP(mBattleTextbox);
    return BattleTextbox(stat);
}

static void BattleCommand_StatDownMessage_Function(struct TextCmdState* state) {
    static const txt_cmd_s BattleStatSharplyFellText[] = {
        text_far(v_BattleStatSharplyFellText)
        text_end
    };

    static const txt_cmd_s BattleStatFellText[] = {
        text_far(v_BattleStatFellText)
        text_end
    };

    // LD_HL(mBattleCommand_StatDownMessage_BattleStatFellText);
    if((wram->wLoweredStat & 0xf0) == 0) {
        state->hl = BattleStatFellText;
        // LD_A_addr(wLoweredStat);
        // AND_A(0xf0);
        // RET_Z ;
    }
    else {
        // LD_HL(mBattleCommand_StatDownMessage_BattleStatSharplyFellText);
        state->hl = BattleStatSharplyFellText;
    }
    // RET;
}

//  Lower stat c from stat struct hl (buffer de).
bool TryLowerStat(uint8_t c, uint16_t* hl){
    // PUSH_BC;
    // SLA_C;
    // LD_B(0);
    // ADD_HL_BC;
// add de, c
    // LD_A_C;
    // ADD_A_E;
    // LD_E_A;
    // IF_NC goto no_carry;
    // INC_D;

// no_carry:
    // POP_BC;

//  The lowest possible stat is 1.
    // LD_A_hld;
    uint8_t a = hl[c];
    // SUB_A(1);
    // IF_NZ goto not_min;
    if(a - 1 == 0)
        // LD_A_hl;
        // AND_A_A;
        // RET_Z ;
        return false;

// not_min:
    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // IF_Z goto Player;

    if(hram->hBattleTurn != TURN_PLAYER) {
        // CALL(aBattleCommand_SwitchTurn);
        BattleCommand_SwitchTurn();
        // CALL(aCalcPlayerStats);
        CalcPlayerStats();
        // CALL(aBattleCommand_SwitchTurn);
        BattleCommand_SwitchTurn();
        // goto end;
    }
    else {
    // Player:
        // CALL(aBattleCommand_SwitchTurn);
        BattleCommand_SwitchTurn();
        // CALL(aCalcEnemyStats);
        CalcEnemyStats();
        // CALL(aBattleCommand_SwitchTurn);
        BattleCommand_SwitchTurn();
    }
// end:
    // LD_A(1);
    // AND_A_A;
    // RET;
    return true;
}

void BattleCommand_StatUpFailText(void){
//  statupfailtext
    PEEK("");
    // LD_A_addr(wFailedMessage);
    uint8_t failed = wram->wFailedMessage;
    // AND_A_A;
    // RET_Z ;
    if(!failed)
        return;
    // PUSH_AF;
    // CALL(aBattleCommand_MoveDelay);
    BattleCommand_MoveDelay();
    // POP_AF;
    // DEC_A;
    // JP_Z (mTryPrintButItFailed);
    if(failed == 1) {
        return TryPrintButItFailed();
    }
    else {
        // LD_A_addr(wLoweredStat);
        // AND_A(0xf);
        // LD_B_A;
        // INC_B;
        // CALL(aGetStatName);
        GetStatName((wram->wLoweredStat & 0xf) + 1);
        // LD_HL(mWontRiseAnymoreText);
        // JP(mStdBattleTextbox);
        return StdBattleTextbox(WontRiseAnymoreText);
    }
}

void BattleCommand_StatDownFailText(void){
//  statdownfailtext
    PEEK("");
    // LD_A_addr(wFailedMessage);
    uint8_t failed = wram->wFailedMessage;
    // AND_A_A;
    // RET_Z ;
    if(!failed)
        return;
    // PUSH_AF;
    // CALL(aBattleCommand_MoveDelay);
    BattleCommand_MoveDelay();
    // POP_AF;
    // DEC_A;
    // JP_Z (mTryPrintButItFailed);
    if(failed == 1)
        return TryPrintButItFailed();
    // DEC_A;
    // LD_HL(mProtectedByMistText);
    // JP_Z (mStdBattleTextbox);
    else if(failed == 2)
        return StdBattleTextbox(ProtectedByMistText);
    else {
        // LD_A_addr(wLoweredStat);
        // AND_A(0xf);
        // LD_B_A;
        // INC_B;
        // CALL(aGetStatName);
        GetStatName((wram->wLoweredStat & 0xf) + 1);
        // LD_HL(mWontDropAnymoreText);
        // JP(mStdBattleTextbox);
        return StdBattleTextbox(WontDropAnymoreText);
    }
}

uint8_t* GetStatName(uint8_t b){
    // LD_HL(mStatNames);
    // LD_C(0x50);

// CheckName:
    // DEC_B;
    // IF_Z goto Copy;

// GetName:
    // LD_A_hli;
    // CP_A_C;
    // IF_Z goto CheckName;
    // goto GetName;


// Copy:
    // LD_DE(wStringBuffer2);
    // LD_BC(STRING_BUFFER_LENGTH);
    // JP(mCopyBytes);
    U82CA(wram->wStringBuffer2, StatNames[b]);

// INCLUDE "data/battle/stat_names.asm"

// INCLUDE "data/battle/stat_multipliers.asm"

    return wram->wStringBuffer2;
}

void BattleCommand_AllStatsUp(void){
//  allstatsup

//  Attack
    // CALL(aResetMiss);
    ResetMiss();
    // CALL(aBattleCommand_AttackUp);
    BattleCommand_AttackUp();
    // CALL(aBattleCommand_StatUpMessage);
    BattleCommand_StatUpMessage();

//  Defense
    // CALL(aResetMiss);
    ResetMiss();
    // CALL(aBattleCommand_DefenseUp);
    BattleCommand_DefenseUp();
    // CALL(aBattleCommand_StatUpMessage);
    BattleCommand_StatUpMessage();

//  Speed
    // CALL(aResetMiss);
    ResetMiss();
    // CALL(aBattleCommand_SpeedUp);
    BattleCommand_SpeedUp();
    // CALL(aBattleCommand_StatUpMessage);
    BattleCommand_StatUpMessage();

//  Special Attack
    // CALL(aResetMiss);
    ResetMiss();
    // CALL(aBattleCommand_SpecialAttackUp);
    BattleCommand_SpecialAttackUp();
    // CALL(aBattleCommand_StatUpMessage);
    BattleCommand_StatUpMessage();

//  Special Defense
    // CALL(aResetMiss);
    ResetMiss();
    // CALL(aBattleCommand_SpecialDefenseUp);
    BattleCommand_SpecialDefenseUp();
    // JP(mBattleCommand_StatUpMessage);
    BattleCommand_StatUpMessage();
}

void ResetMiss(void){
    // XOR_A_A;
    // LD_addr_A(wAttackMissed);
    wram->wAttackMissed = FALSE;
    // RET;

}

void LowerStat(uint8_t a){
    // LD_addr_A(wLoweredStat);
    wram->wLoweredStat = a;

    // LD_HL(wPlayerStatLevels);
    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // IF_Z goto got_target;
    // LD_HL(wEnemyStatLevels);
    uint8_t* hl = (hram->hBattleTurn == TURN_PLAYER)? wram->wPlayerStatLevels: wram->wEnemyStatLevels;

// got_target:
    // LD_A_addr(wLoweredStat);
    // AND_A(0xf);
    // LD_C_A;
    uint8_t c = wram->wLoweredStat & 0xf;
    // LD_B(0);
    // ADD_HL_BC;
    // LD_B_hl;
    uint8_t b = hl[c];
    // DEC_B;
    // IF_Z goto cant_lower_anymore;
    if(--b == 0) {
    // cant_lower_anymore:
        // LD_A(2);
        // LD_addr_A(wFailedMessage);
        wram->wFailedMessage = 2;
        // RET;
        return;
    }

    // LD_A_addr(wLoweredStat);
    // AND_A(0xf0);
    // IF_Z goto got_num_stages;
    if(wram->wLoweredStat & 0xf0) {
        // DEC_B;
        // IF_NZ goto got_num_stages;
        // INC_B;
        if(--b == 0) ++b;
    }

// got_num_stages:
    // LD_hl_B;
    hl[c] = b;
    // LD_A_C;
    // CP_A(5);
    // IF_NC goto accuracy_evasion;
    if(c < 5) {
        // PUSH_HL;
        // LD_HL(wBattleMonStats + 1);
        // LD_DE(wPlayerStats);
        // LDH_A_addr(hBattleTurn);
        // AND_A_A;
        // IF_Z goto got_target_2;
        // LD_HL(wEnemyMonStats + 1);
        // LD_DE(wEnemyStats);
        uint16_t *hl2 = (uint16_t*)((hram->hBattleTurn == TURN_PLAYER)? wram_ptr(wEnemyMonAttack): wram_ptr(wBattleMonAttack));
        // uint16_t *de = (uint16_t*)((hram->hBattleTurn == 0)? wram_ptr(wEnemyStats): wram_ptr(wPlayerStats));

    // got_target_2:
        // CALL(aTryLowerStat);
        bool success = TryLowerStat(c, hl2);
        // POP_HL;
        // IF_Z goto failed;
        if(!success) {
        // failed:
            // INC_hl;
            hl[c]++;

        // cant_lower_anymore:
            // LD_A(2);
            // LD_addr_A(wFailedMessage);
            wram->wFailedMessage = 2;
            // RET;
            return;
        }
    }

// accuracy_evasion:
    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // IF_Z goto player;
    if(hram->hBattleTurn != TURN_PLAYER) {
        // CALL(aCalcEnemyStats);
        CalcEnemyStats();
        // goto finish;
    } else {
    // player:
        // CALL(aCalcPlayerStats);
        CalcPlayerStats();
    }
// finish:
    // XOR_A_A;
    // LD_addr_A(wFailedMessage);
    wram->wFailedMessage = 0;
    // RET;
}

void BattleCommand_TriStatusChance(void){
//  tristatuschance

    // CALL(aBattleCommand_EffectChance);
    BattleCommand_EffectChance();

    uint8_t a;
    do {
    // loop:
    // 1/3 chance of each status
        // CALL(aBattleRandom);
        a = v_BattleRandom_Conv();
        // SWAP_A;
        a = (a >> 4) | (a << 4);
        // AND_A(0b11);
        // IF_Z goto loop;
    } while((a & 0b11) == 0);
    // DEC_A;
    --a;
    // LD_HL(mBattleCommand_TriStatusChance_StatusCommands);
    // RST(aJumpTable);
    switch(a) {
        case 0: BattleCommand_ParalyzeTarget(); break;
        case 1: BattleCommand_FreezeTarget(); break;
        case 2: BattleCommand_BurnTarget(); break;
    }
    // RET;
    return;


// StatusCommands:
    //dw ['BattleCommand_ParalyzeTarget'];  // paralyze
    //dw ['BattleCommand_FreezeTarget'];  // freeze
    //dw ['BattleCommand_BurnTarget'];  // burn
}

void BattleCommand_Curl(void){
//  curl
    PEEK("");
    // LD_A(BATTLE_VARS_SUBSTATUS2);
    // CALL(aGetBattleVarAddr);
    // SET_hl(SUBSTATUS_CURLED);
    bit_set(*GetBattleVarAddr(BATTLE_VARS_SUBSTATUS2), SUBSTATUS_CURLED);
    // RET;

}

void BattleCommand_RaiseSubNoAnim(void){
    // LD_HL(mGetBattleMonBackpic);
    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // IF_Z goto PlayerTurn;
    // LD_HL(mGetEnemyMonFrontpic);

// PlayerTurn:
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = BGMAPMODE_NONE;
    // CALL(aCallBattleCore);
    if(hram->hBattleTurn == TURN_PLAYER)
        GetBattleMonBackpic();
    else
        GetEnemyMonFrontpic();
    // JP(mWaitBGMap);
    return WaitBGMap();

}

void BattleCommand_LowerSubNoAnim(void){
    // LD_HL(mDropPlayerSub);
    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // IF_Z goto PlayerTurn;
    // LD_HL(mDropEnemySub);

// PlayerTurn:
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = BGMAPMODE_NONE;
    // CALL(aCallBattleCore);
    if(hram->hBattleTurn == TURN_PLAYER)
        DropPlayerSub();
    else
        DropEnemySub();
    // JP(mWaitBGMap);
    return WaitBGMap();
}

void CalcPlayerStats(void){
    // LD_HL(wPlayerAtkLevel);
    // LD_DE(wPlayerStats);
    // LD_BC(wBattleMonAttack);

    // LD_A(5);
    // CALL(aCalcBattleStats);
    CalcBattleStats(wram->wPlayerStatLevels, (uint16_t*)wram_ptr(wPlayerStats), (uint16_t*)wram_ptr(wBattleMonAttack), 5);

    // LD_HL(mBadgeStatBoosts);
    // CALL(aCallBattleCore);
    BadgeStatBoosts();

    // CALL(aBattleCommand_SwitchTurn);
    BattleCommand_SwitchTurn();

    // LD_HL(mApplyPrzEffectOnSpeed);
    // CALL(aCallBattleCore);
    ApplyPrzEffectOnSpeed_Conv(hram->hBattleTurn);

    // LD_HL(mApplyBrnEffectOnAttack);
    // CALL(aCallBattleCore);
    ApplyBrnEffectOnAttack_Conv(hram->hBattleTurn);

    // JP(mBattleCommand_SwitchTurn);
    BattleCommand_SwitchTurn();
}

void CalcEnemyStats(void){
    // LD_HL(wEnemyAtkLevel);
    // LD_DE(wEnemyStats);
    // LD_BC(wEnemyMonAttack);

    // LD_A(5);
    // CALL(aCalcBattleStats);
    CalcBattleStats(wram->wEnemyStatLevels, (uint16_t*)wram_ptr(wEnemyStats), (uint16_t*)wram_ptr(wEnemyMonAttack), 5);

    // CALL(aBattleCommand_SwitchTurn);
    BattleCommand_SwitchTurn();

    // LD_HL(mApplyPrzEffectOnSpeed);
    // CALL(aCallBattleCore);
    ApplyPrzEffectOnSpeed_Conv(hram->hBattleTurn);

    // LD_HL(mApplyBrnEffectOnAttack);
    // CALL(aCallBattleCore);
    ApplyBrnEffectOnAttack_Conv(hram->hBattleTurn);

    // JP(mBattleCommand_SwitchTurn);
    BattleCommand_SwitchTurn();
}

void CalcBattleStats(uint8_t* hl, uint16_t* de, uint16_t* bc, uint8_t a){
    do {
    // loop:
        // PUSH_AF;
        // LD_A_hli;
        // PUSH_HL;
        // PUSH_BC;

        // LD_C_A;
        // DEC_C;
        uint8_t c = *(hl++);
        // LD_B(0);
        // LD_HL(mStatLevelMultipliers);
        // ADD_HL_BC;
        // ADD_HL_BC;
        const uint8_t* mul = StatLevelMultipliers[c - 1];

        // XOR_A_A;
        // LDH_addr_A(hMultiplicand + 0);
        // LD_A_de;
        // LDH_addr_A(hMultiplicand + 1);
        // INC_DE;
        // LD_A_de;
        // LDH_addr_A(hMultiplicand + 2);
        // INC_DE;

        // LD_A_hli;
        // LDH_addr_A(hMultiplier);
        // CALL(aMultiply);

        uint32_t n = (uint32_t)BigEndianToNative16(*(de++));
        n *= mul[0];

        // LD_A_hl;
        // LDH_addr_A(hDivisor);
        // LD_B(4);
        // CALL(aDivide);

        n /= mul[1];

        // LDH_A_addr(hQuotient + 2);
        // LD_B_A;
        // LDH_A_addr(hQuotient + 3);
        // OR_A_B;
        // IF_NZ goto check_maxed_out;
        if(n == 0) {
            n = 1;
        }

        // LD_A(1);
        // LDH_addr_A(hQuotient + 3);
        // goto not_maxed_out;


    // check_maxed_out:
        // LDH_A_addr(hQuotient + 3);
        // CP_A(LOW(MAX_STAT_VALUE));
        // LD_A_B;
        // SBC_A(HIGH(MAX_STAT_VALUE));
        // IF_C goto not_maxed_out;

        // LD_A(LOW(MAX_STAT_VALUE));
        // LDH_addr_A(hQuotient + 3);
        // LD_A(HIGH(MAX_STAT_VALUE));
        // LDH_addr_A(hQuotient + 2);
        else if(n > MAX_STAT_VALUE) {
            n = MAX_STAT_VALUE;
        }


    // not_maxed_out:
        // POP_BC;
        // LDH_A_addr(hQuotient + 2);
        // LD_bc_A;
        // INC_BC;
        // LDH_A_addr(hQuotient + 3);
        // LD_bc_A;
        // INC_BC;
        *(bc++) = NativeToBigEndian16((uint16_t)n);
        // POP_HL;
        // POP_AF;
        // DEC_A;
        // IF_NZ goto loop;
    } while(--a != 0);

    // RET;

// INCLUDE "engine/battle/move_effects/bide.asm"

}

void BattleCommand_CheckRampage(void){
//  checkrampage
    PEEK("");
    // LD_DE(wPlayerRolloutCount);
    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // IF_Z goto player;
    // LD_DE(wEnemyRolloutCount);
    uint8_t* de =  (hram->hBattleTurn == TURN_PLAYER)? &wram->wPlayerRolloutCount: &wram->wEnemyRolloutCount;
    uint8_t* de2 = (hram->hBattleTurn == TURN_PLAYER)? &wram->wPlayerConfuseCount: &wram->wEnemyConfuseCount;

// player:
    // LD_A(BATTLE_VARS_SUBSTATUS3);
    // CALL(aGetBattleVarAddr);
    uint8_t* hl = GetBattleVarAddr(BATTLE_VARS_SUBSTATUS3);
    // BIT_hl(SUBSTATUS_RAMPAGE);
    // RET_Z ;
    if(!bit_test(*hl, SUBSTATUS_RAMPAGE))
        return;
    // LD_A_de;
    // DEC_A;
    // LD_de_A;
    // IF_NZ goto continue_rampage;

    if(--(*de) == 0) {
        // RES_hl(SUBSTATUS_RAMPAGE);
        bit_reset(*hl, SUBSTATUS_RAMPAGE);
        // CALL(aBattleCommand_SwitchTurn);
        BattleCommand_SwitchTurn();
        // CALL(aSafeCheckSafeguard);
        bool hasSafeguard = SafeCheckSafeguard();
        // PUSH_AF;
        // CALL(aBattleCommand_SwitchTurn);
        BattleCommand_SwitchTurn();
        // POP_AF;
        // IF_NZ goto continue_rampage;
        if(!hasSafeguard) {
            // SET_hl(SUBSTATUS_CONFUSED);
            bit_set(*hl, SUBSTATUS_CONFUSED);
            // CALL(aBattleRandom);
            // AND_A(0b00000001);
            // INC_A;
            // INC_A;
            // INC_DE;  // ConfuseCount
            // LD_de_A;
            *de2 = (v_BattleRandom_Conv() & 0b00000001) + 2;
        }
    }

// continue_rampage:
    // LD_B(rampage_command);
    // JP(mSkipToBattleCommand);
    return SkipToBattleCommand(rampage_command);

}

void BattleCommand_Rampage(void){
//  rampage
    PEEK("");
//  No rampage during Sleep Talk.
    // LD_A(BATTLE_VARS_STATUS);
    // CALL(aGetBattleVar);
    // AND_A(SLP);
    // RET_NZ ;
    if(GetBattleVar(BATTLE_VARS_STATUS) & SLP)
        return;

    // LD_DE(wPlayerRolloutCount);
    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // IF_Z goto ok;
    // LD_DE(wEnemyRolloutCount);
    uint8_t* de = (hram->hBattleTurn == TURN_PLAYER)? &wram->wPlayerRolloutCount: &wram->wEnemyRolloutCount;

// ok:
    // LD_A(BATTLE_VARS_SUBSTATUS3);
    // CALL(aGetBattleVarAddr);
    // SET_hl(SUBSTATUS_RAMPAGE);
    bit_set(*GetBattleVarAddr(BATTLE_VARS_SUBSTATUS3), SUBSTATUS_RAMPAGE);
//  Rampage for 1 or 2 more turns
    // CALL(aBattleRandom);
    // AND_A(0b00000001);
    // INC_A;
    // LD_de_A;
    *de = (v_BattleRandom_Conv() & 1) + 1;
    // LD_A(1);
    // LD_addr_A(wSomeoneIsRampaging);
    wram->wSomeoneIsRampaging = TRUE;
    // RET;

// INCLUDE "engine/battle/move_effects/teleport.asm"

}

void SetBattleDraw(void){
    // LD_A_addr(wBattleResult);
    // AND_A(BATTLERESULT_BITMASK);
    // OR_A(DRAW);
    // LD_addr_A(wBattleResult);
    wram->wBattleResult = (wram->wBattleResult & BATTLERESULT_BITMASK) | DRAW;
    // RET;
}

void BattleCommand_ForceSwitch(void){
//  forceswitch

    // LD_A_addr(wBattleType);
    // CP_A(BATTLETYPE_SHINY);
    // JP_Z (mBattleCommand_ForceSwitch_fail);
    // CP_A(BATTLETYPE_TRAP);
    // JP_Z (mBattleCommand_ForceSwitch_fail);
    // CP_A(BATTLETYPE_CELEBI);
    // JP_Z (mBattleCommand_ForceSwitch_fail);
    // CP_A(BATTLETYPE_SUICUNE);
    // JP_Z (mBattleCommand_ForceSwitch_fail);
    switch(wram->wBattleType) {
        case BATTLETYPE_SHINY:
        case BATTLETYPE_TRAP:
        case BATTLETYPE_CELEBI:
        case BATTLETYPE_SUICUNE:
        fail:
            // CALL(aBattleCommand_LowerSub);
            BattleCommand_LowerSub();
            // CALL(aBattleCommand_MoveDelay);
            BattleCommand_MoveDelay();
            // CALL(aBattleCommand_RaiseSub);
            BattleCommand_RaiseSub();
            // JP(mPrintButItFailed);
            return PrintButItFailed();
        default:
            break;
    }
    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // JP_NZ (mBattleCommand_ForceSwitch_force_player_switch);
    uint8_t anim;
    if(hram->hBattleTurn != TURN_PLAYER) {
    // force_player_switch:
        // LD_A_addr(wAttackMissed);
        // AND_A_A;
        // IF_NZ goto player_miss;
        if(wram->wAttackMissed)
            goto player_miss;

        // LD_A_addr(wBattleMode);
        // DEC_A;
        // IF_NZ goto vs_trainer;
        if(wram->wBattleMode == WILD_BATTLE) {
            // LD_A_addr(wBattleMonLevel);
            // LD_B_A;
            uint8_t b = wram->wBattleMon.level;
            // LD_A_addr(wCurPartyLevel);
            // CP_A_B;
            // IF_NC goto wild_succeed_playeristarget;
            if(wram->wCurPartyLevel < b) {
                // ADD_A_B;
                // LD_C_A;
                // INC_C;
                uint8_t c = b + wram->wCurPartyLevel + 1;

                uint8_t a;
                do {
                // wild_random_loop_playeristarget:
                    // CALL(aBattleRandom);
                    a = v_BattleRandom_Conv();
                    // CP_A_C;
                    // IF_NC goto wild_random_loop_playeristarget;
                } while(a >= c);

                // SRL_B;
                // SRL_B;
                // CP_A_B;
                // IF_NC goto wild_succeed_playeristarget;
                if(a < b >> 2) {
                player_miss:
                    goto fail;
                }
            }

        // wild_succeed_playeristarget:
            // CALL(aUpdateBattleMonInParty);
            UpdateBattleMonInParty();
            // XOR_A_A;
            // LD_addr_A(wNumHits);
            wram->wNumHits = 0;
            // INC_A;  // TRUE
            // LD_addr_A(wForcedSwitch);
            wram->wForcedSwitch = TRUE;
            // CALL(aSetBattleDraw);
            SetBattleDraw();
            // LD_A_addr(wEnemyMoveStructAnimation);
            anim = wram->wEnemyMoveStruct.animation;
            // goto succeed;
        }
        else {
        // vs_trainer:
            // CALL(aCheckPlayerHasMonToSwitchTo);
            // IF_C goto fail;
            if(!CheckPlayerHasMonToSwitchTo())
                goto fail;

            // LD_A_addr(wEnemyGoesFirst);
            // CP_A(0x1);
            // IF_Z goto switch_fail;
            if(wram->wEnemyGoesFirst == 0x1)
                goto switch_fail;

            // CALL(aUpdateBattleMonInParty);
            UpdateBattleMonInParty();
            // LD_A(0x1);
            // LD_addr_A(wBattleAnimParam);
            wram->wBattleAnimParam = 0x1;
            // CALL(aAnimateCurrentMove);
            AnimateCurrentMove();
            // LD_C(20);
            // CALL(aDelayFrames);
            DelayFrames(20);
            // hlcoord(9, 7, wTilemap);
            // LD_BC((5 << 8) | 11);
            // CALL(aClearBox);
            ClearBox(coord(9, 7, wram->wTilemap), 11, 5);
            // LD_C(20);
            // CALL(aDelayFrames);
            DelayFrames(20);
            // LD_A_addr(wPartyCount);
            // LD_B_A;
            uint8_t b = wram->wPartyCount;
            // LD_A_addr(wCurBattleMon);
            // LD_C_A;
            uint8_t c = wram->wCurBattleMon;

            uint8_t a;
            do {
            // random_loop_trainer_playeristarget:
                // CALL(aBattleRandom);
                // AND_A(0x7);
                a = v_BattleRandom_Conv() & 0x7;
                // CP_A_B;
                // IF_NC goto random_loop_trainer_playeristarget;

                // CP_A_C;
                // IF_Z goto random_loop_trainer_playeristarget;
            } while(a >= b || a == c || BigEndianToNative16(wram->wPartyMon[a].HP) == 0);

            // PUSH_AF;
            // PUSH_BC;
            // LD_HL(wPartyMon1HP);
            // CALL(aGetPartyLocation);
            // LD_A_hli;
            // OR_A_hl;
            // POP_BC;
            // POP_DE;
            // IF_Z goto random_loop_trainer_playeristarget;

            // LD_A_D;
            // LD_addr_A(wCurPartyMon);
            wram->wCurPartyMon = a;
            // LD_HL(mSwitchPlayerMon);
            // CALL(aCallBattleCore);
            SwitchPlayerMon();

            // LD_HL(mDraggedOutText);
            // CALL(aStdBattleTextbox);
            StdBattleTextbox(DraggedOutText);

            // LD_HL(mSpikesDamage);
            // JP(mCallBattleCore);
            return SpikesDamage();
        }
    }
    else {
        // LD_A_addr(wAttackMissed);
        // AND_A_A;
        // IF_NZ goto missed;
        if(wram->wAttackMissed)
            goto missed;
        // LD_A_addr(wBattleMode);
        // DEC_A;
        // IF_NZ goto trainer;
        if(wram->wBattleMode != WILD_BATTLE) {
        // trainer:
            // CALL(aFindAliveEnemyMons);
            // IF_C goto switch_fail;
            // LD_A_addr(wEnemyGoesFirst);
            // AND_A_A;
            // IF_Z goto switch_fail;
            if(FindAliveEnemyMons_Conv().flag || !wram->wEnemyGoesFirst) {
            switch_fail:
                // JP(mBattleCommand_ForceSwitch_fail);
                goto fail;
            }
            // CALL(aUpdateEnemyMonInParty);
            UpdateEnemyMonInParty();
            // LD_A(0x1);
            // LD_addr_A(wBattleAnimParam);
            wram->wBattleAnimParam = 0x1;
            // CALL(aAnimateCurrentMove);
            AnimateCurrentMove();
            // LD_C(0x14);
            // CALL(aDelayFrames);
            DelayFrames(0x14);
            // hlcoord(1, 0, wTilemap);
            // LD_BC((4 << 8) | 10);
            // CALL(aClearBox);
            ClearBox(coord(1, 0, wram->wTilemap), 10, 4);
            // LD_C(20);
            // CALL(aDelayFrames);
            DelayFrames(20);
            // LD_A_addr(wOTPartyCount);
            // LD_B_A;
            uint8_t b = wram->wOTPartyCount;
            // LD_A_addr(wCurOTMon);
            // LD_C_A;
            uint8_t c = wram->wCurOTMon;
        //  select a random enemy mon to switch to

            uint8_t a;
            do {
            // random_loop_trainer:
                // CALL(aBattleRandom);
                // AND_A(0x7);
                a = v_BattleRandom_Conv() & 0x7;
                // CP_A_B;
                // IF_NC goto random_loop_trainer;
                // CP_A_C;
                // IF_Z goto random_loop_trainer;
                // PUSH_AF;
                // PUSH_BC;
                // LD_HL(wOTPartyMon1HP);
                // CALL(aGetPartyLocation);
                // LD_A_hli;
                // OR_A_hl;
                // POP_BC;
                // POP_DE;
                // IF_Z goto random_loop_trainer;
            } while(a >= b || a == c || BigEndianToNative16(wram->wOTPartyMon[a].HP) == 0);
            // LD_A_D;
            // INC_A;
            // LD_addr_A(wEnemySwitchMonIndex);
            wram->wEnemySwitchMonIndex = a;
            // CALLFAR(aForceEnemySwitch);
            ForceEnemySwitch();

            // LD_HL(mDraggedOutText);
            // CALL(aStdBattleTextbox);
            StdBattleTextbox(DraggedOutText);

            // LD_HL(mSpikesDamage);
            // JP(mCallBattleCore);
            return SpikesDamage();
        }
        else {
            // LD_A_addr(wCurPartyLevel);
            // LD_B_A;
            uint8_t b = wram->wCurPartyLevel;
            // LD_A_addr(wBattleMonLevel);
            // CP_A_B;
            // IF_NC goto wild_force_flee;
            if(wram->wBattleMon.level < b) {
                // ADD_A_B;
                // LD_C_A;
                // INC_C;
                uint8_t c = b + wram->wBattleMon.level + 1;

                uint8_t a;
                do {
                // random_loop_wild:
                    // CALL(aBattleRandom);
                    a = v_BattleRandom_Conv();
                    // CP_A_C;
                    // IF_NC goto random_loop_wild;
                } while(a >= c);
                // SRL_B;
                // SRL_B;
                // CP_A_B;
                // IF_NC goto wild_force_flee;
                if(a < (b >> 2)) {
                missed:
                    // JP(mBattleCommand_ForceSwitch_fail);
                    goto fail;
                }
            }

        // wild_force_flee:
            // CALL(aUpdateBattleMonInParty);
            UpdateBattleMonInParty();
            // XOR_A_A;
            // LD_addr_A(wNumHits);
            wram->wNumHits = 0;
            // INC_A;  // TRUE
            // LD_addr_A(wForcedSwitch);
            wram->wForcedSwitch = TRUE;
            // CALL(aSetBattleDraw);
            SetBattleDraw();
            // LD_A_addr(wPlayerMoveStructAnimation);
            anim = wram->wPlayerMoveStruct.animation;
            // JP(mBattleCommand_ForceSwitch_succeed);
        }
    }

// succeed:
    // PUSH_AF;
    // CALL(aSetBattleDraw);
    SetBattleDraw();
    // LD_A(0x1);
    // LD_addr_A(wBattleAnimParam);
    wram->wBattleAnimParam = 0x1;
    // CALL(aAnimateCurrentMove);
    AnimateCurrentMove();
    // LD_C(20);
    // CALL(aDelayFrames);
    DelayFrames(20);
    // POP_AF;

    if(anim == ROAR) {
        // LD_HL(mFledInFearText);
        // CP_A(ROAR);
        // IF_Z goto do_text;
    // do_text:
        // JP(mStdBattleTextbox);
        return StdBattleTextbox(FledInFearText);
    }
    else {
        // LD_HL(mBlownAwayText);
    // do_text:
        // JP(mStdBattleTextbox);
        return StdBattleTextbox(BlownAwayText);
    }
}

//  Returns nc (true), if player has another mon to switch to.
bool CheckPlayerHasMonToSwitchTo(void){
    // LD_A_addr(wPartyCount);
    // LD_D_A;
    uint8_t d = wram->wPartyCount;
    // LD_E(0);
    uint8_t e = 0;
    // LD_BC(PARTYMON_STRUCT_LENGTH);

    do {
    // loop:
        // LD_A_addr(wCurBattleMon);
        // CP_A_E;
        // IF_Z goto next;
        if(wram->wCurBattleMon == e)
            continue;

        // LD_A_E;
        // LD_HL(wPartyMon1HP);
        // CALL(aAddNTimes);
        // LD_A_hli;
        // OR_A_hl;
        // IF_NZ goto not_fainted;
        if(BigEndianToNative16(wram->wPartyMon[e].HP) != 0)
            return true;

    // next:
        // INC_E;
        // DEC_D;
        // IF_NZ goto loop;
    } while(++e, --d != 0);

    // SCF;
    // RET;
    return false;

// not_fainted:
    // AND_A_A;
    // RET;
}

void BattleCommand_EndLoop(void){
//  endloop
    PEEK("");
//  Loop back to 'critical'.

// TODO: fix the gotos here.
    uint8_t* bc;
    uint8_t* de;
    if(hram->hBattleTurn == TURN_PLAYER) { 
        // LD_DE(wPlayerRolloutCount);
        de = &wram->wPlayerRolloutCount;
        // LD_BC(wPlayerDamageTaken);
        bc = wram_ptr(wPlayerDamageTaken);
        // LDH_A_addr(hBattleTurn);
        // AND_A_A;
        // IF_Z goto got_addrs;
    }
    else {
        // LD_DE(wEnemyRolloutCount);
        de = &wram->wEnemyRolloutCount;
        // LD_BC(wEnemyDamageTaken);
        bc = wram_ptr(wEnemyDamageTaken);
    }

// got_addrs:

    // LD_A(BATTLE_VARS_SUBSTATUS3);
    // CALL(aGetBattleVarAddr);
    uint8_t* ss3 = GetBattleVarAddr(BATTLE_VARS_SUBSTATUS3);
    // BIT_hl(SUBSTATUS_IN_LOOP);
    // JP_NZ (mBattleCommand_EndLoop_in_loop);
    if(bit_test(*ss3, SUBSTATUS_IN_LOOP)) 
        goto in_loop;
    // SET_hl(SUBSTATUS_IN_LOOP);
    bit_set(*ss3, SUBSTATUS_IN_LOOP);
    // LD_A(BATTLE_VARS_MOVE_EFFECT);
    // CALL(aGetBattleVarAddr);
    uint8_t* eff = GetBattleVarAddr(BATTLE_VARS_MOVE_EFFECT);
    // LD_A_hl;
    uint8_t a;
    switch(*eff) {
        // CP_A(EFFECT_POISON_MULTI_HIT);
        // IF_Z goto twineedle;
        case EFFECT_POISON_MULTI_HIT:
        // twineedle:
            // LD_A(1);
            a = 1;
            goto double_hit;
        // CP_A(EFFECT_DOUBLE_HIT);
        // LD_A(1);
        // IF_Z goto double_hit;
        case EFFECT_DOUBLE_HIT:
            a = 1;
            // goto double_hit;
        double_hit:
            // LD_de_A;
            *de = a;
            // INC_A;
            // LD_bc_A;
            *bc = a + 1;
            goto loop_back_to_critical;
        // LD_A_hl;
        // CP_A(EFFECT_BEAT_UP);
        // IF_Z goto beat_up;
        case EFFECT_BEAT_UP:
            // goto beat_up;
        beat_up:
            // LDH_A_addr(hBattleTurn);
            // AND_A_A;
            // IF_NZ goto check_ot_beat_up;
            if(hram->hBattleTurn != TURN_PLAYER) {
            // check_ot_beat_up:
                // LD_A_addr(wBattleMode);
                // CP_A(WILD_BATTLE);
                // JP_Z (mBattleCommand_EndLoop_only_one_beatup);
                // LD_A_addr(wOTPartyCount);
                // CP_A(1);
                // JP_Z (mBattleCommand_EndLoop_only_one_beatup);
                // DEC_A;
                if(wram->wBattleMode != WILD_BATTLE && wram->wOTPartyCount != 1) {
                    a = wram->wOTPartyCount - 1;
                    goto double_hit;
                }
            }
            else {
                // LD_A_addr(wPartyCount);
                // CP_A(1);
                // JP_Z (mBattleCommand_EndLoop_only_one_beatup);
                // DEC_A;
                if(wram->wPartyCount != 1) {
                    a = wram->wPartyCount - 1;
                    goto double_hit;
                }
            }

        // only_one_beatup:
            // LD_A(BATTLE_VARS_SUBSTATUS3);
            // CALL(aGetBattleVarAddr);
            // RES_hl(SUBSTATUS_IN_LOOP);
            bit_reset(*GetBattleVarAddr(BATTLE_VARS_SUBSTATUS3), SUBSTATUS_IN_LOOP);
            // CALL(aBattleCommand_BeatUpFailText);
            BattleCommand_BeatUpFailText();
            // JP(mEndMoveEffect);
            return EndMoveEffect();
        // CP_A(EFFECT_TRIPLE_KICK);
        // IF_NZ goto not_triple_kick;
        case EFFECT_TRIPLE_KICK:
            do {
            // reject_triple_kick_sample:
                // CALL(aBattleRandom);
                // AND_A(0x3);
                a = v_BattleRandom_Conv() & 0x3;
                // IF_Z goto reject_triple_kick_sample;
            } while(a == 0);
            // DEC_A;
            // IF_NZ goto double_hit;
            if(--a != 0)
                goto double_hit;
            // LD_A(1);
            // LD_bc_A;
            *bc = 1;
            goto done_loop;
        default:
        // not_triple_kick:
            // CALL(aBattleRandom);
            // AND_A(0x3);
            a = v_BattleRandom_Conv() & 0x3;
            // CP_A(2);
            // IF_C goto got_number_hits;
            if(a >= 2) {
                // CALL(aBattleRandom);
                // AND_A(0x3);
                a = v_BattleRandom_Conv() & 0x3;
            }

        // got_number_hits:
            // INC_A;
            a++;
            goto double_hit;
    }


in_loop:
    // LD_A_de;
    // DEC_A;
    // LD_de_A;
    // IF_NZ goto loop_back_to_critical;
    if(--(*de) != 0)
        goto loop_back_to_critical;

done_loop:
    // LD_A(BATTLE_VARS_SUBSTATUS3);
    // CALL(aGetBattleVarAddr);
    // RES_hl(SUBSTATUS_IN_LOOP);
    bit_reset(*GetBattleVarAddr(BATTLE_VARS_SUBSTATUS3), SUBSTATUS_IN_LOOP);

    const struct TextCmd* text;
    if(hram->hBattleTurn == TURN_PLAYER) {
        // LD_HL(mPlayerHitTimesText);
        text = PlayerHitTimesText;
        // LDH_A_addr(hBattleTurn);
        // AND_A_A;
        // IF_Z goto got_hit_n_times_text;
    }
    else {
        // LD_HL(mEnemyHitTimesText);
        text = EnemyHitTimesText;
    }

// got_hit_n_times_text:

    // PUSH_BC;
    // LD_A(BATTLE_VARS_MOVE_EFFECT);
    // CALL(aGetBattleVar);
    // CP_A(EFFECT_BEAT_UP);
    // IF_Z goto beat_up_2;
    if(GetBattleVar(BATTLE_VARS_MOVE_EFFECT) != EFFECT_BEAT_UP) {
        // CALL(aStdBattleTextbox);
        StdBattleTextbox(text);
    }

// beat_up_2:

    // POP_BC;
    // XOR_A_A;
    // LD_bc_A;
    *bc = 0;
    // RET;
    return;


loop_back_to_critical:
    // LD_A_addr(wBattleScriptBufferAddress + 1);
    // LD_H_A;
    // LD_A_addr(wBattleScriptBufferAddress);
    // LD_L_A;

    do {
    // not_critical:
        // LD_A_hld;
        // CP_A(critical_command);
        // IF_NZ goto not_critical;
    } while(wram->wBattleScriptBuffer[wram->wBattleScriptBufferAddress--] != critical_command);
    // INC_HL;
    wram->wBattleScriptBufferAddress++;
    // LD_A_H;
    // LD_addr_A(wBattleScriptBufferAddress + 1);
    // LD_A_L;
    // LD_addr_A(wBattleScriptBufferAddress);
    // RET;
    return;
}

void BattleCommand_FakeOut(void){
    PEEK("");
    // LD_A_addr(wAttackMissed);
    // AND_A_A;
    // RET_NZ ;
    if(wram->wAttackMissed)
        return;

    // CALL(aCheckSubstituteOpp);
    // IF_NZ goto fail;

    // LD_A(BATTLE_VARS_STATUS_OPP);
    // CALL(aGetBattleVar);
    // AND_A(1 << FRZ | SLP);
    // IF_NZ goto fail;

    // CALL(aCheckOpponentWentFirst);
    // JR_Z (mFlinchTarget);
    if(!CheckSubstituteOpp()
    && (GetBattleVar(BATTLE_VARS_STATUS_OPP) & ((1 << FRZ) | SLP)) == 0
    && !CheckOpponentWentFirst()) {
        return FlinchTarget();
    }

    else {
    // fail:
        // LD_A(1);
        // LD_addr_A(wAttackMissed);
        wram->wAttackMissed = TRUE;
        // RET;
        return;
    }
}

void BattleCommand_FlinchTarget(void){
    PEEK("");
    // CALL(aCheckSubstituteOpp);
    // RET_NZ ;
    if(CheckSubstituteOpp())
        return;

    // LD_A(BATTLE_VARS_STATUS_OPP);
    // CALL(aGetBattleVar);
    // AND_A(1 << FRZ | SLP);
    // RET_NZ ;
    if(GetBattleVar(BATTLE_VARS_STATUS_OPP) & ((1 << FRZ) | SLP))
        return;

    // CALL(aCheckOpponentWentFirst);
    // RET_NZ ;
    if(CheckOpponentWentFirst())
        return;

    // LD_A_addr(wEffectFailed);
    // AND_A_A;
    // RET_NZ ;
    if(wram->wEffectFailed)
        return;

// fallthrough

    return FlinchTarget();
}

void FlinchTarget(void){
    // LD_A(BATTLE_VARS_SUBSTATUS3_OPP);
    // CALL(aGetBattleVarAddr);
    // SET_hl(SUBSTATUS_FLINCHED);
    bit_set(*GetBattleVarAddr(BATTLE_VARS_SUBSTATUS3_OPP), SUBSTATUS_FLINCHED);
    // JP(mEndRechargeOpp);
    return EndRechargeOpp();
}

//  Returns a=0, z (false) if user went first
//  Returns a=1, nz (true) if opponent went first
bool CheckOpponentWentFirst(void){
    // PUSH_BC;
    // LD_A_addr(wEnemyGoesFirst);  // 0 if player went first
    // LD_B_A;
    // LDH_A_addr(hBattleTurn);  // 0 if it's the player's turn
    // XOR_A_B;  // 1 if opponent went first
    return (wram->wEnemyGoesFirst ^ hram->hBattleTurn) != 0;
    // POP_BC;
    // RET;

}

void BattleCommand_HeldFlinch(void){
//  kingsrock
    PEEK("");
    // LD_A_addr(wAttackMissed);
    // AND_A_A;
    // RET_NZ ;
    if(wram->wAttackMissed)
        return;

    // CALL(aGetUserItem);
    uint16_t effect = GetUserItem(NULL);
    // LD_A_B;
    // CP_A(HELD_FLINCH);
    // RET_NZ ;
    if(HIGH(effect) != HELD_FLINCH)
        return;

    // CALL(aCheckSubstituteOpp);
    // RET_NZ ;
    if(CheckSubstituteOpp())
        return;
    // LD_A(BATTLE_VARS_MOVE_EFFECT);
    // CALL(aGetBattleVarAddr);
    // LD_D_H;
    // LD_E_L;
    // CALL(aGetUserItem);
    // CALL(aBattleRandom);
    // CP_A_C;
    // RET_NC ;
    if(v_BattleRandom_Conv() >= LOW(effect))
        return;
    // CALL(aEndRechargeOpp);
    EndRechargeOpp();
    // LD_A(BATTLE_VARS_SUBSTATUS3_OPP);
    // CALL(aGetBattleVarAddr);
    // SET_hl(SUBSTATUS_FLINCHED);
    bit_set(*GetBattleVarAddr(BATTLE_VARS_SUBSTATUS3_OPP), SUBSTATUS_FLINCHED);
    // RET;
}

void BattleCommand_OHKO(void){
//  ohko
    PEEK("");
    // CALL(aResetDamage);
    ResetDamage();
    // LD_A_addr(wTypeModifier);
    // AND_A(0x7f);
    // IF_Z goto no_effect;
    if((wram->wTypeModifier & 0x7f) == 0)
        goto no_effect;
    // LD_HL(wEnemyMonLevel);
    uint8_t* hl = (hram->hBattleTurn == TURN_PLAYER)? &wram->wEnemyMon.level: &wram->wBattleMon.level;
    // LD_DE(wBattleMonLevel);
    uint8_t* de = (hram->hBattleTurn == TURN_PLAYER)? &wram->wBattleMon.level: &wram->wEnemyMon.level;
    // LD_BC(wPlayerMoveStruct + MOVE_ACC);
    uint8_t* bc = (hram->hBattleTurn == TURN_PLAYER)? &wram->wPlayerMoveStruct.accuracy: &wram->wEnemyMoveStruct.accuracy;
    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // IF_Z goto got_move_accuracy;
    // PUSH_HL;
    // LD_H_D;
    // LD_L_E;
    // POP_DE;
    // LD_BC(wEnemyMoveStruct + MOVE_ACC);

// got_move_accuracy:
    // LD_A_de;
    // SUB_A_hl;
    // IF_C goto no_effect;
    if(*de < *hl)
        goto no_effect;
    // ADD_A_A;
    // LD_E_A;
    // LD_A_bc;
    // ADD_A_E;
    uint16_t temp = *bc + ((*de - *hl) << 1);
    // IF_NC goto finish_ohko;
    // LD_A(0xff);
    if(temp & 0xff00)
        *bc = 0xff;
    else
    // finish_ohko:
        // LD_bc_A;
        *bc = (temp & 0xff);
    // CALL(aBattleCommand_CheckHit);
    BattleCommand_CheckHit();
    // LD_HL(wCurDamage);
    // LD_A(0xff);
    // LD_hli_A;
    // LD_hl_A;
    wram->wCurDamage = NativeToBigEndian16(0xffff);
    // LD_A(0x2);
    // LD_addr_A(wCriticalHit);
    wram->wCriticalHit = 0x2;
    // RET;
    return;


no_effect:
    // LD_A(0xff);
    // LD_addr_A(wCriticalHit);
    wram->wCriticalHit = 0xff;
    // LD_A(0x1);
    // LD_addr_A(wAttackMissed);
    wram->wAttackMissed = TRUE;
    // RET;

}

void BattleCommand_CheckCharge(void){
//  checkcharge
    PEEK("");
    // LD_A(BATTLE_VARS_SUBSTATUS3);
    // CALL(aGetBattleVarAddr);
    uint8_t* hl = GetBattleVarAddr(BATTLE_VARS_SUBSTATUS3);
    // BIT_hl(SUBSTATUS_CHARGED);
    // RET_Z ;
    if(!bit_test(*hl, SUBSTATUS_CHARGED))
        return;
    // RES_hl(SUBSTATUS_CHARGED);
    bit_reset(*hl, SUBSTATUS_CHARGED);
    // RES_hl(SUBSTATUS_UNDERGROUND);
    bit_reset(*hl, SUBSTATUS_UNDERGROUND);
    // RES_hl(SUBSTATUS_FLYING);
    bit_reset(*hl, SUBSTATUS_FLYING);
    // LD_B(charge_command);
    // JP(mSkipToBattleCommand);
    return SkipToBattleCommand(charge_command);
}

static void BattleCommand_Charge_UsedText_Function(struct TextCmdState* state);
static const txt_cmd_s BattleCommand_Charge_UsedText[] = {
    text_far(v_Text_BattleUser)  // "<USER>"
    text_asm(BattleCommand_Charge_UsedText_Function)
};

static void BattleCommand_Charge_UsedText_Function(struct TextCmdState* state) {
    static const txt_cmd_s BattleMadeWhirlwindText[] = {
        text_far(v_BattleMadeWhirlwindText)
        text_end
    };

    static const txt_cmd_s BattleTookSunlightText[] = {
        text_far(v_BattleTookSunlightText)
        text_end
    };

    static const txt_cmd_s BattleLoweredHeadText[] = {
        text_far(v_BattleLoweredHeadText)
        text_end
    };

    static const txt_cmd_s BattleGlowingText[] = {
        text_far(v_BattleGlowingText)
        text_end
    };

    static const txt_cmd_s BattleFlewText[] = {
        text_far(v_BattleFlewText)
        text_end
    };

    static const txt_cmd_s BattleDugText[] = {
        text_far(v_BattleDugText)
        text_end
    };

    // LD_A(BATTLE_VARS_MOVE_ANIM);
    // CALL(aGetBattleVar);
    switch(GetBattleVar(BATTLE_VARS_MOVE_ANIM)) {
        // CP_A(RAZOR_WIND);
        // LD_HL(mBattleCommand_Charge_BattleMadeWhirlwindText);
        // IF_Z goto done;
        case RAZOR_WIND: state->hl = BattleMadeWhirlwindText; break;

        // CP_A(SOLARBEAM);
        // LD_HL(mBattleCommand_Charge_BattleTookSunlightText);
        // IF_Z goto done;
        case SOLARBEAM: state->hl = BattleTookSunlightText; break;

        // CP_A(SKULL_BASH);
        // LD_HL(mBattleCommand_Charge_BattleLoweredHeadText);
        // IF_Z goto done;
        case SKULL_BASH: state->hl = BattleLoweredHeadText; break;

        // CP_A(SKY_ATTACK);
        // LD_HL(mBattleCommand_Charge_BattleGlowingText);
        // IF_Z goto done;
        case SKY_ATTACK: state->hl = BattleGlowingText; break;

        // CP_A(FLY);
        // LD_HL(mBattleCommand_Charge_BattleFlewText);
        // IF_Z goto done;
        case FLY: state->hl = BattleFlewText; break;

        // CP_A(DIG);
        // LD_HL(mBattleCommand_Charge_BattleDugText);
        default:
        case DIG: state->hl = BattleDugText; break;
    }

// done:
    // RET;
}

void BattleCommand_Charge(void){
//  charge
    PEEK("");
    // CALL(aBattleCommand_ClearText);
    BattleCommand_ClearText();
    // LD_A(BATTLE_VARS_STATUS);
    // CALL(aGetBattleVar);
    // AND_A(SLP);
    // IF_Z goto awake;

    if(GetBattleVar(BATTLE_VARS_STATUS) & SLP) {
        // CALL(aBattleCommand_MoveDelay);
        BattleCommand_MoveDelay();
        // CALL(aBattleCommand_RaiseSub);
        BattleCommand_RaiseSub();
        // CALL(aPrintButItFailed);
        PrintButItFailed();
        // JP(mEndMoveEffect);
        return EndMoveEffect();
    }

// awake:
    // LD_A(BATTLE_VARS_SUBSTATUS3);
    // CALL(aGetBattleVarAddr);
    // SET_hl(SUBSTATUS_CHARGED);
    bit_set(*GetBattleVarAddr(BATTLE_VARS_SUBSTATUS3), SUBSTATUS_CHARGED);

    // LD_HL(mIgnoredOrders2Text);
    // LD_A_addr(wAlreadyDisobeyed);
    // AND_A_A;
    // CALL_NZ (aStdBattleTextbox);
    if(wram->wAlreadyDisobeyed)
        StdBattleTextbox(IgnoredOrders2Text);

    // CALL(aBattleCommand_LowerSub);
    BattleCommand_LowerSub();
    // XOR_A_A;
    // LD_addr_A(wNumHits);
    wram->wNumHits = 0;
    // INC_A;
    // LD_addr_A(wBattleAnimParam);
    wram->wBattleAnimParam = 1;
    // CALL(aLoadMoveAnim);
    LoadMoveAnim();
    // LD_A(BATTLE_VARS_MOVE_ANIM);
    // CALL(aGetBattleVar);
    uint8_t anim = GetBattleVar(BATTLE_VARS_MOVE_ANIM);
    // CP_A(FLY);
    // IF_Z goto flying;
    // CP_A(DIG);
    // IF_Z goto flying;
    if(anim == FLY || anim == DIG) {
    // flying:
        // CALL(aDisappearUser);
        DisappearUser();
    }
    else {
        // CALL(aBattleCommand_RaiseSub);
        BattleCommand_RaiseSub();
        // goto not_flying;
    }

// not_flying:
    // LD_A(BATTLE_VARS_SUBSTATUS3);
    // CALL(aGetBattleVarAddr);
    uint8_t* ss3 = GetBattleVarAddr(BATTLE_VARS_SUBSTATUS3);
    // LD_A(BATTLE_VARS_MOVE_ANIM);
    // CALL(aGetBattleVar);
    anim = GetBattleVar(BATTLE_VARS_MOVE_ANIM); // Maybe delete this since we already have the animation?
    // LD_B_A;
    // CP_A(FLY);
    // IF_Z goto set_flying;
    // CP_A(DIG);
    // IF_NZ goto dont_set_digging;
    if(anim == DIG) {
        // SET_hl(SUBSTATUS_UNDERGROUND);
        bit_set(*ss3, SUBSTATUS_UNDERGROUND);
        // goto dont_set_digging;
    }
    else if(anim == FLY) {
    // set_flying:
        // SET_hl(SUBSTATUS_FLYING);
        bit_set(*ss3, SUBSTATUS_FLYING);
    }

// dont_set_digging:
    // CALL(aCheckUserIsCharging);
    // IF_NZ goto mimic;
    if(!CheckUserIsCharging()) {
        // LD_A(BATTLE_VARS_LAST_COUNTER_MOVE);
        // CALL(aGetBattleVarAddr);
        // LD_hl_B;
        *GetBattleVarAddr(BATTLE_VARS_LAST_COUNTER_MOVE) = anim;
        // LD_A(BATTLE_VARS_LAST_MOVE);
        // CALL(aGetBattleVarAddr);
        // LD_hl_B;
        *GetBattleVarAddr(BATTLE_VARS_LAST_MOVE) = anim;
    }

// mimic:
    // CALL(aResetDamage);
    ResetDamage();

    // LD_HL(mBattleCommand_Charge_UsedText);
    // CALL(aBattleTextbox);
    BattleTextbox(BattleCommand_Charge_UsedText);

    // LD_A(BATTLE_VARS_MOVE_EFFECT);
    // CALL(aGetBattleVar);
    // CP_A(EFFECT_SKULL_BASH);
    // LD_B(endturn_command);
    // JP_Z (mSkipToBattleCommand);
    if(GetBattleVar(BATTLE_VARS_MOVE_EFFECT) == EFFECT_SKULL_BASH) {
        return SkipToBattleCommand(endturn_command);
    }
    // JP(mEndMoveEffect);
    return EndMoveEffect();
}

void BattleCommand_Unused3C(void){
//  effect0x3c
    // RET;
    return;
}

struct MoveText {
    move_t move;
    const struct TextCmd* text; 
};

void BattleCommand_TrapTarget(void){
//  traptarget
    PEEK("");
    static const struct MoveText Traps[] = {
        {BIND, UsedBindText},  // 'used BIND on'
        {WRAP, WrappedByText},  // 'was WRAPPED by'
        {FIRE_SPIN, FireSpinTrapText},  // 'was trapped!'
        {CLAMP, ClampedByText},  // 'was CLAMPED by'
        {WHIRLPOOL, WhirlpoolTrapText},  // 'was trapped!'
    };
    // LD_A_addr(wAttackMissed);
    // AND_A_A;
    // RET_NZ ;
    if(wram->wAttackMissed)
        return;
    uint8_t* hl;
    move_t* de;
    if(hram->hBattleTurn == TURN_PLAYER) {
        // LD_HL(wEnemyWrapCount);
        hl = &wram->wEnemyWrapCount;
        // LD_DE(wEnemyTrappingMove);
        de = &wram->wEnemyTrappingMove;
        // LDH_A_addr(hBattleTurn);
        // AND_A_A;
        // IF_Z goto got_trap;
    }
    else {
        // LD_HL(wPlayerWrapCount);
        hl = &wram->wPlayerWrapCount;
        // LD_DE(wPlayerTrappingMove);
        de = &wram->wPlayerTrappingMove;
    }

// got_trap:
    // LD_A_hl;
    // AND_A_A;
    // RET_NZ ;
    if(*hl != 0)
        return;
    // LD_A(BATTLE_VARS_SUBSTATUS4_OPP);
    // CALL(aGetBattleVar);
    // BIT_A(SUBSTATUS_SUBSTITUTE);
    // RET_NZ ;
    if(bit_test(GetBattleVar(BATTLE_VARS_SUBSTATUS4_OPP), SUBSTATUS_SUBSTITUTE))
        return;
    // CALL(aBattleRandom);
// trapped for 2-5 turns
    // AND_A(0b11);
    // INC_A;
    // INC_A;
    // INC_A;
    // LD_hl_A;
    *hl = (v_BattleRandom_Conv() & 0b11) + 3;
    // LD_A(BATTLE_VARS_MOVE_ANIM);
    // CALL(aGetBattleVar);
    uint8_t b = GetBattleVar(BATTLE_VARS_MOVE_ANIM);
    // LD_de_A;
    *de = b;
    // LD_B_A;
    // LD_HL(mBattleCommand_TrapTarget_Traps);
    const struct MoveText* traps = Traps;

    while(traps->move != b) {
    // find_trap_text:
        // LD_A_hli;
        // CP_A_B;
        // IF_Z goto found_trap_text;
        // INC_HL;
        // INC_HL;
        // goto find_trap_text;
        traps++;
    }


// found_trap_text:
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // JP(mStdBattleTextbox);
    return StdBattleTextbox(traps->text);

// INCLUDE "engine/battle/move_effects/mist.asm"

// INCLUDE "engine/battle/move_effects/focus_energy.asm"

}

void BattleCommand_Recoil(void){
//  recoil
    PEEK("");
    // LD_HL(wBattleMonMaxHP);
    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // IF_Z goto got_hp;
    // LD_HL(wEnemyMonMaxHP);
    uint16_t* hp = (hram->hBattleTurn == TURN_PLAYER)? (uint16_t*)wram_ptr(wBattleMonHP): (uint16_t*)wram_ptr(wEnemyMonHP);
    uint16_t* maxHP = (hram->hBattleTurn == TURN_PLAYER)? (uint16_t*)wram_ptr(wBattleMonMaxHP): (uint16_t*)wram_ptr(wEnemyMonMaxHP);

// got_hp:
    // LD_A(BATTLE_VARS_MOVE_ANIM);
    // CALL(aGetBattleVar);
    // LD_D_A;
    gBattleCmdState.d = GetBattleVar(BATTLE_VARS_MOVE_ANIM);
//  get 1/4 damage or 1 HP, whichever is higher
    // LD_A_addr(wCurDamage);
    // LD_B_A;
    // LD_A_addr(wCurDamage + 1);
    // LD_C_A;
    uint16_t bc = BigEndianToNative16(wram->wCurDamage);
    // SRL_B;
    // RR_C;
    // SRL_B;
    // RR_C;
    bc >>= 2;
    // LD_A_B;
    // OR_A_C;
    // IF_NZ goto min_damage;
    if(bc == 0) {
        // INC_C;
        bc = 1;
    }

// min_damage:
    // LD_A_hli;
    // LD_addr_A(wHPBuffer1 + 1);
    // LD_A_hl;
    // LD_addr_A(wHPBuffer1);
    wram->wHPBuffer1 = BigEndianToNative16(*maxHP);
    // DEC_HL;
    // DEC_HL;
    // LD_A_hl;
    // LD_addr_A(wHPBuffer2);
    // SUB_A_C;
    // LD_hld_A;
    // LD_addr_A(wHPBuffer3);
    // LD_A_hl;
    // LD_addr_A(wHPBuffer2 + 1);
    // SBC_A_B;
    // LD_hl_A;
    // LD_addr_A(wHPBuffer3 + 1);
    wram->wHPBuffer2 = BigEndianToNative16(*hp);
    // IF_NC goto dont_ko;
    if(wram->wHPBuffer2 < bc) {
        // XOR_A_A;
        // LD_hli_A;
        // LD_hl_A;
        *hp = NativeToBigEndian16(0);
        // LD_HL(wHPBuffer3);
        // LD_hli_A;
        // LD_hl_A;
        wram->wHPBuffer3 = 0;
    }
    else {
        *hp = NativeToBigEndian16(wram->wHPBuffer2 - bc);
        wram->wHPBuffer3 = wram->wHPBuffer2 - bc;
    }

// dont_ko:
    tile_t* hl;
    uint8_t which;
    if(hram->hBattleTurn == TURN_PLAYER) {
        // hlcoord(10, 9, wTilemap);
        hl = coord(10, 9, wram->wTilemap);
        // LDH_A_addr(hBattleTurn);
        // AND_A_A;
        // LD_A(1);
        which = 1;
        // IF_Z goto animate_hp_bar;
    }
    else {
        // hlcoord(2, 2, wTilemap);
        hl = coord(2, 2, wram->wTilemap);
        // XOR_A_A;
        which = 0;
    }
// animate_hp_bar:
    // LD_addr_A(wWhichHPBar);
    // PREDEF(pAnimateHPBar);
    AnimateHPBar_Conv(hl, which);
    // CALL(aRefreshBattleHuds);
    RefreshBattleHuds();
    // LD_HL(mRecoilText);
    // JP(mStdBattleTextbox);
    return StdBattleTextbox(RecoilText);

}

void BattleCommand_ConfuseTarget(void){
//  confusetarget
    PEEK("");
    // CALL(aGetOpponentItem);
    // LD_A_B;
    // CP_A(HELD_PREVENT_CONFUSE);
    // RET_Z ;
    if(HIGH(GetOpponentItem(NULL)) == HELD_PREVENT_CONFUSE)
        return;
    // LD_A_addr(wEffectFailed);
    // AND_A_A;
    // RET_NZ ;
    // CALL(aSafeCheckSafeguard);
    // RET_NZ ;
    // CALL(aCheckSubstituteOpp);
    // RET_NZ ;
    if(wram->wEffectFailed || SafeCheckSafeguard() || CheckSubstituteOpp())
        return;
    // LD_A(BATTLE_VARS_SUBSTATUS3_OPP);
    // CALL(aGetBattleVarAddr);
    uint8_t* hl = GetBattleVarAddr(BATTLE_VARS_SUBSTATUS3_OPP);
    // BIT_hl(SUBSTATUS_CONFUSED);
    // RET_NZ ;
    if(bit_test(*hl, SUBSTATUS_CONFUSED))
        return;
    // JR(mBattleCommand_FinishConfusingTarget);
    return BattleCommand_FinishConfusingTarget(hl);

}

void BattleCommand_Confuse(void){
//  confuse
    PEEK("");
    // CALL(aGetOpponentItem);
    // LD_A_B;
    // CP_A(HELD_PREVENT_CONFUSE);
    // IF_NZ goto no_item_protection;
    item_t item;
    if(HIGH(GetOpponentItem(&item)) == HELD_PREVENT_CONFUSE) {
        // LD_A_hl;
        // LD_addr_A(wNamedObjectIndex);
        // CALL(aGetItemName);
        GetItemName(item);
        // CALL(aAnimateFailedMove);
        AnimateFailedMove();
        // LD_HL(mProtectedByText);
        // JP(mStdBattleTextbox);
        return StdBattleTextbox(ProtectedByText);
    }

// no_item_protection:
    // LD_A(BATTLE_VARS_SUBSTATUS3_OPP);
    // CALL(aGetBattleVarAddr);
    uint8_t* hl = GetBattleVarAddr(BATTLE_VARS_SUBSTATUS3_OPP);
    // BIT_hl(SUBSTATUS_CONFUSED);
    // IF_Z goto not_already_confused;
    if(bit_test(*hl, SUBSTATUS_CONFUSED)) {
        // CALL(aAnimateFailedMove);
        AnimateFailedMove();
        // LD_HL(mAlreadyConfusedText);
        // JP(mStdBattleTextbox);
        return StdBattleTextbox(AlreadyConfusedText);
    }

// not_already_confused:
    // CALL(aCheckSubstituteOpp);
    // JR_NZ (mBattleCommand_Confuse_CheckSnore_Swagger_ConfuseHit);
    // LD_A_addr(wAttackMissed);
    // AND_A_A;
    // JR_NZ (mBattleCommand_Confuse_CheckSnore_Swagger_ConfuseHit);
    if(CheckSubstituteOpp() || wram->wAttackMissed)
        return BattleCommand_Confuse_CheckSnore_Swagger_ConfuseHit();
    return BattleCommand_FinishConfusingTarget(hl);
}

void BattleCommand_FinishConfusingTarget(uint8_t* hl){
    // LD_BC(wEnemyConfuseCount);
    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // IF_Z goto got_confuse_count;
    // LD_BC(wPlayerConfuseCount);
    uint8_t* bc = (hram->hBattleTurn == TURN_PLAYER)? &wram->wEnemyConfuseCount: &wram->wPlayerConfuseCount;

// got_confuse_count:
    // SET_hl(SUBSTATUS_CONFUSED);
    bit_set(*hl, SUBSTATUS_CONFUSED);
// confused for 2-5 turns
    // CALL(aBattleRandom);
    // AND_A(0b11);
    // INC_A;
    // INC_A;
    // LD_bc_A;
    *bc = (v_BattleRandom_Conv() & 0b11) + 2;

    // LD_A(BATTLE_VARS_MOVE_EFFECT);
    // CALL(aGetBattleVar);
    uint8_t effect = GetBattleVar(BATTLE_VARS_MOVE_EFFECT);
    // CP_A(EFFECT_CONFUSE_HIT);
    // IF_Z goto got_effect;
    // CP_A(EFFECT_SNORE);
    // IF_Z goto got_effect;
    // CP_A(EFFECT_SWAGGER);
    // IF_Z goto got_effect;
    if(effect != EFFECT_CONFUSE_HIT && effect != EFFECT_SNORE && effect != EFFECT_SWAGGER) {
        // CALL(aAnimateCurrentMove);
        AnimateCurrentMove();
    }

// got_effect:
    // LD_DE(ANIM_CONFUSED);
    // CALL(aPlayOpponentBattleAnim);
    PlayOpponentBattleAnim(ANIM_CONFUSED);

    // LD_HL(mBecameConfusedText);
    // CALL(aStdBattleTextbox);
    StdBattleTextbox(BecameConfusedText);

    // CALL(aGetOpponentItem);
    // LD_A_B;
    uint8_t item_effect = HIGH(GetOpponentItem(NULL));
    // CP_A(HELD_HEAL_STATUS);
    // IF_Z goto heal_confusion;
    // CP_A(HELD_HEAL_CONFUSION);
    // RET_NZ ;
    if(item_effect == HELD_HEAL_STATUS || item_effect == HELD_HEAL_CONFUSION) {
    // heal_confusion:
        // LD_HL(mUseConfusionHealingItem);
        // JP(mCallBattleCore);
        return UseConfusionHealingItem();
    }
}

void BattleCommand_Confuse_CheckSnore_Swagger_ConfuseHit(void){
    // LD_A(BATTLE_VARS_MOVE_EFFECT);
    // CALL(aGetBattleVar);
    uint8_t effect = GetBattleVar(BATTLE_VARS_MOVE_EFFECT);
    // CP_A(EFFECT_CONFUSE_HIT);
    // RET_Z ;
    // CP_A(EFFECT_SNORE);
    // RET_Z ;
    // CP_A(EFFECT_SWAGGER);
    // RET_Z ;
    if(effect == EFFECT_CONFUSE_HIT
    || effect == EFFECT_SNORE
    || effect == EFFECT_SWAGGER)
        return;
    // JP(mPrintDidntAffect2);
    return PrintDidntAffect2();
}

void BattleCommand_Paralyze(void){
//  paralyze
    PEEK("");
    // LD_A(BATTLE_VARS_STATUS_OPP);
    // CALL(aGetBattleVar);
    // BIT_A(PAR);
    // IF_NZ goto paralyzed;
    if(bit_test(GetBattleVar(BATTLE_VARS_STATUS_OPP), PAR)) {
    // paralyzed:
        // CALL(aAnimateFailedMove);
        AnimateFailedMove();
        // LD_HL(mAlreadyParalyzedText);
        // JP(mStdBattleTextbox);
        return StdBattleTextbox(AlreadyParalyzedText);
    }
    // LD_A_addr(wTypeModifier);
    // AND_A(0x7f);
    // IF_Z goto didnt_affect;
    if((wram->wTypeModifier & 0x7f) == 0) {
    // didnt_affect:
        // CALL(aAnimateFailedMove);
        AnimateFailedMove();
        // JP(mPrintDoesntAffect);
        return PrintDoesntAffect();
    }
    // CALL(aGetOpponentItem);
    // LD_A_B;
    // CP_A(HELD_PREVENT_PARALYZE);
    // IF_NZ goto no_item_protection;
    item_t item;
    if(HIGH(GetOpponentItem(&item)) == HELD_PREVENT_PARALYZE) {
        // LD_A_hl;
        // LD_addr_A(wNamedObjectIndex);
        // CALL(aGetItemName);
        GetItemName(item);
        // CALL(aAnimateFailedMove);
        AnimateFailedMove();
        // LD_HL(mProtectedByText);
        // JP(mStdBattleTextbox);
        return StdBattleTextbox(ProtectedByText);
    }

// no_item_protection:
    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // IF_Z goto dont_sample_failure;

    // LD_A_addr(wLinkMode);
    // AND_A_A;
    // IF_NZ goto dont_sample_failure;

    // LD_A_addr(wInBattleTowerBattle);
    // AND_A_A;
    // IF_NZ goto dont_sample_failure;

    // LD_A_addr(wPlayerSubStatus5);
    // BIT_A(SUBSTATUS_LOCK_ON);
    // IF_NZ goto dont_sample_failure;

    if(hram->hBattleTurn != TURN_PLAYER
    && wram->wLinkMode == LINK_NULL
    && wram->wInBattleTowerBattle == 0
    && !bit_test(wram->wPlayerSubStatus5, SUBSTATUS_LOCK_ON)) {
        // CALL(aBattleRandom);
        // CP_A(25 percent + 1);  // 25% chance AI fails
        // IF_C goto failed;
        if(v_BattleRandom_Conv() < 25 percent + 1)
            goto failed;
    }

// dont_sample_failure:
    // LD_A(BATTLE_VARS_STATUS_OPP);
    // CALL(aGetBattleVarAddr);
    uint8_t* hl = GetBattleVarAddr(BATTLE_VARS_STATUS_OPP);
    // AND_A_A;
    // IF_NZ goto failed;
    // LD_A_addr(wAttackMissed);
    // AND_A_A;
    // IF_NZ goto failed;
    // CALL(aCheckSubstituteOpp);
    // IF_NZ goto failed;
    if(*hl == 0
    && !wram->wAttackMissed
    && !CheckSubstituteOpp()) {
        // LD_C(30);
        // CALL(aDelayFrames);
        DelayFrames(30);
        // CALL(aAnimateCurrentMove);
        AnimateCurrentMove();
        // LD_A(0x1);
        // LDH_addr_A(hBGMapMode);
        hram->hBGMapMode = BGMAPMODE_UPDATE_TILES;
        // LD_A(BATTLE_VARS_STATUS_OPP);
        // CALL(aGetBattleVarAddr);
        // SET_hl(PAR);
        bit_set(*GetBattleVarAddr(BATTLE_VARS_STATUS_OPP), PAR);
        // CALL(aUpdateOpponentInParty);
        UpdateOpponentInParty();
        // LD_HL(mApplyPrzEffectOnSpeed);
        // CALL(aCallBattleCore);
        ApplyPrzEffectOnSpeed();
        // CALL(aUpdateBattleHuds);
        UpdateBattleHuds();
        // CALL(aPrintParalyze);
        PrintParalyze();
        // LD_HL(mUseHeldStatusHealingItem);
        // JP(mCallBattleCore);
        UseHeldStatusHealingItem();
        return;
    }

failed:
    // JP(mPrintDidntAffect2);
    return PrintDidntAffect2();
}

//  Compare move type to opponent type.
//  Return z (true) if matching the opponent type,
//  unless the move is Normal (Tri Attack).
bool CheckMoveTypeMatchesTarget(void){
    // PUSH_HL;

    // LD_HL(wEnemyMonType1);
    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // IF_Z goto ok;
    // LD_HL(wBattleMonType1);
    uint8_t* mon_types = (hram->hBattleTurn == TURN_PLAYER)? wram->wEnemyMon.types: wram->wBattleMon.types;

// ok:

    // LD_A(BATTLE_VARS_MOVE_TYPE);
    // CALL(aGetBattleVar);
    uint8_t move_type = GetBattleVar(BATTLE_VARS_MOVE_TYPE);
    // CP_A(NORMAL);
    // IF_Z goto normal;
    if(move_type == NORMAL) {
    // normal:
        // LD_A(1);
        // AND_A_A;
        // POP_HL;
        // RET;
        return false;
    }

    // CP_A_hl;
    // IF_Z goto l_return;

    // INC_HL;
    // CP_A_hl;


// l_return:
    // POP_HL;
    // RET;
    return mon_types[0] == move_type || mon_types[1] == move_type;

// INCLUDE "engine/battle/move_effects/substitute.asm"

}

void BattleCommand_RechargeNextTurn(void){
//  rechargenextturn
    PEEK("");
    // LD_A(BATTLE_VARS_SUBSTATUS4);
    // CALL(aGetBattleVarAddr);
    // SET_hl(SUBSTATUS_RECHARGE);
    bit_set(*GetBattleVarAddr(BATTLE_VARS_SUBSTATUS4), SUBSTATUS_RECHARGE);
    // RET;
}

void EndRechargeOpp(void){
    // PUSH_HL;
    // LD_A(BATTLE_VARS_SUBSTATUS4_OPP);
    // CALL(aGetBattleVarAddr);
    // RES_hl(SUBSTATUS_RECHARGE);
    bit_reset(*GetBattleVarAddr(BATTLE_VARS_SUBSTATUS4_OPP), SUBSTATUS_RECHARGE);
    // POP_HL;
    // RET;

// INCLUDE "engine/battle/move_effects/rage.asm"
}

void BattleCommand_DoubleFlyingDamage(void){
//  doubleflyingdamage
    PEEK("");
    // LD_A(BATTLE_VARS_SUBSTATUS3_OPP);
    // CALL(aGetBattleVar);
    // BIT_A(SUBSTATUS_FLYING);
    // RET_Z ;
    if(!bit_test(GetBattleVar(BATTLE_VARS_SUBSTATUS3_OPP), SUBSTATUS_FLYING))
        return;
    
    // JR(mDoubleDamage);
    return DoubleDamage();
}

void BattleCommand_DoubleUndergroundDamage(void){
//  doubleundergrounddamage
    PEEK("");
    // LD_A(BATTLE_VARS_SUBSTATUS3_OPP);
    // CALL(aGetBattleVar);
    // BIT_A(SUBSTATUS_UNDERGROUND);
    // RET_Z ;
    if(!bit_test(GetBattleVar(BATTLE_VARS_SUBSTATUS3_OPP), SUBSTATUS_UNDERGROUND))
        return;

// fallthrough

    return DoubleDamage();
}

void DoubleDamage(void){
    // LD_HL(wCurDamage + 1);
    uint16_t dmg = BigEndianToNative16(wram->wCurDamage);
    // SLA_hl;
    // DEC_HL;
    // RL_hl;
    // IF_NC goto quit;
    if((uint32_t)dmg << 1 > 0xffffu) {
        // LD_A(0xff);
        // LD_hli_A;
        // LD_hl_A;
        wram->wCurDamage = NativeToBigEndian16(0xffff);
    }
    else {
        dmg <<= 1;
        wram->wCurDamage = NativeToBigEndian16(wram->wCurDamage);
    }
// quit:
    // RET;

// INCLUDE "engine/battle/move_effects/mimic.asm"

// INCLUDE "engine/battle/move_effects/leech_seed.asm"

// INCLUDE "engine/battle/move_effects/splash.asm"

// INCLUDE "engine/battle/move_effects/disable.asm"

// INCLUDE "engine/battle/move_effects/pay_day.asm"

// INCLUDE "engine/battle/move_effects/conversion.asm"

}

static void BattleCommand_ResetStats_Fill(uint8_t* hl, uint8_t a) {
    // LD_B(NUM_LEVEL_STATS);

    for(uint8_t b = 0; b < NUM_LEVEL_STATS; ++b) {
    // next:
        // LD_hli_A;
        hl[b] = a;
        // DEC_B;
        // IF_NZ goto next;
    }
    // RET;
}

void BattleCommand_ResetStats(void){
//  resetstats
    PEEK("");
    // LD_A(BASE_STAT_LEVEL);
    // LD_HL(wPlayerStatLevels);
    // CALL(aBattleCommand_ResetStats_Fill);
    BattleCommand_ResetStats_Fill(wram->wPlayerStatLevels, BASE_STAT_LEVEL);
    // LD_HL(wEnemyStatLevels);
    // CALL(aBattleCommand_ResetStats_Fill);
    BattleCommand_ResetStats_Fill(wram->wEnemyStatLevels, BASE_STAT_LEVEL);

    // LDH_A_addr(hBattleTurn);
    // PUSH_AF;
    uint8_t turn = hram->hBattleTurn;

    // CALL(aSetPlayerTurn);
    SetPlayerTurn();
    // CALL(aCalcPlayerStats);
    CalcPlayerStats();
    // CALL(aSetEnemyTurn);
    SetEnemyTurn();
    // CALL(aCalcEnemyStats);
    CalcEnemyStats();

    // POP_AF;
    // LDH_addr_A(hBattleTurn);
    hram->hBattleTurn = turn;

    // CALL(aAnimateCurrentMove);
    AnimateCurrentMove();

    // LD_HL(mEliminatedStatsText);
    // JP(mStdBattleTextbox);
    return StdBattleTextbox(EliminatedStatsText);
}

void BattleCommand_Heal(void){
//  heal
    PEEK("");
    // LD_DE(wBattleMonHP);
    // LD_HL(wBattleMonMaxHP);
    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // IF_Z goto got_hp;
    // LD_DE(wEnemyMonHP);
    // LD_HL(wEnemyMonMaxHP);
    uint16_t hp = BigEndianToNative16((hram->hBattleTurn == TURN_PLAYER)? wram->wBattleMon.hp: wram->wEnemyMon.hp);
    uint16_t maxhp = BigEndianToNative16((hram->hBattleTurn == TURN_PLAYER)? wram->wBattleMon.maxHP: wram->wEnemyMon.maxHP);

// got_hp:
    // LD_A(BATTLE_VARS_MOVE_ANIM);
    // CALL(aGetBattleVar);
    // LD_B_A;
    uint8_t b = GetBattleVar(BATTLE_VARS_MOVE_ANIM);
    // PUSH_HL;
    // PUSH_DE;
    // PUSH_BC;
    // LD_C(2);
    // CALL(aCompareBytes);
    // POP_BC;
    // POP_DE;
    // POP_HL;
    // JP_Z (mBattleCommand_Heal_hp_full);
    if(hp == maxhp) {
    // hp_full:
        // CALL(aAnimateFailedMove);
        AnimateFailedMove();
        // LD_HL(mHPIsFullText);
        // JP(mStdBattleTextbox);
        return StdBattleTextbox(HPIsFullText);
    }
    // LD_A_B;
    // CP_A(REST);
    // IF_NZ goto not_rest;
    uint16_t bc;
    if(b == REST) {
        // PUSH_HL;
        // PUSH_DE;
        // PUSH_AF;
        // CALL(aBattleCommand_MoveDelay);
        BattleCommand_MoveDelay();
        // LD_A(BATTLE_VARS_SUBSTATUS5);
        // CALL(aGetBattleVarAddr);
        uint8_t* hl = GetBattleVarAddr(BATTLE_VARS_SUBSTATUS5);
        // RES_hl(SUBSTATUS_TOXIC);
        bit_set(*hl, SUBSTATUS_TOXIC);
        // LD_A(BATTLE_VARS_STATUS);
        // CALL(aGetBattleVarAddr);
        hl = GetBattleVarAddr(BATTLE_VARS_STATUS);
        // LD_A_hl;
        // AND_A_A;
        uint8_t slp = *hl;
        // LD_hl(REST_SLEEP_TURNS + 1);
        *hl = REST_SLEEP_TURNS + 1;

        if(slp == 0) {
            // LD_HL(mWentToSleepText);
            // IF_Z goto no_status_to_heal;
            StdBattleTextbox(WentToSleepText);
        }
        else {
            // LD_HL(mRestedText);
            StdBattleTextbox(RestedText);
        }

    // no_status_to_heal:
        // CALL(aStdBattleTextbox);
        // LDH_A_addr(hBattleTurn);
        // AND_A_A;
        // IF_NZ goto calc_enemy_stats;
        if(hram->hBattleTurn == TURN_PLAYER) {
            // CALL(aCalcPlayerStats);
            CalcPlayerStats();
            // goto got_stats;
        }
        else {
        // calc_enemy_stats:
            // CALL(aCalcEnemyStats);
            CalcEnemyStats();
        }

    // got_stats:
        // POP_AF;
        // POP_DE;
        // POP_HL;

    // restore_full_hp:
        // LD_HL(mGetMaxHP);
        // CALL(aCallBattleCore);
        bc = GetMaxHP_Conv();
    }
    else {
    // not_rest:
        // IF_Z goto restore_full_hp;
        // LD_HL(mGetHalfMaxHP);
        // CALL(aCallBattleCore);
        bc = GetHalfMaxHP_Conv();
        // goto finish;
    }

// finish:
    // CALL(aAnimateCurrentMove);
    AnimateCurrentMove();
    // CALL(aBattleCommand_SwitchTurn);
    BattleCommand_SwitchTurn();
    // LD_HL(mRestoreHP);
    // CALL(aCallBattleCore);
    RestoreHP_Conv(bc);
    // CALL(aBattleCommand_SwitchTurn);
    BattleCommand_SwitchTurn();
    // CALL(aUpdateUserInParty);
    UpdateUserInParty();
    // CALL(aRefreshBattleHuds);
    RefreshBattleHuds();
    // LD_HL(mRegainedHealthText);
    // JP(mStdBattleTextbox);
    return StdBattleTextbox(RegainedHealthText);

// INCLUDE "engine/battle/move_effects/transform.asm"
}

void BattleEffect_ButItFailed(void){
    // CALL(aAnimateFailedMove);
    AnimateFailedMove();
    // JP(mPrintButItFailed);

    return PrintButItFailed();
}

void ClearLastMove(void){
    // LD_A(BATTLE_VARS_LAST_COUNTER_MOVE);
    // CALL(aGetBattleVarAddr);
    // XOR_A_A;
    // LD_hl_A;
    *GetBattleVarAddr(BATTLE_VARS_LAST_COUNTER_MOVE) = NO_MOVE;

    // LD_A(BATTLE_VARS_LAST_MOVE);
    // CALL(aGetBattleVarAddr);
    // XOR_A_A;
    // LD_hl_A;
    *GetBattleVarAddr(BATTLE_VARS_LAST_MOVE) = NO_MOVE;
    // RET;
}

void ResetActorDisable(void){
    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // IF_Z goto player;

    if(hram->hBattleTurn != TURN_PLAYER) {
        // XOR_A_A;
        // LD_addr_A(wEnemyDisableCount);
        wram->wEnemyDisableCount = 0;
        // LD_addr_A(wEnemyDisabledMove);
        wram->wEnemyDisabledMove = NO_MOVE;
        // RET;
    }
    else {
    // player:
        // XOR_A_A;
        // LD_addr_A(wPlayerDisableCount);
        wram->wPlayerDisableCount = 0;
        // LD_addr_A(wDisabledMove);
        wram->wDisabledMove = NO_MOVE;
        // RET;
    }
}

void BattleCommand_Screen(void){
//  screen
    PEEK("");
    // LD_HL(wPlayerScreens);
    // LD_BC(wPlayerLightScreenCount);
    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // IF_Z goto got_screens_pointer;
    // LD_HL(wEnemyScreens);
    uint8_t* hl = (hram->hBattleTurn == TURN_PLAYER)? &wram->wPlayerScreens: &wram->wEnemyScreens;
    // LD_BC(wEnemyLightScreenCount);
    uint8_t* ls_cnt = (hram->hBattleTurn == TURN_PLAYER)? &wram->wPlayerLightScreenCount: &wram->wEnemyLightScreenCount;
    uint8_t* rf_cnt = (hram->hBattleTurn == TURN_PLAYER)? &wram->wPlayerReflectCount: &wram->wEnemyReflectCount;


// got_screens_pointer:
    // LD_A(BATTLE_VARS_MOVE_EFFECT);
    // CALL(aGetBattleVar);
    // CP_A(EFFECT_LIGHT_SCREEN);
    // IF_NZ goto Reflect;
    if(GetBattleVar(BATTLE_VARS_MOVE_EFFECT) == EFFECT_LIGHT_SCREEN) {
        // BIT_hl(SCREENS_LIGHT_SCREEN);
        // IF_NZ goto failed;
        if(bit_test(*hl, SCREENS_LIGHT_SCREEN)) {
        // failed:
            // CALL(aAnimateFailedMove);
            AnimateFailedMove();
            // JP(mPrintButItFailed);
            return PrintButItFailed();
        }
        // SET_hl(SCREENS_LIGHT_SCREEN);
        bit_set(*hl, SCREENS_LIGHT_SCREEN);
        // LD_A(5);
        // LD_bc_A;
        *ls_cnt = 5;
        // LD_HL(mLightScreenEffectText);
        // goto good;
        AnimateCurrentMove();
        return StdBattleTextbox(LightScreenEffectText);
    }
    else {
    // Reflect:
        // BIT_hl(SCREENS_REFLECT);
        // IF_NZ goto failed;
        if(bit_test(*hl, SCREENS_REFLECT)) {
        // failed:
            // CALL(aAnimateFailedMove);
            AnimateFailedMove();
            // JP(mPrintButItFailed);
            return PrintButItFailed();
        }
        // SET_hl(SCREENS_REFLECT);
        bit_set(*hl, SCREENS_REFLECT);

    // LightScreenCount -> ReflectCount
        // INC_BC;

        // LD_A(5);
        // LD_bc_A;
        *rf_cnt = 5;
        // LD_HL(mReflectEffectText);
        AnimateCurrentMove();
        return StdBattleTextbox(ReflectEffectText);
    }

// good:
    // CALL(aAnimateCurrentMove);
    // JP(mStdBattleTextbox);


// failed:
    // CALL(aAnimateFailedMove);
    // JP(mPrintButItFailed);

}

void PrintDoesntAffect(void){
//  'it doesn't affect'
    // LD_HL(mDoesntAffectText);
    // JP(mStdBattleTextbox);
    return StdBattleTextbox(DoesntAffectText);
}

void PrintNothingHappened(void){
//  'but nothing happened!'
    // LD_HL(mNothingHappenedText);
    // JP(mStdBattleTextbox);
    return StdBattleTextbox(NothingHappenedText);
}

void TryPrintButItFailed(void){
    // LD_A_addr(wAlreadyFailed);
    // AND_A_A;
    // RET_NZ ;
    if(wram->wAlreadyFailed)
        return;

// fallthrough

    return PrintButItFailed();
}

void PrintButItFailed(void){
//  'but it failed!'
    // LD_HL(mButItFailedText);
    // JP(mStdBattleTextbox);
    return StdBattleTextbox(ButItFailedText);
}

void FailMove(void){
    // CALL(aAnimateFailedMove);
    AnimateFailedMove();
// fallthrough

    return FailMimic();
}

void FailMimic(void){
    // LD_HL(mButItFailedText);  // 'but it failed!'
    // LD_DE(mItFailedText);  // 'it failed!'
    // JP(mFailText_CheckOpponentProtect);
    return FailText_CheckOpponentProtect(ButItFailedText, ItFailedText);
}

void PrintDidntAffect(void){
//  'it didn't affect'
    // LD_HL(mDidntAffect1Text);
    // JP(mStdBattleTextbox);
    return StdBattleTextbox(DidntAffect1Text);
}

void PrintDidntAffect2(void){
    // CALL(aAnimateFailedMove);
    AnimateFailedMove();
    // LD_HL(mDidntAffect1Text);  // 'it didn't affect'
    // LD_DE(mDidntAffect2Text);  // 'it didn't affect'
    // JP(mFailText_CheckOpponentProtect);
    return FailText_CheckOpponentProtect(DidntAffect1Text, DidntAffect2Text);
}

void PrintParalyze(void){
//  'paralyzed! maybe it can't attack!'
    // LD_HL(mParalyzedText);
    // JP(mStdBattleTextbox);
    return StdBattleTextbox(ParalyzedText);
}

bool CheckSubstituteOpp(void){
    // LD_A(BATTLE_VARS_SUBSTATUS4_OPP);
    // CALL(aGetBattleVar);
    // BIT_A(SUBSTATUS_SUBSTITUTE);
    // RET;
    return bit_test(GetBattleVar(BATTLE_VARS_SUBSTATUS4_OPP), SUBSTATUS_SUBSTITUTE);

// INCLUDE "engine/battle/move_effects/selfdestruct.asm"

// INCLUDE "engine/battle/move_effects/mirror_move.asm"

// INCLUDE "engine/battle/move_effects/metronome.asm"
}

//  Return z (true) if the user has move a.
bool CheckUserMove(move_t a){
    // LD_B_A;
    // LD_DE(wBattleMonMoves);
    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // IF_Z goto ok;
    // LD_DE(wEnemyMonMoves);
    const move_t* de = (hram->hBattleTurn == TURN_PLAYER)? wram->wBattleMon.moves: wram->wEnemyMon.moves;

// ok:

    // LD_C(NUM_MOVES);

    for(int i = 0; i < NUM_MOVES; ++i) {
    // loop:
        // LD_A_de;
        // INC_DE;
        // CP_A_B;
        // RET_Z ;
        if(de[i] == a)
            return true;

        // DEC_C;
        // IF_NZ goto loop;
    }

    // LD_A(1);
    // AND_A_A;
    // RET;
    return false;
}

void ResetTurn(void){
    // LD_HL(wPlayerCharging);
    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // IF_Z goto player;
    // LD_HL(wEnemyCharging);
    uint8_t* hl = (hram->hBattleTurn == TURN_PLAYER)? &wram->wPlayerCharging: &wram->wEnemyCharging;


// player:
    // LD_hl(1);
    *hl = TRUE;
    // XOR_A_A;
    // LD_addr_A(wAlreadyDisobeyed);
    wram->wAlreadyDisobeyed = FALSE;
    // CALL(aDoMove);
    DoMove();
    // JP(mEndMoveEffect);
    return EndMoveEffect();

// INCLUDE "engine/battle/move_effects/thief.asm"
}

void BattleCommand_ArenaTrap(void){
//  arenatrap
    PEEK("");
//  Doesn't work on an absent opponent.

    // CALL(aCheckHiddenOpponent);
    // IF_NZ goto failed;
    if(!CheckHiddenOpponent()) {
    //  Don't trap if the opponent is already trapped.
        // LD_A(BATTLE_VARS_SUBSTATUS5);
        // CALL(aGetBattleVarAddr);
        uint8_t* hl = GetBattleVarAddr(BATTLE_VARS_SUBSTATUS5);
        // BIT_hl(SUBSTATUS_CANT_RUN);
        // IF_NZ goto failed;
        if(!bit_test(*hl, SUBSTATUS_CANT_RUN)) {
        //  Otherwise trap the opponent.
            // SET_hl(SUBSTATUS_CANT_RUN);
            bit_set(*hl, SUBSTATUS_CANT_RUN);
            // CALL(aAnimateCurrentMove);
            AnimateCurrentMove();
            // LD_HL(mCantEscapeNowText);
            // JP(mStdBattleTextbox);
            return StdBattleTextbox(CantEscapeNowText);
        }
    }

// failed:
    // CALL(aAnimateFailedMove);
    AnimateFailedMove();
    // JP(mPrintButItFailed);
    return PrintButItFailed();

// INCLUDE "engine/battle/move_effects/nightmare.asm"

}

void BattleCommand_Defrost(void){
//  defrost
    PEEK("");
//  Thaw the user.

    // LD_A(BATTLE_VARS_STATUS);
    // CALL(aGetBattleVarAddr);
    uint8_t* hl = GetBattleVarAddr(BATTLE_VARS_STATUS);
    // BIT_hl(FRZ);
    // RET_Z ;
    if(!bit_test(*hl, FRZ))
        return;
    // RES_hl(FRZ);
    bit_reset(*hl, FRZ);

//  Don't update the enemy's party struct in a wild battle.

    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // IF_Z goto party;

    // LD_A_addr(wBattleMode);
    // DEC_A;
    // IF_Z goto done;
    if(hram->hBattleTurn == TURN_PLAYER || wram->wBattleMode != WILD_BATTLE) {
    // party:
        // LD_A(MON_STATUS);
        // CALL(aUserPartyAttr);
        // RES_hl(FRZ);
        bit_reset(UserPartyMon()->status, FRZ);
    }


// done:
    // CALL(aRefreshBattleHuds);
    RefreshBattleHuds();
    // LD_HL(mWasDefrostedText);
    // JP(mStdBattleTextbox);
    StdBattleTextbox(WasDefrostedText);

// INCLUDE "engine/battle/move_effects/curse.asm"

// INCLUDE "engine/battle/move_effects/protect.asm"

// INCLUDE "engine/battle/move_effects/endure.asm"

// INCLUDE "engine/battle/move_effects/spikes.asm"

// INCLUDE "engine/battle/move_effects/foresight.asm"

// INCLUDE "engine/battle/move_effects/perish_song.asm"

// INCLUDE "engine/battle/move_effects/sandstorm.asm"

// INCLUDE "engine/battle/move_effects/rollout.asm"
}

void BattleCommand_Unused5D(void){
//  effect0x5d
    // RET;
    return;

// INCLUDE "engine/battle/move_effects/fury_cutter.asm"

// INCLUDE "engine/battle/move_effects/attract.asm"

// INCLUDE "engine/battle/move_effects/return.asm"

// INCLUDE "engine/battle/move_effects/present.asm"

// INCLUDE "engine/battle/move_effects/frustration.asm"

// INCLUDE "engine/battle/move_effects/safeguard.asm"
}

bool SafeCheckSafeguard(void){
    // PUSH_HL;
    // LD_HL(wEnemyScreens);
    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // IF_Z goto got_turn;
    // LD_HL(wPlayerScreens);

    if(hram->hBattleTurn == TURN_PLAYER) {
        return bit_test(wram->wEnemyScreens, SCREENS_SAFEGUARD);
    }
    else {
        return bit_test(wram->wPlayerScreens, SCREENS_SAFEGUARD);
    }
// got_turn:
    // BIT_hl(SCREENS_SAFEGUARD);
    // POP_HL;
    // RET;
}

void BattleCommand_CheckSafeguard(void){
//  checksafeguard
    PEEK("");
    // LD_HL(wEnemyScreens);
    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // IF_Z goto got_turn;
    // LD_HL(wPlayerScreens);
    uint8_t screens = (hram->hBattleTurn == TURN_PLAYER)? wram->wEnemyScreens: wram->wPlayerScreens;

// got_turn:
    // BIT_hl(SCREENS_SAFEGUARD);
    // RET_Z ;
    if(bit_test(screens, SCREENS_SAFEGUARD)) {
        // LD_A(1);
        // LD_addr_A(wAttackMissed);
        wram->wAttackMissed = 1;
        // CALL(aBattleCommand_MoveDelay);
        BattleCommand_MoveDelay();
        // LD_HL(mSafeguardProtectText);
        // CALL(aStdBattleTextbox);
        StdBattleTextbox(SafeguardProtectText);
        // JP(mEndMoveEffect);
        return EndMoveEffect();
    }

// INCLUDE "engine/battle/move_effects/magnitude.asm"

// INCLUDE "engine/battle/move_effects/baton_pass.asm"

// INCLUDE "engine/battle/move_effects/pursuit.asm"

// INCLUDE "engine/battle/move_effects/rapid_spin.asm"

}

void BattleCommand_HealMorn(void){
//  healmorn
    PEEK("");
    // LD_B(MORN_F);
    // JR(mBattleCommand_TimeBasedHealContinue);

    return BattleCommand_TimeBasedHealContinue(MORN_F);
}

void BattleCommand_HealDay(void){
//  healday
    PEEK("");
    // LD_B(DAY_F);
    // JR(mBattleCommand_TimeBasedHealContinue);

    return BattleCommand_TimeBasedHealContinue(DAY_F);
}

void BattleCommand_HealNite(void){
//  healnite
    PEEK("");
    // LD_B(NITE_F);
// fallthrough

    return BattleCommand_TimeBasedHealContinue(NITE_F);
}

void BattleCommand_TimeBasedHealContinue(uint8_t b){
//  Time- and weather-sensitive heal.

    static uint16_t (*const Multipliers[])(void) = {
        &GetEighthMaxHP_Conv,
        &GetQuarterMaxHP_Conv,
        &GetHalfMaxHP_Conv,
        &GetMaxHP_Conv
    };

    // LD_HL(wBattleMonMaxHP);
    // LD_DE(wBattleMonHP);
    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // IF_Z goto start;
    // LD_HL(wEnemyMonMaxHP);
    // LD_DE(wEnemyMonHP);
    uint16_t maxHP = BigEndianToNative16((hram->hBattleTurn == TURN_PLAYER)? wram->wBattleMon.maxHP: wram->wEnemyMon.maxHP);
    uint16_t hp = BigEndianToNative16((hram->hBattleTurn == TURN_PLAYER)? wram->wBattleMon.hp: wram->wEnemyMon.hp);


// start:
//  Index for .Multipliers
//  Default restores half max HP.
    // LD_C(2);
    uint8_t c = 2;

//  Don't bother healing if HP is already full.
    // PUSH_BC;
    // CALL(aCompareBytes);
    // POP_BC;
    // IF_Z goto Full;
    if(hp == maxHP) {
    // Full:
        // CALL(aAnimateFailedMove);
        AnimateFailedMove();

    //  'hp is full!'
        // LD_HL(mHPIsFullText);
        // JP(mStdBattleTextbox);
        return StdBattleTextbox(HPIsFullText);
    }

//  Don't factor in time of day in link battles.
    // LD_A_addr(wLinkMode);
    // AND_A_A;
    // IF_NZ goto Weather;
    if(wram->wLinkMode == LINK_NULL) {
        // LD_A_addr(wTimeOfDay);
        // CP_A_B;
        // IF_Z goto Weather;
        // DEC_C;  // double
        if(wram->wTimeOfDay == b)
            c--;
    }

// Weather:
    // LD_A_addr(wBattleWeather);
    // AND_A_A;
    // IF_Z goto Heal;
    if(wram->wBattleWeather != 0) {
    //  x2 in sun
    //  /2 in rain/sandstorm
        // INC_C;
        // CP_A(WEATHER_SUN);
        // IF_Z goto Heal;
        if(wram->wBattleWeather == WEATHER_SUN)
            c++;
        else {
            // DEC_C;
            // DEC_C;
            c--;
        }
    }

// Heal:
    // LD_B(0);
    // LD_HL(mBattleCommand_TimeBasedHealContinue_Multipliers);
    // ADD_HL_BC;
    // ADD_HL_BC;

    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // LD_A(BANK(aGetMaxHP));
    // RST(aFarCall);
    uint16_t bc = Multipliers[c]();

    // CALL(aAnimateCurrentMove);
    AnimateCurrentMove();
    // CALL(aBattleCommand_SwitchTurn);
    BattleCommand_SwitchTurn();

    // CALLFAR(aRestoreHP);
    RestoreHP_Conv(bc);

    // CALL(aBattleCommand_SwitchTurn);
    BattleCommand_SwitchTurn();
    // CALL(aUpdateUserInParty);
    UpdateUserInParty();

//  'regained health!'
    // LD_HL(mRegainedHealthText);
    // JP(mStdBattleTextbox);
    return StdBattleTextbox(RegainedHealthText);

// INCLUDE "engine/battle/move_effects/hidden_power.asm"

// INCLUDE "engine/battle/move_effects/rain_dance.asm"

// INCLUDE "engine/battle/move_effects/sunny_day.asm"

// INCLUDE "engine/battle/move_effects/belly_drum.asm"

// INCLUDE "engine/battle/move_effects/psych_up.asm"

// INCLUDE "engine/battle/move_effects/mirror_coat.asm"

}

void BattleCommand_DoubleMinimizeDamage(void){
//  doubleminimizedamage
    PEEK("");
    // LD_HL(wEnemyMinimized);
    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // IF_Z goto ok;
    // LD_HL(wPlayerMinimized);
    uint8_t minimized = (hram->hBattleTurn == TURN_PLAYER)? wram->wEnemyMinimized: wram->wPlayerMinimized;

// ok:
    // LD_A_hl;
    // AND_A_A;
    // RET_Z ;
    if(minimized) {
        // LD_HL(wCurDamage + 1);
        // SLA_hl;
        // DEC_HL;
        // RL_hl;
        // RET_NC ;
        if((BigEndianToNative16(wram->wCurDamage) << 1) > 0xffff) {
            // LD_A(0xff);
            // LD_hli_A;
            // LD_hl_A;
            wram->wCurDamage = NativeToBigEndian16(0xffff);
        }
        else {
            wram->wCurDamage = NativeToBigEndian16(BigEndianToNative16(wram->wCurDamage) << 1);
        }
    }
    // RET;
}

void BattleCommand_SkipSunCharge(void){
//  mimicsuncharge
    PEEK("");
    // LD_A_addr(wBattleWeather);
    // CP_A(WEATHER_SUN);
    // RET_NZ ;
    if(wram->wBattleWeather != WEATHER_SUN)
        return;
    // LD_B(charge_command);
    // JP(mSkipToBattleCommand);
    return SkipToBattleCommand(charge_command);

// INCLUDE "engine/battle/move_effects/future_sight.asm"

// INCLUDE "engine/battle/move_effects/thunder.asm"
}

//  BUG: This routine is completely redundant and introduces a bug, since BattleCommand_CheckHit does these checks properly.
bool CheckHiddenOpponent(void){
#if BUGFIX_CHECKHIDDENOPPONENT
    return false;
#else
    // LD_A(BATTLE_VARS_SUBSTATUS3_OPP);
    // CALL(aGetBattleVar);
    // AND_A(1 << SUBSTATUS_FLYING | 1 << SUBSTATUS_UNDERGROUND);
    // RET;
    return (GetBattleVar(BATTLE_VARS_SUBSTATUS3_OPP) & (1 << SUBSTATUS_FLYING | 1 << SUBSTATUS_UNDERGROUND)) != 0;
#endif
}

uint16_t GetUserItem(item_t* hl){
//  Return the effect of the user's item in bc, and its id at hl.
    item_t itm;
    // LD_HL(wBattleMonItem);
    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // IF_Z goto go;
    // LD_HL(wEnemyMonItem);
    if(hl == NULL)
        hl = &itm;
    
    *hl = (hram->hBattleTurn == TURN_PLAYER)? wram->wBattleMon.item: wram->wEnemyMon.item;

// go:
    // LD_B_hl;
    // JP(mGetItemHeldEffect);
    return GetItemHeldEffect(*hl);
}

uint16_t GetOpponentItem(item_t* hl){
//  Return the effect of the opponent's item in bc, and its id at hl.
    item_t item;
    // LD_HL(wEnemyMonItem);
    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // IF_Z goto go;
    // LD_HL(wBattleMonItem);
    if(hl == NULL)
        hl = &item;

    *hl = (hram->hBattleTurn == TURN_PLAYER)? wram->wEnemyMon.item: wram->wBattleMon.item;

// go:
    // LD_B_hl;
    // JP(mGetItemHeldEffect);
    return GetItemHeldEffect(*hl);
}

uint16_t GetItemHeldEffect(item_t b){
//  Return the effect of item b in bc.
    // LD_A_B;
    // AND_A_A;
    // RET_Z ;
    if(b == NO_ITEM)
        return 0;

    // PUSH_HL;
    // LD_HL(mItemAttributes + ITEMATTR_EFFECT);
    // DEC_A;
    // LD_C_A;
    // LD_B(0);
    // LD_A(ITEMATTR_STRUCT_LENGTH);
    // CALL(aAddNTimes);
    // LD_A(BANK(aItemAttributes));
    // CALL(aGetFarWord);
    // LD_B_L;
    // LD_C_H;
    uint16_t bc = (ItemAttributes[b].effect << 8) | ItemAttributes[b].param;
    // POP_HL;
    // RET;
    return bc;
}

void AnimateCurrentMoveEitherSide(void){
    // PUSH_HL;
    // PUSH_DE;
    // PUSH_BC;
    // LD_A_addr(wBattleAnimParam);
    // PUSH_AF;
    uint8_t param = wram->wBattleAnimParam;
    // CALL(aBattleCommand_LowerSub);
    BattleCommand_LowerSub();
    // POP_AF;
    // LD_addr_A(wBattleAnimParam);
    wram->wBattleAnimParam = param;
    // CALL(aPlayDamageAnim);
    PlayDamageAnim();
    // CALL(aBattleCommand_RaiseSub);
    BattleCommand_RaiseSub();
    // POP_BC;
    // POP_DE;
    // POP_HL;
    // RET;
}

void AnimateCurrentMove(void){
    // PUSH_HL;
    // PUSH_DE;
    // PUSH_BC;
    // LD_A_addr(wBattleAnimParam);
    // PUSH_AF;
    uint8_t param = wram->wBattleAnimParam;
    // CALL(aBattleCommand_LowerSub);
    BattleCommand_LowerSub();
    // POP_AF;
    // LD_addr_A(wBattleAnimParam);
    wram->wBattleAnimParam = param;
    // CALL(aLoadMoveAnim);
    LoadMoveAnim();
    // CALL(aBattleCommand_RaiseSub);
    BattleCommand_RaiseSub();
    // POP_BC;
    // POP_DE;
    // POP_HL;
    // RET;

}

void PlayDamageAnim(void){
    // XOR_A_A;
    // LD_addr_A(wFXAnimID + 1);

    // LD_A(BATTLE_VARS_MOVE_ANIM);
    uint8_t anim = GetBattleVar(BATTLE_VARS_MOVE_ANIM);
    // CALL(aGetBattleVar);
    // AND_A_A;
    // RET_Z ;
    if(anim == 0)
        return;

    // LD_addr_A(wFXAnimID);
    wram->wFXAnimID = anim;

    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // LD_A(BATTLEANIM_ENEMY_DAMAGE);
    // IF_Z goto player;
    // LD_A(BATTLEANIM_PLAYER_DAMAGE);


// player:
    // LD_addr_A(wNumHits);
    wram->wNumHits = (hram->hBattleTurn == TURN_PLAYER)? BATTLEANIM_ENEMY_DAMAGE: BATTLEANIM_PLAYER_DAMAGE;

    // JP(mPlayUserBattleAnim);
    return PlayUserBattleAnim();
}

void LoadMoveAnim(void){
    // XOR_A_A;
    // LD_addr_A(wNumHits);
    wram->wNumHits = 0;
    // LD_addr_A(wFXAnimID + 1);
    wram->wFXAnimID &= 0xff;

    // LD_A(BATTLE_VARS_MOVE_ANIM);
    // CALL(aGetBattleVar);
    uint8_t a = GetBattleVar(BATTLE_VARS_MOVE_ANIM);
    // AND_A_A;
    // RET_Z ;
    if(a == 0)
        return;

// fallthrough

    return LoadAnim(a);
}

void LoadAnim(uint8_t a){
    // LD_addr_A(wFXAnimID);
    wram->wFXAnimID = (wram->wFXAnimID & 0xff00) | a;

// fallthrough

    return PlayUserBattleAnim();
}

void PlayUserBattleAnim(void){
    // PUSH_HL;
    // PUSH_DE;
    // PUSH_BC;
    // CALLFAR(aPlayBattleAnim);
    PlayBattleAnim();
    // POP_BC;
    // POP_DE;
    // POP_HL;
    // RET;
}

void PlayOpponentBattleAnim(uint16_t de){
    // LD_A_E;
    // LD_addr_A(wFXAnimID);
    // LD_A_D;
    // LD_addr_A(wFXAnimID + 1);
    wram->wFXAnimID = de;
    // XOR_A_A;
    // LD_addr_A(wNumHits);
    wram->wNumHits = 0;

    // PUSH_HL;
    // PUSH_DE;
    // PUSH_BC;
    // CALL(aBattleCommand_SwitchTurn);
    BattleCommand_SwitchTurn();

    // CALLFAR(aPlayBattleAnim);
    PlayBattleAnim();

    // CALL(aBattleCommand_SwitchTurn);
    BattleCommand_SwitchTurn();
    // POP_BC;
    // POP_DE;
    // POP_HL;
    // RET;
}

void CallBattleCore(void){
    LD_A(BANK(aDoBattle)); // AKA BANK("Battle Core")
    RST(aFarCall);
    RET;

}

void AnimateFailedMove(void){
    // CALL(aBattleCommand_LowerSub);
    BattleCommand_LowerSub();
    // CALL(aBattleCommand_MoveDelay);
    BattleCommand_MoveDelay();
    // JP(mBattleCommand_RaiseSub);
    BattleCommand_RaiseSub();

}

void BattleCommand_MoveDelay(void){
//  movedelay
//  Wait 40 frames.
    // LD_C(40);
    // JP(mDelayFrames);
    DelayFrames(40);
}

void BattleCommand_ClearText(void){
//  cleartext

//  Used in multi-hit moves.
    // LD_HL(mBattleCommand_ClearText_text);
    // JP(mBattleTextbox);
    BattleTextbox((const struct TextCmd[]){
        text_end
    });

// text:
    //text_end ['?']
}

void SkipToBattleCommand(uint8_t b){
//  Skip over commands until reaching command b.
    // LD_A_addr(wBattleScriptBufferAddress + 1);
    // LD_H_A;
    // LD_A_addr(wBattleScriptBufferAddress);
    // LD_L_A;

    do {
    // loop:
        // LD_A_hli;
        // CP_A_B;
        // IF_NZ goto loop;
    } while(wram->wBattleScriptBuffer[wram->wBattleScriptBufferAddress++] != b);

    // LD_A_H;
    // LD_addr_A(wBattleScriptBufferAddress + 1);
    // LD_A_L;
    // LD_addr_A(wBattleScriptBufferAddress);
    // RET;
}

//  Assuming hl = Moves + x, return attribute x of move a.
const struct Move* GetMoveAttr(move_t a){
    // PUSH_BC;
    // LD_BC(MOVE_LENGTH);
    // CALL(aAddNTimes);
    // CALL(aGetMoveByte);
    // POP_BC;
    // RET;
    return Moves + a;
}

//  Copy move struct a to de.
void GetMoveData(struct Move* de, move_t a){
    // LD_HL(mMoves);
    // LD_BC(MOVE_LENGTH);
    // CALL(aAddNTimes);
    // LD_A(BANK(aMoves));
    // JP(mFarCopyBytes);
    CopyBytes(de, Moves + a, sizeof(*de));
}

void GetMoveByte(void){
    LD_A(BANK(aMoves));
    JP(mGetFarByte);

}

void DisappearUser(void){
    // FARCALL(av_DisappearUser);
    v_DisappearUser();
    // RET;

}

void AppearUserLowerSub(void){
    // FARCALL(av_AppearUserLowerSub);
    v_AppearUserLowerSub();
    // RET;
}

void AppearUserRaiseSub(void){
    // FARCALL(av_AppearUserRaiseSub);
    v_AppearUserRaiseSub();
    // RET;
}

//  Checks the options.  Returns true if battle animations are disabled.
bool v_CheckBattleScene(void){
    // PUSH_HL;
    // PUSH_DE;
    // PUSH_BC;
    // FARCALL(aCheckBattleScene);
    // POP_BC;
    // POP_DE;
    // POP_HL;
    // REG_F_C = CheckBattleScene()? 0: 1;
    // RET;
    return CheckBattleScene()? false: true;
}

#include "./move_effects/triple_kick.c"
#include "./move_effects/beat_up.c"
#include "./move_effects/counter.c"
#include "./move_effects/encore.c"
#include "./move_effects/pain_split.c"
#include "./move_effects/snore.c"
#include "./move_effects/conversion2.c"
#include "./move_effects/lock_on.c"
#include "./move_effects/sketch.c"
#include "./move_effects/sleep_talk.c"
#include "./move_effects/destiny_bond.c"
#include "./move_effects/spite.c"
#include "./move_effects/false_swipe.c"
#include "./move_effects/heal_bell.c"
#include "./move_effects/bide.c"
#include "./move_effects/teleport.c"
#include "./move_effects/mist.c"
#include "./move_effects/focus_energy.c"
#include "./move_effects/substitute.c"
#include "./move_effects/rage.c"
#include "./move_effects/mimic.c"
#include "./move_effects/leech_seed.c"
#include "./move_effects/splash.c"
#include "./move_effects/disable.c"
#include "./move_effects/pay_day.c"
#include "./move_effects/conversion.c"
#include "./move_effects/transform.c"
#include "./move_effects/selfdestruct.c"
#include "./move_effects/mirror_move.c"
#include "./move_effects/metronome.c"
#include "./move_effects/thief.c"
#include "./move_effects/nightmare.c"
#include "./move_effects/curse.c"
#include "./move_effects/protect.c"
#include "./move_effects/endure.c"
#include "./move_effects/spikes.c"
#include "./move_effects/foresight.c"
#include "./move_effects/perish_song.c"
#include "./move_effects/sandstorm.c"
#include "./move_effects/rollout.c"
#include "./move_effects/fury_cutter.c"
#include "./move_effects/attract.c"
#include "./move_effects/return.c"
#include "./move_effects/present.c"
#include "./move_effects/frustration.c"
#include "./move_effects/safeguard.c"
#include "./move_effects/magnitude.c"
#include "./move_effects/baton_pass.c"
#include "./move_effects/pursuit.c"
#include "./move_effects/rapid_spin.c"
#include "./move_effects/hidden_power.c"
#include "./move_effects/rain_dance.c"
#include "./move_effects/sunny_day.c"
#include "./move_effects/belly_drum.c"
#include "./move_effects/psych_up.c"
#include "./move_effects/mirror_coat.c"
#include "./move_effects/future_sight.c"
#include "./move_effects/thunder.c"
