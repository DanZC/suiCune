#pragma once
//// EVENTS
extern const struct MapScripts RuinsOfAlphKabutoChamber_MapScripts;
extern const struct MapEvents RuinsOfAlphKabutoChamber_MapEvents;

//// CODE

bool RuinsOfAlphKabutoChamber_MapScripts_CheckWall(script_s* s);
bool RuinsOfAlphKabutoChamber_MapScripts_DummyScene(script_s* s);
bool RuinsOfAlphKabutoChamber_MapScripts_HiddenDoors(script_s* s);
bool RuinsOfAlphKabutoChamber_MapScripts_WallOpenScript(script_s* s);
bool RuinsOfAlphKabutoChamberReceptionistScript(script_s* s);
bool RuinsOfAlphKabutoChamberPuzzle(script_s* s);
bool RuinsOfAlphKabutoChamberScientistScript(script_s* s);
bool RuinsOfAlphKabutoChamberAncientReplica(script_s* s);
bool RuinsOfAlphKabutoChamberDescriptionSign(script_s* s);
bool RuinsOfAlphKabutoChamberWallPatternLeft(script_s* s);
bool RuinsOfAlphKabutoChamberWallPatternRight(script_s* s);
extern const uint8_t RuinsOfAlphKabutoChamberSkyfallTopMovement[];
extern const txt_cmd_s RuinsOfAlphKabutoChamberReceptionistText[];
extern const txt_cmd_s RuinsOfAlphKabutoChamberScientistCrypticText[];
extern const txt_cmd_s RuinsOfAlphKabutoChamberScientistHoleText[];
extern const txt_cmd_s RuinsOfAlphKabutoChamberScientistTremorText[];
extern const txt_cmd_s RuinsOfAlphKabutoChamberUnusedText[];
extern const txt_cmd_s RuinsOfAlphKabutoChamberWallPatternLeftText[];
extern const txt_cmd_s RuinsOfAlphKabutoChamberUnownText[];
extern const txt_cmd_s RuinsOfAlphKabutoChamberWallPatternRightText[];
extern const txt_cmd_s RuinsOfAlphKabutoChamberWallHoleText[];
extern const txt_cmd_s RuinsOfAlphKabutoChamberAncientReplicaText[];
extern const txt_cmd_s RuinsOfAlphKabutoChamberDescriptionText[];
