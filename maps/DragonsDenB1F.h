#pragma once
//// EVENTS
extern const struct MapScripts DragonsDenB1F_MapScripts;
extern const struct MapEvents DragonsDenB1F_MapEvents;

//// CODE

bool DragonsDenB1F_MapScripts_DummyScene0(script_s* s);
bool DragonsDenB1F_MapScripts_DummyScene1(script_s* s);
bool DragonsDenB1F_MapScripts_CheckSilver(script_s* s);
bool DragonsDenB1F_MapScripts_CheckDay(script_s* s);
bool DragonsDenB1F_MapScripts_AppearSilver(script_s* s);
bool DragonsDenB1F_ClairScene(script_s* s);
extern const struct TrainerObj TrainerCooltrainermDarin;
bool TrainerCooltrainermDarin_Script(script_s* s);
extern const struct TrainerObj TrainerCooltrainerfCara;
bool TrainerCooltrainerfCara_Script(script_s* s);
extern const struct TrainerObj TrainerTwinsLeaandpia1;
bool TrainerTwinsLeaandpia1_Script(script_s* s);
extern const struct TrainerObj TrainerTwinsLeaandpia2;
bool TrainerTwinsLeaandpia2_Script(script_s* s);
bool DragonsDenB1FDragonFangScript(script_s* s);
bool DragonsDenB1FSilverScript(script_s* s);
bool DragonShrineSignpost(script_s* s);
extern const struct ItemBall DragonsDenB1FCalcium;
extern const struct ItemBall DragonsDenB1FMaxElixer;
extern const struct HiddenItem DragonsDenB1FHiddenRevive;
extern const struct HiddenItem DragonsDenB1FHiddenMaxPotion;
extern const struct HiddenItem DragonsDenB1FHiddenMaxElixer;
extern const uint8_t MovementDragonsDen_ClairWalksToYou[];
extern const uint8_t MovementDragonsDen_ClairWalksAway[];
extern const txt_cmd_s ClairText_Wait[];
extern const txt_cmd_s ClairText_GiveDragonbreathDragonDen[];
extern const txt_cmd_s Text_ReceivedTM24[];
extern const txt_cmd_s ClairText_DescribeDragonbreathDragonDen[];
extern const txt_cmd_s ClairText_NoRoom[];
extern const txt_cmd_s ClairText_WhatsTheMatterDragonDen[];
extern const txt_cmd_s DragonShrineSignpostText[];
extern const txt_cmd_s SilverText_Training1[];
extern const txt_cmd_s SilverText_Training2[];
extern const txt_cmd_s CooltrainermDarinSeenText[];
extern const txt_cmd_s CooltrainermDarinBeatenText[];
extern const txt_cmd_s CooltrainermDarinAfterBattleText[];
extern const txt_cmd_s CooltrainerfCaraSeenText[];
extern const txt_cmd_s CooltrainerfCaraBeatenText[];
extern const txt_cmd_s CooltrainerfCaraAfterBattleText[];
extern const txt_cmd_s TwinsLeaandpia1SeenText[];
extern const txt_cmd_s TwinsLeaandpia1BeatenText[];
extern const txt_cmd_s TwinsLeaandpia1AfterBattleText[];
extern const txt_cmd_s TwinsLeaandpia2SeenText[];
extern const txt_cmd_s TwinsLeaandpia2BeatenText[];
extern const txt_cmd_s TwinsLeaandpia2AfterBattleText[];
extern const txt_cmd_s Text_FoundDragonFang[];
extern const txt_cmd_s Text_NoRoomForDragonFang[];
