#pragma once
//// EVENTS
extern const struct MapScripts TimeCapsule_MapScripts;
extern const struct MapEvents TimeCapsule_MapEvents;

//// CODE

bool TimeCapsule_MapScripts_InitializeTimeCapsule(script_s* s);
bool TimeCapsule_MapScripts_DummyScene(script_s* s);
bool TimeCapsule_MapScripts_SetWhichChris(script_s* s);
bool TimeCapsule_MapScripts_InitializeAndPreparePokecenter2F(script_s* s);
bool TimeCapsuleConsoleScript(script_s* s);
bool TimeCapsuleFriendScript(script_s* s);
extern const txt_cmd_s TimeCapsuleFriendScript_FriendReadyText[];
