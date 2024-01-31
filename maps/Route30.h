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
extern const struct TextCmd Text_UseTackle[];
extern const struct TextCmd Text_ThisIsABigBattle[];
extern const struct TextCmd YoungsterJoey1SeenText[];
extern const struct TextCmd YoungsterJoey1BeatenText[];
extern const struct TextCmd YoungsterJoey1AfterText[];
extern const struct TextCmd YoungsterMikeySeenText[];
extern const struct TextCmd YoungsterMikeyBeatenText[];
extern const struct TextCmd YoungsterMikeyAfterText[];
extern const struct TextCmd BugCatcherDonSeenText[];
extern const struct TextCmd BugCatcherDonBeatenText[];
extern const struct TextCmd BugCatcherDonAfterText[];
extern const struct TextCmd Route30YoungsterText_DirectionsToMrPokemonsHouse[];
extern const struct TextCmd Route30YoungsterText_EveryoneIsBattling[];
extern const struct TextCmd Route30CooltrainerFText[];
extern const struct TextCmd Route30SignText[];
extern const struct TextCmd MrPokemonsHouseDirectionsSignText[];
extern const struct TextCmd MrPokemonsHouseSignText[];
extern const struct TextCmd Route30TrainerTipsText[];
extern const struct TextCmd YoungsterJoeyText_GiveHPUpAfterBattle[];
