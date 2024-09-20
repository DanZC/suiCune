#include "../constants.h"
#include "../util/scripting.h"
#include "MountMoonGiftShop.h"
//// EVENTS
enum {
    MOUNTMOONGIFTSHOP_GRAMPS1 = 2, // morning only 
    MOUNTMOONGIFTSHOP_GRAMPS2, // day only
    MOUNTMOONGIFTSHOP_LASS1, // morning only
    MOUNTMOONGIFTSHOP_LASS2, // day only
};

const Script_fn_t MountMoonGiftShop_SceneScripts[] = {
    0,
};

const struct MapCallback MountMoonGiftShop_MapCallbacks[] = {
    0,
};

const struct MapScripts MountMoonGiftShop_MapScripts = {
    .scene_script_count = 0, // lengthof(MountMoonGiftShop_SceneScripts),
    .scene_scripts = MountMoonGiftShop_SceneScripts,

    .callback_count = 0, // lengthof(MountMoonGiftShop_MapCallbacks),
    .callbacks = MountMoonGiftShop_MapCallbacks,
};

static const struct CoordEvent MountMoonGiftShop_CoordEvents[] = {
    0,
};

static const struct BGEvent MountMoonGiftShop_BGEvents[] = {
    0,
};

static const struct WarpEventData MountMoonGiftShop_WarpEvents[] = {
    warp_event(3, 7, MOUNT_MOON_SQUARE, 3),
    warp_event(4, 7, MOUNT_MOON_SQUARE, 3),
};

static const struct ObjEvent MountMoonGiftShop_ObjectEvents[] = {
    object_event(4, 3, SPRITE_GRAMPS, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, MORN, 0, OBJECTTYPE_SCRIPT, 0, &MountMoonGiftShopClerkScript, -1),
    object_event(1, 2, SPRITE_GRAMPS, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, DAY, 0, OBJECTTYPE_SCRIPT, 0, &MountMoonGiftShopClerkScript, -1),
    object_event(1, 6, SPRITE_LASS, SPRITEMOVEDATA_WALK_LEFT_RIGHT, 1, 0, -1, MORN, 0, OBJECTTYPE_SCRIPT, 0, &MountMoonGiftShopLassScript, -1),
    object_event(5, 4, SPRITE_LASS, SPRITEMOVEDATA_WALK_UP_DOWN, 0, 1, -1, DAY, 0, OBJECTTYPE_SCRIPT, 0, &MountMoonGiftShopLassScript, -1),
};

const struct MapEvents MountMoonGiftShop_MapEvents = {
    .warp_event_count = lengthof(MountMoonGiftShop_WarpEvents),
    .warp_events = MountMoonGiftShop_WarpEvents,

    .coord_event_count = 0, // lengthof(MountMoonGiftShop_CoordEvents),
    .coord_events = MountMoonGiftShop_CoordEvents,

    .bg_event_count = 0, // lengthof(MountMoonGiftShop_BGEvents),
    .bg_events = MountMoonGiftShop_BGEvents,

    .obj_event_count = lengthof(MountMoonGiftShop_ObjectEvents),
    .obj_events = MountMoonGiftShop_ObjectEvents,
};

//// CODE

bool MountMoonGiftShopClerkScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    pokemart(MARTTYPE_STANDARD, MART_MT_MOON)
    closetext
    s_end
    SCRIPT_END
}
bool MountMoonGiftShopLassScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(MountMoonGiftShopLassText)
    SCRIPT_END
}
const txt_cmd_s MountMoonGiftShopLassText[] = {
    text_start("When the sun goes"
        t_line "down, CLEFAIRY"
        t_cont "come out to play."
        t_done )
    //db(0, 0) // filler
};
