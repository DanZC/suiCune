#include "../constants.h"
#include "../util/scripting.h"
#include "OlivineLighthouse1F.h"
//// EVENTS
enum {
    OLIVINELIGHTHOUSE1F_SAILOR = 2,
    OLIVINELIGHTHOUSE1F_POKEFAN_F,
};

const Script_fn_t OlivineLighthouse1F_SceneScripts[] = {
    0,
};

const struct MapCallback OlivineLighthouse1F_MapCallbacks[] = {
    0,
};

const struct MapScripts OlivineLighthouse1F_MapScripts = {
    .scene_script_count = 0, // lengthof(OlivineLighthouse1F_SceneScripts),
    .scene_scripts = OlivineLighthouse1F_SceneScripts,

    .callback_count = 0, // lengthof(OlivineLighthouse1F_MapCallbacks),
    .callbacks = OlivineLighthouse1F_MapCallbacks,
};

static const struct CoordEvent OlivineLighthouse1F_CoordEvents[] = {
    0,
};

static const struct BGEvent OlivineLighthouse1F_BGEvents[] = {
    0,
};

static const struct WarpEventData OlivineLighthouse1F_WarpEvents[] = {
    warp_event(10, 17, OLIVINE_CITY, 9),
    warp_event(11, 17, OLIVINE_CITY, 9),
    warp_event(3, 11, OLIVINE_LIGHTHOUSE_2F, 1),
    warp_event(16, 13, OLIVINE_LIGHTHOUSE_2F, 3),
    warp_event(17, 13, OLIVINE_LIGHTHOUSE_2F, 4),
};

static const struct ObjEvent OlivineLighthouse1F_ObjectEvents[] = {
    object_event(8, 2, SPRITE_SAILOR, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &OlivineLighthouse1FSailorScript, -1),
    object_event(16, 9, SPRITE_POKEFAN_F, SPRITEMOVEDATA_WALK_UP_DOWN, 0, 2, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &OlivineLighthouse1FPokefanFScript, -1),
};

const struct MapEvents OlivineLighthouse1F_MapEvents = {
    .warp_event_count = lengthof(OlivineLighthouse1F_WarpEvents),
    .warp_events = OlivineLighthouse1F_WarpEvents,

    .coord_event_count = 0, // lengthof(OlivineLighthouse1F_CoordEvents),
    .coord_events = OlivineLighthouse1F_CoordEvents,

    .bg_event_count = 0, // lengthof(OlivineLighthouse1F_BGEvents),
    .bg_events = OlivineLighthouse1F_BGEvents,

    .obj_event_count = lengthof(OlivineLighthouse1F_ObjectEvents),
    .obj_events = OlivineLighthouse1F_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "OlivineLighthouse1F.h"

bool OlivineLighthouse1FSailorScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(OlivineLighthouse1FSailorText)
    SCRIPT_END
}
bool OlivineLighthouse1FPokefanFScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(OlivineLighthouse1FPokefanFText)
    SCRIPT_END
}
const txt_cmd_s OlivineLighthouse1FSailorText[] = {
    text_start("People train at"
        t_line "this LIGHTHOUSE."
        t_para "It's not easy to"
        t_line "climb because of"
        t_cont "all the trainers."
        t_done )
};
const txt_cmd_s OlivineLighthouse1FPokefanFText[] = {
    text_start("In the past, #-"
        t_line "MON used to light"
        t_para "the sea around"
        t_line "OLIVINE at night."
        t_para "The LIGHTHOUSE was"
        t_line "made in honor of"
        t_cont "those #MON."
        t_done )
    //db(0, 0) // filler
};
