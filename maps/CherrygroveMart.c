#include "../constants.h"
#include "../util/scripting.h"
#include "CherrygroveMart.h"
//// EVENTS
enum {
    CHERRYGROVEMART_CLERK = 2,
    CHERRYGROVEMART_COOLTRAINER_M,
    CHERRYGROVEMART_YOUNGSTER,
};

const Script_fn_t CherrygroveMart_SceneScripts[] = {
};

const struct MapCallback CherrygroveMart_MapCallbacks[] = {
};

const struct MapScripts CherrygroveMart_MapScripts = {
    .scene_script_count = lengthof(CherrygroveMart_SceneScripts),
    .scene_scripts = CherrygroveMart_SceneScripts,

    .callback_count = lengthof(CherrygroveMart_MapCallbacks),
    .callbacks = CherrygroveMart_MapCallbacks,
};

static const struct CoordEvent CherrygroveMart_CoordEvents[] = {
};

static const struct BGEvent CherrygroveMart_BGEvents[] = {
};

static const struct WarpEventData CherrygroveMart_WarpEvents[] = {
    warp_event(2, 7, CHERRYGROVE_CITY, 1),
    warp_event(3, 7, CHERRYGROVE_CITY, 1),
};

static const struct ObjEvent CherrygroveMart_ObjectEvents[] = {
    object_event(1, 3, SPRITE_CLERK, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &CherrygroveMartClerkScript, -1),
    object_event(7, 6, SPRITE_COOLTRAINER_M, SPRITEMOVEDATA_WALK_LEFT_RIGHT, 2, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &CherrygroveMartCooltrainerMScript, -1),
    object_event(2, 5, SPRITE_YOUNGSTER, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &CherrygroveMartYoungsterScript, -1),
};

const struct MapEvents CherrygroveMart_MapEvents = {
    .warp_event_count = lengthof(CherrygroveMart_WarpEvents),
    .warp_events = CherrygroveMart_WarpEvents,

    .coord_event_count = lengthof(CherrygroveMart_CoordEvents),
    .coord_events = CherrygroveMart_CoordEvents,

    .bg_event_count = lengthof(CherrygroveMart_BGEvents),
    .bg_events = CherrygroveMart_BGEvents,

    .obj_event_count = lengthof(CherrygroveMart_ObjectEvents),
    .obj_events = CherrygroveMart_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "CherrygroveMart.h"

bool CherrygroveMartClerkScript(script_s* s) {
    SCRIPT_BEGIN
    opentext
    checkevent(EVENT_GAVE_MYSTERY_EGG_TO_ELM)
    iftrue(PokeBallsInStock)
    pokemart(MARTTYPE_STANDARD, MART_CHERRYGROVE)
    closetext
    s_end
PokeBallsInStock:
    pokemart(MARTTYPE_STANDARD, MART_CHERRYGROVE_DEX)
    closetext
    s_end
    SCRIPT_END
}
bool CherrygroveMartCooltrainerMScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_GAVE_MYSTERY_EGG_TO_ELM)
    iftrue(PokeBallsInStock)
    writetext(CherrygroveMartCooltrainerMText)
    waitbutton
    closetext
    s_end
PokeBallsInStock:
    writetext(CherrygroveMartCooltrainerMText_PokeBallsInStock)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool CherrygroveMartYoungsterScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(CherrygroveMartYoungsterText)
    SCRIPT_END
}
const txt_cmd_s CherrygroveMartCooltrainerMText[] = {
    text_start("They're fresh out"
        t_line "of # BALLS!"
        t_para "When will they get"
        t_line "more of them?"
        t_done )
};
const txt_cmd_s CherrygroveMartCooltrainerMText_PokeBallsInStock[] = {
    text_start("# BALLS are in"
        t_line "stock! Now I can"
        t_cont "catch #MON!"
        t_done )
};
const txt_cmd_s CherrygroveMartYoungsterText[] = {
    text_start("When I was walking"
        t_line "in the grass, a"
        t_para "bug #MON poi-"
        t_line "soned my #MON!"
        t_para "I just kept going,"
        t_line "but then my"
        t_cont "#MON fainted."
        t_para "You should keep an"
        t_line "ANTIDOTE with you."
        t_done )
    //db(0, 0) // filler
};
