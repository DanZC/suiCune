#include "../../constants.h"
#include "title.h"
#include "../../home/tilemap.h"
#include "../../home/clear_sprites.h"
#include "../../home/text.h"
#include "../../home/lcd.h"
#include "../../home/copy.h"
#include "../../home/audio.h"

static const char TitleSuicuneGFX[] = "gfx/title/suicune.png";
static const char TitleLogoGFX[] = "gfx/title/logo.png";
static const char TitleCrystalGFX[] = "gfx/title/crystal.png";

static const uint16_t TitleScreenPalettes[] = {
// INCLUDE "gfx/title/title.pal"
// BG
	rgb( 0,  0,  0),
	rgb(19,  0,  0),
	rgb(15,  8, 31),
	rgb(15,  8, 31),

	rgb( 0,  0,  0),
	rgb(31, 31, 31),
	rgb(15, 16, 31),
	rgb(31,  1, 13),

	rgb( 0,  0,  0),
	rgb( 7,  7,  7),
	rgb(31, 31, 31),
	rgb(02,  3, 30),

	rgb(00, 00, 00),
	rgb(13, 13, 13),
	rgb(31, 31, 18),
	rgb(02, 03, 30),

	rgb(00, 00, 00),
	rgb(19, 19, 19),
	rgb(29, 28, 12),
	rgb(02, 03, 30),

	rgb(00, 00, 00),
	rgb(25, 25, 25),
	rgb(28, 25, 06),
	rgb(02, 03, 30),

	rgb(00, 00, 00),
	rgb(31, 31, 31),
	rgb(26, 21, 00),
	rgb(02, 03, 30),

	rgb(00, 00, 00),
	rgb(11, 11, 19),
	rgb(31, 31, 31),
	rgb(00, 00, 00),

// OBJ
	rgb(00, 00, 00),
	rgb(10, 00, 15),
	rgb(17, 05, 22),
	rgb(19,  9, 31),

	rgb(31, 31, 31),
	rgb(00, 00, 00),
	rgb(00, 00, 00),
	rgb(00, 00, 00),

	rgb(31, 31, 31),
	rgb(00, 00, 00),
	rgb(00, 00, 00),
	rgb(00, 00, 00),

	rgb(31, 31, 31),
	rgb(00, 00, 00),
	rgb(00, 00, 00),
	rgb(00, 00, 00),

	rgb(31, 31, 31),
	rgb(00, 00, 00),
	rgb(00, 00, 00),
	rgb(00, 00, 00),

	rgb(31, 31, 31),
	rgb(00, 00, 00),
	rgb(00, 00, 00),
	rgb(00, 00, 00),

	rgb(31, 31, 31),
	rgb(00, 00, 00),
	rgb(00, 00, 00),
	rgb(00, 00, 00),

	rgb(31, 31, 31),
	rgb(00, 00, 00),
	rgb(00, 00, 00),
	rgb(00, 00, 00),
};

void v_TitleScreen(void){
    // CALL(aClearBGPalettes);
    ClearBGPalettes_Conv();
    // CALL(aClearSprites);
    ClearSprites();
    // CALL(aClearTilemap);
    ClearTilemap_Conv2();

//  Turn BG Map update off
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = BGMAPMODE_NONE;

//  Reset timing variables
    // LD_HL(wJumptableIndex);
    // LD_hli_A;  // wJumptableIndex
    wram->wJumptableIndex = 0;
    // LD_hli_A;  // wTitleScreenSelectedOption
    wram->wTitleScreenSelectedOption = 0;
    // LD_hli_A;  // wTitleScreenTimer
    // LD_hl_A;  // wTitleScreenTimer + 1
    wram->wTitleScreenTimer = 0;

//  Turn LCD off
    // CALL(aDisableLCD);
    DisableLCD();

//  VRAM bank 1
    // LD_A(1);
    // LDH_addr_A(rVBK);

//  Decompress running Suicune gfx
    // LD_HL(mTitleSuicuneGFX);
    // LD_DE(vTiles1);
    // CALL(aDecompress);
    LoadPNG2bppAssetToVRAM(vram->vTiles4, TitleSuicuneGFX);

//  Clear screen palettes
    // hlbgcoord(0, 0, vBGMap0);
    // LD_BC(20 * BG_MAP_WIDTH);
    // XOR_A_A;
    // CALL(aByteFill);
    ByteFill(bgcoord(0, 0, vram->vBGMap2), 20 * BG_MAP_WIDTH, 0);

//  Fill tile palettes:

//  BG Map 1:

//  line 0 (copyright)
    // hlbgcoord(0, 0, vBGMap1);
    // LD_BC(BG_MAP_WIDTH);
    // LD_A(7);  // palette
    // CALL(aByteFill);
    ByteFill(bgcoord(0, 0, vram->vBGMap3), BG_MAP_WIDTH, 7);

//  BG Map 0:

//  Apply logo gradient:

//  lines 3-4
    // hlbgcoord(0, 3, vBGMap0);
    // LD_BC(2 * BG_MAP_WIDTH);
    // LD_A(2);
    // CALL(aByteFill);
    ByteFill(bgcoord(0, 3, vram->vBGMap2), 2 * BG_MAP_WIDTH, 2);
//  line 5
    // hlbgcoord(0, 5, vBGMap0);
    // LD_BC(BG_MAP_WIDTH);
    // LD_A(3);
    // CALL(aByteFill);
    ByteFill(bgcoord(0, 5, vram->vBGMap2), BG_MAP_WIDTH, 3);
//  line 6
    // hlbgcoord(0, 6, vBGMap0);
    // LD_BC(BG_MAP_WIDTH);
    // LD_A(4);
    // CALL(aByteFill);
    ByteFill(bgcoord(0, 6, vram->vBGMap2), BG_MAP_WIDTH, 4);
//  line 7
    // hlbgcoord(0, 7, vBGMap0);
    // LD_BC(BG_MAP_WIDTH);
    // LD_A(5);
    // CALL(aByteFill);
    ByteFill(bgcoord(0, 7, vram->vBGMap2), BG_MAP_WIDTH, 5);
//  lines 8-9
    // hlbgcoord(0, 8, vBGMap0);
    // LD_BC(2 * BG_MAP_WIDTH);
    // LD_A(6);
    // CALL(aByteFill);
    ByteFill(bgcoord(0, 8, vram->vBGMap2), 2 * BG_MAP_WIDTH, 6);

//  'CRYSTAL VERSION'
    // hlbgcoord(5, 9, vBGMap0);
    // LD_BC(11);  // length of version text
    // LD_A(1);
    // CALL(aByteFill);
    ByteFill(bgcoord(5, 9, vram->vBGMap2), 11, 1);

//  Suicune gfx
    // hlbgcoord(0, 12, vBGMap0);
    // LD_BC(6 * BG_MAP_WIDTH);  // the rest of the screen
    // LD_A(0 | VRAM_BANK_1);
    // CALL(aByteFill);
    ByteFill(bgcoord(0, 12, vram->vBGMap2), 6 * BG_MAP_WIDTH, 0 | VRAM_BANK_1);

//  Back to VRAM bank 0
    // LD_A(0);
    // LDH_addr_A(rVBK);

//  Decompress logo
    // LD_HL(mTitleLogoGFX);
    // LD_DE(vTiles1);
    // CALL(aDecompress);
    LoadPNG2bppAssetToVRAM(vram->vTiles1, TitleLogoGFX);

//  Decompress background crystal
    // LD_HL(mTitleCrystalGFX);
    // LD_DE(vTiles0);
    // CALL(aDecompress);
    LoadPNG2bppAssetToVRAMByColumn(vram->vTiles0, TitleCrystalGFX);

//  Clear screen tiles
    // hlbgcoord(0, 0, vBGMap0);
    // LD_BC(64 * BG_MAP_WIDTH);
    // LD_A(0x7f);
    // CALL(aByteFill);
    ByteFill(bgcoord(0, 0, vram->vBGMap0), 64 * BG_MAP_WIDTH, 0x7f);

//  Draw Pokemon logo
    // hlcoord(0, 3, wTilemap);
    // LD_BC((7 << 8) | 20);
    // LD_D(0x80);
    // LD_E(20);
    // CALL(aDrawTitleGraphic);
    DrawTitleGraphic_Conv(coord(0, 3, wram->wTilemap), 7, 20, 0x80, 20);

//  Draw copyright text
    // hlbgcoord(3, 0, vBGMap1);
    // LD_BC((1 << 8) | 13);
    // LD_D(0xc);
    // LD_E(16);
    // CALL(aDrawTitleGraphic);
    // DrawTitleGraphic_Conv(bgcoord(3, 0, vram->vBGMap1), 1, 13, 0xc, 16);
    DrawTitleGraphic_Conv(bgcoord(3, 0, vram->vBGMap1), 1, 13, 0xc, 16);

//  Initialize running Suicune?
    // LD_D(0x0);
    // CALL(aLoadSuicuneFrame);
    LoadSuicuneFrame_Conv(0x0);

//  Initialize background crystal
    // CALL(aInitializeBackground);
    InitializeBackground_Conv();

//  Update palette colors
    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    // LD_A(BANK(wBGPals1));
    // LDH_addr_A(rSVBK);

    // LD_HL(mTitleScreenPalettes);
    // LD_DE(wBGPals1);
    // LD_BC(16 * PALETTE_SIZE);
    // CALL(aCopyBytes);
    CopyBytes(wram->wBGPals1, TitleScreenPalettes, 16 * PALETTE_SIZE);

    // LD_HL(mTitleScreenPalettes);
    // LD_DE(wBGPals2);
    // LD_BC(16 * PALETTE_SIZE);
    // CALL(aCopyBytes);
    CopyBytes(wram->wBGPals2, TitleScreenPalettes, 16 * PALETTE_SIZE);

    // POP_AF;
    // LDH_addr_A(rSVBK);

//  LY/SCX trickery starts here

    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    // LD_A(BANK(wLYOverrides));
    // LDH_addr_A(rSVBK);

//  Make alternating lines come in from opposite sides

//  (This part is actually totally pointless, you can't
//   see anything until these values are overwritten!)

    // LD_B(80 / 2);  // alternate for 80 lines
    // LD_HL(wLYOverrides);

    for(uint8_t b = 0; b < 80; b += 2) {
    // loop:
    //  $00 is the middle position
        // LD_hl(+112);  // coming from the left
        // INC_HL;
        wram->wLYOverrides[b] = +112;
        // LD_hl(-112);  // coming from the right
        // INC_HL;
        wram->wLYOverrides[b + 1] = -112;
        // DEC_B;
        // IF_NZ goto loop;
    }

//  Make sure the rest of the buffer is empty
    // LD_HL(wLYOverrides + 80);
    // XOR_A_A;
    // LD_BC(wLYOverridesEnd - (wLYOverrides + 80));
    // CALL(aByteFill);
    ByteFill(wram->wLYOverrides + 80, sizeof(wram->wLYOverrides) - 80, 0);

//  Let LCD Stat know we're messing around with SCX
    // LD_A(LOW(rSCX));
    // LDH_addr_A(hLCDCPointer);
    hram->hLCDCPointer = LOW(rSCX);

    // POP_AF;
    // LDH_addr_A(rSVBK);

//  Reset audio
    // CALL(aChannelsOff);
    ChannelsOff();
    // CALL(aEnableLCD);
    EnableLCD();

//  Set sprite size to 8x16
    // LDH_A_addr(rLCDC);
    // SET_A(rLCDC_SPRITE_SIZE);
    // LDH_addr_A(rLCDC);
    gb_write(rLCDC, gb_read(rLCDC) | (1 << rLCDC_SPRITE_SIZE));

    // LD_A(+112);
    // LDH_addr_A(hSCX);
    hram->hSCX = +112;
    // LD_A(8);
    // LDH_addr_A(hSCY);
    hram->hSCY = 8;
    // LD_A(7);
    // LDH_addr_A(hWX);
    hram->hWX = 7;
    // LD_A(-112);
    // LDH_addr_A(hWY);
    hram->hWY = -112;

    // LD_A(TRUE);
    // LDH_addr_A(hCGBPalUpdate);
    hram->hCGBPalUpdate = TRUE;

//  Update BG Map 0 (bank 0)
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = BGMAPMODE_UPDATE_TILES;

    // XOR_A_A;
    // LD_addr_A(wSuicuneFrame);
    wram->wSuicuneFrame = 0;

//  Play starting sound effect
    // CALL(aSFXChannelsOff);
    SFXChannelsOff();
    // LD_DE(SFX_TITLE_SCREEN_ENTRANCE);
    // CALL(aPlaySFX);
    PlaySFX(SFX_TITLE_SCREEN_ENTRANCE);

    // RET;
}

void SuicuneFrameIterator(void){
    LD_HL(wSuicuneFrame);
    LD_A_hl;
    LD_C_A;
    INC_hl;

//  Only do this once every eight frames
    AND_A(0b111);
    RET_NZ ;

    LD_A_C;
    AND_A(0b11000);
    SLA_A;
    SWAP_A;
    LD_E_A;
    LD_D(0);
    LD_HL(mSuicuneFrameIterator_Frames);
    ADD_HL_DE;
    LD_D_hl;
    XOR_A_A;
    LDH_addr_A(hBGMapMode);
    CALL(aLoadSuicuneFrame);
    LD_A(0x1);
    LDH_addr_A(hBGMapMode);
    LD_A(0x3);
    LDH_addr_A(hBGMapThird);
    RET;


Frames:
    //db ['0x80'];  // vTiles3 tile $80
    //db ['0x88'];  // vTiles3 tile $88
    //db ['0x00'];  // vTiles5 tile $00
    //db ['0x08'];  // vTiles5 tile $08

    return LoadSuicuneFrame();
}

void SuicuneFrameIterator_Conv(void){
    static const uint8_t Frames[] = {
        0x80,  // vTiles3 tile $80
        0x88,  // vTiles3 tile $88
        0x00,  // vTiles5 tile $00
        0x08,  // vTiles5 tile $08
    };
    // LD_HL(wSuicuneFrame);
    // LD_A_hl;
    // LD_C_A;
    // INC_hl;
    uint8_t a = wram->wSuicuneFrame++;

//  Only do this once every eight frames
    // AND_A(0b111);
    // RET_NZ ;
    if(a & 0b111)
        return;

    // LD_A_C;
    // AND_A(0b11000);
    // SLA_A;
    // SWAP_A;
    // LD_E_A;
    // LD_D(0);
    // LD_HL(mSuicuneFrameIterator_Frames);
    // ADD_HL_DE;
    // LD_D_hl;
    uint8_t d = Frames[((a & 0b11000) << 1) >> 4];
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = BGMAPMODE_NONE;
    // CALL(aLoadSuicuneFrame);
    LoadSuicuneFrame_Conv(d);
    // LD_A(0x1);
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = BGMAPMODE_UPDATE_TILES;
    // LD_A(0x3);
    // LDH_addr_A(hBGMapThird);
    hram->hBGMapThird = 0x3;
    // RET;
}

void LoadSuicuneFrame(void){
    hlcoord(6, 12, wTilemap);
    LD_B(6);

bgrows:
    LD_C(8);

col:
    LD_A_D;
    LD_hli_A;
    INC_D;
    DEC_C;
    IF_NZ goto col;
    LD_A(SCREEN_WIDTH - 8);
    ADD_A_L;
    LD_L_A;
    LD_A(0);
    ADC_A_H;
    LD_H_A;
    LD_A(8);
    ADD_A_D;
    LD_D_A;
    DEC_B;
    IF_NZ goto bgrows;
    RET;

}

void LoadSuicuneFrame_Conv(uint8_t d){
    // hlcoord(6, 12, wTilemap);
    uint8_t* hl = coord(6, 12, wram->wTilemap);
    // LD_B(6);
    uint8_t b = 6;

    do {
    // bgrows:
        // LD_C(8);
        uint8_t c = 8;

        do {
        // col:
            // LD_A_D;
            // LD_hli_A;
            *(hl++) = d++;
            // INC_D;
            // DEC_C;
            // IF_NZ goto col;
        } while(--c != 0);
        // LD_A(SCREEN_WIDTH - 8);
        // ADD_A_L;
        // LD_L_A;
        // LD_A(0);
        // ADC_A_H;
        // LD_H_A;
        hl += SCREEN_WIDTH - 8;
        // LD_A(8);
        // ADD_A_D;
        // LD_D_A;
        d += 8;
        // DEC_B;
        // IF_NZ goto bgrows;
    } while(--b != 0);
    // RET;
}

void DrawTitleGraphic(void){
//  input:
//    hl: draw location
//    b: height
//    c: width
//    d: tile to start drawing from
//    e: number of tiles to advance for each bgrows

bgrows:
    PUSH_DE;
    PUSH_BC;
    PUSH_HL;

col:
    LD_A_D;
    LD_hli_A;
    INC_D;
    DEC_C;
    IF_NZ goto col;
    POP_HL;
    LD_BC(SCREEN_WIDTH);
    ADD_HL_BC;
    POP_BC;
    POP_DE;
    LD_A_E;
    ADD_A_D;
    LD_D_A;
    DEC_B;
    IF_NZ goto bgrows;
    RET;

}

//  input:
//    hl: draw location
//    b: height
//    c: width
//    d: tile to start drawing from
//    e: number of tiles to advance for each bgrows
void DrawTitleGraphic_Conv(uint8_t* hl, uint8_t b, uint8_t c, uint8_t d, uint8_t e){
    do {
    // bgrows:
        // PUSH_DE;
        uint8_t d2 = d;
        // PUSH_BC;
        uint8_t c2 = c;
        // PUSH_HL;
        uint8_t* hl2 = hl;

        do {
        // col:
            // LD_A_D;
            // LD_hli_A;
            *(hl++) = d;
            // INC_D;
            d++;
            // DEC_C;
            // IF_NZ goto col;
        } while(--c != 0);
        // POP_HL;
        // LD_BC(SCREEN_WIDTH);
        // ADD_HL_BC;
        hl = hl2 + SCREEN_WIDTH;
        // POP_BC;
        c = c2;
        // POP_DE;
        // LD_A_E;
        // ADD_A_D;
        // LD_D_A;
        d = d2 + e;
        // DEC_B;
        // IF_NZ goto bgrows;
    } while(--b != 0);
    // RET;
}

void InitializeBackground(void){
    LD_HL(wVirtualOAMSprite00);
    LD_D(-0x22);
    LD_E(0x0);
    LD_C(5);

loop:
    PUSH_BC;
    CALL(aInitializeBackground_InitColumn);
    POP_BC;
    LD_A(0x10);
    ADD_A_D;
    LD_D_A;
    DEC_C;
    IF_NZ goto loop;
    RET;


InitColumn:
    LD_C(0x6);
    LD_B(0x40);

loop2:
    LD_A_D;
    LD_hli_A;  // y
    LD_A_B;
    LD_hli_A;  // x
    ADD_A(0x8);
    LD_B_A;
    LD_A_E;
    LD_hli_A;  // tile id
    INC_E;
    INC_E;
    LD_A(0 | PRIORITY);
    LD_hli_A;  // attributes
    DEC_C;
    IF_NZ goto loop2;
    RET;

}

static void InitializeBackground_InitColumn(struct SpriteOAM* hl, uint8_t d, uint8_t e) {
    // LD_C(0x6);
    // LD_B(0x40);
    uint8_t b = 0x40;

    for(uint8_t c = 0; c < 0x6; ++c) {
    // loop2:
        // LD_A_D;
        // LD_hli_A;  // y
        hl[c].yCoord = d;
        // LD_A_B;
        // LD_hli_A;  // x
        hl[c].xCoord = b;
        // ADD_A(0x8);
        // LD_B_A;
        b += 0x8;
        // LD_A_E;
        // LD_hli_A;  // tile id
        hl[c].tileID = e;
        // INC_E;
        // INC_E;
        e += 10;
        // LD_A(0 | PRIORITY);
        // LD_hli_A;  // attributes
        hl[c].attributes = (0 | PRIORITY);
        // DEC_C;
        // IF_NZ goto loop2;
    }
    // RET;
}

void InitializeBackground_Conv(void){
    // LD_HL(wVirtualOAMSprite00);
    struct SpriteOAM* hl = wram->wVirtualOAMSprite;
    // LD_D(-0x22);
    uint8_t d = -0x22;
    // LD_E(0x0);
    // LD_C(5);

    for(uint8_t c = 0; c < 5; ++c) {
    // loop:
        // PUSH_BC;
        // CALL(aInitializeBackground_InitColumn);
        InitializeBackground_InitColumn(hl + (0x6 * c), d, 2 * c);
        // POP_BC;
        // LD_A(0x10);
        // ADD_A_D;
        // LD_D_A;
        d += 0x10;
        // DEC_C;
        // IF_NZ goto loop;
    }
    // RET;

}

void AnimateTitleCrystal(void){
//  Move the title screen crystal downward until it's fully visible

//  Stop at y=6
//  y is really from the bottom of the sprite, which is two tiles high
    LD_HL(wVirtualOAMSprite00YCoord);
    LD_A_hl;
    CP_A(6 + 2 * TILE_WIDTH);
    RET_Z ;

//  Move all 30 parts of the crystal down by 2
    LD_C(30);

loop:
    LD_A_hl;
    ADD_A(2);
    LD_hli_A;  // y
    for(int rept = 0; rept < SPRITEOAMSTRUCT_LENGTH - 1; rept++){
    INC_HL;
    }
    DEC_C;
    IF_NZ goto loop;

    RET;

}

//  Move the title screen crystal downward until it's fully visible
void AnimateTitleCrystal_Conv(void){
//  Stop at y=6
//  y is really from the bottom of the sprite, which is two tiles high
    // LD_HL(wVirtualOAMSprite00YCoord);
    struct SpriteOAM* hl = wram->wVirtualOAMSprite;
    // LD_A_hl;
    // CP_A(6 + 2 * TILE_WIDTH);
    // RET_Z ;
    if(hl->yCoord == 6 + 2 * TILE_WIDTH)
        return;

//  Move all 30 parts of the crystal down by 2
    // LD_C(30);

    for(uint8_t c = 0; c < 30; ++c) {
    // loop:
        // LD_A_hl;
        // ADD_A(2);
        // LD_hli_A;  // y
        hl[c].yCoord += 2;
        // for(int rept = 0; rept < SPRITEOAMSTRUCT_LENGTH - 1; rept++){
        // INC_HL;
        // }
        // DEC_C;
        // IF_NZ goto loop;
    }

    // RET;
}
