#include "../constants.h"
#include "../util/scripting.h"
#include "VermilionPortPassage.h"
//// EVENTS
enum {
    VERMILIONPORTPASSAGE_TEACHER = 2,
};

const Script_fn_t VermilionPortPassage_SceneScripts[] = {
    0,
};

const struct MapCallback VermilionPortPassage_MapCallbacks[] = {
    0,
};

const struct MapScripts VermilionPortPassage_MapScripts = {
    .scene_script_count = 0, // lengthof(VermilionPortPassage_SceneScripts),
    .scene_scripts = VermilionPortPassage_SceneScripts,

    .callback_count = 0, // lengthof(VermilionPortPassage_MapCallbacks),
    .callbacks = VermilionPortPassage_MapCallbacks,
};

static const struct CoordEvent VermilionPortPassage_CoordEvents[] = {
    0,
};

static const struct BGEvent VermilionPortPassage_BGEvents[] = {
    0,
};

static const struct WarpEventData VermilionPortPassage_WarpEvents[] = {
    warp_event(15, 0, VERMILION_CITY, 8),
    warp_event(16, 0, VERMILION_CITY, 9),
    warp_event(15, 4, VERMILION_PORT_PASSAGE, 4),
    warp_event(3, 2, VERMILION_PORT_PASSAGE, 3),
    warp_event(3, 14, VERMILION_PORT, 1),
};

static const struct ObjEvent VermilionPortPassage_ObjectEvents[] = {
    object_event(17, 1, SPRITE_TEACHER, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &VermilionPortPassageTeacherScript, -1),
};

const struct MapEvents VermilionPortPassage_MapEvents = {
    .warp_event_count = lengthof(VermilionPortPassage_WarpEvents),
    .warp_events = VermilionPortPassage_WarpEvents,

    .coord_event_count = 0, // lengthof(VermilionPortPassage_CoordEvents),
    .coord_events = VermilionPortPassage_CoordEvents,

    .bg_event_count = 0, // lengthof(VermilionPortPassage_BGEvents),
    .bg_events = VermilionPortPassage_BGEvents,

    .obj_event_count = lengthof(VermilionPortPassage_ObjectEvents),
    .obj_events = VermilionPortPassage_ObjectEvents,
};

//// CODE

bool VermilionPortPassageTeacherScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(VermilionPortPassageTeacherText)
    SCRIPT_END
}
const txt_cmd_s VermilionPortPassageTeacherText[] = {
    text_start("The FAST SHIP"
        t_line "sails on Wednes-"
        t_cont "days and Sundays"
        t_cont "every week."
        t_done )
    //db(0, 0) // filler
};
