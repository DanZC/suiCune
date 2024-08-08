#pragma once
//// EVENTS
extern const struct MapScripts CinnabarIsland_MapScripts;
extern const struct MapEvents CinnabarIsland_MapEvents;

//// CODE

bool CinnabarIsland_MapScripts_FlyPoint(script_s* s);
bool CinnabarIslandBlue(script_s* s);
bool CinnabarIslandGymSign(script_s* s);
bool CinnabarIslandSign(script_s* s);
bool CinnabarIslandPokecenterSign(script_s* s);
extern const struct HiddenItem CinnabarIslandHiddenRareCandy;
extern const uint8_t CinnabarIslandBlueTeleport[];
extern const txt_cmd_s CinnabarIslandBlueText[];
extern const txt_cmd_s CinnabarIslandGymSignText[];
extern const txt_cmd_s CinnabarIslandSignText[];
