#include "../constants.h"
#include "../util/scripting.h"
#include "Route6.h"
//// EVENTS
enum {
    ROUTE6_POKEFAN_M1 = 2,
    ROUTE6_POKEFAN_M2,
    ROUTE6_POKEFAN_M3,
};

const Script_fn_t Route6_SceneScripts[] = {
    0,
};

const struct MapCallback Route6_MapCallbacks[] = {
    0,
};

const struct MapScripts Route6_MapScripts = {
    .scene_script_count = 0, // lengthof(Route6_SceneScripts),
    .scene_scripts = Route6_SceneScripts,

    .callback_count = 0, // lengthof(Route6_MapCallbacks),
    .callbacks = Route6_MapCallbacks,
};

static const struct CoordEvent Route6_CoordEvents[] = {
    0,
};

static const struct BGEvent Route6_BGEvents[] = {
    bg_event(19, 5, BGEVENT_READ, &Route6UndergroundPathSign),
};

static const struct WarpEventData Route6_WarpEvents[] = {
    warp_event(17, 3, ROUTE_6_UNDERGROUND_PATH_ENTRANCE, 1),
    warp_event(6, 1, ROUTE_6_SAFFRON_GATE, 3),
};

static const struct ObjEvent Route6_ObjectEvents[] = {
    object_event(17, 4, SPRITE_POKEFAN_M, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_BROWN, OBJECTTYPE_SCRIPT, 2, &Route6PokefanMScript, EVENT_ROUTE_5_6_POKEFAN_M_BLOCKS_UNDERGROUND_PATH),
    object_event(9, 12, SPRITE_POKEFAN_M, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_TRAINER, 0, &TrainerPokefanmRex, -1),
    object_event(10, 12, SPRITE_POKEFAN_M, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_TRAINER, 0, &TrainerPokefanmAllan, -1),
};

const struct MapEvents Route6_MapEvents = {
    .warp_event_count = lengthof(Route6_WarpEvents),
    .warp_events = Route6_WarpEvents,

    .coord_event_count = 0, // lengthof(Route6_CoordEvents),
    .coord_events = Route6_CoordEvents,

    .bg_event_count = lengthof(Route6_BGEvents),
    .bg_events = Route6_BGEvents,

    .obj_event_count = lengthof(Route6_ObjectEvents),
    .obj_events = Route6_ObjectEvents,
};

//// CODE

const struct TrainerObj TrainerPokefanmRex = {POKEFANM, REX, EVENT_BEAT_POKEFANM_REX, PokefanmRexSeenText, PokefanmRexBeatenText, 0, TrainerPokefanmRex_Script};
bool TrainerPokefanmRex_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(PokefanmRexAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerPokefanmAllan = {POKEFANM, ALLAN, EVENT_BEAT_POKEFANM_ALLAN, PokefanmAllanSeenText, PokefanmAllanBeatenText, 0, TrainerPokefanmAllan_Script};
bool TrainerPokefanmAllan_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(PokefanmAllanAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool Route6PokefanMScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(Route6PokefanMText)
    SCRIPT_END
}
bool Route6UndergroundPathSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(Route6UndergroundPathSignText)
    SCRIPT_END
}
const txt_cmd_s Route6PokefanMText[] = {
    text_start("The road is closed"
        t_line "until the problem"
        t_para "at the POWER PLANT"
        t_line "is solved."
        t_done )
};
const txt_cmd_s Route6UndergroundPathSignText[] = {
    text_start("UNDERGROUND PATH"
        t_para "CERULEAN CITY -"
        t_line "VERMILION CITY"
        t_done )
};
const txt_cmd_s PokefanmRexSeenText[] = {
    text_start("My PHANPY is the"
        t_line "cutest in the"
        t_cont "world."
        t_done )
};
const txt_cmd_s PokefanmRexBeatenText[] = {
    text_start("My PHANPY!"
        t_done )
};
const txt_cmd_s PokefanmRexAfterBattleText[] = {
    text_start("Look how adorable"
        t_line "my PHANPY acts!"
        t_para "Isn't it cute"
        t_line "enough to make"
        t_cont "your heart melt?"
        t_done )
};
const txt_cmd_s PokefanmAllanSeenText[] = {
    text_start("My TEDDIURSA is"
        t_line "the cutest in the"
        t_cont "world."
        t_done )
};
const txt_cmd_s PokefanmAllanBeatenText[] = {
    text_start("My TEDDIURSA!"
        t_done )
};
const txt_cmd_s PokefanmAllanAfterBattleText[] = {
    text_start("Look how adorable"
        t_line "my TEDDIURSA acts!"
        t_para "Isn't it cute"
        t_line "enough to make"
        t_cont "your heart melt?"
        t_done )
    //db(0, 0) // filler
};
