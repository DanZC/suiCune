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
extern const struct TextCmd GuideGentIntroText[];
extern const struct TextCmd GuideGentTourText1[];
extern const struct TextCmd GuideGentPokecenterText[];
extern const struct TextCmd GuideGentMartText[];
extern const struct TextCmd GuideGentRoute30Text[];
extern const struct TextCmd GuideGentSeaText[];
extern const struct TextCmd GuideGentGiftText[];
extern const struct TextCmd GotMapCardText[];
extern const struct TextCmd GuideGentPokegearText[];
extern const struct TextCmd GuideGentNoText[];
extern const struct TextCmd CherrygroveRivalText_Seen[];
extern const struct TextCmd SilverCherrygroveWinText[];
extern const struct TextCmd CherrygroveRivalText_YouLost[];
extern const struct TextCmd SilverCherrygroveLossText[];
extern const struct TextCmd CherrygroveRivalText_YouWon[];
extern const struct TextCmd CherrygroveTeacherText_NoMapCard[];
extern const struct TextCmd CherrygroveTeacherText_HaveMapCard[];
extern const struct TextCmd CherrygroveYoungsterText_NoPokedex[];
extern const struct TextCmd CherrygroveYoungsterText_HavePokedex[];
extern const struct TextCmd MysticWaterGuyTextBefore[];
extern const struct TextCmd MysticWaterGuyTextAfter[];
extern const struct TextCmd CherrygroveCitySignText[];
extern const struct TextCmd GuideGentsHouseSignText[];
