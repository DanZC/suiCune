#include "../../constants.h"
#include "intro_menu.h"
#include <stdio.h>
#include <string.h>
#include "../../home/audio.h"
#include "../../home/delay.h"
#include "../../home/string.h"
#include "../../home/copy.h"
#include "../../home/copy_name.h"
#include "../../home/fade.h"
#include "../../home/gfx.h"
#include "../../home/text.h"
#include "../../home/pokemon.h"
#include "../../home/joypad.h"
#include "../../home/menu.h"
#include "../../home/sram.h"
#include "../../home/random.h"
#include "../../gfx/misc.h"
#include "../../data/text/common.h"
#include "../../charmap.h"
#include "../gfx/place_graphic.h"
#include "../gfx/player_gfx.h"
#include "../movie/splash.h"
#include "../movie/intro.h"
#include "../movie/title.h"

void Intro_MainMenu() {
    PlayMusic_Conv(MUSIC_NONE);
    // CALL(aDelayFrame);
    DelayFrame();
    // LD_A_E;
    // LD_addr_A(wMapMusic);
    wram->wMapMusic = MUSIC_NONE;
    PlayMusic_Conv(MUSIC_MAIN_MENU);
    FARCALL(aMainMenu);
    JP(mStartTitleScreen);
}

void PrintDayOfWeek(void) {
    PUSH_DE;
    LD_HL(mPrintDayOfWeek_Days);
    LD_A_B;
    CALL(aGetNthString);
    LD_D_H;
    LD_E_L;
    POP_HL;
    CALL(aPlaceString);
    LD_H_B;
    LD_L_C;
    LD_DE(mPrintDayOfWeek_Day);
    CALL(aPlaceString);
    RET;

Day:
    //db ['"DAY@"'];

    return NewGame_ClearTilemapEtc();
}

void PrintDayOfWeek_Conv(tile_t* de, uint8_t b) {
    static const char* days[] = {
        "SUN",
        "MON",
        "TUES",
        "WEDNES",
        "THURS",
        "FRI",
        "SATUR"
    };
    // PUSH_DE;
    // LD_HL(mPrintDayOfWeek_Days);
    // LD_A_B;
    // CALL(aGetNthString);
    // LD_D_H;
    // LD_E_L;
    // POP_HL;
    // CALL(aPlaceString);
    struct TextPrintState st = {.de = U82C(days[b]), .hl = de};
    PlaceString_Conv(&st, st.hl);
    static const char Day[] = "DAY@";
    // LD_H_B;
    // LD_L_C;
    st.hl = st.bc;
    // LD_DE(mPrintDayOfWeek_Day);
    st.de = U82C(Day);
    // CALL(aPlaceString);
    PlaceString_Conv(&st, st.hl);
    // RET;
}

void NewGame_ClearTilemapEtc(void) {
    XOR_A_A;
    LDH_addr_A(hMapAnims);
    CALL(aClearTilemap);
    CALL(aLoadFontsExtra);
    CALL(aLoadStandardFont);
    CALL(aClearWindowData);
    RET;

}

void MysteryGift(void) {
    CALL(aUpdateTime);
    FARCALL(aDoMysteryGiftIfDayHasPassed);
    FARCALL(aDoMysteryGift);
    RET;

}

void Option(void) {
    FARCALL(av_Option);
    RET;

}

void NewGame(void) {
    // XOR_A_A;
    // LD_addr_A(wDebugFlags);
    wram->wDebugFlags = 0;
    CALL(aResetWRAM);
    CALL(aNewGame_ClearTilemapEtc);
    CALL(aAreYouABoyOrAreYouAGirl);
    CALL(aOakSpeech);
    CALL(aInitializeWorld);

    LD_A(LANDMARK_NEW_BARK_TOWN);
    LD_addr_A(wPrevLandmark);

    LD_A(SPAWN_HOME);
    LD_addr_A(wDefaultSpawnpoint);

    LD_A(MAPSETUP_WARP);
    LDH_addr_A(hMapEntryMethod);
    JP(mFinishContinueFunction);

}

void AreYouABoyOrAreYouAGirl(void) {
    FARCALL(aMobile_AlwaysReturnNotCarry);  // mobile
    IF_C goto ok;
    FARCALL(aInitGender);
    RET;


ok:
    LD_C(0);
    FARCALL(aInitMobileProfile);  // mobile
    RET;

}

void DebugRoom(void) {
    //FARCALL(_DebugRoom);
    RET;
}

void ResetWRAM(void) {
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = 0;
    CALL(av_ResetWRAM);
    // RET;
}

void v_ResetWRAM(void) {
    LD_HL(wVirtualOAM);
    LD_BC(wOptions - wVirtualOAM);
    XOR_A_A;
    CALL(aByteFill);

    LD_HL(WRAM1_Begin);
    LD_BC(wGameData - WRAM1_Begin);
    XOR_A_A;
    CALL(aByteFill);

    LD_HL(wGameData);
    LD_BC(wGameDataEnd - wGameData);
    XOR_A_A;
    CALL(aByteFill);

    LDH_A_addr(rLY);
    LDH_addr_A(hUnusedBackup);
    CALL(aDelayFrame);
    LDH_A_addr(hRandomSub);
    LD_addr_A(wPlayerID);

    LDH_A_addr(rLY);
    LDH_addr_A(hUnusedBackup);
    CALL(aDelayFrame);
    LDH_A_addr(hRandomAdd);
    LD_addr_A(wPlayerID + 1);

    CALL(aRandom);
    LD_addr_A(wSecretID);
    CALL(aDelayFrame);
    CALL(aRandom);
    LD_addr_A(wSecretID + 1);

    LD_HL(wPartyCount);
    CALL(av_ResetWRAM_InitList);

    XOR_A_A;
    LD_addr_A(wCurBox);
    LD_addr_A(wSavedAtLeastOnce);

    CALL(aSetDefaultBoxNames);

    LD_A(MBANK(asBoxCount));
    CALL(aOpenSRAM);
    LD_HL(sBoxCount);
    CALL(av_ResetWRAM_InitList);
    CALL(aCloseSRAM);

    LD_HL(wNumItems);
    CALL(av_ResetWRAM_InitList);

    LD_HL(wNumKeyItems);
    CALL(av_ResetWRAM_InitList);

    LD_HL(wNumBalls);
    CALL(av_ResetWRAM_InitList);

    LD_HL(wNumPCItems);
    CALL(av_ResetWRAM_InitList);

    XOR_A_A;
    LD_addr_A(wRoamMon1Species);
    LD_addr_A(wRoamMon2Species);
    LD_addr_A(wRoamMon3Species);
    LD_A(-1);
    LD_addr_A(wRoamMon1MapGroup);
    LD_addr_A(wRoamMon2MapGroup);
    LD_addr_A(wRoamMon3MapGroup);
    LD_addr_A(wRoamMon1MapNumber);
    LD_addr_A(wRoamMon2MapNumber);
    LD_addr_A(wRoamMon3MapNumber);

    LD_A(MBANK(asMysteryGiftItem));  // aka BANK(sMysteryGiftUnlocked)
    CALL(aOpenSRAM);
    LD_HL(sMysteryGiftItem);
    XOR_A_A;
    LD_hli_A;
    //assert ['sMysteryGiftItem + 1 == sMysteryGiftUnlocked'];
    DEC_A;  // -1
    LD_hl_A;
    CALL(aCloseSRAM);

    CALL(aLoadOrRegenerateLuckyIDNumber);
    CALL(aInitializeMagikarpHouse);

    XOR_A_A;
    LD_addr_A(wMonType);

    LD_addr_A(wJohtoBadges);
    LD_addr_A(wKantoBadges);

    LD_addr_A(wCoins);
    LD_addr_A(wCoins + 1);

    if (START_MONEY >= 10000)
        LD_A(HIGH(START_MONEY >> 8));
    else
        LD_addr_A(wMoney);
    LD_A(HIGH(START_MONEY));  // mid
    LD_addr_A(wMoney + 1);
    LD_A(LOW(START_MONEY));
    LD_addr_A(wMoney + 2);

    XOR_A_A;
    LD_addr_A(wWhichMomItem);

    LD_HL(wMomItemTriggerBalance);
    LD_hl(HIGH(MOM_MONEY >> 8));
    INC_HL;
    LD_hl(HIGH(MOM_MONEY));  // mid
    INC_HL;
    LD_hl(LOW(MOM_MONEY));

    CALL(aInitializeNPCNames);

    FARCALL(aInitDecorations);

    FARCALL(aDeletePartyMonMail);

    FARCALL(aDeleteMobileEventIndex);

    CALL(aResetGameTime);
    RET;


InitList:
    //  Loads 0 in the count and -1 in the first item or mon slot.
    XOR_A_A;
    LD_hli_A;
    DEC_A;
    LD_hl_A;
    RET;

}

void SetDefaultBoxNames(void) {
    LD_HL(wBoxNames);
    LD_C(0);

loop:
    PUSH_HL;
    LD_DE(mSetDefaultBoxNames_Box);
    CALL(aCopyName2);
    DEC_HL;
    LD_A_C;
    INC_A;
    CP_A(10);
    IF_C goto less;
    SUB_A(10);
    LD_hl(0xf7);
    INC_HL;


less:
    ADD_A(0xf6);
    LD_hli_A;
    LD_hl(0x50);
    POP_HL;
    LD_DE(9);
    ADD_HL_DE;
    INC_C;
    LD_A_C;
    CP_A(NUM_BOXES);
    IF_C goto loop;
    RET;


Box:
    //db ['"BOX@"'];

    return InitializeMagikarpHouse();
}

void InitializeMagikarpHouse(void) {
    LD_HL(wBestMagikarpLengthFeet);
    LD_A(0x3);
    LD_hli_A;
    LD_A(0x6);
    LD_hli_A;
    LD_DE(mInitializeMagikarpHouse_Ralph);
    CALL(aCopyName2);
    RET;


Ralph:
    //db ['"RALPH@"'];

    return InitializeNPCNames();
}

void InitializeNPCNames(void) {
    LD_HL(mInitializeNPCNames_Rival);
    LD_DE(wRivalName);
    CALL(aInitializeNPCNames_Copy);

    LD_HL(mInitializeNPCNames_Mom);
    LD_DE(wMomsName);
    CALL(aInitializeNPCNames_Copy);

    LD_HL(mInitializeNPCNames_Red);
    LD_DE(wRedsName);
    CALL(aInitializeNPCNames_Copy);

    LD_HL(mInitializeNPCNames_Green);
    LD_DE(wGreensName);


Copy:
    LD_BC(NAME_LENGTH);
    CALL(aCopyBytes);
    RET;


//Rival:
    //  db "???@"

//Red:    db:
    // "RED@"

//Green:
    //  db "GREEN@"

//Mom:
    //    db "MOM@"

}

void InitializeWorld(void) {
    CALL(aShrinkPlayer);
    FARCALL(aSpawnPlayer);
    FARCALL(av_InitializeStartDay);
    RET;

}

void LoadOrRegenerateLuckyIDNumber(void) {
    // LD_A(MBANK(asLuckyIDNumber));
    // CALL(aOpenSRAM);
    OpenSRAM_Conv(MBANK(asLuckyIDNumber));
    // LD_A_addr(wCurDay);
    // INC_A;
    // LD_B_A;
    uint8_t b = wram->wCurDay + 1;
    // LD_A_addr(sLuckyNumberDay);
    // CP_A_B;
    uint16_t id;
    if(gb_read(sLuckyNumberDay) == b) {
        // LD_A_addr(sLuckyIDNumber + 1);
        // LD_C_A;
        // LD_A_addr(sLuckyIDNumber);
        // IF_Z goto skip;
        id = gb_read16(sLuckyNumberDay);
    }
    else {
        // LD_A_B;
        // LD_addr_A(sLuckyNumberDay);
        gb_write(sLuckyNumberDay, b);
        // CALL(aRandom);
        // LD_C_A;
        // CALL(aRandom);
        id = Random_Conv() << 8;
        id |= Random_Conv();
    }

// skip:
    // LD_addr_A(wLuckyIDNumber);
    wram->wLuckyIDNumber = id;
    // LD_addr_A(sLuckyIDNumber);
    // LD_A_C;
    gb_write16(sLuckyIDNumber, id);
    // LD_addr_A(wLuckyIDNumber + 1);
    // LD_addr_A(sLuckyIDNumber + 1);
    // JP(mCloseSRAM);
    return CloseSRAM_Conv();
}

void Continue(void) {
    FARCALL(aTryLoadSaveFile);
    IF_C goto FailToLoad;
    FARCALL(av_LoadData);
    // CALL(aLoadStandardMenuHeader);
    LoadStandardMenuHeader_Conv();
    CALL(aDisplaySaveInfoOnContinue);
    // LD_A(0x1);
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = 0x1;
    // LD_C(20);
    // CALL(aDelayFrames);
    DelayFrames_Conv(20);
    // CALL(aConfirmContinue);
    // IF_NC goto Check1Pass;
    if(ConfirmContinue_Conv())
        goto Check1Pass;
    CALL(aCloseWindow);
    goto FailToLoad;


Check1Pass:
    CALL(aContinue_CheckRTC_RestartClock);
    IF_NC goto Check2Pass;
    CALL(aCloseWindow);
    goto FailToLoad;


Check2Pass:
    LD_A(0x8);
    LD_addr_A(wMusicFade);
    LD_A(LOW(MUSIC_NONE));
    LD_addr_A(wMusicFadeID);
    LD_A(HIGH(MUSIC_NONE));
    LD_addr_A(wMusicFadeID + 1);
    CALL(aClearBGPalettes);
    CALL(aContinue_MobileAdapterMenu);
    CALL(aCloseWindow);
    CALL(aClearTilemap);
    LD_C(20);
    CALL(aDelayFrames);
    FARCALL(aJumpRoamMons);
    FARCALL(aCopyMysteryGiftReceivedDecorationsToPC);
    FARCALL(aClockContinue);
    LD_A_addr(wSpawnAfterChampion);
    CP_A(SPAWN_LANCE);
    IF_Z goto SpawnAfterE4;
    LD_A(MAPSETUP_CONTINUE);
    LDH_addr_A(hMapEntryMethod);
    JP(mFinishContinueFunction);


FailToLoad:
    RET;


SpawnAfterE4:
    LD_A(SPAWN_NEW_BARK);
    LD_addr_A(wDefaultSpawnpoint);
    CALL(aPostCreditsSpawn);
    JP(mFinishContinueFunction);

}

void SpawnAfterRed(void) {
    // LD_A(SPAWN_MT_SILVER);
    // LD_addr_A(wDefaultSpawnpoint);
    wram->wDefaultSpawnpoint = SPAWN_MT_SILVER;

    return PostCreditsSpawn();
}

void PostCreditsSpawn(void) {
    // XOR_A_A;
    // LD_addr_A(wSpawnAfterChampion);
    wram->wSpawnAfterChampion = 0;
    // LD_A(MAPSETUP_WARP);
    // LDH_addr_A(hMapEntryMethod);
    hram->hMapEntryMethod = MAPSETUP_WARP;
    RET;
}

void Continue_MobileAdapterMenu(void) {
    FARCALL(aMobile_AlwaysReturnNotCarry);  // mobile check
    RET_NC;

    //  the rest of this stuff is never reached because
    //  the previous function returns with carry not set
    LD_HL(wd479);
    BIT_hl(1);
    RET_NZ;
    LD_A(5);
    LD_addr_A(wMusicFade);
    LD_A(LOW(MUSIC_MOBILE_ADAPTER_MENU));
    LD_addr_A(wMusicFadeID);
    LD_A(HIGH(MUSIC_MOBILE_ADAPTER_MENU));
    LD_addr_A(wMusicFadeID + 1);
    LD_C(20);
    CALL(aDelayFrames);
    LD_C(0x1);
    FARCALL(aInitMobileProfile);  // mobile
    FARCALL(av_SaveData);
    LD_A(8);
    LD_addr_A(wMusicFade);
    LD_A(LOW(MUSIC_NONE));
    LD_addr_A(wMusicFadeID);
    LD_A(HIGH(MUSIC_NONE));
    LD_addr_A(wMusicFadeID + 1);
    LD_C(35);
    CALL(aDelayFrames);
    RET;

}

void ConfirmContinue(void) {

loop:
    CALL(aDelayFrame);
    CALL(aGetJoypad);
    LD_HL(hJoyPressed);
    BIT_hl(A_BUTTON_F);
    IF_NZ goto PressA;
    BIT_hl(B_BUTTON_F);
    IF_Z goto loop;
    SCF;
    RET;


PressA:
    RET;

}

// Returns true if the player confirmed the continue.
// Returns false if cancelled.
bool ConfirmContinue_Conv(void) {

    do {
    // loop:
        // CALL(aDelayFrame);
        DelayFrame();
        // CALL(aGetJoypad);
        GetJoypad_Conv();
        // LD_HL(hJoyPressed);
        // BIT_hl(A_BUTTON_F);
        // IF_NZ goto PressA;
        if(bit_test(hram->hJoyPressed, A_BUTTON_F))
            return true;
        // BIT_hl(B_BUTTON_F);
        // IF_Z goto loop;
    } while(!bit_test(hram->hJoyPressed, B_BUTTON_F));
    // SCF;
    // RET;
    return false;

// PressA:
    // RET;
}

void Continue_CheckRTC_RestartClock(void) {
    CALL(aCheckRTCStatus);
    AND_A(0b10000000);  // Day count exceeded 16383
    IF_Z goto pass;
    FARCALL(aRestartClock);
    LD_A_C;
    AND_A_A;
    IF_Z goto pass;
    SCF;
    RET;


pass:
    XOR_A_A;
    RET;

}

void FinishContinueFunction(void) {

loop:
    XOR_A_A;
    LD_addr_A(wDontPlayMapMusicOnReload);
    LD_addr_A(wLinkMode);
    LD_HL(wGameTimerPaused);
    SET_hl(GAME_TIMER_PAUSED_F);
    RES_hl(GAME_TIMER_MOBILE_F);
    LD_HL(wEnteredMapFromContinue);
    SET_hl(1);
    FARCALL(aOverworldLoop);
    LD_A_addr(wSpawnAfterChampion);
    CP_A(SPAWN_RED);
    IF_Z goto AfterRed;
    JP(mReset);


AfterRed:
    CALL(aSpawnAfterRed);
    goto loop;
}

void DisplaySaveInfoOnContinue(void) {
    CALL(aCheckRTCStatus);
    AND_A(0b10000000);
    IF_Z goto clock_ok;
    LD_DE((4 << 8) | 8);
    CALL(aDisplayContinueDataWithRTCError);
    RET;


clock_ok:
    LD_DE((4 << 8) | 8);
    CALL(aDisplayNormalContinueData);
    RET;

}

void DisplaySaveInfoOnSave(void) {
    LD_DE((4 << 8) | 0);
    JR(mDisplayNormalContinueData);

}

void DisplayNormalContinueData(void) {
    CALL(aContinue_LoadMenuHeader);
    CALL(aContinue_DisplayBadgesDexPlayerName);
    CALL(aContinue_PrintGameTime);
    CALL(aLoadFontsExtra);
    CALL(aUpdateSprites);
    RET;

}

void DisplayContinueDataWithRTCError(void) {
    CALL(aContinue_LoadMenuHeader);
    CALL(aContinue_DisplayBadgesDexPlayerName);
    CALL(aContinue_UnknownGameTime);
    CALL(aLoadFontsExtra);
    CALL(aUpdateSprites);
    RET;

}

void Continue_LoadMenuHeader(void) {
    XOR_A_A;
    LDH_addr_A(hBGMapMode);
    LD_HL(mContinue_LoadMenuHeader_MenuHeader_Dex);
    LD_A_addr(wStatusFlags);
    BIT_A(STATUSFLAGS_POKEDEX_F);
    IF_NZ goto show_menu;
    LD_HL(mContinue_LoadMenuHeader_MenuHeader_NoDex);


show_menu:
    CALL(av_OffsetMenuHeader);
    CALL(aMenuBox);
    CALL(aPlaceVerticalMenuItems);
    RET;


MenuHeader_Dex:
    //db ['MENU_BACKUP_TILES'];  // flags
    //menu_coords ['0', '0', '15', '9'];
    //dw ['.MenuData_Dex'];
    //db ['1'];  // default option


MenuData_Dex:
    //db ['0'];  // flags
    //db ['4'];  // items
    //db ['"PLAYER@"'];
    //db ['"BADGES@"'];
    //db ['"#DEX@"'];
    //db ['"TIME@"'];


MenuHeader_NoDex:
    //db ['MENU_BACKUP_TILES'];  // flags
    //menu_coords ['0', '0', '15', '9'];
    //dw ['.MenuData_NoDex'];
    //db ['1'];  // default option


MenuData_NoDex:
    //db ['0'];  // flags
    //db ['4'];  // items
    //db ['"PLAYER <PLAYER>@"'];
    //db ['"BADGES@"'];
    //db ['" @"'];
    //db ['"TIME@"'];

    return Continue_DisplayBadgesDexPlayerName();
}

void Continue_DisplayBadgesDexPlayerName(void) {
    CALL(aMenuBoxCoord2Tile);
    PUSH_HL;
    decoord(13, 4, 0);
    ADD_HL_DE;
    CALL(aContinue_DisplayBadgeCount);
    POP_HL;
    PUSH_HL;
    decoord(12, 6, 0);
    ADD_HL_DE;
    CALL(aContinue_DisplayPokedexNumCaught);
    POP_HL;
    PUSH_HL;
    decoord(8, 2, 0);
    ADD_HL_DE;
    LD_DE(mContinue_DisplayBadgesDexPlayerName_Player);
    CALL(aPlaceString);
    POP_HL;
    RET;


Player:
    //db ['"<PLAYER>@"'];

    return Continue_PrintGameTime();
}

void Continue_PrintGameTime(void) {
    decoord(9, 8, 0);
    ADD_HL_DE;
    CALL(aContinue_DisplayGameTime);
    RET;

}

void Continue_UnknownGameTime(void) {
    decoord(9, 8, 0);
    ADD_HL_DE;
    LD_DE(mContinue_UnknownGameTime_three_question_marks);
    CALL(aPlaceString);
    RET;


three_question_marks:
    //db ['" ???@"'];

    return Continue_DisplayBadgeCount();
}

void Continue_DisplayBadgeCount(void) {
    PUSH_HL;
    LD_HL(wJohtoBadges);
    LD_B(2);
    CALL(aCountSetBits);
    POP_HL;
    LD_DE(wNumSetBits);
    LD_BC((1 << 8) | 2);
    JP(mPrintNum);

}

void Continue_DisplayPokedexNumCaught(void) {
    LD_A_addr(wStatusFlags);
    BIT_A(STATUSFLAGS_POKEDEX_F);
    RET_Z;
    PUSH_HL;
    LD_HL(wPokedexCaught);
    if (NUM_POKEMON % 8)
        LD_B(NUM_POKEMON / 8 + 1);
    else
        LD_B(NUM_POKEMON / 8);
    CALL(aCountSetBits);
    POP_HL;
    LD_DE(wNumSetBits);
    LD_BC((1 << 8) | 3);
    JP(mPrintNum);

}

void Continue_DisplayGameTime(void) {
    LD_DE(wGameTimeHours);
    LD_BC((2 << 8) | 3);
    CALL(aPrintNum);
    LD_hl(0x6d);
    INC_HL;
    LD_DE(wGameTimeMinutes);
    LD_BC((PRINTNUM_LEADINGZEROS | 1 << 8) | 2);
    JP(mPrintNum);

}

void OakSpeech(void) {
    FARCALL(aInitClock);
    CALL(aRotateFourPalettesLeft);
    CALL(aClearTilemap);

    LD_DE(MUSIC_ROUTE_30);
    CALL(aPlayMusic);

    CALL(aRotateFourPalettesRight);
    CALL(aRotateThreePalettesRight);
    XOR_A_A;
    LD_addr_A(wCurPartySpecies);
    LD_A(POKEMON_PROF);
    LD_addr_A(wTrainerClass);
    CALL(aIntro_PrepTrainerPic);

    LD_B(SCGB_TRAINER_OR_MON_FRONTPIC_PALS);
    CALL(aGetSGBLayout);
    CALL(aIntro_RotatePalettesLeftFrontpic);

    LD_HL(mOakText1);
    CALL(aPrintText);
    CALL(aRotateThreePalettesRight);
    CALL(aClearTilemap);

    LD_A(WOOPER);
    LD_addr_A(wCurSpecies);
    LD_addr_A(wCurPartySpecies);
    CALL(aGetBaseData);

    hlcoord(6, 4, wTilemap);
    CALL(aPrepMonFrontpic);

    XOR_A_A;
    LD_addr_A(wTempMonDVs);
    LD_addr_A(wTempMonDVs + 1);

    LD_B(SCGB_TRAINER_OR_MON_FRONTPIC_PALS);
    CALL(aGetSGBLayout);
    CALL(aIntro_WipeInFrontpic);

    LD_HL(mOakText2);
    CALL(aPrintText);
    LD_HL(mOakText4);
    CALL(aPrintText);
    CALL(aRotateThreePalettesRight);
    CALL(aClearTilemap);

    XOR_A_A;
    LD_addr_A(wCurPartySpecies);
    LD_A(POKEMON_PROF);
    LD_addr_A(wTrainerClass);
    CALL(aIntro_PrepTrainerPic);

    LD_B(SCGB_TRAINER_OR_MON_FRONTPIC_PALS);
    CALL(aGetSGBLayout);
    CALL(aIntro_RotatePalettesLeftFrontpic);

    LD_HL(mOakText5);
    CALL(aPrintText);
    CALL(aRotateThreePalettesRight);
    CALL(aClearTilemap);

    XOR_A_A;
    LD_addr_A(wCurPartySpecies);
    FARCALL(aDrawIntroPlayerPic);

    LD_B(SCGB_TRAINER_OR_MON_FRONTPIC_PALS);
    CALL(aGetSGBLayout);
    CALL(aIntro_RotatePalettesLeftFrontpic);

    LD_HL(mOakText6);
    CALL(aPrintText);
    CALL(aNamePlayer);
    LD_HL(mOakText7);
    CALL(aPrintText);
    RET;

}

const struct TextCmd OakText1[] = {
    text_far(v_OakText1)
    text_end
};

void OakText2_ASM(struct TextCmdState* state);

const struct TextCmd OakText2[] = {
    text_far(v_OakText2)
    text_asm(OakText2_ASM)
};

void OakText2_ASM(struct TextCmdState* state) {
    // LD_A(WOOPER);
    // CALL(aPlayMonCry);
    PlayMonCry_Conv(WOOPER);
    // CALL(aWaitSFX);
    WaitSFX_Conv();
    // LD_HL(mOakText3);
    // RET;
    state->hl = OakText3;
}

const struct TextCmd OakText3[] = {
    text_far(v_OakText3)
    text_end
};

const struct TextCmd OakText4[] = {
    text_far(v_OakText4)
    text_end
};

const struct TextCmd OakText5[] = {
    text_far(v_OakText5)
    text_end
};

const struct TextCmd OakText6[] = {
    text_far(v_OakText6)
    text_end
};

const struct TextCmd OakText7[] = {
    text_far(v_OakText7)
    text_end
};

void NamePlayer(void) {
// Chris:
    //db ['"CHRIS@@@@@@"'];
    static const char Chris[] = "CHRIS@@@@@@";

// Kris:
    //db ['"KRIS@@@@@@@"'];
    static const char Kris[] = "KRIS@@@@@@@";

    FARCALL(aMovePlayerPicRight);
    FARCALL(aShowPlayerNamingChoices);
    LD_A_addr(wMenuCursorY);
    DEC_A;
    IF_Z goto NewName;
    CALL(aStorePlayerName);
    FARCALL(aApplyMonOrTrainerPals);
    FARCALL(aMovePlayerPicLeft);
    RET;


NewName:
    LD_B(NAME_PLAYER);
    LD_DE(wPlayerName);
    FARCALL(aNamingScreen);

    CALL(aRotateThreePalettesRight);
    CALL(aClearTilemap);

    CALL(aLoadFontsExtra);
    CALL(aWaitBGMap);

    XOR_A_A;
    LD_addr_A(wCurPartySpecies);
    FARCALL(aDrawIntroPlayerPic);

    LD_B(SCGB_TRAINER_OR_MON_FRONTPIC_PALS);
    CALL(aGetSGBLayout);
    CALL(aRotateThreePalettesLeft);

    // LD_HL(wPlayerName);
    // LD_DE(mNamePlayer_Chris);
    // LD_A_addr(wPlayerGender);
    // BIT_A(PLAYERGENDER_FEMALE_F);
    // IF_Z goto Male;
    if(bit_test(wram->wPlayerGender, PLAYERGENDER_FEMALE_F)) {
        InitName_Conv2(wram->wPlayerName, U82C(Kris));
    }
    // LD_DE(mNamePlayer_Kris);

// Male:
    // CALL(aInitName);
    else {
        InitName_Conv2(wram->wPlayerName, U82C(Chris));
    }
    RET;

    // return GSShowPlayerNamingChoices();
}

void GSShowPlayerNamingChoices(void) {
    //  //  unreferenced
    CALL(aLoadMenuHeader);
    CALL(aVerticalMenu);
    LD_A_addr(wMenuCursorY);
    DEC_A;
    CALL(aCopyNameFromMenu);
    CALL(aCloseWindow);
    RET;

}

void StorePlayerName(void) {
    // LD_A(0x50);
    // LD_BC(NAME_LENGTH);
    // LD_HL(wPlayerName);
    // CALL(aByteFill);
    ByteFill_Conv2(wram->wPlayerName, NAME_LENGTH, 0x50);
    // LD_HL(wPlayerName);
    // LD_DE(wStringBuffer2);
    // CALL(aCopyName2);
    CopyName2_Conv2(wram->wPlayerName, wram->wStringBuffer2);
    RET;
}

void ShrinkPlayer(void) {
    PEEK("");
    // LDH_A_addr(hROMBank);
    // PUSH_AF;

    // LD_A(32);  // fade time
    // LD_addr_A(wMusicFade);
    wram->wMusicFade = 32;
    // LD_DE(MUSIC_NONE);
    // LD_A_E;
    // LD_addr_A(wMusicFadeID);
    // LD_A_D;
    // LD_addr_A(wMusicFadeID + 1);
    wram->wMusicFadeID = MUSIC_NONE;

    // LD_DE(SFX_ESCAPE_ROPE);
    // CALL(aPlaySFX);
    PlaySFX_Conv(SFX_ESCAPE_ROPE);
    // POP_AF;
    // RST(aBankswitch);

    // LD_C(8);
    // CALL(aDelayFrames);
    DelayFrames_Conv(8);

    // LD_HL(mShrink1Pic);
    // LD_B(BANK(aShrink1Pic));
    // CALL(aShrinkFrame);
    ShrinkFrame_Conv(Shrink1Pic);

    // LD_C(8);
    // CALL(aDelayFrames);
    DelayFrames_Conv(16);

    // LD_HL(mShrink2Pic);
    // LD_B(BANK(aShrink2Pic));
    // CALL(aShrinkFrame);
    ShrinkFrame_Conv(Shrink2Pic);

    // LD_C(8);
    // CALL(aDelayFrames);
    DelayFrames_Conv(16);

    // hlcoord(6, 5, wTilemap);
    // LD_B(7);
    // LD_C(7);
    // CALL(aClearBox);
    ClearBox_Conv2(coord(6, 5, wram->wTilemap), 7, 7);

    // LD_C(3);
    // CALL(aDelayFrames);
    DelayFrames_Conv(3);

    // CALL(aIntro_PlacePlayerSprite);
    Intro_PlacePlayerSprite_Conv();
    // CALL(aLoadFontsExtra);
    LoadFontsExtra_Conv();

    // LD_C(50);
    // CALL(aDelayFrames);
    DelayFrames_Conv(50);

    // CALL(aRotateThreePalettesRight);
    RotateThreePalettesRight_Conv();
    // CALL(aClearTilemap);
    ClearTilemap_Conv2();
    RET;
}

void Intro_RotatePalettesLeftFrontpic(void) {
    LD_HL(mIntroFadePalettes);
    //LD_B(IntroFadePalettes.End - mIntroFadePalettes);

loop:
    LD_A_hli;
    CALL(aDmgToCgbBGPals);
    LD_C(10);
    CALL(aDelayFrames);
    DEC_B;
    IF_NZ goto loop;
    RET;

}

void IntroFadePalettes(void) {
    //dc ['1', '1', '1', '0']
    //dc ['2', '2', '2', '0']
    //dc ['3', '3', '3', '0']
    //dc ['3', '3', '2', '0']
    //dc ['3', '3', '1', '0']
    //dc ['3', '2', '1', '0']

End:

    return Intro_WipeInFrontpic();
}

void Intro_WipeInFrontpic(void) {
    LD_A(0x77);
    LDH_addr_A(hWX);
    CALL(aDelayFrame);
    LD_A(0b11100100);
    CALL(aDmgToCgbBGPals);

loop:
    CALL(aDelayFrame);
    LDH_A_addr(hWX);
    SUB_A(0x8);
    CP_A(-1);
    RET_Z;
    LDH_addr_A(hWX);
    goto loop;

    return Intro_PrepTrainerPic();
}

void Intro_PrepTrainerPic(void) {
    LD_DE(vTiles2);
    FARCALL(aGetTrainerPic);
    XOR_A_A;
    LDH_addr_A(hGraphicStartTile);
    hlcoord(6, 4, wTilemap);
    LD_BC((7 << 8) | 7);
    PREDEF(pPlaceGraphic);
    RET;

}

void ShrinkFrame(void) {
    LD_DE(vTiles2);
    LD_C(7 * 7);
    PREDEF(pDecompressGet2bpp);
    XOR_A_A;
    LDH_addr_A(hGraphicStartTile);
    hlcoord(6, 4, wTilemap);
    LD_BC((7 << 8) | 7);
    PREDEF(pPlaceGraphic);
    RET;

}

void ShrinkFrame_Conv(const char* path) {
    // LD_DE(vTiles2);
    // LD_C(7 * 7);
    // PREDEF(pDecompressGet2bpp);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles2, path, 0, 7 * 7);
    // XOR_A_A;
    // LDH_addr_A(hGraphicStartTile);
    hram->hGraphicStartTile = 0;
    // hlcoord(6, 4, wTilemap);
    // LD_BC((7 << 8) | 7);
    // PREDEF(pPlaceGraphic);
    PlaceGraphicYStagger_Conv(coord(6, 4, wram->wTilemap), 7, 7);
    // RET;
}

void Intro_PlacePlayerSprite(void){
    FARCALL(aGetPlayerIcon);
    LD_C(12);
    LD_HL(vTiles0);
    CALL(aRequest2bpp);

    LD_HL(wVirtualOAMSprite00);
    LD_DE(mIntro_PlacePlayerSprite_sprites);
    LD_A_de;
    INC_DE;

    LD_C_A;

loop:
    LD_A_de;
    INC_DE;
    LD_hli_A;  // y
    LD_A_de;
    INC_DE;
    LD_hli_A;  // x
    LD_A_de;
    INC_DE;
    LD_hli_A;  // tile id

    LD_B(PAL_OW_RED);
    LD_A_addr(wPlayerGender);
    BIT_A(PLAYERGENDER_FEMALE_F);
    IF_Z goto male;
    LD_B(PAL_OW_BLUE);

male:
    LD_A_B;

    LD_hli_A;  // attributes
    DEC_C;
    IF_NZ goto loop;
    RET;


sprites:
    //db ['4'];
// y pxl, x pxl, tile offset
    //db ['9 * 8 + 4', '9 * 8', '0'];
    //db ['9 * 8 + 4', '10 * 8', '1'];
    //db ['10 * 8 + 4', '9 * 8', '2'];
    //db ['10 * 8 + 4', '10 * 8', '3'];




    return IntroSequence();
}

void Intro_PlacePlayerSprite_Conv(void){
    static const struct {
        int8_t y;
        int8_t x;
        tile_t tile;
    } sprites[] = {
        //db ['4'];
    // y pxl, x pxl, tile offset
        {9 * 8 + 4, 9 * 8, 0},
        {9 * 8 + 4, 10 * 8, 1},
        {10 * 8 + 4, 9 * 8, 2},
        {10 * 8 + 4, 10 * 8, 3},
    };

    // FARCALL(aGetPlayerIcon);
    // LD_C(12);
    // LD_HL(vTiles0);
    // CALL(aRequest2bpp);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles0, GetPlayerIcon_Conv2(), 0, 12);

    // LD_HL(wVirtualOAMSprite00);
    // LD_DE(mIntro_PlacePlayerSprite_sprites);
    // LD_A_de;
    // INC_DE;

    // LD_C_A;
    for(uint8_t i = 0; i < lengthof(sprites); ++i) {
    // loop:
        // LD_A_de;
        // INC_DE;
        // LD_hli_A;  // y
        wram->wVirtualOAMSprite[i].yCoord = sprites[i].y;
        // LD_A_de;
        // INC_DE;
        // LD_hli_A;  // x
        wram->wVirtualOAMSprite[i].xCoord = sprites[i].x;
        // LD_A_de;
        // INC_DE;
        // LD_hli_A;  // tile id
        wram->wVirtualOAMSprite[i].tileID = sprites[i].tile;

        // LD_B(PAL_OW_RED);
        // LD_A_addr(wPlayerGender);
        // BIT_A(PLAYERGENDER_FEMALE_F);
        // IF_Z goto male;
        // LD_B(PAL_OW_BLUE);

    // male:
        // LD_A_B;

        // LD_hli_A;  // attributes
        wram->wVirtualOAMSprite[i].attributes = (bit_test(wram->wPlayerGender, PLAYERGENDER_FEMALE_F))? PAL_OW_BLUE: PAL_OW_RED;
        // DEC_C;
        // IF_NZ goto loop;
    }
    // RET;
}

typedef enum {
    TITLESCREENOPTION_MAIN_MENU,
    TITLESCREENOPTION_DELETE_SAVE_DATA,
    TITLESCREENOPTION_RESTART,
    TITLESCREENOPTION_UNUSED,
    TITLESCREENOPTION_RESET_CLOCK,
    NUM_TITLESCREENOPTIONS
} TitlescreenOption;

void IntroSequence(void){
// Comment the four lines below to remove the copyright splash screen.
    // CALLFAR(aSplashScreen);
    bool skip = SplashScreen();
    // JR_C (mStartTitleScreen);
    if(!skip)
// Comment the line below to remove the intro movie.
        FARCALL(aCrystalIntro);

// fallthrough

    return StartTitleScreen();
}

void StartTitleScreen(void){
    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(MBANK(awLYOverrides));
    LDH_addr_A(rSVBK);

    CALL(aStartTitleScreen_TitleScreen);
    CALL(aDelayFrame);

loop:
    CALL(aRunTitleScreen);
    IF_NC goto loop;

    CALL(aClearSprites);
    CALL(aClearBGPalettes);

    POP_AF;
    LDH_addr_A(rSVBK);

    LD_HL(rLCDC);
    RES_hl(rLCDC_SPRITE_SIZE);  // 8x8
    CALL(aClearScreen);
    CALL(aWaitBGMap2);
    XOR_A_A;
    LDH_addr_A(hLCDCPointer);
    LDH_addr_A(hSCX);
    LDH_addr_A(hSCY);
    LD_A(0x7);
    LDH_addr_A(hWX);
    LD_A(0x90);
    LDH_addr_A(hWY);
    LD_B(SCGB_DIPLOMA);
    CALL(aGetSGBLayout);
    CALL(aUpdateTimePals);
    LD_A_addr(wTitleScreenSelectedOption);
    //CP_A(NUM_TITLESCREENOPTIONS);
    // IF_C goto ok;
    // XOR_A_A;

// ok:
    // LD_E_A;
    // LD_D(0);
    // LD_HL(mStartTitleScreen_dw);
    // ADD_HL_DE;
    // ADD_HL_DE;
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // JP_hl;
    switch(REG_A) {
        default:
        case TITLESCREENOPTION_MAIN_MENU:           return Intro_MainMenu();
        case TITLESCREENOPTION_DELETE_SAVE_DATA:    return DeleteSaveData();
        case TITLESCREENOPTION_RESTART:             return IntroSequence();
        case TITLESCREENOPTION_UNUSED:              return IntroSequence();
        case TITLESCREENOPTION_RESET_CLOCK:         return ResetClock();
    }


dw:
    //dw ['Intro_MainMenu'];
    //dw ['DeleteSaveData'];
    //dw ['IntroSequence'];
    //dw ['IntroSequence'];
    //dw ['ResetClock'];


TitleScreen:
    FARCALL(av_TitleScreen);
    RET;

}

void RunTitleScreen(void){
    LD_A_addr(wJumptableIndex);
    BIT_A(7);
    IF_NZ goto done_title;
    CALL(aTitleScreenScene);
    FARCALL(aSuicuneFrameIterator);
    CALL(aDelayFrame);
    AND_A_A;
    RET;


done_title:
    SCF;
    RET;

}

bool RunTitleScreen_Conv(void){
    // LD_A_addr(wJumptableIndex);
    // BIT_A(7);
    // IF_NZ goto done_title;
    if(bit_test(wram->wJumptableIndex, 7)) {
    // done_title:
        // SCF;
        // RET;
        return true;
    }

    // CALL(aTitleScreenScene);
    TitleScreenScene_Conv(wram->wJumptableIndex);
    // FARCALL(aSuicuneFrameIterator);
    SuicuneFrameIterator_Conv();
    // CALL(aDelayFrame);
    DelayFrame();
    // AND_A_A;
    // RET;
    return false;
}

void UnusedTitlePerspectiveScroll(void){
//  //  unreferenced
//  Similar behavior to Intro_PerspectiveScrollBG.
    LDH_A_addr(hVBlankCounter);
    AND_A(0x7);
    RET_NZ ;
    LD_HL(wLYOverrides + 0x5f);
    LD_A_hl;
    DEC_A;
    LD_BC(2 * SCREEN_WIDTH);
    CALL(aByteFill);
    RET;

}

void TitleScreenScene(void){
    // LD_E_A;
    // LD_D(0);
    // LD_HL(mTitleScreenScene_scenes);
    // ADD_HL_DE;
    // ADD_HL_DE;
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // JP_hl;
// scenes:
    //dw ['TitleScreenEntrance'];
    //dw ['TitleScreenTimer'];
    //dw ['TitleScreenMain'];
    //dw ['TitleScreenEnd'];

    switch(REG_A) {
        default:
        case 0: TitleScreenEntrance_Conv(); break;
        case 1: TitleScreenTimer_Conv(); break;
        case 2: TitleScreenMain_Conv(); break;
        case 3: TitleScreenEnd_Conv(); break;
    }
    // RET;
}

void TitleScreenScene_Conv(uint8_t a){
    // LD_E_A;
    // LD_D(0);
    // LD_HL(mTitleScreenScene_scenes);
    // ADD_HL_DE;
    // ADD_HL_DE;
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // JP_hl;
// scenes:
    //dw ['TitleScreenEntrance'];
    //dw ['TitleScreenTimer'];
    //dw ['TitleScreenMain'];
    //dw ['TitleScreenEnd'];

    switch(a) {
        default:
        case 0: TitleScreenEntrance_Conv(); break;
        case 1: TitleScreenTimer_Conv(); break;
        case 2: TitleScreenMain_Conv(); break;
        case 3: TitleScreenEnd_Conv(); break;
    }
}

void TitleScreenNextScene(void){
//  //  unreferenced
    LD_HL(wJumptableIndex);
    INC_hl;
    RET;

}

void TitleScreenEntrance(void){
//  Animate the logo:
//  Move each line by 4 pixels until our count hits 0.
    LDH_A_addr(hSCX);
    AND_A_A;
    IF_Z goto done;
    SUB_A(4);
    LDH_addr_A(hSCX);

//  Lay out a base (all lines scrolling together).
    LD_E_A;
    LD_HL(wLYOverrides);
    LD_BC(8 * 10);  // logo height
    CALL(aByteFill);

//  Reversed signage for every other line's position.
//  This is responsible for the interlaced effect.
    LD_A_E;
    XOR_A(0xff);
    INC_A;

    LD_B(8 * 10 / 2);  // logo height / 2
    LD_HL(wLYOverrides + 1);

loop:
    LD_hli_A;
    INC_HL;
    DEC_B;
    IF_NZ goto loop;

    FARCALL(aAnimateTitleCrystal);
    RET;


done:
//  Next scene
    LD_HL(wJumptableIndex);
    INC_hl;
    XOR_A_A;
    LDH_addr_A(hLCDCPointer);

//  Play the title screen music.
    LD_DE(MUSIC_TITLE);
    CALL(aPlayMusic);

    LD_A(0x88);
    LDH_addr_A(hWY);
    RET;

}

//  Animate the logo:
//  Move each line by 4 pixels until our count hits 0.
void TitleScreenEntrance_Conv(void){
    // LDH_A_addr(hSCX);
    // AND_A_A;
    // IF_Z goto done;
    if(hram->hSCX != 0) {
        // SUB_A(4);
        // LDH_addr_A(hSCX);
        hram->hSCX -= 4;

    //  Lay out a base (all lines scrolling together).
        // LD_E_A;
        // LD_HL(wLYOverrides);
        // LD_BC(8 * 10);  // logo height
        // CALL(aByteFill);
        ByteFill_Conv2(wram->wLYOverrides, 8 * 10, hram->hSCX);

    //  Reversed signage for every other line's position.
    //  This is responsible for the interlaced effect.
        // LD_A_E;
        // XOR_A(0xff);
        // INC_A;
        uint8_t a = -hram->hSCX;

        // LD_B(8 * 10 / 2);  // logo height / 2
        // LD_HL(wLYOverrides + 1);
        uint8_t* hl = wram->wLYOverrides + 1;

        for(uint8_t b = 0; b < 8 * 10; b += 2) {
        // loop:
            // LD_hli_A;
            hl[b] = a;
            // INC_HL;
            // DEC_B;
            // IF_NZ goto loop;
        }

        // FARCALL(aAnimateTitleCrystal);
        AnimateTitleCrystal_Conv();
        // RET;
        return;
    }

// done:
//  Next scene
    // LD_HL(wJumptableIndex);
    // INC_hl;
    wram->wJumptableIndex++;
    // XOR_A_A;
    // LDH_addr_A(hLCDCPointer);
    hram->hLCDCPointer = 0;

//  Play the title screen music.
    // LD_DE(MUSIC_TITLE);
    // CALL(aPlayMusic);
    PlayMusic_Conv(MUSIC_TITLE);

    // LD_A(0x88);
    // LDH_addr_A(hWY);
    hram->hWY = 0x88;
    // RET;
}

void TitleScreenTimer(void){
//  Next scene
    LD_HL(wJumptableIndex);
    INC_hl;

//  Start a timer
    LD_HL(wTitleScreenTimer);
    LD_DE(73 * 60 + 36);
    LD_hl_E;
    INC_HL;
    LD_hl_D;
    RET;

}

void TitleScreenTimer_Conv(void){
//  Next scene
    // LD_HL(wJumptableIndex);
    // INC_hl;
    wram->wJumptableIndex++;

//  Start a timer
    // LD_HL(wTitleScreenTimer);
    // LD_DE(73 * 60 + 36);
    // LD_hl_E;
    // INC_HL;
    // LD_hl_D;
    // RET;
    wram->wTitleScreenTimer = 73 * 60 + 36;
}

void TitleScreenMain(void) {
    //  Run the timer down.
    LD_HL(wTitleScreenTimer);
    LD_E_hl;
    INC_HL;
    LD_D_hl;
    LD_A_E;
    OR_A_D;
    IF_Z goto end;

    DEC_DE;
    LD_hl_D;
    DEC_HL;
    LD_hl_E;

    //  Save data can be deleted by pressing Up + B + Select.
    CALL(aGetJoypad);
    LD_HL(hJoyDown);
    LD_A_hl;
    AND_A(D_UP + B_BUTTON + SELECT);
    CP_A(D_UP + B_BUTTON + SELECT);
    IF_Z goto delete_save_data;

    //  To bring up the clock reset dialog:

    //  Hold Down + B + Select to initiate the sequence.
    LDH_A_addr(hClockResetTrigger);
    CP_A(0x34);
    IF_Z goto check_clock_reset;

    LD_A_hl;
    AND_A(D_DOWN + B_BUTTON + SELECT);
    CP_A(D_DOWN + B_BUTTON + SELECT);
    IF_NZ goto check_start;

    LD_A(0x34);
    LDH_addr_A(hClockResetTrigger);
    goto check_start;

    //  Keep Select pressed, and hold Left + Up.
    //  Then let go of Select.

check_clock_reset:
    BIT_hl(SELECT_F);
    IF_NZ goto check_start;

    XOR_A_A;
    LDH_addr_A(hClockResetTrigger);

    LD_A_hl;
    AND_A(D_LEFT + D_UP);
    CP_A(D_LEFT + D_UP);
    IF_Z goto reset_clock;

    //  Press Start or A to start the game.

check_start:
    LD_A_hl;
    AND_A(START | A_BUTTON);
    IF_NZ goto incave;
    RET;


incave:
    LD_A(TITLESCREENOPTION_MAIN_MENU);
    goto done;


delete_save_data:
    LD_A(TITLESCREENOPTION_DELETE_SAVE_DATA);


done:
    LD_addr_A(wTitleScreenSelectedOption);

    //  Return to the intro sequence.
    LD_HL(wJumptableIndex);
    SET_hl(7);
    RET;


end:
    //  Next scene
    LD_HL(wJumptableIndex);
    INC_hl;

    //  Fade out the title screen music
    XOR_A_A;  // MUSIC_NONE
    LD_addr_A(wMusicFadeID);
    LD_addr_A(wMusicFadeID + 1);
    LD_HL(wMusicFade);
    LD_hl(8);  // 1 second

    LD_HL(wTitleScreenTimer);
    INC_hl;
    RET;


reset_clock:
    LD_A(TITLESCREENOPTION_RESET_CLOCK);
    LD_addr_A(wTitleScreenSelectedOption);

    //  Return to the intro sequence.
    LD_HL(wJumptableIndex);
    SET_hl(7);
    RET;

}

void TitleScreenMain_Conv(void) {
    //  Run the timer down.
    // LD_HL(wTitleScreenTimer);
    // LD_E_hl;
    // INC_HL;
    // LD_D_hl;
    // LD_A_E;
    // OR_A_D;
    // IF_Z goto end;
    if(wram->wTitleScreenTimer != 0) {
        // DEC_DE;
        // LD_hl_D;
        // DEC_HL;
        // LD_hl_E;
        wram->wTitleScreenTimer--;

        //  Save data can be deleted by pressing Up + B + Select.
        // CALL(aGetJoypad);
        GetJoypad_Conv();
        // LD_HL(hJoyDown);
        // LD_A_hl;
        // AND_A(D_UP + B_BUTTON + SELECT);
        // CP_A(D_UP + B_BUTTON + SELECT);
        // IF_Z goto delete_save_data;
        if((hram->hJoyDown & (D_UP + B_BUTTON + SELECT)) == (D_UP + B_BUTTON + SELECT)) {
        // delete_save_data:
            // LD_A(TITLESCREENOPTION_DELETE_SAVE_DATA);
            wram->wTitleScreenSelectedOption = TITLESCREENOPTION_DELETE_SAVE_DATA;
        }
        else {
            //  To bring up the clock reset dialog:

            //  Hold Down + B + Select to initiate the sequence.
            // LDH_A_addr(hClockResetTrigger);
            // CP_A(0x34);
            // IF_Z goto check_clock_reset;
            if(hram->hClockResetTrigger == 0x34) {
            //  Keep Select pressed, and hold Left + Up.
            //  Then let go of Select.
            // check_clock_reset:
                // BIT_hl(SELECT_F);
                // IF_NZ goto check_start;
                if(!bit_test(hram->hJoyDown, SELECT_F)) {
                    // XOR_A_A;
                    // LDH_addr_A(hClockResetTrigger);
                    hram->hClockResetTrigger = 0;

                    // LD_A_hl;
                    // AND_A(D_LEFT + D_UP);
                    // CP_A(D_LEFT + D_UP);
                    // IF_Z goto reset_clock;
                    if((hram->hJoyDown & (D_LEFT + D_UP)) == (D_LEFT + D_UP)) {
                    // reset_clock:
                        // LD_A(TITLESCREENOPTION_RESET_CLOCK);
                        // LD_addr_A(wTitleScreenSelectedOption);
                        wram->wTitleScreenSelectedOption = TITLESCREENOPTION_RESET_CLOCK;

                        //  Return to the intro sequence.
                        // LD_HL(wJumptableIndex);
                        // SET_hl(7);
                        // RET;
                        bit_set(wram->wJumptableIndex, 7);
                        return;
                    }
                }
            }

            // LD_A_hl;
            // AND_A(D_DOWN + B_BUTTON + SELECT);
            // CP_A(D_DOWN + B_BUTTON + SELECT);
            // IF_NZ goto check_start;
            else if((hram->hJoyDown & (D_DOWN + B_BUTTON + SELECT)) == (D_DOWN + B_BUTTON + SELECT)) {
                // LD_A(0x34);
                // LDH_addr_A(hClockResetTrigger);
                hram->hClockResetTrigger = 0x34;
                // goto check_start;
            }

            //  Press Start or A to start the game.

        // check_start:
            // LD_A_hl;
            // AND_A(START | A_BUTTON);
            // IF_NZ goto incave;
            if(hram->hJoyDown & (START | A_BUTTON)) {
            // incave:
                // LD_A(TITLESCREENOPTION_MAIN_MENU);
                // goto done;
                wram->wTitleScreenSelectedOption = TITLESCREENOPTION_MAIN_MENU;
            }
            else {
                // RET;
                return;
            }
        }

    // done:
        // LD_addr_A(wTitleScreenSelectedOption);

        //  Return to the intro sequence.
        // LD_HL(wJumptableIndex);
        // SET_hl(7);
        // RET;
        bit_set(wram->wJumptableIndex, 7);
        return;
    }

// end:
    //  Next scene
    // LD_HL(wJumptableIndex);
    // INC_hl;
    wram->wJumptableIndex++;

    //  Fade out the title screen music
    // XOR_A_A;  // MUSIC_NONE
    // LD_addr_A(wMusicFadeID);
    // LD_addr_A(wMusicFadeID + 1);
    wram->wMusicFadeID = MUSIC_NONE;
    // LD_HL(wMusicFade);
    // LD_hl(8);  // 1 second
    wram->wMusicFade = 8;

    // LD_HL(wTitleScreenTimer);
    // INC_hl;
    // RET;
    wram->wTitleScreenTimer++;
}

void TitleScreenEnd(void) {
    //  Wait until the music is done fading.

    LD_HL(wTitleScreenTimer);
    INC_hl;

    LD_A_addr(wMusicFade);
    AND_A_A;
    RET_NZ;

    //LD_A(TITLESCREENOPTION_RESTART);
    LD_addr_A(wTitleScreenSelectedOption);

    //  Back to the intro.
    LD_HL(wJumptableIndex);
    SET_hl(7);
    RET;

}

void TitleScreenEnd_Conv(void) {
    //  Wait until the music is done fading.

    // LD_HL(wTitleScreenTimer);
    // INC_hl;
    wram->wTitleScreenTimer++;

    // LD_A_addr(wMusicFade);
    // AND_A_A;
    // RET_NZ;
    if(wram->wMusicFade != 0)
        return;

    //LD_A(TITLESCREENOPTION_RESTART);
    // LD_addr_A(wTitleScreenSelectedOption);
    wram->wTitleScreenSelectedOption = TITLESCREENOPTION_RESTART;

    //  Back to the intro.
    // LD_HL(wJumptableIndex);
    // SET_hl(7);
    bit_set(wram->wJumptableIndex, 7);
    // RET;
}

void DeleteSaveData(void) {
    FARCALL(av_DeleteSaveData);
    JP(mInit);

}

void ResetClock(void) {
    FARCALL(av_ResetClock);
    JP(mInit);

}

#ifdef _DEBUG
void DebugMenu(void) {
    FARCALL(av_ResetClock);
    JP(mInit);

}
#endif

void UpdateTitleTrailSprite(void) {
    //  //  unreferenced
    // If bit 0 or 1 of [wTitleScreenTimer] is set, we don't need to be here.
    LD_A_addr(wTitleScreenTimer);
    AND_A(0b00000011);
    RET_NZ;
    LD_BC(wSpriteAnim10);
    LD_HL(SPRITEANIMSTRUCT_FRAME);
    ADD_HL_BC;
    LD_L_hl;
    LD_H(0);
    ADD_HL_HL;
    ADD_HL_HL;
    LD_DE(mUpdateTitleTrailSprite_TitleTrailCoords);
    ADD_HL_DE;
    // If bit 2 of [wTitleScreenTimer] is set, get the second coords// else, get the first coords
    LD_A_addr(wTitleScreenTimer);
    AND_A(0b00000100);
    SRL_A;
    SRL_A;
    LD_E_A;
    LD_D(0);
    ADD_HL_DE;
    ADD_HL_DE;
    LD_A_hli;
    AND_A_A;
    RET_Z;
    LD_E_A;
    LD_D_hl;
    LD_A(SPRITE_ANIM_INDEX_GS_TITLE_TRAIL);
    CALL(aInitSpriteAnimStruct);
    RET;


// TitleTrailCoords:
    // trail_coords: MACRO
    // rept _NARG / 2
    // _dx = 4
    // if \1 == 0 && \2 == 0
    // _dx = 0
    // endc
    //     dbpixel \1, \2, _dx, 0
    //     shift 2
    // endr
    // ENDM
    // frame 0 y, x// frame 1 y, x
        //trail_coords ['11', '10', '0', '0']
        //trail_coords ['11', '13', '11', '11']
        //trail_coords ['11', '13', '11', '15']
        //trail_coords ['11', '17', '11', '15']
        //trail_coords ['0', '0', '11', '15']
        //trail_coords ['0', '0', '11', '11']
}

void Copyright(void) {
    // CALL(aClearTilemap);
    ClearTilemap_Conv2();
    // CALL(aLoadFontsExtra);
    LoadFontsExtra_Conv();
    // LD_DE(mCopyrightGFX);
    // LD_HL(vTiles2 + LEN_2BPP_TILE * 0x60);
    // LD_BC((BANK(aCopyrightGFX) << 8) | 29);
    // CALL(aRequest2bpp);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles2 + LEN_2BPP_TILE * 0x60, CopyrightGFX, 0, 29);
    // hlcoord(2, 7, wTilemap);
    // LD_DE(mCopyrightString);
    // JP(mPlaceString);
    PlaceStringSimple(CopyrightString, coord(2, 7, wram->wTilemap));
}

// Crystal encoded string.
uint8_t CopyrightString[] = {
    // �1995-2001 Nintendo
        0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66,
        0x67, 0x68, 0x69, 0x6a, 0x6b, 0x6c,

    // �1995-2001 Creatures inc.
        CHAR_NEXT, 0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66,
        0x6d, 0x6e, 0x6f, 0x70, 0x71, 0x72, 0x7a, 0x7b, 0x7c,

    // �1995-2001 GAME FREAK inc.
        CHAR_NEXT, 0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66,
        0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7a, 0x7b, 0x7c,

        //db ['"@"'];
        CHAR_TERM,
};

void GameInit(void) {
    FARCALL(aTryLoadSaveData);
    CALL(aClearWindowData);
    CALL(aClearBGPalettes);
    CALL(aClearTilemap);
    LD_A(HIGH(vBGMap0));
    LDH_addr_A(hBGMapAddress + 1);
    XOR_A_A;  // LOW(vBGMap0)
    LDH_addr_A(hBGMapAddress);
    LDH_addr_A(hJoyDown);
    LDH_addr_A(hSCX);
    LDH_addr_A(hSCY);
    LD_A(0x90);
    LDH_addr_A(hWY);
    CALL(aWaitBGMap);
    JP(mIntroSequence);

}
