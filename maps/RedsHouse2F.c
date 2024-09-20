#include "../constants.h"
#include "../util/scripting.h"
#include "RedsHouse2F.h"
//// EVENTS
const Script_fn_t RedsHouse2F_SceneScripts[] = {
    0,
};

const struct MapCallback RedsHouse2F_MapCallbacks[] = {
    0,
};

const struct MapScripts RedsHouse2F_MapScripts = {
    .scene_script_count = 0, // lengthof(RedsHouse2F_SceneScripts),
    .scene_scripts = RedsHouse2F_SceneScripts,

    .callback_count = 0, // lengthof(RedsHouse2F_MapCallbacks),
    .callbacks = RedsHouse2F_MapCallbacks,
};

static const struct CoordEvent RedsHouse2F_CoordEvents[] = {
    0,
};

static const struct BGEvent RedsHouse2F_BGEvents[] = {
    bg_event(3, 5, BGEVENT_READ, &RedsHouse2FN64Script),
    bg_event(0, 1, BGEVENT_READ, &RedsHouse2FPCScript),
};

static const struct WarpEventData RedsHouse2F_WarpEvents[] = {
    warp_event(7, 0, REDS_HOUSE_1F, 3),
};

static const struct ObjEvent RedsHouse2F_ObjectEvents[] = {
    0,
};

const struct MapEvents RedsHouse2F_MapEvents = {
    .warp_event_count = lengthof(RedsHouse2F_WarpEvents),
    .warp_events = RedsHouse2F_WarpEvents,

    .coord_event_count = 0, // lengthof(RedsHouse2F_CoordEvents),
    .coord_events = RedsHouse2F_CoordEvents,

    .bg_event_count = lengthof(RedsHouse2F_BGEvents),
    .bg_events = RedsHouse2F_BGEvents,

    .obj_event_count = 0, // lengthof(RedsHouse2F_ObjectEvents),
    .obj_events = RedsHouse2F_ObjectEvents,
};

//// CODE

bool RedsHouse2FN64Script(script_s* s) {
    SCRIPT_BEGIN
    jumptext(RedsHouse2FN64Text)
    SCRIPT_END
}
bool RedsHouse2FPCScript(script_s* s) {
    SCRIPT_BEGIN
    jumptext(RedsHouse2FPCText)
    SCRIPT_END
}
const txt_cmd_s RedsHouse2FN64Text[] = {
    text_start("<PLAYER> played the"
        t_line "N64."
        t_para "Better get going--"
        t_line "no time to lose!"
        t_done )
};
const txt_cmd_s RedsHouse2FPCText[] = {
    text_start("It looks like it"
        t_line "hasn't been used"
        t_cont "in a long time…"
        t_done )
    //db(0, 0) // filler
};
