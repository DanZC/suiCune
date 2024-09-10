#pragma once
//// EVENTS
extern const struct MapScripts PlayersHouse2F_MapScripts;
extern const struct MapEvents PlayersHouse2F_MapEvents;

//// CODE

bool PlayersHouse2F_MapScripts_DummyScene(script_s* s);
bool PlayersHouse2F_MapScripts_InitializeRoom(script_s* s);
bool PlayersHouse2F_MapScripts_SetUpTileDecorations(script_s* s);
bool PlayersHouseDoll1Script(script_s* s);
bool PlayersHouseDoll2Script(script_s* s);
bool PlayersHouseBigDollScript(script_s* s);
bool PlayersHouseGameConsoleScript(script_s* s);
extern const struct ConditionalEvent PlayersHousePosterScript;
bool PlayersHousePosterScript_Script(script_s* s);
bool PlayersHouseRadioScript(script_s* s);
bool PlayersHouseBookshelfScript(script_s* s);
bool PlayersHousePCScript(script_s* s);
extern const txt_cmd_s PlayersRadioText1[];
extern const txt_cmd_s PlayersRadioText2[];
extern const txt_cmd_s PlayersRadioText3[];
extern const txt_cmd_s PlayersRadioText4[];
