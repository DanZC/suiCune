#pragma once
//// EVENTS
extern const struct MapScripts Route1_MapScripts;
extern const struct MapEvents Route1_MapEvents;

//// CODE

extern const struct TrainerObj TrainerSchoolboyDanny;
bool TrainerSchoolboyDanny_Script(script_s* s);
extern const struct TrainerObj TrainerCooltrainerfQuinn;
bool TrainerCooltrainerfQuinn_Script(script_s* s);
bool Route1Sign(script_s* s);
bool Route1FruitTree(script_s* s);
extern const txt_cmd_s SchoolboyDannySeenText[];
extern const txt_cmd_s SchoolboyDannyBeatenText[];
extern const txt_cmd_s SchoolboyDannyAfterBattleText[];
extern const txt_cmd_s CooltrainerfQuinnSeenText[];
extern const txt_cmd_s CooltrainerfQuinnBeatenText[];
extern const txt_cmd_s CooltrainerfQuinnAfterBattleText[];
extern const txt_cmd_s Route1SignText[];
