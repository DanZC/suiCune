#include "../constants.h"
#include "../util/scripting.h"
#include "DragonShrine.h"
//// EVENTS
enum {
    DRAGONSHRINE_ELDER1 = 2,
    DRAGONSHRINE_ELDER2,
    DRAGONSHRINE_ELDER3,
    DRAGONSHRINE_CLAIR,
};

const Script_fn_t DragonShrine_SceneScripts[] = {
    DragonShrine_MapScripts_DragonShrineTest , //  SCENE_DEFAULT,
    DragonShrine_MapScripts_DummyScene , //  SCENE_FINISHED,
};

const struct MapCallback DragonShrine_MapCallbacks[] = {
    0,
};

const struct MapScripts DragonShrine_MapScripts = {
    .scene_script_count = lengthof(DragonShrine_SceneScripts),
    .scene_scripts = DragonShrine_SceneScripts,

    .callback_count = 0, // lengthof(DragonShrine_MapCallbacks),
    .callbacks = DragonShrine_MapCallbacks,
};

static const struct CoordEvent DragonShrine_CoordEvents[] = {
    0,
};

static const struct BGEvent DragonShrine_BGEvents[] = {
    0,
};

static const struct WarpEventData DragonShrine_WarpEvents[] = {
    warp_event(4, 9, DRAGONS_DEN_B1F, 2),
    warp_event(5, 9, DRAGONS_DEN_B1F, 2),
};

static const struct ObjEvent DragonShrine_ObjectEvents[] = {
    object_event(5, 1, SPRITE_ELDER, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &DragonShrineElder1Script, EVENT_TEMPORARY_UNTIL_MAP_RELOAD_1),
    object_event(2, 4, SPRITE_ELDER, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &DragonShrineElder2Script, EVENT_TEMPORARY_UNTIL_MAP_RELOAD_1),
    object_event(7, 4, SPRITE_ELDER, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &DragonShrineElder3Script, EVENT_TEMPORARY_UNTIL_MAP_RELOAD_1),
    object_event(4, 8, SPRITE_CLAIR, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &ObjectEvent, EVENT_DRAGON_SHRINE_CLAIR),
};

const struct MapEvents DragonShrine_MapEvents = {
    .warp_event_count = lengthof(DragonShrine_WarpEvents),
    .warp_events = DragonShrine_WarpEvents,

    .coord_event_count = 0, // lengthof(DragonShrine_CoordEvents),
    .coord_events = DragonShrine_CoordEvents,

    .bg_event_count = 0, // lengthof(DragonShrine_BGEvents),
    .bg_events = DragonShrine_BGEvents,

    .obj_event_count = lengthof(DragonShrine_ObjectEvents),
    .obj_events = DragonShrine_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "DragonShrine.h"

bool DragonShrine_MapScripts_DragonShrineTest(script_s* s) {
    SCRIPT_BEGIN
    sdefer(DragonShrine_MapScripts_DragonShrineTestScript);
    s_end
    SCRIPT_END
}
bool DragonShrine_MapScripts_DummyScene(script_s* s) {
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}
bool DragonShrine_MapScripts_DragonShrineTestScript(script_s* s) {
    SCRIPT_BEGIN
    applymovement(PLAYER, DragonShrinePlayerWalkInMovement)
    applymovement(DRAGONSHRINE_ELDER1, DragonShrineElderStepDownMovement)
    opentext
    writetext(DragonShrineElderGreetingText)
    promptbutton
Question1:
    setevent(EVENT_TEMPORARY_UNTIL_MAP_RELOAD_2)
    writetext(DragonShrineQuestion1Text)
    promptbutton
    loadmenu(&DragonShrineQuestion1_MenuHeader)
    verticalmenu
    closewindow
    ifequal(1, RightAnswer)
    ifequal(2, WrongAnswer)
    ifequal(3, RightAnswer)
    s_end
Question2:
    setevent(EVENT_TEMPORARY_UNTIL_MAP_RELOAD_3)
    writetext(DragonShrineQuestion2Text)
    promptbutton
    loadmenu(&DragonShrineQuestion2_MenuHeader)
    verticalmenu
    closewindow
    ifequal(1, RightAnswer)
    ifequal(2, RightAnswer)
    ifequal(3, WrongAnswer)
Question3:
    setevent(EVENT_TEMPORARY_UNTIL_MAP_RELOAD_4)
    writetext(DragonShrineQuestion3Text)
    promptbutton
    loadmenu(&DragonShrineQuestion3_MenuHeader)
    verticalmenu
    closewindow
    ifequal(1, WrongAnswer)
    ifequal(2, RightAnswer)
    ifequal(3, RightAnswer)
Question4:
    setevent(EVENT_TEMPORARY_UNTIL_MAP_RELOAD_5)
    writetext(DragonShrineQuestion4Text)
    promptbutton
    loadmenu(&DragonShrineQuestion4_MenuHeader)
    verticalmenu
    closewindow
    ifequal(1, RightAnswer)
    ifequal(2, WrongAnswer)
    ifequal(3, RightAnswer)
Question5:
    setevent(EVENT_TEMPORARY_UNTIL_MAP_RELOAD_6)
    writetext(DragonShrineQuestion5Text)
    promptbutton
    loadmenu(&DragonShrineQuestion5_MenuHeader)
    verticalmenu
    closewindow
    ifequal(1, WrongAnswer)
    ifequal(2, RightAnswer)
    ifequal(3, WrongAnswer)
RightAnswer:
    checkevent(EVENT_TEMPORARY_UNTIL_MAP_RELOAD_6)
    iftrue(PassedTheTest)
    writetext(DragonShrineRightAnswerText)
    promptbutton
    checkevent(EVENT_TEMPORARY_UNTIL_MAP_RELOAD_5)
    iftrue(Question5)
    checkevent(EVENT_TEMPORARY_UNTIL_MAP_RELOAD_4)
    iftrue(Question4)
    checkevent(EVENT_TEMPORARY_UNTIL_MAP_RELOAD_3)
    iftrue(Question3)
    checkevent(EVENT_TEMPORARY_UNTIL_MAP_RELOAD_2)
    iftrue(Question2)
WrongAnswer:
    closetext
    turnobject(DRAGONSHRINE_ELDER1, LEFT)
    opentext
    writetext(DragonShrineWrongAnswerText1)
    waitbutton
    closetext
    turnobject(DRAGONSHRINE_ELDER1, DOWN)
    opentext
    writetext(DragonShrineWrongAnswerText2)
    waitbutton
    closetext
    setevent(EVENT_ANSWERED_DRAGON_MASTER_QUIZ_WRONG)
    opentext
    checkevent(EVENT_TEMPORARY_UNTIL_MAP_RELOAD_6)
    iftrue(Question5)
    checkevent(EVENT_TEMPORARY_UNTIL_MAP_RELOAD_5)
    iftrue(Question4)
    checkevent(EVENT_TEMPORARY_UNTIL_MAP_RELOAD_4)
    iftrue(Question3)
    checkevent(EVENT_TEMPORARY_UNTIL_MAP_RELOAD_3)
    iftrue(Question2)
    checkevent(EVENT_TEMPORARY_UNTIL_MAP_RELOAD_2)
    iftrue(Question1)
PassedTheTest:
    writetext(DragonShrinePassedTestText)
    waitbutton
    closetext
    playsound(SFX_ENTER_DOOR)
    showemote(EMOTE_SHOCK, PLAYER, 15)
    playmusic(MUSIC_CLAIR)
    appear(DRAGONSHRINE_CLAIR)
    waitsfx
    turnobject(PLAYER, DOWN)
    pause(30)
    applymovement(DRAGONSHRINE_CLAIR, DragonShrineClairWalkInMovement)
    turnobject(DRAGONSHRINE_CLAIR, RIGHT)
    turnobject(PLAYER, LEFT)
    turnobject(DRAGONSHRINE_ELDER1, LEFT)
    opentext
    writetext(DragonShrineClairYouPassedText)
    waitbutton
    closetext
    special(FadeOutMusic)
    applymovement(DRAGONSHRINE_CLAIR, DragonShrineClairBigStepLeftMovement)
    opentext
    writetext(DragonShrineClairThatCantBeText)
    waitbutton
    closetext
    applymovement(DRAGONSHRINE_CLAIR, DragonShrineClairSlowStepLeftMovement)
    opentext
    writetext(DragonShrineClairYoureLyingText)
    waitbutton
    closetext
    applymovement(DRAGONSHRINE_ELDER1, DragonShrineElderWalkToClairMovement)
    turnobject(DRAGONSHRINE_CLAIR, UP)
    opentext
    writetext(DragonShrineMustIInformLanceText)
    waitbutton
    closetext
    showemote(EMOTE_SHOCK, DRAGONSHRINE_CLAIR, 15)
    opentext
    writetext(DragonShrineIUnderstandText)
    waitbutton
    closetext
    applymovement(DRAGONSHRINE_CLAIR, DragonShrineClairTwoSlowStepsRightMovement)
    opentext
    writetext(DragonShrineHereRisingBadgeText)
    waitbutton
    setflag(ENGINE_RISINGBADGE)
    playsound(SFX_GET_BADGE)
    waitsfx
    special(RestartMapMusic)
    specialphonecall(SPECIALCALL_MASTERBALL)
    setscene(SCENE_FINISHED)
    setmapscene(DRAGONS_DEN_B1F, SCENE_DRAGONSDENB1F_CLAIR_GIVES_TM)
    writetext(DragonShrinePlayerReceivedRisingBadgeText)
    promptbutton
    writetext(DragonShrineRisingBadgeExplanationText)
    waitbutton
    closetext
    applymovement(DRAGONSHRINE_ELDER1, DragonShrineElderWalkAway1Movement)
    turnobject(DRAGONSHRINE_CLAIR, UP)
    applymovement(DRAGONSHRINE_ELDER1, DragonShrineElderWalkAway2Movement)
    turnobject(PLAYER, UP)
    opentext
    writetext(DragonShrineElderScoldsClairText)
    waitbutton
    closetext
    opentext
    writetext(DragonShrineSpeechlessText)
    waitbutton
    closetext
    applymovement(DRAGONSHRINE_CLAIR, DragonShrineClairWalkOutMovement)
    playsound(SFX_ENTER_DOOR)
    disappear(DRAGONSHRINE_CLAIR)
    waitsfx
    setevent(EVENT_TEMPORARY_UNTIL_MAP_RELOAD_1)
    s_end
    SCRIPT_END
}
bool DragonShrineElder1Script(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_TEMPORARY_UNTIL_MAP_RELOAD_1)
    iftrue(DontGiveDratiniYet)
    checkevent(EVENT_TEMPORARY_UNTIL_MAP_RELOAD_7)
    iftrue(ReceivedDratini)
    checkevent(EVENT_GOT_DRATINI)
    iffalse(GiveDratini)
    checkevent(EVENT_BEAT_RIVAL_IN_MT_MOON)
    iftrue(BeatRivalInMtMoon)
    writetext(DragonShrineClairsGrandfatherText)
    waitbutton
    closetext
    s_end
GiveDratini:
    writetext(DragonShrineTakeThisDratiniText)
    waitbutton
    readvar(VAR_PARTYCOUNT)
    ifequal(PARTY_LENGTH, PartyFull)
    writetext(DragonShrinePlayerReceivedDratiniText)
    playsound(SFX_CAUGHT_MON)
    waitsfx
    givepoke(DRATINI, 15, NO_ITEM)
    checkevent(EVENT_ANSWERED_DRAGON_MASTER_QUIZ_WRONG)
    special(GiveDratini)
    setevent(EVENT_GOT_DRATINI)
    setevent(EVENT_TEMPORARY_UNTIL_MAP_RELOAD_7)
    writetext(DragonShrineSymbolicDragonText)
    waitbutton
    closetext
    s_end
PartyFull:
    writetext(DragonShrinePartyFullText)
    waitbutton
    closetext
    s_end
BeatRivalInMtMoon:
    writetext(DragonShrineSilverIsInTrainingText)
    waitbutton
    closetext
    s_end
DontGiveDratiniYet:
    writetext(DragonShrineComeAgainText)
    waitbutton
    closetext
    s_end
ReceivedDratini:
    writetext(DragonShrineSymbolicDragonText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool DragonShrineElder2Script(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    writetext(DragonShrineElder2Text)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool DragonShrineElder3Script(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    writetext(DragonShrineElder3Text)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct MenuHeader DragonShrineQuestion1_MenuHeader = {
    .flags = MENU_BACKUP_TILES, // flags
    .coord = menu_coords(8, 4, SCREEN_WIDTH - 1, TEXTBOX_Y - 1),
    //dw(.MenuData)
    .defaultOption = 1, // default option
// MenuData:
    .data = &(struct MenuData) {
        .flags = STATICMENU_CURSOR | STATICMENU_DISABLE_B, // flags
        .verticalMenu = {
            .count = 3, // items
            .options = (const char*[]) {
                "Pal@",
                "Underling@",
                "Friend@",
            },
        },
    },
};
const struct MenuHeader DragonShrineQuestion2_MenuHeader = {
    .flags = MENU_BACKUP_TILES, // flags
    .coord = menu_coords(9, 4, SCREEN_WIDTH - 1, TEXTBOX_Y - 1),
    //dw(.MenuData)
    .defaultOption = 1, // default option
// MenuData:
    .data = &(struct MenuData) {
        .flags = STATICMENU_CURSOR | STATICMENU_DISABLE_B, // flags
        .verticalMenu = {
            .count = 3, // items
            .options = (const char*[]) {
                "Strategy@",
                "Raising@",
                "Cheating@",
            },
        },
    },
};
const struct MenuHeader DragonShrineQuestion3_MenuHeader = {
    .flags = MENU_BACKUP_TILES, // flags
    .coord = menu_coords(5, 4, SCREEN_WIDTH - 1, TEXTBOX_Y - 1),
    //dw(.MenuData)
    .defaultOption = 1, // default option
// MenuData:
    .data = &(struct MenuData) {
        .flags = STATICMENU_CURSOR | STATICMENU_DISABLE_B, // flags
        .verticalMenu = {
            .count = 3, // items
            .options = (const char*[]) {
                "Weak person@",
                "Tough person@",
                "Anybody@",
            },
        },
    },
};
const struct MenuHeader DragonShrineQuestion4_MenuHeader = {
    .flags = MENU_BACKUP_TILES, // flags
    .coord = menu_coords(8, 4, SCREEN_WIDTH - 1, TEXTBOX_Y - 1),
    //dw(.MenuData)
    .defaultOption = 1, // default option
// MenuData:
    .data = &(struct MenuData) {
        .flags = STATICMENU_CURSOR | STATICMENU_DISABLE_B, // flags
        .verticalMenu = {
            .count = 3, // items
            .options = (const char*[]) {
                "Love@",
                "Violence@",
                "Knowledge@",
            },
        },
    },
};
const struct MenuHeader DragonShrineQuestion5_MenuHeader = {
    .flags = MENU_BACKUP_TILES, // flags
    .coord = menu_coords(12, 4, SCREEN_WIDTH - 1, TEXTBOX_Y - 1),
    //dw(.MenuData)
    .data = &(struct MenuData) {
    // MenuData:
        .flags = STATICMENU_CURSOR | STATICMENU_DISABLE_B, // flags
        .verticalMenu = {
            //db(3) // items
            .count = 3,
            .options = (const char*[]) {
                "Tough@",
                "Both@",
                "Weak@",
            },
        },
    },
    .defaultOption = 1, // default option
};
const uint8_t DragonShrinePlayerWalkInMovement[] = {
    slow_step(UP),
    slow_step(UP),
    slow_step(UP),
    slow_step(RIGHT),
    slow_step(UP),
    slow_step(UP),
    slow_step(UP),
    movement_step_end,
};
const uint8_t DragonShrineElderStepDownMovement[] = {
    slow_step(DOWN),
    movement_step_end,
};
const uint8_t DragonShrineElderWalkToClairMovement[] = {
    slow_step(LEFT),
    slow_step(LEFT),
    slow_step(LEFT),
    turn_head(DOWN),
    movement_step_end,
};
const uint8_t DragonShrineElderWalkAway1Movement[] = {
    slow_step(RIGHT),
    slow_step(RIGHT),
    movement_step_end,
};
const uint8_t DragonShrineElderWalkAway2Movement[] = {
    slow_step(RIGHT),
    turn_head(DOWN),
    movement_step_end,
};
const uint8_t DragonShrineClairWalkInMovement[] = {
    slow_step(UP),
    slow_step(UP),
    slow_step(UP),
    slow_step(UP),
    slow_step(UP),
    movement_step_end,
};
const uint8_t DragonShrineClairBigStepLeftMovement[] = {
    movement_fix_facing,
    big_step(LEFT),
    movement_step_end,
};
const uint8_t DragonShrineClairSlowStepLeftMovement[] = {
    slow_step(LEFT),
    movement_remove_fixed_facing,
    movement_step_end,
};
const uint8_t DragonShrineClairTwoSlowStepsRightMovement[] = {
    slow_step(RIGHT),
    slow_step(RIGHT),
    movement_step_end,
};
const uint8_t DragonShrineClairWalkOutMovement[] = {
    step(DOWN),
    step(DOWN),
    step(DOWN),
    step(DOWN),
    step(DOWN),
    step(DOWN),
    movement_step_end,
};
const txt_cmd_s DragonShrineElderGreetingText[] = {
    text_start("Hm… Good to see"
        t_line "you here."
        t_para "No need to explain"
        t_line "why you came."
        t_para "CLAIR sent you"
        t_line "here, didn't she?"
        t_para "That girl is a"
        t_line "handful…"
        t_para "I am sorry, but I"
        t_line "must test you."
        t_para "Not to worry, you"
        t_line "are to answer only"
        t_cont "a few questions."
        t_para "Ready?"
        t_done )
};
const txt_cmd_s DragonShrineQuestion1Text[] = {
    text_start("What are #MON"
        t_line "to you?"
        t_done )
};
const txt_cmd_s DragonShrineQuestion2Text[] = {
    text_start("What helps you to"
        t_line "win battles?"
        t_done )
};
const txt_cmd_s DragonShrineQuestion3Text[] = {
    text_start("What kind of"
        t_line "trainer do you"
        t_cont "wish to battle?"
        t_done )
};
const txt_cmd_s DragonShrineQuestion4Text[] = {
    text_start("What is most"
        t_line "important for"
        t_cont "raising #MON?"
        t_done )
};
const txt_cmd_s DragonShrineQuestion5Text[] = {
    text_start("Strong #MON."
        t_line "Weak #MON."
        t_para "Which is more"
        t_line "important?"
        t_done )
};
const txt_cmd_s DragonShrinePassedTestText[] = {
    text_start("Hm… I see…"
        t_para "You care deeply"
        t_line "for #MON."
        t_para "Very commendable."
        t_para "That conviction is"
        t_line "what is important!"
        t_para "<PLAYER>, don't"
        t_line "lose that belief."
        t_para "It will see you"
        t_line "through at the"
        t_cont "#MON LEAGUE."
        t_done )
};
const txt_cmd_s DragonShrineMustIInformLanceText[] = {
    text_start("CLAIR!"
        t_para "This child is"
        t_line "impeccable, in"
        t_cont "skill and spirit!"
        t_para "Admit defeat and"
        t_line "confer the RISING-"
        t_cont "BADGE!"
        t_para "…Or must I inform"
        t_line "LANCE of this?"
        t_done )
};
const txt_cmd_s DragonShrineElderScoldsClairText[] = {
    text_start("CLAIR…"
        t_para "Reflect upon what"
        t_line "it is that you"
        t_para "lack and this"
        t_line "child has."
        t_done )
};
const txt_cmd_s DragonShrineComeAgainText[] = {
    text_start("Come again, if you"
        t_line "so desire."
        t_done )
};
const txt_cmd_s DragonShrineTakeThisDratiniText[] = {
    text_start("Hm… Good to see"
        t_line "you here."
        t_para "Your arrival is"
        t_line "most fortunate."
        t_para "I have something"
        t_line "for you."
        t_para "Take this DRATINI"
        t_line "as proof that I"
        t_para "have recognized"
        t_line "your worth."
        t_done )
};
const txt_cmd_s DragonShrinePlayerReceivedDratiniText[] = {
    text_start("<PLAYER> received"
        t_line "DRATINI!"
        t_done )
};
const txt_cmd_s DragonShrinePartyFullText[] = {
    text_start("Hm? Your #MON"
        t_line "party is full."
        t_done )
};
const txt_cmd_s DragonShrineSymbolicDragonText[] = {
    text_start("Dragon #MON are"
        t_line "symbolic of our"
        t_cont "clan."
        t_para "You have shown"
        t_line "that you can be"
        t_para "entrusted with"
        t_line "one."
        t_done )
};
const txt_cmd_s DragonShrineClairsGrandfatherText[] = {
    text_start("CLAIR appears to"
        t_line "have learned an"
        t_para "invaluable lesson"
        t_line "from you."
        t_para "I thank you as her"
        t_line "grandfather."
        t_done )
};
const txt_cmd_s DragonShrineSilverIsInTrainingText[] = {
    text_start("A boy close to"
        t_line "your age is in"
        t_cont "training here."
        t_para "He is much like"
        t_line "CLAIR when she was"
        t_para "younger. It is a"
        t_line "little worrisome…"
        t_done )
};
const txt_cmd_s DragonShrineWrongAnswerText1[] = {
    text_start("Hah? I didn't"
        t_line "quite catch that…"
        t_done )
};
const txt_cmd_s DragonShrineWrongAnswerText2[] = {
    text_start("What was it you"
        t_line "said?"
        t_done )
};
const txt_cmd_s DragonShrineRightAnswerText[] = {
    text_start("Oh, I understand…"
        t_done )
};
const txt_cmd_s DragonShrineElder2Text[] = {
    text_start("It's been quite"
        t_line "some time since a"
        t_para "trainer has gained"
        t_line "our MASTER's rare"
        t_cont "approval."
        t_para "In fact, not since"
        t_line "Master LANCE."
        t_done )
};
const txt_cmd_s DragonShrineElder3Text[] = {
    text_start("You know young"
        t_line "Master LANCE?"
        t_para "He looks so much"
        t_line "like our MASTER"
        t_cont "did in his youth."
        t_para "It's in their"
        t_line "blood."
        t_done )
};
const txt_cmd_s DragonShrineClairYouPassedText[] = {
    text_start("So how did it go?"
        t_para "I guess there's no"
        t_line "point in asking."
        t_para "You did fail?"
        t_para "<……><……><……><……><……><……>"
        t_para "…What? You passed?"
        t_done )
};
const txt_cmd_s DragonShrineClairThatCantBeText[] = {
    text_start("That can't be!"
        t_done )
};
const txt_cmd_s DragonShrineClairYoureLyingText[] = {
    text_start("You're lying!"
        t_para "Even I haven't"
        t_line "been approved!"
        t_done )
};
const txt_cmd_s DragonShrineIUnderstandText[] = {
    text_start("I-I understand…"
        t_done )
};
const txt_cmd_s DragonShrineHereRisingBadgeText[] = {
    text_start("Here, this is the"
        t_line "RISINGBADGE…"
        t_para "Hurry up! Take it!"
        t_done )
};
const txt_cmd_s DragonShrinePlayerReceivedRisingBadgeText[] = {
    text_start("<PLAYER> received"
        t_line "RISINGBADGE."
        t_done )
};
const txt_cmd_s DragonShrineRisingBadgeExplanationText[] = {
    text_start("RISINGBADGE will"
        t_line "enable your"
        t_para "#MON to use the"
        t_line "move for climbing"
        t_cont "waterfalls."
        t_para "Also, all #MON"
        t_line "will recognize you"
        t_para "as a trainer and"
        t_line "obey your every"
        t_para "command without"
        t_line "question."
        t_done )
};
const txt_cmd_s DragonShrineSpeechlessText[] = {
    text_start("<……><……><……><……><……><……>"
        t_done )
    //db(0, 0) // filler
};
