#include "../constants.h"
#include "../util/scripting.h"
#include "Route7.h"
//// EVENTS
const Script_fn_t Route7_SceneScripts[] = {
    0,
};

const struct MapCallback Route7_MapCallbacks[] = {
    0,
};

const struct MapScripts Route7_MapScripts = {
    .scene_script_count = 0, // lengthof(Route7_SceneScripts),
    .scene_scripts = Route7_SceneScripts,

    .callback_count = 0, // lengthof(Route7_MapCallbacks),
    .callbacks = Route7_MapCallbacks,
};

static const struct CoordEvent Route7_CoordEvents[] = {
    0,
};

static const struct BGEvent Route7_BGEvents[] = {
    bg_event(5, 11, BGEVENT_READ, &Route7UndergroundPathSign),
    bg_event(6, 9, BGEVENT_READ, &Route7LockedDoor),
};

static const struct WarpEventData Route7_WarpEvents[] = {
    warp_event(15, 6, ROUTE_7_SAFFRON_GATE, 1),
    warp_event(15, 7, ROUTE_7_SAFFRON_GATE, 2),
};

static const struct ObjEvent Route7_ObjectEvents[] = {
    0,
};

const struct MapEvents Route7_MapEvents = {
    .warp_event_count = lengthof(Route7_WarpEvents),
    .warp_events = Route7_WarpEvents,

    .coord_event_count = 0, // lengthof(Route7_CoordEvents),
    .coord_events = Route7_CoordEvents,

    .bg_event_count = lengthof(Route7_BGEvents),
    .bg_events = Route7_BGEvents,

    .obj_event_count = 0, // lengthof(Route7_ObjectEvents),
    .obj_events = Route7_ObjectEvents,
};

//// CODE

bool Route7UndergroundPathSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(Route7UndergroundPathSignText)
    SCRIPT_END
}
bool Route7LockedDoor(script_s* s) {
    SCRIPT_BEGIN
    jumptext(Route7LockedDoorText)
    SCRIPT_END
}
const txt_cmd_s Route7UndergroundPathSignText[] = {
    text_start("What's this flyer?"
        t_para "… Uncouth trainers"
        t_line "have been holding"
        t_para "battles in the"
        t_line "UNDERGROUND PATH."
        t_para "Because of rising"
        t_line "complaints by lo-"
        t_cont "cal residents, the"
        t_cont "UNDERGROUND PATH"
        t_cont "has been sealed"
        t_cont "indefinitely."
        t_para "CELADON POLICE"
        t_done )
};
const txt_cmd_s Route7LockedDoorText[] = {
    text_start("It's locked…"
        t_done )
    //db(0, 0) // filler
};
