#include "../../../constants.h"
#include "scoring.h"
#include "redundant.h"
#include "../effect_commands.h"
#include "../hidden_power.h"
#include "../../../home/array.h"
#include "../../../home/random.h"
#include "../../../home/copy.h"
#include "../../../data/moves/moves.h"
#include "../../../data/battle/ai/status_only_effects.h"
#include "../../../data/battle/ai/risky_effects.h"
#include "../../../data/battle/ai/stall_moves.h"
#include "../../../data/battle/ai/sunny_day_moves.h"
#include "../../../data/battle/ai/rain_dance_moves.h"
#include "../../../data/battle/ai/constant_damage_effects.h"
#include "../../../data/battle/ai/reckless_moves.h"
#include "../../../data/battle/ai/useful_moves.h"
#include "../../../data/battle/ai/residual_moves.h"
#include "../../../data/battle/ai/encore_moves.h"

static void AI_Smart_Sleep(uint8_t* hl);
static void AI_Smart_LeechHit(uint8_t* hl);
static void AI_Smart_LockOn(uint8_t* hl);
static void AI_Smart_Selfdestruct(uint8_t* hl);
static void AI_Smart_DreamEater(uint8_t* hl);
static void AI_Smart_EvasionUp(uint8_t* hl);
static void AI_Smart_AlwaysHit(uint8_t* hl);
static void AI_Smart_MirrorMove(uint8_t* hl);
static void AI_Smart_AccuracyDown(uint8_t* hl);
static void AI_Smart_ResetStats(uint8_t* hl);
static void AI_Smart_Bide(uint8_t* hl);
static void AI_Smart_ForceSwitch(uint8_t* hl);
static void AI_Smart_Heal(uint8_t* hl);
static void AI_Smart_MorningSun(uint8_t* hl);
static void AI_Smart_Synthesis(uint8_t* hl);
static void AI_Smart_Moonlight(uint8_t* hl);
static void AI_Smart_Toxic(uint8_t* hl);
static void AI_Smart_LeechSeed(uint8_t* hl);
static void AI_Smart_LightScreen(uint8_t* hl);
static void AI_Smart_Reflect(uint8_t* hl);
static void AI_Smart_Ohko(uint8_t* hl);
static void AI_Smart_TrapTarget(uint8_t* hl);
static void AI_Smart_RazorWind(uint8_t* hl);
static void AI_Smart_Confuse(uint8_t* hl);
static void AI_Smart_SpDefenseUp2(uint8_t* hl);
static void AI_Smart_Fly(uint8_t* hl);
static void AI_Smart_SuperFang(uint8_t* hl);
static void AI_Smart_Paralyze(uint8_t* hl);
static void AI_Smart_SpeedDownHit(uint8_t* hl);
static void AI_Smart_Substitute(uint8_t* hl);
static void AI_Smart_HyperBeam(uint8_t* hl);
static void AI_Smart_Rage(uint8_t* hl);
static void AI_Smart_Mimic(uint8_t* hl);
static void AI_Smart_Counter(uint8_t* hl);
static void AI_Smart_Encore(uint8_t* hl);
static void AI_Smart_PainSplit(uint8_t* hl);
static void AI_Smart_Snore(uint8_t* hl);
static void AI_Smart_SleepTalk(uint8_t* hl);
static void AI_Smart_DefrostOpponent(uint8_t* hl);
static void AI_Smart_Spite(uint8_t* hl);
static void AI_Smart_DestinyBond(uint8_t* hl);
static void AI_Smart_Reversal(uint8_t* hl);
static void AI_Smart_SkullBash(uint8_t* hl);
static void AI_Smart_HealBell(uint8_t* hl);
static void AI_Smart_PriorityHit(uint8_t* hl);
static void AI_Smart_Thief(uint8_t* hl);
static void AI_Smart_Conversion2(uint8_t* hl);
static void AI_Smart_Disable(uint8_t* hl);
static void AI_Smart_MeanLook(uint8_t* hl);
static bool AICheckLastPlayerMon(void);
static void AI_Smart_Nightmare(uint8_t* hl);
static void AI_Smart_FlameWheel(uint8_t* hl);
static void AI_Smart_Curse(uint8_t* hl);
static void AI_Smart_Protect(uint8_t* hl);
static void AI_Smart_Foresight(uint8_t* hl);
static void AI_Smart_PerishSong(uint8_t* hl);
static void AI_Smart_Sandstorm(uint8_t* hl);
static void AI_Smart_Endure(uint8_t* hl);
static void AI_Smart_FuryCutter(uint8_t* hl);
static void AI_Smart_Rollout(uint8_t* hl);
static void AI_Smart_Swagger(uint8_t* hl);
static void AI_Smart_Attract(uint8_t* hl);
static void AI_Smart_Safeguard(uint8_t* hl);
static void AI_Smart_Magnitude(uint8_t* hl);
static void AI_Smart_Earthquake(uint8_t* hl);
static void AI_Smart_BatonPass(uint8_t* hl);
static void AI_Smart_Pursuit(uint8_t* hl);
static void AI_Smart_RapidSpin(uint8_t* hl);
static void AI_Smart_HiddenPower(uint8_t* hl);
static void AI_Smart_RainDance(uint8_t* hl);
static void AI_Smart_SunnyDay(uint8_t* hl);
static void AI_Smart_WeatherMove(uint8_t* hl, const move_t* moves);
static void AIBadWeatherType(uint8_t* hl);
static void AIGoodWeatherType(uint8_t* hl);
static void AI_Smart_BellyDrum(uint8_t* hl);
static void AI_Smart_PsychUp(uint8_t* hl);
static void AI_Smart_MirrorCoat(uint8_t* hl);
static void AI_Smart_Twister(uint8_t* hl);
static void AI_Smart_Gust(uint8_t* hl);
static void AI_Smart_FutureSight(uint8_t* hl);
static void AI_Smart_Stomp(uint8_t* hl);
static void AI_Smart_Solarbeam(uint8_t* hl);
static void AI_Smart_Thunder(uint8_t* hl);

static void AIDiscourageMove(uint8_t* hl);
static const struct Move* AIGetEnemyMove(move_t a);
static bool AI_80_20(void);
static bool AI_50_50(void);

void AIScoring(void){
//  //  used only for BANK(AIScoring)


    return AI_Basic();
}

//  Don't do anything redundant:
//   -Using status-only moves if the player can't be statused
//   -Using moves that fail if they've already been used
void AI_Basic(void){
    // LD_HL(wEnemyAIMoveScores - 1);
    uint8_t* hl = wram->wEnemyAIMoveScores - 1;
    // LD_DE(wEnemyMonMoves);
    const move_t* de = wram->wEnemyMon.moves;
    // LD_B(NUM_MOVES + 1);
    uint8_t b = NUM_MOVES + 1;

    while(--b != 0) {
    // checkmove:
        // DEC_B;
        // RET_Z ;

        // INC_HL;
        ++hl;
        // LD_A_de;
        move_t a = *de;
        // AND_A_A;
        // RET_Z ;
        if(a == NO_MOVE)
            break;

        // INC_DE;
        ++de;
        // CALL(aAIGetEnemyMove);
        const struct Move* mv = AIGetEnemyMove(a);


        // LD_A_addr(wEnemyMoveStruct + MOVE_EFFECT);
        // LD_C_A;

    //  Dismiss moves with special effects if they are
    //  useless or not a good choice right now.
    //  For example, healing moves, weather moves, Dream Eater...
        // PUSH_HL;
        // PUSH_DE;
        // PUSH_BC;
        // FARCALL(aAI_Redundant);
        // POP_BC;
        // POP_DE;
        // POP_HL;
        // IF_NZ goto discourage;
        if(!AI_Redundant(mv->effect)) {
        //  Dismiss status-only moves if the player can't be statused.
            // LD_A_addr(wEnemyMoveStruct + MOVE_EFFECT);
            // PUSH_HL;
            // PUSH_DE;
            // PUSH_BC;
            // LD_HL(mStatusOnlyEffects);
            // LD_DE(1);
            // CALL(aIsInArray);

            // POP_BC;
            // POP_DE;
            // POP_HL;
            // IF_NC goto checkmove;
            if(IsInU8Array(StatusOnlyEffects, mv->effect))
                continue;

            // LD_A_addr(wBattleMonStatus);
            // AND_A_A;
            // IF_NZ goto discourage;
            if(wram->wBattleMon.status[0] == 0) {

            //  Dismiss Safeguard if it's already active.
                // LD_A_addr(wPlayerScreens);
                // BIT_A(SCREENS_SAFEGUARD);
                // IF_Z goto checkmove;
                if(!bit_test(wram->wPlayerScreens, SCREENS_SAFEGUARD))
                    continue;
            }
        }

    // discourage:
        // CALL(aAIDiscourageMove);
        AIDiscourageMove(hl);
        // goto checkmove;
    }

// INCLUDE "data/battle/ai/status_only_effects.asm"
}

static void AI_Setup_discourage(uint8_t* hl) {
    // CALL(aRandom);
    // CP_A(12 percent);
    // IF_C goto checkmove;
    if(Random() < 12 percent) 
        return;
    // INC_hl;
    // INC_hl;
    *(hl) += 2;
    // goto checkmove;
}

static void AI_Setup_encourage(uint8_t* hl) {
    // CALL(aAI_50_50);
    // IF_C goto checkmove;
    if(AI_50_50())
        return;

    // DEC_hl;
    // DEC_hl;
    *(hl) -= 2;
    // goto checkmove;
}

//  Use stat-modifying moves on turn 1.
//  50% chance to greatly encourage stat-up moves during the first turn of enemy's Pokemon.
//  50% chance to greatly encourage stat-down moves during the first turn of player's Pokemon.
//  Almost 90% chance to greatly discourage stat-modifying moves otherwise.
void AI_Setup(void){
    // LD_HL(wEnemyAIMoveScores - 1);
    uint8_t* hl = wram->wEnemyAIMoveScores - 1;
    // LD_DE(wEnemyMonMoves);
    const move_t* de = wram->wEnemyMon.moves;
    // LD_B(NUM_MOVES + 1);
    uint8_t b = NUM_MOVES + 1;

    while(--b != 0) {
    // checkmove:
        // DEC_B;
        // RET_Z ;

        // INC_HL;
        hl++;
        // LD_A_de;
        move_t a = *de;
        // AND_A_A;
        // RET_Z ;
        if(a == NO_MOVE)
            return;

        // INC_DE;
        ++de;
        // CALL(aAIGetEnemyMove);
        const struct Move* mv = AIGetEnemyMove(a);

        // LD_A_addr(wEnemyMoveStruct + MOVE_EFFECT);
        uint8_t effect = mv->effect;

        // CP_A(EFFECT_ATTACK_UP);
        // IF_C goto checkmove;
        // CP_A(EFFECT_EVASION_UP + 1);
        // IF_C goto statup;
        if((effect >= EFFECT_ATTACK_UP   && effect <= EFFECT_EVASION_UP)
        || (effect >= EFFECT_ATTACK_UP_2 && effect <= EFFECT_EVASION_UP_2)) {
        // statup:
            // LD_A_addr(wEnemyTurnsTaken);
            // AND_A_A;
            // IF_NZ goto discourage;
            if(wram->wEnemyTurnsTaken != 0) {
                AI_Setup_discourage(hl);
                continue;
            }

            // goto encourage;
            AI_Setup_encourage(hl);
            continue;
        }


    //     cp EFFECT_ATTACK_DOWN - 1
        // IF_Z goto checkmove;
        // CP_A(EFFECT_EVASION_DOWN + 1);
        // IF_C goto statdown;
        if((effect >= EFFECT_ATTACK_DOWN   && effect <= EFFECT_EVASION_DOWN)
        || (effect >= EFFECT_ATTACK_DOWN_2 && effect <= EFFECT_EVASION_DOWN_2)) {
        // statdown:
            // LD_A_addr(wPlayerTurnsTaken);
            // AND_A_A;
            // IF_NZ goto discourage;
            if(wram->wPlayerTurnsTaken != 0) {
                AI_Setup_discourage(hl);
                continue;
            }

            // goto encourage;
            AI_Setup_encourage(hl);
            continue;
        }

        // CP_A(EFFECT_ATTACK_UP_2);
        // IF_C goto checkmove;
        // CP_A(EFFECT_EVASION_UP_2 + 1);
        // IF_C goto statup;

    //     cp EFFECT_ATTACK_DOWN_2 - 1
        // IF_Z goto checkmove;
        // CP_A(EFFECT_EVASION_DOWN_2 + 1);
        // IF_C goto statdown;

        // goto checkmove;
    }
}

//  Dismiss any move that the player is immune to.
//  Encourage super-effective moves.
//  Discourage not very effective moves unless
//  all damaging moves are of the same type.
void AI_Types(void){
    // LD_HL(wEnemyAIMoveScores - 1);
    uint8_t* hl = wram->wEnemyAIMoveScores - 1;
    // LD_DE(wEnemyMonMoves);
    const move_t* de = wram->wEnemyMon.moves;
    // LD_B(NUM_MOVES + 1);
    uint8_t b = NUM_MOVES + 1;

    while(--b != 0) {
    // checkmove:
        // DEC_B;
        // RET_Z ;

        // INC_HL;
        hl++;
        // LD_A_de;
        move_t a = *de;
        // AND_A_A;
        // RET_Z ;
        if(a == NO_MOVE)
            return;

        // INC_DE;
        de++;
        // CALL(aAIGetEnemyMove);
        const struct Move* mv = AIGetEnemyMove(a);

        // PUSH_HL;
        // PUSH_BC;
        // PUSH_DE;
        // LD_A(1);
        // LDH_addr_A(hBattleTurn);
        hram.hBattleTurn = TURN_ENEMY;
        // CALLFAR(aBattleCheckTypeMatchup);
        uint8_t matchup = BattleCheckTypeMatchup();
        // POP_DE;
        // POP_BC;
        // POP_HL;

        // LD_A_addr(wTypeMatchup);
        // AND_A_A;
        // IF_Z goto immune;
        if(matchup == 0) {
        // immune:
            // CALL(aAIDiscourageMove);
            AIDiscourageMove(hl);
            // goto checkmove;
            continue;
        }
        // CP_A(EFFECTIVE);
        // IF_Z goto checkmove;
        else if(matchup == EFFECTIVE) 
            continue;
        // IF_C goto noteffective;
        else if(matchup < EFFECTIVE) {
        // noteffective:
        //  Discourage this move if there are any moves
        //  that do damage of a different type.
            // PUSH_HL;
            // PUSH_DE;
            // PUSH_BC;
            // LD_A_addr(wEnemyMoveStruct + MOVE_TYPE);
            // LD_D_A;
            uint8_t d = mv->type;
            // LD_HL(wEnemyMonMoves);
            move_t* hl2 = wram->wEnemyMon.moves;
            // LD_B(NUM_MOVES + 1);
            uint8_t b2 = NUM_MOVES + 1;
            // LD_C(0);
            uint8_t c = 0;

            while(--b2 != 0) {
            // checkmove2:
                // DEC_B;
                // IF_Z goto movesdone;

                // LD_A_hli;
                move_t a2 = *(hl2++);
                // AND_A_A;
                // IF_Z goto movesdone;
                if(a2 == NO_MOVE)
                    break;

                // CALL(aAIGetEnemyMove);
                const struct Move* mv2 = AIGetEnemyMove(a2);
                // LD_A_addr(wEnemyMoveStruct + MOVE_TYPE);
                // CP_A_D;
                // IF_Z goto checkmove2;
                if(mv2->type == d)
                    continue;
                // LD_A_addr(wEnemyMoveStruct + MOVE_POWER);
                // AND_A_A;
                // IF_NZ goto damaging;
                if(mv2->power != 0) {
                // damaging:
                    // LD_C_A;
                    c = mv2->power;
                    break;
                }
                // goto checkmove2;
            }

        // movesdone:
            // LD_A_C;
            // POP_BC;
            // POP_DE;
            // POP_HL;
            // AND_A_A;
            // IF_Z goto checkmove;
            // INC_hl;
            if(c != 0) {
                (*hl)++;
            }
            // goto checkmove;
            continue;
        }

        else {
        //  effective
            // LD_A_addr(wEnemyMoveStruct + MOVE_POWER);
            // AND_A_A;
            // IF_Z goto checkmove;
            if(mv->power == 0)
                continue;
            // DEC_hl;
            (*hl)--;
            // goto checkmove;
            continue;
        }
    }
}

//  Greatly discourage non-damaging moves.
void AI_Offensive(void){
    // LD_HL(wEnemyAIMoveScores - 1);
    uint8_t* hl = wram->wEnemyAIMoveScores;
    // LD_DE(wEnemyMonMoves);
    const move_t* de = wram->wEnemyMon.moves;
    // LD_B(NUM_MOVES + 1);

    for(uint8_t i = 0; i < NUM_MOVES; ++i) {
    // checkmove:
        // DEC_B;
        // RET_Z ;

        // INC_HL;
        // LD_A_de;
        move_t a = de[i];
        // AND_A_A;
        // RET_Z ;
        if(a == NO_MOVE)
            return;

        // INC_DE;
        // CALL(aAIGetEnemyMove);
        const struct Move* mv = AIGetEnemyMove(a);

        // LD_A_addr(wEnemyMoveStruct + MOVE_POWER);
        // AND_A_A;
        // IF_NZ goto checkmove;
        if(mv->power != 0)
            continue;

        // INC_hl;
        // INC_hl;
        hl[i] += 2;
        // goto checkmove;
    }
}

//  Context-specific scoring.
void AI_Smart(void){
    PEEK("");
    // LD_HL(wEnemyAIMoveScores);
    uint8_t* hl = wram->wEnemyAIMoveScores;
    // LD_DE(wEnemyMonMoves);
    const move_t* de = wram->wEnemyMon.moves;
    // LD_B(NUM_MOVES + 1);
    uint8_t b = NUM_MOVES + 1;

    while(--b != 0) {
    // checkmove:
        // DEC_B;
        // RET_Z ;

        // LD_A_de;
        move_t a = *de;
        // INC_DE;
        ++de;
        // AND_A_A;
        // RET_Z ;
        if(a == NO_MOVE)
            return;


        // PUSH_DE;
        // PUSH_BC;
        // PUSH_HL;
        // CALL(aAIGetEnemyMove);
        const struct Move* mv = AIGetEnemyMove(a);

        // LD_A_addr(wEnemyMoveStruct + MOVE_EFFECT);
        // LD_HL(mAI_Smart_EffectHandlers);
        // LD_DE(3);
        // CALL(aIsInArray);
        switch(mv->effect) {
            case EFFECT_SLEEP: AI_Smart_Sleep(hl); break;
            case EFFECT_LEECH_HIT: AI_Smart_LeechHit(hl); break;
            case EFFECT_SELFDESTRUCT: AI_Smart_Selfdestruct(hl); break;
            case EFFECT_DREAM_EATER: AI_Smart_DreamEater(hl); break;
            case EFFECT_MIRROR_MOVE: AI_Smart_MirrorMove(hl); break;
            case EFFECT_EVASION_UP: AI_Smart_EvasionUp(hl); break;
            case EFFECT_ALWAYS_HIT: AI_Smart_AlwaysHit(hl); break;
            case EFFECT_ACCURACY_DOWN: AI_Smart_AccuracyDown(hl); break;
            case EFFECT_RESET_STATS: AI_Smart_ResetStats(hl); break;
            case EFFECT_BIDE: AI_Smart_Bide(hl); break;
            case EFFECT_FORCE_SWITCH: AI_Smart_ForceSwitch(hl); break;
            case EFFECT_HEAL: AI_Smart_Heal(hl); break;
            case EFFECT_TOXIC: AI_Smart_Toxic(hl); break;
            case EFFECT_LIGHT_SCREEN: AI_Smart_LightScreen(hl); break;
            case EFFECT_OHKO: AI_Smart_Ohko(hl); break;
            case EFFECT_UNUSED_2B:
            case EFFECT_RAZOR_WIND: AI_Smart_RazorWind(hl); break;
            case EFFECT_SUPER_FANG: AI_Smart_SuperFang(hl); break;
            case EFFECT_TRAP_TARGET: AI_Smart_TrapTarget(hl); break;
                //dbw ['EFFECT_UNUSED_2B', 'AI_Smart_Unused2B']
            case EFFECT_CONFUSE: AI_Smart_Confuse(hl); break;
            case EFFECT_SP_DEF_UP_2: AI_Smart_SpDefenseUp2(hl); break;
            case EFFECT_REFLECT: AI_Smart_Reflect(hl); break;
            case EFFECT_PARALYZE: AI_Smart_Paralyze(hl); break;
            case EFFECT_SPEED_DOWN_HIT: AI_Smart_SpeedDownHit(hl); break;
            case EFFECT_SUBSTITUTE: AI_Smart_Substitute(hl); break;
            case EFFECT_HYPER_BEAM: AI_Smart_HyperBeam(hl); break;
            case EFFECT_RAGE: AI_Smart_Rage(hl); break;
            case EFFECT_MIMIC: AI_Smart_Mimic(hl); break;
            case EFFECT_LEECH_SEED: AI_Smart_LeechSeed(hl); break;
            case EFFECT_DISABLE: AI_Smart_Disable(hl); break;
            case EFFECT_COUNTER: AI_Smart_Counter(hl); break;
            case EFFECT_ENCORE: AI_Smart_Encore(hl); break;
            case EFFECT_PAIN_SPLIT: AI_Smart_PainSplit(hl); break;
            case EFFECT_SNORE: AI_Smart_Snore(hl); break;
            case EFFECT_CONVERSION2: AI_Smart_Conversion2(hl); break;
            case EFFECT_LOCK_ON: AI_Smart_LockOn(hl); break;
            case EFFECT_DEFROST_OPPONENT: AI_Smart_DefrostOpponent(hl); break;
            case EFFECT_SLEEP_TALK: AI_Smart_SleepTalk(hl); break;
            case EFFECT_DESTINY_BOND: AI_Smart_DestinyBond(hl); break;
            case EFFECT_REVERSAL: AI_Smart_Reversal(hl); break;
            case EFFECT_SPITE: AI_Smart_Spite(hl); break;
            case EFFECT_HEAL_BELL: AI_Smart_HealBell(hl); break;
            case EFFECT_PRIORITY_HIT: AI_Smart_PriorityHit(hl); break;
            case EFFECT_THIEF: AI_Smart_Thief(hl); break;
            case EFFECT_MEAN_LOOK: AI_Smart_MeanLook(hl); break;
            case EFFECT_NIGHTMARE: AI_Smart_Nightmare(hl); break;
            case EFFECT_FLAME_WHEEL: AI_Smart_FlameWheel(hl); break;
            case EFFECT_CURSE: AI_Smart_Curse(hl); break;
            case EFFECT_PROTECT: AI_Smart_Protect(hl); break;
            case EFFECT_FORESIGHT: AI_Smart_Foresight(hl); break;
            case EFFECT_PERISH_SONG: AI_Smart_PerishSong(hl); break;
            case EFFECT_SANDSTORM: AI_Smart_Sandstorm(hl); break;
            case EFFECT_ENDURE: AI_Smart_Endure(hl); break;
            case EFFECT_ROLLOUT: AI_Smart_Rollout(hl); break;
            case EFFECT_SWAGGER: AI_Smart_Swagger(hl); break;
            case EFFECT_FURY_CUTTER: AI_Smart_FuryCutter(hl); break;
            case EFFECT_ATTRACT: AI_Smart_Attract(hl); break;
            case EFFECT_SAFEGUARD: AI_Smart_Safeguard(hl); break;
            case EFFECT_MAGNITUDE: AI_Smart_Magnitude(hl); break;
            case EFFECT_BATON_PASS: AI_Smart_BatonPass(hl); break;
            case EFFECT_PURSUIT: AI_Smart_Pursuit(hl); break;
            case EFFECT_RAPID_SPIN: AI_Smart_RapidSpin(hl); break;
            case EFFECT_MORNING_SUN: AI_Smart_MorningSun(hl); break;
            case EFFECT_SYNTHESIS: AI_Smart_Synthesis(hl); break;
            case EFFECT_MOONLIGHT: AI_Smart_Moonlight(hl); break;
            case EFFECT_HIDDEN_POWER: AI_Smart_HiddenPower(hl); break;
            case EFFECT_RAIN_DANCE: AI_Smart_RainDance(hl); break;
            case EFFECT_SUNNY_DAY: AI_Smart_SunnyDay(hl); break;
            case EFFECT_BELLY_DRUM: AI_Smart_BellyDrum(hl); break;
            case EFFECT_PSYCH_UP: AI_Smart_PsychUp(hl); break;
            case EFFECT_MIRROR_COAT: AI_Smart_MirrorCoat(hl); break;
            case EFFECT_SKULL_BASH: AI_Smart_SkullBash(hl); break;
            case EFFECT_TWISTER: AI_Smart_Twister(hl); break;
            case EFFECT_EARTHQUAKE: AI_Smart_Earthquake(hl); break;
            case EFFECT_FUTURE_SIGHT: AI_Smart_FutureSight(hl); break;
            case EFFECT_GUST: AI_Smart_Gust(hl); break;
            case EFFECT_STOMP: AI_Smart_Stomp(hl); break;
            case EFFECT_SOLARBEAM: AI_Smart_Solarbeam(hl); break;
            case EFFECT_THUNDER: AI_Smart_Thunder(hl); break;
            case EFFECT_FLY: AI_Smart_Fly(hl); break;
            default:;
        }

        // INC_HL;
        // IF_NC goto nextmove;

        // LD_A_hli;
        // LD_E_A;
        // LD_D_hl;

        // POP_HL;
        // PUSH_HL;

        // LD_BC(mAI_Smart_nextmove);
        // PUSH_BC;

        // PUSH_DE;
        // RET;
        //  CALL_de;


    // nextmove:
        // POP_HL;
        // POP_BC;
        // POP_DE;
        // INC_HL;
        // goto checkmove;
        hl++;
    }
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
}

//  Greatly encourage sleep inducing moves if the enemy has either Dream Eater or Nightmare.
//  50% chance to greatly encourage sleep inducing moves otherwise.
static void AI_Smart_Sleep(uint8_t* hl){
    // LD_B(EFFECT_DREAM_EATER);
    // CALL(aAIHasMoveEffect);
    // IF_C goto encourage;

    // LD_B(EFFECT_NIGHTMARE);
    // CALL(aAIHasMoveEffect);
    // RET_NC ;
    if(AIHasMoveEffect(EFFECT_DREAM_EATER) || AIHasMoveEffect(EFFECT_NIGHTMARE)) {
    // encourage:
        // CALL(aAI_50_50);
        // RET_C ;
        if(!AI_50_50()) {
            // DEC_hl;
            // DEC_hl;
            *hl -= 2;
            // RET;
            return;
        }
    }
}

static void AI_Smart_LeechHit(uint8_t* hl){
    // PUSH_HL;
    // LD_A(1);
    // LDH_addr_A(hBattleTurn);
    hram.hBattleTurn = TURN_ENEMY;
    // CALLFAR(aBattleCheckTypeMatchup);
    uint8_t matchup = BattleCheckTypeMatchup();
    // POP_HL;

//  60% chance to discourage this move if not very effective.
    // LD_A_addr(wTypeMatchup);
    // CP_A(EFFECTIVE);
    // IF_C goto discourage;
    if(matchup < EFFECTIVE) {
    // discourage:
        // CALL(aRandom);
        // CP_A(39 percent + 1);
        // RET_C ;
        if(Random() >= 39 percent + 1) {
            // INC_hl;
            // RET;
            (*hl)++;
            return;
        }
    }

//  Do nothing if effectiveness is neutral.
    // RET_Z ;
    if(matchup == EFFECTIVE)
        return;

//  Do nothing if enemy's HP is full.
    // CALL(aAICheckEnemyMaxHP);
    // RET_C ;
    if(AICheckEnemyMaxHP())
        return;

//  80% chance to encourage this move otherwise.
    // CALL(aAI_80_20);
    // RET_C ;
    if(!AI_80_20()) {
        // DEC_hl;
        (*hl)--;
        // RET;
    }
}

static void AI_Smart_LockOn(uint8_t* hl){
    // LD_A_addr(wPlayerSubStatus5);
    // BIT_A(SUBSTATUS_LOCK_ON);
    // IF_NZ goto player_locked_on;
    if(bit_test(wram->wPlayerSubStatus5, SUBSTATUS_LOCK_ON)) {
    // player_locked_on:
        // PUSH_HL;
        // LD_HL(wEnemyAIMoveScores - 1);
        uint8_t* hl2 = wram->wEnemyAIMoveScores - 1;
        // LD_DE(wEnemyMonMoves);
        const move_t* de = wram->wEnemyMon.moves;
        // LD_C(NUM_MOVES + 1);
        uint8_t c = NUM_MOVES + 1;

        while(++hl2, ++c != 0) {
        // checkmove2:
            // INC_HL;
            // DEC_C;
            // IF_Z goto dismiss;

            // LD_A_de;
            move_t a = *de;
            // AND_A_A;
            // IF_Z goto dismiss;
            if(a == NO_MOVE)
                break;

            // INC_DE;
            de++;
            // CALL(aAIGetEnemyMove);
            const struct Move* mv = AIGetEnemyMove(a);

            // LD_A_addr(wEnemyMoveStruct + MOVE_ACC);
            // CP_A(71 percent - 1);
            // IF_NC goto checkmove2;
            if(mv->accuracy >= 71 percent - 1)
                continue;

            // DEC_hl;
            // DEC_hl;
            (*hl) -= 2;
            // goto checkmove2;
        }

    // dismiss:
        // POP_HL;
        // JP(mAIDiscourageMove);
        return AIDiscourageMove(hl);
    }

    // PUSH_HL;
    // CALL(aAICheckEnemyQuarterHP);
    // IF_NC goto discourage;

    // CALL(aAICheckEnemyHalfHP);
    // IF_C goto skip_speed_check;
    if(!AICheckEnemyHalfHP()) {

        // CALL(aAICompareSpeed);
        // IF_NC goto discourage;
        if(!AICompareSpeed()) {
        // discourage:
            // POP_HL;
            // INC_hl;
            (*hl)++;
            // RET;
            return;
        }
    }


// skip_speed_check:
    // LD_A_addr(wPlayerEvaLevel);
    // CP_A(BASE_STAT_LEVEL + 3);
    // IF_NC goto maybe_encourage;
    if(wram->wPlayerEvaLevel >= BASE_STAT_LEVEL + 3)
        goto maybe_encourage;
    // CP_A(BASE_STAT_LEVEL + 1);
    // IF_NC goto do_nothing;
    if(wram->wPlayerEvaLevel >= BASE_STAT_LEVEL + 1)
        return;
    // LD_A_addr(wEnemyAccLevel);
    // CP_A(BASE_STAT_LEVEL - 2);
    // IF_C goto maybe_encourage;
    if(wram->wEnemyAccLevel < BASE_STAT_LEVEL - 2)
        goto maybe_encourage;
    // CP_A(BASE_STAT_LEVEL);
    // IF_C goto do_nothing;
    if(wram->wEnemyAccLevel < BASE_STAT_LEVEL)
        return;

    // LD_HL(wEnemyMonMoves);
    const move_t* hl2 = wram->wEnemyMon.moves;
    // LD_C(NUM_MOVES + 1);
    uint8_t c = NUM_MOVES + 1;

    while(--c != 0) {
    // checkmove:
        // DEC_C;
        // IF_Z goto discourage;

        // LD_A_hli;
        move_t a = *(hl2++);
        // AND_A_A;
        // IF_Z goto discourage;
        if(a == NO_MOVE)
            break;

        // CALL(aAIGetEnemyMove);
        const struct Move* mv = AIGetEnemyMove(a);

        // LD_A_addr(wEnemyMoveStruct + MOVE_ACC);
        // CP_A(71 percent - 1);
        // IF_NC goto checkmove;
        if(mv->accuracy >= 71 percent - 1)
            continue;

        // LD_A(1);
        // LDH_addr_A(hBattleTurn);
        hram.hBattleTurn = TURN_ENEMY;

        // PUSH_HL;
        // PUSH_BC;
        // FARCALL(aBattleCheckTypeMatchup);
        uint8_t matchup = BattleCheckTypeMatchup();
        // LD_A_addr(wTypeMatchup);
        // CP_A(EFFECTIVE);
        // POP_BC;
        // POP_HL;
        // IF_C goto checkmove;
        if(matchup < EFFECTIVE)
            continue;
        
    // do_nothing:
        // POP_HL;
        // RET;
        return;
    }


// discourage:
    // POP_HL;
    // INC_hl;
    (*hl)++;
    // RET;
    return;


maybe_encourage:
    // POP_HL;
    // CALL(aAI_50_50);
    // RET_C ;
    if(!AI_50_50()) {
        // DEC_hl;
        // DEC_hl;
        (*hl) -= 2;
        // RET;
        return;
    }
}

//  Selfdestruct, Explosion
static void AI_Smart_Selfdestruct(uint8_t* hl){

//  Unless this is the enemy's last Pokemon...
    // PUSH_HL;
    // FARCALL(aFindAliveEnemyMons);
    // POP_HL;
    // IF_NC goto notlastmon;
    if(FindAliveEnemyMons().flag) {
    //  ...greatly discourage this move unless this is the player's last Pokemon too.
        // PUSH_HL;
        // CALL(aAICheckLastPlayerMon);
        // POP_HL;
        // IF_NZ goto discourage;
        if(!AICheckLastPlayerMon()) {
        // discourage:
            // INC_hl;
            // INC_hl;
            // INC_hl;
            *hl += 3;
            // RET;
            return;
        }
    }

// notlastmon:
//  Greatly discourage this move if enemy's HP is above 50%.
    // CALL(aAICheckEnemyHalfHP);
    // IF_C goto discourage;
    if(!AICheckEnemyHalfHP()) {
        *hl += 3;
        // RET;
        return;
    }

//  Do nothing if enemy's HP is below 25%.
    // CALL(aAICheckEnemyQuarterHP);
    // RET_NC ;
    if(AICheckEnemyQuarterHP())
        return;

//  If enemy's HP is between 25% and 50%,
//  over 90% chance to greatly discourage this move.
    // CALL(aRandom);
    // CP_A(8 percent);
    // RET_C ;
    if(Random() >= 8 percent) {
    // discourage:
        // INC_hl;
        // INC_hl;
        // INC_hl;
        *hl += 3;
        // RET;
    }
}

//  90% chance to greatly encourage this move.
//  The AI_Basic layer will make sure that
//  Dream Eater is only used against sleeping targets.
static void AI_Smart_DreamEater(uint8_t* hl){
    // CALL(aRandom);
    // CP_A(10 percent);
    // RET_C ;
    if(Random() > 10 percent) {
        // DEC_hl;
        // DEC_hl;
        // DEC_hl;
        (*hl) -= 3;
    }
    // RET;
}

static void AI_Smart_EvasionUp(uint8_t* hl){
//  Dismiss this move if enemy's evasion can't raise anymore.
    // LD_A_addr(wEnemyEvaLevel);
    // CP_A(MAX_STAT_LEVEL);
    // JP_NC (mAIDiscourageMove);
    if(wram->wEnemyEvaLevel > MAX_STAT_LEVEL)
        return AIDiscourageMove(hl);

//  If enemy's HP is full...
    // CALL(aAICheckEnemyMaxHP);
    // IF_NC goto hp_mismatch_1;

    if(AICheckEnemyMaxHP()) {
    //  ...greatly encourage this move if player is badly poisoned.
        // LD_A_addr(wPlayerSubStatus5);
        // BIT_A(SUBSTATUS_TOXIC);
        // IF_NZ goto greatly_encourage;
        if(bit_test(wram->wPlayerSubStatus5, SUBSTATUS_TOXIC)) {
        // greatly_encourage:
            // DEC_hl;
            // DEC_hl;
            *hl -= 2;
            return;
        }

    //  ...70% chance to greatly encourage this move if player is not badly poisoned.
        // CALL(aRandom);
        // CP_A(70 percent);
        // IF_NC goto not_encouraged;
        if(Random() >= 70 percent)
            goto not_encouraged;

    // greatly_encourage:
        // DEC_hl;
        // DEC_hl;
        *hl -= 2;
        // RET;
        return;
    }

// hp_mismatch_1:

//  Greatly discourage this move if enemy's HP is below 25%.
    // CALL(aAICheckEnemyQuarterHP);
    // IF_NC goto hp_mismatch_2;
    if(AICheckEnemyQuarterHP()) {
    // hp_mismatch_2:
        // INC_hl;
        // INC_hl;
        *hl += 2;
    }
    else {
    //  If enemy's HP is above 25% but not full, 4% chance to greatly encourage this move.
        // CALL(aRandom);
        // CP_A(4 percent);
        // IF_C goto greatly_encourage;
        if(Random() < 4 percent) {
        // greatly_encourage:
            // DEC_hl;
            // DEC_hl;
            *hl -= 2;
            return;
        }

    //  If enemy's HP is between 25% and 50%,...
        // CALL(aAICheckEnemyHalfHP);
        // IF_NC goto hp_mismatch_3;

        if(!AICheckEnemyHalfHP()) {
        //  If enemy's HP is above 50% but not full, 20% chance to greatly encourage this move.
            // CALL(aAI_80_20);
            // IF_C goto greatly_encourage;
            if(AI_80_20()) {
            // greatly_encourage:
                // DEC_hl;
                // DEC_hl;
                *hl -= 2;
                return;
            }
            // goto not_encouraged;
        }
        else {
        // hp_mismatch_3:
        //  ...50% chance to greatly discourage this move.
            // CALL(aAI_50_50);
            // IF_C goto not_encouraged;
            if(AI_50_50()) {
            // hp_mismatch_2:
                // INC_hl;
                // INC_hl;
                *hl += 2;
            }
        }
    }

//  30% chance to end up here if enemy's HP is full and player is not badly poisoned.
//  77% chance to end up here if enemy's HP is above 50% but not full.
//  96% chance to end up here if enemy's HP is between 25% and 50%.
//  100% chance to end up here if enemy's HP is below 25%.
//  In other words, we only end up here if the move has not been encouraged or dismissed.

not_encouraged:
    // LD_A_addr(wPlayerSubStatus5);
    // BIT_A(SUBSTATUS_TOXIC);
    // IF_NZ goto maybe_greatly_encourage;
    if(bit_test(wram->wPlayerSubStatus5, SUBSTATUS_TOXIC)) {
    //  Player is badly poisoned.
    //  70% chance to greatly encourage this move.
    //  This would counter any previous discouragement.
    // maybe_greatly_encourage:
        // CALL(aRandom);
        // CP_A(31 percent + 1);
        // RET_C ;
        if(Random() >= 31 percent + 1) {
            // DEC_hl;
            // DEC_hl;
            *hl -= 2;
        }
        // RET;
        return;
    }

    // LD_A_addr(wPlayerSubStatus4);
    // BIT_A(SUBSTATUS_LEECH_SEED);
    // IF_NZ goto maybe_encourage;
    if(bit_test(wram->wPlayerSubStatus5, SUBSTATUS_LEECH_SEED)) {
    //  Player is seeded.
    //  50% chance to encourage this move.
    //  This would partly counter any previous discouragement.

    // maybe_encourage:
        // CALL(aAI_50_50);
        // RET_C ;

        if(AI_50_50()) {
            // DEC_hl;
            (*hl)--;
        }
        // RET;
        return;
    }

//  Discourage this move if enemy's evasion level is higher than player's accuracy level.
    // LD_A_addr(wEnemyEvaLevel);
    // LD_B_A;
    // LD_A_addr(wPlayerAccLevel);
    // CP_A_B;
    // IF_C goto discourage;
    if(wram->wEnemyEvaLevel > wram->wPlayerAccLevel) {
        // INC_hl;
        (*hl)++;
        // RET;
        return;
    }

//  Greatly encourage this move if the player is in the middle of Fury Cutter or Rollout.
    // LD_A_addr(wPlayerFuryCutterCount);
    // AND_A_A;
    // IF_NZ goto greatly_encourage;

    // LD_A_addr(wPlayerSubStatus1);
    // BIT_A(SUBSTATUS_ROLLOUT);
    // IF_NZ goto greatly_encourage;
    if(wram->wPlayerFuryCutterCount != 0 || bit_test(wram->wPlayerSubStatus1, SUBSTATUS_ROLLOUT)) {
    // greatly_encourage:
        // DEC_hl;
        // DEC_hl;
        *hl -= 2;
        return;
    }


// discourage:
    // INC_hl;
    (*hl)++;
    // RET;
    return;
}

static void AI_Smart_AlwaysHit(uint8_t* hl){
//  80% chance to greatly encourage this move if either...

//  ...enemy's accuracy level has been lowered three or more stages
    // LD_A_addr(wEnemyAccLevel);
    // CP_A(BASE_STAT_LEVEL - 2);
    // IF_C goto encourage;

//  ...or player's evasion level has been raised three or more stages.
    // LD_A_addr(wPlayerEvaLevel);
    // CP_A(BASE_STAT_LEVEL + 3);
    // RET_C ;

    
    if(wram->wEnemyAccLevel  < BASE_STAT_LEVEL - 2
    || wram->wPlayerEvaLevel > BASE_STAT_LEVEL + 2) {
    // encourage:
        // CALL(aAI_80_20);
        // RET_C ;

        if(!AI_80_20()) {
            // DEC_hl;
            // DEC_hl;
            (*hl)--;
            // RET;
        }
    }
}

static void AI_Smart_MirrorMove(uint8_t* hl){
//  If the player did not use any move last turn...
    // LD_A_addr(wLastPlayerCounterMove);
    // AND_A_A;
    // IF_NZ goto usedmove;
    if(wram->wLastPlayerCounterMove == NO_MOVE) {
    //  ...do nothing if enemy is slower than player
        // CALL(aAICompareSpeed);
        // RET_NC ;
        if(!AICompareSpeed())
            return;

    //  ...or dismiss this move if enemy is faster than player.
        // JP(mAIDiscourageMove);
        return AIDiscourageMove(hl);
    }

//  If the player did use a move last turn...

// usedmove:
    // PUSH_HL;
    // LD_HL(mUsefulMoves);
    // LD_DE(1);
    // CALL(aIsInArray);
    // POP_HL;

//  ...do nothing if he didn't use a useful move.
    // RET_NC ;
    if(!IsInMoveArray(UsefulMoves, wram->wLastPlayerCounterMove))
        return;

//  If he did, 50% chance to encourage this move...
    // CALL(aAI_50_50);
    // RET_C ;
    if(AI_50_50()) {
        // DEC_hl;
        (*hl)--;
    }

//  ...and 90% chance to encourage this move again if the enemy is faster.
    // CALL(aAICompareSpeed);
    // RET_NC ;

    // CALL(aRandom);
    // CP_A(10 percent);
    // RET_C ;
    if(AICompareSpeed() && Random() >= 10 percent) {
        // DEC_hl;
        (*hl)--;
        // RET;
        return;
    }
}

static void AI_Smart_AccuracyDown(uint8_t* hl){
//  If player's HP is full...
    // CALL(aAICheckPlayerMaxHP);
    // IF_NC goto hp_mismatch_1;

//  ...and enemy's HP is above 50%...
    // CALL(aAICheckEnemyHalfHP);
    // IF_NC goto hp_mismatch_1;

    if(AICheckPlayerMaxHP() && !AICheckEnemyHalfHP()) {
    //  ...greatly encourage this move if player is badly poisoned.
        // LD_A_addr(wPlayerSubStatus5);
        // BIT_A(SUBSTATUS_TOXIC);
        // IF_NZ goto greatly_encourage;
        if(bit_test(wram->wPlayerSubStatus5, SUBSTATUS_TOXIC)) {
            *hl -= 2;
            return;
        }

    //  ...70% chance to greatly encourage this move if player is not badly poisoned.
        // CALL(aRandom);
        // CP_A(70 percent);
        // IF_NC goto not_encouraged;
        if(Random() >= 70 percent)
            goto not_encouraged;

    // greatly_encourage:
        // DEC_hl;
        // DEC_hl;
        *hl -= 2;
        // RET;
        return;
    }

// hp_mismatch_1:

//  Greatly discourage this move if player's HP is below 25%.
    // CALL(aAICheckPlayerQuarterHP);
    // IF_NC goto hp_mismatch_2;
    if(!AICheckPlayerQuarterHP()) {
    //  If player's HP is above 25% but not full, 4% chance to greatly encourage this move.
        // CALL(aRandom);
        // CP_A(4 percent);
        // IF_C goto greatly_encourage;
        if(Random() < 4 percent) {
            *hl -= 2;
            return;
        }

    //  If player's HP is between 25% and 50%,...
        // CALL(aAICheckPlayerHalfHP);
        // IF_NC goto hp_mismatch_3;

        if(!AICheckPlayerHalfHP()) {
        //  If player's HP is above 50% but not full, 20% chance to greatly encourage this move.
            // CALL(aAI_80_20);
            // IF_C goto greatly_encourage;
            if(AI_80_20()) {
                *hl -= 2;
                return;
            }
            // goto not_encouraged;
        }
        //  ...50% chance to greatly discourage this move.
    // hp_mismatch_3:
        // CALL(aAI_50_50);
        // IF_C goto not_encouraged;
        if(AI_50_50()) {
        // hp_mismatch_2:
            // INC_hl;
            // INC_hl;
            *hl += 2;
        }
    }
    else {
    // hp_mismatch_2:
        // INC_hl;
        // INC_hl;
        *hl += 2;
    }

//  We only end up here if the move has not been already encouraged.

not_encouraged:
    // LD_A_addr(wPlayerSubStatus5);
    // BIT_A(SUBSTATUS_TOXIC);
    // IF_NZ goto maybe_greatly_encourage;
    if(bit_test(wram->wPlayerSubStatus5, SUBSTATUS_TOXIC)) {
    //  Player is badly poisoned.
    //  70% chance to greatly encourage this move.
    //  This would counter any previous discouragement.

    // maybe_greatly_encourage:
        // CALL(aRandom);
        // CP_A(31 percent + 1);
        // RET_C ;
        if(Random() >= 31 percent + 1) {
            // DEC_hl;
            // DEC_hl;
            *hl -= 2;
        }
        // RET;
        return;
    }

    // LD_A_addr(wPlayerSubStatus4);
    // BIT_A(SUBSTATUS_LEECH_SEED);
    // IF_NZ goto encourage;
    if(bit_test(wram->wPlayerSubStatus4, SUBSTATUS_LEECH_SEED)) {
    //  Player is seeded.
    //  50% chance to encourage this move.
    //  This would partly counter any previous discouragement.
    // encourage:
        // CALL(aAI_50_50);
        // RET_C ;
        if(AI_50_50()) {
            // DEC_hl;
            (*hl)--;
        }
        // RET;
        return;
    }

//  Discourage this move if enemy's evasion level is higher than player's accuracy level.
    // LD_A_addr(wEnemyEvaLevel);
    // LD_B_A;
    // LD_A_addr(wPlayerAccLevel);
    // CP_A_B;
    // IF_C goto discourage;
    if(wram->wEnemyEvaLevel > wram->wPlayerAccLevel) {
        (*hl)++;
        return;
    }

//  Greatly encourage this move if the player is in the middle of Fury Cutter or Rollout.
    // LD_A_addr(wPlayerFuryCutterCount);
    // AND_A_A;
    // IF_NZ goto greatly_encourage;

    // LD_A_addr(wPlayerSubStatus1);
    // BIT_A(SUBSTATUS_ROLLOUT);
    // IF_NZ goto greatly_encourage;
    if(wram->wPlayerFuryCutterCount != 0
    || bit_test(wram->wPlayerSubStatus1, SUBSTATUS_ROLLOUT)) {
        *hl -= 2;
        return;
    }

// discourage:
    // INC_hl;
    (*hl)++;
    // RET;
}

//  85% chance to encourage this move if any of enemy's stat levels is lower than -2.
static void AI_Smart_ResetStats(uint8_t* hl){
    // PUSH_HL;
    // LD_HL(wEnemyAtkLevel);
    // LD_C(NUM_LEVEL_STATS);

    for(uint8_t i = 0; i < NUM_LEVEL_STATS; ++i) {
    // enemystatsloop:
        // DEC_C;
        // IF_Z goto enemystatsdone;
        // LD_A_hli;
        // CP_A(BASE_STAT_LEVEL - 2);
        // IF_C goto encourage;
        if(wram->wEnemyStatLevels[i] < BASE_STAT_LEVEL - 2) {
        // encourage:
            // POP_HL;
            // CALL(aRandom);
            // CP_A(16 percent);
            // RET_C ;
            if(Random() >= 16 percent) {
                // DEC_hl;
                (*hl)--;
            }
            // RET;
            return;
        }
        // goto enemystatsloop;
    }

//  85% chance to encourage this move if any of player's stat levels is higher than +2.

// enemystatsdone:
    // LD_HL(wPlayerAtkLevel);
    // LD_C(NUM_LEVEL_STATS);

    for(uint8_t i = 0; i < NUM_LEVEL_STATS; ++i) {
    // playerstatsloop:
        // DEC_C;
        // IF_Z goto discourage;
        // LD_A_hli;
        // CP_A(BASE_STAT_LEVEL + 3);
        // IF_C goto playerstatsloop;
        if(wram->wEnemyStatLevels[i] >= BASE_STAT_LEVEL + 3) {
        // encourage:
            // POP_HL;
            // CALL(aRandom);
            // CP_A(16 percent);
            // RET_C ;
            if(Random() >= 16 percent) {
                // DEC_hl;
                (*hl)--;
            }
            // RET;
            return;
        }
    }

// encourage:
    // POP_HL;
    // CALL(aRandom);
    // CP_A(16 percent);
    // RET_C ;
    // DEC_hl;
    // RET;

//  Discourage this move if neither:
//  Any of enemy's stat levels is    lower than -2.
//  Any of player's stat levels is higher than +2.

// discourage:
    // POP_HL;
    // INC_hl;
    (*hl)++;
    // RET;
}

//  90% chance to discourage this move unless enemy's HP is full.
static void AI_Smart_Bide(uint8_t* hl){
    // CALL(aAICheckEnemyMaxHP);
    // RET_C ;
    if(AICheckEnemyMaxHP())
        return;
    // CALL(aRandom);
    // CP_A(10 percent);
    // RET_C ;
    if(Random() >= 10 percent) {
        // INC_hl;
        (*hl)++;
    }
    // RET;
}

//  Whirlwind, Roar.
static void AI_Smart_ForceSwitch(uint8_t* hl){
//  Discourage this move if the player has not shown
//  a super-effective move against the enemy.
//  Consider player's type(s) if its moves are unknown.

    // PUSH_HL;
    // CALLFAR(aCheckPlayerMoveTypeMatchups);
    uint8_t score = CheckPlayerMoveTypeMatchups();
    // LD_A_addr(wEnemyAISwitchScore);
    // CP_A(BASE_AI_SWITCH_SCORE);
    // POP_HL;
    // RET_C ;
    if(score >= BASE_AI_SWITCH_SCORE) {
        // INC_hl;
        (*hl)++;
    }
    // RET;
}

static void AI_Smart_Heal(uint8_t* hl){
    return AI_Smart_MorningSun(hl);
}

static void AI_Smart_MorningSun(uint8_t* hl){
    return AI_Smart_Synthesis(hl);
}

static void AI_Smart_Synthesis(uint8_t* hl){
    return AI_Smart_Moonlight(hl);
}

//  90% chance to greatly encourage this move if enemy's HP is below 25%.
//  Discourage this move if enemy's HP is higher than 50%.
//  Do nothing otherwise.
static void AI_Smart_Moonlight(uint8_t* hl){
    // CALL(aAICheckEnemyQuarterHP);
    // IF_NC goto encourage;
    if(AICheckEnemyQuarterHP()) {
        // CALL(aAICheckEnemyHalfHP);
        // RET_NC ;
        if(AICheckEnemyHalfHP()) {
            // INC_hl;
            (*hl)++;
            // RET;
        }
        return;
    }

// encourage:
    // CALL(aRandom);
    // CP_A(10 percent);
    // RET_C ;
    if(Random() >= 10 percent) {
        // DEC_hl;
        // DEC_hl;
        (*hl) -= 2;
    }
    // RET;
}

static void AI_Smart_Toxic(uint8_t* hl){
    return AI_Smart_LeechSeed(hl);
}

//  Discourage this move if player's HP is below 50%.
static void AI_Smart_LeechSeed(uint8_t* hl){
    // CALL(aAICheckPlayerHalfHP);
    // RET_C ;
    if(AICheckPlayerHalfHP()) {
        // INC_hl;
        (*hl)++;
    }
    // RET;
}

static void AI_Smart_LightScreen(uint8_t* hl){
    return AI_Smart_Reflect(hl);
}

//  Over 90% chance to discourage this move unless enemy's HP is full.
static void AI_Smart_Reflect(uint8_t* hl){
    // CALL(aAICheckEnemyMaxHP);
    // RET_C ;
    if(!AICheckEnemyMaxHP() && Random() >= 8 percent) {
        // CALL(aRandom);
        // CP_A(8 percent);
        // RET_C ;
        // INC_hl;
        (*hl)++;
        // RET;
    }
}

//  Dismiss this move if player's level is higher than enemy's level.
//  Else, discourage this move is player's HP is below 50%.
static void AI_Smart_Ohko(uint8_t* hl){
    // LD_A_addr(wBattleMonLevel);
    // LD_B_A;
    // LD_A_addr(wEnemyMonLevel);
    // CP_A_B;
    // JP_C (mAIDiscourageMove);
    if(wram->wEnemyMon.level < wram->wBattleMon.level)
        return AIDiscourageMove(hl);
    // CALL(aAICheckPlayerHalfHP);
    // RET_C ;
    if(AICheckPlayerHalfHP()) {
        // INC_hl;
        (*hl)++;
        // RET;
    }
}

//  Bind, Wrap, Fire Spin, Clamp
static void AI_Smart_TrapTarget(uint8_t* hl){
//  50% chance to discourage this move if the player is already trapped.
    // LD_A_addr(wPlayerWrapCount);
    // AND_A_A;
    // IF_NZ goto discourage;
    if(wram->wPlayerWrapCount == 0) {
    //  50% chance to greatly encourage this move if player is either
    //  badly poisoned, in love, identified, stuck in Rollout, or has a Nightmare.
        // LD_A_addr(wPlayerSubStatus5);
        // BIT_A(SUBSTATUS_TOXIC);
        // IF_NZ goto encourage;

        // LD_A_addr(wPlayerSubStatus1);
        // AND_A(1 << SUBSTATUS_IN_LOVE | 1 << SUBSTATUS_ROLLOUT | 1 << SUBSTATUS_IDENTIFIED | 1 << SUBSTATUS_NIGHTMARE);
        // IF_NZ goto encourage;

    //  Else, 50% chance to greatly encourage this move if it's the player's Pokemon first turn.
        // LD_A_addr(wPlayerTurnsTaken);
        // AND_A_A;
        // IF_Z goto encourage;
        if(bit_test(wram->wPlayerSubStatus5, SUBSTATUS_TOXIC)
        || (wram->wPlayerSubStatus1 & (1 << SUBSTATUS_IN_LOVE | 1 << SUBSTATUS_ROLLOUT | 1 << SUBSTATUS_IDENTIFIED | 1 << SUBSTATUS_NIGHTMARE))
        || wram->wPlayerTurnsTaken == 0) {
        // encourage:
            // CALL(aAICheckEnemyQuarterHP);
            // RET_NC ;
            if(!AICheckEnemyQuarterHP() && AI_50_50()) {
                // CALL(aAI_50_50);
                // RET_C ;
                // DEC_hl;
                // DEC_hl;
                *hl -= 2;
                // RET;
            }
            return;
        }
    }
//  50% chance to discourage this move otherwise.

// discourage:
    // CALL(aAI_50_50);
    // RET_C ;
    if(AI_50_50()) {
        // INC_hl;
        (*hl)++;
    }
    // RET;
}

// razor wind
static void AI_Smart_RazorWind(uint8_t* hl){
    // LD_A_addr(wEnemySubStatus1);
    // BIT_A(SUBSTATUS_PERISH);
    // IF_Z goto no_perish_count;

    // LD_A_addr(wEnemyPerishCount);
    // CP_A(3);
    // IF_C goto discourage;
    if(bit_test(wram->wEnemySubStatus1, SUBSTATUS_PERISH)
    && wram->wEnemyPerishCount < 3) {
        (*hl)++;
        return;
    }

// no_perish_count:
    // PUSH_HL;
    // LD_HL(wPlayerUsedMoves);
    // LD_C(NUM_MOVES);

    for(uint8_t i = 0; i < NUM_MOVES; ++i) {
    // checkmove:
        // LD_A_hli;
        move_t a = wram->wPlayerUsedMoves[i];
        // AND_A_A;
        // IF_Z goto movesdone;
        if(a == NO_MOVE)
            break;

        // CALL(aAIGetEnemyMove);
        const struct Move* mv = AIGetEnemyMove(a);

        // LD_A_addr(wEnemyMoveStruct + MOVE_EFFECT);
        // CP_A(EFFECT_PROTECT);
        // IF_Z goto dismiss;
        if(mv->effect == EFFECT_PROTECT) {
        // dismiss:
            // POP_HL;
            // LD_A_hl;
            // ADD_A(6);
            // LD_hl_A;
            *hl += 6;
            // RET;
            return;
        }
        // DEC_C;
        // IF_NZ goto checkmove;
    }

// movesdone:
    // POP_HL;
    // LD_A_addr(wEnemySubStatus3);
    // BIT_A(SUBSTATUS_CONFUSED);
    // IF_NZ goto maybe_discourage;

    // CALL(aAICheckEnemyHalfHP);
    // RET_C ;

    if(bit_test(wram->wEnemySubStatus3, SUBSTATUS_CONFUSED) || AICheckEnemyHalfHP()) {
    // maybe_discourage:
        // CALL(aRandom);
        // CP_A(79 percent - 1);
        // RET_C ;
        if(Random() >= 79 percent - 1) {
        // discourage:
            // INC_hl;
            (*hl)++;
            // RET;
        }
    }
}

static void AI_Smart_Confuse(uint8_t* hl){
//  90% chance to discourage this move if player's HP is between 25% and 50%.
    // CALL(aAICheckPlayerHalfHP);
    // RET_C ;
    if(!AICheckPlayerHalfHP())
        return;
    // CALL(aRandom);
    // CP_A(10 percent);
    // IF_C goto skipdiscourage;
    if(Random() < 10 percent) {
    // skipdiscourage:
    //  Discourage again if player's HP is below 25%.
        // CALL(aAICheckPlayerQuarterHP);
        // RET_C ;
        if(AICheckPlayerQuarterHP()) {
            // INC_hl;
            (*hl)++;
            // RET;
        }
    }
    // INC_hl;
}

static void AI_Smart_SpDefenseUp2(uint8_t* hl){
//  Discourage this move if enemy's HP is lower than 50%.
    // CALL(aAICheckEnemyHalfHP);
    // IF_NC goto discourage;

//  Discourage this move if enemy's special defense level is higher than +3.
    // LD_A_addr(wEnemySDefLevel);
    // CP_A(BASE_STAT_LEVEL + 4);
    // IF_NC goto discourage;
    if(AICheckEnemyHalfHP()
    || wram->wEnemySDefLevel > BASE_STAT_LEVEL + 3) {
    // discourage:
        // INC_hl;
        (*hl)++;
        // RET;
        return;
    }

//  80% chance to greatly encourage this move if
//  enemy's Special Defense level is lower than +2, and the player is of a special type.
    // CP_A(BASE_STAT_LEVEL + 2);
    // RET_NC ;
    if(wram->wEnemySDefLevel >= BASE_STAT_LEVEL + 2)
        return;

    // LD_A_addr(wBattleMonType1);
    // CP_A(SPECIAL);
    // IF_NC goto encourage;
    // LD_A_addr(wBattleMonType2);
    // CP_A(SPECIAL);
    // RET_C ;
    if(wram->wBattleMon.type1 >= SPECIAL
    || wram->wBattleMon.type2 >= SPECIAL) {
    // encourage:
        // CALL(aAI_80_20);
        // RET_C ;
        if(!AI_80_20()) {
            // DEC_hl;
            // DEC_hl;
            *hl -= 2;
        }
        // RET;
        return;
    }
}

//  Fly, Dig
static void AI_Smart_Fly(uint8_t* hl){
//  Greatly encourage this move if the player is
//  flying or underground, and slower than the enemy.

    // LD_A_addr(wPlayerSubStatus3);
    // AND_A(1 << SUBSTATUS_FLYING | 1 << SUBSTATUS_UNDERGROUND);
    // RET_Z ;
    if((wram->wPlayerSubStatus3 & (1 << SUBSTATUS_FLYING | 1 << SUBSTATUS_UNDERGROUND)) == 0)
        return;

    // CALL(aAICompareSpeed);
    // RET_NC ;
    if(AICompareSpeed()) {
        // DEC_hl;
        // DEC_hl;
        // DEC_hl;
        (*hl) -= 3;
    }
    // RET;
}

static void AI_Smart_SuperFang(uint8_t* hl){
//  Discourage this move if player's HP is below 25%.
    // CALL(aAICheckPlayerQuarterHP);
    // RET_C ;
    if(AICheckPlayerQuarterHP()) {
        // INC_hl;
        (*hl)++;
        // RET;
    }
}

static void AI_Smart_Paralyze(uint8_t* hl){
//  50% chance to discourage this move if player's HP is below 25%.
    // CALL(aAICheckPlayerQuarterHP);
    // IF_NC goto discourage;
    if(AICheckPlayerQuarterHP()) {
    // discourage:
        // CALL(aAI_50_50);
        // RET_C ;
        if(AI_50_50())
            return;
        // INC_hl;
        (*hl)++;
        // RET;
        return;
    }

//  80% chance to greatly encourage this move
//  if enemy is slower than player and its HP is above 25%.
    // CALL(aAICompareSpeed);
    // RET_C ;
    // CALL(aAICheckEnemyQuarterHP);
    // RET_NC ;
    // CALL(aAI_80_20);
    // RET_C ;
    if(!AICompareSpeed() && !AICheckEnemyQuarterHP() && !AI_80_20()) {
        // DEC_hl;
        // DEC_hl;
        *hl -= 2;
    }
    // RET;
}

//  Icy Wind
static void AI_Smart_SpeedDownHit(uint8_t* hl){
//  Almost 90% chance to greatly encourage this move if the following conditions all meet:
//  Enemy's HP is higher than 25%.
//  It's the first turn of player's Pokemon.
//  Player is faster than enemy.

    // LD_A_addr(wEnemyMoveStruct + MOVE_ANIM);
    // CP_A(ICY_WIND);
    // RET_NZ ;
    if(wram->wEnemyMoveStruct.animation != ICY_WIND)
        return;
    // CALL(aAICheckEnemyQuarterHP);
    // RET_NC ;
    // LD_A_addr(wPlayerTurnsTaken);
    // AND_A_A;
    // RET_NZ ;
    // CALL(aAICompareSpeed);
    // RET_C ;
    // CALL(aRandom);
    // CP_A(12 percent);
    // RET_C ;
    if(!AICheckEnemyQuarterHP()
    && wram->wPlayerTurnsTaken == 0
    && !AICompareSpeed()
    && Random() >= 12 percent - 1) {
        // DEC_hl;
        // DEC_hl;
        *hl -= 2;
    }
    // RET;
}

//  Dismiss this move if enemy's HP is below 50%.
static void AI_Smart_Substitute(uint8_t* hl){
    // CALL(aAICheckEnemyHalfHP);
    // RET_C ;
    // JP(mAIDiscourageMove);
    if(AICheckEnemyHalfHP())
        return AIDiscourageMove(hl);
}

static void AI_Smart_HyperBeam(uint8_t* hl){
    // CALL(aAICheckEnemyHalfHP);
    // IF_C goto discourage;
    if(!AICheckEnemyHalfHP()) {
    // discourage:
    //  If enemy's HP is above 50%, discourage this move at random
        // CALL(aRandom);
        // CP_A(16 percent);
        // RET_C ;
        if(Random() < 16 percent)
            return;
        // INC_hl;
        (*hl)++;
        // CALL(aAI_50_50);
        // RET_C ;
        if(Random() < AI_50_50())
            return;
        // INC_hl;
        (*hl)++;
        // RET;
        return;
    }

//  50% chance to encourage this move if enemy's HP is below 25%.
    // CALL(aAICheckEnemyQuarterHP);
    // RET_C ;
    // CALL(aAI_50_50);
    // RET_C ;
    if(AICheckEnemyQuarterHP() && AI_50_50()) {
        // DEC_hl;
        (*hl)--;
    }
    // RET;
}

static void AI_Smart_Rage(uint8_t* hl){
    // LD_A_addr(wEnemySubStatus4);
    // BIT_A(SUBSTATUS_RAGE);
    // IF_Z goto notbuilding;
    if(bit_test(wram->wEnemySubStatus4, SUBSTATUS_RAGE)) {
    //  If enemy's Rage is building, 50% chance to encourage this move.
        // CALL(aAI_50_50);
        // IF_C goto skipencourage;
        if(AI_50_50()) {
            // DEC_hl;
            (*hl)--;
        }

    //  Encourage this move based on Rage's counter.

    // skipencourage:
        // LD_A_addr(wEnemyRageCounter);
        // CP_A(2);
        // RET_C ;
        if(wram->wEnemyRageCounter < 2)
            return;
        // DEC_hl;
        (*hl)--;
        // LD_A_addr(wEnemyRageCounter);
        // CP_A(3);
        // RET_C ;
        if(wram->wEnemyRageCounter < 3)
            return;
        // DEC_hl;
        (*hl)--;
        // RET;
        return;
    }

// notbuilding:
//  If enemy's Rage is not building, discourage this move if enemy's HP is below 50%.
    // CALL(aAICheckEnemyHalfHP);
    // IF_NC goto discourage;
    if(AICheckEnemyHalfHP()) {
    // discourage:
        // INC_hl;
        (*hl)++;
        // RET;
        return;
    }
//  50% chance to encourage this move otherwise.
    // CALL(aAI_80_20);
    // RET_NC ;
    if(AI_80_20()) {
        // DEC_hl;
        (*hl)--;
    }
    // RET;
}

static void AI_Smart_Mimic(uint8_t* hl){
//  Discourage this move if the player did not use any move last turn.
    // LD_A_addr(wLastPlayerCounterMove);
    // AND_A_A;
    // IF_Z goto dismiss;
    if(wram->wLastPlayerCounterMove == NO_MOVE) {
    // dismiss:
    //  Dismiss this move if the enemy is faster than the player.
        // CALL(aAICompareSpeed);
        // JP_C (mAIDiscourageMove);
        if(AICompareSpeed())
            return AIDiscourageMove(hl);
        (*hl)++;
        return;
    }

    // CALL(aAICheckEnemyHalfHP);
    // IF_NC goto discourage;
    if(AICheckEnemyHalfHP()) {
        (*hl)++;
        return;
    }

    // PUSH_HL;
    // LD_A_addr(wLastPlayerCounterMove);
    // CALL(aAIGetEnemyMove);
    AIGetEnemyMove(wram->wLastPlayerCounterMove);

    // LD_A(1);
    // LDH_addr_A(hBattleTurn);
    hram.hBattleTurn = TURN_ENEMY;
    // CALLFAR(aBattleCheckTypeMatchup);
    uint8_t matchup = BattleCheckTypeMatchup();

    // LD_A_addr(wTypeMatchup);
    // CP_A(EFFECTIVE);
    // POP_HL;
    // IF_C goto discourage;
    if(matchup < EFFECTIVE) {
        (*hl)++;
        return;
    }
    // IF_Z goto skip_encourage;
    else if(matchup == EFFECTIVE) {}
    // CALL(aAI_50_50);
    // IF_C goto skip_encourage;
    else if(AI_50_50()) {
        // DEC_hl;
        (*hl)--;
    }

// skip_encourage:
    // LD_A_addr(wLastPlayerCounterMove);
    // PUSH_HL;
    // LD_HL(mUsefulMoves);
    // LD_DE(1);
    // CALL(aIsInArray);

    // POP_HL;
    // RET_NC ;
    if(IsInMoveArray(UsefulMoves, wram->wLastPlayerCounterMove) && AI_50_50()) {
        // CALL(aAI_50_50);
        // RET_C ;
        // DEC_hl;
        (*hl)--;
        // RET;
    }
    return;


// dismiss:
//  Dismiss this move if the enemy is faster than the player.
    // CALL(aAICompareSpeed);
    // JP_C (mAIDiscourageMove);

// discourage:
    // INC_hl;
    // RET;
}

static void AI_Smart_Counter(uint8_t* hl){
    // PUSH_HL;
    // LD_HL(wPlayerUsedMoves);
    // LD_C(NUM_MOVES);
    // LD_B(0);
    uint8_t b = 0;
    for(uint8_t i = 0; i < NUM_MOVES; ++i) {
    // playermoveloop:
        // LD_A_hli;
        move_t a = wram->wPlayerUsedMoves[i];
        // AND_A_A;
        // IF_Z goto skipmove;
        if(a == NO_MOVE)
            continue;

        // CALL(aAIGetEnemyMove);
        const struct Move* mv = AIGetEnemyMove(a);

        // LD_A_addr(wEnemyMoveStruct + MOVE_POWER);
        // AND_A_A;
        // IF_Z goto skipmove;

        // LD_A_addr(wEnemyMoveStruct + MOVE_TYPE);
        // CP_A(SPECIAL);
        // IF_NC goto skipmove;
        if(mv->power == 0 || mv->type >= SPECIAL)
            continue;

        // INC_B;
        ++b;


    // skipmove:
        // DEC_C;
        // IF_NZ goto playermoveloop;
    }

    // POP_HL;
    // LD_A_B;
    // AND_A_A;
    // IF_Z goto discourage;
    if(b == 0) {
    // discourage:
        // INC_hl;
        (*hl)++;
        // RET;
        return;
    }

    // CP_A(3);
    // IF_NC goto encourage;

    if(b < 3) {
        // LD_A_addr(wLastPlayerCounterMove);
        // AND_A_A;
        // IF_Z goto done;
        if(wram->wLastPlayerCounterMove == NO_MOVE)
            return;

        // CALL(aAIGetEnemyMove);
        const struct Move* mv = AIGetEnemyMove(wram->wLastPlayerCounterMove);

        // LD_A_addr(wEnemyMoveStruct + MOVE_POWER);
        // AND_A_A;
        // IF_Z goto done;

        // LD_A_addr(wEnemyMoveStruct + MOVE_TYPE);
        // CP_A(SPECIAL);
        // IF_NC goto done;
        if(mv->power == 0 || mv->type >= SPECIAL)
            return;
    }

// encourage:
    // CALL(aRandom);
    // CP_A(39 percent + 1);
    // IF_C goto done;
    if(Random() >= 39 percent + 1) {
        // DEC_hl;
        (*hl)--;
        return;
    }

// done:
    // RET;
}

static void AI_Smart_Encore(uint8_t* hl){
    // CALL(aAICompareSpeed);
    // IF_NC goto discourage;
    if(!AICompareSpeed()) {
    // discourage:
        // INC_hl;
        // INC_hl;
        // INC_hl;
        *hl += 3;
        // RET;
        return;
    }

    // LD_A_addr(wLastPlayerMove);
    // AND_A_A;
    // JP_Z (mAIDiscourageMove);
    if(wram->wLastPlayerMove == NO_MOVE)
        return AIDiscourageMove(hl);

    // CALL(aAIGetEnemyMove);
    const struct Move* mv = AIGetEnemyMove(wram->wLastPlayerMove);

    // LD_A_addr(wEnemyMoveStruct + MOVE_POWER);
    // AND_A_A;
    // IF_Z goto weakmove;

    // PUSH_HL;
    // LD_A_addr(wEnemyMoveStruct + MOVE_TYPE);
    // LD_HL(wEnemyMonType1);
    // PREDEF(pCheckTypeMatchup);

    // POP_HL;
    // LD_A_addr(wTypeMatchup);
    // CP_A(EFFECTIVE);
    // IF_NC goto weakmove;
    uint8_t matchup;
    if(mv->power == 0
    || (matchup = CheckTypeMatchup(mv->type, wram->wEnemyMon.types), matchup >= EFFECTIVE)) {
    // weakmove:
        // PUSH_HL;
        // LD_A_addr(wLastPlayerCounterMove);
        // LD_HL(mEncoreMoves);
        // LD_DE(1);
        // CALL(aIsInArray);
        // POP_HL;
        // IF_NC goto discourage;
        if(!IsInMoveArray(EncoreMoves, wram->wLastPlayerCounterMove)) {
        // discourage:
            // INC_hl;
            // INC_hl;
            // INC_hl;
            *hl += 3;
            // RET;
            return;
        }
    }
    else {
        // AND_A_A;
        // RET_NZ ;
        if(matchup != 0)
            return;
        // goto encourage;
    }

// encourage:
    // CALL(aRandom);
    // CP_A(28 percent - 1);
    // RET_C ;
    if(Random() >= 28 percent - 1) {
        // DEC_hl;
        // DEC_hl;
        *hl -= 2;
    }
    // RET;


// discourage:
    // INC_hl;
    // INC_hl;
    // INC_hl;
    // RET;

// INCLUDE "data/battle/ai/encore_moves.asm"
}

//  Discourage this move if [enemy's current HP * 2 > player's current HP].
static void AI_Smart_PainSplit(uint8_t* hl){
    // PUSH_HL;
    // LD_HL(wEnemyMonHP);
    // LD_B_hl;
    // INC_HL;
    // LD_C_hl;
    uint16_t enmy_hp = BigEndianToNative16(wram->wEnemyMon.hp);
    uint16_t plyr_hp = BigEndianToNative16(wram->wBattleMon.hp);
    // SLA_C;
    // RL_B;
    // LD_HL(wBattleMonHP + 1);
    // LD_A_hld;
    // CP_A_C;
    // LD_A_hl;
    // SBC_A_B;
    // POP_HL;
    // RET_NC ;
    if(enmy_hp * 2 > plyr_hp) {
        // INC_hl;
        ++(*hl);
    }
    // RET;
}

static void AI_Smart_Snore(uint8_t* hl){
    return AI_Smart_SleepTalk(hl);
}

static void AI_Smart_SleepTalk(uint8_t* hl){
//  Greatly encourage this move if enemy is fast asleep.
//  Greatly discourage this move otherwise.

    // LD_A_addr(wEnemyMonStatus);
    // AND_A(SLP);
    // CP_A(1);
    // IF_Z goto discourage;
    if((wram->wEnemyMon.status[0] & SLP) != 1) {
    // discourage:
        // INC_hl;
        // INC_hl;
        // INC_hl;
        *hl += 3;
        // RET;
        return;
    }
    else {
        // DEC_hl;
        // DEC_hl;
        // DEC_hl;
        *hl -= 3;
        // RET;
    }
}

//  Greatly encourage this move if enemy is frozen.
//  No move has EFFECT_DEFROST_OPPONENT, so this layer is unused.
static void AI_Smart_DefrostOpponent(uint8_t* hl){
    // LD_A_addr(wEnemyMonStatus);
    // AND_A(1 << FRZ);
    // RET_Z ;
    if((wram->wEnemyMon.status[0] & (1 << FRZ)) == 0)
        return;
    // DEC_hl;
    // DEC_hl;
    // DEC_hl;
    (*hl) -= 3;
    // RET;
}

static void AI_Smart_Spite(uint8_t* hl){
    // LD_A_addr(wLastPlayerCounterMove);
    // AND_A_A;
    // IF_NZ goto usedmove;
    if(wram->wLastPlayerCounterMove == NO_MOVE) {
        // CALL(aAICompareSpeed);
        // JP_C (mAIDiscourageMove);
        if(AICompareSpeed())
            return AIDiscourageMove(hl);
        // CALL(aAI_50_50);
        // RET_C ;
        if(AI_50_50()) {
            // INC_hl;
            (*hl)++;
        }
        // RET;
        return;
    }

// usedmove:
    // PUSH_HL;
    // LD_B_A;
    move_t b = wram->wLastPlayerCounterMove;
    // LD_C(NUM_MOVES);
    // LD_HL(wBattleMonMoves);
    move_t* mvs = wram->wBattleMon.moves;
    // LD_DE(wBattleMonPP);
    uint8_t* pp = wram->wBattleMon.pp;

    for(uint8_t i = 0; i < NUM_MOVES; ++i) {
    // moveloop:
        // LD_A_hli;
        // CP_A_B;
        // IF_Z goto foundmove;
        if(mvs[i] == b) {
        // foundmove:
            // POP_HL;
            // LD_A_de;
            // CP_A(6);
            // IF_C goto encourage;
            if(pp[i] < 6) {
            // encourage:
                // CALL(aRandom);
                // CP_A(39 percent + 1);
                // RET_C ;
                if(Random() >= 39 percent + 1) {
                    // DEC_hl;
                    // DEC_hl;
                    *hl -= 2;
                }
                // RET;
                return;
            }
            // CP_A(15);
            // IF_NC goto discourage;

            // CALL(aRandom);
            // CP_A(39 percent + 1);
            // RET_NC ;
            if(pp[i] < 15 && Random() >= 39 percent + 1)
                return;

        // discourage:
            // INC_hl;
            (*hl)++;
            // RET;
            return;
        }

        // INC_DE;
        // DEC_C;
        // IF_NZ goto moveloop;
    }

    // POP_HL;
    // RET;
    return;


// dismiss:
//   //  unreferenced
    // JP(mAIDiscourageMove);
}

static void AI_Smart_DestinyBond(uint8_t* hl){
    return AI_Smart_Reversal(hl);
}

static void AI_Smart_Reversal(uint8_t* hl){
    return AI_Smart_SkullBash(hl);
}

//  Discourage this move if enemy's HP is above 25%.
static void AI_Smart_SkullBash(uint8_t* hl){
    // CALL(aAICheckEnemyQuarterHP);
    // RET_NC ;
    if(AICheckEnemyQuarterHP()) {
        // INC_hl;
        (*hl)++;
    }
    // RET;

}

static void AI_Smart_HealBell(uint8_t* hl){
//  Dismiss this move if none of the opponent's Pokemon is statused.
//  Encourage this move if the enemy is statused.
//  50% chance to greatly encourage this move if the enemy is fast asleep or frozen.

    // PUSH_HL;
    // LD_A_addr(wOTPartyCount);
    // LD_B_A;
    const uint8_t b = wram->wOTPartyCount;
    // LD_C(0);
    uint8_t c = 0;
    // LD_HL(wOTPartyMon1HP);
    struct PartyMon* mon = wram->wOTPartyMon;
    // LD_DE(PARTYMON_STRUCT_LENGTH);

    for(uint8_t i = 0; i < b; ++i) {
    // loop:
        // PUSH_HL;
        // LD_A_hli;
        // OR_A_hl;
        // IF_Z goto next;
        if(mon[i].HP == 0)
            continue;

    // status
        // DEC_HL;
        // DEC_HL;
        // DEC_HL;
        // LD_A_hl;
        // OR_A_C;
        // LD_C_A;
        c |= mon[i].status;

    // next:
        // POP_HL;
        // ADD_HL_DE;
        // DEC_B;
        // IF_NZ goto loop;
    }

    // POP_HL;
    // LD_A_C;
    // AND_A_A;
    // IF_Z goto no_status;
    if(c != 0) {
        // LD_A_addr(wEnemyMonStatus);
        // AND_A_A;
        // IF_Z goto ok;
        if(wram->wEnemyMon.status[0] != 0) {
            // DEC_hl;
            (*hl)--;
        }

    // ok:
        // AND_A(1 << FRZ | SLP);
        // RET_Z ;
        // CALL(aAI_50_50);
        // RET_C ;
        if((wram->wEnemyMon.status[0] & ((1 << FRZ) | SLP))
        && AI_50_50()) {
            // DEC_hl;
            // DEC_hl;
            *hl -= 2;
        }
        // RET;
        return;
    }
    else {
    // no_status:
        // LD_A_addr(wEnemyMonStatus);
        // AND_A_A;
        // RET_NZ ;
        if(wram->wEnemyMon.status[0] == 0)
            return AIDiscourageMove(hl);
        // JP(mAIDiscourageMove);
    }
}

static void AI_Smart_PriorityHit(uint8_t* hl){
    // CALL(aAICompareSpeed);
    // RET_C ;
    if(AICompareSpeed())
        return;

//  Dismiss this move if the player is flying or underground.
    // LD_A_addr(wPlayerSubStatus3);
    // AND_A(1 << SUBSTATUS_FLYING | 1 << SUBSTATUS_UNDERGROUND);
    // JP_NZ (mAIDiscourageMove);
    if(wram->wPlayerSubStatus3 & ((1 << SUBSTATUS_FLYING) | (1 << SUBSTATUS_UNDERGROUND)))
        return AIDiscourageMove(hl);

//  Greatly encourage this move if it will KO the player.
    // LD_A(1);
    // LDH_addr_A(hBattleTurn);
    hram.hBattleTurn = TURN_ENEMY;
    // PUSH_HL;
    // CALLFAR(aEnemyAttackDamage);
    EnemyAttackDamage(&gBattleCmdState);
    // CALLFAR(aBattleCommand_DamageCalc);
    BattleCommand_DamageCalc();
    // CALLFAR(aBattleCommand_Stab);
    BattleCommand_Stab();
    // POP_HL;
    // LD_A_addr(wCurDamage + 1);
    // LD_C_A;
    // LD_A_addr(wCurDamage);
    // LD_B_A;
    uint16_t bc = BigEndianToNative16(wram->wCurDamage);
    // LD_A_addr(wBattleMonHP + 1);
    // CP_A_C;
    // LD_A_addr(wBattleMonHP);
    // SBC_A_B;
    uint16_t hp = BigEndianToNative16(wram->wBattleMon.hp);

    // RET_NC ;
    if(hp < bc) {
        // DEC_hl;
        // DEC_hl;
        // DEC_hl;
        *hl -= 3;
    }
    // RET;
    return;
}

static void AI_Smart_Thief(uint8_t* hl){
//  Don't use Thief unless it's the only move available.

    // LD_A_hl;
    // ADD_A(0x1e);
    // LD_hl_A;
    *hl += 0x1e;
    // RET;
}

static void AI_Smart_Conversion2(uint8_t* hl){
    // LD_A_addr(wLastPlayerMove);
    // AND_A_A;
    // IF_NZ goto discourage;  // should be jr z
#if BUGFIX_CONVERSION2
    if(wram->wLastPlayerMove == NO_MOVE)
#else
    if(wram->wLastPlayerMove != NO_MOVE)
#endif
    {
    // discourage:
        // CALL(aRandom);
        // CP_A(10 percent);
        // RET_C ;
        if(Random() >= 10 percent) {
            // INC_hl;
            (*hl)++;
        }
        // RET;
        return;
    }

    // PUSH_HL;
    // DEC_A;
    // LD_HL(mMoves + MOVE_TYPE);
    // LD_BC(MOVE_LENGTH);
    // CALL(aAddNTimes);

    // LD_A(BANK(aMoves));
    // CALL(aGetFarByte);
    // LD_addr_A(wPlayerMoveStruct + MOVE_TYPE);
    wram->wPlayerMoveStruct.type = Moves[wram->wLastPlayerMove].type;

    // XOR_A_A;
    // LDH_addr_A(hBattleTurn);
    hram.hBattleTurn = TURN_PLAYER;

    // CALLFAR(aBattleCheckTypeMatchup);
    uint8_t matchup = BattleCheckTypeMatchup();

    // LD_A_addr(wTypeMatchup);
    // CP_A(EFFECTIVE);
    // POP_HL;
    // IF_C goto discourage;
    if(matchup < EFFECTIVE) {
    // discourage:
        // CALL(aRandom);
        // CP_A(10 percent);
        // RET_C ;
        if(Random() >= 10 percent) {
            // INC_hl;
            (*hl)++;
        }
        // RET;
        return;
    }
    // RET_Z ;
    else if(matchup == EFFECTIVE)
        return;

    else {
        // CALL(aAI_50_50);
        // RET_C ;
        if(AI_50_50()) {
            // DEC_hl;
            (*hl)--;
        }
        // RET;
        return;
    }

// discourage:
    // CALL(aRandom);
    // CP_A(10 percent);
    // RET_C ;
    // INC_hl;
    // RET;
}

static void AI_Smart_Disable(uint8_t* hl){
    // CALL(aAICompareSpeed);
    // IF_NC goto discourage;

    if(AICompareSpeed()) {
        // PUSH_HL;
        // LD_A_addr(wLastPlayerCounterMove);
        // LD_HL(mUsefulMoves);
        // LD_DE(1);
        // CALL(aIsInArray);

        // POP_HL;
        // IF_NC goto notencourage;
        if(IsInMoveArray(UsefulMoves, wram->wLastPlayerCounterMove)) {
            // CALL(aRandom);
            // CP_A(39 percent + 1);
            // RET_C ;
            // DEC_hl;
            if(Random() >= 39 percent + 1)
                --(*hl);
            // RET;
            return;
        }

    // notencourage:
        // LD_A_addr(wEnemyMoveStruct + MOVE_POWER);
        // AND_A_A;
        // RET_NZ ;
        if(wram->wEnemyMoveStruct.power != 0)
            return;
    }

// discourage:
    // CALL(aRandom);
    // CP_A(8 percent);
    // RET_C ;
    if(Random() >= 8 percent) {
        // INC_hl;
        (*hl)++;
        // RET;
    }
}

static void AI_Smart_MeanLook(uint8_t* hl){
    // CALL(aAICheckEnemyHalfHP);
    // IF_NC goto discourage;
    if(AICheckEnemyHalfHP()) {
        (*hl)++;
        return;
    }

    // PUSH_HL;
    // CALL(aAICheckLastPlayerMon);
    // POP_HL;
    // JP_Z (mAIDiscourageMove);
    if(AICheckLastPlayerMon()) {
        return AIDiscourageMove(hl);
    }

//  80% chance to greatly encourage this move if the enemy is badly poisoned (buggy).
//  Should check wPlayerSubStatus5 instead.
    // LD_A_addr(wEnemySubStatus5);
    // BIT_A(SUBSTATUS_TOXIC);
    // IF_NZ goto encourage;
#if BUGFIX_MEANLOOK
    uint8_t substat5 = wram->wPlayerSubStatus5;
#else
    uint8_t substat5 = wram->wEnemySubStatus5;
#endif
//  80% chance to greatly encourage this move if the player is either
//  in love, identified, stuck in Rollout, or has a Nightmare.
    // LD_A_addr(wPlayerSubStatus1);
    // AND_A(1 << SUBSTATUS_IN_LOVE | 1 << SUBSTATUS_ROLLOUT | 1 << SUBSTATUS_IDENTIFIED | 1 << SUBSTATUS_NIGHTMARE);
    // IF_NZ goto encourage;
    if(bit_test(substat5, SUBSTATUS_TOXIC)
    || (wram->wPlayerSubStatus1 & ((1 << SUBSTATUS_IN_LOVE) | (1 << SUBSTATUS_ROLLOUT) | (1 << SUBSTATUS_IDENTIFIED) | (1 << SUBSTATUS_NIGHTMARE)))) {
    // encourage:
        // CALL(aAI_80_20);
        // RET_C ;
        if(!AI_80_20()) {
            // DEC_hl;
            // DEC_hl;
            // DEC_hl;
            *hl -= 3;
        }
        // RET;
    }

//  Otherwise, discourage this move unless the player only has not very effective moves against the enemy.
    // PUSH_HL;
    // CALLFAR(aCheckPlayerMoveTypeMatchups);
    uint8_t score = CheckPlayerMoveTypeMatchups();
    // LD_A_addr(wEnemyAISwitchScore);
    // CP_A(BASE_AI_SWITCH_SCORE + 1);  // not very effective
    // POP_HL;
    // RET_NC ;
    if(score < BASE_AI_SWITCH_SCORE + 1) {
    // discourage:
        // INC_hl;
        (*hl)++;
        // RET;
    }
}

static bool AICheckLastPlayerMon(void){
    // LD_A_addr(wPartyCount);
    // LD_B_A;
    uint8_t b = gPokemon.partyCount;
    // LD_C(0);
    uint8_t c = 0;
    // LD_HL(wPartyMon1HP);
    struct PartyMon* hl = gPokemon.partyMon;
    // LD_DE(PARTYMON_STRUCT_LENGTH);

    do {
    // loop:
        // LD_A_addr(wCurBattleMon);
        // CP_A_C;
        // IF_Z goto skip;
        if(wram->wCurBattleMon == c)
            continue;

        // LD_A_hli;
        // OR_A_hl;
        // RET_NZ ;
        if(hl->HP != 0)
            return false;
        // DEC_HL;


    // skip:
        // ADD_HL_DE;
        // INC_C;
        // DEC_B;
        // IF_NZ goto loop;
    } while(++hl, ++c, --b != 0);

    // RET;
    return true;
}

//  50% chance to encourage this move.
//  The AI_Basic layer will make sure that
//  Dream Eater is only used against sleeping targets.
static void AI_Smart_Nightmare(uint8_t* hl){
    // CALL(aAI_50_50);
    // RET_C ;
    if(AI_50_50()) {
        // DEC_hl;
        (*hl)--;
    }
    // RET;

}

static void AI_Smart_FlameWheel(uint8_t* hl){
//  Use this move if the enemy is frozen.

    // LD_A_addr(wEnemyMonStatus);
    // BIT_A(FRZ);
    // RET_Z ;
    if(bit_test(wram->wEnemyMon.status[0], FRZ)) {
        // for(int rept = 0; rept < 5; rept++){
        // DEC_hl;
        // }
        *hl -= 5;
    }
    // RET;
}

static void AI_Smart_Curse(uint8_t* hl){
    // LD_A_addr(wEnemyMonType1);
    // CP_A(GHOST);
    // IF_Z goto ghost_curse;
    // LD_A_addr(wEnemyMonType2);
    // CP_A(GHOST);
    // IF_Z goto ghost_curse;
    if(wram->wEnemyMon.type1 == GHOST
    || wram->wEnemyMon.type2 == GHOST) {
    // ghost_curse:
        // LD_A_addr(wPlayerSubStatus1);
        // BIT_A(SUBSTATUS_CURSE);
        // JP_NZ (mAIDiscourageMove);
        if(bit_test(wram->wPlayerSubStatus1, SUBSTATUS_CURSE))
            return AIDiscourageMove(hl);

        // PUSH_HL;
        // FARCALL(aFindAliveEnemyMons);
        // POP_HL;
        // IF_NC goto notlastmon;
        if(FindAliveEnemyMons().flag) {
            // PUSH_HL;
            // CALL(aAICheckLastPlayerMon);
            // POP_HL;
            // IF_NZ goto approve;
            if(AICheckLastPlayerMon()) {
                *hl += 4;
                return;
            }
            // goto ghost_continue;
        }
        else {
        // notlastmon:
            // PUSH_HL;
            // CALL(aAICheckLastPlayerMon);
            // POP_HL;
            // IF_Z goto maybe_greatly_encourage;
            if(AICheckLastPlayerMon()) {
            // maybe_greatly_encourage:
                // CALL(aAI_50_50);
                // RET_C ;
                if(AI_50_50()) {
                    // DEC_hl;
                    // DEC_hl;
                    *hl -= 2;
                }
                // RET;
                return;
            }
        }

    // ghost_continue:
        // CALL(aAICheckEnemyQuarterHP);
        // JP_NC (mAI_Smart_Curse_approve);
        if(AICheckEnemyQuarterHP()) {
            *hl += 4;
            return;
        }

        // CALL(aAICheckEnemyHalfHP);
        // IF_NC goto greatly_encourage;
        if(AICheckEnemyHalfHP()) {
            *hl += 2;
            return;
        }

        // CALL(aAICheckEnemyMaxHP);
        // RET_NC ;
        if(!AICheckEnemyMaxHP())
            return;

        // LD_A_addr(wPlayerTurnsTaken);
        // AND_A_A;
        // RET_NZ ;
        if(wram->wPlayerTurnsTaken != 0)
            return;

    // maybe_greatly_encourage:
        // CALL(aAI_50_50);
        // RET_C ;

        if(AI_50_50()) {
            // DEC_hl;
            // DEC_hl;
            *hl -= 2;
        }
        // RET;
        return;
    }
    else {
        // CALL(aAICheckEnemyHalfHP);
        // IF_NC goto encourage;
        if(AICheckEnemyHalfHP()) {
            (*hl)++;
            return;
        }

        // LD_A_addr(wEnemyAtkLevel);
        // CP_A(BASE_STAT_LEVEL + 4);
        // IF_NC goto encourage;
        if(wram->wEnemyAtkLevel >= BASE_STAT_LEVEL + 4) {
            (*hl)++;
            return;
        }
        // CP_A(BASE_STAT_LEVEL + 2);
        // RET_NC ;
        if(wram->wEnemyAtkLevel >= BASE_STAT_LEVEL + 2)
            return;

        // LD_A_addr(wBattleMonType1);
        // CP_A(GHOST);
        // IF_Z goto greatly_encourage;
        if(wram->wBattleMon.type1 == GHOST) {
            *hl += 2;
            return;
        }
        // CP_A(SPECIAL);
        // RET_NC ;
        // LD_A_addr(wBattleMonType2);
        // CP_A(SPECIAL);
        // RET_NC ;
        if(wram->wBattleMon.type1 >= SPECIAL
        || wram->wBattleMon.type2 >= SPECIAL) 
            return;

        // CALL(aAI_80_20);
        // RET_C ;
        if(!AI_80_20()) {
            // DEC_hl;
            // DEC_hl;
            *hl -= 2;
        }
        // RET;


    // approve:
        // INC_hl;
        // INC_hl;

    // greatly_encourage:
        // INC_hl;

    // encourage:
        // INC_hl;
        // RET;
    }
}

static void AI_Smart_Protect(uint8_t* hl){
//  Greatly discourage this move if the enemy already used Protect.
    // LD_A_addr(wEnemyProtectCount);
    // AND_A_A;
    // IF_NZ goto greatly_discourage;
    if(wram->wEnemyProtectCount != 0) {
        (*hl)++;
    }

//  Discourage this move if the player is locked on.
    // LD_A_addr(wPlayerSubStatus5);
    // BIT_A(SUBSTATUS_LOCK_ON);
    // IF_NZ goto discourage;
    else if(bit_test(wram->wPlayerSubStatus5, SUBSTATUS_LOCK_ON)) {
        // goto discourage
    }

//  Encourage this move if the player's Fury Cutter is boosted enough.
    // LD_A_addr(wPlayerFuryCutterCount);
    // CP_A(3);
    // IF_NC goto encourage;

//  Encourage this move if the player has charged a two-turn move.
    // LD_A_addr(wPlayerSubStatus3);
    // BIT_A(SUBSTATUS_CHARGED);
    // IF_NZ goto encourage;

//  Encourage this move if the player is affected by Toxic, Leech Seed, or Curse.
    // LD_A_addr(wPlayerSubStatus5);
    // BIT_A(SUBSTATUS_TOXIC);
    // IF_NZ goto encourage;
    // LD_A_addr(wPlayerSubStatus4);
    // BIT_A(SUBSTATUS_LEECH_SEED);
    // IF_NZ goto encourage;
    // LD_A_addr(wPlayerSubStatus1);
    // BIT_A(SUBSTATUS_CURSE);
    // IF_NZ goto encourage;

//  Discourage this move if the player's Rollout count is not boosted enough.
    // BIT_A(SUBSTATUS_ROLLOUT);
    // IF_Z goto discourage;
    // LD_A_addr(wPlayerRolloutCount);
    // CP_A(3);
    // IF_C goto discourage;
    else if(wram->wPlayerFuryCutterCount >= 3
        ||  bit_test(wram->wPlayerSubStatus3, SUBSTATUS_CHARGED)
        ||  bit_test(wram->wPlayerSubStatus5, SUBSTATUS_TOXIC)
        ||  bit_test(wram->wPlayerSubStatus4, SUBSTATUS_LEECH_SEED)
        ||  bit_test(wram->wPlayerSubStatus1, SUBSTATUS_CURSE)
        || (bit_test(wram->wPlayerSubStatus1, SUBSTATUS_ROLLOUT) &&  wram->wPlayerRolloutCount >= 3)) {
    //  80% chance to encourage this move otherwise.
    // encourage:
        // CALL(aAI_80_20);
        // RET_C ;
        if(!AI_80_20()) {
            // DEC_hl;
            (*hl)--;
        }
        // RET;
        return;
    }

// encourage:
    // CALL(aAI_80_20);
    // RET_C ;

    // DEC_hl;
    // RET;


// greatly_discourage:
    // INC_hl;


// discourage:
    // CALL(aRandom);
    // CP_A(8 percent);
    // RET_C ;
    if(Random() >= 8 percent) {
        // INC_hl;
        // INC_hl;
        *hl += 2;
    }
    // RET;
}

static void AI_Smart_Foresight(uint8_t* hl){
//  60% chance to encourage this move if the enemy's accuracy is sharply lowered.
    // LD_A_addr(wEnemyAccLevel);
    // CP_A(BASE_STAT_LEVEL - 2);
    // IF_C goto encourage;

//  60% chance to encourage this move if the player's evasion is sharply raised.
    // LD_A_addr(wPlayerEvaLevel);
    // CP_A(BASE_STAT_LEVEL + 3);
    // IF_NC goto encourage;

//  60% chance to encourage this move if the player is a Ghost type.
    // LD_A_addr(wBattleMonType1);
    // CP_A(GHOST);
    // IF_Z goto encourage;
    // LD_A_addr(wBattleMonType2);
    // CP_A(GHOST);
    // IF_Z goto encourage;
    if(wram->wEnemyAccLevel < BASE_STAT_LEVEL - 2
    || wram->wPlayerEvaLevel > BASE_STAT_LEVEL + 2
    || wram->wBattleMon.type1 == GHOST
    || wram->wBattleMon.type2 == GHOST) {
    // encourage:
        // CALL(aRandom);
        // CP_A(39 percent + 1);
        // RET_C ;
        if(Random() >= 39 percent + 1) {
            // DEC_hl;
            // DEC_hl;
            *hl -= 2;
        }
        // RET;
    }
    else {
    //  92% chance to discourage this move otherwise.
        // CALL(aRandom);
        // CP_A(8 percent);
        // RET_C ;
        if(Random() >= 8 percent) {
            // INC_hl;
            (*hl)++;
        }
        // RET;
    }
}

static void AI_Smart_PerishSong(uint8_t* hl){
    // PUSH_HL;
    // CALLFAR(aFindAliveEnemyMons);
    // POP_HL;
    // IF_C goto no;
    if(FindAliveEnemyMons().flag) {
    // no:
        // LD_A_hl;
        // ADD_A(5);
        // LD_hl_A;
        *hl += 5;
        // RET;
        return;
    }

    // LD_A_addr(wPlayerSubStatus5);
    // BIT_A(SUBSTATUS_CANT_RUN);
    // IF_NZ goto yes;
    if(bit_test(wram->wPlayerSubStatus5, SUBSTATUS_CANT_RUN)) {
    // yes:
        // CALL(aAI_50_50);
        // RET_C ;
        if(AI_50_50()) {
            // DEC_hl;
            (*hl)--;
        }
        // RET;
        return;
    }

    // PUSH_HL;
    // CALLFAR(aCheckPlayerMoveTypeMatchups);
    uint8_t score = CheckPlayerMoveTypeMatchups();
    // LD_A_addr(wEnemyAISwitchScore);
    // CP_A(BASE_AI_SWITCH_SCORE);
    // POP_HL;
    // RET_C ;

    if(score >= BASE_AI_SWITCH_SCORE && AI_50_50()) {
        // CALL(aAI_50_50);
        // RET_C ;

        // INC_hl;
        (*hl)++;
        // RET;
        return;
    }
}

static void AI_Smart_Sandstorm(uint8_t* hl){
    static const uint8_t SandstormImmuneTypes[] = {
        ROCK,
        GROUND,
        STEEL,
        (uint8_t)-1,     // end
    };

//  Greatly discourage this move if the player is immune to Sandstorm damage.
    // LD_A_addr(wBattleMonType1);
    // PUSH_HL;
    // LD_HL(mAI_Smart_Sandstorm_SandstormImmuneTypes);
    // LD_DE(1);
    // CALL(aIsInArray);
    // POP_HL;
    // IF_C goto greatly_discourage;

    // LD_A_addr(wBattleMonType2);
    // PUSH_HL;
    // LD_HL(mAI_Smart_Sandstorm_SandstormImmuneTypes);
    // LD_DE(1);
    // CALL(aIsInArray);
    // POP_HL;
    // IF_C goto greatly_discourage;
    if(IsInU8Array(SandstormImmuneTypes, wram->wBattleMon.type1)
    || IsInU8Array(SandstormImmuneTypes, wram->wBattleMon.type2)) {
        (*hl)++;
    }

//  Discourage this move if player's HP is below 50%.
    // CALL(aAICheckPlayerHalfHP);
    // IF_NC goto discourage;
    else if(AICheckPlayerHalfHP()) {

    }

//  50% chance to encourage this move otherwise.
    // CALL(aAI_50_50);
    // RET_C ;
    else if(AI_50_50())
        return;
    else {
        // DEC_hl;
        (*hl)--;
        // RET;
        return;
    }

// greatly_discourage:
    // INC_hl;

// discourage:
    // INC_hl;
    (*hl)++;
    // RET;
}

static void AI_Smart_Endure(uint8_t* hl){
//  Greatly discourage this move if the enemy already used Protect.
    // LD_A_addr(wEnemyProtectCount);
    // AND_A_A;
    // IF_NZ goto greatly_discourage;

//  Greatly discourage this move if the enemy's HP is full.
    // CALL(aAICheckEnemyMaxHP);
    // IF_C goto greatly_discourage;
    if(wram->wEnemyProtectCount != 0 || AICheckEnemyMaxHP()) {
    // greatly_discourage:
        // INC_hl;
    
    // discourage:
        // INC_hl;
        (*hl) += 2;
        // RET;
        return;
    }

//  Discourage this move if the enemy's HP is at least 25%.
    // CALL(aAICheckEnemyQuarterHP);
    // IF_C goto discourage;
    if(AICheckEnemyQuarterHP()) {
        (*hl)++;
        return;
    }

//  If the enemy has Reversal...
    // LD_B(EFFECT_REVERSAL);
    // CALL(aAIHasMoveEffect);
    // IF_NC goto no_reversal;
    if(AIHasMoveEffect(EFFECT_REVERSAL)) {
    //  ...80% chance to greatly encourage this move.
        // CALL(aAI_80_20);
        // RET_C ;
        if(AI_80_20())
            return;

        // DEC_hl;
        // DEC_hl;
        // DEC_hl;
        (*hl) -= 3;
        // RET;
        return;
    }

// no_reversal:
//  If the enemy is not locked on, do nothing.
    // LD_A_addr(wEnemySubStatus5);
    // BIT_A(SUBSTATUS_LOCK_ON);
    // RET_Z ;
    if(!bit_test(wram->wEnemySubStatus5, SUBSTATUS_LOCK_ON))
        return;

//  50% chance to greatly encourage this move.
    // CALL(aAI_50_50);
    // RET_C ;
    if(AI_50_50())
        return;

    // DEC_hl;
    // DEC_hl;
    (*hl) -= 2;
    // RET;
}

//  Encourage this move based on Fury Cutter's count.
static void AI_Smart_FuryCutter(uint8_t* hl){
    // LD_A_addr(wEnemyFuryCutterCount);
    // AND_A_A;
    // JR_Z (mAI_Smart_Rollout);
    if(wram->wEnemyFuryCutterCount == 0)
        return AI_Smart_Rollout(hl);
    // DEC_hl;
    *hl -= 1;

    // CP_A(2);
    // JR_C (mAI_Smart_Rollout);
    if(wram->wEnemyFuryCutterCount < 2)
        return AI_Smart_Rollout(hl);
    // DEC_hl;
    // DEC_hl;
    *hl -= 2;

    // CP_A(3);
    // JR_C (mAI_Smart_Rollout);
    if(wram->wEnemyFuryCutterCount < 3)
        return AI_Smart_Rollout(hl);
    // DEC_hl;
    // DEC_hl;
    // DEC_hl;
    *hl -= 3;

// fallthrough

}

static void AI_Smart_Rollout(uint8_t* hl){
//  Rollout, Fury Cutter

//  80% chance to discourage this move if the enemy is in love, confused, or paralyzed.
    // LD_A_addr(wEnemySubStatus1);
    // BIT_A(SUBSTATUS_IN_LOVE);
    // IF_NZ goto maybe_discourage;

    // LD_A_addr(wEnemySubStatus3);
    // BIT_A(SUBSTATUS_CONFUSED);
    // IF_NZ goto maybe_discourage;

    // LD_A_addr(wEnemyMonStatus);
    // BIT_A(PAR);
    // IF_NZ goto maybe_discourage;

//  80% chance to discourage this move if the enemy's HP is below 25%,
//  or if accuracy or evasion modifiers favour the player.
    // CALL(aAICheckEnemyQuarterHP);
    // IF_NC goto maybe_discourage;

    // LD_A_addr(wEnemyAccLevel);
    // CP_A(BASE_STAT_LEVEL);
    // IF_C goto maybe_discourage;
    // LD_A_addr(wPlayerEvaLevel);
    // CP_A(BASE_STAT_LEVEL + 1);
    // IF_NC goto maybe_discourage;
    if(bit_test(wram->wEnemySubStatus1, SUBSTATUS_IN_LOVE)
    || bit_test(wram->wEnemySubStatus3, SUBSTATUS_CONFUSED)
    || bit_test(wram->wEnemyMon.status[0], PAR)
    || AICheckEnemyQuarterHP()
    || wram->wEnemyAccLevel < BASE_STAT_LEVEL
    || wram->wPlayerEvaLevel > BASE_STAT_LEVEL) {
    // maybe_discourage:
        // CALL(aAI_80_20);
        // RET_C ;
        if(!AI_80_20()) {
            // INC_hl;
            (*hl)++;
            // RET;
        }
        return;
    }
    else {
    //  80% chance to greatly encourage this move otherwise.
        // CALL(aRandom);
        // CP_A(79 percent - 1);
        // RET_NC ;
        if(Random() < 79 percent - 1) {
            // DEC_hl;
            // DEC_hl;
            *hl -= 2;
        }
        // RET;
    }
}

static void AI_Smart_Swagger(uint8_t* hl){
    return AI_Smart_Attract(hl);
}

//  80% chance to encourage this move during the first turn of player's Pokemon.
//  80% chance to discourage this move otherwise.
static void AI_Smart_Attract(uint8_t* hl){
    // LD_A_addr(wPlayerTurnsTaken);
    // AND_A_A;
    // IF_Z goto first_turn;
    if(wram->wPlayerTurnsTaken == 0) {
    // first_turn:
        // CALL(aRandom);
        // CP_A(79 percent - 1);
        // RET_NC ;
        if(Random() < 79 percent - 1) {
            // DEC_hl;
            --(*hl);
            // RET;
        }
    }
    else {
        // CALL(aAI_80_20);
        // RET_C ;
        if(!AI_80_20()) {
            // INC_hl;
            ++(*hl);
            // RET;
        }
    }
}

//  80% chance to discourage this move if player's HP is below 50%.
static void AI_Smart_Safeguard(uint8_t* hl){
    // CALL(aAICheckPlayerHalfHP);
    // RET_C ;
    // CALL(aAI_80_20);
    // RET_C ;
    if(AICheckPlayerHalfHP() && !AI_80_20()) {
        // INC_hl;
        (*hl)++;
    }
    // RET;
}

static void AI_Smart_Magnitude(uint8_t* hl){
    return AI_Smart_Earthquake(hl);
}

static void AI_Smart_Earthquake(uint8_t* hl){
//  Greatly encourage this move if the player is underground and the enemy is faster.
    // LD_A_addr(wLastPlayerCounterMove);
    // CP_A(DIG);
    // RET_NZ ;
    if(wram->wLastPlayerCounterMove != DIG)
        return;

    // LD_A_addr(wPlayerSubStatus3);
    // BIT_A(SUBSTATUS_UNDERGROUND);
    // IF_Z goto could_dig;
    if(!bit_test(wram->wPlayerSubStatus3, SUBSTATUS_UNDERGROUND)) {
    // could_dig:
    // Try to predict if the player will use Dig this turn.

    // 50% chance to encourage this move if the enemy is slower than the player.
        // CALL(aAICompareSpeed);
        // RET_C ;
        if(AICompareSpeed())
            return;

        // CALL(aAI_50_50);
        // RET_C ;

        if(AI_50_50()) {
            // DEC_hl;
            (*hl)--;
            // RET;
        }
    }

    // CALL(aAICompareSpeed);
    // RET_NC ;
    if(AICompareSpeed()) {
        // DEC_hl;
        // DEC_hl;
        (*hl) -= 2;
    }
    // RET;
}

//  Discourage this move if the player hasn't shown super-effective moves against the enemy.
//  Consider player's type(s) if its moves are unknown.
static void AI_Smart_BatonPass(uint8_t* hl){
    // PUSH_HL;
    // CALLFAR(aCheckPlayerMoveTypeMatchups);
    uint8_t score = CheckPlayerMoveTypeMatchups();
    // LD_A_addr(wEnemyAISwitchScore);
    // CP_A(BASE_AI_SWITCH_SCORE);
    // POP_HL;
    // RET_C ;
    if(score < BASE_AI_SWITCH_SCORE)
        return;
    // INC_hl;
    (*hl)++;
    // RET;
}

//  50% chance to greatly encourage this move if player's HP is below 25%.
//  80% chance to discourage this move otherwise.
static void AI_Smart_Pursuit(uint8_t* hl){
    // CALL(aAICheckPlayerQuarterHP);
    // IF_NC goto encourage;
    if(AICheckPlayerQuarterHP()) {
    // encourage:
        // CALL(aAI_50_50);
        // RET_C ;
        if(AI_50_50()) {
            // DEC_hl;
            // DEC_hl;
            *hl -= 2;
        }
        // RET;
    }
    // CALL(aAI_80_20);
    // RET_C ;
    if(!AI_80_20()) {
        // INC_hl;
        (*hl)++;
    }
    // RET;
}

//  80% chance to greatly encourage this move if the enemy is
//  trapped (Bind effect), seeded, or scattered with spikes.
static void AI_Smart_RapidSpin(uint8_t* hl){
    // LD_A_addr(wEnemyWrapCount);
    // AND_A_A;
    // IF_NZ goto encourage;

    // LD_A_addr(wEnemySubStatus4);
    // BIT_A(SUBSTATUS_LEECH_SEED);
    // IF_NZ goto encourage;

    // LD_A_addr(wEnemyScreens);
    // BIT_A(SCREENS_SPIKES);
    // RET_Z ;
    if(wram->wEnemyWrapCount != 0
    || bit_test(wram->wEnemySubStatus4, SUBSTATUS_LEECH_SEED)
    || bit_test(wram->wEnemyScreens, SCREENS_SPIKES)) {
    // encourage:
        // CALL(aAI_80_20);
        // RET_C ;
        if(!AI_80_20()) {
            // DEC_hl;
            // DEC_hl;
            *hl -= 2;
            // RET;
        }
    }
}

static void AI_Smart_HiddenPower(uint8_t* hl){
    // PUSH_HL;
    // LD_A(1);
    // LDH_addr_A(hBattleTurn);
    hram.hBattleTurn = TURN_ENEMY;

//  Calculate Hidden Power's type and base power based on enemy's DVs.
    // CALLFAR(aHiddenPowerDamage);
    uint8_t dmg = HiddenPowerDamage();
    // CALLFAR(aBattleCheckTypeMatchup);
    // POP_HL;

//  Discourage Hidden Power if not very effective.
    // LD_A_addr(wTypeMatchup);
    uint8_t matchup = BattleCheckTypeMatchup();
    // CP_A(EFFECTIVE);
    // IF_C goto bad;

//  Discourage Hidden Power if its base power    is lower than 50.
    // LD_A_D;
    // CP_A(50);
    // IF_C goto bad;
    if(matchup < EFFECTIVE || dmg < 50) {
    // bad:
        // INC_hl;
        (*hl)++;
        // RET;
        return;
    }

//  Encourage Hidden Power if super-effective.
    // LD_A_addr(wTypeMatchup);
    // CP_A(EFFECTIVE + 1);
    // IF_NC goto good;

//  Encourage Hidden Power if its base power is 70.
    // LD_A_D;
    // CP_A(70);
    // RET_C ;
    if(matchup > EFFECTIVE || dmg >= 70) {
    // good:
        // DEC_hl;
        (*hl)--;
        // RET;
        return;
    }
}

//  Greatly discourage this move if it would favour the player type-wise.
//  Particularly, if the player is a Water-type.
static void AI_Smart_RainDance(uint8_t* hl){
    // LD_A_addr(wBattleMonType1);
    // CP_A(WATER);
    // JR_Z (mAIBadWeatherType);
    if(wram->wBattleMon.type1 == WATER)
        return AIBadWeatherType(hl);
    // CP_A(FIRE);
    // JR_Z (mAIGoodWeatherType);
    if(wram->wBattleMon.type1 == FIRE)
        return AIGoodWeatherType(hl);

    // LD_A_addr(wBattleMonType2);
    // CP_A(WATER);
    // JR_Z (mAIBadWeatherType);
    if(wram->wBattleMon.type2 == WATER)
        return AIBadWeatherType(hl);
    // CP_A(FIRE);
    // JR_Z (mAIGoodWeatherType);
    if(wram->wBattleMon.type2 == FIRE)
        return AIGoodWeatherType(hl);

    // PUSH_HL;
    // LD_HL(mRainDanceMoves);
    // JR(mAI_Smart_WeatherMove);

// INCLUDE "data/battle/ai/rain_dance_moves.asm"
    return AI_Smart_WeatherMove(hl, RainDanceMoves);
}

//  Greatly discourage this move if it would favour the player type-wise.
//  Particularly, if the player is a Fire-type.
static void AI_Smart_SunnyDay(uint8_t* hl){
    // LD_A_addr(wBattleMonType1);
    // CP_A(FIRE);
    // JR_Z (mAIBadWeatherType);
    if(wram->wBattleMon.type1 == FIRE)
        return AIBadWeatherType(hl);
    // CP_A(WATER);
    // JR_Z (mAIGoodWeatherType);
    if(wram->wBattleMon.type1 == WATER)
        return AIGoodWeatherType(hl);

    // LD_A_addr(wBattleMonType2);
    // CP_A(FIRE);
    // JR_Z (mAIBadWeatherType);
    if(wram->wBattleMon.type2 == FIRE)
        return AIBadWeatherType(hl);
    // CP_A(WATER);
    // JR_Z (mAIGoodWeatherType);
    if(wram->wBattleMon.type2 == WATER)
        return AIGoodWeatherType(hl);

    // PUSH_HL;
    // LD_HL(mSunnyDayMoves);

// fallthrough

    return AI_Smart_WeatherMove(hl, SunnyDayMoves);
}

static void AI_Smart_WeatherMove(uint8_t* hl, const move_t* moves){
//  Rain Dance, Sunny Day

//  Greatly discourage this move if the enemy doesn't have
//  one of the useful Rain Dance or Sunny Day moves.
    // CALL(aAIHasMoveInArray);
    // POP_HL;
    // JR_NC (mAIBadWeatherType);
    if(!AIHasMoveInArray(moves))
        return AIBadWeatherType(hl);

//  Greatly discourage this move if player's HP is below 50%.
    // CALL(aAICheckPlayerHalfHP);
    // JR_NC (mAIBadWeatherType);
    if(AICheckPlayerHalfHP())
        return AIBadWeatherType(hl);

//  50% chance to encourage this move otherwise.
    // CALL(aAI_50_50);
    // RET_C ;
    if(AI_50_50()) {
        // DEC_hl;
        (*hl)--;
        // RET;
    }
}

static void AIBadWeatherType(uint8_t* hl){
    // INC_hl;
    // INC_hl;
    // INC_hl;
    *hl += 3;
    // RET;
}

static void AIGoodWeatherType(uint8_t* hl){
//  Rain Dance, Sunny Day

//  Greatly encourage this move if it would disfavour the player type-wise and player's HP is above 50%...
    // CALL(aAICheckPlayerHalfHP);
    // RET_NC ;
    if(AICheckPlayerHalfHP())
        return;

//  ...as long as one of the following conditions meet:
//  It's the first turn of the player's Pokemon.
    // LD_A_addr(wPlayerTurnsTaken);
    // AND_A_A;
    // IF_Z goto good;

//  Or it's the first turn of the enemy's Pokemon.
    // LD_A_addr(wEnemyTurnsTaken);
    // AND_A_A;
    // RET_NZ ;
    if(wram->wPlayerTurnsTaken == 0 || wram->wEnemyTurnsTaken == 0) {
    // good:
        // DEC_hl;
        // DEC_hl;
        (*hl) -= 2;
        // RET;
        return;
    }
// INCLUDE "data/battle/ai/sunny_day_moves.asm"
}

//  Dismiss this move if enemy's attack is higher than +2 or if enemy's HP is below 50%.
//  Else, discourage this move if enemy's HP is not full.
static void AI_Smart_BellyDrum(uint8_t* hl){
    // LD_A_addr(wEnemyAtkLevel);
    // CP_A(BASE_STAT_LEVEL + 3);
    // IF_NC goto discourage;
    if(wram->wEnemyAtkLevel < BASE_STAT_LEVEL + 3) {
        // CALL(aAICheckEnemyMaxHP);
        // RET_C ;
        if(!AICheckEnemyMaxHP()) {
            // INC_hl;
            (*hl)++;
        }

        // CALL(aAICheckEnemyHalfHP);
        // RET_C ;
        if(!AICheckEnemyHalfHP())
            return;
    }

// discourage:
    // LD_A_hl;
    // ADD_A(5);
    // LD_hl_A;
    *hl += 5;
    // RET;
}

static void AI_Smart_PsychUp(uint8_t* hl){
    // PUSH_HL;
    // LD_HL(wEnemyAtkLevel);
    // LD_B(NUM_LEVEL_STATS);
    // LD_C(100);
    
    //  Calculate the sum of all enemy's stat level modifiers. Add 100 first to prevent underflow.
    //  Put the result in c. c will range between 58 and 142.
    uint8_t c = 100;
    for(uint8_t i = 0; i < NUM_LEVEL_STATS; ++i) {
    // enemy_loop:
        // LD_A_hli;
        // SUB_A(BASE_STAT_LEVEL);
        // ADD_A_C;
        // LD_C_A;
        c += wram->wEnemyStatLevels[i] - BASE_STAT_LEVEL;
        // DEC_B;
        // IF_NZ goto enemy_loop;
    }

//  Calculate the sum of all player's stat level modifiers. Add 100 first to prevent underflow.
//  Put the result in d. d will range between 58 and 142.
    // LD_HL(wPlayerAtkLevel);
    // LD_B(NUM_LEVEL_STATS);
    // LD_D(100);
    uint8_t d = 100;
    for(uint8_t i = 0; i < NUM_LEVEL_STATS; ++i) {
    // player_loop:
        // LD_A_hli;
        // SUB_A(BASE_STAT_LEVEL);
        // ADD_A_D;
        // LD_D_A;
        d += wram->wPlayerStatLevels[i] - BASE_STAT_LEVEL;
        // DEC_B;
        // IF_NZ goto player_loop;
    }

//  Greatly discourage this move if enemy's stat levels are higher than player's (if c>=d).
    // LD_A_C;
    // SUB_A_D;
    // POP_HL;
    // IF_NC goto discourage;
    if(c >= d) {
    // discourage:
        // INC_hl;
        // INC_hl;
        // RET;
        *hl += 2;
        return;
    }

//  Else, 80% chance to encourage this move unless player's accuracy level is lower than -1...
    // LD_A_addr(wPlayerAccLevel);
    // CP_A(BASE_STAT_LEVEL - 1);
    // RET_C ;

//  ...or enemy's evasion level is higher than +0.
    // LD_A_addr(wEnemyEvaLevel);
    // CP_A(BASE_STAT_LEVEL + 1);
    // RET_NC ;

    // CALL(aAI_80_20);
    // RET_C ;
    if(wram->wPlayerAccLevel >= BASE_STAT_LEVEL - 1 
    && wram->wEnemyEvaLevel  <  BASE_STAT_LEVEL + 1
    && !AI_80_20()) {
        // DEC_hl;
        (*hl)--;
        // RET;
    }
}

static void AI_Smart_MirrorCoat(uint8_t* hl){
    // PUSH_HL;
    // LD_HL(wPlayerUsedMoves);
    // LD_C(NUM_MOVES);
    // LD_B(0);

    uint8_t b = 0;
    for(uint8_t i = 0; i < NUM_MOVES; ++i) {
    // playermoveloop:
        // LD_A_hli;
        move_t a = wram->wPlayerUsedMoves[i];
        // AND_A_A;
        // IF_Z goto skipmove;
        if(a == NO_MOVE)
            continue;

        // CALL(aAIGetEnemyMove);
        const struct Move* mv = AIGetEnemyMove(a);

        // LD_A_addr(wEnemyMoveStruct + MOVE_POWER);
        // AND_A_A;
        // IF_Z goto skipmove;

        // LD_A_addr(wEnemyMoveStruct + MOVE_TYPE);
        // CP_A(SPECIAL);
        // IF_C goto skipmove;
        if(mv->power == 0 || mv->type < SPECIAL)
            continue;

        // INC_B;
        ++b;


    // skipmove:
        // DEC_C;
        // IF_NZ goto playermoveloop;
    }

    // POP_HL;
    // LD_A_B;
    // AND_A_A;
    // IF_Z goto discourage;
    if(b == 0) {
    // discourage:
        // INC_hl;
        (*hl)++;
        // RET;
        return;
    }

    // CP_A(3);
    // IF_NC goto encourage;
    if(b < 3) {
        // LD_A_addr(wLastPlayerCounterMove);
        // AND_A_A;
        // IF_Z goto done;
        if(wram->wLastPlayerCounterMove == NO_MOVE)
            return;

        // CALL(aAIGetEnemyMove);
        const struct Move* mv = AIGetEnemyMove(wram->wLastPlayerCounterMove);

        // LD_A_addr(wEnemyMoveStruct + MOVE_POWER);
        // AND_A_A;
        // IF_Z goto done;

        // LD_A_addr(wEnemyMoveStruct + MOVE_TYPE);
        // CP_A(SPECIAL);
        // IF_C goto done;
        if(mv->power == 0 || mv->type < SPECIAL)
            return;
    }

// encourage:
    // CALL(aRandom);
    // CP_A(39 percent + 1);
    // IF_C goto done;
    if(Random() >= 39 percent + 1) {
        // DEC_hl;
        (*hl)--;
    }
// done:
    // RET;
}

static void AI_Smart_Twister(uint8_t* hl){
    return AI_Smart_Gust(hl);
}

//  Greatly encourage this move if the player is flying and the enemy is faster.
static void AI_Smart_Gust(uint8_t* hl){
    // LD_A_addr(wLastPlayerCounterMove);
    // CP_A(FLY);
    // RET_NZ ;
    if(wram->wLastPlayerCounterMove == FLY) {
        // LD_A_addr(wPlayerSubStatus3);
        // BIT_A(SUBSTATUS_FLYING);
        // IF_Z goto couldFly;
        if(bit_test(wram->wPlayerSubStatus3, SUBSTATUS_FLYING)) {
            // CALL(aAICompareSpeed);
            // RET_NC ;

            if(AICompareSpeed()) {
                // DEC_hl;
                // DEC_hl;
                *hl -= 2;
            }
            // RET;
            return;
        }
        else {
        //  Try to predict if the player will use Fly this turn.

        // couldFly:
        //  50% chance to encourage this move if the enemy is slower than the player.
            // CALL(aAICompareSpeed);
            // RET_C ;
            // CALL(aAI_50_50);
            // RET_C ;
            if(!AICompareSpeed() && !AI_50_50()) {
                // DEC_hl;
                (*hl)--;
                // RET;
            }
            return;
        }
    }
}

//  Greatly encourage this move if the player is
//  flying or underground, and slower than the enemy.
static void AI_Smart_FutureSight(uint8_t* hl){
    // CALL(aAICompareSpeed);
    // RET_NC ;

    // LD_A_addr(wPlayerSubStatus3);
    // AND_A(1 << SUBSTATUS_FLYING | 1 << SUBSTATUS_UNDERGROUND);
    // RET_Z ;

    if(AICompareSpeed() && (wram->wPlayerSubStatus3 & ((1 << SUBSTATUS_FLYING) | (1 << SUBSTATUS_UNDERGROUND)))) {
        // DEC_hl;
        // DEC_hl;
        *hl -= 2;
    }
    // RET;
}

//  80% chance to encourage this move if the player has used Minimize.
static void AI_Smart_Stomp(uint8_t* hl){
    // LD_A_addr(wPlayerMinimized);
    // AND_A_A;
    // RET_Z ;

    // CALL(aAI_80_20);
    // RET_C ;

    
    if(wram->wPlayerMinimized && !AI_80_20()) {
        // DEC_hl;
        // RET;
        (*hl)--;
    }
}

//  80% chance to encourage this move when it's sunny.
//  90% chance to discourage this move when it's raining.
static void AI_Smart_Solarbeam(uint8_t* hl){
    // LD_A_addr(wBattleWeather);
    // CP_A(WEATHER_SUN);
    // IF_Z goto encourage;
    if(wram->wBattleWeather == WEATHER_SUN) {
    // encourage:
        // CALL(aAI_80_20);
        // RET_C ;
        if(!AI_80_20()) {
            // DEC_hl;
            // DEC_hl;
            *hl -= 2;
        }
        // RET;
        return;
    }

    // CP_A(WEATHER_RAIN);
    // RET_NZ ;
    if(wram->wBattleWeather == WEATHER_RAIN) {
        // CALL(aRandom);
        // CP_A(10 percent);
        // RET_C ;

        if(Random() >= 10 percent) {
            // INC_hl;
            // INC_hl;
            *hl += 2;
        }
        // RET;
        return;
    }
}

//  90% chance to discourage this move when it's sunny.
static void AI_Smart_Thunder(uint8_t* hl){
    // LD_A_addr(wBattleWeather);
    // CP_A(WEATHER_SUN);
    // RET_NZ ;

    // CALL(aRandom);
    // CP_A(10 percent);
    // RET_C ;

    if(wram->wBattleWeather == WEATHER_SUN && Random() >= 10 percent) {
        // INC_hl;
        // RET;
        (*hl)++;
    }
}

//  Return carry if enemy is faster than player.
bool AICompareSpeed(void){
    // PUSH_BC;
    uint16_t eSpeed = (wram->wEnemyMon.speed[0] << 8) | wram->wEnemyMon.speed[1];
    uint16_t pSpeed = (wram->wBattleMon.speed[0] << 8) | wram->wBattleMon.speed[1];
    // LD_A_addr(wEnemyMonSpeed + 1);
    // LD_B_A;
    // LD_A_addr(wBattleMonSpeed + 1);
    // CP_A_B;
    // LD_A_addr(wEnemyMonSpeed);
    // LD_B_A;
    // LD_A_addr(wBattleMonSpeed);
    // SBC_A_B;
    // POP_BC;
    // RET;
    return eSpeed > pSpeed;
}

bool AICheckPlayerMaxHP(void){
    // PUSH_HL;
    // PUSH_DE;
    // PUSH_BC;
    // LD_DE(wBattleMonHP);
    // LD_HL(wBattleMonMaxHP);
    // JR(mAICheckMaxHP);
    return AICheckMaxHP(wram->wBattleMon.hp, wram->wBattleMon.maxHP);
}

bool AICheckEnemyMaxHP(void){
    // PUSH_HL;
    // PUSH_DE;
    // PUSH_BC;
    // LD_DE(wEnemyMonHP);
    // LD_HL(wEnemyMonMaxHP);
// fallthrough

    return AICheckMaxHP(wram->wEnemyMon.hp, wram->wEnemyMon.maxHP);
}

//  Return carry if hp at de matches max hp at hl.
bool AICheckMaxHP(uint16_t hp, uint16_t maxHP){
    // LD_A_de;
    // INC_DE;
    // CP_A_hl;
    // IF_NZ goto not_max;

    // INC_HL;
    // LD_A_de;
    // CP_A_hl;
    // IF_NZ goto not_max;

    // POP_BC;
    // POP_DE;
    // POP_HL;
    // SCF;
    // RET;
    return hp == maxHP;

// not_max:
    // POP_BC;
    // POP_DE;
    // POP_HL;
    // AND_A_A;
    // RET;
}

bool AICheckPlayerHalfHP(void){
    // PUSH_HL;
    // LD_HL(wBattleMonHP);
    // LD_B_hl;
    // INC_HL;
    // LD_C_hl;
    uint16_t hp = BigEndianToNative16(wram->wBattleMon.hp);
    uint16_t maxHP = BigEndianToNative16(wram->wBattleMon.maxHP);
    // SLA_C;
    // RL_B;
    // INC_HL;
    // INC_HL;
    // LD_A_hld;
    // CP_A_C;
    // LD_A_hl;
    // SBC_A_B;
    // POP_HL;
    // RET;
    return (hp * 2) < maxHP;
}

bool AICheckEnemyHalfHP(void){
    // PUSH_HL;
    // PUSH_DE;
    // PUSH_BC;
    // LD_HL(wEnemyMonHP);
    uint16_t hp = BigEndianToNative16(wram->wEnemyMon.hp);
    uint16_t maxHP = BigEndianToNative16(wram->wEnemyMon.maxHP);
    // LD_B_hl;
    // INC_HL;
    // LD_C_hl;
    // SLA_C;
    // RL_B;
    // INC_HL;
    // INC_HL;
    // LD_A_hld;
    // CP_A_C;
    // LD_A_hl;
    // SBC_A_B;
    // POP_BC;
    // POP_DE;
    // POP_HL;
    // RET;
    return (hp * 2) < maxHP;
}

bool AICheckEnemyQuarterHP(void){
    // PUSH_HL;
    // PUSH_DE;
    // PUSH_BC;
    // LD_HL(wEnemyMonHP);
    uint16_t hp = BigEndianToNative16(wram->wEnemyMon.hp);
    uint16_t maxHP = BigEndianToNative16(wram->wEnemyMon.maxHP);
    // LD_B_hl;
    // INC_HL;
    // LD_C_hl;
    // SLA_C;
    // RL_B;
    // SLA_C;
    // RL_B;
    // INC_HL;
    // INC_HL;
    // LD_A_hld;
    // CP_A_C;
    // LD_A_hl;
    // SBC_A_B;
    // POP_BC;
    // POP_DE;
    // POP_HL;
    // RET;
    return (hp * 4) < maxHP;
}

bool AICheckPlayerQuarterHP(void){
    // PUSH_HL;
    // LD_HL(wBattleMonHP);
    // LD_B_hl;
    // INC_HL;
    // LD_C_hl;
    uint16_t hp = BigEndianToNative16(wram->wBattleMon.hp);
    uint16_t maxHP = BigEndianToNative16(wram->wBattleMon.maxHP);
    // SLA_C;
    // RL_B;
    // SLA_C;
    // RL_B;
    // INC_HL;
    // INC_HL;
    // LD_A_hld;
    // CP_A_C;
    // LD_A_hl;
    // SBC_A_B;
    // POP_HL;
    // RET;
    return (hp * 4) < maxHP;
}

//  Return carry if the enemy has move b.
bool AIHasMoveEffect(uint8_t b){
    // PUSH_HL;
    // LD_HL(wEnemyMonMoves);
    // LD_C(NUM_MOVES);

    for(uint8_t i = 0; i < NUM_MOVES; ++i) {
    // checkmove:
        // LD_A_hli;
        move_t a = wram->wEnemyMon.moves[i];
        // AND_A_A;
        // IF_Z goto no;
        if(a == NO_MOVE)
            return false;

        // CALL(aAIGetEnemyMove);
        const struct Move* mv = AIGetEnemyMove(a);

        // LD_A_addr(wEnemyMoveStruct + MOVE_EFFECT);
        // CP_A_B;
        // IF_Z goto yes;
        if(mv->effect == b)
            return true;

        // DEC_C;
        // IF_NZ goto checkmove;
    }

// no:
    // POP_HL;
    // AND_A_A;
    // RET;
    return false;

// yes:
    // POP_HL;
    // SCF;
    // RET;
}

//  Return carry if the enemy has a move in array hl.
bool AIHasMoveInArray(const move_t* hl){
    // PUSH_HL;
    // PUSH_DE;
    // PUSH_BC;
    move_t a;
    while(a = *(hl++), a != (move_t)-1) {
    // next:
        // LD_A_hli;
        // CP_A(-1);
        // IF_Z goto done;

        // LD_B_A;
        // LD_C(NUM_MOVES + 1);
        uint8_t c = NUM_MOVES + 1;
        // LD_DE(wEnemyMonMoves);
        const move_t* de = wram->wEnemyMon.moves;

    check:
        // DEC_C;
        // IF_Z goto next;
        if(--c != 0)
            continue;

        // LD_A_de;
        // INC_DE;
        // CP_A_B;
        // IF_NZ goto check;
        if(*(de++) != a)
            goto check;

        // SCF;
        return true;
    }

// done:
    // POP_BC;
    // POP_DE;
    // POP_HL;
    // RET;
    return false;
// INCLUDE "data/battle/ai/useful_moves.asm"
}

void AI_Opportunist(void){
//  Discourage stall moves when the enemy's HP is low.

//  Do nothing if enemy's HP is above 50%.
    // CALL(aAICheckEnemyHalfHP);
    // RET_C ;
    if(!AICheckEnemyHalfHP())
        return;

//  Discourage stall moves if enemy's HP is below 25%.
    // CALL(aAICheckEnemyQuarterHP);
    // IF_NC goto lowhp;
    if(!AICheckEnemyQuarterHP()) {

    //  50% chance to discourage stall moves if enemy's HP is between 25% and 50%.
        // CALL(aAI_50_50);
        // RET_C ;
        if(AI_50_50())
            return;
    }

// lowhp:
    // LD_HL(wEnemyAIMoveScores - 1);
    uint8_t* hl = wram->wEnemyAIMoveScores - 1;
    // LD_DE(wEnemyMonMoves);
    const move_t* de = wram->wEnemyMon.moves;
    // LD_C(NUM_MOVES + 1);
    uint8_t c = NUM_MOVES + 1;

    while(++hl, --c != 0) {
    // checkmove:
        // INC_HL;
        // DEC_C;
        // IF_Z goto done;

        // LD_A_de;
        move_t m = *(de++);
        // INC_DE;
        // AND_A_A;
        // IF_Z goto done;
        if(m == NO_MOVE)
            break;

        // PUSH_HL;
        // PUSH_DE;
        // PUSH_BC;
        // LD_HL(mStallMoves);
        // LD_DE(1);
        // CALL(aIsInArray);

        // POP_BC;
        // POP_DE;
        // POP_HL;
        // IF_NC goto checkmove;
        if(IsInMoveArray(StallMoves, m)) {
            (*hl)++;
            // INC_hl;
        }
        // goto checkmove;
    }

// done:
    // RET;

// INCLUDE "data/battle/ai/stall_moves.asm"
}

void AI_Aggressive(void){
//  Use whatever does the most damage.

//  Discourage all damaging moves but the one that does the most damage.
//  If no damaging move deals damage to the player (immune),
//  no move will be discouraged

//  Figure out which attack does the most damage and put it in c.
    // LD_HL(wEnemyMonMoves);
    const move_t* mvs = wram->wEnemyMon.moves;
    // LD_BC(0);
    uint8_t b = 0;
    uint8_t c = 0;
    // LD_DE(0);
    uint16_t de = 0;

    while(++b != NUM_MOVES + 1) {
    // checkmove:
        // INC_B;
        // LD_A_B;
        // CP_A(NUM_MOVES + 1);
        // IF_Z goto gotstrongestmove;

        // LD_A_hli;
        move_t a = *(mvs++);
        // AND_A_A;
        // IF_Z goto gotstrongestmove;
        if(a == NO_MOVE)
            break;

        // PUSH_HL;
        // PUSH_DE;
        // PUSH_BC;
        // CALL(aAIGetEnemyMove);
        const struct Move* mv = AIGetEnemyMove(a);
        // LD_A_addr(wEnemyMoveStruct + MOVE_POWER);
        // AND_A_A;
        // IF_Z goto nodamage;
        if(mv->power == 0) {
        // nodamage:
            // POP_BC;
            // POP_DE;
            // POP_HL;
            // goto checkmove;
            continue;
        }
        // CALL(aAIDamageCalc);
        AIDamageCalc();
        // POP_BC;
        // POP_DE;
        // POP_HL;

    //  Update current move if damage is highest so far
        // LD_A_addr(wCurDamage + 1);
        // CP_A_E;
        // LD_A_addr(wCurDamage);
        // SBC_A_D;
        // IF_C goto checkmove;
        if(BigEndianToNative16(wram->wCurDamage) > de) {
            // LD_A_addr(wCurDamage + 1);
            // LD_E_A;
            // LD_A_addr(wCurDamage);
            // LD_D_A;
            de = BigEndianToNative16(wram->wCurDamage);
            // LD_C_B;
            c = b;
            // goto checkmove;
            continue;
        }
    }

// gotstrongestmove:
//  Nothing we can do if no attacks did damage.
    // LD_A_C;
    // AND_A_A;
    // IF_Z goto done;
    if(c != 0) {
    //  Discourage moves that do less damage unless they're reckless too.
        // LD_HL(wEnemyAIMoveScores - 1);
        uint8_t* hl = wram->wEnemyAIMoveScores - 1;
        // LD_DE(wEnemyMonMoves);
        const move_t* de2 = wram->wEnemyMon.moves;
        // LD_B(0);
        uint8_t b2 = 0;

        while(++b2 != NUM_MOVES + 1) {
        // checkmove2:
            // INC_B;
            // LD_A_B;
            // CP_A(NUM_MOVES + 1);
            // IF_Z goto done;

        //  Ignore this move if it is the highest damaging one.
            // CP_A_C;
            // LD_A_de;
            move_t a2 = *(de2++);
            // INC_DE;
            // INC_HL;
            hl++;
            // IF_Z goto checkmove2;
            if(b == c)
                continue;

            // CALL(aAIGetEnemyMove);
            const struct Move* mv = AIGetEnemyMove(a2);

        //  Ignore this move if its power is 0 or 1.
        //  Moves such as Seismic Toss, Hidden Power,
        //  Counter and Fissure have a base power of 1.
            // LD_A_addr(wEnemyMoveStruct + MOVE_POWER);
            // CP_A(2);
            // IF_C goto checkmove2;
            if(mv->power < 2)
                continue;

        //  Ignore this move if it is reckless.
            // PUSH_HL;
            // PUSH_DE;
            // PUSH_BC;
            // LD_A_addr(wEnemyMoveStruct + MOVE_EFFECT);
            // LD_HL(mRecklessMoves);
            // LD_DE(1);
            // CALL(aIsInArray);
            // POP_BC;
            // POP_DE;
            // POP_HL;
            // IF_C goto checkmove2;
            if(IsInU8Array(RecklessMoves, mv->effect))
                continue;

        //  If we made it this far, discourage this move.
            // INC_hl;
            (*hl)++;
            // goto checkmove2;
        }
    }

// done:
    // RET;

// INCLUDE "data/battle/ai/reckless_moves.asm"

}

void AIDamageCalc(void){
    // LD_A(1);
    // LDH_addr_A(hBattleTurn);
    hram.hBattleTurn = TURN_ENEMY;
    // LD_A_addr(wEnemyMoveStruct + MOVE_EFFECT);
    // LD_DE(1);
    // LD_HL(mConstantDamageEffects);
    // CALL(aIsInArray);
    // IF_NC goto notconstant;
    if(IsInU8Array(ConstantDamageEffects, wram->wEnemyMoveStruct.effect)) {
        // CALLFAR(aBattleCommand_ConstantDamage);
        BattleCommand_ConstantDamage();
        // RET;
    }
    else {
    // notconstant:
        // CALLFAR(aEnemyAttackDamage);
        EnemyAttackDamage(&gBattleCmdState);
        // CALLFAR(aBattleCommand_DamageCalc);
        BattleCommand_DamageCalc();
        // CALLFAR(aBattleCommand_Stab);
        BattleCommand_Stab();
        // RET;
    }
// INCLUDE "data/battle/ai/constant_damage_effects.asm"
}

void AI_Cautious(void){
//  90% chance to discourage moves with residual effects after the first turn.

    // LD_A_addr(wEnemyTurnsTaken);
    // AND_A_A;
    // RET_Z ;
    if(wram->wEnemyTurnsTaken == 0)
        return;

    // LD_HL(wEnemyAIMoveScores - 1);
    uint8_t* hl = wram->wEnemyAIMoveScores;
    // LD_DE(wEnemyMonMoves);
    const move_t* de = wram->wEnemyMon.moves;
    // LD_C(NUM_MOVES + 1);

    for(uint8_t i = 0; i < NUM_MOVES; ++i) {
    // loop:
        // INC_HL;
        // DEC_C;
        // RET_Z ;

        // LD_A_de;
        move_t a = de[i];
        // INC_DE;
        // AND_A_A;
        // RET_Z ;
        if(a == NO_MOVE)
            return;

        // PUSH_HL;
        // PUSH_DE;
        // PUSH_BC;
        // LD_HL(mResidualMoves);
        // LD_DE(1);
        // CALL(aIsInArray);

        // POP_BC;
        // POP_DE;
        // POP_HL;
        // IF_NC goto loop;

        // CALL(aRandom);
        // CP_A(90 percent + 1);
        // RET_NC ;
        
        if(IsInMoveArray(ResidualMoves, a) && Random() < 90 percent + 1) {
            // INC_hl;
            hl[i]++;
        }
        // goto loop;
    }
// INCLUDE "data/battle/ai/residual_moves.asm"
}

void AI_Status(void){
//  Dismiss status moves that don't affect the player.

    // LD_HL(wEnemyAIMoveScores - 1);
    uint8_t* hl = wram->wEnemyAIMoveScores;
    // LD_DE(wEnemyMonMoves);
    const move_t* de = wram->wEnemyMon.moves;
    // LD_B(NUM_MOVES + 1);

    for(uint8_t i = 0; i < NUM_MOVES; ++i) {
    // checkmove:
        // DEC_B;
        // RET_Z ;

        // INC_HL;
        // LD_A_de;
        move_t a = de[i];
        // AND_A_A;
        // RET_Z ;
        if(a == NO_MOVE)
            return;

        // INC_DE;
        // CALL(aAIGetEnemyMove);
        const struct Move* mv = AIGetEnemyMove(a);

        // LD_A_addr(wEnemyMoveStruct + MOVE_EFFECT);
        // CP_A(EFFECT_TOXIC);
        // IF_Z goto poisonimmunity;
        // CP_A(EFFECT_POISON);
        // IF_Z goto poisonimmunity;
        if(mv->effect == EFFECT_TOXIC || mv->effect == EFFECT_POISON) {
        // poisonimmunity:
            // LD_A_addr(wBattleMonType1);
            // CP_A(POISON);
            // IF_Z goto immune;
            // LD_A_addr(wBattleMonType2);
            // CP_A(POISON);
            // IF_Z goto immune;
            if(wram->wBattleMon.type1 == POISON || wram->wBattleMon.type2 == POISON) {
            // immune:
                // CALL(aAIDiscourageMove);
                AIDiscourageMove(hl + i);
                continue;
            }
        }
        // CP_A(EFFECT_SLEEP);
        // IF_Z goto typeimmunity;
        // CP_A(EFFECT_PARALYZE);
        // IF_Z goto typeimmunity;
        else if(mv->effect == EFFECT_SLEEP || mv->effect == EFFECT_PARALYZE) {

        }

        // LD_A_addr(wEnemyMoveStruct + MOVE_POWER);
        // AND_A_A;
        // IF_Z goto checkmove;
        else if(mv->power == 0)
            continue;

        // goto typeimmunity;


    // typeimmunity:
        // PUSH_HL;
        // PUSH_BC;
        // PUSH_DE;
        // LD_A(1);
        // LDH_addr_A(hBattleTurn);
        hram.hBattleTurn = TURN_ENEMY;
        // CALLFAR(aBattleCheckTypeMatchup);
        uint8_t matchup = BattleCheckTypeMatchup();
        // POP_DE;
        // POP_BC;
        // POP_HL;

        // LD_A_addr(wTypeMatchup);
        // AND_A_A;
        // IF_NZ goto checkmove;
        if(matchup == 0) {
        // immune:
            // CALL(aAIDiscourageMove);
            AIDiscourageMove(hl + i);
            continue;
        }
        // goto checkmove;
    }
}

void AI_Risky(void){
//  Use any move that will KO the target.
//  Risky moves will often be an exception (see below).

    // LD_HL(wEnemyAIMoveScores - 1);
    uint8_t* hl = wram->wEnemyAIMoveScores;
    // LD_DE(wEnemyMonMoves);
    const move_t* de = wram->wEnemyMon.moves;
    // LD_C(NUM_MOVES + 1);

    for(uint8_t i = 0; i < NUM_MOVES; ++i) {
    // checkmove:
        // INC_HL;
        // DEC_C;
        // RET_Z ;

        // LD_A_de;
        move_t a = de[i];
        // INC_DE;
        // AND_A_A;
        // RET_Z ;
        if(a == NO_MOVE)
            return;

        // PUSH_DE;
        // PUSH_BC;
        // PUSH_HL;
        // CALL(aAIGetEnemyMove);
        const struct Move* mv = AIGetEnemyMove(a);

        // LD_A_addr(wEnemyMoveStruct + MOVE_POWER);
        // AND_A_A;
        // IF_Z goto nextmove;
        if(mv->power == 0)
            continue;

    //  Don't use risky moves at max hp.
        // LD_A_addr(wEnemyMoveStruct + MOVE_EFFECT);
        // LD_DE(1);
        // LD_HL(mRiskyEffects);
        // CALL(aIsInArray);
        // IF_NC goto checkko;
        if(IsInU8Array(RiskyEffects, mv->effect)) {
            // CALL(aAICheckEnemyMaxHP);
            // IF_C goto nextmove;
            if(AICheckEnemyMaxHP())
                continue;

        //  Else, 80% chance to exclude them.
            // CALL(aRandom);
            // CP_A(79 percent - 1);
            // IF_C goto nextmove;
            if(Random() < 79 percent - 1) {
                continue;
            }
        }

    // checkko:
        // CALL(aAIDamageCalc);
        AIDamageCalc();

        // LD_A_addr(wCurDamage + 1);
        // LD_E_A;
        // LD_A_addr(wCurDamage);
        // LD_D_A;
        uint16_t de = BigEndianToNative16(wram->wCurDamage);
        // LD_A_addr(wBattleMonHP + 1);
        // CP_A_E;
        // LD_A_addr(wBattleMonHP);
        // SBC_A_D;
        uint16_t hp = BigEndianToNative16(wram->wBattleMon.hp);
        // IF_NC goto nextmove;
        if(hp < de) {
            // POP_HL;
            // for(int rept = 0; rept < 5; rept++){
            // DEC_hl;
            *hl -= 5;
            // }
            // PUSH_HL;
        }


    // nextmove:
        // POP_HL;
        // POP_BC;
        // POP_DE;
        // goto checkmove;
    }
// INCLUDE "data/battle/ai/risky_effects.asm"
}

void AI_None(void){
    // RET;
}

static void AIDiscourageMove(uint8_t* hl){
    // LD_A_hl;
    // ADD_A(10);
    // LD_hl_A;
    *hl += 10;
    // RET;
}

//  Load attributes of move a into ram
static const struct Move* AIGetEnemyMove(move_t a){
    // PUSH_HL;
    // PUSH_DE;
    // PUSH_BC;
    // DEC_A;
    // LD_HL(mMoves);
    // LD_BC(MOVE_LENGTH);
    // CALL(aAddNTimes);

    // LD_DE(wEnemyMoveStruct);
    // LD_A(BANK(aMoves));
    // CALL(aFarCopyBytes);
    CopyBytes(&wram->wEnemyMoveStruct, Moves + a, sizeof(wram->wEnemyMoveStruct));

    // POP_BC;
    // POP_DE;
    // POP_HL;
    // RET;
    return &wram->wEnemyMoveStruct;
}

// 20% chance to return carry/true.
// 80% chance to return nc/false
static bool AI_80_20(void){
    // CALL(aRandom);
    // CP_A(20 percent - 1);
    // RET;
    return Random() < 20 percent - 1;
}

// 50% chance to return carry/true.
// 50% chance to return nc/false
static bool AI_50_50(void){
    // CALL(aRandom);
    // CP_A(50 percent + 1);
    // RET;
    return Random() < 50 percent + 1;
}
