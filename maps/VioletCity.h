#pragma once
//// EVENTS
extern const struct MapScripts VioletCity_MapScripts;
extern const struct MapEvents VioletCity_MapEvents;

//// CODE

bool VioletCity_MapScripts_FlyPoint(script_s* s);
bool VioletCityEarlScript(script_s* s);
bool VioletCityLassScript(script_s* s);
bool VioletCitySuperNerdScript(script_s* s);
bool VioletCityGrampsScript(script_s* s);
bool VioletCityYoungsterScript(script_s* s);
bool VioletCitySign(script_s* s);
bool VioletGymSign(script_s* s);
bool SproutTowerSign(script_s* s);
bool EarlsPokemonAcademySign(script_s* s);
bool VioletCityPokecenterSign(script_s* s);
bool VioletCityMartSign(script_s* s);
extern const struct ItemBall VioletCityPPUp;
extern const struct ItemBall VioletCityRareCandy;
bool VioletCityFruitTree(script_s* s);
extern const struct HiddenItem VioletCityHiddenHyperPotion;
extern const uint8_t VioletCityFollowEarl_MovementData[];
extern const uint8_t VioletCityFinishFollowEarl_MovementData[];
extern const uint8_t VioletCitySpinningEarl_MovementData[];
extern const txt_cmd_s Text_EarlAsksIfYouBeatFalkner[];
extern const txt_cmd_s Text_VeryNiceIndeed[];
extern const txt_cmd_s Text_FollowEarl[];
extern const txt_cmd_s Text_HereTeacherIAm[];
extern const txt_cmd_s VioletCityLassText[];
extern const txt_cmd_s VioletCitySuperNerdText[];
extern const txt_cmd_s VioletCityGrampsText[];
extern const txt_cmd_s VioletCityYoungsterText[];
extern const txt_cmd_s VioletCitySignText[];
extern const txt_cmd_s VioletGymSignText[];
extern const txt_cmd_s SproutTowerSignText[];
extern const txt_cmd_s EarlsPokemonAcademySignText[];
