#pragma once
//// EVENTS
extern const struct MapScripts Route37_MapScripts;
extern const struct MapEvents Route37_MapEvents;

//// CODE

bool Route37_MapScripts_Sunny(script_s* s);
bool Route37_MapScripts_SunnyAppears(script_s* s);
extern const struct TrainerObj TrainerTwinsAnnandanne1;
bool TrainerTwinsAnnandanne1_Script(script_s* s);
extern const struct TrainerObj TrainerTwinsAnnandanne2;
bool TrainerTwinsAnnandanne2_Script(script_s* s);
extern const struct TrainerObj TrainerPsychicGreg;
bool TrainerPsychicGreg_Script(script_s* s);
bool SunnyScript(script_s* s);
bool SunnySundayScript(script_s* s);
bool SunnyDoneScript(script_s* s);
bool SunnyNotSundayScript(script_s* s);
bool Route37Sign(script_s* s);
bool Route37FruitTree1(script_s* s);
bool Route37FruitTree2(script_s* s);
bool Route37FruitTree3(script_s* s);
extern const struct HiddenItem Route37HiddenEther;
extern const txt_cmd_s TwinsAnnandanne1SeenText[];
extern const txt_cmd_s TwinsAnnandanne1BeatenText[];
extern const txt_cmd_s TwinsAnnandanne1AfterBattleText[];
extern const txt_cmd_s TwinsAnnandanne2SeenText[];
extern const txt_cmd_s TwinsAnnandanne2BeatenText[];
extern const txt_cmd_s TwinsAnnandanne2AfterBattleText[];
extern const txt_cmd_s PsychicGregSeenText[];
extern const txt_cmd_s PsychicGregBeatenText[];
extern const txt_cmd_s PsychicGregAfterBattleText[];
extern const txt_cmd_s MeetSunnyText[];
extern const txt_cmd_s SunnyGivesGiftText1[];
extern const txt_cmd_s SunnyGivesGiftText2[];
extern const txt_cmd_s SunnyGaveGiftText[];
extern const txt_cmd_s SunnySundayText[];
extern const txt_cmd_s SunnyNotSundayText[];
extern const txt_cmd_s Route37SignText[];
