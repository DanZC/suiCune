void CompareBytes(void);
void CompareBytesLong(void);
bool CompareBytes_Conv(uint16_t de, uint16_t hl, uint8_t c);
int CompareBytes_Conv2(const void* de, const void* hl, uint8_t c);
bool CompareBytesLong_Conv(uint16_t de, uint16_t hl, uint16_t bc);
bool CompareBytesLong_Conv2(const void* de, const void* hl, uint16_t bc);

bool Test_CompareBytes(void);
bool Test_CompareBytesLong(void);
