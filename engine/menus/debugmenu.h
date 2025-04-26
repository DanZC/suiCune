#pragma once

#define MAX_OPTIONS_PER_PAGE 7

typedef void (*DebugMenuFunction)();

// void DebugMenu_AddOption(const char* name, DebugMenuFunction function);
// void DebugMenu_RemoveAllOptions(void);
void DebugMenu_PrintStrings(void);
void DebugMenu_MoveCursor(int8_t dir);
void DebugMenu_PlaceCursor(void);
void DebugMenu(void);
void DebugMenu_SoundTest(void);
void DebugMenu_BattleTest(void);
void DebugMenu_GFXTest(void);
void DebugMenu_Stats(void);
void DebugMenu_Pics(void);
void DebugMenu_Scripting(void);
void DebugMenu_Link(void);
void DebugMenu_TradeAnim(void);
void DebugMenu_BattleAnim(void);
void DebugMenu_Credits(void);
void DebugMenu_MysteryGift(void);
void DebugMenu_News(void);
void DebugMenu_MobileTradeAnim(void);
// void debugMenuOptionField();
// void debugMenuOptionFight();
// void debugMenuOptionSubGames();
// void debugMenuOptionMonsterTest();
// void debugMenuOptionName();
