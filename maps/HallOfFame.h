#pragma once
//// EVENTS
extern const struct MapScripts HallOfFame_MapScripts;
extern const struct MapEvents HallOfFame_MapEvents;

//// CODE

bool HallOfFame_MapScripts_EnterHallOfFame(script_s* s);
bool HallOfFame_MapScripts_DummyScene(script_s* s);
bool HallOfFame_MapScripts_EnterHallOfFameScript(script_s* s);
bool HallOfFame_MapScripts_SkipPhoneCall(script_s* s);
extern const uint8_t HallOfFame_WalkUpWithLance[];
extern const uint8_t HallOfFame_SlowlyApproachMachine[];
extern const txt_cmd_s HallOfFame_LanceText[];
