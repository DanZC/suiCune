#include "../../constants.h"
#include "effect_commands.h"
#include "../../data/battle/effect_command_pointers.h"
#include "check_battle_scene.h"

void DoPlayerTurn(void){
    CALL(aSetPlayerTurn);

    LD_A_addr(wBattlePlayerAction);
    AND_A_A;  // BATTLEPLAYERACTION_USEMOVE?
    RET_NZ ;

    JR(mDoTurn);

}

void DoEnemyTurn(void){
    CALL(aSetEnemyTurn);

    LD_A_addr(wLinkMode);
    AND_A_A;
    JR_Z (mDoTurn);

    LD_A_addr(wBattleAction);
    CP_A(BATTLEACTION_STRUGGLE);
    JR_Z (mDoTurn);
    CP_A(BATTLEACTION_SWITCH1);
    RET_NC ;

// fallthrough

    return DoTurn();
}

void DoTurn(void){
//  Read in and execute the user's move effects for this turn.

    XOR_A_A;
    LD_addr_A(wTurnEnded);

// Effect command checkturn is called for every move.
    CALL(aCheckTurn);

    LD_A_addr(wTurnEnded);
    AND_A_A;
    RET_NZ ;

    CALL(aUpdateMoveData);

    return DoMove();
}

void DoMove(void){
//  Get the user's move effect.
    LD_A(BATTLE_VARS_MOVE_EFFECT);
    CALL(aGetBattleVar);
    LD_C_A;
    LD_B(0);
    LD_HL(mMoveEffectsPointers);
    ADD_HL_BC;
    ADD_HL_BC;
    LD_A(BANK(aMoveEffectsPointers));
    CALL(aGetFarWord);

    LD_DE(wBattleScriptBuffer);


GetMoveEffect:
    LD_A(BANK(aMoveEffects));
    CALL(aGetFarByte);
    INC_HL;
    LD_de_A;
    INC_DE;
    CP_A(endmove_command);
    IF_NZ goto GetMoveEffect;

//  Start at the first command.
    LD_HL(wBattleScriptBuffer);
    LD_A_L;
    LD_addr_A(wBattleScriptBufferAddress);
    LD_A_H;
    LD_addr_A(wBattleScriptBufferAddress + 1);


ReadMoveEffectCommand:
//  ld a, [wBattleScriptBufferAddress++]
    LD_A_addr(wBattleScriptBufferAddress);
    LD_L_A;
    LD_A_addr(wBattleScriptBufferAddress + 1);
    LD_H_A;

    LD_A_hli;

    PUSH_AF;
    LD_A_L;
    LD_addr_A(wBattleScriptBufferAddress);
    LD_A_H;
    LD_addr_A(wBattleScriptBufferAddress + 1);
    POP_AF;

//  endturn_command (-2) is used to terminate branches without ending the read cycle.
    CP_A(endturn_command);
    RET_NC ;

//  The rest of the commands (01-af) are read from BattleCommandPointers.
    PUSH_BC;
    DEC_A;
    LD_C_A;
    LD_B(0);
    LD_HL(mBattleCommandPointers);
    ADD_HL_BC;
    ADD_HL_BC;
    POP_BC;

    LD_A(BANK(aBattleCommandPointers));
    CALL(aGetFarWord);

    CALL(aDoMove_DoMoveEffectCommand);
    
    goto ReadMoveEffectCommand;


DoMoveEffectCommand:

    JP_hl;
    // BattleCommandPointers[REG_BC]();
}

void CheckTurn(void){
    return BattleCommand_CheckTurn();
}

void BattleCommand_CheckTurn(void){
//  checkturn

//  Repurposed as hardcoded turn handling. Useless as a command.

//  Move $ff immediately ends the turn.
    LD_A(BATTLE_VARS_MOVE);
    CALL(aGetBattleVar);
    INC_A;
    JP_Z (mEndTurn);

    XOR_A_A;
    LD_addr_A(wAttackMissed);
    LD_addr_A(wEffectFailed);
    LD_addr_A(wBattleAnimParam);
    LD_addr_A(wAlreadyDisobeyed);
    LD_addr_A(wAlreadyFailed);
    LD_addr_A(wSomeoneIsRampaging);

    LD_A(EFFECTIVE);
    LD_addr_A(wTypeModifier);

    LDH_A_addr(hBattleTurn);
    AND_A_A;
    JP_NZ (mCheckEnemyTurn);

//  check player turn
    LD_HL(wPlayerSubStatus4);
    BIT_hl(SUBSTATUS_RECHARGE);
    IF_Z goto no_recharge;

    RES_hl(SUBSTATUS_RECHARGE);
    LD_HL(mMustRechargeText);
    CALL(aStdBattleTextbox);
    CALL(aCantMove);
    JP(mEndTurn);


no_recharge:

    LD_HL(wBattleMonStatus);
    LD_A_hl;
    AND_A(SLP);
    IF_Z goto not_asleep;

    DEC_A;
    LD_addr_A(wBattleMonStatus);
    AND_A(SLP);
    IF_Z goto woke_up;

    XOR_A_A;
    LD_addr_A(wNumHits);
    LD_DE(ANIM_SLP);
    CALL(aFarPlayBattleAnimation);
    goto fast_asleep;


woke_up:
    LD_HL(mWokeUpText);
    CALL(aStdBattleTextbox);
    CALL(aCantMove);
    CALL(aUpdateBattleMonInParty);
    LD_HL(mUpdatePlayerHUD);
    CALL(aCallBattleCore);
    LD_A(0x1);
    LDH_addr_A(hBGMapMode);
    LD_HL(wPlayerSubStatus1);
    RES_hl(SUBSTATUS_NIGHTMARE);
    goto not_asleep;


fast_asleep:
    LD_HL(mFastAsleepText);
    CALL(aStdBattleTextbox);

// Snore and Sleep Talk bypass sleep.
    LD_A_addr(wCurPlayerMove);
    CP_A(SNORE);
    IF_Z goto not_asleep;
    CP_A(SLEEP_TALK);
    IF_Z goto not_asleep;

    CALL(aCantMove);
    JP(mEndTurn);


not_asleep:

    LD_HL(wBattleMonStatus);
    BIT_hl(FRZ);
    IF_Z goto not_frozen;

// Flame Wheel and Sacred Fire thaw the user.
    LD_A_addr(wCurPlayerMove);
    CP_A(FLAME_WHEEL);
    IF_Z goto not_frozen;
    CP_A(SACRED_FIRE);
    IF_Z goto not_frozen;

    LD_HL(mFrozenSolidText);
    CALL(aStdBattleTextbox);

    CALL(aCantMove);
    JP(mEndTurn);


not_frozen:

    LD_HL(wPlayerSubStatus3);
    BIT_hl(SUBSTATUS_FLINCHED);
    IF_Z goto not_flinched;

    RES_hl(SUBSTATUS_FLINCHED);
    LD_HL(mFlinchedText);
    CALL(aStdBattleTextbox);

    CALL(aCantMove);
    JP(mEndTurn);


not_flinched:

    LD_HL(wPlayerDisableCount);
    LD_A_hl;
    AND_A_A;
    IF_Z goto not_disabled;

    DEC_A;
    LD_hl_A;
    AND_A(0xf);
    IF_NZ goto not_disabled;

    LD_hl_A;
    LD_addr_A(wDisabledMove);
    LD_HL(mDisabledNoMoreText);
    CALL(aStdBattleTextbox);


not_disabled:

    LD_A_addr(wPlayerSubStatus3);
    ADD_A_A;
    IF_NC goto not_confused;
    LD_HL(wPlayerConfuseCount);
    DEC_hl;
    IF_NZ goto confused;

    LD_HL(wPlayerSubStatus3);
    RES_hl(SUBSTATUS_CONFUSED);
    LD_HL(mConfusedNoMoreText);
    CALL(aStdBattleTextbox);
    goto not_confused;


confused:
    LD_HL(mIsConfusedText);
    CALL(aStdBattleTextbox);
    XOR_A_A;
    LD_addr_A(wNumHits);
    LD_DE(ANIM_CONFUSED);
    CALL(aFarPlayBattleAnimation);

// 50% chance of hitting itself
    CALL(aBattleRandom);
    CP_A(50 percent + 1);
    IF_NC goto not_confused;

// clear confusion-dependent substatus
    LD_HL(wPlayerSubStatus3);
    LD_A_hl;
    AND_A(1 << SUBSTATUS_CONFUSED);
    LD_hl_A;

    CALL(aHitConfusion);
    CALL(aCantMove);
    JP(mEndTurn);


not_confused:

    LD_A_addr(wPlayerSubStatus1);
    ADD_A_A;  // bit SUBSTATUS_ATTRACT
    IF_NC goto not_infatuated;

    LD_HL(mInLoveWithText);
    CALL(aStdBattleTextbox);
    XOR_A_A;
    LD_addr_A(wNumHits);
    LD_DE(ANIM_IN_LOVE);
    CALL(aFarPlayBattleAnimation);

// 50% chance of infatuation
    CALL(aBattleRandom);
    CP_A(50 percent + 1);
    IF_C goto not_infatuated;

    LD_HL(mInfatuationText);
    CALL(aStdBattleTextbox);
    CALL(aCantMove);
    JP(mEndTurn);


not_infatuated:

// We can't disable a move that doesn't exist.
    LD_A_addr(wDisabledMove);
    AND_A_A;
    IF_Z goto no_disabled_move;

// Are we using the disabled move?
    LD_HL(wCurPlayerMove);
    CP_A_hl;
    IF_NZ goto no_disabled_move;

    CALL(aMoveDisabled);
    CALL(aCantMove);
    JP(mEndTurn);


no_disabled_move:

    LD_HL(wBattleMonStatus);
    BIT_hl(PAR);
    RET_Z ;

// 25% chance to be fully paralyzed
    CALL(aBattleRandom);
    CP_A(25 percent);
    RET_NC ;

    LD_HL(mFullyParalyzedText);
    CALL(aStdBattleTextbox);
    CALL(aCantMove);
    JP(mEndTurn);

}

void CantMove(void){
    LD_A(BATTLE_VARS_SUBSTATUS1);
    CALL(aGetBattleVarAddr);
    RES_hl(SUBSTATUS_ROLLOUT);

    LD_A(BATTLE_VARS_SUBSTATUS3);
    CALL(aGetBattleVarAddr);
    LD_A_hl;
    AND_A(~(1 << SUBSTATUS_BIDE | 1 << SUBSTATUS_RAMPAGE | 1 << SUBSTATUS_CHARGED));
    LD_hl_A;

    CALL(aResetFuryCutterCount);

    LD_A(BATTLE_VARS_MOVE_ANIM);
    CALL(aGetBattleVar);
    CP_A(FLY);
    IF_Z goto fly_dig;

    CP_A(DIG);
    RET_NZ ;


fly_dig:
    RES_hl(SUBSTATUS_UNDERGROUND);
    RES_hl(SUBSTATUS_FLYING);
    JP(mAppearUserRaiseSub);

}

void OpponentCantMove(void){
    CALL(aBattleCommand_SwitchTurn);
    CALL(aCantMove);
    JP(mBattleCommand_SwitchTurn);

}

void CheckEnemyTurn(void){
    LD_HL(wEnemySubStatus4);
    BIT_hl(SUBSTATUS_RECHARGE);
    IF_Z goto no_recharge;

    RES_hl(SUBSTATUS_RECHARGE);
    LD_HL(mMustRechargeText);
    CALL(aStdBattleTextbox);
    CALL(aCantMove);
    JP(mEndTurn);


no_recharge:

    LD_HL(wEnemyMonStatus);
    LD_A_hl;
    AND_A(SLP);
    IF_Z goto not_asleep;

    DEC_A;
    LD_addr_A(wEnemyMonStatus);
    AND_A_A;
    IF_Z goto woke_up;

    LD_HL(mFastAsleepText);
    CALL(aStdBattleTextbox);
    XOR_A_A;
    LD_addr_A(wNumHits);
    LD_DE(ANIM_SLP);
    CALL(aFarPlayBattleAnimation);
    goto fast_asleep;


woke_up:
    LD_HL(mWokeUpText);
    CALL(aStdBattleTextbox);
    CALL(aCantMove);
    CALL(aUpdateEnemyMonInParty);
    LD_HL(mUpdateEnemyHUD);
    CALL(aCallBattleCore);
    LD_A(0x1);
    LDH_addr_A(hBGMapMode);
    LD_HL(wEnemySubStatus1);
    RES_hl(SUBSTATUS_NIGHTMARE);
    goto not_asleep;


fast_asleep:
// Snore and Sleep Talk bypass sleep.
    LD_A_addr(wCurEnemyMove);
    CP_A(SNORE);
    IF_Z goto not_asleep;
    CP_A(SLEEP_TALK);
    IF_Z goto not_asleep;
    CALL(aCantMove);
    JP(mEndTurn);


not_asleep:

    LD_HL(wEnemyMonStatus);
    BIT_hl(FRZ);
    IF_Z goto not_frozen;

// Flame Wheel and Sacred Fire thaw the user.
    LD_A_addr(wCurEnemyMove);
    CP_A(FLAME_WHEEL);
    IF_Z goto not_frozen;
    CP_A(SACRED_FIRE);
    IF_Z goto not_frozen;

    LD_HL(mFrozenSolidText);
    CALL(aStdBattleTextbox);
    CALL(aCantMove);
    JP(mEndTurn);


not_frozen:

    LD_HL(wEnemySubStatus3);
    BIT_hl(SUBSTATUS_FLINCHED);
    IF_Z goto not_flinched;

    RES_hl(SUBSTATUS_FLINCHED);
    LD_HL(mFlinchedText);
    CALL(aStdBattleTextbox);

    CALL(aCantMove);
    JP(mEndTurn);


not_flinched:

    LD_HL(wEnemyDisableCount);
    LD_A_hl;
    AND_A_A;
    IF_Z goto not_disabled;

    DEC_A;
    LD_hl_A;
    AND_A(0xf);
    IF_NZ goto not_disabled;

    LD_hl_A;
    LD_addr_A(wEnemyDisabledMove);

    LD_HL(mDisabledNoMoreText);
    CALL(aStdBattleTextbox);


not_disabled:

    LD_A_addr(wEnemySubStatus3);
    ADD_A_A;  // bit SUBSTATUS_CONFUSED
    IF_NC goto not_confused;

    LD_HL(wEnemyConfuseCount);
    DEC_hl;
    IF_NZ goto confused;

    LD_HL(wEnemySubStatus3);
    RES_hl(SUBSTATUS_CONFUSED);
    LD_HL(mConfusedNoMoreText);
    CALL(aStdBattleTextbox);
    goto not_confused;


confused:
    LD_HL(mIsConfusedText);
    CALL(aStdBattleTextbox);

    XOR_A_A;
    LD_addr_A(wNumHits);
    LD_DE(ANIM_CONFUSED);
    CALL(aFarPlayBattleAnimation);

// 50% chance of hitting itself
    CALL(aBattleRandom);
    CP_A(50 percent + 1);
    IF_NC goto not_confused;

// clear confusion-dependent substatus
    LD_HL(wEnemySubStatus3);
    LD_A_hl;
    AND_A(1 << SUBSTATUS_CONFUSED);
    LD_hl_A;

    LD_HL(mHurtItselfText);
    CALL(aStdBattleTextbox);

    CALL(aHitSelfInConfusion);
    CALL(aBattleCommand_DamageCalc);
    CALL(aBattleCommand_LowerSub);

    XOR_A_A;
    LD_addr_A(wNumHits);

// Flicker the monster pic unless flying or underground.
    LD_DE(ANIM_HIT_CONFUSION);
    LD_A(BATTLE_VARS_SUBSTATUS3_OPP);
    CALL(aGetBattleVar);
    AND_A(1 << SUBSTATUS_FLYING | 1 << SUBSTATUS_UNDERGROUND);
    CALL_Z (aPlayFXAnimID);

    LD_C(TRUE);
    CALL(aDoEnemyDamage);
    CALL(aBattleCommand_RaiseSub);
    CALL(aCantMove);
    JP(mEndTurn);


not_confused:

    LD_A_addr(wEnemySubStatus1);
    ADD_A_A;  // bit SUBSTATUS_ATTRACT
    IF_NC goto not_infatuated;

    LD_HL(mInLoveWithText);
    CALL(aStdBattleTextbox);
    XOR_A_A;
    LD_addr_A(wNumHits);
    LD_DE(ANIM_IN_LOVE);
    CALL(aFarPlayBattleAnimation);

// 50% chance of infatuation
    CALL(aBattleRandom);
    CP_A(50 percent + 1);
    IF_C goto not_infatuated;

    LD_HL(mInfatuationText);
    CALL(aStdBattleTextbox);
    CALL(aCantMove);
    JP(mEndTurn);


not_infatuated:

// We can't disable a move that doesn't exist.
    LD_A_addr(wEnemyDisabledMove);
    AND_A_A;
    IF_Z goto no_disabled_move;

// Are we using the disabled move?
    LD_HL(wCurEnemyMove);
    CP_A_hl;
    IF_NZ goto no_disabled_move;

    CALL(aMoveDisabled);

    CALL(aCantMove);
    JP(mEndTurn);


no_disabled_move:

    LD_HL(wEnemyMonStatus);
    BIT_hl(PAR);
    RET_Z ;

// 25% chance to be fully paralyzed
    CALL(aBattleRandom);
    CP_A(25 percent);
    RET_NC ;

    LD_HL(mFullyParalyzedText);
    CALL(aStdBattleTextbox);
    CALL(aCantMove);

// fallthrough

    return EndTurn();
}

void EndTurn(void){
    LD_A(0x1);
    LD_addr_A(wTurnEnded);
    JP(mResetDamage);

}

void MoveDisabled(void){
// Make sure any charged moves fail
    LD_A(BATTLE_VARS_SUBSTATUS3);
    CALL(aGetBattleVarAddr);
    RES_hl(SUBSTATUS_CHARGED);

    LD_A(BATTLE_VARS_MOVE);
    CALL(aGetBattleVar);
    LD_addr_A(wNamedObjectIndex);
    CALL(aGetMoveName);

    LD_HL(mDisabledMoveText);
    JP(mStdBattleTextbox);

}

void HitConfusion(void){
    LD_HL(mHurtItselfText);
    CALL(aStdBattleTextbox);

    XOR_A_A;
    LD_addr_A(wCriticalHit);

    CALL(aHitSelfInConfusion);
    CALL(aBattleCommand_DamageCalc);
    CALL(aBattleCommand_LowerSub);

    XOR_A_A;
    LD_addr_A(wNumHits);

// Flicker the monster pic unless flying or underground.
    LD_DE(ANIM_HIT_CONFUSION);
    LD_A(BATTLE_VARS_SUBSTATUS3_OPP);
    CALL(aGetBattleVar);
    AND_A(1 << SUBSTATUS_FLYING | 1 << SUBSTATUS_UNDERGROUND);
    CALL_Z (aPlayFXAnimID);

    LD_HL(mUpdatePlayerHUD);
    CALL(aCallBattleCore);
    LD_A(0x1);
    LDH_addr_A(hBGMapMode);
    LD_C(TRUE);
    CALL(aDoPlayerDamage);
    JP(mBattleCommand_RaiseSub);

}

void BattleCommand_CheckObedience(void){
//  checkobedience

// Enemy can't disobey
    LDH_A_addr(hBattleTurn);
    AND_A_A;
    RET_NZ ;

    CALL(aCheckUserIsCharging);
    RET_NZ ;

// If we've already checked this turn
    LD_A_addr(wAlreadyDisobeyed);
    AND_A_A;
    RET_NZ ;

    XOR_A_A;
    LD_addr_A(wAlreadyDisobeyed);

// No obedience in link battles
// (since no handling exists for enemy)
    LD_A_addr(wLinkMode);
    AND_A_A;
    RET_NZ ;

    LD_A_addr(wInBattleTowerBattle);
    AND_A_A;
    RET_NZ ;

// If the monster's id doesn't match the player's,
// some conditions need to be met.
    LD_A(MON_ID);
    CALL(aBattlePartyAttr);

    LD_A_addr(wPlayerID);
    CP_A_hl;
    IF_NZ goto obeylevel;
    INC_HL;
    LD_A_addr(wPlayerID + 1);
    CP_A_hl;
    RET_Z ;


obeylevel:
// The maximum obedience level is constrained by owned badges:
    LD_HL(wJohtoBadges);

// risingbadge
    BIT_hl(RISINGBADGE);
    LD_A(MAX_LEVEL + 1);
    IF_NZ goto getlevel;

// stormbadge
    BIT_hl(STORMBADGE);
    LD_A(70);
    IF_NZ goto getlevel;

// fogbadge
    BIT_hl(FOGBADGE);
    LD_A(50);
    IF_NZ goto getlevel;

// hivebadge
    BIT_hl(HIVEBADGE);
    LD_A(30);
    IF_NZ goto getlevel;

// no badges
    LD_A(10);


getlevel:
//  c = obedience level
//  d = monster level
//  b = c + d

    LD_B_A;
    LD_C_A;

    LD_A_addr(wBattleMonLevel);
    LD_D_A;

    ADD_A_B;
    LD_B_A;

//  No overflow (this should never happen)
    IF_NC goto checklevel;
    LD_B(0xff);


checklevel:
//  If the monster's level is lower than the obedience level, it will obey.
    LD_A_C;
    CP_A_D;
    RET_NC ;

//  Random number from 0 to obedience level + monster level

rand1:
    CALL(aBattleRandom);
    SWAP_A;
    CP_A_B;
    IF_NC goto rand1;

//  The higher above the obedience level the monster is,
//  the more likely it is to disobey.
    CP_A_C;
    RET_C ;

//  Sleep-only moves have separate handling, and a higher chance of
//  being ignored. Lazy monsters like their sleep.
    CALL(aIgnoreSleepOnly);
    RET_C ;

//  Another random number from 0 to obedience level + monster level

rand2:
    CALL(aBattleRandom);
    CP_A_B;
    IF_NC goto rand2;

//  A second chance.
    CP_A_C;
    IF_C goto UseInstead;

//  No hope of using a move now.

//  b = number of levels the monster is above the obedience level
    LD_A_D;
    SUB_A_C;
    LD_B_A;

//  The chance of napping is the difference out of 256.
    CALL(aBattleRandom);
    SWAP_A;
    SUB_A_B;
    IF_C goto Nap;

//  The chance of not hitting itself is the same.
    CP_A_B;
    IF_NC goto DoNothing;

    LD_HL(mWontObeyText);
    CALL(aStdBattleTextbox);
    CALL(aHitConfusion);
    JP(mBattleCommand_CheckObedience_EndDisobedience);


Nap:
    CALL(aBattleRandom);
    ADD_A_A;
    SWAP_A;
    AND_A(SLP);
    IF_Z goto Nap;

    LD_addr_A(wBattleMonStatus);

    LD_HL(mBeganToNapText);
    goto Print;


DoNothing:
// 4 random choices
    CALL(aBattleRandom);
    AND_A(0b11);

    LD_HL(mLoafingAroundText);
    AND_A_A;  // 0
    IF_Z goto Print;

    LD_HL(mWontObeyText);
    DEC_A;  // 1
    IF_Z goto Print;

    LD_HL(mTurnedAwayText);
    DEC_A;  // 2
    IF_Z goto Print;

    LD_HL(mIgnoredOrdersText);


Print:
    CALL(aStdBattleTextbox);
    JP(mBattleCommand_CheckObedience_EndDisobedience);


UseInstead:
//  Can't use another move if the monster only has one!
    LD_A_addr(wBattleMonMoves + 1);
    AND_A_A;
    IF_Z goto DoNothing;

//  Don't bother trying to handle Disable.
    LD_A_addr(wDisabledMove);
    AND_A_A;
    IF_NZ goto DoNothing;

    LD_HL(wBattleMonPP);
    LD_DE(wBattleMonMoves);
    LD_B(0);
    LD_C(NUM_MOVES);


GetTotalPP:
    LD_A_hli;
    AND_A(PP_MASK);
    ADD_A_B;
    LD_B_A;

    DEC_C;
    IF_Z goto CheckMovePP;

//  Stop at undefined moves.
    INC_DE;
    LD_A_de;
    AND_A_A;
    IF_NZ goto GetTotalPP;


CheckMovePP:
    LD_HL(wBattleMonPP);
    LD_A_addr(wCurMoveNum);
    LD_E_A;
    LD_D(0);
    ADD_HL_DE;

//  Can't use another move if only one move has PP.
    LD_A_hl;
    AND_A(PP_MASK);
    CP_A_B;
    IF_Z goto DoNothing;

//  Make sure we can actually use the move once we get there.
    LD_A(1);
    LD_addr_A(wAlreadyDisobeyed);

    LD_A_addr(w2DMenuNumRows);
    LD_B_A;

//  Save the move we originally picked for afterward.
    LD_A_addr(wCurMoveNum);
    LD_C_A;
    PUSH_AF;


RandomMove:
    CALL(aBattleRandom);
    maskbits(NUM_MOVES, 0);

    CP_A_B;
    IF_NC goto RandomMove;

//  Not the move we were trying to use.
    CP_A_C;
    IF_Z goto RandomMove;

//  Make sure it has PP.
    LD_addr_A(wCurMoveNum);
    LD_HL(wBattleMonPP);
    LD_E_A;
    LD_D(0);
    ADD_HL_DE;
    LD_A_hl;
    AND_A(PP_MASK);
    IF_Z goto RandomMove;

//  Use it.
    LD_A_addr(wCurMoveNum);
    LD_C_A;
    LD_B(0);
    LD_HL(wBattleMonMoves);
    ADD_HL_BC;
    LD_A_hl;
    LD_addr_A(wCurPlayerMove);

    CALL(aSetPlayerTurn);
    CALL(aUpdateMoveData);
    CALL(aDoMove);

//  Restore original move choice.
    POP_AF;
    LD_addr_A(wCurMoveNum);


EndDisobedience:
    XOR_A_A;
    LD_addr_A(wLastPlayerMove);
    LD_addr_A(wLastPlayerCounterMove);

// Break Encore too.
    LD_HL(wPlayerSubStatus5);
    RES_hl(SUBSTATUS_ENCORED);
    XOR_A_A;
    LD_addr_A(wPlayerEncoreCount);

    JP(mEndMoveEffect);

}

void IgnoreSleepOnly(void){
    LD_A(BATTLE_VARS_MOVE_ANIM);
    CALL(aGetBattleVar);

// Snore and Sleep Talk bypass sleep.
    CP_A(SNORE);
    IF_Z goto CheckSleep;
    CP_A(SLEEP_TALK);
    IF_Z goto CheckSleep;
    AND_A_A;
    RET;


CheckSleep:
    LD_A(BATTLE_VARS_STATUS);
    CALL(aGetBattleVar);
    AND_A(SLP);
    RET_Z ;

//  'ignored orders…sleeping!'
    LD_HL(mIgnoredSleepingText);
    CALL(aStdBattleTextbox);

    CALL(aEndMoveEffect);

    SCF;
    RET;

}

void BattleCommand_UsedMoveText(void){
//  usedmovetext
    FARCALL(aDisplayUsedMoveText);
    RET;

}

void CheckUserIsCharging(void){
    LDH_A_addr(hBattleTurn);
    AND_A_A;
    LD_A_addr(wPlayerCharging);  // player
    IF_Z goto end;
    LD_A_addr(wEnemyCharging);  // enemy

end:
    AND_A_A;
    RET;

}

void BattleCommand_DoTurn(void){
    CALL(aCheckUserIsCharging);
    RET_NZ ;

    LD_HL(wBattleMonPP);
    LD_DE(wPlayerSubStatus3);
    LD_BC(wPlayerTurnsTaken);

    LDH_A_addr(hBattleTurn);
    AND_A_A;
    IF_Z goto proceed;

    LD_HL(wEnemyMonPP);
    LD_DE(wEnemySubStatus3);
    LD_BC(wEnemyTurnsTaken);


proceed:

//  If we've gotten this far, this counts as a turn.
    LD_A_bc;
    INC_A;
    LD_bc_A;

    LD_A(BATTLE_VARS_MOVE);
    CALL(aGetBattleVar);
    CP_A(STRUGGLE);
    RET_Z ;

    LD_A_de;
    AND_A(1 << SUBSTATUS_IN_LOOP | 1 << SUBSTATUS_RAMPAGE | 1 << SUBSTATUS_BIDE);
    RET_NZ ;

    CALL(aBattleCommand_DoTurn_consume_pp);
    LD_A_B;
    AND_A_A;
    JP_NZ (mEndMoveEffect);

// SubStatus5
    INC_DE;
    INC_DE;

    LD_A_de;
    BIT_A(SUBSTATUS_TRANSFORMED);
    RET_NZ ;

    LDH_A_addr(hBattleTurn);
    AND_A_A;

    LD_HL(wPartyMon1PP);
    LD_A_addr(wCurBattleMon);
    IF_Z goto player;

//  mimic this part entirely if wildbattle
    LD_A_addr(wBattleMode);
    DEC_A;
    IF_Z goto wild;

    LD_HL(wOTPartyMon1PP);
    LD_A_addr(wCurOTMon);


player:
    CALL(aGetPartyLocation);
    PUSH_HL;
    CALL(aCheckMimicUsed);
    POP_HL;
    RET_C ;


consume_pp:
    LDH_A_addr(hBattleTurn);
    AND_A_A;
    LD_A_addr(wCurMoveNum);
    IF_Z goto okay;
    LD_A_addr(wCurEnemyMoveNum);


okay:
    LD_C_A;
    LD_B(0);
    ADD_HL_BC;
    LD_A_hl;
    AND_A(PP_MASK);
    IF_Z goto out_of_pp;
    DEC_hl;
    LD_B(0);
    RET;


wild:
    LD_HL(wEnemyMonMoves);
    LD_A_addr(wCurEnemyMoveNum);
    LD_C_A;
    LD_B(0);
    ADD_HL_BC;
    LD_A_hl;
    CP_A(MIMIC);
    IF_Z goto mimic;
    LD_HL(wWildMonMoves);
    ADD_HL_BC;
    LD_A_hl;
    CP_A(MIMIC);
    RET_Z ;


mimic:
    LD_HL(wWildMonPP);
    CALL(aBattleCommand_DoTurn_consume_pp);
    RET;


out_of_pp:
    CALL(aBattleCommand_MoveDelay);
//  get move effect
    LD_A(BATTLE_VARS_MOVE_EFFECT);
    CALL(aGetBattleVar);
//  continuous?
    LD_HL(mBattleCommand_DoTurn_continuousmoves);
    LD_DE(1);
    CALL(aIsInArray);

//  'has no pp left for [move]'
    LD_HL(mHasNoPPLeftText);
    IF_C goto print;
//  'but no pp is left for the move'
    LD_HL(mNoPPLeftText);

print:
    CALL(aStdBattleTextbox);
    LD_B(1);
    RET;


continuousmoves:
    //db ['EFFECT_RAZOR_WIND'];
    //db ['EFFECT_SKY_ATTACK'];
    //db ['EFFECT_SKULL_BASH'];
    //db ['EFFECT_SOLARBEAM'];
    //db ['EFFECT_FLY'];
    //db ['EFFECT_ROLLOUT'];
    //db ['EFFECT_BIDE'];
    //db ['EFFECT_RAMPAGE'];
    //db ['-1'];

    return CheckMimicUsed();
}

void CheckMimicUsed(void){
    LDH_A_addr(hBattleTurn);
    AND_A_A;
    LD_A_addr(wCurMoveNum);
    IF_Z goto player;
    LD_A_addr(wCurEnemyMoveNum);


player:
    LD_C_A;
    LD_A(MON_MOVES);
    CALL(aUserPartyAttr);

    LD_A(BATTLE_VARS_MOVE);
    CALL(aGetBattleVar);
    CP_A(MIMIC);
    IF_Z goto mimic;

    LD_B(0);
    ADD_HL_BC;
    LD_A_hl;
    CP_A(MIMIC);
    IF_NZ goto mimic;

    SCF;
    RET;


mimic:
    AND_A_A;
    RET;

}

void BattleCommand_Critical(void){
//  critical

//  Determine whether this attack's hit will be critical.

    XOR_A_A;
    LD_addr_A(wCriticalHit);

    LD_A(BATTLE_VARS_MOVE_POWER);
    CALL(aGetBattleVar);
    AND_A_A;
    RET_Z ;

    LDH_A_addr(hBattleTurn);
    AND_A_A;
    LD_HL(wEnemyMonItem);
    LD_A_addr(wEnemyMonSpecies);
    IF_NZ goto Item;
    LD_HL(wBattleMonItem);
    LD_A_addr(wBattleMonSpecies);


Item:
    LD_C(0);

    CP_A(CHANSEY);
    IF_NZ goto Farfetchd;
    LD_A_hl;
    CP_A(LUCKY_PUNCH);
    IF_NZ goto FocusEnergy;

//  +2 critical level
    LD_C(2);
    goto Tally;


Farfetchd:
    CP_A(FARFETCH_D);
    IF_NZ goto FocusEnergy;
    LD_A_hl;
    CP_A(STICK);
    IF_NZ goto FocusEnergy;

//  +2 critical level
    LD_C(2);
    goto Tally;


FocusEnergy:
    LD_A(BATTLE_VARS_SUBSTATUS4);
    CALL(aGetBattleVar);
    BIT_A(SUBSTATUS_FOCUS_ENERGY);
    IF_Z goto CheckCritical;

//  +1 critical level
    INC_C;


CheckCritical:
    LD_A(BATTLE_VARS_MOVE_ANIM);
    CALL(aGetBattleVar);
    LD_DE(1);
    LD_HL(mCriticalHitMoves);
    PUSH_BC;
    CALL(aIsInArray);
    POP_BC;
    IF_NC goto ScopeLens;

//  +2 critical level
    INC_C;
    INC_C;


ScopeLens:
    PUSH_BC;
    CALL(aGetUserItem);
    LD_A_B;
    CP_A(HELD_CRITICAL_UP);  // Increased critical chance. Only Scope Lens has this.
    POP_BC;
    IF_NZ goto Tally;

//  +1 critical level
    INC_C;


Tally:
    LD_HL(mCriticalHitChances);
    LD_B(0);
    ADD_HL_BC;
    CALL(aBattleRandom);
    CP_A_hl;
    RET_NC ;
    LD_A(1);
    LD_addr_A(wCriticalHit);
    RET;

// INCLUDE "data/moves/critical_hit_moves.asm"

// INCLUDE "data/battle/critical_hit_chances.asm"

// INCLUDE "engine/battle/move_effects/triple_kick.asm"

    return BattleCommand_Stab();
}

void BattleCommand_Stab(void){
//  STAB = Same Type Attack Bonus
    LD_A(BATTLE_VARS_MOVE_ANIM);
    CALL(aGetBattleVar);
    CP_A(STRUGGLE);
    RET_Z ;

    LD_HL(wBattleMonType1);
    LD_A_hli;
    LD_B_A;
    LD_C_hl;
    LD_HL(wEnemyMonType1);
    LD_A_hli;
    LD_D_A;
    LD_E_hl;

    LDH_A_addr(hBattleTurn);
    AND_A_A;
    IF_Z goto go;  // Who Attacks and who Defends

    LD_HL(wEnemyMonType1);
    LD_A_hli;
    LD_B_A;
    LD_C_hl;
    LD_HL(wBattleMonType1);
    LD_A_hli;
    LD_D_A;
    LD_E_hl;


go:
    LD_A(BATTLE_VARS_MOVE_TYPE);
    CALL(aGetBattleVarAddr);
    LD_addr_A(wCurType);

    PUSH_HL;
    PUSH_DE;
    PUSH_BC;
    FARCALL(aDoWeatherModifiers);
    POP_BC;
    POP_DE;
    POP_HL;

    PUSH_DE;
    PUSH_BC;
    FARCALL(aDoBadgeTypeBoosts);
    POP_BC;
    POP_DE;

    LD_A_addr(wCurType);
    CP_A_B;
    IF_Z goto stab;
    CP_A_C;
    IF_Z goto stab;

    goto SkipStab;


stab:
    LD_HL(wCurDamage + 1);
    LD_A_hld;
    LD_H_hl;
    LD_L_A;

    LD_B_H;
    LD_C_L;
    SRL_B;
    RR_C;
    ADD_HL_BC;

    LD_A_H;
    LD_addr_A(wCurDamage);
    LD_A_L;
    LD_addr_A(wCurDamage + 1);

    LD_HL(wTypeModifier);
    SET_hl(7);


SkipStab:
    LD_A(BATTLE_VARS_MOVE_TYPE);
    CALL(aGetBattleVar);
    LD_B_A;
    LD_HL(mTypeMatchups);


TypesLoop:
    LD_A_hli;

    CP_A(-1);
    IF_Z goto end;

// foresight
    CP_A(-2);
    IF_NZ goto SkipForesightCheck;
    LD_A(BATTLE_VARS_SUBSTATUS1_OPP);
    CALL(aGetBattleVar);
    BIT_A(SUBSTATUS_IDENTIFIED);
    IF_NZ goto end;

    goto TypesLoop;


SkipForesightCheck:
    CP_A_B;
    IF_NZ goto SkipType;
    LD_A_hl;
    CP_A_D;
    IF_Z goto GotMatchup;
    CP_A_E;
    IF_Z goto GotMatchup;
    goto SkipType;


GotMatchup:
    PUSH_HL;
    PUSH_BC;
    INC_HL;
    LD_A_addr(wTypeModifier);
    AND_A(0b10000000);
    LD_B_A;
//  If the target is immune to the move, treat it as a miss and calculate the damage as 0
    LD_A_hl;
    AND_A_A;
    IF_NZ goto NotImmune;
    INC_A;
    LD_addr_A(wAttackMissed);
    XOR_A_A;

NotImmune:
    LDH_addr_A(hMultiplier);
    ADD_A_B;
    LD_addr_A(wTypeModifier);

    XOR_A_A;
    LDH_addr_A(hMultiplicand + 0);

    LD_HL(wCurDamage);
    LD_A_hli;
    LDH_addr_A(hMultiplicand + 1);
    LD_A_hld;
    LDH_addr_A(hMultiplicand + 2);

    CALL(aMultiply);

    LDH_A_addr(hProduct + 1);
    LD_B_A;
    LDH_A_addr(hProduct + 2);
    OR_A_B;
    LD_B_A;
    LDH_A_addr(hProduct + 3);
    OR_A_B;
    IF_Z goto ok;  // This is a very convoluted way to get back that we've essentially dealt no damage.

//  Take the product and divide it by 10.
    LD_A(10);
    LDH_addr_A(hDivisor);
    LD_B(4);
    CALL(aDivide);
    LDH_A_addr(hQuotient + 2);
    LD_B_A;
    LDH_A_addr(hQuotient + 3);
    OR_A_B;
    IF_NZ goto ok;

    LD_A(1);
    LDH_addr_A(hMultiplicand + 2);


ok:
    LDH_A_addr(hMultiplicand + 1);
    LD_hli_A;
    LDH_A_addr(hMultiplicand + 2);
    LD_hl_A;
    POP_BC;
    POP_HL;


SkipType:
    INC_HL;
    INC_HL;
    goto TypesLoop;


end:
    CALL(aBattleCheckTypeMatchup);
    LD_A_addr(wTypeMatchup);
    LD_B_A;
    LD_A_addr(wTypeModifier);
    AND_A(0b10000000);
    OR_A_B;
    LD_addr_A(wTypeModifier);
    RET;

}

void BattleCheckTypeMatchup(void){
    LD_HL(wEnemyMonType1);
    LDH_A_addr(hBattleTurn);
    AND_A_A;
    JR_Z (mCheckTypeMatchup);
    LD_HL(wBattleMonType1);
    return CheckTypeMatchup();
}

void CheckTypeMatchup(void){
//  There is an incorrect assumption about this function made in the AI related code: when
//  the AI calls CheckTypeMatchup (not BattleCheckTypeMatchup), it assumes that placing the
//  offensive type in a will make this function do the right thing. Since a is overwritten,
//  this assumption is incorrect. A simple fix would be to load the move type for the
//  current move into a in BattleCheckTypeMatchup, before falling through, which is
//  consistent with how the rest of the code assumes this code works like.
    PUSH_HL;
    PUSH_DE;
    PUSH_BC;
    LD_A(BATTLE_VARS_MOVE_TYPE);
    CALL(aGetBattleVar);
    LD_D_A;
    LD_B_hl;
    INC_HL;
    LD_C_hl;
    LD_A(EFFECTIVE);
    LD_addr_A(wTypeMatchup);
    LD_HL(mTypeMatchups);

TypesLoop:
    LD_A_hli;
    CP_A(-1);
    IF_Z goto End;
    CP_A(-2);
    IF_NZ goto Next;
    LD_A(BATTLE_VARS_SUBSTATUS1_OPP);
    CALL(aGetBattleVar);
    BIT_A(SUBSTATUS_IDENTIFIED);
    IF_NZ goto End;
    goto TypesLoop;


Next:
    CP_A_D;
    IF_NZ goto Nope;
    LD_A_hli;
    CP_A_B;
    IF_Z goto Yup;
    CP_A_C;
    IF_Z goto Yup;
    goto Nope2;


Nope:
    INC_HL;

Nope2:
    INC_HL;
    goto TypesLoop;


Yup:
    XOR_A_A;
    LDH_addr_A(hDividend + 0);
    LDH_addr_A(hMultiplicand + 0);
    LDH_addr_A(hMultiplicand + 1);
    LD_A_hli;
    LDH_addr_A(hMultiplicand + 2);
    LD_A_addr(wTypeMatchup);
    LDH_addr_A(hMultiplier);
    CALL(aMultiply);
    LD_A(10);
    LDH_addr_A(hDivisor);
    PUSH_BC;
    LD_B(4);
    CALL(aDivide);
    POP_BC;
    LDH_A_addr(hQuotient + 3);
    LD_addr_A(wTypeMatchup);
    goto TypesLoop;


End:
    POP_BC;
    POP_DE;
    POP_HL;
    RET;

}

void BattleCommand_ResetTypeMatchup(void){
//  Reset the type matchup multiplier to 1.0, if the type matchup is not 0.
//  If there is immunity in play, the move automatically misses.
    CALL(aBattleCheckTypeMatchup);
    LD_A_addr(wTypeMatchup);
    AND_A_A;
    LD_A(EFFECTIVE);
    IF_NZ goto reset;
    CALL(aResetDamage);
    XOR_A_A;
    LD_addr_A(wTypeModifier);
    INC_A;
    LD_addr_A(wAttackMissed);
    RET;


reset:
    LD_addr_A(wTypeMatchup);
    RET;

// INCLUDE "engine/battle/ai/switch.asm"

// INCLUDE "data/types/type_matchups.asm"

    return BattleCommand_DamageVariation();
}

void BattleCommand_DamageVariation(void){
//  damagevariation

//  Modify the damage spread between 85% and 100%.

//  Because of the method of division the probability distribution
//  is not consistent. This makes the highest damage multipliers
//  rarer than normal.

//  No point in reducing 1 or 0 damage.
    LD_HL(wCurDamage);
    LD_A_hli;
    AND_A_A;
    IF_NZ goto go;
    LD_A_hl;
    CP_A(2);
    RET_C ;


go:
//  Start with the maximum damage.
    XOR_A_A;
    LDH_addr_A(hMultiplicand + 0);
    DEC_HL;
    LD_A_hli;
    LDH_addr_A(hMultiplicand + 1);
    LD_A_hl;
    LDH_addr_A(hMultiplicand + 2);

//  Multiply by 85-100%...

loop:
    CALL(aBattleRandom);
    RRCA;
    CP_A(85 percent + 1);
    IF_C goto loop;

    LDH_addr_A(hMultiplier);
    CALL(aMultiply);

//  ...divide by 100%...
    LD_A(100 percent);
    LDH_addr_A(hDivisor);
    LD_B(0x4);
    CALL(aDivide);

//  ...to get .85-1.00x damage.
    LDH_A_addr(hQuotient + 2);
    LD_HL(wCurDamage);
    LD_hli_A;
    LDH_A_addr(hQuotient + 3);
    LD_hl_A;
    RET;

}

void BattleCommand_CheckHit(void){
//  checkhit

    CALL(aBattleCommand_CheckHit_DreamEater);
    JP_Z (mBattleCommand_CheckHit_Miss);

    CALL(aBattleCommand_CheckHit_Protect);
    JP_NZ (mBattleCommand_CheckHit_Miss);

    CALL(aBattleCommand_CheckHit_DrainSub);
    JP_Z (mBattleCommand_CheckHit_Miss);

    CALL(aBattleCommand_CheckHit_LockOn);
    RET_NZ ;

    CALL(aBattleCommand_CheckHit_FlyDigMoves);
    JP_NZ (mBattleCommand_CheckHit_Miss);

    CALL(aBattleCommand_CheckHit_ThunderRain);
    RET_Z ;

    CALL(aBattleCommand_CheckHit_XAccuracy);
    RET_NZ ;

// Perfect-accuracy moves
    LD_A(BATTLE_VARS_MOVE_EFFECT);
    CALL(aGetBattleVar);
    CP_A(EFFECT_ALWAYS_HIT);
    RET_Z ;

    CALL(aBattleCommand_CheckHit_StatModifiers);

    LD_A_addr(wPlayerMoveStruct + MOVE_ACC);
    LD_B_A;
    LDH_A_addr(hBattleTurn);
    AND_A_A;
    IF_Z goto BrightPowder;
    LD_A_addr(wEnemyMoveStruct + MOVE_ACC);
    LD_B_A;


BrightPowder:
    PUSH_BC;
    CALL(aGetOpponentItem);
    LD_A_B;
    CP_A(HELD_BRIGHTPOWDER);
    LD_A_C;  // % miss
    POP_BC;
    IF_NZ goto skip_brightpowder;

    LD_C_A;
    LD_A_B;
    SUB_A_C;
    LD_B_A;
    IF_NC goto skip_brightpowder;
    LD_B(0);


skip_brightpowder:
    LD_A_B;
    CP_A(-1);
    IF_Z goto Hit;

    CALL(aBattleRandom);
    CP_A_B;
    IF_NC goto Miss;


Hit:
    RET;


Miss:
//  Keep the damage value intact if we're using (Hi) Jump Kick.
    LD_A(BATTLE_VARS_MOVE_EFFECT);
    CALL(aGetBattleVar);
    CP_A(EFFECT_JUMP_KICK);
    IF_Z goto Missed;
    CALL(aResetDamage);


Missed:
    LD_A(1);
    LD_addr_A(wAttackMissed);
    RET;


DreamEater:
//  Return z if we're trying to eat the dream of
//  a monster that isn't sleeping.
    LD_A(BATTLE_VARS_MOVE_EFFECT);
    CALL(aGetBattleVar);
    CP_A(EFFECT_DREAM_EATER);
    RET_NZ ;

    LD_A(BATTLE_VARS_STATUS_OPP);
    CALL(aGetBattleVar);
    AND_A(SLP);
    RET;


Protect:
//  Return nz if the opponent is protected.
    LD_A(BATTLE_VARS_SUBSTATUS1_OPP);
    CALL(aGetBattleVar);
    BIT_A(SUBSTATUS_PROTECT);
    RET_Z ;

    LD_C(40);
    CALL(aDelayFrames);

//  'protecting itself!'
    LD_HL(mProtectingItselfText);
    CALL(aStdBattleTextbox);

    LD_C(40);
    CALL(aDelayFrames);

    LD_A(1);
    AND_A_A;
    RET;


LockOn:
//  Return nz if we are locked-on and aren't trying to use Earthquake,
//  Fissure or Magnitude on a monster that is flying.
    LD_A(BATTLE_VARS_SUBSTATUS5_OPP);
    CALL(aGetBattleVarAddr);
    BIT_hl(SUBSTATUS_LOCK_ON);
    RES_hl(SUBSTATUS_LOCK_ON);
    RET_Z ;

    LD_A(BATTLE_VARS_SUBSTATUS3_OPP);
    CALL(aGetBattleVar);
    BIT_A(SUBSTATUS_FLYING);
    IF_Z goto LockedOn;

    LD_A(BATTLE_VARS_MOVE_ANIM);
    CALL(aGetBattleVar);

    CP_A(EARTHQUAKE);
    RET_Z ;
    CP_A(FISSURE);
    RET_Z ;
    CP_A(MAGNITUDE);
    RET_Z ;


LockedOn:
    LD_A(1);
    AND_A_A;
    RET;


DrainSub:
//  Return z if using an HP drain move on a substitute.
    CALL(aCheckSubstituteOpp);
    IF_Z goto not_draining_sub;

    LD_A(BATTLE_VARS_MOVE_EFFECT);
    CALL(aGetBattleVar);

    CP_A(EFFECT_LEECH_HIT);
    RET_Z ;
    CP_A(EFFECT_DREAM_EATER);
    RET_Z ;


not_draining_sub:
    LD_A(1);
    AND_A_A;
    RET;


FlyDigMoves:
//  Check for moves that can hit underground/flying opponents.
//  Return z if the current move can hit the opponent.

    LD_A(BATTLE_VARS_SUBSTATUS3_OPP);
    CALL(aGetBattleVar);
    AND_A(1 << SUBSTATUS_FLYING | 1 << SUBSTATUS_UNDERGROUND);
    RET_Z ;

    BIT_A(SUBSTATUS_FLYING);
    IF_Z goto DigMoves;

    LD_A(BATTLE_VARS_MOVE_ANIM);
    CALL(aGetBattleVar);

    CP_A(GUST);
    RET_Z ;
    CP_A(WHIRLWIND);
    RET_Z ;
    CP_A(THUNDER);
    RET_Z ;
    CP_A(TWISTER);
    RET;


DigMoves:
    LD_A(BATTLE_VARS_MOVE_ANIM);
    CALL(aGetBattleVar);

    CP_A(EARTHQUAKE);
    RET_Z ;
    CP_A(FISSURE);
    RET_Z ;
    CP_A(MAGNITUDE);
    RET;


ThunderRain:
//  Return z if the current move always hits in rain, and it is raining.
    LD_A(BATTLE_VARS_MOVE_EFFECT);
    CALL(aGetBattleVar);
    CP_A(EFFECT_THUNDER);
    RET_NZ ;

    LD_A_addr(wBattleWeather);
    CP_A(WEATHER_RAIN);
    RET;


XAccuracy:
    LD_A(BATTLE_VARS_SUBSTATUS4);
    CALL(aGetBattleVar);
    BIT_A(SUBSTATUS_X_ACCURACY);
    RET;


StatModifiers:
    LDH_A_addr(hBattleTurn);
    AND_A_A;

// load the user's accuracy into b and the opponent's evasion into c.
    LD_HL(wPlayerMoveStruct + MOVE_ACC);
    LD_A_addr(wPlayerAccLevel);
    LD_B_A;
    LD_A_addr(wEnemyEvaLevel);
    LD_C_A;

    IF_Z goto got_acc_eva;

    LD_HL(wEnemyMoveStruct + MOVE_ACC);
    LD_A_addr(wEnemyAccLevel);
    LD_B_A;
    LD_A_addr(wPlayerEvaLevel);
    LD_C_A;


got_acc_eva:
    CP_A_B;
    IF_C goto skip_foresight_check;

// if the target's evasion is greater than the user's accuracy,
// check the target's foresight status
    LD_A(BATTLE_VARS_SUBSTATUS1_OPP);
    CALL(aGetBattleVar);
    BIT_A(SUBSTATUS_IDENTIFIED);
    RET_NZ ;


skip_foresight_check:
// subtract evasion from 14
    LD_A(MAX_STAT_LEVEL + 1);
    SUB_A_C;
    LD_C_A;
// store the base move accuracy for math ops
    XOR_A_A;
    LDH_addr_A(hMultiplicand + 0);
    LDH_addr_A(hMultiplicand + 1);
    LD_A_hl;
    LDH_addr_A(hMultiplicand + 2);
    PUSH_HL;
    LD_D(2);  // do this twice, once for the user's accuracy and once for the target's evasion


accuracy_loop:
// look up the multiplier from the table
    PUSH_BC;
    LD_HL(mAccuracyLevelMultipliers);
    DEC_B;
    SLA_B;
    LD_C_B;
    LD_B(0);
    ADD_HL_BC;
    POP_BC;
// multiply by the first byte in that row...
    LD_A_hli;
    LDH_addr_A(hMultiplier);
    CALL(aMultiply);
// ... and divide by the second byte
    LD_A_hl;
    LDH_addr_A(hDivisor);
    LD_B(4);
    CALL(aDivide);
// minimum accuracy is $0001
    LDH_A_addr(hQuotient + 3);
    LD_B_A;
    LDH_A_addr(hQuotient + 2);
    OR_A_B;
    IF_NZ goto min_accuracy;
    LDH_addr_A(hQuotient + 2);
    LD_A(1);
    LDH_addr_A(hQuotient + 3);


min_accuracy:
// do the same thing to the target's evasion
    LD_B_C;
    DEC_D;
    IF_NZ goto accuracy_loop;

// if the result is more than 2 bytes, max out at 100%
    LDH_A_addr(hQuotient + 2);
    AND_A_A;
    LDH_A_addr(hQuotient + 3);
    IF_Z goto finish_accuracy;
    LD_A(0xff);


finish_accuracy:
    POP_HL;
    LD_hl_A;
    RET;

// INCLUDE "data/battle/accuracy_multipliers.asm"

    return BattleCommand_EffectChance();
}

void BattleCommand_EffectChance(void){
//  effectchance

    XOR_A_A;
    LD_addr_A(wEffectFailed);
    CALL(aCheckSubstituteOpp);
    IF_NZ goto failed;

    PUSH_HL;
    LD_HL(wPlayerMoveStruct + MOVE_CHANCE);
    LDH_A_addr(hBattleTurn);
    AND_A_A;
    IF_Z goto got_move_chance;
    LD_HL(wEnemyMoveStruct + MOVE_CHANCE);

got_move_chance:

// BUG: 1/256 chance to fail even for a 100% effect chance,
// since carry is not set if BattleRandom == [hl] == 255
    CALL(aBattleRandom);
    CP_A_hl;
    POP_HL;
    RET_C ;


failed:
    LD_A(1);
    LD_addr_A(wEffectFailed);
    AND_A_A;
    RET;

}

void BattleCommand_LowerSub(void){
//  lowersub

    LD_A(BATTLE_VARS_SUBSTATUS4);
    CALL(aGetBattleVar);
    BIT_A(SUBSTATUS_SUBSTITUTE);
    RET_Z ;

    LD_A(BATTLE_VARS_SUBSTATUS3);
    CALL(aGetBattleVar);
    BIT_A(SUBSTATUS_CHARGED);
    IF_NZ goto already_charged;

    LD_A(BATTLE_VARS_MOVE_EFFECT);
    CALL(aGetBattleVar);
    CP_A(EFFECT_RAZOR_WIND);
    IF_Z goto charge_turn;
    CP_A(EFFECT_SKY_ATTACK);
    IF_Z goto charge_turn;
    CP_A(EFFECT_SKULL_BASH);
    IF_Z goto charge_turn;
    CP_A(EFFECT_SOLARBEAM);
    IF_Z goto charge_turn;
    CP_A(EFFECT_FLY);
    IF_Z goto charge_turn;


already_charged:
    CALL(aBattleCommand_LowerSub_Rampage);
    IF_Z goto charge_turn;

    CALL(aCheckUserIsCharging);
    RET_NZ ;


charge_turn:
    CALL(av_CheckBattleScene);
    IF_C goto mimic_anims;

    XOR_A_A;
    LD_addr_A(wNumHits);
    LD_addr_A(wFXAnimID + 1);
    INC_A;
    LD_addr_A(wBattleAnimParam);
    LD_A(SUBSTITUTE);
    JP(mLoadAnim);


mimic_anims:
    CALL(aBattleCommand_LowerSubNoAnim);
    JP(mBattleCommand_MoveDelay);


Rampage:
    LD_A(BATTLE_VARS_MOVE_EFFECT);
    CALL(aGetBattleVar);
    CP_A(EFFECT_ROLLOUT);
    IF_Z goto rollout_rampage;
    CP_A(EFFECT_RAMPAGE);
    IF_Z goto rollout_rampage;

    LD_A(1);
    AND_A_A;
    RET;


rollout_rampage:
    LD_A_addr(wSomeoneIsRampaging);
    AND_A_A;
    LD_A(0);
    LD_addr_A(wSomeoneIsRampaging);
    RET;

}

void BattleCommand_MoveAnim(void){
//  moveanim
    CALL(aBattleCommand_LowerSub);
    CALL(aBattleCommand_MoveAnimNoSub);
    JP(mBattleCommand_RaiseSub);

}

void BattleCommand_MoveAnimNoSub(void){
    LD_A_addr(wAttackMissed);
    AND_A_A;
    JP_NZ (mBattleCommand_MoveDelay);

    LDH_A_addr(hBattleTurn);
    AND_A_A;
    LD_DE(wPlayerRolloutCount);
    LD_A(BATTLEANIM_ENEMY_DAMAGE);
    IF_Z goto got_rollout_count;
    LD_DE(wEnemyRolloutCount);
    LD_A(BATTLEANIM_PLAYER_DAMAGE);


got_rollout_count:
    LD_addr_A(wNumHits);
    LD_A(BATTLE_VARS_MOVE_EFFECT);
    CALL(aGetBattleVar);
    CP_A(EFFECT_MULTI_HIT);
    IF_Z goto alternate_anim;
    CP_A(EFFECT_CONVERSION);
    IF_Z goto alternate_anim;
    CP_A(EFFECT_DOUBLE_HIT);
    IF_Z goto alternate_anim;
    CP_A(EFFECT_POISON_MULTI_HIT);
    IF_Z goto alternate_anim;
    CP_A(EFFECT_TRIPLE_KICK);
    IF_Z goto triplekick;
    XOR_A_A;
    LD_addr_A(wBattleAnimParam);


triplekick:
    LD_A(BATTLE_VARS_MOVE_ANIM);
    CALL(aGetBattleVar);
    LD_E_A;
    LD_D(0);
    CALL(aPlayFXAnimID);

    LD_A(BATTLE_VARS_MOVE_ANIM);
    CALL(aGetBattleVar);
    CP_A(FLY);
    IF_Z goto clear_sprite;
    CP_A(DIG);
    RET_NZ ;

clear_sprite:
    JP(mAppearUserLowerSub);


alternate_anim:
    LD_A_addr(wBattleAnimParam);
    AND_A(1);
    XOR_A(1);
    LD_addr_A(wBattleAnimParam);
    LD_A_de;
    CP_A(1);
    PUSH_AF;
    LD_A(BATTLE_VARS_MOVE_ANIM);
    CALL(aGetBattleVar);
    LD_E_A;
    LD_D(0);
    POP_AF;
    JP_Z (mPlayFXAnimID);
    XOR_A_A;
    LD_addr_A(wNumHits);
    JP(mPlayFXAnimID);

}

void BattleCommand_StatUpAnim(void){
    LD_A_addr(wAttackMissed);
    AND_A_A;
    JP_NZ (mBattleCommand_MoveDelay);

    XOR_A_A;
    JR(mBattleCommand_StatUpDownAnim);

}

void BattleCommand_StatDownAnim(void){
    LD_A_addr(wAttackMissed);
    AND_A_A;
    JP_NZ (mBattleCommand_MoveDelay);

    LDH_A_addr(hBattleTurn);
    AND_A_A;
    LD_A(BATTLEANIM_ENEMY_STAT_DOWN);
    JR_Z (mBattleCommand_StatUpDownAnim);
    LD_A(BATTLEANIM_WOBBLE);

// fallthrough

    return BattleCommand_StatUpDownAnim();
}

void BattleCommand_StatUpDownAnim(void){
// Uncomment the following line to turn off the stat up/down animation.
    // REG_A = BATTLEANIM_NONE;
    LD_addr_A(wNumHits);
    XOR_A_A;
    LD_addr_A(wBattleAnimParam);
    LD_A(BATTLE_VARS_MOVE_ANIM);
    CALL(aGetBattleVar);
    LD_E_A;
    LD_D(0);
    JP(mPlayFXAnimID);

}

void BattleCommand_SwitchTurn(void){
//  switchturn

    LDH_A_addr(hBattleTurn);
    XOR_A(1);
    LDH_addr_A(hBattleTurn);
    RET;

}

void BattleCommand_RaiseSub(void){
//  raisesub

    LD_A(BATTLE_VARS_SUBSTATUS4);
    CALL(aGetBattleVar);
    BIT_A(SUBSTATUS_SUBSTITUTE);
    RET_Z ;

    CALL(av_CheckBattleScene);
    JP_C (mBattleCommand_RaiseSubNoAnim);

    XOR_A_A;
    LD_addr_A(wNumHits);
    LD_addr_A(wFXAnimID + 1);
    LD_A(0x2);
    LD_addr_A(wBattleAnimParam);
    LD_A(SUBSTITUTE);
    JP(mLoadAnim);

}

void BattleCommand_FailureText(void){
//  failuretext
//  If the move missed or failed, load the appropriate
//  text, and end the effects of multi-turn or multi-
//  hit moves.
    LD_A_addr(wAttackMissed);
    AND_A_A;
    RET_Z ;

    CALL(aGetFailureResultText);
    LD_A(BATTLE_VARS_MOVE_ANIM);
    CALL(aGetBattleVarAddr);

    CP_A(FLY);
    IF_Z goto fly_dig;
    CP_A(DIG);
    IF_Z goto fly_dig;

//  Move effect:
    INC_HL;
    LD_A_hl;

    CP_A(EFFECT_MULTI_HIT);
    IF_Z goto multihit;
    CP_A(EFFECT_DOUBLE_HIT);
    IF_Z goto multihit;
    CP_A(EFFECT_POISON_MULTI_HIT);
    IF_Z goto multihit;
    JP(mEndMoveEffect);


multihit:
    CALL(aBattleCommand_RaiseSub);
    JP(mEndMoveEffect);


fly_dig:
    LD_A(BATTLE_VARS_SUBSTATUS3);
    CALL(aGetBattleVarAddr);
    RES_hl(SUBSTATUS_UNDERGROUND);
    RES_hl(SUBSTATUS_FLYING);
    CALL(aAppearUserRaiseSub);
    JP(mEndMoveEffect);

}

void BattleCommand_ApplyDamage(void){
//  applydamage

    LD_A(BATTLE_VARS_SUBSTATUS1_OPP);
    CALL(aGetBattleVar);
    BIT_A(SUBSTATUS_ENDURE);
    IF_Z goto focus_band;

    CALL(aBattleCommand_FalseSwipe);
    LD_B(0);
    IF_NC goto damage;
    LD_B(1);
    goto damage;


focus_band:
    CALL(aGetOpponentItem);
    LD_A_B;
    CP_A(HELD_FOCUS_BAND);
    LD_B(0);
    IF_NZ goto damage;

    CALL(aBattleRandom);
    CP_A_C;
    IF_NC goto damage;
    CALL(aBattleCommand_FalseSwipe);
    LD_B(0);
    IF_NC goto damage;
    LD_B(2);


damage:
    PUSH_BC;
    CALL(aBattleCommand_ApplyDamage_update_damage_taken);
    LD_C(FALSE);
    LDH_A_addr(hBattleTurn);
    AND_A_A;
    IF_NZ goto damage_player;
    CALL(aDoEnemyDamage);
    goto done_damage;


damage_player:
    CALL(aDoPlayerDamage);


done_damage:
    POP_BC;
    LD_A_B;
    AND_A_A;
    RET_Z ;

    DEC_A;
    IF_NZ goto focus_band_text;
    LD_HL(mEnduredText);
    JP(mStdBattleTextbox);


focus_band_text:
    CALL(aGetOpponentItem);
    LD_A_hl;
    LD_addr_A(wNamedObjectIndex);
    CALL(aGetItemName);
    LD_HL(mHungOnText);
    JP(mStdBattleTextbox);


update_damage_taken:
    LD_A(BATTLE_VARS_SUBSTATUS4_OPP);
    CALL(aGetBattleVar);
    BIT_A(SUBSTATUS_SUBSTITUTE);
    RET_NZ ;

    LD_DE(wPlayerDamageTaken + 1);
    LDH_A_addr(hBattleTurn);
    AND_A_A;
    IF_NZ goto got_damage_taken;
    LD_DE(wEnemyDamageTaken + 1);


got_damage_taken:
    LD_A_addr(wCurDamage + 1);
    LD_B_A;
    LD_A_de;
    ADD_A_B;
    LD_de_A;
    DEC_DE;
    LD_A_addr(wCurDamage);
    LD_B_A;
    LD_A_de;
    ADC_A_B;
    LD_de_A;
    RET_NC ;
    LD_A(0xff);
    LD_de_A;
    INC_DE;
    LD_de_A;
    RET;

}

void GetFailureResultText(void){
    LD_HL(mDoesntAffectText);
    LD_DE(mDoesntAffectText);
    LD_A_addr(wTypeModifier);
    AND_A(0x7f);
    IF_Z goto got_text;
    LD_A(BATTLE_VARS_MOVE_EFFECT);
    CALL(aGetBattleVar);
    CP_A(EFFECT_FUTURE_SIGHT);
    LD_HL(mButItFailedText);
    LD_DE(mItFailedText);
    IF_Z goto got_text;
    LD_HL(mAttackMissedText);
    LD_DE(mAttackMissed2Text);
    LD_A_addr(wCriticalHit);
    CP_A(-1);
    IF_NZ goto got_text;
    LD_HL(mUnaffectedText);

got_text:
    CALL(aFailText_CheckOpponentProtect);
    XOR_A_A;
    LD_addr_A(wCriticalHit);

    LD_A(BATTLE_VARS_MOVE_EFFECT);
    CALL(aGetBattleVar);
    CP_A(EFFECT_JUMP_KICK);
    RET_NZ ;

    LD_A_addr(wTypeModifier);
    AND_A(0x7f);
    RET_Z ;

    LD_HL(wCurDamage);
    LD_A_hli;
    LD_B_hl;
    for(int rept = 0; rept < 3; rept++){
    SRL_A;
    RR_B;
    }
    LD_hl_B;
    DEC_HL;
    LD_hli_A;
    OR_A_B;
    IF_NZ goto do_at_least_1_damage;
    INC_A;
    LD_hl_A;

do_at_least_1_damage:
    LD_HL(mCrashedText);
    CALL(aStdBattleTextbox);
    LD_A(0x1);
    LD_addr_A(wBattleAnimParam);
    CALL(aLoadMoveAnim);
    LD_C(TRUE);
    LDH_A_addr(hBattleTurn);
    AND_A_A;
    JP_NZ (mDoEnemyDamage);
    JP(mDoPlayerDamage);

}

void FailText_CheckOpponentProtect(void){
    LD_A(BATTLE_VARS_SUBSTATUS1_OPP);
    CALL(aGetBattleVar);
    BIT_A(SUBSTATUS_PROTECT);
    IF_Z goto not_protected;
    LD_H_D;
    LD_L_E;

not_protected:
    JP(mStdBattleTextbox);

}

void BattleCommand_BideFailText(void){
    LD_A_addr(wAttackMissed);
    AND_A_A;
    RET_Z ;

    LD_A_addr(wTypeModifier);
    AND_A(0x7f);
    JP_Z (mPrintDoesntAffect);
    JP(mPrintButItFailed);

}

void BattleCommand_CriticalText(void){
//  criticaltext
//  Prints the message for critical hits or one-hit KOs.

//  If there is no message to be printed, wait 20 frames.
    LD_A_addr(wCriticalHit);
    AND_A_A;
    IF_Z goto wait;

    DEC_A;
    ADD_A_A;
    LD_HL(mBattleCommand_CriticalText_texts);
    LD_B(0);
    LD_C_A;
    ADD_HL_BC;
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    CALL(aStdBattleTextbox);

    XOR_A_A;
    LD_addr_A(wCriticalHit);


wait:
    LD_C(20);
    JP(mDelayFrames);


texts:
    //dw ['CriticalHitText'];
    //dw ['OneHitKOText'];

    return BattleCommand_StartLoop();
}

void BattleCommand_StartLoop(void){
//  startloop

    LD_HL(wPlayerRolloutCount);
    LDH_A_addr(hBattleTurn);
    AND_A_A;
    IF_Z goto ok;
    LD_HL(wEnemyRolloutCount);

ok:
    XOR_A_A;
    LD_hl_A;
    RET;

}

void BattleCommand_SuperEffectiveLoopText(void){
//  supereffectivelooptext

    LD_A(BATTLE_VARS_SUBSTATUS3);
    CALL(aGetBattleVarAddr);
    BIT_A(SUBSTATUS_IN_LOOP);
    RET_NZ ;

// fallthrough

    return BattleCommand_SuperEffectiveText();
}

void BattleCommand_SuperEffectiveText(void){
//  supereffectivetext

    LD_A_addr(wTypeModifier);
    AND_A(0x7f);
    CP_A(EFFECTIVE);
    RET_Z ;
    LD_HL(mSuperEffectiveText);
    IF_NC goto print;
    LD_HL(mNotVeryEffectiveText);

print:
    JP(mStdBattleTextbox);

}

void BattleCommand_CheckFaint(void){
//  checkfaint

//  Faint the opponent if its HP reached zero
//   and faint the user along with it if it used Destiny Bond.
//  Ends the move effect if the opponent faints.

    LD_HL(wEnemyMonHP);
    LDH_A_addr(hBattleTurn);
    AND_A_A;
    IF_Z goto got_hp;
    LD_HL(wBattleMonHP);


got_hp:
    LD_A_hli;
    OR_A_hl;
    RET_NZ ;

    LD_A(BATTLE_VARS_SUBSTATUS5_OPP);
    CALL(aGetBattleVar);
    BIT_A(SUBSTATUS_DESTINY_BOND);
    IF_Z goto no_dbond;

    LD_HL(mTookDownWithItText);
    CALL(aStdBattleTextbox);

    LDH_A_addr(hBattleTurn);
    AND_A_A;
    LD_HL(wEnemyMonMaxHP + 1);
    bccoord(2, 2, wTilemap);  // hp bar
    LD_A(0);
    IF_NZ goto got_max_hp;
    LD_HL(wBattleMonMaxHP + 1);
    bccoord(10, 9, wTilemap);  // hp bar
    LD_A(1);


got_max_hp:
    LD_addr_A(wWhichHPBar);
    LD_A_hld;
    LD_addr_A(wHPBuffer1);
    LD_A_hld;
    LD_addr_A(wHPBuffer1 + 1);
    LD_A_hl;
    LD_addr_A(wHPBuffer2);
    XOR_A_A;
    LD_hld_A;
    LD_A_hl;
    LD_addr_A(wHPBuffer2 + 1);
    XOR_A_A;
    LD_hl_A;
    LD_addr_A(wHPBuffer3);
    LD_addr_A(wHPBuffer3 + 1);
    LD_H_B;
    LD_L_C;
    PREDEF(pAnimateHPBar);
    CALL(aRefreshBattleHuds);

    CALL(aBattleCommand_SwitchTurn);
    XOR_A_A;
    LD_addr_A(wNumHits);
    LD_addr_A(wFXAnimID + 1);
    INC_A;
    LD_addr_A(wBattleAnimParam);
    LD_A(DESTINY_BOND);
    CALL(aLoadAnim);
    CALL(aBattleCommand_SwitchTurn);

    goto finish;


no_dbond:
    LD_A(BATTLE_VARS_MOVE_EFFECT);
    CALL(aGetBattleVar);
    CP_A(EFFECT_MULTI_HIT);
    IF_Z goto multiple_hit_raise_sub;
    CP_A(EFFECT_DOUBLE_HIT);
    IF_Z goto multiple_hit_raise_sub;
    CP_A(EFFECT_POISON_MULTI_HIT);
    IF_Z goto multiple_hit_raise_sub;
    CP_A(EFFECT_TRIPLE_KICK);
    IF_Z goto multiple_hit_raise_sub;
    CP_A(EFFECT_BEAT_UP);
    IF_NZ goto finish;


multiple_hit_raise_sub:
    CALL(aBattleCommand_RaiseSub);


finish:
    JP(mEndMoveEffect);

}

void BattleCommand_BuildOpponentRage(void){
//  buildopponentrage

    JP(mBattleCommand_BuildOpponentRage_start);


start:
    LD_A_addr(wAttackMissed);
    AND_A_A;
    RET_NZ ;

    LD_A(BATTLE_VARS_SUBSTATUS4_OPP);
    CALL(aGetBattleVar);
    BIT_A(SUBSTATUS_RAGE);
    RET_Z ;

    LD_DE(wEnemyRageCounter);
    LDH_A_addr(hBattleTurn);
    AND_A_A;
    IF_Z goto player;
    LD_DE(wPlayerRageCounter);

player:
    LD_A_de;
    INC_A;
    RET_Z ;
    LD_de_A;

    CALL(aBattleCommand_SwitchTurn);
    LD_HL(mRageBuildingText);
    CALL(aStdBattleTextbox);
    JP(mBattleCommand_SwitchTurn);

}

void BattleCommand_RageDamage(void){
//  ragedamage

    LD_A_addr(wCurDamage);
    LD_H_A;
    LD_B_A;
    LD_A_addr(wCurDamage + 1);
    LD_L_A;
    LD_C_A;
    LDH_A_addr(hBattleTurn);
    AND_A_A;
    LD_A_addr(wPlayerRageCounter);
    IF_Z goto rage_loop;
    LD_A_addr(wEnemyRageCounter);

rage_loop:
    AND_A_A;
    IF_Z goto done;
    DEC_A;
    ADD_HL_BC;
    IF_NC goto rage_loop;
    LD_HL(0xffff);

done:
    LD_A_H;
    LD_addr_A(wCurDamage);
    LD_A_L;
    LD_addr_A(wCurDamage + 1);
    RET;

}

void EndMoveEffect(void){
    LD_A_addr(wBattleScriptBufferAddress);
    LD_L_A;
    LD_A_addr(wBattleScriptBufferAddress + 1);
    LD_H_A;
    LD_A(endmove_command);
    LD_hli_A;
    LD_hli_A;
    LD_hl_A;
    RET;

}

void DittoMetalPowder(void){
    LD_A(MON_SPECIES);
    CALL(aBattlePartyAttr);
    LDH_A_addr(hBattleTurn);
    AND_A_A;
    LD_A_hl;
    IF_NZ goto got_species;
    LD_A_addr(wTempEnemyMonSpecies);


got_species:
    CP_A(DITTO);
    RET_NZ ;

    PUSH_BC;
    CALL(aGetOpponentItem);
    LD_A_hl;
    CP_A(METAL_POWDER);
    POP_BC;
    RET_NZ ;

    LD_A_C;
    SRL_A;
    ADD_A_C;
    LD_C_A;
    RET_NC ;

    SRL_B;
    LD_A_B;
    AND_A_A;
    IF_NZ goto done;
    INC_B;

done:
    SCF;
    RR_C;
    RET;

}

void BattleCommand_DamageStats(void){
//  damagestats

    LDH_A_addr(hBattleTurn);
    AND_A_A;
    JP_NZ (mEnemyAttackDamage);

// fallthrough

    return PlayerAttackDamage();
}

void PlayerAttackDamage(void){
//  Return move power d, player level e, enemy defense c and player attack b.

    CALL(aResetDamage);

    LD_HL(wPlayerMoveStructPower);
    LD_A_hli;
    AND_A_A;
    LD_D_A;
    RET_Z ;

    LD_A_hl;
    CP_A(SPECIAL);
    IF_NC goto special;

//  physical
    LD_HL(wEnemyMonDefense);
    LD_A_hli;
    LD_B_A;
    LD_C_hl;

    LD_A_addr(wEnemyScreens);
    BIT_A(SCREENS_REFLECT);
    IF_Z goto physicalcrit;
    SLA_C;
    RL_B;


physicalcrit:
    LD_HL(wBattleMonAttack);
    CALL(aCheckDamageStatsCritical);
    IF_C goto thickclub;

    LD_HL(wEnemyDefense);
    LD_A_hli;
    LD_B_A;
    LD_C_hl;
    LD_HL(wPlayerAttack);
    goto thickclub;


special:
    LD_HL(wEnemyMonSpclDef);
    LD_A_hli;
    LD_B_A;
    LD_C_hl;

    LD_A_addr(wEnemyScreens);
    BIT_A(SCREENS_LIGHT_SCREEN);
    IF_Z goto specialcrit;
    SLA_C;
    RL_B;


specialcrit:
    LD_HL(wBattleMonSpclAtk);
    CALL(aCheckDamageStatsCritical);
    IF_C goto lightball;

    LD_HL(wEnemySpDef);
    LD_A_hli;
    LD_B_A;
    LD_C_hl;
    LD_HL(wPlayerSpAtk);


lightball:
//  Note: Returns player special attack at hl in hl.
    CALL(aLightBallBoost);
    goto done;


thickclub:
//  Note: Returns player attack at hl in hl.
    CALL(aThickClubBoost);


done:
    CALL(aTruncateHL_BC);

    LD_A_addr(wBattleMonLevel);
    LD_E_A;
    CALL(aDittoMetalPowder);

    LD_A(1);
    AND_A_A;
    RET;

}

void TruncateHL_BC(void){

loop:
//  Truncate 16-bit values hl and bc to 8-bit values b and c respectively.
//  b = hl, c = bc

    LD_A_H;
    OR_A_B;
    IF_Z goto finish;

    SRL_B;
    RR_C;
    SRL_B;
    RR_C;

    LD_A_C;
    OR_A_B;
    IF_NZ goto done_bc;
    INC_C;


done_bc:
    SRL_H;
    RR_L;
    SRL_H;
    RR_L;

    LD_A_L;
    OR_A_H;
    IF_NZ goto finish;
    INC_L;


finish:
    LD_A_addr(wLinkMode);
    CP_A(LINK_COLOSSEUM);
    IF_Z goto done;
//  If we go back to the loop point,
//  it's the same as doing this exact
//  same check twice.
    LD_A_H;
    OR_A_B;
    IF_NZ goto loop;


done:
    LD_B_L;
    RET;

}

void CheckDamageStatsCritical(void){
//  Return carry if boosted stats should be used in damage calculations.
//  Unboosted stats should be used if the attack is a critical hit,
//   and the stage of the opponent's defense is higher than the user's attack.

    LD_A_addr(wCriticalHit);
    AND_A_A;
    SCF;
    RET_Z ;

    PUSH_HL;
    PUSH_BC;
    LDH_A_addr(hBattleTurn);
    AND_A_A;
    IF_NZ goto enemy;
    LD_A_addr(wPlayerMoveStructType);
    CP_A(SPECIAL);
//  special
    LD_A_addr(wPlayerSAtkLevel);
    LD_B_A;
    LD_A_addr(wEnemySDefLevel);
    IF_NC goto end;
//  physical
    LD_A_addr(wPlayerAtkLevel);
    LD_B_A;
    LD_A_addr(wEnemyDefLevel);
    goto end;


enemy:
    LD_A_addr(wEnemyMoveStructType);
    CP_A(SPECIAL);
//  special
    LD_A_addr(wEnemySAtkLevel);
    LD_B_A;
    LD_A_addr(wPlayerSDefLevel);
    IF_NC goto end;
//  physical
    LD_A_addr(wEnemyAtkLevel);
    LD_B_A;
    LD_A_addr(wPlayerDefLevel);

end:
    CP_A_B;
    POP_BC;
    POP_HL;
    RET;

}

void ThickClubBoost(void){
//  Return in hl the stat value at hl.

//  If the attacking monster is Cubone or Marowak and
//  it's holding a Thick Club, double it.
    PUSH_BC;
    PUSH_DE;
    LD_B(CUBONE);
    LD_C(MAROWAK);
    LD_D(THICK_CLUB);
    CALL(aSpeciesItemBoost);
    POP_DE;
    POP_BC;
    RET;

}

void LightBallBoost(void){
//  Return in hl the stat value at hl.

//  If the attacking monster is Pikachu and it's
//  holding a Light Ball, double it.
    PUSH_BC;
    PUSH_DE;
    LD_B(PIKACHU);
    LD_C(PIKACHU);
    LD_D(LIGHT_BALL);
    CALL(aSpeciesItemBoost);
    POP_DE;
    POP_BC;
    RET;

}

void SpeciesItemBoost(void){
//  Return in hl the stat value at hl.

//  If the attacking monster is species b or c and
//  it's holding item d, double it.

    LD_A_hli;
    LD_L_hl;
    LD_H_A;

    PUSH_HL;
    LD_A(MON_SPECIES);
    CALL(aBattlePartyAttr);

    LDH_A_addr(hBattleTurn);
    AND_A_A;
    LD_A_hl;
    IF_Z goto CompareSpecies;
    LD_A_addr(wTempEnemyMonSpecies);

CompareSpecies:
    POP_HL;

    CP_A_B;
    IF_Z goto GetItemHeldEffect;
    CP_A_C;
    RET_NZ ;


GetItemHeldEffect:
    PUSH_HL;
    CALL(aGetUserItem);
    LD_A_hl;
    POP_HL;
    CP_A_D;
    RET_NZ ;

//  Double the stat
    SLA_L;
    RL_H;
    RET;

}

void EnemyAttackDamage(void){
    CALL(aResetDamage);

//  No damage dealt with 0 power.
    LD_HL(wEnemyMoveStructPower);
    LD_A_hli;  // hl = wEnemyMoveStructType
    LD_D_A;
    AND_A_A;
    RET_Z ;

    LD_A_hl;
    CP_A(SPECIAL);
    IF_NC goto special;

//  physical
    LD_HL(wBattleMonDefense);
    LD_A_hli;
    LD_B_A;
    LD_C_hl;

    LD_A_addr(wPlayerScreens);
    BIT_A(SCREENS_REFLECT);
    IF_Z goto physicalcrit;
    SLA_C;
    RL_B;


physicalcrit:
    LD_HL(wEnemyMonAttack);
    CALL(aCheckDamageStatsCritical);
    IF_C goto thickclub;

    LD_HL(wPlayerDefense);
    LD_A_hli;
    LD_B_A;
    LD_C_hl;
    LD_HL(wEnemyAttack);
    goto thickclub;


special:
    LD_HL(wBattleMonSpclDef);
    LD_A_hli;
    LD_B_A;
    LD_C_hl;

    LD_A_addr(wPlayerScreens);
    BIT_A(SCREENS_LIGHT_SCREEN);
    IF_Z goto specialcrit;
    SLA_C;
    RL_B;


specialcrit:
    LD_HL(wEnemyMonSpclAtk);
    CALL(aCheckDamageStatsCritical);
    IF_C goto lightball;
    LD_HL(wPlayerSpDef);
    LD_A_hli;
    LD_B_A;
    LD_C_hl;
    LD_HL(wEnemySpAtk);


lightball:
    CALL(aLightBallBoost);
    goto done;


thickclub:
    CALL(aThickClubBoost);


done:
    CALL(aTruncateHL_BC);

    LD_A_addr(wEnemyMonLevel);
    LD_E_A;
    CALL(aDittoMetalPowder);

    LD_A(1);
    AND_A_A;
    RET;

// INCLUDE "engine/battle/move_effects/beat_up.asm"

    return BattleCommand_ClearMissDamage();
}

void BattleCommand_ClearMissDamage(void){
//  clearmissdamage
    LD_A_addr(wAttackMissed);
    AND_A_A;
    RET_Z ;

    JP(mResetDamage);

}

void HitSelfInConfusion(void){
    CALL(aResetDamage);
    LDH_A_addr(hBattleTurn);
    AND_A_A;
    LD_HL(wBattleMonDefense);
    LD_DE(wPlayerScreens);
    LD_A_addr(wBattleMonLevel);
    IF_Z goto got_it;

    LD_HL(wEnemyMonDefense);
    LD_DE(wEnemyScreens);
    LD_A_addr(wEnemyMonLevel);

got_it:
    PUSH_AF;
    LD_A_hli;
    LD_B_A;
    LD_C_hl;
    LD_A_de;
    BIT_A(SCREENS_REFLECT);
    IF_Z goto mimic_screen;

    SLA_C;
    RL_B;

mimic_screen:
    DEC_HL;
    DEC_HL;
    DEC_HL;
    LD_A_hli;
    LD_L_hl;
    LD_H_A;
    CALL(aTruncateHL_BC);
    LD_D(40);
    POP_AF;
    LD_E_A;
    RET;

}

void BattleCommand_DamageCalc(void){
//  damagecalc

//  Return a damage value for move power d, player level e, enemy defense c and player attack b.

//  Return 1 if successful, else 0.

    LD_A(BATTLE_VARS_MOVE_EFFECT);
    CALL(aGetBattleVar);

//  Selfdestruct and Explosion halve defense.
    CP_A(EFFECT_SELFDESTRUCT);
    IF_NZ goto dont_selfdestruct;

    SRL_C;
    IF_NZ goto dont_selfdestruct;
    INC_C;


dont_selfdestruct:

//  Variable-hit moves and Conversion can have a power of 0.
    CP_A(EFFECT_MULTI_HIT);
    IF_Z goto skip_zero_damage_check;

    CP_A(EFFECT_CONVERSION);
    IF_Z goto skip_zero_damage_check;

//  No damage if move power is 0.
    LD_A_D;
    AND_A_A;
    RET_Z ;


skip_zero_damage_check:
//  Minimum defense value is 1.
    LD_A_C;
    AND_A_A;
    IF_NZ goto not_dividing_by_zero;
    LD_C(1);

not_dividing_by_zero:

    XOR_A_A;
    LD_HL(hDividend);
    LD_hli_A;
    LD_hli_A;
    LD_hl_A;

//  Level * 2
    LD_A_E;
    ADD_A_A;
    IF_NC goto level_not_overflowing;
    LD_hl(1);

level_not_overflowing:
    INC_HL;
    LD_hli_A;

//  / 5
    LD_A(5);
    LD_hld_A;
    PUSH_BC;
    LD_B(4);
    CALL(aDivide);
    POP_BC;

//  + 2
    INC_hl;
    INC_hl;

//  * bp
    INC_HL;
    LD_hl_D;
    CALL(aMultiply);

//  * Attack
    LD_hl_B;
    CALL(aMultiply);

//  / Defense
    LD_hl_C;
    LD_B(4);
    CALL(aDivide);

//  / 50
    LD_hl(50);
    LD_B(0x4);
    CALL(aDivide);

//  Item boosts
    CALL(aGetUserItem);

    LD_A_B;
    AND_A_A;
    IF_Z goto DoneItem;

    LD_HL(mTypeBoostItems);


NextItem:
    LD_A_hli;
    CP_A(-1);
    IF_Z goto DoneItem;

//  Item effect
    CP_A_B;
    LD_A_hli;
    IF_NZ goto NextItem;

//  Type
    LD_B_A;
    LD_A(BATTLE_VARS_MOVE_TYPE);
    CALL(aGetBattleVar);
    CP_A_B;
    IF_NZ goto DoneItem;

//  * 100 + item effect amount
    LD_A_C;
    ADD_A(100);
    LDH_addr_A(hMultiplier);
    CALL(aMultiply);

//  / 100
    LD_A(100);
    LDH_addr_A(hDivisor);
    LD_B(4);
    CALL(aDivide);


DoneItem:
//  Critical hits
    CALL(aBattleCommand_DamageCalc_CriticalMultiplier);

//  Update wCurDamage. Max 999 (capped at 997, then add 2).
#define MAX_DAMAGE (999)
#define MIN_DAMAGE (2)
#define DAMAGE_CAP (MAX_DAMAGE - MIN_DAMAGE)

    LD_HL(wCurDamage);
    LD_B_hl;
    LDH_A_addr(hQuotient + 3);
    ADD_A_B;
    LDH_addr_A(hQuotient + 3);
    IF_NC goto dont_cap_1;

    LDH_A_addr(hQuotient + 2);
    INC_A;
    LDH_addr_A(hQuotient + 2);
    AND_A_A;
    IF_Z goto Cap;


dont_cap_1:
    LDH_A_addr(hQuotient);
    LD_B_A;
    LDH_A_addr(hQuotient + 1);
    OR_A_A;
    IF_NZ goto Cap;

    LDH_A_addr(hQuotient + 2);
    CP_A(HIGH(DAMAGE_CAP + 1));
    IF_C goto dont_cap_2;

    CP_A(HIGH(DAMAGE_CAP + 1) + 1);
    IF_NC goto Cap;

    LDH_A_addr(hQuotient + 3);
    CP_A(LOW(DAMAGE_CAP + 1));
    IF_NC goto Cap;


dont_cap_2:
    INC_HL;

    LDH_A_addr(hQuotient + 3);
    LD_B_hl;
    ADD_A_B;
    LD_hld_A;

    LDH_A_addr(hQuotient + 2);
    LD_B_hl;
    ADC_A_B;
    LD_hl_A;
    IF_C goto Cap;

    LD_A_hl;
    CP_A(HIGH(DAMAGE_CAP + 1));
    IF_C goto dont_cap_3;

    CP_A(HIGH(DAMAGE_CAP + 1) + 1);
    IF_NC goto Cap;

    INC_HL;
    LD_A_hld;
    CP_A(LOW(DAMAGE_CAP + 1));
    IF_C goto dont_cap_3;


Cap:
    LD_A(HIGH(DAMAGE_CAP));
    LD_hli_A;
    LD_A(LOW(DAMAGE_CAP));
    LD_hld_A;


dont_cap_3:
//  Add back MIN_DAMAGE (capping at 999).
    INC_HL;
    LD_A_hl;
    ADD_A(MIN_DAMAGE);
    LD_hld_A;
    IF_NC goto dont_floor;
    INC_hl;

dont_floor:

//  Returns nz and nc.
    LD_A(1);
    AND_A_A;
    RET;


CriticalMultiplier:
    LD_A_addr(wCriticalHit);
    AND_A_A;
    RET_Z ;

//  x2
    LDH_A_addr(hQuotient + 3);
    ADD_A_A;
    LDH_addr_A(hQuotient + 3);

    LDH_A_addr(hQuotient + 2);
    RL_A;
    LDH_addr_A(hQuotient + 2);

//  Cap at $ffff.
    RET_NC ;

    LD_A(0xff);
    LDH_addr_A(hQuotient + 2);
    LDH_addr_A(hQuotient + 3);

    RET;

// INCLUDE "data/types/type_boost_items.asm"

    return BattleCommand_ConstantDamage();
}

void BattleCommand_ConstantDamage(void){
//  constantdamage

    LD_HL(wBattleMonLevel);
    LDH_A_addr(hBattleTurn);
    AND_A_A;
    IF_Z goto got_turn;
    LD_HL(wEnemyMonLevel);


got_turn:
    LD_A(BATTLE_VARS_MOVE_EFFECT);
    CALL(aGetBattleVar);
    CP_A(EFFECT_LEVEL_DAMAGE);
    LD_B_hl;
    LD_A(0);
    IF_Z goto got_power;

    LD_A(BATTLE_VARS_MOVE_EFFECT);
    CALL(aGetBattleVar);
    CP_A(EFFECT_PSYWAVE);
    IF_Z goto psywave;

    CP_A(EFFECT_SUPER_FANG);
    IF_Z goto super_fang;

    CP_A(EFFECT_REVERSAL);
    IF_Z goto reversal;

    LD_A(BATTLE_VARS_MOVE_POWER);
    CALL(aGetBattleVar);
    LD_B_A;
    LD_A(0x0);
    goto got_power;


psywave:
    LD_A_B;
    SRL_A;
    ADD_A_B;
    LD_B_A;

psywave_loop:
    CALL(aBattleRandom);
    AND_A_A;
    IF_Z goto psywave_loop;
    CP_A_B;
    IF_NC goto psywave_loop;
    LD_B_A;
    LD_A(0);
    goto got_power;


super_fang:
    LD_HL(wEnemyMonHP);
    LDH_A_addr(hBattleTurn);
    AND_A_A;
    IF_Z goto got_hp;
    LD_HL(wBattleMonHP);

got_hp:
    LD_A_hli;
    SRL_A;
    LD_B_A;
    LD_A_hl;
    RR_A;
    PUSH_AF;
    LD_A_B;
    POP_BC;
    AND_A_A;
    IF_NZ goto got_power;
    OR_A_B;
    LD_A(0);
    IF_NZ goto got_power;
    LD_B(1);
    goto got_power;


got_power:
    LD_HL(wCurDamage);
    LD_hli_A;
    LD_hl_B;
    RET;


reversal:
    LD_HL(wBattleMonHP);
    LDH_A_addr(hBattleTurn);
    AND_A_A;
    IF_Z goto reversal_got_hp;
    LD_HL(wEnemyMonHP);

reversal_got_hp:
    XOR_A_A;
    LDH_addr_A(hDividend);
    LDH_addr_A(hMultiplicand + 0);
    LD_A_hli;
    LDH_addr_A(hMultiplicand + 1);
    LD_A_hli;
    LDH_addr_A(hMultiplicand + 2);
    LD_A(48);
    LDH_addr_A(hMultiplier);
    CALL(aMultiply);
    LD_A_hli;
    LD_B_A;
    LD_A_hl;
    LDH_addr_A(hDivisor);
    LD_A_B;
    AND_A_A;
    IF_Z goto skip_to_divide;

    LDH_A_addr(hProduct + 4);
    SRL_B;
    RR_A;
    SRL_B;
    RR_A;
    LDH_addr_A(hDivisor);
    LDH_A_addr(hProduct + 2);
    LD_B_A;
    SRL_B;
    LDH_A_addr(hProduct + 3);
    RR_A;
    SRL_B;
    RR_A;
    LDH_addr_A(hDividend + 3);
    LD_A_B;
    LDH_addr_A(hDividend + 2);


skip_to_divide:
    LD_B(4);
    CALL(aDivide);
    LDH_A_addr(hQuotient + 3);
    LD_B_A;
    LD_HL(mFlailReversalPower);


reversal_loop:
    LD_A_hli;
    CP_A_B;
    IF_NC goto break_loop;
    INC_HL;
    goto reversal_loop;


break_loop:
    LDH_A_addr(hBattleTurn);
    AND_A_A;
    LD_A_hl;
    IF_NZ goto notPlayersTurn;

    LD_HL(wPlayerMoveStructPower);
    LD_hl_A;
    PUSH_HL;
    CALL(aPlayerAttackDamage);
    goto notEnemysTurn;


notPlayersTurn:
    LD_HL(wEnemyMoveStructPower);
    LD_hl_A;
    PUSH_HL;
    CALL(aEnemyAttackDamage);


notEnemysTurn:
    CALL(aBattleCommand_DamageCalc);
    POP_HL;
    LD_hl(1);
    RET;

// INCLUDE "data/moves/flail_reversal_power.asm"

// INCLUDE "engine/battle/move_effects/counter.asm"

// INCLUDE "engine/battle/move_effects/encore.asm"

// INCLUDE "engine/battle/move_effects/pain_split.asm"

// INCLUDE "engine/battle/move_effects/snore.asm"

// INCLUDE "engine/battle/move_effects/conversion2.asm"

// INCLUDE "engine/battle/move_effects/lock_on.asm"

// INCLUDE "engine/battle/move_effects/sketch.asm"

    return BattleCommand_DefrostOpponent();
}

void BattleCommand_DefrostOpponent(void){
//  defrostopponent
//  Thaw the opponent if frozen, and
//  raise the user's Attack one stage.

    CALL(aAnimateCurrentMove);

    LD_A(BATTLE_VARS_STATUS_OPP);
    CALL(aGetBattleVarAddr);
    CALL(aDefrost);

    LD_A(BATTLE_VARS_MOVE_EFFECT);
    CALL(aGetBattleVarAddr);
    LD_A_hl;
    PUSH_HL;
    PUSH_AF;

    LD_A(EFFECT_ATTACK_UP);
    LD_hl_A;
    CALL(aBattleCommand_StatUp);

    POP_AF;
    POP_HL;
    LD_hl_A;
    RET;

// INCLUDE "engine/battle/move_effects/sleep_talk.asm"

// INCLUDE "engine/battle/move_effects/destiny_bond.asm"

// INCLUDE "engine/battle/move_effects/spite.asm"

// INCLUDE "engine/battle/move_effects/false_swipe.asm"

// INCLUDE "engine/battle/move_effects/heal_bell.asm"

    return FarPlayBattleAnimation();
}

void FarPlayBattleAnimation(void){
//  play animation de

    LD_A(BATTLE_VARS_SUBSTATUS3);
    CALL(aGetBattleVar);
    AND_A(1 << SUBSTATUS_FLYING | 1 << SUBSTATUS_UNDERGROUND);
    RET_NZ ;

// fallthrough

    return PlayFXAnimID();
}

void PlayFXAnimID(void){
    LD_A_E;
    LD_addr_A(wFXAnimID);
    LD_A_D;
    LD_addr_A(wFXAnimID + 1);

    LD_C(3);
    CALL(aDelayFrames);
    CALLFAR(aPlayBattleAnim);
    RET;

}

void DoEnemyDamage(void){
    LD_HL(wCurDamage);
    LD_A_hli;
    LD_B_A;
    LD_A_hl;
    OR_A_B;
    IF_Z goto did_no_damage;

    LD_A_C;
    AND_A_A;
    IF_NZ goto ignore_substitute;
    LD_A_addr(wEnemySubStatus4);
    BIT_A(SUBSTATUS_SUBSTITUTE);
    JP_NZ (mDoSubstituteDamage);


ignore_substitute:
// Subtract wCurDamage from wEnemyMonHP.
//  store original HP in little endian wHPBuffer2
    LD_A_hld;
    LD_B_A;
    LD_A_addr(wEnemyMonHP + 1);
    LD_addr_A(wHPBuffer2);
    SUB_A_B;
    LD_addr_A(wEnemyMonHP + 1);
    LD_A_hl;
    LD_B_A;
    LD_A_addr(wEnemyMonHP);
    LD_addr_A(wHPBuffer2 + 1);
    SBC_A_B;
    LD_addr_A(wEnemyMonHP);
#if defined(_DEBUG)
    PUSH_AF;
    LD_A(BANK(sSkipBattle));
    CALL(aOpenSRAM);
    LD_A_addr(sSkipBattle);
    CALL(aCloseSRAM);
    OR_A_A;
// If [sSkipBattle] is nonzero, skip the "jr nc, .no_underflow" check,
// so any attack deals maximum damage to the enemy.
    IF_NZ goto debug_skip;
    POP_AF;
    IF_NC goto no_underflow;
    PUSH_AF;

debug_skip:
    POP_AF;
#else
    IF_NC goto no_underflow;
#endif

    LD_A_addr(wHPBuffer2 + 1);
    LD_hli_A;
    LD_A_addr(wHPBuffer2);
    LD_hl_A;
    XOR_A_A;
    LD_HL(wEnemyMonHP);
    LD_hli_A;
    LD_hl_A;


no_underflow:
    LD_HL(wEnemyMonMaxHP);
    LD_A_hli;
    LD_addr_A(wHPBuffer1 + 1);
    LD_A_hl;
    LD_addr_A(wHPBuffer1);
    LD_HL(wEnemyMonHP);
    LD_A_hli;
    LD_addr_A(wHPBuffer3 + 1);
    LD_A_hl;
    LD_addr_A(wHPBuffer3);

    hlcoord(2, 2, wTilemap);
    XOR_A_A;
    LD_addr_A(wWhichHPBar);
    PREDEF(pAnimateHPBar);

did_no_damage:
    JP(mRefreshBattleHuds);

}

void DoPlayerDamage(void){
    LD_HL(wCurDamage);
    LD_A_hli;
    LD_B_A;
    LD_A_hl;
    OR_A_B;
    IF_Z goto did_no_damage;

    LD_A_C;
    AND_A_A;
    IF_NZ goto ignore_substitute;
    LD_A_addr(wPlayerSubStatus4);
    BIT_A(SUBSTATUS_SUBSTITUTE);
    JP_NZ (mDoSubstituteDamage);


ignore_substitute:
// Subtract wCurDamage from wBattleMonHP.
//  store original HP in little endian wHPBuffer2
//  store new HP in little endian wHPBuffer3
    LD_A_hld;
    LD_B_A;
    LD_A_addr(wBattleMonHP + 1);
    LD_addr_A(wHPBuffer2);
    SUB_A_B;
    LD_addr_A(wBattleMonHP + 1);
    LD_addr_A(wHPBuffer3);
    LD_B_hl;
    LD_A_addr(wBattleMonHP);
    LD_addr_A(wHPBuffer2 + 1);
    SBC_A_B;
    LD_addr_A(wBattleMonHP);
    LD_addr_A(wHPBuffer3 + 1);
    IF_NC goto no_underflow;

    LD_A_addr(wHPBuffer2 + 1);
    LD_hli_A;
    LD_A_addr(wHPBuffer2);
    LD_hl_A;
    XOR_A_A;
    LD_HL(wBattleMonHP);
    LD_hli_A;
    LD_hl_A;
    LD_HL(wHPBuffer3);
    LD_hli_A;
    LD_hl_A;


no_underflow:
    LD_HL(wBattleMonMaxHP);
    LD_A_hli;
    LD_addr_A(wHPBuffer1 + 1);
    LD_A_hl;
    LD_addr_A(wHPBuffer1);

    hlcoord(10, 9, wTilemap);
    LD_A(1);
    LD_addr_A(wWhichHPBar);
    PREDEF(pAnimateHPBar);

did_no_damage:
    JP(mRefreshBattleHuds);

}

void DoSubstituteDamage(void){
    LD_HL(mSubTookDamageText);
    CALL(aStdBattleTextbox);

    LD_DE(wEnemySubstituteHP);
    LDH_A_addr(hBattleTurn);
    AND_A_A;
    IF_Z goto got_hp;
    LD_DE(wPlayerSubstituteHP);

got_hp:

    LD_HL(wCurDamage);
    LD_A_hli;
    AND_A_A;
    IF_NZ goto broke;

    LD_A_de;
    SUB_A_hl;
    LD_de_A;
    IF_Z goto broke;
    IF_NC goto done;


broke:
    LD_A(BATTLE_VARS_SUBSTATUS4_OPP);
    CALL(aGetBattleVarAddr);
    RES_hl(SUBSTATUS_SUBSTITUTE);

    LD_HL(mSubFadedText);
    CALL(aStdBattleTextbox);

    CALL(aBattleCommand_SwitchTurn);
    CALL(aBattleCommand_LowerSubNoAnim);
    LD_A(BATTLE_VARS_SUBSTATUS3);
    CALL(aGetBattleVar);
    AND_A(1 << SUBSTATUS_FLYING | 1 << SUBSTATUS_UNDERGROUND);
    CALL_Z (aAppearUserLowerSub);
    CALL(aBattleCommand_SwitchTurn);

    LD_A(BATTLE_VARS_MOVE_EFFECT);
    CALL(aGetBattleVarAddr);
    CP_A(EFFECT_MULTI_HIT);
    IF_Z goto ok;
    CP_A(EFFECT_DOUBLE_HIT);
    IF_Z goto ok;
    CP_A(EFFECT_POISON_MULTI_HIT);
    IF_Z goto ok;
    CP_A(EFFECT_TRIPLE_KICK);
    IF_Z goto ok;
    CP_A(EFFECT_BEAT_UP);
    IF_Z goto ok;
    XOR_A_A;
    LD_hl_A;

ok:
    CALL(aRefreshBattleHuds);

done:
    JP(mResetDamage);

}

void UpdateMoveData(void){
    LD_A(BATTLE_VARS_MOVE_ANIM);
    CALL(aGetBattleVarAddr);
    LD_D_H;
    LD_E_L;

    LD_A(BATTLE_VARS_MOVE);
    CALL(aGetBattleVar);
    LD_addr_A(wCurSpecies);
    LD_addr_A(wNamedObjectIndex);

    DEC_A;
    CALL(aGetMoveData);
    CALL(aGetMoveName);
    JP(mCopyName1);

}

void BattleCommand_SleepTarget(void){
//  sleeptarget

    CALL(aGetOpponentItem);
    LD_A_B;
    CP_A(HELD_PREVENT_SLEEP);
    IF_NZ goto not_protected_by_item;

    LD_A_hl;
    LD_addr_A(wNamedObjectIndex);
    CALL(aGetItemName);
    LD_HL(mProtectedByText);
    goto fail;


not_protected_by_item:
    LD_A(BATTLE_VARS_STATUS_OPP);
    CALL(aGetBattleVarAddr);
    LD_D_H;
    LD_E_L;
    LD_A_de;
    AND_A(SLP);
    LD_HL(mAlreadyAsleepText);
    IF_NZ goto fail;

    LD_A_addr(wAttackMissed);
    AND_A_A;
    JP_NZ (mPrintDidntAffect2);

    LD_HL(mDidntAffect1Text);
    CALL(aBattleCommand_SleepTarget_CheckAIRandomFail);
    IF_C goto fail;

    LD_A_de;
    AND_A_A;
    IF_NZ goto fail;

    CALL(aCheckSubstituteOpp);
    IF_NZ goto fail;

    CALL(aAnimateCurrentMove);
    LD_B(SLP);
    LD_A_addr(wInBattleTowerBattle);
    AND_A_A;
    IF_Z goto random_loop;
    LD_B(0b011);


random_loop:
    CALL(aBattleRandom);
    AND_A_B;
    IF_Z goto random_loop;
    CP_A(SLP);
    IF_Z goto random_loop;
    INC_A;
    LD_de_A;
    CALL(aUpdateOpponentInParty);
    CALL(aRefreshBattleHuds);

    LD_HL(mFellAsleepText);
    CALL(aStdBattleTextbox);

    FARCALL(aUseHeldStatusHealingItem);

    JP_Z (mOpponentCantMove);
    RET;


fail:
    PUSH_HL;
    CALL(aAnimateFailedMove);
    POP_HL;
    JP(mStdBattleTextbox);


CheckAIRandomFail:
// Enemy turn
    LDH_A_addr(hBattleTurn);
    AND_A_A;
    IF_Z goto dont_fail;

// Not in link battle
    LD_A_addr(wLinkMode);
    AND_A_A;
    IF_NZ goto dont_fail;

    LD_A_addr(wInBattleTowerBattle);
    AND_A_A;
    IF_NZ goto dont_fail;

// Not locked-on by the enemy
    LD_A_addr(wPlayerSubStatus5);
    BIT_A(SUBSTATUS_LOCK_ON);
    IF_NZ goto dont_fail;

    CALL(aBattleRandom);
    CP_A(25 percent + 1);  // 25% chance AI fails
    RET_C ;


dont_fail:
    XOR_A_A;
    RET;

}

void BattleCommand_PoisonTarget(void){
//  poisontarget

    CALL(aCheckSubstituteOpp);
    RET_NZ ;
    LD_A(BATTLE_VARS_STATUS_OPP);
    CALL(aGetBattleVarAddr);
    AND_A_A;
    RET_NZ ;
    LD_A_addr(wTypeModifier);
    AND_A(0x7f);
    RET_Z ;
    CALL(aCheckIfTargetIsPoisonType);
    RET_Z ;
    CALL(aGetOpponentItem);
    LD_A_B;
    CP_A(HELD_PREVENT_POISON);
    RET_Z ;
    LD_A_addr(wEffectFailed);
    AND_A_A;
    RET_NZ ;
    CALL(aSafeCheckSafeguard);
    RET_NZ ;

    CALL(aPoisonOpponent);
    LD_DE(ANIM_PSN);
    CALL(aPlayOpponentBattleAnim);
    CALL(aRefreshBattleHuds);

    LD_HL(mWasPoisonedText);
    CALL(aStdBattleTextbox);

    FARCALL(aUseHeldStatusHealingItem);
    RET;

}

void BattleCommand_Poison(void){
//  poison

    LD_HL(mDoesntAffectText);
    LD_A_addr(wTypeModifier);
    AND_A(0x7f);
    JP_Z (mBattleCommand_Poison_failed);

    CALL(aCheckIfTargetIsPoisonType);
    JP_Z (mBattleCommand_Poison_failed);

    LD_A(BATTLE_VARS_STATUS_OPP);
    CALL(aGetBattleVar);
    LD_B_A;
    LD_HL(mAlreadyPoisonedText);
    AND_A(1 << PSN);
    JP_NZ (mBattleCommand_Poison_failed);

    CALL(aGetOpponentItem);
    LD_A_B;
    CP_A(HELD_PREVENT_POISON);
    IF_NZ goto do_poison;
    LD_A_hl;
    LD_addr_A(wNamedObjectIndex);
    CALL(aGetItemName);
    LD_HL(mProtectedByText);
    goto failed;


do_poison:
    LD_HL(mDidntAffect1Text);
    LD_A(BATTLE_VARS_STATUS_OPP);
    CALL(aGetBattleVar);
    AND_A_A;
    IF_NZ goto failed;

    LDH_A_addr(hBattleTurn);
    AND_A_A;
    IF_Z goto dont_sample_failure;

    LD_A_addr(wLinkMode);
    AND_A_A;
    IF_NZ goto dont_sample_failure;

    LD_A_addr(wInBattleTowerBattle);
    AND_A_A;
    IF_NZ goto dont_sample_failure;

    LD_A_addr(wPlayerSubStatus5);
    BIT_A(SUBSTATUS_LOCK_ON);
    IF_NZ goto dont_sample_failure;

    CALL(aBattleRandom);
    CP_A(25 percent + 1);  // 25% chance AI fails
    IF_C goto failed;


dont_sample_failure:
    CALL(aCheckSubstituteOpp);
    IF_NZ goto failed;
    LD_A_addr(wAttackMissed);
    AND_A_A;
    IF_NZ goto failed;
    CALL(aBattleCommand_Poison_check_toxic);
    IF_Z goto toxic;

    CALL(aBattleCommand_Poison_apply_poison);
    LD_HL(mWasPoisonedText);
    CALL(aStdBattleTextbox);
    goto finished;


toxic:
    SET_hl(SUBSTATUS_TOXIC);
    XOR_A_A;
    LD_de_A;
    CALL(aBattleCommand_Poison_apply_poison);

    LD_HL(mBadlyPoisonedText);
    CALL(aStdBattleTextbox);


finished:
    FARCALL(aUseHeldStatusHealingItem);
    RET;


failed:
    PUSH_HL;
    CALL(aAnimateFailedMove);
    POP_HL;
    JP(mStdBattleTextbox);


apply_poison:
    CALL(aAnimateCurrentMove);
    CALL(aPoisonOpponent);
    JP(mRefreshBattleHuds);


check_toxic:
    LD_A(BATTLE_VARS_SUBSTATUS5_OPP);
    CALL(aGetBattleVarAddr);
    LDH_A_addr(hBattleTurn);
    AND_A_A;
    LD_DE(wEnemyToxicCount);
    IF_Z goto ok;
    LD_DE(wPlayerToxicCount);

ok:
    LD_A(BATTLE_VARS_MOVE_EFFECT);
    CALL(aGetBattleVar);
    CP_A(EFFECT_TOXIC);
    RET;

}

void CheckIfTargetIsPoisonType(void){
    LD_DE(wEnemyMonType1);
    LDH_A_addr(hBattleTurn);
    AND_A_A;
    IF_Z goto ok;
    LD_DE(wBattleMonType1);

ok:
    LD_A_de;
    INC_DE;
    CP_A(POISON);
    RET_Z ;
    LD_A_de;
    CP_A(POISON);
    RET;

}

void PoisonOpponent(void){
    LD_A(BATTLE_VARS_STATUS_OPP);
    CALL(aGetBattleVarAddr);
    SET_hl(PSN);
    JP(mUpdateOpponentInParty);

}

void BattleCommand_DrainTarget(void){
//  draintarget
    CALL(aSapHealth);
    LD_HL(mSuckedHealthText);
    JP(mStdBattleTextbox);

}

void BattleCommand_EatDream(void){
//  eatdream
    CALL(aSapHealth);
    LD_HL(mDreamEatenText);
    JP(mStdBattleTextbox);

}

void SapHealth(void){
// Divide damage by 2, store it in hDividend
    LD_HL(wCurDamage);
    LD_A_hli;
    SRL_A;
    LDH_addr_A(hDividend);
    LD_B_A;
    LD_A_hl;
    RR_A;
    LDH_addr_A(hDividend + 1);
    OR_A_B;
    IF_NZ goto at_least_one;
    LD_A(1);
    LDH_addr_A(hDividend + 1);

at_least_one:

    LD_HL(wBattleMonHP);
    LD_DE(wBattleMonMaxHP);
    LDH_A_addr(hBattleTurn);
    AND_A_A;
    IF_Z goto battlemonhp;
    LD_HL(wEnemyMonHP);
    LD_DE(wEnemyMonMaxHP);

battlemonhp:

// Store current HP in little endian wHPBuffer2
    LD_BC(wHPBuffer2 + 1);
    LD_A_hli;
    LD_bc_A;
    LD_A_hl;
    DEC_BC;
    LD_bc_A;

// Store max HP in little endian wHPBuffer1
    LD_A_de;
    DEC_BC;
    LD_bc_A;
    INC_DE;
    LD_A_de;
    DEC_BC;
    LD_bc_A;

// Add hDividend to current HP and copy it to little endian wHPBuffer3
    LDH_A_addr(hDividend + 1);
    LD_B_hl;
    ADD_A_B;
    LD_hld_A;
    LD_addr_A(wHPBuffer3);
    LDH_A_addr(hDividend);
    LD_B_hl;
    ADC_A_B;
    LD_hli_A;
    LD_addr_A(wHPBuffer3 + 1);
    IF_C goto max_hp;

// Subtract current HP from max HP (to see if we have more than max HP)
    LD_A_hld;
    LD_B_A;
    LD_A_de;
    DEC_DE;
    SUB_A_B;
    LD_A_hli;
    LD_B_A;
    LD_A_de;
    INC_DE;
    SBC_A_B;
    IF_NC goto finish;


max_hp:
// Load max HP into current HP and copy it to little endian wHPBuffer3
    LD_A_de;
    LD_hld_A;
    LD_addr_A(wHPBuffer3);
    DEC_DE;
    LD_A_de;
    LD_hli_A;
    LD_addr_A(wHPBuffer3 + 1);
    INC_DE;


finish:
    LDH_A_addr(hBattleTurn);
    AND_A_A;
    hlcoord(10, 9, wTilemap);
    LD_A(0x1);
    IF_Z goto hp_bar;
    hlcoord(2, 2, wTilemap);
    XOR_A_A;

hp_bar:
    LD_addr_A(wWhichHPBar);
    PREDEF(pAnimateHPBar);
    CALL(aRefreshBattleHuds);
    JP(mUpdateBattleMonInParty);

}

void BattleCommand_BurnTarget(void){
//  burntarget

    XOR_A_A;
    LD_addr_A(wNumHits);
    CALL(aCheckSubstituteOpp);
    RET_NZ ;
    LD_A(BATTLE_VARS_STATUS_OPP);
    CALL(aGetBattleVarAddr);
    AND_A_A;
    JP_NZ (mDefrost);
    LD_A_addr(wTypeModifier);
    AND_A(0x7f);
    RET_Z ;
    CALL(aCheckMoveTypeMatchesTarget);  // Don't burn a Fire-type
    RET_Z ;
    CALL(aGetOpponentItem);
    LD_A_B;
    CP_A(HELD_PREVENT_BURN);
    RET_Z ;
    LD_A_addr(wEffectFailed);
    AND_A_A;
    RET_NZ ;
    CALL(aSafeCheckSafeguard);
    RET_NZ ;
    LD_A(BATTLE_VARS_STATUS_OPP);
    CALL(aGetBattleVarAddr);
    SET_hl(BRN);
    CALL(aUpdateOpponentInParty);
    LD_HL(mApplyBrnEffectOnAttack);
    CALL(aCallBattleCore);
    LD_DE(ANIM_BRN);
    CALL(aPlayOpponentBattleAnim);
    CALL(aRefreshBattleHuds);

    LD_HL(mWasBurnedText);
    CALL(aStdBattleTextbox);

    FARCALL(aUseHeldStatusHealingItem);
    RET;

}

void Defrost(void){
    LD_A_hl;
    AND_A(1 << FRZ);
    RET_Z ;

    XOR_A_A;
    LD_hl_A;

    LDH_A_addr(hBattleTurn);
    AND_A_A;
    LD_A_addr(wCurOTMon);
    LD_HL(wOTPartyMon1Status);
    IF_Z goto ok;
    LD_HL(wPartyMon1Status);
    LD_A_addr(wCurBattleMon);

ok:

    CALL(aGetPartyLocation);
    XOR_A_A;
    LD_hl_A;
    CALL(aUpdateOpponentInParty);

    LD_HL(mDefrostedOpponentText);
    JP(mStdBattleTextbox);

}

void BattleCommand_FreezeTarget(void){
//  freezetarget

    XOR_A_A;
    LD_addr_A(wNumHits);
    CALL(aCheckSubstituteOpp);
    RET_NZ ;
    LD_A(BATTLE_VARS_STATUS_OPP);
    CALL(aGetBattleVarAddr);
    AND_A_A;
    RET_NZ ;
    LD_A_addr(wTypeModifier);
    AND_A(0x7f);
    RET_Z ;
    LD_A_addr(wBattleWeather);
    CP_A(WEATHER_SUN);
    RET_Z ;
    CALL(aCheckMoveTypeMatchesTarget);  // Don't freeze an Ice-type
    RET_Z ;
    CALL(aGetOpponentItem);
    LD_A_B;
    CP_A(HELD_PREVENT_FREEZE);
    RET_Z ;
    LD_A_addr(wEffectFailed);
    AND_A_A;
    RET_NZ ;
    CALL(aSafeCheckSafeguard);
    RET_NZ ;
    LD_A(BATTLE_VARS_STATUS_OPP);
    CALL(aGetBattleVarAddr);
    SET_hl(FRZ);
    CALL(aUpdateOpponentInParty);
    LD_DE(ANIM_FRZ);
    CALL(aPlayOpponentBattleAnim);
    CALL(aRefreshBattleHuds);

    LD_HL(mWasFrozenText);
    CALL(aStdBattleTextbox);

    FARCALL(aUseHeldStatusHealingItem);
    RET_NZ ;

    CALL(aOpponentCantMove);
    CALL(aEndRechargeOpp);
    LD_HL(wEnemyJustGotFrozen);
    LDH_A_addr(hBattleTurn);
    AND_A_A;
    IF_Z goto finish;
    LD_HL(wPlayerJustGotFrozen);

finish:
    LD_hl(0x1);
    RET;

}

void BattleCommand_ParalyzeTarget(void){
//  paralyzetarget

    XOR_A_A;
    LD_addr_A(wNumHits);
    CALL(aCheckSubstituteOpp);
    RET_NZ ;
    LD_A(BATTLE_VARS_STATUS_OPP);
    CALL(aGetBattleVarAddr);
    AND_A_A;
    RET_NZ ;
    LD_A_addr(wTypeModifier);
    AND_A(0x7f);
    RET_Z ;
    CALL(aGetOpponentItem);
    LD_A_B;
    CP_A(HELD_PREVENT_PARALYZE);
    RET_Z ;
    LD_A_addr(wEffectFailed);
    AND_A_A;
    RET_NZ ;
    CALL(aSafeCheckSafeguard);
    RET_NZ ;
    LD_A(BATTLE_VARS_STATUS_OPP);
    CALL(aGetBattleVarAddr);
    SET_hl(PAR);
    CALL(aUpdateOpponentInParty);
    LD_HL(mApplyPrzEffectOnSpeed);
    CALL(aCallBattleCore);
    LD_DE(ANIM_PAR);
    CALL(aPlayOpponentBattleAnim);
    CALL(aRefreshBattleHuds);
    CALL(aPrintParalyze);
    LD_HL(mUseHeldStatusHealingItem);
    JP(mCallBattleCore);

}

void BattleCommand_AttackUp(void){
//  attackup
    LD_B(ATTACK);
    JR(mBattleCommand_StatUp);

}

void BattleCommand_DefenseUp(void){
//  defenseup
    LD_B(DEFENSE);
    JR(mBattleCommand_StatUp);

}

void BattleCommand_SpeedUp(void){
//  speedup
    LD_B(SPEED);
    JR(mBattleCommand_StatUp);

}

void BattleCommand_SpecialAttackUp(void){
//  specialattackup
    LD_B(SP_ATTACK);
    JR(mBattleCommand_StatUp);

}

void BattleCommand_SpecialDefenseUp(void){
//  specialdefenseup
    LD_B(SP_DEFENSE);
    JR(mBattleCommand_StatUp);

}

void BattleCommand_AccuracyUp(void){
//  accuracyup
    LD_B(ACCURACY);
    JR(mBattleCommand_StatUp);

}

void BattleCommand_EvasionUp(void){
//  evasionup
    LD_B(EVASION);
    JR(mBattleCommand_StatUp);

}

void BattleCommand_AttackUp2(void){
//  attackup2
    LD_B(0x10 | ATTACK);
    JR(mBattleCommand_StatUp);

}

void BattleCommand_DefenseUp2(void){
//  defenseup2
    LD_B(0x10 | DEFENSE);
    JR(mBattleCommand_StatUp);

}

void BattleCommand_SpeedUp2(void){
//  speedup2
    LD_B(0x10 | SPEED);
    JR(mBattleCommand_StatUp);

}

void BattleCommand_SpecialAttackUp2(void){
//  specialattackup2
    LD_B(0x10 | SP_ATTACK);
    JR(mBattleCommand_StatUp);

}

void BattleCommand_SpecialDefenseUp2(void){
//  specialdefenseup2
    LD_B(0x10 | SP_DEFENSE);
    JR(mBattleCommand_StatUp);

}

void BattleCommand_AccuracyUp2(void){
//  accuracyup2
    LD_B(0x10 | ACCURACY);
    JR(mBattleCommand_StatUp);

}

void BattleCommand_EvasionUp2(void){
//  evasionup2
    LD_B(0x10 | EVASION);
    JR(mBattleCommand_StatUp);

}

void BattleCommand_StatUp(void){
//  statup
    CALL(aRaiseStat);
    LD_A_addr(wFailedMessage);
    AND_A_A;
    RET_NZ ;
    JP(mMinimizeDropSub);

}

void RaiseStat(void){
    LD_A_B;
    LD_addr_A(wLoweredStat);
    LD_HL(wPlayerStatLevels);
    LDH_A_addr(hBattleTurn);
    AND_A_A;
    IF_Z goto got_stat_levels;
    LD_HL(wEnemyStatLevels);

got_stat_levels:
    LD_A_addr(wAttackMissed);
    AND_A_A;
    JP_NZ (mRaiseStat_stat_raise_failed);
    LD_A_addr(wEffectFailed);
    AND_A_A;
    JP_NZ (mRaiseStat_stat_raise_failed);
    LD_A_addr(wLoweredStat);
    AND_A(0xf);
    LD_C_A;
    LD_B(0);
    ADD_HL_BC;
    LD_B_hl;
    INC_B;
    LD_A(0xd);
    CP_A_B;
    JP_C (mRaiseStat_cant_raise_stat);
    LD_A_addr(wLoweredStat);
    AND_A(0xf0);
    IF_Z goto got_num_stages;
    INC_B;
    LD_A(0xd);
    CP_A_B;
    IF_NC goto got_num_stages;
    LD_B_A;

got_num_stages:
    LD_hl_B;
    PUSH_HL;
    LD_A_C;
    CP_A(0x5);
    IF_NC goto done_calcing_stats;
    LD_HL(wBattleMonStats + 1);
    LD_DE(wPlayerStats);
    LDH_A_addr(hBattleTurn);
    AND_A_A;
    IF_Z goto got_stats_pointer;
    LD_HL(wEnemyMonStats + 1);
    LD_DE(wEnemyStats);

got_stats_pointer:
    PUSH_BC;
    SLA_C;
    LD_B(0);
    ADD_HL_BC;
    LD_A_C;
    ADD_A_E;
    LD_E_A;
    IF_NC goto no_carry;
    INC_D;

no_carry:
    POP_BC;
    LD_A_hld;
    SUB_A(LOW(MAX_STAT_VALUE));
    IF_NZ goto not_already_max;
    LD_A_hl;
    SBC_A(HIGH(MAX_STAT_VALUE));
    JP_Z (mRaiseStat_stats_already_max);

not_already_max:
    LDH_A_addr(hBattleTurn);
    AND_A_A;
    IF_Z goto calc_player_stats;
    CALL(aCalcEnemyStats);
    goto done_calcing_stats;


calc_player_stats:
    CALL(aCalcPlayerStats);

done_calcing_stats:
    POP_HL;
    XOR_A_A;
    LD_addr_A(wFailedMessage);
    RET;


stats_already_max:
    POP_HL;
    DEC_hl;
// fallthrough


cant_raise_stat:
    LD_A(0x2);
    LD_addr_A(wFailedMessage);
    LD_A(0x1);
    LD_addr_A(wAttackMissed);
    RET;


stat_raise_failed:
    LD_A(0x1);
    LD_addr_A(wFailedMessage);
    RET;

}

void MinimizeDropSub(void){
//  Lower the substitute if we're minimizing

    LD_BC(wPlayerMinimized);
    LD_HL(mDropPlayerSub);
    LDH_A_addr(hBattleTurn);
    AND_A_A;
    IF_Z goto do_player;
    LD_BC(wEnemyMinimized);
    LD_HL(mDropEnemySub);

do_player:
    LD_A(BATTLE_VARS_MOVE_ANIM);
    CALL(aGetBattleVar);
    CP_A(MINIMIZE);
    RET_NZ ;

    LD_A(0x1);
    LD_bc_A;
    CALL(av_CheckBattleScene);
    RET_NC ;

    XOR_A_A;
    LDH_addr_A(hBGMapMode);
    CALL(aCallBattleCore);
    CALL(aWaitBGMap);
    JP(mBattleCommand_MoveDelay);

}

void BattleCommand_AttackDown(void){
//  attackdown
    LD_A(ATTACK);
    JR(mBattleCommand_StatDown);

}

void BattleCommand_DefenseDown(void){
//  defensedown
    LD_A(DEFENSE);
    JR(mBattleCommand_StatDown);

}

void BattleCommand_SpeedDown(void){
//  speeddown
    LD_A(SPEED);
    JR(mBattleCommand_StatDown);

}

void BattleCommand_SpecialAttackDown(void){
//  specialattackdown
    LD_A(SP_ATTACK);
    JR(mBattleCommand_StatDown);

}

void BattleCommand_SpecialDefenseDown(void){
//  specialdefensedown
    LD_A(SP_DEFENSE);
    JR(mBattleCommand_StatDown);

}

void BattleCommand_AccuracyDown(void){
//  accuracydown
    LD_A(ACCURACY);
    JR(mBattleCommand_StatDown);

}

void BattleCommand_EvasionDown(void){
//  evasiondown
    LD_A(EVASION);
    JR(mBattleCommand_StatDown);

}

void BattleCommand_AttackDown2(void){
//  attackdown2
    LD_A(0x10 | ATTACK);
    JR(mBattleCommand_StatDown);

}

void BattleCommand_DefenseDown2(void){
//  defensedown2
    LD_A(0x10 | DEFENSE);
    JR(mBattleCommand_StatDown);

}

void BattleCommand_SpeedDown2(void){
//  speeddown2
    LD_A(0x10 | SPEED);
    JR(mBattleCommand_StatDown);

}

void BattleCommand_SpecialAttackDown2(void){
//  specialattackdown2
    LD_A(0x10 | SP_ATTACK);
    JR(mBattleCommand_StatDown);

}

void BattleCommand_SpecialDefenseDown2(void){
//  specialdefensedown2
    LD_A(0x10 | SP_DEFENSE);
    JR(mBattleCommand_StatDown);

}

void BattleCommand_AccuracyDown2(void){
//  accuracydown2
    LD_A(0x10 | ACCURACY);
    JR(mBattleCommand_StatDown);

}

void BattleCommand_EvasionDown2(void){
//  evasiondown2
    LD_A(0x10 | EVASION);

    return BattleCommand_StatDown();
}

void BattleCommand_StatDown(void){
//  statdown

    LD_addr_A(wLoweredStat);

    CALL(aCheckMist);
    JP_NZ (mBattleCommand_StatDown_Mist);

    LD_HL(wEnemyStatLevels);
    LDH_A_addr(hBattleTurn);
    AND_A_A;
    IF_Z goto GetStatLevel;
    LD_HL(wPlayerStatLevels);


GetStatLevel:
//  Attempt to lower the stat.
    LD_A_addr(wLoweredStat);
    AND_A(0xf);
    LD_C_A;
    LD_B(0);
    ADD_HL_BC;
    LD_B_hl;
    DEC_B;
    JP_Z (mBattleCommand_StatDown_CantLower);

//  Sharply lower the stat if applicable.
    LD_A_addr(wLoweredStat);
    AND_A(0xf0);
    IF_Z goto ComputerMiss;
    DEC_B;
    IF_NZ goto ComputerMiss;
    INC_B;


ComputerMiss:
//  Computer opponents have a 25% chance of failing.
    LDH_A_addr(hBattleTurn);
    AND_A_A;
    IF_Z goto DidntMiss;

    LD_A_addr(wLinkMode);
    AND_A_A;
    IF_NZ goto DidntMiss;

    LD_A_addr(wInBattleTowerBattle);
    AND_A_A;
    IF_NZ goto DidntMiss;

//  Lock-On still always works.
    LD_A_addr(wPlayerSubStatus5);
    BIT_A(SUBSTATUS_LOCK_ON);
    IF_NZ goto DidntMiss;

//  Attacking moves that also lower accuracy are unaffected.
    LD_A(BATTLE_VARS_MOVE_EFFECT);
    CALL(aGetBattleVar);
    CP_A(EFFECT_ACCURACY_DOWN_HIT);
    IF_Z goto DidntMiss;

    CALL(aBattleRandom);
    CP_A(25 percent + 1);  // 25% chance AI fails
    IF_C goto Failed;


DidntMiss:
    CALL(aCheckSubstituteOpp);
    IF_NZ goto Failed;

    LD_A_addr(wAttackMissed);
    AND_A_A;
    IF_NZ goto Failed;

    LD_A_addr(wEffectFailed);
    AND_A_A;
    IF_NZ goto Failed;

    CALL(aCheckHiddenOpponent);
    IF_NZ goto Failed;

//  Accuracy/Evasion reduction don't involve stats.
    LD_hl_B;
    LD_A_C;
    CP_A(ACCURACY);
    IF_NC goto Hit;

    PUSH_HL;
    LD_HL(wEnemyMonAttack + 1);
    LD_DE(wEnemyStats);
    LDH_A_addr(hBattleTurn);
    AND_A_A;
    IF_Z goto do_enemy;
    LD_HL(wBattleMonAttack + 1);
    LD_DE(wPlayerStats);

do_enemy:
    CALL(aTryLowerStat);
    POP_HL;
    IF_Z goto CouldntLower;


Hit:
    XOR_A_A;
    LD_addr_A(wFailedMessage);
    RET;


CouldntLower:
    INC_hl;

CantLower:
    LD_A(3);
    LD_addr_A(wFailedMessage);
    LD_A(1);
    LD_addr_A(wAttackMissed);
    RET;


Failed:
    LD_A(1);
    LD_addr_A(wFailedMessage);
    LD_addr_A(wAttackMissed);
    RET;


Mist:
    LD_A(2);
    LD_addr_A(wFailedMessage);
    LD_A(1);
    LD_addr_A(wAttackMissed);
    RET;

}

void CheckMist(void){
    LD_A(BATTLE_VARS_MOVE_EFFECT);
    CALL(aGetBattleVar);
    CP_A(EFFECT_ATTACK_DOWN);
    IF_C goto dont_check_mist;
    CP_A(EFFECT_EVASION_DOWN + 1);
    IF_C goto check_mist;
    CP_A(EFFECT_ATTACK_DOWN_2);
    IF_C goto dont_check_mist;
    CP_A(EFFECT_EVASION_DOWN_2 + 1);
    IF_C goto check_mist;
    CP_A(EFFECT_ATTACK_DOWN_HIT);
    IF_C goto dont_check_mist;
    CP_A(EFFECT_EVASION_DOWN_HIT + 1);
    IF_C goto check_mist;

dont_check_mist:
    XOR_A_A;
    RET;


check_mist:
    LD_A(BATTLE_VARS_SUBSTATUS4_OPP);
    CALL(aGetBattleVar);
    BIT_A(SUBSTATUS_MIST);
    RET;

}

void BattleCommand_StatUpMessage(void){
    LD_A_addr(wFailedMessage);
    AND_A_A;
    RET_NZ ;
    LD_A_addr(wLoweredStat);
    AND_A(0xf);
    LD_B_A;
    INC_B;
    CALL(aGetStatName);
    LD_HL(mBattleCommand_StatUpMessage_stat);
    JP(mBattleTextbox);


stat:
    //text_far ['Text_BattleEffectActivate']
    //text_asm ['?']
    LD_HL(mBattleCommand_StatUpMessage_BattleStatWentUpText);
    LD_A_addr(wLoweredStat);
    AND_A(0xf0);
    RET_Z ;
    LD_HL(mBattleCommand_StatUpMessage_BattleStatWentWayUpText);
    RET;


BattleStatWentWayUpText:
    //text_far ['_BattleStatWentWayUpText']
    //text_end ['?']


BattleStatWentUpText:
    //text_far ['_BattleStatWentUpText']
    //text_end ['?']

    return BattleCommand_StatDownMessage();
}

void BattleCommand_StatDownMessage(void){
    LD_A_addr(wFailedMessage);
    AND_A_A;
    RET_NZ ;
    LD_A_addr(wLoweredStat);
    AND_A(0xf);
    LD_B_A;
    INC_B;
    CALL(aGetStatName);
    LD_HL(mBattleCommand_StatDownMessage_stat);
    JP(mBattleTextbox);


stat:
    //text_far ['Text_BattleFoeEffectActivate']
    //text_asm ['?']
    LD_HL(mBattleCommand_StatDownMessage_BattleStatFellText);
    LD_A_addr(wLoweredStat);
    AND_A(0xf0);
    RET_Z ;
    LD_HL(mBattleCommand_StatDownMessage_BattleStatSharplyFellText);
    RET;


BattleStatSharplyFellText:
    //text_far ['_BattleStatSharplyFellText']
    //text_end ['?']


BattleStatFellText:
    //text_far ['_BattleStatFellText']
    //text_end ['?']

    return TryLowerStat();
}

void TryLowerStat(void){
//  Lower stat c from stat struct hl (buffer de).

    PUSH_BC;
    SLA_C;
    LD_B(0);
    ADD_HL_BC;
// add de, c
    LD_A_C;
    ADD_A_E;
    LD_E_A;
    IF_NC goto no_carry;
    INC_D;

no_carry:
    POP_BC;

//  The lowest possible stat is 1.
    LD_A_hld;
    SUB_A(1);
    IF_NZ goto not_min;
    LD_A_hl;
    AND_A_A;
    RET_Z ;


not_min:
    LDH_A_addr(hBattleTurn);
    AND_A_A;
    IF_Z goto Player;

    CALL(aBattleCommand_SwitchTurn);
    CALL(aCalcPlayerStats);
    CALL(aBattleCommand_SwitchTurn);
    goto end;


Player:
    CALL(aBattleCommand_SwitchTurn);
    CALL(aCalcEnemyStats);
    CALL(aBattleCommand_SwitchTurn);

end:
    LD_A(1);
    AND_A_A;
    RET;

}

void BattleCommand_StatUpFailText(void){
//  statupfailtext
    LD_A_addr(wFailedMessage);
    AND_A_A;
    RET_Z ;
    PUSH_AF;
    CALL(aBattleCommand_MoveDelay);
    POP_AF;
    DEC_A;
    JP_Z (mTryPrintButItFailed);
    LD_A_addr(wLoweredStat);
    AND_A(0xf);
    LD_B_A;
    INC_B;
    CALL(aGetStatName);
    LD_HL(mWontRiseAnymoreText);
    JP(mStdBattleTextbox);

}

void BattleCommand_StatDownFailText(void){
//  statdownfailtext
    LD_A_addr(wFailedMessage);
    AND_A_A;
    RET_Z ;
    PUSH_AF;
    CALL(aBattleCommand_MoveDelay);
    POP_AF;
    DEC_A;
    JP_Z (mTryPrintButItFailed);
    DEC_A;
    LD_HL(mProtectedByMistText);
    JP_Z (mStdBattleTextbox);
    LD_A_addr(wLoweredStat);
    AND_A(0xf);
    LD_B_A;
    INC_B;
    CALL(aGetStatName);
    LD_HL(mWontDropAnymoreText);
    JP(mStdBattleTextbox);

}

void GetStatName(void){
    LD_HL(mStatNames);
    LD_C(0x50);

CheckName:
    DEC_B;
    IF_Z goto Copy;

GetName:
    LD_A_hli;
    CP_A_C;
    IF_Z goto CheckName;
    goto GetName;


Copy:
    LD_DE(wStringBuffer2);
    LD_BC(STRING_BUFFER_LENGTH);
    JP(mCopyBytes);

// INCLUDE "data/battle/stat_names.asm"

// INCLUDE "data/battle/stat_multipliers.asm"

    return BattleCommand_AllStatsUp();
}

void BattleCommand_AllStatsUp(void){
//  allstatsup

//  Attack
    CALL(aResetMiss);
    CALL(aBattleCommand_AttackUp);
    CALL(aBattleCommand_StatUpMessage);

//  Defense
    CALL(aResetMiss);
    CALL(aBattleCommand_DefenseUp);
    CALL(aBattleCommand_StatUpMessage);

//  Speed
    CALL(aResetMiss);
    CALL(aBattleCommand_SpeedUp);
    CALL(aBattleCommand_StatUpMessage);

//  Special Attack
    CALL(aResetMiss);
    CALL(aBattleCommand_SpecialAttackUp);
    CALL(aBattleCommand_StatUpMessage);

//  Special Defense
    CALL(aResetMiss);
    CALL(aBattleCommand_SpecialDefenseUp);
    JP(mBattleCommand_StatUpMessage);

}

void ResetMiss(void){
    XOR_A_A;
    LD_addr_A(wAttackMissed);
    RET;

}

void LowerStat(void){
    LD_addr_A(wLoweredStat);

    LD_HL(wPlayerStatLevels);
    LDH_A_addr(hBattleTurn);
    AND_A_A;
    IF_Z goto got_target;
    LD_HL(wEnemyStatLevels);


got_target:
    LD_A_addr(wLoweredStat);
    AND_A(0xf);
    LD_C_A;
    LD_B(0);
    ADD_HL_BC;
    LD_B_hl;
    DEC_B;
    IF_Z goto cant_lower_anymore;

    LD_A_addr(wLoweredStat);
    AND_A(0xf0);
    IF_Z goto got_num_stages;
    DEC_B;
    IF_NZ goto got_num_stages;
    INC_B;


got_num_stages:
    LD_hl_B;
    LD_A_C;
    CP_A(5);
    IF_NC goto accuracy_evasion;

    PUSH_HL;
    LD_HL(wBattleMonStats + 1);
    LD_DE(wPlayerStats);
    LDH_A_addr(hBattleTurn);
    AND_A_A;
    IF_Z goto got_target_2;
    LD_HL(wEnemyMonStats + 1);
    LD_DE(wEnemyStats);


got_target_2:
    CALL(aTryLowerStat);
    POP_HL;
    IF_Z goto failed;


accuracy_evasion:
    LDH_A_addr(hBattleTurn);
    AND_A_A;
    IF_Z goto player;

    CALL(aCalcEnemyStats);

    goto finish;


player:
    CALL(aCalcPlayerStats);


finish:
    XOR_A_A;
    LD_addr_A(wFailedMessage);
    RET;


failed:
    INC_hl;


cant_lower_anymore:
    LD_A(2);
    LD_addr_A(wFailedMessage);
    RET;

}

void BattleCommand_TriStatusChance(void){
//  tristatuschance

    CALL(aBattleCommand_EffectChance);

loop:
// 1/3 chance of each status
    CALL(aBattleRandom);
    SWAP_A;
    AND_A(0b11);
    IF_Z goto loop;
    DEC_A;
    // LD_HL(mBattleCommand_TriStatusChance_StatusCommands);
    // RST(aJumpTable);
    switch(REG_A) {
        case 0: CALL(aBattleCommand_ParalyzeTarget); break;
        case 1: CALL(aBattleCommand_FreezeTarget); break;
        case 2: CALL(aBattleCommand_BurnTarget); break;
    }
    RET;


StatusCommands:
    //dw ['BattleCommand_ParalyzeTarget'];  // paralyze
    //dw ['BattleCommand_FreezeTarget'];  // freeze
    //dw ['BattleCommand_BurnTarget'];  // burn

    return BattleCommand_Curl();
}

void BattleCommand_Curl(void){
//  curl
    LD_A(BATTLE_VARS_SUBSTATUS2);
    CALL(aGetBattleVarAddr);
    SET_hl(SUBSTATUS_CURLED);
    RET;

}

void BattleCommand_RaiseSubNoAnim(void){
    LD_HL(mGetBattleMonBackpic);
    LDH_A_addr(hBattleTurn);
    AND_A_A;
    IF_Z goto PlayerTurn;
    LD_HL(mGetEnemyMonFrontpic);

PlayerTurn:
    XOR_A_A;
    LDH_addr_A(hBGMapMode);
    CALL(aCallBattleCore);
    JP(mWaitBGMap);

}

void BattleCommand_LowerSubNoAnim(void){
    LD_HL(mDropPlayerSub);
    LDH_A_addr(hBattleTurn);
    AND_A_A;
    IF_Z goto PlayerTurn;
    LD_HL(mDropEnemySub);

PlayerTurn:
    XOR_A_A;
    LDH_addr_A(hBGMapMode);
    CALL(aCallBattleCore);
    JP(mWaitBGMap);

}

void CalcPlayerStats(void){
    LD_HL(wPlayerAtkLevel);
    LD_DE(wPlayerStats);
    LD_BC(wBattleMonAttack);

    LD_A(5);
    CALL(aCalcBattleStats);

    LD_HL(mBadgeStatBoosts);
    CALL(aCallBattleCore);

    CALL(aBattleCommand_SwitchTurn);

    LD_HL(mApplyPrzEffectOnSpeed);
    CALL(aCallBattleCore);

    LD_HL(mApplyBrnEffectOnAttack);
    CALL(aCallBattleCore);

    JP(mBattleCommand_SwitchTurn);

}

void CalcEnemyStats(void){
    LD_HL(wEnemyAtkLevel);
    LD_DE(wEnemyStats);
    LD_BC(wEnemyMonAttack);

    LD_A(5);
    CALL(aCalcBattleStats);

    CALL(aBattleCommand_SwitchTurn);

    LD_HL(mApplyPrzEffectOnSpeed);
    CALL(aCallBattleCore);

    LD_HL(mApplyBrnEffectOnAttack);
    CALL(aCallBattleCore);

    JP(mBattleCommand_SwitchTurn);

}

void CalcBattleStats(void){

loop:
    PUSH_AF;
    LD_A_hli;
    PUSH_HL;
    PUSH_BC;

    LD_C_A;
    DEC_C;
    LD_B(0);
    LD_HL(mStatLevelMultipliers);
    ADD_HL_BC;
    ADD_HL_BC;

    XOR_A_A;
    LDH_addr_A(hMultiplicand + 0);
    LD_A_de;
    LDH_addr_A(hMultiplicand + 1);
    INC_DE;
    LD_A_de;
    LDH_addr_A(hMultiplicand + 2);
    INC_DE;

    LD_A_hli;
    LDH_addr_A(hMultiplier);
    CALL(aMultiply);

    LD_A_hl;
    LDH_addr_A(hDivisor);
    LD_B(4);
    CALL(aDivide);

    LDH_A_addr(hQuotient + 2);
    LD_B_A;
    LDH_A_addr(hQuotient + 3);
    OR_A_B;
    IF_NZ goto check_maxed_out;

    LD_A(1);
    LDH_addr_A(hQuotient + 3);
    goto not_maxed_out;


check_maxed_out:
    LDH_A_addr(hQuotient + 3);
    CP_A(LOW(MAX_STAT_VALUE));
    LD_A_B;
    SBC_A(HIGH(MAX_STAT_VALUE));
    IF_C goto not_maxed_out;

    LD_A(LOW(MAX_STAT_VALUE));
    LDH_addr_A(hQuotient + 3);
    LD_A(HIGH(MAX_STAT_VALUE));
    LDH_addr_A(hQuotient + 2);


not_maxed_out:
    POP_BC;
    LDH_A_addr(hQuotient + 2);
    LD_bc_A;
    INC_BC;
    LDH_A_addr(hQuotient + 3);
    LD_bc_A;
    INC_BC;
    POP_HL;
    POP_AF;
    DEC_A;
    IF_NZ goto loop;

    RET;

// INCLUDE "engine/battle/move_effects/bide.asm"

    return BattleCommand_CheckRampage();
}

void BattleCommand_CheckRampage(void){
//  checkrampage

    LD_DE(wPlayerRolloutCount);
    LDH_A_addr(hBattleTurn);
    AND_A_A;
    IF_Z goto player;
    LD_DE(wEnemyRolloutCount);

player:
    LD_A(BATTLE_VARS_SUBSTATUS3);
    CALL(aGetBattleVarAddr);
    BIT_hl(SUBSTATUS_RAMPAGE);
    RET_Z ;
    LD_A_de;
    DEC_A;
    LD_de_A;
    IF_NZ goto continue_rampage;

    RES_hl(SUBSTATUS_RAMPAGE);
    CALL(aBattleCommand_SwitchTurn);
    CALL(aSafeCheckSafeguard);
    PUSH_AF;
    CALL(aBattleCommand_SwitchTurn);
    POP_AF;
    IF_NZ goto continue_rampage;

    SET_hl(SUBSTATUS_CONFUSED);
    CALL(aBattleRandom);
    AND_A(0b00000001);
    INC_A;
    INC_A;
    INC_DE;  // ConfuseCount
    LD_de_A;

continue_rampage:
    LD_B(rampage_command);
    JP(mSkipToBattleCommand);

}

void BattleCommand_Rampage(void){
//  rampage

//  No rampage during Sleep Talk.
    LD_A(BATTLE_VARS_STATUS);
    CALL(aGetBattleVar);
    AND_A(SLP);
    RET_NZ ;

    LD_DE(wPlayerRolloutCount);
    LDH_A_addr(hBattleTurn);
    AND_A_A;
    IF_Z goto ok;
    LD_DE(wEnemyRolloutCount);

ok:
    LD_A(BATTLE_VARS_SUBSTATUS3);
    CALL(aGetBattleVarAddr);
    SET_hl(SUBSTATUS_RAMPAGE);
//  Rampage for 1 or 2 more turns
    CALL(aBattleRandom);
    AND_A(0b00000001);
    INC_A;
    LD_de_A;
    LD_A(1);
    LD_addr_A(wSomeoneIsRampaging);
    RET;

// INCLUDE "engine/battle/move_effects/teleport.asm"

    return SetBattleDraw();
}

void SetBattleDraw(void){
    LD_A_addr(wBattleResult);
    AND_A(BATTLERESULT_BITMASK);
    OR_A(DRAW);
    LD_addr_A(wBattleResult);
    RET;

}

void BattleCommand_ForceSwitch(void){
//  forceswitch

    LD_A_addr(wBattleType);
    CP_A(BATTLETYPE_SHINY);
    JP_Z (mBattleCommand_ForceSwitch_fail);
    CP_A(BATTLETYPE_TRAP);
    JP_Z (mBattleCommand_ForceSwitch_fail);
    CP_A(BATTLETYPE_CELEBI);
    JP_Z (mBattleCommand_ForceSwitch_fail);
    CP_A(BATTLETYPE_SUICUNE);
    JP_Z (mBattleCommand_ForceSwitch_fail);
    LDH_A_addr(hBattleTurn);
    AND_A_A;
    JP_NZ (mBattleCommand_ForceSwitch_force_player_switch);
    LD_A_addr(wAttackMissed);
    AND_A_A;
    IF_NZ goto missed;
    LD_A_addr(wBattleMode);
    DEC_A;
    IF_NZ goto trainer;
    LD_A_addr(wCurPartyLevel);
    LD_B_A;
    LD_A_addr(wBattleMonLevel);
    CP_A_B;
    IF_NC goto wild_force_flee;
    ADD_A_B;
    LD_C_A;
    INC_C;

random_loop_wild:
    CALL(aBattleRandom);
    CP_A_C;
    IF_NC goto random_loop_wild;
    SRL_B;
    SRL_B;
    CP_A_B;
    IF_NC goto wild_force_flee;

missed:
    JP(mBattleCommand_ForceSwitch_fail);


wild_force_flee:
    CALL(aUpdateBattleMonInParty);
    XOR_A_A;
    LD_addr_A(wNumHits);
    INC_A;  // TRUE
    LD_addr_A(wForcedSwitch);
    CALL(aSetBattleDraw);
    LD_A_addr(wPlayerMoveStructAnimation);
    JP(mBattleCommand_ForceSwitch_succeed);


trainer:
    CALL(aFindAliveEnemyMons);
    IF_C goto switch_fail;
    LD_A_addr(wEnemyGoesFirst);
    AND_A_A;
    IF_Z goto switch_fail;
    CALL(aUpdateEnemyMonInParty);
    LD_A(0x1);
    LD_addr_A(wBattleAnimParam);
    CALL(aAnimateCurrentMove);
    LD_C(0x14);
    CALL(aDelayFrames);
    hlcoord(1, 0, wTilemap);
    LD_BC((4 << 8) | 10);
    CALL(aClearBox);
    LD_C(20);
    CALL(aDelayFrames);
    LD_A_addr(wOTPartyCount);
    LD_B_A;
    LD_A_addr(wCurOTMon);
    LD_C_A;
//  select a random enemy mon to switch to

random_loop_trainer:
    CALL(aBattleRandom);
    AND_A(0x7);
    CP_A_B;
    IF_NC goto random_loop_trainer;
    CP_A_C;
    IF_Z goto random_loop_trainer;
    PUSH_AF;
    PUSH_BC;
    LD_HL(wOTPartyMon1HP);
    CALL(aGetPartyLocation);
    LD_A_hli;
    OR_A_hl;
    POP_BC;
    POP_DE;
    IF_Z goto random_loop_trainer;
    LD_A_D;
    INC_A;
    LD_addr_A(wEnemySwitchMonIndex);
    CALLFAR(aForceEnemySwitch);

    LD_HL(mDraggedOutText);
    CALL(aStdBattleTextbox);

    LD_HL(mSpikesDamage);
    JP(mCallBattleCore);


switch_fail:
    JP(mBattleCommand_ForceSwitch_fail);


force_player_switch:
    LD_A_addr(wAttackMissed);
    AND_A_A;
    IF_NZ goto player_miss;

    LD_A_addr(wBattleMode);
    DEC_A;
    IF_NZ goto vs_trainer;

    LD_A_addr(wBattleMonLevel);
    LD_B_A;
    LD_A_addr(wCurPartyLevel);
    CP_A_B;
    IF_NC goto wild_succeed_playeristarget;

    ADD_A_B;
    LD_C_A;
    INC_C;

wild_random_loop_playeristarget:
    CALL(aBattleRandom);
    CP_A_C;
    IF_NC goto wild_random_loop_playeristarget;

    SRL_B;
    SRL_B;
    CP_A_B;
    IF_NC goto wild_succeed_playeristarget;


player_miss:
    goto fail;


wild_succeed_playeristarget:
    CALL(aUpdateBattleMonInParty);
    XOR_A_A;
    LD_addr_A(wNumHits);
    INC_A;  // TRUE
    LD_addr_A(wForcedSwitch);
    CALL(aSetBattleDraw);
    LD_A_addr(wEnemyMoveStructAnimation);
    goto succeed;


vs_trainer:
    CALL(aCheckPlayerHasMonToSwitchTo);
    IF_C goto fail;

    LD_A_addr(wEnemyGoesFirst);
    CP_A(0x1);
    IF_Z goto switch_fail;

    CALL(aUpdateBattleMonInParty);
    LD_A(0x1);
    LD_addr_A(wBattleAnimParam);
    CALL(aAnimateCurrentMove);
    LD_C(20);
    CALL(aDelayFrames);
    hlcoord(9, 7, wTilemap);
    LD_BC((5 << 8) | 11);
    CALL(aClearBox);
    LD_C(20);
    CALL(aDelayFrames);
    LD_A_addr(wPartyCount);
    LD_B_A;
    LD_A_addr(wCurBattleMon);
    LD_C_A;

random_loop_trainer_playeristarget:
    CALL(aBattleRandom);
    AND_A(0x7);
    CP_A_B;
    IF_NC goto random_loop_trainer_playeristarget;

    CP_A_C;
    IF_Z goto random_loop_trainer_playeristarget;

    PUSH_AF;
    PUSH_BC;
    LD_HL(wPartyMon1HP);
    CALL(aGetPartyLocation);
    LD_A_hli;
    OR_A_hl;
    POP_BC;
    POP_DE;
    IF_Z goto random_loop_trainer_playeristarget;

    LD_A_D;
    LD_addr_A(wCurPartyMon);
    LD_HL(mSwitchPlayerMon);
    CALL(aCallBattleCore);

    LD_HL(mDraggedOutText);
    CALL(aStdBattleTextbox);

    LD_HL(mSpikesDamage);
    JP(mCallBattleCore);


fail:
    CALL(aBattleCommand_LowerSub);
    CALL(aBattleCommand_MoveDelay);
    CALL(aBattleCommand_RaiseSub);
    JP(mPrintButItFailed);


succeed:
    PUSH_AF;
    CALL(aSetBattleDraw);
    LD_A(0x1);
    LD_addr_A(wBattleAnimParam);
    CALL(aAnimateCurrentMove);
    LD_C(20);
    CALL(aDelayFrames);
    POP_AF;

    LD_HL(mFledInFearText);
    CP_A(ROAR);
    IF_Z goto do_text;
    LD_HL(mBlownAwayText);

do_text:
    JP(mStdBattleTextbox);

}

void CheckPlayerHasMonToSwitchTo(void){
    LD_A_addr(wPartyCount);
    LD_D_A;
    LD_E(0);
    LD_BC(PARTYMON_STRUCT_LENGTH);

loop:
    LD_A_addr(wCurBattleMon);
    CP_A_E;
    IF_Z goto next;

    LD_A_E;
    LD_HL(wPartyMon1HP);
    CALL(aAddNTimes);
    LD_A_hli;
    OR_A_hl;
    IF_NZ goto not_fainted;


next:
    INC_E;
    DEC_D;
    IF_NZ goto loop;

    SCF;
    RET;


not_fainted:
    AND_A_A;
    RET;

}

void BattleCommand_EndLoop(void){
//  endloop

//  Loop back to 'critical'.

    LD_DE(wPlayerRolloutCount);
    LD_BC(wPlayerDamageTaken);
    LDH_A_addr(hBattleTurn);
    AND_A_A;
    IF_Z goto got_addrs;
    LD_DE(wEnemyRolloutCount);
    LD_BC(wEnemyDamageTaken);

got_addrs:

    LD_A(BATTLE_VARS_SUBSTATUS3);
    CALL(aGetBattleVarAddr);
    BIT_hl(SUBSTATUS_IN_LOOP);
    JP_NZ (mBattleCommand_EndLoop_in_loop);
    SET_hl(SUBSTATUS_IN_LOOP);
    LD_A(BATTLE_VARS_MOVE_EFFECT);
    CALL(aGetBattleVarAddr);
    LD_A_hl;
    CP_A(EFFECT_POISON_MULTI_HIT);
    IF_Z goto twineedle;
    CP_A(EFFECT_DOUBLE_HIT);
    LD_A(1);
    IF_Z goto double_hit;
    LD_A_hl;
    CP_A(EFFECT_BEAT_UP);
    IF_Z goto beat_up;
    CP_A(EFFECT_TRIPLE_KICK);
    IF_NZ goto not_triple_kick;

reject_triple_kick_sample:
    CALL(aBattleRandom);
    AND_A(0x3);
    IF_Z goto reject_triple_kick_sample;
    DEC_A;
    IF_NZ goto double_hit;
    LD_A(1);
    LD_bc_A;
    goto done_loop;


beat_up:
    LDH_A_addr(hBattleTurn);
    AND_A_A;
    IF_NZ goto check_ot_beat_up;
    LD_A_addr(wPartyCount);
    CP_A(1);
    JP_Z (mBattleCommand_EndLoop_only_one_beatup);
    DEC_A;
    goto double_hit;


check_ot_beat_up:
    LD_A_addr(wBattleMode);
    CP_A(WILD_BATTLE);
    JP_Z (mBattleCommand_EndLoop_only_one_beatup);
    LD_A_addr(wOTPartyCount);
    CP_A(1);
    JP_Z (mBattleCommand_EndLoop_only_one_beatup);
    DEC_A;
    goto double_hit;


only_one_beatup:
    LD_A(BATTLE_VARS_SUBSTATUS3);
    CALL(aGetBattleVarAddr);
    RES_hl(SUBSTATUS_IN_LOOP);
    CALL(aBattleCommand_BeatUpFailText);
    JP(mEndMoveEffect);


not_triple_kick:
    CALL(aBattleRandom);
    AND_A(0x3);
    CP_A(2);
    IF_C goto got_number_hits;
    CALL(aBattleRandom);
    AND_A(0x3);

got_number_hits:
    INC_A;

double_hit:
    LD_de_A;
    INC_A;
    LD_bc_A;
    goto loop_back_to_critical;


twineedle:
    LD_A(1);
    goto double_hit;


in_loop:
    LD_A_de;
    DEC_A;
    LD_de_A;
    IF_NZ goto loop_back_to_critical;

done_loop:
    LD_A(BATTLE_VARS_SUBSTATUS3);
    CALL(aGetBattleVarAddr);
    RES_hl(SUBSTATUS_IN_LOOP);

    LD_HL(mPlayerHitTimesText);
    LDH_A_addr(hBattleTurn);
    AND_A_A;
    IF_Z goto got_hit_n_times_text;
    LD_HL(mEnemyHitTimesText);

got_hit_n_times_text:

    PUSH_BC;
    LD_A(BATTLE_VARS_MOVE_EFFECT);
    CALL(aGetBattleVar);
    CP_A(EFFECT_BEAT_UP);
    IF_Z goto beat_up_2;
    CALL(aStdBattleTextbox);

beat_up_2:

    POP_BC;
    XOR_A_A;
    LD_bc_A;
    RET;


loop_back_to_critical:
    LD_A_addr(wBattleScriptBufferAddress + 1);
    LD_H_A;
    LD_A_addr(wBattleScriptBufferAddress);
    LD_L_A;

not_critical:
    LD_A_hld;
    CP_A(critical_command);
    IF_NZ goto not_critical;
    INC_HL;
    LD_A_H;
    LD_addr_A(wBattleScriptBufferAddress + 1);
    LD_A_L;
    LD_addr_A(wBattleScriptBufferAddress);
    RET;

}

void BattleCommand_FakeOut(void){
    LD_A_addr(wAttackMissed);
    AND_A_A;
    RET_NZ ;

    CALL(aCheckSubstituteOpp);
    IF_NZ goto fail;

    LD_A(BATTLE_VARS_STATUS_OPP);
    CALL(aGetBattleVar);
    AND_A(1 << FRZ | SLP);
    IF_NZ goto fail;

    CALL(aCheckOpponentWentFirst);
    JR_Z (mFlinchTarget);


fail:
    LD_A(1);
    LD_addr_A(wAttackMissed);
    RET;

}

void BattleCommand_FlinchTarget(void){
    CALL(aCheckSubstituteOpp);
    RET_NZ ;

    LD_A(BATTLE_VARS_STATUS_OPP);
    CALL(aGetBattleVar);
    AND_A(1 << FRZ | SLP);
    RET_NZ ;

    CALL(aCheckOpponentWentFirst);
    RET_NZ ;

    LD_A_addr(wEffectFailed);
    AND_A_A;
    RET_NZ ;

// fallthrough

    return FlinchTarget();
}

void FlinchTarget(void){
    LD_A(BATTLE_VARS_SUBSTATUS3_OPP);
    CALL(aGetBattleVarAddr);
    SET_hl(SUBSTATUS_FLINCHED);
    JP(mEndRechargeOpp);

}

void CheckOpponentWentFirst(void){
//  Returns a=0, z if user went first
//  Returns a=1, nz if opponent went first
    PUSH_BC;
    LD_A_addr(wEnemyGoesFirst);  // 0 if player went first
    LD_B_A;
    LDH_A_addr(hBattleTurn);  // 0 if it's the player's turn
    XOR_A_B;  // 1 if opponent went first
    POP_BC;
    RET;

}

void BattleCommand_HeldFlinch(void){
//  kingsrock

    LD_A_addr(wAttackMissed);
    AND_A_A;
    RET_NZ ;

    CALL(aGetUserItem);
    LD_A_B;
    CP_A(HELD_FLINCH);
    RET_NZ ;

    CALL(aCheckSubstituteOpp);
    RET_NZ ;
    LD_A(BATTLE_VARS_MOVE_EFFECT);
    CALL(aGetBattleVarAddr);
    LD_D_H;
    LD_E_L;
    CALL(aGetUserItem);
    CALL(aBattleRandom);
    CP_A_C;
    RET_NC ;
    CALL(aEndRechargeOpp);
    LD_A(BATTLE_VARS_SUBSTATUS3_OPP);
    CALL(aGetBattleVarAddr);
    SET_hl(SUBSTATUS_FLINCHED);
    RET;

}

void BattleCommand_OHKO(void){
//  ohko

    CALL(aResetDamage);
    LD_A_addr(wTypeModifier);
    AND_A(0x7f);
    IF_Z goto no_effect;
    LD_HL(wEnemyMonLevel);
    LD_DE(wBattleMonLevel);
    LD_BC(wPlayerMoveStruct + MOVE_ACC);
    LDH_A_addr(hBattleTurn);
    AND_A_A;
    IF_Z goto got_move_accuracy;
    PUSH_HL;
    LD_H_D;
    LD_L_E;
    POP_DE;
    LD_BC(wEnemyMoveStruct + MOVE_ACC);

got_move_accuracy:
    LD_A_de;
    SUB_A_hl;
    IF_C goto no_effect;
    ADD_A_A;
    LD_E_A;
    LD_A_bc;
    ADD_A_E;
    IF_NC goto finish_ohko;
    LD_A(0xff);

finish_ohko:
    LD_bc_A;
    CALL(aBattleCommand_CheckHit);
    LD_HL(wCurDamage);
    LD_A(0xff);
    LD_hli_A;
    LD_hl_A;
    LD_A(0x2);
    LD_addr_A(wCriticalHit);
    RET;


no_effect:
    LD_A(0xff);
    LD_addr_A(wCriticalHit);
    LD_A(0x1);
    LD_addr_A(wAttackMissed);
    RET;

}

void BattleCommand_CheckCharge(void){
//  checkcharge

    LD_A(BATTLE_VARS_SUBSTATUS3);
    CALL(aGetBattleVarAddr);
    BIT_hl(SUBSTATUS_CHARGED);
    RET_Z ;
    RES_hl(SUBSTATUS_CHARGED);
    RES_hl(SUBSTATUS_UNDERGROUND);
    RES_hl(SUBSTATUS_FLYING);
    LD_B(charge_command);
    JP(mSkipToBattleCommand);

}

void BattleCommand_Charge(void){
//  charge

    CALL(aBattleCommand_ClearText);
    LD_A(BATTLE_VARS_STATUS);
    CALL(aGetBattleVar);
    AND_A(SLP);
    IF_Z goto awake;

    CALL(aBattleCommand_MoveDelay);
    CALL(aBattleCommand_RaiseSub);
    CALL(aPrintButItFailed);
    JP(mEndMoveEffect);


awake:
    LD_A(BATTLE_VARS_SUBSTATUS3);
    CALL(aGetBattleVarAddr);
    SET_hl(SUBSTATUS_CHARGED);

    LD_HL(mIgnoredOrders2Text);
    LD_A_addr(wAlreadyDisobeyed);
    AND_A_A;
    CALL_NZ (aStdBattleTextbox);

    CALL(aBattleCommand_LowerSub);
    XOR_A_A;
    LD_addr_A(wNumHits);
    INC_A;
    LD_addr_A(wBattleAnimParam);
    CALL(aLoadMoveAnim);
    LD_A(BATTLE_VARS_MOVE_ANIM);
    CALL(aGetBattleVar);
    CP_A(FLY);
    IF_Z goto flying;
    CP_A(DIG);
    IF_Z goto flying;
    CALL(aBattleCommand_RaiseSub);
    goto not_flying;


flying:
    CALL(aDisappearUser);

not_flying:
    LD_A(BATTLE_VARS_SUBSTATUS3);
    CALL(aGetBattleVarAddr);
    LD_A(BATTLE_VARS_MOVE_ANIM);
    CALL(aGetBattleVar);
    LD_B_A;
    CP_A(FLY);
    IF_Z goto set_flying;
    CP_A(DIG);
    IF_NZ goto dont_set_digging;
    SET_hl(SUBSTATUS_UNDERGROUND);
    goto dont_set_digging;


set_flying:
    SET_hl(SUBSTATUS_FLYING);


dont_set_digging:
    CALL(aCheckUserIsCharging);
    IF_NZ goto mimic;
    LD_A(BATTLE_VARS_LAST_COUNTER_MOVE);
    CALL(aGetBattleVarAddr);
    LD_hl_B;
    LD_A(BATTLE_VARS_LAST_MOVE);
    CALL(aGetBattleVarAddr);
    LD_hl_B;


mimic:
    CALL(aResetDamage);

    LD_HL(mBattleCommand_Charge_UsedText);
    CALL(aBattleTextbox);

    LD_A(BATTLE_VARS_MOVE_EFFECT);
    CALL(aGetBattleVar);
    CP_A(EFFECT_SKULL_BASH);
    LD_B(endturn_command);
    JP_Z (mSkipToBattleCommand);
    JP(mEndMoveEffect);


UsedText:
    //text_far ['Text_BattleUser']  // "<USER>"
    //text_asm ['?']
    LD_A(BATTLE_VARS_MOVE_ANIM);
    CALL(aGetBattleVar);
    CP_A(RAZOR_WIND);
    LD_HL(mBattleCommand_Charge_BattleMadeWhirlwindText);
    IF_Z goto done;

    CP_A(SOLARBEAM);
    LD_HL(mBattleCommand_Charge_BattleTookSunlightText);
    IF_Z goto done;

    CP_A(SKULL_BASH);
    LD_HL(mBattleCommand_Charge_BattleLoweredHeadText);
    IF_Z goto done;

    CP_A(SKY_ATTACK);
    LD_HL(mBattleCommand_Charge_BattleGlowingText);
    IF_Z goto done;

    CP_A(FLY);
    LD_HL(mBattleCommand_Charge_BattleFlewText);
    IF_Z goto done;

    CP_A(DIG);
    LD_HL(mBattleCommand_Charge_BattleDugText);


done:
    RET;


BattleMadeWhirlwindText:
    //text_far ['_BattleMadeWhirlwindText']
    //text_end ['?']


BattleTookSunlightText:
    //text_far ['_BattleTookSunlightText']
    //text_end ['?']


BattleLoweredHeadText:
    //text_far ['_BattleLoweredHeadText']
    //text_end ['?']


BattleGlowingText:
    //text_far ['_BattleGlowingText']
    //text_end ['?']


BattleFlewText:
    //text_far ['_BattleFlewText']
    //text_end ['?']


BattleDugText:
    //text_far ['_BattleDugText']
    //text_end ['?']

    return BattleCommand_Unused3C();
}

void BattleCommand_Unused3C(void){
//  effect0x3c
    RET;

}

void BattleCommand_TrapTarget(void){
//  traptarget

    LD_A_addr(wAttackMissed);
    AND_A_A;
    RET_NZ ;
    LD_HL(wEnemyWrapCount);
    LD_DE(wEnemyTrappingMove);
    LDH_A_addr(hBattleTurn);
    AND_A_A;
    IF_Z goto got_trap;
    LD_HL(wPlayerWrapCount);
    LD_DE(wPlayerTrappingMove);


got_trap:
    LD_A_hl;
    AND_A_A;
    RET_NZ ;
    LD_A(BATTLE_VARS_SUBSTATUS4_OPP);
    CALL(aGetBattleVar);
    BIT_A(SUBSTATUS_SUBSTITUTE);
    RET_NZ ;
    CALL(aBattleRandom);
// trapped for 2-5 turns
    AND_A(0b11);
    INC_A;
    INC_A;
    INC_A;
    LD_hl_A;
    LD_A(BATTLE_VARS_MOVE_ANIM);
    CALL(aGetBattleVar);
    LD_de_A;
    LD_B_A;
    LD_HL(mBattleCommand_TrapTarget_Traps);


find_trap_text:
    LD_A_hli;
    CP_A_B;
    IF_Z goto found_trap_text;
    INC_HL;
    INC_HL;
    goto find_trap_text;


found_trap_text:
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    JP(mStdBattleTextbox);


Traps:
    //dbw ['BIND', 'UsedBindText']  // 'used BIND on'
    //dbw ['WRAP', 'WrappedByText']  // 'was WRAPPED by'
    //dbw ['FIRE_SPIN', 'FireSpinTrapText']  // 'was trapped!'
    //dbw ['CLAMP', 'ClampedByText']  // 'was CLAMPED by'
    //dbw ['WHIRLPOOL', 'WhirlpoolTrapText']  // 'was trapped!'

// INCLUDE "engine/battle/move_effects/mist.asm"

// INCLUDE "engine/battle/move_effects/focus_energy.asm"

    return BattleCommand_Recoil();
}

void BattleCommand_Recoil(void){
//  recoil

    LD_HL(wBattleMonMaxHP);
    LDH_A_addr(hBattleTurn);
    AND_A_A;
    IF_Z goto got_hp;
    LD_HL(wEnemyMonMaxHP);

got_hp:
    LD_A(BATTLE_VARS_MOVE_ANIM);
    CALL(aGetBattleVar);
    LD_D_A;
//  get 1/4 damage or 1 HP, whichever is higher
    LD_A_addr(wCurDamage);
    LD_B_A;
    LD_A_addr(wCurDamage + 1);
    LD_C_A;
    SRL_B;
    RR_C;
    SRL_B;
    RR_C;
    LD_A_B;
    OR_A_C;
    IF_NZ goto min_damage;
    INC_C;

min_damage:
    LD_A_hli;
    LD_addr_A(wHPBuffer1 + 1);
    LD_A_hl;
    LD_addr_A(wHPBuffer1);
    DEC_HL;
    DEC_HL;
    LD_A_hl;
    LD_addr_A(wHPBuffer2);
    SUB_A_C;
    LD_hld_A;
    LD_addr_A(wHPBuffer3);
    LD_A_hl;
    LD_addr_A(wHPBuffer2 + 1);
    SBC_A_B;
    LD_hl_A;
    LD_addr_A(wHPBuffer3 + 1);
    IF_NC goto dont_ko;
    XOR_A_A;
    LD_hli_A;
    LD_hl_A;
    LD_HL(wHPBuffer3);
    LD_hli_A;
    LD_hl_A;

dont_ko:
    hlcoord(10, 9, wTilemap);
    LDH_A_addr(hBattleTurn);
    AND_A_A;
    LD_A(1);
    IF_Z goto animate_hp_bar;
    hlcoord(2, 2, wTilemap);
    XOR_A_A;

animate_hp_bar:
    LD_addr_A(wWhichHPBar);
    PREDEF(pAnimateHPBar);
    CALL(aRefreshBattleHuds);
    LD_HL(mRecoilText);
    JP(mStdBattleTextbox);

}

void BattleCommand_ConfuseTarget(void){
//  confusetarget

    CALL(aGetOpponentItem);
    LD_A_B;
    CP_A(HELD_PREVENT_CONFUSE);
    RET_Z ;
    LD_A_addr(wEffectFailed);
    AND_A_A;
    RET_NZ ;
    CALL(aSafeCheckSafeguard);
    RET_NZ ;
    CALL(aCheckSubstituteOpp);
    RET_NZ ;
    LD_A(BATTLE_VARS_SUBSTATUS3_OPP);
    CALL(aGetBattleVarAddr);
    BIT_hl(SUBSTATUS_CONFUSED);
    RET_NZ ;
    JR(mBattleCommand_FinishConfusingTarget);

}

void BattleCommand_Confuse(void){
//  confuse

    CALL(aGetOpponentItem);
    LD_A_B;
    CP_A(HELD_PREVENT_CONFUSE);
    IF_NZ goto no_item_protection;
    LD_A_hl;
    LD_addr_A(wNamedObjectIndex);
    CALL(aGetItemName);
    CALL(aAnimateFailedMove);
    LD_HL(mProtectedByText);
    JP(mStdBattleTextbox);


no_item_protection:
    LD_A(BATTLE_VARS_SUBSTATUS3_OPP);
    CALL(aGetBattleVarAddr);
    BIT_hl(SUBSTATUS_CONFUSED);
    IF_Z goto not_already_confused;
    CALL(aAnimateFailedMove);
    LD_HL(mAlreadyConfusedText);
    JP(mStdBattleTextbox);


not_already_confused:
    CALL(aCheckSubstituteOpp);
    JR_NZ (mBattleCommand_Confuse_CheckSnore_Swagger_ConfuseHit);
    LD_A_addr(wAttackMissed);
    AND_A_A;
    JR_NZ (mBattleCommand_Confuse_CheckSnore_Swagger_ConfuseHit);
    return BattleCommand_FinishConfusingTarget();
}

void BattleCommand_FinishConfusingTarget(void){
    LD_BC(wEnemyConfuseCount);
    LDH_A_addr(hBattleTurn);
    AND_A_A;
    IF_Z goto got_confuse_count;
    LD_BC(wPlayerConfuseCount);


got_confuse_count:
    SET_hl(SUBSTATUS_CONFUSED);
// confused for 2-5 turns
    CALL(aBattleRandom);
    AND_A(0b11);
    INC_A;
    INC_A;
    LD_bc_A;

    LD_A(BATTLE_VARS_MOVE_EFFECT);
    CALL(aGetBattleVar);
    CP_A(EFFECT_CONFUSE_HIT);
    IF_Z goto got_effect;
    CP_A(EFFECT_SNORE);
    IF_Z goto got_effect;
    CP_A(EFFECT_SWAGGER);
    IF_Z goto got_effect;
    CALL(aAnimateCurrentMove);


got_effect:
    LD_DE(ANIM_CONFUSED);
    CALL(aPlayOpponentBattleAnim);

    LD_HL(mBecameConfusedText);
    CALL(aStdBattleTextbox);

    CALL(aGetOpponentItem);
    LD_A_B;
    CP_A(HELD_HEAL_STATUS);
    IF_Z goto heal_confusion;
    CP_A(HELD_HEAL_CONFUSION);
    RET_NZ ;

heal_confusion:
    LD_HL(mUseConfusionHealingItem);
    JP(mCallBattleCore);

}

void BattleCommand_Confuse_CheckSnore_Swagger_ConfuseHit(void){
    LD_A(BATTLE_VARS_MOVE_EFFECT);
    CALL(aGetBattleVar);
    CP_A(EFFECT_CONFUSE_HIT);
    RET_Z ;
    CP_A(EFFECT_SNORE);
    RET_Z ;
    CP_A(EFFECT_SWAGGER);
    RET_Z ;
    JP(mPrintDidntAffect2);

}

void BattleCommand_Paralyze(void){
//  paralyze

    LD_A(BATTLE_VARS_STATUS_OPP);
    CALL(aGetBattleVar);
    BIT_A(PAR);
    IF_NZ goto paralyzed;
    LD_A_addr(wTypeModifier);
    AND_A(0x7f);
    IF_Z goto didnt_affect;
    CALL(aGetOpponentItem);
    LD_A_B;
    CP_A(HELD_PREVENT_PARALYZE);
    IF_NZ goto no_item_protection;
    LD_A_hl;
    LD_addr_A(wNamedObjectIndex);
    CALL(aGetItemName);
    CALL(aAnimateFailedMove);
    LD_HL(mProtectedByText);
    JP(mStdBattleTextbox);


no_item_protection:
    LDH_A_addr(hBattleTurn);
    AND_A_A;
    IF_Z goto dont_sample_failure;

    LD_A_addr(wLinkMode);
    AND_A_A;
    IF_NZ goto dont_sample_failure;

    LD_A_addr(wInBattleTowerBattle);
    AND_A_A;
    IF_NZ goto dont_sample_failure;

    LD_A_addr(wPlayerSubStatus5);
    BIT_A(SUBSTATUS_LOCK_ON);
    IF_NZ goto dont_sample_failure;

    CALL(aBattleRandom);
    CP_A(25 percent + 1);  // 25% chance AI fails
    IF_C goto failed;


dont_sample_failure:
    LD_A(BATTLE_VARS_STATUS_OPP);
    CALL(aGetBattleVarAddr);
    AND_A_A;
    IF_NZ goto failed;
    LD_A_addr(wAttackMissed);
    AND_A_A;
    IF_NZ goto failed;
    CALL(aCheckSubstituteOpp);
    IF_NZ goto failed;
    LD_C(30);
    CALL(aDelayFrames);
    CALL(aAnimateCurrentMove);
    LD_A(0x1);
    LDH_addr_A(hBGMapMode);
    LD_A(BATTLE_VARS_STATUS_OPP);
    CALL(aGetBattleVarAddr);
    SET_hl(PAR);
    CALL(aUpdateOpponentInParty);
    LD_HL(mApplyPrzEffectOnSpeed);
    CALL(aCallBattleCore);
    CALL(aUpdateBattleHuds);
    CALL(aPrintParalyze);
    LD_HL(mUseHeldStatusHealingItem);
    JP(mCallBattleCore);


paralyzed:
    CALL(aAnimateFailedMove);
    LD_HL(mAlreadyParalyzedText);
    JP(mStdBattleTextbox);


failed:
    JP(mPrintDidntAffect2);


didnt_affect:
    CALL(aAnimateFailedMove);
    JP(mPrintDoesntAffect);

}

void CheckMoveTypeMatchesTarget(void){
//  Compare move type to opponent type.
//  Return z if matching the opponent type,
//  unless the move is Normal (Tri Attack).

    PUSH_HL;

    LD_HL(wEnemyMonType1);
    LDH_A_addr(hBattleTurn);
    AND_A_A;
    IF_Z goto ok;
    LD_HL(wBattleMonType1);

ok:

    LD_A(BATTLE_VARS_MOVE_TYPE);
    CALL(aGetBattleVar);
    CP_A(NORMAL);
    IF_Z goto normal;

    CP_A_hl;
    IF_Z goto l_return;

    INC_HL;
    CP_A_hl;


l_return:
    POP_HL;
    RET;


normal:
    LD_A(1);
    AND_A_A;
    POP_HL;
    RET;

// INCLUDE "engine/battle/move_effects/substitute.asm"

    return BattleCommand_RechargeNextTurn();
}

void BattleCommand_RechargeNextTurn(void){
//  rechargenextturn
    LD_A(BATTLE_VARS_SUBSTATUS4);
    CALL(aGetBattleVarAddr);
    SET_hl(SUBSTATUS_RECHARGE);
    RET;

}

void EndRechargeOpp(void){
    PUSH_HL;
    LD_A(BATTLE_VARS_SUBSTATUS4_OPP);
    CALL(aGetBattleVarAddr);
    RES_hl(SUBSTATUS_RECHARGE);
    POP_HL;
    RET;

// INCLUDE "engine/battle/move_effects/rage.asm"

    return BattleCommand_DoubleFlyingDamage();
}

void BattleCommand_DoubleFlyingDamage(void){
//  doubleflyingdamage
    LD_A(BATTLE_VARS_SUBSTATUS3_OPP);
    CALL(aGetBattleVar);
    BIT_A(SUBSTATUS_FLYING);
    RET_Z ;
    JR(mDoubleDamage);

}

void BattleCommand_DoubleUndergroundDamage(void){
//  doubleundergrounddamage
    LD_A(BATTLE_VARS_SUBSTATUS3_OPP);
    CALL(aGetBattleVar);
    BIT_A(SUBSTATUS_UNDERGROUND);
    RET_Z ;

// fallthrough

    return DoubleDamage();
}

void DoubleDamage(void){
    LD_HL(wCurDamage + 1);
    SLA_hl;
    DEC_HL;
    RL_hl;
    IF_NC goto quit;

    LD_A(0xff);
    LD_hli_A;
    LD_hl_A;

quit:
    RET;

// INCLUDE "engine/battle/move_effects/mimic.asm"

// INCLUDE "engine/battle/move_effects/leech_seed.asm"

// INCLUDE "engine/battle/move_effects/splash.asm"

// INCLUDE "engine/battle/move_effects/disable.asm"

// INCLUDE "engine/battle/move_effects/pay_day.asm"

// INCLUDE "engine/battle/move_effects/conversion.asm"

    return BattleCommand_ResetStats();
}

void BattleCommand_ResetStats(void){
//  resetstats

    LD_A(BASE_STAT_LEVEL);
    LD_HL(wPlayerStatLevels);
    CALL(aBattleCommand_ResetStats_Fill);
    LD_HL(wEnemyStatLevels);
    CALL(aBattleCommand_ResetStats_Fill);

    LDH_A_addr(hBattleTurn);
    PUSH_AF;

    CALL(aSetPlayerTurn);
    CALL(aCalcPlayerStats);
    CALL(aSetEnemyTurn);
    CALL(aCalcEnemyStats);

    POP_AF;
    LDH_addr_A(hBattleTurn);

    CALL(aAnimateCurrentMove);

    LD_HL(mEliminatedStatsText);
    JP(mStdBattleTextbox);


Fill:
    LD_B(NUM_LEVEL_STATS);

next:
    LD_hli_A;
    DEC_B;
    IF_NZ goto next;
    RET;

}

void BattleCommand_Heal(void){
//  heal

    LD_DE(wBattleMonHP);
    LD_HL(wBattleMonMaxHP);
    LDH_A_addr(hBattleTurn);
    AND_A_A;
    IF_Z goto got_hp;
    LD_DE(wEnemyMonHP);
    LD_HL(wEnemyMonMaxHP);

got_hp:
    LD_A(BATTLE_VARS_MOVE_ANIM);
    CALL(aGetBattleVar);
    LD_B_A;
    PUSH_HL;
    PUSH_DE;
    PUSH_BC;
    LD_C(2);
    CALL(aCompareBytes);
    POP_BC;
    POP_DE;
    POP_HL;
    JP_Z (mBattleCommand_Heal_hp_full);
    LD_A_B;
    CP_A(REST);
    IF_NZ goto not_rest;

    PUSH_HL;
    PUSH_DE;
    PUSH_AF;
    CALL(aBattleCommand_MoveDelay);
    LD_A(BATTLE_VARS_SUBSTATUS5);
    CALL(aGetBattleVarAddr);
    RES_hl(SUBSTATUS_TOXIC);
    LD_A(BATTLE_VARS_STATUS);
    CALL(aGetBattleVarAddr);
    LD_A_hl;
    AND_A_A;
    LD_hl(REST_SLEEP_TURNS + 1);
    LD_HL(mWentToSleepText);
    IF_Z goto no_status_to_heal;
    LD_HL(mRestedText);

no_status_to_heal:
    CALL(aStdBattleTextbox);
    LDH_A_addr(hBattleTurn);
    AND_A_A;
    IF_NZ goto calc_enemy_stats;
    CALL(aCalcPlayerStats);
    goto got_stats;


calc_enemy_stats:
    CALL(aCalcEnemyStats);

got_stats:
    POP_AF;
    POP_DE;
    POP_HL;


not_rest:
    IF_Z goto restore_full_hp;
    LD_HL(mGetHalfMaxHP);
    CALL(aCallBattleCore);
    goto finish;


restore_full_hp:
    LD_HL(mGetMaxHP);
    CALL(aCallBattleCore);

finish:
    CALL(aAnimateCurrentMove);
    CALL(aBattleCommand_SwitchTurn);
    LD_HL(mRestoreHP);
    CALL(aCallBattleCore);
    CALL(aBattleCommand_SwitchTurn);
    CALL(aUpdateUserInParty);
    CALL(aRefreshBattleHuds);
    LD_HL(mRegainedHealthText);
    JP(mStdBattleTextbox);


hp_full:
    CALL(aAnimateFailedMove);
    LD_HL(mHPIsFullText);
    JP(mStdBattleTextbox);

// INCLUDE "engine/battle/move_effects/transform.asm"

    return BattleEffect_ButItFailed();
}

void BattleEffect_ButItFailed(void){
    CALL(aAnimateFailedMove);
    JP(mPrintButItFailed);

}

void ClearLastMove(void){
    LD_A(BATTLE_VARS_LAST_COUNTER_MOVE);
    CALL(aGetBattleVarAddr);
    XOR_A_A;
    LD_hl_A;

    LD_A(BATTLE_VARS_LAST_MOVE);
    CALL(aGetBattleVarAddr);
    XOR_A_A;
    LD_hl_A;
    RET;

}

void ResetActorDisable(void){
    LDH_A_addr(hBattleTurn);
    AND_A_A;
    IF_Z goto player;

    XOR_A_A;
    LD_addr_A(wEnemyDisableCount);
    LD_addr_A(wEnemyDisabledMove);
    RET;


player:
    XOR_A_A;
    LD_addr_A(wPlayerDisableCount);
    LD_addr_A(wDisabledMove);
    RET;

}

void BattleCommand_Screen(void){
//  screen

    LD_HL(wPlayerScreens);
    LD_BC(wPlayerLightScreenCount);
    LDH_A_addr(hBattleTurn);
    AND_A_A;
    IF_Z goto got_screens_pointer;
    LD_HL(wEnemyScreens);
    LD_BC(wEnemyLightScreenCount);


got_screens_pointer:
    LD_A(BATTLE_VARS_MOVE_EFFECT);
    CALL(aGetBattleVar);
    CP_A(EFFECT_LIGHT_SCREEN);
    IF_NZ goto Reflect;

    BIT_hl(SCREENS_LIGHT_SCREEN);
    IF_NZ goto failed;
    SET_hl(SCREENS_LIGHT_SCREEN);
    LD_A(5);
    LD_bc_A;
    LD_HL(mLightScreenEffectText);
    goto good;


Reflect:
    BIT_hl(SCREENS_REFLECT);
    IF_NZ goto failed;
    SET_hl(SCREENS_REFLECT);

// LightScreenCount -> ReflectCount
    INC_BC;

    LD_A(5);
    LD_bc_A;
    LD_HL(mReflectEffectText);


good:
    CALL(aAnimateCurrentMove);
    JP(mStdBattleTextbox);


failed:
    CALL(aAnimateFailedMove);
    JP(mPrintButItFailed);

}

void PrintDoesntAffect(void){
//  'it doesn't affect'
    LD_HL(mDoesntAffectText);
    JP(mStdBattleTextbox);

}

void PrintNothingHappened(void){
//  'but nothing happened!'
    LD_HL(mNothingHappenedText);
    JP(mStdBattleTextbox);

}

void TryPrintButItFailed(void){
    LD_A_addr(wAlreadyFailed);
    AND_A_A;
    RET_NZ ;

// fallthrough

    return PrintButItFailed();
}

void PrintButItFailed(void){
//  'but it failed!'
    LD_HL(mButItFailedText);
    JP(mStdBattleTextbox);

}

void FailMove(void){
    CALL(aAnimateFailedMove);
// fallthrough

    return FailMimic();
}

void FailMimic(void){
    LD_HL(mButItFailedText);  // 'but it failed!'
    LD_DE(mItFailedText);  // 'it failed!'
    JP(mFailText_CheckOpponentProtect);

}

void PrintDidntAffect(void){
//  'it didn't affect'
    LD_HL(mDidntAffect1Text);
    JP(mStdBattleTextbox);

}

void PrintDidntAffect2(void){
    CALL(aAnimateFailedMove);
    LD_HL(mDidntAffect1Text);  // 'it didn't affect'
    LD_DE(mDidntAffect2Text);  // 'it didn't affect'
    JP(mFailText_CheckOpponentProtect);

}

void PrintParalyze(void){
//  'paralyzed! maybe it can't attack!'
    LD_HL(mParalyzedText);
    JP(mStdBattleTextbox);

}

void CheckSubstituteOpp(void){
    LD_A(BATTLE_VARS_SUBSTATUS4_OPP);
    CALL(aGetBattleVar);
    BIT_A(SUBSTATUS_SUBSTITUTE);
    RET;

// INCLUDE "engine/battle/move_effects/selfdestruct.asm"

// INCLUDE "engine/battle/move_effects/mirror_move.asm"

// INCLUDE "engine/battle/move_effects/metronome.asm"

    return CheckUserMove();
}

void CheckUserMove(void){
//  Return z if the user has move a.
    LD_B_A;
    LD_DE(wBattleMonMoves);
    LDH_A_addr(hBattleTurn);
    AND_A_A;
    IF_Z goto ok;
    LD_DE(wEnemyMonMoves);

ok:

    LD_C(NUM_MOVES);

loop:
    LD_A_de;
    INC_DE;
    CP_A_B;
    RET_Z ;

    DEC_C;
    IF_NZ goto loop;

    LD_A(1);
    AND_A_A;
    RET;

}

void ResetTurn(void){
    LD_HL(wPlayerCharging);
    LDH_A_addr(hBattleTurn);
    AND_A_A;
    IF_Z goto player;
    LD_HL(wEnemyCharging);


player:
    LD_hl(1);
    XOR_A_A;
    LD_addr_A(wAlreadyDisobeyed);
    CALL(aDoMove);
    JP(mEndMoveEffect);

// INCLUDE "engine/battle/move_effects/thief.asm"

    return BattleCommand_ArenaTrap();
}

void BattleCommand_ArenaTrap(void){
//  arenatrap

//  Doesn't work on an absent opponent.

    CALL(aCheckHiddenOpponent);
    IF_NZ goto failed;

//  Don't trap if the opponent is already trapped.

    LD_A(BATTLE_VARS_SUBSTATUS5);
    CALL(aGetBattleVarAddr);
    BIT_hl(SUBSTATUS_CANT_RUN);
    IF_NZ goto failed;

//  Otherwise trap the opponent.

    SET_hl(SUBSTATUS_CANT_RUN);
    CALL(aAnimateCurrentMove);
    LD_HL(mCantEscapeNowText);
    JP(mStdBattleTextbox);


failed:
    CALL(aAnimateFailedMove);
    JP(mPrintButItFailed);

// INCLUDE "engine/battle/move_effects/nightmare.asm"

    return BattleCommand_Defrost();
}

void BattleCommand_Defrost(void){
//  defrost

//  Thaw the user.

    LD_A(BATTLE_VARS_STATUS);
    CALL(aGetBattleVarAddr);
    BIT_hl(FRZ);
    RET_Z ;
    RES_hl(FRZ);

//  Don't update the enemy's party struct in a wild battle.

    LDH_A_addr(hBattleTurn);
    AND_A_A;
    IF_Z goto party;

    LD_A_addr(wBattleMode);
    DEC_A;
    IF_Z goto done;


party:
    LD_A(MON_STATUS);
    CALL(aUserPartyAttr);
    RES_hl(FRZ);


done:
    CALL(aRefreshBattleHuds);
    LD_HL(mWasDefrostedText);
    JP(mStdBattleTextbox);

// INCLUDE "engine/battle/move_effects/curse.asm"

// INCLUDE "engine/battle/move_effects/protect.asm"

// INCLUDE "engine/battle/move_effects/endure.asm"

// INCLUDE "engine/battle/move_effects/spikes.asm"

// INCLUDE "engine/battle/move_effects/foresight.asm"

// INCLUDE "engine/battle/move_effects/perish_song.asm"

// INCLUDE "engine/battle/move_effects/sandstorm.asm"

// INCLUDE "engine/battle/move_effects/rollout.asm"

    return BattleCommand_Unused5D();
}

void BattleCommand_Unused5D(void){
//  effect0x5d
    RET;

// INCLUDE "engine/battle/move_effects/fury_cutter.asm"

// INCLUDE "engine/battle/move_effects/attract.asm"

// INCLUDE "engine/battle/move_effects/return.asm"

// INCLUDE "engine/battle/move_effects/present.asm"

// INCLUDE "engine/battle/move_effects/frustration.asm"

// INCLUDE "engine/battle/move_effects/safeguard.asm"

    return SafeCheckSafeguard();
}

void SafeCheckSafeguard(void){
    PUSH_HL;
    LD_HL(wEnemyScreens);
    LDH_A_addr(hBattleTurn);
    AND_A_A;
    IF_Z goto got_turn;
    LD_HL(wPlayerScreens);


got_turn:
    BIT_hl(SCREENS_SAFEGUARD);
    POP_HL;
    RET;

}

void BattleCommand_CheckSafeguard(void){
//  checksafeguard
    LD_HL(wEnemyScreens);
    LDH_A_addr(hBattleTurn);
    AND_A_A;
    IF_Z goto got_turn;
    LD_HL(wPlayerScreens);

got_turn:
    BIT_hl(SCREENS_SAFEGUARD);
    RET_Z ;
    LD_A(1);
    LD_addr_A(wAttackMissed);
    CALL(aBattleCommand_MoveDelay);
    LD_HL(mSafeguardProtectText);
    CALL(aStdBattleTextbox);
    JP(mEndMoveEffect);

// INCLUDE "engine/battle/move_effects/magnitude.asm"

// INCLUDE "engine/battle/move_effects/baton_pass.asm"

// INCLUDE "engine/battle/move_effects/pursuit.asm"

// INCLUDE "engine/battle/move_effects/rapid_spin.asm"

    return BattleCommand_HealMorn();
}

void BattleCommand_HealMorn(void){
//  healmorn
    LD_B(MORN_F);
    JR(mBattleCommand_TimeBasedHealContinue);

}

void BattleCommand_HealDay(void){
//  healday
    LD_B(DAY_F);
    JR(mBattleCommand_TimeBasedHealContinue);

}

void BattleCommand_HealNite(void){
//  healnite
    LD_B(NITE_F);
// fallthrough

    return BattleCommand_TimeBasedHealContinue();
}

void BattleCommand_TimeBasedHealContinue(void){
//  Time- and weather-sensitive heal.

    LD_HL(wBattleMonMaxHP);
    LD_DE(wBattleMonHP);
    LDH_A_addr(hBattleTurn);
    AND_A_A;
    IF_Z goto start;
    LD_HL(wEnemyMonMaxHP);
    LD_DE(wEnemyMonHP);


start:
//  Index for .Multipliers
//  Default restores half max HP.
    LD_C(2);

//  Don't bother healing if HP is already full.
    PUSH_BC;
    CALL(aCompareBytes);
    POP_BC;
    IF_Z goto Full;

//  Don't factor in time of day in link battles.
    LD_A_addr(wLinkMode);
    AND_A_A;
    IF_NZ goto Weather;

    LD_A_addr(wTimeOfDay);
    CP_A_B;
    IF_Z goto Weather;
    DEC_C;  // double


Weather:
    LD_A_addr(wBattleWeather);
    AND_A_A;
    IF_Z goto Heal;

//  x2 in sun
//  /2 in rain/sandstorm
    INC_C;
    CP_A(WEATHER_SUN);
    IF_Z goto Heal;
    DEC_C;
    DEC_C;


Heal:
    LD_B(0);
    LD_HL(mBattleCommand_TimeBasedHealContinue_Multipliers);
    ADD_HL_BC;
    ADD_HL_BC;

    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    LD_A(BANK(aGetMaxHP));
    RST(aFarCall);

    CALL(aAnimateCurrentMove);
    CALL(aBattleCommand_SwitchTurn);

    CALLFAR(aRestoreHP);

    CALL(aBattleCommand_SwitchTurn);
    CALL(aUpdateUserInParty);

//  'regained health!'
    LD_HL(mRegainedHealthText);
    JP(mStdBattleTextbox);


Full:
    CALL(aAnimateFailedMove);

//  'hp is full!'
    LD_HL(mHPIsFullText);
    JP(mStdBattleTextbox);


Multipliers:
    //dw ['GetEighthMaxHP'];
    //dw ['GetQuarterMaxHP'];
    //dw ['GetHalfMaxHP'];
    //dw ['GetMaxHP'];

// INCLUDE "engine/battle/move_effects/hidden_power.asm"

// INCLUDE "engine/battle/move_effects/rain_dance.asm"

// INCLUDE "engine/battle/move_effects/sunny_day.asm"

// INCLUDE "engine/battle/move_effects/belly_drum.asm"

// INCLUDE "engine/battle/move_effects/psych_up.asm"

// INCLUDE "engine/battle/move_effects/mirror_coat.asm"

    return BattleCommand_DoubleMinimizeDamage();
}

void BattleCommand_DoubleMinimizeDamage(void){
//  doubleminimizedamage

    LD_HL(wEnemyMinimized);
    LDH_A_addr(hBattleTurn);
    AND_A_A;
    IF_Z goto ok;
    LD_HL(wPlayerMinimized);

ok:
    LD_A_hl;
    AND_A_A;
    RET_Z ;
    LD_HL(wCurDamage + 1);
    SLA_hl;
    DEC_HL;
    RL_hl;
    RET_NC ;
    LD_A(0xff);
    LD_hli_A;
    LD_hl_A;
    RET;

}

void BattleCommand_SkipSunCharge(void){
//  mimicsuncharge
    LD_A_addr(wBattleWeather);
    CP_A(WEATHER_SUN);
    RET_NZ ;
    LD_B(charge_command);
    JP(mSkipToBattleCommand);

// INCLUDE "engine/battle/move_effects/future_sight.asm"

// INCLUDE "engine/battle/move_effects/thunder.asm"

    return CheckHiddenOpponent();
}

void CheckHiddenOpponent(void){
//  BUG: This routine is completely redundant and introduces a bug, since BattleCommand_CheckHit does these checks properly.
    LD_A(BATTLE_VARS_SUBSTATUS3_OPP);
    CALL(aGetBattleVar);
    AND_A(1 << SUBSTATUS_FLYING | 1 << SUBSTATUS_UNDERGROUND);
    RET;

}

void GetUserItem(void){
//  Return the effect of the user's item in bc, and its id at hl.
    LD_HL(wBattleMonItem);
    LDH_A_addr(hBattleTurn);
    AND_A_A;
    IF_Z goto go;
    LD_HL(wEnemyMonItem);

go:
    LD_B_hl;
    JP(mGetItemHeldEffect);

}

void GetOpponentItem(void){
//  Return the effect of the opponent's item in bc, and its id at hl.
    LD_HL(wEnemyMonItem);
    LDH_A_addr(hBattleTurn);
    AND_A_A;
    IF_Z goto go;
    LD_HL(wBattleMonItem);

go:
    LD_B_hl;
    JP(mGetItemHeldEffect);

}

void GetItemHeldEffect(void){
//  Return the effect of item b in bc.
    LD_A_B;
    AND_A_A;
    RET_Z ;

    PUSH_HL;
    LD_HL(mItemAttributes + ITEMATTR_EFFECT);
    DEC_A;
    LD_C_A;
    LD_B(0);
    LD_A(ITEMATTR_STRUCT_LENGTH);
    CALL(aAddNTimes);
    LD_A(BANK(aItemAttributes));
    CALL(aGetFarWord);
    LD_B_L;
    LD_C_H;
    POP_HL;
    RET;

}

void AnimateCurrentMoveEitherSide(void){
    PUSH_HL;
    PUSH_DE;
    PUSH_BC;
    LD_A_addr(wBattleAnimParam);
    PUSH_AF;
    CALL(aBattleCommand_LowerSub);
    POP_AF;
    LD_addr_A(wBattleAnimParam);
    CALL(aPlayDamageAnim);
    CALL(aBattleCommand_RaiseSub);
    POP_BC;
    POP_DE;
    POP_HL;
    RET;

}

void AnimateCurrentMove(void){
    PUSH_HL;
    PUSH_DE;
    PUSH_BC;
    LD_A_addr(wBattleAnimParam);
    PUSH_AF;
    CALL(aBattleCommand_LowerSub);
    POP_AF;
    LD_addr_A(wBattleAnimParam);
    CALL(aLoadMoveAnim);
    CALL(aBattleCommand_RaiseSub);
    POP_BC;
    POP_DE;
    POP_HL;
    RET;

}

void PlayDamageAnim(void){
    XOR_A_A;
    LD_addr_A(wFXAnimID + 1);

    LD_A(BATTLE_VARS_MOVE_ANIM);
    CALL(aGetBattleVar);
    AND_A_A;
    RET_Z ;

    LD_addr_A(wFXAnimID);

    LDH_A_addr(hBattleTurn);
    AND_A_A;
    LD_A(BATTLEANIM_ENEMY_DAMAGE);
    IF_Z goto player;
    LD_A(BATTLEANIM_PLAYER_DAMAGE);


player:
    LD_addr_A(wNumHits);

    JP(mPlayUserBattleAnim);

}

void LoadMoveAnim(void){
    XOR_A_A;
    LD_addr_A(wNumHits);
    LD_addr_A(wFXAnimID + 1);

    LD_A(BATTLE_VARS_MOVE_ANIM);
    CALL(aGetBattleVar);
    AND_A_A;
    RET_Z ;

// fallthrough

    return LoadAnim();
}

void LoadAnim(void){
    LD_addr_A(wFXAnimID);

// fallthrough

    return PlayUserBattleAnim();
}

void PlayUserBattleAnim(void){
    PUSH_HL;
    PUSH_DE;
    PUSH_BC;
    CALLFAR(aPlayBattleAnim);
    POP_BC;
    POP_DE;
    POP_HL;
    RET;

}

void PlayOpponentBattleAnim(void){
    LD_A_E;
    LD_addr_A(wFXAnimID);
    LD_A_D;
    LD_addr_A(wFXAnimID + 1);
    XOR_A_A;
    LD_addr_A(wNumHits);

    PUSH_HL;
    PUSH_DE;
    PUSH_BC;
    CALL(aBattleCommand_SwitchTurn);

    CALLFAR(aPlayBattleAnim);

    CALL(aBattleCommand_SwitchTurn);
    POP_BC;
    POP_DE;
    POP_HL;
    RET;

}

void CallBattleCore(void){
    LD_A(BANK(aDoBattle)); // AKA BANK("Battle Core")
    RST(aFarCall);
    RET;

}

void AnimateFailedMove(void){
    CALL(aBattleCommand_LowerSub);
    CALL(aBattleCommand_MoveDelay);
    JP(mBattleCommand_RaiseSub);

}

void BattleCommand_MoveDelay(void){
//  movedelay
//  Wait 40 frames.
    LD_C(40);
    JP(mDelayFrames);

}

void BattleCommand_ClearText(void){
//  cleartext

//  Used in multi-hit moves.
    LD_HL(mBattleCommand_ClearText_text);
    JP(mBattleTextbox);


text:
    //text_end ['?']

    return SkipToBattleCommand();
}

void SkipToBattleCommand(void){
//  Skip over commands until reaching command b.
    LD_A_addr(wBattleScriptBufferAddress + 1);
    LD_H_A;
    LD_A_addr(wBattleScriptBufferAddress);
    LD_L_A;

loop:
    LD_A_hli;
    CP_A_B;
    IF_NZ goto loop;

    LD_A_H;
    LD_addr_A(wBattleScriptBufferAddress + 1);
    LD_A_L;
    LD_addr_A(wBattleScriptBufferAddress);
    RET;

}

void GetMoveAttr(void){
//  Assuming hl = Moves + x, return attribute x of move a.
    PUSH_BC;
    LD_BC(MOVE_LENGTH);
    CALL(aAddNTimes);
    CALL(aGetMoveByte);
    POP_BC;
    RET;

}

void GetMoveData(void){
//  Copy move struct a to de.
    LD_HL(mMoves);
    LD_BC(MOVE_LENGTH);
    CALL(aAddNTimes);
    LD_A(BANK(aMoves));
    JP(mFarCopyBytes);

}

void GetMoveByte(void){
    LD_A(BANK(aMoves));
    JP(mGetFarByte);

}

void DisappearUser(void){
    FARCALL(av_DisappearUser);
    RET;

}

void AppearUserLowerSub(void){
    FARCALL(av_AppearUserLowerSub);
    RET;

}

void AppearUserRaiseSub(void){
    FARCALL(av_AppearUserRaiseSub);
    RET;

}

void v_CheckBattleScene(void){
//  Checks the options.  Returns carry if battle animations are disabled.
    // PUSH_HL;
    // PUSH_DE;
    // PUSH_BC;
    // FARCALL(aCheckBattleScene);
    // POP_BC;
    // POP_DE;
    // POP_HL;
    REG_F_C = CheckBattleScene_Conv()? 0: 1;
    RET;

}
