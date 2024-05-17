#pragma once
//// EVENTS
extern const struct MapScripts GoldenrodGym_MapScripts;
extern const struct MapEvents GoldenrodGym_MapEvents;

//// CODE

bool GoldenrodGym_MapScripts_DummyScene0(script_s* s);
bool GoldenrodGym_MapScripts_DummyScene1(script_s* s);
bool GoldenrodGymWhitneyScript(script_s* s);
bool GoldenrodGymActivateRockets(script_s* s);
extern const struct TrainerObj TrainerLassCarrie;
bool TrainerLassCarrie_Script(script_s* s);
bool WhitneyCriesScript(script_s* s);
extern const struct TrainerObj TrainerLassBridget;
bool TrainerLassBridget_Script(script_s* s);
extern const struct TrainerObj TrainerBeautyVictoria;
bool TrainerBeautyVictoria_Script(script_s* s);
extern const struct TrainerObj TrainerBeautySamantha;
bool TrainerBeautySamantha_Script(script_s* s);
bool GoldenrodGymGuideScript(script_s* s);
bool GoldenrodGymStatue(script_s* s);
extern const uint8_t BridgetWalksUpMovement[];
extern const uint8_t BridgetWalksAwayMovement[];
extern const txt_cmd_s WhitneyBeforeText[];
extern const txt_cmd_s WhitneyShouldntBeSoSeriousText[];
extern const txt_cmd_s WhitneyYouMeanieText[];
extern const txt_cmd_s WhitneyWhatDoYouWantText[];
extern const txt_cmd_s PlayerReceivedPlainBadgeText[];
extern const txt_cmd_s WhitneyPlainBadgeText[];
extern const txt_cmd_s WhitneyAttractText[];
extern const txt_cmd_s WhitneyGoodCryText[];
extern const txt_cmd_s LassCarrieSeenText[];
extern const txt_cmd_s LassCarrieBeatenText[];
extern const txt_cmd_s LassCarrieAfterBattleText[];
extern const txt_cmd_s LassBridgetSeenText[];
extern const txt_cmd_s LassBridgetBeatenText[];
extern const txt_cmd_s LassBridgetAfterBattleText[];
extern const txt_cmd_s BridgetWhitneyCriesText[];
extern const txt_cmd_s BeautyVictoriaSeenText[];
extern const txt_cmd_s BeautyVictoriaBeatenText[];
extern const txt_cmd_s BeautyVictoriaAfterBattleText[];
extern const txt_cmd_s BeautySamanthaSeenText[];
extern const txt_cmd_s BeautySamanthaBeatenText[];
extern const txt_cmd_s BeautySamanthaAfterBattleText[];
extern const txt_cmd_s GoldenrodGymGuideText[];
extern const txt_cmd_s GoldenrodGymGuideWinText[];
