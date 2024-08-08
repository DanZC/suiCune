#pragma once
//// EVENTS
extern const struct MapScripts Route18_MapScripts;
extern const struct MapEvents Route18_MapEvents;

//// CODE

extern const struct TrainerObj TrainerBirdKeeperBoris;
bool TrainerBirdKeeperBoris_Script(script_s* s);
extern const struct TrainerObj TrainerBirdKeeperBob;
bool TrainerBirdKeeperBob_Script(script_s* s);
bool Route18Sign(script_s* s);
extern const txt_cmd_s BirdKeeperBorisSeenText[];
extern const txt_cmd_s BirdKeeperBorisBeatenText[];
extern const txt_cmd_s BirdKeeperBorisAfterBattleText[];
extern const txt_cmd_s BirdKeeperBobSeenText[];
extern const txt_cmd_s BirdKeeperBobBeatenText[];
extern const txt_cmd_s BirdKeeperBobAfterBattleText[];
extern const txt_cmd_s Route18SignText[];
