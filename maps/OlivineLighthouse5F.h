#pragma once
//// EVENTS
extern const struct MapScripts OlivineLighthouse5F_MapScripts;
extern const struct MapEvents OlivineLighthouse5F_MapEvents;

//// CODE

extern const struct TrainerObj TrainerBirdKeeperDenis;
bool TrainerBirdKeeperDenis_Script(script_s* s);
extern const struct TrainerObj TrainerSailorErnest;
bool TrainerSailorErnest_Script(script_s* s);
extern const struct ItemBall OlivineLighthouse5FRareCandy;
extern const struct ItemBall OlivineLighthouse5FSuperRepel;
extern const struct ItemBall OlivineLighthouse5FTMSwagger;
extern const struct HiddenItem OlivineLighthouse5FHiddenHyperPotion;
extern const txt_cmd_s SailorErnestSeenText[];
extern const txt_cmd_s SailorErnestBeatenText[];
extern const txt_cmd_s SailorErnestAfterBattleText[];
extern const txt_cmd_s BirdKeeperDenisSeenText[];
extern const txt_cmd_s BirdKeeperDenisBeatenText[];
extern const txt_cmd_s BirdKeeperDenisAfterBattleText[];
