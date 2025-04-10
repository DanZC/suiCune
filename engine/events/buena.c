#include "../../constants.h"
#include "buena.h"
#include "buena_menu.h"
#include "../../home/delay.h"
#include "../../home/text.h"
#include "../../home/menu.h"
#include "../../home/scrolling_menu.h"
#include "../../home/map_objects.h"
#include "../../home/print_text.h"
#include "../../home/names.h"
#include "../../home/item.h"
#include "../../home/audio.h"
#include "../../home/joypad.h"
#include "../pokegear/radio.h"
#include "../../data/text/common.h"
#include "../../data/items/buena_prizes.h"

static void BuenasPassword_PlacePasswordChoices(const char** items, uint8_t* de, uint8_t selection) {
    (void)items;
    // PUSH_DE;
    // LD_A_addr(wBuenasPassword);
    // AND_A(0xf0);
    // LD_C_A;
    // LD_A_addr(wMenuSelection);
    // ADD_A_C;
    // LD_C_A;
    uint8_t c = selection + (wram->wBuenasPassword & 0xf0);
    // FARCALL(aGetBuenasPassword);
    uint8_t* str = GetBuenasPassword_Conv(&c);
    // POP_HL;
    // CALL(aPlaceString);
    PlaceStringSimple(str, de);
    // RET;
}

static const uint8_t *BuenasPassword_PasswordIndices[] = {
    [0] = (uint8_t[]){
        NUM_PASSWORDS_PER_CATEGORY,
        // for(int x = 0; x < NUM_PASSWORDS_PER_CATEGORY; x++){
        0,
        1,
        2,
        // }
        (uint8_t)-1,
    },
    //db ['-1'];
};

static const struct MenuHeader BuenasPassword_MenuHeader = {
    .flags = MENU_BACKUP_TILES,  // flags
    .coord = menu_coords(0, 0, 10, 7),
    //dw ['.MenuData'];
    .data = &(struct MenuData){
        .flags = STATICMENU_CURSOR | STATICMENU_DISABLE_B,  // flags
        .setupMenu = {
            //db ['0'];  // items
            .count = 0,
            //dw ['.PasswordIndices'];
            .itemList = BuenasPassword_PasswordIndices,
            //dw ['.PlacePasswordChoices'];
            .displayFunction = BuenasPassword_PlacePasswordChoices,
        },
    },
    //db ['1'];  // default option
};

void BuenasPassword(void){
    // XOR_A_A;
    // LD_addr_A(wWhichIndexSet);
    wram->wWhichIndexSet = 0;
    // LD_HL(mBuenasPassword_MenuHeader);
    // CALL(aCopyMenuHeader);
    CopyMenuHeader_Conv2(&BuenasPassword_MenuHeader);
    // LD_A_addr(wBuenasPassword);
    // LD_C_A;
    uint8_t c = wram->wBuenasPassword;
    // FARCALL(aGetBuenasPassword);
    GetBuenasPassword_Conv(&c);
    // LD_A_addr(wMenuBorderLeftCoord);
    // ADD_A_C;
    // ADD_A(0x2);
    // LD_addr_A(wMenuBorderRightCoord);
    wram->wMenuBorderRightCoord = wram->wMenuBorderLeftCoord + c + 0x2;
    // CALL(aPushWindow);
    PushWindow_Conv();
    // CALL(aDoNthMenu);  // menu
    DoNthMenu_Conv();
    // FARCALL(aBuena_ExitMenu);
    Buena_ExitMenu();
    // LD_B(0x0);
    // LD_A_addr(wMenuSelection);
    // LD_C_A;
    // LD_A_addr(wBuenasPassword);
    // maskbits(NUM_PASSWORDS_PER_CATEGORY, 0);
    // CP_A_C;
    // IF_NZ goto wrong;
    // LD_B(0x1);
    wram->wScriptVar = ((wram->wBuenasPassword & 0x3) == wram->wMenuSelection)? 0x1: 0x0;

// wrong:
    // LD_A_B;
    // LD_addr_A(wScriptVar);
    // RET;

    //db ['0'];
}

void BuenaPrize(void){
    static const txt_cmd_s BuenaAskWhichPrizeText[] = {
        text_far(v_BuenaAskWhichPrizeText)
        text_end
    };


    static const txt_cmd_s BuenaIsThatRightText[] = {
        text_far(v_BuenaIsThatRightText)
        text_end
    };

    static const txt_cmd_s BuenaHereYouGoText[] = {
        text_far(v_BuenaHereYouGoText)
        text_end
    };

    static const txt_cmd_s BuenaNotEnoughPointsText[] = {
        text_far(v_BuenaNotEnoughPointsText)
        text_end
    };

    static const txt_cmd_s BuenaNoRoomText[] = {
        text_far(v_BuenaNoRoomText)
        text_end
    };

    static const txt_cmd_s BuenaComeAgainText[] = {
        text_far(v_BuenaComeAgainText)
        text_end
    };
    // XOR_A_A;
    // LD_addr_A(wMenuScrollPosition);
    wram->wMenuScrollPosition = 0;
    // LD_A(0x1);
    // LD_addr_A(wMenuSelection);
    wram->wMenuSelection = 0x1;
    // CALL(aBuena_PlacePrizeMenuBox);
    Buena_PlacePrizeMenuBox();
    // CALL(aBuena_DisplayBlueCardBalance);
    Buena_DisplayBlueCardBalance();
    // LD_HL(mBuenaPrize_BuenaAskWhichPrizeText);
    // CALL(aPrintText);
    PrintText_Conv2(BuenaAskWhichPrizeText);
    goto okay; // TODO: Figure out a graceful way to remove this goto.

    while(1) {
    // loop:
        // LD_HL(mBuenaPrize_BuenaAskWhichPrizeText);
        // CALL(aBuenaPrintText);
        BuenaPrintText_Conv2(BuenaAskWhichPrizeText);

    okay:
        // CALL(aDelayFrame);
        DelayFrame();
        // CALL(aUpdateSprites);
        UpdateSprites_Conv();
        // CALL(aPrintBlueCardBalance);
        PrintBlueCardBalance();
        // CALL(aBuena_PrizeMenu);
        uint8_t a = Buena_PrizeMenu();
        // IF_Z goto done;
        if(a == 0)
            break;
        // LD_addr_A(wMenuSelectionQuantity);
        wram->wMenuSelectionQuantity = a;
        // CALL(aBuena_GetPrize);
        const item_price_s* prize = Buena_GetPrize(a);
        // LD_A_hl;
        // LD_addr_A(wNamedObjectIndex);
        // CALL(aGetItemName);
        GetItemName(prize->id);
        // LD_HL(mBuenaPrize_BuenaIsThatRightText);
        // CALL(aBuenaPrintText);
        BuenaPrintText_Conv2(BuenaIsThatRightText);
        // CALL(aYesNoBox);
        // IF_C goto loop;
        if(!YesNoBox_Conv())
            continue;

        // LD_A_addr(wMenuSelectionQuantity);
        // CALL(aBuena_GetPrize);
        // INC_HL;
        // LD_A_hld;
        // LD_C_A;
        // LD_A_addr(wBlueCardBalance);
        // CP_A_C;
        // IF_C goto InsufficientBalance;
        if(wram->wBlueCardBalance < prize->price) {
        // InsufficientBalance:
            // LD_HL(mBuenaPrize_BuenaNotEnoughPointsText);
            // goto print;
            BuenaPrintText_Conv2(BuenaNotEnoughPointsText);
            continue;
        }

        // LD_A_hli;
        // PUSH_HL;
        // LD_addr_A(wCurItem);
        // LD_A(0x1);
        // LD_addr_A(wItemQuantityChange);
        // LD_HL(wNumItems);
        // CALL(aReceiveItem);
        // POP_HL;
        // IF_NC goto BagFull;
        if(!ReceiveItem_Conv((item_pocket_s*)&wram->wNumItems, prize->id, 0x1)) {
        // BagFull:
            // LD_HL(mBuenaPrize_BuenaNoRoomText);
            // goto print;
            BuenaPrintText_Conv2(BuenaNoRoomText);
            continue;
        }
        // LD_A_hl;
        // LD_C_A;
        // LD_A_addr(wBlueCardBalance);
        // SUB_A_C;
        // LD_addr_A(wBlueCardBalance);
        wram->wBlueCardBalance -= (uint8_t)prize->price;
        // CALL(aPrintBlueCardBalance);
        PrintBlueCardBalance();
        // goto Purchase;

    // Purchase:
        // LD_DE(SFX_TRANSACTION);
        // CALL(aPlaySFX);
        PlaySFX(SFX_TRANSACTION);
        // LD_HL(mBuenaPrize_BuenaHereYouGoText);

    // print:
        // CALL(aBuenaPrintText);
        BuenaPrintText_Conv2(BuenaHereYouGoText);
        // goto loop;
    }

// done:
    // CALL(aCloseWindow);
    CloseWindow_Conv2();
    // CALL(aCloseWindow);
    CloseWindow_Conv2();
    // LD_HL(mBuenaPrize_BuenaComeAgainText);
    // CALL(aPrintText);
    PrintText_Conv2(BuenaComeAgainText);
    // CALL(aJoyWaitAorB);
    JoyWaitAorB_Conv();
    // CALL(aPlayClickSFX);
    PlayClickSFX_Conv();
    // RET;
}

void Buena_DisplayBlueCardBalance(void){
    // LD_HL(mBlueCardBalanceMenuHeader);
    // CALL(aLoadMenuHeader);
    LoadMenuHeader_Conv2(&BlueCardBalanceMenuHeader);
    // RET;
}

static void PrintBlueCardBalance_DrawBox(const uint8_t* de) {
    static const char Points_string[] = "Points";
    // PUSH_DE;
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = 0;
    // LD_HL(mBlueCardBalanceMenuHeader);
    // CALL(aCopyMenuHeader);
    CopyMenuHeader_Conv2(&BlueCardBalanceMenuHeader);
    // CALL(aMenuBox);
    MenuBox_Conv();
    // CALL(aUpdateSprites);
    UpdateSprites_Conv();
    // CALL(aMenuBoxCoord2Tile);
    // LD_BC(SCREEN_WIDTH + 1);
    // ADD_HL_BC;
    // LD_DE(mPrintBlueCardBalance_Points_string);
    struct TextPrintState st = {.de = U82C(Points_string), .hl = MenuBoxCoord2Tile_Conv() + SCREEN_WIDTH + 1};
    // CALL(aPlaceString);
    PlaceString_Conv(&st, st.hl);
    // LD_H_B;
    // LD_L_C;
    // INC_HL;
    st.hl = st.bc + 1;
    // LD_A(0x7f);
    // LD_hli_A;
    st.hl[0] = 0x7f;
    // LD_hld_A;
    st.hl[1] = 0x7f;
    // POP_DE;
    // LD_BC((1 << 8) | 2);
    // CALL(aPrintNum);
    PrintNum_Conv2(st.hl, de, 1, 2);
    // RET;
}

void PrintBlueCardBalance(void){
    // LD_DE(wBlueCardBalance);
    // CALL(aPrintBlueCardBalance_DrawBox);
    PrintBlueCardBalance_DrawBox(&wram->wBlueCardBalance);
    // RET;
}

const struct MenuHeader BlueCardBalanceMenuHeader = {
    .flags = MENU_BACKUP_TILES,  // flags
    .coord = menu_coords(0, 11, 11, 13),
    .data = NULL,
    .defaultOption = 1,
};

void Buena_PlacePrizeMenuBox(void){
    static const struct MenuHeader MenuHeader = {
        .flags = MENU_BACKUP_TILES,  // flags
        .coord = menu_coords(0, 0, 17, TEXTBOX_Y - 1),
        .data = NULL,
        .defaultOption = 1,
    };
    // LD_HL(mBuena_PlacePrizeMenuBox_MenuHeader);
    // CALL(aLoadMenuHeader);
    // RET;
    LoadMenuHeader_Conv2(&MenuHeader);
}

static void Buena_PrizeMenu_PrintPrizeItem(const struct MenuData* data, tile_t* de){
    (void)data;
    // LD_A_addr(wMenuSelection);
    // CALL(aBuena_GetPrize);
    const item_price_s* prize = Buena_GetPrize(wram->wMenuSelection);
    // LD_A_hl;
    // PUSH_DE;
    // LD_addr_A(wNamedObjectIndex);
    // CALL(aGetItemName);
    // POP_HL;
    // CALL(aPlaceString);
    PlaceStringSimple(GetItemName(prize->id), de);
    // RET;
}

static void Buena_PrizeMenu_PrintPrizePoints(const struct MenuData* data, tile_t* de) {
    (void)data;
    // LD_A_addr(wMenuSelection);
    // CALL(aBuena_GetPrize);
    const item_price_s* prize = Buena_GetPrize(wram->wMenuSelection);
    // INC_HL;
    // LD_A_hl;
    // LD_C(0xf6);
    // ADD_A_C;
    // LD_de_A;
    *de = 0xf6 + (uint8_t)prize->price;
    // RET;
}

static const struct MenuHeader Buena_PrizeMenu_MenuHeader = {
    .flags = MENU_BACKUP_TILES,  // flags
    .coord = menu_coords(1, 1, 16, 9),
    //dw ['.MenuData'];
    .data = &(struct MenuData) {
    // MenuData:
        .flags = SCROLLINGMENU_DISPLAY_ARROWS,  // flags
        .scrollingMenu = {
            .rows = 4, .cols = 13,  // rows, columns
            .format = SCROLLINGMENU_ITEMS_NORMAL,  // item format
            //dba ['.Prizes']
            .list = (uint8_t[]) {
            // Prizes:
                NUM_BUENA_PRIZES,
                // for(int x = 0; x < NUM_BUENA_PRIZES; x++){
                //db ['x + 1'];
                1,
                2,
                3,
                4,
                5,
                6,
                7,
                8,
                9,
                // }
                //db ['-1'];
                (uint8_t)-1,
            },
            //dba ['.PrintPrizeItem']
            .func1 = Buena_PrizeMenu_PrintPrizeItem,
            //dba ['.PrintPrizePoints']
            .func2 = Buena_PrizeMenu_PrintPrizePoints,
        },
    },
    .defaultOption = 1,  // default option
};
    //db ['0'];

uint8_t Buena_PrizeMenu(void){
    // LD_HL(mBuena_PrizeMenu_MenuHeader);
    // CALL(aCopyMenuHeader);
    CopyMenuHeader_Conv2(&Buena_PrizeMenu_MenuHeader);
    // LD_A_addr(wMenuSelection);
    // LD_addr_A(wMenuCursorPosition);
    wram->wMenuCursorPosition = wram->wMenuSelection;
    // XOR_A_A;
    // LD_addr_A(wWhichIndexSet);
    wram->wWhichIndexSet = 0;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = 0x0;
    // CALL(aInitScrollingMenu);
    InitScrollingMenu_Conv();
    // CALL(aUpdateSprites);
    UpdateSprites_Conv();
    // CALL(aScrollingMenu);
    uint8_t c = ScrollingMenu_Conv();
    // LD_A_addr(wMenuSelection);
    // LD_C_A;
    uint8_t sel = wram->wMenuSelection;
    // LD_A_addr(wMenuCursorY);
    // LD_addr_A(wMenuSelection);
    wram->wMenuSelection = wram->wMenuCursorY;
    // LD_A_addr(wMenuJoypad);
    // CP_A(0x2);
    // IF_Z goto cancel;
    if(c != 0x2) {
        // LD_A_C;
        // AND_A_A;
        // RET_NZ ;
        if(sel != 0)
            return sel;
    }

// cancel:
    // XOR_A_A;
    // RET;
    return 0;
}

const item_price_s* Buena_GetPrize(uint8_t a){
    // DEC_A;
    // LD_HL(mBuenaPrizeItems);
    // LD_B(0);
    // LD_C_A;
    // ADD_HL_BC;
    // ADD_HL_BC;
    return BuenaPrizeItems + (a - 1);
    // RET;

// INCLUDE "data/items/buena_prizes.asm"

}
