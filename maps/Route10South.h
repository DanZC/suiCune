#pragma once
//// EVENTS
extern const struct MapScripts Route10South_MapScripts;
extern const struct MapEvents Route10South_MapEvents;

//// CODE

extern const struct TrainerObj TrainerHikerJim;
bool TrainerHikerJim_Script(script_s* s);
extern const struct TrainerObj TrainerPokefanmRobert;
bool TrainerPokefanmRobert_Script(script_s* s);
bool Route10Sign(script_s* s);
extern const txt_cmd_s HikerJimSeenText[];
extern const txt_cmd_s HikerJimBeatenText[];
extern const txt_cmd_s HikerJimAfterBattleText[];
extern const txt_cmd_s PokefanmRobertSeenText[];
extern const txt_cmd_s PokefanmRobertBeatenText[];
extern const txt_cmd_s PokefanmRobertAfterBattleText[];
extern const txt_cmd_s Route10SignText[];
