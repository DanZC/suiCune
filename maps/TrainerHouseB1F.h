#pragma once
//// EVENTS
extern const struct MapScripts TrainerHouseB1F_MapScripts;
extern const struct MapEvents TrainerHouseB1F_MapEvents;

//// CODE

bool TrainerHouseB1F_MapScripts_DummyScene(script_s* s);
bool TrainerHouseReceptionistScript(script_s* s);
extern const uint8_t Movement_EnterTrainerHouseBattleRoom[];
extern const uint8_t Movement_ExitTrainerHouseBattleRoom[];
extern const uint8_t Movement_TrainerHouseTurnBack[];
extern const txt_cmd_s TrainerHouseB1FIntroText[];
extern const txt_cmd_s TrainerHouseB1FYourOpponentIsText[];
extern const txt_cmd_s TrainerHouseB1FAskWantToBattleText[];
extern const txt_cmd_s TrainerHouseB1FGoRightInText[];
extern const txt_cmd_s TrainerHouseB1FPleaseComeAgainText[];
extern const txt_cmd_s TrainerHouseB1FSecondChallengeDeniedText[];
extern const txt_cmd_s TrainerHouseB1FCalBeatenText[];
extern const txt_cmd_s TrainerHouseB1FCalBeforeText[];
