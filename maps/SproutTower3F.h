#pragma once
//// EVENTS
extern const struct MapScripts SproutTower3F_MapScripts;
extern const struct MapEvents SproutTower3F_MapEvents;

//// CODE

bool SproutTower3F_MapScripts_DummyScene0(script_s* s);
bool SproutTower3F_MapScripts_DummyScene1(script_s* s);
bool SproutTower3FRivalScene(script_s* s);
bool SageLiScript(script_s* s);
extern const struct TrainerObj TrainerSageJin;
bool TrainerSageJin_Script(script_s* s);
extern const struct TrainerObj TrainerSageTroy;
bool TrainerSageTroy_Script(script_s* s);
extern const struct TrainerObj TrainerSageNeal;
bool TrainerSageNeal_Script(script_s* s);
bool SproutTower3FPainting(script_s* s);
bool SproutTower3FStatue(script_s* s);
extern const struct ItemBall SproutTower3FPotion;
extern const struct ItemBall SproutTower3FEscapeRope;
extern const uint8_t SproutTower3FPlayerApproachesRivalMovement[];
extern const uint8_t SproutTower3FRivalApproachesElderMovement[];
extern const uint8_t SproutTower3FRivalLeavesElderMovement[];
extern const txt_cmd_s SproutTowerElderLecturesRivalText[];
extern const txt_cmd_s SproutTowerRivalOnlyCareAboutStrongText[];
extern const txt_cmd_s SproutTowerRivalUsedEscapeRopeText[];
extern const txt_cmd_s SageLiSeenText[];
extern const txt_cmd_s SageLiBeatenText[];
extern const txt_cmd_s SageLiTakeThisFlashText[];
extern const txt_cmd_s SageLiFlashExplanationText[];
extern const txt_cmd_s SageLiAfterBattleText[];
extern const txt_cmd_s SageJinSeenText[];
extern const txt_cmd_s SageJinBeatenText[];
extern const txt_cmd_s SageJinAfterBattleText[];
extern const txt_cmd_s SageTroySeenText[];
extern const txt_cmd_s SageTroyBeatenText[];
extern const txt_cmd_s SageTroyAfterBattleText[];
extern const txt_cmd_s SageNealSeenText[];
extern const txt_cmd_s SageNealBeatenText[];
extern const txt_cmd_s SageNealAfterBattleText[];
extern const txt_cmd_s SproutTower3FPaintingText[];
extern const txt_cmd_s SproutTower3FStatueText[];
