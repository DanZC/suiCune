#include "../../constants.h"
#include "kurt.h"
#include "kurt_selectquantity_interpretjoypad.h"
#include "../../home/text.h"
#include "../../home/menu.h"
#include "../../home/scrolling_menu.h"
#include "../../home/map_objects.h"
#include "../../home/tilemap.h"
#include "../../home/print_text.h"
#include "../../home/item.h"
#include "../menus/menu_2.h"
#include "../../data/text/common.h"

void Kurt_PrintTextWhichApricorn(void){
    static const txt_cmd_s WhichApricornText[] = {
        text_far(v_WhichApricornText)
        text_end
    };
    // LD_HL(mKurt_PrintTextWhichApricorn_WhichApricornText);
    // CALL(aPrintText);
    PrintText_Conv2(WhichApricornText);
    // RET;
}

void Kurt_PrintTextHowMany(void){
    static const txt_cmd_s HowManyShouldIMakeText[] = {
        text_far(v_HowManyShouldIMakeText)
        text_end
    };
    // LD_HL(mKurt_PrintTextHowMany_HowManyShouldIMakeText);
    // CALL(aPrintText);
    PrintText_Conv2(HowManyShouldIMakeText);
    // RET;
}

void SelectApricornForKurt(void){
    // CALL(aLoadStandardMenuHeader);
    LoadStandardMenuHeader_Conv();
    // LD_C(0x1);
    uint8_t c = 0x1;
    // XOR_A_A;
    // LD_addr_A(wMenuScrollPosition);
    wram->wMenuScrollPosition = 0;
    // LD_addr_A(wKurtApricornQuantity);
    wram->wKurtApricornQuantity = 0;

    do {
    // loop:
        // PUSH_BC;
        // CALL(aKurt_PrintTextWhichApricorn);
        Kurt_PrintTextWhichApricorn();
        // POP_BC;
        // LD_A_C;
        // LD_addr_A(wMenuSelection);
        wram->wMenuSelection = c;
        // CALL(aKurt_SelectApricorn);
        // LD_A_C;
        // LD_addr_A(wScriptVar);
        wram->wScriptVar = Kurt_SelectApricorn_Conv();
        // AND_A_A;
        // IF_Z goto done;
        if(wram->wScriptVar == 0)
            goto done;
        // LD_addr_A(wCurItem);
        wram->wCurItem = wram->wScriptVar;
        // LD_A_addr(wMenuCursorY);
        // LD_C_A;
        c = wram->wMenuCursorY;
        // PUSH_BC;
        // CALL(aKurt_PrintTextHowMany);
        Kurt_PrintTextHowMany();
        // CALL(aKurt_SelectQuantity);
        // POP_BC;
        // IF_NC goto loop;
    } while(!Kurt_SelectQuantity_Conv());
    // LD_A_addr(wItemQuantityChange);
    // LD_addr_A(wKurtApricornQuantity);
    wram->wKurtApricornQuantity = wram->wItemQuantityChange;
    // CALL(aKurt_GiveUpSelectedQuantityOfSelectedApricorn);
    Kurt_GiveUpSelectedQuantityOfSelectedApricorn();


done:
    // CALL(aCall_ExitMenu);
    ExitMenu_Conv2();
    // RET;
}

static void Kurt_SelectApricorn_Name(const struct MenuData* data, tile_t* de) {
    // LD_A_addr(wMenuSelection);
    // AND_A_A;
    // RET_Z ;
    if(wram->wMenuSelection == 0)
        return;
    // FARCALL(aPlaceMenuItemName);
    PlaceMenuItemName_Conv(data, de);
    // RET;
}

static void Kurt_SelectApricorn_Quantity(const struct MenuData* data, tile_t* de) {
    // LD_A_addr(wMenuSelection);
    // LD_addr_A(wCurItem);
    wram->wCurItem = wram->wMenuSelection;
    // CALL(aKurt_GetQuantityOfApricorn);
    uint8_t quantity = Kurt_GetQuantityOfApricorn_Conv(wram->wMenuSelection);
    // RET_Z ;
    if(quantity == 0)
        return;
    // LD_A_addr(wItemQuantityChange);
    // LD_addr_A(wMenuSelectionQuantity);
    wram->wMenuSelectionQuantity = quantity;
    // FARCALL(aPlaceMenuItemQuantity);
    PlaceMenuItemQuantity_Conv(data, de);
    // RET;
}

static struct MenuHeader Kurt_SelectApricorn_MenuHeader = {
    .flags = MENU_BACKUP_TILES,  // flags
    .coord = menu_coords(1, 1, 13, 10),
    //dw ['.MenuData'];
    .data = &(struct MenuData) {
    // MenuData:
        .flags = SCROLLINGMENU_DISPLAY_ARROWS,  // flags
        .scrollingMenu = {
            .rows=4, .cols=7,  // rows, columns
            .format = SCROLLINGMENU_ITEMS_NORMAL,  // item format
            //dbw ['0', 'wKurtApricornCount']
            .list = wram_ptr(wKurtApricornCount),
            //dba ['.Name']
            .func1 = Kurt_SelectApricorn_Name,
            //dba ['.Quantity']
            .func2 = Kurt_SelectApricorn_Quantity,
            //dba ['NULL']
            .func3 = NULL,
        },
    },
    //db ['1'];  // default option
    .defaultOption = 1,
};
    //db ['0'];  // unused


void Kurt_SelectApricorn(void){
    FARCALL(aFindApricornsInBag);
    IF_C goto nope;
    LD_HL(mKurt_SelectApricorn_MenuHeader);
    CALL(aCopyMenuHeader);
    LD_A_addr(wMenuSelection);
    LD_addr_A(wMenuCursorPosition);
    XOR_A_A;
    LDH_addr_A(hBGMapMode);
    CALL(aInitScrollingMenu);
    CALL(aUpdateSprites);
    CALL(aScrollingMenu);
    LD_A_addr(wMenuJoypad);
    CP_A(B_BUTTON);
    IF_Z goto nope;
    LD_A_addr(wMenuSelection);
    CP_A(-1);
    IF_NZ goto done;


nope:
    XOR_A_A;  // FALSE


done:
    LD_C_A;
    RET;

}

uint8_t Kurt_SelectApricorn_Conv(void){
    // FARCALL(aFindApricornsInBag);
    // IF_C goto nope;
    if(FindApricornsInBag_Conv()) {
        // LD_HL(mKurt_SelectApricorn_MenuHeader);
        // CALL(aCopyMenuHeader);
        CopyMenuHeader_Conv2(&Kurt_SelectApricorn_MenuHeader);
        // LD_A_addr(wMenuSelection);
        // LD_addr_A(wMenuCursorPosition);
        wram->wMenuCursorPosition = wram->wMenuSelection;
        // XOR_A_A;
        // LDH_addr_A(hBGMapMode);
        hBGMapMode = 0;
        // CALL(aInitScrollingMenu);
        InitScrollingMenu_Conv();
        // CALL(aUpdateSprites);
        UpdateSprites_Conv();
        // CALL(aScrollingMenu);
        uint8_t joypad = ScrollingMenu_Conv();
        // LD_A_addr(wMenuJoypad);
        // CP_A(B_BUTTON);
        // IF_Z goto nope;
        if(joypad != B_BUTTON) {
            // LD_A_addr(wMenuSelection);
            // CP_A(-1);
            // IF_NZ goto done;
            return wram->wMenuSelection;
        }
        else {
            return FALSE;
        }
    }

// nope:
    // XOR_A_A;  // FALSE
    return FALSE;

// done:
    // LD_C_A;
    // RET;
}

static const struct MenuHeader Kurt_SelectQuantity_MenuHeader = {
    .flags = MENU_BACKUP_TILES,  // flags
    .coord = menu_coords(6, 9, SCREEN_WIDTH - 1, 12),
    //dw ['NULL'];
    .data = NULL,
    .defaultOption = 0xff  // default option
    //db ['0'];
};

void Kurt_SelectQuantity(void){
    LD_A_addr(wCurItem);
    LD_addr_A(wMenuSelection);
    CALL(aKurt_GetQuantityOfApricorn);
    IF_Z goto done;
    LD_A_addr(wItemQuantityChange);
    LD_addr_A(wItemQuantity);
    LD_A(0x1);
    LD_addr_A(wItemQuantityChange);
    LD_HL(mKurt_SelectQuantity_MenuHeader);
    CALL(aLoadMenuHeader);

loop:
    XOR_A_A;
    LDH_addr_A(hBGMapMode);
    CALL(aMenuBox);
    CALL(aUpdateSprites);
    CALL(aKurt_SelectQuantity_PlaceApricornName);
    CALL(aPlaceApricornQuantity);
    CALL(aApplyTilemap);
    FARCALL(aKurt_SelectQuantity_InterpretJoypad);
    IF_NC goto loop;

    PUSH_BC;
    CALL(aPlayClickSFX);
    POP_BC;
    LD_A_B;
    CP_A(-1);
    IF_Z goto done;
    LD_A_addr(wItemQuantityChange);
    LD_addr_A(wItemQuantityChange);  // What is the point of this operation?
    SCF;


done:
    CALL(aCloseWindow);
    RET;


PlaceApricornName:
    CALL(aMenuBoxCoord2Tile);
    LD_DE(SCREEN_WIDTH + 1);
    ADD_HL_DE;
    LD_D_H;
    LD_E_L;
    FARCALL(aPlaceMenuItemName);
    RET;

}

static void Kurt_SelectQuantity_PlaceApricornName(void);

bool Kurt_SelectQuantity_Conv(void){
    // LD_A_addr(wCurItem);
    // LD_addr_A(wMenuSelection);
    wram->wMenuSelection = wram->wCurItem;
    // CALL(aKurt_GetQuantityOfApricorn);
    // IF_Z goto done;
    uint8_t q = Kurt_GetQuantityOfApricorn_Conv(wram->wCurItem);
    if(q == 0) {
        CloseWindow_Conv2();
        return false;
    }
    // LD_A_addr(wItemQuantityChange);
    // LD_addr_A(wItemQuantity);
    wram->wItemQuantity = wram->wItemQuantityChange;
    // LD_A(0x1);
    // LD_addr_A(wItemQuantityChange);
    wram->wItemQuantityChange = 0x1;
    // LD_HL(mKurt_SelectQuantity_MenuHeader);
    // CALL(aLoadMenuHeader);
    LoadMenuHeader_Conv2(&Kurt_SelectQuantity_MenuHeader);

    u8_flag_s res;
    do {
    // loop:
        // XOR_A_A;
        // LDH_addr_A(hBGMapMode);
        hBGMapMode = 0x0;
        // CALL(aMenuBox);
        MenuBox_Conv();
        // CALL(aUpdateSprites);
        UpdateSprites_Conv();
        // CALL(aKurt_SelectQuantity_PlaceApricornName);
        Kurt_SelectQuantity_PlaceApricornName();
        // CALL(aPlaceApricornQuantity);
        PlaceApricornQuantity();
        // CALL(aApplyTilemap);
        ApplyTilemap_Conv();
        // FARCALL(aKurt_SelectQuantity_InterpretJoypad);
        res = Kurt_SelectQuantity_InterpretJoypad();
        // IF_NC goto loop;
    } while(!res.flag);

    // PUSH_BC;
    // CALL(aPlayClickSFX);
    PlayClickSFX_Conv();
    // POP_BC;
    // LD_A_B;
    // CP_A(-1);
    // IF_Z goto done;
    bool f = false;
    if(res.a != 0xff) {
        // LD_A_addr(wItemQuantityChange);
        // LD_addr_A(wItemQuantityChange);  // What is the point of this operation?
        // SCF;
        f = true;
    }

// done:
    // CALL(aCloseWindow);
    CloseWindow_Conv2();
    // RET;
    return f;
}

static void Kurt_SelectQuantity_PlaceApricornName(void){
    // CALL(aMenuBoxCoord2Tile);
    // LD_DE(SCREEN_WIDTH + 1);
    // ADD_HL_DE;
    // LD_D_H;
    // LD_E_L;
    // FARCALL(aPlaceMenuItemName);
    PlaceMenuItemName_Conv(GetMenuData(), MenuBoxCoord2Tile_Conv() + SCREEN_WIDTH + 1);
    // RET;
}

void PlaceApricornQuantity(void){
    // CALL(aMenuBoxCoord2Tile);
    // LD_DE(2 * SCREEN_WIDTH + 10);
    // ADD_HL_DE;
    tile_t* hl = MenuBoxCoord2Tile_Conv() + 2 * SCREEN_WIDTH + 10;
    // LD_hl(0xf1);
    *hl = 0xf1;
    // INC_HL;
    // LD_DE(wItemQuantityChange);
    // LD_BC((PRINTNUM_LEADINGZEROS | 1 << 8) | 2);
    // JP(mPrintNum);
    PrintNum_Conv2(hl + 1, &wram->wItemQuantityChange, PRINTNUM_LEADINGZEROS | 1, 2);
}

void Kurt_GetQuantityOfApricorn(void){
    PUSH_BC;
    LD_HL(wNumItems);
    LD_A_addr(wCurItem);
    LD_C_A;
    LD_B(0);

loop:
    INC_HL;
    LD_A_hli;
    CP_A(-1);
    IF_Z goto done;
    CP_A_C;
    IF_NZ goto loop;
    LD_A_hl;
    ADD_A_B;
    LD_B_A;
    IF_NC goto loop;
    LD_B(-1);


done:
    LD_A_B;
    SUB_A(99);
    IF_C goto done2;
    LD_B(99);


done2:
    LD_A_B;
    LD_addr_A(wItemQuantityChange);
    AND_A_A;
    POP_BC;
    RET;

}

uint8_t Kurt_GetQuantityOfApricorn_Conv(item_t apricorn){
    // PUSH_BC;
    // LD_HL(wNumItems);
    item_pocket_s* hl = (item_pocket_s*)&wram->wNumItems;
    // LD_A_addr(wCurItem);
    // LD_C_A;
    // LD_B(0);
    uint8_t b = 0;

    for(uint32_t i = 0; i < wram->wNumItems; ++i) {
    // loop:
        // INC_HL;
        // LD_A_hli;
        // CP_A(-1);
        // IF_Z goto done;
        // CP_A_C;
        // IF_NZ goto loop;
        if(hl->pocket[i].item == apricorn) {
            // LD_A_hl;
            // ADD_A_B;
            if(b + hl->pocket[i].quantity > 0xff) {
                // LD_B_A;
                b = 0xff;
                // IF_NC goto loop;
                break;
            }
            else {
                b += hl->pocket[i].quantity;
            }
        }
    }
    // LD_B(-1);


// done:
    // LD_A_B;
    // SUB_A(99);
    if(b >= 99)
        b = 99;
    // IF_C goto done2;
    // LD_B(99);

// done2:
    // LD_A_B;
    // LD_addr_A(wItemQuantityChange);
    wram->wItemQuantityChange = b;
    // AND_A_A;
    // POP_BC;
    // RET;
    return b != 0;
}

void Kurt_GiveUpSelectedQuantityOfSelectedApricorn(void){
//  Get the quantity of Apricorns of type [wCurItem]
//  in the bag. Compatible with multiple stacks.

//  Initialize the search.
    // PUSH_DE;
    // PUSH_BC;
    // LD_HL(wNumItems);
    item_pocket_s* hl = (item_pocket_s*)&wram->wNumItems;
    // LD_A_addr(wCurItem);
    // LD_C_A;
    item_t c = wram->wCurItem;
    // LD_E(0x0);
    uint8_t e = 0x0;
    // XOR_A_A;
    // LD_addr_A(wCurItemQuantity);
    wram->wCurItemQuantity = 0;
    // LD_A(-1);
    // LD_addr_A(wApricorns);
    wram->wApricorns = 0xff;

//  Search for [wCurItem] in the bag.
    item_t a;
    uint32_t i = 0;
    while(1) {
    // loop1:
        do {
        //  Increase the total count.
            // LD_A_addr(wCurItemQuantity);
            // INC_A;
            // LD_addr_A(wCurItemQuantity);
            wram->wCurItemQuantity++;
        //  Get the index of the next item.
            // INC_HL;
            // LD_A_hli;
            a = hl->pocket[i].item;
        //  If we've reached the end of the pocket, break.
            // CP_A(-1);
            // IF_Z goto okay1;
            if(a == (item_t)-1)
                goto okay1;
        //  If we haven't found what we're looking for, continue.
            // CP_A_C;
            // IF_NZ goto loop1;
        } while(a != c);
    //  Increment the result counter and store the bag index of the match.
        // LD_D(0x0);
        // PUSH_HL;
        // LD_HL(wApricorns);
        // ADD_HL_DE;
        uint8_t* de = &wram->wApricorns + e;
        // INC_E;
        e++;
        // LD_A_addr(wCurItemQuantity);
        // DEC_A;
        // LD_hli_A;
        de[0] = wram->wCurItemQuantity - 1;
        // LD_A(-1);
        // LD_hl_A;
        de[1] = 0xff;
        // POP_HL;
        // goto loop1;
    }

okay1:
//  How many stacks have we found?
    // LD_A_E;
    // AND_A_A;
    // IF_Z goto done;
    uint8_t* hl_;
    if(e != 0) {
        // DEC_A;
        // IF_Z goto OnlyOne;
        if(e != 1) {
            // LD_HL(wApricorns);
            hl_ = &wram->wApricorns;

            do {
            // loop2:
                // LD_A_hl;
                // LD_C_A;
                uint8_t c2 = *hl_;
                // PUSH_HL;
                uint8_t* hl2 = hl_;

                while(1) {
                // loop3:
                    // INC_HL;
                    hl2++;
                    // LD_A_hl;
                    // CP_A(-1);
                    // IF_Z goto okay2;
                    if(*hl2 == 0xff)
                        break;
                    // LD_B_A;
                    uint8_t b = *hl2;
                    // LD_A_C;
                    // CALL(aKurt_GetAddressOfApricornQuantity);
                    // LD_E_A;
                    uint8_t e = Kurt_GetAddressOfApricornQuantity_Conv(c2);
                    // LD_A_B;
                    // CALL(aKurt_GetAddressOfApricornQuantity);
                    uint8_t t = Kurt_GetAddressOfApricornQuantity_Conv(b);
                    // SUB_A_E;
                    // IF_Z goto equal;
                    if(t == e) {
                    // equal:
                        // LD_A_C;
                        // SUB_A_B;
                        // IF_NC goto loop3;
                        if(c2 >= b)
                            continue;
                        goto less;
                    }
                    // IF_C goto less;
                    else if(t < e) {
                    less:
                        // LD_A_C;
                        // LD_C_B;
                        // LD_hl_A;
                        *hl2 = c2;
                        // LD_A_C;
                        // POP_HL;
                        // LD_hl_A;
                        *hl_ = b;
                        // PUSH_HL;
                        // goto loop3;
                        continue;
                    }
                    // goto loop3;
                    continue;
                }


            // okay2:
                // POP_HL;
                // INC_HL;
                hl_++;
                // LD_A_hl;
                a = *hl_;
                // CP_A(-1);
                // IF_NZ goto loop2;
            } while(a != 0xff);
        }

    // OnlyOne:
        // LD_HL(wApricorns);
        hl_ = &wram->wApricorns;

        while(1) {
        // loop4:
            // LD_A_hl;
            // CP_A(-1);
            // IF_Z goto done;
            if(*hl_ == 0xff)
                break;
            // PUSH_HL;
            // LD_addr_A(wCurItemQuantity);
            wram->wCurItemQuantity = *hl_;
            // CALL(aKurt_GetRidOfItem);
            Kurt_GetRidOfItem_Conv();
            // POP_HL;
            // LD_A_addr(wItemQuantityChange);
            // AND_A_A;
            // IF_Z goto done;
            if(wram->wItemQuantityChange == 0)
                break;
            // PUSH_HL;
            uint8_t* hl2 = hl_;
            // LD_A_hli;
            // LD_C_A;
            uint8_t c2 = *(hl2++);

            uint8_t a2;
            while(1) {
            // loop5:
                // LD_A_hli;
                // CP_A(-1);
                a2 = *(hl2++);
                // IF_Z goto okay3;
                if(a2 == 0xff)
                    break;
                // CP_A_C;
                // IF_C goto loop5;
                if(a2 < c2)
                    continue;
                // DEC_A;
                // DEC_HL;
                // LD_hli_A;
                hl2[-1] = a2 - 1;
                // goto loop5;
            }

        // okay3:
            // POP_HL;
            // INC_HL;
            hl_++;
            // goto loop4;
        }
    }

// done:
    // LD_A_addr(wItemQuantityChange);
    // AND_A_A;
    // POP_BC;
    // POP_DE;
    // RET;
    return;
}

void Kurt_GetAddressOfApricornQuantity(void){
    PUSH_HL;
    PUSH_BC;
    LD_HL(wNumItems);
    INC_HL;
    LD_C_A;
    LD_B(0);
    ADD_HL_BC;
    ADD_HL_BC;
    INC_HL;
    LD_A_hl;
    POP_BC;
    POP_HL;
    RET;

}

uint8_t Kurt_GetAddressOfApricornQuantity_Conv(uint8_t a){
    // PUSH_HL;
    // PUSH_BC;
    // LD_HL(wNumItems);
    item_pocket_s* pocket = (item_pocket_s*)&wram->wNumItems;
    // INC_HL;
    // LD_C_A;
    // LD_B(0);
    // ADD_HL_BC;
    // ADD_HL_BC;
    // INC_HL;
    // LD_A_hl;
    // POP_BC;
    // POP_HL;
    // RET;
    return pocket->pocket[a].quantity;
}

void Kurt_GetRidOfItem(void){
    PUSH_BC;
    LD_HL(wNumItems);
    LD_A_addr(wCurItemQuantity);
    LD_C_A;
    LD_B(0);
    INC_HL;
    ADD_HL_BC;
    ADD_HL_BC;
    LD_A_addr(wCurItem);
    LD_C_A;
    LD_A_hli;
    CP_A(-1);
    IF_Z goto done;
    CP_A_C;
    IF_NZ goto done;
    LD_A_addr(wItemQuantityChange);
    LD_C_A;
    LD_A_hl;
    SUB_A_C;
    LD_B_C;
    IF_NC goto okay;
    ADD_A_C;
    LD_B_A;


okay:
    PUSH_BC;
    LD_HL(wNumItems);
    LD_A_B;
    LD_addr_A(wItemQuantityChange);
    CALL(aTossItem);
    POP_BC;
    LD_A_C;
    SUB_A_B;


done:
    LD_addr_A(wItemQuantityChange);
    POP_BC;
    RET;

}

void Kurt_GetRidOfItem_Conv(void){
    // PUSH_BC;
    // LD_HL(wNumItems);
    item_pocket_s* pocket = (item_pocket_s*)&wram->wNumItems;
    // LD_A_addr(wCurItemQuantity);
    // LD_C_A;
    // LD_B(0);
    // INC_HL;
    // ADD_HL_BC;
    // ADD_HL_BC;
    // LD_A_addr(wCurItem);
    // LD_C_A;
    item_t c = wram->wCurItem;
    // LD_A_hli;
    item_t a = pocket->pocket[wram->wCurItemQuantity].item;
    // CP_A(-1);
    // IF_Z goto done;
    // CP_A_C;
    // IF_NZ goto done;
    if(a != 0xff && a == c) {
        // LD_A_addr(wItemQuantityChange);
        // LD_C_A;
        uint8_t count = wram->wItemQuantityChange;
        // LD_A_hl;
        // SUB_A_C;
        uint8_t b = count;
        // LD_B_C;
        // IF_NC goto okay;
        if(pocket->pocket[wram->wCurItemQuantity].quantity < count) {
            // ADD_A_C;
            // LD_B_A;
            b = pocket->pocket[wram->wCurItemQuantity].quantity;
        }

    // okay:
        // PUSH_BC;
        // LD_HL(wNumItems);
        // LD_A_B;
        // LD_addr_A(wItemQuantityChange);
        wram->wItemQuantityChange = b;
        // CALL(aTossItem);
        TossItem_Conv((item_pocket_s*)&wram->wNumItems, b);
        // POP_BC;
        // LD_A_C;
        // SUB_A_B;
        a = count - b;
    }

// done:
    // LD_addr_A(wItemQuantityChange);
    wram->wItemQuantityChange = (uint8_t)a;
    // POP_BC;
    // RET;
}
