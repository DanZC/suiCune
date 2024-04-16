#pragma once
//// EVENTS
extern const struct MapScripts ElmsHouse_MapScripts;
extern const struct MapEvents ElmsHouse_MapEvents;

//// CODE

bool ElmsWife(script_s* s);
bool ElmsSon(script_s* s);
bool ElmsHousePC(script_s* s);
bool ElmsHouseBookshelf(script_s* s);
extern const txt_cmd_s ElmsWifeText[];
extern const txt_cmd_s ElmsSonText[];
extern const txt_cmd_s ElmsHouseLabFoodText[];
extern const txt_cmd_s ElmsHousePokemonFoodText[];
extern const txt_cmd_s ElmsHousePCText[];
