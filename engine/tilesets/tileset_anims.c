#include "../../constants.h"
#include "tileset_anims.h"
#include "../../home/copy.h"
#include "../../home/map.h"

struct TileAnimPtr {
    uint8_t* dest;
    const char* src;
};

static struct TileAnimPtr TowerPillarTilePointer1  = {vram_ptr(vTiles2 + LEN_2BPP_TILE * 0x2d), TowerPillarTile1};
static struct TileAnimPtr TowerPillarTilePointer2  = {vram_ptr(vTiles2 + LEN_2BPP_TILE * 0x2f), TowerPillarTile2};
static struct TileAnimPtr TowerPillarTilePointer3  = {vram_ptr(vTiles2 + LEN_2BPP_TILE * 0x3d), TowerPillarTile3};
static struct TileAnimPtr TowerPillarTilePointer4  = {vram_ptr(vTiles2 + LEN_2BPP_TILE * 0x3f), TowerPillarTile4};
static struct TileAnimPtr TowerPillarTilePointer5  = {vram_ptr(vTiles2 + LEN_2BPP_TILE * 0x3c), TowerPillarTile5};
static struct TileAnimPtr TowerPillarTilePointer6  = {vram_ptr(vTiles2 + LEN_2BPP_TILE * 0x2c), TowerPillarTile6};
static struct TileAnimPtr TowerPillarTilePointer7  = {vram_ptr(vTiles2 + LEN_2BPP_TILE * 0x4d), TowerPillarTile7};
static struct TileAnimPtr TowerPillarTilePointer8  = {vram_ptr(vTiles2 + LEN_2BPP_TILE * 0x4f), TowerPillarTile8};
static struct TileAnimPtr TowerPillarTilePointer9  = {vram_ptr(vTiles2 + LEN_2BPP_TILE * 0x5d), TowerPillarTile9};
static struct TileAnimPtr TowerPillarTilePointer10 = {vram_ptr(vTiles2 + LEN_2BPP_TILE * 0x5f), TowerPillarTile10};

const char TowerPillarTile1[] = "gfx/tilesets/tower-pillar/1.png";
const char TowerPillarTile2[] = "gfx/tilesets/tower-pillar/2.png";
const char TowerPillarTile3[] = "gfx/tilesets/tower-pillar/3.png";
const char TowerPillarTile4[] = "gfx/tilesets/tower-pillar/4.png";
const char TowerPillarTile5[] = "gfx/tilesets/tower-pillar/5.png";
const char TowerPillarTile6[] = "gfx/tilesets/tower-pillar/6.png";
const char TowerPillarTile7[] = "gfx/tilesets/tower-pillar/7.png";
const char TowerPillarTile8[] = "gfx/tilesets/tower-pillar/8.png";
const char TowerPillarTile9[] = "gfx/tilesets/tower-pillar/9.png";
const char TowerPillarTile10[] = "gfx/tilesets/tower-pillar/10.png";

static struct TileAnimPtr WhirlpoolFrames1 = {vram_ptr(vTiles2 + LEN_2BPP_TILE * 0x32), WhirlpoolTiles1};
static struct TileAnimPtr WhirlpoolFrames2 = {vram_ptr(vTiles2 + LEN_2BPP_TILE * 0x33), WhirlpoolTiles2};
static struct TileAnimPtr WhirlpoolFrames3 = {vram_ptr(vTiles2 + LEN_2BPP_TILE * 0x42), WhirlpoolTiles3};
static struct TileAnimPtr WhirlpoolFrames4 = {vram_ptr(vTiles2 + LEN_2BPP_TILE * 0x43), WhirlpoolTiles4};

const char WhirlpoolTiles1[] = "gfx/tilesets/whirlpool/1.png";
const char WhirlpoolTiles2[] = "gfx/tilesets/whirlpool/2.png";
const char WhirlpoolTiles3[] = "gfx/tilesets/whirlpool/3.png";
const char WhirlpoolTiles4[] = "gfx/tilesets/whirlpool/4.png";

//  Increment [hTileAnimFrame] and run that frame's function
//  from the array pointed to by wTilesetAnim.
//  Called in WRAM bank 1, VRAM bank 0, so map tiles
//  $80 and above in VRAM bank 1 cannot be animated
//  without switching to that bank themselves.
void v_AnimateTileset(void){
    // LD_A_addr(wTilesetAnim);
    // LD_E_A;
    // LD_A_addr(wTilesetAnim + 1);
    // LD_D_A;
    const struct TileAnimFrame* de = gTilesetAnim;
    if(!de)
        return;

    // LDH_A_addr(hTileAnimFrame);
    // LD_L_A;
    // INC_A;
    // LDH_addr_A(hTileAnimFrame);
    uint8_t l = hram.hTileAnimFrame++;

    // LD_H(0);
    // ADD_HL_HL;
    // ADD_HL_HL;
    // ADD_HL_DE;

//  2-byte parameter
//  All functions take input de
    // LD_E_hl;
    // INC_HL;
    // LD_D_hl;
    // INC_HL;

//  Function address
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;

    // JP_hl;
    return de[l].func(de[l].tile);
}

#define Tileset0Anim TilesetKantoAnim
#define TilesetJohtoModernAnim TilesetKantoAnim

const struct TileAnimFrame TilesetKantoAnim[] = {
    {vram_ptr(vTiles2 + LEN_2BPP_TILE * 0x14), AnimateWaterTile},
    {NULL, WaitTileAnimation},
    {NULL, WaitTileAnimation},
    {NULL, WaitTileAnimation},
    {NULL, AnimateWaterPalette},
    {NULL, WaitTileAnimation},
    {NULL, AnimateFlowerTile},
    {NULL, WaitTileAnimation},
    {NULL, WaitTileAnimation},
    {NULL, StandingTileFrame8},
    {NULL, DoneTileAnimation},
};

const struct TileAnimFrame TilesetParkAnim[] = {
    {vram_ptr(vTiles2 + LEN_2BPP_TILE * 0x14), AnimateWaterTile},
    {NULL, WaitTileAnimation},
    {vram_ptr(vTiles2 + LEN_2BPP_TILE * 0x5f), AnimateFountainTile},
    {NULL, WaitTileAnimation},
    {NULL, AnimateWaterPalette},
    {NULL, WaitTileAnimation},
    {NULL, AnimateFlowerTile},
    {NULL, WaitTileAnimation},
    {NULL, WaitTileAnimation},
    {NULL, StandingTileFrame8},
    {NULL, DoneTileAnimation},
};

const struct TileAnimFrame TilesetForestAnim[] = {
    {NULL, ForestTreeLeftAnimation},
    {NULL, ForestTreeRightAnimation},
    {NULL, WaitTileAnimation},
    {NULL, WaitTileAnimation},
    {NULL, WaitTileAnimation},
    {NULL, ForestTreeLeftAnimation2},
    {NULL, ForestTreeRightAnimation2},
    {NULL, AnimateFlowerTile},
    {vram_ptr(vTiles2 + LEN_2BPP_TILE * 0x14), AnimateWaterTile},
    {NULL, AnimateWaterPalette},
    {NULL, StandingTileFrame8},
    {NULL, DoneTileAnimation},
};

const struct TileAnimFrame TilesetJohtoAnim[] = {
    {vram_ptr(vTiles2 + LEN_2BPP_TILE * 0x14), AnimateWaterTile},
    {NULL, WaitTileAnimation},
    {NULL, WaitTileAnimation},
    {NULL, AnimateWaterPalette},
    {NULL, WaitTileAnimation},
    {NULL, AnimateFlowerTile},
    {(uint8_t*)&WhirlpoolFrames1, AnimateWhirlpoolTile},
    {(uint8_t*)&WhirlpoolFrames2, AnimateWhirlpoolTile},
    {(uint8_t*)&WhirlpoolFrames3, AnimateWhirlpoolTile},
    {(uint8_t*)&WhirlpoolFrames4, AnimateWhirlpoolTile},
    {NULL, WaitTileAnimation},
    {NULL, StandingTileFrame8},
    {NULL, DoneTileAnimation},
};

const struct TileAnimFrame UnusedTilesetAnim1[] = {
//  //  unreferenced
//  Scrolls tile $03 like cave water, but also has the standard $03 flower tile.
    {vram_ptr(vTiles2 + LEN_2BPP_TILE * 0x03), ReadTileToAnimBuffer},
    {wram_ptr(wTileAnimBuffer), ScrollTileRightLeft},
    {vram_ptr(vTiles2 + LEN_2BPP_TILE * 0x03), WriteTileFromAnimBuffer},
    {NULL, WaitTileAnimation},
    {NULL, WaitTileAnimation},
    {NULL, WaitTileAnimation},
    {NULL, AnimateFlowerTile},
    {NULL, WaitTileAnimation},
    {NULL, WaitTileAnimation},
    {NULL, WaitTileAnimation},
    {NULL, DoneTileAnimation},
};

const struct TileAnimFrame UnusedTilesetAnim2[] = {
//  //  unreferenced
//  Scrolls tile $14 like cave water.
    {vram_ptr(vTiles2 + LEN_2BPP_TILE * 0x14), ReadTileToAnimBuffer},
    {wram_ptr(wTileAnimBuffer), ScrollTileRightLeft},
    {vram_ptr(vTiles2 + LEN_2BPP_TILE * 0x14), WriteTileFromAnimBuffer},
    {NULL, WaitTileAnimation},
    {NULL, WaitTileAnimation},
    {NULL, WaitTileAnimation},
    {NULL, WaitTileAnimation},
    {NULL, WaitTileAnimation},
    {NULL, WaitTileAnimation},
    {NULL, WaitTileAnimation},
    {NULL, DoneTileAnimation},
};

const struct TileAnimFrame TilesetPortAnim[] = {
    {vram_ptr(vTiles2 + LEN_2BPP_TILE * 0x14), AnimateWaterTile},
    {NULL, WaitTileAnimation},
    {NULL, WaitTileAnimation},
    {NULL, WaitTileAnimation},
    {NULL, WaitTileAnimation},
    {NULL, AnimateWaterPalette},
    {NULL, WaitTileAnimation},
    {NULL, WaitTileAnimation},
    {NULL, WaitTileAnimation},
    {NULL, WaitTileAnimation},
    {NULL, StandingTileFrame8},
    {NULL, DoneTileAnimation},
};

const struct TileAnimFrame TilesetEliteFourRoomAnim[] = {
    {NULL, AnimateLavaBubbleTile2},
    {NULL, WaitTileAnimation},
    {NULL, WaitTileAnimation},
    {NULL, WaitTileAnimation},
    {NULL, AnimateLavaBubbleTile1},
    {NULL, WaitTileAnimation},
    {NULL, StandingTileFrame8},
    {NULL, DoneTileAnimation},
};

void UnusedTilesetAnim3(void){
//  //  unreferenced
//  Scrolls tile $53 like a waterfall
    //dw ['vTiles2 + LEN_2BPP_TILE * 0x53', 'ReadTileToAnimBuffer'];
    //dw ['wTileAnimBuffer', 'ScrollTileDown'];
    //dw ['wTileAnimBuffer', 'ScrollTileDown'];
    //dw ['vTiles2 + LEN_2BPP_TILE * 0x53', 'WriteTileFromAnimBuffer'];
    //dw ['vTiles2 + LEN_2BPP_TILE * 0x03', 'ReadTileToAnimBuffer'];
    //dw ['wTileAnimBuffer', 'ScrollTileRightLeft'];
    //dw ['vTiles2 + LEN_2BPP_TILE * 0x03', 'WriteTileFromAnimBuffer'];
    //dw ['vTiles2 + LEN_2BPP_TILE * 0x53', 'ReadTileToAnimBuffer'];
    //dw ['wTileAnimBuffer', 'ScrollTileDown'];
    //dw ['wTileAnimBuffer', 'ScrollTileDown'];
    //dw ['vTiles2 + LEN_2BPP_TILE * 0x53', 'WriteTileFromAnimBuffer'];
    //dw ['NULL', 'DoneTileAnimation'];

    return UnusedTilesetAnim4();
}

void UnusedTilesetAnim4(void){
//  //  unreferenced
//  Scrolls tile $54 like a waterfall
    //dw ['vTiles2 + LEN_2BPP_TILE * 0x54', 'ReadTileToAnimBuffer'];
    //dw ['wTileAnimBuffer', 'ScrollTileDown'];
    //dw ['wTileAnimBuffer', 'ScrollTileDown'];
    //dw ['vTiles2 + LEN_2BPP_TILE * 0x54', 'WriteTileFromAnimBuffer'];
    //dw ['NULL', 'WaitTileAnimation'];
    //dw ['vTiles2 + LEN_2BPP_TILE * 0x03', 'ReadTileToAnimBuffer'];
    //dw ['wTileAnimBuffer', 'ScrollTileRightLeft'];
    //dw ['vTiles2 + LEN_2BPP_TILE * 0x03', 'WriteTileFromAnimBuffer'];
    //dw ['NULL', 'WaitTileAnimation'];
    //dw ['vTiles2 + LEN_2BPP_TILE * 0x54', 'ReadTileToAnimBuffer'];
    //dw ['wTileAnimBuffer', 'ScrollTileDown'];
    //dw ['wTileAnimBuffer', 'ScrollTileDown'];
    //dw ['vTiles2 + LEN_2BPP_TILE * 0x54', 'WriteTileFromAnimBuffer'];
    //dw ['NULL', 'DoneTileAnimation'];
}

#define TilesetCaveAnim TilesetDarkCaveAnim

const struct TileAnimFrame TilesetDarkCaveAnim[] =  {
    {vram_ptr(vTiles2 + LEN_2BPP_TILE * 0x14), ReadTileToAnimBuffer},
    {NULL, FlickeringCaveEntrancePalette},
    {wram_ptr(wTileAnimBuffer), ScrollTileRightLeft},
    {NULL, FlickeringCaveEntrancePalette},
    {vram_ptr(vTiles2 + LEN_2BPP_TILE * 0x14), WriteTileFromAnimBuffer},
    {NULL, FlickeringCaveEntrancePalette},
    {NULL, AnimateWaterPalette},
    {NULL, FlickeringCaveEntrancePalette},
    {vram_ptr(vTiles2 + LEN_2BPP_TILE * 0x40), ReadTileToAnimBuffer},
    {NULL, FlickeringCaveEntrancePalette},
    {wram_ptr(wTileAnimBuffer), ScrollTileDown},
    {NULL, FlickeringCaveEntrancePalette},
    {wram_ptr(wTileAnimBuffer), ScrollTileDown},
    {NULL, FlickeringCaveEntrancePalette},
    {wram_ptr(wTileAnimBuffer), ScrollTileDown},
    {NULL, FlickeringCaveEntrancePalette},
    {vram_ptr(vTiles2 + LEN_2BPP_TILE * 0x40), WriteTileFromAnimBuffer},
    {NULL, FlickeringCaveEntrancePalette},
    {NULL, DoneTileAnimation},
};

const struct TileAnimFrame TilesetIcePathAnim[] = {
    {vram_ptr(vTiles2 + LEN_2BPP_TILE * 0x35), ReadTileToAnimBuffer},
    {NULL, FlickeringCaveEntrancePalette},
    {wram_ptr(wTileAnimBuffer), ScrollTileRightLeft},
    {NULL, FlickeringCaveEntrancePalette},
    {vram_ptr(vTiles2 + LEN_2BPP_TILE * 0x35), WriteTileFromAnimBuffer},
    {NULL, FlickeringCaveEntrancePalette},
    {NULL, AnimateWaterPalette},
    {NULL, FlickeringCaveEntrancePalette},
    {vram_ptr(vTiles2 + LEN_2BPP_TILE * 0x31), ReadTileToAnimBuffer},
    {NULL, FlickeringCaveEntrancePalette},
    {wram_ptr(wTileAnimBuffer), ScrollTileDown},
    {NULL, FlickeringCaveEntrancePalette},
    {wram_ptr(wTileAnimBuffer), ScrollTileDown},
    {NULL, FlickeringCaveEntrancePalette},
    {wram_ptr(wTileAnimBuffer), ScrollTileDown},
    {NULL, FlickeringCaveEntrancePalette},
    {vram_ptr(vTiles2 + LEN_2BPP_TILE * 0x31), WriteTileFromAnimBuffer},
    {NULL, FlickeringCaveEntrancePalette},
    {NULL, DoneTileAnimation},
};

const struct TileAnimFrame TilesetTowerAnim[] = {
    {(uint8_t*)&TowerPillarTilePointer9,  AnimateTowerPillarTile},
    {(uint8_t*)&TowerPillarTilePointer10, AnimateTowerPillarTile},
    {(uint8_t*)&TowerPillarTilePointer7,  AnimateTowerPillarTile},
    {(uint8_t*)&TowerPillarTilePointer8,  AnimateTowerPillarTile},
    {(uint8_t*)&TowerPillarTilePointer5,  AnimateTowerPillarTile},
    {(uint8_t*)&TowerPillarTilePointer6,  AnimateTowerPillarTile},
    {(uint8_t*)&TowerPillarTilePointer3,  AnimateTowerPillarTile},
    {(uint8_t*)&TowerPillarTilePointer4,  AnimateTowerPillarTile},
    {(uint8_t*)&TowerPillarTilePointer1,  AnimateTowerPillarTile},
    {(uint8_t*)&TowerPillarTilePointer2,  AnimateTowerPillarTile},
    {NULL, StandingTileFrame},
    {NULL, WaitTileAnimation},
    {NULL, WaitTileAnimation},
    {NULL, WaitTileAnimation},
    {NULL, WaitTileAnimation},
    {NULL, DoneTileAnimation},
};

void UnusedTilesetAnim5(void){
//  //  unreferenced
//  Scrolls tile $4f like cave water.
    //dw ['vTiles2 + LEN_2BPP_TILE * 0x4f', 'ReadTileToAnimBuffer'];
    //dw ['wTileAnimBuffer', 'ScrollTileRightLeft'];
    //dw ['vTiles2 + LEN_2BPP_TILE * 0x4f', 'WriteTileFromAnimBuffer'];
    //dw ['NULL', 'WaitTileAnimation'];
    //dw ['NULL', 'WaitTileAnimation'];
    //dw ['NULL', 'WaitTileAnimation'];
    //dw ['NULL', 'WaitTileAnimation'];
    //dw ['NULL', 'WaitTileAnimation'];
    //dw ['NULL', 'WaitTileAnimation'];
    //dw ['NULL', 'DoneTileAnimation'];
}

#define TilesetBattleTowerOutsideAnim TilesetAerodactylWordRoomAnim
#define TilesetHouseAnim TilesetAerodactylWordRoomAnim
#define TilesetPlayersHouseAnim TilesetAerodactylWordRoomAnim
#define TilesetPokecenterAnim TilesetAerodactylWordRoomAnim
#define TilesetGateAnim TilesetAerodactylWordRoomAnim
#define TilesetLabAnim TilesetAerodactylWordRoomAnim
#define TilesetFacilityAnim TilesetAerodactylWordRoomAnim
#define TilesetMartAnim TilesetAerodactylWordRoomAnim
#define TilesetMansionAnim TilesetAerodactylWordRoomAnim
#define TilesetGameCornerAnim TilesetAerodactylWordRoomAnim
#define TilesetTraditionalHouseAnim TilesetAerodactylWordRoomAnim
#define TilesetTrainStationAnim TilesetAerodactylWordRoomAnim
#define TilesetChampionsRoomAnim TilesetAerodactylWordRoomAnim
#define TilesetLighthouseAnim TilesetAerodactylWordRoomAnim
#define TilesetPlayersRoomAnim TilesetAerodactylWordRoomAnim
#define TilesetPokeComCenterAnim TilesetAerodactylWordRoomAnim
#define TilesetBattleTowerInsideAnim TilesetAerodactylWordRoomAnim
#define TilesetRuinsOfAlphAnim TilesetAerodactylWordRoomAnim
#define TilesetRadioTowerAnim TilesetAerodactylWordRoomAnim
#define TilesetUndergroundAnim TilesetAerodactylWordRoomAnim
#define TilesetBetaWordRoomAnim TilesetAerodactylWordRoomAnim
#define TilesetHoOhWordRoomAnim TilesetAerodactylWordRoomAnim
#define TilesetKabutoWordRoomAnim TilesetAerodactylWordRoomAnim
#define TilesetOmanyteWordRoomAnim TilesetAerodactylWordRoomAnim

const struct TileAnimFrame TilesetAerodactylWordRoomAnim[] = {
    {NULL, WaitTileAnimation},
    {NULL, WaitTileAnimation},
    {NULL, WaitTileAnimation},
    {NULL, WaitTileAnimation},
    {NULL, DoneTileAnimation},
};

//  Reset the animation command loop.
void DoneTileAnimation(uint8_t* de){
    (void)de;
    // XOR_A_A;
    // LDH_addr_A(hTileAnimFrame);
    hram.hTileAnimFrame = 0;
}

//  Do nothing this frame.
void WaitTileAnimation(uint8_t* de){
    (void)de;
    // RET;
}

//  Tick the wTileAnimationTimer, wrapping from 7 to 0.
void StandingTileFrame8(uint8_t* de){
    (void)de;
    // LD_A_addr(wTileAnimationTimer);
    // INC_A;
    // AND_A(0b111);
    // LD_addr_A(wTileAnimationTimer);
    wram->wTileAnimationTimer = (wram->wTileAnimationTimer + 1) & 0b111;
    // RET;
}

void ScrollTileRightLeft(uint8_t* de){
//  Scroll right for 4 ticks, then left for 4 ticks.
    // LD_A_addr(wTileAnimationTimer);
    // INC_A;
    // AND_A(0b111);
    // LD_addr_A(wTileAnimationTimer);
    wram->wTileAnimationTimer = (wram->wTileAnimationTimer + 1) & 0b111;
    // AND_A(0b100);
    // JR_NZ (mScrollTileLeft);
    if(wram->wTileAnimationTimer & 0b100)
        return ScrollTileLeft(de);
    // JR(mScrollTileRight);
    return ScrollTileRight(de);
}

//  //  unreferenced
//  Scroll up for 4 ticks, then down for 4 ticks.
void ScrollTileUpDown(void){
    // LD_A_addr(wTileAnimationTimer);
    // INC_A;
    // AND_A(0b111);
    // LD_addr_A(wTileAnimationTimer);
    // AND_A(0b100);
    // JR_NZ (mScrollTileDown);
    // JR(mScrollTileUp);
}

void ScrollTileLeft(uint8_t* de){
    // LD_H_D;
    // LD_L_E;
    // LD_C(LEN_2BPP_TILE / 4);

    for(int i = 0; i < LEN_2BPP_TILE; ++i) {
    // loop:
        de[i] = (de[i] >> 7) | (de[i] << 1);
        // for(int rept = 0; rept < 4; rept++){
        // LD_A_hl;
        // RLCA;
        // LD_hli_A;
        // }
        // DEC_C;
        // IF_NZ goto loop;
    }
    // RET;

}

void ScrollTileRight(uint8_t* de){
    // LD_H_D;
    // LD_L_E;
    // LD_C(LEN_2BPP_TILE / 4);

    for(int i = 0; i < LEN_2BPP_TILE; ++i) {
    // loop:
        de[i] = (de[i] >> 1) | (de[i] << 7);
        // for(int rept = 0; rept < 4; rept++){
        // LD_A_hl;
        // RRCA;
        // LD_hli_A;
        // }
        // DEC_C;
        // IF_NZ goto loop;
    }
    // RET;

}

void ScrollTileUp(uint8_t* de){
    // LD_H_D;
    // LD_L_E;
    // LD_D_hl;
    uint8_t d = de[0];
    // INC_HL;
    // LD_E_hl;
    uint8_t e = de[1];
    // LD_BC(LEN_2BPP_TILE - 2);
    // ADD_HL_BC;
    de += LEN_2BPP_TILE - 2;
    // LD_A(LEN_2BPP_TILE / 4);
    uint8_t a = LEN_2BPP_TILE / 4;

    uint8_t b, c;
    do {
    // loop:
        // LD_C_hl;
        c = *de;
        // LD_hl_E;
        *de = e;
        // DEC_HL;
        --de;
        // LD_B_hl;
        b = *de;
        // LD_hl_D;
        *de = d;
        // DEC_HL;
        --de;
        // LD_E_hl;
        e = *de;
        // LD_hl_C;
        *de = c;
        // DEC_HL;
        --de;
        // LD_D_hl;
        d = *de;
        // LD_hl_B;
        *de = b;
        // DEC_HL;
        --de;
        // DEC_A;
        // IF_NZ goto loop;
    } while(--a != 0);
    // RET;
}

void ScrollTileDown(uint8_t* de){
    // LD_H_D;
    // LD_L_E;
    // LD_DE(LEN_2BPP_TILE - 2);
    // PUSH_HL;
    // ADD_HL_DE;
    // LD_D_hl;
    // INC_HL;
    // LD_E_hl;
    // POP_HL;
    uint8_t d = de[LEN_2BPP_TILE - 2];
    uint8_t e = de[LEN_2BPP_TILE - 1];
    // LD_A(LEN_2BPP_TILE / 4);
    uint8_t a = LEN_2BPP_TILE / 4;

    uint8_t b, c;
    do {
    // loop:
        // LD_B_hl;
        b = *de;
        // LD_hl_D;
        *de = d;
        // INC_HL;
        de++;
        // LD_C_hl;
        c = *de;
        // LD_hl_E;
        *de = e;
        // INC_HL;
        de++;
        // LD_D_hl;
        d = *de;
        // LD_hl_B;
        *de = b;
        // INC_HL;
        // LD_E_hl;
        e = *de;
        // LD_hl_C;
        *de = c;
        // INC_HL;
        de++;
        // DEC_A;
        // IF_NZ goto loop;
    } while(--a != 0);
    // RET;
}

void AnimateFountainTile(uint8_t* de){
    static const char FountainTile1[] = "gfx/tilesets/fountain/1.png";
    static const char FountainTile2[] = "gfx/tilesets/fountain/2.png";
    static const char FountainTile3[] = "gfx/tilesets/fountain/3.png";
    static const char FountainTile4[] = "gfx/tilesets/fountain/4.png";
    static const char FountainTile5[] = "gfx/tilesets/fountain/5.png";
    static const char *FountainTileFramePointers[] = {
        FountainTile1,
        FountainTile2,
        FountainTile3,
        FountainTile4,
        FountainTile3,
        FountainTile4,
        FountainTile5,
        FountainTile1,
    };
//  Save the stack pointer in bc for WriteTile to restore
    // LD_HL_SP(0);
    // LD_B_H;
    // LD_C_L;

    // LD_HL(mAnimateFountainTile_FountainTileFramePointers);

//  A cycle of 8 frames, updating every tick
    // LD_A_addr(wTileAnimationTimer);
    // AND_A(0b111);
    uint8_t a = wram->wTileAnimationTimer & 0b111;

//  hl = [.FountainTileFramePointers + a * 2]
    // ADD_A_A;
    // ADD_A_L;
    // LD_L_A;
    // IF_NC goto okay;
    // INC_H;

// okay:
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;

//  Write the tile graphic from hl (now sp) to de (now hl)
    // LD_SP_HL;
    // LD_L_E;
    // LD_H_D;
    // JP(mWriteTile);
    LoadPNG2bppAssetSectionToVRAM(de, FountainTileFramePointers[a], 0, 1);
}

void AnimateWaterTile(uint8_t* de){
    static const char WaterTileFrames[] = "gfx/tilesets/water/water.png";
//  Save the stack pointer in bc for WriteTile to restore
    // LD_HL_SP(0);
    // LD_B_H;
    // LD_C_L;

//  A cycle of 4 frames, updating every other tick
    // LD_A_addr(wTileAnimationTimer);
    // AND_A(0b110);

//  hl = .WaterTileFrames + a * 8
//  (a was pre-multiplied by 2 from 'and %110')
    // ADD_A_A;
    // ADD_A_A;
    // ADD_A_A;
    // ADD_A(LOW(aAnimateWaterTile_WaterTileFrames));
    // LD_L_A;
    // LD_A(0);
    // ADC_A(HIGH(aAnimateWaterTile_WaterTileFrames));
    // LD_H_A;

//  Write the tile graphic from hl (now sp) to de (now hl)
    // LD_SP_HL;
    // LD_L_E;
    // LD_H_D;
    // JP(mWriteTile);
    LoadPNG2bppAssetSectionToVRAM(de, WaterTileFrames, (wram->wTileAnimationTimer & 0b110) >> 1, 1);
}

void ForestTreeLeftAnimation(uint8_t* de){
    (void)de;
//  Save the stack pointer in bc for WriteTile to restore
    // LD_HL_SP(0);
    // LD_B_H;
    // LD_C_L;

    const char* hl;
//  Only animate this during the Celebi event
    // LD_A_addr(wCelebiEvent);
    // BIT_A(CELEBIEVENT_FOREST_IS_RESTLESS_F);
    // IF_NZ goto do_animation;
    if(!bit_test(wram->wCelebiEvent, CELEBIEVENT_FOREST_IS_RESTLESS_F)) {
        // LD_HL(mForestTreeLeftFrames);
        // goto got_frames;
        hl = ForestTreeLeftFrames[0];
    }
    else {
    // do_animation:
    //  A cycle of 2 frames, updating every tick
        // LD_A_addr(wTileAnimationTimer);
        // CALL(aGetForestTreeFrame);
        uint8_t a = GetForestTreeFrame(wram->wTileAnimationTimer);

    //  hl = ForestTreeLeftFrames + a * 8
    //  (a was pre-multiplied by 2 from GetForestTreeFrame)
        // ADD_A_A;
        // ADD_A_A;
        // ADD_A_A;
        // ADD_A(LOW(aForestTreeLeftFrames));
        // LD_L_A;
        // LD_A(0);
        // ADC_A(HIGH(aForestTreeLeftFrames));
        // LD_H_A;
        hl = ForestTreeLeftFrames[a];
    }

// got_frames:
//  Write the tile graphic from hl (now sp) to tile $0c (now hl)
    // LD_SP_HL;
    // LD_HL(vTiles2 + LEN_2BPP_TILE * 0x0c);
    // JP(mWriteTile);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles2 + LEN_2BPP_TILE * 0x0c, hl, 0, 1);
}

const char* ForestTreeLeftFrames[] = {
    "gfx/tilesets/forest-tree/1.png",
    "gfx/tilesets/forest-tree/2.png",
};

const char* ForestTreeRightFrames[] = {
    "gfx/tilesets/forest-tree/3.png",
    "gfx/tilesets/forest-tree/4.png",
};

void ForestTreeRightAnimation(uint8_t* de){
    (void)de;
//  Save the stack pointer in bc for WriteTile to restore
    // LD_HL_SP(0);
    // LD_B_H;
    // LD_C_L;

    const char* hl;
//  Only animate this during the Celebi event
    // LD_A_addr(wCelebiEvent);
    // BIT_A(CELEBIEVENT_FOREST_IS_RESTLESS_F);
    // IF_NZ goto do_animation;
    if(!bit_test(wram->wCelebiEvent, CELEBIEVENT_FOREST_IS_RESTLESS_F)) {
        // LD_HL(mForestTreeRightFrames);
        hl = ForestTreeRightFrames[0];
        // goto got_frames;
    }
    else {
    // do_animation:
    //  A cycle of 2 frames, updating every tick
        // LD_A_addr(wTileAnimationTimer);
        // CALL(aGetForestTreeFrame);
        uint8_t a = GetForestTreeFrame(wram->wTileAnimationTimer);

    //  hl = ForestTreeRightFrames + a * 8
    //  (a was pre-multiplied by 2 from GetForestTreeFrame)
        // ADD_A_A;
        // ADD_A_A;
        // ADD_A_A;
        // ADD_A(LOW(aForestTreeLeftFrames));
        // LD_L_A;
        // LD_A(0);
        // ADC_A(HIGH(aForestTreeLeftFrames));
        // LD_H_A;
        // PUSH_BC;
        // LD_BC(mForestTreeRightFrames - mForestTreeLeftFrames);
        // ADD_HL_BC;
        // POP_BC;
        hl = ForestTreeRightFrames[a];
    }

// got_frames:
//  Write the tile graphic from hl (now sp) to tile $0f (now hl)
    // LD_SP_HL;
    // LD_HL(vTiles2 + LEN_2BPP_TILE * 0x0f);
    // JP(mWriteTile);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles2 + LEN_2BPP_TILE * 0x0f, hl, 0, 1);
}

void ForestTreeLeftAnimation2(uint8_t* de){
    (void)de;
//  Save the stack pointer in bc for WriteTile to restore
    // LD_HL_SP(0);
    // LD_B_H;
    // LD_C_L;

//  Only animate this during the Celebi event
    // LD_A_addr(wCelebiEvent);
    // BIT_A(CELEBIEVENT_FOREST_IS_RESTLESS_F);
    // IF_NZ goto do_animation;
    const char* hl;
    if(!bit_test(wram->wCelebiEvent, CELEBIEVENT_FOREST_IS_RESTLESS_F)) {
        // LD_HL(mForestTreeLeftFrames);
        hl = ForestTreeLeftFrames[0];
        // goto got_frames;
    }
    else {
    // do_animation:
    //  A cycle of 2 frames, updating every tick
        // LD_A_addr(wTileAnimationTimer);
        // CALL(aGetForestTreeFrame);

    //  Offset by 1 frame from ForestTreeLeftAnimation
        // XOR_A(0b10);
        uint8_t f = GetForestTreeFrame(wram->wTileAnimationTimer) ^ 0b10;

    //  hl = ForestTreeLeftFrames + a * 8
    //  (a was pre-multiplied by 2 from GetForestTreeFrame)
        // ADD_A_A;
        // ADD_A_A;
        // ADD_A_A;
        // ADD_A(LOW(aForestTreeLeftFrames));
        // LD_L_A;
        // LD_A(0);
        // ADC_A(HIGH(aForestTreeLeftFrames));
        // LD_H_A;
        hl = ForestTreeLeftFrames[f];
    }

// got_frames:
//  Write the tile graphic from hl (now sp) to tile $0c (now hl)
    // LD_SP_HL;
    // LD_HL(vTiles2 + LEN_2BPP_TILE * 0x0c);
    // JP(mWriteTile);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles2 + LEN_2BPP_TILE * 0x0c, hl, 0, 1);
}

void ForestTreeRightAnimation2(uint8_t* de){
    (void)de;
//  Save the stack pointer in bc for WriteTile to restore
    // LD_HL_SP(0);
    // LD_B_H;
    // LD_C_L;

//  Only animate this during the Celebi event
    const char* hl;
    // LD_A_addr(wCelebiEvent);
    // BIT_A(CELEBIEVENT_FOREST_IS_RESTLESS_F);
    // IF_NZ goto do_animation;
    if(!bit_test(wram->wCelebiEvent, CELEBIEVENT_FOREST_IS_RESTLESS_F)) {
        // LD_HL(mForestTreeRightFrames);
        hl = ForestTreeRightFrames[0];
        // goto got_frames;
    }
    else {
    // do_animation:
    //  A cycle of 2 frames, updating every tick
        // LD_A_addr(wTileAnimationTimer);
        // CALL(aGetForestTreeFrame);

    //  Offset by 1 frame from ForestTreeRightAnimation
        // XOR_A(0b10);
        uint8_t f = GetForestTreeFrame(wram->wTileAnimationTimer) ^ 0b10;

    //  hl = ForestTreeRightFrames + a * 8
    //  (a was pre-multiplied by 2 from GetForestTreeFrame)
        // ADD_A_A;
        // ADD_A_A;
        // ADD_A_A;
        // ADD_A(LOW(aForestTreeLeftFrames));
        // LD_L_A;
        // LD_A(0);
        // ADC_A(HIGH(aForestTreeLeftFrames));
        // LD_H_A;
        // PUSH_BC;
        // LD_BC(mForestTreeRightFrames - mForestTreeLeftFrames);
        // ADD_HL_BC;
        // POP_BC;
        hl = ForestTreeRightFrames[f];
    }

// got_frames:
//  Write the tile graphic from hl (now sp) to tile $0f (now hl)
    // LD_SP_HL;
    // LD_HL(vTiles2 + LEN_2BPP_TILE * 0x0f);
    // JP(mWriteTile);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles2 + LEN_2BPP_TILE * 0x0f, hl, 0, 1);
}

uint8_t GetForestTreeFrame(uint8_t a){
//  Return 0 if a is even, or 2 if odd.
//  lmao
    // AND_A_A;
    // IF_Z goto even;
    // CP_A(1);
    // IF_Z goto odd;
    // CP_A(2);
    // IF_Z goto even;
    // CP_A(3);
    // IF_Z goto odd;
    // CP_A(4);
    // IF_Z goto even;
    // CP_A(5);
    // IF_Z goto odd;
    // CP_A(6);
    // IF_Z goto even;

// odd:
    // LD_A(2);
    // SCF;
    // RET;

// even:
    // XOR_A_A;
    // RET;
    return (a & 1)? 2: 0;
}

void AnimateFlowerTile(uint8_t* de){
    (void)de;
    static const char* FlowerTileFrames[] = {
        "gfx/tilesets/flower/dmg_1.png",
        "gfx/tilesets/flower/cgb_1.png",
        "gfx/tilesets/flower/dmg_2.png",
        "gfx/tilesets/flower/cgb_2.png",
    };
//  Save the stack pointer in bc for WriteTile to restore
    // LD_HL_SP(0);
    // LD_B_H;
    // LD_C_L;

//  A cycle of 2 frames, updating every other tick
    // LD_A_addr(wTileAnimationTimer);
    // AND_A(0b10);
    uint8_t e = wram->wTileAnimationTimer & 0b10;

//  CGB has different tile graphics for flowers
    // LD_E_A;
    // LDH_A_addr(hCGB);
    // AND_A(1);
    // ADD_A_E;

//  hl = .FlowerTileFrames + a * 16
    // SWAP_A;
    // LD_E_A;
    // LD_D(0);
    // LD_HL(mAnimateFlowerTile_FlowerTileFrames);
    // ADD_HL_DE;

//  Write the tile graphic from hl (now sp) to tile $03 (now hl)
    // LD_SP_HL;
    // LD_HL(vTiles2 + LEN_2BPP_TILE * 0x03);
    // JP(mWriteTile);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles2 + LEN_2BPP_TILE * 0x03, FlowerTileFrames[e + (hram.hCGB & 1)], 0, 1);
}

void AnimateLavaBubbleTile1(uint8_t* de){
    (void)de;
//  Save the stack pointer in bc for WriteTile to restore
    // LD_HL_SP(0);
    // LD_B_H;
    // LD_C_L;

//  A cycle of 4 frames, updating every other tick
    // LD_A_addr(wTileAnimationTimer);
    // AND_A(0b110);

//  Offset by 2 frames from AnimateLavaBubbleTile2
    // SRL_A;
    // INC_A;
    // INC_A;
    // AND_A(0b011);
    uint8_t a = (((wram->wTileAnimationTimer & 0b110) >> 1) + 2) & 0b011;

//  hl = LavaBubbleTileFrames + a * 16
    // SWAP_A;
    // LD_E_A;
    // LD_D(0);
    // LD_HL(mLavaBubbleTileFrames);
    // ADD_HL_DE;

//  Write the tile graphic from hl (now sp) to tile $5b (now hl)
    // LD_SP_HL;
    // LD_HL(vTiles2 + LEN_2BPP_TILE * 0x5b);
    // JP(mWriteTile);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles2 + LEN_2BPP_TILE * 0x5b, LavaBubbleTileFrames[a], 0, 1);
}

void AnimateLavaBubbleTile2(uint8_t* de){
    (void)de;
//  Save the stack pointer in bc for WriteTile to restore
    // LD_HL_SP(0);
    // LD_B_H;
    // LD_C_L;

//  A cycle of 4 frames, updating every other tick
    // LD_A_addr(wTileAnimationTimer);
    // AND_A(0b110);

//  hl = LavaBubbleTileFrames + a * 8
//  (a was pre-multiplied by 2 from 'and %110')
    // ADD_A_A;
    // ADD_A_A;
    // ADD_A_A;
    // LD_E_A;
    // LD_D(0);
    // LD_HL(mLavaBubbleTileFrames);
    // ADD_HL_DE;

//  Write the tile graphic from hl (now sp) to tile $38 (now hl)
    // LD_SP_HL;
    // LD_HL(vTiles2 + LEN_2BPP_TILE * 0x38);
    // JP(mWriteTile);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles2 + LEN_2BPP_TILE * 0x38, LavaBubbleTileFrames[(wram->wTileAnimationTimer & 0b110) >> 1], 0, 1);
}

const char* LavaBubbleTileFrames[] = {
    "gfx/tilesets/lava/1.png",
    "gfx/tilesets/lava/2.png",
    "gfx/tilesets/lava/3.png",
    "gfx/tilesets/lava/4.png",
};

//  Input de points to the destination in VRAM, then the source tile frames
void AnimateTowerPillarTile(uint8_t* de){
    static const uint8_t TowerPillarTileFrameOffsets[] = {
        0,
        1,
        2,
        3,
        4,
        3,
        2,
        1,
    };
    const struct TileAnimPtr* p = (const struct TileAnimPtr*)de;
//  Save the stack pointer in bc for WriteTile to restore
    // LD_HL_SP(0);
    // LD_B_H;
    // LD_C_L;

//  A cycle of 8 frames, updating every tick
    // LD_A_addr(wTileAnimationTimer);
    // AND_A(0b111);
    uint8_t a = wram->wTileAnimationTimer & 0b111;

//  a = [.TowerPillarTileFrameOffsets + a]
    // LD_HL(mAnimateTowerPillarTile_TowerPillarTileFrameOffsets);
    // ADD_A_L;
    // LD_L_A;
    // LD_A(0);
    // ADC_A_H;
    // LD_H_A;
    // LD_A_hl;

//  de = the destination in VRAM
    // LD_L_E;
    // LD_H_D;
    // LD_E_hl;
    // INC_HL;
    // LD_D_hl;
    // INC_HL;

//  hl = the source tile frames + offset a
    // ADD_A_hl;
    // INC_HL;
    // LD_H_hl;
    // LD_L_A;
    // LD_A(0);
    // ADC_A_H;
    // LD_H_A;

//  Write the tile graphic from hl (now sp) to de (now hl)
    // LD_SP_HL;
    // LD_L_E;
    // LD_H_D;
    // JR(mWriteTile);
    LoadPNG2bppAssetSectionToVRAM(p->dest, p->src, TowerPillarTileFrameOffsets[a], 1);
}

//  Tick the wTileAnimationTimer.
void StandingTileFrame(uint8_t* de){
    (void)de;
    // LD_HL(wTileAnimationTimer);
    // INC_hl;
    wram->wTileAnimationTimer++;
    // RET;

}

//  Input de points to the destination in VRAM, then the source tile frames
void AnimateWhirlpoolTile(uint8_t* de){

//  Save the stack pointer in bc for WriteTile to restore
    // LD_HL_SP(0);
    // LD_B_H;
    // LD_C_L;
    const struct TileAnimPtr* p = (const struct TileAnimPtr*)de;

//  de = the destination in VRAM
    // LD_L_E;
    // LD_H_D;
    // LD_E_hl;
    // INC_HL;
    // LD_D_hl;
    // INC_HL;

//  A cycle of 4 frames, updating every tick
    // LD_A_addr(wTileAnimationTimer);
    // AND_A(0b11);
    uint8_t t = wram->wTileAnimationTimer & 0b11;

//  hl = the source tile frames + a * 16
    // SWAP_A;
    // ADD_A_hl;
    // INC_HL;
    // LD_H_hl;
    // LD_L_A;
    // LD_A(0);
    // ADC_A_H;
    // LD_H_A;

//  Write the tile graphic from hl (now sp) to de (now hl)
    // LD_SP_HL;
    // LD_L_E;
    // LD_H_D;
    // JR(mWriteTile);
    LoadPNG2bppAssetSectionToVRAM(p->dest, p->src, t, 1);
}

void WriteTileFromAnimBuffer(uint8_t* de){
//  Save the stack pointer in bc for WriteTile to restore
    // LD_HL_SP(0);
    // LD_B_H;
    // LD_C_L;

//  Write the tile graphic from wTileAnimBuffer (now sp) to de (now hl)
    // LD_HL(wTileAnimBuffer);
    // LD_SP_HL;
    // LD_H_D;
    // LD_L_E;
    // JR(mWriteTile);
    WriteTile(de, wram->wTileAnimBuffer);
}

void ReadTileToAnimBuffer(uint8_t* de){
//  Save the stack pointer in bc for WriteTile to restore
    // LD_HL_SP(0);
    // LD_B_H;
    // LD_C_L;

//  Write the tile graphic from de (now sp) to wTileAnimBuffer (now hl)
    // LD_H_D;
    // LD_L_E;
    // LD_SP_HL;
    // LD_HL(wTileAnimBuffer);
// fallthrough

    return WriteTile(wram->wTileAnimBuffer, de);
}

//  Write one tile from sp to hl.
//  Unlike the original version, this just uses CopyBytes.
void WriteTile(uint8_t* hl, const uint8_t* sp){
    // POP_DE;
    // LD_hl_E;
    // INC_HL;
    // LD_hl_D;
    // for(int rept = 0; rept < (LEN_2BPP_TILE - 2) / 2; rept++){
    // POP_DE;
    // INC_HL;
    // LD_hl_E;
    // INC_HL;
    // LD_hl_D;
    // }

//  Restore the stack pointer from bc
    // LD_H_B;
    // LD_L_C;
    // LD_SP_HL;
    // RET;
    return CopyBytes(hl, sp, LEN_2BPP_TILE);
}

//  Transition between color values 0-2 for color 0 in palette 3.
void AnimateWaterPalette(uint8_t* de){
    (void)de;
//  Don't update the palette on DMG
    // LDH_A_addr(hCGB);
    // AND_A_A;
    // RET_Z ;
    if(hram.hCGB == 0)
        return;

//  Don't update a non-standard palette order
    // LDH_A_addr(rBGP);
    // CP_A(0b11100100);
    // RET_NZ ;
    if(gb_read(rBGP) != 0b11100100)
        return;

//  Only update on even ticks
    // LD_A_addr(wTileAnimationTimer);
    // LD_L_A;
    uint8_t l = wram->wTileAnimationTimer;
    // AND_A(1);  // odd
    // RET_NZ ;
    if(l & 1)
        return;

//  Ready for BGPD input
    // LD_A((1 << rBGPI_AUTO_INCREMENT) + PALETTE_SIZE * PAL_BG_WATER + PAL_COLOR_SIZE * 0);
    // LDH_addr_A(rBGPI);
    gb_write(rBGPI, (1 << rBGPI_AUTO_INCREMENT) + PALETTE_SIZE * PAL_BG_WATER + PAL_COLOR_SIZE * 0);

    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    // LD_A(BANK(wBGPals1));
    // LDH_addr_A(rSVBK);

//  A cycle of 4 colors (0 1 2 1), updating every other tick
    // LD_A_L;
    // AND_A(0b110);
    // IF_Z goto color0;
    if((l & 0b110) == 0) {
    // color0:
        // LD_HL(wBGPals1 + PALETTE_SIZE * PAL_BG_WATER + PAL_COLOR_SIZE * 0);
        // LD_A_hli;
        // LDH_addr_A(rBGPD);
        gb_write(rBGPD, wram->wBGPals1[PALETTE_SIZE * PAL_BG_WATER + PAL_COLOR_SIZE * 0]);
        // LD_A_hli;
        // LDH_addr_A(rBGPD);
        gb_write(rBGPD, wram->wBGPals1[PALETTE_SIZE * PAL_BG_WATER + PAL_COLOR_SIZE * 0 + 1]);
        // goto end;
    }
    // CP_A(0b100);
    // IF_Z goto color2;
    else if((l & 0b110) == 0b100) {
    // color2:
        // LD_HL(wBGPals1 + PALETTE_SIZE * PAL_BG_WATER + PAL_COLOR_SIZE * 2);
        // LD_A_hli;
        // LDH_addr_A(rBGPD);
        gb_write(rBGPD, wram->wBGPals1[PALETTE_SIZE * PAL_BG_WATER + PAL_COLOR_SIZE * 2]);
        // LD_A_hli;
        // LDH_addr_A(rBGPD);
        gb_write(rBGPD, wram->wBGPals1[PALETTE_SIZE * PAL_BG_WATER + PAL_COLOR_SIZE * 2 + 1]);
    }
//  Copy one color from hl to rBGPI via rBGPD
    else {
    //  color1
        // LD_HL(wBGPals1 + PALETTE_SIZE * PAL_BG_WATER + PAL_COLOR_SIZE * 1);
        // LD_A_hli;
        // LDH_addr_A(rBGPD);
        gb_write(rBGPD, wram->wBGPals1[PALETTE_SIZE * PAL_BG_WATER + PAL_COLOR_SIZE * 1]);
        // LD_A_hli;
        // LDH_addr_A(rBGPD);
        gb_write(rBGPD, wram->wBGPals1[PALETTE_SIZE * PAL_BG_WATER + PAL_COLOR_SIZE * 1 + 1]);
        // goto end;
    }

// end:
    // POP_AF;
    // LDH_addr_A(rSVBK);
    // RET;
}

void FlickeringCaveEntrancePalette(uint8_t* de){
    (void)de;
//  Don't update the palette on DMG
    // LDH_A_addr(hCGB);
    // AND_A_A;
    // RET_Z ;
    if(hram.hCGB == 0)
        return;

//  Don't update a non-standard palette order
    // LDH_A_addr(rBGP);
    // CP_A(0b11100100);
    // RET_NZ ;
    if(gb_read(rBGP) != 0b11100100)
        return;

//  We only want to be here if we're in a dark cave.
    // LD_A_addr(wTimeOfDayPalset);
    // CP_A(DARKNESS_PALSET);
    // RET_NZ ;
    if(wram->wTimeOfDayPalset != DARKNESS_PALSET)
        return;

    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    // LD_A(BANK(wBGPals1));
    // LDH_addr_A(rSVBK);

//  Ready for BGPD input
    // LD_A((1 << rBGPI_AUTO_INCREMENT) + PALETTE_SIZE * PAL_BG_YELLOW + PAL_COLOR_SIZE * 0);
    // LDH_addr_A(rBGPI);
    gb_write(rBGPI, (1 << rBGPI_AUTO_INCREMENT) + PALETTE_SIZE * PAL_BG_YELLOW + PAL_COLOR_SIZE * 0);

//  A cycle of 2 colors (0 2), updating every other vblank
    // LDH_A_addr(hVBlankCounter);
    // AND_A(0b10);
    // IF_NZ goto color1;
    if((hram.hVBlankCounter & 0b10)) {
    // color1:
        // LD_HL(wBGPals1 + PALETTE_SIZE * PAL_BG_YELLOW + PAL_COLOR_SIZE * 1);
        gb_write(rBGPD, wram->wBGPals1[PALETTE_SIZE * PAL_BG_YELLOW + PAL_COLOR_SIZE * 1 + 0]);
        gb_write(rBGPD, wram->wBGPals1[PALETTE_SIZE * PAL_BG_YELLOW + PAL_COLOR_SIZE * 1 + 1]);
    }
    else {
    //  Copy one color from hl to rBGPI via rBGPD

    //  color0
        // LD_HL(wBGPals1 + PALETTE_SIZE * PAL_BG_YELLOW + PAL_COLOR_SIZE * 0);
        gb_write(rBGPD, wram->wBGPals1[PALETTE_SIZE * PAL_BG_YELLOW + PAL_COLOR_SIZE * 0 + 0]);
        gb_write(rBGPD, wram->wBGPals1[PALETTE_SIZE * PAL_BG_YELLOW + PAL_COLOR_SIZE * 0 + 1]);
        // goto okay;
    }


// okay:
    // LD_A_hli;
    // LDH_addr_A(rBGPD);
    // LD_A_hli;
    // LDH_addr_A(rBGPD);

    // POP_AF;
    // LDH_addr_A(rSVBK);
    // RET;
}
