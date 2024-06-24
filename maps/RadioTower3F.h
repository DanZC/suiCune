#pragma once
//// EVENTS
extern const struct MapScripts RadioTower3F_MapScripts;
extern const struct MapEvents RadioTower3F_MapEvents;

//// CODE

bool RadioTower3F_MapScripts_CardKeyShutterCallback(script_s* s);
bool RadioTower3FSuperNerdScript(script_s* s);
bool RadioTower3FGymGuideScript(script_s* s);
bool RadioTower3FCooltrainerFScript(script_s* s);
extern const struct TrainerObj TrainerGruntM7;
bool TrainerGruntM7_Script(script_s* s);
extern const struct TrainerObj TrainerGruntM8;
bool TrainerGruntM8_Script(script_s* s);
extern const struct TrainerObj TrainerGruntM9;
bool TrainerGruntM9_Script(script_s* s);
extern const struct TrainerObj TrainerScientistMarc;
bool TrainerScientistMarc_Script(script_s* s);
bool CardKeySlotScript(script_s* s);
bool RadioTower3FPersonnelSign(script_s* s);
bool RadioTower3FPokemonMusicSign(script_s* s);
extern const txt_cmd_s RadioTower3FSuperNerdText[];
extern const txt_cmd_s RadioTower3FGymGuideText_Rockets[];
extern const txt_cmd_s RadioTower3FGymGuideText[];
extern const txt_cmd_s RadioTower3FCooltrainerFPleaseSaveDirectorText[];
extern const txt_cmd_s RadioTower3FCooltrainerFIsDirectorSafeText[];
extern const txt_cmd_s RadioTower3FCooltrainerFYoureMyHeroText[];
extern const txt_cmd_s RadioTower3FCooltrainerFItsSunnyDayText[];
extern const txt_cmd_s RadioTower3FCooltrainerFYouWereMarvelousText[];
extern const txt_cmd_s GruntM7SeenText[];
extern const txt_cmd_s GruntM7BeatenText[];
extern const txt_cmd_s GruntM7AfterBattleText[];
extern const txt_cmd_s GruntM8SeenText[];
extern const txt_cmd_s GruntM8BeatenText[];
extern const txt_cmd_s GruntM8AfterBattleText[];
extern const txt_cmd_s GruntM9SeenText[];
extern const txt_cmd_s GruntM9BeatenText[];
extern const txt_cmd_s GruntM9AfterBattleText[];
extern const txt_cmd_s ScientistMarcSeenText[];
extern const txt_cmd_s ScientistMarcBeatenText[];
extern const txt_cmd_s ScientistMarcAfterBattleText[];
extern const txt_cmd_s RadioTower3FCardKeySlotText[];
extern const txt_cmd_s InsertedTheCardKeyText[];
extern const txt_cmd_s RadioTower3FPersonnelSignText[];
extern const txt_cmd_s RadioTower3FPokemonMusicSignText[];
