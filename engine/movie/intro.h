void CrystalIntro(void);
// void CrystalIntro_InitRAMAddrs(void);
// void IntroSceneJumper(void);
// void IntroScenes(void);
// void NextIntroScene(void);
// void IntroScene1(void);
// void IntroScene2(void);
// void IntroScene3(void);
// void IntroScene4(void);
// void IntroScene5(void);
// void IntroScene6(void);
// void IntroScene7(void);
// void IntroScene8(void);
// void IntroScene9(void);
// void IntroScene10(void);
// void IntroScene11(void);
// void IntroScene12(void);
// void IntroScene13(void);
// void IntroScene14(void);
// void IntroScene15(void);
// void IntroScene16(void);
// void IntroScene17(void);
// void IntroScene18(void);
// void IntroScene19(void);
// void IntroScene20(void);
// void IntroScene21(void);
// void IntroScene22(void);
// void IntroScene23(void);
// void IntroScene24(void);
// void IntroScene25(void);
// void IntroScene26(void);
// void IntroScene27(void);
// void IntroScene28(void);
// void Intro_Scene24_ApplyPaletteFade(uint8_t a);
// void CrystalIntro_InitUnownAnim(uint16_t de);
// void CrystalIntro_UnownFade(uint8_t a);
// void Intro_Scene20_AppearUnown(uint8_t pal);
// void Intro_FadeUnownWordPals(uint8_t a);
// void Intro_LoadTilemap(void);
// void Intro_Scene16_AnimateSuicune(void);
// void Intro_ColoredSuicuneFrameSwap(void);
// void Intro_RustleGrass(void);
// void Intro_SetCGBPalUpdate(void);
// void Intro_ClearBGPals(void);
// void Intro_DecompressRequest2bpp_128Tiles(void);
// void Intro_DecompressRequest2bpp_128Tiles(uint16_t hl, uint16_t de);
// void Intro_DecompressRequest2bpp_255Tiles(void);
// void Intro_DecompressRequest2bpp_255Tiles(uint16_t hl, uint16_t de);
// void Intro_DecompressRequest2bpp_64Tiles(void);
// void Intro_DecompressRequest2bpp_64Tiles(uint16_t hl, uint16_t de);
// void Intro_ResetLYOverrides(void);
// void Intro_PerspectiveScrollBG(void);
// void IntroSuicuneRunGFX(void);
// void IntroPichuWooperGFX(void);
// void IntroBackgroundGFX(void);
// void IntroBackgroundTilemap(void);
// void IntroBackgroundAttrmap(void);
// void IntroBackgroundPalette(void);
// void IntroUnownsGFX(void);
// void IntroPulseGFX(void);
// void IntroUnownATilemap(void);
// void IntroUnownAAttrmap(void);
// void IntroUnownHITilemap(void);
// void IntroUnownHIAttrmap(void);
// void IntroUnownsTilemap(void);
// void IntroUnownsAttrmap(void);
// void IntroUnownsPalette(void);
// void IntroCrystalUnownsGFX(void);
// void IntroCrystalUnownsTilemap(void);
// void IntroCrystalUnownsAttrmap(void);
// void IntroCrystalUnownsPalette(void);
// void IntroSuicuneCloseGFX(void);
// void IntroSuicuneCloseTilemap(void);
// void IntroSuicuneCloseAttrmap(void);
// void IntroSuicuneClosePalette(void);
// void IntroSuicuneJumpGFX(void);
// void IntroSuicuneBackGFX(void);
// void IntroSuicuneJumpTilemap(void);
// void IntroSuicuneJumpAttrmap(void);
// void IntroSuicuneBackTilemap(void);
// void IntroSuicuneBackAttrmap(void);
// void IntroSuicunePalette(void);
// void IntroUnownBackGFX(void);
// void IntroGrass1GFX(void);
// void IntroGrass2GFX(void);
// void IntroGrass3GFX(void);
// void IntroGrass4GFX(void);
//#include "gfx/intro/fade.pal"
//#include "gfx/intro/unown_1.pal"
//#include "gfx/intro/unown_2.pal"
//#include "gfx/intro/suicune_run.2bpp.lz"
//#include "gfx/intro/pichu_wooper.2bpp.lz"
//#include "gfx/intro/background.2bpp.lz"
//#include "gfx/intro/background.tilemap.lz"
//#include "gfx/intro/background.attrmap.lz"
//#include "gfx/intro/background.pal"
//#include "gfx/intro/unowns.2bpp.lz"
//#include "gfx/intro/pulse.2bpp.lz"
//#include "gfx/intro/unown_a.tilemap.lz"
//#include "gfx/intro/unown_a.attrmap.lz"
//#include "gfx/intro/unown_hi.tilemap.lz"
//#include "gfx/intro/unown_hi.attrmap.lz"
//#include "gfx/intro/unowns.tilemap.lz"
//#include "gfx/intro/unowns.attrmap.lz"
//#include "gfx/intro/unowns.pal"
//#include "gfx/intro/crystal_unowns.2bpp.lz"
//#include "gfx/intro/crystal_unowns.tilemap.lz"
//#include "gfx/intro/crystal_unowns.attrmap.lz"
//#include "gfx/intro/crystal_unowns.pal"
//#include "gfx/intro/suicune_close.2bpp.lz"
//#include "gfx/intro/suicune_close.tilemap.lz"
//#include "gfx/intro/suicune_close.attrmap.lz"
//#include "gfx/intro/suicune_close.pal"
//#include "gfx/intro/suicune_jump.2bpp.lz"
//#include "gfx/intro/suicune_back.2bpp.lz"
//#include "gfx/intro/suicune_jump.tilemap.lz"
//#include "gfx/intro/suicune_jump.attrmap.lz"
//#include "gfx/intro/suicune_back.tilemap.lz"
//#include "gfx/intro/suicune_back.attrmap.lz"
//#include "gfx/intro/suicune.pal"
//#include "gfx/intro/unown_back.2bpp.lz"
//#include "gfx/intro/grass1.2bpp"
//#include "gfx/intro/grass2.2bpp"
//#include "gfx/intro/grass3.2bpp"
//#include "gfx/intro/grass4.2bpp"
