#include "../constants.h"
#include "../util/scripting.h"
#include "LavenderMart.h"
//// EVENTS
enum {
    LAVENDERMART_CLERK = 2,
    LAVENDERMART_POKEFAN_M,
    LAVENDERMART_ROCKER,
};

const Script_fn_t LavenderMart_SceneScripts[] = {
    0,
};

const struct MapCallback LavenderMart_MapCallbacks[] = {
    0,
};

const struct MapScripts LavenderMart_MapScripts = {
    .scene_script_count = 0, // lengthof(LavenderMart_SceneScripts),
    .scene_scripts = LavenderMart_SceneScripts,

    .callback_count = 0, // lengthof(LavenderMart_MapCallbacks),
    .callbacks = LavenderMart_MapCallbacks,
};

static const struct CoordEvent LavenderMart_CoordEvents[] = {
    0,
};

static const struct BGEvent LavenderMart_BGEvents[] = {
    0,
};

static const struct WarpEventData LavenderMart_WarpEvents[] = {
    warp_event(2, 7, LAVENDER_TOWN, 5),
    warp_event(3, 7, LAVENDER_TOWN, 5),
};

static const struct ObjEvent LavenderMart_ObjectEvents[] = {
    object_event(1, 3, SPRITE_CLERK, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &LavenderMartClerkScript, -1),
    object_event(6, 6, SPRITE_POKEFAN_M, SPRITEMOVEDATA_WALK_LEFT_RIGHT, 2, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &LavenderMartPokefanMScript, -1),
    object_event(9, 2, SPRITE_ROCKER, SPRITEMOVEDATA_SPINRANDOM_SLOW, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &LavenderMartRockerScript, -1),
};

const struct MapEvents LavenderMart_MapEvents = {
    .warp_event_count = lengthof(LavenderMart_WarpEvents),
    .warp_events = LavenderMart_WarpEvents,

    .coord_event_count = 0, // lengthof(LavenderMart_CoordEvents),
    .coord_events = LavenderMart_CoordEvents,

    .bg_event_count = 0, // lengthof(LavenderMart_BGEvents),
    .bg_events = LavenderMart_BGEvents,

    .obj_event_count = lengthof(LavenderMart_ObjectEvents),
    .obj_events = LavenderMart_ObjectEvents,
};

//// CODE

bool LavenderMartClerkScript(script_s* s) {
    SCRIPT_BEGIN
    opentext
    pokemart(MARTTYPE_STANDARD, MART_LAVENDER)
    closetext
    s_end
    SCRIPT_END
}
bool LavenderMartPokefanMScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(LavenderMartPokefanMText)
    SCRIPT_END
}
bool LavenderMartRockerScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(LavenderMartRockerText)
    SCRIPT_END
}
const txt_cmd_s LavenderMartPokefanMText[] = {
    text_start("REPEL is a neces-"
        t_line "sity if you are"
        t_para "going to explore a"
        t_line "cave."
        t_para "Even though I like"
        t_line "exploring, I still"
        t_para "haven't made it to"
        t_line "all the caves."
        t_done )
};
const txt_cmd_s LavenderMartRockerText[] = {
    text_start("I heard about a"
        t_line "craftsman who"
        t_para "makes custom BALLS"
        t_line "in the JOHTO town"
        t_para "of AZALEA. I wish"
        t_line "I had some."
        t_done )
    //db(0, 0) // filler
};
