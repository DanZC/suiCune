#include "../constants.h"
#include "../util/scripting.h"
#include "Route5UndergroundPathEntrance.h"
//// EVENTS
enum {
    ROUTE5UNDERGROUNDPATHENTRANCE_TEACHER = 2,
};

const Script_fn_t Route5UndergroundPathEntrance_SceneScripts[] = {
    0,
};

const struct MapCallback Route5UndergroundPathEntrance_MapCallbacks[] = {
    0,
};

const struct MapScripts Route5UndergroundPathEntrance_MapScripts = {
    .scene_script_count = 0, // lengthof(Route5UndergroundPathEntrance_SceneScripts),
    .scene_scripts = Route5UndergroundPathEntrance_SceneScripts,

    .callback_count = 0, // lengthof(Route5UndergroundPathEntrance_MapCallbacks),
    .callbacks = Route5UndergroundPathEntrance_MapCallbacks,
};

static const struct CoordEvent Route5UndergroundPathEntrance_CoordEvents[] = {
    0,
};

static const struct BGEvent Route5UndergroundPathEntrance_BGEvents[] = {
    0,
};

static const struct WarpEventData Route5UndergroundPathEntrance_WarpEvents[] = {
    warp_event(3, 7, ROUTE_5, 1),
    warp_event(4, 7, ROUTE_5, 1),
    warp_event(4, 3, UNDERGROUND_PATH, 1),
};

static const struct ObjEvent Route5UndergroundPathEntrance_ObjectEvents[] = {
    object_event(2, 2, SPRITE_TEACHER, SPRITEMOVEDATA_WANDER, 1, 1, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &Route5UndergroundPathEntranceTeacherScript, -1),
};

const struct MapEvents Route5UndergroundPathEntrance_MapEvents = {
    .warp_event_count = lengthof(Route5UndergroundPathEntrance_WarpEvents),
    .warp_events = Route5UndergroundPathEntrance_WarpEvents,

    .coord_event_count = 0, // lengthof(Route5UndergroundPathEntrance_CoordEvents),
    .coord_events = Route5UndergroundPathEntrance_CoordEvents,

    .bg_event_count = 0, // lengthof(Route5UndergroundPathEntrance_BGEvents),
    .bg_events = Route5UndergroundPathEntrance_BGEvents,

    .obj_event_count = lengthof(Route5UndergroundPathEntrance_ObjectEvents),
    .obj_events = Route5UndergroundPathEntrance_ObjectEvents,
};

//// CODE

bool Route5UndergroundPathEntranceTeacherScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(Route5UndergroundPathEntranceTeacherText)
    SCRIPT_END
}
const txt_cmd_s Route5UndergroundPathEntranceTeacherText[] = {
    text_start("Many cities in"
        t_line "JOHTO have long"
        t_para "histories. I'd"
        t_line "love to visit!"
        t_done )
    //db(0, 0) // filler
};
