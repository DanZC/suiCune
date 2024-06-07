#pragma once
//// EVENTS
extern const struct MapScripts Route40_MapScripts;
extern const struct MapEvents Route40_MapEvents;

//// CODE

bool Route40_MapScripts_MonicaCallback(script_s* s);
extern const struct TrainerObj TrainerSwimmerfElaine;
bool TrainerSwimmerfElaine_Script(script_s* s);
extern const struct TrainerObj TrainerSwimmerfPaula;
bool TrainerSwimmerfPaula_Script(script_s* s);
extern const struct TrainerObj TrainerSwimmermSimon;
bool TrainerSwimmermSimon_Script(script_s* s);
extern const struct TrainerObj TrainerSwimmermRandall;
bool TrainerSwimmermRandall_Script(script_s* s);
bool Route40Lass1Script(script_s* s);
bool Route40PokefanMScript(script_s* s);
bool Route40Lass2Script(script_s* s);
bool Route40StandingYoungsterScript(script_s* s);
bool MonicaScript(script_s* s);
bool Route40Sign(script_s* s);
bool Route40Rock(script_s* s);
extern const struct HiddenItem Route40HiddenHyperPotion;
extern const uint8_t Route40_StepRightUp6Movement[];
extern const uint8_t Route40_StepUp5Movement[];
extern const uint8_t Route40_StepUp4Movement[];
extern const txt_cmd_s SwimmermSimonSeenText[];
extern const txt_cmd_s SwimmermSimonBeatenText[];
extern const txt_cmd_s SwimmermSimonAfterBattleText[];
extern const txt_cmd_s SwimmermRandallSeenText[];
extern const txt_cmd_s SwimmermRandallBeatenText[];
extern const txt_cmd_s SwimmermRandallAfterBattleText[];
extern const txt_cmd_s SwimmerfElaineSeenText[];
extern const txt_cmd_s SwimmerfElaineBeatenText[];
extern const txt_cmd_s SwimmerfElaineAfterBattleText[];
extern const txt_cmd_s SwimmerfPaulaSeenText[];
extern const txt_cmd_s SwimmerfPaulaBeatenText[];
extern const txt_cmd_s SwimmerfPaulaAfterBattleText[];
extern const txt_cmd_s Route40Lass1Text[];
extern const txt_cmd_s Route40PokefanMText[];
extern const txt_cmd_s Route40PokefanMText_Mobile[];
extern const txt_cmd_s Route40Lass2Text[];
extern const txt_cmd_s Route40StandingYoungsterText[];
extern const txt_cmd_s MeetMonicaText[];
extern const txt_cmd_s MonicaGivesGiftText[];
extern const txt_cmd_s MonicaGaveGiftText[];
extern const txt_cmd_s MonicaMondayText[];
extern const txt_cmd_s MonicaNotMondayText[];
extern const txt_cmd_s Route40SignText[];
