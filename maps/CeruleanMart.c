#include "../constants.h"
#include "../util/scripting.h"
#include "CeruleanMart.h"
//// EVENTS
enum {
    CERULEANMART_CLERK = 2,
    CERULEANMART_COOLTRAINER_M,
    CERULEANMART_COOLTRAINER_F,
};

const Script_fn_t CeruleanMart_SceneScripts[] = {
    0,
};

const struct MapCallback CeruleanMart_MapCallbacks[] = {
    0,
};

const struct MapScripts CeruleanMart_MapScripts = {
    .scene_script_count = 0, // lengthof(CeruleanMart_SceneScripts),
    .scene_scripts = CeruleanMart_SceneScripts,

    .callback_count = 0, // lengthof(CeruleanMart_MapCallbacks),
    .callbacks = CeruleanMart_MapCallbacks,
};

static const struct CoordEvent CeruleanMart_CoordEvents[] = {
    0,
};

static const struct BGEvent CeruleanMart_BGEvents[] = {
    0,
};

static const struct WarpEventData CeruleanMart_WarpEvents[] = {
    warp_event(2, 7, CERULEAN_CITY, 6),
    warp_event(3, 7, CERULEAN_CITY, 6),
};

static const struct ObjEvent CeruleanMart_ObjectEvents[] = {
    object_event(1, 3, SPRITE_CLERK, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &CeruleanMart_Clerk, -1),
    object_event(1, 6, SPRITE_COOLTRAINER_M, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &CeruleanMart_CooltrainerM, -1),
    object_event(7, 2, SPRITE_COOLTRAINER_F, SPRITEMOVEDATA_WALK_LEFT_RIGHT, 2, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &CeruleanMart_CooltrainerF, -1),
};

const struct MapEvents CeruleanMart_MapEvents = {
    .warp_event_count = lengthof(CeruleanMart_WarpEvents),
    .warp_events = CeruleanMart_WarpEvents,

    .coord_event_count = 0, // lengthof(CeruleanMart_CoordEvents),
    .coord_events = CeruleanMart_CoordEvents,

    .bg_event_count = 0, // lengthof(CeruleanMart_BGEvents),
    .bg_events = CeruleanMart_BGEvents,

    .obj_event_count = lengthof(CeruleanMart_ObjectEvents),
    .obj_events = CeruleanMart_ObjectEvents,
};

//// CODE

bool CeruleanMart_Clerk(script_s* s) {
    SCRIPT_BEGIN
    opentext
    pokemart(MARTTYPE_STANDARD, MART_CERULEAN)
    closetext
    s_end
    SCRIPT_END
}
bool CeruleanMart_CooltrainerM(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(CeruleanMart_CooltrainerMText)
    SCRIPT_END
}
bool CeruleanMart_CooltrainerF(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(CeruleanMart_CooltrainerFText)
    SCRIPT_END
}
const txt_cmd_s CeruleanMart_CooltrainerMText[] = {
    text_start("You'll run into"
        t_line "many trainers on"
        t_para "the way to CERU-"
        t_line "LEAN's CAPE."
        t_para "They want to see"
        t_line "how they stack"
        t_para "up against other"
        t_line "trainers."
        t_done )
};
const txt_cmd_s CeruleanMart_CooltrainerFText[] = {
    text_start("MISTY is about the"
        t_line "only person in"
        t_para "town who can beat"
        t_line "the trainers at"
        t_cont "CERULEAN's CAPE."
        t_done )
    //db(0, 0) // filler
};
