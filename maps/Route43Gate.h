#pragma once
//// EVENTS
extern const struct MapScripts Route43Gate_MapScripts;
extern const struct MapEvents Route43Gate_MapEvents;

//// CODE

bool Route43Gate_MapScripts_RocketShakedown(script_s* s);
bool Route43Gate_MapScripts_DummyScene(script_s* s);
bool Route43Gate_MapScripts_CheckIfRockets(script_s* s);
bool Route43Gate_MapScripts_RocketTakeover(script_s* s);
bool RocketScript_Southbound(script_s* s);
bool RocketScript_TollSouth(script_s* s);
bool RocketScript_YoureBrokeSouth(script_s* s);
bool RocketScript_ShakeDownSouth(script_s* s);
bool RocketScript_Northbound(script_s* s);
bool RocketScript_TollNorth(script_s* s);
bool RocketScript_YoureBrokeNorth(script_s* s);
bool RocketScript_ShakeDownNorth(script_s* s);
bool RocketScript_MakingABundle(script_s* s);
bool OfficerScript_GuardWithSludgeBomb(script_s* s);
extern const uint8_t PlayerStepsIn[];
extern const uint8_t Rocket1Script_BlocksYouSouth[];
extern const uint8_t Rocket1Script_LetsYouPassSouth[];
extern const uint8_t Rocket1Script_BlocksYouNorth[];
extern const uint8_t Rocket1Script_LetsYouPassNorth[];
extern const uint8_t Rocket2Script_BlocksYouSouth[];
extern const uint8_t Rocket2Script_LetsYouPassSouth[];
extern const uint8_t Rocket2Script_BlocksYouNorth[];
extern const uint8_t Rocket2Script_LetsYouPassNorth[];
extern const txt_cmd_s RocketText_TollFee[];
extern const txt_cmd_s RocketText_ThankYou[];
extern const txt_cmd_s RocketText_AllYouGot[];
extern const txt_cmd_s RocketText_MakingABundle[];
extern const txt_cmd_s OfficerText_FoundTM[];
extern const txt_cmd_s Text_ReceivedTM30[];
extern const txt_cmd_s OfficerText_AvoidGrass[];
