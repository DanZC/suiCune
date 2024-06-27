#pragma once
//// EVENTS
extern const struct MapScripts BlackthornGym1F_MapScripts;
extern const struct MapEvents BlackthornGym1F_MapEvents;

//// CODE

bool BlackthornGym1F_MapScripts_Boulders(script_s* s);
bool BlackthornGymClairScript(script_s* s);
extern const struct TrainerObj TrainerCooltrainermPaul;
bool TrainerCooltrainermPaul_Script(script_s* s);
extern const struct TrainerObj TrainerCooltrainermMike;
bool TrainerCooltrainermMike_Script(script_s* s);
extern const struct TrainerObj TrainerCooltrainerfLola;
bool TrainerCooltrainerfLola_Script(script_s* s);
bool BlackthornGymGuideScript(script_s* s);
bool BlackthornGymStatue(script_s* s);
extern const txt_cmd_s ClairIntroText[];
extern const txt_cmd_s ClairWinText[];
extern const txt_cmd_s ClairText_GoToDragonsDen[];
extern const txt_cmd_s ClairText_TooMuchToExpect[];
extern const txt_cmd_s BlackthornGymClairText_YouKeptMeWaiting[];
extern const txt_cmd_s BlackthornGymText_ReceivedTM24[];
extern const txt_cmd_s BlackthornGymClairText_DescribeTM24[];
extern const txt_cmd_s BlackthornGymClairText_BagFull[];
extern const txt_cmd_s BlackthornGymClairText_League[];
extern const txt_cmd_s CooltrainermPaulSeenText[];
extern const txt_cmd_s CooltrainermPaulBeatenText[];
extern const txt_cmd_s CooltrainermPaulAfterBattleText[];
extern const txt_cmd_s CooltrainermMikeSeenText[];
extern const txt_cmd_s CooltrainermMikeBeatenText[];
extern const txt_cmd_s CooltrainermMikeAfterBattleText[];
extern const txt_cmd_s CooltrainerfLolaSeenText[];
extern const txt_cmd_s CooltrainerfLolaBeatenText[];
extern const txt_cmd_s CooltrainerfLolaAfterBattleText[];
extern const txt_cmd_s BlackthornGymGuideText[];
extern const txt_cmd_s BlackthornGymGuideWinText[];
