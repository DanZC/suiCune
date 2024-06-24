#pragma once
//// EVENTS
extern const struct MapScripts GoldenrodUndergroundWarehouse_MapScripts;
extern const struct MapEvents GoldenrodUndergroundWarehouse_MapEvents;

//// CODE

bool GoldenrodUndergroundWarehouse_MapScripts_ResetSwitches(script_s* s);
extern const struct TrainerObj TrainerGruntM24;
bool TrainerGruntM24_Script(script_s* s);
extern const struct TrainerObj TrainerGruntM14;
bool TrainerGruntM14_Script(script_s* s);
extern const struct TrainerObj TrainerGruntM15;
bool TrainerGruntM15_Script(script_s* s);
bool GoldenrodUndergroundWarehouseDirectorScript(script_s* s);
extern const struct ItemBall GoldenrodUndergroundWarehouseMaxEther;
extern const struct ItemBall GoldenrodUndergroundWarehouseTMSleepTalk;
extern const struct ItemBall GoldenrodUndergroundWarehouseUltraBall;
extern const txt_cmd_s GruntM24SeenText[];
extern const txt_cmd_s GruntM24BeatenText[];
extern const txt_cmd_s GruntM24AfterBattleText[];
extern const txt_cmd_s GruntM14SeenText[];
extern const txt_cmd_s GruntM14BeatenText[];
extern const txt_cmd_s GruntM14AfterBattleText[];
extern const txt_cmd_s GruntM15SeenText[];
extern const txt_cmd_s GruntM15BeatenText[];
extern const txt_cmd_s GruntM15AfterBattleText[];
extern const txt_cmd_s DirectorIntroText[];
extern const txt_cmd_s DirectorCardKeyText[];
extern const txt_cmd_s DirectorAfterText[];
