#pragma once
//// EVENTS
extern const struct MapScripts CherrygroveCity_MapScripts;
extern const struct MapEvents CherrygroveCity_MapEvents;

//// CODE

bool CherrygroveCity_MapScripts_DummyScene0(script_s* s);
bool CherrygroveCity_MapScripts_DummyScene1(script_s* s);
bool CherrygroveCity_MapScripts_FlyPoint(script_s* s);
bool CherrygroveCityGuideGent(script_s* s);
bool CherrygroveSilverSceneSouth(script_s* s);
bool CherrygroveSilverSceneNorth(script_s* s);
bool CherrygroveTeacherScript(script_s* s);
bool CherrygroveYoungsterScript(script_s* s);
bool MysticWaterGuy(script_s* s);
bool CherrygroveCitySign(script_s* s);
bool GuideGentsHouseSign(script_s* s);
bool CherrygroveCityPokecenterSign(script_s* s);
bool CherrygroveCityMartSign(script_s* s);
extern const uint8_t GuideGentMovement1[];
extern const uint8_t GuideGentMovement2[];
extern const uint8_t GuideGentMovement3[];
extern const uint8_t GuideGentMovement4[];
extern const uint8_t GuideGentMovement5[];
extern const uint8_t GuideGentMovement6[];
extern const uint8_t CherrygroveCity_RivalWalksToYou[];
extern const uint8_t CherrygroveCity_RivalPushesYouOutOfTheWay[];
extern const uint8_t CherrygroveCity_UnusedMovementData[];
extern const uint8_t CherrygroveCity_RivalExitsStageLeft[];
extern const txt_cmd_s GuideGentIntroText[];
extern const txt_cmd_s GuideGentTourText1[];
extern const txt_cmd_s GuideGentPokecenterText[];
extern const txt_cmd_s GuideGentMartText[];
extern const txt_cmd_s GuideGentRoute30Text[];
extern const txt_cmd_s GuideGentSeaText[];
extern const txt_cmd_s GuideGentGiftText[];
extern const txt_cmd_s GotMapCardText[];
extern const txt_cmd_s GuideGentPokegearText[];
extern const txt_cmd_s GuideGentNoText[];
extern const txt_cmd_s CherrygroveRivalText_Seen[];
extern const txt_cmd_s SilverCherrygroveWinText[];
extern const txt_cmd_s CherrygroveRivalText_YouLost[];
extern const txt_cmd_s SilverCherrygroveLossText[];
extern const txt_cmd_s CherrygroveRivalText_YouWon[];
extern const txt_cmd_s CherrygroveTeacherText_NoMapCard[];
extern const txt_cmd_s CherrygroveTeacherText_HaveMapCard[];
extern const txt_cmd_s CherrygroveYoungsterText_NoPokedex[];
extern const txt_cmd_s CherrygroveYoungsterText_HavePokedex[];
extern const txt_cmd_s MysticWaterGuyTextBefore[];
extern const txt_cmd_s MysticWaterGuyTextAfter[];
extern const txt_cmd_s CherrygroveCitySignText[];
extern const txt_cmd_s GuideGentsHouseSignText[];
