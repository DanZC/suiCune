#pragma once
//// EVENTS
extern const struct MapScripts Route34_MapScripts;
extern const struct MapEvents Route34_MapEvents;

//// CODE

bool Route34_MapScripts_EggCheckCallback(script_s* s);
bool Route34_MapScripts_PutDayCareManOutside(script_s* s);
bool Route34_MapScripts_CheckMon1(script_s* s);
bool Route34_MapScripts_HideMon1(script_s* s);
bool Route34_MapScripts_CheckMon2(script_s* s);
bool Route34_MapScripts_HideMon2(script_s* s);
bool DayCareManScript_Outside(script_s* s);
bool DayCareMon1Script(script_s* s);
bool DayCareMon2Script(script_s* s);
extern const struct TrainerObj TrainerCamperTodd1;
bool TrainerCamperTodd1_Script(script_s* s);
extern const struct TrainerObj TrainerPicnickerGina1;
bool TrainerPicnickerGina1_Script(script_s* s);
bool OfficerKeithScript(script_s* s);
extern const struct TrainerObj TrainerYoungsterSamuel;
bool TrainerYoungsterSamuel_Script(script_s* s);
extern const struct TrainerObj TrainerYoungsterIan;
bool TrainerYoungsterIan_Script(script_s* s);
extern const struct TrainerObj TrainerPokefanmBrandon;
bool TrainerPokefanmBrandon_Script(script_s* s);
extern const struct TrainerObj TrainerCooltrainerfIrene;
bool TrainerCooltrainerfIrene_Script(script_s* s);
extern const struct TrainerObj TrainerCooltrainerfJenn;
bool TrainerCooltrainerfJenn_Script(script_s* s);
extern const struct TrainerObj TrainerCooltrainerfKate;
bool TrainerCooltrainerfKate_Script(script_s* s);
bool Route34IlexForestSign(script_s* s);
bool Route34Sign(script_s* s);
bool Route34TrainerTips(script_s* s);
bool DayCareSign(script_s* s);
extern const struct ItemBall Route34Nugget;
extern const struct HiddenItem Route34HiddenRareCandy;
extern const struct HiddenItem Route34HiddenSuperPotion;
extern const uint8_t Route34MovementData_DayCareManWalksBackInside[];
extern const uint8_t Route34MovementData_DayCareManWalksBackInside_WalkAroundPlayer[];
extern const txt_cmd_s YoungsterSamuelSeenText[];
extern const txt_cmd_s YoungsterSamuelBeatenText[];
extern const txt_cmd_s YoungsterSamuelMobileText[];
extern const txt_cmd_s YoungsterSamuelAfterText[];
extern const txt_cmd_s YoungsterIanSeenText[];
extern const txt_cmd_s YoungsterIanBeatenText[];
extern const txt_cmd_s YoungsterIanAfterText[];
extern const txt_cmd_s CamperTodd1SeenText[];
extern const txt_cmd_s CamperTodd1BeatenText[];
extern const txt_cmd_s CamperTodd1AfterText[];
extern const txt_cmd_s CamperToddSaleText[];
extern const txt_cmd_s PicnickerGina1SeenText[];
extern const txt_cmd_s PicnickerGina1BeatenText[];
extern const txt_cmd_s PicnickerGina1AfterText[];
extern const txt_cmd_s OfficerKeithSeenText[];
extern const txt_cmd_s OfficerKeithWinText[];
extern const txt_cmd_s OfficerKeithAfterText[];
extern const txt_cmd_s OfficerKeithDaytimeText[];
extern const txt_cmd_s PokefanmBrandonSeenText[];
extern const txt_cmd_s PokefanmBrandonBeatenText[];
extern const txt_cmd_s PokefanmBrandonAfterText[];
extern const txt_cmd_s CooltrainerfIreneSeenText[];
extern const txt_cmd_s CooltrainerfIreneBeatenText[];
extern const txt_cmd_s CooltrainerfIreneAfterText1[];
extern const txt_cmd_s CooltrainerfIreneAfterText2[];
extern const txt_cmd_s CooltrainerfJennSeenText[];
extern const txt_cmd_s CooltrainerfJennBeatenText[];
extern const txt_cmd_s CooltrainerfJennAfterText1[];
extern const txt_cmd_s CooltrainerfJennAfterText2[];
extern const txt_cmd_s CooltrainerfKateSeenText[];
extern const txt_cmd_s CooltrainerfKateBeatenText[];
extern const txt_cmd_s CooltrainerfKateOfferSoftSandText[];
extern const txt_cmd_s CooltrainerfKateAfterText[];
extern const txt_cmd_s Route34IlexForestSignText[];
extern const txt_cmd_s Route34SignText[];
extern const txt_cmd_s Route34TrainerTipsText[];
extern const txt_cmd_s DayCareSignText[];
