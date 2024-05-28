#include "../constants.h"
#include "../util/scripting.h"
#include "Route35NationalParkGate.h"
//// EVENTS
enum {
    ROUTE35NATIONALPARKGATE_OFFICER1 = 2,
    ROUTE35NATIONALPARKGATE_YOUNGSTER,
    ROUTE35NATIONALPARKGATE_OFFICER2,
};

const Script_fn_t Route35NationalParkGate_SceneScripts[] = {
    Route35NationalParkGate_MapScripts_DummyScene0 , //  SCENE_ROUTE35NATIONALPARKGATE_NOTHING,
    Route35NationalParkGate_MapScripts_DummyScene1 , //  SCENE_ROUTE35NATIONALPARKGATE_UNUSED,
    Route35NationalParkGate_MapScripts_LeaveContestEarly , //  SCENE_ROUTE35NATIONALPARKGATE_LEAVE_CONTEST_EARLY,
};

const struct MapCallback Route35NationalParkGate_MapCallbacks[] = {
    map_callback(MAPCALLBACK_NEWMAP, Route35NationalParkGate_MapScripts_CheckIfContestRunning),
    map_callback(MAPCALLBACK_OBJECTS, Route35NationalParkGate_MapScripts_CheckIfContestAvailable),
};

const struct MapScripts Route35NationalParkGate_MapScripts = {
    .scene_script_count = lengthof(Route35NationalParkGate_SceneScripts),
    .scene_scripts = Route35NationalParkGate_SceneScripts,

    .callback_count = lengthof(Route35NationalParkGate_MapCallbacks),
    .callbacks = Route35NationalParkGate_MapCallbacks,
};

static const struct CoordEvent Route35NationalParkGate_CoordEvents[] = {
    0,
};

static const struct BGEvent Route35NationalParkGate_BGEvents[] = {
    bg_event(5, 0, BGEVENT_READ, &BugCatchingContestExplanationSign),
};

static const struct WarpEventData Route35NationalParkGate_WarpEvents[] = {
    warp_event(3, 0, NATIONAL_PARK, 3),
    warp_event(4, 0, NATIONAL_PARK, 4),
    warp_event(3, 7, ROUTE_35, 3),
    warp_event(4, 7, ROUTE_35, 3),
};

static const struct ObjEvent Route35NationalParkGate_ObjectEvents[] = {
    object_event(2, 1, SPRITE_OFFICER, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &Route35OfficerScriptContest, EVENT_ROUTE_35_NATIONAL_PARK_GATE_OFFICER_CONTEST_DAY),
    object_event(6, 5, SPRITE_YOUNGSTER, SPRITEMOVEDATA_WANDER, 1, 1, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &Route35NationalParkGateYoungsterScript, EVENT_ROUTE_35_NATIONAL_PARK_GATE_YOUNGSTER),
    object_event(0, 3, SPRITE_OFFICER, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &Route35NationalParkGateOfficerScript, EVENT_ROUTE_35_NATIONAL_PARK_GATE_OFFICER_NOT_CONTEST_DAY),
};

const struct MapEvents Route35NationalParkGate_MapEvents = {
    .warp_event_count = lengthof(Route35NationalParkGate_WarpEvents),
    .warp_events = Route35NationalParkGate_WarpEvents,

    .coord_event_count = 0, // lengthof(Route35NationalParkGate_CoordEvents),
    .coord_events = Route35NationalParkGate_CoordEvents,

    .bg_event_count = lengthof(Route35NationalParkGate_BGEvents),
    .bg_events = Route35NationalParkGate_BGEvents,

    .obj_event_count = lengthof(Route35NationalParkGate_ObjectEvents),
    .obj_events = Route35NationalParkGate_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "Route35NationalParkGate.h"

bool Route35NationalParkGate_MapScripts_DummyScene0(script_s* s) {
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}
bool Route35NationalParkGate_MapScripts_DummyScene1(script_s* s) {
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}
bool Route35NationalParkGate_MapScripts_LeaveContestEarly(script_s* s) {
    SCRIPT_BEGIN
    sdefer(Route35NationalParkGate_MapScripts_LeavingContestEarly2);
    s_end
    SCRIPT_END
}
bool Route35NationalParkGate_MapScripts_CheckIfContestRunning(script_s* s) {
    SCRIPT_BEGIN
    checkflag(ENGINE_BUG_CONTEST_TIMER)
    iftrue_jump(Route35NationalParkGate_MapScripts_BugContestIsRunning)
    setscene(SCENE_ROUTE35NATIONALPARKGATE_NOTHING)
    s_endcallback
    SCRIPT_END
}
bool Route35NationalParkGate_MapScripts_BugContestIsRunning(script_s* s) {
    SCRIPT_BEGIN
    setscene(SCENE_ROUTE35NATIONALPARKGATE_LEAVE_CONTEST_EARLY)
    s_endcallback
    SCRIPT_END
}
bool Route35NationalParkGate_MapScripts_CheckIfContestAvailable(script_s* s) {
    SCRIPT_BEGIN
    readvar(VAR_WEEKDAY)
    ifequal(TUESDAY, SetContestOfficer)
    ifequal(THURSDAY, SetContestOfficer)
    ifequal(SATURDAY, SetContestOfficer)
    checkflag(ENGINE_BUG_CONTEST_TIMER)
    iftrue_jump(Route35NationalParkGate_MapScripts_BugContestIsRunning)
    disappear(ROUTE35NATIONALPARKGATE_OFFICER1)
    appear(ROUTE35NATIONALPARKGATE_YOUNGSTER)
    appear(ROUTE35NATIONALPARKGATE_OFFICER2)
    s_endcallback
SetContestOfficer:
    appear(ROUTE35NATIONALPARKGATE_OFFICER1)
    disappear(ROUTE35NATIONALPARKGATE_YOUNGSTER)
    disappear(ROUTE35NATIONALPARKGATE_OFFICER2)
    s_endcallback
    SCRIPT_END
}
bool Route35NationalParkGate_MapScripts_LeavingContestEarly2(script_s* s) {
    SCRIPT_BEGIN
    applymovement(PLAYER, Route35NationalParkGatePlayerApproachOfficer1Movement)
    turnobject(ROUTE35NATIONALPARKGATE_OFFICER1, RIGHT)
    opentext
    readvar(VAR_CONTESTMINUTES)
    addval(1)
    getnum(STRING_BUFFER_3)
    writetext(Route35NationalParkGateOfficer1WantToFinishText)
    yesorno
    iffalse(GoBackToContest)
    writetext(Route35NationalParkGateOfficer1WaitAtNorthGateText)
    waitbutton
    closetext
    jumpstd(BugContestResultsWarpScript)
GoBackToContest:
    writetext(Route35NationalParkGateOfficer1OkGoFinishText)
    waitbutton
    closetext
    scall(Route35NationalParkGate_EnterContest)
    playsound(SFX_ENTER_DOOR)
    special(FadeOutPalettes)
    waitsfx
    warpfacing(UP, NATIONAL_PARK_BUG_CONTEST, 10, 47)
    s_end
    SCRIPT_END
}
bool Route35OfficerScriptContest(script_s* s) {
    SCRIPT_BEGIN
    readvar(VAR_WEEKDAY)
    ifequal_jump(SUNDAY, Route35NationalParkGate_NoContestToday)
    ifequal_jump(MONDAY, Route35NationalParkGate_NoContestToday)
    ifequal_jump(WEDNESDAY, Route35NationalParkGate_NoContestToday)
    ifequal_jump(FRIDAY, Route35NationalParkGate_NoContestToday)
    faceplayer
    opentext
    checkflag(ENGINE_DAILY_BUG_CONTEST)
    iftrue_jump(Route35NationalParkGate_ContestIsOver)
    scall(Route35NationalParkGate_GetDayOfWeek)
    writetext(Route35NationalParkGateOfficer1AskToParticipateText)
    yesorno
    iffalse_jump(Route35NationalParkGate_DeclinedToParticipate)
    readvar(VAR_PARTYCOUNT)
    ifgreater_jump(1, Route35NationalParkGate_LeaveTheRestBehind)
    special(ContestDropOffMons)
    clearevent(EVENT_LEFT_MONS_WITH_CONTEST_OFFICER)
    SCRIPT_FALLTHROUGH(Route35NationalParkGate_OkayToProceed)
}
bool Route35NationalParkGate_OkayToProceed(script_s* s) {
    SCRIPT_BEGIN
    setflag(ENGINE_BUG_CONTEST_TIMER)
    special(PlayMapMusic)
    writetext(Route35NationalParkGateOfficer1GiveParkBallsText)
    promptbutton
    writetext(Route35NationalParkGatePlayerReceivedParkBallsText)
    playsound(SFX_ITEM)
    waitsfx
    writetext(Route35NationalParkGateOfficer1ExplainsRulesText)
    waitbutton
    closetext
    special(GiveParkBalls)
    scall(Route35NationalParkGate_EnterContest)
    playsound(SFX_ENTER_DOOR)
    special(FadeOutPalettes)
    waitsfx
    special(SelectRandomBugContestContestants)
    warpfacing(UP, NATIONAL_PARK_BUG_CONTEST, 10, 47)
    s_end
    SCRIPT_END
}
bool Route35NationalParkGate_EnterContest(script_s* s) {
    SCRIPT_BEGIN
    readvar(VAR_FACING)
    ifequal_jump(LEFT, Route35NationalParkGate_FacingLeft)
    applymovement(PLAYER, Route35NationalParkGatePlayerGoAroundOfficerAndEnterParkMovement)
    s_end
    SCRIPT_END
}
bool Route35NationalParkGate_FacingLeft(script_s* s) {
    SCRIPT_BEGIN
    applymovement(PLAYER, Route35NationalParkGatePlayerEnterParkMovement)
    s_end
    SCRIPT_END
}
bool Route35NationalParkGate_LeaveTheRestBehind(script_s* s) {
    SCRIPT_BEGIN
    readvar(VAR_PARTYCOUNT)
    ifless_jump(PARTY_LENGTH, Route35NationalParkGate_LessThanFullParty)
    readvar(VAR_BOXSPACE)
    ifequal_jump(0, Route35NationalParkGate_NoRoomInBox)
    SCRIPT_FALLTHROUGH(Route35NationalParkGate_LessThanFullParty)
}
bool Route35NationalParkGate_LessThanFullParty(script_s* s) {
    SCRIPT_BEGIN
    special(CheckFirstMonIsEgg)
    ifequal_jump(TRUE, Route35NationalParkGate_FirstMonIsEgg)
    writetext(Route35NationalParkGateOfficer1AskToUseFirstMonText)
    yesorno
    iffalse_jump(Route35NationalParkGate_DeclinedToLeaveMonsBehind)
    special(ContestDropOffMons)
    iftrue_jump(Route35NationalParkGate_FirstMonIsFainted)
    setevent(EVENT_LEFT_MONS_WITH_CONTEST_OFFICER)
    writetext(Route35NationalParkGateOfficer1WellHoldYourMonText)
    promptbutton
    writetext(Route35NationalParkGatePlayersMonLeftWithHelperText)
    playsound(SFX_GOT_SAFARI_BALLS)
    waitsfx
    promptbutton
    sjump(Route35NationalParkGate_OkayToProceed)
    SCRIPT_END
}
bool Route35NationalParkGate_DeclinedToParticipate(script_s* s) {
    SCRIPT_BEGIN
    writetext(Route35NationalParkGateOfficer1TakePartInFutureText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool Route35NationalParkGate_DeclinedToLeaveMonsBehind(script_s* s) {
    SCRIPT_BEGIN
    writetext(Route35NationalParkGateOfficer1ChooseMonAndComeBackText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool Route35NationalParkGate_FirstMonIsFainted(script_s* s) {
    SCRIPT_BEGIN
    writetext(Route35NationalParkGateOfficer1FirstMonCantBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool Route35NationalParkGate_NoRoomInBox(script_s* s) {
    SCRIPT_BEGIN
    writetext(Route35NationalParkGateOfficer1MakeRoomText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool Route35NationalParkGate_FirstMonIsEgg(script_s* s) {
    SCRIPT_BEGIN
    writetext(Route35NationalParkGateOfficer1EggAsFirstMonText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool Route35NationalParkGate_ContestIsOver(script_s* s) {
    SCRIPT_BEGIN
    writetext(Route35NationalParkGateOfficer1ContestIsOverText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool Route35NationalParkGate_NoContestToday(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(Route35NationalParkGateOfficer1WeHoldContestsText)
    SCRIPT_END
}
bool Route35NationalParkGateOfficerScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkflag(ENGINE_DAILY_BUG_CONTEST)
    iftrue_jump(Route35NationalParkGate_ContestIsOver)
    writetext(Route35NationalParkGateOfficer1WeHoldContestsText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool Route35NationalParkGateYoungsterScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(Route35NationalParkGateYoungsterText)
    SCRIPT_END
}
bool BugCatchingContestExplanationSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(BugCatchingContestExplanationText)
    SCRIPT_END
}
bool Route35NationalParkGate_GetDayOfWeek(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(DayToTextScript)
    s_end
    SCRIPT_END
}
const uint8_t Route35NationalParkGatePlayerApproachOfficer1Movement[] = {
    step(DOWN),
    turn_head(LEFT),
    movement_step_end,
};
const uint8_t Route35NationalParkGatePlayerGoAroundOfficerAndEnterParkMovement[] = {
    step(RIGHT),
    step(UP),
    step(UP),
    movement_step_end,
};
const uint8_t Route35NationalParkGatePlayerEnterParkMovement[] = {
    step(UP),
    movement_step_end,
};
const txt_cmd_s Route35NationalParkGateOfficer1AskToParticipateText[] = {
    text_start("Today's @")
    text_ram(wram_ptr(wStringBuffer3))
    text_start("."
        t_line "That means the"
        t_para "Bug-Catching Con-"
        t_line "test is on today."
        t_para "The rules are sim-"
        t_line "ple."
        t_para "Using one of your"
        t_line "#MON, catch a"
        t_para "bug #MON to be"
        t_line "judged."
        t_para "Would you like to"
        t_line "give it a try?"
        t_done )
};
const txt_cmd_s Route35NationalParkGateOfficer1GiveParkBallsText[] = {
    text_start("Here are the PARK"
        t_line "BALLS for the"
        t_cont "Contest."
        t_done )
};
const txt_cmd_s Route35NationalParkGatePlayerReceivedParkBallsText[] = {
    text_start("<PLAYER> received"
        t_line "{d:BUG_CONTEST_BALLS} PARK BALLS."
        t_done )
};
const txt_cmd_s Route35NationalParkGateOfficer1ExplainsRulesText[] = {
    text_start("The person who"
        t_line "gets the strong-"
        t_cont "est bug #MON"
        t_cont "is the winner."
        t_para "You have {d:BUG_CONTEST_MINUTES}"
        t_line "minutes."
        t_para "If you run out of"
        t_line "PARK BALLS, you're"
        t_cont "done."
        t_para "You can keep the"
        t_line "last #MON you"
        t_cont "catch as your own."
        t_para "Go out and catch"
        t_line "the strongest bug"
        t_para "#MON you can"
        t_line "find!"
        t_done )
};
const txt_cmd_s Route35NationalParkGateOfficer1AskToUseFirstMonText[] = {
    text_start("Uh-oh…"
        t_para "You have more than"
        t_line "one #MON."
        t_para "You'll have to use"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer3))
    text_start(", the"
        t_para "first #MON in"
        t_line "your party."
        t_para "Is that OK with"
        t_line "you?"
        t_done )
};
const txt_cmd_s Route35NationalParkGateOfficer1WellHoldYourMonText[] = {
    text_start("Fine, we'll hold"
        t_line "your other #MON"
        t_cont "while you compete."
        t_done )
};
const txt_cmd_s Route35NationalParkGatePlayersMonLeftWithHelperText[] = {
    text_start("<PLAYER>'s #MON"
        t_line "were left with the"
        t_cont "CONTEST HELPER."
        t_done )
};
const txt_cmd_s Route35NationalParkGateOfficer1ChooseMonAndComeBackText[] = {
    text_start("Please choose the"
        t_line "#MON to be used"
        t_para "in the Contest,"
        t_line "then come see me."
        t_done )
};
const txt_cmd_s Route35NationalParkGateOfficer1TakePartInFutureText[] = {
    text_start("OK. We hope you'll"
        t_line "take part in the"
        t_cont "future."
        t_done )
};
const txt_cmd_s Route35NationalParkGateOfficer1FirstMonCantBattleText[] = {
    text_start("Uh-oh…"
        t_line "The first #MON"
        t_para "in your party"
        t_line "can't battle."
        t_para "Please switch it"
        t_line "with the #MON"
        t_para "you want to use,"
        t_line "then come see me."
        t_done )
};
const txt_cmd_s Route35NationalParkGateOfficer1MakeRoomText[] = {
    text_start("Uh-oh…"
        t_line "Both your party"
        t_para "and your PC BOX"
        t_line "are full."
        t_para "You have no room"
        t_line "to put the bug"
        t_cont "#MON you catch."
        t_para "Please make room"
        t_line "in your party or"
        t_para "your PC BOX, then"
        t_line "come see me."
        t_done )
};
const txt_cmd_s Route35NationalParkGateOfficer1EggAsFirstMonText[] = {
    text_start("Uh-oh…"
        t_line "You have an EGG as"
        t_para "the first #MON"
        t_line "in your party."
        t_para "Please switch it"
        t_line "with the #MON"
        t_para "you want to use,"
        t_line "then come see me."
        t_done )
};
const txt_cmd_s Route35NationalParkGateOfficer1WantToFinishText[] = {
    text_start("You still have @")
    text_ram(wram_ptr(wStringBuffer3))
    text_start(
        t_line "minute(s) left."
        t_para "Do you want to"
        t_line "finish now?"
        t_done )
};
const txt_cmd_s Route35NationalParkGateOfficer1WaitAtNorthGateText[] = {
    text_start("OK. Please wait at"
        t_line "the North Gate for"
        t_para "the announcement"
        t_line "of the winners."
        t_done )
};
const txt_cmd_s Route35NationalParkGateOfficer1OkGoFinishText[] = {
    text_start("OK. Please get"
        t_line "back outside and"
        t_cont "finish up."
        t_done )
};
const txt_cmd_s Route35NationalParkGateOfficer1ContestIsOverText[] = {
    text_start("Today's Contest is"
        t_line "over. We hope you"
        t_para "will participate"
        t_line "in the future."
        t_done )
};
const txt_cmd_s Route35NationalParkGateOfficer1WeHoldContestsText[] = {
    text_start("We hold Contests"
        t_line "regularly in the"
        t_para "PARK. You should"
        t_line "give it a shot."
        t_done )
};
const txt_cmd_s Route35NationalParkGateYoungsterText[] = {
    text_start("When is the next"
        t_line "Bug-Catching Con-"
        t_cont "test going to be?"
        t_done )
};
const txt_cmd_s BugCatchingContestExplanationText[] = {
    text_start("The Bug-Catching"
        t_line "Contest is held on"
        t_para "Tuesday, Thursday"
        t_line "and Saturday."
        t_para "Not only do you"
        t_line "earn a prize just"
        t_para "for participating,"
        t_line "you also get to"
        t_para "keep the bug"
        t_line "#MON you may"
        t_para "have at the end of"
        t_line "the contest."
        t_done )
    //db(0, 0) // filler
};
