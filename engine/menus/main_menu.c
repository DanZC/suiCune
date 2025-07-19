#include "../../constants.h"
#include "main_menu.h"
#include "intro_menu.h"
#include "../rtc/timeset.h"
#include "../../home/text.h"
#include "../../home/gfx.h"
#include "../../home/menu.h"
#include "../../home/time.h"
#include "../../home/tilemap.h"
#include "../../home/pokedex_flags.h"
#include "../../home/sram.h"
#include "../../home/print_text.h"
#include "../../util/intro_jumptable.h"
#include "../../mobile/mobile_menu.h"
#include "../../charmap.h"

static uint8_t MainMenu_GetWhichMenu(void);
static bool MainMenuJoypadLoop(void);
static void MainMenu_PrintCurrentTimeAndDay(void);
static void ClearTilemapEtc(void);

#if DEBUG
#define SHOW_DEBUG_MENU 1
#else
#define SHOW_DEBUG_MENU 0
#endif
void DebugMenu(void);

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

const char MobileMenuGFX[] = "gfx/mobile/mobile_menu.png";

void MainMenu(void){
    static bool (*const Jumptable[])(void) = {
    //  entries correspond to MAINMENUITEM_* constants
        [MAINMENUITEM_CONTINUE]       = MainMenu_Continue,
        [MAINMENUITEM_NEW_GAME]       = MainMenu_NewGame,
        [MAINMENUITEM_OPTION]         = MainMenu_Option,
        [MAINMENUITEM_MYSTERY_GIFT]   = MainMenu_MysteryGift,
        [MAINMENUITEM_MOBILE]         = MainMenu_Mobile,
        [MAINMENUITEM_MOBILE_STUDIUM] = MainMenu_MobileStudium,
    #if SHOW_DEBUG_MENU
        [MAINMENUITEM_DEBUG_ROOM]     = MainMenu_DebugRoom,
    #endif
    };

    static const char* Strings[] = {
    //  entries correspond to MAINMENUITEM_* constants
        [MAINMENUITEM_CONTINUE]         = "CONTINUE@",
        [MAINMENUITEM_NEW_GAME]         = "NEW GAME@",
        [MAINMENUITEM_OPTION]           = "OPTION@",
        [MAINMENUITEM_MYSTERY_GIFT]     = "MYSTERY GIFT@",
        [MAINMENUITEM_MOBILE]           = "MOBILE@",
        [MAINMENUITEM_MOBILE_STUDIUM]   = "MOBILE STUDIUM@",
    #if SHOW_DEBUG_MENU
        [MAINMENUITEM_DEBUG_ROOM]       = "DEBUG ROOM@",
    #endif
    };

    static const struct MenuData MainMenu_MenuData = {
        .flags = STATICMENU_CURSOR,  // flags
        .setupMenu = {
            .count = 0,  // items
            //dw ['MainMenuItems'];
            .itemList = MainMenuItems,
            //dw ['PlaceMenuStrings'];
            .displayFunction = PlaceMenuStrings,
            //dw ['.Strings'];
            .stringsList = Strings,
        },
        .function = NULL,
    };

    static const struct MenuHeader MainMenu_MenuHeader = {
        .flags = MENU_BACKUP_TILES,  // flags
        .coord = menu_coords(0, 0, 16, 7),
        //dw ['.MenuData'];
        .data = &MainMenu_MenuData,
        //db ['1'];  // default option
        .defaultOption = 1,
    };

    while(1) {
    // loop:
        // XOR_A_A;
        // LD_addr_A(wDisableTextAcceleration);
        wram->wDisableTextAcceleration = 0;
        // CALL(aClearTilemapEtc);
        ClearTilemapEtc();
        // LD_B(SCGB_DIPLOMA);
        // CALL(aGetSGBLayout);
        GetSGBLayout(SCGB_DIPLOMA);
        // CALL(aSetPalettes);
        SetPalettes();
        // LD_HL(wGameTimerPaused);
        // RES_hl(GAME_TIMER_PAUSED_F);
        bit_reset(wram->wGameTimerPaused, GAME_TIMER_PAUSED_F);
        // CALL(aMainMenu_GetWhichMenu);
        // LD_addr_A(wWhichIndexSet);
        wram->wWhichIndexSet = MainMenu_GetWhichMenu();
        // CALL(aMainMenu_PrintCurrentTimeAndDay);
        MainMenu_PrintCurrentTimeAndDay();
        // LD_HL(mMainMenu_MenuHeader);
        // CALL(aLoadMenuHeader);
        LoadMenuHeader(&MainMenu_MenuHeader);
        // CALL(aMainMenuJoypadLoop);
        bool q = MainMenuJoypadLoop();
        // CALL(aCloseWindow);
        CloseWindow();
        // IF_C goto quit;
        if(!q)
            return;
        // CALL(aClearTilemap);
        ClearTilemap();
        // LD_A_addr(wMenuSelection);
        // LD_HL(mMainMenu_Jumptable);
        // RST(aJumpTable);
        printf("wMenuSelection = %d\n", wram->wMenuSelection);
        if(Jumptable[wram->wMenuSelection]())
            return;
        // goto loop;
    }


// quit:
    // RET;
}

const uint8_t* MainMenuItems[] = {
//  entries correspond to MAINMENU_* constants

// MAINMENU_NEW_GAME
    [MAINMENU_NEW_GAME] = (const uint8_t[]){
        //db ['2'];
        2,
        MAINMENUITEM_NEW_GAME,
        MAINMENUITEM_OPTION,
        0xff,
    },

// MAINMENU_CONTINUE
    [MAINMENU_CONTINUE] = (const uint8_t[]){
    //db ['3 + DEF(_DEBUG)'];
#if SHOW_DEBUG_MENU
        4,
#else
        3,
#endif
        MAINMENUITEM_CONTINUE,
        MAINMENUITEM_NEW_GAME,
        MAINMENUITEM_OPTION,
#if SHOW_DEBUG_MENU
        MAINMENUITEM_DEBUG_ROOM,
#endif
        0xff,
    },

// MAINMENU_MOBILE_MYSTERY
    [MAINMENU_MOBILE_MYSTERY] = (const uint8_t[]){
    //db ['5 + DEF(_DEBUG)'];
#if SHOW_DEBUG_MENU
        6,
#else
        5,
#endif
        MAINMENUITEM_CONTINUE,
        MAINMENUITEM_NEW_GAME,
        MAINMENUITEM_OPTION,
        MAINMENUITEM_MYSTERY_GIFT,
        MAINMENUITEM_MOBILE,
#if SHOW_DEBUG_MENU
        MAINMENUITEM_DEBUG_ROOM,
#endif
        0xff,
    },

// MAINMENU_MOBILE
    [MAINMENU_MOBILE] = (const uint8_t[]){
    //db ['4 + DEF(_DEBUG)'];
#if SHOW_DEBUG_MENU
        5,
#else
        4,
#endif
        MAINMENUITEM_CONTINUE,
        MAINMENUITEM_NEW_GAME,
        MAINMENUITEM_OPTION,
        MAINMENUITEM_MOBILE,
#if SHOW_DEBUG_MENU
        MAINMENUITEM_DEBUG_ROOM,
#endif
        0xff,
    },

// MAINMENU_MOBILE_STUDIUM
    [MAINMENU_MOBILE_STUDIUM] = (const uint8_t[]){
#if SHOW_DEBUG_MENU
        6,
#else
        5,
#endif
        MAINMENUITEM_CONTINUE,
        MAINMENUITEM_NEW_GAME,
        MAINMENUITEM_OPTION,
        MAINMENUITEM_MOBILE,
        MAINMENUITEM_MOBILE_STUDIUM,
#if SHOW_DEBUG_MENU
        MAINMENUITEM_DEBUG_ROOM,
#endif
        0xff,
    },

// MAINMENU_MYSTERY_MOBILE_STUDIUM
    [MAINMENU_MYSTERY_MOBILE_STUDIUM] = (const uint8_t[]){
#if SHOW_DEBUG_MENU
        7,
#else
        6,
#endif
        MAINMENUITEM_CONTINUE,
        MAINMENUITEM_NEW_GAME,
        MAINMENUITEM_OPTION,
        MAINMENUITEM_MYSTERY_GIFT,
        MAINMENUITEM_MOBILE,
        MAINMENUITEM_MOBILE_STUDIUM,
#if SHOW_DEBUG_MENU
        MAINMENUITEM_DEBUG_ROOM,
#endif
        0xff,
    },

// MAINMENU_MYSTERY
    [MAINMENU_MYSTERY] = (const uint8_t[]){
#if SHOW_DEBUG_MENU
        5,
#else
        4,
#endif
        MAINMENUITEM_CONTINUE,
        MAINMENUITEM_NEW_GAME,
        MAINMENUITEM_OPTION,
        MAINMENUITEM_MYSTERY_GIFT,
#if SHOW_DEBUG_MENU
        MAINMENUITEM_DEBUG_ROOM,
#endif
        0xff,
    },

// MAINMENU_MYSTERY_STUDIUM
    [MAINMENU_MYSTERY_STUDIUM] = (const uint8_t[]){
#if SHOW_DEBUG_MENU
        6,
#else
        5,
#endif
        MAINMENUITEM_CONTINUE,
        MAINMENUITEM_NEW_GAME,
        MAINMENUITEM_OPTION,
        MAINMENUITEM_MYSTERY_GIFT,
        MAINMENUITEM_MOBILE_STUDIUM,
#if SHOW_DEBUG_MENU
        MAINMENUITEM_DEBUG_ROOM,
#endif
        0xff,
    },

// MAINMENU_STUDIUM
    [MAINMENU_STUDIUM] = (const uint8_t[]){
#if SHOW_DEBUG_MENU
        5,
#else
        4,
#endif
        MAINMENUITEM_CONTINUE,
        MAINMENUITEM_NEW_GAME,
        MAINMENUITEM_OPTION,
        MAINMENUITEM_MOBILE_STUDIUM,
#if SHOW_DEBUG_MENU
        MAINMENUITEM_DEBUG_ROOM,
#endif
        0xff,
    },
};

static uint8_t MainMenu_GetWhichMenu(void){
    // NOP;
    // NOP;
    // NOP;
    // LD_A_addr(wSaveFileExists);
    // AND_A_A;
    // IF_NZ goto next;
    if(!gOptions.saveFileExists) {
        // LD_A(MAINMENU_NEW_GAME);
        // RET;
        return MAINMENU_NEW_GAME;
    }

// next:
    // LDH_A_addr(hCGB);
    // CP_A(TRUE);
    // LD_A(MAINMENU_CONTINUE);
    // RET_NZ ;
    if(hram.hCGB != TRUE)
        return MAINMENU_CONTINUE;
    // LD_A(MBANK(asNumDailyMysteryGiftPartnerIDs));
    // CALL(aOpenSRAM);
    OpenSRAM(MBANK(asNumDailyMysteryGiftPartnerIDs));
    // LD_A_addr(sNumDailyMysteryGiftPartnerIDs);
    uint8_t a = gb_read(sNumDailyMysteryGiftPartnerIDs);
    // CP_A(-1);  // locked?
    // CALL(aCloseSRAM);
    CloseSRAM();
    // IF_NZ goto mystery_gift;
    if(a != 0xff) {
    // mystery_gift:
    // This check makes no difference.
        // LD_A_addr(wStatusFlags);
        // BIT_A(STATUSFLAGS_MAIN_MENU_MOBILE_CHOICES_F);
        // IF_Z goto ok3;
        // goto ok3;
        if(bit_test(gPlayer.statusFlags, STATUSFLAGS_MAIN_MENU_MOBILE_CHOICES_F)) {
            return MAINMENU_MOBILE_MYSTERY;
        }


    // ok3:
        // goto ok4;


    // ok4:
        // LD_A(MAINMENU_MYSTERY);
        // RET;
        return MAINMENU_MYSTERY;
    }
    else {
    // This check makes no difference.
        // LD_A_addr(wStatusFlags);
        // BIT_A(STATUSFLAGS_MAIN_MENU_MOBILE_CHOICES_F);
        // LD_A(MAINMENU_MYSTERY); // MAINMENU_CONTINUE
        // IF_Z goto ok;
        // goto ok;
        if(bit_test(gPlayer.statusFlags, STATUSFLAGS_MAIN_MENU_MOBILE_CHOICES_F)) {
            return MAINMENU_MOBILE;
        }


    // ok:
        // goto ok2;


    // ok2:
        // LD_A(MAINMENU_MYSTERY); // MAINMENU_CONTINUE
        // RET;
        return MAINMENU_CONTINUE;
    }
}

static bool MainMenuJoypadLoop(void){
    // CALL(aSetUpMenu);
    SetUpMenu();

// loop:
    while(1)
    {
        // CALL(aMainMenu_PrintCurrentTimeAndDay);
        MainMenu_PrintCurrentTimeAndDay();
        // LD_A_addr(w2DMenuFlags1);
        // SET_A(5);
        // LD_addr_A(w2DMenuFlags1);
        bit_set(wram->w2DMenuFlags1, 5);
        // CALL(aGetScrollingMenuJoypad);
        GetScrollingMenuJoypad();
        // LD_A_addr(wMenuJoypad);
        // CP_A(B_BUTTON);
        // IF_Z goto b_button;
        if(wram->wMenuJoypad == B_BUTTON) {
        // b_button:
            // SCF;
            // RET;
            return false;
        }
        // CP_A(A_BUTTON);
        // IF_Z goto a_button;
        if(wram->wMenuJoypad == A_BUTTON) {
        // a_button:
            // CALL(aPlayClickSFX);
            // AND_A_A;
            // RET;
            PlayClickSFX();
            return true;
        }
        // goto loop;
    }

}

static void MainMenu_PrintCurrentTimeAndDay_PlaceBox(void) {
// PlaceBox:
    // CALL(aCheckRTCStatus);
    uint8_t a = CheckRTCStatus();
    // AND_A(0b10000000);  // Day count exceeded 16383
    // IF_NZ goto TimeFail;
    if((a & 0b10000000) != 0) {   // Day count exceeded 16383    
    // TimeFail:
        // CALL(aSpeechTextbox);
        // RET;
        return SpeechTextbox();
    }
    // hlcoord(0, 14, wTilemap);
    // LD_B(2);
    // LD_C(18);
    // CALL(aTextbox);
    // RET;
    return Textbox(coord(0, 14, wram->wTilemap), 2, 18);
}

static void MainMenu_PrintCurrentTimeAndDay_PrintDayOfWeek(uint8_t wd, uint8_t* de) {
    static const char* Days[] = {
    // Days:
        "SUN@",
        "MON@",
        "TUES@",
        "WEDNES@",
        "THURS@",
        "FRI@",
        "SATUR@",
    };

// PrintDayOfWeek:
    // PUSH_DE;
    // LD_HL(mMainMenu_PrintCurrentTimeAndDay_Days);
    // LD_A_B;
    // CALL(aGetNthString);
    // LD_D_H;
    // LD_E_L;
    // POP_HL;
    // CALL(aPlaceString);
    struct TextPrintState st = {.hl=de, .de=Utf8ToCrystal(Days[wd])};
    PlaceString(&st, de);
    // LD_H_B;
    // LD_L_C;
    // LD_DE(mMainMenu_PrintCurrentTimeAndDay_Day);
    // CALL(aPlaceString);
    st.hl = st.bc;
    st.de = Utf8ToCrystal("DAY@");
    PlaceString(&st, st.hl);
    // RET;


// Days:
    //db ['"SUN@"'];
    //db ['"MON@"'];
    //db ['"TUES@"'];
    //db ['"WEDNES@"'];
    //db ['"THURS@"'];
    //db ['"FRI@"'];
    //db ['"SATUR@"'];

// Day:
    //db ['"DAY@"'];
}

static void MainMenu_PrintCurrentTimeAndDay_PlaceTime(void) {
// PlaceTime:
    // LD_A_addr(wSaveFileExists);
    // AND_A_A;
    // RET_Z ;
    if(!gOptions.saveFileExists)
        return;
    // CALL(aCheckRTCStatus);
    // AND_A(0x80);
    // JP_NZ (mMainMenu_PrintCurrentTimeAndDay_PrintTimeNotSet);
    if(CheckRTCStatus() & 0x80) {
    // PrintTimeNotSet:
        // hlcoord(1, 14, wTilemap);
        // LD_DE(mMainMenu_PrintCurrentTimeAndDay_TimeNotSetString);
        // CALL(aPlaceString);
        // RET;
        return PlaceStringSimple(Utf8ToCrystal("TIME NOT SET@"), coord(1, 14, wram->wTilemap));


    // TimeNotSetString:
        //db ['"TIME NOT SET@"'];
    }
    // CALL(aUpdateTime);
    UpdateTime();
    // CALL(aGetWeekday);
    // LD_B_A;
    // decoord(1, 15, wTilemap);
    // CALL(aMainMenu_PrintCurrentTimeAndDay_PrintDayOfWeek);
    MainMenu_PrintCurrentTimeAndDay_PrintDayOfWeek(GetWeekday(), coord(1, 15, wram->wTilemap));
    // decoord(4, 16, wTilemap);
    // LDH_A_addr(hHours);
    // LD_C_A;
    // FARCALL(aPrintHour);
    uint8_t* hl = PrintHour(coord(4, 16, wram->wTilemap), hram.hHours);
    // LD_hl(0x9c);
    *(hl++) = CHAR_COLON2;
    // INC_HL;
    // LD_DE(hMinutes);
    // LD_BC((PRINTNUM_LEADINGZEROS | 1 << 8) | 2);
    // CALL(aPrintNum);
    PrintNum(hl, &hram.hMinutes, PRINTNUM_LEADINGZEROS | 1, 2);
    // RET;
    return;


// minString:
//   //  unreferenced
    //db ['"min.@"'];


// MainMenuTimeUnknownText:
//   //  unreferenced
    //text_far ['_MainMenuTimeUnknownText']
    //text_end ['?']
}

static void MainMenu_PrintCurrentTimeAndDay(void){
    // LD_A_addr(wSaveFileExists);
    // AND_A_A;
    // RET_Z ;
    if(!gOptions.saveFileExists)
        return;
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram.hBGMapMode = BGMAPMODE_NONE;
    // CALL(aMainMenu_PrintCurrentTimeAndDay_PlaceBox);
    MainMenu_PrintCurrentTimeAndDay_PlaceBox();
    // LD_HL(wOptions);
    // LD_A_hl;
    // PUSH_AF;
    uint8_t temp = gOptions.options;
    // SET_hl(NO_TEXT_SCROLL);
    bit_set(gOptions.options, NO_TEXT_SCROLL);
    // CALL(aMainMenu_PrintCurrentTimeAndDay_PlaceTime);
    MainMenu_PrintCurrentTimeAndDay_PlaceTime();
    // POP_AF;
    // LD_addr_A(wOptions);
    gOptions.options = temp;
    // LD_A(0x1);
    // LDH_addr_A(hBGMapMode);
    hram.hBGMapMode = BGMAPMODE_UPDATE_TILES;
    // RET;
}

static void ClearTilemapEtc(void){
    // XOR_A_A;
    // LDH_addr_A(hMapAnims);
    hram.hMapAnims = 0;
    // CALL(aClearTilemap);
    ClearTilemap();
    // CALL(aLoadFontsExtra);
    LoadFontsExtra();
    // CALL(aLoadStandardFont);
    LoadStandardFont();
    // CALL(aClearWindowData);
    ClearWindowData();
    // RET;
}

bool MainMenu_NewGame(void){
    // FARCALL(aNewGame);
    NewGame();
    // RET;
    return true;
}

bool MainMenu_Option(void){
    // FARCALL(aOption);
    Option();
    // RET;
    return false;
}

bool MainMenu_Continue(void){
    // FARCALL(aContinue);
    // RET;
    return Continue();
}

bool MainMenu_DebugRoom(void){
    // farcall _DebugRoom
    DebugMenu();
    // ret
    return false;
}

bool MainMenu_MysteryGift(void){
    // FARCALL(aMysteryGift);
    MysteryGift();
    // RET;
    return false;
}
