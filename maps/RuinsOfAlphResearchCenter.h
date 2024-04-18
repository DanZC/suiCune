#pragma once
//// EVENTS
extern const struct MapScripts RuinsOfAlphResearchCenter_MapScripts;
extern const struct MapEvents RuinsOfAlphResearchCenter_MapEvents;

//// CODE

bool RuinsOfAlphResearchCenter_MapScripts_DummyScene0(script_s* s);
bool RuinsOfAlphResearchCenter_MapScripts_GetUnownDex(script_s* s);
bool RuinsOfAlphResearchCenter_MapScripts_ScientistCallback(script_s* s);
bool RuinsOfAlphResearchCenter_MapScripts_ShowScientist(script_s* s);
bool RuinsOfAlphResearchCenter_MapScripts_GetUnownDexScript(script_s* s);
bool RuinsOfAlphResearchCenterScientist3Script(script_s* s);
bool RuinsOfAlphResearchCenterScientist1Script(script_s* s);
bool RuinsOfAlphResearchCenterScientist2Script(script_s* s);
bool RuinsOfAlphResearchCenterComputer(script_s* s);
bool RuinsOfAlphResearchCenterPrinter(script_s* s);
bool RuinsOfAlphResearchCenterPhoto(script_s* s);
bool RuinsOfAlphResearchCenterBookshelf(script_s* s);
extern const uint8_t RuinsOfAlphResearchCenterApproachesComputerMovement[];
extern const uint8_t RuinsOfAlphResearchCenterApproachesPlayerMovement[];
extern const uint8_t RuinsOfAlphResearchCenterLeavesPlayerMovement[];
extern const txt_cmd_s RuinsOfAlphResearchCenterModifiedDexText[];
extern const txt_cmd_s RuinsOfAlphResearchCenterDexUpgradedText[];
extern const txt_cmd_s RuinsOfAlphResearchCenterScientist3Text[];
extern const txt_cmd_s RuinsOfAlphResearchCenterScientist3_PrinterAvailable[];
extern const txt_cmd_s RuinsOfAlphResearchCenterScientist1Text[];
extern const txt_cmd_s RuinsOfAlphResearchCenterScientist1Text_GotUnownDex[];
extern const txt_cmd_s RuinsOfAlphResearchCenterScientist1Text_UnownAppeared[];
extern const txt_cmd_s RuinsOfAlphResearchCenterScientist1Text_GotAllUnown[];
extern const txt_cmd_s RuinsOfAlphResearchCenterScientist2Text[];
extern const txt_cmd_s RuinsOfAlphResearchCenterScientist2Text_UnownAppeared[];
extern const txt_cmd_s RuinsOfAlphResearchCenterUnusedText1[];
extern const txt_cmd_s RuinsOfAlphResearchCenterUnusedText2[];
extern const txt_cmd_s RuinsOfAlphResearchCenterScientist2Text_GotAllUnown[];
extern const txt_cmd_s RuinsOfAlphResearchCenterComputerText[];
extern const txt_cmd_s RuinsOfAlphResearchCenterComputerText_GotAllUnown[];
extern const txt_cmd_s RuinsOfAlphResearchCenterPrinterText_DoesntWork[];
extern const txt_cmd_s RuinsOfAlphResearchCenterUnownPrinterText[];
extern const txt_cmd_s RuinsOfAlphResearchCenterProfSilktreePhotoText[];
extern const txt_cmd_s RuinsOfAlphResearchCenterAcademicBooksText[];
