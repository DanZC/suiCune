#pragma once
//// EVENTS
extern const struct MapScripts BlackthornGym2F_MapScripts;
extern const struct MapEvents BlackthornGym2F_MapEvents;

//// CODE

bool BlackthornGym2F_MapScripts_SetUpStoneTable(script_s* s);
extern const struct CmdQueue BlackthornGym2F_MapScripts_CommandQueue[];
extern const struct Stonetable BlackthornGym2F_MapScripts_StoneTable[];
bool BlackthornGym2F_MapScripts_Boulder1(script_s* s);
bool BlackthornGym2F_MapScripts_Boulder2(script_s* s);
bool BlackthornGym2F_MapScripts_Boulder3(script_s* s);
bool BlackthornGym2F_MapScripts_Fall(script_s* s);
bool BlackthornGym2F_MapScripts_FX(script_s* s);
bool BlackthornGymBoulder(script_s* s);
extern const struct TrainerObj TrainerCooltrainermCody;
bool TrainerCooltrainermCody_Script(script_s* s);
extern const struct TrainerObj TrainerCooltrainerfFran;
bool TrainerCooltrainerfFran_Script(script_s* s);
extern const txt_cmd_s CooltrainermCodySeenText[];
extern const txt_cmd_s CooltrainermCodyBeatenText[];
extern const txt_cmd_s CooltrainermCodyAfterBattleText[];
extern const txt_cmd_s CooltrainerfFranSeenText[];
extern const txt_cmd_s CooltrainerfFranBeatenText[];
extern const txt_cmd_s CooltrainerfFranAfterBattleText[];
extern const txt_cmd_s BlackthornGym2FBoulderFellText[];
