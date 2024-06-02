#pragma once
//// EVENTS
extern const struct MapScripts BurnedTower1F_MapScripts;
extern const struct MapEvents BurnedTower1F_MapEvents;

//// CODE

bool BurnedTower1F_MapScripts_EusineScene(script_s* s);
bool BurnedTower1F_MapScripts_DummyScene1(script_s* s);
bool BurnedTower1F_MapScripts_DummyScene2(script_s* s);
bool BurnedTower1F_MapScripts_HoleAndLadder(script_s* s);
bool BurnedTower1F_MapScripts_MeetEusine(script_s* s);
bool BurnedTowerRivalBattleScript(script_s* s);
bool BurnedTower1FEusineScript(script_s* s);
bool BurnedTower1FMortyScript(script_s* s);
bool BurnedTower1FRock(script_s* s);
extern const struct HiddenItem BurnedTower1FHiddenEther;
extern const struct HiddenItem BurnedTower1FHiddenUltraBall;
extern const struct ItemBall BurnedTower1FHPUp;
extern const uint8_t BurnedTowerMovement_PlayerWalksToSilver[];
extern const uint8_t BurnedTowerMovement_SilverWalksToPlayer[];
extern const uint8_t BurnedTower1FMovement_PlayerStartsToFall[];
extern const uint8_t BurnedTower1FEusineMovement[];
extern const txt_cmd_s BurnedTowerSilver_BeforeText[];
extern const txt_cmd_s BurnedTowerSilver_WinText[];
extern const txt_cmd_s BurnedTowerSilver_AfterText1[];
extern const txt_cmd_s BurnedTowerSilver_LossText[];
extern const txt_cmd_s BurnedTowerSilver_AfterText2[];
extern const txt_cmd_s BurnedTower1FEusineIntroText[];
extern const txt_cmd_s BurnedTower1FEusineText[];
extern const txt_cmd_s BurnedTower1FMortyText[];
