#pragma once
//// EVENTS
extern const struct MapScripts Route11_MapScripts;
extern const struct MapEvents Route11_MapEvents;

//// CODE

extern const struct TrainerObj TrainerYoungsterOwen;
bool TrainerYoungsterOwen_Script(script_s* s);
extern const struct TrainerObj TrainerYoungsterJason;
bool TrainerYoungsterJason_Script(script_s* s);
extern const struct TrainerObj TrainerPsychicHerman;
bool TrainerPsychicHerman_Script(script_s* s);
extern const struct TrainerObj TrainerPsychicFidel;
bool TrainerPsychicFidel_Script(script_s* s);
bool Route11Sign(script_s* s);
bool Route11FruitTree(script_s* s);
extern const struct HiddenItem Route11HiddenRevive;
extern const txt_cmd_s YoungsterOwenSeenText[];
extern const txt_cmd_s YoungsterOwenBeatenText[];
extern const txt_cmd_s YoungsterOwenAfterBattleText[];
extern const txt_cmd_s YoungsterJasonSeenText[];
extern const txt_cmd_s YoungsterJasonBeatenText[];
extern const txt_cmd_s YoungsterJasonAfterBattleText[];
extern const txt_cmd_s PsychicHermanSeenText[];
extern const txt_cmd_s PsychicHermanBeatenText[];
extern const txt_cmd_s PsychicHermanAfterBattleText[];
extern const txt_cmd_s PsychicFidelSeenText[];
extern const txt_cmd_s PsychicFidelBeatenText[];
extern const txt_cmd_s PsychicFidelAfterBattleText[];
extern const txt_cmd_s Route11SignText[];
