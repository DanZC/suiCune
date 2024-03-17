#pragma once
//// EVENTS
extern const struct MapScripts Route46_MapScripts;
extern const struct MapEvents Route46_MapEvents;

//// CODE

extern const struct TrainerObj TrainerCamperTed;
bool TrainerCamperTed_Script(script_s* s);
extern const struct TrainerObj TrainerPicnickerErin1;
bool TrainerPicnickerErin1_Script(script_s* s);
bool Route46AskNumber1F(script_s* s);
bool Route46AskNumber2F(script_s* s);
bool Route46RegisteredNumberF(script_s* s);
bool Route46NumberAcceptedF(script_s* s);
bool Route46NumberDeclinedF(script_s* s);
bool Route46PhoneFullF(script_s* s);
bool Route46RematchF(script_s* s);
bool ErinNoRoomForCalcium(script_s* s);
bool Route46RematchGiftF(script_s* s);
extern const struct TrainerObj TrainerHikerBailey;
bool TrainerHikerBailey_Script(script_s* s);
bool Route46Sign(script_s* s);
extern const struct ItemBall Route46XSpeed;
bool Route46FruitTree1(script_s* s);
bool Route46FruitTree2(script_s* s);
extern const txt_cmd_s HikerBaileySeenText[];
extern const txt_cmd_s HikerBaileyBeatenText[];
extern const txt_cmd_s HikerBaileyAfterBattleText[];
extern const txt_cmd_s CamperTedSeenText[];
extern const txt_cmd_s CamperTedBeatenText[];
extern const txt_cmd_s CamperTedAfterBattleText[];
extern const txt_cmd_s PicnickerErin1SeenText[];
extern const txt_cmd_s PicnickerErin1BeatenText[];
extern const txt_cmd_s PicnickerErinAfterBattleText[];
extern const txt_cmd_s PicnickerErin2BeatenText[];
extern const txt_cmd_s Route46SignText[];
