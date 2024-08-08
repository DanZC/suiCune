#include "../constants.h"
#include "../util/scripting.h"
#include "Route10South.h"
//// EVENTS
enum {
    ROUTE10SOUTH_POKEFAN_M1 = 2,
    ROUTE10SOUTH_POKEFAN_M2,
};

const Script_fn_t Route10South_SceneScripts[] = {
    0,
};

const struct MapCallback Route10South_MapCallbacks[] = {
    0,
};

const struct MapScripts Route10South_MapScripts = {
    .scene_script_count = 0, // lengthof(Route10South_SceneScripts),
    .scene_scripts = Route10South_SceneScripts,

    .callback_count = 0, // lengthof(Route10South_MapCallbacks),
    .callbacks = Route10South_MapCallbacks,
};

static const struct CoordEvent Route10South_CoordEvents[] = {
    0,
};

static const struct BGEvent Route10South_BGEvents[] = {
    bg_event(5, 3, BGEVENT_READ, &Route10Sign),
};

static const struct WarpEventData Route10South_WarpEvents[] = {
    warp_event(6, 1, ROCK_TUNNEL_1F, 2),
};

static const struct ObjEvent Route10South_ObjectEvents[] = {
    object_event(17, 3, SPRITE_POKEFAN_M, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, -1, PAL_NPC_BROWN, OBJECTTYPE_TRAINER, 3, &TrainerHikerJim, -1),
    object_event(8, 10, SPRITE_POKEFAN_M, SPRITEMOVEDATA_SPINRANDOM_FAST, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_TRAINER, 3, &TrainerPokefanmRobert, -1),
};

const struct MapEvents Route10South_MapEvents = {
    .warp_event_count = lengthof(Route10South_WarpEvents),
    .warp_events = Route10South_WarpEvents,

    .coord_event_count = 0, // lengthof(Route10South_CoordEvents),
    .coord_events = Route10South_CoordEvents,

    .bg_event_count = lengthof(Route10South_BGEvents),
    .bg_events = Route10South_BGEvents,

    .obj_event_count = lengthof(Route10South_ObjectEvents),
    .obj_events = Route10South_ObjectEvents,
};

//// CODE

const struct TrainerObj TrainerHikerJim = {HIKER, JIM, EVENT_BEAT_HIKER_JIM, HikerJimSeenText, HikerJimBeatenText, 0, TrainerHikerJim_Script};
bool TrainerHikerJim_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(HikerJimAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerPokefanmRobert = {POKEFANM, ROBERT, EVENT_BEAT_POKEFANM_ROBERT, PokefanmRobertSeenText, PokefanmRobertBeatenText, 0, TrainerPokefanmRobert_Script};
bool TrainerPokefanmRobert_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(PokefanmRobertAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool Route10Sign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(Route10SignText)
    SCRIPT_END
}
const txt_cmd_s HikerJimSeenText[] = {
    text_start("Hahahah!"
        t_done )
};
const txt_cmd_s HikerJimBeatenText[] = {
    text_start("Hahaha-hachoo!"
        t_done )
};
const txt_cmd_s HikerJimAfterBattleText[] = {
    text_start("Hay fever is"
        t_line "making me sneeze!"
        t_cont "Ahahah-CHOO!"
        t_done )
};
const txt_cmd_s PokefanmRobertSeenText[] = {
    text_start("You like #MON,"
        t_line "don't you?"
        t_para "Me too!"
        t_done )
};
const txt_cmd_s PokefanmRobertBeatenText[] = {
    text_start("I'd have to say"
        t_line "that's my loss."
        t_done )
};
const txt_cmd_s PokefanmRobertAfterBattleText[] = {
    text_start("Look what you did"
        t_line "to my #MON…"
        t_para "I won't forget"
        t_line "this…"
        t_done )
};
const txt_cmd_s Route10SignText[] = {
    text_start("ROUTE 10"
        t_para "CERULEAN CITY -"
        t_line "LAVENDER TOWN"
        t_done )
    //db(0, 0) // filler
};
