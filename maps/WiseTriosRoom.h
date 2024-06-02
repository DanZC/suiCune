#pragma once
//// EVENTS
extern const struct MapScripts WiseTriosRoom_MapScripts;
extern const struct MapEvents WiseTriosRoom_MapEvents;

//// CODE

bool WiseTriosRoom_MapScripts_DummyScene0(script_s* s);
bool WiseTriosRoom_MapScripts_DummyScene1(script_s* s);
bool WiseTriosRoom_MapScripts_WiseTrioCallback(script_s* s);
bool WiseTriosRoomSage1Script(script_s* s);
bool WiseTriosRoomSage2Script(script_s* s);
bool WiseTriosRoomSage3Script(script_s* s);
bool WiseTriosRoom_CannotEnterTinTowerScript(script_s* s);
extern const struct TrainerObj TrainerSageGaku;
bool TrainerSageGaku_Script(script_s* s);
extern const struct TrainerObj TrainerSageMasa;
bool TrainerSageMasa_Script(script_s* s);
extern const struct TrainerObj TrainerSageKoji;
bool TrainerSageKoji_Script(script_s* s);
extern const uint8_t WiseTriosRoomSageBlocksPlayerMovement[];
extern const uint8_t WiseTriosRoomSageReturnsMovement[];
extern const uint8_t WiseTriosRoomSageAllowsPassageMovement[];
extern const txt_cmd_s WiseTriosRoomSage1Text[];
extern const txt_cmd_s WiseTriosRoomSage2Text[];
extern const txt_cmd_s WiseTriosRoomSage3BlocksExitText[];
extern const txt_cmd_s WiseTriosRoomSage3Text[];
extern const txt_cmd_s SageGakuSeenText[];
extern const txt_cmd_s SageGakuBeatenText[];
extern const txt_cmd_s SageGakuAfterBattleText[];
extern const txt_cmd_s SageMasaSeenText[];
extern const txt_cmd_s SageMasaBeatenText[];
extern const txt_cmd_s SageMasaAfterBattleText[];
extern const txt_cmd_s SageKojiSeenText[];
extern const txt_cmd_s SageKojiBeatenText[];
extern const txt_cmd_s SageKojiAfterBattleQuestionText[];
extern const txt_cmd_s SageKojiAfterBattleSpeechText[];
extern const txt_cmd_s SageKojiAfterBattleFinalText[];
