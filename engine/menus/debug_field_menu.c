#include "../../constants.h"
#include "../../home/menu.h"
#include "../../home/delay.h"
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
#include "../overworld/init_map.h"
#include "../overworld/map_setup.h"
#include "../pokegear/pokegear.h"
#include "../../util/scripting.h"

enum {
    DEBUGFIELDITEM_TELEPORT,
    DEBUGFIELDITEM_FLAG,
    DEBUGFIELDITEM_EXIT,
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
    // reloadmappart
    playsound(SFX_WARP_TO)
    HideSprites_Conv();
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

static void DebugFlagMenu(void) {
    LoadStandardMenuHeader_Conv();
    Textbox_Conv2(coord(0, 0, wram->wTilemap), 6, 12);
    WaitBGMap_Conv();
    uint16_t flag = EVENT_TEMPORARY_UNTIL_MAP_RELOAD_1;
    while(1) {
        GetJoypad_Conv();
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
            WaitSFX_Conv();
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
            .count = 2,  // items
            .options = (const char*[]) {
                "TELEPORT@",
                "FLAG@",
                "EXIT@",
            },
        },
    },
    .defaultOption = 1,  // default option
};
    ClearWindowData_Conv2();
    PlaySFX_Conv(SFX_MENU);
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
            ClearSprites_Conv();
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