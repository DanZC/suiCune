#pragma once
//// EVENTS
extern const struct MapScripts FastShip1F_MapScripts;
extern const struct MapEvents FastShip1F_MapEvents;

//// CODE

bool FastShip1F_MapScripts_DummyScene0(script_s* s);
bool FastShip1F_MapScripts_EnterFastShip(script_s* s);
bool FastShip1F_MapScripts_DummyScene2(script_s* s);
bool FastShip1F_MapScripts_EnterFastShipScript(script_s* s);
bool FastShip1FSailor1Script(script_s* s);
bool FastShip1FSailor2Script(script_s* s);
bool FastShip1FSailor3Script(script_s* s);
bool WorriedGrandpaSceneRight(script_s* s);
bool WorriedGrandpaSceneLeft(script_s* s);
extern const uint8_t FastShip1F_SailorStepAsideMovement[];
extern const uint8_t FastShip1F_SailorBlocksDoorMovement[];
extern const uint8_t FastShip1F_SailorStepAsideDownMovement[];
extern const uint8_t FastShip1F_PlayerEntersShipMovement[];
extern const uint8_t FastShip1F_GrandpaRunsInMovement[];
extern const uint8_t FastShip1F_GrandpaApproachesPlayerMovement[];
extern const uint8_t FastShip1F_GrandpaRunsOutMovement[];
extern const uint8_t FastShip1F_PlayerHitByGrandpaMovement[];
extern const uint8_t FastShip1F_StepUpMovement[];
extern const uint8_t FastShip1F_StepDownMovement[];
extern const uint8_t FastShip1F_PlayerLeavesShipMovement[];
extern const uint8_t FastShip1F_PlayerLeavesShipRightMovement[];
extern const txt_cmd_s FastShip1FSailor1Text_ToVermilion[];
extern const txt_cmd_s FastShip1FSailor1Text_ToOlivine[];
extern const txt_cmd_s FastShip1FSailor2Text_FirstTime[];
extern const txt_cmd_s FastShip1FSailor2Text[];
extern const txt_cmd_s FastShip1FSailor3Text[];
extern const txt_cmd_s FastShip1FGrandpaText[];
extern const txt_cmd_s FastShip1FSailor1Text_InOlivine[];
extern const txt_cmd_s FastShip1FSailor1Text_InVermilion[];
