#pragma once
//// EVENTS
extern const struct MapScripts PlayersNeighborsHouse_MapScripts;
extern const struct MapEvents PlayersNeighborsHouse_MapEvents;

//// CODE

bool PlayersNeighborsDaughterScript(script_s* s);
bool PlayersNeighborScript(script_s* s);
bool PlayersNeighborsHouseBookshelfScript(script_s* s);
bool PlayersNeighborsHouseRadioScript(script_s* s);
extern const txt_cmd_s PlayersNeighborsDaughterText[];
extern const txt_cmd_s PlayersNeighborText[];
extern const txt_cmd_s PlayerNeighborRadioText1[];
extern const txt_cmd_s PlayerNeighborRadioText2[];
extern const txt_cmd_s PlayerNeighborRadioText3[];
extern const txt_cmd_s PlayerNeighborRadioText4[];
