#include "../../constants.h"
#include "mon_submenu.h"
#include "mail_2.h"
#include "../../home/menu.h"
#include "../../home/copy.h"
#include "../../home/names.h"
#include "../../home/text.h"
#include "../../home/audio.h"
#include "../../home/map_objects.h"
#include "../../home/tilemap.h"
#include "../gfx/mon_icons.h"
#include "../../data/mon_menu.h"

// INCLUDE "data/mon_menu.asm"

static struct MenuHeader MonSubmenu_MenuHeader = {
    .flags = MENU_BACKUP_TILES,  // flags
    .coord = menu_coords(6, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1),
    .data = NULL,
    .defaultOption = 1,  // default option
};

static void MonSubmenu_GetTopCoord(void){
//  [wMenuBorderTopCoord] = 1 + [wMenuBorderBottomCoord] - 2 * ([wMonSubmenuCount] + 1)
    // LD_A_addr(wMonSubmenuCount);
    // INC_A;
    // ADD_A_A;
    // LD_B_A;
    // LD_A_addr(wMenuBorderBottomCoord);
    // SUB_A_B;
    // INC_A;
    // LD_addr_A(wMenuBorderTopCoord);
    wram->wMenuBorderTopCoord = 1 + wram->wMenuBorderBottomCoord - 2 * (wram->wMonSubmenuCount + 1);
    // CALL(aMenuBox);
    MenuBox_Conv();
    // RET;
}

void MonSubmenu(void){
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hBGMapMode = 0x0;
    // CALL(aGetMonSubmenuItems);
    GetMonSubmenuItems();
    // FARCALL(aFreezeMonIcons);
    FreezeMonIcons_Conv();
    // LD_HL(mMonSubmenu_MenuHeader);
    // CALL(aLoadMenuHeader);
    LoadMenuHeader_Conv2(&MonSubmenu_MenuHeader);
    // CALL(aMonSubmenu_GetTopCoord);
    MonSubmenu_GetTopCoord();
    // CALL(aPopulateMonMenu);
    PopulateMonMenu();

    // LD_A(1);
    // LDH_addr_A(hBGMapMode);
    hBGMapMode = 1;
    // CALL(aMonMenuLoop);
    // LD_addr_A(wMenuSelection);
    wram->wMenuSelection = MonMenuLoop();

    // CALL(aExitMenu);
    ExitMenu_Conv2();
    // RET;
}

uint8_t MonMenuLoop(void){
    while(1) {
    // loop:
        // LD_A(MENU_UNUSED_3 | MENU_BACKUP_TILES_2);  // flags
        // LD_addr_A(wMenuDataFlags);
        // LD_A_addr(wMonSubmenuCount);
        // LD_addr_A(wMenuDataItems);
        struct MenuData data = {.flags = MENU_UNUSED_3 | MENU_BACKUP_TILES_2, .verticalMenu = {.count = wram->wMonSubmenuCount}};
        // CALL(aInitVerticalMenuCursor);
        InitVerticalMenuCursor_Conv(&data);
        // LD_HL(w2DMenuFlags1);
        // SET_hl(6);
        bit_set(wram->w2DMenuFlags1, 6);
        // CALL(aStaticMenuJoypad);
        uint8_t pad = StaticMenuJoypad_Conv();
        // LD_DE(SFX_READ_TEXT_2);
        // CALL(aPlaySFX);
        PlaySFX_Conv(SFX_READ_TEXT_2);
        // LDH_A_addr(hJoyPressed);
        // BIT_A(A_BUTTON_F);
        // IF_NZ goto select;
        if(bit_test(pad, A_BUTTON_F)) {
        // select:
            // LD_A_addr(wMenuCursorY);
            // DEC_A;
            // LD_C_A;
            // LD_B(0);
            // LD_HL(wMonSubmenuItems);
            // ADD_HL_BC;
            // LD_A_hl;
            // RET;
            return wram->wMonSubmenuItems[wram->wMenuCursorY - 1];
        }
        // BIT_A(B_BUTTON_F);
        // IF_NZ goto cancel;
        else if(bit_test(pad, B_BUTTON_F)) {
        // cancel:
            // LD_A(MONMENUITEM_CANCEL);
            // RET;
            return MONMENUITEM_CANCEL;
        }
        // goto loop;
    }
}

void PopulateMonMenu(void){
    // CALL(aMenuBoxCoord2Tile);
    // LD_BC(2 * SCREEN_WIDTH + 2);
    // ADD_HL_BC;
    uint8_t* hl = MenuBoxCoord2Tile_Conv() + 2 * SCREEN_WIDTH + 2;
    // LD_DE(wMonSubmenuItems);
    const uint8_t* de = wram->wMonSubmenuItems;

    while(*de != (uint8_t)-1) {
    // loop:
        // LD_A_de;
        // INC_DE;
        // CP_A(-1);
        // RET_Z ;
        // PUSH_DE;
        // PUSH_HL;
        // CALL(aGetMonMenuString);
        // POP_HL;
        // CALL(aPlaceString);
        PlaceStringSimple(GetMonMenuString(*de), hl);
        // LD_BC(2 * SCREEN_WIDTH);
        // ADD_HL_BC;
        hl += 2 * SCREEN_WIDTH;
        // POP_DE;
        de++;
        // goto loop;
    }
}

uint8_t* GetMonMenuString(uint8_t item){
    // LD_HL(mMonMenuOptions + 1);
    // LD_DE(3);
    // CALL(aIsInArray);
    uint32_t idx = 0;
    while(idx < NUM_MONMENUITEMS) {
        if(MonMenuOptions[idx].item == item)
            break;
        idx++;
    }
    if(idx >= NUM_MONMENUITEMS) {
        return U82C(MonMenuOptionStrings[MONMENUVALUE_ERROR - 1]);
    }
    // DEC_HL;
    // LD_A_hli;
    // CP_A(MONMENU_MENUOPTION);
    // IF_Z goto NotMove;
    if(MonMenuOptions[idx].category == MONMENU_MENUOPTION) {
    // NotMove:
        // INC_HL;
        // LD_A_hl;
        // DEC_A;
        // LD_HL(mMonMenuOptionStrings);
        // CALL(aGetNthString);
        // LD_D_H;
        // LD_E_L;
        // RET;
        return U82C(MonMenuOptionStrings[MonMenuOptions[idx].value - 1]);
    }
    // INC_HL;
    // LD_A_hl;
    // LD_addr_A(wNamedObjectIndex);
    // CALL(aGetMoveName);
    // RET;
    return GetMoveName_Conv2(MonMenuOptions[idx].value);
}

void GetMonSubmenuItems(void){
    // CALL(aResetMonSubmenu);
    ResetMonSubmenu();
    // LD_A_addr(wCurPartySpecies);
    // CP_A(EGG);
    // IF_Z goto egg;
    if(wram->wCurPartySpecies == EGG) {
    // egg:
        // LD_A(MONMENUITEM_STATS);
        // CALL(aAddMonMenuItem);
        AddMonMenuItem(MONMENUITEM_STATS);
        // LD_A(MONMENUITEM_SWITCH);
        // CALL(aAddMonMenuItem);
        AddMonMenuItem(MONMENUITEM_SWITCH);
        // LD_A(MONMENUITEM_CANCEL);
        // CALL(aAddMonMenuItem);
        AddMonMenuItem(MONMENUITEM_CANCEL);
        // CALL(aTerminateMonSubmenu);
        TerminateMonSubmenu();
        // RET;
        return;
    }
    // LD_A_addr(wLinkMode);
    // AND_A_A;
    // IF_NZ goto skip_moves;
    if(wram->wLinkMode == 0) {
        // LD_A(MON_MOVES);
        // CALL(aGetPartyParamLocation);
        // LD_D_H;
        // LD_E_L;
        move_t* moves = wram->wPartyMon[wram->wCurPartyMon].mon.moves;
        // LD_C(NUM_MOVES);

        for(uint32_t i = 0; i < NUM_MOVES; ++i) {
        // loop:
            // PUSH_BC;
            // PUSH_DE;
            // LD_A_de;
            // AND_A_A;
            // IF_Z goto next;
            if(moves[i] == NO_MOVE)
                continue;
            // PUSH_HL;
            // CALL(aIsFieldMove);
            u8_flag_s res = IsFieldMove(moves[i]);
            // POP_HL;
            // IF_NC goto next;
            if(!res.flag)
                continue;
            // CALL(aAddMonMenuItem);
            AddMonMenuItem(res.a);

        // next:
            // POP_DE;
            // INC_DE;
            // POP_BC;
            // DEC_C;
            // IF_NZ goto loop;
        }
    }

// skip_moves:
    // LD_A(MONMENUITEM_STATS);
    // CALL(aAddMonMenuItem);
    AddMonMenuItem(MONMENUITEM_STATS);
    // LD_A(MONMENUITEM_SWITCH);
    // CALL(aAddMonMenuItem);
    AddMonMenuItem(MONMENUITEM_SWITCH);
    // LD_A(MONMENUITEM_MOVE);
    // CALL(aAddMonMenuItem);
    AddMonMenuItem(MONMENUITEM_MOVE);
    // LD_A_addr(wLinkMode);
    // AND_A_A;
    // IF_NZ goto skip2;
    if(wram->wLinkMode == 0) {
        // PUSH_HL;
        // LD_A(MON_ITEM);
        // CALL(aGetPartyParamLocation);
        // LD_D_hl;
        // FARCALL(aItemIsMail);
        // POP_HL;
        // LD_A(MONMENUITEM_MAIL);
        // IF_C goto ok;
        // LD_A(MONMENUITEM_ITEM);
        uint8_t item = (ItemIsMail_Conv(wram->wPartyMon[wram->wCurPartyMon].mon.item))
            ? MONMENUITEM_MAIL
            : MONMENUITEM_ITEM;

    // ok:
        // CALL(aAddMonMenuItem);
        AddMonMenuItem(item);
    }

// skip2:
    // LD_A_addr(wMonSubmenuCount);
    // CP_A(NUM_MONMENU_ITEMS);
    // IF_Z goto ok2;
    if(wram->wMonSubmenuCount != NUM_MONMENU_ITEMS) {
        // LD_A(MONMENUITEM_CANCEL);
        // CALL(aAddMonMenuItem);
        AddMonMenuItem(MONMENUITEM_CANCEL);
    }

// ok2:
    // CALL(aTerminateMonSubmenu);
    TerminateMonSubmenu();
    // RET;

}

u8_flag_s IsFieldMove(move_t a){
    // LD_B_A;
    // LD_HL(mMonMenuOptions);

    for(uint32_t i = 0; i < NUM_MONMENUITEMS; ++i) {
    // next:
        // LD_A_hli;
        // CP_A(-1);
        // IF_Z goto nope;
        // CP_A(MONMENU_MENUOPTION);
        // IF_Z goto nope;
        if(MonMenuOptions[i].category == MONMENU_MENUOPTION)
            break;
        // LD_D_hl;
        // INC_HL;
        // LD_A_hli;
        // CP_A_B;
        // IF_NZ goto next;
        if(MonMenuOptions[i].value == a) {
            return u8_flag(MonMenuOptions[i].item, true);
        }
    }
    // LD_A_D;
    // SCF;

// nope:
    // RET;
    return u8_flag(0, false);
}

void ResetMonSubmenu(void){
    // XOR_A_A;
    // LD_addr_A(wMonSubmenuCount);
    wram->wMonSubmenuCount = 0;
    // LD_HL(wMonSubmenuItems);
    // LD_BC(NUM_MONMENU_ITEMS + 1);
    // CALL(aByteFill);
    ByteFill_Conv2(wram->wMonSubmenuItems, sizeof(wram->wMonSubmenuItems), 0);
    // RET;

}

void TerminateMonSubmenu(void){
    // LD_A_addr(wMonSubmenuCount);
    // LD_E_A;
    // LD_D(0);
    // LD_HL(wMonSubmenuItems);
    // ADD_HL_DE;
    // LD_hl(-1);
    // RET;
    wram->wMonSubmenuItems[wram->wMonSubmenuCount] = (uint8_t)-1;
}

void AddMonMenuItem(uint8_t item){
    // PUSH_HL;
    // PUSH_DE;
    // PUSH_AF;
    // LD_A_addr(wMonSubmenuCount);
    // LD_E_A;
    // INC_A;
    // LD_addr_A(wMonSubmenuCount);
    uint8_t e = wram->wMonSubmenuCount++;
    // LD_D(0);
    // LD_HL(wMonSubmenuItems);
    // ADD_HL_DE;
    // POP_AF;
    // LD_hl_A;
    wram->wMonSubmenuItems[e] = item;
    // POP_DE;
    // POP_HL;
    // RET;

}

static struct MenuHeader BattleMonMenu_MenuHeader = {
    .flags = 0,  // flags
    .coord = menu_coords(11, 11, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1),
    .data = &(struct MenuData) {
        .flags = STATICMENU_CURSOR | STATICMENU_NO_TOP_SPACING,  // flags
        .verticalMenu = {
            .count = 3,  // items
            .options = (const char*[]) {
                "SWITCH",
                "STATS",
                "CANCEL",
            },
        },
    },
    .defaultOption = 1,  // default option
};

bool BattleMonMenu(void){
    // LD_HL(mBattleMonMenu_MenuHeader);
    // CALL(aCopyMenuHeader);
    CopyMenuHeader_Conv2(&BattleMonMenu_MenuHeader);
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hBGMapMode = 0x0;
    // CALL(aMenuBox);
    MenuBox_Conv();
    // CALL(aUpdateSprites);
    UpdateSprites_Conv();
    // CALL(aPlaceVerticalMenuItems);
    PlaceVerticalMenuItems_Conv2();
    // CALL(aWaitBGMap);
    WaitBGMap_Conv();
    // CALL(aCopyMenuData);
    const struct MenuData* data = GetMenuData();
    // LD_A_addr(wMenuDataFlags);
    // BIT_A(7);
    // IF_Z goto set_carry;
    if(!bit_test(data->flags, 7))
        return true;
    // CALL(aInitVerticalMenuCursor);
    InitVerticalMenuCursor_Conv(data);
    // LD_HL(w2DMenuFlags1);
    // SET_hl(6);
    bit_set(wram->w2DMenuFlags1, 6);
    // CALL(aStaticMenuJoypad);
    uint8_t pad = StaticMenuJoypad_Conv();
    // LD_DE(SFX_READ_TEXT_2);
    // CALL(aPlaySFX);
    PlaySFX_Conv(SFX_READ_TEXT_2);
    // LDH_A_addr(hJoyPressed);
    // BIT_A(B_BUTTON_F);
    // IF_Z goto clear_carry;
    // RET_Z ;
    if(!bit_test(pad, B_BUTTON_F))
        return false;

// set_carry:
    // SCF;
    // RET;
    return true;

// clear_carry:
    // AND_A_A;
    // RET;
}
