#include "../../constants.h"
#include "intro.h"
#include "../../home/palettes.h"
#include "../../home/joypad.h"
#include "../../home/delay.h"

void CrystalIntro(void){
    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(MBANK(awGBCPalettes));
    LDH_addr_A(rSVBK);
    // LDH_A_addr(hInMenu);
    REG_A = hram->hInMenu;
    PUSH_AF;
    // LDH_A_addr(hVBlank);
    REG_A = hram->hVBlank;
    PUSH_AF;
    // CALL(aCrystalIntro_InitRAMAddrs);
    CrystalIntro_InitRAMAddrs();
    PEEK("");

// loop:
    while(1)
    {
        CALL(aJoyTextDelay);
        // JoyTextDelay_Conv();
        LDH_A_addr(hJoyLast);
        AND_A(BUTTONS);
        IF_NZ goto ShutOffMusic;
        LD_A_addr(wJumptableIndex);
        BIT_A(7);
        IF_NZ goto done;
        CALL(aIntroSceneJumper);
        FARCALL(aPlaySpriteAnimations);
        CALL(aDelayFrame);
        // DelayFrame();
        // JP(mCrystalIntro_loop);
    }


ShutOffMusic:
    LD_DE(MUSIC_NONE);
    CALL(aPlayMusic);


done:
    PEEK("");
    CALL(aClearBGPalettes);
    CALL(aClearSprites);
    CALL(aClearTilemap);
    // XOR_A_A;
    // LDH_addr_A(hSCX);
    // LDH_addr_A(hSCY);
    CHECK_HRAM_FLD(hSCX);
    hram->hSCX = 0;
    CHECK_HRAM_FLD(hSCY);
    hram->hSCY = 0;
    // LD_A(0x7);
    // LDH_addr_A(hWX);
    CHECK_HRAM_FLD(hWX);
    hram->hWX = 0x7;
    // LD_A(0x90);
    // LDH_addr_A(hWY);
    CHECK_HRAM_FLD(hWY);
    hram->hWY = 0x90;
    POP_AF;
    // LDH_addr_A(hVBlank);
    CHECK_HRAM_FLD(hVBlank);
    hram->hVBlank = REG_A;
    POP_AF;
    // LDH_addr_A(hInMenu);
    CHECK_HRAM_FLD(hInMenu);
    hram->hInMenu = REG_A;
    POP_AF;
    LDH_addr_A(rSVBK);
    RET;


InitRAMAddrs:
    XOR_A_A;
    LDH_addr_A(hVBlank);
    LD_A(0x1);
    LDH_addr_A(hInMenu);
    XOR_A_A;
    LDH_addr_A(hMapAnims);
    LD_addr_A(wJumptableIndex);
    RET;

}

void CrystalIntro_InitRAMAddrs(void){
    XOR_A_A;
    LDH_addr_A(hVBlank);
    // hram->hVBlank = 0;
    LD_A(0x1);
    LDH_addr_A(hInMenu);
    // hram->hInMenu = 0x1;
    XOR_A_A;
    LDH_addr_A(hMapAnims);
    // hram->hMapAnims = 0;
    REG_A = 0;
    LD_addr_A(wJumptableIndex);
    // RET;
}

void IntroSceneJumper(void){
    //jumptable ['IntroScenes', 'wJumptableIndex']
    //fast_jumptable(mIntroScenes, wJumptableIndex);
    switch(gb_read(wJumptableIndex)) {
        case 0:  CALL(aIntroScene1);  break;
        case 1:  CALL(aIntroScene2);  break;
        case 2:  CALL(aIntroScene3);  break;
        case 3:  CALL(aIntroScene4);  break;
        case 4:  CALL(aIntroScene5);  break;
        case 5:  CALL(aIntroScene6);  break;
        case 6:  CALL(aIntroScene7);  break;
        case 7:  CALL(aIntroScene8);  break;
        case 8:  CALL(aIntroScene9);  break;
        case 9:  CALL(aIntroScene10); break;
        case 10: CALL(aIntroScene11); break;
        case 11: CALL(aIntroScene12); break;
        case 12: CALL(aIntroScene13); break;
        case 13: CALL(aIntroScene14); break;
        case 14: CALL(aIntroScene15); break;
        case 15: CALL(aIntroScene16); break;
        case 16: CALL(aIntroScene17); break;
        case 17: CALL(aIntroScene18); break;
        case 18: CALL(aIntroScene19); break;
        case 19: CALL(aIntroScene20); break;
        case 20: CALL(aIntroScene21); break;
        case 21: CALL(aIntroScene22); break;
        case 22: CALL(aIntroScene23); break;
        case 23: CALL(aIntroScene24); break;
        case 24: CALL(aIntroScene25); break;
        case 25: CALL(aIntroScene26); break;
        case 26: CALL(aIntroScene27); break;
        case 27: CALL(aIntroScene28); break;
    }

    RET;
}

void IntroScenes(void){
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
    IntroScene1();
    IntroScene2();
    IntroScene3();
    IntroScene4();
    IntroScene5();
    IntroScene6();
    IntroScene7();
    IntroScene8();
    IntroScene9();
    IntroScene10();
    IntroScene11();
    IntroScene12();
    IntroScene13();
    IntroScene14();
    IntroScene15();
    IntroScene16();
    IntroScene17();
    IntroScene18();
    IntroScene19();
    IntroScene20();
    IntroScene21();
    IntroScene22();
    IntroScene23();
    IntroScene24();
    IntroScene25();
    IntroScene26();
    IntroScene27();
    IntroScene28();

    RET;
}

void NextIntroScene(void){
    LD_HL(wJumptableIndex);
    INC_hl;
    // gb_write(wJumptableIndex, gb_read(wJumptableIndex) + 1);
    RET;

}

void IntroScene1(void){
//  Setup the next scene.
    CALL(aIntro_ClearBGPals);
    CALL(aClearSprites);
    CALL(aClearTilemap);
    XOR_A_A;
    LDH_addr_A(hBGMapMode);
    LD_A(0x1);
    LDH_addr_A(rVBK);
    LD_HL(mIntroUnownAAttrmap);
    debgcoord(0, 0, vBGMap0);
    CALL(aIntro_DecompressRequest2bpp_64Tiles);
    LD_A(0x0);
    LDH_addr_A(rVBK);
    LD_HL(mIntroUnownsGFX);
    LD_DE(vTiles2 + LEN_2BPP_TILE * 0x00);
    CALL(aIntro_DecompressRequest2bpp_128Tiles);
    LD_HL(mIntroPulseGFX);
    LD_DE(vTiles0 + LEN_2BPP_TILE * 0x00);
    CALL(aIntro_DecompressRequest2bpp_128Tiles);
    LD_HL(mIntroUnownATilemap);
    debgcoord(0, 0, vBGMap0);
    CALL(aIntro_DecompressRequest2bpp_64Tiles);
    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(MBANK(awBGPals1));
    LDH_addr_A(rSVBK);
    LD_HL(mIntroUnownsPalette);
    LD_DE(wBGPals1);
    LD_BC(16 * PALETTE_SIZE);
    CALL(aCopyBytes);
    LD_HL(mIntroUnownsPalette);
    LD_DE(wBGPals2);
    LD_BC(16 * PALETTE_SIZE);
    CALL(aCopyBytes);
    POP_AF;
    LDH_addr_A(rSVBK);
    XOR_A_A;
    LDH_addr_A(hSCX);
    LDH_addr_A(hSCY);
    LD_A(0x7);
    LDH_addr_A(hWX);
    LD_A(0x90);
    LDH_addr_A(hWY);
    FARCALL(aClearSpriteAnims);
    CALL(aIntro_SetCGBPalUpdate);
    XOR_A_A;
    LD_addr_A(wIntroSceneFrameCounter);
    LD_addr_A(wIntroSceneTimer);
    CALL(aNextIntroScene);
    RET;

}

void IntroScene2(void){
//  First Unown (A) fades in, pulses, then fades out.
    LD_HL(wIntroSceneFrameCounter);
    LD_A_hl;
    INC_hl;
    CP_A(0x80);
    IF_NC goto endscene;
    CP_A(0x60);
    IF_NZ goto nosound;
    PUSH_AF;
    //depixel ['11', '11']
    depixel2(11, 11);
    CALL(aCrystalIntro_InitUnownAnim);
    LD_DE(SFX_INTRO_UNOWN_1);
    CALL(aPlaySFX);
    POP_AF;

nosound:
    LD_addr_A(wIntroSceneTimer);
    XOR_A_A;
    CALL(aCrystalIntro_UnownFade);
    RET;

endscene:
    CALL(aNextIntroScene);
    RET;
    // return;

}

void IntroScene3(void){
//  More setup. Transition to the outdoor scene.
    CALL(aIntro_ClearBGPals);
    CALL(aClearSprites);
    CALL(aClearTilemap);
    XOR_A_A;
    LDH_addr_A(hBGMapMode);
    LD_A(0x1);
    LDH_addr_A(rVBK);
    LD_HL(mIntroBackgroundAttrmap);
    debgcoord(0, 0, vBGMap0);
    CALL(aIntro_DecompressRequest2bpp_64Tiles);
    LD_A(0x0);
    LDH_addr_A(rVBK);
    LD_HL(mIntroBackgroundGFX);
    LD_DE(vTiles2 + LEN_2BPP_TILE * 0x00);
    CALL(aIntro_DecompressRequest2bpp_128Tiles);
    LD_HL(mIntroBackgroundTilemap);
    debgcoord(0, 0, vBGMap0);
    CALL(aIntro_DecompressRequest2bpp_64Tiles);
    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(MBANK(awBGPals1));
    LDH_addr_A(rSVBK);
    LD_HL(mIntroBackgroundPalette);
    LD_DE(wBGPals1);
    LD_BC(16 * PALETTE_SIZE);
    CALL(aCopyBytes);
    LD_HL(mIntroBackgroundPalette);
    LD_DE(wBGPals2);
    LD_BC(16 * PALETTE_SIZE);
    CALL(aCopyBytes);
    POP_AF;
    LDH_addr_A(rSVBK);
    XOR_A_A;
    LDH_addr_A(hSCX);
    LDH_addr_A(hSCY);
    LD_A(0x7);
    LDH_addr_A(hWX);
    LD_A(0x90);
    LDH_addr_A(hWY);
    CALL(aIntro_ResetLYOverrides);
    CALL(aIntro_SetCGBPalUpdate);
    XOR_A_A;
    LD_addr_A(wIntroSceneFrameCounter);
    CALL(aNextIntroScene);
    RET;
    // return;

}

void IntroScene4(void){
//  Scroll the outdoor panorama for a bit.
    CALL(aIntro_PerspectiveScrollBG);
    LD_HL(wIntroSceneFrameCounter);
    LD_A_hl;
    CP_A(0x80);
    IF_Z goto endscene;
    INC_hl;
    RET;


endscene:
    // return;
    CALL(aNextIntroScene);
    RET;

}

void IntroScene5(void){
//  Go back to the Unown.
    CALL(aIntro_ClearBGPals);
    CALL(aClearSprites);
    CALL(aClearTilemap);
    XOR_A_A;
    LDH_addr_A(hBGMapMode);
    LDH_addr_A(hLCDCPointer);
    LD_A(0x1);
    LDH_addr_A(rVBK);
    LD_HL(mIntroUnownHIAttrmap);
    debgcoord(0, 0, vBGMap0);
    CALL(aIntro_DecompressRequest2bpp_64Tiles);
    LD_A(0x0);
    LDH_addr_A(rVBK);
    LD_HL(mIntroUnownsGFX);
    LD_DE(vTiles2 + LEN_2BPP_TILE * 0x00);
    CALL(aIntro_DecompressRequest2bpp_128Tiles);
    LD_HL(mIntroPulseGFX);
    LD_DE(vTiles0 + LEN_2BPP_TILE * 0x00);
    CALL(aIntro_DecompressRequest2bpp_128Tiles);
    LD_HL(mIntroUnownHITilemap);
    debgcoord(0, 0, vBGMap0);
    CALL(aIntro_DecompressRequest2bpp_64Tiles);
    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(MBANK(awBGPals1));
    LDH_addr_A(rSVBK);
    LD_HL(mIntroUnownsPalette);
    LD_DE(wBGPals1);
    LD_BC(16 * PALETTE_SIZE);
    CALL(aCopyBytes);
    LD_HL(mIntroUnownsPalette);
    LD_DE(wBGPals2);
    LD_BC(16 * PALETTE_SIZE);
    CALL(aCopyBytes);
    POP_AF;
    LDH_addr_A(rSVBK);
    XOR_A_A;
    LDH_addr_A(hSCX);
    LDH_addr_A(hSCY);
    LD_A(0x7);
    LDH_addr_A(hWX);
    LD_A(0x90);
    LDH_addr_A(hWY);
    FARCALL(aClearSpriteAnims);
    CALL(aIntro_SetCGBPalUpdate);
    XOR_A_A;
    LD_addr_A(wIntroSceneFrameCounter);
    LD_addr_A(wIntroSceneTimer);
    CALL(aNextIntroScene);
    RET;
    // return;

}

void IntroScene6(void){
//  Two more Unown (I, H) fade in.
    LD_HL(wIntroSceneFrameCounter);
    LD_A_hl;
    INC_hl;
    CP_A(0x80);
    IF_NC goto endscene;
    CP_A(0x60);
    IF_Z goto SecondUnown;
    CP_A(0x40);
    IF_NC goto StopUnown;
    CP_A(0x20);
    IF_Z goto FirstUnown;
    goto NoUnown;


FirstUnown:
    PUSH_AF;
    //depixel ['7', '15']
    depixel2(7, 15);
    CALL(aCrystalIntro_InitUnownAnim);
    LD_DE(SFX_INTRO_UNOWN_2);
    CALL(aPlaySFX);
    POP_AF;

NoUnown:
    LD_addr_A(wIntroSceneTimer);
    XOR_A_A;
    CALL(aCrystalIntro_UnownFade);
    RET;


SecondUnown:
    PUSH_AF;
    //depixel ['14', '6']
    depixel2(14, 6);
    CALL(aCrystalIntro_InitUnownAnim);
    LD_DE(SFX_INTRO_UNOWN_1);
    CALL(aPlaySFX);
    POP_AF;

StopUnown:
    LD_addr_A(wIntroSceneTimer);
    LD_A(0x1);
    CALL(aCrystalIntro_UnownFade);
    RET;


endscene:
    CALL(aNextIntroScene);
    RET;
    // return;

}

void IntroScene7(void){
//  Back to the outdoor scene.
    CALL(aIntro_ClearBGPals);
    CALL(aClearSprites);
    CALL(aClearTilemap);
    XOR_A_A;
    LDH_addr_A(hBGMapMode);

    LD_A(0x1);
    LDH_addr_A(rVBK);
    LD_HL(mIntroBackgroundAttrmap);
    debgcoord(0, 0, vBGMap0);
    CALL(aIntro_DecompressRequest2bpp_64Tiles);

    LD_HL(mIntroPichuWooperGFX);
    LD_DE(vTiles0 + LEN_2BPP_TILE * 0x00);
    CALL(aIntro_DecompressRequest2bpp_128Tiles);

    LD_A(0x0);
    LDH_addr_A(rVBK);
    LD_HL(mIntroSuicuneRunGFX);
    LD_DE(vTiles0 + LEN_2BPP_TILE * 0x00);
    CALL(aIntro_DecompressRequest2bpp_255Tiles);

    LD_HL(mIntroBackgroundGFX);
    LD_DE(vTiles2 + LEN_2BPP_TILE * 0x00);
    CALL(aIntro_DecompressRequest2bpp_128Tiles);

    LD_HL(mIntroBackgroundTilemap);
    debgcoord(0, 0, vBGMap0);
    CALL(aIntro_DecompressRequest2bpp_64Tiles);

    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(MBANK(awBGPals1));
    LDH_addr_A(rSVBK);

    LD_HL(mIntroBackgroundPalette);
    LD_DE(wBGPals1);
    LD_BC(16 * PALETTE_SIZE);
    CALL(aCopyBytes);

    LD_HL(mIntroBackgroundPalette);
    LD_DE(wBGPals2);
    LD_BC(16 * PALETTE_SIZE);
    CALL(aCopyBytes);

    POP_AF;
    LDH_addr_A(rSVBK);

    XOR_A_A;
    LDH_addr_A(hSCX);
    LDH_addr_A(hSCY);
    LD_A(0x7);
    LDH_addr_A(hWX);
    LD_A(0x90);
    LDH_addr_A(hWY);
    CALL(aIntro_ResetLYOverrides);
    FARCALL(aClearSpriteAnims);
    //depixel ['13', '27', '4', '0']
    depixel4(13, 27, 4, 0);
    LD_A(SPRITE_ANIM_INDEX_INTRO_SUICUNE);
    CALL(aInitSpriteAnimStruct);
    LD_A(0xf0);
    LD_addr_A(wGlobalAnimXOffset);
    CALL(aIntro_SetCGBPalUpdate);
    XOR_A_A;
    LD_addr_A(wIntroSceneFrameCounter);
    LD_addr_A(wIntroSceneTimer);
    CALL(aNextIntroScene);
    RET;
    // return;

}

void IntroScene8(void){
//  Scroll the scene, then show Suicune running across the screen.
    LD_HL(wIntroSceneFrameCounter);
    LD_A_hl;
    INC_hl;
    CP_A(0x40);
    IF_Z goto suicune_sound;
    IF_NC goto animate_suicune;
    CALL(aIntro_PerspectiveScrollBG);
    // return;
    RET;


suicune_sound:
    LD_DE(SFX_INTRO_SUICUNE_3);
    CALL(aPlaySFX);

animate_suicune:
    LD_A_addr(wGlobalAnimXOffset);
    AND_A_A;
    IF_Z goto finish;
    SUB_A(0x8);
    LD_addr_A(wGlobalAnimXOffset);
    // return;
    RET;


finish:
    LD_DE(SFX_INTRO_SUICUNE_2);
    CALL(aPlaySFX);
    FARCALL(aDeinitializeAllSprites);
    CALL(aNextIntroScene);
    RET;
    // return;

}

void IntroScene9(void){
//  Set up the next scene (same bg).
    XOR_A_A;
    LDH_addr_A(hLCDCPointer);
    CALL(aClearSprites);
    hlcoord(0, 0, wAttrmap);
// first 12 rows have palette 1
    LD_BC(12 * SCREEN_WIDTH);
    LD_A(0x1);
    CALL(aByteFill);
// middle 3 rows have palette 2
    LD_BC(3 * SCREEN_WIDTH);
    LD_A(0x2);
    CALL(aByteFill);
// last three rows have palette 3
    LD_BC(3 * SCREEN_WIDTH);
    LD_A(0x3);
    CALL(aByteFill);
    LD_A(0x2);
    LDH_addr_A(hBGMapMode);
    CALL(aDelayFrame);
    CALL(aDelayFrame);
    CALL(aDelayFrame);
    LD_A(LOW(vBGMap0 + 0xc));  // $c
    LDH_addr_A(hBGMapAddress);
    CALL(aDelayFrame);
    CALL(aDelayFrame);
    CALL(aDelayFrame);
    XOR_A_A;
    LDH_addr_A(hBGMapMode);
    LDH_addr_A(hBGMapAddress);
    LD_addr_A(wGlobalAnimXOffset);
    XOR_A_A;
    LD_addr_A(wIntroSceneFrameCounter);
    CALL(aNextIntroScene);
    RET;
    // return;

}

void IntroScene10(void){
//  Wooper and Pichu enter.
    CALL(aIntro_RustleGrass);
    LD_HL(wIntroSceneFrameCounter);
    LD_A_hl;
    INC_hl;
    CP_A(0xc0);
    IF_Z goto done;
    CP_A(0x20);
    IF_Z goto wooper;
    CP_A(0x40);
    IF_Z goto pichu;
    // return;
    RET;


pichu:
    //depixel ['21', '16', '1', '0']
    depixel4(21, 16, 1, 0);
    LD_A(SPRITE_ANIM_INDEX_INTRO_PICHU);
    CALL(aInitSpriteAnimStruct);
    LD_DE(SFX_INTRO_PICHU);
    CALL(aPlaySFX);
    // return;
    RET;


wooper:
    //depixel ['22', '6']
    depixel2(22, 6);
    LD_A(SPRITE_ANIM_INDEX_INTRO_WOOPER);
    CALL(aInitSpriteAnimStruct);
    LD_DE(SFX_INTRO_PICHU);
    CALL(aPlaySFX);
    // return;
    RET;

done:
    CALL(aNextIntroScene);
    RET;
    // return;

}

void IntroScene11(void){
//  Back to Unown again.
    CALL(aIntro_ClearBGPals);
    CALL(aClearSprites);
    CALL(aClearTilemap);
    XOR_A_A;
    LDH_addr_A(hBGMapMode);
    LDH_addr_A(hLCDCPointer);
    LD_A(0x1);
    LDH_addr_A(rVBK);
    LD_HL(mIntroUnownsAttrmap);
    debgcoord(0, 0, vBGMap0);
    CALL(aIntro_DecompressRequest2bpp_64Tiles);
    LD_A(0x0);
    LDH_addr_A(rVBK);
    LD_HL(mIntroUnownsGFX);
    LD_DE(vTiles2 + LEN_2BPP_TILE * 0x00);
    CALL(aIntro_DecompressRequest2bpp_128Tiles);
    LD_HL(mIntroUnownsTilemap);
    debgcoord(0, 0, vBGMap0);
    CALL(aIntro_DecompressRequest2bpp_64Tiles);
    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(MBANK(awBGPals1));
    LDH_addr_A(rSVBK);
    LD_HL(mIntroUnownsPalette);
    LD_DE(wBGPals1);
    LD_BC(16 * PALETTE_SIZE);
    CALL(aCopyBytes);
    LD_HL(mIntroUnownsPalette);
    LD_DE(wBGPals2);
    LD_BC(16 * PALETTE_SIZE);
    CALL(aCopyBytes);
    POP_AF;
    LDH_addr_A(rSVBK);
    XOR_A_A;
    LDH_addr_A(hSCX);
    LDH_addr_A(hSCY);
    LD_A(0x7);
    LDH_addr_A(hWX);
    LD_A(0x90);
    LDH_addr_A(hWY);
    FARCALL(aClearSpriteAnims);
    CALL(aIntro_SetCGBPalUpdate);
    XOR_A_A;
    LD_addr_A(wIntroSceneFrameCounter);
    LD_addr_A(wIntroSceneTimer);
    CALL(aNextIntroScene);
    RET;
    // return;

}

void IntroScene12(void){
//  Even more Unown.
    CALL(aIntroScene12_PlayUnownSound);
    LD_HL(wIntroSceneFrameCounter);
    LD_A_hl;
    INC_hl;
    CP_A(0xc0);
    IF_NC goto done;
    CP_A(0x80);
    IF_NC goto second_half;
//  first half
    LD_C_A;
    AND_A(0x1f);
    SLA_A;
    LD_addr_A(wIntroSceneTimer);
    LD_A_C;
    AND_A(0xe0);
    SRL_A;
    SWAP_A;
    CALL(aCrystalIntro_UnownFade);
    RET;


second_half:
//  double speed
    LD_C_A;
    AND_A(0xf);
    SLA_A;
    SLA_A;
    LD_addr_A(wIntroSceneTimer);
    LD_A_C;
    AND_A(0x70);
    OR_A(0x40);
    SWAP_A;
    CALL(aCrystalIntro_UnownFade);
    RET;


done:
    CALL(aNextIntroScene);
    RET;
    // return;


PlayUnownSound:
    LD_A_addr(wIntroSceneFrameCounter);
    LD_C_A;
    LD_HL(mIntroScene12_UnownSounds);

loop:
    LD_A_hli;
    CP_A(-1);
    RET_Z ;
    CP_A_C;
    IF_Z goto playsound;
    INC_HL;
    INC_HL;
    goto loop;

playsound:
    LD_A_hli;
    LD_D_hl;
    LD_E_A;
    PUSH_DE;
    CALL(aSFXChannelsOff);
    POP_DE;
    CALL(aPlaySFX);
    RET;


UnownSounds:
    //dbw ['0x00', 'SFX_INTRO_UNOWN_3']
    //dbw ['0x20', 'SFX_INTRO_UNOWN_2']
    //dbw ['0x40', 'SFX_INTRO_UNOWN_1']
    //dbw ['0x60', 'SFX_INTRO_UNOWN_2']
    //dbw ['0x80', 'SFX_INTRO_UNOWN_3']
    //dbw ['0x90', 'SFX_INTRO_UNOWN_2']
    //dbw ['0xa0', 'SFX_INTRO_UNOWN_1']
    //dbw ['0xb0', 'SFX_INTRO_UNOWN_2']
    //db ['-1'];

    return IntroScene13();
}

void IntroScene13(void){
//  Switch scenes again.
    CALL(aIntro_ClearBGPals);
    CALL(aClearSprites);
    CALL(aClearTilemap);
    XOR_A_A;
    LDH_addr_A(hBGMapMode);
    LD_A(0x1);
    LDH_addr_A(rVBK);
    LD_HL(mIntroBackgroundAttrmap);
    debgcoord(0, 0, vBGMap0);
    CALL(aIntro_DecompressRequest2bpp_64Tiles);
    LD_A(0x0);
    LDH_addr_A(rVBK);
    LD_HL(mIntroSuicuneRunGFX);
    LD_DE(vTiles0 + LEN_2BPP_TILE * 0x00);
    CALL(aIntro_DecompressRequest2bpp_255Tiles);
    LD_HL(mIntroBackgroundGFX);
    LD_DE(vTiles2 + LEN_2BPP_TILE * 0x00);
    CALL(aIntro_DecompressRequest2bpp_128Tiles);
    LD_HL(mIntroBackgroundTilemap);
    debgcoord(0, 0, vBGMap0);
    CALL(aIntro_DecompressRequest2bpp_64Tiles);
    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(MBANK(awBGPals1));
    LDH_addr_A(rSVBK);
    LD_HL(mIntroBackgroundPalette);
    LD_DE(wBGPals1);
    LD_BC(16 * PALETTE_SIZE);
    CALL(aCopyBytes);
    LD_HL(mIntroBackgroundPalette);
    LD_DE(wBGPals2);
    LD_BC(16 * PALETTE_SIZE);
    CALL(aCopyBytes);
    POP_AF;
    LDH_addr_A(rSVBK);
    XOR_A_A;
    LDH_addr_A(hSCX);
    LDH_addr_A(hSCY);
    LD_A(0x7);
    LDH_addr_A(hWX);
    LD_A(0x90);
    LDH_addr_A(hWY);
    FARCALL(aClearSpriteAnims);
    //depixel ['13', '11', '4', '0']
    depixel4(13, 11, 4, 0);
    LD_A(SPRITE_ANIM_INDEX_INTRO_SUICUNE);
    CALL(aInitSpriteAnimStruct);
    LD_DE(MUSIC_CRYSTAL_OPENING);
    CALL(aPlayMusic);
    XOR_A_A;
    LD_addr_A(wGlobalAnimXOffset);
    CALL(aIntro_SetCGBPalUpdate);
    XOR_A_A;
    LD_addr_A(wIntroSceneFrameCounter);
    LD_addr_A(wIntroSceneTimer);
    CALL(aNextIntroScene);
    RET;
    // return;

}

void IntroScene14(void){
//  Suicune runs then jumps.
    LDH_A_addr(hSCX);
    SUB_A(10);
    LDH_addr_A(hSCX);
    LD_HL(wIntroSceneFrameCounter);
    LD_A_hl;
    INC_hl;
    CP_A(0x80);
    IF_Z goto done;
    CP_A(0x60);
    IF_Z goto jump;
    IF_NC goto run_after_jump;
    CP_A(0x40);
    IF_NC goto run;
    RET;


jump:
    LD_DE(SFX_INTRO_SUICUNE_4);
    CALL(aPlaySFX);


run_after_jump:
    LD_A(0x1);
    LD_addr_A(wIntroSceneTimer);
    LD_A_addr(wGlobalAnimXOffset);
    CP_A(0x88);
    IF_C goto disappear;
    SUB_A(0x8);
    LD_addr_A(wGlobalAnimXOffset);
    RET;


disappear:
    FARCALL(aDeinitializeAllSprites);
    RET;


run:
    LD_A_addr(wGlobalAnimXOffset);
    SUB_A(0x2);
    LD_addr_A(wGlobalAnimXOffset);
    RET;


done:
    CALL(aNextIntroScene);
    RET;
    // return;

}

void IntroScene15(void){
//  Transition to a new scene.
    CALL(aIntro_ClearBGPals);
    CALL(aClearSprites);
    CALL(aClearTilemap);
    XOR_A_A;
    LDH_addr_A(hBGMapMode);
    LD_A(0x1);
    LDH_addr_A(rVBK);
    LD_HL(mIntroSuicuneJumpAttrmap);
    debgcoord(0, 0, vBGMap0);
    CALL(aIntro_DecompressRequest2bpp_64Tiles);
    LD_A(0x0);
    LDH_addr_A(rVBK);
    LD_HL(mIntroSuicuneJumpGFX);
    LD_DE(vTiles2 + LEN_2BPP_TILE * 0x00);
    CALL(aIntro_DecompressRequest2bpp_128Tiles);
    LD_HL(mIntroUnownBackGFX);
    LD_DE(vTiles0 + LEN_2BPP_TILE * 0x00);
    CALL(aIntro_DecompressRequest2bpp_128Tiles);
    LD_DE(mIntroGrass4GFX);
    LD_HL(vTiles1 + LEN_2BPP_TILE * 0x00);
    LD_BC((BANK(aIntroGrass4GFX) << 8) | 1);
    CALL(aRequest2bpp);
    LD_HL(mIntroSuicuneJumpTilemap);
    debgcoord(0, 0, vBGMap0);
    CALL(aIntro_DecompressRequest2bpp_64Tiles);
    CALL(aIntro_LoadTilemap);
    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(MBANK(awBGPals1));
    LDH_addr_A(rSVBK);
    LD_HL(mIntroSuicunePalette);
    LD_DE(wBGPals1);
    LD_BC(16 * PALETTE_SIZE);
    CALL(aCopyBytes);
    LD_HL(mIntroSuicunePalette);
    LD_DE(wBGPals2);
    LD_BC(16 * PALETTE_SIZE);
    CALL(aCopyBytes);
    POP_AF;
    LDH_addr_A(rSVBK);
    XOR_A_A;
    LDH_addr_A(hSCX);
    LD_A(0x90);
    LDH_addr_A(hSCY);
    LD_A(0x7);
    LDH_addr_A(hWX);
    LD_A(0x90);
    LDH_addr_A(hWY);
    FARCALL(aClearSpriteAnims);
    CALL(aIntro_SetCGBPalUpdate);
    //depixel ['8', '5']
    depixel2(8, 5);
    LD_A(SPRITE_ANIM_INDEX_INTRO_UNOWN_F);
    CALL(aInitSpriteAnimStruct);
    //depixel ['12', '0']
    depixel2(12, 0);
    LD_A(SPRITE_ANIM_INDEX_INTRO_SUICUNE_AWAY);
    CALL(aInitSpriteAnimStruct);
    XOR_A_A;
    LD_addr_A(wIntroSceneFrameCounter);
    LD_addr_A(wIntroSceneTimer);
    CALL(aNextIntroScene);
    RET;
    // return;

}

void IntroScene16(void){
//  Suicune shows its face. An Unown appears in front.
    LD_HL(wIntroSceneFrameCounter);
    LD_A_hl;
    INC_hl;
    CP_A(0x80);
    IF_NC goto done;
    CALL(aIntro_Scene16_AnimateSuicune);
    LDH_A_addr(hSCY);
    AND_A_A;
    RET_Z ;
    ADD_A(8);
    LDH_addr_A(hSCY);
    RET;

done:
    CALL(aNextIntroScene);
    RET;
    // return;

}

void IntroScene17(void){
//  ...
    CALL(aIntro_ClearBGPals);
    CALL(aClearSprites);
    CALL(aClearTilemap);
    XOR_A_A;
    LDH_addr_A(hBGMapMode);
    LD_A(0x1);
    LDH_addr_A(rVBK);
    LD_HL(mIntroSuicuneCloseAttrmap);
    debgcoord(0, 0, vBGMap0);
    CALL(aIntro_DecompressRequest2bpp_64Tiles);
    LD_A(0x0);
    LDH_addr_A(rVBK);
    LD_HL(mIntroSuicuneCloseGFX);
    LD_DE(vTiles1 + LEN_2BPP_TILE * 0x00);
    CALL(aIntro_DecompressRequest2bpp_255Tiles);
    LD_HL(mIntroSuicuneCloseTilemap);
    debgcoord(0, 0, vBGMap0);
    CALL(aIntro_DecompressRequest2bpp_64Tiles);
    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(MBANK(awBGPals1));
    LDH_addr_A(rSVBK);
    LD_HL(mIntroSuicuneClosePalette);
    LD_DE(wBGPals1);
    LD_BC(16 * PALETTE_SIZE);
    CALL(aCopyBytes);
    LD_HL(mIntroSuicuneClosePalette);
    LD_DE(wBGPals2);
    LD_BC(16 * PALETTE_SIZE);
    CALL(aCopyBytes);
    POP_AF;
    LDH_addr_A(rSVBK);
    XOR_A_A;
    LDH_addr_A(hSCX);
    LDH_addr_A(hSCY);
    LD_A(0x7);
    LDH_addr_A(hWX);
    LD_A(0x90);
    LDH_addr_A(hWY);
    FARCALL(aClearSpriteAnims);
    CALL(aIntro_SetCGBPalUpdate);
    XOR_A_A;
    LD_addr_A(wIntroSceneFrameCounter);
    LD_addr_A(wIntroSceneTimer);
    CALL(aNextIntroScene);
    RET;
    // return;

}

void IntroScene18(void){
//  Suicune close up.
    LD_HL(wIntroSceneFrameCounter);
    LD_A_hl;
    INC_hl;
    CP_A(0x60);
    IF_NC goto done;
    LDH_A_addr(hSCX);
    CP_A(0x60);
    RET_Z ;
    ADD_A(8);
    LDH_addr_A(hSCX);
    RET;

done:
    CALL(aNextIntroScene);
    RET;
    // return;

}

void IntroScene19(void){
//  More setup.
    CALL(aIntro_ClearBGPals);
    CALL(aClearSprites);
    CALL(aClearTilemap);
    XOR_A_A;
    LDH_addr_A(hBGMapMode);
    LD_A(0x1);
    LDH_addr_A(rVBK);
    LD_HL(mIntroSuicuneBackAttrmap);
    debgcoord(0, 0, vBGMap0);
    CALL(aIntro_DecompressRequest2bpp_64Tiles);
    LD_A(0x0);
    LDH_addr_A(rVBK);
    LD_HL(mIntroSuicuneBackGFX);
    LD_DE(vTiles2 + LEN_2BPP_TILE * 0x00);
    CALL(aIntro_DecompressRequest2bpp_128Tiles);
    LD_HL(mIntroUnownsGFX);
    LD_DE(vTiles1 + LEN_2BPP_TILE * 0x00);
    CALL(aIntro_DecompressRequest2bpp_128Tiles);
    LD_DE(mIntroGrass4GFX);
    LD_HL(vTiles1 + LEN_2BPP_TILE * 0x7f);
    LD_BC((BANK(aIntroGrass4GFX) << 8) | 1);
    CALL(aRequest2bpp);
    LD_HL(mIntroSuicuneBackTilemap);
    debgcoord(0, 0, vBGMap0);
    CALL(aIntro_DecompressRequest2bpp_64Tiles);
    CALL(aIntro_LoadTilemap);
    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(MBANK(awBGPals1));
    LDH_addr_A(rSVBK);
    LD_HL(mIntroSuicunePalette);
    LD_DE(wBGPals1);
    LD_BC(16 * PALETTE_SIZE);
    CALL(aCopyBytes);
    LD_HL(mIntroSuicunePalette);
    LD_DE(wBGPals2);
    LD_BC(16 * PALETTE_SIZE);
    CALL(aCopyBytes);
    POP_AF;
    LDH_addr_A(rSVBK);
    XOR_A_A;
    LDH_addr_A(hSCX);
    LD_A(0xd8);
    LDH_addr_A(hSCY);
    LD_A(0x7);
    LDH_addr_A(hWX);
    LD_A(0x90);
    LDH_addr_A(hWY);
    FARCALL(aClearSpriteAnims);
    LD_HL(wSpriteAnimDict);
    XOR_A_A;  // SPRITE_ANIM_DICT_DEFAULT
    LD_hli_A;
    LD_hl(0x7f);
    CALL(aIntro_SetCGBPalUpdate);
    //depixel ['12', '0']
    depixel2(12, 0);
    LD_A(SPRITE_ANIM_INDEX_INTRO_SUICUNE_AWAY);
    CALL(aInitSpriteAnimStruct);
    XOR_A_A;
    LD_addr_A(wIntroSceneFrameCounter);
    LD_addr_A(wIntroSceneTimer);
    CALL(aNextIntroScene);
    RET;
    // return;

}

void IntroScene20(void){
//  Suicune running away. A bunch of Unown appear.
    LD_HL(wIntroSceneFrameCounter);
    LD_A_hl;
    INC_hl;
    CP_A(0x98);
    IF_NC goto finished;
    CP_A(0x58);
    // RET_NC ;
    CP_A(0x40);
    IF_NC goto AppearUnown;
    CP_A(0x28);
    RET_NC ;
    LDH_A_addr(hSCY);
    INC_A;
    LDH_addr_A(hSCY);
    RET;


AppearUnown:
    SUB_A(0x18);
    LD_C_A;
    AND_A(0x3);
    CP_A(0x3);
    RET_NZ ;
    LD_A_C;
    AND_A(0x1c);
    SRL_A;
    SRL_A;
    LD_addr_A(wIntroSceneTimer);
    XOR_A_A;
    CALL(aIntro_Scene20_AppearUnown);
    RET;


AppearUnownPal2:
//   //  unreferenced
    LD_A_C;
    AND_A(0x1c);
    SRL_A;
    SRL_A;
    LD_addr_A(wIntroSceneTimer);
    LD_A(1);
    CALL(aIntro_Scene20_AppearUnown);
    RET;


finished:
    CALL(aNextIntroScene);
    RET;
    // return;

}

void IntroScene21(void){
//  Suicune gets more distant and turns black.
    CALL(aIntro_ColoredSuicuneFrameSwap);
    LD_C(3);
    CALL(aDelayFrames);
    XOR_A_A;
    LDH_addr_A(hBGMapMode);
    LD_addr_A(wIntroSceneFrameCounter);
    LD_addr_A(wIntroSceneTimer);
    CALL(aNextIntroScene);
    RET;
    // return;

}

void IntroScene22(void){
    LD_HL(wIntroSceneFrameCounter);
    LD_A_hl;
    INC_hl;
    CP_A(0x8);
    IF_NC goto done;
    RET;

done:
    FARCALL(aDeinitializeAllSprites);
    CALL(aNextIntroScene);
    RET;
    // return;

}

void IntroScene23(void){
    XOR_A_A;
    LD_addr_A(wIntroSceneFrameCounter);
    CALL(aNextIntroScene);
    RET;
    // return;

}

void IntroScene24(void){
//  Fade to white.
    LD_HL(wIntroSceneFrameCounter);
    LD_A_hl;
    INC_hl;
    CP_A(0x20);
    IF_NC goto done;

    LD_C_A;
    AND_A(0x3);
    RET_NZ ;

    LD_A_C;
    AND_A(0x1c);
    SLA_A;
    CALL(aIntro_Scene24_ApplyPaletteFade);
    RET;


done:
    LD_A(0x40);
    LD_addr_A(wIntroSceneFrameCounter);
    CALL(aNextIntroScene);
    RET;
    // return;

}

void IntroScene25(void){
//  Wait around a bit.
    LD_A_addr(wIntroSceneFrameCounter);
    DEC_A;
    IF_Z goto done;
    LD_addr_A(wIntroSceneFrameCounter);
    RET;


done:
    CALL(aNextIntroScene);
    RET;
    // return;

}

void IntroScene26(void){
//  Load the final scene.
    CALL(aClearBGPalettes);
    CALL(aClearSprites);
    CALL(aClearTilemap);
    XOR_A_A;
    LDH_addr_A(hBGMapMode);
    LD_A(0x1);
    LDH_addr_A(rVBK);
    LD_HL(mIntroCrystalUnownsAttrmap);
    debgcoord(0, 0, vBGMap0);
    CALL(aIntro_DecompressRequest2bpp_64Tiles);
    LD_A(0x0);
    LDH_addr_A(rVBK);
    LD_HL(mIntroCrystalUnownsGFX);
    LD_DE(vTiles2 + LEN_2BPP_TILE * 0x00);
    CALL(aIntro_DecompressRequest2bpp_128Tiles);
    LD_HL(mIntroCrystalUnownsTilemap);
    debgcoord(0, 0, vBGMap0);
    CALL(aIntro_DecompressRequest2bpp_64Tiles);
    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(MBANK(awBGPals1));
    LDH_addr_A(rSVBK);
    LD_HL(mIntroCrystalUnownsPalette);
    LD_DE(wBGPals1);
    LD_BC(16 * PALETTE_SIZE);
    CALL(aCopyBytes);
    LD_HL(mIntroCrystalUnownsPalette);
    LD_DE(wBGPals2);
    LD_BC(16 * PALETTE_SIZE);
    CALL(aCopyBytes);
    POP_AF;
    LDH_addr_A(rSVBK);
    XOR_A_A;
    LDH_addr_A(hSCX);
    LDH_addr_A(hSCY);
    LD_A(0x7);
    LDH_addr_A(hWX);
    LD_A(0x90);
    LDH_addr_A(hWY);
    FARCALL(aClearSpriteAnims);
    CALL(aIntro_SetCGBPalUpdate);
    XOR_A_A;
    LD_addr_A(wIntroSceneFrameCounter);
    LD_addr_A(wIntroSceneTimer);
    CALL(aNextIntroScene);
    RET;
    // return;

}

void IntroScene27(void){
//  Spell out C R Y S T A L with Unown.
    LD_HL(wIntroSceneTimer);
    INC_hl;
    LD_HL(wIntroSceneFrameCounter);
    LD_A_hl;
    INC_hl;
    CP_A(0x80);
    IF_NC goto done;

    LD_C_A;
    AND_A(0xf);
    LD_addr_A(wIntroSceneTimer);
    LD_A_C;
    AND_A(0x70);
    SWAP_A;
    CALL(aIntro_FadeUnownWordPals);
    RET;


done:
    CALL(aNextIntroScene);
    LD_A(0x80);
    LD_addr_A(wIntroSceneFrameCounter);
    RET;
    // return;

}

void IntroScene28(void){
//  Cut out when the music ends, and lead into the title screen.
    LD_HL(wIntroSceneFrameCounter);
    LD_A_hl;
    AND_A_A;
    IF_Z goto done;
    DEC_hl;
    CP_A(0x18);
    IF_Z goto clear;
    CP_A(0x8);
    RET_NZ ;

    LD_DE(SFX_INTRO_WHOOSH);
    CALL(aPlaySFX);
    RET;


clear:
    CALL(aClearBGPalettes);
    RET;


done:
    LD_HL(wJumptableIndex);
    SET_hl(7);
    RET;
    // return;

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


FadePals:
// INCLUDE "gfx/intro/fade.pal"

    return CrystalIntro_InitUnownAnim();
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

    return Intro_Scene20_AppearUnown();
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


pal1:
// INCLUDE "gfx/intro/unown_1.pal"


pal2:
// INCLUDE "gfx/intro/unown_2.pal"

    return Intro_FadeUnownWordPals();
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


FastFadePalettes:
// hue = 31
//     for(int rept = 0; rept < 8; rept++){
//     //rgb ['hue', 'hue', 'hue']
// hue -= 1
//     //rgb ['hue', 'hue', 'hue']
// hue -= 2
//     }


SlowFadePalettes:
// hue = 31
//     for(int rept = 0; rept < 16; rept++){
//     //rgb ['hue', 'hue', 'hue']
// hue -= 1
//     }

    return Intro_LoadTilemap();
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

void Intro_Scene16_AnimateSuicune(void){
    LD_A_addr(wIntroSceneFrameCounter);
    AND_A(0x3);
    JR_Z (mIntro_ColoredSuicuneFrameSwap);
    CP_A(0x3);
    IF_Z goto PrepareForSuicuneSwap;
    RET;


PrepareForSuicuneSwap:
    XOR_A_A;
    LDH_addr_A(hBGMapMode);
    RET;

}

void Intro_ColoredSuicuneFrameSwap(void){
    hlcoord(0, 0, wTilemap);
    LD_BC(SCREEN_HEIGHT * SCREEN_WIDTH);

loop:
    LD_A_hl;
    AND_A_A;
    IF_Z goto skip;
    CP_A(0x80);
    IF_NC goto skip;
    XOR_A(0x8);
    LD_hl_A;

skip:
    INC_HL;
    DEC_BC;
    LD_A_C;
    OR_A_B;
    IF_NZ goto loop;
    LD_A(0x1);
    LDH_addr_A(hBGMapMode);
    RET;

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

void Intro_SetCGBPalUpdate(void){
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

void IntroSuicuneRunGFX(void){
// INCBIN "gfx/intro/suicune_run.2bpp.lz"

    return IntroPichuWooperGFX();
}

void IntroPichuWooperGFX(void){
// INCBIN "gfx/intro/pichu_wooper.2bpp.lz"

    return IntroBackgroundGFX();
}

void IntroBackgroundGFX(void){
// INCBIN "gfx/intro/background.2bpp.lz"

    return IntroBackgroundTilemap();
}

void IntroBackgroundTilemap(void){
// INCBIN "gfx/intro/background.tilemap.lz"

    return IntroBackgroundAttrmap();
}

void IntroBackgroundAttrmap(void){
// INCBIN "gfx/intro/background.attrmap.lz"

    return IntroBackgroundPalette();
}

void IntroBackgroundPalette(void){
// INCLUDE "gfx/intro/background.pal"

    return IntroUnownsGFX();
}

void IntroUnownsGFX(void){
// INCBIN "gfx/intro/unowns.2bpp.lz"

    return IntroPulseGFX();
}

void IntroPulseGFX(void){
// INCBIN "gfx/intro/pulse.2bpp.lz"

    return IntroUnownATilemap();
}

void IntroUnownATilemap(void){
// INCBIN "gfx/intro/unown_a.tilemap.lz"

    return IntroUnownAAttrmap();
}

void IntroUnownAAttrmap(void){
// INCBIN "gfx/intro/unown_a.attrmap.lz"

    return IntroUnownHITilemap();
}

void IntroUnownHITilemap(void){
// INCBIN "gfx/intro/unown_hi.tilemap.lz"

    return IntroUnownHIAttrmap();
}

void IntroUnownHIAttrmap(void){
// INCBIN "gfx/intro/unown_hi.attrmap.lz"

    return IntroUnownsTilemap();
}

void IntroUnownsTilemap(void){
// INCBIN "gfx/intro/unowns.tilemap.lz"

    return IntroUnownsAttrmap();
}

void IntroUnownsAttrmap(void){
// INCBIN "gfx/intro/unowns.attrmap.lz"

    return IntroUnownsPalette();
}

void IntroUnownsPalette(void){
// INCLUDE "gfx/intro/unowns.pal"

    return IntroCrystalUnownsGFX();
}

void IntroCrystalUnownsGFX(void){
// INCBIN "gfx/intro/crystal_unowns.2bpp.lz"

    return IntroCrystalUnownsTilemap();
}

void IntroCrystalUnownsTilemap(void){
// INCBIN "gfx/intro/crystal_unowns.tilemap.lz"

    return IntroCrystalUnownsAttrmap();
}

void IntroCrystalUnownsAttrmap(void){
// INCBIN "gfx/intro/crystal_unowns.attrmap.lz"

    return IntroCrystalUnownsPalette();
}

void IntroCrystalUnownsPalette(void){
// INCLUDE "gfx/intro/crystal_unowns.pal"

    return IntroSuicuneCloseGFX();
}

void IntroSuicuneCloseGFX(void){
// INCBIN "gfx/intro/suicune_close.2bpp.lz"

    return IntroSuicuneCloseTilemap();
}

void IntroSuicuneCloseTilemap(void){
// INCBIN "gfx/intro/suicune_close.tilemap.lz"

    return IntroSuicuneCloseAttrmap();
}

void IntroSuicuneCloseAttrmap(void){
// INCBIN "gfx/intro/suicune_close.attrmap.lz"

    return IntroSuicuneClosePalette();
}

void IntroSuicuneClosePalette(void){
// INCLUDE "gfx/intro/suicune_close.pal"

    return IntroSuicuneJumpGFX();
}

void IntroSuicuneJumpGFX(void){
// INCBIN "gfx/intro/suicune_jump.2bpp.lz"

    return IntroSuicuneBackGFX();
}

void IntroSuicuneBackGFX(void){
// INCBIN "gfx/intro/suicune_back.2bpp.lz"

    return IntroSuicuneJumpTilemap();
}

void IntroSuicuneJumpTilemap(void){
// INCBIN "gfx/intro/suicune_jump.tilemap.lz"

    return IntroSuicuneJumpAttrmap();
}

void IntroSuicuneJumpAttrmap(void){
// INCBIN "gfx/intro/suicune_jump.attrmap.lz"

    return IntroSuicuneBackTilemap();
}

void IntroSuicuneBackTilemap(void){
// INCBIN "gfx/intro/suicune_back.tilemap.lz"

    return IntroSuicuneBackAttrmap();
}

void IntroSuicuneBackAttrmap(void){
// INCBIN "gfx/intro/suicune_back.attrmap.lz"

    return IntroSuicunePalette();
}

void IntroSuicunePalette(void){
// INCLUDE "gfx/intro/suicune.pal"

    return IntroUnownBackGFX();
}

void IntroUnownBackGFX(void){
// INCBIN "gfx/intro/unown_back.2bpp.lz"

    return IntroGrass1GFX();
}

void IntroGrass1GFX(void){
// INCBIN "gfx/intro/grass1.2bpp"
    return IntroGrass2GFX();
}

void IntroGrass2GFX(void){
// INCBIN "gfx/intro/grass2.2bpp"
    return IntroGrass3GFX();
}

void IntroGrass3GFX(void){
// INCBIN "gfx/intro/grass3.2bpp"
    return IntroGrass4GFX();
}

void IntroGrass4GFX(void){
// INCBIN "gfx/intro/grass4.2bpp"

}
