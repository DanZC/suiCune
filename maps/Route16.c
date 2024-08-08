#include "../constants.h"
#include "../util/scripting.h"
#include "Route16.h"
//// EVENTS
const Script_fn_t Route16_SceneScripts[] = {
    0,
};

const struct MapCallback Route16_MapCallbacks[] = {
    map_callback(MAPCALLBACK_NEWMAP, Route16_MapScripts_AlwaysOnBike),
};

const struct MapScripts Route16_MapScripts = {
    .scene_script_count = 0, // lengthof(Route16_SceneScripts),
    .scene_scripts = Route16_SceneScripts,

    .callback_count = lengthof(Route16_MapCallbacks),
    .callbacks = Route16_MapCallbacks,
};

static const struct CoordEvent Route16_CoordEvents[] = {
    0,
};

static const struct BGEvent Route16_BGEvents[] = {
    bg_event(5, 5, BGEVENT_READ, &CyclingRoadSign),
};

static const struct WarpEventData Route16_WarpEvents[] = {
    warp_event(3, 1, ROUTE_16_FUCHSIA_SPEECH_HOUSE, 1),
    warp_event(14, 6, ROUTE_16_GATE, 3),
    warp_event(14, 7, ROUTE_16_GATE, 4),
    warp_event(9, 6, ROUTE_16_GATE, 1),
    warp_event(9, 7, ROUTE_16_GATE, 2),
};

static const struct ObjEvent Route16_ObjectEvents[] = {
    0,
};

const struct MapEvents Route16_MapEvents = {
    .warp_event_count = lengthof(Route16_WarpEvents),
    .warp_events = Route16_WarpEvents,

    .coord_event_count = 0, // lengthof(Route16_CoordEvents),
    .coord_events = Route16_CoordEvents,

    .bg_event_count = lengthof(Route16_BGEvents),
    .bg_events = Route16_BGEvents,

    .obj_event_count = 0, // lengthof(Route16_ObjectEvents),
    .obj_events = Route16_ObjectEvents,
};

//// CODE

bool Route16_MapScripts_AlwaysOnBike(script_s* s) {
    SCRIPT_BEGIN
    readvar(VAR_YCOORD)
    ifless(5, CanWalk)
    readvar(VAR_XCOORD)
    ifgreater(13, CanWalk)
    setflag(ENGINE_ALWAYS_ON_BIKE)
    s_endcallback
CanWalk:
    clearflag(ENGINE_ALWAYS_ON_BIKE)
    s_endcallback
    SCRIPT_END
}
bool CyclingRoadSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(CyclingRoadSignText)
    SCRIPT_END
}
const txt_cmd_s CyclingRoadSignText[] = {
    text_start("CYCLING ROAD"
        t_para "DOWNHILL COASTING"
        t_line "ALL THE WAY!"
        t_done )
    //db(0, 0) // filler
};
