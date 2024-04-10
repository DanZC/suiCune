void PlaceMenuItemName(void);
void PlaceMenuItemName_Conv(const struct MenuData* data, uint8_t* de);
void PlaceMenuItemQuantity(void);
void PlaceMenuItemQuantity_Conv(const struct MenuData* data, tile_t* de);
void PlaceMoneyTopRight(void);
void PlaceMoneyBottomLeft(void);
void PlaceMoneyAtTopLeftOfTextbox(void);
void PlaceMoneyTextbox(void);
extern const struct MenuHeader MoneyTopRightMenuHeader;
extern const struct MenuHeader MoneyBottomLeftMenuHeader;
void DisplayCoinCaseBalance(void);
void DisplayMoneyAndCoinBalance(void);
void MoneyString(void);
void CoinString(void);
void ShowMoney_TerminatorString(void);
void StartMenu_PrintSafariGameStatus(void);
void StartMenu_DrawBugContestStatusBox(void);
void StartMenu_PrintBugContestStatus(void);
void FindApricornsInBag(void);
//#include "data/items/apricorn_balls.h"
