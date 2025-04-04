void PrintLetterDelay(void);
void PrintLetterDelay_Conv(void);
void CopyDataUntil(void);
void CopyDataUntil_Conv(uint16_t de, uint16_t hl, uint16_t bc);
void CopyDataUntil_Conv2(void* de, const void* hl, const void* bc);
void PrintNum(void);
uint16_t PrintNum_Conv(uint16_t hl, uint16_t de, uint8_t b, uint8_t c);
uint8_t* PrintNum_Conv2(uint8_t* hl, const void* de, uint8_t b, uint8_t c);
uint8_t* MobilePrintNum(uint8_t* hl, const void* de, uint8_t b, uint8_t c);
void FarPrintText(void);
void CallPointerAt(void);
