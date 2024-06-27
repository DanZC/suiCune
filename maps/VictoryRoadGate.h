#pragma once
//// EVENTS
extern const struct MapScripts VictoryRoadGate_MapScripts;
extern const struct MapEvents VictoryRoadGate_MapEvents;

//// CODE

bool VictoryRoadGate_MapScripts_DummyScene0(script_s* s);
bool VictoryRoadGate_MapScripts_DummyScene1(script_s* s);
bool VictoryRoadGateBadgeCheckScene(script_s* s);
bool VictoryRoadGateOfficerScript(script_s* s);
bool VictoryRoadGateBadgeCheckScript(script_s* s);
bool VictoryRoadGateLeftBlackBeltScript(script_s* s);
bool VictoryRoadGateRightBlackBeltScript(script_s* s);
extern const uint8_t VictoryRoadGateStepDownMovement[];
extern const txt_cmd_s VictoryRoadGateOfficerText[];
extern const txt_cmd_s VictoryRoadGateNotEnoughBadgesText[];
extern const txt_cmd_s VictoryRoadGateEightBadgesText[];
extern const txt_cmd_s VictoryRoadGateLeftBlackBeltText[];
extern const txt_cmd_s VictoryRoadGateRightBlackBeltText[];
