#include "../constants.h"
#include "../util/scripting.h"
#include "Route8SaffronGate.h"
//// EVENTS
enum {
    ROUTE8SAFFRONGATE_OFFICER = 2,
};

const Script_fn_t Route8SaffronGate_SceneScripts[] = {
    0,
};

const struct MapCallback Route8SaffronGate_MapCallbacks[] = {
    0,
};

const struct MapScripts Route8SaffronGate_MapScripts = {
    .scene_script_count = 0, // lengthof(Route8SaffronGate_SceneScripts),
    .scene_scripts = Route8SaffronGate_SceneScripts,

    .callback_count = 0, // lengthof(Route8SaffronGate_MapCallbacks),
    .callbacks = Route8SaffronGate_MapCallbacks,
};

static const struct CoordEvent Route8SaffronGate_CoordEvents[] = {
    0,
};

static const struct BGEvent Route8SaffronGate_BGEvents[] = {
    0,
};

static const struct WarpEventData Route8SaffronGate_WarpEvents[] = {
    warp_event(0, 4, SAFFRON_CITY, 14),
    warp_event(0, 5, SAFFRON_CITY, 15),
    warp_event(9, 4, ROUTE_8, 1),
    warp_event(9, 5, ROUTE_8, 2),
};

static const struct ObjEvent Route8SaffronGate_ObjectEvents[] = {
    object_event(5, 2, SPRITE_OFFICER, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &Route8SaffronGateOfficerScript, -1),
};

const struct MapEvents Route8SaffronGate_MapEvents = {
    .warp_event_count = lengthof(Route8SaffronGate_WarpEvents),
    .warp_events = Route8SaffronGate_WarpEvents,

    .coord_event_count = 0, // lengthof(Route8SaffronGate_CoordEvents),
    .coord_events = Route8SaffronGate_CoordEvents,

    .bg_event_count = 0, // lengthof(Route8SaffronGate_BGEvents),
    .bg_events = Route8SaffronGate_BGEvents,

    .obj_event_count = lengthof(Route8SaffronGate_ObjectEvents),
    .obj_events = Route8SaffronGate_ObjectEvents,
};

//// CODE

bool Route8SaffronGateOfficerScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(Route8SaffronGateOfficerText)
    SCRIPT_END
}
const txt_cmd_s Route8SaffronGateOfficerText[] = {
    text_start("Have you been to"
        t_line "LAVENDER TOWN?"
        t_para "There's a tall"
        t_line "RADIO TOWER there."
        t_done )
    //db(0, 0) // filler
};
