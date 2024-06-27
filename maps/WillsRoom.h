#pragma once
//// EVENTS
extern const struct MapScripts WillsRoom_MapScripts;
extern const struct MapEvents WillsRoom_MapEvents;

//// CODE

bool WillsRoom_MapScripts_LockDoor(script_s* s);
bool WillsRoom_MapScripts_DummyScene(script_s* s);
bool WillsRoom_MapScripts_WillsRoomDoors(script_s* s);
bool WillsRoom_MapScripts_WillsDoorLocksBehindYou(script_s* s);
bool WillScript_Battle(script_s* s);
bool WillScript_AfterBattle(script_s* s);
extern const uint8_t WillsRoom_EnterMovement[];
extern const txt_cmd_s WillScript_WillBeforeText[];
extern const txt_cmd_s WillScript_WillBeatenText[];
extern const txt_cmd_s WillScript_WillDefeatText[];
