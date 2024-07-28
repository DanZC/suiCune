#pragma once
//// EVENTS
extern const struct MapScripts FastShipCabins_NNW_NNE_NE_MapScripts;
extern const struct MapEvents FastShipCabins_NNW_NNE_NE_MapEvents;

//// CODE

extern const struct TrainerObj TrainerCooltrainermSean;
bool TrainerCooltrainermSean_Script(script_s* s);
extern const struct TrainerObj TrainerCooltrainerfCarol;
bool TrainerCooltrainerfCarol_Script(script_s* s);
extern const struct TrainerObj TrainerPokemaniacEthan;
bool TrainerPokemaniacEthan_Script(script_s* s);
extern const struct TrainerObj TrainerHikerNoland;
bool TrainerHikerNoland_Script(script_s* s);
extern const struct TrainerObj TrainerGentlemanEdward;
bool TrainerGentlemanEdward_Script(script_s* s);
extern const struct TrainerObj TrainerBurglarCorey;
bool TrainerBurglarCorey_Script(script_s* s);
bool FastShipLazySailorScript(script_s* s);
bool FastShipCabins_NNW_NNE_NETrashcan(script_s* s);
extern const uint8_t FastShipLazySailorLeavesMovement1[];
extern const uint8_t FastShipLazySailorLeavesMovement2[];
extern const txt_cmd_s CooltrainermSeanSeenText[];
extern const txt_cmd_s CooltrainermSeanBeatenText[];
extern const txt_cmd_s CooltrainermSeanAfterBattleText[];
extern const txt_cmd_s CooltrainerfCarolSeenText[];
extern const txt_cmd_s CooltrainerfCarolBeatenText[];
extern const txt_cmd_s CooltrainerfCarolAfterBattleText[];
extern const txt_cmd_s PokemaniacEthanSeenText[];
extern const txt_cmd_s PokemaniacEthanBeatenText[];
extern const txt_cmd_s PokemaniacEthanAfterBattleText[];
extern const txt_cmd_s HikerNolandSeenText[];
extern const txt_cmd_s HikerNolandBeatenText[];
extern const txt_cmd_s HikerNolandAfterBattleText[];
extern const txt_cmd_s SailorStanlySeenText[];
extern const txt_cmd_s SailorStanlyBeatenText[];
extern const txt_cmd_s SailorStanlyAfterBattleText[];
extern const txt_cmd_s GentlemanEdwardSeenText[];
extern const txt_cmd_s GentlemanEdwardBeatenText[];
extern const txt_cmd_s GentlemanEdwardAfterBattleText[];
extern const txt_cmd_s BurglarCoreySeenText[];
extern const txt_cmd_s BurglarCoreyBeatenText[];
extern const txt_cmd_s BurglarCoreyAfterBattleText[];
