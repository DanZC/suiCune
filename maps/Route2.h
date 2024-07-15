#pragma once
//// EVENTS
extern const struct MapScripts Route2_MapScripts;
extern const struct MapEvents Route2_MapEvents;

//// CODE

extern const struct TrainerObj TrainerBugCatcherRob;
bool TrainerBugCatcherRob_Script(script_s* s);
extern const struct TrainerObj TrainerBugCatcherEd;
bool TrainerBugCatcherEd_Script(script_s* s);
extern const struct TrainerObj TrainerBugCatcherDoug;
bool TrainerBugCatcherDoug_Script(script_s* s);
bool Route2Sign(script_s* s);
bool Route2DiglettsCaveSign(script_s* s);
extern const struct ItemBall Route2DireHit;
extern const struct ItemBall Route2MaxPotion;
extern const struct ItemBall Route2Carbos;
extern const struct ItemBall Route2Elixer;
bool Route2FruitTree(script_s* s);
extern const struct HiddenItem Route2HiddenMaxEther;
extern const struct HiddenItem Route2HiddenFullHeal;
extern const struct HiddenItem Route2HiddenFullRestore;
extern const struct HiddenItem Route2HiddenRevive;
extern const txt_cmd_s BugCatcherRobSeenText[];
extern const txt_cmd_s BugCatcherRobBeatenText[];
extern const txt_cmd_s BugCatcherRobAfterBattleText[];
extern const txt_cmd_s BugCatcherEdSeenText[];
extern const txt_cmd_s BugCatcherEdBeatenText[];
extern const txt_cmd_s BugCatcherEdAfterBattleText[];
extern const txt_cmd_s BugCatcherDougSeenText[];
extern const txt_cmd_s BugCatcherDougBeatenText[];
extern const txt_cmd_s BugCatcherDougAfterBattleText[];
extern const txt_cmd_s Route2SignText[];
extern const txt_cmd_s Route2DiglettsCaveSignText[];
