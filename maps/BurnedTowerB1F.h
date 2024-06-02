#pragma once
//// EVENTS
extern const struct MapScripts BurnedTowerB1F_MapScripts;
extern const struct MapEvents BurnedTowerB1F_MapEvents;

//// CODE

bool BurnedTowerB1F_MapScripts_DummyScene0(script_s* s);
bool BurnedTowerB1F_MapScripts_DummyScene1(script_s* s);
bool BurnedTowerB1F_MapScripts_LadderCallback(script_s* s);
bool ReleaseTheBeasts(script_s* s);
bool BurnedTowerB1FEusine(script_s* s);
extern const struct ItemBall BurnedTowerB1FTMEndure;
bool BurnedTowerB1FBoulder(script_s* s);
extern const uint8_t BurnedTowerRaikouMovement[];
extern const uint8_t BurnedTowerEnteiMovement[];
extern const uint8_t BurnedTowerSuicuneMovement1[];
extern const uint8_t BurnedTowerSuicuneMovement2[];
extern const uint8_t BurnedTowerUnusedMovement[];
extern const uint8_t BurnedTowerSuicuneMovement3[];
extern const uint8_t BurnedTowerB1FEusineMovement2[];
extern const uint8_t BurnedTowerB1FEusineMovement1[];
extern const txt_cmd_s BurnedTowerB1FEusineText[];
