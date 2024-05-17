#pragma once
//// EVENTS
extern const struct MapScripts GoldenrodGameCorner_MapScripts;
extern const struct MapEvents GoldenrodGameCorner_MapEvents;

//// CODE

bool GoldenrodGameCorner_MapScripts_MoveTutor(script_s* s);
bool GoldenrodGameCorner_MapScripts_move_tutor_inside(script_s* s);
bool GoldenrodGameCorner_MapScripts_move_tutor_outside(script_s* s);
bool GoldenrodGameCorner_MapScripts_finish(script_s* s);
bool MoveTutorInsideScript(script_s* s);
bool GoldenrodGameCornerCoinVendorScript(script_s* s);
bool GoldenrodGameCornerTMVendorScript(script_s* s);
bool GoldenrodGameCornerTMVendor_LoopScript(script_s* s);
bool GoldenrodGameCornerPrizeVendor_ConfirmPurchaseScript(script_s* s);
bool GoldenrodGameCornerTMVendor_FinishScript(script_s* s);
bool GoldenrodGameCornerPrizeVendor_NotEnoughCoinsScript(script_s* s);
bool GoldenrodGameCornerPrizeMonVendor_NoRoomForPrizeScript(script_s* s);
bool GoldenrodGameCornerPrizeVendor_CancelPurchaseScript(script_s* s);
bool GoldenrodGameCornerPrizeVendor_NoCoinCaseScript(script_s* s);
// bool GoldenrodGameCornerTMVendorMenuHeader(script_s* s);
bool GoldenrodGameCornerPrizeMonVendorScript(script_s* s);
bool GoldenrodGameCornerPharmacistScript(script_s* s);
bool GoldenrodGameCornerPokefanM1Script(script_s* s);
bool GoldenrodGameCornerCooltrainerMScript(script_s* s);
bool GoldenrodGameCornerPokefanFScript(script_s* s);
bool GoldenrodGameCornerCooltrainerFScript(script_s* s);
bool GoldenrodGameCornerGentlemanScript(script_s* s);
bool GoldenrodGameCornerPokefanM2Script(script_s* s);
bool GoldenrodGameCornerLeftTheirDrinkScript(script_s* s);
bool GoldenrodGameCornerSlotsMachineScript(script_s* s);
bool GoldenrodGameCornerLuckySlotsMachineScript(script_s* s);
bool GoldenrodGameCornerCardFlipMachineScript(script_s* s);
extern const txt_cmd_s GoldenrodGameCornerPrizeVendorIntroText[];
extern const txt_cmd_s GoldenrodGameCornerPrizeVendorWhichPrizeText[];
extern const txt_cmd_s GoldenrodGameCornerPrizeVendorConfirmPrizeText[];
extern const txt_cmd_s GoldenrodGameCornerPrizeVendorHereYouGoText[];
extern const txt_cmd_s GoldenrodGameCornerPrizeVendorNeedMoreCoinsText[];
extern const txt_cmd_s GoldenrodGameCornerPrizeVendorNoMoreRoomText[];
extern const txt_cmd_s GoldenrodGameCornerPrizeVendorQuitText[];
extern const txt_cmd_s GoldenrodGameCornerPrizeVendorNoCoinCaseText[];
extern const txt_cmd_s GoldenrodGameCornerPharmacistText[];
extern const txt_cmd_s GoldenrodGameCornerPokefanM1Text[];
extern const txt_cmd_s GoldenrodGameCornerCooltrainerMText[];
extern const txt_cmd_s GoldenrodGameCornerPokefanFText[];
extern const txt_cmd_s GoldenrodGameCornerCooltrainerFText[];
extern const txt_cmd_s GoldenrodGameCornerGentlemanText[];
extern const txt_cmd_s GoldenrodGameCornerPokefanM2Text[];
extern const txt_cmd_s MoveTutorInsideText[];
extern const txt_cmd_s GoldenrodGameCornerLeftTheirDrinkText[];
