#pragma once
//// EVENTS
extern const struct MapScripts EcruteakPokecenter1F_MapScripts;
extern const struct MapEvents EcruteakPokecenter1F_MapEvents;

//// CODE

bool EcruteakPokecenter1F_MapScripts_MeetBill(script_s* s);
bool EcruteakPokecenter1F_MapScripts_DummyScene(script_s* s);
bool EcruteakPokecenter1F_MapScripts_BillActivatesTimeCapsule(script_s* s);
bool EcruteakPokecenter1FNurseScript(script_s* s);
bool EcruteakPokecenter1FPokefanMScript(script_s* s);
bool EcruteakPokecenter1FCooltrainerFScript(script_s* s);
bool EcruteakPokecenter1FGymGuideScript(script_s* s);
extern const uint8_t EcruteakPokecenter1FBillMovement1[];
extern const uint8_t EcruteakPokecenter1FBillMovement2[];
extern const uint8_t EcruteakPokecenter1FPlayerMovement1[];
extern const txt_cmd_s EcruteakPokecenter1F_BillText1[];
extern const txt_cmd_s EcruteakPokecenter1F_BillText2[];
extern const txt_cmd_s EcruteakPokecenter1FPokefanMText[];
extern const txt_cmd_s EcruteakPokecenter1FPokefanMTextMobile[];
extern const txt_cmd_s EcruteakPokecenter1FCooltrainerFText[];
extern const txt_cmd_s EcruteakPokecenter1FGymGuideText[];
