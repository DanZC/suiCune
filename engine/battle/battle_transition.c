#include "../../constants.h"
#include "battle_transition.h"
#include "../overworld/init_map.h"
#include "../../home/delay.h"
#include "../../home/map_objects.h"
#include "../../home/tilemap.h"
#include "../../home/copy.h"
#include "../../home/palettes.h"
#include "../../home/clear_sprites.h"
#include "../../home/random.h"
#include "../../home/sine.h"
#include "../overworld/map_objects.h"

static const char TrainerBattlePokeballTiles[] = "gfx/overworld/trainer_battle_pokeball_tiles.png";

//  BattleTransitionJumptable.Jumptable indexes
#define BATTLETRANSITION_CAVE     (0x01)
#define BATTLETRANSITION_CAVE_STRONGER (0x09)
#define BATTLETRANSITION_NO_CAVE (0x10)
#define BATTLETRANSITION_NO_CAVE_STRONGER (0x18)
#define BATTLETRANSITION_FINISH (0x20)
#define BATTLETRANSITION_END (0x80)

#define BATTLETRANSITION_SQUARE (0xFE)  //  $fe
#define BATTLETRANSITION_BLACK (0xFF)  //  $ff

static void DoBattleTransition_InitGFX(void) {
    // LD_A_addr(wLinkMode);
    // CP_A(LINK_MOBILE);
    // IF_Z goto mobile;
    if(wram->wLinkMode == LINK_MOBILE) {
    // mobile:
        // CALL(aLoadTrainerBattlePokeballTiles);
        LoadTrainerBattlePokeballTiles();
    }
    else {
        // FARCALL(aReanchorBGMap_NoOAMUpdate);
        ReanchorBGMap_NoOAMUpdate();
        // CALL(aUpdateSprites);
        UpdateSprites();
        // CALL(aDelayFrame);
        DelayFrame();
        // CALL(aDoBattleTransition_NonMobile_LoadPokeballTiles);
        LoadTrainerBattlePokeballTiles();
        // CALL(aBattleStart_CopyTilemapAtOnce);
        CopyTilemapAtOnce();
        // goto resume;
    }
// resume:
    // LD_A(SCREEN_HEIGHT_PX);
    // LDH_addr_A(hWY);
    hram->hWY = SCREEN_HEIGHT_PX;
    // CALL(aDelayFrame);
    DelayFrame();
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = BGMAPMODE_NONE;
    // LD_HL(wJumptableIndex);
    // XOR_A_A;
    // LD_hli_A;
    wram->wJumptableIndex = 0;
    // LD_hli_A;
    wram->wBattleTransitionCounter = 0;
    // LD_hl_A;
    wram->wBattleTransitionSpinQuadrant = 0;
    // CALL(aWipeLYOverrides);
    WipeLYOverrides();
    // RET;


// NonMobile_LoadPokeballTiles:
    // CALL(aLoadTrainerBattlePokeballTiles);
    // hlbgcoord(0, 0, vBGMap0);
    // CALL(aConvertTrainerBattlePokeballTilesTo2bpp);
    // RET;
}

void DoBattleTransition(void){
    PEEK("");
    // CALL(aDoBattleTransition_InitGFX);
    DoBattleTransition_InitGFX();
    // LDH_A_addr(rBGP);
    // LD_addr_A(wBGP);
    wram->wBGP = gb_read(rBGP);
    // LDH_A_addr(rOBP0);
    // LD_addr_A(wOBP0);
    wram->wOBP0 = gb_read(rOBP0);
    // LDH_A_addr(rOBP1);
    // LD_addr_A(wOBP1);
    wram->wOBP1 = gb_read(rOBP1);
    // CALL(aDelayFrame);
    DelayFrame();
    // LD_HL(hVBlank);
    // LD_A_hl;
    // PUSH_AF;
    uint8_t vblank = hram->hVBlank;
    // LD_hl(0x1);
    hram->hVBlank = 0x1;

    while(1) {
    // loop:
        // LD_A_addr(wJumptableIndex);
        // BIT_A(7);  // BATTLETRANSITION_END?
        // IF_NZ goto done;
        if(bit_test(wram->wJumptableIndex, 7))
            break;
        // CALL(aBattleTransitionJumptable);
        BattleTransitionJumptable();
        // CALL(aDelayFrame);
        DelayFrame();
        // goto loop;
    }


// done:
    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    // LD_A(MBANK(awBGPals1));
    // LDH_addr_A(rSVBK);

    // LD_HL(wBGPals1);
    // LD_BC(8 * PALETTE_SIZE);
    // XOR_A_A;
    // CALL(aByteFill);
    ByteFill(wram->wBGPals1, 0, 8 * PALETTE_SIZE);

    // POP_AF;
    // LDH_addr_A(rSVBK);

    // LD_A(0b11111111);
    // LD_addr_A(wBGP);
    wram->wBGP = 0b11111111;
    // CALL(aDmgToCgbBGPals);
    DmgToCgbBGPals(0b11111111);
    // CALL(aDelayFrame);
    DelayFrame();
    // XOR_A_A;
    // LDH_addr_A(hLCDCPointer);
    hram->hLCDCPointer = 0;
    // LDH_addr_A(hLYOverrideStart);
    hram->hLYOverrideStart = 0;
    // LDH_addr_A(hLYOverrideEnd);
    hram->hLYOverrideStart = 0;
    // LDH_addr_A(hSCY);
    hram->hSCY = 0;

    // LD_A(0x1);  // unnecessary bankswitch?
    // LDH_addr_A(rSVBK);
    // POP_AF;
    // LDH_addr_A(hVBlank);
    hram->hVBlank = vblank;
    // CALL(aDelayFrame);
    DelayFrame();
    // PEEK("end");
    // RET;
}

//  Load the tiles used in the Pokeball Graphic that fills the screen
//  at the start of every Trainer battle.
void LoadTrainerBattlePokeballTiles(void){
    // LD_DE(mTrainerBattlePokeballTiles);
    // LD_HL(vTiles0 + LEN_2BPP_TILE * BATTLETRANSITION_SQUARE);
    // LD_B(BANK(aTrainerBattlePokeballTiles));
    // LD_C(2);
    // CALL(aRequest2bpp);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles0 + LEN_2BPP_TILE * BATTLETRANSITION_SQUARE, TrainerBattlePokeballTiles, 0, 2);

    // LDH_A_addr(rVBK);
    // PUSH_AF;
    // LD_A(0x1);
    // LDH_addr_A(rVBK);

    // LD_DE(mTrainerBattlePokeballTiles);
    // LD_HL(vTiles3 + LEN_2BPP_TILE * BATTLETRANSITION_SQUARE);
    // LD_B(BANK(aTrainerBattlePokeballTiles));
    // LD_C(2);
    // CALL(aRequest2bpp);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles3 + LEN_2BPP_TILE * BATTLETRANSITION_SQUARE, TrainerBattlePokeballTiles, 0, 2);

    // POP_AF;
    // LDH_addr_A(rVBK);
    // RET;
}

void ConvertTrainerBattlePokeballTilesTo2bpp(void){
    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(MBANK(awDecompressScratch));
    LDH_addr_A(rSVBK);
    PUSH_HL;
    LD_HL(wDecompressScratch);
    LD_BC(0x28 * LEN_2BPP_TILE);


loop:
    LD_hl(-1);
    INC_HL;
    DEC_BC;
    LD_A_C;
    OR_A_B;
    IF_NZ goto loop;

    POP_HL;
    LD_DE(wDecompressScratch);
    //LD_B(BANK(@));
    LD_B(BANK(aConvertTrainerBattlePokeballTilesTo2bpp));
    LD_C(0x28);
    CALL(aRequest2bpp);
    POP_AF;
    LDH_addr_A(rSVBK);
    RET;

}

void BattleTransitionJumptable(void){
    //jumptable ['.Jumptable', 'wJumptableIndex']
    // fast_jumptable(mBattleTransitionJumptable_Jumptable, wJumptableIndex);
    switch(wram->wJumptableIndex) {
// Jumptable:
    //dw ['StartTrainerBattle_DetermineWhichAnimation'];  // 00
        case 0x00: return StartTrainerBattle_DetermineWhichAnimation();

// BATTLETRANSITION_CAVE
    //dw ['StartTrainerBattle_LoadPokeBallGraphics'];  // 01
        case 0x01: return StartTrainerBattle_LoadPokeBallGraphics();
    //dw ['StartTrainerBattle_SetUpBGMap'];  // 02
        case 0x02: return StartTrainerBattle_SetUpBGMap();
    //dw ['StartTrainerBattle_Flash'];  // 03
        case 0x03: return StartTrainerBattle_Flash();
    //dw ['StartTrainerBattle_Flash'];  // 04
        case 0x04: return StartTrainerBattle_Flash();
    //dw ['StartTrainerBattle_Flash'];  // 05
        case 0x05: return StartTrainerBattle_Flash();
    //dw ['StartTrainerBattle_NextScene'];  // 06
        case 0x06: return StartTrainerBattle_NextScene();
    //dw ['StartTrainerBattle_SetUpForWavyOutro'];  // 07
        case 0x07: return StartTrainerBattle_SetUpForWavyOutro();
    //dw ['StartTrainerBattle_SineWave'];  // 08
        case 0x08: return StartTrainerBattle_SineWave();

// BATTLETRANSITION_CAVE_STRONGER
    //dw ['StartTrainerBattle_LoadPokeBallGraphics'];  // 09
        case 0x09: return StartTrainerBattle_LoadPokeBallGraphics();
    //dw ['StartTrainerBattle_SetUpBGMap'];  // 0a
        case 0x0a: return StartTrainerBattle_SetUpBGMap();
    //dw ['StartTrainerBattle_Flash'];  // 0b
        case 0x0b: return StartTrainerBattle_Flash();
    //dw ['StartTrainerBattle_Flash'];  // 0c
        case 0x0c: return StartTrainerBattle_Flash();
    //dw ['StartTrainerBattle_Flash'];  // 0d
        case 0x0d: return StartTrainerBattle_Flash();
    //dw ['StartTrainerBattle_NextScene'];  // 0e
        case 0x0e: return StartTrainerBattle_NextScene();
// There is no setup for this one
    //dw ['StartTrainerBattle_ZoomToBlack'];  // 0f
        case 0x0f: return StartTrainerBattle_ZoomToBlack();

// BATTLETRANSITION_NO_CAVE
    //dw ['StartTrainerBattle_LoadPokeBallGraphics'];  // 10
        case 0x10: return StartTrainerBattle_LoadPokeBallGraphics();
    //dw ['StartTrainerBattle_SetUpBGMap'];  // 11
        case 0x11: return StartTrainerBattle_SetUpBGMap();
    //dw ['StartTrainerBattle_Flash'];  // 12
        case 0x12: return StartTrainerBattle_Flash();
    //dw ['StartTrainerBattle_Flash'];  // 13
        case 0x13: return StartTrainerBattle_Flash();
    //dw ['StartTrainerBattle_Flash'];  // 14
        case 0x14: return StartTrainerBattle_Flash();
    //dw ['StartTrainerBattle_NextScene'];  // 15
        case 0x15: return StartTrainerBattle_NextScene();
    //dw ['StartTrainerBattle_SetUpForSpinOutro'];  // 16
        case 0x16: return StartTrainerBattle_SetUpForSpinOutro();
    //dw ['StartTrainerBattle_SpinToBlack'];  // 17
        case 0x17: return StartTrainerBattle_SpinToBlack();

// BATTLETRANSITION_NO_CAVE_STRONGER
    //dw ['StartTrainerBattle_LoadPokeBallGraphics'];  // 18
        case 0x18: return StartTrainerBattle_LoadPokeBallGraphics();
    //dw ['StartTrainerBattle_SetUpBGMap'];  // 19
        case 0x19: return StartTrainerBattle_SetUpBGMap();
    //dw ['StartTrainerBattle_Flash'];  // 1a
        case 0x1a: return StartTrainerBattle_Flash();
    //dw ['StartTrainerBattle_Flash'];  // 1b
        case 0x1b: return StartTrainerBattle_Flash();
    //dw ['StartTrainerBattle_Flash'];  // 1c
        case 0x1c: return StartTrainerBattle_Flash();
    //dw ['StartTrainerBattle_NextScene'];  // 1d
        case 0x1d: return StartTrainerBattle_NextScene();
    //dw ['StartTrainerBattle_SetUpForRandomScatterOutro'];  // 1e
        case 0x1e: return StartTrainerBattle_SetUpForRandomScatterOutro();
    //dw ['StartTrainerBattle_SpeckleToBlack'];  // 1f
        case 0x1f: return StartTrainerBattle_SpeckleToBlack();

// BATTLETRANSITION_FINISH
    //dw ['StartTrainerBattle_Finish'];  // 20
        case 0x20: return StartTrainerBattle_Finish();
    }
    // RET;
}

//  transition animations
//const_def ['?']
enum {
    TRANS_CAVE,
    TRANS_CAVE_STRONGER,
    TRANS_NO_CAVE,
    TRANS_NO_CAVE_STRONGER,
};

//  transition animation bits
#define TRANS_STRONGER_F (0)  //  bit set in TRANS_CAVE_STRONGER and TRANS_NO_CAVE_STRONGER
#define TRANS_NO_CAVE_F (1)  //  bit set in TRANS_NO_CAVE and TRANS_NO_CAVE_STRONGER

//  The screen flashes a different number of times depending on the level of
//  your lead Pokemon relative to the opponent's.
void StartTrainerBattle_DetermineWhichAnimation(void){
//  BUG: wBattleMonLevel and wEnemyMonLevel are not set at this point, so whatever
//  values happen to be there will determine the animation.

    static const uint8_t StartingPoints[] = {
    //  entries correspond to TRANS_* constants
        [TRANS_CAVE]             = BATTLETRANSITION_CAVE,
        [TRANS_CAVE_STRONGER]    = BATTLETRANSITION_CAVE_STRONGER,
        [TRANS_NO_CAVE]          = BATTLETRANSITION_NO_CAVE,
        [TRANS_NO_CAVE_STRONGER] = BATTLETRANSITION_NO_CAVE_STRONGER,
    };

    // LD_DE(0);
    uint8_t e = 0;
    // LD_A_addr(wBattleMonLevel);
    // ADD_A(3);
    // LD_HL(wEnemyMonLevel);
    // CP_A_hl;
    // IF_NC goto not_stronger;
    if(wram->wBattleMon.level + 3 < wram->wEnemyMon.level) {
        // SET_E(TRANS_STRONGER_F);
        bit_set(e, TRANS_STRONGER_F);
    }

// not_stronger:
    // LD_A_addr(wEnvironment);
    // CP_A(CAVE);
    // IF_Z goto cave;
    // CP_A(ENVIRONMENT_5);
    // IF_Z goto cave;
    // CP_A(DUNGEON);
    // IF_Z goto cave;
    if(wram->wEnvironment != CAVE && wram->wEnvironment != ENVIRONMENT_5 && wram->wEnvironment != DUNGEON) {
        // SET_E(TRANS_NO_CAVE_F);
        bit_set(e, TRANS_NO_CAVE_F);
    }
// cave:
    // LD_HL(mStartTrainerBattle_DetermineWhichAnimation_StartingPoints);
    // ADD_HL_DE;
    // LD_A_hl;
    // LD_addr_A(wJumptableIndex);
    wram->wJumptableIndex = StartingPoints[e];
    // RET;
}

void StartTrainerBattle_Finish(void){
    // CALL(aClearSprites);
    ClearSprites();
    // LD_A(BATTLETRANSITION_END);
    // LD_addr_A(wJumptableIndex);
    wram->wJumptableIndex = BATTLETRANSITION_END;
    // RET;

}

void StartTrainerBattle_NextScene(void){
    // LD_HL(wJumptableIndex);
    // INC_hl;
    wram->wJumptableIndex++;
    // RET;

}

void StartTrainerBattle_SetUpBGMap(void){
    // CALL(aStartTrainerBattle_NextScene);
    StartTrainerBattle_NextScene();
    // XOR_A_A;
    // LD_addr_A(wBattleTransitionCounter);
    wram->wBattleTransitionCounter = 0;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = BGMAPMODE_NONE;
    // RET;

}

#define dc(a, b, c, d) ((a & 0x3) << 6) | ((b & 0x3) << 4) | ((c & 0x3) << 2) | (d & 0x3)

static bool StartTrainerBattle_Flash_DoFlashAnimation(void) {
    static const uint8_t pals[] = {
        dc(3, 3, 2, 1),
        dc(3, 3, 3, 2),
        dc(3, 3, 3, 3),
        dc(3, 3, 3, 2),
        dc(3, 3, 2, 1),
        dc(3, 2, 1, 0),
        dc(2, 1, 0, 0),
        dc(1, 0, 0, 0),
        dc(0, 0, 0, 0),
        dc(1, 0, 0, 0),
        dc(2, 1, 0, 0),
        dc(3, 2, 1, 0),
        dc(0, 0, 0, 1),
    };

    // LD_A_addr(wTimeOfDayPalset);
    // CP_A(DARKNESS_PALSET);
    // IF_Z goto done;
    if(wram->wTimeOfDayPalset == DARKNESS_PALSET) {
    // done:
        // XOR_A_A;
        // LD_addr_A(wBattleTransitionCounter);
        wram->wBattleTransitionCounter = 0;
        // SCF;
        // RET;
        return true;
    }
    // LD_HL(wBattleTransitionCounter);
    // LD_A_hl;
    uint8_t a = wram->wBattleTransitionCounter++;
    // INC_hl;
    // SRL_A;
    // LD_E_A;
    // LD_D(0);
    // LD_HL(mStartTrainerBattle_Flash_pals);
    // ADD_HL_DE;
    // LD_A_hl;
    a = pals[a >> 1];
    // CP_A(0b00000001);
    // IF_Z goto done;
    if(a != 0b00000001) {
        // LD_addr_A(wBGP);
        wram->wBGP = a;
        // CALL(aDmgToCgbBGPals);
        DmgToCgbBGPals(a);
        // AND_A_A;
        // RET;
        return false;
    }
    else {
    // done:
        // XOR_A_A;
        // LD_addr_A(wBattleTransitionCounter);
        wram->wBattleTransitionCounter = 0;
        // SCF;
        // RET;
        return true;
    }
}

void StartTrainerBattle_Flash(void){
    // CALL(aStartTrainerBattle_Flash_DoFlashAnimation);
    // RET_NC ;
    if(!StartTrainerBattle_Flash_DoFlashAnimation())
        return;
    // CALL(aStartTrainerBattle_NextScene);
    // RET;
    StartTrainerBattle_NextScene();
}

void StartTrainerBattle_SetUpForWavyOutro(void){
    PEEK("");
    // FARCALL(aRespawnPlayerAndOpponent);
    RespawnPlayerAndOpponent_Conv();
    // LD_A(MBANK(awLYOverrides));
    // LDH_addr_A(rSVBK);
    // CALL(aStartTrainerBattle_NextScene);
    StartTrainerBattle_NextScene();

    // LD_A(LOW(rSCX));
    // LDH_addr_A(hLCDCPointer);
    hram->hLCDCPointer = LOW(rSCX);
    // XOR_A_A;
    // LDH_addr_A(hLYOverrideStart);
    hram->hLYOverrideStart = 0;
    // LD_A(0x90);
    // LDH_addr_A(hLYOverrideEnd);
    hram->hLYOverrideEnd = 0x90;
    // XOR_A_A;
    // LD_addr_A(wBattleTransitionCounter);
    wram->wBattleTransitionCounter = 0;
    // LD_addr_A(wBattleTransitionSineWaveOffset);
    wram->wBattleTransitionSineWaveOffset = 0;
    // RET;
}

static void StartTrainerBattle_DoSineWave(void) {
    // LD_HL(wBattleTransitionSineWaveOffset);
    // LD_A_hl;
    // INC_hl;
    uint8_t a0 = wram->wBattleTransitionSineWaveOffset++;
    // LD_HL(wBattleTransitionCounter);
    // LD_D_hl;
    uint8_t d = wram->wBattleTransitionCounter;
    // ADD_A_hl;
    a0 += wram->wBattleTransitionCounter;
    // LD_hl_A;
    wram->wBattleTransitionCounter = a0;
    // LD_A(wLYOverridesEnd - wLYOverrides);
    // LD_BC(wLYOverrides);
    // LD_E(0);
    uint8_t e = 0;

    for(uint32_t a = 0; a < lengthof(wram->wLYOverrides); ++a) {
    // loop:
        // PUSH_AF;
        // PUSH_DE;
        // LD_A_E;
        // CALL(aStartTrainerBattle_DrawSineWave);
        // LD_bc_A;
        // INC_BC;
        wram->wLYOverrides[a] = Sine(e, d);
        // POP_DE;
        // LD_A_E;
        // ADD_A(2);
        // LD_E_A;
        e += 2;
        // POP_AF;
        // DEC_A;
        // IF_NZ goto loop;
    }
    // RET;
}

void StartTrainerBattle_SineWave(void){
    PEEK("");
    // LD_A_addr(wBattleTransitionCounter);
    // CP_A(0x60);
    // IF_NC goto end;
    if(wram->wBattleTransitionCounter >= 0x60) {
    // end:
        // LD_A(BATTLETRANSITION_FINISH);
        // LD_addr_A(wJumptableIndex);
        wram->wJumptableIndex = BATTLETRANSITION_FINISH;
        // RET;
        return;
    }
    // CALL(aStartTrainerBattle_SineWave_DoSineWave);
    StartTrainerBattle_DoSineWave();
    DelayFrames(2); // Needed since without it, the animation is too fast.
    // RET;
}

void StartTrainerBattle_SetUpForSpinOutro(void){
    // FARCALL(aRespawnPlayerAndOpponent);
    RespawnPlayerAndOpponent_Conv();
    // LD_A(MBANK(awLYOverrides));
    // LDH_addr_A(rSVBK);
    // CALL(aStartTrainerBattle_NextScene);
    StartTrainerBattle_NextScene();
    // XOR_A_A;
    // LD_addr_A(wBattleTransitionCounter);
    wram->wBattleTransitionCounter = 0;
    // RET;

}

typedef struct {
    uint8_t quadrant;
    const int8_t*  const wedge;
    uint8_t* const coord;
} spin_quadrant_s;

void StartTrainerBattle_SpinToBlack(void){
static const int8_t wedge1[] = {2, 3, 5, 4, 9, -1};
static const int8_t wedge2[] = {1, 1, 2, 2, 4, 2, 4, 2, 3, -1};
static const int8_t wedge3[] = {2, 1, 3, 1, 4, 1, 4, 1, 4, 1, 3, 1, 2, 1, 1, 1, 1, -1};
static const int8_t wedge4[] = {4, 1, 4, 0, 3, 1, 3, 0, 2, 1, 2, 0, 1, -1};
static const int8_t wedge5[] = {4, 0, 3, 0, 3, 0, 2, 0, 2, 0, 1, 0, 1, 0, 1, -1};

//  quadrants
    enum {
        UPPER_LEFT,
        UPPER_RIGHT,
        LOWER_LEFT,
        LOWER_RIGHT,
    };

//  quadrant bits
#define RIGHT_QUADRANT_F (0)  //  bit set in UPPER_RIGHT and LOWER_RIGHT
#define LOWER_QUADRANT_F (1)  //  bit set in LOWER_LEFT and LOWER_RIGHT
#define spin_quadrant(_0, _1, _2, _3) {_0, _1, .coord=coord(_2, _3, wram_ptr(wTilemap))}

    static const spin_quadrant_s spin_quadrants[] = {
// spin_quadrant: MACRO
//     db \1
//     dw \2
//     dwcoord \3, \4
// ENDM
        spin_quadrant(UPPER_LEFT, wedge1, 1, 6),
        spin_quadrant(UPPER_LEFT, wedge2, 0, 3),
        spin_quadrant(UPPER_LEFT, wedge3, 1, 0),
        spin_quadrant(UPPER_LEFT, wedge4, 5, 0),
        spin_quadrant(UPPER_LEFT, wedge5, 9, 0),
        spin_quadrant(UPPER_RIGHT, wedge5, 10, 0),
        spin_quadrant(UPPER_RIGHT, wedge4, 14, 0),
        spin_quadrant(UPPER_RIGHT, wedge3, 18, 0),
        spin_quadrant(UPPER_RIGHT, wedge2, 19, 3),
        spin_quadrant(UPPER_RIGHT, wedge1, 18, 6),
        spin_quadrant(LOWER_RIGHT, wedge1, 18, 11),
        spin_quadrant(LOWER_RIGHT, wedge2, 19, 14),
        spin_quadrant(LOWER_RIGHT, wedge3, 18, 17),
        spin_quadrant(LOWER_RIGHT, wedge4, 14, 17),
        spin_quadrant(LOWER_RIGHT, wedge5, 10, 17),
        spin_quadrant(LOWER_LEFT, wedge5, 9, 17),
        spin_quadrant(LOWER_LEFT, wedge4, 5, 17),
        spin_quadrant(LOWER_LEFT, wedge3, 1, 17),
        spin_quadrant(LOWER_LEFT, wedge2, 0, 14),
        spin_quadrant(LOWER_LEFT, wedge1, 1, 11),
        spin_quadrant(0xff, NULL, 0, 0),
    };

    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = BGMAPMODE_NONE;
    // LD_A_addr(wBattleTransitionCounter);
    // LD_E_A;
    // LD_D(0);
    // LD_HL(mStartTrainerBattle_SpinToBlack_spin_quadrants);
    // for(int rept = 0; rept < 5; rept++){
    // ADD_HL_DE;
    // }
    // LD_A_hli;
    // CP_A(-1);
    // IF_Z goto end;
    if(spin_quadrants[wram->wBattleTransitionCounter].quadrant != 0xff) {
        // LD_addr_A(wBattleTransitionSineWaveOffset);
        wram->wBattleTransitionSpinQuadrant = spin_quadrants[wram->wBattleTransitionCounter].quadrant;
        // CALL(aStartTrainerBattle_SpinToBlack_load);
        // load:
        // LD_A_hli;
        // LD_E_A;
        // LD_A_hli;
        // LD_D_A;
        const int8_t* de = spin_quadrants[wram->wBattleTransitionCounter].wedge;
        // LD_A_hli;
        // LD_H_hl;
        // LD_L_A;
        uint8_t* hl = spin_quadrants[wram->wBattleTransitionCounter].coord;

        while(1) {
        // loop:
            // PUSH_HL;
            uint8_t* hl2 = hl;
            // LD_A_de;
            // LD_C_A;
            // INC_DE;
            int8_t c = *(de++);

            do {
            // loop1:
                // LD_hl(BATTLETRANSITION_BLACK);
                *hl = BATTLETRANSITION_BLACK;
                // LD_A_addr(wBattleTransitionSineWaveOffset);
                // BIT_A(RIGHT_QUADRANT_F);
                // IF_Z goto leftside;
                if(bit_test(wram->wBattleTransitionSpinQuadrant, RIGHT_QUADRANT_F))
                    hl++;
                else
                    hl--;
                // INC_HL;
                // goto okay1;

            // leftside:
                // DEC_HL;

            // okay1:
                // DEC_C;
                // IF_NZ goto loop1;
            } while(--c != 0);
            // POP_HL;
            hl = hl2 + (bit_test(wram->wBattleTransitionSpinQuadrant, LOWER_QUADRANT_F)? -SCREEN_WIDTH: SCREEN_WIDTH);
            // LD_A_addr(wBattleTransitionSineWaveOffset);
            // BIT_A(LOWER_QUADRANT_F);
            // LD_BC(SCREEN_WIDTH);
            // IF_Z goto upper;
            // LD_BC(-SCREEN_WIDTH);

        // upper:
            // ADD_HL_BC;
            // LD_A_de;
            // INC_DE;
            // CP_A(-1);
            // RET_Z ;
            int8_t a = *(de++);
            if(a == -1) break;
            // AND_A_A;
            // IF_Z goto loop;
            if(a == 0) continue;
            // LD_C_A;

            do {
            // loop2:
                // LD_A_addr(wBattleTransitionSineWaveOffset);
                // BIT_A(RIGHT_QUADRANT_F);
                // IF_Z goto leftside2;
                if(bit_test(wram->wBattleTransitionSpinQuadrant, RIGHT_QUADRANT_F))
                    hl--;
                else
                    hl++;
                // DEC_HL;
                // goto okay2;

            // leftside2:
                // INC_HL;

            // okay2:
                // DEC_C;
                // IF_NZ goto loop2;
            } while(--a != 0);
            // goto loop;
        }
        // LD_A(1);
        // LDH_addr_A(hBGMapMode);
        hram->hBGMapMode = BGMAPMODE_UPDATE_TILES;
        // CALL(aDelayFrame);
        // CALL(aDelayFrame);
        DelayFrame();
        DelayFrame();
        // LD_HL(wBattleTransitionCounter);
        // INC_hl;
        wram->wBattleTransitionCounter++;
        // RET;
        return;
    }
// end:
    // LD_A(1);
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = BGMAPMODE_UPDATE_TILES;
    // CALL(aDelayFrame);
    // CALL(aDelayFrame);
    // CALL(aDelayFrame);
    DelayFrame();
    DelayFrame();
    DelayFrame();
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = BGMAPMODE_NONE;
    // LD_A(BATTLETRANSITION_FINISH);
    // LD_addr_A(wJumptableIndex);
    wram->wJumptableIndex = BATTLETRANSITION_FINISH;
    // RET;
}

void StartTrainerBattle_SetUpForRandomScatterOutro(void){
    // FARCALL(aRespawnPlayerAndOpponent);
    RespawnPlayerAndOpponent_Conv();
    // LD_A(MBANK(awLYOverrides));
    // LDH_addr_A(rSVBK);
    // CALL(aStartTrainerBattle_NextScene);
    StartTrainerBattle_NextScene();
    // LD_A(0x10);
    // LD_addr_A(wBattleTransitionCounter);
    wram->wBattleTransitionCounter = 0x10;
    // LD_A(1);
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = BGMAPMODE_UPDATE_TILES;
    // RET;
}

static void StartTrainerBattle_SpeckleToBlack_BlackOutRandomTile(void) {
    while(1) {
        uint8_t b;
        do {
        // y_loop:
            // CALL(aRandom);
            b = Random();
            // CP_A(SCREEN_HEIGHT);
            // IF_NC goto y_loop;
        } while(b >= SCREEN_HEIGHT);
        // LD_B_A;

        uint8_t c;
        do {
        // x_loop:
            // CALL(aRandom);
            c = Random();
            // CP_A(SCREEN_WIDTH);
            // IF_NC goto x_loop;
        } while(c >= SCREEN_WIDTH);
        // LD_C_A;

        // hlcoord(0, -1, wTilemap);
        // LD_DE(SCREEN_WIDTH);
        // INC_B;


    // row_loop:
        // ADD_HL_DE;
        // DEC_B;
        // IF_NZ goto row_loop;
        // ADD_HL_BC;
        tile_t* hl = coord(c, b, wram->wTilemap);

    //  If the tile has already been blacked out,
    //  sample a new tile
        // LD_A_hl;
        // CP_A(BATTLETRANSITION_BLACK);
        // IF_Z goto y_loop;
        if(*hl == BATTLETRANSITION_BLACK)
            continue;
        // LD_hl(BATTLETRANSITION_BLACK);
        *hl = BATTLETRANSITION_BLACK;
        // RET;
        return;
    }
}

void StartTrainerBattle_SpeckleToBlack(void){
    // LD_HL(wBattleTransitionCounter);
    // LD_A_hl;
    // AND_A_A;
    // IF_Z goto done;
    if(wram->wBattleTransitionCounter == 0) {
    // done:
        // LD_A(0x1);
        // LDH_addr_A(hBGMapMode);
        hram->hBGMapMode = BGMAPMODE_UPDATE_TILES;
        // CALL(aDelayFrame);
        DelayFrame();
        // CALL(aDelayFrame);
        DelayFrame();
        // CALL(aDelayFrame);
        DelayFrame();
        // XOR_A_A;
        // LDH_addr_A(hBGMapMode);
        hram->hBGMapMode = BGMAPMODE_NONE;
        // LD_A(BATTLETRANSITION_FINISH);
        // LD_addr_A(wJumptableIndex);
        wram->wJumptableIndex = BATTLETRANSITION_FINISH;
        // RET;
        return;
    }
    // DEC_hl;
    wram->wBattleTransitionCounter--;
    // LD_C(0xc);
    uint8_t c = 0xc;

    do {
    // loop:
        // PUSH_BC;
        // CALL(aStartTrainerBattle_SpeckleToBlack_BlackOutRandomTile);
        StartTrainerBattle_SpeckleToBlack_BlackOutRandomTile();
        // POP_BC;
        // DEC_C;
        // IF_NZ goto loop;
    } while(--c != 0);
    DelayFrames(2);
    // RET;

}

#define bigdw(_x) HIGH(_x), LOW(_x)

static const uint8_t PokeBallTransition[] = {
//  16x16 overlay of a Poke Ball
//pusho
//opt b.X   //  . = 0, X = 1
    bigdw(0b0000001111000000),
    bigdw(0b0000111111110000),
    bigdw(0b0011110000111100),
    bigdw(0b0011000000001100),
    bigdw(0b0110000000000110),
    bigdw(0b0110001111000110),
    bigdw(0b1100011001100011),
    bigdw(0b1111110000111111),
    bigdw(0b1111110000111111),
    bigdw(0b1100011001100011),
    bigdw(0b0110001111000110),
    bigdw(0b0110000000000110),
    bigdw(0b0011000000001100),
    bigdw(0b0011110000111100),
    bigdw(0b0000111111110000),
    bigdw(0b0000001111000000),
//popo
};

static void StartTrainerBattle_LoadPokeballGraphics_copypals(const uint16_t* hl) {
    // LD_DE(wBGPals1 + PALETTE_SIZE * PAL_BG_TEXT);
    // CALL(aStartTrainerBattle_LoadPokeBallGraphics_copy);
    CopyBytes(wram->wBGPals1 + PALETTE_SIZE * PAL_BG_TEXT, hl, 1 * PALETTE_SIZE);
    // LD_DE(wBGPals2 + PALETTE_SIZE * PAL_BG_TEXT);
    // CALL(aStartTrainerBattle_LoadPokeBallGraphics_copy);
    CopyBytes(wram->wBGPals2 + PALETTE_SIZE * PAL_BG_TEXT, hl, 1 * PALETTE_SIZE);
    // LD_DE(wOBPals1 + PALETTE_SIZE * PAL_OW_TREE);
    // CALL(aStartTrainerBattle_LoadPokeBallGraphics_copy);
    CopyBytes(wram->wOBPals1 + PALETTE_SIZE * PAL_OW_TREE, hl, 1 * PALETTE_SIZE);
    // LD_DE(wOBPals2 + PALETTE_SIZE * PAL_OW_TREE);
    // CALL(aStartTrainerBattle_LoadPokeBallGraphics_copy);
    CopyBytes(wram->wOBPals2 + PALETTE_SIZE * PAL_OW_TREE, hl, 1 * PALETTE_SIZE);
    // LD_DE(wOBPals1 + PALETTE_SIZE * PAL_OW_ROCK);
    // CALL(aStartTrainerBattle_LoadPokeBallGraphics_copy);
    CopyBytes(wram->wOBPals1 + PALETTE_SIZE * PAL_OW_ROCK, hl, 1 * PALETTE_SIZE);
    // LD_DE(wOBPals2 + PALETTE_SIZE * PAL_OW_ROCK);
    CopyBytes(wram->wOBPals2 + PALETTE_SIZE * PAL_OW_ROCK, hl, 1 * PALETTE_SIZE);

// copy:
    // PUSH_HL;
    // LD_BC(1 * PALETTE_SIZE);
    // CALL(aCopyBytes);
    // POP_HL;
    // RET;
}

void StartTrainerBattle_LoadPokeBallGraphics(void){
    // INCLUDE "gfx/overworld/trainer_battle.pal"
    static const uint16_t pals[] = {
        rgb(31, 18, 29),
        rgb(31, 11, 15),
        rgb(31, 05, 05),
        rgb(07, 07, 07),
    };
    // INCLUDE "gfx/overworld/trainer_battle_dark.pal"
    static const uint16_t darkpals[] = {
        rgb(31, 18, 29),
        rgb(31, 05, 05),
        rgb(31, 05, 05),
        rgb(31, 05, 05),
    };
    // LD_A_addr(wOtherTrainerClass);
    // AND_A_A;
    // JP_Z (mStartTrainerBattle_LoadPokeBallGraphics_nextscene);  // don't need to be here if wild
    if(wram->wOtherTrainerClass == 0) {
    // nextscene:
        // CALL(aStartTrainerBattle_NextScene);
        StartTrainerBattle_NextScene();
        // RET;
        return;
    }

    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = BGMAPMODE_NONE;

    // hlcoord(0, 0, wAttrmap);
    uint8_t* hl = wram->wAttrmap;
    // LD_BC(SCREEN_HEIGHT * SCREEN_WIDTH);
    // INC_B;
    // INC_C;
    // goto enter_loop_midway;

    for(uint16_t bc = 0; bc < SCREEN_HEIGHT * SCREEN_WIDTH; bc++) {
    // pal_loop:
    //  set all pals to 7
        // LD_A_hl;
        // OR_A(PAL_BG_TEXT);
        // LD_hli_A;
        hl[bc] |= PAL_BG_TEXT;

    // enter_loop_midway:
        // DEC_C;
        // IF_NZ goto pal_loop;
        // DEC_B;
        // IF_NZ goto pal_loop;
    }

    // CALL(aStartTrainerBattle_LoadPokeBallGraphics_loadpokeballgfx);
// loadpokeballgfx:
    // LD_A_addr(wOtherTrainerClass);
    // LD_DE(mPokeBallTransition);
    const uint8_t* de = PokeBallTransition;
    // RET;

    // hlcoord(2, 1, wTilemap);
    hl = coord(2, 1, wram->wTilemap);

    // LD_B(SCREEN_WIDTH - 4);
    uint8_t b = SCREEN_WIDTH - 4;

    do {
    // tile_loop:
        // PUSH_HL;
        uint8_t* hl2 = hl;
        // LD_C(2);
        uint8_t c = 2;

        do {
        // row_loop:
            // PUSH_HL;
            uint8_t* hl3 = hl;
            // LD_A_de;
            // INC_DE;
            uint8_t a = *(de++);

            while(a != 0) {
            // col_loop:
            //  Loading is done bit by bit
                // AND_A_A;
                // IF_Z goto done;
                // SLA_A;
                // IF_NC goto no_load;
                if(a & 0x80) {
                    // LD_hl(BATTLETRANSITION_SQUARE);
                    *hl = BATTLETRANSITION_SQUARE;
                }
            // no_load:
                // INC_HL;
                hl++;
                a <<= 1;
                // goto col_loop;
            }

        // done:
            // POP_HL;
            // PUSH_BC;
            // LD_BC((SCREEN_WIDTH - 4) / 2);
            // ADD_HL_BC;
            hl = hl3 + ((SCREEN_WIDTH - 4) / 2);
            // POP_BC;
            // DEC_C;
            // IF_NZ goto row_loop;
        } while(--c != 0);

        // POP_HL;
        // PUSH_BC;
        // LD_BC(SCREEN_WIDTH);
        // ADD_HL_BC;
        // POP_BC;
        hl = hl2 + SCREEN_WIDTH;
        // DEC_B;
        // IF_NZ goto tile_loop;
    } while(--b != 0);

    // LDH_A_addr(hCGB);
    // AND_A_A;
    // IF_NZ goto cgb;
    if(hram->hCGB == 0) {
        // LD_A(1);
        // LDH_addr_A(hBGMapMode);
        hram->hBGMapMode = BGMAPMODE_UPDATE_TILES;
        // CALL(aDelayFrame);
        // CALL(aDelayFrame);
        DelayFrame();
        DelayFrame();
        // goto nextscene;
    }
    else {
    // cgb:
        // LD_HL(mStartTrainerBattle_LoadPokeBallGraphics_pals);
        // LD_A_addr(wTimeOfDayPal);
        // maskbits(NUM_DAYTIMES, 0);
        // CP_A(DARKNESS_F);
        // IF_NZ goto not_dark;
        if((wram->wTimeOfDayPal & (NUM_DAYTIMES - 1)) == DARKNESS_F) {
            // LD_HL(mStartTrainerBattle_LoadPokeBallGraphics_darkpals);
            StartTrainerBattle_LoadPokeballGraphics_copypals(darkpals);
            CopyBytes(wram->wBGPals1 + PALETTE_SIZE * PAL_BG_TEXT, darkpals, 1 * PALETTE_SIZE);
            CopyBytes(wram->wBGPals2 + PALETTE_SIZE * PAL_BG_TEXT, darkpals, 1 * PALETTE_SIZE);
        }
    // not_dark:
        else {
            StartTrainerBattle_LoadPokeballGraphics_copypals(pals);
            CopyBytes(wram->wBGPals1 + PALETTE_SIZE * PAL_BG_TEXT, pals, 1 * PALETTE_SIZE);
            CopyBytes(wram->wBGPals2 + PALETTE_SIZE * PAL_BG_TEXT, pals, 1 * PALETTE_SIZE);
        }
        // LDH_A_addr(rSVBK);
        // PUSH_AF;
        // LD_A(MBANK(awBGPals1));
        // LDH_addr_A(rSVBK);
        // CALL(aStartTrainerBattle_LoadPokeBallGraphics_copypals);
        // PUSH_HL;
        // LD_DE(wBGPals1 + PALETTE_SIZE * PAL_BG_TEXT);
        // LD_BC(1 * PALETTE_SIZE);
        // CALL(aCopyBytes);
        // POP_HL;
        // LD_DE(wBGPals2 + PALETTE_SIZE * PAL_BG_TEXT);
        // LD_BC(1 * PALETTE_SIZE);
        // CALL(aCopyBytes);
        // POP_AF;
        // LDH_addr_A(rSVBK);
        // LD_A(TRUE);
        // LDH_addr_A(hCGBPalUpdate);
        hram->hCGBPalUpdate = TRUE;
        // CALL(aDelayFrame);
        DelayFrame();
        // CALL(aBattleStart_CopyTilemapAtOnce);
        CopyTilemapAtOnce();
    }


// nextscene:
    // CALL(aStartTrainerBattle_NextScene);
    // RET;
    StartTrainerBattle_NextScene();
    // RET;


// loadpokeballgfx:
    // LD_A_addr(wOtherTrainerClass);
    // LD_DE(mPokeBallTransition);
    // RET;
}

void WipeLYOverrides(void){
    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    // LD_A(MBANK(awLYOverrides));
    // LDH_addr_A(rSVBK);

    // LD_HL(wLYOverrides);
    // CALL(aWipeLYOverrides_wipe);
    // LD_HL(wLYOverridesBackup);
    // CALL(aWipeLYOverrides_wipe);

    // POP_AF;
    // LDH_addr_A(rSVBK);
    // RET;


    for(uint8_t c = 0; c < SCREEN_HEIGHT_PX; c++) {
    // wipe:
        // XOR_A_A;
        // LD_C(SCREEN_HEIGHT_PX);

    // loop:
        // LD_hli_A;
        wram->wLYOverrides[c] = 0;
        wram->wLYOverridesBackup[c] = 0;
        // DEC_C;
        // IF_NZ goto loop;
        // RET;
    }
}

static void StartTrainerBattle_ZoomToBlack_Copy(uint8_t* hl, uint8_t c, uint8_t b) {
    // LD_A(BATTLETRANSITION_BLACK);

    do {
    // row:
        // PUSH_BC;
        // PUSH_HL;

        for(uint8_t c2 = 0; c2 < c; ++c2) {
        // col:
            // LD_hli_A;
            // DEC_C;
            // IF_NZ goto col;
            hl[c2] = BATTLETRANSITION_BLACK;
        }
        // POP_HL;
        // LD_BC(SCREEN_WIDTH);
        // ADD_HL_BC;
        hl += SCREEN_WIDTH;
        // POP_BC;
        // DEC_B;
        // IF_NZ goto row;
    } while(--b != 0);
    // RET;
}

void StartTrainerBattle_ZoomToBlack(void){
    struct Zoombox {
        uint8_t w;
        uint8_t h;
        uint8_t* start;
    };
    #define zoombox(w, h, sy, sx) {w, h, coord(sx, sy, wram_ptr(wTilemap))}
    static const struct Zoombox boxes[] = {
// zoombox: MACRO
// ; width, height, start y, start x
//     db \1, \2
//     dwcoord \3, \4
// ENDM
        zoombox(4, 2, 8, 8),
        zoombox(6, 4, 7, 7),
        zoombox(8, 6, 6, 6),
        zoombox(10, 8, 5, 5),
        zoombox(12, 10, 4, 4),
        zoombox(14, 12, 3, 3),
        zoombox(16, 14, 2, 2),
        zoombox(18, 16, 1, 1),
        zoombox(20, 18, 0, 0),
    //db ['-1'];
    };
    // FARCALL(aRespawnPlayerAndOpponent);
    RespawnPlayerAndOpponent_Conv();
    // LD_DE(mStartTrainerBattle_ZoomToBlack_boxes);

    for(uint32_t i = 0; i < lengthof(boxes); ++i) {
    // loop:
        // LD_A_de;
        // CP_A(-1);
        // IF_Z goto done;
        // INC_DE;
        // LD_C_A;
        // LD_A_de;
        // INC_DE;
        // LD_B_A;
        // LD_A_de;
        // INC_DE;
        // LD_L_A;
        // LD_A_de;
        // INC_DE;
        // LD_H_A;
        // XOR_A_A;
        // LDH_addr_A(hBGMapMode);
        hram->hBGMapMode = BGMAPMODE_NONE;
        // CALL(aStartTrainerBattle_ZoomToBlack_Copy);
        StartTrainerBattle_ZoomToBlack_Copy(boxes[i].start, boxes[i].w, boxes[i].h);
        // CALL(aWaitBGMap);
        WaitBGMap();
        // goto loop;
    }

// done:
    // LD_A(BATTLETRANSITION_FINISH);
    // LD_addr_A(wJumptableIndex);
    wram->wJumptableIndex = BATTLETRANSITION_FINISH;
    // RET;
}

void UnusedWaitBGMapOnce(void){
//  //  unreferenced
    LD_A(1);
    LDH_addr_A(hBGMapMode);  // redundant
    CALL(aWaitBGMap);
    XOR_A_A;
    LDH_addr_A(hBGMapMode);
    RET;

}
