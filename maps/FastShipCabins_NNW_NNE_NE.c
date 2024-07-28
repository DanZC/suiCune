#include "../constants.h"
#include "../util/scripting.h"
#include "FastShipCabins_NNW_NNE_NE.h"
//// EVENTS
enum {
    FASTSHIPCABINS_NNW_NNE_NE_COOLTRAINER_M = 2,
    FASTSHIPCABINS_NNW_NNE_NE_COOLTRAINER_F,
    FASTSHIPCABINS_NNW_NNE_NE_SUPER_NERD,
    FASTSHIPCABINS_NNW_NNE_NE_POKEFAN_M,
    FASTSHIPCABINS_NNW_NNE_NE_SAILOR,
    FASTSHIPCABINS_NNW_NNE_NE_GENTLEMAN,
    FASTSHIPCABINS_NNW_NNE_NE_PHARMACIST,
};

const Script_fn_t FastShipCabins_NNW_NNE_NE_SceneScripts[] = {
    0,
};

const struct MapCallback FastShipCabins_NNW_NNE_NE_MapCallbacks[] = {
    0,
};

const struct MapScripts FastShipCabins_NNW_NNE_NE_MapScripts = {
    .scene_script_count = 0, // lengthof(FastShipCabins_NNW_NNE_NE_SceneScripts),
    .scene_scripts = FastShipCabins_NNW_NNE_NE_SceneScripts,

    .callback_count = 0, // lengthof(FastShipCabins_NNW_NNE_NE_MapCallbacks),
    .callbacks = FastShipCabins_NNW_NNE_NE_MapCallbacks,
};

static const struct CoordEvent FastShipCabins_NNW_NNE_NE_CoordEvents[] = {
    0,
};

static const struct BGEvent FastShipCabins_NNW_NNE_NE_BGEvents[] = {
    bg_event(6, 13, BGEVENT_READ, &FastShipCabins_NNW_NNE_NETrashcan),
    bg_event(7, 19, BGEVENT_READ, &FastShipCabins_NNW_NNE_NETrashcan),
    bg_event(7, 31, BGEVENT_READ, &FastShipCabins_NNW_NNE_NETrashcan),
};

static const struct WarpEventData FastShipCabins_NNW_NNE_NE_WarpEvents[] = {
    warp_event(2, 0, FAST_SHIP_1F, 2),
    warp_event(2, 12, FAST_SHIP_1F, 3),
    warp_event(2, 24, FAST_SHIP_1F, 4),
};

static const struct ObjEvent FastShipCabins_NNW_NNE_NE_ObjectEvents[] = {
    object_event(4, 3, SPRITE_COOLTRAINER_M, SPRITEMOVEDATA_SPINRANDOM_FAST, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_TRAINER, 2, &TrainerCooltrainermSean, EVENT_FAST_SHIP_PASSENGERS_EASTBOUND),
    object_event(1, 5, SPRITE_COOLTRAINER_F, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_TRAINER, 3, &TrainerCooltrainerfCarol, EVENT_FAST_SHIP_PASSENGERS_EASTBOUND),
    object_event(1, 5, SPRITE_SUPER_NERD, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_TRAINER, 3, &TrainerPokemaniacEthan, EVENT_FAST_SHIP_PASSENGERS_WESTBOUND),
    object_event(4, 17, SPRITE_POKEFAN_M, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, PAL_NPC_BROWN, OBJECTTYPE_TRAINER, 3, &TrainerHikerNoland, EVENT_FAST_SHIP_PASSENGERS_FIRST_TRIP),
    object_event(4, 26, SPRITE_SAILOR, SPRITEMOVEDATA_SPINRANDOM_SLOW, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &FastShipLazySailorScript, EVENT_FAST_SHIP_CABINS_NNW_NNE_NE_SAILOR),
    object_event(7, 30, SPRITE_GENTLEMAN, SPRITEMOVEDATA_SPINRANDOM_SLOW, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_TRAINER, 1, &TrainerGentlemanEdward, EVENT_FAST_SHIP_PASSENGERS_EASTBOUND),
    object_event(2, 30, SPRITE_PHARMACIST, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_TRAINER, 4, &TrainerBurglarCorey, EVENT_FAST_SHIP_PASSENGERS_WESTBOUND),
};

const struct MapEvents FastShipCabins_NNW_NNE_NE_MapEvents = {
    .warp_event_count = lengthof(FastShipCabins_NNW_NNE_NE_WarpEvents),
    .warp_events = FastShipCabins_NNW_NNE_NE_WarpEvents,

    .coord_event_count = 0, // lengthof(FastShipCabins_NNW_NNE_NE_CoordEvents),
    .coord_events = FastShipCabins_NNW_NNE_NE_CoordEvents,

    .bg_event_count = lengthof(FastShipCabins_NNW_NNE_NE_BGEvents),
    .bg_events = FastShipCabins_NNW_NNE_NE_BGEvents,

    .obj_event_count = lengthof(FastShipCabins_NNW_NNE_NE_ObjectEvents),
    .obj_events = FastShipCabins_NNW_NNE_NE_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "FastShipCabins_NNW_NNE_NE.h"

const struct TrainerObj TrainerCooltrainermSean = {COOLTRAINERM, SEAN, EVENT_BEAT_COOLTRAINERM_SEAN, CooltrainermSeanSeenText, CooltrainermSeanBeatenText, 0, TrainerCooltrainermSean_Script};
bool TrainerCooltrainermSean_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(CooltrainermSeanAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerCooltrainerfCarol = {COOLTRAINERF, CAROL, EVENT_BEAT_COOLTRAINERF_CAROL, CooltrainerfCarolSeenText, CooltrainerfCarolBeatenText, 0, TrainerCooltrainerfCarol_Script};
bool TrainerCooltrainerfCarol_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(CooltrainerfCarolAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerPokemaniacEthan = {POKEMANIAC, ETHAN, EVENT_BEAT_POKEMANIAC_ETHAN, PokemaniacEthanSeenText, PokemaniacEthanBeatenText, 0, TrainerPokemaniacEthan_Script};
bool TrainerPokemaniacEthan_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(PokemaniacEthanAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerHikerNoland = {HIKER, NOLAND, EVENT_BEAT_HIKER_NOLAND, HikerNolandSeenText, HikerNolandBeatenText, 0, TrainerHikerNoland_Script};
bool TrainerHikerNoland_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(HikerNolandAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerGentlemanEdward = {GENTLEMAN, EDWARD, EVENT_BEAT_GENTLEMAN_EDWARD, GentlemanEdwardSeenText, GentlemanEdwardBeatenText, 0, TrainerGentlemanEdward_Script};
bool TrainerGentlemanEdward_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(GentlemanEdwardAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerBurglarCorey = {BURGLAR, COREY, EVENT_BEAT_BURGLAR_COREY, BurglarCoreySeenText, BurglarCoreyBeatenText, 0, TrainerBurglarCorey_Script};
bool TrainerBurglarCorey_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(BurglarCoreyAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool FastShipLazySailorScript(script_s* s) {
    SCRIPT_BEGIN
    playmusic(MUSIC_HIKER_ENCOUNTER)
    faceplayer
    opentext
    writetext(SailorStanlySeenText)
    waitbutton
    closetext
    winlosstext(SailorStanlyBeatenText, 0)
    loadtrainer(SAILOR, STANLY)
    startbattle
    reloadmap
    special(HealParty)
    setevent(EVENT_BEAT_SAILOR_STANLY)
    opentext
    writetext(SailorStanlyAfterBattleText)
    waitbutton
    closetext
    setevent(EVENT_FAST_SHIP_LAZY_SAILOR)
    setmapscene(FAST_SHIP_B1F, SCENE_FINISHED)
    readvar(VAR_FACING)
    ifequal(RIGHT, Movement2)
    applymovement(FASTSHIPCABINS_NNW_NNE_NE_SAILOR, FastShipLazySailorLeavesMovement1)
    playsound(SFX_EXIT_BUILDING)
    disappear(FASTSHIPCABINS_NNW_NNE_NE_SAILOR)
    waitsfx
    s_end
Movement2:
    applymovement(FASTSHIPCABINS_NNW_NNE_NE_SAILOR, FastShipLazySailorLeavesMovement2)
    playsound(SFX_EXIT_BUILDING)
    disappear(FASTSHIPCABINS_NNW_NNE_NE_SAILOR)
    waitsfx
    s_end
    SCRIPT_END
}
bool FastShipCabins_NNW_NNE_NETrashcan(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(TrashCanScript)
    SCRIPT_END
}
const uint8_t FastShipLazySailorLeavesMovement1[] = {
    step(LEFT),
    step(LEFT),
    step(UP),
    step(UP),
    movement_step_end,
};
const uint8_t FastShipLazySailorLeavesMovement2[] = {
    step(DOWN),
    step(LEFT),
    step(LEFT),
    step(UP),
    step(UP),
    step(UP),
    movement_step_end,
};
const txt_cmd_s CooltrainermSeanSeenText[] = {
    text_start("I'm going to KANTO"
        t_line "to test my skills."
        t_done )
};
const txt_cmd_s CooltrainermSeanBeatenText[] = {
    text_start("I wanted to win!"
        t_done )
};
const txt_cmd_s CooltrainermSeanAfterBattleText[] = {
    text_start("Trainers from"
        t_line "JOHTO can battle"
        t_para "with KANTO GYM"
        t_line "LEADERS."
        t_done )
};
const txt_cmd_s CooltrainerfCarolSeenText[] = {
    text_start("I'm training to"
        t_line "become the CHAMP!"
        t_done )
};
const txt_cmd_s CooltrainerfCarolBeatenText[] = {
    text_start("What's so differ-"
        t_line "ent between us?"
        t_done )
};
const txt_cmd_s CooltrainerfCarolAfterBattleText[] = {
    text_start("I'm going to beat"
        t_line "you someday!"
        t_done )
};
const txt_cmd_s PokemaniacEthanSeenText[] = {
    text_start("Do you know LILY?"
        t_line "She's a hot DJ in"
        t_cont "KANTO."
        t_done )
};
const txt_cmd_s PokemaniacEthanBeatenText[] = {
    text_start("Gyaaaah!"
        t_done )
};
const txt_cmd_s PokemaniacEthanAfterBattleText[] = {
    text_start("LILY's nice, but"
        t_line "MARY's the best!"
        t_para "I want to check"
        t_line "out JOHTO's radio"
        t_cont "programs!"
        t_done )
};
const txt_cmd_s HikerNolandSeenText[] = {
    text_start("Are you alone?"
        t_line "Then let's battle!"
        t_done )
};
const txt_cmd_s HikerNolandBeatenText[] = {
    text_start("That's too much to"
        t_line "handle!"
        t_done )
};
const txt_cmd_s HikerNolandAfterBattleText[] = {
    text_start("I wonder if there"
        t_line "are any mountains"
        t_para "worth climbing in"
        t_line "KANTO?"
        t_done )
};
const txt_cmd_s SailorStanlySeenText[] = {
    text_start("Yeah, I'm a sail-"
        t_line "or, all right."
        t_para "I wasn't goofing"
        t_line "off!"
        t_para "This cabin was"
        t_line "vacant, so I just"
        t_cont "took a quick nap!"
        t_para "Ah, forget it!"
        t_line "Let's battle!"
        t_done )
};
const txt_cmd_s SailorStanlyBeatenText[] = {
    text_start("Sorry! It's all my"
        t_line "fault!"
        t_done )
};
const txt_cmd_s SailorStanlyAfterBattleText[] = {
    text_start("Being a sailor, I"
        t_line "have to do phys-"
        t_cont "ical labor. It's"
        t_cont "exhausting!"
        t_done )
};
const txt_cmd_s GentlemanEdwardSeenText[] = {
    text_start("Oh, no. I've lost"
        t_line "something that's"
        t_cont "very important."
        t_done )
};
const txt_cmd_s GentlemanEdwardBeatenText[] = {
    text_start("I… I can't find"
        t_line "it…"
        t_done )
};
const txt_cmd_s GentlemanEdwardAfterBattleText[] = {
    text_start("I give up."
        t_line "You don't have to"
        t_para "look. Just forget"
        t_line "about it!"
        t_done )
};
const txt_cmd_s BurglarCoreySeenText[] = {
    text_start("Yeehaw!"
        t_line "Lucky!"
        t_done )
};
const txt_cmd_s BurglarCoreyBeatenText[] = {
    text_start("How unlucky!"
        t_line "I lost!"
        t_done )
};
const txt_cmd_s BurglarCoreyAfterBattleText[] = {
    text_start("I found a pretty"
        t_line "coin here."
        t_para "Someone must have"
        t_line "lost it…"
        t_done )
    //db(0, 0) // filler
};
