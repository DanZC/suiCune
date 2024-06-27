#include "../constants.h"
#include "../util/scripting.h"
#include "BlackthornMart.h"
//// EVENTS
enum {
    BLACKTHORNMART_CLERK = 2,
    BLACKTHORNMART_COOLTRAINER_M,
    BLACKTHORNMART_BLACK_BELT,
};

const Script_fn_t BlackthornMart_SceneScripts[] = {
    0,
};

const struct MapCallback BlackthornMart_MapCallbacks[] = {
    0,
};

const struct MapScripts BlackthornMart_MapScripts = {
    .scene_script_count = 0, // lengthof(BlackthornMart_SceneScripts),
    .scene_scripts = BlackthornMart_SceneScripts,

    .callback_count = 0, // lengthof(BlackthornMart_MapCallbacks),
    .callbacks = BlackthornMart_MapCallbacks,
};

static const struct CoordEvent BlackthornMart_CoordEvents[] = {
    0,
};

static const struct BGEvent BlackthornMart_BGEvents[] = {
    0,
};

static const struct WarpEventData BlackthornMart_WarpEvents[] = {
    warp_event(2, 7, BLACKTHORN_CITY, 4),
    warp_event(3, 7, BLACKTHORN_CITY, 4),
};

static const struct ObjEvent BlackthornMart_ObjectEvents[] = {
    object_event(1, 3, SPRITE_CLERK, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &BlackthornMartClerkScript, -1),
    object_event(7, 6, SPRITE_COOLTRAINER_M, SPRITEMOVEDATA_WALK_LEFT_RIGHT, 2, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &BlackthornMartCooltrainerMScript, -1),
    object_event(5, 2, SPRITE_BLACK_BELT, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &BlackthornMartBlackBeltScript, -1),
};

const struct MapEvents BlackthornMart_MapEvents = {
    .warp_event_count = lengthof(BlackthornMart_WarpEvents),
    .warp_events = BlackthornMart_WarpEvents,

    .coord_event_count = 0, // lengthof(BlackthornMart_CoordEvents),
    .coord_events = BlackthornMart_CoordEvents,

    .bg_event_count = 0, // lengthof(BlackthornMart_BGEvents),
    .bg_events = BlackthornMart_BGEvents,

    .obj_event_count = lengthof(BlackthornMart_ObjectEvents),
    .obj_events = BlackthornMart_ObjectEvents,
};

//// CODE

bool BlackthornMartClerkScript(script_s* s) {
    SCRIPT_BEGIN
    opentext
    pokemart(MARTTYPE_STANDARD, MART_BLACKTHORN)
    closetext
    s_end
    SCRIPT_END
}
bool BlackthornMartCooltrainerMScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(BlackthornMartCooltrainerMText)
    SCRIPT_END
}
bool BlackthornMartBlackBeltScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(BlackthornMartBlackBeltText)
    SCRIPT_END
}
const txt_cmd_s BlackthornMartCooltrainerMText[] = {
    text_start("You can't buy MAX"
        t_line "REVIVE, but it"
        t_para "fully restores a"
        t_line "fainted #MON."
        t_para "Beware--it won't"
        t_line "restore PP, the"
        t_para "POWER POINTS"
        t_line "needed for moves."
        t_done )
};
const txt_cmd_s BlackthornMartBlackBeltText[] = {
    text_start("MAX REPEL keeps"
        t_line "weak #MON away"
        t_cont "from you."
        t_para "It's the longest"
        t_line "lasting of the"
        t_cont "REPEL sprays."
        t_done )
    //db(0, 0) // filler
};
