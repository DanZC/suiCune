#pragma once
//// EVENTS
extern const struct MapScripts LavenderTown_MapScripts;
extern const struct MapEvents LavenderTown_MapEvents;

//// CODE

bool LavenderTown_MapScripts_FlyPoint(script_s* s);
bool LavenderTownPokefanMScript(script_s* s);
bool LavenderTownTeacherScript(script_s* s);
bool LavenderTownGrampsScript(script_s* s);
bool LavenderTownYoungsterScript(script_s* s);
bool LavenderTownSign(script_s* s);
bool KantoRadioStationSign(script_s* s);
bool VolunteerPokemonHouseSign(script_s* s);
bool SoulHouseSign(script_s* s);
bool LavenderPokecenterSignText(script_s* s);
bool LavenderMartSignText(script_s* s);
extern const txt_cmd_s LavenderTownPokefanMText[];
extern const txt_cmd_s LavenderTownTeacherText[];
extern const txt_cmd_s LavenderTownGrampsText[];
extern const txt_cmd_s LavenderTownYoungsterText[];
extern const txt_cmd_s LavenderTownSignText[];
extern const txt_cmd_s KantoRadioStationSignText[];
extern const txt_cmd_s VolunteerPokemonHouseSignText[];
extern const txt_cmd_s SoulHouseSignText[];
