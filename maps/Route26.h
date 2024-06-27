#pragma once
//// EVENTS
extern const struct MapScripts Route26_MapScripts;
extern const struct MapEvents Route26_MapEvents;

//// CODE

extern const struct TrainerObj TrainerCooltrainermJake;
bool TrainerCooltrainermJake_Script(script_s* s);
extern const struct TrainerObj TrainerCooltrainermGaven3;
bool TrainerCooltrainermGaven3_Script(script_s* s);
extern const struct TrainerObj TrainerCooltrainerfJoyce;
bool TrainerCooltrainerfJoyce_Script(script_s* s);
extern const struct TrainerObj TrainerCooltrainerfBeth1;
bool TrainerCooltrainerfBeth1_Script(script_s* s);
extern const struct TrainerObj TrainerPsychicRichard;
bool TrainerPsychicRichard_Script(script_s* s);
extern const struct TrainerObj TrainerFisherScott;
bool TrainerFisherScott_Script(script_s* s);
bool Route26Sign(script_s* s);
bool Route26FruitTree(script_s* s);
extern const struct ItemBall Route26MaxElixer;
extern const txt_cmd_s CooltrainermJakeSeenText[];
extern const txt_cmd_s CooltrainermJakeBeatenText[];
extern const txt_cmd_s CooltrainermJakeAfterBattleText[];
extern const txt_cmd_s CooltrainermGaven3SeenText[];
extern const txt_cmd_s CooltrainermGaven3BeatenText[];
extern const txt_cmd_s CooltrainermGavenAfterText[];
extern const txt_cmd_s CooltrainerfJoyceSeenText[];
extern const txt_cmd_s CooltrainerfJoyceBeatenText[];
extern const txt_cmd_s CooltrainerfJoyceAfterBattleText[];
extern const txt_cmd_s CooltrainerfBeth1SeenText[];
extern const txt_cmd_s CooltrainerfBeth1BeatenText[];
extern const txt_cmd_s CooltrainerfBethAfterText[];
extern const txt_cmd_s PsychicRichardSeenText[];
extern const txt_cmd_s PsychicRichardBeatenText[];
extern const txt_cmd_s PsychicRichardAfterBattleText[];
extern const txt_cmd_s FisherScottSeenText[];
extern const txt_cmd_s FisherScottBeatenText[];
extern const txt_cmd_s FisherScottAfterBattleText[];
extern const txt_cmd_s Route26SignText[];
