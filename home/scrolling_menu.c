#include "../constants.h"
#include "scrolling_menu.h"
#include "delay.h"
#include "joypad.h"
#include "menu.h"
#include "tilemap.h"
#include "time_palettes.h"
#include "text.h"
#include "../engine/menus/scrolling_menu.h"

static void ScrollingMenu_UpdatePalettes(void){
    // LD_HL(wVramState);
    // BIT_hl(0);
    // JP_NZ (mUpdateTimePals);
    if(bit_test(wram->wVramState, 0))
        return UpdateTimePals();
    // JP(mSetPalettes);
    SetPalettes();
}

uint8_t ScrollingMenu(void){
    // CALL(aCopyMenuData);
    const struct MenuData* data = GetMenuData();
    // LDH_A_addr(hROMBank);
    // PUSH_AF;

    // LD_A(BANK(av_ScrollingMenu));  // aka BANK(_InitScrollingMenu)
    // RST(aBankswitch);

    // CALL(av_InitScrollingMenu);
    v_InitScrollingMenu(data);
    // CALL(aScrollingMenu_UpdatePalettes);
    ScrollingMenu_UpdatePalettes();
    // CALL(av_ScrollingMenu);
    v_ScrollingMenu(data);

    // POP_AF;
    // RST(aBankswitch);

    // LD_A_addr(wMenuJoypad);
    // RET;
    return wram->wMenuJoypad;
}

void InitScrollingMenu(void){
    // LD_A_addr(wMenuBorderTopCoord);
    // DEC_A;
    // LD_B_A;
    // LD_A_addr(wMenuBorderBottomCoord);
    // SUB_A_B;
    // LD_D_A;
    uint8_t d = wram->wMenuBorderBottomCoord - (wram->wMenuBorderTopCoord - 1);
    // LD_A_addr(wMenuBorderLeftCoord);
    // DEC_A;
    // LD_C_A;
    // LD_A_addr(wMenuBorderRightCoord);
    // SUB_A_C;
    // LD_E_A;
    uint8_t e = wram->wMenuBorderRightCoord - (wram->wMenuBorderLeftCoord - 1);
    // PUSH_DE;
    // CALL(aCoord2Tile);
    // POP_BC;
    // JP(mTextbox);
    Textbox(Coord2Tile(wram->wMenuBorderLeftCoord - 1, wram->wMenuBorderTopCoord - 1), d, e);
}

uint8_t JoyTextDelay_ForcehJoyDown(void){
    // CALL(aDelayFrame);
    DelayFrame();

    // LDH_A_addr(hInMenu);
    // PUSH_AF;
    uint8_t inMenu = hram.hInMenu;
    // LD_A(0x1);
    // LDH_addr_A(hInMenu);
    hram.hInMenu = TRUE;
    // CALL(aJoyTextDelay);
    JoyTextDelay();
    // POP_AF;
    // LDH_addr_A(hInMenu);
    hram.hInMenu = inMenu;

    // LDH_A_addr(hJoyLast);
    // AND_A(D_RIGHT + D_LEFT + D_UP + D_DOWN);
    // LD_C_A;
    // LDH_A_addr(hJoyPressed);
    // AND_A(A_BUTTON + B_BUTTON + SELECT + START);
    // OR_A_C;
    // LD_C_A;
    // RET;
    return (hram.hJoyLast & (D_RIGHT + D_LEFT + D_UP + D_DOWN)) | (hram.hJoyPressed & (A_BUTTON + B_BUTTON + SELECT + START));
}
