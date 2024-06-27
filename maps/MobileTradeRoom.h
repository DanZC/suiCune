#pragma once
//// EVENTS
extern const struct MapScripts MobileTradeRoom_MapScripts;
extern const struct MapEvents MobileTradeRoom_MapEvents;

//// CODE

bool MobileTradeRoom_MapScripts_InitializeMobileTradeRoom(script_s* s);
bool MobileTradeRoom_MapScripts_DummyScene(script_s* s);
bool MobileTradeRoom_MapScripts_InitializeAndPreparePokecenter2F(script_s* s);
bool MobileTradeRoomConsoleScript(script_s* s);
extern const txt_cmd_s MobileTradeRoom_EstablishingCommsText[];
