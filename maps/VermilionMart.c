#include "../constants.h"
#include "../util/scripting.h"
#include "VermilionMart.h"
//// EVENTS
enum {
    VERMILIONMART_CLERK = 2,
    VERMILIONMART_SUPER_NERD,
    VERMILIONMART_BEAUTY,
};

const Script_fn_t VermilionMart_SceneScripts[] = {
    0,
};

const struct MapCallback VermilionMart_MapCallbacks[] = {
    0,
};

const struct MapScripts VermilionMart_MapScripts = {
    .scene_script_count = 0, // lengthof(VermilionMart_SceneScripts),
    .scene_scripts = VermilionMart_SceneScripts,

    .callback_count = 0, // lengthof(VermilionMart_MapCallbacks),
    .callbacks = VermilionMart_MapCallbacks,
};

static const struct CoordEvent VermilionMart_CoordEvents[] = {
    0,
};

static const struct BGEvent VermilionMart_BGEvents[] = {
    0,
};

static const struct WarpEventData VermilionMart_WarpEvents[] = {
    warp_event(2, 7, VERMILION_CITY, 5),
    warp_event(3, 7, VERMILION_CITY, 5),
};

static const struct ObjEvent VermilionMart_ObjectEvents[] = {
    object_event(1, 3, SPRITE_CLERK, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &VermilionMartClerkScript, -1),
    object_event(5, 2, SPRITE_SUPER_NERD, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &VermilionMartSuperNerdScript, -1),
    object_event(8, 6, SPRITE_BEAUTY, SPRITEMOVEDATA_WALK_LEFT_RIGHT, 1, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &VermilionMartBeautyScript, -1),
};

const struct MapEvents VermilionMart_MapEvents = {
    .warp_event_count = lengthof(VermilionMart_WarpEvents),
    .warp_events = VermilionMart_WarpEvents,

    .coord_event_count = 0, // lengthof(VermilionMart_CoordEvents),
    .coord_events = VermilionMart_CoordEvents,

    .bg_event_count = 0, // lengthof(VermilionMart_BGEvents),
    .bg_events = VermilionMart_BGEvents,

    .obj_event_count = lengthof(VermilionMart_ObjectEvents),
    .obj_events = VermilionMart_ObjectEvents,
};

//// CODE

bool VermilionMartClerkScript(script_s* s) {
    SCRIPT_BEGIN
    opentext
    pokemart(MARTTYPE_STANDARD, MART_VERMILION)
    closetext
    s_end
    SCRIPT_END
}
bool VermilionMartSuperNerdScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(VermilionMartSuperNerdText)
    SCRIPT_END
}
bool VermilionMartBeautyScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(VermilionMartBeautyText)
    SCRIPT_END
}
const txt_cmd_s VermilionMartSuperNerdText[] = {
    text_start("TEAM ROCKET is no"
        t_line "longer in KANTO."
        t_para "That alone makes"
        t_line "me happy."
        t_done )
};
const txt_cmd_s VermilionMartBeautyText[] = {
    text_start("I'm thinking about"
        t_line "going shopping in"
        t_cont "SAFFRON."
        t_done )
    //db(0, 0) // filler
};
