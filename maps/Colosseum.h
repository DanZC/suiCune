#pragma once
//// EVENTS
extern const struct MapScripts Colosseum_MapScripts;
extern const struct MapEvents Colosseum_MapEvents;

//// CODE

bool Colosseum_MapScripts_InitializeColosseum(script_s* s);
bool Colosseum_MapScripts_DummyScene1(script_s* s);
bool Colosseum_MapScripts_DummyScene2(script_s* s);
bool Colosseum_MapScripts_SetWhichKris(script_s* s);
bool Colosseum_MapScripts_SetWhichChris(script_s* s);
bool Colosseum_MapScripts_PreparePokecenter2F(script_s* s);
bool Colosseum_MapScripts_InitializeAndPreparePokecenter2F(script_s* s);
bool ColosseumConsoleScript(script_s* s);
bool CableClubFriendScript(script_s* s);
extern const txt_cmd_s Colosseum_FriendReadyText[];
