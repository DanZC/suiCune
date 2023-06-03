#include "../../constants.h"
#include "main_menu.h"

// MainMenuItems indexes
enum {
    MAINMENU_NEW_GAME,  // 0
    MAINMENU_CONTINUE,  // 1
    MAINMENU_MOBILE_MYSTERY,  // 2
    MAINMENU_MOBILE,  // 3
    MAINMENU_MOBILE_STUDIUM,  // 4
    MAINMENU_MYSTERY_MOBILE_STUDIUM,  // 5
    MAINMENU_MYSTERY,  // 6
    MAINMENU_MYSTERY_STUDIUM,  // 7
    MAINMENU_STUDIUM,  // 8
};

// MainMenu.Strings and MainMenu.Jumptable indexes
enum {
    MAINMENUITEM_CONTINUE,  // 0
    MAINMENUITEM_NEW_GAME,  // 1
    MAINMENUITEM_OPTION,  // 2
    MAINMENUITEM_MYSTERY_GIFT,  // 3
    MAINMENUITEM_MOBILE,  // 4
    MAINMENUITEM_MOBILE_STUDIUM,  // 5
    MAINMENUITEM_DEBUG_ROOM,  // 6
};

void MobileMenuGFX(void){
// INCBIN "gfx/mobile/mobile_menu.2bpp"

    return MainMenu();
}

void MainMenu(void){

loop:
    XOR_A_A;
    LD_addr_A(wDisableTextAcceleration);
    CALL(aClearTilemapEtc);
    LD_B(SCGB_DIPLOMA);
    CALL(aGetSGBLayout);
    CALL(aSetPalettes);
    LD_HL(wGameTimerPaused);
    RES_hl(GAME_TIMER_PAUSED_F);
    CALL(aMainMenu_GetWhichMenu);
    LD_addr_A(wWhichIndexSet);
    CALL(aMainMenu_PrintCurrentTimeAndDay);
    LD_HL(mMainMenu_MenuHeader);
    CALL(aLoadMenuHeader);
    CALL(aMainMenuJoypadLoop);
    CALL(aCloseWindow);
    IF_C goto quit;
    CALL(aClearTilemap);
    LD_A_addr(wMenuSelection);
    LD_HL(mMainMenu_Jumptable);
    RST(aJumpTable);
    goto loop;


quit:
    RET;


MenuHeader:
    //db ['MENU_BACKUP_TILES'];  // flags
    //menu_coords ['0', '0', '16', '7'];
    //dw ['.MenuData'];
    //db ['1'];  // default option


MenuData:
    //db ['STATICMENU_CURSOR'];  // flags
    //db ['0'];  // items
    //dw ['MainMenuItems'];
    //dw ['PlaceMenuStrings'];
    //dw ['.Strings'];


Strings:
//  entries correspond to MAINMENUITEM_* constants
    //db ['"CONTINUE@"'];
    //db ['"NEW GAME@"'];
    //db ['"OPTION@"'];
    //db ['"MYSTERY GIFT@"'];
    //db ['"MOBILE@"'];
    //db ['"MOBILE STUDIUM@"'];
#if _DEBUG
    //db ['"DEBUG ROOM@"'];
#endif


Jumptable:
//  entries correspond to MAINMENUITEM_* constants
    //dw ['MainMenu_Continue'];
    //dw ['MainMenu_NewGame'];
    //dw ['MainMenu_Option'];
    //dw ['MainMenu_MysteryGift'];
    //dw ['MainMenu_Mobile'];
    //dw ['MainMenu_MobileStudium'];
#if _DEBUG
    //dw ['MainMenu_DebugRoom'];
#endif

    return MainMenuItems();
}

void MainMenuItems(void){
//  entries correspond to MAINMENU_* constants

// MAINMENU_NEW_GAME
    //db ['2'];
    //db ['MAINMENUITEM_NEW_GAME'];
    //db ['MAINMENUITEM_OPTION'];
    //db ['-1'];

// MAINMENU_CONTINUE
    //db ['3 + DEF(_DEBUG)'];
    //db ['MAINMENUITEM_CONTINUE'];
    //db ['MAINMENUITEM_NEW_GAME'];
    //db ['MAINMENUITEM_OPTION'];
#if _DEBUG
    //db ['MAINMENUITEM_DEBUG_ROOM'];
#endif
    //db ['-1'];

// MAINMENU_MOBILE_MYSTERY
    //db ['5 + DEF(_DEBUG)'];
    //db ['MAINMENUITEM_CONTINUE'];
    //db ['MAINMENUITEM_NEW_GAME'];
    //db ['MAINMENUITEM_OPTION'];
    //db ['MAINMENUITEM_MYSTERY_GIFT'];
    //db ['MAINMENUITEM_MOBILE'];
#if _DEBUG
    //db ['MAINMENUITEM_DEBUG_ROOM'];
#endif
    //db ['-1'];

// MAINMENU_MOBILE
    //db ['4 + DEF(_DEBUG)'];
    //db ['MAINMENUITEM_CONTINUE'];
    //db ['MAINMENUITEM_NEW_GAME'];
    //db ['MAINMENUITEM_OPTION'];
    //db ['MAINMENUITEM_MOBILE'];
#if _DEBUG
    //db ['MAINMENUITEM_DEBUG_ROOM'];
#endif
    //db ['-1'];

// MAINMENU_MOBILE_STUDIUM
    //db ['5 + DEF(_DEBUG)'];
    //db ['MAINMENUITEM_CONTINUE'];
    //db ['MAINMENUITEM_NEW_GAME'];
    //db ['MAINMENUITEM_OPTION'];
    //db ['MAINMENUITEM_MOBILE'];
    //db ['MAINMENUITEM_MOBILE_STUDIUM'];
#if _DEBUG
    //db ['MAINMENUITEM_DEBUG_ROOM'];
#endif
    //db ['-1'];

// MAINMENU_MYSTERY_MOBILE_STUDIUM
    //db ['6 + DEF(_DEBUG)'];
    //db ['MAINMENUITEM_CONTINUE'];
    //db ['MAINMENUITEM_NEW_GAME'];
    //db ['MAINMENUITEM_OPTION'];
    //db ['MAINMENUITEM_MYSTERY_GIFT'];
    //db ['MAINMENUITEM_MOBILE'];
    //db ['MAINMENUITEM_MOBILE_STUDIUM'];
#if _DEBUG
    //db ['MAINMENUITEM_DEBUG_ROOM'];
#endif
    //db ['-1'];

// MAINMENU_MYSTERY
    //db ['4 + DEF(_DEBUG)'];
    //db ['MAINMENUITEM_CONTINUE'];
    //db ['MAINMENUITEM_NEW_GAME'];
    //db ['MAINMENUITEM_OPTION'];
    //db ['MAINMENUITEM_MYSTERY_GIFT'];
#if _DEBUG
    //db ['MAINMENUITEM_DEBUG_ROOM'];
#endif
    //db ['-1'];

// MAINMENU_MYSTERY_STUDIUM
    //db ['5 + DEF(_DEBUG)'];
    //db ['MAINMENUITEM_CONTINUE'];
    //db ['MAINMENUITEM_NEW_GAME'];
    //db ['MAINMENUITEM_OPTION'];
    //db ['MAINMENUITEM_MYSTERY_GIFT'];
    //db ['MAINMENUITEM_MOBILE_STUDIUM'];
#if _DEBUG
    //db ['MAINMENUITEM_DEBUG_ROOM'];
#endif
    //db ['-1'];

// MAINMENU_STUDIUM
    //db ['4 + DEF(_DEBUG)'];
    //db ['MAINMENUITEM_CONTINUE'];
    //db ['MAINMENUITEM_NEW_GAME'];
    //db ['MAINMENUITEM_OPTION'];
    //db ['MAINMENUITEM_MOBILE_STUDIUM'];
#if _DEBUG
    //db ['MAINMENUITEM_DEBUG_ROOM'];
#endif
    //db ['-1'];

    return MainMenu_GetWhichMenu();
}

void MainMenu_GetWhichMenu(void){
    NOP;
    NOP;
    NOP;
    LD_A_addr(wSaveFileExists);
    AND_A_A;
    IF_NZ goto next;
    LD_A(MAINMENU_NEW_GAME);
    RET;


next:
    LDH_A_addr(hCGB);
    CP_A(TRUE);
    LD_A(MAINMENU_CONTINUE);
    RET_NZ ;
    LD_A(MBANK(asNumDailyMysteryGiftPartnerIDs));
    CALL(aOpenSRAM);
    LD_A_addr(sNumDailyMysteryGiftPartnerIDs);
    CP_A(-1);  // locked?
    CALL(aCloseSRAM);
    IF_NZ goto mystery_gift;
// This check makes no difference.
    LD_A_addr(wStatusFlags);
    BIT_A(STATUSFLAGS_MAIN_MENU_MOBILE_CHOICES_F);
    LD_A(MAINMENU_CONTINUE);
    IF_Z goto ok;
    goto ok;


ok:
    goto ok2;


ok2:
    LD_A(MAINMENU_CONTINUE);
    RET;


mystery_gift:
// This check makes no difference.
    LD_A_addr(wStatusFlags);
    BIT_A(STATUSFLAGS_MAIN_MENU_MOBILE_CHOICES_F);
    IF_Z goto ok3;
    goto ok3;


ok3:
    goto ok4;


ok4:
    LD_A(MAINMENU_MYSTERY);
    RET;

}

void MainMenuJoypadLoop(void){
    CALL(aSetUpMenu);

loop:
    CALL(aMainMenu_PrintCurrentTimeAndDay);
    LD_A_addr(w2DMenuFlags1);
    SET_A(5);
    LD_addr_A(w2DMenuFlags1);
    CALL(aGetScrollingMenuJoypad);
    LD_A_addr(wMenuJoypad);
    CP_A(B_BUTTON);
    IF_Z goto b_button;
    CP_A(A_BUTTON);
    IF_Z goto a_button;
    goto loop;


a_button:
    CALL(aPlayClickSFX);
    AND_A_A;
    RET;


b_button:
    SCF;
    RET;

}

void MainMenu_PrintCurrentTimeAndDay(void){
    LD_A_addr(wSaveFileExists);
    AND_A_A;
    RET_Z ;
    XOR_A_A;
    LDH_addr_A(hBGMapMode);
    CALL(aMainMenu_PrintCurrentTimeAndDay_PlaceBox);
    LD_HL(wOptions);
    LD_A_hl;
    PUSH_AF;
    SET_hl(NO_TEXT_SCROLL);
    CALL(aMainMenu_PrintCurrentTimeAndDay_PlaceTime);
    POP_AF;
    LD_addr_A(wOptions);
    LD_A(0x1);
    LDH_addr_A(hBGMapMode);
    RET;


PlaceBox:
    CALL(aCheckRTCStatus);
    AND_A(0b10000000);  // Day count exceeded 16383
    IF_NZ goto TimeFail;
    hlcoord(0, 14, wTilemap);
    LD_B(2);
    LD_C(18);
    CALL(aTextbox);
    RET;


TimeFail:
    CALL(aSpeechTextbox);
    RET;


PlaceTime:
    LD_A_addr(wSaveFileExists);
    AND_A_A;
    RET_Z ;
    CALL(aCheckRTCStatus);
    AND_A(0x80);
    JP_NZ (mMainMenu_PrintCurrentTimeAndDay_PrintTimeNotSet);
    CALL(aUpdateTime);
    CALL(aGetWeekday);
    LD_B_A;
    decoord(1, 15, wTilemap);
    CALL(aMainMenu_PrintCurrentTimeAndDay_PrintDayOfWeek);
    decoord(4, 16, wTilemap);
    LDH_A_addr(hHours);
    LD_C_A;
    FARCALL(aPrintHour);
    LD_hl(0x9c);
    INC_HL;
    LD_DE(hMinutes);
    LD_BC((PRINTNUM_LEADINGZEROS | 1 << 8) | 2);
    CALL(aPrintNum);
    RET;


minString:
//   //  unreferenced
    //db ['"min.@"'];


PrintTimeNotSet:
    hlcoord(1, 14, wTilemap);
    LD_DE(mMainMenu_PrintCurrentTimeAndDay_TimeNotSetString);
    CALL(aPlaceString);
    RET;


TimeNotSetString:
    //db ['"TIME NOT SET@"'];


MainMenuTimeUnknownText:
//   //  unreferenced
    //text_far ['_MainMenuTimeUnknownText']
    //text_end ['?']


PrintDayOfWeek:
    PUSH_DE;
    LD_HL(mMainMenu_PrintCurrentTimeAndDay_Days);
    LD_A_B;
    CALL(aGetNthString);
    LD_D_H;
    LD_E_L;
    POP_HL;
    CALL(aPlaceString);
    LD_H_B;
    LD_L_C;
    LD_DE(mMainMenu_PrintCurrentTimeAndDay_Day);
    CALL(aPlaceString);
    RET;


Days:
    //db ['"SUN@"'];
    //db ['"MON@"'];
    //db ['"TUES@"'];
    //db ['"WEDNES@"'];
    //db ['"THURS@"'];
    //db ['"FRI@"'];
    //db ['"SATUR@"'];

Day:
    //db ['"DAY@"'];

    return ClearTilemapEtc();
}

void ClearTilemapEtc(void){
    XOR_A_A;
    LDH_addr_A(hMapAnims);
    CALL(aClearTilemap);
    CALL(aLoadFontsExtra);
    CALL(aLoadStandardFont);
    CALL(aClearWindowData);
    RET;

}

void MainMenu_NewGame(void){
    FARCALL(aNewGame);
    RET;

}

void MainMenu_Option(void){
    FARCALL(aOption);
    RET;

}

void MainMenu_Continue(void){
    FARCALL(aContinue);
    RET;

}

void MainMenu_MysteryGift(void){
    FARCALL(aMysteryGift);
    RET;

}
