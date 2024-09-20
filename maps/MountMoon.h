#pragma once
//// EVENTS
extern const struct MapScripts MountMoon_MapScripts;
extern const struct MapEvents MountMoon_MapEvents;

//// CODE

bool MountMoon_MapScripts_RivalEncounter(script_s* s);
bool MountMoon_MapScripts_DummyScene(script_s* s);
bool MountMoon_MapScripts_RivalBattle(script_s* s);
extern const uint8_t MountMoonSilverMovementBefore[];
extern const uint8_t MountMoonSilverMovementAfter[];
extern const txt_cmd_s MountMoonSilverTextBefore[];
extern const txt_cmd_s MountMoonSilverTextWin[];
extern const txt_cmd_s MountMoonSilverTextAfter[];
extern const txt_cmd_s MountMoonSilverTextLoss[];
