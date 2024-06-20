#pragma once
//// EVENTS
extern const struct MapScripts RuinsOfAlphOmanyteChamber_MapScripts;
extern const struct MapEvents RuinsOfAlphOmanyteChamber_MapEvents;

//// CODE

bool RuinsOfAlphOmanyteChamber_MapScripts_CheckWall(script_s* s);
bool RuinsOfAlphOmanyteChamber_MapScripts_DummyScene(script_s* s);
bool RuinsOfAlphOmanyteChamber_MapScripts_HiddenDoors(script_s* s);
bool RuinsOfAlphOmanyteChamber_MapScripts_WallOpenScript(script_s* s);
bool RuinsOfAlphOmanyteChamberPuzzle(script_s* s);
bool RuinsOfAlphOmanyteChamberAncientReplica(script_s* s);
bool RuinsOfAlphOmanyteChamberDescriptionSign(script_s* s);
bool RuinsOfAlphOmanyteChamberWallPatternLeft(script_s* s);
bool RuinsOfAlphOmanyteChamberWallPatternRight(script_s* s);
extern const uint8_t RuinsOfAlphOmanyteChamberSkyfallTopMovement[];
extern const txt_cmd_s RuinsOfAlphOmanyteChamberWallPatternLeftText[];
extern const txt_cmd_s RuinsOfAlphOmanyteChamberUnownText[];
extern const txt_cmd_s RuinsOfAlphOmanyteChamberWallPatternRightText[];
extern const txt_cmd_s RuinsOfAlphOmanyteChamberWallHoleText[];
extern const txt_cmd_s RuinsOfAlphOmanyteChamberAncientReplicaText[];
extern const txt_cmd_s RuinsOfAlphOmanyteChamberDescriptionText[];
