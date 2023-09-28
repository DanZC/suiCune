#include "../../constants.h"
#include "dma_transfer.h"
#include "../../home/delay.h"
#include "../../home/gfx.h"
#include "../../home/copy.h"

void HDMATransferAttrmapAndTilemapToWRAMBank3(void) {
    LD_HL(mHDMATransferAttrmapAndTilemapToWRAMBank3_Function);
    JP(mCallInSafeGFXMode);

Function:
    decoord(0, 0, wAttrmap);
    LD_HL(wScratchAttrmap);
    CALL(mPadAttrmapForHDMATransfer);
    decoord(0, 0, wTilemap);
    LD_HL(wScratchTilemap);
    CALL(mPadTilemapForHDMATransfer);
    LD_A(0x0);
    LDH_addr_A(rVBK);
    LD_HL(wScratchTilemap);
    CALL(mHDMATransferToWRAMBank3);
    LD_A(0x1);
    LDH_addr_A(rVBK);
    LD_HL(wScratchAttrmap);
    CALL(mHDMATransferToWRAMBank3);
    RET;
}

void HDMATransferTilemapToWRAMBank3(void) {
    LD_HL(mHDMATransferTilemapToWRAMBank3_Function);
    JP(mCallInSafeGFXMode);

Function:
    decoord(0, 0, wTilemap);
    LD_HL(wScratchTilemap);
    CALL(mPadTilemapForHDMATransfer);
    LD_A(0x0);
    LDH_addr_A(rVBK);
    LD_HL(wScratchTilemap);
    CALL(mHDMATransferToWRAMBank3);
    RET;
}

static void HDMATransferTilemapToWRAMBank3_Function(void) {
    // decoord(0, 0, wTilemap);
    // LD_HL(wScratchTilemap);
    // CALL(mPadTilemapForHDMATransfer);
    PadTilemapForHDMATransfer_Conv2(wram->wScratchTilemap, wram->wTilemap);
    // LD_A(0x0);
    // LDH_addr_A(rVBK);
    gb_write(rVBK, 0x0);
    // LD_HL(wScratchTilemap);
    // CALL(mHDMATransferToWRAMBank3);
    HDMATransferToWRAMBank3_Conv(wram->wScratchTilemap);
    // RET;
}

void HDMATransferTilemapToWRAMBank3_Conv(void) {
    // LD_HL(mHDMATransferTilemapToWRAMBank3_Function);
    // JP(mCallInSafeGFXMode);
    CallInSafeGFXMode_Conv(HDMATransferTilemapToWRAMBank3_Function);
}

static void HDMATransferAttrmapToWRAMBank3_Function(void) {
// Function:
    // decoord(0, 0, wAttrmap);
    // LD_HL(wScratchAttrmap);
    // CALL(mPadAttrmapForHDMATransfer);
    PadAttrmapForHDMATransfer_Conv2(wram->wScratchAttrmap, coord(0, 0, wram->wAttrmap));
    // LD_A(0x1);
    // LDH_addr_A(rVBK);
    gb_write(rVBK, 0x1);
    // LD_HL(wScratchAttrmap);
    // CALL(mHDMATransferToWRAMBank3);
    HDMATransferToWRAMBank3_Conv(wram->wScratchAttrmap);
    // RET;
}

void HDMATransferAttrmapToWRAMBank3_Conv(void) {
    // LD_HL(mHDMATransferAttrmapToWRAMBank3_Function);
    // JP(mCallInSafeGFXMode);
    CallInSafeGFXMode_Conv(HDMATransferAttrmapToWRAMBank3_Function);
}

void HDMATransferAttrmapToWRAMBank3(void) {
    LD_HL(mHDMATransferAttrmapToWRAMBank3_Function);
    JP(mCallInSafeGFXMode);

Function:
    decoord(0, 0, wAttrmap);
    LD_HL(wScratchAttrmap);
    CALL(mPadAttrmapForHDMATransfer);
    LD_A(0x1);
    LDH_addr_A(rVBK);
    LD_HL(wScratchAttrmap);
    CALL(mHDMATransferToWRAMBank3);
    RET;
}

void ReloadMapPart(void) {
    LD_HL(mReloadMapPart_Function);
    JP(mCallInSafeGFXMode);

Function:
    decoord(0, 0, wAttrmap);
    LD_HL(wScratchAttrmap);
    CALL(mPadAttrmapForHDMATransfer);
    decoord(0, 0, wTilemap);
    LD_HL(wScratchTilemap);
    CALL(mPadTilemapForHDMATransfer);
    CALL(mDelayFrame);

    NOP;
    LDH_A_addr(rVBK);
    PUSH_AF;
    LD_A(0x1);
    LDH_addr_A(rVBK);
    LD_HL(wScratchAttrmap);
    CALL(mHDMATransfer_Wait127Scanlines_toBGMap);
    LD_A(0x0);
    LDH_addr_A(rVBK);
    LD_HL(wScratchTilemap);
    CALL(mHDMATransfer_Wait127Scanlines_toBGMap);
    POP_AF;
    LDH_addr_A(rVBK);
    NOP;

    RET;
}

void Mobile_ReloadMapPart(void) {
    LD_HL(mReloadMapPart);  // useless
    LD_HL(mMobile_ReloadMapPart_Function);
    JP(mCallInSafeGFXMode);

Function:
    decoord(0, 0, wAttrmap);
    LD_HL(wScratchAttrmap);
    CALL(mPadAttrmapForHDMATransfer);
    decoord(0, 0, wTilemap);
    LD_HL(wScratchTilemap);
    CALL(mPadTilemapForHDMATransfer);
    CALL(mDelayFrame);

    NOP;
    LDH_A_addr(rVBK);
    PUSH_AF;
    LD_A(0x1);
    LDH_addr_A(rVBK);
    LD_HL(wScratchAttrmap);
    CALL(mHDMATransfer_NoDI);
    LD_A(0x0);
    LDH_addr_A(rVBK);
    LD_HL(wScratchTilemap);
    CALL(mHDMATransfer_NoDI);
    POP_AF;
    LDH_addr_A(rVBK);
    NOP;

    RET;
}

void Function1040d4(void) {
    //  //  unreferenced
    LD_HL(mFunction1040d4_Function);
    JP(mCallInSafeGFXMode);

Function:
    LD_A(0x1);
    LDH_addr_A(rVBK);
    LD_A(MBANK(aw3_d800));
    LDH_addr_A(rSVBK);
    LD_DE(w3_d800);
    LDH_A_addr(hBGMapAddress + 1);
    LDH_addr_A(rHDMA1);
    LDH_A_addr(hBGMapAddress);
    LDH_addr_A(rHDMA2);
    LD_A_D;
    LDH_addr_A(rHDMA3);
    LD_A_E;
    LDH_addr_A(rHDMA4);
    LD_A(0x23);
    LDH_addr_A(hDMATransfer);
    CALL(mWaitDMATransfer);
    RET;
}

void Function1040fb(void) {
    //  //  unreferenced
    LD_HL(mFunction1040fb_Function);
    JP(mCallInSafeGFXMode);

Function:
    LD_A(0x1);
    LDH_addr_A(rVBK);
    LD_A(MBANK(aw3_d800));
    LDH_addr_A(rSVBK);
    LD_HL(w3_d800);
    CALL(mHDMATransferToWRAMBank3);
    RET;
}

void OpenAndCloseMenu_HDMATransferTilemapAndAttrmap(void) {
    //  OpenText
    LD_HL(mOpenAndCloseMenu_HDMATransferTilemapAndAttrmap_Function);
    JP(mCallInSafeGFXMode);

Function:
    // Transfer wAttrmap and Tilemap to BGMap
    // Fill vBGAttrs with $00
    // Fill vBGTiles with " "
    decoord(0, 0, wAttrmap);
    LD_HL(wScratchAttrmap);
    CALL(mPadAttrmapForHDMATransfer);
    decoord(0, 0, wTilemap);
    LD_HL(wScratchTilemap);
    CALL(mPadTilemapForHDMATransfer);
    CALL(mDelayFrame);

    NOP;
    LDH_A_addr(rVBK);
    PUSH_AF;
    LD_A(0x1);
    LDH_addr_A(rVBK);
    LD_HL(wScratchAttrmap);
    CALL(mHDMATransfer_Wait123Scanlines_toBGMap);
    LD_A(0x0);
    LDH_addr_A(rVBK);
    LD_HL(wScratchTilemap);
    CALL(mHDMATransfer_Wait123Scanlines_toBGMap);
    POP_AF;
    LDH_addr_A(rVBK);
    NOP;
    RET;
}

static void OpenAndCloseMenu_HDMATransferTilemapAndAttrmap_Function(void) {
    // Transfer wAttrmap and Tilemap to BGMap
    // Fill vBGAttrs with $00
    // Fill vBGTiles with " "
    // decoord(0, 0, wAttrmap);
    // LD_HL(wScratchAttrmap);
    // CALL(mPadAttrmapForHDMATransfer);
    PadAttrmapForHDMATransfer_Conv(wScratchAttrmap, coord(0, 0, wAttrmap));
    // decoord(0, 0, wTilemap);
    // LD_HL(wScratchTilemap);
    // CALL(mPadTilemapForHDMATransfer);
    PadTilemapForHDMATransfer_Conv(wScratchTilemap, coord(0, 0, wTilemap));
    // CALL(mDelayFrame);
    DelayFrame();

    // NOP;
    // LDH_A_addr(rVBK);
    // PUSH_AF;
    uint8_t vbk = gb_read(rVBK);
    // LD_A(0x1);
    // LDH_addr_A(rVBK);
    gb_write(rVBK, 0x1);
    // LD_HL(wScratchAttrmap);
    // CALL(mHDMATransfer_Wait123Scanlines_toBGMap);
    HDMATransfer_Wait123Scanlines_toBGMap_Conv(wScratchAttrmap);
    // LD_A(0x0);
    // LDH_addr_A(rVBK);
    gb_write(rVBK, 0x0);
    // LD_HL(wScratchTilemap);
    // CALL(mHDMATransfer_Wait123Scanlines_toBGMap);
    HDMATransfer_Wait123Scanlines_toBGMap_Conv(wScratchTilemap);
    // POP_AF;
    // LDH_addr_A(rVBK);
    gb_write(rVBK, vbk);
    // NOP;
    // RET;
}

void OpenAndCloseMenu_HDMATransferTilemapAndAttrmap_Conv(void) {
    //  OpenText
    // LD_HL(mOpenAndCloseMenu_HDMATransferTilemapAndAttrmap_Function);
    // JP(mCallInSafeGFXMode);
    return CallInSafeGFXMode_Conv(OpenAndCloseMenu_HDMATransferTilemapAndAttrmap_Function);
}

void Mobile_OpenAndCloseMenu_HDMATransferTilemapAndAttrmap(void) {
    LD_HL(mMobile_OpenAndCloseMenu_HDMATransferTilemapAndAttrmap_Function);
    JP(mCallInSafeGFXMode);

Function:
    // Transfer wAttrmap and Tilemap to BGMap
    // Fill vBGAttrs with $00
    // Fill vBGTiles with $ff
    decoord(0, 0, wAttrmap);
    LD_HL(wScratchAttrmap);
    CALL(mPadAttrmapForHDMATransfer);
    LD_C(0xff);
    decoord(0, 0, wTilemap);
    LD_HL(wScratchTilemap);
    CALL(mPadMapForHDMATransfer);

    LD_A(0x1);
    LDH_addr_A(rVBK);
    LD_HL(wScratchAttrmap);
    CALL(mHDMATransfer_Wait127Scanlines_toBGMap);
    LD_A(0x0);
    LDH_addr_A(rVBK);
    LD_HL(wScratchTilemap);
    CALL(mHDMATransfer_Wait127Scanlines_toBGMap);
    RET;
}

void CallInSafeGFXMode(void) {
    LDH_A_addr(hBGMapMode);
    PUSH_AF;
    LDH_A_addr(hMapAnims);
    PUSH_AF;
    XOR_A_A;
    LDH_addr_A(hBGMapMode);
    LDH_addr_A(hMapAnims);
    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(MBANK(awScratchTilemap));
    LDH_addr_A(rSVBK);
    LDH_A_addr(rVBK);
    PUSH_AF;

    CALL(mCallInSafeGFXMode__hl_);

    POP_AF;
    LDH_addr_A(rVBK);
    POP_AF;
    LDH_addr_A(rSVBK);
    POP_AF;
    LDH_addr_A(hMapAnims);
    POP_AF;
    LDH_addr_A(hBGMapMode);
    RET;

_hl_:
    JP_hl;
}

void CallInSafeGFXMode_Conv(void(*hl)(void)) {
    // LDH_A_addr(hBGMapMode);
    // PUSH_AF;
    uint8_t bgmapmode = hram->hBGMapMode;
    // LDH_A_addr(hMapAnims);
    // PUSH_AF;
    uint8_t mapanims = hram->hMapAnims;
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    // LDH_addr_A(hMapAnims);
    hram->hBGMapMode = 0;
    hram->hMapAnims = 0;
    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    uint8_t svbk = gb_read(rSVBK);
    // LD_A(MBANK(awScratchTilemap));
    // LDH_addr_A(rSVBK);
    gb_write(rSVBK, MBANK(awScratchTilemap));
    // LDH_A_addr(rVBK);
    // PUSH_AF;
    uint8_t vbk = gb_read(rVBK);

    // CALL(mCallInSafeGFXMode__hl_);
    hl();

    // POP_AF;
    // LDH_addr_A(rVBK);
    gb_write(rVBK, vbk);
    // POP_AF;
    // LDH_addr_A(rSVBK);
    gb_write(rSVBK, svbk);
    // POP_AF;
    // LDH_addr_A(hMapAnims);
    hram->hMapAnims = mapanims;
    // POP_AF;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = bgmapmode;
    // RET;

// _hl_:
//     JP_hl;
}

void HDMATransferToWRAMBank3(void) {
    CALL(mv_LoadHDMAParameters);
    LD_A(0x23);
    LDH_addr_A(hDMATransfer);

    return WaitDMATransfer();
}

void HDMATransferToWRAMBank3_Conv(uint8_t* hl) {
    // CALL(mv_LoadHDMAParameters);
    // LD_A(0x23);
    // LDH_addr_A(hDMATransfer);
    DelayFrame();
    CopyBytes_Conv2(GBToRAMAddr(0x8000 + (hram->hBGMapAddress & 0x1ff0)), hl, 1024); // (0x23 + 1) * 10 * 2);
}

void WaitDMATransfer(void) {
loop:
    CALL(mDelayFrame);
    LDH_A_addr(hDMATransfer);
    AND_A_A;
    IF_NZ goto loop;
    RET;
}

void HDMATransfer_Wait127Scanlines_toBGMap(void) {
    //  HDMA transfer from hl to [hBGMapAddress]
    //  hBGMapAddress -> de
    //  2 * SCREEN_HEIGHT -> c
    LDH_A_addr(hBGMapAddress + 1);
    LD_D_A;
    LDH_A_addr(hBGMapAddress);
    LD_E_A;
    LD_C(2 * SCREEN_HEIGHT);
    JR(mHDMATransfer_Wait127Scanlines);
}

void HDMATransfer_Wait123Scanlines_toBGMap(void) {
    //  HDMA transfer from hl to [hBGMapAddress]
    //  hBGMapAddress -> de
    //  2 * SCREEN_HEIGHT -> c
    //  $7b --> b
    LDH_A_addr(hBGMapAddress + 1);
    LD_D_A;
    LDH_A_addr(hBGMapAddress);
    LD_E_A;
    LD_C(2 * SCREEN_HEIGHT);
    JR(mHDMATransfer_Wait123Scanlines);
}

void HDMATransfer_Wait123Scanlines_toBGMap_Conv(uint16_t hl) {
    //  HDMA transfer from hl to [hBGMapAddress]
    //  hBGMapAddress -> de
    //  2 * SCREEN_HEIGHT -> c
    //  $7b --> b
    // LDH_A_addr(hBGMapAddress + 1);
    // LD_D_A;
    // LDH_A_addr(hBGMapAddress);
    // LD_E_A;
    // LD_C(2 * SCREEN_HEIGHT);
    // JR(mHDMATransfer_Wait123Scanlines);
    return HDMATransfer_Wait123Scanlines_Conv(hl, gb_read16(hBGMapAddress), 2 * SCREEN_HEIGHT);
}

void HDMATransfer_NoDI(void) {
    //  HDMA transfer from hl to [hBGMapAddress]
    //  [hBGMapAddress] --> de
    //  2 * SCREEN_HEIGHT --> c
    LDH_A_addr(hBGMapAddress + 1);
    LD_D_A;
    LDH_A_addr(hBGMapAddress);
    LD_E_A;
    LD_C(2 * SCREEN_HEIGHT);

    // [rHDMA1, rHDMA2] = hl & $fff0
    LD_A_H;
    LDH_addr_A(rHDMA1);
    LD_A_L;
    AND_A(0xf0);
    LDH_addr_A(rHDMA2);
    // [rHDMA3, rHDMA4] = de & $1ff0
    LD_A_D;
    AND_A(0x1f);
    LDH_addr_A(rHDMA3);
    LD_A_E;
    AND_A(0xf0);
    LDH_addr_A(rHDMA4);
    // b = c | %10000000
    LD_A_C;
    DEC_C;
    OR_A(0x80);
    LD_B_A;
    // d = $7f - c + 1
    LD_A(0x7f);
    SUB_A_C;
    LD_D_A;
    // while [rLY] >= d: pass

loop1:
    LDH_A_addr(rLY);
    CP_A_D;
    // IF_NC goto loop1;
    //  while not [rSTAT] & 3: pass

loop2:
    LDH_A_addr(rSTAT);
    AND_A(0x3);
    // IF_Z goto loop2;
    //  load the 5th byte of HDMA
    LD_A_B;
    DEC_A;
    LDH_addr_A(rHDMA5);
    // wait until rLY advances (c + 1) times
    LDH_A_addr(rLY);
    INC_C;
    LD_HL(rLY);

loop3:
    CP_A_hl;
    // IF_Z goto loop3;
    LD_A_hl;
    DEC_C;
    // IF_NZ goto loop3;
    LD_HL(rHDMA5);
    // RES_hl(7);
    RET;
}

void HDMATransfer_Wait123Scanlines(void) {
    LD_B(0x7b);
    JR(mv_continue_HDMATransfer);
}

void HDMATransfer_Wait123Scanlines_Conv(uint16_t hl, uint16_t de, uint8_t c) {
    // LD_B(0x7b);
    // JR(mv_continue_HDMATransfer);
    return v_continue_HDMATransfer_Conv(hl, de, c, 0x7b);
}

void HDMATransfer_Wait127Scanlines(void) {
    LD_B(0x7f);
    return v_continue_HDMATransfer();
}

void HDMATransfer_Wait127Scanlines_Conv(uint16_t hl, uint16_t de, uint8_t c) {
    // LD_B(0x7f);
    return v_continue_HDMATransfer_Conv(hl, de, c, 0x7f);
}

void v_continue_HDMATransfer(void) {
    //  a lot of waiting around for hardware registers
    // [rHDMA1, rHDMA2] = hl & $fff0
    LD_A_H;
    LDH_addr_A(rHDMA1);
    LD_A_L;
    AND_A(0xf0);  // high nybble
    LDH_addr_A(rHDMA2);
    // [rHDMA3, rHDMA4] = de & $1ff0
    LD_A_D;
    AND_A(0x1f);  // lower 5 bits
    LDH_addr_A(rHDMA3);
    LD_A_E;
    AND_A(0xf0);  // high nybble
    LDH_addr_A(rHDMA4);
    // e = c | %10000000
    LD_A_C;
    DEC_C;
    OR_A(0x80);
    LD_E_A;
    // d = b - c + 1
    LD_A_B;
    SUB_A_C;
    LD_D_A;
    // while [rLY] >= d: pass

ly_loop:
    LDH_A_addr(rLY);
    CP_A_D;
    // IF_NC goto ly_loop;

    NOP;
    // while [rSTAT] & 3: pass

rstat_loop_1:
    LDH_A_addr(rSTAT);
    AND_A(0x3);
    // IF_NZ goto rstat_loop_1;
    //  while not [rSTAT] & 3: pass

rstat_loop_2:
    LDH_A_addr(rSTAT);
    AND_A(0x3);
    // IF_Z goto rstat_loop_2;
    //  load the 5th byte of HDMA
    LD_A_E;
    DEC_A;  // patch
    LDH_addr_A(rHDMA5);
    // wait until rLY advances (c + 1) times
    LDH_A_addr(rLY);
    INC_C;
    LD_HL(rLY);

final_ly_loop:
    CP_A_hl;
    // IF_Z goto final_ly_loop;
    LD_A_hl;
    DEC_C;
    // IF_NZ goto final_ly_loop;
    // LD_HL(rHDMA5);
    // RES_hl(7);
    NOP;

    RET;
}

void v_continue_HDMATransfer_Conv(uint16_t hl, uint16_t de, uint8_t c, uint8_t b) {
    //  a lot of waiting around for hardware registers
    // [rHDMA1, rHDMA2] = hl & $fff0
    // LD_A_H;
    // LDH_addr_A(rHDMA1);
    gb_write(rHDMA1, HIGH(hl));
    // LD_A_L;
    // AND_A(0xf0);  // high nybble
    // LDH_addr_A(rHDMA2);
    gb_write(rHDMA2, (uint8_t)(hl & 0xf0));  // high nybble
    // [rHDMA3, rHDMA4] = de & $1ff0
    // LD_A_D;
    // AND_A(0x1f);  // lower 5 bits
    // LDH_addr_A(rHDMA3);
    gb_write(rHDMA3, HIGH(de) & 0x1f);
    // LD_A_E;
    // AND_A(0xf0);  // high nybble
    // LDH_addr_A(rHDMA4);
    gb_write(rHDMA4, (uint8_t)(de & 0xf0));  // high nybble
    // e = c | %10000000
    // LD_A_C;
    // DEC_C;
    // OR_A(0x80);
    // LD_E_A;
    // d = b - c + 1
    // LD_A_B;
    // SUB_A_C;
    // LD_D_A;
    // while [rLY] >= d: pass
    de = ((uint16_t)(b - c + 1) << 8) | (c | 0b10000000);

ly_loop:;
    // LDH_A_addr(rLY);
    // CP_A_D;
    // IF_NC goto ly_loop;

    // NOP;
    // while [rSTAT] & 3: pass

rstat_loop_1:;
    // LDH_A_addr(rSTAT);
    // AND_A(0x3);
    // IF_NZ goto rstat_loop_1;
    //  while not [rSTAT] & 3: pass

rstat_loop_2:;
    // LDH_A_addr(rSTAT);
    // AND_A(0x3);
    // IF_Z goto rstat_loop_2;
    //  load the 5th byte of HDMA
    // LD_A_E;
    // DEC_A;  // patch
    // LDH_addr_A(rHDMA5);
    gb_write(rHDMA5, LOW(de));
    // wait until rLY advances (c + 1) times
    // LDH_A_addr(rLY);
    // INC_C;
    // LD_HL(rLY);

final_ly_loop:;
    // CP_A_hl;
    // IF_Z goto final_ly_loop;
    // LD_A_hl;
    // DEC_C;
    // IF_NZ goto final_ly_loop;
    // LD_HL(rHDMA5);
    // RES_hl(7);
    // NOP;

    // RET;
}

void v_LoadHDMAParameters(void) {
    LD_A_H;
    LDH_addr_A(rHDMA1);
    LD_A_L;
    LDH_addr_A(rHDMA2);
    LDH_A_addr(hBGMapAddress + 1);
    AND_A(0x1f);
    LDH_addr_A(rHDMA3);
    LDH_A_addr(hBGMapAddress);
    LDH_addr_A(rHDMA4);
    RET;
}

void PadTilemapForHDMATransfer(void) {
    LD_C(0x7f);
    JR(mPadMapForHDMATransfer);
}

void PadTilemapForHDMATransfer_Conv(uint16_t hl, uint16_t de) {
    return PadMapForHDMATransfer_Conv(hl, de, 0x7f);
}

void PadTilemapForHDMATransfer_Conv2(uint8_t* hl, const uint8_t* de) {
    return PadMapForHDMATransfer_Conv2(hl, de, 0x7f);
}

void PadAttrmapForHDMATransfer(void) {
    LD_C(0x0);

    return PadMapForHDMATransfer();
}

void PadAttrmapForHDMATransfer_Conv(uint16_t hl, uint16_t de) {
    return PadMapForHDMATransfer_Conv(hl, de, 0x0);
}

void PadAttrmapForHDMATransfer_Conv2(uint8_t* hl, const uint8_t* de) {
    return PadMapForHDMATransfer_Conv2(hl, de, 0x0);
}

void PadMapForHDMATransfer(void) {
    //  pad a 20x18 map to 32x18 for HDMA transfer
    //  back up the padding value in c to hMapObjectIndex
    LDH_A_addr(hMapObjectIndex);
    PUSH_AF;
    LD_A_C;
    LDH_addr_A(hMapObjectIndex);

    //  for each row on the screen
    LD_C(SCREEN_HEIGHT);

loop1:
    //  for each tile in the row
    LD_B(SCREEN_WIDTH);

loop2:
    //  copy from de to hl
    LD_A_de;
    INC_DE;
    LD_hli_A;
    DEC_B;
    IF_NZ goto loop2;

    //  load the original padding value of c into hl for 32 - 20 = 12 rows
    LDH_A_addr(hMapObjectIndex);
    LD_B(BG_MAP_WIDTH - SCREEN_WIDTH);

loop3:
    LD_hli_A;
    DEC_B;
    IF_NZ goto loop3;

    DEC_C;
    IF_NZ goto loop1;

    //  restore the original value of hMapObjectIndex
    POP_AF;
    LDH_addr_A(hMapObjectIndex);
    RET;
}

//  pad a 20x18 map to 32x18 for HDMA transfer
void PadMapForHDMATransfer_Conv(uint16_t hl, uint16_t de, uint8_t c) {
    //  back up the padding value in c to hMapObjectIndex
    // LDH_A_addr(hMapObjectIndex);
    // PUSH_AF;
    // uint8_t mapobjidx = gb_read(hMapObjectIndex);
    // LD_A_C;
    // LDH_addr_A(hMapObjectIndex);
    // gb_write(hMapObjectIndex, c);

    //  for each row on the screen
    // LD_C(SCREEN_HEIGHT);

    for(uint8_t r = SCREEN_HEIGHT; r > 0; --r) {
        //  for each tile in the row
        // LD_B(SCREEN_WIDTH);

        for(uint8_t b = SCREEN_WIDTH; b > 0; --b) {
            //  copy from de to hl
            // LD_A_de;
            // INC_DE;
            // LD_hli_A;
            gb_write(hl++, gb_read(de++));
            // DEC_B;
            // IF_NZ goto loop2;
        }

        //  load the original padding value of c into hl for 32 - 20 = 12 rows
        // LDH_A_addr(hMapObjectIndex);
        // LD_B(BG_MAP_WIDTH - SCREEN_WIDTH);

        for(uint8_t b = (BG_MAP_WIDTH - SCREEN_WIDTH); b > 0; --b) {
            // LD_hli_A;
            gb_write(hl++, c);
            // DEC_B;
            // IF_NZ goto loop3;
        }

        // DEC_C;
        // IF_NZ goto loop1;
    }

    //  restore the original value of hMapObjectIndex
    // POP_AF;
    // LDH_addr_A(hMapObjectIndex);
    // RET;
}

//  pad a 20x18 map to 32x18 for HDMA transfer
void PadMapForHDMATransfer_Conv2(uint8_t* hl, const uint8_t* de, uint8_t c) {
    //  back up the padding value in c to hMapObjectIndex
    // LDH_A_addr(hMapObjectIndex);
    // PUSH_AF;
    // uint8_t mapobjidx = gb_read(hMapObjectIndex);
    // LD_A_C;
    // LDH_addr_A(hMapObjectIndex);
    // gb_write(hMapObjectIndex, c);

    //  for each row on the screen
    // LD_C(SCREEN_HEIGHT);

    for(uint8_t r = SCREEN_HEIGHT; r > 0; --r) {
        //  for each tile in the row
        // LD_B(SCREEN_WIDTH);

        for(uint8_t b = SCREEN_WIDTH; b > 0; --b) {
            //  copy from de to hl
            // LD_A_de;
            // INC_DE;
            // LD_hli_A;
            *(hl++) = *(de++);
            // DEC_B;
            // IF_NZ goto loop2;
        }

        //  load the original padding value of c into hl for 32 - 20 = 12 rows
        // LDH_A_addr(hMapObjectIndex);
        // LD_B(BG_MAP_WIDTH - SCREEN_WIDTH);

        for(uint8_t b = (BG_MAP_WIDTH - SCREEN_WIDTH); b > 0; --b) {
            // LD_hli_A;
            *(hl++) = c;
            // DEC_B;
            // IF_NZ goto loop3;
        }

        // DEC_C;
        // IF_NZ goto loop1;
    }

    //  restore the original value of hMapObjectIndex
    // POP_AF;
    // LDH_addr_A(hMapObjectIndex);
    // RET;
}

void HDMATransfer2bpp(void) {
    // 2bpp when [rLCDC] & $80
    // switch to WRAM bank 6
    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(MBANK(awScratchTilemap));
    LDH_addr_A(rSVBK);

    PUSH_BC;
    PUSH_HL;

    // Copy c tiles of the 2bpp from b:de to wScratchTilemap
    LD_A_B;  // bank
    LD_L_C;  // number of tiles
    LD_H(0x0);
    // multiply by 16 (16 bytes of a 2bpp = 8 x 8 tile)
    ADD_HL_HL;
    ADD_HL_HL;
    ADD_HL_HL;
    ADD_HL_HL;
    LD_B_H;
    LD_C_L;
    LD_H_D;  // address
    LD_L_E;
    LD_DE(wScratchTilemap);
    CALL(mFarCopyBytes);

    POP_HL;
    POP_BC;

    PUSH_BC;
    CALL(mDelayFrame);
    POP_BC;

    LD_D_H;
    LD_E_L;
    LD_HL(wScratchTilemap);
    CALL(mHDMATransfer_Wait127Scanlines);

    // restore the previous bank
    POP_AF;
    LDH_addr_A(rSVBK);
    RET;
}

void HDMATransfer2bpp_Conv(uint8_t b, uint16_t de, uint16_t hl, uint8_t c) {
    // 2bpp when [rLCDC] & $80
    // switch to WRAM bank 6
    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    // LD_A(MBANK(awScratchTilemap));
    // LDH_addr_A(rSVBK);
    wbank_push(MBANK(awScratchTilemap));

    // PUSH_BC;
    // PUSH_HL;

    // Copy c tiles of the 2bpp from b:de to wScratchTilemap
    // LD_A_B;  // bank
    // LD_L_C;  // number of tiles
    // LD_H(0x0);
    // multiply by 16 (16 bytes of a 2bpp = 8 x 8 tile)
    // ADD_HL_HL;
    // ADD_HL_HL;
    // ADD_HL_HL;
    // ADD_HL_HL;
    // LD_B_H;
    // LD_C_L;
    // LD_H_D;  // address
    // LD_L_E;
    // LD_DE(wScratchTilemap);
    // CALL(mFarCopyBytes);
    FarCopyBytes_Conv(wScratchTilemap, b, de, c * LEN_2BPP_TILE);

    // POP_HL;
    // POP_BC;

    // PUSH_BC;
    // CALL(mDelayFrame);
    DelayFrame();
    // POP_BC;

    // LD_D_H;
    // LD_E_L;
    // LD_HL(wScratchTilemap);
    // CALL(mHDMATransfer_Wait127Scanlines);
    HDMATransfer_Wait123Scanlines_Conv(wScratchTilemap, hl, c);

    // restore the previous bank
    // POP_AF;
    // LDH_addr_A(rSVBK);
    // RET;
    wbank_pop;
}

void HDMATransfer1bpp(void) {
    // 1bpp when [rLCDC] & $80

loop:
    LD_A_C;
    CP_A(0x10);
    JP_C(mHDMATransfer1bpp_bankswitch);
    JP_Z(mHDMATransfer1bpp_bankswitch);
    PUSH_BC;
    PUSH_HL;
    PUSH_DE;
    LD_C(0x10);
    CALL(mHDMATransfer1bpp_bankswitch);
    POP_DE;
    LD_HL(0x80);
    ADD_HL_DE;
    LD_D_H;
    LD_E_L;
    POP_HL;
    LD_BC((1 << 8) | 0);
    ADD_HL_BC;
    POP_BC;
    LD_A_C;
    SUB_A(0x10);
    LD_C_A;
    goto loop;

bankswitch:
    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(MBANK(awScratchTilemap));
    LDH_addr_A(rSVBK);

    PUSH_BC;
    PUSH_HL;

    LD_A_B;
    LD_L_C;
    LD_H(0x0);
    ADD_HL_HL;  // multiply by 8
    ADD_HL_HL;  // multiply by 8
    ADD_HL_HL;  // multiply by 8
    LD_C_L;
    LD_B_H;
    LD_H_D;
    LD_L_E;
    LD_DE(wScratchTilemap);
    CALL(mFarCopyBytesDouble_DoubleBankSwitch);

    POP_HL;
    POP_BC;

    PUSH_BC;
    CALL(mDelayFrame);
    POP_BC;

    LD_D_H;
    LD_E_L;
    LD_HL(wScratchTilemap);
    CALL(mHDMATransfer_Wait127Scanlines);

    POP_AF;
    LDH_addr_A(rSVBK);
    RET;
}

void HDMATransfer_OnlyTopFourRows(void) {
    LD_HL(mHDMATransfer_OnlyTopFourRows_Function);
    JP(mCallInSafeGFXMode);

Function:
    LD_HL(wScratchTilemap);
    decoord(0, 0, wTilemap);
    CALL(mHDMATransfer_OnlyTopFourRows_Copy);
    LD_HL(wScratchTilemap + 0x80);
    decoord(0, 0, wAttrmap);
    CALL(mHDMATransfer_OnlyTopFourRows_Copy);
    LD_A(0x1);
    LDH_addr_A(rVBK);
    LD_C(0x8);
    LD_HL(wScratchTilemap + 0x80);
    debgcoord(0, 0, vBGMap1);
    CALL(mHDMATransfer_Wait127Scanlines);
    LD_A(0x0);
    LDH_addr_A(rVBK);
    LD_C(0x8);
    LD_HL(wScratchTilemap);
    debgcoord(0, 0, vBGMap1);
    CALL(mHDMATransfer_Wait127Scanlines);
    RET;

Copy:
    LD_B(4);

outer_loop:
    LD_C(SCREEN_WIDTH);

inner_loop:
    LD_A_de;
    LD_hli_A;
    INC_DE;
    DEC_C;
    IF_NZ goto inner_loop;
    LD_A_L;
    ADD_A(BG_MAP_WIDTH - SCREEN_WIDTH);
    LD_L_A;
    LD_A_H;
    ADC_A(0);
    LD_H_A;
    DEC_B;
    IF_NZ goto outer_loop;
    RET;
}

static void HDMATransfer_OnlyTopFourRows_Copy(uint8_t* hl, uint8_t* de) {
    // LD_B(4);
    uint8_t b = 4;

    do {
    // outer_loop:
        // LD_C(SCREEN_WIDTH);
        uint8_t c = SCREEN_WIDTH;

        do {
        // inner_loop:
            // LD_A_de;
            // LD_hli_A;
            // INC_DE;
            *(hl++) = *(de++);
            // DEC_C;
            // IF_NZ goto inner_loop;
        } while(--c != 0);
        // LD_A_L;
        // ADD_A(BG_MAP_WIDTH - SCREEN_WIDTH);
        // LD_L_A;
        // LD_A_H;
        // ADC_A(0);
        // LD_H_A;
        hl += BG_MAP_WIDTH - SCREEN_WIDTH;
        // DEC_B;
        // IF_NZ goto outer_loop;
    } while(--b != 0);
    // RET;
}

static void HDMATransfer_OnlyTopFourRows_Function(void) {
// Function:
    // LD_HL(wScratchTilemap);
    // decoord(0, 0, wTilemap);
    // CALL(mHDMATransfer_OnlyTopFourRows_Copy);
    HDMATransfer_OnlyTopFourRows_Copy(wram->wScratchTilemap, wram->wTilemap);
    // LD_HL(wScratchTilemap + 0x80);
    // decoord(0, 0, wAttrmap);
    // CALL(mHDMATransfer_OnlyTopFourRows_Copy);
    HDMATransfer_OnlyTopFourRows_Copy(wram->wScratchTilemap + 0x80, wram->wAttrmap);
    // LD_A(0x1);
    // LDH_addr_A(rVBK);
    // LD_C(0x8);
    // LD_HL(wScratchTilemap + 0x80);
    // debgcoord(0, 0, vBGMap1);
    // CALL(mHDMATransfer_Wait127Scanlines);
    CopyBytes_Conv2(vram->vBGMap3, wram->wScratchTilemap + 0x80, 0x8 * LEN_2BPP_TILE);
    // LD_A(0x0);
    // LDH_addr_A(rVBK);
    // LD_C(0x8);
    // LD_HL(wScratchTilemap);
    // debgcoord(0, 0, vBGMap1);
    // CALL(mHDMATransfer_Wait127Scanlines);
    CopyBytes_Conv2(vram->vBGMap1, wram->wScratchTilemap, 0x8 * LEN_2BPP_TILE);
    // RET;
}

void HDMATransfer_OnlyTopFourRows_Conv(void) {
    // LD_HL(mHDMATransfer_OnlyTopFourRows_Function);
    // JP(mCallInSafeGFXMode);
    return CallInSafeGFXMode_Conv(HDMATransfer_OnlyTopFourRows_Function);
}
