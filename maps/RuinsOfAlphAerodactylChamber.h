#pragma once
//// EVENTS
extern const struct MapScripts RuinsOfAlphAerodactylChamber_MapScripts;
extern const struct MapEvents RuinsOfAlphAerodactylChamber_MapEvents;

//// CODE

bool RuinsOfAlphAerodactylChamber_MapScripts_CheckWall(script_s* s);
bool RuinsOfAlphAerodactylChamber_MapScripts_OpenWall(script_s* s);
bool RuinsOfAlphAerodactylChamber_MapScripts_DummyScene(script_s* s);
bool RuinsOfAlphAerodactylChamber_MapScripts_HiddenDoors(script_s* s);
bool RuinsOfAlphAerodactylChamber_MapScripts_WallOpen(script_s* s);
bool RuinsOfAlphAerodactylChamber_MapScripts_FloorClosed(script_s* s);
bool RuinsOfAlphAerodactylChamber_MapScripts_WallOpenScript(script_s* s);
bool RuinsOfAlphAerodactylChamberPuzzle(script_s* s);
bool RuinsOfAlphAerodactylChamberAncientReplica(script_s* s);
bool RuinsOfAlphAerodactylChamberDescriptionSign(script_s* s);
bool RuinsOfAlphAerodactylChamberWallPatternLeft(script_s* s);
bool RuinsOfAlphAerodactylChamberWallPatternRight(script_s* s);
extern const uint8_t RuinsOfAlphAerodactylChamberSkyfallTopMovement[];
extern const txt_cmd_s RuinsOfAlphAerodactylChamberWallPatternLeftText[];
extern const txt_cmd_s RuinsOfAlphAerodactylChamberUnownText[];
extern const txt_cmd_s RuinsOfAlphAerodactylChamberWallPatternRightText[];
extern const txt_cmd_s RuinsOfAlphAerodactylChamberWallHoleText[];
extern const txt_cmd_s RuinsOfAlphAerodactylChamberAncientReplicaText[];
extern const txt_cmd_s RuinsOfAlphAerodactylChamberDescriptionText[];
