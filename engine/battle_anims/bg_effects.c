#include "../../constants.h"
#include "bg_effects.h"
#include "core.h"
#include "functions.h"
#include "../../home/text.h"
#include "../../home/delay.h"
#include "../../home/palettes.h"
#include "../../home/sine.h"

// static int8_t* lBattlePicResizeTempPointer;

// const_def ['?']
// const ['BGSQUARE_SIX']
// const ['BGSQUARE_FOUR']
// const ['BGSQUARE_TWO']
// const ['BGSQUARE_SEVEN']
// const ['BGSQUARE_FIVE']
// const ['BGSQUARE_THREE']
enum {
    BGSQUARE_SIX,
    BGSQUARE_FOUR,
    BGSQUARE_TWO,
    BGSQUARE_SEVEN,
    BGSQUARE_FIVE,
    BGSQUARE_THREE,
};


struct BGSquare
{
    uint8_t w: 4;
    uint8_t h: 4;
    const uint8_t* const ptr;
};

static void EndBattleBGEffect(struct BattleBGEffect* bc);
static void DoBattleBGEffectFunction(struct BattleBGEffect* bc);

static void BattleBGEffects_IncAnonJumptableIndex(struct BattleBGEffect* bc);

static void BattleBGEffect_End(struct BattleBGEffect* bc);
static void BattleBGEffect_FlashInverted(struct BattleBGEffect* bc);
static void BattleBGEffect_FlashWhite(struct BattleBGEffect* bc);
static void BattleBGEffect_FlashContinue(struct BattleBGEffect* bc, const uint8_t* de);
static void BattleBGEffect_WhiteHues(struct BattleBGEffect* bc);
static void BattleBGEffect_BlackHues(struct BattleBGEffect* bc);
static void BattleBGEffect_AlternateHues(struct BattleBGEffect* bc);
static void BattleBGEffect_CycleOBPalsGrayAndYellow(struct BattleBGEffect* bc);
static void BattleBGEffect_CycleMidOBPalsGrayAndYellow(struct BattleBGEffect* bc);
static void BattleBGEffect_CycleBGPals_Inverted(struct BattleBGEffect* bc);
static void BattleBGEffect_HideMon(struct BattleBGEffect* bc);
static void BattleBGEffect_ShowMon(struct BattleBGEffect* bc);
static void BattleBGEffect_BattlerObj_1Row(struct BattleBGEffect* bc);
static void BattleBGEffect_BattlerObj_2Row(struct BattleBGEffect* bc);
static void BattleBGEffect_RemoveMon(struct BattleBGEffect* bc);
static void BattleBGEffect_EnterMon(struct BattleBGEffect* bc);
static void BattleBGEffect_ReturnMon(struct BattleBGEffect* bc);
static void BattleBGEffect_RunPicResizeScript(struct BattleBGEffect* bc, const uint8_t* de);
static void BattleBGEffect_Surf(struct BattleBGEffect* bc);
static void BattleBGEffect_Whirlpool(struct BattleBGEffect* bc);
static void BattleBGEffect_StartWater(struct BattleBGEffect* bc);
static void BattleBGEffect_Water(struct BattleBGEffect* bc);
static void BattleBGEffect_EndWater(struct BattleBGEffect* bc);
static void BattleBGEffect_Psychic(struct BattleBGEffect* bc);
static void BattleBGEffect_Teleport(struct BattleBGEffect* bc);
static void BattleBGEffect_NightShade(struct BattleBGEffect* bc);
static void BattleBGEffect_DoubleTeam(struct BattleBGEffect* bc);
static void BattleBGEffect_AcidArmor(struct BattleBGEffect* bc);
static void BattleBGEffect_Withdraw(struct BattleBGEffect* bc);
static void BattleBGEffect_Dig(struct BattleBGEffect* bc);
static void BattleBGEffect_Tackle(struct BattleBGEffect* bc);
static void BattleBGEffect_BodySlam(struct BattleBGEffect* bc);
static void Tackle_MoveForward(struct BattleBGEffect* bc);
static void Tackle_ReturnMove(struct BattleBGEffect* bc);
static void Rollout_FillLYOverridesBackup(uint8_t a);
static void BattleBGEffect_BetaPursuit(struct BattleBGEffect* bc);
static void VitalThrow_MoveBackwards(struct BattleBGEffect* bc);
static void BattleBGEffect_VitalThrow(struct BattleBGEffect* bc);
static void BattleBGEffect_WobbleMon(struct BattleBGEffect* bc);
static void BattleBGEffect_Flail(struct BattleBGEffect* bc);
static void BattleBGEffect_WaveDeformMon(struct BattleBGEffect* bc);
static void BattleBGEffect_BounceDown(struct BattleBGEffect* bc);
static void BattleBGEffect_FadeMonsToBlackRepeating(struct BattleBGEffect* bc);
static void BattleBGEffect_RapidFlash(struct BattleBGEffect* bc);
static void BattleBGEffect_FadeMonToLight(struct BattleBGEffect* bc);
static void BattleBGEffect_FadeMonToBlack(struct BattleBGEffect* bc);
static void BattleBGEffect_FadeMonToLightRepeating(struct BattleBGEffect* bc);
static void BattleBGEffect_FadeMonToBlackRepeating(struct BattleBGEffect* bc);
static void BattleBGEffect_CycleMonLightDarkRepeating(struct BattleBGEffect* bc);
static void BattleBGEffect_FlashMonRepeating(struct BattleBGEffect* bc);
static void BattleBGEffect_FadeMonToWhiteWaitFadeBack(struct BattleBGEffect* bc);
static void BattleBGEffect_FadeMonFromWhite(struct BattleBGEffect* bc);
static void BattleBGEffect_VibrateMon(struct BattleBGEffect* bc);
static void BattleBGEffect_WobblePlayer(struct BattleBGEffect* bc);
static void BattleBGEffect_Rollout(struct BattleBGEffect* bc);
static void BattleBGEffect_ShakeScreenX(struct BattleBGEffect* bc);
static void BattleBGEffect_ShakeScreenY(struct BattleBGEffect* bc);
static u8_flag_s BattleBGEffects_GetShakeAmount(struct BattleBGEffect* bc);
static void BattleBGEffect_WobbleScreen(struct BattleBGEffect* bc);
static u8_flag_s BattleBGEffect_GetNthDMGPal(struct BattleBGEffect* bc, const uint8_t* de);
static void BGEffect_RapidCyclePals(struct BattleBGEffect* bc, const uint8_t* de);
static void BGEffects_LoadBGPal0_OBPal1(uint8_t a);
static void BGEffects_LoadBGPal1_OBPal0(uint8_t a);
static u8_flag_s BattleBGEffect_GetFirstDMGPal(struct BattleBGEffect* bc, const uint8_t* de);
static u8_flag_s BattleBGEffect_GetNextDMGPal(struct BattleBGEffect* bc, const uint8_t* de, uint8_t a);
static void BattleBGEffects_ClearLYOverrides(void);
static void BattleBGEffects_SetLYOverrides(uint8_t a);
static void BattleBGEffect_SetLCDStatCustoms1(struct BattleBGEffect* bc, uint8_t a);
static void BattleBGEffect_SetLCDStatCustoms2(struct BattleBGEffect* bc, uint8_t a);
static void BattleAnim_ResetLCDStatCustom(struct BattleBGEffect* bc);
static void DeformScreen(uint8_t d, uint8_t e);
static void InitSurfWaves(uint8_t d, uint8_t e);
static void DeformWater(uint8_t d, uint8_t e, uint8_t a);
static void BattleBGEffect_WavyScreenFX(void);
static void BGEffect_FillLYOverridesBackup(uint8_t a);
static void BGEffect_DisplaceLYOverridesBackup(uint8_t a);
static uint8_t BGEffect_CheckBattleTurn(struct BattleBGEffect* bc);
static bool BGEffect_CheckFlyDigStatus(struct BattleBGEffect* bc);

static bool BattleBGEffects_CheckSGB(void);

//  BG effects for use in battle animations.

void ExecuteBGEffects(void) {
    // SET_PC(aExecuteBGEffects);
    // LD_HL(wActiveBGEffects);
    struct BattleBGEffect* hl = wram->wBGEffect;
    // LD_E(NUM_BG_EFFECTS);
    uint8_t e = NUM_BG_EFFECTS;

    do {
    // loop:

        // LD_A_hl;
        // AND_A_A;
        // IF_Z goto next;
        if(hl->function != 0) {
            // LD_C_L;
            // LD_B_H;
            // PUSH_HL;
            // PUSH_DE;
            // CALL(aDoBattleBGEffectFunction);
            DoBattleBGEffectFunction(hl);
            // POP_DE;
            // POP_HL;
        }
    // next:

        // LD_BC(BG_EFFECT_STRUCT_LENGTH);
        // ADD_HL_BC;
        hl++;
        // DEC_E;
        // IF_NZ goto loop;
    } while(--e != 0);
    // RET;
}

bool QueueBGEffect(void) {
    // SET_PC(aQueueBGEffect);
    // LD_HL(wActiveBGEffects);
    struct BattleBGEffect* hl = wram->wBGEffect;
    // LD_E(NUM_BG_EFFECTS);
    uint8_t e = NUM_BG_EFFECTS;

    do {
    // loop:
        // LD_A_hl;
        // AND_A_A;
        // IF_Z goto load;
        if(hl->function == 0) {
        // load:
            // LD_C_L;
            // LD_B_H;
            // LD_HL(BG_EFFECT_STRUCT_FUNCTION);
            // ADD_HL_BC;
            // LD_A_addr(wBattleBGEffectTempID);
            // LD_hli_A;
            hl->function = wram->wBattleBGEffectTempID;
            // LD_A_addr(wBattleBGEffectTempJumptableIndex);
            // LD_hli_A;
            hl->jumptableIndex = wram->wBattleBGEffectTempJumptableIndex;
            // LD_A_addr(wBattleBGEffectTempTurn);
            // LD_hli_A;
            hl->battleTurn = wram->wBattleBGEffectTempTurn;
            // LD_A_addr(wBattleBGEffectTempParam);
            // LD_hl_A;
            hl->param = wram->wBattleBGEffectTempParam;
            // RET;
            return false;
        }
        // LD_BC(BG_EFFECT_STRUCT_LENGTH);
        // ADD_HL_BC;
        hl++;
        // DEC_E;
        // IF_NZ goto loop;
    } while(--e != 0);
    // SCF;
    // RET;
    return true;
}

static void EndBattleBGEffect(struct BattleBGEffect* bc) {
    // SET_PC(aEndBattleBGEffect);
    // LD_HL(BG_EFFECT_STRUCT_FUNCTION);
    // ADD_HL_BC;
    // LD_hl(0);
    // RET;
    bc->function = 0;
}

static void DoBattleBGEffectFunction(struct BattleBGEffect* bc) {
    // SET_PC(aDoBattleBGEffectFunction);
    // LD_HL(BG_EFFECT_STRUCT_FUNCTION);
    // ADD_HL_BC;
    // LD_E_hl;
    // LD_D(0);
    // LD_HL(mBattleBGEffects);
    // ADD_HL_DE;
    // ADD_HL_DE;
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // JP_hl;
    BattleBGEffects[bc->function](bc);
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

void(*const BattleBGEffects[])(struct BattleBGEffect*) = {
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
    BattleBGEffect_End, // BattleBGEffect_BetaSendOutMon1_Conv,
    BattleBGEffect_End, // BattleBGEffect_BetaSendOutMon2_Conv,
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

void BattleBGEffect_End(struct BattleBGEffect* bc) {
    // SET_PC(aBattleBGEffect_End);
    // CALL(aEndBattleBGEffect);
    // RET;
    return EndBattleBGEffect(bc);
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

static void BattleBGEffects_IncAnonJumptableIndex(struct BattleBGEffect* bc) {
    // SET_PC(aBattleBGEffects_IncAnonJumptableIndex);
    // LD_HL(BG_EFFECT_STRUCT_JT_INDEX);
    // ADD_HL_BC;
    // INC_hl;
    bc->jumptableIndex++;
    // RET;
}

#define dc(a, b, c, d) ((a & 0x3) << 6) | ((b & 0x3) << 4) | ((c & 0x3) << 2) | (d & 0x3)

static void BattleBGEffect_FlashInverted(struct BattleBGEffect* bc) {
    static const uint8_t inverted[] = {
        dc(3, 2, 1, 0),
        dc(0, 1, 2, 3),
    };
    // SET_PC(aBattleBGEffect_FlashInverted);
    // LD_DE(mBattleBGEffect_FlashInverted_inverted);
    // JP(mBattleBGEffect_FlashContinue);
    return BattleBGEffect_FlashContinue(bc, inverted);
}

static void BattleBGEffect_FlashWhite(struct BattleBGEffect* bc) {
    static const uint8_t white[] = {
        dc(3, 2, 1, 0),
        dc(0, 0, 0, 0)
    };
    // SET_PC(aBattleBGEffect_FlashWhite);
    // LD_DE(mBattleBGEffect_FlashWhite_white);
    // JP(mBattleBGEffect_FlashContinue);
    return BattleBGEffect_FlashContinue(bc, white);
}

static void BattleBGEffect_FlashContinue(struct BattleBGEffect* bc, const uint8_t* de) {
    // SET_PC(aBattleBGEffect_FlashContinue);
    //  current timer, flash duration, number of flashes
    // LD_A(0x1);
    // LD_addr_A(wBattleBGEffectTempID);  // unused?
    wram->wBattleBGEffectTempID = 0x1;
    // LD_HL(BG_EFFECT_STRUCT_JT_INDEX);
    // ADD_HL_BC;
    // LD_A_hl;
    // AND_A_A;
    // IF_Z goto init;
    if(bc->jumptableIndex != 0){
        // DEC_hl;
        bc->jumptableIndex--;
        // RET;
        return;
    }

// init:
    // LD_HL(BG_EFFECT_STRUCT_BATTLE_TURN);
    // ADD_HL_BC;
    // LD_A_hl;
    // LD_HL(BG_EFFECT_STRUCT_JT_INDEX);
    // ADD_HL_BC;
    // LD_hl_A;
    bc->jumptableIndex = bc->battleTurn;
    // LD_HL(BG_EFFECT_STRUCT_PARAM);
    // ADD_HL_BC;
    // LD_A_hl;
    // AND_A_A;
    // IF_NZ goto apply_pal;
    if(bc->param == 0){
        // CALL(aEndBattleBGEffect);
        EndBattleBGEffect(bc);
        // RET;
        return;
    }

// apply_pal:
    // DEC_A;
    // LD_hl_A;
    bc->param--;
    // AND_A(1);
    // LD_L_A;
    // LD_H(0);
    // ADD_HL_DE;
    // LD_A_hl;
    // LD_addr_A(wBGP);
    wram->wBGP = de[bc->param & 1];
    // RET;
}

static void BattleBGEffect_WhiteHues(struct BattleBGEffect* bc) {
    static const uint8_t Pals[] = {
        dc(3, 2, 1, 0),
        dc(3, 2, 0, 0),
        dc(3, 1, 0, 0),
        (uint8_t)-1
    };
    // SET_PC(aBattleBGEffect_WhiteHues);
    // LD_DE(mBattleBGEffect_WhiteHues_Pals);
    // CALL(aBattleBGEffect_GetNthDMGPal);
    u8_flag_s res = BattleBGEffect_GetNthDMGPal(bc, Pals);
    // IF_C goto quit;
    if(!res.flag){
        // LD_addr_A(wBGP);
        wram->wBGP = res.a;
        // RET;
        return;
    }

// quit:
    // CALL(aEndBattleBGEffect);
    EndBattleBGEffect(bc);
    // RET;
}

static void BattleBGEffect_BlackHues(struct BattleBGEffect* bc) {
    // SET_PC(aBattleBGEffect_BlackHues);
    static const uint8_t Pals[] = {
        dc(3, 2, 1, 0),
        dc(3, 3, 1, 0),
        dc(3, 3, 2, 0),
        (uint8_t)-1
    };
    // LD_DE(mBattleBGEffect_BlackHues_Pals);
    // CALL(aBattleBGEffect_GetNthDMGPal);
    u8_flag_s res = BattleBGEffect_GetNthDMGPal(bc, Pals);
    // IF_C goto quit;
    if(!res.flag){
        // LD_addr_A(wBGP);
        wram->wBGP = res.a;
        // RET;
        return;
    }

// quit:
    // CALL(aEndBattleBGEffect);
    EndBattleBGEffect(bc);
    // RET;
}

static void BattleBGEffect_AlternateHues(struct BattleBGEffect* bc) {
    // SET_PC(aBattleBGEffect_AlternateHues);
    static const uint8_t Pals[] = {
        dc(3, 2, 1, 0),
        dc(3, 3, 2, 0),
        dc(3, 3, 3, 0),
        dc(3, 3, 2, 0),
        dc(3, 2, 1, 0),
        dc(2, 1, 0, 0),
        dc(1, 0, 0, 0),
        dc(2, 1, 0, 0),
        (uint8_t)-2
    };
    // LD_DE(mBattleBGEffect_AlternateHues_Pals);
    // CALL(aBattleBGEffect_GetNthDMGPal);
    u8_flag_s res = BattleBGEffect_GetNthDMGPal(bc, Pals);
    // IF_C goto quit;
    if(!res.flag){
        // LD_addr_A(wBGP);
        wram->wBGP = res.a;
        // LD_addr_A(wOBP1);
        wram->wOBP1 = res.a;
        // RET;
        return;
    }

// quit:
    // CALL(aEndBattleBGEffect);
    EndBattleBGEffect(bc);
    // RET;
}

static void BattleBGEffect_CycleOBPalsGrayAndYellow(struct BattleBGEffect* bc) {
    static const uint8_t PalsCGB[] = {
        dc(3, 2, 1, 0),
        dc(2, 1, 0, 0),
        (uint8_t)-2
    };
    static const uint8_t PalsSGB[] = {
        dc(3, 3, 0, 0),
        dc(3, 0, 0, 0),
        (uint8_t)-2
    };
    // SET_PC(aBattleBGEffect_CycleOBPalsGrayAndYellow);
    // CALL(aBattleBGEffects_CheckSGB);
    // IF_NZ goto sgb;
    // LD_DE(mBattleBGEffect_CycleOBPalsGrayAndYellow_PalsCGB);
    // goto okay;

// sgb:
    // LD_DE(mBattleBGEffect_CycleOBPalsGrayAndYellow_PalsSGB);

// okay:
    const uint8_t* de = (BattleBGEffects_CheckSGB())? PalsSGB: PalsCGB;
    // CALL(aBattleBGEffect_GetNthDMGPal);
    u8_flag_s res = BattleBGEffect_GetNthDMGPal(bc, de);
    // LD_addr_A(wOBP0);
    wram->wOBP0 = res.a;
    // RET;
}

static void BattleBGEffect_CycleMidOBPalsGrayAndYellow(struct BattleBGEffect* bc) {
    static const uint8_t PalsCGB[] = {
        dc(3, 2, 1, 0),
        dc(3, 1, 2, 0),
        (uint8_t)-2
    };
    static const uint8_t PalsSGB[] = {
        dc(3, 3, 0, 0),
        dc(3, 0, 3, 0),
        (uint8_t)-2
    };
    // SET_PC(aBattleBGEffect_CycleMidOBPalsGrayAndYellow);
    // CALL(aBattleBGEffects_CheckSGB);
    // IF_NZ goto sgb;
    // LD_DE(mBattleBGEffect_CycleMidOBPalsGrayAndYellow_PalsCGB);
    // goto okay;

// sgb:
    // LD_DE(mBattleBGEffect_CycleMidOBPalsGrayAndYellow_PalsSGB);

// okay:
    const uint8_t* de = (BattleBGEffects_CheckSGB())? PalsSGB: PalsCGB;
    // CALL(aBattleBGEffect_GetNthDMGPal);
    u8_flag_s res = BattleBGEffect_GetNthDMGPal(bc, de);
    // LD_addr_A(wOBP0);
    wram->wOBP0 = res.a;
    // RET;
}

static void BattleBGEffect_CycleBGPals_Inverted(struct BattleBGEffect* bc) {
    static const uint8_t Pals[] = {
        dc(0, 1, 2, 3),
        dc(1, 2, 0, 3),
        dc(2, 0, 1, 3),
        (uint8_t)-2
    };
    // SET_PC(aBattleBGEffect_CycleBGPals_Inverted);
    // LD_DE(mBattleBGEffect_CycleBGPals_Inverted_Pals);
    // CALL(aBattleBGEffect_GetNthDMGPal);
    u8_flag_s res = BattleBGEffect_GetNthDMGPal(bc, Pals);
    // LD_addr_A(wBGP);
    wram->wBGP = res.a;
    // RET;
}

static void BattleBGEffect_HideMon(struct BattleBGEffect* bc) {
    PEEK("");
    // SET_PC(aBattleBGEffect_HideMon);
    // CALL(aBattleBGEffects_AnonJumptable);
    // uint8_t index = gb_read(REG_BC + BG_EFFECT_STRUCT_JT_INDEX);

// anon_dw:
    switch(bc->jumptableIndex){
        // if (index == 0) goto zero;
        case 0: {
        // zero:
            // CALL(aBattleBGEffects_IncAnonJumptableIndex);
            // PUSH_BC;
            BattleBGEffects_IncAnonJumptableIndex(bc);
            // CALL(aBGEffect_CheckBattleTurn);
            // IF_NZ goto player_side;
            uint8_t* hl;
            uint8_t b, c;
            if(BGEffect_CheckBattleTurn(bc) == 0) {
                // hlcoord(12, 0, wTilemap);
                hl = coord(12, 0, wram->wTilemap);
                // LD_BC((7 << 8) | 7);
                b = 7;
                c = 7;
                // goto got_pointer;
            }
            else {
            // player_side:
                // hlcoord(2, 6, wTilemap);
                hl = coord(2, 6, wram->wTilemap);
                // LD_BC((6 << 8) | 6);
                b = 6;
                c = 6;
            }

        // got_pointer:
            // CALL(aClearBox);
            ClearBox(hl, c, b);
            // POP_BC;
            // XOR_A_A;
            // LDH_addr_A(hBGMapThird);
            hram->hBGMapThird = 0x0;
            // LD_A(0x1);
            // LDH_addr_A(hBGMapMode);
            hram->hBGMapMode = BGMAPMODE_UPDATE_TILES;
            // RET;
        } return;
        // if (index == 1) return BattleBGEffects_IncAnonJumptableIndex();
        case 1: return BattleBGEffects_IncAnonJumptableIndex(bc);
        // if (index == 2) return BattleBGEffects_IncAnonJumptableIndex();
        case 2: return BattleBGEffects_IncAnonJumptableIndex(bc);
        // if (index == 3) return BattleBGEffects_IncAnonJumptableIndex();
        case 3: return BattleBGEffects_IncAnonJumptableIndex(bc);
        // if (index == 4) goto four;
        default:
        case 4: {
        // four:
            // XOR_A_A;
            // LDH_addr_A(hBGMapMode);
            hram->hBGMapMode = BGMAPMODE_NONE;
            // CALL(aEndBattleBGEffect);
            EndBattleBGEffect(bc);
            // RET;
        } return;
    }
}

static void BattleBGEffect_ShowMon(struct BattleBGEffect* bc) {
    PEEK("");
    static const uint8_t PlayerData[] = {
        0, 0x31, 0,
        (uint8_t)-1,
    };

    static const uint8_t EnemyData[] = {
        3, 0x00, 3,
        (uint8_t)-1,
    };
    // SET_PC(aBattleBGEffect_ShowMon);
    // CALL(aBGEffect_CheckFlyDigStatus);
    // IF_Z goto not_flying;
    if(BGEffect_CheckFlyDigStatus(bc)) {
        // CALL(aEndBattleBGEffect);
        EndBattleBGEffect(bc);
        // RET;
        return;
    }

// not_flying:
    // CALL(aBGEffect_CheckBattleTurn);
    // IF_NZ goto player_side;
    // LD_DE(mBattleBGEffect_ShowMon_EnemyData);
    // goto got_pointer;

// player_side:
    // LD_DE(mBattleBGEffect_ShowMon_PlayerData);

// got_pointer:
    // LD_A_E;
    // LD_addr_A(wBattlePicResizeTempPointer);
    // LD_A_D;
    // LD_addr_A(wBattlePicResizeTempPointer + 1);
    const uint8_t* de = (BGEffect_CheckBattleTurn(bc) == 0)? EnemyData: PlayerData;
    // CALL(aBattleBGEffect_RunPicResizeScript);
    BattleBGEffect_RunPicResizeScript(bc, de);
    // RET;
}

static void BattleBGEffect_BattlerObj_1Row(struct BattleBGEffect* bc) {
    PEEK("");
    // SET_PC(aBattleBGEffect_BattlerObj_1Row);
    // CALL(aBattleBGEffects_AnonJumptable);
    // uint8_t index = gb_read(REG_BC + BG_EFFECT_STRUCT_JT_INDEX);


// anon_dw:
    switch(bc->jumptableIndex){
        // if (index == 0) goto zero;
        case 0: {
        // zero:
            // CALL(aBGEffect_CheckFlyDigStatus);
            // IF_Z goto not_flying_digging;
            if(BGEffect_CheckFlyDigStatus(bc)){
                // LD_HL(wLastAnimObjectIndex);
                // INC_hl;
                wram->wLastAnimObjectIndex++;
                // CALL(aEndBattleBGEffect);
                // RET;
                return EndBattleBGEffect(bc);
            }

        // not_flying_digging:
            // CALL(aBattleBGEffects_IncAnonJumptableIndex);
            BattleBGEffects_IncAnonJumptableIndex(bc);
            // PUSH_BC;
            // CALL(aBGEffect_CheckBattleTurn);
            // IF_NZ goto player_side;
            uint8_t a;
            if(BGEffect_CheckBattleTurn(bc) == 0){
                // LD_A(ANIM_OBJ_ENEMYFEET_1ROW);
                // LD_addr_A(wBattleObjectTempID);
                wram->wBattleObjectTempID = ANIM_OBJ_ENEMYFEET_1ROW;
                // LD_A(16 * TILE_WIDTH + 4);
                a = 16 * TILE_WIDTH + 4;
                // goto okay;
            }
            else {
            // player_side:
                // LD_A(ANIM_OBJ_PLAYERHEAD_1ROW);
                // LD_addr_A(wBattleObjectTempID);
                wram->wBattleObjectTempID = ANIM_OBJ_PLAYERHEAD_1ROW;
                // LD_A(6 * TILE_WIDTH);
                a = 6 * TILE_WIDTH;
            }
        // okay:
            // LD_addr_A(wBattleObjectTempXCoord);
            wram->wBattleObjectTempXCoord = a;
            // LD_A(8 * TILE_WIDTH);
            // LD_addr_A(wBattleObjectTempYCoord);
            wram->wBattleObjectTempYCoord = 8 * TILE_WIDTH;
            // XOR_A_A;
            // LD_addr_A(wBattleObjectTempParam);
            wram->wBattleObjectTempParam = 0x0;
            // CALL(av_QueueBattleAnimation);
            v_QueueBattleAnimation();
            // POP_BC;
            // RET;
        } return;
        // if (index == 1) goto one;
        case 1: {
        // one:
            // CALL(aBattleBGEffects_IncAnonJumptableIndex);
            BattleBGEffects_IncAnonJumptableIndex(bc);
            // PUSH_BC;
            // CALL(aBGEffect_CheckBattleTurn);
            // IF_NZ goto player_side_2;
            tile_t* hl;
            uint8_t b, c;
            if(BGEffect_CheckBattleTurn(bc) == 0){
                // hlcoord(12, 6, wTilemap);
                hl = coord(12, 6, wram->wTilemap);
                // LD_BC((1 << 8) | 7);
                b = 1;
                c = 7;
                // goto okay2;
            }
            else {
            // player_side_2:
                // hlcoord(2, 6, wTilemap);
                hl = coord(2, 6, wram->wTilemap);
                // LD_BC((1 << 8) | 6);
                b = 1;
                c = 6;
            }

        // okay2:
            // CALL(aClearBox);
            ClearBox(hl, c, b);
            // LD_A(0x1);
            // LDH_addr_A(hBGMapMode);
            hram->hBGMapMode = BGMAPMODE_UPDATE_TILES;
            // POP_BC;
            // RET;
        } return;
        // if (index == 2) return BattleBGEffects_IncAnonJumptableIndex();
        case 2: return BattleBGEffects_IncAnonJumptableIndex(bc);
        case 3: return BattleBGEffects_IncAnonJumptableIndex(bc);
        case 4: return BattleBGEffects_IncAnonJumptableIndex(bc);
        // if (index == 3) return BattleBGEffects_IncAnonJumptableIndex();
        // if (index == 4) return BattleBGEffects_IncAnonJumptableIndex();
        // if (index == 5) goto five;
        default:
        case 5: {
        // five:
            // XOR_A_A;
            // LDH_addr_A(hBGMapMode);
            hram->hBGMapMode = BGMAPMODE_NONE;
            // CALL(aEndBattleBGEffect);
            EndBattleBGEffect(bc);
            // RET;
        } return;
    }
}

static void BattleBGEffect_BattlerObj_2Row(struct BattleBGEffect* bc) {
    PEEK("");
    // SET_PC(aBattleBGEffect_BattlerObj_2Row);
    // CALL(aBattleBGEffects_AnonJumptable);
    // uint8_t index = gb_read(REG_BC + BG_EFFECT_STRUCT_JT_INDEX);

// anon_dw:
    switch(bc->jumptableIndex){
        // if (index == 0) goto zero;
        case 0: {
        // zero:
            // CALL(aBGEffect_CheckFlyDigStatus);
            // IF_Z goto not_flying_digging;
            if(BGEffect_CheckFlyDigStatus(bc)){
                // LD_HL(wLastAnimObjectIndex);
                // INC_hl;
                wram->wLastAnimObjectIndex++;
                // CALL(aEndBattleBGEffect);
                // RET;
                return EndBattleBGEffect(bc);
            }

        // not_flying_digging:
            // CALL(aBattleBGEffects_IncAnonJumptableIndex);
            BattleBGEffects_IncAnonJumptableIndex(bc);
            // PUSH_BC;
            // CALL(aBGEffect_CheckBattleTurn);
            // IF_NZ goto player_side;
            uint8_t a;
            if(BGEffect_CheckBattleTurn(bc) == 0){
                // LD_A(ANIM_OBJ_ENEMYFEET_2ROW);
                // LD_addr_A(wBattleObjectTempID);
                wram->wBattleObjectTempID = ANIM_OBJ_ENEMYFEET_2ROW;
                // LD_A(16 * TILE_WIDTH + 4);
                a = 16 * TILE_WIDTH + 4;
                // goto okay;
            }
            else {
            // player_side:
                // LD_A(ANIM_OBJ_PLAYERHEAD_2ROW);
                // LD_addr_A(wBattleObjectTempID);
                wram->wBattleObjectTempID = ANIM_OBJ_PLAYERHEAD_2ROW;
                // LD_A(6 * TILE_WIDTH);
                a = 6 * TILE_WIDTH;
            }

        // okay:
            // LD_addr_A(wBattleObjectTempXCoord);
            wram->wBattleObjectTempXCoord = a;
            // LD_A(8 * TILE_WIDTH);
            // LD_addr_A(wBattleObjectTempYCoord);
            wram->wBattleObjectTempYCoord = 8 * TILE_WIDTH;
            // XOR_A_A;
            // LD_addr_A(wBattleObjectTempParam);
            wram->wBattleObjectTempParam = 0x0;
            // CALL(av_QueueBattleAnimation);
            v_QueueBattleAnimation();
            // POP_BC;
            // RET;
        } return;
        // if (index == 1) goto one;
        case 1: {
        // one:
            // CALL(aBattleBGEffects_IncAnonJumptableIndex);
            // PUSH_BC;
            BattleBGEffects_IncAnonJumptableIndex(bc);
            // CALL(aBGEffect_CheckBattleTurn);
            // IF_NZ goto player_side_2;
            tile_t* hl;
            uint8_t b, c;
            if(BGEffect_CheckBattleTurn(bc) == 0){
                // hlcoord(12, 5, wTilemap);
                hl = coord(12, 5, wram->wTilemap);
                // LD_BC((2 << 8) | 7);
                b = 2;
                c = 7;
                // goto okay2;
            }
            else {
            // player_side_2:
                // hlcoord(2, 6, wTilemap);
                hl = coord(2, 6, wram->wTilemap);
                // LD_BC((2 << 8) | 6);
                b = 2;
                c = 6;
            }

        // okay2:
            // CALL(aClearBox);
            ClearBox(hl, c, b);
            // LD_A(0x1);
            // LDH_addr_A(hBGMapMode);
            hram->hBGMapMode = BGMAPMODE_UPDATE_TILES;
            // POP_BC;
            // RET;
        } return;
        // if (index == 2) return BattleBGEffects_IncAnonJumptableIndex();
        case 2: return BattleBGEffects_IncAnonJumptableIndex(bc);
        case 3: return BattleBGEffects_IncAnonJumptableIndex(bc);
        case 4: return BattleBGEffects_IncAnonJumptableIndex(bc);
        // if (index == 3) return BattleBGEffects_IncAnonJumptableIndex();
        // if (index == 4) return BattleBGEffects_IncAnonJumptableIndex();
        // if (index == 5) goto five;
        default:
        case 5: {
        // five:
            // XOR_A_A;
            // LDH_addr_A(hBGMapMode);
            hram->hBGMapMode = BGMAPMODE_NONE;
            // CALL(aEndBattleBGEffect);
            EndBattleBGEffect(bc);
            // RET;
        } return;
    }
}

void v_QueueBattleAnimation(void) {
    // SET_PC(av_QueueBattleAnimation);
    // CALLFAR(aQueueBattleAnimation);
    QueueBattleAnimation();
    // RET;
}

static void BattleBGEffect_RemoveMon(struct BattleBGEffect* bc) {
    // SET_PC(aBattleBGEffect_RemoveMon);
    //  Slides mon out of screen
    // CALL(aBattleBGEffects_AnonJumptable);
    // uint8_t index = gb_read(REG_BC + BG_EFFECT_STRUCT_JT_INDEX);

anon_dw:
    switch(bc->jumptableIndex){
        // if (index == 0) goto zero;
        case 0: {
        // zero:
            // CALL(aBattleBGEffects_IncAnonJumptableIndex);
            BattleBGEffects_IncAnonJumptableIndex(bc);
            // CALL(aBGEffect_CheckBattleTurn);
            // LD_hl_A;
            bc->battleTurn = BGEffect_CheckBattleTurn(bc);
            // LD_HL(BG_EFFECT_STRUCT_BATTLE_TURN);
            // ADD_HL_BC;
            // LD_A_hl;
            // AND_A_A;
            // IF_Z goto user;
            // LD_A(0x9);
            // goto okay;

        // user:
            // LD_A(0x8);

        // okay:
            // LD_HL(BG_EFFECT_STRUCT_PARAM);
            // ADD_HL_BC;
            // LD_hl_A;
            bc->param = (bc->battleTurn == 0)? 0x8: 0x9;
            // RET;
        } return;
        // if (index == 1) goto one;
        case 1: {
        // one:
            // LD_HL(BG_EFFECT_STRUCT_BATTLE_TURN);
            // ADD_HL_BC;
            // LD_A_hl;
            // AND_A_A;
            // IF_Z goto user_2;
            if(bc->battleTurn != 0){
                // hlcoord(0, 6, wTilemap);
                tile_t* hl = coord(0, 6, wram->wTilemap);
                // LD_DE((8 << 8) | 6);
                uint8_t d = 8;
                uint8_t e = 6;

                do {
                // row1:
                    // PUSH_DE;
                    uint8_t d2 = d;
                    // PUSH_HL;
                    tile_t* hl2 = hl;
                    do {
                    // col1:
                        // INC_HL;
                        // LD_A_hld;
                        // LD_hli_A;
                        hl2[0] = hl2[1];
                        // DEC_D;
                        // IF_NZ goto col1;
                    } while(hl2++, --d2 != 0);
                    // POP_HL;
                    // LD_DE(SCREEN_WIDTH);
                    // ADD_HL_DE;
                    hl += SCREEN_WIDTH;
                    // POP_DE;
                    // DEC_E;
                    // IF_NZ goto row1;
                } while(--e != 0);
                // goto okay2;
            }
            else {
            // user_2:
                // hlcoord(19, 0, wTilemap);
                tile_t* hl = coord(19, 0, wram->wTilemap);
                // LD_DE((8 << 8) | 7);
                uint8_t d = 8;
                uint8_t e = 7;

                do {
                // row2:
                    // PUSH_DE;
                    uint8_t d2 = d;
                    // PUSH_HL;
                    tile_t* hl2 = hl;

                    do {
                    // col2:
                        // DEC_HL;
                        --hl2;
                        // LD_A_hli;
                        // LD_hld_A;
                        hl2[1] = hl2[0];
                        // DEC_D;
                        // IF_NZ goto col2;
                    } while(--d2 != 0);
                    // POP_HL;
                    // LD_DE(SCREEN_WIDTH);
                    // ADD_HL_DE;
                    hl += SCREEN_WIDTH;
                    // POP_DE;
                    // DEC_E;
                    // IF_NZ goto row2;
                } while(--e != 0);
            }

        // okay2:
            // XOR_A_A;
            // LDH_addr_A(hBGMapThird);
            hram->hBGMapThird = 0x0;
            // LD_A(0x1);
            // LDH_addr_A(hBGMapMode);
            hram->hBGMapMode = BGMAPMODE_UPDATE_TILES;
            // CALL(aBattleBGEffects_IncAnonJumptableIndex);
            BattleBGEffects_IncAnonJumptableIndex(bc);
            // LD_HL(BG_EFFECT_STRUCT_PARAM);
            // ADD_HL_BC;
            // DEC_hl;
            bc->param--;
            // RET;
        } return;
        // if (index == 2) return BattleBGEffects_IncAnonJumptableIndex();
        case 2: return BattleBGEffects_IncAnonJumptableIndex(bc);
        // if (index == 3) return BattleBGEffects_IncAnonJumptableIndex();
        case 3: return BattleBGEffects_IncAnonJumptableIndex(bc);
        // if (index == 4) goto four;
        case 4: {
        // four:
            // XOR_A_A;
            // LDH_addr_A(hBGMapMode);
            hram->hBGMapMode = BGMAPMODE_NONE;
            // LD_HL(BG_EFFECT_STRUCT_PARAM);
            // ADD_HL_BC;
            // LD_A_hl;
            // AND_A_A;
            // IF_Z goto done;
            if(bc->param != 0x0){
                // LD_HL(BG_EFFECT_STRUCT_JT_INDEX);
                // ADD_HL_BC;
                // LD_hl(0x1);
                bc->jumptableIndex = 0x1;
                // RET;
                return;
            }
        // done:
            // CALL(aEndBattleBGEffect);
            EndBattleBGEffect(bc);
            // RET;
        } return;
    }
}

static void BattleBGEffect_EnterMon(struct BattleBGEffect* bc) {
    static const uint8_t PlayerData[] = {
        2, 0x31, 2,
        1, 0x31, 1,
        0, 0x31, 0,
        (uint8_t)-1,
    };

    static const uint8_t EnemyData[] = {
        5, 0x00, 5,
        4, 0x00, 4,
        3, 0x00, 3,
        (uint8_t)-1,
    };
    // SET_PC(aBattleBGEffect_EnterMon);
    // CALL(aBGEffect_CheckBattleTurn);
    // IF_NZ goto player_turn;
    // LD_DE(mBattleBGEffect_EnterMon_EnemyData);
    // goto okay;

// player_turn:
    // LD_DE(mBattleBGEffect_EnterMon_PlayerData);

// okay:
    // LD_A_E;
    // LD_addr_A(wBattlePicResizeTempPointer);
    // LD_A_D;
    // LD_addr_A(wBattlePicResizeTempPointer + 1);
    const uint8_t* de = (BGEffect_CheckBattleTurn(bc) == 0)? EnemyData: PlayerData;
    // CALL(aBattleBGEffect_RunPicResizeScript);
    BattleBGEffect_RunPicResizeScript(bc, de);
    // RET;
}

static void BattleBGEffect_ReturnMon(struct BattleBGEffect* bc) {
// PlayerData:
    static const uint8_t PlayerData[] = {
        0, 0x31, 0,
        -2, 0x66, 0,
        1, 0x31, 1,
        -2, 0x44, 1,
        2, 0x31, 2,
        -2, 0x22, 2,
        -3, 0x00, 0,
        -1,
    };

// EnemyData:
    static const uint8_t EnemyData[] = {
        3, 0x00, 3,
        -2, 0x77, 3,
        4, 0x00, 4,
        -2, 0x55, 4,
        5, 0x00, 5,
        -2, 0x33, 5,
        -3, 0x00, 0,
        -1,
    };

    // SET_PC(aBattleBGEffect_ReturnMon);
    // CALL(aBGEffect_CheckBattleTurn);
    // IF_NZ goto player_turn;
    // LD_DE(mBattleBGEffect_ReturnMon_EnemyData);
    // goto okay;

// player_turn:
    // LD_DE(mBattleBGEffect_ReturnMon_PlayerData);

// okay:
    // LD_A_E;
    // LD_addr_A(wBattlePicResizeTempPointer);
    // LD_A_D;
    // LD_addr_A(wBattlePicResizeTempPointer + 1);
    const uint8_t* de = (BGEffect_CheckBattleTurn(bc) == 0)? EnemyData: PlayerData;
    // CALL(aBattleBGEffect_RunPicResizeScript);
    BattleBGEffect_RunPicResizeScript(bc, de);
    // RET;
}

static void BattleBGEffect_RunPicResizeScript(struct BattleBGEffect* bc, const uint8_t* de) {
// BGSquares:

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
    static const uint8_t SixBySix[] = {
        0x00, 0x06, 0x0c, 0x12, 0x18, 0x1e,
        0x01, 0x07, 0x0d, 0x13, 0x19, 0x1f,
        0x02, 0x08, 0x0e, 0x14, 0x1a, 0x20,
        0x03, 0x09, 0x0f, 0x15, 0x1b, 0x21,
        0x04, 0x0a, 0x10, 0x16, 0x1c, 0x22,
        0x05, 0x0b, 0x11, 0x17, 0x1d, 0x23,
    };
    static const uint8_t FourByFour[] = {
        0x00, 0x0c, 0x12, 0x1e,
        0x02, 0x0e, 0x14, 0x20,
        0x03, 0x0f, 0x15, 0x21,
        0x05, 0x11, 0x17, 0x23,
    };
    static const uint8_t TwoByTwo[] = {
        0x00, 0x1e,
        0x05, 0x23,
    };
    static const uint8_t SevenBySeven[] = {
        0x00, 0x07, 0x0e, 0x15, 0x1c, 0x23, 0x2a,
        0x01, 0x08, 0x0f, 0x16, 0x1d, 0x24, 0x2b,
        0x02, 0x09, 0x10, 0x17, 0x1e, 0x25, 0x2c,
        0x03, 0x0a, 0x11, 0x18, 0x1f, 0x26, 0x2d,
        0x04, 0x0b, 0x12, 0x19, 0x20, 0x27, 0x2e,
        0x05, 0x0c, 0x13, 0x1a, 0x21, 0x28, 0x2f,
        0x06, 0x0d, 0x14, 0x1b, 0x22, 0x29, 0x30,
    };
    static const uint8_t FiveByFive[] = {
        0x00, 0x07, 0x15, 0x23, 0x2a,
        0x01, 0x08, 0x16, 0x24, 0x2b,
        0x03, 0x0a, 0x18, 0x26, 0x2d,
        0x05, 0x0c, 0x1a, 0x28, 0x2f,
        0x06, 0x0d, 0x1b, 0x29, 0x30,
    };
    
    static const uint8_t ThreeByThree[] = {
        0x00, 0x15, 0x2a,
        0x03, 0x18, 0x2d,
        0x06, 0x1b, 0x30,
    };

    static const struct BGSquare BGSquares[] = {
        [BGSQUARE_SIX]   = {.w = 6, .h = 6, .ptr=SixBySix},
        [BGSQUARE_FOUR]  = {.w = 4, .h = 4, .ptr=FourByFour},
        [BGSQUARE_TWO]   = {.w = 2, .h = 2, .ptr=TwoByTwo},
        [BGSQUARE_SEVEN] = {.w = 7, .h = 7, .ptr=SevenBySeven},
        [BGSQUARE_FIVE]  = {.w = 5, .h = 5, .ptr=FiveByFive},
        [BGSQUARE_THREE] = {.w = 3, .h = 3, .ptr=ThreeByThree},
    };

// Coords:

    // dwcoord ['2', '6'];
    // dwcoord ['3', '8'];
    // dwcoord ['4', '10'];
    // dwcoord ['12', '0'];
    // dwcoord ['13', '2'];
    // dwcoord ['14', '4'];
    static const uint16_t Coords[] = {
        coord(2, 6, 0),
        coord(3, 8, 0),
        coord(4, 10, 0),
        coord(12, 0, 0),
        coord(13, 2, 0),
        coord(14, 4, 0),
    };

    // SET_PC(aBattleBGEffect_RunPicResizeScript);
    // CALL(aBattleBGEffects_AnonJumptable);
    // uint8_t index = gb_read(REG_BC + BG_EFFECT_STRUCT_JT_INDEX);

// anon_dw:
    switch(bc->jumptableIndex){
        // if (index == 0) goto zero;
        case 0: {
        zero:
            // LD_HL(BG_EFFECT_STRUCT_PARAM);
            // ADD_HL_BC;
            // LD_E_hl;
            // LD_D(0x0);
            // INC_hl;
            // LD_A_addr(wBattlePicResizeTempPointer);
            // LD_L_A;
            // LD_A_addr(wBattlePicResizeTempPointer + 1);
            // LD_H_A;
            // ADD_HL_DE;
            // ADD_HL_DE;
            // ADD_HL_DE;
            const uint8_t* hl2 = de + (3 * bc->param++);
            // LD_A_hl;
            // CP_A(0xff);
            // IF_Z goto end;
            if(*hl2 == 0xff){
                goto end;
            }
            // CP_A(0xfe);
            // IF_Z goto clear;
            if(*hl2 == 0xfe) {
            // clear:
                // CALL(aBattleBGEffect_RunPicResizeScript_ClearBox);
            // ClearBox:
                //  get dims
                // PUSH_BC;
                // INC_HL;
                hl2++;
                // LD_A_hli;
                // LD_B_A;
                // AND_A(0xf);
                // LD_C_A;
                uint8_t c = *hl2 & 0xf;
                // LD_A_B;
                // SWAP_A;
                // AND_A(0xf);
                // LD_B_A;
                uint8_t b = (*hl2 & 0xf0) >> 4;
                hl2++;
                //  get coords
                // LD_E_hl;
                // LD_D(0);
                // LD_HL(mBattleBGEffect_RunPicResizeScript_Coords);
                // ADD_HL_DE;
                // ADD_HL_DE;
                // LD_A_hli;
                // LD_H_hl;
                // LD_L_A;
                // REG_HL = Coords[*hl2];
                // CALL(aClearBox);
                ClearBox(wram->wTilemap + Coords[*hl2], c, b);
                // POP_BC;
                // RET;
                goto zero;
            }
            // CP_A(0xfd);
            // IF_Z goto skip;
            // CALL(aBattleBGEffect_RunPicResizeScript_PlaceGraphic);
            if(*hl2 != 0xfd)
            {
            // PlaceGraphic:

                //  get dims
                // PUSH_BC;
                // PUSH_HL;
                // LD_E_hl;
                uint8_t e = *hl2;
                // LD_D(0);
                // LD_HL(mBattleBGEffect_RunPicResizeScript_BGSquares);
                // ADD_HL_DE;
                // ADD_HL_DE;
                // ADD_HL_DE;
                // LD_A_hli;
                // LD_B_A;
                // AND_A(0xf);
                // LD_C_A;
                uint8_t w = BGSquares[e].w;
                uint8_t c = w;
                // LD_A_B;
                // SWAP_A;
                // AND_A(0xf);
                // LD_B_A;
                uint8_t h = BGSquares[e].h;
                //  store pointer
                // LD_E_hl;
                // INC_HL;
                // LD_D_hl;
                const uint8_t* de = BGSquares[e].ptr;
                const uint8_t* de2;
                //  get byte
                // POP_HL;
                // INC_HL;
                // LD_A_hli;
                // LD_addr_A(wBattlePicResizeTempBaseTileID);
                wram->wBattlePicResizeTempBaseTileID = hl2[1];
                //  get coord
                // PUSH_DE;
                // LD_E_hl;
                // LD_D(0);
                // LD_HL(mBattleBGEffect_RunPicResizeScript_Coords);
                // ADD_HL_DE;
                // ADD_HL_DE;
                // LD_A_hli;
                // LD_H_hl;
                // LD_L_A;
                // REG_HL = Coords[hl2[2]];
                uint8_t* hl3 = wram->wTilemap + Coords[hl2[2]];
                // POP_DE;
                //  fill box
                do {
                // row:
                    de2 = de;
                    // PUSH_BC;
                    uint8_t c2 = c;
                    // PUSH_HL;
                    tile_t* hl4 = hl3;
                    // LD_A_addr(wBattlePicResizeTempBaseTileID);
                    // LD_B_A;
                    uint8_t b = wram->wBattlePicResizeTempBaseTileID;
                    do {
                    // col:
                        // LD_A_de;
                        // ADD_A_B;
                        // LD_hli_A;
                        *(hl4++) = b + *de;
                        // INC_DE;
                        de += c;
                        // DEC_C;
                        // IF_NZ goto col;
                    } while(--c2 != 0);
                    // POP_HL;
                    // LD_BC(SCREEN_WIDTH);
                    // ADD_HL_BC;
                    hl3 += SCREEN_WIDTH;
                    // POP_BC;
                    de = de2 + 1;
                    // DEC_B;
                    // IF_NZ goto row;
                } while(--h != 0);
                // POP_BC;
                // RET;
            }

        // skip:
            // CALL(aBattleBGEffects_IncAnonJumptableIndex);
            BattleBGEffects_IncAnonJumptableIndex(bc);
            // LD_A(0x1);
            // LDH_addr_A(hBGMapMode);
            hram->hBGMapMode = BGMAPMODE_UPDATE_TILES;
            // RET;
            return;
        } return;
        // if (index == 1) return BattleBGEffects_IncAnonJumptableIndex();
        // if (index == 2) return BattleBGEffects_IncAnonJumptableIndex();
        case 1: return BattleBGEffects_IncAnonJumptableIndex(bc);
        case 2: return BattleBGEffects_IncAnonJumptableIndex(bc);
        // if (index == 3) goto restart;
        case 3: {
        // restart:
            // XOR_A_A;
            // LDH_addr_A(hBGMapMode);
            hram->hBGMapMode = BGMAPMODE_NONE;
            // LD_HL(BG_EFFECT_STRUCT_JT_INDEX);
            // ADD_HL_BC;
            // LD_hl(0x0);
            bc->jumptableIndex = 0x0;
            // RET;
        } return;
        // if (index == 4) goto end;
        case 4: {
        end:
            // XOR_A_A;
            // LDH_addr_A(hBGMapMode);
            hram->hBGMapMode = BGMAPMODE_NONE;
            // CALL(aEndBattleBGEffect);
            EndBattleBGEffect(bc);
            // RET;
        } return;
    }
}

static void BattleBGEffect_Surf_RotatewSurfWaveBGEffect(void){
    // LD_HL(wSurfWaveBGEffect);
    uint8_t* hl = wram->wSurfWaveBGEffect;
    // LD_DE(wSurfWaveBGEffect + 1);
    uint8_t* de = wram->wSurfWaveBGEffect + 1;
    // LD_C(wSurfWaveBGEffectEnd - wSurfWaveBGEffect - 1);
    uint8_t c = sizeof(wram->wSurfWaveBGEffect) - 1;
    // LD_A_hl;
    // PUSH_AF;
    uint8_t temp = *hl;

    do {
    // loop:
        // LD_A_de;
        // INC_DE;
        // LD_hli_A;
        *(hl++) = *(de++);
        // DEC_C;
        // IF_NZ goto loop;
    } while(--c != 0);
    // POP_AF;
    // LD_hl_A;
    *hl = temp;
    // LD_DE(wLYOverridesBackup);
    de = wram->wLYOverridesBackup;
    // LD_HL(wSurfWaveBGEffect);
    hl = wram->wSurfWaveBGEffect;
    // LD_BC(0x0);
    c = 0x0;

    uint8_t e = 0x0;
    do {
    // loop2:
        // LDH_A_addr(hLYOverrideStart);
        // CP_A_E;
        // IF_NC goto load_zero;
        if(hram->hLYOverrideStart >= e){
        // load_zero:
            // XOR_A_A;
            de[e] = 0;
        }
        else {
            // PUSH_HL;
            // ADD_HL_BC;
            // LD_A_hl;
            // POP_HL;
            // goto okay;
            de[e] = hl[c];
        }

    // okay:
        // LD_de_A;
        // LD_A_C;
        // INC_A;
        // AND_A(0x3f);
        // LD_C_A;
        c = (c + 1) & 0x3f;
        // INC_DE;
        // LD_A_E;
        // CP_A(0x5f);
        // IF_C goto loop2;
    } while(++e < 0x5f);
    // RET;
}

static void BattleBGEffect_Surf(struct BattleBGEffect* bc) {
    // SET_PC(aBattleBGEffect_Surf);
    // CALL(aBattleBGEffects_AnonJumptable);
    // uint8_t index = gb_read(REG_BC + BG_EFFECT_STRUCT_JT_INDEX);

// anon_dw:
    switch(bc->jumptableIndex){
        // if (index == 0) goto zero;
        case 0:
        // zero:
            // CALL(aBattleBGEffects_IncAnonJumptableIndex);
            BattleBGEffects_IncAnonJumptableIndex(bc);
            // LD_DE((2 << 8) | 2);
            // CALL(aInitSurfWaves);
            InitSurfWaves(2, 2);
            fallthrough;
        // if (index == 1) goto one;
        case 1:
        // one:
            // LDH_A_addr(hLCDCPointer);
            // AND_A_A;
            // RET_Z;
            if(hram->hLCDCPointer == 0)
                return;
            // PUSH_BC;
            // CALL(aBattleBGEffect_Surf_RotatewSurfWaveBGEffect);
            BattleBGEffect_Surf_RotatewSurfWaveBGEffect();
            // POP_BC;
            // RET;
            return;
        // if (index == 2) goto two;
        case 2:
        // two:
            // CALL(aBattleAnim_ResetLCDStatCustom);
            // RET;
            return BattleAnim_ResetLCDStatCustom(bc);
    }
}

static void BattleBGEffect_Whirlpool(struct BattleBGEffect* bc) {
    // SET_PC(aBattleBGEffect_Whirlpool);
    // CALL(aBattleBGEffects_AnonJumptable);
    // uint8_t index = gb_read(REG_BC + BG_EFFECT_STRUCT_JT_INDEX);

// anon_dw:
    switch(bc->jumptableIndex){
        // if (index == 0) goto zero;
        case 0: {
        // zero:
            // CALL(aBattleBGEffects_IncAnonJumptableIndex);
            BattleBGEffects_IncAnonJumptableIndex(bc);
            // CALL(aBattleBGEffects_ClearLYOverrides);
            BattleBGEffects_ClearLYOverrides();
            // LD_A(LOW(rSCY));
            // LDH_addr_A(hLCDCPointer);
            hram->hLCDCPointer = LOW(rSCY);
            // XOR_A_A;
            // LDH_addr_A(hLYOverrideStart);
            hram->hLYOverrideStart = 0x0;
            // LD_A(0x5e);
            // LDH_addr_A(hLYOverrideEnd);
            hram->hLYOverrideEnd = 0x5e;
            // LD_DE((2 << 8) | 2);
            // CALL(aDeformScreen);
            DeformScreen(2, 2);
            // RET;
        } return;
        // if (index == 1) goto one;
        case 1: {
        // one:
            // CALL(aBattleBGEffect_WavyScreenFX);
            BattleBGEffect_WavyScreenFX();
            // RET;
        } return;
        // if (index == 2) goto two;
        case 2: {
        // two:
            // CALL(aBattleAnim_ResetLCDStatCustom);
            BattleAnim_ResetLCDStatCustom(bc);
            // RET;
        } return;
    }
}

static void BattleBGEffect_StartWater(struct BattleBGEffect* bc) {
    // SET_PC(aBattleBGEffect_StartWater);
    // CALL(aBattleBGEffects_ClearLYOverrides);
    BattleBGEffects_ClearLYOverrides();
    // LD_A(LOW(rSCY));
    // CALL(aBattleBGEffect_SetLCDStatCustoms1);
    BattleBGEffect_SetLCDStatCustoms1(bc, LOW(rSCY));
    // CALL(aEndBattleBGEffect);
    EndBattleBGEffect(bc);
    // RET;
}

static void BattleBGEffect_Water(struct BattleBGEffect* bc) {
    // SET_PC(aBattleBGEffect_Water);
    //  BG_EFFECT_STRUCT_JT_INDEX: defines Y position of deformation
    // LD_HL(BG_EFFECT_STRUCT_PARAM);
    // ADD_HL_BC;
    // LD_A_hl;
    // LD_E_A;
    uint8_t e = bc->param;
    // ADD_A(0x4);
    // LD_hl_A;
    bc->param = e + 0x4;
    // LD_HL(BG_EFFECT_STRUCT_BATTLE_TURN);
    // ADD_HL_BC;
    // LD_A_hl;
    // AND_A(0xf0);
    // SWAP_A;
    // XOR_A(0xff);
    // ADD_A(0x4);
    // LD_D_A;
    uint8_t d = (((bc->battleTurn & 0xf0) >> 4) ^ 0xff) + 0x4;
    // LD_HL(BG_EFFECT_STRUCT_JT_INDEX);
    // ADD_HL_BC;
    // LD_A_hl;
    // LD_addr_A(wBattleSineWaveTempProgress);
    wram->wBattleSineWaveTempProgress = bc->jumptableIndex;
    // LD_HL(BG_EFFECT_STRUCT_BATTLE_TURN);
    // ADD_HL_BC;
    // LD_A_hl;
    // CP_A(0x20);
    // IF_NC goto done;
    if(bc->battleTurn < 0x20){
        uint8_t a = bc->battleTurn;
        // INC_hl;
        // INC_hl;
        bc->battleTurn += 2;
        // CALL(aDeformWater);
        DeformWater(d, e, a);
        // RET;
        return;
    }

// done:
    // CALL(aBattleBGEffects_ClearLYOverrides);
    BattleBGEffects_ClearLYOverrides();
    // CALL(aEndBattleBGEffect);
    EndBattleBGEffect(bc);
    // RET;
}

static void BattleBGEffect_EndWater(struct BattleBGEffect* bc) {
    // SET_PC(aBattleBGEffect_EndWater);
    // CALL(aBattleAnim_ResetLCDStatCustom);
    BattleAnim_ResetLCDStatCustom(bc);
    // RET;
}

static void BattleBGEffect_Psychic(struct BattleBGEffect* bc) {
    // SET_PC(aBattleBGEffect_Psychic);
    //  Hardcoded to always affect opponent
    // CALL(aBattleBGEffects_AnonJumptable);
    // uint8_t index = gb_read(REG_BC + BG_EFFECT_STRUCT_JT_INDEX);

// anon_dw:
    switch(bc->jumptableIndex){
        // if (index == 0) goto zero;
        case 0: {
        // zero:
            // CALL(aBattleBGEffects_IncAnonJumptableIndex);
            BattleBGEffects_IncAnonJumptableIndex(bc);
            // CALL(aBattleBGEffects_ClearLYOverrides);
            BattleBGEffects_ClearLYOverrides();
            // LD_A(LOW(rSCX));
            // LDH_addr_A(hLCDCPointer);
            hram->hLCDCPointer = LOW(rSCX);
            // XOR_A_A;
            // LDH_addr_A(hLYOverrideStart);
            hram->hLYOverrideStart = 0x0;
            // LD_A(0x5f);
            // LDH_addr_A(hLYOverrideEnd);
            hram->hLYOverrideEnd = 0x5f;
            // LD_DE((6 << 8) | 5);
            // CALL(aDeformScreen);
            DeformScreen(6, 5);
            // LD_HL(BG_EFFECT_STRUCT_PARAM);
            // ADD_HL_BC;
            // LD_hl(0x0);
            bc->param = 0x0;
            // RET;
        } return;
        // if (index == 1) goto one;
        case 1: {
        // one:
            // LD_HL(BG_EFFECT_STRUCT_PARAM);
            // ADD_HL_BC;
            // LD_A_hl;
            uint8_t param = bc->param;
            // INC_hl;
            bc->param++;
            // AND_A(0x3);
            // RET_NZ;
            if(param & 0x3)
                return;
            // CALL(aBattleBGEffect_WavyScreenFX);
            BattleBGEffect_WavyScreenFX();
            // RET;
        } return;
        // if (index == 2) goto two;
        case 2: {
        // two:
            // CALL(aBattleAnim_ResetLCDStatCustom);
            BattleAnim_ResetLCDStatCustom(bc);
            // RET;
        } return;
    }
}

static void BattleBGEffect_Teleport(struct BattleBGEffect* bc) {
    // SET_PC(aBattleBGEffect_Teleport);
    // CALL(aBattleBGEffects_AnonJumptable);
    // uint8_t index = gb_read(REG_BC + BG_EFFECT_STRUCT_JT_INDEX);

// anon_dw:
    switch(bc->jumptableIndex){
        // if (index == 0) goto zero;
        case 0: {
        // zero:
            // CALL(aBattleBGEffects_IncAnonJumptableIndex);
            BattleBGEffects_IncAnonJumptableIndex(bc);
            // CALL(aBattleBGEffects_ClearLYOverrides);
            BattleBGEffects_ClearLYOverrides();
            // LD_A(LOW(rSCX));
            // CALL(aBattleBGEffect_SetLCDStatCustoms1);
            BattleBGEffect_SetLCDStatCustoms1(bc, LOW(rSCX));
            // LD_DE((6 << 8) | 5);
            // CALL(aDeformScreen);
            DeformScreen(6, 5);
            // RET;
        } return;
        // if (index == 1) goto one;
        case 1: {
        // one:
            // CALL(aBattleBGEffect_WavyScreenFX);
            BattleBGEffect_WavyScreenFX();
            // RET;
        } return;
        // if (index == 2) goto two;
        case 2: {
        // two:
            // CALL(aBattleAnim_ResetLCDStatCustom);
            BattleAnim_ResetLCDStatCustom(bc);
            // RET;
        } return;
    }
}

static void BattleBGEffect_NightShade(struct BattleBGEffect* bc) {
    // SET_PC(aBattleBGEffect_NightShade);
    // CALL(aBattleBGEffects_AnonJumptable);
    // uint8_t index = gb_read(REG_BC + BG_EFFECT_STRUCT_JT_INDEX);

// anon_dw:
    switch(bc->jumptableIndex){
        // if (index == 0) goto zero;
        case 0: {
        // zero:
            // CALL(aBattleBGEffects_IncAnonJumptableIndex);
            BattleBGEffects_IncAnonJumptableIndex(bc);
            // CALL(aBattleBGEffects_ClearLYOverrides);
            BattleBGEffects_ClearLYOverrides();
            // LD_A(LOW(rSCY));
            // CALL(aBattleBGEffect_SetLCDStatCustoms1);
            BattleBGEffect_SetLCDStatCustoms1(bc, LOW(rSCY));
            // LD_HL(BG_EFFECT_STRUCT_PARAM);
            // ADD_HL_BC;
            // LD_E_hl;
            // LD_D(2);
            // CALL(aDeformScreen);
            DeformScreen(2, bc->param);
            // RET;
        } return;
        // if (index == 1) goto one;
        case 1: {
        // one:
            // CALL(aBattleBGEffect_WavyScreenFX);
            BattleBGEffect_WavyScreenFX();
            // RET;
        } return;
        // if (index == 2) goto two;
        case 2: {
        // two:
            // CALL(aBattleAnim_ResetLCDStatCustom);
            BattleAnim_ResetLCDStatCustom(bc);
            // RET;
        } return;
    }
}

static void BattleBGEffect_DoubleTeam_UpdateLYOverrides(uint8_t a){
    // LD_E_A;
    uint8_t e = a;
    // XOR_A(0xff);
    // INC_A;
    // LD_D_A;
    uint8_t d = (a ^ 0xff) + 1;
    // LD_H(HIGH(wLYOverridesBackup));
    // LDH_A_addr(hLYOverrideStart);
    // LD_L_A;
    uint8_t l = hram->hLYOverrideStart;
    // LDH_A_addr(hLYOverrideEnd);
    // SUB_A_L;
    // SRL_A;
    uint8_t carry = (hram->hLYOverrideEnd - hram->hLYOverrideStart) & 1;
    // PUSH_AF;
    uint8_t a2 = (hram->hLYOverrideEnd - hram->hLYOverrideStart) / 2;

    do {
    // loop:
        // LD_hl_E;
        // INC_HL;
        wram->wLYOverridesBackup[l++] = e;
        // LD_hl_D;
        // INC_HL;
        wram->wLYOverridesBackup[l++] = d;
        // DEC_A;
        // IF_NZ goto loop;
    } while(--a2 != 0);
    // POP_AF;
    // RET_NC;
    if(carry){
        // LD_hl_E;
        wram->wLYOverridesBackup[l] = e;
        // RET;
    }
}

static void BattleBGEffect_DoubleTeam(struct BattleBGEffect* bc) {
    // SET_PC(aBattleBGEffect_DoubleTeam);
    // CALL(aBattleBGEffects_AnonJumptable);
    // uint8_t index = gb_read(REG_BC + BG_EFFECT_STRUCT_JT_INDEX);

// anon_dw:
    switch(bc->jumptableIndex){
        // if (index == 0) goto zero;
        case 0:
        // zero:
            // CALL(aBattleBGEffects_IncAnonJumptableIndex);
            BattleBGEffects_IncAnonJumptableIndex(bc);
            // CALL(aBattleBGEffects_ClearLYOverrides);
            BattleBGEffects_ClearLYOverrides();
            // LD_A(LOW(rSCX));
            // CALL(aBattleBGEffect_SetLCDStatCustoms1);
            BattleBGEffect_SetLCDStatCustoms1(bc, LOW(rSCX));
            // LDH_A_addr(hLYOverrideEnd);
            // INC_A;
            // LDH_addr_A(hLYOverrideEnd);
            hram->hLYOverrideEnd++;
            // LD_HL(BG_EFFECT_STRUCT_BATTLE_TURN);
            // ADD_HL_BC;
            // LD_hl(0x0);
            bc->battleTurn = 0x0;
            // RET;
            return;
        // if (index == 1) goto one;
        case 1: {
        // one:
            // LD_HL(BG_EFFECT_STRUCT_PARAM);
            // ADD_HL_BC;
            // LD_A_hl;
            // CP_A(0x10);
            // IF_NC goto next;
            if(bc->param >= 0x10)
                return BattleBGEffects_IncAnonJumptableIndex(bc);
            // INC_hl;
            uint8_t param = bc->param++;
            // CALL(aBattleBGEffect_DoubleTeam_UpdateLYOverrides);
            BattleBGEffect_DoubleTeam_UpdateLYOverrides(param);
            // RET;
        } return;
        // if (index == 2) goto two;
        case 2: {
        // two:
            // LD_HL(BG_EFFECT_STRUCT_BATTLE_TURN);
            // ADD_HL_BC;
            // LD_A_hl;
            // LD_D(0x2);
            // CALL(aBattleBGEffects_Sine);
            // LD_HL(BG_EFFECT_STRUCT_PARAM);
            // ADD_HL_BC;
            // ADD_A_hl;
            // CALL(aBattleBGEffect_DoubleTeam_UpdateLYOverrides);
            BattleBGEffect_DoubleTeam_UpdateLYOverrides(bc->param + Sine(bc->battleTurn, 0x2));
            // LD_HL(BG_EFFECT_STRUCT_BATTLE_TURN);
            // ADD_HL_BC;
            // LD_A_hl;
            // ADD_A(0x4);
            // LD_hl_A;
            bc->battleTurn += 0x4;
        } fallthrough;
        // if (index == 4) goto four;
        case 4:
        // four:
            // RET;
            return;
        // if (index == 3) goto three;
        case 3: {
        // three:
            // LD_HL(BG_EFFECT_STRUCT_PARAM);
            // ADD_HL_BC;
            // LD_A_hl;
            // CP_A(0xff);
            // IF_Z goto next;
            if(bc->param == 0xff)
                return BattleBGEffects_IncAnonJumptableIndex(bc);
            // DEC_hl;
            uint8_t param = bc->param--;
            // CALL(aBattleBGEffect_DoubleTeam_UpdateLYOverrides);
            BattleBGEffect_DoubleTeam_UpdateLYOverrides(param);
            // RET;
        } return;
        // if (index == 5) goto five;
        case 5:
        // five:
            // CALL(aBattleAnim_ResetLCDStatCustom);
            // RET;
            return BattleAnim_ResetLCDStatCustom(bc);
    }

// next:
    // CALL(aBattleBGEffects_IncAnonJumptableIndex);
    // RET;
}

static void BattleBGEffect_AcidArmor(struct BattleBGEffect* bc) {
    // SET_PC(aBattleBGEffect_AcidArmor);
    // CALL(aBattleBGEffects_AnonJumptable);
    // uint8_t index = gb_read(REG_BC + BG_EFFECT_STRUCT_JT_INDEX);

// anon_dw:
    switch(bc->jumptableIndex){
        // if (index == 0) goto zero;
        case 0:
        // zero:
            // CALL(aBattleBGEffects_IncAnonJumptableIndex);
            BattleBGEffects_IncAnonJumptableIndex(bc);
            // CALL(aBattleBGEffects_ClearLYOverrides);
            BattleBGEffects_ClearLYOverrides();
            // LD_A(LOW(rSCY));
            // CALL(aBattleBGEffect_SetLCDStatCustoms1);
            BattleBGEffect_SetLCDStatCustoms1(bc, LOW(rSCY));
            // LD_HL(BG_EFFECT_STRUCT_PARAM);
            // ADD_HL_BC;
            // LD_E_hl;
            // LD_D(2);
            // CALL(aDeformScreen);
            DeformScreen(2, bc->param);
            // LD_H(HIGH(wLYOverridesBackup));
            // LDH_A_addr(hLYOverrideEnd);
            // LD_L_A;
            // LD_hl(0x0);
            wram->wLYOverridesBackup[hram->hLYOverrideEnd] = 0x0;
            // DEC_L;
            // LD_hl(0x0);
            wram->wLYOverridesBackup[hram->hLYOverrideEnd - 1] = 0x0;
            // RET;
            return;
        // if (index == 1) goto one;
        case 1: {
        // one:
            // LDH_A_addr(hLYOverrideEnd);
            // LD_L_A;
            // LD_H(HIGH(wLYOverridesBackup));
            uint8_t l = hram->hLYOverrideEnd;
            // LD_E_L;
            // LD_D_H;
            // DEC_DE;
            uint8_t* de = wram->wLYOverridesBackup + (l - 1);

            do {
            // loop:
                // LD_A_de;
                // DEC_DE;
                // LD_hld_A;
                wram->wLYOverridesBackup[l--] = *de;
                --de;
                // LDH_A_addr(hLYOverrideStart);
                // CP_A_L;
                // IF_NZ goto loop;
            } while(hram->hLYOverrideStart != l);
            // LD_hl(0x90);
            wram->wLYOverridesBackup[l] = 0x90;
            // LDH_A_addr(hLYOverrideEnd);
            // LD_L_A;
            l = hram->hLYOverrideEnd;
            // LD_A_hl;
            uint8_t a = wram->wLYOverridesBackup[l];
            // CP_A(0x1);
            // IF_C goto okay;
            // CP_A(0x90);
            // IF_Z goto okay;
            if(a >= 0x1 && a != 0x90){
                // LD_hl(0x0);
                wram->wLYOverridesBackup[l] = 0x0;
            }

        // okay:
            // DEC_L;
            --l;
            // LD_A_hl;
            a = wram->wLYOverridesBackup[l];
            // CP_A(0x2);
            // RET_C;
            // CP_A(0x90);
            // RET_Z;
            if(a >= 0x1 && a != 0x90){
                // LD_hl(0x0);
                wram->wLYOverridesBackup[l] = 0x0;
                // RET;
            }
        } return;
        // if (index == 2) goto two;
        case 2: {
        // two:
            // CALL(aBattleAnim_ResetLCDStatCustom);
            BattleAnim_ResetLCDStatCustom(bc);
            // RET;
        } return;
    }
}

static void BattleBGEffect_Withdraw(struct BattleBGEffect* bc) {
    // SET_PC(aBattleBGEffect_Withdraw);
    // CALL(aBattleBGEffects_AnonJumptable);
    // uint8_t index = gb_read(REG_BC + BG_EFFECT_STRUCT_JT_INDEX);

// anon_dw:
    switch(bc->jumptableIndex){
        // if (index == 0) goto zero;
        case 0:
        // zero:
            // CALL(aBattleBGEffects_IncAnonJumptableIndex);
            BattleBGEffects_IncAnonJumptableIndex(bc);
            // CALL(aBattleBGEffects_ClearLYOverrides);
            BattleBGEffects_ClearLYOverrides();
            // LD_A(LOW(rSCY));
            // CALL(aBattleBGEffect_SetLCDStatCustoms1);
            BattleBGEffect_SetLCDStatCustoms1(bc, LOW(rSCY));
            // LDH_A_addr(hLYOverrideEnd);
            // INC_A;
            // LDH_addr_A(hLYOverrideEnd);
            hram->hLYOverrideEnd++;
            // LD_HL(BG_EFFECT_STRUCT_BATTLE_TURN);
            // ADD_HL_BC;
            // LD_hl(0x1);
            bc->battleTurn = 0x1;
            // RET;
            return;
        // if (index == 1) goto one;
        case 1: {
        // one:
            // LD_HL(BG_EFFECT_STRUCT_PARAM);
            // ADD_HL_BC;
            // LD_A_hl;
            // AND_A(0x3f);
            // LD_D_A;
            uint8_t d = bc->param & 0x3f;
            // LD_HL(BG_EFFECT_STRUCT_BATTLE_TURN);
            // ADD_HL_BC;
            // LD_A_hl;
            // CP_A_D;
            // RET_NC;
            if(bc->battleTurn >= d)
                return;
            // CALL(aBGEffect_DisplaceLYOverridesBackup);
            BGEffect_DisplaceLYOverridesBackup(bc->battleTurn);
            // LD_HL(BG_EFFECT_STRUCT_PARAM);
            // ADD_HL_BC;
            // LD_A_hl;
            // RLCA;
            // RLCA;
            // AND_A(0x3);
            const uint8_t a = ((bc->param << 2) | (bc->param >> 6)) & 0x3;
            // LD_HL(BG_EFFECT_STRUCT_BATTLE_TURN);
            // ADD_HL_BC;
            // ADD_A_hl;
            // LD_hl_A;
            bc->battleTurn += a;
            // RET;
        } return;
        // if (index == 2) goto two;
        case 2:
        // two:
            // CALL(aBattleAnim_ResetLCDStatCustom);
            // RET;
            return BattleAnim_ResetLCDStatCustom(bc);
    }
}

static void BattleBGEffect_Dig(struct BattleBGEffect* bc) {
    // SET_PC(aBattleBGEffect_Dig);
    // CALL(aBattleBGEffects_AnonJumptable);
    // uint8_t index = gb_read(REG_BC + BG_EFFECT_STRUCT_JT_INDEX);

// anon_dw:
    switch(bc->jumptableIndex){
        // if (index == 0) goto zero;
        case 0:
        // zero:
            // CALL(aBattleBGEffects_IncAnonJumptableIndex);
            BattleBGEffects_IncAnonJumptableIndex(bc);
            // CALL(aBattleBGEffects_ClearLYOverrides);
            BattleBGEffects_ClearLYOverrides();
            // LD_A(LOW(rSCY));
            // CALL(aBattleBGEffect_SetLCDStatCustoms1);
            BattleBGEffect_SetLCDStatCustoms1(bc, LOW(rSCY));
            // LDH_A_addr(hLYOverrideEnd);
            // INC_A;
            // LDH_addr_A(hLYOverrideEnd);
            hram->hLYOverrideEnd++;
            // LD_HL(BG_EFFECT_STRUCT_BATTLE_TURN);
            // ADD_HL_BC;
            // LD_hl(0x2);
            bc->battleTurn = 0x2;
            // LD_HL(BG_EFFECT_STRUCT_PARAM);
            // ADD_HL_BC;
            // LD_hl(0x0);
            bc->param = 0x0;
            // RET;
            return;
        // if (index == 1) goto one;
        case 1: {
        // one:
            // LD_HL(BG_EFFECT_STRUCT_PARAM);
            // ADD_HL_BC;
            // LD_A_hl;
            // AND_A_A;
            // IF_Z goto next;
            if(bc->param != 0){
                // DEC_hl;
                bc->param--;
                // RET;
                return;
            }

        // next:
            // LD_hl(0x10);
            bc->param = 0x10;
            // CALL(aBattleBGEffects_IncAnonJumptableIndex);
            BattleBGEffects_IncAnonJumptableIndex(bc);
        } fallthrough;
        // if (index == 2) goto two;
        case 2: {
        // two:
            // LDH_A_addr(hLYOverrideStart);
            // LD_L_A;
            // LDH_A_addr(hLYOverrideEnd);
            // SUB_A_L;
            // DEC_A;
            // LD_HL(BG_EFFECT_STRUCT_BATTLE_TURN);
            // ADD_HL_BC;
            // CP_A_hl;
            // RET_C;
            if(bc->battleTurn < hram->hLYOverrideEnd - hram->hLYOverrideStart - 1)
                return;
            // LD_A_hl;
            // PUSH_AF;
            uint8_t bt = bc->battleTurn;
            // AND_A(0x7);
            // IF_NZ goto skip;
            if((bt & 0x7) == 0){
                // LD_HL(BG_EFFECT_STRUCT_JT_INDEX);
                // ADD_HL_BC;
                // DEC_hl;
                bc->jumptableIndex--;
            }

        // skip:
            // POP_AF;
            // CALL(aBGEffect_DisplaceLYOverridesBackup);
            BGEffect_DisplaceLYOverridesBackup(bt);
            // LD_HL(BG_EFFECT_STRUCT_BATTLE_TURN);
            // ADD_HL_BC;
            // INC_hl;
            // INC_hl;
            bc->battleTurn += 2;
            // RET;
        } return;
        // if (index == 3) goto three;
        case 3:
        // three:
            // CALL(aBattleAnim_ResetLCDStatCustom);
            // RET;
            return BattleAnim_ResetLCDStatCustom(bc);
    }
}

static void BattleBGEffect_Tackle(struct BattleBGEffect* bc) {
    // SET_PC(aBattleBGEffect_Tackle);
    // CALL(aBattleBGEffects_AnonJumptable);
    // uint8_t index = gb_read(REG_BC + BG_EFFECT_STRUCT_JT_INDEX);

// anon_dw:
    switch(bc->jumptableIndex){
        // if (index == 0) goto zero;
        case 0: {
        // zero:
            //  Prepares mon to move forward (player moves right, enemy moves left)
            //  BG_EFFECT_STRUCT_PARAM will keep track of distance moved, so it's reset to 0 here
            //  BG_EFFECT_STRUCT_BATTLE_TURN is set to 2 or -2 depending on target
            // CALL(aBattleBGEffects_IncAnonJumptableIndex);
            BattleBGEffects_IncAnonJumptableIndex(bc);
            // CALL(aBattleBGEffects_ClearLYOverrides);
            BattleBGEffects_ClearLYOverrides();
            // LD_A(LOW(rSCX));
            // CALL(aBattleBGEffect_SetLCDStatCustoms1);
            BattleBGEffect_SetLCDStatCustoms1(bc, LOW(rSCX));
            // LDH_A_addr(hLYOverrideEnd);
            // INC_A;
            // LDH_addr_A(hLYOverrideEnd);
            hram->hLYOverrideEnd++;
            // LD_HL(BG_EFFECT_STRUCT_PARAM);
            // ADD_HL_BC;
            // LD_hl(0);
            bc->param = 0;
            // CALL(aBGEffect_CheckBattleTurn);
            // IF_NZ goto player_side;
            // LD_A(2);
            // goto okay;

        // player_side:
            // LD_A(-2);

        // okay:
            // LD_hl_A;
            bc->battleTurn = (BGEffect_CheckBattleTurn(bc) == 0)? 2: (uint8_t)-2;
            // RET;
        } return;
        // if (index == 1) return Tackle_MoveForward();
        case 1: return Tackle_MoveForward(bc);
        // if (index == 2) return Tackle_ReturnMove();
        case 2: return Tackle_ReturnMove(bc);
        // if (index == 3) goto three;
        case 3: {
        // three:
            // CALL(aBattleAnim_ResetLCDStatCustom);
            BattleAnim_ResetLCDStatCustom(bc);
            // RET;
        } return;
    }
}

static void BattleBGEffect_BodySlam(struct BattleBGEffect* bc) {
    PEEK("");
    // SET_PC(aBattleBGEffect_BodySlam);
    // CALL(aBattleBGEffects_AnonJumptable);
    // uint8_t index = gb_read(REG_BC + BG_EFFECT_STRUCT_JT_INDEX);

// anon_dw:
    switch(bc->jumptableIndex){
        // if (index == 0) goto zero;
        case 0: {
        // zero:
            //  Prepares mon to move forward (player moves right, enemy moves left)
            //  BG_EFFECT_STRUCT_PARAM will keep track of distance moved, so it's reset to 0 here
            //  BG_EFFECT_STRUCT_BATTLE_TURN is set to 2 or -2 depending on target
            // CALL(aBattleBGEffects_IncAnonJumptableIndex);
            BattleBGEffects_IncAnonJumptableIndex(bc);
            // CALL(aBattleBGEffects_ClearLYOverrides);
            BattleBGEffects_ClearLYOverrides();
            // LD_A(LOW(rSCX));
            // CALL(aBattleBGEffect_SetLCDStatCustoms2);
            BattleBGEffect_SetLCDStatCustoms2(bc, LOW(rSCX));
            // LDH_A_addr(hLYOverrideEnd);
            // INC_A;
            // LDH_addr_A(hLYOverrideEnd);
            hram->hLYOverrideEnd++;
            // LD_HL(BG_EFFECT_STRUCT_PARAM);
            // ADD_HL_BC;
            // LD_hl(0);
            bc->param = 0;
            // CALL(aBGEffect_CheckBattleTurn);
            // IF_NZ goto player_side;
            // LD_A(2);
            // goto okay;

        // player_side:
            // LD_A(-2);

        // okay:
            // LD_hl_A;
            bc->battleTurn = (BGEffect_CheckBattleTurn(bc) == 0)? 2: (uint8_t)-2;
            // RET;
        } return;
        // if (index == 1) return Tackle_MoveForward();
        case 1: return Tackle_MoveForward(bc);
        // if (index == 2) return Tackle_ReturnMove();
        case 2: return Tackle_ReturnMove(bc);
        // if (index == 3) goto three;
        case 3: {
        // three:
            // CALL(aBattleAnim_ResetLCDStatCustom);
            BattleAnim_ResetLCDStatCustom(bc);
            // RET;
        } return;
    }
}

static void Tackle_MoveForward(struct BattleBGEffect* bc) {
    // SET_PC(aTackle_MoveForward);
    //  Moves user horizontally in a direction that can be positive or negative. When the limit is reached (8 pixels) we move to the next function in the jumptable (Tackle_ReturnMove)
    //  BG_EFFECT_STRUCT_BATTLE_TURN: speed and direction
    //  BG_EFFECT_STRUCT_PARAM: keeps track of distance moved
    // LD_HL(BG_EFFECT_STRUCT_PARAM);
    // ADD_HL_BC;
    // LD_A_hl;
    // CP_A(-8);
    // IF_Z goto reached_limit;
    // CP_A(8);
    // IF_NZ goto finish;
    if(bc->param == (uint8_t)-8 || bc->param == 8){
    // reached_limit:
        // CALL(aBattleBGEffects_IncAnonJumptableIndex);
        BattleBGEffects_IncAnonJumptableIndex(bc);
    }

// finish:
    // CALL(aRollout_FillLYOverridesBackup);
    Rollout_FillLYOverridesBackup(bc->param);
    // LD_HL(BG_EFFECT_STRUCT_BATTLE_TURN);
    // ADD_HL_BC;
    // LD_A_hl;
    // LD_HL(BG_EFFECT_STRUCT_PARAM);
    // ADD_HL_BC;
    // ADD_A_hl;
    // LD_hl_A;
    bc->param += bc->battleTurn;
    // RET;
}

static void Tackle_ReturnMove(struct BattleBGEffect* bc) {
    // SET_PC(aTackle_ReturnMove);
    //  Move user horizontally back to initial position. When we back to position 0, we move to the next function in the jumptable
    //  BG_EFFECT_STRUCT_BATTLE_TURN: is turned into a negative number (this number is not saved to preserve the initial number)
    //  BG_EFFECT_STRUCT_PARAM: keeps track of distance moved
    // LD_HL(BG_EFFECT_STRUCT_PARAM);
    // ADD_HL_BC;
    // LD_A_hl;
    // AND_A_A;
    // IF_NZ goto move_back;
    if(bc->param == 0x0){
        // CALL(aBattleBGEffects_IncAnonJumptableIndex);
        BattleBGEffects_IncAnonJumptableIndex(bc);
    }

// move_back:
    // CALL(aRollout_FillLYOverridesBackup);
    Rollout_FillLYOverridesBackup(bc->param);
    // LD_HL(BG_EFFECT_STRUCT_BATTLE_TURN);
    // ADD_HL_BC;
    // LD_A_hl;
    // XOR_A(0xff);
    // INC_A;
    // LD_HL(BG_EFFECT_STRUCT_PARAM);
    // ADD_HL_BC;
    // ADD_A_hl;
    // LD_hl_A;
    bc->param += (bc->battleTurn ^ 0xff) + 1;
    // RET;
}

static void Rollout_FillLYOverridesBackup(uint8_t a) {
    // SET_PC(aRollout_FillLYOverridesBackup);
    // PUSH_AF;
    // LD_A_addr(wFXAnimID + 1);
    // OR_A_A;
    // IF_NZ goto not_rollout;
    // LD_A_addr(wFXAnimID);
    // CP_A(ROLLOUT);
    // IF_Z goto rollout;
    if(wram->wFXAnimID != ROLLOUT){
    // not_rollout:
        // POP_AF;
        // JP(mBGEffect_FillLYOverridesBackup);
        return BGEffect_FillLYOverridesBackup(a);
    }

// rollout:
    // LDH_A_addr(hLYOverrideStart);
    // LD_D_A;
    // LDH_A_addr(hLYOverrideEnd);
    // SUB_A_D;
    // LD_D_A;
    uint8_t d = hram->hLYOverrideEnd - hram->hLYOverrideStart;
    // LD_H(HIGH(wLYOverridesBackup));
    // LDH_A_addr(hSCY);
    // OR_A_A;
    // IF_NZ goto skip1;
    uint8_t* hl;
    if(hram->hSCY != 0){
    // skip1:
        // LDH_A_addr(hLYOverrideEnd);
        // DEC_A;
        // LD_L_A;
        hl = wram->wLYOverridesBackup + (hram->hLYOverrideEnd - 1);
        // LD_hl(0x0);
        *hl = 0x0;
    }
    // LDH_A_addr(hLYOverrideStart);
    // OR_A_A;
    // IF_Z goto skip2;
    else if(hram->hLYOverrideStart != 0) {
        // DEC_A;
        // LD_L_A;
        hl = wram->wLYOverridesBackup + (hram->hLYOverrideStart - 1);
        // LD_hl(0x0);
        *hl = 0x0;
        // goto skip2;
    }

// skip2:
    // LDH_A_addr(hSCY);
    // LD_L_A;
    // LDH_A_addr(hLYOverrideStart);
    // SUB_A_L;
    // IF_NC goto skip3;
    if(hram->hLYOverrideStart < hram->hSCY){
        // XOR_A_A;
        hl = wram->wLYOverridesBackup;
        // DEC_D;
        --d;
    }
    else {
        hl = wram->wLYOverridesBackup + (hram->hLYOverrideStart - hram->hSCY);
    }

// skip3:
    // LD_L_A;
    // POP_AF;
    do {
    // loop:
        // LD_hli_A;
        *(hl++) = a;
        // DEC_D;
        // IF_NZ goto loop;
    } while(--d != 0);
    // RET;
}

static void BattleBGEffect_BetaPursuit(struct BattleBGEffect* bc) {
    // SET_PC(aBattleBGEffect_BetaPursuit);
    //  //  unused
    // CALL(aBattleBGEffects_AnonJumptable);
    // uint8_t index = gb_read(REG_BC + BG_EFFECT_STRUCT_JT_INDEX);

// anon_dw:
    switch(bc->jumptableIndex){
        // if (index == 0) return VitalThrow_MoveBackwards();
        case 0: return VitalThrow_MoveBackwards(bc);
        // if (index == 1) return Tackle_MoveForward();
        case 1: return Tackle_MoveForward(bc);
        // if (index == 2) return Tackle_ReturnMove();
        case 2: return Tackle_ReturnMove(bc);
        // if (index == 3) goto three;
        case 3: {
        // three:
            // CALL(aBattleAnim_ResetLCDStatCustom);
            BattleAnim_ResetLCDStatCustom(bc);
            // RET;
        } return;
    }
}

//  Prepares mon to move back back (player moves left, enemy moves right)
//  BG_EFFECT_STRUCT_PARAM: keeps track of distance moved, so it's reset to 0 here
static void VitalThrow_MoveBackwards(struct BattleBGEffect* bc) {
    // SET_PC(aVitalThrow_MoveBackwards);
    // CALL(aBattleBGEffects_IncAnonJumptableIndex);
    BattleBGEffects_IncAnonJumptableIndex(bc);
    // CALL(aBattleBGEffects_ClearLYOverrides);
    BattleBGEffects_ClearLYOverrides();
    // LD_A(LOW(rSCX));
    // CALL(aBattleBGEffect_SetLCDStatCustoms1);
    BattleBGEffect_SetLCDStatCustoms1(bc, LOW(rSCX));
    // LDH_A_addr(hLYOverrideEnd);
    // INC_A;
    // LDH_addr_A(hLYOverrideEnd);
    hram->hLYOverrideEnd++;
    // LD_HL(BG_EFFECT_STRUCT_PARAM);
    // ADD_HL_BC;
    // LD_hl(0x0);
    bc->param = 0x0;
    // CALL(aBGEffect_CheckBattleTurn);
    // IF_NZ goto player_turn;
    // LD_A(-2);
    // goto okay;

// player_turn:
    // LD_A(2);

// okay:
    // LD_hl_A;
    bc->battleTurn = (BGEffect_CheckBattleTurn(bc) == 0)? (uint8_t)-2: 2;
    // RET;
}

static void BattleBGEffect_VitalThrow(struct BattleBGEffect* bc) {
    // SET_PC(aBattleBGEffect_VitalThrow);
    // CALL(aBattleBGEffects_AnonJumptable);
    // uint8_t index = gb_read(REG_BC + BG_EFFECT_STRUCT_JT_INDEX);

// anon_dw:
    switch(bc->jumptableIndex){
        // if (index == 0) return VitalThrow_MoveBackwards();
        case 0: return VitalThrow_MoveBackwards(bc);
        // if (index == 1) return Tackle_MoveForward();
        case 1: return Tackle_MoveForward(bc);
        // if (index == 2) goto two;
        case 2: return;
        // if (index == 3) return Tackle_ReturnMove();
        case 3: return Tackle_MoveForward(bc);
        // if (index == 4) goto four;
        case 4: {
        // four:
            // CALL(aBattleAnim_ResetLCDStatCustom);
            BattleAnim_ResetLCDStatCustom(bc);
        } return;
    }

// two:
    // RET;
}

//  Similar to BattleBGEffect_WobblePlayer, except it can affect either side and the sine movement has a radius of 8 instead of 6 and it moves at twice the rate
static void BattleBGEffect_WobbleMon(struct BattleBGEffect* bc) {
    PEEK("");
    // SET_PC(aBattleBGEffect_WobbleMon);
    // CALL(aBattleBGEffects_AnonJumptable);
    // uint8_t index = gb_read(REG_BC + BG_EFFECT_STRUCT_JT_INDEX);

// anon_dw:
    switch(bc->jumptableIndex){
        // if (index == 0) goto zero;
        case 0: {
        // zero:
            // CALL(aBattleBGEffects_IncAnonJumptableIndex);
            BattleBGEffects_IncAnonJumptableIndex(bc);
            // CALL(aBattleBGEffects_ClearLYOverrides);
            BattleBGEffects_ClearLYOverrides();
            // LD_A(LOW(rSCX));
            // CALL(aBattleBGEffect_SetLCDStatCustoms1);
            BattleBGEffect_SetLCDStatCustoms1(bc, LOW(rSCX));
            // LDH_A_addr(hLYOverrideEnd);
            // INC_A;
            // LDH_addr_A(hLYOverrideEnd);
            hram->hLYOverrideEnd++;
            // LD_HL(BG_EFFECT_STRUCT_PARAM);
            // ADD_HL_BC;
            // LD_hl(0x0);
            bc->param = 0x0;
            // RET;
        } return;
        // if (index == 1) goto one;
        case 1: {
        // one:
            // LD_HL(BG_EFFECT_STRUCT_PARAM);
            // ADD_HL_BC;
            // LD_A_hl;
            // LD_D(0x8);
            // CALL(aBattleBGEffects_Sine);
            // CALL(aBGEffect_FillLYOverridesBackup);
            BGEffect_FillLYOverridesBackup(Sine(bc->param, 0x8));
            // LD_HL(BG_EFFECT_STRUCT_PARAM);
            // ADD_HL_BC;
            // LD_A_hl;
            // ADD_A(0x4);
            // LD_hl_A;
            bc->param += 0x4;
            // RET;
        } return;
        // if (index == 2) goto two;
        case 2:
        // two:
            // CALL(aBattleAnim_ResetLCDStatCustom);
            BattleAnim_ResetLCDStatCustom(bc);
            // RET;
            return;
    }
}

static void BattleBGEffect_Flail(struct BattleBGEffect* bc) {
    // SET_PC(aBattleBGEffect_Flail);
    // CALL(aBattleBGEffects_AnonJumptable);
    // uint8_t index = gb_read(REG_BC + BG_EFFECT_STRUCT_JT_INDEX);

// anon_dw:
    switch(bc->jumptableIndex){
        // if (index == 0) goto zero;
        case 0:{
        // zero:
            // CALL(aBattleBGEffects_IncAnonJumptableIndex);
            BattleBGEffects_IncAnonJumptableIndex(bc);
            // CALL(aBattleBGEffects_ClearLYOverrides);
            BattleBGEffects_ClearLYOverrides();
            // LD_A(LOW(rSCX));
            // CALL(aBattleBGEffect_SetLCDStatCustoms1);
            BattleBGEffect_SetLCDStatCustoms1(bc, LOW(rSCX));
            // LDH_A_addr(hLYOverrideEnd);
            // INC_A;
            // LDH_addr_A(hLYOverrideEnd);
            hram->hLYOverrideEnd++;
            // XOR_A_A;
            // LD_HL(BG_EFFECT_STRUCT_BATTLE_TURN);
            // ADD_HL_BC;
            // LD_hli_A;
            bc->battleTurn = 0;
            // LD_hl_A;
            bc->param = 0;
            // RET;
        } return;
        // if (index == 1) goto one;
        case 1: {
        // one:
            // LD_HL(BG_EFFECT_STRUCT_PARAM);
            // ADD_HL_BC;
            // LD_A_hl;
            // LD_D(0x6);
            // CALL(aBattleBGEffects_Sine);
            // PUSH_AF;
            uint8_t a = Sine(bc->param, 0x6);
            // LD_HL(BG_EFFECT_STRUCT_BATTLE_TURN);
            // ADD_HL_BC;
            // LD_A_hl;
            // LD_D(0x2);
            // CALL(aBattleBGEffects_Sine);
            // LD_E_A;
            uint8_t e = Sine(bc->battleTurn, 0x2);
            // POP_AF;
            // ADD_A_E;
            // CALL(aBGEffect_FillLYOverridesBackup);
            BGEffect_FillLYOverridesBackup(a + e);
            // LD_HL(BG_EFFECT_STRUCT_BATTLE_TURN);
            // ADD_HL_BC;
            // LD_A_hl;
            // ADD_A(0x8);
            // LD_hl_A;
            bc->battleTurn += 0x8;
            // LD_HL(BG_EFFECT_STRUCT_PARAM);
            // ADD_HL_BC;
            // LD_A_hl;
            // ADD_A(0x2);
            // LD_hl_A;
            bc->param += 0x2;
            // RET;
        } return;
        // if (index == 2) goto two;
        case 2: {
        // two:
            // CALL(aBattleAnim_ResetLCDStatCustom);
            BattleAnim_ResetLCDStatCustom(bc);
            // RET;
        } return;
    }
}

static void BattleBGEffect_WaveDeformMon(struct BattleBGEffect* bc) {
    PEEK("");
    // SET_PC(aBattleBGEffect_WaveDeformMon);
    // CALL(aBattleBGEffects_AnonJumptable);
    // uint8_t index = gb_read(REG_BC + BG_EFFECT_STRUCT_JT_INDEX);

// anon_dw:
    switch(bc->jumptableIndex){
        // if (index == 0) goto zero;
        case 0: {
        // zero:
            // CALL(aBattleBGEffects_IncAnonJumptableIndex);
            BattleBGEffects_IncAnonJumptableIndex(bc);
            // CALL(aBattleBGEffects_ClearLYOverrides);
            BattleBGEffects_ClearLYOverrides();
            // LD_A(LOW(rSCX));
            // CALL(aBattleBGEffect_SetLCDStatCustoms1);
            BattleBGEffect_SetLCDStatCustoms1(bc, LOW(rSCX));
            // RET;
        } return;
        // if (index == 1) goto one;
        case 1: {
        // one:
            // LD_HL(BG_EFFECT_STRUCT_PARAM);
            // ADD_HL_BC;
            // LD_A_hl;
            // CP_A(0x20);
            // RET_NC;
            if(bc->param >= 0x20)
                return;
            // INC_hl;
            // LD_D_A;
            // LD_E(4);
            // CALL(aDeformScreen);
            DeformScreen(bc->param++, 4);
            // RET;
        } return;
        // if (index == 2) goto two;
        case 2: {
        // two:
            // LD_HL(BG_EFFECT_STRUCT_PARAM);
            // ADD_HL_BC;
            // LD_A_hl;
            // AND_A_A;
            // IF_Z goto reset;
            if(bc->param == 0){
            // reset:
                // CALL(aBattleAnim_ResetLCDStatCustom);
                BattleAnim_ResetLCDStatCustom(bc);
                // RET;
                return;
            }
            // DEC_hl;
            // LD_D_A;
            // LD_E(4);
            // CALL(aDeformScreen);
            DeformScreen(bc->param--, 4);
            // RET;
        } return;
    }
}

static void BattleBGEffect_BounceDown(struct BattleBGEffect* bc) {
    PEEK("");
    // SET_PC(aBattleBGEffect_BounceDown);
    // CALL(aBattleBGEffects_AnonJumptable);
    // uint8_t index = gb_read(REG_BC + BG_EFFECT_STRUCT_JT_INDEX);

// anon_dw:
    switch(bc->jumptableIndex){
        // if (index == 0) goto zero;
        case 0:
        // zero:
            // CALL(aBattleBGEffects_IncAnonJumptableIndex);
            BattleBGEffects_IncAnonJumptableIndex(bc);
            // CALL(aBattleBGEffects_ClearLYOverrides);
            BattleBGEffects_ClearLYOverrides();
            // LD_A(LOW(rSCY));
            // CALL(aBattleBGEffect_SetLCDStatCustoms2);
            BattleBGEffect_SetLCDStatCustoms2(bc, LOW(rSCY));
            // LDH_A_addr(hLYOverrideEnd);
            // INC_A;
            // LDH_addr_A(hLYOverrideEnd);
            hram->hLYOverrideEnd++;
            // LD_HL(BG_EFFECT_STRUCT_BATTLE_TURN);
            // ADD_HL_BC;
            // LD_hl(0x1);
            bc->battleTurn = 0x1;
            // LD_HL(BG_EFFECT_STRUCT_PARAM);
            // ADD_HL_BC;
            // LD_hl(0x20);
            bc->param = 0x20;
            // RET;
            return;
        // if (index == 1) goto one;
        case 1: {
        // one:
            // LD_HL(BG_EFFECT_STRUCT_BATTLE_TURN);
            // ADD_HL_BC;
            // LD_A_hl;
            // CP_A(0x38);
            // RET_NC;
            if(bc->battleTurn >= 0x38)
                return;
            // PUSH_AF;
            uint8_t bt = bc->battleTurn;
            // LD_HL(BG_EFFECT_STRUCT_PARAM);
            // ADD_HL_BC;
            // LD_A_hl;
            // LD_D(0x10);
            // CALL(aBattleBGEffects_Cosine);
            // ADD_A(0x10);
            // LD_D_A;
            uint8_t d = Cosine(bc->param, 0x10) + 0x10;
            // POP_AF;
            // ADD_A_D;
            // CALL(aBGEffect_DisplaceLYOverridesBackup);
            BGEffect_DisplaceLYOverridesBackup(bt + d);
            // LD_HL(BG_EFFECT_STRUCT_PARAM);
            // ADD_HL_BC;
            // INC_hl;
            // INC_hl;
            bc->param += 2;
            // RET;
        } return;
        // if (index == 2) goto two;
        case 2:
        // two:
            // CALL(aBattleAnim_ResetLCDStatCustom);
            // RET;
            return BattleAnim_ResetLCDStatCustom(bc);
    }
}

void BattleBGEffect_BetaSendOutMon1(void) {
    SET_PC(aBattleBGEffect_BetaSendOutMon1);
    //  //  unused
    // CALL(aBattleBGEffects_AnonJumptable);
    uint8_t index = gb_read(REG_BC + BG_EFFECT_STRUCT_JT_INDEX);

anon_dw:

    if (index == 0) goto zero;
    if (index == 1) goto one;
    if (index == 2) goto two;
    if (index == 3) goto three;
    if (index == 4) goto four;
    if (index == 5) goto five;

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
    uint8_t index = gb_read(REG_BC + BG_EFFECT_STRUCT_JT_INDEX);

anon_dw:

    if (index == 0) goto zero;
    if (index == 1) goto one;

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

static void BattleBGEffect_FadeMonsToBlackRepeating(struct BattleBGEffect* bc) {
    static const uint8_t CGB_DMGEnemyData[] = {
        0xe4, 0xe4,
        0xf8, 0x90,
        0xfc, 0x40,
        0xf8, 0x90,
    };
    // SET_PC(aBattleBGEffect_FadeMonsToBlackRepeating);
    // uint8_t index;
    // LDH_A_addr(hCGB);
    // AND_A_A;
    // IF_NZ goto cgb;
    // index = gb_read(REG_BC + BG_EFFECT_STRUCT_JT_INDEX);
    // CALL(aBattleBGEffects_AnonJumptable);
    if(hram->hCGB == 0) {
    // anon_dw:

    //     if (index == 0) goto zero;
    //     if (index == 1) goto one;
    //     if (index == 2) goto two;

    // zero:

    //     CALL(aBattleBGEffects_IncAnonJumptableIndex);
    //     LD_A(0xe4);
    //     CALL(aBattleBGEffects_SetLYOverrides);
    //     LD_A(LOW(rBGP));
    //     LDH_addr_A(hLCDCPointer);
    //     XOR_A_A;
    //     LDH_addr_A(hLYOverrideStart);
    //     LD_A(0x60);
    //     LDH_addr_A(hLYOverrideEnd);
    //     RET;

    // one:

    //     LD_HL(BG_EFFECT_STRUCT_PARAM);
    //     ADD_HL_BC;
    //     LD_A_hl;
    //     INC_hl;
    //     LD_E_A;
    //     AND_A(0x7);
    //     RET_NZ;
    //     LD_A_E;
    //     AND_A(0x18);
    //     SLA_A;
    //     SWAP_A;
    //     SLA_A;
    //     LD_E_A;
    //     LD_D(0);
    //     PUSH_BC;
    //     CALL(aBGEffect_CheckBattleTurn);
    //     IF_NZ goto player;
    //     LD_HL(mBattleBGEffect_FadeMonsToBlackRepeating_CGB_DMGEnemyData);
    //     ADD_HL_DE;
    //     LD_A_hli;
    //     LD_addr_A(wOBP1);
    //     LD_D_A;
    //     LD_E_hl;
    //     LD_BC((0x2f << 8) | 0x30);
    //     goto okay;

    // player:

    //     LD_HL(mBattleBGEffect_FadeMonsToBlackRepeating_DMG_PlayerData);
    //     ADD_HL_DE;
    //     LD_D_hl;
    //     INC_HL;
    //     LD_A_hl;
    //     LD_addr_A(wOBP1);
    //     LD_E_A;
    //     LD_BC((0x37 << 8) | 0x28);

    // okay:

    //     CALL(aBattleBGEffect_FadeMonsToBlackRepeating_DMG_LYOverrideLoads);
    //     POP_BC;
    //     RET;

    // two:

    //     CALL(aBattleBGEffects_ResetVideoHRAM);
    //     LD_A(0xe4);
    //     LD_addr_A(wBGP);
    //     LD_addr_A(wOBP1);
    //     RET;

    // DMG_LYOverrideLoads:

    //     LD_HL(wLYOverridesBackup);

    // loop1:

    //     LD_hl_D;
    //     INC_HL;
    //     DEC_B;
    //     IF_NZ goto loop1;

    // loop2:

    //     LD_hl_E;
    //     INC_HL;
    //     DEC_C;
    //     IF_NZ goto loop2;
    //     RET;
    }
    else {
    // cgb:
        // LD_DE(mBattleBGEffect_FadeMonsToBlackRepeating_Jumptable);
        // CALL(aBatttleBGEffects_GetNamedJumptablePointer);
        // JP_hl;
        // index = gb_read(REG_BC + BG_EFFECT_STRUCT_JT_INDEX);

        switch(bc->jumptableIndex) {
        // Jumptable:
            // if (index == 0) goto cgb_zero;
            case 0:
            // cgb_zero:
                // CALL(aBattleBGEffects_IncAnonJumptableIndex);
                BattleBGEffects_IncAnonJumptableIndex(bc);
                // LD_HL(BG_EFFECT_STRUCT_PARAM);
                // ADD_HL_BC;
                // LD_hl(0x0);
                bc->param = 0x0;
                // RET;
                return;
            // if (index == 1) goto cgb_one;
            case 1: {
            // cgb_one:
                // LD_HL(BG_EFFECT_STRUCT_PARAM);
                // ADD_HL_BC;
                // LD_A_hl;
                // INC_hl;
                // LD_E_A;
                uint8_t e = bc->param++;
                // AND_A(0x7);
                // RET_NZ;
                if(e & 0x7)
                    return;
                // LD_A_E;
                // AND_A(0x18);
                // SLA_A;
                // SWAP_A;
                // SLA_A;
                // LD_E_A;
                // LD_D(0);
                uint16_t offset = (((e & 0x18) << 1) >> 4) << 1;
                // CALL(aBGEffect_CheckBattleTurn);
                // IF_NZ goto player_2;
                if(BGEffect_CheckBattleTurn(bc)) {
                // player_2:
                    // LD_HL(mBattleBGEffect_FadeMonsToBlackRepeating_CGB_DMGEnemyData);
                    // ADD_HL_DE;
                    // LD_A_hli;
                    // PUSH_HL;
                    // CALL(aBGEffects_LoadBGPal0_OBPal1);
                    BGEffects_LoadBGPal0_OBPal1(CGB_DMGEnemyData[offset]);
                    // POP_HL;
                    // LD_A_hl;
                    // CALL(aBGEffects_LoadBGPal1_OBPal0);
                    BGEffects_LoadBGPal1_OBPal0(CGB_DMGEnemyData[offset+1]);
                    // RET;
                }
                else {
                    // LD_HL(mBattleBGEffect_FadeMonsToBlackRepeating_CGB_DMGEnemyData);
                    // ADD_HL_DE;
                    // LD_A_hli;
                    // PUSH_HL;
                    // CALL(aBGEffects_LoadBGPal1_OBPal0);
                    BGEffects_LoadBGPal1_OBPal0(CGB_DMGEnemyData[offset]);
                    // POP_HL;
                    // LD_A_hl;
                    // CALL(aBGEffects_LoadBGPal0_OBPal1);
                    BGEffects_LoadBGPal0_OBPal1(CGB_DMGEnemyData[offset+1]);
                    // RET;
                }
            } return;
            // if (index == 2) goto cgb_two;
            case 2:
            // cgb_two:
                // LD_A(0xe4);
                // CALL(aBGEffects_LoadBGPal0_OBPal1);
                BGEffects_LoadBGPal0_OBPal1(0xe4);
                // LD_A(0xe4);
                // CALL(aBGEffects_LoadBGPal1_OBPal0);
                BGEffects_LoadBGPal1_OBPal0(0xe4);
                // CALL(aEndBattleBGEffect);
                EndBattleBGEffect(bc);
                // RET;
                return;
        }

    // DMG_PlayerData:

        // db ['0xe4', '0xe4'];
        // db ['0x90', '0xf8'];
        // db ['0x40', '0xfc'];
        // db ['0x90', '0xf8'];
    }
}

static void BattleBGEffect_RapidFlash(struct BattleBGEffect* bc) {
    // SET_PC(aBattleBGEffect_RapidFlash);
    //  //  unused
    // LD_DE(mBattleBGEffect_RapidFlash_FlashPals);
    static const uint8_t FlashPals[] = {0xe4, 0x6c, 0xfe};
    // CALL(aBGEffect_RapidCyclePals);
    BGEffect_RapidCyclePals(bc, FlashPals);
    // RET;
}

static void BattleBGEffect_FadeMonToLight(struct BattleBGEffect* bc) {
    // SET_PC(aBattleBGEffect_FadeMonToLight);
    //  BG_EFFECT_STRUCT_BATTLE_TURN = BG_EFFECT_TARGET or BG_EFFECT_USER
    static const uint8_t Pals[] = {0xe4, 0x90, 0x40, 0xff};
    // LD_DE(mBattleBGEffect_FadeMonToLight_Pals);
    // CALL(aBGEffect_RapidCyclePals);
    BGEffect_RapidCyclePals(bc, Pals);
    // RET;
}

static void BattleBGEffect_FadeMonToBlack(struct BattleBGEffect* bc) {
    // SET_PC(aBattleBGEffect_FadeMonToBlack);
    //  BG_EFFECT_STRUCT_BATTLE_TURN = BG_EFFECT_TARGET or BG_EFFECT_USER
    static const uint8_t Pals[] = {0xe4, 0xf8, 0xfc, 0xff};
    // LD_DE(mBattleBGEffect_FadeMonToBlack_Pals);
    // CALL(aBGEffect_RapidCyclePals);
    BGEffect_RapidCyclePals(bc, Pals);
    // RET;
}

static void BattleBGEffect_FadeMonToLightRepeating(struct BattleBGEffect* bc) {
    // SET_PC(aBattleBGEffect_FadeMonToLightRepeating);
    //  BG_EFFECT_STRUCT_BATTLE_TURN = BG_EFFECT_TARGET or BG_EFFECT_USER
    // LD_DE(mBattleBGEffect_FadeMonToLightRepeating_Pals);
    static const uint8_t Pals[] = {0xe4, 0x90, 0x40, 0x90, 0xfe};
    // CALL(aBGEffect_RapidCyclePals);
    BGEffect_RapidCyclePals(bc, Pals);
    // RET;
}

static void BattleBGEffect_FadeMonToBlackRepeating(struct BattleBGEffect* bc) {
    // SET_PC(aBattleBGEffect_FadeMonToBlackRepeating);
    //  BG_EFFECT_STRUCT_BATTLE_TURN = BG_EFFECT_TARGET or BG_EFFECT_USER
    // LD_DE(mBattleBGEffect_FadeMonToBlackRepeating_Pals);
    static const uint8_t Pals[] = {0xe4, 0xf8, 0xfc, 0xf8, 0xfe};
    // CALL(aBGEffect_RapidCyclePals);
    BGEffect_RapidCyclePals(bc, Pals);
    // RET;
}

static void BattleBGEffect_CycleMonLightDarkRepeating(struct BattleBGEffect* bc) {
    // SET_PC(aBattleBGEffect_CycleMonLightDarkRepeating);
    //  BG_EFFECT_STRUCT_BATTLE_TURN = BG_EFFECT_TARGET or BG_EFFECT_USER
    // LD_DE(mBattleBGEffect_CycleMonLightDarkRepeating_Pals);
    static const uint8_t Pals[] = {0xe4, 0xf8, 0xfc, 0xf8, 0xe4, 0x90, 0x40, 0x90, 0xfe};
    // CALL(aBGEffect_RapidCyclePals);
    BGEffect_RapidCyclePals(bc, Pals);
    // RET;
}

static void BattleBGEffect_FlashMonRepeating(struct BattleBGEffect* bc) {
    // SET_PC(aBattleBGEffect_FlashMonRepeating);
    //  //  unused
    //  BG_EFFECT_STRUCT_BATTLE_TURN = BG_EFFECT_TARGET or BG_EFFECT_USER
    // LD_DE(mBattleBGEffect_FlashMonRepeating_Pals);
    static const uint8_t Pals[] = {0xe4, 0xfc, 0xe4, 0x00, 0xfe};
    // CALL(aBGEffect_RapidCyclePals);
    BGEffect_RapidCyclePals(bc, Pals);
    // RET;
}

static void BattleBGEffect_FadeMonToWhiteWaitFadeBack(struct BattleBGEffect* bc) {
    // SET_PC(aBattleBGEffect_FadeMonToWhiteWaitFadeBack);
    //  BG_EFFECT_STRUCT_BATTLE_TURN = BG_EFFECT_TARGET or BG_EFFECT_USER
    // LD_DE(mBattleBGEffect_FadeMonToWhiteWaitFadeBack_Pals);
    static const uint8_t Pals[] = {
        0xe4, 0x90, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x90, 0xe4, 0xff
    };
    // CALL(aBGEffect_RapidCyclePals);
    BGEffect_RapidCyclePals(bc, Pals);
    // RET;
}

static void BattleBGEffect_FadeMonFromWhite(struct BattleBGEffect* bc) {
    // SET_PC(aBattleBGEffect_FadeMonFromWhite);
    //  //  unused
    //  BG_EFFECT_STRUCT_BATTLE_TURN = BG_EFFECT_TARGET or BG_EFFECT_USER
    // LD_DE(mBattleBGEffect_FadeMonFromWhite_Pals);
    static const uint8_t Pals[] = {0x00, 0x40, 0x90, 0xe4, 0xff};
    // CALL(aBGEffect_RapidCyclePals);
    BGEffect_RapidCyclePals(bc, Pals);
    // RET;
}

static void BattleBGEffect_VibrateMon(struct BattleBGEffect* bc) {
    // SET_PC(aBattleBGEffect_VibrateMon);
    //  Moves mon back and forth sideways for $20 frames
    //  BG_EFFECT_STRUCT_BATTLE_TURN = BG_EFFECT_TARGET or BG_EFFECT_USER
    // CALL(aBattleBGEffects_AnonJumptable);
    // uint8_t index = gb_read(REG_BC + BG_EFFECT_STRUCT_JT_INDEX);

// anon_dw:
    switch(bc->jumptableIndex){
        // if (index == 0) goto zero;
        case 0: {
        // zero:
            // CALL(aBattleBGEffects_IncAnonJumptableIndex);
            BattleBGEffects_IncAnonJumptableIndex(bc);
            // CALL(aBattleBGEffects_ClearLYOverrides);
            BattleBGEffects_ClearLYOverrides();
            // LD_A(LOW(rSCX));
            // CALL(aBattleBGEffect_SetLCDStatCustoms1);
            BattleBGEffect_SetLCDStatCustoms1(bc, LOW(rSCX));
            // LDH_A_addr(hLYOverrideEnd);
            // INC_A;
            // LDH_addr_A(hLYOverrideEnd);
            hram->hLYOverrideEnd++;
            // LD_HL(BG_EFFECT_STRUCT_BATTLE_TURN);
            // ADD_HL_BC;
            // LD_hl(0x1);
            bc->battleTurn = 0x1;
            // LD_HL(BG_EFFECT_STRUCT_PARAM);
            // ADD_HL_BC;
            // LD_hl(0x20);
            bc->param = 0x20;
            // RET;
        } return;
        // if (index == 1) goto one;
        case 1: {
        // one:
            // LD_HL(BG_EFFECT_STRUCT_PARAM);
            // ADD_HL_BC;
            // LD_A_hl;
            // AND_A_A;
            // IF_Z goto finish;
            if(bc->param == 0x0){
            // finish:
                // CALL(aBattleAnim_ResetLCDStatCustom);
                BattleAnim_ResetLCDStatCustom(bc);
                // RET;
                return;
            }
            // DEC_hl;
            uint8_t a = bc->param--;
            // AND_A(0x1);
            // RET_NZ;
            if(a & 0x1)
                return;
            // LD_HL(BG_EFFECT_STRUCT_BATTLE_TURN);
            // ADD_HL_BC;
            // LD_A_hl;
            // XOR_A(0xff);
            // INC_A;
            // LD_hl_A;
            bc->battleTurn = (bc->battleTurn ^ 0xff) + 1;
            // CALL(aBGEffect_FillLYOverridesBackup);
            BGEffect_FillLYOverridesBackup(bc->battleTurn);
            // RET;
        } return;
    }
}

static void BattleBGEffect_WobblePlayer(struct BattleBGEffect* bc) {
    // SET_PC(aBattleBGEffect_WobblePlayer);
    //  Always affects the player
    // CALL(aBattleBGEffects_AnonJumptable);
    // uint8_t index = gb_read(REG_BC + BG_EFFECT_STRUCT_JT_INDEX);

// anon_dw:
    switch(bc->jumptableIndex){
        // if (index == 0) goto zero;
        case 0:
        // zero:
            // CALL(aBattleBGEffects_IncAnonJumptableIndex);
            BattleBGEffects_IncAnonJumptableIndex(bc);
            // CALL(aBattleBGEffects_ClearLYOverrides);
            BattleBGEffects_ClearLYOverrides();
            // LD_A(LOW(rSCX));
            // LDH_addr_A(hLCDCPointer);
            hram->hLCDCPointer = LOW(rSCX);
            // XOR_A_A;
            // LDH_addr_A(hLYOverrideStart);
            hram->hLYOverrideStart = 0x0;
            // LD_A(0x37);
            // LDH_addr_A(hLYOverrideEnd);
            hram->hLYOverrideStart = 0x37;
            // LD_HL(BG_EFFECT_STRUCT_PARAM);
            // ADD_HL_BC;
            // LD_hl(0x0);
            bc->param = 0x0;
            // RET;
            return;
        // if (index == 1) goto one;
        case 1:
        // one:
            // LD_HL(BG_EFFECT_STRUCT_PARAM);
            // ADD_HL_BC;
            // LD_A_hl;
            // CP_A(0x40);
            // IF_NC goto two;
            if(bc->param < 0x40){
                // LD_D(0x6);
                // CALL(aBattleBGEffects_Sine);
                // CALL(aBGEffect_FillLYOverridesBackup);
                BGEffect_FillLYOverridesBackup(Sine(bc->param, 0x6));
                // LD_HL(BG_EFFECT_STRUCT_PARAM);
                // ADD_HL_BC;
                // LD_A_hl;
                // ADD_A(0x2);
                // LD_hl_A;
                bc->param += 0x2;
                // RET;
                return;
            }
            fallthrough;
        // if (index == 2) goto two;
        case 2:
        // two:
            // CALL(aBattleAnim_ResetLCDStatCustom);
            BattleAnim_ResetLCDStatCustom(bc);
            // RET;
            return;
    }
}

static void BattleBGEffect_Rollout(struct BattleBGEffect* bc) {
    // SET_PC(aBattleBGEffect_Rollout);
    // CALL(aBattleBGEffects_GetShakeAmount);
    u8_flag_s shake = BattleBGEffects_GetShakeAmount(bc);
    // IF_C goto xor_a;
    // BIT_A(7);
    // IF_Z goto okay;

// xor_a:
    // XOR_A_A;

// okay:
    uint8_t a = (!shake.flag && !bit_test(shake.a, 7))? shake.a: 0;
    // PUSH_AF;
    // CALL(aDelayFrame);
    DelayFrame();
    // POP_AF;
    // LDH_addr_A(hSCY);
    hram->hSCY = a;
    // XOR_A(0xff);
    // INC_A;
    // LD_addr_A(wAnimObject1YOffset);
    wram->wAnimObject[0].yOffset = (a ^ 0xff) + 1;
    // RET;
}

static void BattleBGEffect_ShakeScreenX(struct BattleBGEffect* bc) {
    // SET_PC(aBattleBGEffect_ShakeScreenX);
    // CALL(aBattleBGEffects_GetShakeAmount);
    // IF_NC goto skip;
    // XOR_A_A;

// skip:
    // LDH_addr_A(hSCX);
    hram->hSCX = BattleBGEffects_GetShakeAmount(bc).a;
    // RET;
}

static void BattleBGEffect_ShakeScreenY(struct BattleBGEffect* bc) {
    // SET_PC(aBattleBGEffect_ShakeScreenY);
    // CALL(aBattleBGEffects_GetShakeAmount);
    // IF_NC goto skip;
    // XOR_A_A;

// skip:
    // LDH_addr_A(hSCY);
    hram->hSCY = BattleBGEffects_GetShakeAmount(bc).a;
    // RET;
}

static u8_flag_s BattleBGEffects_GetShakeAmount(struct BattleBGEffect* bc) {
    // SET_PC(aBattleBGEffects_GetShakeAmount);
    // LD_HL(BG_EFFECT_STRUCT_JT_INDEX);
    // ADD_HL_BC;
    // LD_A_hl;
    // AND_A_A;
    // IF_NZ goto okay;
    if(bc->jumptableIndex == 0){
        // CALL(aEndBattleBGEffect);
        // SCF;
        // RET;
        return u8_flag(0, true);
    }

// okay:
    // DEC_hl;
    --bc->jumptableIndex;
    // LD_HL(BG_EFFECT_STRUCT_PARAM);
    // ADD_HL_BC;
    // LD_A_hl;
    // AND_A(0xf);
    // IF_Z goto every_16_frames;
    if((bc->param & 0xf) != 0){
        // DEC_hl;
        --bc->param;
        // LD_HL(BG_EFFECT_STRUCT_BATTLE_TURN);
        // ADD_HL_BC;
        // LD_A_hl;
        // AND_A_A;
        // RET;
        return u8_flag(bc->battleTurn, false);
    }

// every_16_frames:
    // LD_A_hl;
    // SWAP_A;
    // OR_A_hl;
    // LD_hl_A;
    bc->param |= (bc->param & 0xf0) >> 4;
    // LD_HL(BG_EFFECT_STRUCT_BATTLE_TURN);
    // ADD_HL_BC;
    // LD_A_hl;
    // XOR_A(0xff);
    // INC_A;
    // LD_hl_A;
    bc->battleTurn = (bc->battleTurn ^ 0xff) + 1;
    // AND_A_A;
    // RET;
    return u8_flag(bc->battleTurn, false);
}

static void BattleBGEffect_WobbleScreen(struct BattleBGEffect* bc) {
    // SET_PC(aBattleBGEffect_WobbleScreen);
    // LD_HL(BG_EFFECT_STRUCT_PARAM);
    // ADD_HL_BC;
    // LD_A_hl;
    // CP_A(0x40);
    // IF_NC goto finish;
    if(bc->param >= 0x40){
    // finish:
        // XOR_A_A;
        // LDH_addr_A(hSCX);
        hram->hSCX = 0x0;
        // RET;
        return;
    }
    // LD_D(0x6);
    // CALL(aBattleBGEffects_Sine);
    // LDH_addr_A(hSCX);
    hram->hSCX = Sine(bc->param, 0x6);
    // LD_HL(BG_EFFECT_STRUCT_PARAM);
    // ADD_HL_BC;
    // LD_A_hl;
    // ADD_A(0x2);
    // LD_hl_A;
    bc->param += 0x2;
    // RET;
}

static u8_flag_s BattleBGEffect_GetNthDMGPal(struct BattleBGEffect* bc, const uint8_t* de) {
    // SET_PC(aBattleBGEffect_GetNthDMGPal);
    // LD_HL(BG_EFFECT_STRUCT_JT_INDEX);
    // ADD_HL_BC;
    // LD_A_hl;
    // AND_A_A;
    // IF_Z goto zero;
    if(bc->jumptableIndex != 0){
        // DEC_hl;
        bc->jumptableIndex--;
        // LD_HL(BG_EFFECT_STRUCT_PARAM);
        // ADD_HL_BC;
        // LD_A_hl;
        // CALL(aBattleBGEffect_GetNextDMGPal);
        // RET;
        return BattleBGEffect_GetNextDMGPal(bc, de, bc->param);
    }

// zero:
    // LD_HL(BG_EFFECT_STRUCT_BATTLE_TURN);
    // ADD_HL_BC;
    // LD_A_hl;
    // LD_HL(BG_EFFECT_STRUCT_JT_INDEX);
    // ADD_HL_BC;
    // LD_hl_A;
    bc->jumptableIndex = bc->battleTurn;
    // CALL(aBattleBGEffect_GetFirstDMGPal);
    // RET;
    return BattleBGEffect_GetFirstDMGPal(bc, de);
}

static void BGEffect_RapidCyclePals(struct BattleBGEffect* bc, const uint8_t* de) {
    // SET_PC(aBGEffect_RapidCyclePals);
    // uint8_t index;
    //  Last index in DE: $fe signals a loop, $ff signals end
    // LDH_A_addr(hCGB);
    // AND_A_A;
    // IF_NZ goto Jumptable_CGB;
    // IF_NZ goto cgb;
    // PUSH_DE;
    // LD_DE(mBGEffect_RapidCyclePals_Jumptable_DMG);
    // CALL(aBatttleBGEffects_GetNamedJumptablePointer);
    // POP_DE;
    // JP_hl;
/*
Jumptable_DMG:

    index = gb_read(REG_BC + BG_EFFECT_STRUCT_JT_INDEX);
    if (index == 0) goto zero_dmg;
    if (index == 1) goto one_dmg;
    if (index == 2) goto two_dmg;

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
*/
// cgb:

    // PUSH_DE;
    // LD_DE(mBGEffect_RapidCyclePals_Jumptable_CGB);
    // CALL(aBatttleBGEffects_GetNamedJumptablePointer);
    // POP_DE;
    // JP_hl;

// Jumptable_CGB:
    // index = gb_read(REG_BC + BG_EFFECT_STRUCT_JT_INDEX);
    switch(bc->jumptableIndex){
        // if (index == 0) goto zero_cgb;
        case 0: {
        // zero_cgb:
            // CALL(aBGEffect_CheckBattleTurn);
            // IF_NZ goto player_turn_cgb;
            if(BGEffect_CheckBattleTurn(bc) == 0){
                // CALL(aBattleBGEffects_IncAnonJumptableIndex);
                BattleBGEffects_IncAnonJumptableIndex(bc);
                // CALL(aBattleBGEffects_IncAnonJumptableIndex);
                BattleBGEffects_IncAnonJumptableIndex(bc);
            }

        // player_turn_cgb:
            // CALL(aBattleBGEffects_IncAnonJumptableIndex);
            BattleBGEffects_IncAnonJumptableIndex(bc);
            // LD_HL(BG_EFFECT_STRUCT_PARAM);
            // ADD_HL_BC;
            // LD_A_hl;
            uint8_t param = bc->param;
            // LD_hl(0x0);
            bc->param = 0x0;
            // LD_HL(BG_EFFECT_STRUCT_BATTLE_TURN);
            // ADD_HL_BC;
            // LD_hl_A;
            bc->battleTurn = param;
            // RET;
        } return;
        // if (index == 1) goto one_cgb;
        case 1: {
        // one_cgb:
            // LD_HL(BG_EFFECT_STRUCT_BATTLE_TURN);
            // ADD_HL_BC;
            // LD_A_hl;
            // AND_A(0xf);
            // IF_Z goto okay_1_cgb;
            if(bc->battleTurn & 0xf){
                // DEC_hl;
                --bc->battleTurn;
                // RET;
                return;
            }

        // okay_1_cgb:
            // LD_A_hl;
            // SWAP_A;
            // OR_A_hl;
            // LD_hl_A;
            bc->battleTurn |= (bc->battleTurn >> 4);
            // CALL(aBattleBGEffect_GetFirstDMGPal);
            // IF_C goto okay_2_cgb;
            u8_flag_s res = BattleBGEffect_GetFirstDMGPal(bc, de);
            if(!res.flag){
                // CALL(aBGEffects_LoadBGPal0_OBPal1);
                BGEffects_LoadBGPal0_OBPal1(res.a);
                // RET;
                return;
            }

        // okay_2_cgb:
            // LD_HL(BG_EFFECT_STRUCT_PARAM);
            // ADD_HL_BC;
            // DEC_hl;
            bc->param--;
            // RET;
        } return;
        // if (index == 2) goto two_cgb;
        case 2: {
        // two_cgb:
            // LD_A(0xe4);
            // CALL(aBGEffects_LoadBGPal0_OBPal1);
            BGEffects_LoadBGPal0_OBPal1(0xe4);
            // CALL(aEndBattleBGEffect);
            EndBattleBGEffect(bc);
            // RET;
        } return;
        // if (index == 3) goto three_cgb;
        case 3: {
        // three_cgb:
            // LD_HL(BG_EFFECT_STRUCT_BATTLE_TURN);
            // ADD_HL_BC;
            // LD_A_hl;
            // AND_A(0xf);
            // IF_Z goto okay_3_cgb;
            if(bc->battleTurn & 0xf){
                // DEC_hl;
                bc->battleTurn--;
                // RET;
                return;
            }

        // okay_3_cgb:
            // LD_A_hl;
            // SWAP_A;
            // OR_A_hl;
            // LD_hl_A;
            bc->battleTurn |= (bc->battleTurn >> 4);
            // CALL(aBattleBGEffect_GetFirstDMGPal);
            // IF_C goto okay_4_cgb;
            u8_flag_s res = BattleBGEffect_GetFirstDMGPal(bc, de);
            if(!res.flag){
                // CALL(aBGEffects_LoadBGPal1_OBPal0);
                BGEffects_LoadBGPal1_OBPal0(res.a);
                // RET;
                return;
            }

        // okay_4_cgb:
            // LD_HL(BG_EFFECT_STRUCT_PARAM);
            // ADD_HL_BC;
            // DEC_hl;
            bc->param--;
            // RET;
        } return;
        // if (index == 4) goto four_cgb;
        case 4: {
        // four_cgb:
            // LD_A(0xe4);
            // CALL(aBGEffects_LoadBGPal1_OBPal0);
            BGEffects_LoadBGPal1_OBPal0(0xe4);
            // CALL(aEndBattleBGEffect);
            EndBattleBGEffect(bc);
            // RET;
        } return;
    }
}

static void BGEffects_LoadBGPal0_OBPal1(uint8_t a) {
    // SET_PC(aBGEffects_LoadBGPal0_OBPal1);
    // LD_H_A;
    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    // LD_A(MBANK(awBGPals1));
    // LDH_addr_A(rSVBK);
    // LD_A_H;
    // PUSH_BC;
    // PUSH_AF;
    // LD_HL(wBGPals2);
    // LD_DE(wBGPals1);
    // LD_B_A;
    // LD_C(0x1);
    // CALL(aCopyPals);
    CopyPals(wram->wBGPals2, wram->wBGPals1, a, 0x1);
    // LD_HL(wOBPals2 + PALETTE_SIZE * 1);
    // LD_DE(wOBPals1 + PALETTE_SIZE * 1);
    // POP_AF;
    // LD_B_A;
    // LD_C(0x1);
    // CALL(aCopyPals);
    CopyPals(wram->wOBPals2 + PALETTE_SIZE * 1, wram->wOBPals1 + PALETTE_SIZE * 1, a, 0x1);
    // POP_BC;
    // POP_AF;
    // LDH_addr_A(rSVBK);
    // LD_A(TRUE);
    // LDH_addr_A(hCGBPalUpdate);
    hram->hCGBPalUpdate = TRUE;
    // RET;
}

static void BGEffects_LoadBGPal1_OBPal0(uint8_t a) {
    // SET_PC(aBGEffects_LoadBGPal1_OBPal0);
    // LD_H_A;
    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    // LD_A(MBANK(awBGPals1));
    // LDH_addr_A(rSVBK);
    // LD_A_H;
    // PUSH_BC;
    // PUSH_AF;
    // LD_HL(wBGPals2 + PALETTE_SIZE * 1);
    // LD_DE(wBGPals1 + PALETTE_SIZE * 1);
    // LD_B_A;
    // LD_C(0x1);
    // CALL(aCopyPals);
    CopyPals(wram->wBGPals2 + PALETTE_SIZE * 1, wram->wBGPals1 + PALETTE_SIZE * 1, a, 0x1);
    // LD_HL(wOBPals2);
    // LD_DE(wOBPals1);
    // POP_AF;
    // LD_B_A;
    // LD_C(0x1);
    // CALL(aCopyPals);
    CopyPals(wram->wOBPals2, wram->wOBPals1, a, 0x1);
    // POP_BC;
    // POP_AF;
    // LDH_addr_A(rSVBK);
    // LD_A(TRUE);
    // LDH_addr_A(hCGBPalUpdate);
    hram->hCGBPalUpdate = TRUE;
    // RET;
}

static u8_flag_s BattleBGEffect_GetFirstDMGPal(struct BattleBGEffect* bc, const uint8_t* de) {
    // SET_PC(aBattleBGEffect_GetFirstDMGPal);
    // LD_HL(BG_EFFECT_STRUCT_PARAM);
    // ADD_HL_BC;
    // LD_A_hl;
    // INC_hl;
    uint8_t a = bc->param++;
    return BattleBGEffect_GetNextDMGPal(bc, de, a);
}

static u8_flag_s BattleBGEffect_GetNextDMGPal(struct BattleBGEffect* bc, const uint8_t* de, uint8_t a) {
    // SET_PC(aBattleBGEffect_GetNextDMGPal);
    // LD_L_A;
    // LD_H(0);
    // ADD_HL_DE;
    // LD_A_hl;
    uint8_t x = de[a];
    // CP_A(-1);
    // IF_Z goto quit;
    if(x == (uint8_t)-1){
    // quit:
        // SCF;
        // RET;
        return u8_flag(x, true);
    }
    // CP_A(-2);
    // IF_NZ goto repeat;
    if(x == (uint8_t)-2){
        // LD_A_de;
        x = *de;
        // LD_HL(BG_EFFECT_STRUCT_PARAM);
        // ADD_HL_BC;
        // LD_hl(0x0);
        bc->param = 0x0;
    }

// repeat:
    // AND_A_A;
    // RET;
    return u8_flag(x, false);
}

static void BattleBGEffects_ClearLYOverrides(void) {
    // SET_PC(aBattleBGEffects_ClearLYOverrides);
    // XOR_A_A;
    return BattleBGEffects_SetLYOverrides(0x0);
}

static void BattleBGEffects_SetLYOverrides(uint8_t a) {
    // SET_PC(aBattleBGEffects_SetLYOverrides);
    // LD_HL(wLYOverrides);
    uint8_t* hl = wram->wLYOverrides;
    // LD_E(0x99);
    uint8_t e = 0x99;

    do {
    // loop1:
        // LD_hli_A;
        *(hl++) = a;
        // DEC_E;
        // IF_NZ goto loop1;
    } while(--e != 0);
    // LD_HL(wLYOverridesBackup);
    hl = wram->wLYOverridesBackup;
    // LD_E(0x91);
    e = 0x91;

    do {
    // loop2:
        // LD_hli_A;
        *(hl++) = a;
        // DEC_E;
        // IF_NZ goto loop2;
    } while(--e != 0);
    // RET;
}

static void BattleBGEffect_SetLCDStatCustoms1(struct BattleBGEffect* bc, uint8_t a) {
    // SET_PC(aBattleBGEffect_SetLCDStatCustoms1);
    // LDH_addr_A(hLCDCPointer);
    hram->hLCDCPointer = a;
    // CALL(aBGEffect_CheckBattleTurn);
    // IF_NZ goto player_turn;
    // LD_DE((0x00 << 8) | 0x36);
    // goto okay;

// player_turn:
    // LD_DE((0x2f << 8) | 0x5e);
    uint16_t de = (BGEffect_CheckBattleTurn(bc) == 0)? (0x00 << 8) | 0x36 : (0x2f << 8) | 0x5e;

// okay:
    // LD_A_D;
    // LDH_addr_A(hLYOverrideStart);
    hram->hLYOverrideStart = HIGH(de);
    // LD_A_E;
    // LDH_addr_A(hLYOverrideEnd);
    hram->hLYOverrideEnd = LOW(de);
    // RET;
}

static void BattleBGEffect_SetLCDStatCustoms2(struct BattleBGEffect* bc, uint8_t a) {
    // SET_PC(aBattleBGEffect_SetLCDStatCustoms2);
    // LDH_addr_A(hLCDCPointer);
    hram->hLCDCPointer = a;
    // CALL(aBGEffect_CheckBattleTurn);
    // IF_NZ goto player_turn;
    // LD_DE((0x00 << 8) | 0x36);
    // goto okay;

// player_turn:
    // LD_DE((0x2d << 8) | 0x5e);
    uint16_t de = (BGEffect_CheckBattleTurn(bc) == 0)? (0x00 << 8) | 0x36 : (0x2d << 8) | 0x5e;

// okay:
    // LD_A_D;
    // LDH_addr_A(hLYOverrideStart);
    hram->hLYOverrideStart = HIGH(de);
    // LD_A_E;
    // LDH_addr_A(hLYOverrideEnd);
    hram->hLYOverrideEnd = LOW(de);
    // RET;
}

static void BattleAnim_ResetLCDStatCustom(struct BattleBGEffect* bc) {
    // SET_PC(aBattleAnim_ResetLCDStatCustom);
    // XOR_A_A;
    // LDH_addr_A(hLYOverrideStart);
    hram->hLYOverrideStart = 0x0;
    // LDH_addr_A(hLYOverrideEnd);
    hram->hLYOverrideEnd = 0x0;
    // CALL(aBattleBGEffects_ClearLYOverrides);
    BattleBGEffects_ClearLYOverrides();
    // XOR_A_A;
    // LDH_addr_A(hLCDCPointer);
    hram->hLCDCPointer = 0x0;
    // CALL(aEndBattleBGEffect);
    EndBattleBGEffect(bc);
    // RET;
}

void BattleBGEffects_ResetVideoHRAM(void) {
    // SET_PC(aBattleBGEffects_ResetVideoHRAM);
    // XOR_A_A;
    // LDH_addr_A(hLCDCPointer);
    hram->hLCDCPointer = 0x0;
    // LD_A(0b11100100);
    // LDH_addr_A(rBGP);
    gb_write(rBGP, 0b11100100);
    // LD_addr_A(wBGP);
    wram->wBGP = 0b11100100;
    // LD_addr_A(wOBP1);
    wram->wOBP1 = 0b11100100;
    // LDH_addr_A(hLYOverrideStart);
    hram->hLYOverrideStart = 0b11100100; // Is this correct?
    // LDH_addr_A(hLYOverrideEnd);
    hram->hLYOverrideEnd = 0b11100100; // Is this correct?
    // CALL(aBattleBGEffects_ClearLYOverrides);
    BattleBGEffects_ClearLYOverrides();
    // RET;
}

static void DeformScreen(uint8_t d, uint8_t e) {
    // SET_PC(aDeformScreen);
    // PUSH_BC;
    // XOR_A_A;
    // LD_addr_A(wBattleSineWaveTempProgress);
    wram->wBattleSineWaveTempProgress = 0x0;
    // LD_A_E;
    // LD_addr_A(wBattleSineWaveTempOffset);
    wram->wBattleSineWaveTempOffset = e;
    // LD_A_D;
    // LD_addr_A(wBattleSineWaveTempAmplitude);
    wram->wBattleSineWaveTempAmplitude = d;
    // LD_A(0x80);
    // LD_addr_A(wBattleSineWaveTempTimer);
    wram->wBattleSineWaveTempTimer = 0x80;
    // LD_BC(wLYOverridesBackup);
    uint8_t* hl = wram->wLYOverridesBackup;
    uint8_t c = 0;

    do {
    // loop:
        // LDH_A_addr(hLYOverrideStart);
        // CP_A_C;
        // IF_NC goto next;
        // LDH_A_addr(hLYOverrideEnd);
        // CP_A_C;
        // IF_C goto next;
        if(hram->hLYOverrideStart < c && hram->hLYOverrideEnd >= c){
            // LD_A_addr(wBattleSineWaveTempAmplitude);
            // LD_D_A;
            // LD_A_addr(wBattleSineWaveTempProgress);
            // CALL(aBattleBGEffects_Sine);
            // LD_bc_A;
            hl[c] = Sine(wram->wBattleSineWaveTempProgress, wram->wBattleSineWaveTempAmplitude);
        }

    // next:
        // INC_BC;
        c++;
        // LD_A_addr(wBattleSineWaveTempOffset);
        // LD_HL(wBattleSineWaveTempProgress);
        // ADD_A_hl;
        // LD_hl_A;
        wram->wBattleSineWaveTempProgress += wram->wBattleSineWaveTempOffset;
        // LD_HL(wBattleSineWaveTempTimer);
        // DEC_hl;
        // IF_NZ goto loop;
    } while(--wram->wBattleSineWaveTempTimer != 0);
    // POP_BC;
    // RET;
}

static void InitSurfWaves(uint8_t d, uint8_t e) {
    // SET_PC(aInitSurfWaves);
    // PUSH_BC;
    // XOR_A_A;
    // LD_addr_A(wBattleSineWaveTempProgress);
    wram->wBattleSineWaveTempProgress = 0;
    // LD_A_E;
    // LD_addr_A(wBattleSineWaveTempOffset);
    wram->wBattleSineWaveTempOffset = e;
    // LD_A_D;
    // LD_addr_A(wBattleSineWaveTempAmplitude);
    wram->wBattleSineWaveTempAmplitude = d;
    // LD_A(0x40);
    // LD_addr_A(wBattleSineWaveTempTimer);
    wram->wBattleSineWaveTempTimer = 0x40;
    // LD_BC(wSurfWaveBGEffect);
    uint8_t* bc = wram->wSurfWaveBGEffect;

    do {
    // loop:
        // LD_A_addr(wBattleSineWaveTempAmplitude);
        // LD_D_A;
        // LD_A_addr(wBattleSineWaveTempProgress);
        // CALL(aBattleBGEffects_Sine);
        // LD_bc_A;
        // INC_BC;
        *(bc++) = Sine(wram->wBattleSineWaveTempProgress, wram->wBattleSineWaveTempAmplitude);
        // LD_A_addr(wBattleSineWaveTempOffset);
        // LD_HL(wBattleSineWaveTempProgress);
        // ADD_A_hl;
        // LD_hl_A;
        wram->wBattleSineWaveTempProgress += wram->wBattleSineWaveTempOffset;
        // LD_HL(wBattleSineWaveTempTimer);
        // DEC_hl;
        // IF_NZ goto loop;
    } while(--wram->wBattleSineWaveTempTimer != 0);
    // POP_BC;
    // RET;
}

static uint8_t DeformWater_GetLYOverrideBackupAddrOffset(void){
    // LDH_A_addr(hLYOverrideStart);
    // LD_E_A;
    // LD_A_addr(wBattleSineWaveTempProgress);
    // ADD_A_E;
    // LD_E_A;
    // LD_D(0);
    // RET;
    return wram->wBattleSineWaveTempProgress + hram->hLYOverrideStart;
}

static void DeformWater(uint8_t d, uint8_t e, uint8_t a) {
    // SET_PC(aDeformWater);
    // PUSH_BC;
    // LD_addr_A(wBattleSineWaveTempTimer);
    wram->wBattleSineWaveTempTimer = a;
    // LD_A_E;
    // LD_addr_A(wBattleSineWaveTempOffset);
    wram->wBattleSineWaveTempOffset = e;
    // LD_A_D;
    // LD_addr_A(wBattleSineWaveTempAmplitude);
    wram->wBattleSineWaveTempAmplitude = d;
    // CALL(aDeformWater_GetLYOverrideBackupAddrOffset);
    // LD_HL(wLYOverridesBackup);
    // ADD_HL_DE;
    uint8_t c = DeformWater_GetLYOverrideBackupAddrOffset();
    uint8_t c2 = c;
    // LD_C_L;
    // LD_B_H;
    uint8_t* hl = wram->wLYOverridesBackup;

    while(wram->wBattleSineWaveTempTimer != 0){
    // loop:
        // LD_A_addr(wBattleSineWaveTempTimer);
        // AND_A_A;
        // IF_Z goto done;
        // DEC_A;
        // LD_addr_A(wBattleSineWaveTempTimer);
        --wram->wBattleSineWaveTempTimer;
        // PUSH_AF;
        // LD_A_addr(wBattleSineWaveTempAmplitude);
        // LD_D_A;
        // LD_A_addr(wBattleSineWaveTempOffset);
        // PUSH_HL;
        // CALL(aBattleBGEffects_Sine);
        // LD_E_A;
        uint8_t e2 = Sine(wram->wBattleSineWaveTempOffset, wram->wBattleSineWaveTempAmplitude);
        // POP_HL;
        // LDH_A_addr(hLYOverrideEnd);
        // CP_A_C;
        // IF_C goto skip1;
        if(hram->hLYOverrideEnd >= c2){
            // LD_A_E;
            // LD_bc_A;
            hl[c2] = e2;
            // INC_BC;
            c2++;
        }

    // skip1:
        // LDH_A_addr(hLYOverrideStart);
        // CP_A_L;
        // IF_NC goto skip2;
        if(hram->hLYOverrideStart < c){
            // LD_hl_E;
            hl[c] = e2;
            // DEC_HL;
            --c;
        }

    // skip2:
        // LD_A_addr(wBattleSineWaveTempOffset);
        // ADD_A(0x4);
        // LD_addr_A(wBattleSineWaveTempOffset);
        wram->wBattleSineWaveTempOffset += 0x4;
        // POP_AF;
        // goto loop;
    }

// done:
    // POP_BC;
    // AND_A_A;
    // RET;
}

static void BattleBGEffect_WavyScreenFX(void) {
    // SET_PC(aBattleBGEffect_WavyScreenFX);
    // PUSH_BC;
    // LDH_A_addr(hLYOverrideStart);
    // LD_L_A;
    uint8_t l = hram->hLYOverrideStart;
    // INC_A;
    // LD_E_A;
    uint8_t e = l + 1;
    // LD_H(HIGH(wLYOverridesBackup));
    // LD_D_H;
    // LDH_A_addr(hLYOverrideEnd);
    // SUB_A_L;
    // AND_A_A;
    // IF_Z goto done;
    if(hram->hLYOverrideEnd == l)
        return;
    // LD_C_A;
    uint8_t c = hram->hLYOverrideEnd - l;
    // LD_A_hl;
    // PUSH_AF;
    uint8_t a = wram->wLYOverridesBackup[l];

    do {
    // loop:
        // LD_A_de;
        // INC_DE;
        // LD_hli_A;
        wram->wLYOverridesBackup[l++] = wram->wLYOverridesBackup[e++];
        // DEC_C;
        // IF_NZ goto loop;
    } while(--c != 0);
    // POP_AF;
    // LD_hl_A;
    wram->wLYOverridesBackup[l] = a;

// done:
    // POP_BC;
    // RET;
}

static void BGEffect_FillLYOverridesBackup(uint8_t a) {
    // SET_PC(aBGEffect_FillLYOverridesBackup);
    // PUSH_AF;
    // LD_H(HIGH(wLYOverridesBackup));
    // LDH_A_addr(hLYOverrideStart);
    // LD_L_A;
    // LDH_A_addr(hLYOverrideEnd);
    // SUB_A_L;
    // LD_D_A;
    // POP_AF;
    uint8_t d = hram->hLYOverrideEnd - hram->hLYOverrideStart;
    uint8_t* hl = wram->wLYOverridesBackup + hram->hLYOverrideStart;

    do {
    // loop:
        // LD_hli_A;
        *(hl++) = a;
        // DEC_D;
        // IF_NZ goto loop;
    } while(--d != 0);
    // RET;
}

// e = a
// d = [hLYOverrideEnd] - [hLYOverrideStart] - a
static void BGEffect_DisplaceLYOverridesBackup(uint8_t a) {
    // SET_PC(aBGEffect_DisplaceLYOverridesBackup);
    // PUSH_AF;
    // LD_E_A;
    uint8_t e = a;
    // LDH_A_addr(hLYOverrideStart);
    // LD_L_A;
    // LDH_A_addr(hLYOverrideEnd);
    // SUB_A_L;
    // SUB_A_E;
    // LD_D_A;
    uint8_t d = hram->hLYOverrideEnd - hram->hLYOverrideStart - a;
    // LD_H(HIGH(wLYOverridesBackup));
    // LDH_A_addr(hLYOverrideStart);
    // LD_L_A;
    uint8_t l = hram->hLYOverrideStart;
    // LD_A(0x90);

    do {
    // loop:
        // LD_hli_A;
        wram->wLYOverridesBackup[l++] = 0x90;
        // DEC_E;
        // IF_NZ goto loop;
    } while(--e != 0);
    // POP_AF;
    // XOR_A(0xff);

    do {
    // loop2:
        // LD_hli_A;
        wram->wLYOverridesBackup[l++] = a ^ 0xff;
        // DEC_D;
        // IF_NZ goto loop2;
    } while(--d != 0);
    // RET;
}

static uint8_t BGEffect_CheckBattleTurn(struct BattleBGEffect* bc) {
    // SET_PC(aBGEffect_CheckBattleTurn);
    // LD_HL(BG_EFFECT_STRUCT_BATTLE_TURN);
    // ADD_HL_BC;
    // LDH_A_addr(hBattleTurn);
    // AND_A(0x1);
    // XOR_A_hl;
    // RET;
    return (hram->hBattleTurn & 0x1) ^ bc->battleTurn;
}

static bool BGEffect_CheckFlyDigStatus(struct BattleBGEffect* bc) {
    // SET_PC(aBGEffect_CheckFlyDigStatus);
    // LD_HL(BG_EFFECT_STRUCT_BATTLE_TURN);
    // ADD_HL_BC;
    // LDH_A_addr(hBattleTurn);
    // AND_A(0x1);
    // XOR_A_hl;
    // IF_NZ goto player;
    if((hram->hBattleTurn & 0x1) ^ bc->battleTurn){
    // player:
        // LD_A_addr(wPlayerSubStatus3);  // PlayerSubStatus3
        // AND_A(1 << SUBSTATUS_FLYING | 1 << SUBSTATUS_UNDERGROUND);
        // RET;
        return (wram->wPlayerSubStatus3 & (1 << SUBSTATUS_FLYING | 1 << SUBSTATUS_UNDERGROUND)) != 0;
    }
    // LD_A_addr(wEnemySubStatus3);  // EnemySubStatus3
    // AND_A(1 << SUBSTATUS_FLYING | 1 << SUBSTATUS_UNDERGROUND);
    // RET;
    return (wram->wEnemySubStatus3 & (1 << SUBSTATUS_FLYING | 1 << SUBSTATUS_UNDERGROUND)) != 0;
}

static bool BattleBGEffects_CheckSGB(void) {
    // SET_PC(aBattleBGEffects_CheckSGB);
    // LDH_A_addr(hSGB);
    // AND_A_A;
    // RET;
    return hram->hSGB != 0;
}

uint8_t BattleBGEffects_Sine(uint8_t e, uint8_t d) {
    // SET_PC(aBattleBGEffects_Sine);
    // LD_E_A;
    // CALLFAR(aBattleAnim_Sine_e);
    // LD_A_E;
    // RET;
    return Sine(e, d);
}

uint8_t BattleBGEffects_Cosine(uint8_t e, uint8_t d) {
    // SET_PC(aBattleBGEffects_Cosine);
    // LD_E_A;
    // CALLFAR(aBattleAnim_Cosine_e);
    // LD_A_E;
    // RET;
    return Cosine(e, d);
}
