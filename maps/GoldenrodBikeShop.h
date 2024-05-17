#pragma once
//// EVENTS
extern const struct MapScripts GoldenrodBikeShop_MapScripts;
extern const struct MapEvents GoldenrodBikeShop_MapEvents;

//// CODE

bool GoldenrodBikeShop_MapScripts_DummyScene(script_s* s);
bool GoldenrodBikeShopClerkScript(script_s* s);
bool GoldenrodBikeShopJustReleasedCompactBike(script_s* s);
bool GoldenrodBikeShopBicycle(script_s* s);
extern const txt_cmd_s GoldenrodBikeShopClerkIntroText[];
extern const txt_cmd_s GoldenrodBikeShopClerkAgreedText[];
extern const txt_cmd_s BorrowedABicycleText[];
extern const txt_cmd_s GoldenrodBikeShopClerkFirstRateBikesText[];
extern const txt_cmd_s GoldenrodBikeShopClerkRefusedText[];
extern const txt_cmd_s GoldenrodBikeShopJustReleasedCompactBikeText[];
extern const txt_cmd_s GoldenrodBikeShopBicycleText[];
