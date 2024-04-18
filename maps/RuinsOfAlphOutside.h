#pragma once
//// EVENTS
extern const struct MapScripts RuinsOfAlphOutside_MapScripts;
extern const struct MapEvents RuinsOfAlphOutside_MapEvents;

//// CODE

bool RuinsOfAlphOutside_MapScripts_DummyScene0(script_s* s);
bool RuinsOfAlphOutside_MapScripts_DummyScene1(script_s* s);
bool RuinsOfAlphOutside_MapScripts_ScientistCallback(script_s* s);
bool RuinsOfAlphOutside_MapScripts_MaybeScientist(script_s* s);
bool RuinsOfAlphOutside_MapScripts_YesScientist(script_s* s);
bool RuinsOfAlphOutside_MapScripts_NoScientist(script_s* s);
bool RuinsOfAlphOutsideScientistScene1(script_s* s);
bool RuinsOfAlphOutsideScientistScene2(script_s* s);
bool RuinsOfAlphOutsideScientistScript(script_s* s);
bool RuinsOfAlphOutsideScientistSceneContinue(script_s* s);
bool RuinsOfAlphOutsideFisherScript(script_s* s);
bool RuinsOfAlphOutsideYoungster1Script(script_s* s);
bool RuinsOfAlphOutsideYoungster2Script(script_s* s);
extern const struct TrainerObj TrainerPsychicNathan;
bool TrainerPsychicNathan_Script(script_s* s);
extern const struct TrainerObj TrainerSuperNerdStan;
bool TrainerSuperNerdStan_Script(script_s* s);
bool RuinsOfAlphOutsideMysteryChamberSign(script_s* s);
bool RuinsOfAlphSign(script_s* s);
bool RuinsOfAlphResearchCenterSign(script_s* s);
extern const uint8_t RuinsOfAlphOutsideScientistWalkToLabMovement[];
extern const uint8_t RuinsOfAlphOutsidePlayerEnterLabMovement[];
extern const txt_cmd_s RuinsOfAlphOutsideScientistText[];
extern const txt_cmd_s SuperNerdStanSeenText[];
extern const txt_cmd_s SuperNerdStanBeatenText[];
extern const txt_cmd_s SuperNerdStanAfterBattleText[];
extern const txt_cmd_s PsychicNathanSeenText[];
extern const txt_cmd_s PsychicNathanBeatenText[];
extern const txt_cmd_s PsychicNathanAfterBattleText[];
extern const txt_cmd_s RuinsOfAlphOutsideMysteryChamberSignText[];
extern const txt_cmd_s RuinsOfAlphSignText[];
extern const txt_cmd_s RuinsOfAlphResearchCenterSignText[];
extern const txt_cmd_s RuinsOfAlphOutsideFisherText1[];
extern const txt_cmd_s RuinsOfAlphOutsideFisherText2[];
extern const txt_cmd_s RuinsOfAlphOutsideYoungster1Text[];
extern const txt_cmd_s RuinsOfAlphOutsideYoungster2Text[];
