#include "../../constants.h"
#include "field_moves.h"
#include "../../home/delay.h"
#include "../../home/copy.h"
#include "../../home/audio.h"
#include "../../home/sprite_anims.h"
#include "../../home/tilemap.h"
#include "../../home/map.h"
#include "../../home/gfx.h"
#include "../tilesets/timeofday_pals.h"
#include "../gfx/crystal_layouts.h"
#include "../gfx/sprites.h"
#include "../gfx/mon_icons.h"
#include "../../gfx/font.h"

#define FIELDMOVE_GRASS (0x80)
#define FIELDMOVE_TREE (0x84)
#define FIELDMOVE_FLY (0x84)

static const char CutTreeGFX[] = "gfx/overworld/cut_tree.png";
static const char CutGrassGFX[] = "gfx/overworld/cut_grass.png";

void PlayWhirlpoolSound(void){
    // CALL(aWaitSFX);
    WaitSFX();
    // LD_DE(SFX_SURF);
    // CALL(aPlaySFX);
    PlaySFX(SFX_SURF);
    // CALL(aWaitSFX);
    WaitSFX();
    // RET;
}

void BlindingFlash(void){
    // FARCALL(aFadeOutPalettes);
    FadeOutPalettes();
    // LD_HL(wStatusFlags);
    // SET_hl(STATUSFLAGS_FLASH_F);
    bit_set(wram->wStatusFlags, STATUSFLAGS_FLASH_F);
    // FARCALL(aReplaceTimeOfDayPals);
    ReplaceTimeOfDayPals_Conv();
    // FARCALL(aUpdateTimeOfDayPal);
    UpdateTimeOfDayPal();
    // LD_B(SCGB_MAPPALS);
    // CALL(aGetSGBLayout);
    GetSGBLayout(SCGB_MAPPALS);
    // FARCALL(aLoadOW_BGPal7);
    LoadOW_BGPal7();
    // FARCALL(aFadeInPalettes);
    FadeInPalettes();
    // RET;
}

const char HeadbuttTreeGFX[] = "gfx/overworld/headbutt_tree.png";

void ShakeHeadbuttTree(void){
    // FARCALL(aClearSpriteAnims);
    ClearSpriteAnims();
    // LD_DE(mCutGrassGFX);
    // LD_HL(vTiles0 + LEN_2BPP_TILE * FIELDMOVE_GRASS);
    // LD_BC((BANK(aCutGrassGFX) << 8) | 4);
    // CALL(aRequest2bpp);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles0 + LEN_2BPP_TILE * FIELDMOVE_GRASS, CutTreeGFX, 0, 4);
    // LD_DE(mHeadbuttTreeGFX);
    // LD_HL(vTiles0 + LEN_2BPP_TILE * FIELDMOVE_TREE);
    // LD_BC((BANK(aHeadbuttTreeGFX) << 8) | 8);
    // CALL(aRequest2bpp);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles0 + LEN_2BPP_TILE * FIELDMOVE_TREE, HeadbuttTreeGFX, 0, 8);
    // CALL(aCut_Headbutt_GetPixelFacing);
    // LD_A(SPRITE_ANIM_INDEX_HEADBUTT);
    // CALL(aInitSpriteAnimStruct);
    struct SpriteAnim* bc = InitSpriteAnimStruct(SPRITE_ANIM_INDEX_HEADBUTT, Cut_Headbutt_GetPixelFacing_Conv());
    // LD_HL(SPRITEANIMSTRUCT_TILE_ID);
    // ADD_HL_BC;
    // LD_hl(FIELDMOVE_TREE);
    bc->tileID = FIELDMOVE_TREE;
    // LD_A(36 * SPRITEOAMSTRUCT_LENGTH);
    // LD_addr_A(wCurSpriteOAMAddr);
    wram->wCurSpriteOAMAddr = 36 * SPRITEOAMSTRUCT_LENGTH;
    // FARCALL(aDoNextFrameForAllSprites);
    DoNextFrameForAllSprites();
    // CALL(aHideHeadbuttTree);
    HideHeadbuttTree();
    // LD_A(32);
    // LD_addr_A(wFrameCounter);
    wram->wFrameCounter = 32;
    // CALL(aWaitSFX);
    WaitSFX();
    // LD_DE(SFX_SANDSTORM);
    // CALL(aPlaySFX);
    PlaySFX(SFX_SANDSTORM);

    while(wram->wFrameCounter != 0) {
    // loop:
        // LD_HL(wFrameCounter);
        // LD_A_hl;
        // AND_A_A;
        // IF_Z goto done;
        // DEC_hl;
        --wram->wFrameCounter;
        // LD_A(36 * SPRITEOAMSTRUCT_LENGTH);
        // LD_addr_A(wCurSpriteOAMAddr);
        wram->wCurSpriteOAMAddr = 36 * SPRITEOAMSTRUCT_LENGTH;
        // FARCALL(aDoNextFrameForAllSprites);
        DoNextFrameForAllSprites();
        // CALL(aDelayFrame);
        DelayFrame();
        // goto loop;
    }

// done:
    // CALL(aOverworldTextModeSwitch);
    OverworldTextModeSwitch();
    // CALL(aWaitBGMap);
    WaitBGMap();
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = BGMAPMODE_NONE;
    // FARCALL(aClearSpriteAnims);
    ClearSpriteAnims();
    // LD_HL(wVirtualOAMSprite36);
    // LD_BC(wVirtualOAMEnd - wVirtualOAMSprite36);
    // XOR_A_A;
    // CALL(aByteFill);
    ByteFill(wram->wVirtualOAMSprite + 36, wVirtualOAMEnd - wVirtualOAMSprite36, 0);
    // LD_DE(mFont);
    // LD_HL(vTiles1);
    // LD_BC((BANK(aFont) << 8) | 12);
    // CALL(aGet1bpp);
    LoadPNG1bppAssetSectionToVRAM(vram->vTiles1, Font, 0, 12);
    // CALL(aUpdatePlayerSprite);
    UpdatePlayerSprite();
    // RET;
}

const uint16_t TreeRelativeLocationTable[] = {
    dwcoordidx(8, 8 + 2),  // RIGHT
    dwcoordidx(8, 8 - 2),  // LEFT
    dwcoordidx(8 - 2, 8),  // DOWN
    dwcoordidx(8 + 2, 8),  // UP
};

void HideHeadbuttTree(void){
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = BGMAPMODE_NONE;
    // LD_A_addr(wPlayerDirection);
    // AND_A(0b00001100);
    // SRL_A;
    // LD_E_A;
    // LD_D(0);
    // LD_HL(mTreeRelativeLocationTable);
    // ADD_HL_DE;
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    tile_t* loc = wram->wTilemap + TreeRelativeLocationTable[(wram->wPlayerStruct.facing & 0b00001100) >> 2];

    enum { grass_block = 0x05 };
    // LD_A(0x05);  // grass block
    // LD_hli_A;
    // LD_hld_A;
    loc[0] = grass_block;
    loc[1] = grass_block;
    // LD_BC(SCREEN_WIDTH);
    // ADD_HL_BC;
    // LD_hli_A;
    // LD_hld_A;
    loc[SCREEN_WIDTH]   = grass_block;
    loc[SCREEN_WIDTH+1] = grass_block;
    // CALL(aWaitBGMap);
    WaitBGMap();
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = BGMAPMODE_NONE;
    // RET;
}

void OWCutAnimation(void){
// Animation index in e
// 0: Split tree in half
// 1: Mow the lawn
    LD_A_E;
    AND_A(1);
    LD_addr_A(wJumptableIndex);
    CALL(aOWCutAnimation_LoadCutGFX);
    CALL(aWaitSFX);
    LD_DE(SFX_PLACE_PUZZLE_PIECE_DOWN);
    CALL(aPlaySFX);

loop:
    LD_A_addr(wJumptableIndex);
    BIT_A(7);
    IF_NZ goto finish;
    LD_A(36 * SPRITEOAMSTRUCT_LENGTH);
    LD_addr_A(wCurSpriteOAMAddr);
    CALLFAR(aDoNextFrameForAllSprites);
    CALL(aOWCutJumptable);
    CALL(aDelayFrame);
    goto loop;


finish:
    RET;


LoadCutGFX:
    CALLFAR(aClearSpriteAnims);  // pointless to farcall
    LD_DE(mCutGrassGFX);
    LD_HL(vTiles0 + LEN_2BPP_TILE * FIELDMOVE_GRASS);
    LD_BC((BANK(aCutGrassGFX) << 8) | 4);
    CALL(aRequest2bpp);
    LD_DE(mCutTreeGFX);
    LD_HL(vTiles0 + LEN_2BPP_TILE * FIELDMOVE_TREE);
    LD_BC((BANK(aCutTreeGFX) << 8) | 4);
    CALL(aRequest2bpp);
    RET;

}

static void OWCutAnimation_LoadCutGFX(void) {
    // CALLFAR(aClearSpriteAnims);  // pointless to farcall
    ClearSpriteAnims();
    // LD_DE(mCutGrassGFX);
    // LD_HL(vTiles0 + LEN_2BPP_TILE * FIELDMOVE_GRASS);
    // LD_BC((BANK(aCutGrassGFX) << 8) | 4);
    // CALL(aRequest2bpp);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles0 + LEN_2BPP_TILE * FIELDMOVE_GRASS, CutGrassGFX, 0, 4);
    // LD_DE(mCutTreeGFX);
    // LD_HL(vTiles0 + LEN_2BPP_TILE * FIELDMOVE_TREE);
    // LD_BC((BANK(aCutTreeGFX) << 8) | 4);
    // CALL(aRequest2bpp);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles0 + LEN_2BPP_TILE * FIELDMOVE_TREE, CutTreeGFX, 0, 4);
    // RET;
}

// Animation index in e
// 0: Split tree in half
// 1: Mow the lawn
void OWCutAnimation_Conv(uint8_t e){
    // LD_A_E;
    // AND_A(1);
    // LD_addr_A(wJumptableIndex);
    wram->wJumptableIndex = e & 1;
    // CALL(aOWCutAnimation_LoadCutGFX);
    OWCutAnimation_LoadCutGFX();
    // CALL(aWaitSFX);
    WaitSFX();
    // LD_DE(SFX_PLACE_PUZZLE_PIECE_DOWN);
    // CALL(aPlaySFX);
    PlaySFX(SFX_PLACE_PUZZLE_PIECE_DOWN);

    while(!bit_test(wram->wJumptableIndex, 7)) {
    // loop:
        // LD_A_addr(wJumptableIndex);
        // BIT_A(7);
        // IF_NZ goto finish;
        // LD_A(36 * SPRITEOAMSTRUCT_LENGTH);
        // LD_addr_A(wCurSpriteOAMAddr);
        wram->wCurSpriteOAMAddr = 36 * SPRITEOAMSTRUCT_LENGTH;
        // CALLFAR(aDoNextFrameForAllSprites);
        DoNextFrameForAllSprites();
        // CALL(aOWCutJumptable);
        OWCutJumptable();
        // CALL(aDelayFrame);
        DelayFrame();
        // goto loop;
    }


// finish:
    // RET;
}

void OWCutJumptable(void){
    //jumptable ['.dw', 'wJumptableIndex']

    switch(wram->wJumptableIndex) {
    // dw:
        case 0: return Cut_SpawnAnimateTree();
        case 1: return Cut_SpawnAnimateLeaves();
        case 2: return Cut_StartWaiting();
        case 3: return Cut_WaitAnimSFX();
    }
}

void Cut_SpawnAnimateTree(void){
    // CALL(aCut_Headbutt_GetPixelFacing);
    uint16_t pixel = Cut_Headbutt_GetPixelFacing_Conv();
    // LD_A(SPRITE_ANIM_INDEX_CUT_TREE);  // cut tree
    // CALL(aInitSpriteAnimStruct);
    struct SpriteAnim* bc = InitSpriteAnimStruct(SPRITE_ANIM_INDEX_CUT_TREE, pixel);
    // LD_HL(SPRITEANIMSTRUCT_TILE_ID);
    // ADD_HL_BC;
    // LD_hl(FIELDMOVE_TREE);
    bc->tileID = FIELDMOVE_TREE;
    // LD_A(32);
    // LD_addr_A(wFrameCounter);
    wram->wFrameCounter = 32;
//  Cut_StartWaiting
    // LD_HL(wJumptableIndex);
    // INC_hl;
    // INC_hl;
    wram->wJumptableIndex += 2;
    // RET;
}

void Cut_SpawnAnimateLeaves(void){
    // CALL(aCut_GetLeafSpawnCoords);
    uint16_t pixel = Cut_GetLeafSpawnCoords_Conv();
    // XOR_A_A;
    // CALL(aCut_SpawnLeaf);
    Cut_SpawnLeaf_Conv(pixel, 0);
    // LD_A(0x10);
    // CALL(aCut_SpawnLeaf);
    Cut_SpawnLeaf_Conv(pixel, 0x10);
    // LD_A(0x20);
    // CALL(aCut_SpawnLeaf);
    Cut_SpawnLeaf_Conv(pixel, 0x20);
    // LD_A(0x30);
    // CALL(aCut_SpawnLeaf);
    Cut_SpawnLeaf_Conv(pixel, 0x30);
    // LD_A(32);  // frames
    // LD_addr_A(wFrameCounter);
    wram->wFrameCounter = 32;
//  Cut_StartWaiting
    // LD_HL(wJumptableIndex);
    // INC_hl;
    wram->wJumptableIndex++;
    // RET;
}

void Cut_StartWaiting(void){
    // LD_A(1);
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = BGMAPMODE_UPDATE_TILES;
//  Cut_WaitAnimSFX
    // LD_HL(wJumptableIndex);
    // INC_hl;
    wram->wJumptableIndex++;

    return Cut_WaitAnimSFX();
}

void Cut_WaitAnimSFX(void){
    // LD_HL(wFrameCounter);
    // LD_A_hl;
    // AND_A_A;
    // IF_Z goto finished;
    // DEC_hl;
    // RET;
    if(wram->wFrameCounter != 0) {
        --wram->wFrameCounter;
        return;
    }

// finished:
    // LD_HL(wJumptableIndex);
    // SET_hl(7);
    bit_set(wram->wJumptableIndex, 7);
    // RET;
}

void Cut_SpawnLeaf(void){
    PUSH_DE;
    PUSH_AF;
    LD_A(SPRITE_ANIM_INDEX_LEAF);  // leaf
    CALL(aInitSpriteAnimStruct);
    LD_HL(SPRITEANIMSTRUCT_TILE_ID);
    ADD_HL_BC;
    LD_hl(FIELDMOVE_GRASS);
    LD_HL(SPRITEANIMSTRUCT_VAR3);
    ADD_HL_BC;
    LD_hl(0x4);
    POP_AF;
    LD_HL(SPRITEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_hl_A;
    POP_DE;
    RET;

}

struct SpriteAnim* Cut_SpawnLeaf_Conv(uint16_t de, uint8_t a){
    // PUSH_DE;
    // PUSH_AF;
    // LD_A(SPRITE_ANIM_INDEX_LEAF);  // leaf
    // CALL(aInitSpriteAnimStruct);
    struct SpriteAnim* bc = InitSpriteAnimStruct(SPRITE_ANIM_INDEX_LEAF, de);
    // LD_HL(SPRITEANIMSTRUCT_TILE_ID);
    // ADD_HL_BC;
    // LD_hl(FIELDMOVE_GRASS);
    bc->tileID = FIELDMOVE_GRASS;
    // LD_HL(SPRITEANIMSTRUCT_VAR3);
    // ADD_HL_BC;
    // LD_hl(0x4);
    bc->var3 = 0x4;
    // POP_AF;
    // LD_HL(SPRITEANIMSTRUCT_VAR1);
    // ADD_HL_BC;
    // LD_hl_A;
    bc->var1 = a;
    // POP_DE;
    // RET;
    return bc;
}

void Cut_GetLeafSpawnCoords(void){
    LD_DE(0);
    LD_A_addr(wMetatileStandingX);
    BIT_A(0);
    IF_Z goto left_side;
    SET_E(0);

left_side:
    LD_A_addr(wMetatileStandingY);
    BIT_A(0);
    IF_Z goto top_side;
    SET_E(1);

top_side:
    LD_A_addr(wPlayerDirection);
    AND_A(0b00001100);
    ADD_A_E;
    LD_E_A;
    LD_HL(mCut_GetLeafSpawnCoords_Coords);
    ADD_HL_DE;
    ADD_HL_DE;
    LD_E_hl;
    INC_HL;
    LD_D_hl;
    RET;


Coords:
    //dbpixel ['11', '12']  // facing down,  top left
    //dbpixel ['9', '12']  // facing down,  top right
    //dbpixel ['11', '14']  // facing down,  bottom left
    //dbpixel ['9', '14']  // facing down,  bottom right

    //dbpixel ['11', '8']  // facing up,    top left
    //dbpixel ['9', '8']  // facing up,    top right
    //dbpixel ['11', '10']  // facing up,    bottom left
    //dbpixel ['9', '10']  // facing up,    bottom right

    //dbpixel ['7', '12']  // facing left,  top left
    //dbpixel ['9', '12']  // facing left,  top right
    //dbpixel ['7', '10']  // facing left,  bottom left
    //dbpixel ['9', '10']  // facing left,  bottom right

    //dbpixel ['11', '12']  // facing right, top left
    //dbpixel ['13', '12']  // facing right, top right
    //dbpixel ['11', '10']  // facing right, bottom left
    //dbpixel ['13', '10']  // facing right, bottom right

    return Cut_Headbutt_GetPixelFacing();
}

uint16_t Cut_GetLeafSpawnCoords_Conv(void){
    static const uint8_t Coords[] = {
        dbpixel2(11, 12),  // facing down,  top left
        dbpixel2(9, 12),  // facing down,  top right
        dbpixel2(11, 14),  // facing down,  bottom left
        dbpixel2(9, 14),  // facing down,  bottom right

        dbpixel2(11, 8),  // facing up,    top left
        dbpixel2(9, 8),  // facing up,    top right
        dbpixel2(11, 10),  // facing up,    bottom left
        dbpixel2(9, 10),  // facing up,    bottom right

        dbpixel2(7, 12),  // facing left,  top left
        dbpixel2(9, 12),  // facing left,  top right
        dbpixel2(7, 10),  // facing left,  bottom left
        dbpixel2(9, 10),  // facing left,  bottom right

        dbpixel2(11, 12),  // facing right, top left
        dbpixel2(13, 12),  // facing right, top right
        dbpixel2(11, 10),  // facing right, bottom left
        dbpixel2(13, 10),  // facing right, bottom right
    };
    // LD_DE(0);
    // LD_A_addr(wMetatileStandingX);
    // BIT_A(0);
    // IF_Z goto left_side;
    // SET_E(0);
    uint8_t e = bit_test(wram->wMetatileStandingX, 0)? 1: 0;

// left_side:
    // LD_A_addr(wMetatileStandingY);
    // BIT_A(0);
    // IF_Z goto top_side;
    // SET_E(1);
    e |= bit_test(wram->wMetatileStandingY, 0)? 2: 0;

// top_side:
    // LD_A_addr(wPlayerDirection);
    // AND_A(0b00001100);
    // ADD_A_E;
    // LD_E_A;
    e += wram->wPlayerStruct.facing & 0b00001100;
    // LD_HL(mCut_GetLeafSpawnCoords_Coords);
    // ADD_HL_DE;
    // ADD_HL_DE;
    // LD_E_hl;
    // INC_HL;
    // LD_D_hl;
    // RET;

    return Coords[e * 2] | (Coords[(e * 2) + 1] << 8);
}

void Cut_Headbutt_GetPixelFacing(void){
    LD_A_addr(wPlayerDirection);
    AND_A(0b00001100);
    SRL_A;
    LD_E_A;
    LD_D(0);
    LD_HL(mCut_Headbutt_GetPixelFacing_Coords);
    ADD_HL_DE;
    LD_E_hl;
    INC_HL;
    LD_D_hl;
    RET;


// Coords:
    //dbpixel 10, 13
    //dbpixel 10, 9
    //dbpixel 8, 11
    //dbpixel 12, 11
}

uint16_t Cut_Headbutt_GetPixelFacing_Conv(void){
    static const uint8_t Coords[] = {
        dbpixel2(10, 13),
        dbpixel2(10, 9),
        dbpixel2(8, 11),
        dbpixel2(12, 11),
    };

    // LD_A_addr(wPlayerDirection);
    // AND_A(0b00001100);
    // SRL_A;
    uint8_t e = (wram->wPlayerStruct.facing & 0b00001100) >> 1;
    // LD_E_A;
    // LD_D(0);
    // LD_HL(mCut_Headbutt_GetPixelFacing_Coords);
    // ADD_HL_DE;
    // LD_E_hl;
    // INC_HL;
    // LD_D_hl;
    // RET;

    return Coords[e] | (Coords[e+1] << 8);
}

void FlyFromAnim(void){
    // CALL(aDelayFrame);
    DelayFrame();
    // LD_A_addr(wVramState);
    // PUSH_AF;
    uint8_t vramState = wram->wVramState;
    // XOR_A_A;
    // LD_addr_A(wVramState);
    wram->wVramState = 0;
    // CALL(aFlyFunction_InitGFX);
    FlyFunction_InitGFX();
    // depixel4(10, 10, 4, 0);
    // LD_A(SPRITE_ANIM_INDEX_RED_WALK);
    // CALL(aInitSpriteAnimStruct);
    struct SpriteAnim* bc = InitSpriteAnimStruct(SPRITE_ANIM_INDEX_RED_WALK, pixel4(10, 10, 4, 0));
    // LD_HL(SPRITEANIMSTRUCT_TILE_ID);
    // ADD_HL_BC;
    // LD_hl(FIELDMOVE_FLY);
    bc->tileID = FIELDMOVE_FLY;
    // LD_HL(SPRITEANIMSTRUCT_ANIM_SEQ_ID);
    // ADD_HL_BC;
    // LD_hl(SPRITE_ANIM_SEQ_FLY_FROM);
    bc->animSeqID = SPRITE_ANIM_SEQ_FLY_FROM;
    // LD_A(128);
    // LD_addr_A(wFrameCounter);
    wram->wFrameCounter = 128;

    while(!bit_test(wram->wJumptableIndex, 7)) {
    // loop:
        // LD_A_addr(wJumptableIndex);
        // BIT_A(7);
        // IF_NZ goto exit;
        // LD_A(0 * SPRITEOAMSTRUCT_LENGTH);
        // LD_addr_A(wCurSpriteOAMAddr);
        wram->wCurSpriteOAMAddr = 0 * SPRITEOAMSTRUCT_LENGTH;
        // CALLFAR(aDoNextFrameForAllSprites);
        DoNextFrameForAllSprites();
        // CALL(aFlyFunction_FrameTimer);
        FlyFunction_FrameTimer();
        // CALL(aDelayFrame);
        DelayFrame();
        // goto loop;
    }

// exit:
    // POP_AF;
    // LD_addr_A(wVramState);
    wram->wVramState = vramState;
    // RET;
}

static void FlyToAnim_RestorePlayerSprite_DespawnLeaves(void) {
    // LD_HL(wVirtualOAMSprite00TileID);
    struct SpriteOAM* hl = wram->wVirtualOAMSprite;
    // XOR_A_A;
    uint8_t a = 0;
    // LD_C(4);
    uint32_t c;

    for(c = 0; c < 4; ++c) {
    // OAMloop:
        // LD_hli_A;  // tile id
        hl[c].tileID = a++;
        // for(int rept = 0; rept < SPRITEOAMSTRUCT_LENGTH - 1; rept++){
        // INC_HL;
        // }
        // INC_A;
        // DEC_C;
        // IF_NZ goto OAMloop;
    }
    // LD_HL(wVirtualOAMSprite04);
    // LD_BC(wVirtualOAMEnd - wVirtualOAMSprite04);
    // XOR_A_A;
    // CALL(aByteFill);
    ByteFill(wram->wVirtualOAMSprite + 4, sizeof(wram->wVirtualOAMSprite) - (4 * sizeof(wram->wVirtualOAMSprite[0])), 0);
    // RET;
}

void FlyToAnim(void){
    // CALL(aDelayFrame);
    DelayFrame();
    // LD_A_addr(wVramState);
    // PUSH_AF;
    uint8_t vramState = wram->wVramState;
    // XOR_A_A;
    // LD_addr_A(wVramState);
    wram->wVramState = 0;
    // CALL(aFlyFunction_InitGFX);
    FlyFunction_InitGFX();
    // depixel4(31, 10, 4, 0);
    // LD_A(SPRITE_ANIM_INDEX_RED_WALK);
    // CALL(aInitSpriteAnimStruct);
    struct SpriteAnim* bc = InitSpriteAnimStruct(SPRITE_ANIM_INDEX_RED_WALK, pixel4(31, 10, 4, 0));
    // LD_HL(SPRITEANIMSTRUCT_TILE_ID);
    // ADD_HL_BC;
    // LD_hl(FIELDMOVE_FLY);
    bc->tileID = FIELDMOVE_FLY;
    // LD_HL(SPRITEANIMSTRUCT_ANIM_SEQ_ID);
    // ADD_HL_BC;
    // LD_hl(SPRITE_ANIM_SEQ_FLY_TO);
    bc->animSeqID = SPRITE_ANIM_SEQ_FLY_TO;
    // LD_HL(SPRITEANIMSTRUCT_VAR4);
    // ADD_HL_BC;
    // LD_hl(11 * 8);
    bc->var4 = 11 * 8;
    // LD_A(64);
    // LD_addr_A(wFrameCounter);
    wram->wFrameCounter = 64;

    while(!bit_test(wram->wJumptableIndex, 7)) {
    // loop:
        // LD_A_addr(wJumptableIndex);
        // BIT_A(7);
        // IF_NZ goto exit;
        // LD_A(0 * SPRITEOAMSTRUCT_LENGTH);
        // LD_addr_A(wCurSpriteOAMAddr);
        wram->wCurSpriteOAMAddr = 0 * SPRITEOAMSTRUCT_LENGTH;
        // CALLFAR(aDoNextFrameForAllSprites);
        DoNextFrameForAllSprites();
        // CALL(aFlyFunction_FrameTimer);
        FlyFunction_FrameTimer();
        // CALL(aDelayFrame);
        DelayFrame();
        // goto loop;
    }

// exit:
    // POP_AF;
    // LD_addr_A(wVramState);
    wram->wVramState = vramState;
    // CALL(aFlyToAnim_RestorePlayerSprite_DespawnLeaves);
    FlyToAnim_RestorePlayerSprite_DespawnLeaves();
    // RET;
}

void FlyFunction_InitGFX(void){
    // CALLFAR(aClearSpriteAnims);
    ClearSpriteAnims();
    // LD_DE(mCutGrassGFX);
    // LD_HL(vTiles0 + LEN_2BPP_TILE * FIELDMOVE_GRASS);
    // LD_BC((BANK(aCutGrassGFX) << 8) | 4);
    // CALL(aRequest2bpp);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles0 + LEN_2BPP_TILE * FIELDMOVE_GRASS, CutGrassGFX, 0, 4);
    // LD_A_addr(wCurPartyMon);
    // LD_HL(wPartySpecies);
    // LD_E_A;
    // LD_D(0);
    // ADD_HL_DE;
    // LD_A_hl;
    // LD_addr_A(wTempIconSpecies);
    wram->wTempIconSpecies = wram->wPartySpecies[wram->wCurPartyMon];
    // LD_E(FIELDMOVE_FLY);
    // FARCALL(aFlyFunction_GetMonIcon);
    FlyFunction_GetMonIcon(FIELDMOVE_FLY);
    // XOR_A_A;
    // LD_addr_A(wJumptableIndex);
    wram->wJumptableIndex = 0;
    // RET;
}

static void FlyFunction_FrameTimer_SpawnLeaf(void) {
    // LD_HL(wFrameCounter2);
    // LD_A_hl;
    // INC_hl;
    // AND_A(0x7);
    // RET_NZ ;
    if((wram->wFrameCounter2++ & 0xf) != 0) // was every seven frames, but that spawned too many leaves.
        return;
    // LD_A_hl;
    // AND_A((6 * 8) >> 1);
    // SLA_A;
    // ADD_A(8 * 8);  // gives a number in [$40, $50, $60, $70]
    // LD_D_A;
    uint16_t de = (((wram->wFrameCounter2 & ((6 * 8) >> 1)) << 1) + (8 * 8)) << 8;
    // LD_E(0);
    // LD_A(SPRITE_ANIM_INDEX_FLY_LEAF);
    // CALL(aInitSpriteAnimStruct);
    struct SpriteAnim* bc = InitSpriteAnimStruct(SPRITE_ANIM_INDEX_FLY_LEAF, de);
    // LD_HL(SPRITEANIMSTRUCT_TILE_ID);
    // ADD_HL_BC;
    // LD_hl(FIELDMOVE_GRASS);
    bc->tileID = FIELDMOVE_GRASS;
    // RET;
}

void FlyFunction_FrameTimer(void){
    // CALL(aFlyFunction_FrameTimer_SpawnLeaf);
    FlyFunction_FrameTimer_SpawnLeaf();
    // LD_HL(wFrameCounter);
    // LD_A_hl;
    // AND_A_A;
    // IF_Z goto exit;
    if(wram->wFrameCounter != 0) {
        // DEC_hl;
        uint8_t a = --wram->wFrameCounter;
        // CP_A(0x40);
        // RET_C ;
        // AND_A(0x7);
        // RET_NZ ;
        if(a < 0x40 || (a & 0x7) != 0)
            return;
        // LD_DE(SFX_FLY);
        // CALL(aPlaySFX);
        PlaySFX(SFX_FLY);
        // RET;
        return;
    }

// exit:
    // LD_HL(wJumptableIndex);
    // SET_hl(7);
    bit_set(wram->wJumptableIndex, 7);
    // RET;
}
