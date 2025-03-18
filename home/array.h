uint16_t IsInArray_GB(uint16_t hl, uint16_t de, uint8_t a);
uint16_t IsInArray_Item(const item_t* hl, item_t a);
bool IsInU8Array(const uint8_t* hl, uint8_t a);
const struct BlockPointer* ArrayFindStructBlockPointer(const struct BlockPointer* hl, uint8_t a);
bool IsInMoveArray(const move_t* hl, uint8_t a);
const uint8_t* SkipNames(const uint8_t* hl, uint8_t a);
uint16_t SkipNames_GB(uint16_t hl, uint8_t a);
uint8_t* AddNTimes(uint8_t* hl, uint16_t bc, uint8_t a);
uint16_t AddNTimes_GB(uint16_t bc, uint16_t hl, uint8_t a);
