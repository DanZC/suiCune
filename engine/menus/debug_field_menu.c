#include "../../constants.h"
#include "menu_2.h"
#include "../../home/menu.h"
#include "../../home/delay.h"
#include "../../home/copy.h"
#include "../../home/audio.h"
#include "../../home/tilemap.h"
#include "../../home/window.h"
#include "../../home/queue_script.h"
#include "../../home/clear_sprites.h"
#include "../../home/map.h"
#include "../../home/gfx.h"
#include "../../home/time_palettes.h"
#include "../../home/flag.h"
#include "../../home/joypad.h"
#include "../../home/text.h"
#include "../../home/scrolling_menu.h"
#include "../events/overworld.h"
#include "../events/specials.h"
#include "../overworld/init_map.h"
#include "../overworld/map_setup.h"
#include "../pokemon/move_mon.h"
#include "../pokegear/pokegear.h"
#include "../phone/phone.h"
#include "../../mobile/mobile_5f.h"
#include "../../util/scripting.h"

enum {
    DEBUGFIELDITEM_TELEPORT,
    DEBUGFIELDITEM_PHONE,
    DEBUGFIELDITEM_TUTORIAL,
    DEBUGFIELDITEM_UNOWN,
    DEBUGFIELDITEM_FLAG,
    DEBUGFIELDITEM_WILD_BATTLE,
    DEBUGFIELDITEM_MOBILE,
    DEBUGFIELDITEM_EXIT,
    DEBUGFIELDITEM_COUNT,
};

static bool DebugTeleportScript(script_s* s) {
    static uint8_t TeleportFrom[] = {
        movement_teleport_from,
        movement_step_end
    };
    static uint8_t TeleportTo[] = {
        movement_teleport_to,
        movement_step_end
    };
    SCRIPT_BEGIN
    reloadmappart
    playsound(SFX_WARP_TO)
    HideSprites();
    special(UpdateTimePals)
    applymovement(PLAYER, TeleportFrom)
    special(WarpToSpawnPoint)
    SkipUpdateMapSprites();
    waitsfx
    loadvar(VAR_MOVEMENT, PLAYER_NORMAL)
    newloadmap(MAPSETUP_TELEPORT)
    playsound(SFX_WARP_FROM)
    applymovement(PLAYER, TeleportTo)
    s_end
    SCRIPT_END
}

static bool DebugSpecialPhoneCall(script_s* s){
    SCRIPT_BEGIN
    pause(15)
    sjump(Script_ReceivePhoneCall)
    SCRIPT_END
}

static void DebugPhoneCall(void){
    LoadCallerScript(0x00);
    gQueuedScriptAddr = DebugSpecialPhoneCall;
    hram.hMenuReturn = HMENURETURN_SCRIPT;
    gPlayer.specialPhoneCallID = SPECIALCALL_BIKESHOP;
}

// static bool DebugShowCatchTutorialScript(script_s* s){
//     SCRIPT_BEGIN
//     loadwildmon(PIDGEY, 5)
//     catchtutorial(BATTLETYPE_TUTORIAL)
//     s_end
//     SCRIPT_END
// }

// static void DebugShowCatchTutorial(void){
//     gQueuedScriptAddr = DebugShowCatchTutorialScript;
//     hram.hMenuReturn = HMENURETURN_SCRIPT;
// }

static void DebugAddPokemon(species_t species, uint8_t level, item_t item) {
    wram->wCurPartySpecies = species;
    wram->wCurPartyLevel = level;
    wram->wCurItem = item;
    GivePoke(0, NULL, NULL);
}

static struct MenuHeader DebugWildBattleMenu_MenuHeader = {
    .coord = menu_coords(0, 0, 15, 8),
    .flags = MENU_BACKUP_TILES,
    .data = NULL,
    .defaultOption = 0,
};

static void DebugAddPokemonMenu(void) {
    LoadStandardMenuHeader();
    Textbox(coord(0, 0, wram->wTilemap), 8, 15);
    WaitBGMap();
    species_t species = BULBASAUR;
    uint8_t level = 2;
    while(1) {
        GetJoypad();
        if(hram.hJoyPressed & (B_BUTTON))
            break;

        if(hram.hJoyPressed & (D_DOWN)) {
            if(species == BULBASAUR) species = NUM_POKEMON;
            else --species;
        }
        if(hram.hJoyPressed & (D_UP)) {
            if(species == NUM_POKEMON) species = BULBASAUR;
            else ++species;
        }

        if(hram.hJoyPressed & (D_LEFT)) {
            if(level > 5) --level; else level = 100;
        }
        if(hram.hJoyPressed & (D_RIGHT)) {
            if(level < 100) ++level; else level = 5;
        }

        if(hram.hJoyPressed & (A_BUTTON)) {
            PlayClickSFX();
            WaitSFX();
            CloseWindow();
            WaitBGMap();
            DebugAddPokemon(species, level, NO_ITEM);
            return;
        }

        char buffer[48];
        sprintf(buffer, "SPECIES - % 3d<LF>"
                        "LVL     - % 3d", species, level);
        ClearBox(coord(2, 2, wram->wTilemap), 11, 6);
        PlaceStringSimple(U82C(buffer), coord(2, 2, wram->wTilemap));

        DelayFrame();
    }

    CloseWindow();
    WaitBGMap();
}

static void DebugUnownPrinter(void){
    uint8_t temp[sizeof(gPokemon.unownDex)];
    CopyBytes(temp, gPokemon.unownDex, sizeof(gPokemon.unownDex));
    for(uint8_t i = 0; i < NUM_UNOWN; ++i){
        gPokemon.unownDex[i] = UNOWN_A + i;
    }
    UnownPrinter();
    CopyBytes(gPokemon.unownDex, temp, sizeof(gPokemon.unownDex));
}

static bool DebugWildBattleScript(script_s* s){
    SCRIPT_BEGIN
    startbattle
    reloadmapafterbattle
    s_end
    SCRIPT_END
}

static void DebugWildBattle(species_t species, uint8_t level){
    Script_loadwildmon(&gCurScript, species, level);
    gQueuedScriptAddr = DebugWildBattleScript;
    hram.hMenuReturn = HMENURETURN_SCRIPT;
}

static void DebugWildBattleMenu(void) {
    LoadMenuHeader(&DebugWildBattleMenu_MenuHeader);
    Textbox(coord(0, 0, wram->wTilemap), 8, 15);
    WaitBGMap();
    species_t species = BULBASAUR;
    uint8_t level = 2;
    while(1) {
        GetJoypad();
        if(hram.hJoyPressed & (B_BUTTON))
            break;

        if(hram.hJoyPressed & (D_DOWN)) {
            if(species == BULBASAUR) species = NUM_POKEMON;
            else --species;
        }
        if(hram.hJoyPressed & (D_UP)) {
            if(species == NUM_POKEMON) species = BULBASAUR;
            else ++species;
        }

        if(hram.hJoyPressed & (D_LEFT)) {
            if(level > 5) --level; else level = 100;
        }
        if(hram.hJoyPressed & (D_RIGHT)) {
            if(level < 100) ++level; else level = 5;
        }

        if(hram.hJoyPressed & (A_BUTTON)) {
            PlayClickSFX();
            WaitSFX();
            CloseWindow();
            WaitBGMap();
            DebugWildBattle(species, level);
            return;
        }

        char buffer[48];
        sprintf(buffer, "SPECIES - % 3d<LF>"
                        "LVL     - % 3d", species, level);
        ClearBox(coord(2, 2, wram->wTilemap), 11, 6);
        PlaceStringSimple(U82C(buffer), coord(2, 2, wram->wTilemap));

        DelayFrame();
    }

    CloseWindow();
    WaitBGMap();
}

enum {
    DEBUGMOBILE_DOWNLOAD_NEWS,
    DEBUGMOBILE_BACK,
    DEBUGMOBILE_COUNT,
};

const struct MenuHeader DebugMobileConnection_Menu = {
    .flags = MENU_BACKUP_TILES,  // flags
    .coord = menu_coords(1, 1, 16, 10),
    .data = &(struct MenuData) {
        .flags = STATICMENU_CURSOR,
        .verticalMenu = {
            .count = DEBUGMOBILE_COUNT,
            .options = (const char*[]) {
                [DEBUGMOBILE_DOWNLOAD_NEWS] = "DOWNLOAD NEWS",
                [DEBUGMOBILE_BACK] = "BACK",
            },
        },
    },
    .defaultOption = DEBUGMOBILE_BACK,
};

static void DebugMobileConnection(void) {
    LoadMenuHeader(&DebugMobileConnection_Menu);
    bool cancel = VerticalMenu();
    if(!cancel && wram->wMenuCursorY != DEBUGMOBILE_COUNT) {
        switch(wram->wMenuCursorY - 1) {
            case DEBUGMOBILE_DOWNLOAD_NEWS: Function17d2b6(); break;
            case DEBUGMOBILE_BACK: break;
        }
    }
    ExitMenu();
    return;
}

static void DebugFlagMenu(void) {
    LoadStandardMenuHeader();
    Textbox(coord(0, 0, wram->wTilemap), 6, 12);
    WaitBGMap();
    uint16_t flag = EVENT_TEMPORARY_UNTIL_MAP_RELOAD_1;
    while(1) {
        GetJoypad();
        if(hram.hJoyPressed & (B_BUTTON))
            break;

        if(hram.hJoyPressed & (D_DOWN)) {
            if(flag == 0) flag = EVENT_BATTLE_TOWER_OUTSIDE_SAILOR;
            else flag--;
        }
        if(hram.hJoyPressed & (D_UP)) {
            if(flag == EVENT_BATTLE_TOWER_OUTSIDE_SAILOR) flag = 0;
            else flag++;
        }

        if(hram.hJoyPressed & (A_BUTTON)) {
            PlayClickSFX();
            if(EventFlagAction(flag, CHECK_FLAG))
                EventFlagAction(flag, RESET_FLAG);
            else
                EventFlagAction(flag, SET_FLAG);
            WaitSFX();
        }

        char buffer[32];
        sprintf(buffer, "FLAG - %03d<LF>  %s@", flag, EventFlagAction(flag, CHECK_FLAG)? "ON": "OFF");
        ClearBox(coord(2, 2, wram->wTilemap), 11, 5);
        PlaceStringSimple(U82C(buffer), coord(2, 2, wram->wTilemap));

        DelayFrame();
    }

    CloseWindow();
    WaitBGMap();
}

void DebugFieldMenu(void) {
const struct MenuHeader MenuHeader = {
    .flags = MENU_BACKUP_TILES,  // flags
    .coord = menu_coords(9, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1),
    //dw ['.MenuData'];
    .data = &(struct MenuData) {
    // MenuData:
        .flags = STATICMENU_CURSOR | STATICMENU_WRAP,  // flags
        .verticalMenu = {
            .count = DEBUGFIELDITEM_COUNT,  // items
            .options = (const char*[]) {
                "TELEPORT@",
                "PHONE@",
                "POKEMON@",
                "UNOWN@",
                "FLAG@",
                "WILD@",
                "MOBILE",
                "EXIT@",
            },
        },
    },
    .defaultOption = 1,  // default option
};
    ClearWindowData();
    PlaySFX(SFX_MENU);
    ReanchorBGMap_NoOAMUpdate();

    LoadMenuHeader(&MenuHeader);
    SafeUpdateSprites();
    v_OpenAndCloseMenu_HDMATransferTilemapAndAttrmap();
    LoadFonts_NoOAMUpdate();
    UpdateTimePals();

    loop: {
        bool cancel = VerticalMenu();

        if(!cancel) {
            switch(wram->wMenuCursorY - 1) {
            case DEBUGFIELDITEM_TELEPORT: {
                FadeToMenu();
                hram.hMapAnims = 0;
                ClearSprites();
                LoadStandardMenuHeader();
                uint8_t spawn = EntireFlyMap();
                if(spawn == 0xff || spawn >= NUM_SPAWNS) {
                    CloseWindow();
                    // WaitBGMap();
                    ExitAllMenus();
                    break;
                }
                gQueuedScriptAddr = DebugTeleportScript;
                wram->wDefaultSpawnpoint = spawn;
                CloseWindow();
                hram.hMenuReturn = HMENURETURN_SCRIPT;
                ExitAllMenus();
            } break;
            case DEBUGFIELDITEM_FLAG:
                DebugFlagMenu();
                goto loop;
            case DEBUGFIELDITEM_PHONE:
                DebugPhoneCall();
                break;
            case DEBUGFIELDITEM_TUTORIAL:
                DebugAddPokemonMenu();
                goto loop;
            case DEBUGFIELDITEM_UNOWN:
                DebugUnownPrinter();
                goto loop;
            case DEBUGFIELDITEM_WILD_BATTLE:
                DebugWildBattleMenu();
                break;
            case DEBUGFIELDITEM_MOBILE:
                DebugMobileConnection();
                goto loop;
            case DEBUGFIELDITEM_EXIT:
                break;
            }
        }
    }
    uint8_t oamUpdate = hram.hOAMUpdate;
    hram.hOAMUpdate = 1;
    LoadFontsExtra();
    hram.hOAMUpdate = oamUpdate;
    CloseWindow();
    v_OpenAndCloseMenu_HDMATransferTilemapAndAttrmap();
    hram.hBGMapMode = BGMAPMODE_NONE;
}