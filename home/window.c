#include "../constants.h"
#include "window.h"
#include "menu.h"
#include "../engine/overworld/init_map.h"
#include "../engine/gfx/dma_transfer.h"
#include "delay.h"
#include "map_objects.h"

void RefreshScreen(void){
        CALL(aClearWindowData);
    LDH_A_addr(hROMBank);
    PUSH_AF;
    LD_A(BANK(aReanchorBGMap_NoOAMUpdate));  // aka BANK(LoadFonts_NoOAMUpdate)
    RST(aBankswitch);

    CALL(aReanchorBGMap_NoOAMUpdate);
    CALL(av_OpenAndCloseMenu_HDMATransferTilemapAndAttrmap);
    CALL(aLoadFonts_NoOAMUpdate);

    POP_AF;
    RST(aBankswitch);
    RET;

}

void RefreshScreen_Conv(void){
    // CALL(aClearWindowData);
    ClearWindowData_Conv();
    // LDH_A_addr(hROMBank);
    // PUSH_AF;
    // LD_A(BANK(aReanchorBGMap_NoOAMUpdate));  // aka BANK(LoadFonts_NoOAMUpdate)
    // RST(aBankswitch);
    uint8_t oldbank = gb_read(hROMBank);
    Bankswitch_Conv(BANK(aReanchorBGMap_NoOAMUpdate));

    CALL(aReanchorBGMap_NoOAMUpdate);
    // ReanchorBGMap_NoOAMUpdate();
    // CALL(av_OpenAndCloseMenu_HDMATransferTilemapAndAttrmap);
    v_OpenAndCloseMenu_HDMATransferTilemapAndAttrmap_Conv();
    CALL(aLoadFonts_NoOAMUpdate);
    // LoadFonts_NoOAMUpdate();

    // POP_AF;
    // RST(aBankswitch);
    Bankswitch_Conv(oldbank);
    // RET;
}

void CloseText(void){
    LDH_A_addr(hOAMUpdate);
    PUSH_AF;
    LD_A(0x1);
    LDH_addr_A(hOAMUpdate);

    CALL(aCloseText_CloseText);

    POP_AF;
    LDH_addr_A(hOAMUpdate);
    LD_HL(wVramState);
    RES_hl(6);
    RET;


CloseText:
        CALL(aClearWindowData);
    XOR_A_A;
    LDH_addr_A(hBGMapMode);
    CALL(aOverworldTextModeSwitch);
    CALL(av_OpenAndCloseMenu_HDMATransferTilemapAndAttrmap);
    XOR_A_A;
    LDH_addr_A(hBGMapMode);
    CALL(aSafeUpdateSprites);
    LD_A(0x90);
    LDH_addr_A(hWY);
    CALL(aUpdatePlayerSprite);
    FARCALL(aInitMapNameSign);
    FARCALL(aLoadOverworldFont);
    RET;

}

void OpenText(void){
    CALL(aClearWindowData);
    LDH_A_addr(hROMBank);
    PUSH_AF;
    LD_A(BANK(aReanchorBGMap_NoOAMUpdate));  // aka BANK(LoadFonts_NoOAMUpdate)
    RST(aBankswitch);

    CALL(aReanchorBGMap_NoOAMUpdate);  // clear bgmap
    CALL(aSpeechTextbox);
    CALL(av_OpenAndCloseMenu_HDMATransferTilemapAndAttrmap);  // anchor bgmap
    CALL(aLoadFonts_NoOAMUpdate);  // load font
    POP_AF;
    RST(aBankswitch);

    RET;

}

void OpenText_Conv(void){
    // CALL(aClearWindowData);
    ClearWindowData_Conv();
    // LDH_A_addr(hROMBank);
    // PUSH_AF;
    // LD_A(BANK(aReanchorBGMap_NoOAMUpdate));  // aka BANK(LoadFonts_NoOAMUpdate)
    // RST(aBankswitch);
    uint8_t oldbank = gb_read(hROMBank);
    Bankswitch_Conv(BANK(aReanchorBGMap_NoOAMUpdate));

    CALL(aReanchorBGMap_NoOAMUpdate);  // clear bgmap
    CALL(aSpeechTextbox);
    // CALL(av_OpenAndCloseMenu_HDMATransferTilemapAndAttrmap);  // anchor bgmap
    v_OpenAndCloseMenu_HDMATransferTilemapAndAttrmap_Conv();  // anchor bgmap
    // CALL(aLoadFonts_NoOAMUpdate);  // load font
    LoadFonts_NoOAMUpdate_Conv();
    // POP_AF;
    // RST(aBankswitch);
    Bankswitch_Conv(oldbank);

    // RET;

}

void v_OpenAndCloseMenu_HDMATransferTilemapAndAttrmap(void){
    LDH_A_addr(hOAMUpdate);
    PUSH_AF;
    LD_A(0x1);
    LDH_addr_A(hOAMUpdate);

    FARCALL(aOpenAndCloseMenu_HDMATransferTilemapAndAttrmap);

    POP_AF;
    LDH_addr_A(hOAMUpdate);
    RET;

}

void v_OpenAndCloseMenu_HDMATransferTilemapAndAttrmap_Conv(void){
    // LDH_A_addr(hOAMUpdate);
    // PUSH_AF;
    // LD_A(0x1);
    // LDH_addr_A(hOAMUpdate);
    uint8_t oldoamupdate = hram->hOAMUpdate;
    hram->hOAMUpdate = 0x1;

    // FARCALL(aOpenAndCloseMenu_HDMATransferTilemapAndAttrmap);
    farcall(OpenAndCloseMenu_HDMATransferTilemapAndAttrmap);

    // POP_AF;
    // LDH_addr_A(hOAMUpdate);
    // RET;
    hram->hOAMUpdate = oldoamupdate;
}

void SafeUpdateSprites(void){
    LDH_A_addr(hOAMUpdate);
    PUSH_AF;
    LDH_A_addr(hBGMapMode);
    PUSH_AF;
    XOR_A_A;
    LDH_addr_A(hBGMapMode);
    LD_A(0x1);
    LDH_addr_A(hOAMUpdate);

    CALL(aUpdateSprites);

    XOR_A_A;
    LDH_addr_A(hOAMUpdate);
    CALL(aDelayFrame);
    POP_AF;
    LDH_addr_A(hBGMapMode);
    POP_AF;
    LDH_addr_A(hOAMUpdate);
    RET;

}

void SafeUpdateSprites_Conv(void){
    // LDH_A_addr(hOAMUpdate);
    // PUSH_AF;
    uint8_t oamupdate = hram->hOAMUpdate;
    // LDH_A_addr(hBGMapMode);
    // PUSH_AF;
    uint8_t bgmapmode = hram->hBGMapMode;
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = 0;
    // LD_A(0x1);
    // LDH_addr_A(hOAMUpdate);
    hram->hOAMUpdate = 0x1;

    // CALL(aUpdateSprites);
    UpdateSprites_Conv();

    // XOR_A_A;
    // LDH_addr_A(hOAMUpdate);
    hram->hOAMUpdate = 0x0;
    // CALL(aDelayFrame);
    DelayFrame();
    // POP_AF;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = bgmapmode;
    // POP_AF;
    // LDH_addr_A(hOAMUpdate);
    hram->hOAMUpdate = oamupdate;
    // RET;
}

void SetCarryFlag(void){
    //  //  unreferenced
    SCF;
    RET;

}
