#include "../constants.h"
#include "../util/scripting.h"
#include "SaffronMart.h"
//// EVENTS
enum {
    SAFFRONMART_CLERK = 2,
    SAFFRONMART_COOLTRAINER_M,
    SAFFRONMART_COOLTRAINER_F,
};

const Script_fn_t SaffronMart_SceneScripts[] = {
    0,
};

const struct MapCallback SaffronMart_MapCallbacks[] = {
    0,
};

const struct MapScripts SaffronMart_MapScripts = {
    .scene_script_count = 0, // lengthof(SaffronMart_SceneScripts),
    .scene_scripts = SaffronMart_SceneScripts,

    .callback_count = 0, // lengthof(SaffronMart_MapCallbacks),
    .callbacks = SaffronMart_MapCallbacks,
};

static const struct CoordEvent SaffronMart_CoordEvents[] = {
    0,
};

static const struct BGEvent SaffronMart_BGEvents[] = {
    0,
};

static const struct WarpEventData SaffronMart_WarpEvents[] = {
    warp_event(2, 7, SAFFRON_CITY, 3),
    warp_event(3, 7, SAFFRON_CITY, 3),
};

static const struct ObjEvent SaffronMart_ObjectEvents[] = {
    object_event(1, 3, SPRITE_CLERK, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &SaffronMartClerkScript, -1),
    object_event(7, 2, SPRITE_COOLTRAINER_M, SPRITEMOVEDATA_SPINRANDOM_SLOW, 0, 0, -1, -1, PAL_NPC_BROWN, OBJECTTYPE_SCRIPT, 0, &SaffronMartCooltrainerMScript, -1),
    object_event(7, 6, SPRITE_COOLTRAINER_F, SPRITEMOVEDATA_WALK_LEFT_RIGHT, 1, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &SaffronMartCooltrainerFScript, -1),
};

const struct MapEvents SaffronMart_MapEvents = {
    .warp_event_count = lengthof(SaffronMart_WarpEvents),
    .warp_events = SaffronMart_WarpEvents,

    .coord_event_count = 0, // lengthof(SaffronMart_CoordEvents),
    .coord_events = SaffronMart_CoordEvents,

    .bg_event_count = 0, // lengthof(SaffronMart_BGEvents),
    .bg_events = SaffronMart_BGEvents,

    .obj_event_count = lengthof(SaffronMart_ObjectEvents),
    .obj_events = SaffronMart_ObjectEvents,
};

//// CODE

bool SaffronMartClerkScript(script_s* s) {
    SCRIPT_BEGIN
    opentext
    pokemart(MARTTYPE_STANDARD, MART_SAFFRON)
    closetext
    s_end
    SCRIPT_END
}
bool SaffronMartCooltrainerMScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(SaffronMartCooltrainerMText)
    SCRIPT_END
}
bool SaffronMartCooltrainerFScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(SaffronMartCooltrainerFText)
    SCRIPT_END
}
const txt_cmd_s SaffronMartCooltrainerMText[] = {
    text_start("There's a big"
        t_line "RADIO TOWER in"
        t_cont "LAVENDER."
        t_done )
};
const txt_cmd_s SaffronMartCooltrainerFText[] = {
    text_start("I want to become"
        t_line "stronger, but I'm"
        t_cont "not good yet…"
        t_para "Could you show me"
        t_line "how sometime?"
        t_done )
    //db(0, 0) // filler
};
