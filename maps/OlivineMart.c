#include "../constants.h"
#include "../util/scripting.h"
#include "OlivineMart.h"
//// EVENTS
enum {
    OLIVINEMART_CLERK = 2,
    OLIVINEMART_COOLTRAINER_F,
    OLIVINEMART_LASS,
};

const Script_fn_t OlivineMart_SceneScripts[] = {
    0,
};

const struct MapCallback OlivineMart_MapCallbacks[] = {
    0,
};

const struct MapScripts OlivineMart_MapScripts = {
    .scene_script_count = 0, // lengthof(OlivineMart_SceneScripts),
    .scene_scripts = OlivineMart_SceneScripts,

    .callback_count = 0, // lengthof(OlivineMart_MapCallbacks),
    .callbacks = OlivineMart_MapCallbacks,
};

static const struct CoordEvent OlivineMart_CoordEvents[] = {
    0,
};

static const struct BGEvent OlivineMart_BGEvents[] = {
    0,
};

static const struct WarpEventData OlivineMart_WarpEvents[] = {
    warp_event(2, 7, OLIVINE_CITY, 8),
    warp_event(3, 7, OLIVINE_CITY, 8),
};

static const struct ObjEvent OlivineMart_ObjectEvents[] = {
    object_event(1, 3, SPRITE_CLERK, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &OlivineMartClerkScript, -1),
    object_event(6, 2, SPRITE_COOLTRAINER_F, SPRITEMOVEDATA_WALK_LEFT_RIGHT, 2, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &OlivineMartCooltrainerFScript, -1),
    object_event(1, 6, SPRITE_LASS, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &OlivineMartLassScript, -1),
};

const struct MapEvents OlivineMart_MapEvents = {
    .warp_event_count = lengthof(OlivineMart_WarpEvents),
    .warp_events = OlivineMart_WarpEvents,

    .coord_event_count = 0, // lengthof(OlivineMart_CoordEvents),
    .coord_events = OlivineMart_CoordEvents,

    .bg_event_count = 0, // lengthof(OlivineMart_BGEvents),
    .bg_events = OlivineMart_BGEvents,

    .obj_event_count = lengthof(OlivineMart_ObjectEvents),
    .obj_events = OlivineMart_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "OlivineMart.h"

bool OlivineMartClerkScript(script_s* s) {
    SCRIPT_BEGIN
    opentext
    pokemart(MARTTYPE_STANDARD, MART_OLIVINE)
    closetext
    s_end
    SCRIPT_END
}
bool OlivineMartCooltrainerFScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(OlivineMartCooltrainerFText)
    SCRIPT_END
}
bool OlivineMartLassScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(OlivineMartLassText)
    SCRIPT_END
}
const txt_cmd_s OlivineMartCooltrainerFText[] = {
    text_start("Do your #MON"
        t_line "already know the"
        t_para "move for carrying"
        t_line "people on water?"
        t_done )
};
const txt_cmd_s OlivineMartLassText[] = {
    text_start("My BUTTERFREE came"
        t_line "from my boyfriend"
        t_cont "overseas."
        t_para "It carried some"
        t_line "MAIL from him."
        t_para "Want to know what"
        t_line "it says?"
        t_para "Let's see… Nope!"
        t_line "It's a secret!"
        t_done )
    //db(0, 0) // filler
};
