#pragma once
//// EVENTS
extern const struct MapScripts CherrygrovePokecenter1F_MapScripts;
extern const struct MapEvents CherrygrovePokecenter1F_MapEvents;

//// CODE

// bool CherrygrovePokecenter1F_MapScripts(script_s* s);
bool CherrygrovePokecenter1FNurseScript(script_s* s);
bool CherrygrovePokecenter1FFisherScript(script_s* s);
bool CherrygrovePokecenter1FGentlemanScript(script_s* s);
bool CherrygrovePokecenter1FTeacherScript(script_s* s);
extern const struct TextCmd CherrygrovePokecenter1FFisherText[];
extern const struct TextCmd CherrygrovePokecenter1FGentlemanText[];
extern const struct TextCmd CherrygrovePokecenter1FTeacherText[];
extern const struct TextCmd CherrygrovePokecenter1FTeacherText_CommCenterOpen[];
// bool CherrygrovePokecenter1F_MapEvents(script_s* s);
