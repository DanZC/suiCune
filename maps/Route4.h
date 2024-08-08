#pragma once
//// EVENTS
extern const struct MapScripts Route4_MapScripts;
extern const struct MapEvents Route4_MapEvents;

//// CODE

extern const struct TrainerObj TrainerBirdKeeperHank;
bool TrainerBirdKeeperHank_Script(script_s* s);
extern const struct TrainerObj TrainerPicnickerHope;
bool TrainerPicnickerHope_Script(script_s* s);
extern const struct TrainerObj TrainerPicnickerSharon;
bool TrainerPicnickerSharon_Script(script_s* s);
bool MtMoonSquareSign(script_s* s);
extern const struct ItemBall Route4HPUp;
extern const struct HiddenItem Route4HiddenUltraBall;
extern const txt_cmd_s BirdKeeperHankSeenText[];
extern const txt_cmd_s BirdKeeperHankBeatenText[];
extern const txt_cmd_s BirdKeeperHankAfterBattleText[];
extern const txt_cmd_s PicnickerHopeSeenText[];
extern const txt_cmd_s PicnickerHopeBeatenText[];
extern const txt_cmd_s PicnickerHopeAfterBattleText[];
extern const txt_cmd_s PicnickerSharonSeenText[];
extern const txt_cmd_s PicnickerSharonBeatenText[];
extern const txt_cmd_s PicnickerSharonAfterBattleText[];
extern const txt_cmd_s MtMoonSquareSignText[];
