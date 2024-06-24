#include "../constants.h"
#include "../util/scripting.h"
#include "Route43MahoganyGate.h"
//// EVENTS
enum {
    ROUTE43MAHOGANYGATE_OFFICER = 2,
};

const Script_fn_t Route43MahoganyGate_SceneScripts[] = {
    0,
};

const struct MapCallback Route43MahoganyGate_MapCallbacks[] = {
    0,
};

const struct MapScripts Route43MahoganyGate_MapScripts = {
    .scene_script_count = 0, // lengthof(Route43MahoganyGate_SceneScripts),
    .scene_scripts = Route43MahoganyGate_SceneScripts,

    .callback_count = 0, // lengthof(Route43MahoganyGate_MapCallbacks),
    .callbacks = Route43MahoganyGate_MapCallbacks,
};

static const struct CoordEvent Route43MahoganyGate_CoordEvents[] = {
    0,
};

static const struct BGEvent Route43MahoganyGate_BGEvents[] = {
    0,
};

static const struct WarpEventData Route43MahoganyGate_WarpEvents[] = {
    warp_event(4, 0, ROUTE_43, 1),
    warp_event(5, 0, ROUTE_43, 2),
    warp_event(4, 7, MAHOGANY_TOWN, 5),
    warp_event(5, 7, MAHOGANY_TOWN, 5),
};

static const struct ObjEvent Route43MahoganyGate_ObjectEvents[] = {
    object_event(0, 4, SPRITE_OFFICER, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &Route43MahoganyGateOfficer, -1),
};

const struct MapEvents Route43MahoganyGate_MapEvents = {
    .warp_event_count = lengthof(Route43MahoganyGate_WarpEvents),
    .warp_events = Route43MahoganyGate_WarpEvents,

    .coord_event_count = 0, // lengthof(Route43MahoganyGate_CoordEvents),
    .coord_events = Route43MahoganyGate_CoordEvents,

    .bg_event_count = 0, // lengthof(Route43MahoganyGate_BGEvents),
    .bg_events = Route43MahoganyGate_BGEvents,

    .obj_event_count = lengthof(Route43MahoganyGate_ObjectEvents),
    .obj_events = Route43MahoganyGate_ObjectEvents,
};

//// CODE

bool Route43MahoganyGateOfficer(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_CLEARED_ROCKET_HIDEOUT)
    iftrue(RocketsCleared)
    writetext(Route43MahoganyGateOfficerText)
    waitbutton
    closetext
    s_end
RocketsCleared:
    writetext(Route43MahoganyGateOfficerRocketsClearedText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const txt_cmd_s Route43MahoganyGateOfficerText[] = {
    text_start("Only people headed"
        t_line "up to LAKE OF RAGE"
        t_para "have been through"
        t_line "here lately."
        t_done )
};
const txt_cmd_s Route43MahoganyGateOfficerRocketsClearedText[] = {
    text_start("Nobody goes up to"
        t_line "LAKE OF RAGE these"
        t_cont "days."
        t_done )
    //db(0, 0) // filler
};
