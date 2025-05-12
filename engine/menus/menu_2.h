void PlaceMenuItemName(const struct MenuData* data, uint8_t* de);
void PlaceMenuItemQuantity(const struct MenuData* data, tile_t* de);
void PlaceMoneyTopRight(void);
void PlaceMoneyBottomLeft(void);
void PlaceMoneyAtTopLeftOfTextbox(void);
void PlaceMoneyTextbox(void);
extern const struct MenuHeader MoneyTopRightMenuHeader;
extern const struct MenuHeader MoneyBottomLeftMenuHeader;
void DisplayCoinCaseBalance(void);
void DisplayMoneyAndCoinBalance(void);
extern const char MoneyString[];
extern const char CoinString[];
extern const char ShowMoney_TerminatorString[];
void StartMenu_PrintSafariGameStatus(void);
void StartMenu_DrawBugContestStatusBox(void);
void StartMenu_PrintBugContestStatus(void);
bool FindApricornsInBag(void);
//#include "data/items/apricorn_balls.h"
