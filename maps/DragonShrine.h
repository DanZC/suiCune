#pragma once
//// EVENTS
extern const struct MapScripts DragonShrine_MapScripts;
extern const struct MapEvents DragonShrine_MapEvents;

//// CODE

bool DragonShrine_MapScripts_DragonShrineTest(script_s* s);
bool DragonShrine_MapScripts_DummyScene(script_s* s);
bool DragonShrine_MapScripts_DragonShrineTestScript(script_s* s);
bool DragonShrineElder1Script(script_s* s);
bool DragonShrineElder2Script(script_s* s);
bool DragonShrineElder3Script(script_s* s);
extern const struct MenuHeader DragonShrineQuestion1_MenuHeader;
extern const struct MenuHeader DragonShrineQuestion2_MenuHeader;
extern const struct MenuHeader DragonShrineQuestion3_MenuHeader;
extern const struct MenuHeader DragonShrineQuestion4_MenuHeader;
extern const struct MenuHeader DragonShrineQuestion5_MenuHeader;
extern const uint8_t DragonShrinePlayerWalkInMovement[];
extern const uint8_t DragonShrineElderStepDownMovement[];
extern const uint8_t DragonShrineElderWalkToClairMovement[];
extern const uint8_t DragonShrineElderWalkAway1Movement[];
extern const uint8_t DragonShrineElderWalkAway2Movement[];
extern const uint8_t DragonShrineClairWalkInMovement[];
extern const uint8_t DragonShrineClairBigStepLeftMovement[];
extern const uint8_t DragonShrineClairSlowStepLeftMovement[];
extern const uint8_t DragonShrineClairTwoSlowStepsRightMovement[];
extern const uint8_t DragonShrineClairWalkOutMovement[];
extern const txt_cmd_s DragonShrineElderGreetingText[];
extern const txt_cmd_s DragonShrineQuestion1Text[];
extern const txt_cmd_s DragonShrineQuestion2Text[];
extern const txt_cmd_s DragonShrineQuestion3Text[];
extern const txt_cmd_s DragonShrineQuestion4Text[];
extern const txt_cmd_s DragonShrineQuestion5Text[];
extern const txt_cmd_s DragonShrinePassedTestText[];
extern const txt_cmd_s DragonShrineMustIInformLanceText[];
extern const txt_cmd_s DragonShrineElderScoldsClairText[];
extern const txt_cmd_s DragonShrineComeAgainText[];
extern const txt_cmd_s DragonShrineTakeThisDratiniText[];
extern const txt_cmd_s DragonShrinePlayerReceivedDratiniText[];
extern const txt_cmd_s DragonShrinePartyFullText[];
extern const txt_cmd_s DragonShrineSymbolicDragonText[];
extern const txt_cmd_s DragonShrineClairsGrandfatherText[];
extern const txt_cmd_s DragonShrineSilverIsInTrainingText[];
extern const txt_cmd_s DragonShrineWrongAnswerText1[];
extern const txt_cmd_s DragonShrineWrongAnswerText2[];
extern const txt_cmd_s DragonShrineRightAnswerText[];
extern const txt_cmd_s DragonShrineElder2Text[];
extern const txt_cmd_s DragonShrineElder3Text[];
extern const txt_cmd_s DragonShrineClairYouPassedText[];
extern const txt_cmd_s DragonShrineClairThatCantBeText[];
extern const txt_cmd_s DragonShrineClairYoureLyingText[];
extern const txt_cmd_s DragonShrineIUnderstandText[];
extern const txt_cmd_s DragonShrineHereRisingBadgeText[];
extern const txt_cmd_s DragonShrinePlayerReceivedRisingBadgeText[];
extern const txt_cmd_s DragonShrineRisingBadgeExplanationText[];
extern const txt_cmd_s DragonShrineSpeechlessText[];
