#pragma once
//// EVENTS
extern const struct MapScripts BattleTowerOutside_MapScripts;
extern const struct MapEvents BattleTowerOutside_MapEvents;

//// CODE

bool BattleTowerOutside_MapScripts_Callback1(script_s* s);
bool BattleTowerOutside_MapScripts_Callback2(script_s* s);
bool BattleTowerOutsideYoungsterScript(script_s* s);
bool BattleTowerOutsideBeautyScript(script_s* s);
bool BattleTowerOutsideSailorScript(script_s* s);
bool BattleTowerOutsideSign(script_s* s);
extern const txt_cmd_s BattleTowerOutsideYoungsterText_NotYetOpen[];
extern const txt_cmd_s BattleTowerOutsideYoungsterText_Mobile[];
extern const txt_cmd_s BattleTowerOutsideYoungsterText[];
extern const txt_cmd_s BattleTowerOutsideBeautyText_NotYetOpen[];
extern const txt_cmd_s BattleTowerOutsideBeautyText[];
extern const txt_cmd_s BattleTowerOutsideSailorText_Mobile[];
extern const txt_cmd_s BattleTowerOutsideSailorText[];
extern const txt_cmd_s BattleTowerOutsideSignText_NotYetOpen[];
extern const txt_cmd_s BattleTowerOutsideSignText[];
extern const txt_cmd_s BattleTowerOutsideText_DoorsClosed[];
extern const txt_cmd_s BattleTowerOutsideText_DoorsOpen[];
