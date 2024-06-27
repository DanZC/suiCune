#pragma once
//// EVENTS
extern const struct MapScripts VictoryRoad_MapScripts;
extern const struct MapEvents VictoryRoad_MapEvents;

//// CODE

bool VictoryRoad_MapScripts_DummyScene0(script_s* s);
bool VictoryRoad_MapScripts_DummyScene1(script_s* s);
bool VictoryRoadRivalLeft(script_s* s);
bool VictoryRoadRivalRight(script_s* s);
bool VictoryRoadRivalNext(script_s* s);
extern const struct ItemBall VictoryRoadTMEarthquake;
extern const struct ItemBall VictoryRoadMaxRevive;
extern const struct ItemBall VictoryRoadFullRestore;
extern const struct ItemBall VictoryRoadFullHeal;
extern const struct ItemBall VictoryRoadHPUp;
extern const struct HiddenItem VictoryRoadHiddenMaxPotion;
extern const struct HiddenItem VictoryRoadHiddenFullHeal;
extern const uint8_t VictoryRoadRivalBattleApproachMovement1[];
extern const uint8_t VictoryRoadRivalBattleApproachMovement2[];
extern const uint8_t VictoryRoadRivalBattleExitMovement1[];
extern const uint8_t VictoryRoadRivalBattleExitMovement2[];
extern const txt_cmd_s VictoryRoadRivalBeforeText[];
extern const txt_cmd_s VictoryRoadRivalDefeatText[];
extern const txt_cmd_s VictoryRoadRivalAfterText[];
extern const txt_cmd_s VictoryRoadRivalVictoryText[];
