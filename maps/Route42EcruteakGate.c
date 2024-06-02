#include "../constants.h"
#include "../util/scripting.h"
#include "Route42EcruteakGate.h"
//// EVENTS
enum {
    ROUTE42ECRUTEAKGATE_OFFICER = 2,
};

const Script_fn_t Route42EcruteakGate_SceneScripts[] = {
    0,
};

const struct MapCallback Route42EcruteakGate_MapCallbacks[] = {
    0,
};

const struct MapScripts Route42EcruteakGate_MapScripts = {
    .scene_script_count = 0, // lengthof(Route42EcruteakGate_SceneScripts),
    .scene_scripts = Route42EcruteakGate_SceneScripts,

    .callback_count = 0, // lengthof(Route42EcruteakGate_MapCallbacks),
    .callbacks = Route42EcruteakGate_MapCallbacks,
};

static const struct CoordEvent Route42EcruteakGate_CoordEvents[] = {
    0,
};

static const struct BGEvent Route42EcruteakGate_BGEvents[] = {
    0,
};

static const struct WarpEventData Route42EcruteakGate_WarpEvents[] = {
    warp_event(0, 4, ECRUTEAK_CITY, 1),
    warp_event(0, 5, ECRUTEAK_CITY, 2),
    warp_event(9, 4, ROUTE_42, 1),
    warp_event(9, 5, ROUTE_42, 2),
};

static const struct ObjEvent Route42EcruteakGate_ObjectEvents[] = {
    object_event(5, 2, SPRITE_OFFICER, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &Route42EcruteakGateOfficerScript, -1),
};

const struct MapEvents Route42EcruteakGate_MapEvents = {
    .warp_event_count = lengthof(Route42EcruteakGate_WarpEvents),
    .warp_events = Route42EcruteakGate_WarpEvents,

    .coord_event_count = 0, // lengthof(Route42EcruteakGate_CoordEvents),
    .coord_events = Route42EcruteakGate_CoordEvents,

    .bg_event_count = 0, // lengthof(Route42EcruteakGate_BGEvents),
    .bg_events = Route42EcruteakGate_BGEvents,

    .obj_event_count = lengthof(Route42EcruteakGate_ObjectEvents),
    .obj_events = Route42EcruteakGate_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "Route42EcruteakGate.h"

bool Route42EcruteakGateOfficerScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(Route42EcruteakGateOfficerText)
    SCRIPT_END
}
const txt_cmd_s Route42EcruteakGateOfficerText[] = {
    text_start("MT.MORTAR is like"
        t_line "a maze inside."
        t_para "Be careful. Don't"
        t_line "get lost in there."
        t_done )
    //db(0, 0) // filler
};
