#pragma once
//// EVENTS
extern const struct MapScripts EcruteakGym_MapScripts;
extern const struct MapEvents EcruteakGym_MapEvents;

//// CODE

bool EcruteakGym_MapScripts_ForcedToLeave(script_s* s);
bool EcruteakGym_MapScripts_DummyScene(script_s* s);
bool EcruteakGymMortyScript(script_s* s);
bool EcruteakGymActivateRockets(script_s* s);
bool EcruteakGymClosed(script_s* s);
extern const struct TrainerObj TrainerSageJeffrey;
bool TrainerSageJeffrey_Script(script_s* s);
extern const struct TrainerObj TrainerSagePing;
bool TrainerSagePing_Script(script_s* s);
extern const struct TrainerObj TrainerMediumMartha;
bool TrainerMediumMartha_Script(script_s* s);
extern const struct TrainerObj TrainerMediumGrace;
bool TrainerMediumGrace_Script(script_s* s);
bool EcruteakGymGuideScript(script_s* s);
bool EcruteakGymStatue(script_s* s);
extern const uint8_t EcruteakGymPlayerStepUpMovement[];
extern const uint8_t EcruteakGymPlayerSlowStepDownMovement[];
extern const uint8_t EcruteakGymGrampsSlowStepDownMovement[];
extern const txt_cmd_s MortyIntroText[];
extern const txt_cmd_s MortyWinLossText[];
extern const txt_cmd_s Text_ReceivedFogBadge[];
extern const txt_cmd_s MortyText_FogBadgeSpeech[];
extern const txt_cmd_s MortyText_ShadowBallSpeech[];
extern const txt_cmd_s MortyFightDoneText[];
extern const txt_cmd_s SageJeffreySeenText[];
extern const txt_cmd_s SageJeffreyBeatenText[];
extern const txt_cmd_s SageJeffreyAfterBattleText[];
extern const txt_cmd_s SagePingSeenText[];
extern const txt_cmd_s SagePingBeatenText[];
extern const txt_cmd_s SagePingAfterBattleText[];
extern const txt_cmd_s MediumMarthaSeenText[];
extern const txt_cmd_s MediumMarthaBeatenText[];
extern const txt_cmd_s MediumMarthaAfterBattleText[];
extern const txt_cmd_s MediumGraceSeenText[];
extern const txt_cmd_s MediumGraceBeatenText[];
extern const txt_cmd_s MediumGraceAfterBattleText[];
extern const txt_cmd_s EcruteakGymGuideText[];
extern const txt_cmd_s EcruteakGymGuideWinText[];
extern const txt_cmd_s EcruteakGymClosedText[];
