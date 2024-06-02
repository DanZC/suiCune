#pragma once
//// EVENTS
extern const struct MapScripts EcruteakTinTowerEntrance_MapScripts;
extern const struct MapEvents EcruteakTinTowerEntrance_MapEvents;

//// CODE

bool EcruteakTinTowerEntrance_MapScripts_DummyScene0(script_s* s);
bool EcruteakTinTowerEntrance_MapScripts_DummyScene1(script_s* s);
bool EcruteakTinTowerEntrance_MapScripts_InitializeSages(script_s* s);
bool EcruteakTinTowerEntranceSageBlocksLeft(script_s* s);
bool EcruteakTinTowerEntranceSageBlocksRight(script_s* s);
bool EcruteakTinTowerEntranceAlreadyBlocked(script_s* s);
bool EcruteakTinTowerEntranceSageScript(script_s* s);
bool EcruteakTinTowerEntranceWanderingSageScript(script_s* s);
bool EcruteakTinTowerEntranceGrampsScript(script_s* s);
extern const uint8_t EcruteakTinTowerEntranceSageBlocksLeftMovement[];
extern const uint8_t EcruteakTinTowerEntranceSageBlocksRightMovement[];
extern const txt_cmd_s EcruteakTinTowerEntranceSageText[];
extern const txt_cmd_s EcruteakTinTowerEntranceSageText_GotFogBadge[];
extern const txt_cmd_s EcruteakTinTowerEntranceSageText_NoClearBell[];
extern const txt_cmd_s EcruteakTinTowerEntranceSageText_HearsClearBell[];
extern const txt_cmd_s EcruteakTinTowerEntranceSageText_PleaseDoGoOn[];
extern const txt_cmd_s EcruteakTinTowerEntranceSageText_HeardClearBell[];
extern const txt_cmd_s EcruteakTinTowerEntranceWanderingSageText[];
extern const txt_cmd_s EcruteakTinTowerEntranceWanderingSageText_GotClearBell[];
extern const txt_cmd_s EcruteakTinTowerEntranceGrampsText[];
