#include "../../constants.h"
#include "menu_2.h"
#include "../../home/text.h"
#include "../../home/print_text.h"
#include "../../home/names.h"
#include "../../home/pokemon.h"

void PlaceMenuItemName(void){
    PUSH_DE;
    LD_A_addr(wMenuSelection);
    LD_addr_A(wNamedObjectIndex);
    CALL(aGetItemName);
    POP_HL;
    CALL(aPlaceString);
    RET;

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

void PlaceMoneyTopRight(void){
    LD_HL(mMoneyTopRightMenuHeader);
    CALL(aCopyMenuHeader);
    JR(mPlaceMoneyTextbox);

}

void PlaceMoneyBottomLeft(void){
    LD_HL(mMoneyBottomLeftMenuHeader);
    CALL(aCopyMenuHeader);
    JR(mPlaceMoneyTextbox);

}

void PlaceMoneyAtTopLeftOfTextbox(void){
    LD_HL(mMoneyTopRightMenuHeader);
    LD_DE((0 << 8) | 11);
    CALL(aOffsetMenuHeader);

    return PlaceMoneyTextbox();
}

void PlaceMoneyTextbox(void){
    CALL(aMenuBox);
    CALL(aMenuBoxCoord2Tile);
    LD_DE(SCREEN_WIDTH + 1);
    ADD_HL_DE;
    LD_DE(wMoney);
    LD_BC((PRINTNUM_MONEY | 3 << 8) | 6);
    CALL(aPrintNum);
    RET;

}

void MoneyTopRightMenuHeader(void){
    //db ['MENU_BACKUP_TILES'];  // flags
    //menu_coords ['11', '0', 'SCREEN_WIDTH - 1', '2'];
    //dw ['NULL'];
    //db ['1'];  // default option

    return MoneyBottomLeftMenuHeader();
}

void MoneyBottomLeftMenuHeader(void){
    //db ['MENU_BACKUP_TILES'];  // flags
    //menu_coords ['0', '11', '8', '13'];
    //dw ['NULL'];
    //db ['1'];  // default option

    return DisplayCoinCaseBalance();
}

void DisplayCoinCaseBalance(void){
// Place a text box of size 1x7 at 11, 0.
    hlcoord(11, 0, wTilemap);
    LD_B(1);
    LD_C(7);
    CALL(aTextbox);
    hlcoord(12, 0, wTilemap);
    LD_DE(mCoinString);
    CALL(aPlaceString);
    hlcoord(17, 1, wTilemap);
    LD_DE(mShowMoney_TerminatorString);
    CALL(aPlaceString);
    LD_DE(wCoins);
    LD_BC((2 << 8) | 4);
    hlcoord(13, 1, wTilemap);
    CALL(aPrintNum);
    RET;

}

void DisplayMoneyAndCoinBalance(void){
    hlcoord(5, 0, wTilemap);
    LD_B(3);
    LD_C(13);
    CALL(aTextbox);
    hlcoord(6, 1, wTilemap);
    LD_DE(mMoneyString);
    CALL(aPlaceString);
    hlcoord(12, 1, wTilemap);
    LD_DE(wMoney);
    LD_BC((PRINTNUM_MONEY | 3 << 8) | 6);
    CALL(aPrintNum);
    hlcoord(6, 3, wTilemap);
    LD_DE(mCoinString);
    CALL(aPlaceString);
    hlcoord(15, 3, wTilemap);
    LD_DE(wCoins);
    LD_BC((2 << 8) | 4);
    CALL(aPrintNum);
    RET;

}

void MoneyString(void){
    //db ['"MONEY@"'];
    return CoinString();
}

void CoinString(void){
    //db ['"COIN@"'];
    return ShowMoney_TerminatorString();
}

void ShowMoney_TerminatorString(void){
    //db ['"@"'];

    return StartMenu_PrintSafariGameStatus();
}

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


slash_500:
    //db ['"／５００@"'];

booru_ko:
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
