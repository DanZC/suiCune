#pragma once
//// EVENTS
extern const struct MapScripts NewBarkTown_MapScripts;
extern const struct MapEvents NewBarkTown_MapEvents;

//// CODE

bool NewBarkTown_MapScripts_DummyScene0(script_s* s);
bool NewBarkTown_MapScripts_DummyScene1(script_s* s);
bool NewBarkTown_MapScripts_FlyPoint(script_s* s);
bool NewBarkTown_TeacherStopsYouScene1(script_s* s);
bool NewBarkTown_TeacherStopsYouScene2(script_s* s);
bool NewBarkTownTeacherScript(script_s* s);
bool NewBarkTownFisherScript(script_s* s);
bool NewBarkTownSilverScript(script_s* s);
bool NewBarkTownSign(script_s* s);
bool NewBarkTownPlayersHouseSign(script_s* s);
bool NewBarkTownElmsLabSign(script_s* s);
bool NewBarkTownElmsHouseSign(script_s* s);
extern const uint8_t NewBarkTown_TeacherRunsToYouMovement1[];
extern const uint8_t NewBarkTown_TeacherRunsToYouMovement2[];
extern const uint8_t NewBarkTown_TeacherBringsYouBackMovement1[];
extern const uint8_t NewBarkTown_TeacherBringsYouBackMovement2[];
extern const uint8_t NewBarkTown_SilverPushesYouAwayMovement[];
extern const uint8_t NewBarkTown_SilverShovesYouOutMovement[];
extern const uint8_t NewBarkTown_SilverReturnsToTheShadowsMovement[];
extern const struct TextCmd Text_GearIsImpressive[];
extern const struct TextCmd Text_WaitPlayer[];
extern const struct TextCmd Text_WhatDoYouThinkYoureDoing[];
extern const struct TextCmd Text_ItsDangerousToGoAlone[];
extern const struct TextCmd Text_YourMonIsAdorable[];
extern const struct TextCmd Text_TellMomIfLeaving[];
extern const struct TextCmd Text_CallMomOnGear[];
extern const struct TextCmd Text_ElmDiscoveredNewMon[];
extern const struct TextCmd NewBarkTownRivalText1[];
extern const struct TextCmd NewBarkTownRivalText2[];
extern const struct TextCmd NewBarkTownSignText[];
extern const struct TextCmd NewBarkTownPlayersHouseSignText[];
extern const struct TextCmd NewBarkTownElmsLabSignText[];
extern const struct TextCmd NewBarkTownElmsHouseSignText[];
