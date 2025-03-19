#include "../../constants.h"
#include "magnet_train.h"
#include "../../home/audio.h"
#include "../../home/battle.h" // For PushLYOverrides
#include "../../home/clear_sprites.h"
#include "../../home/copy.h"
#include "../../home/delay.h"
#include "../../home/lcd.h"
#include "../../home/tilemap.h"
#include "../../home/text.h"
#include "../../home/sprite_anims.h"
#include "../../home/time_palettes.h"
#include "../gfx/sprites.h"
#include "../gfx/player_gfx.h"

void MagnetTrain(void){
    // LD_A_addr(wScriptVar);
    // AND_A_A;
    // IF_NZ goto ToGoldenrod;
    int8_t dir;
    int8_t init_pos;
    int8_t hold_pos;
    int8_t final_pos;
    uint8_t player_sprite_init_x;
    if(wram->wScriptVar == 0) {
        // LD_A(1);  // forwards
        dir = 1;
        // LD_BC((8 * TILE_WIDTH << 8) | 12 * TILE_WIDTH);
        init_pos = 12 * TILE_WIDTH;
        hold_pos = 8 * TILE_WIDTH;
        // LD_DE(((11 * TILE_WIDTH) - (11 * TILE_WIDTH + 4) << 8) | -12 * TILE_WIDTH);
        final_pos = -12 * TILE_WIDTH;
        player_sprite_init_x = (11 * TILE_WIDTH) - (11 * TILE_WIDTH + 4);
        // goto continue_;
    }
    else {
    // ToGoldenrod:
        // LD_A(-1);  // backwards
        dir = -1;
        // LD_BC((-8 * TILE_WIDTH << 8) | -12 * TILE_WIDTH);
        init_pos = -12 * TILE_WIDTH;
        hold_pos = -8 * TILE_WIDTH;
        // LD_DE(((11 * TILE_WIDTH) + (11 * TILE_WIDTH + 4) << 8) | 12 * TILE_WIDTH);
        final_pos = 12 * TILE_WIDTH;
        player_sprite_init_x = (11 * TILE_WIDTH) + (11 * TILE_WIDTH + 4);
    }

// continue_:
    // LD_H_A;
    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    // LD_A(BANK(wMagnetTrain));
    // LDH_addr_A(rSVBK);

    // LD_A_H;
    // LD_addr_A(wMagnetTrainDirection);
    wram->wMagnetTrainDirection = dir;
    // LD_A_C;
    // LD_addr_A(wMagnetTrainInitPosition);
    wram->wMagnetTrainInitPosition = init_pos;
    // LD_A_B;
    // LD_addr_A(wMagnetTrainHoldPosition);
    wram->wMagnetTrainHoldPosition = hold_pos;
    // LD_A_E;
    // LD_addr_A(wMagnetTrainFinalPosition);
    wram->wMagnetTrainFinalPosition = final_pos;
    // LD_A_D;
    // LD_addr_A(wMagnetTrainPlayerSpriteInitX);
    wram->wMagnetTrainPlayerSpriteInitX = player_sprite_init_x;

    // LDH_A_addr(hSCX);
    // PUSH_AF;
    uint8_t scx = hram->hSCX;
    // LDH_A_addr(hSCY);
    // PUSH_AF;
    uint8_t scy = hram->hSCX;
    // CALL(aMagnetTrain_LoadGFX_PlayMusic);
    MagnetTrain_LoadGFX_PlayMusic();
    // LD_HL(hVBlank);
    // LD_A_hl;
    uint8_t vblank = hram->hVBlank;
    // PUSH_AF;
    // LD_hl(1);
    hram->hVBlank = 1;

    while(!bit_test(wram->wJumptableIndex, 7)) {
    // loop:
        // LD_A_addr(wJumptableIndex);
        // AND_A_A;
        // IF_Z goto initialize;
        if(wram->wJumptableIndex == 0){
        // initialize:
            // CALL(aMagnetTrain_Jumptable_FirstRunThrough);
            MagnetTrain_Jumptable_FirstRunThrough();
            // goto loop;
            continue;
        }
        // BIT_A(7);
        // IF_NZ goto done;
        // CALLFAR(aPlaySpriteAnimations);
        PlaySpriteAnimations_Conv();
        // CALL(aMagnetTrain_Jumptable);
        MagnetTrain_Jumptable();
        // CALL(aMagnetTrain_UpdateLYOverrides);
        MagnetTrain_UpdateLYOverrides();
        // CALL(aPushLYOverrides);
        PushLYOverrides();
        // CALL(aDelayFrame);
        DelayFrame();
        // goto loop;
    }

// done:
    // POP_AF;
    // LDH_addr_A(hVBlank);
    hram->hVBlank = vblank;
    // CALL(aClearBGPalettes);
    ClearBGPalettes_Conv();
    // XOR_A_A;
    // LDH_addr_A(hLCDCPointer);
    hram->hLCDCPointer = 0x0;
    // LDH_addr_A(hLYOverrideStart);
    hram->hLYOverrideStart = 0x0;
    // LDH_addr_A(hLYOverrideEnd);
    hram->hLYOverrideEnd = 0x0;
    // LDH_addr_A(hSCX);
    hram->hSCX = 0x0;
    // LD_addr_A(wRequested2bppSource);
    // LD_addr_A(wRequested2bppSource + 1);
    // LD_addr_A(wRequested2bppDest);
    // LD_addr_A(wRequested2bppDest + 1);
    // LD_addr_A(wRequested2bppSize);
    // CALL(aClearTilemap);
    ClearTilemap_Conv2();

    // POP_AF;
    // LDH_addr_A(hSCY);
    hram->hSCY = scy;
    // POP_AF;
    // LDH_addr_A(hSCX);
    hram->hSCX = scx;
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = 0x0;

    // POP_AF;
    // LDH_addr_A(rSVBK);
    // RET;
}

static uint8_t* MagnetTrain_UpdateLYOverrides_loadloop(uint8_t* hl, uint8_t c, uint8_t a) {
    do {
        // LD_hli_A;
        *(hl++) = a;
        // DEC_C;
        // IF_NZ goto loadloop;
    } while(--c != 0);
    // RET;
    return hl;
}

void MagnetTrain_UpdateLYOverrides(void){
    // LD_HL(wLYOverridesBackup);
    uint8_t* hl = wram->wLYOverridesBackup;
    // LD_C(6 * TILE_WIDTH - 1);
    // LD_A_addr(wMagnetTrainOffset);
    // ADD_A_A;
    // LDH_addr_A(hSCX);
    hram->hSCX = wram->wMagnetTrainOffset << 1;
    // CALL(aMagnetTrain_UpdateLYOverrides_loadloop);
    hl = MagnetTrain_UpdateLYOverrides_loadloop(hl, 6 * TILE_WIDTH - 1, wram->wMagnetTrainOffset << 1);
    // LD_C(6 * TILE_WIDTH);
    // LD_A_addr(wMagnetTrainPosition);
    // CALL(aMagnetTrain_UpdateLYOverrides_loadloop);
    hl = MagnetTrain_UpdateLYOverrides_loadloop(hl, 6 * TILE_WIDTH, wram->wMagnetTrainPosition);
    // LD_C(6 * TILE_WIDTH + 1);
    // LD_A_addr(wMagnetTrainOffset);
    // ADD_A_A;
    // CALL(aMagnetTrain_UpdateLYOverrides_loadloop);
    hl = MagnetTrain_UpdateLYOverrides_loadloop(hl, 6 * TILE_WIDTH + 1, wram->wMagnetTrainOffset << 1);

    // LD_A_addr(wMagnetTrainDirection);
    // LD_D_A;
    // LD_HL(wMagnetTrainOffset);
    // LD_A_hl;
    // ADD_A_D;
    // ADD_A_D;
    // LD_hl_A;
    wram->wMagnetTrainOffset += 2 * wram->wMagnetTrainDirection;
    // RET;
}

void MagnetTrain_LoadGFX_PlayMusic(void){
    // CALL(aClearBGPalettes);
    ClearBGPalettes_Conv();
    // CALL(aClearSprites);
    ClearSprites();
    // CALL(aDisableLCD);
    DisableLCD();
    // CALLFAR(aClearSpriteAnims);
    ClearSpriteAnims_Conv();
    // CALL(aSetMagnetTrainPals);
    SetMagnetTrainPals();
    // CALL(aDrawMagnetTrain);
    DrawMagnetTrain();
    // LD_A(SCREEN_HEIGHT_PX);
    // LDH_addr_A(hWY);
    hram->hWY = SCREEN_HEIGHT_PX;
    // CALL(aEnableLCD);
    EnableLCD();
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = 0x0;
    // LDH_addr_A(hSCX);
    hram->hSCX = 0x0;
    // LDH_addr_A(hSCY);
    hram->hSCY = 0x0;

// Load the player sprite's standing frames
    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    // LD_A(BANK(wPlayerGender));
    // LDH_addr_A(rSVBK);
    // FARCALL(aGetPlayerIcon);
    const char* icon_path = GetPlayerIcon_Conv2();
    // POP_AF;
    // LDH_addr_A(rSVBK);
    // LD_HL(vTiles0);
    // LD_C(4);
    // CALL(aRequest2bpp);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles0, icon_path, 0, 4);

// Load the player sprite's walking frames
    // LD_HL(12 * LEN_2BPP_TILE);
    // ADD_HL_DE;
    // LD_D_H;
    // LD_E_L;
    // LD_HL(vTiles0 + LEN_2BPP_TILE * 0x04);
    // LD_C(4);
    // CALL(aRequest2bpp);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles0 + LEN_2BPP_TILE * 0x04, icon_path, 12, 4);

    // CALL(aMagnetTrain_InitLYOverrides);
    MagnetTrain_InitLYOverrides();

    // LD_HL(wJumptableIndex);
    // XOR_A_A;
    // LD_hli_A;  // wJumptableIndex
    wram->wJumptableIndex = 0x0;
    // LD_A_addr(wMagnetTrainInitPosition);
    // LD_hli_A;  // wMagnetTrainOffset
    wram->wMagnetTrainOffset = wram->wMagnetTrainInitPosition;
    // LD_hli_A;  // wMagnetTrainPosition
    wram->wMagnetTrainPosition = wram->wMagnetTrainInitPosition;
    // LD_hli_A;  // wMagnetTrainWaitCounter
    wram->wMagnetTrainWaitCounter = wram->wMagnetTrainInitPosition;

    // LD_DE(MUSIC_MAGNET_TRAIN);
    // CALL(aPlayMusic2);
    PlayMusic2(MUSIC_MAGNET_TRAIN);
    // RET;
}

static void DrawMagnetTrain_FillLine(tile_t* hl, const tile_t* de, uint8_t c) {
    do {
        // LD_A_de;
        // INC_DE;
        // LD_hli_A;
        *(hl++) = *(de++);
        // DEC_C;
        // IF_NZ goto FillLine;
    } while(--c != 0);
    // RET;
}


static tile_t* DrawMagnetTrain_FillAlt(tile_t* hl, tile_t e, tile_t d, uint8_t b) {
    do {
        // LD_hl_E;
        // INC_HL;
        *(hl++) = e;
        // LD_hl_D;
        // INC_HL;
        *(hl++) = d;
        // DEC_B;
        // IF_NZ goto FillAlt;
    } while(--b != 0);
    // RET;
    return hl;
}

void DrawMagnetTrain(void){
    // hlbgcoord(0, 0, vBGMap0);
    tile_t* hl = bgcoord(0, 0, vram->vBGMap0);
    // XOR_A_A;
    const tile_t* tiles = GetMagnetTrainBGTiles();

    for(uint32_t i = 0; i < SCREEN_HEIGHT; ++i) {
    // loop:
        // CALL(aGetMagnetTrainBGTiles);
        // LD_B(BG_MAP_WIDTH / 2);
        // CALL(aDrawMagnetTrain_FillAlt);
        hl = DrawMagnetTrain_FillAlt(hl, tiles[i*2+0], tiles[i*2+1], BG_MAP_WIDTH / 2);
        // INC_A;
        // CP_A(SCREEN_HEIGHT);
        // IF_C goto loop;
    }
    FreeMagnetTrainBGTiles();

    asset_s tilemapAsset = LoadAsset(MagnetTrainTilemap);
    const tile_t* tilemap = (const tile_t*)tilemapAsset.ptr;
    // hlbgcoord(0, 6, vBGMap0);
    // LD_DE(mMagnetTrainTilemap);
    // LD_C(SCREEN_WIDTH);
    // CALL(aDrawMagnetTrain_FillLine);
    DrawMagnetTrain_FillLine(bgcoord(0, 6, vram->vBGMap0), tilemap, SCREEN_WIDTH);
    // hlbgcoord(0, 7, vBGMap0);
    // LD_DE(mMagnetTrainTilemap + SCREEN_WIDTH);
    // LD_C(SCREEN_WIDTH);
    // CALL(aDrawMagnetTrain_FillLine);
    DrawMagnetTrain_FillLine(bgcoord(0, 7, vram->vBGMap0), tilemap + SCREEN_WIDTH, SCREEN_WIDTH);
    // hlbgcoord(0, 8, vBGMap0);
    // LD_DE(mMagnetTrainTilemap + (SCREEN_WIDTH * 2));
    // LD_C(SCREEN_WIDTH);
    // CALL(aDrawMagnetTrain_FillLine);
    DrawMagnetTrain_FillLine(bgcoord(0, 8, vram->vBGMap0), tilemap + (2 * SCREEN_WIDTH), SCREEN_WIDTH);
    // hlbgcoord(0, 9, vBGMap0);
    // LD_DE(mMagnetTrainTilemap + (SCREEN_WIDTH * 3));
    // LD_C(SCREEN_WIDTH);
    // CALL(aDrawMagnetTrain_FillLine);
    DrawMagnetTrain_FillLine(bgcoord(0, 9, vram->vBGMap0), tilemap + (3 * SCREEN_WIDTH), SCREEN_WIDTH);
    FreeAsset(tilemapAsset);
    // RET;
}

static asset_s MagnetTrainBGTilesAsset;

const tile_t* GetMagnetTrainBGTiles(void){
    // PUSH_HL;
    // LD_E_A;
    // LD_D(0);
    // LD_HL(mMagnetTrainBGTiles);
    // ADD_HL_DE;
    // ADD_HL_DE;
    // LD_E_hl;
    // INC_HL;
    // LD_D_hl;
    // POP_HL;
    // RET;
    if(MagnetTrainBGTilesAsset.ptr == NULL)
        MagnetTrainBGTilesAsset = LoadAsset(MagnetTrainBGTiles);
    return (const tile_t*)MagnetTrainBGTilesAsset.ptr;
}

void FreeMagnetTrainBGTiles(void) {
    if(MagnetTrainBGTilesAsset.ptr != NULL) {
        FreeAsset(MagnetTrainBGTilesAsset);
        MagnetTrainBGTilesAsset.ptr = NULL;
    }
}

//  2x18 tilemap, repeated in vertical strips for the background.
const char MagnetTrainBGTiles[] = "gfx/overworld/magnet_train_bg.tilemap";

void MagnetTrain_InitLYOverrides(void){
    // LD_HL(wLYOverrides);
    // LD_BC(wLYOverridesEnd - wLYOverrides);
    // LD_A_addr(wMagnetTrainInitPosition);
    // CALL(aByteFill);
    ByteFill(wram->wLYOverrides, sizeof(wram->wLYOverrides), wram->wMagnetTrainInitPosition);
    // LD_HL(wLYOverridesBackup);
    // LD_BC(wLYOverridesBackupEnd - wLYOverridesBackup);
    // LD_A_addr(wMagnetTrainInitPosition);
    // CALL(aByteFill);
    ByteFill(wram->wLYOverridesBackup, sizeof(wram->wLYOverridesBackup), wram->wMagnetTrainInitPosition);
    // LD_A(LOW(rSCX));
    // LDH_addr_A(hLCDCPointer);
    hram->hLCDCPointer = LOW(rSCX);
    // RET;

}

void SetMagnetTrainPals(void){
    // LD_A(1);
    // LDH_addr_A(rVBK);

// bushes
    // hlbgcoord(0, 0, vBGMap0);
    // LD_BC(4 * BG_MAP_WIDTH);
    // LD_A(PAL_BG_GREEN);
    // CALL(aByteFill);
    ByteFill(bgcoord(0, 0, vram->vBGMap2), 4 * BG_MAP_WIDTH, PAL_BG_GREEN);

// train
    // hlbgcoord(0, 4, vBGMap0);
    // LD_BC(10 * BG_MAP_WIDTH);
    // XOR_A_A;  // PAL_BG_GRAY
    // CALL(aByteFill);
    ByteFill(bgcoord(0, 4, vram->vBGMap2), 10 * BG_MAP_WIDTH, PAL_BG_GRAY);

// more bushes
    // hlbgcoord(0, 14, vBGMap0);
    // LD_BC(4 * BG_MAP_WIDTH);
    // LD_A(PAL_BG_GREEN);
    // CALL(aByteFill);
    ByteFill(bgcoord(0, 14, vram->vBGMap2), 4 * BG_MAP_WIDTH, PAL_BG_GREEN);

// train window
    // hlbgcoord(7, 8, vBGMap0);
    // LD_BC(6);
    // LD_A(PAL_BG_YELLOW);
    // CALL(aByteFill);
    ByteFill(bgcoord(7, 8, vram->vBGMap2), 6, PAL_BG_YELLOW);

    // LD_A(0);
    // LDH_addr_A(rVBK);
    // RET;

}

static void MagnetTrain_Jumptable_Next(void){
    // LD_HL(wJumptableIndex);
    // INC_hl;
    wram->wJumptableIndex++;
    // RET;
}

void MagnetTrain_Jumptable(void){
    //jumptable ['.Jumptable', 'wJumptableIndex']

// Jumptable:
    switch(wram->wJumptableIndex) {
    //dw ['.InitPlayerSpriteAnim'];
    case 0: {
    // InitPlayerSpriteAnim:
        // LD_D((8 + 2) * TILE_WIDTH + 5);
        // LD_A_addr(wMagnetTrainPlayerSpriteInitX);
        // LD_E_A;
        // LD_B(SPRITE_ANIM_INDEX_MAGNET_TRAIN_RED);
        // LDH_A_addr(rSVBK);
        // PUSH_AF;
        // LD_A(BANK(wPlayerGender));
        // LDH_addr_A(rSVBK);
        // LD_A_addr(wPlayerGender);
        // BIT_A(PLAYERGENDER_FEMALE_F);
        // IF_Z goto got_gender;
        // LD_B(SPRITE_ANIM_INDEX_MAGNET_TRAIN_BLUE);

    // got_gender:
        const uint8_t b = (bit_test(wram->wPlayerGender, PLAYERGENDER_FEMALE_F))
            ? SPRITE_ANIM_INDEX_MAGNET_TRAIN_BLUE
            : SPRITE_ANIM_INDEX_MAGNET_TRAIN_RED;
        // POP_AF;
        // LDH_addr_A(rSVBK);
        // LD_A_B;
        // CALL(aInitSpriteAnimStruct);
        struct SpriteAnim* bc = InitSpriteAnimStruct_Conv(b, wram->wMagnetTrainPlayerSpriteInitX | (((8 + 2) * TILE_WIDTH + 5) << 8));
        // LD_HL(SPRITEANIMSTRUCT_TILE_ID);
        // ADD_HL_BC;
        // LD_hl(0);
        bc->tileID = 0;
        // CALL(aMagnetTrain_Jumptable_Next);
        MagnetTrain_Jumptable_Next();
        // LD_A(128);
        // LD_addr_A(wMagnetTrainWaitCounter);
        wram->wMagnetTrainWaitCounter = 128;
        // RET;
    } return;
    //dw ['.WaitScene'];
    //dw ['.MoveTrain1'];
    case 2: {
    // MoveTrain1:
        // LD_HL(wMagnetTrainHoldPosition);
        // LD_A_addr(wMagnetTrainPosition);
        // CP_A_hl;
        // IF_Z goto PrepareToHoldTrain;
        if(wram->wMagnetTrainPosition == wram->wMagnetTrainHoldPosition) {
        // PrepareToHoldTrain:
            // CALL(aMagnetTrain_Jumptable_Next);
            MagnetTrain_Jumptable_Next();
            // LD_A(128);
            // LD_addr_A(wMagnetTrainWaitCounter);
            wram->wMagnetTrainWaitCounter = 128;
            // RET;
            return;
        }
        // LD_E_A;
        // LD_A_addr(wMagnetTrainDirection);
        // XOR_A(0xff);
        // INC_A;
        // ADD_A_E;
        // LD_addr_A(wMagnetTrainPosition);
        wram->wMagnetTrainPosition = wram->wMagnetTrainPosition - wram->wMagnetTrainDirection;
        // LD_HL(wGlobalAnimXOffset);
        // LD_A_addr(wMagnetTrainDirection);
        // ADD_A_hl;
        // LD_hl_A;
        wram->wGlobalAnimXOffset += wram->wMagnetTrainDirection;
        // RET;
    } return;
    //dw ['.WaitScene'];
    //dw ['.MoveTrain2'];
    case 4: {
    // MoveTrain2:
        // LD_HL(wMagnetTrainFinalPosition);
        // LD_A_addr(wMagnetTrainPosition);
        // CP_A_hl;
        // IF_Z goto PrepareToFinishAnim;
        if(wram->wMagnetTrainPosition == wram->wMagnetTrainFinalPosition) {
        // PrepareToFinishAnim:
            // CALL(aMagnetTrain_Jumptable_Next);
            MagnetTrain_Jumptable_Next();
            // RET;
            return;
        }
        // LD_E_A;
        // LD_A_addr(wMagnetTrainDirection);
        // XOR_A(0xff);
        // INC_A;
        // LD_D_A;
        // LD_A_E;
        // ADD_A_D;
        // ADD_A_D;
        // LD_addr_A(wMagnetTrainPosition);
        wram->wMagnetTrainPosition -= wram->wMagnetTrainDirection * 2;
        // LD_HL(wGlobalAnimXOffset);
        // LD_A_addr(wMagnetTrainDirection);
        // LD_D_A;
        // LD_A_hl;
        // ADD_A_D;
        // ADD_A_D;
        // LD_hl_A;
        wram->wGlobalAnimXOffset += wram->wMagnetTrainDirection * 2;
        // RET;

        // RET; // Stubbed code?
    } return;
    //dw ['.WaitScene'];
    case 1:
    case 3:
    case 5: {
    // WaitScene:
        // LD_HL(wMagnetTrainWaitCounter);
        // LD_A_hl;
        // AND_A_A;
        // IF_Z goto DoneWaiting;
        if(wram->wMagnetTrainWaitCounter == 0) {
        // DoneWaiting:
            // CALL(aMagnetTrain_Jumptable_Next);
            MagnetTrain_Jumptable_Next();
            // RET;
            return;
        }
        // DEC_hl;
        wram->wMagnetTrainWaitCounter--;
        // RET;
    } return;
    //dw ['.TrainArrived'];
    case 6: {
    // TrainArrived:
        // LD_A(0x80);
        // LD_addr_A(wJumptableIndex);
        wram->wJumptableIndex = 0x80;
        // LD_DE(SFX_TRAIN_ARRIVED);
        // CALL(aPlaySFX);
        PlaySFX(SFX_TRAIN_ARRIVED);
        // RET;
    } return;
    }
}

void MagnetTrain_Jumptable_FirstRunThrough(void){
    // FARCALL(aPlaySpriteAnimations);
    PlaySpriteAnimations_Conv();
    // CALL(aMagnetTrain_Jumptable);
    MagnetTrain_Jumptable();
    // CALL(aMagnetTrain_UpdateLYOverrides);
    MagnetTrain_UpdateLYOverrides();
    // CALL(aPushLYOverrides);
    PushLYOverrides();
    // CALL(aDelayFrame);
    DelayFrame();

    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    // LD_A(BANK(wEnvironment));
    // LDH_addr_A(rSVBK);
    // LD_A_addr(wTimeOfDayPal);
    // PUSH_AF;
    uint8_t timeOfDayPal = wram->wTimeOfDayPal;
    // LD_A_addr(wEnvironment);
    // PUSH_AF;
    uint8_t environment = wram->wEnvironment;

    // LD_A_addr(wTimeOfDay);
    // maskbits(NUM_DAYTIMES, 0);
    // LD_addr_A(wTimeOfDayPal);
    wram->wTimeOfDayPal = wram->wTimeOfDay & (NUM_DAYTIMES - 1);
    // LD_A(TOWN);
    // LD_addr_A(wEnvironment);
    wram->wEnvironment = TOWN;
    // LD_B(SCGB_MAPPALS);
    // CALL(aGetSGBLayout);
    GetSGBLayout_Conv(SCGB_MAPPALS);
    // CALL(aUpdateTimePals);
    UpdateTimePals();

    // LDH_A_addr(rBGP);
    // LD_addr_A(wBGP);
    wram->wBGP = gb_read(rBGP);
    // LDH_A_addr(rOBP0);
    // LD_addr_A(wOBP0);
    wram->wOBP0 = gb_read(rOBP0);
    // LDH_A_addr(rOBP1);
    // LD_addr_A(wOBP1);
    wram->wOBP1 = gb_read(rOBP1);

    // POP_AF;
    // LD_addr_A(wEnvironment);
    wram->wEnvironment = environment;
    // POP_AF;
    // LD_addr_A(wTimeOfDayPal);
    wram->wTimeOfDayPal = timeOfDayPal;
    // POP_AF;
    // LDH_addr_A(rSVBK);
    // RET;

}

//  20x4 tilemap
const char MagnetTrainTilemap[] = "gfx/overworld/magnet_train_fg.tilemap";
