#pragma once
//// EVENTS
extern const struct MapScripts Route43_MapScripts;
extern const struct MapEvents Route43_MapEvents;

//// CODE

bool Route43_MapScripts_CheckIfRockets(script_s* s);
bool Route43_MapScripts_NoRockets(script_s* s);
extern const struct TrainerObj TrainerCamperSpencer;
bool TrainerCamperSpencer_Script(script_s* s);
extern const struct TrainerObj TrainerPokemaniacBen;
bool TrainerPokemaniacBen_Script(script_s* s);
extern const struct TrainerObj TrainerPokemaniacBrent;
bool TrainerPokemaniacBrent_Script(script_s* s);
extern const struct TrainerObj TrainerPokemaniacRon;
bool TrainerPokemaniacRon_Script(script_s* s);
extern const struct TrainerObj TrainerFisherMarvin;
bool TrainerFisherMarvin_Script(script_s* s);
extern const struct TrainerObj TrainerPicnickerTiffany;
bool TrainerPicnickerTiffany_Script(script_s* s);
bool Route43Sign1(script_s* s);
bool Route43Sign2(script_s* s);
bool Route43TrainerTips(script_s* s);
bool Route43FruitTree(script_s* s);
extern const struct ItemBall Route43MaxEther;
extern const txt_cmd_s PokemaniacBenSeenText[];
extern const txt_cmd_s PokemaniacBenBeatenText[];
extern const txt_cmd_s PokemaniacBenAfterBattleText[];
extern const txt_cmd_s PokemaniacBrentSeenText[];
extern const txt_cmd_s PokemaniacBrentBeatenText[];
extern const txt_cmd_s PokemaniacBrentAfterBattleText[];
extern const txt_cmd_s PokemaniacRonSeenText[];
extern const txt_cmd_s PokemaniacRonBeatenText[];
extern const txt_cmd_s PokemaniacRonAfterBattleText[];
extern const txt_cmd_s FisherMarvinSeenText[];
extern const txt_cmd_s FisherMarvinBeatenText[];
extern const txt_cmd_s FisherMarvinAfterBattleText[];
extern const txt_cmd_s CamperSpencerSeenText[];
extern const txt_cmd_s CamperSpencerBeatenText[];
extern const txt_cmd_s CamperSpencerAfterBattleText[];
extern const txt_cmd_s PicnickerTiffanySeenText[];
extern const txt_cmd_s PicnickerTiffanyBeatenText[];
extern const txt_cmd_s PicnickerTiffanyWantsPicnicText[];
extern const txt_cmd_s PicnickerTiffanyClefairyText[];
extern const txt_cmd_s Route43Sign1Text[];
extern const txt_cmd_s Route43Sign2Text[];
extern const txt_cmd_s Route43TrainerTipsText[];
