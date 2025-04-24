uint8_t CountSetBits(const uint8_t* hl, uint8_t b);
uint8_t GetWeekday(void);
void SetSeenAndCaughtMon(dex_t c);
void SetSeenMon(dex_t c);
bool CheckCaughtMon(dex_t c);
bool CheckSeenMon(dex_t c);
bool PokedexFlagAction(uint8_t* hl, dex_t c, uint8_t b);
