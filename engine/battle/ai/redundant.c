#include "../../../constants.h"
#include "redundant.h"
#include "../move_effects/attract.h"
#include "scoring.h"

//  Check if move effect c will fail because it's already been used.
//  Return false if the move is a good choice.
//  Return true if the move is a bad choice.
bool AI_Redundant(uint8_t c){
    // LD_A_C;
    // LD_DE(3);
    // LD_HL(mAI_Redundant_Moves);
    // CALL(aIsInArray);
    // JP_NC (mAI_Redundant_NotRedundant);
    // INC_HL;
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // JP_hl;
    switch(c) {
// Moves:
    //dbw ['EFFECT_DREAM_EATER', '.DreamEater']
    case EFFECT_DREAM_EATER:
    // DreamEater:
        // LD_A_addr(wBattleMonStatus);
        // AND_A(SLP);
        // IF_Z return true;
        if(wram->wBattleMon.status[0] & SLP)
            return true;
        // goto NotRedundant;
        return false;
    //dbw ['EFFECT_HEAL', '.Heal']
    case EFFECT_HEAL:
    case EFFECT_MORNING_SUN:
    case EFFECT_SYNTHESIS:
    case EFFECT_MOONLIGHT:
        // FARCALL(aAICheckEnemyMaxHP);
        // IF_NC return false;
        // return true;
        return AICheckEnemyMaxHP();
    //dbw ['EFFECT_LIGHT_SCREEN', '.LightScreen']
    case EFFECT_LIGHT_SCREEN:
    // LightScreen:
        // LD_A_addr(wEnemyScreens);
        // BIT_A(SCREENS_LIGHT_SCREEN);
        // RET;
        return bit_test(wram->wEnemyScreens, SCREENS_LIGHT_SCREEN);
    //dbw ['EFFECT_MIST', '.Mist']
    case EFFECT_MIST:
    // Mist:
        // LD_A_addr(wEnemySubStatus4);
        // BIT_A(SUBSTATUS_MIST);
        // RET;
        return bit_test(wram->wEnemySubStatus4, SUBSTATUS_MIST);
    //dbw ['EFFECT_FOCUS_ENERGY', '.FocusEnergy']
    case EFFECT_FOCUS_ENERGY:
    // FocusEnergy:
        // LD_A_addr(wEnemySubStatus4);
        // BIT_A(SUBSTATUS_FOCUS_ENERGY);
        // RET;
        return bit_test(wram->wEnemySubStatus1, SUBSTATUS_FOCUS_ENERGY);
    //dbw ['EFFECT_CONFUSE', '.Confuse']
    case EFFECT_CONFUSE:
    // Confuse:
        // LD_A_addr(wPlayerSubStatus3);
        // BIT_A(SUBSTATUS_CONFUSED);
        // RET_NZ ;
        if(bit_test(wram->wPlayerSubStatus3, SUBSTATUS_CONFUSED))
            return true;
        // LD_A_addr(wPlayerScreens);
        // BIT_A(SCREENS_SAFEGUARD);
        // RET;
        return bit_test(wram->wPlayerScreens, SCREENS_SAFEGUARD);
    //dbw ['EFFECT_TRANSFORM', '.Transform']
    case EFFECT_TRANSFORM:
    // Transform:
        // LD_A_addr(wEnemySubStatus5);
        // BIT_A(SUBSTATUS_TRANSFORMED);
        // RET;
        return bit_test(wram->wEnemySubStatus5, SUBSTATUS_TRANSFORMED);
    //dbw ['EFFECT_REFLECT', '.Reflect']
    case EFFECT_REFLECT:
    // Reflect:
        // LD_A_addr(wEnemyScreens);
        // BIT_A(SCREENS_REFLECT);
        // RET;
        return bit_test(wram->wEnemyScreens, SCREENS_REFLECT);
    //dbw ['EFFECT_SUBSTITUTE', '.Substitute']
    case EFFECT_SUBSTITUTE:
    // Substitute:
        // LD_A_addr(wEnemySubStatus4);
        // BIT_A(SUBSTATUS_SUBSTITUTE);
        // RET;
        return bit_test(wram->wEnemySubStatus4, SUBSTATUS_SUBSTITUTE);
    //dbw ['EFFECT_LEECH_SEED', '.LeechSeed']
    case EFFECT_LEECH_SEED:
    // LeechSeed:
        // LD_A_addr(wPlayerSubStatus4);
        // BIT_A(SUBSTATUS_LEECH_SEED);
        // RET;
        return bit_test(wram->wPlayerSubStatus4, SUBSTATUS_LEECH_SEED);
    //dbw ['EFFECT_DISABLE', '.Disable']
    case EFFECT_DISABLE:
    // Disable:
        // LD_A_addr(wPlayerDisableCount);
        // AND_A_A;
        // RET;
        return wram->wPlayerDisableCount != 0;
    //dbw ['EFFECT_ENCORE', '.Encore']
    case EFFECT_ENCORE:
    // Encore:
        // LD_A_addr(wPlayerSubStatus5);
        // BIT_A(SUBSTATUS_ENCORED);
        // RET;
        return bit_test(wram->wPlayerSubStatus5, SUBSTATUS_ENCORED);
    //dbw ['EFFECT_SNORE', '.Snore']
    case EFFECT_SNORE:
    // Snore:
    //dbw ['EFFECT_SLEEP_TALK', '.SleepTalk']
    case EFFECT_SLEEP_TALK:
    // SleepTalk:
        // LD_A_addr(wEnemyMonStatus);
        // AND_A(SLP);
        // IF_Z goto Redundant;
        if((wram->wEnemyMon.status[0] & SLP) == 0)
            return true;
        // goto NotRedundant;
        return false;
    //dbw ['EFFECT_MEAN_LOOK', '.MeanLook']
    case EFFECT_MEAN_LOOK:
    // MeanLook:
        // LD_A_addr(wEnemySubStatus5);
        // BIT_A(SUBSTATUS_CANT_RUN);
        // RET;
        return bit_test(wram->wEnemySubStatus5, SUBSTATUS_CANT_RUN);
    //dbw ['EFFECT_NIGHTMARE', '.Nightmare']
    case EFFECT_NIGHTMARE:
    // Nightmare:
        // LD_A_addr(wBattleMonStatus);
        // AND_A_A;
        // IF_Z goto Redundant;
        if(wram->wBattleMon.status[0] == 0)
            return true;
        // LD_A_addr(wPlayerSubStatus1);
        // BIT_A(SUBSTATUS_NIGHTMARE);
        // RET;
        return bit_test(wram->wPlayerSubStatus1, SUBSTATUS_NIGHTMARE);
    //dbw ['EFFECT_SPIKES', '.Spikes']
    case EFFECT_SPIKES:
    // Spikes:
        // LD_A_addr(wPlayerScreens);
        // BIT_A(SCREENS_SPIKES);
        // RET;
        return bit_test(wram->wPlayerScreens, SCREENS_SPIKES);
    //dbw ['EFFECT_FORESIGHT', '.Foresight']
    case EFFECT_FORESIGHT:
    // Foresight:
        // LD_A_addr(wPlayerSubStatus1);
        // BIT_A(SUBSTATUS_IDENTIFIED);
        // RET;
        return bit_test(wram->wPlayerSubStatus1, SUBSTATUS_IDENTIFIED);
    //dbw ['EFFECT_PERISH_SONG', '.PerishSong']
    case EFFECT_PERISH_SONG:
    // PerishSong:
        // LD_A_addr(wPlayerSubStatus1);
        // BIT_A(SUBSTATUS_PERISH);
        // RET;
        return bit_test(wram->wPlayerSubStatus1, SUBSTATUS_PERISH);
    //dbw ['EFFECT_SANDSTORM', '.Sandstorm']
    case EFFECT_SANDSTORM:
    // Sandstorm:
        // LD_A_addr(wBattleWeather);
        // CP_A(WEATHER_SANDSTORM);
        // IF_Z goto Redundant;
        if(wram->wBattleWeather == WEATHER_SANDSTORM)
            return true;
        // goto NotRedundant;
        return false;
    //dbw ['EFFECT_ATTRACT', '.Attract']
    case EFFECT_ATTRACT:
    // Attract:
        // FARCALL(aCheckOppositeGender);
        // IF_C return true;
        if(!CheckOppositeGender(wram->wCurBattleMon))
            return true;
        // LD_A_addr(wPlayerSubStatus1);
        // BIT_A(SUBSTATUS_IN_LOVE);
        // RET;
        return bit_test(wram->wPlayerSubStatus1, SUBSTATUS_IN_LOVE);
    //dbw ['EFFECT_SAFEGUARD', '.Safeguard']
    case EFFECT_SAFEGUARD:
    // Safeguard:
        // LD_A_addr(wEnemyScreens);
        // BIT_A(SCREENS_SAFEGUARD);
        // RET;
        return bit_test(wram->wEnemyScreens, SCREENS_SAFEGUARD);
    //dbw ['EFFECT_RAIN_DANCE', '.RainDance']
    case EFFECT_RAIN_DANCE:
    // RainDance:
        // LD_A_addr(wBattleWeather);
        // CP_A(WEATHER_RAIN);
        // IF_Z goto Redundant;
        if(wram->wBattleWeather == WEATHER_RAIN)
            return true;
        // goto NotRedundant;
        return false;
    //dbw ['EFFECT_SUNNY_DAY', '.SunnyDay']
    case EFFECT_SUNNY_DAY:
    // SunnyDay:
        // LD_A_addr(wBattleWeather);
        // CP_A(WEATHER_SUN);
        // IF_Z goto Redundant;
        if(wram->wBattleWeather == WEATHER_SUN)
            return true;
        // goto NotRedundant;
        return false;
    //dbw ['EFFECT_TELEPORT', '.Teleport']
    case EFFECT_TELEPORT:
    // Teleport:
    // Redundant:
        return true;
    //dbw ['EFFECT_MORNING_SUN', '.MorningSun']
    //dbw ['EFFECT_SYNTHESIS', '.Synthesis']
    //dbw ['EFFECT_MOONLIGHT', '.Moonlight']
    //dbw ['EFFECT_SWAGGER', '.Swagger']
    case EFFECT_SWAGGER:
    // Swagger:
        // LD_A_addr(wPlayerSubStatus3);
        // BIT_A(SUBSTATUS_CONFUSED);
        // RET;
        return bit_test(wram->wPlayerSubStatus3, SUBSTATUS_CONFUSED);
    //dbw ['EFFECT_FUTURE_SIGHT', '.FutureSight']
    case EFFECT_FUTURE_SIGHT:
    // FutureSight:
        // LD_A_addr(wEnemyScreens);
        // BIT_A(5);
        // RET;
        return bit_test(wram->wEnemyScreens, 5);
    //db ['-1'];
    default:
        return false;
    }
}
