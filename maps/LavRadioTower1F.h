#pragma once
//// EVENTS
extern const struct MapScripts LavRadioTower1F_MapScripts;
extern const struct MapEvents LavRadioTower1F_MapEvents;

//// CODE

bool LavRadioTower1FReceptionistScript(script_s* s);
bool LavRadioTower1FOfficerScript(script_s* s);
bool LavRadioTower1FSuperNerd1Script(script_s* s);
bool LavRadioTower1FGentlemanScript(script_s* s);
extern const char expncardname[];
bool LavRadioTower1FSuperNerd2Script(script_s* s);
bool LavRadioTower1FDirectory(script_s* s);
bool LavRadioTower1FPokeFluteSign(script_s* s);
bool LavRadioTower1FReferenceLibrary(script_s* s);
extern const txt_cmd_s LavRadioTower1FReceptionistText[];
extern const txt_cmd_s LavRadioTower1FOfficerText[];
extern const txt_cmd_s LavRadioTower1FSuperNerd1Text[];
extern const txt_cmd_s LavRadioTower1FGentlemanText[];
extern const txt_cmd_s LavRadioTower1FGentlemanText_ReturnedMachinePart[];
extern const txt_cmd_s LavRadioTower1FGentlemanText_GotExpnCard[];
extern const txt_cmd_s LavRadioTower1FSuperNerd2Text[];
extern const txt_cmd_s LavRadioTower1FSuperNerd2Text_GotExpnCard[];
extern const txt_cmd_s LavRadioTower1FDirectoryText[];
extern const txt_cmd_s LavRadioTower1FPokeFluteSignText[];
extern const txt_cmd_s LavRadioTower1FReferenceLibraryText[];
