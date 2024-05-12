#pragma once
//// EVENTS
extern const struct MapScripts VioletPokecenter1F_MapScripts;
extern const struct MapEvents VioletPokecenter1F_MapEvents;

//// CODE

bool VioletPokecenterNurse(script_s* s);
bool VioletPokecenter1F_ElmsAideScript(script_s* s);
bool VioletPokecenter1FGameboyKidScript(script_s* s);
bool VioletPokecenter1FGentlemanScript(script_s* s);
bool VioletPokecenter1FYoungsterScript(script_s* s);
extern const uint8_t MovementData_AideWalksStraightOutOfPokecenter[];
extern const uint8_t MovementData_AideWalksLeftToExitPokecenter[];
extern const uint8_t MovementData_AideFinishesLeavingPokecenter[];
extern const txt_cmd_s VioletPokecenterElmsAideFavorText[];
extern const txt_cmd_s VioletPokecenterElmsAideGiveEggText[];
extern const txt_cmd_s VioletCityElmsAideFullPartyText[];
extern const txt_cmd_s VioletPokecenterElmsAideRefuseText[];
extern const txt_cmd_s VioletPokecenterElmsAideAskEggText[];
extern const txt_cmd_s VioletPokecenterFarawayLinkText[];
extern const txt_cmd_s VioletPokecenterMobileAdapterText[];
extern const txt_cmd_s VioletPokecenter1FGameboyKidText[];
extern const txt_cmd_s VioletPokecenter1FGentlemanText[];
extern const txt_cmd_s VioletPokecenter1FYoungsterText[];
