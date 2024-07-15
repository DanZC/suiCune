#include "../constants.h"
#include "../util/scripting.h"
#include "Route2Gate.h"
//// EVENTS
enum {
    ROUTE2GATE_SCIENTIST = 2,
};

const Script_fn_t Route2Gate_SceneScripts[] = {
    0,
};

const struct MapCallback Route2Gate_MapCallbacks[] = {
    0,
};

const struct MapScripts Route2Gate_MapScripts = {
    .scene_script_count = 0, // lengthof(Route2Gate_SceneScripts),
    .scene_scripts = Route2Gate_SceneScripts,

    .callback_count = 0, // lengthof(Route2Gate_MapCallbacks),
    .callbacks = Route2Gate_MapCallbacks,
};

static const struct CoordEvent Route2Gate_CoordEvents[] = {
    0,
};

static const struct BGEvent Route2Gate_BGEvents[] = {
    0,
};

static const struct WarpEventData Route2Gate_WarpEvents[] = {
    warp_event(4, 0, ROUTE_2, 3),
    warp_event(5, 0, ROUTE_2, 4),
    warp_event(4, 7, ROUTE_2, 2),
    warp_event(5, 7, ROUTE_2, 2),
};

static const struct ObjEvent Route2Gate_ObjectEvents[] = {
    object_event(6, 4, SPRITE_SCIENTIST, SPRITEMOVEDATA_WALK_UP_DOWN, 0, 2, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &Route2GateScientistScript, -1),
};

const struct MapEvents Route2Gate_MapEvents = {
    .warp_event_count = lengthof(Route2Gate_WarpEvents),
    .warp_events = Route2Gate_WarpEvents,

    .coord_event_count = 0, // lengthof(Route2Gate_CoordEvents),
    .coord_events = Route2Gate_CoordEvents,

    .bg_event_count = 0, // lengthof(Route2Gate_BGEvents),
    .bg_events = Route2Gate_BGEvents,

    .obj_event_count = lengthof(Route2Gate_ObjectEvents),
    .obj_events = Route2Gate_ObjectEvents,
};

//// CODE

bool Route2GateScientistScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(Route2GateScientistText)
    SCRIPT_END
}
const txt_cmd_s Route2GateScientistText[] = {
    text_start("Are you <PLAY_G>?"
        t_para "I work as PROF."
        t_line "OAK's AIDE."
        t_para "I had no idea that"
        t_line "you were out here."
        t_para "PROF.OAK's LAB is"
        t_line "nearby in PALLET"
        t_cont "TOWN."
        t_done )
    //db(0, 0) // filler
};
