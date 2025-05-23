void CopyBytes(void* de, const void* hl, uint16_t bc);
void CopyBytes_GB(uint16_t de, uint16_t hl, uint16_t bc);
void SwapBytes(void* hl, void* de, uint16_t bc);
void SwapBytes_GB(uint16_t hl, uint16_t de, uint16_t bc);
void ByteFill(void* ptr, uint16_t len, uint8_t value);
void ByteFill_GB(uint16_t ptr, uint16_t len, uint8_t value);
uint8_t GetFarByte(uint8_t a, uint16_t hl);
uint16_t GetFarWord(uint8_t a, uint16_t hl);
void FarCopyWRAM(uint8_t a, uint16_t de, uint16_t hl, uint16_t bc);
uint8_t GetFarWRAMByte(uint8_t bank, uint16_t address);
void GetFarWRAMWord(void);
