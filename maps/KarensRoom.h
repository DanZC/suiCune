#pragma once
//// EVENTS
extern const struct MapScripts KarensRoom_MapScripts;
extern const struct MapEvents KarensRoom_MapEvents;

//// CODE

bool KarensRoom_MapScripts_LockDoor(script_s* s);
bool KarensRoom_MapScripts_DummyScene(script_s* s);
bool KarensRoom_MapScripts_KarensRoomDoors(script_s* s);
bool KarensRoom_MapScripts_KeepEntranceOpen(script_s* s);
bool KarensRoom_MapScripts_KeepExitClosed(script_s* s);
bool KarensRoom_MapScripts_KarensDoorLocksBehindYou(script_s* s);
bool KarenScript_Battle(script_s* s);
bool KarenScript_AfterBattle(script_s* s);
extern const uint8_t KarensRoom_EnterMovement[];
extern const txt_cmd_s KarenScript_KarenBeforeText[];
extern const txt_cmd_s KarenScript_KarenBeatenText[];
extern const txt_cmd_s KarenScript_KarenDefeatText[];
