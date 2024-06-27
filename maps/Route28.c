#include "../constants.h"
#include "../util/scripting.h"
#include "Route28.h"
//// EVENTS
const Script_fn_t Route28_SceneScripts[] = {
    0,
};

const struct MapCallback Route28_MapCallbacks[] = {
    0,
};

const struct MapScripts Route28_MapScripts = {
    .scene_script_count = 0, // lengthof(Route28_SceneScripts),
    .scene_scripts = Route28_SceneScripts,

    .callback_count = 0, // lengthof(Route28_MapCallbacks),
    .callbacks = Route28_MapCallbacks,
};

static const struct CoordEvent Route28_CoordEvents[] = {
    0,
};

static const struct BGEvent Route28_BGEvents[] = {
    bg_event(31, 5, BGEVENT_READ, &Route28Sign),
    bg_event(25, 2, BGEVENT_ITEM, &Route28HiddenRareCandy),
};

static const struct WarpEventData Route28_WarpEvents[] = {
    warp_event(7, 3, ROUTE_28_STEEL_WING_HOUSE, 1),
    warp_event(33, 5, VICTORY_ROAD_GATE, 7),
};

static const struct ObjEvent Route28_ObjectEvents[] = {
    0,
};

const struct MapEvents Route28_MapEvents = {
    .warp_event_count = lengthof(Route28_WarpEvents),
    .warp_events = Route28_WarpEvents,

    .coord_event_count = 0, // lengthof(Route28_CoordEvents),
    .coord_events = Route28_CoordEvents,

    .bg_event_count = lengthof(Route28_BGEvents),
    .bg_events = Route28_BGEvents,

    .obj_event_count = 0, // lengthof(Route28_ObjectEvents),
    .obj_events = Route28_ObjectEvents,
};

//// CODE

bool Route28Sign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(Route28SignText)
    SCRIPT_END
}
const struct HiddenItem Route28HiddenRareCandy = {RARE_CANDY, EVENT_ROUTE_28_HIDDEN_RARE_CANDY};
const txt_cmd_s Route28SignText[] = {
    text_start("ROUTE 28"
        t_done )
    //db(0, 0) // filler
};
