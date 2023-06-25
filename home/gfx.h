void Get2bppViaHDMA(void);
void Get1bppViaHDMA(void);
void FarCopyBytesDouble_DoubleBankSwitch(void);
void SafeHDMATransfer(void);
void UpdatePlayerSprite(void);
void LoadStandardFont(void);
void LoadFontsBattleExtra(void);
void LoadFontsExtra(void);
void LoadFontsExtra2(void);
void DecompressRequest2bpp(void);
void FarCopyBytes(void);
void FarCopyBytes_Conv(uint16_t de, uint8_t a, uint16_t hl, uint16_t bc);
void FarCopyBytesDouble(void);
void FarCopyBytesDouble_Conv(uint16_t de, uint8_t a, uint16_t hl, uint16_t bc);
void Request2bpp(void);
void Request2bpp_Conv(uint8_t b, uint16_t de, uint8_t c, uint16_t hl);
void Request1bpp(void);
void Request1bpp_Conv(uint8_t b, uint16_t de, uint8_t c, uint16_t hl);
void Get2bpp(void);
void Get2bpp_Conv(uint8_t b, uint16_t de, uint16_t hl, uint8_t c);
void Copy2bpp(void);
void Copy2bpp_Conv(uint8_t b, uint16_t de, uint16_t hl, uint8_t c);
void Get1bpp(void);
void Get1bpp_Conv(uint16_t hl, uint8_t b, uint16_t de, uint8_t c);
void Copy1bpp(void);
void Copy1bpp_Conv(uint16_t hl, uint8_t b, uint16_t de, uint8_t c);
