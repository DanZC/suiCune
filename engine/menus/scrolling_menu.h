void v_InitScrollingMenu(void);
void v_InitScrollingMenu_Conv(const struct MenuData* data);
void v_ScrollingMenu(void);
void v_ScrollingMenu_Conv(const struct MenuData* data);
void ScrollingMenu_InitDisplay(void);
void ScrollingMenu_InitDisplay_Conv(const struct MenuData* data);
void ScrollingMenuJoyAction(void);
u8_flag_s ScrollingMenuJoyAction_Conv(const struct MenuData* data);
void ScrollingMenu_GetCursorPosition(void);
uint8_t ScrollingMenu_GetCursorPosition_Conv(void);
void ScrollingMenu_ClearLeftColumn(void);
void InitScrollingMenuCursor(void);
void InitScrollingMenuCursor_Conv(const struct MenuData* data);
void ScrollingMenu_InitFlags(void);
void ScrollingMenu_InitFlags_Conv(const struct MenuData* data);
void ScrollingMenu_ValidateSwitchItem(void);
void ScrollingMenu_ValidateSwitchItem_Conv(void);
void ScrollingMenu_UpdateDisplay(void);
void ScrollingMenu_UpdateDisplay_Conv(const struct MenuData* data);
void ScrollingMenu_CallFunctions1and2(void);
void ScrollingMenu_CallFunctions1and2_Conv(const struct MenuData* data, tile_t* hl);
void ScrollingMenu_PlaceCursor(void);
void ScrollingMenu_PlaceCursor_Conv(const struct MenuData* data);
void ScrollingMenu_CheckCallFunction3(void);
void ScrollingMenu_CheckCallFunction3_Conv(const struct MenuData* data);
void ScrollingMenu_GetListItemCoordAndFunctionArgs(void);
void ScrollingMenu_GetListItemCoordAndFunctionArgs_Conv(const struct MenuData* data, uint8_t a);