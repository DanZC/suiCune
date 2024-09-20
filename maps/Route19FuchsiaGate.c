#include "../constants.h"
#include "../util/scripting.h"
#include "Route19FuchsiaGate.h"
//// EVENTS
enum {
    ROUTE19FUCHSIAGATE_OFFICER = 2,
};

const Script_fn_t Route19FuchsiaGate_SceneScripts[] = {
    0,
};

const struct MapCallback Route19FuchsiaGate_MapCallbacks[] = {
    0,
};

const struct MapScripts Route19FuchsiaGate_MapScripts = {
    .scene_script_count = 0, // lengthof(Route19FuchsiaGate_SceneScripts),
    .scene_scripts = Route19FuchsiaGate_SceneScripts,

    .callback_count = 0, // lengthof(Route19FuchsiaGate_MapCallbacks),
    .callbacks = Route19FuchsiaGate_MapCallbacks,
};

static const struct CoordEvent Route19FuchsiaGate_CoordEvents[] = {
    0,
};

static const struct BGEvent Route19FuchsiaGate_BGEvents[] = {
    0,
};

static const struct WarpEventData Route19FuchsiaGate_WarpEvents[] = {
    warp_event(4, 0, FUCHSIA_CITY, 10),
    warp_event(5, 0, FUCHSIA_CITY, 11),
    warp_event(4, 7, ROUTE_19, 1),
    warp_event(5, 7, ROUTE_19, 1),
};

static const struct ObjEvent Route19FuchsiaGate_ObjectEvents[] = {
    object_event(0, 4, SPRITE_OFFICER, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &Route19FuchsiaGateOfficerScript, -1),
};

const struct MapEvents Route19FuchsiaGate_MapEvents = {
    .warp_event_count = lengthof(Route19FuchsiaGate_WarpEvents),
    .warp_events = Route19FuchsiaGate_WarpEvents,

    .coord_event_count = 0, // lengthof(Route19FuchsiaGate_CoordEvents),
    .coord_events = Route19FuchsiaGate_CoordEvents,

    .bg_event_count = 0, // lengthof(Route19FuchsiaGate_BGEvents),
    .bg_events = Route19FuchsiaGate_BGEvents,

    .obj_event_count = lengthof(Route19FuchsiaGate_ObjectEvents),
    .obj_events = Route19FuchsiaGate_ObjectEvents,
};

//// CODE

bool Route19FuchsiaGateOfficerScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_CINNABAR_ROCKS_CLEARED)
    iftrue(RocksCleared)
    writetext(Route19FuchsiaGateOfficerText)
    waitbutton
    closetext
    s_end
RocksCleared:
    writetext(Route19FuchsiaGateOfficerText_RocksCleared)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const txt_cmd_s Route19FuchsiaGateOfficerText[] = {
    text_start("CINNABAR's volcano"
        t_line "erupted."
        t_para "It hurled boulders"
        t_line "that cut off ROUTE"
        t_cont "19 indefinitely."
        t_para "I wonder if the"
        t_line "people of CINNABAR"
        t_cont "are safe…"
        t_done )
};
const txt_cmd_s Route19FuchsiaGateOfficerText_RocksCleared[] = {
    text_start("No CINNABAR citi-"
        t_line "zens were injured"
        t_para "by the eruption."
        t_line "That's great!"
        t_done )
    //db(0, 0) // filler
};
