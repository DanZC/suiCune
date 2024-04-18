#pragma once
//// EVENTS
extern const struct MapScripts UnionCaveB2F_MapScripts;
extern const struct MapEvents UnionCaveB2F_MapEvents;

//// CODE

bool UnionCaveB2F_MapScripts_Lapras(script_s* s);
bool UnionCaveB2F_MapScripts_NoAppear(script_s* s);
bool UnionCaveB2F_MapScripts_Appear(script_s* s);
bool UnionCaveLapras(script_s* s);
extern const struct TrainerObj TrainerCooltrainermNick;
bool TrainerCooltrainermNick_Script(script_s* s);
extern const struct TrainerObj TrainerCooltrainerfGwen;
bool TrainerCooltrainerfGwen_Script(script_s* s);
extern const struct TrainerObj TrainerCooltrainerfEmma;
bool TrainerCooltrainerfEmma_Script(script_s* s);
extern const struct ItemBall UnionCaveB2FElixer;
extern const struct ItemBall UnionCaveB2FHyperPotion;
extern const txt_cmd_s CooltrainermNickSeenText[];
extern const txt_cmd_s CooltrainermNickBeatenText[];
extern const txt_cmd_s CooltrainermNickAfterBattleText[];
extern const txt_cmd_s CooltrainerfGwenSeenText[];
extern const txt_cmd_s CooltrainerfGwenBeatenText[];
extern const txt_cmd_s CooltrainerfGwenAfterBattleText[];
extern const txt_cmd_s CooltrainerfEmmaSeenText[];
extern const txt_cmd_s CooltrainerfEmmaBeatenText[];
extern const txt_cmd_s CooltrainerfEmmaAfterBattleText[];
