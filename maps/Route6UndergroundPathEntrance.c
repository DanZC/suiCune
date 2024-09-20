#include "../constants.h"
#include "../util/scripting.h"
#include "Route6UndergroundPathEntrance.h"
//// EVENTS
const Script_fn_t Route6UndergroundPathEntrance_SceneScripts[] = {
    0,
};

const struct MapCallback Route6UndergroundPathEntrance_MapCallbacks[] = {
    0,
};

const struct MapScripts Route6UndergroundPathEntrance_MapScripts = {
    .scene_script_count = 0, // lengthof(Route6UndergroundPathEntrance_SceneScripts),
    .scene_scripts = Route6UndergroundPathEntrance_SceneScripts,

    .callback_count = 0, // lengthof(Route6UndergroundPathEntrance_MapCallbacks),
    .callbacks = Route6UndergroundPathEntrance_MapCallbacks,
};

static const struct CoordEvent Route6UndergroundPathEntrance_CoordEvents[] = {
    0,
};

static const struct BGEvent Route6UndergroundPathEntrance_BGEvents[] = {
    0,
};

static const struct WarpEventData Route6UndergroundPathEntrance_WarpEvents[] = {
    warp_event(3, 7, ROUTE_6, 1),
    warp_event(4, 7, ROUTE_6, 1),
    warp_event(4, 3, UNDERGROUND_PATH, 2),
};

static const struct ObjEvent Route6UndergroundPathEntrance_ObjectEvents[] = {
    0,
};

const struct MapEvents Route6UndergroundPathEntrance_MapEvents = {
    .warp_event_count = lengthof(Route6UndergroundPathEntrance_WarpEvents),
    .warp_events = Route6UndergroundPathEntrance_WarpEvents,

    .coord_event_count = 0, // lengthof(Route6UndergroundPathEntrance_CoordEvents),
    .coord_events = Route6UndergroundPathEntrance_CoordEvents,

    .bg_event_count = 0, // lengthof(Route6UndergroundPathEntrance_BGEvents),
    .bg_events = Route6UndergroundPathEntrance_BGEvents,

    .obj_event_count = 0, // lengthof(Route6UndergroundPathEntrance_ObjectEvents),
    .obj_events = Route6UndergroundPathEntrance_ObjectEvents,
};

//// CODE

    //db(0, 0) // filler
