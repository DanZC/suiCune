#pragma once
//// EVENTS
extern const struct MapScripts CeladonDeptStore1F_MapScripts;
extern const struct MapEvents CeladonDeptStore1F_MapEvents;

//// CODE

bool CeladonDeptStore1FReceptionistScript(script_s* s);
bool CeladonDeptStore1FGentlemanScript(script_s* s);
bool CeladonDeptStore1FTeacherScript(script_s* s);
bool CeladonDeptStore1FDirectory(script_s* s);
bool CeladonDeptStore1FElevatorButton(script_s* s);
extern const txt_cmd_s CeladonDeptStore1FReceptionistText[];
extern const txt_cmd_s CeladonDeptStore1FGentlemanText[];
extern const txt_cmd_s CeladonDeptStore1FTeacherText[];
extern const txt_cmd_s CeladonDeptStore1FDirectoryText[];
