#include "../constants.h"
#include "../util/scripting.h"
#include "DragonsDen1F.h"
//// EVENTS
const Script_fn_t DragonsDen1F_SceneScripts[] = {
    0,
};

const struct MapCallback DragonsDen1F_MapCallbacks[] = {
    0,
};

const struct MapScripts DragonsDen1F_MapScripts = {
    .scene_script_count = 0, // lengthof(DragonsDen1F_SceneScripts),
    .scene_scripts = DragonsDen1F_SceneScripts,

    .callback_count = 0, // lengthof(DragonsDen1F_MapCallbacks),
    .callbacks = DragonsDen1F_MapCallbacks,
};

static const struct CoordEvent DragonsDen1F_CoordEvents[] = {
    0,
};

static const struct BGEvent DragonsDen1F_BGEvents[] = {
    0,
};

static const struct WarpEventData DragonsDen1F_WarpEvents[] = {
    warp_event(3, 5, BLACKTHORN_CITY, 8),
    warp_event(3, 3, DRAGONS_DEN_1F, 4),
    warp_event(5, 15, DRAGONS_DEN_B1F, 1),
    warp_event(5, 13, DRAGONS_DEN_1F, 2),
};

static const struct ObjEvent DragonsDen1F_ObjectEvents[] = {
    0,
};

const struct MapEvents DragonsDen1F_MapEvents = {
    .warp_event_count = lengthof(DragonsDen1F_WarpEvents),
    .warp_events = DragonsDen1F_WarpEvents,

    .coord_event_count = 0, // lengthof(DragonsDen1F_CoordEvents),
    .coord_events = DragonsDen1F_CoordEvents,

    .bg_event_count = 0, // lengthof(DragonsDen1F_BGEvents),
    .bg_events = DragonsDen1F_BGEvents,

    .obj_event_count = 0, // lengthof(DragonsDen1F_ObjectEvents),
    .obj_events = DragonsDen1F_ObjectEvents,
};

//// CODE

    //db(0, 0) // filler
