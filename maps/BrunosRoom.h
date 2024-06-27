#pragma once
//// EVENTS
extern const struct MapScripts BrunosRoom_MapScripts;
extern const struct MapEvents BrunosRoom_MapEvents;

//// CODE

bool BrunosRoom_MapScripts_LockDoor(script_s* s);
bool BrunosRoom_MapScripts_DummyScene(script_s* s);
bool BrunosRoom_MapScripts_BrunosRoomDoors(script_s* s);
bool BrunosRoom_MapScripts_BrunosDoorLocksBehindYou(script_s* s);
bool BrunoScript_Battle(script_s* s);
bool BrunoScript_AfterBattle(script_s* s);
extern const uint8_t BrunosRoom_EnterMovement[];
extern const txt_cmd_s BrunoScript_BrunoBeforeText[];
extern const txt_cmd_s BrunoScript_BrunoBeatenText[];
extern const txt_cmd_s BrunoScript_BrunoDefeatText[];
