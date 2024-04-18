#include "../constants.h"
#include "../util/scripting.h"
#include "Route36RuinsOfAlphGate.h"
//// EVENTS
enum {
    ROUTE36RUINSOFALPHGATE_OFFICER = 2,
    ROUTE36RUINSOFALPHGATE_GRAMPS,
};

const Script_fn_t Route36RuinsOfAlphGate_SceneScripts[] = {
    0,
};

const struct MapCallback Route36RuinsOfAlphGate_MapCallbacks[] = {
    0,
};

const struct MapScripts Route36RuinsOfAlphGate_MapScripts = {
    .scene_script_count = 0, // lengthof(Route36RuinsOfAlphGate_SceneScripts),
    .scene_scripts = Route36RuinsOfAlphGate_SceneScripts,

    .callback_count = 0, // lengthof(Route36RuinsOfAlphGate_MapCallbacks),
    .callbacks = Route36RuinsOfAlphGate_MapCallbacks,
};

static const struct CoordEvent Route36RuinsOfAlphGate_CoordEvents[] = {
    0,
};

static const struct BGEvent Route36RuinsOfAlphGate_BGEvents[] = {
    0,
};

static const struct WarpEventData Route36RuinsOfAlphGate_WarpEvents[] = {
    warp_event(4, 0, ROUTE_36, 3),
    warp_event(5, 0, ROUTE_36, 4),
    warp_event(4, 7, RUINS_OF_ALPH_OUTSIDE, 9),
    warp_event(5, 7, RUINS_OF_ALPH_OUTSIDE, 9),
};

static const struct ObjEvent Route36RuinsOfAlphGate_ObjectEvents[] = {
    object_event(0, 4, SPRITE_OFFICER, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &Route36RuinsOfAlphGateOfficerScript, -1),
    object_event(7, 5, SPRITE_GRAMPS, SPRITEMOVEDATA_WANDER, 1, 2, -1, -1, PAL_NPC_BROWN, OBJECTTYPE_SCRIPT, 0, &Route36RuinsOfAlphGateGrampsScript, -1),
};

const struct MapEvents Route36RuinsOfAlphGate_MapEvents = {
    .warp_event_count = lengthof(Route36RuinsOfAlphGate_WarpEvents),
    .warp_events = Route36RuinsOfAlphGate_WarpEvents,

    .coord_event_count = 0, // lengthof(Route36RuinsOfAlphGate_CoordEvents),
    .coord_events = Route36RuinsOfAlphGate_CoordEvents,

    .bg_event_count = 0, // lengthof(Route36RuinsOfAlphGate_BGEvents),
    .bg_events = Route36RuinsOfAlphGate_BGEvents,

    .obj_event_count = lengthof(Route36RuinsOfAlphGate_ObjectEvents),
    .obj_events = Route36RuinsOfAlphGate_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "Route36RuinsOfAlphGate.h"

bool Route36RuinsOfAlphGateOfficerScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(Route36RuinsOfAlphGateOfficerText)
    SCRIPT_END
}
bool Route36RuinsOfAlphGateGrampsScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(Route36RuinsOfAlphGateGrampsText)
    SCRIPT_END
}
const txt_cmd_s Route36RuinsOfAlphGateOfficerText[] = {
    text_start("Don't you wonder"
        t_line "who'd make some-"
        t_cont "thing like this?"
        t_cont "And why?"
        t_done )
};
const txt_cmd_s Route36RuinsOfAlphGateGrampsText[] = {
    text_start("Did you see that"
        t_line "strange tree in"
        t_cont "the road?"
        t_para "That may explain"
        t_line "why fewer people"
        t_para "are visiting the"
        t_line "RUINS OF ALPH."
        t_done )
    //db(0, 0) // filler
};
