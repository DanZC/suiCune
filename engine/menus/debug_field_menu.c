#include "../../constants.h"
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
#include "../events/overworld.h"
#include "../events/specials.h"
#include "../overworld/init_map.h"
#include "../overworld/map_setup.h"
#include "../pokegear/pokegear.h"
#include "../phone/phone.h"
#include "../../util/scripting.h"

enum {
    DEBUGFIELDITEM_TELEPORT,
    DEBUGFIELDITEM_PHONE,
    DEBUGFIELDITEM_TUTORIAL,
    DEBUGFIELDITEM_UNOWN,
    DEBUGFIELDITEM_FLAG,
    DEBUGFIELDITEM_WILD_BATTLE,
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
    LoadCallerScript_Conv(0x00);
    gQueuedScriptAddr = DebugSpecialPhoneCall;
    hram->hMenuReturn = HMENURETURN_SCRIPT;
    wram->wSpecialPhoneCallID = SPECIALCALL_BIKESHOP;
}

static bool DebugShowCatchTutorialScript(script_s* s){
    SCRIPT_BEGIN
    loadwildmon(PIDGEY, 5)
    catchtutorial(BATTLETYPE_TUTORIAL)
    s_end
    SCRIPT_END
}

static void DebugShowCatchTutorial(void){
    gQueuedScriptAddr = DebugShowCatchTutorialScript;
    hram->hMenuReturn = HMENURETURN_SCRIPT;
}

static void DebugUnownPrinter(void){
    uint8_t temp[sizeof(wram->wUnownDex)];
    CopyBytes(temp, wram->wUnownDex, sizeof(wram->wUnownDex));
    for(uint8_t i = 0; i < NUM_UNOWN; ++i){
        wram->wUnownDex[i] = UNOWN_A + i;
    }
    UnownPrinter();
    CopyBytes(wram->wUnownDex, temp, sizeof(wram->wUnownDex));
}

static bool DebugWildBattleScript(script_s* s){
    SCRIPT_BEGIN
    startbattle
    reloadmapafterbattle
    s_end
    SCRIPT_END
}

static void DebugWildBattle(species_t species, uint8_t level){
    Script_loadwildmon_Conv(&gCurScript, species, level);
    gQueuedScriptAddr = DebugWildBattleScript;
    hram->hMenuReturn = HMENURETURN_SCRIPT;
}

static void DebugFlagMenu(void) {
    LoadStandardMenuHeader_Conv();
    Textbox_Conv2(coord(0, 0, wram->wTilemap), 6, 12);
    WaitBGMap_Conv();
    uint16_t flag = EVENT_TEMPORARY_UNTIL_MAP_RELOAD_1;
    while(1) {
        GetJoypad_Conv2();
        if(hram->hJoyPressed & (B_BUTTON))
            break;

        if(hram->hJoyPressed & (D_DOWN)) {
            if(flag == 0) flag = EVENT_BATTLE_TOWER_OUTSIDE_SAILOR;
            else flag--;
        }
        if(hram->hJoyPressed & (D_UP)) {
            if(flag == EVENT_BATTLE_TOWER_OUTSIDE_SAILOR) flag = 0;
            else flag++;
        }

        if(hram->hJoyPressed & (A_BUTTON)) {
            PlayClickSFX_Conv();
            if(EventFlagAction_Conv2(flag, CHECK_FLAG))
                EventFlagAction_Conv2(flag, RESET_FLAG);
            else
                EventFlagAction_Conv2(flag, SET_FLAG);
            WaitSFX();
        }

        char buffer[32];
        sprintf(buffer, "FLAG - %03d<LF>  %s@", flag, EventFlagAction_Conv2(flag, CHECK_FLAG)? "ON": "OFF");
        ClearBox_Conv2(coord(2, 2, wram->wTilemap), 11, 5);
        PlaceStringSimple(U82C(buffer), coord(2, 2, wram->wTilemap));

        DelayFrame();
    }

    CloseWindow_Conv2();
    WaitBGMap_Conv();
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
                "TUTORIAL@",
                "UNOWN@",
                "FLAG@",
                "WILD@",
                "EXIT@",
            },
        },
    },
    .defaultOption = 1,  // default option
};
    ClearWindowData_Conv2();
    PlaySFX(SFX_MENU);
    ReanchorBGMap_NoOAMUpdate_Conv();

    LoadMenuHeader_Conv2(&MenuHeader);
    SafeUpdateSprites_Conv();
    v_OpenAndCloseMenu_HDMATransferTilemapAndAttrmap_Conv();
    LoadFonts_NoOAMUpdate_Conv();
    UpdateTimePals();

loop:
    bool no_cancel = VerticalMenu_Conv();

    if(no_cancel) {
        switch(wram->wMenuCursorY - 1) {
        case DEBUGFIELDITEM_TELEPORT: {
            FadeToMenu_Conv();
            hram->hMapAnims = 0;
            ClearSprites();
            LoadStandardMenuHeader_Conv();
            uint8_t spawn = EntireFlyMap();
            if(spawn == 0xff || spawn >= NUM_SPAWNS) {
                CloseWindow_Conv2();
                // WaitBGMap_Conv();
                ExitAllMenus_Conv();
                break;
            }
            gQueuedScriptAddr = DebugTeleportScript;
            wram->wDefaultSpawnpoint = spawn;
            CloseWindow_Conv2();
            hram->hMenuReturn = HMENURETURN_SCRIPT;
            ExitAllMenus_Conv();
        } break;
        case DEBUGFIELDITEM_FLAG:
            DebugFlagMenu();
            goto loop;
        case DEBUGFIELDITEM_PHONE:
            DebugPhoneCall();
            break;
        case DEBUGFIELDITEM_TUTORIAL:
            DebugShowCatchTutorial();
            break;
        case DEBUGFIELDITEM_UNOWN:
            DebugUnownPrinter();
            goto loop;
        case DEBUGFIELDITEM_WILD_BATTLE:
            DebugWildBattle(CHARIZARD, 45);
            break;
        case DEBUGFIELDITEM_EXIT:
            break;
        }
    }
    uint8_t oamUpdate = hram->hOAMUpdate;
    hram->hOAMUpdate = 1;
    LoadFontsExtra_Conv();
    hram->hOAMUpdate = oamUpdate;
    CloseWindow_Conv2();
    v_OpenAndCloseMenu_HDMATransferTilemapAndAttrmap_Conv();
    hram->hBGMapMode = 0;
}