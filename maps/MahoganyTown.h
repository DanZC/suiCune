#pragma once
//// EVENTS
extern const struct MapScripts MahoganyTown_MapScripts;
extern const struct MapEvents MahoganyTown_MapEvents;

//// CODE

bool MahoganyTown_MapScripts_DummyScene0(script_s* s);
bool MahoganyTown_MapScripts_DummyScene1(script_s* s);
bool MahoganyTown_MapScripts_FlyPoint(script_s* s);
bool MahoganyTownTryARageCandyBarScript(script_s* s);
bool MahoganyTownPokefanMScript(script_s* s);
bool RageCandyBarMerchantScript(script_s* s);
bool MahoganyTownGrampsScript(script_s* s);
bool MahoganyTownFisherScript(script_s* s);
bool MahoganyTownLassScript(script_s* s);
bool MahoganyTownSign(script_s* s);
bool MahoganyTownRagecandybarSign(script_s* s);
bool MahoganyGymSign(script_s* s);
bool MahoganyTownPokecenterSign(script_s* s);
extern const uint8_t MahoganyTownCollideDownFaceLeftMovement[];
extern const uint8_t MahoganyTownPlayerStepLeftMovement[];
extern const uint8_t MahoganyTownRageCandyBarMerchantBlocksYouMovement[];
extern const uint8_t MahoganyTownRageCandyBarMerchantReturnsMovement[];
extern const txt_cmd_s RageCandyBarMerchantTryOneText[];
extern const txt_cmd_s RageCandyBarMerchantSavorItText[];
extern const txt_cmd_s RageCandyBarMerchantNotEnoughMoneyText[];
extern const txt_cmd_s RageCandyBarMerchantRefusedText[];
extern const txt_cmd_s RageCandyBarMerchantNoRoomText[];
extern const txt_cmd_s RageCandyBarMerchantSoldOutText[];
extern const txt_cmd_s MahoganyTownGrampsText[];
extern const txt_cmd_s MahoganyTownGrampsText_ClearedRocketHideout[];
extern const txt_cmd_s MahoganyTownFisherText[];
extern const txt_cmd_s MahoganyTownLassText[];
extern const txt_cmd_s MahoganyTownSignText[];
extern const txt_cmd_s MahoganyTownRagecandybarSignText[];
extern const txt_cmd_s MahoganyGymSignText[];
