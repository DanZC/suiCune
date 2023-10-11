#include "../../constants.h"
#include "core.h"
#include "../../home/array.h"
#include "../../data/trainers/leaders.h"
#include "../pokemon/experience.h"
#include "../gfx/pic_animation.h"

//  Core components of the battle engine.

void DoBattle(void){
    PEEK("");
    // XOR_A_A;
    // LD_addr_A(wBattleParticipantsNotFainted);
    wram->wBattleParticipantsNotFainted = 0;
    // LD_addr_A(wBattleParticipantsIncludingFainted);
    wram->wBattleParticipantsIncludingFainted = 0;
    // LD_addr_A(wBattlePlayerAction);
    wram->wBattlePlayerAction = 0;
    // LD_addr_A(wBattleEnded);
    wram->wBattleEnded = FALSE;
    // INC_A;
    // LD_addr_A(wBattleHasJustStarted);
    wram->wBattleHasJustStarted = TRUE;
    LD_HL(wOTPartyMon1HP);
    LD_BC(PARTYMON_STRUCT_LENGTH - 1);
    LD_D(BATTLEACTION_SWITCH1 - 1);

loop:
    INC_D;
    LD_A_hli;
    OR_A_hl;
    IF_NZ goto alive;
    ADD_HL_BC;
    goto loop;


alive:
    LD_A_D;
    LD_addr_A(wBattleAction);
    LD_A_addr(wLinkMode);
    AND_A_A;
    IF_Z goto not_linked;

    LDH_A_addr(hSerialConnectionStatus);
    CP_A(USING_INTERNAL_CLOCK);
    IF_Z goto player_2;


not_linked:
    LD_A_addr(wBattleMode);
    printf("wBattleMode = %s\n", (wram->wBattleMode == TRAINER_BATTLE)? "trainer": "wild");
    DEC_A;
    IF_Z goto wild;
    XOR_A_A;
    LD_addr_A(wEnemySwitchMonIndex);
    // CALL(aNewEnemyMonStatus);
    NewEnemyMonStatus_Conv();
    // CALL(aResetEnemyStatLevels);
    ResetEnemyStatLevels_Conv();
    // CALL(aBreakAttraction);
    BreakAttraction();
    CALL(aEnemySwitch);


wild:
    LD_C(40);
    CALL(aDelayFrames);


player_2:
    CALL(aLoadTilemapToTempTilemap);
    CALL(aCheckPlayerPartyForFitMon);
    LD_A_D;
    AND_A_A;
    JP_Z (mLostBattle);
    CALL(aSafeLoadTempTilemapToTilemap);
    LD_A_addr(wBattleType);
    CP_A(BATTLETYPE_DEBUG);
    JP_Z (mDoBattle_tutorial_debug);
    CP_A(BATTLETYPE_TUTORIAL);
    JP_Z (mDoBattle_tutorial_debug);
    XOR_A_A;
    LD_addr_A(wCurPartyMon);

loop2:
    CALL(aCheckIfCurPartyMonIsFitToFight);
    IF_NZ goto alive2;
    LD_HL(wCurPartyMon);
    INC_hl;
    goto loop2;


alive2:
    LD_A_addr(wCurBattleMon);
    LD_addr_A(wLastPlayerMon);
    LD_A_addr(wCurPartyMon);
    LD_addr_A(wCurBattleMon);
    INC_A;
    LD_HL(wPartySpecies - 1);
    LD_C_A;
    LD_B(0);
    ADD_HL_BC;
    LD_A_hl;
    LD_addr_A(wCurPartySpecies);
    LD_addr_A(wTempBattleMonSpecies);
    hlcoord(1, 5, wTilemap);
    LD_A(9);
    CALL(aSlideBattlePicOut);
    CALL(aLoadTilemapToTempTilemap);
    CALL(aResetBattleParticipants);
    CALL(aInitBattleMon);
    CALL(aResetPlayerStatLevels);
    CALL(aSendOutMonText);
    CALL(aNewBattleMonStatus);
    CALL(aBreakAttraction);
    CALL(aSendOutPlayerMon);
    CALL(aEmptyBattleTextbox);
    CALL(aLoadTilemapToTempTilemap);
    CALL(aSetPlayerTurn);
    CALL(aSpikesDamage);
    LD_A_addr(wLinkMode);
    AND_A_A;
    IF_Z goto not_linked_2;
    LDH_A_addr(hSerialConnectionStatus);
    CP_A(USING_INTERNAL_CLOCK);
    IF_NZ goto not_linked_2;
    XOR_A_A;
    LD_addr_A(wEnemySwitchMonIndex);
    CALL(aNewEnemyMonStatus);
    CALL(aResetEnemyStatLevels);
    CALL(aBreakAttraction);
    CALL(aEnemySwitch);
    CALL(aSetEnemyTurn);
    CALL(aSpikesDamage);


not_linked_2:
    JP(mBattleTurn);


tutorial_debug:
    JP(mBattleMenu);

}

void WildFled_EnemyFled_LinkBattleCanceled(void){
    CALL(aSafeLoadTempTilemapToTilemap);
    LD_A_addr(wBattleResult);
    AND_A(BATTLERESULT_BITMASK);
    ADD_A(DRAW);
    LD_addr_A(wBattleResult);
    LD_A_addr(wLinkMode);
    AND_A_A;
    LD_HL(mBattleText_WildFled);
    IF_Z goto print_text;

    LD_A_addr(wBattleResult);
    AND_A(BATTLERESULT_BITMASK);
    LD_addr_A(wBattleResult);  // WIN
    LD_HL(mBattleText_EnemyFled);
    CALL(aCheckMobileBattleError);
    IF_NC goto print_text;

    LD_HL(wcd2a);
    BIT_hl(4);
    IF_NZ goto skip_text;

    LD_HL(mBattleText_LinkErrorBattleCanceled);


print_text:
    CALL(aStdBattleTextbox);


skip_text:
    CALL(aStopDangerSound);
    CALL(aCheckMobileBattleError);
    IF_C goto skip_sfx;

    LD_DE(SFX_RUN);
    CALL(aPlaySFX);


skip_sfx:
    CALL(aSetPlayerTurn);
    LD_A(1);
    LD_addr_A(wBattleEnded);
    RET;

}

void BattleTurn(void){

loop:
    CALL(aStubbed_Increments5_a89a);
    CALL(aCheckContestBattleOver);
    JP_C (mBattleTurn_quit);

    XOR_A_A;
    LD_addr_A(wPlayerIsSwitching);
    LD_addr_A(wEnemyIsSwitching);
    LD_addr_A(wBattleHasJustStarted);
    LD_addr_A(wPlayerJustGotFrozen);
    LD_addr_A(wEnemyJustGotFrozen);
    LD_addr_A(wCurDamage);
    LD_addr_A(wCurDamage + 1);

    CALL(aHandleBerserkGene);
    CALL(aUpdateBattleMonInParty);
    FARCALL(aAIChooseMove);

    CALL(aIsMobileBattle);
    IF_NZ goto not_disconnected;
    FARCALL(aFunction100da5);
    FARCALL(aStartMobileInactivityTimer);
    FARCALL(aFunction100dd8);
    JP_C (mBattleTurn_quit);

not_disconnected:

    CALL(aCheckPlayerLockedIn);
    IF_C goto skip_iteration;

loop1:
    CALL(aBattleMenu);
    IF_C goto quit;
    LD_A_addr(wBattleEnded);
    AND_A_A;
    IF_NZ goto quit;
    LD_A_addr(wForcedSwitch);  // roared/whirlwinded/teleported
    AND_A_A;
    IF_NZ goto quit;

skip_iteration:
    CALL(aParsePlayerAction);
    IF_NZ goto loop1;

    CALL(aEnemyTriesToFlee);
    IF_C goto quit;

    CALL(aDetermineMoveOrder);
    IF_C goto _false;
    CALL(aBattle_EnemyFirst);
    goto proceed;

_false:
    CALL(aBattle_PlayerFirst);

proceed:
    CALL(aCheckMobileBattleError);
    IF_C goto quit;

    LD_A_addr(wForcedSwitch);
    AND_A_A;
    IF_NZ goto quit;

    LD_A_addr(wBattleEnded);
    AND_A_A;
    IF_NZ goto quit;

    CALL(aHandleBetweenTurnEffects);
    LD_A_addr(wBattleEnded);
    AND_A_A;
    IF_NZ goto quit;
    JP(mBattleTurn_loop);


quit:
    RET;

}

void Stubbed_Increments5_a89a(void){
    RET;
    LD_A(MBANK(as5_a89a));  // MBC30 bank used by JP Crystal// inaccessible by MBC3
    CALL(aOpenSRAM);
    LD_HL(s5_a89a + 1);  // address of MBC30 bank
    INC_hl;
    IF_NZ goto finish;
    DEC_HL;
    INC_hl;
    IF_NZ goto finish;
    DEC_hl;
    INC_HL;
    DEC_hl;


finish:
    CALL(aCloseSRAM);
    RET;

}

void HandleBetweenTurnEffects(void){
    LDH_A_addr(hSerialConnectionStatus);
    CP_A(USING_EXTERNAL_CLOCK);
    IF_Z goto CheckEnemyFirst;
    CALL(aCheckFaint_PlayerThenEnemy);
    RET_C ;
    CALL(aHandleFutureSight);
    CALL(aCheckFaint_PlayerThenEnemy);
    RET_C ;
    CALL(aHandleWeather);
    CALL(aCheckFaint_PlayerThenEnemy);
    RET_C ;
    CALL(aHandleWrap);
    CALL(aCheckFaint_PlayerThenEnemy);
    RET_C ;
    CALL(aHandlePerishSong);
    CALL(aCheckFaint_PlayerThenEnemy);
    RET_C ;
    goto NoMoreFaintingConditions;


CheckEnemyFirst:
    CALL(aCheckFaint_EnemyThenPlayer);
    RET_C ;
    CALL(aHandleFutureSight);
    CALL(aCheckFaint_EnemyThenPlayer);
    RET_C ;
    CALL(aHandleWeather);
    CALL(aCheckFaint_EnemyThenPlayer);
    RET_C ;
    CALL(aHandleWrap);
    CALL(aCheckFaint_EnemyThenPlayer);
    RET_C ;
    CALL(aHandlePerishSong);
    CALL(aCheckFaint_EnemyThenPlayer);
    RET_C ;


NoMoreFaintingConditions:
    CALL(aHandleLeftovers);
    CALL(aHandleMysteryberry);
    CALL(aHandleDefrost);
    CALL(aHandleSafeguard);
    CALL(aHandleScreens);
    CALL(aHandleStatBoostingHeldItems);
    CALL(aHandleHealingItems);
    CALL(aUpdateBattleMonInParty);
    CALL(aLoadTilemapToTempTilemap);
    JP(mHandleEncore);

}

void CheckFaint_PlayerThenEnemy(void){
    CALL(aHasPlayerFainted);
    IF_NZ goto PlayerNotFainted;
    CALL(aHandlePlayerMonFaint);
    LD_A_addr(wBattleEnded);
    AND_A_A;
    IF_NZ goto BattleIsOver;


PlayerNotFainted:
    CALL(aHasEnemyFainted);
    IF_NZ goto BattleContinues;
    CALL(aHandleEnemyMonFaint);
    LD_A_addr(wBattleEnded);
    AND_A_A;
    IF_NZ goto BattleIsOver;


BattleContinues:
    AND_A_A;
    RET;


BattleIsOver:
    SCF;
    RET;

}

void CheckFaint_EnemyThenPlayer(void){
    CALL(aHasEnemyFainted);
    IF_NZ goto EnemyNotFainted;
    CALL(aHandleEnemyMonFaint);
    LD_A_addr(wBattleEnded);
    AND_A_A;
    IF_NZ goto BattleIsOver;


EnemyNotFainted:
    CALL(aHasPlayerFainted);
    IF_NZ goto BattleContinues;
    CALL(aHandlePlayerMonFaint);
    LD_A_addr(wBattleEnded);
    AND_A_A;
    IF_NZ goto BattleIsOver;


BattleContinues:
    AND_A_A;
    RET;


BattleIsOver:
    SCF;
    RET;

}

void HandleBerserkGene(void){
    LDH_A_addr(hSerialConnectionStatus);
    CP_A(USING_EXTERNAL_CLOCK);
    IF_Z goto reverse;

    CALL(aHandleBerserkGene_player);
    goto enemy;


reverse:
    CALL(aHandleBerserkGene_enemy);
// fallthrough


player:
    CALL(aSetPlayerTurn);
    LD_DE(wPartyMon1Item);
    LD_A_addr(wCurBattleMon);
    LD_B_A;
    goto go;


enemy:
    CALL(aSetEnemyTurn);
    LD_DE(wOTPartyMon1Item);
    LD_A_addr(wCurOTMon);
    LD_B_A;
// fallthrough


go:
    PUSH_DE;
    PUSH_BC;
    CALLFAR(aGetUserItem);
    LD_A_hl;
    LD_addr_A(wNamedObjectIndex);
    SUB_A(BERSERK_GENE);
    POP_BC;
    POP_DE;
    RET_NZ ;

    LD_hl_A;

    LD_H_D;
    LD_L_E;
    LD_A_B;
    CALL(aGetPartyLocation);
    XOR_A_A;
    LD_hl_A;
    LD_A(BATTLE_VARS_SUBSTATUS3);
    CALL(aGetBattleVarAddr);
    PUSH_AF;
    SET_hl(SUBSTATUS_CONFUSED);
    LD_A(BATTLE_VARS_MOVE_ANIM);
    CALL(aGetBattleVarAddr);
    PUSH_HL;
    PUSH_AF;
    XOR_A_A;
    LD_hl_A;
    LD_addr_A(wAttackMissed);
    LD_addr_A(wEffectFailed);
    FARCALL(aBattleCommand_AttackUp2);
    POP_AF;
    POP_HL;
    LD_hl_A;
    CALL(aGetItemName);
    LD_HL(mBattleText_UsersStringBuffer1Activated);
    CALL(aStdBattleTextbox);
    CALLFAR(aBattleCommand_StatUpMessage);
    POP_AF;
    BIT_A(SUBSTATUS_CONFUSED);
    RET_NZ ;
    XOR_A_A;
    LD_addr_A(wNumHits);
    LD_DE(ANIM_CONFUSED);
    CALL(aCall_PlayBattleAnim_OnlyIfVisible);
    CALL(aSwitchTurnCore);
    LD_HL(mBecameConfusedText);
    JP(mStdBattleTextbox);

}

void EnemyTriesToFlee(void){
    LD_A_addr(wLinkMode);
    AND_A_A;
    IF_Z goto not_linked;
    LD_A_addr(wBattleAction);
    CP_A(BATTLEACTION_FORFEIT);
    IF_Z goto forfeit;


not_linked:
    AND_A_A;
    RET;


forfeit:
    CALL(aWildFled_EnemyFled_LinkBattleCanceled);
    SCF;
    RET;

}

void DetermineMoveOrder(void){
    LD_A_addr(wLinkMode);
    AND_A_A;
    IF_Z goto use_move;
    LD_A_addr(wBattleAction);
    CP_A(BATTLEACTION_STRUGGLE);
    IF_Z goto use_move;
    CP_A(BATTLEACTION_SKIPTURN);
    IF_Z goto use_move;
    SUB_A(BATTLEACTION_SWITCH1);
    IF_C goto use_move;
    LD_A_addr(wBattlePlayerAction);
    CP_A(BATTLEPLAYERACTION_SWITCH);
    IF_NZ goto switch_;
    LDH_A_addr(hSerialConnectionStatus);
    CP_A(USING_INTERNAL_CLOCK);
    IF_Z goto player_2;

    CALL(aBattleRandom);
    CP_A(50 percent + 1);
    JP_C (mDetermineMoveOrder_player_first);
    JP(mDetermineMoveOrder_enemy_first);


player_2:
    CALL(aBattleRandom);
    CP_A(50 percent + 1);
    JP_C (mDetermineMoveOrder_enemy_first);
    JP(mDetermineMoveOrder_player_first);


switch_:
    CALLFAR(aAI_Switch);
    CALL(aSetEnemyTurn);
    CALL(aSpikesDamage);
    JP(mDetermineMoveOrder_enemy_first);


use_move:
    LD_A_addr(wBattlePlayerAction);
    AND_A_A;  // BATTLEPLAYERACTION_USEMOVE?
    JP_NZ (mDetermineMoveOrder_player_first);
    CALL(aCompareMovePriority);
    IF_Z goto equal_priority;
    JP_C (mDetermineMoveOrder_player_first);  // player goes first
    JP(mDetermineMoveOrder_enemy_first);


equal_priority:
    CALL(aSetPlayerTurn);
    CALLFAR(aGetUserItem);
    PUSH_BC;
    CALLFAR(aGetOpponentItem);
    POP_DE;
    LD_A_D;
    CP_A(HELD_QUICK_CLAW);
    IF_NZ goto player_no_quick_claw;
    LD_A_B;
    CP_A(HELD_QUICK_CLAW);
    IF_Z goto both_have_quick_claw;
    CALL(aBattleRandom);
    CP_A_E;
    IF_NC goto speed_check;
    JP(mDetermineMoveOrder_player_first);


player_no_quick_claw:
    LD_A_B;
    CP_A(HELD_QUICK_CLAW);
    IF_NZ goto speed_check;
    CALL(aBattleRandom);
    CP_A_C;
    IF_NC goto speed_check;
    JP(mDetermineMoveOrder_enemy_first);


both_have_quick_claw:
    LDH_A_addr(hSerialConnectionStatus);
    CP_A(USING_INTERNAL_CLOCK);
    IF_Z goto player_2b;
    CALL(aBattleRandom);
    CP_A_C;
    JP_C (mDetermineMoveOrder_enemy_first);
    CALL(aBattleRandom);
    CP_A_E;
    JP_C (mDetermineMoveOrder_player_first);
    goto speed_check;


player_2b:
    CALL(aBattleRandom);
    CP_A_E;
    JP_C (mDetermineMoveOrder_player_first);
    CALL(aBattleRandom);
    CP_A_C;
    JP_C (mDetermineMoveOrder_enemy_first);
    goto speed_check;


speed_check:
    LD_DE(wBattleMonSpeed);
    LD_HL(wEnemyMonSpeed);
    LD_C(2);
    CALL(aCompareBytes);
    IF_Z goto speed_tie;
    JP_NC (mDetermineMoveOrder_player_first);
    JP(mDetermineMoveOrder_enemy_first);


speed_tie:
    LDH_A_addr(hSerialConnectionStatus);
    CP_A(USING_INTERNAL_CLOCK);
    IF_Z goto player_2c;
    CALL(aBattleRandom);
    CP_A(50 percent + 1);
    JP_C (mDetermineMoveOrder_player_first);
    JP(mDetermineMoveOrder_enemy_first);


player_2c:
    CALL(aBattleRandom);
    CP_A(50 percent + 1);
    JP_C (mDetermineMoveOrder_enemy_first);

player_first:
    SCF;
    RET;


enemy_first:
    AND_A_A;
    RET;

}

void CheckContestBattleOver(void){
    LD_A_addr(wBattleType);
    CP_A(BATTLETYPE_CONTEST);
    IF_NZ goto contest_not_over;
    LD_A_addr(wParkBallsRemaining);
    AND_A_A;
    IF_NZ goto contest_not_over;
    LD_A_addr(wBattleResult);
    AND_A(BATTLERESULT_BITMASK);
    ADD_A(DRAW);
    LD_addr_A(wBattleResult);
    SCF;
    RET;


contest_not_over:
    AND_A_A;
    RET;

}

void CheckPlayerLockedIn(void){
    LD_A_addr(wPlayerSubStatus4);
    AND_A(1 << SUBSTATUS_RECHARGE);
    JP_NZ (mCheckPlayerLockedIn_quit);

    LD_HL(wEnemySubStatus3);
    RES_hl(SUBSTATUS_FLINCHED);
    LD_HL(wPlayerSubStatus3);
    RES_hl(SUBSTATUS_FLINCHED);

    LD_A_hl;
    AND_A(1 << SUBSTATUS_CHARGED | 1 << SUBSTATUS_RAMPAGE);
    JP_NZ (mCheckPlayerLockedIn_quit);

    LD_HL(wPlayerSubStatus1);
    BIT_hl(SUBSTATUS_ROLLOUT);
    JP_NZ (mCheckPlayerLockedIn_quit);

    AND_A_A;
    RET;


quit:
    SCF;
    RET;

}

bool CheckPlayerLockedIn_Conv(void){
    // LD_A_addr(wPlayerSubStatus4);
    // AND_A(1 << SUBSTATUS_RECHARGE);
    // JP_NZ (mCheckPlayerLockedIn_quit);
    if(wram->wPlayerSubStatus4 & (1 << SUBSTATUS_RECHARGE))
        return true;

    // LD_HL(wEnemySubStatus3);
    // RES_hl(SUBSTATUS_FLINCHED);
    bit_reset(wram->wEnemySubStatus3, SUBSTATUS_FLINCHED);
    // LD_HL(wPlayerSubStatus3);
    // RES_hl(SUBSTATUS_FLINCHED);
    bit_reset(wram->wPlayerSubStatus3, SUBSTATUS_FLINCHED);

    // LD_A_hl;
    // AND_A(1 << SUBSTATUS_CHARGED | 1 << SUBSTATUS_RAMPAGE);
    // JP_NZ (mCheckPlayerLockedIn_quit);
    if(wram->wPlayerSubStatus3 & (1 << SUBSTATUS_CHARGED | 1 << SUBSTATUS_RAMPAGE))
        return true;

    // LD_HL(wPlayerSubStatus1);
    // BIT_hl(SUBSTATUS_ROLLOUT);
    // JP_NZ (mCheckPlayerLockedIn_quit);
    if(bit_test(wram->wPlayerSubStatus1, SUBSTATUS_ROLLOUT))
        return true;

    // AND_A_A;
    // RET;
    return false;

// quit:
    // SCF;
    // RET;
}

void ParsePlayerAction(void){
    CALL(aCheckPlayerLockedIn);
    JP_C (mParsePlayerAction_locked_in);
    LD_HL(wPlayerSubStatus5);
    BIT_hl(SUBSTATUS_ENCORED);
    IF_Z goto not_encored;
    LD_A_addr(wLastPlayerMove);
    LD_addr_A(wCurPlayerMove);
    goto encored;


not_encored:
    LD_A_addr(wBattlePlayerAction);
    CP_A(BATTLEPLAYERACTION_SWITCH);
    IF_Z goto reset_rage;
    AND_A_A;
    IF_NZ goto reset_bide;
    LD_A_addr(wPlayerSubStatus3);
    AND_A(1 << SUBSTATUS_BIDE);
    IF_NZ goto locked_in;
    XOR_A_A;
    LD_addr_A(wMoveSelectionMenuType);
    INC_A;  // POUND
    LD_addr_A(wFXAnimID);
    CALL(aMoveSelectionScreen);
    PUSH_AF;
    CALL(aSafeLoadTempTilemapToTilemap);
    CALL(aUpdateBattleHuds);
    LD_A_addr(wCurPlayerMove);
    CP_A(STRUGGLE);
    IF_Z goto struggle;
    CALL(aPlayClickSFX);


struggle:
    LD_A(0x1);
    LDH_addr_A(hBGMapMode);
    POP_AF;
    RET_NZ ;


encored:
    CALL(aSetPlayerTurn);
    CALLFAR(aUpdateMoveData);
    XOR_A_A;
    LD_addr_A(wPlayerCharging);
    LD_A_addr(wPlayerMoveStruct + MOVE_EFFECT);
    CP_A(EFFECT_FURY_CUTTER);
    IF_Z goto continue_fury_cutter;
    XOR_A_A;
    LD_addr_A(wPlayerFuryCutterCount);


continue_fury_cutter:
    LD_A_addr(wPlayerMoveStruct + MOVE_EFFECT);
    CP_A(EFFECT_RAGE);
    IF_Z goto continue_rage;
    LD_HL(wPlayerSubStatus4);
    RES_hl(SUBSTATUS_RAGE);
    XOR_A_A;
    LD_addr_A(wPlayerRageCounter);


continue_rage:
    LD_A_addr(wPlayerMoveStruct + MOVE_EFFECT);
    CP_A(EFFECT_PROTECT);
    IF_Z goto continue_protect;
    CP_A(EFFECT_ENDURE);
    IF_Z goto continue_protect;
    XOR_A_A;
    LD_addr_A(wPlayerProtectCount);
    goto continue_protect;


reset_bide:
    LD_HL(wPlayerSubStatus3);
    RES_hl(SUBSTATUS_BIDE);


locked_in:
    XOR_A_A;
    LD_addr_A(wPlayerFuryCutterCount);
    LD_addr_A(wPlayerProtectCount);
    LD_addr_A(wPlayerRageCounter);
    LD_HL(wPlayerSubStatus4);
    RES_hl(SUBSTATUS_RAGE);


continue_protect:
    CALL(aParseEnemyAction);
    XOR_A_A;
    RET;


reset_rage:
    XOR_A_A;
    LD_addr_A(wPlayerFuryCutterCount);
    LD_addr_A(wPlayerProtectCount);
    LD_addr_A(wPlayerRageCounter);
    LD_HL(wPlayerSubStatus4);
    RES_hl(SUBSTATUS_RAGE);
    XOR_A_A;
    RET;

}

void HandleEncore(void){
    LDH_A_addr(hSerialConnectionStatus);
    CP_A(USING_EXTERNAL_CLOCK);
    IF_Z goto player_1;
    CALL(aHandleEncore_do_player);
    goto do_enemy;


player_1:
    CALL(aHandleEncore_do_enemy);

do_player:
    LD_HL(wPlayerSubStatus5);
    BIT_hl(SUBSTATUS_ENCORED);
    RET_Z ;
    LD_A_addr(wPlayerEncoreCount);
    DEC_A;
    LD_addr_A(wPlayerEncoreCount);
    IF_Z goto end_player_encore;
    LD_HL(wBattleMonPP);
    LD_A_addr(wCurMoveNum);
    LD_C_A;
    LD_B(0);
    ADD_HL_BC;
    LD_A_hl;
    AND_A(PP_MASK);
    RET_NZ ;


end_player_encore:
    LD_HL(wPlayerSubStatus5);
    RES_hl(SUBSTATUS_ENCORED);
    CALL(aSetEnemyTurn);
    LD_HL(mBattleText_TargetsEncoreEnded);
    JP(mStdBattleTextbox);


do_enemy:
    LD_HL(wEnemySubStatus5);
    BIT_hl(SUBSTATUS_ENCORED);
    RET_Z ;
    LD_A_addr(wEnemyEncoreCount);
    DEC_A;
    LD_addr_A(wEnemyEncoreCount);
    IF_Z goto end_enemy_encore;
    LD_HL(wEnemyMonPP);
    LD_A_addr(wCurEnemyMoveNum);
    LD_C_A;
    LD_B(0);
    ADD_HL_BC;
    LD_A_hl;
    AND_A(PP_MASK);
    RET_NZ ;


end_enemy_encore:
    LD_HL(wEnemySubStatus5);
    RES_hl(SUBSTATUS_ENCORED);
    CALL(aSetPlayerTurn);
    LD_HL(mBattleText_TargetsEncoreEnded);
    JP(mStdBattleTextbox);

}

void TryEnemyFlee(void){
    LD_A_addr(wBattleMode);
    DEC_A;
    IF_NZ goto Stay;

    LD_A_addr(wPlayerSubStatus5);
    BIT_A(SUBSTATUS_CANT_RUN);
    IF_NZ goto Stay;

    LD_A_addr(wEnemyWrapCount);
    AND_A_A;
    IF_NZ goto Stay;

    LD_A_addr(wEnemyMonStatus);
    AND_A(1 << FRZ | SLP);
    IF_NZ goto Stay;

    LD_A_addr(wTempEnemyMonSpecies);
    LD_DE(1);
    LD_HL(mAlwaysFleeMons);
    CALL(aIsInArray);
    IF_C goto Flee;

    CALL(aBattleRandom);
    LD_B_A;
    CP_A(50 percent + 1);
    IF_NC goto Stay;

    PUSH_BC;
    LD_A_addr(wTempEnemyMonSpecies);
    LD_DE(1);
    LD_HL(mOftenFleeMons);
    CALL(aIsInArray);
    POP_BC;
    IF_C goto Flee;

    LD_A_B;
    CP_A(10 percent + 1);
    IF_NC goto Stay;

    LD_A_addr(wTempEnemyMonSpecies);
    LD_DE(1);
    LD_HL(mSometimesFleeMons);
    CALL(aIsInArray);
    IF_C goto Flee;


Stay:
    AND_A_A;
    RET;


Flee:
    SCF;
    RET;

// INCLUDE "data/wild/flee_mons.asm"

    return CompareMovePriority();
}

void CompareMovePriority(void){
//  Compare the priority of the player and enemy's moves.
//  Return carry if the player goes first, or z if they match.

    LD_A_addr(wCurPlayerMove);
    CALL(aGetMovePriority);
    LD_B_A;
    PUSH_BC;
    LD_A_addr(wCurEnemyMove);
    CALL(aGetMovePriority);
    POP_BC;
    CP_A_B;
    RET;

}

void GetMovePriority(void){
//  Return the priority (0-3) of move a.

    LD_B_A;

// Vital Throw goes last.
    CP_A(VITAL_THROW);
    LD_A(0);
    RET_Z ;

    CALL(aGetMoveEffect);
    LD_HL(mMoveEffectPriorities);

loop:
    LD_A_hli;
    CP_A_B;
    IF_Z goto done;
    INC_HL;
    CP_A(-1);
    IF_NZ goto loop;

    LD_A(BASE_PRIORITY);
    RET;


done:
    LD_A_hl;
    RET;

// INCLUDE "data/moves/effects_priorities.asm"

    return GetMoveEffect();
}

void GetMoveEffect(void){
    LD_A_B;
    DEC_A;
    LD_HL(mMoves + MOVE_EFFECT);
    LD_BC(MOVE_LENGTH);
    CALL(aAddNTimes);
    LD_A(BANK(aMoves));
    CALL(aGetFarByte);
    LD_B_A;
    RET;

}

void Battle_EnemyFirst(void){
    CALL(aLoadTilemapToTempTilemap);
    CALL(aTryEnemyFlee);
    JP_C (mWildFled_EnemyFled_LinkBattleCanceled);
    CALL(aSetEnemyTurn);
    LD_A(0x1);
    LD_addr_A(wEnemyGoesFirst);
    CALLFAR(aAI_SwitchOrTryItem);
    IF_C goto switch_item;
    CALL(aEnemyTurn_EndOpponentProtectEndureDestinyBond);
    CALL(aCheckMobileBattleError);
    RET_C ;
    LD_A_addr(wForcedSwitch);
    AND_A_A;
    RET_NZ ;
    CALL(aHasPlayerFainted);
    JP_Z (mHandlePlayerMonFaint);
    CALL(aHasEnemyFainted);
    JP_Z (mHandleEnemyMonFaint);


switch_item:
    CALL(aSetEnemyTurn);
    CALL(aResidualDamage);
    JP_Z (mHandleEnemyMonFaint);
    CALL(aRefreshBattleHuds);
    CALL(aPlayerTurn_EndOpponentProtectEndureDestinyBond);
    CALL(aCheckMobileBattleError);
    RET_C ;
    LD_A_addr(wForcedSwitch);
    AND_A_A;
    RET_NZ ;
    CALL(aHasEnemyFainted);
    JP_Z (mHandleEnemyMonFaint);
    CALL(aHasPlayerFainted);
    JP_Z (mHandlePlayerMonFaint);
    CALL(aSetPlayerTurn);
    CALL(aResidualDamage);
    JP_Z (mHandlePlayerMonFaint);
    CALL(aRefreshBattleHuds);
    XOR_A_A;  // BATTLEPLAYERACTION_USEMOVE
    LD_addr_A(wBattlePlayerAction);
    RET;

}

void Battle_PlayerFirst(void){
    XOR_A_A;
    LD_addr_A(wEnemyGoesFirst);
    CALL(aSetEnemyTurn);
    CALLFAR(aAI_SwitchOrTryItem);
    PUSH_AF;
    CALL(aPlayerTurn_EndOpponentProtectEndureDestinyBond);
    POP_BC;
    LD_A_addr(wForcedSwitch);
    AND_A_A;
    RET_NZ ;
    CALL(aCheckMobileBattleError);
    RET_C ;
    CALL(aHasEnemyFainted);
    JP_Z (mHandleEnemyMonFaint);
    CALL(aHasPlayerFainted);
    JP_Z (mHandlePlayerMonFaint);
    PUSH_BC;
    CALL(aSetPlayerTurn);
    CALL(aResidualDamage);
    POP_BC;
    JP_Z (mHandlePlayerMonFaint);
    PUSH_BC;
    CALL(aRefreshBattleHuds);
    POP_AF;
    IF_C goto switched_or_used_item;
    CALL(aLoadTilemapToTempTilemap);
    CALL(aTryEnemyFlee);
    JP_C (mWildFled_EnemyFled_LinkBattleCanceled);
    CALL(aEnemyTurn_EndOpponentProtectEndureDestinyBond);
    CALL(aCheckMobileBattleError);
    RET_C ;
    LD_A_addr(wForcedSwitch);
    AND_A_A;
    RET_NZ ;
    CALL(aHasPlayerFainted);
    JP_Z (mHandlePlayerMonFaint);
    CALL(aHasEnemyFainted);
    JP_Z (mHandleEnemyMonFaint);


switched_or_used_item:
    CALL(aSetEnemyTurn);
    CALL(aResidualDamage);
    JP_Z (mHandleEnemyMonFaint);
    CALL(aRefreshBattleHuds);
    XOR_A_A;  // BATTLEPLAYERACTION_USEMOVE
    LD_addr_A(wBattlePlayerAction);
    RET;

}

void PlayerTurn_EndOpponentProtectEndureDestinyBond(void){
    CALL(aSetPlayerTurn);
    CALL(aEndUserDestinyBond);
    CALLFAR(aDoPlayerTurn);
    JP(mEndOpponentProtectEndureDestinyBond);

}

void EnemyTurn_EndOpponentProtectEndureDestinyBond(void){
    CALL(aSetEnemyTurn);
    CALL(aEndUserDestinyBond);
    CALLFAR(aDoEnemyTurn);
    JP(mEndOpponentProtectEndureDestinyBond);

}

void EndOpponentProtectEndureDestinyBond(void){
    LD_A(BATTLE_VARS_SUBSTATUS1_OPP);
    CALL(aGetBattleVarAddr);
    RES_hl(SUBSTATUS_PROTECT);
    RES_hl(SUBSTATUS_ENDURE);
    LD_A(BATTLE_VARS_SUBSTATUS5_OPP);
    CALL(aGetBattleVarAddr);
    RES_hl(SUBSTATUS_DESTINY_BOND);
    RET;

}

void EndUserDestinyBond(void){
    LD_A(BATTLE_VARS_SUBSTATUS5);
    CALL(aGetBattleVarAddr);
    RES_hl(SUBSTATUS_DESTINY_BOND);
    RET;

}

void HasUserFainted(void){
    LDH_A_addr(hBattleTurn);
    AND_A_A;
    JR_Z (mHasPlayerFainted);
    return HasEnemyFainted();
}

void HasEnemyFainted(void){
    LD_HL(wEnemyMonHP);
    JR(mCheckIfHPIsZero);

}

void HasPlayerFainted(void){
    LD_HL(wBattleMonHP);

    return CheckIfHPIsZero();
}

void CheckIfHPIsZero(void){
    LD_A_hli;
    OR_A_hl;
    RET;

}

void ResidualDamage(void){
//  Return z if the user fainted before
//  or as a result of residual damage.
//  For Sandstorm damage, see HandleWeather.

    CALL(aHasUserFainted);
    RET_Z ;

    LD_A(BATTLE_VARS_STATUS);
    CALL(aGetBattleVar);
    AND_A(1 << PSN | 1 << BRN);
    IF_Z goto did_psn_brn;

    LD_HL(mHurtByPoisonText);
    LD_DE(ANIM_PSN);
    AND_A(1 << BRN);
    IF_Z goto got_anim;
    LD_HL(mHurtByBurnText);
    LD_DE(ANIM_BRN);

got_anim:

    PUSH_DE;
    CALL(aStdBattleTextbox);
    POP_DE;

    XOR_A_A;
    LD_addr_A(wNumHits);
    CALL(aCall_PlayBattleAnim_OnlyIfVisible);
    CALL(aGetEighthMaxHP);
    LD_DE(wPlayerToxicCount);
    LDH_A_addr(hBattleTurn);
    AND_A_A;
    IF_Z goto check_toxic;
    LD_DE(wEnemyToxicCount);

check_toxic:

    LD_A(BATTLE_VARS_SUBSTATUS5);
    CALL(aGetBattleVar);
    BIT_A(SUBSTATUS_TOXIC);
    IF_Z goto did_toxic;
    CALL(aGetSixteenthMaxHP);
    LD_A_de;
    INC_A;
    LD_de_A;
    LD_HL(0);

add:
    ADD_HL_BC;
    DEC_A;
    IF_NZ goto add;
    LD_B_H;
    LD_C_L;

did_toxic:

    CALL(aSubtractHPFromUser);

did_psn_brn:

    CALL(aHasUserFainted);
    JP_Z (mResidualDamage_fainted);

    LD_A(BATTLE_VARS_SUBSTATUS4);
    CALL(aGetBattleVarAddr);
    BIT_hl(SUBSTATUS_LEECH_SEED);
    IF_Z goto not_seeded;

    CALL(aSwitchTurnCore);
    XOR_A_A;
    LD_addr_A(wNumHits);
    LD_DE(ANIM_SAP);
    LD_A(BATTLE_VARS_SUBSTATUS3_OPP);
    CALL(aGetBattleVar);
    AND_A(1 << SUBSTATUS_FLYING | 1 << SUBSTATUS_UNDERGROUND);
    CALL_Z (aCall_PlayBattleAnim_OnlyIfVisible);
    CALL(aSwitchTurnCore);

    CALL(aGetEighthMaxHP);
    CALL(aSubtractHPFromUser);
    LD_A(0x1);
    LDH_addr_A(hBGMapMode);
    CALL(aRestoreHP);
    LD_HL(mLeechSeedSapsText);
    CALL(aStdBattleTextbox);

not_seeded:

    CALL(aHasUserFainted);
    IF_Z goto fainted;

    LD_A(BATTLE_VARS_SUBSTATUS1);
    CALL(aGetBattleVarAddr);
    BIT_hl(SUBSTATUS_NIGHTMARE);
    IF_Z goto not_nightmare;
    XOR_A_A;
    LD_addr_A(wNumHits);
    LD_DE(ANIM_IN_NIGHTMARE);
    CALL(aCall_PlayBattleAnim_OnlyIfVisible);
    CALL(aGetQuarterMaxHP);
    CALL(aSubtractHPFromUser);
    LD_HL(mHasANightmareText);
    CALL(aStdBattleTextbox);

not_nightmare:

    CALL(aHasUserFainted);
    IF_Z goto fainted;

    LD_A(BATTLE_VARS_SUBSTATUS1);
    CALL(aGetBattleVarAddr);
    BIT_hl(SUBSTATUS_CURSE);
    IF_Z goto not_cursed;

    XOR_A_A;
    LD_addr_A(wNumHits);
    LD_DE(ANIM_IN_NIGHTMARE);
    CALL(aCall_PlayBattleAnim_OnlyIfVisible);
    CALL(aGetQuarterMaxHP);
    CALL(aSubtractHPFromUser);
    LD_HL(mHurtByCurseText);
    CALL(aStdBattleTextbox);


not_cursed:
    LD_HL(wBattleMonHP);
    LDH_A_addr(hBattleTurn);
    AND_A_A;
    IF_Z goto check_fainted;
    LD_HL(wEnemyMonHP);


check_fainted:
    LD_A_hli;
    OR_A_hl;
    RET_NZ ;


fainted:
    CALL(aRefreshBattleHuds);
    LD_C(20);
    CALL(aDelayFrames);
    XOR_A_A;
    RET;

}

void HandlePerishSong(void){
    LDH_A_addr(hSerialConnectionStatus);
    CP_A(USING_EXTERNAL_CLOCK);
    IF_Z goto EnemyFirst;
    CALL(aSetPlayerTurn);
    CALL(aHandlePerishSong_do_it);
    CALL(aSetEnemyTurn);
    JP(mHandlePerishSong_do_it);


EnemyFirst:
    CALL(aSetEnemyTurn);
    CALL(aHandlePerishSong_do_it);
    CALL(aSetPlayerTurn);


do_it:
    LD_HL(wPlayerPerishCount);
    LDH_A_addr(hBattleTurn);
    AND_A_A;
    IF_Z goto got_count;
    LD_HL(wEnemyPerishCount);


got_count:
    LD_A(BATTLE_VARS_SUBSTATUS1);
    CALL(aGetBattleVar);
    BIT_A(SUBSTATUS_PERISH);
    RET_Z ;
    DEC_hl;
    LD_A_hl;
    LD_addr_A(wTextDecimalByte);
    PUSH_AF;
    LD_HL(mPerishCountText);
    CALL(aStdBattleTextbox);
    POP_AF;
    RET_NZ ;
    LD_A(BATTLE_VARS_SUBSTATUS1);
    CALL(aGetBattleVarAddr);
    RES_hl(SUBSTATUS_PERISH);
    LDH_A_addr(hBattleTurn);
    AND_A_A;
    IF_NZ goto kill_enemy;
    LD_HL(wBattleMonHP);
    XOR_A_A;
    LD_hli_A;
    LD_hl_A;
    LD_HL(wPartyMon1HP);
    LD_A_addr(wCurBattleMon);
    CALL(aGetPartyLocation);
    XOR_A_A;
    LD_hli_A;
    LD_hl_A;
    RET;


kill_enemy:
    LD_HL(wEnemyMonHP);
    XOR_A_A;
    LD_hli_A;
    LD_hl_A;
    LD_A_addr(wBattleMode);
    DEC_A;
    RET_Z ;
    LD_HL(wOTPartyMon1HP);
    LD_A_addr(wCurOTMon);
    CALL(aGetPartyLocation);
    XOR_A_A;
    LD_hli_A;
    LD_hl_A;
    RET;

}

void HandleWrap(void){
    LDH_A_addr(hSerialConnectionStatus);
    CP_A(USING_EXTERNAL_CLOCK);
    IF_Z goto EnemyFirst;
    CALL(aSetPlayerTurn);
    CALL(aHandleWrap_do_it);
    CALL(aSetEnemyTurn);
    JP(mHandleWrap_do_it);


EnemyFirst:
    CALL(aSetEnemyTurn);
    CALL(aHandleWrap_do_it);
    CALL(aSetPlayerTurn);


do_it:
    LD_HL(wPlayerWrapCount);
    LD_DE(wPlayerTrappingMove);
    LDH_A_addr(hBattleTurn);
    AND_A_A;
    IF_Z goto got_addrs;
    LD_HL(wEnemyWrapCount);
    LD_DE(wEnemyTrappingMove);


got_addrs:
    LD_A_hl;
    AND_A_A;
    RET_Z ;

    LD_A(BATTLE_VARS_SUBSTATUS4);
    CALL(aGetBattleVar);
    BIT_A(SUBSTATUS_SUBSTITUTE);
    RET_NZ ;

    LD_A_de;
    LD_addr_A(wNamedObjectIndex);
    LD_addr_A(wFXAnimID);
    CALL(aGetMoveName);
    DEC_hl;
    IF_Z goto release_from_bounds;

    LD_A(BATTLE_VARS_SUBSTATUS3);
    CALL(aGetBattleVar);
    AND_A(1 << SUBSTATUS_FLYING | 1 << SUBSTATUS_UNDERGROUND);
    IF_NZ goto skip_anim;

    CALL(aSwitchTurnCore);
    XOR_A_A;
    LD_addr_A(wNumHits);
    LD_addr_A(wFXAnimID + 1);
    PREDEF(pPlayBattleAnim);
    CALL(aSwitchTurnCore);


skip_anim:
    CALL(aGetSixteenthMaxHP);
    CALL(aSubtractHPFromUser);
    LD_HL(mBattleText_UsersHurtByStringBuffer1);
    goto print_text;


release_from_bounds:
    LD_HL(mBattleText_UserWasReleasedFromStringBuffer1);


print_text:
    JP(mStdBattleTextbox);

}

void SwitchTurnCore(void){
    LDH_A_addr(hBattleTurn);
    XOR_A(1);
    LDH_addr_A(hBattleTurn);
    RET;

}

void HandleLeftovers(void){
    LDH_A_addr(hSerialConnectionStatus);
    CP_A(USING_EXTERNAL_CLOCK);
    IF_Z goto DoEnemyFirst;
    CALL(aSetPlayerTurn);
    CALL(aHandleLeftovers_do_it);
    CALL(aSetEnemyTurn);
    JP(mHandleLeftovers_do_it);


DoEnemyFirst:
    CALL(aSetEnemyTurn);
    CALL(aHandleLeftovers_do_it);
    CALL(aSetPlayerTurn);

do_it:

    CALLFAR(aGetUserItem);
    LD_A_hl;
    LD_addr_A(wNamedObjectIndex);
    CALL(aGetItemName);
    LD_A_B;
    CP_A(HELD_LEFTOVERS);
    RET_NZ ;

    LD_HL(wBattleMonHP);
    LDH_A_addr(hBattleTurn);
    AND_A_A;
    IF_Z goto got_hp;
    LD_HL(wEnemyMonHP);


got_hp:
//  Don't restore if we're already at max HP
    LD_A_hli;
    LD_B_A;
    LD_A_hli;
    LD_C_A;
    LD_A_hli;
    CP_A_B;
    IF_NZ goto restore;
    LD_A_hl;
    CP_A_C;
    RET_Z ;


restore:
    CALL(aGetSixteenthMaxHP);
    CALL(aSwitchTurnCore);
    CALL(aRestoreHP);
    LD_HL(mBattleText_TargetRecoveredWithItem);
    JP(mStdBattleTextbox);

}

void HandleMysteryberry(void){
    LDH_A_addr(hSerialConnectionStatus);
    CP_A(USING_EXTERNAL_CLOCK);
    IF_Z goto DoEnemyFirst;
    CALL(aSetPlayerTurn);
    CALL(aHandleMysteryberry_do_it);
    CALL(aSetEnemyTurn);
    JP(mHandleMysteryberry_do_it);


DoEnemyFirst:
    CALL(aSetEnemyTurn);
    CALL(aHandleMysteryberry_do_it);
    CALL(aSetPlayerTurn);


do_it:
    CALLFAR(aGetUserItem);
    LD_A_B;
    CP_A(HELD_RESTORE_PP);
    IF_NZ goto quit;
    LD_HL(wPartyMon1PP);
    LD_A_addr(wCurBattleMon);
    CALL(aGetPartyLocation);
    LD_D_H;
    LD_E_L;
    LD_HL(wPartyMon1Moves);
    LD_A_addr(wCurBattleMon);
    CALL(aGetPartyLocation);
    LDH_A_addr(hBattleTurn);
    AND_A_A;
    IF_Z goto wild;
    LD_DE(wWildMonPP);
    LD_HL(wWildMonMoves);
    LD_A_addr(wBattleMode);
    DEC_A;
    IF_Z goto wild;
    LD_HL(wOTPartyMon1PP);
    LD_A_addr(wCurOTMon);
    CALL(aGetPartyLocation);
    LD_D_H;
    LD_E_L;
    LD_HL(wOTPartyMon1Moves);
    LD_A_addr(wCurOTMon);
    CALL(aGetPartyLocation);


wild:
    LD_C(0x0);

loop:
    LD_A_hl;
    AND_A_A;
    IF_Z goto quit;
    LD_A_de;
    AND_A(PP_MASK);
    IF_Z goto restore;
    INC_HL;
    INC_DE;
    INC_C;
    LD_A_C;
    CP_A(NUM_MOVES);
    IF_NZ goto loop;


quit:
    RET;


restore:
// lousy hack
    LD_A_hl;
    CP_A(SKETCH);
    LD_B(1);
    IF_Z goto sketch;
    LD_B(5);

sketch:
    LD_A_de;
    ADD_A_B;
    LD_de_A;
    PUSH_BC;
    PUSH_BC;
    LD_A_hl;
    LD_addr_A(wTempByteValue);
    LD_DE(wBattleMonMoves - 1);
    LD_HL(wBattleMonPP);
    LDH_A_addr(hBattleTurn);
    AND_A_A;
    IF_Z goto player_pp;
    LD_DE(wEnemyMonMoves - 1);
    LD_HL(wEnemyMonPP);

player_pp:
    INC_DE;
    POP_BC;
    LD_B(0);
    ADD_HL_BC;
    PUSH_HL;
    LD_H_D;
    LD_L_E;
    ADD_HL_BC;
    POP_DE;
    POP_BC;

    LD_A_addr(wTempByteValue);
    CP_A_hl;
    IF_NZ goto skip_checks;
    LDH_A_addr(hBattleTurn);
    AND_A_A;
    LD_A_addr(wPlayerSubStatus5);
    IF_Z goto check_transform;
    LD_A_addr(wEnemySubStatus5);

check_transform:
    BIT_A(SUBSTATUS_TRANSFORMED);
    IF_NZ goto skip_checks;
    LD_A_de;
    ADD_A_B;
    LD_de_A;

skip_checks:
    CALLFAR(aGetUserItem);
    LD_A_hl;
    LD_addr_A(wNamedObjectIndex);
    XOR_A_A;
    LD_hl_A;
    CALL(aGetPartymonItem);
    LDH_A_addr(hBattleTurn);
    AND_A_A;
    IF_Z goto consume_item;
    LD_A_addr(wBattleMode);
    DEC_A;
    IF_Z goto skip_consumption;
    CALL(aGetOTPartymonItem);


consume_item:
    XOR_A_A;
    LD_hl_A;


skip_consumption:
    CALL(aGetItemName);
    CALL(aSwitchTurnCore);
    CALL(aItemRecoveryAnim);
    CALL(aSwitchTurnCore);
    LD_HL(mBattleText_UserRecoveredPPUsing);
    JP(mStdBattleTextbox);

}

void HandleFutureSight(void){
    LDH_A_addr(hSerialConnectionStatus);
    CP_A(USING_EXTERNAL_CLOCK);
    IF_Z goto enemy_first;
    CALL(aSetPlayerTurn);
    CALL(aHandleFutureSight_do_it);
    CALL(aSetEnemyTurn);
    JP(mHandleFutureSight_do_it);


enemy_first:
    CALL(aSetEnemyTurn);
    CALL(aHandleFutureSight_do_it);
    CALL(aSetPlayerTurn);


do_it:
    LD_HL(wPlayerFutureSightCount);
    LDH_A_addr(hBattleTurn);
    AND_A_A;
    IF_Z goto okay;
    LD_HL(wEnemyFutureSightCount);


okay:
    LD_A_hl;
    AND_A_A;
    RET_Z ;
    DEC_A;
    LD_hl_A;
    CP_A(0x1);
    RET_NZ ;

    LD_HL(mBattleText_TargetWasHitByFutureSight);
    CALL(aStdBattleTextbox);

    LD_A(BATTLE_VARS_MOVE);
    CALL(aGetBattleVarAddr);
    PUSH_AF;
    LD_A(FUTURE_SIGHT);
    LD_hl_A;

    CALLFAR(aUpdateMoveData);
    XOR_A_A;
    LD_addr_A(wAttackMissed);
    LD_addr_A(wAlreadyDisobeyed);
    LD_A(EFFECTIVE);
    LD_addr_A(wTypeModifier);
    CALLFAR(aDoMove);
    XOR_A_A;
    LD_addr_A(wCurDamage);
    LD_addr_A(wCurDamage + 1);

    LD_A(BATTLE_VARS_MOVE);
    CALL(aGetBattleVarAddr);
    POP_AF;
    LD_hl_A;

    CALL(aUpdateBattleMonInParty);
    JP(mUpdateEnemyMonInParty);

}

void HandleDefrost(void){
    LDH_A_addr(hSerialConnectionStatus);
    CP_A(USING_EXTERNAL_CLOCK);
    IF_Z goto enemy_first;
    CALL(aHandleDefrost_do_player_turn);
    goto do_enemy_turn;


enemy_first:
    CALL(aHandleDefrost_do_enemy_turn);

do_player_turn:
    LD_A_addr(wBattleMonStatus);
    BIT_A(FRZ);
    RET_Z ;

    LD_A_addr(wPlayerJustGotFrozen);
    AND_A_A;
    RET_NZ ;

    CALL(aBattleRandom);
    CP_A(10 percent);
    RET_NC ;
    XOR_A_A;
    LD_addr_A(wBattleMonStatus);
    LD_A_addr(wCurBattleMon);
    LD_HL(wPartyMon1Status);
    CALL(aGetPartyLocation);
    LD_hl(0);
    CALL(aUpdateBattleHuds);
    CALL(aSetEnemyTurn);
    LD_HL(mDefrostedOpponentText);
    JP(mStdBattleTextbox);


do_enemy_turn:
    LD_A_addr(wEnemyMonStatus);
    BIT_A(FRZ);
    RET_Z ;
    LD_A_addr(wEnemyJustGotFrozen);
    AND_A_A;
    RET_NZ ;
    CALL(aBattleRandom);
    CP_A(10 percent);
    RET_NC ;
    XOR_A_A;
    LD_addr_A(wEnemyMonStatus);

    LD_A_addr(wBattleMode);
    DEC_A;
    IF_Z goto wild;
    LD_A_addr(wCurOTMon);
    LD_HL(wOTPartyMon1Status);
    CALL(aGetPartyLocation);
    LD_hl(0);

wild:

    CALL(aUpdateBattleHuds);
    CALL(aSetPlayerTurn);
    LD_HL(mDefrostedOpponentText);
    JP(mStdBattleTextbox);

}

void HandleSafeguard(void){
    LDH_A_addr(hSerialConnectionStatus);
    CP_A(USING_EXTERNAL_CLOCK);
    IF_Z goto player1;
    CALL(aHandleSafeguard_CheckPlayer);
    goto CheckEnemy;


player1:
    CALL(aHandleSafeguard_CheckEnemy);

CheckPlayer:
    LD_A_addr(wPlayerScreens);
    BIT_A(SCREENS_SAFEGUARD);
    RET_Z ;
    LD_HL(wPlayerSafeguardCount);
    DEC_hl;
    RET_NZ ;
    RES_A(SCREENS_SAFEGUARD);
    LD_addr_A(wPlayerScreens);
    XOR_A_A;
    goto print;


CheckEnemy:
    LD_A_addr(wEnemyScreens);
    BIT_A(SCREENS_SAFEGUARD);
    RET_Z ;
    LD_HL(wEnemySafeguardCount);
    DEC_hl;
    RET_NZ ;
    RES_A(SCREENS_SAFEGUARD);
    LD_addr_A(wEnemyScreens);
    LD_A(0x1);


print:
    LDH_addr_A(hBattleTurn);
    LD_HL(mBattleText_SafeguardFaded);
    JP(mStdBattleTextbox);

}

void HandleScreens(void){
    LDH_A_addr(hSerialConnectionStatus);
    CP_A(USING_EXTERNAL_CLOCK);
    IF_Z goto Both;
    CALL(aHandleScreens_CheckPlayer);
    goto CheckEnemy;


Both:
    CALL(aHandleScreens_CheckEnemy);


CheckPlayer:
    CALL(aSetPlayerTurn);
    LD_DE(mHandleScreens_Your);
    CALL(aHandleScreens_Copy);
    LD_HL(wPlayerScreens);
    LD_DE(wPlayerLightScreenCount);
    goto TickScreens;


CheckEnemy:
    CALL(aSetEnemyTurn);
    LD_DE(mHandleScreens_Enemy);
    CALL(aHandleScreens_Copy);
    LD_HL(wEnemyScreens);
    LD_DE(wEnemyLightScreenCount);


TickScreens:
    BIT_hl(SCREENS_LIGHT_SCREEN);
    CALL_NZ (aHandleScreens_LightScreenTick);
    BIT_hl(SCREENS_REFLECT);
    CALL_NZ (aHandleScreens_ReflectTick);
    RET;


Copy:
    LD_HL(wStringBuffer1);
    JP(mCopyName2);


Your:
    //db ['"Your@"'];

Enemy:
    //db ['"Enemy@"'];


LightScreenTick:
    LD_A_de;
    DEC_A;
    LD_de_A;
    RET_NZ ;
    RES_hl(SCREENS_LIGHT_SCREEN);
    PUSH_HL;
    PUSH_DE;
    LD_HL(mBattleText_MonsLightScreenFell);
    CALL(aStdBattleTextbox);
    POP_DE;
    POP_HL;
    RET;


ReflectTick:
    INC_DE;
    LD_A_de;
    DEC_A;
    LD_de_A;
    RET_NZ ;
    RES_hl(SCREENS_REFLECT);
    LD_HL(mBattleText_MonsReflectFaded);
    JP(mStdBattleTextbox);

}

void HandleWeather(void){
    LD_A_addr(wBattleWeather);
    CP_A(WEATHER_NONE);
    RET_Z ;

    LD_HL(wWeatherCount);
    DEC_hl;
    IF_Z goto ended;

    LD_HL(mHandleWeather_WeatherMessages);
    CALL(aHandleWeather_PrintWeatherMessage);

    LD_A_addr(wBattleWeather);
    CP_A(WEATHER_SANDSTORM);
    RET_NZ ;

    LDH_A_addr(hSerialConnectionStatus);
    CP_A(USING_EXTERNAL_CLOCK);
    IF_Z goto enemy_first;

//  player first
    CALL(aSetPlayerTurn);
    CALL(aHandleWeather_SandstormDamage);
    CALL(aSetEnemyTurn);
    goto SandstormDamage;


enemy_first:
    CALL(aSetEnemyTurn);
    CALL(aHandleWeather_SandstormDamage);
    CALL(aSetPlayerTurn);


SandstormDamage:
    LD_A(BATTLE_VARS_SUBSTATUS3);
    CALL(aGetBattleVar);
    BIT_A(SUBSTATUS_UNDERGROUND);
    RET_NZ ;

    LD_HL(wBattleMonType1);
    LDH_A_addr(hBattleTurn);
    AND_A_A;
    IF_Z goto ok;
    LD_HL(wEnemyMonType1);

ok:
    LD_A_hli;
    CP_A(ROCK);
    RET_Z ;
    CP_A(GROUND);
    RET_Z ;
    CP_A(STEEL);
    RET_Z ;

    LD_A_hl;
    CP_A(ROCK);
    RET_Z ;
    CP_A(GROUND);
    RET_Z ;
    CP_A(STEEL);
    RET_Z ;

    CALL(aSwitchTurnCore);
    XOR_A_A;
    LD_addr_A(wNumHits);
    LD_DE(ANIM_IN_SANDSTORM);
    CALL(aCall_PlayBattleAnim);
    CALL(aSwitchTurnCore);
    CALL(aGetEighthMaxHP);
    CALL(aSubtractHPFromUser);

    LD_HL(mSandstormHitsText);
    JP(mStdBattleTextbox);


ended:
    LD_HL(mHandleWeather_WeatherEndedMessages);
    CALL(aHandleWeather_PrintWeatherMessage);
    XOR_A_A;
    LD_addr_A(wBattleWeather);
    RET;


PrintWeatherMessage:
    LD_A_addr(wBattleWeather);
    DEC_A;
    LD_C_A;
    LD_B(0);
    ADD_HL_BC;
    ADD_HL_BC;
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    JP(mStdBattleTextbox);


WeatherMessages:
//  entries correspond to WEATHER_* constants
    //dw ['BattleText_RainContinuesToFall'];
    //dw ['BattleText_TheSunlightIsStrong'];
    //dw ['BattleText_TheSandstormRages'];


WeatherEndedMessages:
//  entries correspond to WEATHER_* constants
    //dw ['BattleText_TheRainStopped'];
    //dw ['BattleText_TheSunlightFaded'];
    //dw ['BattleText_TheSandstormSubsided'];

    return SubtractHPFromTarget();
}

void SubtractHPFromTarget(void){
    CALL(aSubtractHP);
    JP(mUpdateHPBar);

}

void SubtractHPFromUser(void){
//  Subtract HP from mon
    CALL(aSubtractHP);
    JP(mUpdateHPBarBattleHuds);

}

void SubtractHP(void){
    LD_HL(wBattleMonHP);
    LDH_A_addr(hBattleTurn);
    AND_A_A;
    IF_Z goto ok;
    LD_HL(wEnemyMonHP);

ok:
    INC_HL;
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
    RET_NC ;

    LD_A_addr(wHPBuffer2);
    LD_C_A;
    LD_A_addr(wHPBuffer2 + 1);
    LD_B_A;
    XOR_A_A;
    LD_hli_A;
    LD_hl_A;
    LD_addr_A(wHPBuffer3);
    LD_addr_A(wHPBuffer3 + 1);
    RET;

}

void GetSixteenthMaxHP(void){
    CALL(aGetQuarterMaxHP);
//  quarter result
    SRL_C;
    SRL_C;
//  at least 1
    LD_A_C;
    AND_A_A;
    IF_NZ goto ok;
    INC_C;

ok:
    RET;

}

void GetEighthMaxHP(void){
//  output: bc
    CALL(aGetQuarterMaxHP);
//  assumes nothing can have 1024 or more hp
//  halve result
    SRL_C;
//  at least 1
    LD_A_C;
    AND_A_A;
    IF_NZ goto end;
    INC_C;

end:
    RET;

}

void GetQuarterMaxHP(void){
//  output: bc
    CALL(aGetMaxHP);

//  quarter result
    SRL_B;
    RR_C;
    SRL_B;
    RR_C;

//  assumes nothing can have 1024 or more hp
//  at least 1
    LD_A_C;
    AND_A_A;
    IF_NZ goto end;
    INC_C;

end:
    RET;

}

void GetHalfMaxHP(void){
//  output: bc
    CALL(aGetMaxHP);

//  halve result
    SRL_B;
    RR_C;

//  at least 1
    LD_A_C;
    OR_A_B;
    IF_NZ goto end;
    INC_C;

end:
    RET;

}

void GetMaxHP(void){
//  output: bc, wHPBuffer1

    LD_HL(wBattleMonMaxHP);
    LDH_A_addr(hBattleTurn);
    AND_A_A;
    IF_Z goto ok;
    LD_HL(wEnemyMonMaxHP);

ok:
    LD_A_hli;
    LD_addr_A(wHPBuffer1 + 1);
    LD_B_A;

    LD_A_hl;
    LD_addr_A(wHPBuffer1);
    LD_C_A;
    RET;

}

void GetHalfHP(void){
//  //  unreferenced
    LD_HL(wBattleMonHP);
    LDH_A_addr(hBattleTurn);
    AND_A_A;
    IF_Z goto ok;
    LD_HL(wEnemyMonHP);

ok:
    LD_A_hli;
    LD_B_A;
    LD_A_hli;
    LD_C_A;
    SRL_B;
    RR_C;
    LD_A_hli;
    LD_addr_A(wHPBuffer1 + 1);
    LD_A_hl;
    LD_addr_A(wHPBuffer1);
    RET;

}

void CheckUserHasEnoughHP(void){
    LD_HL(wBattleMonHP + 1);
    LDH_A_addr(hBattleTurn);
    AND_A_A;
    IF_Z goto ok;
    LD_HL(wEnemyMonHP + 1);

ok:
    LD_A_C;
    SUB_A_hl;
    DEC_HL;
    LD_A_B;
    SBC_A_hl;
    RET;

}

void RestoreHP(void){
    LD_HL(wEnemyMonMaxHP);
    LDH_A_addr(hBattleTurn);
    AND_A_A;
    IF_Z goto ok;
    LD_HL(wBattleMonMaxHP);

ok:
    LD_A_hli;
    LD_addr_A(wHPBuffer1 + 1);
    LD_A_hld;
    LD_addr_A(wHPBuffer1);
    DEC_HL;
    LD_A_hl;
    LD_addr_A(wHPBuffer2);
    ADD_A_C;
    LD_hld_A;
    LD_addr_A(wHPBuffer3);
    LD_A_hl;
    LD_addr_A(wHPBuffer2 + 1);
    ADC_A_B;
    LD_hli_A;
    LD_addr_A(wHPBuffer3 + 1);

    LD_A_addr(wHPBuffer1);
    LD_C_A;
    LD_A_hld;
    SUB_A_C;
    LD_A_addr(wHPBuffer1 + 1);
    LD_B_A;
    LD_A_hl;
    SBC_A_B;
    IF_C goto overflow;
    LD_A_B;
    LD_hli_A;
    LD_addr_A(wHPBuffer3 + 1);
    LD_A_C;
    LD_hl_A;
    LD_addr_A(wHPBuffer3);

overflow:

    CALL(aSwitchTurnCore);
    CALL(aUpdateHPBarBattleHuds);
    JP(mSwitchTurnCore);

}

void UpdateHPBarBattleHuds(void){
    CALL(aUpdateHPBar);
    JP(mUpdateBattleHuds);

}

void UpdateHPBar(void){
    hlcoord(10, 9, wTilemap);
    LDH_A_addr(hBattleTurn);
    AND_A_A;
    LD_A(1);
    IF_Z goto ok;
    hlcoord(2, 2, wTilemap);
    XOR_A_A;

ok:
    PUSH_BC;
    LD_addr_A(wWhichHPBar);
    PREDEF(pAnimateHPBar);
    POP_BC;
    RET;

}

void HandleEnemyMonFaint(void){
    CALL(aFaintEnemyPokemon);
    LD_HL(wBattleMonHP);
    LD_A_hli;
    OR_A_hl;
    CALL_Z (aFaintYourPokemon);
    XOR_A_A;
    LD_addr_A(wWhichMonFaintedFirst);
    CALL(aUpdateBattleStateAndExperienceAfterEnemyFaint);
    CALL(aCheckPlayerPartyForFitMon);
    LD_A_D;
    AND_A_A;
    JP_Z (mLostBattle);

    LD_HL(wBattleMonHP);
    LD_A_hli;
    OR_A_hl;
    CALL_NZ (aUpdatePlayerHUD);

    LD_A(0x1);
    LDH_addr_A(hBGMapMode);
    LD_C(60);
    CALL(aDelayFrames);

    LD_A_addr(wBattleMode);
    DEC_A;
    IF_NZ goto trainer;

    LD_A(1);
    LD_addr_A(wBattleEnded);
    RET;


trainer:
    CALL(aCheckEnemyTrainerDefeated);
    JP_Z (mWinTrainerBattle);

    LD_HL(wBattleMonHP);
    LD_A_hli;
    OR_A_hl;
    IF_NZ goto player_mon_not_fainted;

    CALL(aAskUseNextPokemon);
    IF_NC goto dont_flee;

    LD_A(1);
    LD_addr_A(wBattleEnded);
    RET;


dont_flee:
    CALL(aForcePlayerMonChoice);
    CALL(aCheckMobileBattleError);
    JP_C (mWildFled_EnemyFled_LinkBattleCanceled);

    LD_A(BATTLEPLAYERACTION_USEITEM);
    LD_addr_A(wBattlePlayerAction);
    CALL(aHandleEnemySwitch);
    JP_Z (mWildFled_EnemyFled_LinkBattleCanceled);
    JR(mDoubleSwitch);


player_mon_not_fainted:
    LD_A(BATTLEPLAYERACTION_USEITEM);
    LD_addr_A(wBattlePlayerAction);
    CALL(aHandleEnemySwitch);
    JP_Z (mWildFled_EnemyFled_LinkBattleCanceled);
    XOR_A_A;  // BATTLEPLAYERACTION_USEMOVE
    LD_addr_A(wBattlePlayerAction);
    RET;

}

void DoubleSwitch(void){
    LDH_A_addr(hSerialConnectionStatus);
    CP_A(USING_EXTERNAL_CLOCK);
    IF_Z goto player_1;
    CALL(aClearSprites);
    hlcoord(1, 0, wTilemap);
    LD_BC((4 << 8) | 10);
    CALL(aClearBox);
    CALL(aPlayerPartyMonEntrance);
    LD_A(0x1);
    CALL(aEnemyPartyMonEntrance);
    goto done;


player_1:
    LD_A_addr(wCurPartyMon);
    PUSH_AF;
    LD_A(0x1);
    CALL(aEnemyPartyMonEntrance);
    CALL(aClearSprites);
    CALL(aLoadTilemapToTempTilemap);
    POP_AF;
    LD_addr_A(wCurPartyMon);
    CALL(aPlayerPartyMonEntrance);


done:
    XOR_A_A;  // BATTLEPLAYERACTION_USEMOVE
    LD_addr_A(wBattlePlayerAction);
    RET;

}

void UpdateBattleStateAndExperienceAfterEnemyFaint(void){
    CALL(aUpdateBattleMonInParty);
    LD_A_addr(wBattleMode);
    DEC_A;
    IF_Z goto wild;
    LD_A_addr(wCurOTMon);
    LD_HL(wOTPartyMon1HP);
    CALL(aGetPartyLocation);
    XOR_A_A;
    LD_hli_A;
    LD_hl_A;


wild:
    LD_HL(wPlayerSubStatus3);
    RES_hl(SUBSTATUS_IN_LOOP);
    XOR_A_A;
    LD_HL(wEnemyDamageTaken);
    LD_hli_A;
    LD_hl_A;
    CALL(aNewEnemyMonStatus);
    CALL(aBreakAttraction);
    LD_A_addr(wBattleMode);
    DEC_A;
    IF_Z goto wild2;
    goto trainer;


wild2:
    CALL(aStopDangerSound);
    LD_A(0x1);
    LD_addr_A(wBattleLowHealthAlarm);


trainer:
    LD_HL(wBattleMonHP);
    LD_A_hli;
    OR_A_hl;
    IF_NZ goto player_mon_did_not_faint;
    LD_A_addr(wWhichMonFaintedFirst);
    AND_A_A;
    IF_NZ goto player_mon_did_not_faint;
    CALL(aUpdateFaintedPlayerMon);


player_mon_did_not_faint:
    CALL(aCheckPlayerPartyForFitMon);
    LD_A_D;
    AND_A_A;
    RET_Z ;
    LD_A_addr(wBattleMode);
    DEC_A;
    CALL_Z (aPlayVictoryMusic);
    CALL(aEmptyBattleTextbox);
    CALL(aLoadTilemapToTempTilemap);
    LD_A_addr(wBattleResult);
    AND_A(BATTLERESULT_BITMASK);
    LD_addr_A(wBattleResult);  // WIN
    CALL(aIsAnyMonHoldingExpShare);
    IF_Z goto skip_exp;
    LD_HL(wEnemyMonBaseStats);
    LD_B(wEnemyMonEnd - wEnemyMonBaseStats);

loop:
    SRL_hl;
    INC_HL;
    DEC_B;
    IF_NZ goto loop;


skip_exp:
    LD_HL(wEnemyMonBaseStats);
    LD_DE(wBackupEnemyMonBaseStats);
    LD_BC(wEnemyMonEnd - wEnemyMonBaseStats);
    CALL(aCopyBytes);
    XOR_A_A;
    LD_addr_A(wGivingExperienceToExpShareHolders);
    CALL(aGiveExperiencePoints);
    CALL(aIsAnyMonHoldingExpShare);
    RET_Z ;

    LD_A_addr(wBattleParticipantsNotFainted);
    PUSH_AF;
    LD_A_D;
    LD_addr_A(wBattleParticipantsNotFainted);
    LD_HL(wBackupEnemyMonBaseStats);
    LD_DE(wEnemyMonBaseStats);
    LD_BC(wEnemyMonEnd - wEnemyMonBaseStats);
    CALL(aCopyBytes);
    LD_A(0x1);
    LD_addr_A(wGivingExperienceToExpShareHolders);
    CALL(aGiveExperiencePoints);
    POP_AF;
    LD_addr_A(wBattleParticipantsNotFainted);
    RET;

}

void IsAnyMonHoldingExpShare(void){
    LD_A_addr(wPartyCount);
    LD_B_A;
    LD_HL(wPartyMon1);
    LD_C(1);
    LD_D(0);

loop:
    PUSH_HL;
    PUSH_BC;
    LD_BC(MON_HP);
    ADD_HL_BC;
    LD_A_hli;
    OR_A_hl;
    POP_BC;
    POP_HL;
    IF_Z goto next;

    PUSH_HL;
    PUSH_BC;
    LD_BC(MON_ITEM);
    ADD_HL_BC;
    POP_BC;
    LD_A_hl;
    POP_HL;

    CP_A(EXP_SHARE);
    IF_NZ goto next;
    LD_A_D;
    OR_A_C;
    LD_D_A;


next:
    SLA_C;
    PUSH_DE;
    LD_DE(PARTYMON_STRUCT_LENGTH);
    ADD_HL_DE;
    POP_DE;
    DEC_B;
    IF_NZ goto loop;

    LD_A_D;
    LD_E(0);
    LD_B(PARTY_LENGTH);

loop2:
    SRL_A;
    IF_NC goto okay;
    INC_E;


okay:
    DEC_B;
    IF_NZ goto loop2;
    LD_A_E;
    AND_A_A;
    RET;

}

void StopDangerSound(void){
    XOR_A_A;
    LD_addr_A(wLowHealthAlarm);
    RET;

}

void FaintYourPokemon(void){
    CALL(aStopDangerSound);
    CALL(aWaitSFX);
    LD_A(0xf0);
    LD_addr_A(wCryTracks);
    LD_A_addr(wBattleMonSpecies);
    CALL(aPlayStereoCry);
    CALL(aPlayerMonFaintedAnimation);
    hlcoord(9, 7, wTilemap);
    LD_BC((5 << 8) | 11);
    CALL(aClearBox);
    LD_HL(mBattleText_MonFainted);
    JP(mStdBattleTextbox);

}

void FaintEnemyPokemon(void){
    CALL(aWaitSFX);
    LD_DE(SFX_KINESIS);
    CALL(aPlaySFX);
    CALL(aEnemyMonFaintedAnimation);
    LD_DE(SFX_FAINT);
    CALL(aPlaySFX);
    hlcoord(1, 0, wTilemap);
    LD_BC((4 << 8) | 10);
    CALL(aClearBox);
    LD_HL(mBattleText_EnemyMonFainted);
    JP(mStdBattleTextbox);

}

void CheckEnemyTrainerDefeated(void){
    LD_A_addr(wOTPartyCount);
    LD_B_A;
    XOR_A_A;
    LD_HL(wOTPartyMon1HP);
    LD_DE(PARTYMON_STRUCT_LENGTH);


loop:
    OR_A_hl;
    INC_HL;
    OR_A_hl;
    DEC_HL;
    ADD_HL_DE;
    DEC_B;
    IF_NZ goto loop;

    AND_A_A;
    RET;

}

void HandleEnemySwitch(void){
    LD_HL(wEnemyHPPal);
    LD_E(HP_BAR_LENGTH_PX);
    CALL(aUpdateHPPal);
    CALL(aWaitBGMap);
    FARCALL(aEnemySwitch_TrainerHud);
    LD_A_addr(wLinkMode);
    AND_A_A;
    IF_Z goto not_linked;

    CALL(aLinkBattleSendReceiveAction);
    LD_A_addr(wBattleAction);
    CP_A(BATTLEACTION_FORFEIT);
    RET_Z ;

    CALL(aSafeLoadTempTilemapToTilemap);


not_linked:
    LD_HL(wBattleMonHP);
    LD_A_hli;
    OR_A_hl;
    LD_A(0x0);
    JR_NZ (mEnemyPartyMonEntrance);
    INC_A;
    RET;

}

void EnemyPartyMonEntrance(void){
    PUSH_AF;
    XOR_A_A;
    LD_addr_A(wEnemySwitchMonIndex);
    CALL(aNewEnemyMonStatus);
    CALL(aResetEnemyStatLevels);
    CALL(aBreakAttraction);
    POP_AF;
    AND_A_A;
    IF_NZ goto set;
    CALL(aEnemySwitch);
    goto done_switch;


set:
    CALL(aEnemySwitch_SetMode);

done_switch:
    CALL(aResetBattleParticipants);
    CALL(aSetEnemyTurn);
    CALL(aSpikesDamage);
    XOR_A_A;
    LD_addr_A(wEnemyMoveStruct + MOVE_ANIM);
    LD_addr_A(wBattlePlayerAction);
    INC_A;
    RET;

}

void WinTrainerBattle(void){
//  Player won the battle
    PEEK("");
    CALL(aStopDangerSound);
    LD_A(0x1);
    LD_addr_A(wBattleLowHealthAlarm);
    LD_addr_A(wBattleEnded);
    LD_A_addr(wLinkMode);
    AND_A_A;
    LD_A_B;
    CALL_Z (aPlayVictoryMusic);
    CALLFAR(aBattle_GetTrainerName);
    LD_HL(mBattleText_EnemyWasDefeated);
    CALL(aStdBattleTextbox);

    CALL(aIsMobileBattle);
    IF_Z goto mobile;
    LD_A_addr(wLinkMode);
    AND_A_A;
    RET_NZ ;

    LD_A_addr(wInBattleTowerBattle);
    BIT_A(0);
    IF_NZ goto battle_tower;

    CALL(aBattleWinSlideInEnemyTrainerFrontpic);
    LD_C(40);
    CALL(aDelayFrames);

    LD_A_addr(wBattleType);
    CP_A(BATTLETYPE_CANLOSE);
    IF_NZ goto skip_heal;
    PREDEF(pHealParty);

skip_heal:

    LD_A_addr(wDebugFlags);
    BIT_A(DEBUG_BATTLE_F);
    IF_NZ goto skip_win_loss_text;
    CALL(aPrintWinLossText);

skip_win_loss_text:

    // JP(mWinTrainerBattle_give_money);
    goto give_money;


mobile:
    CALL(aBattleWinSlideInEnemyTrainerFrontpic);
    LD_C(40);
    CALL(aDelayFrames);
    LD_C(0x4);  // win
    FARCALL(aMobile_PrintOpponentBattleMessage);
    RET;


battle_tower:
    CALL(aBattleWinSlideInEnemyTrainerFrontpic);
    LD_C(40);
    CALL(aDelayFrames);
    CALL(aEmptyBattleTextbox);
    LD_C(BATTLETOWERTEXT_LOSS_TEXT);
    FARCALL(aBattleTowerText);
    CALL(aWaitPressAorB_BlinkCursor);
    LD_HL(wPayDayMoney);
    LD_A_hli;
    OR_A_hl;
    INC_HL;
    OR_A_hl;
    RET_NZ ;
    CALL(aClearTilemap);
    CALL(aClearBGPalettes);
    RET;


give_money:
    PEEK("give_money");
    LD_A_addr(wAmuletCoin);
    AND_A_A;
    CALL_NZ (aWinTrainerBattle_DoubleReward);
    CALL(aWinTrainerBattle_CheckMaxedOutMomMoney);
    PUSH_AF;
    LD_A(FALSE);
    IF_NC goto okay;
    LD_A_addr(wMomSavingMoney);
    AND_A(MOM_SAVING_MONEY_MASK);
    CP_A((1 << MOM_SAVING_SOME_MONEY_F) | (1 << MOM_SAVING_HALF_MONEY_F));
    IF_NZ goto okay;
    INC_A;  // TRUE


okay:
    LD_B_A;
    LD_C(4);

loop:
    LD_A_B;
    AND_A_A;
    IF_Z goto loop2;
    CALL(aWinTrainerBattle_AddMoneyToMom);
    DEC_C;
    DEC_B;
    goto loop;


loop2:
    LD_A_C;
    AND_A_A;
    IF_Z goto done;
    CALL(aWinTrainerBattle_AddMoneyToWallet);
    DEC_C;
    goto loop2;


done:
    CALL(aWinTrainerBattle_DoubleReward);
    CALL(aWinTrainerBattle_DoubleReward);
    POP_AF;
    IF_NC goto KeepItAll;
    LD_A_addr(wMomSavingMoney);
    AND_A(MOM_SAVING_MONEY_MASK);
    IF_Z goto KeepItAll;
    LD_HL(mWinTrainerBattle_SentToMomTexts);
    DEC_A;
    LD_C_A;
    LD_B(0);
    ADD_HL_BC;
    ADD_HL_BC;
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    JP(mStdBattleTextbox);


KeepItAll:
    PEEK("KeepItAll");
    LD_HL(mGotMoneyForWinningText);
    JP(mStdBattleTextbox);


AddMoneyToMom:
    PUSH_BC;
    LD_HL(wBattleReward + 2);
    LD_DE(wMomsMoney + 2);
    CALL(aAddBattleMoneyToAccount);
    POP_BC;
    RET;


AddMoneyToWallet:
    PUSH_BC;
    LD_HL(wBattleReward + 2);
    LD_DE(wMoney + 2);
    CALL(aAddBattleMoneyToAccount);
    POP_BC;
    RET;


DoubleReward:
    LD_HL(wBattleReward + 2);
    SLA_hl;
    DEC_HL;
    RL_hl;
    DEC_HL;
    RL_hl;
    RET_NC ;
    LD_A(0xff);
    LD_hli_A;
    LD_hli_A;
    LD_hl_A;
    RET;


SentToMomTexts:
//  entries correspond to MOM_SAVING_* constants
    //dw ['SentSomeToMomText'];
    //dw ['SentHalfToMomText'];
    //dw ['SentAllToMomText'];


CheckMaxedOutMomMoney:
    LD_HL(wMomsMoney + 2);
    LD_A_hld;
    CP_A(LOW(MAX_MONEY));
    LD_A_hld;
    SBC_A(HIGH(MAX_MONEY));  // mid
    LD_A_hl;
    SBC_A(HIGH(MAX_MONEY >> 8));
    RET;

}

void AddBattleMoneyToAccount(void){
    LD_C(3);
    AND_A_A;
    PUSH_DE;
    PUSH_HL;
    PUSH_BC;
    LD_B_H;
    LD_C_L;
    FARCALL(aStubbedTrainerRankings_AddToBattlePayouts);
    POP_BC;
    POP_HL;

loop:
    LD_A_de;
    ADC_A_hl;
    LD_de_A;
    DEC_DE;
    DEC_HL;
    DEC_C;
    IF_NZ goto loop;
    POP_HL;
    LD_A_hld;
    CP_A(LOW(MAX_MONEY));
    LD_A_hld;
    SBC_A(HIGH(MAX_MONEY));  // mid
    LD_A_hl;
    SBC_A(HIGH(MAX_MONEY >> 8));
    RET_C ;
    LD_hl(HIGH(MAX_MONEY >> 8));
    INC_HL;
    LD_hl(HIGH(MAX_MONEY));  // mid
    INC_HL;
    LD_hl(LOW(MAX_MONEY));
    RET;

}

void PlayVictoryMusic(void){
    PUSH_DE;
    LD_DE(MUSIC_NONE);
    CALL(aPlayMusic);
    CALL(aDelayFrame);
    LD_DE(MUSIC_WILD_VICTORY);
    LD_A_addr(wBattleMode);
    DEC_A;
    IF_NZ goto trainer_victory;
    PUSH_DE;
    CALL(aIsAnyMonHoldingExpShare);
    POP_DE;
    IF_NZ goto play_music;
    LD_HL(wPayDayMoney);
    LD_A_hli;
    OR_A_hl;
    IF_NZ goto play_music;
    LD_A_addr(wBattleParticipantsNotFainted);
    AND_A_A;
    IF_Z goto lost;
    goto play_music;


trainer_victory:
    LD_DE(MUSIC_GYM_VICTORY);
    CALL(aIsGymLeader);
    IF_C goto play_music;
    LD_DE(MUSIC_TRAINER_VICTORY);


play_music:
    CALL(aPlayMusic);


lost:
    POP_DE;
    RET;

}

void IsKantoGymLeader(void){
    LD_HL(mKantoGymLeaders);
    JR(mIsGymLeaderCommon);

}

bool IsKantoGymLeader_Conv(uint8_t a){
    // LD_HL(mKantoGymLeaders);
    // JR(mIsGymLeaderCommon);
    for(uint8_t i = 0; KantoGymLeaders[i] != 0xff; ++i) {
        if(a == KantoGymLeaders[i])
            return true;
    }
    return false;
}

void IsGymLeader(void){
    LD_HL(mGymLeaders);
    return IsGymLeaderCommon();
}

bool IsGymLeader_Conv(uint8_t a){
    // LD_HL(mGymLeaders);
    // JR(mIsGymLeaderCommon);
    for(uint8_t i = 0; GymLeaders[i] != 0xff; ++i) {
        if(a == GymLeaders[i])
            return true;
    }
    return false;
}

void IsGymLeaderCommon(void){
    PUSH_DE;
    LD_A_addr(wOtherTrainerClass);
    LD_DE(1);
    CALL(aIsInArray);
    POP_DE;
    RET;

// INCLUDE "data/trainers/leaders.asm"

    return HandlePlayerMonFaint();
}

void HandlePlayerMonFaint(void){
    CALL(aFaintYourPokemon);
    LD_HL(wEnemyMonHP);
    LD_A_hli;
    OR_A_hl;
    CALL_Z (aFaintEnemyPokemon);
    LD_A(0x1);
    LD_addr_A(wWhichMonFaintedFirst);
    CALL(aUpdateFaintedPlayerMon);
    CALL(aCheckPlayerPartyForFitMon);
    LD_A_D;
    AND_A_A;
    JP_Z (mLostBattle);
    LD_HL(wEnemyMonHP);
    LD_A_hli;
    OR_A_hl;
    IF_NZ goto notfainted;
    CALL(aUpdateBattleStateAndExperienceAfterEnemyFaint);
    LD_A_addr(wBattleMode);
    DEC_A;
    IF_NZ goto trainer;
    LD_A(0x1);
    LD_addr_A(wBattleEnded);
    RET;


trainer:
    CALL(aCheckEnemyTrainerDefeated);
    JP_Z (mWinTrainerBattle);


notfainted:
    CALL(aAskUseNextPokemon);
    IF_NC goto switch_;
    LD_A(0x1);
    LD_addr_A(wBattleEnded);
    RET;


switch_:
    CALL(aForcePlayerMonChoice);
    CALL(aCheckMobileBattleError);
    JP_C (mWildFled_EnemyFled_LinkBattleCanceled);
    LD_A_C;
    AND_A_A;
    RET_NZ ;
    LD_A(BATTLEPLAYERACTION_USEITEM);
    LD_addr_A(wBattlePlayerAction);
    CALL(aHandleEnemySwitch);
    JP_Z (mWildFled_EnemyFled_LinkBattleCanceled);
    JP(mDoubleSwitch);

}

void UpdateFaintedPlayerMon(void){
    LD_A_addr(wCurBattleMon);
    LD_C_A;
    LD_HL(wBattleParticipantsNotFainted);
    LD_B(RESET_FLAG);
    PREDEF(pSmallFarFlagAction);
    LD_HL(wEnemySubStatus3);
    RES_hl(SUBSTATUS_IN_LOOP);
    XOR_A_A;
    LD_addr_A(wLowHealthAlarm);
    LD_HL(wPlayerDamageTaken);
    LD_hli_A;
    LD_hl_A;
    LD_addr_A(wBattleMonStatus);
    CALL(aUpdateBattleMonInParty);
    LD_C(HAPPINESS_FAINTED);
// If TheirLevel > (YourLevel + 30), use a different parameter
    LD_A_addr(wBattleMonLevel);
    ADD_A(30);
    LD_B_A;
    LD_A_addr(wEnemyMonLevel);
    CP_A_B;
    IF_C goto got_param;
    LD_C(HAPPINESS_BEATENBYSTRONGFOE);


got_param:
    LD_A_addr(wCurBattleMon);
    LD_addr_A(wCurPartyMon);
    CALLFAR(aChangeHappiness);
    LD_A_addr(wBattleResult);
    AND_A(BATTLERESULT_BITMASK);
    ADD_A(LOSE);
    LD_addr_A(wBattleResult);
    LD_A_addr(wWhichMonFaintedFirst);
    AND_A_A;
    RET_Z ;
// code was probably dummied out here
    RET;

}

void AskUseNextPokemon(void){
    CALL(aEmptyBattleTextbox);
    CALL(aLoadTilemapToTempTilemap);
//  We don't need to be here if we're in a Trainer battle,
//  as that decision is made for us.
    LD_A_addr(wBattleMode);
    AND_A_A;
    DEC_A;
    RET_NZ ;

    LD_HL(mBattleText_UseNextMon);
    CALL(aStdBattleTextbox);

loop:
    LD_BC((1 << 8) | 7);
    CALL(aPlaceYesNoBox);
    LD_A_addr(wMenuCursorY);
    IF_C goto pressed_b;
    AND_A_A;
    RET;


pressed_b:
    LD_A_addr(wMenuCursorY);
    CP_A(0x1);  // YES
    IF_Z goto loop;
    LD_HL(wPartyMon1Speed);
    LD_DE(wEnemyMonSpeed);
    JP(mTryToRunAwayFromBattle);

}

void ForcePlayerMonChoice(void){
    CALL(aEmptyBattleTextbox);
    CALL(aLoadStandardMenuHeader);
    CALL(aSetUpBattlePartyMenu);
    CALL(aForcePickPartyMonInBattle);
    LD_A_addr(wLinkMode);
    AND_A_A;
    IF_Z goto skip_link;
    LD_A(BATTLEPLAYERACTION_USEITEM);
    LD_addr_A(wBattlePlayerAction);
    CALL(aLinkBattleSendReceiveAction);


skip_link:
    XOR_A_A;  // BATTLEPLAYERACTION_USEMOVE
    LD_addr_A(wBattlePlayerAction);
    CALL(aCheckMobileBattleError);
    IF_C goto enemy_fainted_mobile_error;
    LD_HL(wEnemyMonHP);
    LD_A_hli;
    OR_A_hl;
    IF_NZ goto send_out_pokemon;


enemy_fainted_mobile_error:
    CALL(aClearSprites);
    CALL(aClearBGPalettes);
    CALL(av_LoadHPBar);
    CALL(aExitMenu);
    CALL(aLoadTilemapToTempTilemap);
    CALL(aWaitBGMap);
    CALL(aGetMemSGBLayout);
    CALL(aSetPalettes);
    XOR_A_A;
    LD_C_A;
    RET;


send_out_pokemon:
    CALL(aClearSprites);
    LD_A_addr(wCurBattleMon);
    LD_addr_A(wLastPlayerMon);
    LD_A_addr(wCurPartyMon);
    LD_addr_A(wCurBattleMon);
    CALL(aAddBattleParticipant);
    CALL(aInitBattleMon);
    CALL(aResetPlayerStatLevels);
    CALL(aClearPalettes);
    CALL(aDelayFrame);
    CALL(av_LoadHPBar);
    CALL(aCloseWindow);
    CALL(aGetMemSGBLayout);
    CALL(aSetPalettes);
    CALL(aSendOutMonText);
    CALL(aNewBattleMonStatus);
    CALL(aBreakAttraction);
    CALL(aSendOutPlayerMon);
    CALL(aEmptyBattleTextbox);
    CALL(aLoadTilemapToTempTilemap);
    CALL(aSetPlayerTurn);
    CALL(aSpikesDamage);
    LD_A(0x1);
    AND_A_A;
    LD_C_A;
    RET;

}

void PlayerPartyMonEntrance(void){
    LD_A_addr(wCurBattleMon);
    LD_addr_A(wLastPlayerMon);
    LD_A_addr(wCurPartyMon);
    LD_addr_A(wCurBattleMon);
    CALL(aAddBattleParticipant);
    CALL(aInitBattleMon);
    CALL(aResetPlayerStatLevels);
    CALL(aSendOutMonText);
    CALL(aNewBattleMonStatus);
    CALL(aBreakAttraction);
    CALL(aSendOutPlayerMon);
    CALL(aEmptyBattleTextbox);
    CALL(aLoadTilemapToTempTilemap);
    CALL(aSetPlayerTurn);
    JP(mSpikesDamage);

}

void CheckMobileBattleError(void){
    LD_A_addr(wLinkMode);
    CP_A(LINK_MOBILE);
    IF_NZ goto not_mobile;  // It's not a mobile battle

    LD_A_addr(wcd2b);
    AND_A_A;
    IF_Z goto not_mobile;

//  We have a mobile battle and something else happened
    SCF;
    RET;


not_mobile:
    XOR_A_A;
    RET;

}

void IsMobileBattle(void){
    LD_A_addr(wLinkMode);
    CP_A(LINK_MOBILE);
    RET;

}

void SetUpBattlePartyMenu(void){
    CALL(aClearBGPalettes);
    return SetUpBattlePartyMenu_Loop();
}

void SetUpBattlePartyMenu_Loop(void){
//  //  switch to fullscreen menu?
    FARCALL(aLoadPartyMenuGFX);
    FARCALL(aInitPartyMenuWithCancel);
    FARCALL(aInitPartyMenuBGPal7);
    FARCALL(aInitPartyMenuGFX);
    RET;

}

void JumpToPartyMenuAndPrintText(void){
    FARCALL(aWritePartyMenuTilemap);
    FARCALL(aPrintPartyMenuText);
    CALL(aWaitBGMap);
    CALL(aSetPalettes);
    CALL(aDelayFrame);
    RET;

}

void SelectBattleMon(void){
    CALL(aIsMobileBattle);
    IF_Z goto mobile;
    FARCALL(aPartyMenuSelect);
    RET;


mobile:
    FARCALL(aMobile_PartyMenuSelect);
    RET;

}

void PickPartyMonInBattle(void){

loop:
    LD_A(PARTYMENUACTION_SWITCH);  // Which PKMN?
    LD_addr_A(wPartyMenuActionText);
    CALL(aJumpToPartyMenuAndPrintText);
    CALL(aSelectBattleMon);
    RET_C ;
    CALL(aCheckIfCurPartyMonIsFitToFight);
    IF_Z goto loop;
    XOR_A_A;
    RET;

}

void SwitchMonAlreadyOut(void){
    LD_HL(wCurBattleMon);
    LD_A_addr(wCurPartyMon);
    CP_A_hl;
    IF_NZ goto notout;

    LD_HL(mBattleText_MonIsAlreadyOut);
    CALL(aStdBattleTextbox);
    SCF;
    RET;


notout:
    XOR_A_A;
    RET;

}

void ForcePickPartyMonInBattle(void){
//  Can't back out.


pick:
    CALL(aPickPartyMonInBattle);
    RET_NC ;
    CALL(aCheckMobileBattleError);
    RET_C ;

    LD_DE(SFX_WRONG);
    CALL(aPlaySFX);
    CALL(aWaitSFX);
    goto pick;

    return PickSwitchMonInBattle();
}

void PickSwitchMonInBattle(void){

pick:
    CALL(aPickPartyMonInBattle);
    RET_C ;
    CALL(aSwitchMonAlreadyOut);
    IF_C goto pick;
    XOR_A_A;
    RET;

}

void ForcePickSwitchMonInBattle(void){
//  Can't back out.


pick:
    CALL(aForcePickPartyMonInBattle);
    CALL(aCheckMobileBattleError);
    RET_C ;
    CALL(aSwitchMonAlreadyOut);
    IF_C goto pick;

    XOR_A_A;
    RET;

}

void LostBattle(void){
    LD_A(1);
    LD_addr_A(wBattleEnded);

    LD_A_addr(wInBattleTowerBattle);
    BIT_A(0);
    IF_NZ goto battle_tower;

    LD_A_addr(wBattleType);
    CP_A(BATTLETYPE_CANLOSE);
    IF_NZ goto not_canlose;

//  Remove the enemy from the screen.
    hlcoord(0, 0, wTilemap);
    LD_BC((8 << 8) | 21);
    CALL(aClearBox);
    CALL(aBattleWinSlideInEnemyTrainerFrontpic);

    LD_C(40);
    CALL(aDelayFrames);

    LD_A_addr(wDebugFlags);
    BIT_A(DEBUG_BATTLE_F);
    IF_NZ goto skip_win_loss_text;
    CALL(aPrintWinLossText);

skip_win_loss_text:
    RET;


battle_tower:
//  Remove the enemy from the screen.
    hlcoord(0, 0, wTilemap);
    LD_BC((8 << 8) | 21);
    CALL(aClearBox);
    CALL(aBattleWinSlideInEnemyTrainerFrontpic);

    LD_C(40);
    CALL(aDelayFrames);

    CALL(aEmptyBattleTextbox);
    LD_C(BATTLETOWERTEXT_WIN_TEXT);
    FARCALL(aBattleTowerText);
    CALL(aWaitPressAorB_BlinkCursor);
    CALL(aClearTilemap);
    CALL(aClearBGPalettes);
    RET;


not_canlose:
    LD_A_addr(wLinkMode);
    AND_A_A;
    IF_NZ goto LostLinkBattle;

//  Grayscale
    LD_B(SCGB_BATTLE_GRAYSCALE);
    CALL(aGetSGBLayout);
    CALL(aSetPalettes);
    goto end;


LostLinkBattle:
    CALL(aUpdateEnemyMonInParty);
    CALL(aCheckEnemyTrainerDefeated);
    IF_NZ goto not_tied;
    LD_HL(mTiedAgainstText);
    LD_A_addr(wBattleResult);
    AND_A(BATTLERESULT_BITMASK);
    ADD_A(DRAW);
    LD_addr_A(wBattleResult);
    goto text;


not_tied:
    LD_HL(mLostAgainstText);
    CALL(aIsMobileBattle);
    IF_Z goto mobile;


text:
    CALL(aStdBattleTextbox);


end:
    SCF;
    RET;


mobile:
//  Remove the enemy from the screen.
    hlcoord(0, 0, wTilemap);
    LD_BC((8 << 8) | 21);
    CALL(aClearBox);
    CALL(aBattleWinSlideInEnemyTrainerFrontpic);

    LD_C(40);
    CALL(aDelayFrames);

    LD_C(0x3);  // lost
    FARCALL(aMobile_PrintOpponentBattleMessage);
    SCF;
    RET;

}

void EnemyMonFaintedAnimation(void){
    hlcoord(12, 5, wTilemap);
    decoord(12, 6, wTilemap);
    JP(mMonFaintedAnimation);

}

void PlayerMonFaintedAnimation(void){
    hlcoord(1, 10, wTilemap);
    decoord(1, 11, wTilemap);
    JP(mMonFaintedAnimation);

}

void MonFaintedAnimation(void){
    LD_A_addr(wJoypadDisable);
    PUSH_AF;
    SET_A(JOYPAD_DISABLE_MON_FAINT_F);
    LD_addr_A(wJoypadDisable);

    LD_B(7);


OuterLoop:
    PUSH_BC;
    PUSH_DE;
    PUSH_HL;
    LD_B(6);


InnerLoop:
    PUSH_BC;
    PUSH_HL;
    PUSH_DE;
    LD_BC(7);
    CALL(aCopyBytes);
    POP_DE;
    POP_HL;
    LD_BC(-SCREEN_WIDTH);
    ADD_HL_BC;
    PUSH_HL;
    LD_H_D;
    LD_L_E;
    ADD_HL_BC;
    LD_D_H;
    LD_E_L;
    POP_HL;
    POP_BC;
    DEC_B;
    IF_NZ goto InnerLoop;

    LD_BC(20);
    ADD_HL_BC;
    LD_DE(mMonFaintedAnimation_Spaces);
    CALL(aPlaceString);
    LD_C(2);
    CALL(aDelayFrames);
    POP_HL;
    POP_DE;
    POP_BC;
    DEC_B;
    IF_NZ goto OuterLoop;

    POP_AF;
    LD_addr_A(wJoypadDisable);
    RET;


Spaces:
    //db ['"\t   @"'];

    return SlideBattlePicOut();
}

void SlideBattlePicOut(void){
    LDH_addr_A(hMapObjectIndex);
    LD_C_A;

loop:
    PUSH_BC;
    PUSH_HL;
    LD_B(0x7);

loop2:
    PUSH_HL;
    CALL(aSlideBattlePicOut_DoFrame);
    POP_HL;
    LD_DE(SCREEN_WIDTH);
    ADD_HL_DE;
    DEC_B;
    IF_NZ goto loop2;
    LD_C(2);
    CALL(aDelayFrames);
    POP_HL;
    POP_BC;
    DEC_C;
    IF_NZ goto loop;
    RET;


DoFrame:
    LDH_A_addr(hMapObjectIndex);
    LD_C_A;
    CP_A(0x8);
    IF_NZ goto back;

forward:
    LD_A_hli;
    LD_hld_A;
    DEC_HL;
    DEC_C;
    IF_NZ goto forward;
    RET;


back:
    LD_A_hld;
    LD_hli_A;
    INC_HL;
    DEC_C;
    IF_NZ goto back;
    RET;

}

void ForceEnemySwitch(void){
    CALL(aResetEnemyBattleVars);
    LD_A_addr(wEnemySwitchMonIndex);
    DEC_A;
    LD_B_A;
    CALL(aLoadEnemyMonToSwitchTo);
    CALL(aClearEnemyMonBox);
    CALL(aNewEnemyMonStatus);
    CALL(aResetEnemyStatLevels);
    CALL(aShowSetEnemyMonAndSendOutAnimation);
    CALL(aBreakAttraction);
    CALL(aResetBattleParticipants);
    RET;

}

void EnemySwitch(void){
    CALL(aCheckWhetherToAskSwitch);
    JR_NC (mEnemySwitch_SetMode);
// Shift Mode
    CALL(aResetEnemyBattleVars);
    CALL(aCheckWhetherSwitchmonIsPredetermined);
    IF_C goto skip;
    CALL(aFindMonInOTPartyToSwitchIntoBattle);

skip:
// 'b' contains the PartyNr of the mon the AI will switch to
    CALL(aLoadEnemyMonToSwitchTo);
    CALL(aOfferSwitch);
    PUSH_AF;
    CALL(aClearEnemyMonBox);
    CALL(aShowBattleTextEnemySentOut);
    CALL(aShowSetEnemyMonAndSendOutAnimation);
    POP_AF;
    RET_C ;
// If we're here, then we're switching too
    XOR_A_A;
    LD_addr_A(wBattleParticipantsNotFainted);
    LD_addr_A(wBattleParticipantsIncludingFainted);
    LD_addr_A(wBattlePlayerAction);
    INC_A;
    LD_addr_A(wEnemyIsSwitching);
    CALL(aLoadTilemapToTempTilemap);
    JP(mPlayerSwitch);

}

void EnemySwitch_SetMode(void){
    CALL(aResetEnemyBattleVars);
    CALL(aCheckWhetherSwitchmonIsPredetermined);
    IF_C goto skip;
    CALL(aFindMonInOTPartyToSwitchIntoBattle);

skip:
// 'b' contains the PartyNr of the mon the AI will switch to
    CALL(aLoadEnemyMonToSwitchTo);
    LD_A(1);
    LD_addr_A(wEnemyIsSwitching);
    CALL(aClearEnemyMonBox);
    CALL(aShowBattleTextEnemySentOut);
    JP(mShowSetEnemyMonAndSendOutAnimation);

}

void CheckWhetherSwitchmonIsPredetermined(void){
//  returns the enemy switchmon index in b, or
//  returns carry if the index is not yet determined.
    LD_A_addr(wLinkMode);
    AND_A_A;
    IF_Z goto not_linked;

    LD_A_addr(wBattleAction);
    SUB_A(BATTLEACTION_SWITCH1);
    LD_B_A;
    goto return_carry;


not_linked:
    LD_A_addr(wEnemySwitchMonIndex);
    AND_A_A;
    IF_Z goto check_wBattleHasJustStarted;

    DEC_A;
    LD_B_A;
    goto return_carry;


check_wBattleHasJustStarted:
    LD_A_addr(wBattleHasJustStarted);
    AND_A_A;
    LD_B(0);
    IF_NZ goto return_carry;

    AND_A_A;
    RET;


return_carry:
    SCF;
    RET;

}

void ResetEnemyBattleVars(void){
//  and draw empty Textbox
    XOR_A_A;
    LD_addr_A(wLastPlayerCounterMove);
    LD_addr_A(wLastEnemyCounterMove);
    LD_addr_A(wLastEnemyMove);
    LD_addr_A(wCurEnemyMove);
    DEC_A;
    LD_addr_A(wEnemyItemState);
    XOR_A_A;
    LD_addr_A(wPlayerWrapCount);
    hlcoord(18, 0, wTilemap);
    LD_A(8);
    CALL(aSlideBattlePicOut);
    CALL(aEmptyBattleTextbox);
    JP(mLoadStandardMenuHeader);

}

void ResetBattleParticipants(void){
    XOR_A_A;
    LD_addr_A(wBattleParticipantsNotFainted);
    LD_addr_A(wBattleParticipantsIncludingFainted);
    return AddBattleParticipant();
}

void AddBattleParticipant(void){
    LD_A_addr(wCurBattleMon);
    LD_C_A;
    LD_HL(wBattleParticipantsNotFainted);
    LD_B(SET_FLAG);
    PUSH_BC;
    PREDEF(pSmallFarFlagAction);
    POP_BC;
    LD_HL(wBattleParticipantsIncludingFainted);
    PREDEF_JUMP(pSmallFarFlagAction);

    return FindMonInOTPartyToSwitchIntoBattle();
}

void FindMonInOTPartyToSwitchIntoBattle(void){
    LD_B(-1);
    LD_A(0b000001);
    LD_addr_A(wEnemyEffectivenessVsPlayerMons);
    LD_addr_A(wPlayerEffectivenessVsEnemyMons);

loop:
    LD_HL(wEnemyEffectivenessVsPlayerMons);
    SLA_hl;
    INC_HL;  // wPlayerEffectivenessVsEnemyMons
    SLA_hl;
    INC_B;
    LD_A_addr(wOTPartyCount);
    CP_A_B;
    JP_Z (mScoreMonTypeMatchups);
    LD_A_addr(wCurOTMon);
    CP_A_B;
    IF_Z goto discourage;
    LD_HL(wOTPartyMon1HP);
    PUSH_BC;
    LD_A_B;
    CALL(aGetPartyLocation);
    LD_A_hli;
    LD_C_A;
    LD_A_hl;
    OR_A_C;
    POP_BC;
    IF_Z goto discourage;
    CALL(aLookUpTheEffectivenessOfEveryMove);
    CALL(aIsThePlayerMonTypesEffectiveAgainstOTMon);
    goto loop;


discourage:
    LD_HL(wPlayerEffectivenessVsEnemyMons);
    SET_hl(0);
    goto loop;

    return LookUpTheEffectivenessOfEveryMove();
}

void LookUpTheEffectivenessOfEveryMove(void){
    PUSH_BC;
    LD_HL(wOTPartyMon1Moves);
    LD_A_B;
    CALL(aGetPartyLocation);
    POP_BC;
    LD_E(NUM_MOVES + 1);

loop:
    DEC_E;
    IF_Z goto done;
    LD_A_hli;
    AND_A_A;
    IF_Z goto done;
    PUSH_HL;
    PUSH_DE;
    PUSH_BC;
    DEC_A;
    LD_HL(mMoves);
    LD_BC(MOVE_LENGTH);
    CALL(aAddNTimes);
    LD_DE(wEnemyMoveStruct);
    LD_A(BANK(aMoves));
    CALL(aFarCopyBytes);
    CALL(aSetEnemyTurn);
    CALLFAR(aBattleCheckTypeMatchup);
    POP_BC;
    POP_DE;
    POP_HL;
    LD_A_addr(wTypeMatchup);
    CP_A(EFFECTIVE + 1);
    IF_C goto loop;
    LD_HL(wEnemyEffectivenessVsPlayerMons);
    SET_hl(0);
    RET;

done:
    RET;

}

void IsThePlayerMonTypesEffectiveAgainstOTMon(void){
//  Calculates the effectiveness of the types of the PlayerMon
//  against the OTMon
    PUSH_BC;
    LD_HL(wOTPartyCount);
    LD_A_B;
    INC_A;
    LD_C_A;
    LD_B(0);
    ADD_HL_BC;
    LD_A_hl;
    DEC_A;
    LD_HL(mBaseData + BASE_TYPES);
    LD_BC(BASE_DATA_SIZE);
    CALL(aAddNTimes);
    LD_DE(wEnemyMonType);
    LD_BC(BASE_CATCH_RATE - BASE_TYPES);
    LD_A(BANK(aBaseData));
    CALL(aFarCopyBytes);
    LD_A_addr(wBattleMonType1);
    LD_addr_A(wPlayerMoveStruct + MOVE_TYPE);
    CALL(aSetPlayerTurn);
    CALLFAR(aBattleCheckTypeMatchup);
    LD_A_addr(wTypeMatchup);
    CP_A(EFFECTIVE + 1);
    IF_NC goto super_effective;
    LD_A_addr(wBattleMonType2);
    LD_addr_A(wPlayerMoveStruct + MOVE_TYPE);
    CALLFAR(aBattleCheckTypeMatchup);
    LD_A_addr(wTypeMatchup);
    CP_A(EFFECTIVE + 1);
    IF_NC goto super_effective;
    POP_BC;
    RET;


super_effective:
    POP_BC;
    LD_HL(wEnemyEffectivenessVsPlayerMons);
    BIT_hl(0);
    IF_NZ goto reset;
    INC_HL;  // wPlayerEffectivenessVsEnemyMons
    SET_hl(0);
    RET;


reset:
    RES_hl(0);
    RET;

}

void ScoreMonTypeMatchups(void){

loop1:
    LD_HL(wEnemyEffectivenessVsPlayerMons);
    SLA_hl;
    INC_HL;  // wPlayerEffectivenessVsEnemyMons
    SLA_hl;
    IF_NC goto loop1;
    LD_A_addr(wOTPartyCount);
    LD_B_A;
    LD_C_hl;

loop2:
    SLA_C;
    IF_NC goto okay;
    DEC_B;
    IF_Z goto loop5;
    goto loop2;


okay:
    LD_A_addr(wEnemyEffectivenessVsPlayerMons);
    AND_A_A;
    IF_Z goto okay2;
    LD_B(-1);
    LD_C_A;

loop3:
    INC_B;
    SLA_C;
    IF_NC goto loop3;
    goto quit;


okay2:
    LD_B(-1);
    LD_A_addr(wPlayerEffectivenessVsEnemyMons);
    LD_C_A;

loop4:
    INC_B;
    SLA_C;
    IF_C goto loop4;
    goto quit;


loop5:
    LD_A_addr(wOTPartyCount);
    LD_B_A;
    CALL(aBattleRandom);
    AND_A(0x7);
    CP_A_B;
    IF_NC goto loop5;
    LD_B_A;
    LD_A_addr(wCurOTMon);
    CP_A_B;
    IF_Z goto loop5;
    LD_HL(wOTPartyMon1HP);
    PUSH_BC;
    LD_A_B;
    CALL(aGetPartyLocation);
    POP_BC;
    LD_A_hli;
    LD_C_A;
    LD_A_hl;
    OR_A_C;
    IF_Z goto loop5;


quit:
    RET;

}

void LoadEnemyMonToSwitchTo(void){
// 'b' contains the PartyNr of the mon the AI will switch to
    LD_A_B;
    LD_addr_A(wCurPartyMon);
    LD_HL(wOTPartyMon1Level);
    CALL(aGetPartyLocation);
    LD_A_hl;
    LD_addr_A(wCurPartyLevel);
    LD_A_addr(wCurPartyMon);
    INC_A;
    LD_HL(wOTPartyCount);
    LD_C_A;
    LD_B(0);
    ADD_HL_BC;
    LD_A_hl;
    LD_addr_A(wTempEnemyMonSpecies);
    LD_addr_A(wCurPartySpecies);
    CALL(aLoadEnemyMon);

    LD_A_addr(wCurPartySpecies);
    CP_A(UNOWN);
    IF_NZ goto skip_unown;
    LD_A_addr(wFirstUnownSeen);
    AND_A_A;
    IF_NZ goto skip_unown;
    LD_HL(wEnemyMonDVs);
    PREDEF(pGetUnownLetter);
    LD_A_addr(wUnownLetter);
    LD_addr_A(wFirstUnownSeen);

skip_unown:

    LD_HL(wEnemyMonHP);
    LD_A_hli;
    LD_addr_A(wEnemyHPAtTimeOfPlayerSwitch);
    LD_A_hl;
    LD_addr_A(wEnemyHPAtTimeOfPlayerSwitch + 1);
    RET;

}

void CheckWhetherToAskSwitch(void){
    LD_A_addr(wBattleHasJustStarted);
    DEC_A;
    JP_Z (mCheckWhetherToAskSwitch_return_nc);
    LD_A_addr(wPartyCount);
    DEC_A;
    JP_Z (mCheckWhetherToAskSwitch_return_nc);
    LD_A_addr(wLinkMode);
    AND_A_A;
    JP_NZ (mCheckWhetherToAskSwitch_return_nc);
    LD_A_addr(wOptions);
    BIT_A(BATTLE_SHIFT);
    IF_NZ goto return_nc;
    LD_A_addr(wCurPartyMon);
    PUSH_AF;
    LD_A_addr(wCurBattleMon);
    LD_addr_A(wCurPartyMon);
    FARCALL(aCheckCurPartyMonFainted);
    POP_BC;
    LD_A_B;
    LD_addr_A(wCurPartyMon);
    IF_C goto return_nc;
    SCF;
    RET;


return_nc:
    AND_A_A;
    RET;

}

void OfferSwitch(void){
    LD_A_addr(wCurPartyMon);
    PUSH_AF;
    CALLFAR(aBattle_GetTrainerName);
    LD_HL(mBattleText_EnemyIsAboutToUseWillPlayerChangeMon);
    CALL(aStdBattleTextbox);
    LD_BC((1 << 8) | 7);
    CALL(aPlaceYesNoBox);
    LD_A_addr(wMenuCursorY);
    DEC_A;
    IF_NZ goto said_no;
    CALL(aSetUpBattlePartyMenu);
    CALL(aPickSwitchMonInBattle);
    IF_C goto canceled_switch;
    LD_A_addr(wCurBattleMon);
    LD_addr_A(wLastPlayerMon);
    LD_A_addr(wCurPartyMon);
    LD_addr_A(wCurBattleMon);
    CALL(aClearPalettes);
    CALL(aDelayFrame);
    CALL(av_LoadHPBar);
    POP_AF;
    LD_addr_A(wCurPartyMon);
    XOR_A_A;
    LD_addr_A(wCurEnemyMove);
    LD_addr_A(wCurPlayerMove);
    AND_A_A;
    RET;


canceled_switch:
    CALL(aClearPalettes);
    CALL(aDelayFrame);
    CALL(av_LoadHPBar);


said_no:
    POP_AF;
    LD_addr_A(wCurPartyMon);
    SCF;
    RET;

}

void ClearEnemyMonBox(void){
    XOR_A_A;
    LDH_addr_A(hBGMapMode);
    CALL(aExitMenu);
    CALL(aClearSprites);
    hlcoord(1, 0, wTilemap);
    LD_BC((4 << 8) | 10);
    CALL(aClearBox);
    CALL(aWaitBGMap);
    JP(mFinishBattleAnim);

}

void ShowBattleTextEnemySentOut(void){
    PEEK("");
    CALLFAR(aBattle_GetTrainerName);
    LD_HL(mBattleText_EnemySentOut);
    CALL(aStdBattleTextbox);
    JP(mWaitBGMap);

}

void ShowSetEnemyMonAndSendOutAnimation(void){
    PEEK("");
    LD_A_addr(wTempEnemyMonSpecies);
    LD_addr_A(wCurPartySpecies);
    LD_addr_A(wCurSpecies);
    CALL(aGetBaseData);
    LD_A(OTPARTYMON);
    LD_addr_A(wMonType);
    PREDEF(pCopyMonToTempMon);
    CALL(aGetEnemyMonFrontpic);

    XOR_A_A;
    LD_addr_A(wNumHits);
    LD_addr_A(wBattleAnimParam);
    CALL(aSetEnemyTurn);
    LD_DE(ANIM_SEND_OUT_MON);
    CALL(aCall_PlayBattleAnim);

    CALL(aBattleCheckEnemyShininess);
    IF_NC goto not_shiny;

    LD_A(1);  // shiny anim
    LD_addr_A(wBattleAnimParam);
    LD_DE(ANIM_SEND_OUT_MON);
    CALL(aCall_PlayBattleAnim);


not_shiny:
    LD_BC(wTempMonSpecies);
    FARCALL(aCheckFaintedFrzSlp);
    IF_C goto skip_cry;

    FARCALL(aCheckBattleScene);
    IF_C goto cry_no_anim;

    // hlcoord(12, 0, wTilemap);
    // LD_D(0x0);
    // LD_E(ANIM_MON_SLOW);
    // PREDEF(pAnimateFrontpic);
    AnimateFrontpic_Conv(coord(12, 0, wram->wTilemap), 0x0, ANIM_MON_SLOW);
    goto skip_cry;


cry_no_anim:
    LD_A(0xf);
    LD_addr_A(wCryTracks);
    LD_A_addr(wTempEnemyMonSpecies);
    CALL(aPlayStereoCry);


skip_cry:
    CALL(aUpdateEnemyHUD);
    LD_A(0x1);
    LDH_addr_A(hBGMapMode);
    RET;

}

void NewEnemyMonStatus(void){
    XOR_A_A;
    LD_addr_A(wLastPlayerCounterMove);
    LD_addr_A(wLastEnemyCounterMove);
    LD_addr_A(wLastEnemyMove);
    LD_HL(wEnemySubStatus1);
    for(int rept = 0; rept < 4; rept++){
    LD_hli_A;
    }
    LD_hl_A;
    LD_addr_A(wEnemyDisableCount);
    LD_addr_A(wEnemyFuryCutterCount);
    LD_addr_A(wEnemyProtectCount);
    LD_addr_A(wEnemyRageCounter);
    LD_addr_A(wEnemyDisabledMove);
    LD_addr_A(wEnemyMinimized);
    LD_addr_A(wPlayerWrapCount);
    LD_addr_A(wEnemyWrapCount);
    LD_addr_A(wEnemyTurnsTaken);
    LD_HL(wPlayerSubStatus5);
    RES_hl(SUBSTATUS_CANT_RUN);
    RET;

}

void NewEnemyMonStatus_Conv(void){
    // XOR_A_A;
    // LD_addr_A(wLastPlayerCounterMove);
    wram->wLastPlayerCounterMove = NO_MOVE;
    // LD_addr_A(wLastEnemyCounterMove);
    wram->wLastEnemyCounterMove = NO_MOVE;
    // LD_addr_A(wLastEnemyMove);
    wram->wLastEnemyMove = NO_MOVE;
    // LD_HL(wEnemySubStatus1);
    // for(int rept = 0; rept < 4; rept++){
    // LD_hli_A;
    // }
    wram->wEnemySubStatus1 = 0;
    wram->wEnemySubStatus2 = 0;
    wram->wEnemySubStatus3 = 0;
    wram->wEnemySubStatus4 = 0;
    // LD_hl_A;
    wram->wEnemySubStatus5 = 0;
    // LD_addr_A(wEnemyDisableCount);
    wram->wEnemyDisableCount = 0;
    // LD_addr_A(wEnemyFuryCutterCount);
    wram->wEnemyFuryCutterCount = 0;
    // LD_addr_A(wEnemyProtectCount);
    wram->wEnemyProtectCount = 0;
    // LD_addr_A(wEnemyRageCounter);
    wram->wEnemyRageCounter = 0;
    // LD_addr_A(wEnemyDisabledMove);
    wram->wEnemyDisabledMove = NO_MOVE;
    // LD_addr_A(wEnemyMinimized);
    wram->wEnemyMinimized = FALSE;
    // LD_addr_A(wPlayerWrapCount);
    wram->wPlayerWrapCount = 0;
    // LD_addr_A(wEnemyWrapCount);
    wram->wEnemyWrapCount = 0;
    // LD_addr_A(wEnemyTurnsTaken);
    wram->wEnemyTurnsTaken = 0;
    // LD_HL(wPlayerSubStatus5);
    // RES_hl(SUBSTATUS_CANT_RUN);
    bit_reset(wram->wPlayerSubStatus5, SUBSTATUS_CANT_RUN);
    // RET;
}

void ResetEnemyStatLevels(void){
    LD_A(BASE_STAT_LEVEL);
    LD_B(NUM_LEVEL_STATS);
    LD_HL(wEnemyStatLevels);

loop:
    LD_hli_A;
    DEC_B;
    IF_NZ goto loop;
    RET;

}

void ResetEnemyStatLevels_Conv(void){
    // LD_A(BASE_STAT_LEVEL);
    // LD_B(NUM_LEVEL_STATS);
    // LD_HL(wEnemyStatLevels);

    for(int i = 0; i < NUM_LEVEL_STATS; ++i) {
    // loop:
        // LD_hli_A;
        // DEC_B;
        // IF_NZ goto loop;
        wram->wEnemyStatLevels[i] = BASE_STAT_LEVEL;
    }
    // RET;
}

void CheckPlayerPartyForFitMon(void){
//  Has the player any mon in his Party that can fight?
    LD_A_addr(wPartyCount);
    LD_E_A;
    XOR_A_A;
    LD_HL(wPartyMon1HP);
    LD_BC(PARTYMON_STRUCT_LENGTH - 1);

loop:
    OR_A_hl;
    INC_HL;  // + 1
    OR_A_hl;
    ADD_HL_BC;
    DEC_E;
    IF_NZ goto loop;
    LD_D_A;
    RET;

}

void CheckIfCurPartyMonIsFitToFight(void){
    LD_A_addr(wCurPartyMon);
    LD_HL(wPartyMon1HP);
    CALL(aGetPartyLocation);
    LD_A_hli;
    OR_A_hl;
    RET_NZ ;

    LD_A_addr(wBattleHasJustStarted);
    AND_A_A;
    IF_NZ goto finish_fail;
    LD_HL(wPartySpecies);
    LD_A_addr(wCurPartyMon);
    LD_C_A;
    LD_B(0);
    ADD_HL_BC;
    LD_A_hl;
    CP_A(EGG);
    LD_HL(mBattleText_AnEGGCantBattle);
    IF_Z goto print_textbox;

    LD_HL(mBattleText_TheresNoWillToBattle);


print_textbox:
    CALL(aStdBattleTextbox);


finish_fail:
    XOR_A_A;
    RET;

}

void TryToRunAwayFromBattle(void){
//  Run away from battle, with or without item
    LD_A_addr(wBattleType);
    CP_A(BATTLETYPE_DEBUG);
    JP_Z (mTryToRunAwayFromBattle_can_escape);
    CP_A(BATTLETYPE_CONTEST);
    JP_Z (mTryToRunAwayFromBattle_can_escape);
    CP_A(BATTLETYPE_TRAP);
    JP_Z (mTryToRunAwayFromBattle_cant_escape);
    CP_A(BATTLETYPE_CELEBI);
    JP_Z (mTryToRunAwayFromBattle_cant_escape);
    CP_A(BATTLETYPE_SHINY);
    JP_Z (mTryToRunAwayFromBattle_cant_escape);
    CP_A(BATTLETYPE_SUICUNE);
    JP_Z (mTryToRunAwayFromBattle_cant_escape);

    LD_A_addr(wLinkMode);
    AND_A_A;
    JP_NZ (mTryToRunAwayFromBattle_can_escape);

    LD_A_addr(wBattleMode);
    DEC_A;
    JP_NZ (mTryToRunAwayFromBattle_cant_run_from_trainer);

    LD_A_addr(wEnemySubStatus5);
    BIT_A(SUBSTATUS_CANT_RUN);
    JP_NZ (mTryToRunAwayFromBattle_cant_escape);

    LD_A_addr(wPlayerWrapCount);
    AND_A_A;
    JP_NZ (mTryToRunAwayFromBattle_cant_escape);

    PUSH_HL;
    PUSH_DE;
    LD_A_addr(wBattleMonItem);
    LD_addr_A(wNamedObjectIndex);
    LD_B_A;
    CALLFAR(aGetItemHeldEffect);
    LD_A_B;
    CP_A(HELD_ESCAPE);
    POP_DE;
    POP_HL;
    IF_NZ goto no_flee_item;

    CALL(aSetPlayerTurn);
    CALL(aGetItemName);
    LD_HL(mBattleText_UserFledUsingAStringBuffer1);
    CALL(aStdBattleTextbox);
    JP(mTryToRunAwayFromBattle_can_escape);


no_flee_item:
    LD_A_addr(wNumFleeAttempts);
    INC_A;
    LD_addr_A(wNumFleeAttempts);
    LD_A_hli;
    LDH_addr_A(hMultiplicand + 1);
    LD_A_hl;
    LDH_addr_A(hMultiplicand + 2);
    LD_A_de;
    INC_DE;
    LDH_addr_A(hEnemyMonSpeed + 0);
    LD_A_de;
    LDH_addr_A(hEnemyMonSpeed + 1);
    CALL(aSafeLoadTempTilemapToTilemap);
    LD_DE(hMultiplicand + 1);
    LD_HL(hEnemyMonSpeed);
    LD_C(2);
    CALL(aCompareBytes);
    IF_NC goto can_escape;

    XOR_A_A;
    LDH_addr_A(hMultiplicand + 0);
    LD_A(32);
    LDH_addr_A(hMultiplier);
    CALL(aMultiply);
    LDH_A_addr(hProduct + 2);
    LDH_addr_A(hDividend + 0);
    LDH_A_addr(hProduct + 3);
    LDH_addr_A(hDividend + 1);
    LDH_A_addr(hEnemyMonSpeed + 0);
    LD_B_A;
    LDH_A_addr(hEnemyMonSpeed + 1);
    SRL_B;
    RR_A;
    SRL_B;
    RR_A;
    AND_A_A;
    IF_Z goto can_escape;
    LDH_addr_A(hDivisor);
    LD_B(2);
    CALL(aDivide);
    LDH_A_addr(hQuotient + 2);
    AND_A_A;
    IF_NZ goto can_escape;
    LD_A_addr(wNumFleeAttempts);
    LD_C_A;

loop:
    DEC_C;
    IF_Z goto cant_escape_2;
    LD_B(30);
    LDH_A_addr(hQuotient + 3);
    ADD_A_B;
    LDH_addr_A(hQuotient + 3);
    IF_C goto can_escape;
    goto loop;


cant_escape_2:
    CALL(aBattleRandom);
    LD_B_A;
    LDH_A_addr(hQuotient + 3);
    CP_A_B;
    IF_NC goto can_escape;
    LD_A(BATTLEPLAYERACTION_USEITEM);
    LD_addr_A(wBattlePlayerAction);
    LD_HL(mBattleText_CantEscape2);
    goto print_inescapable_text;


cant_escape:
    LD_HL(mBattleText_CantEscape);
    goto print_inescapable_text;


cant_run_from_trainer:
    LD_HL(mBattleText_TheresNoEscapeFromTrainerBattle);


print_inescapable_text:
    CALL(aStdBattleTextbox);
    LD_A(TRUE);
    LD_addr_A(wFailedToFlee);
    CALL(aLoadTilemapToTempTilemap);
    AND_A_A;
    RET;


can_escape:
    LD_A_addr(wLinkMode);
    AND_A_A;
    LD_A(DRAW);
    IF_Z goto fled;
    CALL(aLoadTilemapToTempTilemap);
    XOR_A_A;  // BATTLEPLAYERACTION_USEMOVE
    LD_addr_A(wBattlePlayerAction);
    LD_A(0xf);
    LD_addr_A(wCurMoveNum);
    XOR_A_A;
    LD_addr_A(wCurPlayerMove);
    CALL(aLinkBattleSendReceiveAction);
    CALL(aSafeLoadTempTilemapToTilemap);
    CALL(aCheckMobileBattleError);
    IF_C goto mobile;

// Got away safely
    LD_A_addr(wBattleAction);
    CP_A(BATTLEACTION_FORFEIT);
    LD_A(DRAW);
    IF_Z goto fled;
    DEC_A;  // LOSE

fled:
    LD_B_A;
    LD_A_addr(wBattleResult);
    AND_A(BATTLERESULT_BITMASK);
    ADD_A_B;
    LD_addr_A(wBattleResult);
    CALL(aStopDangerSound);
    PUSH_DE;
    LD_DE(SFX_RUN);
    CALL(aWaitPlaySFX);
    POP_DE;
    CALL(aWaitSFX);
    LD_HL(mBattleText_GotAwaySafely);
    CALL(aStdBattleTextbox);
    CALL(aWaitSFX);
    CALL(aLoadTilemapToTempTilemap);
    SCF;
    RET;


mobile:
    CALL(aStopDangerSound);
    LD_HL(wcd2a);
    BIT_hl(4);
    IF_NZ goto skip_link_error;
    LD_HL(mBattleText_LinkErrorBattleCanceled);
    CALL(aStdBattleTextbox);


skip_link_error:
    CALL(aWaitSFX);
    CALL(aLoadTilemapToTempTilemap);
    SCF;
    RET;

}

void InitBattleMon(void){
    LD_A(MON_SPECIES);
    CALL(aGetPartyParamLocation);
    LD_DE(wBattleMonSpecies);
    LD_BC(MON_ID);
    CALL(aCopyBytes);
    LD_BC(MON_DVS - MON_ID);
    ADD_HL_BC;
    LD_DE(wBattleMonDVs);
    LD_BC(MON_POKERUS - MON_DVS);
    CALL(aCopyBytes);
    INC_HL;
    INC_HL;
    INC_HL;
    LD_DE(wBattleMonLevel);
    LD_BC(PARTYMON_STRUCT_LENGTH - MON_LEVEL);
    CALL(aCopyBytes);
    LD_A_addr(wBattleMonSpecies);
    LD_addr_A(wTempBattleMonSpecies);
    LD_addr_A(wCurPartySpecies);
    LD_addr_A(wCurSpecies);
    CALL(aGetBaseData);
    LD_A_addr(wBaseType1);
    LD_addr_A(wBattleMonType1);
    LD_A_addr(wBaseType2);
    LD_addr_A(wBattleMonType2);
    LD_HL(wPartyMonNicknames);
    LD_A_addr(wCurBattleMon);
    CALL(aSkipNames);
    LD_DE(wBattleMonNickname);
    LD_BC(MON_NAME_LENGTH);
    CALL(aCopyBytes);
    LD_HL(wBattleMonAttack);
    LD_DE(wPlayerStats);
    LD_BC(PARTYMON_STRUCT_LENGTH - MON_ATK);
    CALL(aCopyBytes);
    CALL(aApplyStatusEffectOnPlayerStats);
    CALL(aBadgeStatBoosts);
    RET;

}

void BattleCheckPlayerShininess(void){
    CALL(aGetPartyMonDVs);
    JR(mBattleCheckShininess);

}

void BattleCheckEnemyShininess(void){
    CALL(aGetEnemyMonDVs);

    return BattleCheckShininess();
}

void BattleCheckShininess(void){
    LD_B_H;
    LD_C_L;
    CALLFAR(aCheckShininess);
    RET;

}

void GetPartyMonDVs(void){
    LD_HL(wBattleMonDVs);
    LD_A_addr(wPlayerSubStatus5);
    BIT_A(SUBSTATUS_TRANSFORMED);
    RET_Z ;
    LD_HL(wPartyMon1DVs);
    LD_A_addr(wCurBattleMon);
    JP(mGetPartyLocation);

}

void GetEnemyMonDVs(void){
    LD_HL(wEnemyMonDVs);
    LD_A_addr(wEnemySubStatus5);
    BIT_A(SUBSTATUS_TRANSFORMED);
    RET_Z ;
    LD_HL(wEnemyBackupDVs);
    LD_A_addr(wBattleMode);
    DEC_A;
    RET_Z ;
    LD_HL(wOTPartyMon1DVs);
    LD_A_addr(wCurOTMon);
    JP(mGetPartyLocation);

}

void ResetPlayerStatLevels(void){
    LD_A(BASE_STAT_LEVEL);
    LD_B(NUM_LEVEL_STATS);
    LD_HL(wPlayerStatLevels);

loop:
    LD_hli_A;
    DEC_B;
    IF_NZ goto loop;
    RET;

}

void InitEnemyMon(void){
    LD_A_addr(wCurPartyMon);
    LD_HL(wOTPartyMon1Species);
    CALL(aGetPartyLocation);
    LD_DE(wEnemyMonSpecies);
    LD_BC(MON_ID);
    CALL(aCopyBytes);
    LD_BC(MON_DVS - MON_ID);
    ADD_HL_BC;
    LD_DE(wEnemyMonDVs);
    LD_BC(MON_POKERUS - MON_DVS);
    CALL(aCopyBytes);
    INC_HL;
    INC_HL;
    INC_HL;
    LD_DE(wEnemyMonLevel);
    LD_BC(PARTYMON_STRUCT_LENGTH - MON_LEVEL);
    CALL(aCopyBytes);
    LD_A_addr(wEnemyMonSpecies);
    LD_addr_A(wCurSpecies);
    CALL(aGetBaseData);
    LD_HL(wOTPartyMonNicknames);
    LD_A_addr(wCurPartyMon);
    CALL(aSkipNames);
    LD_DE(wEnemyMonNickname);
    LD_BC(MON_NAME_LENGTH);
    CALL(aCopyBytes);
    LD_HL(wEnemyMonAttack);
    LD_DE(wEnemyStats);
    LD_BC(PARTYMON_STRUCT_LENGTH - MON_ATK);
    CALL(aCopyBytes);
    CALL(aApplyStatusEffectOnEnemyStats);
    LD_HL(wBaseType1);
    LD_DE(wEnemyMonType1);
    LD_A_hli;
    LD_de_A;
    INC_DE;
    LD_A_hl;
    LD_de_A;
// The enemy mon's base Sp. Def isn't needed since its base
// Sp. Atk is also used to calculate Sp. Def stat experience.
    LD_HL(wBaseStats);
    LD_DE(wEnemyMonBaseStats);
    LD_B(NUM_STATS - 1);

loop:
    LD_A_hli;
    LD_de_A;
    INC_DE;
    DEC_B;
    IF_NZ goto loop;
    LD_A_addr(wCurPartyMon);
    LD_addr_A(wCurOTMon);
    RET;

}

void SwitchPlayerMon(void){
    CALL(aClearSprites);
    LD_A_addr(wCurBattleMon);
    LD_addr_A(wLastPlayerMon);
    LD_A_addr(wCurPartyMon);
    LD_addr_A(wCurBattleMon);
    CALL(aAddBattleParticipant);
    CALL(aInitBattleMon);
    CALL(aResetPlayerStatLevels);
    CALL(aNewBattleMonStatus);
    CALL(aBreakAttraction);
    CALL(aSendOutPlayerMon);
    CALL(aEmptyBattleTextbox);
    CALL(aLoadTilemapToTempTilemap);
    LD_HL(wEnemyMonHP);
    LD_A_hli;
    OR_A_hl;
    RET;

}

void SendOutPlayerMon(void){
    LD_HL(wBattleMonDVs);
    PREDEF(pGetUnownLetter);
    hlcoord(1, 5, wTilemap);
    LD_B(7);
    LD_C(8);
    CALL(aClearBox);
    CALL(aWaitBGMap);
    XOR_A_A;
    LDH_addr_A(hBGMapMode);
    CALL(aGetBattleMonBackpic);
    XOR_A_A;
    LDH_addr_A(hGraphicStartTile);
    LD_addr_A(wBattleMenuCursorPosition);
    LD_addr_A(wCurMoveNum);
    LD_addr_A(wTypeModifier);
    LD_addr_A(wPlayerMoveStruct + MOVE_ANIM);
    LD_addr_A(wLastPlayerCounterMove);
    LD_addr_A(wLastEnemyCounterMove);
    LD_addr_A(wLastPlayerMove);
    CALL(aCheckAmuletCoin);
    CALL(aFinishBattleAnim);
    XOR_A_A;
    LD_addr_A(wEnemyWrapCount);
    CALL(aSetPlayerTurn);
    XOR_A_A;
    LD_addr_A(wNumHits);
    LD_addr_A(wBattleAnimParam);
    LD_DE(ANIM_SEND_OUT_MON);
    CALL(aCall_PlayBattleAnim);
    CALL(aBattleCheckPlayerShininess);
    IF_NC goto not_shiny;
    LD_A(1);
    LD_addr_A(wBattleAnimParam);
    LD_DE(ANIM_SEND_OUT_MON);
    CALL(aCall_PlayBattleAnim);


not_shiny:
    LD_A(MON_SPECIES);
    CALL(aGetPartyParamLocation);
    LD_B_H;
    LD_C_L;
    FARCALL(aCheckFaintedFrzSlp);
    IF_C goto statused;
    LD_A(0xf0);
    LD_addr_A(wCryTracks);
    LD_A_addr(wCurPartySpecies);
    CALL(aPlayStereoCry);


statused:
    CALL(aUpdatePlayerHUD);
    LD_A(0x1);
    LDH_addr_A(hBGMapMode);
    RET;

}

void NewBattleMonStatus(void){
    XOR_A_A;
    LD_addr_A(wLastPlayerCounterMove);
    LD_addr_A(wLastEnemyCounterMove);
    LD_addr_A(wLastPlayerMove);
    LD_HL(wPlayerSubStatus1);
    for(int rept = 0; rept < 4; rept++){
    LD_hli_A;
    }
    LD_hl_A;
    LD_HL(wPlayerUsedMoves);
    LD_hli_A;
    LD_hli_A;
    LD_hli_A;
    LD_hl_A;
    LD_addr_A(wPlayerDisableCount);
    LD_addr_A(wPlayerFuryCutterCount);
    LD_addr_A(wPlayerProtectCount);
    LD_addr_A(wPlayerRageCounter);
    LD_addr_A(wDisabledMove);
    LD_addr_A(wPlayerMinimized);
    LD_addr_A(wEnemyWrapCount);
    LD_addr_A(wPlayerWrapCount);
    LD_addr_A(wPlayerTurnsTaken);
    LD_HL(wEnemySubStatus5);
    RES_hl(SUBSTATUS_CANT_RUN);
    RET;

}

void BreakAttraction(void){
    // LD_HL(wPlayerSubStatus1);
    // RES_hl(SUBSTATUS_IN_LOVE);
    bit_reset(wram->wPlayerSubStatus1, SUBSTATUS_IN_LOVE);
    // LD_HL(wEnemySubStatus1);
    // RES_hl(SUBSTATUS_IN_LOVE);
    bit_reset(wram->wEnemySubStatus1, SUBSTATUS_IN_LOVE);
    // RET;
}

void SpikesDamage(void){
    LD_HL(wPlayerScreens);
    LD_DE(wBattleMonType);
    LD_BC(mUpdatePlayerHUD);
    LDH_A_addr(hBattleTurn);
    AND_A_A;
    IF_Z goto ok;
    LD_HL(wEnemyScreens);
    LD_DE(wEnemyMonType);
    LD_BC(mUpdateEnemyHUD);

ok:

    BIT_hl(SCREENS_SPIKES);
    RET_Z ;

// Flying-types aren't affected by Spikes.
    LD_A_de;
    CP_A(FLYING);
    RET_Z ;
    INC_DE;
    LD_A_de;
    CP_A(FLYING);
    RET_Z ;

    PUSH_BC;

    LD_HL(mBattleText_UserHurtBySpikes);  // "hurt by SPIKES!"
    CALL(aStdBattleTextbox);

    CALL(aGetEighthMaxHP);
    CALL(aSubtractHPFromTarget);

    POP_HL;
    CALL(aSpikesDamage_hl);

    JP(mWaitBGMap);


hl:
    JP_hl;

}

void PursuitSwitch(void){
    LD_A(BATTLE_VARS_MOVE);
    CALL(aGetBattleVar);
    LD_B_A;
    CALL(aGetMoveEffect);
    LD_A_B;
    CP_A(EFFECT_PURSUIT);
    IF_NZ goto done;

    LD_A_addr(wCurBattleMon);
    PUSH_AF;

    LD_HL(mDoPlayerTurn);
    LDH_A_addr(hBattleTurn);
    AND_A_A;
    IF_Z goto do_turn;
    LD_HL(mDoEnemyTurn);
    LD_A_addr(wLastPlayerMon);
    LD_addr_A(wCurBattleMon);

do_turn:
    LD_A(BANK(aDoPlayerTurn));  // aka BANK(DoEnemyTurn)
    RST(aFarCall);

    LD_A(BATTLE_VARS_MOVE);
    CALL(aGetBattleVarAddr);
    LD_A(0xff);
    LD_hl_A;

    POP_AF;
    LD_addr_A(wCurBattleMon);

    LDH_A_addr(hBattleTurn);
    AND_A_A;
    IF_Z goto check_enemy_fainted;

    LD_A_addr(wLastPlayerMon);
    CALL(aUpdateBattleMon);
    LD_HL(wBattleMonHP);
    LD_A_hli;
    OR_A_hl;
    IF_NZ goto done;

    LD_A(0xf0);
    LD_addr_A(wCryTracks);
    LD_A_addr(wBattleMonSpecies);
    CALL(aPlayStereoCry);
    LD_A_addr(wLastPlayerMon);
    LD_C_A;
    LD_HL(wBattleParticipantsNotFainted);
    LD_B(RESET_FLAG);
    PREDEF(pSmallFarFlagAction);
    CALL(aPlayerMonFaintedAnimation);
    LD_HL(mBattleText_MonFainted);
    goto done_fainted;


check_enemy_fainted:
    LD_HL(wEnemyMonHP);
    LD_A_hli;
    OR_A_hl;
    IF_NZ goto done;

    LD_DE(SFX_KINESIS);
    CALL(aPlaySFX);
    CALL(aWaitSFX);
    LD_DE(SFX_FAINT);
    CALL(aPlaySFX);
    CALL(aWaitSFX);
    CALL(aEnemyMonFaintedAnimation);
    LD_HL(mBattleText_EnemyMonFainted);


done_fainted:
    CALL(aStdBattleTextbox);
    SCF;
    RET;


done:
    AND_A_A;
    RET;

}

void RecallPlayerMon(void){
    LDH_A_addr(hBattleTurn);
    PUSH_AF;
    XOR_A_A;
    LDH_addr_A(hBattleTurn);
    LD_addr_A(wNumHits);
    LD_DE(ANIM_RETURN_MON);
    CALL(aCall_PlayBattleAnim);
    POP_AF;
    LDH_addr_A(hBattleTurn);
    RET;

}

void HandleHealingItems(void){
    LDH_A_addr(hSerialConnectionStatus);
    CP_A(USING_EXTERNAL_CLOCK);
    IF_Z goto player_1;
    CALL(aSetPlayerTurn);
    CALL(aHandleHPHealingItem);
    CALL(aUseHeldStatusHealingItem);
    CALL(aUseConfusionHealingItem);
    CALL(aSetEnemyTurn);
    CALL(aHandleHPHealingItem);
    CALL(aUseHeldStatusHealingItem);
    JP(mUseConfusionHealingItem);


player_1:
    CALL(aSetEnemyTurn);
    CALL(aHandleHPHealingItem);
    CALL(aUseHeldStatusHealingItem);
    CALL(aUseConfusionHealingItem);
    CALL(aSetPlayerTurn);
    CALL(aHandleHPHealingItem);
    CALL(aUseHeldStatusHealingItem);
    JP(mUseConfusionHealingItem);

}

void HandleHPHealingItem(void){
    CALLFAR(aGetOpponentItem);
    LD_A_B;
    CP_A(HELD_BERRY);
    RET_NZ ;
    LD_DE(wEnemyMonHP + 1);
    LD_HL(wEnemyMonMaxHP);
    LDH_A_addr(hBattleTurn);
    AND_A_A;
    IF_Z goto go;
    LD_DE(wBattleMonHP + 1);
    LD_HL(wBattleMonMaxHP);


go:
//  If, and only if, Pokemon's HP is less than half max, use the item.
//  Store current HP in Buffer 3/4
    PUSH_BC;
    LD_A_de;
    LD_addr_A(wHPBuffer2);
    ADD_A_A;
    LD_C_A;
    DEC_DE;
    LD_A_de;
    INC_DE;
    LD_addr_A(wHPBuffer2 + 1);
    ADC_A_A;
    LD_B_A;
    LD_A_B;
    CP_A_hl;
    LD_A_C;
    POP_BC;
    IF_Z goto equal;
    IF_C goto less;
    RET;


equal:
    INC_HL;
    CP_A_hl;
    DEC_HL;
    RET_NC ;


less:
    CALL(aItemRecoveryAnim);
// store max HP in wHPBuffer1
    LD_A_hli;
    LD_addr_A(wHPBuffer1 + 1);
    LD_A_hl;
    LD_addr_A(wHPBuffer1);
    LD_A_de;
    ADD_A_C;
    LD_addr_A(wHPBuffer3);
    LD_C_A;
    DEC_DE;
    LD_A_de;
    ADC_A(0);
    LD_addr_A(wHPBuffer3 + 1);
    LD_B_A;
    LD_A_hld;
    CP_A_C;
    LD_A_hl;
    SBC_A_B;
    IF_NC goto okay;
    LD_A_hli;
    LD_addr_A(wHPBuffer3 + 1);
    LD_A_hl;
    LD_addr_A(wHPBuffer3);


okay:
    LD_A_addr(wHPBuffer3 + 1);
    LD_de_A;
    INC_DE;
    LD_A_addr(wHPBuffer3);
    LD_de_A;
    LDH_A_addr(hBattleTurn);
    LD_addr_A(wWhichHPBar);
    AND_A_A;
    hlcoord(2, 2, wTilemap);
    IF_Z goto got_hp_bar_coords;
    hlcoord(10, 9, wTilemap);


got_hp_bar_coords:
    LD_addr_A(wWhichHPBar);
    PREDEF(pAnimateHPBar);
    return UseOpponentItem();
}

void UseOpponentItem(void){
    CALL(aRefreshBattleHuds);
    CALLFAR(aGetOpponentItem);
    LD_A_hl;
    LD_addr_A(wNamedObjectIndex);
    CALL(aGetItemName);
    CALLFAR(aConsumeHeldItem);
    LD_HL(mRecoveredUsingText);
    JP(mStdBattleTextbox);

}

void ItemRecoveryAnim(void){
    PUSH_HL;
    PUSH_DE;
    PUSH_BC;
    CALL(aEmptyBattleTextbox);
    LD_A(RECOVER);
    LD_addr_A(wFXAnimID);
    CALL(aSwitchTurnCore);
    XOR_A_A;
    LD_addr_A(wNumHits);
    LD_addr_A(wFXAnimID + 1);
    PREDEF(pPlayBattleAnim);
    CALL(aSwitchTurnCore);
    POP_BC;
    POP_DE;
    POP_HL;
    RET;

}

void UseHeldStatusHealingItem(void){
    CALLFAR(aGetOpponentItem);
    LD_HL(mHeldStatusHealingEffects);

loop:
    LD_A_hli;
    CP_A(0xff);
    RET_Z ;
    INC_HL;
    CP_A_B;
    IF_NZ goto loop;
    DEC_HL;
    LD_B_hl;
    LD_A(BATTLE_VARS_STATUS_OPP);
    CALL(aGetBattleVarAddr);
    AND_A_B;
    RET_Z ;
    XOR_A_A;
    LD_hl_A;
    PUSH_BC;
    CALL(aUpdateOpponentInParty);
    POP_BC;
    LD_A(BATTLE_VARS_SUBSTATUS5_OPP);
    CALL(aGetBattleVarAddr);
    AND_A_hl;
    RES_hl(SUBSTATUS_TOXIC);
    LD_A(BATTLE_VARS_SUBSTATUS1_OPP);
    CALL(aGetBattleVarAddr);
    AND_A_hl;
    RES_hl(SUBSTATUS_NIGHTMARE);
    LD_A_B;
    CP_A(ALL_STATUS);
    IF_NZ goto skip_confuse;
    LD_A(BATTLE_VARS_SUBSTATUS3_OPP);
    CALL(aGetBattleVarAddr);
    RES_hl(SUBSTATUS_CONFUSED);


skip_confuse:
    LD_HL(mCalcEnemyStats);
    LDH_A_addr(hBattleTurn);
    AND_A_A;
    IF_Z goto got_pointer;
    LD_HL(mCalcPlayerStats);


got_pointer:
    CALL(aSwitchTurnCore);
    LD_A(BANK(aCalcPlayerStats));  // aka BANK(CalcEnemyStats)
    RST(aFarCall);
    CALL(aSwitchTurnCore);
    CALL(aItemRecoveryAnim);
    CALL(aUseOpponentItem);
    LD_A(0x1);
    AND_A_A;
    RET;

// INCLUDE "data/battle/held_heal_status.asm"

    return UseConfusionHealingItem();
}

void UseConfusionHealingItem(void){
    LD_A(BATTLE_VARS_SUBSTATUS3_OPP);
    CALL(aGetBattleVar);
    BIT_A(SUBSTATUS_CONFUSED);
    RET_Z ;
    CALLFAR(aGetOpponentItem);
    LD_A_B;
    CP_A(HELD_HEAL_CONFUSION);
    IF_Z goto heal_status;
    CP_A(HELD_HEAL_STATUS);
    RET_NZ ;


heal_status:
    LD_A_hl;
    LD_addr_A(wNamedObjectIndex);
    LD_A(BATTLE_VARS_SUBSTATUS3_OPP);
    CALL(aGetBattleVarAddr);
    RES_hl(SUBSTATUS_CONFUSED);
    CALL(aGetItemName);
    CALL(aItemRecoveryAnim);
    LD_HL(mBattleText_ItemHealedConfusion);
    CALL(aStdBattleTextbox);
    LDH_A_addr(hBattleTurn);
    AND_A_A;
    IF_NZ goto do_partymon;
    CALL(aGetOTPartymonItem);
    XOR_A_A;
    LD_bc_A;
    LD_A_addr(wBattleMode);
    DEC_A;
    RET_Z ;
    LD_hl(0x0);
    RET;


do_partymon:
    CALL(aGetPartymonItem);
    XOR_A_A;
    LD_bc_A;
    LD_hl_A;
    RET;

}

void HandleStatBoostingHeldItems(void){
//  The effects handled here are not used in-game.
    LDH_A_addr(hSerialConnectionStatus);
    CP_A(USING_EXTERNAL_CLOCK);
    IF_Z goto player_1;
    CALL(aHandleStatBoostingHeldItems_DoPlayer);
    JP(mHandleStatBoostingHeldItems_DoEnemy);


player_1:
    CALL(aHandleStatBoostingHeldItems_DoEnemy);
    JP(mHandleStatBoostingHeldItems_DoPlayer);


DoPlayer:
    CALL(aGetPartymonItem);
    LD_A(0x0);
    JP(mHandleStatBoostingHeldItems_HandleItem);


DoEnemy:
    CALL(aGetOTPartymonItem);
    LD_A(0x1);

HandleItem:
    LDH_addr_A(hBattleTurn);
    LD_D_H;
    LD_E_L;
    PUSH_DE;
    PUSH_BC;
    LD_A_bc;
    LD_B_A;
    CALLFAR(aGetItemHeldEffect);
    LD_HL(mHeldStatUpItems);

loop:
    LD_A_hli;
    CP_A(-1);
    IF_Z goto finish;
    INC_HL;
    INC_HL;
    CP_A_B;
    IF_NZ goto loop;
    POP_BC;
    LD_A_bc;
    LD_addr_A(wNamedObjectIndex);
    PUSH_BC;
    DEC_HL;
    DEC_HL;
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    LD_A(BANK(aBattleCommand_AttackUp));
    RST(aFarCall);
    POP_BC;
    POP_DE;
    LD_A_addr(wFailedMessage);
    AND_A_A;
    RET_NZ ;
    XOR_A_A;
    LD_bc_A;
    LD_de_A;
    CALL(aGetItemName);
    LD_HL(mBattleText_UsersStringBuffer1Activated);
    CALL(aStdBattleTextbox);
    CALLFAR(aBattleCommand_StatUpMessage);
    RET;


finish:
    POP_BC;
    POP_DE;
    RET;

// INCLUDE "data/battle/held_stat_up.asm"

    return GetPartymonItem();
}

void GetPartymonItem(void){
    LD_HL(wPartyMon1Item);
    LD_A_addr(wCurBattleMon);
    CALL(aGetPartyLocation);
    LD_BC(wBattleMonItem);
    RET;

}

void GetOTPartymonItem(void){
    LD_HL(wOTPartyMon1Item);
    LD_A_addr(wCurOTMon);
    CALL(aGetPartyLocation);
    LD_BC(wEnemyMonItem);
    RET;

}

void UpdateBattleHUDs(void){
    PUSH_HL;
    PUSH_DE;
    PUSH_BC;
    CALL(aDrawPlayerHUD);
    LD_HL(wPlayerHPPal);
    CALL(aSetHPPal);
    CALL(aCheckDanger);
    CALL(aDrawEnemyHUD);
    LD_HL(wEnemyHPPal);
    CALL(aSetHPPal);
    POP_BC;
    POP_DE;
    POP_HL;
    RET;

}

void UpdatePlayerHUD(void){
    PUSH_HL;
    PUSH_DE;
    PUSH_BC;
    CALL(aDrawPlayerHUD);
    CALL(aUpdatePlayerHPPal);
    CALL(aCheckDanger);
    POP_BC;
    POP_DE;
    POP_HL;
    RET;

}

void DrawPlayerHUD(void){
    XOR_A_A;
    LDH_addr_A(hBGMapMode);

// Clear the area
    hlcoord(9, 7, wTilemap);
    LD_BC((5 << 8) | 11);
    CALL(aClearBox);

    FARCALL(aDrawPlayerHUDBorder);

    hlcoord(18, 9, wTilemap);
    LD_hl(0x73);  // vertical bar
    CALL(aPrintPlayerHUD);

// HP bar
    hlcoord(10, 9, wTilemap);
    LD_B(1);
    XOR_A_A;  // PARTYMON
    LD_addr_A(wMonType);
    PREDEF(pDrawPlayerHP);

// Exp bar
    PUSH_DE;
    LD_A_addr(wCurBattleMon);
    LD_HL(wPartyMon1Exp + 2);
    CALL(aGetPartyLocation);
    LD_D_H;
    LD_E_L;

    hlcoord(10, 11, wTilemap);
    LD_A_addr(wTempMonLevel);
    LD_B_A;
    CALL(aFillInExpBar);
    POP_DE;
    RET;

}

void UpdatePlayerHPPal(void){
    LD_HL(wPlayerHPPal);
    JP(mUpdateHPPal);

}

void CheckDanger(void){
    LD_HL(wBattleMonHP);
    LD_A_hli;
    OR_A_hl;
    IF_Z goto no_danger;
    LD_A_addr(wBattleLowHealthAlarm);
    AND_A_A;
    IF_NZ goto done;
    LD_A_addr(wPlayerHPPal);
    CP_A(HP_RED);
    IF_Z goto danger;


no_danger:
    LD_HL(wLowHealthAlarm);
    RES_hl(DANGER_ON_F);
    goto done;


danger:
    LD_HL(wLowHealthAlarm);
    SET_hl(DANGER_ON_F);


done:
    RET;

}

void PrintPlayerHUD(void){
    LD_DE(wBattleMonNickname);
    hlcoord(10, 7, wTilemap);
    CALL(aBattle_DummyFunction);
    CALL(aPlaceString);

    PUSH_BC;

    LD_A_addr(wCurBattleMon);
    LD_HL(wPartyMon1DVs);
    CALL(aGetPartyLocation);
    LD_DE(wTempMonDVs);
    LD_A_hli;
    LD_de_A;
    INC_DE;
    LD_A_hl;
    LD_de_A;
    LD_HL(wBattleMonLevel);
    LD_DE(wTempMonLevel);
    LD_BC(wTempMonStructEnd - wTempMonLevel);
    CALL(aCopyBytes);  // battle_struct and party_struct end with the same data
    LD_A_addr(wCurBattleMon);
    LD_HL(wPartyMon1Species);
    CALL(aGetPartyLocation);
    LD_A_hl;
    LD_addr_A(wCurPartySpecies);
    LD_addr_A(wCurSpecies);
    CALL(aGetBaseData);

    POP_HL;
    DEC_HL;

    LD_A(TEMPMON);
    LD_addr_A(wMonType);
    CALLFAR(aGetGender);
    LD_A(0x7f);
    IF_C goto got_gender_char;
    LD_A(0xef);
    IF_NZ goto got_gender_char;
    LD_A(0xf5);


got_gender_char:
    hlcoord(17, 8, wTilemap);
    LD_hl_A;
    hlcoord(14, 8, wTilemap);
    PUSH_AF;  // back up gender
    PUSH_HL;
    LD_DE(wBattleMonStatus);
    PREDEF(pPlaceNonFaintStatus);
    POP_HL;
    POP_BC;
    RET_NZ ;
    LD_A_B;
    CP_A(0x7f);
    IF_NZ goto copy_level;  // male or female
    DEC_HL;  // genderless


copy_level:
    LD_A_addr(wBattleMonLevel);
    LD_addr_A(wTempMonLevel);
    JP(mPrintLevel);

}

void UpdateEnemyHUD(void){
    PUSH_HL;
    PUSH_DE;
    PUSH_BC;
    CALL(aDrawEnemyHUD);
    CALL(aUpdateEnemyHPPal);
    POP_BC;
    POP_DE;
    POP_HL;
    RET;

}

void DrawEnemyHUD(void){
    XOR_A_A;
    LDH_addr_A(hBGMapMode);

    hlcoord(1, 0, wTilemap);
    LD_BC((4 << 8) | 11);
    CALL(aClearBox);

    FARCALL(aDrawEnemyHUDBorder);

    LD_A_addr(wTempEnemyMonSpecies);
    LD_addr_A(wCurSpecies);
    LD_addr_A(wCurPartySpecies);
    CALL(aGetBaseData);
    LD_DE(wEnemyMonNickname);
    hlcoord(1, 0, wTilemap);
    CALL(aBattle_DummyFunction);
    CALL(aPlaceString);
    LD_H_B;
    LD_L_C;
    DEC_HL;

    LD_HL(wEnemyMonDVs);
    LD_DE(wTempMonDVs);
    LD_A_addr(wEnemySubStatus5);
    BIT_A(SUBSTATUS_TRANSFORMED);
    IF_Z goto ok;
    LD_HL(wEnemyBackupDVs);

ok:
    LD_A_hli;
    LD_de_A;
    INC_DE;
    LD_A_hl;
    LD_de_A;

    LD_A(TEMPMON);
    LD_addr_A(wMonType);
    CALLFAR(aGetGender);
    LD_A(0x7f);
    IF_C goto got_gender;
    LD_A(0xef);
    IF_NZ goto got_gender;
    LD_A(0xf5);


got_gender:
    hlcoord(9, 1, wTilemap);
    LD_hl_A;

    hlcoord(6, 1, wTilemap);
    PUSH_AF;
    PUSH_HL;
    LD_DE(wEnemyMonStatus);
    PREDEF(pPlaceNonFaintStatus);
    POP_HL;
    POP_BC;
    IF_NZ goto skip_level;
    LD_A_B;
    CP_A(0x7f);
    IF_NZ goto print_level;
    DEC_HL;

print_level:
    LD_A_addr(wEnemyMonLevel);
    LD_addr_A(wTempMonLevel);
    CALL(aPrintLevel);

skip_level:

    LD_HL(wEnemyMonHP);
    LD_A_hli;
    LDH_addr_A(hMultiplicand + 1);
    LD_A_hld;
    LDH_addr_A(hMultiplicand + 2);
    OR_A_hl;
    IF_NZ goto not_fainted;

    LD_C_A;
    LD_E_A;
    LD_D(HP_BAR_LENGTH);
    JP(mDrawEnemyHUD_draw_bar);


not_fainted:
    XOR_A_A;
    LDH_addr_A(hMultiplicand + 0);
    LD_A(HP_BAR_LENGTH_PX);
    LDH_addr_A(hMultiplier);
    CALL(aMultiply);
    LD_HL(wEnemyMonMaxHP);
    LD_A_hli;
    LD_B_A;
    LD_A_hl;
    LDH_addr_A(hMultiplier);
    LD_A_B;
    AND_A_A;
    IF_Z goto less_than_256_max;
    LDH_A_addr(hMultiplier);
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
    LDH_addr_A(hProduct + 3);
    LD_A_B;
    LDH_addr_A(hProduct + 2);


less_than_256_max:
    LDH_A_addr(hProduct + 2);
    LDH_addr_A(hDividend + 0);
    LDH_A_addr(hProduct + 3);
    LDH_addr_A(hDividend + 1);
    LD_A(2);
    LD_B_A;
    CALL(aDivide);
    LDH_A_addr(hQuotient + 3);
    LD_E_A;
    LD_A(HP_BAR_LENGTH);
    LD_D_A;
    LD_C_A;


draw_bar:
    XOR_A_A;
    LD_addr_A(wWhichHPBar);
    hlcoord(2, 2, wTilemap);
    LD_B(0);
    CALL(aDrawBattleHPBar);
    RET;

}

void UpdateEnemyHPPal(void){
    LD_HL(wEnemyHPPal);
    CALL(aUpdateHPPal);
    RET;

}

void UpdateHPPal(void){
    LD_B_hl;
    CALL(aSetHPPal);
    LD_A_hl;
    CP_A_B;
    RET_Z ;
    JP(mFinishBattleAnim);

}

void Battle_DummyFunction(void){
//  called before placing either battler's nickname in the HUD
    RET;

}

void BattleMenu(void){
    XOR_A_A;
    LDH_addr_A(hBGMapMode);
    CALL(aLoadTempTilemapToTilemap);

    LD_A_addr(wBattleType);
    CP_A(BATTLETYPE_DEBUG);
    IF_Z goto ok;
    CP_A(BATTLETYPE_TUTORIAL);
    IF_Z goto ok;
    CALL(aEmptyBattleTextbox);
    CALL(aUpdateBattleHuds);
    CALL(aEmptyBattleTextbox);
    CALL(aLoadTilemapToTempTilemap);

ok:


loop:
    LD_A_addr(wBattleType);
    CP_A(BATTLETYPE_CONTEST);
    IF_NZ goto not_contest;
    FARCALL(aContestBattleMenu);
    goto next;

not_contest:

// Auto input: choose "ITEM"
    LD_A_addr(wInputType);
    OR_A_A;
    IF_Z goto skip_dude_pack_select;
    FARCALL(av_DudeAutoInput_DownA);

skip_dude_pack_select:
    CALL(aLoadBattleMenu2);
    RET_C ;


next:
    LD_A(0x1);
    LDH_addr_A(hBGMapMode);
    LD_A_addr(wBattleMenuCursorPosition);
    CP_A(0x1);
    JP_Z (mBattleMenu_Fight);
    CP_A(0x3);
    JP_Z (mBattleMenu_Pack);
    CP_A(0x2);
    JP_Z (mBattleMenu_PKMN);
    CP_A(0x4);
    JP_Z (mBattleMenu_Run);
    goto loop;

    return BattleMenu_Fight();
}

void BattleMenu_Fight(void){
    XOR_A_A;
    LD_addr_A(wNumFleeAttempts);
    CALL(aSafeLoadTempTilemapToTilemap);
    AND_A_A;
    RET;

}

void LoadBattleMenu2(void){
    CALL(aIsMobileBattle);
    IF_Z goto mobile;

    FARCALL(aLoadBattleMenu);
    AND_A_A;
    RET;


mobile:
    FARCALL(aMobile_LoadBattleMenu);
    LD_A_addr(wcd2b);
    AND_A_A;
    RET_Z ;

    LD_HL(wcd2a);
    BIT_hl(4);
    IF_NZ goto error;
    LD_HL(mBattleText_LinkErrorBattleCanceled);
    CALL(aStdBattleTextbox);
    LD_C(60);
    CALL(aDelayFrames);

error:
    SCF;
    RET;

}

void BattleMenu_Pack(void){
    LD_A_addr(wLinkMode);
    AND_A_A;
    JP_NZ (mBattleMenu_Pack_ItemsCantBeUsed);

    LD_A_addr(wInBattleTowerBattle);
    AND_A_A;
    JP_NZ (mBattleMenu_Pack_ItemsCantBeUsed);

    CALL(aLoadStandardMenuHeader);

    LD_A_addr(wBattleType);
    CP_A(BATTLETYPE_TUTORIAL);
    IF_Z goto tutorial;
    CP_A(BATTLETYPE_CONTEST);
    IF_Z goto contest;

    FARCALL(aBattlePack);
    LD_A_addr(wBattlePlayerAction);
    AND_A_A;  // BATTLEPLAYERACTION_USEMOVE?
    IF_Z goto didnt_use_item;
    goto got_item;


tutorial:
    FARCALL(aTutorialPack);
    LD_A(POKE_BALL);
    LD_addr_A(wCurItem);
    CALL(aDoItemEffect);
    goto got_item;


contest:
    LD_A(PARK_BALL);
    LD_addr_A(wCurItem);
    CALL(aDoItemEffect);


got_item:
    CALL(aBattleMenu_Pack_UseItem);
    RET;


didnt_use_item:
    CALL(aClearPalettes);
    CALL(aDelayFrame);
    CALL(av_LoadBattleFontsHPBar);
    CALL(aGetBattleMonBackpic);
    CALL(aGetEnemyMonFrontpic);
    CALL(aExitMenu);
    CALL(aWaitBGMap);
    CALL(aFinishBattleAnim);
    CALL(aLoadTilemapToTempTilemap);
    JP(mBattleMenu);


ItemsCantBeUsed:
    LD_HL(mBattleText_ItemsCantBeUsedHere);
    CALL(aStdBattleTextbox);
    JP(mBattleMenu);


UseItem:
    LD_A_addr(wWildMon);
    AND_A_A;
    IF_NZ goto run;
    CALLFAR(aCheckItemPocket);
    LD_A_addr(wItemAttributeValue);
    CP_A(BALL);
    IF_Z goto ball;
    CALL(aClearBGPalettes);


ball:
    XOR_A_A;
    LDH_addr_A(hBGMapMode);
    CALL(av_LoadBattleFontsHPBar);
    CALL(aClearSprites);
    LD_A_addr(wBattleType);
    CP_A(BATTLETYPE_TUTORIAL);
    IF_Z goto tutorial2;
    CALL(aGetBattleMonBackpic);


tutorial2:
    CALL(aGetEnemyMonFrontpic);
    LD_A(0x1);
    LD_addr_A(wMenuCursorY);
    CALL(aExitMenu);
    CALL(aUpdateBattleHUDs);
    CALL(aWaitBGMap);
    CALL(aLoadTilemapToTempTilemap);
    CALL(aClearWindowData);
    CALL(aFinishBattleAnim);
    AND_A_A;
    RET;


run:
    XOR_A_A;
    LD_addr_A(wWildMon);
    LD_A_addr(wBattleResult);
    AND_A(BATTLERESULT_BITMASK);
    LD_addr_A(wBattleResult);  // WIN
    CALL(aClearWindowData);
    CALL(aSetPalettes);
    SCF;
    RET;

}

void BattleMenu_PKMN(void){
    CALL(aLoadStandardMenuHeader);
    return BattleMenuPKMN_ReturnFromStats();
}

void BattleMenuPKMN_ReturnFromStats(void){
    CALL(aExitMenu);
    CALL(aLoadStandardMenuHeader);
    CALL(aClearBGPalettes);
    return BattleMenuPKMN_Loop();
}

void BattleMenuPKMN_Loop(void){
    CALL(aSetUpBattlePartyMenu_Loop);
    XOR_A_A;
    LD_addr_A(wPartyMenuActionText);
    CALL(aJumpToPartyMenuAndPrintText);
    CALL(aSelectBattleMon);
    IF_C goto Cancel;

loop:
    FARCALL(aFreezeMonIcons);
    CALL(aBattleMenuPKMN_Loop_GetMenu);
    IF_C goto PressedB;
    CALL(aPlaceHollowCursor);
    LD_A_addr(wMenuCursorY);
    CP_A(0x1);  // SWITCH
    JP_Z (mTryPlayerSwitch);
    CP_A(0x2);  // STATS
    IF_Z goto Stats;
    CP_A(0x3);  // CANCEL
    IF_Z goto Cancel;
    goto loop;


PressedB:
    CALL(aCheckMobileBattleError);
    IF_C goto Cancel;
    JR(mBattleMenuPKMN_Loop);


Stats:
    CALL(aBattle_StatsScreen);
    CALL(aCheckMobileBattleError);
    IF_C goto Cancel;
    JP(mBattleMenuPKMN_ReturnFromStats);


Cancel:
    CALL(aClearSprites);
    CALL(aClearPalettes);
    CALL(aDelayFrame);
    CALL(av_LoadHPBar);
    CALL(aCloseWindow);
    CALL(aLoadTilemapToTempTilemap);
    CALL(aGetMemSGBLayout);
    CALL(aSetPalettes);
    JP(mBattleMenu);


GetMenu:
    CALL(aIsMobileBattle);
    IF_Z goto mobile;
    FARCALL(aBattleMonMenu);
    RET;


mobile:
    FARCALL(aMobileBattleMonMenu);
    RET;

}

void Battle_StatsScreen(void){
    CALL(aDisableLCD);

    LD_HL(vTiles2 + LEN_2BPP_TILE * 0x31);
    LD_DE(vTiles0);
    LD_BC(0x11 * LEN_2BPP_TILE);
    CALL(aCopyBytes);

    LD_HL(vTiles2);
    LD_DE(vTiles0 + LEN_2BPP_TILE * 0x11);
    LD_BC(0x31 * LEN_2BPP_TILE);
    CALL(aCopyBytes);

    CALL(aEnableLCD);

    CALL(aClearSprites);
    CALL(aLowVolume);
    XOR_A_A;  // PARTYMON
    LD_addr_A(wMonType);
    FARCALL(aBattleStatsScreenInit);
    CALL(aMaxVolume);

    CALL(aDisableLCD);

    LD_HL(vTiles0);
    LD_DE(vTiles2 + LEN_2BPP_TILE * 0x31);
    LD_BC(0x11 * LEN_2BPP_TILE);
    CALL(aCopyBytes);

    LD_HL(vTiles0 + LEN_2BPP_TILE * 0x11);
    LD_DE(vTiles2);
    LD_BC(0x31 * LEN_2BPP_TILE);
    CALL(aCopyBytes);

    CALL(aEnableLCD);
    RET;

}

void TryPlayerSwitch(void){
    LD_A_addr(wCurBattleMon);
    LD_D_A;
    LD_A_addr(wCurPartyMon);
    CP_A_D;
    IF_NZ goto check_trapped;
    LD_HL(mBattleText_MonIsAlreadyOut);
    CALL(aStdBattleTextbox);
    JP(mBattleMenuPKMN_Loop);


check_trapped:
    LD_A_addr(wPlayerWrapCount);
    AND_A_A;
    IF_NZ goto trapped;
    LD_A_addr(wEnemySubStatus5);
    BIT_A(SUBSTATUS_CANT_RUN);
    IF_Z goto try_switch;


trapped:
    LD_HL(mBattleText_MonCantBeRecalled);
    CALL(aStdBattleTextbox);
    JP(mBattleMenuPKMN_Loop);


try_switch:
    CALL(aCheckIfCurPartyMonIsFitToFight);
    JP_Z (mBattleMenuPKMN_Loop);
    LD_A_addr(wCurBattleMon);
    LD_addr_A(wLastPlayerMon);
    LD_A(BATTLEPLAYERACTION_SWITCH);
    LD_addr_A(wBattlePlayerAction);
    CALL(aClearPalettes);
    CALL(aDelayFrame);
    CALL(aClearSprites);
    CALL(av_LoadHPBar);
    CALL(aCloseWindow);
    CALL(aGetMemSGBLayout);
    CALL(aSetPalettes);
    LD_A_addr(wCurPartyMon);
    LD_addr_A(wCurBattleMon);
    return PlayerSwitch();
}

void PlayerSwitch(void){
    LD_A(1);
    LD_addr_A(wPlayerIsSwitching);
    LD_A_addr(wLinkMode);
    AND_A_A;
    IF_Z goto not_linked;
    CALL(aLoadStandardMenuHeader);
    CALL(aLinkBattleSendReceiveAction);
    CALL(aCloseWindow);


not_linked:
    CALL(aParseEnemyAction);
    LD_A_addr(wLinkMode);
    AND_A_A;
    IF_NZ goto linked;


switch_:
    CALL(aBattleMonEntrance);
    AND_A_A;
    RET;


linked:
    LD_A_addr(wBattleAction);
    CP_A(BATTLEACTION_STRUGGLE);
    JP_Z (mPlayerSwitch_switch);
    CP_A(BATTLEACTION_SKIPTURN);
    JP_Z (mPlayerSwitch_switch);
    CP_A(BATTLEACTION_SWITCH1);
    JP_C (mPlayerSwitch_switch);
    CP_A(BATTLEACTION_FORFEIT);
    IF_NZ goto dont_run;
    CALL(aWildFled_EnemyFled_LinkBattleCanceled);
    RET;


dont_run:
    LDH_A_addr(hSerialConnectionStatus);
    CP_A(USING_EXTERNAL_CLOCK);
    IF_Z goto player_1;
    CALL(aBattleMonEntrance);
    CALL(aEnemyMonEntrance);
    AND_A_A;
    RET;


player_1:
    CALL(aEnemyMonEntrance);
    CALL(aBattleMonEntrance);
    AND_A_A;
    RET;

}

void EnemyMonEntrance(void){
    CALLFAR(aAI_Switch);
    CALL(aSetEnemyTurn);
    JP(mSpikesDamage);

}

void BattleMonEntrance(void){
    CALL(aWithdrawMonText);

    LD_C(50);
    CALL(aDelayFrames);

    LD_HL(wPlayerSubStatus4);
    RES_hl(SUBSTATUS_RAGE);

    CALL(aSetEnemyTurn);
    CALL(aPursuitSwitch);
    IF_C goto ok;
    CALL(aRecallPlayerMon);

ok:

    hlcoord(9, 7, wTilemap);
    LD_BC((5 << 8) | 11);
    CALL(aClearBox);

    LD_A_addr(wCurBattleMon);
    LD_addr_A(wCurPartyMon);
    CALL(aAddBattleParticipant);
    CALL(aInitBattleMon);
    CALL(aResetPlayerStatLevels);
    CALL(aSendOutMonText);
    CALL(aNewBattleMonStatus);
    CALL(aBreakAttraction);
    CALL(aSendOutPlayerMon);
    CALL(aEmptyBattleTextbox);
    CALL(aLoadTilemapToTempTilemap);
    CALL(aSetPlayerTurn);
    CALL(aSpikesDamage);
    LD_A(0x2);
    LD_addr_A(wMenuCursorY);
    RET;

}

void PassedBattleMonEntrance(void){
    LD_C(50);
    CALL(aDelayFrames);

    hlcoord(9, 7, wTilemap);
    LD_BC((5 << 8) | 11);
    CALL(aClearBox);

    LD_A_addr(wCurPartyMon);
    LD_addr_A(wCurBattleMon);
    CALL(aAddBattleParticipant);
    CALL(aInitBattleMon);
    XOR_A_A;  // FALSE
    LD_addr_A(wApplyStatLevelMultipliersToEnemy);
    CALL(aApplyStatLevelMultiplierOnAllStats);
    CALL(aSendOutPlayerMon);
    CALL(aEmptyBattleTextbox);
    CALL(aLoadTilemapToTempTilemap);
    CALL(aSetPlayerTurn);
    JP(mSpikesDamage);

}

void BattleMenu_Run(void){
    CALL(aSafeLoadTempTilemapToTilemap);
    LD_A(0x3);
    LD_addr_A(wMenuCursorY);
    LD_HL(wBattleMonSpeed);
    LD_DE(wEnemyMonSpeed);
    CALL(aTryToRunAwayFromBattle);
    LD_A(FALSE);
    LD_addr_A(wFailedToFlee);
    RET_C ;
    LD_A_addr(wBattlePlayerAction);
    AND_A_A;  // BATTLEPLAYERACTION_USEMOVE?
    RET_NZ ;
    JP(mBattleMenu);

}

void CheckAmuletCoin(void){
    LD_A_addr(wBattleMonItem);
    LD_B_A;
    CALLFAR(aGetItemHeldEffect);
    LD_A_B;
    CP_A(HELD_AMULET_COIN);
    RET_NZ ;
    LD_A(1);
    LD_addr_A(wAmuletCoin);
    RET;

}

void MoveSelectionScreen(void){
    CALL(aIsMobileBattle);
    IF_NZ goto not_mobile;
    FARCALL(aMobile_MoveSelectionScreen);
    RET;


not_mobile:
    LD_HL(wEnemyMonMoves);
    LD_A_addr(wMoveSelectionMenuType);
    DEC_A;
    IF_Z goto got_menu_type;
    DEC_A;
    IF_Z goto ether_elixer_menu;
    CALL(aCheckPlayerHasUsableMoves);
    RET_Z ;  // use Struggle
    LD_HL(wBattleMonMoves);
    goto got_menu_type;


ether_elixer_menu:
    LD_A(MON_MOVES);
    CALL(aGetPartyParamLocation);


got_menu_type:
    LD_DE(wListMoves_MoveIndicesBuffer);
    LD_BC(NUM_MOVES);
    CALL(aCopyBytes);
    XOR_A_A;
    LDH_addr_A(hBGMapMode);

    hlcoord(4, 17 - NUM_MOVES - 1, wTilemap);
    LD_B(4);
    LD_C(14);
    LD_A_addr(wMoveSelectionMenuType);
    CP_A(0x2);
    IF_NZ goto got_dims;
    hlcoord(4, 17 - NUM_MOVES - 1 - 4, wTilemap);
    LD_B(4);
    LD_C(14);

got_dims:
    CALL(aTextbox);

    hlcoord(6, 17 - NUM_MOVES, wTilemap);
    LD_A_addr(wMoveSelectionMenuType);
    CP_A(0x2);
    IF_NZ goto got_start_coord;
    hlcoord(6, 17 - NUM_MOVES - 4, wTilemap);

got_start_coord:
    LD_A(SCREEN_WIDTH);
    LD_addr_A(wListMovesLineSpacing);
    PREDEF(pListMoves);

    LD_B(5);
    LD_A_addr(wMoveSelectionMenuType);
    CP_A(0x2);
    LD_A(17 - NUM_MOVES);
    IF_NZ goto got_default_coord;
    LD_B(5);
    LD_A(17 - NUM_MOVES - 4);


got_default_coord:
    LD_addr_A(w2DMenuCursorInitY);
    LD_A_B;
    LD_addr_A(w2DMenuCursorInitX);
    LD_A_addr(wMoveSelectionMenuType);
    CP_A(0x1);
    IF_Z goto skip_inc;
    LD_A_addr(wCurMoveNum);
    INC_A;


skip_inc:
    LD_addr_A(wMenuCursorY);
    LD_A(1);
    LD_addr_A(wMenuCursorX);
    LD_A_addr(wNumMoves);
    INC_A;
    LD_addr_A(w2DMenuNumRows);
    LD_A(1);
    LD_addr_A(w2DMenuNumCols);
    LD_C(STATICMENU_ENABLE_LEFT_RIGHT | STATICMENU_ENABLE_START | STATICMENU_WRAP);
    LD_A_addr(wMoveSelectionMenuType);
    DEC_A;
    LD_B(D_DOWN | D_UP | A_BUTTON);
    IF_Z goto okay;
    DEC_A;
    LD_B(D_DOWN | D_UP | A_BUTTON | B_BUTTON);
    IF_Z goto okay;
    LD_A_addr(wLinkMode);
    AND_A_A;
    IF_NZ goto okay;
    LD_B(D_DOWN | D_UP | A_BUTTON | B_BUTTON | SELECT);


okay:
    LD_A_B;
    LD_addr_A(wMenuJoypadFilter);
    LD_A_C;
    LD_addr_A(w2DMenuFlags1);
    XOR_A_A;
    LD_addr_A(w2DMenuFlags2);
    LD_A(0x10);
    LD_addr_A(w2DMenuCursorOffsets);

menu_loop:
    LD_A_addr(wMoveSelectionMenuType);
    AND_A_A;
    IF_Z goto battle_player_moves;
    DEC_A;
    IF_NZ goto interpret_joypad;
    hlcoord(11, 14, wTilemap);
    LD_DE(mMoveSelectionScreen_empty_string);
    CALL(aPlaceString);
    goto interpret_joypad;


battle_player_moves:
    CALL(aMoveInfoBox);
    LD_A_addr(wSwappingMove);
    AND_A_A;
    IF_Z goto interpret_joypad;
    hlcoord(5, 13, wTilemap);
    LD_BC(SCREEN_WIDTH);
    DEC_A;
    CALL(aAddNTimes);
    LD_hl(0xec);


interpret_joypad:
    LD_A(0x1);
    LDH_addr_A(hBGMapMode);
    CALL(aScrollingMenuJoypad);
    BIT_A(D_UP_F);
    JP_NZ (mMoveSelectionScreen_pressed_up);
    BIT_A(D_DOWN_F);
    JP_NZ (mMoveSelectionScreen_pressed_down);
    BIT_A(SELECT_F);
    JP_NZ (mMoveSelectionScreen_pressed_select);
    BIT_A(B_BUTTON_F);
// A button
    PUSH_AF;

    XOR_A_A;
    LD_addr_A(wSwappingMove);
    LD_A_addr(wMenuCursorY);
    DEC_A;
    LD_addr_A(wMenuCursorY);
    LD_B_A;
    LD_A_addr(wMoveSelectionMenuType);
    DEC_A;
    IF_NZ goto not_enemy_moves_process_b;

    POP_AF;
    RET;


not_enemy_moves_process_b:
    DEC_A;
    LD_A_B;
    LD_addr_A(wCurMoveNum);
    IF_NZ goto use_move;

    POP_AF;
    RET;


use_move:
    POP_AF;
    RET_NZ ;

    LD_HL(wBattleMonPP);
    LD_A_addr(wMenuCursorY);
    LD_C_A;
    LD_B(0);
    ADD_HL_BC;
    LD_A_hl;
    AND_A(PP_MASK);
    IF_Z goto no_pp_left;
    LD_A_addr(wPlayerDisableCount);
    SWAP_A;
    AND_A(0xf);
    DEC_A;
    CP_A_C;
    IF_Z goto move_disabled;
    LD_A_addr(wUnusedPlayerLockedMove);
    AND_A_A;
    IF_NZ goto skip2;
    LD_A_addr(wMenuCursorY);
    LD_HL(wBattleMonMoves);
    LD_C_A;
    LD_B(0);
    ADD_HL_BC;
    LD_A_hl;


skip2:
    LD_addr_A(wCurPlayerMove);
    XOR_A_A;
    RET;


move_disabled:
    LD_HL(mBattleText_TheMoveIsDisabled);
    goto place_textbox_start_over;


no_pp_left:
    LD_HL(mBattleText_TheresNoPPLeftForThisMove);


place_textbox_start_over:
    CALL(aStdBattleTextbox);
    CALL(aSafeLoadTempTilemapToTilemap);
    JP(mMoveSelectionScreen);


empty_string:
    //db ['"@"'];


pressed_up:
    LD_A_addr(wMenuCursorY);
    AND_A_A;
    JP_NZ (mMoveSelectionScreen_menu_loop);
    LD_A_addr(wNumMoves);
    INC_A;
    LD_addr_A(wMenuCursorY);
    JP(mMoveSelectionScreen_menu_loop);


pressed_down:
    LD_A_addr(wMenuCursorY);
    LD_B_A;
    LD_A_addr(wNumMoves);
    INC_A;
    INC_A;
    CP_A_B;
    JP_NZ (mMoveSelectionScreen_menu_loop);
    LD_A(0x1);
    LD_addr_A(wMenuCursorY);
    JP(mMoveSelectionScreen_menu_loop);


pressed_select:
    LD_A_addr(wSwappingMove);
    AND_A_A;
    IF_Z goto start_swap;
    LD_HL(wBattleMonMoves);
    CALL(aMoveSelectionScreen_swap_bytes);
    LD_HL(wBattleMonPP);
    CALL(aMoveSelectionScreen_swap_bytes);
    LD_HL(wPlayerDisableCount);
    LD_A_hl;
    SWAP_A;
    AND_A(0xf);
    LD_B_A;
    LD_A_addr(wMenuCursorY);
    CP_A_B;
    IF_NZ goto not_swapping_disabled_move;
    LD_A_hl;
    AND_A(0xf);
    LD_B_A;
    LD_A_addr(wSwappingMove);
    SWAP_A;
    ADD_A_B;
    LD_hl_A;
    goto swap_moves_in_party_struct;


not_swapping_disabled_move:
    LD_A_addr(wSwappingMove);
    CP_A_B;
    IF_NZ goto swap_moves_in_party_struct;
    LD_A_hl;
    AND_A(0xf);
    LD_B_A;
    LD_A_addr(wMenuCursorY);
    SWAP_A;
    ADD_A_B;
    LD_hl_A;


swap_moves_in_party_struct:
//  Fixes the COOLTRAINER glitch
    LD_A_addr(wPlayerSubStatus5);
    BIT_A(SUBSTATUS_TRANSFORMED);
    IF_NZ goto transformed;
    LD_HL(wPartyMon1Moves);
    LD_A_addr(wCurBattleMon);
    CALL(aGetPartyLocation);
    PUSH_HL;
    CALL(aMoveSelectionScreen_swap_bytes);
    POP_HL;
    LD_BC(MON_PP - MON_MOVES);
    ADD_HL_BC;
    CALL(aMoveSelectionScreen_swap_bytes);


transformed:
    XOR_A_A;
    LD_addr_A(wSwappingMove);
    JP(mMoveSelectionScreen);


swap_bytes:
    PUSH_HL;
    LD_A_addr(wSwappingMove);
    DEC_A;
    LD_C_A;
    LD_B(0);
    ADD_HL_BC;
    LD_D_H;
    LD_E_L;
    POP_HL;
    LD_A_addr(wMenuCursorY);
    DEC_A;
    LD_C_A;
    LD_B(0);
    ADD_HL_BC;
    LD_A_de;
    LD_B_hl;
    LD_hl_A;
    LD_A_B;
    LD_de_A;
    RET;


start_swap:
    LD_A_addr(wMenuCursorY);
    LD_addr_A(wSwappingMove);
    JP(mMoveSelectionScreen);

}

void MoveInfoBox(void){
    XOR_A_A;
    LDH_addr_A(hBGMapMode);

    hlcoord(0, 8, wTilemap);
    LD_B(3);
    LD_C(9);
    CALL(aTextbox);
    CALL(aMobileTextBorder);

    LD_A_addr(wPlayerDisableCount);
    AND_A_A;
    IF_Z goto not_disabled;

    SWAP_A;
    AND_A(0xf);
    LD_B_A;
    LD_A_addr(wMenuCursorY);
    CP_A_B;
    IF_NZ goto not_disabled;

    hlcoord(1, 10, wTilemap);
    LD_DE(mMoveInfoBox_Disabled);
    CALL(aPlaceString);
    goto done;


not_disabled:
    LD_HL(wMenuCursorY);
    DEC_hl;
    CALL(aSetPlayerTurn);
    LD_HL(wBattleMonMoves);
    LD_A_addr(wMenuCursorY);
    LD_C_A;
    LD_B(0);
    ADD_HL_BC;
    LD_A_hl;
    LD_addr_A(wCurPlayerMove);

    LD_A_addr(wCurBattleMon);
    LD_addr_A(wCurPartyMon);
    LD_A(WILDMON);
    LD_addr_A(wMonType);
    CALLFAR(aGetMaxPPOfMove);

    LD_HL(wMenuCursorY);
    LD_C_hl;
    INC_hl;
    LD_B(0);
    LD_HL(wBattleMonPP);
    ADD_HL_BC;
    LD_A_hl;
    AND_A(PP_MASK);
    LD_addr_A(wStringBuffer1);
    CALL(aMoveInfoBox_PrintPP);

    hlcoord(1, 9, wTilemap);
    LD_DE(mMoveInfoBox_Type);
    CALL(aPlaceString);

    hlcoord(7, 11, wTilemap);
    LD_hl(0xf3);

    CALLFAR(aUpdateMoveData);
    LD_A_addr(wPlayerMoveStruct + MOVE_ANIM);
    LD_B_A;
    hlcoord(2, 10, wTilemap);
    PREDEF(pPrintMoveType);


done:
    RET;


Disabled:
    //db ['"Disabled!@"'];

Type:
    //db ['"TYPE/@"'];


PrintPP:
    hlcoord(5, 11, wTilemap);
    LD_A_addr(wLinkMode);  // What's the point of this check?
    CP_A(LINK_MOBILE);
    IF_C goto ok;
    hlcoord(5, 11, wTilemap);

ok:
    PUSH_HL;
    LD_DE(wStringBuffer1);
    LD_BC((1 << 8) | 2);
    CALL(aPrintNum);
    POP_HL;
    INC_HL;
    INC_HL;
    LD_hl(0xf3);
    INC_HL;
    LD_DE(wNamedObjectIndex);
    LD_BC((1 << 8) | 2);
    CALL(aPrintNum);
    RET;

}

void CheckPlayerHasUsableMoves(void){
    LD_A(STRUGGLE);
    LD_addr_A(wCurPlayerMove);
    LD_A_addr(wPlayerDisableCount);
    AND_A_A;
    LD_HL(wBattleMonPP);
    IF_NZ goto disabled;

    LD_A_hli;
    OR_A_hl;
    INC_HL;
    OR_A_hl;
    INC_HL;
    OR_A_hl;
    AND_A(PP_MASK);
    RET_NZ ;
    goto force_struggle;


disabled:
    SWAP_A;
    AND_A(0xf);
    LD_B_A;
    LD_D(NUM_MOVES + 1);
    XOR_A_A;

loop:
    DEC_D;
    IF_Z goto done;
    LD_C_hl;
    INC_HL;
    DEC_B;
    IF_Z goto loop;
    OR_A_C;
    goto loop;


done:
// Bug: this will result in a move with PP Up confusing the game.
    AND_A_A;  // should be "and PP_MASK"
    RET_NZ ;


force_struggle:
    LD_HL(mBattleText_MonHasNoMovesLeft);
    CALL(aStdBattleTextbox);
    LD_C(60);
    CALL(aDelayFrames);
    XOR_A_A;
    RET;

}

void ParseEnemyAction(void){
    LD_A_addr(wEnemyIsSwitching);
    AND_A_A;
    RET_NZ ;
    LD_A_addr(wLinkMode);
    AND_A_A;
    IF_Z goto not_linked;
    CALL(aEmptyBattleTextbox);
    CALL(aLoadTilemapToTempTilemap);
    LD_A_addr(wBattlePlayerAction);
    AND_A_A;  // BATTLEPLAYERACTION_USEMOVE?
    CALL_Z (aLinkBattleSendReceiveAction);
    CALL(aSafeLoadTempTilemapToTilemap);
    LD_A_addr(wBattleAction);
    CP_A(BATTLEACTION_STRUGGLE);
    JP_Z (mParseEnemyAction_struggle);
    CP_A(BATTLEACTION_SKIPTURN);
    JP_Z (mParseEnemyAction_skip_turn);
    CP_A(BATTLEACTION_SWITCH1);
    JP_NC (mResetVarsForSubstatusRage);
    LD_addr_A(wCurEnemyMoveNum);
    LD_C_A;
    LD_A_addr(wEnemySubStatus1);
    BIT_A(SUBSTATUS_ROLLOUT);
    JP_NZ (mParseEnemyAction_skip_load);
    LD_A_addr(wEnemySubStatus3);
    AND_A(1 << SUBSTATUS_CHARGED | 1 << SUBSTATUS_RAMPAGE | 1 << SUBSTATUS_BIDE);
    JP_NZ (mParseEnemyAction_skip_load);

    LD_HL(wEnemySubStatus5);
    BIT_hl(SUBSTATUS_ENCORED);
    LD_A_addr(wLastEnemyMove);
    JP_NZ (mParseEnemyAction_finish);
    LD_HL(wEnemyMonMoves);
    LD_B(0);
    ADD_HL_BC;
    LD_A_hl;
    JP(mParseEnemyAction_finish);


not_linked:
    LD_HL(wEnemySubStatus5);
    BIT_hl(SUBSTATUS_ENCORED);
    IF_Z goto skip_encore;
    LD_A_addr(wLastEnemyMove);
    JP(mParseEnemyAction_finish);


skip_encore:
    CALL(aCheckEnemyLockedIn);
    JP_NZ (mResetVarsForSubstatusRage);
    goto continue_;


skip_turn:
    LD_A(0xff);
    goto finish;


continue_:
    LD_HL(wEnemyMonMoves);
    LD_DE(wEnemyMonPP);
    LD_B(NUM_MOVES);

loop:
    LD_A_hl;
    AND_A_A;
    JP_Z (mParseEnemyAction_struggle);
    LD_A_addr(wEnemyDisabledMove);
    CP_A_hl;
    IF_Z goto disabled;
    LD_A_de;
    AND_A(PP_MASK);
    IF_NZ goto enough_pp;


disabled:
    INC_HL;
    INC_DE;
    DEC_B;
    IF_NZ goto loop;
    goto struggle;


enough_pp:
    LD_A_addr(wBattleMode);
    DEC_A;
    IF_NZ goto skip_load;
//  wild

loop2:
    LD_HL(wEnemyMonMoves);
    CALL(aBattleRandom);
    maskbits(NUM_MOVES, 0);
    LD_C_A;
    LD_B(0);
    ADD_HL_BC;
    LD_A_addr(wEnemyDisableCount);
    SWAP_A;
    AND_A(0xf);
    DEC_A;
    CP_A_C;
    IF_Z goto loop2;
    LD_A_hl;
    AND_A_A;
    IF_Z goto loop2;
    LD_HL(wEnemyMonPP);
    ADD_HL_BC;
    LD_B_A;
    LD_A_hl;
    AND_A(PP_MASK);
    IF_Z goto loop2;
    LD_A_C;
    LD_addr_A(wCurEnemyMoveNum);
    LD_A_B;


finish:
    LD_addr_A(wCurEnemyMove);


skip_load:
    CALL(aSetEnemyTurn);
    CALLFAR(aUpdateMoveData);
    CALL(aCheckEnemyLockedIn);
    IF_NZ goto raging;
    XOR_A_A;
    LD_addr_A(wEnemyCharging);


raging:
    LD_A_addr(wEnemyMoveStruct + MOVE_EFFECT);
    CP_A(EFFECT_FURY_CUTTER);
    IF_Z goto fury_cutter;
    XOR_A_A;
    LD_addr_A(wEnemyFuryCutterCount);


fury_cutter:
    LD_A_addr(wEnemyMoveStruct + MOVE_EFFECT);
    CP_A(EFFECT_RAGE);
    IF_Z goto no_rage;
    LD_HL(wEnemySubStatus4);
    RES_hl(SUBSTATUS_RAGE);
    XOR_A_A;
    LD_addr_A(wEnemyRageCounter);


no_rage:
    LD_A_addr(wEnemyMoveStruct + MOVE_EFFECT);
    CP_A(EFFECT_PROTECT);
    RET_Z ;
    CP_A(EFFECT_ENDURE);
    RET_Z ;
    XOR_A_A;
    LD_addr_A(wEnemyProtectCount);
    RET;


struggle:
    LD_A(STRUGGLE);
    goto finish;

    return ResetVarsForSubstatusRage();
}

void ResetVarsForSubstatusRage(void){
    XOR_A_A;
    LD_addr_A(wEnemyFuryCutterCount);
    LD_addr_A(wEnemyProtectCount);
    LD_addr_A(wEnemyRageCounter);
    LD_HL(wEnemySubStatus4);
    RES_hl(SUBSTATUS_RAGE);
    RET;

}

void CheckEnemyLockedIn(void){
    LD_A_addr(wEnemySubStatus4);
    AND_A(1 << SUBSTATUS_RECHARGE);
    RET_NZ ;

    LD_HL(wEnemySubStatus3);
    LD_A_hl;
    AND_A(1 << SUBSTATUS_CHARGED | 1 << SUBSTATUS_RAMPAGE | 1 << SUBSTATUS_BIDE);
    RET_NZ ;

    LD_HL(wEnemySubStatus1);
    BIT_hl(SUBSTATUS_ROLLOUT);
    RET;

}

void LinkBattleSendReceiveAction(void){
    FARCALL(av_LinkBattleSendReceiveAction);
    RET;

}

void LoadEnemyMon(void){
//  Initialize enemy monster parameters
//  To do this we pull the species from wTempEnemyMonSpecies

//  Notes:
//    BattleRandom is used to ensure sync between Game Boys

//  Clear the whole enemy mon struct (wEnemyMon)
    XOR_A_A;
    LD_HL(wEnemyMonSpecies);
    LD_BC(wEnemyMonEnd - wEnemyMon);
    CALL(aByteFill);

//  We don't need to be here if we're in a link battle
    LD_A_addr(wLinkMode);
    AND_A_A;
    JP_NZ (mInitEnemyMon);

//  and also not in a BattleTower-Battle
    LD_A_addr(wInBattleTowerBattle);
    BIT_A(0);
    JP_NZ (mInitEnemyMon);

//  Make sure everything knows what species we're working with
    LD_A_addr(wTempEnemyMonSpecies);
    LD_addr_A(wEnemyMonSpecies);
    LD_addr_A(wCurSpecies);
    LD_addr_A(wCurPartySpecies);

//  Grab the BaseData for this species
    CALL(aGetBaseData);

//  Let's get the item:

//  Is the item predetermined?
    LD_A_addr(wBattleMode);
    DEC_A;
    IF_Z goto WildItem;

//  If we're in a trainer battle, the item is in the party struct
    LD_A_addr(wCurPartyMon);
    LD_HL(wOTPartyMon1Item);
    CALL(aGetPartyLocation);  // bc = PartyMon[wCurPartyMon] - wPartyMons
    LD_A_hl;
    goto UpdateItem;


WildItem:
//  In a wild battle, we pull from the item slots in BaseData

//  Force Item1
//  Used for Ho-Oh, Lugia and Snorlax encounters
    LD_A_addr(wBattleType);
    CP_A(BATTLETYPE_FORCEITEM);
    LD_A_addr(wBaseItem1);
    IF_Z goto UpdateItem;

//  Failing that, it's all up to chance
//   Effective chances:
//     75% None
//     23% Item1
//      2% Item2

//  25% chance of getting an item
    CALL(aBattleRandom);
    CP_A(75 percent + 1);
    LD_A(NO_ITEM);
    IF_C goto UpdateItem;

//  From there, an 8% chance for Item2
    CALL(aBattleRandom);
    CP_A(8 percent);  // 8% of 25% = 2% Item2
    LD_A_addr(wBaseItem1);
    IF_NC goto UpdateItem;
    LD_A_addr(wBaseItem2);


UpdateItem:
    LD_addr_A(wEnemyMonItem);

//  Initialize DVs

//  If we're in a trainer battle, DVs are predetermined
    LD_A_addr(wBattleMode);
    AND_A_A;
    IF_Z goto InitDVs;

    LD_A_addr(wEnemySubStatus5);
    BIT_A(SUBSTATUS_TRANSFORMED);
    IF_Z goto InitDVs;

//  Unknown
    LD_HL(wEnemyBackupDVs);
    LD_DE(wEnemyMonDVs);
    LD_A_hli;
    LD_de_A;
    INC_DE;
    LD_A_hl;
    LD_de_A;
    JP(mLoadEnemyMon_Happiness);


InitDVs:
//  Trainer DVs

//  All trainers have preset DVs, determined by class
//  See GetTrainerDVs for more on that
    FARCALL(aGetTrainerDVs);
//  These are the DVs we'll use if we're actually in a trainer battle
    LD_A_addr(wBattleMode);
    DEC_A;
    IF_NZ goto UpdateDVs;

//  Wild DVs
//  Here's where the fun starts

//  Roaming monsters (Entei, Raikou) work differently
//  They have their own structs, which are shorter than normal
    LD_A_addr(wBattleType);
    CP_A(BATTLETYPE_ROAMING);
    IF_NZ goto NotRoaming;

//  Grab HP
    CALL(aGetRoamMonHP);
    LD_A_hl;
//  Check if the HP has been initialized
    AND_A_A;
//  We'll do something with the result in a minute
    PUSH_AF;

//  Grab DVs
    CALL(aGetRoamMonDVs);
    INC_HL;
    LD_A_hld;
    LD_C_A;
    LD_B_hl;

//  Get back the result of our check
    POP_AF;
//  If the RoamMon struct has already been initialized, we're done
    IF_NZ goto UpdateDVs;

//  If it hasn't, we need to initialize the DVs
//  (HP is initialized at the end of the battle)
    CALL(aGetRoamMonDVs);
    INC_HL;
    CALL(aBattleRandom);
    LD_hld_A;
    LD_C_A;
    CALL(aBattleRandom);
    LD_hl_A;
    LD_B_A;
//  We're done with DVs
    goto UpdateDVs;


NotRoaming:
//  Register a contains wBattleType

//  Forced shiny battle type
//  Used by Red Gyarados at Lake of Rage
    CP_A(BATTLETYPE_SHINY);
    IF_NZ goto GenerateDVs;

    LD_B(ATKDEFDV_SHINY);  // $ea
    LD_C(SPDSPCDV_SHINY);  // $aa
    goto UpdateDVs;


GenerateDVs:
//  Generate new random DVs
    CALL(aBattleRandom);
    LD_B_A;
    CALL(aBattleRandom);
    LD_C_A;


UpdateDVs:
//  Input DVs in register bc
    LD_HL(wEnemyMonDVs);
    LD_A_B;
    LD_hli_A;
    LD_hl_C;

//  We've still got more to do if we're dealing with a wild monster
    LD_A_addr(wBattleMode);
    DEC_A;
    IF_NZ goto Happiness;

//  Species-specfic:

//  Unown
    LD_A_addr(wTempEnemyMonSpecies);
    CP_A(UNOWN);
    IF_NZ goto Magikarp;

//  Get letter based on DVs
    LD_HL(wEnemyMonDVs);
    PREDEF(pGetUnownLetter);
//  Can't use any letters that haven't been unlocked
//  If combined with forced shiny battletype, causes an infinite loop
    CALL(aCheckUnownLetter);
    IF_C goto GenerateDVs;  // try again


Magikarp:
//  These filters are untranslated.
//  They expect at wMagikarpLength a 2-byte value in mm,
//  but the value is in feet and inches (one byte each).

//  The first filter is supposed to make very large Magikarp even rarer,
//  by targeting those 1600 mm (= 5'3") or larger.
//  After the conversion to feet, it is unable to target any,
//  since the largest possible Magikarp is 5'3", and $0503 = 1283 mm.
    LD_A_addr(wTempEnemyMonSpecies);
    CP_A(MAGIKARP);
    IF_NZ goto Happiness;

//  Get Magikarp's length
    LD_DE(wEnemyMonDVs);
    LD_BC(wPlayerID);
    CALLFAR(aCalcMagikarpLength);

//  No reason to keep going if length > 1536 mm (i.e. if HIGH(length) > 6 feet)
    LD_A_addr(wMagikarpLength);
    CP_A(HIGH(1536));  // should be "cp 5", since 1536 mm = 5'0", but HIGH(1536) = 6
    IF_NZ goto CheckMagikarpArea;

//  5% chance of skipping both size checks
    CALL(aRandom);
    CP_A(5 percent);
    IF_C goto CheckMagikarpArea;
//  Try again if length >= 1616 mm (i.e. if LOW(length) >= 4 inches)
    LD_A_addr(wMagikarpLength + 1);
    CP_A(LOW(1616));  // should be "cp 4", since 1616 mm = 5'4", but LOW(1616) = 80
    IF_NC goto GenerateDVs;

//  20% chance of skipping this check
    CALL(aRandom);
    CP_A(20 percent - 1);
    IF_C goto CheckMagikarpArea;
//  Try again if length >= 1600 mm (i.e. if LOW(length) >= 3 inches)
    LD_A_addr(wMagikarpLength + 1);
    CP_A(LOW(1600));  // should be "cp 3", since 1600 mm = 5'3", but LOW(1600) = 64
    IF_NC goto GenerateDVs;


CheckMagikarpArea:
//  The "jr z" checks are supposed to be "jr nz".

//  Instead, all maps in GROUP_LAKE_OF_RAGE (Mahogany area)
//  and Routes 20 and 44 are treated as Lake of Rage.

//  This also means Lake of Rage Magikarp can be smaller than ones
//  caught elsewhere rather than the other way around.

//  Intended behavior enforces a minimum size at Lake of Rage.
//  The real behavior prevents a minimum size in the Lake of Rage area.

//  Moreover, due to the check not being translated to feet+inches, all Magikarp
//  smaller than 4'0" may be caught by the filter, a lot more than intended.
    LD_A_addr(wMapGroup);
    CP_A(GROUP_LAKE_OF_RAGE);
    IF_Z goto Happiness;
    LD_A_addr(wMapNumber);
    CP_A(MAP_LAKE_OF_RAGE);
    IF_Z goto Happiness;
//  40% chance of not flooring
    CALL(aRandom);
    CP_A(39 percent + 1);
    IF_C goto Happiness;
//  Try again if length < 1024 mm (i.e. if HIGH(length) < 3 feet)
    LD_A_addr(wMagikarpLength);
    CP_A(HIGH(1024));  // should be "cp 3", since 1024 mm = 3'4", but HIGH(1024) = 4
    IF_C goto GenerateDVs;  // try again

//  Finally done with DVs


Happiness:
//  Set happiness
    LD_A(BASE_HAPPINESS);
    LD_addr_A(wEnemyMonHappiness);
//  Set level
    LD_A_addr(wCurPartyLevel);
    LD_addr_A(wEnemyMonLevel);
//  Fill stats
    LD_DE(wEnemyMonMaxHP);
    LD_B(FALSE);
    LD_HL(wEnemyMonDVs - (MON_DVS - MON_STAT_EXP + 1));
    PREDEF(pCalcMonStats);

//  If we're in a trainer battle,
//  get the rest of the parameters from the party struct
    LD_A_addr(wBattleMode);
    CP_A(TRAINER_BATTLE);
    IF_Z goto OpponentParty;

//  If we're in a wild battle, check wild-specific stuff
    AND_A_A;
    IF_Z goto TreeMon;

    LD_A_addr(wEnemySubStatus5);
    BIT_A(SUBSTATUS_TRANSFORMED);
    JP_NZ (mLoadEnemyMon_Moves);


TreeMon:
//  If we're headbutting trees, some monsters enter battle asleep
    CALL(aCheckSleepingTreeMon);
    LD_A(TREEMON_SLEEP_TURNS);
    IF_C goto UpdateStatus;
//  Otherwise, no status
    XOR_A_A;


UpdateStatus:
    LD_HL(wEnemyMonStatus);
    LD_hli_A;

//  Unused byte
    XOR_A_A;
    LD_hli_A;

//  Full HP..
    LD_A_addr(wEnemyMonMaxHP);
    LD_hli_A;
    LD_A_addr(wEnemyMonMaxHP + 1);
    LD_hl_A;

//  ..unless it's a RoamMon
    LD_A_addr(wBattleType);
    CP_A(BATTLETYPE_ROAMING);
    IF_NZ goto Moves;

//  Grab HP
    CALL(aGetRoamMonHP);
    LD_A_hl;
//  Check if it's been initialized again
    AND_A_A;
    IF_Z goto InitRoamHP;
//  Update from the struct if it has
    LD_A_hl;
    LD_addr_A(wEnemyMonHP + 1);
    goto Moves;


InitRoamHP:
//  HP only uses the lo byte in the RoamMon struct since
//  Raikou and Entei will have < 256 hp at level 40
    LD_A_addr(wEnemyMonHP + 1);
    LD_hl_A;
    goto Moves;


OpponentParty:
//  Get HP from the party struct
    LD_HL((wOTPartyMon1HP + 1));
    LD_A_addr(wCurPartyMon);
    CALL(aGetPartyLocation);
    LD_A_hld;
    LD_addr_A(wEnemyMonHP + 1);
    LD_A_hld;
    LD_addr_A(wEnemyMonHP);

//  Make sure everything knows which monster the opponent is using
    LD_A_addr(wCurPartyMon);
    LD_addr_A(wCurOTMon);

//  Get status from the party struct
    DEC_HL;
    LD_A_hl;  // OTPartyMonStatus
    LD_addr_A(wEnemyMonStatus);


Moves:
    LD_HL(wBaseType1);
    LD_DE(wEnemyMonType1);
    LD_A_hli;
    LD_de_A;
    INC_DE;
    LD_A_hl;
    LD_de_A;

//  Get moves
    LD_DE(wEnemyMonMoves);
//  Are we in a trainer battle?
    LD_A_addr(wBattleMode);
    CP_A(TRAINER_BATTLE);
    IF_NZ goto WildMoves;
//  Then copy moves from the party struct
    LD_HL(wOTPartyMon1Moves);
    LD_A_addr(wCurPartyMon);
    CALL(aGetPartyLocation);
    LD_BC(NUM_MOVES);
    CALL(aCopyBytes);
    goto PP;


WildMoves:
//  Clear wEnemyMonMoves
    XOR_A_A;
    LD_H_D;
    LD_L_E;
    LD_hli_A;
    LD_hli_A;
    LD_hli_A;
    LD_hl_A;
    LD_addr_A(wSkipMovesBeforeLevelUp);
//  Fill moves based on level
    PREDEF(pFillMoves);


PP:
//  Trainer battle?
    LD_A_addr(wBattleMode);
    CP_A(TRAINER_BATTLE);
    IF_Z goto TrainerPP;

//  Fill wild PP
    LD_HL(wEnemyMonMoves);
    LD_DE(wEnemyMonPP);
    PREDEF(pFillPP);
    goto Finish;


TrainerPP:
//  Copy PP from the party struct
    LD_HL(wOTPartyMon1PP);
    LD_A_addr(wCurPartyMon);
    CALL(aGetPartyLocation);
    LD_DE(wEnemyMonPP);
    LD_BC(NUM_MOVES);
    CALL(aCopyBytes);


Finish:
//  Copy the first five base stats (the enemy mon's base Sp. Atk
//  is also used to calculate Sp. Def stat experience)
    LD_HL(wBaseStats);
    LD_DE(wEnemyMonBaseStats);
    LD_B(NUM_STATS - 1);

loop:
    LD_A_hli;
    LD_de_A;
    INC_DE;
    DEC_B;
    IF_NZ goto loop;

    LD_A_addr(wBaseCatchRate);
    LD_de_A;
    INC_DE;

    LD_A_addr(wBaseExp);
    LD_de_A;

    LD_A_addr(wTempEnemyMonSpecies);
    LD_addr_A(wNamedObjectIndex);

    CALL(aGetPokemonName);

//  Did we catch it?
    LD_A_addr(wBattleMode);
    AND_A_A;
    RET_Z ;

//  Update enemy nickname
    LD_HL(wStringBuffer1);
    LD_DE(wEnemyMonNickname);
    LD_BC(MON_NAME_LENGTH);
    CALL(aCopyBytes);

//  Saw this mon
    LD_A_addr(wTempEnemyMonSpecies);
    DEC_A;
    LD_C_A;
    LD_B(SET_FLAG);
    LD_HL(wPokedexSeen);
    PREDEF(pSmallFarFlagAction);

    LD_HL(wEnemyMonStats);
    LD_DE(wEnemyStats);
    LD_BC(NUM_EXP_STATS * 2);
    CALL(aCopyBytes);

    RET;

}

void CheckSleepingTreeMon(void){
//  Return carry if species is in the list
//  for the current time of day

//  Don't do anything if this isn't a tree encounter
    LD_A_addr(wBattleType);
    CP_A(BATTLETYPE_TREE);
    IF_NZ goto NotSleeping;

//  Get list for the time of day
    LD_HL(mAsleepTreeMonsMorn);
    LD_A_addr(wTimeOfDay);
    CP_A(DAY_F);
    IF_C goto Check;
    LD_HL(mAsleepTreeMonsDay);
    IF_Z goto Check;
    LD_HL(mAsleepTreeMonsNite);


Check:
    LD_A_addr(wTempEnemyMonSpecies);
    LD_DE(1);  // length of species id
    CALL(aIsInArray);
//  If it's a match, the opponent is asleep
    RET_C ;


NotSleeping:
    AND_A_A;
    RET;

// INCLUDE "data/wild/treemons_asleep.asm"

    return CheckUnownLetter();
}

void CheckUnownLetter(void){
//  Return carry if the Unown letter hasn't been unlocked yet

    LD_A_addr(wUnlockedUnowns);
    LD_C_A;
    LD_DE(0);


loop:

//  Don't check this set unless it's been unlocked
    SRL_C;
    IF_NC goto next;

//  Is our letter in the set?
    LD_HL(mUnlockedUnownLetterSets);
    ADD_HL_DE;
    LD_A_hli;
    LD_H_hl;
    LD_L_A;

    PUSH_DE;
    LD_A_addr(wUnownLetter);
    LD_DE(1);
    PUSH_BC;
    CALL(aIsInArray);
    POP_BC;
    POP_DE;

    IF_C goto match;


next:
//  Make sure we haven't gone past the end of the table
    INC_E;
    INC_E;
    LD_A_E;
    CP_A(aUnlockedUnownLetterSets_End - aUnlockedUnownLetterSets);
    IF_C goto loop;

//  Hasn't been unlocked, or the letter is invalid
    SCF;
    RET;


match:
//  Valid letter
    AND_A_A;
    RET;

// INCLUDE "data/wild/unlocked_unowns.asm"

    return SwapBattlerLevels();
}

void SwapBattlerLevels(void){
//  //  unreferenced
    PUSH_BC;
    LD_A_addr(wBattleMonLevel);
    LD_B_A;
    LD_A_addr(wEnemyMonLevel);
    LD_addr_A(wBattleMonLevel);
    LD_A_B;
    LD_addr_A(wEnemyMonLevel);
    POP_BC;
    RET;

}

void BattleWinSlideInEnemyTrainerFrontpic(void){
    XOR_A_A;
    LD_addr_A(wTempEnemyMonSpecies);
    CALL(aFinishBattleAnim);
    LD_A_addr(wOtherTrainerClass);
    LD_addr_A(wTrainerClass);
    LD_DE(vTiles2);
    CALLFAR(aGetTrainerPic);
    hlcoord(19, 0, wTilemap);
    LD_C(0);


outer_loop:
    INC_C;
    LD_A_C;
    CP_A(7);
    RET_Z ;
    XOR_A_A;
    LDH_addr_A(hBGMapMode);
    LDH_addr_A(hBGMapThird);
    LD_D(0x0);
    PUSH_BC;
    PUSH_HL;


inner_loop:
    CALL(aBattleWinSlideInEnemyTrainerFrontpic_CopyColumn);
    INC_HL;
    LD_A(7);
    ADD_A_D;
    LD_D_A;
    DEC_C;
    IF_NZ goto inner_loop;

    LD_A(0x1);
    LDH_addr_A(hBGMapMode);
    LD_C(4);
    CALL(aDelayFrames);
    POP_HL;
    POP_BC;
    DEC_HL;
    goto outer_loop;


CopyColumn:
    PUSH_HL;
    PUSH_DE;
    PUSH_BC;
    LD_E(7);


loop:
    LD_hl_D;
    LD_BC(SCREEN_WIDTH);
    ADD_HL_BC;
    INC_D;
    DEC_E;
    IF_NZ goto loop;

    POP_BC;
    POP_DE;
    POP_HL;
    RET;

}

void ApplyStatusEffectOnPlayerStats(void){
    LD_A(1);
    JR(mApplyStatusEffectOnStats);

}

void ApplyStatusEffectOnEnemyStats(void){
    XOR_A_A;

    return ApplyStatusEffectOnStats();
}

void ApplyStatusEffectOnStats(void){
    LDH_addr_A(hBattleTurn);
    CALL(aApplyPrzEffectOnSpeed);
    JP(mApplyBrnEffectOnAttack);

}

void ApplyPrzEffectOnSpeed(void){
    LDH_A_addr(hBattleTurn);
    AND_A_A;
    IF_Z goto enemy;
    LD_A_addr(wBattleMonStatus);
    AND_A(1 << PAR);
    RET_Z ;
    LD_HL(wBattleMonSpeed + 1);
    LD_A_hld;
    LD_B_A;
    LD_A_hl;
    SRL_A;
    RR_B;
    SRL_A;
    RR_B;
    LD_hli_A;
    OR_A_B;
    IF_NZ goto player_ok;
    LD_B(0x1);  // min speed


player_ok:
    LD_hl_B;
    RET;


enemy:
    LD_A_addr(wEnemyMonStatus);
    AND_A(1 << PAR);
    RET_Z ;
    LD_HL(wEnemyMonSpeed + 1);
    LD_A_hld;
    LD_B_A;
    LD_A_hl;
    SRL_A;
    RR_B;
    SRL_A;
    RR_B;
    LD_hli_A;
    OR_A_B;
    IF_NZ goto enemy_ok;
    LD_B(0x1);  // min speed


enemy_ok:
    LD_hl_B;
    RET;

}

void ApplyBrnEffectOnAttack(void){
    LDH_A_addr(hBattleTurn);
    AND_A_A;
    IF_Z goto enemy;
    LD_A_addr(wBattleMonStatus);
    AND_A(1 << BRN);
    RET_Z ;
    LD_HL(wBattleMonAttack + 1);
    LD_A_hld;
    LD_B_A;
    LD_A_hl;
    SRL_A;
    RR_B;
    LD_hli_A;
    OR_A_B;
    IF_NZ goto player_ok;
    LD_B(0x1);  // min attack


player_ok:
    LD_hl_B;
    RET;


enemy:
    LD_A_addr(wEnemyMonStatus);
    AND_A(1 << BRN);
    RET_Z ;
    LD_HL(wEnemyMonAttack + 1);
    LD_A_hld;
    LD_B_A;
    LD_A_hl;
    SRL_A;
    RR_B;
    LD_hli_A;
    OR_A_B;
    IF_NZ goto enemy_ok;
    LD_B(0x1);  // min attack


enemy_ok:
    LD_hl_B;
    RET;

}

void ApplyStatLevelMultiplierOnAllStats(void){
//  Apply StatLevelMultipliers on all 5 Stats
    LD_C(0);

stat_loop:
    CALL(aApplyStatLevelMultiplier);
    INC_C;
    LD_A_C;
    CP_A(NUM_BATTLE_STATS);
    IF_NZ goto stat_loop;
    RET;

}

void ApplyStatLevelMultiplier(void){
    PUSH_BC;
    PUSH_BC;
    LD_A_addr(wApplyStatLevelMultipliersToEnemy);
    AND_A_A;
    LD_A_C;
    LD_HL(wBattleMonAttack);
    LD_DE(wPlayerStats);
    LD_BC(wPlayerAtkLevel);
    IF_Z goto got_pointers;
    LD_HL(wEnemyMonAttack);
    LD_DE(wEnemyStats);
    LD_BC(wEnemyAtkLevel);


got_pointers:
    ADD_A_C;
    LD_C_A;
    IF_NC goto okay;
    INC_B;

okay:
    LD_A_bc;
    POP_BC;
    LD_B_A;
    PUSH_BC;
    SLA_C;
    LD_B(0);
    ADD_HL_BC;
    LD_A_C;
    ADD_A_E;
    LD_E_A;
    IF_NC goto okay2;
    INC_D;

okay2:
    POP_BC;
    PUSH_HL;
    LD_HL(mStatLevelMultipliers_Applied);
    DEC_B;
    SLA_B;
    LD_C_B;
    LD_B(0);
    ADD_HL_BC;
    XOR_A_A;
    LDH_addr_A(hMultiplicand + 0);
    LD_A_de;
    LDH_addr_A(hMultiplicand + 1);
    INC_DE;
    LD_A_de;
    LDH_addr_A(hMultiplicand + 2);
    LD_A_hli;
    LDH_addr_A(hMultiplier);
    CALL(aMultiply);
    LD_A_hl;
    LDH_addr_A(hDivisor);
    LD_B(4);
    CALL(aDivide);
    POP_HL;

//  Cap at 999.
    LDH_A_addr(hQuotient + 3);
    SUB_A(LOW(MAX_STAT_VALUE));
    LDH_A_addr(hQuotient + 2);
    SBC_A(HIGH(MAX_STAT_VALUE));
    JP_C (mApplyStatLevelMultiplier_okay3);

    LD_A(HIGH(MAX_STAT_VALUE));
    LDH_addr_A(hQuotient + 2);
    LD_A(LOW(MAX_STAT_VALUE));
    LDH_addr_A(hQuotient + 3);


okay3:
    LDH_A_addr(hQuotient + 2);
    LD_hli_A;
    LD_B_A;
    LDH_A_addr(hQuotient + 3);
    LD_hl_A;
    OR_A_B;
    IF_NZ goto okay4;
    INC_hl;


okay4:
    POP_BC;
    RET;

// INCLUDE "data/battle/stat_multipliers_2.asm"

    return BadgeStatBoosts();
}

void BadgeStatBoosts(void){
//  Raise the stats of the battle mon in wBattleMon
//  depending on which badges have been obtained.

//  Every other badge boosts a stat, starting from the first.
//  GlacierBadge also boosts Special Defense, although the relevant code is buggy (see below).

//      ZephyrBadge:  Attack
//      PlainBadge:   Speed
//      MineralBadge: Defense
//      GlacierBadge: Special Attack and Special Defense

//  The boosted stats are in order, except PlainBadge and MineralBadge's boosts are swapped.

    LD_A_addr(wLinkMode);
    AND_A_A;
    RET_NZ ;

    LD_A_addr(wInBattleTowerBattle);
    AND_A_A;
    RET_NZ ;

    LD_A_addr(wJohtoBadges);

//  Swap badges 3 (PlainBadge) and 5 (MineralBadge).
    LD_D_A;
    AND_A((1 << PLAINBADGE));
    ADD_A_A;
    ADD_A_A;
    LD_B_A;
    LD_A_D;
    AND_A((1 << MINERALBADGE));
    RRCA;
    RRCA;
    LD_C_A;
    LD_A_D;
    AND_A(((1 << ZEPHYRBADGE) | (1 << HIVEBADGE) | (1 << FOGBADGE) | (1 << STORMBADGE) | (1 << GLACIERBADGE) | (1 << RISINGBADGE)));
    OR_A_B;
    OR_A_C;
    LD_B_A;

    LD_HL(wBattleMonAttack);
    LD_C(4);

CheckBadge:
    LD_A_B;
    SRL_B;
    CALL_C (aBoostStat);
    INC_HL;
    INC_HL;
//  Check every other badge.
    SRL_B;
    DEC_C;
    IF_NZ goto CheckBadge;
//  Check GlacierBadge again for Special Defense.
//  This check is buggy because it assumes that a is set by the "ld a, b" in the above loop,
//  but it can actually be overwritten by the call to BoostStat.
    SRL_A;
    CALL_C (aBoostStat);
    RET;

}

void BoostStat(void){
//  Raise stat at hl by 1/8.

    LD_A_hli;
    LD_D_A;
    LD_E_hl;
    SRL_D;
    RR_E;
    SRL_D;
    RR_E;
    SRL_D;
    RR_E;
    LD_A_hl;
    ADD_A_E;
    LD_hld_A;
    LD_A_hl;
    ADC_A_D;
    LD_hli_A;

//  Cap at 999.
    LD_A_hld;
    SUB_A(LOW(MAX_STAT_VALUE));
    LD_A_hl;
    SBC_A(HIGH(MAX_STAT_VALUE));
    RET_C ;
    LD_A(HIGH(MAX_STAT_VALUE));
    LD_hli_A;
    LD_A(LOW(MAX_STAT_VALUE));
    LD_hld_A;
    RET;

}

void v_LoadBattleFontsHPBar(void){
    CALLFAR(aLoadBattleFontsHPBar);
    RET;

}

void v_LoadHPBar(void){
    CALLFAR(aLoadHPBar);
    RET;

}

void LoadHPExpBarGFX(void){
//  //  unreferenced
    LD_DE(mEnemyHPBarBorderGFX);
    LD_HL(vTiles2 + LEN_2BPP_TILE * 0x6c);
    LD_BC((BANK(aEnemyHPBarBorderGFX) << 8) | 4);
    CALL(aGet1bpp);
    LD_DE(mHPExpBarBorderGFX);
    LD_HL(vTiles2 + LEN_2BPP_TILE * 0x73);
    LD_BC((BANK(aHPExpBarBorderGFX) << 8) | 6);
    CALL(aGet1bpp);
    LD_DE(mExpBarGFX);
    LD_HL(vTiles2 + LEN_2BPP_TILE * 0x55);
    LD_BC((BANK(aExpBarGFX) << 8) | 8);
    JP(mGet2bpp);

}

void EmptyBattleTextbox(void){
    LD_HL(mEmptyBattleTextbox_empty);
    JP(mBattleTextbox);


empty:
    //text_end ['?']

    return v_BattleRandom();
}

void v_BattleRandom(void){
//  If the normal RNG is used in a link battle it'll desync.
//  To circumvent this a shared PRNG is used instead.

//  But if we're in a non-link battle we're safe to use it
    LD_A_addr(wLinkMode);
    AND_A_A;
    JP_Z (mRandom);

//  The PRNG operates in streams of 10 values.

//  Which value are we trying to pull?
    PUSH_HL;
    PUSH_BC;
    LD_A_addr(wLinkBattleRNCount);
    LD_C_A;
    LD_B(0);
    LD_HL(wLinkBattleRNs);
    ADD_HL_BC;
    INC_A;
    LD_addr_A(wLinkBattleRNCount);

//  If we haven't hit the end yet, we're good
    CP_A(10 - 1);  // Exclude last value. See the closing comment
    LD_A_hl;
    POP_BC;
    POP_HL;
    RET_C ;

//  If we have, we have to generate new pseudorandom data
//  Instead of having multiple PRNGs, ten seeds are used
    PUSH_HL;
    PUSH_BC;
    PUSH_AF;

//  Reset count to 0
    XOR_A_A;
    LD_addr_A(wLinkBattleRNCount);
    LD_HL(wLinkBattleRNs);
    LD_B(10);  // number of seeds

//  Generate next number in the sequence for each seed
//  a[n+1] = (a[n] * 5 + 1) % 256

loop:
// get last #
    LD_A_hl;

// a * 5 + 1
    LD_C_A;
    ADD_A_A;
    ADD_A_A;
    ADD_A_C;
    INC_A;

// update #
    LD_hli_A;
    DEC_B;
    IF_NZ goto loop;

//  This has the side effect of pulling the last value first,
//  then wrapping around. As a result, when we check to see if
//  we've reached the end, we check the one before it.

    POP_AF;
    POP_BC;
    POP_HL;
    RET;

}

void Call_PlayBattleAnim_OnlyIfVisible(void){
    LD_A(BATTLE_VARS_SUBSTATUS3);
    CALL(aGetBattleVar);
    AND_A(1 << SUBSTATUS_FLYING | 1 << SUBSTATUS_UNDERGROUND);
    RET_NZ ;

    return Call_PlayBattleAnim();
}

void Call_PlayBattleAnim(void){
    LD_A_E;
    LD_addr_A(wFXAnimID);
    LD_A_D;
    LD_addr_A(wFXAnimID + 1);
    CALL(aWaitBGMap);
    PREDEF_JUMP(pPlayBattleAnim);

    return FinishBattleAnim();
}

void FinishBattleAnim(void){
    PUSH_AF;
    PUSH_BC;
    PUSH_DE;
    PUSH_HL;
    LD_B(SCGB_BATTLE_COLORS);
    CALL(aGetSGBLayout);
    CALL(aSetPalettes);
    CALL(aDelayFrame);
    POP_HL;
    POP_DE;
    POP_BC;
    POP_AF;
    RET;

}

void GiveExperiencePoints(void){
//  Give experience.
//  Don't give experience if linked or in the Battle Tower.
    LD_A_addr(wLinkMode);
    AND_A_A;
    RET_NZ ;

    LD_A_addr(wInBattleTowerBattle);
    BIT_A(0);
    RET_NZ ;

    CALL(aGiveExperiencePoints_EvenlyDivideExpAmongParticipants);
    XOR_A_A;
    LD_addr_A(wCurPartyMon);
    LD_BC(wPartyMon1Species);


loop:
    LD_HL(MON_HP);
    ADD_HL_BC;
    LD_A_hli;
    OR_A_hl;
    JP_Z (mGiveExperiencePoints_next_mon);  // fainted

    PUSH_BC;
    LD_HL(wBattleParticipantsNotFainted);
    LD_A_addr(wCurPartyMon);
    LD_C_A;
    LD_B(CHECK_FLAG);
    LD_D(0);
    PREDEF(pSmallFarFlagAction);
    LD_A_C;
    AND_A_A;
    POP_BC;
    JP_Z (mGiveExperiencePoints_next_mon);

//  give stat exp
    LD_HL(MON_STAT_EXP + 1);
    ADD_HL_BC;
    LD_D_H;
    LD_E_L;
    LD_HL(wEnemyMonBaseStats - 1);
    PUSH_BC;
    LD_C(NUM_EXP_STATS);

stat_exp_loop:
    INC_HL;
    LD_A_de;
    ADD_A_hl;
    LD_de_A;
    IF_NC goto no_carry_stat_exp;
    DEC_DE;
    LD_A_de;
    INC_A;
    IF_Z goto stat_exp_maxed_out;
    LD_de_A;
    INC_DE;


no_carry_stat_exp:
    PUSH_HL;
    PUSH_BC;
    LD_A(MON_POKERUS);
    CALL(aGetPartyParamLocation);
    LD_A_hl;
    AND_A_A;
    POP_BC;
    POP_HL;
    IF_Z goto stat_exp_awarded;
    LD_A_de;
    ADD_A_hl;
    LD_de_A;
    IF_NC goto stat_exp_awarded;
    DEC_DE;
    LD_A_de;
    INC_A;
    IF_Z goto stat_exp_maxed_out;
    LD_de_A;
    INC_DE;
    goto stat_exp_awarded;


stat_exp_maxed_out:
    LD_A(0xff);
    LD_de_A;
    INC_DE;
    LD_de_A;


stat_exp_awarded:
    INC_DE;
    INC_DE;
    DEC_C;
    IF_NZ goto stat_exp_loop;
    XOR_A_A;
    LDH_addr_A(hMultiplicand + 0);
    LDH_addr_A(hMultiplicand + 1);
    LD_A_addr(wEnemyMonBaseExp);
    LDH_addr_A(hMultiplicand + 2);
    LD_A_addr(wEnemyMonLevel);
    LDH_addr_A(hMultiplier);
    CALL(aMultiply);
    LD_A(7);
    LDH_addr_A(hDivisor);
    LD_B(4);
    CALL(aDivide);
//  Boost Experience for traded Pokemon
    POP_BC;
    LD_HL(MON_ID);
    ADD_HL_BC;
    LD_A_addr(wPlayerID);
    CP_A_hl;
    IF_NZ goto boosted;
    INC_HL;
    LD_A_addr(wPlayerID + 1);
    CP_A_hl;
    LD_A(0);
    IF_Z goto no_boost;


boosted:
    CALL(aBoostExp);
    LD_A(1);


no_boost:
//  Boost experience for a Trainer Battle
    LD_addr_A(wStringBuffer2 + 2);
    LD_A_addr(wBattleMode);
    DEC_A;
    CALL_NZ (aBoostExp);
//  Boost experience for Lucky Egg
    PUSH_BC;
    LD_A(MON_ITEM);
    CALL(aGetPartyParamLocation);
    LD_A_hl;
    CP_A(LUCKY_EGG);
    CALL_Z (aBoostExp);
    LDH_A_addr(hQuotient + 3);
    LD_addr_A(wStringBuffer2 + 1);
    LDH_A_addr(hQuotient + 2);
    LD_addr_A(wStringBuffer2);
    LD_A_addr(wCurPartyMon);
    LD_HL(wPartyMonNicknames);
    CALL(aGetNickname);
    LD_HL(mText_MonGainedExpPoint);
    CALL(aBattleTextbox);
    LD_A_addr(wStringBuffer2 + 1);
    LDH_addr_A(hQuotient + 3);
    LD_A_addr(wStringBuffer2);
    LDH_addr_A(hQuotient + 2);
    POP_BC;
    CALL(aAnimateExpBar);
    PUSH_BC;
    CALL(aLoadTilemapToTempTilemap);
    POP_BC;
    LD_HL(MON_EXP + 2);
    ADD_HL_BC;
    LD_D_hl;
    LDH_A_addr(hQuotient + 3);
    ADD_A_D;
    LD_hld_A;
    LD_D_hl;
    LDH_A_addr(hQuotient + 2);
    ADC_A_D;
    LD_hl_A;
    IF_NC goto no_exp_overflow;
    DEC_HL;
    INC_hl;
    IF_NZ goto no_exp_overflow;
    LD_A(0xff);
    LD_hli_A;
    LD_hli_A;
    LD_hl_A;


no_exp_overflow:
    LD_A_addr(wCurPartyMon);
    LD_E_A;
    LD_D(0);
    LD_HL(wPartySpecies);
    ADD_HL_DE;
    LD_A_hl;
    LD_addr_A(wCurSpecies);
    CALL(aGetBaseData);
    PUSH_BC;
    LD_D(MAX_LEVEL);
    CALLFAR(aCalcExpAtLevel);
    POP_BC;
    LD_HL(MON_EXP + 2);
    ADD_HL_BC;
    PUSH_BC;
    LDH_A_addr(hQuotient + 1);
    LD_B_A;
    LDH_A_addr(hQuotient + 2);
    LD_C_A;
    LDH_A_addr(hQuotient + 3);
    LD_D_A;
    LD_A_hld;
    SUB_A_D;
    LD_A_hld;
    SBC_A_C;
    LD_A_hl;
    SBC_A_B;
    IF_C goto not_max_exp;
    LD_A_B;
    LD_hli_A;
    LD_A_C;
    LD_hli_A;
    LD_A_D;
    LD_hld_A;


not_max_exp:
//  Check if the mon leveled up
    XOR_A_A;  // PARTYMON
    LD_addr_A(wMonType);
    PREDEF(pCopyMonToTempMon);
    CALLFAR(aCalcLevel);
    POP_BC;
    LD_HL(MON_LEVEL);
    ADD_HL_BC;
    LD_A_hl;
    CP_A(MAX_LEVEL);
    JP_NC (mGiveExperiencePoints_next_mon);
    CP_A_D;
    JP_Z (mGiveExperiencePoints_next_mon);
//  <NICKNAME> grew to level ##!
    LD_addr_A(wTempLevel);
    LD_A_addr(wCurPartyLevel);
    PUSH_AF;
    LD_A_D;
    LD_addr_A(wCurPartyLevel);
    LD_hl_A;
    LD_HL(MON_SPECIES);
    ADD_HL_BC;
    LD_A_hl;
    LD_addr_A(wCurSpecies);
    LD_addr_A(wTempSpecies);  // unused?
    CALL(aGetBaseData);
    LD_HL(MON_MAXHP + 1);
    ADD_HL_BC;
    LD_A_hld;
    LD_E_A;
    LD_D_hl;
    PUSH_DE;
    LD_HL(MON_MAXHP);
    ADD_HL_BC;
    LD_D_H;
    LD_E_L;
    LD_HL(MON_STAT_EXP - 1);
    ADD_HL_BC;
    PUSH_BC;
    LD_B(TRUE);
    PREDEF(pCalcMonStats);
    POP_BC;
    POP_DE;
    LD_HL(MON_MAXHP + 1);
    ADD_HL_BC;
    LD_A_hld;
    SUB_A_E;
    LD_E_A;
    LD_A_hl;
    SBC_A_D;
    LD_D_A;
    DEC_HL;
    LD_A_hl;
    ADD_A_E;
    LD_hld_A;
    LD_A_hl;
    ADC_A_D;
    LD_hl_A;
    LD_A_addr(wCurBattleMon);
    LD_D_A;
    LD_A_addr(wCurPartyMon);
    CP_A_D;
    IF_NZ goto skip_active_mon_update;
    LD_DE(wBattleMonHP);
    LD_A_hli;
    LD_de_A;
    INC_DE;
    LD_A_hli;
    LD_de_A;
    LD_DE(wBattleMonMaxHP);
    PUSH_BC;
    LD_BC(PARTYMON_STRUCT_LENGTH - MON_MAXHP);
    CALL(aCopyBytes);
    POP_BC;
    LD_HL(MON_LEVEL);
    ADD_HL_BC;
    LD_A_hl;
    LD_addr_A(wBattleMonLevel);
    LD_A_addr(wPlayerSubStatus5);
    BIT_A(SUBSTATUS_TRANSFORMED);
    IF_NZ goto transformed;
    LD_HL(MON_ATK);
    ADD_HL_BC;
    LD_DE(wPlayerStats);
    LD_BC(PARTYMON_STRUCT_LENGTH - MON_ATK);
    CALL(aCopyBytes);


transformed:
    XOR_A_A;  // FALSE
    LD_addr_A(wApplyStatLevelMultipliersToEnemy);
    CALL(aApplyStatLevelMultiplierOnAllStats);
    CALLFAR(aApplyStatusEffectOnPlayerStats);
    CALLFAR(aBadgeStatBoosts);
    CALLFAR(aUpdatePlayerHUD);
    CALL(aEmptyBattleTextbox);
    CALL(aLoadTilemapToTempTilemap);
    LD_A(0x1);
    LDH_addr_A(hBGMapMode);


skip_active_mon_update:
    FARCALL(aLevelUpHappinessMod);
    LD_A_addr(wCurBattleMon);
    LD_B_A;
    LD_A_addr(wCurPartyMon);
    CP_A_B;
    IF_Z goto skip_exp_bar_animation;
    LD_DE(SFX_HIT_END_OF_EXP_BAR);
    CALL(aPlaySFX);
    CALL(aWaitSFX);
    LD_HL(mBattleText_StringBuffer1GrewToLevel);
    CALL(aStdBattleTextbox);
    CALL(aLoadTilemapToTempTilemap);


skip_exp_bar_animation:
    XOR_A_A;  // PARTYMON
    LD_addr_A(wMonType);
    PREDEF(pCopyMonToTempMon);
    hlcoord(9, 0, wTilemap);
    LD_B(10);
    LD_C(9);
    CALL(aTextbox);
    hlcoord(11, 1, wTilemap);
    LD_BC(4);
    PREDEF(pPrintTempMonStats);
    LD_C(30);
    CALL(aDelayFrames);
    CALL(aWaitPressAorB_BlinkCursor);
    CALL(aSafeLoadTempTilemapToTilemap);
    XOR_A_A;  // PARTYMON
    LD_addr_A(wMonType);
    LD_A_addr(wCurSpecies);
    LD_addr_A(wTempSpecies);  // unused?
    LD_A_addr(wCurPartyLevel);
    PUSH_AF;
    LD_C_A;
    LD_A_addr(wTempLevel);
    LD_B_A;


level_loop:
    INC_B;
    LD_A_B;
    LD_addr_A(wCurPartyLevel);
    PUSH_BC;
    PREDEF(pLearnLevelMoves);
    POP_BC;
    LD_A_B;
    CP_A_C;
    IF_NZ goto level_loop;
    POP_AF;
    LD_addr_A(wCurPartyLevel);
    LD_HL(wEvolvableFlags);
    LD_A_addr(wCurPartyMon);
    LD_C_A;
    LD_B(SET_FLAG);
    PREDEF(pSmallFarFlagAction);
    POP_AF;
    LD_addr_A(wCurPartyLevel);


next_mon:
    LD_A_addr(wPartyCount);
    LD_B_A;
    LD_A_addr(wCurPartyMon);
    INC_A;
    CP_A_B;
    IF_Z goto done;
    LD_addr_A(wCurPartyMon);
    LD_A(MON_SPECIES);
    CALL(aGetPartyParamLocation);
    LD_B_H;
    LD_C_L;
    JP(mGiveExperiencePoints_loop);


done:
    JP(mResetBattleParticipants);


EvenlyDivideExpAmongParticipants:
//  count number of battle participants
    LD_A_addr(wBattleParticipantsNotFainted);
    LD_B_A;
    LD_C(PARTY_LENGTH);
    LD_D(0);

count_loop:
    XOR_A_A;
    SRL_B;
    ADC_A_D;
    LD_D_A;
    DEC_C;
    IF_NZ goto count_loop;
    CP_A(2);
    RET_C ;

    LD_addr_A(wTempByteValue);
    LD_HL(wEnemyMonBaseStats);
    LD_C(wEnemyMonEnd - wEnemyMonBaseStats);

base_stat_division_loop:
    XOR_A_A;
    LDH_addr_A(hDividend + 0);
    LD_A_hl;
    LDH_addr_A(hDividend + 1);
    LD_A_addr(wTempByteValue);
    LDH_addr_A(hDivisor);
    LD_B(2);
    CALL(aDivide);
    LDH_A_addr(hQuotient + 3);
    LD_hli_A;
    DEC_C;
    IF_NZ goto base_stat_division_loop;
    RET;

}

void BoostExp(void){
//  Multiply experience by 1.5x
    PUSH_BC;
//  load experience value
    LDH_A_addr(hProduct + 2);
    LD_B_A;
    LDH_A_addr(hProduct + 3);
    LD_C_A;
//  halve it
    SRL_B;
    RR_C;
//  add it back to the whole exp value
    ADD_A_C;
    LDH_addr_A(hProduct + 3);
    LDH_A_addr(hProduct + 2);
    ADC_A_B;
    LDH_addr_A(hProduct + 2);
    POP_BC;
    RET;

}

void Text_MonGainedExpPoint(void){
    //text_far ['Text_Gained']
    //text_asm ['?']
    LD_HL(mExpPointsText);
    LD_A_addr(wStringBuffer2 + 2);  // IsTradedMon
    AND_A_A;
    RET_Z ;

    LD_HL(mBoostedExpPointsText);
    RET;

}

void BoostedExpPointsText(void){
    //text_far ['_BoostedExpPointsText']
    //text_end ['?']

    return ExpPointsText();
}

void ExpPointsText(void){
    //text_far ['_ExpPointsText']
    //text_end ['?']

    return AnimateExpBar();
}

void AnimateExpBar(void){
    PUSH_BC;

    LD_HL(wCurPartyMon);
    LD_A_addr(wCurBattleMon);
    CP_A_hl;
    JP_NZ (mAnimateExpBar_finish);

    LD_A_addr(wBattleMonLevel);
    CP_A(MAX_LEVEL);
    JP_NC (mAnimateExpBar_finish);

    LDH_A_addr(hProduct + 3);
    LD_addr_A(wExperienceGained + 2);
    PUSH_AF;
    LDH_A_addr(hProduct + 2);
    LD_addr_A(wExperienceGained + 1);
    PUSH_AF;
    XOR_A_A;
    LD_addr_A(wExperienceGained);
    XOR_A_A;  // PARTYMON
    LD_addr_A(wMonType);
    PREDEF(pCopyMonToTempMon);
    LD_A_addr(wTempMonLevel);
    LD_B_A;
    LD_E_A;
    PUSH_DE;
    LD_DE(wTempMonExp + 2);
    CALL(aCalcExpBar);
    PUSH_BC;
    LD_HL(wTempMonExp + 2);
    LD_A_addr(wExperienceGained + 2);
    ADD_A_hl;
    LD_hld_A;
    LD_A_addr(wExperienceGained + 1);
    ADC_A_hl;
    LD_hld_A;
    IF_NC goto NoOverflow;
    INC_hl;
    IF_NZ goto NoOverflow;
    LD_A(0xff);
    LD_hli_A;
    LD_hli_A;
    LD_hl_A;


NoOverflow:
    LD_D(MAX_LEVEL);
    CALLFAR(aCalcExpAtLevel);
    LDH_A_addr(hProduct + 1);
    LD_B_A;
    LDH_A_addr(hProduct + 2);
    LD_C_A;
    LDH_A_addr(hProduct + 3);
    LD_D_A;
    LD_HL(wTempMonExp + 2);
    LD_A_hld;
    SUB_A_D;
    LD_A_hld;
    SBC_A_C;
    LD_A_hl;
    SBC_A_B;
    IF_C goto AlreadyAtMaxExp;
    LD_A_B;
    LD_hli_A;
    LD_A_C;
    LD_hli_A;
    LD_A_D;
    LD_hld_A;


AlreadyAtMaxExp:
    CALLFAR(aCalcLevel);
    LD_A_D;
    POP_BC;
    POP_DE;
    LD_D_A;
    CP_A_E;
    IF_NC goto LoopLevels;
    LD_A_E;
    LD_D_A;


LoopLevels:
    LD_A_E;
    CP_A(MAX_LEVEL);
    IF_NC goto FinishExpBar;
    CP_A_D;
    IF_Z goto FinishExpBar;
    INC_A;
    LD_addr_A(wTempMonLevel);
    LD_addr_A(wCurPartyLevel);
    LD_addr_A(wBattleMonLevel);
    PUSH_DE;
    CALL(aAnimateExpBar_PlayExpBarSound);
    LD_C(0x40);
    CALL(aAnimateExpBar_LoopBarAnimation);
    CALL(aPrintPlayerHUD);
    LD_HL(wBattleMonNickname);
    LD_DE(wStringBuffer1);
    LD_BC(MON_NAME_LENGTH);
    CALL(aCopyBytes);
    CALL(aTerminateExpBarSound);
    LD_DE(SFX_HIT_END_OF_EXP_BAR);
    CALL(aPlaySFX);
    FARCALL(aAnimateEndOfExpBar);
    CALL(aWaitSFX);
    LD_HL(mBattleText_StringBuffer1GrewToLevel);
    CALL(aStdBattleTextbox);
    POP_DE;
    INC_E;
    LD_B(0x0);
    goto LoopLevels;


FinishExpBar:
    PUSH_BC;
    LD_B_D;
    LD_DE(wTempMonExp + 2);
    CALL(aCalcExpBar);
    LD_A_B;
    POP_BC;
    LD_C_A;
    CALL(aAnimateExpBar_PlayExpBarSound);
    CALL(aAnimateExpBar_LoopBarAnimation);
    CALL(aTerminateExpBarSound);
    POP_AF;
    LDH_addr_A(hProduct + 2);
    POP_AF;
    LDH_addr_A(hProduct + 3);


finish:
    POP_BC;
    RET;


PlayExpBarSound:
    PUSH_BC;
    CALL(aWaitSFX);
    LD_DE(SFX_EXP_BAR);
    CALL(aPlaySFX);
    LD_C(10);
    CALL(aDelayFrames);
    POP_BC;
    RET;


LoopBarAnimation:
    LD_D(3);
    DEC_B;

anim_loop:
    INC_B;
    PUSH_BC;
    PUSH_DE;
    hlcoord(17, 11, wTilemap);
    CALL(aPlaceExpBar);
    POP_DE;
    LD_A(0x1);
    LDH_addr_A(hBGMapMode);
    LD_C_D;
    CALL(aDelayFrames);
    XOR_A_A;
    LDH_addr_A(hBGMapMode);
    POP_BC;
    LD_A_C;
    CP_A_B;
    IF_Z goto end_animation;
    INC_B;
    PUSH_BC;
    PUSH_DE;
    hlcoord(17, 11, wTilemap);
    CALL(aPlaceExpBar);
    POP_DE;
    LD_A(0x1);
    LDH_addr_A(hBGMapMode);
    LD_C_D;
    CALL(aDelayFrames);
    XOR_A_A;
    LDH_addr_A(hBGMapMode);
    DEC_D;
    IF_NZ goto min_number_of_frames;
    LD_D(1);

min_number_of_frames:
    POP_BC;
    LD_A_C;
    CP_A_B;
    IF_NZ goto anim_loop;

end_animation:
    LD_A(0x1);
    LDH_addr_A(hBGMapMode);
    RET;

}

void SendOutMonText(void){
    LD_A_addr(wLinkMode);
    AND_A_A;
    IF_Z goto not_linked;

//  If we're in a LinkBattle print just "Go <PlayerMon>"
//  unless DoBattle already set [wBattleHasJustStarted]
    LD_HL(mGoMonText);
    LD_A_addr(wBattleHasJustStarted);
    AND_A_A;
    IF_NZ goto skip_to_textbox;


not_linked:
//  Depending on the HP of the enemy mon, the game prints a different text
    LD_HL(wEnemyMonHP);
    LD_A_hli;
    OR_A_hl;
    LD_HL(mGoMonText);
    IF_Z goto skip_to_textbox;

// compute enemy health remaining as a percentage
    XOR_A_A;
    LDH_addr_A(hMultiplicand + 0);
    LD_HL(wEnemyMonHP);
    LD_A_hli;
    LD_addr_A(wEnemyHPAtTimeOfPlayerSwitch);
    LDH_addr_A(hMultiplicand + 1);
    LD_A_hl;
    LD_addr_A(wEnemyHPAtTimeOfPlayerSwitch + 1);
    LDH_addr_A(hMultiplicand + 2);
    LD_A(25);
    LDH_addr_A(hMultiplier);
    CALL(aMultiply);
    LD_HL(wEnemyMonMaxHP);
    LD_A_hli;
    LD_B_hl;
    SRL_A;
    RR_B;
    SRL_A;
    RR_B;
    LD_A_B;
    LD_B(4);
    LDH_addr_A(hDivisor);
    CALL(aDivide);

    LDH_A_addr(hQuotient + 3);
    LD_HL(mGoMonText);
    CP_A(70);
    IF_NC goto skip_to_textbox;

    LD_HL(mDoItMonText);
    CP_A(40);
    IF_NC goto skip_to_textbox;

    LD_HL(mGoForItMonText);
    CP_A(10);
    IF_NC goto skip_to_textbox;

    LD_HL(mYourFoesWeakGetmMonText);

skip_to_textbox:
    JP(mBattleTextbox);

}

void GoMonText(void){
    //text_far ['_GoMonText']
    //text_asm ['?']
    JR(mPrepareBattleMonNicknameText);

}

void DoItMonText(void){
    //text_far ['_DoItMonText']
    //text_asm ['?']
    JR(mPrepareBattleMonNicknameText);

}

void GoForItMonText(void){
    //text_far ['_GoForItMonText']
    //text_asm ['?']
    JR(mPrepareBattleMonNicknameText);

}

void YourFoesWeakGetmMonText(void){
    //text_far ['_YourFoesWeakGetmMonText']
    //text_asm ['?']
    return PrepareBattleMonNicknameText();
}

void PrepareBattleMonNicknameText(void){
    LD_HL(mBattleMonNicknameText);
    RET;

}

void BattleMonNicknameText(void){
    //text_far ['_BattleMonNicknameText']
    //text_end ['?']

    return WithdrawMonText();
}

void WithdrawMonText(void){
    LD_HL(mWithdrawMonText_WithdrawMonText);
    JP(mBattleTextbox);


WithdrawMonText:
    //text_far ['_BattleMonNickCommaText']
    //text_asm ['?']
//  Depending on the HP lost since the enemy mon was sent out, the game prints a different text
    PUSH_DE;
    PUSH_BC;
// compute enemy health lost as a percentage
    LD_HL(wEnemyMonHP + 1);
    LD_DE(wEnemyHPAtTimeOfPlayerSwitch + 1);
    LD_B_hl;
    DEC_HL;
    LD_A_de;
    SUB_A_B;
    LDH_addr_A(hMultiplicand + 2);
    DEC_DE;
    LD_B_hl;
    LD_A_de;
    SBC_A_B;
    LDH_addr_A(hMultiplicand + 1);
    LD_A(25);
    LDH_addr_A(hMultiplier);
    CALL(aMultiply);
    LD_HL(wEnemyMonMaxHP);
    LD_A_hli;
    LD_B_hl;
    SRL_A;
    RR_B;
    SRL_A;
    RR_B;
    LD_A_B;
    LD_B(4);
    LDH_addr_A(hDivisor);
    CALL(aDivide);
    POP_BC;
    POP_DE;
    LDH_A_addr(hQuotient + 3);
    LD_HL(mThatsEnoughComeBackText);
    AND_A_A;
    RET_Z ;

    LD_HL(mComeBackText);
    CP_A(30);
    RET_C ;

    LD_HL(mOKComeBackText);
    CP_A(70);
    RET_C ;

    LD_HL(mGoodComeBackText);
    RET;

}

void ThatsEnoughComeBackText(void){
    //text_far ['_ThatsEnoughComeBackText']
    //text_end ['?']

    return OKComeBackText();
}

void OKComeBackText(void){
    //text_far ['_OKComeBackText']
    //text_end ['?']

    return GoodComeBackText();
}

void GoodComeBackText(void){
    //text_far ['_GoodComeBackText']
    //text_end ['?']

    return TextJump_ComeBack();
}

void TextJump_ComeBack(void){
//  //  unreferenced
    LD_HL(mComeBackText);
    RET;

}

void ComeBackText(void){
    //text_far ['_ComeBackText']
    //text_end ['?']

    return HandleSafariAngerEatingStatus();
}

void HandleSafariAngerEatingStatus(void){
//  //  unreferenced
    LD_HL(wSafariMonEating);
    LD_A_hl;
    AND_A_A;
    IF_Z goto angry;
    DEC_hl;
    LD_HL(mBattleText_WildMonIsEating);
    goto finish;


angry:
    DEC_HL;
    //assert ['wSafariMonEating - 1 == wSafariMonAngerCount'];
    LD_A_hl;
    AND_A_A;
    RET_Z ;
    DEC_hl;
    LD_HL(mBattleText_WildMonIsAngry);
    IF_NZ goto finish;
    PUSH_HL;
    LD_A_addr(wEnemyMonSpecies);
    LD_addr_A(wCurSpecies);
    CALL(aGetBaseData);
    LD_A_addr(wBaseCatchRate);
    LD_addr_A(wEnemyMonCatchRate);
    POP_HL;


finish:
    PUSH_HL;
    CALL(aSafeLoadTempTilemapToTilemap);
    POP_HL;
    JP(mStdBattleTextbox);

}

void FillInExpBar(void){
    PUSH_HL;
    CALL(aCalcExpBar);
    POP_HL;
    LD_DE(7);
    ADD_HL_DE;
    JP(mPlaceExpBar);

}

void FillInExpBar_Conv(uint8_t* hl, uint8_t b, const uint8_t* de) {
    uint8_t pct = CalcExpBar_Conv(b, de);
    PlaceExpBar_Conv(hl + 7, pct);
}

void CalcExpBar(void){
//  Calculate the percent exp between this level and the next
//  Level in b
    PUSH_DE;
    LD_D_B;
    PUSH_DE;
    CALLFAR(aCalcExpAtLevel);
    POP_DE;
//  exp at current level gets pushed to the stack
    LD_HL(hMultiplicand);
    LD_A_hli;
    PUSH_AF;
    LD_A_hli;
    PUSH_AF;
    LD_A_hl;
    PUSH_AF;
//  next level
    INC_D;
    CALLFAR(aCalcExpAtLevel);
//  back up the next level exp, and subtract the two levels
    LD_HL(hMultiplicand + 2);
    LD_A_hl;
    LDH_addr_A(hMathBuffer + 2);
    POP_BC;
    SUB_A_B;
    LD_hld_A;
    LD_A_hl;
    LDH_addr_A(hMathBuffer + 1);
    POP_BC;
    SBC_A_B;
    LD_hld_A;
    LD_A_hl;
    LDH_addr_A(hMathBuffer);
    POP_BC;
    SBC_A_B;
    LD_hl_A;
    POP_DE;

    LD_HL(hMultiplicand + 1);
    LD_A_hli;
    PUSH_AF;
    LD_A_hl;
    PUSH_AF;

//  get the amount of exp remaining to the next level
    LD_A_de;
    DEC_DE;
    LD_C_A;
    LDH_A_addr(hMathBuffer + 2);
    SUB_A_C;
    LD_hld_A;
    LD_A_de;
    DEC_DE;
    LD_B_A;
    LDH_A_addr(hMathBuffer + 1);
    SBC_A_B;
    LD_hld_A;
    LD_A_de;
    LD_C_A;
    LDH_A_addr(hMathBuffer);
    SBC_A_C;
    LD_hld_A;
    XOR_A_A;
    LD_hl_A;
    LD_A(64);
    LDH_addr_A(hMultiplier);
    CALL(aMultiply);
    POP_AF;
    LD_C_A;
    POP_AF;
    LD_B_A;

loop:
    LD_A_B;
    AND_A_A;
    IF_Z goto done;
    SRL_B;
    RR_C;
    LD_HL(hProduct);
    SRL_hl;
    INC_HL;
    RR_hl;
    INC_HL;
    RR_hl;
    INC_HL;
    RR_hl;
    goto loop;


done:
    LD_A_C;
    LDH_addr_A(hDivisor);
    LD_B(4);
    CALL(aDivide);
    LDH_A_addr(hQuotient + 3);
    LD_B_A;
    LD_A(0x40);
    SUB_A_B;
    LD_B_A;
    RET;

}

//  Calculate the percent exp between this level and the next
uint8_t CalcExpBar_Conv(uint8_t b, const uint8_t* de){
//  Level in b
    // PUSH_DE;
    // LD_D_B;
    // PUSH_DE;
    // CALLFAR(aCalcExpAtLevel);
    uint32_t exp = CalcExpAtLevel_Conv(b);
    // POP_DE;
//  exp at current level gets pushed to the stack
    // LD_HL(hMultiplicand);
    // LD_A_hli;
    // PUSH_AF;
    // LD_A_hli;
    // PUSH_AF;
    // LD_A_hl;
    // PUSH_AF;
//  next level
    // INC_D;
    // CALLFAR(aCalcExpAtLevel);
    uint32_t next = CalcExpAtLevel_Conv(b + 1);
//  back up the next level exp, and subtract the two levels
    // LD_HL(hMultiplicand + 2);
    // LD_A_hl;
    // LDH_addr_A(hMathBuffer + 2);
    // POP_BC;
    // SUB_A_B;
    // LD_hld_A;
    // LD_A_hl;
    // LDH_addr_A(hMathBuffer + 1);
    // POP_BC;
    // SBC_A_B;
    // LD_hld_A;
    // LD_A_hl;
    // LDH_addr_A(hMathBuffer);
    // POP_BC;
    // SBC_A_B;
    // LD_hl_A;
    // POP_DE;

    // LD_HL(hMultiplicand + 1);
    // LD_A_hli;
    // PUSH_AF;
    // LD_A_hl;
    // PUSH_AF;
    uint32_t l = next - exp;

//  get the amount of exp remaining to the next level
    uint32_t cur_exp = (de[0])
        + (de[-1] << 8)
        + (de[-2] << 16);

    uint32_t h = cur_exp - exp;
    // LD_A_de;
    // DEC_DE;
    // LD_C_A;
    // LDH_A_addr(hMathBuffer + 2);
    // SUB_A_C;
    // LD_hld_A;
    // LD_A_de;
    // DEC_DE;
    // LD_B_A;
    // LDH_A_addr(hMathBuffer + 1);
    // SBC_A_B;
    // LD_hld_A;
    // LD_A_de;
    // LD_C_A;
    // LDH_A_addr(hMathBuffer);
    // SBC_A_C;
    // LD_hld_A;
    // XOR_A_A;
    // LD_hl_A;
    // LD_A(64);
    // LDH_addr_A(hMultiplier);
    // CALL(aMultiply);
    // POP_AF;
    // LD_C_A;
    // POP_AF;
    // LD_B_A;

// loop:
    // LD_A_B;
    // AND_A_A;
    // IF_Z goto done;
    // SRL_B;
    // RR_C;
    // LD_HL(hProduct);
    // SRL_hl;
    // INC_HL;
    // RR_hl;
    // INC_HL;
    // RR_hl;
    // INC_HL;
    // RR_hl;
    // goto loop;


// done:
    // LD_A_C;
    // LDH_addr_A(hDivisor);
    // LD_B(4);
    // CALL(aDivide);
    // LDH_A_addr(hQuotient + 3);
    // LD_B_A;
    // LD_A(0x40);
    // SUB_A_B;
    // LD_B_A;
    // RET;

    return (uint8_t)((64 * h) / l);
}

void PlaceExpBar(void){
    LD_C(0x8);  // number of tiles

loop1:
    LD_A_B;
    SUB_A(0x8);
    IF_C goto next;
    LD_B_A;
    LD_A(0x6a);  // full bar
    LD_hld_A;
    DEC_C;
    IF_Z goto finish;
    goto loop1;


next:
    ADD_A(0x8);
    IF_Z goto loop2;
    ADD_A(0x54);  // tile to the left of small exp bar tile
    goto skip;


loop2:
    LD_A(0x62);  // empty bar


skip:
    LD_hld_A;
    LD_A(0x62);  // empty bar
    DEC_C;
    IF_NZ goto loop2;


finish:
    RET;

}

void PlaceExpBar_Conv(uint8_t* hl, uint8_t b){
    // LD_C(0x8);  // number of tiles
    uint8_t c = 0x8;

    while(1)
    {
    // loop1:
        // LD_A_B;
        // SUB_A(0x8);
        // IF_C goto next;
        if(b < 0x8)
            break;
        // LD_B_A;
        b -= 0x8;
        // LD_A(0x6a);  // full bar
        // LD_hld_A;
        *(hl--) = 0x6a;
        // DEC_C;
        // IF_Z goto finish;
        if(--c == 0)
            return;
        // goto loop1;
    }


// next:
    // ADD_A(0x8);
    // IF_Z goto loop2;
    uint8_t a;
    if(b != 0x0) {
        // ADD_A(0x54);  // tile to the left of small exp bar tile
        a = b + 0x54;
    }
    else {
        a = 0x62;
    }
    // goto skip;


    do {
    // loop2:
        // LD_A(0x62);  // empty bar

    // skip:
        // LD_hld_A;
        *(hl--) = a;
        // LD_A(0x62);  // empty bar
        a = 0x62;
        // DEC_C;
        // IF_NZ goto loop2;
    } while(--c != 0);


// finish:
    // RET;
}

void GetBattleMonBackpic(void){
    LD_A_addr(wPlayerSubStatus4);
    BIT_A(SUBSTATUS_SUBSTITUTE);
    LD_HL(mBattleAnimCmd_RaiseSub);
    JR_NZ (mGetBattleMonBackpic_DoAnim);  // substitute

    return DropPlayerSub();
}

void DropPlayerSub(void){
    LD_A_addr(wPlayerMinimized);
    AND_A_A;
    LD_HL(mBattleAnimCmd_MinimizeOpp);
    JR_NZ (mGetBattleMonBackpic_DoAnim);
    LD_A_addr(wCurPartySpecies);
    PUSH_AF;
    LD_A_addr(wBattleMonSpecies);
    LD_addr_A(wCurPartySpecies);
    LD_HL(wBattleMonDVs);
    PREDEF(pGetUnownLetter);
    LD_DE(vTiles2 + LEN_2BPP_TILE * 0x31);
    PREDEF(pGetMonBackpic);
    POP_AF;
    LD_addr_A(wCurPartySpecies);
    RET;

}

void GetBattleMonBackpic_DoAnim(void){
    LDH_A_addr(hBattleTurn);
    PUSH_AF;
    XOR_A_A;
    LDH_addr_A(hBattleTurn);
    LD_A(BANK(aBattleAnimCommands));
    RST(aFarCall);
    POP_AF;
    LDH_addr_A(hBattleTurn);
    RET;

}

void GetEnemyMonFrontpic(void){
    LD_A_addr(wEnemySubStatus4);
    BIT_A(SUBSTATUS_SUBSTITUTE);
    LD_HL(mBattleAnimCmd_RaiseSub);
    JR_NZ (mGetEnemyMonFrontpic_DoAnim);

    return DropEnemySub();
}

void DropEnemySub(void){
    LD_A_addr(wEnemyMinimized);
    AND_A_A;
    LD_HL(mBattleAnimCmd_MinimizeOpp);
    JR_NZ (mGetEnemyMonFrontpic_DoAnim);

    LD_A_addr(wCurPartySpecies);
    PUSH_AF;
    LD_A_addr(wEnemyMonSpecies);
    LD_addr_A(wCurSpecies);
    LD_addr_A(wCurPartySpecies);
    CALL(aGetBaseData);
    LD_HL(wEnemyMonDVs);
    PREDEF(pGetUnownLetter);
    LD_DE(vTiles2);
    PREDEF(pGetAnimatedFrontpic);
    POP_AF;
    LD_addr_A(wCurPartySpecies);
    RET;

}

void GetEnemyMonFrontpic_DoAnim(void){
    LDH_A_addr(hBattleTurn);
    PUSH_AF;
    CALL(aSetEnemyTurn);
    LD_A(BANK(aBattleAnimCommands));
    RST(aFarCall);
    POP_AF;
    LDH_addr_A(hBattleTurn);
    RET;

}

void StartBattle(void){
//  This check prevents you from entering a battle without any Pokemon.
//  Those using walk-through-walls to bypass getting a Pokemon experience
//  the effects of this check.
    PEEK("");
    LD_A_addr(wPartyCount);
    AND_A_A;
    RET_Z ;

    LD_A_addr(wTimeOfDayPal);
    PUSH_AF;
    CALL(aBattleIntro);
    CALL(aDoBattle);
    CALL(aExitBattle);
    POP_AF;
    LD_addr_A(wTimeOfDayPal);
    SCF;
    RET;

}

bool StartBattle_Conv(void){
//  This check prevents you from entering a battle without any Pokemon.
//  Those using walk-through-walls to bypass getting a Pokemon experience
//  the effects of this check.
    // LD_A_addr(wPartyCount);
    // AND_A_A;
    // RET_Z ;
    if(wram->wPartyCount == 0)
        return false;

    // LD_A_addr(wTimeOfDayPal);
    // PUSH_AF;
    uint8_t pal = wram->wTimeOfDayPal;
    // CALL(aBattleIntro);
    BattleIntro();
    // CALL(aDoBattle);
    DoBattle();
    // CALL(aExitBattle);
    ExitBattle();
    // POP_AF;
    // LD_addr_A(wTimeOfDayPal);
    wram->wTimeOfDayPal = pal;
    // SCF;
    // RET;
    return true;
}

void CallDoBattle(void){
//  //  unreferenced
    CALL(aDoBattle);
    RET;

}

void BattleIntro(void){
    FARCALL(aStubbedTrainerRankings_Battles);  // mobile
    CALL(aLoadTrainerOrWildMonPic);
    XOR_A_A;
    LD_addr_A(wTempBattleMonSpecies);
    LD_addr_A(wBattleMenuCursorPosition);
    XOR_A_A;
    LDH_addr_A(hMapAnims);
    FARCALL(aPlayBattleMusic);
    FARCALL(aShowLinkBattleParticipants);
    FARCALL(aFindFirstAliveMonAndStartBattle);
    CALL(aDisableSpriteUpdates);
    FARCALL(aClearBattleRAM);
    CALL(aInitEnemy);
    CALL(aBackUpBGMap2);
    LD_B(SCGB_BATTLE_GRAYSCALE);
    CALL(aGetSGBLayout);
    LD_HL(rLCDC);
    RES_hl(rLCDC_WINDOW_TILEMAP);  // select vBGMap0/vBGMap2
    CALL(aInitBattleDisplay);
    CALL(aBattleStartMessage);
    LD_HL(rLCDC);
    SET_hl(rLCDC_WINDOW_TILEMAP);  // select vBGMap1/vBGMap3
    XOR_A_A;
    LDH_addr_A(hBGMapMode);
    CALL(aEmptyBattleTextbox);
    hlcoord(9, 7, wTilemap);
    LD_BC((5 << 8) | 11);
    CALL(aClearBox);
    hlcoord(1, 0, wTilemap);
    LD_BC((4 << 8) | 10);
    CALL(aClearBox);
    CALL(aClearSprites);
    LD_A_addr(wBattleMode);
    CP_A(WILD_BATTLE);
    CALL_Z (aUpdateEnemyHUD);
    LD_A(0x1);
    LDH_addr_A(hBGMapMode);
    RET;

}

void LoadTrainerOrWildMonPic(void){
    LD_A_addr(wOtherTrainerClass);
    AND_A_A;
    IF_NZ goto Trainer;
    LD_A_addr(wTempWildMonSpecies);
    LD_addr_A(wCurPartySpecies);


Trainer:
    LD_addr_A(wTempEnemyMonSpecies);
    RET;

}

void InitEnemy(void){
    LD_A_addr(wOtherTrainerClass);
    AND_A_A;
    // JP_NZ (mInitEnemyTrainer);  // trainer
    // JP(mInitEnemyWildmon);  // wild
    IF_NZ
        return InitEnemyTrainer();
    return InitEnemyWildmon();

}

void BackUpBGMap2(void){
    PEEK("");
    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(MBANK(awDecompressScratch));
    LDH_addr_A(rSVBK);
    LD_HL(wDecompressScratch);
    LD_BC(0x40 * LEN_2BPP_TILE);  // vBGMap3 - vBGMap2
    LD_A(0x2);
    CALL(aByteFill);
    LDH_A_addr(rVBK);
    PUSH_AF;
    LD_A(0x1);
    LDH_addr_A(rVBK);
    LD_DE(wDecompressScratch);
    hlbgcoord(0, 0, vBGMap0);  // vBGMap2
    LD_BC((BANK(aBackUpBGMap2) << 8) | 0x40);
    CALL(aRequest2bpp);
    POP_AF;
    LDH_addr_A(rVBK);
    POP_AF;
    LDH_addr_A(rSVBK);
    RET;

}

void InitEnemyTrainer(void){
    PEEK("");
    LD_addr_A(wTrainerClass);
    FARCALL(aStubbedTrainerRankings_TrainerBattles);
    XOR_A_A;
    LD_addr_A(wTempEnemyMonSpecies);
    CALLFAR(aGetTrainerAttributes);
    CALLFAR(aReadTrainerParty);

// RIVAL1's first mon has no held item
    LD_A_addr(wTrainerClass);
    CP_A(RIVAL1);
    IF_NZ goto ok;
    XOR_A_A;
    LD_addr_A(wOTPartyMon1Item);


ok:
    LD_DE(vTiles2);
    CALLFAR(aGetTrainerPic);
    XOR_A_A;
    LDH_addr_A(hGraphicStartTile);
    DEC_A;
    LD_addr_A(wEnemyItemState);
    hlcoord(12, 0, wTilemap);
    LD_BC((7 << 8) | 7);
    PREDEF(pPlaceGraphic);
    LD_A(-1);
    LD_addr_A(wCurOTMon);
    LD_A(TRAINER_BATTLE);
    LD_addr_A(wBattleMode);

    CALL(aIsGymLeader);
    IF_NC goto done;
    XOR_A_A;
    LD_addr_A(wCurPartyMon);
    LD_A_addr(wPartyCount);
    LD_B_A;

partyloop:
    PUSH_BC;
    LD_A(MON_HP);
    CALL(aGetPartyParamLocation);
    LD_A_hli;
    OR_A_hl;
    IF_Z goto skipfaintedmon;
    LD_C(HAPPINESS_GYMBATTLE);
    CALLFAR(aChangeHappiness);

skipfaintedmon:
    POP_BC;
    DEC_B;
    IF_Z goto done;
    LD_HL(wCurPartyMon);
    INC_hl;
    goto partyloop;

done:
    RET;

}

void InitEnemyWildmon(void){
    LD_A(WILD_BATTLE);
    LD_addr_A(wBattleMode);
    FARCALL(aStubbedTrainerRankings_WildBattles);
    CALL(aLoadEnemyMon);
    LD_HL(wEnemyMonMoves);
    LD_DE(wWildMonMoves);
    LD_BC(NUM_MOVES);
    CALL(aCopyBytes);
    LD_HL(wEnemyMonPP);
    LD_DE(wWildMonPP);
    LD_BC(NUM_MOVES);
    CALL(aCopyBytes);
    LD_HL(wEnemyMonDVs);
    PREDEF(pGetUnownLetter);
    LD_A_addr(wCurPartySpecies);
    CP_A(UNOWN);
    IF_NZ goto skip_unown;
    LD_A_addr(wFirstUnownSeen);
    AND_A_A;
    IF_NZ goto skip_unown;
    LD_A_addr(wUnownLetter);
    LD_addr_A(wFirstUnownSeen);

skip_unown:
    LD_DE(vTiles2);
    PREDEF(pGetAnimatedFrontpic);
    XOR_A_A;
    LD_addr_A(wTrainerClass);
    LDH_addr_A(hGraphicStartTile);
    hlcoord(12, 0, wTilemap);
    LD_BC((7 << 8) | 7);
    PREDEF(pPlaceGraphic);
    RET;

}

void FillEnemyMovesFromMoveIndicesBuffer(void){
//  //  unreferenced
    LD_HL(wEnemyMonMoves);
    LD_DE(wListMoves_MoveIndicesBuffer);
    LD_B(NUM_MOVES);

loop:
    LD_A_de;
    INC_DE;
    LD_hli_A;
    AND_A_A;
    IF_Z goto clearpp;

    PUSH_BC;
    PUSH_HL;

    PUSH_HL;
    DEC_A;
    LD_HL(mMoves + MOVE_PP);
    LD_BC(MOVE_LENGTH);
    CALL(aAddNTimes);
    LD_A(BANK(aMoves));
    CALL(aGetFarByte);
    POP_HL;

    LD_BC(wEnemyMonPP - (wEnemyMonMoves + 1));
    ADD_HL_BC;
    LD_hl_A;

    POP_HL;
    POP_BC;

    DEC_B;
    IF_NZ goto loop;
    RET;


clear:
    XOR_A_A;
    LD_hli_A;


clearpp:
    PUSH_BC;
    PUSH_HL;
    LD_BC(wEnemyMonPP - (wEnemyMonMoves + 1));
    ADD_HL_BC;
    XOR_A_A;
    LD_hl_A;
    POP_HL;
    POP_BC;
    DEC_B;
    IF_NZ goto clear;
    RET;

}

void ExitBattle(void){
    CALL(aExitBattle_HandleEndOfBattle);
    CALL(aCleanUpBattleRAM);
    RET;


HandleEndOfBattle:
    LD_A_addr(wLinkMode);
    AND_A_A;
    IF_Z goto not_linked;
    CALL(aShowLinkBattleParticipantsAfterEnd);
    LD_C(150);
    CALL(aDelayFrames);
    CALL(aDisplayLinkBattleResult);
    RET;


not_linked:
    LD_A_addr(wBattleResult);
    AND_A(0xf);
    RET_NZ ;
    CALL(aCheckPayDay);
    XOR_A_A;
    LD_addr_A(wForceEvolution);
    PREDEF(pEvolveAfterBattle);
    FARCALL(aGivePokerusAndConvertBerries);
    RET;

}

void CleanUpBattleRAM(void){
    CALL(aBattleEnd_HandleRoamMons);
    XOR_A_A;
    LD_addr_A(wLowHealthAlarm);
    LD_addr_A(wBattleMode);
    LD_addr_A(wBattleType);
    LD_addr_A(wAttackMissed);
    LD_addr_A(wTempWildMonSpecies);
    LD_addr_A(wOtherTrainerClass);
    LD_addr_A(wFailedToFlee);
    LD_addr_A(wNumFleeAttempts);
    LD_addr_A(wForcedSwitch);
    LD_addr_A(wPartyMenuCursor);
    LD_addr_A(wKeyItemsPocketCursor);
    LD_addr_A(wItemsPocketCursor);
    LD_addr_A(wBattleMenuCursorPosition);
    LD_addr_A(wCurMoveNum);
    LD_addr_A(wBallsPocketCursor);
    LD_addr_A(wLastPocket);
    LD_addr_A(wMenuScrollPosition);
    LD_addr_A(wKeyItemsPocketScrollPosition);
    LD_addr_A(wItemsPocketScrollPosition);
    LD_addr_A(wBallsPocketScrollPosition);
    LD_HL(wPlayerSubStatus1);
    LD_B(wEnemyFuryCutterCount - wPlayerSubStatus1);

loop:
    LD_hli_A;
    DEC_B;
    IF_NZ goto loop;
    CALL(aWaitSFX);
    RET;

}

void CheckPayDay(void){
    LD_HL(wPayDayMoney);
    LD_A_hli;
    OR_A_hl;
    INC_HL;
    OR_A_hl;
    RET_Z ;
    LD_A_addr(wAmuletCoin);
    AND_A_A;
    IF_Z goto okay;
    LD_HL(wPayDayMoney + 2);
    SLA_hl;
    DEC_HL;
    RL_hl;
    DEC_HL;
    RL_hl;
    IF_NC goto okay;
    LD_A(0xff);
    LD_hli_A;
    LD_hli_A;
    LD_hl_A;


okay:
    LD_HL(wPayDayMoney + 2);
    LD_DE(wMoney + 2);
    CALL(aAddBattleMoneyToAccount);
    LD_HL(mBattleText_PlayerPickedUpPayDayMoney);
    CALL(aStdBattleTextbox);
    LD_A_addr(wInBattleTowerBattle);
    BIT_A(0);
    RET_Z ;
    CALL(aClearTilemap);
    CALL(aClearBGPalettes);
    RET;

}

void ShowLinkBattleParticipantsAfterEnd(void){
    FARCALL(aStubbedTrainerRankings_LinkBattles);
    FARCALL(aBackupMobileEventIndex);
    LD_A_addr(wCurOTMon);
    LD_HL(wOTPartyMon1Status);
    CALL(aGetPartyLocation);
    LD_A_addr(wEnemyMonStatus);
    LD_hl_A;
    CALL(aClearTilemap);
    FARCALL(av_ShowLinkBattleParticipants);
    RET;

}

void DisplayLinkBattleResult(void){
    FARCALL(aCheckMobileBattleError);
    JP_C (mDisplayLinkBattleResult_Mobile_InvalidBattle);
    CALL(aIsMobileBattle2);
    IF_NZ goto proceed;

    LD_HL(wcd2a);
    BIT_hl(4);
    IF_Z goto proceed;

    FARCALL(aDetermineLinkBattleResult);


proceed:
    LD_A_addr(wBattleResult);
    AND_A(0xf);
    CP_A(LOSE);
    IF_C goto win;  // WIN
    IF_Z goto lose;  // LOSE
// DRAW
    FARCALL(aStubbedTrainerRankings_ColosseumDraws);
    LD_DE(mDisplayLinkBattleResult_Draw);
    goto store_result;


win:
    FARCALL(aStubbedTrainerRankings_ColosseumWins);
    LD_DE(mDisplayLinkBattleResult_YouWin);
    goto store_result;


lose:
    FARCALL(aStubbedTrainerRankings_ColosseumLosses);
    LD_DE(mDisplayLinkBattleResult_YouLose);
    goto store_result;


store_result:
    hlcoord(6, 8, wTilemap);
    CALL(aPlaceString);
    FARCALL(aBackupMobileEventIndex);
    LD_C(200);
    CALL(aDelayFrames);

    LD_A(MBANK(asLinkBattleStats));
    CALL(aOpenSRAM);

    CALL(aAddLastLinkBattleToLinkRecord);
    CALL(aReadAndPrintLinkBattleRecord);

    CALL(aCloseSRAM);

    CALL(aIsMobileBattle2);
    IF_Z goto mobile;
    CALL(aWaitPressAorB_BlinkCursor);
    CALL(aClearTilemap);
    RET;


mobile:
    LD_C(200);
    CALL(aDelayFrames);
    CALL(aClearTilemap);
    RET;


YouWin:
    //db ['"YOU WIN@"'];

YouLose:
    //db ['"YOU LOSE@"'];

Draw:
    //db ['"  DRAW@"'];


Mobile_InvalidBattle:
    hlcoord(6, 8, wTilemap);
    LD_DE(mDisplayLinkBattleResult_InvalidBattle);
    CALL(aPlaceString);
    LD_C(200);
    CALL(aDelayFrames);
    CALL(aClearTilemap);
    RET;


InvalidBattle:
    //db ['"INVALID BATTLE@"'];

    return IsMobileBattle2();
}

void IsMobileBattle2(void){
    LD_A_addr(wLinkMode);
    CP_A(LINK_MOBILE);
    RET;

}

void v_DisplayLinkRecord(void){
    LD_A(MBANK(asLinkBattleStats));
    CALL(aOpenSRAM);

    CALL(aReadAndPrintLinkBattleRecord);

    CALL(aCloseSRAM);
    hlcoord(0, 0, wAttrmap);
    XOR_A_A;
    LD_BC(SCREEN_WIDTH * SCREEN_HEIGHT);
    CALL(aByteFill);
    CALL(aWaitBGMap2);
    LD_B(SCGB_DIPLOMA);
    CALL(aGetSGBLayout);
    CALL(aSetPalettes);
    LD_C(8);
    CALL(aDelayFrames);
    CALL(aWaitPressAorB_BlinkCursor);
    RET;

}

void ReadAndPrintLinkBattleRecord(void){
    CALL(aClearTilemap);
    CALL(aClearSprites);
    CALL(aReadAndPrintLinkBattleRecord_PrintBattleRecord);
    hlcoord(0, 8, wTilemap);
    LD_B(NUM_LINK_BATTLE_RECORDS);
    LD_DE(sLinkBattleRecord1Name);

loop:
    PUSH_BC;
    PUSH_HL;
    PUSH_DE;
    LD_A_de;
    AND_A_A;
    IF_Z goto PrintFormatString;
    LD_A_addr(wSavedAtLeastOnce);
    AND_A_A;
    IF_Z goto PrintFormatString;
    PUSH_HL;
    PUSH_HL;
    LD_H_D;
    LD_L_E;
    LD_DE(wLinkBattleRecordName);
    LD_BC(NAME_LENGTH - 1);
    CALL(aCopyBytes);
    LD_A(0x50);
    LD_de_A;
    INC_DE;  // wLinkBattleRecordWins
    LD_BC(6);
    CALL(aCopyBytes);
    LD_DE(wLinkBattleRecordName);
    POP_HL;
    CALL(aPlaceString);
    POP_HL;
    LD_DE(26);
    ADD_HL_DE;
    PUSH_HL;
    LD_DE(wLinkBattleRecordWins);
    LD_BC((2 << 8) | 4);
    CALL(aPrintNum);
    POP_HL;
    LD_DE(5);
    ADD_HL_DE;
    PUSH_HL;
    LD_DE(wLinkBattleRecordLosses);
    LD_BC((2 << 8) | 4);
    CALL(aPrintNum);
    POP_HL;
    LD_DE(5);
    ADD_HL_DE;
    LD_DE(wLinkBattleRecordDraws);
    LD_BC((2 << 8) | 4);
    CALL(aPrintNum);
    goto next;


PrintFormatString:
    LD_DE(mReadAndPrintLinkBattleRecord_Format);
    CALL(aPlaceString);

next:
    POP_HL;
    LD_BC(LINK_BATTLE_RECORD_LENGTH);
    ADD_HL_BC;
    LD_D_H;
    LD_E_L;
    POP_HL;
    LD_BC(2 * SCREEN_WIDTH);
    ADD_HL_BC;
    POP_BC;
    DEC_B;
    IF_NZ goto loop;
    RET;


PrintBattleRecord:
    hlcoord(1, 0, wTilemap);
    LD_DE(mReadAndPrintLinkBattleRecord_Record);
    CALL(aPlaceString);

    hlcoord(0, 6, wTilemap);
    LD_DE(mReadAndPrintLinkBattleRecord_Result);
    CALL(aPlaceString);

    hlcoord(0, 2, wTilemap);
    LD_DE(mReadAndPrintLinkBattleRecord_Total);
    CALL(aPlaceString);

    hlcoord(6, 4, wTilemap);
    LD_DE(sLinkBattleWins);
    CALL(aReadAndPrintLinkBattleRecord_PrintZerosIfNoSaveFileExists);
    IF_C goto quit;

    LD_BC((2 << 8) | 4);
    CALL(aPrintNum);

    hlcoord(11, 4, wTilemap);
    LD_DE(sLinkBattleLosses);
    CALL(aReadAndPrintLinkBattleRecord_PrintZerosIfNoSaveFileExists);

    LD_BC((2 << 8) | 4);
    CALL(aPrintNum);

    hlcoord(16, 4, wTilemap);
    LD_DE(sLinkBattleDraws);
    CALL(aReadAndPrintLinkBattleRecord_PrintZerosIfNoSaveFileExists);

    LD_BC((2 << 8) | 4);
    CALL(aPrintNum);


quit:
    RET;


PrintZerosIfNoSaveFileExists:
    LD_A_addr(wSavedAtLeastOnce);
    AND_A_A;
    RET_NZ ;
    LD_DE(mReadAndPrintLinkBattleRecord_Scores);
    CALL(aPlaceString);
    SCF;
    RET;


Scores:
    //db ['"   0    0    0@"'];


Format:
    //db ['"  ---  <LF>"'];
    //db ['"         -    -    -@"'];

Record:
    //db ['"<PLAYER>\'s RECORD@"'];

Result:
    //db ['"RESULT WIN LOSE DRAW@"'];

Total:
    //db ['"TOTAL  WIN LOSE DRAW@"'];

    return BattleEnd_HandleRoamMons();
}

void BattleEnd_HandleRoamMons(void){
    LD_A_addr(wBattleType);
    CP_A(BATTLETYPE_ROAMING);
    IF_NZ goto not_roaming;
    LD_A_addr(wBattleResult);
    AND_A(0xf);
    IF_Z goto caught_or_defeated_roam_mon;  // WIN
    CALL(aGetRoamMonHP);
    LD_A_addr(wEnemyMonHP + 1);
    LD_hl_A;
    goto update_roam_mons;


caught_or_defeated_roam_mon:
    CALL(aGetRoamMonHP);
    LD_hl(0);
    CALL(aGetRoamMonMapGroup);
    LD_hl(GROUP_N_A);
    CALL(aGetRoamMonMapNumber);
    LD_hl(MAP_N_A);
    CALL(aGetRoamMonSpecies);
    LD_hl(0);
    RET;


not_roaming:
    CALL(aBattleRandom);
    AND_A(0xf);
    RET_NZ ;


update_roam_mons:
    CALLFAR(aUpdateRoamMons);
    RET;

}

void GetRoamMonMapGroup(void){
    LD_A_addr(wTempEnemyMonSpecies);
    LD_B_A;
    LD_A_addr(wRoamMon1Species);
    CP_A_B;
    LD_HL(wRoamMon1MapGroup);
    RET_Z ;
    LD_A_addr(wRoamMon2Species);
    CP_A_B;
    LD_HL(wRoamMon2MapGroup);
    RET_Z ;
    LD_HL(wRoamMon3MapGroup);
    RET;

}

void GetRoamMonMapNumber(void){
    LD_A_addr(wTempEnemyMonSpecies);
    LD_B_A;
    LD_A_addr(wRoamMon1Species);
    CP_A_B;
    LD_HL(wRoamMon1MapNumber);
    RET_Z ;
    LD_A_addr(wRoamMon2Species);
    CP_A_B;
    LD_HL(wRoamMon2MapNumber);
    RET_Z ;
    LD_HL(wRoamMon3MapNumber);
    RET;

}

void GetRoamMonHP(void){
//  output: hl = wRoamMonHP
    LD_A_addr(wTempEnemyMonSpecies);
    LD_B_A;
    LD_A_addr(wRoamMon1Species);
    CP_A_B;
    LD_HL(wRoamMon1HP);
    RET_Z ;
    LD_A_addr(wRoamMon2Species);
    CP_A_B;
    LD_HL(wRoamMon2HP);
    RET_Z ;
    LD_HL(wRoamMon3HP);
    RET;

}

void GetRoamMonDVs(void){
//  output: hl = wRoamMonDVs
    LD_A_addr(wTempEnemyMonSpecies);
    LD_B_A;
    LD_A_addr(wRoamMon1Species);
    CP_A_B;
    LD_HL(wRoamMon1DVs);
    RET_Z ;
    LD_A_addr(wRoamMon2Species);
    CP_A_B;
    LD_HL(wRoamMon2DVs);
    RET_Z ;
    LD_HL(wRoamMon3DVs);
    RET;

}

void GetRoamMonSpecies(void){
    LD_A_addr(wTempEnemyMonSpecies);
    LD_HL(wRoamMon1Species);
    CP_A_hl;
    RET_Z ;
    LD_HL(wRoamMon2Species);
    CP_A_hl;
    RET_Z ;
    LD_HL(wRoamMon3Species);
    RET;

}

void AddLastLinkBattleToLinkRecord(void){
    LD_HL(wOTPlayerID);
    LD_DE(wStringBuffer1);
    LD_BC(2);
    CALL(aCopyBytes);
    LD_HL(wOTPlayerName);
    LD_BC(NAME_LENGTH - 1);
    CALL(aCopyBytes);
    LD_HL(sLinkBattleStats - (LINK_BATTLE_RECORD_LENGTH - 6));
    CALL(aAddLastLinkBattleToLinkRecord_StoreResult);
    LD_HL(sLinkBattleRecord);
    LD_D(NUM_LINK_BATTLE_RECORDS);

loop:
    PUSH_HL;
    INC_HL;
    INC_HL;
    LD_A_hl;
    DEC_HL;
    DEC_HL;
    AND_A_A;
    IF_Z goto copy;
    PUSH_DE;
    LD_BC(LINK_BATTLE_RECORD_LENGTH - 6);
    LD_DE(wStringBuffer1);
    CALL(aCompareBytesLong);
    POP_DE;
    POP_HL;
    IF_C goto done;
    LD_BC(LINK_BATTLE_RECORD_LENGTH);
    ADD_HL_BC;
    DEC_D;
    IF_NZ goto loop;
    LD_BC(-LINK_BATTLE_RECORD_LENGTH);
    ADD_HL_BC;
    PUSH_HL;


copy:
    LD_D_H;
    LD_E_L;
    LD_HL(wStringBuffer1);
    LD_BC(LINK_BATTLE_RECORD_LENGTH - 6);
    CALL(aCopyBytes);
    LD_B(6);
    XOR_A_A;

loop2:
    LD_de_A;
    INC_DE;
    DEC_B;
    IF_NZ goto loop2;
    POP_HL;


done:
    CALL(aAddLastLinkBattleToLinkRecord_StoreResult);
    CALL(aAddLastLinkBattleToLinkRecord_FindOpponentAndAppendRecord);
    RET;


StoreResult:
    LD_A_addr(wBattleResult);
    AND_A(0xf);
    CP_A(LOSE);
    LD_BC((sLinkBattleRecord1Wins - sLinkBattleRecord1) + 1);
    IF_C goto okay;  // WIN
    LD_BC((sLinkBattleRecord1Losses - sLinkBattleRecord1) + 1);
    IF_Z goto okay;  // LOSE
// DRAW
    LD_BC((sLinkBattleRecord1Draws - sLinkBattleRecord1) + 1);

okay:
    ADD_HL_BC;
    CALL(aAddLastLinkBattleToLinkRecord_CheckOverflow);
    RET_NC ;
    INC_hl;
    RET_NZ ;
    DEC_HL;
    INC_hl;
    RET;


CheckOverflow:
    DEC_HL;
    LD_A_hl;
    INC_HL;
    CP_A(HIGH(MAX_LINK_RECORD));
    RET_C ;
    LD_A_hl;
    CP_A(LOW(MAX_LINK_RECORD));
    RET;


FindOpponentAndAppendRecord:
    LD_B(NUM_LINK_BATTLE_RECORDS);
    LD_HL(sLinkBattleRecord1End - 1);
    LD_DE(wLinkBattleRecordBuffer);

loop3:
    PUSH_BC;
    PUSH_DE;
    PUSH_HL;
    CALL(aAddLastLinkBattleToLinkRecord_LoadPointer);
    POP_HL;
    LD_A_E;
    POP_DE;
    LD_de_A;
    INC_DE;
    LD_A_B;
    LD_de_A;
    INC_DE;
    LD_A_C;
    LD_de_A;
    INC_DE;
    LD_BC(LINK_BATTLE_RECORD_LENGTH);
    ADD_HL_BC;
    POP_BC;
    DEC_B;
    IF_NZ goto loop3;
    LD_B(0x0);
    LD_C(0x1);

loop4:
    LD_A_B;
    ADD_A_B;
    ADD_A_B;
    LD_E_A;
    LD_D(0);
    LD_HL(wLinkBattleRecordBuffer);
    ADD_HL_DE;
    PUSH_HL;
    LD_A_C;
    ADD_A_C;
    ADD_A_C;
    LD_E_A;
    LD_D(0);
    LD_HL(wLinkBattleRecordBuffer);
    ADD_HL_DE;
    LD_D_H;
    LD_E_L;
    POP_HL;
    PUSH_BC;
    LD_C(3);
    CALL(aCompareBytes);
    POP_BC;
    IF_Z goto equal;
    IF_NC goto done2;


equal:
    INC_C;
    LD_A_C;
    CP_A(0x5);
    IF_NZ goto loop4;
    INC_B;
    LD_C_B;
    INC_C;
    LD_A_B;
    CP_A(0x4);
    IF_NZ goto loop4;
    RET;


done2:
    PUSH_BC;
    LD_A_B;
    LD_BC(LINK_BATTLE_RECORD_LENGTH);
    LD_HL(sLinkBattleRecord);
    CALL(aAddNTimes);
    PUSH_HL;
    LD_DE(wLinkBattleRecordBuffer);
    LD_BC(LINK_BATTLE_RECORD_LENGTH);
    CALL(aCopyBytes);
    POP_HL;
    POP_BC;
    PUSH_HL;
    LD_A_C;
    LD_BC(LINK_BATTLE_RECORD_LENGTH);
    LD_HL(sLinkBattleRecord);
    CALL(aAddNTimes);
    POP_DE;
    PUSH_HL;
    LD_BC(LINK_BATTLE_RECORD_LENGTH);
    CALL(aCopyBytes);
    LD_HL(wLinkBattleRecordBuffer);
    LD_BC(LINK_BATTLE_RECORD_LENGTH);
    POP_DE;
    CALL(aCopyBytes);
    RET;


LoadPointer:
    LD_E(0x0);
    LD_A_hld;
    LD_C_A;
    LD_A_hld;
    LD_B_A;
    LD_A_hld;
    ADD_A_C;
    LD_C_A;
    LD_A_hld;
    ADC_A_B;
    LD_B_A;
    IF_NC goto okay2;
    INC_E;


okay2:
    LD_A_hld;
    ADD_A_C;
    LD_C_A;
    LD_A_hl;
    ADC_A_B;
    LD_B_A;
    RET_NC ;
    INC_E;
    RET;

}

void InitBattleDisplay(void){
    CALL(aInitBattleDisplay_InitBackPic);
    hlcoord(0, 12, wTilemap);
    LD_B(4);
    LD_C(18);
    CALL(aTextbox);
    FARCALL(aMobileTextBorder);
    hlcoord(1, 5, wTilemap);
    LD_BC((3 << 8) | 7);
    CALL(aClearBox);
    CALL(aLoadStandardFont);
    CALL(av_LoadBattleFontsHPBar);
    CALL(aInitBattleDisplay_BlankBGMap);
    XOR_A_A;
    LDH_addr_A(hMapAnims);
    LDH_addr_A(hSCY);
    LD_A(0x90);
    LDH_addr_A(hWY);
    LDH_addr_A(rWY);
    CALL(aWaitBGMap);
    XOR_A_A;
    LDH_addr_A(hBGMapMode);
    FARCALL(aBattleIntroSlidingPics);
    LD_A(0x1);
    LDH_addr_A(hBGMapMode);
    LD_A(0x31);
    LDH_addr_A(hGraphicStartTile);
    hlcoord(2, 6, wTilemap);
    LD_BC((6 << 8) | 6);
    PREDEF(pPlaceGraphic);
    XOR_A_A;
    LDH_addr_A(hWY);
    LDH_addr_A(rWY);
    CALL(aWaitBGMap);
    CALL(aHideSprites);
    LD_B(SCGB_BATTLE_COLORS);
    CALL(aGetSGBLayout);
    CALL(aSetPalettes);
    LD_A(0x90);
    LDH_addr_A(hWY);
    XOR_A_A;
    LDH_addr_A(hSCX);
    RET;


BlankBGMap:
    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(MBANK(awDecompressScratch));
    LDH_addr_A(rSVBK);

    LD_HL(wDecompressScratch);
    LD_BC(BG_MAP_WIDTH * BG_MAP_HEIGHT);
    LD_A(0x7f);
    CALL(aByteFill);

    LD_DE(wDecompressScratch);
    hlbgcoord(0, 0, vBGMap0);
    //LD_BC((BANK(@) << 8) | (BG_MAP_WIDTH * BG_MAP_HEIGHT) / LEN_2BPP_TILE);
    LD_BC((BANK(aInitBattleDisplay_BlankBGMap) << 8) | (BG_MAP_WIDTH * BG_MAP_HEIGHT) / LEN_2BPP_TILE);
    CALL(aRequest2bpp);

    POP_AF;
    LDH_addr_A(rSVBK);
    RET;


InitBackPic:
    CALL(aGetTrainerBackpic);
    CALL(aCopyBackpic);
    RET;

}

void GetTrainerBackpic(void){
//  Load the player character's backpic (6x6) into VRAM starting from vTiles2 tile $31.

//  Special exception for Dude.
    LD_B(BANK(aDudeBackpic));
    LD_HL(mDudeBackpic);
    LD_A_addr(wBattleType);
    CP_A(BATTLETYPE_TUTORIAL);
    IF_Z goto Decompress;

//  What gender are we?
    LD_A_addr(wPlayerSpriteSetupFlags);
    BIT_A(PLAYERSPRITESETUP_FEMALE_TO_MALE_F);
    IF_NZ goto Chris;
    LD_A_addr(wPlayerGender);
    BIT_A(PLAYERGENDER_FEMALE_F);
    IF_Z goto Chris;

//  It's a girl.
    FARCALL(aGetKrisBackpic);
    RET;


Chris:
//  It's a boy.
    LD_B(BANK(aChrisBackpic));
    LD_HL(mChrisBackpic);


Decompress:
    LD_DE(vTiles2 + LEN_2BPP_TILE * 0x31);
    LD_C(7 * 7);
    PREDEF(pDecompressGet2bpp);
    RET;

}

void CopyBackpic(void){
    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(MBANK(awDecompressScratch));
    LDH_addr_A(rSVBK);
    LD_HL(vTiles0);
    LD_DE(vTiles2 + LEN_2BPP_TILE * 0x31);
    LDH_A_addr(hROMBank);
    LD_B_A;
    LD_C(7 * 7);
    CALL(aGet2bpp);
    POP_AF;
    LDH_addr_A(rSVBK);
    CALL(aCopyBackpic_LoadTrainerBackpicAsOAM);
    LD_A(0x31);
    LDH_addr_A(hGraphicStartTile);
    hlcoord(2, 6, wTilemap);
    LD_BC((6 << 8) | 6);
    PREDEF(pPlaceGraphic);
    RET;


LoadTrainerBackpicAsOAM:
    LD_HL(wVirtualOAMSprite00);
    XOR_A_A;
    LDH_addr_A(hMapObjectIndex);
    LD_B(6);
    LD_E((SCREEN_WIDTH + 1) * TILE_WIDTH);

outer_loop:
    LD_C(3);
    LD_D(8 * TILE_WIDTH);

inner_loop:
    LD_hl_D;  // y
    INC_HL;
    LD_hl_E;  // x
    INC_HL;
    LDH_A_addr(hMapObjectIndex);
    LD_hli_A;  // tile id
    INC_A;
    LDH_addr_A(hMapObjectIndex);
    LD_A(PAL_BATTLE_OB_PLAYER);
    LD_hli_A;  // attributes
    LD_A_D;
    ADD_A(1 * TILE_WIDTH);
    LD_D_A;
    DEC_C;
    IF_NZ goto inner_loop;
    LDH_A_addr(hMapObjectIndex);
    ADD_A(0x3);
    LDH_addr_A(hMapObjectIndex);
    LD_A_E;
    ADD_A(1 * TILE_WIDTH);
    LD_E_A;
    DEC_B;
    IF_NZ goto outer_loop;
    RET;

}

void BattleStartMessage(void){
    LD_A_addr(wBattleMode);
    DEC_A;
    IF_Z goto wild;

    LD_DE(SFX_SHINE);
    CALL(aPlaySFX);
    CALL(aWaitSFX);

    LD_C(20);
    CALL(aDelayFrames);

    FARCALL(aBattle_GetTrainerName);

    LD_HL(mWantsToBattleText);
    goto PlaceBattleStartText;


wild:
    CALL(aBattleCheckEnemyShininess);
    IF_NC goto not_shiny;

    XOR_A_A;
    LD_addr_A(wNumHits);
    LD_A(1);
    LDH_addr_A(hBattleTurn);
    LD_A(1);
    LD_addr_A(wBattleAnimParam);
    LD_DE(ANIM_SEND_OUT_MON);
    CALL(aCall_PlayBattleAnim);


not_shiny:
    FARCALL(aCheckSleepingTreeMon);
    IF_C goto skip_cry;

    FARCALL(aCheckBattleScene);
    IF_C goto cry_no_anim;

    // hlcoord(12, 0, wTilemap);
    // LD_D(0x0);
    // LD_E(ANIM_MON_NORMAL);
    // PREDEF(pAnimateFrontpic);
    AnimateFrontpic_Conv(coord(12, 0, wram->wTilemap), 0x0, ANIM_MON_NORMAL);
    goto skip_cry;  // cry is played during the animation


cry_no_anim:
    LD_A(0xf);
    LD_addr_A(wCryTracks);
    LD_A_addr(wTempEnemyMonSpecies);
    CALL(aPlayStereoCry);


skip_cry:
    LD_A_addr(wBattleType);
    CP_A(BATTLETYPE_FISH);
    IF_NZ goto NotFishing;

    FARCALL(aStubbedTrainerRankings_HookedEncounters);

    LD_HL(mHookedPokemonAttackedText);
    goto PlaceBattleStartText;


NotFishing:
    LD_HL(mPokemonFellFromTreeText);
    CP_A(BATTLETYPE_TREE);
    IF_Z goto PlaceBattleStartText;
    LD_HL(mWildCelebiAppearedText);
    CP_A(BATTLETYPE_CELEBI);
    IF_Z goto PlaceBattleStartText;
    LD_HL(mWildPokemonAppearedText);


PlaceBattleStartText:
    PUSH_HL;
    FARCALL(aBattleStart_TrainerHuds);
    POP_HL;
    CALL(aStdBattleTextbox);

    CALL(aIsMobileBattle2);
    RET_NZ ;

    LD_C(0x2);  // start
    FARCALL(aMobile_PrintOpponentBattleMessage);

    RET;

}
