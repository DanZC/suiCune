#include "../constants.h"
#include "../util/scripting.h"
#include "UndergroundPath.h"
//// EVENTS
const Script_fn_t UndergroundPath_SceneScripts[] = {
    0,
};

const struct MapCallback UndergroundPath_MapCallbacks[] = {
    0,
};

const struct MapScripts UndergroundPath_MapScripts = {
    .scene_script_count = 0, // lengthof(UndergroundPath_SceneScripts),
    .scene_scripts = UndergroundPath_SceneScripts,

    .callback_count = 0, // lengthof(UndergroundPath_MapCallbacks),
    .callbacks = UndergroundPath_MapCallbacks,
};

static const struct CoordEvent UndergroundPath_CoordEvents[] = {
    0,
};

static const struct BGEvent UndergroundPath_BGEvents[] = {
    bg_event(3, 9, BGEVENT_ITEM, &UndergroundPathHiddenFullRestore),
    bg_event(1, 19, BGEVENT_ITEM, &UndergroundPathHiddenXSpecial),
};

static const struct WarpEventData UndergroundPath_WarpEvents[] = {
    warp_event(3, 2, ROUTE_5_UNDERGROUND_PATH_ENTRANCE, 3),
    warp_event(3, 24, ROUTE_6_UNDERGROUND_PATH_ENTRANCE, 3),
};

static const struct ObjEvent UndergroundPath_ObjectEvents[] = {
    0,
};

const struct MapEvents UndergroundPath_MapEvents = {
    .warp_event_count = lengthof(UndergroundPath_WarpEvents),
    .warp_events = UndergroundPath_WarpEvents,

    .coord_event_count = 0, // lengthof(UndergroundPath_CoordEvents),
    .coord_events = UndergroundPath_CoordEvents,

    .bg_event_count = lengthof(UndergroundPath_BGEvents),
    .bg_events = UndergroundPath_BGEvents,

    .obj_event_count = 0, // lengthof(UndergroundPath_ObjectEvents),
    .obj_events = UndergroundPath_ObjectEvents,
};

//// CODE

const struct HiddenItem UndergroundPathHiddenFullRestore = {FULL_RESTORE, EVENT_UNDERGROUND_PATH_HIDDEN_FULL_RESTORE};
const struct HiddenItem UndergroundPathHiddenXSpecial = {X_SPECIAL, EVENT_UNDERGROUND_PATH_HIDDEN_X_SPECIAL};
    //db(0, 0) // filler
