#include "../../constants.h"
#include "intro.h"
#include "../../home/palettes.h"
#include "../../home/joypad.h"
#include "../../home/delay.h"
#include "../../home/decompress.h"
#include "../../home/gfx.h"
#include "../../home/copy.h"
#include "../../home/sprite_anims.h"
#include "../../home/text.h"
#include "../../home/clear_sprites.h"
#include "../../home/audio.h"
#include "../../home/tilemap.h"
#include "../../engine/gfx/sprites.h"

// Additional waiting to better sync music with scene.
#define TRANSITION_WAIT_FRAMES 60

static void IntroScene1(void);
static void IntroScene2(void);
static void IntroScene3(void);
static void IntroScene4(void);
static void IntroScene5(void);
static void IntroScene6(void);
static void IntroScene7(void);
static void IntroScene8(void);
static void IntroScene9(void);
static void IntroScene10(void);
static void IntroScene11(void);
static void IntroScene12(void);
static void IntroScene13(void);
static void IntroScene14(void);
static void IntroScene15(void);
static void IntroScene16(void);
static void IntroScene17(void);
static void IntroScene18(void);
static void IntroScene19(void);
static void IntroScene20(void);
static void IntroScene21(void);
static void IntroScene22(void);
static void IntroScene23(void);
static void IntroScene24(void);
static void IntroScene25(void);
static void IntroScene26(void);
static void IntroScene27(void);
static void IntroScene28(void);

static void IntroSceneJumper(void);
static void NextIntroScene(void);

static void CrystalIntro_InitRAMAddrs(void);
static void CrystalIntro_InitUnownAnim_Conv(uint16_t de);
static void CrystalIntro_UnownFade_Conv(uint8_t a);

static void Intro_FadeUnownWordPals_Conv(uint8_t a);
static void Intro_LoadTilemap_Conv(uint8_t* tilemap);
static void Intro_Scene16_AnimateSuicune(void);
static void Intro_ColoredSuicuneFrameSwap(void);
static void Intro_RustleGrass_Conv(void);
static void Intro_SetCGBPalUpdate(void);
static void Intro_ClearBGPals_Conv(void);
// static void Intro_DecompressRequest2bpp_128Tiles_Conv(uint16_t hl, uint16_t de);
// static void Intro_DecompressRequest2bpp_255Tiles_Conv(uint16_t hl, uint16_t de);
// static void Intro_DecompressRequest2bpp_64Tiles_Conv(uint16_t hl, uint16_t de);
static void Intro_ResetLYOverrides_Conv(void);
static void Intro_PerspectiveScrollBG_Conv(void);

// void IntroSuicuneRunGFX(void){
// INCBIN "gfx/intro/suicune_run.2bpp.lz"
// }
static const char IntroSuicuneRunGFX[] = "gfx/intro/suicune_run.png";

// void IntroPichuWooperGFX(void){
// INCBIN "gfx/intro/pichu_wooper.2bpp.lz"
// }
static const char IntroPichuWooperGFX[] = "gfx/intro/pichu_wooper.png";

// void IntroBackgroundGFX(void){
// INCBIN "gfx/intro/background.2bpp.lz"
// }
static const char IntroBackgroundGFX[] = "gfx/intro/background.png";

// void IntroBackgroundTilemap(void){
// INCBIN "gfx/intro/background.tilemap.lz"
// }
static const char IntroBackgroundTilemap[] = "gfx/intro/background.tilemap";

// void IntroBackgroundAttrmap(void){
// INCBIN "gfx/intro/background.attrmap.lz"
// }
static const char IntroBackgroundAttrmap[] = "gfx/intro/background.attrmap";

// void IntroBackgroundPalette(void){
// INCLUDE "gfx/intro/background.pal"
// }
static const char IntroBackgroundPalette[] = "gfx/intro/background.pal";

// void IntroUnownsGFX(void){
// INCBIN "gfx/intro/unowns.2bpp.lz"
// }
static const char IntroUnownsGFX[] = "gfx/intro/unowns.png";

// void IntroPulseGFX(void){
// INCBIN "gfx/intro/pulse.2bpp.lz"
// }
static const char IntroPulseGFX[] = "gfx/intro/pulse.png";

// void IntroUnownATilemap(void){
// INCBIN "gfx/intro/unown_a.tilemap.lz"
// }
static const char IntroUnownATilemap[] = "gfx/intro/unown_a.tilemap";

// void IntroUnownAAttrmap(void){
// INCBIN "gfx/intro/unown_a.attrmap.lz"
// }
static const char IntroUnownAAttrmap[] = "gfx/intro/unown_a.attrmap";

// void IntroUnownHITilemap(void){
// INCBIN "gfx/intro/unown_hi.tilemap.lz"
// }
static const char IntroUnownHITilemap[] = "gfx/intro/unown_hi.tilemap";

// void IntroUnownHIAttrmap(void){
// INCBIN "gfx/intro/unown_hi.attrmap.lz"
// }
static const char IntroUnownHIAttrmap[] = "gfx/intro/unown_hi.attrmap";

// void IntroUnownsTilemap(void){
// INCBIN "gfx/intro/unowns.tilemap.lz"
// }
static const char IntroUnownsTilemap[] = "gfx/intro/unowns.tilemap";

// void IntroUnownsAttrmap(void){
// INCBIN "gfx/intro/unowns.attrmap.lz"
// }
static const char IntroUnownsAttrmap[] = "gfx/intro/unowns.attrmap";

// void IntroUnownsPalette(void){
// INCLUDE "gfx/intro/unowns.pal"
// }
static const char IntroUnownsPalette[] = "gfx/intro/unowns.pal";

// void IntroCrystalUnownsGFX(void){
// INCBIN "gfx/intro/crystal_unowns.2bpp.lz"
// }
static const char IntroCrystalUnownsGFX[] = "gfx/intro/crystal_unowns.png";

// void IntroCrystalUnownsTilemap(void){
// INCBIN "gfx/intro/crystal_unowns.tilemap.lz"
// }
static const char IntroCrystalUnownsTilemap[] = "gfx/intro/crystal_unowns.tilemap";

// void IntroCrystalUnownsAttrmap(void){
// INCBIN "gfx/intro/crystal_unowns.attrmap.lz"
// }
static const char IntroCrystalUnownsAttrmap[] = "gfx/intro/crystal_unowns.attrmap";

// void IntroCrystalUnownsPalette(void){
// INCLUDE "gfx/intro/crystal_unowns.pal"
// }
static const char IntroCrystalUnownsPalette[] = "gfx/intro/crystal_unowns.pal";

// void IntroSuicuneCloseGFX(void){
// INCBIN "gfx/intro/suicune_close.2bpp.lz"
// }
static const char IntroSuicuneCloseGFX[] = "gfx/intro/suicune_close.png";

// void IntroSuicuneCloseTilemap(void){
// INCBIN "gfx/intro/suicune_close.tilemap.lz"
// }
static const char IntroSuicuneCloseTilemap[] = "gfx/intro/suicune_close.tilemap";

// void IntroSuicuneCloseAttrmap(void){
// INCBIN "gfx/intro/suicune_close.attrmap.lz"
// }
static const char IntroSuicuneCloseAttrmap[] = "gfx/intro/suicune_close.attrmap";

// void IntroSuicuneClosePalette(void){
// INCLUDE "gfx/intro/suicune_close.pal"
// }
static const char IntroSuicuneClosePalette[] = "gfx/intro/suicune_close.pal";

// void IntroSuicuneJumpGFX(void){
// INCBIN "gfx/intro/suicune_jump.2bpp.lz"
// }
static const char IntroSuicuneJumpGFX[] = "gfx/intro/suicune_jump.png";

// void IntroSuicuneBackGFX(void){
// INCBIN "gfx/intro/suicune_back.2bpp.lz"
// }
static const char IntroSuicuneBackGFX[] = "gfx/intro/suicune_back.png";

// void IntroSuicuneJumpTilemap(void){
// INCBIN "gfx/intro/suicune_jump.tilemap.lz"
// }
static const char IntroSuicuneJumpTilemap[] = "gfx/intro/suicune_jump.tilemap";

// void IntroSuicuneJumpAttrmap(void){
// INCBIN "gfx/intro/suicune_jump.attrmap.lz"
// }
static const char IntroSuicuneJumpAttrmap[] = "gfx/intro/suicune_jump.attrmap";

// void IntroSuicuneBackTilemap(void){
// INCBIN "gfx/intro/suicune_back.tilemap.lz"
// }
static const char IntroSuicuneBackTilemap[] = "gfx/intro/suicune_back.tilemap";

// void IntroSuicuneBackAttrmap(void){
// INCBIN "gfx/intro/suicune_back.attrmap.lz"
// }
static const char IntroSuicuneBackAttrmap[] = "gfx/intro/suicune_back.attrmap";

// void IntroSuicunePalette(void){
// INCLUDE "gfx/intro/suicune.pal"
// }
static const char IntroSuicunePalette[] = "gfx/intro/suicune.pal";

// void IntroUnownBackGFX(void){
// INCBIN "gfx/intro/unown_back.2bpp.lz"
// }
static const char IntroUnownBackGFX[] = "gfx/intro/unown_back.png";

// void IntroGrass1GFX(void){
// INCBIN "gfx/intro/grass1.2bpp"
// }

// void IntroGrass2GFX(void){
// INCBIN "gfx/intro/grass2.2bpp"
// }

// void IntroGrass3GFX(void){
// INCBIN "gfx/intro/grass3.2bpp"
// }

// void IntroGrass4GFX(void){
// INCBIN "gfx/intro/grass4.2bpp"
// }
static const char* IntroGrassGFX[] = {
    "gfx/intro/grass1.png",
    "gfx/intro/grass2.png",
    "gfx/intro/grass3.png",
    "gfx/intro/grass4.png"
};

static uint8_t IntroGrass1GFX[4 * LEN_2BPP_TILE];
static uint8_t IntroGrass2GFX[4 * LEN_2BPP_TILE];
static uint8_t IntroGrass3GFX[4 * LEN_2BPP_TILE];
static uint8_t IntroGrass4GFX[LEN_2BPP_TILE];

void CrystalIntro(void){
    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    // LD_A(MBANK(awGBCPalettes));
    // LDH_addr_A(rSVBK);
    wbank_push(MBANK(awGBCPalettes));
    // LDH_A_addr(hInMenu);
    // PUSH_AF;
    uint8_t in_menu = hram->hInMenu;
    // LDH_A_addr(hVBlank);
    // PUSH_AF;
    uint8_t vblank_num = hram->hVBlank;
    // CALL(aCrystalIntro_InitRAMAddrs);
    CrystalIntro_InitRAMAddrs();

    LoadPNG2bppAssetSectionToVRAM(IntroGrass1GFX, IntroGrassGFX[0], 0, 4);
    LoadPNG2bppAssetSectionToVRAM(IntroGrass2GFX, IntroGrassGFX[1], 0, 4);
    LoadPNG2bppAssetSectionToVRAM(IntroGrass3GFX, IntroGrassGFX[2], 0, 4);
    LoadPNG2bppAssetSectionToVRAM(IntroGrass4GFX, IntroGrassGFX[3], 0, 1);

    // Uncomment line below to fix Suicune colors when disabling ditto/copyright splash screen.
    // DmgToCgbObjPals(0b11100100, 0b11100100);

// loop:
    while(1)
    {
        // CALL(aJoyTextDelay);
        JoyTextDelay();
        // LDH_A_addr(hJoyLast);
        // AND_A(BUTTONS);
        // IF_NZ goto ShutOffMusic;
        if(hram->hJoyLast & (BUTTONS)) {
            // LD_DE(MUSIC_NONE);
            // CALL(aPlayMusic);
            PlayMusic(MUSIC_NONE);
            break;
        }
        // LD_A_addr(wJumptableIndex);
        // BIT_A(7);
        // IF_NZ goto done;
        if(wram->wJumptableIndex & (1 << 7)) 
            break;
        // CALL(aIntroSceneJumper);
        IntroSceneJumper();
        // FARCALL(aPlaySpriteAnimations);
        PlaySpriteAnimations();
        // CALL(aDelayFrame);
        DelayFrame();
        // JP(mCrystalIntro_loop);
    }

    // CALL(aClearBGPalettes);
    // CALL(aClearSprites);
    // CALL(aClearTilemap);
    ClearBGPalettes();
    ClearSprites();
    ClearTilemap();
    // XOR_A_A;
    // LDH_addr_A(hSCX);
    // LDH_addr_A(hSCY);
    hram->hSCX = 0;
    hram->hSCY = 0;
    // LD_A(0x7);
    // LDH_addr_A(hWX);
    hram->hWX = 0x7;
    // LD_A(0x90);
    // LDH_addr_A(hWY);
    hram->hWY = 0x90;
    // POP_AF;
    // LDH_addr_A(hVBlank);
    hram->hVBlank = vblank_num;
    // POP_AF;
    // LDH_addr_A(hInMenu);
    hram->hInMenu = in_menu;
    // POP_AF;
    // LDH_addr_A(rSVBK);
    // RET;
    wbank_pop;
}

static void CrystalIntro_InitRAMAddrs(void){
    // XOR_A_A;
    // LDH_addr_A(hVBlank);
    hram->hVBlank = 0;
    // LD_A(0x1);
    // LDH_addr_A(hInMenu);
    hram->hInMenu = 0x1;
    // XOR_A_A;
    // LDH_addr_A(hMapAnims);
    hram->hMapAnims = 0;
    // REG_A = 0;
    // LD_addr_A(wJumptableIndex);
    wram->wJumptableIndex = 0;
    // RET;
}

static void IntroSceneJumper(void){
    //jumptable ['IntroScenes', 'wJumptableIndex']
    //fast_jumptable(mIntroScenes, wJumptableIndex);
    switch(wram->wJumptableIndex) {
        case 0:  IntroScene1();  break;
        case 1:  IntroScene2();  break;
        case 2:  IntroScene3();  break;
        case 3:  IntroScene4();  break;
        case 4:  IntroScene5();  break;
        case 5:  IntroScene6();  break;
        case 6:  IntroScene7();  break;
        case 7:  IntroScene8();  break;
        case 8:  IntroScene9();  break;
        case 9:  IntroScene10(); break;
        case 10: IntroScene11(); break;
        case 11: IntroScene12(); break;
        case 12: IntroScene13(); break;
        case 13: IntroScene14(); break;
        case 14: IntroScene15(); break;
        case 15: IntroScene16(); break;
        case 16: IntroScene17(); break;
        case 17: IntroScene18(); break;
        case 18: IntroScene19(); break;
        case 19: IntroScene20(); break;
        case 20: IntroScene21(); break;
        case 21: IntroScene22(); break;
        case 22: IntroScene23(); break;
        case 23: IntroScene24(); break;
        case 24: IntroScene25(); break;
        case 25: IntroScene26(); break;
        case 26: IntroScene27(); break;
        case 27: IntroScene28(); break;
    }

    // RET;
}

// void IntroScenes(void){
    //dw ['IntroScene1'];
    //dw ['IntroScene2'];
    //dw ['IntroScene3'];
    //dw ['IntroScene4'];
    //dw ['IntroScene5'];
    //dw ['IntroScene6'];
    //dw ['IntroScene7'];
    //dw ['IntroScene8'];
    //dw ['IntroScene9'];
    //dw ['IntroScene10'];
    //dw ['IntroScene11'];
    //dw ['IntroScene12'];
    //dw ['IntroScene13'];
    //dw ['IntroScene14'];
    //dw ['IntroScene15'];
    //dw ['IntroScene16'];
    //dw ['IntroScene17'];
    //dw ['IntroScene18'];
    //dw ['IntroScene19'];
    //dw ['IntroScene20'];
    //dw ['IntroScene21'];
    //dw ['IntroScene22'];
    //dw ['IntroScene23'];
    //dw ['IntroScene24'];
    //dw ['IntroScene25'];
    //dw ['IntroScene26'];
    //dw ['IntroScene27'];
    //dw ['IntroScene28'];
    // IntroScene1();
    // IntroScene2();
    // IntroScene3();
    // IntroScene4();
    // IntroScene5();
    // IntroScene6();
    // IntroScene7();
    // IntroScene8();
    // IntroScene9();
    // IntroScene10();
    // IntroScene11();
    // IntroScene12();
    // IntroScene13();
    // IntroScene14();
    // IntroScene15();
    // IntroScene16();
    // IntroScene17();
    // IntroScene18();
    // IntroScene19();
    // IntroScene20();
    // IntroScene21();
    // IntroScene22();
    // IntroScene23();
    // IntroScene24();
    // IntroScene25();
    // IntroScene26();
    // IntroScene27();
    // IntroScene28();

    // RET;
// }

static void NextIntroScene(void){
    // LD_HL(wJumptableIndex);
    // INC_hl;
    wram->wJumptableIndex++;
    // gb_write(wJumptableIndex, gb_read(wJumptableIndex) + 1);
    // RET;
}

static void IntroScene1(void){
//  Setup the next scene.
    // CALL(aIntro_ClearBGPals);
    Intro_ClearBGPals_Conv();
    // CALL(aClearSprites);
    // CALL(aClearTilemap);
    ClearSprites();
    ClearTilemap();
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = BGMAPMODE_NONE;
    // LD_A(0x1);
    // LDH_addr_A(rVBK);
    // gb_write(rVBK, 0x1);
    // LD_HL(mIntroUnownAAttrmap);
    // debgcoord(0, 0, vBGMap0);
    // CALL(aIntro_DecompressRequest2bpp_64Tiles);
    // Intro_DecompressRequest2bpp_64Tiles_Conv(mIntroUnownAAttrmap, bgcoord(0, 0, vBGMap0));
    Load2bppBinaryAssetToBuffer(coord(0, 0, vram->vBGMap2), sizeof(vram->vBGMap2), IntroUnownAAttrmap, 0, 64);
    // LD_A(0x0);
    // LDH_addr_A(rVBK);
    // gb_write(rVBK, 0x0);
    // LD_HL(mIntroUnownsGFX);
    // LD_DE(vTiles2 + LEN_2BPP_TILE * 0x00);
    // CALL(aIntro_DecompressRequest2bpp_128Tiles);
    // Intro_DecompressRequest2bpp_128Tiles_Conv(mIntroUnownsGFX, vTiles2 + LEN_2BPP_TILE * 0x00);
    LoadPNG2bppAssetToVRAM(vram->vTiles2, IntroUnownsGFX);
    // LD_HL(mIntroPulseGFX);
    // LD_DE(vTiles0 + LEN_2BPP_TILE * 0x00);
    // CALL(aIntro_DecompressRequest2bpp_128Tiles);
    // Intro_DecompressRequest2bpp_128Tiles_Conv(mIntroPulseGFX, vTiles0 + LEN_2BPP_TILE * 0x00);
    LoadPNG2bppAssetToVRAM(vram->vTiles0, IntroPulseGFX);
    // LD_HL(mIntroUnownATilemap);
    // debgcoord(0, 0, vBGMap0);
    // CALL(aIntro_DecompressRequest2bpp_64Tiles);
    // Intro_DecompressRequest2bpp_64Tiles_Conv(mIntroUnownATilemap, bgcoord(0, 0, vBGMap0));
    Load2bppBinaryAssetToBuffer(coord(0, 0, vram->vBGMap0), sizeof(vram->vBGMap0), IntroUnownATilemap, 0, 64);
    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    // LD_A(MBANK(awBGPals1));
    // LDH_addr_A(rSVBK);

    // LD_HL(mIntroUnownsPalette);
    // LD_DE(wBGPals1);
    // LD_BC(16 * PALETTE_SIZE);
    // CALL(aCopyBytes);
    // CopyBytes_GB(wBGPals1, mIntroUnownsPalette, 16 * PALETTE_SIZE);
    LoadPaletteAssetToBuffer(wram->wBGPals1, sizeof(wram->wBGPals1), IntroUnownsPalette, 16);
    // LD_HL(mIntroUnownsPalette);
    // LD_DE(wBGPals2);
    // LD_BC(16 * PALETTE_SIZE);
    // CALL(aCopyBytes);
    // CopyBytes_GB(wBGPals2, mIntroUnownsPalette, 16 * PALETTE_SIZE);
    LoadPaletteAssetToBuffer(wram->wBGPals2, sizeof(wram->wBGPals2), IntroUnownsPalette, 16);
    // POP_AF;
    // LDH_addr_A(rSVBK);

    // XOR_A_A;
    // LDH_addr_A(hSCX);
    // LDH_addr_A(hSCY);
    hram->hSCX = 0;
    hram->hSCY = 0;
    // LD_A(0x7);
    // LDH_addr_A(hWX);
    hram->hWX = 0x7;
    // LD_A(0x90);
    // LDH_addr_A(hWY);
    hram->hWY = 0x90;
    // FARCALL(aClearSpriteAnims);
    ClearSpriteAnims();
    // CALL(aIntro_SetCGBPalUpdate);
    hram->hCGBPalUpdate = TRUE;
    // XOR_A_A;
    // LD_addr_A(wIntroSceneFrameCounter);
    // LD_addr_A(wIntroSceneTimer);
    wram->wIntroSceneFrameCounter = 0;
    wram->wIntroSceneTimer = 0;
    // CALL(aNextIntroScene);
    NextIntroScene();
    // RET;
}

static void IntroScene2(void){
//  First Unown (A) fades in, pulses, then fades out.
    // LD_HL(wIntroSceneFrameCounter);
    // LD_A_hl;
    // INC_hl;
    uint8_t a = wram->wIntroSceneFrameCounter++;
    // CP_A(0x80);
    // IF_NC {
    if(a >= 0x80) {
        // CALL(aNextIntroScene);
        NextIntroScene();
        // RET;
        return;
    }

    // CP_A(0x60);
    // IF_Z {
    if(a == 0x60) {
        // PUSH_AF;
        //depixel ['11', '11']
        // depixel2(11, 11);
        // CALL(aCrystalIntro_InitUnownAnim);
        CrystalIntro_InitUnownAnim_Conv(pixel2(11, 11));
        // LD_DE(SFX_INTRO_UNOWN_1);
        // CALL(aPlaySFX);
        PlaySFX(SFX_INTRO_UNOWN_1);
        // POP_AF;
    }

    // LD_addr_A(wIntroSceneTimer);
    wram->wIntroSceneTimer = a;
    // XOR_A_A;
    // CALL(aCrystalIntro_UnownFade);
    CrystalIntro_UnownFade_Conv(0);
    // RET;
}

static void IntroScene3(void){
//  More setup. Transition to the outdoor scene.
    // CALL(aIntro_ClearBGPals);
    Intro_ClearBGPals_Conv();
    // CALL(aClearSprites);
    ClearSprites();
    // CALL(aClearTilemap);
    ClearTilemap();
    DelayFrames(TRANSITION_WAIT_FRAMES);
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = BGMAPMODE_NONE;
    // LD_A(0x1);
    // LDH_addr_A(rVBK);
    // gb_write(rVBK, 0x1);
    // LD_HL(mIntroBackgroundAttrmap);
    // debgcoord(0, 0, vBGMap0);
    // CALL(aIntro_DecompressRequest2bpp_64Tiles);
    // Intro_DecompressRequest2bpp_64Tiles_Conv(mIntroBackgroundAttrmap, bgcoord(0, 0, vBGMap0));
    Load2bppBinaryAssetToBuffer(coord(0, 0, vram->vBGMap2), sizeof(vram->vBGMap2), IntroBackgroundAttrmap, 0, 64);
    // LD_A(0x0);
    // LDH_addr_A(rVBK);
    // gb_write(rVBK, 0x0);
    // LD_HL(mIntroBackgroundGFX);
    // LD_DE(vTiles2 + LEN_2BPP_TILE * 0x00);
    // CALL(aIntro_DecompressRequest2bpp_128Tiles);
    // Intro_DecompressRequest2bpp_128Tiles_Conv(mIntroBackgroundGFX, vTiles2 + LEN_2BPP_TILE * 0x00);
    LoadPNG2bppAssetToVRAM(vram->vTiles2, IntroBackgroundGFX);
    // LD_HL(mIntroBackgroundTilemap);
    // debgcoord(0, 0, vBGMap0);
    // CALL(aIntro_DecompressRequest2bpp_64Tiles);
    // Intro_DecompressRequest2bpp_64Tiles_Conv(mIntroBackgroundTilemap, bgcoord(0, 0, vBGMap0));
    Load2bppBinaryAssetToBuffer(coord(0, 0, vram->vBGMap0), sizeof(vram->vBGMap0), IntroBackgroundTilemap, 0, 64);
    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    // LD_A(MBANK(awBGPals1));
    // LDH_addr_A(rSVBK);

    // LD_HL(mIntroBackgroundPalette);
    // LD_DE(wBGPals1);
    // LD_BC(16 * PALETTE_SIZE);
    // CALL(aCopyBytes);
    // CopyBytes_GB(wBGPals1, mIntroBackgroundPalette, 16 * PALETTE_SIZE);
    LoadPaletteAssetToArray(wram->wBGPals1, IntroBackgroundPalette, 16);
    // LD_HL(mIntroBackgroundPalette);
    // LD_DE(wBGPals2);
    // LD_BC(16 * PALETTE_SIZE);
    // CALL(aCopyBytes);
    // CopyBytes_GB(wBGPals2, mIntroBackgroundPalette, 16 * PALETTE_SIZE);
    LoadPaletteAssetToArray(wram->wBGPals2, IntroBackgroundPalette, 16);
    // POP_AF;
    // LDH_addr_A(rSVBK);

    // XOR_A_A;
    // LDH_addr_A(hSCX);
    // LDH_addr_A(hSCY);
    hram->hSCX = 0;
    hram->hSCY = 0;
    // LD_A(0x7);
    // LDH_addr_A(hWX);
    hram->hWX = 0x7;
    // LD_A(0x90);
    // LDH_addr_A(hWY);
    hram->hWY = 0x90;
    // CALL(aIntro_ResetLYOverrides);
    Intro_ResetLYOverrides_Conv();
    // CALL(aIntro_SetCGBPalUpdate);
    hram->hCGBPalUpdate = TRUE;
    // XOR_A_A;
    // LD_addr_A(wIntroSceneFrameCounter);
    wram->wIntroSceneFrameCounter = 0;
    // CALL(aNextIntroScene);
    NextIntroScene();
    // RET;

}

static void IntroScene4(void){
//  Scroll the outdoor panorama for a bit.
    // CALL(aIntro_PerspectiveScrollBG);
    Intro_PerspectiveScrollBG_Conv();
    // LD_HL(wIntroSceneFrameCounter);
    // LD_A_hl;
    // CP_A(0x80);
    // IF_Z goto endscene;
    // INC_hl;
    // RET;
    if(wram->wIntroSceneFrameCounter != 0x80) {
        wram->wIntroSceneFrameCounter++;
        // RET;
        return;
    }

// endscene:
    // CALL(aNextIntroScene);
    NextIntroScene();
    return;
    // RET;

}

static void IntroScene5(void){
//  Go back to the Unown.
    // CALL(aIntro_ClearBGPals);
    Intro_ClearBGPals_Conv();
    // CALL(aClearSprites);
    ClearSprites();
    // CALL(aClearTilemap);
    ClearTilemap();
    DelayFrames(TRANSITION_WAIT_FRAMES);
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    // LDH_addr_A(hLCDCPointer);
    hram->hBGMapMode = BGMAPMODE_NONE;
    hram->hLCDCPointer = 0;
    // LD_A(0x1);
    // LDH_addr_A(rVBK);
    // gb_write(rVBK, 0x1);
    // LD_HL(mIntroUnownHIAttrmap);
    // debgcoord(0, 0, vBGMap0);
    // CALL(aIntro_DecompressRequest2bpp_64Tiles);
    // Intro_DecompressRequest2bpp_64Tiles_Conv(mIntroUnownHIAttrmap, bgcoord(0, 0, vBGMap0));
    Load2bppBinaryAssetToBuffer(coord(0, 0, vram->vBGMap2), sizeof(vram->vBGMap2), IntroUnownHIAttrmap, 0, 64);
    // LD_A(0x0);
    // LDH_addr_A(rVBK);
    // gb_write(rVBK, 0x0);
    // LD_HL(mIntroUnownsGFX);
    // LD_DE(vTiles2 + LEN_2BPP_TILE * 0x00);
    // CALL(aIntro_DecompressRequest2bpp_128Tiles);
    // Intro_DecompressRequest2bpp_128Tiles_Conv(mIntroUnownsGFX, vTiles2 + LEN_2BPP_TILE * 0x00);
    LoadPNG2bppAssetToVRAM(vram->vTiles2, IntroUnownsGFX);
    // LD_HL(mIntroPulseGFX);
    // LD_DE(vTiles0 + LEN_2BPP_TILE * 0x00);
    // CALL(aIntro_DecompressRequest2bpp_128Tiles);
    // Intro_DecompressRequest2bpp_128Tiles_Conv(mIntroPulseGFX, vTiles0 + LEN_2BPP_TILE * 0x00);
    LoadPNG2bppAssetToVRAM(vram->vTiles0, IntroPulseGFX);
    // LD_HL(mIntroUnownHITilemap);
    // debgcoord(0, 0, vBGMap0);
    // CALL(aIntro_DecompressRequest2bpp_64Tiles);
    // Intro_DecompressRequest2bpp_64Tiles_Conv(mIntroUnownHITilemap, bgcoord(0, 0, vBGMap0));
    Load2bppBinaryAssetToBuffer(coord(0, 0, vram->vBGMap0), sizeof(vram->vBGMap0), IntroUnownHITilemap, 0, 64);
    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    // LD_A(MBANK(awBGPals1));
    // LDH_addr_A(rSVBK);
    // wbank_push(MBANK(awBGPals1));
    // LD_HL(mIntroUnownsPalette);
    // LD_DE(wBGPals1);
    // LD_BC(16 * PALETTE_SIZE);
    // CALL(aCopyBytes);
    // CopyBytes_GB(wBGPals1, mIntroUnownsPalette, 16 * PALETTE_SIZE);
    LoadPaletteAssetToArray(wram->wBGPals1, IntroUnownsPalette, 16);
    // LD_HL(mIntroUnownsPalette);
    // LD_DE(wBGPals2);
    // LD_BC(16 * PALETTE_SIZE);
    // CALL(aCopyBytes);
    // CopyBytes_GB(wBGPals2, mIntroUnownsPalette, 16 * PALETTE_SIZE);
    LoadPaletteAssetToArray(wram->wBGPals2, IntroUnownsPalette, 16);
    // POP_AF;
    // LDH_addr_A(rSVBK);
    // wbank_pop;
    // XOR_A_A;
    // LDH_addr_A(hSCX);
    // LDH_addr_A(hSCY);
    hram->hSCX = 0;
    hram->hSCY = 0;
    // LD_A(0x7);
    // LDH_addr_A(hWX);
    hram->hWX = 0x7;
    // LD_A(0x90);
    // LDH_addr_A(hWY);
    hram->hWY = 0x90;
    // FARCALL(aClearSpriteAnims);
    ClearSpriteAnims();
    // CALL(aIntro_SetCGBPalUpdate);
    hram->hCGBPalUpdate = TRUE;
    // XOR_A_A;
    // LD_addr_A(wIntroSceneFrameCounter);
    // LD_addr_A(wIntroSceneTimer);
    wram->wIntroSceneFrameCounter = 0;
    wram->wIntroSceneTimer = 0;
    // CALL(aNextIntroScene);
    NextIntroScene();
    // RET;
    // return;

}

static void IntroScene6(void){
//  Two more Unown (I, H) fade in.
    // LD_HL(wIntroSceneFrameCounter);
    // LD_A_hl;
    // INC_hl;
    uint8_t ctr = wram->wIntroSceneFrameCounter++;
    // CP_A(0x80);
    // IF_NC goto endscene;
    if(ctr >= 0x80) {
    // endscene:
    //     CALL(aNextIntroScene);
    //     RET;
        NextIntroScene();
        return;
    }
    // CP_A(0x60);
    // IF_Z goto SecondUnown;
    if(ctr == 0x60) {
        // PUSH_AF;
        // //depixel ['14', '6']
        // depixel2(14, 6);
        // CALL(aCrystalIntro_InitUnownAnim);
        CrystalIntro_InitUnownAnim_Conv(pixel2(14, 6));
        // LD_DE(SFX_INTRO_UNOWN_1);
        // CALL(aPlaySFX);
        PlaySFX(SFX_INTRO_UNOWN_1);
        // POP_AF;
    }
    // CP_A(0x40);
    // IF_NC goto StopUnown;
    if(ctr >= 0x40) {
        // LD_addr_A(wIntroSceneTimer);
        wram->wIntroSceneTimer = ctr;
        // LD_A(0x1);
        // CALL(aCrystalIntro_UnownFade);
        CrystalIntro_UnownFade_Conv(0x1);
        // RET;
        return;
    }
    // CP_A(0x20);
    // IF_Z goto FirstUnown;
    if(ctr == 0x20) {
        // PUSH_AF;
        //depixel ['7', '15']
        // depixel2(7, 15);
        // CALL(aCrystalIntro_InitUnownAnim);
        CrystalIntro_InitUnownAnim_Conv(pixel2(7, 15));
        // LD_DE(SFX_INTRO_UNOWN_2);
        // CALL(aPlaySFX);
        PlaySFX(SFX_INTRO_UNOWN_2);
        // POP_AF;
    }

    // LD_addr_A(wIntroSceneTimer);
    wram->wIntroSceneTimer = ctr;
    // XOR_A_A;
    // CALL(aCrystalIntro_UnownFade);
    CrystalIntro_UnownFade_Conv(0);
    // RET;
}

static void IntroScene7(void){
//  Back to the outdoor scene.
    // CALL(aIntro_ClearBGPals);
    Intro_ClearBGPals_Conv();
    // CALL(aClearSprites);
    ClearSprites();
    // CALL(aClearTilemap);
    ClearTilemap();
    DelayFrames(TRANSITION_WAIT_FRAMES);
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = BGMAPMODE_NONE;

    // LD_A(0x1);
    // LDH_addr_A(rVBK);
    // gb_write(rVBK, 0x1);
    // LD_HL(mIntroBackgroundAttrmap);
    // debgcoord(0, 0, vBGMap0);
    // CALL(aIntro_DecompressRequest2bpp_64Tiles);
    // Intro_DecompressRequest2bpp_64Tiles_Conv(mIntroBackgroundAttrmap, bgcoord(0, 0, vBGMap0));
    Load2bppBinaryAssetToBuffer(coord(0, 0, vram->vBGMap2), sizeof(vram->vBGMap2), IntroBackgroundAttrmap, 0, 64);

    // LD_HL(mIntroPichuWooperGFX);
    // LD_DE(vTiles0 + LEN_2BPP_TILE * 0x00);
    // CALL(aIntro_DecompressRequest2bpp_128Tiles);
    // Intro_DecompressRequest2bpp_128Tiles_Conv(mIntroPichuWooperGFX, vTiles0 + LEN_2BPP_TILE * 0x00);
    LoadPNG2bppAssetToVRAM(vram->vTiles3, IntroPichuWooperGFX);

    // LD_A(0x0);
    // LDH_addr_A(rVBK);
    // gb_write(rVBK, 0x0);
    // LD_HL(mIntroSuicuneRunGFX);
    // LD_DE(vTiles0 + LEN_2BPP_TILE * 0x00);
    // CALL(aIntro_DecompressRequest2bpp_255Tiles);
    // Intro_DecompressRequest2bpp_255Tiles_Conv(mIntroSuicuneRunGFX, vTiles0 + LEN_2BPP_TILE * 0x00);
    LoadPNG2bppAssetToVRAM(vram->vTiles0, IntroSuicuneRunGFX);

    // LD_HL(mIntroBackgroundGFX);
    // LD_DE(vTiles2 + LEN_2BPP_TILE * 0x00);
    // CALL(aIntro_DecompressRequest2bpp_128Tiles);
    // Intro_DecompressRequest2bpp_128Tiles_Conv(mIntroBackgroundGFX, vTiles2 + LEN_2BPP_TILE * 0x00);
    LoadPNG2bppAssetToVRAM(vram->vTiles2, IntroBackgroundGFX);

    // LD_HL(mIntroBackgroundTilemap);
    // debgcoord(0, 0, vBGMap0);
    // CALL(aIntro_DecompressRequest2bpp_64Tiles);
    // Intro_DecompressRequest2bpp_64Tiles_Conv(mIntroBackgroundTilemap, bgcoord(0, 0, vBGMap0));
    Load2bppBinaryAssetToBuffer(coord(0, 0, vram->vBGMap0), sizeof(vram->vBGMap0), IntroBackgroundTilemap, 0, 64);

    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    // LD_A(MBANK(awBGPals1));
    // LDH_addr_A(rSVBK);
    // wbank_push(MBANK(awBGPals1));

    // LD_HL(mIntroBackgroundPalette);
    // LD_DE(wBGPals1);
    // LD_BC(16 * PALETTE_SIZE);
    // CALL(aCopyBytes);
    // CopyBytes_GB(wBGPals1, mIntroBackgroundPalette, 16 * PALETTE_SIZE);
    LoadPaletteAssetToArray(wram->wBGPals1, IntroBackgroundPalette, 16);

    // LD_HL(mIntroBackgroundPalette);
    // LD_DE(wBGPals2);
    // LD_BC(16 * PALETTE_SIZE);
    // CALL(aCopyBytes);
    // CopyBytes_GB(wBGPals2, mIntroBackgroundPalette, 16 * PALETTE_SIZE);
    LoadPaletteAssetToArray(wram->wBGPals2, IntroBackgroundPalette, 16);

    // POP_AF;
    // LDH_addr_A(rSVBK);
    // wbank_pop;

    // XOR_A_A;
    // LDH_addr_A(hSCX);
    // LDH_addr_A(hSCY);
    hram->hSCX = 0;
    hram->hSCY = 0;
    // LD_A(0x7);
    // LDH_addr_A(hWX);
    hram->hWX = 0x7;
    // LD_A(0x90);
    // LDH_addr_A(hWY);
    hram->hWY = 0x90;
    // CALL(aIntro_ResetLYOverrides);
    Intro_ResetLYOverrides_Conv();
    // FARCALL(aClearSpriteAnims);
    ClearSpriteAnims();
    //depixel ['13', '27', '4', '0']
    // depixel4(13, 27, 4, 0);
    // LD_A(SPRITE_ANIM_INDEX_INTRO_SUICUNE);
    // CALL(aInitSpriteAnimStruct);
    InitSpriteAnimStruct(SPRITE_ANIM_INDEX_INTRO_SUICUNE, pixel4(13, 27, 4, 0));
    // LD_A(0xf0);
    // LD_addr_A(wGlobalAnimXOffset);
    wram->wGlobalAnimXOffset = 0xf0;
    // CALL(aIntro_SetCGBPalUpdate);
    hram->hCGBPalUpdate = TRUE;
    // XOR_A_A;
    // LD_addr_A(wIntroSceneFrameCounter);
    // LD_addr_A(wIntroSceneTimer);
    wram->wIntroSceneFrameCounter = 0;
    wram->wIntroSceneTimer = 0;
    // CALL(aNextIntroScene);
    NextIntroScene();
    // return;

}

static void IntroScene8(void){
//  Scroll the scene, then show Suicune running across the screen.
    // LD_HL(wIntroSceneFrameCounter);
    // LD_A_hl;
    // INC_hl;
    uint8_t ctr = wram->wIntroSceneFrameCounter++;
    // CP_A(0x40);
    // IF_Z goto suicune_sound;
    if(ctr == 0x40) {
    // suicune_sound:
        // LD_DE(SFX_INTRO_SUICUNE_3);
        // CALL(aPlaySFX);
        PlaySFX(SFX_INTRO_SUICUNE_3);
    }
    // IF_NC goto animate_suicune;
    if(ctr >= 0x40) {
    // animate_suicune:
        // LD_A_addr(wGlobalAnimXOffset);
        // AND_A_A;
        // IF_Z goto finish;
        if(wram->wGlobalAnimXOffset == 0) {
        // finish:
            // LD_DE(SFX_INTRO_SUICUNE_2);
            // CALL(aPlaySFX);
            PlaySFX(SFX_INTRO_SUICUNE_2);
            // FARCALL(aDeinitializeAllSprites);
            DeinitializeAllSprites();
            // CALL(aNextIntroScene);
            // RET;
            NextIntroScene();
            return;
        }
        // SUB_A(0x8);
        // LD_addr_A(wGlobalAnimXOffset);
        wram->wGlobalAnimXOffset -= 8;
        return;
        // RET;
    }

    // CALL(aIntro_PerspectiveScrollBG);
    Intro_PerspectiveScrollBG_Conv();
    // return;
    // RET;

}

static void IntroScene9(void){
//  Set up the next scene (same bg).
    // XOR_A_A;
    // LDH_addr_A(hLCDCPointer);
    hram->hLCDCPointer = 0;
    // CALL(aClearSprites);
    ClearSprites();
    // hlcoord(0, 0, wAttrmap);
// first 12 rows have palette 1
    // LD_BC(12 * SCREEN_WIDTH);
    // LD_A(0x1);
    // CALL(aByteFill);
    ByteFill(coord(0, 0, wram->wAttrmap), 12 * SCREEN_WIDTH, 0x1);
// middle 3 rows have palette 2
    // LD_BC(3 * SCREEN_WIDTH);
    // LD_A(0x2);
    // CALL(aByteFill);
    ByteFill(coord(0, 12, wram->wAttrmap), 3 * SCREEN_WIDTH, 0x2);
// last three rows have palette 3
    // LD_BC(3 * SCREEN_WIDTH);
    // LD_A(0x3);
    // CALL(aByteFill);
    ByteFill(coord(0, 15, wram->wAttrmap), 3 * SCREEN_WIDTH, 0x3);
    // LD_A(0x2);
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = BGMAPMODE_UPDATE_ATTRS;
    // CALL(aDelayFrame);
    // CALL(aDelayFrame);
    // CALL(aDelayFrame);
    DelayFrames(3);
    // LD_A(LOW(vBGMap0 + 0xc));  // $c
    // LDH_addr_A(hBGMapAddress);
    hram->hBGMapAddress = vBGMap0 + 0xc;
    // CALL(aDelayFrame);
    // CALL(aDelayFrame);
    // CALL(aDelayFrame);
    DelayFrames(3);
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    // LDH_addr_A(hBGMapAddress);
    hram->hBGMapMode = BGMAPMODE_NONE;
    hram->hBGMapAddress = vBGMap0 + 0x0;
    // LD_addr_A(wGlobalAnimXOffset);
    wram->wGlobalAnimXOffset = 0;
    // XOR_A_A;
    // LD_addr_A(wIntroSceneFrameCounter);
    wram->wIntroSceneFrameCounter = 0;
    // CALL(aNextIntroScene);
    NextIntroScene();
    // RET;
    // return;
}

static void IntroScene10(void){
//  Wooper and Pichu enter.
    // CALL(aIntro_RustleGrass);
    Intro_RustleGrass_Conv();
    // LD_HL(wIntroSceneFrameCounter);
    // LD_A_hl;
    // INC_hl;
    uint8_t ctr = wram->wIntroSceneFrameCounter++;
    // CP_A(0xc0);
    // IF_Z goto done;
    if(ctr == 0xc0) {
    // done:
        // CALL(aNextIntroScene);
        NextIntroScene();
        // RET;
        return;
    }
    // CP_A(0x20);
    // IF_Z goto wooper;
    if(ctr == 0x20) {
    // wooper:
        // depixel2(22, 6);
        // LD_A(SPRITE_ANIM_INDEX_INTRO_WOOPER);
        // CALL(aInitSpriteAnimStruct);
        InitSpriteAnimStruct(SPRITE_ANIM_INDEX_INTRO_WOOPER, pixel2(22, 6));
        // LD_DE(SFX_INTRO_PICHU);
        // CALL(aPlaySFX);
        PlaySFX(SFX_INTRO_PICHU);
        // RET;
        return;
    }
    // CP_A(0x40);
    // IF_Z goto pichu;
    if(ctr == 0x40) {
    // pichu:
        // depixel4(21, 16, 1, 0);
        // LD_A(SPRITE_ANIM_INDEX_INTRO_PICHU);
        // CALL(aInitSpriteAnimStruct);
        InitSpriteAnimStruct(SPRITE_ANIM_INDEX_INTRO_PICHU, pixel4(21, 16, 1, 0));
        // LD_DE(SFX_INTRO_PICHU);
        // CALL(aPlaySFX);
        PlaySFX(SFX_INTRO_PICHU);
        // RET;
        return;
    }
    // RET;
}

static void IntroScene11(void){
//  Back to Unown again.
    // CALL(aIntro_ClearBGPals);
    Intro_ClearBGPals_Conv();
    // CALL(aClearSprites);
    ClearSprites();
    // CALL(aClearTilemap);
    ClearTilemap();
    DelayFrames(TRANSITION_WAIT_FRAMES);
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    // LDH_addr_A(hLCDCPointer);
    hram->hBGMapMode = BGMAPMODE_NONE;
    hram->hLCDCPointer = 0;
    // LD_A(0x1);
    // LDH_addr_A(rVBK);
    // gb_write(rVBK, 0x1);
    // LD_HL(mIntroUnownsAttrmap);
    // debgcoord(0, 0, vBGMap0);
    // CALL(aIntro_DecompressRequest2bpp_64Tiles);
    // Intro_DecompressRequest2bpp_64Tiles_Conv(mIntroUnownsAttrmap, bgcoord(0, 0, vBGMap0));
    Load2bppBinaryAssetToBuffer(coord(0, 0, vram->vBGMap2), sizeof(vram->vBGMap2), IntroUnownsAttrmap, 0, 64);
    // LD_A(0x0);
    // LDH_addr_A(rVBK);
    // gb_write(rVBK, 0x0);
    // LD_HL(mIntroUnownsGFX);
    // LD_DE(vTiles2 + LEN_2BPP_TILE * 0x00);
    // CALL(aIntro_DecompressRequest2bpp_128Tiles);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles2 + LEN_2BPP_TILE * 0x00, IntroUnownsGFX, 0, 128);
    // LD_HL(mIntroUnownsTilemap);
    // debgcoord(0, 0, vBGMap0);
    // CALL(aIntro_DecompressRequest2bpp_64Tiles);
    // Intro_DecompressRequest2bpp_64Tiles_Conv(mIntroUnownsTilemap, bgcoord(0, 0, vBGMap0));
    Load2bppBinaryAssetToBuffer(coord(0, 0, vram->vBGMap0), sizeof(vram->vBGMap0), IntroUnownsTilemap, 0, 64);
    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    // LD_A(MBANK(awBGPals1));
    // LDH_addr_A(rSVBK);
    // wbank_push(MBANK(awBGPals1));
    // LD_HL(mIntroUnownsPalette);
    // LD_DE(wBGPals1);
    // LD_BC(16 * PALETTE_SIZE);
    // CALL(aCopyBytes);
    // CopyBytes_GB(wBGPals1, mIntroUnownsPalette, 16 * PALETTE_SIZE);
    LoadPaletteAssetToArray(wram->wBGPals1, IntroUnownsPalette, 16);
    // LD_HL(mIntroUnownsPalette);
    // LD_DE(wBGPals2);
    // LD_BC(16 * PALETTE_SIZE);
    // CALL(aCopyBytes);
    // CopyBytes_GB(wBGPals2, mIntroUnownsPalette, 16 * PALETTE_SIZE);
    LoadPaletteAssetToArray(wram->wBGPals2, IntroUnownsPalette, 16);
    // POP_AF;
    // LDH_addr_A(rSVBK);
    // wbank_pop;
    // XOR_A_A;
    // LDH_addr_A(hSCX);
    // LDH_addr_A(hSCY);
    hram->hSCX = 0;
    hram->hSCY = 0;
    // LD_A(0x7);
    // LDH_addr_A(hWX);
    hram->hWX = 0x7;
    // LD_A(0x90);
    // LDH_addr_A(hWY);
    hram->hWY = 0x90;
    // FARCALL(aClearSpriteAnims);
    ClearSpriteAnims();
    // CALL(aIntro_SetCGBPalUpdate);
    hram->hCGBPalUpdate = TRUE;
    // XOR_A_A;
    // LD_addr_A(wIntroSceneFrameCounter);
    wram->wIntroSceneFrameCounter = 0;
    // LD_addr_A(wIntroSceneTimer);
    wram->wIntroSceneTimer = 0;
    // CALL(aNextIntroScene);
    NextIntroScene();
    // RET;
    // return;

}

static void IntroScene12_PlayUnownSound(void) {
// UnownSounds:
    //dbw ['0x00', 'SFX_INTRO_UNOWN_3']
    //dbw ['0x20', 'SFX_INTRO_UNOWN_2']
    //dbw ['0x40', 'SFX_INTRO_UNOWN_1']
    //dbw ['0x60', 'SFX_INTRO_UNOWN_2']
    //dbw ['0x80', 'SFX_INTRO_UNOWN_3']
    //dbw ['0x90', 'SFX_INTRO_UNOWN_2']
    //dbw ['0xa0', 'SFX_INTRO_UNOWN_1']
    //dbw ['0xb0', 'SFX_INTRO_UNOWN_2']
    //db ['-1'];
    static const struct ByteWord UnownSounds[] = {
        {0x00, SFX_INTRO_UNOWN_3},
        {0x20, SFX_INTRO_UNOWN_2},
        {0x40, SFX_INTRO_UNOWN_1},
        {0x60, SFX_INTRO_UNOWN_2},
        {0x80, SFX_INTRO_UNOWN_3},
        {0x90, SFX_INTRO_UNOWN_2},
        {0xa0, SFX_INTRO_UNOWN_1},
        {0xb0, SFX_INTRO_UNOWN_2},
        {0xff, 0xffff}
    };
    // LD_A_addr(wIntroSceneFrameCounter);
    uint8_t a = wram->wIntroSceneFrameCounter;
    // LD_C_A;
    // LD_HL(mIntroScene12_UnownSounds);

    for(uint16_t i = 0; UnownSounds[i].byte != 0xff; i++) {
        // LD_A_hli;
        // CP_A(-1);
        // RET_Z ;
        // CP_A_C;
        // IF_Z goto playsound;
        if(UnownSounds[i].byte == a) {
        // playsound:
            // LD_A_hli;
            // LD_D_hl;
            // LD_E_A;
            // PUSH_DE;
            uint16_t sound = UnownSounds[i].word;
            CALL(aSFXChannelsOff);
            // SFXChannelsOff();
            // POP_DE;
            // CALL(aPlaySFX);
            PlaySFX(sound);
            // RET;
            return;
        }
        // INC_HL;
        // INC_HL;
        // goto loop;
    }
}

static void IntroScene12(void){
//  Even more Unown.
    // CALL(aIntroScene12_PlayUnownSound);
    IntroScene12_PlayUnownSound();
    // LD_HL(wIntroSceneFrameCounter);
    // LD_A_hl;
    // INC_hl;
    uint8_t ctr = wram->wIntroSceneFrameCounter++;
    // CP_A(0xc0);
    // IF_NC goto done;
    if(ctr >= 0xc0) {
    // done:
        // CALL(aNextIntroScene);
        NextIntroScene();
        // RET;
        return;
    }
    // CP_A(0x80);
    // IF_NC goto second_half;
    if(ctr >= 0x80) {
    // second_half:
    //  double speed
        // LD_C_A;
        // AND_A(0xf);
        // SLA_A;
        // SLA_A;
        // LD_addr_A(wIntroSceneTimer);
        wram->wIntroSceneTimer = (ctr & 0xf) << 2;
        // LD_A_C;
        // AND_A(0x70);
        // OR_A(0x40);
        uint8_t a = (ctr & 0x70) | 0x40;
        // SWAP_A;
        a = (a << 4) | (a >> 4);
        // CALL(aCrystalIntro_UnownFade);
        CrystalIntro_UnownFade_Conv(a);
        // RET;
        return;
    }
    else {
    //  first half
        // LD_C_A;
        // AND_A(0x1f);
        // SLA_A;
        // LD_addr_A(wIntroSceneTimer);
        wram->wIntroSceneTimer = (ctr & 0x1f) << 1;
        // LD_A_C;
        // AND_A(0xe0);
        // SRL_A;
        uint8_t a = (ctr & 0xe0) >> 1;
        // SWAP_A;
        a = (a << 4) | (a >> 4);
        // CALL(aCrystalIntro_UnownFade);
        CrystalIntro_UnownFade_Conv(a);
        // RET;
        return;
    }
}

static void IntroScene13(void){
//  Switch scenes again.
    // CALL(aIntro_ClearBGPals);
    Intro_ClearBGPals_Conv();
    // CALL(aClearSprites);
    ClearSprites();
    // CALL(aClearTilemap);
    ClearTilemap();
    DelayFrames(TRANSITION_WAIT_FRAMES);
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = BGMAPMODE_NONE;
    // LD_A(0x1);
    // LDH_addr_A(rVBK);
    // gb_write(rVBK, 0x1);
    // LD_HL(mIntroBackgroundAttrmap);
    // debgcoord(0, 0, vBGMap0);
    // CALL(aIntro_DecompressRequest2bpp_64Tiles);
    // Intro_DecompressRequest2bpp_64Tiles_Conv(mIntroBackgroundAttrmap, bgcoord(0, 0, vBGMap0));
    Load2bppBinaryAssetToBuffer(coord(0, 0, vram->vBGMap2), sizeof(vram->vBGMap2), IntroBackgroundAttrmap, 0, 64);
    // LD_A(0x0);
    // LDH_addr_A(rVBK);
    // gb_write(rVBK, 0x0);
    // LD_HL(mIntroSuicuneRunGFX);
    // LD_DE(vTiles0 + LEN_2BPP_TILE * 0x00);
    // CALL(aIntro_DecompressRequest2bpp_255Tiles);
    // Intro_DecompressRequest2bpp_255Tiles_Conv(mIntroSuicuneRunGFX, vTiles0 + LEN_2BPP_TILE * 0x00);
    LoadPNG2bppAssetToVRAM(vram->vTiles0, IntroSuicuneRunGFX);
    // LD_HL(mIntroBackgroundGFX);
    // LD_DE(vTiles2 + LEN_2BPP_TILE * 0x00);
    // CALL(aIntro_DecompressRequest2bpp_128Tiles);
    // Intro_DecompressRequest2bpp_128Tiles_Conv(mIntroBackgroundGFX, vTiles2 + LEN_2BPP_TILE * 0x00);
    LoadPNG2bppAssetToVRAM(vram->vTiles2, IntroBackgroundGFX);
    // LD_HL(mIntroBackgroundTilemap);
    // debgcoord(0, 0, vBGMap0);
    // CALL(aIntro_DecompressRequest2bpp_64Tiles);
    // Intro_DecompressRequest2bpp_64Tiles_Conv(mIntroBackgroundTilemap, bgcoord(0, 0, vBGMap0));
    Load2bppBinaryAssetToBuffer(coord(0, 0, vram->vBGMap0), sizeof(vram->vBGMap0), IntroBackgroundTilemap, 0, 64);
    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    // LD_A(MBANK(awBGPals1));
    // LDH_addr_A(rSVBK);
    // LD_HL(mIntroBackgroundPalette);
    // LD_DE(wBGPals1);
    // LD_BC(16 * PALETTE_SIZE);
    // CALL(aCopyBytes);
    // CopyBytes_GB(wBGPals1, mIntroBackgroundPalette, 16 * PALETTE_SIZE);
    LoadPaletteAssetToArray(wram->wBGPals1, IntroBackgroundPalette, 16);
    // LD_HL(mIntroBackgroundPalette);
    // LD_DE(wBGPals2);
    // LD_BC(16 * PALETTE_SIZE);
    // CALL(aCopyBytes);
    // CopyBytes_GB(wBGPals2, mIntroBackgroundPalette, 16 * PALETTE_SIZE);
    LoadPaletteAssetToArray(wram->wBGPals2, IntroBackgroundPalette, 16);
    // POP_AF;
    // LDH_addr_A(rSVBK);
    // XOR_A_A;
    // LDH_addr_A(hSCX);
    // LDH_addr_A(hSCY);
    hram->hSCX = 0;
    hram->hSCY = 0;
    // LD_A(0x7);
    // LDH_addr_A(hWX);
    hram->hWX = 0x7;
    // LD_A(0x90);
    // LDH_addr_A(hWY);
    hram->hWY = 0x90;
    // FARCALL(aClearSpriteAnims);
    ClearSpriteAnims();
    // depixel4(13, 11, 4, 0);
    // LD_A(SPRITE_ANIM_INDEX_INTRO_SUICUNE);
    // CALL(aInitSpriteAnimStruct);
    InitSpriteAnimStruct(SPRITE_ANIM_INDEX_INTRO_SUICUNE, pixel4(13, 11, 4, 0));
    // LD_DE(MUSIC_CRYSTAL_OPENING);
    // CALL(aPlayMusic);
    PlayMusic(MUSIC_CRYSTAL_OPENING);
    // XOR_A_A;
    // LD_addr_A(wGlobalAnimXOffset);
    wram->wGlobalAnimXOffset = 0;
    // CALL(aIntro_SetCGBPalUpdate);
    hram->hCGBPalUpdate = TRUE;
    // XOR_A_A;
    // LD_addr_A(wIntroSceneFrameCounter);
    // LD_addr_A(wIntroSceneTimer);
    wram->wIntroSceneFrameCounter = 0;
    wram->wIntroSceneTimer = 0;
    // CALL(aNextIntroScene);
    NextIntroScene();
    // RET;
}

static void IntroScene14(void){
//  Suicune runs then jumps.
    // LDH_A_addr(hSCX);
    // SUB_A(10);
    // LDH_addr_A(hSCX);
    hram->hSCX -= 10;
    // LD_HL(wIntroSceneFrameCounter);
    // LD_A_hl;
    // INC_hl;
    uint8_t ctr = wram->wIntroSceneFrameCounter++;
    // CP_A(0x80);
    // IF_Z goto done;
    if(ctr == 0x80) {
    // done:
        // CALL(aNextIntroScene);
        NextIntroScene();
        // RET;
        return;
    }
    // CP_A(0x60);
    // IF_Z goto jump;
    if(ctr == 0x60) {
    // jump:
        // LD_DE(SFX_INTRO_SUICUNE_4);
        // CALL(aPlaySFX);
        PlaySFX(SFX_INTRO_SUICUNE_4);
    }
    // IF_NC goto run_after_jump;
    if(ctr >= 0x60) {
    // run_after_jump:
        // LD_A(0x1);
        // LD_addr_A(wIntroSceneTimer);
        wram->wIntroSceneTimer = 0x1;
        // LD_A_addr(wGlobalAnimXOffset);
        // CP_A(0x88);
        // IF_C goto disappear;
        if(wram->wGlobalAnimXOffset < 0x88) {
        // disappear:
            // FARCALL(aDeinitializeAllSprites);
            DeinitializeAllSprites();
            // RET;
            return;
        }
        // SUB_A(0x8);
        // LD_addr_A(wGlobalAnimXOffset);
        wram->wGlobalAnimXOffset -= 8;
        // RET;
        return;
    }
    // CP_A(0x40);
    // IF_NC goto run;
    if(ctr >= 0x40) {
    // run:
        // LD_A_addr(wGlobalAnimXOffset);
        // SUB_A(0x2);
        // LD_addr_A(wGlobalAnimXOffset);
        wram->wGlobalAnimXOffset -= 2;
        // RET;
        return;
    }
    // RET;
    return;
}

static void IntroScene15(void){
//  Transition to a new scene.
    // CALL(aIntro_ClearBGPals);
    Intro_ClearBGPals_Conv();
    // CALL(aClearSprites);
    ClearSprites();
    // CALL(aClearTilemap);
    ClearTilemap();
    DelayFrames(TRANSITION_WAIT_FRAMES);
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = BGMAPMODE_NONE;
    // LD_A(0x1);
    // LDH_addr_A(rVBK);
    // gb_write(rVBK, 0x1);
    // LD_HL(mIntroSuicuneJumpAttrmap);
    // debgcoord(0, 0, vBGMap0);
    // CALL(aIntro_DecompressRequest2bpp_64Tiles);
    // Intro_DecompressRequest2bpp_64Tiles_Conv(mIntroSuicuneJumpAttrmap, bgcoord(0, 0, vBGMap0));
    Load2bppBinaryAssetToBuffer(coord(0, 0, vram->vBGMap2), sizeof(vram->vBGMap2), IntroSuicuneJumpAttrmap, 0, 64);
    // LD_A(0x0);
    // LDH_addr_A(rVBK);
    // gb_write(rVBK, 0x0);
    // LD_HL(mIntroSuicuneJumpGFX);
    // LD_DE(vTiles2 + LEN_2BPP_TILE * 0x00);
    // CALL(aIntro_DecompressRequest2bpp_128Tiles);
    // Intro_DecompressRequest2bpp_128Tiles_Conv(mIntroSuicuneJumpGFX, vTiles2 + LEN_2BPP_TILE * 0x00);
    LoadPNG2bppAssetToVRAM(vram->vTiles2, IntroSuicuneJumpGFX);
    // LD_HL(mIntroUnownBackGFX);
    // LD_DE(vTiles0 + LEN_2BPP_TILE * 0x00);
    // CALL(aIntro_DecompressRequest2bpp_128Tiles);
    // Intro_DecompressRequest2bpp_128Tiles_Conv(mIntroUnownBackGFX, vTiles0 + LEN_2BPP_TILE * 0x00);
    LoadPNG2bppAssetToVRAM(vram->vTiles0, IntroUnownBackGFX);
    // LD_DE(mIntroGrass4GFX);
    // LD_HL(vTiles1 + LEN_2BPP_TILE * 0x00);
    // LD_BC((BANK(aIntroGrass4GFX) << 8) | 1);
    // CALL(aRequest2bpp);
    // Request2bpp_Conv(BANK(aIntroGrass4GFX), mIntroGrass4GFX, vTiles1 + LEN_2BPP_TILE * 0x00, 1);
    CopyBytes(vram->vTiles1 + LEN_2BPP_TILE * 0x00, IntroGrass4GFX, LEN_2BPP_TILE);
    // LD_HL(mIntroSuicuneJumpTilemap);
    // debgcoord(0, 0, vBGMap0);
    // CALL(aIntro_DecompressRequest2bpp_64Tiles);
    // Intro_DecompressRequest2bpp_64Tiles_Conv(mIntroSuicuneJumpTilemap, bgcoord(0, 0, vBGMap0));
    // CALL(aIntro_LoadTilemap);
    Intro_LoadTilemap_Conv(Load2bppBinaryAssetToBuffer(coord(0, 0, vram->vBGMap0), sizeof(vram->vBGMap0), IntroSuicuneJumpTilemap, 0, 64));
    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    // LD_A(MBANK(awBGPals1));
    // LDH_addr_A(rSVBK);
    // wbank_push(MBANK(awBGPals1));
    // LD_HL(mIntroSuicunePalette);
    // LD_DE(wBGPals1);
    // LD_BC(16 * PALETTE_SIZE);
    // CALL(aCopyBytes);
    // CopyBytes_GB(wBGPals1, mIntroSuicunePalette, 16 * PALETTE_SIZE);
    LoadPaletteAssetToArray(wram->wBGPals1, IntroSuicunePalette, 16);
    // LD_HL(mIntroSuicunePalette);
    // LD_DE(wBGPals2);
    // LD_BC(16 * PALETTE_SIZE);
    // CALL(aCopyBytes);
    // CopyBytes_GB(wBGPals2, mIntroSuicunePalette, 16 * PALETTE_SIZE);
    LoadPaletteAssetToArray(wram->wBGPals2, IntroSuicunePalette, 16);
    // POP_AF;
    // LDH_addr_A(rSVBK);
    // wbank_pop;
    // XOR_A_A;
    // LDH_addr_A(hSCX);
    hram->hSCX = 0;
    // LD_A(0x90);
    // LDH_addr_A(hSCY);
    hram->hSCY = 0x90;
    // LD_A(0x7);
    // LDH_addr_A(hWX);
    hram->hWX = 0x7;
    // LD_A(0x90);
    // LDH_addr_A(hWY);
    hram->hWY = 0x90;
    // FARCALL(aClearSpriteAnims);
    ClearSpriteAnims();
    // CALL(aIntro_SetCGBPalUpdate);
    hram->hCGBPalUpdate = TRUE;
    //depixel ['8', '5']
    // depixel2(8, 5);
    // LD_A(SPRITE_ANIM_INDEX_INTRO_UNOWN_F);
    // CALL(aInitSpriteAnimStruct);
    InitSpriteAnimStruct(SPRITE_ANIM_INDEX_INTRO_UNOWN_F, pixel2(8, 5));
    //depixel ['12', '0']
    // depixel2(12, 0);
    // LD_A(SPRITE_ANIM_INDEX_INTRO_SUICUNE_AWAY);
    // CALL(aInitSpriteAnimStruct);
    InitSpriteAnimStruct(SPRITE_ANIM_INDEX_INTRO_SUICUNE_AWAY, pixel2(12, 0));
    // XOR_A_A;
    // LD_addr_A(wIntroSceneFrameCounter);
    // LD_addr_A(wIntroSceneTimer);
    wram->wIntroSceneFrameCounter = 0;
    wram->wIntroSceneTimer = 0;
    // CALL(aNextIntroScene);
    // RET;
    NextIntroScene();

}

static void IntroScene16(void){
//  Suicune shows its face. An Unown appears in front.
    // LD_HL(wIntroSceneFrameCounter);
    // LD_A_hl;
    // INC_hl;
    uint8_t ctr = wram->wIntroSceneFrameCounter++;
    // CP_A(0x80);
    // IF_NC goto done;
    if(ctr >= 0x80) { 
    // done:
        // CALL(aNextIntroScene);
        // RET;
        NextIntroScene();
        return;
    }
    // CALL(aIntro_Scene16_AnimateSuicune);
    Intro_Scene16_AnimateSuicune();
    // LDH_A_addr(hSCY);
    // AND_A_A;
    // RET_Z ;
    if(hram->hSCY == 0)
        return;
    // ADD_A(8);
    // LDH_addr_A(hSCY);
    hram->hSCY += 8;
    // RET;
    // return;

}

static void IntroScene17(void){
//  ...
    // CALL(aIntro_ClearBGPals);
    Intro_ClearBGPals_Conv();
    // CALL(aClearSprites);
    ClearSprites();
    // CALL(aClearTilemap);
    ClearTilemap();
    DelayFrames(TRANSITION_WAIT_FRAMES);
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = BGMAPMODE_NONE;
    // LD_A(0x1);
    // LDH_addr_A(rVBK);
    // gb_write(rVBK, 0x1);
    // LD_HL(mIntroSuicuneCloseAttrmap);
    // debgcoord(0, 0, vBGMap0);
    // CALL(aIntro_DecompressRequest2bpp_64Tiles);
    // Intro_DecompressRequest2bpp_64Tiles_Conv(mIntroSuicuneCloseAttrmap, bgcoord(0, 0, vBGMap0));
    Load2bppBinaryAssetToBuffer(coord(0, 0, vram->vBGMap2), sizeof(vram->vBGMap2), IntroSuicuneCloseAttrmap, 0, 64);
    // LD_A(0x0);
    // LDH_addr_A(rVBK);
    // gb_write(rVBK, 0x0);
    // LD_HL(mIntroSuicuneCloseGFX);
    // LD_DE(vTiles1 + LEN_2BPP_TILE * 0x00);
    // CALL(aIntro_DecompressRequest2bpp_255Tiles);
    // Intro_DecompressRequest2bpp_255Tiles_Conv(mIntroSuicuneCloseGFX, vTiles1 + LEN_2BPP_TILE * 0x00);
    LoadPNG2bppAssetToVRAM(vram->vTiles1, IntroSuicuneCloseGFX);
    // LD_HL(mIntroSuicuneCloseTilemap);
    // debgcoord(0, 0, vBGMap0);
    // CALL(aIntro_DecompressRequest2bpp_64Tiles);
    // Intro_DecompressRequest2bpp_64Tiles_Conv(mIntroSuicuneCloseTilemap, bgcoord(0, 0, vBGMap0));
    Load2bppBinaryAssetToBuffer(coord(0, 0, vram->vBGMap0), sizeof(vram->vBGMap0), IntroSuicuneCloseTilemap, 0, 64);
    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    // LD_A(MBANK(awBGPals1));
    // LDH_addr_A(rSVBK);
    // wbank_push(MBANK(awBGPals1));
    // LD_HL(mIntroSuicuneClosePalette);
    // LD_DE(wBGPals1);
    // LD_BC(16 * PALETTE_SIZE);
    // CALL(aCopyBytes);
    // CopyBytes_GB(wBGPals1, mIntroSuicuneClosePalette, 16 * PALETTE_SIZE);
    LoadPaletteAssetToArray(wram->wBGPals1, IntroSuicuneClosePalette, 16);
    // LD_HL(mIntroSuicuneClosePalette);
    // LD_DE(wBGPals2);
    // LD_BC(16 * PALETTE_SIZE);
    // CALL(aCopyBytes);
    // CopyBytes_GB(wBGPals2, mIntroSuicuneClosePalette, 16 * PALETTE_SIZE);
    LoadPaletteAssetToArray(wram->wBGPals2, IntroSuicuneClosePalette, 16);
    // POP_AF;
    // LDH_addr_A(rSVBK);
    // wbank_pop;
    // XOR_A_A;
    // LDH_addr_A(hSCX);
    // LDH_addr_A(hSCY);
    hram->hSCX = 0;
    hram->hSCY = 0;
    // LD_A(0x7);
    // LDH_addr_A(hWX);
    hram->hWX = 0x7;
    // LD_A(0x90);
    // LDH_addr_A(hWY);
    hram->hWY = 0x90;
    // FARCALL(aClearSpriteAnims);
    ClearSpriteAnims();
    // CALL(aIntro_SetCGBPalUpdate);
    hram->hCGBPalUpdate = TRUE;
    // XOR_A_A;
    // LD_addr_A(wIntroSceneFrameCounter);
    // LD_addr_A(wIntroSceneTimer);
    wram->wIntroSceneFrameCounter = 0;
    wram->wIntroSceneTimer = 0;
    // CALL(aNextIntroScene);
    // RET;
    NextIntroScene();
}

static void IntroScene18(void){
//  Suicune close up.
    // LD_HL(wIntroSceneFrameCounter);
    // LD_A_hl;
    // INC_hl;
    uint8_t ctr = wram->wIntroSceneFrameCounter++;
    // CP_A(0x60);
    // IF_NC goto done;
    if(ctr >= 0x60) {    
    // done:
        // CALL(aNextIntroScene);
        // RET;
        NextIntroScene();
        return;
    }
    // LDH_A_addr(hSCX);
    // CP_A(0x60);
    // RET_Z ;
    if(hram->hSCX == 0x60)
        return;
    // ADD_A(8);
    // LDH_addr_A(hSCX);
    hram->hSCX += 8;
    // RET;
    // return;
}

static void IntroScene19(void){
//  More setup.
    // CALL(aIntro_ClearBGPals);
    Intro_ClearBGPals_Conv();
    // CALL(aClearSprites);
    ClearSprites();
    // CALL(aClearTilemap);
    ClearTilemap();
    DelayFrames(TRANSITION_WAIT_FRAMES);
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = BGMAPMODE_NONE;
    // LD_A(0x1);
    // LDH_addr_A(rVBK);
    // gb_write(rVBK, 0x1);
    // LD_HL(mIntroSuicuneBackAttrmap);
    // debgcoord(0, 0, vBGMap0);
    // CALL(aIntro_DecompressRequest2bpp_64Tiles);
    // Intro_DecompressRequest2bpp_64Tiles_Conv(mIntroSuicuneBackAttrmap, bgcoord(0, 0, vBGMap0));
    Load2bppBinaryAssetToBuffer(coord(0, 0, vram->vBGMap2), sizeof(vram->vBGMap2), IntroSuicuneBackAttrmap, 0, 64);
    // LD_A(0x0);
    // LDH_addr_A(rVBK);
    // gb_write(rVBK, 0x0);
    // LD_HL(mIntroSuicuneBackGFX);
    // LD_DE(vTiles2 + LEN_2BPP_TILE * 0x00);
    // CALL(aIntro_DecompressRequest2bpp_128Tiles);
    // Intro_DecompressRequest2bpp_128Tiles_Conv(mIntroSuicuneBackGFX, vTiles2 + LEN_2BPP_TILE * 0x00);
    LoadPNG2bppAssetToVRAM(vram->vTiles2, IntroSuicuneBackGFX);
    // LD_HL(mIntroUnownsGFX);
    // LD_DE(vTiles1 + LEN_2BPP_TILE * 0x00);
    // CALL(aIntro_DecompressRequest2bpp_128Tiles);
    // Intro_DecompressRequest2bpp_128Tiles_Conv(mIntroUnownsGFX, vTiles1 + LEN_2BPP_TILE * 0x00);
    LoadPNG2bppAssetToVRAM(vram->vTiles1, IntroUnownsGFX);
    // LD_DE(mIntroGrass4GFX);
    // LD_HL(vTiles1 + LEN_2BPP_TILE * 0x7f);
    // LD_BC((BANK(aIntroGrass4GFX) << 8) | 1);
    // CALL(aRequest2bpp);
    // Request2bpp_Conv(BANK(aIntroGrass4GFX), mIntroGrass4GFX, vTiles1 + LEN_2BPP_TILE * 0x7f, 1);
    // LoadPNG2bppAssetSectionToVRAM(vram->vTiles1 + LEN_2BPP_TILE * 0x7f, "gfx/intro/grass4.png", 0, 1);
    CopyBytes(vram->vTiles1 + LEN_2BPP_TILE * 0x7f, IntroGrass4GFX, 1 * LEN_2BPP_TILE);
    // LD_HL(mIntroSuicuneBackTilemap);
    // debgcoord(0, 0, vBGMap0);
    // CALL(aIntro_DecompressRequest2bpp_64Tiles);
    // Intro_DecompressRequest2bpp_64Tiles_Conv(mIntroSuicuneBackTilemap, bgcoord(0, 0, vBGMap0));
    // CALL(aIntro_LoadTilemap);
    Intro_LoadTilemap_Conv(Load2bppBinaryAssetToBuffer(bgcoord(0, 0, vram->vBGMap0), sizeof(vram->vBGMap0), IntroSuicuneBackTilemap, 0, 64));
    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    // LD_A(MBANK(awBGPals1));
    // LDH_addr_A(rSVBK);
    // wbank_push(MBANK(awBGPals1));
    // LD_HL(mIntroSuicunePalette);
    // LD_DE(wBGPals1);
    // LD_BC(16 * PALETTE_SIZE);
    // CALL(aCopyBytes);
    // CopyBytes_GB(wBGPals1, mIntroSuicunePalette, 16 * PALETTE_SIZE);
    LoadPaletteAssetToArray(wram->wBGPals1, IntroSuicunePalette, 16);
    // LD_HL(mIntroSuicunePalette);
    // LD_DE(wBGPals2);
    // LD_BC(16 * PALETTE_SIZE);
    // CALL(aCopyBytes);
    // CopyBytes_GB(wBGPals2, mIntroSuicunePalette, 16 * PALETTE_SIZE);
    LoadPaletteAssetToArray(wram->wBGPals2, IntroSuicunePalette, 16);
    // POP_AF;
    // LDH_addr_A(rSVBK);
    // wbank_pop;
    // XOR_A_A;
    // LDH_addr_A(hSCX);
    hram->hSCX = 0;
    // LD_A(0xd8);
    // LDH_addr_A(hSCY);
    hram->hSCY = 0xd8;
    // LD_A(0x7);
    // LDH_addr_A(hWX);
    hram->hWX = 0x7;
    // LD_A(0x90);
    // LDH_addr_A(hWY);
    hram->hWY = 0x90;
    // FARCALL(aClearSpriteAnims);
    ClearSpriteAnims();
    // LD_HL(wSpriteAnimDict);
    // XOR_A_A;  // SPRITE_ANIM_DICT_DEFAULT
    // LD_hli_A;
    // LD_hl(0x7f);
    wram->wSpriteAnimDict[0] = SPRITE_ANIM_DICT_DEFAULT;
    wram->wSpriteAnimDict[1] = 0x7f;
    // CALL(aIntro_SetCGBPalUpdate);
    hram->hCGBPalUpdate = TRUE;
    //depixel ['12', '0']
    // depixel2(12, 0);
    // LD_A(SPRITE_ANIM_INDEX_INTRO_SUICUNE_AWAY);
    // CALL(aInitSpriteAnimStruct);
    InitSpriteAnimStruct(SPRITE_ANIM_INDEX_INTRO_SUICUNE_AWAY, pixel2(12, 0));
    // XOR_A_A;
    // LD_addr_A(wIntroSceneFrameCounter);
    // LD_addr_A(wIntroSceneTimer);
    wram->wIntroSceneFrameCounter = 0;
    wram->wIntroSceneTimer = 0;
    // CALL(aNextIntroScene);
    // RET;
    NextIntroScene();
}

//  Spawn the palette for the nth Unown
static void Intro_Scene20_AppearUnown_Conv(uint8_t pal){
    static const char pal1[] = "gfx/intro/unown_1.pal";
    static const char pal2[] = "gfx/intro/unown_2.pal";
    // AND_A_A;
    // IF_NZ goto load_pal_2;

    // LD_HL(mIntro_Scene20_AppearUnown_pal1);
    // goto got_pointer;


// load_pal_2:
    // LD_HL(mIntro_Scene20_AppearUnown_pal2);

    const char* hl;
    switch(pal) {
        case 0: hl = pal1; break;
        default: hl = pal2; break;
    }

// got_pointer:
    // LD_A_addr(wIntroSceneTimer);
    // AND_A(0x7);
    // ADD_A_A;
    // ADD_A_A;
    // ADD_A_A;
    // LD_C_A;
    uint8_t c = (wram->wIntroSceneTimer & 0x7) << 3;
    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    // LD_A(MBANK(awBGPals2));
    // LDH_addr_A(rSVBK);

    // PUSH_BC;
    // LD_DE(wBGPals2);

    // LD_A_C;
    // ADD_A_E;
    // LD_E_A;
    // LD_A(0x0);
    // ADC_A_D;
    // LD_D_A;

    // LD_BC(1 * PALETTE_SIZE);
    // CALL(aCopyBytes);
    // CopyBytes_GB(wBGPals2 + c, hl, 1 * PALETTE_SIZE);
    LoadPaletteAssetColorsToBuffer(wram->wBGPals2 + c, sizeof(wram->wBGPals2) - c, hl, 0, NUM_PAL_COLORS);
    // POP_BC;

    // LD_DE(wBGPals1);
    // LD_A_C;
    // ADD_A_E;
    // LD_E_A;
    // LD_A(0x0);
    // ADC_A_D;
    // LD_D_A;

    // LD_BC(1 * PALETTE_SIZE);
    // CALL(aCopyBytes);
    // CopyBytes_GB(wBGPals1 + c, hl, 1 * PALETTE_SIZE);
    LoadPaletteAssetColorsToBuffer(wram->wBGPals1 + c, sizeof(wram->wBGPals2) - c, hl, 1 * NUM_PAL_COLORS, NUM_PAL_COLORS);

    // POP_AF;
    // LDH_addr_A(rSVBK);
    // LD_A(TRUE);
    // LDH_addr_A(hCGBPalUpdate);
    hram->hCGBPalUpdate = TRUE;
    // RET;

    // return Intro_FadeUnownWordPals();
}

static void IntroScene20(void){
//  Suicune running away. A bunch of Unown appear.
    // LD_HL(wIntroSceneFrameCounter);
    // LD_A_hl;
    // INC_hl;
    uint8_t ctr = wram->wIntroSceneFrameCounter++;
    // CP_A(0x98);
    // IF_NC goto finished;
    if(ctr >= 0x98) {
    // finished:
        // CALL(aNextIntroScene);
        NextIntroScene();
        // RET;
        return;
    }
    // CP_A(0x58);
    // RET_NC ;
    if(ctr >= 0x58)
        return;
    // CP_A(0x40);
    // IF_NC goto AppearUnown;
    if(ctr >= 0x40) {
    // AppearUnown:
        // SUB_A(0x18);
        // LD_C_A;
        uint8_t c = ctr - 0x18;
        // AND_A(0x3);
        // CP_A(0x3);
        // RET_NZ ;
        if((c & 0x3) != 0x3)
            return;
        // LD_A_C;
        // AND_A(0x1c);
        // SRL_A;
        // SRL_A;
        // LD_addr_A(wIntroSceneTimer);
        wram->wIntroSceneTimer = (c & 0x1c) >> 2;
        // XOR_A_A;
        // CALL(aIntro_Scene20_AppearUnown);
        Intro_Scene20_AppearUnown_Conv(0);
        // RET;
        return;
    }
    // CP_A(0x28);
    // RET_NC ;
    if(ctr >= 0x28)
        return;
    // LDH_A_addr(hSCY);
    // INC_A;
    // LDH_addr_A(hSCY);
    hram->hSCY++;
    // RET;


// AppearUnownPal2:
//   //  unreferenced
    // LD_A_C;
    // AND_A(0x1c);
    // SRL_A;
    // SRL_A;
    // LD_addr_A(wIntroSceneTimer);
    // LD_A(1);
    // CALL(aIntro_Scene20_AppearUnown);
    // RET;
}

static void IntroScene21(void){
//  Suicune gets more distant and turns black.
    // CALL(aIntro_ColoredSuicuneFrameSwap);
    Intro_ColoredSuicuneFrameSwap();
    // LD_C(3);
    // CALL(aDelayFrames);
    DelayFrames(3);
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = BGMAPMODE_NONE;
    // LD_addr_A(wIntroSceneFrameCounter);
    // LD_addr_A(wIntroSceneTimer);
    wram->wIntroSceneFrameCounter = 0;
    wram->wIntroSceneTimer = 0;
    // CALL(aNextIntroScene);
    NextIntroScene();
    // RET;

}

static void IntroScene22(void){
    // LD_HL(wIntroSceneFrameCounter);
    // LD_A_hl;
    // INC_hl;
    uint8_t ctr = wram->wIntroSceneFrameCounter++;
    // CP_A(0x8);
    // IF_NC goto done;
    if(ctr >= 0x8) {
    // done:
        // FARCALL(aDeinitializeAllSprites);
        DeinitializeAllSprites();
        // CALL(aNextIntroScene);
        NextIntroScene();
        // RET;
        return;
    }
    // RET;

}

static void IntroScene23(void){
    // XOR_A_A;
    // LD_addr_A(wIntroSceneFrameCounter);
    wram->wIntroSceneFrameCounter = 0;
    // CALL(aNextIntroScene);
    NextIntroScene();
    // RET;

}

//  load the (a)th palette from .FadePals to all wBGPals2
static void Intro_Scene24_ApplyPaletteFade_Conv(uint8_t a){
    // Fade to white.
    static const uint16_t FadePals[] = {
        rgb(24, 12,  9),
        rgb(31, 31, 31),
        rgb(12,  0, 31),
        rgb( 0,  0,  0),

        rgb(31, 19,  5),
        rgb(31, 31, 31),
        rgb(15,  5, 31),
        rgb( 7,  7,  7),

        rgb(31, 21,  9),
        rgb(31, 31, 31),
        rgb(18,  9, 31),
        rgb(11, 11, 11),

        rgb(31, 23, 13),
        rgb(31, 31, 31),
        rgb(21, 13, 31),
        rgb(15, 15, 15),

        rgb(31, 25, 17),
        rgb(31, 31, 31),
        rgb(25, 17, 31),
        rgb(19, 19, 19),

        rgb(31, 27, 21),
        rgb(31, 31, 31),
        rgb(27, 21, 31),
        rgb(23, 23, 23),

        rgb(31, 29, 25),
        rgb(31, 31, 31),
        rgb(29, 26, 31),
        rgb(27, 27, 27),

        rgb(31, 31, 31),
        rgb(31, 31, 31),
        rgb(31, 31, 31),
        rgb(31, 31, 31),
    };
    // LD_HL(mIntro_Scene24_ApplyPaletteFade_FadePals);
    // ADD_A_L;
    // LD_L_A;
    // LD_A(0x0);
    // ADC_A_H;
    // LD_H_A;
    // uint16_t hl = mIntro_Scene24_ApplyPaletteFade_FadePals + a;
    const uint16_t* hl = FadePals + (a >> 1);

    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    // LD_A(MBANK(awBGPals2));
    // LDH_addr_A(rSVBK);
    // LD_DE(wBGPals2);
    uint16_t* de = (uint16_t*)wram_ptr(wBGPals2);
    // LD_B(8);  // number of BG pals
    uint8_t b = 8;  // number of BG pals

    do {
    // loop1:
        // PUSH_HL;
        // LD_C(1 * PALETTE_SIZE);

        for(uint8_t c = 0; c < NUM_PAL_COLORS; ++c) {
        // loop2:
            // LD_A_hli;
            // LD_de_A;
            // INC_DE;
            de[(8-b)*NUM_PAL_COLORS + c] = hl[c];
            // DEC_C;
            // IF_NZ goto loop2;
        }
        // POP_HL;
        // DEC_B;
        // IF_NZ goto loop1;
    } while(--b != 0);
    // POP_AF;
    // LDH_addr_A(rSVBK);
    // LD_A(TRUE);
    // LDH_addr_A(hCGBPalUpdate);
    hram->hCGBPalUpdate = TRUE;
    // RET;


// FadePals:
// INCLUDE "gfx/intro/fade.pal"
}

static void IntroScene24(void){
//  Fade to white.
    // LD_HL(wIntroSceneFrameCounter);
    // LD_A_hl;
    // INC_hl;
    uint8_t ctr = wram->wIntroSceneFrameCounter++;
    // CP_A(0x20);
    // IF_NC goto done;
    if(ctr >= 0x20) {
    // done:
        // LD_A(0x40);
        // LD_addr_A(wIntroSceneFrameCounter);
        wram->wIntroSceneFrameCounter = 0x40;
        // CALL(aNextIntroScene);
        NextIntroScene();
        // RET;
        return;
    }

    // LD_C_A;
    // AND_A(0x3);
    // RET_NZ ;
    if((ctr & 0x3) != 0) 
        return;

    // LD_A_C;
    // AND_A(0x1c);
    // SLA_A;
    // CALL(aIntro_Scene24_ApplyPaletteFade);
    Intro_Scene24_ApplyPaletteFade_Conv((ctr & 0x1c) << 1);
    // RET;
}

static void IntroScene25(void){
//  Wait around a bit.
    // LD_A_addr(wIntroSceneFrameCounter);
    // DEC_A;
    // IF_Z goto done;
    // LD_addr_A(wIntroSceneFrameCounter);
    // RET;
    if(--wram->wIntroSceneFrameCounter == 0) {
    // done:
        // CALL(aNextIntroScene);
        // RET;
        NextIntroScene();
    }
    // return;

}

static void IntroScene26(void){
//  Load the final scene.
    // CALL(aClearBGPalettes);
    ClearBGPalettes();
    // CALL(aClearSprites);
    ClearSprites();
    // CALL(aClearTilemap);
    ClearTilemap();
    DelayFrames(TRANSITION_WAIT_FRAMES);
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = BGMAPMODE_NONE;
    // LD_A(0x1);
    // LDH_addr_A(rVBK);
    // gb_write(rVBK, 0x1);
    // LD_HL(mIntroCrystalUnownsAttrmap);
    // debgcoord(0, 0, vBGMap0);
    // CALL(aIntro_DecompressRequest2bpp_64Tiles);
    // Intro_DecompressRequest2bpp_64Tiles_Conv(mIntroCrystalUnownsAttrmap, bgcoord(0, 0, vBGMap0));
    // Load2bppBinaryAssetToBuffer(bgcoord(0, 0, vram->vBGMap2), sizeof(vram->vBGMap2), IntroCrystalUnownsAttrmap, 0, 64);
    LoadAssetToBuffer(bgcoord(0, 0, vram->vBGMap2), sizeof(vram->vBGMap2), IntroCrystalUnownsAttrmap);
    // LD_A(0x0);
    // LDH_addr_A(rVBK);
    // gb_write(rVBK, 0x0);
    // LD_HL(mIntroCrystalUnownsGFX);
    // LD_DE(vTiles2 + LEN_2BPP_TILE * 0x00);
    // CALL(aIntro_DecompressRequest2bpp_128Tiles);
    // Intro_DecompressRequest2bpp_128Tiles_Conv(mIntroCrystalUnownsGFX, vTiles2 + LEN_2BPP_TILE * 0x00);
    LoadPNG2bppAssetToVRAM(vram->vTiles2, IntroCrystalUnownsGFX);
    // LD_HL(mIntroCrystalUnownsTilemap);
    // debgcoord(0, 0, vBGMap0);
    // CALL(aIntro_DecompressRequest2bpp_64Tiles);
    // Intro_DecompressRequest2bpp_64Tiles_Conv(mIntroCrystalUnownsTilemap, bgcoord(0, 0, vBGMap0));
    // Load2bppBinaryAssetToBuffer(bgcoord(0, 0, vram->vBGMap0), sizeof(vram->vBGMap0), IntroCrystalUnownsTilemap, 0, 64);
    LoadAssetToBuffer(bgcoord(0, 0, vram->vBGMap0), sizeof(vram->vBGMap0), IntroCrystalUnownsTilemap);
    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    // LD_A(MBANK(awBGPals1));
    // LDH_addr_A(rSVBK);
    // wbank_push(MBANK(awBGPals1));
    // LD_HL(mIntroCrystalUnownsPalette);
    // LD_DE(wBGPals1);
    // LD_BC(16 * PALETTE_SIZE);
    // CALL(aCopyBytes);
    // CopyBytes_GB(wBGPals1, mIntroCrystalUnownsPalette, 16 * PALETTE_SIZE);
    LoadPaletteAssetToArray(wram->wBGPals1, IntroCrystalUnownsPalette, 16);
    // LD_HL(mIntroCrystalUnownsPalette);
    // LD_DE(wBGPals2);
    // LD_BC(16 * PALETTE_SIZE);
    // CALL(aCopyBytes);
    // CopyBytes_GB(wBGPals2, mIntroCrystalUnownsPalette, 16 * PALETTE_SIZE);
    LoadPaletteAssetToArray(wram->wBGPals2, IntroCrystalUnownsPalette, 16);
    // POP_AF;
    // LDH_addr_A(rSVBK);
    // wbank_pop;
    // XOR_A_A;
    // LDH_addr_A(hSCX);
    // LDH_addr_A(hSCY);
    hram->hSCX = 0;
    hram->hSCY = 0;
    // LD_A(0x7);
    // LDH_addr_A(hWX);
    hram->hWX = 0x7;
    // LD_A(0x90);
    // LDH_addr_A(hWY);
    hram->hWY = 0x90;
    // FARCALL(aClearSpriteAnims);
    ClearSpriteAnims();
    // CALL(aIntro_SetCGBPalUpdate);
    hram->hCGBPalUpdate = TRUE;
    // XOR_A_A;
    // LD_addr_A(wIntroSceneFrameCounter);
    // LD_addr_A(wIntroSceneTimer);
    wram->wIntroSceneFrameCounter = 0;
    wram->wIntroSceneTimer = 0;
    // CALL(aNextIntroScene);
    // RET;
    NextIntroScene();
}

static void IntroScene27(void){
//  Spell out C R Y S T A L with Unown.
    // LD_HL(wIntroSceneTimer);
    // INC_hl;
    wram->wIntroSceneTimer++;
    // LD_HL(wIntroSceneFrameCounter);
    // LD_A_hl;
    // INC_hl;
    uint8_t ctr = wram->wIntroSceneFrameCounter++;
    // CP_A(0x80);
    // IF_NC goto done;
    if(ctr >= 0x80) {
    // done:
        // CALL(aNextIntroScene);
        NextIntroScene();
        // LD_A(0x80);
        // LD_addr_A(wIntroSceneFrameCounter);
        wram->wIntroSceneFrameCounter = 0x80;
        // RET;
        return;
    }

    // LD_C_A;
    // AND_A(0xf);
    // LD_addr_A(wIntroSceneTimer);
    wram->wIntroSceneTimer = ctr & 0xf;
    // LD_A_C;
    // AND_A(0x70);
    // SWAP_A;
    // CALL(aIntro_FadeUnownWordPals);
    Intro_FadeUnownWordPals_Conv((ctr & 0x70) >> 4);
    // RET;
}

static void IntroScene28(void){
//  Cut out when the music ends, and lead into the title screen.
    // LD_HL(wIntroSceneFrameCounter);
    // LD_A_hl;
    uint8_t ctr = wram->wIntroSceneFrameCounter--;
    // AND_A_A;
    // IF_Z goto done;
    if(ctr == 0) {
    // done:
        // LD_HL(wJumptableIndex);
        // SET_hl(7);
        wram->wJumptableIndex |= (1 << 7);
        // RET;
        return;
    }
    // DEC_hl;
    // CP_A(0x18);
    // IF_Z goto clear;
    if(ctr == 0x18) {
    // clear:
        // CALL(aClearBGPalettes);
        ClearBGPalettes();
        // RET;
        return;
    }
    // CP_A(0x8);
    // RET_NZ ;
    if(ctr != 0x8)
        return;

    // LD_DE(SFX_INTRO_WHOOSH);
    // CALL(aPlaySFX);
    // RET;
    PlaySFX(SFX_INTRO_WHOOSH);
}

void Intro_Scene24_ApplyPaletteFade(void){
//  load the (a)th palette from .FadePals to all wBGPals2
    LD_HL(mIntro_Scene24_ApplyPaletteFade_FadePals);
    ADD_A_L;
    LD_L_A;
    LD_A(0x0);
    ADC_A_H;
    LD_H_A;

    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(MBANK(awBGPals2));
    LDH_addr_A(rSVBK);
    LD_DE(wBGPals2);
    LD_B(8);  // number of BG pals

loop1:
    PUSH_HL;
    LD_C(1 * PALETTE_SIZE);

loop2:
    LD_A_hli;
    LD_de_A;
    INC_DE;
    DEC_C;
    IF_NZ goto loop2;
    POP_HL;
    DEC_B;
    IF_NZ goto loop1;
    POP_AF;
    LDH_addr_A(rSVBK);
    LD_A(TRUE);
    LDH_addr_A(hCGBPalUpdate);
    RET;


// FadePals:
// INCLUDE "gfx/intro/fade.pal"

    // return CrystalIntro_InitUnownAnim();
}

void CrystalIntro_InitUnownAnim(void){
    PUSH_DE;
    LD_A(SPRITE_ANIM_INDEX_INTRO_UNOWN);
    CALL(aInitSpriteAnimStruct);
    LD_HL(SPRITEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_hl(0x8);
    LD_A(SPRITE_ANIM_FRAMESET_INTRO_UNOWN_4);
    CALL(aReinitSpriteAnimFrame);
    POP_DE;

    PUSH_DE;
    LD_A(SPRITE_ANIM_INDEX_INTRO_UNOWN);
    CALL(aInitSpriteAnimStruct);
    LD_HL(SPRITEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_hl(0x18);
    LD_A(SPRITE_ANIM_FRAMESET_INTRO_UNOWN_3);
    CALL(aReinitSpriteAnimFrame);
    POP_DE;

    PUSH_DE;
    LD_A(SPRITE_ANIM_INDEX_INTRO_UNOWN);
    CALL(aInitSpriteAnimStruct);
    LD_HL(SPRITEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_hl(0x28);
    LD_A(SPRITE_ANIM_FRAMESET_INTRO_UNOWN_1);
    CALL(aReinitSpriteAnimFrame);
    POP_DE;

    LD_A(SPRITE_ANIM_INDEX_INTRO_UNOWN);
    CALL(aInitSpriteAnimStruct);
    LD_HL(SPRITEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_hl(0x38);
    LD_A(SPRITE_ANIM_FRAMESET_INTRO_UNOWN_2);
    CALL(aReinitSpriteAnimFrame);
    RET;

}

static void CrystalIntro_InitUnownAnim_Conv(uint16_t de){
    // PUSH_DE;
    // LD_A(SPRITE_ANIM_INDEX_INTRO_UNOWN);
    // CALL(aInitSpriteAnimStruct);
    struct SpriteAnim* bc = InitSpriteAnimStruct(SPRITE_ANIM_INDEX_INTRO_UNOWN, de);
    // LD_HL(SPRITEANIMSTRUCT_VAR1);
    // ADD_HL_BC;
    // LD_hl(0x8);
    bc->var1 = 0x8;
    // LD_A(SPRITE_ANIM_FRAMESET_INTRO_UNOWN_4);
    // CALL(aReinitSpriteAnimFrame);
    // POP_DE;
    ReinitSpriteAnimFrame(bc, SPRITE_ANIM_FRAMESET_INTRO_UNOWN_4);

    // PUSH_DE;
    // LD_A(SPRITE_ANIM_INDEX_INTRO_UNOWN);
    // CALL(aInitSpriteAnimStruct);
    bc = InitSpriteAnimStruct(SPRITE_ANIM_INDEX_INTRO_UNOWN, de);
    // LD_HL(SPRITEANIMSTRUCT_VAR1);
    // ADD_HL_BC;
    // LD_hl(0x18);
    bc->var1 = 0x18;
    // LD_A(SPRITE_ANIM_FRAMESET_INTRO_UNOWN_3);
    // CALL(aReinitSpriteAnimFrame);
    // POP_DE;
    ReinitSpriteAnimFrame(bc, SPRITE_ANIM_FRAMESET_INTRO_UNOWN_3);

    // PUSH_DE;
    // LD_A(SPRITE_ANIM_INDEX_INTRO_UNOWN);
    // CALL(aInitSpriteAnimStruct);
    bc = InitSpriteAnimStruct(SPRITE_ANIM_INDEX_INTRO_UNOWN, de);
    // LD_HL(SPRITEANIMSTRUCT_VAR1);
    // ADD_HL_BC;
    // LD_hl(0x28);
    bc->var1 = 0x28;
    // LD_A(SPRITE_ANIM_FRAMESET_INTRO_UNOWN_1);
    // CALL(aReinitSpriteAnimFrame);
    // POP_DE;
    ReinitSpriteAnimFrame(bc, SPRITE_ANIM_FRAMESET_INTRO_UNOWN_1);

    // LD_A(SPRITE_ANIM_INDEX_INTRO_UNOWN);
    // CALL(aInitSpriteAnimStruct);
    bc = InitSpriteAnimStruct(SPRITE_ANIM_INDEX_INTRO_UNOWN, de);
    // LD_HL(SPRITEANIMSTRUCT_VAR1);
    // ADD_HL_BC;
    // LD_hl(0x38);
    bc->var1 = 0x38;
    // LD_A(SPRITE_ANIM_FRAMESET_INTRO_UNOWN_2);
    // CALL(aReinitSpriteAnimFrame);
    // RET;
    ReinitSpriteAnimFrame(bc, SPRITE_ANIM_FRAMESET_INTRO_UNOWN_2);
}

void CrystalIntro_UnownFade(void){
    ADD_A_A;
    ADD_A_A;
    ADD_A_A;
    LD_E_A;
    LD_D(0);
    LD_HL(wBGPals2);
    ADD_HL_DE;
    INC_HL;
    INC_HL;
    LD_A_addr(wIntroSceneTimer);
    AND_A(0b111111);
    CP_A(0b011111);
    IF_Z goto okay;
    IF_C goto okay;
    LD_C_A;
    LD_A(0b111111);
    SUB_A_C;

okay:

    LD_C_A;
    LD_B(0);
    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(MBANK(awBGPals2));
    LDH_addr_A(rSVBK);

    PUSH_HL;
    PUSH_BC;
    LD_HL(wBGPals2);
    LD_BC(8 * PALETTE_SIZE);
    XOR_A_A;
    CALL(aByteFill);
    POP_BC;
    POP_HL;

    PUSH_HL;
    LD_HL(mCrystalIntro_UnownFade_BWFade);
    ADD_HL_BC;
    ADD_HL_BC;
    LD_A_hli;
    LD_D_hl;
    LD_E_A;
    POP_HL;
    LD_A_E;
    LD_hli_A;
    LD_A_D;
    LD_hli_A;

    PUSH_HL;
    LD_HL(mCrystalIntro_UnownFade_BlackLBlueFade);
    ADD_HL_BC;
    ADD_HL_BC;
    LD_A_hli;
    LD_D_hl;
    LD_E_A;
    POP_HL;
    LD_A_E;
    LD_hli_A;
    LD_A_D;
    LD_hli_A;

    PUSH_HL;
    LD_HL(mCrystalIntro_UnownFade_BlackBlueFade);
    ADD_HL_BC;
    ADD_HL_BC;
    LD_A_hli;
    LD_D_hl;
    LD_E_A;
    POP_HL;
    LD_A_E;
    LD_hli_A;
    LD_A_D;
    LD_hli_A;

    POP_AF;
    LDH_addr_A(rSVBK);
    LD_A(TRUE);
    LDH_addr_A(hCGBPalUpdate);
    RET;


BWFade:
//  Fade between black and white.
    for(int hue = 0; hue < 32; hue++){
    //rgb ['hue', 'hue', 'hue']
    }


BlackLBlueFade:
//  Fade between black and light blue.
    for(int hue = 0; hue < 32; hue++){
    //rgb ['0', 'hue / 2', 'hue']
    }


BlackBlueFade:
//  Fade between black and blue.
    for(int hue = 0; hue < 32; hue++){
    //rgb ['0', '0', 'hue']
    }

    // return Intro_Scene20_AppearUnown();
}

static void CrystalIntro_UnownFade_Conv(uint8_t a){
// BWFade:
//  Fade between black and white.
    // for(int hue = 0; hue < 32; hue++){
    // //rgb ['hue', 'hue', 'hue']
    // }
    static const uint16_t BWFade[] = { 
        rgb(0x00,0x00,0x00), rgb(0x01,0x01,0x01), rgb(0x02,0x02,0x02), rgb(0x03,0x03,0x03),
        rgb(0x04,0x04,0x04), rgb(0x05,0x05,0x05), rgb(0x06,0x06,0x06), rgb(0x07,0x07,0x07),
        rgb(0x08,0x08,0x08), rgb(0x09,0x09,0x09), rgb(0x0a,0x0a,0x0a), rgb(0x0b,0x0b,0x0b),
        rgb(0x0c,0x0c,0x0c), rgb(0x0d,0x0d,0x0d), rgb(0x0e,0x0e,0x0e), rgb(0x0f,0x0f,0x0f),
        rgb(0x10,0x10,0x10), rgb(0x11,0x11,0x11), rgb(0x12,0x12,0x12), rgb(0x13,0x13,0x13),
        rgb(0x14,0x14,0x14), rgb(0x15,0x15,0x15), rgb(0x16,0x16,0x16), rgb(0x17,0x17,0x17),
        rgb(0x18,0x18,0x18), rgb(0x19,0x19,0x19), rgb(0x1a,0x1a,0x1a), rgb(0x1b,0x1b,0x1b),
        rgb(0x1c,0x1c,0x1c), rgb(0x1d,0x1d,0x1d), rgb(0x1e,0x1e,0x1e), rgb(0x1f,0x1f,0x1f), 
    };
// BlackLBlueFade:
//  Fade between black and light blue.
    // for(int hue = 0; hue < 32; hue++){
    // //rgb ['0', 'hue / 2', 'hue']
    // }
    static const uint16_t BlackLBlueFade[] = { 
        rgb(0x00,0x00,0x00), rgb(0x00,0x00,0x01), rgb(0x00,0x01,0x02), rgb(0x00,0x01,0x03),
        rgb(0x00,0x02,0x04), rgb(0x00,0x02,0x05), rgb(0x00,0x03,0x06), rgb(0x00,0x03,0x07),
        rgb(0x00,0x04,0x08), rgb(0x00,0x04,0x09), rgb(0x00,0x05,0x0a), rgb(0x00,0x05,0x0b),
        rgb(0x00,0x06,0x0c), rgb(0x00,0x06,0x0d), rgb(0x00,0x07,0x0e), rgb(0x00,0x07,0x0f),
        rgb(0x00,0x08,0x10), rgb(0x00,0x08,0x11), rgb(0x00,0x09,0x12), rgb(0x00,0x09,0x13),
        rgb(0x00,0x0a,0x14), rgb(0x00,0x0a,0x15), rgb(0x00,0x0b,0x16), rgb(0x00,0x0b,0x17),
        rgb(0x00,0x0c,0x18), rgb(0x00,0x0c,0x19), rgb(0x00,0x0d,0x1a), rgb(0x00,0x0d,0x1b),
        rgb(0x00,0x0e,0x1c), rgb(0x00,0x0e,0x1d), rgb(0x00,0x0f,0x1e), rgb(0x00,0x0f,0x1f), 
    };
// BlackBlueFade:
//  Fade between black and blue.
    // for(int hue = 0; hue < 32; hue++){
    // //rgb ['0', '0', 'hue']
    // }
    static const uint16_t BlackBlueFade[] = { 
        rgb(0x00,0x00,0x00), rgb(0x00,0x00,0x01), rgb(0x00,0x00,0x02), rgb(0x00,0x00,0x03),
        rgb(0x00,0x00,0x04), rgb(0x00,0x00,0x05), rgb(0x00,0x00,0x06), rgb(0x00,0x00,0x07),
        rgb(0x00,0x00,0x08), rgb(0x00,0x00,0x09), rgb(0x00,0x00,0x0a), rgb(0x00,0x00,0x0b),
        rgb(0x00,0x00,0x0c), rgb(0x00,0x00,0x0d), rgb(0x00,0x00,0x0e), rgb(0x00,0x00,0x0f),
        rgb(0x00,0x00,0x10), rgb(0x00,0x00,0x11), rgb(0x00,0x00,0x12), rgb(0x00,0x00,0x13),
        rgb(0x00,0x00,0x14), rgb(0x00,0x00,0x15), rgb(0x00,0x00,0x16), rgb(0x00,0x00,0x17),
        rgb(0x00,0x00,0x18), rgb(0x00,0x00,0x19), rgb(0x00,0x00,0x1a), rgb(0x00,0x00,0x1b),
        rgb(0x00,0x00,0x1c), rgb(0x00,0x00,0x1d), rgb(0x00,0x00,0x1e), rgb(0x00,0x00,0x1f), 
    };

    // ADD_A_A;
    // ADD_A_A;
    // ADD_A_A;
    // LD_E_A;
    // LD_D(0);
    // LD_HL(wBGPals2);
    // ADD_HL_DE;
    // INC_HL;
    // INC_HL;
    uint8_t* hl = wram->wBGPals2 + (a << 3) + 2;
    // LD_A_addr(wIntroSceneTimer);
    // AND_A(0b111111);
    // CP_A(0b011111);
    // IF_Z goto okay;
    // IF_C goto okay;
    uint16_t bc;
    if((wram->wIntroSceneTimer & 0b111111) > 0b011111) {
        // LD_C_A;
        // LD_A(0b111111);
        // SUB_A_C;
        bc = 0b111111 - (wram->wIntroSceneTimer & 0b111111);
    }
    else {
        // LD_C_A;
        // LD_B(0);
        bc = (wram->wIntroSceneTimer & 0b111111);
    }
    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    // LD_A(MBANK(awBGPals2));
    // LDH_addr_A(rSVBK);
    // wbank_push(MBANK(awBGPals2));

    // PUSH_HL;
    // PUSH_BC;
    // LD_HL(wBGPals2);
    // LD_BC(8 * PALETTE_SIZE);
    // XOR_A_A;
    // CALL(aByteFill);
    ByteFill(wram->wBGPals2, 8 * PALETTE_SIZE, 0);
    // POP_BC;
    // POP_HL;

    uint16_t de;
    // PUSH_HL;
    // LD_HL(mCrystalIntro_UnownFade_BWFade);
    // ADD_HL_BC;
    // ADD_HL_BC;
    // LD_A_hli;
    // LD_D_hl;
    // LD_E_A;
    de = BWFade[bc];
    // POP_HL;
    // LD_A_E;
    // LD_hli_A;
    *(hl++) = LOW(de);
    // LD_A_D;
    // LD_hli_A;
    *(hl++) = HIGH(de);

    // PUSH_HL;
    // LD_HL(mCrystalIntro_UnownFade_BlackLBlueFade);
    // ADD_HL_BC;
    // ADD_HL_BC;
    // LD_A_hli;
    // LD_D_hl;
    // LD_E_A;
    // de = gb_read16(mCrystalIntro_UnownFade_BlackLBlueFade + (2 * bc));
    de = BlackLBlueFade[bc];
    // POP_HL;
    // LD_A_E;
    // LD_hli_A;
    *(hl++) = LOW(de);
    // LD_A_D;
    // LD_hli_A;
    *(hl++) = HIGH(de);

    // PUSH_HL;
    // LD_HL(mCrystalIntro_UnownFade_BlackBlueFade);
    // ADD_HL_BC;
    // ADD_HL_BC;
    // LD_A_hli;
    // LD_D_hl;
    // LD_E_A;
    // de = gb_read16(mCrystalIntro_UnownFade_BlackBlueFade + (2 * bc));
    de = BlackBlueFade[bc];
    // POP_HL;
    // LD_A_E;
    // LD_hli_A;
    *(hl++) = LOW(de);
    // LD_A_D;
    // LD_hli_A;
    *(hl++) = HIGH(de);

    // POP_AF;
    // LDH_addr_A(rSVBK);
    // wbank_pop;
    // LD_A(TRUE);
    // LDH_addr_A(hCGBPalUpdate);
    hram->hCGBPalUpdate = TRUE;
    // RET;
}

void Intro_Scene20_AppearUnown(void){
//  Spawn the palette for the nth Unown
    AND_A_A;
    IF_NZ goto load_pal_2;

    LD_HL(mIntro_Scene20_AppearUnown_pal1);
    goto got_pointer;


load_pal_2:
    LD_HL(mIntro_Scene20_AppearUnown_pal2);


got_pointer:
    LD_A_addr(wIntroSceneTimer);
    AND_A(0x7);
    ADD_A_A;
    ADD_A_A;
    ADD_A_A;
    LD_C_A;
    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(MBANK(awBGPals2));
    LDH_addr_A(rSVBK);

    PUSH_BC;
    LD_DE(wBGPals2);

    LD_A_C;
    ADD_A_E;
    LD_E_A;
    LD_A(0x0);
    ADC_A_D;
    LD_D_A;

    LD_BC(1 * PALETTE_SIZE);
    CALL(aCopyBytes);
    POP_BC;

    LD_DE(wBGPals1);
    LD_A_C;
    ADD_A_E;
    LD_E_A;
    LD_A(0x0);
    ADC_A_D;
    LD_D_A;

    LD_BC(1 * PALETTE_SIZE);
    CALL(aCopyBytes);

    POP_AF;
    LDH_addr_A(rSVBK);
    LD_A(TRUE);
    LDH_addr_A(hCGBPalUpdate);
    RET;


// pal1:
// INCLUDE "gfx/intro/unown_1.pal"


// pal2:
// INCLUDE "gfx/intro/unown_2.pal"

    // return Intro_FadeUnownWordPals();
}

void Intro_FadeUnownWordPals(void){
    ADD_A_A;
    ADD_A_A;
    ADD_A_A;
    LD_E_A;
    LD_D(0);
    LD_HL(wBGPals2);
    ADD_HL_DE;
    for(int rept = 0; rept < 4; rept++){
    INC_HL;
    }
    LD_A_addr(wIntroSceneTimer);
    ADD_A_A;
    LD_C_A;
    LD_B(0);

    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(MBANK(awBGPals2));
    LDH_addr_A(rSVBK);

    PUSH_HL;
    LD_HL(mIntro_FadeUnownWordPals_FastFadePalettes);
    ADD_HL_BC;
    LD_A_hli;
    LD_D_hl;
    LD_E_A;
    POP_HL;
    LD_A_E;
    LD_hli_A;
    LD_A_D;
    LD_hli_A;

    PUSH_HL;
    LD_HL(mIntro_FadeUnownWordPals_SlowFadePalettes);
    ADD_HL_BC;
    LD_A_hli;
    LD_D_hl;
    LD_E_A;
    POP_HL;
    LD_A_E;
    LD_hli_A;
    LD_A_D;
    LD_hli_A;

    POP_AF;
    LDH_addr_A(rSVBK);
    LD_A(TRUE);
    LDH_addr_A(hCGBPalUpdate);
    RET;


// FastFadePalettes:
// hue = 31
//     for(int rept = 0; rept < 8; rept++){
//     //rgb ['hue', 'hue', 'hue']
// hue -= 1
//     //rgb ['hue', 'hue', 'hue']
// hue -= 2
//     }


// SlowFadePalettes:
// hue = 31
//     for(int rept = 0; rept < 16; rept++){
//     //rgb ['hue', 'hue', 'hue']
// hue -= 1
//     }

    // return Intro_LoadTilemap();
}

static void Intro_FadeUnownWordPals_Conv(uint8_t a){
// FastFadePalettes:
// hue = 31
//     for(int rept = 0; rept < 8; rept++){
//     //rgb ['hue', 'hue', 'hue']
// hue -= 1
//     //rgb ['hue', 'hue', 'hue']
// hue -= 2
//     }
    static const uint16_t FastFadePalettes[] = {
        rgb(31,31,31),rgb(30,30,30),
        rgb(28,28,28),rgb(27,27,27),
        rgb(25,25,25),rgb(24,24,24),
        rgb(22,22,22),rgb(21,21,21),
        rgb(19,19,19),rgb(18,18,18),
        rgb(16,16,16),rgb(15,15,15),
        rgb(13,13,13),rgb(12,12,12),
        rgb(10,10,10),rgb( 9, 9, 9),
    };
// SlowFadePalettes:
// hue = 31
//     for(int rept = 0; rept < 16; rept++){
//     //rgb ['hue', 'hue', 'hue']
// hue -= 1
//     }
    static const uint16_t SlowFadePalettes[] = {
        rgb(31,31,31),rgb(30,30,30),
        rgb(29,29,29),rgb(28,28,28),
        rgb(27,27,27),rgb(26,26,26),
        rgb(25,25,25),rgb(24,24,24),
        rgb(23,23,23),rgb(22,22,22),
        rgb(21,21,21),rgb(20,20,20),
        rgb(19,19,19),rgb(18,18,18),
        rgb(17,17,17),rgb(16,16,16),
    };
    // ADD_A_A;
    // ADD_A_A;
    // ADD_A_A;
    // LD_E_A;
    // LD_D(0);
    // LD_HL(wBGPals2);
    // ADD_HL_DE;
    // for(int rept = 0; rept < 4; rept++){
    // INC_HL;
    // }
    uint8_t* hl = wram->wBGPals2 + (a << 3) + 4;
    // uint16_t hl = wBGPals2 + (a << 3) + 4;
    // LD_A_addr(wIntroSceneTimer);
    // ADD_A_A;
    // LD_C_A;
    // LD_B(0);
    uint16_t bc = wram->wIntroSceneTimer;

    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    // LD_A(MBANK(awBGPals2));
    // LDH_addr_A(rSVBK);
    // wbank_push(MBANK(awBGPals2));

    // PUSH_HL;
    // LD_HL(mIntro_FadeUnownWordPals_FastFadePalettes);
    // ADD_HL_BC;
    // LD_A_hli;
    // LD_D_hl;
    // LD_E_A;
    // POP_HL;
    // LD_A_E;
    // LD_hli_A;
    // LD_A_D;
    // LD_hli_A;
    *(hl++) = LOW(FastFadePalettes[bc]);
    *(hl++) = HIGH(FastFadePalettes[bc]);
    // gb_write16(hl, FastFadePalettes[bc]);
    // hl += 2;

    // PUSH_HL;
    // LD_HL(mIntro_FadeUnownWordPals_SlowFadePalettes);
    // ADD_HL_BC;
    // LD_A_hli;
    // LD_D_hl;
    // LD_E_A;
    // POP_HL;
    // LD_A_E;
    // LD_hli_A;
    // LD_A_D;
    // LD_hli_A;
    // gb_write16(hl, SlowFadePalettes[bc]);
    *(hl++) = LOW(SlowFadePalettes[bc]);
    *hl = HIGH(SlowFadePalettes[bc]);

    // POP_AF;
    // LDH_addr_A(rSVBK);
    // wbank_pop;
    // LD_A(TRUE);
    // LDH_addr_A(hCGBPalUpdate);
    hram->hCGBPalUpdate = TRUE;
    // RET;
}

void Intro_LoadTilemap(void){
    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(MBANK(awDecompressScratch));
    LDH_addr_A(rSVBK);

    LD_HL(wDecompressScratch);
    decoord(0, 0, wTilemap);
    LD_B(SCREEN_HEIGHT);

row:
    LD_C(SCREEN_WIDTH);

col:
    LD_A_hli;
    LD_de_A;
    INC_DE;
    DEC_C;
    IF_NZ goto col;
    LD_A(BG_MAP_WIDTH - SCREEN_WIDTH);
    ADD_A_L;
    LD_L_A;
    LD_A(0);
    ADC_A_H;
    LD_H_A;
    DEC_B;
    IF_NZ goto row;

    POP_AF;
    LDH_addr_A(rSVBK);
    RET;

}

static void Intro_LoadTilemap_Conv(uint8_t* tilemap){
    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    // LD_A(MBANK(awDecompressScratch));
    // LDH_addr_A(rSVBK);
    // wbank_push(MBANK(awDecompressScratch));

    // LD_HL(wDecompressScratch);
    uint8_t* hl = tilemap;
    // decoord(0, 0, wTilemap);
    uint8_t* de = wram->wTilemap + coordidx(0, 0);
    // LD_B(SCREEN_HEIGHT);
    uint8_t b = SCREEN_HEIGHT;
    do {
// row:
        // LD_C(SCREEN_WIDTH);
        uint8_t c = SCREEN_WIDTH;
        do {
        // col:
            // LD_A_hli;
            // LD_de_A;
            // INC_DE;
            *(de++) = *(hl++);
            // DEC_C;
            // IF_NZ goto col;
        } while(--c != 0);
        // LD_A(BG_MAP_WIDTH - SCREEN_WIDTH);
        // ADD_A_L;
        // LD_L_A;
        // LD_A(0);
        // ADC_A_H;
        // LD_H_A;
        hl += (BG_MAP_WIDTH - SCREEN_WIDTH);
        // DEC_B;
        // IF_NZ goto row;
    } while(--b != 0);

    // POP_AF;
    // LDH_addr_A(rSVBK);
    // wbank_pop;
    // RET;
}

static void Intro_Scene16_AnimateSuicune(void){
    // LD_A_addr(wIntroSceneFrameCounter);
    // AND_A(0x3);
    // JR_Z (mIntro_ColoredSuicuneFrameSwap);
    if((wram->wIntroSceneFrameCounter & 3) == 0)
        return Intro_ColoredSuicuneFrameSwap();
    // CP_A(0x3);
    // IF_Z goto PrepareForSuicuneSwap;
    if((wram->wIntroSceneFrameCounter & 3) == 3) {
    // PrepareForSuicuneSwap:
        // XOR_A_A;
        // LDH_addr_A(hBGMapMode);
        hram->hBGMapMode = BGMAPMODE_NONE;
        // RET;
        return;
    }
    // RET;
}

static void Intro_ColoredSuicuneFrameSwap(void){
    // hlcoord(0, 0, wTilemap);
    uint8_t* hl = coord(0, 0, wram->wTilemap);
    // LD_BC(SCREEN_HEIGHT * SCREEN_WIDTH);
    uint16_t bc = SCREEN_HEIGHT * SCREEN_WIDTH;

// loop:
    do {
        // LD_A_hl;
        uint8_t a = *hl;
        // AND_A_A;
        // IF_Z goto skip;
        // CP_A(0x80);
        // IF_NC goto skip;
        if(a != 0 && a < 0x80) {
            // XOR_A(0x8);
            // LD_hl_A;
            *hl = a ^ 0x8;
        }

    // skip:
        // INC_HL;
        hl++;
        // DEC_BC;
        // LD_A_C;
        // OR_A_B;
        // IF_NZ goto loop;
    } while(--bc != 0);
    // LD_A(0x1);
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = BGMAPMODE_UPDATE_TILES;
    // RET;
}

void Intro_RustleGrass(void){
    LD_A_addr(wIntroSceneFrameCounter);
    CP_A(36);
    RET_NC ;
    AND_A(0xc);
    SRL_A;
    LD_E_A;
    LD_D(0);
    LD_HL(mIntro_RustleGrass_RustlingGrassPointers);
    ADD_HL_DE;
    LD_A_hli;
    LD_addr_A(wRequested2bppSource);
    LD_A_hli;
    LD_addr_A(wRequested2bppSource + 1);
    LD_A(LOW(vTiles2 + LEN_2BPP_TILE * 0x09));
    LD_addr_A(wRequested2bppDest);
    LD_A(HIGH(vTiles2 + LEN_2BPP_TILE * 0x09));
    LD_addr_A(wRequested2bppDest + 1);
    LD_A(4);
    LD_addr_A(wRequested2bppSize);
    RET;


RustlingGrassPointers:
    //dw ['IntroGrass1GFX'];
    //dw ['IntroGrass2GFX'];
    //dw ['IntroGrass3GFX'];
    //dw ['IntroGrass2GFX'];

    return Intro_SetCGBPalUpdate();
}

static void Intro_RustleGrass_Conv(void){
    static const uint8_t* RustlingGrassPointers[] = {
        IntroGrass1GFX,
        IntroGrass2GFX,
        IntroGrass3GFX,
        IntroGrass2GFX,
    };

    // LD_A_addr(wIntroSceneFrameCounter);
    // CP_A(36);
    // RET_NC ;
    if(wram->wIntroSceneFrameCounter >= 36)
        return;
    // AND_A(0xc);
    // SRL_A;
    // LD_E_A;
    // LD_D(0);
    // LD_HL(mIntro_RustleGrass_RustlingGrassPointers);
    // ADD_HL_DE;
    // LD_A_hli;
    // LD_addr_A(wRequested2bppSource);
    // LD_A_hli;
    // LD_addr_A(wRequested2bppSource + 1);
    // wram->wRequested2bppSource = RustlingGrassPointers[(wram->wIntroSceneFrameCounter & 0xc) >> 2];
    // LD_A(LOW(vTiles2 + LEN_2BPP_TILE * 0x09));
    // LD_addr_A(wRequested2bppDest);
    // LD_A(HIGH(vTiles2 + LEN_2BPP_TILE * 0x09));
    // LD_addr_A(wRequested2bppDest + 1);
    // wram->wRequested2bppDest = vTiles2 + LEN_2BPP_TILE * 0x09;
    // LD_A(4);
    // LD_addr_A(wRequested2bppSize);
    // wram->wRequested2bppSize = 4;
    CopyBytes(vram->vTiles2 + LEN_2BPP_TILE * 0x09, RustlingGrassPointers[(wram->wIntroSceneFrameCounter & 0xc) >> 2], 4 * LEN_2BPP_TILE);
    // RET;
}

// Useless function?
static void Intro_SetCGBPalUpdate(void){
    LD_A(TRUE);
    LDH_addr_A(hCGBPalUpdate);
    RET;
}

void Intro_ClearBGPals(void){
    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(MBANK(awBGPals2));
    LDH_addr_A(rSVBK);

    LD_HL(wBGPals2);
    LD_BC(16 * PALETTE_SIZE);
    XOR_A_A;
    CALL(aByteFill);

    POP_AF;
    LDH_addr_A(rSVBK);
    LD_A(TRUE);
    LDH_addr_A(hCGBPalUpdate);
    CALL(aDelayFrame);
    CALL(aDelayFrame);
    RET;

}

static void Intro_ClearBGPals_Conv(void){
    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    // LD_A(MBANK(awBGPals2));
    // LDH_addr_A(rSVBK);
    // wbank_push(MBANK(awBGPals2));

    // LD_HL(wBGPals2);
    // LD_BC(16 * PALETTE_SIZE);
    // XOR_A_A;
    // CALL(aByteFill);
    ByteFill(wram->wBGPals2, 16 * PALETTE_SIZE, 0);

    // POP_AF;
    // LDH_addr_A(rSVBK);
    // wbank_pop;
    // LD_A(TRUE);
    // LDH_addr_A(hCGBPalUpdate);
    hram->hCGBPalUpdate = TRUE;
    // CALL(aDelayFrame);
    // CALL(aDelayFrame);
    DelayFrames(2);
    // RET;
}

void Intro_DecompressRequest2bpp_128Tiles(void){
    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(MBANK(awDecompressScratch));
    LDH_addr_A(rSVBK);

    PUSH_DE;
    LD_DE(wDecompressScratch);
    CALL(aDecompress);
    POP_HL;

    LD_DE(wDecompressScratch);
    LD_BC((0x01 << 8) | 0x80);
    CALL(aRequest2bpp);

    POP_AF;
    LDH_addr_A(rSVBK);
    RET;

}

// static void Intro_DecompressRequest2bpp_128Tiles_Conv(uint16_t hl, uint16_t de) {
//     uint8_t svbk = gb_read(rSVBK);
//     gb_write(rSVBK, MBANK(awDecompressScratch));
//     Decompress_Conv(wDecompressScratch, hl);
//     Request2bpp_Conv(0x01, wDecompressScratch, de, 128);
//     gb_write(rSVBK, svbk);
// }

void Intro_DecompressRequest2bpp_255Tiles(void){
    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(MBANK(awDecompressScratch));
    LDH_addr_A(rSVBK);

    PUSH_DE;
    LD_DE(wDecompressScratch);
    CALL(aDecompress);
    POP_HL;

    LD_DE(wDecompressScratch);
    LD_BC((0x01 << 8) | 0xff);
    CALL(aRequest2bpp);

    POP_AF;
    LDH_addr_A(rSVBK);
    RET;

}

// Unused
// static void Intro_DecompressRequest2bpp_255Tiles_Conv(uint16_t hl, uint16_t de) {
//     uint8_t svbk = gb_read(rSVBK);
//     gb_write(rSVBK, MBANK(awDecompressScratch));
//     Decompress_Conv(wDecompressScratch, hl);
//     Request2bpp_Conv(0x01, wDecompressScratch, de, 255);
//     gb_write(rSVBK, svbk);
// }

void Intro_DecompressRequest2bpp_64Tiles(void){
    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(MBANK(awDecompressScratch));
    LDH_addr_A(rSVBK);

    PUSH_DE;
    LD_DE(wDecompressScratch);
    CALL(aDecompress);
    POP_HL;

    LD_DE(wDecompressScratch);
    LD_BC((0x01 << 8) | 0x40);
    CALL(aRequest2bpp);

    POP_AF;
    LDH_addr_A(rSVBK);
    RET;

}

// static void Intro_DecompressRequest2bpp_64Tiles_Conv(uint16_t hl, uint16_t de){
//     // LDH_A_addr(rSVBK);
//     // PUSH_AF;
//     // LD_A(MBANK(awDecompressScratch));
//     // LDH_addr_A(rSVBK);
//     uint8_t svbk = gb_read(rSVBK);
//     gb_write(rSVBK, MBANK(awDecompressScratch));

//     // PUSH_DE;
//     // LD_DE(wDecompressScratch);
//     // CALL(aDecompress);
//     // POP_HL;
//     Decompress_Conv(wDecompressScratch, hl);

//     // LD_DE(wDecompressScratch);
//     // LD_BC((0x01 << 8) | 0x40);
//     // CALL(aRequest2bpp);
//     Request2bpp_Conv(0x01, wDecompressScratch, de, 0x40);

//     // POP_AF;
//     // LDH_addr_A(rSVBK);
//     // RET;
//     gb_write(rSVBK, svbk);
// }

void Intro_ResetLYOverrides(void){
    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(MBANK(awLYOverrides));
    LDH_addr_A(rSVBK);

    LD_HL(wLYOverrides);
    LD_BC(wLYOverridesEnd - wLYOverrides);
    XOR_A_A;
    CALL(aByteFill);

    POP_AF;
    LDH_addr_A(rSVBK);
    LD_A(LOW(rSCX));
    LDH_addr_A(hLCDCPointer);
    RET;
}

static void Intro_ResetLYOverrides_Conv(void){
    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    // LD_A(MBANK(awLYOverrides));
    // LDH_addr_A(rSVBK);
    // uint8_t svbk = gb_read(rSVBK);
    // gb_write(rSVBK, MBANK(awLYOverrides));

    // LD_HL(wLYOverrides);
    // LD_BC(wLYOverridesEnd - wLYOverrides);
    // XOR_A_A;
    // CALL(aByteFill);
    ByteFill(wram->wLYOverrides, sizeof(wram->wLYOverrides), 0);

    // POP_AF;
    // LDH_addr_A(rSVBK);
    // gb_write(rSVBK, svbk);
    // LD_A(LOW(rSCX));
    // LDH_addr_A(hLCDCPointer);
    // RET;
    hram->hLCDCPointer = LOW(rSCX);
}

void Intro_PerspectiveScrollBG(void){
    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(MBANK(awLYOverrides));
    LDH_addr_A(rSVBK);
// Scroll the grass every frame.
// Scroll the trees every other frame and at half speed.
// This creates an illusion of perspective.
    LD_A_addr(wIntroSceneFrameCounter);
    AND_A(0x1);
    IF_Z goto skip;
// trees in the back
    LD_HL(wLYOverrides);
    LD_A_hl;
    INC_A;
    LD_BC(0x5f);
    CALL(aByteFill);

skip:
// grass in the front
    LD_HL(wLYOverrides + 0x5f);
    LD_A_hl;
    INC_A;
    INC_A;
    LD_BC(0x31);
    CALL(aByteFill);
    LD_A_addr(wLYOverrides + 0);
    LDH_addr_A(hSCX);
    POP_AF;
    LDH_addr_A(rSVBK);
    RET;

}

static void Intro_PerspectiveScrollBG_Conv(void){
    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    // uint8_t svbk = gb_read(rSVBK);
    // LD_A(MBANK(awLYOverrides));
    // LDH_addr_A(rSVBK);
    // gb_write(rSVBK, MBANK(awLYOverrides));
// Scroll the grass every frame.
// Scroll the trees every other frame and at half speed.
// This creates an illusion of perspective.
    // LD_A_addr(wIntroSceneFrameCounter);
    // AND_A(0x1);
    // IF_Z goto skip;
    if(wram->wIntroSceneFrameCounter & 1) {
    // trees in the back
        // LD_HL(wLYOverrides);
        // LD_A_hl;
        // INC_A;
        uint8_t a = wram->wLYOverrides[0] + 1;
        // LD_BC(0x5f);
        // CALL(aByteFill);
        ByteFill(wram->wLYOverrides, 0x5f, a);
    }

// grass in the front
    // LD_HL(wLYOverrides + 0x5f);
    // LD_A_hl;
    // INC_A;
    // INC_A;
    // LD_BC(0x31);
    // CALL(aByteFill);
    ByteFill(&wram->wLYOverrides[0x5f], 0x31, wram->wLYOverrides[0x5f] + 2);
    // LD_A_addr(wLYOverrides + 0);
    // LDH_addr_A(hSCX);
    hram->hSCX = wram->wLYOverrides[0];
    // POP_AF;
    // LDH_addr_A(rSVBK);
    // RET;
    // gb_write(rSVBK, svbk);
}
