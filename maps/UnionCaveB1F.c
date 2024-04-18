#include "../constants.h"
#include "../util/scripting.h"
#include "UnionCaveB1F.h"
//// EVENTS
enum {
    UNIONCAVEB1F_POKEFAN_M1 = 2,
    UNIONCAVEB1F_POKEFAN_M2,
    UNIONCAVEB1F_SUPER_NERD1,
    UNIONCAVEB1F_SUPER_NERD2,
    UNIONCAVEB1F_POKE_BALL1,
    UNIONCAVEB1F_BOULDER,
    UNIONCAVEB1F_POKE_BALL2,
};

const Script_fn_t UnionCaveB1F_SceneScripts[] = {
    0,
};

const struct MapCallback UnionCaveB1F_MapCallbacks[] = {
    0,
};

const struct MapScripts UnionCaveB1F_MapScripts = {
    .scene_script_count = 0, // lengthof(UnionCaveB1F_SceneScripts),
    .scene_scripts = UnionCaveB1F_SceneScripts,

    .callback_count = 0, // lengthof(UnionCaveB1F_MapCallbacks),
    .callbacks = UnionCaveB1F_MapCallbacks,
};

static const struct CoordEvent UnionCaveB1F_CoordEvents[] = {
    0,
};

static const struct BGEvent UnionCaveB1F_BGEvents[] = {
    0,
};

static const struct WarpEventData UnionCaveB1F_WarpEvents[] = {
    warp_event(3, 3, RUINS_OF_ALPH_OUTSIDE, 7),
    warp_event(3, 11, RUINS_OF_ALPH_OUTSIDE, 8),
    warp_event(7, 19, UNION_CAVE_1F, 1),
    warp_event(3, 33, UNION_CAVE_1F, 2),
    warp_event(17, 31, UNION_CAVE_B2F, 1),
};

static const struct ObjEvent UnionCaveB1F_ObjectEvents[] = {
    object_event(9, 4, SPRITE_POKEFAN_M, SPRITEMOVEDATA_SPINRANDOM_FAST, 0, 0, -1, -1, PAL_NPC_BROWN, OBJECTTYPE_TRAINER, 3, &TrainerHikerPhillip, -1),
    object_event(16, 7, SPRITE_POKEFAN_M, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_BROWN, OBJECTTYPE_TRAINER, 3, &TrainerHikerLeonard, -1),
    object_event(5, 32, SPRITE_SUPER_NERD, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_TRAINER, 3, &TrainerPokemaniacAndrew, -1),
    object_event(17, 30, SPRITE_SUPER_NERD, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_TRAINER, 3, &TrainerPokemaniacCalvin, -1),
    object_event(2, 16, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &UnionCaveB1FTMSwift, EVENT_UNION_CAVE_B1F_TM_SWIFT),
    object_event(7, 10, SPRITE_BOULDER, SPRITEMOVEDATA_STRENGTH_BOULDER, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &UnionCaveB1FBoulder, -1),
    object_event(17, 23, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &UnionCaveB1FXDefend, EVENT_UNION_CAVE_B1F_X_DEFEND),
};

const struct MapEvents UnionCaveB1F_MapEvents = {
    .warp_event_count = lengthof(UnionCaveB1F_WarpEvents),
    .warp_events = UnionCaveB1F_WarpEvents,

    .coord_event_count = 0, // lengthof(UnionCaveB1F_CoordEvents),
    .coord_events = UnionCaveB1F_CoordEvents,

    .bg_event_count = 0, // lengthof(UnionCaveB1F_BGEvents),
    .bg_events = UnionCaveB1F_BGEvents,

    .obj_event_count = lengthof(UnionCaveB1F_ObjectEvents),
    .obj_events = UnionCaveB1F_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "UnionCaveB1F.h"

const struct TrainerObj TrainerPokemaniacAndrew = {POKEMANIAC, ANDREW, EVENT_BEAT_POKEMANIAC_ANDREW, PokemaniacAndrewSeenText, PokemaniacAndrewBeatenText, 0, TrainerPokemaniacAndrew_Script};
bool TrainerPokemaniacAndrew_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(PokemaniacAndrewAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerPokemaniacCalvin = {POKEMANIAC, CALVIN, EVENT_BEAT_POKEMANIAC_CALVIN, PokemaniacCalvinSeenText, PokemaniacCalvinBeatenText, 0, TrainerPokemaniacCalvin_Script};
bool TrainerPokemaniacCalvin_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(PokemaniacCalvinAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerHikerPhillip = {HIKER, PHILLIP, EVENT_BEAT_HIKER_PHILLIP, HikerPhillipSeenText, HikerPhillipBeatenText, 0, TrainerHikerPhillip_Script};
bool TrainerHikerPhillip_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(HikerPhillipAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerHikerLeonard = {HIKER, LEONARD, EVENT_BEAT_HIKER_LEONARD, HikerLeonardSeenText, HikerLeonardBeatenText, 0, TrainerHikerLeonard_Script};
bool TrainerHikerLeonard_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(HikerLeonardAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct ItemBall UnionCaveB1FTMSwift = {TM_SWIFT, 1};
const struct ItemBall UnionCaveB1FXDefend = {X_DEFEND, 1};
bool UnionCaveB1FBoulder(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(StrengthBoulderScript)
    SCRIPT_END
}
const txt_cmd_s HikerPhillipSeenText[] = {
    text_start("It's been a while"
        t_line "since I last saw"
        t_cont "another person."
        t_para "Don't be shy."
        t_line "Let's battle!"
        t_done )
};
const txt_cmd_s HikerPhillipBeatenText[] = {
    text_start("Uurggh…"
        t_done )
};
const txt_cmd_s HikerPhillipAfterBattleText[] = {
    text_start("I've been lost for"
        t_line "a long time…"
        t_para "I don't mind it"
        t_line "here, but I am"
        t_cont "soooo hungry!"
        t_done )
};
const txt_cmd_s HikerLeonardSeenText[] = {
    text_start("What do you know!"
        t_line "A visitor!"
        t_done )
};
const txt_cmd_s HikerLeonardBeatenText[] = {
    text_start("Wahahah! You're a"
        t_line "feisty one!"
        t_done )
};
const txt_cmd_s HikerLeonardAfterBattleText[] = {
    text_start("I live down here."
        t_para "You can, too, if"
        t_line "you'd like."
        t_para "There's plenty of"
        t_line "room, you see."
        t_done )
};
const txt_cmd_s PokemaniacAndrewSeenText[] = {
    text_start("Who's there?"
        t_para "Leave me and my"
        t_line "#MON alone!"
        t_done )
};
const txt_cmd_s PokemaniacAndrewBeatenText[] = {
    text_start("Go…"
        t_line "Go away!"
        t_done )
};
const txt_cmd_s PokemaniacAndrewAfterBattleText[] = {
    text_start("Just me and my"
        t_line "#MON. I'm de-"
        t_cont "lirious with joy."
        t_done )
};
const txt_cmd_s PokemaniacCalvinSeenText[] = {
    text_start("I came all the way"
        t_line "here to conduct my"
        t_cont "#MON research."
        t_para "Let me demonstrate"
        t_line "my findings in a"
        t_cont "real battle!"
        t_done )
};
const txt_cmd_s PokemaniacCalvinBeatenText[] = {
    text_start("You demonstrated"
        t_line "on me!"
        t_done )
};
const txt_cmd_s PokemaniacCalvinAfterBattleText[] = {
    text_start("I should compile"
        t_line "and announce my"
        t_cont "study findings."
        t_para "I might even be-"
        t_line "come famous like"
        t_cont "PROF.ELM."
        t_done )
    //db(0, 0) // filler
};
