#pragma once
//// EVENTS
extern const struct MapScripts UnionCaveB1F_MapScripts;
extern const struct MapEvents UnionCaveB1F_MapEvents;

//// CODE

extern const struct TrainerObj TrainerPokemaniacAndrew;
bool TrainerPokemaniacAndrew_Script(script_s* s);
extern const struct TrainerObj TrainerPokemaniacCalvin;
bool TrainerPokemaniacCalvin_Script(script_s* s);
extern const struct TrainerObj TrainerHikerPhillip;
bool TrainerHikerPhillip_Script(script_s* s);
extern const struct TrainerObj TrainerHikerLeonard;
bool TrainerHikerLeonard_Script(script_s* s);
extern const struct ItemBall UnionCaveB1FTMSwift;
extern const struct ItemBall UnionCaveB1FXDefend;
bool UnionCaveB1FBoulder(script_s* s);
extern const txt_cmd_s HikerPhillipSeenText[];
extern const txt_cmd_s HikerPhillipBeatenText[];
extern const txt_cmd_s HikerPhillipAfterBattleText[];
extern const txt_cmd_s HikerLeonardSeenText[];
extern const txt_cmd_s HikerLeonardBeatenText[];
extern const txt_cmd_s HikerLeonardAfterBattleText[];
extern const txt_cmd_s PokemaniacAndrewSeenText[];
extern const txt_cmd_s PokemaniacAndrewBeatenText[];
extern const txt_cmd_s PokemaniacAndrewAfterBattleText[];
extern const txt_cmd_s PokemaniacCalvinSeenText[];
extern const txt_cmd_s PokemaniacCalvinBeatenText[];
extern const txt_cmd_s PokemaniacCalvinAfterBattleText[];
