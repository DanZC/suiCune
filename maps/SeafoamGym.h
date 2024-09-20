#pragma once
//// EVENTS
extern const struct MapScripts SeafoamGym_MapScripts;
extern const struct MapEvents SeafoamGym_MapEvents;

//// CODE

bool SeafoamGym_MapScripts_DummyScene(script_s* s);
bool SeafoamGymBlaineScript(script_s* s);
bool SeafoamGymGuideScript(script_s* s);
extern const txt_cmd_s BlaineIntroText[];
extern const txt_cmd_s BlaineWinLossText[];
extern const txt_cmd_s ReceivedVolcanoBadgeText[];
extern const txt_cmd_s BlaineAfterBattleText[];
extern const txt_cmd_s BlaineFightDoneText[];
extern const txt_cmd_s SeafoamGymGuideWinText[];
extern const txt_cmd_s SeafoamGymGuideWinText2[];
