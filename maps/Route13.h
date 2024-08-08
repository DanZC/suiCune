#pragma once
//// EVENTS
extern const struct MapScripts Route13_MapScripts;
extern const struct MapEvents Route13_MapEvents;

//// CODE

extern const struct TrainerObj TrainerPokefanmAlex;
bool TrainerPokefanmAlex_Script(script_s* s);
extern const struct TrainerObj TrainerPokefanmJoshua;
bool TrainerPokefanmJoshua_Script(script_s* s);
extern const struct TrainerObj TrainerBirdKeeperPerry;
bool TrainerBirdKeeperPerry_Script(script_s* s);
extern const struct TrainerObj TrainerBirdKeeperBret;
bool TrainerBirdKeeperBret_Script(script_s* s);
extern const struct TrainerObj TrainerHikerKenny;
bool TrainerHikerKenny_Script(script_s* s);
bool Route13TrainerTips(script_s* s);
bool Route13Sign(script_s* s);
bool Route13DirectionsSign(script_s* s);
extern const struct HiddenItem Route13HiddenCalcium;
extern const txt_cmd_s PokefanmAlexSeenText[];
extern const txt_cmd_s PokefanmAlexBeatenText[];
extern const txt_cmd_s PokefanmAlexAfterBattleText[];
extern const txt_cmd_s PokefanmJoshuaSeenText[];
extern const txt_cmd_s PokefanmJoshuaBeatenText[];
extern const txt_cmd_s PokefanmJoshuaAfterBattleText[];
extern const txt_cmd_s BirdKeeperPerrySeenText[];
extern const txt_cmd_s BirdKeeperPerryBeatenText[];
extern const txt_cmd_s BirdKeeperPerryAfterBattleText[];
extern const txt_cmd_s BirdKeeperBretSeenText[];
extern const txt_cmd_s BirdKeeperBretBeatenText[];
extern const txt_cmd_s BirdKeeperBretAfterBattleText[];
extern const txt_cmd_s HikerKennySeenText[];
extern const txt_cmd_s HikerKennyBeatenText[];
extern const txt_cmd_s HikerKennyAfterBattleText[];
extern const txt_cmd_s Route13TrainerTipsText[];
extern const txt_cmd_s Route13SignText[];
extern const txt_cmd_s Route13DirectionsSignText[];
