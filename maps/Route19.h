#pragma once
//// EVENTS
extern const struct MapScripts Route19_MapScripts;
extern const struct MapEvents Route19_MapEvents;

//// CODE

bool Route19_MapScripts_ClearRocks(script_s* s);
extern const struct TrainerObj TrainerSwimmerfDawn;
bool TrainerSwimmerfDawn_Script(script_s* s);
extern const struct TrainerObj TrainerSwimmermHarold;
bool TrainerSwimmermHarold_Script(script_s* s);
extern const struct TrainerObj TrainerSwimmermJerome;
bool TrainerSwimmermJerome_Script(script_s* s);
extern const struct TrainerObj TrainerSwimmermTucker;
bool TrainerSwimmermTucker_Script(script_s* s);
bool Route19Fisher1Script(script_s* s);
bool Route19Fisher2Script(script_s* s);
bool Route19Sign(script_s* s);
bool CarefulSwimmingSign(script_s* s);
extern const txt_cmd_s SwimmermHaroldSeenText[];
extern const txt_cmd_s SwimmermHaroldBeatenText[];
extern const txt_cmd_s SwimmermHaroldAfterBattleText[];
extern const txt_cmd_s SwimmermTuckerSeenText[];
extern const txt_cmd_s SwimmermTuckerBeatenText[];
extern const txt_cmd_s SwimmermTuckerAfterBattleText[];
extern const txt_cmd_s SwimmerfDawnSeenText[];
extern const txt_cmd_s SwimmerfDawnBeatenText[];
extern const txt_cmd_s SwimmerfDawnAfterBattleText[];
extern const txt_cmd_s SwimmermJeromeSeenText[];
extern const txt_cmd_s SwimmermJeromeBeatenText[];
extern const txt_cmd_s SwimmermJeromeAfterBattleText[];
extern const txt_cmd_s Route19Fisher1Text[];
extern const txt_cmd_s Route19Fisher1Text_RocksCleared[];
extern const txt_cmd_s Route19Fisher2Text[];
extern const txt_cmd_s Route19Fisher2Text_RocksCleared[];
extern const txt_cmd_s Route19SignText[];
extern const txt_cmd_s CarefulSwimmingSignText[];
