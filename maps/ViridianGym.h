#pragma once
//// EVENTS
extern const struct MapScripts ViridianGym_MapScripts;
extern const struct MapEvents ViridianGym_MapEvents;

//// CODE

bool ViridianGymBlueScript(script_s* s);
bool ViridianGymGuideScript(script_s* s);
bool ViridianGymStatue(script_s* s);
extern const txt_cmd_s LeaderBlueBeforeText[];
extern const txt_cmd_s LeaderBlueWinText[];
extern const txt_cmd_s Text_ReceivedEarthBadge[];
extern const txt_cmd_s LeaderBlueAfterText[];
extern const txt_cmd_s LeaderBlueEpilogueText[];
extern const txt_cmd_s ViridianGymGuideText[];
extern const txt_cmd_s ViridianGymGuideWinText[];
