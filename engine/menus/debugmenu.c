#include <stdint.h>
#include <stdbool.h>
#include "../../constants.h"
#include "debugmenu.h"
#include "../../home/audio.h"
#include "../../home/delay.h"
#include "../../home/joypad.h"
#include "../../home/menu.h"
#include "../../home/text.h"
#include "../../charmap.h"
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

DebugMenuOption debugMenuOptions[] = {
    {"FIGHT@", Handler_Fight},
    {"LINK@", Handler_Link},
    {"FIELD@", Handler_Field},
    {"SOUND@", Handler_SoundTest},
    {"MINIGAME@", Handler_Subgame},
    {"ANIME@", Handler_Anime},
    {"GRAPHICS@", Handler_Graphics},
    {"POKEDEX@", Handler_Pokedex},
    {"POKEGEAR@", Handler_Trainergear}
};

#define MAX_OPTIONS_PER_PAGE 7

static uint8_t cursorIndex = 0;
static uint8_t currentPage = 0;

void DebugMenu_PrintStrings() {
    uint8_t* hl = wram->wTilemap + coordidx(2, 1);
    uint8_t start = currentPage * MAX_OPTIONS_PER_PAGE;
    uint8_t end = start + MAX_OPTIONS_PER_PAGE;
    if (end > sizeof(debugMenuOptions) / sizeof(DebugMenuOption)) {
        end = sizeof(debugMenuOptions) / sizeof(DebugMenuOption);
    }
    for(uint8_t i = start; i < end; ++i) {
        PlaceStringSimple(Utf8ToCrystal(debugMenuOptions[i].name), hl);
        hl = wram->wTilemap + coordidx(2, 1 + (i - start + 1) * 2);
    }
    char buf[10];
    sprintf(buf, "PAGE%d@", currentPage + 1);
    PlaceStringSimple(Utf8ToCrystal(buf), hl);
}

void DebugMenu_PlaceCursor(void) {
    wram->wTilemap[coordidx(1, cursorIndex*2 + 1)] = CHAR_RIGHT_CURSOR;
}

void DebugMenu_MoveCursor(int8_t dir) {
    wram->wTilemap[coordidx(1, cursorIndex*2 + 1)] = CHAR_SPACE;
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

void DebugMenu(void) {
    PlayMusic_Conv(MUSIC_NONE);
    DelayFrame();
    PlayMusic_Conv(MUSIC_MOBILE_ADAPTER_MENU);
    MenuBox_Conv();
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
            } else {
                debugMenuOptions[currentPage * MAX_OPTIONS_PER_PAGE + cursorIndex].handler();
            }
            PlayMusic_Conv(MUSIC_MOBILE_ADAPTER_MENU);
            MenuBox_Conv();
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
}

void Handler_Fight(void) {
    // TODO: Implement this function
}

void Handler_Link(void) {
    // TODO: Implement this function
}

void Handler_Field(void) {
    // TODO: Implement this function
}

void Handler_SoundTest(void) {
    // TODO: Implement this function
}

void Handler_Subgame(void) {
    // TODO: Implement this function
}

void Handler_Anime(void) {
    // TODO: Implement this function
}

void Handler_Graphics(void) {
    // TODO: Implement this function
}

void Handler_Pokedex(void) {
    // TODO: Implement this function
}

void Handler_Trainergear(void) {
    // TODO: Implement this function
}

static const char* DebugMenu_MusicNames[] = {
    [MUSIC_NONE] = "NONE@",
    [MUSIC_TITLE] = "TITLE@",
    [MUSIC_ROUTE_1] = "ROUTE 1@",
    [MUSIC_ROUTE_3] = "ROUTE 3@",
    [MUSIC_ROUTE_12] = "ROUTE 12@",
    [MUSIC_MAGNET_TRAIN] = "MAGNET TRAIN@",
    [MUSIC_KANTO_GYM_LEADER_BATTLE] = "BATTLE KANTO GYM@",
};

static const char* DebugMenu_SoundNames[] = {
    [SFX_DEX_FANFARE_50_79] = "DEX FAN 50 79@",
    [SFX_ITEM] = "ITEM@",
};

static void DebugMenu_SoundTest_PlaceMusicName(uint16_t track) {
    ClearBox_Conv2(wram->wTilemap + coordidx(2, 2), SCREEN_WIDTH - 4, 1);
    if(track >= lengthof(DebugMenu_MusicNames)) {
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
    if(track >= lengthof(DebugMenu_SoundNames)) {
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
