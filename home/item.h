void DoItemEffect(void);
void CheckTossableItem(void);
bool CheckTossableItem_Conv(item_t item);
void TossItem(void);
bool TossItem_Conv(item_pocket_s* pocket, item_t item);
void ReceiveItem(void);
bool ReceiveItem_Conv(item_pocket_s* pocket, item_t item, uint8_t quantity);
void CheckItem(void);
bool CheckItem_Conv(item_t item, item_t* hl);
