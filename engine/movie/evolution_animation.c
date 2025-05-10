#include "../../constants.h"
#include "evolution_animation.h"
#include "../../home/copy.h"
#include "../../home/delay.h"
#include "../../home/tilemap.h"
#include "../../home/audio.h"
#include "../../home/pokemon.h"
#include "../../home/joypad.h"
#include "../../home/sprite_anims.h"
#include "../gfx/load_pics.h"
#include "../gfx/sprites.h"
#include "../gfx/cgb_layouts.h"
#include "../gfx/pic_animation.h"
#include "../pokemon/stats_screen.h"

void EvolutionAnimation(void) {
    REG_F_C = EvolutionAnimation_Conv();
}

static void EvolutionAnimation_GetSGBLayout(bool c){
    // LD_B(SCGB_EVOLUTION);
    // JP(mGetSGBLayout);
    if(c) {
        return v_CGB_Evolution2();
    }
    else {
        return GetSGBLayout(SCGB_EVOLUTION);
    }
}

static void EvolutionAnimation_PlaceFrontpic(species_t species){
    // CALL(aGetBaseData);
    GetBaseData(species);
    // hlcoord(7, 2, wTilemap);
    // JP(mPrepMonFrontpic);
    PrepMonFrontpic(coord(7, 2, wram->wTilemap));
}

static void EvolutionAnimation_LoadFrontpic(species_t species){
    // CALL(aGetBaseData);
    GetBaseData(species);
    // LD_A(0x1);
    // LD_addr_A(wBoxAlignment);
    wram->wBoxAlignment = 0x1;
    // LD_DE(vTiles2);
    // PREDEF(pGetAnimatedFrontpic);
    GetAnimatedFrontpic(vram->vTiles2, 0);
    // XOR_A_A;
    // LD_addr_A(wBoxAlignment);
    wram->wBoxAlignment = 0x0;
    // RET;
}

static bool EvolutionAnimation_check_statused(void){
    // LD_A_addr(wCurPartyMon);
    // LD_HL(wPartyMon1Species);
    // CALL(aGetPartyLocation);
    // LD_B_H;
    // LD_C_L;
    // FARCALL(aCheckFaintedFrzSlp);
    // RET;
    return CheckFaintedFrzSlp(wram->wPartyMon + wram->wCurPartyMon);
}

static void EvolutionAnimation_ReplaceFrontpic(void){
    // PUSH_BC;
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = BGMAPMODE_NONE;
    // hlcoord(7, 2, wTilemap);
    tile_t* hl = coord(7, 2, wram->wTilemap);
    // LD_BC((7 << 8) | 7);
    uint8_t b = 7;
    uint8_t c = 7;
    // LD_DE(SCREEN_WIDTH - 7);

    do {
    // loop1:
        // PUSH_BC;
        uint8_t c2 = c;
        tile_t* hl2 = hl;

        do {
        // loop2:
            // LD_A_addr(wEvolutionPicOffset);
            // ADD_A_hl;
            *hl2 += wram->wEvolutionPicOffset;
            // LD_hli_A;
            hl2++;
            // DEC_C;
            // IF_NZ goto loop2;
        } while(--c2 != 0);
        // POP_BC;
        // ADD_HL_DE;
        hl += SCREEN_WIDTH;
        // DEC_B;
        // IF_NZ goto loop1;
    } while(--b != 0);
    // LD_A(0x1);
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = BGMAPMODE_UPDATE_TILES;
    // CALL(aWaitBGMap);
    WaitBGMap();
    // POP_BC;
    // RET;
}

static void EvolutionAnimation_Flash(uint8_t b){
    do {
        // LD_A(-7 * 7);  // new stage
        // LD_addr_A(wEvolutionPicOffset);
        wram->wEvolutionPicOffset = (uint8_t)(-7 * 7);
        // CALL(aEvolutionAnimation_ReplaceFrontpic);
        EvolutionAnimation_ReplaceFrontpic();
        // LD_A(7 * 7);  // previous stage
        // LD_addr_A(wEvolutionPicOffset);
        wram->wEvolutionPicOffset = 7 * 7;
        // CALL(aEvolutionAnimation_ReplaceFrontpic);
        EvolutionAnimation_ReplaceFrontpic();
        // DEC_B;
        // IF_NZ goto Flash;
    } while(--b != 0);
    // RET;
}

static bool EvolutionAnimation_WaitFrames_CheckPressedB(uint8_t c){
    do {
        // CALL(aDelayFrame);
        DelayFrame();
        // PUSH_BC;
        // CALL(aJoyTextDelay);
        JoyTextDelay();
        // LDH_A_addr(hJoyDown);
        // POP_BC;
        // AND_A(B_BUTTON);
        // IF_NZ goto pressed_b;
        if(hram->hJoyDown & B_BUTTON) {
        // pressed_b:
            // LD_A_addr(wForceEvolution);
            // AND_A_A;
            // IF_NZ goto loop3;
            if(!wram->wForceEvolution) {
                // SCF;
                // RET;
                return true;
            }
        }

    // loop3:
        // DEC_C;
        // IF_NZ goto WaitFrames_CheckPressedB;
    } while(--c != 0);
    // AND_A_A;
    // RET;
    return false;
}

static bool EvolutionAnimation_AnimationSequence(void){
    // CALL(aClearJoypad);
    ClearJoypad();
    // LD_BC((1 << 8) | 2 * 7);  // flash b times, wait c frames in between
    uint8_t b = 1;
    uint8_t c = 2 * 7;

    do {
    // loop:
        // PUSH_BC;
        // CALL(aEvolutionAnimation_WaitFrames_CheckPressedB);
        // POP_BC;
        // IF_C goto exit_sequence;
        if(EvolutionAnimation_WaitFrames_CheckPressedB(c)) {
        // exit_sequence:
            // SCF;
            // RET;
            return true;
        }
        // PUSH_BC;
        // CALL(aEvolutionAnimation_Flash);
        EvolutionAnimation_Flash(b);
        // POP_BC;
        // INC_B;
        // DEC_C;
        // DEC_C;
        c -= 2;
        // IF_NZ goto loop;
    } while(++b, c != 0);
    // AND_A_A;
    // RET;
    return false;
}

static void EvolutionAnimation_GenerateBallOfLight(uint8_t e){
    // PUSH_DE;
    // depixel2(9, 11);
    // LD_A(SPRITE_ANIM_INDEX_EVOLUTION_BALL_OF_LIGHT);
    // CALL(aInitSpriteAnimStruct);
    struct SpriteAnim* bc = InitSpriteAnimStruct(SPRITE_ANIM_INDEX_EVOLUTION_BALL_OF_LIGHT, pixel2(9, 11));
    // LD_HL(SPRITEANIMSTRUCT_JUMPTABLE_INDEX);
    // ADD_HL_BC;
    // LD_A_addr(wJumptableIndex);
    // AND_A(0b1110);
    // SLA_A;
    // POP_DE;
    // ADD_A_E;
    // LD_hl_A;
    bc->jumptableIndex = ((wram->wJumptableIndex & 0b1110) << 1) + e;
    // LD_HL(SPRITEANIMSTRUCT_TILE_ID);
    // ADD_HL_BC;
    // LD_hl(0x0);
    bc->tileID = 0x0;
    // LD_HL(SPRITEANIMSTRUCT_VAR1);
    // ADD_HL_BC;
    // LD_hl(0x10);
    bc->var1 = 0x10;
    // RET;
}

static bool EvolutionAnimation_balls_of_light(void){
    // LD_HL(wJumptableIndex);
    // LD_A_hl;
    // CP_A(32);
    // RET_NC ;
    if(wram->wJumptableIndex >= 8)  // Changed this to 8, since there aren't enough SpriteAnim slots for these balls of light.
                                    // Maybe there's a logic error somewhere else?
        return false;
    // LD_D_A;
    // INC_hl;
    uint8_t d = wram->wJumptableIndex++;
    // AND_A(0x1);
    // IF_NZ goto done_balls;
    if((d & 0x1) == 0) {
        // LD_E(0x0);
        // CALL(aEvolutionAnimation_GenerateBallOfLight);
        EvolutionAnimation_GenerateBallOfLight(0x0);
        // LD_E(0x10);
        // CALL(aEvolutionAnimation_GenerateBallOfLight);
        EvolutionAnimation_GenerateBallOfLight(0x10);
    }

// done_balls:
    // SCF;
    // RET;
    return true;
}

static void EvolutionAnimation_AnimateBallsOfLight(void){
    // PUSH_BC;
    // CALLFAR(aPlaySpriteAnimations);
    PlaySpriteAnimations();
// a = (([hVBlankCounter] + 4) / 2) % NUM_PALETTES
    // LDH_A_addr(hVBlankCounter);
    // AND_A(0b1110);
    // SRL_A;
    // INC_A;
    // INC_A;
    // AND_A(0x7);
    // LD_B_A;
    uint8_t b = ((hram->hVBlankCounter + 4) / 2) & 7;
    // LD_HL(wVirtualOAMSprite00Attributes);
    struct SpriteOAM* hl = wram->wVirtualOAMSprite;
    // LD_C(NUM_SPRITE_OAM_STRUCTS);
    uint8_t c = NUM_SPRITE_OAM_STRUCTS;

    do {
    // loop6:
        // LD_A_hl;
        // OR_A_B;
        // LD_hli_A;  // attributes
        hl->attributes |= b;
        // for(int rept = 0; rept < SPRITEOAMSTRUCT_LENGTH - 1; rept++){
        // INC_HL;
        // }
        hl++;
        // DEC_C;
        // IF_NZ goto loop6;
    } while(--c != 0);
    // POP_BC;
    // CALL(aDelayFrame);
    DelayFrame();
    // RET;
}

static void EvolutionAnimation_PlayEvolvedSFX(void){
    // LD_A_addr(wEvolutionCanceled);
    // AND_A_A;
    // RET_NZ ;
    if(wram->wEvolutionCanceled)
        return;
    // LD_DE(SFX_EVOLVED);
    // CALL(aPlaySFX);
    PlaySFX(SFX_EVOLVED);
    // LD_HL(wJumptableIndex);
    // LD_A_hl;
    // PUSH_AF;
    uint8_t jumptableIndex = wram->wJumptableIndex;
    // LD_hl(0x0);
    wram->wJumptableIndex = 0x0;

    while(EvolutionAnimation_balls_of_light()) {
    // loop4:
        // CALL(aEvolutionAnimation_balls_of_light);
        // IF_NC goto done;
        // CALL(aEvolutionAnimation_AnimateBallsOfLight);
        EvolutionAnimation_AnimateBallsOfLight();
        // goto loop4;
    }

// done:
    // LD_C(32);
    uint8_t c = 32;

    do {
    // loop5:
        // CALL(aEvolutionAnimation_AnimateBallsOfLight);
        EvolutionAnimation_AnimateBallsOfLight();
        // DEC_C;
        // IF_NZ goto loop5;
    } while(--c != 0);
    // POP_AF;
    // LD_addr_A(wJumptableIndex);
    wram->wJumptableIndex = jumptableIndex;
    // RET;
}

static void EvolutionAnimation_EvolutionAnimation(void){
    static const char GFX0[] = "gfx/evo/bubble_large.png";
    static const char GFX1[] = "gfx/evo/bubble.png";
    // LD_A(0b11100100);
    // LDH_addr_A(rOBP0);
    gb_write(rOBP0, 0b11100100);

    // LD_DE(MUSIC_NONE);
    // CALL(aPlayMusic);
    PlayMusic(MUSIC_NONE);

    // FARCALL(aClearSpriteAnims);
    ClearSpriteAnims();

    // LD_DE(mEvolutionAnimation_GFX);
    // LD_HL(vTiles0);
    // LD_BC((BANK(aEvolutionAnimation_GFX) << 8) | 8);
    // CALL(aRequest2bpp);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles0 + 0x00 * LEN_2BPP_TILE, GFX0, 0, 4);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles0 + 0x04 * LEN_2BPP_TILE, GFX1, 0, 1);

    // XOR_A_A;
    // LD_addr_A(wLowHealthAlarm);
    wram->wLowHealthAlarm = 0x0;
    // CALL(aWaitBGMap);
    WaitBGMap();
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = BGMAPMODE_NONE;

    // LD_A_addr(wEvolutionOldSpecies);
    // LD_addr_A(wPlayerHPPal);
    wram->wPlayerHPPal = wram->wEvolutionOldSpecies;

    // LD_C(FALSE);
    // CALL(aEvolutionAnimation_GetSGBLayout);
    EvolutionAnimation_GetSGBLayout(false);

    // LD_A_addr(wEvolutionOldSpecies);
    // LD_addr_A(wCurPartySpecies);
    wram->wCurPartySpecies = wram->wEvolutionOldSpecies;
    // LD_addr_A(wCurSpecies);
    // CALL(aEvolutionAnimation_PlaceFrontpic);
    EvolutionAnimation_PlaceFrontpic(wram->wEvolutionOldSpecies);

    // LD_DE(vTiles2);
    // LD_HL(vTiles2 + LEN_2BPP_TILE * 0x31);
    // LD_BC(7 * 7);
    // CALL(aRequest2bpp);
    CopyBytes(vram->vTiles2 + LEN_2BPP_TILE * 0x31, vram->vTiles2, 7 * 7 * LEN_2BPP_TILE);

    // LD_A(7 * 7);
    // LD_addr_A(wEvolutionPicOffset);
    wram->wEvolutionPicOffset = 7 * 7;
    // CALL(aEvolutionAnimation_ReplaceFrontpic);
    EvolutionAnimation_ReplaceFrontpic();
    // LD_A_addr(wEvolutionNewSpecies);
    // LD_addr_A(wCurPartySpecies);
    wram->wCurPartySpecies = wram->wEvolutionNewSpecies;
    // LD_addr_A(wCurSpecies);
    // CALL(aEvolutionAnimation_LoadFrontpic);
    EvolutionAnimation_LoadFrontpic(wram->wEvolutionNewSpecies);

    // LD_A_addr(wEvolutionOldSpecies);
    // LD_addr_A(wCurPartySpecies);
    wram->wCurPartySpecies = wram->wEvolutionOldSpecies;
    // LD_addr_A(wCurSpecies);

    // LD_A(1);
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = BGMAPMODE_UPDATE_TILES;

    // CALL(aEvolutionAnimation_check_statused);
    // IF_C goto skip_cry;
    if(!EvolutionAnimation_check_statused()) {
        // LD_A_addr(wEvolutionOldSpecies);
        // CALL(aPlayMonCry);
        PlayMonCry(wram->wEvolutionOldSpecies);
    }

// skip_cry:
    // LD_DE(MUSIC_EVOLUTION);
    // CALL(aPlayMusic);
    PlayMusic(MUSIC_EVOLUTION);

    // LD_C(80);
    // CALL(aDelayFrames);
    DelayFrames(80);

    // LD_C(TRUE);
    // CALL(aEvolutionAnimation_GetSGBLayout);
    EvolutionAnimation_GetSGBLayout(true);

    // CALL(aEvolutionAnimation_AnimationSequence);
    // IF_C goto cancel_evo;
    bool cancel = EvolutionAnimation_AnimationSequence();
    if(cancel) {
    // cancel_evo:
        // LD_A(TRUE);
        // LD_addr_A(wEvolutionCanceled);
        wram->wEvolutionCanceled = TRUE;

        // LD_A_addr(wEvolutionOldSpecies);
        // LD_addr_A(wPlayerHPPal);
        wram->wPlayerHPPal = wram->wEvolutionOldSpecies;

        // LD_C(FALSE);
        // CALL(aEvolutionAnimation_GetSGBLayout);
        EvolutionAnimation_GetSGBLayout(false);

        // CALL(aEvolutionAnimation_PlayEvolvedSFX);
        EvolutionAnimation_PlayEvolvedSFX();
        // FARCALL(aClearSpriteAnims);
        ClearSpriteAnims();
        // CALL(aEvolutionAnimation_check_statused);
        // RET_C ;
        if(EvolutionAnimation_check_statused())
            return;

        // LD_A_addr(wPlayerHPPal);
        // CALL(aPlayMonCry);
        PlayMonCry(wram->wPlayerHPPal);
        // RET;
        return;
    }

    // LD_A(-7 * 7);
    // LD_addr_A(wEvolutionPicOffset);
    wram->wEvolutionPicOffset = (uint8_t)(-7 * 7);
    // CALL(aEvolutionAnimation_ReplaceFrontpic);
    EvolutionAnimation_ReplaceFrontpic();

    // XOR_A_A;
    // LD_addr_A(wEvolutionCanceled);
    wram->wEvolutionCanceled = FALSE;

    // LD_A_addr(wEvolutionNewSpecies);
    // LD_addr_A(wPlayerHPPal);
    wram->wPlayerHPPal = wram->wEvolutionNewSpecies;

    // LD_C(FALSE);
    // CALL(aEvolutionAnimation_GetSGBLayout);
    EvolutionAnimation_GetSGBLayout(false);

    // CALL(aEvolutionAnimation_PlayEvolvedSFX);
    EvolutionAnimation_PlayEvolvedSFX();
    // FARCALL(aClearSpriteAnims);
    ClearSpriteAnims();
    // CALL(aEvolutionAnimation_check_statused);
    // IF_C goto no_anim;
    if(EvolutionAnimation_check_statused())
        return;

    // LD_A_addr(wBoxAlignment);
    // PUSH_AF;
    uint8_t boxAlignment = wram->wBoxAlignment;
    // LD_A(0x1);
    // LD_addr_A(wBoxAlignment);
    wram->wBoxAlignment = 0x1;
    // LD_A_addr(wCurPartySpecies);
    // PUSH_AF;
    species_t curPartySpecies = wram->wCurPartySpecies;

    // LD_A_addr(wPlayerHPPal);
    // LD_addr_A(wCurPartySpecies);
    wram->wCurPartySpecies = wram->wPlayerHPPal;
    // hlcoord(7, 2, wTilemap);
    // LD_D(0x0);
    // LD_E(ANIM_MON_EVOLVE);
    // PREDEF(pAnimateFrontpic);
    AnimateFrontpic(coord(7, 2, wram->wTilemap), 0x0, ANIM_MON_EVOLVE);

    // POP_AF;
    // LD_addr_A(wCurPartySpecies);
    wram->wCurPartySpecies = curPartySpecies;
    // POP_AF;
    // LD_addr_A(wBoxAlignment);
    wram->wBoxAlignment = boxAlignment;
    // RET;

// no_anim:
    // RET;
}

bool EvolutionAnimation_Conv(void){
    // PUSH_HL;
    // PUSH_DE;
    // PUSH_BC;
    // LD_A_addr(wCurSpecies);
    // PUSH_AF;
    species_t curSpecies = wram->wCurSpecies;
    // LDH_A_addr(rOBP0);
    // PUSH_AF;
    uint8_t obp0 = gb_read(rOBP0);
    // LD_A_addr(wBaseDexNo);
    // PUSH_AF;
    species_t baseDexNo = wram->wBaseDexNo;

    // CALL(aEvolutionAnimation_EvolutionAnimation);
    EvolutionAnimation_EvolutionAnimation();

    // POP_AF;
    // LD_addr_A(wBaseDexNo);
    wram->wBaseDexNo = baseDexNo;
    // POP_AF;
    // LDH_addr_A(rOBP0);
    gb_write(rOBP0, obp0);
    // POP_AF;
    // LD_addr_A(wCurSpecies);
    wram->wCurSpecies = curSpecies;
    // POP_BC;
    // POP_DE;
    // POP_HL;

    // LD_A_addr(wEvolutionCanceled);
    // AND_A_A;
    // RET_Z ;
    if(wram->wEvolutionCanceled == 0)
        return false;

    // SCF;
    // RET;
    return true;
}
