#pragma once
//// EVENTS
extern const struct MapScripts Route3_MapScripts;
extern const struct MapEvents Route3_MapEvents;

//// CODE

extern const struct TrainerObj TrainerFirebreatherOtis;
bool TrainerFirebreatherOtis_Script(script_s* s);
extern const struct TrainerObj TrainerYoungsterWarren;
bool TrainerYoungsterWarren_Script(script_s* s);
extern const struct TrainerObj TrainerYoungsterJimmy;
bool TrainerYoungsterJimmy_Script(script_s* s);
extern const struct TrainerObj TrainerFirebreatherBurt;
bool TrainerFirebreatherBurt_Script(script_s* s);
bool Route3MtMoonSquareSign(script_s* s);
extern const txt_cmd_s FirebreatherOtisSeenText[];
extern const txt_cmd_s FirebreatherOtisBeatenText[];
extern const txt_cmd_s FirebreatherOtisAfterBattleText[];
extern const txt_cmd_s YoungsterWarrenSeenText[];
extern const txt_cmd_s YoungsterWarrenBeatenText[];
extern const txt_cmd_s YoungsterWarrenAfterBattleText[];
extern const txt_cmd_s YoungsterJimmySeenText[];
extern const txt_cmd_s YoungsterJimmyBeatenText[];
extern const txt_cmd_s YoungsterJimmyAfterBattleText[];
extern const txt_cmd_s FirebreatherBurtSeenText[];
extern const txt_cmd_s FirebreatherBurtBeatenText[];
extern const txt_cmd_s FirebreatherBurtAfterBattleText[];
extern const txt_cmd_s Route3MtMoonSquareSignText[];
