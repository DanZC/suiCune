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
extern const txt_cmd_s Text_GearIsImpressive[];
extern const txt_cmd_s Text_WaitPlayer[];
extern const txt_cmd_s Text_WhatDoYouThinkYoureDoing[];
extern const txt_cmd_s Text_ItsDangerousToGoAlone[];
extern const txt_cmd_s Text_YourMonIsAdorable[];
extern const txt_cmd_s Text_TellMomIfLeaving[];
extern const txt_cmd_s Text_CallMomOnGear[];
extern const txt_cmd_s Text_ElmDiscoveredNewMon[];
extern const txt_cmd_s NewBarkTownRivalText1[];
extern const txt_cmd_s NewBarkTownRivalText2[];
extern const txt_cmd_s NewBarkTownSignText[];
extern const txt_cmd_s NewBarkTownPlayersHouseSignText[];
extern const txt_cmd_s NewBarkTownElmsLabSignText[];
extern const txt_cmd_s NewBarkTownElmsHouseSignText[];
