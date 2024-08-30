void Load2DMenuData(void);
void Load2DMenuData_Conv(const uint8_t* de);
void StaticMenuJoypad(void);
uint8_t StaticMenuJoypad_Conv(void);
void ScrollingMenuJoypad(void);
uint8_t ScrollingMenuJoypad_Conv(void);
void GetMenuJoypad(void);
uint8_t GetMenuJoypad_Conv(void);
void PlaceHollowCursor(void);
void PlaceHollowCursor_Conv(void);
void HideCursor(void);
uint8_t* HideCursor_Conv(void);
void PushWindow(void);
void PushWindow_Conv(void);
void ExitMenu(void);
void ExitMenu_Conv(void);
void ExitMenu_Conv2(void);
void InitVerticalMenuCursor(void);
void InitVerticalMenuCursor_Conv(const struct MenuData* data);
void CloseWindow(void);
void CloseWindow_Conv2(void);
void RestoreTileBackup(void);
void RestoreTileBackup_Conv(uint8_t* de);
void RestoreTileBackup_Conv2(const uint8_t* de);
void PopWindow(void);
void PopWindow_Conv(uint16_t hl);
void PopWindow_Conv2(struct MenuHeader* hl);
void GetMenuBoxDims(void);
void GetMenuBoxDims_Conv(uint8_t* w, uint8_t* h);
void CopyMenuData(void);
void CopyMenuData_Conv(void);
const struct MenuData* GetMenuData(void);
void GetWindowStackTop(void);
uint16_t GetWindowStackTop_Conv(void);
void PlaceVerticalMenuItems(void);
void PlaceVerticalMenuItems_Conv2(void);
void MenuBox(void);
void MenuBox_Conv(void);
void GetMenuTextStartCoord(void);
void GetMenuTextStartCoord_Conv(uint8_t* b, uint8_t* c);
void GetMenuTextStartCoord_Conv2(const struct MenuData* data, uint8_t* b, uint8_t* c);
void ClearMenuBoxInterior(void);
void ClearWholeMenuBox(void);
void MenuBoxCoord2Tile(void);
uint8_t* MenuBoxCoord2Tile_Conv(void);
void Coord2Tile(void);
uint8_t* Coord2Tile_Conv(uint8_t c, uint8_t b);
void MenuBoxCoord2Attr(void);
uint8_t* MenuBoxCoord2Attr_Conv(void);
void Coord2Attr(void);
uint8_t* Coord2Attr_Conv(uint8_t c, uint8_t b);
void LoadMenuHeader(void);
void LoadMenuHeader_Conv2(const struct MenuHeader* hl);
void CopyMenuHeader(void);
void CopyMenuHeader_Conv(uint16_t hl);
void CopyMenuHeader_Conv2(const struct MenuHeader* hl);
void StoreMenuCursorPosition(void);
void StoreMenuCursorPosition_Conv(uint8_t a);
void MenuTextbox(void);
void MenuTextbox_Conv(const struct TextCmd* hl);
void Menu_DummyFunction(void);
void LoadMenuTextbox(void);
void LoadMenuTextbox_Conv(void);
void MenuTextboxBackup(void);
void MenuTextboxBackup_Conv(const struct TextCmd* hl);
void LoadStandardMenuHeader(void);
void LoadStandardMenuHeader_Conv(void);
void Call_ExitMenu(void);
void VerticalMenu(void);
bool VerticalMenu_Conv(void);
void GetMenu2(void);
u8_flag_s GetMenu2_Conv(const struct MenuHeader* hl);
void CopyNameFromMenu(void);
void CopyNameFromMenu_Conv(uint8_t a);
void YesNoBox(void);
bool YesNoBox_Conv(void);
void PlaceYesNoBox(void);
bool PlaceYesNoBox_Conv(uint8_t b, uint8_t c);
void PlaceGenericTwoOptionBox(void);
void v_YesNoBox(void);
bool v_YesNoBox_Conv(uint8_t b, uint8_t c);
void InterpretTwoOptionMenu(void);
bool InterpretTwoOptionMenu_Conv(void);
// void YesNoMenuHeader(void);
extern const struct MenuHeader YesNoMenuHeader;
void OffsetMenuHeader(void);
void OffsetMenuHeader_Conv2(const struct MenuHeader* hl, uint8_t d, uint8_t e);
void v_OffsetMenuHeader(void);
void v_OffsetMenuHeader_Conv(const struct MenuHeader* hl, uint8_t d, uint8_t e);
void DoNthMenu(void);
u8_flag_s DoNthMenu_Conv(void);
void SetUpMenu(void);
void SetUpMenu_Conv(void);
void DrawVariableLengthMenuBox(void);
void DrawVariableLengthMenuBox_Conv(void);
void MenuWriteText(void);
void MenuWriteText_Conv(void);
void AutomaticGetMenuBottomCoord(void);
void AutomaticGetMenuBottomCoord_Conv(uint8_t* b, uint8_t* c);
void GetMenuIndexSet(void);
const uint8_t* GetMenuIndexSet_Conv2(const struct MenuData* data);
void RunMenuItemPrintingFunction(void);
void RunMenuItemPrintingFunction_Conv(const struct MenuData* data, const uint8_t* de);
void InitMenuCursorAndButtonPermissions(void);
void InitMenuCursorAndButtonPermissions_Conv(void);
void GetScrollingMenuJoypad(void);
bool GetScrollingMenuJoypad_Conv(void);
bool GetScrollingMenuJoypad_Conv2(void);
void GetStaticMenuJoypad(void);
bool GetStaticMenuJoypad_Conv(void);
bool GetStaticMenuJoypad_Conv2(void);
void ContinueGettingMenuJoypad(void);
bool ContinueGettingMenuJoypad_Conv(uint8_t a);
bool ContinueGettingMenuJoypad_Conv2(uint8_t a);
void PlaceMenuStrings(void);
void PlaceMenuStrings_Conv(const char** strings, uint8_t* de, uint8_t selection);
void PlaceNthMenuStrings(void);
void PlaceNthMenuStrings_Conv(const char** strings, uint8_t* de, uint8_t selection);
void GetNthMenuStrings(void);
void MenuJumptable(void);
u8_flag_s MenuJumptable_Conv(void);
void GetMenuDataPointerTableEntry(void);
void ClearWindowData(void);
void ClearWindowData_Conv(void);
void ClearWindowData_Conv2(void);
void MenuClickSound(void);
void MenuClickSound_Conv(uint8_t a);
void PlayClickSFX(void);
void PlayClickSFX_Conv(void);
void MenuTextboxWaitButton(const struct TextCmd* hl);
void Place2DMenuItemName(void);
void Place2DMenuItemName_Conv(uint8_t* hl, const char* de);
void v_2DMenu(void);
u8_flag_s v_2DMenu_Conv(void);
void InterpretBattleMenu(void);
u8_flag_s InterpretBattleMenu_Conv(void);
void InterpretMobileMenu(void);

extern const void* gMenuDataPointer;
