#include "../../constants.h"
#include "core.h"

void QueueBattleAnimation(void){
    LD_HL(wActiveAnimObjects);
    LD_E(NUM_ANIM_OBJECTS);

loop:
    LD_A_hl;
    AND_A_A;
    IF_Z goto done;
    LD_BC(BATTLEANIMSTRUCT_LENGTH);
    ADD_HL_BC;
    DEC_E;
    IF_NZ goto loop;
    SCF;
    RET;


done:
    LD_C_L;
    LD_B_H;
    LD_HL(wLastAnimObjectIndex);
    INC_hl;
    CALL(aInitBattleAnimation);
    RET;

}

void DeinitBattleAnimation(void){
    LD_HL(BATTLEANIMSTRUCT_INDEX);
    ADD_HL_BC;
    LD_hl(0x0);
    RET;

}

void InitBattleAnimation(void){
    LD_A_addr(wBattleObjectTempID);
    LD_E_A;
    LD_D(0);
    LD_HL(mBattleAnimObjects);
    for(int rept = 0; rept < BATTLEANIMOBJ_LENGTH; rept++){
    ADD_HL_DE;
    }
    LD_E_L;
    LD_D_H;
    LD_HL(BATTLEANIMSTRUCT_INDEX);
    ADD_HL_BC;
    LD_A_addr(wLastAnimObjectIndex);
    LD_hli_A;  // BATTLEANIMSTRUCT_INDEX
    LD_A_de;
    INC_DE;
    LD_hli_A;  // BATTLEANIMSTRUCT_OAMFLAGS
    LD_A_de;
    INC_DE;
    LD_hli_A;  // BATTLEANIMSTRUCT_FIX_Y
    LD_A_de;
    INC_DE;
    LD_hli_A;  // BATTLEANIMSTRUCT_FRAMESET_ID
    LD_A_de;
    INC_DE;
    LD_hli_A;  // BATTLEANIMSTRUCT_FUNCTION
    LD_A_de;
    INC_DE;
    LD_hli_A;  // BATTLEANIMSTRUCT_PALETTE
    LD_A_de;
    CALL(aGetBattleAnimTileOffset);
    LD_hli_A;  // BATTLEANIMSTRUCT_TILEID
    LD_A_addr(wBattleObjectTempXCoord);
    LD_hli_A;  // BATTLEANIMSTRUCT_XCOORD
    LD_A_addr(wBattleObjectTempYCoord);
    LD_hli_A;  // BATTLEANIMSTRUCT_YCOORD
    XOR_A_A;
    LD_hli_A;  // BATTLEANIMSTRUCT_XOFFSET
    LD_hli_A;  // BATTLEANIMSTRUCT_YOFFSET
    LD_A_addr(wBattleObjectTempParam);
    LD_hli_A;  // BATTLEANIMSTRUCT_PARAM
    XOR_A_A;
    LD_hli_A;  // BATTLEANIMSTRUCT_DURATION
    DEC_A;
    LD_hli_A;  // BATTLEANIMSTRUCT_FRAME
    XOR_A_A;
    LD_hli_A;  // BATTLEANIMSTRUCT_JUMPTABLE_INDEX
    LD_hli_A;  // BATTLEANIMSTRUCT_VAR1
    LD_hl_A;  // BATTLEANIMSTRUCT_VAR2
    RET;

}

// #define delanim_command 0xFC
// #define dowait_command 0xFD

void BattleAnimOAMUpdate(void){
    CALL(aInitBattleAnimBuffer);
    CALL(aGetBattleAnimFrame);
    CP_A(dowait_command);
    JP_Z (mBattleAnimOAMUpdate_done);
    CP_A(delanim_command);
    JP_Z (mBattleAnimOAMUpdate_delete);

    PUSH_AF;
    LD_HL(wBattleAnimTempOAMFlags);
    LD_A_addr(wBattleAnimTempFrameOAMFlags);
    XOR_A_hl;
    AND_A(PRIORITY | Y_FLIP | X_FLIP);
    LD_hl_A;
    POP_AF;

    PUSH_BC;
    CALL(aGetBattleAnimOAMPointer);
    LD_A_addr(wBattleAnimTempTileID);
    ADD_A_hl;  // tile offset
    LD_addr_A(wBattleAnimTempTileID);
    INC_HL;
    LD_A_hli;  // oam data length
    LD_C_A;
    LD_A_hli;  // oam data pointer
    LD_H_hl;
    LD_L_A;
    LD_A_addr(wBattleAnimOAMPointerLo);
    LD_E_A;
    LD_D(HIGH(wVirtualOAM));


loop:
// Y Coord
    LD_A_addr(wBattleAnimTempYCoord);
    LD_B_A;
    LD_A_addr(wBattleAnimTempYOffset);
    ADD_A_B;
    LD_B_A;
    PUSH_HL;
    LD_A_hl;
    LD_HL(wBattleAnimTempOAMFlags);
    BIT_hl(OAM_Y_FLIP);
    IF_Z goto no_yflip;
    ADD_A(0x8);
    XOR_A(0xff);
    INC_A;

no_yflip:
    POP_HL;
    ADD_A_B;
    LD_de_A;

// X Coord
    INC_HL;
    INC_DE;
    LD_A_addr(wBattleAnimTempXCoord);
    LD_B_A;
    LD_A_addr(wBattleAnimTempXOffset);
    ADD_A_B;
    LD_B_A;
    PUSH_HL;
    LD_A_hl;
    LD_HL(wBattleAnimTempOAMFlags);
    BIT_hl(OAM_X_FLIP);
    IF_Z goto no_xflip;
    ADD_A(0x8);
    XOR_A(0xff);
    INC_A;

no_xflip:
    POP_HL;
    ADD_A_B;
    LD_de_A;

// Tile ID
    INC_HL;
    INC_DE;
    LD_A_addr(wBattleAnimTempTileID);
    ADD_A(BATTLEANIM_BASE_TILE);
    ADD_A_hl;
    LD_de_A;

// Attributes
    INC_HL;
    INC_DE;
    LD_A_addr(wBattleAnimTempOAMFlags);
    LD_B_A;
    LD_A_hl;
    XOR_A_B;
    AND_A(PRIORITY | Y_FLIP | X_FLIP);
    LD_B_A;
    LD_A_hl;
    AND_A(OBP_NUM);
    OR_A_B;
    LD_B_A;
    LD_A_addr(wBattleAnimTempPalette);
    AND_A(PALETTE_MASK | VRAM_BANK_1);
    OR_A_B;
    LD_de_A;

    INC_HL;
    INC_DE;
    LD_A_E;
    LD_addr_A(wBattleAnimOAMPointerLo);
    CP_A(LOW(wVirtualOAMEnd));
    IF_NC goto exit_set_carry;
    DEC_C;
    IF_NZ goto loop;
    POP_BC;
    goto done;


delete:
    CALL(aDeinitBattleAnimation);


done:
    AND_A_A;
    RET;


exit_set_carry:
    POP_BC;
    SCF;
    RET;

}

void InitBattleAnimBuffer(void){
    LD_HL(BATTLEANIMSTRUCT_OAMFLAGS);
    ADD_HL_BC;
    LD_A_hl;

    AND_A(PRIORITY);
    LD_addr_A(wBattleAnimTempOAMFlags);
    XOR_A_A;
    LD_addr_A(wBattleAnimTempFrameOAMFlags);
    LD_HL(BATTLEANIMSTRUCT_PALETTE);
    ADD_HL_BC;
    LD_A_hl;
    LD_addr_A(wBattleAnimTempPalette);
    LD_HL(BATTLEANIMSTRUCT_FIX_Y);
    ADD_HL_BC;
    LD_A_hl;
    LD_addr_A(wBattleAnimTempFixY);
    LD_HL(BATTLEANIMSTRUCT_TILEID);
    ADD_HL_BC;
    LD_A_hli;
    LD_addr_A(wBattleAnimTempTileID);
    LD_A_hli;
    LD_addr_A(wBattleAnimTempXCoord);
    LD_A_hli;
    LD_addr_A(wBattleAnimTempYCoord);
    LD_A_hli;
    LD_addr_A(wBattleAnimTempXOffset);
    LD_A_hli;
    LD_addr_A(wBattleAnimTempYOffset);

    LDH_A_addr(hBattleTurn);
    AND_A_A;
    RET_Z ;

    LD_HL(BATTLEANIMSTRUCT_OAMFLAGS);
    ADD_HL_BC;
    LD_A_hl;
    LD_addr_A(wBattleAnimTempOAMFlags);
    BIT_hl(0);
    RET_Z ;

    LD_HL(BATTLEANIMSTRUCT_XCOORD);
    ADD_HL_BC;
    LD_A_hli;
    LD_D_A;
    LD_A((-10 * 8) + 4);
    SUB_A_D;
    LD_addr_A(wBattleAnimTempXCoord);
    LD_A_hli;
    LD_D_A;
    LD_A_addr(wBattleAnimTempFixY);
    CP_A(0xff);
    IF_NZ goto check_kinesis_softboiled_milkdrink;
    LD_A(5 * 8);
    ADD_A_D;
    goto done;


check_kinesis_softboiled_milkdrink:
    SUB_A_D;
    PUSH_AF;
    LD_A_addr(wFXAnimID + 1);
    OR_A_A;
    IF_NZ goto no_sub;
    LD_A_addr(wFXAnimID);
    CP_A(KINESIS);
    IF_Z goto do_sub;
    CP_A(SOFTBOILED);
    IF_Z goto do_sub;
    CP_A(MILK_DRINK);
    IF_NZ goto no_sub;

do_sub:
    POP_AF;
    SUB_A(1 * 8);
    goto done;


no_sub:
    POP_AF;

done:
    LD_addr_A(wBattleAnimTempYCoord);
    LD_A_hli;
    XOR_A(0xff);
    INC_A;
    LD_addr_A(wBattleAnimTempXOffset);
    RET;

}

void GetBattleAnimTileOffset(void){
    PUSH_HL;
    PUSH_BC;
    LD_HL(wBattleAnimTileDict);
    LD_B_A;
    LD_C(NUM_BATTLEANIMTILEDICT_ENTRIES);

loop:
    LD_A_hli;
    CP_A_B;
    IF_Z goto load;
    INC_HL;
    DEC_C;
    IF_NZ goto loop;
    XOR_A_A;
    goto done;


load:
    LD_A_hl;

done:
    POP_BC;
    POP_HL;
    RET;

}

void v_ExecuteBGEffects(void){
    CALLFAR(aExecuteBGEffects);
    RET;

}

void v_QueueBGEffect(void){
    CALLFAR(aQueueBGEffect);
    RET;

// INCLUDE "data/battle_anims/objects.asm"

}
