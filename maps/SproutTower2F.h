#pragma once
//// EVENTS
extern const struct MapScripts SproutTower2F_MapScripts;
extern const struct MapEvents SproutTower2F_MapEvents;

//// CODE

extern const struct TrainerObj TrainerSageNico;
bool TrainerSageNico_Script(script_s* s);
extern const struct TrainerObj TrainerSageEdmond;
bool TrainerSageEdmond_Script(script_s* s);
bool SproutTower2FStatue(script_s* s);
extern const struct ItemBall SproutTower2FXAccuracy;
extern const txt_cmd_s SageNicoSeenText[];
extern const txt_cmd_s SageNicoBeatenText[];
extern const txt_cmd_s SageNicoAfterBattleText[];
extern const txt_cmd_s SageEdmondSeenText[];
extern const txt_cmd_s SageEdmondBeatenText[];
extern const txt_cmd_s SageEdmondAfterBattleText[];
extern const txt_cmd_s SproutTower2FStatueText[];
