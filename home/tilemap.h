void ClearBGPalettes(void);
void WaitBGMap(void);
void WaitBGMap2(void);
bool IsCGB(void);
void ApplyTilemap(void);
void CGBOnly_CopyTilemapAtOnce(void);
void CopyTilemapAtOnce(void);
void CopyAttrmapAndTilemapToWRAMBank3(void);
void v_CopyTilemapAtOnce(void);
void v_CopyTilemapAtOnce_CopyBGMapViaStack(const tile_t* sp);
void SetPalettes(void);
void ClearPalettes(void);
void GetMemSGBLayout(void);
void GetSGBLayout(uint8_t e);
void SetHPPal(uint8_t* hl, uint8_t e);
uint8_t GetHPPal(uint8_t e);
