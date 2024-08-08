#pragma once
//// EVENTS
extern const struct MapScripts Route21_MapScripts;
extern const struct MapEvents Route21_MapEvents;

//// CODE

extern const struct TrainerObj TrainerSwimmermSeth;
bool TrainerSwimmermSeth_Script(script_s* s);
extern const struct TrainerObj TrainerSwimmerfNikki;
bool TrainerSwimmerfNikki_Script(script_s* s);
extern const struct TrainerObj TrainerFisherArnold;
bool TrainerFisherArnold_Script(script_s* s);
extern const txt_cmd_s SwimmermSethSeenText[];
extern const txt_cmd_s SwimmermSethBeatenText[];
extern const txt_cmd_s SwimmermSethAfterBattleText[];
extern const txt_cmd_s SwimmerfNikkiSeenText[];
extern const txt_cmd_s SwimmerfNikkiBeatenText[];
extern const txt_cmd_s SwimmerfNikkiAfterBattleText[];
extern const txt_cmd_s FisherArnoldSeenText[];
extern const txt_cmd_s FisherArnoldBeatenText[];
extern const txt_cmd_s FisherArnoldAfterBattleText[];
