#include "../constants.h"
#include "../util/scripting.h"
#include "Route31VioletGate.h"
//// EVENTS
enum {
    ROUTE31VIOLETGATE_OFFICER = 2,
    ROUTE31VIOLETGATE_COOLTRAINER_F,
};

const Script_fn_t Route31VioletGate_SceneScripts[] = {
};

const struct MapCallback Route31VioletGate_MapCallbacks[] = {
};

const struct MapScripts Route31VioletGate_MapScripts = {
    .scene_script_count = lengthof(Route31VioletGate_SceneScripts),
    .scene_scripts = Route31VioletGate_SceneScripts,

    .callback_count = lengthof(Route31VioletGate_MapCallbacks),
    .callbacks = Route31VioletGate_MapCallbacks,
};

static const struct CoordEvent Route31VioletGate_CoordEvents[] = {
};

static const struct BGEvent Route31VioletGate_BGEvents[] = {
};

static const struct WarpEventData Route31VioletGate_WarpEvents[] = {
    warp_event(0, 4, VIOLET_CITY, 8),
    warp_event(0, 5, VIOLET_CITY, 9),
    warp_event(9, 4, ROUTE_31, 1),
    warp_event(9, 5, ROUTE_31, 2),
};

static const struct ObjEvent Route31VioletGate_ObjectEvents[] = {
    object_event(5, 2, SPRITE_OFFICER, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &Route31VioletGateOfficerScript, -1),
    object_event(1, 2, SPRITE_COOLTRAINER_F, SPRITEMOVEDATA_SPINRANDOM_SLOW, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &Route31VioletGateCooltrainerFScript, -1),
};

const struct MapEvents Route31VioletGate_MapEvents = {
    .warp_event_count = lengthof(Route31VioletGate_WarpEvents),
    .warp_events = Route31VioletGate_WarpEvents,

    .coord_event_count = lengthof(Route31VioletGate_CoordEvents),
    .coord_events = Route31VioletGate_CoordEvents,

    .bg_event_count = lengthof(Route31VioletGate_BGEvents),
    .bg_events = Route31VioletGate_BGEvents,

    .obj_event_count = lengthof(Route31VioletGate_ObjectEvents),
    .obj_events = Route31VioletGate_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "Route31VioletGate.h"

bool Route31VioletGateOfficerScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(Route31VioletGateOfficerText)
    SCRIPT_END
}
bool Route31VioletGateCooltrainerFScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(Route31VioletGateCooltrainerFText)
    SCRIPT_END
}
const txt_cmd_s Route31VioletGateOfficerText[] = {
    text_start("Hi there!"
        t_line "Did you visit"
        t_cont "SPROUT TOWER?"
        t_done )
};
const txt_cmd_s Route31VioletGateCooltrainerFText[] = {
    text_start("I came too far"
        t_line "out. I'd better"
        t_cont "phone home!"
        t_done )
    //db(0, 0) // filler
};
