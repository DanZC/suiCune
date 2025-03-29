void UpdatePalsIfCGB(void);
bool UpdatePalsIfCGB_Conv(void);
void UpdateCGBPals(void);
bool UpdateCGBPals_Conv(void);
void ForceUpdateCGBPals(void);
bool ForceUpdateCGBPals_Conv(void);
void DmgToCgbBGPals(void);
void DmgToCgbBGPals_Conv(uint8_t a);
void DmgToCgbObjPals(void);
void DmgToCgbObjPals_Conv(uint8_t d, uint8_t e);
void DmgToCgbObjPal0(void);
void DmgToCgbObjPal0_Conv(uint8_t a);
void DmgToCgbObjPal1(void);
void DmgToCgbObjPal1_Conv(uint8_t a);
void CopyPals(void);
void CopyPals_Conv(uint16_t hl, uint16_t de, uint8_t b, uint8_t c);
void CopyPals_Conv2(uint16_t* hl, const uint16_t* de, uint8_t b, uint8_t c);
void ClearVBank1(void);
void GSReloadPalettes(void);
void ReloadSpritesNoPalettes(void);
void SwapTextboxPalettes(void);
void SwapTextboxPalettes_Conv(void);
void ScrollBGMapPalettes(void);
void ScrollBGMapPalettes_Conv(uint8_t c);
