#pragma once
//// EVENTS
extern const struct MapScripts Route20_MapScripts;
extern const struct MapEvents Route20_MapEvents;

//// CODE

bool Route20_MapScripts_ClearRocks(script_s* s);
extern const struct TrainerObj TrainerSwimmerfNicole;
bool TrainerSwimmerfNicole_Script(script_s* s);
extern const struct TrainerObj TrainerSwimmerfLori;
bool TrainerSwimmerfLori_Script(script_s* s);
extern const struct TrainerObj TrainerSwimmermCameron;
bool TrainerSwimmermCameron_Script(script_s* s);
bool CinnabarGymSign(script_s* s);
extern const txt_cmd_s SwimmerfNicoleSeenText[];
extern const txt_cmd_s SwimmerfNicoleBeatenText[];
extern const txt_cmd_s SwimmerfNicoleAfterBattleText[];
extern const txt_cmd_s SwimmerfLoriSeenText[];
extern const txt_cmd_s SwimmerfLoriBeatenText[];
extern const txt_cmd_s SwimmerfLoriAfterBattleText[];
extern const txt_cmd_s SwimmermCameronSeenText[];
extern const txt_cmd_s SwimmermCameronBeatenText[];
extern const txt_cmd_s SwimmermCameronAfterBattleText[];
extern const txt_cmd_s CinnabarGymSignText[];
