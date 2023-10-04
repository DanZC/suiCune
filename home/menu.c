#include "../constants.h"
#include "menu.h"
#include "copy.h"
#include "text.h"
#include "map_objects.h"
#include "audio.h"
#include "tilemap.h"
#include "../charmap.h"
#include "../engine/menus/menu.h"

void Load2DMenuData(void) {
    PUSH_HL;
    PUSH_BC;
    LD_HL(w2DMenuData);
    LD_B(w2DMenuDataEnd - w2DMenuData);

loop:
    LD_A_de;
    INC_DE;
    LD_hli_A;
    DEC_B;
    IF_NZ goto loop;

    // Reset menu state
    LD_A(0x1);
    LD_hli_A;  // wMenuCursorY
    LD_hli_A;  // wMenuCursorX
    XOR_A_A;
    LD_hli_A;  // wCursorOffCharacter
    LD_hli_A;  // wCursorCurrentTile
    LD_hli_A;
    POP_BC;
    POP_HL;
    RET;
}

void Load2DMenuData_Conv(void) {
    uint16_t hl = REG_HL;
    uint16_t bc = REG_BC;
    REG_HL = w2DMenuData;
    REG_B = (w2DMenuDataEnd - w2DMenuData);

    do {
        gb_write(REG_HL++, gb_read(REG_DE++));
    } while(--REG_B != 0);

    // Reset menu state
    gb_write(wMenuCursorY, 0x1);
    gb_write(wMenuCursorX, 0x1);
    gb_write(wCursorOffCharacter, 0);
    gb_write(wCursorCurrentTile, 0);
    gb_write(wCursorCurrentTile + 1, 0);
    REG_BC = bc;
    REG_HL = hl;
}

void StaticMenuJoypad(void) {
    CALLFAR(av_StaticMenuJoypad);
    CALL(aGetMenuJoypad);
    RET;
}

uint8_t StaticMenuJoypad_Conv(void) {
    // CALLFAR(av_StaticMenuJoypad);
    v_StaticMenuJoypad_Conv();
    // CALL(aGetMenuJoypad);
    // RET;
    return GetMenuJoypad_Conv();
}

void ScrollingMenuJoypad(void) {
    CALLFAR(av_ScrollingMenuJoypad);
    CALL(aGetMenuJoypad);
    RET;
}

uint8_t ScrollingMenuJoypad_Conv(void) {
    // CALLFAR(av_ScrollingMenuJoypad);
    v_ScrollingMenuJoypad_Conv();
    // CALL(aGetMenuJoypad);
    // RET;
    return GetMenuJoypad_Conv();
}

void GetMenuJoypad(void) {
    PUSH_BC;
    PUSH_AF;
    LDH_A_addr(hJoyLast);
    AND_A(D_PAD);
    LD_B_A;
    LDH_A_addr(hJoyPressed);
    AND_A(BUTTONS);
    OR_A_B;
    LD_B_A;
    POP_AF;
    LD_A_B;
    POP_BC;
    RET;
}

uint8_t GetMenuJoypad_Conv(void) {
    uint8_t pad_last = (hram->hJoyLast & (D_PAD));
    uint8_t button_last = (hram->hJoyPressed & (BUTTONS));
    return (pad_last | button_last);
}

void PlaceHollowCursor(void) {
    LD_HL(wCursorCurrentTile);
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    LD_hl(CHAR_RIGHT_CURSOR_SEL);
    RET;
}

void PlaceHollowCursor_Conv(void) {
    // LD_HL(wCursorCurrentTile);
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // LD_hl(CHAR_RIGHT_CURSOR_SEL);
    // RET;
    *(uint8_t*)GBToRAMAddr(wram->wCursorCurrentTile) = CHAR_RIGHT_CURSOR_SEL;
}

void HideCursor(void) {
    LD_HL(wCursorCurrentTile);
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    LD_hl(CHAR_SPACE);
    RET;
}

void HideCursor_Conv(void){
    gb_write(gb_read16(wCursorCurrentTile), CHAR_SPACE);
}

void PushWindow(void) {
    CALLFAR(av_PushWindow);
    RET;
}

void ExitMenu(void) {
    PUSH_AF;
    CALLFAR(av_ExitMenu);
    POP_AF;
    RET;
}

void ExitMenu_Conv(void) {
    // PUSH_AF;
    // CALLFAR(av_ExitMenu);
    // POP_AF;
    // RET;
    return v_ExitMenu_Conv();
}

void InitVerticalMenuCursor(void) {
    CALLFAR(av_InitVerticalMenuCursor);
    RET;
}

void InitVerticalMenuCursor_Conv(void) {
    // CALLFAR(av_InitVerticalMenuCursor);
    // RET;
    return v_InitVerticalMenuCursor_Conv();
}

void CloseWindow(void) {
    PUSH_AF;
    CALL(aExitMenu);
    CALL(aApplyTilemap);
    CALL(aUpdateSprites);
    POP_AF;
    RET;
}

void CloseWindow_Conv(void) {
    // PUSH_AF;
    // CALL(aExitMenu);
    ExitMenu_Conv();
    // CALL(aApplyTilemap);
    ApplyTilemap_Conv();
    // CALL(aUpdateSprites);
    UpdateSprites_Conv();
    // POP_AF;
    // RET;
}

void RestoreTileBackup(void) {
    CALL(aMenuBoxCoord2Tile);
    CALL(aRestoreTileBackup_copy);
    CALL(aMenuBoxCoord2Attr);
    CALL(aRestoreTileBackup_copy);
    RET;

copy:
    CALL(aGetMenuBoxDims);
    INC_B;
    INC_C;

row:
    PUSH_BC;
    PUSH_HL;

col:
    LD_A_de;
    LD_hli_A;
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
}

static uint8_t* RestoreTileBackup_copy(uint8_t* de, uint8_t* hl) {
    // CALL(aGetMenuBoxDims);
    // INC_B;
    // INC_C;
    uint8_t b, c, c2;
    GetMenuBoxDims_Conv(&b, &c);
    b++, c++;
    uint8_t* hl2;

    do {
    // row:
        // PUSH_BC;
        c2 = c;
        // PUSH_HL;
        hl2 = hl;

        do {
        // col:
            // LD_A_de;
            // LD_hli_A;
            *(hl++) = *(de--);
            // DEC_DE;
            // DEC_C;
            // IF_NZ goto col;
        } while(--c != 0);

        // POP_HL;
        hl = hl2;
        // LD_BC(SCREEN_WIDTH);
        // ADD_HL_BC;
        hl += SCREEN_WIDTH;
        // POP_BC;
        c = c2;
        // DEC_B;
        // IF_NZ goto row;
    } while(--b != 0);

    // RET;
    return de;
}

void RestoreTileBackup_Conv(uint8_t* de) {
    // CALL(aMenuBoxCoord2Tile);
    uint8_t* hl = MenuBoxCoord2Tile_Conv();
    // CALL(aRestoreTileBackup_copy);
    de = RestoreTileBackup_copy(de, hl);
    // CALL(aMenuBoxCoord2Attr);
    hl = MenuBoxCoord2Attr_Conv();
    // CALL(aRestoreTileBackup_copy);
    RestoreTileBackup_copy(de, hl);
    // RET;
}

void PopWindow(void) {
    LD_B(wMenuHeaderEnd - wMenuHeader);
    LD_DE(wMenuHeader);

loop:
    LD_A_hld;
    LD_de_A;
    INC_DE;
    DEC_B;
    IF_NZ goto loop;
    RET;
}

void PopWindow_Conv(uint16_t hl) {
    uint8_t i = wMenuHeaderEnd - wMenuHeader;
    uint16_t de = wMenuHeader;

    do {
        gb_write(de++, gb_read(hl--));
    } while(--i != 0);
}

void GetMenuBoxDims(void) {
    LD_A_addr(wMenuBorderTopCoord);  // top
    LD_B_A;
    LD_A_addr(wMenuBorderBottomCoord);  // bottom
    SUB_A_B;
    LD_B_A;
    LD_A_addr(wMenuBorderLeftCoord);  // left
    LD_C_A;
    LD_A_addr(wMenuBorderRightCoord);  // right
    SUB_A_C;
    LD_C_A;
    RET;
}

void GetMenuBoxDims_Conv(uint8_t* w, uint8_t* h) {
    uint8_t top = wram->wMenuBorderTopCoord;  // top
    uint8_t bottom = wram->wMenuBorderBottomCoord;  // bottom
    uint8_t left = wram->wMenuBorderLeftCoord; // left
    uint8_t right = wram->wMenuBorderRightCoord; // right
    *h = bottom - top; 
    *w = right - left;
}

void CopyMenuData(void) {
    PUSH_HL;
    PUSH_DE;
    PUSH_BC;
    PUSH_AF;
    LD_HL(wMenuDataPointer);
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    LD_DE(wMenuData);
    LD_BC(wMenuDataEnd - wMenuData);
    CALL(aCopyBytes);
    POP_AF;
    POP_BC;
    POP_DE;
    POP_HL;
    RET;
}

void CopyMenuData_Conv(void) {
    // LD_HL(wMenuDataPointer);

    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    const void* hl = GBToRAMAddr(wram->wMenuDataPointer);

    // LD_DE(wMenuData);
    void* de = &wram->wMenuDataFlags;

    // LD_BC(wMenuDataEnd - wMenuData);
    uint16_t bc = (wMenuDataEnd - wMenuData);

    // CALL(aCopyBytes);
    CopyBytes_Conv2(de, hl, bc);
}

void GetWindowStackTop(void) {
    LD_HL(wWindowStackPointer);
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    INC_HL;
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    RET;
}

uint16_t GetWindowStackTop_Conv(void) {
    uint16_t hl = (gb_read(wWindowStackPointer + 1) << 8) | gb_read(wWindowStackPointer);
    hl = (gb_read(hl + 2) << 8) | gb_read(hl + 1);
    return hl;
}

void PlaceVerticalMenuItems(void) {
    CALL(aCopyMenuData);
    LD_HL(wMenuDataPointer);
    LD_E_hl;
    INC_HL;
    LD_D_hl;
    CALL(aGetMenuTextStartCoord);
    CALL(aCoord2Tile);  // hl now contains the tilemap address where we will start printing text.
    INC_DE;
    LD_A_de;  // Number of items
    INC_DE;
    LD_B_A;

loop:
    PUSH_BC;
    CALL(aPlaceString);
    INC_DE;
    LD_BC(2 * SCREEN_WIDTH);
    ADD_HL_BC;
    POP_BC;
    DEC_B;
    IF_NZ goto loop;

    LD_A_addr(wMenuDataFlags);
    BIT_A(4);
    RET_Z;

    CALL(aMenuBoxCoord2Tile);
    LD_A_de;
    LD_C_A;
    INC_DE;
    LD_B(0);
    ADD_HL_BC;
    JP(mPlaceString);
}

void PlaceVerticalMenuItems_Conv(void) {
    // CALL(aCopyMenuData);
    CopyMenuData_Conv();
    // LD_HL(wMenuDataPointer);
    // LD_E_hl;
    // INC_HL;
    // LD_D_hl;
    uint8_t* de = GBToRAMAddr(wram->wMenuDataPointer);
    // CALL(aGetMenuTextStartCoord);
    uint8_t b, c;
    GetMenuTextStartCoord_Conv(&b, &c);
    // CALL(aCoord2Tile);  // hl now contains the tilemap address where we will start printing text.
    uint8_t* hl = Coord2Tile_Conv(c, b);
    // INC_DE;
    // LD_A_de;  // Number of items
    b = *(++de);
    // INC_DE;
    // LD_B_A;
    de++;
    struct TextPrintState st = {.de = de, .hl = hl};

    do {
    // loop:
        // PUSH_BC;
        // CALL(aPlaceString);
        PlaceString_Conv(&st, st.hl);
        // INC_DE;
        st.de++;
        // LD_BC(2 * SCREEN_WIDTH);
        // ADD_HL_BC;
        st.hl += 2 * SCREEN_WIDTH;
        // POP_BC;
        // DEC_B;
        // IF_NZ goto loop;
    } while(--b != 0);

    // LD_A_addr(wMenuDataFlags);
    // BIT_A(4);
    // RET_Z;
    if(!bit_test(wram->wMenuDataFlags, 4))
        return;

    // CALL(aMenuBoxCoord2Tile);
    // LD_A_de;
    // LD_C_A;
    // INC_DE;
    // LD_B(0);
    // ADD_HL_BC;
    st.hl = MenuBoxCoord2Tile_Conv() + *(st.de++);
    // JP(mPlaceString);
    return PlaceString_Conv(&st, st.hl);
}

void MenuBox(void) {
    CALL(aMenuBoxCoord2Tile);
    CALL(aGetMenuBoxDims);
    DEC_B;
    DEC_C;
    JP(mTextbox);
}

void MenuBox_Conv(void) {
    uint8_t w, h;
    // CALL(aMenuBoxCoord2Tile);
    uint8_t* ptr = MenuBoxCoord2Tile_Conv();
    // CALL(aGetMenuBoxDims);
    GetMenuBoxDims_Conv(&w, &h);
    // DEC_B;
    // DEC_C;
    // JP(mTextbox);
    return Textbox_Conv2(ptr, w - 1, h - 1);
}

void GetMenuTextStartCoord(void) {
    LD_A_addr(wMenuBorderTopCoord);
    LD_B_A;
    INC_B;
    LD_A_addr(wMenuBorderLeftCoord);
    LD_C_A;
    INC_C;
    //  bit 6: if not set, leave extra room on top
    LD_A_addr(wMenuDataFlags);
    BIT_A(6);
    IF_NZ goto bit_6_set;
    INC_B;

bit_6_set:
    //  bit 7: if set, leave extra room on the left
    LD_A_addr(wMenuDataFlags);
    BIT_A(7);
    IF_Z goto bit_7_clear;
    INC_C;

bit_7_clear:
    RET;
}

void GetMenuTextStartCoord_Conv(uint8_t* b, uint8_t* c) {
    // LD_A_addr(wMenuBorderTopCoord);
    // LD_B_A;
    // INC_B;
    *b = wram->wMenuBorderTopCoord + 1;
    // LD_A_addr(wMenuBorderLeftCoord);
    // LD_C_A;
    // INC_C;
    *c = wram->wMenuBorderLeftCoord + 1;
    //  bit 6: if not set, leave extra room on top
    // LD_A_addr(wMenuDataFlags);
    // BIT_A(6);
    // IF_NZ goto bit_6_set;
    if(!bit_test(wram->wMenuDataFlags, 6)) {
        // INC_B;
        ++(*b);
    }

// bit_6_set:
    //  bit 7: if set, leave extra room on the left
    // LD_A_addr(wMenuDataFlags);
    // BIT_A(7);
    // IF_Z goto bit_7_clear;
    if(bit_test(wram->wMenuDataFlags, 7)) {
        // INC_C;
        ++(*c);
    }

// bit_7_clear:
    // RET;
}

void ClearMenuBoxInterior(void) {
    CALL(aMenuBoxCoord2Tile);
    LD_BC(SCREEN_WIDTH + 1);
    ADD_HL_BC;
    CALL(aGetMenuBoxDims);
    DEC_B;
    DEC_C;
    CALL(aClearBox);
    RET;
}

void ClearWholeMenuBox(void) {
    CALL(aMenuBoxCoord2Tile);
    CALL(aGetMenuBoxDims);
    INC_C;
    INC_B;
    CALL(aClearBox);
    RET;
}

void MenuBoxCoord2Tile(void) {
    LD_A_addr(wMenuBorderLeftCoord);
    LD_C_A;
    LD_A_addr(wMenuBorderTopCoord);
    LD_B_A;
    // fallthrough

    return Coord2Tile();
}

uint8_t* MenuBoxCoord2Tile_Conv(void) {
    // LD_A_addr(wMenuBorderLeftCoord);
    // LD_C_A;
    // LD_A_addr(wMenuBorderTopCoord);
    // LD_B_A;
    // fallthrough

    return Coord2Tile_Conv(wram->wMenuBorderLeftCoord, wram->wMenuBorderTopCoord);
}

void Coord2Tile(void) {
    //  Return the address of wTilemap(c, b) in hl.
    XOR_A_A;
    LD_H_A;
    LD_L_B;
    LD_A_C;
    LD_B_H;
    LD_C_L;
    ADD_HL_HL;
    ADD_HL_HL;
    ADD_HL_BC;
    ADD_HL_HL;
    ADD_HL_HL;
    LD_C_A;
    XOR_A_A;
    LD_B_A;
    ADD_HL_BC;
    bccoord(0, 0, wTilemap);
    ADD_HL_BC;
    RET;
}

//  Return the address of wTilemap(c, b) in hl.
uint8_t* Coord2Tile_Conv(uint8_t c, uint8_t b) {
    // XOR_A_A;
    // LD_H_A;
    // LD_L_B;
    uint16_t hl = b;

    // LD_A_C;
    uint16_t a = c;

    // LD_B_H;
    // LD_C_L;
    uint16_t bc = hl;

    // ADD_HL_HL;
    // ADD_HL_HL;
    hl += (2 * hl);

    // ADD_HL_BC;
    hl += bc;

    // ADD_HL_HL;
    // ADD_HL_HL;
    hl += (2 * hl);

    // LD_C_A;
    // XOR_A_A;
    // LD_B_A;
    // ADD_HL_BC;
    hl += a;

    // bccoord(0, 0, wTilemap);
    // ADD_HL_BC;

    // RET;
    return wram->wTilemap + hl;
}

void MenuBoxCoord2Attr(void) {
    LD_A_addr(wMenuBorderLeftCoord);
    LD_C_A;
    LD_A_addr(wMenuBorderTopCoord);
    LD_B_A;
    // fallthrough

    return Coord2Attr();
}

uint8_t* MenuBoxCoord2Attr_Conv(void) {
    // LD_A_addr(wMenuBorderLeftCoord);
    // LD_C_A;
    // LD_A_addr(wMenuBorderTopCoord);
    // LD_B_A;
    // fallthrough
    return Coord2Attr_Conv(wram->wMenuBorderLeftCoord, wram->wMenuBorderTopCoord);
}

void Coord2Attr(void) {
    //  //  unreferenced
    //  Return the address of wAttrmap(c, b) in hl.
    XOR_A_A;
    LD_H_A;
    LD_L_B;
    LD_A_C;
    LD_B_H;
    LD_C_L;
    ADD_HL_HL;
    ADD_HL_HL;
    ADD_HL_BC;
    ADD_HL_HL;
    ADD_HL_HL;
    LD_C_A;
    XOR_A_A;
    LD_B_A;
    ADD_HL_BC;
    bccoord(0, 0, wAttrmap);
    ADD_HL_BC;
    RET;
}

//  //  unreferenced
//  Return the address of wAttrmap(c, b) in hl.
uint8_t* Coord2Attr_Conv(uint8_t c, uint8_t b) {
    // XOR_A_A;
    // LD_H_A;
    // LD_L_B;
    uint16_t hl = b;

    // LD_A_C;
    uint16_t a = c;

    // LD_B_H;
    // LD_C_L;
    uint16_t bc = hl;

    // ADD_HL_HL;
    // ADD_HL_HL;
    hl <<= 2;

    // ADD_HL_BC;
    hl += bc;

    // ADD_HL_HL;
    // ADD_HL_HL;
    hl <<= 2;

    // LD_C_A;
    // XOR_A_A;
    // LD_B_A;
    // ADD_HL_BC;
    hl += a;

    // bccoord(0, 0, wAttrmap);
    // ADD_HL_BC;
    // RET;
    return wram->wAttrmap + hl;
}

void LoadMenuHeader(void) {
    CALL(aCopyMenuHeader);
    CALL(aPushWindow);
    RET;
}

void LoadMenuHeader_Conv(uint16_t hl) {
    // CALL(aCopyMenuHeader);
    CopyMenuHeader_Conv(hl);
    CALL(aPushWindow);
    RET;
}

void CopyMenuHeader(void) {
    LD_DE(wMenuHeader);
    LD_BC(wMenuHeaderEnd - wMenuHeader);
    CALL(aCopyBytes);
    LDH_A_addr(hROMBank);
    LD_addr_A(wMenuDataBank);
    RET;
}

void CopyMenuHeader_Conv(uint16_t hl) {
    // LD_DE(wMenuHeader);
    // LD_BC(wMenuHeaderEnd - wMenuHeader);
    // CALL(aCopyBytes);
    CopyBytes_Conv(wMenuHeader, hl, (wMenuHeaderEnd - wMenuHeader));

    // LDH_A_addr(hROMBank);
    // LD_addr_A(wMenuDataBank);
    gb_write(wMenuDataBank, gb_read(hROMBank));
}

void StoreMenuCursorPosition(void) {
    LD_addr_A(wMenuCursorPosition);
    RET;
}

void StoreMenuCursorPosition_Conv(uint8_t a) {
    // LD_addr_A(wMenuCursorPosition);
    // RET;
    gb_write(wMenuCursorPosition, a);
}

void MenuTextbox(void) {
    PUSH_HL;
    CALL(aLoadMenuTextbox);
    POP_HL;
    JP(mPrintText);
}

void Menu_DummyFunction(void) {
    //  //  unreferenced
    RET;
}

void LoadMenuTextbox(void) {
    LD_HL(mLoadMenuTextbox_MenuHeader);
    CALL(aLoadMenuHeader);
    RET;

MenuHeader:
    // db ['MENU_BACKUP_TILES'];  // flags
    // menu_coords ['0', '12', 'SCREEN_WIDTH - 1', 'SCREEN_HEIGHT - 1'];
    // dw ['vTiles0'];
    // db ['0'];  // default option

    return MenuTextboxBackup();
}

void MenuTextboxBackup(void) {
    CALL(aMenuTextbox);
    CALL(aCloseWindow);
    RET;
}

void LoadStandardMenuHeader(void) {
    LD_HL(mLoadStandardMenuHeader_MenuHeader);
    CALL(aLoadMenuHeader);
    RET;

MenuHeader:
    // db ['MENU_BACKUP_TILES'];  // flags
    // menu_coords ['0', '0', 'SCREEN_WIDTH - 1', 'SCREEN_HEIGHT - 1'];
    // dw ['0'];
    // db ['1'];  // default option

    return Call_ExitMenu();
}

void Call_ExitMenu(void) {
    CALL(aExitMenu);
    RET;
}

void VerticalMenu(void) {
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = 0;
    CALL(aMenuBox);
    CALL(aUpdateSprites);
    CALL(aPlaceVerticalMenuItems);
    CALL(aApplyTilemap);
    CALL(aCopyMenuData);
    LD_A_addr(wMenuDataFlags);
    BIT_A(7);
    IF_Z goto cancel;
    CALL(aInitVerticalMenuCursor);
    CALL(aStaticMenuJoypad);
    CALL(aMenuClickSound);
    BIT_A(1);
    IF_Z goto okay;

cancel:
    SCF;
    RET;

okay:
    AND_A_A;
    RET;
}

// Displays a vertical menu. Returns false if the player cancels out of the menu.
bool VerticalMenu_Conv(void) {
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = 0;
    // CALL(aMenuBox);
    MenuBox_Conv();
    // CALL(aUpdateSprites);
    UpdateSprites_Conv();
    // CALL(aPlaceVerticalMenuItems);
    PlaceVerticalMenuItems_Conv();
    // CALL(aApplyTilemap);
    ApplyTilemap_Conv();
    // CALL(aCopyMenuData);
    CopyMenuData_Conv();
    // LD_A_addr(wMenuDataFlags);
    // BIT_A(7);
    // IF_Z goto cancel;
    if(!bit_test(wram->wMenuDataFlags, 7))
        return false;
    // CALL(aInitVerticalMenuCursor);
    InitVerticalMenuCursor_Conv();
    // CALL(aStaticMenuJoypad);
    const uint8_t a = StaticMenuJoypad_Conv();
    // CALL(aMenuClickSound);
    MenuClickSound_Conv(a);
    // BIT_A(1);
    // IF_Z goto okay;
    return !bit_test(a, 1);

// cancel:
    // SCF;
    // RET;

// okay:
    // AND_A_A;
    // RET;
}

void GetMenu2(void) {
    CALL(aLoadMenuHeader);
    CALL(aVerticalMenu);
    CALL(aCloseWindow);
    LD_A_addr(wMenuCursorY);
    RET;
}

void CopyNameFromMenu(void) {
    PUSH_HL;
    PUSH_BC;
    PUSH_AF;
    LD_HL(wMenuDataPointer);
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    INC_HL;
    INC_HL;
    POP_AF;
    CALL(aGetNthString);
    LD_D_H;
    LD_E_L;
    CALL(aCopyName1);
    POP_BC;
    POP_HL;
    RET;
}

void YesNoBox(void) {
    LD_BC(((SCREEN_WIDTH - 6) << 8) | 7);

    return PlaceYesNoBox();
}

void PlaceYesNoBox(void) {
    JR(mv_YesNoBox);
}

void PlaceGenericTwoOptionBox(void) {
    //  //  unreferenced
    CALL(aLoadMenuHeader);
    JR(mInterpretTwoOptionMenu);
}

void v_YesNoBox(void) {
    //  Return nc (yes) or c (no).
    PUSH_BC;
    LD_HL(mYesNoMenuHeader);
    CALL(aCopyMenuHeader);
    POP_BC;
    //  This seems to be an overflow prevention,
    //  but it was coded wrong.
    LD_A_B;
    CP_A(SCREEN_WIDTH - 1 - 5);
    IF_NZ goto okay;  // should this be "jr nc"?
    LD_A(SCREEN_WIDTH - 1 - 5);
    LD_B_A;

okay:
    LD_A_B;
    LD_addr_A(wMenuBorderLeftCoord);
    ADD_A(5);
    LD_addr_A(wMenuBorderRightCoord);
    LD_A_C;
    LD_addr_A(wMenuBorderTopCoord);
    ADD_A(4);
    LD_addr_A(wMenuBorderBottomCoord);
    CALL(aPushWindow);

    return InterpretTwoOptionMenu();
}

void InterpretTwoOptionMenu(void) {
    CALL(aVerticalMenu);
    PUSH_AF;
    LD_C(0xf);
    CALL(aDelayFrames);
    CALL(aCloseWindow);
    POP_AF;
    IF_C goto no;
    LD_A_addr(wMenuCursorY);
    CP_A(2);  // no
    IF_Z goto no;
    AND_A_A;
    RET;

no:
    LD_A(2);
    LD_addr_A(wMenuCursorY);
    SCF;
    RET;
}

void YesNoMenuHeader(void) {
    // db ['MENU_BACKUP_TILES'];  // flags
    // menu_coords ['10', '5', '15', '9'];
    // dw ['.MenuData'];
    // db ['1'];  // default option

MenuData:
    // db ['STATICMENU_CURSOR | STATICMENU_NO_TOP_SPACING'];  // flags
    // db ['2'];
    // db ['"YES@"'];
    // db ['"NO@"'];

    return OffsetMenuHeader();
}

void OffsetMenuHeader(void) {
    CALL(av_OffsetMenuHeader);
    CALL(aPushWindow);
    RET;
}

void v_OffsetMenuHeader(void) {
    PUSH_DE;
    CALL(aCopyMenuHeader);
    POP_DE;
    LD_A_addr(wMenuBorderLeftCoord);
    LD_H_A;
    LD_A_addr(wMenuBorderRightCoord);
    SUB_A_H;
    LD_H_A;
    LD_A_D;
    LD_addr_A(wMenuBorderLeftCoord);
    ADD_A_H;
    LD_addr_A(wMenuBorderRightCoord);
    LD_A_addr(wMenuBorderTopCoord);
    LD_L_A;
    LD_A_addr(wMenuBorderBottomCoord);
    SUB_A_L;
    LD_L_A;
    LD_A_E;
    LD_addr_A(wMenuBorderTopCoord);
    ADD_A_L;
    LD_addr_A(wMenuBorderBottomCoord);
    RET;
}

void DoNthMenu(void) {
    CALL(aDrawVariableLengthMenuBox);
    CALL(aMenuWriteText);
    CALL(aInitMenuCursorAndButtonPermissions);
    CALL(aGetStaticMenuJoypad);
    CALL(aGetMenuJoypad);
    CALL(aMenuClickSound);
    RET;
}

void SetUpMenu(void) {
    CALL(aDrawVariableLengthMenuBox);
    CALL(aMenuWriteText);
    CALL(aInitMenuCursorAndButtonPermissions);
    LD_HL(w2DMenuFlags1);
    SET_hl(7);
    RET;
}

void DrawVariableLengthMenuBox(void) {
    CALL(aCopyMenuData);
    CALL(aGetMenuIndexSet);
    CALL(aAutomaticGetMenuBottomCoord);
    CALL(aMenuBox);
    RET;
}

void MenuWriteText(void) {
    XOR_A_A;
    LDH_addr_A(hBGMapMode);
    CALL(aGetMenuIndexSet);              // sort out the text
    CALL(aRunMenuItemPrintingFunction);  // actually write it
    CALL(aSafeUpdateSprites);
    LDH_A_addr(hOAMUpdate);
    PUSH_AF;
    LD_A(0x1);
    LDH_addr_A(hOAMUpdate);
    CALL(aApplyTilemap);
    POP_AF;
    LDH_addr_A(hOAMUpdate);
    RET;
}

void AutomaticGetMenuBottomCoord(void) {
    LD_A_addr(wMenuBorderLeftCoord);
    LD_C_A;
    LD_A_addr(wMenuBorderRightCoord);
    SUB_A_C;
    LD_C_A;
    LD_A_addr(wMenuDataItems);
    ADD_A_A;
    INC_A;
    LD_B_A;
    LD_A_addr(wMenuBorderTopCoord);
    ADD_A_B;
    LD_addr_A(wMenuBorderBottomCoord);
    RET;
}

void GetMenuIndexSet(void) {
    LD_HL(wMenuDataIndicesPointer);
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    LD_A_addr(wWhichIndexSet);
    AND_A_A;
    IF_Z goto skip;
    LD_B_A;
    LD_C(-1);

loop:
    LD_A_hli;
    CP_A_C;
    IF_NZ goto loop;
    DEC_B;
    IF_NZ goto loop;

skip:
    LD_D_H;
    LD_E_L;
    LD_A_hl;
    LD_addr_A(wMenuDataItems);
    RET;
}

uint8_t* GetMenuIndexSet_Conv(void) {
    // LD_HL(wMenuDataIndicesPointer);
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    uint8_t* hl = GBToRAMAddr(wram->wMenuDataIndicesPointer);
    // LD_A_addr(wWhichIndexSet);
    // AND_A_A;
    // IF_Z goto skip;
    if(wram->wWhichIndexSet != 0) {
        // LD_B_A;
        // LD_C(-1);
        uint8_t b = wram->wWhichIndexSet;
        do {
        // loop:
            // LD_A_hli;
            // CP_A_C;
            // IF_NZ goto loop;
            // DEC_B;
            // IF_NZ goto loop;
        } while(*(hl++) != 0xff || --b != 0);
    }

// skip:
    // LD_D_H;
    // LD_E_L;
    // LD_A_hl;
    // LD_addr_A(wMenuDataItems);
    wram->wMenuDataItems = *hl;
    // RET;
    return hl;
}

void RunMenuItemPrintingFunction(void) {
    CALL(aMenuBoxCoord2Tile);
    LD_BC(2 * SCREEN_WIDTH + 2);
    ADD_HL_BC;

loop:
    INC_DE;
    LD_A_de;
    CP_A(-1);
    RET_Z;
    LD_addr_A(wMenuSelection);
    PUSH_DE;
    PUSH_HL;
    LD_D_H;
    LD_E_L;
    LD_HL(wMenuDataDisplayFunctionPointer);
    CALL(aRunMenuItemPrintingFunction__hl_);
    POP_HL;
    LD_DE(2 * SCREEN_WIDTH);
    ADD_HL_DE;
    POP_DE;
    goto loop;

_hl_:
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    JP_hl;
}

void InitMenuCursorAndButtonPermissions(void) {
    CALL(aInitVerticalMenuCursor);
    LD_HL(wMenuJoypadFilter);
    LD_A_addr(wMenuDataFlags);
    BIT_A(3);
    IF_Z goto disallow_select;
    SET_hl(START_F);

disallow_select:
    LD_A_addr(wMenuDataFlags);
    BIT_A(2);
    IF_Z goto disallow_left_right;
    SET_hl(D_LEFT_F);
    SET_hl(D_RIGHT_F);

disallow_left_right:
    RET;
}

void GetScrollingMenuJoypad(void) {
    CALL(aScrollingMenuJoypad);
    LD_HL(wMenuJoypadFilter);
    AND_A_hl;
    JR(mContinueGettingMenuJoypad);
}

bool GetScrollingMenuJoypad_Conv(void) {
    // CALL(aScrollingMenuJoypad);
    // LD_HL(wMenuJoypadFilter);
    // AND_A_hl;
    // JR(mContinueGettingMenuJoypad);
    return ContinueGettingMenuJoypad_Conv(ScrollingMenuJoypad_Conv() & wram->wMenuJoypadFilter);
}

void GetStaticMenuJoypad(void) {
    XOR_A_A;
    LD_addr_A(wMenuJoypad);
    CALL(aStaticMenuJoypad);

    return ContinueGettingMenuJoypad();
}

bool GetStaticMenuJoypad_Conv(void) {
    // XOR_A_A;
    // LD_addr_A(wMenuJoypad);
    wram->wMenuJoypad = 0;
    // CALL(aStaticMenuJoypad);

    return ContinueGettingMenuJoypad_Conv(StaticMenuJoypad_Conv());
}

void ContinueGettingMenuJoypad(void) {
    BIT_A(A_BUTTON_F);
    IF_NZ goto a_button;
    BIT_A(B_BUTTON_F);
    IF_NZ goto b_start;
    BIT_A(START_F);
    IF_NZ goto b_start;
    BIT_A(D_RIGHT_F);
    IF_NZ goto d_right;
    BIT_A(D_LEFT_F);
    IF_NZ goto d_left;
    XOR_A_A;
    LD_addr_A(wMenuJoypad);
    goto done;

d_right:
    LD_A(D_RIGHT);
    LD_addr_A(wMenuJoypad);
    goto done;

d_left:
    LD_A(D_LEFT);
    LD_addr_A(wMenuJoypad);
    goto done;

a_button:
    LD_A(A_BUTTON);
    LD_addr_A(wMenuJoypad);

done:
    CALL(aGetMenuIndexSet);
    LD_A_addr(wMenuCursorY);
    LD_L_A;
    LD_H(0);
    ADD_HL_DE;
    LD_A_hl;
    LD_addr_A(wMenuSelection);
    LD_A_addr(wMenuCursorY);
    LD_addr_A(wMenuCursorPosition);
    AND_A_A;
    RET;

b_start:
    LD_A(B_BUTTON);
    LD_addr_A(wMenuJoypad);
    LD_A(-1);
    LD_addr_A(wMenuSelection);
    SCF;
    RET;
}

bool ContinueGettingMenuJoypad_Conv(uint8_t a) {
    // BIT_A(A_BUTTON_F);
    // IF_NZ goto a_button;
    if(bit_test(a, A_BUTTON_F)) {
    // a_button:
        // LD_A(A_BUTTON);
        // LD_addr_A(wMenuJoypad);
        wram->wMenuJoypad = A_BUTTON;
    }
    // BIT_A(B_BUTTON_F);
    // IF_NZ goto b_start;
    // BIT_A(START_F);
    // IF_NZ goto b_start;
    else if(bit_test(a, B_BUTTON_F) || bit_test(a, START_F)) {
    // b_start:
        // LD_A(B_BUTTON);
        // LD_addr_A(wMenuJoypad);
        wram->wMenuJoypad = B_BUTTON;
        // LD_A(-1);
        // LD_addr_A(wMenuSelection);
        wram->wMenuSelection = 0xff;
        // SCF;
        // RET;
        return true;
    }
    // BIT_A(D_RIGHT_F);
    // IF_NZ goto d_right;
    else if(bit_test(a, D_RIGHT_F)) {
    // d_right:
        // LD_A(D_RIGHT);
        // LD_addr_A(wMenuJoypad);
        // goto done;
        wram->wMenuJoypad = D_RIGHT;
    }
    // BIT_A(D_LEFT_F);
    // IF_NZ goto d_left;
    else if(bit_test(a, D_LEFT_F)) {
    // d_left:
        // LD_A(D_LEFT);
        // LD_addr_A(wMenuJoypad);
        // goto done;
        wram->wMenuJoypad = D_LEFT;
    }
    // XOR_A_A;
    // LD_addr_A(wMenuJoypad);
    // goto done;
    else {
        wram->wMenuJoypad = 0;
    }

// done:
    // CALL(aGetMenuIndexSet);
    // LD_A_addr(wMenuCursorY);
    // LD_L_A;
    // LD_H(0);
    // ADD_HL_DE;
    // LD_A_hl;
    // LD_addr_A(wMenuSelection);
    wram->wMenuSelection = GetMenuIndexSet_Conv()[wram->wMenuCursorY];
    // LD_A_addr(wMenuCursorY);
    // LD_addr_A(wMenuCursorPosition);
    wram->wMenuCursorPosition = wram->wMenuCursorY;
    // AND_A_A;
    // RET;
    return false;
}

void PlaceMenuStrings(void) {
    PUSH_DE;
    LD_HL(wMenuDataPointerTableAddr);
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    LD_A_addr(wMenuSelection);
    CALL(aGetNthString);
    LD_D_H;
    LD_E_L;
    POP_HL;
    CALL(aPlaceString);
    RET;
}

void PlaceNthMenuStrings(void) {
    PUSH_DE;
    LD_A_addr(wMenuSelection);
    CALL(aGetMenuDataPointerTableEntry);
    INC_HL;
    INC_HL;
    LD_A_hli;
    LD_D_hl;
    LD_E_A;
    POP_HL;
    CALL(aPlaceString);
    RET;
}

void GetNthMenuStrings(void) {
    //  //  unreferenced
    CALL(aGetMenuDataPointerTableEntry);
    INC_HL;
    INC_HL;
    LD_A_hli;
    LD_D_hl;
    LD_E_A;
    RET;
}

void MenuJumptable(void) {
    LD_A_addr(wMenuSelection);
    CALL(aGetMenuDataPointerTableEntry);
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    JP_hl;
}

void GetMenuDataPointerTableEntry(void) {
    LD_E_A;
    LD_D(0);
    LD_HL(wMenuDataPointerTableAddr);
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    ADD_HL_DE;
    ADD_HL_DE;
    ADD_HL_DE;
    ADD_HL_DE;
    RET;
}

void ClearWindowData(void) {
    LD_HL(wMenuMetadata);
    CALL(aClearWindowData_ClearMenuData);
    LD_HL(wMenuHeader);
    CALL(aClearWindowData_ClearMenuData);
    LD_HL(wMenuData);
    CALL(aClearWindowData_ClearMenuData);
    LD_HL(wMoreMenuData);
    CALL(aClearWindowData_ClearMenuData);

    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(MBANK(awWindowStack));
    LDH_addr_A(rSVBK);

    XOR_A_A;
    LD_HL(wWindowStackBottom);
    LD_hld_A;
    LD_hld_A;
    LD_A_L;
    LD_addr_A(wWindowStackPointer);
    LD_A_H;
    LD_addr_A(wWindowStackPointer + 1);

    POP_AF;
    LDH_addr_A(rSVBK);
    RET;

ClearMenuData:
    LD_BC(wMenuMetadataEnd - wMenuMetadata);
    // assert ['wMenuMetadataEnd - wMenuMetadata == wMenuHeaderEnd - wMenuHeader'];
    // assert ['wMenuMetadataEnd - wMenuMetadata == wMenuDataEnd - wMenuData'];
    // assert ['wMenuMetadataEnd - wMenuMetadata == wMoreMenuDataEnd - wMoreMenuData'];
    XOR_A_A;
    CALL(aByteFill);
    RET;
}

void ClearWindowData_Conv(void) {
    ByteFill_Conv(wMenuMetadata, (wMenuMetadataEnd - wMenuMetadata), 0);
    ByteFill_Conv(wMenuHeader, (wMenuHeaderEnd - wMenuHeader), 0);
    ByteFill_Conv(wMenuData, (wMenuDataEnd - wMenuData), 0);
    ByteFill_Conv(wMoreMenuData, (wMoreMenuDataEnd - wMoreMenuData), 0);

    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    uint8_t oldvbk = gb_read(rSVBK);

    // LD_A(BANK(wWindowStack));
    // LDH_addr_A(rSVBK);
    gb_write(rSVBK, MBANK(awWindowStack));

    // XOR_A_A;
    // LD_HL(wWindowStackBottom);
    // LD_hld_A;
    gb_write(wWindowStackBottom, 0);
    // LD_hld_A;
    gb_write(wWindowStackBottom - 1, 0);

    // LD_A_L;
    // LD_addr_A(wWindowStackPointer);
    gb_write(wWindowStackPointer, LOW(wWindowStackBottom - 2));
    // LD_A_H;
    // LD_addr_A(wWindowStackPointer + 1);
    gb_write(wWindowStackPointer + 1, HIGH(wWindowStackBottom - 2));

    // POP_AF;
    // LDH_addr_A(rSVBK);
    gb_write(rSVBK, oldvbk);
    // RET;
}

void MenuClickSound(void) {
    PUSH_AF;
    AND_A(A_BUTTON | B_BUTTON);
    IF_Z goto nosound;
    LD_HL(wMenuFlags);
    BIT_hl(3);
    IF_NZ goto nosound;
    CALL(aPlayClickSFX);

nosound:
    POP_AF;
    RET;
}

void MenuClickSound_Conv(uint8_t a) {
    // PUSH_AF;
    // AND_A(A_BUTTON | B_BUTTON);
    // IF_Z goto nosound;
    if(a & (A_BUTTON | B_BUTTON)) {
        // LD_HL(wMenuFlags);
        // BIT_hl(3);
        // IF_NZ goto nosound;
        if(!bit_test(wram->wMenuFlags, 3)) {
            // CALL(aPlayClickSFX);
            PlayClickSFX_Conv();
        }
    }

// nosound:
    // POP_AF;
    // RET;
}

void PlayClickSFX(void) {
    PUSH_DE;
    LD_DE(SFX_READ_TEXT_2);
    CALL(aPlaySFX);
    POP_DE;
    RET;
}

void PlayClickSFX_Conv(void) {
    // PUSH_DE;
    // LD_DE(SFX_READ_TEXT_2);
    // CALL(aPlaySFX);
    // POP_DE;
    // RET;
    return PlaySFX_Conv(SFX_READ_TEXT_2);
}

void MenuTextboxWaitButton(void) {
    CALL(aMenuTextbox);
    CALL(aWaitButton);
    CALL(aExitMenu);
    RET;
}

void Place2DMenuItemName(void) {
    LDH_addr_A(hTempBank);
    LDH_A_addr(hROMBank);
    PUSH_AF;
    LDH_A_addr(hTempBank);
    RST(aBankswitch);

    CALL(aPlaceString);
    POP_AF;
    RST(aBankswitch);

    RET;
}

void v_2DMenu(void) {
    LDH_A_addr(hROMBank);
    LD_addr_A(wMenuData_2DMenuItemStringsBank);
    FARCALL(av_2DMenu_);
    LD_A_addr(wMenuCursorPosition);
    RET;
}

void InterpretBattleMenu(void) {
    LDH_A_addr(hROMBank);
    LD_addr_A(wMenuData_2DMenuItemStringsBank);
    FARCALL(av_InterpretBattleMenu);
    LD_A_addr(wMenuCursorPosition);
    RET;
}

void InterpretMobileMenu(void) {
    //  //  unreferenced
    LDH_A_addr(hROMBank);
    LD_addr_A(wMenuData_2DMenuItemStringsBank);
    FARCALL(av_InterpretMobileMenu);
    LD_A_addr(wMenuCursorPosition);
    RET;
}
