#include "../constants.h"
#include "../util/scripting.h"
#include "AzaleaMart.h"
//// EVENTS
enum {
    AZALEAMART_CLERK = 2,
    AZALEAMART_COOLTRAINER_M,
    AZALEAMART_BUG_CATCHER,
};

const Script_fn_t AzaleaMart_SceneScripts[] = {
    0,
};

const struct MapCallback AzaleaMart_MapCallbacks[] = {
    0,
};

const struct MapScripts AzaleaMart_MapScripts = {
    .scene_script_count = 0, // lengthof(AzaleaMart_SceneScripts),
    .scene_scripts = AzaleaMart_SceneScripts,

    .callback_count = 0, // lengthof(AzaleaMart_MapCallbacks),
    .callbacks = AzaleaMart_MapCallbacks,
};

static const struct CoordEvent AzaleaMart_CoordEvents[] = {
    0,
};

static const struct BGEvent AzaleaMart_BGEvents[] = {
    0,
};

static const struct WarpEventData AzaleaMart_WarpEvents[] = {
    warp_event(2, 7, AZALEA_TOWN, 3),
    warp_event(3, 7, AZALEA_TOWN, 3),
};

static const struct ObjEvent AzaleaMart_ObjectEvents[] = {
    object_event(1, 3, SPRITE_CLERK, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &AzaleaMartClerkScript, -1),
    object_event(2, 5, SPRITE_COOLTRAINER_M, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &AzaleaMartCooltrainerMScript, -1),
    object_event(7, 2, SPRITE_BUG_CATCHER, SPRITEMOVEDATA_WALK_LEFT_RIGHT, 2, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &AzaleaMartBugCatcherScript, -1),
};

const struct MapEvents AzaleaMart_MapEvents = {
    .warp_event_count = lengthof(AzaleaMart_WarpEvents),
    .warp_events = AzaleaMart_WarpEvents,

    .coord_event_count = 0, // lengthof(AzaleaMart_CoordEvents),
    .coord_events = AzaleaMart_CoordEvents,

    .bg_event_count = 0, // lengthof(AzaleaMart_BGEvents),
    .bg_events = AzaleaMart_BGEvents,

    .obj_event_count = lengthof(AzaleaMart_ObjectEvents),
    .obj_events = AzaleaMart_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "AzaleaMart.h"

bool AzaleaMartClerkScript(script_s* s) {
    SCRIPT_BEGIN
    opentext
    pokemart(MARTTYPE_STANDARD, MART_AZALEA)
    closetext
    s_end
    SCRIPT_END
}
bool AzaleaMartCooltrainerMScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(AzaleaMartCooltrainerMText)
    SCRIPT_END
}
bool AzaleaMartBugCatcherScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(AzaleaMartBugCatcherText)
    SCRIPT_END
}
const txt_cmd_s AzaleaMartCooltrainerMText[] = {
    text_start("There's no GREAT"
        t_line "BALL here. #"
        t_para "BALLS will have"
        t_line "to do."
        t_para "I wish KURT would"
        t_line "make me some of"
        t_cont "his custom BALLS."
        t_done )
};
const txt_cmd_s AzaleaMartBugCatcherText[] = {
    text_start("A GREAT BALL is"
        t_line "better for catch-"
        t_cont "ing #MON than a"
        t_cont "# BALL."
        t_para "But KURT's might"
        t_line "be better some-"
        t_cont "times."
        t_done )
    //db(0, 0) // filler
};
