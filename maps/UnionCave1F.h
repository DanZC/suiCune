#pragma once
//// EVENTS
extern const struct MapScripts UnionCave1F_MapScripts;
extern const struct MapEvents UnionCave1F_MapEvents;

//// CODE

extern const struct TrainerObj TrainerPokemaniacLarry;
bool TrainerPokemaniacLarry_Script(script_s* s);
extern const struct TrainerObj TrainerHikerRussell;
bool TrainerHikerRussell_Script(script_s* s);
extern const struct TrainerObj TrainerHikerDaniel;
bool TrainerHikerDaniel_Script(script_s* s);
extern const struct TrainerObj TrainerFirebreatherBill;
bool TrainerFirebreatherBill_Script(script_s* s);
extern const struct TrainerObj TrainerFirebreatherRay;
bool TrainerFirebreatherRay_Script(script_s* s);
extern const struct ItemBall UnionCave1FGreatBall;
extern const struct ItemBall UnionCave1FXAttack;
extern const struct ItemBall UnionCave1FPotion;
extern const struct ItemBall UnionCave1FAwakening;
bool UnionCave1FUnusedSign(script_s* s);
extern const txt_cmd_s HikerRussellSeenText[];
extern const txt_cmd_s HikerRussellBeatenText[];
extern const txt_cmd_s HikerRussellAfterBattleText[];
extern const txt_cmd_s PokemaniacLarrySeenText[];
extern const txt_cmd_s PokemaniacLarryBeatenText[];
extern const txt_cmd_s PokemaniacLarryAfterBattleText[];
extern const txt_cmd_s HikerDanielSeenText[];
extern const txt_cmd_s HikerDanielBeatenText[];
extern const txt_cmd_s HikerDanielAfterBattleText[];
extern const txt_cmd_s FirebreatherBillSeenText[];
extern const txt_cmd_s FirebreatherBillBeatenText[];
extern const txt_cmd_s FirebreatherBillAfterBattleText[];
extern const txt_cmd_s FirebreatherRaySeenText[];
extern const txt_cmd_s FirebreatherRayBeatenText[];
extern const txt_cmd_s FirebreatherRayAfterBattleText[];
extern const txt_cmd_s UnionCave1FUnusedSignText[];
