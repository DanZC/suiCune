#pragma once
//// EVENTS
extern const struct MapScripts TradeCenter_MapScripts;
extern const struct MapEvents TradeCenter_MapEvents;

//// CODE

bool TradeCenter_MapScripts_InitializeTradeCenter(script_s* s);
bool TradeCenter_MapScripts_DummyScene(script_s* s);
bool TradeCenter_MapScripts_SetupOtherPlayer(script_s* s);
bool TradeCenter_MapScripts_SetWhichKris(script_s* s);
bool TradeCenter_MapScripts_Kris2(script_s* s);
bool TradeCenter_MapScripts_SetWhichChris(script_s* s);
bool TradeCenter_MapScripts_Chris2(script_s* s);
bool TradeCenter_MapScripts_InitializeAndPreparePokecenter2F(script_s* s);
bool TradeCenterConsoleScript(script_s* s);
bool TradeCenterFriendScript(script_s* s);
extern const txt_cmd_s TradeCenterFriendReadyText[];
