#include "../constants.h"
#include "../util/scripting.h"
#include "RadioTower4F.h"
//// EVENTS
enum {
    RADIOTOWER4F_FISHER = 2,
    RADIOTOWER4F_TEACHER,
    RADIOTOWER4F_GROWLITHE,
    RADIOTOWER4F_ROCKET1,
    RADIOTOWER4F_ROCKET2,
    RADIOTOWER4F_ROCKET_GIRL,
    RADIOTOWER4F_SCIENTIST,
};

const Script_fn_t RadioTower4F_SceneScripts[] = {
    0,
};

const struct MapCallback RadioTower4F_MapCallbacks[] = {
    0,
};

const struct MapScripts RadioTower4F_MapScripts = {
    .scene_script_count = 0, // lengthof(RadioTower4F_SceneScripts),
    .scene_scripts = RadioTower4F_SceneScripts,

    .callback_count = 0, // lengthof(RadioTower4F_MapCallbacks),
    .callbacks = RadioTower4F_MapCallbacks,
};

static const struct CoordEvent RadioTower4F_CoordEvents[] = {
    0,
};

static const struct BGEvent RadioTower4F_BGEvents[] = {
    bg_event(7, 0, BGEVENT_READ, &RadioTower4FProductionSign),
    bg_event(15, 0, BGEVENT_READ, &RadioTower4FStudio2Sign),
};

static const struct WarpEventData RadioTower4F_WarpEvents[] = {
    warp_event(0, 0, RADIO_TOWER_5F, 1),
    warp_event(9, 0, RADIO_TOWER_3F, 2),
    warp_event(12, 0, RADIO_TOWER_5F, 2),
    warp_event(17, 0, RADIO_TOWER_3F, 3),
};

static const struct ObjEvent RadioTower4F_ObjectEvents[] = {
    object_event(6, 4, SPRITE_FISHER, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &RadioTower4FFisherScript, EVENT_RADIO_TOWER_CIVILIANS_AFTER),
    object_event(14, 6, SPRITE_TEACHER, SPRITEMOVEDATA_SPINRANDOM_SLOW, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &RadioTower4FDJMaryScript, -1),
    object_event(12, 7, SPRITE_GROWLITHE, SPRITEMOVEDATA_POKEMON, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &RadioTowerMeowth, -1),
    object_event(5, 6, SPRITE_ROCKET, SPRITEMOVEDATA_SPINCLOCKWISE, 0, 0, -1, -1, 0, OBJECTTYPE_TRAINER, 3, &TrainerGruntM10, EVENT_RADIO_TOWER_ROCKET_TAKEOVER),
    object_event(14, 1, SPRITE_ROCKET, SPRITEMOVEDATA_STANDING_LEFT, 2, 0, -1, -1, 0, OBJECTTYPE_TRAINER, 2, &TrainerExecutivem2, EVENT_RADIO_TOWER_ROCKET_TAKEOVER),
    object_event(12, 4, SPRITE_ROCKET_GIRL, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_TRAINER, 1, &TrainerGruntF4, EVENT_RADIO_TOWER_ROCKET_TAKEOVER),
    object_event(4, 2, SPRITE_SCIENTIST, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_TRAINER, 4, &TrainerScientistRich, EVENT_RADIO_TOWER_ROCKET_TAKEOVER),
};

const struct MapEvents RadioTower4F_MapEvents = {
    .warp_event_count = lengthof(RadioTower4F_WarpEvents),
    .warp_events = RadioTower4F_WarpEvents,

    .coord_event_count = 0, // lengthof(RadioTower4F_CoordEvents),
    .coord_events = RadioTower4F_CoordEvents,

    .bg_event_count = lengthof(RadioTower4F_BGEvents),
    .bg_events = RadioTower4F_BGEvents,

    .obj_event_count = lengthof(RadioTower4F_ObjectEvents),
    .obj_events = RadioTower4F_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "RadioTower4F.h"

bool RadioTower4FFisherScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(RadioTower4FFisherText)
    SCRIPT_END
}
bool RadioTower4FDJMaryScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_GOT_PINK_BOW_FROM_MARY)
    iftrue(GotPinkBow)
    checkevent(EVENT_CLEARED_RADIO_TOWER)
    iftrue(ClearedRockets)
    writetext(RadioTower4FDJMaryText)
    waitbutton
    closetext
    s_end
ClearedRockets:
    writetext(RadioTower4FDJMaryText_ClearedRockets)
    promptbutton
    verbosegiveitem(PINK_BOW, 1)
    iffalse(NoRoom)
    writetext(RadioTower4FDJMaryText_GivePinkBow)
    waitbutton
    closetext
    setevent(EVENT_GOT_PINK_BOW_FROM_MARY)
    s_end
GotPinkBow:
    writetext(RadioTower4FDJMaryText_After)
    waitbutton
NoRoom:
    closetext
    s_end
    SCRIPT_END
}
bool RadioTowerMeowth(script_s* s) {
    SCRIPT_BEGIN
    opentext
    writetext(RadioTowerMeowthText)
    playcry(MEOWTH)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerGruntM10 = {GRUNTM, GRUNTM_10, EVENT_BEAT_ROCKET_GRUNTM_10, GruntM10SeenText, GruntM10BeatenText, 0, TrainerGruntM10_Script};
bool TrainerGruntM10_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(GruntM10AfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerExecutivem2 = {EXECUTIVEM, EXECUTIVEM_2, EVENT_BEAT_ROCKET_EXECUTIVEM_2, Executivem2SeenText, Executivem2BeatenText, 0, TrainerExecutivem2_Script};
bool TrainerExecutivem2_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(Executivem2AfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerGruntF4 = {GRUNTF, GRUNTF_4, EVENT_BEAT_ROCKET_GRUNTF_4, GruntF4SeenText, GruntF4BeatenText, 0, TrainerGruntF4_Script};
bool TrainerGruntF4_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(GruntF4AfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerScientistRich = {SCIENTIST, RICH, EVENT_BEAT_SCIENTIST_RICH, ScientistRichSeenText, ScientistRichBeatenText, 0, TrainerScientistRich_Script};
bool TrainerScientistRich_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(ScientistRichAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool RadioTower4FProductionSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(RadioTower4FProductionSignText)
    SCRIPT_END
}
bool RadioTower4FStudio2Sign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(RadioTower4FStudio2SignText)
    SCRIPT_END
}
const txt_cmd_s RadioTower4FFisherText[] = {
    text_start("I listened to the"
        t_line "radio while I was"
        t_cont "at the RUINS."
        t_para "I heard a strange"
        t_line "broadcast there."
        t_done )
};
const txt_cmd_s RadioTower4FDJMaryText[] = {
    text_start("MARY: Why? Why do"
        t_line "I have to suffer"
        t_cont "through this?"
        t_para "MEOWTH, help me!"
        t_done )
};
const txt_cmd_s RadioTower4FDJMaryText_ClearedRockets[] = {
    text_start("MARY: Oh! You're"
        t_line "my little savior!"
        t_para "Will you take this"
        t_line "as my thanks?"
        t_done )
};
const txt_cmd_s RadioTower4FDJMaryText_GivePinkBow[] = {
    text_start("MARY: It's just"
        t_line "right for #MON"
        t_para "that know normal-"
        t_line "type moves."
        t_done )
};
const txt_cmd_s RadioTower4FDJMaryText_After[] = {
    text_start("MARY: Please tune"
        t_line "into me on PROF."
        t_para "OAK'S #MON TALK"
        t_line "show."
        t_done )
};
const txt_cmd_s RadioTowerMeowthText[] = {
    text_start("MEOWTH: Meowth…"
        t_done )
};
const txt_cmd_s GruntM10SeenText[] = {
    text_start("You plan to rescue"
        t_line "the DIRECTOR?"
        t_para "That won't be pos-"
        t_line "sible because I'm"
        t_cont "going to beat you!"
        t_done )
};
const txt_cmd_s GruntM10BeatenText[] = {
    text_start("No! Unbelievable!"
        t_done )
};
const txt_cmd_s GruntM10AfterBattleText[] = {
    text_start("I don't believe"
        t_line "it! I was beaten!"
        t_done )
};
const txt_cmd_s Executivem2SeenText[] = {
    text_start("Stop! I'm known as"
        t_line "the TEAM ROCKET"
        t_cont "fortress!"
        t_para "You're not taking"
        t_line "another step!"
        t_done )
};
const txt_cmd_s Executivem2BeatenText[] = {
    text_start("The fortress came"
        t_line "down!"
        t_done )
};
const txt_cmd_s Executivem2AfterBattleText[] = {
    text_start("You've earned my"
        t_line "respect, so here's"
        t_cont "some advice."
        t_para "It's not too late."
        t_line "You can still turn"
        t_cont "back."
        t_done )
};
const txt_cmd_s GruntF4SeenText[] = {
    text_start("Don't I think"
        t_line "#MON are cute?"
        t_para "I'll think my"
        t_line "#MON are cute--"
        t_para "after they beat"
        t_line "yours!"
        t_done )
};
const txt_cmd_s GruntF4BeatenText[] = {
    text_start("Oh, no! They're so"
        t_line "useless!"
        t_done )
};
const txt_cmd_s GruntF4AfterBattleText[] = {
    text_start("I love my"
        t_line "beautiful self!"
        t_para "Who cares about"
        t_line "#MON?"
        t_done )
};
const txt_cmd_s ScientistRichSeenText[] = {
    text_start("Most excellent."
        t_para "This RADIO TOWER"
        t_line "will fulfill our"
        t_cont "grand design."
        t_done )
};
const txt_cmd_s ScientistRichBeatenText[] = {
    text_start("Hmmm…"
        t_para "All grand plans"
        t_line "come with snags."
        t_done )
};
const txt_cmd_s ScientistRichAfterBattleText[] = {
    text_start("Do you honestly"
        t_line "believe you can"
        t_cont "stop TEAM ROCKET?"
        t_done )
};
const txt_cmd_s RadioTower4FProductionSignText[] = {
    text_start("4F PRODUCTION"
        t_done )
};
const txt_cmd_s RadioTower4FStudio2SignText[] = {
    text_start("4F STUDIO 2"
        t_done )
    //db(0, 0) // filler
};
