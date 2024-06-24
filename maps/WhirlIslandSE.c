#include "../constants.h"
#include "../util/scripting.h"
#include "WhirlIslandSE.h"
//// EVENTS
const Script_fn_t WhirlIslandSE_SceneScripts[] = {
    0,
};

const struct MapCallback WhirlIslandSE_MapCallbacks[] = {
    0,
};

const struct MapScripts WhirlIslandSE_MapScripts = {
    .scene_script_count = 0, // lengthof(WhirlIslandSE_SceneScripts),
    .scene_scripts = WhirlIslandSE_SceneScripts,

    .callback_count = 0, // lengthof(WhirlIslandSE_MapCallbacks),
    .callbacks = WhirlIslandSE_MapCallbacks,
};

static const struct CoordEvent WhirlIslandSE_CoordEvents[] = {
    0,
};

static const struct BGEvent WhirlIslandSE_BGEvents[] = {
    0,
};

static const struct WarpEventData WhirlIslandSE_WarpEvents[] = {
    warp_event(5, 13, ROUTE_41, 4),
    warp_event(5, 3, WHIRL_ISLAND_B1F, 6),
};

static const struct ObjEvent WhirlIslandSE_ObjectEvents[] = {
    0,
};

const struct MapEvents WhirlIslandSE_MapEvents = {
    .warp_event_count = lengthof(WhirlIslandSE_WarpEvents),
    .warp_events = WhirlIslandSE_WarpEvents,

    .coord_event_count = 0, // lengthof(WhirlIslandSE_CoordEvents),
    .coord_events = WhirlIslandSE_CoordEvents,

    .bg_event_count = 0, // lengthof(WhirlIslandSE_BGEvents),
    .bg_events = WhirlIslandSE_BGEvents,

    .obj_event_count = 0, // lengthof(WhirlIslandSE_ObjectEvents),
    .obj_events = WhirlIslandSE_ObjectEvents,
};

//// CODE

    //db(0, 0) // filler
