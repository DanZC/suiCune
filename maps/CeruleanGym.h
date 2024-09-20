#pragma once
//// EVENTS
extern const struct MapScripts CeruleanGym_MapScripts;
extern const struct MapEvents CeruleanGym_MapEvents;

//// CODE

bool CeruleanGym_MapScripts_DummyScene0(script_s* s);
bool CeruleanGym_MapScripts_GruntRunsOut(script_s* s);
bool CeruleanGym_MapScripts_GruntRunsOutScript(script_s* s);
bool CeruleanGymMistyScript(script_s* s);
extern const struct TrainerObj TrainerSwimmerfDiana;
bool TrainerSwimmerfDiana_Script(script_s* s);
extern const struct TrainerObj TrainerSwimmerfBriana;
bool TrainerSwimmerfBriana_Script(script_s* s);
extern const struct TrainerObj TrainerSwimmermParker;
bool TrainerSwimmermParker_Script(script_s* s);
bool CeruleanGymGuideScript(script_s* s);
extern const struct HiddenItem CeruleanGymHiddenMachinePart;
bool CeruleanGymStatue1(script_s* s);
bool CeruleanGymStatue2(script_s* s);
bool CeruleanGymStatue(script_s* s);
extern const uint8_t CeruleanGymGruntRunsDownMovement[];
extern const uint8_t CeruleanGymGruntRunsOutMovement[];
extern const uint8_t CeruleanGymGruntRunsIntoYouMovement[];
extern const uint8_t CeruleanGymGruntMovesCloseMovement[];
extern const uint8_t CeruleanGymGruntBacksAwayMovement[];
extern const txt_cmd_s CeruleanGymGruntIntroText[];
extern const txt_cmd_s CeruleanGymGruntBigMistakeText[];
extern const txt_cmd_s CeruleanGymGruntByeText[];
extern const txt_cmd_s CeruleanGymNote1Text[];
extern const txt_cmd_s CeruleanGymNote2Text[];
extern const txt_cmd_s MistyIntroText[];
extern const txt_cmd_s MistyWinLossText[];
extern const txt_cmd_s ReceivedCascadeBadgeText[];
extern const txt_cmd_s MistyFightDoneText[];
extern const txt_cmd_s SwimmerfDianaSeenText[];
extern const txt_cmd_s SwimmerfDianaBeatenText[];
extern const txt_cmd_s SwimmerfDianaAfterBattleText[];
extern const txt_cmd_s SwimmerfBrianaSeenText[];
extern const txt_cmd_s SwimmerfBrianaBeatenText[];
extern const txt_cmd_s SwimmerfBrianaAfterBattleText[];
extern const txt_cmd_s SwimmermParkerSeenText[];
extern const txt_cmd_s SwimmermParkerBeatenText[];
extern const txt_cmd_s SwimmermParkerAfterBattleText[];
extern const txt_cmd_s CeruleanGymGuideText[];
extern const txt_cmd_s CeruleanGymGuideWinText[];
