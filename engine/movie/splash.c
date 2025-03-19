#include "../../constants.h"
#include "splash.h"
#include "../../home/audio.h"
#include "../../home/delay.h"
#include "../../home/copy.h"
#include "../../home/tilemap.h"
#include "../../home/text.h"
#include "../../home/sprite_anims.h"
#include "../../home/clear_sprites.h"
#include "../../home/palettes.h"
#include "../../home/joypad.h"
#include "../menus/intro_menu.h"
#include "../gfx/sprites.h"
#include "gbc_only.h"
#include "../../gfx/misc.h"
#include "../math/sine.h"
#include "../../charmap.h"

 // "gfx/splash/ditto_fade.pal";
// Ditto's color as it turns into the Game Freak logo.
// Fade from pink to orange.
// One color per step.
const uint16_t GameFreakDittoPaletteFade[] = {
    rgb(23, 12, 28),
    rgb(23, 12, 27),
    rgb(23, 13, 26),
    rgb(23, 13, 24),
    rgb(24, 14, 22),
    rgb(24, 14, 20),
    rgb(24, 15, 18),
    rgb(24, 15, 16),
    rgb(25, 16, 14),
    rgb(25, 16, 12),
    rgb(25, 17, 10),
    rgb(25, 17,  8),
    rgb(26, 18,  6),
    rgb(26, 18,  4),
    rgb(26, 19,  2),
    rgb(26, 19,  0),
};


const char GameFreakPresentsGFX[] = "gfx/splash/gamefreak_presents.png";
const char GameFreakLogoGFX[] = "gfx/splash/gamefreak_logo.png";

//  Play the copyright screen and GameFreak Presents sequence.
//  Return carry if user cancels animation by pressing a button.
bool SplashScreen(void){
//  Reinitialize everything
    // LD_DE(MUSIC_NONE);
    // CALL(aPlayMusic);
    PlayMusic(MUSIC_NONE);
    // CALL(aClearBGPalettes);
    ClearBGPalettes_Conv();
    // CALL(aClearTilemap);
    ClearTilemap_Conv2();
    // LD_A(HIGH(vBGMap0));
    // LDH_addr_A(hBGMapAddress + 1);
    // XOR_A_A;  // LOW(vBGMap0)
    // LDH_addr_A(hBGMapAddress);
    hram->hBGMapAddress = vBGMap0;
    // LDH_addr_A(hJoyDown);
    hram->hJoyDown = 0;
    // LDH_addr_A(hSCX);
    hram->hSCX = 0;
    // LDH_addr_A(hSCY);
    hram->hSCY = 0;
    // LD_A(SCREEN_HEIGHT_PX);
    // LDH_addr_A(hWY);
    hram->hWY = SCREEN_HEIGHT_PX;
    // CALL(aWaitBGMap);
    WaitBGMap_Conv();
    // LD_B(SCGB_GAMEFREAK_LOGO);
    // CALL(aGetSGBLayout);
    GetSGBLayout_Conv(SCGB_GAMEFREAK_LOGO);
    // CALL(aSetPalettes);
    SetPalettes_Conv();
    // LD_C(10);
    // CALL(aDelayFrames);
    DelayFrames(10);

//  Draw copyright screen
    // CALLFAR(aCopyright);
    Copyright();
    // CALL(aWaitBGMap);
    WaitBGMap_Conv();
    // LD_C(100);
    // CALL(aDelayFrames);
    DelayFrames(100);
    // CALL(aClearTilemap);
    ClearTilemap_Conv2();

//  Stop here if not in GBC mode
    // FARCALL(aGBCOnlyScreen);
    GBCOnlyScreen();

//  Play GameFreak logo animation
    // CALL(aGameFreakPresentsInit);
    GameFreakPresentsInit();

    while(1) {
    // joy_loop:
        // CALL(aJoyTextDelay);
        JoyTextDelay_Conv();
        // LDH_A_addr(hJoyLast);
        // AND_A(BUTTONS);
        // IF_NZ goto pressed_button;
        if(hram->hJoyLast & (BUTTONS)) {
        // pressed_button:
            // CALL(aGameFreakPresentsEnd);
            GameFreakPresentsEnd();
            // SCF;
            // RET;
            return true;
        }
        // LD_A_addr(wJumptableIndex);
        // BIT_A(7);
        // IF_NZ goto finish;
        if(bit_test(wram->wJumptableIndex, 7))
            break;
        // CALL(aGameFreakPresentsScene);
        GameFreakPresentsScene();
        // FARCALL(aPlaySpriteAnimations);
        {
            bank_push(BANK(aPlaySpriteAnimations));
            PlaySpriteAnimations_Conv();
            bank_pop;
        }
        // CALL(aDelayFrame);
        DelayFrame();
        // goto joy_loop;
    }

// finish:
    // CALL(aGameFreakPresentsEnd);
    GameFreakPresentsEnd();
    // AND_A_A;
    // RET;
    return false;
}

void GameFreakPresentsInit(void){
    // LD_DE(mGameFreakLogoGFX);
    // LD_HL(vTiles2);
    // LD_BC((BANK(aGameFreakLogoGFX) << 8) | 28);
    // CALL(aGet1bpp);
    LoadPNG1bppAssetSectionToVRAM(vram->vTiles2, GameFreakPresentsGFX, 0, 13);
    LoadPNG1bppAssetSectionToVRAM(vram->vTiles2 + 13 * LEN_2BPP_TILE, GameFreakLogoGFX, 0, 15);

    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    // LD_A(BANK(wDecompressScratch));
    // LDH_addr_A(rSVBK);

    // LD_HL(mGameFreakDittoGFX);
    // LD_DE(wDecompressScratch);
    // LD_A(BANK(aGameFreakDittoGFX));
    // CALL(aFarDecompress);

    // LD_HL(vTiles0);
    // LD_DE(wDecompressScratch);
    // LD_BC((1 << 8) | 8 * LEN_2BPP_TILE);
    // CALL(aRequest2bpp);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles0, GameFreakDittoGFX, 0, 0x80);

    // LD_HL(vTiles1);
    // LD_DE(wDecompressScratch + 0x80 * LEN_2BPP_TILE);
    // LD_BC((1 << 8) | 8 * LEN_2BPP_TILE);
    // CALL(aRequest2bpp);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles1, GameFreakDittoGFX, 0x80, 0x80);

    // POP_AF;
    // LDH_addr_A(rSVBK);

    // FARCALL(aClearSpriteAnims);
    ClearSpriteAnims_Conv();
    // depixel4(10, 11, 4, 0);
    // LD_A(SPRITE_ANIM_INDEX_GAMEFREAK_LOGO);
    // CALL(aInitSpriteAnimStruct);
    struct SpriteAnim* bc = InitSpriteAnimStruct_Conv(SPRITE_ANIM_INDEX_GAMEFREAK_LOGO, pixel4(10, 11, 4, 0));
    // LD_HL(SPRITEANIMSTRUCT_YOFFSET);
    // ADD_HL_BC;
    // LD_hl(160);
    bc->yOffset = 160;
    // LD_HL(SPRITEANIMSTRUCT_VAR1);
    // ADD_HL_BC;
    // LD_hl(96);
    bc->var1 = 96;
    // LD_HL(SPRITEANIMSTRUCT_VAR2);
    // ADD_HL_BC;
    // LD_hl(48);
    bc->var2 = 48;
    // XOR_A_A;
    // LD_addr_A(wJumptableIndex);
    wram->wJumptableIndex = 0;
    // LD_addr_A(wIntroSceneFrameCounter);
    wram->wIntroSceneFrameCounter = 0;
    // LD_addr_A(wIntroSceneTimer);
    wram->wIntroSceneTimer = 0;
    // LDH_addr_A(hSCX);
    hram->hSCX = 0;
    // LDH_addr_A(hSCY);
    hram->hSCY = 0;
    // LD_A(1);
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = 1;
    // LD_A(144);
    // LDH_addr_A(hWY);
    hram->hWY = SCREEN_HEIGHT_PX;
    // LD_DE((0b11100100 << 8) | 0b11100100);
    // CALL(aDmgToCgbObjPals);
    DmgToCgbObjPals_Conv(0b11100100, 0b11100100);
    // RET;
}

void GameFreakPresentsEnd(void){
    // FARCALL(aClearSpriteAnims);
    ClearSpriteAnims_Conv();
    // CALL(aClearTilemap);
    ClearTilemap_Conv2();
    // CALL(aClearSprites);
    ClearSprites();
    // LD_C(16);
    // CALL(aDelayFrames);
    DelayFrames(16);
    // RET;
}

void GameFreakPresentsScene(void){
    switch(wram->wJumptableIndex) {
        case 0: return GameFreakPresents_WaitSpriteAnim();
        case 1: return GameFreakPresents_PlaceGameFreak();
        case 2: return GameFreakPresents_PlacePresents();
        case 3: return GameFreakPresents_WaitForTimer();
    }
    // RET;
}

void GameFreakPresents_NextScene(void){
    // LD_HL(wJumptableIndex);
    // INC_hl;
    wram->wJumptableIndex++;
    // RET;
}

void GameFreakPresents_WaitSpriteAnim(void){
    // RET;

}

void GameFreakPresents_PlaceGameFreak(void){
    static const uint8_t game_freak[] = {0x00, 0x01, 0x02, 0x03, 0x0d, 0x04, 0x05, 0x03, 0x01, 0x06, CHAR_TERM};
    // LD_HL(wIntroSceneTimer);
    // LD_A_hl;
    // CP_A(32);
    // IF_NC goto PlaceGameFreak;
    if(wram->wIntroSceneTimer < 32) {
        // INC_hl;
        wram->wIntroSceneTimer++;
        // RET;
        return;
    }

// PlaceGameFreak:
    // LD_hl(0);
    wram->wIntroSceneTimer = 0;
    // LD_HL(mGameFreakPresents_PlaceGameFreak_game_freak);
    // decoord(5, 10, wTilemap);
    // LD_BC(mGameFreakPresents_PlaceGameFreak_end - mGameFreakPresents_PlaceGameFreak_game_freak);
    // CALL(aCopyBytes);
    CopyBytes(coord(5, 10, wram->wTilemap), game_freak, sizeof(game_freak) - 1);
    // CALL(aGameFreakPresents_NextScene);
    GameFreakPresents_NextScene();
    // LD_DE(SFX_GAME_FREAK_PRESENTS);
    // CALL(aPlaySFX);
    PlaySFX(SFX_GAME_FREAK_PRESENTS);
    // RET;
    return;

end:;
    //db ['"@"'];

    return GameFreakPresents_PlacePresents();
}

void GameFreakPresents_PlacePresents(void){
    static const uint8_t presents[] = {0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, CHAR_TERM};
    // LD_HL(wIntroSceneTimer);
    // LD_A_hl;
    // CP_A(64);
    // IF_NC goto place_presents;
    if(wram->wIntroSceneTimer < 64) {
        // INC_hl;
        wram->wIntroSceneTimer++;
        // RET;
        return;
    }


// place_presents:
    // LD_hl(0);
    wram->wIntroSceneTimer = 0;
    // LD_HL(mGameFreakPresents_PlacePresents_presents);
    // decoord(7, 11, wTilemap);
    // LD_BC(mGameFreakPresents_PlacePresents_end - mGameFreakPresents_PlacePresents_presents);
    // CALL(aCopyBytes);
    CopyBytes(coord(7, 11, wram->wTilemap), presents, sizeof(presents) - 1);
    // CALL(aGameFreakPresents_NextScene);
    GameFreakPresents_NextScene();
    // RET;
    return;

end:;
    //db ['"@"'];
}

void GameFreakPresents_WaitForTimer(void){
    // LD_HL(wIntroSceneTimer);
    // LD_A_hl;
    // CP_A(128);
    // IF_NC goto finish;
    if(wram->wIntroSceneTimer < 128) {
        // INC_hl;
        wram->wIntroSceneTimer++;
        // RET;
        return;
    }

// finish:
    // LD_HL(wJumptableIndex);
    // SET_hl(7);
    bit_set(wram->wJumptableIndex, 7);
    // RET;
}

void GameFreakLogoSpriteAnim(void){
    LD_HL(SPRITEANIMSTRUCT_JUMPTABLE_INDEX);
    ADD_HL_BC;
    LD_E_hl;
    LD_D(0);
    LD_HL(mGameFreakLogoSpriteAnim_scenes);
    ADD_HL_DE;
    ADD_HL_DE;
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    JP_hl;


//scenes:
    //dw ['GameFreakLogo_Init'];
    //dw ['GameFreakLogo_Bounce'];
    //dw ['GameFreakLogo_Ditto'];
    //dw ['GameFreakLogo_Transform'];
    //dw ['GameFreakLogo_Done'];
}

void GameFreakLogoSpriteAnim_Conv(struct SpriteAnim* bc){
    // LD_HL(SPRITEANIMSTRUCT_JUMPTABLE_INDEX);
    // ADD_HL_BC;
    // LD_E_hl;
    // LD_D(0);
    // LD_HL(mGameFreakLogoSpriteAnim_scenes);
    // ADD_HL_DE;
    // ADD_HL_DE;
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // JP_hl;
    switch(bc->jumptableIndex) {
    // scenes:
        //dw ['GameFreakLogo_Init'];
        case 0: GameFreakLogo_Init(bc); break;
        //dw ['GameFreakLogo_Bounce'];
        case 1: GameFreakLogo_Bounce(bc); break;
        //dw ['GameFreakLogo_Ditto'];
        case 2: GameFreakLogo_Ditto(bc); break;
        //dw ['GameFreakLogo_Transform'];
        case 3: GameFreakLogo_Transform(bc); break;
        //dw ['GameFreakLogo_Done'];
        default:
        case 4: GameFreakLogo_Done(bc); break;
    }
}

void GameFreakLogo_Init(struct SpriteAnim* bc){
    // LD_HL(SPRITEANIMSTRUCT_JUMPTABLE_INDEX);
    // ADD_HL_BC;
    // INC_hl;
    bc->jumptableIndex++;
    // RET;
}

//  Bounce with a height of 0C, 0C / 48 times.
//  By default, this is twice, with a height of 96 pixels and 48 pixels.
//  Sine offset starts at 48 (32+32/2, or pi+pi/2), so it starts at the maximum
//  value of the sine wave (i.e. the top of the screen).
void GameFreakLogo_Bounce(struct SpriteAnim* bc){
    // LD_HL(SPRITEANIMSTRUCT_VAR1);  // jump height
    // ADD_HL_BC;
    // LD_A_hl;
    uint8_t jumpHeight = bc->var1;
    // AND_A_A;
    // IF_Z goto done;
    if(jumpHeight == 0) {
    // done:
        // LD_HL(SPRITEANIMSTRUCT_JUMPTABLE_INDEX);
        // ADD_HL_BC;
        // INC_hl;
        bc->jumptableIndex++;
        // LD_HL(SPRITEANIMSTRUCT_VAR2);
        // ADD_HL_BC;
        // LD_hl(0);
        bc->var2 = 0;
        // LD_DE(SFX_DITTO_POP_UP);
        // CALL(aPlaySFX);
        PlaySFX(SFX_DITTO_POP_UP);
        // RET;
        return;
    }

//  Load the sine offset, make sure it doesn't reach the negative part of the wave
    // LD_D_A;
    // LD_HL(SPRITEANIMSTRUCT_VAR2);  // sine offset
    // ADD_HL_BC;
    // LD_A_hl;
    uint8_t sineOffset = bc->var2 & 0x3f;
    // AND_A(0x3f);  // full circle = 2*pi = 2*32
    // CP_A(32);
    // IF_NC goto no_negative;
    if(sineOffset < 32) {
        // ADD_A(32);
        sineOffset += 32;
    }
// no_negative:

    // LD_E_A;
    // FARCALL(aBattleAnim_Sine_e);  // e = d * sin(e * pi/32)
    // LD_HL(SPRITEANIMSTRUCT_YOFFSET);
    // ADD_HL_BC;
    // LD_hl_E;
    bc->yOffset = v_Sine_Conv(sineOffset, jumpHeight);

//  Decrement the sine offset
    // LD_HL(SPRITEANIMSTRUCT_VAR2);  // sine offset
    // ADD_HL_BC;
    // LD_A_hl;
    // DEC_hl;
    // AND_A(0x1f);  // a%32 == 0
    // RET_NZ ;
    if(((--bc->var2) & 0x1f) != 0)
        return;

//  If the ditto's reached the ground, decrement the jump height and play the sfx
    // LD_HL(SPRITEANIMSTRUCT_VAR1);  // jump height
    // ADD_HL_BC;
    // LD_A_hl;
    // SUB_A(48);
    // LD_hl_A;
    bc->var1 -= 48;
    // LD_DE(SFX_DITTO_BOUNCE);
    // CALL(aPlaySFX);
    PlaySFX(SFX_DITTO_BOUNCE);
    // RET;
}

//  Wait a little, then start transforming
void GameFreakLogo_Ditto(struct SpriteAnim* bc){
    // LD_HL(SPRITEANIMSTRUCT_VAR2);  // frame count
    // ADD_HL_BC;
    // LD_A_hl;
    // CP_A(32);
    // IF_NC goto start_transform;
    if(bc->var2 >= 32) {
    // start_transform:
        // LD_HL(SPRITEANIMSTRUCT_JUMPTABLE_INDEX);
        // ADD_HL_BC;
        // INC_hl;
        bc->jumptableIndex++;
        // LD_HL(SPRITEANIMSTRUCT_VAR2);
        // ADD_HL_BC;
        // LD_hl(0);
        bc->var2 = 0;
        // LD_DE(SFX_DITTO_TRANSFORM);
        // CALL(aPlaySFX);
        PlaySFX(SFX_DITTO_TRANSFORM);
        // RET;
        return;
    }
    // INC_hl;
    bc->var2++;
    // RET;
    return;
}

void GameFreakLogo_Transform(struct SpriteAnim* bc){
    // LD_HL(SPRITEANIMSTRUCT_VAR2);  // frame count
    // ADD_HL_BC;
    // LD_A_hl;
    // CP_A(64);
    // IF_Z goto done;
    if(bc->var2 == 64) {
    // done:
        // LD_HL(SPRITEANIMSTRUCT_JUMPTABLE_INDEX);
        // ADD_HL_BC;
        // INC_hl;
        bc->jumptableIndex++;
        // CALL(aGameFreakPresents_NextScene);
        GameFreakPresents_NextScene();
        return;
    }
    // INC_hl;
    uint8_t a = bc->var2++;

//  Fade ditto's palettes while it's transforming
    // SRL_A;
    // SRL_A;
    // LD_E_A;
    // LD_D(0);
    // LD_HL(mGameFreakDittoPaletteFade);
    uint16_t color = GameFreakDittoPaletteFade[(a >> 2) & 0xf];
    // ADD_HL_DE;
    // ADD_HL_DE;
    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    // LD_A(BANK(wOBPals2));
    // LDH_addr_A(rSVBK);
    // LD_A_hli;
    // LD_addr_A(wOBPals2 + 12);
    // LD_A_hli;
    // LD_addr_A(wOBPals2 + 13);
    *(uint16_t*)(wram->wOBPals2 + 12) = color;
    // POP_AF;
    // LDH_addr_A(rSVBK);
    // LD_A(TRUE);
    // LDH_addr_A(hCGBPalUpdate);
    hram->hCGBPalUpdate = TRUE;
    // RET;
    return;
}

void GameFreakLogo_Done(struct SpriteAnim* bc){
    (void)bc;
    // RET;
    return;
}
