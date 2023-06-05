#include "../constants.h"
#include "tilemap.h"
#include "copy.h"
#include "palettes.h"
#include "delay.h"

void ClearBGPalettes(void) {
    SET_PC(aClearBGPalettes);
    CALL(aClearPalettes);
    return WaitBGMap();
}

void ClearBGPalettes_Conv(void) {
    // CALL(aClearPalettes);
    ClearPalettes_Conv();

    return WaitBGMap_Conv(); // Maybe not necessary in C?
}

void WaitBGMap(void) {
    SET_PC(aWaitBGMap);
    //  Tell VBlank to update BG Map
    LD_A(1);  // BG Map 0 tiles
    LDH_addr_A(hBGMapMode);
    //  Wait for it to do its magic
    LD_C(4);
    CALL(aDelayFrames);
    RET;
}

void WaitBGMap_Conv(void) {
    //  Tell VBlank to update BG Map
    // LD_A(1);  // BG Map 0 tiles
    // LDH_addr_A(hBGMapMode);
    gb_write(hBGMapMode, 1);  // BG Map 0 tiles 

    //  Wait for it to do its magic
    // LD_C(4);
    // CALL(aDelayFrames);
    DelayFrames_Conv(4);
}

void WaitBGMap2(void) {
    SET_PC(aWaitBGMap2);
    LDH_A_addr(hCGB);
    AND_A_A;
    IF_Z goto bg0;

    LD_A(2);
    LDH_addr_A(hBGMapMode);
    LD_C(4);
    CALL(aDelayFrames);

bg0:

    LD_A(1);
    LDH_addr_A(hBGMapMode);
    LD_C(4);
    CALL(aDelayFrames);
    RET;
}

void IsCGB(void) {
    SET_PC(aIsCGB);
    LDH_A_addr(hCGB);
    AND_A_A;
    RET;
}

bool IsCGB_Conv(void){
    return gb_read(hCGB) == 1;
}

void ApplyTilemap(void) {
    SET_PC(aApplyTilemap);
    LDH_A_addr(hCGB);
    AND_A_A;
    IF_Z goto dmg;

    LD_A_addr(wSpriteUpdatesEnabled);
    CP_A(0);
    IF_Z goto dmg;

    LD_A(1);
    LDH_addr_A(hBGMapMode);
    JR(mCopyTilemapAtOnce);

dmg:

    //  WaitBGMap
    LD_A(1);
    LDH_addr_A(hBGMapMode);
    LD_C(4);
    CALL(aDelayFrames);
    RET;
}

void ApplyTilemap_Conv(void) {
    if(gb_read(hCGB) == 0 || gb_read(wSpriteUpdatesEnabled) == 0) {
        //  WaitBGMap
        gb_write(hBGMapMode, 1);
        // LD_C(4);
        // CALL(aDelayFrames);
        DelayFrames_Conv(4);
    }

    gb_write(hBGMapMode, 1);
    // JR(mCopyTilemapAtOnce);
    return CopyTilemapAtOnce_Conv();
}

void CGBOnly_CopyTilemapAtOnce(void) {
    SET_PC(aCGBOnly_CopyTilemapAtOnce);
    LDH_A_addr(hCGB);
    AND_A_A;
    JR_Z(mWaitBGMap);

    return CopyTilemapAtOnce();
}

void CopyTilemapAtOnce(void) {
    SET_PC(aCopyTilemapAtOnce);
    JR(mv_CopyTilemapAtOnce);
}

void CopyTilemapAtOnce_Conv(void) {
    return v_CopyTilemapAtOnce_Conv();
}

void CopyAttrmapAndTilemapToWRAMBank3(void) {
    SET_PC(aCopyAttrmapAndTilemapToWRAMBank3);
    //  //  unreferenced
    FARCALL(aHDMATransferAttrmapAndTilemapToWRAMBank3);
    RET;
}

void v_CopyTilemapAtOnce(void) {
    SET_PC(av_CopyTilemapAtOnce);
    LDH_A_addr(hBGMapMode);
    PUSH_AF;
    XOR_A_A;
    LDH_addr_A(hBGMapMode);

    LDH_A_addr(hMapAnims);
    PUSH_AF;
    XOR_A_A;
    LDH_addr_A(hMapAnims);

wait:

    LDH_A_addr(rLY);
    CP_A(0x80 - 1);
    // IF_C goto wait;

    NOP;
    LD_A(MBANK(avBGMap2));
    LDH_addr_A(rVBK);
    hlcoord(0, 0, wAttrmap);
    CALL(av_CopyTilemapAtOnce_CopyBGMapViaStack);
    LD_A(MBANK(avBGMap0));
    LDH_addr_A(rVBK);
    hlcoord(0, 0, wTilemap);
    CALL(av_CopyTilemapAtOnce_CopyBGMapViaStack);

wait2:

    LDH_A_addr(rLY);
    CP_A(0x80 - 1);
    // IF_C goto wait2;
    NOP;

    POP_AF;
    LDH_addr_A(hMapAnims);
    POP_AF;
    LDH_addr_A(hBGMapMode);
    RET;
}

void v_CopyTilemapAtOnce_Conv(void) {
    uint8_t bg_map_mode = gb_read(hBGMapMode);
    gb_write(hBGMapMode, 0);

    uint8_t map_anims = gb_read(hMapAnims);
    gb_write(map_anims, 0);

    // In C we don't wait.
    // wait:
    // LDH_A_addr(rLY);
    // CP_A(0x80 - 1);
    // IF_C goto wait;

    gb_write(rVBK, MBANK(avBGMap2));
    v_CopyTilemapAtOnce_CopyBGMapViaStack_Conv(coord(0, 0, wAttrmap));

    gb_write(rVBK, MBANK(avBGMap0));
    v_CopyTilemapAtOnce_CopyBGMapViaStack_Conv(coord(0, 0, wTilemap));

    // In C we don't wait.
    // wait2:
    // LDH_A_addr(rLY);
    // CP_A(0x80 - 1);
    // IF_C goto wait2;

    gb_write(hMapAnims, map_anims);
    gb_write(hBGMapMode, bg_map_mode);
}

void v_CopyTilemapAtOnce_CopyBGMapViaStack(void) {
    //  Copy all tiles to vBGMap
    LD_addr_SP(hSPBuffer);
    LD_SP_HL;
    LDH_A_addr(hBGMapAddress + 1);
    LD_H_A;
    LD_L(0);
    LD_A(SCREEN_HEIGHT);
    LDH_addr_A(hTilesPerCycle);
    LD_B(1 << 1);  // not in v/hblank
    LD_C(LOW(rSTAT));

loop:

    for (int rept = 0; rept < SCREEN_WIDTH / 2; rept++) {
        POP_DE;
        //  if in v/hblank, wait until not in v/hblank
        LDH_A_c;
        AND_A_B;
        // IF_NZ goto loop\@;
        //  load vBGMap
        LD_hl_E;
        INC_L;
        LD_hl_D;
        INC_L;
    }

    LD_DE(BG_MAP_WIDTH - SCREEN_WIDTH);
    ADD_HL_DE;
    LDH_A_addr(hTilesPerCycle);
    DEC_A;
    LDH_addr_A(hTilesPerCycle);
    IF_NZ goto loop;

    LDH_A_addr(hSPBuffer);
    LD_L_A;
    LDH_A_addr(hSPBuffer + 1);
    LD_H_A;
    LD_SP_HL;
    RET;
}

void v_CopyTilemapAtOnce_CopyBGMapViaStack_Conv(uint16_t hl) {
    //  Copy all tiles to vBGMap
    uint16_t sp = hl;
    hl = gb_read(hBGMapAddress + 1);
    gb_write(hTilesPerCycle, SCREEN_HEIGHT);
    // uint8_t b = 1 << 1;
    // uint8_t c = LOW(rSTAT);
    uint8_t a = SCREEN_HEIGHT;
    do {
        for (int rept = 0; rept < SCREEN_WIDTH / 2; rept++) {
            uint8_t e = gb_read(sp++);
            uint8_t d = gb_read(sp++);
            //  if in v/hblank, wait until not in v/hblank
            // LDH_A_c;
            // AND_A_B;
            // IF_NZ goto loop\@;
            //  load vBGMap

            gb_write(hl++, e);
            gb_write(hl++, d);
        }
        hl += (BG_MAP_WIDTH - SCREEN_WIDTH);
    } while(--a != 0);
    gb_write(hTilesPerCycle, 0);
}

void SetPalettes(void) {
    SET_PC(aSetPalettes);
    //  Inits the Palettes
    //  depending on the system the monochromes palettes or color palettes
    LDH_A_addr(hCGB);
    AND_A_A;
    IF_NZ goto SetPalettesForGameBoyColor;
    LD_A(0b11100100);
    LDH_addr_A(rBGP);
    LD_A(0b11010000);
    LDH_addr_A(rOBP0);
    LDH_addr_A(rOBP1);
    RET;

SetPalettesForGameBoyColor:

    PUSH_DE;
    LD_A(0b11100100);
    CALL(aDmgToCgbBGPals);
    LD_DE((0b11100100 << 8) | 0b11100100);
    CALL(aDmgToCgbObjPals);
    POP_DE;
    RET;
}

//  Inits the Palettes
//  depending on the system the monochromes palettes or color palettes
void SetPalettes_Conv(void) {
    // LDH_A_addr(hCGB);
    // AND_A_A;
    // IF_NZ goto SetPalettesForGameBoyColor;
    if(gb_read(hCGB) != 0)
    {
        // PUSH_DE;
        // LD_A(0b11100100);
        // CALL(aDmgToCgbBGPals);
        DmgToCgbBGPals_Conv(0b11100100);

        // LD_DE((0b11100100 << 8) | 0b11100100);
        // CALL(aDmgToCgbObjPals);
        DmgToCgbObjPals_Conv(0b11100100, 0b11100100);
        
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

void ClearPalettes(void) {
    SET_PC(aClearPalettes);
    //  Make all palettes white

    //  CGB: make all the palette colors white
    LDH_A_addr(hCGB);
    AND_A_A;
    IF_NZ goto cgb;

    //  DMG: just change palettes to 0 (white)
    XOR_A_A;
    LDH_addr_A(rBGP);
    LDH_addr_A(rOBP0);
    LDH_addr_A(rOBP1);
    RET;

cgb:

    LDH_A_addr(rSVBK);
    PUSH_AF;

    LD_A(MBANK(awBGPals2));
    LDH_addr_A(rSVBK);

    //  Fill wBGPals2 and wOBPals2 with $ffff (white)
    LD_HL(wBGPals2);
    LD_BC(16 * PALETTE_SIZE);
    LD_A(0xff);
    CALL(aByteFill);

    POP_AF;
    LDH_addr_A(rSVBK);

    //  Request palette update
    LD_A(TRUE);
    LDH_addr_A(hCGBPalUpdate);
    RET;
}

//  Make all palettes white
//  CGB: make all the palette colors white
void ClearPalettes_Conv(void) {
    // LDH_A_addr(hCGB);
    // AND_A_A;
    // IF_NZ goto cgb;
    if(gb_read(hCGB) != 0)
    {
        // LDH_A_addr(rSVBK);
        // PUSH_AF;
        uint8_t vbk_temp = gb_read(rSVBK);

        // LD_A(MBANK(awBGPals2));
        // LDH_addr_A(rSVBK);
        gb_write(rSVBK, MBANK(awBGPals2));

        //  Fill wBGPals2 and wOBPals2 with $ffff (white)
        // LD_HL(wBGPals2);
        // LD_BC(16 * PALETTE_SIZE);
        // LD_A(0xff);
        // CALL(aByteFill);
        ByteFill_Conv(wBGPals2, (16 * PALETTE_SIZE), 0xff);

        // POP_AF;
        // LDH_addr_A(rSVBK);
        gb_write(rSVBK, vbk_temp);

        //  Request palette update
        // LD_A(TRUE);
        // LDH_addr_A(hCGBPalUpdate);
        gb_write(hCGBPalUpdate, TRUE);

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
    SET_PC(aGetMemSGBLayout);
    LD_B(SCGB_DEFAULT);
    return GetSGBLayout();
}

void GetSGBLayout(void) {
    SET_PC(aGetSGBLayout);
    //  load sgb packets unless dmg

    LDH_A_addr(hCGB);
    AND_A_A;
    IF_NZ goto sgb;

    LDH_A_addr(hSGB);
    AND_A_A;
    RET_Z;

sgb:

    PREDEF_JUMP(pLoadSGBLayout);

    return SetHPPal();
}

//  load sgb packets unless dmg
void GetSGBLayout_Conv(void) {
    // LDH_A_addr(hCGB);
    // AND_A_A;
    // IF_NZ goto sgb;
    if(gb_read(hCGB) != 0)
        PREDEF_JUMP(pLoadSGBLayout);

    // LDH_A_addr(hSGB);
    // AND_A_A;
    // RET_Z;
    if(gb_read(hSGB) == 0)
        return;

    PREDEF_JUMP(pLoadSGBLayout);
}

void SetHPPal(void) {
    SET_PC(aSetHPPal);
    //  Set palette for hp bar pixel length e at hl.
    CALL(aGetHPPal);
    LD_hl_D;
    RET;
}

void GetHPPal(void) {
    SET_PC(aGetHPPal);
    //  Get palette for hp bar pixel length e in d.
    LD_D(HP_GREEN);
    LD_A_E;
    CP_A((HP_BAR_LENGTH_PX * 50 / 100));  // 24
    RET_NC;
    INC_D;                                // HP_YELLOW
    CP_A((HP_BAR_LENGTH_PX * 21 / 100));  // 10
    RET_NC;
    INC_D;  // HP_RED
    RET;
}
