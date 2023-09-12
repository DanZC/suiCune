#include "../../constants.h"
#include "init_map.h"
#include "../../home/gfx.h"
#include "../../home/sprite_updates.h"
#include "../../home/window.h"
#include "../../home/copy.h"
#include "../../home/delay.h"
#include "../../home/map.h"
#include "../gfx/color.h"
#include "../gfx/crystal_layouts.h"

void ReanchorBGMap_NoOAMUpdate(void){
    CALL(aDelayFrame);
    LDH_A_addr(hOAMUpdate);
    PUSH_AF;

    LD_A(0x1);
    LDH_addr_A(hOAMUpdate);
    LDH_A_addr(hBGMapMode);
    PUSH_AF;
    XOR_A_A;
    LDH_addr_A(hBGMapMode);

    CALL(aReanchorBGMap_NoOAMUpdate_ReanchorBGMap);

    POP_AF;
    LDH_addr_A(hBGMapMode);
    POP_AF;
    LDH_addr_A(hOAMUpdate);

    LD_HL(wVramState);
    SET_hl(6);
    RET;


ReanchorBGMap:
    XOR_A_A;
    LDH_addr_A(hLCDCPointer);
    LDH_addr_A(hBGMapMode);
    LD_A(0x90);
    LDH_addr_A(hWY);
    CALL(aOverworldTextModeSwitch);
    LD_A(HIGH(vBGMap1));
    CALL(aReanchorBGMap_NoOAMUpdate_LoadBGMapAddrIntoHRAM);
    CALL(av_OpenAndCloseMenu_HDMATransferTilemapAndAttrmap);
    FARCALL(aLoadOW_BGPal7);
    FARCALL(aApplyPals);
    LD_A(TRUE);
    LDH_addr_A(hCGBPalUpdate);
    XOR_A_A;
    LDH_addr_A(hBGMapMode);
    LDH_addr_A(hWY);
    FARCALL(aHDMATransfer_FillBGMap0WithBlack);  // no need to farcall
    LD_A(HIGH(vBGMap0));
    CALL(aReanchorBGMap_NoOAMUpdate_LoadBGMapAddrIntoHRAM);
    XOR_A_A;  // LOW(vBGMap0)
    LD_addr_A(wBGMapAnchor);
    LD_A(HIGH(vBGMap0));
    LD_addr_A(wBGMapAnchor + 1);
    XOR_A_A;
    LDH_addr_A(hSCX);
    LDH_addr_A(hSCY);
    CALL(aApplyBGMapAnchorToObjects);
    RET;


LoadBGMapAddrIntoHRAM:
    LDH_addr_A(hBGMapAddress + 1);
    XOR_A_A;
    LDH_addr_A(hBGMapAddress);
    RET;

}

static void ReanchorBGMap_NoOAMUpdate_LoadBGMapAddrIntoHRAM(uint8_t a) {
    // LDH_addr_A(hBGMapAddress + 1);
    // XOR_A_A;
    // LDH_addr_A(hBGMapAddress);
    // RET;
    hram->hBGMapAddress = (a << 8);
}

static void ReanchorBGMap_NoOAMUpdate_ReanchorBGMap(void) {
    // XOR_A_A;
    // LDH_addr_A(hLCDCPointer);
    // LDH_addr_A(hBGMapMode);
    hram->hLCDCPointer = 0;
    hram->hBGMapMode = 0;
    // LD_A(0x90);
    // LDH_addr_A(hWY);
    hram->hWY = 0x90;
    // CALL(aOverworldTextModeSwitch);
    OverworldTextModeSwitch_Conv();
    // LD_A(HIGH(vBGMap1));
    // CALL(aReanchorBGMap_NoOAMUpdate_LoadBGMapAddrIntoHRAM);
    ReanchorBGMap_NoOAMUpdate_LoadBGMapAddrIntoHRAM(HIGH(vBGMap1));
    // CALL(av_OpenAndCloseMenu_HDMATransferTilemapAndAttrmap);
    v_OpenAndCloseMenu_HDMATransferTilemapAndAttrmap_Conv();
    // FARCALL(aLoadOW_BGPal7);
    LoadOW_BGPal7();
    // FARCALL(aApplyPals);
    ApplyPals_Conv();
    // LD_A(TRUE);
    // LDH_addr_A(hCGBPalUpdate);
    hram->hCGBPalUpdate = TRUE;
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = 0;
    // LDH_addr_A(hWY);
    hram->hWY = 0;
    // FARCALL(aHDMATransfer_FillBGMap0WithBlack);  // no need to farcall
    HDMATransfer_FillBGMap0WithBlack_Conv();
    // LD_A(HIGH(vBGMap0));
    // CALL(aReanchorBGMap_NoOAMUpdate_LoadBGMapAddrIntoHRAM);
    ReanchorBGMap_NoOAMUpdate_LoadBGMapAddrIntoHRAM(HIGH(vBGMap0));
    // XOR_A_A;  // LOW(vBGMap0)
    // LD_addr_A(wBGMapAnchor);
    // LD_A(HIGH(vBGMap0));
    // LD_addr_A(wBGMapAnchor + 1);
    wram->wBGMapAnchor = vBGMap0;
    // XOR_A_A;
    // LDH_addr_A(hSCX);
    hram->hSCX = 0;
    // LDH_addr_A(hSCY);
    hram->hSCY = 0;
    // CALL(aApplyBGMapAnchorToObjects);
    // RET;
}

void ReanchorBGMap_NoOAMUpdate_Conv(void){
    // CALL(aDelayFrame);
    DelayFrame();
    // LDH_A_addr(hOAMUpdate);
    // PUSH_AF;
    uint8_t oam = hram->hOAMUpdate;

    // LD_A(0x1);
    // LDH_addr_A(hOAMUpdate);
    hram->hOAMUpdate = 0x1;
    // LDH_A_addr(hBGMapMode);
    // PUSH_AF;
    uint8_t bg = hram->hBGMapMode;
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = bg;

    // CALL(aReanchorBGMap_NoOAMUpdate_ReanchorBGMap);
    ReanchorBGMap_NoOAMUpdate_ReanchorBGMap();

    // POP_AF;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = bg;
    // POP_AF;
    // LDH_addr_A(hOAMUpdate);
    hram->hOAMUpdate = oam;

    // LD_HL(wVramState);
    // SET_hl(6);
    // RET;
    bit_set(wram->wVramState, 6);
}

void LoadFonts_NoOAMUpdate(void){
    LDH_A_addr(hOAMUpdate);
    PUSH_AF;
    LD_A(0x1);
    LDH_addr_A(hOAMUpdate);

    CALL(aLoadFonts_NoOAMUpdate_LoadGFX);

    POP_AF;
    LDH_addr_A(hOAMUpdate);
    RET;


LoadGFX:
    CALL(aLoadFontsExtra);
    LD_A(0x90);
    LDH_addr_A(hWY);
    CALL(aSafeUpdateSprites);
    CALL(aLoadStandardFont);
    RET;

}

static void LoadFonts_NoOAMUpdate_LoadGFX(void) {
// LoadGFX:
    // CALL(aLoadFontsExtra);
    LoadFontsExtra_Conv();
    // LD_A(0x90);
    // LDH_addr_A(hWY);
    hram->hWY = 0x90;
    // CALL(aSafeUpdateSprites);
    SafeUpdateSprites_Conv();
    // CALL(aLoadStandardFont);
    LoadStandardFont_Conv();
    // RET;
}

void LoadFonts_NoOAMUpdate_Conv(void){
    // LDH_A_addr(hOAMUpdate);
    // PUSH_AF;
    uint8_t temp = hram->hOAMUpdate;
    // LD_A(0x1);
    // LDH_addr_A(hOAMUpdate);
    hram->hOAMUpdate = 0x1;

    // CALL(aLoadFonts_NoOAMUpdate_LoadGFX);
    LoadFonts_NoOAMUpdate_LoadGFX();

    // POP_AF;
    // LDH_addr_A(hOAMUpdate);
    // RET;
    hram->hOAMUpdate = temp;
}

void HDMATransfer_FillBGMap0WithBlack(void){
    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(MBANK(awDecompressScratch));
    LDH_addr_A(rSVBK);

    LD_A(0x60);
    LD_HL(wDecompressScratch);
    LD_BC(wScratchAttrmap - wDecompressScratch);
    CALL(aByteFill);
    LD_A(HIGH(wDecompressScratch));
    LDH_addr_A(rHDMA1);
    LD_A(LOW(wDecompressScratch));
    LDH_addr_A(rHDMA2);
    LD_A(HIGH(vBGMap0 - VRAM_Begin));
    LDH_addr_A(rHDMA3);
    LD_A(LOW(vBGMap0 - VRAM_Begin));
    LDH_addr_A(rHDMA4);
    LD_A(0x3f);
    LDH_addr_A(hDMATransfer);
    CALL(aDelayFrame);

    POP_AF;
    LDH_addr_A(rSVBK);
    RET;

}

void HDMATransfer_FillBGMap0WithBlack_Conv(void){
    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    // LD_A(MBANK(awDecompressScratch));
    // LDH_addr_A(rSVBK);
    wbank_push(MBANK(awDecompressScratch));

    // LD_A(0x60);
    // LD_HL(wDecompressScratch);
    // LD_BC(wScratchAttrmap - wDecompressScratch);
    // CALL(aByteFill);
    ByteFill_Conv(wDecompressScratch, wScratchAttrmap - wDecompressScratch, 0x60);
    // LD_A(HIGH(wDecompressScratch));
    // LDH_addr_A(rHDMA1);
    gb_write(rHDMA1, HIGH(wDecompressScratch));
    // LD_A(LOW(wDecompressScratch));
    // LDH_addr_A(rHDMA2);
    gb_write(rHDMA2, LOW(wDecompressScratch));
    // LD_A(HIGH(vBGMap0 - VRAM_Begin));
    // LDH_addr_A(rHDMA3);
    gb_write(rHDMA3, HIGH(vBGMap0 - VRAM_Begin));
    // LD_A(LOW(vBGMap0 - VRAM_Begin));
    // LDH_addr_A(rHDMA4);
    gb_write(rHDMA4, LOW(vBGMap0 - VRAM_Begin));
    // LD_A(0x3f);
    // LDH_addr_A(hDMATransfer);
    hram->hDMATransfer = 0x3f;
    // CALL(aDelayFrame);
    DelayFrame();

    // POP_AF;
    // LDH_addr_A(rSVBK);
    // RET;
    wbank_pop;
}
