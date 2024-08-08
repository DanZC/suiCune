#pragma once
//// EVENTS
extern const struct MapScripts Route15_MapScripts;
extern const struct MapEvents Route15_MapEvents;

//// CODE

extern const struct TrainerObj TrainerTeacherColette;
bool TrainerTeacherColette_Script(script_s* s);
extern const struct TrainerObj TrainerTeacherHillary;
bool TrainerTeacherHillary_Script(script_s* s);
extern const struct TrainerObj TrainerSchoolboyKipp;
bool TrainerSchoolboyKipp_Script(script_s* s);
extern const struct TrainerObj TrainerSchoolboyTommy;
bool TrainerSchoolboyTommy_Script(script_s* s);
extern const struct TrainerObj TrainerSchoolboyJohnny;
bool TrainerSchoolboyJohnny_Script(script_s* s);
extern const struct TrainerObj TrainerSchoolboyBilly;
bool TrainerSchoolboyBilly_Script(script_s* s);
bool Route15Sign(script_s* s);
extern const struct ItemBall Route15PPUp;
extern const txt_cmd_s TeacherColetteSeenText[];
extern const txt_cmd_s TeacherColetteBeatenText[];
extern const txt_cmd_s TeacherColetteAfterBattleText[];
extern const txt_cmd_s TeacherHillarySeenText[];
extern const txt_cmd_s TeacherHillaryBeatenText[];
extern const txt_cmd_s TeacherHillaryAfterBattleText[];
extern const txt_cmd_s SchoolboyKippSeenText[];
extern const txt_cmd_s SchoolboyKippBeatenText[];
extern const txt_cmd_s SchoolboyKippAfterBattleText[];
extern const txt_cmd_s SchoolboyTommySeenText[];
extern const txt_cmd_s SchoolboyTommyBeatenText[];
extern const txt_cmd_s SchoolboyTommyAfterBattleText[];
extern const txt_cmd_s SchoolboyJohnnySeenText[];
extern const txt_cmd_s SchoolboyJohnnyBeatenText[];
extern const txt_cmd_s SchoolboyJohnnyAfterBattleText[];
extern const txt_cmd_s SchoolboyBillySeenText[];
extern const txt_cmd_s SchoolboyBillyBeatenText[];
extern const txt_cmd_s SchoolboyBillyAfterBattleText[];
extern const txt_cmd_s Route15SignText[];
