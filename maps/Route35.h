#pragma once
//// EVENTS
extern const struct MapScripts Route35_MapScripts;
extern const struct MapEvents Route35_MapEvents;

//// CODE

extern const struct TrainerObj TrainerBirdKeeperBryan;
bool TrainerBirdKeeperBryan_Script(script_s* s);
extern const struct TrainerObj TrainerJugglerIrwin;
bool TrainerJugglerIrwin_Script(script_s* s);
bool Route35AskNumber1M(script_s* s);
bool Route35AskNumber2M(script_s* s);
bool Route35RegisteredNumberM(script_s* s);
bool Route35NumberAcceptedM(script_s* s);
bool Route35NumberDeclinedM(script_s* s);
bool Route35PhoneFullM(script_s* s);
bool Route35RematchM(script_s* s);
extern const struct TrainerObj TrainerCamperIvan;
bool TrainerCamperIvan_Script(script_s* s);
extern const struct TrainerObj TrainerCamperElliot;
bool TrainerCamperElliot_Script(script_s* s);
extern const struct TrainerObj TrainerPicnickerBrooke;
bool TrainerPicnickerBrooke_Script(script_s* s);
extern const struct TrainerObj TrainerPicnickerKim;
bool TrainerPicnickerKim_Script(script_s* s);
extern const struct TrainerObj TrainerBugCatcherArnie;
bool TrainerBugCatcherArnie_Script(script_s* s);
extern const struct TrainerObj TrainerFirebreatherWalt;
bool TrainerFirebreatherWalt_Script(script_s* s);
bool TrainerOfficerDirk(script_s* s);
bool Route35Sign(script_s* s);
extern const struct ItemBall Route35TMRollout;
bool Route35FruitTree(script_s* s);
extern const txt_cmd_s CamperIvanSeenText[];
extern const txt_cmd_s CamperIvanBeatenText[];
extern const txt_cmd_s CamperIvanAfterBattleText[];
extern const txt_cmd_s CamperElliotSeenText[];
extern const txt_cmd_s CamperElliotBeatenText[];
extern const txt_cmd_s CamperElliotAfterBattleText[];
extern const txt_cmd_s PicnickerBrookeSeenText[];
extern const txt_cmd_s PicnickerBrookeBeatenText[];
extern const txt_cmd_s PicnickerBrookeAfterBattleText[];
extern const txt_cmd_s PicnickerKimSeenText[];
extern const txt_cmd_s PicnickerKimBeatenText[];
extern const txt_cmd_s PicnickerKimAfterBattleText[];
extern const txt_cmd_s BirdKeeperBryanSeenText[];
extern const txt_cmd_s BirdKeeperBryanBeatenText[];
extern const txt_cmd_s BirdKeeperBryanAfterBattleText[];
extern const txt_cmd_s JugglerIrwin1SeenText[];
extern const txt_cmd_s JugglerIrwin1BeatenText[];
extern const txt_cmd_s JugglerIrwinAfterBattleText[];
extern const txt_cmd_s BugCatcherArnieSeenText[];
extern const txt_cmd_s BugCatcherArnieBeatenText[];
extern const txt_cmd_s BugCatcherArnieAfterBattleText[];
extern const txt_cmd_s BugCatcherArnieYanmaText[];
extern const txt_cmd_s FirebreatherWaltSeenText[];
extern const txt_cmd_s FirebreatherWaltBeatenText[];
extern const txt_cmd_s FirebreatherWaltAfterBattleText[];
extern const txt_cmd_s OfficerDirkSeenText[];
extern const txt_cmd_s OfficerDirkBeatenText[];
extern const txt_cmd_s OfficerDirkAfterBattleText[];
extern const txt_cmd_s OfficerDirkPrettyToughText[];
extern const txt_cmd_s Route35SignText[];