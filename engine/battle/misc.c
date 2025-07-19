#include "../../constants.h"
#include "misc.h"
#include "effect_commands.h"
#include "../gfx/place_graphic.h"
#include "../../home/battle_vars.h"
#include "../../home/text.h"
#include "../../data/battle/weather_modifiers.h"
#include "../../data/types/badge_type_boosts.h"

struct PicCoords {
    tile_t* hl;
    uint8_t b;
    uint8_t c;
};

static struct PicCoords GetEnemyFrontpicCoords(void) {
    return (struct PicCoords){.hl = coord(12, 0, wram->wTilemap), .b = 7, .c = 7};
}

static struct PicCoords GetPlayerBackpicCoords(void){
    return (struct PicCoords){.hl = coord(2, 6, wram->wTilemap), .b = 6, .c = 6};
}

void v_DisappearUser(void){
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram.hBGMapMode = BGMAPMODE_NONE;
    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // IF_Z goto player;
    struct PicCoords ccoords;
    if(hram.hBattleTurn != TURN_PLAYER) {
        // CALL(aGetEnemyFrontpicCoords);
        // goto okay;
        ccoords = GetEnemyFrontpicCoords();
    }
    else {
    // player:
        // CALL(aGetPlayerBackpicCoords);
        ccoords = GetPlayerBackpicCoords();
    }

// okay:
    // CALL(aClearBox);
    ClearBox(ccoords.hl, ccoords.c, ccoords.b);
    // JR(mFinishAppearDisappearUser);
    return FinishAppearDisappearUser();
}

void v_AppearUserRaiseSub(void){
    // FARCALL(aBattleCommand_RaiseSubNoAnim);
    BattleCommand_RaiseSubNoAnim();
    // JR(mAppearUser);
    return AppearUser();
}

void v_AppearUserLowerSub(void){
    // FARCALL(aBattleCommand_LowerSubNoAnim);
    BattleCommand_LowerSubNoAnim();

    return AppearUser();
}

void AppearUser(void){
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram.hBGMapMode = BGMAPMODE_NONE;
    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // IF_Z goto player;
    struct PicCoords ccoords;
    uint8_t a;
    if(hram.hBattleTurn != TURN_PLAYER) {
        // CALL(aGetEnemyFrontpicCoords);
        ccoords = GetEnemyFrontpicCoords();
        // XOR_A_A;
        a = 0;
        // goto okay;
    }
    else {
    // player:
        // CALL(aGetPlayerBackpicCoords);
        ccoords = GetPlayerBackpicCoords();
        // LD_A(0x31);
        a = 0x31;
    }
// okay:
    // LDH_addr_A(hGraphicStartTile);
    hram.hGraphicStartTile = a;
    // PREDEF(pPlaceGraphic);
    PlaceGraphicYStagger(ccoords.hl, ccoords.b, ccoords.c);
    return FinishAppearDisappearUser();
}

void FinishAppearDisappearUser(void){
    // LD_A(0x1);
    // LDH_addr_A(hBGMapMode);
    hram.hBGMapMode = BGMAPMODE_UPDATE_TILES;
    // RET;
}

// void GetEnemyFrontpicCoords(void){
//     hlcoord(12, 0, wTilemap);
//     LD_BC((7 << 8) | 7);
//     RET;

// }

// void GetPlayerBackpicCoords(void){
//     hlcoord(2, 6, wTilemap);
//     LD_BC((6 << 8) | 6);
//     RET;

// }

static void DoWeatherModifiers_ApplyModifier(const uint8_t* de) {
    // XOR_A_A;
    // LDH_addr_A(hMultiplicand + 0);
    // LD_HL(wCurDamage);
    // LD_A_hli;
    // LDH_addr_A(hMultiplicand + 1);
    // LD_A_hl;
    // LDH_addr_A(hMultiplicand + 2);
    uint16_t dmg = BigEndianToNative16(wram->wCurDamage);

    // INC_DE;
    // LD_A_de;
    // LDH_addr_A(hMultiplier);

    // CALL(aMultiply);
    uint32_t n = dmg * de[1];

    // LD_A(10);
    // LDH_addr_A(hDivisor);
    // LD_B(4);
    // CALL(aDivide);
    n /= 10;

    uint16_t r;
    if((n & 0xff0000) != 0) {
        // LDH_A_addr(hQuotient + 1);
        // AND_A_A;
        // LD_BC(-1);
        // IF_NZ goto Update;
        r = 0xffff;
    }
    else if((n & 0xffff) != 0) {
        // LDH_A_addr(hQuotient + 2);
        // LD_B_A;
        // LDH_A_addr(hQuotient + 3);
        // LD_C_A;
        r = (uint16_t)n;
        // OR_A_B;
        // IF_NZ goto Update;
    }
    else {
        // LD_BC(1);
        r = 1;
    }

// Update:
    // LD_A_B;
    // LD_addr_A(wCurDamage);
    // LD_A_C;
    // LD_addr_A(wCurDamage + 1);
    wram->wCurDamage = NativeToBigEndian16(r);


// done:
    // RET;
}

void DoWeatherModifiers(void){
    // LD_DE(mWeatherTypeModifiers);
    const uint8_t* de = WeatherTypeModifiers;
    // LD_A_addr(wBattleWeather);
    // LD_B_A;
    uint8_t b = wram->wBattleWeather;
    // LD_A_addr(wCurType);
    // LD_C_A;
    uint8_t c = wram->wCurType;


    do {
    // CheckWeatherType:
        // LD_A_de;
        // INC_DE;
        uint8_t a = *(de++);
        // CP_A(-1);
        // IF_Z goto done_weather_types;
        if(a == 0xff)
            break;

        // CP_A_B;
        // IF_NZ goto NextWeatherType;
        if(a != b)
            continue;

        // LD_A_de;
        // CP_A_C;
        // IF_Z goto ApplyModifier;
        if(*de == c)
            return DoWeatherModifiers_ApplyModifier(de);


    // NextWeatherType:
        // INC_DE;
        // INC_DE;
        // goto CheckWeatherType;
    } while(de += 2, 1);


// done_weather_types:
    // LD_DE(mWeatherMoveModifiers);
    de = WeatherMoveModifiers;

    // LD_A(BATTLE_VARS_MOVE_EFFECT);
    // CALL(aGetBattleVar);
    // LD_C_A;
    c = GetBattleVar(BATTLE_VARS_MOVE_EFFECT);

    do {
    // CheckWeatherMove:
        // LD_A_de;
        // INC_DE;
        uint8_t a = *(de++);
        // CP_A(-1);
        // IF_Z goto done;
        if(a == 0xff)
            return;

        // CP_A_B;
        // IF_NZ goto NextWeatherMove;
        if(a != b)
            continue;

        // LD_A_de;
        // CP_A_C;
        // IF_Z goto ApplyModifier;
        if(*de == c)
            return DoWeatherModifiers_ApplyModifier(de);


    // NextWeatherMove:
        // INC_DE;
        // INC_DE;
        // goto CheckWeatherMove;
    } while(de += 2, 1);

    return;
// ApplyModifier:
    // XOR_A_A;
    // LDH_addr_A(hMultiplicand + 0);
    // LD_HL(wCurDamage);
    // LD_A_hli;
    // LDH_addr_A(hMultiplicand + 1);
    // LD_A_hl;
    // LDH_addr_A(hMultiplicand + 2);

    // INC_DE;
    // LD_A_de;
    // LDH_addr_A(hMultiplier);

    // CALL(aMultiply);

    // LD_A(10);
    // LDH_addr_A(hDivisor);
    // LD_B(4);
    // CALL(aDivide);

    // LDH_A_addr(hQuotient + 1);
    // AND_A_A;
    // LD_BC(-1);
    // IF_NZ goto Update;

    // LDH_A_addr(hQuotient + 2);
    // LD_B_A;
    // LDH_A_addr(hQuotient + 3);
    // LD_C_A;
    // OR_A_B;
    // IF_NZ goto Update;

    // LD_BC(1);


// Update:
    // LD_A_B;
    // LD_addr_A(wCurDamage);
    // LD_A_C;
    // LD_addr_A(wCurDamage + 1);


// done:
    // RET;

// INCLUDE "data/battle/weather_modifiers.asm"
}

void DoBadgeTypeBoosts(void){
    // LD_A_addr(wLinkMode);
    // AND_A_A;
    // RET_NZ ;
    if(wram->wLinkMode != LINK_NULL)
        return;

    // LD_A_addr(wInBattleTowerBattle);
    // AND_A_A;
    // RET_NZ ;
    if(wram->wInBattleTowerBattle)
        return;

    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // RET_NZ ;
    if(hram.hBattleTurn != TURN_PLAYER)
        return;

    // PUSH_DE;
    // PUSH_BC;

    // LD_HL(mBadgeTypeBoosts);
    const uint8_t* hl = BadgeTypeBoosts;

    // LD_A_addr(wKantoBadges);
    // LD_B_A;
    // LD_A_addr(wJohtoBadges);
    // LD_C_A;
    uint16_t bc = (gPlayer.kantoBadges[0] << 8) | gPlayer.johtoBadges[0];


    do {
    // CheckBadge:
        // LD_A_hl;
        uint8_t a = *hl;
        // CP_A(-1);
        // IF_Z goto done;
        if(a == 0xff)
            return;

        // SRL_B;
        // RR_C;
        bool carry = bc & 1;
        bc >>= 1;
        // IF_NC goto NextBadge;
        if(!carry)
            continue; 

        // LD_A_addr(wCurType);
        // CP_A_hl;
        // IF_Z goto ApplyBoost;
        if(wram->wCurType == *hl) {
        // ApplyBoost:
            // LD_A_addr(wCurDamage);
            // LD_H_A;
            // LD_D_A;
            // LD_A_addr(wCurDamage + 1);
            // LD_L_A;
            // LD_E_A;
            uint16_t dmg = BigEndianToNative16(wram->wCurDamage);

            // SRL_D;
            // RR_E;
            // SRL_D;
            // RR_E;
            // SRL_D;
            // RR_E;
            uint16_t de2 = dmg >> 3;

            // LD_A_E;
            // OR_A_D;
            // IF_NZ goto done_min;
            // LD_E(1);
            if(de2 == 0)
                de2 = 1;

        // done_min:
            uint32_t temp = dmg + de2;
            // ADD_HL_DE;
            // IF_NC goto Update;
            if(temp > 0xffffu) {
                // LD_HL(0xffff);
                temp = 0xffff;
            }

        // Update:
            // LD_A_H;
            // LD_addr_A(wCurDamage);
            // LD_A_L;
            // LD_addr_A(wCurDamage + 1);
            wram->wCurDamage = NativeToBigEndian16((uint16_t)temp);

        // done:
            // POP_BC;
            // POP_DE;
            // RET;
            return;
        }


    // NextBadge:
        // INC_HL;
        // goto CheckBadge;
    } while(++hl, 1);

// INCLUDE "data/types/badge_type_boosts.asm"

}
