#include "../constants.h"
#include "window.h"
#include "menu.h"
#include "../engine/overworld/init_map.h"
#include "../engine/gfx/dma_transfer.h"
#include "../engine/gfx/load_overworld_font.h"
#include "../engine/events/map_name_sign.h"
#include "text.h"
#include "delay.h"
#include "map_objects.h"
#include "gfx.h"
#include "map.h"

void RefreshScreen(void){
    return RefreshScreen_Conv();
    // RET;
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
    ClearWindowData_Conv2();
    // LDH_A_addr(hROMBank);
    // PUSH_AF;
    // LD_A(BANK(aReanchorBGMap_NoOAMUpdate));  // aka BANK(LoadFonts_NoOAMUpdate)
    // RST(aBankswitch);

    // CALL(aReanchorBGMap_NoOAMUpdate);
    ReanchorBGMap_NoOAMUpdate_Conv();
    // CALL(av_OpenAndCloseMenu_HDMATransferTilemapAndAttrmap);
    v_OpenAndCloseMenu_HDMATransferTilemapAndAttrmap_Conv();
    // CALL(aLoadFonts_NoOAMUpdate);
    LoadFonts_NoOAMUpdate_Conv();

    // POP_AF;
    // RST(aBankswitch);
    // RET;
}

void CloseText(void){
    CloseText_Conv();
    RET;
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

void CloseText_Conv(void){
    // LDH_A_addr(hOAMUpdate);
    // PUSH_AF;
    // LD_A(0x1);
    // LDH_addr_A(hOAMUpdate);
    uint8_t oldoamupdate = hram->hOAMUpdate;
    hram->hOAMUpdate = 0x1;

    // CALL(aCloseText_CloseText);
// CloseText:
    // CALL(aClearWindowData);
    ClearWindowData_Conv2();
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = 0;
    // CALL(aOverworldTextModeSwitch);
    OverworldTextModeSwitch_Conv();
    // CALL(av_OpenAndCloseMenu_HDMATransferTilemapAndAttrmap);
    v_OpenAndCloseMenu_HDMATransferTilemapAndAttrmap_Conv();
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = 0;
    // CALL(aSafeUpdateSprites);
    SafeUpdateSprites_Conv();
    // LD_A(0x90);
    // LDH_addr_A(hWY);
    hram->hWY = 0x90;
    // CALL(aUpdatePlayerSprite);
    UpdatePlayerSprite_Conv();
    // FARCALL(aInitMapNameSign);
    InitMapNameSign_Conv();
    // FARCALL(aLoadOverworldFont);
    LoadOverworldFont_Conv();
    // RET;

    // POP_AF;
    // LDH_addr_A(hOAMUpdate);
    hram->hOAMUpdate = oldoamupdate;
    // LD_HL(wVramState);
    // RES_hl(6);
    // RET;
    bit_reset(wram->wVramState, 6);
}

void OpenText(void){
    OpenText_Conv();
    RET;
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
    ClearWindowData_Conv2();
    // LDH_A_addr(hROMBank);
    // PUSH_AF;
    // LD_A(BANK(aReanchorBGMap_NoOAMUpdate));  // aka BANK(LoadFonts_NoOAMUpdate)
    // RST(aBankswitch);

    // CALL(aReanchorBGMap_NoOAMUpdate);  // clear bgmap
    ReanchorBGMap_NoOAMUpdate_Conv();
    // CALL(aSpeechTextbox);
    SpeechTextbox_Conv2();
    // CALL(av_OpenAndCloseMenu_HDMATransferTilemapAndAttrmap);  // anchor bgmap
    v_OpenAndCloseMenu_HDMATransferTilemapAndAttrmap_Conv();  // anchor bgmap
    // CALL(aLoadFonts_NoOAMUpdate);  // load font
    LoadFonts_NoOAMUpdate_Conv();
    // POP_AF;
    // RST(aBankswitch);

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
    OpenAndCloseMenu_HDMATransferTilemapAndAttrmap_Conv();

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
