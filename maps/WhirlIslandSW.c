#include "../constants.h"
#include "../util/scripting.h"
#include "WhirlIslandSW.h"
//// EVENTS
enum {
    WHIRLISLANDSW_POKE_BALL = 2,
};

const Script_fn_t WhirlIslandSW_SceneScripts[] = {
    0,
};

const struct MapCallback WhirlIslandSW_MapCallbacks[] = {
    0,
};

const struct MapScripts WhirlIslandSW_MapScripts = {
    .scene_script_count = 0, // lengthof(WhirlIslandSW_SceneScripts),
    .scene_scripts = WhirlIslandSW_SceneScripts,

    .callback_count = 0, // lengthof(WhirlIslandSW_MapCallbacks),
    .callbacks = WhirlIslandSW_MapCallbacks,
};

static const struct CoordEvent WhirlIslandSW_CoordEvents[] = {
    0,
};

static const struct BGEvent WhirlIslandSW_BGEvents[] = {
    0,
};

static const struct WarpEventData WhirlIslandSW_WarpEvents[] = {
    warp_event(5, 7, ROUTE_41, 3),
    warp_event(17, 3, WHIRL_ISLAND_B1F, 5),
    warp_event(3, 3, WHIRL_ISLAND_B1F, 4),
    warp_event(3, 15, WHIRL_ISLAND_NW, 3),
    warp_event(17, 15, WHIRL_ISLAND_B2F, 4),
};

static const struct ObjEvent WhirlIslandSW_ObjectEvents[] = {
    object_event(15, 2, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &WhirlIslandSWUltraBall, EVENT_WHIRL_ISLAND_SW_ULTRA_BALL),
};

const struct MapEvents WhirlIslandSW_MapEvents = {
    .warp_event_count = lengthof(WhirlIslandSW_WarpEvents),
    .warp_events = WhirlIslandSW_WarpEvents,

    .coord_event_count = 0, // lengthof(WhirlIslandSW_CoordEvents),
    .coord_events = WhirlIslandSW_CoordEvents,

    .bg_event_count = 0, // lengthof(WhirlIslandSW_BGEvents),
    .bg_events = WhirlIslandSW_BGEvents,

    .obj_event_count = lengthof(WhirlIslandSW_ObjectEvents),
    .obj_events = WhirlIslandSW_ObjectEvents,
};

//// CODE

const struct ItemBall WhirlIslandSWUltraBall = {ULTRA_BALL, 1};
    //db(0, 0) // filler
