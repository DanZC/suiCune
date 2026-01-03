void MobileTradeAnimation_SendGivemonToGTS(void);
void MobileTradeAnimation_RetrieveGivemonFromGTS(void);
void MobileTradeAnimation_ReceiveGetmonFromGTS(void);
void asm_108018(uint8_t a);
void Function108026(void);
void Function10802a(void);
void asm_10802c(uint8_t a);
void Function10803d(void);
void Function10804d(void);
void RunMobileTradeAnim_Frontpics(const uint8_t* de);
void RunMobileTradeAnim_NoFrontpics(const uint8_t* de);
void Function1080b7(void);
void Function108157(void);
void MobileTradeAnim_ClearTiles(void);
void MobileTradeAnim_ClearBGMap(void);
void MobileTradeAnim_GetFrontpic(uint8_t* de, species_t species, uint16_t dvs);
void Function108201(uint8_t* de, species_t species, uint16_t dvs);
void Function108219(species_t species);
void Function108229(species_t species);
void MobileTradeAnim_InitSpeciesName(uint8_t* de, species_t species);
bool MobileTradeAnim_JumptableLoop(void);
void MobileTradeAnim_Next(void);
void GetMobileTradeAnimByte(void);
void EndMobileTradeAnim(void);
void WaitMobileTradeSpriteAnims(uint8_t c);
void Function1082db(void);
void Function1082f0(uint16_t* hl, uint8_t c);
void Function1082fa(uint16_t* hl, uint8_t c);
void MobileTradeAnim_ShowPlayerMonToBeSent(void);
void MobileTradeAnim_ShowOTMonFromTrade(void);
void MobileTradeAnim_ShowPlayerMonForGTS(void);
void MobileTradeAnim_ShowOTMonFromGTS(void);
void MobileTradeAnim_GetOddEgg(void);
void MobileTradeAnim_02(void);
void MobileTradeAnim_10(void);
void MobileTradeAnim_11(void);
void MobileTradeAnim_GiveTrademon1(void);
void MobileTradeAnim_GiveTrademon2(void);
void MobileTradeAnim_05(void);
void MobileTradeAnim_06(void);
void MobileTradeAnim_07(void);
void MobileTradeAnim_GetTrademon1(void);
void MobileTradeAnim_GetTrademon2(void);
void MobileTradeAnim_GetTrademon3(void);
void MobileTradeAnim_0f(void);
void MobileTradeAnim_FadeToBlack(void);
void Function10895e(void);
void Function108963(void);
void asm_108966(const uint8_t* de);
void Function10898a(species_t species, uint16_t dvs);
void MobileTradeAnim_DisplayMonToBeSent(void);
void MobileTradeAnim_DisplayReceivedMon(void);
void MobileTradeAnim_DisplayEggData(void);
void Function108a33(void);
void MobileTradeAnim_LoadMonTemplate(void);
void MobileTradeAnim_MonDisplay_UpdateBGMap(void);
void MobileTradeAnim_MonDisplay_PrintSpeciesNumber(species_t species);
void MobileTradeAnim_MonDisplay_PrintSpeciesName(uint8_t* de);
void MobileTradeAnim_MonDisplay_PrintOTNameAndGender(uint8_t* de, uint8_t a);
void MobileTradeAnim_MonDisplay_PrintIDNumber(const void* de);
void MobileTradeAnim_ClearTilemap(void);
void Function108ad4(uint8_t a);
void Function108af4(void);
void Function108b45(void);
void Function108b5a(void);
void Function108b78(uint16_t* hl, uint8_t c);
void Palette_108b98(void);
void Function108b98(void);
void MobileTradeAnim_DeleteSprites(void);
void MobileTradeAnim_AnimateSentPulse(struct SpriteAnim* bc);
void MobileTradeAnim_AnimateOTPulse(struct SpriteAnim* bc);
void Function108bec(void);
void Function108c16(void);
void Function108c2b(void);
void Function108c40(void);
void Function108c6d(void);
void Function108c80(void);
void DebugMobileTrade(void);
void LoadMobileAdapterPalette(void);
extern const char MobileTradeSpritesGFX[];
extern const char MobileTradeGFX[];
extern const char MobileTradeTilemapLZ[];
extern const char MobileTradeAttrmapLZ[];
void UnusedMobilePulsePalettes(void);
extern const char MobileTradeBGPalettes[];
extern const char MobileTradeOB1Palettes[];
extern const char MobileTradeOB2Palettes[];
extern const char MobileCable1GFX[];
extern const char MobileCable2GFX[];
extern const uint16_t MobileAdapterPalettes[];
//#include "gfx/mobile/mobile_trade_sprites.2bpp.lz"
//#include "gfx/mobile/mobile_trade.2bpp.lz"
//#include "gfx/mobile/mobile_trade.tilemap.lz"
//#include "gfx/mobile/mobile_trade.attrmap.lz"
//#include "gfx/mobile/unused_mobile_pulses.pal"
//#include "gfx/mobile/mobile_trade_bg.pal"
//#include "gfx/mobile/mobile_trade_ob1.pal"
//#include "gfx/mobile/mobile_trade_ob2.pal"
//#include "gfx/mobile/mobile_cable_1.2bpp"
//#include "gfx/mobile/mobile_cable_2.2bpp"
//#include "gfx/mobile/mobile_adapters.pal"
