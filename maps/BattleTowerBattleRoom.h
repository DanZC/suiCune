#pragma once
//// EVENTS
extern const struct MapScripts BattleTowerBattleRoom_MapScripts;
extern const struct MapEvents BattleTowerBattleRoom_MapEvents;

//// CODE

bool BattleTowerBattleRoom_MapScripts_EnterBattleRoom(script_s* s);
bool BattleTowerBattleRoom_MapScripts_DummyScene(script_s* s);
bool Script_BattleRoom(script_s* s);
bool Script_BattleRoomLoop(script_s* s);
bool Script_ContinueAndBattleNextOpponent(script_s* s);
bool Script_DontBattleNextOpponent(script_s* s);
bool Script_DontSaveAndEndTheSession(script_s* s);
bool Script_FailedBattleTowerChallenge(script_s* s);
bool Script_BeatenAllTrainers(script_s* s);
bool Script_BeatenAllTrainers2(script_s* s);
bool Script_TooMuchTimeElapsedNoRegister(script_s* s);
bool Script_ChallengeCanceled(script_s* s);
extern const txt_cmd_s Text_ReturnedAfterSave_Mobile[];
