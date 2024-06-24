#include "../constants.h"
#include "../util/scripting.h"
#include "WhirlIslandNW.h"
//// EVENTS
const Script_fn_t WhirlIslandNW_SceneScripts[] = {
    0,
};

const struct MapCallback WhirlIslandNW_MapCallbacks[] = {
    0,
};

const struct MapScripts WhirlIslandNW_MapScripts = {
    .scene_script_count = 0, // lengthof(WhirlIslandNW_SceneScripts),
    .scene_scripts = WhirlIslandNW_SceneScripts,

    .callback_count = 0, // lengthof(WhirlIslandNW_MapCallbacks),
    .callbacks = WhirlIslandNW_MapCallbacks,
};

static const struct CoordEvent WhirlIslandNW_CoordEvents[] = {
    0,
};

static const struct BGEvent WhirlIslandNW_BGEvents[] = {
    0,
};

static const struct WarpEventData WhirlIslandNW_WarpEvents[] = {
    warp_event(5, 7, ROUTE_41, 1),
    warp_event(5, 3, WHIRL_ISLAND_B1F, 1),
    warp_event(3, 15, WHIRL_ISLAND_SW, 4),
    warp_event(7, 15, WHIRL_ISLAND_CAVE, 2),
};

static const struct ObjEvent WhirlIslandNW_ObjectEvents[] = {
    0,
};

const struct MapEvents WhirlIslandNW_MapEvents = {
    .warp_event_count = lengthof(WhirlIslandNW_WarpEvents),
    .warp_events = WhirlIslandNW_WarpEvents,

    .coord_event_count = 0, // lengthof(WhirlIslandNW_CoordEvents),
    .coord_events = WhirlIslandNW_CoordEvents,

    .bg_event_count = 0, // lengthof(WhirlIslandNW_BGEvents),
    .bg_events = WhirlIslandNW_BGEvents,

    .obj_event_count = 0, // lengthof(WhirlIslandNW_ObjectEvents),
    .obj_events = WhirlIslandNW_ObjectEvents,
};

//// CODE

    //db(0, 0) // filler
