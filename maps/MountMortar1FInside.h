#pragma once
//// EVENTS
extern const struct MapScripts MountMortar1FInside_MapScripts;
extern const struct MapEvents MountMortar1FInside_MapEvents;

//// CODE

extern const struct TrainerObj TrainerPokemaniacMiller;
bool TrainerPokemaniacMiller_Script(script_s* s);
extern const struct TrainerObj TrainerSupernerdMarkus;
bool TrainerSupernerdMarkus_Script(script_s* s);
bool MountMortar1FBoulder(script_s* s);
extern const struct ItemBall MountMortar1FInsideEscapeRope;
extern const struct ItemBall MountMortar1FInsideMaxRevive;
extern const struct ItemBall MountMortar1FInsideHyperPotion;
extern const struct ItemBall MountMortar1FInsideMaxPotion;
extern const struct ItemBall MountMortar1FInsideNugget;
extern const struct ItemBall MountMortar1FInsideIron;
extern const struct ItemBall MountMortar1FInsideUltraBall;
extern const struct HiddenItem MountMortar1FInsideHiddenMaxRepel;
extern const txt_cmd_s PokemaniacMillerSeenText[];
extern const txt_cmd_s PokemaniacMillerBeatenText[];
extern const txt_cmd_s PokemaniacMillerAfterBattleText[];
extern const txt_cmd_s SupernerdMarkusSeenText[];
extern const txt_cmd_s SupernerdMarkusBeatenText[];
extern const txt_cmd_s SupernerdMarkusAfterBattleText[];
