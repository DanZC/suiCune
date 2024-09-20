#pragma once
//// EVENTS
extern const struct MapScripts CopycatsHouse2F_MapScripts;
extern const struct MapEvents CopycatsHouse2F_MapEvents;

//// CODE

bool CopycatsHouse2F_MapScripts_Callback(script_s* s);
bool Copycat(script_s* s);
bool CopycatsDodrio(script_s* s);
bool CopycatsHouse2FDoll(script_s* s);
bool CopycatsHouse2FBookshelf(script_s* s);
extern const uint8_t CopycatSpinAroundMovementData[];
extern const txt_cmd_s CopycatText_Male_1[];
extern const txt_cmd_s CopycatText_QuickMimicking[];
extern const txt_cmd_s CopycatText_Male_2[];
extern const txt_cmd_s CopycatText_Worried[];
extern const txt_cmd_s CopycatText_GiveDoll[];
extern const txt_cmd_s CopycatText_GivePass[];
extern const txt_cmd_s CopycatText_ExplainPass[];
extern const txt_cmd_s CopycatText_Male_3[];
extern const txt_cmd_s CopycatText_ItsAScream[];
extern const txt_cmd_s CopycatText_Female_1[];
extern const txt_cmd_s CopycatText_Female_2[];
extern const txt_cmd_s CopycatText_Female_3[];
extern const txt_cmd_s CopycatsDodrioText1[];
extern const txt_cmd_s CopycatsDodrioText2[];
extern const txt_cmd_s CopycatsHouse2FDollText[];
