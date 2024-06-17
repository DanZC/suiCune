#pragma once
//// EVENTS
extern const struct MapScripts CianwoodGym_MapScripts;
extern const struct MapEvents CianwoodGym_MapEvents;

//// CODE

bool CianwoodGymChuckScript(script_s* s);
bool CianwoodGymActivateRockets(script_s* s);
extern const struct TrainerObj TrainerBlackbeltYoshi;
bool TrainerBlackbeltYoshi_Script(script_s* s);
extern const struct TrainerObj TrainerBlackbeltLao;
bool TrainerBlackbeltLao_Script(script_s* s);
extern const struct TrainerObj TrainerBlackbeltNob;
bool TrainerBlackbeltNob_Script(script_s* s);
extern const struct TrainerObj TrainerBlackbeltLung;
bool TrainerBlackbeltLung_Script(script_s* s);
bool CianwoodGymBoulder(script_s* s);
bool CianwoodGymStatue(script_s* s);
extern const uint8_t CianwoodGymMovement_ChuckChucksBoulder[];
extern const txt_cmd_s ChuckIntroText1[];
extern const txt_cmd_s ChuckIntroText2[];
extern const txt_cmd_s ChuckIntroText3[];
extern const txt_cmd_s ChuckLossText[];
extern const txt_cmd_s GetStormBadgeText[];
extern const txt_cmd_s ChuckExplainBadgeText[];
extern const txt_cmd_s ChuckExplainTMText[];
extern const txt_cmd_s ChuckAfterText[];
extern const txt_cmd_s BlackbeltYoshiSeenText[];
extern const txt_cmd_s BlackbeltYoshiBeatenText[];
extern const txt_cmd_s BlackbeltYoshiAfterText[];
extern const txt_cmd_s BlackbeltLaoSeenText[];
extern const txt_cmd_s BlackbeltLaoBeatenText[];
extern const txt_cmd_s BlackbeltLaoAfterText[];
extern const txt_cmd_s BlackbeltNobSeenText[];
extern const txt_cmd_s BlackbeltNobBeatenText[];
extern const txt_cmd_s BlackbeltNobAfterText[];
extern const txt_cmd_s BlackbeltLungSeenText[];
extern const txt_cmd_s BlackbeltLungBeatenText[];
extern const txt_cmd_s BlackbeltLungAfterText[];
