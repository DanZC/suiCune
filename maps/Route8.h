#pragma once
//// EVENTS
extern const struct MapScripts Route8_MapScripts;
extern const struct MapEvents Route8_MapEvents;

//// CODE

extern const struct TrainerObj TrainerBikerDwayne;
bool TrainerBikerDwayne_Script(script_s* s);
extern const struct TrainerObj TrainerBikerHarris;
bool TrainerBikerHarris_Script(script_s* s);
extern const struct TrainerObj TrainerBikerZeke;
bool TrainerBikerZeke_Script(script_s* s);
extern const struct TrainerObj TrainerSupernerdSam;
bool TrainerSupernerdSam_Script(script_s* s);
extern const struct TrainerObj TrainerSupernerdTom;
bool TrainerSupernerdTom_Script(script_s* s);
bool Route8LockedDoor(script_s* s);
bool Route8UndergroundPathSign(script_s* s);
bool Route8FruitTree(script_s* s);
extern const txt_cmd_s BikerDwayneSeenText[];
extern const txt_cmd_s BikerDwayneBeatenText[];
extern const txt_cmd_s BikerDwayneAfterBattleText[];
extern const txt_cmd_s BikerHarrisSeenText[];
extern const txt_cmd_s BikerHarrisBeatenText[];
extern const txt_cmd_s BikerHarrisAfterBattleText[];
extern const txt_cmd_s BikerZekeSeenText[];
extern const txt_cmd_s BikerZekeBeatenText[];
extern const txt_cmd_s BikerZekeAfterBattleText[];
extern const txt_cmd_s SupernerdSamSeenText[];
extern const txt_cmd_s SupernerdSamBeatenText[];
extern const txt_cmd_s SupernerdSamAfterBattleText[];
extern const txt_cmd_s SupernerdTomSeenText[];
extern const txt_cmd_s SupernerdTomBeatenText[];
extern const txt_cmd_s SupernerdTomAfterBattleText[];
extern const txt_cmd_s Route8LockedDoorText[];
extern const txt_cmd_s Route8UndergroundPathSignText[];
