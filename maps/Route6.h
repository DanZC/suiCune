#pragma once
//// EVENTS
extern const struct MapScripts Route6_MapScripts;
extern const struct MapEvents Route6_MapEvents;

//// CODE

extern const struct TrainerObj TrainerPokefanmRex;
bool TrainerPokefanmRex_Script(script_s* s);
extern const struct TrainerObj TrainerPokefanmAllan;
bool TrainerPokefanmAllan_Script(script_s* s);
bool Route6PokefanMScript(script_s* s);
bool Route6UndergroundPathSign(script_s* s);
extern const txt_cmd_s Route6PokefanMText[];
extern const txt_cmd_s Route6UndergroundPathSignText[];
extern const txt_cmd_s PokefanmRexSeenText[];
extern const txt_cmd_s PokefanmRexBeatenText[];
extern const txt_cmd_s PokefanmRexAfterBattleText[];
extern const txt_cmd_s PokefanmAllanSeenText[];
extern const txt_cmd_s PokefanmAllanBeatenText[];
extern const txt_cmd_s PokefanmAllanAfterBattleText[];
