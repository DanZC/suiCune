#pragma once
//// EVENTS
extern const struct MapScripts SproutTower1F_MapScripts;
extern const struct MapEvents SproutTower1F_MapEvents;

//// CODE

bool SproutTower1FSage1Script(script_s* s);
bool SproutTower1FSage2Script(script_s* s);
bool SproutTower1FGrannyScript(script_s* s);
bool SproutTower1FTeacherScript(script_s* s);
extern const struct TrainerObj TrainerSageChow;
bool TrainerSageChow_Script(script_s* s);
extern const struct ItemBall SproutTower1FParlyzHeal;
bool SproutTower1FStatue(script_s* s);
extern const txt_cmd_s SageChowSeenText[];
extern const txt_cmd_s SageChowBeatenText[];
extern const txt_cmd_s SageChowAfterBattleText[];
extern const txt_cmd_s SproutTower1FSage1Text[];
extern const txt_cmd_s SproutTower1FSage2Text[];
extern const txt_cmd_s SproutTower1FGrannyText[];
extern const txt_cmd_s SproutTower1FTeacherText[];
extern const txt_cmd_s SproutTower1FStatueText[];
