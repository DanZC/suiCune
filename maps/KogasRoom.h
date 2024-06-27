#pragma once
//// EVENTS
extern const struct MapScripts KogasRoom_MapScripts;
extern const struct MapEvents KogasRoom_MapEvents;

//// CODE

bool KogasRoom_MapScripts_LockDoor(script_s* s);
bool KogasRoom_MapScripts_DummyScene(script_s* s);
bool KogasRoom_MapScripts_KogasRoomDoors(script_s* s);
bool KogasRoom_MapScripts_KogasDoorLocksBehindYou(script_s* s);
bool KogaScript_Battle(script_s* s);
bool KogaScript_AfterBattle(script_s* s);
extern const uint8_t KogasRoom_EnterMovement[];
extern const txt_cmd_s KogaScript_KogaBeforeText[];
extern const txt_cmd_s KogaScript_KogaBeatenText[];
extern const txt_cmd_s KogaScript_KogaDefeatText[];
