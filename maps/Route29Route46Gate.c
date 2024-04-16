#include "../constants.h"
#include "../util/scripting.h"
#include "Route29Route46Gate.h"
//// EVENTS
enum {
    ROUTE29ROUTE46GATE_OFFICER = 2,
    ROUTE29ROUTE46GATE_YOUNGSTER,
};

const Script_fn_t Route29Route46Gate_SceneScripts[] = {
    0
};

const struct MapCallback Route29Route46Gate_MapCallbacks[] = {
    0
};

const struct MapScripts Route29Route46Gate_MapScripts = {
    .scene_script_count = lengthof(Route29Route46Gate_SceneScripts),
    .scene_scripts = Route29Route46Gate_SceneScripts,

    .callback_count = lengthof(Route29Route46Gate_MapCallbacks),
    .callbacks = Route29Route46Gate_MapCallbacks,
};

static const struct CoordEvent Route29Route46Gate_CoordEvents[] = {
    0
};

static const struct BGEvent Route29Route46Gate_BGEvents[] = {
    0
};

static const struct WarpEventData Route29Route46Gate_WarpEvents[] = {
    warp_event(4, 0, ROUTE_46, 1),
    warp_event(5, 0, ROUTE_46, 2),
    warp_event(4, 7, ROUTE_29, 1),
    warp_event(5, 7, ROUTE_29, 1),
};

static const struct ObjEvent Route29Route46Gate_ObjectEvents[] = {
    object_event(0, 4, SPRITE_OFFICER, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &Route29Route46GateOfficerScript, -1),
    object_event(6, 4, SPRITE_YOUNGSTER, SPRITEMOVEDATA_WALK_UP_DOWN, 0, 1, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &Route29Route46GateYoungsterScript, -1),
};

const struct MapEvents Route29Route46Gate_MapEvents = {
    .warp_event_count = lengthof(Route29Route46Gate_WarpEvents),
    .warp_events = Route29Route46Gate_WarpEvents,

    .coord_event_count = lengthof(Route29Route46Gate_CoordEvents),
    .coord_events = Route29Route46Gate_CoordEvents,

    .bg_event_count = lengthof(Route29Route46Gate_BGEvents),
    .bg_events = Route29Route46Gate_BGEvents,

    .obj_event_count = lengthof(Route29Route46Gate_ObjectEvents),
    .obj_events = Route29Route46Gate_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "Route29Route46Gate.h"

bool Route29Route46GateOfficerScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(Route29Route46GateOfficerText)
    SCRIPT_END
}
bool Route29Route46GateYoungsterScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(Route29Route46GateYoungsterText)
    SCRIPT_END
}
const txt_cmd_s Route29Route46GateOfficerText[] = {
    text_start("You can't climb"
        t_line "ledges."
        t_para "But you can jump"
        t_line "down from them to"
        t_cont "take a shortcut."
        t_done )
};
const txt_cmd_s Route29Route46GateYoungsterText[] = {
    text_start("Different kinds of"
        t_line "#MON appear"
        t_cont "past here."
        t_para "If you want to"
        t_line "catch them all,"
        t_para "you have to look"
        t_line "everywhere."
        t_done )
    //db(0, 0) // filler
};
