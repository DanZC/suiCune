void ClearBGPalettes(void);
void ClearBGPalettes_Conv(void);
void WaitBGMap(void);
void WaitBGMap_Conv(void);
void WaitBGMap2(void);
void IsCGB(void);
bool IsCGB_Conv(void);
void ApplyTilemap(void);
void ApplyTilemap_Conv(void);
void CGBOnly_CopyTilemapAtOnce(void);
void CopyTilemapAtOnce(void);
void CopyTilemapAtOnce_Conv(void);
void CopyAttrmapAndTilemapToWRAMBank3(void);
void v_CopyTilemapAtOnce(void);
void v_CopyTilemapAtOnce_Conv(void);
void v_CopyTilemapAtOnce_CopyBGMapViaStack(void);
void v_CopyTilemapAtOnce_CopyBGMapViaStack_Conv(uint16_t hl);
void v_CopyTilemapAtOnce_CopyBGMapViaStack_Conv2(const uint8_t* sp);
void SetPalettes(void);
void SetPalettes_Conv(void);
void ClearPalettes(void);
void ClearPalettes_Conv(void);
void GetMemSGBLayout(void);
void GetSGBLayout(void);
void GetSGBLayout_Conv(uint8_t e);
void SetHPPal(void);
void SetHPPal_Conv(uint8_t* hl, uint8_t e);
void GetHPPal(void);
uint8_t GetHPPal_Conv(uint8_t e);
