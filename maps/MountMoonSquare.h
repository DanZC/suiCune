#pragma once
//// EVENTS
extern const struct MapScripts MountMoonSquare_MapScripts;
extern const struct MapEvents MountMoonSquare_MapEvents;

//// CODE

bool MountMoonSquare_MapScripts_DummyScene(script_s* s);
bool MountMoonSquare_MapScripts_DisappearMoonStone(script_s* s);
bool MountMoonSquare_MapScripts_DisappearRock(script_s* s);
bool ClefairyDance(script_s* s);
extern const struct HiddenItem MountMoonSquareHiddenMoonStone;
bool DontLitterSign(script_s* s);
bool MtMoonSquareRock(script_s* s);
extern const uint8_t PlayerWalksUpToDancingClefairies[];
extern const uint8_t ClefairyDanceStep1[];
extern const uint8_t ClefairyDanceStep2[];
extern const uint8_t ClefairyDanceStep3[];
extern const uint8_t ClefairyDanceStep4[];
extern const uint8_t ClefairyDanceStep5[];
extern const uint8_t ClefairyDanceStep6[];
extern const uint8_t ClefairyDanceStep7[];
extern const uint8_t ClefairyFleeMovement[];
extern const txt_cmd_s DontLitterSignText[];
