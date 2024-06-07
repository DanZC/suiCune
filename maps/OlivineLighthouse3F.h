#pragma once
//// EVENTS
extern const struct MapScripts OlivineLighthouse3F_MapScripts;
extern const struct MapEvents OlivineLighthouse3F_MapEvents;

//// CODE

extern const struct TrainerObj TrainerBirdKeeperTheo;
bool TrainerBirdKeeperTheo_Script(script_s* s);
extern const struct TrainerObj TrainerGentlemanPreston;
bool TrainerGentlemanPreston_Script(script_s* s);
extern const struct TrainerObj TrainerSailorTerrell;
bool TrainerSailorTerrell_Script(script_s* s);
extern const struct ItemBall OlivineLighthouse3FEther;
extern const txt_cmd_s BirdKeeperTheoSeenText[];
extern const txt_cmd_s BirdKeeperTheoBeatenText[];
extern const txt_cmd_s BirdKeeperTheoAfterBattleText[];
extern const txt_cmd_s SailorTerrellSeenText[];
extern const txt_cmd_s SailorTerrellBeatenText[];
extern const txt_cmd_s SailorTerrellAfterBattleText[];
extern const txt_cmd_s GentlemanPrestonSeenText[];
extern const txt_cmd_s GentlemanPrestonBeatenText[];
extern const txt_cmd_s GentlemanPrestonAfterBattleText[];
