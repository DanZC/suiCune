#include "../constants.h"
#include "../util/scripting.h"
#include "Route32RuinsOfAlphGate.h"
//// EVENTS
enum {
    ROUTE32RUINSOFALPHGATE_OFFICER = 2,
    ROUTE32RUINSOFALPHGATE_POKEFAN_M,
    ROUTE32RUINSOFALPHGATE_YOUNGSTER,
};

const Script_fn_t Route32RuinsOfAlphGate_SceneScripts[] = {
    0,
};

const struct MapCallback Route32RuinsOfAlphGate_MapCallbacks[] = {
    0,
};

const struct MapScripts Route32RuinsOfAlphGate_MapScripts = {
    .scene_script_count = 0, // lengthof(Route32RuinsOfAlphGate_SceneScripts),
    .scene_scripts = Route32RuinsOfAlphGate_SceneScripts,

    .callback_count = 0, // lengthof(Route32RuinsOfAlphGate_MapCallbacks),
    .callbacks = Route32RuinsOfAlphGate_MapCallbacks,
};

static const struct CoordEvent Route32RuinsOfAlphGate_CoordEvents[] = {
    0,
};

static const struct BGEvent Route32RuinsOfAlphGate_BGEvents[] = {
    0,
};

static const struct WarpEventData Route32RuinsOfAlphGate_WarpEvents[] = {
    warp_event(0, 4, RUINS_OF_ALPH_OUTSIDE, 10),
    warp_event(0, 5, RUINS_OF_ALPH_OUTSIDE, 11),
    warp_event(9, 4, ROUTE_32, 2),
    warp_event(9, 5, ROUTE_32, 3),
};

static const struct ObjEvent Route32RuinsOfAlphGate_ObjectEvents[] = {
    object_event(5, 2, SPRITE_OFFICER, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &Route32RuinsOfAlphGateOfficerScript, -1),
    object_event(8, 2, SPRITE_POKEFAN_M, SPRITEMOVEDATA_WALK_UP_DOWN, 0, 1, -1, -1, PAL_NPC_BROWN, OBJECTTYPE_SCRIPT, 0, &Route32RuinsOfAlphGatePokefanMScript, -1),
    object_event(1, 6, SPRITE_YOUNGSTER, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &Route32RuinsOfAlphGateYoungsterScript, -1),
};

const struct MapEvents Route32RuinsOfAlphGate_MapEvents = {
    .warp_event_count = lengthof(Route32RuinsOfAlphGate_WarpEvents),
    .warp_events = Route32RuinsOfAlphGate_WarpEvents,

    .coord_event_count = 0, // lengthof(Route32RuinsOfAlphGate_CoordEvents),
    .coord_events = Route32RuinsOfAlphGate_CoordEvents,

    .bg_event_count = 0, // lengthof(Route32RuinsOfAlphGate_BGEvents),
    .bg_events = Route32RuinsOfAlphGate_BGEvents,

    .obj_event_count = lengthof(Route32RuinsOfAlphGate_ObjectEvents),
    .obj_events = Route32RuinsOfAlphGate_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "Route32RuinsOfAlphGate.h"

bool Route32RuinsOfAlphGateOfficerScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(Route32RuinsOfAlphGateOfficerText)
    SCRIPT_END
}
bool Route32RuinsOfAlphGatePokefanMScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(Route32RuinsOfAlphGatePokefanMText)
    SCRIPT_END
}
bool Route32RuinsOfAlphGateYoungsterScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(Route32RuinsOfAlphGateYoungsterText)
    SCRIPT_END
}
const txt_cmd_s Route32RuinsOfAlphGateOfficerText[] = {
    text_start("RUINS OF ALPH"
        t_para "A Look-and-Touch"
        t_line "Tourist Site"
        t_para "Try the sliding"
        t_line "stone panels!"
        t_done )
};
const txt_cmd_s Route32RuinsOfAlphGatePokefanMText[] = {
    text_start("You're studying"
        t_line "the RUINS?"
        t_para "I see a scientist"
        t_line "in the making."
        t_done )
};
const txt_cmd_s Route32RuinsOfAlphGateYoungsterText[] = {
    text_start("There are drawings"
        t_line "on stone panels."
        t_para "I tried moving"
        t_line "them. I wonder"
        t_cont "what they are."
        t_done )
    //db(0, 0) // filler
};
