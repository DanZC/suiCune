void MemoryGameGFX(void);
void UnusedCursor_InterpretJoypad_AnimateCursor(void);
void v_CardFlip(void);
void CardFlip_ShuffleDeck(void);
uint16_t CollapseCursorPosition(void);
void GetCoordsOfChosenCard(tile_t** hl, uint16_t* bc, uint8_t card);
void PlaceCardFaceDown(tile_t* hl);
void CardFlip_DisplayCardFaceUp(tile_t* hl);
void CardFlip_UpdateCoinBalanceDisplay(const txt_cmd_s* hl);
void CardFlip_PrintCoinBalance(void);
void CardFlip_InitTilemap(void);
void CardFlip_FillGreenBox(tile_t* hl, uint8_t b, uint8_t c);
void CardFlip_FillBox(tile_t* hl, uint8_t b, uint8_t c, uint8_t a);
void CardFlip_CopyToBox(tile_t* hl, const tile_t* de, uint8_t b, uint8_t c);
void CardFlip_CopyOAM(const uint8_t* hl, uint8_t b, uint8_t c);
void CardFlip_ShiftDigitsUpOnePixel(void);
void CardFlip_BlankDiscardedCardSlot(void);
void CardFlip_CheckWinCondition(void);
void PlaceOAMCardBorder(uint8_t card);
void ChooseCard_HandleJoypad(void);
void CardFlip_UpdateCursorOAM(void);
void CardFlip_InitAttrPals(void);
extern const char CardFlipLZ03[];
extern const char CardFlipOffButtonGFX[];
extern const char CardFlipOnButtonGFX[];
extern const char CardFlipLZ01[];
extern const char CardFlipLZ02[];
extern const char CardFlipTilemap[];
//#include "gfx/card_flip/card_flip.pal"
//#include "gfx/card_flip/card_flip_3.2bpp.lz"
//#include "gfx/card_flip/off.2bpp"
//#include "gfx/card_flip/on.2bpp"
//#include "gfx/card_flip/card_flip_1.2bpp.lz"
//#include "gfx/card_flip/card_flip_2.2bpp.lz"
//#include "gfx/card_flip/card_flip.tilemap"
