#include "../../constants.h"
#include "sprites.h"

void ClearSpriteAnims(void){
    LD_HL(wSpriteAnimData);
    LD_BC(wSpriteAnimDataEnd - wSpriteAnimData);

loop:
    LD_hl(0);
    INC_HL;
    DEC_BC;
    LD_A_C;
    OR_A_B;
    IF_NZ goto loop;
    RET;

}

void PlaySpriteAnimationsAndDelayFrame(void){
    CALL(aPlaySpriteAnimations);
    CALL(aDelayFrame);
    RET;

}

void PlaySpriteAnimations(void){
    PUSH_HL;
    PUSH_DE;
    PUSH_BC;
    PUSH_AF;

    LD_A(LOW(wVirtualOAM));
    LD_addr_A(wCurSpriteOAMAddr);
    CALL(aDoNextFrameForAllSprites);

    POP_AF;
    POP_BC;
    POP_DE;
    POP_HL;
    RET;

}

void DoNextFrameForAllSprites(void){
    LD_HL(wSpriteAnimationStructs);
    LD_E(NUM_SPRITE_ANIM_STRUCTS);


loop:
    LD_A_hl;
    AND_A_A;
    IF_Z goto next;  // This struct is deinitialized.
    LD_C_L;
    LD_B_H;
    PUSH_HL;
    PUSH_DE;
    CALL(aDoAnimFrame);  // Uses a massive dw
    CALL(aUpdateAnimFrame);
    POP_DE;
    POP_HL;
    IF_C goto done;


next:
    LD_BC(SPRITEANIMSTRUCT_LENGTH);
    ADD_HL_BC;
    DEC_E;
    IF_NZ goto loop;

    LD_A_addr(wCurSpriteOAMAddr);
    LD_L_A;
    LD_H(HIGH(wVirtualOAM));


loop2:
//   //  Clear (wVirtualOAM + [wCurSpriteOAMAddr] --> wVirtualOAMEnd)
    LD_A_L;
    CP_A(LOW(wVirtualOAMEnd));
    IF_NC goto done;
    XOR_A_A;
    LD_hli_A;
    goto loop2;


done:
    RET;

}

void DoNextFrameForFirst16Sprites(void){
    LD_HL(wSpriteAnimationStructs);
    LD_E(NUM_SPRITE_ANIM_STRUCTS);


loop:
    LD_A_hl;
    AND_A_A;
    IF_Z goto next;
    LD_C_L;
    LD_B_H;
    PUSH_HL;
    PUSH_DE;
    CALL(aDoAnimFrame);  // Uses a massive dw
    CALL(aUpdateAnimFrame);
    POP_DE;
    POP_HL;
    IF_C goto done;


next:
    LD_BC(SPRITEANIMSTRUCT_LENGTH);
    ADD_HL_BC;
    DEC_E;
    IF_NZ goto loop;

    LD_A_addr(wCurSpriteOAMAddr);
    LD_L_A;
    LD_H(HIGH(wVirtualOAMSprite16));


loop2:
//   //  Clear (wVirtualOAM + [wCurSpriteOAMAddr] --> Sprites + $40)
    LD_A_L;
    CP_A(LOW(wVirtualOAMSprite16));
    IF_NC goto done;
    XOR_A_A;
    LD_hli_A;
    goto loop2;


done:
    RET;

}

void v_InitSpriteAnimStruct(void){
//  Initialize animation a at pixel x=e, y=d
//  Find if there's any room in the wSpriteAnimationStructs array, which is 10x16
    PUSH_DE;
    PUSH_AF;
    LD_HL(wSpriteAnimationStructs);
    LD_E(NUM_SPRITE_ANIM_STRUCTS);

loop:
    LD_A_hl;
    AND_A_A;
    IF_Z goto found;
    LD_BC(SPRITEANIMSTRUCT_LENGTH);
    ADD_HL_BC;
    DEC_E;
    IF_NZ goto loop;
//  We've reached the end.  There is no more room here.
//  Return carry.
    POP_AF;
    POP_DE;
    SCF;
    RET;


found:
//  Back up the structure address to bc.
    LD_C_L;
    LD_B_H;

//  Increment [wSpriteAnimCount], skipping a 0 value.
    LD_HL(wSpriteAnimCount);
    INC_hl;
    LD_A_hl;
    AND_A_A;
    IF_NZ goto nonzero;
    INC_hl;

nonzero:

//  Get row a of SpriteAnimSeqData, copy the pointer into de
    POP_AF;
    LD_E_A;
    LD_D(0);
    LD_HL(mSpriteAnimSeqData);
    ADD_HL_DE;
    ADD_HL_DE;
    ADD_HL_DE;
    LD_E_L;
    LD_D_H;
//  Set hl to the first field (field 0) in the current structure.
    LD_HL(SPRITEANIMSTRUCT_INDEX);
    ADD_HL_BC;
//  Load the index.
    LD_A_addr(wSpriteAnimCount);
    LD_hli_A;  // SPRITEANIMSTRUCT_INDEX
//  Copy the table entry to the next two fields.
    LD_A_de;
    LD_hli_A;  // SPRITEANIMSTRUCT_FRAMESET_ID
    INC_DE;
    LD_A_de;
    LD_hli_A;  // SPRITEANIMSTRUCT_ANIM_SEQ_ID
    INC_DE;
//  Look up the third field in the wSpriteAnimDict mapping.
//  Take the mapped value and load it in.
    LD_A_de;
    CALL(aGetSpriteAnimVTile);
    LD_hli_A;  // SPRITEANIMSTRUCT_TILE_ID
    POP_DE;
//  Set hl to field 4 (X coordinate).  Kinda pointless, because we're presumably already here.
    LD_HL(SPRITEANIMSTRUCT_XCOORD);
    ADD_HL_BC;
//  Load the original value of de into here.
    LD_A_E;
    LD_hli_A;  // SPRITEANIMSTRUCT_XCOORD
    LD_A_D;
    LD_hli_A;  // SPRITEANIMSTRUCT_YCOORD
//  load 0 into the next four fields
    XOR_A_A;
    LD_hli_A;  // SPRITEANIMSTRUCT_XOFFSET
    LD_hli_A;  // SPRITEANIMSTRUCT_YOFFSET
    XOR_A_A;
    LD_hli_A;  // SPRITEANIMSTRUCT_DURATION
    LD_hli_A;  // SPRITEANIMSTRUCT_DURATIONOFFSET
//  load -1 into the next field
    DEC_A;
    LD_hli_A;  // SPRITEANIMSTRUCT_FRAME
//  load 0 into the last five fields
    XOR_A_A;
    LD_hli_A;  // SPRITEANIMSTRUCT_JUMPTABLE_INDEX
    LD_hli_A;  // SPRITEANIMSTRUCT_VAR1
    LD_hli_A;  // SPRITEANIMSTRUCT_VAR2
    LD_hli_A;  // SPRITEANIMSTRUCT_VAR3
    LD_hl_A;  // SPRITEANIMSTRUCT_VAR4
//  back up the address of the first field to wSpriteAnimAddrBackup
    LD_A_C;
    LD_addr_A(wSpriteAnimAddrBackup);
    LD_A_B;
    LD_addr_A(wSpriteAnimAddrBackup + 1);
    RET;

}

void DeinitializeSprite(void){
//  Clear the index field of the struct in bc.
    LD_HL(SPRITEANIMSTRUCT_INDEX);
    ADD_HL_BC;
    LD_hl(0);
    RET;

}

void DeinitializeAllSprites(void){
//  Clear the index field of every struct in the wSpriteAnimationStructs array.
    LD_HL(wSpriteAnimationStructs);
    LD_BC(SPRITEANIMSTRUCT_LENGTH);
    LD_E(NUM_SPRITE_ANIM_STRUCTS);
    XOR_A_A;

loop:
    LD_hl_A;
    ADD_HL_BC;
    DEC_E;
    IF_NZ goto loop;
    RET;

}

void UpdateAnimFrame(void){
    CALL(aInitSpriteAnimBuffer);  // init WRAM
    CALL(aGetSpriteAnimFrame);  // read from a memory array
    CP_A(dowait_command);
    IF_Z goto done;
    CP_A(delanim_command);
    IF_Z goto delete;
    CALL(aGetFrameOAMPointer);
// add byte to [wCurAnimVTile]
    LD_A_addr(wCurAnimVTile);
    ADD_A_hl;
    LD_addr_A(wCurAnimVTile);
    INC_HL;
// load pointer into hl
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    PUSH_BC;
    LD_A_addr(wCurSpriteOAMAddr);
    LD_E_A;
    LD_D(HIGH(wVirtualOAM));
    LD_A_hli;
    LD_C_A;  // number of objects

loop:
// first byte: y (px)
// [de] = [wCurAnimYCoord] + [wCurAnimYOffset] + [wGlobalAnimYOffset] + AddOrSubtractY([hl])
    LD_A_addr(wCurAnimYCoord);
    LD_B_A;
    LD_A_addr(wCurAnimYOffset);
    ADD_A_B;
    LD_B_A;
    LD_A_addr(wGlobalAnimYOffset);
    ADD_A_B;
    LD_B_A;
    CALL(aAddOrSubtractY);
    ADD_A_B;
    LD_de_A;
    INC_HL;
    INC_DE;
// second byte: x (px)
// [de] = [wCurAnimXCoord] + [wCurAnimXOffset] + [wGlobalAnimXOffset] + AddOrSubtractX([hl])
    LD_A_addr(wCurAnimXCoord);
    LD_B_A;
    LD_A_addr(wCurAnimXOffset);
    ADD_A_B;
    LD_B_A;
    LD_A_addr(wGlobalAnimXOffset);
    ADD_A_B;
    LD_B_A;
    CALL(aAddOrSubtractX);
    ADD_A_B;
    LD_de_A;
    INC_HL;
    INC_DE;
// third byte: vtile
// [de] = [wCurAnimVTile] + [hl]
    LD_A_addr(wCurAnimVTile);
    ADD_A_hl;
    LD_de_A;
    INC_HL;
    INC_DE;
// fourth byte: attributes
// [de] = GetSpriteOAMAttr([hl])
    CALL(aGetSpriteOAMAttr);
    LD_de_A;
    INC_HL;
    INC_DE;
    LD_A_E;
    LD_addr_A(wCurSpriteOAMAddr);
    CP_A(LOW(wVirtualOAMEnd));
    IF_NC goto reached_the_end;
    DEC_C;
    IF_NZ goto loop;
    POP_BC;
    goto done;


delete:
    CALL(aDeinitializeSprite);

done:
    AND_A_A;
    RET;


reached_the_end:
    POP_BC;
    SCF;
    RET;

}

void AddOrSubtractY(void){
    PUSH_HL;
    LD_A_hl;
    LD_HL(wCurSpriteOAMFlags);
    BIT_hl(OAM_Y_FLIP);
    IF_Z goto ok;
// -8 - a
    ADD_A(8);
    XOR_A(0xff);
    INC_A;


ok:
    POP_HL;
    RET;

}

void AddOrSubtractX(void){
    PUSH_HL;
    LD_A_hl;
    LD_HL(wCurSpriteOAMFlags);
    BIT_hl(OAM_X_FLIP);
    IF_Z goto ok;
// -8 - a
    ADD_A(8);
    XOR_A(0xff);
    INC_A;


ok:
    POP_HL;
    RET;

}

void GetSpriteOAMAttr(void){
    LD_A_addr(wCurSpriteOAMFlags);
    LD_B_A;
    LD_A_hl;
    XOR_A_B;
    AND_A(PRIORITY | Y_FLIP | X_FLIP);
    LD_B_A;
    LD_A_hl;
    AND_A(~(PRIORITY | Y_FLIP | X_FLIP));
    OR_A_B;
    RET;

}

void InitSpriteAnimBuffer(void){
    XOR_A_A;
    LD_addr_A(wCurSpriteOAMFlags);
    LD_HL(SPRITEANIMSTRUCT_TILE_ID);
    ADD_HL_BC;
    LD_A_hli;
    LD_addr_A(wCurAnimVTile);
    LD_A_hli;
    LD_addr_A(wCurAnimXCoord);
    LD_A_hli;
    LD_addr_A(wCurAnimYCoord);
    LD_A_hli;
    LD_addr_A(wCurAnimXOffset);
    LD_A_hli;
    LD_addr_A(wCurAnimYOffset);
    RET;

}

void GetSpriteAnimVTile(void){
//  a = wSpriteAnimDict[a] if a in wSpriteAnimDict else vtile offset $00
    PUSH_HL;
    PUSH_BC;
    LD_HL(wSpriteAnimDict);
    LD_B_A;
    LD_C(NUM_SPRITEANIMDICT_ENTRIES);

loop:
    LD_A_hli;
    CP_A_B;
    IF_Z goto ok;
    INC_HL;
    DEC_C;
    IF_NZ goto loop;
    XOR_A_A;
    goto done;


ok:
    LD_A_hl;


done:
    POP_BC;
    POP_HL;
    RET;

}

void v_ReinitSpriteAnimFrame(void){
    LD_HL(SPRITEANIMSTRUCT_FRAMESET_ID);
    ADD_HL_BC;
    LD_hl_A;
    LD_HL(SPRITEANIMSTRUCT_DURATION);
    ADD_HL_BC;
    LD_hl(0);
    LD_HL(SPRITEANIMSTRUCT_FRAME);
    ADD_HL_BC;
    LD_hl(-1);
    RET;

}

void GetSpriteAnimFrame(void){

loop:
    LD_HL(SPRITEANIMSTRUCT_DURATION);
    ADD_HL_BC;
    LD_A_hl;
    AND_A_A;
    IF_Z goto next_frame;
    DEC_hl;
    CALL(aGetSpriteAnimFrame_GetPointer);
    LD_A_hli;
    PUSH_AF;
    goto okay;


next_frame:
    LD_HL(SPRITEANIMSTRUCT_FRAME);
    ADD_HL_BC;
    INC_hl;
    CALL(aGetSpriteAnimFrame_GetPointer);
    LD_A_hli;
    CP_A(dorestart_command);
    IF_Z goto restart;
    CP_A(endanim_command);
    IF_Z goto repeat_last;

    PUSH_AF;
    LD_A_hl;
    PUSH_HL;
    AND_A(~(Y_FLIP << 1 | X_FLIP << 1));
    LD_HL(SPRITEANIMSTRUCT_DURATIONOFFSET);
    ADD_HL_BC;
    ADD_A_hl;
    LD_HL(SPRITEANIMSTRUCT_DURATION);
    ADD_HL_BC;
    LD_hl_A;
    POP_HL;

okay:
    LD_A_hl;
    AND_A(Y_FLIP << 1 | X_FLIP << 1);  // The << 1 is compensated in the "frame" macro
    SRL_A;
    LD_addr_A(wCurSpriteOAMFlags);
    POP_AF;
    RET;


repeat_last:
    XOR_A_A;
    LD_HL(SPRITEANIMSTRUCT_DURATION);
    ADD_HL_BC;
    LD_hl_A;

    LD_HL(SPRITEANIMSTRUCT_FRAME);
    ADD_HL_BC;
    DEC_hl;
    DEC_hl;
    goto loop;


restart:
    XOR_A_A;
    LD_HL(SPRITEANIMSTRUCT_DURATION);
    ADD_HL_BC;
    LD_hl_A;

    DEC_A;
    LD_HL(SPRITEANIMSTRUCT_FRAME);
    ADD_HL_BC;
    LD_hl_A;
    goto loop;


GetPointer:
    LD_HL(SPRITEANIMSTRUCT_FRAMESET_ID);
    ADD_HL_BC;
    LD_E_hl;
    LD_D(0);
    LD_HL(mSpriteAnimFrameData);
    ADD_HL_DE;
    ADD_HL_DE;
    LD_E_hl;
    INC_HL;
    LD_D_hl;
    LD_HL(SPRITEANIMSTRUCT_FRAME);
    ADD_HL_BC;
    LD_L_hl;
    LD_H(0);
    ADD_HL_HL;
    ADD_HL_DE;
    RET;

}

void GetFrameOAMPointer(void){
    LD_E_A;
    LD_D(0);
    LD_HL(mSpriteAnimOAMData);
    ADD_HL_DE;
    ADD_HL_DE;
    ADD_HL_DE;
    RET;

}

void UnusedLoadSpriteAnimGFX(void){
//  //  unreferenced
    PUSH_HL;
    LD_L_A;
    LD_H(0);
    ADD_HL_HL;
    ADD_HL_HL;
    LD_DE(mUnusedSpriteAnimGFX);
    ADD_HL_DE;
    LD_C_hl;
    INC_HL;
    LD_B_hl;
    INC_HL;
    LD_E_hl;
    INC_HL;
    LD_D_hl;
    POP_HL;
    PUSH_BC;
    CALL(aRequest2bpp);
    POP_BC;
    RET;

// INCLUDE "data/sprite_anims/sequences.asm"

// INCLUDE "engine/gfx/sprite_anims.asm"

// INCLUDE "data/sprite_anims/framesets.asm"

// INCLUDE "data/sprite_anims/oam.asm"

// INCLUDE "data/sprite_anims/unused_gfx.asm"

    return Sprites_Cosine();
}

void Sprites_Cosine(void){
//  a = d * cos(a * pi/32)
    ADD_A(0b010000);  // cos(x) = sin(x + pi/2)
// fallthrough
    return Sprites_Sine();
}

void Sprites_Sine(void){
//  a = d * sin(a * pi/32)
    
    //calc_sine_wave ['?']

    return AnimateEndOfExpBar();
}

void AnimateEndOfExpBar(void){
    LDH_A_addr(hSGB);
    LD_DE(mEndOfExpBarGFX);
    AND_A_A;
    IF_Z goto load;
    LD_DE(mSGBEndOfExpBarGFX);


load:
    LD_HL(vTiles0 + LEN_2BPP_TILE * 0x00);
    LD_BC((BANK(aEndOfExpBarGFX) << 8) | 1);
    CALL(aRequest2bpp);
    LD_C(8);
    LD_D(0);

loop:
    PUSH_BC;
    CALL(aAnimateEndOfExpBar_AnimateFrame);
    CALL(aDelayFrame);
    POP_BC;
    INC_D;
    INC_D;
    DEC_C;
    IF_NZ goto loop;
    CALL(aClearSprites);
    RET;


AnimateFrame:
    LD_HL(wVirtualOAMSprite00);
    LD_C(8);  // number of animated circles

anim_loop:
    LD_A_C;
    AND_A_A;
    RET_Z ;
    DEC_C;
    LD_A_C;
//  multiply by 8
    SLA_A;
    SLA_A;
    SLA_A;
    PUSH_AF;

    PUSH_DE;
    PUSH_HL;
    CALL(aSprites_Sine);
    POP_HL;
    POP_DE;
    ADD_A(13 * TILE_WIDTH);
    LD_hli_A;  // y

    POP_AF;
    PUSH_DE;
    PUSH_HL;
    CALL(aSprites_Cosine);
    POP_HL;
    POP_DE;
    ADD_A(10 * TILE_WIDTH + 4);
    LD_hli_A;  // x

    LD_A(0x0);
    LD_hli_A;  // tile id
    LD_A(PAL_BATTLE_OB_BLUE);
    LD_hli_A;  // attributes
    goto anim_loop;

    return EndOfExpBarGFX();
}

void EndOfExpBarGFX(void){
// INCBIN "gfx/battle/expbarend.2bpp"
    return SGBEndOfExpBarGFX();
}

void SGBEndOfExpBarGFX(void){
// INCBIN "gfx/battle/expbarend_sgb.2bpp"

    return ClearSpriteAnims2();
}

void ClearSpriteAnims2(void){
    PUSH_HL;
    PUSH_DE;
    PUSH_BC;
    PUSH_AF;
    LD_HL(wSpriteAnimData);
    LD_BC(wSpriteAnimDataEnd - wSpriteAnimData);

loop:
    LD_hl(0);
    INC_HL;
    DEC_BC;
    LD_A_C;
    OR_A_B;
    IF_NZ goto loop;
    POP_AF;
    POP_BC;
    POP_DE;
    POP_HL;
    RET;

}
