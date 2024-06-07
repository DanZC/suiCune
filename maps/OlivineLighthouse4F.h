#pragma once
//// EVENTS
extern const struct MapScripts OlivineLighthouse4F_MapScripts;
extern const struct MapEvents OlivineLighthouse4F_MapEvents;

//// CODE

extern const struct TrainerObj TrainerLassConnie;
bool TrainerLassConnie_Script(script_s* s);
extern const struct TrainerObj TrainerSailorKent;
bool TrainerSailorKent_Script(script_s* s);
extern const txt_cmd_s SailorKentSeenText[];
extern const txt_cmd_s SailorKentBeatenText[];
extern const txt_cmd_s SailorKentAfterBattleText[];
extern const txt_cmd_s LassConnie1SeenText[];
extern const txt_cmd_s LassConnie1BeatenText[];
extern const txt_cmd_s LassConnie1AfterBattleText[];
