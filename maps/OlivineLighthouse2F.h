#pragma once
//// EVENTS
extern const struct MapScripts OlivineLighthouse2F_MapScripts;
extern const struct MapEvents OlivineLighthouse2F_MapEvents;

//// CODE

extern const struct TrainerObj TrainerGentlemanAlfred;
bool TrainerGentlemanAlfred_Script(script_s* s);
extern const struct TrainerObj TrainerSailorHuey;
bool TrainerSailorHuey_Script(script_s* s);
extern const txt_cmd_s SailorHueySeenText[];
extern const txt_cmd_s SailorHueyBeatenText[];
extern const txt_cmd_s SailorHueyUnusedText[];
extern const txt_cmd_s GentlemanAlfredSeenText[];
extern const txt_cmd_s GentlemanAlfredBeatenText[];
extern const txt_cmd_s GentlemanAlfredAfterBattleText[];
extern const txt_cmd_s SailorHueyGiveProteinText[];
