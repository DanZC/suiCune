#include "../../constants.h"
#include "scrolling_menu.h"
#include "../../home/tilemap.h"
#include "../../home/menu.h"
#include "../../home/text.h"
#include "../../home/delay.h"
#include "../../charmap.h"

static void ScrollingMenu_InitDisplay(const struct MenuData* data);
static u8_flag_s ScrollingMenuJoyAction(const struct MenuData* data);
static uint8_t ScrollingMenu_GetCursorPosition(void);

static void InitScrollingMenuCursor(const struct MenuData* data);
static void ScrollingMenu_InitFlags(const struct MenuData* data);
static void ScrollingMenu_ValidateSwitchItem(void);
static void ScrollingMenu_UpdateDisplay(const struct MenuData* data);
static void ScrollingMenu_CallFunctions1and2(const struct MenuData* data, tile_t* hl);
static void ScrollingMenu_PlaceCursor(const struct MenuData* data);
static void ScrollingMenu_CheckCallFunction3(const struct MenuData* data);
static void ScrollingMenu_GetListItemCoordAndFunctionArgs(const struct MenuData* data, uint8_t a);

void v_InitScrollingMenu(const struct MenuData* data){
    // XOR_A_A;
    // LD_addr_A(wMenuJoypad);
    wram->wMenuJoypad = 0;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = BGMAPMODE_NONE;
    // INC_A;
    // LDH_addr_A(hInMenu);
    hram->hInMenu = TRUE;
    // CALL(aInitScrollingMenuCursor);
    InitScrollingMenuCursor(data);
    // CALL(aScrollingMenu_InitFlags);
    ScrollingMenu_InitFlags(data);
    // CALL(aScrollingMenu_ValidateSwitchItem);
    ScrollingMenu_ValidateSwitchItem();
    // CALL(aScrollingMenu_InitDisplay);
    ScrollingMenu_InitDisplay(data);
    // CALL(aApplyTilemap);
    ApplyTilemap();
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = BGMAPMODE_NONE;
    // RET;
}

void v_ScrollingMenu(const struct MenuData* data){
    u8_flag_s res;
    while(1) {
    // loop:
        // CALL(aScrollingMenuJoyAction);
        res = ScrollingMenuJoyAction(data);
        // JP_C (mv_ScrollingMenu_exit);
        if(res.flag)
            break;
        // CALL_Z (av_ScrollingMenu_zero);
        if(res.a == 0) {
        // zero:
            // CALL(aScrollingMenu_InitDisplay);
            ScrollingMenu_InitDisplay(data);
            // LD_A(1);
            // LDH_addr_A(hBGMapMode);
            hram->hBGMapMode = BGMAPMODE_UPDATE_TILES;
            // LD_C(3);
            // CALL(aDelayFrames);
            DelayFrames(3);
            // XOR_A_A;
            // LDH_addr_A(hBGMapMode);
            hram->hBGMapMode = BGMAPMODE_NONE;
            // RET;
        }
        // goto loop;
    }

// exit:
    if(res.a == 0xff)
        res.a = 0;
    // CALL(aMenuClickSound);
    MenuClickSound(res.a);
    // LD_addr_A(wMenuJoypad);
    wram->wMenuJoypad = res.a;
    printf("%c%c%c%c%c%c%c%c\n", 
        (wram->wMenuJoypad & D_DOWN)?   'D': ' ',
        (wram->wMenuJoypad & D_UP)?     'U': ' ',
        (wram->wMenuJoypad & D_LEFT)?   'L': ' ',
        (wram->wMenuJoypad & D_RIGHT)?  'R': ' ',
        (wram->wMenuJoypad & START)?    'S': ' ',
        (wram->wMenuJoypad & SELECT)?   's': ' ',
        (wram->wMenuJoypad & B_BUTTON)? 'B': ' ',
        (wram->wMenuJoypad & A_BUTTON)? 'A': ' ');
    // LD_A(0);
    // LDH_addr_A(hInMenu);
    hram->hInMenu = 0;
    // RET;
}

static void ScrollingMenu_InitDisplay(const struct MenuData* data){
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = BGMAPMODE_NONE;
    // LD_HL(wOptions);
    // LD_A_hl;
    // PUSH_AF;
    uint8_t options = wram->wOptions;
    // SET_hl(NO_TEXT_SCROLL);
    bit_set(wram->wOptions, NO_TEXT_SCROLL);
    // CALL(aScrollingMenu_UpdateDisplay);
    ScrollingMenu_UpdateDisplay(data);
    // CALL(aScrollingMenu_PlaceCursor);
    ScrollingMenu_PlaceCursor(data);
    // CALL(aScrollingMenu_CheckCallFunction3);
    ScrollingMenu_CheckCallFunction3(data);
    // POP_AF;
    // LD_addr_A(wOptions);
    wram->wOptions = options;
    // RET;
}

static u8_flag_s ScrollingMenuJoyAction(const struct MenuData* data){
    do {
    // loop:
        // CALL(aScrollingMenuJoypad);
        ScrollingMenuJoypad();
        // LDH_A_addr(hJoyLast);
        // AND_A(D_PAD);
        // LD_B_A;
        uint8_t pad_last = hram->hJoyLast & (D_PAD);
        // LDH_A_addr(hJoyPressed);
        // AND_A(BUTTONS);
        // OR_A_B;
        uint8_t input = (hram->hJoyPressed & (BUTTONS)) | pad_last;
        // BIT_A(A_BUTTON_F);
        // JP_NZ (mScrollingMenuJoyAction_a_button);
        if(bit_test(input, A_BUTTON_F)) {
        // a_button:
            // CALL(aPlaceHollowCursor);
            PlaceHollowCursor();
            // LD_A_addr(wMenuCursorY);
            // DEC_A;
            // CALL(aScrollingMenu_GetListItemCoordAndFunctionArgs);
            ScrollingMenu_GetListItemCoordAndFunctionArgs(data, wram->wMenuCursorY - 1);
            // LD_A_addr(wMenuSelection);
            // LD_addr_A(wCurItem);
            wram->wCurItem = wram->wMenuSelection;
            // LD_A_addr(wMenuSelectionQuantity);
            // LD_addr_A(wItemQuantity);
            wram->wItemQuantity = wram->wMenuSelectionQuantity;
            // CALL(aScrollingMenu_GetCursorPosition);
            // DEC_A;
            // LD_addr_A(wScrollingMenuCursorPosition);
            // LD_addr_A(wCurItemQuantity);
            wram->wScrollingMenuCursorPosition = ScrollingMenu_GetCursorPosition() - 1;
            wram->wCurItemQuantity = wram->wScrollingMenuCursorPosition;
            // LD_A_addr(wMenuSelection);
            // CP_A(-1);
            // IF_Z goto b_button;
            if(wram->wMenuSelection == 0xff)
                return u8_flag(B_BUTTON, true);
            // LD_A(A_BUTTON);
            // SCF;
            // RET;
            return u8_flag(A_BUTTON, true);
        }
        // BIT_A(B_BUTTON_F);
        // JP_NZ (mScrollingMenuJoyAction_b_button);
        else if(bit_test(input, B_BUTTON_F)) {
        // b_button:
            // LD_A(B_BUTTON);
            // SCF;
            // RET;
            return u8_flag(B_BUTTON, true);
        }
        // BIT_A(SELECT_F);
        // JP_NZ (mScrollingMenuJoyAction_select);
        else if(bit_test(input, SELECT_F)) {
        // select:
            // LD_A_addr(wMenuDataFlags);
            // BIT_A(7);
            // JP_Z (mxor_a_dec_a);
            if(!bit_test(data->flags, 7))
                return u8_flag(0xff, true);
            // LD_A_addr(wMenuCursorY);
            // DEC_A;
            // CALL(aScrollingMenu_GetListItemCoordAndFunctionArgs);
            ScrollingMenu_GetListItemCoordAndFunctionArgs(data, wram->wMenuCursorY - 1);
            // LD_A_addr(wMenuSelection);
            // CP_A(-1);
            // JP_Z (mxor_a_dec_a);
            if(wram->wMenuSelection == 0xff)
                return u8_flag(0xff, true);
            // CALL(aScrollingMenu_GetCursorPosition);
            // DEC_A;
            // LD_addr_A(wScrollingMenuCursorPosition);
            wram->wScrollingMenuCursorPosition = ScrollingMenu_GetCursorPosition() - 1;
            // LD_A(SELECT);
            // SCF;
            // RET;
            return u8_flag(SELECT, true);
        }
        // BIT_A(START_F);
        // JP_NZ (mScrollingMenuJoyAction_start);
        else if(bit_test(input, START_F)) {
        // start:
            // LD_A_addr(wMenuDataFlags);
            // BIT_A(6);
            // JP_Z (mxor_a_dec_a);
            if(!bit_test(data->flags, 6))
                return u8_flag(0xff, true);
            // LD_A(START);
            // SCF;
            // RET;
            return u8_flag(START, true);
        }
        // BIT_A(D_RIGHT_F);
        // JP_NZ (mScrollingMenuJoyAction_d_right);
        else if(bit_test(input, D_RIGHT_F)) {
        // d_right:
            // LD_HL(w2DMenuFlags2);
            // BIT_hl(7);
            // JP_Z (mxor_a_dec_a);
            if(bit_test(wram->w2DMenuFlags2, 7))
                return u8_flag(0xff, true);
            // LD_A_addr(wMenuDataFlags);
            // BIT_A(2);
            // JP_Z (mxor_a_dec_a);
            if(!bit_test(data->flags, STATICMENU_ENABLE_LEFT_RIGHT_F))
                return u8_flag(0xff, true);
            // LD_A(D_RIGHT);
            // SCF;
            // RET;
            return u8_flag(D_RIGHT, true);
        }
        // BIT_A(D_LEFT_F);
        // JP_NZ (mScrollingMenuJoyAction_d_left);
        else if(bit_test(input, D_LEFT_F)) {
        // d_left:
            // LD_HL(w2DMenuFlags2);
            // BIT_hl(7);
            // JP_Z (mxor_a_dec_a);
            if(bit_test(wram->w2DMenuFlags2, 7))
                return u8_flag(0xff, true);
            // LD_A_addr(wMenuDataFlags);
            // BIT_A(3);
            // JP_Z (mxor_a_dec_a);
            if(!bit_test(data->flags, STATICMENU_ENABLE_START_F))
                return u8_flag(0xff, true);
            // LD_A(D_LEFT);
            // SCF;
            // RET;
            return u8_flag(D_LEFT, true);
        }
        // BIT_A(D_UP_F);
        // JP_NZ (mScrollingMenuJoyAction_d_up);
        else if(bit_test(input, D_UP_F)) {
        // d_up:
            // LD_HL(w2DMenuFlags2);
            // BIT_hl(7);
            // JP_Z (mxor_a);
            if(!bit_test(wram->w2DMenuFlags2, 7))
                return u8_flag(0, false);
            // LD_HL(wMenuScrollPosition);
            // LD_A_hl;
            // AND_A_A;
            // IF_Z goto xor_dec_up;
            if(wram->wMenuScrollPosition == 0)
                return u8_flag(0xff, false);
            // DEC_hl;
            --wram->wMenuScrollPosition;
            // JP(mxor_a);
            return u8_flag(0, false);

        // xor_dec_up:
            // JP(mxor_a_dec_a);
        }
        // BIT_A(D_DOWN_F);
        // JP_NZ (mScrollingMenuJoyAction_d_down);
        else if(bit_test(input, D_DOWN_F)) {
        // d_down:
            // LD_HL(w2DMenuFlags2);
            // BIT_hl(7);
            // JP_Z (mxor_a);
            if(!bit_test(wram->w2DMenuFlags2, 7))
                return u8_flag(0, false);
            // LD_HL(wMenuScrollPosition);
            // LD_A_addr(wMenuData_ScrollingMenuHeight);
            // ADD_A_hl;
            // LD_B_A;
            // LD_A_addr(wScrollingMenuListSize);
            // CP_A_B;
            // IF_C goto xor_dec_down;
            if(wram->wScrollingMenuListSize < wram->wMenuScrollPosition + data->scrollingMenu.rows)
                return u8_flag(0xff, false);
            // INC_hl;
            wram->wMenuScrollPosition++;
            // JP(mxor_a);
            return u8_flag(0, false);

        // xor_dec_down:
            // JP(mxor_a_dec_a);
        }
        // goto loop;
    } while(1);


// no_zero_no_carry:
//   //  unreferenced
    // LD_A(-1);
    // AND_A_A;
    // RET;

}

static uint8_t ScrollingMenu_GetCursorPosition(void){
    // LD_A_addr(wMenuScrollPosition);
    // LD_C_A;
    // LD_A_addr(wMenuCursorY);
    // ADD_A_C;
    // LD_C_A;
    // RET;
    return wram->wMenuCursorY + wram->wMenuScrollPosition;
}

void ScrollingMenu_ClearLeftColumn(void){
    // CALL(aMenuBoxCoord2Tile);
    // LD_DE(SCREEN_WIDTH);
    // ADD_HL_DE;
    tile_t* hl = MenuBoxCoord2Tile() + SCREEN_WIDTH;
    // LD_DE(2 * SCREEN_WIDTH);
    // LD_A_addr(wMenuData_ScrollingMenuHeight);
    uint8_t a = GetMenuData()->scrollingMenu.rows;

    do {
    // loop:
        // LD_hl(0x7f);
        *hl = 0x7f;
        // ADD_HL_DE;
        hl += 2 * SCREEN_WIDTH;
        // DEC_A;
        // IF_NZ goto loop;
    } while(--a != 0);
    // RET;
}

static void InitScrollingMenuCursor(const struct MenuData* data){
    // LD_HL(wMenuData_ItemsPointerAddr);
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    const uint8_t* hl = data->scrollingMenu.list;
    // LD_A_addr(wMenuData_ItemsPointerBank);
    // CALL(aGetFarByte);
    // LD_addr_A(wScrollingMenuListSize);
    wram->wScrollingMenuListSize = *(hl++);
    printf("scrolling menu size: %d\n", wram->wScrollingMenuListSize);
    // LD_A_addr(wMenuData_ScrollingMenuHeight);
    // LD_C_A;
    // LD_A_addr(wMenuScrollPosition);
    // ADD_A_C;
    // LD_C_A;
    uint8_t c = data->scrollingMenu.rows + wram->wMenuScrollPosition;
    // LD_A_addr(wScrollingMenuListSize);
    // INC_A;
    // CP_A_C;
    // IF_NC goto skip;
    if(wram->wScrollingMenuListSize + 1 < c) {
        // LD_A_addr(wMenuData_ScrollingMenuHeight);
        // LD_C_A;
        c = data->scrollingMenu.rows;
        // LD_A_addr(wScrollingMenuListSize);
        // INC_A;
        // SUB_A_C;
        // IF_NC goto store;
        if(wram->wScrollingMenuListSize + 1 < c) {
            // XOR_A_A;
            wram->wMenuScrollPosition = 0;
        }
        else {
        // store:
            // LD_addr_A(wMenuScrollPosition);
            wram->wMenuScrollPosition = (wram->wScrollingMenuListSize + 1) - c;
        }
    }

// skip:
    // LD_A_addr(wMenuScrollPosition);
    // LD_C_A;
    // LD_A_addr(wMenuCursorPosition);
    // ADD_A_C;
    // LD_B_A;
    uint8_t b = wram->wMenuScrollPosition + wram->wMenuCursorPosition;
    // LD_A_addr(wScrollingMenuListSize);
    // INC_A;
    // CP_A_B;
    // IF_C goto wrap;
    // IF_NC goto done;
    if(wram->wScrollingMenuListSize + 1 < b){
    // wrap:
        // XOR_A_A;
        // LD_addr_A(wMenuScrollPosition);
        wram->wMenuScrollPosition = 0;
        // LD_A(0x1);
        // LD_addr_A(wMenuCursorPosition);
        wram->wMenuCursorPosition = 0x1;
    }

// done:
    // RET;

}

static void ScrollingMenu_InitFlags(const struct MenuData* data){
    // LD_A_addr(wMenuDataFlags);
    // LD_C_A;
    uint8_t c = data->scrollingMenu.flags;
    // LD_A_addr(wScrollingMenuListSize);
    // LD_B_A;
    // LD_A_addr(wMenuBorderTopCoord);
    // ADD_A(1);
    // LD_addr_A(w2DMenuCursorInitY);
    wram->w2DMenuCursorInitY = wram->wMenuBorderTopCoord + 1;
    // LD_A_addr(wMenuBorderLeftCoord);
    // ADD_A(0);
    // LD_addr_A(w2DMenuCursorInitX);
    wram->w2DMenuCursorInitX = wram->wMenuBorderLeftCoord;
    // LD_A_addr(wMenuData_ScrollingMenuHeight);
    uint8_t a = data->scrollingMenu.rows;
    // CP_A_B;
    // IF_C goto no_extra_row;
    // IF_Z goto no_extra_row;
    if(a > wram->wScrollingMenuListSize){
        // LD_A_B;
        // INC_A;
        a = wram->wScrollingMenuListSize + 1;
    }

// no_extra_row:
    // LD_addr_A(w2DMenuNumRows);
    wram->w2DMenuNumRows = a;
    // LD_A(1);
    // LD_addr_A(w2DMenuNumCols);
    wram->w2DMenuNumCols = 1;
    // LD_A(0x8c);
    a = 0x8c;
    // BIT_C(2);
    // IF_Z goto skip_set_0;
    if(bit_test(c, 2)){
        // SET_A(0);
        bit_set(a, 0);
    }

// skip_set_0:
    // BIT_C(3);
    // IF_Z goto skip_set_1;
    if(bit_test(c, 3)){
        // SET_A(1);
        bit_set(a, 1);
    }

// skip_set_1:
    // LD_addr_A(w2DMenuFlags1);
    wram->w2DMenuFlags1 = a;
    // XOR_A_A;
    // LD_addr_A(w2DMenuFlags2);
    wram->w2DMenuFlags2 = 0;
    // LD_A(0x20);
    // LD_addr_A(w2DMenuCursorOffsets);
    wram->w2DMenuCursorOffsets = 0x20;
    // LD_A(A_BUTTON | B_BUTTON | D_UP | D_DOWN);
    a = A_BUTTON | B_BUTTON | D_UP | D_DOWN;
    // BIT_C(7);
    // IF_Z goto disallow_select;
    if(bit_test(c, 7)){
        // ADD_A(SELECT);
        a |= SELECT;
    }

// disallow_select:
    // BIT_C(6);
    // IF_Z goto disallow_start;
    if(bit_test(c, 6)){
        // ADD_A(START);
        a |= START;
    }


// disallow_start:
    // LD_addr_A(wMenuJoypadFilter);
    wram->wMenuJoypadFilter = a;
    // LD_A_addr(w2DMenuNumRows);
    // LD_B_A;
    // LD_A_addr(wMenuCursorPosition);
    // AND_A_A;
    // IF_Z goto reset_cursor;
    // CP_A_B;
    // IF_Z goto cursor_okay;
    // IF_C goto cursor_okay;

    if(wram->wMenuCursorPosition == 0
    || wram->wMenuCursorPosition > wram->w2DMenuNumRows) {
    // reset_cursor:
        // LD_A(1);
        wram->wMenuCursorY = 1;
    }
    else {
        wram->wMenuCursorY = wram->wMenuCursorPosition;
    }

// cursor_okay:
    // LD_addr_A(wMenuCursorY);
    // LD_A(1);
    // LD_addr_A(wMenuCursorX);
    wram->wMenuCursorX = 1;
    // XOR_A_A;
    // LD_addr_A(wCursorCurrentTile);
    // LD_addr_A(wCursorCurrentTile + 1);
    wram->wCursorCurrentTile = 0;
    // LD_addr_A(wCursorOffCharacter);
    wram->wCursorOffCharacter = 0;
    // RET;
}

static void ScrollingMenu_ValidateSwitchItem(void){
    // LD_A_addr(wScrollingMenuListSize);
    // LD_C_A;
    uint8_t c = wram->wScrollingMenuListSize;
    // LD_A_addr(wSwitchItem);
    // AND_A_A;
    // IF_Z goto done;
    // DEC_A;
    // CP_A_C;
    // IF_C goto done;
    if(wram->wSwitchItem != 0
    && wram->wSwitchItem - 1 >= c) {
        // XOR_A_A;
        // LD_addr_A(wSwitchItem);
        wram->wSwitchItem = 0;
    }

// done:
    // RET;

}

static void ScrollingMenu_UpdateDisplay(const struct MenuData* data){
    // CALL(aClearWholeMenuBox);
    ClearWholeMenuBox();
    // LD_A_addr(wMenuDataFlags);
    // BIT_A(4);  // place arrows
    // IF_Z goto okay;
    // LD_A_addr(wMenuScrollPosition);
    // AND_A_A;
    // IF_Z goto okay;
    if(bit_test(data->flags, 4)
    && wram->wMenuScrollPosition != 0){
        // LD_A_addr(wMenuBorderTopCoord);
        // LD_B_A;
        // LD_A_addr(wMenuBorderRightCoord);
        // LD_C_A;
        // CALL(aCoord2Tile);
        // LD_hl(0x61);
        *Coord2Tile(wram->wMenuBorderRightCoord, wram->wMenuBorderTopCoord) = CHAR_UP_ARROW;
    }

// okay:
    // CALL(aMenuBoxCoord2Tile);
    // LD_BC(SCREEN_WIDTH + 1);
    // ADD_HL_BC;
    uint8_t* hl = MenuBoxCoord2Tile() + SCREEN_WIDTH + 1;
    // LD_A_addr(wMenuData_ScrollingMenuHeight);
    // LD_B_A;
    uint8_t b = data->scrollingMenu.rows;
    // LD_C(0x0);
    uint8_t c = 0x0;

    do {
    // loop:
        // LD_A_addr(wMenuScrollPosition);
        // ADD_A_C;
        // LD_addr_A(wScrollingMenuCursorPosition);
        wram->wScrollingMenuCursorPosition = wram->wMenuScrollPosition + c;
        // LD_A_C;
        // CALL(aScrollingMenu_GetListItemCoordAndFunctionArgs);
        ScrollingMenu_GetListItemCoordAndFunctionArgs(data, c);
        // LD_A_addr(wMenuSelection);
        // CP_A(-1);
        // IF_Z goto cancel;
        if(wram->wMenuSelection == 0xff) {
        // cancel:
            // LD_A_addr(wMenuDataFlags);
            // BIT_A(0);  // call function on cancel
            // IF_NZ goto call_function;
            if(bit_test(data->flags, 0)){
            // call_function:
                // LD_D_H;
                // LD_E_L;
                // LD_HL(wMenuData_ScrollingMenuFunction1);
                // JP(mCallPointerAt);
                data->scrollingMenu.func1(data, hl);
            }
            // LD_DE(mScrollingMenu_UpdateDisplay_CancelString);
            // CALL(aPlaceString);
            PlaceStringSimple(U82C("CANCEL@"), hl);
            // RET;
            return;

        // CancelString:
            //db ['"CANCEL@"'];
        }
        // PUSH_BC;
        // PUSH_HL;
        // CALL(aScrollingMenu_CallFunctions1and2);
        ScrollingMenu_CallFunctions1and2(data, hl);
        // POP_HL;
        // LD_BC(2 * SCREEN_WIDTH);
        // ADD_HL_BC;
        hl += 2 * SCREEN_WIDTH;
        // POP_BC;
        // INC_C;
        // LD_A_C;
        // CP_A_B;
        // IF_NZ goto loop;
    } while(++c != b);
    // LD_A_addr(wMenuDataFlags);
    // BIT_A(4);  // place arrows
    // IF_Z goto done;
    if(bit_test(data->flags, 4)){
        // LD_A_addr(wMenuBorderBottomCoord);
        // LD_B_A;
        // LD_A_addr(wMenuBorderRightCoord);
        // LD_C_A;
        // CALL(aCoord2Tile);
        // LD_hl(0xee);
        *Coord2Tile(wram->wMenuBorderRightCoord, wram->wMenuBorderBottomCoord) = CHAR_DOWN_CURSOR;
    }

// done:
    // RET;
}

static void ScrollingMenu_CallFunctions1and2(const struct MenuData* data, tile_t* hl){
    // PUSH_HL;
    // LD_D_H;
    // LD_E_L;
    // LD_HL(wMenuData_ScrollingMenuFunction1);
    // CALL(aCallPointerAt);
    data->scrollingMenu.func1(data, hl);
    // POP_HL;
    // LD_A_addr(wMenuData_ScrollingMenuWidth);
    // AND_A_A;
    // IF_Z goto done;
    if(data->scrollingMenu.cols != 0) {
        // LD_E_A;
        // LD_D(0);
        // ADD_HL_DE;
        // LD_D_H;
        // LD_E_L;
        // LD_HL(wMenuData_ScrollingMenuFunction2);
        // CALL(aCallPointerAt);
        data->scrollingMenu.func2(data, hl + data->scrollingMenu.cols);
    }

// done:
    // RET;
}

static void ScrollingMenu_PlaceCursor(const struct MenuData* data){
    // LD_A_addr(wSwitchItem);
    // AND_A_A;
    // IF_Z goto done;
    if(wram->wSwitchItem == 0)
        return;
    // LD_B_A;
    // LD_A_addr(wMenuScrollPosition);
    // CP_A_B;
    // IF_NC goto done;
    if(wram->wMenuScrollPosition >= wram->wSwitchItem)
        return;
    // LD_C_A;
    // LD_A_addr(wMenuData_ScrollingMenuHeight);
    // ADD_A_C;
    // CP_A_B;
    // IF_C goto done;
    if(data->scrollingMenu.rows + wram->wMenuScrollPosition < wram->wSwitchItem)
        return;
    // LD_A_B;
    // SUB_A_C;
    // DEC_A;
    // ADD_A_A;
    // ADD_A(0x1);
    // LD_C_A;
    uint8_t c = (((wram->wSwitchItem - wram->wMenuScrollPosition) - 1) * 2) + 0x1;
    // LD_A_addr(wMenuBorderTopCoord);
    // ADD_A_C;
    // LD_B_A;
    uint8_t b = wram->wMenuBorderTopCoord + c;
    // LD_A_addr(wMenuBorderLeftCoord);
    // ADD_A(0x0);
    // LD_C_A;
    // CALL(aCoord2Tile);
    // LD_hl(0xec);
    *Coord2Tile(wram->wMenuBorderLeftCoord, b) = CHAR_RIGHT_CURSOR_SEL;

// done:
    // RET;

}

static void ScrollingMenu_CheckCallFunction3(const struct MenuData* data){
    // LD_A_addr(wMenuDataFlags);
    // BIT_A(5);  // call function 3
    // RET_Z ;
    if(!bit_test(data->flags, 5))
        return;
    // BIT_A(1);  // call function 3 if not switching items
    // IF_Z goto call;
    if(bit_test(data->flags, 1)){
        // LD_A_addr(wSwitchItem);
        // AND_A_A;
        // RET_NZ ;
        if(wram->wSwitchItem != 0)
            return;
    }

// call:
    // LD_A_addr(wMenuCursorY);
    // DEC_A;
    // CALL(aScrollingMenu_GetListItemCoordAndFunctionArgs);
    ScrollingMenu_GetListItemCoordAndFunctionArgs(data, wram->wMenuCursorY - 1);
    // LD_HL(wMenuData_ScrollingMenuFunction3);
    // CALL(aCallPointerAt);
    data->scrollingMenu.func3();
    // RET;
}

static void ScrollingMenu_GetListItemCoordAndFunctionArgs(const struct MenuData* data, uint8_t a){
    // PUSH_DE;
    // PUSH_HL;
    // LD_E_A;
    // LD_A_addr(wMenuScrollPosition);
    // ADD_A_E;
    // LD_E_A;
    // LD_D(0);
    uint16_t de = wram->wMenuScrollPosition + a;
    // LD_HL(wMenuData_ItemsPointerAddr);
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // INC_HL;  // items
    const uint8_t* items = data->scrollingMenu.list + 1;
    // LD_A_addr(wMenuData_ScrollingMenuItemFormat);
    // CP_A(SCROLLINGMENU_ITEMS_NORMAL);
    // IF_Z goto got_spacing;
    if(data->scrollingMenu.format != SCROLLINGMENU_ITEMS_NORMAL){
        // CP_A(SCROLLINGMENU_ITEMS_QUANTITY);
        // IF_Z goto pointless_jump;

    // pointless_jump:
        // ADD_HL_DE;
        items += de;
    }

// got_spacing:
    // ADD_HL_DE;
    items += de;
    // LD_A_addr(wMenuData_ItemsPointerBank);
    // CALL(aGetFarByte);
    // LD_addr_A(wMenuSelection);
    wram->wMenuSelection = *(items++);
    // LD_addr_A(wCurItem);
    // INC_HL;
    // LD_A_addr(wMenuData_ItemsPointerBank);
    // CALL(aGetFarByte);
    // LD_addr_A(wMenuSelectionQuantity);
    wram->wMenuSelectionQuantity = *items;
    // POP_HL;
    // POP_DE;
    // RET;

}
