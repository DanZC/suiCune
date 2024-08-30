#include "../../constants.h"
#include "intro_menu.h"
#include "options_menu.h"
#include "naming_screen.h"
#include "init_gender.h"
#include "delete_save.h"
#include "main_menu.h"
#include "save.h"
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
#include "../../home/tilemap.h"
#include "../../home/palettes.h"
#include "../../home/time.h"
#include "../../home/time_palettes.h"
#include "../../home/clear_sprites.h"
#include "../../home/game_time.h"
#include "../../home/menu.h"
#include "../../home/sram.h"
#include "../../home/random.h"
#include "../../home/pokedex_flags.h"
#include "../../home/print_text.h"
#include "../../home/map_objects.h"
#include "../../mobile/mobile_41.h"
#include "../../gfx/misc.h"
#include "../../data/text/common.h"
#include "../../charmap.h"
#include "../gfx/place_graphic.h"
#include "../gfx/player_gfx.h"
#include "../gfx/load_pics.h"
#include "../gfx/color.h"
#include "../overworld/player_object.h"
#include "../overworld/time.h"
#include "../overworld/events.h"
#include "../overworld/wildmons.h"
#include "../overworld/decorations.h"
#include "../link/mystery_gift.h"
#include "../rtc/timeset.h"
#include "../rtc/reset_password.h"
#include "../rtc/rtc.h"
#include "../rtc/restart_clock.h"
#include "../pokemon/mail.h"
#include "../movie/splash.h"
#include "../movie/intro.h"
#include "../movie/title.h"
#include "../../util/intro_jumptable.h"

void Intro_MainMenu() {
    PlayMusic_Conv(MUSIC_NONE);
    // CALL(aDelayFrame);
    DelayFrame();
    // LD_A_E;
    // LD_addr_A(wMapMusic);
    wram->wMapMusic = MUSIC_NONE;
    PlayMusic_Conv(MUSIC_MAIN_MENU);
    // FARCALL(aMainMenu);
    MainMenu();
    // JP(mStartTitleScreen);
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
    // XOR_A_A;
    // LDH_addr_A(hMapAnims);
    hram->hMapAnims = 0x0;
    // CALL(aClearTilemap);
    ClearTilemap_Conv2();
    // CALL(aLoadFontsExtra);
    LoadFontsExtra_Conv();
    // CALL(aLoadStandardFont);
    LoadStandardFont_Conv();
    // CALL(aClearWindowData);
    ClearWindowData_Conv2();
    // RET;

}

void MysteryGift(void) {
    // CALL(aUpdateTime);
    UpdateTime_Conv();
    // FARCALL(aDoMysteryGiftIfDayHasPassed);
    DoMysteryGiftIfDayHasPassed();
    // FARCALL(aDoMysteryGift);
    DoMysteryGift();
    // RET;
}

void Option(void) {
    FARCALL(av_Option);
    RET;

}

void Option_Conv(void) {
    // FARCALL(av_Option);
    // RET;
    return v_Option();
}

void NewGame(void) {
    // XOR_A_A;
    // LD_addr_A(wDebugFlags);
    wram->wDebugFlags = 0;
    // CALL(aResetWRAM);
    ResetWRAM();
    // CALL(aNewGame_ClearTilemapEtc);
    NewGame_ClearTilemapEtc();
    // CALL(aAreYouABoyOrAreYouAGirl);
    AreYouABoyOrAreYouAGirl();
    // CALL(aOakSpeech);
    OakSpeech();
    // CALL(aInitializeWorld);
    InitializeWorld();

    // LD_A(LANDMARK_NEW_BARK_TOWN);
    // LD_addr_A(wPrevLandmark);
    wram->wPrevLandmark = LANDMARK_NEW_BARK_TOWN;

    // LD_A(SPAWN_HOME);
    // LD_addr_A(wDefaultSpawnpoint);
    wram->wDefaultSpawnpoint = SPAWN_HOME;

    // LD_A(MAPSETUP_WARP);
    // LDH_addr_A(hMapEntryMethod);
    hram->hMapEntryMethod = MAPSETUP_WARP;
    // JP(mFinishContinueFunction);
    return Intro_SetJumptableIndex(INTRO_CONTINUE);
}

void AreYouABoyOrAreYouAGirl(void) {
    // FARCALL(aMobile_AlwaysReturnNotCarry);  // mobile
    u8_flag_s res = Mobile_AlwaysReturnNotCarry();
    // IF_C goto ok;
    if(!res.flag){
        // FARCALL(aInitGender);
        InitGender();
        // RET;
        return;
    }

// ok:
    // LD_C(0);
    struct cpu_registers_s reg = {.c = 0};
    // FARCALL(aInitMobileProfile);  // mobile
    SafeCallGB(aInitMobileProfile, &reg);
    // RET;
}

void DebugRoom(void) {
    //FARCALL(_DebugRoom);
    RET;
}

void ResetWRAM(void) {
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = 0;
    // CALL(av_ResetWRAM);
    v_ResetWRAM();
    // RET;
}

//  Loads 0 in the count and -1 in the first mon slot.
static void v_ResetWRAM_InitMonList(uint8_t* hl, species_t* sp){
    // XOR_A_A;
    // LD_hli_A;
    *hl = 0;
    // DEC_A;
    // LD_hl_A;
    *sp = (species_t)-1;
    // RET;
}

//  Loads 0 in the count and -1 in the first item slot.
static void v_ResetWRAM_InitItemList(item_pocket_s* hl){
    // XOR_A_A;
    // LD_hli_A;
    hl->count = 0;
    // DEC_A;
    // LD_hl_A;
    hl->pocket[0].item = (item_t)-1;
    // RET;
}

void v_ResetWRAM(void) {
    // LD_HL(wVirtualOAM);
    // LD_BC(wOptions - wVirtualOAM);
    // XOR_A_A;
    // CALL(aByteFill);
    ByteFill_Conv(wVirtualOAM, wOptions - wVirtualOAM, 0);

    // LD_HL(WRAM1_Begin);
    // LD_BC(wGameData - WRAM1_Begin);
    // XOR_A_A;
    // CALL(aByteFill);
    ByteFill_Conv(WRAM1_Begin, wGameData - WRAM1_Begin, 0);

    // LD_HL(wGameData);
    // LD_BC(wGameDataEnd - wGameData);
    // XOR_A_A;
    // CALL(aByteFill);
    ByteFill_Conv(wGameData, wGameDataEnd - wGameData, 0);

    // LDH_A_addr(rLY);
    // LDH_addr_A(hUnusedBackup);
    // CALL(aDelayFrame);
    DelayFrame();
    // LDH_A_addr(hRandomSub);
    // LD_addr_A(wPlayerID);
    uint8_t pid_lo = hram->hRandomSub;

    // LDH_A_addr(rLY);
    // LDH_addr_A(hUnusedBackup);
    // CALL(aDelayFrame);
    DelayFrame();
    // LDH_A_addr(hRandomAdd);
    // LD_addr_A(wPlayerID + 1);
    uint8_t pid_hi = hram->hRandomAdd;
    wram->wPlayerID = (pid_hi << 8) | pid_lo;

    // CALL(aRandom);
    // LD_addr_A(wSecretID);
    // CALL(aDelayFrame);
    // CALL(aRandom);
    // LD_addr_A(wSecretID + 1);
    uint8_t sid_lo = Random_Conv();
    DelayFrame();
    uint8_t sid_hi = Random_Conv();
    wram->wSecretID = (sid_hi << 8) | sid_lo;

    // LD_HL(wPartyCount);
    // CALL(av_ResetWRAM_InitList);
    v_ResetWRAM_InitMonList(&wram->wPartyCount, wram->wPartySpecies);

    // XOR_A_A;
    // LD_addr_A(wCurBox);
    wram->wCurBox = 0;
    // LD_addr_A(wSavedAtLeastOnce);
    wram->wSavedAtLeastOnce = FALSE;

    // CALL(aSetDefaultBoxNames);
    SetDefaultBoxNames();

    // LD_A(MBANK(asBoxCount));
    // CALL(aOpenSRAM);
    OpenSRAM_Conv(MBANK(asBoxCount));
    // LD_HL(sBoxCount);
    // CALL(av_ResetWRAM_InitList);
    v_ResetWRAM_InitMonList((uint8_t*)GBToRAMAddr(sBoxCount), (species_t*)GBToRAMAddr(sBoxSpecies));
    // CALL(aCloseSRAM);
    CloseSRAM_Conv();

    // LD_HL(wNumItems);
    // CALL(av_ResetWRAM_InitList);
    v_ResetWRAM_InitItemList((item_pocket_s*)&wram->wNumItems);

    // LD_HL(wNumKeyItems);
    // CALL(av_ResetWRAM_InitList);
    v_ResetWRAM_InitItemList((item_pocket_s*)&wram->wNumKeyItems);

    // LD_HL(wNumBalls);
    // CALL(av_ResetWRAM_InitList);
    v_ResetWRAM_InitItemList((item_pocket_s*)&wram->wNumBalls);

    // LD_HL(wNumPCItems);
    // CALL(av_ResetWRAM_InitList);
    v_ResetWRAM_InitItemList((item_pocket_s*)&wram->wNumPCItems);

    // XOR_A_A;
    // LD_addr_A(wRoamMon1Species);
    wram->wRoamMon1.species = 0;
    // LD_addr_A(wRoamMon2Species);
    wram->wRoamMon2.species = 0;
    // LD_addr_A(wRoamMon3Species);
    wram->wRoamMon3.species = 0;
    // LD_A(-1);
    // LD_addr_A(wRoamMon1MapGroup);
    // LD_addr_A(wRoamMon2MapGroup);
    // LD_addr_A(wRoamMon3MapGroup);
    // LD_addr_A(wRoamMon1MapNumber);
    // LD_addr_A(wRoamMon2MapNumber);
    // LD_addr_A(wRoamMon3MapNumber);
    wram->wRoamMon1.mapId = (struct MapId){0xff, 0xff};
    wram->wRoamMon2.mapId = (struct MapId){0xff, 0xff};
    wram->wRoamMon3.mapId = (struct MapId){0xff, 0xff};

    // LD_A(MBANK(asMysteryGiftItem));  // aka BANK(sMysteryGiftUnlocked)
    // CALL(aOpenSRAM);
    OpenSRAM_Conv(MBANK(asMysteryGiftItem));
    // LD_HL(sMysteryGiftItem);
    uint8_t* hl = GBToRAMAddr(sMysteryGiftItem);
    // XOR_A_A;
    // LD_hli_A;
    hl[0] = NO_ITEM;
    //assert ['sMysteryGiftItem + 1 == sMysteryGiftUnlocked'];
    // DEC_A;  // -1
    // LD_hl_A;
    hl[1] = (uint8_t)-1;
    // CALL(aCloseSRAM);
    CloseSRAM_Conv();

    // CALL(aLoadOrRegenerateLuckyIDNumber);
    LoadOrRegenerateLuckyIDNumber();
    // CALL(aInitializeMagikarpHouse);
    InitializeMagikarpHouse();

    // XOR_A_A;
    // LD_addr_A(wMonType);
    wram->wMonType = 0x0;

    // LD_addr_A(wJohtoBadges);
    wram->wJohtoBadges[0] = 0;
    // LD_addr_A(wKantoBadges);
    wram->wKantoBadges[0] = 0;

    // LD_addr_A(wCoins);
    // LD_addr_A(wCoins + 1);
    wram->wCoins = NativeToBigEndian16(0);

    // if (START_MONEY >= 10000)
    //     LD_A(HIGH(START_MONEY >> 8));
    // else
    //     LD_addr_A(wMoney);
    wram->wMoney[0] = (START_MONEY >= 10000)? HIGH(START_MONEY >> 8): 0x0;
    // LD_A(HIGH(START_MONEY));  // mid
    // LD_addr_A(wMoney + 1);
    wram->wMoney[1] = HIGH(START_MONEY);
    // LD_A(LOW(START_MONEY));
    // LD_addr_A(wMoney + 2);
    wram->wMoney[2] = LOW(START_MONEY);

    // XOR_A_A;
    // LD_addr_A(wWhichMomItem);
    wram->wWhichMomItem = NO_ITEM;

    // LD_HL(wMomItemTriggerBalance);
    // LD_hl(HIGH(MOM_MONEY >> 8));
    wram->wMomItemTriggerBalance[0] = HIGH(MOM_MONEY >> 8);
    // INC_HL;
    // LD_hl(HIGH(MOM_MONEY));  // mid
    wram->wMomItemTriggerBalance[1] = HIGH(MOM_MONEY);
    // INC_HL;
    // LD_hl(LOW(MOM_MONEY));
    wram->wMomItemTriggerBalance[2] = LOW(MOM_MONEY);

    // CALL(aInitializeNPCNames);
    InitializeNPCNames();

    // FARCALL(aInitDecorations);
    InitDecorations();

    // FARCALL(aDeletePartyMonMail);
    DeletePartyMonMail();

    // FARCALL(aDeleteMobileEventIndex);
    DeleteMobileEventIndex();

    // CALL(aResetGameTime);
    ResetGameTime_Conv();
    // RET;
}

void SetDefaultBoxNames(void) {
    // LD_HL(wBoxNames);
    uint8_t* hl = wram->wBoxNames;
    // LD_C(0);

    for(uint8_t c = 0; c < NUM_BOXES; c++){
    // loop:
        // PUSH_HL;
        uint8_t* hl2 = hl;
        // LD_DE(mSetDefaultBoxNames_Box);
        // CALL(aCopyName2);
        hl2 = CopyName2_Conv2(hl2, U82C("BOX@"));
        // DEC_HL;
        --hl2;
        // LD_A_C;
        // INC_A;
        uint8_t a = c + 1;
        // CP_A(10);
        // IF_C goto less;
        if(a >= 10){
            // SUB_A(10);
            a -= 10;
            // LD_hl(0xf7);
            // INC_HL;
            *(hl2++) = 0xf7;
        }

    // less:
        // ADD_A(0xf6);
        // LD_hli_A;
        *(hl2++) = 0xf6 + a;
        // LD_hl(0x50);
        *hl2 = 0x50;
        // POP_HL;
        // LD_DE(9);
        // ADD_HL_DE;
        hl += 9;
        // INC_C;
        // LD_A_C;
        // CP_A(NUM_BOXES);
        // IF_C goto loop;
    }
    // RET;

// Box:
    //db ['"BOX@"'];
}

void InitializeMagikarpHouse(void) {
    // LD_HL(wBestMagikarpLengthFeet);
    // LD_A(0x3);
    // LD_hli_A;
    wram->wBestMagikarpLengthFeet = 0x3;
    // LD_A(0x6);
    // LD_hli_A;
    wram->wBestMagikarpLengthInches = 0x6;
    // LD_DE(mInitializeMagikarpHouse_Ralph);
    // CALL(aCopyName2);
    CopyName2_Conv2(wram->wMagikarpRecordHoldersName, U82C("RALPH@"));
    // RET;

// Ralph:
    //db ['"RALPH@"'];
}

void InitializeNPCNames(void) {
    // LD_HL(mInitializeNPCNames_Rival);
    // LD_DE(wRivalName);
    // CALL(aInitializeNPCNames_Copy);
    U82CB(wram->wRivalName, NAME_LENGTH, "???@");

    // LD_HL(mInitializeNPCNames_Mom);
    // LD_DE(wMomsName);
    // CALL(aInitializeNPCNames_Copy);
    U82CB(wram->wMomsName, NAME_LENGTH, "MOM@");

    // LD_HL(mInitializeNPCNames_Red);
    // LD_DE(wRedsName);
    // CALL(aInitializeNPCNames_Copy);
    U82CB(wram->wRedsName, NAME_LENGTH, "RED@");

    // LD_HL(mInitializeNPCNames_Green);
    // LD_DE(wGreensName);
    U82CB(wram->wGreensName, NAME_LENGTH, "GREEN@");

// Copy:
    // LD_BC(NAME_LENGTH);
    // CALL(aCopyBytes);
    // RET;


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
    // CALL(aShrinkPlayer);
    ShrinkPlayer();
    // FARCALL(aSpawnPlayer);
    SpawnPlayer();
    // FARCALL(av_InitializeStartDay);
    v_InitializeStartDay();
    // RET;
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

bool Continue(void) {
    // FARCALL(aTryLoadSaveFile);
    // IF_C goto FailToLoad;
    if(TryLoadSaveFile()) {
        // FARCALL(av_LoadData);
        v_LoadData();
        // CALL(aLoadStandardMenuHeader);
        LoadStandardMenuHeader_Conv();
        // CALL(aDisplaySaveInfoOnContinue);
        DisplaySaveInfoOnContinue_Conv();
        // LD_A(0x1);
        // LDH_addr_A(hBGMapMode);
        hram->hBGMapMode = 0x1;
        // LD_C(20);
        // CALL(aDelayFrames);
        DelayFrames_Conv(20);
        // CALL(aConfirmContinue);
        // IF_NC goto Check1Pass;
        if(ConfirmContinue_Conv() && !Continue_CheckRTC_RestartClock()) {
        // Check1Pass:
            // CALL(aContinue_CheckRTC_RestartClock);
            // IF_NC goto Check2Pass;
            // CALL(aCloseWindow);
            // goto FailToLoad;

        // Check2Pass:
            // LD_A(0x8);
            // LD_addr_A(wMusicFade);
            wram->wMusicFade = 0x8;
            // LD_A(LOW(MUSIC_NONE));
            // LD_addr_A(wMusicFadeID);
            // LD_A(HIGH(MUSIC_NONE));
            // LD_addr_A(wMusicFadeID + 1);
            wram->wMusicFadeID = MUSIC_NONE;
            // CALL(aClearBGPalettes);
            ClearBGPalettes_Conv();
            // CALL(aContinue_MobileAdapterMenu);
            Continue_MobileAdapterMenu();
            // CALL(aCloseWindow);
            CloseWindow_Conv2();
            // CALL(aClearTilemap);
            ClearTilemap_Conv2();
            // LD_C(20);
            // CALL(aDelayFrames);
            DelayFrames_Conv(20);
            // FARCALL(aJumpRoamMons);
            JumpRoamMons();
            // FARCALL(aCopyMysteryGiftReceivedDecorationsToPC);
            CopyMysteryGiftReceivedDecorationsToPC();
            // FARCALL(aClockContinue);
            ClockContinue_Conv();
            // LD_A_addr(wSpawnAfterChampion);
            // CP_A(SPAWN_LANCE);
            // IF_Z goto SpawnAfterE4;
            if(wram->wSpawnAfterChampion != SPAWN_LANCE){
                // LD_A(MAPSETUP_CONTINUE);
                // LDH_addr_A(hMapEntryMethod);
                hram->hMapEntryMethod = MAPSETUP_CONTINUE;
                // JP(mFinishContinueFunction);
                Intro_SetJumptableIndex(INTRO_CONTINUE);
                return true;

            // FailToLoad:
                // RET;
            }
            else {
            // SpawnAfterE4:
                // LD_A(SPAWN_NEW_BARK);
                // LD_addr_A(wDefaultSpawnpoint);
                wram->wDefaultSpawnpoint = SPAWN_NEW_BARK;
                // CALL(aPostCreditsSpawn);
                PostCreditsSpawn();
                // JP(mFinishContinueFunction);
                Intro_SetJumptableIndex(INTRO_CONTINUE);
                return true;
            }
        }
        // CALL(aCloseWindow);
        CloseWindow_Conv2();
        // goto FailToLoad;
    }

    return false;
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
    // RET;
}

void Continue_MobileAdapterMenu(void) {
    // FARCALL(aMobile_AlwaysReturnNotCarry);  // mobile check
    u8_flag_s res = Mobile_AlwaysReturnNotCarry();
    // RET_NC;
    if(!res.flag)
        return;

    //  the rest of this stuff is never reached because
    //  the previous function returns with carry not set
    // LD_HL(wd479);
    // BIT_hl(1);
    // RET_NZ;
    if(bit_test(wram->wd479[0], 1))
        return;
    // LD_A(5);
    // LD_addr_A(wMusicFade);
    wram->wMusicFade = 5;
    // LD_A(LOW(MUSIC_MOBILE_ADAPTER_MENU));
    // LD_addr_A(wMusicFadeID);
    // LD_A(HIGH(MUSIC_MOBILE_ADAPTER_MENU));
    // LD_addr_A(wMusicFadeID + 1);
    wram->wMusicFadeID = MUSIC_MOBILE_ADAPTER_MENU;
    // LD_C(20);
    // CALL(aDelayFrames);
    DelayFrames_Conv(20);
    // LD_C(0x1);
    // FARCALL(aInitMobileProfile);  // mobile
    SafeCallGB(aInitMobileProfile, &(struct cpu_registers_s){.c = 0x1});
    // FARCALL(av_SaveData);
    v_SaveData();
    // LD_A(8);
    // LD_addr_A(wMusicFade);
    wram->wMusicFade = 8;
    // LD_A(LOW(MUSIC_NONE));
    // LD_addr_A(wMusicFadeID);
    // LD_A(HIGH(MUSIC_NONE));
    // LD_addr_A(wMusicFadeID + 1);
    wram->wMusicFadeID = MUSIC_NONE;
    // LD_C(35);
    // CALL(aDelayFrames);
    DelayFrames_Conv(35);
    // RET;
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
        GetJoypad_Conv2();
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

bool Continue_CheckRTC_RestartClock(void) {
    // CALL(aCheckRTCStatus);
    // AND_A(0b10000000);  // Day count exceeded 16383
    // IF_Z goto pass;
    if((CheckRTCStatus_Conv() & 0b10000000) != 0) {
        // FARCALL(aRestartClock);
        uint8_t c = RestartClock();
        // LD_A_C;
        // AND_A_A;
        // IF_Z goto pass;
        if(c != FALSE){
            // SCF;
            // RET;
            return true;
        }
    }

// pass:
    // XOR_A_A;
    // RET;
    return false;
}

void FinishContinueFunction(void) {
    while(1){
    // loop:
        // XOR_A_A;
        // LD_addr_A(wDontPlayMapMusicOnReload);
        wram->wDontPlayMapMusicOnReload = 0x0;
        // LD_addr_A(wLinkMode);
        wram->wLinkMode = 0x0;
        // LD_HL(wGameTimerPaused);
        // SET_hl(GAME_TIMER_PAUSED_F);
        bit_set(wram->wGameTimerPaused, GAME_TIMER_PAUSED_F);
        // RES_hl(GAME_TIMER_MOBILE_F);
        bit_reset(wram->wGameTimerPaused, GAME_TIMER_MOBILE_F);
        // LD_HL(wEnteredMapFromContinue);
        // SET_hl(1);
        bit_set(wram->wEnteredMapFromContinue, 1);
        // FARCALL(aOverworldLoop);
        OverworldLoop();
        // LD_A_addr(wSpawnAfterChampion);
        // CP_A(SPAWN_RED);
        // IF_Z goto AfterRed;
        if(wram->wSpawnAfterChampion != SPAWN_RED){
            // JP(mReset);
            return Intro_SetJumptableIndex(INTRO_SOFT_RESET);
        }

    // AfterRed:
        // CALL(aSpawnAfterRed);
        SpawnAfterRed();
        // goto loop;
    }
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

void DisplaySaveInfoOnContinue_Conv(void) {
    // CALL(aCheckRTCStatus);
    // AND_A(0b10000000);
    // IF_Z goto clock_ok;
    if((CheckRTCStatus_Conv() & 0b10000000) != 0) {
        // LD_DE((4 << 8) | 8);
        // CALL(aDisplayContinueDataWithRTCError);
        // RET;
        return DisplayContinueDataWithRTCError_Conv(4, 8);
    }
    else {
    // clock_ok:
        // LD_DE((4 << 8) | 8);
        // CALL(aDisplayNormalContinueData);
        // RET;
        return DisplayNormalContinueData_Conv(4, 8);
    }
}

void DisplaySaveInfoOnSave(void) {
    LD_DE((4 << 8) | 0);
    JR(mDisplayNormalContinueData);

}

void DisplaySaveInfoOnSave_Conv(void) {
    // LD_DE((4 << 8) | 0);
    // JR(mDisplayNormalContinueData);
    return DisplayNormalContinueData_Conv(4, 0);
}

void DisplayNormalContinueData(void) {
    CALL(aContinue_LoadMenuHeader);
    CALL(aContinue_DisplayBadgesDexPlayerName);
    CALL(aContinue_PrintGameTime);
    CALL(aLoadFontsExtra);
    CALL(aUpdateSprites);
    RET;

}

void DisplayNormalContinueData_Conv(uint8_t d, uint8_t e) {
    // CALL(aContinue_LoadMenuHeader);
    Continue_LoadMenuHeader_Conv(d, e);
    // CALL(aContinue_DisplayBadgesDexPlayerName);
    tile_t* hl = Continue_DisplayBadgesDexPlayerName_Conv();
    // CALL(aContinue_PrintGameTime);
    Continue_PrintGameTime_Conv(hl);
    // CALL(aLoadFontsExtra);
    LoadFontsExtra_Conv();
    // CALL(aUpdateSprites);
    UpdateSprites_Conv();
    // RET;
}

void DisplayContinueDataWithRTCError(void) {
    CALL(aContinue_LoadMenuHeader);
    CALL(aContinue_DisplayBadgesDexPlayerName);
    CALL(aContinue_UnknownGameTime);
    CALL(aLoadFontsExtra);
    CALL(aUpdateSprites);
    RET;

}

void DisplayContinueDataWithRTCError_Conv(uint8_t d, uint8_t e) {
    // CALL(aContinue_LoadMenuHeader);
    Continue_LoadMenuHeader_Conv(d, e);
    // CALL(aContinue_DisplayBadgesDexPlayerName);
    tile_t* hl = Continue_DisplayBadgesDexPlayerName_Conv();
    // CALL(aContinue_UnknownGameTime);
    Continue_UnknownGameTime(hl);
    // CALL(aLoadFontsExtra);
    LoadFontsExtra_Conv();
    // CALL(aUpdateSprites);
    UpdateSprites_Conv();
    // RET;
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

static const struct MenuHeader MenuHeader_Dex = {
    .flags=MENU_BACKUP_TILES,  // flags
    .coord = menu_coords(0, 0, 15, 9),
    //dw ['.MenuData_Dex'];
    .data = &(struct MenuData){
        .flags = 0,
        .verticalMenu = {
            .count = 4,
            .options = (const char* []) {
                "PLAYER@",
                "BADGES@",
                "#DEX@",
                "TIME@",
            }
        },
    },
    .defaultOption = 1,  // default option
};

static const struct MenuHeader MenuHeader_NoDex = {
    .flags=MENU_BACKUP_TILES,  // flags
    .coord = menu_coords(0, 0, 15, 9),
    //dw ['.MenuData_Dex'];
    .data = &(struct MenuData){
        .flags = 0,
        .verticalMenu = {
            .count = 4,
            .options = (const char* []) {
                "PLAYER <PLAYER>@",
                "BADGES@",
                " @",
                "TIME@",
            }
        },
    },
    .defaultOption = 1,  // default option
};

void Continue_LoadMenuHeader_Conv(uint8_t d, uint8_t e) {
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = 0;
    // LD_HL(mContinue_LoadMenuHeader_MenuHeader_Dex);
    // LD_A_addr(wStatusFlags);
    // BIT_A(STATUSFLAGS_POKEDEX_F);
    // IF_NZ goto show_menu;
    // LD_HL(mContinue_LoadMenuHeader_MenuHeader_NoDex);


// show_menu:
    const struct MenuHeader* hl = (bit_test(wram->wStatusFlags, STATUSFLAGS_POKEDEX_F))? &MenuHeader_Dex: &MenuHeader_NoDex;
    // CALL(av_OffsetMenuHeader);
    v_OffsetMenuHeader_Conv(hl, d, e);
    // CALL(aMenuBox);
    MenuBox_Conv();
    // CALL(aPlaceVerticalMenuItems);
    PlaceVerticalMenuItems_Conv2();
    // RET;


// MenuHeader_NoDex:
    //db ['MENU_BACKUP_TILES'];  // flags
    //menu_coords ['0', '0', '15', '9'];
    //dw ['.MenuData_NoDex'];
    //db ['1'];  // default option


// MenuData_NoDex:
    //db ['0'];  // flags
    //db ['4'];  // items
    //db ['"PLAYER <PLAYER>@"'];
    //db ['"BADGES@"'];
    //db ['" @"'];
    //db ['"TIME@"'];
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

tile_t* Continue_DisplayBadgesDexPlayerName_Conv(void) {
    static const char Player[] = "<PLAYER>@";
    uint8_t buf[16];
    // CALL(aMenuBoxCoord2Tile);
    tile_t* hl = MenuBoxCoord2Tile_Conv();
    // PUSH_HL;
    // decoord(13, 4, 0);
    // ADD_HL_DE;
    // CALL(aContinue_DisplayBadgeCount);
    Continue_DisplayBadgeCount_Conv(hl + coord(13, 4, 0));
    // POP_HL;
    // PUSH_HL;
    // decoord(12, 6, 0);
    // ADD_HL_DE;
    // CALL(aContinue_DisplayPokedexNumCaught);
    Continue_DisplayBadgeCount_Conv(hl + coord(12, 6, 0));
    // POP_HL;
    // PUSH_HL;
    // decoord(8, 2, 0);
    // ADD_HL_DE;
    // LD_DE(mContinue_DisplayBadgesDexPlayerName_Player);
    // CALL(aPlaceString);
    PlaceStringSimple(U82CA(buf, Player), hl + coord(8, 2, 0));
    // POP_HL;
    // RET;
    return hl;
}

void Continue_PrintGameTime(void) {
    decoord(9, 8, 0);
    ADD_HL_DE;
    CALL(aContinue_DisplayGameTime);
    RET;

}

void Continue_PrintGameTime_Conv(tile_t* hl) {
    // decoord(9, 8, 0);
    // ADD_HL_DE;
    // CALL(aContinue_DisplayGameTime);
    Continue_DisplayGameTime_Conv(hl + coord(9, 8, 0));
    // RET;
}

void Continue_UnknownGameTime(tile_t* hl) {
    // decoord(9, 8, 0);
    // ADD_HL_DE;
    // LD_DE(mContinue_UnknownGameTime_three_question_marks);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(" ???@"), coord(9, 8, hl));
    // RET;

// three_question_marks:
    //db ['" ???@"'];
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

tile_t* Continue_DisplayBadgeCount_Conv(tile_t* hl) {
    // PUSH_HL;
    // LD_HL(wJohtoBadges);
    // LD_B(2);
    // CALL(aCountSetBits);
    uint8_t count = CountSetBits_Conv2(wram->wJohtoBadges, 2);
    // POP_HL;
    // LD_DE(wNumSetBits);
    // LD_BC((1 << 8) | 2);
    // JP(mPrintNum);
    return PrintNum_Conv2(hl, &count, 1, 2);
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

tile_t* Continue_DisplayPokedexNumCaught_Conv(tile_t* hl) {
    // LD_A_addr(wStatusFlags);
    // BIT_A(STATUSFLAGS_POKEDEX_F);
    // RET_Z;
    if(!bit_test(wram->wStatusFlags, STATUSFLAGS_POKEDEX_F))
        return hl;
    // PUSH_HL;
    // LD_HL(wPokedexCaught);
    // if (NUM_POKEMON % 8)
    //     LD_B(NUM_POKEMON / 8 + 1);
    // else
    //     LD_B(NUM_POKEMON / 8);
    // CALL(aCountSetBits);
    uint8_t count = CountSetBits_Conv2(wram->wPokedexCaught, (NUM_POKEMON % 8)? NUM_POKEMON / 8 + 1: NUM_POKEMON / 8);
    // POP_HL;
    // LD_DE(wNumSetBits);
    // LD_BC((1 << 8) | 3);
    // JP(mPrintNum);
    return PrintNum_Conv2(hl, &count, 1, 3);
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

void Continue_DisplayGameTime_Conv(tile_t* hl) {
    // LD_DE(wGameTimeHours);
    // LD_BC((2 << 8) | 3);
    // CALL(aPrintNum);
    hl = PrintNum_Conv2(hl, &wram->wGameTimeHours, 2, 3);
    // LD_hl(0x6d);
    // INC_HL;
    *(hl++) = 0x6d;
    // LD_DE(wGameTimeMinutes);
    // LD_BC((PRINTNUM_LEADINGZEROS | 1 << 8) | 2);
    // JP(mPrintNum);
    PrintNum_Conv2(hl, &wram->wGameTimeMinutes, PRINTNUM_LEADINGZEROS | 1, 2);
}

void OakSpeech(void) {
    // FARCALL(aInitClock);
    InitClock();
    // CALL(aRotateFourPalettesLeft);
    RotateFourPalettesLeft_Conv();
    // CALL(aClearTilemap);
    ClearTilemap_Conv2();

    // LD_DE(MUSIC_ROUTE_30);
    // CALL(aPlayMusic);
    PlayMusic_Conv(MUSIC_ROUTE_30);

    // CALL(aRotateFourPalettesRight);
    RotateFourPalettesRight_Conv();
    // CALL(aRotateThreePalettesRight);
    RotateThreePalettesRight_Conv();
    // XOR_A_A;
    // LD_addr_A(wCurPartySpecies);
    wram->wCurPartySpecies = 0x0;
    // LD_A(POKEMON_PROF);
    // LD_addr_A(wTrainerClass);
    wram->wTrainerClass = POKEMON_PROF;
    // CALL(aIntro_PrepTrainerPic);
    Intro_PrepTrainerPic(POKEMON_PROF);

    // LD_B(SCGB_TRAINER_OR_MON_FRONTPIC_PALS);
    // CALL(aGetSGBLayout);
    GetSGBLayout_Conv(SCGB_TRAINER_OR_MON_FRONTPIC_PALS);
    // CALL(aIntro_RotatePalettesLeftFrontpic);
    Intro_RotatePalettesLeftFrontpic();

    // LD_HL(mOakText1);
    // CALL(aPrintText);
    PrintText_Conv2(OakText1);
    // CALL(aRotateThreePalettesRight);
    RotateThreePalettesRight_Conv();
    // CALL(aClearTilemap);
    ClearTilemap_Conv2();

    // LD_A(WOOPER);
    // LD_addr_A(wCurSpecies);
    wram->wCurSpecies = WOOPER;
    // LD_addr_A(wCurPartySpecies);
    wram->wCurPartySpecies = WOOPER;
    // CALL(aGetBaseData);
    GetBaseData_Conv2(WOOPER);

    // hlcoord(6, 4, wTilemap);
    // CALL(aPrepMonFrontpic);
    PrepMonFrontpic_Conv(coord(6, 4, wram->wTilemap));

    // XOR_A_A;
    // LD_addr_A(wTempMonDVs);
    // LD_addr_A(wTempMonDVs + 1);
    wram->wTempMon.mon.DVs = 0;

    // LD_B(SCGB_TRAINER_OR_MON_FRONTPIC_PALS);
    // CALL(aGetSGBLayout);
    GetSGBLayout_Conv(SCGB_TRAINER_OR_MON_FRONTPIC_PALS);
    // CALL(aIntro_WipeInFrontpic);
    Intro_WipeInFrontpic();

    // LD_HL(mOakText2);
    // CALL(aPrintText);
    PrintText_Conv2(OakText2);
    // LD_HL(mOakText4);
    // CALL(aPrintText);
    PrintText_Conv2(OakText4);
    // CALL(aRotateThreePalettesRight);
    RotateThreePalettesRight_Conv();
    // CALL(aClearTilemap);
    ClearTilemap_Conv2();

    // XOR_A_A;
    // LD_addr_A(wCurPartySpecies);
    wram->wCurPartySpecies = 0x0;
    // LD_A(POKEMON_PROF);
    // LD_addr_A(wTrainerClass);
    wram->wTrainerClass = POKEMON_PROF;
    // CALL(aIntro_PrepTrainerPic);
    Intro_PrepTrainerPic(POKEMON_PROF);

    // LD_B(SCGB_TRAINER_OR_MON_FRONTPIC_PALS);
    // CALL(aGetSGBLayout);
    GetSGBLayout_Conv(SCGB_TRAINER_OR_MON_FRONTPIC_PALS);
    // CALL(aIntro_RotatePalettesLeftFrontpic);
    Intro_RotatePalettesLeftFrontpic();

    // LD_HL(mOakText5);
    // CALL(aPrintText);
    PrintText_Conv2(OakText5);
    // CALL(aRotateThreePalettesRight);
    RotateThreePalettesRight_Conv();
    // CALL(aClearTilemap);
    ClearTilemap_Conv2();

    // XOR_A_A;
    // LD_addr_A(wCurPartySpecies);
    wram->wCurPartySpecies = 0x0;
    // FARCALL(aDrawIntroPlayerPic);
    DrawIntroPlayerPic_Conv();

    // LD_B(SCGB_TRAINER_OR_MON_FRONTPIC_PALS);
    // CALL(aGetSGBLayout);
    GetSGBLayout_Conv(SCGB_TRAINER_OR_MON_FRONTPIC_PALS);
    // CALL(aIntro_RotatePalettesLeftFrontpic);
    Intro_RotatePalettesLeftFrontpic();

    // LD_HL(mOakText6);
    // CALL(aPrintText);
    PrintText_Conv2(OakText6);
    // CALL(aNamePlayer);
    NamePlayer();
    // LD_HL(mOakText7);
    // CALL(aPrintText);
    PrintText_Conv2(OakText7);
    // RET;
}

const txt_cmd_s OakText1[] = {
    text_far(v_OakText1)
    text_end
};

void OakText2_ASM(struct TextCmdState* state);

const txt_cmd_s OakText2[] = {
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

const txt_cmd_s OakText3[] = {
    text_far(v_OakText3)
    text_end
};

const txt_cmd_s OakText4[] = {
    text_far(v_OakText4)
    text_end
};

const txt_cmd_s OakText5[] = {
    text_far(v_OakText5)
    text_end
};

const txt_cmd_s OakText6[] = {
    text_far(v_OakText6)
    text_end
};

const txt_cmd_s OakText7[] = {
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

    // FARCALL(aMovePlayerPicRight);
    MovePlayerPicRight_Conv();
    // FARCALL(aShowPlayerNamingChoices);
    ShowPlayerNamingChoices();
    // LD_A_addr(wMenuCursorY);
    // DEC_A;
    // IF_Z goto NewName;
    if(wram->wMenuCursorY - 1 != 0){
        // CALL(aStorePlayerName);
        StorePlayerName();
        // FARCALL(aApplyMonOrTrainerPals);
        ApplyMonOrTrainerPals(0);
        // FARCALL(aMovePlayerPicLeft);
        MovePlayerPicLeft_Conv();
        // RET;
        return;
    }
    else {
    // NewName:
        // LD_B(NAME_PLAYER);
        // LD_DE(wPlayerName);
        // FARCALL(aNamingScreen);
        NamingScreen_Conv(wram->wPlayerName, NAME_PLAYER);

        // CALL(aRotateThreePalettesRight);
        RotateThreePalettesRight_Conv();
        // CALL(aClearTilemap);
        ClearTilemap_Conv2();

        // CALL(aLoadFontsExtra);
        LoadFontsExtra_Conv();
        // CALL(aWaitBGMap);
        WaitBGMap_Conv();

        // XOR_A_A;
        // LD_addr_A(wCurPartySpecies);
        wram->wCurPartySpecies = 0x0;
        // FARCALL(aDrawIntroPlayerPic);
        DrawIntroPlayerPic_Conv();

        // LD_B(SCGB_TRAINER_OR_MON_FRONTPIC_PALS);
        // CALL(aGetSGBLayout);
        GetSGBLayout_Conv(SCGB_TRAINER_OR_MON_FRONTPIC_PALS);
        // CALL(aRotateThreePalettesLeft);
        RotateThreePalettesLeft_Conv();

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
        // RET;
    }
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
    // RET;
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
    // RET;
}

#define dc(a, b, c, d) ((a & 0x3) << 6) | ((b & 0x3) << 4) | ((c & 0x3) << 2) | (d & 0x3)

void Intro_RotatePalettesLeftFrontpic(void) {
    static const uint8_t IntroFadePalettes[] = {
        dc(1, 1, 1, 0),
        dc(2, 2, 2, 0),
        dc(3, 3, 3, 0),
        dc(3, 3, 2, 0),
        dc(3, 3, 1, 0),
        dc(3, 2, 1, 0),
    };
    // LD_HL(mIntroFadePalettes);
    const uint8_t* hl = IntroFadePalettes;
    //LD_B(IntroFadePalettes.End - mIntroFadePalettes);
    uint8_t b = sizeof(IntroFadePalettes);

    do {
    // loop:
        // LD_A_hli;
        // CALL(aDmgToCgbBGPals);
        DmgToCgbBGPals_Conv(*(hl++));
        // LD_C(10);
        // CALL(aDelayFrames);
        DelayFrames_Conv(10);
        // DEC_B;
        // IF_NZ goto loop;
    } while(--b != 0);
    // RET;
}

void Intro_WipeInFrontpic(void) {
    // LD_A(0x77);
    // LDH_addr_A(hWX);
    // CALL(aDelayFrame);
    DelayFrame();
    // LD_A(0b11100100);
    // CALL(aDmgToCgbBGPals);
    DmgToCgbBGPals_Conv(0b11100100);

    while(1) {
    // loop:
        // CALL(aDelayFrame);
        DelayFrame();
        // LDH_A_addr(hWX);
        // SUB_A(0x8);
        // CP_A(-1);
        // RET_Z;
        if(hram->hWX - 0x8 == 0xff)
            return;
        // LDH_addr_A(hWX);
        hram->hWX -= 0x8;
        // goto loop;
    }
}

void Intro_PrepTrainerPic(uint8_t tclass) {
    // LD_DE(vTiles2);
    // FARCALL(aGetTrainerPic);
    GetTrainerPic_Conv(vram->vTiles2, tclass);
    // XOR_A_A;
    // LDH_addr_A(hGraphicStartTile);
    hram->hGraphicStartTile = 0x0;
    // hlcoord(6, 4, wTilemap);
    // LD_BC((7 << 8) | 7);
    // PREDEF(pPlaceGraphic);
    PlaceGraphicYStagger_Conv(coord(6, 4, wram->wTilemap), 7, 7);
    // RET;
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
        CrystalIntro();
// Comment the line below to remove the intro movie.
        // FARCALL(aCrystalIntro);

// fallthrough
    return Intro_SetJumptableIndex(INTRO_TITLE);
}

static void StartTitleScreen_TitleScreen(void){
    // FARCALL(av_TitleScreen);
    v_TitleScreen();
    // RET;
}

void StartTitleScreen(void){
    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    // LD_A(MBANK(awLYOverrides));
    // LDH_addr_A(rSVBK);

    // CALL(aStartTitleScreen_TitleScreen);
    StartTitleScreen_TitleScreen();
    // CALL(aDelayFrame);
    DelayFrame();

    do {
    // loop:
        // CALL(aRunTitleScreen);
        // IF_NC goto loop;
    } while(!RunTitleScreen_Conv());

    // CALL(aClearSprites);
    ClearSprites_Conv();
    // CALL(aClearBGPalettes);
    ClearBGPalettes_Conv();

    // POP_AF;
    // LDH_addr_A(rSVBK);

    // LD_HL(rLCDC);
    // RES_hl(rLCDC_SPRITE_SIZE);  // 8x8
    gb_write(rLCDC, gb_read(rLCDC) & ~(1 << rLCDC_SPRITE_SIZE));
    // CALL(aClearScreen);
    ClearScreen_Conv2();
    // CALL(aWaitBGMap2);
    WaitBGMap2_Conv();
    // XOR_A_A;
    // LDH_addr_A(hLCDCPointer);
    hram->hLCDCPointer = 0x0;
    // LDH_addr_A(hSCX);
    hram->hSCX = 0x0;
    // LDH_addr_A(hSCY);
    hram->hSCY = 0x0;
    // LD_A(0x7);
    // LDH_addr_A(hWX);
    hram->hWX = 0x7;
    // LD_A(0x90);
    // LDH_addr_A(hWY);
    hram->hWY = 0x90;
    // LD_B(SCGB_DIPLOMA);
    // CALL(aGetSGBLayout);
    GetSGBLayout_Conv(SCGB_DIPLOMA);
    // CALL(aUpdateTimePals);
    UpdateTimePals();
    // LD_A_addr(wTitleScreenSelectedOption);
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
    switch(wram->wTitleScreenSelectedOption) {
        default:
        case TITLESCREENOPTION_MAIN_MENU:           return Intro_MainMenu();
        case TITLESCREENOPTION_DELETE_SAVE_DATA:    return DeleteSaveData();
        case TITLESCREENOPTION_RESTART:             return Intro_SetJumptableIndex(INTRO_INTRO_SEQUENCE);
        case TITLESCREENOPTION_UNUSED:              return Intro_SetJumptableIndex(INTRO_INTRO_SEQUENCE);
        case TITLESCREENOPTION_RESET_CLOCK:         return ResetClock();
    }


// dw:
    //dw ['Intro_MainMenu'];
    //dw ['DeleteSaveData'];
    //dw ['IntroSequence'];
    //dw ['IntroSequence'];
    //dw ['ResetClock'];
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
        GetJoypad_Conv2();
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
    // FARCALL(av_DeleteSaveData);
    v_DeleteSaveData();
    // JP(mInit);
    return Intro_SetJumptableIndex(INTRO_HARD_RESET);
}

void ResetClock(void) {
    // FARCALL(av_ResetClock);
    v_ResetClock();
    // JP(mInit);
    return Intro_SetJumptableIndex(INTRO_HARD_RESET);
}

//#ifdef _DEBUG
//void DebugMenu(void) {
    //FARCALL(av_ResetClock);
    //JP(mInit);

//}
//#endif

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
    // FARCALL(aTryLoadSaveData);
    TryLoadSaveData();
    // CALL(aClearWindowData);
    ClearWindowData_Conv2();
    // CALL(aClearBGPalettes);
    ClearBGPalettes_Conv();
    // CALL(aClearTilemap);
    ClearTilemap_Conv2();
    // LD_A(HIGH(vBGMap0));
    // LDH_addr_A(hBGMapAddress + 1);
    // XOR_A_A;  // LOW(vBGMap0)
    // LDH_addr_A(hBGMapAddress);
    hram->hBGMapAddress = vBGMap0;
    // LDH_addr_A(hJoyDown);
    hram->hJoyDown = 0x0;
    // LDH_addr_A(hSCX);
    hram->hSCX = 0x0;
    // LDH_addr_A(hSCY);
    hram->hSCY = 0x0;
    // LD_A(0x90);
    // LDH_addr_A(hWY);
    hram->hWY = 0x90;
    // CALL(aWaitBGMap);
    WaitBGMap_Conv();
    // JP(mIntroSequence);
    return Intro_SetJumptableIndex(INTRO_INTRO_SEQUENCE);
}
