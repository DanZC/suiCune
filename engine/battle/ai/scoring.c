#include "../../../constants.h"
#include "scoring.h"

void AIScoring(void){
//  //  used only for BANK(AIScoring)


    return AI_Basic();
}

void AI_Basic(void){
//  Don't do anything redundant:
//   -Using status-only moves if the player can't be statused
//   -Using moves that fail if they've already been used

    LD_HL(wEnemyAIMoveScores - 1);
    LD_DE(wEnemyMonMoves);
    LD_B(NUM_MOVES + 1);

checkmove:
    DEC_B;
    RET_Z ;

    INC_HL;
    LD_A_de;
    AND_A_A;
    RET_Z ;

    INC_DE;
    CALL(aAIGetEnemyMove);

    LD_A_addr(wEnemyMoveStruct + MOVE_EFFECT);
    LD_C_A;

//  Dismiss moves with special effects if they are
//  useless or not a good choice right now.
//  For example, healing moves, weather moves, Dream Eater...
    PUSH_HL;
    PUSH_DE;
    PUSH_BC;
    FARCALL(aAI_Redundant);
    POP_BC;
    POP_DE;
    POP_HL;
    IF_NZ goto discourage;

//  Dismiss status-only moves if the player can't be statused.
    LD_A_addr(wEnemyMoveStruct + MOVE_EFFECT);
    PUSH_HL;
    PUSH_DE;
    PUSH_BC;
    LD_HL(mStatusOnlyEffects);
    LD_DE(1);
    CALL(aIsInArray);

    POP_BC;
    POP_DE;
    POP_HL;
    IF_NC goto checkmove;

    LD_A_addr(wBattleMonStatus);
    AND_A_A;
    IF_NZ goto discourage;

//  Dismiss Safeguard if it's already active.
    LD_A_addr(wPlayerScreens);
    BIT_A(SCREENS_SAFEGUARD);
    IF_Z goto checkmove;


discourage:
    CALL(aAIDiscourageMove);
    goto checkmove;

// INCLUDE "data/battle/ai/status_only_effects.asm"


    return AI_Setup();
}

void AI_Setup(void){
//  Use stat-modifying moves on turn 1.

//  50% chance to greatly encourage stat-up moves during the first turn of enemy's Pokemon.
//  50% chance to greatly encourage stat-down moves during the first turn of player's Pokemon.
//  Almost 90% chance to greatly discourage stat-modifying moves otherwise.

    LD_HL(wEnemyAIMoveScores - 1);
    LD_DE(wEnemyMonMoves);
    LD_B(NUM_MOVES + 1);

checkmove:
    DEC_B;
    RET_Z ;

    INC_HL;
    LD_A_de;
    AND_A_A;
    RET_Z ;

    INC_DE;
    CALL(aAIGetEnemyMove);

    LD_A_addr(wEnemyMoveStruct + MOVE_EFFECT);

    CP_A(EFFECT_ATTACK_UP);
    IF_C goto checkmove;
    CP_A(EFFECT_EVASION_UP + 1);
    IF_C goto statup;

//     cp EFFECT_ATTACK_DOWN - 1
    IF_Z goto checkmove;
    CP_A(EFFECT_EVASION_DOWN + 1);
    IF_C goto statdown;

    CP_A(EFFECT_ATTACK_UP_2);
    IF_C goto checkmove;
    CP_A(EFFECT_EVASION_UP_2 + 1);
    IF_C goto statup;

//     cp EFFECT_ATTACK_DOWN_2 - 1
    IF_Z goto checkmove;
    CP_A(EFFECT_EVASION_DOWN_2 + 1);
    IF_C goto statdown;

    goto checkmove;


statup:
    LD_A_addr(wEnemyTurnsTaken);
    AND_A_A;
    IF_NZ goto discourage;

    goto encourage;


statdown:
    LD_A_addr(wPlayerTurnsTaken);
    AND_A_A;
    IF_NZ goto discourage;


encourage:
    CALL(aAI_50_50);
    IF_C goto checkmove;

    DEC_hl;
    DEC_hl;
    goto checkmove;


discourage:
    CALL(aRandom);
    CP_A(12 percent);
    IF_C goto checkmove;
    INC_hl;
    INC_hl;
    goto checkmove;


    return AI_Types();
}

void AI_Types(void){
//  Dismiss any move that the player is immune to.
//  Encourage super-effective moves.
//  Discourage not very effective moves unless
//  all damaging moves are of the same type.

    LD_HL(wEnemyAIMoveScores - 1);
    LD_DE(wEnemyMonMoves);
    LD_B(NUM_MOVES + 1);

checkmove:
    DEC_B;
    RET_Z ;

    INC_HL;
    LD_A_de;
    AND_A_A;
    RET_Z ;

    INC_DE;
    CALL(aAIGetEnemyMove);

    PUSH_HL;
    PUSH_BC;
    PUSH_DE;
    LD_A(1);
    LDH_addr_A(hBattleTurn);
    CALLFAR(aBattleCheckTypeMatchup);
    POP_DE;
    POP_BC;
    POP_HL;

    LD_A_addr(wTypeMatchup);
    AND_A_A;
    IF_Z goto immune;
    CP_A(EFFECTIVE);
    IF_Z goto checkmove;
    IF_C goto noteffective;

//  effective
    LD_A_addr(wEnemyMoveStruct + MOVE_POWER);
    AND_A_A;
    IF_Z goto checkmove;
    DEC_hl;
    goto checkmove;


noteffective:
//  Discourage this move if there are any moves
//  that do damage of a different type.
    PUSH_HL;
    PUSH_DE;
    PUSH_BC;
    LD_A_addr(wEnemyMoveStruct + MOVE_TYPE);
    LD_D_A;
    LD_HL(wEnemyMonMoves);
    LD_B(NUM_MOVES + 1);
    LD_C(0);

checkmove2:
    DEC_B;
    IF_Z goto movesdone;

    LD_A_hli;
    AND_A_A;
    IF_Z goto movesdone;

    CALL(aAIGetEnemyMove);
    LD_A_addr(wEnemyMoveStruct + MOVE_TYPE);
    CP_A_D;
    IF_Z goto checkmove2;
    LD_A_addr(wEnemyMoveStruct + MOVE_POWER);
    AND_A_A;
    IF_NZ goto damaging;
    goto checkmove2;


damaging:
    LD_C_A;

movesdone:
    LD_A_C;
    POP_BC;
    POP_DE;
    POP_HL;
    AND_A_A;
    IF_Z goto checkmove;
    INC_hl;
    goto checkmove;


immune:
    CALL(aAIDiscourageMove);
    goto checkmove;


    return AI_Offensive();
}

void AI_Offensive(void){
//  Greatly discourage non-damaging moves.

    LD_HL(wEnemyAIMoveScores - 1);
    LD_DE(wEnemyMonMoves);
    LD_B(NUM_MOVES + 1);

checkmove:
    DEC_B;
    RET_Z ;

    INC_HL;
    LD_A_de;
    AND_A_A;
    RET_Z ;

    INC_DE;
    CALL(aAIGetEnemyMove);

    LD_A_addr(wEnemyMoveStruct + MOVE_POWER);
    AND_A_A;
    IF_NZ goto checkmove;

    INC_hl;
    INC_hl;
    goto checkmove;


    return AI_Smart();
}

void AI_Smart(void){
    PEEK("");
//  Context-specific scoring.

    LD_HL(wEnemyAIMoveScores);
    LD_DE(wEnemyMonMoves);
    LD_B(NUM_MOVES + 1);

checkmove:
    DEC_B;
    RET_Z ;

    LD_A_de;
    INC_DE;
    AND_A_A;
    RET_Z ;

    PUSH_DE;
    PUSH_BC;
    PUSH_HL;
    CALL(aAIGetEnemyMove);

    LD_A_addr(wEnemyMoveStruct + MOVE_EFFECT);
    LD_HL(mAI_Smart_EffectHandlers);
    LD_DE(3);
    CALL(aIsInArray);

    INC_HL;
    IF_NC goto nextmove;

    LD_A_hli;
    LD_E_A;
    LD_D_hl;

    POP_HL;
    PUSH_HL;

    // LD_BC(mAI_Smart_nextmove);
    // PUSH_BC;

    // PUSH_DE;
    // RET;
    CALL_de;


nextmove:
    POP_HL;
    POP_BC;
    POP_DE;
    INC_HL;
    goto checkmove;

    return AI_Smart_EffectHandlers();
}

void AI_Smart_EffectHandlers(void){
    //dbw ['EFFECT_SLEEP', 'AI_Smart_Sleep']
    //dbw ['EFFECT_LEECH_HIT', 'AI_Smart_LeechHit']
    //dbw ['EFFECT_SELFDESTRUCT', 'AI_Smart_Selfdestruct']
    //dbw ['EFFECT_DREAM_EATER', 'AI_Smart_DreamEater']
    //dbw ['EFFECT_MIRROR_MOVE', 'AI_Smart_MirrorMove']
    //dbw ['EFFECT_EVASION_UP', 'AI_Smart_EvasionUp']
    //dbw ['EFFECT_ALWAYS_HIT', 'AI_Smart_AlwaysHit']
    //dbw ['EFFECT_ACCURACY_DOWN', 'AI_Smart_AccuracyDown']
    //dbw ['EFFECT_RESET_STATS', 'AI_Smart_ResetStats']
    //dbw ['EFFECT_BIDE', 'AI_Smart_Bide']
    //dbw ['EFFECT_FORCE_SWITCH', 'AI_Smart_ForceSwitch']
    //dbw ['EFFECT_HEAL', 'AI_Smart_Heal']
    //dbw ['EFFECT_TOXIC', 'AI_Smart_Toxic']
    //dbw ['EFFECT_LIGHT_SCREEN', 'AI_Smart_LightScreen']
    //dbw ['EFFECT_OHKO', 'AI_Smart_Ohko']
    //dbw ['EFFECT_RAZOR_WIND', 'AI_Smart_RazorWind']
    //dbw ['EFFECT_SUPER_FANG', 'AI_Smart_SuperFang']
    //dbw ['EFFECT_TRAP_TARGET', 'AI_Smart_TrapTarget']
    //dbw ['EFFECT_UNUSED_2B', 'AI_Smart_Unused2B']
    //dbw ['EFFECT_CONFUSE', 'AI_Smart_Confuse']
    //dbw ['EFFECT_SP_DEF_UP_2', 'AI_Smart_SpDefenseUp2']
    //dbw ['EFFECT_REFLECT', 'AI_Smart_Reflect']
    //dbw ['EFFECT_PARALYZE', 'AI_Smart_Paralyze']
    //dbw ['EFFECT_SPEED_DOWN_HIT', 'AI_Smart_SpeedDownHit']
    //dbw ['EFFECT_SUBSTITUTE', 'AI_Smart_Substitute']
    //dbw ['EFFECT_HYPER_BEAM', 'AI_Smart_HyperBeam']
    //dbw ['EFFECT_RAGE', 'AI_Smart_Rage']
    //dbw ['EFFECT_MIMIC', 'AI_Smart_Mimic']
    //dbw ['EFFECT_LEECH_SEED', 'AI_Smart_LeechSeed']
    //dbw ['EFFECT_DISABLE', 'AI_Smart_Disable']
    //dbw ['EFFECT_COUNTER', 'AI_Smart_Counter']
    //dbw ['EFFECT_ENCORE', 'AI_Smart_Encore']
    //dbw ['EFFECT_PAIN_SPLIT', 'AI_Smart_PainSplit']
    //dbw ['EFFECT_SNORE', 'AI_Smart_Snore']
    //dbw ['EFFECT_CONVERSION2', 'AI_Smart_Conversion2']
    //dbw ['EFFECT_LOCK_ON', 'AI_Smart_LockOn']
    //dbw ['EFFECT_DEFROST_OPPONENT', 'AI_Smart_DefrostOpponent']
    //dbw ['EFFECT_SLEEP_TALK', 'AI_Smart_SleepTalk']
    //dbw ['EFFECT_DESTINY_BOND', 'AI_Smart_DestinyBond']
    //dbw ['EFFECT_REVERSAL', 'AI_Smart_Reversal']
    //dbw ['EFFECT_SPITE', 'AI_Smart_Spite']
    //dbw ['EFFECT_HEAL_BELL', 'AI_Smart_HealBell']
    //dbw ['EFFECT_PRIORITY_HIT', 'AI_Smart_PriorityHit']
    //dbw ['EFFECT_THIEF', 'AI_Smart_Thief']
    //dbw ['EFFECT_MEAN_LOOK', 'AI_Smart_MeanLook']
    //dbw ['EFFECT_NIGHTMARE', 'AI_Smart_Nightmare']
    //dbw ['EFFECT_FLAME_WHEEL', 'AI_Smart_FlameWheel']
    //dbw ['EFFECT_CURSE', 'AI_Smart_Curse']
    //dbw ['EFFECT_PROTECT', 'AI_Smart_Protect']
    //dbw ['EFFECT_FORESIGHT', 'AI_Smart_Foresight']
    //dbw ['EFFECT_PERISH_SONG', 'AI_Smart_PerishSong']
    //dbw ['EFFECT_SANDSTORM', 'AI_Smart_Sandstorm']
    //dbw ['EFFECT_ENDURE', 'AI_Smart_Endure']
    //dbw ['EFFECT_ROLLOUT', 'AI_Smart_Rollout']
    //dbw ['EFFECT_SWAGGER', 'AI_Smart_Swagger']
    //dbw ['EFFECT_FURY_CUTTER', 'AI_Smart_FuryCutter']
    //dbw ['EFFECT_ATTRACT', 'AI_Smart_Attract']
    //dbw ['EFFECT_SAFEGUARD', 'AI_Smart_Safeguard']
    //dbw ['EFFECT_MAGNITUDE', 'AI_Smart_Magnitude']
    //dbw ['EFFECT_BATON_PASS', 'AI_Smart_BatonPass']
    //dbw ['EFFECT_PURSUIT', 'AI_Smart_Pursuit']
    //dbw ['EFFECT_RAPID_SPIN', 'AI_Smart_RapidSpin']
    //dbw ['EFFECT_MORNING_SUN', 'AI_Smart_MorningSun']
    //dbw ['EFFECT_SYNTHESIS', 'AI_Smart_Synthesis']
    //dbw ['EFFECT_MOONLIGHT', 'AI_Smart_Moonlight']
    //dbw ['EFFECT_HIDDEN_POWER', 'AI_Smart_HiddenPower']
    //dbw ['EFFECT_RAIN_DANCE', 'AI_Smart_RainDance']
    //dbw ['EFFECT_SUNNY_DAY', 'AI_Smart_SunnyDay']
    //dbw ['EFFECT_BELLY_DRUM', 'AI_Smart_BellyDrum']
    //dbw ['EFFECT_PSYCH_UP', 'AI_Smart_PsychUp']
    //dbw ['EFFECT_MIRROR_COAT', 'AI_Smart_MirrorCoat']
    //dbw ['EFFECT_SKULL_BASH', 'AI_Smart_SkullBash']
    //dbw ['EFFECT_TWISTER', 'AI_Smart_Twister']
    //dbw ['EFFECT_EARTHQUAKE', 'AI_Smart_Earthquake']
    //dbw ['EFFECT_FUTURE_SIGHT', 'AI_Smart_FutureSight']
    //dbw ['EFFECT_GUST', 'AI_Smart_Gust']
    //dbw ['EFFECT_STOMP', 'AI_Smart_Stomp']
    //dbw ['EFFECT_SOLARBEAM', 'AI_Smart_Solarbeam']
    //dbw ['EFFECT_THUNDER', 'AI_Smart_Thunder']
    //dbw ['EFFECT_FLY', 'AI_Smart_Fly']
    //db ['-1'];  // end

    return AI_Smart_Sleep();
}

void AI_Smart_Sleep(void){
//  Greatly encourage sleep inducing moves if the enemy has either Dream Eater or Nightmare.
//  50% chance to greatly encourage sleep inducing moves otherwise.

    LD_B(EFFECT_DREAM_EATER);
    CALL(aAIHasMoveEffect);
    IF_C goto encourage;

    LD_B(EFFECT_NIGHTMARE);
    CALL(aAIHasMoveEffect);
    RET_NC ;


encourage:
    CALL(aAI_50_50);
    RET_C ;
    DEC_hl;
    DEC_hl;
    RET;

}

void AI_Smart_LeechHit(void){
    PUSH_HL;
    LD_A(1);
    LDH_addr_A(hBattleTurn);
    CALLFAR(aBattleCheckTypeMatchup);
    POP_HL;

//  60% chance to discourage this move if not very effective.
    LD_A_addr(wTypeMatchup);
    CP_A(EFFECTIVE);
    IF_C goto discourage;

//  Do nothing if effectiveness is neutral.
    RET_Z ;

//  Do nothing if enemy's HP is full.
    CALL(aAICheckEnemyMaxHP);
    RET_C ;

//  80% chance to encourage this move otherwise.
    CALL(aAI_80_20);
    RET_C ;

    DEC_hl;
    RET;


discourage:
    CALL(aRandom);
    CP_A(39 percent + 1);
    RET_C ;

    INC_hl;
    RET;

}

void AI_Smart_LockOn(void){
    LD_A_addr(wPlayerSubStatus5);
    BIT_A(SUBSTATUS_LOCK_ON);
    IF_NZ goto player_locked_on;

    PUSH_HL;
    CALL(aAICheckEnemyQuarterHP);
    IF_NC goto discourage;

    CALL(aAICheckEnemyHalfHP);
    IF_C goto skip_speed_check;

    CALL(aAICompareSpeed);
    IF_NC goto discourage;


skip_speed_check:
    LD_A_addr(wPlayerEvaLevel);
    CP_A(BASE_STAT_LEVEL + 3);
    IF_NC goto maybe_encourage;
    CP_A(BASE_STAT_LEVEL + 1);
    IF_NC goto do_nothing;

    LD_A_addr(wEnemyAccLevel);
    CP_A(BASE_STAT_LEVEL - 2);
    IF_C goto maybe_encourage;
    CP_A(BASE_STAT_LEVEL);
    IF_C goto do_nothing;

    LD_HL(wEnemyMonMoves);
    LD_C(NUM_MOVES + 1);

checkmove:
    DEC_C;
    IF_Z goto discourage;

    LD_A_hli;
    AND_A_A;
    IF_Z goto discourage;

    CALL(aAIGetEnemyMove);

    LD_A_addr(wEnemyMoveStruct + MOVE_ACC);
    CP_A(71 percent - 1);
    IF_NC goto checkmove;

    LD_A(1);
    LDH_addr_A(hBattleTurn);

    PUSH_HL;
    PUSH_BC;
    FARCALL(aBattleCheckTypeMatchup);
    LD_A_addr(wTypeMatchup);
    CP_A(EFFECTIVE);
    POP_BC;
    POP_HL;
    IF_C goto checkmove;


do_nothing:
    POP_HL;
    RET;


discourage:
    POP_HL;
    INC_hl;
    RET;


maybe_encourage:
    POP_HL;
    CALL(aAI_50_50);
    RET_C ;

    DEC_hl;
    DEC_hl;
    RET;


player_locked_on:
    PUSH_HL;
    LD_HL(wEnemyAIMoveScores - 1);
    LD_DE(wEnemyMonMoves);
    LD_C(NUM_MOVES + 1);


checkmove2:
    INC_HL;
    DEC_C;
    IF_Z goto dismiss;

    LD_A_de;
    AND_A_A;
    IF_Z goto dismiss;

    INC_DE;
    CALL(aAIGetEnemyMove);

    LD_A_addr(wEnemyMoveStruct + MOVE_ACC);
    CP_A(71 percent - 1);
    IF_NC goto checkmove2;

    DEC_hl;
    DEC_hl;
    goto checkmove2;


dismiss:
    POP_HL;
    JP(mAIDiscourageMove);

}

void AI_Smart_Selfdestruct(void){
//  Selfdestruct, Explosion

//  Unless this is the enemy's last Pokemon...
    PUSH_HL;
    FARCALL(aFindAliveEnemyMons);
    POP_HL;
    IF_NC goto notlastmon;

//  ...greatly discourage this move unless this is the player's last Pokemon too.
    PUSH_HL;
    CALL(aAICheckLastPlayerMon);
    POP_HL;
    IF_NZ goto discourage;


notlastmon:
//  Greatly discourage this move if enemy's HP is above 50%.
    CALL(aAICheckEnemyHalfHP);
    IF_C goto discourage;

//  Do nothing if enemy's HP is below 25%.
    CALL(aAICheckEnemyQuarterHP);
    RET_NC ;

//  If enemy's HP is between 25% and 50%,
//  over 90% chance to greatly discourage this move.
    CALL(aRandom);
    CP_A(8 percent);
    RET_C ;


discourage:
    INC_hl;
    INC_hl;
    INC_hl;
    RET;

}

void AI_Smart_DreamEater(void){
//  90% chance to greatly encourage this move.
//  The AI_Basic layer will make sure that
//  Dream Eater is only used against sleeping targets.
    CALL(aRandom);
    CP_A(10 percent);
    RET_C ;
    DEC_hl;
    DEC_hl;
    DEC_hl;
    RET;

}

void AI_Smart_EvasionUp(void){
//  Dismiss this move if enemy's evasion can't raise anymore.
    LD_A_addr(wEnemyEvaLevel);
    CP_A(MAX_STAT_LEVEL);
    JP_NC (mAIDiscourageMove);

//  If enemy's HP is full...
    CALL(aAICheckEnemyMaxHP);
    IF_NC goto hp_mismatch_1;

//  ...greatly encourage this move if player is badly poisoned.
    LD_A_addr(wPlayerSubStatus5);
    BIT_A(SUBSTATUS_TOXIC);
    IF_NZ goto greatly_encourage;

//  ...70% chance to greatly encourage this move if player is not badly poisoned.
    CALL(aRandom);
    CP_A(70 percent);
    IF_NC goto not_encouraged;


greatly_encourage:
    DEC_hl;
    DEC_hl;
    RET;


hp_mismatch_1:

//  Greatly discourage this move if enemy's HP is below 25%.
    CALL(aAICheckEnemyQuarterHP);
    IF_NC goto hp_mismatch_2;

//  If enemy's HP is above 25% but not full, 4% chance to greatly encourage this move.
    CALL(aRandom);
    CP_A(4 percent);
    IF_C goto greatly_encourage;

//  If enemy's HP is between 25% and 50%,...
    CALL(aAICheckEnemyHalfHP);
    IF_NC goto hp_mismatch_3;

//  If enemy's HP is above 50% but not full, 20% chance to greatly encourage this move.
    CALL(aAI_80_20);
    IF_C goto greatly_encourage;
    goto not_encouraged;


hp_mismatch_3:
//  ...50% chance to greatly discourage this move.
    CALL(aAI_50_50);
    IF_C goto not_encouraged;


hp_mismatch_2:
    INC_hl;
    INC_hl;

//  30% chance to end up here if enemy's HP is full and player is not badly poisoned.
//  77% chance to end up here if enemy's HP is above 50% but not full.
//  96% chance to end up here if enemy's HP is between 25% and 50%.
//  100% chance to end up here if enemy's HP is below 25%.
//  In other words, we only end up here if the move has not been encouraged or dismissed.

not_encouraged:
    LD_A_addr(wPlayerSubStatus5);
    BIT_A(SUBSTATUS_TOXIC);
    IF_NZ goto maybe_greatly_encourage;

    LD_A_addr(wPlayerSubStatus4);
    BIT_A(SUBSTATUS_LEECH_SEED);
    IF_NZ goto maybe_encourage;

//  Discourage this move if enemy's evasion level is higher than player's accuracy level.
    LD_A_addr(wEnemyEvaLevel);
    LD_B_A;
    LD_A_addr(wPlayerAccLevel);
    CP_A_B;
    IF_C goto discourage;

//  Greatly encourage this move if the player is in the middle of Fury Cutter or Rollout.
    LD_A_addr(wPlayerFuryCutterCount);
    AND_A_A;
    IF_NZ goto greatly_encourage;

    LD_A_addr(wPlayerSubStatus1);
    BIT_A(SUBSTATUS_ROLLOUT);
    IF_NZ goto greatly_encourage;


discourage:
    INC_hl;
    RET;

//  Player is badly poisoned.
//  70% chance to greatly encourage this move.
//  This would counter any previous discouragement.

maybe_greatly_encourage:
    CALL(aRandom);
    CP_A(31 percent + 1);
    RET_C ;

    DEC_hl;
    DEC_hl;
    RET;

//  Player is seeded.
//  50% chance to encourage this move.
//  This would partly counter any previous discouragement.

maybe_encourage:
    CALL(aAI_50_50);
    RET_C ;

    DEC_hl;
    RET;

}

void AI_Smart_AlwaysHit(void){
//  80% chance to greatly encourage this move if either...

//  ...enemy's accuracy level has been lowered three or more stages
    LD_A_addr(wEnemyAccLevel);
    CP_A(BASE_STAT_LEVEL - 2);
    IF_C goto encourage;

//  ...or player's evasion level has been raised three or more stages.
    LD_A_addr(wPlayerEvaLevel);
    CP_A(BASE_STAT_LEVEL + 3);
    RET_C ;


encourage:
    CALL(aAI_80_20);
    RET_C ;

    DEC_hl;
    DEC_hl;
    RET;

}

void AI_Smart_MirrorMove(void){
//  If the player did not use any move last turn...
    LD_A_addr(wLastPlayerCounterMove);
    AND_A_A;
    IF_NZ goto usedmove;

//  ...do nothing if enemy is slower than player
    CALL(aAICompareSpeed);
    RET_NC ;

//  ...or dismiss this move if enemy is faster than player.
    JP(mAIDiscourageMove);

//  If the player did use a move last turn...

usedmove:
    PUSH_HL;
    LD_HL(mUsefulMoves);
    LD_DE(1);
    CALL(aIsInArray);
    POP_HL;

//  ...do nothing if he didn't use a useful move.
    RET_NC ;

//  If he did, 50% chance to encourage this move...
    CALL(aAI_50_50);
    RET_C ;

    DEC_hl;

//  ...and 90% chance to encourage this move again if the enemy is faster.
    CALL(aAICompareSpeed);
    RET_NC ;

    CALL(aRandom);
    CP_A(10 percent);
    RET_C ;

    DEC_hl;
    RET;

}

void AI_Smart_AccuracyDown(void){
//  If player's HP is full...
    CALL(aAICheckPlayerMaxHP);
    IF_NC goto hp_mismatch_1;

//  ...and enemy's HP is above 50%...
    CALL(aAICheckEnemyHalfHP);
    IF_NC goto hp_mismatch_1;

//  ...greatly encourage this move if player is badly poisoned.
    LD_A_addr(wPlayerSubStatus5);
    BIT_A(SUBSTATUS_TOXIC);
    IF_NZ goto greatly_encourage;

//  ...70% chance to greatly encourage this move if player is not badly poisoned.
    CALL(aRandom);
    CP_A(70 percent);
    IF_NC goto not_encouraged;


greatly_encourage:
    DEC_hl;
    DEC_hl;
    RET;


hp_mismatch_1:

//  Greatly discourage this move if player's HP is below 25%.
    CALL(aAICheckPlayerQuarterHP);
    IF_NC goto hp_mismatch_2;

//  If player's HP is above 25% but not full, 4% chance to greatly encourage this move.
    CALL(aRandom);
    CP_A(4 percent);
    IF_C goto greatly_encourage;

//  If player's HP is between 25% and 50%,...
    CALL(aAICheckPlayerHalfHP);
    IF_NC goto hp_mismatch_3;

//  If player's HP is above 50% but not full, 20% chance to greatly encourage this move.
    CALL(aAI_80_20);
    IF_C goto greatly_encourage;
    goto not_encouraged;

//  ...50% chance to greatly discourage this move.

hp_mismatch_3:
    CALL(aAI_50_50);
    IF_C goto not_encouraged;


hp_mismatch_2:
    INC_hl;
    INC_hl;

//  We only end up here if the move has not been already encouraged.

not_encouraged:
    LD_A_addr(wPlayerSubStatus5);
    BIT_A(SUBSTATUS_TOXIC);
    IF_NZ goto maybe_greatly_encourage;

    LD_A_addr(wPlayerSubStatus4);
    BIT_A(SUBSTATUS_LEECH_SEED);
    IF_NZ goto encourage;

//  Discourage this move if enemy's evasion level is higher than player's accuracy level.
    LD_A_addr(wEnemyEvaLevel);
    LD_B_A;
    LD_A_addr(wPlayerAccLevel);
    CP_A_B;
    IF_C goto discourage;

//  Greatly encourage this move if the player is in the middle of Fury Cutter or Rollout.
    LD_A_addr(wPlayerFuryCutterCount);
    AND_A_A;
    IF_NZ goto greatly_encourage;

    LD_A_addr(wPlayerSubStatus1);
    BIT_A(SUBSTATUS_ROLLOUT);
    IF_NZ goto greatly_encourage;


discourage:
    INC_hl;
    RET;

//  Player is badly poisoned.
//  70% chance to greatly encourage this move.
//  This would counter any previous discouragement.

maybe_greatly_encourage:
    CALL(aRandom);
    CP_A(31 percent + 1);
    RET_C ;

    DEC_hl;
    DEC_hl;
    RET;

//  Player is seeded.
//  50% chance to encourage this move.
//  This would partly counter any previous discouragement.

encourage:
    CALL(aAI_50_50);
    RET_C ;

    DEC_hl;
    RET;

}

void AI_Smart_ResetStats(void){
//  85% chance to encourage this move if any of enemy's stat levels is lower than -2.
    PUSH_HL;
    LD_HL(wEnemyAtkLevel);
    LD_C(NUM_LEVEL_STATS);

enemystatsloop:
    DEC_C;
    IF_Z goto enemystatsdone;
    LD_A_hli;
    CP_A(BASE_STAT_LEVEL - 2);
    IF_C goto encourage;
    goto enemystatsloop;

//  85% chance to encourage this move if any of player's stat levels is higher than +2.

enemystatsdone:
    LD_HL(wPlayerAtkLevel);
    LD_C(NUM_LEVEL_STATS);

playerstatsloop:
    DEC_C;
    IF_Z goto discourage;
    LD_A_hli;
    CP_A(BASE_STAT_LEVEL + 3);
    IF_C goto playerstatsloop;


encourage:
    POP_HL;
    CALL(aRandom);
    CP_A(16 percent);
    RET_C ;
    DEC_hl;
    RET;

//  Discourage this move if neither:
//  Any of enemy's stat levels is    lower than -2.
//  Any of player's stat levels is higher than +2.

discourage:
    POP_HL;
    INC_hl;
    RET;

}

void AI_Smart_Bide(void){
//  90% chance to discourage this move unless enemy's HP is full.

    CALL(aAICheckEnemyMaxHP);
    RET_C ;
    CALL(aRandom);
    CP_A(10 percent);
    RET_C ;
    INC_hl;
    RET;

}

void AI_Smart_ForceSwitch(void){
//  Whirlwind, Roar.

//  Discourage this move if the player has not shown
//  a super-effective move against the enemy.
//  Consider player's type(s) if its moves are unknown.

    PUSH_HL;
    CALLFAR(aCheckPlayerMoveTypeMatchups);
    LD_A_addr(wEnemyAISwitchScore);
    CP_A(BASE_AI_SWITCH_SCORE);
    POP_HL;
    RET_C ;
    INC_hl;
    RET;

}

void AI_Smart_Heal(void){
    return AI_Smart_MorningSun();
}

void AI_Smart_MorningSun(void){
    return AI_Smart_Synthesis();
}

void AI_Smart_Synthesis(void){
    return AI_Smart_Moonlight();
}

void AI_Smart_Moonlight(void){
//  90% chance to greatly encourage this move if enemy's HP is below 25%.
//  Discourage this move if enemy's HP is higher than 50%.
//  Do nothing otherwise.

    CALL(aAICheckEnemyQuarterHP);
    IF_NC goto encourage;
    CALL(aAICheckEnemyHalfHP);
    RET_NC ;
    INC_hl;
    RET;


encourage:
    CALL(aRandom);
    CP_A(10 percent);
    RET_C ;
    DEC_hl;
    DEC_hl;
    RET;

}

void AI_Smart_Toxic(void){
    return AI_Smart_LeechSeed();
}

void AI_Smart_LeechSeed(void){
//  Discourage this move if player's HP is below 50%.

    CALL(aAICheckPlayerHalfHP);
    RET_C ;
    INC_hl;
    RET;

}

void AI_Smart_LightScreen(void){
    return AI_Smart_Reflect();
}

void AI_Smart_Reflect(void){
//  Over 90% chance to discourage this move unless enemy's HP is full.

    CALL(aAICheckEnemyMaxHP);
    RET_C ;
    CALL(aRandom);
    CP_A(8 percent);
    RET_C ;
    INC_hl;
    RET;

}

void AI_Smart_Ohko(void){
//  Dismiss this move if player's level is higher than enemy's level.
//  Else, discourage this move is player's HP is below 50%.

    LD_A_addr(wBattleMonLevel);
    LD_B_A;
    LD_A_addr(wEnemyMonLevel);
    CP_A_B;
    JP_C (mAIDiscourageMove);
    CALL(aAICheckPlayerHalfHP);
    RET_C ;
    INC_hl;
    RET;

}

void AI_Smart_TrapTarget(void){
//  Bind, Wrap, Fire Spin, Clamp

//  50% chance to discourage this move if the player is already trapped.
    LD_A_addr(wPlayerWrapCount);
    AND_A_A;
    IF_NZ goto discourage;

//  50% chance to greatly encourage this move if player is either
//  badly poisoned, in love, identified, stuck in Rollout, or has a Nightmare.
    LD_A_addr(wPlayerSubStatus5);
    BIT_A(SUBSTATUS_TOXIC);
    IF_NZ goto encourage;

    LD_A_addr(wPlayerSubStatus1);
    AND_A(1 << SUBSTATUS_IN_LOVE | 1 << SUBSTATUS_ROLLOUT | 1 << SUBSTATUS_IDENTIFIED | 1 << SUBSTATUS_NIGHTMARE);
    IF_NZ goto encourage;

//  Else, 50% chance to greatly encourage this move if it's the player's Pokemon first turn.
    LD_A_addr(wPlayerTurnsTaken);
    AND_A_A;
    IF_Z goto encourage;

//  50% chance to discourage this move otherwise.

discourage:
    CALL(aAI_50_50);
    RET_C ;
    INC_hl;
    RET;


encourage:
    CALL(aAICheckEnemyQuarterHP);
    RET_NC ;
    CALL(aAI_50_50);
    RET_C ;
    DEC_hl;
    DEC_hl;
    RET;

}

void AI_Smart_RazorWind(void){
    return AI_Smart_Unused2B();
}

void AI_Smart_Unused2B(void){
    LD_A_addr(wEnemySubStatus1);
    BIT_A(SUBSTATUS_PERISH);
    IF_Z goto no_perish_count;

    LD_A_addr(wEnemyPerishCount);
    CP_A(3);
    IF_C goto discourage;


no_perish_count:
    PUSH_HL;
    LD_HL(wPlayerUsedMoves);
    LD_C(NUM_MOVES);


checkmove:
    LD_A_hli;
    AND_A_A;
    IF_Z goto movesdone;

    CALL(aAIGetEnemyMove);

    LD_A_addr(wEnemyMoveStruct + MOVE_EFFECT);
    CP_A(EFFECT_PROTECT);
    IF_Z goto dismiss;
    DEC_C;
    IF_NZ goto checkmove;


movesdone:
    POP_HL;
    LD_A_addr(wEnemySubStatus3);
    BIT_A(SUBSTATUS_CONFUSED);
    IF_NZ goto maybe_discourage;

    CALL(aAICheckEnemyHalfHP);
    RET_C ;


maybe_discourage:
    CALL(aRandom);
    CP_A(79 percent - 1);
    RET_C ;


discourage:
    INC_hl;
    RET;


dismiss:
    POP_HL;
    LD_A_hl;
    ADD_A(6);
    LD_hl_A;
    RET;

}

void AI_Smart_Confuse(void){
//  90% chance to discourage this move if player's HP is between 25% and 50%.
    CALL(aAICheckPlayerHalfHP);
    RET_C ;
    CALL(aRandom);
    CP_A(10 percent);
    IF_C goto skipdiscourage;
    INC_hl;


skipdiscourage:
//  Discourage again if player's HP is below 25%.
    CALL(aAICheckPlayerQuarterHP);
    RET_C ;
    INC_hl;
    RET;

}

void AI_Smart_SpDefenseUp2(void){
//  Discourage this move if enemy's HP is lower than 50%.
    CALL(aAICheckEnemyHalfHP);
    IF_NC goto discourage;

//  Discourage this move if enemy's special defense level is higher than +3.
    LD_A_addr(wEnemySDefLevel);
    CP_A(BASE_STAT_LEVEL + 4);
    IF_NC goto discourage;

//  80% chance to greatly encourage this move if
//  enemy's Special Defense level is lower than +2, and the player is of a special type.
    CP_A(BASE_STAT_LEVEL + 2);
    RET_NC ;

    LD_A_addr(wBattleMonType1);
    CP_A(SPECIAL);
    IF_NC goto encourage;
    LD_A_addr(wBattleMonType2);
    CP_A(SPECIAL);
    RET_C ;


encourage:
    CALL(aAI_80_20);
    RET_C ;
    DEC_hl;
    DEC_hl;
    RET;


discourage:
    INC_hl;
    RET;

}

void AI_Smart_Fly(void){
//  Fly, Dig

//  Greatly encourage this move if the player is
//  flying or underground, and slower than the enemy.

    LD_A_addr(wPlayerSubStatus3);
    AND_A(1 << SUBSTATUS_FLYING | 1 << SUBSTATUS_UNDERGROUND);
    RET_Z ;

    CALL(aAICompareSpeed);
    RET_NC ;

    DEC_hl;
    DEC_hl;
    DEC_hl;
    RET;

}

void AI_Smart_SuperFang(void){
//  Discourage this move if player's HP is below 25%.

    CALL(aAICheckPlayerQuarterHP);
    RET_C ;
    INC_hl;
    RET;

}

void AI_Smart_Paralyze(void){
//  50% chance to discourage this move if player's HP is below 25%.
    CALL(aAICheckPlayerQuarterHP);
    IF_NC goto discourage;

//  80% chance to greatly encourage this move
//  if enemy is slower than player and its HP is above 25%.
    CALL(aAICompareSpeed);
    RET_C ;
    CALL(aAICheckEnemyQuarterHP);
    RET_NC ;
    CALL(aAI_80_20);
    RET_C ;
    DEC_hl;
    DEC_hl;
    RET;


discourage:
    CALL(aAI_50_50);
    RET_C ;
    INC_hl;
    RET;

}

void AI_Smart_SpeedDownHit(void){
//  Icy Wind

//  Almost 90% chance to greatly encourage this move if the following conditions all meet:
//  Enemy's HP is higher than 25%.
//  It's the first turn of player's Pokemon.
//  Player is faster than enemy.

    LD_A_addr(wEnemyMoveStruct + MOVE_ANIM);
    CP_A(ICY_WIND);
    RET_NZ ;
    CALL(aAICheckEnemyQuarterHP);
    RET_NC ;
    LD_A_addr(wPlayerTurnsTaken);
    AND_A_A;
    RET_NZ ;
    CALL(aAICompareSpeed);
    RET_C ;
    CALL(aRandom);
    CP_A(12 percent);
    RET_C ;
    DEC_hl;
    DEC_hl;
    RET;

}

void AI_Smart_Substitute(void){
//  Dismiss this move if enemy's HP is below 50%.

    CALL(aAICheckEnemyHalfHP);
    RET_C ;
    JP(mAIDiscourageMove);

}

void AI_Smart_HyperBeam(void){
    CALL(aAICheckEnemyHalfHP);
    IF_C goto discourage;

//  50% chance to encourage this move if enemy's HP is below 25%.
    CALL(aAICheckEnemyQuarterHP);
    RET_C ;
    CALL(aAI_50_50);
    RET_C ;
    DEC_hl;
    RET;


discourage:
//  If enemy's HP is above 50%, discourage this move at random
    CALL(aRandom);
    CP_A(16 percent);
    RET_C ;
    INC_hl;
    CALL(aAI_50_50);
    RET_C ;
    INC_hl;
    RET;

}

void AI_Smart_Rage(void){
    LD_A_addr(wEnemySubStatus4);
    BIT_A(SUBSTATUS_RAGE);
    IF_Z goto notbuilding;

//  If enemy's Rage is building, 50% chance to encourage this move.
    CALL(aAI_50_50);
    IF_C goto skipencourage;

    DEC_hl;

//  Encourage this move based on Rage's counter.

skipencourage:
    LD_A_addr(wEnemyRageCounter);
    CP_A(2);
    RET_C ;
    DEC_hl;
    LD_A_addr(wEnemyRageCounter);
    CP_A(3);
    RET_C ;
    DEC_hl;
    RET;


notbuilding:
//  If enemy's Rage is not building, discourage this move if enemy's HP is below 50%.
    CALL(aAICheckEnemyHalfHP);
    IF_NC goto discourage;

//  50% chance to encourage this move otherwise.
    CALL(aAI_80_20);
    RET_NC ;
    DEC_hl;
    RET;


discourage:
    INC_hl;
    RET;

}

void AI_Smart_Mimic(void){
//  Discourage this move if the player did not use any move last turn.
    LD_A_addr(wLastPlayerCounterMove);
    AND_A_A;
    IF_Z goto dismiss;

    CALL(aAICheckEnemyHalfHP);
    IF_NC goto discourage;

    PUSH_HL;
    LD_A_addr(wLastPlayerCounterMove);
    CALL(aAIGetEnemyMove);

    LD_A(1);
    LDH_addr_A(hBattleTurn);
    CALLFAR(aBattleCheckTypeMatchup);

    LD_A_addr(wTypeMatchup);
    CP_A(EFFECTIVE);
    POP_HL;
    IF_C goto discourage;
    IF_Z goto skip_encourage;

    CALL(aAI_50_50);
    IF_C goto skip_encourage;

    DEC_hl;


skip_encourage:
    LD_A_addr(wLastPlayerCounterMove);
    PUSH_HL;
    LD_HL(mUsefulMoves);
    LD_DE(1);
    CALL(aIsInArray);

    POP_HL;
    RET_NC ;
    CALL(aAI_50_50);
    RET_C ;
    DEC_hl;
    RET;


dismiss:
//  Dismiss this move if the enemy is faster than the player.
    CALL(aAICompareSpeed);
    JP_C (mAIDiscourageMove);


discourage:
    INC_hl;
    RET;

}

void AI_Smart_Counter(void){
    PUSH_HL;
    LD_HL(wPlayerUsedMoves);
    LD_C(NUM_MOVES);
    LD_B(0);


playermoveloop:
    LD_A_hli;
    AND_A_A;
    IF_Z goto skipmove;

    CALL(aAIGetEnemyMove);

    LD_A_addr(wEnemyMoveStruct + MOVE_POWER);
    AND_A_A;
    IF_Z goto skipmove;

    LD_A_addr(wEnemyMoveStruct + MOVE_TYPE);
    CP_A(SPECIAL);
    IF_NC goto skipmove;

    INC_B;


skipmove:
    DEC_C;
    IF_NZ goto playermoveloop;

    POP_HL;
    LD_A_B;
    AND_A_A;
    IF_Z goto discourage;

    CP_A(3);
    IF_NC goto encourage;

    LD_A_addr(wLastPlayerCounterMove);
    AND_A_A;
    IF_Z goto done;

    CALL(aAIGetEnemyMove);

    LD_A_addr(wEnemyMoveStruct + MOVE_POWER);
    AND_A_A;
    IF_Z goto done;

    LD_A_addr(wEnemyMoveStruct + MOVE_TYPE);
    CP_A(SPECIAL);
    IF_NC goto done;


encourage:
    CALL(aRandom);
    CP_A(39 percent + 1);
    IF_C goto done;

    DEC_hl;


done:
    RET;


discourage:
    INC_hl;
    RET;

}

void AI_Smart_Encore(void){
    CALL(aAICompareSpeed);
    IF_NC goto discourage;

    LD_A_addr(wLastPlayerMove);
    AND_A_A;
    JP_Z (mAIDiscourageMove);

    CALL(aAIGetEnemyMove);

    LD_A_addr(wEnemyMoveStruct + MOVE_POWER);
    AND_A_A;
    IF_Z goto weakmove;

    PUSH_HL;
    LD_A_addr(wEnemyMoveStruct + MOVE_TYPE);
    LD_HL(wEnemyMonType1);
    PREDEF(pCheckTypeMatchup);

    POP_HL;
    LD_A_addr(wTypeMatchup);
    CP_A(EFFECTIVE);
    IF_NC goto weakmove;

    AND_A_A;
    RET_NZ ;
    goto encourage;


weakmove:
    PUSH_HL;
    LD_A_addr(wLastPlayerCounterMove);
    LD_HL(mEncoreMoves);
    LD_DE(1);
    CALL(aIsInArray);
    POP_HL;
    IF_NC goto discourage;


encourage:
    CALL(aRandom);
    CP_A(28 percent - 1);
    RET_C ;
    DEC_hl;
    DEC_hl;
    RET;


discourage:
    INC_hl;
    INC_hl;
    INC_hl;
    RET;

// INCLUDE "data/battle/ai/encore_moves.asm"

    return AI_Smart_PainSplit();
}

void AI_Smart_PainSplit(void){
//  Discourage this move if [enemy's current HP * 2 > player's current HP].

    PUSH_HL;
    LD_HL(wEnemyMonHP);
    LD_B_hl;
    INC_HL;
    LD_C_hl;
    SLA_C;
    RL_B;
    LD_HL(wBattleMonHP + 1);
    LD_A_hld;
    CP_A_C;
    LD_A_hl;
    SBC_A_B;
    POP_HL;
    RET_NC ;
    INC_hl;
    RET;

}

void AI_Smart_Snore(void){
    return AI_Smart_SleepTalk();
}

void AI_Smart_SleepTalk(void){
//  Greatly encourage this move if enemy is fast asleep.
//  Greatly discourage this move otherwise.

    LD_A_addr(wEnemyMonStatus);
    AND_A(SLP);
    CP_A(1);
    IF_Z goto discourage;

    DEC_hl;
    DEC_hl;
    DEC_hl;
    RET;


discourage:
    INC_hl;
    INC_hl;
    INC_hl;
    RET;

}

void AI_Smart_DefrostOpponent(void){
//  Greatly encourage this move if enemy is frozen.
//  No move has EFFECT_DEFROST_OPPONENT, so this layer is unused.

    LD_A_addr(wEnemyMonStatus);
    AND_A(1 << FRZ);
    RET_Z ;
    DEC_hl;
    DEC_hl;
    DEC_hl;
    RET;

}

void AI_Smart_Spite(void){
    LD_A_addr(wLastPlayerCounterMove);
    AND_A_A;
    IF_NZ goto usedmove;

    CALL(aAICompareSpeed);
    JP_C (mAIDiscourageMove);

    CALL(aAI_50_50);
    RET_C ;
    INC_hl;
    RET;


usedmove:
    PUSH_HL;
    LD_B_A;
    LD_C(NUM_MOVES);
    LD_HL(wBattleMonMoves);
    LD_DE(wBattleMonPP);


moveloop:
    LD_A_hli;
    CP_A_B;
    IF_Z goto foundmove;

    INC_DE;
    DEC_C;
    IF_NZ goto moveloop;

    POP_HL;
    RET;


foundmove:
    POP_HL;
    LD_A_de;
    CP_A(6);
    IF_C goto encourage;
    CP_A(15);
    IF_NC goto discourage;

    CALL(aRandom);
    CP_A(39 percent + 1);
    RET_NC ;


discourage:
    INC_hl;
    RET;


encourage:
    CALL(aRandom);
    CP_A(39 percent + 1);
    RET_C ;
    DEC_hl;
    DEC_hl;
    RET;


dismiss:
//   //  unreferenced
    JP(mAIDiscourageMove);

}

void AI_Smart_DestinyBond(void){
    return AI_Smart_Reversal();
}

void AI_Smart_Reversal(void){
    return AI_Smart_SkullBash();
}

void AI_Smart_SkullBash(void){
//  Discourage this move if enemy's HP is above 25%.

    CALL(aAICheckEnemyQuarterHP);
    RET_NC ;
    INC_hl;
    RET;

}

void AI_Smart_HealBell(void){
//  Dismiss this move if none of the opponent's Pokemon is statused.
//  Encourage this move if the enemy is statused.
//  50% chance to greatly encourage this move if the enemy is fast asleep or frozen.

    PUSH_HL;
    LD_A_addr(wOTPartyCount);
    LD_B_A;
    LD_C(0);
    LD_HL(wOTPartyMon1HP);
    LD_DE(PARTYMON_STRUCT_LENGTH);


loop:
    PUSH_HL;
    LD_A_hli;
    OR_A_hl;
    IF_Z goto next;

// status
    DEC_HL;
    DEC_HL;
    DEC_HL;
    LD_A_hl;
    OR_A_C;
    LD_C_A;


next:
    POP_HL;
    ADD_HL_DE;
    DEC_B;
    IF_NZ goto loop;

    POP_HL;
    LD_A_C;
    AND_A_A;
    IF_Z goto no_status;

    LD_A_addr(wEnemyMonStatus);
    AND_A_A;
    IF_Z goto ok;
    DEC_hl;

ok:
    AND_A(1 << FRZ | SLP);
    RET_Z ;
    CALL(aAI_50_50);
    RET_C ;
    DEC_hl;
    DEC_hl;
    RET;


no_status:
    LD_A_addr(wEnemyMonStatus);
    AND_A_A;
    RET_NZ ;
    JP(mAIDiscourageMove);


}

void AI_Smart_PriorityHit(void){
    CALL(aAICompareSpeed);
    RET_C ;

//  Dismiss this move if the player is flying or underground.
    LD_A_addr(wPlayerSubStatus3);
    AND_A(1 << SUBSTATUS_FLYING | 1 << SUBSTATUS_UNDERGROUND);
    JP_NZ (mAIDiscourageMove);

//  Greatly encourage this move if it will KO the player.
    LD_A(1);
    LDH_addr_A(hBattleTurn);
    PUSH_HL;
    CALLFAR(aEnemyAttackDamage);
    CALLFAR(aBattleCommand_DamageCalc);
    CALLFAR(aBattleCommand_Stab);
    POP_HL;
    LD_A_addr(wCurDamage + 1);
    LD_C_A;
    LD_A_addr(wCurDamage);
    LD_B_A;
    LD_A_addr(wBattleMonHP + 1);
    CP_A_C;
    LD_A_addr(wBattleMonHP);
    SBC_A_B;
    RET_NC ;
    DEC_hl;
    DEC_hl;
    DEC_hl;
    RET;

}

void AI_Smart_Thief(void){
//  Don't use Thief unless it's the only move available.

    LD_A_hl;
    ADD_A(0x1e);
    LD_hl_A;
    RET;

}

void AI_Smart_Conversion2(void){
    LD_A_addr(wLastPlayerMove);
    AND_A_A;
    IF_NZ goto discourage;  // should be jr z

    PUSH_HL;
    DEC_A;
    LD_HL(mMoves + MOVE_TYPE);
    LD_BC(MOVE_LENGTH);
    CALL(aAddNTimes);

    LD_A(BANK(aMoves));
    CALL(aGetFarByte);
    LD_addr_A(wPlayerMoveStruct + MOVE_TYPE);

    XOR_A_A;
    LDH_addr_A(hBattleTurn);

    CALLFAR(aBattleCheckTypeMatchup);

    LD_A_addr(wTypeMatchup);
    CP_A(EFFECTIVE);
    POP_HL;
    IF_C goto discourage;
    RET_Z ;

    CALL(aAI_50_50);
    RET_C ;

    DEC_hl;
    RET;


discourage:
    CALL(aRandom);
    CP_A(10 percent);
    RET_C ;
    INC_hl;
    RET;

}

void AI_Smart_Disable(void){
    CALL(aAICompareSpeed);
    IF_NC goto discourage;

    PUSH_HL;
    LD_A_addr(wLastPlayerCounterMove);
    LD_HL(mUsefulMoves);
    LD_DE(1);
    CALL(aIsInArray);

    POP_HL;
    IF_NC goto notencourage;

    CALL(aRandom);
    CP_A(39 percent + 1);
    RET_C ;
    DEC_hl;
    RET;


notencourage:
    LD_A_addr(wEnemyMoveStruct + MOVE_POWER);
    AND_A_A;
    RET_NZ ;


discourage:
    CALL(aRandom);
    CP_A(8 percent);
    RET_C ;
    INC_hl;
    RET;

}

void AI_Smart_MeanLook(void){
    CALL(aAICheckEnemyHalfHP);
    IF_NC goto discourage;

    PUSH_HL;
    CALL(aAICheckLastPlayerMon);
    POP_HL;
    JP_Z (mAIDiscourageMove);

//  80% chance to greatly encourage this move if the enemy is badly poisoned (buggy).
//  Should check wPlayerSubStatus5 instead.
    LD_A_addr(wEnemySubStatus5);
    BIT_A(SUBSTATUS_TOXIC);
    IF_NZ goto encourage;

//  80% chance to greatly encourage this move if the player is either
//  in love, identified, stuck in Rollout, or has a Nightmare.
    LD_A_addr(wPlayerSubStatus1);
    AND_A(1 << SUBSTATUS_IN_LOVE | 1 << SUBSTATUS_ROLLOUT | 1 << SUBSTATUS_IDENTIFIED | 1 << SUBSTATUS_NIGHTMARE);
    IF_NZ goto encourage;

//  Otherwise, discourage this move unless the player only has not very effective moves against the enemy.
    PUSH_HL;
    CALLFAR(aCheckPlayerMoveTypeMatchups);
    LD_A_addr(wEnemyAISwitchScore);
    CP_A(BASE_AI_SWITCH_SCORE + 1);  // not very effective
    POP_HL;
    RET_NC ;


discourage:
    INC_hl;
    RET;


encourage:
    CALL(aAI_80_20);
    RET_C ;
    DEC_hl;
    DEC_hl;
    DEC_hl;
    RET;

}

void AICheckLastPlayerMon(void){
    LD_A_addr(wPartyCount);
    LD_B_A;
    LD_C(0);
    LD_HL(wPartyMon1HP);
    LD_DE(PARTYMON_STRUCT_LENGTH);


loop:
    LD_A_addr(wCurBattleMon);
    CP_A_C;
    IF_Z goto skip;

    LD_A_hli;
    OR_A_hl;
    RET_NZ ;
    DEC_HL;


skip:
    ADD_HL_DE;
    INC_C;
    DEC_B;
    IF_NZ goto loop;

    RET;

}

void AI_Smart_Nightmare(void){
//  50% chance to encourage this move.
//  The AI_Basic layer will make sure that
//  Dream Eater is only used against sleeping targets.

    CALL(aAI_50_50);
    RET_C ;
    DEC_hl;
    RET;

}

void AI_Smart_FlameWheel(void){
//  Use this move if the enemy is frozen.

    LD_A_addr(wEnemyMonStatus);
    BIT_A(FRZ);
    RET_Z ;
    for(int rept = 0; rept < 5; rept++){
    DEC_hl;
    }
    RET;

}

void AI_Smart_Curse(void){
    LD_A_addr(wEnemyMonType1);
    CP_A(GHOST);
    IF_Z goto ghost_curse;
    LD_A_addr(wEnemyMonType2);
    CP_A(GHOST);
    IF_Z goto ghost_curse;

    CALL(aAICheckEnemyHalfHP);
    IF_NC goto encourage;

    LD_A_addr(wEnemyAtkLevel);
    CP_A(BASE_STAT_LEVEL + 4);
    IF_NC goto encourage;
    CP_A(BASE_STAT_LEVEL + 2);
    RET_NC ;

    LD_A_addr(wBattleMonType1);
    CP_A(GHOST);
    IF_Z goto greatly_encourage;
    CP_A(SPECIAL);
    RET_NC ;
    LD_A_addr(wBattleMonType2);
    CP_A(SPECIAL);
    RET_NC ;
    CALL(aAI_80_20);
    RET_C ;
    DEC_hl;
    DEC_hl;
    RET;


approve:
    INC_hl;
    INC_hl;

greatly_encourage:
    INC_hl;

encourage:
    INC_hl;
    RET;


ghost_curse:
    LD_A_addr(wPlayerSubStatus1);
    BIT_A(SUBSTATUS_CURSE);
    JP_NZ (mAIDiscourageMove);

    PUSH_HL;
    FARCALL(aFindAliveEnemyMons);
    POP_HL;
    IF_NC goto notlastmon;

    PUSH_HL;
    CALL(aAICheckLastPlayerMon);
    POP_HL;
    IF_NZ goto approve;

    goto ghost_continue;


notlastmon:
    PUSH_HL;
    CALL(aAICheckLastPlayerMon);
    POP_HL;
    IF_Z goto maybe_greatly_encourage;


ghost_continue:
    CALL(aAICheckEnemyQuarterHP);
    JP_NC (mAI_Smart_Curse_approve);

    CALL(aAICheckEnemyHalfHP);
    IF_NC goto greatly_encourage;

    CALL(aAICheckEnemyMaxHP);
    RET_NC ;

    LD_A_addr(wPlayerTurnsTaken);
    AND_A_A;
    RET_NZ ;


maybe_greatly_encourage:
    CALL(aAI_50_50);
    RET_C ;

    DEC_hl;
    DEC_hl;
    RET;

}

void AI_Smart_Protect(void){
//  Greatly discourage this move if the enemy already used Protect.
    LD_A_addr(wEnemyProtectCount);
    AND_A_A;
    IF_NZ goto greatly_discourage;

//  Discourage this move if the player is locked on.
    LD_A_addr(wPlayerSubStatus5);
    BIT_A(SUBSTATUS_LOCK_ON);
    IF_NZ goto discourage;

//  Encourage this move if the player's Fury Cutter is boosted enough.
    LD_A_addr(wPlayerFuryCutterCount);
    CP_A(3);
    IF_NC goto encourage;

//  Encourage this move if the player has charged a two-turn move.
    LD_A_addr(wPlayerSubStatus3);
    BIT_A(SUBSTATUS_CHARGED);
    IF_NZ goto encourage;

//  Encourage this move if the player is affected by Toxic, Leech Seed, or Curse.
    LD_A_addr(wPlayerSubStatus5);
    BIT_A(SUBSTATUS_TOXIC);
    IF_NZ goto encourage;
    LD_A_addr(wPlayerSubStatus4);
    BIT_A(SUBSTATUS_LEECH_SEED);
    IF_NZ goto encourage;
    LD_A_addr(wPlayerSubStatus1);
    BIT_A(SUBSTATUS_CURSE);
    IF_NZ goto encourage;

//  Discourage this move if the player's Rollout count is not boosted enough.
    BIT_A(SUBSTATUS_ROLLOUT);
    IF_Z goto discourage;
    LD_A_addr(wPlayerRolloutCount);
    CP_A(3);
    IF_C goto discourage;

//  80% chance to encourage this move otherwise.

encourage:
    CALL(aAI_80_20);
    RET_C ;

    DEC_hl;
    RET;


greatly_discourage:
    INC_hl;


discourage:
    CALL(aRandom);
    CP_A(8 percent);
    RET_C ;

    INC_hl;
    INC_hl;
    RET;

}

void AI_Smart_Foresight(void){
//  60% chance to encourage this move if the enemy's accuracy is sharply lowered.
    LD_A_addr(wEnemyAccLevel);
    CP_A(BASE_STAT_LEVEL - 2);
    IF_C goto encourage;

//  60% chance to encourage this move if the player's evasion is sharply raised.
    LD_A_addr(wPlayerEvaLevel);
    CP_A(BASE_STAT_LEVEL + 3);
    IF_NC goto encourage;

//  60% chance to encourage this move if the player is a Ghost type.
    LD_A_addr(wBattleMonType1);
    CP_A(GHOST);
    IF_Z goto encourage;
    LD_A_addr(wBattleMonType2);
    CP_A(GHOST);
    IF_Z goto encourage;

//  92% chance to discourage this move otherwise.
    CALL(aRandom);
    CP_A(8 percent);
    RET_C ;

    INC_hl;
    RET;


encourage:
    CALL(aRandom);
    CP_A(39 percent + 1);
    RET_C ;

    DEC_hl;
    DEC_hl;
    RET;

}

void AI_Smart_PerishSong(void){
    PUSH_HL;
    CALLFAR(aFindAliveEnemyMons);
    POP_HL;
    IF_C goto no;

    LD_A_addr(wPlayerSubStatus5);
    BIT_A(SUBSTATUS_CANT_RUN);
    IF_NZ goto yes;

    PUSH_HL;
    CALLFAR(aCheckPlayerMoveTypeMatchups);
    LD_A_addr(wEnemyAISwitchScore);
    CP_A(BASE_AI_SWITCH_SCORE);
    POP_HL;
    RET_C ;

    CALL(aAI_50_50);
    RET_C ;

    INC_hl;
    RET;


yes:
    CALL(aAI_50_50);
    RET_C ;

    DEC_hl;
    RET;


no:
    LD_A_hl;
    ADD_A(5);
    LD_hl_A;
    RET;

}

void AI_Smart_Sandstorm(void){
//  Greatly discourage this move if the player is immune to Sandstorm damage.
    LD_A_addr(wBattleMonType1);
    PUSH_HL;
    LD_HL(mAI_Smart_Sandstorm_SandstormImmuneTypes);
    LD_DE(1);
    CALL(aIsInArray);
    POP_HL;
    IF_C goto greatly_discourage;

    LD_A_addr(wBattleMonType2);
    PUSH_HL;
    LD_HL(mAI_Smart_Sandstorm_SandstormImmuneTypes);
    LD_DE(1);
    CALL(aIsInArray);
    POP_HL;
    IF_C goto greatly_discourage;

//  Discourage this move if player's HP is below 50%.
    CALL(aAICheckPlayerHalfHP);
    IF_NC goto discourage;

//  50% chance to encourage this move otherwise.
    CALL(aAI_50_50);
    RET_C ;

    DEC_hl;
    RET;


greatly_discourage:
    INC_hl;

discourage:
    INC_hl;
    RET;


SandstormImmuneTypes:
    //db ['ROCK'];
    //db ['GROUND'];
    //db ['STEEL'];
    //db ['-1'];  // end

    return AI_Smart_Endure();
}

void AI_Smart_Endure(void){
//  Greatly discourage this move if the enemy already used Protect.
    LD_A_addr(wEnemyProtectCount);
    AND_A_A;
    IF_NZ goto greatly_discourage;

//  Greatly discourage this move if the enemy's HP is full.
    CALL(aAICheckEnemyMaxHP);
    IF_C goto greatly_discourage;

//  Discourage this move if the enemy's HP is at least 25%.
    CALL(aAICheckEnemyQuarterHP);
    IF_C goto discourage;

//  If the enemy has Reversal...
    LD_B(EFFECT_REVERSAL);
    CALL(aAIHasMoveEffect);
    IF_NC goto no_reversal;

//  ...80% chance to greatly encourage this move.
    CALL(aAI_80_20);
    RET_C ;

    DEC_hl;
    DEC_hl;
    DEC_hl;
    RET;


no_reversal:
//  If the enemy is not locked on, do nothing.
    LD_A_addr(wEnemySubStatus5);
    BIT_A(SUBSTATUS_LOCK_ON);
    RET_Z ;

//  50% chance to greatly encourage this move.
    CALL(aAI_50_50);
    RET_C ;

    DEC_hl;
    DEC_hl;
    RET;


greatly_discourage:
    INC_hl;

discourage:
    INC_hl;
    RET;

}

void AI_Smart_FuryCutter(void){
//  Encourage this move based on Fury Cutter's count.

    LD_A_addr(wEnemyFuryCutterCount);
    AND_A_A;
    JR_Z (mAI_Smart_Rollout);
    DEC_hl;

    CP_A(2);
    JR_C (mAI_Smart_Rollout);
    DEC_hl;
    DEC_hl;

    CP_A(3);
    JR_C (mAI_Smart_Rollout);
    DEC_hl;
    DEC_hl;
    DEC_hl;

// fallthrough

    return AI_Smart_Rollout();
}

void AI_Smart_Rollout(void){
//  Rollout, Fury Cutter

//  80% chance to discourage this move if the enemy is in love, confused, or paralyzed.
    LD_A_addr(wEnemySubStatus1);
    BIT_A(SUBSTATUS_IN_LOVE);
    IF_NZ goto maybe_discourage;

    LD_A_addr(wEnemySubStatus3);
    BIT_A(SUBSTATUS_CONFUSED);
    IF_NZ goto maybe_discourage;

    LD_A_addr(wEnemyMonStatus);
    BIT_A(PAR);
    IF_NZ goto maybe_discourage;

//  80% chance to discourage this move if the enemy's HP is below 25%,
//  or if accuracy or evasion modifiers favour the player.
    CALL(aAICheckEnemyQuarterHP);
    IF_NC goto maybe_discourage;

    LD_A_addr(wEnemyAccLevel);
    CP_A(BASE_STAT_LEVEL);
    IF_C goto maybe_discourage;
    LD_A_addr(wPlayerEvaLevel);
    CP_A(BASE_STAT_LEVEL + 1);
    IF_NC goto maybe_discourage;

//  80% chance to greatly encourage this move otherwise.
    CALL(aRandom);
    CP_A(79 percent - 1);
    RET_NC ;
    DEC_hl;
    DEC_hl;
    RET;


maybe_discourage:
    CALL(aAI_80_20);
    RET_C ;
    INC_hl;
    RET;

}

void AI_Smart_Swagger(void){
    return AI_Smart_Attract();
}

void AI_Smart_Attract(void){
//  80% chance to encourage this move during the first turn of player's Pokemon.
//  80% chance to discourage this move otherwise.

    LD_A_addr(wPlayerTurnsTaken);
    AND_A_A;
    IF_Z goto first_turn;

    CALL(aAI_80_20);
    RET_C ;
    INC_hl;
    RET;


first_turn:
    CALL(aRandom);
    CP_A(79 percent - 1);
    RET_NC ;
    DEC_hl;
    RET;

}

void AI_Smart_Safeguard(void){
//  80% chance to discourage this move if player's HP is below 50%.

    CALL(aAICheckPlayerHalfHP);
    RET_C ;
    CALL(aAI_80_20);
    RET_C ;
    INC_hl;
    RET;

}

void AI_Smart_Magnitude(void){
    return AI_Smart_Earthquake();
}

void AI_Smart_Earthquake(void){
//  Greatly encourage this move if the player is underground and the enemy is faster.
    LD_A_addr(wLastPlayerCounterMove);
    CP_A(DIG);
    RET_NZ ;

    LD_A_addr(wPlayerSubStatus3);
    BIT_A(SUBSTATUS_UNDERGROUND);
    IF_Z goto could_dig;

    CALL(aAICompareSpeed);
    RET_NC ;
    DEC_hl;
    DEC_hl;
    RET;


could_dig:
// Try to predict if the player will use Dig this turn.

// 50% chance to encourage this move if the enemy is slower than the player.
    CALL(aAICompareSpeed);
    RET_C ;

    CALL(aAI_50_50);
    RET_C ;

    DEC_hl;
    RET;

}

void AI_Smart_BatonPass(void){
//  Discourage this move if the player hasn't shown super-effective moves against the enemy.
//  Consider player's type(s) if its moves are unknown.

    PUSH_HL;
    CALLFAR(aCheckPlayerMoveTypeMatchups);
    LD_A_addr(wEnemyAISwitchScore);
    CP_A(BASE_AI_SWITCH_SCORE);
    POP_HL;
    RET_C ;
    INC_hl;
    RET;

}

void AI_Smart_Pursuit(void){
//  50% chance to greatly encourage this move if player's HP is below 25%.
//  80% chance to discourage this move otherwise.

    CALL(aAICheckPlayerQuarterHP);
    IF_NC goto encourage;
    CALL(aAI_80_20);
    RET_C ;
    INC_hl;
    RET;


encourage:
    CALL(aAI_50_50);
    RET_C ;
    DEC_hl;
    DEC_hl;
    RET;

}

void AI_Smart_RapidSpin(void){
//  80% chance to greatly encourage this move if the enemy is
//  trapped (Bind effect), seeded, or scattered with spikes.

    LD_A_addr(wEnemyWrapCount);
    AND_A_A;
    IF_NZ goto encourage;

    LD_A_addr(wEnemySubStatus4);
    BIT_A(SUBSTATUS_LEECH_SEED);
    IF_NZ goto encourage;

    LD_A_addr(wEnemyScreens);
    BIT_A(SCREENS_SPIKES);
    RET_Z ;


encourage:
    CALL(aAI_80_20);
    RET_C ;

    DEC_hl;
    DEC_hl;
    RET;

}

void AI_Smart_HiddenPower(void){
    PUSH_HL;
    LD_A(1);
    LDH_addr_A(hBattleTurn);

//  Calculate Hidden Power's type and base power based on enemy's DVs.
    CALLFAR(aHiddenPowerDamage);
    CALLFAR(aBattleCheckTypeMatchup);
    POP_HL;

//  Discourage Hidden Power if not very effective.
    LD_A_addr(wTypeMatchup);
    CP_A(EFFECTIVE);
    IF_C goto bad;

//  Discourage Hidden Power if its base power    is lower than 50.
    LD_A_D;
    CP_A(50);
    IF_C goto bad;

//  Encourage Hidden Power if super-effective.
    LD_A_addr(wTypeMatchup);
    CP_A(EFFECTIVE + 1);
    IF_NC goto good;

//  Encourage Hidden Power if its base power is 70.
    LD_A_D;
    CP_A(70);
    RET_C ;


good:
    DEC_hl;
    RET;


bad:
    INC_hl;
    RET;

}

void AI_Smart_RainDance(void){
//  Greatly discourage this move if it would favour the player type-wise.
//  Particularly, if the player is a Water-type.
    LD_A_addr(wBattleMonType1);
    CP_A(WATER);
    JR_Z (mAIBadWeatherType);
    CP_A(FIRE);
    JR_Z (mAIGoodWeatherType);

    LD_A_addr(wBattleMonType2);
    CP_A(WATER);
    JR_Z (mAIBadWeatherType);
    CP_A(FIRE);
    JR_Z (mAIGoodWeatherType);

    PUSH_HL;
    LD_HL(mRainDanceMoves);
    JR(mAI_Smart_WeatherMove);

// INCLUDE "data/battle/ai/rain_dance_moves.asm"

    return AI_Smart_SunnyDay();
}

void AI_Smart_SunnyDay(void){
//  Greatly discourage this move if it would favour the player type-wise.
//  Particularly, if the player is a Fire-type.
    LD_A_addr(wBattleMonType1);
    CP_A(FIRE);
    JR_Z (mAIBadWeatherType);
    CP_A(WATER);
    JR_Z (mAIGoodWeatherType);

    LD_A_addr(wBattleMonType2);
    CP_A(FIRE);
    JR_Z (mAIBadWeatherType);
    CP_A(WATER);
    JR_Z (mAIGoodWeatherType);

    PUSH_HL;
    LD_HL(mSunnyDayMoves);

// fallthrough

    return AI_Smart_WeatherMove();
}

void AI_Smart_WeatherMove(void){
//  Rain Dance, Sunny Day

//  Greatly discourage this move if the enemy doesn't have
//  one of the useful Rain Dance or Sunny Day moves.
    CALL(aAIHasMoveInArray);
    POP_HL;
    JR_NC (mAIBadWeatherType);

//  Greatly discourage this move if player's HP is below 50%.
    CALL(aAICheckPlayerHalfHP);
    JR_NC (mAIBadWeatherType);

//  50% chance to encourage this move otherwise.
    CALL(aAI_50_50);
    RET_C ;

    DEC_hl;
    RET;

}

void AIBadWeatherType(void){
    INC_hl;
    INC_hl;
    INC_hl;
    RET;

}

void AIGoodWeatherType(void){
//  Rain Dance, Sunny Day

//  Greatly encourage this move if it would disfavour the player type-wise and player's HP is above 50%...
    CALL(aAICheckPlayerHalfHP);
    RET_NC ;

//  ...as long as one of the following conditions meet:
//  It's the first turn of the player's Pokemon.
    LD_A_addr(wPlayerTurnsTaken);
    AND_A_A;
    IF_Z goto good;

//  Or it's the first turn of the enemy's Pokemon.
    LD_A_addr(wEnemyTurnsTaken);
    AND_A_A;
    RET_NZ ;


good:
    DEC_hl;
    DEC_hl;
    RET;

// INCLUDE "data/battle/ai/sunny_day_moves.asm"

    return AI_Smart_BellyDrum();
}

void AI_Smart_BellyDrum(void){
//  Dismiss this move if enemy's attack is higher than +2 or if enemy's HP is below 50%.
//  Else, discourage this move if enemy's HP is not full.

    LD_A_addr(wEnemyAtkLevel);
    CP_A(BASE_STAT_LEVEL + 3);
    IF_NC goto discourage;

    CALL(aAICheckEnemyMaxHP);
    RET_C ;

    INC_hl;

    CALL(aAICheckEnemyHalfHP);
    RET_C ;


discourage:
    LD_A_hl;
    ADD_A(5);
    LD_hl_A;
    RET;

}

void AI_Smart_PsychUp(void){
    PUSH_HL;
    LD_HL(wEnemyAtkLevel);
    LD_B(NUM_LEVEL_STATS);
    LD_C(100);

//  Calculate the sum of all enemy's stat level modifiers. Add 100 first to prevent underflow.
//  Put the result in c. c will range between 58 and 142.

enemy_loop:
    LD_A_hli;
    SUB_A(BASE_STAT_LEVEL);
    ADD_A_C;
    LD_C_A;
    DEC_B;
    IF_NZ goto enemy_loop;

//  Calculate the sum of all player's stat level modifiers. Add 100 first to prevent underflow.
//  Put the result in d. d will range between 58 and 142.
    LD_HL(wPlayerAtkLevel);
    LD_B(NUM_LEVEL_STATS);
    LD_D(100);


player_loop:
    LD_A_hli;
    SUB_A(BASE_STAT_LEVEL);
    ADD_A_D;
    LD_D_A;
    DEC_B;
    IF_NZ goto player_loop;

//  Greatly discourage this move if enemy's stat levels are higher than player's (if c>=d).
    LD_A_C;
    SUB_A_D;
    POP_HL;
    IF_NC goto discourage;

//  Else, 80% chance to encourage this move unless player's accuracy level is lower than -1...
    LD_A_addr(wPlayerAccLevel);
    CP_A(BASE_STAT_LEVEL - 1);
    RET_C ;

//  ...or enemy's evasion level is higher than +0.
    LD_A_addr(wEnemyEvaLevel);
    CP_A(BASE_STAT_LEVEL + 1);
    RET_NC ;

    CALL(aAI_80_20);
    RET_C ;

    DEC_hl;
    RET;


discourage:
    INC_hl;
    INC_hl;
    RET;

}

void AI_Smart_MirrorCoat(void){
    PUSH_HL;
    LD_HL(wPlayerUsedMoves);
    LD_C(NUM_MOVES);
    LD_B(0);


playermoveloop:
    LD_A_hli;
    AND_A_A;
    IF_Z goto skipmove;

    CALL(aAIGetEnemyMove);

    LD_A_addr(wEnemyMoveStruct + MOVE_POWER);
    AND_A_A;
    IF_Z goto skipmove;

    LD_A_addr(wEnemyMoveStruct + MOVE_TYPE);
    CP_A(SPECIAL);
    IF_C goto skipmove;

    INC_B;


skipmove:
    DEC_C;
    IF_NZ goto playermoveloop;

    POP_HL;
    LD_A_B;
    AND_A_A;
    IF_Z goto discourage;

    CP_A(3);
    IF_NC goto encourage;

    LD_A_addr(wLastPlayerCounterMove);
    AND_A_A;
    IF_Z goto done;

    CALL(aAIGetEnemyMove);

    LD_A_addr(wEnemyMoveStruct + MOVE_POWER);
    AND_A_A;
    IF_Z goto done;

    LD_A_addr(wEnemyMoveStruct + MOVE_TYPE);
    CP_A(SPECIAL);
    IF_C goto done;


encourage:
    CALL(aRandom);
    CP_A(39 percent + 1);
    IF_C goto done;
    DEC_hl;


done:
    RET;


discourage:
    INC_hl;
    RET;

}

void AI_Smart_Twister(void){
    return AI_Smart_Gust();
}

void AI_Smart_Gust(void){
//  Greatly encourage this move if the player is flying and the enemy is faster.
    LD_A_addr(wLastPlayerCounterMove);
    CP_A(FLY);
    RET_NZ ;

    LD_A_addr(wPlayerSubStatus3);
    BIT_A(SUBSTATUS_FLYING);
    IF_Z goto couldFly;

    CALL(aAICompareSpeed);
    RET_NC ;

    DEC_hl;
    DEC_hl;
    RET;

//  Try to predict if the player will use Fly this turn.

couldFly:

//  50% chance to encourage this move if the enemy is slower than the player.
    CALL(aAICompareSpeed);
    RET_C ;
    CALL(aAI_50_50);
    RET_C ;
    DEC_hl;
    RET;

}

void AI_Smart_FutureSight(void){
//  Greatly encourage this move if the player is
//  flying or underground, and slower than the enemy.

    CALL(aAICompareSpeed);
    RET_NC ;

    LD_A_addr(wPlayerSubStatus3);
    AND_A(1 << SUBSTATUS_FLYING | 1 << SUBSTATUS_UNDERGROUND);
    RET_Z ;

    DEC_hl;
    DEC_hl;
    RET;

}

void AI_Smart_Stomp(void){
//  80% chance to encourage this move if the player has used Minimize.

    LD_A_addr(wPlayerMinimized);
    AND_A_A;
    RET_Z ;

    CALL(aAI_80_20);
    RET_C ;

    DEC_hl;
    RET;

}

void AI_Smart_Solarbeam(void){
//  80% chance to encourage this move when it's sunny.
//  90% chance to discourage this move when it's raining.

    LD_A_addr(wBattleWeather);
    CP_A(WEATHER_SUN);
    IF_Z goto encourage;

    CP_A(WEATHER_RAIN);
    RET_NZ ;

    CALL(aRandom);
    CP_A(10 percent);
    RET_C ;

    INC_hl;
    INC_hl;
    RET;


encourage:
    CALL(aAI_80_20);
    RET_C ;

    DEC_hl;
    DEC_hl;
    RET;

}

void AI_Smart_Thunder(void){
//  90% chance to discourage this move when it's sunny.

    LD_A_addr(wBattleWeather);
    CP_A(WEATHER_SUN);
    RET_NZ ;

    CALL(aRandom);
    CP_A(10 percent);
    RET_C ;

    INC_hl;
    RET;

}

void AICompareSpeed(void){
//  Return carry if enemy is faster than player.

    PUSH_BC;
    LD_A_addr(wEnemyMonSpeed + 1);
    LD_B_A;
    LD_A_addr(wBattleMonSpeed + 1);
    CP_A_B;
    LD_A_addr(wEnemyMonSpeed);
    LD_B_A;
    LD_A_addr(wBattleMonSpeed);
    SBC_A_B;
    POP_BC;
    RET;

}

void AICheckPlayerMaxHP(void){
    PUSH_HL;
    PUSH_DE;
    PUSH_BC;
    LD_DE(wBattleMonHP);
    LD_HL(wBattleMonMaxHP);
    JR(mAICheckMaxHP);

}

void AICheckEnemyMaxHP(void){
    PUSH_HL;
    PUSH_DE;
    PUSH_BC;
    LD_DE(wEnemyMonHP);
    LD_HL(wEnemyMonMaxHP);
// fallthrough

    return AICheckMaxHP();
}

void AICheckMaxHP(void){
//  Return carry if hp at de matches max hp at hl.

    LD_A_de;
    INC_DE;
    CP_A_hl;
    IF_NZ goto not_max;

    INC_HL;
    LD_A_de;
    CP_A_hl;
    IF_NZ goto not_max;

    POP_BC;
    POP_DE;
    POP_HL;
    SCF;
    RET;


not_max:
    POP_BC;
    POP_DE;
    POP_HL;
    AND_A_A;
    RET;

}

void AICheckPlayerHalfHP(void){
    PUSH_HL;
    LD_HL(wBattleMonHP);
    LD_B_hl;
    INC_HL;
    LD_C_hl;
    SLA_C;
    RL_B;
    INC_HL;
    INC_HL;
    LD_A_hld;
    CP_A_C;
    LD_A_hl;
    SBC_A_B;
    POP_HL;
    RET;

}

void AICheckEnemyHalfHP(void){
    PUSH_HL;
    PUSH_DE;
    PUSH_BC;
    LD_HL(wEnemyMonHP);
    LD_B_hl;
    INC_HL;
    LD_C_hl;
    SLA_C;
    RL_B;
    INC_HL;
    INC_HL;
    LD_A_hld;
    CP_A_C;
    LD_A_hl;
    SBC_A_B;
    POP_BC;
    POP_DE;
    POP_HL;
    RET;

}

void AICheckEnemyQuarterHP(void){
    PUSH_HL;
    PUSH_DE;
    PUSH_BC;
    LD_HL(wEnemyMonHP);
    LD_B_hl;
    INC_HL;
    LD_C_hl;
    SLA_C;
    RL_B;
    SLA_C;
    RL_B;
    INC_HL;
    INC_HL;
    LD_A_hld;
    CP_A_C;
    LD_A_hl;
    SBC_A_B;
    POP_BC;
    POP_DE;
    POP_HL;
    RET;

}

void AICheckPlayerQuarterHP(void){
    PUSH_HL;
    LD_HL(wBattleMonHP);
    LD_B_hl;
    INC_HL;
    LD_C_hl;
    SLA_C;
    RL_B;
    SLA_C;
    RL_B;
    INC_HL;
    INC_HL;
    LD_A_hld;
    CP_A_C;
    LD_A_hl;
    SBC_A_B;
    POP_HL;
    RET;

}

void AIHasMoveEffect(void){
//  Return carry if the enemy has move b.

    PUSH_HL;
    LD_HL(wEnemyMonMoves);
    LD_C(NUM_MOVES);


checkmove:
    LD_A_hli;
    AND_A_A;
    IF_Z goto no;

    CALL(aAIGetEnemyMove);

    LD_A_addr(wEnemyMoveStruct + MOVE_EFFECT);
    CP_A_B;
    IF_Z goto yes;

    DEC_C;
    IF_NZ goto checkmove;


no:
    POP_HL;
    AND_A_A;
    RET;


yes:
    POP_HL;
    SCF;
    RET;

}

void AIHasMoveInArray(void){
//  Return carry if the enemy has a move in array hl.

    PUSH_HL;
    PUSH_DE;
    PUSH_BC;


next:
    LD_A_hli;
    CP_A(-1);
    IF_Z goto done;

    LD_B_A;
    LD_C(NUM_MOVES + 1);
    LD_DE(wEnemyMonMoves);


check:
    DEC_C;
    IF_Z goto next;

    LD_A_de;
    INC_DE;
    CP_A_B;
    IF_NZ goto check;

    SCF;


done:
    POP_BC;
    POP_DE;
    POP_HL;
    RET;

// INCLUDE "data/battle/ai/useful_moves.asm"

    return AI_Opportunist();
}

void AI_Opportunist(void){
//  Discourage stall moves when the enemy's HP is low.

//  Do nothing if enemy's HP is above 50%.
    CALL(aAICheckEnemyHalfHP);
    RET_C ;

//  Discourage stall moves if enemy's HP is below 25%.
    CALL(aAICheckEnemyQuarterHP);
    IF_NC goto lowhp;

//  50% chance to discourage stall moves if enemy's HP is between 25% and 50%.
    CALL(aAI_50_50);
    RET_C ;


lowhp:
    LD_HL(wEnemyAIMoveScores - 1);
    LD_DE(wEnemyMonMoves);
    LD_C(NUM_MOVES + 1);

checkmove:
    INC_HL;
    DEC_C;
    IF_Z goto done;

    LD_A_de;
    INC_DE;
    AND_A_A;
    IF_Z goto done;

    PUSH_HL;
    PUSH_DE;
    PUSH_BC;
    LD_HL(mStallMoves);
    LD_DE(1);
    CALL(aIsInArray);

    POP_BC;
    POP_DE;
    POP_HL;
    IF_NC goto checkmove;

    INC_hl;
    goto checkmove;


done:
    RET;

// INCLUDE "data/battle/ai/stall_moves.asm"


    return AI_Aggressive();
}

void AI_Aggressive(void){
//  Use whatever does the most damage.

//  Discourage all damaging moves but the one that does the most damage.
//  If no damaging move deals damage to the player (immune),
//  no move will be discouraged

//  Figure out which attack does the most damage and put it in c.
    LD_HL(wEnemyMonMoves);
    LD_BC(0);
    LD_DE(0);

checkmove:
    INC_B;
    LD_A_B;
    CP_A(NUM_MOVES + 1);
    IF_Z goto gotstrongestmove;

    LD_A_hli;
    AND_A_A;
    IF_Z goto gotstrongestmove;

    PUSH_HL;
    PUSH_DE;
    PUSH_BC;
    CALL(aAIGetEnemyMove);
    LD_A_addr(wEnemyMoveStruct + MOVE_POWER);
    AND_A_A;
    IF_Z goto nodamage;
    CALL(aAIDamageCalc);
    POP_BC;
    POP_DE;
    POP_HL;

//  Update current move if damage is highest so far
    LD_A_addr(wCurDamage + 1);
    CP_A_E;
    LD_A_addr(wCurDamage);
    SBC_A_D;
    IF_C goto checkmove;

    LD_A_addr(wCurDamage + 1);
    LD_E_A;
    LD_A_addr(wCurDamage);
    LD_D_A;
    LD_C_B;
    goto checkmove;


nodamage:
    POP_BC;
    POP_DE;
    POP_HL;
    goto checkmove;


gotstrongestmove:
//  Nothing we can do if no attacks did damage.
    LD_A_C;
    AND_A_A;
    IF_Z goto done;

//  Discourage moves that do less damage unless they're reckless too.
    LD_HL(wEnemyAIMoveScores - 1);
    LD_DE(wEnemyMonMoves);
    LD_B(0);

checkmove2:
    INC_B;
    LD_A_B;
    CP_A(NUM_MOVES + 1);
    IF_Z goto done;

//  Ignore this move if it is the highest damaging one.
    CP_A_C;
    LD_A_de;
    INC_DE;
    INC_HL;
    IF_Z goto checkmove2;

    CALL(aAIGetEnemyMove);

//  Ignore this move if its power is 0 or 1.
//  Moves such as Seismic Toss, Hidden Power,
//  Counter and Fissure have a base power of 1.
    LD_A_addr(wEnemyMoveStruct + MOVE_POWER);
    CP_A(2);
    IF_C goto checkmove2;

//  Ignore this move if it is reckless.
    PUSH_HL;
    PUSH_DE;
    PUSH_BC;
    LD_A_addr(wEnemyMoveStruct + MOVE_EFFECT);
    LD_HL(mRecklessMoves);
    LD_DE(1);
    CALL(aIsInArray);
    POP_BC;
    POP_DE;
    POP_HL;
    IF_C goto checkmove2;

//  If we made it this far, discourage this move.
    INC_hl;
    goto checkmove2;


done:
    RET;

// INCLUDE "data/battle/ai/reckless_moves.asm"

    return AIDamageCalc();
}

void AIDamageCalc(void){
    LD_A(1);
    LDH_addr_A(hBattleTurn);
    LD_A_addr(wEnemyMoveStruct + MOVE_EFFECT);
    LD_DE(1);
    LD_HL(mConstantDamageEffects);
    CALL(aIsInArray);
    IF_NC goto notconstant;
    CALLFAR(aBattleCommand_ConstantDamage);
    RET;


notconstant:
    CALLFAR(aEnemyAttackDamage);
    CALLFAR(aBattleCommand_DamageCalc);
    CALLFAR(aBattleCommand_Stab);
    RET;

// INCLUDE "data/battle/ai/constant_damage_effects.asm"

    return AI_Cautious();
}

void AI_Cautious(void){
//  90% chance to discourage moves with residual effects after the first turn.

    LD_A_addr(wEnemyTurnsTaken);
    AND_A_A;
    RET_Z ;

    LD_HL(wEnemyAIMoveScores - 1);
    LD_DE(wEnemyMonMoves);
    LD_C(NUM_MOVES + 1);

loop:
    INC_HL;
    DEC_C;
    RET_Z ;

    LD_A_de;
    INC_DE;
    AND_A_A;
    RET_Z ;

    PUSH_HL;
    PUSH_DE;
    PUSH_BC;
    LD_HL(mResidualMoves);
    LD_DE(1);
    CALL(aIsInArray);

    POP_BC;
    POP_DE;
    POP_HL;
    IF_NC goto loop;

    CALL(aRandom);
    CP_A(90 percent + 1);
    RET_NC ;

    INC_hl;
    goto loop;

// INCLUDE "data/battle/ai/residual_moves.asm"


    return AI_Status();
}

void AI_Status(void){
//  Dismiss status moves that don't affect the player.

    LD_HL(wEnemyAIMoveScores - 1);
    LD_DE(wEnemyMonMoves);
    LD_B(NUM_MOVES + 1);

checkmove:
    DEC_B;
    RET_Z ;

    INC_HL;
    LD_A_de;
    AND_A_A;
    RET_Z ;

    INC_DE;
    CALL(aAIGetEnemyMove);

    LD_A_addr(wEnemyMoveStruct + MOVE_EFFECT);
    CP_A(EFFECT_TOXIC);
    IF_Z goto poisonimmunity;
    CP_A(EFFECT_POISON);
    IF_Z goto poisonimmunity;
    CP_A(EFFECT_SLEEP);
    IF_Z goto typeimmunity;
    CP_A(EFFECT_PARALYZE);
    IF_Z goto typeimmunity;

    LD_A_addr(wEnemyMoveStruct + MOVE_POWER);
    AND_A_A;
    IF_Z goto checkmove;

    goto typeimmunity;


poisonimmunity:
    LD_A_addr(wBattleMonType1);
    CP_A(POISON);
    IF_Z goto immune;
    LD_A_addr(wBattleMonType2);
    CP_A(POISON);
    IF_Z goto immune;


typeimmunity:
    PUSH_HL;
    PUSH_BC;
    PUSH_DE;
    LD_A(1);
    LDH_addr_A(hBattleTurn);
    CALLFAR(aBattleCheckTypeMatchup);
    POP_DE;
    POP_BC;
    POP_HL;

    LD_A_addr(wTypeMatchup);
    AND_A_A;
    IF_NZ goto checkmove;


immune:
    CALL(aAIDiscourageMove);
    goto checkmove;


    return AI_Risky();
}

void AI_Risky(void){
//  Use any move that will KO the target.
//  Risky moves will often be an exception (see below).

    LD_HL(wEnemyAIMoveScores - 1);
    LD_DE(wEnemyMonMoves);
    LD_C(NUM_MOVES + 1);

checkmove:
    INC_HL;
    DEC_C;
    RET_Z ;

    LD_A_de;
    INC_DE;
    AND_A_A;
    RET_Z ;

    PUSH_DE;
    PUSH_BC;
    PUSH_HL;
    CALL(aAIGetEnemyMove);

    LD_A_addr(wEnemyMoveStruct + MOVE_POWER);
    AND_A_A;
    IF_Z goto nextmove;

//  Don't use risky moves at max hp.
    LD_A_addr(wEnemyMoveStruct + MOVE_EFFECT);
    LD_DE(1);
    LD_HL(mRiskyEffects);
    CALL(aIsInArray);
    IF_NC goto checkko;

    CALL(aAICheckEnemyMaxHP);
    IF_C goto nextmove;

//  Else, 80% chance to exclude them.
    CALL(aRandom);
    CP_A(79 percent - 1);
    IF_C goto nextmove;


checkko:
    CALL(aAIDamageCalc);

    LD_A_addr(wCurDamage + 1);
    LD_E_A;
    LD_A_addr(wCurDamage);
    LD_D_A;
    LD_A_addr(wBattleMonHP + 1);
    CP_A_E;
    LD_A_addr(wBattleMonHP);
    SBC_A_D;
    IF_NC goto nextmove;

    POP_HL;
    for(int rept = 0; rept < 5; rept++){
    DEC_hl;
    }
    PUSH_HL;


nextmove:
    POP_HL;
    POP_BC;
    POP_DE;
    goto checkmove;

// INCLUDE "data/battle/ai/risky_effects.asm"


    return AI_None();
}

void AI_None(void){
    RET;

}

void AIDiscourageMove(void){
    LD_A_hl;
    ADD_A(10);
    LD_hl_A;
    RET;

}

void AIGetEnemyMove(void){
//  Load attributes of move a into ram

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

    POP_BC;
    POP_DE;
    POP_HL;
    RET;

}

void AI_80_20(void){
    CALL(aRandom);
    CP_A(20 percent - 1);
    RET;

}

void AI_50_50(void){
    CALL(aRandom);
    CP_A(50 percent + 1);
    RET;

}
