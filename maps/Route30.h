#pragma once
//// EVENTS
extern const struct MapScripts Route30_MapScripts;
extern const struct MapEvents Route30_MapEvents;

//// CODE

bool YoungsterJoey_ImportantBattleScript(script_s* s);
extern const struct TrainerObj TrainerYoungsterJoey;
bool TrainerYoungsterJoey_Script(script_s* s);
extern const struct TrainerObj TrainerYoungsterMikey;
bool TrainerYoungsterMikey_Script(script_s* s);
extern const struct TrainerObj TrainerBugCatcherDon;
bool TrainerBugCatcherDon_Script(script_s* s);
bool Route30YoungsterScript(script_s* s);
bool Route30CooltrainerFScript(script_s* s);
bool Route30Sign(script_s* s);
bool MrPokemonsHouseDirectionsSign(script_s* s);
bool MrPokemonsHouseSign(script_s* s);
bool Route30TrainerTips(script_s* s);
extern const struct ItemBall Route30Antidote;
bool Route30FruitTree1(script_s* s);
bool Route30FruitTree2(script_s* s);
extern const struct HiddenItem Route30HiddenPotion;
extern const uint8_t Route30_JoeysRattataAttacksMovement[];
extern const uint8_t Route30_MikeysRattataAttacksMovement[];
extern const txt_cmd_s Text_UseTackle[];
extern const txt_cmd_s Text_ThisIsABigBattle[];
extern const txt_cmd_s YoungsterJoey1SeenText[];
extern const txt_cmd_s YoungsterJoey1BeatenText[];
extern const txt_cmd_s YoungsterJoey1AfterText[];
extern const txt_cmd_s YoungsterMikeySeenText[];
extern const txt_cmd_s YoungsterMikeyBeatenText[];
extern const txt_cmd_s YoungsterMikeyAfterText[];
extern const txt_cmd_s BugCatcherDonSeenText[];
extern const txt_cmd_s BugCatcherDonBeatenText[];
extern const txt_cmd_s BugCatcherDonAfterText[];
extern const txt_cmd_s Route30YoungsterText_DirectionsToMrPokemonsHouse[];
extern const txt_cmd_s Route30YoungsterText_EveryoneIsBattling[];
extern const txt_cmd_s Route30CooltrainerFText[];
extern const txt_cmd_s Route30SignText[];
extern const txt_cmd_s MrPokemonsHouseDirectionsSignText[];
extern const txt_cmd_s MrPokemonsHouseSignText[];
extern const txt_cmd_s Route30TrainerTipsText[];
extern const txt_cmd_s YoungsterJoeyText_GiveHPUpAfterBattle[];
