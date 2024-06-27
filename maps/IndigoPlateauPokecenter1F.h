#pragma once
//// EVENTS
extern const struct MapScripts IndigoPlateauPokecenter1F_MapScripts;
extern const struct MapEvents IndigoPlateauPokecenter1F_MapEvents;

//// CODE

bool IndigoPlateauPokecenter1F_MapScripts_DummyScene(script_s* s);
bool IndigoPlateauPokecenter1F_MapScripts_PrepareElite4(script_s* s);
bool PlateauRivalBattle1(script_s* s);
bool PlateauRivalBattle2(script_s* s);
bool PlateauRivalBattleCommon(script_s* s);
bool PlateauRivalPostBattle(script_s* s);
bool PlateauRivalScriptDone(script_s* s);
bool IndigoPlateauPokecenter1FNurseScript(script_s* s);
bool IndigoPlateauPokecenter1FClerkScript(script_s* s);
bool IndigoPlateauPokecenter1FCooltrainerMScript(script_s* s);
bool TeleportGuyScript(script_s* s);
bool AbraScript(script_s* s);
extern const uint8_t PlateauRivalMovement1[];
extern const uint8_t PlateauRivalMovement2[];
extern const uint8_t PlateauRivalLeavesMovement[];
extern const txt_cmd_s IndigoPlateauPokecenter1FCooltrainerMText[];
extern const txt_cmd_s PlateauRivalText1[];
extern const txt_cmd_s PlateauRivalWinText[];
extern const txt_cmd_s PlateauRivalText2[];
extern const txt_cmd_s PlateauRivalLoseText[];
extern const txt_cmd_s TeleportGuyText1[];
extern const txt_cmd_s TeleportGuyYesText[];
extern const txt_cmd_s TeleportGuyNoText[];
extern const txt_cmd_s AbraText[];
