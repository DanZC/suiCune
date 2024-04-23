#pragma once
//// EVENTS
extern const struct MapScripts PlayersHouse1F_MapScripts;
extern const struct MapEvents PlayersHouse1F_MapEvents;

//// CODE

bool PlayersHouse1F_MapScripts_DummyScene0(script_s* s);
bool PlayersHouse1F_MapScripts_DummyScene1(script_s* s);
bool MeetMomLeftScript(script_s* s);
bool MeetMomRightScript(script_s* s);
bool MeetMomScript(script_s* s);
bool MeetMomTalkedScript(script_s* s);
extern const char PokegearName[];
bool PlayersHouse1FReceiveItemStd(script_s* s);
bool MomScript(script_s* s);
bool NeighborScript(script_s* s);
bool PlayersHouse1FTVScript(script_s* s);
bool PlayersHouse1FStoveScript(script_s* s);
bool PlayersHouse1FSinkScript(script_s* s);
bool PlayersHouse1FFridgeScript(script_s* s);
extern const uint8_t MomTurnsTowardPlayerMovement[];
extern const uint8_t MomWalksToPlayerMovement[];
extern const uint8_t MomTurnsBackMovement[];
extern const uint8_t MomWalksBackMovement[];
extern const txt_cmd_s ElmsLookingForYouText[];
extern const txt_cmd_s MomGivesPokegearText[];
extern const txt_cmd_s IsItDSTText[];
extern const txt_cmd_s ComeHomeForDSTText[];
extern const txt_cmd_s KnowTheInstructionsText[];
extern const txt_cmd_s DontKnowTheInstructionsText[];
extern const txt_cmd_s InstructionsNextText[];
extern const txt_cmd_s HurryUpElmIsWaitingText[];
extern const txt_cmd_s SoWhatWasProfElmsErrandText[];
extern const txt_cmd_s ImBehindYouText[];
extern const txt_cmd_s NeighborMornIntroText[];
extern const txt_cmd_s NeighborDayIntroText[];
extern const txt_cmd_s NeighborNiteIntroText[];
extern const txt_cmd_s NeighborText[];
extern const txt_cmd_s PlayersHouse1FStoveText[];
extern const txt_cmd_s PlayersHouse1FSinkText[];
extern const txt_cmd_s PlayersHouse1FFridgeText[];
extern const txt_cmd_s PlayersHouse1FTVText[];
