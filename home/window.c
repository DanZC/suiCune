#include "../constants.h"
#include "window.h"

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

void SetCarryFlag(void){
    //  //  unreferenced
    SCF;
    RET;

}
