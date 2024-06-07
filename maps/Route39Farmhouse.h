#pragma once
//// EVENTS
extern const struct MapScripts Route39Farmhouse_MapScripts;
extern const struct MapEvents Route39Farmhouse_MapEvents;

//// CODE

bool PokefanM_DairyFarmer(script_s* s);
bool FarmerMScript_SellMilk(script_s* s);
bool FarmerMScript_NoMoney(script_s* s);
bool FarmerMScript_NoRoom(script_s* s);
bool FarmerMScript_NoSale(script_s* s);
bool FarmerMScript_Milking(script_s* s);
bool PokefanF_SnoreFarmer(script_s* s);
bool FarmerFScript_GiveSnore(script_s* s);
bool FarmerFScript_GotSnore(script_s* s);
bool FarmerFScript_NoRoomForSnore(script_s* s);
bool FarmhouseBookshelf(script_s* s);
extern const txt_cmd_s FarmerMText_SickCow[];
extern const txt_cmd_s FarmerMText_BuyMilk[];
extern const txt_cmd_s FarmerMText_GotMilk[];
extern const txt_cmd_s FarmerMText_NoMoney[];
extern const txt_cmd_s FarmerMText_NoRoom[];
extern const txt_cmd_s FarmerMText_NoSale[];
extern const txt_cmd_s FarmerMText_Milking[];
extern const txt_cmd_s FarmerFText_InTrouble[];
extern const txt_cmd_s FarmerFText_HealedMiltank[];
extern const txt_cmd_s Text_ReceivedTM13[];
extern const txt_cmd_s FarmerFText_SnoreSpeech[];
