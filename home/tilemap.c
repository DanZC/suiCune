#include "../constants.h"
#include "tilemap.h"
#include "copy.h"
#include "palettes.h"
#include "delay.h"
#include "../engine/gfx/cgb_layouts.h"

void ClearBGPalettes(void) {
    // CALL(aClearPalettes);
    ClearPalettes();

    return WaitBGMap(); // Maybe not necessary in C?
}

void WaitBGMap(void) {
    //  Tell VBlank to update BG Map
    // LD_A(1);  // BG Map 0 tiles
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = BGMAPMODE_UPDATE_TILES;  // BG Map 0 tiles 

    //  Wait for it to do its magic
    // LD_C(4);
    // CALL(aDelayFrames);
#if ENHANCEMENT_DRAW_BG_IN_ONE_FRAME
    DelayFrame();
#else
    DelayFrames(4);
#endif
}

void WaitBGMap2(void) {
    // SET_PC(aWaitBGMap2);
    // LDH_A_addr(hCGB);
    // AND_A_A;
    // IF_Z goto bg0;
    if(hram->hCGB != 0) {
        // LD_A(2);
        // LDH_addr_A(hBGMapMode);
        hram->hBGMapMode = BGMAPMODE_UPDATE_ATTRS;
        // LD_C(4);
        // CALL(aDelayFrames);
#if ENHANCEMENT_DRAW_BG_IN_ONE_FRAME
        DelayFrame();
#else
        DelayFrames(4);
#endif
    }
// bg0:
    // LD_A(1);
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = BGMAPMODE_UPDATE_TILES;
    // LD_C(4);
    // CALL(aDelayFrames);
#if ENHANCEMENT_DRAW_BG_IN_ONE_FRAME
    DelayFrame();
#else
    DelayFrames(4);
#endif
    // RET;
}

bool IsCGB(void){
    return hram->hCGB == 1;
}

void ApplyTilemap(void) {
    if(hram->hCGB == 0 || wram->wSpriteUpdatesEnabled == 0) {
        //  WaitBGMap
        hram->hBGMapMode = BGMAPMODE_UPDATE_TILES;
        // LD_C(4);
        // CALL(aDelayFrames);
#if ENHANCEMENT_DRAW_BG_IN_ONE_FRAME
        DelayFrame();
#else
        DelayFrames(4);
#endif
        return;
    }
    else {
        hram->hBGMapMode = BGMAPMODE_UPDATE_TILES;
        // JR(mCopyTilemapAtOnce);
        return CopyTilemapAtOnce();
    }
}

void CGBOnly_CopyTilemapAtOnce(void) {
    // SET_PC(aCGBOnly_CopyTilemapAtOnce);
    // LDH_A_addr(hCGB);
    // AND_A_A;
    // JR_Z(mWaitBGMap);
    if(hram->hCGB == 0)
        return WaitBGMap();

    return CopyTilemapAtOnce();
}

void CopyTilemapAtOnce(void) {
    return v_CopyTilemapAtOnce();
}

void CopyAttrmapAndTilemapToWRAMBank3(void) {
    SET_PC(aCopyAttrmapAndTilemapToWRAMBank3);
    //  //  unreferenced
    FARCALL(aHDMATransferAttrmapAndTilemapToWRAMBank3);
    RET;
}

void v_CopyTilemapAtOnce(void) {
    uint8_t bg_map_mode = hram->hBGMapMode;
    hram->hBGMapMode = BGMAPMODE_NONE;
    uint8_t map_anims = hram->hMapAnims;
    hram->hMapAnims = 0;

    // In C we don't wait.
    // wait:
    // LDH_A_addr(rLY);
    // CP_A(0x80 - 1);
    // IF_C goto wait;

    gb_write(rVBK, MBANK(avBGMap2));
    v_CopyTilemapAtOnce_CopyBGMapViaStack(coord(0, 0, wram->wAttrmap));

    gb_write(rVBK, MBANK(avBGMap0));
    v_CopyTilemapAtOnce_CopyBGMapViaStack(coord(0, 0, wram->wTilemap));

    // wait2:
    // LDH_A_addr(rLY);
    // CP_A(0x80 - 1);
    // IF_C goto wait2;
    DelayFrame();

    hram->hMapAnims = map_anims;
    hram->hBGMapMode = bg_map_mode;
}

//  Copy all tiles to vBGMap
void v_CopyTilemapAtOnce_CopyBGMapViaStack(const tile_t* sp) {
    tile_t* hl = GBToRAMAddr(hram->hBGMapAddress & 0xff00);
    hram->hTilesPerCycle = SCREEN_HEIGHT;
    // uint8_t b = 1 << 1;
    // uint8_t c = LOW(rSTAT);
    uint8_t a = SCREEN_HEIGHT;
    do {
        for (int rept = 0; rept < SCREEN_WIDTH / 2; rept++) {
            tile_t e = *(sp++);
            tile_t d = *(sp++);
            //  if in v/hblank, wait until not in v/hblank
            // LDH_A_c;
            // AND_A_B;
            // IF_NZ goto loop\@;
            //  load vBGMap

            *(hl++) = e;
            *(hl++) = d;
        }
        hl += (BG_MAP_WIDTH - SCREEN_WIDTH);
    } while(--a != 0);
    hram->hTilesPerCycle = 0;
}

//  Inits the Palettes
//  depending on the system the monochromes palettes or color palettes
void SetPalettes(void) {
    // LDH_A_addr(hCGB);
    // AND_A_A;
    // IF_NZ goto SetPalettesForGameBoyColor;
    if(hram->hCGB != 0)
    {
        // PUSH_DE;
        // LD_A(0b11100100);
        // CALL(aDmgToCgbBGPals);
        DmgToCgbBGPals(0b11100100);

        // LD_DE((0b11100100 << 8) | 0b11100100);
        // CALL(aDmgToCgbObjPals);
        DmgToCgbObjPals(0b11100100, 0b11100100);
        
        // POP_DE;
        return;
    }

    // LD_A(0b11100100);
    // LDH_addr_A(rBGP);
    gb_write(rBGP, 0b11100100);

    // LD_A(0b11010000);
    // LDH_addr_A(rOBP0);
    // LDH_addr_A(rOBP1);
    gb_write(rOBP0, 0b11010000);
    gb_write(rOBP1, 0b11010000);
}

//  Make all palettes white
void ClearPalettes(void) {
    // LDH_A_addr(hCGB);
    // AND_A_A;
    // IF_NZ goto cgb;
    if(hram->hCGB != 0)
    {
        //  CGB: make all the palette colors white
        // LDH_A_addr(rSVBK);
        // PUSH_AF;

        // LD_A(MBANK(awBGPals2));
        // LDH_addr_A(rSVBK);

        //  Fill wBGPals2 and wOBPals2 with $ffff (white)
        // LD_HL(wBGPals2);
        // LD_BC(16 * PALETTE_SIZE);
        // LD_A(0xff);
        // CALL(aByteFill);
        ByteFill(wram->wBGPals2, (16 * PALETTE_SIZE), 0xff);

        // POP_AF;
        // LDH_addr_A(rSVBK);

        //  Request palette update
        // LD_A(TRUE);
        // LDH_addr_A(hCGBPalUpdate);
        hram->hCGBPalUpdate = TRUE;

        // RET;
        return;
    }

//  DMG: just change palettes to 0 (white)
    // XOR_A_A;
    // LDH_addr_A(rBGP);
    // LDH_addr_A(rOBP0);
    // LDH_addr_A(rOBP1);
    gb_write(rBGP, 0);
    gb_write(rOBP0, 0);
    gb_write(rOBP1, 0);
}

void GetMemSGBLayout(void) {
    // LD_B(SCGB_DEFAULT);
    // return GetSGBLayout();
    return GetSGBLayout(SCGB_DEFAULT);
}

//  load sgb packets unless dmg
void GetSGBLayout(uint8_t b) {
    // LDH_A_addr(hCGB);
    // AND_A_A;
    // IF_NZ goto sgb;
    if(hram->hCGB != 0) {
        // PREDEF_JUMP(pLoadSGBLayout);
        LoadSGBLayoutCGB_Conv(b);
        return;
    }

    // LDH_A_addr(hSGB);
    // AND_A_A;
    // RET_Z;
    if(hram->hSGB == 0)
        return;

    // PREDEF_JUMP(pLoadSGBLayout);
}

//  Set palette for hp bar pixel length e at hl.
void SetHPPal(uint8_t* hl, uint8_t e) {
    // SET_PC(aSetHPPal);
    // CALL(aGetHPPal);
    // LD_hl_D;
    // RET;
    *hl = GetHPPal(e);
}

//  Get palette for hp bar pixel length e in d.
uint8_t GetHPPal(uint8_t e) {
    // LD_D(HP_GREEN);
    // LD_A_E;
    // CP_A((HP_BAR_LENGTH_PX * 50 / 100));  // 24
    // RET_NC;
    if(e >= (HP_BAR_LENGTH_PX * 50 / 100))
        return HP_GREEN;
    // INC_D;                                // HP_YELLOW
    // CP_A((HP_BAR_LENGTH_PX * 21 / 100));  // 10
    // RET_NC;
    else if(e >= (HP_BAR_LENGTH_PX * 21 / 100))
        return HP_YELLOW;
    // INC_D;  // HP_RED
    // RET;
    else
        return HP_RED;
}
