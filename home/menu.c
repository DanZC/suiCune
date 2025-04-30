#include "../constants.h"
#include "menu.h"
#include "delay.h"
#include "copy.h"
#include "copy_name.h"
#include "text.h"
#include "map_objects.h"
#include "audio.h"
#include "tilemap.h"
#include "window.h"
#include "joypad.h"
#include "../charmap.h"
#include "../engine/menus/menu.h"

const void* gMenuDataPointer;

void Load2DMenuData(const uint8_t* de) {
    // uint8_t* hl = &wram->w2DMenuCursorInitY;
    // uint8_t b = (w2DMenuDataEnd - w2DMenuData);

    // do {
    //     *(hl++) = *(de++);
    // } while(--b != 0);
    wram->w2DMenuCursorInitY = de[0];
    wram->w2DMenuCursorInitX = de[1];
    wram->w2DMenuNumRows = de[2];
    wram->w2DMenuNumCols = de[3];
    wram->w2DMenuFlags1 = de[4];
    wram->w2DMenuFlags2 = de[5];
    wram->w2DMenuCursorOffsets = de[6];
    wram->wMenuJoypadFilter = de[7];

    // Reset menu state
    wram->wMenuCursorY = 0x1;
    wram->wMenuCursorX = 0x1;
    wram->wCursorOffCharacter = 0;
    wram->wCursorCurrentTile = 0;
}

uint8_t StaticMenuJoypad(void) {
    // CALLFAR(av_StaticMenuJoypad);
    v_StaticMenuJoypad_Conv();
    // CALL(aGetMenuJoypad);
    // RET;
    return GetMenuJoypad();
}

uint8_t ScrollingMenuJoypad(void) {
    // CALLFAR(av_ScrollingMenuJoypad);
    v_ScrollingMenuJoypad_Conv();
    // CALL(aGetMenuJoypad);
    // RET;
    return GetMenuJoypad();
}

uint8_t GetMenuJoypad(void) {
    uint8_t pad_last = (hram->hJoyLast & (D_PAD));
    uint8_t button_last = (hram->hJoyPressed & (BUTTONS));
    return (pad_last | button_last);
}

void PlaceHollowCursor(void) {
    // LD_HL(wCursorCurrentTile);
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // LD_hl(CHAR_RIGHT_CURSOR_SEL);
    // RET;
    if(wram->wCursorCurrentTile != 0)
        wram->wTilemap[wram->wCursorCurrentTile - 1] = CHAR_RIGHT_CURSOR_SEL;
}

uint8_t* HideCursor(void){
    if(wram->wCursorCurrentTile != 0) {
        wram->wTilemap[wram->wCursorCurrentTile - 1] = CHAR_SPACE;
        return wram->wTilemap + (wram->wCursorCurrentTile - 1);
    }
    return NULL;
}

void PushWindow(void) {
    // CALLFAR(av_PushWindow);
    // RET;
    return v_PushWindow_Conv();
}

void ExitMenu(void) {
    // PUSH_AF;
    // CALLFAR(av_ExitMenu);
    // POP_AF;
    // RET;
    return v_ExitMenu();
}

void InitVerticalMenuCursor(const struct MenuData* data) {
    // CALLFAR(av_InitVerticalMenuCursor);
    // RET;
    return v_InitVerticalMenuCursor_Conv(data);
}

void CloseWindow(void) {
    // PUSH_AF;
    // CALL(aExitMenu);
    ExitMenu();
    // CALL(aApplyTilemap);
    ApplyTilemap();
    // CALL(aUpdateSprites);
    UpdateSprites();
    // POP_AF;
    // RET;
}

static const uint8_t* RestoreTileBackup_copy(uint8_t* hl, const uint8_t* de) {
    // CALL(aGetMenuBoxDims);
    // INC_B;
    // INC_C;
    uint8_t b, c, c2;
    GetMenuBoxDims(&c, &b);
    b++, c++;

    do {
    // row:
        // PUSH_BC;
        c2 = c;
        // PUSH_HL;
        uint8_t* hl2 = hl;

        do {
        // col:
            // LD_A_de;
            // LD_hli_A;
            *(hl++) = *(de++);
            // DEC_DE;
            // DEC_C;
            // IF_NZ goto col;
        } while(--c != 0);

        // POP_HL;
        // LD_BC(SCREEN_WIDTH);
        // ADD_HL_BC;
        hl = hl2 + SCREEN_WIDTH;
        // POP_BC;
        c = c2;
        // DEC_B;
        // IF_NZ goto row;
    } while(--b != 0);

    // RET;
    return de;
}

void RestoreTileBackup(const uint8_t* de) {
    // CALL(aMenuBoxCoord2Tile);
    uint8_t* hl = MenuBoxCoord2Tile();
    // CALL(aRestoreTileBackup_copy);
    de = RestoreTileBackup_copy(hl, de);
    // CALL(aMenuBoxCoord2Attr);
    hl = MenuBoxCoord2Attr();
    // CALL(aRestoreTileBackup_copy);
    RestoreTileBackup_copy(hl, de);
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

void PopWindow_Conv2(struct MenuHeader* hl) {
    CopyMenuHeader(hl);
}

// w = c, h = b
void GetMenuBoxDims(uint8_t* w, uint8_t* h) {
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
    CopyBytes(de, hl, bc);
}

const struct MenuData* GetMenuData(void) {
    return (const struct MenuData*)gMenuDataPointer;
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
    // CALL(aCopyMenuData);
    const struct MenuData* data = GetMenuData();
    // LD_HL(wMenuDataPointer);
    // LD_E_hl;
    // INC_HL;
    // LD_D_hl;
    // CALL(aGetMenuTextStartCoord);
    uint8_t b, c;
    GetMenuTextStartCoord(data, &b, &c);
    // CALL(aCoord2Tile);  // hl now contains the tilemap address where we will start printing text.
    uint8_t* hl = Coord2Tile(c, b);
    // INC_DE;
    // LD_A_de;  // Number of items
    // INC_DE;
    // LD_B_A;
    struct TextPrintState st = {.hl = hl};

    for(uint8_t b = 0; b < data->verticalMenu.count; ++b) {
    // loop:
        // PUSH_BC;
        // CALL(aPlaceString);
        st.de = U82C(data->verticalMenu.options[b]);
        PlaceString(&st, st.hl);
        // INC_DE;
        // LD_BC(2 * SCREEN_WIDTH);
        // ADD_HL_BC;
        st.hl += 2 * SCREEN_WIDTH;
        // POP_BC;
        // DEC_B;
        // IF_NZ goto loop;
    }

    // LD_A_addr(wMenuDataFlags);
    // BIT_A(4);
    // RET_Z;
    if(!bit_test(data->flags, STATICMENU_PLACE_TITLE_F))
        return;

    // CALL(aMenuBoxCoord2Tile);
    // LD_A_de;
    // LD_C_A;
    // INC_DE;
    // LD_B(0);
    // ADD_HL_BC;
    // st.hl = MenuBoxCoord2Tile() + *(st.de++);
    // JP(mPlaceString);
    // PlaceString(&st, st.hl);
}

void MenuBox(void) {
    uint8_t w, h;
    // CALL(aMenuBoxCoord2Tile);
    uint8_t* ptr = MenuBoxCoord2Tile();
    // CALL(aGetMenuBoxDims);
    GetMenuBoxDims(&w, &h);
    // DEC_B;
    // DEC_C;
    // JP(mTextbox);
    return Textbox(ptr, h - 1, w - 1);
}

void GetMenuTextStartCoord(const struct MenuData* data, uint8_t* b, uint8_t* c) {
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
    if(!bit_test(data->flags, STATICMENU_NO_TOP_SPACING_F)) {
        // INC_B;
        ++(*b);
    }

// bit_6_set:
    //  bit 7: if set, leave extra room on the left
    // LD_A_addr(wMenuDataFlags);
    // BIT_A(7);
    // IF_Z goto bit_7_clear;
    if(bit_test(data->flags, STATICMENU_CURSOR_F)) {
        // INC_C;
        ++(*c);
    }

// bit_7_clear:
    // RET;
}

void ClearMenuBoxInterior(void) {
    // CALL(aMenuBoxCoord2Tile);
    // LD_BC(SCREEN_WIDTH + 1);
    // ADD_HL_BC;
    uint8_t* hl = MenuBoxCoord2Tile() + SCREEN_WIDTH + 1;
    // CALL(aGetMenuBoxDims);
    uint8_t c, b;
    GetMenuBoxDims(&c, &b);
    // DEC_B;
    // DEC_C;
    // CALL(aClearBox);
    ClearBox(hl, c, b);
    // RET;
}

void ClearWholeMenuBox(void) {
    // CALL(aMenuBoxCoord2Tile);
    uint8_t* hl = MenuBoxCoord2Tile();
    // CALL(aGetMenuBoxDims);
    uint8_t c, b;
    GetMenuBoxDims(&c, &b);
    // INC_C;
    // INC_B;
    // CALL(aClearBox);
    ClearBox(hl, c + 1, b + 1);
    // RET;
}

uint8_t* MenuBoxCoord2Tile(void) {
    // LD_A_addr(wMenuBorderLeftCoord);
    // LD_C_A;
    // LD_A_addr(wMenuBorderTopCoord);
    // LD_B_A;
    // fallthrough

    return Coord2Tile(wram->wMenuBorderLeftCoord, wram->wMenuBorderTopCoord);
}

//  Return the address of wTilemap(c, b) in hl.
uint8_t* Coord2Tile(uint8_t c, uint8_t b) {
    // XOR_A_A;
    // LD_H_A;
    // LD_L_B;
    // uint16_t hl = b;

    // LD_A_C;
    // uint16_t a = c;

    // LD_B_H;
    // LD_C_L;
    // uint16_t bc = hl;

    // ADD_HL_HL;
    // ADD_HL_HL;
    // hl <<= 2;

    // ADD_HL_BC;
    // hl += bc;

    // ADD_HL_HL;
    // ADD_HL_HL;
    // hl <<= 2;

    // LD_C_A;
    // XOR_A_A;
    // LD_B_A;
    // ADD_HL_BC;
    // hl += a;

    // bccoord(0, 0, wTilemap);
    // ADD_HL_BC;

    // RET;
    return coord(c, b, wram->wTilemap);
}

uint8_t* MenuBoxCoord2Attr(void) {
    // LD_A_addr(wMenuBorderLeftCoord);
    // LD_C_A;
    // LD_A_addr(wMenuBorderTopCoord);
    // LD_B_A;
    // fallthrough
    return Coord2Attr(wram->wMenuBorderLeftCoord, wram->wMenuBorderTopCoord);
}

//  //  unreferenced
//  Return the address of wAttrmap(c, b) in hl.
uint8_t* Coord2Attr(uint8_t c, uint8_t b) {
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

void LoadMenuHeader(const struct MenuHeader* hl) {
    // CALL(aCopyMenuHeader);
    CopyMenuHeader(hl);
    // CALL(aPushWindow);
    PushWindow();
    // RET;
}

void CopyMenuHeader(const struct MenuHeader* hl) {
    // LD_DE(wMenuHeader);
    // LD_BC(wMenuHeaderEnd - wMenuHeader);
    // CALL(aCopyBytes);
    wram->wMenuFlags = hl->flags;
    wram->wMenuBorderLeftCoord = hl->coord.x1;
    wram->wMenuBorderRightCoord = hl->coord.x2;
    wram->wMenuBorderTopCoord = hl->coord.y1;
    wram->wMenuBorderBottomCoord = hl->coord.y2;
    wram->wMenuCursorPosition = hl->defaultOption;

    gMenuDataPointer = hl->data;

    // LDH_A_addr(hROMBank);
    // LD_addr_A(wMenuDataBank);
}

void StoreMenuCursorPosition(uint8_t a) {
    // LD_addr_A(wMenuCursorPosition);
    // RET;
    wram->wMenuCursorPosition = a;
}

void MenuTextbox(const struct TextCmd* hl) {
    // PUSH_HL;
    // CALL(aLoadMenuTextbox);
    LoadMenuTextbox();
    // POP_HL;
    // JP(mPrintText);
    PrintText(hl);
}

void Menu_DummyFunction(void) {
    //  //  unreferenced
    // RET;
}

void LoadMenuTextbox(void) {
    // LD_HL(mLoadMenuTextbox_MenuHeader);
    // CALL(aLoadMenuHeader);
    // RET;

    static const struct MenuHeader header = {
        .flags = MENU_BACKUP_TILES,  // flags
        .coord = menu_coords(0, 12, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1),
        .data = &((struct vram_s*)gb.vram)->vTiles0,
        .defaultOption = 0,  // default option
    };

    LoadMenuHeader(&header);
}

void MenuTextboxBackup(const struct TextCmd* hl) {
    // CALL(aMenuTextbox);
    MenuTextbox(hl);
    // CALL(aCloseWindow);
    CloseWindow();
    // RET;
}

void LoadStandardMenuHeader(void) {
    static const struct MenuHeader header = {
        .flags=MENU_BACKUP_TILES,  // flags
        .coord = menu_coords(0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1),
        .data = NULL,
        .defaultOption = 1,  // default option
    };
    // LD_HL(mLoadStandardMenuHeader_MenuHeader);
    // CALL(aLoadMenuHeader);
    // RET;
    LoadMenuHeader(&header);
}

void Call_ExitMenu(void) {
    CALL(aExitMenu);
    RET;
}

// Displays a vertical menu. Returns false if the player cancels out of the menu.
bool VerticalMenu(void) {
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = BGMAPMODE_NONE;
    // CALL(aMenuBox);
    MenuBox();
    // CALL(aUpdateSprites);
    UpdateSprites();
    // CALL(aPlaceVerticalMenuItems);
    PlaceVerticalMenuItems();
    // CALL(aApplyTilemap);
    ApplyTilemap();
    // CALL(aCopyMenuData);
    const struct MenuData* data = GetMenuData();
    // LD_A_addr(wMenuDataFlags);
    // BIT_A(7);
    // IF_Z goto cancel;
    if(!bit_test(data->flags, 7))
        return false;
    // CALL(aInitVerticalMenuCursor);
    InitVerticalMenuCursor(data);
    // CALL(aStaticMenuJoypad);
    const uint8_t a = StaticMenuJoypad();
    // CALL(aMenuClickSound);
    MenuClickSound(a);
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

u8_flag_s GetMenu2_Conv(const struct MenuHeader* hl) {
    // CALL(aLoadMenuHeader);
    LoadMenuHeader(hl);
    // CALL(aVerticalMenu);
    bool cancel = !VerticalMenu();
    // CALL(aCloseWindow);
    CloseWindow();
    // LD_A_addr(wMenuCursorY);
    // RET;
    return u8_flag(wram->wMenuCursorY, cancel);
}

void CopyNameFromMenu(uint8_t a) {
    // PUSH_HL;
    // PUSH_BC;
    // PUSH_AF;
    // LD_HL(wMenuDataPointer);
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    const struct MenuData* data = GetMenuData();
    // INC_HL;
    // INC_HL;
    // POP_AF;
    // CALL(aGetNthString);
    // LD_D_H;
    // LD_E_L;
    // CALL(aCopyName1);
    CopyName1(U82C(data->verticalMenu.options[a]));
    // POP_BC;
    // POP_HL;
    // RET;
}

//  Return true (yes) or false (no).
bool YesNoBox(void) {
    // LD_BC(((SCREEN_WIDTH - 6) << 8) | 7);
    return v_YesNoBox((SCREEN_WIDTH - 6), 7);
}

//  Return true (yes) or false (no).
bool PlaceYesNoBox(uint8_t b, uint8_t c) {
    // LD_BC(((SCREEN_WIDTH - 6) << 8) | 7);
    return v_YesNoBox(b, c);
}

void PlaceGenericTwoOptionBox(void) {
    //  //  unreferenced
    CALL(aLoadMenuHeader);
    JR(mInterpretTwoOptionMenu);
}

//  Return true (yes) or false (no).
bool v_YesNoBox(uint8_t b, uint8_t c) {
    // PUSH_BC;
    // LD_HL(mYesNoMenuHeader);
    // CALL(aCopyMenuHeader);
    CopyMenuHeader(&YesNoMenuHeader);
    // POP_BC;
    //  This seems to be an overflow prevention,
    //  but it was coded wrong.
    // LD_A_B;
    // CP_A(SCREEN_WIDTH - 1 - 5);
    // IF_NZ goto okay;  // should this be "jr nc"?
#if BUGFIX_YESNO_OVERFLOW
    if(b >= SCREEN_WIDTH - 1 - 5)
#else
    if(b == SCREEN_WIDTH - 1 - 5)
#endif
    {
        // LD_A(SCREEN_WIDTH - 1 - 5);
        // LD_B_A;
        b = SCREEN_WIDTH - 1 - 5;
    }

// okay:
    // LD_A_B;
    // LD_addr_A(wMenuBorderLeftCoord);
    wram->wMenuBorderLeftCoord = b;
    // ADD_A(5);
    // LD_addr_A(wMenuBorderRightCoord);
    wram->wMenuBorderRightCoord = b + 5;
    // LD_A_C;
    // LD_addr_A(wMenuBorderTopCoord);
    wram->wMenuBorderTopCoord = c;
    // ADD_A(4);
    // LD_addr_A(wMenuBorderBottomCoord);
    wram->wMenuBorderBottomCoord = c + 4;
    PushWindow();
    // CALL(aPushWindow);

    return InterpretTwoOptionMenu();
}

bool InterpretTwoOptionMenu(void) {
    // CALL(aVerticalMenu);
    bool cancel = !VerticalMenu();
    // PUSH_AF;
    // LD_C(0xf);
    // CALL(aDelayFrames);
    DelayFrames(0xf);
    // CALL(aCloseWindow);
    CloseWindow();
    // POP_AF;
    // IF_C goto no;
    // LD_A_addr(wMenuCursorY);
    // CP_A(2);  // no
    // IF_Z goto no;
    if(cancel || wram->wMenuCursorY == 2) {
    // no:
        // LD_A(2);
        // LD_addr_A(wMenuCursorY);
        wram->wMenuCursorY = 2;
        // SCF;
        // RET;
        return false;
    }
    // AND_A_A;
    // RET;
    return true;
}

const struct MenuHeader YesNoMenuHeader = {
    .flags = MENU_BACKUP_TILES,  // flags
    .coord = menu_coords(10, 5, 15, 9),
    // dw ['.MenuData'];
    .data = &(struct MenuData) {
        .flags = STATICMENU_CURSOR | STATICMENU_NO_TOP_SPACING,  // flags
        // db ['2'];
        .verticalMenu = {
            .count = 2,
            .options = (const char* []){
                "YES@",
                "NO@",
            },
        },
    },
    .defaultOption = 1  // default option
};

void OffsetMenuHeader(const struct MenuHeader* hl, uint8_t d, uint8_t e) {
    // CALL(av_OffsetMenuHeader);
    v_OffsetMenuHeader(hl, d, e);
    // CALL(aPushWindow);
    PushWindow();
    // RET;
}

void v_OffsetMenuHeader(const struct MenuHeader* hl, uint8_t d, uint8_t e) {
    // PUSH_DE;
    // CALL(aCopyMenuHeader);
    CopyMenuHeader(hl);
    // POP_DE;
    // LD_A_addr(wMenuBorderLeftCoord);
    // LD_H_A;
    // LD_A_addr(wMenuBorderRightCoord);
    // SUB_A_H;
    // LD_H_A;
    uint8_t h = wram->wMenuBorderRightCoord - wram->wMenuBorderLeftCoord;
    // LD_A_D;
    // LD_addr_A(wMenuBorderLeftCoord);
    wram->wMenuBorderLeftCoord = d;
    // ADD_A_H;
    // LD_addr_A(wMenuBorderRightCoord);
    wram->wMenuBorderRightCoord = d + h;
    // LD_A_addr(wMenuBorderTopCoord);
    // LD_L_A;
    // LD_A_addr(wMenuBorderBottomCoord);
    // SUB_A_L;
    uint8_t l = wram->wMenuBorderBottomCoord - wram->wMenuBorderTopCoord;
    // LD_L_A;
    // LD_A_E;
    // LD_addr_A(wMenuBorderTopCoord);
    wram->wMenuBorderTopCoord = e;
    // ADD_A_L;
    // LD_addr_A(wMenuBorderBottomCoord);
    wram->wMenuBorderBottomCoord = e + l;
    // RET;
}

u8_flag_s DoNthMenu(void) {
    // CALL(aDrawVariableLengthMenuBox);
    DrawVariableLengthMenuBox();
    // CALL(aMenuWriteText);
    MenuWriteText();
    // CALL(aInitMenuCursorAndButtonPermissions);
    InitMenuCursorAndButtonPermissions();
    // CALL(aGetStaticMenuJoypad);
    bool cancel = GetStaticMenuJoypad();
    // CALL(aGetMenuJoypad);
    uint8_t joypad = GetMenuJoypad();
    // CALL(aMenuClickSound);
    MenuClickSound(joypad);
    // RET;
    return u8_flag(joypad, cancel);
}

void SetUpMenu(void) {
    // CALL(aDrawVariableLengthMenuBox);
    DrawVariableLengthMenuBox();
    // CALL(aMenuWriteText);
    MenuWriteText();
    // CALL(aInitMenuCursorAndButtonPermissions);
    InitMenuCursorAndButtonPermissions();
    // LD_HL(w2DMenuFlags1);
    // SET_hl(7);
    bit_set(wram->w2DMenuFlags1, MENU2D_DISABLE_MENU_FILTER_F);
    // RET;
}

void DrawVariableLengthMenuBox(void) {
    // CALL(aCopyMenuData);
    const struct MenuData* data = GetMenuData();
    // CALL(aGetMenuIndexSet);
    GetMenuIndexSet(data);
    // CALL(aAutomaticGetMenuBottomCoord);
    uint8_t b, c;
    AutomaticGetMenuBottomCoord(&b, &c);
    // CALL(aMenuBox);
    MenuBox();
    // RET;
}

void MenuWriteText(void) {
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = BGMAPMODE_NONE;
    const struct MenuData* data = GetMenuData();
    // CALL(aGetMenuIndexSet);              // sort out the text
    const uint8_t* idxSet = GetMenuIndexSet(data);
    // CALL(aRunMenuItemPrintingFunction);  // actually write it
    RunMenuItemPrintingFunction(data, idxSet);
    // CALL(aSafeUpdateSprites);
    SafeUpdateSprites();
    // LDH_A_addr(hOAMUpdate);
    // PUSH_AF;
    uint8_t oam = hram->hOAMUpdate;
    // LD_A(0x1);
    // LDH_addr_A(hOAMUpdate);
    hram->hOAMUpdate = 0x1;
    // CALL(aApplyTilemap);
    ApplyTilemap();
    // POP_AF;
    // LDH_addr_A(hOAMUpdate);
    hram->hOAMUpdate = oam;
    // RET;
}

void AutomaticGetMenuBottomCoord(uint8_t* b, uint8_t* c) {
    // LD_A_addr(wMenuBorderLeftCoord);
    // LD_C_A;
    // LD_A_addr(wMenuBorderRightCoord);
    // SUB_A_C;
    // LD_C_A;
    *c = wram->wMenuBorderRightCoord - wram->wMenuBorderLeftCoord;
    // LD_A_addr(wMenuDataItems);
    // ADD_A_A;
    // INC_A;
    // LD_B_A;
    *b = (wram->wMenuDataItems << 1) + 1;
    // LD_A_addr(wMenuBorderTopCoord);
    // ADD_A_B;
    // LD_addr_A(wMenuBorderBottomCoord);
    wram->wMenuBorderBottomCoord = wram->wMenuBorderTopCoord + *b;
    // RET;
}

const uint8_t* GetMenuIndexSet(const struct MenuData* data) {
    // LD_HL(wMenuDataIndicesPointer);
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    const uint8_t* hl = data->setupMenu.itemList[wram->wWhichIndexSet];
    // LD_A_addr(wWhichIndexSet);
    // AND_A_A;
    // IF_Z goto skip;
    // if(wram->wWhichIndexSet != 0) {
        // LD_B_A;
        // LD_C(-1);
        // uint8_t b = wram->wWhichIndexSet;
        // do {
        // loop:
            // LD_A_hli;
            // CP_A_C;
            // IF_NZ goto loop;
            // DEC_B;
            // IF_NZ goto loop;
        // } while(*(hl++) != 0xff || --b != 0);
    // }

// skip:
    // LD_D_H;
    // LD_E_L;
    // LD_A_hl;
    // LD_addr_A(wMenuDataItems);
    wram->wMenuDataItems = *hl;
    // RET;
    return hl;
}

void RunMenuItemPrintingFunction(const struct MenuData* data, const uint8_t* de) {
    // CALL(aMenuBoxCoord2Tile);
    // LD_BC(2 * SCREEN_WIDTH + 2);
    // ADD_HL_BC;
    uint8_t* hl = MenuBoxCoord2Tile() + (2 * SCREEN_WIDTH + 2);

    while(1) {
    // loop:
        // INC_DE;
        ++de;
        // LD_A_de;
        // CP_A(-1);
        // RET_Z;
        if(*de == 0xff)
            return;
        // LD_addr_A(wMenuSelection);
        wram->wMenuSelection = *de;
        // PUSH_DE;
        // PUSH_HL;
        // LD_D_H;
        // LD_E_L;
        // LD_HL(wMenuDataDisplayFunctionPointer);
        // CALL(aRunMenuItemPrintingFunction__hl_);
        data->setupMenu.displayFunction(data->setupMenu.stringsList, hl, *de);
        // POP_HL;
        // LD_DE(2 * SCREEN_WIDTH);
        // ADD_HL_DE;
        hl += 2 * SCREEN_WIDTH;
        // POP_DE;
        // goto loop;
    }

// _hl_:
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // JP_hl;
}

void InitMenuCursorAndButtonPermissions(void) {
    const struct MenuData* data = GetMenuData();
    // CALL(aInitVerticalMenuCursor);
    InitVerticalMenuCursor(data);
    GetMenuIndexSet(data);
    wram->w2DMenuNumRows = wram->wMenuDataItems;
    // LD_HL(wMenuJoypadFilter);
    // LD_A_addr(wMenuDataFlags);
    // BIT_A(3);
    // IF_Z goto disallow_select;
    if(bit_test(data->flags, STATICMENU_ENABLE_START_F)) {
        // SET_hl(START_F);
        bit_set(wram->wMenuJoypadFilter, START_F);
    }
// disallow_select:
    // LD_A_addr(wMenuDataFlags);
    // BIT_A(2);
    // IF_Z goto disallow_left_right;
    if(bit_test(data->flags, STATICMENU_ENABLE_LEFT_RIGHT_F)) {
        // SET_hl(D_LEFT_F);
        // SET_hl(D_RIGHT_F);
        bit_set(wram->wMenuJoypadFilter, D_LEFT_F);
        bit_set(wram->wMenuJoypadFilter, D_RIGHT_F);
    }

// disallow_left_right:
    // RET;
}

bool GetScrollingMenuJoypad(void) {
    // CALL(aScrollingMenuJoypad);
    // LD_HL(wMenuJoypadFilter);
    // AND_A_hl;
    // JR(mContinueGettingMenuJoypad);
    return ContinueGettingMenuJoypad(ScrollingMenuJoypad() & wram->wMenuJoypadFilter);
}

bool GetStaticMenuJoypad(void) {
    // XOR_A_A;
    // LD_addr_A(wMenuJoypad);
    wram->wMenuJoypad = 0;
    // CALL(aStaticMenuJoypad);

    return ContinueGettingMenuJoypad(StaticMenuJoypad());
}

bool ContinueGettingMenuJoypad(uint8_t a) {
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
    const struct MenuData* data = GetMenuData();
    // CALL(aGetMenuIndexSet);
    // LD_A_addr(wMenuCursorY);
    // LD_L_A;
    // LD_H(0);
    // ADD_HL_DE;
    // LD_A_hl;
    // LD_addr_A(wMenuSelection);
    wram->wMenuSelection = GetMenuIndexSet(data)[wram->wMenuCursorY];
    // LD_A_addr(wMenuCursorY);
    // LD_addr_A(wMenuCursorPosition);
    wram->wMenuCursorPosition = wram->wMenuCursorY;
    // AND_A_A;
    // RET;
    return false;
}

void PlaceMenuStrings(const char** strings, uint8_t* de, uint8_t selection) {
    // PUSH_DE;
    // LD_HL(wMenuDataPointerTableAddr);
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // LD_A_addr(wMenuSelection);
    // CALL(aGetNthString);
    const char* hl = strings[selection];
    // LD_D_H;
    // LD_E_L;
    // POP_HL;
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(hl), de);
    // RET;
}

void PlaceNthMenuStrings(const char** strings, uint8_t* de, uint8_t selection) {
    uint8_t buf[32];
    // PUSH_DE;
    // LD_A_addr(wMenuSelection);
    // CALL(aGetMenuDataPointerTableEntry);
    // INC_HL;
    // INC_HL;
    // LD_A_hli;
    // LD_D_hl;
    // LD_E_A;
    // POP_HL;
    // CALL(aPlaceString);
    PlaceStringSimple(U82CA(buf, ((const struct LabeledMenuItem*)strings)[selection].label), de);
    // RET;
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

u8_flag_s MenuJumptable(void) {
    // LD_A_addr(wMenuSelection);
    // CALL(aGetMenuDataPointerTableEntry);
    const struct MenuData* data = GetMenuData();
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // JP_hl;
    return data->setupMenu.labelList[wram->wMenuSelection].function();
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
    ByteFill(&wram->wWindowStackPointer, (wMenuMetadataEnd - wMenuMetadata), 0);
    ByteFill(&wram->wMenuFlags, (wMenuHeaderEnd - wMenuHeader), 0);
    ByteFill(&wram->wMenuDataFlags, (wMenuDataEnd - wMenuData), 0);
    ByteFill(&wram->w2DMenuCursorInitY, (wMoreMenuDataEnd - wMoreMenuData), 0);

    // LDH_A_addr(rSVBK);
    // PUSH_AF;

    // LD_A(BANK(wWindowStack));
    // LDH_addr_A(rSVBK);

    // XOR_A_A;
    // LD_HL(wWindowStackBottom);
    // LD_hld_A;
    wram->wWindowStackBottom[0] = 0;
    // LD_hld_A;
    wram->wWindowStack[0xffe] = 0;

    // LD_A_L;
    // LD_addr_A(wWindowStackPointer);
    gWindowStackPointer = 0;
    ByteFill(gWindowStack, sizeof(gWindowStack), 0);
    ByteFill(gTileBackupStack, sizeof(gTileBackupStack), 0);
    // LD_A_H;
    // LD_addr_A(wWindowStackPointer + 1);
    wram->wWindowStackPointer = wWindowStackBottom - 2;

    // POP_AF;
    // LDH_addr_A(rSVBK);
    // RET;
}

void MenuClickSound(uint8_t a) {
    // PUSH_AF;
    // AND_A(A_BUTTON | B_BUTTON);
    // IF_Z goto nosound;
    if(a & (A_BUTTON | B_BUTTON)) {
        // LD_HL(wMenuFlags);
        // BIT_hl(3);
        // IF_NZ goto nosound;
        if(!bit_test(wram->wMenuFlags, 3)) {
            // CALL(aPlayClickSFX);
            PlayClickSFX();
        }
    }

// nosound:
    // POP_AF;
    // RET;
}

void PlayClickSFX(void) {
    // PUSH_DE;
    // LD_DE(SFX_READ_TEXT_2);
    // CALL(aPlaySFX);
    // POP_DE;
    // RET;
    return PlaySFX(SFX_READ_TEXT_2);
}

void MenuTextboxWaitButton(const struct TextCmd* hl) {
    // CALL(aMenuTextbox);
    MenuTextbox(hl);
    // CALL(aWaitButton);
    WaitButton();
    // CALL(aExitMenu);
    ExitMenu();
    // RET;
}

void Place2DMenuItemName(uint8_t* hl, const char* de) {
    uint8_t buf[128];
    // LDH_addr_A(hTempBank);
    // LDH_A_addr(hROMBank);
    // PUSH_AF;
    // LDH_A_addr(hTempBank);
    // RST(aBankswitch);

    // CALL(aPlaceString);
    printf("%s\n", de);
    PlaceStringSimple(U82CA(buf, de), hl);
    // POP_AF;
    // RST(aBankswitch);

    // RET;
}

u8_flag_s v_2DMenu(void) {
    // LDH_A_addr(hROMBank);
    // LD_addr_A(wMenuData_2DMenuItemStringsBank);
    // FARCALL(av_2DMenu_);
    bool cancel = v_2DMenu__Conv();
    // LD_A_addr(wMenuCursorPosition);
    // RET;
    return u8_flag(wram->wMenuCursorPosition, cancel);
}

u8_flag_s InterpretBattleMenu(void) {
    // LDH_A_addr(hROMBank);
    // LD_addr_A(wMenuData_2DMenuItemStringsBank);
    // FARCALL(av_InterpretBattleMenu);
    bool c = v_InterpretBattleMenu_Conv();
    // LD_A_addr(wMenuCursorPosition);
    // RET;
    return u8_flag(wram->wMenuCursorPosition, c);
}

void InterpretMobileMenu(void) {
    //  //  unreferenced
    LDH_A_addr(hROMBank);
    LD_addr_A(wMenuData_2DMenuItemStringsBank);
    FARCALL(av_InterpretMobileMenu);
    LD_A_addr(wMenuCursorPosition);
    RET;
}
