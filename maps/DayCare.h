#pragma once
//// EVENTS
extern const struct MapScripts DayCare_MapScripts;
extern const struct MapEvents DayCare_MapEvents;

//// CODE

bool DayCare_MapScripts_EggCheckCallback(script_s* s);
bool DayCare_MapScripts_PutDayCareManOutside(script_s* s);
bool DayCareManScript_Inside(script_s* s);
bool DayCareLadyScript(script_s* s);
bool DayCareBookshelf(script_s* s);
extern const txt_cmd_s Text_GrampsLookingForYou[];
extern const txt_cmd_s Text_DayCareManTalksAboutEggTicket[];
extern const txt_cmd_s DayCareManText_GiveOddEgg[];
extern const txt_cmd_s DayCareText_ComeAgain[];
extern const txt_cmd_s DayCareText_GotOddEgg[];
extern const txt_cmd_s DayCareText_DescribeOddEgg[];
extern const txt_cmd_s DayCareText_PartyFull[];
