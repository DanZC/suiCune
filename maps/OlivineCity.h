#pragma once
//// EVENTS
extern const struct MapScripts OlivineCity_MapScripts;
extern const struct MapEvents OlivineCity_MapEvents;

//// CODE

bool OlivineCity_MapScripts_DummyScene0(script_s* s);
bool OlivineCity_MapScripts_DummyScene1(script_s* s);
bool OlivineCity_MapScripts_FlyPoint(script_s* s);
bool OlivineCityRivalSceneTop(script_s* s);
bool OlivineCityRivalSceneBottom(script_s* s);
bool OlivineCitySailor1Script(script_s* s);
bool OlivineCityStandingYoungsterScript(script_s* s);
bool OlivineCitySailor2Script(script_s* s);
bool OlivineCitySign(script_s* s);
bool OlivineCityPortSign(script_s* s);
bool OlivineGymSign(script_s* s);
bool OlivineLighthouseSign(script_s* s);
bool OlivineCityBattleTowerSign(script_s* s);
bool OlivineCityPokecenterSign(script_s* s);
bool OlivineCityMartSign(script_s* s);
extern const uint8_t OlivineCityRivalApproachesTopMovement[];
extern const uint8_t OlivineCityRivalApproachesBottomMovement[];
extern const uint8_t OlivineCityRivalLeavesTopMovement[];
extern const uint8_t OlivineCityRivalLeavesBottomMovement[];
extern const uint8_t OlivineCityPlayerStepsAsideTopMovement[];
extern const uint8_t OlivineCityPlayerStepsAsideBottomMovement[];
extern const txt_cmd_s OlivineCityRivalText[];
extern const txt_cmd_s OlivineCitySailor1Text[];
extern const txt_cmd_s OlivineCityStandingYoungsterPokegearText[];
extern const txt_cmd_s OlivineCityStandingYoungsterPokedexText[];
extern const txt_cmd_s OlivineCitySailor2Text[];
extern const txt_cmd_s OlivineCitySignText[];
extern const txt_cmd_s OlivineCityPortSignText[];
extern const txt_cmd_s OlivineGymSignText[];
extern const txt_cmd_s OlivineLighthouseSignText[];
extern const txt_cmd_s OlivineCityBattleTowerSignText[];
extern const txt_cmd_s OlivineCityBattleTowerSignText_NotYetOpen[];
