#include "../../constants.h"
#include "menu_2.h"
#include "../../home/menu.h"
#include "../../home/text.h"
#include "../../home/print_text.h"
#include "../../home/names.h"
#include "../../home/pokemon.h"
#include "../../home/copy.h"
#include "../../home/item.h"
#include "../../data/items/apricorn_balls.h"
#include "../items/items.h"

void PlaceMenuItemName(void){
    PUSH_DE;
    LD_A_addr(wMenuSelection);
    LD_addr_A(wNamedObjectIndex);
    CALL(aGetItemName);
    POP_HL;
    CALL(aPlaceString);
    RET;

}

void PlaceMenuItemName_Conv(const struct MenuData* data, uint8_t* de){
    (void)data;
    // PUSH_DE;
    // LD_A_addr(wMenuSelection);
    // LD_addr_A(wNamedObjectIndex);
    // CALL(aGetItemName);
    uint8_t* str = GetItemName_Conv2(wram->wMenuSelection);
    // POP_HL;
    // CALL(aPlaceString);
    PlaceStringSimple(str, de);
    // RET;
}

void PlaceMenuItemQuantity(void){
    PUSH_DE;
    LD_A_addr(wMenuSelection);
    LD_addr_A(wCurItem);
    FARCALL(av_CheckTossableItem);
    LD_A_addr(wItemAttributeValue);
    POP_HL;
    AND_A_A;
    IF_NZ goto done;
    LD_DE(0x15);
    ADD_HL_DE;
    LD_hl(0xf1);
    INC_HL;
    LD_DE(wMenuSelectionQuantity);
    LD_BC((1 << 8) | 2);
    CALL(aPrintNum);


done:
    RET;

}

void PlaceMenuItemQuantity_Conv(const struct MenuData* data, tile_t* de){
    (void)data;
    // PUSH_DE;
    // LD_A_addr(wMenuSelection);
    // LD_addr_A(wCurItem);
    // FARCALL(av_CheckTossableItem);
    // LD_A_addr(wItemAttributeValue);
    // POP_HL;
    // AND_A_A;
    // IF_NZ goto done;
    if(v_CheckTossableItem_Conv(wram->wMenuSelection)){
        // LD_DE(0x15);
        // ADD_HL_DE;
        // LD_hl(0xf1);
        de[0x15] = 0xf1;
        // INC_HL;
        // LD_DE(wMenuSelectionQuantity);
        // LD_BC((1 << 8) | 2);
        // CALL(aPrintNum);
        PrintNum_Conv2(de + 0x16, &wram->wMenuSelectionQuantity, 1, 2);
    }

// done:
    // RET;

}

void PlaceMoneyTopRight(void){
    // LD_HL(mMoneyTopRightMenuHeader);
    // CALL(aCopyMenuHeader);
    CopyMenuHeader_Conv2(&MoneyTopRightMenuHeader);
    // JR(mPlaceMoneyTextbox);
    return PlaceMoneyTextbox();
}

void PlaceMoneyBottomLeft(void){
    // LD_HL(mMoneyBottomLeftMenuHeader);
    // CALL(aCopyMenuHeader);
    CopyMenuHeader_Conv2(&MoneyBottomLeftMenuHeader);
    // JR(mPlaceMoneyTextbox);
    return PlaceMoneyTextbox();
}

void PlaceMoneyAtTopLeftOfTextbox(void){
    // LD_HL(mMoneyTopRightMenuHeader);
    // LD_DE((0 << 8) | 11);
    // CALL(aOffsetMenuHeader);
    OffsetMenuHeader_Conv2(&MoneyTopRightMenuHeader, 0, 11);

    return PlaceMoneyTextbox();
}

void PlaceMoneyTextbox(void){
    // CALL(aMenuBox);
    MenuBox_Conv();
    // CALL(aMenuBoxCoord2Tile);
    // LD_DE(SCREEN_WIDTH + 1);
    // ADD_HL_DE;
    // LD_DE(wMoney);
    // LD_BC((PRINTNUM_MONEY | 3 << 8) | 6);
    // CALL(aPrintNum);
    PrintNum_Conv2(MenuBoxCoord2Tile_Conv() + SCREEN_WIDTH + 1, &wram->wMoney, PRINTNUM_MONEY | 3, 6);
    // RET;
}

const struct MenuHeader MoneyTopRightMenuHeader = {
    .flags = MENU_BACKUP_TILES,  // flags
    .coord = menu_coords(11, 0, SCREEN_WIDTH - 1, 2),
    //dw ['NULL'];
    .data = NULL,
    //db ['1'];  // default option
    .defaultOption = 1,
};

const struct MenuHeader MoneyBottomLeftMenuHeader = {
    .flags = MENU_BACKUP_TILES,  // flags
    .coord = menu_coords(0, 11, 8, 13),
    //dw ['NULL'];
    .data = NULL,
    //db ['1'];  // default option
    .defaultOption = 1,
};

void DisplayCoinCaseBalance(void){
// Place a text box of size 1x7 at 11, 0.
    // hlcoord(11, 0, wTilemap);
    // LD_B(1);
    // LD_C(7);
    // CALL(aTextbox);
    Textbox_Conv2(coord(11, 0, wram->wTilemap), 1, 7);
    // hlcoord(12, 0, wTilemap);
    // LD_DE(mCoinString);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(CoinString), coord(12, 0, wram->wTilemap));
    // hlcoord(17, 1, wTilemap);
    // LD_DE(mShowMoney_TerminatorString);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(ShowMoney_TerminatorString), coord(17, 1, wram->wTilemap));
    // LD_DE(wCoins);
    // LD_BC((2 << 8) | 4);
    // hlcoord(13, 1, wTilemap);
    // CALL(aPrintNum);
    PrintNum_Conv2(coord(13, 1, wram->wTilemap), &wram->wCoins, 2, 4);
    // RET;
}

void DisplayMoneyAndCoinBalance(void){
    // hlcoord(5, 0, wTilemap);
    // LD_B(3);
    // LD_C(13);
    // CALL(aTextbox);
    Textbox_Conv2(coord(5, 0, wram->wTilemap), 3, 13);
    // hlcoord(6, 1, wTilemap);
    // LD_DE(mMoneyString);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(MoneyString), coord(6, 1, wram->wTilemap));
    // hlcoord(12, 1, wTilemap);
    // LD_DE(wMoney);
    // LD_BC((PRINTNUM_MONEY | 3 << 8) | 6);
    // CALL(aPrintNum);
    PrintNum_Conv2(coord(12, 1, wram->wTilemap), wram->wMoney, PRINTNUM_MONEY | 3, 6);
    // hlcoord(6, 3, wTilemap);
    // LD_DE(mCoinString);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(CoinString), coord(6, 3, wram->wTilemap));
    // hlcoord(15, 3, wTilemap);
    // LD_DE(wCoins);
    // LD_BC((2 << 8) | 4);
    // CALL(aPrintNum);
    PrintNum_Conv2(coord(15, 3, wram->wTilemap), &wram->wCoins, 2, 4);
    // RET;
}

const char MoneyString[] = "MONEY@";
const char CoinString[] = "COIN@";
const char ShowMoney_TerminatorString[] = "@";

void StartMenu_PrintSafariGameStatus(void){
//  //  unreferenced
    LD_HL(wOptions);
    LD_A_hl;
    PUSH_AF;
    SET_hl(NO_TEXT_SCROLL);
    hlcoord(0, 0, wTilemap);
    LD_B(3);
    LD_C(7);
    CALL(aTextbox);
    hlcoord(1, 1, wTilemap);
    LD_DE(wSafariTimeRemaining);
    LD_BC((2 << 8) | 3);
    CALL(aPrintNum);
    hlcoord(4, 1, wTilemap);
    LD_DE(mStartMenu_PrintSafariGameStatus_slash_500);
    CALL(aPlaceString);
    hlcoord(1, 3, wTilemap);
    LD_DE(mStartMenu_PrintSafariGameStatus_booru_ko);
    CALL(aPlaceString);
    hlcoord(5, 3, wTilemap);
    LD_DE(wSafariBallsRemaining);
    LD_BC((1 << 8) | 2);
    CALL(aPrintNum);
    POP_AF;
    LD_addr_A(wOptions);
    RET;


//slash_500:
    //db ['"／５００@"'];

//booru_ko:
    //db ['"ボール\u3000\u3000\u3000こ@"'];
}

void StartMenu_DrawBugContestStatusBox(void){
    // hlcoord(0, 0, wTilemap);
    // LD_B(5);
    // LD_C(17);
    // CALL(aTextbox);
    Textbox_Conv2(coord(0, 0, wram->wTilemap), 5, 17);
    // RET;
}

void StartMenu_PrintBugContestStatus(void){
    static const char BallsString[] = "BALLS:@";
    static const char CaughtString[] = "CAUGHT@";
    static const char NoneString[] = "None@";
    static const char LevelString[] = "LEVEL@";
    // LD_HL(wOptions);
    // LD_A_hl;
    // PUSH_AF;
    uint8_t options = wram->wOptions;
    // SET_hl(NO_TEXT_SCROLL);
    bit_set(wram->wOptions, NO_TEXT_SCROLL);
    // CALL(aStartMenu_DrawBugContestStatusBox);
    StartMenu_DrawBugContestStatusBox();
    // hlcoord(1, 5, wTilemap);
    // LD_DE(mStartMenu_PrintBugContestStatus_BallsString);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(BallsString), coord(1, 5, wram->wTilemap));
    // hlcoord(8, 5, wTilemap);
    // LD_DE(wParkBallsRemaining);
    // LD_BC((PRINTNUM_LEFTALIGN | 1 << 8) | 2);
    // CALL(aPrintNum);
    PrintNum_Conv2(coord(8, 5, wram->wTilemap), &wram->wParkBallsRemaining, PRINTNUM_LEFTALIGN | 1, 2);
    // hlcoord(1, 1, wTilemap);
    // LD_DE(mStartMenu_PrintBugContestStatus_CaughtString);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(CaughtString), coord(1, 1, wram->wTilemap));
    // LD_A_addr(wContestMon);
    // AND_A_A;
    // LD_DE(mStartMenu_PrintBugContestStatus_NoneString);
    U82CA(wram->wStringBuffer1, NoneString);
    // IF_Z goto no_contest_mon;
    if(wram->wContestMon.mon.species != 0) {
        // LD_addr_A(wNamedObjectIndex);
        // CALL(aGetPokemonName);
        GetPokemonName_Conv2(wram->wContestMon.mon.species);
    }

// no_contest_mon:
    // hlcoord(8, 1, wTilemap);
    // CALL(aPlaceString);
    PlaceStringSimple(wram->wStringBuffer1, coord(8, 1, wram->wTilemap));
    // LD_A_addr(wContestMon);
    // AND_A_A;
    // IF_Z goto skip_level;
    if(wram->wContestMon.mon.species != 0) {
        // hlcoord(1, 3, wTilemap);
        // LD_DE(mStartMenu_PrintBugContestStatus_LevelString);
        // CALL(aPlaceString);
        struct TextPrintState st = {.hl = coord(1, 3, wram->wTilemap), .de = U82C(LevelString)};
        PlaceString_Conv(&st, st.hl);
        // LD_A_addr(wContestMonLevel);
        // LD_H_B;
        // LD_L_C;
        st.hl = st.bc;
        // INC_HL;
        // LD_C(3);
        // CALL(aPrint8BitNumLeftAlign);
        Print8BitNumLeftAlign_Conv(st.hl + 1, wram->wContestMon.mon.level, 3);
    }

// skip_level:
    // POP_AF;
    // LD_addr_A(wOptions);
    wram->wOptions = options;
    // RET;


BallsJPString:;
//   //  unreferenced
    //db ['"ボール\u3000\u3000\u3000こ@"'];
}

void FindApricornsInBag(void){
//  Checks the bag for Apricorns.
    LD_HL(wKurtApricornCount);
    XOR_A_A;
    LD_hli_A;
    //assert ['wKurtApricornCount + 1 == wKurtApricornItems'];
    DEC_A;
    LD_BC(10);
    CALL(aByteFill);

    LD_HL(mApricornBalls);

loop:
    LD_A_hl;
    CP_A(-1);
    IF_Z goto done;
    PUSH_HL;
    LD_addr_A(wCurItem);
    LD_HL(wNumItems);
    CALL(aCheckItem);
    POP_HL;
    IF_NC goto nope;
    LD_A_hl;
    CALL(aFindApricornsInBag_addtobuffer);

nope:
    INC_HL;
    INC_HL;
    goto loop;


done:
    LD_A_addr(wKurtApricornCount);
    AND_A_A;
    RET_NZ ;
    SCF;
    RET;


addtobuffer:
    PUSH_HL;
    LD_HL(wKurtApricornCount);
    INC_hl;
    LD_E_hl;
    LD_D(0);
    ADD_HL_DE;
    LD_hl_A;
    POP_HL;
    RET;

// INCLUDE "data/items/apricorn_balls.asm"

}

static void FindApricornsInBag_addtobuffer(item_t a) {
    // PUSH_HL;
    // LD_HL(wKurtApricornCount);
    // INC_hl;
    // LD_E_hl;
    // LD_D(0);
    // ADD_HL_DE;
    // LD_hl_A;
    wram->wKurtApricornItems[wram->wKurtApricornCount++] = a;
    // POP_HL;
    // RET;
}

bool FindApricornsInBag_Conv(void){
//  Checks the bag for Apricorns.
    // LD_HL(wKurtApricornCount);
    wram->wKurtApricornCount = 0;
    // XOR_A_A;
    // LD_hli_A;
    //assert ['wKurtApricornCount + 1 == wKurtApricornItems'];
    // DEC_A;
    // LD_BC(10);
    // CALL(aByteFill);
    ByteFill_Conv2(wram->wKurtApricornItems, 10, 0xff);
    // LD_HL(mApricornBalls);
    const struct U8Item* hl = ApricornBalls;

    uint8_t a;
    while(1) {
    // loop:
        // LD_A_hl;
        a = hl->value;
        // CP_A(-1);
        // IF_Z goto done;
        if(a == 0xff) {
        // done:
            // LD_A_addr(wKurtApricornCount);
            // AND_A_A;
            // RET_NZ ;
            if(wram->wKurtApricornCount != 0)
                return true;
            // SCF;
            // RET;
            return false;
        }
        // PUSH_HL;
        // LD_addr_A(wCurItem);
        wram->wCurItem = a;
        // LD_HL(wNumItems);
        // CALL(aCheckItem);
        // POP_HL;
        // IF_NC goto nope;
        if(CheckItem_Conv(a, &wram->wNumItems)) {
            // LD_A_hl;
            // CALL(aFindApricornsInBag_addtobuffer);
            FindApricornsInBag_addtobuffer(hl->item);
        }

    // nope:
        // INC_HL;
        // INC_HL;
        hl++;
        // goto loop;
    }

// INCLUDE "data/items/apricorn_balls.asm"

}
