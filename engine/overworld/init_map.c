#include "../../constants.h"
#include "init_map.h"
#include "../../home/gfx.h"
#include "../../home/sprite_updates.h"
#include "../../home/window.h"

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
