void Credits(uint8_t b);
bool Credits_HandleAButton(void);
void Credits_HandleBButton(void);
void Credits_Jumptable(void);
void Credits_Next(void);
void Credits_LoopBack(void);
void Credits_PrepBGMapUpdate(void);
void Credits_UpdateGFXRequestPath(void);
void Credits_RequestGFX(void);
void Credits_LYOverride(void);
void ParseCredits(void);
void ConstructCreditsTilemap(void);
void DrawCreditsBorder(tile_t* hl, uint8_t a);
void GetCreditsPalette(void);
extern const uint16_t CreditsPalettes[];
uint8_t* Credits_LoadBorderGFX(void);
void Credits_TheEnd(void);
extern const char CreditsBorderGFX[];
// void CreditsMonsGFX(void);
extern const char CreditsPichuGFX[];
extern const char CreditsSmoochumGFX[];
extern const char CreditsDittoGFX[];
extern const char CreditsIgglybuffGFX[];
//#include "constants.h"
//#include "gfx/credits/credits.pal"
//#include "data/credits_script.h"
//#include "data/credits_strings.h"
