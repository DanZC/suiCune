#pragma once
//// EVENTS
extern const struct MapScripts MobileBattleRoom_MapScripts;
extern const struct MapEvents MobileBattleRoom_MapEvents;

//// CODE

bool MobileBattleRoom_MapScripts_InitializeMobileBattleRoom(script_s* s);
bool MobileBattleRoom_MapScripts_DummyScene(script_s* s);
bool MobileBattleRoom_MapScripts_InitializeAndPreparePokecenter2F(script_s* s);
bool MobileBattleRoomConsoleScript(script_s* s);
extern const txt_cmd_s MobileBattleRoom_EstablishingCommsText[];
extern const txt_cmd_s MobileBattleRoom_HealText[];
