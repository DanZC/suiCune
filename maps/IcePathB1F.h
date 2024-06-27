#pragma once
//// EVENTS
extern const struct MapScripts IcePathB1F_MapScripts;
extern const struct MapEvents IcePathB1F_MapEvents;

//// CODE

bool IcePathB1F_MapScripts_SetUpStoneTable(script_s* s);
extern const struct CmdQueue IcePathB1F_MapScripts_CommandQueue[];
extern const struct Stonetable IcePathB1F_MapScripts_StoneTable[];
bool IcePathB1F_MapScripts_Boulder1(script_s* s);
bool IcePathB1F_MapScripts_Boulder2(script_s* s);
bool IcePathB1F_MapScripts_Boulder3(script_s* s);
bool IcePathB1F_MapScripts_Boulder4(script_s* s);
bool IcePathB1F_MapScripts_FinishBoulder(script_s* s);
bool IcePathB1FBoulder(script_s* s);
extern const struct ItemBall IcePathB1FIron;
extern const struct HiddenItem IcePathB1FHiddenMaxPotion;
extern const txt_cmd_s IcePathBoulderFellThroughText[];
