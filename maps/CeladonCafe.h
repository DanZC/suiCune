#pragma once
//// EVENTS
extern const struct MapScripts CeladonCafe_MapScripts;
extern const struct MapEvents CeladonCafe_MapEvents;

//// CODE

bool CeladonCafeChef(script_s* s);
bool CeladonCafeFisher1(script_s* s);
bool CeladonCafeFisher2(script_s* s);
bool CeladonCafeFisher3(script_s* s);
bool CeladonCafeTeacher(script_s* s);
bool EatathonContestPoster(script_s* s);
bool CeladonCafeTrashcan(script_s* s);
extern const txt_cmd_s ChefText_Eatathon[];
extern const txt_cmd_s Fisher1Text_Snarfle[];
extern const txt_cmd_s Fisher1Text_Concentration[];
extern const txt_cmd_s Fisher2Text_GulpChew[];
extern const txt_cmd_s Fisher2Text_Quantity[];
extern const txt_cmd_s Fisher3Text_MunchMunch[];
extern const txt_cmd_s Fisher3Text_GoldenrodIsBest[];
extern const txt_cmd_s TeacherText_CrunchCrunch[];
extern const txt_cmd_s TeacherText_NoCoinCase[];
extern const txt_cmd_s TeacherText_KeepEating[];
extern const txt_cmd_s TeacherText_MoreChef[];
extern const txt_cmd_s EatathonContestPosterText[];
extern const txt_cmd_s FoundLeftoversText[];
extern const txt_cmd_s NoRoomForLeftoversText[];
