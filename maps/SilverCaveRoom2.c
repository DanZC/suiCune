#include "../constants.h"
#include "../util/scripting.h"
#include "SilverCaveRoom2.h"
//// EVENTS
enum {
    SILVERCAVEROOM2_POKE_BALL1 = 2,
    SILVERCAVEROOM2_POKE_BALL2,
    SILVERCAVEROOM2_POKE_BALL3,
};

const Script_fn_t SilverCaveRoom2_SceneScripts[] = {
    0,
};

const struct MapCallback SilverCaveRoom2_MapCallbacks[] = {
    0,
};

const struct MapScripts SilverCaveRoom2_MapScripts = {
    .scene_script_count = 0, // lengthof(SilverCaveRoom2_SceneScripts),
    .scene_scripts = SilverCaveRoom2_SceneScripts,

    .callback_count = 0, // lengthof(SilverCaveRoom2_MapCallbacks),
    .callbacks = SilverCaveRoom2_MapCallbacks,
};

static const struct CoordEvent SilverCaveRoom2_CoordEvents[] = {
    0,
};

static const struct BGEvent SilverCaveRoom2_BGEvents[] = {
    bg_event(14, 31, BGEVENT_ITEM, &SilverCaveRoom2HiddenMaxPotion),
};

static const struct WarpEventData SilverCaveRoom2_WarpEvents[] = {
    warp_event(17, 31, SILVER_CAVE_ROOM_1, 2),
    warp_event(11, 5, SILVER_CAVE_ROOM_3, 1),
    warp_event(13, 21, SILVER_CAVE_ITEM_ROOMS, 1),
    warp_event(23, 3, SILVER_CAVE_ITEM_ROOMS, 2),
};

static const struct ObjEvent SilverCaveRoom2_ObjectEvents[] = {
    object_event(24, 10, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &SilverCaveRoom2Calcium, EVENT_SILVER_CAVE_ROOM_2_CALCIUM),
    object_event(22, 24, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &SilverCaveRoom2UltraBall, EVENT_SILVER_CAVE_ROOM_2_ULTRA_BALL),
    object_event(4, 20, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &SilverCaveRoom2PPUp, EVENT_SILVER_CAVE_ROOM_2_PP_UP),
};

const struct MapEvents SilverCaveRoom2_MapEvents = {
    .warp_event_count = lengthof(SilverCaveRoom2_WarpEvents),
    .warp_events = SilverCaveRoom2_WarpEvents,

    .coord_event_count = 0, // lengthof(SilverCaveRoom2_CoordEvents),
    .coord_events = SilverCaveRoom2_CoordEvents,

    .bg_event_count = lengthof(SilverCaveRoom2_BGEvents),
    .bg_events = SilverCaveRoom2_BGEvents,

    .obj_event_count = lengthof(SilverCaveRoom2_ObjectEvents),
    .obj_events = SilverCaveRoom2_ObjectEvents,
};

//// CODE

const struct ItemBall SilverCaveRoom2Calcium = {CALCIUM, 1};
const struct ItemBall SilverCaveRoom2UltraBall = {ULTRA_BALL, 1};
const struct ItemBall SilverCaveRoom2PPUp = {PP_UP, 1};
const struct HiddenItem SilverCaveRoom2HiddenMaxPotion = {MAX_POTION, EVENT_SILVER_CAVE_ROOM_2_HIDDEN_MAX_POTION};
    //db(0, 0) // filler
