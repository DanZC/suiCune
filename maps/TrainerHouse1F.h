#pragma once
//// EVENTS
extern const struct MapScripts TrainerHouse1F_MapScripts;
extern const struct MapEvents TrainerHouse1F_MapEvents;

//// CODE

bool TrainerHouse1FReceptionistScript(script_s* s);
bool TrainerHouse1FCooltrainerMScript(script_s* s);
bool TrainerHouse1FCooltrainerFScript(script_s* s);
bool TrainerHouse1FYoungsterScript(script_s* s);
bool TrainerHouse1FGentlemanScript(script_s* s);
bool TrainerHouseSign1(script_s* s);
bool TrainerHouseSign2(script_s* s);
bool TrainerHouseIllegibleBook(script_s* s);
extern const txt_cmd_s TrainerHouse1FReceptionistText[];
extern const txt_cmd_s TrainerHouse1FCooltrainerMText[];
extern const txt_cmd_s TrainerHouse1FCooltrainerFText[];
extern const txt_cmd_s TrainerHouse1FYoungsterText[];
extern const txt_cmd_s TrainerHouse1FGentlemanText[];
extern const txt_cmd_s TrainerHouseSign1Text[];
extern const txt_cmd_s TrainerHouseSign2Text[];
extern const txt_cmd_s TrainerHouseIllegibleText[];
