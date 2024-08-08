#pragma once
//// EVENTS
extern const struct MapScripts Route17_MapScripts;
extern const struct MapEvents Route17_MapEvents;

//// CODE

bool Route17_MapScripts_AlwaysOnBike(script_s* s);
extern const struct TrainerObj TrainerBikerCharles;
bool TrainerBikerCharles_Script(script_s* s);
extern const struct TrainerObj TrainerBikerRiley;
bool TrainerBikerRiley_Script(script_s* s);
extern const struct TrainerObj TrainerBikerJoel;
bool TrainerBikerJoel_Script(script_s* s);
extern const struct TrainerObj TrainerBikerGlenn;
bool TrainerBikerGlenn_Script(script_s* s);
extern const struct HiddenItem Route17HiddenMaxEther;
extern const struct HiddenItem Route17HiddenMaxElixer;
extern const txt_cmd_s BikerRileySeenText[];
extern const txt_cmd_s BikerRileyBeatenText[];
extern const txt_cmd_s BikerRileyAfterBattleText[];
extern const txt_cmd_s BikerJoelSeenText[];
extern const txt_cmd_s BikerJoelBeatenText[];
extern const txt_cmd_s BikerJoelAfterBattleText[];
extern const txt_cmd_s BikerGlennSeenText[];
extern const txt_cmd_s BikerGlennBeatenText[];
extern const txt_cmd_s BikerGlennAfterBattleText[];
extern const txt_cmd_s BikerCharlesSeenText[];
extern const txt_cmd_s BikerCharlesBeatenText[];
extern const txt_cmd_s BikerCharlesAfterBattleText[];
