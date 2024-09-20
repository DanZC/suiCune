#include "../constants.h"
#include "../util/scripting.h"
#include "CeruleanGym.h"
//// EVENTS
enum {
    CERULEANGYM_ROCKET = 2,
    CERULEANGYM_MISTY,
    CERULEANGYM_SWIMMER_GIRL1,
    CERULEANGYM_SWIMMER_GIRL2,
    CERULEANGYM_SWIMMER_GUY,
    CERULEANGYM_GYM_GUIDE,
};

const Script_fn_t CeruleanGym_SceneScripts[] = {
    CeruleanGym_MapScripts_DummyScene0 , //  SCENE_CERULEANGYM_NOTHING,
    CeruleanGym_MapScripts_GruntRunsOut , //  SCENE_CERULEANGYM_GRUNT_RUNS_OUT,
};

const struct MapCallback CeruleanGym_MapCallbacks[] = {
    0,
};

const struct MapScripts CeruleanGym_MapScripts = {
    .scene_script_count = lengthof(CeruleanGym_SceneScripts),
    .scene_scripts = CeruleanGym_SceneScripts,

    .callback_count = 0, // lengthof(CeruleanGym_MapCallbacks),
    .callbacks = CeruleanGym_MapCallbacks,
};

static const struct CoordEvent CeruleanGym_CoordEvents[] = {
    0,
};

static const struct BGEvent CeruleanGym_BGEvents[] = {
    bg_event(3, 8, BGEVENT_ITEM, &CeruleanGymHiddenMachinePart),
    bg_event(2, 13, BGEVENT_READ, &CeruleanGymStatue1),
    bg_event(6, 13, BGEVENT_READ, &CeruleanGymStatue2),
};

static const struct WarpEventData CeruleanGym_WarpEvents[] = {
    warp_event(4, 15, CERULEAN_CITY, 5),
    warp_event(5, 15, CERULEAN_CITY, 5),
};

static const struct ObjEvent CeruleanGym_ObjectEvents[] = {
    object_event(4, 10, SPRITE_ROCKET, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &ObjectEvent, EVENT_CERULEAN_GYM_ROCKET),
    object_event(5, 3, SPRITE_MISTY, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &CeruleanGymMistyScript, EVENT_TRAINERS_IN_CERULEAN_GYM),
    object_event(4, 6, SPRITE_SWIMMER_GIRL, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_TRAINER, 3, &TrainerSwimmerfDiana, EVENT_TRAINERS_IN_CERULEAN_GYM),
    object_event(1, 9, SPRITE_SWIMMER_GIRL, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_TRAINER, 1, &TrainerSwimmerfBriana, EVENT_TRAINERS_IN_CERULEAN_GYM),
    object_event(8, 9, SPRITE_SWIMMER_GUY, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_TRAINER, 3, &TrainerSwimmermParker, EVENT_TRAINERS_IN_CERULEAN_GYM),
    object_event(7, 13, SPRITE_GYM_GUIDE, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &CeruleanGymGuideScript, EVENT_TRAINERS_IN_CERULEAN_GYM),
};

const struct MapEvents CeruleanGym_MapEvents = {
    .warp_event_count = lengthof(CeruleanGym_WarpEvents),
    .warp_events = CeruleanGym_WarpEvents,

    .coord_event_count = 0, // lengthof(CeruleanGym_CoordEvents),
    .coord_events = CeruleanGym_CoordEvents,

    .bg_event_count = lengthof(CeruleanGym_BGEvents),
    .bg_events = CeruleanGym_BGEvents,

    .obj_event_count = lengthof(CeruleanGym_ObjectEvents),
    .obj_events = CeruleanGym_ObjectEvents,
};

//// CODE

bool CeruleanGym_MapScripts_DummyScene0(script_s* s) {
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}
bool CeruleanGym_MapScripts_GruntRunsOut(script_s* s) {
    SCRIPT_BEGIN
    sdefer(CeruleanGym_MapScripts_GruntRunsOutScript);
    s_end
    SCRIPT_END
}
bool CeruleanGym_MapScripts_GruntRunsOutScript(script_s* s) {
    SCRIPT_BEGIN
    applymovement(CERULEANGYM_ROCKET, CeruleanGymGruntRunsDownMovement)
    playsound(SFX_TACKLE)
    applymovement(CERULEANGYM_ROCKET, CeruleanGymGruntRunsIntoYouMovement)
    playmusic(MUSIC_ROCKET_ENCOUNTER)
    opentext
    writetext(CeruleanGymGruntIntroText)
    waitbutton
    closetext
    showemote(EMOTE_SHOCK, CERULEANGYM_ROCKET, 15)
    applymovement(CERULEANGYM_ROCKET, CeruleanGymGruntBacksAwayMovement)
    opentext
    writetext(CeruleanGymGruntBigMistakeText)
    waitbutton
    closetext
    applymovement(CERULEANGYM_ROCKET, CeruleanGymGruntMovesCloseMovement)
    opentext
    writetext(CeruleanGymGruntByeText)
    waitbutton
    closetext
    applymovement(CERULEANGYM_ROCKET, CeruleanGymGruntRunsOutMovement)
    playsound(SFX_EXIT_BUILDING)
    disappear(CERULEANGYM_ROCKET)
    setevent(EVENT_MET_ROCKET_GRUNT_AT_CERULEAN_GYM)
    clearevent(EVENT_ROUTE_24_ROCKET)
    clearevent(EVENT_ROUTE_25_MISTY_BOYFRIEND)
    setscene(SCENE_CERULEANGYM_NOTHING)
    setmapscene(ROUTE_25, SCENE_ROUTE25_MISTYS_DATE)
    setmapscene(POWER_PLANT, SCENE_POWERPLANT_NOTHING)
    waitsfx
    special(RestartMapMusic)
    pause(15)
    turnobject(PLAYER, DOWN)
    pause(15)
    s_end
    SCRIPT_END
}
bool CeruleanGymMistyScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkflag(ENGINE_CASCADEBADGE)
    iftrue(FightDone)
    writetext(MistyIntroText)
    waitbutton
    closetext
    winlosstext(MistyWinLossText, 0)
    loadtrainer(MISTY, MISTY1)
    startbattle
    reloadmapafterbattle
    setevent(EVENT_BEAT_MISTY)
    setevent(EVENT_BEAT_SWIMMERF_DIANA)
    setevent(EVENT_BEAT_SWIMMERF_BRIANA)
    setevent(EVENT_BEAT_SWIMMERM_PARKER)
    opentext
    writetext(ReceivedCascadeBadgeText)
    playsound(SFX_GET_BADGE)
    waitsfx
    setflag(ENGINE_CASCADEBADGE)
FightDone:
    writetext(MistyFightDoneText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerSwimmerfDiana = {SWIMMERF, DIANA, EVENT_BEAT_SWIMMERF_DIANA, SwimmerfDianaSeenText, SwimmerfDianaBeatenText, 0, TrainerSwimmerfDiana_Script};
bool TrainerSwimmerfDiana_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(SwimmerfDianaAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerSwimmerfBriana = {SWIMMERF, BRIANA, EVENT_BEAT_SWIMMERF_BRIANA, SwimmerfBrianaSeenText, SwimmerfBrianaBeatenText, 0, TrainerSwimmerfBriana_Script};
bool TrainerSwimmerfBriana_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(SwimmerfBrianaAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerSwimmermParker = {SWIMMERM, PARKER, EVENT_BEAT_SWIMMERM_PARKER, SwimmermParkerSeenText, SwimmermParkerBeatenText, 0, TrainerSwimmermParker_Script};
bool TrainerSwimmermParker_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(SwimmermParkerAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool CeruleanGymGuideScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_BEAT_MISTY)
    iftrue(CeruleanGymGuideWinScript)
    writetext(CeruleanGymGuideText)
    waitbutton
    closetext
    s_end
CeruleanGymGuideWinScript:
    writetext(CeruleanGymGuideWinText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct HiddenItem CeruleanGymHiddenMachinePart = {MACHINE_PART, EVENT_FOUND_MACHINE_PART_IN_CERULEAN_GYM};
bool CeruleanGymStatue1(script_s* s) {
    SCRIPT_BEGIN
    checkevent(EVENT_TRAINERS_IN_CERULEAN_GYM)
    iffalse_jump(CeruleanGymStatue)
    opentext
    writetext(CeruleanGymNote1Text)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool CeruleanGymStatue2(script_s* s) {
    SCRIPT_BEGIN
    checkevent(EVENT_TRAINERS_IN_CERULEAN_GYM)
    iffalse_jump(CeruleanGymStatue)
    opentext
    writetext(CeruleanGymNote2Text)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool CeruleanGymStatue(script_s* s) {
    SCRIPT_BEGIN
    checkflag(ENGINE_CASCADEBADGE)
    iftrue(Beaten)
    jumpstd(GymStatue1Script)
Beaten:
    gettrainername(STRING_BUFFER_4, MISTY, MISTY1)
    jumpstd(GymStatue2Script)
    SCRIPT_END
}
const uint8_t CeruleanGymGruntRunsDownMovement[] = {
    big_step(DOWN),
    big_step(DOWN),
    big_step(DOWN),
    big_step(DOWN),
    movement_step_end,
};
const uint8_t CeruleanGymGruntRunsOutMovement[] = {
    big_step(RIGHT),
    big_step(DOWN),
    movement_step_end,
};
const uint8_t CeruleanGymGruntRunsIntoYouMovement[] = {
    movement_fix_facing,
    movement_set_sliding,
    jump_step(UP),
    movement_remove_sliding,
    movement_remove_fixed_facing,
    step_sleep(8),
    step_sleep(8),
    step(DOWN),
    step(DOWN),
    movement_step_end,
};
const uint8_t CeruleanGymGruntMovesCloseMovement[] = {
    big_step(DOWN),
    movement_step_end,
};
const uint8_t CeruleanGymGruntBacksAwayMovement[] = {
    movement_fix_facing,
    slow_step(UP),
    movement_remove_fixed_facing,
    movement_step_end,
};
const txt_cmd_s CeruleanGymGruntIntroText[] = {
    text_start("Oops! I so sorry!"
        t_line "You not hurt,"
        t_cont "okay?"
        t_para "I very busy."
        t_line "No time for talk-"
        t_cont "ing with you. Not"
        t_cont "good for me if"
        t_cont "seen by somebody."
        t_done )
};
const txt_cmd_s CeruleanGymGruntBigMistakeText[] = {
    text_start("Oh no! You seen"
        t_line "me already! I make"
        t_cont "big mistake!"
        t_done )
};
const txt_cmd_s CeruleanGymGruntByeText[] = {
    text_start("Hey, you! Forget"
        t_line "you see me, okay?"
        t_para "You see, hear,"
        t_line "know nothing,"
        t_para "okay?"
        t_line "Bye, kid! Nothing!"
        t_para "Bye-bye a go-go!"
        t_done )
};
const txt_cmd_s CeruleanGymNote1Text[] = {
    text_start("Sorry, I'll be out"
        t_line "for a while."
        t_cont "MISTY, GYM LEADER"
        t_done )
};
const txt_cmd_s CeruleanGymNote2Text[] = {
    text_start("Since MISTY's out,"
        t_line "we'll be away too."
        t_cont "GYM TRAINERS"
        t_done )
};
const txt_cmd_s MistyIntroText[] = {
    text_start("MISTY: I was ex-"
        t_line "pecting you, you"
        t_cont "pest!"
        t_para "You may have a"
        t_line "lot of JOHTO GYM"
        t_para "BADGES, but you'd"
        t_line "better not take me"
        t_cont "too lightly."
        t_para "My water-type"
        t_line "#MON are tough!"
        t_done )
};
const txt_cmd_s MistyWinLossText[] = {
    text_start("MISTY: You really"
        t_line "are good…"
        t_para "I'll admit that"
        t_line "you are skilled…"
        t_para "Here you go. It's"
        t_line "CASCADEBADGE."
        t_done )
};
const txt_cmd_s ReceivedCascadeBadgeText[] = {
    text_start("<PLAYER> received"
        t_line "CASCADEBADGE."
        t_done )
};
const txt_cmd_s MistyFightDoneText[] = {
    text_start("MISTY: Are there"
        t_line "many strong train-"
        t_cont "ers in JOHTO? Like"
        t_cont "you, I mean."
        t_para "I'm going to"
        t_line "travel one day, so"
        t_para "I can battle some"
        t_line "skilled trainers."
        t_done )
};
const txt_cmd_s SwimmerfDianaSeenText[] = {
    text_start("Sorry about being"
        t_line "away. Let's get on"
        t_cont "with it!"
        t_done )
};
const txt_cmd_s SwimmerfDianaBeatenText[] = {
    text_start("I give up! You're"
        t_line "the winner!"
        t_done )
};
const txt_cmd_s SwimmerfDianaAfterBattleText[] = {
    text_start("I'll be swimming"
        t_line "quietly."
        t_done )
};
const txt_cmd_s SwimmerfBrianaSeenText[] = {
    text_start("Don't let my ele-"
        t_line "gant swimming un-"
        t_cont "nerve you."
        t_done )
};
const txt_cmd_s SwimmerfBrianaBeatenText[] = {
    text_start("Ooh, you calmly"
        t_line "disposed of me…"
        t_done )
};
const txt_cmd_s SwimmerfBrianaAfterBattleText[] = {
    text_start("Don't be too smug"
        t_line "about beating me."
        t_para "MISTY will destroy"
        t_line "you if you get"
        t_cont "complacent."
        t_done )
};
const txt_cmd_s SwimmermParkerSeenText[] = {
    text_start("Glub…"
        t_para "I'm first! Come"
        t_line "and get me!"
        t_done )
};
const txt_cmd_s SwimmermParkerBeatenText[] = {
    text_start("This can't be…"
        t_done )
};
const txt_cmd_s SwimmermParkerAfterBattleText[] = {
    text_start("MISTY has gotten"
        t_line "much better in the"
        t_cont "past few years."
        t_para "Don't let your"
        t_line "guard down, or"
        t_cont "you'll be crushed!"
        t_done )
};
const txt_cmd_s CeruleanGymGuideText[] = {
    text_start("Yo! CHAMP in"
        t_line "making!"
        t_para "Since MISTY was"
        t_line "away, I went out"
        t_para "for some fun too."
        t_line "He-he-he."
        t_done )
};
const txt_cmd_s CeruleanGymGuideWinText[] = {
    text_start("Hoo, you showed me"
        t_line "how tough you are."
        t_para "As always, that"
        t_line "was one heck of a"
        t_cont "great battle!"
        t_done )
    //db(0, 0) // filler
};
