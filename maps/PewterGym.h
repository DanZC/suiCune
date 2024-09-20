#pragma once
//// EVENTS
extern const struct MapScripts PewterGym_MapScripts;
extern const struct MapEvents PewterGym_MapEvents;

//// CODE

bool PewterGymBrockScript(script_s* s);
extern const struct TrainerObj TrainerCamperJerry;
bool TrainerCamperJerry_Script(script_s* s);
bool PewterGymGuideScript(script_s* s);
bool PewterGymStatue(script_s* s);
extern const txt_cmd_s BrockIntroText[];
extern const txt_cmd_s BrockWinLossText[];
extern const txt_cmd_s ReceivedBoulderBadgeText[];
extern const txt_cmd_s BrockBoulderBadgeText[];
extern const txt_cmd_s BrockFightDoneText[];
extern const txt_cmd_s CamperJerrySeenText[];
extern const txt_cmd_s CamperJerryBeatenText[];
extern const txt_cmd_s CamperJerryAfterBattleText[];
extern const txt_cmd_s PewterGymGuideText[];
extern const txt_cmd_s PewterGymGuideWinText[];
