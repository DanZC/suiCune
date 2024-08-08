#include "../constants.h"
#include "../util/scripting.h"
#include "Route25.h"
//// EVENTS
enum {
    ROUTE25_MISTY = 2,
    ROUTE25_COOLTRAINER_M1,
    ROUTE25_YOUNGSTER1,
    ROUTE25_LASS1,
    ROUTE25_YOUNGSTER2,
    ROUTE25_LASS2,
    ROUTE25_YOUNGSTER3,
    ROUTE25_LASS3,
    ROUTE25_SUPER_NERD,
    ROUTE25_COOLTRAINER_M2,
    ROUTE25_POKE_BALL,
};

const Script_fn_t Route25_SceneScripts[] = {
    Route25_MapScripts_DummyScene0 , //  SCENE_ROUTE25_NOTHING,
    Route25_MapScripts_DummyScene1 , //  SCENE_ROUTE25_MISTYS_DATE,
};

const struct MapCallback Route25_MapCallbacks[] = {
    0,
};

const struct MapScripts Route25_MapScripts = {
    .scene_script_count = lengthof(Route25_SceneScripts),
    .scene_scripts = Route25_SceneScripts,

    .callback_count = 0, // lengthof(Route25_MapCallbacks),
    .callbacks = Route25_MapCallbacks,
};

static const struct CoordEvent Route25_CoordEvents[] = {
    coord_event(42, 6, SCENE_ROUTE25_MISTYS_DATE, &Route25MistyDate1Script),
    coord_event(42, 7, SCENE_ROUTE25_MISTYS_DATE, &Route25MistyDate2Script),
};

static const struct BGEvent Route25_BGEvents[] = {
    bg_event(45, 5, BGEVENT_READ, &BillsHouseSign),
    bg_event(4, 5, BGEVENT_ITEM, &Route25HiddenPotion),
};

static const struct WarpEventData Route25_WarpEvents[] = {
    warp_event(47, 5, BILLS_HOUSE, 1),
};

static const struct ObjEvent Route25_ObjectEvents[] = {
    object_event(46, 9, SPRITE_MISTY, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &ObjectEvent, EVENT_ROUTE_25_MISTY_BOYFRIEND),
    object_event(46, 10, SPRITE_COOLTRAINER_M, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &ObjectEvent, EVENT_ROUTE_25_MISTY_BOYFRIEND),
    object_event(12, 8, SPRITE_YOUNGSTER, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_TRAINER, 3, &TrainerSchoolboyDudley, -1),
    object_event(16, 11, SPRITE_LASS, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_TRAINER, 3, &TrainerLassEllen, -1),
    object_event(21, 8, SPRITE_YOUNGSTER, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_TRAINER, 1, &TrainerSchoolboyJoe, -1),
    object_event(22, 6, SPRITE_LASS, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_TRAINER, 3, &TrainerLassLaura, -1),
    object_event(25, 4, SPRITE_YOUNGSTER, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_TRAINER, 2, &TrainerCamperLloyd, -1),
    object_event(28, 11, SPRITE_LASS, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_TRAINER, 1, &TrainerLassShannon, -1),
    object_event(31, 7, SPRITE_SUPER_NERD, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_BROWN, OBJECTTYPE_TRAINER, 1, &TrainerSupernerdPat, -1),
    object_event(37, 8, SPRITE_COOLTRAINER_M, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &TrainerCooltrainermKevin, -1),
    object_event(32, 4, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &Route25Protein, EVENT_ROUTE_25_PROTEIN),
};

const struct MapEvents Route25_MapEvents = {
    .warp_event_count = lengthof(Route25_WarpEvents),
    .warp_events = Route25_WarpEvents,

    .coord_event_count = lengthof(Route25_CoordEvents),
    .coord_events = Route25_CoordEvents,

    .bg_event_count = lengthof(Route25_BGEvents),
    .bg_events = Route25_BGEvents,

    .obj_event_count = lengthof(Route25_ObjectEvents),
    .obj_events = Route25_ObjectEvents,
};

//// CODE

bool Route25_MapScripts_DummyScene0(script_s* s) {
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}
bool Route25_MapScripts_DummyScene1(script_s* s) {
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}
bool Route25MistyDate1Script(script_s* s) {
    SCRIPT_BEGIN
    showemote(EMOTE_HEART, ROUTE25_MISTY, 15)
    pause(30)
    showemote(EMOTE_SHOCK, ROUTE25_COOLTRAINER_M1, 10)
    turnobject(ROUTE25_MISTY, DOWN)
    applymovement(ROUTE25_COOLTRAINER_M1, Route25MistysDateLeavesMovement1)
    disappear(ROUTE25_COOLTRAINER_M1)
    pause(15)
    playmusic(MUSIC_BEAUTY_ENCOUNTER)
    turnobject(ROUTE25_MISTY, UP)
    pause(10)
    applymovement(ROUTE25_MISTY, Route25MistyApproachesPlayerMovement1)
    opentext
    writetext(Route25MistyDateText)
    waitbutton
    closetext
    turnobject(PLAYER, DOWN)
    applymovement(ROUTE25_MISTY, Route25MistyLeavesPlayerMovement1)
    turnobject(PLAYER, LEFT)
    applymovement(ROUTE25_MISTY, Route25MistyLeavesMovement)
    disappear(ROUTE25_MISTY)
    clearevent(EVENT_TRAINERS_IN_CERULEAN_GYM)
    setscene(SCENE_ROUTE25_NOTHING)
    special(RestartMapMusic)
    s_end
    SCRIPT_END
}
bool Route25MistyDate2Script(script_s* s) {
    SCRIPT_BEGIN
    showemote(EMOTE_HEART, ROUTE25_MISTY, 15)
    pause(30)
    showemote(EMOTE_SHOCK, ROUTE25_COOLTRAINER_M1, 10)
    turnobject(ROUTE25_MISTY, DOWN)
    applymovement(ROUTE25_COOLTRAINER_M1, Route25MistysDateLeavesMovement2)
    disappear(ROUTE25_COOLTRAINER_M1)
    pause(15)
    playmusic(MUSIC_BEAUTY_ENCOUNTER)
    turnobject(ROUTE25_MISTY, UP)
    pause(10)
    applymovement(ROUTE25_MISTY, Route25MistyApproachesPlayerMovement2)
    opentext
    writetext(Route25MistyDateText)
    waitbutton
    closetext
    turnobject(PLAYER, UP)
    applymovement(ROUTE25_MISTY, Route25MistyLeavesPlayerMovement2)
    turnobject(PLAYER, LEFT)
    applymovement(ROUTE25_MISTY, Route25MistyLeavesMovement)
    disappear(ROUTE25_MISTY)
    clearevent(EVENT_TRAINERS_IN_CERULEAN_GYM)
    setscene(SCENE_ROUTE25_NOTHING)
    special(RestartMapMusic)
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerSchoolboyDudley = {SCHOOLBOY, DUDLEY, EVENT_BEAT_SCHOOLBOY_DUDLEY, SchoolboyDudleySeenText, SchoolboyDudleyBeatenText, 0, TrainerSchoolboyDudley_Script};
bool TrainerSchoolboyDudley_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(SchoolboyDudleyAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerLassEllen = {LASS, ELLEN, EVENT_BEAT_LASS_ELLEN, LassEllenSeenText, LassEllenBeatenText, 0, TrainerLassEllen_Script};
bool TrainerLassEllen_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(LassEllenAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerSchoolboyJoe = {SCHOOLBOY, JOE, EVENT_BEAT_SCHOOLBOY_JOE, SchoolboyJoeSeenText, SchoolboyJoeBeatenText, 0, TrainerSchoolboyJoe_Script};
bool TrainerSchoolboyJoe_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(SchoolboyJoeAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerLassLaura = {LASS, LAURA, EVENT_BEAT_LASS_LAURA, LassLauraSeenText, LassLauraBeatenText, 0, TrainerLassLaura_Script};
bool TrainerLassLaura_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(LassLauraAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerCamperLloyd = {CAMPER, LLOYD, EVENT_BEAT_CAMPER_LLOYD, CamperLloydSeenText, CamperLloydBeatenText, 0, TrainerCamperLloyd_Script};
bool TrainerCamperLloyd_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(CamperLloydAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerLassShannon = {LASS, SHANNON, EVENT_BEAT_LASS_SHANNON, LassShannonSeenText, LassShannonBeatenText, 0, TrainerLassShannon_Script};
bool TrainerLassShannon_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(LassShannonAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerSupernerdPat = {SUPER_NERD, PAT, EVENT_BEAT_SUPER_NERD_PAT, SupernerdPatSeenText, SupernerdPatBeatenText, 0, TrainerSupernerdPat_Script};
bool TrainerSupernerdPat_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(SupernerdPatAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool TrainerCooltrainermKevin(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_BEAT_COOLTRAINERM_KEVIN)
    iftrue(AfterBattle)
    checkevent(EVENT_CLEARED_NUGGET_BRIDGE)
    iftrue(AfterNuggetBridge)
    writetext(CooltrainermKevinNuggetText)
    promptbutton
    verbosegiveitem(NUGGET, 1)
    iffalse(NoRoomForNugget)
    setevent(EVENT_CLEARED_NUGGET_BRIDGE)
AfterNuggetBridge:
    writetext(CooltrainermKevinSeenText)
    waitbutton
    closetext
    winlosstext(CooltrainermKevinBeatenText, 0)
    loadtrainer(COOLTRAINERM, KEVIN)
    startbattle
    reloadmapafterbattle
    setevent(EVENT_BEAT_COOLTRAINERM_KEVIN)
    opentext
AfterBattle:
    writetext(CooltrainermKevinAfterBattleText)
    waitbutton
NoRoomForNugget:
    closetext
    s_end
    SCRIPT_END
}
bool BillsHouseSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(BillsHouseSignText)
    SCRIPT_END
}
const struct ItemBall Route25Protein = {PROTEIN, 1};
const struct HiddenItem Route25HiddenPotion = {POTION, EVENT_ROUTE_25_HIDDEN_POTION};
const uint8_t Route25MistysDateLeavesMovement1[] = {
    big_step(DOWN),
    movement_step_end,
};
const uint8_t Route25MistysDateLeavesMovement2[] = {
    big_step(DOWN),
    big_step(DOWN),
    movement_step_end,
};
const uint8_t Route25MistyApproachesPlayerMovement1[] = {
    step(UP),
    step(UP),
    step(UP),
    step(LEFT),
    step(LEFT),
    step(LEFT),
    movement_step_end,
};
const uint8_t Route25MistyApproachesPlayerMovement2[] = {
    step(UP),
    step(UP),
    step(LEFT),
    step(LEFT),
    step(LEFT),
    movement_step_end,
};
const uint8_t Route25MistyLeavesPlayerMovement1[] = {
    step(DOWN),
    step(LEFT),
    movement_step_end,
};
const uint8_t Route25MistyLeavesPlayerMovement2[] = {
    step(UP),
    step(LEFT),
    movement_step_end,
};
const uint8_t Route25MistyLeavesMovement[] = {
    step(LEFT),
    step(LEFT),
    step(LEFT),
    step(LEFT),
    step(LEFT),
    movement_step_end,
};
const txt_cmd_s Route25MistyDateText[] = {
    text_start("MISTY: Aww! Why"
        t_line "did you have to"
        t_para "show up and bug us"
        t_line "now?"
        t_para "Do you know what"
        t_line "they call people"
        t_cont "like you?"
        t_para "Pests! You heard"
        t_line "me right, pest!"
        t_para "…"
        t_para "…Oh? Those BADGES"
        t_line "you have… Are they"
        t_cont "JOHTO GYM BADGES?"
        t_para "If you have eight,"
        t_line "you must be good."
        t_para "OK, then. Come to"
        t_line "CERULEAN GYM."
        t_para "I'll be happy to"
        t_line "take you on."
        t_para "I'm MISTY, the"
        t_line "GYM LEADER in"
        t_cont "CERULEAN."
        t_done )
};
const txt_cmd_s SchoolboyDudleySeenText[] = {
    text_start("Beat the six of us"
        t_line "trainers to win a"
        t_cont "fabulous prize!"
        t_para "Think you've got"
        t_line "what it takes?"
        t_done )
};
const txt_cmd_s SchoolboyDudleyBeatenText[] = {
    text_start("Whoo! Good stuff."
        t_done )
};
const txt_cmd_s SchoolboyDudleyAfterBattleText[] = {
    text_start("I did my best."
        t_line "I have no regrets."
        t_done )
};
const txt_cmd_s LassEllenSeenText[] = {
    text_start("I'm second."
        t_line "Now it's serious!"
        t_done )
};
const txt_cmd_s LassEllenBeatenText[] = {
    text_start("How could I lose?"
        t_done )
};
const txt_cmd_s LassEllenAfterBattleText[] = {
    text_start("I did my best."
        t_line "I have no regrets."
        t_done )
};
const txt_cmd_s SchoolboyJoeSeenText[] = {
    text_start("Here's No. 3!"
        t_line "I won't be easy."
        t_done )
};
const txt_cmd_s SchoolboyJoeBeatenText[] = {
    text_start("Ow! Stomped flat!"
        t_done )
};
const txt_cmd_s SchoolboyJoeAfterBattleText[] = {
    text_start("I did my best."
        t_line "I have no regrets."
        t_done )
};
const txt_cmd_s LassLauraSeenText[] = {
    text_start("I'm No. 4!"
        t_line "Getting tired?"
        t_done )
};
const txt_cmd_s LassLauraBeatenText[] = {
    text_start("I lost too…"
        t_done )
};
const txt_cmd_s LassLauraAfterBattleText[] = {
    text_start("I did my best."
        t_line "I have no regrets."
        t_done )
};
const txt_cmd_s CamperLloydSeenText[] = {
    text_start("OK! I'm No. 5."
        t_line "I'll stomp you!"
        t_done )
};
const txt_cmd_s CamperLloydBeatenText[] = {
    text_start("Whoa! Too much."
        t_done )
};
const txt_cmd_s CamperLloydAfterBattleText[] = {
    text_start("I did my best."
        t_line "I have no regrets."
        t_done )
};
const txt_cmd_s LassShannonSeenText[] = {
    text_start("I'm the last in"
        t_line "line, but I tell"
        t_cont "you, I'm tough!"
        t_done )
};
const txt_cmd_s LassShannonBeatenText[] = {
    text_start("You're kidding."
        t_done )
};
const txt_cmd_s LassShannonAfterBattleText[] = {
    text_start("I did my best."
        t_line "I have no regrets."
        t_done )
};
const txt_cmd_s SupernerdPatSeenText[] = {
    text_start("Mufufufu…"
        t_para "I have nothing to"
        t_line "do with the six-"
        t_cont "pack trainers."
        t_para "I waited here to"
        t_line "beat you when you"
        t_para "were tired out by"
        t_line "all the battles."
        t_done )
};
const txt_cmd_s SupernerdPatBeatenText[] = {
    text_start("Aren't you tired"
        t_line "at all?"
        t_done )
};
const txt_cmd_s SupernerdPatAfterBattleText[] = {
    text_start("I'm sorry… I won't"
        t_line "cheat anymore…"
        t_done )
};
const txt_cmd_s CooltrainermKevinNuggetText[] = {
    text_start("You took on one"
        t_line "more battle than"
        t_para "you expected, but"
        t_line "you won anyway."
        t_para "As promised, you"
        t_line "win a prize."
        t_done )
};
const txt_cmd_s CooltrainermKevinSeenText[] = {
    text_start("But after seeing"
        t_line "how you battle, I"
        t_para "want to see how"
        t_line "I'll fare."
        t_para "How about it? Let"
        t_line "me take you on."
        t_done )
};
const txt_cmd_s CooltrainermKevinBeatenText[] = {
    text_start("I've never had a"
        t_line "battle this good!"
        t_done )
};
const txt_cmd_s CooltrainermKevinAfterBattleText[] = {
    text_start("That was a great"
        t_line "battle!"
        t_para "You and your #-"
        t_line "MON are truly out-"
        t_cont "standing!"
        t_done )
};
const txt_cmd_s BillsHouseSignText[] = {
    text_start("SEA COTTAGE"
        t_line "BILL'S HOUSE"
        t_done )
};
const txt_cmd_s UnusedBillsHouseSignText[] = {
    text_start("BILL'S HOUSE"
        t_done )
    //db(0, 0) // filler
};
