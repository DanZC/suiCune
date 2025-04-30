void PrintLetterDelay(void);
void CopyDataUntil_GB(uint16_t de, uint16_t hl, uint16_t bc);
void CopyDataUntil(void* de, const void* hl, const void* bc);
uint8_t* PrintNum(uint8_t* hl, const void* de, uint8_t b, uint8_t c);
uint16_t PrintNum_GB(uint16_t hl, uint16_t de, uint8_t b, uint8_t c);
uint8_t* MobilePrintNum(uint8_t* hl, const void* de, uint8_t b, uint8_t c);
void FarPrintText(void);
void CallPointerAt(void);
