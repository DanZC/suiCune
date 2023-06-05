#include "../../constants.h"
#include "bg_effects.h"

// const_def ['?']
// const ['BGSQUARE_SIX']
// const ['BGSQUARE_FOUR']
// const ['BGSQUARE_TWO']
// const ['BGSQUARE_SEVEN']
// const ['BGSQUARE_FIVE']
// const ['BGSQUARE_THREE']

//  BG effects for use in battle animations.

void ExecuteBGEffects(void) {
    SET_PC(aExecuteBGEffects);
    LD_HL(wActiveBGEffects);
    LD_E(NUM_BG_EFFECTS);

loop:

    LD_A_hl;
    AND_A_A;
    IF_Z goto next;
    LD_C_L;
    LD_B_H;
    PUSH_HL;
    PUSH_DE;
    CALL(aDoBattleBGEffectFunction);
    POP_DE;
    POP_HL;

next:

    LD_BC(BG_EFFECT_STRUCT_LENGTH);
    ADD_HL_BC;
    DEC_E;
    IF_NZ goto loop;
    RET;
}

void QueueBGEffect(void) {
    SET_PC(aQueueBGEffect);
    LD_HL(wActiveBGEffects);
    LD_E(NUM_BG_EFFECTS);

loop:

    LD_A_hl;
    AND_A_A;
    IF_Z goto load;
    LD_BC(BG_EFFECT_STRUCT_LENGTH);
    ADD_HL_BC;
    DEC_E;
    IF_NZ goto loop;
    SCF;
    RET;

load:

    LD_C_L;
    LD_B_H;
    LD_HL(BG_EFFECT_STRUCT_FUNCTION);
    ADD_HL_BC;
    LD_A_addr(wBattleBGEffectTempID);
    LD_hli_A;
    LD_A_addr(wBattleBGEffectTempJumptableIndex);
    LD_hli_A;
    LD_A_addr(wBattleBGEffectTempTurn);
    LD_hli_A;
    LD_A_addr(wBattleBGEffectTempParam);
    LD_hl_A;
    RET;
}

void EndBattleBGEffect(void) {
    SET_PC(aEndBattleBGEffect);
    LD_HL(BG_EFFECT_STRUCT_FUNCTION);
    ADD_HL_BC;
    LD_hl(0);
    RET;
}

void DoBattleBGEffectFunction(void) {
    SET_PC(aDoBattleBGEffectFunction);
    LD_HL(BG_EFFECT_STRUCT_FUNCTION);
    ADD_HL_BC;
    LD_E_hl;
    LD_D(0);
    LD_HL(mBattleBGEffects);
    ADD_HL_DE;
    ADD_HL_DE;
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    JP_hl;
}

// void BattleBGEffects(void) {
//     SET_PC(aBattleBGEffects);
//     //  entries correspond to ANIM_BG_* constants
//     // dw ['BattleBGEffect_End'];
//     // dw ['BattleBGEffect_FlashInverted'];
//     // dw ['BattleBGEffect_FlashWhite'];
//     // dw ['BattleBGEffect_WhiteHues'];
//     // dw ['BattleBGEffect_BlackHues'];
//     // dw ['BattleBGEffect_AlternateHues'];
//     // dw ['BattleBGEffect_CycleOBPalsGrayAndYellow'];
//     // dw ['BattleBGEffect_CycleMidOBPalsGrayAndYellow'];
//     // dw ['BattleBGEffect_CycleBGPals_Inverted'];
//     // dw ['BattleBGEffect_HideMon'];
//     // dw ['BattleBGEffect_ShowMon'];
//     // dw ['BattleBGEffect_EnterMon'];
//     // dw ['BattleBGEffect_ReturnMon'];
//     // dw ['BattleBGEffect_Surf'];
//     // dw ['BattleBGEffect_Whirlpool'];
//     // dw ['BattleBGEffect_Teleport'];
//     // dw ['BattleBGEffect_NightShade'];
//     // dw ['BattleBGEffect_BattlerObj_1Row'];
//     // dw ['BattleBGEffect_BattlerObj_2Row'];
//     // dw ['BattleBGEffect_DoubleTeam'];
//     // dw ['BattleBGEffect_AcidArmor'];
//     // dw ['BattleBGEffect_RapidFlash'];
//     // dw ['BattleBGEffect_FadeMonToLight'];
//     // dw ['BattleBGEffect_FadeMonToBlack'];
//     // dw ['BattleBGEffect_FadeMonToLightRepeating'];
//     // dw ['BattleBGEffect_FadeMonToBlackRepeating'];
//     // dw ['BattleBGEffect_CycleMonLightDarkRepeating'];
//     // dw ['BattleBGEffect_FlashMonRepeating'];
//     // dw ['BattleBGEffect_FadeMonsToBlackRepeating'];
//     // dw ['BattleBGEffect_FadeMonToWhiteWaitFadeBack'];
//     // dw ['BattleBGEffect_FadeMonFromWhite'];
//     // dw ['BattleBGEffect_ShakeScreenX'];
//     // dw ['BattleBGEffect_ShakeScreenY'];
//     // dw ['BattleBGEffect_Withdraw'];
//     // dw ['BattleBGEffect_BounceDown'];
//     // dw ['BattleBGEffect_Dig'];
//     // dw ['BattleBGEffect_Tackle'];
//     // dw ['BattleBGEffect_BodySlam'];
//     // dw ['BattleBGEffect_WobbleMon'];
//     // dw ['BattleBGEffect_RemoveMon'];
//     // dw ['BattleBGEffect_WaveDeformMon'];
//     // dw ['BattleBGEffect_Psychic'];
//     // dw ['BattleBGEffect_BetaSendOutMon1'];
//     // dw ['BattleBGEffect_BetaSendOutMon2'];
//     // dw ['BattleBGEffect_Flail'];
//     // dw ['BattleBGEffect_BetaPursuit'];
//     // dw ['BattleBGEffect_Rollout'];
//     // dw ['BattleBGEffect_VitalThrow'];
//     // dw ['BattleBGEffect_StartWater'];
//     // dw ['BattleBGEffect_Water'];
//     // dw ['BattleBGEffect_EndWater'];
//     // dw ['BattleBGEffect_VibrateMon'];
//     // dw ['BattleBGEffect_WobblePlayer'];
//     // dw ['BattleBGEffect_WobbleScreen'];

//     return BattleBGEffect_End();
// }

void(*const BattleBGEffects[])(void) = {
    BattleBGEffect_End,
    BattleBGEffect_FlashInverted,
    BattleBGEffect_FlashWhite,
    BattleBGEffect_WhiteHues,
    BattleBGEffect_BlackHues,
    BattleBGEffect_AlternateHues,
    BattleBGEffect_CycleOBPalsGrayAndYellow,
    BattleBGEffect_CycleMidOBPalsGrayAndYellow,
    BattleBGEffect_CycleBGPals_Inverted,
    BattleBGEffect_HideMon,
    BattleBGEffect_ShowMon,
    BattleBGEffect_EnterMon,
    BattleBGEffect_ReturnMon,
    BattleBGEffect_Surf,
    BattleBGEffect_Whirlpool,
    BattleBGEffect_Teleport,
    BattleBGEffect_NightShade,
    BattleBGEffect_BattlerObj_1Row,
    BattleBGEffect_BattlerObj_2Row,
    BattleBGEffect_DoubleTeam,
    BattleBGEffect_AcidArmor,
    BattleBGEffect_RapidFlash,
    BattleBGEffect_FadeMonToLight,
    BattleBGEffect_FadeMonToBlack,
    BattleBGEffect_FadeMonToLightRepeating,
    BattleBGEffect_FadeMonToBlackRepeating,
    BattleBGEffect_CycleMonLightDarkRepeating,
    BattleBGEffect_FlashMonRepeating,
    BattleBGEffect_FadeMonsToBlackRepeating,
    BattleBGEffect_FadeMonToWhiteWaitFadeBack,
    BattleBGEffect_FadeMonFromWhite,
    BattleBGEffect_ShakeScreenX,
    BattleBGEffect_ShakeScreenY,
    BattleBGEffect_Withdraw,
    BattleBGEffect_BounceDown,
    BattleBGEffect_Dig,
    BattleBGEffect_Tackle,
    BattleBGEffect_BodySlam,
    BattleBGEffect_WobbleMon,
    BattleBGEffect_RemoveMon,
    BattleBGEffect_WaveDeformMon,
    BattleBGEffect_Psychic,
    BattleBGEffect_BetaSendOutMon1,
    BattleBGEffect_BetaSendOutMon2,
    BattleBGEffect_Flail,
    BattleBGEffect_BetaPursuit,
    BattleBGEffect_Rollout,
    BattleBGEffect_VitalThrow,
    BattleBGEffect_StartWater,
    BattleBGEffect_Water,
    BattleBGEffect_EndWater,
    BattleBGEffect_VibrateMon,
    BattleBGEffect_WobblePlayer,
    BattleBGEffect_WobbleScreen,
};

void BattleBGEffect_End(void) {
    SET_PC(aBattleBGEffect_End);
    CALL(aEndBattleBGEffect);
    RET;
}

void BatttleBGEffects_GetNamedJumptablePointer(void) {
    SET_PC(aBatttleBGEffects_GetNamedJumptablePointer);
    LD_HL(BG_EFFECT_STRUCT_JT_INDEX);
    ADD_HL_BC;
    LD_L_hl;
    LD_H(0);
    ADD_HL_HL;
    ADD_HL_DE;
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    RET;
}

void BattleBGEffects_AnonJumptable(void) {
    SET_PC(aBattleBGEffects_AnonJumptable);
    POP_DE;
    LD_HL(BG_EFFECT_STRUCT_JT_INDEX);
    ADD_HL_BC;
    LD_L_hl;
    LD_H(0);
    ADD_HL_HL;
    ADD_HL_DE;
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    JP_hl;
}

void BattleBGEffects_IncAnonJumptableIndex(void) {
    SET_PC(aBattleBGEffects_IncAnonJumptableIndex);
    LD_HL(BG_EFFECT_STRUCT_JT_INDEX);
    ADD_HL_BC;
    INC_hl;
    RET;
}

void BattleBGEffect_FlashInverted(void) {
    SET_PC(aBattleBGEffect_FlashInverted);
    LD_DE(mBattleBGEffect_FlashInverted_inverted);
    JP(mBattleBGEffect_FlashContinue);

inverted:

    // dc ['3', '2', '1', '0']
    // dc ['0', '1', '2', '3']

    return BattleBGEffect_FlashWhite();
}

void BattleBGEffect_FlashWhite(void) {
    SET_PC(aBattleBGEffect_FlashWhite);
    LD_DE(mBattleBGEffect_FlashWhite_white);
    JP(mBattleBGEffect_FlashContinue);

white:

    // dc ['3', '2', '1', '0']
    // dc ['0', '0', '0', '0']

    return BattleBGEffect_FlashContinue();
}

void BattleBGEffect_FlashContinue(void) {
    SET_PC(aBattleBGEffect_FlashContinue);
    //  current timer, flash duration, number of flashes
    LD_A(0x1);
    LD_addr_A(wBattleBGEffectTempID);  // unused?
    LD_HL(BG_EFFECT_STRUCT_JT_INDEX);
    ADD_HL_BC;
    LD_A_hl;
    AND_A_A;
    IF_Z goto init;
    DEC_hl;
    RET;

init:

    LD_HL(BG_EFFECT_STRUCT_BATTLE_TURN);
    ADD_HL_BC;
    LD_A_hl;
    LD_HL(BG_EFFECT_STRUCT_JT_INDEX);
    ADD_HL_BC;
    LD_hl_A;
    LD_HL(BG_EFFECT_STRUCT_PARAM);
    ADD_HL_BC;
    LD_A_hl;
    AND_A_A;
    IF_NZ goto apply_pal;
    CALL(aEndBattleBGEffect);
    RET;

apply_pal:

    DEC_A;
    LD_hl_A;
    AND_A(1);
    LD_L_A;
    LD_H(0);
    ADD_HL_DE;
    LD_A_hl;
    LD_addr_A(wBGP);
    RET;
}

void BattleBGEffect_WhiteHues(void) {
    SET_PC(aBattleBGEffect_WhiteHues);
    LD_DE(mBattleBGEffect_WhiteHues_Pals);
    CALL(aBattleBGEffect_GetNthDMGPal);
    IF_C goto quit;
    LD_addr_A(wBGP);
    RET;

quit:

    CALL(aEndBattleBGEffect);
    RET;

Pals:

    // dc ['3', '2', '1', '0']
    // dc ['3', '2', '0', '0']
    // dc ['3', '1', '0', '0']
    // db ['-1'];

    return BattleBGEffect_BlackHues();
}

void BattleBGEffect_BlackHues(void) {
    SET_PC(aBattleBGEffect_BlackHues);
    LD_DE(mBattleBGEffect_BlackHues_Pals);
    CALL(aBattleBGEffect_GetNthDMGPal);
    IF_C goto quit;
    LD_addr_A(wBGP);
    RET;

quit:

    CALL(aEndBattleBGEffect);
    RET;

Pals:

    // dc ['3', '2', '1', '0']
    // dc ['3', '3', '1', '0']
    // dc ['3', '3', '2', '0']
    // db ['-1'];

    return BattleBGEffect_AlternateHues();
}

void BattleBGEffect_AlternateHues(void) {
    SET_PC(aBattleBGEffect_AlternateHues);
    LD_DE(mBattleBGEffect_AlternateHues_Pals);
    CALL(aBattleBGEffect_GetNthDMGPal);
    IF_C goto quit;
    LD_addr_A(wBGP);
    LD_addr_A(wOBP1);
    RET;

quit:

    CALL(aEndBattleBGEffect);
    RET;

Pals:

    // dc ['3', '2', '1', '0']
    // dc ['3', '3', '2', '0']
    // dc ['3', '3', '3', '0']
    // dc ['3', '3', '2', '0']
    // dc ['3', '2', '1', '0']
    // dc ['2', '1', '0', '0']
    // dc ['1', '0', '0', '0']
    // dc ['2', '1', '0', '0']
    // db ['-2'];

    return BattleBGEffect_CycleOBPalsGrayAndYellow();
}

void BattleBGEffect_CycleOBPalsGrayAndYellow(void) {
    SET_PC(aBattleBGEffect_CycleOBPalsGrayAndYellow);
    CALL(aBattleBGEffects_CheckSGB);
    IF_NZ goto sgb;
    LD_DE(mBattleBGEffect_CycleOBPalsGrayAndYellow_PalsCGB);
    goto okay;

sgb:

    LD_DE(mBattleBGEffect_CycleOBPalsGrayAndYellow_PalsSGB);

okay:

    CALL(aBattleBGEffect_GetNthDMGPal);
    LD_addr_A(wOBP0);
    RET;

PalsCGB:

    // dc ['3', '2', '1', '0']
    // dc ['2', '1', '0', '0']
    // db ['-2'];

PalsSGB:

    // dc ['3', '3', '0', '0']
    // dc ['3', '0', '0', '0']
    // db ['-2'];

    return BattleBGEffect_CycleMidOBPalsGrayAndYellow();
}

void BattleBGEffect_CycleMidOBPalsGrayAndYellow(void) {
    SET_PC(aBattleBGEffect_CycleMidOBPalsGrayAndYellow);
    CALL(aBattleBGEffects_CheckSGB);
    IF_NZ goto sgb;
    LD_DE(mBattleBGEffect_CycleMidOBPalsGrayAndYellow_PalsCGB);
    goto okay;

sgb:

    LD_DE(mBattleBGEffect_CycleMidOBPalsGrayAndYellow_PalsSGB);

okay:

    CALL(aBattleBGEffect_GetNthDMGPal);
    LD_addr_A(wOBP0);
    RET;

PalsCGB:

    // dc ['3', '2', '1', '0']
    // dc ['3', '1', '2', '0']
    // db ['-2'];

PalsSGB:

    // dc ['3', '3', '0', '0']
    // dc ['3', '0', '3', '0']
    // db ['-2'];

    return BattleBGEffect_CycleBGPals_Inverted();
}

void BattleBGEffect_CycleBGPals_Inverted(void) {
    SET_PC(aBattleBGEffect_CycleBGPals_Inverted);
    LD_DE(mBattleBGEffect_CycleBGPals_Inverted_Pals);
    CALL(aBattleBGEffect_GetNthDMGPal);
    LD_addr_A(wBGP);
    RET;

Pals:

    // dc ['0', '1', '2', '3']
    // dc ['1', '2', '0', '3']
    // dc ['2', '0', '1', '3']
    // db ['-2'];

    return BattleBGEffect_HideMon();
}

void BattleBGEffect_HideMon(void) {
    SET_PC(aBattleBGEffect_HideMon);
    // CALL(aBattleBGEffects_AnonJumptable);

anon_dw:

    if (REG_BC == 0) goto zero;
    if (REG_BC == 1) return BattleBGEffects_IncAnonJumptableIndex();
    if (REG_BC == 2) return BattleBGEffects_IncAnonJumptableIndex();
    if (REG_BC == 3) return BattleBGEffects_IncAnonJumptableIndex();
    if (REG_BC == 4) goto four;

zero:

    CALL(aBattleBGEffects_IncAnonJumptableIndex);
    PUSH_BC;
    CALL(aBGEffect_CheckBattleTurn);
    IF_NZ goto player_side;
    hlcoord(12, 0, wTilemap);
    LD_BC((7 << 8) | 7);
    goto got_pointer;

player_side:

    hlcoord(2, 6, wTilemap);
    LD_BC((6 << 8) | 6);

got_pointer:

    CALL(aClearBox);
    POP_BC;
    XOR_A_A;
    LDH_addr_A(hBGMapThird);
    LD_A(0x1);
    LDH_addr_A(hBGMapMode);
    RET;

four:

    XOR_A_A;
    LDH_addr_A(hBGMapMode);
    CALL(aEndBattleBGEffect);
    RET;
}

void BattleBGEffect_ShowMon(void) {
    SET_PC(aBattleBGEffect_ShowMon);
    CALL(aBGEffect_CheckFlyDigStatus);
    IF_Z goto not_flying;
    CALL(aEndBattleBGEffect);
    RET;

not_flying:

    CALL(aBGEffect_CheckBattleTurn);
    IF_NZ goto player_side;
    LD_DE(mBattleBGEffect_ShowMon_EnemyData);
    goto got_pointer;

player_side:

    LD_DE(mBattleBGEffect_ShowMon_PlayerData);

got_pointer:

    LD_A_E;
    LD_addr_A(wBattlePicResizeTempPointer);
    LD_A_D;
    LD_addr_A(wBattlePicResizeTempPointer + 1);
    CALL(aBattleBGEffect_RunPicResizeScript);
    RET;

PlayerData:

    // db ['0', '0x31', '0'];
    // db ['-1'];

EnemyData:

    // db ['3', '0x00', '3'];
    // db ['-1'];

    return BattleBGEffect_BattlerObj_1Row();
}

void BattleBGEffect_BattlerObj_1Row(void) {
    SET_PC(aBattleBGEffect_BattlerObj_1Row);
    // CALL(aBattleBGEffects_AnonJumptable);

anon_dw:

    if (REG_BC == 0) goto zero;
    if (REG_BC == 1) goto one;
    if (REG_BC == 2) return BattleBGEffects_IncAnonJumptableIndex();
    if (REG_BC == 3) return BattleBGEffects_IncAnonJumptableIndex();
    if (REG_BC == 4) return BattleBGEffects_IncAnonJumptableIndex();
    if (REG_BC == 5) goto five;

zero:

    CALL(aBGEffect_CheckFlyDigStatus);
    IF_Z goto not_flying_digging;
    LD_HL(wLastAnimObjectIndex);
    INC_hl;
    CALL(aEndBattleBGEffect);
    RET;

not_flying_digging:

    CALL(aBattleBGEffects_IncAnonJumptableIndex);
    PUSH_BC;
    CALL(aBGEffect_CheckBattleTurn);
    IF_NZ goto player_side;
    LD_A(ANIM_OBJ_ENEMYFEET_1ROW);
    LD_addr_A(wBattleObjectTempID);
    LD_A(16 * TILE_WIDTH + 4);
    goto okay;

player_side:

    LD_A(ANIM_OBJ_PLAYERHEAD_1ROW);
    LD_addr_A(wBattleObjectTempID);
    LD_A(6 * TILE_WIDTH);

okay:

    LD_addr_A(wBattleObjectTempXCoord);
    LD_A(8 * TILE_WIDTH);
    LD_addr_A(wBattleObjectTempYCoord);
    XOR_A_A;
    LD_addr_A(wBattleObjectTempParam);
    CALL(av_QueueBattleAnimation);
    POP_BC;
    RET;

one:

    CALL(aBattleBGEffects_IncAnonJumptableIndex);
    PUSH_BC;
    CALL(aBGEffect_CheckBattleTurn);
    IF_NZ goto player_side_2;
    hlcoord(12, 6, wTilemap);
    LD_BC((1 << 8) | 7);
    goto okay2;

player_side_2:

    hlcoord(2, 6, wTilemap);
    LD_BC((1 << 8) | 6);

okay2:

    CALL(aClearBox);
    LD_A(0x1);
    LDH_addr_A(hBGMapMode);
    POP_BC;
    RET;

five:

    XOR_A_A;
    LDH_addr_A(hBGMapMode);
    CALL(aEndBattleBGEffect);
    RET;
}

void BattleBGEffect_BattlerObj_2Row(void) {
    SET_PC(aBattleBGEffect_BattlerObj_2Row);
    // CALL(aBattleBGEffects_AnonJumptable);

anon_dw:

    if (REG_BC == 0) goto zero;
    if (REG_BC == 1) goto one;
    if (REG_BC == 2) return BattleBGEffects_IncAnonJumptableIndex();
    if (REG_BC == 3) return BattleBGEffects_IncAnonJumptableIndex();
    if (REG_BC == 4) return BattleBGEffects_IncAnonJumptableIndex();
    if (REG_BC == 5) goto five;

zero:

    CALL(aBGEffect_CheckFlyDigStatus);
    IF_Z goto not_flying_digging;
    LD_HL(wLastAnimObjectIndex);
    INC_hl;
    CALL(aEndBattleBGEffect);
    RET;

not_flying_digging:

    CALL(aBattleBGEffects_IncAnonJumptableIndex);
    PUSH_BC;
    CALL(aBGEffect_CheckBattleTurn);
    IF_NZ goto player_side;
    LD_A(ANIM_OBJ_ENEMYFEET_2ROW);
    LD_addr_A(wBattleObjectTempID);
    LD_A(16 * TILE_WIDTH + 4);
    goto okay;

player_side:

    LD_A(ANIM_OBJ_PLAYERHEAD_2ROW);
    LD_addr_A(wBattleObjectTempID);
    LD_A(6 * TILE_WIDTH);

okay:

    LD_addr_A(wBattleObjectTempXCoord);
    LD_A(8 * TILE_WIDTH);
    LD_addr_A(wBattleObjectTempYCoord);
    XOR_A_A;
    LD_addr_A(wBattleObjectTempParam);
    CALL(av_QueueBattleAnimation);
    POP_BC;
    RET;

one:

    CALL(aBattleBGEffects_IncAnonJumptableIndex);
    PUSH_BC;
    CALL(aBGEffect_CheckBattleTurn);
    IF_NZ goto player_side_2;
    hlcoord(12, 5, wTilemap);
    LD_BC((2 << 8) | 7);
    goto okay2;

player_side_2:

    hlcoord(2, 6, wTilemap);
    LD_BC((2 << 8) | 6);

okay2:

    CALL(aClearBox);
    LD_A(0x1);
    LDH_addr_A(hBGMapMode);
    POP_BC;
    RET;

five:

    XOR_A_A;
    LDH_addr_A(hBGMapMode);
    CALL(aEndBattleBGEffect);
    RET;
}

void v_QueueBattleAnimation(void) {
    SET_PC(av_QueueBattleAnimation);
    CALLFAR(aQueueBattleAnimation);
    RET;
}

void BattleBGEffect_RemoveMon(void) {
    SET_PC(aBattleBGEffect_RemoveMon);
    //  Slides mon out of screen
    // CALL(aBattleBGEffects_AnonJumptable);

anon_dw:

    if (REG_BC == 0) goto zero;
    if (REG_BC == 1) goto one;
    if (REG_BC == 2) return BattleBGEffects_IncAnonJumptableIndex();
    if (REG_BC == 3) return BattleBGEffects_IncAnonJumptableIndex();
    if (REG_BC == 4) goto four;

zero:

    CALL(aBattleBGEffects_IncAnonJumptableIndex);
    CALL(aBGEffect_CheckBattleTurn);
    LD_hl_A;
    LD_HL(BG_EFFECT_STRUCT_BATTLE_TURN);
    ADD_HL_BC;
    LD_A_hl;
    AND_A_A;
    IF_Z goto user;
    LD_A(0x9);
    goto okay;

user:

    LD_A(0x8);

okay:

    LD_HL(BG_EFFECT_STRUCT_PARAM);
    ADD_HL_BC;
    LD_hl_A;
    RET;

one:

    LD_HL(BG_EFFECT_STRUCT_BATTLE_TURN);
    ADD_HL_BC;
    LD_A_hl;
    AND_A_A;
    IF_Z goto user_2;
    hlcoord(0, 6, wTilemap);
    LD_DE((8 << 8) | 6);

row1:

    PUSH_DE;
    PUSH_HL;

col1:

    INC_HL;
    LD_A_hld;
    LD_hli_A;
    DEC_D;
    IF_NZ goto col1;
    POP_HL;
    LD_DE(SCREEN_WIDTH);
    ADD_HL_DE;
    POP_DE;
    DEC_E;
    IF_NZ goto row1;
    goto okay2;

user_2:

    hlcoord(19, 0, wTilemap);
    LD_DE((8 << 8) | 7);

row2:

    PUSH_DE;
    PUSH_HL;

col2:

    DEC_HL;
    LD_A_hli;
    LD_hld_A;
    DEC_D;
    IF_NZ goto col2;
    POP_HL;
    LD_DE(SCREEN_WIDTH);
    ADD_HL_DE;
    POP_DE;
    DEC_E;
    IF_NZ goto row2;

okay2:

    XOR_A_A;
    LDH_addr_A(hBGMapThird);
    LD_A(0x1);
    LDH_addr_A(hBGMapMode);
    CALL(aBattleBGEffects_IncAnonJumptableIndex);
    LD_HL(BG_EFFECT_STRUCT_PARAM);
    ADD_HL_BC;
    DEC_hl;
    RET;

four:

    XOR_A_A;
    LDH_addr_A(hBGMapMode);
    LD_HL(BG_EFFECT_STRUCT_PARAM);
    ADD_HL_BC;
    LD_A_hl;
    AND_A_A;
    IF_Z goto done;
    LD_HL(BG_EFFECT_STRUCT_JT_INDEX);
    ADD_HL_BC;
    LD_hl(0x1);
    RET;

done:

    CALL(aEndBattleBGEffect);
    RET;
}

void BattleBGEffect_EnterMon(void) {
    SET_PC(aBattleBGEffect_EnterMon);
    CALL(aBGEffect_CheckBattleTurn);
    IF_NZ goto player_turn;
    LD_DE(mBattleBGEffect_EnterMon_EnemyData);
    goto okay;

player_turn:

    LD_DE(mBattleBGEffect_EnterMon_PlayerData);

okay:

    LD_A_E;
    LD_addr_A(wBattlePicResizeTempPointer);
    LD_A_D;
    LD_addr_A(wBattlePicResizeTempPointer + 1);
    CALL(aBattleBGEffect_RunPicResizeScript);
    RET;

PlayerData:

    // db ['2', '0x31', '2'];
    // db ['1', '0x31', '1'];
    // db ['0', '0x31', '0'];
    // db ['-1'];

EnemyData:

    // db ['5', '0x00', '5'];
    // db ['4', '0x00', '4'];
    // db ['3', '0x00', '3'];
    // db ['-1'];

    return BattleBGEffect_ReturnMon();
}

void BattleBGEffect_ReturnMon(void) {
    SET_PC(aBattleBGEffect_ReturnMon);
    CALL(aBGEffect_CheckBattleTurn);
    IF_NZ goto player_turn;
    LD_DE(mBattleBGEffect_ReturnMon_EnemyData);
    goto okay;

player_turn:

    LD_DE(mBattleBGEffect_ReturnMon_PlayerData);

okay:

    LD_A_E;
    LD_addr_A(wBattlePicResizeTempPointer);
    LD_A_D;
    LD_addr_A(wBattlePicResizeTempPointer + 1);
    CALL(aBattleBGEffect_RunPicResizeScript);
    RET;

PlayerData:

    // db ['0', '0x31', '0'];
    // db ['-2', '0x66', '0'];
    // db ['1', '0x31', '1'];
    // db ['-2', '0x44', '1'];
    // db ['2', '0x31', '2'];
    // db ['-2', '0x22', '2'];
    // db ['-3', '0x00', '0'];
    // db ['-1'];

EnemyData:

    // db ['3', '0x00', '3'];
    // db ['-2', '0x77', '3'];
    // db ['4', '0x00', '4'];
    // db ['-2', '0x55', '4'];
    // db ['5', '0x00', '5'];
    // db ['-2', '0x33', '5'];
    // db ['-3', '0x00', '0'];
    // db ['-1'];

    return BattleBGEffect_RunPicResizeScript();
}

void BattleBGEffect_RunPicResizeScript(void) {
    SET_PC(aBattleBGEffect_RunPicResizeScript);
    // CALL(aBattleBGEffects_AnonJumptable);

anon_dw:

    if (REG_BC == 0) goto zero;
    if (REG_BC == 1) return BattleBGEffects_IncAnonJumptableIndex();
    if (REG_BC == 2) return BattleBGEffects_IncAnonJumptableIndex();
    if (REG_BC == 3) goto restart;
    if (REG_BC == 4) goto end;

zero:

    LD_HL(BG_EFFECT_STRUCT_PARAM);
    ADD_HL_BC;
    LD_E_hl;
    LD_D(0x0);
    INC_hl;
    LD_A_addr(wBattlePicResizeTempPointer);
    LD_L_A;
    LD_A_addr(wBattlePicResizeTempPointer + 1);
    LD_H_A;
    ADD_HL_DE;
    ADD_HL_DE;
    ADD_HL_DE;
    LD_A_hl;
    CP_A(-1);
    IF_Z goto end;
    CP_A(-2);
    IF_Z goto clear;
    CP_A(-3);
    IF_Z goto skip;
    CALL(aBattleBGEffect_RunPicResizeScript_PlaceGraphic);

skip:

    CALL(aBattleBGEffects_IncAnonJumptableIndex);
    LD_A(0x1);
    LDH_addr_A(hBGMapMode);
    RET;

clear:

    CALL(aBattleBGEffect_RunPicResizeScript_ClearBox);
    goto zero;

restart:

    XOR_A_A;
    LDH_addr_A(hBGMapMode);
    LD_HL(BG_EFFECT_STRUCT_JT_INDEX);
    ADD_HL_BC;
    LD_hl(0x0);
    RET;

end:

    XOR_A_A;
    LDH_addr_A(hBGMapMode);
    CALL(aEndBattleBGEffect);
    RET;

ClearBox:

    //  get dims
    PUSH_BC;
    INC_HL;
    LD_A_hli;
    LD_B_A;
    AND_A(0xf);
    LD_C_A;
    LD_A_B;
    SWAP_A;
    AND_A(0xf);
    LD_B_A;
    //  get coords
    LD_E_hl;
    LD_D(0);
    LD_HL(mBattleBGEffect_RunPicResizeScript_Coords);
    ADD_HL_DE;
    ADD_HL_DE;
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    CALL(aClearBox);
    POP_BC;
    RET;

PlaceGraphic:

    //  get dims
    PUSH_BC;
    PUSH_HL;
    LD_E_hl;
    LD_D(0);
    LD_HL(mBattleBGEffect_RunPicResizeScript_BGSquares);
    ADD_HL_DE;
    ADD_HL_DE;
    ADD_HL_DE;
    LD_A_hli;
    LD_B_A;
    AND_A(0xf);
    LD_C_A;
    LD_A_B;
    SWAP_A;
    AND_A(0xf);
    LD_B_A;
    //  store pointer
    LD_E_hl;
    INC_HL;
    LD_D_hl;
    //  get byte
    POP_HL;
    INC_HL;
    LD_A_hli;
    LD_addr_A(wBattlePicResizeTempBaseTileID);
    //  get coord
    PUSH_DE;
    LD_E_hl;
    LD_D(0);
    LD_HL(mBattleBGEffect_RunPicResizeScript_Coords);
    ADD_HL_DE;
    ADD_HL_DE;
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    POP_DE;
    //  fill box

row:

    PUSH_BC;
    PUSH_HL;
    LD_A_addr(wBattlePicResizeTempBaseTileID);
    LD_B_A;

col:

    LD_A_de;
    ADD_A_B;
    LD_hli_A;
    INC_DE;
    DEC_C;
    IF_NZ goto col;
    POP_HL;
    LD_BC(SCREEN_WIDTH);
    ADD_HL_BC;
    POP_BC;
    DEC_B;
    IF_NZ goto row;
    POP_BC;
    RET;

Coords:

    // dwcoord ['2', '6'];
    // dwcoord ['3', '8'];
    // dwcoord ['4', '10'];
    // dwcoord ['12', '0'];
    // dwcoord ['13', '2'];
    // dwcoord ['14', '4'];

BGSquares:

    // bgsquare: MACRO
    //     dn \1, \2
    //     dw \3
    // ENDM

    // bgsquare ['6', '6', '.SixBySix']
    // bgsquare ['4', '4', '.FourByFour']
    // bgsquare ['2', '2', '.TwoByTwo']
    // bgsquare ['7', '7', '.SevenBySeven']
    // bgsquare ['5', '5', '.FiveByFive']
    // bgsquare ['3', '3', '.ThreeByThree']

SixBySix:

    // db ['0x00', '0x06', '0x0c', '0x12', '0x18', '0x1e'];
    // db ['0x01', '0x07', '0x0d', '0x13', '0x19', '0x1f'];
    // db ['0x02', '0x08', '0x0e', '0x14', '0x1a', '0x20'];
    // db ['0x03', '0x09', '0x0f', '0x15', '0x1b', '0x21'];
    // db ['0x04', '0x0a', '0x10', '0x16', '0x1c', '0x22'];
    // db ['0x05', '0x0b', '0x11', '0x17', '0x1d', '0x23'];

FourByFour:

    // db ['0x00', '0x0c', '0x12', '0x1e'];
    // db ['0x02', '0x0e', '0x14', '0x20'];
    // db ['0x03', '0x0f', '0x15', '0x21'];
    // db ['0x05', '0x11', '0x17', '0x23'];

TwoByTwo:

    // db ['0x00', '0x1e'];
    // db ['0x05', '0x23'];

SevenBySeven:

    // db ['0x00', '0x07', '0x0e', '0x15', '0x1c', '0x23', '0x2a'];
    // db ['0x01', '0x08', '0x0f', '0x16', '0x1d', '0x24', '0x2b'];
    // db ['0x02', '0x09', '0x10', '0x17', '0x1e', '0x25', '0x2c'];
    // db ['0x03', '0x0a', '0x11', '0x18', '0x1f', '0x26', '0x2d'];
    // db ['0x04', '0x0b', '0x12', '0x19', '0x20', '0x27', '0x2e'];
    // db ['0x05', '0x0c', '0x13', '0x1a', '0x21', '0x28', '0x2f'];
    // db ['0x06', '0x0d', '0x14', '0x1b', '0x22', '0x29', '0x30'];

FiveByFive:

    // db ['0x00', '0x07', '0x15', '0x23', '0x2a'];
    // db ['0x01', '0x08', '0x16', '0x24', '0x2b'];
    // db ['0x03', '0x0a', '0x18', '0x26', '0x2d'];
    // db ['0x05', '0x0c', '0x1a', '0x28', '0x2f'];
    // db ['0x06', '0x0d', '0x1b', '0x29', '0x30'];

ThreeByThree:

    // db ['0x00', '0x15', '0x2a'];
    // db ['0x03', '0x18', '0x2d'];
    // db ['0x06', '0x1b', '0x30'];

    return BattleBGEffect_Surf();
}

void BattleBGEffect_Surf(void) {
    SET_PC(aBattleBGEffect_Surf);
    // CALL(aBattleBGEffects_AnonJumptable);

anon_dw:

    if (REG_BC == 0) goto zero;
    if (REG_BC == 1) goto one;
    if (REG_BC == 2) goto two;

zero:

    CALL(aBattleBGEffects_IncAnonJumptableIndex);
    LD_DE((2 << 8) | 2);
    CALL(aInitSurfWaves);

one:

    LDH_A_addr(hLCDCPointer);
    AND_A_A;
    RET_Z;
    PUSH_BC;
    CALL(aBattleBGEffect_Surf_RotatewSurfWaveBGEffect);
    POP_BC;
    RET;

two:

    CALL(aBattleAnim_ResetLCDStatCustom);
    RET;

RotatewSurfWaveBGEffect:

    LD_HL(wSurfWaveBGEffect);
    LD_DE(wSurfWaveBGEffect + 1);
    LD_C(wSurfWaveBGEffectEnd - wSurfWaveBGEffect - 1);
    LD_A_hl;
    PUSH_AF;

loop:

    LD_A_de;
    INC_DE;
    LD_hli_A;
    DEC_C;
    IF_NZ goto loop;
    POP_AF;
    LD_hl_A;
    LD_DE(wLYOverridesBackup);
    LD_HL(wSurfWaveBGEffect);
    LD_BC(0x0);

loop2:

    LDH_A_addr(hLYOverrideStart);
    CP_A_E;
    IF_NC goto load_zero;
    PUSH_HL;
    ADD_HL_BC;
    LD_A_hl;
    POP_HL;
    goto okay;

load_zero:

    XOR_A_A;

okay:

    LD_de_A;
    LD_A_C;
    INC_A;
    AND_A(0x3f);
    LD_C_A;
    INC_DE;
    LD_A_E;
    CP_A(0x5f);
    IF_C goto loop2;
    RET;
}

void BattleBGEffect_Whirlpool(void) {
    SET_PC(aBattleBGEffect_Whirlpool);
    // CALL(aBattleBGEffects_AnonJumptable);

anon_dw:

    if (REG_BC == 0) goto zero;
    if (REG_BC == 1) goto one;
    if (REG_BC == 2) goto two;

zero:

    CALL(aBattleBGEffects_IncAnonJumptableIndex);
    CALL(aBattleBGEffects_ClearLYOverrides);
    LD_A(LOW(rSCY));
    LDH_addr_A(hLCDCPointer);
    XOR_A_A;
    LDH_addr_A(hLYOverrideStart);
    LD_A(0x5e);
    LDH_addr_A(hLYOverrideEnd);
    LD_DE((2 << 8) | 2);
    CALL(aDeformScreen);
    RET;

one:

    CALL(aBattleBGEffect_WavyScreenFX);
    RET;

two:

    CALL(aBattleAnim_ResetLCDStatCustom);
    RET;
}

void BattleBGEffect_StartWater(void) {
    SET_PC(aBattleBGEffect_StartWater);
    CALL(aBattleBGEffects_ClearLYOverrides);
    LD_A(LOW(rSCY));
    CALL(aBattleBGEffect_SetLCDStatCustoms1);
    CALL(aEndBattleBGEffect);
    RET;
}

void BattleBGEffect_Water(void) {
    SET_PC(aBattleBGEffect_Water);
    //  BG_EFFECT_STRUCT_JT_INDEX: defines Y position of deformation
    LD_HL(BG_EFFECT_STRUCT_PARAM);
    ADD_HL_BC;
    LD_A_hl;
    LD_E_A;
    ADD_A(0x4);
    LD_hl_A;
    LD_HL(BG_EFFECT_STRUCT_BATTLE_TURN);
    ADD_HL_BC;
    LD_A_hl;
    AND_A(0xf0);
    SWAP_A;
    XOR_A(0xff);
    ADD_A(0x4);
    LD_D_A;
    LD_HL(BG_EFFECT_STRUCT_JT_INDEX);
    ADD_HL_BC;
    LD_A_hl;
    LD_addr_A(wBattleSineWaveTempProgress);
    LD_HL(BG_EFFECT_STRUCT_BATTLE_TURN);
    ADD_HL_BC;
    LD_A_hl;
    CP_A(0x20);
    IF_NC goto done;
    INC_hl;
    INC_hl;
    CALL(aDeformWater);
    RET;

done:

    CALL(aBattleBGEffects_ClearLYOverrides);
    CALL(aEndBattleBGEffect);
    RET;
}

void BattleBGEffect_EndWater(void) {
    SET_PC(aBattleBGEffect_EndWater);
    CALL(aBattleAnim_ResetLCDStatCustom);
    RET;
}

void BattleBGEffect_Psychic(void) {
    SET_PC(aBattleBGEffect_Psychic);
    //  Hardcoded to always affect opponent
    // CALL(aBattleBGEffects_AnonJumptable);

anon_dw:

    if (REG_BC == 0) goto zero;
    if (REG_BC == 1) goto one;
    if (REG_BC == 2) goto two;

zero:

    CALL(aBattleBGEffects_IncAnonJumptableIndex);
    CALL(aBattleBGEffects_ClearLYOverrides);
    LD_A(LOW(rSCX));
    LDH_addr_A(hLCDCPointer);
    XOR_A_A;
    LDH_addr_A(hLYOverrideStart);
    LD_A(0x5f);
    LDH_addr_A(hLYOverrideEnd);
    LD_DE((6 << 8) | 5);
    CALL(aDeformScreen);
    LD_HL(BG_EFFECT_STRUCT_PARAM);
    ADD_HL_BC;
    LD_hl(0x0);
    RET;

one:

    LD_HL(BG_EFFECT_STRUCT_PARAM);
    ADD_HL_BC;
    LD_A_hl;
    INC_hl;
    AND_A(0x3);
    RET_NZ;
    CALL(aBattleBGEffect_WavyScreenFX);
    RET;

two:

    CALL(aBattleAnim_ResetLCDStatCustom);
    RET;
}

void BattleBGEffect_Teleport(void) {
    SET_PC(aBattleBGEffect_Teleport);
    // CALL(aBattleBGEffects_AnonJumptable);

anon_dw:

    if (REG_BC == 0) goto zero;
    if (REG_BC == 1) goto one;
    if (REG_BC == 2) goto two;

zero:

    CALL(aBattleBGEffects_IncAnonJumptableIndex);
    CALL(aBattleBGEffects_ClearLYOverrides);
    LD_A(LOW(rSCX));
    CALL(aBattleBGEffect_SetLCDStatCustoms1);
    LD_DE((6 << 8) | 5);
    CALL(aDeformScreen);
    RET;

one:

    CALL(aBattleBGEffect_WavyScreenFX);
    RET;

two:

    CALL(aBattleAnim_ResetLCDStatCustom);
    RET;
}

void BattleBGEffect_NightShade(void) {
    SET_PC(aBattleBGEffect_NightShade);
    // CALL(aBattleBGEffects_AnonJumptable);

anon_dw:

    if (REG_BC == 0) goto zero;
    if (REG_BC == 1) goto one;
    if (REG_BC == 2) goto two;

zero:

    CALL(aBattleBGEffects_IncAnonJumptableIndex);
    CALL(aBattleBGEffects_ClearLYOverrides);
    LD_A(LOW(rSCY));
    CALL(aBattleBGEffect_SetLCDStatCustoms1);
    LD_HL(BG_EFFECT_STRUCT_PARAM);
    ADD_HL_BC;
    LD_E_hl;
    LD_D(2);
    CALL(aDeformScreen);
    RET;

one:

    CALL(aBattleBGEffect_WavyScreenFX);
    RET;

two:

    CALL(aBattleAnim_ResetLCDStatCustom);
    RET;
}

void BattleBGEffect_DoubleTeam(void) {
    SET_PC(aBattleBGEffect_DoubleTeam);
    // CALL(aBattleBGEffects_AnonJumptable);

anon_dw:

    if (REG_BC == 0) goto zero;
    if (REG_BC == 1) goto one;
    if (REG_BC == 2) goto two;
    if (REG_BC == 3) goto three;
    if (REG_BC == 4) goto four;
    if (REG_BC == 5) goto five;

zero:

    CALL(aBattleBGEffects_IncAnonJumptableIndex);
    CALL(aBattleBGEffects_ClearLYOverrides);
    LD_A(LOW(rSCX));
    CALL(aBattleBGEffect_SetLCDStatCustoms1);
    LDH_A_addr(hLYOverrideEnd);
    INC_A;
    LDH_addr_A(hLYOverrideEnd);
    LD_HL(BG_EFFECT_STRUCT_BATTLE_TURN);
    ADD_HL_BC;
    LD_hl(0x0);
    RET;

one:

    LD_HL(BG_EFFECT_STRUCT_PARAM);
    ADD_HL_BC;
    LD_A_hl;
    CP_A(0x10);
    IF_NC goto next;
    INC_hl;
    CALL(aBattleBGEffect_DoubleTeam_UpdateLYOverrides);
    RET;

three:

    LD_HL(BG_EFFECT_STRUCT_PARAM);
    ADD_HL_BC;
    LD_A_hl;
    CP_A(0xff);
    IF_Z goto next;
    DEC_hl;
    CALL(aBattleBGEffect_DoubleTeam_UpdateLYOverrides);
    RET;

next:

    CALL(aBattleBGEffects_IncAnonJumptableIndex);
    RET;

two:

    LD_HL(BG_EFFECT_STRUCT_BATTLE_TURN);
    ADD_HL_BC;
    LD_A_hl;
    LD_D(0x2);
    CALL(aBattleBGEffects_Sine);
    LD_HL(BG_EFFECT_STRUCT_PARAM);
    ADD_HL_BC;
    ADD_A_hl;
    CALL(aBattleBGEffect_DoubleTeam_UpdateLYOverrides);
    LD_HL(BG_EFFECT_STRUCT_BATTLE_TURN);
    ADD_HL_BC;
    LD_A_hl;
    ADD_A(0x4);
    LD_hl_A;

four:

    RET;

UpdateLYOverrides:

    LD_E_A;
    XOR_A(0xff);
    INC_A;
    LD_D_A;
    LD_H(HIGH(wLYOverridesBackup));
    LDH_A_addr(hLYOverrideStart);
    LD_L_A;
    LDH_A_addr(hLYOverrideEnd);
    SUB_A_L;
    SRL_A;
    PUSH_AF;

loop:

    LD_hl_E;
    INC_HL;
    LD_hl_D;
    INC_HL;
    DEC_A;
    IF_NZ goto loop;
    POP_AF;
    RET_NC;
    LD_hl_E;
    RET;

five:

    CALL(aBattleAnim_ResetLCDStatCustom);
    RET;
}

void BattleBGEffect_AcidArmor(void) {
    SET_PC(aBattleBGEffect_AcidArmor);
    // CALL(aBattleBGEffects_AnonJumptable);

anon_dw:

    if (REG_BC == 0) goto zero;
    if (REG_BC == 1) goto one;
    if (REG_BC == 2) goto two;

zero:

    CALL(aBattleBGEffects_IncAnonJumptableIndex);
    CALL(aBattleBGEffects_ClearLYOverrides);
    LD_A(LOW(rSCY));
    CALL(aBattleBGEffect_SetLCDStatCustoms1);
    LD_HL(BG_EFFECT_STRUCT_PARAM);
    ADD_HL_BC;
    LD_E_hl;
    LD_D(2);
    CALL(aDeformScreen);
    LD_H(HIGH(wLYOverridesBackup));
    LDH_A_addr(hLYOverrideEnd);
    LD_L_A;
    LD_hl(0x0);
    DEC_L;
    LD_hl(0x0);
    RET;

one:

    LDH_A_addr(hLYOverrideEnd);
    LD_L_A;
    LD_H(HIGH(wLYOverridesBackup));
    LD_E_L;
    LD_D_H;
    DEC_DE;

loop:

    LD_A_de;
    DEC_DE;
    LD_hld_A;
    LDH_A_addr(hLYOverrideStart);
    CP_A_L;
    IF_NZ goto loop;
    LD_hl(0x90);
    LDH_A_addr(hLYOverrideEnd);
    LD_L_A;
    LD_A_hl;
    CP_A(0x1);
    IF_C goto okay;
    CP_A(0x90);
    IF_Z goto okay;
    LD_hl(0x0);

okay:

    DEC_L;
    LD_A_hl;
    CP_A(0x2);
    RET_C;
    CP_A(0x90);
    RET_Z;
    LD_hl(0x0);
    RET;

two:

    CALL(aBattleAnim_ResetLCDStatCustom);
    RET;
}

void BattleBGEffect_Withdraw(void) {
    SET_PC(aBattleBGEffect_Withdraw);
    // CALL(aBattleBGEffects_AnonJumptable);

anon_dw:

    if (REG_BC == 0) goto zero;
    if (REG_BC == 1) goto one;
    if (REG_BC == 2) goto two;

zero:

    CALL(aBattleBGEffects_IncAnonJumptableIndex);
    CALL(aBattleBGEffects_ClearLYOverrides);
    LD_A(LOW(rSCY));
    CALL(aBattleBGEffect_SetLCDStatCustoms1);
    LDH_A_addr(hLYOverrideEnd);
    INC_A;
    LDH_addr_A(hLYOverrideEnd);
    LD_HL(BG_EFFECT_STRUCT_BATTLE_TURN);
    ADD_HL_BC;
    LD_hl(0x1);
    RET;

one:

    LD_HL(BG_EFFECT_STRUCT_PARAM);
    ADD_HL_BC;
    LD_A_hl;
    AND_A(0x3f);
    LD_D_A;
    LD_HL(BG_EFFECT_STRUCT_BATTLE_TURN);
    ADD_HL_BC;
    LD_A_hl;
    CP_A_D;
    RET_NC;
    CALL(aBGEffect_DisplaceLYOverridesBackup);
    LD_HL(BG_EFFECT_STRUCT_PARAM);
    ADD_HL_BC;
    LD_A_hl;
    RLCA;
    RLCA;
    AND_A(0x3);
    LD_HL(BG_EFFECT_STRUCT_BATTLE_TURN);
    ADD_HL_BC;
    ADD_A_hl;
    LD_hl_A;
    RET;

two:

    CALL(aBattleAnim_ResetLCDStatCustom);
    RET;
}

void BattleBGEffect_Dig(void) {
    SET_PC(aBattleBGEffect_Dig);
    // CALL(aBattleBGEffects_AnonJumptable);

anon_dw:

    if (REG_BC == 0) goto zero;
    if (REG_BC == 1) goto one;
    if (REG_BC == 2) goto two;
    if (REG_BC == 3) goto three;

zero:

    CALL(aBattleBGEffects_IncAnonJumptableIndex);
    CALL(aBattleBGEffects_ClearLYOverrides);
    LD_A(LOW(rSCY));
    CALL(aBattleBGEffect_SetLCDStatCustoms1);
    LDH_A_addr(hLYOverrideEnd);
    INC_A;
    LDH_addr_A(hLYOverrideEnd);
    LD_HL(BG_EFFECT_STRUCT_BATTLE_TURN);
    ADD_HL_BC;
    LD_hl(0x2);
    LD_HL(BG_EFFECT_STRUCT_PARAM);
    ADD_HL_BC;
    LD_hl(0x0);
    RET;

one:

    LD_HL(BG_EFFECT_STRUCT_PARAM);
    ADD_HL_BC;
    LD_A_hl;
    AND_A_A;
    IF_Z goto next;
    DEC_hl;
    RET;

next:

    LD_hl(0x10);
    CALL(aBattleBGEffects_IncAnonJumptableIndex);

two:

    LDH_A_addr(hLYOverrideStart);
    LD_L_A;
    LDH_A_addr(hLYOverrideEnd);
    SUB_A_L;
    DEC_A;
    LD_HL(BG_EFFECT_STRUCT_BATTLE_TURN);
    ADD_HL_BC;
    CP_A_hl;
    RET_C;
    LD_A_hl;
    PUSH_AF;
    AND_A(0x7);
    IF_NZ goto skip;
    LD_HL(BG_EFFECT_STRUCT_JT_INDEX);
    ADD_HL_BC;
    DEC_hl;

skip:

    POP_AF;
    CALL(aBGEffect_DisplaceLYOverridesBackup);
    LD_HL(BG_EFFECT_STRUCT_BATTLE_TURN);
    ADD_HL_BC;
    INC_hl;
    INC_hl;
    RET;

three:

    CALL(aBattleAnim_ResetLCDStatCustom);
    RET;
}

void BattleBGEffect_Tackle(void) {
    SET_PC(aBattleBGEffect_Tackle);
    // CALL(aBattleBGEffects_AnonJumptable);

anon_dw:

    if (REG_BC == 0) goto zero;
    if (REG_BC == 1) return Tackle_MoveForward();
    if (REG_BC == 2) return Tackle_ReturnMove();
    if (REG_BC == 3) goto three;

zero:

    //  Prepares mon to move forward (player moves right, enemy moves left)
    //  BG_EFFECT_STRUCT_PARAM will keep track of distance moved, so it's reset to 0 here
    //  BG_EFFECT_STRUCT_BATTLE_TURN is set to 2 or -2 depending on target
    CALL(aBattleBGEffects_IncAnonJumptableIndex);
    CALL(aBattleBGEffects_ClearLYOverrides);
    LD_A(LOW(rSCX));
    CALL(aBattleBGEffect_SetLCDStatCustoms1);
    LDH_A_addr(hLYOverrideEnd);
    INC_A;
    LDH_addr_A(hLYOverrideEnd);
    LD_HL(BG_EFFECT_STRUCT_PARAM);
    ADD_HL_BC;
    LD_hl(0);
    CALL(aBGEffect_CheckBattleTurn);
    IF_NZ goto player_side;
    LD_A(2);
    goto okay;

player_side:

    LD_A(-2);

okay:

    LD_hl_A;
    RET;

three:

    CALL(aBattleAnim_ResetLCDStatCustom);
    RET;
}

void BattleBGEffect_BodySlam(void) {
    SET_PC(aBattleBGEffect_BodySlam);
    // CALL(aBattleBGEffects_AnonJumptable);

anon_dw:

    if (REG_BC == 0) goto zero;
    if (REG_BC == 1) return Tackle_MoveForward();
    if (REG_BC == 2) return Tackle_ReturnMove();
    if (REG_BC == 3) goto three;

zero:

    //  Prepares mon to move forward (player moves right, enemy moves left)
    //  BG_EFFECT_STRUCT_PARAM will keep track of distance moved, so it's reset to 0 here
    //  BG_EFFECT_STRUCT_BATTLE_TURN is set to 2 or -2 depending on target
    CALL(aBattleBGEffects_IncAnonJumptableIndex);
    CALL(aBattleBGEffects_ClearLYOverrides);
    LD_A(LOW(rSCX));
    CALL(aBattleBGEffect_SetLCDStatCustoms2);
    LDH_A_addr(hLYOverrideEnd);
    INC_A;
    LDH_addr_A(hLYOverrideEnd);
    LD_HL(BG_EFFECT_STRUCT_PARAM);
    ADD_HL_BC;
    LD_hl(0);
    CALL(aBGEffect_CheckBattleTurn);
    IF_NZ goto player_side;
    LD_A(2);
    goto okay;

player_side:

    LD_A(-2);

okay:

    LD_hl_A;
    RET;

three:

    CALL(aBattleAnim_ResetLCDStatCustom);
    RET;
}

void Tackle_MoveForward(void) {
    SET_PC(aTackle_MoveForward);
    //  Moves user horizontally in a direction that can be positive or negative. When the limit is reached (8 pixels) we move to the next function in the jumptable (Tackle_ReturnMove)
    //  BG_EFFECT_STRUCT_BATTLE_TURN: speed and direction
    //  BG_EFFECT_STRUCT_PARAM: keeps track of distance moved
    LD_HL(BG_EFFECT_STRUCT_PARAM);
    ADD_HL_BC;
    LD_A_hl;
    CP_A(-8);
    IF_Z goto reached_limit;
    CP_A(8);
    IF_NZ goto finish;

reached_limit:

    CALL(aBattleBGEffects_IncAnonJumptableIndex);

finish:

    CALL(aRollout_FillLYOverridesBackup);
    LD_HL(BG_EFFECT_STRUCT_BATTLE_TURN);
    ADD_HL_BC;
    LD_A_hl;
    LD_HL(BG_EFFECT_STRUCT_PARAM);
    ADD_HL_BC;
    ADD_A_hl;
    LD_hl_A;
    RET;
}

void Tackle_ReturnMove(void) {
    SET_PC(aTackle_ReturnMove);
    //  Move user horizontally back to initial position. When we back to position 0, we move to the next function in the jumptable
    //  BG_EFFECT_STRUCT_BATTLE_TURN: is turned into a negative number (this number is not saved to preserve the initial number)
    //  BG_EFFECT_STRUCT_PARAM: keeps track of distance moved
    LD_HL(BG_EFFECT_STRUCT_PARAM);
    ADD_HL_BC;
    LD_A_hl;
    AND_A_A;
    IF_NZ goto move_back;
    CALL(aBattleBGEffects_IncAnonJumptableIndex);

move_back:

    CALL(aRollout_FillLYOverridesBackup);
    LD_HL(BG_EFFECT_STRUCT_BATTLE_TURN);
    ADD_HL_BC;
    LD_A_hl;
    XOR_A(0xff);
    INC_A;
    LD_HL(BG_EFFECT_STRUCT_PARAM);
    ADD_HL_BC;
    ADD_A_hl;
    LD_hl_A;
    RET;
}

void Rollout_FillLYOverridesBackup(void) {
    SET_PC(aRollout_FillLYOverridesBackup);
    PUSH_AF;
    LD_A_addr(wFXAnimID + 1);
    OR_A_A;
    IF_NZ goto not_rollout;
    LD_A_addr(wFXAnimID);
    CP_A(ROLLOUT);
    IF_Z goto rollout;

not_rollout:

    POP_AF;
    JP(mBGEffect_FillLYOverridesBackup);

rollout:

    LDH_A_addr(hLYOverrideStart);
    LD_D_A;
    LDH_A_addr(hLYOverrideEnd);
    SUB_A_D;
    LD_D_A;
    LD_H(HIGH(wLYOverridesBackup));
    LDH_A_addr(hSCY);
    OR_A_A;
    IF_NZ goto skip1;
    LDH_A_addr(hLYOverrideStart);
    OR_A_A;
    IF_Z goto skip2;
    DEC_A;
    LD_L_A;
    LD_hl(0x0);
    goto skip2;

skip1:

    LDH_A_addr(hLYOverrideEnd);
    DEC_A;
    LD_L_A;
    LD_hl(0x0);

skip2:

    LDH_A_addr(hSCY);
    LD_L_A;
    LDH_A_addr(hLYOverrideStart);
    SUB_A_L;
    IF_NC goto skip3;
    XOR_A_A;
    DEC_D;

skip3:

    LD_L_A;
    POP_AF;

loop:

    LD_hli_A;
    DEC_D;
    IF_NZ goto loop;
    RET;
}

void BattleBGEffect_BetaPursuit(void) {
    SET_PC(aBattleBGEffect_BetaPursuit);
    //  //  unused
    // CALL(aBattleBGEffects_AnonJumptable);

anon_dw:

    if (REG_BC == 0) return VitalThrow_MoveBackwards();
    if (REG_BC == 1) return Tackle_MoveForward();
    if (REG_BC == 2) return Tackle_ReturnMove();
    if (REG_BC == 3) goto three;

three:

    CALL(aBattleAnim_ResetLCDStatCustom);
    RET;
}

void VitalThrow_MoveBackwards(void) {
    SET_PC(aVitalThrow_MoveBackwards);
    //  Prepares mon to move back back (player moves left, enemy moves right)
    //  BG_EFFECT_STRUCT_PARAM: keeps track of distance moved, so it's reset to 0 here
    CALL(aBattleBGEffects_IncAnonJumptableIndex);
    CALL(aBattleBGEffects_ClearLYOverrides);
    LD_A(LOW(rSCX));
    CALL(aBattleBGEffect_SetLCDStatCustoms1);
    LDH_A_addr(hLYOverrideEnd);
    INC_A;
    LDH_addr_A(hLYOverrideEnd);
    LD_HL(BG_EFFECT_STRUCT_PARAM);
    ADD_HL_BC;
    LD_hl(0x0);
    CALL(aBGEffect_CheckBattleTurn);
    IF_NZ goto player_turn;
    LD_A(-2);
    goto okay;

player_turn:

    LD_A(2);

okay:

    LD_hl_A;
    RET;
}

void BattleBGEffect_VitalThrow(void) {
    SET_PC(aBattleBGEffect_VitalThrow);
    // CALL(aBattleBGEffects_AnonJumptable);

anon_dw:

    if (REG_BC == 0) return VitalThrow_MoveBackwards();
    if (REG_BC == 1) return Tackle_MoveForward();
    if (REG_BC == 2) goto two;
    if (REG_BC == 3) return Tackle_ReturnMove();
    if (REG_BC == 4) goto four;

four:

    CALL(aBattleAnim_ResetLCDStatCustom);

two:

    RET;
}

void BattleBGEffect_WobbleMon(void) {
    SET_PC(aBattleBGEffect_WobbleMon);
    //  Similar to BattleBGEffect_WobblePlayer, except it can affect either side and the sine movement has a radius of 8 instead of 6 and it moves at twice the rate
    // CALL(aBattleBGEffects_AnonJumptable);

anon_dw:

    if (REG_BC == 0) goto zero;
    if (REG_BC == 1) goto one;
    if (REG_BC == 2) goto two;

zero:

    CALL(aBattleBGEffects_IncAnonJumptableIndex);
    CALL(aBattleBGEffects_ClearLYOverrides);
    LD_A(LOW(rSCX));
    CALL(aBattleBGEffect_SetLCDStatCustoms1);
    LDH_A_addr(hLYOverrideEnd);
    INC_A;
    LDH_addr_A(hLYOverrideEnd);
    LD_HL(BG_EFFECT_STRUCT_PARAM);
    ADD_HL_BC;
    LD_hl(0x0);
    RET;

one:

    LD_HL(BG_EFFECT_STRUCT_PARAM);
    ADD_HL_BC;
    LD_A_hl;
    LD_D(0x8);
    CALL(aBattleBGEffects_Sine);
    CALL(aBGEffect_FillLYOverridesBackup);
    LD_HL(BG_EFFECT_STRUCT_PARAM);
    ADD_HL_BC;
    LD_A_hl;
    ADD_A(0x4);
    LD_hl_A;
    RET;

two:

    CALL(aBattleAnim_ResetLCDStatCustom);
    RET;
}

void BattleBGEffect_Flail(void) {
    SET_PC(aBattleBGEffect_Flail);
    // CALL(aBattleBGEffects_AnonJumptable);

anon_dw:

    if (REG_BC == 0) goto zero;
    if (REG_BC == 1) goto one;
    if (REG_BC == 2) goto two;

zero:

    CALL(aBattleBGEffects_IncAnonJumptableIndex);
    CALL(aBattleBGEffects_ClearLYOverrides);
    LD_A(LOW(rSCX));
    CALL(aBattleBGEffect_SetLCDStatCustoms1);
    LDH_A_addr(hLYOverrideEnd);
    INC_A;
    LDH_addr_A(hLYOverrideEnd);
    XOR_A_A;
    LD_HL(BG_EFFECT_STRUCT_BATTLE_TURN);
    ADD_HL_BC;
    LD_hli_A;
    LD_hl_A;
    RET;

one:

    LD_HL(BG_EFFECT_STRUCT_PARAM);
    ADD_HL_BC;
    LD_A_hl;
    LD_D(0x6);
    CALL(aBattleBGEffects_Sine);
    PUSH_AF;
    LD_HL(BG_EFFECT_STRUCT_BATTLE_TURN);
    ADD_HL_BC;
    LD_A_hl;
    LD_D(0x2);
    CALL(aBattleBGEffects_Sine);
    LD_E_A;
    POP_AF;
    ADD_A_E;
    CALL(aBGEffect_FillLYOverridesBackup);
    LD_HL(BG_EFFECT_STRUCT_BATTLE_TURN);
    ADD_HL_BC;
    LD_A_hl;
    ADD_A(0x8);
    LD_hl_A;
    LD_HL(BG_EFFECT_STRUCT_PARAM);
    ADD_HL_BC;
    LD_A_hl;
    ADD_A(0x2);
    LD_hl_A;
    RET;

two:

    CALL(aBattleAnim_ResetLCDStatCustom);
    RET;
}

void BattleBGEffect_WaveDeformMon(void) {
    SET_PC(aBattleBGEffect_WaveDeformMon);
    // CALL(aBattleBGEffects_AnonJumptable);

anon_dw:

    if (REG_BC == 0) goto zero;
    if (REG_BC == 1) goto one;
    if (REG_BC == 2) goto two;

zero:

    CALL(aBattleBGEffects_IncAnonJumptableIndex);
    CALL(aBattleBGEffects_ClearLYOverrides);
    LD_A(LOW(rSCX));
    CALL(aBattleBGEffect_SetLCDStatCustoms1);
    RET;

one:

    LD_HL(BG_EFFECT_STRUCT_PARAM);
    ADD_HL_BC;
    LD_A_hl;
    CP_A(0x20);
    RET_NC;
    INC_hl;
    LD_D_A;
    LD_E(4);
    CALL(aDeformScreen);
    RET;

two:

    LD_HL(BG_EFFECT_STRUCT_PARAM);
    ADD_HL_BC;
    LD_A_hl;
    AND_A_A;
    IF_Z goto reset;
    DEC_hl;
    LD_D_A;
    LD_E(4);
    CALL(aDeformScreen);
    RET;

reset:

    CALL(aBattleAnim_ResetLCDStatCustom);
    RET;
}

void BattleBGEffect_BounceDown(void) {
    SET_PC(aBattleBGEffect_BounceDown);
    // CALL(aBattleBGEffects_AnonJumptable);

anon_dw:

    if (REG_BC == 0) goto zero;
    if (REG_BC == 1) goto one;
    if (REG_BC == 2) goto two;

zero:

    CALL(aBattleBGEffects_IncAnonJumptableIndex);
    CALL(aBattleBGEffects_ClearLYOverrides);
    LD_A(LOW(rSCY));
    CALL(aBattleBGEffect_SetLCDStatCustoms2);
    LDH_A_addr(hLYOverrideEnd);
    INC_A;
    LDH_addr_A(hLYOverrideEnd);
    LD_HL(BG_EFFECT_STRUCT_BATTLE_TURN);
    ADD_HL_BC;
    LD_hl(0x1);
    LD_HL(BG_EFFECT_STRUCT_PARAM);
    ADD_HL_BC;
    LD_hl(0x20);
    RET;

one:

    LD_HL(BG_EFFECT_STRUCT_BATTLE_TURN);
    ADD_HL_BC;
    LD_A_hl;
    CP_A(0x38);
    RET_NC;
    PUSH_AF;
    LD_HL(BG_EFFECT_STRUCT_PARAM);
    ADD_HL_BC;
    LD_A_hl;
    LD_D(0x10);
    CALL(aBattleBGEffects_Cosine);
    ADD_A(0x10);
    LD_D_A;
    POP_AF;
    ADD_A_D;
    CALL(aBGEffect_DisplaceLYOverridesBackup);
    LD_HL(BG_EFFECT_STRUCT_PARAM);
    ADD_HL_BC;
    INC_hl;
    INC_hl;
    RET;

two:

    CALL(aBattleAnim_ResetLCDStatCustom);
    RET;
}

void BattleBGEffect_BetaSendOutMon1(void) {
    SET_PC(aBattleBGEffect_BetaSendOutMon1);
    //  //  unused
    // CALL(aBattleBGEffects_AnonJumptable);

anon_dw:

    if (REG_BC == 0) goto zero;
    if (REG_BC == 1) goto one;
    if (REG_BC == 2) goto two;
    if (REG_BC == 3) goto three;
    if (REG_BC == 4) goto four;
    if (REG_BC == 5) goto five;

zero:

    CALL(aBattleBGEffects_IncAnonJumptableIndex);
    LD_A(0xe4);
    CALL(aBattleBGEffects_SetLYOverrides);
    LD_A(0x47);
    CALL(aBattleBGEffect_SetLCDStatCustoms1);
    LDH_A_addr(hLYOverrideEnd);
    INC_A;
    LDH_addr_A(hLYOverrideEnd);
    LDH_A_addr(hLYOverrideStart);
    LD_L_A;
    LD_H(HIGH(wLYOverridesBackup));

loop:

    LDH_A_addr(hLYOverrideEnd);
    CP_A_L;
    IF_Z goto done;
    XOR_A_A;
    LD_hli_A;
    goto loop;

done:

    LD_HL(BG_EFFECT_STRUCT_PARAM);
    ADD_HL_BC;
    LD_hl(0x0);

one:

four:

    RET;

two:

    CALL(aBattleBGEffect_BetaSendOutMon1_GetLYOverride);
    IF_NC goto next;
    CALL(aBattleBGEffect_BetaSendOutMon1_SetLYOverridesBackup);
    RET;

next:

    LD_HL(BG_EFFECT_STRUCT_PARAM);
    ADD_HL_BC;
    LD_hl(0x0);
    LDH_A_addr(hLYOverrideStart);
    INC_A;
    LDH_addr_A(hLYOverrideStart);
    CALL(aBattleBGEffects_IncAnonJumptableIndex);
    RET;

three:

    CALL(aBattleBGEffect_BetaSendOutMon1_GetLYOverride);
    IF_NC goto finish;
    CALL(aBattleBGEffect_BetaSendOutMon1_SetLYOverridesBackup);
    LDH_A_addr(hLYOverrideEnd);
    DEC_A;
    LD_L_A;
    LD_hl_E;
    RET;

finish:

    CALL(aBattleBGEffects_IncAnonJumptableIndex);
    RET;

SetLYOverridesBackup:

    LD_E_A;
    LDH_A_addr(hLYOverrideStart);
    LD_L_A;
    LDH_A_addr(hLYOverrideEnd);
    SUB_A_L;
    SRL_A;
    LD_H(HIGH(wLYOverridesBackup));

loop2:

    LD_hl_E;
    INC_HL;
    INC_HL;
    DEC_A;
    IF_NZ goto loop2;
    RET;

five:

    CALL(aBattleBGEffects_ResetVideoHRAM);
    RET;

GetLYOverride:

    LD_HL(BG_EFFECT_STRUCT_PARAM);
    ADD_HL_BC;
    LD_A_hl;
    INC_hl;
    SRL_A;
    SRL_A;
    SRL_A;
    LD_E_A;
    LD_D(0);
    LD_HL(mBattleBGEffect_BetaSendOutMon1_data);
    ADD_HL_DE;
    LD_A_hl;
    CP_A(0xff);
    RET;

data:

    // db ['0x00', '0x40', '0x90', '0xe4'];
    // db ['-1'];

    return BattleBGEffect_BetaSendOutMon2();
}

void BattleBGEffect_BetaSendOutMon2(void) {
    SET_PC(aBattleBGEffect_BetaSendOutMon2);
    //  //  unused
    // CALL(aBattleBGEffects_AnonJumptable);

anon_dw:

    if (REG_BC == 0) goto zero;
    if (REG_BC == 1) goto one;

zero:

    CALL(aBattleBGEffects_IncAnonJumptableIndex);
    CALL(aBattleBGEffects_ClearLYOverrides);
    LD_A(LOW(rSCX));
    CALL(aBattleBGEffect_SetLCDStatCustoms1);
    LD_HL(BG_EFFECT_STRUCT_BATTLE_TURN);
    ADD_HL_BC;
    LD_hl(0x40);
    RET;

one:

    LD_HL(BG_EFFECT_STRUCT_BATTLE_TURN);
    ADD_HL_BC;
    LD_A_hl;
    AND_A_A;
    IF_Z goto done;
    DEC_hl;
    SRL_A;
    SRL_A;
    SRL_A;
    AND_A(0xf);
    LD_D_A;
    LD_E_A;
    CALL(aDeformScreen);
    RET;

done:

    CALL(aBattleAnim_ResetLCDStatCustom);
    RET;
}

void BattleBGEffect_FadeMonsToBlackRepeating(void) {
    SET_PC(aBattleBGEffect_FadeMonsToBlackRepeating);
    LDH_A_addr(hCGB);
    AND_A_A;
    IF_NZ goto cgb;
    // CALL(aBattleBGEffects_AnonJumptable);

anon_dw:

    if (REG_BC == 0) goto zero;
    if (REG_BC == 1) goto one;
    if (REG_BC == 2) goto two;

zero:

    CALL(aBattleBGEffects_IncAnonJumptableIndex);
    LD_A(0xe4);
    CALL(aBattleBGEffects_SetLYOverrides);
    LD_A(LOW(rBGP));
    LDH_addr_A(hLCDCPointer);
    XOR_A_A;
    LDH_addr_A(hLYOverrideStart);
    LD_A(0x60);
    LDH_addr_A(hLYOverrideEnd);
    RET;

one:

    LD_HL(BG_EFFECT_STRUCT_PARAM);
    ADD_HL_BC;
    LD_A_hl;
    INC_hl;
    LD_E_A;
    AND_A(0x7);
    RET_NZ;
    LD_A_E;
    AND_A(0x18);
    SLA_A;
    SWAP_A;
    SLA_A;
    LD_E_A;
    LD_D(0);
    PUSH_BC;
    CALL(aBGEffect_CheckBattleTurn);
    IF_NZ goto player;
    LD_HL(mBattleBGEffect_FadeMonsToBlackRepeating_CGB_DMGEnemyData);
    ADD_HL_DE;
    LD_A_hli;
    LD_addr_A(wOBP1);
    LD_D_A;
    LD_E_hl;
    LD_BC((0x2f << 8) | 0x30);
    goto okay;

player:

    LD_HL(mBattleBGEffect_FadeMonsToBlackRepeating_DMG_PlayerData);
    ADD_HL_DE;
    LD_D_hl;
    INC_HL;
    LD_A_hl;
    LD_addr_A(wOBP1);
    LD_E_A;
    LD_BC((0x37 << 8) | 0x28);

okay:

    CALL(aBattleBGEffect_FadeMonsToBlackRepeating_DMG_LYOverrideLoads);
    POP_BC;
    RET;

two:

    CALL(aBattleBGEffects_ResetVideoHRAM);
    LD_A(0xe4);
    LD_addr_A(wBGP);
    LD_addr_A(wOBP1);
    RET;

DMG_LYOverrideLoads:

    LD_HL(wLYOverridesBackup);

loop1:

    LD_hl_D;
    INC_HL;
    DEC_B;
    IF_NZ goto loop1;

loop2:

    LD_hl_E;
    INC_HL;
    DEC_C;
    IF_NZ goto loop2;
    RET;

cgb:

    LD_DE(mBattleBGEffect_FadeMonsToBlackRepeating_Jumptable);
    CALL(aBatttleBGEffects_GetNamedJumptablePointer);
    JP_hl;

Jumptable:

    if (REG_BC == 0) goto cgb_zero;
    if (REG_BC == 1) goto cgb_one;
    if (REG_BC == 2) goto cgb_two;

cgb_zero:

    CALL(aBattleBGEffects_IncAnonJumptableIndex);
    LD_HL(BG_EFFECT_STRUCT_PARAM);
    ADD_HL_BC;
    LD_hl(0x0);
    RET;

cgb_one:

    LD_HL(BG_EFFECT_STRUCT_PARAM);
    ADD_HL_BC;
    LD_A_hl;
    INC_hl;
    LD_E_A;
    AND_A(0x7);
    RET_NZ;
    LD_A_E;
    AND_A(0x18);
    SLA_A;
    SWAP_A;
    SLA_A;
    LD_E_A;
    LD_D(0);
    CALL(aBGEffect_CheckBattleTurn);
    IF_NZ goto player_2;
    LD_HL(mBattleBGEffect_FadeMonsToBlackRepeating_CGB_DMGEnemyData);
    ADD_HL_DE;
    LD_A_hli;
    PUSH_HL;
    CALL(aBGEffects_LoadBGPal1_OBPal0);
    POP_HL;
    LD_A_hl;
    CALL(aBGEffects_LoadBGPal0_OBPal1);
    RET;

player_2:

    LD_HL(mBattleBGEffect_FadeMonsToBlackRepeating_CGB_DMGEnemyData);
    ADD_HL_DE;
    LD_A_hli;
    PUSH_HL;
    CALL(aBGEffects_LoadBGPal0_OBPal1);
    POP_HL;
    LD_A_hl;
    CALL(aBGEffects_LoadBGPal1_OBPal0);
    RET;

cgb_two:

    LD_A(0xe4);
    CALL(aBGEffects_LoadBGPal0_OBPal1);
    LD_A(0xe4);
    CALL(aBGEffects_LoadBGPal1_OBPal0);
    CALL(aEndBattleBGEffect);
    RET;

CGB_DMGEnemyData:

    // db ['0xe4', '0xe4'];
    // db ['0xf8', '0x90'];
    // db ['0xfc', '0x40'];
    // db ['0xf8', '0x90'];

DMG_PlayerData:

    // db ['0xe4', '0xe4'];
    // db ['0x90', '0xf8'];
    // db ['0x40', '0xfc'];
    // db ['0x90', '0xf8'];

    return BattleBGEffect_RapidFlash();
}

void BattleBGEffect_RapidFlash(void) {
    SET_PC(aBattleBGEffect_RapidFlash);
    //  //  unused
    LD_DE(mBattleBGEffect_RapidFlash_FlashPals);
    CALL(aBGEffect_RapidCyclePals);
    RET;

FlashPals:

    // db ['0xe4', '0x6c', '0xfe'];

    return BattleBGEffect_FadeMonToLight();
}

void BattleBGEffect_FadeMonToLight(void) {
    SET_PC(aBattleBGEffect_FadeMonToLight);
    //  BG_EFFECT_STRUCT_BATTLE_TURN = BG_EFFECT_TARGET or BG_EFFECT_USER
    LD_DE(mBattleBGEffect_FadeMonToLight_Pals);
    CALL(aBGEffect_RapidCyclePals);
    RET;

Pals:

    // db ['0xe4', '0x90', '0x40', '0xff'];

    return BattleBGEffect_FadeMonToBlack();
}

void BattleBGEffect_FadeMonToBlack(void) {
    SET_PC(aBattleBGEffect_FadeMonToBlack);
    //  BG_EFFECT_STRUCT_BATTLE_TURN = BG_EFFECT_TARGET or BG_EFFECT_USER
    LD_DE(mBattleBGEffect_FadeMonToBlack_Pals);
    CALL(aBGEffect_RapidCyclePals);
    RET;

Pals:

    // db ['0xe4', '0xf8', '0xfc', '0xff'];

    return BattleBGEffect_FadeMonToLightRepeating();
}

void BattleBGEffect_FadeMonToLightRepeating(void) {
    SET_PC(aBattleBGEffect_FadeMonToLightRepeating);
    //  BG_EFFECT_STRUCT_BATTLE_TURN = BG_EFFECT_TARGET or BG_EFFECT_USER
    LD_DE(mBattleBGEffect_FadeMonToLightRepeating_Pals);
    CALL(aBGEffect_RapidCyclePals);
    RET;

Pals:

    // db ['0xe4', '0x90', '0x40', '0x90', '0xfe'];

    return BattleBGEffect_FadeMonToBlackRepeating();
}

void BattleBGEffect_FadeMonToBlackRepeating(void) {
    SET_PC(aBattleBGEffect_FadeMonToBlackRepeating);
    //  BG_EFFECT_STRUCT_BATTLE_TURN = BG_EFFECT_TARGET or BG_EFFECT_USER
    LD_DE(mBattleBGEffect_FadeMonToBlackRepeating_Pals);
    CALL(aBGEffect_RapidCyclePals);
    RET;

Pals:

    // db ['0xe4', '0xf8', '0xfc', '0xf8', '0xfe'];

    return BattleBGEffect_CycleMonLightDarkRepeating();
}

void BattleBGEffect_CycleMonLightDarkRepeating(void) {
    SET_PC(aBattleBGEffect_CycleMonLightDarkRepeating);
    //  BG_EFFECT_STRUCT_BATTLE_TURN = BG_EFFECT_TARGET or BG_EFFECT_USER
    LD_DE(mBattleBGEffect_CycleMonLightDarkRepeating_Pals);
    CALL(aBGEffect_RapidCyclePals);
    RET;

Pals:

    // db ['0xe4', '0xf8', '0xfc', '0xf8', '0xe4', '0x90', '0x40', '0x90', '0xfe'];

    return BattleBGEffect_FlashMonRepeating();
}

void BattleBGEffect_FlashMonRepeating(void) {
    SET_PC(aBattleBGEffect_FlashMonRepeating);
    //  //  unused
    //  BG_EFFECT_STRUCT_BATTLE_TURN = BG_EFFECT_TARGET or BG_EFFECT_USER
    LD_DE(mBattleBGEffect_FlashMonRepeating_Pals);
    CALL(aBGEffect_RapidCyclePals);
    RET;

Pals:

    // db ['0xe4', '0xfc', '0xe4', '0x00', '0xfe'];

    return BattleBGEffect_FadeMonToWhiteWaitFadeBack();
}

void BattleBGEffect_FadeMonToWhiteWaitFadeBack(void) {
    SET_PC(aBattleBGEffect_FadeMonToWhiteWaitFadeBack);
    //  BG_EFFECT_STRUCT_BATTLE_TURN = BG_EFFECT_TARGET or BG_EFFECT_USER
    LD_DE(mBattleBGEffect_FadeMonToWhiteWaitFadeBack_Pals);
    CALL(aBGEffect_RapidCyclePals);
    RET;

Pals:

    // db ['0xe4', '0x90', '0x40', '0x00', '0x00', '0x00', '0x00', '0x00', '0x00', '0x00', '0x00', '0x00', '0x00', '0x00', '0x40', '0x90', '0xe4', '0xff'];

    return BattleBGEffect_FadeMonFromWhite();
}

void BattleBGEffect_FadeMonFromWhite(void) {
    SET_PC(aBattleBGEffect_FadeMonFromWhite);
    //  //  unused
    //  BG_EFFECT_STRUCT_BATTLE_TURN = BG_EFFECT_TARGET or BG_EFFECT_USER
    LD_DE(mBattleBGEffect_FadeMonFromWhite_Pals);
    CALL(aBGEffect_RapidCyclePals);
    RET;

Pals:

    // db ['0x00', '0x40', '0x90', '0xe4', '0xff'];

    return BattleBGEffect_VibrateMon();
}

void BattleBGEffect_VibrateMon(void) {
    SET_PC(aBattleBGEffect_VibrateMon);
    //  Moves mon back and forth sideways for $20 frames
    //  BG_EFFECT_STRUCT_BATTLE_TURN = BG_EFFECT_TARGET or BG_EFFECT_USER
    // CALL(aBattleBGEffects_AnonJumptable);

anon_dw:

    if (REG_BC == 0) goto zero;
    if (REG_BC == 1) goto one;

zero:

    CALL(aBattleBGEffects_IncAnonJumptableIndex);
    CALL(aBattleBGEffects_ClearLYOverrides);
    LD_A(LOW(rSCX));
    CALL(aBattleBGEffect_SetLCDStatCustoms1);
    LDH_A_addr(hLYOverrideEnd);
    INC_A;
    LDH_addr_A(hLYOverrideEnd);
    LD_HL(BG_EFFECT_STRUCT_BATTLE_TURN);
    ADD_HL_BC;
    LD_hl(0x1);
    LD_HL(BG_EFFECT_STRUCT_PARAM);
    ADD_HL_BC;
    LD_hl(0x20);
    RET;

one:

    LD_HL(BG_EFFECT_STRUCT_PARAM);
    ADD_HL_BC;
    LD_A_hl;
    AND_A_A;
    IF_Z goto finish;
    DEC_hl;
    AND_A(0x1);
    RET_NZ;
    LD_HL(BG_EFFECT_STRUCT_BATTLE_TURN);
    ADD_HL_BC;
    LD_A_hl;
    XOR_A(0xff);
    INC_A;
    LD_hl_A;
    CALL(aBGEffect_FillLYOverridesBackup);
    RET;

finish:

    CALL(aBattleAnim_ResetLCDStatCustom);
    RET;
}

void BattleBGEffect_WobblePlayer(void) {
    SET_PC(aBattleBGEffect_WobblePlayer);
    //  Always affects the player
    // CALL(aBattleBGEffects_AnonJumptable);

anon_dw:

    if (REG_BC == 0) goto zero;
    if (REG_BC == 1) goto one;
    if (REG_BC == 2) goto two;

zero:

    CALL(aBattleBGEffects_IncAnonJumptableIndex);
    CALL(aBattleBGEffects_ClearLYOverrides);
    LD_A(LOW(rSCX));
    LDH_addr_A(hLCDCPointer);
    XOR_A_A;
    LDH_addr_A(hLYOverrideStart);
    LD_A(0x37);
    LDH_addr_A(hLYOverrideEnd);
    LD_HL(BG_EFFECT_STRUCT_PARAM);
    ADD_HL_BC;
    LD_hl(0x0);
    RET;

one:

    LD_HL(BG_EFFECT_STRUCT_PARAM);
    ADD_HL_BC;
    LD_A_hl;
    CP_A(0x40);
    IF_NC goto two;
    LD_D(0x6);
    CALL(aBattleBGEffects_Sine);
    CALL(aBGEffect_FillLYOverridesBackup);
    LD_HL(BG_EFFECT_STRUCT_PARAM);
    ADD_HL_BC;
    LD_A_hl;
    ADD_A(0x2);
    LD_hl_A;
    RET;

two:

    CALL(aBattleAnim_ResetLCDStatCustom);
    RET;
}

void BattleBGEffect_Rollout(void) {
    SET_PC(aBattleBGEffect_Rollout);
    CALL(aBattleBGEffects_GetShakeAmount);
    IF_C goto xor_a;
    BIT_A(7);
    IF_Z goto okay;

xor_a:

    XOR_A_A;

okay:

    PUSH_AF;
    CALL(aDelayFrame);
    POP_AF;
    LDH_addr_A(hSCY);
    XOR_A(0xff);
    INC_A;
    LD_addr_A(wAnimObject1YOffset);
    RET;
}

void BattleBGEffect_ShakeScreenX(void) {
    SET_PC(aBattleBGEffect_ShakeScreenX);
    CALL(aBattleBGEffects_GetShakeAmount);
    IF_NC goto skip;
    XOR_A_A;

skip:

    LDH_addr_A(hSCX);
    RET;
}

void BattleBGEffect_ShakeScreenY(void) {
    SET_PC(aBattleBGEffect_ShakeScreenY);
    CALL(aBattleBGEffects_GetShakeAmount);
    IF_NC goto skip;
    XOR_A_A;

skip:

    LDH_addr_A(hSCY);
    RET;
}

void BattleBGEffects_GetShakeAmount(void) {
    SET_PC(aBattleBGEffects_GetShakeAmount);
    LD_HL(BG_EFFECT_STRUCT_JT_INDEX);
    ADD_HL_BC;
    LD_A_hl;
    AND_A_A;
    IF_NZ goto okay;
    CALL(aEndBattleBGEffect);
    SCF;
    RET;

okay:

    DEC_hl;
    LD_HL(BG_EFFECT_STRUCT_PARAM);
    ADD_HL_BC;
    LD_A_hl;
    AND_A(0xf);
    IF_Z goto every_16_frames;
    DEC_hl;
    LD_HL(BG_EFFECT_STRUCT_BATTLE_TURN);
    ADD_HL_BC;
    LD_A_hl;
    AND_A_A;
    RET;

every_16_frames:

    LD_A_hl;
    SWAP_A;
    OR_A_hl;
    LD_hl_A;
    LD_HL(BG_EFFECT_STRUCT_BATTLE_TURN);
    ADD_HL_BC;
    LD_A_hl;
    XOR_A(0xff);
    INC_A;
    LD_hl_A;
    AND_A_A;
    RET;
}

void BattleBGEffect_WobbleScreen(void) {
    SET_PC(aBattleBGEffect_WobbleScreen);
    LD_HL(BG_EFFECT_STRUCT_PARAM);
    ADD_HL_BC;
    LD_A_hl;
    CP_A(0x40);
    IF_NC goto finish;
    LD_D(0x6);
    CALL(aBattleBGEffects_Sine);
    LDH_addr_A(hSCX);
    LD_HL(BG_EFFECT_STRUCT_PARAM);
    ADD_HL_BC;
    LD_A_hl;
    ADD_A(0x2);
    LD_hl_A;
    RET;

finish:

    XOR_A_A;
    LDH_addr_A(hSCX);
    RET;
}

void BattleBGEffect_GetNthDMGPal(void) {
    SET_PC(aBattleBGEffect_GetNthDMGPal);
    LD_HL(BG_EFFECT_STRUCT_JT_INDEX);
    ADD_HL_BC;
    LD_A_hl;
    AND_A_A;
    IF_Z goto zero;
    DEC_hl;
    LD_HL(BG_EFFECT_STRUCT_PARAM);
    ADD_HL_BC;
    LD_A_hl;
    CALL(aBattleBGEffect_GetNextDMGPal);
    RET;

zero:

    LD_HL(BG_EFFECT_STRUCT_BATTLE_TURN);
    ADD_HL_BC;
    LD_A_hl;
    LD_HL(BG_EFFECT_STRUCT_JT_INDEX);
    ADD_HL_BC;
    LD_hl_A;
    CALL(aBattleBGEffect_GetFirstDMGPal);
    RET;
}

void BGEffect_RapidCyclePals(void) {
    SET_PC(aBGEffect_RapidCyclePals);
    //  Last index in DE: $fe signals a loop, $ff signals end
    LDH_A_addr(hCGB);
    AND_A_A;
    IF_NZ goto cgb;
    PUSH_DE;
    LD_DE(mBGEffect_RapidCyclePals_Jumptable_DMG);
    CALL(aBatttleBGEffects_GetNamedJumptablePointer);
    POP_DE;
    JP_hl;

Jumptable_DMG:

    if (REG_BC == 0) goto zero_dmg;
    if (REG_BC == 1) goto one_dmg;
    if (REG_BC == 2) goto two_dmg;

zero_dmg:

    CALL(aBattleBGEffects_IncAnonJumptableIndex);
    LD_A(0xe4);
    CALL(aBattleBGEffects_SetLYOverrides);
    LD_A(0x47);
    CALL(aBattleBGEffect_SetLCDStatCustoms1);
    LDH_A_addr(hLYOverrideEnd);
    INC_A;
    LDH_addr_A(hLYOverrideEnd);
    LD_HL(BG_EFFECT_STRUCT_PARAM);
    ADD_HL_BC;
    LD_A_hl;
    LD_hl(0x0);
    LD_HL(BG_EFFECT_STRUCT_BATTLE_TURN);
    ADD_HL_BC;
    LD_hl_A;
    RET;

one_dmg:

    LD_HL(BG_EFFECT_STRUCT_BATTLE_TURN);
    ADD_HL_BC;
    LD_A_hl;
    AND_A(0xf);
    IF_Z goto okay_1_dmg;
    DEC_hl;
    RET;

okay_1_dmg:

    LD_A_hl;
    SWAP_A;
    OR_A_hl;
    LD_hl_A;
    CALL(aBattleBGEffect_GetFirstDMGPal);
    IF_C goto okay_2_dmg;
    CALL(aBGEffect_FillLYOverridesBackup);
    RET;

okay_2_dmg:

    LD_HL(BG_EFFECT_STRUCT_PARAM);
    ADD_HL_BC;
    DEC_hl;
    RET;

two_dmg:

    CALL(aBattleBGEffects_ResetVideoHRAM);
    LD_A(0b11100100);
    LDH_addr_A(rBGP);
    CALL(aEndBattleBGEffect);
    RET;

cgb:

    PUSH_DE;
    LD_DE(mBGEffect_RapidCyclePals_Jumptable_CGB);
    CALL(aBatttleBGEffects_GetNamedJumptablePointer);
    POP_DE;
    JP_hl;

Jumptable_CGB:

    if (REG_BC == 0) goto zero_cgb;
    if (REG_BC == 1) goto one_cgb;
    if (REG_BC == 2) goto two_cgb;
    if (REG_BC == 3) goto three_cgb;
    if (REG_BC == 4) goto four_cgb;

zero_cgb:

    CALL(aBGEffect_CheckBattleTurn);
    IF_NZ goto player_turn_cgb;
    CALL(aBattleBGEffects_IncAnonJumptableIndex);
    CALL(aBattleBGEffects_IncAnonJumptableIndex);

player_turn_cgb:

    CALL(aBattleBGEffects_IncAnonJumptableIndex);
    LD_HL(BG_EFFECT_STRUCT_PARAM);
    ADD_HL_BC;
    LD_A_hl;
    LD_hl(0x0);
    LD_HL(BG_EFFECT_STRUCT_BATTLE_TURN);
    ADD_HL_BC;
    LD_hl_A;
    RET;

one_cgb:

    LD_HL(BG_EFFECT_STRUCT_BATTLE_TURN);
    ADD_HL_BC;
    LD_A_hl;
    AND_A(0xf);
    IF_Z goto okay_1_cgb;
    DEC_hl;
    RET;

okay_1_cgb:

    LD_A_hl;
    SWAP_A;
    OR_A_hl;
    LD_hl_A;
    CALL(aBattleBGEffect_GetFirstDMGPal);
    IF_C goto okay_2_cgb;
    CALL(aBGEffects_LoadBGPal0_OBPal1);
    RET;

okay_2_cgb:

    LD_HL(BG_EFFECT_STRUCT_PARAM);
    ADD_HL_BC;
    DEC_hl;
    RET;

two_cgb:

    LD_A(0xe4);
    CALL(aBGEffects_LoadBGPal0_OBPal1);
    CALL(aEndBattleBGEffect);
    RET;

three_cgb:

    LD_HL(BG_EFFECT_STRUCT_BATTLE_TURN);
    ADD_HL_BC;
    LD_A_hl;
    AND_A(0xf);
    IF_Z goto okay_3_cgb;
    DEC_hl;
    RET;

okay_3_cgb:

    LD_A_hl;
    SWAP_A;
    OR_A_hl;
    LD_hl_A;
    CALL(aBattleBGEffect_GetFirstDMGPal);
    IF_C goto okay_4_cgb;
    CALL(aBGEffects_LoadBGPal1_OBPal0);
    RET;

okay_4_cgb:

    LD_HL(BG_EFFECT_STRUCT_PARAM);
    ADD_HL_BC;
    DEC_hl;
    RET;

four_cgb:

    LD_A(0xe4);
    CALL(aBGEffects_LoadBGPal1_OBPal0);
    CALL(aEndBattleBGEffect);
    RET;
}

void BGEffects_LoadBGPal0_OBPal1(void) {
    SET_PC(aBGEffects_LoadBGPal0_OBPal1);
    LD_H_A;
    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(MBANK(awBGPals1));
    LDH_addr_A(rSVBK);
    LD_A_H;
    PUSH_BC;
    PUSH_AF;
    LD_HL(wBGPals2);
    LD_DE(wBGPals1);
    LD_B_A;
    LD_C(0x1);
    CALL(aCopyPals);
    LD_HL(wOBPals2 + PALETTE_SIZE * 1);
    LD_DE(wOBPals1 + PALETTE_SIZE * 1);
    POP_AF;
    LD_B_A;
    LD_C(0x1);
    CALL(aCopyPals);
    POP_BC;
    POP_AF;
    LDH_addr_A(rSVBK);
    LD_A(TRUE);
    LDH_addr_A(hCGBPalUpdate);
    RET;
}

void BGEffects_LoadBGPal1_OBPal0(void) {
    SET_PC(aBGEffects_LoadBGPal1_OBPal0);
    LD_H_A;
    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(MBANK(awBGPals1));
    LDH_addr_A(rSVBK);
    LD_A_H;
    PUSH_BC;
    PUSH_AF;
    LD_HL(wBGPals2 + PALETTE_SIZE * 1);
    LD_DE(wBGPals1 + PALETTE_SIZE * 1);
    LD_B_A;
    LD_C(0x1);
    CALL(aCopyPals);
    LD_HL(wOBPals2);
    LD_DE(wOBPals1);
    POP_AF;
    LD_B_A;
    LD_C(0x1);
    CALL(aCopyPals);
    POP_BC;
    POP_AF;
    LDH_addr_A(rSVBK);
    LD_A(TRUE);
    LDH_addr_A(hCGBPalUpdate);
    RET;
}

void BattleBGEffect_GetFirstDMGPal(void) {
    SET_PC(aBattleBGEffect_GetFirstDMGPal);
    LD_HL(BG_EFFECT_STRUCT_PARAM);
    ADD_HL_BC;
    LD_A_hl;
    INC_hl;
    return BattleBGEffect_GetNextDMGPal();
}

void BattleBGEffect_GetNextDMGPal(void) {
    SET_PC(aBattleBGEffect_GetNextDMGPal);
    LD_L_A;
    LD_H(0);
    ADD_HL_DE;
    LD_A_hl;
    CP_A(-1);
    IF_Z goto quit;
    CP_A(-2);
    IF_NZ goto repeat;
    LD_A_de;
    LD_HL(BG_EFFECT_STRUCT_PARAM);
    ADD_HL_BC;
    LD_hl(0x0);

repeat:

    AND_A_A;
    RET;

quit:

    SCF;
    RET;
}

void BattleBGEffects_ClearLYOverrides(void) {
    SET_PC(aBattleBGEffects_ClearLYOverrides);
    XOR_A_A;
    return BattleBGEffects_SetLYOverrides();
}

void BattleBGEffects_SetLYOverrides(void) {
    SET_PC(aBattleBGEffects_SetLYOverrides);
    LD_HL(wLYOverrides);
    LD_E(0x99);

loop1:

    LD_hli_A;
    DEC_E;
    IF_NZ goto loop1;
    LD_HL(wLYOverridesBackup);
    LD_E(0x91);

loop2:

    LD_hli_A;
    DEC_E;
    IF_NZ goto loop2;
    RET;
}

void BattleBGEffect_SetLCDStatCustoms1(void) {
    SET_PC(aBattleBGEffect_SetLCDStatCustoms1);
    LDH_addr_A(hLCDCPointer);
    CALL(aBGEffect_CheckBattleTurn);
    IF_NZ goto player_turn;
    LD_DE((0x00 << 8) | 0x36);
    goto okay;

player_turn:

    LD_DE((0x2f << 8) | 0x5e);

okay:

    LD_A_D;
    LDH_addr_A(hLYOverrideStart);
    LD_A_E;
    LDH_addr_A(hLYOverrideEnd);
    RET;
}

void BattleBGEffect_SetLCDStatCustoms2(void) {
    SET_PC(aBattleBGEffect_SetLCDStatCustoms2);
    LDH_addr_A(hLCDCPointer);
    CALL(aBGEffect_CheckBattleTurn);
    IF_NZ goto player_turn;
    LD_DE((0x00 << 8) | 0x36);
    goto okay;

player_turn:

    LD_DE((0x2d << 8) | 0x5e);

okay:

    LD_A_D;
    LDH_addr_A(hLYOverrideStart);
    LD_A_E;
    LDH_addr_A(hLYOverrideEnd);
    RET;
}

void BattleAnim_ResetLCDStatCustom(void) {
    SET_PC(aBattleAnim_ResetLCDStatCustom);
    XOR_A_A;
    LDH_addr_A(hLYOverrideStart);
    LDH_addr_A(hLYOverrideEnd);
    CALL(aBattleBGEffects_ClearLYOverrides);
    XOR_A_A;
    LDH_addr_A(hLCDCPointer);
    CALL(aEndBattleBGEffect);
    RET;
}

void BattleBGEffects_ResetVideoHRAM(void) {
    SET_PC(aBattleBGEffects_ResetVideoHRAM);
    XOR_A_A;
    LDH_addr_A(hLCDCPointer);
    LD_A(0b11100100);
    LDH_addr_A(rBGP);
    LD_addr_A(wBGP);
    LD_addr_A(wOBP1);
    LDH_addr_A(hLYOverrideStart);
    LDH_addr_A(hLYOverrideEnd);
    CALL(aBattleBGEffects_ClearLYOverrides);
    RET;
}

void DeformScreen(void) {
    SET_PC(aDeformScreen);
    PUSH_BC;
    XOR_A_A;
    LD_addr_A(wBattleSineWaveTempProgress);
    LD_A_E;
    LD_addr_A(wBattleSineWaveTempOffset);
    LD_A_D;
    LD_addr_A(wBattleSineWaveTempAmplitude);
    LD_A(0x80);
    LD_addr_A(wBattleSineWaveTempTimer);
    LD_BC(wLYOverridesBackup);

loop:

    LDH_A_addr(hLYOverrideStart);
    CP_A_C;
    IF_NC goto next;
    LDH_A_addr(hLYOverrideEnd);
    CP_A_C;
    IF_C goto next;
    LD_A_addr(wBattleSineWaveTempAmplitude);
    LD_D_A;
    LD_A_addr(wBattleSineWaveTempProgress);
    CALL(aBattleBGEffects_Sine);
    LD_bc_A;

next:

    INC_BC;
    LD_A_addr(wBattleSineWaveTempOffset);
    LD_HL(wBattleSineWaveTempProgress);
    ADD_A_hl;
    LD_hl_A;
    LD_HL(wBattleSineWaveTempTimer);
    DEC_hl;
    IF_NZ goto loop;
    POP_BC;
    RET;
}

void InitSurfWaves(void) {
    SET_PC(aInitSurfWaves);
    PUSH_BC;
    XOR_A_A;
    LD_addr_A(wBattleSineWaveTempProgress);
    LD_A_E;
    LD_addr_A(wBattleSineWaveTempOffset);
    LD_A_D;
    LD_addr_A(wBattleSineWaveTempAmplitude);
    LD_A(0x40);
    LD_addr_A(wBattleSineWaveTempTimer);
    LD_BC(wSurfWaveBGEffect);

loop:

    LD_A_addr(wBattleSineWaveTempAmplitude);
    LD_D_A;
    LD_A_addr(wBattleSineWaveTempProgress);
    CALL(aBattleBGEffects_Sine);
    LD_bc_A;
    INC_BC;
    LD_A_addr(wBattleSineWaveTempOffset);
    LD_HL(wBattleSineWaveTempProgress);
    ADD_A_hl;
    LD_hl_A;
    LD_HL(wBattleSineWaveTempTimer);
    DEC_hl;
    IF_NZ goto loop;
    POP_BC;
    RET;
}

void DeformWater(void) {
    SET_PC(aDeformWater);
    PUSH_BC;
    LD_addr_A(wBattleSineWaveTempTimer);
    LD_A_E;
    LD_addr_A(wBattleSineWaveTempOffset);
    LD_A_D;
    LD_addr_A(wBattleSineWaveTempAmplitude);
    CALL(aDeformWater_GetLYOverrideBackupAddrOffset);
    LD_HL(wLYOverridesBackup);
    ADD_HL_DE;
    LD_C_L;
    LD_B_H;

loop:

    LD_A_addr(wBattleSineWaveTempTimer);
    AND_A_A;
    IF_Z goto done;
    DEC_A;
    LD_addr_A(wBattleSineWaveTempTimer);
    PUSH_AF;
    LD_A_addr(wBattleSineWaveTempAmplitude);
    LD_D_A;
    LD_A_addr(wBattleSineWaveTempOffset);
    PUSH_HL;
    CALL(aBattleBGEffects_Sine);
    LD_E_A;
    POP_HL;
    LDH_A_addr(hLYOverrideEnd);
    CP_A_C;
    IF_C goto skip1;
    LD_A_E;
    LD_bc_A;
    INC_BC;

skip1:

    LDH_A_addr(hLYOverrideStart);
    CP_A_L;
    IF_NC goto skip2;
    LD_hl_E;
    DEC_HL;

skip2:

    LD_A_addr(wBattleSineWaveTempOffset);
    ADD_A(0x4);
    LD_addr_A(wBattleSineWaveTempOffset);
    POP_AF;
    goto loop;

done:

    POP_BC;
    AND_A_A;
    RET;

GetLYOverrideBackupAddrOffset:

    LDH_A_addr(hLYOverrideStart);
    LD_E_A;
    LD_A_addr(wBattleSineWaveTempProgress);
    ADD_A_E;
    LD_E_A;
    LD_D(0);
    RET;
}

void BattleBGEffect_WavyScreenFX(void) {
    SET_PC(aBattleBGEffect_WavyScreenFX);
    PUSH_BC;
    LDH_A_addr(hLYOverrideStart);
    LD_L_A;
    INC_A;
    LD_E_A;
    LD_H(HIGH(wLYOverridesBackup));
    LD_D_H;
    LDH_A_addr(hLYOverrideEnd);
    SUB_A_L;
    AND_A_A;
    IF_Z goto done;
    LD_C_A;
    LD_A_hl;
    PUSH_AF;

loop:

    LD_A_de;
    INC_DE;
    LD_hli_A;
    DEC_C;
    IF_NZ goto loop;
    POP_AF;
    LD_hl_A;

done:

    POP_BC;
    RET;
}

void BGEffect_FillLYOverridesBackup(void) {
    SET_PC(aBGEffect_FillLYOverridesBackup);
    PUSH_AF;
    LD_H(HIGH(wLYOverridesBackup));
    LDH_A_addr(hLYOverrideStart);
    LD_L_A;
    LDH_A_addr(hLYOverrideEnd);
    SUB_A_L;
    LD_D_A;
    POP_AF;

loop:

    LD_hli_A;
    DEC_D;
    IF_NZ goto loop;
    RET;
}

void BGEffect_DisplaceLYOverridesBackup(void) {
    SET_PC(aBGEffect_DisplaceLYOverridesBackup);
    // e = a
    // d = [hLYOverrideEnd] - [hLYOverrideStart] - a
    PUSH_AF;
    LD_E_A;
    LDH_A_addr(hLYOverrideStart);
    LD_L_A;
    LDH_A_addr(hLYOverrideEnd);
    SUB_A_L;
    SUB_A_E;
    LD_D_A;
    LD_H(HIGH(wLYOverridesBackup));
    LDH_A_addr(hLYOverrideStart);
    LD_L_A;
    LD_A(0x90);

loop:

    LD_hli_A;
    DEC_E;
    IF_NZ goto loop;
    POP_AF;
    XOR_A(0xff);

loop2:

    LD_hli_A;
    DEC_D;
    IF_NZ goto loop2;
    RET;
}

void BGEffect_CheckBattleTurn(void) {
    SET_PC(aBGEffect_CheckBattleTurn);
    LD_HL(BG_EFFECT_STRUCT_BATTLE_TURN);
    ADD_HL_BC;
    LDH_A_addr(hBattleTurn);
    AND_A(0x1);
    XOR_A_hl;
    RET;
}

void BGEffect_CheckFlyDigStatus(void) {
    SET_PC(aBGEffect_CheckFlyDigStatus);
    LD_HL(BG_EFFECT_STRUCT_BATTLE_TURN);
    ADD_HL_BC;
    LDH_A_addr(hBattleTurn);
    AND_A(0x1);
    XOR_A_hl;
    IF_NZ goto player;
    LD_A_addr(wEnemySubStatus3);  // EnemySubStatus3
    AND_A(1 << SUBSTATUS_FLYING | 1 << SUBSTATUS_UNDERGROUND);
    RET;

player:

    LD_A_addr(wPlayerSubStatus3);  // PlayerSubStatus3
    AND_A(1 << SUBSTATUS_FLYING | 1 << SUBSTATUS_UNDERGROUND);
    RET;
}

void BattleBGEffects_CheckSGB(void) {
    SET_PC(aBattleBGEffects_CheckSGB);
    LDH_A_addr(hSGB);
    AND_A_A;
    RET;
}

void BattleBGEffects_Sine(void) {
    SET_PC(aBattleBGEffects_Sine);
    LD_E_A;
    CALLFAR(aBattleAnim_Sine_e);
    LD_A_E;
    RET;
}

void BattleBGEffects_Cosine(void) {
    SET_PC(aBattleBGEffects_Cosine);
    LD_E_A;
    CALLFAR(aBattleAnim_Cosine_e);
    LD_A_E;
    RET;
}
