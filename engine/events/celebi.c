#include "../../constants.h"
#include "celebi.h"
#include "../gfx/sprites.h"
#include "../../home/sprite_anims.h"
#include "../../home/copy.h"
#include "../../home/delay.h"
#include "../../home/sine.h"

#define SPECIALCELEBIEVENT_CELEBI (0x84)

void UnusedForestTreeFrames(void){
//  //  unreferenced
// INCBIN "gfx/tilesets/forest-tree/1.2bpp"
// INCBIN "gfx/tilesets/forest-tree/2.2bpp"
// INCBIN "gfx/tilesets/forest-tree/3.2bpp"
// INCBIN "gfx/tilesets/forest-tree/4.2bpp"
}

static void CelebiShrineEvent_RestorePlayerSprite_DespawnLeaves(void){
    // LD_HL(wVirtualOAMSprite00TileID);
    struct SpriteOAM* hl = wram->wVirtualOAMSprite;
    // XOR_A_A;
    uint8_t a = 0;
    // LD_C(4);
    uint8_t c = 4;

    do {
    // OAMloop:
        // LD_hli_A;  // tile id
        hl->tileID = a;
        // for(int rept = 0; rept < SPRITEOAMSTRUCT_LENGTH - 1; rept++){
        // INC_HL;
        // }
        hl++;
        // INC_A;
        a++;
        // DEC_C;
        // IF_NZ goto OAMloop;
    } while(--c != 0);
    // LD_HL(wVirtualOAMSprite04);
    // LD_BC(wVirtualOAMEnd - wVirtualOAMSprite04);
    // XOR_A_A;
    // CALL(aByteFill);
    ByteFill(wram->wVirtualOAMSprite, sizeof(wram->wVirtualOAMSprite) - 4 * sizeof(wram->wVirtualOAMSprite[0]), 0x0);
    // RET;
}

void CelebiShrineEvent(void){
    // CALL(aDelayFrame);
    // LD_A_addr(wVramState);
    // PUSH_AF;
    uint8_t vramState = wram->wVramState;
    // XOR_A_A;
    // LD_addr_A(wVramState);
    wram->wVramState = 0x0;
    // CALL(aLoadCelebiGFX);
    LoadCelebiGFX();
    // depixel4(0, 10, 7, 0);
    // LD_A(SPRITE_ANIM_INDEX_CELEBI);
    // CALL(aInitSpriteAnimStruct);
    struct SpriteAnim* bc = InitSpriteAnimStruct(SPRITE_ANIM_INDEX_CELEBI, pixel4(0, 10, 7, 0));
    // LD_HL(SPRITEANIMSTRUCT_TILE_ID);
    // ADD_HL_BC;
    // LD_hl(SPECIALCELEBIEVENT_CELEBI);
    bc->tileID = SPECIALCELEBIEVENT_CELEBI;
    // LD_HL(SPRITEANIMSTRUCT_ANIM_SEQ_ID);
    // ADD_HL_BC;
    // LD_hl(SPRITE_ANIM_SEQ_CELEBI);
    bc->animSeqID = SPRITE_ANIM_SEQ_CELEBI;
    // LD_HL(SPRITEANIMSTRUCT_VAR4);
    // ADD_HL_BC;
    // LD_A(0x80);
    // LD_hl_A;
    bc->var4 = 0x80;
    // LD_A(160);  // frame count
    // LD_addr_A(wFrameCounter);
    wram->wFrameCounter = 160;
    // LD_D(0x0);
    uint8_t d = 0x0;

    while(!bit_test(wram->wJumptableIndex, 7)){
    // loop:
        // LD_A_addr(wJumptableIndex);
        // BIT_A(7);
        // IF_NZ goto done;
        // PUSH_BC;
        // CALL(aGetCelebiSpriteTile);
        d = GetCelebiSpriteTile(bc, d);
        // INC_D;
        d++;
        // PUSH_DE;
        // LD_A(36 * SPRITEOAMSTRUCT_LENGTH);
        // LD_addr_A(wCurSpriteOAMAddr);
        wram->wCurSpriteOAMAddr = 36 * SPRITEOAMSTRUCT_LENGTH;
        // FARCALL(aDoNextFrameForAllSprites);
        DoNextFrameForAllSprites();
        // CALL(aCelebiEvent_CountDown);
        CelebiEvent_CountDown();
        // LD_C(2);
        // CALL(aDelayFrames);
        DelayFrames(2);
        // POP_DE;
        // POP_BC;
        // goto loop;
    }

// done:
    // POP_AF;
    // LD_addr_A(wVramState);
    wram->wVramState = vramState;
    // CALL(aCelebiShrineEvent_RestorePlayerSprite_DespawnLeaves);
    CelebiShrineEvent_RestorePlayerSprite_DespawnLeaves();
    // CALL(aCelebiEvent_SetBattleType);
    CelebiEvent_SetBattleType();
    // RET;
    return;
}

void LoadCelebiGFX(void){
    // FARCALL(aClearSpriteAnims);
    ClearSpriteAnims();
    // LD_DE(mSpecialCelebiLeafGFX);
    // LD_HL(vTiles1);
    // LD_BC((BANK(aSpecialCelebiLeafGFX) << 8) | 4);
    // CALL(aRequest2bpp);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles1, SpecialCelebiLeafGFX, 0, 4);
    // LD_DE(mSpecialCelebiGFX);
    // LD_HL(vTiles0 + LEN_2BPP_TILE * SPECIALCELEBIEVENT_CELEBI);
    // LD_BC((BANK(aSpecialCelebiGFX) << 8) | 4 * 4);
    // CALL(aRequest2bpp);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles0 + LEN_2BPP_TILE * SPECIALCELEBIEVENT_CELEBI, SpecialCelebiGFX, 0, 4 * 4);
    // XOR_A_A;
    // LD_addr_A(wJumptableIndex);
    wram->wJumptableIndex = 0x0;
    // RET;

}

void CelebiEvent_CountDown(void){
    // LD_HL(wFrameCounter);
    // LD_A_hl;
    // AND_A_A;
    // IF_Z goto done;
    if(wram->wFrameCounter != 0){
        // DEC_hl;
        wram->wFrameCounter--;
        // RET;
        return;
    }

// done:
    // LD_HL(wJumptableIndex);
    // SET_hl(7);
    bit_set(wram->wJumptableIndex, 7);
    // RET;
}

void CelebiEvent_SpawnLeaf(void){
//  //  unreferenced
    LD_HL(wFrameCounter2);
    LD_A_hl;
    INC_hl;
    AND_A(0x7);
    RET_NZ ;
    LD_A_hl;
    AND_A(0x18);
    SLA_A;
    ADD_A(0x40);
    LD_D_A;
    LD_E(0x0);
    LD_A(SPRITE_ANIM_INDEX_FLY_LEAF);  // fly land
    CALL(aInitSpriteAnimStruct);
    LD_HL(SPRITEANIMSTRUCT_TILE_ID);
    ADD_HL_BC;
    LD_hl(0x80);
    RET;

}

const char SpecialCelebiLeafGFX[] = "gfx/overworld/cut_grass.png";
const char SpecialCelebiGFX[] = "gfx/overworld/celebi.png";

static void UpdateCelebiPosition_FreezeCelebiPosition(struct SpriteAnim* bc){
    // POP_AF;
    // LD_HL(SPRITEANIMSTRUCT_FRAMESET_ID);
    // ADD_HL_BC;
    // LD_A(SPRITE_ANIM_FRAMESET_CELEBI_LEFT);
    // CALL(aReinitSpriteAnimFrame);
    ReinitSpriteAnimFrame(bc, SPRITE_ANIM_FRAMESET_CELEBI_LEFT);
    // RET;
}

void UpdateCelebiPosition(struct SpriteAnim* bc){
    // LD_HL(SPRITEANIMSTRUCT_XOFFSET);
    // ADD_HL_BC;
    // LD_A_hl;
    // PUSH_AF;
    uint8_t xOffset = bc->xOffset;
    // LD_HL(SPRITEANIMSTRUCT_YCOORD);
    // ADD_HL_BC;
    // LD_A_hl;
    // CP_A(8 * 10 + 2);
    // JP_NC (mUpdateCelebiPosition_FreezeCelebiPosition);
    if(bc->yCoord >= 8 * 10 + 2)
        return UpdateCelebiPosition_FreezeCelebiPosition(bc);
    // LD_HL(SPRITEANIMSTRUCT_YCOORD);
    // ADD_HL_BC;
    // INC_hl;
    bc->yCoord++;
    // LD_HL(SPRITEANIMSTRUCT_VAR4);
    // ADD_HL_BC;
    // LD_A_hl;
    // LD_D_A;
    uint8_t d = bc->var4;
    // CP_A(0x3a);
    // IF_C goto skip;
    // IF_Z goto skip;
    if(d > 0x3a){
        // SUB_A(0x3);
        // LD_hl_A;
        bc->var4 = d - 0x3;
    }

// skip:
    // LD_HL(SPRITEANIMSTRUCT_VAR3);
    // ADD_HL_BC;
    // LD_A_hl;
    // INC_hl;
    uint8_t var3 = bc->var3++;
    // CALL(aCelebiEvent_Cosine);
    // LD_HL(SPRITEANIMSTRUCT_XOFFSET);
    // ADD_HL_BC;
    // LD_hl_A;
    bc->xOffset = Cosine(var3, d);
    // LD_D_A;
    d = bc->xOffset;
    // LD_HL(SPRITEANIMSTRUCT_XCOORD);
    // ADD_HL_BC;
    // ADD_A_hl;
    uint8_t x = bc->xCoord + d;
    // CP_A(8 * 11 + 4);
    // IF_NC goto ShiftY;
    // CP_A(8 *  8 + 4);
    // IF_NC goto ReinitSpriteAnimFrame;
    if(x >= 8 * 11 + 4 || x < 8 *  8 + 4) {
    // ShiftY:
        // POP_AF;
        // PUSH_AF;
        // CP_A_D;
        // IF_NC goto moving_left;
        if(xOffset >= d) {
        // moving_left:
            // LD_HL(SPRITEANIMSTRUCT_XCOORD);
            // ADD_HL_BC;
            // ADD_A_hl;
            // CP_A(8 * 10);
            // IF_NC goto float_up;
            if(bc->xCoord + xOffset >= 8 * 10){
            // float_up:
                // LD_HL(SPRITEANIMSTRUCT_YCOORD);
                // ADD_HL_BC;
                // LD_A_hl;
                // ADD_A(0x1);
                // LD_hl_A;
                bc->yCoord += 0x1;
            }
            else {
            // float_down:
                // LD_HL(SPRITEANIMSTRUCT_YCOORD);
                // ADD_HL_BC;
                // LD_A_hl;
                // SUB_A(0x2);
                // LD_hl_A;
                bc->yCoord -= 0x2;
                // goto ReinitSpriteAnimFrame;
            }
        }
        else {
            // LD_HL(SPRITEANIMSTRUCT_XCOORD);
            // ADD_HL_BC;
            // ADD_A_hl;
            // CP_A(8 * 10);
            // IF_C goto float_up;
            // goto float_down;
            if(bc->xCoord + xOffset < 8 * 10){
            // float_up:
                // LD_HL(SPRITEANIMSTRUCT_YCOORD);
                // ADD_HL_BC;
                // LD_A_hl;
                // ADD_A(0x1);
                // LD_hl_A;
                bc->yCoord += 0x1;
            }
            else {
            // float_down:
                // LD_HL(SPRITEANIMSTRUCT_YCOORD);
                // ADD_HL_BC;
                // LD_A_hl;
                // SUB_A(0x2);
                // LD_hl_A;
                bc->yCoord -= 0x2;
                // goto ReinitSpriteAnimFrame;
            }
        }
    }

// ReinitSpriteAnimFrame:
    // POP_AF;
    // LD_HL(SPRITEANIMSTRUCT_XCOORD);
    // ADD_HL_BC;
    // ADD_A_hl;
    // CP_A(8 * 10);
    // IF_C goto left;
    // CP_A(-(8 * 3 + 2));
    // IF_NC goto left;
    if(bc->xCoord + xOffset >= 8 * 10 && bc->xCoord + xOffset < (uint8_t)-(8 * 3 + 2)) {
        // LD_HL(SPRITEANIMSTRUCT_FRAMESET_ID);
        // ADD_HL_BC;
        // LD_A(SPRITE_ANIM_FRAMESET_CELEBI_RIGHT);
        // CALL(aReinitSpriteAnimFrame);
        ReinitSpriteAnimFrame(bc, SPRITE_ANIM_FRAMESET_CELEBI_RIGHT);
        // goto done;
    }
    else {
    // left:
        // LD_HL(SPRITEANIMSTRUCT_FRAMESET_ID);
        // ADD_HL_BC;
        // LD_A(SPRITE_ANIM_FRAMESET_CELEBI_LEFT);
        // CALL(aReinitSpriteAnimFrame);
        ReinitSpriteAnimFrame(bc, SPRITE_ANIM_FRAMESET_CELEBI_LEFT);
    }

// done:
    // RET;
}

uint8_t GetCelebiSpriteTile(struct SpriteAnim* bc, uint8_t d){
    // PUSH_HL;
    // PUSH_BC;
    // PUSH_DE;
    // LD_A_D;
    // LD_D(0x3);
    // LD_E_D;
    // CP_A(0x0);
    // IF_Z goto Frame1;
    uint8_t tile;
    if(d == 0x0){
    // Frame1:
        // LD_A(SPECIALCELEBIEVENT_CELEBI);
        // goto load_tile;
        tile = SPECIALCELEBIEVENT_CELEBI;
    }
    // CP_A_D;
    // IF_Z goto Frame2;
    else if(d == 0x3){
    // Frame2:
        // LD_A(SPECIALCELEBIEVENT_CELEBI + 4);
        // goto load_tile;
        tile = SPECIALCELEBIEVENT_CELEBI + 4;
    }
    // CALL(aGetCelebiSpriteTile_AddE);
    // CP_A_D;
    // IF_Z goto Frame3;
    else if(d == 0x6){
    // Frame3:
        // LD_A(SPECIALCELEBIEVENT_CELEBI + 8);
        // goto load_tile;
        tile = SPECIALCELEBIEVENT_CELEBI + 8;
    }
    // CALL(aGetCelebiSpriteTile_AddE);
    // CP_A_D;
    // IF_Z goto Frame4;
    else if(d == 0x9){
    // Frame4:
        // LD_A(SPECIALCELEBIEVENT_CELEBI + 12);
        tile = SPECIALCELEBIEVENT_CELEBI + 12;
    }
    // CALL(aGetCelebiSpriteTile_AddE);
    // CP_A_D;
    // IF_C goto done;
    else if(d < 0xc){
        return d;
    }
    else {
        // goto restart;
    // restart:
        // POP_DE;
        // LD_D(0xff);
        d = 0xff;
        // PUSH_DE;
        return d;
    }

// load_tile:
    // LD_HL(SPRITEANIMSTRUCT_TILE_ID);
    // ADD_HL_BC;
    // LD_hl_A;
    bc->tileID = tile;
    // goto done;

// done:
    // POP_DE;
    // POP_BC;
    // POP_HL;
    // RET;

// AddE:
    // PUSH_AF;
    // LD_A_D;
    // ADD_A_E;
    // LD_D_A;
    // POP_AF;
    // RET;
    return d;
}

void CelebiEvent_SetBattleType(void){
    // LD_A(BATTLETYPE_CELEBI);
    // LD_addr_A(wBattleType);
    // RET;
    wram->wBattleType = BATTLETYPE_CELEBI;
}

void CheckCaughtCelebi(void){
    // LD_A_addr(wBattleResult);
    // BIT_A(BATTLERESULT_CAUGHT_CELEBI);
    // IF_Z goto false_;
    if(bit_test(wram->wBattleResult, BATTLERESULT_CAUGHT_CELEBI)) {
        // LD_A(TRUE);
        // LD_addr_A(wScriptVar);
        // goto done;
        wram->wScriptVar = TRUE;
    }
    else {
    // false_:
        // XOR_A_A;  // FALSE
        // LD_addr_A(wScriptVar);
        wram->wScriptVar = FALSE;
    }

// done:
    // RET;
}
