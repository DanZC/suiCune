#include "../constants.h"
#include "../util/scripting.h"
#include "VioletMart.h"
//// EVENTS
enum {
    VIOLETMART_CLERK = 2,
    VIOLETMART_GRANNY,
    VIOLETMART_COOLTRAINER_M,
};

const Script_fn_t VioletMart_SceneScripts[] = {
    0,
};

const struct MapCallback VioletMart_MapCallbacks[] = {
    0,
};

const struct MapScripts VioletMart_MapScripts = {
    .scene_script_count = 0, // lengthof(VioletMart_SceneScripts),
    .scene_scripts = VioletMart_SceneScripts,

    .callback_count = 0, // lengthof(VioletMart_MapCallbacks),
    .callbacks = VioletMart_MapCallbacks,
};

static const struct CoordEvent VioletMart_CoordEvents[] = {
    0,
};

static const struct BGEvent VioletMart_BGEvents[] = {
    0,
};

static const struct WarpEventData VioletMart_WarpEvents[] = {
    warp_event(2, 7, VIOLET_CITY, 1),
    warp_event(3, 7, VIOLET_CITY, 1),
};

static const struct ObjEvent VioletMart_ObjectEvents[] = {
    object_event(1, 3, SPRITE_CLERK, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &VioletMartClerkScript, -1),
    object_event(7, 6, SPRITE_GRANNY, SPRITEMOVEDATA_WALK_LEFT_RIGHT, 1, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &VioletMartGrannyScript, -1),
    object_event(5, 2, SPRITE_COOLTRAINER_M, SPRITEMOVEDATA_SPINRANDOM_SLOW, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &VioletMartCooltrainerMScript, -1),
};

const struct MapEvents VioletMart_MapEvents = {
    .warp_event_count = lengthof(VioletMart_WarpEvents),
    .warp_events = VioletMart_WarpEvents,

    .coord_event_count = 0, // lengthof(VioletMart_CoordEvents),
    .coord_events = VioletMart_CoordEvents,

    .bg_event_count = 0, // lengthof(VioletMart_BGEvents),
    .bg_events = VioletMart_BGEvents,

    .obj_event_count = lengthof(VioletMart_ObjectEvents),
    .obj_events = VioletMart_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "VioletMart.h"

bool VioletMartClerkScript(script_s* s) {
    SCRIPT_BEGIN
    opentext
    pokemart(MARTTYPE_STANDARD, MART_VIOLET)
    closetext
    s_end
    SCRIPT_END
}
bool VioletMartGrannyScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(VioletMartGrannyText)
    SCRIPT_END
}
bool VioletMartCooltrainerMScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(VioletMartCooltrainerMText)
    SCRIPT_END
}
const txt_cmd_s VioletMartGrannyText[] = {
    text_start("When you first"
        t_line "catch a #MON,"
        t_cont "it may be weak."
        t_para "But it will even-"
        t_line "tually grow to be"
        t_cont "strong."
        t_para "It's important to"
        t_line "treat #MON with"
        t_cont "love."
        t_done )
};
const txt_cmd_s VioletMartCooltrainerMText[] = {
    text_start("#MON can hold"
        t_line "items like POTION"
        t_cont "and ANTIDOTE."
        t_para "But they don't"
        t_line "appear to know how"
        t_para "to use manmade"
        t_line "items."
        t_done )
    //db(0, 0) // filler
};
