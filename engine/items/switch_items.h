void SwitchItemsInBag(void);
void ItemSwitch_CopyItemToBuffer(uint8_t a);
void ItemSwitch_CopyBufferToItem(uint8_t a);
uint8_t* ItemSwitch_GetNthItem(uint8_t n);
int16_t ItemSwitch_GetItemOffset(uint8_t d, uint8_t e);
uint16_t ItemSwitch_GetItemFormatSize(void);
uint8_t ItemSwitch_GetItemQuantity(uint8_t n);
void ItemSwitch_BackwardsCopyBytes(uint8_t* de, const uint8_t* hl, uint16_t bc);
