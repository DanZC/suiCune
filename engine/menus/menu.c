#include "../../constants.h"
#include "menu.h"
#include "../../home/delay.h"
#include "../../home/menu.h"
#include "../../home/array.h"
#include "../../home/time_palettes.h"
#include "../../home/joypad.h"
#include "../../home/tilemap.h"
#include "../../home/text.h"

void v_2DMenu_(void){
    LD_HL(mCopyMenuData);
    LD_A_addr(wMenuData_2DMenuItemStringsBank);
    RST(aFarCall);

    CALL(aDraw2DMenu);
    CALL(aUpdateSprites);
    CALL(aApplyTilemap);
    CALL(aGet2DMenuSelection);
    RET;

}

void v_InterpretBattleMenu(void){
    LD_HL(mCopyMenuData);
    LD_A_addr(wMenuData_2DMenuItemStringsBank);
    RST(aFarCall);

    CALL(aDraw2DMenu);
    FARCALL(aMobileTextBorder);
    CALL(aUpdateSprites);
    CALL(aApplyTilemap);
    CALL(aGet2DMenuSelection);
    RET;

}

void v_InterpretMobileMenu(void){
    LD_HL(mCopyMenuData);
    LD_A_addr(wMenuData_2DMenuItemStringsBank);
    RST(aFarCall);

    CALL(aDraw2DMenu);
    FARCALL(aMobileTextBorder);
    CALL(aUpdateSprites);
    CALL(aApplyTilemap);
    CALL(aInit2DMenuCursorPosition);
    LD_HL(w2DMenuFlags1);
    SET_hl(7);

loop:
    CALL(aDelayFrame);
    FARCALL(aFunction10032e);
    LD_A_addr(wcd2b);
    AND_A_A;
    IF_NZ goto quit;
    CALL(aMobileMenuJoypad);
    LD_A_addr(wMenuJoypadFilter);
    AND_A_C;
    IF_Z goto loop;
    CALL(aMobile_GetMenuSelection);
    RET;


quit:
    LD_A_addr(w2DMenuNumCols);
    LD_C_A;
    LD_A_addr(w2DMenuNumRows);
    CALL(aSimpleMultiply);
    LD_addr_A(wMenuCursorPosition);
    AND_A_A;
    RET;

}

void Draw2DMenu(void){
    XOR_A_A;
    LDH_addr_A(hBGMapMode);
    CALL(aMenuBox);
    CALL(aPlace2DMenuItemStrings);
    RET;

}

void Get2DMenuSelection(void){
    CALL(aInit2DMenuCursorPosition);
    CALL(aStaticMenuJoypad);
    CALL(aMenuClickSound);
    return Mobile_GetMenuSelection();
}

void Mobile_GetMenuSelection(void){
    LD_A_addr(wMenuDataFlags);
    BIT_A(1);
    IF_Z goto skip;
    CALL(aGetMenuJoypad);
    BIT_A(SELECT_F);
    IF_NZ goto quit1;


skip:
    LD_A_addr(wMenuDataFlags);
    BIT_A(0);
    IF_NZ goto skip2;
    CALL(aGetMenuJoypad);
    BIT_A(B_BUTTON_F);
    IF_NZ goto quit2;


skip2:
    LD_A_addr(w2DMenuNumCols);
    LD_C_A;
    LD_A_addr(wMenuCursorY);
    DEC_A;
    CALL(aSimpleMultiply);
    LD_C_A;
    LD_A_addr(wMenuCursorX);
    ADD_A_C;
    LD_addr_A(wMenuCursorPosition);
    AND_A_A;
    RET;


quit1:
    SCF;
    RET;


quit2:
    SCF;
    RET;

}

void Get2DMenuNumberOfColumns(void){
    LD_A_addr(wMenuData_2DMenuDimensions);
    AND_A(0xf);
    RET;

}

uint8_t Get2DMenuNumberOfColumns_Conv(void){
    // LD_A_addr(wMenuData_2DMenuDimensions);
    // AND_A(0xf);
    // RET;
    return wram->wMenuData_2DMenuDimensions & 0xf;
}

void Get2DMenuNumberOfRows(void){
    LD_A_addr(wMenuData_2DMenuDimensions);
    SWAP_A;
    AND_A(0xf);
    RET;

}

uint8_t Get2DMenuNumberOfRows_Conv(void){
    // LD_A_addr(wMenuData_2DMenuDimensions);
    // SWAP_A;
    // AND_A(0xf);
    // RET;
    return (wram->wMenuData_2DMenuDimensions >> 4) & 0xf;
}

void Place2DMenuItemStrings(void){
    LD_HL(wMenuData_2DMenuItemStringsAddr);
    LD_E_hl;
    INC_HL;
    LD_D_hl;
    CALL(aGetMenuTextStartCoord);
    CALL(aCoord2Tile);
    CALL(aGet2DMenuNumberOfRows);
    LD_B_A;

row:
    PUSH_BC;
    PUSH_HL;
    CALL(aGet2DMenuNumberOfColumns);
    LD_C_A;

col:
    PUSH_BC;
    LD_A_addr(wMenuData_2DMenuItemStringsBank);
    CALL(aPlace2DMenuItemName);
    INC_DE;
    LD_A_addr(wMenuData_2DMenuSpacing);
    LD_C_A;
    LD_B(0);
    ADD_HL_BC;
    POP_BC;
    DEC_C;
    IF_NZ goto col;
    POP_HL;
    LD_BC(2 * SCREEN_WIDTH);
    ADD_HL_BC;
    POP_BC;
    DEC_B;
    IF_NZ goto row;
    LD_HL(wMenuData_2DMenuFunctionAddr);
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    OR_A_H;
    RET_Z ;
    LD_A_addr(wMenuData_2DMenuFunctionBank);
    RST(aFarCall);
    RET;

}

void Init2DMenuCursorPosition(void){
    CALL(aGetMenuTextStartCoord);
    LD_A_B;
    LD_addr_A(w2DMenuCursorInitY);
    DEC_C;
    LD_A_C;
    LD_addr_A(w2DMenuCursorInitX);
    CALL(aGet2DMenuNumberOfRows);
    LD_addr_A(w2DMenuNumRows);
    CALL(aGet2DMenuNumberOfColumns);
    LD_addr_A(w2DMenuNumCols);
    CALL(aInit2DMenuCursorPosition_InitFlags_a);
    CALL(aInit2DMenuCursorPosition_InitFlags_b);
    CALL(aInit2DMenuCursorPosition_InitFlags_c);
    LD_A_addr(w2DMenuNumCols);
    LD_E_A;
    LD_A_addr(wMenuCursorPosition);
    LD_B_A;
    XOR_A_A;
    LD_D(0);

loop:
    INC_D;
    ADD_A_E;
    CP_A_B;
    IF_C goto loop;
    SUB_A_E;
    LD_C_A;
    LD_A_B;
    SUB_A_C;
    AND_A_A;
    IF_Z goto reset1;
    CP_A_E;
    IF_Z goto okay1;
    IF_C goto okay1;

reset1:
    LD_A(1);

okay1:
    LD_addr_A(wMenuCursorX);
    LD_A_addr(w2DMenuNumRows);
    LD_E_A;
    LD_A_D;
    AND_A_A;
    IF_Z goto reset2;
    CP_A_E;
    IF_Z goto okay2;
    IF_C goto okay2;

reset2:
    LD_A(1);

okay2:
    LD_addr_A(wMenuCursorY);
    XOR_A_A;
    LD_addr_A(wCursorOffCharacter);
    LD_addr_A(wCursorCurrentTile);
    LD_addr_A(wCursorCurrentTile + 1);
    RET;


InitFlags_a:
    XOR_A_A;
    LD_HL(w2DMenuFlags1);
    LD_hli_A;
    LD_hld_A;
    LD_A_addr(wMenuDataFlags);
    BIT_A(5);
    RET_Z ;
    SET_hl(5);
    SET_hl(4);
    RET;


InitFlags_b:
    LD_A_addr(wMenuData_2DMenuSpacing);
    OR_A(0x20);
    LD_addr_A(w2DMenuCursorOffsets);
    RET;


InitFlags_c:
    LD_HL(wMenuDataFlags);
    LD_A(A_BUTTON);
    BIT_hl(0);
    IF_NZ goto skip;
    OR_A(B_BUTTON);

skip:
    BIT_hl(1);
    IF_Z goto skip2;
    OR_A(SELECT);

skip2:
    LD_addr_A(wMenuJoypadFilter);
    RET;

}

void v_StaticMenuJoypad(void){
    CALL(aPlace2DMenuCursor);
    return v_ScrollingMenuJoypad();
}

void v_StaticMenuJoypad_Conv(void){
    // CALL(aPlace2DMenuCursor);
    Place2DMenuCursor_Conv();
    return v_ScrollingMenuJoypad_Conv();
}

void v_ScrollingMenuJoypad(void){
    LD_HL(w2DMenuFlags2);
    RES_hl(7);
    LDH_A_addr(hBGMapMode);
    PUSH_AF;
    CALL(aMenuJoypadLoop);
    POP_AF;
    LDH_addr_A(hBGMapMode);
    RET;

}

void v_ScrollingMenuJoypad_Conv(void){
    // LD_HL(w2DMenuFlags2);
    // RES_hl(7);
    bit_reset(wram->w2DMenuFlags2, 7);
    // LDH_A_addr(hBGMapMode);
    // PUSH_AF;
    uint8_t temp = hram->hBGMapMode;
    // CALL(aMenuJoypadLoop);
    // POP_AF;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = temp;
    // RET;
}

void MobileMenuJoypad(void){
    LD_HL(w2DMenuFlags2);
    RES_hl(7);
    LDH_A_addr(hBGMapMode);
    PUSH_AF;
    CALL(aMove2DMenuCursor);
    CALL(aDo2DMenuRTCJoypad);
    IF_NC goto skip_joypad;
    CALL(av_2DMenuInterpretJoypad);

skip_joypad:
    POP_AF;
    LDH_addr_A(hBGMapMode);
    CALL(aGetMenuJoypad);
    LD_C_A;
    RET;

}

void Function241d5(void){
//  //  unreferenced
    CALL(aPlace2DMenuCursor);

loop:
    CALL(aMove2DMenuCursor);
    CALL(aHDMATransferTilemapToWRAMBank3);  // BUG: This function is in another bank.
    CALL(aFunction241d5_loop2);
    IF_NC goto done;
    CALL(av_2DMenuInterpretJoypad);
    IF_C goto done;
    LD_A_addr(w2DMenuFlags1);
    BIT_A(7);
    IF_NZ goto done;
    CALL(aGetMenuJoypad);
    LD_C_A;
    LD_A_addr(wMenuJoypadFilter);
    AND_A_C;
    IF_Z goto loop;


done:
    RET;


loop2:
    CALL(aMenu_WasButtonPressed);
    RET_C ;
    LD_C(1);
    LD_B(3);
    CALL(aAdvanceMobileInactivityTimerAndCheckExpired);  // BUG: This function is in another bank.
    RET_C ;
    FARCALL(aFunction100337);
    RET_C ;
    LD_A_addr(w2DMenuFlags1);
    BIT_A(7);
    IF_Z goto loop2;
    AND_A_A;
    RET;

}

void MenuJoypadLoop(void){

loop:
    CALL(aMove2DMenuCursor);
    CALL(aMenuJoypadLoop_BGMap_OAM);
    CALL(aDo2DMenuRTCJoypad);
    IF_NC goto done;
    CALL(av_2DMenuInterpretJoypad);
    IF_C goto done;
    LD_A_addr(w2DMenuFlags1);
    BIT_A(7);
    IF_NZ goto done;
    CALL(aGetMenuJoypad);
    LD_B_A;
    LD_A_addr(wMenuJoypadFilter);
    AND_A_B;
    IF_Z goto loop;


done:
    RET;


BGMap_OAM:
    LDH_A_addr(hOAMUpdate);
    PUSH_AF;
    LD_A(0x1);
    LDH_addr_A(hOAMUpdate);
    CALL(aWaitBGMap);
    POP_AF;
    LDH_addr_A(hOAMUpdate);
    XOR_A_A;
    LDH_addr_A(hBGMapMode);
    RET;

}

static void MenuJoypadLoop_BGMap_OAM(void) {
// BGMap_OAM:
    // LDH_A_addr(hOAMUpdate);
    // PUSH_AF;
    uint8_t temp = hram->hOAMUpdate;
    // LD_A(0x1);
    // LDH_addr_A(hOAMUpdate);
    hram->hOAMUpdate = 0x1;
    // CALL(aWaitBGMap);
    WaitBGMap_Conv();
    // POP_AF;
    // LDH_addr_A(hOAMUpdate);
    hram->hOAMUpdate = temp;
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = 0;
    // RET;
}

void MenuJoypadLoop_Conv(void){
    do {
    // loop:
        // CALL(aMove2DMenuCursor);
        Move2DMenuCursor_Conv();
        // CALL(aMenuJoypadLoop_BGMap_OAM);
        MenuJoypadLoop_BGMap_OAM();
        // CALL(aDo2DMenuRTCJoypad);
        // IF_NC return;
        if(!Do2DMenuRTCJoypad_Conv()) 
            return;
        // CALL(av_2DMenuInterpretJoypad);
        // IF_C return;
        if(v_2DMenuInterpretJoypad_Conv())
            return;
        // LD_A_addr(w2DMenuFlags1);
        // BIT_A(7);
        // IF_NZ goto done;
        if(bit_test(wram->w2DMenuFlags1, 7))
            return;
        // CALL(aGetMenuJoypad);
        // LD_B_A;
        // LD_A_addr(wMenuJoypadFilter);
        // AND_A_B;
        // IF_Z goto loop;
    } while((GetMenuJoypad_Conv() & wram->wMenuJoypadFilter) == 0);

// done:
    // RET;
}

void Do2DMenuRTCJoypad(void){

loopRTC:
    CALL(aUpdateTimeAndPals);
    CALL(aMenu_WasButtonPressed);
    RET_C ;
    LD_A_addr(w2DMenuFlags1);
    BIT_A(7);
    IF_Z goto loopRTC;
    AND_A_A;
    RET;

}

// Return true if button was pressed. False otherwise.
bool Do2DMenuRTCJoypad_Conv(void){
    do {
    // loopRTC:
        // CALL(aUpdateTimeAndPals);
        UpdateTimeAndPals_Conv();
        // CALL(aMenu_WasButtonPressed);
        // RET_C ;
        if(Menu_WasButtonPressed_Conv())
            return true;
        // LD_A_addr(w2DMenuFlags1);
        // BIT_A(7);
        // IF_Z goto loopRTC;
    } while(!bit_test(wram->w2DMenuFlags1, 7));
    // AND_A_A;
    // RET;
    return false;
}

void Menu_WasButtonPressed(void){
    LD_A_addr(w2DMenuFlags1);
    BIT_A(6);
    IF_Z goto skip_to_joypad;
    CALLFAR(aPlaySpriteAnimationsAndDelayFrame);


skip_to_joypad:
    CALL(aJoyTextDelay);
    CALL(aGetMenuJoypad);
    AND_A_A;
    RET_Z ;
    SCF;
    RET;

}

static void Menu_WasButtonPressed_Conv_PlaySpriteAnimationsAndDelayFrame(void) {
    PUSH_AF;
    PUSH_BC;
    PUSH_DE;
    PUSH_HL;
    CALLFAR(aPlaySpriteAnimationsAndDelayFrame);
    POP_HL;
    POP_DE;
    POP_BC;
    POP_AF;
}

bool Menu_WasButtonPressed_Conv(void){
    // LD_A_addr(w2DMenuFlags1);
    // BIT_A(6);
    // IF_Z goto skip_to_joypad;
    if(bit_test(wram->w2DMenuFlags1, 6)) {
        // CALLFAR(aPlaySpriteAnimationsAndDelayFrame);
        Menu_WasButtonPressed_Conv_PlaySpriteAnimationsAndDelayFrame();
    }


// skip_to_joypad:
    // CALL(aJoyTextDelay);
    JoyTextDelay_Conv();
    // CALL(aGetMenuJoypad);
    // AND_A_A;
    // RET_Z ;
    if(!GetMenuJoypad_Conv())
        return false;
    // SCF;
    // RET;
    return true;
}

void v_2DMenuInterpretJoypad(void){
    CALL(aGetMenuJoypad);
    BIT_A(A_BUTTON_F);
    JP_NZ (mv_2DMenuInterpretJoypad_a_b_start_select);
    BIT_A(B_BUTTON_F);
    JP_NZ (mv_2DMenuInterpretJoypad_a_b_start_select);
    BIT_A(SELECT_F);
    JP_NZ (mv_2DMenuInterpretJoypad_a_b_start_select);
    BIT_A(START_F);
    JP_NZ (mv_2DMenuInterpretJoypad_a_b_start_select);
    BIT_A(D_RIGHT_F);
    IF_NZ goto d_right;
    BIT_A(D_LEFT_F);
    IF_NZ goto d_left;
    BIT_A(D_UP_F);
    IF_NZ goto d_up;
    BIT_A(D_DOWN_F);
    IF_NZ goto d_down;
    AND_A_A;
    RET;


set_bit_7:
    LD_HL(w2DMenuFlags2);
    SET_hl(7);
    SCF;
    RET;


d_down:
    LD_HL(wMenuCursorY);
    LD_A_addr(w2DMenuNumRows);
    CP_A_hl;
    IF_Z goto check_wrap_around_down;
    INC_hl;
    XOR_A_A;
    RET;


check_wrap_around_down:
    LD_A_addr(w2DMenuFlags1);
    BIT_A(5);
    IF_NZ goto wrap_around_down;
    BIT_A(3);
    JP_NZ (mv_2DMenuInterpretJoypad_set_bit_7);
    XOR_A_A;
    RET;


wrap_around_down:
    LD_hl(0x1);
    XOR_A_A;
    RET;


d_up:
    LD_HL(wMenuCursorY);
    LD_A_hl;
    DEC_A;
    IF_Z goto check_wrap_around_up;
    LD_hl_A;
    XOR_A_A;
    RET;


check_wrap_around_up:
    LD_A_addr(w2DMenuFlags1);
    BIT_A(5);
    IF_NZ goto wrap_around_up;
    BIT_A(2);
    JP_NZ (mv_2DMenuInterpretJoypad_set_bit_7);
    XOR_A_A;
    RET;


wrap_around_up:
    LD_A_addr(w2DMenuNumRows);
    LD_hl_A;
    XOR_A_A;
    RET;


d_left:
    LD_HL(wMenuCursorX);
    LD_A_hl;
    DEC_A;
    IF_Z goto check_wrap_around_left;
    LD_hl_A;
    XOR_A_A;
    RET;


check_wrap_around_left:
    LD_A_addr(w2DMenuFlags1);
    BIT_A(4);
    IF_NZ goto wrap_around_left;
    BIT_A(1);
    JP_NZ (mv_2DMenuInterpretJoypad_set_bit_7);
    XOR_A_A;
    RET;


wrap_around_left:
    LD_A_addr(w2DMenuNumCols);
    LD_hl_A;
    XOR_A_A;
    RET;


d_right:
    LD_HL(wMenuCursorX);
    LD_A_addr(w2DMenuNumCols);
    CP_A_hl;
    IF_Z goto check_wrap_around_right;
    INC_hl;
    XOR_A_A;
    RET;


check_wrap_around_right:
    LD_A_addr(w2DMenuFlags1);
    BIT_A(4);
    IF_NZ goto wrap_around_right;
    BIT_A(0);
    JP_NZ (mv_2DMenuInterpretJoypad_set_bit_7);
    XOR_A_A;
    RET;


wrap_around_right:
    LD_hl(0x1);
    XOR_A_A;
    RET;


a_b_start_select:
    XOR_A_A;
    RET;

}

bool v_2DMenuInterpretJoypad_Conv(void){
    // CALL(aGetMenuJoypad);
    uint8_t a = GetMenuJoypad_Conv();
    // BIT_A(A_BUTTON_F);
    // JP_NZ (mv_2DMenuInterpretJoypad_a_b_start_select);
    // BIT_A(B_BUTTON_F);
    // JP_NZ (mv_2DMenuInterpretJoypad_a_b_start_select);
    // BIT_A(SELECT_F);
    // JP_NZ (mv_2DMenuInterpretJoypad_a_b_start_select);
    // BIT_A(START_F);
    // JP_NZ (mv_2DMenuInterpretJoypad_a_b_start_select);
    if(bit_test(a, A_BUTTON_F) || bit_test(a, B_BUTTON_F) || bit_test(a, SELECT_F) || bit_test(a, START_F)) {
    // a_b_start_select:
        // XOR_A_A;
        // RET;
        return false;
    }
    // BIT_A(D_RIGHT_F);
    // IF_NZ goto d_right;
    if(bit_test(a, D_RIGHT_F)) {
    // d_right:
        // LD_HL(wMenuCursorX);
        // LD_A_addr(w2DMenuNumCols);
        // CP_A_hl;
        // IF_Z goto check_wrap_around_right;
        if(wram->w2DMenuNumCols != wram->wMenuCursorX) {
            // INC_hl;
            wram->wMenuCursorX++;
            // XOR_A_A;
            // RET;
            return false;
        }


    // check_wrap_around_right:
        // LD_A_addr(w2DMenuFlags1);
        // BIT_A(4);
        // IF_NZ goto wrap_around_right;
        if(!bit_test(wram->w2DMenuFlags1, 4)) {
            // BIT_A(0);
            // JP_NZ (mv_2DMenuInterpretJoypad_set_bit_7);
            if(bit_test(wram->w2DMenuFlags1, 0)) {
            // set_bit_7:
                // LD_HL(w2DMenuFlags2);
                // SET_hl(7);
                bit_set(wram->w2DMenuFlags2, 7);
                // SCF;
                // RET;
                return true;
            }
            // XOR_A_A;
            // RET;
            return false;
        }


    // wrap_around_right:
        // LD_hl(0x1);
        wram->wMenuCursorX = 0x1;
        // XOR_A_A;
        // RET;
        return false;
    }
    // BIT_A(D_LEFT_F);
    // IF_NZ goto d_left;
    if(bit_test(a, D_LEFT_F)) {
    // d_left:
        // LD_HL(wMenuCursorX);
        // LD_A_hl;
        // DEC_A;
        // IF_Z goto check_wrap_around_left;
        if(wram->wMenuCursorX - 1 != 0) {
            // LD_hl_A;
            --wram->wMenuCursorX;
            // XOR_A_A;
            // RET;
            return false;
        }


    // check_wrap_around_left:
        // LD_A_addr(w2DMenuFlags1);
        // BIT_A(4);
        // IF_NZ goto wrap_around_left;
        if(bit_test(wram->w2DMenuFlags1, 4)) {
            // BIT_A(1);
            // JP_NZ (mv_2DMenuInterpretJoypad_set_bit_7);
            if(bit_test(wram->w2DMenuFlags1, 1)) {
            // set_bit_7:
                // LD_HL(w2DMenuFlags2);
                // SET_hl(7);
                bit_set(wram->w2DMenuFlags2, 7);
                // SCF;
                // RET;
                return true;
            }
            // XOR_A_A;
            // RET;
            return false;
        }


    // wrap_around_left:
        // LD_A_addr(w2DMenuNumCols);
        // LD_hl_A;
        wram->wMenuCursorX = wram->w2DMenuNumCols;
        // XOR_A_A;
        // RET;
        return false;
    }
    // BIT_A(D_UP_F);
    // IF_NZ goto d_up;
    if(bit_test(a, D_UP_F)) {
    // d_up:
        // LD_HL(wMenuCursorY);
        // LD_A_hl;
        // DEC_A;
        // IF_Z goto check_wrap_around_up;
        if(wram->wMenuCursorY - 1 != 0) {
            // LD_hl_A;
            --wram->wMenuCursorY;
            // XOR_A_A;
            // RET;
            return false;
        }


    // check_wrap_around_up:
        // LD_A_addr(w2DMenuFlags1);
        // BIT_A(5);
        // IF_NZ goto wrap_around_up;
        if(!bit_test(wram->w2DMenuFlags1, 5)) {
            // BIT_A(2);
            // JP_NZ (mv_2DMenuInterpretJoypad_set_bit_7);
            if(bit_test(wram->w2DMenuFlags1, 2)) {
            // set_bit_7:
                // LD_HL(w2DMenuFlags2);
                // SET_hl(7);
                bit_set(wram->w2DMenuFlags2, 7);
                // SCF;
                // RET;
                return true;
            }
            // XOR_A_A;
            // RET;
            return false;
        }


    // wrap_around_up:
        // LD_A_addr(w2DMenuNumRows);
        // LD_hl_A;
        wram->wMenuCursorY = wram->w2DMenuNumRows;
        // XOR_A_A;
        // RET;
        return false;
    }
    // BIT_A(D_DOWN_F);
    // IF_NZ goto d_down;
    if(bit_test(a, D_DOWN_F)) {
    // d_down:
        // LD_HL(wMenuCursorY);
        // LD_A_addr(w2DMenuNumRows);
        // CP_A_hl;
        // IF_Z goto check_wrap_around_down;
        if(wram->wMenuCursorY != wram->w2DMenuNumRows) {
            // INC_hl;
            ++wram->wMenuCursorY;
            // XOR_A_A;
            // RET;
            return false;
        }


    // check_wrap_around_down:
        // LD_A_addr(w2DMenuFlags1);
        // BIT_A(5);
        // IF_NZ goto wrap_around_down;
        if(!bit_test(wram->w2DMenuFlags1, 5)) {
            // BIT_A(3);
            // JP_NZ (mv_2DMenuInterpretJoypad_set_bit_7);
            if(bit_test(wram->w2DMenuFlags1, 3)) {
            // set_bit_7:
                // LD_HL(w2DMenuFlags2);
                // SET_hl(7);
                bit_set(wram->w2DMenuFlags2, 7);
                // SCF;
                // RET;
                return true;
            }
            // XOR_A_A;
            // RET;
            return false;
        }


    // wrap_around_down:
        // LD_hl(0x1);
        wram->wMenuCursorY = 0x1;
        // XOR_A_A;
        // RET;
        return false;
    }
    // AND_A_A;
    // RET;
    return false;
}

void Move2DMenuCursor(void){
    LD_HL(wCursorCurrentTile);
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    LD_A_hl;
    CP_A(0xed);
    JR_NZ (mPlace2DMenuCursor);
    LD_A_addr(wCursorOffCharacter);
    LD_hl_A;
    return Place2DMenuCursor();
}

void Move2DMenuCursor_Conv(void){
    // LD_HL(wCursorCurrentTile);
    uint8_t* hl = GBToRAMAddr(wram->wCursorCurrentTile);
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // LD_A_hl;
    // CP_A(0xed);
    if(*hl == 0xed) {
        // JR_NZ (mPlace2DMenuCursor);
        // LD_A_addr(wCursorOffCharacter);
        // LD_hl_A;
        *hl = wram->wCursorOffCharacter;
    }
    return Place2DMenuCursor_Conv();
}

void Place2DMenuCursor(void){
    LD_A_addr(w2DMenuCursorInitY);
    LD_B_A;
    LD_A_addr(w2DMenuCursorInitX);
    LD_C_A;
    CALL(aCoord2Tile);
    LD_A_addr(w2DMenuCursorOffsets);
    SWAP_A;
    AND_A(0xf);
    LD_C_A;
    LD_A_addr(wMenuCursorY);
    LD_B_A;
    XOR_A_A;
    DEC_B;
    IF_Z goto got_row;

row_loop:
    ADD_A_C;
    DEC_B;
    IF_NZ goto row_loop;


got_row:
    LD_C(SCREEN_WIDTH);
    CALL(aAddNTimes);
    LD_A_addr(w2DMenuCursorOffsets);
    AND_A(0xf);
    LD_C_A;
    LD_A_addr(wMenuCursorX);
    LD_B_A;
    XOR_A_A;
    DEC_B;
    IF_Z goto got_col;

col_loop:
    ADD_A_C;
    DEC_B;
    IF_NZ goto col_loop;


got_col:
    LD_C_A;
    ADD_HL_BC;
    LD_A_hl;
    CP_A(0xed);
    IF_Z goto cursor_on;
    LD_addr_A(wCursorOffCharacter);
    LD_hl(0xed);


cursor_on:
    LD_A_L;
    LD_addr_A(wCursorCurrentTile);
    LD_A_H;
    LD_addr_A(wCursorCurrentTile + 1);
    RET;

}

void Place2DMenuCursor_Conv(void){
    // LD_A_addr(w2DMenuCursorInitY);
    // LD_B_A;
    // LD_A_addr(w2DMenuCursorInitX);
    // LD_C_A;
    // CALL(aCoord2Tile);
    uint8_t* hl = Coord2Tile_Conv(wram->w2DMenuCursorInitX, wram->w2DMenuCursorInitY);
    // LD_A_addr(w2DMenuCursorOffsets);
    // SWAP_A;
    // AND_A(0xf);
    // LD_C_A;
    uint8_t c = ((wram->w2DMenuCursorOffsets >> 4) & 0xf);
    // LD_A_addr(wMenuCursorY);
    // LD_B_A;
    uint8_t b = wram->wMenuCursorY;
    // XOR_A_A;
    // DEC_B;
    // IF_Z goto got_row;
// row_loop:
    // ADD_A_C;
    // DEC_B;
    // IF_NZ goto row_loop;


// got_row:
    // LD_C(SCREEN_WIDTH);
    // CALL(aAddNTimes);
    hl = AddNTimes_Conv2(hl, SCREEN_WIDTH, (b - 1) * c);
    // LD_A_addr(w2DMenuCursorOffsets);
    // AND_A(0xf);
    // LD_C_A;
    c = wram->w2DMenuCursorOffsets & 0xf;
    // LD_A_addr(wMenuCursorX);
    // LD_B_A;
    b = wram->wMenuCursorX;
    // XOR_A_A;
    // DEC_B;
    // IF_Z goto got_col;

// col_loop:
    // ADD_A_C;
    // DEC_B;
    // IF_NZ goto col_loop;


// got_col:
    // LD_C_A;
    // ADD_HL_BC;
    hl += (b - 1) * c;
    // LD_A_hl;
    // CP_A(0xed);
    // IF_Z goto cursor_on;
    if(*hl != 0xed) {
        // LD_addr_A(wCursorOffCharacter);
        wram->wCursorOffCharacter = *hl;
        // LD_hl(0xed);
        *hl = 0xed;
    }


// cursor_on:
    // LD_A_L;
    // LD_addr_A(wCursorCurrentTile);
    // LD_A_H;
    // LD_addr_A(wCursorCurrentTile + 1);
    wram->wCursorCurrentTile = RAMAddrToGB(hl);
    // RET;

}

void v_PushWindow(void){
    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(MBANK(awWindowStack));
    LDH_addr_A(rSVBK);

    LD_HL(wWindowStackPointer);
    LD_E_hl;
    INC_HL;
    LD_D_hl;
    PUSH_DE;

    LD_B(wMenuHeaderEnd - wMenuHeader);
    LD_HL(wMenuHeader);

loop:
    LD_A_hli;
    LD_de_A;
    DEC_DE;
    DEC_B;
    IF_NZ goto loop;

//  If bit 6 or 7 of the menu flags is set, set bit 0 of the address
//  at 7:[wWindowStackPointer], and draw the menu using the coordinates from the header.
//  Otherwise, reset bit 0 of 7:[wWindowStackPointer].
    LD_A_addr(wMenuFlags);
    BIT_A(6);
    IF_NZ goto bit_6;
    BIT_A(7);
    IF_Z goto not_bit_7;


bit_6:
    LD_HL(wWindowStackPointer);
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    SET_hl(0);
    CALL(aMenuBoxCoord2Tile);
    CALL(av_PushWindow_copy);
    CALL(aMenuBoxCoord2Attr);
    CALL(av_PushWindow_copy);
    goto done;


not_bit_7:
    POP_HL;  // last-pushed register was de
    PUSH_HL;
    LD_A_hld;
    LD_L_hl;
    LD_H_A;
    RES_hl(0);


done:
    POP_HL;
    CALL(av_PushWindow_ret);  // empty function
    LD_A_H;
    LD_de_A;
    DEC_DE;
    LD_A_L;
    LD_de_A;
    DEC_DE;
    LD_HL(wWindowStackPointer);
    LD_hl_E;
    INC_HL;
    LD_hl_D;

    POP_AF;
    LDH_addr_A(rSVBK);
    LD_HL(wWindowStackSize);
    INC_hl;
    RET;


copy:
    CALL(aGetMenuBoxDims);
    INC_B;
    INC_C;
    CALL(av_PushWindow_ret);  // empty function


row:
    PUSH_BC;
    PUSH_HL;


col:
    LD_A_hli;
    LD_de_A;
    DEC_DE;
    DEC_C;
    IF_NZ goto col;

    POP_HL;
    LD_BC(SCREEN_WIDTH);
    ADD_HL_BC;
    POP_BC;
    DEC_B;
    IF_NZ goto row;

    RET;


ret:
    RET;

}

void v_ExitMenu(void){
    XOR_A_A;
    LDH_addr_A(hBGMapMode);

    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(MBANK(awWindowStack));
    LDH_addr_A(rSVBK);

    CALL(aGetWindowStackTop);
    LD_A_L;
    OR_A_H;
    JP_Z (mError_Cant_ExitMenu);
    LD_A_L;
    LD_addr_A(wWindowStackPointer);
    LD_A_H;
    LD_addr_A(wWindowStackPointer + 1);
    CALL(aPopWindow);
    LD_A_addr(wMenuFlags);
    BIT_A(0);
    IF_Z goto loop;
    LD_D_H;
    LD_E_L;
    CALL(aRestoreTileBackup);


loop:
    CALL(aGetWindowStackTop);
    LD_A_H;
    OR_A_L;
    IF_Z goto done;
    CALL(aPopWindow);


done:
    POP_AF;
    LDH_addr_A(rSVBK);
    LD_HL(wWindowStackSize);
    DEC_hl;
    RET;

}

void v_ExitMenu_Conv(void){
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = 0;

    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    // LD_A(MBANK(awWindowStack));
    // LDH_addr_A(rSVBK);
    wbank_push(MBANK(awWindowStack));

    // CALL(aGetWindowStackTop);
    // LD_A_L;
    // OR_A_H;
    // JP_Z (mError_Cant_ExitMenu);
    uint16_t hl = GetWindowStackTop_Conv();
    if(hl == 0) {
        return Error_Cant_ExitMenu_Conv();
    }
    // LD_A_L;
    // LD_addr_A(wWindowStackPointer);
    // LD_A_H;
    // LD_addr_A(wWindowStackPointer + 1);
    wram->wWindowStackPointer = hl;
    // CALL(aPopWindow);
    PopWindow_Conv(hl);
    // LD_A_addr(wMenuFlags);
    // BIT_A(0);
    // IF_Z goto loop;
    if(bit_test(wram->wMenuFlags, 0)) {
        // LD_D_H;
        // LD_E_L;
        // CALL(aRestoreTileBackup);
        RestoreTileBackup_Conv(GBToRAMAddr(hl));
    }


// loop:
    // CALL(aGetWindowStackTop);
    hl = GetWindowStackTop_Conv();
    // LD_A_H;
    // OR_A_L;
    // IF_Z goto done;
    if(hl != 0) {
        // CALL(aPopWindow);
        PopWindow_Conv(hl);
    }


// done:
    // POP_AF;
    // LDH_addr_A(rSVBK);
    wbank_pop;
    // LD_HL(wWindowStackSize);
    // DEC_hl;
    wram->wWindowStackSize--;
    // RET;
}

void RestoreOverworldMapTiles(void){
//  //  unreferenced
    LD_A_addr(wVramState);
    BIT_A(0);
    RET_Z ;
    XOR_A_A;  // sScratch
    CALL(aOpenSRAM);
    hlcoord(0, 0, wTilemap);
    LD_DE(sScratch);
    LD_BC(SCREEN_WIDTH * SCREEN_HEIGHT);
    CALL(aCopyBytes);
    CALL(aCloseSRAM);
    CALL(aOverworldTextModeSwitch);
    XOR_A_A;  // sScratch
    CALL(aOpenSRAM);
    LD_HL(sScratch);
    decoord(0, 0, wTilemap);
    LD_BC(SCREEN_WIDTH * SCREEN_HEIGHT);

loop:
    LD_A_hl;
    CP_A(0x61);
    IF_C goto next;
    LD_de_A;

next:
    INC_HL;
    INC_DE;
    DEC_BC;
    LD_A_C;
    OR_A_B;
    IF_NZ goto loop;
    CALL(aCloseSRAM);
    RET;

}

void Error_Cant_ExitMenu(void){
    LD_HL(mError_Cant_ExitMenu_WindowPoppingErrorText);
    CALL(aPrintText);
    CALL(aWaitBGMap);

infinite_loop:
    DelayFrame();
    goto infinite_loop;


WindowPoppingErrorText:
    //text_far ['_WindowPoppingErrorText']
    //text_end ['?']

    return v_InitVerticalMenuCursor();
}

#include "../../util/text_cmd.h"
void Error_Cant_ExitMenu_Conv(void){
    // static const struct TextCmd WindowPoppingErrorText[] = {
    //     text_far(v_WindowPoppingErrorText),
    //     text_end
    // };
    LD_HL(mError_Cant_ExitMenu_WindowPoppingErrorText);
    CALL(aPrintText);
    // PrintText_Conv(WindowPoppingErrorText);
    // CALL(aWaitBGMap);
    WaitBGMap_Conv();

infinite_loop:
    DelayFrame();
    goto infinite_loop;


// WindowPoppingErrorText:
    //text_far ['_WindowPoppingErrorText']
    //text_end ['?']

    // return v_InitVerticalMenuCursor();
}

void v_InitVerticalMenuCursor(void){
    LD_A_addr(wMenuDataFlags);
    LD_B_A;
    LD_HL(w2DMenuCursorInitY);
    LD_A_addr(wMenuBorderTopCoord);
    INC_A;
    BIT_B(6);
    IF_NZ goto skip_offset;
    INC_A;

skip_offset:
    LD_hli_A;
//  w2DMenuCursorInitX
    LD_A_addr(wMenuBorderLeftCoord);
    INC_A;
    LD_hli_A;
//  w2DMenuNumRows
    LD_A_addr(wMenuDataItems);
    LD_hli_A;
//  w2DMenuNumCols
    LD_A(1);
    LD_hli_A;
//  w2DMenuFlags1
    LD_hl(0x0);
    BIT_B(5);
    IF_Z goto skip_bit_5;
    SET_hl(5);

skip_bit_5:
    LD_A_addr(wMenuFlags);
    BIT_A(4);
    IF_Z goto skip_bit_6;
    SET_hl(6);

skip_bit_6:
    INC_HL;
//  w2DMenuFlags2
    XOR_A_A;
    LD_hli_A;
//  w2DMenuCursorOffsets
    LD_A((2 << 4) | 0);
    LD_hli_A;
//  wMenuJoypadFilter
    LD_A(A_BUTTON);
    BIT_B(0);
    IF_NZ goto skip_bit_1;
    ADD_A(B_BUTTON);

skip_bit_1:
    LD_hli_A;
//  wMenuCursorY
    LD_A_addr(wMenuCursorPosition);
    AND_A_A;
    IF_Z goto load_at_the_top;
    LD_C_A;
    LD_A_addr(wMenuDataItems);
    CP_A_C;
    IF_NC goto load_position;

load_at_the_top:
    LD_C(1);

load_position:
    LD_hl_C;
    INC_HL;
//  wMenuCursorX
    LD_A(1);
    LD_hli_A;
//  wCursorOffCharacter, wCursorCurrentTile
    XOR_A_A;
    LD_hli_A;
    LD_hli_A;
    LD_hli_A;
    RET;

}

void v_InitVerticalMenuCursor_Conv(void){
    // LD_A_addr(wMenuDataFlags);
    // LD_B_A;
    uint8_t b = wram->wMenuDataFlags;
    // LD_HL(w2DMenuCursorInitY);
    // LD_A_addr(wMenuBorderTopCoord);
    // INC_A;
    uint8_t a = wram->wMenuBorderTopCoord + 1;
    // BIT_B(6);
    // IF_NZ goto skip_offset;
    if(bit_test(b, 6)) {
        // INC_A;
        ++a;
    }

// skip_offset:
    // LD_hli_A;
    wram->w2DMenuCursorInitY = a;
//  w2DMenuCursorInitX
    // LD_A_addr(wMenuBorderLeftCoord);
    // INC_A;
    // LD_hli_A;
    wram->w2DMenuCursorInitX = wram->wMenuBorderLeftCoord + 1;
//  w2DMenuNumRows
    // LD_A_addr(wMenuDataItems);
    // LD_hli_A;
    wram->w2DMenuNumRows = wram->wMenuDataItems;
//  w2DMenuNumCols
    // LD_A(1);
    // LD_hli_A;
    wram->w2DMenuNumCols = 1;
//  w2DMenuFlags1
    // LD_hl(0x0);
    // BIT_B(5);
    // IF_Z goto skip_bit_5;
    // SET_hl(5);
    wram->w2DMenuFlags1 = (bit_test(b, 5))? (1 << 5): 0;

// skip_bit_5:
    // LD_A_addr(wMenuFlags);
    // BIT_A(4);
    // IF_Z goto skip_bit_6;
    // SET_hl(6);
    wram->w2DMenuFlags1 |= (bit_test(wram->wMenuFlags, 4))? (1 << 6): 0;

// skip_bit_6:
    // INC_HL;
//  w2DMenuFlags2
    // XOR_A_A;
    // LD_hli_A;
    wram->w2DMenuFlags2 = 0;
//  w2DMenuCursorOffsets
    // LD_A((2 << 4) | 0);
    // LD_hli_A;
    wram->w2DMenuCursorOffsets = (2 << 4) | 0;
//  wMenuJoypadFilter
    // LD_A(A_BUTTON);
    // BIT_B(0);
    // IF_NZ goto skip_bit_1;
    // ADD_A(B_BUTTON);

// skip_bit_1:
    // LD_hli_A;
    wram->wMenuJoypadFilter = (!bit_test(b, 0))? (A_BUTTON | B_BUTTON): A_BUTTON;
//  wMenuCursorY
    // LD_A_addr(wMenuCursorPosition);
    // AND_A_A;
    // IF_Z goto load_at_the_top;
    if(wram->wMenuCursorPosition == 0 || wram->wMenuDataItems < wram->wMenuCursorPosition) {
        // LD_C_A;
        // LD_A_addr(wMenuDataItems);
        // CP_A_C;
        // IF_NC goto load_position;
    // load_at_the_top:
        // LD_C(1);
        wram->wMenuCursorY = 1;
    }
    else {
    // load_position:
        // LD_hl_C;
        // INC_HL;
        wram->wMenuCursorY = wram->wMenuCursorPosition;
    }
//  wMenuCursorX
    // LD_A(1);
    // LD_hli_A;
    wram->wMenuCursorX = 1;
//  wCursorOffCharacter, wCursorCurrentTile
    // XOR_A_A;
    // LD_hli_A;
    // LD_hli_A;
    // LD_hli_A;
    wram->wCursorOffCharacter = 0;
    wram->wCursorCurrentTile = 0;
    // RET;
}
