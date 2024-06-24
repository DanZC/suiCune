#pragma once
//// EVENTS
extern const struct MapScripts MahoganyGym_MapScripts;
extern const struct MapEvents MahoganyGym_MapEvents;

//// CODE

bool MahoganyGymPryceScript(script_s* s);
bool PryceScript_Defeat(script_s* s);
bool MahoganyGym_NoRoomForIcyWind(script_s* s);
bool MahoganyGymActivateRockets(script_s* s);
extern const struct TrainerObj TrainerSkierRoxanne;
bool TrainerSkierRoxanne_Script(script_s* s);
extern const struct TrainerObj TrainerSkierClarissa;
bool TrainerSkierClarissa_Script(script_s* s);
extern const struct TrainerObj TrainerBoarderRonald;
bool TrainerBoarderRonald_Script(script_s* s);
extern const struct TrainerObj TrainerBoarderBrad;
bool TrainerBoarderBrad_Script(script_s* s);
extern const struct TrainerObj TrainerBoarderDouglas;
bool TrainerBoarderDouglas_Script(script_s* s);
bool MahoganyGymGuideScript(script_s* s);
bool MahoganyGymStatue(script_s* s);
extern const txt_cmd_s PryceText_Intro[];
extern const txt_cmd_s PryceText_Impressed[];
extern const txt_cmd_s Text_ReceivedGlacierBadge[];
extern const txt_cmd_s PryceText_GlacierBadgeSpeech[];
extern const txt_cmd_s PryceText_IcyWindSpeech[];
extern const txt_cmd_s PryceText_CherishYourPokemon[];
extern const txt_cmd_s BoarderRonaldSeenText[];
extern const txt_cmd_s BoarderRonaldBeatenText[];
extern const txt_cmd_s BoarderRonaldAfterBattleText[];
extern const txt_cmd_s BoarderBradSeenText[];
extern const txt_cmd_s BoarderBradBeatenText[];
extern const txt_cmd_s BoarderBradAfterBattleText[];
extern const txt_cmd_s BoarderDouglasSeenText[];
extern const txt_cmd_s BoarderDouglasBeatenText[];
extern const txt_cmd_s BoarderDouglasAfterBattleText[];
extern const txt_cmd_s SkierRoxanneSeenText[];
extern const txt_cmd_s SkierRoxanneBeatenText[];
extern const txt_cmd_s SkierRoxanneAfterBattleText[];
extern const txt_cmd_s SkierClarissaSeenText[];
extern const txt_cmd_s SkierClarissaBeatenText[];
extern const txt_cmd_s SkierClarissaAfterBattleText[];
extern const txt_cmd_s MahoganyGymGuideText[];
extern const txt_cmd_s MahoganyGymGuideWinText[];
