void v_AnimateHPBar(tile_t* hl);
bool ShortAnim_UpdateVariables(uint16_t bc);
bool LongAnim_UpdateVariables(uint16_t bc);
void ShortHPBarAnim_UpdateTiles(tile_t* hl);
void LongHPBarAnim_UpdateTiles(tile_t* hl);
void HPBarAnim_RedrawHPBar(tile_t* hl, uint8_t d, uint8_t e, uint8_t b, uint8_t c);
void HPBarAnim_UpdateHPRemaining(tile_t* hl);
void HPBarAnim_PaletteUpdate(uint8_t e);
void HPBarAnim_BGMapUpdate(void);
void ShortHPBar_CalcPixelFrame(void);
