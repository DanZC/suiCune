#include "../constants.h"
#include "../util/scripting.h"
#include "Route10North.h"
//// EVENTS
const Script_fn_t Route10North_SceneScripts[] = {
    0,
};

const struct MapCallback Route10North_MapCallbacks[] = {
    0,
};

const struct MapScripts Route10North_MapScripts = {
    .scene_script_count = 0, // lengthof(Route10North_SceneScripts),
    .scene_scripts = Route10North_SceneScripts,

    .callback_count = 0, // lengthof(Route10North_MapCallbacks),
    .callbacks = Route10North_MapCallbacks,
};

static const struct CoordEvent Route10North_CoordEvents[] = {
    0,
};

static const struct BGEvent Route10North_BGEvents[] = {
    bg_event(5, 11, BGEVENT_READ, &PowerPlantSign),
    bg_event(12, 1, BGEVENT_READ, &Route10PokecenterSign),
};

static const struct WarpEventData Route10North_WarpEvents[] = {
    warp_event(11, 1, ROUTE_10_POKECENTER_1F, 1),
    warp_event(3, 9, POWER_PLANT, 1),
};

static const struct ObjEvent Route10North_ObjectEvents[] = {
    0,
};

const struct MapEvents Route10North_MapEvents = {
    .warp_event_count = lengthof(Route10North_WarpEvents),
    .warp_events = Route10North_WarpEvents,

    .coord_event_count = 0, // lengthof(Route10North_CoordEvents),
    .coord_events = Route10North_CoordEvents,

    .bg_event_count = lengthof(Route10North_BGEvents),
    .bg_events = Route10North_BGEvents,

    .obj_event_count = 0, // lengthof(Route10North_ObjectEvents),
    .obj_events = Route10North_ObjectEvents,
};

//// CODE

bool PowerPlantSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(PowerPlantSignText)
    SCRIPT_END
}
bool Route10PokecenterSign(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(PokecenterSignScript)
    SCRIPT_END
}
const txt_cmd_s PowerPlantSignText[] = {
    text_start("KANTO POWER PLANT"
        t_done )
    //db(0, 0) // filler
};
