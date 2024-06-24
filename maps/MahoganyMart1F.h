#pragma once
//// EVENTS
extern const struct MapScripts MahoganyMart1F_MapScripts;
extern const struct MapEvents MahoganyMart1F_MapEvents;

//// CODE

bool MahoganyMart1F_MapScripts_DummyScene0(script_s* s);
bool MahoganyMart1F_MapScripts_LanceUncoversStaircase(script_s* s);
bool MahoganyMart1F_MapScripts_MahoganyMart1FStaircase(script_s* s);
bool MahoganyMart1FPharmacistScript(script_s* s);
bool MahoganyMart1FBlackBeltScript(script_s* s);
bool MahoganyMart1FLanceUncoversStaircaseScript(script_s* s);
bool MahoganyMart1FGrannyScript(script_s* s);
extern const uint8_t MahoganyMart1FDragoniteTackleMovement[];
extern const uint8_t MahoganyMart1FBlackBeltKnockedBackMovement[];
extern const uint8_t MahoganyMart1FPharmacistShovedAsideMovement[];
extern const uint8_t MahoganyMart1FLanceApproachPlayerMovement[];
extern const uint8_t MahoganyMart1FLanceApproachPharmacistMovement[];
extern const uint8_t MahoganyMart1FLanceApproachHiddenStairsMovement[];
extern const uint8_t MahoganyMart1FLanceGoDownStairsMovement[];
extern const txt_cmd_s MahoganyMart1FRageCandyBarText[];
extern const txt_cmd_s MahoganyMart1FPharmacistText_LanceEntered[];
extern const txt_cmd_s MahoganyMart1FBlackBeltText[];
extern const txt_cmd_s MahoganyMart1FBlackBeltText_LanceEntered[];
extern const txt_cmd_s MahoganyMart1FLanceDragoniteHyperBeamText[];
extern const txt_cmd_s MahoganyMart1FLanceRadioText[];
extern const txt_cmd_s MahoganyMart1FLanceStairsText[];
extern const txt_cmd_s MahoganyMart1FLanceSplitUpText[];
