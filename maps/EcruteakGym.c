#include "../constants.h"
#include "../util/scripting.h"
#include "EcruteakGym.h"
//// EVENTS
enum {
    ECRUTEAKGYM_MORTY = 2,
    ECRUTEAKGYM_SAGE1,
    ECRUTEAKGYM_SAGE2,
    ECRUTEAKGYM_GRANNY1,
    ECRUTEAKGYM_GRANNY2,
    ECRUTEAKGYM_GYM_GUIDE,
    ECRUTEAKGYM_GRAMPS,
};

const Script_fn_t EcruteakGym_SceneScripts[] = {
    EcruteakGym_MapScripts_ForcedToLeave , //  SCENE_DEFAULT,
    EcruteakGym_MapScripts_DummyScene , //  SCENE_FINISHED,
};

const struct MapCallback EcruteakGym_MapCallbacks[] = {
    0,
};

const struct MapScripts EcruteakGym_MapScripts = {
    .scene_script_count = lengthof(EcruteakGym_SceneScripts),
    .scene_scripts = EcruteakGym_SceneScripts,

    .callback_count = 0, // lengthof(EcruteakGym_MapCallbacks),
    .callbacks = EcruteakGym_MapCallbacks,
};

static const struct CoordEvent EcruteakGym_CoordEvents[] = {
    0,
};

static const struct BGEvent EcruteakGym_BGEvents[] = {
    bg_event(3, 15, BGEVENT_READ, &EcruteakGymStatue),
    bg_event(6, 15, BGEVENT_READ, &EcruteakGymStatue),
};

static const struct WarpEventData EcruteakGym_WarpEvents[] = {
    warp_event(4, 17, ECRUTEAK_CITY, 10),
    warp_event(5, 17, ECRUTEAK_CITY, 10),
    warp_event(4, 14, ECRUTEAK_GYM, 4),
    warp_event(2, 4, ECRUTEAK_GYM, 3),
    warp_event(3, 4, ECRUTEAK_GYM, 3),
    warp_event(4, 4, ECRUTEAK_GYM, 3),
    warp_event(4, 5, ECRUTEAK_GYM, 3),
    warp_event(6, 7, ECRUTEAK_GYM, 3),
    warp_event(7, 4, ECRUTEAK_GYM, 3),
    warp_event(2, 6, ECRUTEAK_GYM, 3),
    warp_event(3, 6, ECRUTEAK_GYM, 3),
    warp_event(4, 6, ECRUTEAK_GYM, 3),
    warp_event(5, 6, ECRUTEAK_GYM, 3),
    warp_event(7, 6, ECRUTEAK_GYM, 3),
    warp_event(7, 7, ECRUTEAK_GYM, 3),
    warp_event(4, 8, ECRUTEAK_GYM, 3),
    warp_event(5, 8, ECRUTEAK_GYM, 3),
    warp_event(6, 8, ECRUTEAK_GYM, 3),
    warp_event(7, 8, ECRUTEAK_GYM, 3),
    warp_event(2, 8, ECRUTEAK_GYM, 3),
    warp_event(2, 9, ECRUTEAK_GYM, 3),
    warp_event(2, 10, ECRUTEAK_GYM, 3),
    warp_event(2, 11, ECRUTEAK_GYM, 3),
    warp_event(4, 10, ECRUTEAK_GYM, 3),
    warp_event(5, 10, ECRUTEAK_GYM, 3),
    warp_event(2, 12, ECRUTEAK_GYM, 3),
    warp_event(3, 12, ECRUTEAK_GYM, 3),
    warp_event(4, 12, ECRUTEAK_GYM, 3),
    warp_event(5, 12, ECRUTEAK_GYM, 3),
    warp_event(7, 10, ECRUTEAK_GYM, 3),
    warp_event(7, 11, ECRUTEAK_GYM, 3),
    warp_event(7, 12, ECRUTEAK_GYM, 3),
    warp_event(7, 13, ECRUTEAK_GYM, 3),
};

static const struct ObjEvent EcruteakGym_ObjectEvents[] = {
    object_event(5, 1, SPRITE_MORTY, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_BROWN, OBJECTTYPE_SCRIPT, 0, &EcruteakGymMortyScript, -1),
    object_event(2, 7, SPRITE_SAGE, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_TRAINER, 1, &TrainerSageJeffrey, -1),
    object_event(3, 13, SPRITE_SAGE, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_TRAINER, 3, &TrainerSagePing, -1),
    object_event(7, 5, SPRITE_GRANNY, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, -1, PAL_NPC_BROWN, OBJECTTYPE_TRAINER, 1, &TrainerMediumMartha, -1),
    object_event(7, 9, SPRITE_GRANNY, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, -1, PAL_NPC_BROWN, OBJECTTYPE_TRAINER, 1, &TrainerMediumGrace, -1),
    object_event(7, 15, SPRITE_GYM_GUIDE, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &EcruteakGymGuideScript, -1),
    object_event(4, 14, SPRITE_GRAMPS, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &ObjectEvent, EVENT_ECRUTEAK_GYM_GRAMPS),
};

const struct MapEvents EcruteakGym_MapEvents = {
    .warp_event_count = lengthof(EcruteakGym_WarpEvents),
    .warp_events = EcruteakGym_WarpEvents,

    .coord_event_count = 0, // lengthof(EcruteakGym_CoordEvents),
    .coord_events = EcruteakGym_CoordEvents,

    .bg_event_count = lengthof(EcruteakGym_BGEvents),
    .bg_events = EcruteakGym_BGEvents,

    .obj_event_count = lengthof(EcruteakGym_ObjectEvents),
    .obj_events = EcruteakGym_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "EcruteakGym.h"

bool EcruteakGym_MapScripts_ForcedToLeave(script_s* s) {
    SCRIPT_BEGIN
    sdefer(EcruteakGymClosed)
    s_end
    SCRIPT_END
}
bool EcruteakGym_MapScripts_DummyScene(script_s* s) {
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}
bool EcruteakGymMortyScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_BEAT_MORTY)
    iftrue(FightDone)
    writetext(MortyIntroText)
    waitbutton
    closetext
    winlosstext(MortyWinLossText, 0)
    loadtrainer(MORTY, MORTY1)
    startbattle
    reloadmapafterbattle
    setevent(EVENT_BEAT_MORTY)
    opentext
    writetext(Text_ReceivedFogBadge)
    playsound(SFX_GET_BADGE)
    waitsfx
    setflag(ENGINE_FOGBADGE)
    readvar(VAR_BADGES)
    scall(EcruteakGymActivateRockets)
    setmapscene(ECRUTEAK_TIN_TOWER_ENTRANCE, SCENE_FINISHED)
    setevent(EVENT_RANG_CLEAR_BELL_1)
    setevent(EVENT_RANG_CLEAR_BELL_2)
FightDone:
    checkevent(EVENT_GOT_TM30_SHADOW_BALL)
    iftrue(GotShadowBall)
    setevent(EVENT_BEAT_SAGE_JEFFREY)
    setevent(EVENT_BEAT_SAGE_PING)
    setevent(EVENT_BEAT_MEDIUM_MARTHA)
    setevent(EVENT_BEAT_MEDIUM_GRACE)
    writetext(MortyText_FogBadgeSpeech)
    promptbutton
    verbosegiveitem(TM_SHADOW_BALL, 1)
    iffalse(NoRoomForShadowBall)
    setevent(EVENT_GOT_TM30_SHADOW_BALL)
    writetext(MortyText_ShadowBallSpeech)
    waitbutton
    closetext
    s_end
GotShadowBall:
    writetext(MortyFightDoneText)
    waitbutton
NoRoomForShadowBall:
    closetext
    s_end
    SCRIPT_END
}
bool EcruteakGymActivateRockets(script_s* s) {
    SCRIPT_BEGIN
    ifequal(7, RadioTowerRockets)
    ifequal(6, GoldenrodRockets)
    s_end
GoldenrodRockets:
    jumpstd(GoldenrodRocketsScript)
RadioTowerRockets:
    jumpstd(RadioTowerRocketsScript)
    SCRIPT_END
}
bool EcruteakGymClosed(script_s* s) {
    SCRIPT_BEGIN
    applymovement(PLAYER, EcruteakGymPlayerStepUpMovement)
    applymovement(ECRUTEAKGYM_GRAMPS, EcruteakGymGrampsSlowStepDownMovement)
    opentext
    writetext(EcruteakGymClosedText)
    waitbutton
    closetext
    follow(PLAYER, ECRUTEAKGYM_GRAMPS)
    applymovement(PLAYER, EcruteakGymPlayerSlowStepDownMovement)
    stopfollow
    special(FadeOutPalettes)
    playsound(SFX_ENTER_DOOR)
    waitsfx
    warp(ECRUTEAK_CITY, 6, 27)
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerSageJeffrey = {SAGE, JEFFREY, EVENT_BEAT_SAGE_JEFFREY, SageJeffreySeenText, SageJeffreyBeatenText, 0, TrainerSageJeffrey_Script};
bool TrainerSageJeffrey_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(SageJeffreyAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerSagePing = {SAGE, PING, EVENT_BEAT_SAGE_PING, SagePingSeenText, SagePingBeatenText, 0, TrainerSagePing_Script};
bool TrainerSagePing_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(SagePingAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerMediumMartha = {MEDIUM, MARTHA, EVENT_BEAT_MEDIUM_MARTHA, MediumMarthaSeenText, MediumMarthaBeatenText, 0, TrainerMediumMartha_Script};
bool TrainerMediumMartha_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(MediumMarthaAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerMediumGrace = {MEDIUM, GRACE, EVENT_BEAT_MEDIUM_GRACE, MediumGraceSeenText, MediumGraceBeatenText, 0, TrainerMediumGrace_Script};
bool TrainerMediumGrace_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(MediumGraceAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool EcruteakGymGuideScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_BEAT_MORTY)
    iftrue(EcruteakGymGuideWinScript)
    writetext(EcruteakGymGuideText)
    waitbutton
    closetext
    s_end
EcruteakGymGuideWinScript:
    writetext(EcruteakGymGuideWinText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool EcruteakGymStatue(script_s* s) {
    SCRIPT_BEGIN
    checkflag(ENGINE_FOGBADGE)
    iftrue(Beaten)
    jumpstd(GymStatue1Script)
Beaten:
    gettrainername(STRING_BUFFER_4, MORTY, MORTY1)
    jumpstd(GymStatue2Script)
    SCRIPT_END
}
const uint8_t EcruteakGymPlayerStepUpMovement[] = {
    step(UP),
    movement_step_end,
};
const uint8_t EcruteakGymPlayerSlowStepDownMovement[] = {
    movement_fix_facing,
    slow_step(DOWN),
    movement_remove_fixed_facing,
    movement_step_end,
};
const uint8_t EcruteakGymGrampsSlowStepDownMovement[] = {
    slow_step(DOWN),
    movement_step_end,
};
const txt_cmd_s MortyIntroText[] = {
    text_start("Good of you to"
        t_line "have come."
        t_para "Here in ECRUTEAK,"
        t_line "#MON have been"
        t_cont "revered."
        t_para "It's said that a"
        t_line "rainbow-colored"
        t_para "#MON will come"
        t_line "down to appear"
        t_para "before a truly"
        t_line "powerful trainer."
        t_para "I believed that"
        t_line "tale, so I have"
        t_para "secretly trained"
        t_line "here all my life."
        t_para "As a result, I can"
        t_line "now see what"
        t_cont "others cannot."
        t_para "Just a bit more…"
        t_para "With a little"
        t_line "more, I could see"
        t_para "a future in which"
        t_line "I meet the #MON"
        t_cont "of rainbow colors."
        t_para "You're going to"
        t_line "help me reach that"
        t_cont "level!"
        t_done )
};
const txt_cmd_s MortyWinLossText[] = {
    text_start("I'm not good"
        t_line "enough yet…"
        t_para "All right. This"
        t_line "BADGE is yours."
        t_done )
};
const txt_cmd_s Text_ReceivedFogBadge[] = {
    text_start("<PLAYER> received"
        t_line "FOGBADGE."
        t_done )
};
const txt_cmd_s MortyText_FogBadgeSpeech[] = {
    text_start("By having FOG-"
        t_line "BADGE, #MON up"
        t_para "to L50 will obey"
        t_line "you."
        t_para "Also, #MON that"
        t_line "know SURF will be"
        t_para "able to use that"
        t_line "move anytime."
        t_para "I want you to have"
        t_line "this too."
        t_done )
};
const txt_cmd_s MortyText_ShadowBallSpeech[] = {
    text_start("It's SHADOW BALL."
        t_line "It causes damage"
        t_para "and may reduce"
        t_line "SPCL.DEF."
        t_para "Use it if it"
        t_line "appeals to you."
        t_done )
};
const txt_cmd_s MortyFightDoneText[] = {
    text_start("I see…"
        t_para "Your journey has"
        t_line "taken you to far-"
        t_cont "away places."
        t_para "And you have wit-"
        t_line "nessed much more"
        t_cont "than I."
        t_para "I envy you for"
        t_line "that…"
        t_done )
};
const txt_cmd_s SageJeffreySeenText[] = {
    text_start("I spent the spring"
        t_line "with my #MON."
        t_para "Then summer, fall"
        t_line "and winter…"
        t_para "Then spring came"
        t_line "again. We have"
        t_para "lived together"
        t_line "for a long time."
        t_done )
};
const txt_cmd_s SageJeffreyBeatenText[] = {
    text_start("Wins and losses, I"
        t_line "experienced both."
        t_done )
};
const txt_cmd_s SageJeffreyAfterBattleText[] = {
    text_start("Where did #MON"
        t_line "come from?"
        t_done )
};
const txt_cmd_s SagePingSeenText[] = {
    text_start("Can you inflict"
        t_line "any damage on our"
        t_cont "#MON?"
        t_done )
};
const txt_cmd_s SagePingBeatenText[] = {
    text_start("Ah! Well done!"
        t_done )
};
const txt_cmd_s SagePingAfterBattleText[] = {
    text_start("We use only ghost-"
        t_line "type #MON."
        t_para "No normal-type"
        t_line "attack can harm"
        t_cont "them!"
        t_done )
};
const txt_cmd_s MediumMarthaSeenText[] = {
    text_start("I shall win!"
        t_done )
};
const txt_cmd_s MediumMarthaBeatenText[] = {
    text_start("I, I, I lost!"
        t_done )
};
const txt_cmd_s MediumMarthaAfterBattleText[] = {
    text_start("The one who wants"
        t_line "to win most--will!"
        t_done )
};
const txt_cmd_s MediumGraceSeenText[] = {
    text_start("Stumped by our in-"
        t_line "visible floor?"
        t_para "Defeat me if you"
        t_line "want a hint!"
        t_done )
};
const txt_cmd_s MediumGraceBeatenText[] = {
    text_start("Wha-what?"
        t_done )
};
const txt_cmd_s MediumGraceAfterBattleText[] = {
    text_start("Fine. I shall tell"
        t_line "you the secret of"
        t_para "the invisible"
        t_line "floor."
        t_para "The path is right"
        t_line "before our eyes!"
        t_done )
};
const txt_cmd_s EcruteakGymGuideText[] = {
    text_start("The trainers here"
        t_line "have secret mo-"
        t_cont "tives."
        t_para "If you win, they"
        t_line "may tell you some"
        t_para "deep secrets about"
        t_line "ECRUTEAK."
        t_done )
};
const txt_cmd_s EcruteakGymGuideWinText[] = {
    text_start("Whew, <PLAYER>."
        t_line "You did great!"
        t_para "I was cowering in"
        t_line "the corner out of"
        t_cont "pure terror!"
        t_done )
};
const txt_cmd_s EcruteakGymClosedText[] = {
    text_start("MORTY, the GYM"
        t_line "LEADER, is absent."
        t_para "Sorry, but you'll"
        t_line "have to leave."
        t_para "Hohohoho."
        t_done )
    //db(0, 0) // filler
};
