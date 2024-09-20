#include "../constants.h"
#include "../util/scripting.h"
#include "DiglettsCave.h"
//// EVENTS
enum {
    DIGLETTSCAVE_POKEFAN_M = 2,
};

const Script_fn_t DiglettsCave_SceneScripts[] = {
    0,
};

const struct MapCallback DiglettsCave_MapCallbacks[] = {
    0,
};

const struct MapScripts DiglettsCave_MapScripts = {
    .scene_script_count = 0, // lengthof(DiglettsCave_SceneScripts),
    .scene_scripts = DiglettsCave_SceneScripts,

    .callback_count = 0, // lengthof(DiglettsCave_MapCallbacks),
    .callbacks = DiglettsCave_MapCallbacks,
};

static const struct CoordEvent DiglettsCave_CoordEvents[] = {
    0,
};

static const struct BGEvent DiglettsCave_BGEvents[] = {
    bg_event(6, 11, BGEVENT_ITEM, &DiglettsCaveHiddenMaxRevive),
};

static const struct WarpEventData DiglettsCave_WarpEvents[] = {
    warp_event(3, 33, VERMILION_CITY, 10),
    warp_event(5, 31, DIGLETTS_CAVE, 5),
    warp_event(15, 5, ROUTE_2, 5),
    warp_event(17, 3, DIGLETTS_CAVE, 6),
    warp_event(17, 33, DIGLETTS_CAVE, 2),
    warp_event(3, 3, DIGLETTS_CAVE, 4),
};

static const struct ObjEvent DiglettsCave_ObjectEvents[] = {
    object_event(3, 31, SPRITE_POKEFAN_M, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &DiglettsCavePokefanMScript, -1),
};

const struct MapEvents DiglettsCave_MapEvents = {
    .warp_event_count = lengthof(DiglettsCave_WarpEvents),
    .warp_events = DiglettsCave_WarpEvents,

    .coord_event_count = 0, // lengthof(DiglettsCave_CoordEvents),
    .coord_events = DiglettsCave_CoordEvents,

    .bg_event_count = lengthof(DiglettsCave_BGEvents),
    .bg_events = DiglettsCave_BGEvents,

    .obj_event_count = lengthof(DiglettsCave_ObjectEvents),
    .obj_events = DiglettsCave_ObjectEvents,
};

//// CODE

bool DiglettsCavePokefanMScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(DiglettsCavePokefanMText)
    SCRIPT_END
}
const struct HiddenItem DiglettsCaveHiddenMaxRevive = {MAX_REVIVE, EVENT_DIGLETTS_CAVE_HIDDEN_MAX_REVIVE};
const txt_cmd_s DiglettsCavePokefanMText[] = {
    text_start("A bunch of DIGLETT"
        t_line "popped out of the"
        t_para "ground! That was"
        t_line "shocking."
        t_done )
    //db(0, 0) // filler
};
