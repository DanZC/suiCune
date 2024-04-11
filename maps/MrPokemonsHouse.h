#pragma once
//// EVENTS
extern const struct MapScripts MrPokemonsHouse_MapScripts;
extern const struct MapEvents MrPokemonsHouse_MapEvents;

//// CODE

bool MrPokemonsHouse_MapScripts_MeetMrPokemon(script_s* s);
bool MrPokemonsHouse_MapScripts_DummyScene(script_s* s);
bool MrPokemonsHouse_MapScripts_MrPokemonEvent(script_s* s);
bool MrPokemonsHouse_MrPokemonScript(script_s* s);
bool MrPokemonsHouse_OakScript(script_s* s);
bool MrPokemonsHouse_ForeignMagazines(script_s* s);
bool MrPokemonsHouse_BrokenComputer(script_s* s);
bool MrPokemonsHouse_StrangeCoins(script_s* s);
extern const uint8_t MrPokemonsHouse_PlayerWalksToMrPokemon[];
extern const uint8_t MrPokemonsHouse_OakWalksToPlayer[];
extern const uint8_t MrPokemonsHouse_OakExits[];
extern const txt_cmd_s MrPokemonIntroText1[];
extern const txt_cmd_s MrPokemonIntroText2[];
extern const txt_cmd_s MrPokemonsHouse_GotEggText[];
extern const txt_cmd_s MrPokemonIntroText3[];
extern const txt_cmd_s MrPokemonIntroText4[];
extern const txt_cmd_s MrPokemonIntroText5[];
extern const txt_cmd_s MrPokemonsHouse_MrPokemonHealText[];
extern const txt_cmd_s MrPokemonText_ImDependingOnYou[];
extern const txt_cmd_s MrPokemonText_AlwaysNewDiscoveries[];
extern const txt_cmd_s MrPokemonsHouse_OakText1[];
extern const txt_cmd_s MrPokemonsHouse_GetDexText[];
extern const txt_cmd_s MrPokemonsHouse_OakText2[];
extern const txt_cmd_s MrPokemonText_GimmeTheScale[];
extern const txt_cmd_s MrPokemonText_Disappointed[];
extern const txt_cmd_s MrPokemonsHouse_ForeignMagazinesText[];
extern const txt_cmd_s MrPokemonsHouse_BrokenComputerText[];
extern const txt_cmd_s MrPokemonsHouse_StrangeCoinsText[];
