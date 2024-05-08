#include "../../constants.h"
#include "helpers.h"
#include "../../data/battle_anims/framesets.h"
#include "../../data/battle_anims/oam.h"
#include "../../data/battle_anims/object_gfx.h"

void ReinitBattleAnimFrameset(void){
    LD_HL(BATTLEANIMSTRUCT_FRAMESET_ID);
    ADD_HL_BC;
    LD_hl_A;
    LD_HL(BATTLEANIMSTRUCT_DURATION);
    ADD_HL_BC;
    LD_hl(0);
    LD_HL(BATTLEANIMSTRUCT_FRAME);
    ADD_HL_BC;
    LD_hl(-1);
    RET;

}

void ReinitBattleAnimFrameset_Conv(struct BattleAnim* bc, uint8_t a){
    // LD_HL(BATTLEANIMSTRUCT_FRAMESET_ID);
    // ADD_HL_BC;
    // LD_hl_A;
    bc->framesetId = a;
    // LD_HL(BATTLEANIMSTRUCT_DURATION);
    // ADD_HL_BC;
    // LD_hl(0);
    bc->duration = 0;
    // LD_HL(BATTLEANIMSTRUCT_FRAME);
    // ADD_HL_BC;
    // LD_hl(-1);
    bc->frame = (uint8_t)-1;
    // RET;
}

void GetBattleAnimFrame(void){

loop:
    LD_HL(BATTLEANIMSTRUCT_DURATION);
    ADD_HL_BC;
    LD_A_hl;
    AND_A_A;
    IF_Z goto next_frame;
    DEC_hl;
    CALL(aGetBattleAnimFrame_GetPointer);
    LD_A_hli;
    PUSH_AF;
    goto okay;


next_frame:
    LD_HL(BATTLEANIMSTRUCT_FRAME);
    ADD_HL_BC;
    INC_hl;
    CALL(aGetBattleAnimFrame_GetPointer);
    LD_A_hli;
    CP_A(dorestart_command);
    IF_Z goto restart;
    CP_A(endanim_command);
    IF_Z goto repeat_last;

    PUSH_AF;
    LD_A_hl;
    PUSH_HL;
    AND_A(~(Y_FLIP << 1 | X_FLIP << 1));
    LD_HL(BATTLEANIMSTRUCT_DURATION);
    ADD_HL_BC;
    LD_hl_A;
    POP_HL;

okay:
    LD_A_hl;
    AND_A(Y_FLIP << 1 | X_FLIP << 1);  // The << 1 is compensated in the "frame" macro
    SRL_A;
    LD_addr_A(wBattleAnimTempFrameOAMFlags);
    POP_AF;
    RET;


repeat_last:
    XOR_A_A;
    LD_HL(BATTLEANIMSTRUCT_DURATION);
    ADD_HL_BC;
    LD_hl_A;

    LD_HL(BATTLEANIMSTRUCT_FRAME);
    ADD_HL_BC;
    DEC_hl;
    DEC_hl;
    goto loop;


restart:
    XOR_A_A;
    LD_HL(BATTLEANIMSTRUCT_DURATION);
    ADD_HL_BC;
    LD_hl_A;

    DEC_A;
    LD_HL(BATTLEANIMSTRUCT_FRAME);
    ADD_HL_BC;
    LD_hl_A;
    goto loop;


GetPointer:
    LD_HL(BATTLEANIMSTRUCT_FRAMESET_ID);
    ADD_HL_BC;
    LD_E_hl;
    LD_D(0);
    LD_HL(mBattleAnimFrameData);
    ADD_HL_DE;
    ADD_HL_DE;
    LD_E_hl;
    INC_HL;
    LD_D_hl;
    LD_HL(BATTLEANIMSTRUCT_FRAME);
    ADD_HL_BC;
    LD_L_hl;
    LD_H(0);
    ADD_HL_HL;
    ADD_HL_DE;
    RET;

}

static const uint8_t* GetBattleAnimFrame_GetPointer(struct BattleAnim* bc) {
    // LD_HL(BATTLEANIMSTRUCT_FRAMESET_ID);
    // ADD_HL_BC;
    // LD_E_hl;
    // LD_D(0);
    // LD_HL(mBattleAnimFrameData);
    // ADD_HL_DE;
    // ADD_HL_DE;
    // LD_E_hl;
    // INC_HL;
    // LD_D_hl;
    const uint8_t* de = BattleAnimFrameData[bc->framesetId];
    // LD_HL(BATTLEANIMSTRUCT_FRAME);
    // ADD_HL_BC;
    // LD_L_hl;
    // LD_H(0);
    // ADD_HL_HL;
    // ADD_HL_DE;
    // RET;
    return de + 2 * bc->frame;
}

uint8_t GetBattleAnimFrame_Conv(struct BattleAnim* bc){
    while(1) {
    // loop:
        // LD_HL(BATTLEANIMSTRUCT_DURATION);
        // ADD_HL_BC;
        // LD_A_hl;
        // AND_A_A;
        // IF_Z goto next_frame;
        uint8_t a;
        const uint8_t* hl;
        if(bc->duration != 0) {
            // DEC_hl;
            bc->duration--;
            // CALL(aGetBattleAnimFrame_GetPointer);
            // LD_A_hli;
            hl = GetBattleAnimFrame_GetPointer(bc);
            // PUSH_AF;
            a = *(hl++);
            // goto okay;
        }
        else {
        // next_frame:
            // LD_HL(BATTLEANIMSTRUCT_FRAME);
            // ADD_HL_BC;
            // INC_hl;
            bc->frame++;
            // CALL(aGetBattleAnimFrame_GetPointer);
            hl = GetBattleAnimFrame_GetPointer(bc);
            // LD_A_hli;
            a = *(hl++);
            // CP_A(dorestart_command);
            // IF_Z goto restart;
            if(a == dorestart_command) {
            // restart:
                // XOR_A_A;
                // LD_HL(BATTLEANIMSTRUCT_DURATION);
                // ADD_HL_BC;
                // LD_hl_A;
                bc->duration = 0;

                // DEC_A;
                // LD_HL(BATTLEANIMSTRUCT_FRAME);
                // ADD_HL_BC;
                // LD_hl_A;
                bc->frame = (uint8_t)-1;
                // goto loop;
                continue;
            }
            // CP_A(endanim_command);
            // IF_Z goto repeat_last;
            else if(a == endanim_command) {
            // repeat_last:
                // XOR_A_A;
                // LD_HL(BATTLEANIMSTRUCT_DURATION);
                // ADD_HL_BC;
                // LD_hl_A;
                bc->duration = 0;

                // LD_HL(BATTLEANIMSTRUCT_FRAME);
                // ADD_HL_BC;
                // DEC_hl;
                // DEC_hl;
                bc->frame -= 2;
                // goto loop;
                continue;
            }

            // PUSH_AF;
            // LD_A_hl;
            // PUSH_HL;
            // AND_A(~(Y_FLIP << 1 | X_FLIP << 1));
            // LD_HL(BATTLEANIMSTRUCT_DURATION);
            // ADD_HL_BC;
            // LD_hl_A;
            bc->duration = (*hl) & ~(Y_FLIP << 1 | X_FLIP << 1);
            // POP_HL;
        }

    // okay:
        // LD_A_hl;
        // AND_A(Y_FLIP << 1 | X_FLIP << 1);  // The << 1 is compensated in the "frame" macro
        // SRL_A;
        // LD_addr_A(wBattleAnimTempFrameOAMFlags);
        wram->wBattleAnimTempFrameOAMFlags = ((*hl) & (Y_FLIP << 1 | X_FLIP << 1)) >> 1;
        // POP_AF;
        // RET;
        return a;
    }
}

void GetBattleAnimOAMPointer(void){
    LD_L_A;
    LD_H(0);
    LD_DE(mBattleAnimOAMData);
    ADD_HL_HL;
    ADD_HL_HL;
    ADD_HL_DE;
    RET;
}

const struct BattleOAMData* GetBattleAnimOAMPointer_Conv(uint8_t a){
    // LD_L_A;
    // LD_H(0);
    // LD_DE(mBattleAnimOAMData);
    // ADD_HL_HL;
    // ADD_HL_HL;
    // ADD_HL_DE;
    // RET;
    return BattleAnimOAMData + a;
}

void LoadBattleAnimGFX(void){
    PUSH_HL;
    LD_L_A;
    LD_H(0);
    ADD_HL_HL;
    ADD_HL_HL;
    LD_DE(mAnimObjGFX);
    ADD_HL_DE;
    LD_C_hl;
    INC_HL;
    LD_B_hl;
    INC_HL;
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    POP_DE;
    PUSH_BC;
    CALL(aDecompressRequest2bpp);
    POP_BC;
    RET;

// INCLUDE "data/battle_anims/framesets.asm"

// INCLUDE "data/battle_anims/oam.asm"

// INCLUDE "data/battle_anims/object_gfx.asm"

}

uint8_t LoadBattleAnimGFX_Conv(uint8_t* de, uint8_t a){
    // PUSH_HL;
    // LD_L_A;
    // LD_H(0);
    // ADD_HL_HL;
    // ADD_HL_HL;
    // LD_DE(mAnimObjGFX);
    // ADD_HL_DE;
    const struct BattleAnimGFX* gfx = AnimObjGFX + a;
    // LD_C_hl;
    // INC_HL;
    // LD_B_hl;
    // INC_HL;
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // POP_DE;
    // PUSH_BC;
    // CALL(aDecompressRequest2bpp);
    // POP_BC;
    switch(a) {
    case ANIM_GFX_STATUS:
    case ANIM_GFX_HIT:
    case ANIM_GFX_PLANT:
    // case ANIM_GFX_WATER:
    case ANIM_GFX_ROCKS:
    case ANIM_GFX_NOISE:
    case ANIM_GFX_EXPLOSION:
    case ANIM_GFX_LIGHTNING:
    case ANIM_GFX_REFLECT:
    case ANIM_GFX_EGG:
        LoadPNG2bppAssetSectionToVRAM_SkipEmptyTiles(de, gfx->gfxPath, 0x0, gfx->tiles);
        break;
    case ANIM_GFX_POKE_BALL:
        LoadPNG2bppAssetSectionToVRAM(de, gfx->gfxPath, 0x0, 1);
        LoadPNG2bppAssetSectionToVRAM(de + 1 * LEN_2BPP_TILE, gfx->gfxPath, 0x2, 1);
        LoadPNG2bppAssetSectionToVRAM(de + 2 * LEN_2BPP_TILE, gfx->gfxPath, 0x4, 4);
        LoadPNG2bppAssetSectionToVRAM(de + 6 * LEN_2BPP_TILE, gfx->gfxPath, 0x8, 1);
        LoadPNG2bppAssetSectionToVRAM(de + 7 * LEN_2BPP_TILE, gfx->gfxPath, 0xa, 1);
        break;
    case ANIM_GFX_OBJECTS:
        LoadPNG2bppAssetSectionToVRAM(de, gfx->gfxPath, 0x0, 8);
        LoadPNG2bppAssetSectionToVRAM(de + 8 * LEN_2BPP_TILE, gfx->gfxPath, 0x8, 1);
        LoadPNG2bppAssetSectionToVRAM(de + 9 * LEN_2BPP_TILE, gfx->gfxPath, 0xa, 1);
        LoadPNG2bppAssetSectionToVRAM(de + 10 * LEN_2BPP_TILE, gfx->gfxPath, 0xc, 1);
        LoadPNG2bppAssetSectionToVRAM(de + 11 * LEN_2BPP_TILE, gfx->gfxPath, 0xe, 1);
        LoadPNG2bppAssetSectionToVRAM(de + 12 * LEN_2BPP_TILE, gfx->gfxPath, 0x10, 1);
        LoadPNG2bppAssetSectionToVRAM(de + 13 * LEN_2BPP_TILE, gfx->gfxPath, 0x12, 1);
        LoadPNG2bppAssetSectionToVRAM(de + 14 * LEN_2BPP_TILE, gfx->gfxPath, 0x14, 4);
        break;
    case ANIM_GFX_MISC:
        LoadPNG2bppAssetSectionToVRAM(de, gfx->gfxPath, 0x0, 11);
        LoadPNG2bppAssetSectionToVRAM(de + 11 * LEN_2BPP_TILE, gfx->gfxPath, 0xc, 1);
        LoadPNG2bppAssetSectionToVRAM(de + 12 * LEN_2BPP_TILE, gfx->gfxPath, 0xe, 5);
        LoadPNG2bppAssetSectionToVRAM(de + 17 * LEN_2BPP_TILE, gfx->gfxPath, 0x14, 1);
        LoadPNG2bppAssetSectionToVRAM(de + 18 * LEN_2BPP_TILE, gfx->gfxPath, 0x16, 17);
        LoadPNG2bppAssetSectionToVRAM(de + 35 * LEN_2BPP_TILE, gfx->gfxPath, 0x28, 1);
        LoadPNG2bppAssetSectionToVRAM(de + 36 * LEN_2BPP_TILE, gfx->gfxPath, 0x2a, 1);
        LoadPNG2bppAssetSectionToVRAM(de + 37 * LEN_2BPP_TILE, gfx->gfxPath, 0x2c, 3);
        break;
    case ANIM_GFX_BEAM:
        LoadPNG2bppAssetSectionToVRAM(de, gfx->gfxPath, 0x0, 1);
        LoadPNG2bppAssetSectionToVRAM(de + 1 * LEN_2BPP_TILE, gfx->gfxPath, 0x2, 1);
        LoadPNG2bppAssetSectionToVRAM(de + 2 * LEN_2BPP_TILE, gfx->gfxPath, 0x5, 2);
        LoadPNG2bppAssetSectionToVRAM(de + 4 * LEN_2BPP_TILE, gfx->gfxPath, 0xa, 7);
        break;
    default:
        LoadPNG2bppAssetSectionToVRAM(de, gfx->gfxPath, 0x0, gfx->tiles);
        break;
    }
    // RET;
    return gfx->tiles;

// INCLUDE "data/battle_anims/framesets.asm"

// INCLUDE "data/battle_anims/oam.asm"

// INCLUDE "data/battle_anims/object_gfx.asm"

}
