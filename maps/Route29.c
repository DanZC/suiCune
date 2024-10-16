#include "../constants.h"
#include "../util/scripting.h"
#include "Route29.h"
//// EVENTS
enum {
    ROUTE29_COOLTRAINER_M1 = 2,
    ROUTE29_YOUNGSTER,
    ROUTE29_TEACHER1,
    ROUTE29_FRUIT_TREE,
    ROUTE29_FISHER,
    ROUTE29_COOLTRAINER_M2,
    ROUTE29_TUSCANY,
    ROUTE29_POKE_BALL,
};

const Script_fn_t Route29_SceneScripts[] = {
    Route29_MapScripts_DummyScene0 , //  SCENE_ROUTE29_NOTHING,
    Route29_MapScripts_DummyScene1 , //  SCENE_ROUTE29_CATCH_TUTORIAL,
};

const struct MapCallback Route29_MapCallbacks[] = {
    map_callback(MAPCALLBACK_OBJECTS, Route29_MapScripts_Tuscany),
};

const struct MapScripts Route29_MapScripts = {
    .scene_script_count = lengthof(Route29_SceneScripts),
    .scene_scripts = Route29_SceneScripts,

    .callback_count = lengthof(Route29_MapCallbacks),
    .callbacks = Route29_MapCallbacks,
};

static const struct CoordEvent Route29_CoordEvents[] = {
    coord_event(53, 8, SCENE_ROUTE29_CATCH_TUTORIAL, Route29Tutorial1),
    coord_event(53, 9, SCENE_ROUTE29_CATCH_TUTORIAL, Route29Tutorial2),
};

static const struct BGEvent Route29_BGEvents[] = {
    bg_event(51, 7, BGEVENT_READ, Route29Sign1),
    bg_event(3, 5, BGEVENT_READ, Route29Sign2),
};

static const struct WarpEventData Route29_WarpEvents[] = {
    warp_event(27, 1, ROUTE_29_ROUTE_46_GATE, 3),
};

static const struct ObjEvent Route29_ObjectEvents[] = {
    object_event(50, 12, SPRITE_COOLTRAINER_M, SPRITEMOVEDATA_SPINRANDOM_SLOW, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, CatchingTutorialDudeScript, -1),
    object_event(27, 16, SPRITE_YOUNGSTER, SPRITEMOVEDATA_WALK_UP_DOWN, 0, 1, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, Route29YoungsterScript, -1),
    object_event(15, 11, SPRITE_TEACHER, SPRITEMOVEDATA_WALK_LEFT_RIGHT, 1, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, Route29TeacherScript, -1),
    object_event(12, 2, SPRITE_FRUIT_TREE, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, Route29FruitTree, -1),
    object_event(25, 3, SPRITE_FISHER, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, Route29FisherScript, -1),
    object_event(13, 4, SPRITE_COOLTRAINER_M, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, Route29CooltrainerMScript, -1),
    object_event(29, 12, SPRITE_TEACHER, SPRITEMOVEDATA_SPINRANDOM_SLOW, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, TuscanyScript, EVENT_ROUTE_29_TUSCANY_OF_TUESDAY),
    object_event(48, 2, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &Route29Potion, EVENT_ROUTE_29_POTION),
};

const struct MapEvents Route29_MapEvents = {
    .warp_event_count = lengthof(Route29_WarpEvents),
    .warp_events = Route29_WarpEvents,

    .coord_event_count = lengthof(Route29_CoordEvents),
    .coord_events = Route29_CoordEvents,

    .bg_event_count = lengthof(Route29_BGEvents),
    .bg_events = Route29_BGEvents,

    .obj_event_count = lengthof(Route29_ObjectEvents),
    .obj_events = Route29_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "Route29.h"

bool Route29_MapScripts_DummyScene0(script_s* s) {
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}
bool Route29_MapScripts_DummyScene1(script_s* s) {
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}
bool Route29_MapScripts_Tuscany(script_s* s) {
    SCRIPT_BEGIN
    checkflag(ENGINE_ZEPHYRBADGE)
    iftrue_jump(Route29_MapScripts_DoesTuscanyAppear)
    SCRIPT_FALLTHROUGH(Route29_MapScripts_TuscanyDisappears)
}
bool Route29_MapScripts_TuscanyDisappears(script_s* s) {
    SCRIPT_BEGIN
    disappear(ROUTE29_TUSCANY)
    s_endcallback
    SCRIPT_END
}
bool Route29_MapScripts_DoesTuscanyAppear(script_s* s) {
    SCRIPT_BEGIN
    readvar(VAR_WEEKDAY)
    ifnotequal_jump(TUESDAY, Route29_MapScripts_TuscanyDisappears)
    appear(ROUTE29_TUSCANY)
    s_endcallback
    SCRIPT_END
}
bool Route29Tutorial1(script_s* s) {
    SCRIPT_BEGIN
    turnobject(ROUTE29_COOLTRAINER_M1, UP)
    showemote(EMOTE_SHOCK, ROUTE29_COOLTRAINER_M1, 15)
    applymovement(ROUTE29_COOLTRAINER_M1, DudeMovementData1a)
    turnobject(PLAYER, LEFT)
    setevent(EVENT_DUDE_TALKED_TO_YOU)
    opentext
    writetext(CatchingTutorialIntroText)
    yesorno
    iffalse_jump(Script_RefusedTutorial1)
    closetext
    follow(ROUTE29_COOLTRAINER_M1, PLAYER)
    applymovement(ROUTE29_COOLTRAINER_M1, DudeMovementData1b)
    stopfollow
    loadwildmon(RATTATA, 5)
    catchtutorial(BATTLETYPE_TUTORIAL)
    turnobject(ROUTE29_COOLTRAINER_M1, UP)
    opentext
    writetext(CatchingTutorialDebriefText)
    waitbutton
    closetext
    setscene(SCENE_ROUTE29_NOTHING)
    setevent(EVENT_LEARNED_TO_CATCH_POKEMON)
    s_end
    SCRIPT_END
}
bool Route29Tutorial2(script_s* s) {
    SCRIPT_BEGIN
    turnobject(ROUTE29_COOLTRAINER_M1, UP)
    showemote(EMOTE_SHOCK, ROUTE29_COOLTRAINER_M1, 15)
    applymovement(ROUTE29_COOLTRAINER_M1, DudeMovementData2a)
    turnobject(PLAYER, LEFT)
    setevent(EVENT_DUDE_TALKED_TO_YOU)
    opentext
    writetext(CatchingTutorialIntroText)
    yesorno
    iffalse_jump(Script_RefusedTutorial2)
    closetext
    follow(ROUTE29_COOLTRAINER_M1, PLAYER)
    applymovement(ROUTE29_COOLTRAINER_M1, DudeMovementData2b)
    stopfollow
    loadwildmon(RATTATA, 5)
    catchtutorial(BATTLETYPE_TUTORIAL)
    turnobject(ROUTE29_COOLTRAINER_M1, UP)
    opentext
    writetext(CatchingTutorialDebriefText)
    waitbutton
    closetext
    setscene(SCENE_ROUTE29_NOTHING)
    setevent(EVENT_LEARNED_TO_CATCH_POKEMON)
    s_end
    SCRIPT_END
}
bool Script_RefusedTutorial1(script_s* s) {
    SCRIPT_BEGIN
    writetext(CatchingTutorialDeclinedText)
    waitbutton
    closetext
    applymovement(ROUTE29_COOLTRAINER_M1, DudeMovementData1b)
    setscene(SCENE_ROUTE29_NOTHING)
    s_end
    SCRIPT_END
}
bool Script_RefusedTutorial2(script_s* s) {
    SCRIPT_BEGIN
    writetext(CatchingTutorialDeclinedText)
    waitbutton
    closetext
    applymovement(ROUTE29_COOLTRAINER_M1, DudeMovementData2b)
    setscene(SCENE_ROUTE29_NOTHING)
    s_end
    SCRIPT_END
}
bool CatchingTutorialDudeScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    readvar(VAR_BOXSPACE)
    ifequal(0, BoxFull)
    checkevent(EVENT_LEARNED_TO_CATCH_POKEMON)
    iftrue(BoxFull)
    checkevent(EVENT_GAVE_MYSTERY_EGG_TO_ELM)
    iffalse(BoxFull)
    writetext(CatchingTutorialRepeatText)
    yesorno
    iffalse(Declined)
    closetext
    loadwildmon(RATTATA, 5)
    catchtutorial(BATTLETYPE_TUTORIAL)
    opentext
    writetext(CatchingTutorialDebriefText)
    waitbutton
    closetext
    setevent(EVENT_LEARNED_TO_CATCH_POKEMON)
    s_end
BoxFull:
    writetext(CatchingTutorialBoxFullText)
    waitbutton
    closetext
    s_end
Declined:
    writetext(CatchingTutorialDeclinedText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool Route29YoungsterScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(Route29YoungsterText)
    SCRIPT_END
}
bool Route29TeacherScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(Route29TeacherText)
    SCRIPT_END
}
bool Route29FisherScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(Route29FisherText)
    SCRIPT_END
}
bool Route29CooltrainerMScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checktime(DAY)
    iftrue(day_morn)
    checktime(NITE)
    iftrue(nite)
day_morn:
    writetext(Route29CooltrainerMText_WaitingForNight)
    waitbutton
    closetext
    s_end
nite:
    writetext(Route29CooltrainerMText_WaitingForMorning)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool TuscanyScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_GOT_PINK_BOW_FROM_TUSCANY)
    iftrue_jump(TuscanyTuesdayScript)
    readvar(VAR_WEEKDAY)
    ifnotequal_jump(TUESDAY, TuscanyNotTuesdayScript)
    checkevent(EVENT_MET_TUSCANY_OF_TUESDAY)
    iftrue(MetTuscany)
    writetext(MeetTuscanyText)
    promptbutton
    setevent(EVENT_MET_TUSCANY_OF_TUESDAY)
MetTuscany:
    writetext(TuscanyGivesGiftText)
    promptbutton
    verbosegiveitem(PINK_BOW, 1)
    iffalse_jump(TuscanyDoneScript)
    setevent(EVENT_GOT_PINK_BOW_FROM_TUSCANY)
    writetext(TuscanyGaveGiftText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool TuscanyTuesdayScript(script_s* s) {
    SCRIPT_BEGIN
    writetext(TuscanyTuesdayText)
    waitbutton
    SCRIPT_FALLTHROUGH(TuscanyDoneScript)
}
bool TuscanyDoneScript(script_s* s) {
    SCRIPT_BEGIN
    closetext
    s_end
    SCRIPT_END
}
bool TuscanyNotTuesdayScript(script_s* s) {
    SCRIPT_BEGIN
    writetext(TuscanyNotTuesdayText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool Route29Sign1(script_s* s) {
    SCRIPT_BEGIN
    jumptext(Route29Sign1Text)
    SCRIPT_END
}
bool Route29Sign2(script_s* s) {
    SCRIPT_BEGIN
    jumptext(Route29Sign2Text)
    SCRIPT_END
}
bool Route29FruitTree(script_s* s) {
    SCRIPT_BEGIN
    fruittree(FRUITTREE_ROUTE_29)
    SCRIPT_END
}
const struct ItemBall Route29Potion = {POTION, 1};
const uint8_t DudeMovementData1a[] = {
    step(UP),
    step(UP),
    step(UP),
    step(UP),
    step(RIGHT),
    step(RIGHT),
    movement_step_end,
};
const uint8_t DudeMovementData2a[] = {
    step(UP),
    step(UP),
    step(UP),
    step(RIGHT),
    step(RIGHT),
    movement_step_end,
};
const uint8_t DudeMovementData1b[] = {
    step(LEFT),
    step(LEFT),
    step(DOWN),
    step(DOWN),
    step(DOWN),
    step(DOWN),
    movement_step_end,
};
const uint8_t DudeMovementData2b[] = {
    step(LEFT),
    step(LEFT),
    step(DOWN),
    step(DOWN),
    step(DOWN),
    movement_step_end,
};
const txt_cmd_s CatchingTutorialBoxFullText[] = {
    text_start("#MON hide in"
        t_line "the grass. Who"
        t_para "knows when they'll"
        t_line "pop out…"
        t_done )
};
const txt_cmd_s CatchingTutorialIntroText[] = {
    text_start("I've seen you a"
        t_line "couple times. How"
        t_para "many #MON have"
        t_line "you caught?"
        t_para "Would you like me"
        t_line "to show you how to"
        t_cont "catch #MON?"
        t_done )
};
const txt_cmd_s CatchingTutorialDebriefText[] = {
    text_start("That's how you do"
        t_line "it."
        t_para "If you weaken them"
        t_line "first, #MON are"
        t_cont "easier to catch."
        t_done )
};
const txt_cmd_s CatchingTutorialDeclinedText[] = {
    text_start("Oh. Fine, then."
        t_para "Anyway, if you"
        t_line "want to catch"
        t_para "#MON, you have"
        t_line "to walk a lot."
        t_done )
};
const txt_cmd_s CatchingTutorialRepeatText[] = {
    text_start("Huh? You want me"
        t_line "to show you how to"
        t_cont "catch #MON?"
        t_done )
};
const txt_cmd_s Route29YoungsterText[] = {
    text_start("Yo. How are your"
        t_line "#MON?"
        t_para "If they're weak"
        t_line "and not ready for"
        t_para "battle, keep out"
        t_line "of the grass."
        t_done )
};
const txt_cmd_s Route29TeacherText[] = {
    text_start("See those ledges?"
        t_line "It's scary to jump"
        t_cont "off them."
        t_para "But you can go to"
        t_line "NEW BARK without"
        t_para "walking through"
        t_line "the grass."
        t_done )
};
const txt_cmd_s Route29FisherText[] = {
    text_start("I wanted to take a"
        t_line "break, so I saved"
        t_para "to record my"
        t_line "progress."
        t_done )
};
const txt_cmd_s Route29CooltrainerMText_WaitingForDay[] = {
    text_start("I'm waiting for"
        t_line "#MON that"
        t_para "appear only in the"
        t_line "daytime."
        t_done )
};
const txt_cmd_s Route29CooltrainerMText_WaitingForNight[] = {
    text_start("I'm waiting for"
        t_line "#MON that"
        t_para "appear only at"
        t_line "night."
        t_done )
};
const txt_cmd_s Route29CooltrainerMText_WaitingForMorning[] = {
    text_start("I'm waiting for"
        t_line "#MON that"
        t_para "appear only in the"
        t_line "morning."
        t_done )
};
const txt_cmd_s MeetTuscanyText[] = {
    text_start("TUSCANY: I do be-"
        t_line "lieve that this is"
        t_para "the first time"
        t_line "we've met?"
        t_para "Please allow me to"
        t_line "introduce myself."
        t_para "I am TUSCANY of"
        t_line "Tuesday."
        t_done )
};
const txt_cmd_s TuscanyGivesGiftText[] = {
    text_start("By way of intro-"
        t_line "duction, please"
        t_para "accept this gift,"
        t_line "a PINK BOW."
        t_done )
};
const txt_cmd_s TuscanyGaveGiftText[] = {
    text_start("TUSCANY: Wouldn't"
        t_line "you agree that it"
        t_cont "is most adorable?"
        t_para "It strengthens"
        t_line "normal-type moves."
        t_para "I am certain it"
        t_line "will be of use."
        t_done )
};
const txt_cmd_s TuscanyTuesdayText[] = {
    text_start("TUSCANY: Have you"
        t_line "met MONICA, my"
        t_cont "older sister?"
        t_para "Or my younger"
        t_line "brother, WESLEY?"
        t_para "I am the second of"
        t_line "seven children."
        t_done )
};
const txt_cmd_s TuscanyNotTuesdayText[] = {
    text_start("TUSCANY: Today is"
        t_line "not Tuesday. That"
        t_cont "is unfortunate…"
        t_done )
};
const txt_cmd_s Route29Sign1Text[] = {
    text_start("ROUTE 29"
        t_para "CHERRYGROVE CITY -"
        t_line "NEW BARK TOWN"
        t_done )
};
const txt_cmd_s Route29Sign2Text[] = {
    text_start("ROUTE 29"
        t_para "CHERRYGROVE CITY -"
        t_line "NEW BARK TOWN"
        t_done )
    //db(0, 0) // filler
};
