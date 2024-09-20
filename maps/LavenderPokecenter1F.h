#pragma once
//// EVENTS
extern const struct MapScripts LavenderPokecenter1F_MapScripts;
extern const struct MapEvents LavenderPokecenter1F_MapEvents;

//// CODE

bool LavenderPokecenter1FNurseScript(script_s* s);
bool LavenderPokecenter1FGentlemanScript(script_s* s);
bool LavenderPokecenter1FTeacherScript(script_s* s);
bool LavenderPokecenter1FYoungsterScript(script_s* s);
extern const txt_cmd_s LavenderPokecenter1FGentlemanText[];
extern const txt_cmd_s LavenderPokecenter1FTeacherText[];
extern const txt_cmd_s LavenderPokecenter1FYoungsterText[];
extern const txt_cmd_s LavenderPokecenter1FYoungsterText_ReturnedMachinePart[];
