#include "../constants.h"
#include "../util/scripting.h"
#include "Route38EcruteakGate.h"
//// EVENTS
enum {
    ROUTE38ECRUTEAKGATE_OFFICER = 2,
};

const Script_fn_t Route38EcruteakGate_SceneScripts[] = {
    0,
};

const struct MapCallback Route38EcruteakGate_MapCallbacks[] = {
    0,
};

const struct MapScripts Route38EcruteakGate_MapScripts = {
    .scene_script_count = 0, // lengthof(Route38EcruteakGate_SceneScripts),
    .scene_scripts = Route38EcruteakGate_SceneScripts,

    .callback_count = 0, // lengthof(Route38EcruteakGate_MapCallbacks),
    .callbacks = Route38EcruteakGate_MapCallbacks,
};

static const struct CoordEvent Route38EcruteakGate_CoordEvents[] = {
    0,
};

static const struct BGEvent Route38EcruteakGate_BGEvents[] = {
    0,
};

static const struct WarpEventData Route38EcruteakGate_WarpEvents[] = {
    warp_event(0, 4, ROUTE_38, 1),
    warp_event(0, 5, ROUTE_38, 2),
    warp_event(9, 4, ECRUTEAK_CITY, 14),
    warp_event(9, 5, ECRUTEAK_CITY, 15),
};

static const struct ObjEvent Route38EcruteakGate_ObjectEvents[] = {
    object_event(5, 2, SPRITE_OFFICER, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &Route38EcruteakGateOfficerScript, -1),
};

const struct MapEvents Route38EcruteakGate_MapEvents = {
    .warp_event_count = lengthof(Route38EcruteakGate_WarpEvents),
    .warp_events = Route38EcruteakGate_WarpEvents,

    .coord_event_count = 0, // lengthof(Route38EcruteakGate_CoordEvents),
    .coord_events = Route38EcruteakGate_CoordEvents,

    .bg_event_count = 0, // lengthof(Route38EcruteakGate_BGEvents),
    .bg_events = Route38EcruteakGate_BGEvents,

    .obj_event_count = lengthof(Route38EcruteakGate_ObjectEvents),
    .obj_events = Route38EcruteakGate_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "Route38EcruteakGate.h"

bool Route38EcruteakGateOfficerScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(Route38EcruteakGateOfficerText)
    SCRIPT_END
}
const txt_cmd_s Route38EcruteakGateOfficerText[] = {
    text_start("Where did you say"
        t_line "you're from?"
        t_para "NEW BARK TOWN?"
        t_para "PROF.ELM lives"
        t_line "over there, right?"
        t_para "You've come a long"
        t_line "way to get here."
        t_done )
    //db(0, 0) // filler
};
