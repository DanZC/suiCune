#include "../constants.h"
#include "../util/scripting.h"
#include "EcruteakMart.h"
//// EVENTS
enum {
    ECRUTEAKMART_CLERK = 2,
    ECRUTEAKMART_SUPER_NERD,
    ECRUTEAKMART_GRANNY,
};

const Script_fn_t EcruteakMart_SceneScripts[] = {
    0,
};

const struct MapCallback EcruteakMart_MapCallbacks[] = {
    0,
};

const struct MapScripts EcruteakMart_MapScripts = {
    .scene_script_count = 0, // lengthof(EcruteakMart_SceneScripts),
    .scene_scripts = EcruteakMart_SceneScripts,

    .callback_count = 0, // lengthof(EcruteakMart_MapCallbacks),
    .callbacks = EcruteakMart_MapCallbacks,
};

static const struct CoordEvent EcruteakMart_CoordEvents[] = {
    0,
};

static const struct BGEvent EcruteakMart_BGEvents[] = {
    0,
};

static const struct WarpEventData EcruteakMart_WarpEvents[] = {
    warp_event(2, 7, ECRUTEAK_CITY, 9),
    warp_event(3, 7, ECRUTEAK_CITY, 9),
};

static const struct ObjEvent EcruteakMart_ObjectEvents[] = {
    object_event(1, 3, SPRITE_CLERK, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &EcruteakMartClerkScript, -1),
    object_event(5, 2, SPRITE_SUPER_NERD, SPRITEMOVEDATA_WALK_LEFT_RIGHT, 1, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &EcruteakMartSuperNerdScript, -1),
    object_event(6, 6, SPRITE_GRANNY, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &EcruteakMartGrannyScript, -1),
};

const struct MapEvents EcruteakMart_MapEvents = {
    .warp_event_count = lengthof(EcruteakMart_WarpEvents),
    .warp_events = EcruteakMart_WarpEvents,

    .coord_event_count = 0, // lengthof(EcruteakMart_CoordEvents),
    .coord_events = EcruteakMart_CoordEvents,

    .bg_event_count = 0, // lengthof(EcruteakMart_BGEvents),
    .bg_events = EcruteakMart_BGEvents,

    .obj_event_count = lengthof(EcruteakMart_ObjectEvents),
    .obj_events = EcruteakMart_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "EcruteakMart.h"

bool EcruteakMartClerkScript(script_s* s) {
    SCRIPT_BEGIN
    opentext
    pokemart(MARTTYPE_STANDARD, MART_ECRUTEAK)
    closetext
    s_end
    SCRIPT_END
}
bool EcruteakMartSuperNerdScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(EcruteakMartSuperNerdText)
    SCRIPT_END
}
bool EcruteakMartGrannyScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(EcruteakMartGrannyText)
    SCRIPT_END
}
const txt_cmd_s EcruteakMartSuperNerdText[] = {
    text_start("My EEVEE evolved"
        t_line "into an ESPEON."
        t_para "But my friend's"
        t_line "EEVEE turned into"
        t_cont "an UMBREON."
        t_para "I wonder why? We"
        t_line "both were raising"
        t_para "our EEVEE in the"
        t_line "same way…"
        t_done )
};
const txt_cmd_s EcruteakMartGrannyText[] = {
    text_start("If you use REVIVE,"
        t_line "a #MON that's"
        t_para "fainted will wake"
        t_line "right up."
        t_done )
    //db(0, 0) // filler
};
