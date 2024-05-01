#include "../../constants.h"
#include "helpers.h"
#include "../../data/battle_anims/framesets.h"
#include "../../data/battle_anims/oam.h"

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
