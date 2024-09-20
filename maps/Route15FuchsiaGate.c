#include "../constants.h"
#include "../util/scripting.h"
#include "Route15FuchsiaGate.h"
//// EVENTS
enum {
    ROUTE15FUCHSIAGATE_OFFICER = 2,
};

const Script_fn_t Route15FuchsiaGate_SceneScripts[] = {
    0,
};

const struct MapCallback Route15FuchsiaGate_MapCallbacks[] = {
    0,
};

const struct MapScripts Route15FuchsiaGate_MapScripts = {
    .scene_script_count = 0, // lengthof(Route15FuchsiaGate_SceneScripts),
    .scene_scripts = Route15FuchsiaGate_SceneScripts,

    .callback_count = 0, // lengthof(Route15FuchsiaGate_MapCallbacks),
    .callbacks = Route15FuchsiaGate_MapCallbacks,
};

static const struct CoordEvent Route15FuchsiaGate_CoordEvents[] = {
    0,
};

static const struct BGEvent Route15FuchsiaGate_BGEvents[] = {
    0,
};

static const struct WarpEventData Route15FuchsiaGate_WarpEvents[] = {
    warp_event(0, 4, FUCHSIA_CITY, 8),
    warp_event(0, 5, FUCHSIA_CITY, 9),
    warp_event(9, 4, ROUTE_15, 1),
    warp_event(9, 5, ROUTE_15, 2),
};

static const struct ObjEvent Route15FuchsiaGate_ObjectEvents[] = {
    object_event(5, 2, SPRITE_OFFICER, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &Route15FuchsiaGateOfficerScript, -1),
};

const struct MapEvents Route15FuchsiaGate_MapEvents = {
    .warp_event_count = lengthof(Route15FuchsiaGate_WarpEvents),
    .warp_events = Route15FuchsiaGate_WarpEvents,

    .coord_event_count = 0, // lengthof(Route15FuchsiaGate_CoordEvents),
    .coord_events = Route15FuchsiaGate_CoordEvents,

    .bg_event_count = 0, // lengthof(Route15FuchsiaGate_BGEvents),
    .bg_events = Route15FuchsiaGate_BGEvents,

    .obj_event_count = lengthof(Route15FuchsiaGate_ObjectEvents),
    .obj_events = Route15FuchsiaGate_ObjectEvents,
};

//// CODE

bool Route15FuchsiaGateOfficerScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(Route15FuchsiaGateOfficerText)
    SCRIPT_END
}
const txt_cmd_s Route15FuchsiaGateOfficerText[] = {
    text_start("You're working on"
        t_line "a #DEX? That's"
        t_para "really something."
        t_line "Don't give up!"
        t_done )
    //db(0, 0) // filler
};
