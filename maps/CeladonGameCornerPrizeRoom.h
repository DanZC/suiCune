#pragma once
//// EVENTS
extern const struct MapScripts CeladonGameCornerPrizeRoom_MapScripts;
extern const struct MapEvents CeladonGameCornerPrizeRoom_MapEvents;

//// CODE

bool CeladonGameCornerPrizeRoomGentlemanScript(script_s* s);
bool CeladonGameCornerPrizeRoomPharmacistScript(script_s* s);
bool CeladonGameCornerPrizeRoomTMVendor(script_s* s);
bool CeladonPrizeRoom_tmcounterloop(script_s* s);
bool CeladonPrizeRoom_askbuy(script_s* s);
bool CeladonPrizeRoom_purchased(script_s* s);
bool CeladonPrizeRoom_notenoughcoins(script_s* s);
bool CeladonPrizeRoom_notenoughroom(script_s* s);
bool CeladonPrizeRoom_CancelPurchaseScript(script_s* s);
bool CeladonPrizeRoom_NoCoinCase(script_s* s);
extern const struct MenuHeader CeladonPrizeRoom_TMMenuHeader;
bool CeladonGameCornerPrizeRoomPokemonVendor(script_s* s);
extern const txt_cmd_s CeladonGameCornerPrizeRoomGentlemanText[];
extern const txt_cmd_s CeladonGameCornerPrizeRoomPharmacistText[];
extern const txt_cmd_s CeladonPrizeRoom_PrizeVendorIntroText[];
extern const txt_cmd_s CeladonPrizeRoom_AskWhichPrizeText[];
extern const txt_cmd_s CeladonPrizeRoom_ConfirmPurchaseText[];
extern const txt_cmd_s CeladonPrizeRoom_HereYouGoText[];
extern const txt_cmd_s CeladonPrizeRoom_NotEnoughCoinsText[];
extern const txt_cmd_s CeladonPrizeRoom_NotEnoughRoomText[];
extern const txt_cmd_s CeladonPrizeRoom_ComeAgainText[];
extern const txt_cmd_s CeladonPrizeRoom_NoCoinCaseText[];
