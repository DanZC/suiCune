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
#include "../../home/item.h"
#include "../../mobile/mobile_41.h"
#include "../../mobile/mobile_5b.h"
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
#include "../link/lan.h"
#include "../../util/intro_jumptable.h"

static void NewGame_ClearTilemapEtc(void);
static void AreYouABoyOrAreYouAGirl(void);

static void ResetWRAM(void);
static void v_ResetWRAM(void);
static void SetDefaultBoxNames(void);
static void InitializeMagikarpHouse(void);
static void InitializeNPCNames(void);
static void InitializeWorld(void);

static void SpawnAfterRed(void);
static void PostCreditsSpawn(void);

static void Continue_MobileAdapterMenu(void);
static bool ConfirmContinue(void);
static bool Continue_CheckRTC_RestartClock(void);
static void DisplaySaveInfoOnContinue(void);
static void DisplayNormalContinueData(uint8_t d, uint8_t e);
static void DisplayContinueDataWithRTCError(uint8_t d, uint8_t e);
static void Continue_LoadMenuHeader(uint8_t d, uint8_t e);
static tile_t* Continue_DisplayBadgesDexPlayerName(void);
static void Continue_PrintGameTime(tile_t* hl);
static void Continue_UnknownGameTime(tile_t* hl);
static tile_t* Continue_DisplayBadgeCount(tile_t* hl);
static tile_t* Continue_DisplayPokedexNumCaught(tile_t* hl);
static void Continue_DisplayGameTime(tile_t* hl);

static void OakSpeech(void);
static void NamePlayer(void);
static void StorePlayerName(void);
static void ShrinkPlayer(void);
static void Intro_RotatePalettesLeftFrontpic(void);
static void Intro_WipeInFrontpic(void);
static void Intro_PrepTrainerPic(uint8_t tclass);
static void ShrinkFrame(const char* path);
static void Intro_PlacePlayerSprite(void);

static bool RunTitleScreen(void);
static void TitleScreenScene(uint8_t a);
static void TitleScreenEntrance(void);
static void TitleScreenTimer(void);
static void TitleScreenMain(void);
static void TitleScreenEnd(void);

static void DeleteSaveData(void);
static void ResetClock(void);

void Intro_MainMenu(void) {
    PlayMusic(MUSIC_NONE);
    // CALL(aDelayFrame);
    DelayFrame();
    // LD_A_E;
    // LD_addr_A(wMapMusic);
    wram->wMapMusic = MUSIC_NONE;
    PlayMusic(MUSIC_MAIN_MENU);
    // FARCALL(aMainMenu);
    MainMenu();
    // JP(mStartTitleScreen);
}

void PrintDayOfWeek(tile_t* de, uint8_t b) {
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
    PlaceString(&st, st.hl);
    static const char Day[] = "DAY@";
    // LD_H_B;
    // LD_L_C;
    st.hl = st.bc;
    // LD_DE(mPrintDayOfWeek_Day);
    st.de = U82C(Day);
    // CALL(aPlaceString);
    PlaceString(&st, st.hl);
    // RET;
}

static void NewGame_ClearTilemapEtc(void) {
    // XOR_A_A;
    // LDH_addr_A(hMapAnims);
    hram.hMapAnims = 0x0;
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

void MysteryGift(void) {
    // CALL(aUpdateTime);
    UpdateTime();
    // FARCALL(aDoMysteryGiftIfDayHasPassed);
    DoMysteryGiftIfDayHasPassed();
    // FARCALL(aDoMysteryGift);

    OpenSRAM(MBANK(asPlayerData));
    wram->wPlayerGender = gb_read(sCrystalData);
    CopyBytes(&wram->wPlayerID,  GBToRAMAddr(sPlayerData + (wPlayerID - wPlayerData)), 2);
    CopyBytes(wram->wPlayerName, GBToRAMAddr(sPlayerData + (wPlayerName - wPlayerData)), NAME_LENGTH);
    CloseSRAM();

    if(!LANTryConnection())
        return;
    DoMysteryGift();
    LANCloseConnection();
    // RET;
}

void Option(void) {
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
    hram.hMapEntryMethod = MAPSETUP_WARP;
    // JP(mFinishContinueFunction);
    return Intro_SetJumptableIndex(INTRO_CONTINUE);
}

static void AreYouABoyOrAreYouAGirl(void) {
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
    // FARCALL(aInitMobileProfile);  // mobile
    InitMobileProfile(0);
    // RET;
}

void DebugRoom(void) {
    //FARCALL(_DebugRoom);
    // RET;
}

static void ResetWRAM(void) {
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram.hBGMapMode = BGMAPMODE_NONE;
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
static void v_ResetWRAM_InitItemList(item_pocket_u* hl){
    // XOR_A_A;
    // LD_hli_A;
    hl->pocket.count = 0;
    // DEC_A;
    // LD_hl_A;
    hl->pocket.pocket[0].item = (item_t)-1;
    // RET;
}

static void v_ResetWRAM(void) {
    // LD_HL(wVirtualOAM);
    // LD_BC(wOptions - wVirtualOAM);
    // XOR_A_A;
    // CALL(aByteFill);
    ByteFill_GB(wVirtualOAM, wOptions - wVirtualOAM, 0);

    // LD_HL(WRAM1_Begin);
    // LD_BC(wGameData - WRAM1_Begin);
    // XOR_A_A;
    // CALL(aByteFill);
    ByteFill_GB(WRAM1_Begin, wGameData - WRAM1_Begin, 0);

    // LD_HL(wGameData);
    // LD_BC(wGameDataEnd - wGameData);
    // XOR_A_A;
    // CALL(aByteFill);
    ByteFill_GB(wGameData, wGameDataEnd - wGameData, 0);

    // LDH_A_addr(rLY);
    // LDH_addr_A(hUnusedBackup);
    // CALL(aDelayFrame);
    DelayFrame();
    // LDH_A_addr(hRandomSub);
    // LD_addr_A(wPlayerID);
    uint8_t pid_lo = hram.hRandomSub;

    // LDH_A_addr(rLY);
    // LDH_addr_A(hUnusedBackup);
    // CALL(aDelayFrame);
    DelayFrame();
    // LDH_A_addr(hRandomAdd);
    // LD_addr_A(wPlayerID + 1);
    uint8_t pid_hi = hram.hRandomAdd;
    wram->wPlayerID = (pid_hi << 8) | pid_lo;

    // CALL(aRandom);
    // LD_addr_A(wSecretID);
    // CALL(aDelayFrame);
    // CALL(aRandom);
    // LD_addr_A(wSecretID + 1);
    uint8_t sid_lo = Random();
    DelayFrame();
    uint8_t sid_hi = Random();
    wram->wSecretID = (sid_hi << 8) | sid_lo;

    // LD_HL(wPartyCount);
    // CALL(av_ResetWRAM_InitList);
    v_ResetWRAM_InitMonList(&gPokemon.partyCount, gPokemon.partySpecies);

    // XOR_A_A;
    // LD_addr_A(wCurBox);
    wram->wCurBox = 0;
    // LD_addr_A(wSavedAtLeastOnce);
    wram->wSavedAtLeastOnce = FALSE;

    // CALL(aSetDefaultBoxNames);
    SetDefaultBoxNames();

    // LD_A(MBANK(asBoxCount));
    // CALL(aOpenSRAM);
    OpenSRAM(MBANK(asBoxCount));
    // LD_HL(sBoxCount);
    // CALL(av_ResetWRAM_InitList);
    v_ResetWRAM_InitMonList((uint8_t*)GBToRAMAddr(sBoxCount), (species_t*)GBToRAMAddr(sBoxSpecies));
    // CALL(aCloseSRAM);
    CloseSRAM();

    // LD_HL(wNumItems);
    // CALL(av_ResetWRAM_InitList);
    v_ResetWRAM_InitItemList(GetItemPocket(ITEM_POCKET));

    // LD_HL(wNumKeyItems);
    // CALL(av_ResetWRAM_InitList);
    v_ResetWRAM_InitItemList(GetItemPocket(KEY_ITEM_POCKET));

    // LD_HL(wNumBalls);
    // CALL(av_ResetWRAM_InitList);
    v_ResetWRAM_InitItemList(GetItemPocket(BALL_POCKET));

    // LD_HL(wNumPCItems);
    // CALL(av_ResetWRAM_InitList);
    v_ResetWRAM_InitItemList(GetItemPocket(PC_ITEM_POCKET));

    // XOR_A_A;
    // LD_addr_A(wRoamMon1Species);
    gPokemon.roamMon1.species = 0;
    // LD_addr_A(wRoamMon2Species);
    gPokemon.roamMon2.species = 0;
    // LD_addr_A(wRoamMon3Species);
    gPokemon.roamMon3.species = 0;
    // LD_A(-1);
    // LD_addr_A(wRoamMon1MapGroup);
    // LD_addr_A(wRoamMon2MapGroup);
    // LD_addr_A(wRoamMon3MapGroup);
    // LD_addr_A(wRoamMon1MapNumber);
    // LD_addr_A(wRoamMon2MapNumber);
    // LD_addr_A(wRoamMon3MapNumber);
    gPokemon.roamMon1.mapId = (struct MapId){0xff, 0xff};
    gPokemon.roamMon2.mapId = (struct MapId){0xff, 0xff};
    gPokemon.roamMon3.mapId = (struct MapId){0xff, 0xff};

    // LD_A(MBANK(asMysteryGiftItem));  // aka BANK(sMysteryGiftUnlocked)
    // CALL(aOpenSRAM);
    OpenSRAM(MBANK(asMysteryGiftItem));
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
    CloseSRAM();

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
    ResetGameTime();
    // RET;
}

static void SetDefaultBoxNames(void) {
    // LD_HL(wBoxNames);
    uint8_t* hl = wram->wBoxNames;
    // LD_C(0);

    for(uint8_t c = 0; c < NUM_BOXES; c++){
    // loop:
        // PUSH_HL;
        uint8_t* hl2 = hl;
        // LD_DE(mSetDefaultBoxNames_Box);
        // CALL(aCopyName2);
        hl2 = CopyName2(hl2, U82C("BOX@"));
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

static void InitializeMagikarpHouse(void) {
    // LD_HL(wBestMagikarpLengthFeet);
    // LD_A(0x3);
    // LD_hli_A;
    gPokemon.bestMagikarpLengthFeet = 0x3;
    // LD_A(0x6);
    // LD_hli_A;
    gPokemon.bestMagikarpLengthInches = 0x6;
    // LD_DE(mInitializeMagikarpHouse_Ralph);
    // CALL(aCopyName2);
    CopyName2(gPokemon.magikarpRecordHoldersName, U82C("RALPH@"));
    // RET;

// Ralph:
    //db ['"RALPH@"'];
}

static void InitializeNPCNames(void) {
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

static void InitializeWorld(void) {
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
    OpenSRAM(MBANK(asLuckyIDNumber));
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
        id = Random() << 8;
        id |= Random();
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
    return CloseSRAM();
}

bool Continue(void) {
    // FARCALL(aTryLoadSaveFile);
    // IF_C goto FailToLoad;
    if(TryLoadSaveFile()) {
        // FARCALL(av_LoadData);
        v_LoadData();
        // CALL(aLoadStandardMenuHeader);
        LoadStandardMenuHeader();
        // CALL(aDisplaySaveInfoOnContinue);
        DisplaySaveInfoOnContinue();
        // LD_A(0x1);
        // LDH_addr_A(hBGMapMode);
        hram.hBGMapMode = BGMAPMODE_UPDATE_TILES;
        // LD_C(20);
        // CALL(aDelayFrames);
        DelayFrames(20);
        // CALL(aConfirmContinue);
        // IF_NC goto Check1Pass;
        if(ConfirmContinue() && !Continue_CheckRTC_RestartClock()) {
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
            ClearBGPalettes();
            // CALL(aContinue_MobileAdapterMenu);
            Continue_MobileAdapterMenu();
            // CALL(aCloseWindow);
            CloseWindow();
            // CALL(aClearTilemap);
            ClearTilemap();
            // LD_C(20);
            // CALL(aDelayFrames);
            DelayFrames(20);
            // FARCALL(aJumpRoamMons);
            JumpRoamMons();
            // FARCALL(aCopyMysteryGiftReceivedDecorationsToPC);
            CopyMysteryGiftReceivedDecorationsToPC();
            // FARCALL(aClockContinue);
            ClockContinue();
            // LD_A_addr(wSpawnAfterChampion);
            // CP_A(SPAWN_LANCE);
            // IF_Z goto SpawnAfterE4;
            if(wram->wSpawnAfterChampion != SPAWN_LANCE){
                // LD_A(MAPSETUP_CONTINUE);
                // LDH_addr_A(hMapEntryMethod);
                hram.hMapEntryMethod = MAPSETUP_CONTINUE;
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
        CloseWindow();
        // goto FailToLoad;
    }

    return false;
}

static void SpawnAfterRed(void) {
    // LD_A(SPAWN_MT_SILVER);
    // LD_addr_A(wDefaultSpawnpoint);
    wram->wDefaultSpawnpoint = SPAWN_MT_SILVER;

    return PostCreditsSpawn();
}

static void PostCreditsSpawn(void) {
    // XOR_A_A;
    // LD_addr_A(wSpawnAfterChampion);
    wram->wSpawnAfterChampion = 0;
    // LD_A(MAPSETUP_WARP);
    // LDH_addr_A(hMapEntryMethod);
    hram.hMapEntryMethod = MAPSETUP_WARP;
    // RET;
}

static void Continue_MobileAdapterMenu(void) {
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
    DelayFrames(20);
    // LD_C(0x1);
    // FARCALL(aInitMobileProfile);  // mobile
    InitMobileProfile(0x1);
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
    DelayFrames(35);
    // RET;
}

// Returns true if the player confirmed the continue.
// Returns false if cancelled.
static bool ConfirmContinue(void) {

    do {
    // loop:
        // CALL(aDelayFrame);
        DelayFrame();
        // CALL(aGetJoypad);
        GetJoypad();
        // LD_HL(hJoyPressed);
        // BIT_hl(A_BUTTON_F);
        // IF_NZ goto PressA;
        if(bit_test(hram.hJoyPressed, A_BUTTON_F))
            return true;
        // BIT_hl(B_BUTTON_F);
        // IF_Z goto loop;
    } while(!bit_test(hram.hJoyPressed, B_BUTTON_F));
    // SCF;
    // RET;
    return false;

// PressA:
    // RET;
}

static bool Continue_CheckRTC_RestartClock(void) {
    // CALL(aCheckRTCStatus);
    // AND_A(0b10000000);  // Day count exceeded 16383
    // IF_Z goto pass;
    if((CheckRTCStatus() & 0b10000000) != 0) {
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
        wram->wLinkMode = LINK_NULL;
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

static void DisplaySaveInfoOnContinue(void) {
    // CALL(aCheckRTCStatus);
    // AND_A(0b10000000);
    // IF_Z goto clock_ok;
    if((CheckRTCStatus() & 0b10000000) != 0) {
        // LD_DE((4 << 8) | 8);
        // CALL(aDisplayContinueDataWithRTCError);
        // RET;
        return DisplayContinueDataWithRTCError(4, 8);
    }
    else {
    // clock_ok:
        // LD_DE((4 << 8) | 8);
        // CALL(aDisplayNormalContinueData);
        // RET;
        return DisplayNormalContinueData(4, 8);
    }
}

void DisplaySaveInfoOnSave(void) {
    // LD_DE((4 << 8) | 0);
    // JR(mDisplayNormalContinueData);
    return DisplayNormalContinueData(4, 0);
}

static void DisplayNormalContinueData(uint8_t d, uint8_t e) {
    // CALL(aContinue_LoadMenuHeader);
    Continue_LoadMenuHeader(d, e);
    // CALL(aContinue_DisplayBadgesDexPlayerName);
    tile_t* hl = Continue_DisplayBadgesDexPlayerName();
    // CALL(aContinue_PrintGameTime);
    Continue_PrintGameTime(hl);
    // CALL(aLoadFontsExtra);
    LoadFontsExtra();
    // CALL(aUpdateSprites);
    UpdateSprites();
    // RET;
}

static void DisplayContinueDataWithRTCError(uint8_t d, uint8_t e) {
    // CALL(aContinue_LoadMenuHeader);
    Continue_LoadMenuHeader(d, e);
    // CALL(aContinue_DisplayBadgesDexPlayerName);
    tile_t* hl = Continue_DisplayBadgesDexPlayerName();
    // CALL(aContinue_UnknownGameTime);
    Continue_UnknownGameTime(hl);
    // CALL(aLoadFontsExtra);
    LoadFontsExtra();
    // CALL(aUpdateSprites);
    UpdateSprites();
    // RET;
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

static void Continue_LoadMenuHeader(uint8_t d, uint8_t e) {
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram.hBGMapMode = BGMAPMODE_NONE;
    // LD_HL(mContinue_LoadMenuHeader_MenuHeader_Dex);
    // LD_A_addr(wStatusFlags);
    // BIT_A(STATUSFLAGS_POKEDEX_F);
    // IF_NZ goto show_menu;
    // LD_HL(mContinue_LoadMenuHeader_MenuHeader_NoDex);


// show_menu:
    const struct MenuHeader* hl = (bit_test(wram->wStatusFlags, STATUSFLAGS_POKEDEX_F))? &MenuHeader_Dex: &MenuHeader_NoDex;
    // CALL(av_OffsetMenuHeader);
    v_OffsetMenuHeader(hl, d, e);
    // CALL(aMenuBox);
    MenuBox();
    // CALL(aPlaceVerticalMenuItems);
    PlaceVerticalMenuItems();
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

static tile_t* Continue_DisplayBadgesDexPlayerName(void) {
    static const char Player[] = "<PLAYER>@";
    uint8_t buf[16];
    // CALL(aMenuBoxCoord2Tile);
    tile_t* hl = MenuBoxCoord2Tile();
    // PUSH_HL;
    // decoord(13, 4, 0);
    // ADD_HL_DE;
    // CALL(aContinue_DisplayBadgeCount);
    Continue_DisplayBadgeCount(hl + coord(13, 4, 0));
    // POP_HL;
    // PUSH_HL;
    // decoord(12, 6, 0);
    // ADD_HL_DE;
    // CALL(aContinue_DisplayPokedexNumCaught);
    Continue_DisplayPokedexNumCaught(hl + coord(12, 6, 0));
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

static void Continue_PrintGameTime(tile_t* hl) {
    // decoord(9, 8, 0);
    // ADD_HL_DE;
    // CALL(aContinue_DisplayGameTime);
    Continue_DisplayGameTime(hl + coord(9, 8, 0));
    // RET;
}

static void Continue_UnknownGameTime(tile_t* hl) {
    // decoord(9, 8, 0);
    // ADD_HL_DE;
    // LD_DE(mContinue_UnknownGameTime_three_question_marks);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(" ???@"), coord(9, 8, hl));
    // RET;

// three_question_marks:
    //db ['" ???@"'];
}

static tile_t* Continue_DisplayBadgeCount(tile_t* hl) {
    // PUSH_HL;
    // LD_HL(wJohtoBadges);
    // LD_B(2);
    // CALL(aCountSetBits);
    uint8_t count = CountSetBits(wram->wJohtoBadges, 2);
    // POP_HL;
    // LD_DE(wNumSetBits);
    // LD_BC((1 << 8) | 2);
    // JP(mPrintNum);
    return PrintNum(hl, &count, 1, 2);
}

static tile_t* Continue_DisplayPokedexNumCaught(tile_t* hl) {
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
    uint8_t count = CountSetBits(gPokemon.pokedexCaught, (NUM_POKEMON % 8)? NUM_POKEMON / 8 + 1: NUM_POKEMON / 8);
    // POP_HL;
    // LD_DE(wNumSetBits);
    // LD_BC((1 << 8) | 3);
    // JP(mPrintNum);
    return PrintNum(hl, &count, 1, 3);
}

static void Continue_DisplayGameTime(tile_t* hl) {
    // LD_DE(wGameTimeHours);
    // LD_BC((2 << 8) | 3);
    // CALL(aPrintNum);
    hl = PrintNum(hl, &wram->wGameTimeHours, 2, 3);
    // LD_hl(0x6d);
    // INC_HL;
    *(hl++) = 0x6d;
    // LD_DE(wGameTimeMinutes);
    // LD_BC((PRINTNUM_LEADINGZEROS | 1 << 8) | 2);
    // JP(mPrintNum);
    PrintNum(hl, &wram->wGameTimeMinutes, PRINTNUM_LEADINGZEROS | 1, 2);
}

static void OakSpeech(void) {
    // FARCALL(aInitClock);
    InitClock();
    // CALL(aRotateFourPalettesLeft);
    RotateFourPalettesLeft();
    // CALL(aClearTilemap);
    ClearTilemap();

    // LD_DE(MUSIC_ROUTE_30);
    // CALL(aPlayMusic);
    PlayMusic(MUSIC_ROUTE_30);

    // CALL(aRotateFourPalettesRight);
    RotateFourPalettesRight();
    // CALL(aRotateThreePalettesRight);
    RotateThreePalettesRight();
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
    GetSGBLayout(SCGB_TRAINER_OR_MON_FRONTPIC_PALS);
    // CALL(aIntro_RotatePalettesLeftFrontpic);
    Intro_RotatePalettesLeftFrontpic();

    // LD_HL(mOakText1);
    // CALL(aPrintText);
    PrintText(OakText1);
    // CALL(aRotateThreePalettesRight);
    RotateThreePalettesRight();
    // CALL(aClearTilemap);
    ClearTilemap();

    // LD_A(WOOPER);
    // LD_addr_A(wCurSpecies);
    wram->wCurSpecies = WOOPER;
    // LD_addr_A(wCurPartySpecies);
    wram->wCurPartySpecies = WOOPER;
    // CALL(aGetBaseData);
    GetBaseData(WOOPER);

    // hlcoord(6, 4, wTilemap);
    // CALL(aPrepMonFrontpic);
    PrepMonFrontpic(coord(6, 4, wram->wTilemap));

    // XOR_A_A;
    // LD_addr_A(wTempMonDVs);
    // LD_addr_A(wTempMonDVs + 1);
    wram->wTempMon.mon.DVs = 0;

    // LD_B(SCGB_TRAINER_OR_MON_FRONTPIC_PALS);
    // CALL(aGetSGBLayout);
    GetSGBLayout(SCGB_TRAINER_OR_MON_FRONTPIC_PALS);
    // CALL(aIntro_WipeInFrontpic);
    Intro_WipeInFrontpic();

    // LD_HL(mOakText2);
    // CALL(aPrintText);
    PrintText(OakText2);
    // LD_HL(mOakText4);
    // CALL(aPrintText);
    PrintText(OakText4);
    // CALL(aRotateThreePalettesRight);
    RotateThreePalettesRight();
    // CALL(aClearTilemap);
    ClearTilemap();

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
    GetSGBLayout(SCGB_TRAINER_OR_MON_FRONTPIC_PALS);
    // CALL(aIntro_RotatePalettesLeftFrontpic);
    Intro_RotatePalettesLeftFrontpic();

    // LD_HL(mOakText5);
    // CALL(aPrintText);
    PrintText(OakText5);
    // CALL(aRotateThreePalettesRight);
    RotateThreePalettesRight();
    // CALL(aClearTilemap);
    ClearTilemap();

    // XOR_A_A;
    // LD_addr_A(wCurPartySpecies);
    wram->wCurPartySpecies = 0x0;
    // FARCALL(aDrawIntroPlayerPic);
    DrawIntroPlayerPic();

    // LD_B(SCGB_TRAINER_OR_MON_FRONTPIC_PALS);
    // CALL(aGetSGBLayout);
    GetSGBLayout(SCGB_TRAINER_OR_MON_FRONTPIC_PALS);
    // CALL(aIntro_RotatePalettesLeftFrontpic);
    Intro_RotatePalettesLeftFrontpic();

    // LD_HL(mOakText6);
    // CALL(aPrintText);
    PrintText(OakText6);
    // CALL(aNamePlayer);
    NamePlayer();
    // LD_HL(mOakText7);
    // CALL(aPrintText);
    PrintText(OakText7);
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
    PlayMonCry(WOOPER);
    // CALL(aWaitSFX);
    WaitSFX();
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

static void NamePlayer(void) {
// Chris:
    //db ['"CHRIS@@@@@@"'];
    static const char Chris[] = "CHRIS@@@@@@";

// Kris:
    //db ['"KRIS@@@@@@@"'];
    static const char Kris[] = "KRIS@@@@@@@";

    // FARCALL(aMovePlayerPicRight);
    MovePlayerPicRight();
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
        MovePlayerPicLeft();
        // RET;
        return;
    }
    else {
    // NewName:
        // LD_B(NAME_PLAYER);
        // LD_DE(wPlayerName);
        // FARCALL(aNamingScreen);
        NamingScreen(wram->wPlayerName, NAME_PLAYER);

        // CALL(aRotateThreePalettesRight);
        RotateThreePalettesRight();
        // CALL(aClearTilemap);
        ClearTilemap();

        // CALL(aLoadFontsExtra);
        LoadFontsExtra();
        // CALL(aWaitBGMap);
        WaitBGMap();

        // XOR_A_A;
        // LD_addr_A(wCurPartySpecies);
        wram->wCurPartySpecies = 0x0;
        // FARCALL(aDrawIntroPlayerPic);
        DrawIntroPlayerPic();

        // LD_B(SCGB_TRAINER_OR_MON_FRONTPIC_PALS);
        // CALL(aGetSGBLayout);
        GetSGBLayout(SCGB_TRAINER_OR_MON_FRONTPIC_PALS);
        // CALL(aRotateThreePalettesLeft);
        RotateThreePalettesLeft();

        // LD_HL(wPlayerName);
        // LD_DE(mNamePlayer_Chris);
        // LD_A_addr(wPlayerGender);
        // BIT_A(PLAYERGENDER_FEMALE_F);
        // IF_Z goto Male;
        if(bit_test(wram->wPlayerGender, PLAYERGENDER_FEMALE_F)) {
            InitName(wram->wPlayerName, U82C(Kris));
        }
        // LD_DE(mNamePlayer_Kris);

    // Male:
        // CALL(aInitName);
        else {
            InitName(wram->wPlayerName, U82C(Chris));
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

static void StorePlayerName(void) {
    // LD_A(0x50);
    // LD_BC(NAME_LENGTH);
    // LD_HL(wPlayerName);
    // CALL(aByteFill);
    ByteFill(wram->wPlayerName, NAME_LENGTH, 0x50);
    // LD_HL(wPlayerName);
    // LD_DE(wStringBuffer2);
    // CALL(aCopyName2);
    CopyName2(wram->wPlayerName, wram->wStringBuffer2);
    // RET;
}

static void ShrinkPlayer(void) {
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
    PlaySFX(SFX_ESCAPE_ROPE);
    // POP_AF;
    // RST(aBankswitch);

    // LD_C(8);
    // CALL(aDelayFrames);
    DelayFrames(8);

    // LD_HL(mShrink1Pic);
    // LD_B(BANK(aShrink1Pic));
    // CALL(aShrinkFrame);
    ShrinkFrame(Shrink1Pic);

    // LD_C(8);
    // CALL(aDelayFrames);
    DelayFrames(16);

    // LD_HL(mShrink2Pic);
    // LD_B(BANK(aShrink2Pic));
    // CALL(aShrinkFrame);
    ShrinkFrame(Shrink2Pic);

    // LD_C(8);
    // CALL(aDelayFrames);
    DelayFrames(16);

    // hlcoord(6, 5, wTilemap);
    // LD_B(7);
    // LD_C(7);
    // CALL(aClearBox);
    ClearBox(coord(6, 5, wram->wTilemap), 7, 7);

    // LD_C(3);
    // CALL(aDelayFrames);
    DelayFrames(3);

    // CALL(aIntro_PlacePlayerSprite);
    Intro_PlacePlayerSprite();
    // CALL(aLoadFontsExtra);
    LoadFontsExtra();

    // LD_C(50);
    // CALL(aDelayFrames);
    DelayFrames(50);

    // CALL(aRotateThreePalettesRight);
    RotateThreePalettesRight();
    // CALL(aClearTilemap);
    ClearTilemap();
    // RET;
}

#define dc(a, b, c, d) ((a & 0x3) << 6) | ((b & 0x3) << 4) | ((c & 0x3) << 2) | (d & 0x3)

static void Intro_RotatePalettesLeftFrontpic(void) {
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
        DmgToCgbBGPals(*(hl++));
        // LD_C(10);
        // CALL(aDelayFrames);
        DelayFrames(10);
        // DEC_B;
        // IF_NZ goto loop;
    } while(--b != 0);
    // RET;
}

static void Intro_WipeInFrontpic(void) {
    // LD_A(0x77);
    // LDH_addr_A(hWX);
    hram.hWX = 0x77;
    // CALL(aDelayFrame);
    DelayFrame();
    // LD_A(0b11100100);
    // CALL(aDmgToCgbBGPals);
    DmgToCgbBGPals(0b11100100);

    while(1) {
    // loop:
        // CALL(aDelayFrame);
        DelayFrame();
        // LDH_A_addr(hWX);
        // SUB_A(0x8);
        // CP_A(-1);
        // RET_Z;
        if(hram.hWX == 0x7) // hWX - 8 == -1/0xff
            return;
        // LDH_addr_A(hWX);
        hram.hWX -= 0x8;
        // goto loop;
    }
}

static void Intro_PrepTrainerPic(uint8_t tclass) {
    // LD_DE(vTiles2);
    // FARCALL(aGetTrainerPic);
    GetTrainerPic(vram->vTiles2, tclass);
    // XOR_A_A;
    // LDH_addr_A(hGraphicStartTile);
    hram.hGraphicStartTile = 0x0;
    // hlcoord(6, 4, wTilemap);
    // LD_BC((7 << 8) | 7);
    // PREDEF(pPlaceGraphic);
    PlaceGraphicYStagger(coord(6, 4, wram->wTilemap), 7, 7);
    // RET;
}

static void ShrinkFrame(const char* path) {
    // LD_DE(vTiles2);
    // LD_C(7 * 7);
    // PREDEF(pDecompressGet2bpp);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles2, path, 0, 7 * 7);
    // XOR_A_A;
    // LDH_addr_A(hGraphicStartTile);
    hram.hGraphicStartTile = 0;
    // hlcoord(6, 4, wTilemap);
    // LD_BC((7 << 8) | 7);
    // PREDEF(pPlaceGraphic);
    PlaceGraphicYStagger(coord(6, 4, wram->wTilemap), 7, 7);
    // RET;
}

static void Intro_PlacePlayerSprite(void){
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
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles0, GetPlayerIcon(), 0, 12);

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
    } while(!RunTitleScreen());

    // CALL(aClearSprites);
    ClearSprites();
    // CALL(aClearBGPalettes);
    ClearBGPalettes();

    // POP_AF;
    // LDH_addr_A(rSVBK);

    // LD_HL(rLCDC);
    // RES_hl(rLCDC_SPRITE_SIZE);  // 8x8
    gb_write(rLCDC, gb_read(rLCDC) & ~(1 << rLCDC_SPRITE_SIZE));
    // CALL(aClearScreen);
    ClearScreen();
    // CALL(aWaitBGMap2);
    WaitBGMap2();
    // XOR_A_A;
    // LDH_addr_A(hLCDCPointer);
    hram.hLCDCPointer = 0x0;
    // LDH_addr_A(hSCX);
    hram.hSCX = 0x0;
    // LDH_addr_A(hSCY);
    hram.hSCY = 0x0;
    // LD_A(0x7);
    // LDH_addr_A(hWX);
    hram.hWX = 0x7;
    // LD_A(0x90);
    // LDH_addr_A(hWY);
    hram.hWY = 0x90;
    // LD_B(SCGB_DIPLOMA);
    // CALL(aGetSGBLayout);
    GetSGBLayout(SCGB_DIPLOMA);
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

static bool RunTitleScreen(void){
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
    TitleScreenScene(wram->wJumptableIndex);
    // FARCALL(aSuicuneFrameIterator);
    SuicuneFrameIterator();
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

void TitleScreenScene(uint8_t a){
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
        case 0: TitleScreenEntrance(); break;
        case 1: TitleScreenTimer(); break;
        case 2: TitleScreenMain(); break;
        case 3: TitleScreenEnd(); break;
    }
}

void TitleScreenNextScene(void){
//  //  unreferenced
    // LD_HL(wJumptableIndex);
    // INC_hl;
    // RET;
}

//  Animate the logo:
//  Move each line by 4 pixels until our count hits 0.
static void TitleScreenEntrance(void){
    // LDH_A_addr(hSCX);
    // AND_A_A;
    // IF_Z goto done;
    if(hram.hSCX != 0) {
        // SUB_A(4);
        // LDH_addr_A(hSCX);
        hram.hSCX -= 4;

    //  Lay out a base (all lines scrolling together).
        // LD_E_A;
        // LD_HL(wLYOverrides);
        // LD_BC(8 * 10);  // logo height
        // CALL(aByteFill);
        ByteFill(wram->wLYOverrides, 8 * 10, hram.hSCX);

    //  Reversed signage for every other line's position.
    //  This is responsible for the interlaced effect.
        // LD_A_E;
        // XOR_A(0xff);
        // INC_A;
        uint8_t a = -hram.hSCX;

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
        AnimateTitleCrystal();
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
    hram.hLCDCPointer = 0;

//  Play the title screen music.
    // LD_DE(MUSIC_TITLE);
    // CALL(aPlayMusic);
    PlayMusic(MUSIC_TITLE);

    // LD_A(0x88);
    // LDH_addr_A(hWY);
    hram.hWY = 0x88;
    // RET;
}

static void TitleScreenTimer(void){
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

static void TitleScreenMain(void) {
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
        GetJoypad();
        // LD_HL(hJoyDown);
        // LD_A_hl;
        // AND_A(D_UP + B_BUTTON + SELECT);
        // CP_A(D_UP + B_BUTTON + SELECT);
        // IF_Z goto delete_save_data;
        if((hram.hJoyDown & (D_UP + B_BUTTON + SELECT)) == (D_UP + B_BUTTON + SELECT)) {
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
            if(hram.hClockResetTrigger == 0x34) {
            //  Keep Select pressed, and hold Left + Up.
            //  Then let go of Select.
            // check_clock_reset:
                // BIT_hl(SELECT_F);
                // IF_NZ goto check_start;
                if(!bit_test(hram.hJoyDown, SELECT_F)) {
                    // XOR_A_A;
                    // LDH_addr_A(hClockResetTrigger);
                    hram.hClockResetTrigger = 0;

                    // LD_A_hl;
                    // AND_A(D_LEFT + D_UP);
                    // CP_A(D_LEFT + D_UP);
                    // IF_Z goto reset_clock;
                    if((hram.hJoyDown & (D_LEFT + D_UP)) == (D_LEFT + D_UP)) {
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
            else if((hram.hJoyDown & (D_DOWN + B_BUTTON + SELECT)) == (D_DOWN + B_BUTTON + SELECT)) {
                // LD_A(0x34);
                // LDH_addr_A(hClockResetTrigger);
                hram.hClockResetTrigger = 0x34;
                // goto check_start;
            }

            //  Press Start or A to start the game.

        // check_start:
            // LD_A_hl;
            // AND_A(START | A_BUTTON);
            // IF_NZ goto incave;
            if(hram.hJoyDown & (START | A_BUTTON)) {
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

static void TitleScreenEnd(void) {
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

static void DeleteSaveData(void) {
    // FARCALL(av_DeleteSaveData);
    v_DeleteSaveData();
    // JP(mInit);
    return Intro_SetJumptableIndex(INTRO_HARD_RESET);
}

static void ResetClock(void) {
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
    ClearTilemap();
    // CALL(aLoadFontsExtra);
    LoadFontsExtra();
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
    ClearWindowData();
    // CALL(aClearBGPalettes);
    ClearBGPalettes();
    // CALL(aClearTilemap);
    ClearTilemap();
    // LD_A(HIGH(vBGMap0));
    // LDH_addr_A(hBGMapAddress + 1);
    // XOR_A_A;  // LOW(vBGMap0)
    // LDH_addr_A(hBGMapAddress);
    hram.hBGMapAddress = vBGMap0;
    // LDH_addr_A(hJoyDown);
    hram.hJoyDown = 0x0;
    // LDH_addr_A(hSCX);
    hram.hSCX = 0x0;
    // LDH_addr_A(hSCY);
    hram.hSCY = 0x0;
    // LD_A(0x90);
    // LDH_addr_A(hWY);
    hram.hWY = 0x90;
    // CALL(aWaitBGMap);
    WaitBGMap();

#if !PM_HIDDEN_NETWORK
    MobileAdapterCheck();
#endif

    // JP(mIntroSequence);
    return Intro_SetJumptableIndex(INTRO_INTRO_SEQUENCE);
}
