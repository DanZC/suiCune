#pragma once
//// EVENTS
extern const struct MapScripts Route42_MapScripts;
extern const struct MapEvents Route42_MapEvents;

//// CODE

bool Route42_MapScripts_DummyScene0(script_s* s);
bool Route42_MapScripts_DummyScene1(script_s* s);
bool Route42SuicuneScript(script_s* s);
extern const struct TrainerObj TrainerFisherTully;
bool TrainerFisherTully_Script(script_s* s);
extern const struct TrainerObj TrainerPokemaniacShane;
bool TrainerPokemaniacShane_Script(script_s* s);
extern const struct TrainerObj TrainerHikerBenjamin;
bool TrainerHikerBenjamin_Script(script_s* s);
bool Route42Sign1(script_s* s);
bool MtMortarSign1(script_s* s);
bool MtMortarSign2(script_s* s);
bool Route42Sign2(script_s* s);
extern const struct ItemBall Route42UltraBall;
extern const struct ItemBall Route42SuperPotion;
bool Route42FruitTree1(script_s* s);
bool Route42FruitTree2(script_s* s);
bool Route42FruitTree3(script_s* s);
extern const struct HiddenItem Route42HiddenMaxPotion;
extern const uint8_t Route42SuicuneMovement[];
extern const txt_cmd_s FisherTullySeenText[];
extern const txt_cmd_s FisherTullyBeatenText[];
extern const txt_cmd_s FisherTullyAfterBattleText[];
extern const txt_cmd_s HikerBenjaminSeenText[];
extern const txt_cmd_s HikerBenjaminBeatenText[];
extern const txt_cmd_s HikerBenjaminAfterBattleText[];
extern const txt_cmd_s PokemaniacShaneSeenText[];
extern const txt_cmd_s PokemaniacShaneBeatenText[];
extern const txt_cmd_s PokemaniacShaneAfterBattleText[];
extern const txt_cmd_s Route42Sign1Text[];
extern const txt_cmd_s MtMortarSign1Text[];
extern const txt_cmd_s MtMortarSign2Text[];
extern const txt_cmd_s Route42Sign2Text[];
