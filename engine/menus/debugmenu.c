#include <stdint.h>
#include <stdbool.h>
#include "../../constants.h"
#include "debugmenu.h"
#include "../../home/audio.h"
#include "../../home/delay.h"
#include "../../home/joypad.h"
#include "../../home/menu.h"
#include "../../home/text.h"
#include "../../home/tilemap.h"
#include "../../home/copy.h"
#include "../../home/gfx.h"
#include "../../charmap.h"
#include "../../data/trainers/class_names.h"
#include "../../data/trainers/parties.h"
#include "../gfx/load_font.h"
#include "../gfx/place_graphic.h"
#include "../gfx/load_pics.h"
#include "../gfx/pic_animation.h"
#include "../gfx/dma_transfer.h"
#include "../gfx/color.h"
#include "../pokemon/stats_screen.h"
#include "../phone/phone.h"
#include "../../util/scripting.h"

typedef struct {
    const char* name;
    void (*handler)(void); // This function is called when the option is selected
} DebugMenuOption;

void Handler_Fight(void);
void Handler_Link(void);
void Handler_Field(void);
void Handler_SoundTest(void);
void Handler_Subgame(void);
void Handler_Anime(void);
void Handler_Graphics(void);
void Handler_Pokedex(void);
void Handler_Trainergear(void);
void Handler_Stats(void);
void Handler_Pics(void);
void Handler_Script(void);

static DebugMenuOption debugMenuOptions[] = {
    {"FIGHT@", Handler_Fight},
    {"LINK@", Handler_Link},
    {"FIELD@", Handler_Field},
    {"SOUND@", Handler_SoundTest},
    {"MINIGAME@", Handler_Subgame},
    {"ANIME@", Handler_Anime},
    {"GRAPHICS@", Handler_Graphics},
    {"POKEDEX@", Handler_Pokedex},
    {"POKEGEAR@", Handler_Trainergear},
    {"STATS@", Handler_Stats},
    {"PICS@", Handler_Pics},
    {"SCRIPT@", Handler_Script},
};

#define MAX_OPTIONS_PER_PAGE 7
#define MAX_OPTION_STRING_LENGTH 8

static uint8_t cursorIndex = 0;
static uint8_t currentPage = 0;

void DebugMenu_PrintStrings() {
    uint8_t* hl = wram->wTilemap + coordidx(6, 1);
    uint8_t start = currentPage * MAX_OPTIONS_PER_PAGE;
    uint8_t end = start + MAX_OPTIONS_PER_PAGE;
    if (end > sizeof(debugMenuOptions) / sizeof(DebugMenuOption)) {
        end = sizeof(debugMenuOptions) / sizeof(DebugMenuOption);
    }
    for(uint8_t i = start; i < end; ++i) {
        PlaceStringSimple(Utf8ToCrystal(debugMenuOptions[i].name), hl);
        hl = wram->wTilemap + coordidx(6, 1 + (i - start + 1) * 2);
    }
    char buf[10];
    sprintf(buf, "PAGE%d@", currentPage + 1);
    PlaceStringSimple(Utf8ToCrystal(buf), hl);
}

void DebugMenu_PlaceCursor(void) {
    wram->wTilemap[coordidx(5, cursorIndex*2 + 1)] = CHAR_RIGHT_CURSOR;
}

void DebugMenu_MoveCursor(int8_t dir) {
    wram->wTilemap[coordidx(5, cursorIndex*2 + 1)] = CHAR_SPACE;
    int next = (int)cursorIndex + dir;

    uint8_t numberOfOptions = sizeof(debugMenuOptions) / sizeof(DebugMenuOption);
    uint8_t maxIndexOnPage = (currentPage == (numberOfOptions - 1) / MAX_OPTIONS_PER_PAGE) ?
                             (numberOfOptions - 1) % MAX_OPTIONS_PER_PAGE + 1 :
                             MAX_OPTIONS_PER_PAGE;

    if(next > maxIndexOnPage) 
        cursorIndex = 0;
    else if(next < 0)
        cursorIndex = maxIndexOnPage;
    else 
        cursorIndex = (uint8_t)next;
    DebugMenu_PlaceCursor();
}

#define DEBUG_MENU_MUSIC MUSIC_NONE

static void DebugMenu_MenuBox(void) {
    return Textbox_Conv2(Coord2Tile_Conv(4, 0), (MAX_OPTIONS_PER_PAGE + 1) * 2, MAX_OPTION_STRING_LENGTH + 1);
}

void DebugMenu(void) {
    uint8_t inMenu = hram->hInMenu;
    hram->hInMenu = 1;
    PlayMusic_Conv(MUSIC_NONE);
    DelayFrame();
    PlayMusic_Conv(DEBUG_MENU_MUSIC);
    DebugMenu_MenuBox();
    DebugMenu_PrintStrings();
    DebugMenu_PlaceCursor();
    while(1)
    {
        wram->wDisableTextAcceleration = 0;
        GetJoypad_Conv();
        int8_t dir = -((hram->hJoyPressed & D_UP)? 1: 0) + ((hram->hJoyPressed & D_DOWN)? 1: 0);
        if(dir != 0) {
            DebugMenu_MoveCursor(dir);
            DelayFrame();
            continue;
        }
        if(hram->hJoyPressed & (A_BUTTON)) {
            uint8_t numberOfOptions = sizeof(debugMenuOptions) / sizeof(DebugMenuOption);
            if(cursorIndex == MAX_OPTIONS_PER_PAGE || 
                currentPage * MAX_OPTIONS_PER_PAGE + cursorIndex >= numberOfOptions) {
                currentPage = (currentPage + 1) % ((numberOfOptions + MAX_OPTIONS_PER_PAGE - 1) / MAX_OPTIONS_PER_PAGE);
                cursorIndex = 0;
                PlayClickSFX_Conv();
            } else {
                debugMenuOptions[currentPage * MAX_OPTIONS_PER_PAGE + cursorIndex].handler();
            }
            DebugMenu_MenuBox();
            DebugMenu_PrintStrings();
            DebugMenu_PlaceCursor();
            continue;
        }
        if(hram->hJoyPressed & (B_BUTTON))
            break;
        DelayFrame();
    }
    PlayMusic_Conv(MUSIC_NONE);
    DelayFrame();
    hram->hInMenu = inMenu;
}

void Handler_Fight(void) {
    // TODO: Implement this function
    DebugMenu_BattleTest();
    PlayMusic_Conv(DEBUG_MENU_MUSIC);
}

void Handler_Link(void) {
    // TODO: Implement this function
    DebugMenu_Link();
    PlayMusic_Conv(DEBUG_MENU_MUSIC);
}

void Handler_Field(void) {
    // TODO: Implement this function
}

void Handler_SoundTest(void) {
    DebugMenu_SoundTest();
    PlayMusic_Conv(DEBUG_MENU_MUSIC);
}

void Handler_Subgame(void) {
    // TODO: Implement this function
}

void Handler_Anime(void) {
    // TODO: Implement this function
}

void Handler_Graphics(void) {
    // TODO: Implement this function
    // DebugMenu_GFXTest();
    ShowTestText();
    PlayMusic_Conv(DEBUG_MENU_MUSIC);
}

void Handler_Pokedex(void) {
    // TODO: Implement this function
}

void Handler_Trainergear(void) {
    // TODO: Implement this function
}

void Handler_Stats(void) {
    // TODO: Implement this function
    DebugMenu_Stats();
    PlayMusic_Conv(DEBUG_MENU_MUSIC);
}

void Handler_Pics(void) {
    // TODO: Implement this function
    DebugMenu_Pics();
    PlayMusic_Conv(DEBUG_MENU_MUSIC);
}

void Handler_Script(void) {
    DebugMenu_Scripting();
    PlayMusic_Conv(DEBUG_MENU_MUSIC);
}

static const char* DebugMenu_MusicNames[] = {
    [MUSIC_NONE] = "NONE@",
    [MUSIC_TITLE] = "TITLE@",
    [MUSIC_ROUTE_1] = "ROUTE 1@",
    [MUSIC_ROUTE_3] = "ROUTE 3@",
    [MUSIC_ROUTE_12] = "ROUTE 12@",
    [MUSIC_MAGNET_TRAIN] = "MAGNET TRAIN@",
    [MUSIC_KANTO_GYM_LEADER_BATTLE] = "VS KANTO GYM@",
    [MUSIC_KANTO_TRAINER_BATTLE] = "VS KANTO TRNR@",
    [MUSIC_KANTO_WILD_BATTLE] = "VS KANTO WILD@",
    [MUSIC_POKEMON_CENTER] = "POKEMON CENTER@",
    [MUSIC_BICYCLE] = "BICYCLE@",
    [MUSIC_DARK_CAVE] = "DARK CAVE@",
    [MUSIC_DRAGONS_DEN] = "DRGNS DEN@",
    [MUSIC_CRYSTAL_OPENING] = "CRYSTAL OPENING@",
    [MUSIC_BATTLE_TOWER_THEME] = "BATTLE T OUTSIDE@",
    [MUSIC_SUICUNE_BATTLE] = "SUICUNE BATTLE@",
    [MUSIC_BATTLE_TOWER_LOBBY] = "BATTLE T LOBBY@",
    [MUSIC_MOBILE_CENTER] = "POKECOM CENTER@",
};

static const char* DebugMenu_SoundNames[] = {
    [SFX_DEX_FANFARE_50_79] = "DEX FAN 50 79@",
    [SFX_ITEM] = "ITEM@",
    [SFX_CAUGHT_MON] = "CAUGHT MON@",
    [SFX_POTION] = "POTION@",
    [SFX_WARP_TO] = "WARP TO",
    [SFX_WARP_FROM] = "WARP FROM",
    [SFX_CALL] = "CALL@",
    [SFX_HANG_UP] = "HANG UP@",
    [SFX_NO_SIGNAL] = "NO SIGNAL@",
};

static void DebugMenu_SoundTest_PlaceMusicName(uint16_t track) {
    ClearBox_Conv2(wram->wTilemap + coordidx(2, 2), SCREEN_WIDTH - 4, 1);
    if(track >= lengthof(DebugMenu_MusicNames) || DebugMenu_MusicNames[track] == NULL) {
        char buf[10];
        sprintf(buf, "M%03X", track);
        PlaceStringSimple(Utf8ToCrystal(buf), wram->wTilemap + coordidx(2, 2));
    }
    else {
        PlaceStringSimple(Utf8ToCrystal(DebugMenu_MusicNames[track]), wram->wTilemap + coordidx(2, 2));
    }
}

static void DebugMenu_SoundTest_PlaceSoundName(uint16_t track) {
    ClearBox_Conv2(wram->wTilemap + coordidx(2, 6), SCREEN_WIDTH - 4, 1);
    if(track >= lengthof(DebugMenu_SoundNames) || DebugMenu_SoundNames[track] == NULL) {
        char buf[10];
        sprintf(buf, "SE%03X", track);
        PlaceStringSimple(Utf8ToCrystal(buf), wram->wTilemap + coordidx(2, 6));
    }
    else {
        PlaceStringSimple(Utf8ToCrystal(DebugMenu_SoundNames[track]), wram->wTilemap + coordidx(2, 6));
    }
}

void DebugMenu_SoundTest(void) {
    PlayMusic_Conv(MUSIC_NONE);
    DelayFrame();

    uint8_t editingWhich = 0;
    uint16_t musicTrack = MUSIC_NONE;
    uint16_t sound = SFX_ITEM;

    ClearBox_Conv2(wram->wTilemap + coordidx(0, 0), SCREEN_WIDTH, SCREEN_HEIGHT);
    Textbox_Conv2(wram->wTilemap + coordidx(TEXTBOX_X, TEXTBOX_Y), TEXTBOX_INNERH, TEXTBOX_INNERW);
    PlaceStringSimple(Utf8ToCrystal("A-PLAY  B-STOP<LINE>START- BACK@"), wram->wTilemap + coordidx(TEXTBOX_INNERX, TEXTBOX_INNERY));
    PlaceStringSimple(Utf8ToCrystal("MUSIC@"), wram->wTilemap + coordidx(0, 0));
    PlaceStringSimple(Utf8ToCrystal("SOUND EFFECT@"), wram->wTilemap + coordidx(0, 4));
    wram->wTilemap[coordidx(1, 2)] = CHAR_LEFT_ARROW;
    wram->wTilemap[coordidx(SCREEN_WIDTH - 2, 2)] = CHAR_RIGHT_ARROW;
    DebugMenu_SoundTest_PlaceMusicName(musicTrack);
    DebugMenu_SoundTest_PlaceSoundName(sound);

    while(1)
    {
        wram->wDisableTextAcceleration = 0;
        GetJoypad_Conv();
        int8_t dir = -((hram->hJoyPressed & D_LEFT)? 1: 0) + ((hram->hJoyPressed & D_RIGHT)? 1: 0);
        if(dir != 0) {
            if(editingWhich == 0) {
                int newTrack = musicTrack + dir;
                if(newTrack >= NUM_MUSIC_SONGS) {
                    musicTrack = 0;
                }
                else if(newTrack < 0) {
                    musicTrack = NUM_MUSIC_SONGS - 1;
                }
                else {
                    musicTrack += dir;
                }
                DebugMenu_SoundTest_PlaceMusicName(musicTrack);
            }
            else {
                int newTrack = sound + dir;
                if(newTrack >= NUM_SFX) {
                    sound = 0;
                }
                else if(newTrack < 0) {
                    sound = NUM_SFX - 1;
                }
                else {
                    sound += dir;
                }
                DebugMenu_SoundTest_PlaceSoundName(sound);
            }
            DelayFrame();
            continue;
        }
        if(hram->hJoyPressed & (D_DOWN)) {
            editingWhich = 1;
            wram->wTilemap[coordidx(1, 2)] = CHAR_SPACE;
            wram->wTilemap[coordidx(SCREEN_WIDTH - 2, 2)] = CHAR_SPACE;
            wram->wTilemap[coordidx(1, 6)] = CHAR_LEFT_ARROW;
            wram->wTilemap[coordidx(SCREEN_WIDTH - 2, 6)] = CHAR_RIGHT_ARROW;
        }
        if(hram->hJoyPressed & (D_UP)) {
            editingWhich = 0;
            wram->wTilemap[coordidx(1, 6)] = CHAR_SPACE;
            wram->wTilemap[coordidx(SCREEN_WIDTH - 2, 6)] = CHAR_SPACE;
            wram->wTilemap[coordidx(1, 2)] = CHAR_LEFT_ARROW;
            wram->wTilemap[coordidx(SCREEN_WIDTH - 2, 2)] = CHAR_RIGHT_ARROW;
        }
        if(hram->hJoyPressed & (B_BUTTON)) {
            PlayMusic_Conv(MUSIC_NONE);
            DelayFrame();
        }
        if(hram->hJoyPressed & (SELECT)) 
            break;
        if(hram->hJoyPressed & (A_BUTTON)) {
            if(editingWhich == 0) {
                PlayMusic_Conv(MUSIC_NONE);
                DelayFrame();
                PlayMusic_Conv(musicTrack);
            } else {
                PlaySFX_Conv(sound);
            }
        }
        DelayFrame();
    }
    PlayMusic_Conv(MUSIC_NONE);
    ClearBox_Conv2(wram->wTilemap + coordidx(0, 0), SCREEN_WIDTH, SCREEN_HEIGHT);
    DelayFrame();
}

static void DebugMenu_BattleTest_StartBattle(uint8_t tclass, uint8_t tid) {
    SAFECALL(aClearTilemap);
    WaitBGMap_Conv();
    DelayFrames_Conv(10);

    // Rival name and Player name are null by default. 
    Utf8ToCrystalBuffer(wram->wRivalName, NAME_LENGTH, "???@");
    Utf8ToCrystalBuffer(wram->wPlayerName, NAME_LENGTH, "PLAYER@");

    wram->wBattleType = BATTLETYPE_NORMAL;
    wram->wInBattleTowerBattle = 0;
    wram->wLinkMode = LINK_NULL;

    wram->wBattleScriptFlags = (1 << 7) | 1;
    wram->wOtherTrainerClass = tclass;
    wram->wOtherTrainerID = tid + 1;

    // wram->wMapScriptsBank = BANK(aRedWinLossText);
    // wram->wLossTextPointer = 0;
    // wram->wWinTextPointer = mRedWinLossText;

    // Skip winloss text, if possible
    bit_set(wram->wDebugFlags, DEBUG_BATTLE_F);

    // Add Pokemon to party
    wram->wCurPartySpecies = DRAGONITE;
    wram->wCurPartyLevel = 100;
    wram->wPartyCount = 0;
    wram->wMonType = PARTYMON;
    {
        wbank_push(MBANK(awPartyMon1));
        PREDEF(pTryAddMonToParty);
        wbank_pop;
    }
    wbank_push(MBANK(awInBattleTowerBattle));
    SafeCallGBAuto(aStartBattle);

    bit_reset(wram->wDebugFlags, DEBUG_BATTLE_F);

    wbank_pop;
    ClearTilemap_Conv2();
    WaitBGMap_Conv();
    LoadFontsExtra_Conv();
    LoadStandardFont_Conv();
    PlayMusic_Conv(MUSIC_NONE);
    DelayFrame();
}

static void DebugMenu_BattleTest_GetNextTrainer(uint8_t* tclass, uint8_t* tid) {
    if(++(*tid) < TrainerGroups[*tclass - 1].count) {
        return;
    }
    else if(++(*tclass) <= MYSTICALMAN) {
        *tid = 0;
        return;
    }
    *tclass = FALKNER;
    *tid = FALKNER1;
}

static void DebugMenu_BattleTest_GetNextTrainerClass(uint8_t* tclass, uint8_t* tid) {
    if(++(*tclass) > MYSTICALMAN) {
        *tclass = FALKNER;
        *tid = 0;
        return;
    }
    while(TrainerGroups[*tclass - 1].count == 0) {
        if(++(*tclass) > MYSTICALMAN) {
            *tclass = FALKNER;
            *tid = 0;
            return;
        }
    }
    *tid = 0;
}

static void DebugMenu_BattleTest_GetPrevTrainer(uint8_t* tclass, uint8_t* tid) {
    if(*tid == 0) {
        if(*tclass == FALKNER) {
            *tclass = MYSTICALMAN;
            return;
        }
        --(*tclass);
        *tid = TrainerGroups[*tclass - 1].count - 1;
        return;
    }
    --(*tid);
}

static void DebugMenu_BattleTest_GetPrevTrainerClass(uint8_t* tclass, uint8_t* tid) {
    if((*tclass)-- == 0) {
        *tclass = MYSTICALMAN;
        *tid = 0;
        return;
    }
    while(TrainerGroups[*tclass - 1].count == 0) {
        if((*tclass)-- == 0) {
            *tclass = MYSTICALMAN;
            *tid = 0;
            return;
        }
    }
    *tid = 0;
}

void DebugMenu_BattleTest_PlaceTrainerName(uint8_t tclass, uint8_t tid) {
    char buffer[32];
    sprintf(buffer, "CLASS- %s", TrainerClassNames[tclass - 1]);
    PlaceStringSimple(U82C(buffer), wram->wTilemap + coordidx(2, 2));
    sprintf(buffer, "   ID- %02d:%02d", tclass, tid);
    PlaceStringSimple(U82C(buffer), wram->wTilemap + coordidx(2, 4));
    sprintf(buffer, " NAME- %s", TrainerGroups[tclass - 1].parties[tid].name);
    PlaceStringSimple(U82C(buffer), wram->wTilemap + coordidx(2, 6));
}

void DebugMenu_BattleTest(void) {
    PlayMusic_Conv(MUSIC_NONE);
    DelayFrame();

    uint8_t tclass = PSYCHIC_T; 
    uint8_t tid = NATHAN;

    ClearBox_Conv2(wram->wTilemap + coordidx(0, 0), SCREEN_WIDTH, SCREEN_HEIGHT);
    Textbox_Conv2(wram->wTilemap + coordidx(TEXTBOX_X, TEXTBOX_Y), TEXTBOX_INNERH, TEXTBOX_INNERW);
    PlaceStringSimple(Utf8ToCrystal("A- FIGHT  LR- MV<LINE>B- BACK@"), wram->wTilemap + coordidx(TEXTBOX_INNERX, TEXTBOX_INNERY));
    DebugMenu_BattleTest_PlaceTrainerName(tclass, tid);

    while(1)
    {
        wram->wDisableTextAcceleration = 0;
        GetJoypad_Conv();
        int8_t hdir = -((hram->hJoyPressed & D_LEFT)? 1: 0) + ((hram->hJoyPressed & D_RIGHT)? 1: 0);
        int8_t vdir = -((hram->hJoyPressed & D_UP)? 1: 0) + ((hram->hJoyPressed & D_DOWN)? 1: 0);
        if(hdir > 0) {
            DebugMenu_BattleTest_GetNextTrainer(&tclass, &tid);
            ClearBox_Conv2(wram->wTilemap + coordidx(0, 0), SCREEN_WIDTH, 7);
            DebugMenu_BattleTest_PlaceTrainerName(tclass, tid);
        }
        else if(hdir < 0) {
            DebugMenu_BattleTest_GetPrevTrainer(&tclass, &tid);
            ClearBox_Conv2(wram->wTilemap + coordidx(0, 0), SCREEN_WIDTH, 7);
            DebugMenu_BattleTest_PlaceTrainerName(tclass, tid);
        }
        if(vdir > 0) {
            DebugMenu_BattleTest_GetNextTrainerClass(&tclass, &tid);
            ClearBox_Conv2(wram->wTilemap + coordidx(0, 0), SCREEN_WIDTH, 7);
            DebugMenu_BattleTest_PlaceTrainerName(tclass, tid);
        }
        else if(vdir < 0) {
            DebugMenu_BattleTest_GetPrevTrainerClass(&tclass, &tid);
            ClearBox_Conv2(wram->wTilemap + coordidx(0, 0), SCREEN_WIDTH, 7);
            DebugMenu_BattleTest_PlaceTrainerName(tclass, tid);
        }
        if(hram->hJoyPressed & (B_BUTTON)) 
            break;
        if(hram->hJoyPressed & (A_BUTTON)) {
            DebugMenu_BattleTest_StartBattle(tclass, tid);
            Textbox_Conv2(wram->wTilemap + coordidx(TEXTBOX_X, TEXTBOX_Y), TEXTBOX_INNERH, TEXTBOX_INNERW);
            PlaceStringSimple(Utf8ToCrystal("A- FIGHT  LR- MV<LINE>B- BACK@"), wram->wTilemap + coordidx(TEXTBOX_INNERX, TEXTBOX_INNERY));
            DebugMenu_BattleTest_PlaceTrainerName(tclass, tid);
        }
        DelayFrame();
    }
    PlayMusic_Conv(MUSIC_NONE);
    ClearBox_Conv2(wram->wTilemap + coordidx(0, 0), SCREEN_WIDTH, SCREEN_HEIGHT);
    DelayFrame();
}

void DebugMenu_GFXTest(void) {
    hram->hBGMapMode = 0;
    ClearBox_Conv2(wram->wTilemap + coordidx(0, 0), SCREEN_WIDTH, SCREEN_HEIGHT);
    ByteFill_Conv2(vram->vTiles0, 2048, 0);
    ByteFill_Conv2(vram->vTiles1, 2048, 0);
    ByteFill_Conv2(vram->vTiles2, 2048, 0);
    v_LoadStandardFont_Conv();
    StatsScreen_LoadFont_Conv();
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles2, "gfx/pokemon/charizard/front.png", 0, 7 * 7);
    PlaceStringSimple(U82C("--0123456789ABCDEF--"), coord(0, 0, wram->wTilemap));
    for(int i = 0; i < 10; i++) {
        *coord(0, i + 1, wram->wTilemap) = CHAR_0 + i;
    }
    for(int i = 0; i < 6; i++) {
        *coord(0, i + 11, wram->wTilemap) = CHAR_A + i;
    }
    for(int i = 0; i < 256; i++) {
        *coord((i & 0xf) + 2, ((i & 0xf0) >> 4) + 1, wram->wTilemap) = i;
    }
    WaitBGMap_Conv();
    DelayFrame();

    while(1)
    {
        wram->wDisableTextAcceleration = 0;
        GetJoypad_Conv();
        if(hram->hJoyPressed & (B_BUTTON)) 
            break;
        if(hram->hJoyPressed & (A_BUTTON))  {
            hram->hGraphicStartTile = 0;
            PlaceGraphic_Conv(coord(0, 0, wram->wTilemap), 7, 7);
        }
        DelayFrame();
    }

    ClearBox_Conv2(wram->wTilemap + coordidx(0, 0), SCREEN_WIDTH, SCREEN_HEIGHT);
    ByteFill_Conv2(vram->vTiles0, 2048, 0);
    ByteFill_Conv2(vram->vTiles1, 2048, 0);
    ByteFill_Conv2(vram->vTiles2, 2048, 0);
    v_LoadFontsExtra1_Conv();
    v_LoadFontsExtra2_Conv();
    v_LoadStandardFont_Conv();
    DelayFrame();
}

void DebugMenu_Stats(void) {
    Utf8ToCrystalBuffer(wram->wPlayerName, NAME_LENGTH, "PLAYER@");

    wram->wCurPartySpecies = CHARIZARD;
    wram->wCurPartyLevel = 100;
    wram->wPartyCount = 0;
    wram->wMonType = PARTYMON;
    {
        wbank_push(MBANK(awPartyMon1));
        PREDEF(pTryAddMonToParty);
        wbank_pop;
    }

    wram->wCurPartyMon = 0;

    SAFECALL(aStatsScreenInit);

    ClearTilemap_Conv2();
    ByteFill_Conv2(vram->vTiles0, 2048, 0);
    ByteFill_Conv2(vram->vTiles1, 2048, 0);
    ByteFill_Conv2(vram->vTiles2, 2048, 0);
    v_LoadFontsExtra1_Conv();
    v_LoadFontsExtra2_Conv();
    v_LoadStandardFont_Conv();
    TextboxPalette_Conv2(wram->wTilemap, SCREEN_WIDTH, SCREEN_HEIGHT);
    WaitBGMap_Conv();
    DelayFrame();
}

void DebugMenu_Pics_PlaceStrings(species_t* sp) {
    char buf[32];
    sprintf(buf, "ID   - %03d@", *sp);
    PlaceStringSimple(U82C(buf), coord(0, 0, wram->wTilemap));
    struct BaseData* hl = AbsGBToRAMAddr(aBaseData);
    uint8_t size = hl[*sp - 1].picSize;
    sprintf(buf, "SIZE - %d, %d@", size & 0xf, size >> 4);
    ClearBox_Conv2(coord(0, 2, wram->wTilemap), SCREEN_WIDTH, 1);
    PlaceStringSimple(U82C(buf), coord(0, 2, wram->wTilemap));
}

static void DebugMenu_Pics_DoAnim(species_t sp) {
    uint16_t palbuf[3 * NUM_PAL_COLORS];
    ClearBox_Conv2(coord(2, 4, wram->wTilemap), 7, 7);

    DelayFrame();

    wram->wUnownLetter = UNOWN_A;
    wram->wCurPartySpecies = sp;
    GetAnimatedFrontpic_Conv(vram->vTiles2 + LEN_2BPP_TILE * 0x00, 0);
    LoadMonAnimation_Conv(coord(2, 4, wram->wTilemap), 0x0, ANIM_MON_MENU);
    GetPlayerOrMonPalettePointer_Conv(palbuf, wram->wCurSpecies, wram->wTempMon.mon.DVs);
    LoadPalette_White_Col1_Col2_Black_Conv((uint16_t*)wram->wBGPals1 + 4, palbuf);
    SetPalettes_Conv();

    while(!SetUpPokeAnim_Conv()) {
        HDMATransferTilemapToWRAMBank3_Conv();
    }
}

static void DebugMenu_Pics_SetLayout(void) {
    FillBoxCGB_Conv(coord(2, 4, wram->wAttrmap), 8, SCREEN_WIDTH, 0x1);
}

void DebugMenu_Pics(void) {
    ClearScreen_Conv2();
    v_LoadFontsExtra1_Conv();
    v_LoadFontsExtra2_Conv();
    v_LoadStandardFont_Conv();

    DebugMenu_Pics_SetLayout();
    
    DelayFrame();

    species_t s = BULBASAUR;
    DebugMenu_Pics_PlaceStrings(&s);
    DebugMenu_Pics_DoAnim(s);

    while(1)
    {
        GetJoypad_Conv();

        if(hram->hJoyPressed & (B_BUTTON))
            break;
        
        int8_t dir = -((hram->hJoyPressed & D_LEFT)? 1: 0) + ((hram->hJoyPressed & D_RIGHT)? 1: 0);
        if(dir < 0) {
            if(s == BULBASAUR) s = CELEBI;
            else s--;
            DebugMenu_Pics_PlaceStrings(&s);
            HDMATransferTilemapToWRAMBank3_Conv();
            continue;
        }
        else if(dir > 0) {
            if(s == CELEBI) s = BULBASAUR;
            else s++;
            DebugMenu_Pics_PlaceStrings(&s);
            HDMATransferTilemapToWRAMBank3_Conv();
            continue;
        }

        if(hram->hJoyPressed & (A_BUTTON)) {
            DebugMenu_Pics_DoAnim(s);
        }
        DelayFrame();
    }

    ClearTilemap_Conv2();
    ByteFill_Conv2(wram->wAttrmap, (SCREEN_WIDTH * SCREEN_HEIGHT), PAL_BG_TEXT);
    ByteFill_Conv2(vram->vTiles0, 2048, 0);
    ByteFill_Conv2(vram->vTiles1, 2048, 0);
    ByteFill_Conv2(vram->vTiles2, 2048, 0);
    v_LoadFontsExtra1_Conv();
    v_LoadFontsExtra2_Conv();
    v_LoadStandardFont_Conv();
    TextboxPalette_Conv2(wram->wTilemap, SCREEN_WIDTH, SCREEN_HEIGHT);
    WaitBGMap_Conv();
    DelayFrame();
}

static const struct TextCmd DebugMenu_TestText[] = {
    text_start("This text was"
        t_line "written in C."
        t_para "Isn't that"
        t_line "pretty cool?"
        t_done )
    text_end
};

static const struct TextCmd DebugMenu_TestText_Yes[] = {
    text_start("Yeah!"
        t_prompt )
    text_end
};

static const struct TextCmd DebugMenu_TestText_No[] = {
    text_start("Oh<……>"
        t_prompt )
    text_end
};

void DebugMenu_Scripting(void) {
    ClearScreen_Conv2();
    v_LoadFontsExtra1_Conv();
    v_LoadFontsExtra2_Conv();
    v_LoadStandardFont_Conv();
    WaitBGMap_Conv();

    PrintText_Conv2(DebugMenu_TestText);
    bool res = YesNoBox_Conv();
    if(res) {
        PrintText_Conv2(DebugMenu_TestText_Yes);
    }
    else {
        PrintText_Conv2(DebugMenu_TestText_No);
    }

    ClearTilemap_Conv2();
    ByteFill_Conv2(vram->vTiles0, 2048, 0);
    ByteFill_Conv2(vram->vTiles1, 2048, 0);
    ByteFill_Conv2(vram->vTiles2, 2048, 0);
    v_LoadFontsExtra1_Conv();
    v_LoadFontsExtra2_Conv();
    v_LoadStandardFont_Conv();
    TextboxPalette_Conv2(wram->wTilemap, SCREEN_WIDTH, SCREEN_HEIGHT);
    WaitBGMap_Conv();
    DelayFrame();
}

#include "../link/lan.h"

void DebugMenu_Link(void) {
    ClearScreen_Conv2();
    v_LoadFontsExtra1_Conv();
    v_LoadFontsExtra2_Conv();
    v_LoadStandardFont_Conv();
    WaitBGMap_Conv();

    U82CA(wram->wPlayerName, "PLAYER@");

    LANConnection();
    
}

