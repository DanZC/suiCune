#pragma once
//// EVENTS
extern const struct MapScripts SilphCo1F_MapScripts;
extern const struct MapEvents SilphCo1F_MapEvents;

//// CODE

bool SilphCoReceptionistScript(script_s* s);
bool SilphCoOfficerScript(script_s* s);
extern const txt_cmd_s SilphCoReceptionistText[];
extern const txt_cmd_s SilphCoOfficerText[];
extern const txt_cmd_s SilphCoOfficerText_GotUpGrade[];
