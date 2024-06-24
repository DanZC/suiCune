#pragma once
//// EVENTS
extern const struct MapScripts RadioTower5F_MapScripts;
extern const struct MapEvents RadioTower5F_MapEvents;

//// CODE

bool RadioTower5F_MapScripts_DummyScene0(script_s* s);
bool RadioTower5F_MapScripts_DummyScene1(script_s* s);
bool RadioTower5F_MapScripts_DummyScene2(script_s* s);
bool FakeDirectorScript(script_s* s);
bool Director(script_s* s);
extern const struct TrainerObj TrainerExecutivef1;
bool TrainerExecutivef1_Script(script_s* s);
bool RadioTower5FRocketBossScene(script_s* s);
bool Ben(script_s* s);
extern const struct ItemBall RadioTower5FUltraBall;
bool RadioTower5FDirectorsOfficeSign(script_s* s);
bool RadioTower5FStudio1Sign(script_s* s);
bool RadioTower5FBookshelf(script_s* s);
extern const uint8_t FakeDirectorMovement[];
extern const uint8_t RadioTower5FDirectorWalksIn[];
extern const uint8_t RadioTower5FDirectorWalksOut[];
extern const uint8_t RadioTower5FPlayerTwoStepsLeftMovement[];
extern const txt_cmd_s FakeDirectorTextBefore1[];
extern const txt_cmd_s FakeDirectorTextBefore2[];
extern const txt_cmd_s FakeDirectorWinText[];
extern const txt_cmd_s FakeDirectorTextAfter[];
extern const txt_cmd_s Executivef1SeenText[];
extern const txt_cmd_s Executivef1BeatenText[];
extern const txt_cmd_s Executivef1AfterBattleText[];
extern const txt_cmd_s RadioTower5FRocketBossBeforeText[];
extern const txt_cmd_s RadioTower5FRocketBossWinText[];
extern const txt_cmd_s RadioTower5FRocketBossAfterText[];
extern const txt_cmd_s RadioTower5FDirectorThankYouText[];
extern const txt_cmd_s RadioTower5FDirectorDescribeClearBellText[];
extern const txt_cmd_s RadioTower5FDirectorText[];
extern const txt_cmd_s BenText[];
extern const txt_cmd_s RadioTower5FDirectorsOfficeSignText[];
extern const txt_cmd_s RadioTower5FStudio1SignText[];
