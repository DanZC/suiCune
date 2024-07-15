#include "../constants.h"
#include "../util/scripting.h"
#include "Route22.h"
//// EVENTS
const Script_fn_t Route22_SceneScripts[] = {
    0,
};

const struct MapCallback Route22_MapCallbacks[] = {
    0,
};

const struct MapScripts Route22_MapScripts = {
    .scene_script_count = 0, // lengthof(Route22_SceneScripts),
    .scene_scripts = Route22_SceneScripts,

    .callback_count = 0, // lengthof(Route22_MapCallbacks),
    .callbacks = Route22_MapCallbacks,
};

static const struct CoordEvent Route22_CoordEvents[] = {
    0,
};

static const struct BGEvent Route22_BGEvents[] = {
    bg_event(15, 7, BGEVENT_READ, &VictoryRoadEntranceSign),
};

static const struct WarpEventData Route22_WarpEvents[] = {
    warp_event(13, 5, VICTORY_ROAD_GATE, 1),
};

static const struct ObjEvent Route22_ObjectEvents[] = {
    0,
};

const struct MapEvents Route22_MapEvents = {
    .warp_event_count = lengthof(Route22_WarpEvents),
    .warp_events = Route22_WarpEvents,

    .coord_event_count = 0, // lengthof(Route22_CoordEvents),
    .coord_events = Route22_CoordEvents,

    .bg_event_count = lengthof(Route22_BGEvents),
    .bg_events = Route22_BGEvents,

    .obj_event_count = 0, // lengthof(Route22_ObjectEvents),
    .obj_events = Route22_ObjectEvents,
};

//// CODE

bool VictoryRoadEntranceSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(VictoryRoadEntranceSignText)
    SCRIPT_END
}
const txt_cmd_s VictoryRoadEntranceSignText[] = {
    text_start("#MON LEAGUE"
        t_para "VICTORY ROAD"
        t_line "ENTRANCE"
        t_done )
    //db(0, 0) // filler
};
