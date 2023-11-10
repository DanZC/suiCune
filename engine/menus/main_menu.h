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
void MainMenu_NewGame(void);
void MainMenu_Option(void);
void MainMenu_Continue(void);
void MainMenu_MysteryGift(void);
//#include "gfx/mobile/mobile_menu.2bpp"
