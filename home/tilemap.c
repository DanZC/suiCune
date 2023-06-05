#include "../constants.h"
#include "tilemap.h"

void ClearBGPalettes(void) {
    SET_PC(aClearBGPalettes);
    CALL(aClearPalettes);
    return WaitBGMap();
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
    LD_A(BANK(vBGMap2));
    LDH_addr_A(rVBK);
    hlcoord(0, 0, wAttrmap);
    CALL(av_CopyTilemapAtOnce_CopyBGMapViaStack);
    LD_A(BANK(vBGMap0));
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
    // IF_NZ goto loop;

    LDH_A_addr(hSPBuffer);
    LD_L_A;
    LDH_A_addr(hSPBuffer + 1);
    LD_H_A;
    LD_SP_HL;
    RET;
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

    LD_A(BANK(wBGPals2));
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
