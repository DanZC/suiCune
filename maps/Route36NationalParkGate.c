#include "../constants.h"
#include "../util/scripting.h"
#include "Route36NationalParkGate.h"
#include "Route35NationalParkGate.h"
//// EVENTS
enum {
    ROUTE36NATIONALPARKGATE_OFFICER1 = 2,
    ROUTE36NATIONALPARKGATE_YOUNGSTER1,
    ROUTE36NATIONALPARKGATE_YOUNGSTER2,
    ROUTE36NATIONALPARKGATE_ROCKER,
    ROUTE36NATIONALPARKGATE_POKEFAN_M,
    ROUTE36NATIONALPARKGATE_YOUNGSTER3,
    ROUTE36NATIONALPARKGATE_YOUNGSTER4,
    ROUTE36NATIONALPARKGATE_LASS,
    ROUTE36NATIONALPARKGATE_YOUNGSTER5,
    ROUTE36NATIONALPARKGATE_YOUNGSTER6,
    ROUTE36NATIONALPARKGATE_YOUNGSTER7,
    ROUTE36NATIONALPARKGATE_OFFICER2,
};

const Script_fn_t Route36NationalParkGate_SceneScripts[] = {
    Route36NationalParkGate_MapScripts_DummyScene0 , //  SCENE_ROUTE36NATIONALPARKGATE_NOTHING,
    Route36NationalParkGate_MapScripts_DummyScene1 , //  SCENE_ROUTE36NATIONALPARKGATE_UNUSED,
    Route36NationalParkGate_MapScripts_LeaveContestEarly , //  SCENE_ROUTE36NATIONALPARKGATE_LEAVE_CONTEST_EARLY,
};

const struct MapCallback Route36NationalParkGate_MapCallbacks[] = {
    map_callback(MAPCALLBACK_NEWMAP, Route36NationalParkGate_MapScripts_CheckIfContestRunning),
    map_callback(MAPCALLBACK_OBJECTS, Route36NationalParkGate_MapScripts_CheckIfContestAvailable),
};

const struct MapScripts Route36NationalParkGate_MapScripts = {
    .scene_script_count = lengthof(Route36NationalParkGate_SceneScripts),
    .scene_scripts = Route36NationalParkGate_SceneScripts,

    .callback_count = lengthof(Route36NationalParkGate_MapCallbacks),
    .callbacks = Route36NationalParkGate_MapCallbacks,
};

static const struct CoordEvent Route36NationalParkGate_CoordEvents[] = {
    0,
};

static const struct BGEvent Route36NationalParkGate_BGEvents[] = {
    bg_event(6, 0, BGEVENT_READ, &BugCatchingContestExplanationSign),
};

static const struct WarpEventData Route36NationalParkGate_WarpEvents[] = {
    warp_event(0, 4, NATIONAL_PARK, 1),
    warp_event(0, 5, NATIONAL_PARK, 2),
    warp_event(9, 4, ROUTE_36, 1),
    warp_event(9, 5, ROUTE_36, 2),
};

static const struct ObjEvent Route36NationalParkGate_ObjectEvents[] = {
    object_event(0, 3, SPRITE_OFFICER, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &Route36OfficerScriptContest, EVENT_ROUTE_36_NATIONAL_PARK_GATE_OFFICER_CONTEST_DAY),
    object_event(2, 5, SPRITE_YOUNGSTER, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &BugCatchingContestant1BScript, EVENT_BUG_CATCHING_CONTESTANT_1B),
    object_event(4, 5, SPRITE_YOUNGSTER, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &BugCatchingContestant2BScript, EVENT_BUG_CATCHING_CONTESTANT_2B),
    object_event(2, 6, SPRITE_ROCKER, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &BugCatchingContestant3BScript, EVENT_BUG_CATCHING_CONTESTANT_3B),
    object_event(6, 5, SPRITE_POKEFAN_M, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, PAL_NPC_BROWN, OBJECTTYPE_SCRIPT, 0, &BugCatchingContestant4BScript, EVENT_BUG_CATCHING_CONTESTANT_4B),
    object_event(2, 7, SPRITE_YOUNGSTER, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &BugCatchingContestant5BScript, EVENT_BUG_CATCHING_CONTESTANT_5B),
    object_event(5, 6, SPRITE_YOUNGSTER, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &BugCatchingContestant6BScript, EVENT_BUG_CATCHING_CONTESTANT_6B),
    object_event(3, 6, SPRITE_LASS, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &BugCatchingContestant7BScript, EVENT_BUG_CATCHING_CONTESTANT_7B),
    object_event(4, 7, SPRITE_YOUNGSTER, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &BugCatchingContestant8BScript, EVENT_BUG_CATCHING_CONTESTANT_8B),
    object_event(6, 7, SPRITE_YOUNGSTER, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &BugCatchingContestant9BScript, EVENT_BUG_CATCHING_CONTESTANT_9B),
    object_event(6, 6, SPRITE_YOUNGSTER, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &BugCatchingContestant10BScript, EVENT_BUG_CATCHING_CONTESTANT_10B),
    object_event(3, 2, SPRITE_OFFICER, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &Route36NationalParkGateOfficerScript, EVENT_ROUTE_36_NATIONAL_PARK_GATE_OFFICER_NOT_CONTEST_DAY),
};

const struct MapEvents Route36NationalParkGate_MapEvents = {
    .warp_event_count = lengthof(Route36NationalParkGate_WarpEvents),
    .warp_events = Route36NationalParkGate_WarpEvents,

    .coord_event_count = 0, // lengthof(Route36NationalParkGate_CoordEvents),
    .coord_events = Route36NationalParkGate_CoordEvents,

    .bg_event_count = lengthof(Route36NationalParkGate_BGEvents),
    .bg_events = Route36NationalParkGate_BGEvents,

    .obj_event_count = lengthof(Route36NationalParkGate_ObjectEvents),
    .obj_events = Route36NationalParkGate_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "Route36NationalParkGate.h"

bool Route36NationalParkGate_MapScripts_DummyScene0(script_s* s) {
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}
bool Route36NationalParkGate_MapScripts_DummyScene1(script_s* s) {
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}
bool Route36NationalParkGate_MapScripts_LeaveContestEarly(script_s* s) {
    SCRIPT_BEGIN
    sdefer(Route36NationalParkGate_MapScripts_LeavingContestEarly);
    s_end
    SCRIPT_END
}
bool Route36NationalParkGate_MapScripts_CheckIfContestRunning(script_s* s) {
    SCRIPT_BEGIN
    checkflag(ENGINE_BUG_CONTEST_TIMER)
    iftrue(BugContestIsRunning)
    setscene(SCENE_ROUTE36NATIONALPARKGATE_NOTHING)
    s_endcallback
BugContestIsRunning:
    setscene(SCENE_ROUTE36NATIONALPARKGATE_LEAVE_CONTEST_EARLY)
    s_endcallback
    SCRIPT_END
}
bool Route36NationalParkGate_MapScripts_CheckIfContestAvailable(script_s* s) {
    SCRIPT_BEGIN
    checkevent(EVENT_WARPED_FROM_ROUTE_35_NATIONAL_PARK_GATE)
    iftrue(Return)
    readvar(VAR_WEEKDAY)
    ifequal(TUESDAY, SetContestOfficer)
    ifequal(THURSDAY, SetContestOfficer)
    ifequal(SATURDAY, SetContestOfficer)
    checkflag(ENGINE_BUG_CONTEST_TIMER)
    iftrue(SetContestOfficer)
    disappear(ROUTE36NATIONALPARKGATE_OFFICER1)
    appear(ROUTE36NATIONALPARKGATE_OFFICER2)
    s_endcallback
SetContestOfficer:
    appear(ROUTE36NATIONALPARKGATE_OFFICER1)
    disappear(ROUTE36NATIONALPARKGATE_OFFICER2)
Return:
    s_endcallback
    SCRIPT_END
}
bool Route36NationalParkGate_MapScripts_LeavingContestEarly(script_s* s) {
    SCRIPT_BEGIN
    turnobject(PLAYER, UP)
    opentext
    readvar(VAR_CONTESTMINUTES)
    addval(1)
    getnum(STRING_BUFFER_3)
    writetext(Route36NationalParkGateOfficer1WantToFinishText)
    yesorno
    iffalse_jump(Route36NationalParkGate_MapScripts_GoBackToContest)
    writetext(Route36NationalParkGateOfficer1WaitHereForAnnouncementText)
    waitbutton
    closetext
    special(FadeBlackQuickly)
    special(ReloadSpritesNoPalettes)
    scall(Route36NationalParkGate_MapScripts_CopyContestants);
    disappear(ROUTE36NATIONALPARKGATE_OFFICER1)
    appear(ROUTE36NATIONALPARKGATE_OFFICER2)
    applymovement(PLAYER, Route36NationalParkGatePlayerWaitWithContestantsMovement)
    pause(15)
    special(FadeInQuickly)
    jumpstd(BugContestResultsScript)
    SCRIPT_END
}
bool Route36NationalParkGate_MapScripts_GoBackToContest(script_s* s) {
    SCRIPT_BEGIN
    writetext(Route36NationalParkGateOfficer1OkGoFinishText)
    waitbutton
    closetext
    turnobject(PLAYER, LEFT)
    playsound(SFX_EXIT_BUILDING)
    special(FadeOutPalettes)
    waitsfx
    warpfacing(LEFT, NATIONAL_PARK_BUG_CONTEST, 33, 18)
    s_end
    SCRIPT_END
}
bool Route36NationalParkGate_MapScripts_CopyContestants(script_s* s) {
    SCRIPT_BEGIN
    checkevent(EVENT_BUG_CATCHING_CONTESTANT_1A)
    iftrue(Not1)
    appear(ROUTE36NATIONALPARKGATE_YOUNGSTER1)
Not1:
    checkevent(EVENT_BUG_CATCHING_CONTESTANT_2A)
    iftrue(Not2)
    appear(ROUTE36NATIONALPARKGATE_YOUNGSTER2)
Not2:
    checkevent(EVENT_BUG_CATCHING_CONTESTANT_3A)
    iftrue(Not3)
    appear(ROUTE36NATIONALPARKGATE_ROCKER)
Not3:
    checkevent(EVENT_BUG_CATCHING_CONTESTANT_4A)
    iftrue(Not4)
    appear(ROUTE36NATIONALPARKGATE_POKEFAN_M)
Not4:
    checkevent(EVENT_BUG_CATCHING_CONTESTANT_5A)
    iftrue(Not5)
    appear(ROUTE36NATIONALPARKGATE_YOUNGSTER3)
Not5:
    checkevent(EVENT_BUG_CATCHING_CONTESTANT_6A)
    iftrue(Not6)
    appear(ROUTE36NATIONALPARKGATE_YOUNGSTER4)
Not6:
    checkevent(EVENT_BUG_CATCHING_CONTESTANT_7A)
    iftrue(Not7)
    appear(ROUTE36NATIONALPARKGATE_LASS)
Not7:
    checkevent(EVENT_BUG_CATCHING_CONTESTANT_8A)
    iftrue(Not8)
    appear(ROUTE36NATIONALPARKGATE_YOUNGSTER5)
Not8:
    checkevent(EVENT_BUG_CATCHING_CONTESTANT_9A)
    iftrue(Not9)
    appear(ROUTE36NATIONALPARKGATE_YOUNGSTER6)
Not9:
    checkevent(EVENT_BUG_CATCHING_CONTESTANT_10A)
    iftrue(Not10)
    appear(ROUTE36NATIONALPARKGATE_YOUNGSTER7)
Not10:
    special(UpdateSprites)
    s_end
    SCRIPT_END
}
bool Route36OfficerScriptContest(script_s* s) {
    SCRIPT_BEGIN
    readvar(VAR_WEEKDAY)
    ifequal_jump(SUNDAY, _ContestNotOn)
    ifequal_jump(MONDAY, _ContestNotOn)
    ifequal_jump(WEDNESDAY, _ContestNotOn)
    ifequal_jump(FRIDAY, _ContestNotOn)
    faceplayer
    opentext
    checkflag(ENGINE_DAILY_BUG_CONTEST)
    iftrue_jump(Route36Officer_ContestHasConcluded)
    scall(Route36ParkGate_DayToText)
    writetext(Route36NationalParkGateOfficer1AskToParticipateText)
    yesorno
    iffalse(DecidedNotToJoinContest)
    readvar(VAR_PARTYCOUNT)
    ifgreater(1, LeaveMonsWithOfficer)
    special(ContestDropOffMons)
    clearevent(EVENT_LEFT_MONS_WITH_CONTEST_OFFICER)
ResumeStartingContest:
    setflag(ENGINE_BUG_CONTEST_TIMER)
    special(PlayMapMusic)
    writetext(Route36NationalParkGateOfficer1GiveParkBallsText)
    promptbutton
    waitsfx
    writetext(Route36NationalParkGatePlayerReceivedParkBallsText)
    playsound(SFX_ITEM)
    waitsfx
    writetext(Route36NationalParkGateOfficer1ExplainsRulesText)
    waitbutton
    closetext
    setflag(ENGINE_BUG_CONTEST_TIMER)
    special(GiveParkBalls)
    turnobject(PLAYER, LEFT)
    playsound(SFX_EXIT_BUILDING)
    special(FadeOutPalettes)
    waitsfx
    special(SelectRandomBugContestContestants)
    warpfacing(LEFT, NATIONAL_PARK_BUG_CONTEST, 33, 18)
    s_end
LeaveMonsWithOfficer:
    readvar(VAR_PARTYCOUNT)
    ifless(PARTY_LENGTH, ContinueLeavingMons)
    readvar(VAR_BOXSPACE)
    ifequal(0, BoxFull)
ContinueLeavingMons:
    special(CheckFirstMonIsEgg)
    ifequal(TRUE, FirstMonIsEgg)
    writetext(Route36NationalParkGateOfficer1AskToUseFirstMonText)
    yesorno
    iffalse(RefusedToLeaveMons)
    special(ContestDropOffMons)
    iftrue(FirstMonIsFainted)
    setevent(EVENT_LEFT_MONS_WITH_CONTEST_OFFICER)
    writetext(Route36NationalParkGateOfficer1WellHoldYourMonText)
    promptbutton
    writetext(Route36NationalParkGatePlayersMonLeftWithHelperText)
    playsound(SFX_GOT_SAFARI_BALLS)
    waitsfx
    promptbutton
    goto ResumeStartingContest;
DecidedNotToJoinContest:
    writetext(Route36NationalParkGateOfficer1TakePartInFutureText)
    waitbutton
    closetext
    s_end
RefusedToLeaveMons:
    writetext(Route36NationalParkGateOfficer1ChooseMonAndComeBackText)
    waitbutton
    closetext
    s_end
FirstMonIsFainted:
    writetext(Route36NationalParkGateOfficer1FirstMonCantBattleText)
    waitbutton
    closetext
    s_end
BoxFull:
    writetext(Route36NationalParkGateOfficer1MakeRoomText)
    waitbutton
    closetext
    s_end
FirstMonIsEgg:
    writetext(Route36NationalParkGateOfficer1EggAsFirstMonText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool Route36Officer_ContestHasConcluded(script_s* s) {
    SCRIPT_BEGIN
    checkevent(EVENT_CONTEST_OFFICER_HAS_SUN_STONE)
    iftrue(Sunstone)
    checkevent(EVENT_CONTEST_OFFICER_HAS_EVERSTONE)
    iftrue(Everstone)
    checkevent(EVENT_CONTEST_OFFICER_HAS_GOLD_BERRY)
    iftrue(GoldBerry)
    checkevent(EVENT_CONTEST_OFFICER_HAS_BERRY)
    iftrue(Berry)
    writetext(Route36NationalParkGateOfficer1ContestIsOverText)
    waitbutton
    closetext
    s_end
Sunstone:
    writetext(Route36NationalParkGateOfficer1HeresThePrizeText)
    promptbutton
    verbosegiveitem(SUN_STONE, 1)
    iffalse(BagFull)
    clearevent(EVENT_CONTEST_OFFICER_HAS_SUN_STONE)
    closetext
    s_end
Everstone:
    writetext(Route36NationalParkGateOfficer1HeresThePrizeText)
    promptbutton
    verbosegiveitem(EVERSTONE, 1)
    iffalse(BagFull)
    clearevent(EVENT_CONTEST_OFFICER_HAS_EVERSTONE)
    closetext
    s_end
GoldBerry:
    writetext(Route36NationalParkGateOfficer1HeresThePrizeText)
    promptbutton
    verbosegiveitem(GOLD_BERRY, 1)
    iffalse(BagFull)
    clearevent(EVENT_CONTEST_OFFICER_HAS_GOLD_BERRY)
    closetext
    s_end
Berry:
    writetext(Route36NationalParkGateOfficer1HeresThePrizeText)
    promptbutton
    verbosegiveitem(BERRY, 1)
    iffalse(BagFull)
    clearevent(EVENT_CONTEST_OFFICER_HAS_BERRY)
    closetext
    s_end
BagFull:
    writetext(Route36NationalParkGateOfficer1WellHoldPrizeText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool _ContestNotOn(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(Route36NationalParkGateOfficer1SomeMonOnlySeenInParkText)
    SCRIPT_END
}
bool Route36NationalParkGateOfficerScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkflag(ENGINE_DAILY_BUG_CONTEST)
    iftrue_jump(Route36Officer_ContestHasConcluded)
    writetext(Route36NationalParkGateOfficer1SomeMonOnlySeenInParkText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool Route36ParkGate_DayToText(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(DayToTextScript)
    s_end
    SCRIPT_END
}
bool BugCatchingContestant1BScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_TEMPORARY_UNTIL_MAP_RELOAD_1)
    iffalse(StillCompeting)
    writetext(BugCatchingContestant1BText)
    waitbutton
    closetext
    s_end
StillCompeting:
    writetext(BugCatchingContestant1BStillCompetingText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool BugCatchingContestant2BScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_TEMPORARY_UNTIL_MAP_RELOAD_1)
    iffalse(StillCompeting)
    writetext(BugCatchingContestant2BText)
    waitbutton
    closetext
    s_end
StillCompeting:
    writetext(BugCatchingContestant2BStillCompetingText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool BugCatchingContestant3BScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_TEMPORARY_UNTIL_MAP_RELOAD_1)
    iffalse(StillCompeting)
    writetext(BugCatchingContestant3BText)
    waitbutton
    closetext
    s_end
StillCompeting:
    writetext(BugCatchingContestant3BStillCompetingText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool BugCatchingContestant4BScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_TEMPORARY_UNTIL_MAP_RELOAD_1)
    iffalse(StillCompeting)
    writetext(BugCatchingContestant4BText)
    waitbutton
    closetext
    s_end
StillCompeting:
    writetext(BugCatchingContestant4BStillCompetingText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool BugCatchingContestant5BScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_TEMPORARY_UNTIL_MAP_RELOAD_1)
    iffalse(StillCompeting)
    writetext(BugCatchingContestant5BText)
    waitbutton
    closetext
    s_end
StillCompeting:
    writetext(BugCatchingContestant5BStillCompetingText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool BugCatchingContestant6BScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_TEMPORARY_UNTIL_MAP_RELOAD_1)
    iffalse(StillCompeting)
    writetext(BugCatchingContestant6BText)
    waitbutton
    closetext
    s_end
StillCompeting:
    writetext(BugCatchingContestant6BStillCompetingText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool BugCatchingContestant7BScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_TEMPORARY_UNTIL_MAP_RELOAD_1)
    iffalse(StillCompeting)
    writetext(BugCatchingContestant7BText)
    waitbutton
    closetext
    s_end
StillCompeting:
    writetext(BugCatchingContestant7BStillCompetingText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool BugCatchingContestant8BScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_TEMPORARY_UNTIL_MAP_RELOAD_1)
    iffalse(StillCompeting)
    writetext(BugCatchingContestant8BText)
    waitbutton
    closetext
    s_end
StillCompeting:
    writetext(BugCatchingContestant8BStillCompetingText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool BugCatchingContestant9BScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_TEMPORARY_UNTIL_MAP_RELOAD_1)
    iffalse(StillCompeting)
    writetext(BugCatchingContestant9BText)
    waitbutton
    closetext
    s_end
StillCompeting:
    writetext(BugCatchingContestant9BStillCompetingText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool BugCatchingContestant10BScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_TEMPORARY_UNTIL_MAP_RELOAD_1)
    iffalse(StillCompeting)
    writetext(BugCatchingContestant10BText)
    waitbutton
    closetext
    s_end
StillCompeting:
    writetext(BugCatchingContestant10BStillCompetingText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool UnusedBugCatchingContestExplanationSign(script_s* s) {
    SCRIPT_BEGIN
// duplicate of BugCatchingContestExplanationSign in Route35NationalParkGate.asm
    jumptext(UnusedBugCatchingContestExplanationText)
    SCRIPT_END
}
const uint8_t Route36NationalParkGatePlayerWaitWithContestantsMovement[] = {
    big_step(DOWN),
    big_step(RIGHT),
    turn_head(UP),
    movement_step_end,
};
const txt_cmd_s Route36NationalParkGateOfficer1AskToParticipateText[] = {
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
const txt_cmd_s Route36NationalParkGateOfficer1GiveParkBallsText[] = {
    text_start("Here are the PARK"
        t_line "BALLS for the"
        t_cont "Contest."
        t_done )
};
const txt_cmd_s Route36NationalParkGatePlayerReceivedParkBallsText[] = {
    text_start("<PLAYER> received"
        t_line _s(BUG_CONTEST_BALLS) " PARK BALLS."
        t_done )
};
const txt_cmd_s Route36NationalParkGateOfficer1ExplainsRulesText[] = {
    text_start("The person who"
        t_line "gets the strong-"
        t_cont "est bug #MON"
        t_cont "is the winner."
        t_para "You have " _s(BUG_CONTEST_MINUTES)
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
const txt_cmd_s Route36NationalParkGateOfficer1AskToUseFirstMonText[] = {
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
const txt_cmd_s Route36NationalParkGateOfficer1WellHoldYourMonText[] = {
    text_start("Fine, we'll hold"
        t_line "your other #MON"
        t_cont "while you compete."
        t_done )
};
const txt_cmd_s Route36NationalParkGatePlayersMonLeftWithHelperText[] = {
    text_start("<PLAYER>'s #MON"
        t_line "were left with the"
        t_cont "CONTEST HELPER."
        t_done )
};
const txt_cmd_s Route36NationalParkGateOfficer1ChooseMonAndComeBackText[] = {
    text_start("Please choose the"
        t_line "#MON to be used"
        t_para "in the Contest,"
        t_line "then come see me."
        t_done )
};
const txt_cmd_s Route36NationalParkGateOfficer1TakePartInFutureText[] = {
    text_start("OK. We hope you'll"
        t_line "take part in the"
        t_cont "future."
        t_done )
};
const txt_cmd_s Route36NationalParkGateOfficer1FirstMonCantBattleText[] = {
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
const txt_cmd_s Route36NationalParkGateOfficer1MakeRoomText[] = {
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
const txt_cmd_s Route36NationalParkGateOfficer1EggAsFirstMonText[] = {
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
const txt_cmd_s Route36NationalParkGateOfficer1WantToFinishText[] = {
    text_start("You still have @")
    text_ram(wram_ptr(wStringBuffer3))
    text_start(
        t_line "minute(s) left."
        t_para "Do you want to"
        t_line "finish now?"
        t_done )
};
const txt_cmd_s Route36NationalParkGateOfficer1WaitHereForAnnouncementText[] = {
    text_start("OK. Please wait"
        t_line "here for the"
        t_para "announcement of"
        t_line "the winners."
        t_done )
};
const txt_cmd_s Route36NationalParkGateOfficer1OkGoFinishText[] = {
    text_start("OK. Please go back"
        t_line "outside and finish"
        t_cont "up."
        t_done )
};
const txt_cmd_s Route36NationalParkGateOfficer1ContestIsOverText[] = {
    text_start("Today's Contest is"
        t_line "over. We hope you"
        t_para "will participate"
        t_line "in the future."
        t_done )
};
const txt_cmd_s Route36NationalParkGateOfficer1SomeMonOnlySeenInParkText[] = {
    text_start("Some #MON can"
        t_line "only be seen in"
        t_cont "the PARK."
        t_done )
};
const txt_cmd_s BugCatchingContestant1BText[] = {
    text_start("DON: Wow, you beat"
        t_line "me. You're pretty"
        t_cont "good."
        t_done )
};
const txt_cmd_s BugCatchingContestant1BStillCompetingText[] = {
    text_start("DON: Luck plays a"
        t_line "big part in this."
        t_para "You never know"
        t_line "what #MON will"
        t_cont "appear."
        t_done )
};
const txt_cmd_s BugCatchingContestant2BText[] = {
    text_start("ED: I envy you."
        t_line "I just couldn't"
        t_cont "do it this time."
        t_done )
};
const txt_cmd_s BugCatchingContestant2BStillCompetingText[] = {
    text_start("ED: Maybe you win"
        t_line "with big #MON?"
        t_done )
};
const txt_cmd_s BugCatchingContestant3BText[] = {
    text_start("NICK: Well done!"
        t_line "I'm going to raise"
        t_cont "my #MON better."
        t_done )
};
const txt_cmd_s BugCatchingContestant3BStillCompetingText[] = {
    text_start("NICK: Maybe you"
        t_line "get a higher score"
        t_para "for a #MON of"
        t_line "an unusual color."
        t_done )
};
const txt_cmd_s BugCatchingContestant4BText[] = {
    text_start("WILLIAM: You're"
        t_line "the winner? What"
        t_cont "did you catch?"
        t_done )
};
const txt_cmd_s BugCatchingContestant4BStillCompetingText[] = {
    text_start("WILLIAM: Well, I'm"
        t_line "satisfied because"
        t_para "I caught a #MON"
        t_line "that I wanted."
        t_done )
};
const txt_cmd_s BugCatchingContestant5BText[] = {
    text_start("BENNY: Congrats!"
        t_line "You have earned my"
        t_cont "respect!"
        t_done )
};
const txt_cmd_s BugCatchingContestant5BStillCompetingText[] = {
    text_start("BENNY: I caught a"
        t_line "SCYTHER before,"
        t_cont "but I didn't win."
        t_done )
};
const txt_cmd_s BugCatchingContestant6BText[] = {
    text_start("BARRY: That #-"
        t_line "MON you caught…"
        t_cont "it's awesome!"
        t_done )
};
const txt_cmd_s BugCatchingContestant6BStillCompetingText[] = {
    text_start("BARRY: It's easier"
        t_line "to win if you get"
        t_para "a high-level bug"
        t_line "#MON."
        t_para "But I think they"
        t_line "also consider some"
        t_cont "other points."
        t_done )
};
const txt_cmd_s BugCatchingContestant7BText[] = {
    text_start("CINDY: You won?"
        t_line "That's great!"
        t_para "Do you feel like"
        t_line "looking for bug"
        t_cont "#MON with me?"
        t_done )
};
const txt_cmd_s BugCatchingContestant7BStillCompetingText[] = {
    text_start("CINDY: I really"
        t_line "love bug #MON!"
        t_done )
};
const txt_cmd_s BugCatchingContestant8BText[] = {
    text_start("JOSH: I… I can't"
        t_line "believe I lost at"
        t_cont "bug-catching…"
        t_done )
};
const txt_cmd_s BugCatchingContestant8BStillCompetingText[] = {
    text_start("JOSH: I heard that"
        t_line "somebody won with"
        t_cont "a CATERPIE!"
        t_done )
};
const txt_cmd_s BugCatchingContestant9BText[] = {
    text_start("SAMUEL: Next time,"
        t_line "I'm going to win."
        t_done )
};
const txt_cmd_s BugCatchingContestant9BStillCompetingText[] = {
    text_start("SAMUEL: Darn."
        t_line "I thought I would"
        t_cont "score higher…"
        t_done )
};
const txt_cmd_s BugCatchingContestant10BText[] = {
    text_start("KIPP: Could you"
        t_line "give me some tips?"
        t_para "I want to study"
        t_line "your style."
        t_done )
};
const txt_cmd_s BugCatchingContestant10BStillCompetingText[] = {
    text_start("KIPP: I study a"
        t_line "lot, but that's"
        t_para "not good enough to"
        t_line "win."
        t_done )
};
// This text is referring to Sudowoodo.
// The SILPHSCOPE2 was later reworked into the SQUIRTBOTTLE.
const txt_cmd_s UnusedSilphScope2Text[] = {
    text_start("I hear there's a"
        t_line "#MON that looks"
        t_cont "just like a tree."
        t_para "You can reveal its"
        t_line "identity using a"
        t_cont "SILPHSCOPE 2."
        t_done )
};
// duplicate of BugCatchingContestExplanationText in Route35NationalParkGate.asm
const txt_cmd_s UnusedBugCatchingContestExplanationText[] = {
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
};
const txt_cmd_s Route36NationalParkGateOfficer1WellHoldPrizeText[] = {
    text_start("Uh-oh… Your PACK"
        t_line "is full."
        t_para "We'll hold on to"
        t_line "your prize, but"
        t_cont "only for today."
        t_para "Please make room,"
        t_line "then come see me."
        t_done )
};
const txt_cmd_s Route36NationalParkGateOfficer1HeresThePrizeText[] = {
    text_start("<PLAYER>?"
        t_para "Here's the prize"
        t_line "we were holding"
        t_cont "for you."
        t_done )
    //db(0, 0) // filler
};
