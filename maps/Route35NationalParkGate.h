#pragma once
//// EVENTS
extern const struct MapScripts Route35NationalParkGate_MapScripts;
extern const struct MapEvents Route35NationalParkGate_MapEvents;

//// CODE

bool Route35NationalParkGate_MapScripts_DummyScene0(script_s* s);
bool Route35NationalParkGate_MapScripts_DummyScene1(script_s* s);
bool Route35NationalParkGate_MapScripts_LeaveContestEarly(script_s* s);
bool Route35NationalParkGate_MapScripts_CheckIfContestRunning(script_s* s);
bool Route35NationalParkGate_MapScripts_BugContestIsRunning(script_s* s);
bool Route35NationalParkGate_MapScripts_CheckIfContestAvailable(script_s* s);
bool Route35NationalParkGate_MapScripts_LeavingContestEarly2(script_s* s);
bool Route35OfficerScriptContest(script_s* s);
bool Route35NationalParkGate_OkayToProceed(script_s* s);
bool Route35NationalParkGate_EnterContest(script_s* s);
bool Route35NationalParkGate_FacingLeft(script_s* s);
bool Route35NationalParkGate_LeaveTheRestBehind(script_s* s);
bool Route35NationalParkGate_LessThanFullParty(script_s* s);
bool Route35NationalParkGate_DeclinedToParticipate(script_s* s);
bool Route35NationalParkGate_DeclinedToLeaveMonsBehind(script_s* s);
bool Route35NationalParkGate_FirstMonIsFainted(script_s* s);
bool Route35NationalParkGate_NoRoomInBox(script_s* s);
bool Route35NationalParkGate_FirstMonIsEgg(script_s* s);
bool Route35NationalParkGate_ContestIsOver(script_s* s);
bool Route35NationalParkGate_NoContestToday(script_s* s);
bool Route35NationalParkGateOfficerScript(script_s* s);
bool Route35NationalParkGateYoungsterScript(script_s* s);
bool BugCatchingContestExplanationSign(script_s* s);
bool Route35NationalParkGate_GetDayOfWeek(script_s* s);
extern const uint8_t Route35NationalParkGatePlayerApproachOfficer1Movement[];
extern const uint8_t Route35NationalParkGatePlayerGoAroundOfficerAndEnterParkMovement[];
extern const uint8_t Route35NationalParkGatePlayerEnterParkMovement[];
extern const txt_cmd_s Route35NationalParkGateOfficer1AskToParticipateText[];
extern const txt_cmd_s Route35NationalParkGateOfficer1GiveParkBallsText[];
extern const txt_cmd_s Route35NationalParkGatePlayerReceivedParkBallsText[];
extern const txt_cmd_s Route35NationalParkGateOfficer1ExplainsRulesText[];
extern const txt_cmd_s Route35NationalParkGateOfficer1AskToUseFirstMonText[];
extern const txt_cmd_s Route35NationalParkGateOfficer1WellHoldYourMonText[];
extern const txt_cmd_s Route35NationalParkGatePlayersMonLeftWithHelperText[];
extern const txt_cmd_s Route35NationalParkGateOfficer1ChooseMonAndComeBackText[];
extern const txt_cmd_s Route35NationalParkGateOfficer1TakePartInFutureText[];
extern const txt_cmd_s Route35NationalParkGateOfficer1FirstMonCantBattleText[];
extern const txt_cmd_s Route35NationalParkGateOfficer1MakeRoomText[];
extern const txt_cmd_s Route35NationalParkGateOfficer1EggAsFirstMonText[];
extern const txt_cmd_s Route35NationalParkGateOfficer1WantToFinishText[];
extern const txt_cmd_s Route35NationalParkGateOfficer1WaitAtNorthGateText[];
extern const txt_cmd_s Route35NationalParkGateOfficer1OkGoFinishText[];
extern const txt_cmd_s Route35NationalParkGateOfficer1ContestIsOverText[];
extern const txt_cmd_s Route35NationalParkGateOfficer1WeHoldContestsText[];
extern const txt_cmd_s Route35NationalParkGateYoungsterText[];
extern const txt_cmd_s BugCatchingContestExplanationText[];
