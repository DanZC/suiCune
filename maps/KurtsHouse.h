#pragma once
//// EVENTS
extern const struct MapScripts KurtsHouse_MapScripts;
extern const struct MapEvents KurtsHouse_MapEvents;

//// CODE

bool KurtsHouse_MapScripts_KurtCallback(script_s* s);
bool KurtsHouse_MapScripts_MakingBalls(script_s* s);
bool KurtsHouse_MapScripts_Done(script_s* s);
bool Kurt1(script_s* s);
bool Kurt2(script_s* s);
bool KurtMakingBallsScript(script_s* s);
bool Script_FirstTimeBuggingKurt(script_s* s);
bool KurtScript_ImCheckingItNow(script_s* s);
bool KurtsGranddaughter1(script_s* s);
bool KurtsGranddaughter2(script_s* s);
bool KurtsGranddaughter2Subscript(script_s* s);
bool KurtsGranddaughterFunScript(script_s* s);
bool KurtsHouseSlowpoke(script_s* s);
bool KurtsHouseOakPhoto(script_s* s);
bool KurtsHouseCelebiStatue(script_s* s);
bool KurtsHouseBookshelf(script_s* s);
bool KurtsHouseRadio(script_s* s);
extern const uint8_t KurtsHouseKurtExitHouseMovement[];
extern const uint8_t KurtsHouseKurtGoAroundPlayerThenExitHouseMovement[];
extern const txt_cmd_s KurtsHouseKurtMakingBallsMustWaitText[];
extern const txt_cmd_s KurtsHouseKurtHonoredToMakeBallsText[];
extern const txt_cmd_s KurtsHouseKurtBallsFromApricornsText[];
extern const txt_cmd_s KurtsHouseKurtAskYouHaveAnApricornText[];
extern const txt_cmd_s KurtsHouseKurtItWillTakeADayText[];
extern const txt_cmd_s KurtsHouseKurtThatsALetdownText[];
extern const txt_cmd_s KurtsHouseKurtDontBotherMeText[];
extern const txt_cmd_s KurtsHouseKurtJustFinishedYourBallText[];
extern const txt_cmd_s KurtsHouseKurtTurnedOutGreatText[];
extern const txt_cmd_s KurtsHouseKurtGranddaughterHelpingWorkFasterText[];
extern const txt_cmd_s KurtsHouseKurtWhatIsThatText[];
extern const txt_cmd_s KurtsHouseKurtImCheckingItNowText[];
extern const txt_cmd_s KurtsHouseKurtAhHaISeeText[];
extern const txt_cmd_s KurtsHouseKurtThisBallStartedToShakeText[];
extern const txt_cmd_s KurtsGranddaughterSlowpokeGoneText[];
extern const txt_cmd_s KurtsGranddaughterLonelyText[];
extern const txt_cmd_s KurtsGranddaughterSlowpokeBackText[];
extern const txt_cmd_s KurtsGranddaughterDadText[];
extern const txt_cmd_s KurtsGranddaughterHelpText[];
extern const txt_cmd_s KurtsGranddaughterFunText[];
extern const txt_cmd_s KurtsGranddaughterGSBallText[];
extern const txt_cmd_s KurtsHouseSlowpokeText[];
extern const txt_cmd_s KurtsHouseOakPhotoText[];
extern const txt_cmd_s KurtsHouseCelebiStatueText[];
