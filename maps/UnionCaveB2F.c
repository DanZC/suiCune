#include "../constants.h"
#include "../util/scripting.h"
#include "UnionCaveB2F.h"
//// EVENTS
enum {
    UNIONCAVEB2F_ROCKER = 2,
    UNIONCAVEB2F_COOLTRAINER_F1,
    UNIONCAVEB2F_COOLTRAINER_F2,
    UNIONCAVEB2F_POKE_BALL1,
    UNIONCAVEB2F_POKE_BALL2,
    UNIONCAVEB2F_LAPRAS,
};

const Script_fn_t UnionCaveB2F_SceneScripts[] = {
    0,
};

const struct MapCallback UnionCaveB2F_MapCallbacks[] = {
    map_callback(MAPCALLBACK_OBJECTS, UnionCaveB2F_MapScripts_Lapras),
};

const struct MapScripts UnionCaveB2F_MapScripts = {
    .scene_script_count = 0, // lengthof(UnionCaveB2F_SceneScripts),
    .scene_scripts = UnionCaveB2F_SceneScripts,

    .callback_count = lengthof(UnionCaveB2F_MapCallbacks),
    .callbacks = UnionCaveB2F_MapCallbacks,
};

static const struct CoordEvent UnionCaveB2F_CoordEvents[] = {
    0,
};

static const struct BGEvent UnionCaveB2F_BGEvents[] = {
    0,
};

static const struct WarpEventData UnionCaveB2F_WarpEvents[] = {
    warp_event(5, 3, UNION_CAVE_B1F, 5),
};

static const struct ObjEvent UnionCaveB2F_ObjectEvents[] = {
    object_event(15, 19, SPRITE_ROCKER, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_TRAINER, 3, &TrainerCooltrainermNick, -1),
    object_event(5, 13, SPRITE_COOLTRAINER_F, SPRITEMOVEDATA_SPINRANDOM_FAST, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_TRAINER, 1, &TrainerCooltrainerfGwen, -1),
    object_event(3, 30, SPRITE_COOLTRAINER_F, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_TRAINER, 3, &TrainerCooltrainerfEmma, -1),
    object_event(16, 2, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &UnionCaveB2FElixer, EVENT_UNION_CAVE_B2F_ELIXER),
    object_event(12, 19, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &UnionCaveB2FHyperPotion, EVENT_UNION_CAVE_B2F_HYPER_POTION),
    object_event(11, 31, SPRITE_SURF, SPRITEMOVEDATA_SWIM_WANDER, 1, 1, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &UnionCaveLapras, EVENT_UNION_CAVE_B2F_LAPRAS),
};

const struct MapEvents UnionCaveB2F_MapEvents = {
    .warp_event_count = lengthof(UnionCaveB2F_WarpEvents),
    .warp_events = UnionCaveB2F_WarpEvents,

    .coord_event_count = 0, // lengthof(UnionCaveB2F_CoordEvents),
    .coord_events = UnionCaveB2F_CoordEvents,

    .bg_event_count = 0, // lengthof(UnionCaveB2F_BGEvents),
    .bg_events = UnionCaveB2F_BGEvents,

    .obj_event_count = lengthof(UnionCaveB2F_ObjectEvents),
    .obj_events = UnionCaveB2F_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "UnionCaveB2F.h"

bool UnionCaveB2F_MapScripts_Lapras(script_s* s) {
    SCRIPT_BEGIN
    checkflag(ENGINE_UNION_CAVE_LAPRAS)
    iftrue_jump(UnionCaveB2F_MapScripts_NoAppear)
    readvar(VAR_WEEKDAY)
    ifequal_jump(FRIDAY, UnionCaveB2F_MapScripts_Appear)
    SCRIPT_FALLTHROUGH(UnionCaveB2F_MapScripts_NoAppear)
}
bool UnionCaveB2F_MapScripts_NoAppear(script_s* s) {
    SCRIPT_BEGIN
    disappear(UNIONCAVEB2F_LAPRAS)
    s_endcallback
    SCRIPT_END
}
bool UnionCaveB2F_MapScripts_Appear(script_s* s) {
    SCRIPT_BEGIN
    appear(UNIONCAVEB2F_LAPRAS)
    s_endcallback
    SCRIPT_END
}
bool UnionCaveLapras(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    playcry(LAPRAS)
    loadwildmon(LAPRAS, 20)
    startbattle
    disappear(UNIONCAVEB2F_LAPRAS)
    setflag(ENGINE_UNION_CAVE_LAPRAS)
    reloadmapafterbattle
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerCooltrainermNick = {COOLTRAINERM, NICK, EVENT_BEAT_COOLTRAINERM_NICK, CooltrainermNickSeenText, CooltrainermNickBeatenText, 0, TrainerCooltrainermNick_Script};
bool TrainerCooltrainermNick_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(CooltrainermNickAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerCooltrainerfGwen = {COOLTRAINERF, GWEN, EVENT_BEAT_COOLTRAINERF_GWEN, CooltrainerfGwenSeenText, CooltrainerfGwenBeatenText, 0, TrainerCooltrainerfGwen_Script};
bool TrainerCooltrainerfGwen_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(CooltrainerfGwenAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerCooltrainerfEmma = {COOLTRAINERF, EMMA, EVENT_BEAT_COOLTRAINERF_EMMA, CooltrainerfEmmaSeenText, CooltrainerfEmmaBeatenText, 0, TrainerCooltrainerfEmma_Script};
bool TrainerCooltrainerfEmma_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(CooltrainerfEmmaAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct ItemBall UnionCaveB2FElixer = {ELIXER, 1};
const struct ItemBall UnionCaveB2FHyperPotion = {HYPER_POTION, 1};
const txt_cmd_s CooltrainermNickSeenText[] = {
    text_start("There are two"
        t_line "kinds of people."
        t_para "Those who have"
        t_line "style, and those"
        t_cont "who don't."
        t_para "What kind of"
        t_line "person are you?"
        t_done )
};
const txt_cmd_s CooltrainermNickBeatenText[] = {
    text_start("You've got"
        t_line "dazzling style!"
        t_done )
};
const txt_cmd_s CooltrainermNickAfterBattleText[] = {
    text_start("Your #MON style"
        t_line "is stunning and"
        t_cont "colorful, I admit."
        t_para "You'll just keep"
        t_line "getting better!"
        t_done )
};
const txt_cmd_s CooltrainerfGwenSeenText[] = {
    text_start("I'm in training."
        t_line "Care for a round?"
        t_done )
};
const txt_cmd_s CooltrainerfGwenBeatenText[] = {
    text_start("Aww, no! You're"
        t_line "too good for me."
        t_done )
};
const txt_cmd_s CooltrainerfGwenAfterBattleText[] = {
    text_start("I'm going to train"
        t_line "by myself until I"
        t_cont "improve."
        t_done )
};
const txt_cmd_s CooltrainerfEmmaSeenText[] = {
    text_start("If the #MON I"
        t_line "liked were there,"
        t_cont "I'd go anywhere."
        t_para "That's what a real"
        t_line "trainer does."
        t_done )
};
const txt_cmd_s CooltrainerfEmmaBeatenText[] = {
    text_start("I'd rather pet my"
        t_line "babies than this!"
        t_done )
};
const txt_cmd_s CooltrainerfEmmaAfterBattleText[] = {
    text_start("Just once a week,"
        t_line "a #MON comes to"
        t_cont "the water's edge."
        t_para "I wanted to see"
        t_line "that #MON…"
        t_done )
    //db(0, 0) // filler
};
