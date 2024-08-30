// void MobileMenuGFX(void);
extern const char MobileMenuGFX[];
void MainMenu(void);
// void MainMenuItems(void);
extern const uint8_t* MainMenuItems[];
void MainMenu_GetWhichMenu(void);
uint8_t MainMenu_GetWhichMenu_Conv(void);
void MainMenuJoypadLoop(void);
bool MainMenuJoypadLoop_Conv(void);
void MainMenu_PrintCurrentTimeAndDay(void);
void MainMenu_PrintCurrentTimeAndDay_Conv(void);
void ClearTilemapEtc(void);
void ClearTilemapEtc_Conv(void);
bool MainMenu_NewGame(void);
bool MainMenu_Option(void);
bool MainMenu_Continue(void);
bool MainMenu_DebugRoom(void);
bool MainMenu_MysteryGift(void);
//#include "gfx/mobile/mobile_menu.2bpp"
