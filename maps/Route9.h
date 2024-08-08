#pragma once
//// EVENTS
extern const struct MapScripts Route9_MapScripts;
extern const struct MapEvents Route9_MapEvents;

//// CODE

extern const struct TrainerObj TrainerCamperDean;
bool TrainerCamperDean_Script(script_s* s);
extern const struct TrainerObj TrainerPicnickerHeidi;
bool TrainerPicnickerHeidi_Script(script_s* s);
extern const struct TrainerObj TrainerCamperSid;
bool TrainerCamperSid_Script(script_s* s);
extern const struct TrainerObj TrainerPicnickerEdna;
bool TrainerPicnickerEdna_Script(script_s* s);
extern const struct TrainerObj TrainerHikerTim;
bool TrainerHikerTim_Script(script_s* s);
extern const struct TrainerObj TrainerHikerSidney;
bool TrainerHikerSidney_Script(script_s* s);
bool Route9Sign(script_s* s);
extern const struct HiddenItem Route9HiddenEther;
extern const txt_cmd_s CamperDeanSeenText[];
extern const txt_cmd_s CamperDeanBeatenText[];
extern const txt_cmd_s CamperDeanAfterBattleText[];
extern const txt_cmd_s PicnickerHeidiSeenText[];
extern const txt_cmd_s PicnickerHeidiBeatenText[];
extern const txt_cmd_s PicnickerHeidiAfterBattleText[];
extern const txt_cmd_s CamperSidSeenText[];
extern const txt_cmd_s CamperSidBeatenText[];
extern const txt_cmd_s CamperSidAfterBattleText[];
extern const txt_cmd_s PicnickerEdnaSeenText[];
extern const txt_cmd_s PicnickerEdnaBeatenText[];
extern const txt_cmd_s PicnickerEdnaAfterBattleText[];
extern const txt_cmd_s HikerTimSeenText[];
extern const txt_cmd_s HikerTimBeatenText[];
extern const txt_cmd_s HikerTimAfterBattleText[];
extern const txt_cmd_s HikerSidneySeenText[];
extern const txt_cmd_s HikerSidneyBeatenText[];
extern const txt_cmd_s HikerSidneyAfterBattleText[];
extern const txt_cmd_s Route9SignText[];
