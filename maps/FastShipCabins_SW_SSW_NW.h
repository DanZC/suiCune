#pragma once
//// EVENTS
extern const struct MapScripts FastShipCabins_SW_SSW_NW_MapScripts;
extern const struct MapEvents FastShipCabins_SW_SSW_NW_MapEvents;

//// CODE

extern const struct TrainerObj TrainerFirebreatherLyle;
bool TrainerFirebreatherLyle_Script(script_s* s);
extern const struct TrainerObj TrainerBugCatcherKen;
bool TrainerBugCatcherKen_Script(script_s* s);
extern const struct TrainerObj TrainerBeautyCassie;
bool TrainerBeautyCassie_Script(script_s* s);
extern const struct TrainerObj TrainerGuitaristClyde;
bool TrainerGuitaristClyde_Script(script_s* s);
bool FastShipBed(script_s* s);
bool FastShipCabinsNorthwestCabinTrashcan(script_s* s);
extern const txt_cmd_s FirebreatherLyleSeenText[];
extern const txt_cmd_s FirebreatherLyleBeatenText[];
extern const txt_cmd_s FirebreatherLyleAfterBattleText[];
extern const txt_cmd_s BugCatcherKenSeenText[];
extern const txt_cmd_s BugCatcherKenBeatenText[];
extern const txt_cmd_s BugCatcherKenAfterBattleText[];
extern const txt_cmd_s BeautyCassieSeenText[];
extern const txt_cmd_s BeautyCassieBeatenText[];
extern const txt_cmd_s BeautyCassieAfterBattleText[];
extern const txt_cmd_s GuitaristClydeSeenText[];
extern const txt_cmd_s GuitaristClydeBeatenText[];
extern const txt_cmd_s GuitaristClydeAfterBattleMobileText[];
extern const txt_cmd_s GuitaristClydeAfterBattleText[];
extern const txt_cmd_s FastShipBedText1[];
extern const txt_cmd_s FastShipBedText2[];
extern const txt_cmd_s FastShipArrivedOlivineText[];
extern const txt_cmd_s FastShipArrivedVermilionText[];
