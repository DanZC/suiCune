#pragma once
//// EVENTS
extern const struct MapScripts PalletTown_MapScripts;
extern const struct MapEvents PalletTown_MapEvents;

//// CODE

bool PalletTown_MapScripts_FlyPoint(script_s* s);
bool PalletTownTeacherScript(script_s* s);
bool PalletTownFisherScript(script_s* s);
bool PalletTownSign(script_s* s);
bool RedsHouseSign(script_s* s);
bool OaksLabSign(script_s* s);
bool BluesHouseSign(script_s* s);
extern const txt_cmd_s PalletTownTeacherText[];
extern const txt_cmd_s PalletTownFisherText[];
extern const txt_cmd_s PalletTownSignText[];
extern const txt_cmd_s RedsHouseSignText[];
extern const txt_cmd_s OaksLabSignText[];
extern const txt_cmd_s BluesHouseSignText[];
