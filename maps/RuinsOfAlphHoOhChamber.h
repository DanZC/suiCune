#pragma once
//// EVENTS
extern const struct MapScripts RuinsOfAlphHoOhChamber_MapScripts;
extern const struct MapEvents RuinsOfAlphHoOhChamber_MapEvents;

//// CODE

bool RuinsOfAlphHoOhChamber_MapScripts_CheckWall(script_s* s);
bool RuinsOfAlphHoOhChamber_MapScripts_DummyScene(script_s* s);
bool RuinsOfAlphHoOhChamber_MapScripts_HiddenDoors(script_s* s);
bool RuinsOfAlphHoOhChamber_MapScripts_WallOpenScript(script_s* s);
bool RuinsOfAlphHoOhChamberPuzzle(script_s* s);
bool RuinsOfAlphHoOhChamberAncientReplica(script_s* s);
bool RuinsOfAlphHoOhChamberDescriptionSign(script_s* s);
bool RuinsOfAlphHoOhChamberWallPatternLeft(script_s* s);
bool RuinsOfAlphHoOhChamberWallPatternRight(script_s* s);
extern const uint8_t RuinsOfAlphHoOhChamberSkyfallTopMovement[];
extern const txt_cmd_s RuinsOfAlphHoOhChamberWallPatternLeftText[];
extern const txt_cmd_s RuinsOfAlphHoOhChamberUnownText[];
extern const txt_cmd_s RuinsOfAlphHoOhChamberWallPatternRightText[];
extern const txt_cmd_s RuinsOfAlphHoOhChamberWallHoleText[];
extern const txt_cmd_s RuinsOfAlphHoOhChamberAncientReplicaText[];
extern const txt_cmd_s RuinsOfAlphHoOhChamberDescriptionText[];
