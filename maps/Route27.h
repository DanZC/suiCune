#pragma once
//// EVENTS
extern const struct MapScripts Route27_MapScripts;
extern const struct MapEvents Route27_MapEvents;

//// CODE

bool Route27_MapScripts_DummyScene0(script_s* s);
bool Route27_MapScripts_DummyScene1(script_s* s);
bool FirstStepIntoKantoLeftScene(script_s* s);
bool FirstStepIntoKantoRightScene(script_s* s);
bool FirstStepIntoKantoScene_Continue(script_s* s);
bool Route27FisherScript(script_s* s);
extern const struct TrainerObj TrainerPsychicGilbert;
bool TrainerPsychicGilbert_Script(script_s* s);
extern const struct TrainerObj TrainerBirdKeeperJose2;
bool TrainerBirdKeeperJose2_Script(script_s* s);
extern const struct TrainerObj TrainerCooltrainermBlake;
bool TrainerCooltrainermBlake_Script(script_s* s);
extern const struct TrainerObj TrainerCooltrainermBrian;
bool TrainerCooltrainermBrian_Script(script_s* s);
extern const struct TrainerObj TrainerCooltrainerfReena;
bool TrainerCooltrainerfReena_Script(script_s* s);
extern const struct TrainerObj TrainerCooltrainerfMegan;
bool TrainerCooltrainerfMegan_Script(script_s* s);
bool TohjoFallsSign(script_s* s);
extern const struct ItemBall Route27TMSolarbeam;
extern const struct ItemBall Route27RareCandy;
extern const uint8_t Route27FisherStepLeftTwiceMovement[];
extern const uint8_t Route27FisherStepLeftOnceMovement[];
extern const txt_cmd_s Route27FisherHeyText[];
extern const txt_cmd_s Route27FisherText[];
extern const txt_cmd_s CooltrainermBlakeSeenText[];
extern const txt_cmd_s CooltrainermBlakeBeatenText[];
extern const txt_cmd_s CooltrainermBlakeAfterBattleText[];
extern const txt_cmd_s CooltrainermBrianSeenText[];
extern const txt_cmd_s CooltrainermBrianBeatenText[];
extern const txt_cmd_s CooltrainermBrianAfterBattleText[];
extern const txt_cmd_s CooltrainerfReenaSeenText[];
extern const txt_cmd_s CooltrainerfReenaBeatenText[];
extern const txt_cmd_s CooltrainerfReenaAfterBattleText[];
extern const txt_cmd_s CooltrainerfMeganSeenText[];
extern const txt_cmd_s CooltrainerfMeganBeatenText[];
extern const txt_cmd_s CooltrainerfMeganAfterBattleText[];
extern const txt_cmd_s PsychicGilbertSeenText[];
extern const txt_cmd_s PsychicGilbertBeatenText[];
extern const txt_cmd_s PsychicGilbertAfterBattleText[];
extern const txt_cmd_s BirdKeeperJose2SeenText[];
extern const txt_cmd_s BirdKeeperJose2BeatenText[];
extern const txt_cmd_s BirdKeeperJose2AfterBattleText[];
extern const txt_cmd_s TohjoFallsSignText[];
