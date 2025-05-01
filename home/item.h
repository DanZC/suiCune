void DoItemEffect(void);
bool CheckTossableItem(item_t item);
bool TossItem(item_pocket_u* pocket, item_t item, uint8_t quantity);
bool ReceiveItem(item_pocket_u* pocket, item_t item, uint8_t quantity);
bool CheckItem(item_pocket_u *pocket, item_t item);
item_pocket_u* GetItemPocket(uint8_t pocket);
