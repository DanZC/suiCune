#include "../constants.h"
#include "../util/scripting.h"
#include "ViridianMart.h"
//// EVENTS
enum {
    VIRIDIANMART_CLERK = 2,
    VIRIDIANMART_LASS,
    VIRIDIANMART_COOLTRAINER_M,
};

const Script_fn_t ViridianMart_SceneScripts[] = {
    0,
};

const struct MapCallback ViridianMart_MapCallbacks[] = {
    0,
};

const struct MapScripts ViridianMart_MapScripts = {
    .scene_script_count = 0, // lengthof(ViridianMart_SceneScripts),
    .scene_scripts = ViridianMart_SceneScripts,

    .callback_count = 0, // lengthof(ViridianMart_MapCallbacks),
    .callbacks = ViridianMart_MapCallbacks,
};

static const struct CoordEvent ViridianMart_CoordEvents[] = {
    0,
};

static const struct BGEvent ViridianMart_BGEvents[] = {
    0,
};

static const struct WarpEventData ViridianMart_WarpEvents[] = {
    warp_event(2, 7, VIRIDIAN_CITY, 4),
    warp_event(3, 7, VIRIDIAN_CITY, 4),
};

static const struct ObjEvent ViridianMart_ObjectEvents[] = {
    object_event(1, 3, SPRITE_CLERK, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &ViridianMartClerkScript, -1),
    object_event(7, 2, SPRITE_LASS, SPRITEMOVEDATA_WALK_LEFT_RIGHT, 2, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &ViridianMartLassScript, -1),
    object_event(1, 6, SPRITE_COOLTRAINER_M, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &ViridianMartCooltrainerMScript, -1),
};

const struct MapEvents ViridianMart_MapEvents = {
    .warp_event_count = lengthof(ViridianMart_WarpEvents),
    .warp_events = ViridianMart_WarpEvents,

    .coord_event_count = 0, // lengthof(ViridianMart_CoordEvents),
    .coord_events = ViridianMart_CoordEvents,

    .bg_event_count = 0, // lengthof(ViridianMart_BGEvents),
    .bg_events = ViridianMart_BGEvents,

    .obj_event_count = lengthof(ViridianMart_ObjectEvents),
    .obj_events = ViridianMart_ObjectEvents,
};

//// CODE

bool ViridianMartClerkScript(script_s* s) {
    SCRIPT_BEGIN
    opentext
    pokemart(MARTTYPE_STANDARD, MART_VIRIDIAN)
    closetext
    s_end
    SCRIPT_END
}
bool ViridianMartLassScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(ViridianMartLassText)
    SCRIPT_END
}
bool ViridianMartCooltrainerMScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(ViridianMartCooltrainerMText)
    SCRIPT_END
}
const txt_cmd_s ViridianMartLassText[] = {
    text_start("The GYM LEADER"
        t_line "here is totally"
        t_cont "cool."
        t_done )
};
const txt_cmd_s ViridianMartCooltrainerMText[] = {
    text_start("Have you been to"
        t_line "CINNABAR?"
        t_para "It's an island way"
        t_line "south of here."
        t_done )
    //db(0, 0) // filler
};
