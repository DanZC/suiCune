#pragma once
//// EVENTS
extern const struct MapScripts LancesRoom_MapScripts;
extern const struct MapEvents LancesRoom_MapEvents;

//// CODE

bool LancesRoom_MapScripts_LockDoor(script_s* s);
bool LancesRoom_MapScripts_DummyScene(script_s* s);
bool LancesRoom_MapScripts_LancesRoomDoors(script_s* s);
bool LancesRoom_MapScripts_LancesDoorLocksBehindYou(script_s* s);
bool Script_ApproachLanceFromLeft(script_s* s);
bool Script_ApproachLanceFromRight(script_s* s);
bool LancesRoomLanceScript(script_s* s);
extern const uint8_t LancesRoom_EnterMovement[];
extern const uint8_t MovementData_ApproachLanceFromLeft[];
extern const uint8_t MovementData_ApproachLanceFromRight[];
extern const uint8_t LancesRoomMovementData_MaryRushesIn[];
extern const uint8_t LancesRoomMovementData_OakWalksIn[];
extern const uint8_t LancesRoomMovementData_MaryYieldsToOak[];
extern const uint8_t LancesRoomMovementData_MaryInterviewChampion[];
extern const uint8_t LancesRoomMovementData_LancePositionsSelfToGuidePlayerAway[];
extern const uint8_t LancesRoomMovementData_LanceLeadsPlayerToHallOfFame[];
extern const uint8_t LancesRoomMovementData_PlayerExits[];
extern const uint8_t LancesRoomMovementData_MaryTriesToFollow[];
extern const uint8_t LancesRoomMovementData_MaryRunsBackAndForth[];
extern const txt_cmd_s LanceBattleIntroText[];
extern const txt_cmd_s LanceBattleWinText[];
extern const txt_cmd_s LanceBattleAfterText[];
extern const txt_cmd_s LancesRoomMaryOhNoOakText[];
extern const txt_cmd_s LancesRoomOakCongratulationsText[];
extern const txt_cmd_s LancesRoomMaryInterviewText[];
extern const txt_cmd_s LancesRoomNoisyText[];
extern const txt_cmd_s LancesRoomMaryNoInterviewText[];
