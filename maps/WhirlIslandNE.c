#include "../constants.h"
#include "../util/scripting.h"
#include "WhirlIslandNE.h"
//// EVENTS
enum {
    WHIRLISLANDNE_POKE_BALL = 2,
};

const Script_fn_t WhirlIslandNE_SceneScripts[] = {
    0,
};

const struct MapCallback WhirlIslandNE_MapCallbacks[] = {
    0,
};

const struct MapScripts WhirlIslandNE_MapScripts = {
    .scene_script_count = 0, // lengthof(WhirlIslandNE_SceneScripts),
    .scene_scripts = WhirlIslandNE_SceneScripts,

    .callback_count = 0, // lengthof(WhirlIslandNE_MapCallbacks),
    .callbacks = WhirlIslandNE_MapCallbacks,
};

static const struct CoordEvent WhirlIslandNE_CoordEvents[] = {
    0,
};

static const struct BGEvent WhirlIslandNE_BGEvents[] = {
    0,
};

static const struct WarpEventData WhirlIslandNE_WarpEvents[] = {
    warp_event(3, 13, ROUTE_41, 2),
    warp_event(17, 3, WHIRL_ISLAND_B1F, 2),
    warp_event(13, 11, WHIRL_ISLAND_B1F, 3),
};

static const struct ObjEvent WhirlIslandNE_ObjectEvents[] = {
    object_event(11, 11, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &WhirlIslandNEUltraBall, EVENT_WHIRL_ISLAND_NE_ULTRA_BALL),
};

const struct MapEvents WhirlIslandNE_MapEvents = {
    .warp_event_count = lengthof(WhirlIslandNE_WarpEvents),
    .warp_events = WhirlIslandNE_WarpEvents,

    .coord_event_count = 0, // lengthof(WhirlIslandNE_CoordEvents),
    .coord_events = WhirlIslandNE_CoordEvents,

    .bg_event_count = 0, // lengthof(WhirlIslandNE_BGEvents),
    .bg_events = WhirlIslandNE_BGEvents,

    .obj_event_count = lengthof(WhirlIslandNE_ObjectEvents),
    .obj_events = WhirlIslandNE_ObjectEvents,
};

//// CODE

const struct ItemBall WhirlIslandNEUltraBall = {ULTRA_BALL, 1};
    //db(0, 0) // filler
