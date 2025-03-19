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
#include "../../home/sram.h"
#include "../../home/map.h"
#include "../../charmap.h"
#include "../../data/trainers/class_names.h"
#include "../../data/trainers/parties.h"
#include "../../data/pokemon/base_stats.h"
#include "../../mobile/mobile_5f.h"
#include "../gfx/load_font.h"
#include "../gfx/place_graphic.h"
#include "../gfx/load_pics.h"
#include "../gfx/pic_animation.h"
#include "../gfx/dma_transfer.h"
#include "../gfx/color.h"
#include "../pokemon/stats_screen.h"
#include "../pokemon/move_mon.h"
#include "../phone/phone.h"
#include "../battle/core.h"
#include "../battle_anims/anim_commands.h"
#include "../link/link.h"
#include "../link/link_trade.h"
#include "../link/mystery_gift.h"
#include "../movie/trade_animation.h"
#include "../movie/init_hof_credits.h"
#include "../movie/credits.h"
#include <stdlib.h>

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
void Handler_TradeAnim(void);
void Handler_BattleAnim(void);
void Handler_Credits(void);
void Handler_MysteryGift(void);
void Handler_News(void);

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
    {"TRADE@", Handler_TradeAnim},
    {"BANIMS@", Handler_BattleAnim},
    {"CREDITS@", Handler_Credits},
    {"MYSTRY G@", Handler_MysteryGift},
    {"NEWS@", Handler_News},
};

#define MAX_OPTIONS_PER_PAGE 7
#define MAX_OPTION_STRING_LENGTH 8

static uint8_t cursorIndex = 0;
static uint8_t currentPage = 0;

static tile_t* sDebugMenuTilemapBuffer;
static tile_t* sDebugMenuAttrmapBuffer;

void DebugMenu_SaveTilemap(void) {
    CopyBytes(sDebugMenuTilemapBuffer, coord(0, 0, wram->wTilemap), sizeof(wram->wTilemap));
}

void DebugMenu_RestoreTilemap(void) {
    CopyBytes(coord(0, 0, wram->wTilemap), sDebugMenuTilemapBuffer, sizeof(wram->wTilemap));
}

void DebugMenu_SaveAttrmap(void) {
    CopyBytes(sDebugMenuAttrmapBuffer, coord(0, 0, wram->wAttrmap), sizeof(wram->wAttrmap));
}

void DebugMenu_RestoreAttrmap(void) {
    CopyBytes(coord(0, 0, wram->wAttrmap), sDebugMenuAttrmapBuffer, sizeof(wram->wAttrmap));
}

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
    PEEK("");
    uint8_t inMenu = hram->hInMenu;
    hram->hInMenu = 1;

    if(sDebugMenuTilemapBuffer) {
        free(sDebugMenuTilemapBuffer); // also frees sDebugMenuAttrmapBuffer
    }
    sDebugMenuTilemapBuffer = malloc(sizeof(wram->wTilemap) * 2);
    sDebugMenuAttrmapBuffer = sDebugMenuTilemapBuffer + sizeof(wram->wTilemap);

    PlayMusic(MUSIC_NONE);
    DelayFrame();
    PlayMusic(DEBUG_MENU_MUSIC);
    DebugMenu_MenuBox();
    DebugMenu_PrintStrings();
    DebugMenu_PlaceCursor();
    while(1)
    {
        wram->wDisableTextAcceleration = 0;
        GetJoypad_Conv2();
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
    PlayMusic(MUSIC_NONE);
    DelayFrame();

    free(sDebugMenuTilemapBuffer); // also frees sDebugMenuAttrmapBuffer
    sDebugMenuTilemapBuffer = NULL;
    sDebugMenuAttrmapBuffer = NULL;

    hram->hInMenu = inMenu;
}

void Handler_Fight(void) {
    DebugMenu_BattleTest();
    PlayMusic(DEBUG_MENU_MUSIC);
}

void Handler_Link(void) {
    // TODO: Implement this function
    DebugMenu_Link();
    PlayMusic(DEBUG_MENU_MUSIC);
}

void Handler_Field(void) {
    // TODO: Implement this function
}

void Handler_SoundTest(void) {
    DebugMenu_SoundTest();
    PlayMusic(DEBUG_MENU_MUSIC);
}

void Handler_Subgame(void) {
    // TODO: Implement this function
}

void Handler_Anime(void) {
    // TODO: Implement this function
}

void Handler_Graphics(void) {
    // TODO: Implement this function
    DebugMenu_GFXTest();
    PlayMusic(DEBUG_MENU_MUSIC);
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
    PlayMusic(DEBUG_MENU_MUSIC);
}

void Handler_Pics(void) {
    // TODO: Implement this function
    DebugMenu_Pics();
    PlayMusic(DEBUG_MENU_MUSIC);
}

void Handler_Script(void) {
    DebugMenu_Scripting();
    PlayMusic(DEBUG_MENU_MUSIC);
}

void Handler_TradeAnim(void) {
    DebugMenu_TradeAnim();
    PlayMusic(DEBUG_MENU_MUSIC);
}

void Handler_BattleAnim(void) {
    DebugMenu_BattleAnim();
    PlayMusic(DEBUG_MENU_MUSIC);
}

void Handler_Credits(void) {
    DebugMenu_Credits();
    PlayMusic(DEBUG_MENU_MUSIC);
}

void Handler_MysteryGift(void) {
    DebugMenu_MysteryGift();
    PlayMusic(DEBUG_MENU_MUSIC);
}

void Handler_News(void) {
    DebugMenu_News();
    PlayMusic(DEBUG_MENU_MUSIC);
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
    [SFX_WARP_TO] = "WARP TO@",
    [SFX_WARP_FROM] = "WARP FROM@",
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
    PlayMusic(MUSIC_NONE);
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
        GetJoypad_Conv2();
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
            PlayMusic(MUSIC_NONE);
            DelayFrame();
        }
        if(hram->hJoyPressed & (SELECT)) 
            break;
        if(hram->hJoyPressed & (A_BUTTON)) {
            if(editingWhich == 0) {
                PlayMusic(MUSIC_NONE);
                DelayFrame();
                PlayMusic(musicTrack);
            } else {
                PlaySFX(sound);
            }
        }
        DelayFrame();
    }
    PlayMusic(MUSIC_NONE);
    ClearBox_Conv2(wram->wTilemap + coordidx(0, 0), SCREEN_WIDTH, SCREEN_HEIGHT);
    DelayFrame();
}

static void DebugMenu_BattleTest_StartBattle(uint8_t tclass, uint8_t tid) {
    ClearTilemap_Conv2();
    WaitBGMap_Conv();
    DelayFrames(10);
    wram->wMapTileset = TILESET_JOHTO;
    LoadMapTileset_Conv2();

    // Rival name and Player name are null by default. 
    U82CB(wram->wRivalName, NAME_LENGTH, "???@");
    U82CB(wram->wPlayerName, NAME_LENGTH, "PLAYER@");

    wram->wBattleType = BATTLETYPE_NORMAL;
    wram->wInBattleTowerBattle = 0;
    wram->wLinkMode = LINK_NULL;

    wram->wBattleScriptFlags = (1 << 7) | 1;
    wram->wOtherTrainerClass = tclass;
    wram->wOtherTrainerID = tid;

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
    // {
    //     wbank_push(MBANK(awPartyMon1));
    //     PREDEF(pTryAddMonToParty);
    //     wbank_pop;
    // }
    TryAddMonToParty_Conv(DRAGONITE, 100);
    wbank_push(MBANK(awInBattleTowerBattle));
    StartBattle_Conv();

    bit_reset(wram->wDebugFlags, DEBUG_BATTLE_F);

    wbank_pop;
    ClearTilemap_Conv2();
    WaitBGMap_Conv();
    LoadFontsExtra_Conv();
    LoadStandardFont_Conv();
    PlayMusic(MUSIC_NONE);
    DelayFrame();
}

static void DebugMenu_BattleTest_GetNextTrainer(uint8_t* tclass, uint8_t* tid) {
    if(++(*tid) <= TrainerGroups[*tclass - 1].count) {
        return;
    }
    else if(++(*tclass) <= NUM_TRAINER_CLASSES) {
        *tid = 1;
        return;
    }
    *tclass = FALKNER;
    *tid = FALKNER1;
}

static void DebugMenu_BattleTest_GetNextTrainerClass(uint8_t* tclass, uint8_t* tid) {
    if(++(*tclass) > NUM_TRAINER_CLASSES) {
        *tclass = FALKNER;
        *tid = FALKNER1;
        return;
    }
    while(TrainerGroups[*tclass - 1].count == 0) {
        if(++(*tclass) > NUM_TRAINER_CLASSES) {
            *tclass = FALKNER;
            *tid = FALKNER1;
            return;
        }
    }
    *tid = 1;
}

static void DebugMenu_BattleTest_GetPrevTrainer(uint8_t* tclass, uint8_t* tid) {
    if(*tid == 1) {
        if(*tclass == FALKNER) {
            *tclass = NUM_TRAINER_CLASSES;
            *tid = 1;
            return;
        }
        do {
            --(*tclass);
            if(*tclass == FALKNER) {
                *tclass = NUM_TRAINER_CLASSES;
                *tid = 1;
                return;
            }
        } while(TrainerGroups[*tclass - 1].count == 0);
        *tid = TrainerGroups[*tclass - 1].count;
        return;
    }
    --(*tid);
}

static void DebugMenu_BattleTest_GetPrevTrainerClass(uint8_t* tclass, uint8_t* tid) {
    if(--(*tclass) == 0) {
        *tclass = NUM_TRAINER_CLASSES;
        *tid = 1;
        return;
    }
    while(TrainerGroups[*tclass - 1].count == 0) {
        if((*tclass)-- == 0) {
            *tclass = NUM_TRAINER_CLASSES;
            *tid = 1;
            return;
        }
    }
    *tid = 1;
}

void DebugMenu_BattleTest_PlaceTrainerName(uint8_t tclass, uint8_t tid) {
    char buffer[32];
    sprintf(buffer, "CLASS- %s", TrainerClassNames[tclass - 1]);
    PlaceStringSimple(U82C(buffer), wram->wTilemap + coordidx(0, 2));
    sprintf(buffer, "   ID- %02d:%02d", tclass, tid);
    PlaceStringSimple(U82C(buffer), wram->wTilemap + coordidx(0, 4));
    sprintf(buffer, " NAME- %s", TrainerGroups[tclass - 1].parties[tid - 1].name);
    PlaceStringSimple(U82C(buffer), wram->wTilemap + coordidx(0, 6));
}

void DebugMenu_BattleTest(void) {
    PlayMusic(MUSIC_NONE);
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
        GetJoypad_Conv2();
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
    PlayMusic(MUSIC_NONE);
    ClearBox_Conv2(wram->wTilemap + coordidx(0, 0), SCREEN_WIDTH, SCREEN_HEIGHT);
    DelayFrame();
}

void DebugMenu_GFXTest(void) {
    hram->hBGMapMode = 0;
    ClearBox_Conv2(wram->wTilemap + coordidx(0, 0), SCREEN_WIDTH, SCREEN_HEIGHT);
    ByteFill(vram->vTiles0, 2048, 0);
    ByteFill(vram->vTiles1, 2048, 0);
    ByteFill(vram->vTiles2, 2048, 0);
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
        GetJoypad_Conv2();
        if(hram->hJoyPressed & (B_BUTTON)) 
            break;
        if(hram->hJoyPressed & (A_BUTTON))  {
            hram->hGraphicStartTile = 0;
            PlaceGraphic_Conv(coord(0, 0, wram->wTilemap), 7, 7);
        }
        DelayFrame();
    }

    ClearBox_Conv2(wram->wTilemap + coordidx(0, 0), SCREEN_WIDTH, SCREEN_HEIGHT);
    ByteFill(vram->vTiles0, 2048, 0);
    ByteFill(vram->vTiles1, 2048, 0);
    ByteFill(vram->vTiles2, 2048, 0);
    v_LoadFontsExtra1_Conv();
    v_LoadFontsExtra2_Conv();
    v_LoadStandardFont_Conv();
    DelayFrame();
}

void DebugMenu_Stats(void) {
    DebugMenu_SaveAttrmap();
    Utf8ToCrystalBuffer(wram->wPlayerName, NAME_LENGTH, "PLAYER@");

    wram->wCurPartySpecies = CHARIZARD;
    wram->wCurPartyLevel = 100;
    wram->wPartyCount = 0;
    wram->wMonType = PARTYMON;
    TryAddMonToParty_Conv(CHARIZARD, 100);

    wram->wCurPartyMon = 0;

    StatsScreenInit();

    DebugMenu_RestoreAttrmap();
    ClearScreen_Conv2();
    v_LoadFontsExtra1_Conv();
    v_LoadFontsExtra2_Conv();
    v_LoadStandardFont_Conv();
    SetPalettes_Conv();
    // TextboxPalette_Conv2(wram->wTilemap, SCREEN_WIDTH, SCREEN_HEIGHT);
    WaitBGMap2_Conv();
    // DelayFrame();
}

void DebugMenu_Pics_PlaceStrings(species_t* sp) {
    char buf[32];
    sprintf(buf, "ID   - %03d@", *sp);
    PlaceStringSimple(U82C(buf), coord(0, 0, wram->wTilemap));
    uint8_t size = BasePokemonData[*sp - 1].picSize;
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
    DebugMenu_SaveTilemap();
    DebugMenu_SaveAttrmap();
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
        GetJoypad_Conv2();

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

    DebugMenu_RestoreTilemap();
    DebugMenu_RestoreAttrmap();
    v_LoadFontsExtra1_Conv();
    v_LoadFontsExtra2_Conv();
    v_LoadStandardFont_Conv();
    TextboxPalette_Conv2(wram->wTilemap, SCREEN_WIDTH - 2, SCREEN_HEIGHT - 2);
    ClearScreen_Conv2();
    WaitBGMap2_Conv();
    // DelayFrame();
}

static const txt_cmd_s DebugMenu_TestText[] = {
    text_start("This text was"
        t_line "written in C."
        t_para "Isn't that"
        t_line "pretty cool?"
        t_done )
    text_end
};

static const txt_cmd_s DebugMenu_TestText_Yes[] = {
    text_start("Yeah!"
        t_prompt )
    text_end
};

static const txt_cmd_s DebugMenu_TestText_No[] = {
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
    ByteFill(vram->vTiles0, 2048, 0);
    ByteFill(vram->vTiles1, 2048, 0);
    ByteFill(vram->vTiles2, 2048, 0);
    v_LoadFontsExtra1_Conv();
    v_LoadFontsExtra2_Conv();
    v_LoadStandardFont_Conv();
    TextboxPalette_Conv2(wram->wTilemap, SCREEN_WIDTH - 2, SCREEN_HEIGHT - 2);
    WaitBGMap_Conv();
    DelayFrame();
}

#include "../link/lan.h"
#include "../../util/network.h"

const txt_cmd_s Text_LANTestSuccess[] = {
    text_start("LAN test was"
        t_line "successful!"
        t_prompt )
};

const txt_cmd_s Text_LANTestFail[] = {
    text_start("LAN test failed!"
        t_prompt )
};

void DebugMenu_Link(void) {
    DebugMenu_SaveTilemap();
    DebugMenu_SaveAttrmap();
    ClearScreen_Conv2();
    v_LoadFontsExtra1_Conv();
    v_LoadFontsExtra2_Conv();
    v_LoadStandardFont_Conv();
    WaitBGMap_Conv();

    OpenSRAM_Conv(MBANK(asPlayerData));
    CopyBytes_GB(wCrystalData, sCrystalData, wCrystalDataEnd - wCrystalData);
    CopyBytes_GB(wPlayerID, sPlayerData + (wPlayerID - wPlayerData), 2);
    CopyBytes_GB(wPlayerName, sPlayerData + (wPlayerName - wPlayerData), NAME_LENGTH);
    CloseSRAM_Conv();

    printf("NAME: "); PrintCrystalStringFromRAM(wram->wPlayerName); printf("\n");
    printf("GENDER: %s\n", (bit_test(wram->wPlayerGender, PLAYERGENDER_FEMALE_F))? "FEMALE": "MALE");
    printf("ID: %d\n", wram->wPlayerID);

    LANConnection();
    
    LoadStandardMenuHeader_Conv();
    if(wram->wScriptVar == FALSE) {
        PrintText_Conv2(Text_LANTestFail);
    }
    else {
        PrintText_Conv2(Text_LANTestSuccess);
    }
    CloseWindow_Conv2();

    NetworkCloseConnection();
    ClearScreen_Conv2();
    DelayFrames(4);
    DebugMenu_RestoreTilemap();
    DebugMenu_RestoreAttrmap();
    v_LoadFontsExtra1_Conv();
    v_LoadFontsExtra2_Conv();
    v_LoadStandardFont_Conv();
}

void DebugMenu_TradeAnim(void) {
    DebugMenu_SaveTilemap();
    DebugMenu_SaveAttrmap();
    ClearScreen_Conv2();
    wram->wPlayerTrademon.species = BULBASAUR;
    wram->wOTTrademon.species = CHARMANDER;
    U82CA(wram->wPlayerTrademon.otName, "PLAYER@");
    U82CA(wram->wOTTrademon.otName, "PLAYER@");
    U82CA(wram->wPlayerTrademon.speciesName, "A@");
    U82CA(wram->wOTTrademon.speciesName, "A@");
    U82CA(wram->wPlayerTrademon.senderName, "A@");
    U82CA(wram->wOTTrademon.senderName, "B@");
    U82CA(wram->wPlayerTrademon.nickname, "A@");
    U82CA(wram->wOTTrademon.nickname, "A@");
    TradeAnimation();
    DebugMenu_RestoreTilemap();
    DebugMenu_RestoreAttrmap();
    v_LoadFontsExtra1_Conv();
    v_LoadFontsExtra2_Conv();
    v_LoadStandardFont_Conv();
}

static void DebugMenu_BattleAnim_PlaceText(uint16_t move) {
    char buffer[64];
    sprintf(buffer, "MOVE - 0x%02X@", move);
    PlaceStringSimple(U82C(buffer), coord(TEXTBOX_INNERX, TEXTBOX_Y + 1, wram->wTilemap));
    sprintf(buffer, "TURN - %s@", (hram->hBattleTurn == TURN_PLAYER)? "PLAYER": "ENEMY");
    PlaceStringSimple(U82C(buffer), coord(TEXTBOX_INNERX, TEXTBOX_Y + 2, wram->wTilemap));
    sprintf(buffer, "B - BACK@");
    PlaceStringSimple(U82C(buffer), coord(TEXTBOX_INNERX, TEXTBOX_Y + 3, wram->wTilemap));
}

void DebugMenu_BattleAnim(void) {
    DebugMenu_SaveTilemap();
    DebugMenu_SaveAttrmap();
    ClearScreen_Conv2();
    uint16_t anim = NO_MOVE + 1;

    uint8_t options = wram->wOptions;
    wram->wOptions &= 0xfc;

// Add Pokemon to party
    wram->wCurPartySpecies = PIKACHU;
    wram->wCurPartyLevel = 50;
    wram->wPartyCount = 0;
    wram->wMonType = PARTYMON;
    // {
    //     wbank_push(MBANK(awPartyMon1));
    //     PREDEF(pTryAddMonToParty);
    //     wbank_pop;
    // }
    TryAddMonToParty_Conv(PIKACHU, 50);
    U82CA(wram->wBattleMonNickname, "PIKACHU@");

    wram->wCurPartySpecies = CHARIZARD;
    wram->wCurPartyLevel = 50;
    wram->wPartyCount = 0;
    wram->wMonType = OTPARTYMON;
    // {
    //     wbank_push(MBANK(awOTPartyMon1));
    //     PREDEF(pTryAddMonToParty);
    //     wbank_pop;
    // }
    TryAddMonToParty_Conv(CHARIZARD, 50);
    U82CA(wram->wEnemyMonNickname, "CHARIZARD@");

    wram->wCurPartyMon = 0;
    wram->wCurOTMon = 0;

    LoadEnemyMonToSwitchTo_Conv(0);
    UpdateEnemyHUD();
    InitBattleMon();
    UpdatePlayerHUD();
    v_LoadBattleFontsHPBar();
    GetBattleMonBackpic();
    wram->wTempBattleMonSpecies = wram->wPartyMon[0].mon.species;
    wram->wTempEnemyMonSpecies = wram->wOTPartySpecies[0];
    GetSGBLayout_Conv(SCGB_BATTLE_COLORS);
    hram->hGraphicStartTile = 0x31;
    PlaceGraphicYStagger_Conv(coord(2, 6, wram->wTilemap), 6, 6);
    GetEnemyMonFrontpic();
    hram->hGraphicStartTile = 0;
    PlaceGraphicYStagger_Conv(coord(12, 0, wram->wTilemap), 7, 7);
    SpeechTextbox_Conv2();
    DebugMenu_BattleAnim_PlaceText(anim);
    ApplyTilemap_Conv();

    while(1) {
        GetJoypad_Conv2();
        if(hram->hJoyPressed & (B_BUTTON))
            break;
        
        int8_t dir = -((hram->hJoyPressed & D_LEFT)? 1: 0) + ((hram->hJoyPressed & D_RIGHT)? 1: 0);
        int8_t dir2 = -((hram->hJoyPressed & D_DOWN)? 1: 0) + ((hram->hJoyPressed & D_UP)? 1: 0);

        if(dir < 0) {
            anim--;
            if(anim == NO_MOVE) anim = NUM_BATTLE_ANIMS + 1;
            SpeechTextbox_Conv2();
            DebugMenu_BattleAnim_PlaceText(anim);
        }
        else if(dir > 0) {
            anim++;
            if(anim > NUM_BATTLE_ANIMS + 1) anim = NO_MOVE + 1;
            SpeechTextbox_Conv2();
            DebugMenu_BattleAnim_PlaceText(anim);
        }

        if(dir2 < 0) {
            if(anim < NO_MOVE + 10) anim = NO_MOVE + 1;
            else anim -= 10;
            SpeechTextbox_Conv2();
            DebugMenu_BattleAnim_PlaceText(anim);
        }
        else if(dir2 > 0) {
            if(anim > (NUM_BATTLE_ANIMS + 1) - 10) anim = NUM_BATTLE_ANIMS + 1;
            else anim += 10;
            SpeechTextbox_Conv2();
            DebugMenu_BattleAnim_PlaceText(anim);
        }

        if(hram->hJoyPressed & SELECT) {
            hram->hBattleTurn ^= 1;
            SpeechTextbox_Conv2();
            DebugMenu_BattleAnim_PlaceText(anim);
        }

        if(hram->hJoyPressed & (A_BUTTON)) {
            if(anim == NUM_BATTLE_ANIMS + 1) {
                wram->wFXAnimID = ANIM_THROW_POKE_BALL;
                wram->wBattleAnimParam = POKE_BALL;
            }
            else if(anim == GROWL || anim == ROAR) {
                wram->wFXAnimID = anim;
                wram->wBattleAnimParam = (hram->hBattleTurn == TURN_PLAYER)? wram->wBattleMon.species: wram->wEnemyMon.species;
            }
            else {
                wram->wFXAnimID = anim;
                wram->wBattleAnimParam = 0;
            }
            wram->wNumHits = 1;
            WaitBGMap_Conv();
            PlayBattleAnim();
            FinishBattleAnim();
            EmptyBattleTextbox();
            DebugMenu_BattleAnim_PlaceText(anim);
        }
        DelayFrame();
    }
    wram->wOptions = options;
    ClearScreen_Conv2();
    DelayFrames(4);
    DebugMenu_RestoreTilemap();
    DebugMenu_RestoreAttrmap();
    v_LoadFontsExtra1_Conv();
    v_LoadFontsExtra2_Conv();
    v_LoadStandardFont_Conv();
}

void DebugMenu_Credits(void) {
    ClearScreen_Conv2();
    InitDisplayForRedCredits();
    Credits(0);
}

void DebugMenu_TradeTest(void) {
    DebugMenu_SaveTilemap();
    DebugMenu_SaveAttrmap();
    ClearScreen_Conv2();
    U82CA(wram->wPlayerName, "PLAYER@");
    U82CA(wram->wOTPlayerName, "OTHER@");
    wram->wPartyCount = 1;
    wram->wPartySpecies[0] = TEDDIURSA;
    wram->wPartySpecies[1] = (species_t)-1;
    wram->wPartyMon[0].mon.species = TEDDIURSA;
    U82CA(wram->wPartyMonNickname[0], "KODA@");
    wram->wOTPartyCount = 1;
    wram->wOTPartySpecies[0] = MEOWTH;
    wram->wOTPartySpecies[1] = (species_t)-1;
    wram->wOTPartyMon[0].mon.species = MEOWTH;
    U82CA(wram->wOTPartyMonNickname[0], "MORGANA@");
    LinkComms_LoadPleaseWaitTextboxBorderGFX();
    SetTradeRoomBGPals();
    WaitBGMap2_Conv();
    PlayMusic(MUSIC_ROUTE_30);
    InitTradeMenuDisplay();
    DebugMenu_RestoreTilemap();
    DebugMenu_RestoreAttrmap();
    v_LoadFontsExtra1_Conv();
    v_LoadFontsExtra2_Conv();
    v_LoadStandardFont_Conv();
}

void DebugMenu_MysteryGift(void) {
    DebugMenu_SaveTilemap();
    DebugMenu_SaveAttrmap();
    ClearScreen_Conv2();

    DoMysteryGift();

    DebugMenu_RestoreTilemap();
    DebugMenu_RestoreAttrmap();
    v_LoadFontsExtra1_Conv();
    v_LoadFontsExtra2_Conv();
    v_LoadStandardFont_Conv();
}

const txt_cmd_s Text_NewsMenuTop[] = {
    text_start("What would you"
        t_line "like to do?"
        t_done )
};

const txt_cmd_s Text_NewsDeleteConfirm[] = {
    text_start("Delete the news?"
        t_done )
};

const txt_cmd_s Text_NewsDeleted[] = {
    text_start("News deleted."
        t_prompt )
};

const txt_cmd_s Text_NewsIsCorrupt[] = {
    text_start("News is corrupt."
        t_prompt )
};

const txt_cmd_s Text_NewsIsOk[] = {
    text_start("News is OK."
        t_prompt )
};

static const struct MenuHeader Menu_NewsMenu = {
    .flags = MENU_BACKUP_TILES, // flags
    .coord = menu_coords(0, 4, 15, TEXTBOX_Y - 1), 
    .data = &(struct MenuData){
    // .MenuData:
        .flags=STATICMENU_CURSOR, // flags
        .verticalMenu = {
            .count=3, // items
            .options = (const char* []) {
                "DELETE NEWS",
                "CHECK NEWS",
                "BACK"
            }
        },
    },
	.defaultOption=1 // default option
};

static void DebugMenu_News_DeleteNews(void) {
    OpenSRAM_Conv(MBANK(as5_aa72));
    gb_write(s5_aa72, 0);
    ByteFill(GBToRAMAddr(s5_aa73), 0xc, 0x0);
    CloseSRAM_Conv();
}

void DebugMenu_News(void) {
    DebugMenu_SaveTilemap();
    DebugMenu_SaveAttrmap();

loop:
    PrintText_Conv2(Text_NewsMenuTop);
    LoadMenuHeader_Conv2(&Menu_NewsMenu);

    bool cancel = !VerticalMenu_Conv();
    ExitMenu_Conv2();
    if(!cancel) {
        switch(wram->wMenuCursorY) {
            case 1:
                PrintText_Conv2(Text_NewsDeleteConfirm);

                if(YesNoBox_Conv()) {
                    DebugMenu_News_DeleteNews();
                    PrintText_Conv2(Text_NewsDeleted);
                }
                goto loop;
            case 2: {
                if(Function17d314()) {
                    PrintText_Conv2(Text_NewsIsCorrupt);
                }
                else {
                    PrintText_Conv2(Text_NewsIsOk);
                }
            } goto loop;
            case 3:break;
        }
    }

    DebugMenu_RestoreTilemap();
    DebugMenu_RestoreAttrmap();
    v_LoadFontsExtra1_Conv();
    v_LoadFontsExtra2_Conv();
    v_LoadStandardFont_Conv();
    DelayFrames(4);
}
