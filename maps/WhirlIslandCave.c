#include "../constants.h"
#include "../util/scripting.h"
#include "WhirlIslandCave.h"
//// EVENTS
const Script_fn_t WhirlIslandCave_SceneScripts[] = {
    0,
};

const struct MapCallback WhirlIslandCave_MapCallbacks[] = {
    0,
};

const struct MapScripts WhirlIslandCave_MapScripts = {
    .scene_script_count = 0, // lengthof(WhirlIslandCave_SceneScripts),
    .scene_scripts = WhirlIslandCave_SceneScripts,

    .callback_count = 0, // lengthof(WhirlIslandCave_MapCallbacks),
    .callbacks = WhirlIslandCave_MapCallbacks,
};

static const struct CoordEvent WhirlIslandCave_CoordEvents[] = {
    0,
};

static const struct BGEvent WhirlIslandCave_BGEvents[] = {
    0,
};

static const struct WarpEventData WhirlIslandCave_WarpEvents[] = {
    warp_event(7, 5, WHIRL_ISLAND_B1F, 9),
    warp_event(3, 13, WHIRL_ISLAND_NW, 4),
};

static const struct ObjEvent WhirlIslandCave_ObjectEvents[] = {
    0,
};

const struct MapEvents WhirlIslandCave_MapEvents = {
    .warp_event_count = lengthof(WhirlIslandCave_WarpEvents),
    .warp_events = WhirlIslandCave_WarpEvents,

    .coord_event_count = 0, // lengthof(WhirlIslandCave_CoordEvents),
    .coord_events = WhirlIslandCave_CoordEvents,

    .bg_event_count = 0, // lengthof(WhirlIslandCave_BGEvents),
    .bg_events = WhirlIslandCave_BGEvents,

    .obj_event_count = 0, // lengthof(WhirlIslandCave_ObjectEvents),
    .obj_events = WhirlIslandCave_ObjectEvents,
};

//// CODE

    //db(0, 0) // filler
