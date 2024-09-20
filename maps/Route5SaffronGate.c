#include "../constants.h"
#include "../util/scripting.h"
#include "Route5SaffronGate.h"
//// EVENTS
enum {
    ROUTE5SAFFRONGATE_OFFICER = 2,
};

const Script_fn_t Route5SaffronGate_SceneScripts[] = {
    0,
};

const struct MapCallback Route5SaffronGate_MapCallbacks[] = {
    0,
};

const struct MapScripts Route5SaffronGate_MapScripts = {
    .scene_script_count = 0, // lengthof(Route5SaffronGate_SceneScripts),
    .scene_scripts = Route5SaffronGate_SceneScripts,

    .callback_count = 0, // lengthof(Route5SaffronGate_MapCallbacks),
    .callbacks = Route5SaffronGate_MapCallbacks,
};

static const struct CoordEvent Route5SaffronGate_CoordEvents[] = {
    0,
};

static const struct BGEvent Route5SaffronGate_BGEvents[] = {
    0,
};

static const struct WarpEventData Route5SaffronGate_WarpEvents[] = {
    warp_event(4, 0, ROUTE_5, 2),
    warp_event(5, 0, ROUTE_5, 3),
    warp_event(4, 7, SAFFRON_CITY, 9),
    warp_event(5, 7, SAFFRON_CITY, 9),
};

static const struct ObjEvent Route5SaffronGate_ObjectEvents[] = {
    object_event(0, 4, SPRITE_OFFICER, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &Route5SaffronGateOfficerScript, -1),
};

const struct MapEvents Route5SaffronGate_MapEvents = {
    .warp_event_count = lengthof(Route5SaffronGate_WarpEvents),
    .warp_events = Route5SaffronGate_WarpEvents,

    .coord_event_count = 0, // lengthof(Route5SaffronGate_CoordEvents),
    .coord_events = Route5SaffronGate_CoordEvents,

    .bg_event_count = 0, // lengthof(Route5SaffronGate_BGEvents),
    .bg_events = Route5SaffronGate_BGEvents,

    .obj_event_count = lengthof(Route5SaffronGate_ObjectEvents),
    .obj_events = Route5SaffronGate_ObjectEvents,
};

//// CODE

bool Route5SaffronGateOfficerScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(Route5SaffronGateOfficerText)
    SCRIPT_END
}
const txt_cmd_s Route5SaffronGateOfficerText[] = {
    text_start("You're from JOHTO,"
        t_line "aren't you?"
        t_para "How do you like"
        t_line "KANTO? It's nice,"
        t_cont "don't you agree?"
        t_done )
    //db(0, 0) // filler
};
