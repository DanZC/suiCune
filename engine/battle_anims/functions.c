#include "../../constants.h"
#include "functions.h"
#include "core.h"
#include "helpers.h"
#include "../math/sine.h"
#include "../../data/battle_anims/ball_colors.h"

void DoBattleAnimFrame(void) {
    SET_PC(aDoBattleAnimFrame);
    LD_HL(BATTLEANIMSTRUCT_FUNCTION);
    ADD_HL_BC;
    LD_E_hl;
    LD_D(0);
    struct BattleAnim* bc = wram->wAnimObject + ((REG_BC - wAnimObject1) / sizeof(wram->wAnimObject[0]));
    // LD_HL(mDoBattleAnimFrame_Jumptable);
    // ADD_HL_DE;
    // ADD_HL_DE;
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // JP_hl;
    switch(REG_DE) {
        case BATTLEANIMFUNC_NULL: // CALL(aBattleAnimFunction_Null); break;
        case BATTLEANIMFUNC_USER_TO_TARGET: // CALL(aBattleAnimFunction_MoveFromUserToTarget); break;
        case BATTLEANIMFUNC_USER_TO_TARGET_DISAPPEAR: // CALL(aBattleAnimFunction_MoveFromUserToTargetAndDisappear); break;
        case BATTLEANIMFUNC_MOVE_IN_CIRCLE: // CALL(aBattleAnimFunction_MoveInCircle); break;
        case BATTLEANIMFUNC_WAVE_TO_TARGET: // CALL(aBattleAnimFunction_MoveWaveToTarget); break;
        case BATTLEANIMFUNC_THROW_TO_TARGET: // CALL(aBattleAnimFunction_ThrowFromUserToTarget); break;
        case BATTLEANIMFUNC_THROW_TO_TARGET_DISAPPEAR: // CALL(aBattleAnimFunction_ThrowFromUserToTargetAndDisappear); break;
        case BATTLEANIMFUNC_DROP: // CALL(aBattleAnimFunction_Drop); break;
        case BATTLEANIMFUNC_USER_TO_TARGET_SPIN: // CALL(aBattleAnimFunction_MoveFromUserToTargetSpinAround); break;
        case BATTLEANIMFUNC_SHAKE: // CALL(aBattleAnimFunction_Shake); break;
        case BATTLEANIMFUNC_FIRE_BLAST: // CALL(aBattleAnimFunction_FireBlast); break;
        case BATTLEANIMFUNC_RAZOR_LEAF: // CALL(aBattleAnimFunction_RazorLeaf); break;
        case BATTLEANIMFUNC_BUBBLE: // CALL(aBattleAnimFunction_Bubble); break;
        case BATTLEANIMFUNC_SURF: // CALL(aBattleAnimFunction_Surf); break;
        case BATTLEANIMFUNC_SING: // CALL(aBattleAnimFunction_Sing); break;
        case BATTLEANIMFUNC_WATER_GUN: // CALL(aBattleAnimFunction_WaterGun); break;
        case BATTLEANIMFUNC_EMBER: // CALL(aBattleAnimFunction_Ember); break;
        case BATTLEANIMFUNC_POWDER: // CALL(aBattleAnimFunction_Powder); break;
        case BATTLEANIMFUNC_POKEBALL: // CALL(aBattleAnimFunction_PokeBall); break;
        case BATTLEANIMFUNC_POKEBALL_BLOCKED: // CALL(aBattleAnimFunction_PokeBallBlocked); break;
        case BATTLEANIMFUNC_RECOVER: // CALL(aBattleAnimFunction_Recover); break;
        case BATTLEANIMFUNC_THUNDER_WAVE: // CALL(aBattleAnimFunction_ThunderWave); break;
        case BATTLEANIMFUNC_CLAMP_ENCORE: // CALL(aBattleAnimFunction_Clamp_Encore); break;
        case BATTLEANIMFUNC_BITE: // CALL(aBattleAnimFunction_Bite); break;
        case BATTLEANIMFUNC_SOLAR_BEAM: // CALL(aBattleAnimFunction_SolarBeam); break;
        case BATTLEANIMFUNC_GUST: // CALL(aBattleAnimFunction_Gust); break;
        case BATTLEANIMFUNC_RAZOR_WIND: // CALL(aBattleAnimFunction_RazorWind); break;
        case BATTLEANIMFUNC_KICK: //CALL(aBattleAnimFunction_Kick); break;
        case BATTLEANIMFUNC_ABSORB: //CALL(aBattleAnimFunction_Absorb); break;
        case BATTLEANIMFUNC_EGG: //CALL(aBattleAnimFunction_Egg); break;
        case BATTLEANIMFUNC_MOVE_UP: //CALL(aBattleAnimFunction_MoveUp); break;
        case BATTLEANIMFUNC_WRAP: //CALL(aBattleAnimFunction_Wrap); break;
        case BATTLEANIMFUNC_LEECH_SEED: //CALL(aBattleAnimFunction_LeechSeed); break;
        case BATTLEANIMFUNC_SOUND: //CALL(aBattleAnimFunction_Sound); break;
        case BATTLEANIMFUNC_CONFUSE_RAY: //CALL(aBattleAnimFunction_ConfuseRay); break;
        case BATTLEANIMFUNC_DIZZY: //CALL(aBattleAnimFunction_Dizzy); break;
        case BATTLEANIMFUNC_AMNESIA: //CALL(aBattleAnimFunction_Amnesia); break;
        case BATTLEANIMFUNC_FLOAT_UP: //CALL(aBattleAnimFunction_FloatUp); break;
        case BATTLEANIMFUNC_DIG: //CALL(aBattleAnimFunction_Dig); break;
        case BATTLEANIMFUNC_STRING: //CALL(aBattleAnimFunction_String); break;
        case BATTLEANIMFUNC_PARALYZED: //CALL(aBattleAnimFunction_Paralyzed); break;
        case BATTLEANIMFUNC_SPIRAL_DESCENT: //CALL(aBattleAnimFunction_SpiralDescent); break;
        case BATTLEANIMFUNC_POISON_GAS: //CALL(aBattleAnimFunction_PoisonGas); break;
        case BATTLEANIMFUNC_HORN: //CALL(aBattleAnimFunction_Horn); break;
        case BATTLEANIMFUNC_NEEDLE: //CALL(aBattleAnimFunction_Needle); break;
        case BATTLEANIMFUNC_PETAL_DANCE: //CALL(aBattleAnimFunction_PetalDance); break;
        case BATTLEANIMFUNC_THIEF_PAYDAY: //CALL(aBattleAnimFunction_ThiefPayday); break;
        case BATTLEANIMFUNC_ABSORB_CIRCLE: //CALL(aBattleAnimFunction_AbsorbCircle); break;
        case BATTLEANIMFUNC_BONEMERANG: //CALL(aBattleAnimFunction_Bonemerang); break;
        case BATTLEANIMFUNC_SHINY: //CALL(aBattleAnimFunction_Shiny); break;
        case BATTLEANIMFUNC_SKY_ATTACK: //CALL(aBattleAnimFunction_SkyAttack); break;
        case BATTLEANIMFUNC_GROWTH_SWORDS_DANCE: //CALL(aBattleAnimFunction_GrowthSwordsDance); break;
        case BATTLEANIMFUNC_SMOKE_FLAME_WHEEL: //CALL(aBattleAnimFunction_SmokeFlameWheel); break;
        case BATTLEANIMFUNC_PRESENT_SMOKESCREEN: //CALL(aBattleAnimFunction_PresentSmokescreen); break;
        case BATTLEANIMFUNC_STRENGTH_SEISMIC_TOSS: //CALL(aBattleAnimFunction_StrengthSeismicToss); break;
        case BATTLEANIMFUNC_SPEED_LINE: //CALL(aBattleAnimFunction_SpeedLine); break;
        case BATTLEANIMFUNC_SLUDGE: //CALL(aBattleAnimFunction_Sludge); break;
        case BATTLEANIMFUNC_METRONOME_HAND: //CALL(aBattleAnimFunction_MetronomeHand); break;
        case BATTLEANIMFUNC_METRONOME_SPARKLE_SKETCH: //CALL(aBattleAnimFunction_MetronomeSparkleSketch); break;
        case BATTLEANIMFUNC_AGILITY: //CALL(aBattleAnimFunction_Agility); break;
        case BATTLEANIMFUNC_SACRED_FIRE: //CALL(aBattleAnimFunction_SacredFire); break;
        case BATTLEANIMFUNC_SAFEGUARD_PROTECT: //CALL(aBattleAnimFunction_SafeguardProtect); break;
        case BATTLEANIMFUNC_LOCK_ON_MIND_READER: //CALL(aBattleAnimFunction_LockOnMindReader); break;
        case BATTLEANIMFUNC_SPIKES: //CALL(aBattleAnimFunction_Spikes); break;
        case BATTLEANIMFUNC_HEAL_BELL_NOTES: //CALL(aBattleAnimFunction_HealBellNotes); break;
        case BATTLEANIMFUNC_BATON_PASS: //CALL(aBattleAnimFunction_BatonPass); break;
        case BATTLEANIMFUNC_CONVERSION: //CALL(aBattleAnimFunction_Conversion); break;
        case BATTLEANIMFUNC_ENCORE_BELLY_DRUM: //CALL(aBattleAnimFunction_EncoreBellyDrum); break;
        case BATTLEANIMFUNC_SWAGGER_MORNING_SUN: // CALL(aBattleAnimFunction_SwaggerMorningSun); break;
        case BATTLEANIMFUNC_HIDDEN_POWER: // CALL(aBattleAnimFunction_HiddenPower); break;
        case BATTLEANIMFUNC_CURSE: // CALL(aBattleAnimFunction_Curse); break;
        case BATTLEANIMFUNC_PERISH_SONG: // CALL(aBattleAnimFunction_PerishSong); break;
        case BATTLEANIMFUNC_RAPID_SPIN: // CALL(aBattleAnimFunction_RapidSpin); break;
        case BATTLEANIMFUNC_BETA_PURSUIT: // CALL(aBattleAnimFunction_BetaPursuit); break;
        case BATTLEANIMFUNC_RAIN_SANDSTORM: // CALL(aBattleAnimFunction_RainSandstorm); break;
            DoBattleAnimFrame_Conv(bc); break;
        case BATTLEANIMFUNC_ANIM_OBJ_B0: CALL(aBattleAnimFunction_AnimObjB0); break;
        case BATTLEANIMFUNC_PSYCH_UP: // CALL(aBattleAnimFunction_PsychUp); break;
        case BATTLEANIMFUNC_ANCIENT_POWER: // CALL(aBattleAnimFunction_AncientPower); break;
        case BATTLEANIMFUNC_ROCK_SMASH: // CALL(aBattleAnimFunction_RockSmash); break;
        case BATTLEANIMFUNC_COTTON: // CALL(aBattleAnimFunction_Cotton); break;
            DoBattleAnimFrame_Conv(bc); break;
        default: break;
    }
    RET;

Jumptable:

    //  entries correspond to BATTLEANIMFUNC_* constants
    // dw ['BattleAnimFunction_Null'];
    // dw ['BattleAnimFunction_MoveFromUserToTarget'];
    // dw ['BattleAnimFunction_MoveFromUserToTargetAndDisappear'];
    // dw ['BattleAnimFunction_MoveInCircle'];
    // dw ['BattleAnimFunction_MoveWaveToTarget'];
    // dw ['BattleAnimFunction_ThrowFromUserToTarget'];
    // dw ['BattleAnimFunction_ThrowFromUserToTargetAndDisappear'];
    // dw ['BattleAnimFunction_Drop'];
    // dw ['BattleAnimFunction_MoveFromUserToTargetSpinAround'];
    // dw ['BattleAnimFunction_Shake'];
    // dw ['BattleAnimFunction_FireBlast'];
    // dw ['BattleAnimFunction_RazorLeaf'];
    // dw ['BattleAnimFunction_Bubble'];
    // dw ['BattleAnimFunction_Surf'];
    // dw ['BattleAnimFunction_Sing'];
    // dw ['BattleAnimFunction_WaterGun'];
    // dw ['BattleAnimFunction_Ember'];
    // dw ['BattleAnimFunction_Powder'];
    // dw ['BattleAnimFunction_PokeBall'];
    // dw ['BattleAnimFunction_PokeBallBlocked'];
    // dw ['BattleAnimFunction_Recover'];
    // dw ['BattleAnimFunction_ThunderWave'];
    // dw ['BattleAnimFunction_Clamp_Encore'];
    // dw ['BattleAnimFunction_Bite'];
    // dw ['BattleAnimFunction_SolarBeam'];
    // dw ['BattleAnimFunction_Gust'];
    // dw ['BattleAnimFunction_RazorWind'];
    // dw ['BattleAnimFunction_Kick'];
    // dw ['BattleAnimFunction_Absorb'];
    // dw ['BattleAnimFunction_Egg'];
    // dw ['BattleAnimFunction_MoveUp'];
    // dw ['BattleAnimFunction_Wrap'];
    // dw ['BattleAnimFunction_LeechSeed'];
    // dw ['BattleAnimFunction_Sound'];
    // dw ['BattleAnimFunction_ConfuseRay'];
    // dw ['BattleAnimFunction_Dizzy'];
    // dw ['BattleAnimFunction_Amnesia'];
    // dw ['BattleAnimFunction_FloatUp'];
    // dw ['BattleAnimFunction_Dig'];
    // dw ['BattleAnimFunction_String'];
    // dw ['BattleAnimFunction_Paralyzed'];
    // dw ['BattleAnimFunction_SpiralDescent'];
    // dw ['BattleAnimFunction_PoisonGas'];
    // dw ['BattleAnimFunction_Horn'];
    // dw ['BattleAnimFunction_Needle'];
    // dw ['BattleAnimFunction_PetalDance'];
    // dw ['BattleAnimFunction_ThiefPayday'];
    // dw ['BattleAnimFunction_AbsorbCircle'];
    // dw ['BattleAnimFunction_Bonemerang'];
    // dw ['BattleAnimFunction_Shiny'];
    // dw ['BattleAnimFunction_SkyAttack'];
    // dw ['BattleAnimFunction_GrowthSwordsDance'];
    // dw ['BattleAnimFunction_SmokeFlameWheel'];
    // dw ['BattleAnimFunction_PresentSmokescreen'];
    // dw ['BattleAnimFunction_StrengthSeismicToss'];
    // dw ['BattleAnimFunction_SpeedLine'];
    // dw ['BattleAnimFunction_Sludge'];
    // dw ['BattleAnimFunction_MetronomeHand'];
    // dw ['BattleAnimFunction_MetronomeSparkleSketch'];
    // dw ['BattleAnimFunction_Agility'];
    // dw ['BattleAnimFunction_SacredFire'];
    // dw ['BattleAnimFunction_SafeguardProtect'];
    // dw ['BattleAnimFunction_LockOnMindReader'];
    // dw ['BattleAnimFunction_Spikes'];
    // dw ['BattleAnimFunction_HealBellNotes'];
    // dw ['BattleAnimFunction_BatonPass'];
    // dw ['BattleAnimFunction_Conversion'];
    // dw ['BattleAnimFunction_EncoreBellyDrum'];
    // dw ['BattleAnimFunction_SwaggerMorningSun'];
    // dw ['BattleAnimFunction_HiddenPower'];
    // dw ['BattleAnimFunction_Curse'];
    // dw ['BattleAnimFunction_PerishSong'];
    // dw ['BattleAnimFunction_RapidSpin'];
    // dw ['BattleAnimFunction_BetaPursuit'];
    // dw ['BattleAnimFunction_RainSandstorm'];
    // dw ['BattleAnimFunction_AnimObjB0'];
    // dw ['BattleAnimFunction_PsychUp'];
    // dw ['BattleAnimFunction_AncientPower'];
    // dw ['BattleAnimFunction_RockSmash'];
    // dw ['BattleAnimFunction_Cotton'];
}

void DoBattleAnimFrame_Conv(struct BattleAnim* bc) {
    // SET_PC(aDoBattleAnimFrame);
    // LD_HL(BATTLEANIMSTRUCT_FUNCTION);
    // ADD_HL_BC;
    // LD_E_hl;
    // LD_D(0);
    // LD_HL(mDoBattleAnimFrame_Jumptable);
    // ADD_HL_DE;
    // ADD_HL_DE;
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // JP_hl;
    switch(bc->function) {
        case BATTLEANIMFUNC_NULL:                       BattleAnimFunction_Null(bc); break;
        case BATTLEANIMFUNC_USER_TO_TARGET:             BattleAnimFunction_MoveFromUserToTarget(bc); break;
        case BATTLEANIMFUNC_USER_TO_TARGET_DISAPPEAR:   BattleAnimFunction_MoveFromUserToTargetAndDisappear(bc); break;
        case BATTLEANIMFUNC_MOVE_IN_CIRCLE:             BattleAnimFunction_MoveInCircle(bc); break;
        case BATTLEANIMFUNC_WAVE_TO_TARGET:             BattleAnimFunction_MoveWaveToTarget(bc); break;
        case BATTLEANIMFUNC_THROW_TO_TARGET:            BattleAnimFunction_ThrowFromUserToTarget(bc); break;
        case BATTLEANIMFUNC_THROW_TO_TARGET_DISAPPEAR:  BattleAnimFunction_ThrowFromUserToTargetAndDisappear(bc); break;
        case BATTLEANIMFUNC_DROP:                       BattleAnimFunction_Drop(bc); break;
        case BATTLEANIMFUNC_USER_TO_TARGET_SPIN:        BattleAnimFunction_MoveFromUserToTargetSpinAround(bc); break;
        case BATTLEANIMFUNC_SHAKE:                      BattleAnimFunction_Shake(bc); break;
        case BATTLEANIMFUNC_FIRE_BLAST:                 BattleAnimFunction_FireBlast(bc); break;
        case BATTLEANIMFUNC_RAZOR_LEAF:                 BattleAnimFunction_RazorLeaf(bc); break;
        case BATTLEANIMFUNC_BUBBLE:                     BattleAnimFunction_Bubble(bc); break;
        case BATTLEANIMFUNC_SURF:                       BattleAnimFunction_Surf(bc); break;
        case BATTLEANIMFUNC_SING:                       BattleAnimFunction_Sing(bc); break;
        case BATTLEANIMFUNC_WATER_GUN:                  BattleAnimFunction_WaterGun(bc); break;
        case BATTLEANIMFUNC_EMBER:                      BattleAnimFunction_Ember(bc); break;
        case BATTLEANIMFUNC_POWDER:                     BattleAnimFunction_Powder(bc); break;
        case BATTLEANIMFUNC_POKEBALL:                   BattleAnimFunction_PokeBall(bc); break;
        case BATTLEANIMFUNC_POKEBALL_BLOCKED:           BattleAnimFunction_PokeBallBlocked(bc); break;
        case BATTLEANIMFUNC_RECOVER:                    BattleAnimFunction_Recover(bc); break;
        case BATTLEANIMFUNC_THUNDER_WAVE:               BattleAnimFunction_ThunderWave(bc); break;
        case BATTLEANIMFUNC_CLAMP_ENCORE:               BattleAnimFunction_Clamp_Encore(bc); break;
        case BATTLEANIMFUNC_BITE:                       BattleAnimFunction_Bite(bc); break;
        case BATTLEANIMFUNC_SOLAR_BEAM:                 BattleAnimFunction_SolarBeam(bc); break;
        case BATTLEANIMFUNC_GUST:                       BattleAnimFunction_Gust(bc); break;
        case BATTLEANIMFUNC_RAZOR_WIND:                 BattleAnimFunction_RazorWind(bc); break;
        case BATTLEANIMFUNC_KICK:                       BattleAnimFunction_Kick(bc); break;
        case BATTLEANIMFUNC_ABSORB:                     BattleAnimFunction_Absorb(bc); break;
        case BATTLEANIMFUNC_EGG:                        BattleAnimFunction_Egg(bc); break;
        case BATTLEANIMFUNC_MOVE_UP:                    BattleAnimFunction_MoveUp(bc); break;
        case BATTLEANIMFUNC_WRAP:                       BattleAnimFunction_Wrap(bc); break;
        case BATTLEANIMFUNC_LEECH_SEED:                 BattleAnimFunction_LeechSeed(bc); break;
        case BATTLEANIMFUNC_SOUND:                      BattleAnimFunction_Sound(bc); break;
        case BATTLEANIMFUNC_CONFUSE_RAY:                BattleAnimFunction_ConfuseRay(bc); break;
        case BATTLEANIMFUNC_DIZZY:                      BattleAnimFunction_Dizzy(bc); break;
        case BATTLEANIMFUNC_AMNESIA:                    BattleAnimFunction_Amnesia(bc); break;
        case BATTLEANIMFUNC_FLOAT_UP:                   BattleAnimFunction_FloatUp(bc); break;
        case BATTLEANIMFUNC_DIG:                        BattleAnimFunction_Dig(bc); break;
        case BATTLEANIMFUNC_STRING:                     BattleAnimFunction_String(bc); break;
        case BATTLEANIMFUNC_PARALYZED:                  BattleAnimFunction_Paralyzed(bc); break;
        case BATTLEANIMFUNC_SPIRAL_DESCENT:             BattleAnimFunction_SpiralDescent(bc); break;
        case BATTLEANIMFUNC_POISON_GAS:                 BattleAnimFunction_PoisonGas(bc); break;
        case BATTLEANIMFUNC_HORN:                       BattleAnimFunction_Horn(bc); break;
        case BATTLEANIMFUNC_NEEDLE:                     BattleAnimFunction_Needle(bc); break;
        case BATTLEANIMFUNC_PETAL_DANCE:                BattleAnimFunction_PetalDance(bc); break;
        case BATTLEANIMFUNC_THIEF_PAYDAY:               BattleAnimFunction_ThiefPayday(bc); break;
        case BATTLEANIMFUNC_ABSORB_CIRCLE:              BattleAnimFunction_AbsorbCircle(bc); break;
        case BATTLEANIMFUNC_BONEMERANG:                 BattleAnimFunction_Bonemerang(bc); break;
        case BATTLEANIMFUNC_SHINY:                      BattleAnimFunction_Shiny(bc); break;
        case BATTLEANIMFUNC_SKY_ATTACK:                 BattleAnimFunction_SkyAttack(bc); break;
        case BATTLEANIMFUNC_GROWTH_SWORDS_DANCE:        BattleAnimFunction_GrowthSwordsDance(bc); break;
        case BATTLEANIMFUNC_SMOKE_FLAME_WHEEL:          BattleAnimFunction_SmokeFlameWheel(bc); break;
        case BATTLEANIMFUNC_PRESENT_SMOKESCREEN:        BattleAnimFunction_PresentSmokescreen(bc); break;
        case BATTLEANIMFUNC_STRENGTH_SEISMIC_TOSS:      BattleAnimFunction_StrengthSeismicToss(bc); break;
        case BATTLEANIMFUNC_SPEED_LINE:                 BattleAnimFunction_SpeedLine(bc); break;
        case BATTLEANIMFUNC_SLUDGE:                     BattleAnimFunction_Sludge(bc); break;
        case BATTLEANIMFUNC_METRONOME_HAND:             BattleAnimFunction_MetronomeHand(bc); break;
        case BATTLEANIMFUNC_METRONOME_SPARKLE_SKETCH:   BattleAnimFunction_MetronomeSparkleSketch(bc); break;
        case BATTLEANIMFUNC_AGILITY:                    BattleAnimFunction_Agility(bc); break;
        case BATTLEANIMFUNC_SACRED_FIRE:                BattleAnimFunction_SacredFire(bc); break;
        case BATTLEANIMFUNC_SAFEGUARD_PROTECT:          BattleAnimFunction_SafeguardProtect(bc); break;
        case BATTLEANIMFUNC_LOCK_ON_MIND_READER:        BattleAnimFunction_LockOnMindReader(bc); break;
        case BATTLEANIMFUNC_SPIKES:                     BattleAnimFunction_Spikes(bc); break;
        case BATTLEANIMFUNC_HEAL_BELL_NOTES:            BattleAnimFunction_HealBellNotes(bc); break;
        case BATTLEANIMFUNC_BATON_PASS:                 BattleAnimFunction_BatonPass(bc); break;
        case BATTLEANIMFUNC_CONVERSION:                 BattleAnimFunction_Conversion(bc); break;
        case BATTLEANIMFUNC_ENCORE_BELLY_DRUM:          BattleAnimFunction_EncoreBellyDrum(bc); break;
        case BATTLEANIMFUNC_SWAGGER_MORNING_SUN:        BattleAnimFunction_SwaggerMorningSun(bc); break;
        case BATTLEANIMFUNC_HIDDEN_POWER:               BattleAnimFunction_HiddenPower(bc); break;
        case BATTLEANIMFUNC_CURSE:                      BattleAnimFunction_Curse(bc); break;
        case BATTLEANIMFUNC_PERISH_SONG:                BattleAnimFunction_PerishSong(bc); break;
        case BATTLEANIMFUNC_RAPID_SPIN:                 BattleAnimFunction_RapidSpin(bc); break;
        case BATTLEANIMFUNC_BETA_PURSUIT:               BattleAnimFunction_BetaPursuit(bc); break;
        case BATTLEANIMFUNC_RAIN_SANDSTORM:             BattleAnimFunction_RainSandstorm(bc); break;
        // case BATTLEANIMFUNC_ANIM_OBJ_B0: CALL(aBattleAnimFunction_AnimObjB0); break; // unused
        case BATTLEANIMFUNC_PSYCH_UP:                   BattleAnimFunction_PsychUp(bc); break;
        case BATTLEANIMFUNC_ANCIENT_POWER:              BattleAnimFunction_AncientPower(bc); break;
        case BATTLEANIMFUNC_ROCK_SMASH:                 BattleAnimFunction_RockSmash(bc); break;
        case BATTLEANIMFUNC_COTTON:                     BattleAnimFunction_Cotton(bc); break;
        default: break;
    }
    // RET;
}

void BattleAnimFunction_Null(struct BattleAnim* bc) {
    // SET_PC(aBattleAnimFunction_Null);
    // CALL(aBattleAnim_AnonJumptable);

// anon_dw:

    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 0) goto zero;
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 1) goto one;
    switch(bc->jumptableIndex) {
    case 1:
    // one:
        // CALL(aDeinitBattleAnimation);
        DeinitBattleAnimation_Conv(bc);
        fallthrough;

    default:
    case 0:
    // zero:
        // RET;
        return;
    }
}

void BattleAnimFunction_ThrowFromUserToTargetAndDisappear(struct BattleAnim* bc) {
    // SET_PC(aBattleAnimFunction_ThrowFromUserToTargetAndDisappear);
    // CALL(aBattleAnimFunction_ThrowFromUserToTarget);
    // RET_C;
    if(BattleAnimFunction_ThrowFromUserToTarget(bc))
        return;
    // CALL(aDeinitBattleAnimation);
    DeinitBattleAnimation_Conv(bc);
    // RET;
}

bool BattleAnimFunction_ThrowFromUserToTarget(struct BattleAnim* bc) {
    // SET_PC(aBattleAnimFunction_ThrowFromUserToTarget);
    // If x coord at $88 or beyond, abort.
    // LD_HL(BATTLEANIMSTRUCT_XCOORD);
    // ADD_HL_BC;
    // LD_A_hl;
    // CP_A(0x88);
    // RET_NC;
    if(bc->xCoord >= 0x88)
        return false;
    // Move right 2 pixels
    // ADD_A(0x2);
    // LD_hl_A;
    bc->xCoord += 2;
    // Move down 1 pixel
    // LD_HL(BATTLEANIMSTRUCT_YCOORD);
    // ADD_HL_BC;
    // DEC_hl;
    bc->yCoord--;
    // Decrease var1 and hold onto its previous value (argument of the sine function)
    // LD_HL(BATTLEANIMSTRUCT_VAR1);
    // ADD_HL_BC;
    // LD_A_hl;
    // DEC_hl;
    uint8_t var1 = bc->var1--;
    // Get param (amplitude of the sine function)
    // LD_HL(BATTLEANIMSTRUCT_PARAM);
    // ADD_HL_BC;
    // LD_D_hl;
    // CALL(aBattleAnim_Sine);
    // Store the sine result in the Y offset
    // LD_HL(BATTLEANIMSTRUCT_YOFFSET);
    // ADD_HL_BC;
    // LD_hl_A;
    bc->yOffset = BattleAnim_Sine_Conv(var1, bc->param);
    // Carry flag denotes success
    // SCF;
    // RET;
    return true;
}

//  Wave motion from one mon to another. Obj is cleared when it reaches x coord $88. Examples: Shadow Ball, Dragon Rage
void BattleAnimFunction_MoveWaveToTarget(struct BattleAnim* bc) {
    // SET_PC(aBattleAnimFunction_MoveWaveToTarget);
    // LD_HL(BATTLEANIMSTRUCT_XCOORD);
    // ADD_HL_BC;
    // LD_A_hl;
    // CP_A(0x88);
    // IF_C goto move;
    if(bc->xCoord >= 0x88) {
        // CALL(aDeinitBattleAnimation);
        DeinitBattleAnimation_Conv(bc);
        // RET;
        return;
    }

// move:
    // ADD_A(0x2);
    // LD_hl_A;
    bc->xCoord += 0x2;
    // LD_HL(BATTLEANIMSTRUCT_YCOORD);
    // ADD_HL_BC;
    // DEC_hl;
    bc->yCoord--;
    // LD_HL(BATTLEANIMSTRUCT_VAR1);
    // ADD_HL_BC;
    // LD_A_hl;
    uint8_t var1 = bc->var1;
    // INC_hl;
    // INC_hl;
    // INC_hl;
    // INC_hl;
    bc->var1 += 4;
    // LD_D(0x10);
    // PUSH_AF;
    // PUSH_DE;
    // CALL(aBattleAnim_Sine);
    // LD_HL(BATTLEANIMSTRUCT_YOFFSET);
    // ADD_HL_BC;
    // LD_hl_A;
    bc->yOffset = BattleAnim_Sine_Conv(var1, 0x10);
    // POP_DE;
    // POP_AF;
    // CALL(aBattleAnim_Cosine);
    int8_t res = (int8_t)BattleAnim_Cosine_Conv(var1, 0x10);
    // LD_HL(BATTLEANIMSTRUCT_XOFFSET);
    // ADD_HL_BC;
    // SRA_A;
    // SRA_A;
    // SRA_A;
    // SRA_A;
    // LD_hl_A;
    bc->xOffset = res >> 4;
    // RET;
}

//  Slow circular motion. Examples: Thundershock, Flamethrower
//  Obj Param: Distance from center (masked with $7F). Bit 7 causes object to start on other side of the circle
void BattleAnimFunction_MoveInCircle(struct BattleAnim* bc) {
    // SET_PC(aBattleAnimFunction_MoveInCircle);
    // CALL(aBattleAnim_AnonJumptable);

// anon_dw:

    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 0) goto zero;
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 1) goto one;
    switch(bc->jumptableIndex) {
    default:
    case 0:
    // zero:
        // CALL(aBattleAnim_IncAnonJumptableIndex);
        bc->jumptableIndex++;
        // LD_HL(BATTLEANIMSTRUCT_PARAM);
        // ADD_HL_BC;
        // BIT_hl(7);
        // LD_A(0x0);
        // IF_Z goto got_starting_position;
        // LD_A(0x20);

    // got_starting_position:
        // LD_HL(BATTLEANIMSTRUCT_VAR1);
        // ADD_HL_BC;
        // LD_hl_A;
        bc->var1 = (bit_test(bc->param, 7))? 0x20: 0x0;
        // LD_HL(BATTLEANIMSTRUCT_PARAM);
        // ADD_HL_BC;
        // LD_A_hl;
        // AND_A(0x7f);
        // LD_hl_A;
        bc->param &= 0x7f;
        fallthrough;

    case 1:
    // one:
        // LD_HL(BATTLEANIMSTRUCT_VAR1);
        // ADD_HL_BC;
        // LD_A_hl;
        // LD_HL(BATTLEANIMSTRUCT_PARAM);
        // ADD_HL_BC;
        // LD_D_hl;
        // PUSH_AF;
        // PUSH_DE;
        // CALL(aBattleAnim_Sine);
        // LD_HL(BATTLEANIMSTRUCT_YOFFSET);
        // ADD_HL_BC;
        // LD_hl_A;
        bc->yOffset = BattleAnim_Sine_Conv(bc->var1, bc->param);
        // POP_DE;
        // POP_AF;
        // CALL(aBattleAnim_Cosine);
        // LD_HL(BATTLEANIMSTRUCT_XOFFSET);
        // ADD_HL_BC;
        // LD_hl_A;
        bc->xOffset = BattleAnim_Cosine_Conv(bc->var1, bc->param);
        // LD_HL(BATTLEANIMSTRUCT_VAR1);
        // ADD_HL_BC;
        // INC_hl;
        bc->var1++;
        // RET;
        return;
    }
}

void BattleAnimFunction_MoveFromUserToTarget(struct BattleAnim* bc) {
    // SET_PC(aBattleAnimFunction_MoveFromUserToTarget);
    //  Moves object diagonally at a ~30° angle towards opponent and stops when it reaches x coord $84. Obj Param changes the speed
    // CALL(aBattleAnim_AnonJumptable);

// anon_dw:

    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 0) goto zero;
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 1) goto one;
    switch(bc->jumptableIndex) {
    default:
    case 1:
    // one:
        // CALL(aDeinitBattleAnimation);
        DeinitBattleAnimation_Conv(bc);
        // RET;
        return;

    case 0:
    // zero:
        // LD_HL(BATTLEANIMSTRUCT_XCOORD);
        // ADD_HL_BC;
        // LD_A_hl;
        // CP_A(0x84);
        // RET_NC;
        if(bc->xCoord >= 0x84)
            return;
        // LD_HL(BATTLEANIMSTRUCT_PARAM);
        // ADD_HL_BC;
        // LD_A_hl;
        // CALL(aBattleAnim_StepToTarget);
        BattleAnim_StepToTarget(bc, bc->param);
        // RET;
        return;
    }
}

void BattleAnimFunction_MoveFromUserToTargetAndDisappear(struct BattleAnim* bc) {
    // SET_PC(aBattleAnimFunction_MoveFromUserToTargetAndDisappear);
    //  Same as BattleAnimFunction_01 but objs are cleared when they reach x coord $84
    // LD_HL(BATTLEANIMSTRUCT_XCOORD);
    // ADD_HL_BC;
    // LD_A_hl;
    // CP_A(0x84);
    // IF_NC goto done;
    if(bc->xCoord >= 0x84) {
    // done:
        // CALL(aDeinitBattleAnimation);
        DeinitBattleAnimation_Conv(bc);
        // RET;
        return;
    }

    // LD_HL(BATTLEANIMSTRUCT_PARAM);
    // ADD_HL_BC;
    // LD_A_hl;
    // CALL(aBattleAnim_StepToTarget);
    BattleAnim_StepToTarget(bc, bc->param);
    // RET;
}

void BattleAnimFunction_PokeBall(struct BattleAnim* bc) {
    // SET_PC(aBattleAnimFunction_PokeBall);
    // CALL(aBattleAnim_AnonJumptable);

// anon_dw:

    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 0) goto zero;
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 1) goto one;
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 2) goto two;
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 3) goto three;
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 4) goto four;
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 5) goto five;
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 6) goto six;
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 7) goto seven;
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 8) goto eight;
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 9) goto nine;
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 10) goto ten;
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 11) goto eleven;
    switch(bc->jumptableIndex) {
    case 0:
    // zero:
        //
        //  init
        // CALL(aGetBallAnimPal);
        GetBallAnimPal_Conv(bc, wram->wCurItem);
        // CALL(aBattleAnim_IncAnonJumptableIndex);
        bc->jumptableIndex++;
        // RET;
        return;

    case 1:
    // one:
        // CALL(aBattleAnimFunction_ThrowFromUserToTarget);
        // RET_C;
        if(BattleAnimFunction_ThrowFromUserToTarget(bc))
            return;
        // LD_HL(BATTLEANIMSTRUCT_YOFFSET);
        // ADD_HL_BC;
        // LD_A_hl;
        // LD_HL(BATTLEANIMSTRUCT_YCOORD);
        // ADD_HL_BC;
        // ADD_A_hl;
        // LD_hl_A;
        bc->yCoord += bc->yOffset;
        // LD_A(BATTLEANIMFRAMESET_0B);
        // CALL(aReinitBattleAnimFrameset);
        ReinitBattleAnimFrameset_Conv(bc, BATTLEANIMFRAMESET_0B);
        // CALL(aBattleAnim_IncAnonJumptableIndex);
        bc->jumptableIndex++;
        // RET;
        return;

    case 3:
    // three:
        // CALL(aBattleAnim_IncAnonJumptableIndex);
        bc->jumptableIndex++;
        // LD_A(BATTLEANIMFRAMESET_09);
        // CALL(aReinitBattleAnimFrameset);
        ReinitBattleAnimFrameset_Conv(bc, BATTLEANIMFRAMESET_09);
        // LD_HL(BATTLEANIMSTRUCT_VAR1);
        // ADD_HL_BC;
        // LD_hl(0x0);
        bc->var1 = 0x0;
        // INC_HL;
        // LD_hl(0x10);
        bc->var2 = 0x10;
        fallthrough;

    case 4: {
    // four:
        // LD_HL(BATTLEANIMSTRUCT_VAR1);
        // ADD_HL_BC;
        // LD_A_hli;
        // LD_D_hl;
        // CALL(aBattleAnim_Sine);
        // LD_HL(BATTLEANIMSTRUCT_YOFFSET);
        // ADD_HL_BC;
        // LD_hl_A;
        bc->yOffset = BattleAnim_Sine_Conv(bc->var1, bc->var2);
        // LD_HL(BATTLEANIMSTRUCT_VAR1);
        // ADD_HL_BC;
        // LD_A_hl;
        // DEC_A;
        // LD_hl_A;
        uint8_t v1 = --bc->var1;
        // AND_A(0x1f);
        // RET_NZ;
        if(v1 & 0x1f)
            return;
        // LD_hl_A;
        bc->var1 = v1;
        // LD_HL(BATTLEANIMSTRUCT_VAR2);
        // ADD_HL_BC;
        // LD_A_hl;
        // SUB_A(0x4);
        // LD_hl_A;
        bc->var2 -= 0x4;
        // RET_NZ;
        if(bc->var2)
            return;
        // LD_A(BATTLEANIMFRAMESET_0C);
        // CALL(aReinitBattleAnimFrameset);
        ReinitBattleAnimFrameset_Conv(bc, BATTLEANIMFRAMESET_0C);
        // CALL(aBattleAnim_IncAnonJumptableIndex);
        bc->jumptableIndex++;
        // RET;
    } return;

    case 6:
    // six:
        // LD_A(BATTLEANIMFRAMESET_0D);
        // CALL(aReinitBattleAnimFrameset);
        ReinitBattleAnimFrameset_Conv(bc, BATTLEANIMFRAMESET_0D);
        // LD_HL(BATTLEANIMSTRUCT_JUMPTABLE_INDEX);
        // ADD_HL_BC;
        // DEC_hl;
        bc->jumptableIndex--;
        fallthrough;

    case 2:
    // two:
    case 5:
    // five:
    case 9:
    // nine:
        // RET;
        return;

    case 7:
    // seven:
        // CALL(aGetBallAnimPal);
        GetBallAnimPal_Conv(bc, wram->wCurItem);
        // LD_A(BATTLEANIMFRAMESET_0A);
        // CALL(aReinitBattleAnimFrameset);
        ReinitBattleAnimFrameset_Conv(bc, BATTLEANIMFRAMESET_0A);
        // CALL(aBattleAnim_IncAnonJumptableIndex);
        bc->jumptableIndex++;
        // LD_HL(BATTLEANIMSTRUCT_VAR2);
        // ADD_HL_BC;
        // LD_hl(0x20);
        bc->var2 = 0x20;
        fallthrough;

    case 8:
    // eight:
    case 10:
    // ten:
        // LD_HL(BATTLEANIMSTRUCT_VAR1);
        // ADD_HL_BC;
        // LD_A_hli;
        // LD_D_hl;
        // CALL(aBattleAnim_Sine);
        // LD_HL(BATTLEANIMSTRUCT_YOFFSET);
        // ADD_HL_BC;
        // LD_hl_A;
        bc->yOffset = BattleAnim_Sine_Conv(bc->var1, bc->var2);
        // LD_HL(BATTLEANIMSTRUCT_VAR1);
        // ADD_HL_BC;
        // LD_A_hl;
        // DEC_A;
        // LD_hl_A;
        // AND_A(0x1f);
        // IF_Z goto eleven;
        if(--bc->var1 & 0x1f) {
            // AND_A(0xf);
            // RET_NZ;
            if(bc->var1 & 0xf)
                return;
            // CALL(aBattleAnim_IncAnonJumptableIndex);
            bc->jumptableIndex++;
            // RET;
            return;
        }
        fallthrough;

    case 11:
    // eleven:
        // CALL(aDeinitBattleAnimation);
        DeinitBattleAnimation_Conv(bc);
        // RET;
        return;
    }
}

void BattleAnimFunction_PokeBallBlocked(struct BattleAnim* bc) {
    // SET_PC(aBattleAnimFunction_PokeBallBlocked);
    // CALL(aBattleAnim_AnonJumptable);

// anon_dw:

    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 0) goto zero;
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 1) goto one;
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 2) goto two;
    switch(bc->jumptableIndex) {
    case 0:
    // zero:
        // CALL(aGetBallAnimPal);
        GetBallAnimPal_Conv(bc, wram->wCurItem);
        // CALL(aBattleAnim_IncAnonJumptableIndex);
        bc->jumptableIndex++;
        // RET;
        return;

    case 1:
    // one:
        // LD_HL(BATTLEANIMSTRUCT_XCOORD);
        // ADD_HL_BC;
        // LD_A_hl;
        // CP_A(0x70);
        // IF_NC goto next;
        if(bc->xCoord < 0x70) {
            // CALL(aBattleAnimFunction_ThrowFromUserToTarget);
            BattleAnimFunction_ThrowFromUserToTarget(bc);
            // RET;
            return;
        }

    // next:
        // CALL(aBattleAnim_IncAnonJumptableIndex);
        bc->jumptableIndex++;
        fallthrough;

    case 2:
    // two:
        // LD_HL(BATTLEANIMSTRUCT_YCOORD);
        // ADD_HL_BC;
        // LD_A_hl;
        // CP_A(0x80);
        // IF_NC goto done;
        if(bc->yCoord >= 0x80) {
        // done:
            // CALL(aDeinitBattleAnimation);
            DeinitBattleAnimation_Conv(bc);
            // RET;
            return;
        }
        // ADD_A(0x4);
        // LD_hl_A;
        bc->yCoord += 0x4;
        // LD_HL(BATTLEANIMSTRUCT_XCOORD);
        // ADD_HL_BC;
        // DEC_hl;
        // DEC_hl;
        bc->xCoord -= 2;
        // RET;
        return;
    }
}

void GetBallAnimPal(void) {
    SET_PC(aGetBallAnimPal);
    LD_HL(mBallColors);
    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(MBANK(awCurItem));
    LDH_addr_A(rSVBK);
    LD_A_addr(wCurItem);
    LD_E_A;
    POP_AF;
    LDH_addr_A(rSVBK);

IsInArray:

    LD_A_hli;
    CP_A(-1);
    IF_Z goto load;
    CP_A_E;
    IF_Z goto load;
    INC_HL;
    goto IsInArray;

load:

    LD_A_hl;
    LD_HL(BATTLEANIMSTRUCT_PALETTE);
    ADD_HL_BC;
    LD_hl_A;
    RET;

    // INCLUDE "data/battle_anims/ball_colors.asm"
}

void GetBallAnimPal_Conv(struct BattleAnim* bc, item_t item) {
    // SET_PC(aGetBallAnimPal);
    // LD_HL(mBallColors);
    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    // LD_A(MBANK(awCurItem));
    // LDH_addr_A(rSVBK);
    // LD_A_addr(wCurItem);
    // LD_E_A;
    // POP_AF;
    // LDH_addr_A(rSVBK);

// IsInArray:
    uint32_t i = 0;
    for(; BallColors[i].item != (item_t)-1 && BallColors[i].item != item; ++i) {
        // LD_A_hli;
        // CP_A(-1);
        // IF_Z goto load;
        // CP_A_E;
        // IF_Z goto load;
        // INC_HL;
        // goto IsInArray;
    }

// load:
    // LD_A_hl;
    // LD_HL(BATTLEANIMSTRUCT_PALETTE);
    // ADD_HL_BC;
    // LD_hl_A;
    bc->palette = BallColors[i].pal;
    // RET;

    // INCLUDE "data/battle_anims/ball_colors.asm"
}

void BattleAnimFunction_Ember(struct BattleAnim* bc) {
    // SET_PC(aBattleAnimFunction_Ember);
    // CALL(aBattleAnim_AnonJumptable);

// anon_dw:

    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 0) goto zero;
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 1) goto one;
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 2) goto two;
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 3) goto three;
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 4) goto four;
    switch(bc->jumptableIndex) {
    case 0:
    // zero:
        // LD_HL(BATTLEANIMSTRUCT_PARAM);
        // ADD_HL_BC;
        // LD_A_hl;
        // SWAP_A;
        // AND_A(0xf);
        // LD_HL(BATTLEANIMSTRUCT_JUMPTABLE_INDEX);
        // ADD_HL_BC;
        // LD_hl_A;
        bc->jumptableIndex = (bc->param >> 4) & 0xf;
        // RET;
        return;

    case 1:
    // one:
        // LD_HL(BATTLEANIMSTRUCT_XCOORD);
        // ADD_HL_BC;
        // LD_A_hl;
        // CP_A(0x88);
        // RET_NC;
        if(bc->xCoord >= 0x88)
            return;
        // LD_HL(BATTLEANIMSTRUCT_PARAM);
        // ADD_HL_BC;
        // LD_A_hl;
        // CALL(aBattleAnim_StepToTarget);
        BattleAnim_StepToTarget(bc, bc->param);
        // RET;
        return;

    case 2:
    // two:
        // CALL(aDeinitBattleAnimation);
        DeinitBattleAnimation_Conv(bc);
        // RET;
        return;

    case 3:
    // three:
        // CALL(aBattleAnim_IncAnonJumptableIndex);
        bc->jumptableIndex++;
        // LD_A(BATTLEANIMFRAMESET_0F);
        // CALL(aReinitBattleAnimFrameset);
        ReinitBattleAnimFrameset_Conv(bc, BATTLEANIMFRAMESET_0F);
        fallthrough;

    case 4:
    // four:
        // RET;
        return;
    }
}

//  Drops obj. The Obj Param dictates how fast it is (lower value is faster) and how long it stays bouncing (lower value is longer). Example: Rock Slide
void BattleAnimFunction_Drop(struct BattleAnim* bc) {
    // SET_PC(aBattleAnimFunction_Drop);
    // CALL(aBattleAnim_AnonJumptable);

// anon_dw:

    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 0) goto zero;
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 1) goto one;
    switch(bc->jumptableIndex) {
    case 0:
    // zero:
        // CALL(aBattleAnim_IncAnonJumptableIndex);
        bc->jumptableIndex++;
        // LD_HL(BATTLEANIMSTRUCT_VAR1);
        // ADD_HL_BC;
        // LD_hl(0x30);
        bc->var1 = 0x30;
        // INC_HL;
        // LD_hl(0x48);
        bc->var2 = 0x48;
        fallthrough;

    case 1:
    // one:
        // LD_HL(BATTLEANIMSTRUCT_VAR1);
        // ADD_HL_BC;
        // LD_A_hli;
        // LD_D_hl;
        // CALL(aBattleAnim_Sine);
        // LD_HL(BATTLEANIMSTRUCT_YOFFSET);
        // ADD_HL_BC;
        // LD_hl_A;
        bc->yOffset = BattleAnim_Sine_Conv(bc->var1, bc->var2);
        // LD_HL(BATTLEANIMSTRUCT_VAR1);
        // ADD_HL_BC;
        // INC_hl;
        // LD_A_hl;
        // AND_A(0x3f);
        // RET_NZ;
        if(++bc->var1 & 0x3f)
            return;
        // LD_HL(BATTLEANIMSTRUCT_VAR1);
        // ADD_HL_BC;
        // LD_hl(0x20);
        bc->var1 = 0x20;
        // LD_HL(BATTLEANIMSTRUCT_VAR2);
        // ADD_HL_BC;
        // LD_A_hl;
        // LD_HL(BATTLEANIMSTRUCT_PARAM);
        // ADD_HL_BC;
        // SUB_A_hl;
        // IF_Z goto done;
        // IF_C goto done;
        if(bc->var2 > bc->param) {
            // LD_HL(BATTLEANIMSTRUCT_VAR2);
            // ADD_HL_BC;
            // LD_hl_A;
            bc->var2 -= bc->param;
            // RET;
            return;
        }

    // done:
        // CALL(aDeinitBattleAnimation);
        DeinitBattleAnimation_Conv(bc);
        // RET;
        return;
    }
}

static void BattleAnimFunction_MoveFromUserToTargetSpinAround_SetCoords(struct BattleAnim* bc) {
    // LD_HL(BATTLEANIMSTRUCT_PARAM);
    // ADD_HL_BC;
    // LD_A_hl;
    // AND_A(0xf);
    // LD_HL(BATTLEANIMSTRUCT_XCOORD);
    // ADD_HL_BC;
    // ADD_A_hl;
    // LD_hl_A;
    bc->xCoord += bc->param & 0xf;
    // LD_HL(BATTLEANIMSTRUCT_PARAM);
    // ADD_HL_BC;
    // LD_A_hl;
    // AND_A(0xf);
    // LD_E_A;
    // SRL_E;
    // LD_HL(BATTLEANIMSTRUCT_YCOORD);
    // ADD_HL_BC;

// loop:
    // DEC_hl;
    // DEC_E;
    // IF_NZ goto loop;
    bc->yCoord -= (bc->param & 0xf) >> 1;
    // RET;
}

//  Object moves from user to target target and spins around it once. Example: Fire Spin, Swift
void BattleAnimFunction_MoveFromUserToTargetSpinAround(struct BattleAnim* bc) {
    // SET_PC(aBattleAnimFunction_MoveFromUserToTargetSpinAround);
    // CALL(aBattleAnim_AnonJumptable);

// anon_dw:

    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 0) goto zero;
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 1) goto one;
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 2) goto two;
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 3) goto three;

    switch(bc->jumptableIndex) {
    case 0:
    // zero:
        // LD_HL(BATTLEANIMSTRUCT_XCOORD);
        // ADD_HL_BC;
        // LD_A_hl;
        // CP_A(0x80);
        // IF_NC goto next;
        if(bc->xCoord < 0x80) {
            // CALL(aBattleAnimFunction_MoveFromUserToTargetSpinAround_SetCoords);
            BattleAnimFunction_MoveFromUserToTargetSpinAround_SetCoords(bc);
            // RET;
            return;
        }

    // next:
        // CALL(aBattleAnim_IncAnonJumptableIndex);
        bc->jumptableIndex++;
        fallthrough;

    case 1:
    // one:
        // CALL(aBattleAnim_IncAnonJumptableIndex);
        bc->jumptableIndex++;
        // LD_HL(BATTLEANIMSTRUCT_VAR1);
        // ADD_HL_BC;
        // LD_hl(0x0);
        bc->var1 = 0x0;
        fallthrough;

    case 2:
    // two:
        // LD_HL(BATTLEANIMSTRUCT_VAR1);
        // ADD_HL_BC;
        // LD_A_hl;
        // CP_A(0x40);
        // IF_NC goto loop_back;
        if(bc->var1 < 0x40) {
            // LD_HL(BATTLEANIMSTRUCT_VAR1);
            // ADD_HL_BC;
            // LD_A_hl;
            // LD_D(0x18);
            // CALL(aBattleAnim_Cosine);
            int8_t cos = (int8_t)BattleAnim_Cosine_Conv(bc->var1, 0x18);
            // SUB_A(0x18);
            // SRA_A;
            // LD_HL(BATTLEANIMSTRUCT_YOFFSET);
            // ADD_HL_BC;
            // LD_hl_A;
            bc->yOffset = (uint8_t)((cos - 0x18) >> 1);
            // LD_HL(BATTLEANIMSTRUCT_VAR1);
            // ADD_HL_BC;
            // LD_A_hl;
            // LD_D(0x18);
            // CALL(aBattleAnim_Sine);
            // LD_HL(BATTLEANIMSTRUCT_XOFFSET);
            // ADD_HL_BC;
            // LD_hl_A;
            bc->xOffset = BattleAnim_Sine_Conv(bc->var1, 0x18);
            // LD_HL(BATTLEANIMSTRUCT_PARAM);
            // ADD_HL_BC;
            // LD_A_hl;
            // AND_A(0xf);
            // LD_HL(BATTLEANIMSTRUCT_VAR1);
            // ADD_HL_BC;
            // ADD_A_hl;
            // LD_hl_A;
            bc->var1 = (bc->param & 0xf) + bc->var1;
            // RET;
            return;
        }

    // loop_back:
        // LD_HL(BATTLEANIMSTRUCT_PARAM);
        // ADD_HL_BC;
        // LD_A_hl;
        // AND_A(0xf0);
        // IF_Z goto finish;
        if(bc->param & 0xf0) {
            // SUB_A(0x10);
            // LD_D_A;
            // LD_A_hl;
            // AND_A(0xf);
            // OR_A_D;
            // LD_hl_A;
            bc->param = ((bc->param & 0xf0) - 0x10) | (bc->param & 0xf);
            // LD_HL(BATTLEANIMSTRUCT_JUMPTABLE_INDEX);
            // ADD_HL_BC;
            // DEC_hl;
            bc->jumptableIndex--;
            // RET;
            return;
        }

    // finish:
        // CALL(aBattleAnim_IncAnonJumptableIndex);
        bc->jumptableIndex++;
        fallthrough;

    case 3:
    // three:
        // LD_HL(BATTLEANIMSTRUCT_XCOORD);
        // ADD_HL_BC;
        // LD_A_hl;
        // CP_A(0xb0);
        // IF_C goto retain;
        if(bc->xCoord >= 0xb0) {
            // CALL(aDeinitBattleAnimation);
            DeinitBattleAnimation_Conv(bc);
            // RET;
            return;
        }

    // retain:
        // CALL(aBattleAnimFunction_MoveFromUserToTargetSpinAround_SetCoords);
        BattleAnimFunction_MoveFromUserToTargetSpinAround_SetCoords(bc);
        // RET;
        return;
    }
}

//  Object switches position side to side. Obj Param defines how far to move it. Example: Dynamic Punch
//  Some objects use this function with a Param of 0
void BattleAnimFunction_Shake(struct BattleAnim* bc) {
    // SET_PC(aBattleAnimFunction_Shake);
    // CALL(aBattleAnim_AnonJumptable);

// anon_dw:

    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 0) goto zero;
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 1) goto one;
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 2) goto two;

    switch(bc->jumptableIndex) {
    case 0:
    // zero:
        // CALL(aBattleAnim_IncAnonJumptableIndex);
        bc->jumptableIndex++;
        // LD_HL(BATTLEANIMSTRUCT_VAR1);
        // ADD_HL_BC;
        // LD_hl(0x0);
        bc->var1 = 0x0;
        // LD_HL(BATTLEANIMSTRUCT_PARAM);
        // ADD_HL_BC;
        // LD_A_hl;
        // AND_A(0xf);
        // LD_HL(BATTLEANIMSTRUCT_XOFFSET);
        // ADD_HL_BC;
        // LD_hl_A;
        bc->xOffset = bc->param & 0xf;
        fallthrough;

    case 1:
    // one:
        // LD_HL(BATTLEANIMSTRUCT_VAR1);
        // ADD_HL_BC;
        // LD_A_hl;
        // AND_A_A;
        // IF_Z goto done_one;
        if(bc->var1 != 0) {
            // DEC_hl;
            // RET;
            bc->var1--;
        }

    // done_one:
        // LD_HL(BATTLEANIMSTRUCT_PARAM);
        // ADD_HL_BC;
        // LD_A_hl;
        // SWAP_A;
        // AND_A(0xf);
        // LD_HL(BATTLEANIMSTRUCT_VAR1);
        // ADD_HL_BC;
        // LD_hl_A;
        bc->var1 = (bc->param >> 4) & 0xf;
        // LD_HL(BATTLEANIMSTRUCT_XOFFSET);
        // ADD_HL_BC;
        // LD_A_hl;
        // XOR_A(0xff);
        // INC_A;
        // LD_hl_A;
        bc->xOffset = (bc->xOffset ^ 0xff) + 1;
        // RET;
        return;

    case 2:
    // two:
        // CALL(aDeinitBattleAnimation);
        DeinitBattleAnimation_Conv(bc);
        // RET;
        return;
    }
}

void BattleAnimFunction_FireBlast(struct BattleAnim* bc) {
    // SET_PC(aBattleAnimFunction_FireBlast);
    // CALL(aBattleAnim_AnonJumptable);

// anon_dw:

    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 0) goto zero;
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 1) goto one;
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 2) goto two;
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 3) goto three;
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 4) goto four;
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 5) goto five;
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 6) goto six;
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 7) goto seven;
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 8) goto eight;
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 9) goto nine;

    switch(bc->jumptableIndex) {
    case 0:
    // zero:
        // LD_HL(BATTLEANIMSTRUCT_PARAM);
        // ADD_HL_BC;
        // LD_A_hl;
        // LD_HL(BATTLEANIMSTRUCT_JUMPTABLE_INDEX);
        // ADD_HL_BC;
        // LD_hl_A;
        bc->jumptableIndex = bc->param;
        // CP_A(0x7);
        // IF_Z goto seven;
        if(bc->param != 0x7) {
            // LD_A(BATTLEANIMFRAMESET_11);
            // CALL(aReinitBattleAnimFrameset);
            ReinitBattleAnimFrameset_Conv(bc, BATTLEANIMFRAMESET_11);
            // RET;
            return;
        }
        fallthrough;

    case 0x7:
    // seven:
        // LD_HL(BATTLEANIMSTRUCT_XCOORD);
        // ADD_HL_BC;
        // LD_A_hl;
        // CP_A(0x88);
        // IF_NC goto set_up_eight;
        if(bc->xCoord < 0x88) {
            // ADD_A(0x2);
            // LD_hl_A;
            bc->xCoord += 0x2;
            // LD_HL(BATTLEANIMSTRUCT_YCOORD);
            // ADD_HL_BC;
            // DEC_hl;
            bc->yCoord--;
            // RET;
            return;
        }

    // set_up_eight:
        // CALL(aBattleAnim_IncAnonJumptableIndex);
        bc->jumptableIndex++;
        // LD_A(BATTLEANIMFRAMESET_10);
        // CALL(aReinitBattleAnimFrameset);
        ReinitBattleAnimFrameset_Conv(bc, BATTLEANIMFRAMESET_10);
        fallthrough;

    case 8:
    // eight:
        // LD_HL(BATTLEANIMSTRUCT_VAR1);
        // ADD_HL_BC;
        // LD_A_hl;
        // LD_D(0x10);
        // PUSH_AF;
        // PUSH_DE;
        // CALL(aBattleAnim_Sine);
        // LD_HL(BATTLEANIMSTRUCT_YOFFSET);
        // ADD_HL_BC;
        // LD_hl_A;
        bc->yOffset = BattleAnim_Sine_Conv(bc->var1, 0x10);
        // POP_DE;
        // POP_AF;
        // CALL(aBattleAnim_Cosine);
        // LD_HL(BATTLEANIMSTRUCT_XOFFSET);
        // ADD_HL_BC;
        // LD_hl_A;
        bc->xOffset = BattleAnim_Cosine_Conv(bc->var1, 0x10);
        // LD_HL(BATTLEANIMSTRUCT_VAR1);
        // ADD_HL_BC;
        // INC_hl;
        bc->var1++;
        // RET;
        return;

    case 9:
    // nine:
        // CALL(aDeinitBattleAnimation);
        DeinitBattleAnimation_Conv(bc);
        // RET;
        return;

    case 1:
    // one:
        // Flame that moves upward
        // LD_HL(BATTLEANIMSTRUCT_YOFFSET);
        // ADD_HL_BC;
        // DEC_hl;
        bc->yOffset--;
        // RET;
        return;

    case 4:
    // four:
        // Flame that moves down and left
        // LD_HL(BATTLEANIMSTRUCT_YOFFSET);
        // ADD_HL_BC;
        // INC_hl;
        bc->yOffset++;
        fallthrough;

    case 2:
    // two:
        // Flame that moves left
        // LD_HL(BATTLEANIMSTRUCT_XOFFSET);
        // ADD_HL_BC;
        // DEC_hl;
        bc->xOffset--;
        // RET;
        return;

    case 5:
    // five:
        // Flame that moves down and right
        // LD_HL(BATTLEANIMSTRUCT_YOFFSET);
        // ADD_HL_BC;
        // INC_hl;
        bc->yOffset++;
        fallthrough;

    case 3:
    // three:
        // Flame that moves right
        // LD_HL(BATTLEANIMSTRUCT_XOFFSET);
        // ADD_HL_BC;
        // INC_hl;
        bc->xOffset++;
        fallthrough;

    case 6:
    // six:
        // RET;
        return;
    }
}

void BattleAnimFunction_RazorLeaf(struct BattleAnim* bc) {
    // SET_PC(aBattleAnimFunction_RazorLeaf);
    // CALL(aBattleAnim_AnonJumptable);

// anon_dw:

    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 0) goto zero;
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 1) goto one;
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 2) goto two;
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 3) goto three;
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 4) goto four;
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 5) goto five;
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 6) goto six;
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 7) goto seven;
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 8) goto eight;

    switch(bc->jumptableIndex) {
    case 0:
    // zero:
        // CALL(aBattleAnim_IncAnonJumptableIndex);
        bc->jumptableIndex++;
        // LD_HL(BATTLEANIMSTRUCT_VAR1);
        // ADD_HL_BC;
        // LD_hl(0x40);
        bc->var1 = 0x40;
        fallthrough;

    case 1: {
    // one:
        // LD_HL(BATTLEANIMSTRUCT_VAR1);
        // ADD_HL_BC;
        // LD_A_hl;
        // CP_A(0x30);
        // IF_NC goto sine_cosine;
        if(bc->var1 < 0x30) {
            // CALL(aBattleAnim_IncAnonJumptableIndex);
            bc->jumptableIndex++;
            // XOR_A_A;
            // LD_HL(BATTLEANIMSTRUCT_VAR1);
            // ADD_HL_BC;
            // LD_hli_A;
            bc->var1 = 0;
            // LD_hl_A;
            bc->var2 = 0;
            // LD_A(BATTLEANIMFRAMESET_17);
            // CALL(aReinitBattleAnimFrameset);
            ReinitBattleAnimFrameset_Conv(bc, BATTLEANIMFRAMESET_17);
            // LD_HL(BATTLEANIMSTRUCT_PARAM);
            // ADD_HL_BC;
            // BIT_hl(6);
            // RET_Z;
            if(!bit_test(bc->param, 6))
                return;
            // LD_HL(BATTLEANIMSTRUCT_FRAME);
            // ADD_HL_BC;
            // LD_hl(0x5);
            bc->frame = 0x5;
            // RET;
            return;
        }

    // sine_cosine:
        // LD_HL(BATTLEANIMSTRUCT_PARAM);
        // ADD_HL_BC;
        // LD_A_hl;
        // AND_A(0x3f);
        // LD_D_A;
        // LD_HL(BATTLEANIMSTRUCT_VAR1);
        // ADD_HL_BC;
        // LD_A_hl;
        // DEC_hl;
        // CALL(aBattleAnim_Sine);
        // LD_HL(BATTLEANIMSTRUCT_YOFFSET);
        // ADD_HL_BC;
        // LD_hl_A;
        bc->yOffset = BattleAnim_Sine_Conv(bc->var1--, bc->param & 0x3f);
        // CALL(aBattleAnim_ScatterHorizontal);
        int16_t de = BattleAnim_ScatterHorizontal(bc);
        // LD_HL(BATTLEANIMSTRUCT_VAR2);
        // ADD_HL_BC;
        // LD_A_hl;
        // LD_HL(BATTLEANIMSTRUCT_XCOORD);
        // ADD_HL_BC;
        // LD_H_hl;
        // LD_L_A;
        uint16_t temp = ((bc->xCoord << 8) | bc->var2) + de;
        // ADD_HL_DE;
        // LD_E_L;
        // LD_D_H;
        // LD_HL(BATTLEANIMSTRUCT_XCOORD);
        // ADD_HL_BC;
        // LD_hl_D;
        bc->xCoord = HIGH(temp);
        // LD_HL(BATTLEANIMSTRUCT_VAR2);
        // ADD_HL_BC;
        // LD_hl_E;
        bc->var2 = LOW(temp);
        // RET;
    } return;

    case 2: {
    // two:
        // LD_HL(BATTLEANIMSTRUCT_YOFFSET);
        // ADD_HL_BC;
        // LD_A_hl;
        // CP_A(0x20);
        // IF_NZ goto sine_cosine_2;
        if(bc->yOffset == 0x20) {
            // CALL(aDeinitBattleAnimation);
            DeinitBattleAnimation_Conv(bc);
            // RET;
            return;
        }

    // sine_cosine_2:
        // LD_HL(BATTLEANIMSTRUCT_VAR1);
        // ADD_HL_BC;
        // LD_A_hl;
        // LD_D(0x10);
        // CALL(aBattleAnim_Sine);
        // LD_HL(BATTLEANIMSTRUCT_XOFFSET);
        // ADD_HL_BC;
        // LD_hl_A;
        bc->xOffset = BattleAnim_Sine_Conv(bc->var1, 0x10);
        // LD_HL(BATTLEANIMSTRUCT_PARAM);
        // ADD_HL_BC;
        // BIT_hl(6);
        // IF_NZ goto decrease;
        if(bit_test(bc->param, 6)) {
        // decrease:
            // LD_HL(BATTLEANIMSTRUCT_VAR1);
            // ADD_HL_BC;
            // DEC_hl;
            bc->var1--;
        }
        else {
            // LD_HL(BATTLEANIMSTRUCT_VAR1);
            // ADD_HL_BC;
            // INC_hl;
            bc->var1++;
            // goto finish;
        }

    // finish:
        // LD_DE(0x80);
        // LD_HL(BATTLEANIMSTRUCT_VAR2);
        // ADD_HL_BC;
        // LD_A_hl;
        // LD_HL(BATTLEANIMSTRUCT_YOFFSET);
        // ADD_HL_BC;
        // LD_H_hl;
        // LD_L_A;
        uint16_t de = ((bc->yOffset << 8) | bc->var2) + 0x80;
        // ADD_HL_DE;
        // LD_E_L;
        // LD_D_H;
        // LD_HL(BATTLEANIMSTRUCT_YOFFSET);
        // ADD_HL_BC;
        // LD_hl_D;
        bc->yOffset = HIGH(de);
        // LD_HL(BATTLEANIMSTRUCT_VAR2);
        // ADD_HL_BC;
        // LD_hl_E;
        bc->var2 = LOW(de);
        // RET;
    } return;

    case 3:
    // three:
        // LD_A(BATTLEANIMFRAMESET_16);
        // CALL(aReinitBattleAnimFrameset);
        ReinitBattleAnimFrameset_Conv(bc, BATTLEANIMFRAMESET_16);
        // LD_HL(BATTLEANIMSTRUCT_OAMFLAGS);
        // ADD_HL_BC;
        // RES_hl(5);
        bit_reset(bc->oamFlags, 5);
        fallthrough;

    case 4:
    // four:
    case 5:
    // five:
    case 6:
    // six:
    case 7:
    // seven:
        // CALL(aBattleAnim_IncAnonJumptableIndex);
        bc->jumptableIndex++;
        // RET;
        return;

    case 8:
    // eight:
        // LD_HL(BATTLEANIMSTRUCT_XCOORD);
        // ADD_HL_BC;
        // LD_A_hl;
        // CP_A(0xc0);
        // RET_NC;
        if(bc->xCoord >= 0xc0)
            return;
        // LD_A(0x8);
        // CALL(aBattleAnim_StepToTarget);
        BattleAnim_StepToTarget(bc, 0x8);
        // RET;
        return;
    }
}

//  Affects horizontal sine movement based on bit 7 of Obj Param
int16_t BattleAnim_ScatterHorizontal(struct BattleAnim* bc) {
    // SET_PC(aBattleAnim_ScatterHorizontal);
    // LD_HL(BATTLEANIMSTRUCT_PARAM);
    // ADD_HL_BC;
    // LD_A_hl;
    // BIT_A(7);
    // IF_NZ goto negative;
    if((int8_t)bc->param < 0) {
    // negative:
        // AND_A(0b00111111);
        // CP_A(0x20);
        // IF_NC goto minus_256;
        if((bc->param & 0b00111111) >= 0x20) {
        // minus_256:
            // LD_DE(-0x100);
            // RET;
            return -0x100;
        }
        // CP_A(0x18);
        // IF_NC goto minus_384;
        else if((bc->param & 0b00111111) >= 0x18) {
        // minus_384:
            // LD_DE(-0x180);
            // RET;
            return -0x180;
        }
        else {
            // LD_DE(-0x200);
            // RET;
            return -0x200;
        }
    }
    // CP_A(0x20);
    // IF_NC goto plus_256;
    else if(bc->param >= 0x20) {
    // plus_256:
        // LD_DE(0x100);
        // RET;
        return 0x100;
    }
    // CP_A(0x18);
    // IF_NC goto plus_384;
    else if(bc->param >= 0x18) {
    // plus_384:
        // LD_DE(0x180);
        // RET;
        return 0x180;
    }
    // LD_DE(0x200);
    // RET;
    return 0x200;
}

//  Object moves at an arc
//  Obj Param: Bit 7 makes arc flip horizontally
//             Bit 6 defines offset from base frameset FRAMESET_19
//             Rest defines arc radius
void BattleAnimFunction_RockSmash(struct BattleAnim* bc) {
    // SET_PC(aBattleAnimFunction_RockSmash);
    // CALL(aBattleAnim_AnonJumptable);

// anon_dw:

    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 0) goto zero;
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 1) goto one;
    switch(bc->jumptableIndex) {
    case 0:
    // zero:
        // LD_HL(BATTLEANIMSTRUCT_PARAM);
        // ADD_HL_BC;
        // LD_A_hl;
        // AND_A(0x40);
        // RLCA;
        // RLCA;
        // ADD_A(BATTLEANIMFRAMESET_19);
        // LD_HL(BATTLEANIMSTRUCT_FRAMESET_ID);
        // ADD_HL_BC;
        // LD_hl_A;
        bc->framesetId = ((bc->param & 0x40) << 2) | ((bc->param & 0x40) >> 6);
        // CALL(aBattleAnim_IncAnonJumptableIndex);
        bc->jumptableIndex++;
        // LD_HL(BATTLEANIMSTRUCT_VAR1);
        // ADD_HL_BC;
        // LD_hl(0x40);
        bc->var1 = 0x40;
        fallthrough;

    case 1: {
    // one:
        // LD_HL(BATTLEANIMSTRUCT_VAR1);
        // ADD_HL_BC;
        // LD_A_hl;
        // CP_A(0x30);
        // IF_NC goto sine_cosine;
        if(bc->var1 < 0x30) {
            // CALL(aDeinitBattleAnimation);
            DeinitBattleAnimation_Conv(bc);
            // RET;
            return;
        }
    
    // sine_cosine:
        // LD_HL(BATTLEANIMSTRUCT_PARAM);
        // ADD_HL_BC;
        // LD_A_hl;
        // AND_A(0x3f);
        // LD_D_A;
        // LD_HL(BATTLEANIMSTRUCT_VAR1);
        // ADD_HL_BC;
        // LD_A_hl;
        // DEC_hl;
        // CALL(aBattleAnim_Sine);
        // LD_HL(BATTLEANIMSTRUCT_YOFFSET);
        // ADD_HL_BC;
        // LD_hl_A;
        bc->yOffset = BattleAnim_Sine_Conv(bc->var1--, bc->param & 0x3f);
        // CALL(aBattleAnim_ScatterHorizontal);
        int16_t de = BattleAnim_ScatterHorizontal(bc);
        // LD_HL(BATTLEANIMSTRUCT_VAR2);
        // ADD_HL_BC;
        // LD_A_hl;
        // LD_HL(BATTLEANIMSTRUCT_XCOORD);
        // ADD_HL_BC;
        // LD_H_hl;
        // LD_L_A;
        // ADD_HL_DE;
        // LD_E_L;
        // LD_D_H;
        uint16_t hl = ((bc->xCoord << 8) | bc->var2) + de;
        // LD_HL(BATTLEANIMSTRUCT_XCOORD);
        // ADD_HL_BC;
        // LD_hl_D;
        bc->xCoord = HIGH(hl);
        // LD_HL(BATTLEANIMSTRUCT_VAR2);
        // ADD_HL_BC;
        // LD_hl_E;
        bc->var2 = LOW(hl);
        // RET;
    } return;
    }
}

void BattleAnimFunction_Bubble(struct BattleAnim* bc) {
    // SET_PC(aBattleAnimFunction_Bubble);
    // CALL(aBattleAnim_AnonJumptable);

// anon_dw:

    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 0) goto zero;
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 1) goto one;
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 2) goto two;
    switch(bc->jumptableIndex) {
    case 0:
    // zero:
        // CALL(aBattleAnim_IncAnonJumptableIndex);
        bc->jumptableIndex++;
        // LD_HL(BATTLEANIMSTRUCT_VAR1);
        // ADD_HL_BC;
        // LD_hl(0xc);
        bc->var1 = 0xc;
        fallthrough;

    case 1:
    // one:
        // LD_HL(BATTLEANIMSTRUCT_VAR1);
        // ADD_HL_BC;
        // LD_A_hl;
        // AND_A_A;
        // IF_Z goto next;
        if(bc->var1 != 0) {
            // DEC_hl;
            bc->var1--;
            // LD_HL(BATTLEANIMSTRUCT_PARAM);
            // ADD_HL_BC;
            // LD_A_hl;
            // CALL(aBattleAnim_StepToTarget);
            BattleAnim_StepToTarget(bc, bc->param);
            // RET;
            return;
        }

    // next:
        // CALL(aBattleAnim_IncAnonJumptableIndex);
        bc->jumptableIndex++;
        // LD_HL(BATTLEANIMSTRUCT_VAR1);
        // ADD_HL_BC;
        // LD_hl(0x0);
        bc->var1 = 0x0;
        // LD_A(BATTLEANIMFRAMESET_22);
        // CALL(aReinitBattleAnimFrameset);
        ReinitBattleAnimFrameset_Conv(bc, BATTLEANIMFRAMESET_22);
        fallthrough;

    case 2: {
    // two:
        // LD_HL(BATTLEANIMSTRUCT_XCOORD);
        // ADD_HL_BC;
        // LD_A_hl;
        // CP_A(0x98);
        // IF_NC goto okay;
        if(bc->xCoord < 0x98) {
            // LD_HL(BATTLEANIMSTRUCT_VAR1);
            // ADD_HL_BC;
            // LD_A_hl;
            // LD_HL(BATTLEANIMSTRUCT_XCOORD);
            // ADD_HL_BC;
            // LD_H_hl;
            // LD_L_A;
            // LD_DE(0x60);
            // ADD_HL_DE;
            uint16_t hl = ((bc->xCoord << 8) | bc->var1) + 0x60;
            // LD_E_L;
            // LD_D_H;
            // LD_HL(BATTLEANIMSTRUCT_VAR1);
            // ADD_HL_BC;
            // LD_hl_E;
            bc->var1 = LOW(hl);
            // LD_HL(BATTLEANIMSTRUCT_XCOORD);
            // ADD_HL_BC;
            // LD_hl_D;
            bc->xCoord = HIGH(hl);
        }

    // okay:
        // LD_HL(BATTLEANIMSTRUCT_YCOORD);
        // ADD_HL_BC;
        // LD_A_hl;
        // CP_A(0x20);
        // RET_C;
        if(bc->yCoord < 0x20)
            return;
        // LD_HL(BATTLEANIMSTRUCT_PARAM);
        // ADD_HL_BC;
        // LD_A_hl;
        // AND_A(0xf0);
        // LD_E_A;
        // LD_D(0xff);
        int16_t de = (int16_t)(0xff00 | (bc->param & 0xf0));
        // LD_HL(BATTLEANIMSTRUCT_VAR2);
        // ADD_HL_BC;
        // LD_A_hl;
        // LD_HL(BATTLEANIMSTRUCT_YCOORD);
        // ADD_HL_BC;
        // LD_H_hl;
        // LD_L_A;
        // ADD_HL_DE;
        uint16_t hl = ((bc->yCoord << 8) | bc->var2) + de;
        // LD_E_L;
        // LD_D_H;
        // LD_HL(BATTLEANIMSTRUCT_VAR2);
        // ADD_HL_BC;
        // LD_hl_E;
        bc->var2 = LOW(hl);
        // LD_HL(BATTLEANIMSTRUCT_YCOORD);
        // ADD_HL_BC;
        // LD_hl_D;
        bc->yCoord = HIGH(hl);
        // RET;
    } return;
    }
}

void BattleAnimFunction_Surf(struct BattleAnim* bc) {
    // SET_PC(aBattleAnimFunction_Surf);
    // CALL(aBattleAnim_AnonJumptable);

// anon_dw:

    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 0) goto zero;
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 1) goto one;
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 2) goto two;
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 3) goto three;
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 4) goto four;
    switch(bc->jumptableIndex) {
    case 0:
    // zero:
        // CALL(aBattleAnim_IncAnonJumptableIndex);
        bc->jumptableIndex++;
        // LD_A(LOW(rSCY));
        // LDH_addr_A(hLCDCPointer);
        hram->hLCDCPointer = LOW(rSCY);
        // LD_A(0x58);
        // LDH_addr_A(hLYOverrideStart);
        hram->hLYOverrideStart = 0x58;
        // LD_A(0x5e);
        // LDH_addr_A(hLYOverrideEnd);
        hram->hLYOverrideEnd = 0x5e;
        // RET;
        return;

    case 1:
    // one:
        // LD_HL(BATTLEANIMSTRUCT_PARAM);
        // ADD_HL_BC;
        // LD_E_hl;
        // LD_HL(BATTLEANIMSTRUCT_YCOORD);
        // ADD_HL_BC;
        // LD_A_hl;
        // CP_A_E;
        // IF_NC goto move;
        if(bc->yCoord < bc->param) {
            // CALL(aBattleAnim_IncAnonJumptableIndex);
            bc->jumptableIndex++;
            // XOR_A_A;
            // LDH_addr_A(hLYOverrideStart);
            hram->hLYOverrideStart = 0x0;
            // RET;
            return;
        }

    // move:
        // DEC_A;
        // LD_hl_A;
        bc->yCoord--;
        // LD_HL(BATTLEANIMSTRUCT_VAR1);
        // ADD_HL_BC;
        // LD_A_hl;
        // LD_D(0x10);
        // CALL(aBattleAnim_Sine);
        // LD_HL(BATTLEANIMSTRUCT_YOFFSET);
        // ADD_HL_BC;
        // LD_hl_A;
        bc->yOffset = BattleAnim_Sine_Conv(bc->var1, 0x10);
        // LD_HL(BATTLEANIMSTRUCT_YCOORD);
        // ADD_HL_BC;
        // ADD_A_hl;
        // SUB_A(0x10);
        // RET_C;
        if(bc->yOffset + bc->yCoord < 0x10)
            return;
        // LDH_addr_A(hLYOverrideStart);
        hram->hLYOverrideStart = bc->yOffset + bc->yCoord - 0x10;
        // LD_HL(BATTLEANIMSTRUCT_XOFFSET);
        // ADD_HL_BC;
        // LD_A_hl;
        // INC_A;
        // AND_A(0x7);
        // LD_hl_A;
        bc->xOffset = (bc->xOffset + 1) & 0x7;
        // LD_HL(BATTLEANIMSTRUCT_VAR1);
        // ADD_HL_BC;
        // INC_hl;
        // INC_hl;
        bc->var1 += 2;
        fallthrough;

    case 2:
    // two:
        // RET;
        return;

    case 3:
    // three:
        // LD_HL(BATTLEANIMSTRUCT_YCOORD);
        // ADD_HL_BC;
        // LD_A_hl;
        // CP_A(0x70);
        // IF_C goto move_down;
        if(bc->yCoord < 0x70) {
        // move_down:
            // INC_A;
            // INC_A;
            // LD_hl_A;
            bc->yCoord += 2;
            // SUB_A(0x10);
            // RET_C;
            if(bc->yCoord < 0x10)
                return;
            // LDH_addr_A(hLYOverrideStart);
            hram->hLYOverrideStart = bc->yCoord - 0x10;
            // RET;
            return;
        }
        // XOR_A_A;
        // LDH_addr_A(hLCDCPointer);
        hram->hLCDCPointer = 0;
        // LDH_addr_A(hLYOverrideStart);
        hram->hLYOverrideStart = 0;
        // LDH_addr_A(hLYOverrideEnd);
        hram->hLYOverrideEnd = 0;
        fallthrough;

    case 4:
    // four:
        // CALL(aDeinitBattleAnimation);
        DeinitBattleAnimation_Conv(bc);
        // RET;
        return;
    }
}

void BattleAnimFunction_Sing(struct BattleAnim* bc) {
    // SET_PC(aBattleAnimFunction_Sing);
    // CALL(aBattleAnim_AnonJumptable);

// anon_dw:

    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 0) goto zero;
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 1) goto one;
    switch(bc->jumptableIndex) {
    case 0:
    // zero:
        // CALL(aBattleAnim_IncAnonJumptableIndex);
        bc->jumptableIndex++;
        // LD_HL(BATTLEANIMSTRUCT_PARAM);
        // ADD_HL_BC;
        // LD_A(BATTLEANIMFRAMESET_24);
        // ADD_A_hl;  // BATTLEANIMFRAMESET_25 BATTLEANIMFRAMESET_26
        // CALL(aReinitBattleAnimFrameset);
        ReinitBattleAnimFrameset_Conv(bc, BATTLEANIMFRAMESET_24 + bc->param);
        fallthrough;

    case 1:
    // one:
        // LD_HL(BATTLEANIMSTRUCT_XCOORD);
        // ADD_HL_BC;
        // LD_A_hl;
        // CP_A(0xb8);
        // IF_C goto move;
        if(bc->xCoord < 0xb8) {
            // CALL(aDeinitBattleAnimation);
            DeinitBattleAnimation_Conv(bc);
            // RET;
            return;
        }

    // move:
        // LD_A(0x2);
        // CALL(aBattleAnim_StepToTarget);
        BattleAnim_StepToTarget(bc, 0x2);
        // LD_HL(BATTLEANIMSTRUCT_VAR1);
        // ADD_HL_BC;
        // LD_A_hl;
        // DEC_hl;
        // LD_D(0x8);
        // CALL(aBattleAnim_Sine);
        // LD_HL(BATTLEANIMSTRUCT_YOFFSET);
        // ADD_HL_BC;
        // LD_hl_A;
        bc->yOffset = BattleAnim_Sine_Conv(bc->var1--, 0x8);
        // RET;
        return;
    }
}

void BattleAnimFunction_WaterGun(struct BattleAnim* bc) {
    // SET_PC(aBattleAnimFunction_WaterGun);
    // CALL(aBattleAnim_AnonJumptable);

// anon_dw:

    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 0) goto zero;
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 1) goto one;
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 2) goto two;
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 3) goto three;
    switch(bc->jumptableIndex) {
    case 0:
    // zero:
        // CALL(aBattleAnim_IncAnonJumptableIndex);
        bc->jumptableIndex++;
        fallthrough;

    case 1:
    // one:
        // LD_HL(BATTLEANIMSTRUCT_YCOORD);
        // ADD_HL_BC;
        // LD_A_hl;
        // CP_A(0x30);
        // IF_C goto run_down;
        if(bc->yCoord >= 0x30) {
            // LD_A(0x2);
            // CALL(aBattleAnim_StepToTarget);
            BattleAnim_StepToTarget(bc, 0x2);
            // LD_HL(BATTLEANIMSTRUCT_VAR1);
            // ADD_HL_BC;
            // LD_A_hl;
            // DEC_hl;
            // LD_D(0x8);
            // CALL(aBattleAnim_Sine);
            // LD_HL(BATTLEANIMSTRUCT_YOFFSET);
            // ADD_HL_BC;
            // LD_hl_A;
            bc->yOffset = BattleAnim_Sine_Conv(bc->var1--, 0x8);
            // RET;
            return;
        }

    // run_down:
        // CALL(aBattleAnim_IncAnonJumptableIndex);
        bc->jumptableIndex++;
        // LD_A(BATTLEANIMFRAMESET_28);
        // CALL(aReinitBattleAnimFrameset);
        ReinitBattleAnimFrameset_Conv(bc, BATTLEANIMFRAMESET_28);
        // LD_HL(BATTLEANIMSTRUCT_YOFFSET);
        // ADD_HL_BC;
        // LD_hl(0x0);
        bc->yOffset = 0x0;
        // LD_HL(BATTLEANIMSTRUCT_YCOORD);
        // ADD_HL_BC;
        // LD_hl(0x30);
        bc->yCoord = 0x30;
        // LD_HL(BATTLEANIMSTRUCT_OAMFLAGS);
        // ADD_HL_BC;
        // LD_A_hl;
        // AND_A(0x1);
        // LD_hl_A;
        bc->oamFlags &= 0x1;
        fallthrough;

    case 2:
    // two:
        // LD_HL(BATTLEANIMSTRUCT_YOFFSET);
        // ADD_HL_BC;
        // LD_A_hl;
        // CP_A(0x18);
        // IF_NC goto splash;
        if(bc->yOffset < 0x18) {
            // INC_hl;
            bc->yOffset++;
            // RET;
        }

    // splash:
        // CALL(aBattleAnim_IncAnonJumptableIndex);
        bc->jumptableIndex++;
        // LD_A(BATTLEANIMFRAMESET_29);
        // CALL(aReinitBattleAnimFrameset);
        ReinitBattleAnimFrameset_Conv(bc, BATTLEANIMFRAMESET_29);
        fallthrough;

    case 3:
    // three:
        // RET;
        return;
    }
}

//  Obj moves down and disappears at x coord $38
void BattleAnimFunction_Powder(struct BattleAnim* bc) {
    // SET_PC(aBattleAnimFunction_Powder);
    // LD_HL(BATTLEANIMSTRUCT_YOFFSET);
    // ADD_HL_BC;
    // LD_A_hl;
    // CP_A(0x38);
    // IF_C goto move;
    if(bc->yOffset >= 0x38) {
        // CALL(aDeinitBattleAnimation);
        DeinitBattleAnimation_Conv(bc);
        // RET;
        return;
    }

// move:
    // LD_A_hl;
    // LD_HL(BATTLEANIMSTRUCT_VAR1);
    // ADD_HL_BC;
    // LD_L_hl;
    // LD_H_A;
    // LD_DE(0x80);
    // ADD_HL_DE;
    uint16_t hl = ((bc->yOffset << 8) | bc->var1) + 0x80;
    // LD_E_L;
    // LD_D_H;
    // LD_HL(BATTLEANIMSTRUCT_VAR1);
    // ADD_HL_BC;
    // LD_hl_E;
    bc->var1 = LOW(hl);
    // LD_HL(BATTLEANIMSTRUCT_YOFFSET);
    // ADD_HL_BC;
    // LD_hl_D;
    bc->yOffset = HIGH(hl);
    // Shakes object back and forth 16 pixels
    // LD_HL(BATTLEANIMSTRUCT_XOFFSET);
    // ADD_HL_BC;
    // LD_A_hl;
    // XOR_A(0x10);
    // LD_hl_A;
    bc->xOffset ^= 0x10;
    // RET;
}

//  Obj moves in an ever shrinking circle. Obj Param defines initial position in the circle
void BattleAnimFunction_Recover(struct BattleAnim* bc) {
    // SET_PC(aBattleAnimFunction_Recover);
    // CALL(aBattleAnim_AnonJumptable);

// anon_dw:

    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 0) goto zero;
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 1) goto one;

    switch(bc->jumptableIndex) {
    case 0:
    // zero:
        // CALL(aBattleAnim_IncAnonJumptableIndex);
        bc->jumptableIndex++;
        // LD_HL(BATTLEANIMSTRUCT_PARAM);
        // ADD_HL_BC;
        // LD_A_hl;
        // AND_A(0xf0);
        // LD_HL(BATTLEANIMSTRUCT_VAR2);
        // ADD_HL_BC;
        // LD_hl_A;
        bc->var2 = bc->param & 0xf0;
        // LD_HL(BATTLEANIMSTRUCT_PARAM);
        // ADD_HL_BC;
        // LD_A_hl;
        // AND_A(0xf);
        // SLA_A;
        // SLA_A;
        // SLA_A;
        // LD_HL(BATTLEANIMSTRUCT_VAR1);
        // ADD_HL_BC;
        // LD_hl_A;
        bc->var1 = (bc->param & 0xf) << 4;
        // LD_HL(BATTLEANIMSTRUCT_PARAM);
        // ADD_HL_BC;
        // LD_hl(0x1);
        bc->param = 0x1;
        fallthrough;

    case 1: {
    // one:
        // LD_HL(BATTLEANIMSTRUCT_VAR2);
        // ADD_HL_BC;
        // LD_A_hl;
        // AND_A_A;
        // IF_NZ goto move;
        if(bc->var2 == 0) {
            // CALL(aDeinitBattleAnimation);
            DeinitBattleAnimation_Conv(bc);
            // RET;
            return;
        }

    // move:
        // LD_HL(BATTLEANIMSTRUCT_VAR1);
        // ADD_HL_BC;
        // LD_A_hl;
        // INC_hl;
        uint8_t a = bc->var1++;
        // LD_HL(BATTLEANIMSTRUCT_VAR2);
        // ADD_HL_BC;
        // LD_D_hl;
        // PUSH_AF;
        // PUSH_DE;
        // CALL(aBattleAnim_Sine);
        // LD_HL(BATTLEANIMSTRUCT_YOFFSET);
        // ADD_HL_BC;
        // LD_hl_A;
        bc->yOffset = BattleAnim_Sine_Conv(a, bc->var2);
        // POP_DE;
        // POP_AF;
        // CALL(aBattleAnim_Cosine);
        // LD_HL(BATTLEANIMSTRUCT_XOFFSET);
        // ADD_HL_BC;
        // LD_hl_A;
        bc->xOffset = BattleAnim_Cosine_Conv(a, bc->var2);
        // LD_HL(BATTLEANIMSTRUCT_PARAM);
        // ADD_HL_BC;
        // LD_A_hl;
        // XOR_A(0x1);
        // LD_hl_A;
        bc->param ^= 0x1;
        // RET_Z;
        if(bc->param == 0)
            return;
        // LD_HL(BATTLEANIMSTRUCT_VAR2);
        // ADD_HL_BC;
        // DEC_hl;
        bc->var2--;
        // RET;
    } return;
    }
}

void BattleAnimFunction_ThunderWave(struct BattleAnim* bc) {
    // SET_PC(aBattleAnimFunction_ThunderWave);
    // CALL(aBattleAnim_AnonJumptable);

// anon_dw:

    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 0) goto zero;
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 1) goto one;
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 2) goto two;
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 3) goto three;

    switch(bc->jumptableIndex) {
    case 1:
    // one:
        // CALL(aBattleAnim_IncAnonJumptableIndex);
        bc->jumptableIndex++;
        // LD_A(BATTLEANIMFRAMESET_35);
        // CALL(aReinitBattleAnimFrameset);
        ReinitBattleAnimFrameset_Conv(bc, BATTLEANIMFRAMESET_35);
        fallthrough;

    case 0:
    // zero:
    case 2:
    // two:
        // RET;
        return;

    case 3:
    // three:
        // CALL(aDeinitBattleAnimation);
        DeinitBattleAnimation_Conv(bc);
        // RET;
        return;
    }
}

//  Claps two objects together, twice. Also used by Encore
//  Second object's frameset and position relative to first are both defined via this function
//  Obj Param: Distance from center (masked with $7F). Bit 7 flips object horizontally by switching to a different frameset
void BattleAnimFunction_Clamp_Encore(struct BattleAnim* bc) {
    // SET_PC(aBattleAnimFunction_Clamp_Encore);
    // CALL(aBattleAnim_AnonJumptable);

// anon_dw:

    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 0) goto zero;
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 1) goto one;
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 2) goto two;
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 3) goto three;
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 4) goto four;
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 5) goto five;
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 6) goto six;
    switch(bc->jumptableIndex) {
    case 0:
    // zero:
        // CALL(aBattleAnim_IncAnonJumptableIndex);
        bc->jumptableIndex++;
        // LD_HL(BATTLEANIMSTRUCT_FRAMESET_ID);
        // ADD_HL_BC;
        // LD_A_hl;
        // LD_HL(BATTLEANIMSTRUCT_VAR2);
        // ADD_HL_BC;
        // LD_hl_A;
        bc->var2 = bc->framesetId;
        // LD_HL(BATTLEANIMSTRUCT_PARAM);
        // ADD_HL_BC;
        // BIT_hl(7);
        // IF_NZ goto flipped;
        if(bit_test(bc->param, 7)) {
        // flipped:
            // LD_HL(BATTLEANIMSTRUCT_VAR1);
            // ADD_HL_BC;
            // LD_hl(0x30);
            bc->var1 = 0x30;
        }
        else {
            // LD_HL(BATTLEANIMSTRUCT_VAR1);
            // ADD_HL_BC;
            // LD_hl(0x10);
            bc->var1 = 0x10;
            // goto got_sine_start;
        }

    // got_sine_start:
        // LD_HL(BATTLEANIMSTRUCT_PARAM);
        // ADD_HL_BC;
        // LD_A_hl;
        // AND_A(0x7f);
        // LD_hl_A;
        bc->param &= 0x7f;
        fallthrough;

    case 1:
    // one:
        // LD_HL(BATTLEANIMSTRUCT_VAR1);
        // ADD_HL_BC;
        // LD_A_hl;
        // LD_HL(BATTLEANIMSTRUCT_PARAM);
        // ADD_HL_BC;
        // LD_D_hl;
        // CALL(aBattleAnim_Sine);
        // LD_HL(BATTLEANIMSTRUCT_XOFFSET);
        // ADD_HL_BC;
        // LD_hl_A;
        bc->xOffset = BattleAnim_Sine_Conv(bc->var1, bc->param);
        // BIT_A(7);
        // IF_NZ goto load_no_inc;
        if(bit_test(bc->xOffset, 7)) {
        // load_no_inc:
            // LD_HL(BATTLEANIMSTRUCT_VAR2);
            // ADD_HL_BC;
            // LD_A_hl;  // BATTLEANIMFRAMESET_3A (Clamp)
            // ['?']  // BATTLEANIMFRAMESET_A0 (Hands)
            ReinitBattleAnimFrameset_Conv(bc, bc->var2);
        }
        else {
            // LD_HL(BATTLEANIMSTRUCT_VAR2);
            // ADD_HL_BC;
            // LD_A_hl;
            // INC_A;  // BATTLEANIMFRAMESET_3B (Clamp Flipped)
            // // ['?']  // BATTLEANIMFRAMESET_A1 (Hands Flipped)
            ReinitBattleAnimFrameset_Conv(bc, bc->var2 + 1);
            // goto reinit;
        }

    // reinit:
        // CALL(aReinitBattleAnimFrameset);
        // LD_HL(BATTLEANIMSTRUCT_VAR1);
        // ADD_HL_BC;
        // INC_hl;
        // LD_A_hl;
        // AND_A(0x1f);
        // RET_NZ;
        if(++bc->var1 & 0x1f)
            return;
        fallthrough;

    case 2:
    // two:
    case 3:
    // three:
    case 4:
    // four:
    case 5:
    // five:
        // CALL(aBattleAnim_IncAnonJumptableIndex);
        bc->jumptableIndex++;
        // RET;
        return;

    case 6:
    // six:
        // LD_HL(BATTLEANIMSTRUCT_JUMPTABLE_INDEX);
        // ADD_HL_BC;
        // LD_hl(0x1);
        bc->jumptableIndex = 0x1;
        // RET;
        return;
    }
}

//  Claps two objects together (vertically), twice
//  Second object's frameset and position relative to first are both defined via this function
//  Obj Param: Distance from center (masked with $7F). Bit 7 flips object vertically by switching to a different frameset
void BattleAnimFunction_Bite(struct BattleAnim* bc) {
    // SET_PC(aBattleAnimFunction_Bite);
    // CALL(aBattleAnim_AnonJumptable);

// anon_dw:

    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 0) goto zero;
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 1) goto one;
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 2) goto two;
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 3) goto three;
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 4) goto four;
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 5) goto five;
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 6) goto six;
    switch(bc->jumptableIndex) {
    case 0:
    // zero:
        // CALL(aBattleAnim_IncAnonJumptableIndex);
        bc->jumptableIndex++;
        // LD_HL(BATTLEANIMSTRUCT_PARAM);
        // ADD_HL_BC;
        // BIT_hl(7);
        // IF_NZ goto flipped;
        if(bit_test(bc->param, 7)) {
        // flipped:
            // LD_HL(BATTLEANIMSTRUCT_VAR1);
            // ADD_HL_BC;
            // LD_hl(0x30);
            bc->var1 = 0x30;
        }
        else {
            // LD_HL(BATTLEANIMSTRUCT_VAR1);
            // ADD_HL_BC;
            // LD_hl(0x10);
            bc->var1 = 0x10;
            // goto got_sine_start;
        }

    // got_sine_start:
        // LD_HL(BATTLEANIMSTRUCT_PARAM);
        // ADD_HL_BC;
        // LD_A_hl;
        // AND_A(0x7f);
        // LD_hl_A;
        bc->param &= 0x7f;
        fallthrough;

    case 1:
    // one:
        // LD_HL(BATTLEANIMSTRUCT_VAR1);
        // ADD_HL_BC;
        // LD_A_hl;
        // LD_HL(BATTLEANIMSTRUCT_PARAM);
        // ADD_HL_BC;
        // LD_D_hl;
        // CALL(aBattleAnim_Sine);
        // LD_HL(BATTLEANIMSTRUCT_YOFFSET);
        // ADD_HL_BC;
        // LD_hl_A;
        bc->yOffset = BattleAnim_Sine_Conv(bc->var1, bc->param);
        // BIT_A(7);
        // IF_NZ goto flipped2;
        if(bit_test(bc->yOffset, 7)) {
        // flipped2:
            // LD_A(BATTLEANIMFRAMESET_3C);
            ReinitBattleAnimFrameset_Conv(bc, BATTLEANIMFRAMESET_3C);
        }
        else {
            // LD_A(BATTLEANIMFRAMESET_3D);
            ReinitBattleAnimFrameset_Conv(bc, BATTLEANIMFRAMESET_3D);
            // goto got_frameset;
        }

    // got_frameset:
        // CALL(aReinitBattleAnimFrameset);
        // LD_HL(BATTLEANIMSTRUCT_VAR1);
        // ADD_HL_BC;
        // INC_hl;
        // INC_hl;
        bc->var1 += 2;
        // LD_A_hl;
        // AND_A(0x1f);
        // RET_NZ;
        if(bc->var1 & 0x1f)
            return;
        fallthrough;

    case 2:
    // two:
    case 3:
    // three:
    case 4:
    // four:
    case 5:
    // five:
        // CALL(aBattleAnim_IncAnonJumptableIndex);
        bc->jumptableIndex++;
        // RET;
        return;

    case 6:
    // six:
        // LD_HL(BATTLEANIMSTRUCT_JUMPTABLE_INDEX);
        // ADD_HL_BC;
        // LD_hl(0x1);
        bc->jumptableIndex = 0x1;
        // RET;
        return;
    }
}

//  Solar Beam charge up animation
void BattleAnimFunction_SolarBeam(struct BattleAnim* bc) {
    // SET_PC(aBattleAnimFunction_SolarBeam);
    // CALL(aBattleAnim_AnonJumptable);

// anon_dw:

    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 0) goto zero;
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 1) goto one;

    switch(bc->jumptableIndex) {
    case 0:
    // zero:
        // CALL(aBattleAnim_IncAnonJumptableIndex);
        bc->jumptableIndex++;
        // LD_HL(BATTLEANIMSTRUCT_VAR1);
        // ADD_HL_BC;
        // LD_hl(0x28);
        bc->var1 = 0x28;
        // INC_HL;
        // LD_hl(0x0);
        bc->var2 = 0x0;
        fallthrough;

    case 1: {
    // one:
        // LD_HL(BATTLEANIMSTRUCT_PARAM);
        // ADD_HL_BC;
        // LD_A_hl;
        // LD_HL(BATTLEANIMSTRUCT_VAR1);
        // ADD_HL_BC;
        // LD_D_hl;
        // PUSH_AF;
        // PUSH_DE;
        // CALL(aBattleAnim_Sine);
        // LD_HL(BATTLEANIMSTRUCT_YOFFSET);
        // ADD_HL_BC;
        // LD_hl_A;
        bc->yOffset = BattleAnim_Sine_Conv(bc->param, bc->var1);
        // POP_DE;
        // POP_AF;
        // CALL(aBattleAnim_Cosine);
        // LD_HL(BATTLEANIMSTRUCT_XOFFSET);
        // ADD_HL_BC;
        // LD_hl_A;
        bc->xOffset = BattleAnim_Cosine_Conv(bc->param, bc->var1);
        // LD_HL(BATTLEANIMSTRUCT_VAR1);
        // ADD_HL_BC;
        // LD_A_hl;
        // AND_A_A;
        // IF_Z goto zero_radius;
        if(bc->var1 == 0) {
        // zero_radius:
            // CALL(aDeinitBattleAnimation);
            DeinitBattleAnimation_Conv(bc);
            // RET;
            return;
        }
        // LD_D_A;
        // LD_HL(BATTLEANIMSTRUCT_VAR2);
        // ADD_HL_BC;
        // LD_E_hl;
        // LD_HL(-0x80);
        // ADD_HL_DE;
        uint16_t hl = ((bc->var1 << 8) | bc->var2) - 0x80;
        // LD_E_L;
        // LD_D_H;
        // LD_HL(BATTLEANIMSTRUCT_VAR2);
        // ADD_HL_BC;
        // LD_hl_E;
        bc->var2 = LOW(hl);
        // LD_HL(BATTLEANIMSTRUCT_VAR1);
        // ADD_HL_BC;
        // LD_hl_D;
        bc->var1 = HIGH(hl);
        // RET;
    } return;
    }
}

static uint8_t BattleAnimFunction_Gust_GetGustRadius(struct BattleAnim* bc) {
    static const uint8_t GustOffsets[] = {
        8, 6, 5, 4, 5, 6, 8, 12, 16
    };
    // LD_HL(BATTLEANIMSTRUCT_VAR2);
    // ADD_HL_BC;
    // LD_E_hl;
    // LD_D(0);
    // LD_HL(mBattleAnimFunction_Gust_GustOffsets);
    // ADD_HL_DE;
    // LD_D_hl;
    // RET;
    return GustOffsets[bc->var2];
}

static void BattleAnimFunction_Gust_GustWobble(struct BattleAnim* bc) {
    // Circular movement where width is retrieved from a list, and height is 1/16 of that
    // CALL(aBattleAnimFunction_Gust_GetGustRadius);
    uint8_t d = BattleAnimFunction_Gust_GetGustRadius(bc);
    // LD_HL(BATTLEANIMSTRUCT_VAR1);
    // ADD_HL_BC;
    // LD_A_hl;
    // PUSH_AF;
    // PUSH_DE;
    // CALL(aBattleAnim_Sine);
    int8_t sine = (int8_t)BattleAnim_Sine_Conv(bc->var1, d);
    // SRA_A;
    // SRA_A;
    // SRA_A;
    // SRA_A;
    // LD_HL(BATTLEANIMSTRUCT_PARAM);
    // ADD_HL_BC;
    // ADD_A_hl;
    // LD_HL(BATTLEANIMSTRUCT_YOFFSET);
    // ADD_HL_BC;
    // LD_hl_A;
    bc->yOffset = (sine >> 4) + bc->param;
    // POP_DE;
    // POP_AF;
    // CALL(aBattleAnim_Cosine);
    // LD_HL(BATTLEANIMSTRUCT_XOFFSET);
    // ADD_HL_BC;
    // LD_hl_A;
    bc->xOffset = BattleAnim_Cosine_Conv(bc->var1, d);
    // LD_HL(BATTLEANIMSTRUCT_VAR1);
    // ADD_HL_BC;
    // LD_A_hl;
    // SUB_A(0x8);
    // LD_hl_A;
    bc->var1 -= 0x8;
    // LD_HL(BATTLEANIMSTRUCT_PARAM);
    // ADD_HL_BC;
    // LD_A_hl;
    // AND_A_A;
    // IF_Z goto start_wobble;
    // CP_A(0xc2);
    // IF_C goto finish_wobble;
    if(bc->param != 0 && bc->param < 0xc2) {
    // finish_wobble:
        // XOR_A_A;
        // LD_HL(BATTLEANIMSTRUCT_VAR2);
        // ADD_HL_BC;
        // LD_hl_A;
        bc->var2 = 0;
        // LD_HL(BATTLEANIMSTRUCT_PARAM);
        // ADD_HL_BC;
        // LD_hl_A;
        bc->param = 0;
        // LD_HL(BATTLEANIMSTRUCT_XOFFSET);
        // ADD_HL_BC;
        // LD_hli_A;
        bc->xOffset = 0;
        // LD_hl_A;
        bc->yOffset = 0;
        // RET;
        return;
    }
    else {
    // start_wobble:
        // DEC_A;
        // LD_hl_A;
        bc->param--;
        // AND_A(0x7);
        // RET_NZ;
        if(bc->param & 0x7)
            return;
        // LD_HL(BATTLEANIMSTRUCT_VAR2);
        // ADD_HL_BC;
        // INC_hl;
        bc->var2++;
        // RET;
        return;
    }
}

void BattleAnimFunction_Gust(struct BattleAnim* bc) {
    // SET_PC(aBattleAnimFunction_Gust);
    // CALL(aBattleAnim_AnonJumptable);

// anon_dw:

    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 0) goto zero;
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 1) goto one;
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 2) goto two;
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 3) goto three;
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 4) goto four;

    switch(bc->jumptableIndex) {
    case 0:
    // zero:
        // CALL(aBattleAnim_IncAnonJumptableIndex);
        bc->jumptableIndex++;
        // LD_HL(BATTLEANIMSTRUCT_PARAM);
        // ADD_HL_BC;
        // LD_hl(0);
        bc->param = 0;
        fallthrough;

    case 1:
    // one:
    case 3:
    // three:
        // CALL(aBattleAnimFunction_Gust_GustWobble);
        BattleAnimFunction_Gust_GustWobble(bc);
        // RET;
        return;

    case 2:
    // two:
        // LD_HL(BATTLEANIMSTRUCT_XCOORD);
        // ADD_HL_BC;
        // LD_A_hl;
        // CP_A(0x88);
        // IF_C goto move;
        if(bc->xCoord < 0x88)
            break;
        // CALL(aBattleAnim_IncAnonJumptableIndex);
        bc->jumptableIndex++;
        // RET;
        return;

    case 4:
    // four:
        // LD_HL(BATTLEANIMSTRUCT_XCOORD);
        // ADD_HL_BC;
        // LD_A_hl;
        // CP_A(0xb8);
        // IF_C goto move;
        if(bc->xCoord < 0xb8)
            break;
        // CALL(aDeinitBattleAnimation);
        DeinitBattleAnimation_Conv(bc);
        // RET;
        return;
    }

// move:
    // CALL(aBattleAnimFunction_Gust_GustWobble);
    BattleAnimFunction_Gust_GustWobble(bc);
    // Move horizontally every frame
    // LD_HL(BATTLEANIMSTRUCT_XCOORD);
    // ADD_HL_BC;
    // INC_hl;
    // LD_A_hl;
    // Move in the vertically every other frame
    // AND_A(0x1);
    // RET_NZ;
    if(++bc->xCoord & 0x1)
        return;
    // LD_HL(BATTLEANIMSTRUCT_YCOORD);
    // ADD_HL_BC;
    // DEC_hl;
    bc->yCoord--;
    // RET;
    return;
}

//  Moves object from target to user and disappears when reaches x coord $30. Example: Absorb, Mega Drain, Leech Seed status
//  Obj Param: Speed in the X axis
void BattleAnimFunction_Absorb(struct BattleAnim* bc) {
    // SET_PC(aBattleAnimFunction_Absorb);
    // LD_HL(BATTLEANIMSTRUCT_XCOORD);
    // ADD_HL_BC;
    // LD_A_hl;
    // CP_A(0x30);
    // IF_NC goto move;
    if(bc->xCoord < 0x30) {
        // CALL(aDeinitBattleAnimation);
        DeinitBattleAnimation_Conv(bc);
        // RET;
        return;
    }

// move:
    // LD_HL(BATTLEANIMSTRUCT_PARAM);
    // ADD_HL_BC;
    // LD_A_hl;
    // AND_A(0xf);
    // LD_E_A;
    // LD_HL(BATTLEANIMSTRUCT_XCOORD);
    // ADD_HL_BC;
    // LD_A_hl;
    // SUB_A_E;
    // LD_hl_A;
    bc->xCoord -= bc->param & 0xf;
    // SRL_E;
    // LD_HL(BATTLEANIMSTRUCT_YCOORD);
    // ADD_HL_BC;

// loop:
    // INC_hl;
    // DEC_E;
    // IF_NZ goto loop;
    bc->yCoord += (bc->param & 0xf) >> 1;
    // RET;
}

//  Plays out object Frameset. Use anim_incobj to move to next frameset
void BattleAnimFunction_Wrap(struct BattleAnim* bc) {
    // SET_PC(aBattleAnimFunction_Wrap);
    // CALL(aBattleAnim_AnonJumptable);

// anon_dw:

    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 0) goto zero;
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 1) goto one;
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 2) goto two;
    switch(bc->jumptableIndex) {
    case 1:
    // one:
        // LD_HL(BATTLEANIMSTRUCT_FRAMESET_ID);
        // ADD_HL_BC;
        // LD_A_hl;
        // INC_A;  // BATTLEANIMFRAMESET_53
        // ['?']  // BATTLEANIMFRAMESET_55
        // CALL(aReinitBattleAnimFrameset);
        ReinitBattleAnimFrameset_Conv(bc, bc->framesetId + 1);
        // CALL(aBattleAnim_IncAnonJumptableIndex);
        bc->jumptableIndex++;
        // LD_HL(BATTLEANIMSTRUCT_VAR1);  // Unused?
        // ADD_HL_BC;
        // LD_hl(0x8);
        bc->var1 = 0x8;
        fallthrough;

    case 0:
    // zero:
    case 2:
    // two:
        // RET;
        return;
    }
}

void BattleAnimFunction_LeechSeed(struct BattleAnim* bc) {
    // SET_PC(aBattleAnimFunction_LeechSeed);
    // CALL(aBattleAnim_AnonJumptable);

// anon_dw:

    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 0) goto zero;
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 1) goto one;
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 2) goto two;
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 3) goto three;

    switch(bc->jumptableIndex) {
    case 0:
    // zero:
        // CALL(aBattleAnim_IncAnonJumptableIndex);
        bc->jumptableIndex++;
        // LD_HL(BATTLEANIMSTRUCT_VAR2);
        // ADD_HL_BC;
        // LD_hl(0x40);
        bc->var2 = 0x40;
        // RET;
        return;

    case 1:
    // one:
        // LD_HL(BATTLEANIMSTRUCT_VAR2);
        // ADD_HL_BC;
        // LD_A_hl;
        // CP_A(0x20);
        // IF_C goto sprout;
        if(bc->var2 >= 0x20) {
            // CALL(aBattleAnim_StepThrownToTarget);
            BattleAnim_StepThrownToTarget(bc, &bc->var2, bc->var2);
            // RET;
            return;
        }

    // sprout:
        // LD_hl(0x40);
        bc->var2 = 0x40;
        // LD_A(BATTLEANIMFRAMESET_57);
        // CALL(aReinitBattleAnimFrameset);
        ReinitBattleAnimFrameset_Conv(bc, BATTLEANIMFRAMESET_57);
        // CALL(aBattleAnim_IncAnonJumptableIndex);
        bc->jumptableIndex++;
        // RET;
        return;

    case 2:
    // two:
        // LD_HL(BATTLEANIMSTRUCT_VAR2);
        // ADD_HL_BC;
        // LD_A_hl;
        // AND_A_A;
        // IF_Z goto flutter;
        if(bc->var2 != 0) {
            // DEC_hl;
            --bc->var2;
            // RET;
            return;
        }

    // flutter:
        // CALL(aBattleAnim_IncAnonJumptableIndex);
        bc->jumptableIndex++;
        // LD_A(BATTLEANIMFRAMESET_58);
        // CALL(aReinitBattleAnimFrameset);
        ReinitBattleAnimFrameset_Conv(bc, BATTLEANIMFRAMESET_58);
        fallthrough;

    case 3:
    // three:
        // RET;
        return;
    }
}

//  Inches object towards the opponent's side in a parabola arc defined by the lower and upper nybble of Obj Param
void BattleAnim_StepThrownToTarget(struct BattleAnim* bc, uint8_t* hl, uint8_t a) {
    // SET_PC(aBattleAnim_StepThrownToTarget);
    // DEC_hl;
    (*hl)--;
    // LD_D(0x20);
    // CALL(aBattleAnim_Sine);
    // LD_HL(BATTLEANIMSTRUCT_YOFFSET);
    // ADD_HL_BC;
    // LD_hl_A;
    bc->yOffset = BattleAnim_Sine_Conv(a, 0x20);
    // LD_HL(BATTLEANIMSTRUCT_FIX_Y);
    // ADD_HL_BC;
    // LD_A_hl;
    // ADD_A(0x2);
    // LD_hl_A;
    bc->fixY += 0x2;
    // LD_HL(BATTLEANIMSTRUCT_VAR1);
    // ADD_HL_BC;
    // LD_E_hl;
    // LD_HL(BATTLEANIMSTRUCT_XCOORD);
    // ADD_HL_BC;
    // LD_D_hl;
    uint16_t de = (bc->xCoord << 8) | bc->var1;
    // LD_HL(BATTLEANIMSTRUCT_PARAM);
    // ADD_HL_BC;
    // LD_H_hl;
    // LD_A_H;
    // AND_A(0xf);
    // SWAP_A;
    // LD_L_A;
    // LD_A_H;
    // AND_A(0xf0);
    // SWAP_A;
    // LD_H_A;
    // ADD_HL_DE;
    de += (uint16_t)(((bc->param & 0xf) << 4) | ((bc->param & 0xf0) << 4));
    // LD_E_L;
    // LD_D_H;
    // LD_HL(BATTLEANIMSTRUCT_VAR1);
    // ADD_HL_BC;
    // LD_hl_E;
    bc->var1 = LOW(de);
    // LD_HL(BATTLEANIMSTRUCT_XCOORD);
    // ADD_HL_BC;
    // LD_hl_D;
    bc->xCoord = HIGH(de);
    // LD_HL(BATTLEANIMSTRUCT_VAR2);
    // ADD_HL_BC;
    // LD_A_hl;
    // AND_A(0x1);
    // RET_NZ;
    if(bc->var2 & 0x1)
        return;
    // LD_HL(BATTLEANIMSTRUCT_YCOORD);
    // ADD_HL_BC;
    // DEC_hl;
    bc->yCoord--;
    // RET;
}

//  Object is thrown at target. After $20 frames it stops and waits another $20 frames then disappear
void BattleAnimFunction_Spikes(struct BattleAnim* bc) {
    // SET_PC(aBattleAnimFunction_Spikes);
    // CALL(aBattleAnim_AnonJumptable);

// anon_dw:

    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 0) goto zero;
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 1) goto one;
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 2) goto two;

    switch(bc->jumptableIndex) {
    case 0:
    // zero:
        // CALL(aBattleAnim_IncAnonJumptableIndex);
        bc->jumptableIndex++;
        // LD_HL(BATTLEANIMSTRUCT_VAR2);
        // ADD_HL_BC;
        // LD_hl(0x40);
        bc->var2 = 0x40;
        // RET;
        return;

    case 1:
    // one:
        // LD_HL(BATTLEANIMSTRUCT_VAR2);
        // ADD_HL_BC;
        // LD_A_hl;
        // CP_A(0x20);
        // IF_C goto wait;
        if(bc->var2 >= 0x20) {
            // CALL(aBattleAnim_StepThrownToTarget);
            BattleAnim_StepThrownToTarget(bc, &bc->var2, bc->var2);
            // RET;
        }

    // wait:
        // CALL(aBattleAnim_IncAnonJumptableIndex);
        bc->jumptableIndex++;
        fallthrough;

    case 2:
    // two:
        // RET;
        return;
    }
}

// Causes object to skip ahead the circular motion every frame
void BattleAnimFunction_RazorWind(struct BattleAnim* bc) {
    // SET_PC(aBattleAnimFunction_RazorWind);
    // CALL(aBattleAnimFunction_MoveInCircle);
    BattleAnimFunction_MoveInCircle(bc);
    // LD_HL(BATTLEANIMSTRUCT_VAR1);
    // ADD_HL_BC;
    // LD_A_hl;
    // ADD_A(0xf);
    // LD_hl_A;
    bc->var2 += 0xf;
    // RET;
}

//  Uses anim_setobj for different kick types
void BattleAnimFunction_Kick(struct BattleAnim* bc) {
    // SET_PC(aBattleAnimFunction_Kick);
    // CALL(aBattleAnim_AnonJumptable);

// anon_dw:

    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 0) goto zero;
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 1) goto one;
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 2) goto two;  // Jump Kick, Hi Jump Kick
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 3) goto three;  // Rolling Kick
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 4) goto four;  // Rolling Kick (continued)

    switch(bc->jumptableIndex) {
    case 0:
    // zero:
        // RET;
        return;

    case 1:
    // one:
        //
        //  Unused?
        // LD_HL(BATTLEANIMSTRUCT_YCOORD);
        // ADD_HL_BC;
        // LD_A_hl;
        // CP_A(0x30);
        // IF_C goto move_down;
        if(bc->yCoord < 0x30) {
        // move_down:
            // ADD_A(0x4);
            // LD_hl_A;
            bc->yCoord += 0x4;
            // RET;
            return;
        }
        // LD_HL(BATTLEANIMSTRUCT_JUMPTABLE_INDEX);
        // ADD_HL_BC;
        // LD_hl(0x0);
        bc->jumptableIndex = 0x0;
        // RET;
        return;

    case 2:
    // two:
        // LD_HL(BATTLEANIMSTRUCT_XCOORD);
        // ADD_HL_BC;
        // LD_A_hl;
        // CP_A(0x98);
        // RET_NC;
        if(bc->xCoord >= 0x98)
            return;
        // INC_hl;
        // INC_hl;
        bc->xCoord += 2;
        // LD_HL(BATTLEANIMSTRUCT_OAMFLAGS);
        // ADD_HL_BC;
        // SET_hl(0);
        bit_set(bc->oamFlags, 0);
        // LD_HL(BATTLEANIMSTRUCT_FIX_Y);
        // ADD_HL_BC;
        // LD_hl(0x90);
        bc->fixY = 0x90;
        // LD_HL(BATTLEANIMSTRUCT_FRAME);
        // ADD_HL_BC;
        // LD_hl(0x0);
        bc->frame = 0x0;
        // LD_HL(BATTLEANIMSTRUCT_DURATION);
        // ADD_HL_BC;
        // LD_hl(0x2);
        bc->duration = 0x2;
        // LD_HL(BATTLEANIMSTRUCT_YCOORD);
        // ADD_HL_BC;
        // DEC_hl;
        bc->yCoord--;
        // RET;
        return;

    case 3:
    // three:
        // CALL(aBattleAnim_IncAnonJumptableIndex);
        bc->jumptableIndex++;
        // LD_HL(BATTLEANIMSTRUCT_VAR1);
        // ADD_HL_BC;
        // LD_hl(0x2c);
        bc->var1 = 0x2c;
        // LD_HL(BATTLEANIMSTRUCT_FRAME);
        // ADD_HL_BC;
        // LD_hl(0x0);
        bc->frame = 0x0;
        // LD_HL(BATTLEANIMSTRUCT_DURATION);
        // ADD_HL_BC;
        // LD_hl(0x80);
        bc->duration = 0x80;
        fallthrough;

    case 4:
    // four:
        // LD_HL(BATTLEANIMSTRUCT_XCOORD);
        // ADD_HL_BC;
        // LD_A_hl;
        // CP_A(0x98);
        // RET_NC;
        if(bc->xCoord >= 0x98)
            return;
        // INC_hl;
        // INC_hl;
        bc->xCoord += 2;
        // LD_HL(BATTLEANIMSTRUCT_VAR1);
        // ADD_HL_BC;
        // LD_A_hl;
        // INC_hl;
        // LD_D(0x8);
        // CALL(aBattleAnim_Sine);
        // LD_HL(BATTLEANIMSTRUCT_YOFFSET);
        // ADD_HL_BC;
        // LD_hl_A;
        bc->yOffset = BattleAnim_Sine_Conv(bc->var1++, 0x8);
        // RET;
        return;
    }
}

static void BattleAnimFunction_Egg_EggVerticalWaveMotion(struct BattleAnim* bc) {
    // LD_HL(BATTLEANIMSTRUCT_VAR1);
    // ADD_HL_BC;
    // LD_A_hli;
    // LD_D_hl;  // BATTLEANIMSTRUCT_VAR2
    // CALL(aBattleAnim_Sine);
    // LD_HL(BATTLEANIMSTRUCT_YOFFSET);
    // ADD_HL_BC;
    // LD_hl_A;
    bc->yOffset = BattleAnim_Sine_Conv(bc->var1, bc->var2);
    // LD_HL(BATTLEANIMSTRUCT_VAR1);
    // ADD_HL_BC;
    // INC_hl;
    // LD_A_hl;
    // AND_A(0x3f);  // cp 64
    // RET_NZ;
    if(++bc->var1 & 0x3f)
        return;
    // LD_HL(BATTLEANIMSTRUCT_VAR1);
    // ADD_HL_BC;
    // LD_hl(0x20);
    bc->var1 = 0x20;
    // LD_HL(BATTLEANIMSTRUCT_VAR2);
    // ADD_HL_BC;
    // LD_A_hl;
    // SUB_A(0x8);
    // LD_hl_A;
    bc->var2 -= 0x8;
    // RET_NZ;
    if(bc->var2 != 0)
        return;
    // XOR_A_A;
    // LD_HL(BATTLEANIMSTRUCT_VAR1);
    // ADD_HL_BC;
    // LD_hli_A;
    bc->var1 = 0;
    // LD_hl_A;
    bc->var2 = 0;
    // CALL(aBattleAnim_IncAnonJumptableIndex);
    bc->jumptableIndex++;
    // RET;
}

//  Used by Egg Bomb and Softboiled
//  Obj Param: Defines jumptable starting index
void BattleAnimFunction_Egg(struct BattleAnim* bc) {
    // SET_PC(aBattleAnimFunction_Egg);
    // CALL(aBattleAnim_AnonJumptable);

// anon_dw:

    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 0) goto zero;
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 1) goto one;  // Egg Bomb start
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 2) goto two;
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 3) goto three;
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 4) goto four;  // ret
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 5) goto five;
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 6) goto six;  // Softboiled obj 1 start
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 7) goto seven;
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 8) goto eight;
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 9) goto nine;
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 10) goto ten;  // ret
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 11) goto eleven;  // Softboiled obj 2 start
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 12) goto twelve;
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 13) goto thirteen;  // ret

    switch(bc->jumptableIndex) {
    case 0:
    // zero:
        // Object starts here then jumps to the jumptable index defined by the Obj Param
        // LD_HL(BATTLEANIMSTRUCT_VAR1);
        // ADD_HL_BC;
        // LD_hl(0x28);
        bc->var1 = 0x28;
        // INC_HL;  // BATTLEANIMSTRUCT_VAR2
        // LD_hl(0x10);
        bc->var2 = 0x10;
        // LD_HL(BATTLEANIMSTRUCT_PARAM);
        // ADD_HL_BC;
        // LD_A_hl;
        // LD_HL(BATTLEANIMSTRUCT_JUMPTABLE_INDEX);
        // ADD_HL_BC;
        // LD_hl_A;
        bc->jumptableIndex = bc->param;
        // RET;
        return;

    case 1:
    // one:
        // Initial Egg Bomb arc movement to x coord $40
        // LD_HL(BATTLEANIMSTRUCT_XCOORD);
        // ADD_HL_BC;
        // LD_A_hl;
        // CP_A(0x40);
        // IF_NC goto egg_bomb_vertical_wave;
        if(bc->xCoord >= 0x40) {
            // INC_hl;
            bc->xCoord++;
        }

    // egg_bomb_vertical_wave:
        // CALL(aBattleAnimFunction_Egg_EggVerticalWaveMotion);
        BattleAnimFunction_Egg_EggVerticalWaveMotion(bc);
        // RET;
        return;

    case 6:
    // six:
        // Initial Softboiled arc movement to x coord $4b
        // LD_HL(BATTLEANIMSTRUCT_XCOORD);
        // ADD_HL_BC;
        // LD_A_hl;
        // CP_A(0x4b);
        // IF_NC goto softboiled_vertical_wave;
        if(bc->xCoord < 0x4b) {
            // INC_hl;
            bc->xCoord++;
        }

    // softboiled_vertical_wave:
        // CALL(aBattleAnimFunction_Egg_EggVerticalWaveMotion);
        BattleAnimFunction_Egg_EggVerticalWaveMotion(bc);
        // RET;
        return;

    case 2:
    // two:
        // Compares the egg's x coord to determine whether to move, wait or end animation
        // LD_HL(BATTLEANIMSTRUCT_XCOORD);
        // ADD_HL_BC;
        // LD_A_hl;
        // CP_A(0x88);
        // IF_NC goto egg_bomb_done;
        if(bc->xCoord < 0x88) {
            // AND_A(0xf);
            // IF_NZ goto egg_bomb_step;
            if(bc->xCoord & 0xf)
                goto egg_bomb_step;
            // LD_HL(BATTLEANIMSTRUCT_VAR2);
            // ADD_HL_BC;
            // LD_hl(0x10);
            bc->var2 = 0x10;
            // CALL(aBattleAnim_IncAnonJumptableIndex);  // jumps to three
            bc->jumptableIndex++;  // jumps to three
            // RET;
            return;
        }
    // egg_bomb_done:
        // Increases jumptable index twice to four
        // CALL(aBattleAnim_IncAnonJumptableIndex);
        // INC_hl;
        bc->jumptableIndex += 2;
        // RET;
        return;

    case 3:
    // three:
        // Waits in place
        // LD_HL(BATTLEANIMSTRUCT_VAR2);
        // ADD_HL_BC;
        // LD_A_hl;
        // AND_A_A;
        // IF_Z goto done_waiting;
        if(bc->var2 != 0) {
            // DEC_hl;
            bc->var2--;
            // RET;
            return;
        }

    // done_waiting:
        // LD_HL(BATTLEANIMSTRUCT_JUMPTABLE_INDEX);
        // ADD_HL_BC;
        // DEC_hl;
        bc->jumptableIndex--;

    egg_bomb_step: {
        // Moves towards the target
        // LD_HL(BATTLEANIMSTRUCT_XCOORD);
        // ADD_HL_BC;
        // INC_hl;
        bc->xCoord++;
        // LD_HL(BATTLEANIMSTRUCT_YCOORD);
        // ADD_HL_BC;
        // LD_D_hl;
        // LD_HL(BATTLEANIMSTRUCT_VAR1);
        // ADD_HL_BC;
        // LD_E_hl;
        // LD_HL(-0x80);
        // ADD_HL_DE;
        uint16_t hl = ((bc->yCoord << 8) | bc->var1) - 0x80;
        // LD_E_L;
        // LD_D_H;
        // LD_HL(BATTLEANIMSTRUCT_YCOORD);
        // ADD_HL_BC;
        // LD_hl_D;
        bc->yCoord = HIGH(hl);
        // LD_HL(BATTLEANIMSTRUCT_VAR1);
        // ADD_HL_BC;
        // LD_hl_E;
        bc->var1 = LOW(hl);
        // RET;
    } return;

    case 5:
    // five:
        // Clears Egg Bomb object via anim_incobj
        // CALL(aDeinitBattleAnimation);
        DeinitBattleAnimation_Conv(bc);
        // RET;
        return;

    case 7:
    // seven:
        // Switches Softboiled frameset to egg wobbling
        // LD_A(BATTLEANIMFRAMESET_4E);  // Egg wobbling
        // CALL(aReinitBattleAnimFrameset);
        ReinitBattleAnimFrameset_Conv(bc, BATTLEANIMFRAMESET_4E);
        // CALL(aBattleAnim_IncAnonJumptableIndex);
        bc->jumptableIndex++;
        // RET;
        return;

    case 8: {
    // eight:
        // Softboiled object waves slightly side to side
        // LD_HL(BATTLEANIMSTRUCT_VAR1);
        // ADD_HL_BC;
        // LD_A_hl;
        uint8_t var1 = bc->var1;
        // INC_hl;
        // INC_hl;
        bc->var1 += 2;
        // LD_D(0x2);
        // CALL(aBattleAnim_Sine);
        // LD_HL(BATTLEANIMSTRUCT_XOFFSET);
        // ADD_HL_BC;
        // LD_hl_A;
        bc->xOffset = BattleAnim_Sine_Conv(var1, 0x2);
        // RET;
    } return;

    case 9:
    // nine:
        // First Softboiled ANIM_OBJ_EGG turns into the bottom half frameset
        // LD_A(BATTLEANIMFRAMESET_50);  // Cracked egg bottom
        // CALL(aReinitBattleAnimFrameset);
        ReinitBattleAnimFrameset_Conv(bc, BATTLEANIMFRAMESET_50);
        // LD_HL(BATTLEANIMSTRUCT_YOFFSET);
        // ADD_HL_BC;
        // LD_hl(0x4);
        bc->yOffset = 0x4;
        // CALL(aBattleAnim_IncAnonJumptableIndex);
        bc->jumptableIndex++;
        // RET;
        return;

    case 11:
    // eleven:
        // Second Softboiled ANIM_OBJ_EGG
        // LD_A(BATTLEANIMFRAMESET_4F);  // Cracked egg top
        // CALL(aReinitBattleAnimFrameset);
        ReinitBattleAnimFrameset_Conv(bc, BATTLEANIMFRAMESET_4F);
        // CALL(aBattleAnim_IncAnonJumptableIndex);
        bc->jumptableIndex++;
        // LD_HL(BATTLEANIMSTRUCT_VAR1);
        // ADD_HL_BC;
        // LD_hl(0x40);
        bc->var1 = 0x40;
        // RET;
        return;

    case 12:
    // twelve:
        // Top half of egg moves upward for $30 frames
        // LD_HL(BATTLEANIMSTRUCT_VAR1);
        // ADD_HL_BC;
        // LD_A_hl;
        // LD_D(0x20);
        // CALL(aBattleAnim_Sine);
        // LD_HL(BATTLEANIMSTRUCT_YOFFSET);
        // ADD_HL_BC;
        // LD_hl_A;
        bc->yOffset = BattleAnim_Sine_Conv(bc->var1, 0x20);
        // LD_HL(BATTLEANIMSTRUCT_VAR1);
        // ADD_HL_BC;
        // LD_A_hl;
        // CP_A(0x30);
        // IF_C goto done_top_shell;
        if(bc->var1 >= 0x30) {
            // DEC_hl;
            bc->var1--;
            // RET;
            return;
        }

    // done_top_shell:
        // CALL(aBattleAnim_IncAnonJumptableIndex);
        bc->jumptableIndex++;
        fallthrough;

    case 4:
    // four:
    case 10:
    // ten:
    case 13:
    // thirteen:
        // RET;
        return;
    }
}

//  Moves object up for 41 frames
//  Obj Param: Movement speed
void BattleAnimFunction_MoveUp(struct BattleAnim* bc) {
    // SET_PC(aBattleAnimFunction_MoveUp);
    // LD_HL(BATTLEANIMSTRUCT_YOFFSET);
    // ADD_HL_BC;
    // LD_A_hl;
    // AND_A_A;
    // IF_Z goto move;
    // CP_A(0xd8);
    // IF_NC goto move;
    if(bc->yOffset == 0 || bc->yOffset >= 0xd8) {
    // move:
        // LD_HL(BATTLEANIMSTRUCT_PARAM);
        // ADD_HL_BC;
        // LD_D_hl;
        // LD_HL(BATTLEANIMSTRUCT_YOFFSET);
        // ADD_HL_BC;
        // LD_A_hl;
        // SUB_A_D;
        // LD_hl_A;
        bc->yOffset -= bc->param;
        // RET;
        return;
    }
    // CALL(aDeinitBattleAnimation);
    DeinitBattleAnimation_Conv(bc);
    // RET;
}

static void BattleAnimFunction_Sound_SoundWaveMotion(struct BattleAnim* bc) {
    // LD_HL(BATTLEANIMSTRUCT_VAR2);
    // ADD_HL_BC;
    // LD_A_hl;
    uint8_t var2 = bc->var2;
    // INC_hl;
    // INC_hl;
    bc->var2 += 2;
    // LD_D(0x10);
    // CALL(aBattleAnim_Sine);
    // LD_D_A;
    // LD_HL(BATTLEANIMSTRUCT_XOFFSET);
    // ADD_HL_BC;
    // LD_hl_A;
    bc->xOffset = BattleAnim_Sine_Conv(var2, 0x10);
    // LD_HL(BATTLEANIMSTRUCT_PARAM);
    // ADD_HL_BC;
    // LD_A_hl;
    // AND_A_A;
    // IF_Z goto negative;
    if(bc->param == 0) {
    // negative:
        // Obj Param 0
        // LD_HL(BATTLEANIMSTRUCT_YOFFSET);
        // ADD_HL_BC;
        // LD_A_D;
        // XOR_A(0xff);
        // INC_A;
        // LD_hl_A;
        bc->yOffset = (bc->xOffset ^ 0xff) + 1;
        // RET;
        return;
    }
    // DEC_A;
    // RET_Z;
    if((bc->param - 1) == 0)
        return;
    // Obj Param 2
    // LD_HL(BATTLEANIMSTRUCT_YOFFSET);
    // ADD_HL_BC;
    // LD_hl_D;
    bc->yOffset = bc->xOffset;
    // RET;
}

//  Moves object back and forth in one of three angles using a sine behavior and disappear after 8 frames. Used in Growl, Snore and Kinesis
//  Obj Param: Used to define object angle. How much to increase from base frameset, which is hardcoded as BATTLEANIMFRAMESET_59
void BattleAnimFunction_Sound(struct BattleAnim* bc) {
    // SET_PC(aBattleAnimFunction_Sound);
    // CALL(aBattleAnim_AnonJumptable);

// anon_dw:

    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 0) goto zero;
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 1) goto one;

    switch(bc->jumptableIndex) {
    case 0:
    // zero:
        // LDH_A_addr(hBattleTurn);
        // AND_A_A;
        // IF_Z goto got_turn;
        if(hram->hBattleTurn != 0) {
            // enemy
            // LD_HL(BATTLEANIMSTRUCT_PARAM);
            // ADD_HL_BC;
            // LD_A_hl;
            // XOR_A(0xff);
            // ADD_A(0x3);
            // LD_hl_A;
            bc->param = (bc->param ^ 0xff) + 0x3;
        }

    // got_turn:
        // CALL(aBattleAnim_IncAnonJumptableIndex);
        bc->jumptableIndex++;
        // LD_HL(BATTLEANIMSTRUCT_VAR1);
        // ADD_HL_BC;
        // LD_hl(0x8);  // duration
        bc->var1 = 0x8;
        // LD_HL(BATTLEANIMSTRUCT_PARAM);
        // ADD_HL_BC;
        // LD_A(BATTLEANIMFRAMESET_59);
        // ADD_A_hl;  // BATTLEANIMFRAMESET_5A BATTLEANIMFRAMESET_5B
        // CALL(aReinitBattleAnimFrameset);
        ReinitBattleAnimFrameset_Conv(bc, BATTLEANIMFRAMESET_59 + bc->param);
        // RET;
        return;

    case 1:
    // one:
        // LD_HL(BATTLEANIMSTRUCT_VAR1);
        // ADD_HL_BC;
        // LD_A_hl;
        // AND_A_A;
        // IF_Z goto done_anim;
        if(bc->var1 != 0) {
            // DEC_hl;
            bc->var1--;
            // CALL(aBattleAnimFunction_Sound_SoundWaveMotion);
            BattleAnimFunction_Sound_SoundWaveMotion(bc);
            // RET;
            return;
        }

    // done_anim:
        // CALL(aDeinitBattleAnimation);
        DeinitBattleAnimation_Conv(bc);
        // RET;
        return;
    }
}

//  Creates the Confuse Ray object and moves it across the screen until x coord $80
//  Moves horizontally every frame and vertically every 3 frames
void BattleAnimFunction_ConfuseRay(struct BattleAnim* bc) {
    // SET_PC(aBattleAnimFunction_ConfuseRay);
    // CALL(aBattleAnim_AnonJumptable);

// anon_dw:

    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 0) goto zero;
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 1) goto one;

    switch(bc->jumptableIndex) {
    case 0:
    // zero:
        // CALL(aBattleAnim_IncAnonJumptableIndex);
        bc->jumptableIndex++;
        // LD_HL(BATTLEANIMSTRUCT_PARAM);
        // ADD_HL_BC;
        // LD_A_hl;
        // AND_A(0x3f);
        // LD_HL(BATTLEANIMSTRUCT_VAR2);
        // ADD_HL_BC;
        // LD_hl_A;
        bc->var2 = bc->param & 0x3f;
        // LD_HL(BATTLEANIMSTRUCT_PARAM);
        // ADD_HL_BC;
        // LD_A_hl;
        // AND_A(0x80);
        // RLCA;
        // LD_hl_A;
        bc->param = (bc->param >> 7);
        // ADD_A(BATTLEANIMFRAMESET_5D);  // BATTLEANIMFRAMESET_5E
        // CALL(aReinitBattleAnimFrameset);
        ReinitBattleAnimFrameset_Conv(bc, BATTLEANIMFRAMESET_5D);
        // RET;
        return;

    case 1: {
    // one:
        // LD_HL(BATTLEANIMSTRUCT_PARAM);
        // ADD_HL_BC;
        // LD_A_hl;
        // SWAP_A;
        // LD_D_A;
        // LD_HL(BATTLEANIMSTRUCT_VAR2);
        // ADD_HL_BC;
        // LD_A_hl;
        uint8_t var2 = bc->var2++;
        // INC_hl;
        // PUSH_AF;
        // PUSH_DE;
        // CALL(aBattleAnim_Sine);
        // LD_HL(BATTLEANIMSTRUCT_YOFFSET);
        // ADD_HL_BC;
        // LD_hl_A;
        bc->yOffset = BattleAnim_Sine_Conv((bc->param << 4) | (bc->param >> 4), var2);
        // POP_DE;
        // POP_AF;
        // CALL(aBattleAnim_Cosine);
        // LD_HL(BATTLEANIMSTRUCT_XOFFSET);
        // ADD_HL_BC;
        // LD_hl_A;
        bc->xOffset = BattleAnim_Cosine_Conv((bc->param << 4) | (bc->param >> 4), var2);
        // LD_HL(BATTLEANIMSTRUCT_XCOORD);
        // ADD_HL_BC;
        // LD_A_hl;
        // CP_A(0x80);
        // RET_NC;
        if(bc->xCoord >= 0x80)
            return;
        // LD_HL(BATTLEANIMSTRUCT_VAR2);
        // ADD_HL_BC;
        // LD_A_hl;
        // AND_A(0x3);
        // IF_NZ goto skip_vertical_movement;
        if((bc->var2 & 0x3) == 0) {
            // LD_HL(BATTLEANIMSTRUCT_YCOORD);
            // ADD_HL_BC;
            // DEC_hl;
            bc->yCoord--;
        }

    // skip_vertical_movement:
        // AND_A(0x1);
        // RET_NZ;
        if(bc->var2 & 0x1)
            return;
        // LD_HL(BATTLEANIMSTRUCT_XCOORD);
        // ADD_HL_BC;
        // INC_hl;
        bc->xCoord++;
        // RET;
    } return;
    }
}

//  Moves object in a circle where the height is 1/4 the width, with the next frameset from base whether moving left or right. Also used for Nightmare
//  Obj Param: Defines starting position in the circle (masked with $80). Bit 7 flips it at the start
void BattleAnimFunction_Dizzy(struct BattleAnim* bc) {
    // SET_PC(aBattleAnimFunction_Dizzy);
    // CALL(aBattleAnim_AnonJumptable);

// anon_dw:

    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 0) goto zero;
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 1) goto one;

    switch(bc->jumptableIndex) {
    case 0:
    // zero:
        // CALL(aBattleAnim_IncAnonJumptableIndex);
        bc->jumptableIndex++;
        // LD_HL(BATTLEANIMSTRUCT_FRAMESET_ID);
        // ADD_HL_BC;
        // LD_A_hl;
        // LD_HL(BATTLEANIMSTRUCT_VAR1);
        // ADD_HL_BC;
        // LD_hl_A;
        bc->var1 = bc->framesetId;
        // LD_HL(BATTLEANIMSTRUCT_PARAM);
        // ADD_HL_BC;
        // LD_A_hl;
        // AND_A(0x80);
        // RLCA;
        // LD_HL(BATTLEANIMSTRUCT_VAR1);
        // ADD_HL_BC;
        // ADD_A_hl;  // BATTLEANIMFRAMESET_61 BATTLEANIMFRAMESET_62
        // // ['?']  // BATTLEANIMFRAMESET_9C BATTLEANIMFRAMESET_9D
        // CALL(aReinitBattleAnimFrameset);
        ReinitBattleAnimFrameset_Conv(bc, ((bc->param & 0x80) >> 7) + bc->var1);
        // LD_HL(BATTLEANIMSTRUCT_PARAM);
        // ADD_HL_BC;
        // LD_A_hl;
        // AND_A(0x7f);
        // LD_hl_A;
        bc->param &= 0x7f;
        fallthrough;

    case 1: {
    // one:
        // LD_HL(BATTLEANIMSTRUCT_PARAM);
        // ADD_HL_BC;
        // LD_A_hl;
        // LD_D(0x10);
        // PUSH_AF;
        // PUSH_DE;
        // CALL(aBattleAnim_Sine);
        int8_t sine = (int8_t)BattleAnim_Sine_Conv(bc->param, 0x10);
        // SRA_A;
        // SRA_A;
        // LD_HL(BATTLEANIMSTRUCT_YOFFSET);
        // ADD_HL_BC;
        // LD_hl_A;
        bc->yOffset = sine >> 2;
        // POP_DE;
        // POP_AF;
        // CALL(aBattleAnim_Cosine);
        // LD_HL(BATTLEANIMSTRUCT_XOFFSET);
        // ADD_HL_BC;
        // LD_hl_A;
        bc->xOffset = BattleAnim_Cosine_Conv(bc->param, 0x10);
        // LD_HL(BATTLEANIMSTRUCT_PARAM);
        // ADD_HL_BC;
        // LD_A_hl;
        // INC_hl;
        uint8_t param = bc->param++;
        // AND_A(0x3f);
        // IF_Z goto not_flipped;
        if(param & 0x3f) {
            // AND_A(0x1f);
            // RET_NZ;
            if(param & 0x1f)
                return;
            // LD_HL(BATTLEANIMSTRUCT_VAR1);
            // ADD_HL_BC;
            // LD_A_hl;
            // INC_A;  // BATTLEANIMFRAMESET_62
            // ['?']  // BATTLEANIMFRAMESET_9D
            // goto got_frameset;
            ReinitBattleAnimFrameset_Conv(bc, bc->var1 + 1);
        }
        else {
        // not_flipped:
            // LD_HL(BATTLEANIMSTRUCT_VAR1);
            // ADD_HL_BC;
            // LD_A_hl;  // BATTLEANIMFRAMESET_61
            // ['?']  // BATTLEANIMFRAMESET_9C
            ReinitBattleAnimFrameset_Conv(bc, bc->var1);
        }
    // got_frameset:
        // CALL(aReinitBattleAnimFrameset);
        // RET;
    } return;
    }
}

//  Creates 3 objects based on Obj Param
//  Obj Param: How much to increase from base frameset, which is hardcoded as BATTLEANIMFRAMESET_63
//  anim_incobj is used to DeInit object (used by Present)
void BattleAnimFunction_Amnesia(struct BattleAnim* bc) {
    //
    //  Hardcoded Y Offsets for each Obj Param
    static const uint8_t AmnesiaOffsets[] = {
        0xec, 0xf8, 0x00
    };
    // SET_PC(aBattleAnimFunction_Amnesia);
    // CALL(aBattleAnim_AnonJumptable);

// anon_dw:

    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 0) goto zero;
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 1) goto one;
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 2) goto two;

    switch(bc->jumptableIndex) {
    case 0:
    // zero:
        // CALL(aBattleAnim_IncAnonJumptableIndex);
        bc->jumptableIndex++;
        // LD_HL(BATTLEANIMSTRUCT_PARAM);
        // ADD_HL_BC;
        // LD_A_hl;
        // ADD_A(BATTLEANIMFRAMESET_63);  // BATTLEANIMFRAMESET_64 BATTLEANIMFRAMESET_65
        // CALL(aReinitBattleAnimFrameset);
        ReinitBattleAnimFrameset_Conv(bc, BATTLEANIMFRAMESET_63);
        // LD_HL(BATTLEANIMSTRUCT_PARAM);
        // ADD_HL_BC;
        // LD_E_hl;
        // LD_D(0);
        // LD_HL(mBattleAnimFunction_Amnesia_AmnesiaOffsets);
        // ADD_HL_DE;
        // LD_A_hl;
        // LD_HL(BATTLEANIMSTRUCT_YOFFSET);
        // ADD_HL_BC;
        // LD_hl_A;
        bc->yOffset = AmnesiaOffsets[bc->param];
        fallthrough;

    case 1:
    // one:
        // RET;
        return;

    case 2:
    // two:
        // anim_incobj forces obj to deinit
        // CALL(aDeinitBattleAnimation);
        DeinitBattleAnimation_Conv(bc);
        // RET;
        return;
    }
}

//  Object moves horizontally in a sine wave, while also moving up. Also used by Charm and the Nightmare status
void BattleAnimFunction_FloatUp(struct BattleAnim* bc) {
    // SET_PC(aBattleAnimFunction_FloatUp);
    // LD_HL(BATTLEANIMSTRUCT_VAR1);
    // ADD_HL_BC;
    // LD_A_hl;
    uint8_t var1 = bc->var1;
    // INC_hl;
    // INC_hl;
    bc->var1 += 2;
    // LD_D(0x4);
    // CALL(aBattleAnim_Sine);
    // LD_HL(BATTLEANIMSTRUCT_XOFFSET);
    // ADD_HL_BC;
    // LD_hl_A;
    bc->xOffset = BattleAnim_Sine_Conv(var1, 0x4);
    // LD_HL(BATTLEANIMSTRUCT_YOFFSET);
    // ADD_HL_BC;
    // LD_D_hl;
    // LD_HL(BATTLEANIMSTRUCT_VAR2);
    // ADD_HL_BC;
    // LD_E_hl;
    // LD_HL((0xFF << 8) | 0xa0);
    // ADD_HL_DE;
    uint16_t hl = ((bc->yOffset << 8) | bc->var2) + 0xffa0;
    // LD_E_L;
    // LD_D_H;
    // LD_HL(BATTLEANIMSTRUCT_YOFFSET);
    // ADD_HL_BC;
    // LD_hl_D;
    bc->yOffset = HIGH(hl);
    // LD_HL(BATTLEANIMSTRUCT_VAR2);
    // ADD_HL_BC;
    // LD_hl_E;
    bc->var2 = LOW(hl);
    // RET;
}

//  Object moves up then down with a wave motion, while also moving away from the user 1 pixel per frame
void BattleAnimFunction_Dig(struct BattleAnim* bc) {
    // SET_PC(aBattleAnimFunction_Dig);
    // LD_HL(BATTLEANIMSTRUCT_VAR1);
    // ADD_HL_BC;
    // LD_A_hl;
    uint8_t var1 = bc->var1;
    // DEC_hl;
    // DEC_hl;
    bc->var1 -= 2;
    // LD_D(0x10);
    // CALL(aBattleAnim_Sine);
    // LD_HL(BATTLEANIMSTRUCT_YOFFSET);
    // ADD_HL_BC;
    // LD_hl_A;
    bc->yOffset = BattleAnim_Sine_Conv(var1, 0x10);
    // LD_HL(BATTLEANIMSTRUCT_XCOORD);
    // ADD_HL_BC;
    // INC_hl;
    bc->xCoord++;
    // RET;
}

void BattleAnimFunction_String(struct BattleAnim* bc) {
    // SET_PC(aBattleAnimFunction_String);
    // CALL(aBattleAnim_AnonJumptable);

// anon_dw:

    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 0) goto zero;
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 1) goto one;

    switch(bc->jumptableIndex) {
    case 0:
    // zero:
        // CALL(aBattleAnim_IncAnonJumptableIndex);
        bc->jumptableIndex++;
        // LD_HL(BATTLEANIMSTRUCT_PARAM);
        // ADD_HL_BC;
        // LD_A_hl;
        // AND_A_A;
        // IF_NZ goto not_param_zero;
        if(bc->param == 0) {
            // Obj Param 0 flips when used by enemy
            // LD_HL(BATTLEANIMSTRUCT_OAMFLAGS);
            // ADD_HL_BC;
            // SET_hl(OAM_Y_FLIP);
            bit_set(bc->oamFlags, OAM_Y_FLIP);
        }

    // not_param_zero:
        // ADD_A(BATTLEANIMFRAMESET_6A);  // BATTLEANIMFRAMESET_6B BATTLEANIMFRAMESET_6C
        // CALL(aReinitBattleAnimFrameset);
        ReinitBattleAnimFrameset_Conv(bc, BATTLEANIMFRAMESET_6A + bc->param);
        fallthrough;

    case 1:
    // one:
        // RET;
        return;
    }
}

//  Also used by Disable
//  Obj Param: When bit 7 is set, frameset is replaced with flipped version. This bit is discarded and object then moves back and forth between position in lower nybble and upper nybble of Param every other frame
void BattleAnimFunction_Paralyzed(struct BattleAnim* bc) {
    // SET_PC(aBattleAnimFunction_Paralyzed);
    // CALL(aBattleAnim_AnonJumptable);

// anon_dw:

    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 0) goto zero;
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 1) goto one;

    switch(bc->jumptableIndex) {
    case 0: {
    // zero:
        // CALL(aBattleAnim_IncAnonJumptableIndex);
        bc->jumptableIndex++;
        // LD_HL(BATTLEANIMSTRUCT_VAR1);
        // ADD_HL_BC;
        // LD_hl(0x0);
        bc->var1 = 0x0;
        // LD_HL(BATTLEANIMSTRUCT_PARAM);
        // ADD_HL_BC;
        // LD_E_hl;
        uint8_t param = bc->param;
        // LD_A_E;
        // AND_A(0x70);
        // SWAP_A;
        // LD_hl_A;
        bc->param = (param & 0x70) >> 4;
        // LD_HL(BATTLEANIMSTRUCT_XOFFSET);
        // ADD_HL_BC;
        // LD_A_E;
        // AND_A(0x80);
        // IF_NZ goto right;
        if(param & 0x80) {
        // right:
            // LD_A_E;
            // AND_A(0xf);
            // XOR_A(0xff);
            // INC_A;
            // LD_hl_A;
            bc->xOffset = -(param & 0xf);
            // LD_A(BATTLEANIMFRAMESET_6E);
            // CALL(aReinitBattleAnimFrameset);
            ReinitBattleAnimFrameset_Conv(bc, BATTLEANIMFRAMESET_6E);
            // RET;
            return;
        }
        else {
            // LD_A_E;
            // AND_A(0xf);
            // LD_hl_A;
            bc->xOffset = param & 0xf;
            // RET;
            return;
        }
    } break;

    case 1:
    // one:
        // LD_HL(BATTLEANIMSTRUCT_VAR1);
        // ADD_HL_BC;
        // LD_A_hl;
        // AND_A_A;
        // IF_Z goto var1_zero;
        if(bc->var1 != 0) {
            // DEC_hl;
            bc->var1--;
            // RET;
        }

    // var1_zero:
        // LD_HL(BATTLEANIMSTRUCT_PARAM);
        // ADD_HL_BC;
        // LD_A_hl;
        // LD_HL(BATTLEANIMSTRUCT_VAR1);
        // ADD_HL_BC;
        // LD_hl_A;
        bc->var1 = bc->param;
        // LD_HL(BATTLEANIMSTRUCT_XOFFSET);
        // ADD_HL_BC;
        // LD_A_hl;
        // XOR_A(0xff);
        // INC_A;
        // LD_hl_A;
        bc->xOffset = -bc->xOffset;
        // RET;
        return;
    }
}

void BattleAnimFunction_SpiralDescent(struct BattleAnim* bc) {
    // SET_PC(aBattleAnimFunction_SpiralDescent);
    // LD_HL(BATTLEANIMSTRUCT_VAR1);
    // ADD_HL_BC;
    // LD_A_hl;
    // LD_D(0x18);
    // PUSH_AF;
    // PUSH_DE;
    // CALL(aBattleAnim_Sine);
    int8_t sine = (int8_t)BattleAnim_Sine_Conv(bc->var1, 0x18);
    // SRA_A;
    // SRA_A;
    // SRA_A;
    // LD_HL(BATTLEANIMSTRUCT_VAR2);
    // ADD_HL_BC;
    // ADD_A_hl;
    // LD_HL(BATTLEANIMSTRUCT_YOFFSET);
    // ADD_HL_BC;
    // LD_hl_A;
    bc->yOffset = (sine >> 3) + bc->var2;
    // POP_DE;
    // POP_AF;
    // CALL(aBattleAnim_Cosine);
    // LD_HL(BATTLEANIMSTRUCT_XOFFSET);
    // ADD_HL_BC;
    // LD_hl_A;
    bc->xOffset = BattleAnim_Cosine_Conv(bc->var1, 0x18);
    // LD_HL(BATTLEANIMSTRUCT_VAR1);
    // ADD_HL_BC;
    // INC_hl;
    // LD_A_hl;
    // AND_A(0x7);
    // RET_NZ;
    if(++bc->var1 & 0x7)
        return;
    // LD_HL(BATTLEANIMSTRUCT_VAR2);
    // ADD_HL_BC;
    // LD_A_hl;
    // CP_A(0x28);
    // IF_NC goto delete;
    if(bc->var2 < 0x28) {
        // INC_hl;
        bc->var2++;
        // RET;
        return;
    }

// delete :
    // CALL(aDeinitBattleAnimation);
    DeinitBattleAnimation_Conv(bc);
    // RET;
}

//  Object moves downwards in a spiral around the user. Object disappears at y coord $28
void BattleAnimFunction_PetalDance(struct BattleAnim* bc) {
    // SET_PC(aBattleAnimFunction_PetalDance);
    // LD_HL(BATTLEANIMSTRUCT_VAR1);
    // ADD_HL_BC;
    // LD_A_hl;
    // LD_D(0x18);
    // PUSH_AF;
    // PUSH_DE;
    // CALL(aBattleAnim_Sine);
    int8_t sine = BattleAnim_Sine_Conv(bc->var1, 0x18);
    // SRA_A;
    // SRA_A;
    // SRA_A;
    // LD_HL(BATTLEANIMSTRUCT_VAR2);
    // ADD_HL_BC;
    // ADD_A_hl;
    // LD_HL(BATTLEANIMSTRUCT_YOFFSET);
    // ADD_HL_BC;
    // LD_hl_A;
    bc->yOffset = (sine >> 3) + bc->var2;
    // POP_DE;
    // POP_AF;
    // CALL(aBattleAnim_Cosine);
    // LD_HL(BATTLEANIMSTRUCT_XOFFSET);
    // ADD_HL_BC;
    // LD_hl_A;
    bc->xOffset = BattleAnim_Cosine_Conv(bc->var1, 0x18);
    // LD_HL(BATTLEANIMSTRUCT_VAR1);
    // ADD_HL_BC;
    // INC_hl;
    // LD_A_hl;
    // AND_A(0x3);
    // RET_NZ;
    if(++bc->var1 & 0x3)
        return;
    // LD_HL(BATTLEANIMSTRUCT_VAR2);
    // ADD_HL_BC;
    // LD_A_hl;
    // CP_A(0x28);
    // IF_NC goto end;
    if(bc->var2 < 0x28) {
        // INC_hl;
        bc->var2++;
        // RET;
        return;
    }

// end:
    // CALL(aDeinitBattleAnimation);
    DeinitBattleAnimation_Conv(bc);
    // RET;
}

void BattleAnimFunction_PoisonGas(struct BattleAnim* bc) {
    // SET_PC(aBattleAnimFunction_PoisonGas);
    // CALL(aBattleAnim_AnonJumptable);

// anon_dw:

    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 0) goto zero;
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 1) return BattleAnimFunction_SpiralDescent();

    switch(bc->jumptableIndex) {
    case 0:
    // zero:
        // LD_HL(BATTLEANIMSTRUCT_XCOORD);
        // ADD_HL_BC;
        // LD_A_hl;
        // CP_A(0x84);
        // IF_NC goto next;
        if(bc->xCoord >= 0x84) {
        // next:
            // CALL(aBattleAnim_IncAnonJumptableIndex);
            bc->jumptableIndex++;
            // RET;
            return;
        }
        // INC_hl;
        ++bc->xCoord;
        // LD_HL(BATTLEANIMSTRUCT_VAR1);
        // ADD_HL_BC;
        // LD_A_hl;
        // INC_hl;
        // LD_D(0x18);
        // CALL(aBattleAnim_Cosine);
        // LD_HL(BATTLEANIMSTRUCT_XOFFSET);
        // ADD_HL_BC;
        // LD_hl_A;
        bc->xOffset = BattleAnim_Cosine_Conv(bc->var1++, 0x18);
        // LD_HL(BATTLEANIMSTRUCT_XCOORD);
        // ADD_HL_BC;
        // LD_A_hl;
        // AND_A(0x1);
        // RET_NZ;
        if(bc->xCoord & 0x1)
            return;
        // LD_HL(BATTLEANIMSTRUCT_YCOORD);
        // ADD_HL_BC;
        // DEC_hl;
        bc->yCoord--;
        // RET;
        return;
    
    case 1:
        return BattleAnimFunction_SpiralDescent(bc);
    }
}

//  Object spins around target while also moving upward until it disappears at x coord $e8
//  Obj Param: Defines where the object starts in the circle
void BattleAnimFunction_SmokeFlameWheel(struct BattleAnim* bc) {
    // SET_PC(aBattleAnimFunction_SmokeFlameWheel);
    // LD_HL(BATTLEANIMSTRUCT_PARAM);
    // ADD_HL_BC;
    // LD_A_hl;
    // LD_D(0x18);
    // PUSH_AF;
    // PUSH_DE;
    // CALL(aBattleAnim_Sine);
    int8_t sine = (int8_t)BattleAnim_Sine_Conv(bc->param, 0x18);
    // SRA_A;
    // SRA_A;
    // SRA_A;
    // LD_HL(BATTLEANIMSTRUCT_VAR2);
    // ADD_HL_BC;
    // ADD_A_hl;
    // LD_HL(BATTLEANIMSTRUCT_YOFFSET);
    // ADD_HL_BC;
    // LD_hl_A;
    bc->yOffset = bc->var2 + (sine >> 3);
    // POP_DE;
    // POP_AF;
    // CALL(aBattleAnim_Cosine);
    // LD_HL(BATTLEANIMSTRUCT_XOFFSET);
    // ADD_HL_BC;
    // LD_hl_A;
    bc->xOffset = BattleAnim_Cosine_Conv(bc->param, 0x18);
    // LD_HL(BATTLEANIMSTRUCT_PARAM);
    // ADD_HL_BC;
    // INC_hl;
    // INC_hl;
    bc->param += 2;
    // LD_A_hl;
    // AND_A(0x7);
    // RET_NZ;
    if(bc->param & 0x7)
        return;
    // LD_HL(BATTLEANIMSTRUCT_VAR2);
    // ADD_HL_BC;
    // LD_A_hl;
    // CP_A(0xe8);
    // IF_Z goto done;
    if(bc->var2 != 0xe8) {
        // DEC_hl;
        bc->var2--;
        // RET;
        return;
    }

// done:
    // CALL(aDeinitBattleAnimation);
    DeinitBattleAnimation_Conv(bc);
    // RET;
}

//  Moves object in a circle where the height is 1/8 the width, while also moving upward 2 pixels per frame for 24 frames after which it disappears
//  Obj Param: Is used internally only
void BattleAnimFunction_SacredFire(struct BattleAnim* bc) {
    // SET_PC(aBattleAnimFunction_SacredFire);
    // LD_HL(BATTLEANIMSTRUCT_PARAM);
    // ADD_HL_BC;
    // LD_A_hl;
    // LD_D(0x18);
    // PUSH_AF;
    // PUSH_DE;
    // CALL(aBattleAnim_Sine);
    int8_t sine = (int8_t)BattleAnim_Sine_Conv(bc->param, 0x18);
    // SRA_A;
    // SRA_A;
    // SRA_A;
    // LD_HL(BATTLEANIMSTRUCT_VAR2);
    // ADD_HL_BC;
    // ADD_A_hl;
    // LD_HL(BATTLEANIMSTRUCT_YOFFSET);
    // ADD_HL_BC;
    // LD_hl_A;
    bc->yOffset = bc->var2 + (sine >> 3);
    // POP_DE;
    // POP_AF;
    // CALL(aBattleAnim_Cosine);
    // LD_HL(BATTLEANIMSTRUCT_XOFFSET);
    // ADD_HL_BC;
    // LD_hl_A;
    bc->xOffset = BattleAnim_Cosine_Conv(bc->param, 0x18);
    // LD_HL(BATTLEANIMSTRUCT_PARAM);
    // ADD_HL_BC;
    // INC_hl;
    // INC_hl;
    bc->param += 2;
    // LD_A_hl;
    // AND_A(0x3);
    // RET_NZ;
    if(bc->param & 0x3)
        return;
    // LD_HL(BATTLEANIMSTRUCT_VAR2);
    // ADD_HL_BC;
    // LD_A_hl;
    // CP_A(0xd0);
    // IF_Z goto done;
    if(bc->var2 != 0xd0) {
        // DEC_hl;
        // DEC_hl;
        bc->var2 -= 2;
        // RET;
        return;
    }
// done:
    // CALL(aDeinitBattleAnimation);
    DeinitBattleAnimation_Conv(bc);
    // RET;
}

//  Object bounces from user to target and stops at x coord $6c. Uses anim_incobj to clear object
//  Obj Param: Defined but not used
void BattleAnimFunction_PresentSmokescreen(struct BattleAnim* bc) {
    // SET_PC(aBattleAnimFunction_PresentSmokescreen);
    // CALL(aBattleAnim_AnonJumptable);

// anon_dw:

    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 0) goto zero;
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 1) goto one;
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 2) goto two;

    switch(bc->jumptableIndex) {
    case 0:
    // zero:
        // CALL(aBattleAnim_IncAnonJumptableIndex);
        bc->jumptableIndex++;
        // LD_HL(BATTLEANIMSTRUCT_VAR1);
        // ADD_HL_BC;
        // LD_hl(0x34);
        bc->var1 = 0x34;
        // LD_HL(BATTLEANIMSTRUCT_VAR2);
        // ADD_HL_BC;
        // LD_hl(0x10);
        bc->var2 = 0x10;
        fallthrough;

    case 1: {
    // one:
        // LD_HL(BATTLEANIMSTRUCT_XCOORD);
        // ADD_HL_BC;
        // LD_A_hl;
        // CP_A(0x6c);
        // IF_C goto do_move;
        // RET;
        if(bc->xCoord >= 0x6c)
            return;

    // do_move:
        // LD_A(0x2);
        // CALL(aBattleAnim_StepToTarget);
        BattleAnim_StepToTarget(bc, 0x2);
        // LD_HL(BATTLEANIMSTRUCT_VAR1);
        // ADD_HL_BC;
        // LD_A_hl;
        // LD_HL(BATTLEANIMSTRUCT_VAR2);
        // ADD_HL_BC;
        // LD_D_hl;
        // CALL(aBattleAnim_Sine);
        uint8_t sine = BattleAnim_Sine_Conv(bc->var1, bc->var2);
        // BIT_A(7);
        // IF_NZ goto negative;
        if(!bit_test(sine, 7)) {
            // XOR_A(0xff);
            // INC_A;
            sine = (sine ^ 0xff) + 1;
        }

    // negative:
        // LD_HL(BATTLEANIMSTRUCT_YOFFSET);
        // ADD_HL_BC;
        // LD_hl_A;
        bc->yOffset = sine;
        // LD_HL(BATTLEANIMSTRUCT_VAR1);
        // ADD_HL_BC;
        // LD_A_hl;
        // SUB_A(0x4);
        // LD_hl_A;
        bc->var1 -= 0x4;
        // AND_A(0x1f);
        // CP_A(0x20);
        // RET_NZ;
        // if((bc->var1 & 0x1f) != 0x20)
            // return;
        // LD_HL(BATTLEANIMSTRUCT_VAR2);
        // ADD_HL_BC;
        // SRL_hl;
        bc->var2 >>= 1;
        // RET;
    } return;

    case 2:
    // two:
        // CALL(aDeinitBattleAnimation);
        DeinitBattleAnimation_Conv(bc);
        // RET;
        return;
    }
}

void BattleAnimFunction_Horn(struct BattleAnim* bc) {
    // SET_PC(aBattleAnimFunction_Horn);
    // CALL(aBattleAnim_AnonJumptable);

// anon_dw:

    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 0) goto zero;
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 1) goto one;
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 2) goto two;
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 3) goto three;

    switch(bc->jumptableIndex) {
    case 0:
    // zero:
        // LD_HL(BATTLEANIMSTRUCT_PARAM);
        // ADD_HL_BC;
        // LD_A_hl;
        // LD_HL(BATTLEANIMSTRUCT_JUMPTABLE_INDEX);
        // ADD_HL_BC;
        // LD_hl_A;
        bc->jumptableIndex = bc->param;
        // LD_HL(BATTLEANIMSTRUCT_YCOORD);
        // ADD_HL_BC;
        // LD_A_hl;
        // LD_HL(BATTLEANIMSTRUCT_VAR1);
        // ADD_HL_BC;
        // LD_hl_A;
        bc->var1 = bc->yCoord;
        // RET;
        return;

    case 1:
    // one:
        // LD_HL(BATTLEANIMSTRUCT_XCOORD);
        // ADD_HL_BC;
        // LD_A_hl;
        // CP_A(0x58);
        // RET_NC;
        if(bc->xCoord >= 0x58)
            return;
        // LD_A(0x2);
        // CALL(aBattleAnim_StepToTarget);
        BattleAnim_StepToTarget(bc, 0x2);
        // RET;
        return;

    case 2:
    // two:
        // LD_HL(BATTLEANIMSTRUCT_VAR2);
        // ADD_HL_BC;
        // LD_A_hl;
        // CP_A(0x20);
        // IF_C goto three;
        if(bc->var2 >= 0x20) {
            // CALL(aDeinitBattleAnimation);
            DeinitBattleAnimation_Conv(bc);
            // RET;
            return;
        }
        fallthrough;

    case 3:
    // three:
        // LD_HL(BATTLEANIMSTRUCT_VAR2);
        // ADD_HL_BC;
        // LD_A_hl;
        // LD_D(0x8);
        // CALL(aBattleAnim_Sine);
        // LD_HL(BATTLEANIMSTRUCT_XOFFSET);
        // ADD_HL_BC;
        // LD_hl_A;
        bc->xOffset = BattleAnim_Sine_Conv(bc->var2, 0x8);
        // SRA_A;
        // XOR_A(0xff);
        // INC_A;
        // LD_HL(BATTLEANIMSTRUCT_VAR1);
        // ADD_HL_BC;
        // ADD_A_hl;
        // LD_HL(BATTLEANIMSTRUCT_YCOORD);
        // ADD_HL_BC;
        // LD_hl_A;
        bc->yCoord = bc->var1 - bc->xOffset;
        // LD_HL(BATTLEANIMSTRUCT_VAR2);
        // ADD_HL_BC;
        // LD_A_hl;
        // ADD_A(0x8);
        // LD_hl_A;
        bc->var2 += 0x8;
        // RET;
        return;
    }
}

//  Moves object towards target, either in a straight line or arc. Stops at x coord $84
//  Obj Param: Upper nybble defines the index of the jumptable. Lower nybble defines the speed.
void BattleAnimFunction_Needle(struct BattleAnim* bc) {
    // SET_PC(aBattleAnimFunction_Needle);
    // CALL(aBattleAnim_AnonJumptable);

// anon_dw:

    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 0) goto zero;
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 1) goto one;
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 2) goto two;

    switch(bc->jumptableIndex) {
    case 0:
    // zero:
        // LD_HL(BATTLEANIMSTRUCT_PARAM);
        // ADD_HL_BC;
        // LD_A_hl;
        // AND_A(0xf0);
        // SWAP_A;
        // LD_HL(BATTLEANIMSTRUCT_JUMPTABLE_INDEX);
        // ADD_HL_BC;
        // LD_hl_A;
        bc->jumptableIndex = (bc->param & 0xf0) >> 4;
        // RET;
        return;

    case 2: {
    // two:
        // Pin Missile needle (arc)
        // LD_HL(BATTLEANIMSTRUCT_VAR1);
        // ADD_HL_BC;
        // LD_A_hl;
        // LD_D(0x10);
        // CALL(aBattleAnim_Sine);
        uint8_t sine = BattleAnim_Sine_Conv(bc->var1, 0x10);
        // LD_HL(BATTLEANIMSTRUCT_YOFFSET);
        // ADD_HL_BC;
        // BIT_A(7);
        // IF_Z goto negative;
        // LD_hl_A;
        if(!bit_test(sine, 7))
            bc->yOffset = sine;

    // negative:
        // LD_HL(BATTLEANIMSTRUCT_VAR1);
        // ADD_HL_BC;
        // LD_A_hl;
        // SUB_A(0x4);
        // LD_hl_A;
        bc->var1 -= 0x4;
    } fallthrough;

    case 1:
    // one:
        // Normal needle (line)
        // LD_HL(BATTLEANIMSTRUCT_XCOORD);
        // ADD_HL_BC;
        // LD_A_hl;
        // CP_A(0x84);
        // IF_C goto move_to_target;
        if(bc->xCoord >= 0x84) {
            // CALL(aDeinitBattleAnimation);
            DeinitBattleAnimation_Conv(bc);
            // RET;
            return;
        }

    // move_to_target:
        // LD_HL(BATTLEANIMSTRUCT_PARAM);
        // ADD_HL_BC;
        // LD_A_hl;
        // CALL(aBattleAnim_StepToTarget);
        BattleAnim_StepToTarget(bc, bc->param);
        // RET;
        return;
    }
}

//  Object drops off target and bounces once on the floor
//  Obj Param: Defines every how many frames the object moves horizontally
void BattleAnimFunction_ThiefPayday(struct BattleAnim* bc) {
    // SET_PC(aBattleAnimFunction_ThiefPayday);
    // CALL(aBattleAnim_AnonJumptable);

// anon_dw:

    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 0) goto zero;
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 1) goto one;

    switch(bc->jumptableIndex) {
    case 0:
    // zero:
        // CALL(aBattleAnim_IncAnonJumptableIndex);
        bc->jumptableIndex++;
        // LD_HL(BATTLEANIMSTRUCT_VAR1);
        // ADD_HL_BC;
        // LD_hl(0x28);
        bc->var1 = 0x28;
        // LD_HL(BATTLEANIMSTRUCT_YCOORD);
        // ADD_HL_BC;
        // LD_A_hl;
        // SUB_A(0x28);
        // LD_HL(BATTLEANIMSTRUCT_VAR2);
        // ADD_HL_BC;
        // LD_hl_A;
        bc->var2 = bc->yCoord - 0x28;
        fallthrough;

    case 1:
    // one:
        // LD_HL(BATTLEANIMSTRUCT_VAR1);
        // ADD_HL_BC;
        // LD_A_hli;
        // LD_D_hl;
        // CALL(aBattleAnim_Sine);
        // LD_HL(BATTLEANIMSTRUCT_YOFFSET);
        // ADD_HL_BC;
        // LD_hl_A;
        bc->yOffset = BattleAnim_Sine_Conv(bc->var1, bc->var2);
        // LD_HL(BATTLEANIMSTRUCT_VAR1);
        // ADD_HL_BC;
        // LD_A_hl;
        // LD_HL(BATTLEANIMSTRUCT_PARAM);
        // ADD_HL_BC;
        // AND_A_hl;
        // IF_NZ goto var_doesnt_equal_param;
        if(bc->param == bc->var1) {
            // LD_HL(BATTLEANIMSTRUCT_XCOORD);
            // ADD_HL_BC;
            // DEC_hl;
            bc->xCoord--;
        }

    // var_doesnt_equal_param:
        // LD_HL(BATTLEANIMSTRUCT_VAR1);
        // ADD_HL_BC;
        // INC_hl;
        // LD_A_hl;
        // AND_A(0x3f);
        // RET_NZ;
        if(++bc->var1 & 0x3f)
            return;
        // LD_HL(BATTLEANIMSTRUCT_VAR1);
        // ADD_HL_BC;
        // LD_hl(0x20);
        bc->var1 = 0x20;
        // INC_HL;
        // SRL_hl;
        bc->var2 >>= 1;
        // RET;
        return;
    }
}

//  A circle of objects that starts at the target and moves to the user. It expands until x coord $5a and then shrinks. Once radius reaches 0, the object disappears. Also used by Mimic and Conversion2
//  Obj Param: Defines the position in the circle the object starts at
void BattleAnimFunction_AbsorbCircle(struct BattleAnim* bc) {
    // SET_PC(aBattleAnimFunction_AbsorbCircle);
    // LD_HL(BATTLEANIMSTRUCT_PARAM);
    // ADD_HL_BC;
    // LD_A_hl;
    // LD_HL(BATTLEANIMSTRUCT_VAR1);
    // ADD_HL_BC;
    // LD_D_hl;
    // PUSH_AF;
    // PUSH_DE;
    // CALL(aBattleAnim_Sine);
    // LD_HL(BATTLEANIMSTRUCT_YOFFSET);
    // ADD_HL_BC;
    // LD_hl_A;
    bc->yOffset = BattleAnim_Sine_Conv(bc->param, bc->var1);
    // POP_DE;
    // POP_AF;
    // CALL(aBattleAnim_Cosine);
    // LD_HL(BATTLEANIMSTRUCT_XOFFSET);
    // ADD_HL_BC;
    // LD_hl_A;
    bc->xOffset = BattleAnim_Sine_Conv(bc->param, bc->var1);
    // LD_HL(BATTLEANIMSTRUCT_PARAM);
    // ADD_HL_BC;
    // INC_hl;
    // LD_A_hl;
    // AND_A(0x1);
    // IF_NZ goto dont_move_x;
    if((++bc->param & 0x1) == 0) {
        // LD_HL(BATTLEANIMSTRUCT_XCOORD);
        // ADD_HL_BC;
        // DEC_hl;
        bc->xCoord--;
    }

// dont_move_x:
    // LD_HL(BATTLEANIMSTRUCT_PARAM);
    // ADD_HL_BC;
    // LD_A_hl;
    // AND_A(0x3);
    // IF_NZ goto dont_move_y;
    if((bc->param & 0x3) == 0) {
        // LD_HL(BATTLEANIMSTRUCT_YCOORD);
        // ADD_HL_BC;
        // INC_hl;
        bc->yCoord++;
    }

// dont_move_y:
    // LD_HL(BATTLEANIMSTRUCT_XCOORD);
    // ADD_HL_BC;
    // LD_A_hl;
    // LD_HL(BATTLEANIMSTRUCT_VAR1);
    // ADD_HL_BC;
    // CP_A(0x5a);
    // IF_NC goto increase_radius;
    if(bc->xCoord == 0x5a) {
    // increase_radius:
        // INC_hl;
        bc->var1++;
        // RET;
        return;
    }
    // LD_A_hl;
    // AND_A_A;
    // IF_Z goto end;
    else if(bc->var1 != 0) {
        // DEC_hl;  // decreases radius
        bc->var1--;
        // RET;
        return;
    }

// end:
    // CALL(aDeinitBattleAnimation);
    DeinitBattleAnimation_Conv(bc);
    // RET;
}

//  A rotating circle of objects centered at a position. It expands for $40 frames and then shrinks. Once radius reaches 0, the object disappears.
//  Obj Param: Defines starting point in the circle
void BattleAnimFunction_Conversion(struct BattleAnim* bc) {
    // SET_PC(aBattleAnimFunction_Conversion);
    // LD_HL(BATTLEANIMSTRUCT_PARAM);
    // ADD_HL_BC;
    // LD_A_hl;
    // INC_hl;
    uint8_t param = bc->param++;
    // LD_HL(BATTLEANIMSTRUCT_VAR1);
    // ADD_HL_BC;
    // LD_D_hl;
    // PUSH_AF;
    // PUSH_DE;
    // CALL(aBattleAnim_Sine);
    // LD_HL(BATTLEANIMSTRUCT_YOFFSET);
    // ADD_HL_BC;
    // LD_hl_A;
    bc->yOffset = BattleAnim_Sine_Conv(param, bc->var1);
    // POP_DE;
    // POP_AF;
    // CALL(aBattleAnim_Cosine);
    // LD_HL(BATTLEANIMSTRUCT_XOFFSET);
    // ADD_HL_BC;
    // LD_hl_A;
    bc->xOffset = BattleAnim_Cosine_Conv(param, bc->var1);
    // LD_HL(BATTLEANIMSTRUCT_VAR2);
    // ADD_HL_BC;
    // LD_A_hl;
    // INC_hl;
    // LD_HL(BATTLEANIMSTRUCT_VAR1);
    // ADD_HL_BC;
    // CP_A(0x40);
    // IF_NC goto shrink;
    if(bc->var2++ < 0x40) {
        // INC_hl;
        bc->var1++;
        // RET;
        return;
    }

// shrink:
    // LD_A_hl;
    // DEC_hl;
    // AND_A_A;
    // RET_NZ;
    if(bc->var1-- != 0)
        return;
    // CALL(aDeinitBattleAnimation);
    DeinitBattleAnimation_Conv(bc);
    // RET;
}

//  Boomerang-like movement from user to target
//  Obj Param: Defines position to start at in the circle
void BattleAnimFunction_Bonemerang(struct BattleAnim* bc) {
    // SET_PC(aBattleAnimFunction_Bonemerang);
    // CALL(aBattleAnim_AnonJumptable);

// anon_dw:

    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 0) goto zero;
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 1) goto one;

    switch(bc->jumptableIndex) {
    case 0:
    // zero:
        // CALL(aBattleAnim_IncAnonJumptableIndex);
        bc->jumptableIndex++;
        // LD_HL(BATTLEANIMSTRUCT_YCOORD);
        // ADD_HL_BC;
        // LD_A_hl;
        // LD_HL(BATTLEANIMSTRUCT_VAR2);
        // ADD_HL_BC;
        // LD_hl_A;
        bc->var2 = bc->yCoord;
        fallthrough;

    case 1:
    // one:
        // LD_HL(BATTLEANIMSTRUCT_PARAM);
        // ADD_HL_BC;
        // LD_A_hl;
        // LD_D(0x30);
        // CALL(aBattleAnim_Sine);
        // LD_HL(BATTLEANIMSTRUCT_VAR2);
        // ADD_HL_BC;
        // ADD_A_hl;
        // LD_HL(BATTLEANIMSTRUCT_YCOORD);
        // ADD_HL_BC;
        // LD_hl_A;
        bc->yCoord = bc->var2 + BattleAnim_Sine_Conv(bc->param, 0x30);
        // LD_HL(BATTLEANIMSTRUCT_PARAM);
        // ADD_HL_BC;
        // LD_A_hl;
        // ADD_A(0x8);
        // LD_D(0x30);
        // CALL(aBattleAnim_Cosine);
        // LD_HL(BATTLEANIMSTRUCT_XOFFSET);
        // ADD_HL_BC;
        // LD_hl_A;
        bc->xOffset = BattleAnim_Cosine_Conv(bc->param + 0x8, 0x30);
        // LD_HL(BATTLEANIMSTRUCT_PARAM);
        // ADD_HL_BC;
        // INC_hl;
        bc->param++;
        // RET;
        return;
    }
}

//  Puts object in a circle formation of radius $10. Also used by Flash and Light Screen
//  Obj Param: Defines where the object starts in the circle
void BattleAnimFunction_Shiny(struct BattleAnim* bc) {
    // SET_PC(aBattleAnimFunction_Shiny);
    // CALL(aBattleAnim_AnonJumptable);

// anon_dw:

    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 0) goto zero;
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 1) goto one;

    switch(bc->jumptableIndex) {
    case 0:
    // zero:
        // CALL(aBattleAnim_IncAnonJumptableIndex);
        bc->jumptableIndex++;
        // LD_HL(BATTLEANIMSTRUCT_PARAM);
        // ADD_HL_BC;
        // LD_A_hl;
        // LD_D(0x10);
        // CALL(aBattleAnim_Sine);
        // LD_HL(BATTLEANIMSTRUCT_YOFFSET);
        // ADD_HL_BC;
        // LD_hl_A;
        bc->yOffset = BattleAnim_Sine_Conv(bc->param, 0x10);
        // LD_HL(BATTLEANIMSTRUCT_PARAM);
        // ADD_HL_BC;
        // LD_A_hl;
        // LD_D(0x10);
        // CALL(aBattleAnim_Cosine);
        // LD_HL(BATTLEANIMSTRUCT_XOFFSET);
        // ADD_HL_BC;
        // LD_hl_A;
        bc->xOffset = BattleAnim_Cosine_Conv(bc->param, 0x10);
        // LD_HL(BATTLEANIMSTRUCT_VAR2);  // unused?
        // ADD_HL_BC;
        // LD_hl(0xf);
        bc->var2 &= 0xf; // unused?
        fallthrough;

    case 1:
    // one:
        // RET;
        return;
    }
}

//  Cycles wOBP0 pallete
static void BattleAnimFunction_SkyAttack_SkyAttack_CyclePalette(struct BattleAnim* bc) {
    static const uint8_t GBCPals[] = {0xff, 0xaa, 0x55, 0xaa};
    static const uint8_t SGBPals[] = {0xff, 0xff, 0x00, 0x00};
    // LD_HL(BATTLEANIMSTRUCT_VAR2);
    // ADD_HL_BC;
    // LD_A_hl;
    // AND_A(0x7);
    // INC_hl;
    // SRL_A;
    // LD_E_A;
    // LD_D(0);
    uint16_t de = (bc->var2++ & 0x7) >> 1;
    // LDH_A_addr(hSGB);
    // AND_A_A;
    // IF_NZ goto sgb;
    // LD_HL(mBattleAnimFunction_SkyAttack_GBCPals);
    // goto got_pals;

// sgb:
    // LD_HL(mBattleAnimFunction_SkyAttack_SGBPals);
    const uint8_t* hl = (hram->hSGB == 0)? GBCPals: SGBPals;

// got_pals:
    // ADD_HL_DE;
    // LD_A_hl;
    // LD_HL(BATTLEANIMSTRUCT_VAR1);
    // ADD_HL_BC;
    // AND_A_hl;
    // LD_addr_A(wOBP0);
    wram->wOBP0 = bc->var1 & hl[de];
    // RET;
}

//  Uses anim_incobj to move to next step
void BattleAnimFunction_SkyAttack(struct BattleAnim* bc) {
    // SET_PC(aBattleAnimFunction_SkyAttack);
    // CALL(aBattleAnim_AnonJumptable);

// anon_dw:

    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 0) goto zero;
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 1) goto one;
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 2) goto two;
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 3) goto three;

    switch(bc->jumptableIndex) {
    case 0:
    // zero:
        // CALL(aBattleAnim_IncAnonJumptableIndex);
        bc->jumptableIndex++;
        // LDH_A_addr(hBattleTurn);
        // AND_A_A;
        // IF_NZ goto enemy_turn;
        // LD_A(0xf0);
        // goto got_var1;

    // enemy_turn:
        // LD_A(0xcc);

    // got_var1:
        // LD_HL(BATTLEANIMSTRUCT_VAR1);
        // ADD_HL_BC;
        // LD_hl_A;
        bc->var1 = (hram->hBattleTurn)? 0xcc: 0xf0;
        // RET;
        return;

    case 1:
    // one:
        // CALL(aBattleAnimFunction_SkyAttack_SkyAttack_CyclePalette);
        BattleAnimFunction_SkyAttack_SkyAttack_CyclePalette(bc);
        // RET;
        return;

    case 2:
    // two:
        //  Moves towards target and stops at x coord $84
        // CALL(aBattleAnimFunction_SkyAttack_SkyAttack_CyclePalette);
        BattleAnimFunction_SkyAttack_SkyAttack_CyclePalette(bc);
        // LD_HL(BATTLEANIMSTRUCT_XCOORD);
        // ADD_HL_BC;
        // LD_A_hl;
        // CP_A(0x84);
        // RET_NC;
        if(bc->xCoord >= 0x84)
            return;
        // LD_A(0x4);
        // CALL(aBattleAnim_StepToTarget);
        BattleAnim_StepToTarget(bc, 0x4);
        // RET;
        return;

    case 3:
    // three:
        //  Moves towards target and disappears at x coord $d0
        // CALL(aBattleAnimFunction_SkyAttack_SkyAttack_CyclePalette);
        BattleAnimFunction_SkyAttack_SkyAttack_CyclePalette(bc);
        // LD_HL(BATTLEANIMSTRUCT_XCOORD);
        // ADD_HL_BC;
        // LD_A_hl;
        // CP_A(0xd0);
        // IF_NC goto done;
        if(bc->xCoord < 0xd0) {
            // LD_A(0x4);
            // CALL(aBattleAnim_StepToTarget);
            BattleAnim_StepToTarget(bc, 0x4);
            // RET;
            return;
        }

    // done:
        // CALL(aDeinitBattleAnimation);
        DeinitBattleAnimation_Conv(bc);
        // RET;
        return;
    }
}

//  Moves object in a circle where the height is 1/8 the width, while also moving upward 2 pixels per frame
//  Obj Param: Defines where the object starts in the circle
void BattleAnimFunction_GrowthSwordsDance(struct BattleAnim* bc) {
    // SET_PC(aBattleAnimFunction_GrowthSwordsDance);
    // LD_HL(BATTLEANIMSTRUCT_PARAM);
    // ADD_HL_BC;
    // LD_A_hl;
    // LD_D(0x18);
    // CALL(aBattleAnim_Sine);
    int8_t sine = (int8_t)BattleAnim_Sine_Conv(bc->param, 0x18);
    // SRA_A;
    // SRA_A;
    // SRA_A;
    // LD_HL(BATTLEANIMSTRUCT_VAR2);
    // ADD_HL_BC;
    // ADD_A_hl;
    // LD_HL(BATTLEANIMSTRUCT_YOFFSET);
    // ADD_HL_BC;
    // LD_hl_A;
    bc->yOffset = (sine >> 3) + bc->var2;
    // LD_HL(BATTLEANIMSTRUCT_PARAM);
    // ADD_HL_BC;
    // LD_A_hl;
    // INC_hl;
    // LD_D(0x18);
    // CALL(aBattleAnim_Cosine);
    // LD_HL(BATTLEANIMSTRUCT_XOFFSET);
    // ADD_HL_BC;
    // LD_hl_A;
    bc->xOffset = BattleAnim_Cosine_Conv(bc->param++, 0x18);
    // LD_HL(BATTLEANIMSTRUCT_VAR2);
    // ADD_HL_BC;
    // DEC_hl;
    // DEC_hl;
    bc->var2 -= 2;
    // RET;
}

//  Moves object up for $e0 frames, then shakes it vertically and throws it at the target. Uses anim_incobj to move to final phase
//  Obj Param: Defined but not used
void BattleAnimFunction_StrengthSeismicToss(struct BattleAnim* bc) {
    // SET_PC(aBattleAnimFunction_StrengthSeismicToss);
    // CALL(aBattleAnim_AnonJumptable);

// anon_dw:

    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 0) goto zero;
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 1) goto one;
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 2) goto two;

    switch(bc->jumptableIndex) {
    case 0: {
    // zero:
        // LD_HL(BATTLEANIMSTRUCT_YOFFSET);
        // ADD_HL_BC;
        // LD_A_hl;
        // CP_A(0xe0);
        // IF_NZ goto move_up;
        if(bc->yOffset == 0xe0) {
            // CALL(aBattleAnim_IncAnonJumptableIndex);
            bc->jumptableIndex++;
            // LD_HL(BATTLEANIMSTRUCT_VAR1);
            // ADD_HL_BC;
            // LD_hl(0x2);
            bc->var1 = 0x2;
            // RET;
            return;
        }

    // move_up:
        // LD_D_A;
        // LD_HL(BATTLEANIMSTRUCT_VAR1);
        // ADD_HL_BC;
        // LD_E_hl;
        // LD_HL(-0x80);
        // ADD_HL_DE;
        uint16_t hl = ((bc->yOffset << 8) | bc->var1) - 0x80;
        // LD_E_L;
        // LD_D_H;
        // LD_HL(BATTLEANIMSTRUCT_YOFFSET);
        // ADD_HL_BC;
        // LD_hl_D;
        bc->yOffset = HIGH(hl);
        // LD_HL(BATTLEANIMSTRUCT_VAR1);
        // ADD_HL_BC;
        // LD_hl_E;
        bc->xOffset = LOW(hl);
        // RET;
    } return;

    case 1:
    // one:
        // LD_HL(BATTLEANIMSTRUCT_VAR2);
        // ADD_HL_BC;
        // LD_A_hl;
        // AND_A_A;
        // IF_Z goto switch_position;
        if(bc->var2 != 0) {
            // DEC_hl;
            bc->var2--;
            // RET;
            return;
        }

    // switch_position:
        // LD_hl(0x4);
        bc->var2 = 0x4;
        // LD_HL(BATTLEANIMSTRUCT_VAR1);
        // ADD_HL_BC;
        // LD_A_hl;
        // XOR_A(0xff);
        // INC_A;
        // LD_hl_A;
        bc->var1 = -bc->var1;
        // LD_HL(BATTLEANIMSTRUCT_YOFFSET);
        // ADD_HL_BC;
        // ADD_A_hl;
        // LD_hl_A;
        bc->yOffset += bc->var1;
        // RET;
        return;

    case 2:
    // two:
        // LD_HL(BATTLEANIMSTRUCT_XCOORD);
        // ADD_HL_BC;
        // LD_A_hl;
        // CP_A(0x84);
        // IF_NC goto done;
        if(bc->xCoord < 0x84) {
            // LD_A(0x4);
            // CALL(aBattleAnim_StepToTarget);
            BattleAnim_StepToTarget(bc, 0x4);
            // RET;
            return;
        }

    // done:
        // CALL(aDeinitBattleAnimation);
        DeinitBattleAnimation_Conv(bc);
        // RET;
        return;
    }
}

//  Used in moves where the user disappears for a speed-based attack such as Quick Attack, Mach Punch and Extremespeed
void BattleAnimFunction_SpeedLine(struct BattleAnim* bc) {
    // SET_PC(aBattleAnimFunction_SpeedLine);
    // CALL(aBattleAnim_AnonJumptable);

// anon_dw:

    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 0) goto zero;
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 1) goto one;

    switch(bc->jumptableIndex) {
    case 0:
    // zero:
        // CALL(aBattleAnim_IncAnonJumptableIndex);
        bc->jumptableIndex++;
        // LD_HL(BATTLEANIMSTRUCT_PARAM);
        // ADD_HL_BC;
        // LD_A_hl;
        // AND_A(0x7f);
        // ADD_A(BATTLEANIMFRAMESET_81);  // BATTLEANIMFRAMESET_82 BATTLEANIMFRAMESET_83
        // CALL(aReinitBattleAnimFrameset);
        ReinitBattleAnimFrameset_Conv(bc, BATTLEANIMFRAMESET_81 + (bc->param & 0x7f));
        fallthrough;

    case 1:
    // one:
        // LD_HL(BATTLEANIMSTRUCT_PARAM);
        // ADD_HL_BC;
        // BIT_hl(7);
        // IF_NZ goto inverted;
        if(bit_test(bc->param, 7)) {
        // inverted:
            // LD_HL(BATTLEANIMSTRUCT_XOFFSET);
            // ADD_HL_BC;
            // DEC_hl;
            bc->xOffset--;
            // RET;
            return;
        }
        // LD_HL(BATTLEANIMSTRUCT_XOFFSET);
        // ADD_HL_BC;
        // INC_hl;
        bc->xOffset++;
        // RET;
        return;
    }
}

//  Object moves upward for $c frames and switches to FRAMESET_20
void BattleAnimFunction_Sludge(struct BattleAnim* bc) {
    // SET_PC(aBattleAnimFunction_Sludge);
    // CALL(aBattleAnim_AnonJumptable);

// anon_dw:

    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 0) goto zero;
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 1) goto one;
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 2) goto two;

    switch(bc->jumptableIndex) {
    case 0:
    // zero:
        // CALL(aBattleAnim_IncAnonJumptableIndex);
        bc->jumptableIndex++;
        // LD_HL(BATTLEANIMSTRUCT_VAR1);
        // ADD_HL_BC;
        // LD_hl(0xc);
        bc->var1 = 0xc;
        // RET;
        return;

    case 1:
    // one:
        // LD_HL(BATTLEANIMSTRUCT_VAR1);
        // ADD_HL_BC;
        // LD_A_hl;
        // AND_A_A;
        // IF_Z goto done;
        if(bc->var1 != 0) {
            // DEC_hl;
            bc->var1--;
            // RET;
            return;
        }

    // done:
        // CALL(aBattleAnim_IncAnonJumptableIndex);
        bc->jumptableIndex++;
        // LD_A(BATTLEANIMFRAMESET_20);
        // CALL(aReinitBattleAnimFrameset);
        ReinitBattleAnimFrameset_Conv(bc, BATTLEANIMFRAMESET_20);
        fallthrough;

    case 2:
    // two:
        // LD_HL(BATTLEANIMSTRUCT_YOFFSET);
        // ADD_HL_BC;
        // DEC_hl;
        bc->yOffset--;
        // RET;
        return;
    }
}

//  Fast circular motion with an x radius of $8 and y radius of $2
void BattleAnimFunction_MetronomeHand(struct BattleAnim* bc) {
    // SET_PC(aBattleAnimFunction_MetronomeHand);
    // LD_HL(BATTLEANIMSTRUCT_VAR1);
    // ADD_HL_BC;
    // LD_A_hl;
    uint8_t var1 = bc->var1;
    // INC_hl;
    // INC_hl;
    bc->var1 += 2;
    // PUSH_AF;
    // LD_D(0x2);
    // CALL(aBattleAnim_Sine);
    // LD_HL(BATTLEANIMSTRUCT_YOFFSET);
    // ADD_HL_BC;
    // LD_hl_A;
    bc->yOffset = BattleAnim_Sine_Conv(var1, 0x2);
    // POP_AF;
    // LD_D(0x8);
    // CALL(aBattleAnim_Cosine);
    // LD_HL(BATTLEANIMSTRUCT_XOFFSET);
    // ADD_HL_BC;
    // LD_hl_A;
    bc->xOffset = BattleAnim_Cosine_Conv(var1, 0x8);
    // RET;
}

//  Sideways wave motion while also moving downward until it disappears at y coord $20
//  Obj Param: Is used internally only
void BattleAnimFunction_MetronomeSparkleSketch(struct BattleAnim* bc) {
    // SET_PC(aBattleAnimFunction_MetronomeSparkleSketch);
    // LD_HL(BATTLEANIMSTRUCT_YOFFSET);
    // ADD_HL_BC;
    // LD_A_hl;
    // CP_A(0x20);
    // IF_C goto do_move;
    if(bc->yOffset >= 0x20) {
        // CALL(aDeinitBattleAnimation);
        DeinitBattleAnimation_Conv(bc);
        // RET;
        return;
    }

// do_move:
    // LD_HL(BATTLEANIMSTRUCT_PARAM);
    // ADD_HL_BC;
    // LD_A_hl;
    // LD_D(0x8);
    // CALL(aBattleAnim_Cosine);
    // LD_HL(BATTLEANIMSTRUCT_XOFFSET);
    // ADD_HL_BC;
    // LD_hl_A;
    bc->xOffset = BattleAnim_Cosine_Conv(bc->param, 0x8);
    // LD_HL(BATTLEANIMSTRUCT_PARAM);
    // ADD_HL_BC;
    // LD_A_hl;
    // ADD_A(0x2);
    // LD_hl_A;
    bc->param += 0x2;
    // AND_A(0x7);
    // RET_NZ;
    if(bc->param & 0x7)
        return;
    // LD_HL(BATTLEANIMSTRUCT_YOFFSET);
    // ADD_HL_BC;
    // INC_hl;
    bc->yOffset++;
    // RET;
}

//  Object moves sideways at a speed determined by Obj Param. Can use anim_incobj to make it disappear
void BattleAnimFunction_Agility(struct BattleAnim* bc) {
    // SET_PC(aBattleAnimFunction_Agility);
    // CALL(aBattleAnim_AnonJumptable);

// anon_dw:

    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 0) goto zero;
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 1) goto one;

    switch(bc->jumptableIndex) {
    case 0:
    // zero:
        // LD_HL(BATTLEANIMSTRUCT_PARAM);
        // ADD_HL_BC;
        // LD_A_hl;
        // LD_HL(BATTLEANIMSTRUCT_XCOORD);
        // ADD_HL_BC;
        // ADD_A_hl;
        // LD_hl_A;
        bc->xCoord += bc->param;
        // RET;
        return;

    case 1:
    // one:
        // CALL(aDeinitBattleAnimation);
        DeinitBattleAnimation_Conv(bc);
        // RET;
        return;
    }
}

//  Moves object in a circle where the width is 1/2 the height
//  Obj Param: Defines starting point in circle
void BattleAnimFunction_SafeguardProtect(struct BattleAnim* bc) {
    // SET_PC(aBattleAnimFunction_SafeguardProtect);
    // LD_HL(BATTLEANIMSTRUCT_PARAM);
    // ADD_HL_BC;
    // LD_A_hl;
    // LD_D(0x18);
    // PUSH_AF;
    // PUSH_DE;
    // CALL(aBattleAnim_Sine);
    // LD_HL(BATTLEANIMSTRUCT_YOFFSET);
    // ADD_HL_BC;
    // LD_hl_A;
    bc->yOffset = BattleAnim_Sine_Conv(bc->param, 0x18);
    // POP_DE;
    // POP_AF;
    // CALL(aBattleAnim_Cosine);
    // LD_HL(BATTLEANIMSTRUCT_XOFFSET);
    // ADD_HL_BC;
    // SRA_A;
    // LD_hl_A;
    bc->xOffset = (uint8_t)((int8_t)BattleAnim_Cosine_Conv(bc->param, 0x18) >> 1);
    // LD_HL(BATTLEANIMSTRUCT_PARAM);
    // ADD_HL_BC;
    // LD_A_hl;
    // INC_hl;
    bc->param++;
    // RET;
}

//  Moves objects towards a center position
//  Obj Param: Used to define object angle from 0 to 3. Lower nybble defines how much to increase from base frameset while upper nybble defines angle of movement. The object moves for $28 frames, then waits for $10 frames and disappears
void BattleAnimFunction_LockOnMindReader(struct BattleAnim* bc) {
    // SET_PC(aBattleAnimFunction_LockOnMindReader);
    // CALL(aBattleAnim_AnonJumptable);

// anon_dw:

    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 0) goto zero;
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 1) goto one;
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 2) goto two;

    switch(bc->jumptableIndex) {
    case 0:
    // zero:
        // CALL(aBattleAnim_IncAnonJumptableIndex);
        bc->jumptableIndex++;
        // LD_HL(BATTLEANIMSTRUCT_VAR1);
        // ADD_HL_BC;
        // LD_hl(0x28);
        bc->var1 = 0x28;
        // LD_HL(BATTLEANIMSTRUCT_PARAM);
        // ADD_HL_BC;
        // LD_A_hl;
        // AND_A(0xf);
        // LD_HL(BATTLEANIMSTRUCT_FRAMESET_ID);
        // ADD_HL_BC;
        // ADD_A_hl;  // BATTLEANIMFRAMESET_8F BATTLEANIMFRAMESET_90 BATTLEANIMFRAMESET_91
        // ['?']  // BATTLEANIMFRAMESET_93 BATTLEANIMFRAMESET_94 BATTLEANIMFRAMESET_95
        // CALL(aReinitBattleAnimFrameset);
        ReinitBattleAnimFrameset_Conv(bc, (bc->param & 0xf) + bc->framesetId);
        // LD_HL(BATTLEANIMSTRUCT_PARAM);
        // ADD_HL_BC;
        // LD_A_hl;
        // AND_A(0xf0);
        // OR_A(0x8);
        // LD_hl_A;
        bc->param = (bc->param & 0xf0) | 0x8;
        fallthrough;

    case 1:
    // one:
        // LD_HL(BATTLEANIMSTRUCT_VAR1);
        // ADD_HL_BC;
        // LD_A_hl;
        // AND_A_A;
        // IF_Z goto done;
        if(bc->var1 != 0) {
            uint8_t var1 = (bc->var1--) + 0x8;
            // DEC_hl;
            // ADD_A(0x8);
            // LD_D_A;
            // LD_HL(BATTLEANIMSTRUCT_PARAM);
            // ADD_HL_BC;
            // LD_A_hl;
            // PUSH_AF;
            // PUSH_DE;
            // CALL(aBattleAnim_Sine);
            // LD_HL(BATTLEANIMSTRUCT_YOFFSET);
            // ADD_HL_BC;
            // LD_hl_A;
            bc->yOffset = BattleAnim_Sine_Conv(bc->param, var1);
            // POP_DE;
            // POP_AF;
            // CALL(aBattleAnim_Cosine);
            // LD_HL(BATTLEANIMSTRUCT_XOFFSET);
            // ADD_HL_BC;
            // LD_hl_A;
            bc->xOffset = BattleAnim_Cosine_Conv(bc->param, var1);
            // RET;
            return;
        }

    // done:
        // LD_hl(0x10);
        bc->var1 = 0x10;
        // CALL(aBattleAnim_IncAnonJumptableIndex);
        bc->jumptableIndex++;
        fallthrough;

    case 2:
    // two:
        // LD_HL(BATTLEANIMSTRUCT_VAR1);
        // ADD_HL_BC;
        // LD_A_hl;
        // DEC_hl;
        // AND_A_A;
        // RET_NZ;
        if(bc->var1-- != 0)
            return;
        // CALL(aDeinitBattleAnimation);
        DeinitBattleAnimation_Conv(bc);
        // RET;
        return;
    }
}

//  Object moves horizontally in a sine wave, while also moving left every other frame and downwards for $38 frames after which it disappears
//  Obj Param: Defines a frameset offset from FRAMESET_24
void BattleAnimFunction_HealBellNotes(struct BattleAnim* bc) {
    // SET_PC(aBattleAnimFunction_HealBellNotes);
    // CALL(aBattleAnim_AnonJumptable);

// anon_dw:

    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 0) goto zero;
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 1) goto one;

    switch(bc->jumptableIndex) {
    case 0:
    // zero:
        // CALL(aBattleAnim_IncAnonJumptableIndex);
        bc->jumptableIndex++;
        // LD_HL(BATTLEANIMSTRUCT_PARAM);
        // ADD_HL_BC;
        // LD_A(BATTLEANIMFRAMESET_24);
        // ADD_A_hl;  // BATTLEANIMFRAMESET_25 BATTLEANIMFRAMESET_26
        // CALL(aReinitBattleAnimFrameset);
        ReinitBattleAnimFrameset_Conv(bc, BATTLEANIMFRAMESET_24 + bc->param);
        fallthrough;

    case 1:
    // one:
        // LD_HL(BATTLEANIMSTRUCT_YOFFSET);
        // ADD_HL_BC;
        // LD_A_hl;
        // CP_A(0x38);
        // IF_NC goto done;
        if(bc->yOffset < 0x38) {
            // INC_hl;
            bc->yOffset++;
            // LD_HL(BATTLEANIMSTRUCT_VAR1);
            // ADD_HL_BC;
            // LD_A_hl;
            // INC_hl;
            // LD_D(0x18);
            // CALL(aBattleAnim_Cosine);
            // LD_HL(BATTLEANIMSTRUCT_XOFFSET);
            // ADD_HL_BC;
            // LD_hl_A;
            bc->xOffset = BattleAnim_Cosine_Conv(bc->var1++, 0x18);
            // LD_HL(BATTLEANIMSTRUCT_YCOORD);
            // ADD_HL_BC;
            // LD_A_hl;
            // AND_A(0x1);
            // RET_NZ;
            if(bc->yCoord & 0x1)
                return;
            // LD_HL(BATTLEANIMSTRUCT_XCOORD);
            // ADD_HL_BC;
            // DEC_hl;
            bc->xCoord--;
            // RET;
            return;
        }

    // done:
        // CALL(aDeinitBattleAnimation);
        DeinitBattleAnimation_Conv(bc);
        // RET;
        return;
    }
}

//  Object falls vertially and bounces on the ground
//  Obj Param: Defines speed and duration
void BattleAnimFunction_BatonPass(struct BattleAnim* bc) {
    // SET_PC(aBattleAnimFunction_BatonPass);
    // LD_HL(BATTLEANIMSTRUCT_PARAM);
    // ADD_HL_BC;
    // LD_A_hl;
    // AND_A_A;
    // RET_Z;
    if(bc->param == 0)
        return;
    // LD_D_A;
    // LD_HL(BATTLEANIMSTRUCT_VAR1);
    // ADD_HL_BC;
    // LD_A_hl;
    // INC_hl;
    // CALL(aBattleAnim_Sine);
    uint8_t sine = BattleAnim_Sine_Conv(bc->var1++, bc->param);
    // BIT_A(7);
    // IF_NZ goto negative;
    if(!bit_test(sine, 7)) {
        // XOR_A(0xff);
        // INC_A;
        sine = (sine ^ 0xff) + 1;
    }

// negative:
    // LD_HL(BATTLEANIMSTRUCT_YOFFSET);
    // ADD_HL_BC;
    // LD_hl_A;
    bc->yOffset = sine;
    // LD_HL(BATTLEANIMSTRUCT_VAR1);
    // ADD_HL_BC;
    // LD_A_hl;
    // AND_A(0x1f);
    // RET_NZ;
    if(bc->var1 & 0x1f)
        return;
    // LD_HL(BATTLEANIMSTRUCT_PARAM);
    // ADD_HL_BC;
    // SRL_hl;
    bc->param >>= 1;
    // RET;
}

//  Object moves at an arc for 8 frames and disappears
//  Obj Param: Defines startging position in the arc
void BattleAnimFunction_EncoreBellyDrum(struct BattleAnim* bc) {
    // SET_PC(aBattleAnimFunction_EncoreBellyDrum);
    // LD_HL(BATTLEANIMSTRUCT_VAR1);
    // ADD_HL_BC;
    // LD_A_hl;
    // CP_A(0x10);
    // IF_NC goto done;
    if(bc->var1 < 0x10) {
        uint8_t var1 = bc->var1;
        // INC_hl;
        // INC_hl;
        bc->var1 += 2;
        // LD_D_A;
        // LD_HL(BATTLEANIMSTRUCT_PARAM);
        // ADD_HL_BC;
        // LD_A_hl;
        // PUSH_AF;
        // PUSH_DE;
        // CALL(aBattleAnim_Sine);
        // LD_HL(BATTLEANIMSTRUCT_YOFFSET);
        // ADD_HL_BC;
        // LD_hl_A;
        bc->yOffset = BattleAnim_Sine_Conv(bc->param, var1);
        // POP_DE;
        // POP_AF;
        // CALL(aBattleAnim_Cosine);
        // LD_HL(BATTLEANIMSTRUCT_XOFFSET);
        // ADD_HL_BC;
        // LD_hl_A;
        bc->xOffset = BattleAnim_Cosine_Conv(bc->param, var1);
        // RET;
        return;
    }

// done:
    // CALL(aDeinitBattleAnimation);
    DeinitBattleAnimation_Conv(bc);
    // RET;
    return;
}

//  Moves object at an angle
//  Obj Param: Lower 6 bits define angle of movement and upper 2 bits define speed
void BattleAnimFunction_SwaggerMorningSun(struct BattleAnim* bc) {
    // SET_PC(aBattleAnimFunction_SwaggerMorningSun);
    // LD_HL(BATTLEANIMSTRUCT_PARAM);
    // ADD_HL_BC;
    // LD_E_hl;
    uint8_t param = bc->param;
    // LD_HL(BATTLEANIMSTRUCT_VAR1);
    // ADD_HL_BC;
    // LD_D_hl;
    uint8_t var1 = bc->var1;
    // LD_A_E;
    // AND_A(0xc0);
    // RLCA;
    // RLCA;
    // ADD_A_hl;
    // LD_hl_A;
    bc->param += RotateLeftC8(RotateLeftC8(param & 0xc0));
    // LD_A_E;
    // AND_A(0x3f);
    // PUSH_AF;
    // PUSH_DE;
    // CALL(aBattleAnim_Sine);
    // LD_HL(BATTLEANIMSTRUCT_YOFFSET);
    // ADD_HL_BC;
    // LD_hl_A;
    bc->yOffset = BattleAnim_Sine_Conv(param & 0x3f, var1);
    // POP_DE;
    // POP_AF;
    // CALL(aBattleAnim_Cosine);
    // LD_HL(BATTLEANIMSTRUCT_XOFFSET);
    // ADD_HL_BC;
    // LD_hl_A;
    bc->xOffset = BattleAnim_Cosine_Conv(param & 0x3f, var1);
    // RET;
}

//  Moves object in a ring around position. Uses anim_incobj to move to second phase,  where it expands the radius 8 pixels at a time for 13 frames and then disappears
//  Obj Param: Defines starting position in circle
void BattleAnimFunction_HiddenPower(struct BattleAnim* bc) {
    // SET_PC(aBattleAnimFunction_HiddenPower);
    // CALL(aBattleAnim_AnonJumptable);

// anon_dw:

    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 0) goto zero;
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 1) goto one;
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 2) goto two;

    switch(bc->jumptableIndex) {
    case 0:
    // zero:
        // LD_D(0x18);
        // LD_HL(BATTLEANIMSTRUCT_PARAM);
        // ADD_HL_BC;
        // LD_A_hl;
        // INC_hl;
        // goto step_circle;
        BattleAnim_StepCircle(bc, bc->param++, 0x18);
        return;

    case 1:
    // one:
        // CALL(aBattleAnim_IncAnonJumptableIndex);
        bc->jumptableIndex++;
        // LD_HL(BATTLEANIMSTRUCT_VAR1);
        // ADD_HL_BC;
        // LD_hl(0x18);
        bc->var1 = 0x18;
        fallthrough;

    case 2:
    // two:
        // LD_HL(BATTLEANIMSTRUCT_VAR1);
        // ADD_HL_BC;
        // LD_A_hl;
        // CP_A(0x80);
        // IF_NC goto done;
        if(bc->var1 < 0x80) {
            uint8_t var1 = bc->var1;
            // LD_D_A;
            // ADD_A(0x8);
            // LD_hl_A;
            bc->var1 += 0x8;
            // LD_HL(BATTLEANIMSTRUCT_PARAM);
            // ADD_HL_BC;
            // LD_A_hl;
            // goto step_circle;
            BattleAnim_StepCircle(bc, bc->param, var1);
            return;
        }

    // done:
        // CALL(aDeinitBattleAnimation);
        DeinitBattleAnimation_Conv(bc);
        // RET;
        return;

    // step_circle:
        // CALL(aBattleAnim_StepCircle);
        // RET;
    }
}

//  Object moves down and to the left 2 pixels at a time until it reaches x coord $30 and disappears
void BattleAnimFunction_Curse(struct BattleAnim* bc) {
    // SET_PC(aBattleAnimFunction_Curse);
    // CALL(aBattleAnim_AnonJumptable);

// anon_dw:

    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 0) goto zero;
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 1) goto one;

    switch(bc->jumptableIndex) {
    case 1:
    // one:
        // LD_HL(BATTLEANIMSTRUCT_XCOORD);
        // ADD_HL_BC;
        // LD_A_hl;
        // CP_A(0x30);
        // IF_C goto done;
        if(bc->xCoord >= 0x30) {
            // LD_HL(BATTLEANIMSTRUCT_XCOORD);
            // ADD_HL_BC;
            // DEC_hl;
            // DEC_hl;
            bc->xCoord -= 2;
            // LD_HL(BATTLEANIMSTRUCT_YCOORD);
            // ADD_HL_BC;
            // INC_hl;
            // INC_hl;
            bc->yCoord += 2;
            // RET;
            return;
        }

    // done:
        // CALL(aDeinitBattleAnimation);
        DeinitBattleAnimation_Conv(bc);
        fallthrough;

    case 0:
    // zero:
        // RET;
        return;
    }
}

//  Moves object in a large circle with a x radius of $50 and a y radius 1/4 or that, while also moving downwards
//  Obj Param: Defines starting position in the circle
void BattleAnimFunction_PerishSong(struct BattleAnim* bc) {
    // SET_PC(aBattleAnimFunction_PerishSong);
    // LD_D(0x50);
    // LD_HL(BATTLEANIMSTRUCT_PARAM);
    // ADD_HL_BC;
    // LD_A_hl;
    uint8_t param = bc->param;
    // INC_hl;
    // INC_hl;
    bc->param += 2;
    // PUSH_AF;
    // PUSH_DE;
    // CALL(aBattleAnim_Sine);
    int8_t sine = (int8_t)BattleAnim_Sine_Conv(param, 0x50);
    // SRA_A;
    // SRA_A;
    // LD_HL(BATTLEANIMSTRUCT_VAR1);
    // ADD_HL_BC;
    // ADD_A_hl;
    // INC_hl;
    // LD_HL(BATTLEANIMSTRUCT_YOFFSET);
    // ADD_HL_BC;
    // LD_hl_A;
    bc->yOffset = (sine >> 2) + (bc->var1++);
    // POP_DE;
    // POP_AF;
    // CALL(aBattleAnim_Cosine);
    // LD_HL(BATTLEANIMSTRUCT_XOFFSET);
    // ADD_HL_BC;
    // LD_hl_A;
    bc->xOffset = BattleAnim_Cosine_Conv(param, 0x50);
    // RET;
}

//  Object moves upwards 4 pixels per frame until it disappears at y coord $d0
void BattleAnimFunction_RapidSpin(struct BattleAnim* bc) {
    // SET_PC(aBattleAnimFunction_RapidSpin);
    // LD_HL(BATTLEANIMSTRUCT_YOFFSET);
    // ADD_HL_BC;
    // LD_A_hl;
    // CP_A(0xd0);
    // IF_Z goto done;
    if(bc->yOffset == 0xd0) {
    // done:
        // CALL(aDeinitBattleAnimation);
        DeinitBattleAnimation_Conv(bc);
        // RET;
        return;
    }
    // DEC_hl;
    // DEC_hl;
    // DEC_hl;
    // DEC_hl;
    bc->yOffset -= 4;
    // RET;
}

//  Working but unused animation
//  Object moves either down or up 4 pixels per frame, depending on Obj Param. Object disappears after 23 frames when going down, or at y coord $d8 when going up
//  Obj Param: 0 moves downwards, 1 moves upwards
void BattleAnimFunction_BetaPursuit(struct BattleAnim* bc) {
    // SET_PC(aBattleAnimFunction_BetaPursuit);
    // CALL(aBattleAnim_AnonJumptable);

// anon_dw:

    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 0) goto zero;
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 1) goto one;
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 2) goto two;
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 3) goto three;

    switch(bc->jumptableIndex) {
    case 0:
    // zero:
        // LD_HL(BATTLEANIMSTRUCT_PARAM);
        // ADD_HL_BC;
        // LD_A_hl;
        // AND_A_A;
        // IF_NZ goto move_up;
        if(bc->param != 0)
            goto move_up;
        // CALL(aBattleAnim_IncAnonJumptableIndex);
        bc->jumptableIndex++;
        // LD_HL(BATTLEANIMSTRUCT_YOFFSET);
        // ADD_HL_BC;
        // LD_hl(0xec);
        bc->yOffset = 0xec;
        fallthrough;

    case 1:
    // one:
        // LD_HL(BATTLEANIMSTRUCT_YOFFSET);
        // ADD_HL_BC;
        // LD_A_hl;
        // CP_A(0x4);
        // IF_Z goto three;
        if(bc->yOffset != 0x4) {
            // INC_hl;
            // INC_hl;
            // INC_hl;
            // INC_hl;
            bc->yOffset += 4;
            // RET;
            return;
        }
        fallthrough;

    case 3:
    // three:
        // CALL(aDeinitBattleAnimation);
        DeinitBattleAnimation_Conv(bc);
        // RET;
        return;

    move_up:
        // CALL(aBattleAnim_IncAnonJumptableIndex);
        // CALL(aBattleAnim_IncAnonJumptableIndex);
        bc->jumptableIndex += 2;
        fallthrough;

    case 2:
    // two:
        // LD_HL(BATTLEANIMSTRUCT_YOFFSET);
        // ADD_HL_BC;
        // LD_A_hl;
        // CP_A(0xd8);
        // RET_Z;
        if(bc->yOffset == 0xd8)
            return;
        // DEC_hl;
        // DEC_hl;
        // DEC_hl;
        // DEC_hl;
        bc->yOffset -= 4;
        // RET;
        return;
    }
}

//  Object moves down 4 pixels at a time and right a variable distance
//  Obj Param: Defines variation in the movement
//             $0: 2 pixels horizontal movement
//             $1: 8 pixels horizontal movement
//             $2: 4 pixels horizontal movement
void BattleAnimFunction_RainSandstorm(struct BattleAnim* bc) {
    // SET_PC(aBattleAnimFunction_RainSandstorm);
    // CALL(aBattleAnim_AnonJumptable);

// anon_dw:

    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 0) goto zero;
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 1) goto one;
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 2) goto two;
    // if (gb_read(REG_BC + BATTLEANIMSTRUCT_JUMPTABLE_INDEX) == 3) goto three;

    switch(bc->jumptableIndex) {
    case 0:
    // zero:
        // LD_HL(BATTLEANIMSTRUCT_PARAM);
        // ADD_HL_BC;
        // LD_A_hl;
        // LD_HL(BATTLEANIMSTRUCT_JUMPTABLE_INDEX);
        // ADD_HL_BC;
        // LD_hl_A;
        bc->jumptableIndex = bc->param;
        // CALL(aBattleAnim_IncAnonJumptableIndex);
        bc->jumptableIndex++;
        // RET;
        return;

    case 1:
    // one:
        //
        //  Obj Param 0
        // LD_HL(BATTLEANIMSTRUCT_YOFFSET);
        // ADD_HL_BC;
        // LD_A_hl;
        // ADD_A(0x4);
        // CP_A(0x70);
        // IF_C goto dont_reset_y_offset_one;
        if(bc->yOffset + 0x4 >= 0x70) {
            // XOR_A_A;
            bc->yOffset = 0;
        }
        else {
        // dont_reset_y_offset_one:
            // LD_hl_A;
            bc->yOffset += 0x4;
        }
        // LD_HL(BATTLEANIMSTRUCT_XOFFSET);
        // ADD_HL_BC;
        // INC_hl;
        // INC_hl;
        bc->xOffset += 2;
        // RET;
        return;

    case 2:
    // two:
        //
        //  Obj Param 1
        // LD_HL(BATTLEANIMSTRUCT_YOFFSET);
        // ADD_HL_BC;
        // LD_A_hl;
        // ADD_A(0x4);
        // CP_A(0x70);
        // IF_C goto dont_reset_y_offset_two;
        if(bc->yOffset + 0x4 >= 0x70) {
            // XOR_A_A;
            bc->yOffset = 0;
        }
        else {
        // dont_reset_y_offset_two:
            // LD_hl_A;
            bc->yOffset += 0x4;
        }
        // LD_HL(BATTLEANIMSTRUCT_XOFFSET);
        // ADD_HL_BC;
        // LD_A_hl;
        // ADD_A(0x8);
        // LD_hl_A;
        bc->xOffset += 0x8;
        // RET;
        return;

    case 3:
    // three:
        //
        //  Obj Param 2
        // LD_HL(BATTLEANIMSTRUCT_YOFFSET);
        // ADD_HL_BC;
        // LD_A_hl;
        // ADD_A(0x4);
        // CP_A(0x70);
        // IF_C goto dont_reset_y_offset_three;
        if(bc->yOffset + 0x4 >= 0x70) {
            // XOR_A_A;
            bc->yOffset = 0;
        }
        else {
        // dont_reset_y_offset_three:
            // LD_hl_A;
            bc->yOffset += 0x4;
        }
        // LD_HL(BATTLEANIMSTRUCT_XOFFSET);
        // ADD_HL_BC;
        // LD_A_hl;
        // ADD_A(0x4);
        // LD_hl_A;
        bc->xOffset += 0x4;
        // RET;
        return;
    }
}

void BattleAnimFunction_AnimObjB0(void) {
    SET_PC(aBattleAnimFunction_AnimObjB0);
    //  //  unused
    //  Used by object ANIM_OBJ_B0, with itself is not used in any animation
    //  Obj Param: Lower nybble is added to VAR1 while upper nybble is added to XCOORD
    LD_HL(BATTLEANIMSTRUCT_XCOORD);
    ADD_HL_BC;
    LD_D_hl;
    LD_HL(BATTLEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_E_hl;
    LD_HL(BATTLEANIMSTRUCT_PARAM);
    ADD_HL_BC;
    LD_A_hl;
    LD_L_A;
    AND_A(0xf0);
    LD_H_A;
    SWAP_A;
    OR_A_H;
    LD_H_A;
    LD_A_L;
    AND_A(0xf);
    SWAP_A;
    LD_L_A;
    ADD_HL_DE;
    LD_E_L;
    LD_D_H;
    LD_HL(BATTLEANIMSTRUCT_XCOORD);
    ADD_HL_BC;
    LD_hl_D;
    LD_HL(BATTLEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_hl_E;
    RET;
}

//  Object moves in a circle
//  Obj Param: Defines starting position in the circle
void BattleAnimFunction_PsychUp(struct BattleAnim* bc) {
    // SET_PC(aBattleAnimFunction_PsychUp);
    // LD_D(0x18);
    // LD_HL(BATTLEANIMSTRUCT_PARAM);
    // ADD_HL_BC;
    // LD_A_hl;
    // INC_hl;
    // CALL(aBattleAnim_StepCircle);
    BattleAnim_StepCircle(bc, bc->param++, 0x18);
    // RET;
}

//  Object moves in a circle slowly
//  Obj Param: Defines starting position in the circle
void BattleAnimFunction_Cotton(struct BattleAnim* bc) {
    // SET_PC(aBattleAnimFunction_Cotton);
    // LD_D(0x18);
    // LD_HL(BATTLEANIMSTRUCT_VAR2);
    // ADD_HL_BC;
    // LD_A_hl;
    // INC_hl;
    uint8_t var2 = bc->var2++;
    // SRL_A;
    // LD_HL(BATTLEANIMSTRUCT_PARAM);
    // ADD_HL_BC;
    // ADD_A_hl;
    // CALL(aBattleAnim_StepCircle);
    BattleAnim_StepCircle(bc, bc->param + (var2 >> 1), 0x18);
    // RET;
}

//  Object moves up and down in an arc for $20 frames and then disappear
//  Obj Param: Defines range of arc motion
void BattleAnimFunction_AncientPower(struct BattleAnim* bc) {
    // SET_PC(aBattleAnimFunction_AncientPower);
    // LD_HL(BATTLEANIMSTRUCT_VAR1);
    // ADD_HL_BC;
    // LD_A_hl;
    // CP_A(0x20);
    // IF_NC goto done;
    if(bc->var1 >= 0x20) {
    // done:
        // CALL(aDeinitBattleAnimation);
        DeinitBattleAnimation_Conv(bc);
        // RET;
        return;
    }
    // INC_hl;
    // LD_HL(BATTLEANIMSTRUCT_PARAM);
    // ADD_HL_BC;
    // LD_D_hl;
    // CALL(aBattleAnim_Sine);
    // XOR_A(0xff);
    // INC_A;
    // LD_HL(BATTLEANIMSTRUCT_YOFFSET);
    // ADD_HL_BC;
    // LD_hl_A;
    bc->yOffset = -BattleAnim_Sine_Conv(bc->var1++, bc->param);
    // RET;
}

void BattleAnim_StepCircle(struct BattleAnim* bc, uint8_t a, uint8_t d) {
    // SET_PC(aBattleAnim_StepCircle);
    //  Inches object in a circular movement where its height is 1/4 the width
    // PUSH_AF;
    // PUSH_DE;
    // CALL(aBattleAnim_Sine);
    int8_t res = (int8_t)BattleAnim_Sine_Conv(a, d);
    // SRA_A;
    // SRA_A;
    // LD_HL(BATTLEANIMSTRUCT_YOFFSET);
    // ADD_HL_BC;
    // LD_hl_A;
    bc->yOffset = res >> 2;
    // POP_DE;
    // POP_AF;
    // CALL(aBattleAnim_Cosine);
    // LD_HL(BATTLEANIMSTRUCT_XOFFSET);
    // ADD_HL_BC;
    // LD_hl_A;
    bc->xOffset = BattleAnim_Cosine_Conv(a, d);
    // RET;
}

void BattleAnim_StepToTarget(struct BattleAnim* bc, uint8_t a) {
    // SET_PC(aBattleAnim_StepToTarget);
    //  Inches object towards the opponent's side, moving half as much in the Y axis as it did in the X axis. Uses lower nybble of A
    // AND_A(0xf);
    // LD_E_A;
    // LD_HL(BATTLEANIMSTRUCT_XCOORD);
    // ADD_HL_BC;
    // ADD_A_hl;
    // LD_hl_A;
    bc->xCoord += a;
    // SRL_E;
    // LD_HL(BATTLEANIMSTRUCT_YCOORD);
    // ADD_HL_BC;

// loop:
    // DEC_hl;
    // DEC_E;
    // IF_NZ goto loop;
    bc->yCoord += a >> 1;
    // RET;
}

void BattleAnim_AnonJumptable(void) {
    SET_PC(aBattleAnim_AnonJumptable);
    POP_DE;
    LD_HL(BATTLEANIMSTRUCT_JUMPTABLE_INDEX);
    ADD_HL_BC;
    LD_L_hl;
    LD_H(0x0);
    ADD_HL_HL;
    ADD_HL_DE;
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    JP_hl;
}

void BattleAnim_IncAnonJumptableIndex(void) {
    SET_PC(aBattleAnim_IncAnonJumptableIndex);
    LD_HL(BATTLEANIMSTRUCT_JUMPTABLE_INDEX);
    ADD_HL_BC;
    INC_hl;
    RET;
}

void BattleAnim_Cosine(void) {
    SET_PC(aBattleAnim_Cosine);
    //  a = d * cos(a * pi/32)
    ADD_A(0b010000);  // cos(x) = sin(x + pi/2)
                      // fallthrough
    return BattleAnim_Sine();
}

uint8_t BattleAnim_Cosine_Conv(uint8_t a, uint8_t d) {
    // SET_PC(aBattleAnim_Cosine);
    //  a = d * cos(a * pi/32)
    // ADD_A(0b010000);  // cos(x) = sin(x + pi/2)
                      // fallthrough
    return BattleAnim_Sine_Conv(a + 0b010000, d);
}

void BattleAnim_Sine(void) {
    SET_PC(aBattleAnim_Sine);
    //  a = d * sin(a * pi/32)
    // calc_sine_wave ['BattleAnimSineWave']
    REG_A = v_Sine_Conv(REG_A, REG_D);

    // return BattleAnim_Sine_e();
}

uint8_t BattleAnim_Sine_Conv(uint8_t a, uint8_t d) {
    // SET_PC(aBattleAnim_Sine);
    //  a = d * sin(a * pi/32)
    // calc_sine_wave ['BattleAnimSineWave']
    return v_Sine_Conv(a, d);

    // return BattleAnim_Sine_e();
}

void BattleAnim_Sine_e(void) {
    SET_PC(aBattleAnim_Sine_e);
    // LD_A_E;
    REG_A = REG_E;
    // CALL(aBattleAnim_Sine);
    REG_E = BattleAnim_Cosine_Conv(REG_A, REG_D);
    // LD_E_A;
    // RET;
}

uint8_t BattleAnim_Sine_e_Conv(uint8_t e, uint8_t d) {
    // SET_PC(aBattleAnim_Sine_e);
    // LD_A_E;
    // CALL(aBattleAnim_Sine);
    // LD_E_A;
    // RET;
    return BattleAnim_Sine_Conv(e, d);
}

void BattleAnim_Cosine_e(void) {
    SET_PC(aBattleAnim_Cosine_e);
    // LD_A_E;
    REG_A = REG_E;
    // CALL(aBattleAnim_Cosine);
    REG_E = BattleAnim_Cosine_Conv(REG_A, REG_D);
    // LD_E_A;
    // RET;
}

uint8_t BattleAnim_Cosine_e_Conv(uint8_t e, uint8_t d) {
    // SET_PC(aBattleAnim_Cosine_e);
    // LD_A_E;
    // CALL(aBattleAnim_Cosine);
    // LD_E_A;
    // RET;
    return BattleAnim_Cosine_Conv(e, d);
}

void BattleAnim_AbsSinePrecise(void) {
    SET_PC(aBattleAnim_AbsSinePrecise);
    //  //  unreferenced
    LD_A_E;
    CALL(aBattleAnim_Sine);
    LD_E_L;
    LD_D_H;
    RET;
}

void BattleAnim_AbsCosinePrecise(void) {
    SET_PC(aBattleAnim_AbsCosinePrecise);
    //  //  unreferenced
    LD_A_E;
    CALL(aBattleAnim_Cosine);
    LD_E_L;
    LD_D_H;
    RET;
}

void BattleAnimSineWave(void) {
    SET_PC(aBattleAnimSineWave);
    // sine_table ['32']
}
