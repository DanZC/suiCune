#include "../../constants.h"
#include "buena_menu.h"
#include "../../home/menu.h"
#include "../../home/map_objects.h"
#include "../../home/delay.h"
#include "../../home/tilemap.h"

static bool AskRememberPassword_DoMenu(void){
    // LD_BC((14 << 8) | 7);
    // PUSH_BC;
    // LD_HL(mYesNoMenuHeader);
    // CALL(aCopyMenuHeader);
    CopyMenuHeader(&YesNoMenuHeader);
    // POP_BC;
    // LD_A_B;
    // LD_addr_A(wMenuBorderLeftCoord);
    wram->wMenuBorderLeftCoord = 14;
    // ADD_A(0x5);
    // LD_addr_A(wMenuBorderRightCoord);
    wram->wMenuBorderRightCoord = wram->wMenuBorderLeftCoord + 0x5;
    // LD_A_C;
    // LD_addr_A(wMenuBorderTopCoord);
    wram->wMenuBorderTopCoord = 7;
    // ADD_A(0x4);
    // LD_addr_A(wMenuBorderBottomCoord);
    wram->wMenuBorderBottomCoord = wram->wMenuBorderTopCoord + 0x4;
    // CALL(aPushWindow);
    PushWindow();
    // CALL(aVerticalMenu);
    bool cancel = VerticalMenu();
    // PUSH_AF;
    // LD_C(15);
    // CALL(aDelayFrames);
    DelayFrames(15);
    // CALL(aBuena_ExitMenu);
    Buena_ExitMenu();
    // POP_AF;
    // IF_C goto refused;
    // LD_A_addr(wMenuCursorY);
    // CP_A(0x2);
    // IF_Z goto refused;
    if(cancel || wram->wMenuCursorY == 0x2) {
    // refused:
        // LD_A(0x2);
        // LD_addr_A(wMenuCursorY);
        wram->wMenuCursorY = 0x2;
        // SCF;
        // RET;
        return true;
    }
    // AND_A_A;
    // RET;
    return false;
}

void AskRememberPassword(void){
    // CALL(aAskRememberPassword_DoMenu);
    bool cancel = AskRememberPassword_DoMenu();
    // LD_A(0x0);
    // IF_C goto okay;
    // LD_A(0x1);

// okay:
    // LD_addr_A(wScriptVar);
    wram->wScriptVar = (cancel)? 0x0: 0x1;
    // RET;
}

void Buena_ExitMenu(void){
    // LDH_A_addr(hOAMUpdate);
    // PUSH_AF;
    uint8_t oamUpdate = hram.hOAMUpdate;
    // CALL(aExitMenu);
    ExitMenu();
    // CALL(aUpdateSprites);
    UpdateSprites();
    // XOR_A_A;
    // LDH_addr_A(hOAMUpdate);
    hram.hOAMUpdate = 0;
    // CALL(aDelayFrame);
    DelayFrame();
    // LD_A(0x1);
    // LDH_addr_A(hOAMUpdate);
    hram.hOAMUpdate = 0x1;
    // CALL(aApplyTilemap);
    ApplyTilemap();
    // POP_AF;
    // LDH_addr_A(hOAMUpdate);
    hram.hOAMUpdate = oamUpdate;
    // RET;
}
