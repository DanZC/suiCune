#pragma once
//// EVENTS
extern const struct MapScripts BattleTowerElevator_MapScripts;
extern const struct MapEvents BattleTowerElevator_MapEvents;

//// CODE

bool BattleTowerElevator_MapScripts_Scene0(script_s* s);
bool BattleTowerElevator_MapScripts_Scene1(script_s* s);
bool BattleTowerElevator_MapScripts_RideElevator(script_s* s);
extern const uint8_t MovementData_BattleTowerElevatorReceptionistWalksIn[];
extern const uint8_t MovementData_BattleTowerElevatorPlayerWalksIn[];
