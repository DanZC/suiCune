#pragma once
//// EVENTS
extern const struct MapScripts Route12_MapScripts;
extern const struct MapEvents Route12_MapEvents;

//// CODE

extern const struct TrainerObj TrainerFisherKyle;
bool TrainerFisherKyle_Script(script_s* s);
extern const struct TrainerObj TrainerFisherMartin;
bool TrainerFisherMartin_Script(script_s* s);
extern const struct TrainerObj TrainerFisherStephen;
bool TrainerFisherStephen_Script(script_s* s);
extern const struct TrainerObj TrainerFisherBarney;
bool TrainerFisherBarney_Script(script_s* s);
bool Route12Sign(script_s* s);
bool FishingSpotSign(script_s* s);
extern const struct ItemBall Route12Calcium;
extern const struct ItemBall Route12Nugget;
extern const struct HiddenItem Route12HiddenElixer;
extern const txt_cmd_s FisherMartinSeenText[];
extern const txt_cmd_s FisherMartinBeatenText[];
extern const txt_cmd_s FisherMartinAfterBattleText[];
extern const txt_cmd_s FisherStephenSeenText[];
extern const txt_cmd_s FisherStephenBeatenText[];
extern const txt_cmd_s FisherStephenAfterBattleText[];
extern const txt_cmd_s FisherBarneySeenText[];
extern const txt_cmd_s FisherBarneyBeatenText[];
extern const txt_cmd_s FisherBarneyAfterBattleText[];
extern const txt_cmd_s FisherKyleSeenText[];
extern const txt_cmd_s FisherKyleBeatenText[];
extern const txt_cmd_s FisherKyleAfterBattleText[];
extern const txt_cmd_s Route12SignText[];
extern const txt_cmd_s FishingSpotSignText[];
