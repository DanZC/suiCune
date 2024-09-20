#include "../constants.h"
#include "../util/scripting.h"
#include "PewterMart.h"
//// EVENTS
enum {
    PEWTERMART_CLERK = 2,
    PEWTERMART_YOUNGSTER,
    PEWTERMART_SUPER_NERD,
};

const Script_fn_t PewterMart_SceneScripts[] = {
    0,
};

const struct MapCallback PewterMart_MapCallbacks[] = {
    0,
};

const struct MapScripts PewterMart_MapScripts = {
    .scene_script_count = 0, // lengthof(PewterMart_SceneScripts),
    .scene_scripts = PewterMart_SceneScripts,

    .callback_count = 0, // lengthof(PewterMart_MapCallbacks),
    .callbacks = PewterMart_MapCallbacks,
};

static const struct CoordEvent PewterMart_CoordEvents[] = {
    0,
};

static const struct BGEvent PewterMart_BGEvents[] = {
    0,
};

static const struct WarpEventData PewterMart_WarpEvents[] = {
    warp_event(2, 7, PEWTER_CITY, 3),
    warp_event(3, 7, PEWTER_CITY, 3),
};

static const struct ObjEvent PewterMart_ObjectEvents[] = {
    object_event(1, 3, SPRITE_CLERK, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &PewterMartClerkScript, -1),
    object_event(9, 2, SPRITE_YOUNGSTER, SPRITEMOVEDATA_WALK_LEFT_RIGHT, 2, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &PewterMartYoungsterScript, -1),
    object_event(6, 6, SPRITE_SUPER_NERD, SPRITEMOVEDATA_SPINRANDOM_SLOW, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &PewterMartSuperNerdScript, -1),
};

const struct MapEvents PewterMart_MapEvents = {
    .warp_event_count = lengthof(PewterMart_WarpEvents),
    .warp_events = PewterMart_WarpEvents,

    .coord_event_count = 0, // lengthof(PewterMart_CoordEvents),
    .coord_events = PewterMart_CoordEvents,

    .bg_event_count = 0, // lengthof(PewterMart_BGEvents),
    .bg_events = PewterMart_BGEvents,

    .obj_event_count = lengthof(PewterMart_ObjectEvents),
    .obj_events = PewterMart_ObjectEvents,
};

//// CODE

bool PewterMartClerkScript(script_s* s) {
    SCRIPT_BEGIN
    opentext
    pokemart(MARTTYPE_STANDARD, MART_PEWTER)
    closetext
    s_end
    SCRIPT_END
}
bool PewterMartYoungsterScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(PewterMartYoungsterText)
    SCRIPT_END
}
bool PewterMartSuperNerdScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(PewterMartSuperNerdText)
    SCRIPT_END
}
const txt_cmd_s PewterMartYoungsterText[] = {
    text_start("Hi! Check out my"
        t_line "GYARADOS!"
        t_para "I raised it from a"
        t_line "MAGIKARP. I can't"
        t_para "believe how strong"
        t_line "it has become."
        t_done )
};
const txt_cmd_s PewterMartSuperNerdText[] = {
    text_start("There once was a"
        t_line "weird old man who"
        t_cont "sold MAGIKARP."
        t_para "He was saying the"
        t_line "MAGIKARP from the"
        t_para "LAKE OF RAGE were"
        t_line "excellent."
        t_done )
    //db(0, 0) // filler
};
