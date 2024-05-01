#include "../../constants.h"
#include "anim_commands.h"
#include "core.h"
#include "helpers.h"
#include "functions.h"
#include "../../home/delay.h"

//  Battle animation command interpreter.

void PlayBattleAnim(void){
    // LDH_A_addr(rSVBK);
    // PUSH_AF;

    // LD_A(MBANK(awActiveAnimObjects));
    // LDH_addr_A(rSVBK);
    wbank_push(MBANK(awActiveAnimObjects));

    CALL(av_PlayBattleAnim);

    // POP_AF;
    // LDH_addr_A(rSVBK);
    // RET;
    wbank_pop;

}

void v_PlayBattleAnim(void){
    // LD_C(6);

// wait:
    // CALL(aBattleAnimDelayFrame);
    // DEC_C;
    // IF_NZ goto wait;
    for(uint8_t c = 0; c < 6; ++c) {
        CALL(aBattleAnimDelayFrame);
    }

    CALL(aBattleAnimAssignPals);
    CALL(aBattleAnimRequestPals);
    CALL(aBattleAnimDelayFrame);

    LD_C(1);
    LDH_A_addr(rKEY1);
    BIT_A(7);  // check CGB double speed mode
    IF_NZ goto got_speed;
    LD_C(3);


got_speed:
    LD_HL(hVBlank);
    LD_A_hl;
    PUSH_AF;

    LD_hl_C;
    CALL(aBattleAnimRunScript);

    POP_AF;
    LDH_addr_A(hVBlank);

    LD_A(1);
    LDH_addr_A(hBGMapMode);

    CALL(aBattleAnimDelayFrame);
    CALL(aBattleAnimDelayFrame);
    CALL(aBattleAnimDelayFrame);
    CALL(aWaitSFX);
    RET;

}

void BattleAnimRunScript(void){
    LD_A_addr(wFXAnimID + 1);
    AND_A_A;
    IF_NZ goto hi_byte;

    FARCALL(aCheckBattleScene);
    IF_C goto disabled;

    CALL(aBattleAnimClearHud);
    CALL(aRunBattleAnimScript);

    CALL(aBattleAnimAssignPals);
    CALL(aBattleAnimRequestPals);

    XOR_A_A;
    LDH_addr_A(hSCX);
    LDH_addr_A(hSCY);
    CALL(aBattleAnimDelayFrame);
    CALL(aBattleAnimRestoreHuds);


disabled:
    LD_A_addr(wNumHits);
    AND_A_A;
    IF_Z goto done;

    LD_L_A;
    LD_H(0);
    LD_DE(ANIM_MISS);
    ADD_HL_DE;
    LD_A_L;
    LD_addr_A(wFXAnimID);
    LD_A_H;
    LD_addr_A(wFXAnimID + 1);


hi_byte:
    CALL(aWaitSFX);
    CALL(aPlayHitSound);
    CALL(aRunBattleAnimScript);


done:
    CALL(aBattleAnim_RevertPals);
    RET;

}

void RunBattleAnimScript(void){
    CALL(aClearBattleAnims);


playframe:
    CALL(aRunBattleAnimCommand);
    CALL(av_ExecuteBGEffects);
    CALL(aBattleAnim_UpdateOAM_All);
    CALL(aPushLYOverrides);
    CALL(aBattleAnimRequestPals);

//  Speed up Rollout's animation.
    LD_A_addr(wFXAnimID + 1);
    OR_A_A;
    IF_NZ goto not_rollout;

    LD_A_addr(wFXAnimID);
    CP_A(ROLLOUT);
    IF_NZ goto not_rollout;

    LD_A(ANIM_BG_ROLLOUT);
    LD_B(NUM_BG_EFFECTS);
    LD_DE(BG_EFFECT_STRUCT_LENGTH);
    LD_HL(wBGEffect1Function);

find:
    CP_A_hl;
    IF_Z goto done;
    ADD_HL_DE;
    DEC_B;
    IF_NZ goto find;


not_rollout:
    CALL(aBattleAnimDelayFrame);


done:
    LD_A_addr(wBattleAnimFlags);
    BIT_A(BATTLEANIM_STOP_F);
    IF_Z goto playframe;

    CALL(aBattleAnim_ClearOAM);
    RET;

}

void BattleAnimClearHud(void){
    CALL(aBattleAnimDelayFrame);
    CALL(aWaitTop);
    CALL(aClearActorHud);
    LD_A(0x1);
    LDH_addr_A(hBGMapMode);
    CALL(aBattleAnimDelayFrame);
    CALL(aBattleAnimDelayFrame);
    CALL(aBattleAnimDelayFrame);
    CALL(aWaitTop);
    RET;

}

void BattleAnimRestoreHuds(void){
    CALL(aBattleAnimDelayFrame);
    CALL(aWaitTop);

    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(MBANK(awCurBattleMon));  // aka BANK(wTempMon), BANK(wPartyMon1), and several others
    LDH_addr_A(rSVBK);

//  this block should just be "call UpdateBattleHuds"
    LD_HL(mUpdateBattleHuds);
    LD_A(BANK(aUpdatePlayerHUD));
    RST(aFarCall);

    POP_AF;
    LDH_addr_A(rSVBK);

    LD_A(0x1);
    LDH_addr_A(hBGMapMode);
    CALL(aBattleAnimDelayFrame);
    CALL(aBattleAnimDelayFrame);
    CALL(aBattleAnimDelayFrame);
    CALL(aWaitTop);
    RET;

}

void BattleAnimRequestPals(void){
    LDH_A_addr(hCGB);
    AND_A_A;
    RET_Z ;

    LDH_A_addr(rBGP);
    LD_B_A;
    LD_A_addr(wBGP);
    CP_A_B;
    CALL_NZ (aBattleAnim_SetBGPals);

    LDH_A_addr(rOBP0);
    LD_B_A;
    LD_A_addr(wOBP0);
    CP_A_B;
    CALL_NZ (aBattleAnim_SetOBPals);
    RET;

}

void BattleAnimDelayFrame(void){
//  Like DelayFrame but wastes battery life.

    // LD_A(1);
    // LD_addr_A(wVBlankOccurred);

// wait:
    // LD_A_addr(wVBlankOccurred);
    // AND_A_A;
    // IF_NZ goto wait;
    // RET;
    DelayFrame();
}

void ClearActorHud(void){
    LDH_A_addr(hBattleTurn);
    AND_A_A;
    IF_Z goto player;

    hlcoord(1, 0, wTilemap);
    LD_BC((4 << 8) | 10);
    CALL(aClearBox);
    RET;


player:
    hlcoord(9, 7, wTilemap);
    LD_BC((5 << 8) | 11);
    CALL(aClearBox);
    RET;

}

void PlaceWindowOverBattleTextbox(void){
//  //  unreferenced
    XOR_A_A;
    LDH_addr_A(hBGMapMode);
// bgcoord hBGMapAddress, 0, 20
    LD_A(LOW(vBGMap0 + 20 * BG_MAP_WIDTH));
    LDH_addr_A(hBGMapAddress);
    LD_A(HIGH(vBGMap0 + 20 * BG_MAP_WIDTH));
    LDH_addr_A(hBGMapAddress + 1);
    CALL(aWaitBGMap2);
    LD_A((SCREEN_HEIGHT - TEXTBOX_HEIGHT) * TILE_WIDTH);
    LDH_addr_A(hWY);
// bgcoord hBGMapAddress, 0, 0
    XOR_A_A;  // LOW(vBGMap0)
    LDH_addr_A(hBGMapAddress);
    LD_A(HIGH(vBGMap0));
    LDH_addr_A(hBGMapAddress + 1);
    CALL(aBattleAnimDelayFrame);
    RET;

}

void BattleAnim_ClearOAM(void){
    LD_A_addr(wBattleAnimFlags);
    BIT_A(BATTLEANIM_KEEPSPRITES_F);
    IF_Z goto delete;

// Instead of deleting the sprites, make them all use PAL_BATTLE_OB_ENEMY
    LD_HL(wVirtualOAMSprite00Attributes);
    LD_C(NUM_SPRITE_OAM_STRUCTS);

loop:
    LD_A_hl;
    AND_A(~(PALETTE_MASK | VRAM_BANK_1));  // zeros out the palette bits
    //assert ['PAL_BATTLE_OB_ENEMY == 0'];
    LD_hli_A;
    for(int rept = 0; rept < SPRITEOAMSTRUCT_LENGTH - 1; rept++){
    INC_HL;
    }
    DEC_C;
    IF_NZ goto loop;
    RET;


delete:
    LD_HL(wVirtualOAM);
    LD_C(wVirtualOAMEnd - wVirtualOAM);
    XOR_A_A;

loop2:
    LD_hli_A;
    DEC_C;
    IF_NZ goto loop2;
    RET;

}

void RunBattleAnimCommand(void){
    CALL(aRunBattleAnimCommand_CheckTimer);
    RET_NC ;
    CALL(aRunBattleAnimCommand_RunScript);
    RET;


CheckTimer:
    LD_A_addr(wBattleAnimDelay);
    AND_A_A;
    IF_Z goto done;

    DEC_A;
    LD_addr_A(wBattleAnimDelay);
    AND_A_A;
    RET;


done:
    SCF;
    RET;


RunScript:

loop:
    CALL(aGetBattleAnimByte);

    CP_A(anim_ret_command);
    IF_NZ goto not_done_with_anim;

//  Return from a subroutine.
    LD_HL(wBattleAnimFlags);
    BIT_hl(BATTLEANIM_IN_SUBROUTINE_F);
    IF_NZ goto do_anim;

    SET_hl(BATTLEANIM_STOP_F);
    RET;


not_done_with_anim:
    CP_A(anim_obj_command);
    IF_NC goto do_anim;

    LD_addr_A(wBattleAnimDelay);
    RET;


do_anim:
    CALL(aRunBattleAnimCommand_DoCommand);

    goto loop;


DoCommand:
//  Execute battle animation command in [wBattleAnimByte].
    LD_A_addr(wBattleAnimByte);
    // SUB_A(anim_obj_command);

    LD_E_A;
    LD_D(0);
    // LD_HL(mBattleAnimCommands);
    // ADD_HL_DE;
    // ADD_HL_DE;
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // JP_hl;
    switch(REG_DE) {
        case anim_obj_command: CALL(aBattleAnimCmd_Obj); break;
        case anim_1gfx_command: CALL(aBattleAnimCmd_1GFX); break;
        case anim_2gfx_command: CALL(aBattleAnimCmd_2GFX); break;
        case anim_3gfx_command: CALL(aBattleAnimCmd_3GFX); break;
        case anim_4gfx_command: CALL(aBattleAnimCmd_4GFX); break;
        case anim_5gfx_command: CALL(aBattleAnimCmd_5GFX); break;
        case anim_incobj_command: CALL(aBattleAnimCmd_IncObj); break;
        case anim_setobj_command: CALL(aBattleAnimCmd_SetObj); break;
        case anim_incbgeffect_command: CALL(aBattleAnimCmd_IncBGEffect); break;
        case anim_battlergfx_1row_command: CALL(aBattleAnimCmd_BattlerGFX_1Row); break;
        case anim_battlergfx_2row_command: CALL(aBattleAnimCmd_BattlerGFX_2Row); break;
        case anim_checkpokeball_command: CALL(aBattleAnimCmd_CheckPokeball); break;
        case anim_transform_command: CALL(aBattleAnimCmd_Transform); break;
        case anim_raisesub_command: CALL(aBattleAnimCmd_RaiseSub); break;
        case anim_dropsub_command: CALL(aBattleAnimCmd_DropSub); break;
        case anim_resetobp0_command: CALL(aBattleAnimCmd_ResetObp0); break;
        case anim_sound_command: CALL(aBattleAnimCmd_Sound); break;
        case anim_cry_command: CALL(aBattleAnimCmd_Cry); break;
        case anim_minimizeopp_command: CALL(aBattleAnimCmd_MinimizeOpp); break;
        case anim_oamon_command: CALL(aBattleAnimCmd_OAMOn); break;
        case anim_oamoff_command: CALL(aBattleAnimCmd_OAMOff); break;
        case anim_clearobjs_command: CALL(aBattleAnimCmd_ClearObjs); break;
        case anim_beatup_command: CALL(aBattleAnimCmd_BeatUp); break;
        case anim_0xe7_command: CALL(aBattleAnimCmd_E7); break;
        case anim_updateactorpic_command: CALL(aBattleAnimCmd_UpdateActorPic); break;
        case anim_minimize_command: CALL(aBattleAnimCmd_Minimize); break;
        case anim_0xea_command: CALL(aBattleAnimCmd_EA); break;
        case anim_0xeb_command: CALL(aBattleAnimCmd_EB); break;
        case anim_0xec_command: CALL(aBattleAnimCmd_EC); break;
        case anim_0xed_command: CALL(aBattleAnimCmd_ED); break;
        case anim_if_param_and_command: CALL(aBattleAnimCmd_IfParamAnd); break;
        case anim_jumpuntil_command: CALL(aBattleAnimCmd_JumpUntil); break;
        case anim_bgeffect_command: CALL(aBattleAnimCmd_BGEffect); break;
        case anim_bgp_command: CALL(aBattleAnimCmd_BGP); break;
        case anim_obp0_command: CALL(aBattleAnimCmd_OBP0); break;
        case anim_obp1_command: CALL(aBattleAnimCmd_OBP1); break;
        case anim_keepsprites_command: CALL(aBattleAnimCmd_KeepSprites); break;
        case anim_0xf5_command: CALL(aBattleAnimCmd_F5); break;
        case anim_0xf6_command: CALL(aBattleAnimCmd_F6); break;
        case anim_0xf7_command: CALL(aBattleAnimCmd_F7); break;
        case anim_if_param_equal_command: CALL(aBattleAnimCmd_IfParamEqual); break;
        case anim_setvar_command: CALL(aBattleAnimCmd_SetVar); break;
        case anim_incvar_command: CALL(aBattleAnimCmd_IncVar); break;
        case anim_if_var_equal_command: CALL(aBattleAnimCmd_IfVarEqual); break;
        case anim_jump_command: CALL(aBattleAnimCmd_Jump); break;
        case anim_loop_command: CALL(aBattleAnimCmd_Loop); break;
        case anim_call_command: CALL(aBattleAnimCmd_Call); break;
        case anim_ret_command: CALL(aBattleAnimCmd_Ret); break;
        default: break;
    }
    RET;
}

// void BattleAnimCommands(void){
//  entries correspond to anim_* constants (see macros/scripts/battle_anims.asm)
    //table_width ['2', 'BattleAnimCommands']
    //dw ['BattleAnimCmd_Obj'];
    //dw ['BattleAnimCmd_1GFX'];
    //dw ['BattleAnimCmd_2GFX'];
    //dw ['BattleAnimCmd_3GFX'];
    //dw ['BattleAnimCmd_4GFX'];
    //dw ['BattleAnimCmd_5GFX'];
    //dw ['BattleAnimCmd_IncObj'];
    //dw ['BattleAnimCmd_SetObj'];
    //dw ['BattleAnimCmd_IncBGEffect'];
    //dw ['BattleAnimCmd_BattlerGFX_1Row'];
    //dw ['BattleAnimCmd_BattlerGFX_2Row'];
    //dw ['BattleAnimCmd_CheckPokeball'];
    //dw ['BattleAnimCmd_Transform'];
    //dw ['BattleAnimCmd_RaiseSub'];
    //dw ['BattleAnimCmd_DropSub'];
    //dw ['BattleAnimCmd_ResetObp0'];
    //dw ['BattleAnimCmd_Sound'];
    //dw ['BattleAnimCmd_Cry'];
    //dw ['BattleAnimCmd_MinimizeOpp'];
    //dw ['BattleAnimCmd_OAMOn'];
    //dw ['BattleAnimCmd_OAMOff'];
    //dw ['BattleAnimCmd_ClearObjs'];
    //dw ['BattleAnimCmd_BeatUp'];
    //dw ['BattleAnimCmd_E7'];
    //dw ['BattleAnimCmd_UpdateActorPic'];
    //dw ['BattleAnimCmd_Minimize'];
    //dw ['BattleAnimCmd_EA'];  // dummy
    //dw ['BattleAnimCmd_EB'];  // dummy
    //dw ['BattleAnimCmd_EC'];  // dummy
    //dw ['BattleAnimCmd_ED'];  // dummy
    //dw ['BattleAnimCmd_IfParamAnd'];
    //dw ['BattleAnimCmd_JumpUntil'];
    //dw ['BattleAnimCmd_BGEffect'];
    //dw ['BattleAnimCmd_BGP'];
    //dw ['BattleAnimCmd_OBP0'];
    //dw ['BattleAnimCmd_OBP1'];
    //dw ['BattleAnimCmd_KeepSprites'];
    //dw ['BattleAnimCmd_F5'];
    //dw ['BattleAnimCmd_F6'];
    //dw ['BattleAnimCmd_F7'];
    //dw ['BattleAnimCmd_IfParamEqual'];
    //dw ['BattleAnimCmd_SetVar'];
    //dw ['BattleAnimCmd_IncVar'];
    //dw ['BattleAnimCmd_IfVarEqual'];
    //dw ['BattleAnimCmd_Jump'];
    //dw ['BattleAnimCmd_Loop'];
    //dw ['BattleAnimCmd_Call'];
    //dw ['BattleAnimCmd_Ret'];
    //assert_table_length ['0x100 - FIRST_BATTLE_ANIM_CMD']

    // return BattleAnimCmd_EA();
// }

void BattleAnimCmd_EA(void){
    return BattleAnimCmd_EB();
}

void BattleAnimCmd_EB(void){
    return BattleAnimCmd_EC();
}

void BattleAnimCmd_EC(void){
    return BattleAnimCmd_ED();
}

void BattleAnimCmd_ED(void){
    RET;

}

void BattleAnimCmd_Ret(void){
    LD_HL(wBattleAnimFlags);
    RES_hl(BATTLEANIM_IN_SUBROUTINE_F);
    LD_HL(wBattleAnimParent);
    LD_E_hl;
    INC_HL;
    LD_D_hl;
    LD_HL(wBattleAnimAddress);
    LD_hl_E;
    INC_HL;
    LD_hl_D;
    RET;

}

void BattleAnimCmd_Call(void){
    CALL(aGetBattleAnimByte);
    LD_E_A;
    CALL(aGetBattleAnimByte);
    LD_D_A;
    PUSH_DE;
    LD_HL(wBattleAnimAddress);
    LD_E_hl;
    INC_HL;
    LD_D_hl;
    LD_HL(wBattleAnimParent);
    LD_hl_E;
    INC_HL;
    LD_hl_D;
    POP_DE;
    LD_HL(wBattleAnimAddress);
    LD_hl_E;
    INC_HL;
    LD_hl_D;
    LD_HL(wBattleAnimFlags);
    SET_hl(BATTLEANIM_IN_SUBROUTINE_F);
    RET;

}

void BattleAnimCmd_Jump(void){
    CALL(aGetBattleAnimByte);
    LD_E_A;
    CALL(aGetBattleAnimByte);
    LD_D_A;
    LD_HL(wBattleAnimAddress);
    LD_hl_E;
    INC_HL;
    LD_hl_D;
    RET;

}

void BattleAnimCmd_Loop(void){
    CALL(aGetBattleAnimByte);
    LD_HL(wBattleAnimFlags);
    BIT_hl(BATTLEANIM_IN_LOOP_F);
    IF_NZ goto continue_loop;
    AND_A_A;
    IF_Z goto perpetual;
    DEC_A;
    SET_hl(BATTLEANIM_IN_LOOP_F);
    LD_addr_A(wBattleAnimLoops);

continue_loop:
    LD_HL(wBattleAnimLoops);
    LD_A_hl;
    AND_A_A;
    IF_Z goto return_from_loop;
    DEC_hl;

perpetual:
    CALL(aGetBattleAnimByte);
    LD_E_A;
    CALL(aGetBattleAnimByte);
    LD_D_A;
    LD_HL(wBattleAnimAddress);
    LD_hl_E;
    INC_HL;
    LD_hl_D;
    RET;


return_from_loop:
    LD_HL(wBattleAnimFlags);
    RES_hl(BATTLEANIM_IN_LOOP_F);
    LD_HL(wBattleAnimAddress);
    LD_E_hl;
    INC_HL;
    LD_D_hl;
    INC_DE;
    INC_DE;
    LD_hl_D;
    DEC_HL;
    LD_hl_E;
    RET;

}

void BattleAnimCmd_JumpUntil(void){
    LD_HL(wBattleAnimParam);
    LD_A_hl;
    AND_A_A;
    IF_Z goto dont_jump;

    DEC_hl;
    CALL(aGetBattleAnimByte);
    LD_E_A;
    CALL(aGetBattleAnimByte);
    LD_D_A;
    LD_HL(wBattleAnimAddress);
    LD_hl_E;
    INC_HL;
    LD_hl_D;
    RET;


dont_jump:
    LD_HL(wBattleAnimAddress);
    LD_E_hl;
    INC_HL;
    LD_D_hl;
    INC_DE;
    INC_DE;
    LD_hl_D;
    DEC_HL;
    LD_hl_E;
    RET;

}

void BattleAnimCmd_SetVar(void){
    CALL(aGetBattleAnimByte);
    LD_addr_A(wBattleAnimVar);
    RET;

}

void BattleAnimCmd_IncVar(void){
    LD_HL(wBattleAnimVar);
    INC_hl;
    RET;

}

void BattleAnimCmd_IfVarEqual(void){
    CALL(aGetBattleAnimByte);
    LD_HL(wBattleAnimVar);
    CP_A_hl;
    IF_Z goto jump;

    LD_HL(wBattleAnimAddress);
    LD_E_hl;
    INC_HL;
    LD_D_hl;
    INC_DE;
    INC_DE;
    LD_hl_D;
    DEC_HL;
    LD_hl_E;
    RET;


jump:
    CALL(aGetBattleAnimByte);
    LD_E_A;
    CALL(aGetBattleAnimByte);
    LD_D_A;
    LD_HL(wBattleAnimAddress);
    LD_hl_E;
    INC_HL;
    LD_hl_D;
    RET;

}

void BattleAnimCmd_IfParamEqual(void){
    CALL(aGetBattleAnimByte);
    LD_HL(wBattleAnimParam);
    CP_A_hl;
    IF_Z goto jump;

    LD_HL(wBattleAnimAddress);
    LD_E_hl;
    INC_HL;
    LD_D_hl;
    INC_DE;
    INC_DE;
    LD_hl_D;
    DEC_HL;
    LD_hl_E;
    RET;


jump:
    CALL(aGetBattleAnimByte);
    LD_E_A;
    CALL(aGetBattleAnimByte);
    LD_D_A;
    LD_HL(wBattleAnimAddress);
    LD_hl_E;
    INC_HL;
    LD_hl_D;
    RET;

}

void BattleAnimCmd_IfParamAnd(void){
    CALL(aGetBattleAnimByte);
    LD_E_A;
    LD_A_addr(wBattleAnimParam);
    AND_A_E;
    IF_NZ goto jump;

    LD_HL(wBattleAnimAddress);
    LD_E_hl;
    INC_HL;
    LD_D_hl;
    INC_DE;
    INC_DE;
    LD_hl_D;
    DEC_HL;
    LD_hl_E;
    RET;


jump:
    CALL(aGetBattleAnimByte);
    LD_E_A;
    CALL(aGetBattleAnimByte);
    LD_D_A;
    LD_HL(wBattleAnimAddress);
    LD_hl_E;
    INC_HL;
    LD_hl_D;
    RET;

}

void BattleAnimCmd_Obj(void){
//  index, x, y, param
    CALL(aGetBattleAnimByte);
    LD_addr_A(wBattleObjectTempID);
    CALL(aGetBattleAnimByte);
    LD_addr_A(wBattleObjectTempXCoord);
    CALL(aGetBattleAnimByte);
    LD_addr_A(wBattleObjectTempYCoord);
    CALL(aGetBattleAnimByte);
    LD_addr_A(wBattleObjectTempParam);
    CALL(aQueueBattleAnimation);
    RET;

}

void BattleAnimCmd_BGEffect(void){
    CALL(aGetBattleAnimByte);
    LD_addr_A(wBattleBGEffectTempID);
    CALL(aGetBattleAnimByte);
    LD_addr_A(wBattleBGEffectTempJumptableIndex);
    CALL(aGetBattleAnimByte);
    LD_addr_A(wBattleBGEffectTempTurn);
    CALL(aGetBattleAnimByte);
    LD_addr_A(wBattleBGEffectTempParam);
    CALL(av_QueueBGEffect);
    RET;

}

void BattleAnimCmd_BGP(void){
    CALL(aGetBattleAnimByte);
    LD_addr_A(wBGP);
    RET;

}

void BattleAnimCmd_OBP0(void){
    CALL(aGetBattleAnimByte);
    LD_addr_A(wOBP0);
    RET;

}

void BattleAnimCmd_OBP1(void){
    CALL(aGetBattleAnimByte);
    LD_addr_A(wOBP1);
    RET;

}

void BattleAnimCmd_ResetObp0(void){
    LDH_A_addr(hSGB);
    AND_A_A;
    LD_A(0xe0);
    IF_Z goto not_sgb;
    LD_A(0xf0);

not_sgb:
    LD_addr_A(wOBP0);
    RET;

}

void BattleAnimCmd_ClearObjs(void){
//  BUG: This function only clears the first 6⅔ objects
    LD_HL(wActiveAnimObjects);
    LD_A(0xa0);  // should be NUM_ANIM_OBJECTS * BATTLEANIMSTRUCT_LENGTH

loop:
    LD_hl(0);
    INC_HL;
    DEC_A;
    IF_NZ goto loop;
    RET;

}

void BattleAnimCmd_1GFX(void){
    return BattleAnimCmd_2GFX();
}

void BattleAnimCmd_2GFX(void){
    return BattleAnimCmd_3GFX();
}

void BattleAnimCmd_3GFX(void){
    return BattleAnimCmd_4GFX();
}

void BattleAnimCmd_4GFX(void){
    return BattleAnimCmd_5GFX();
}

void BattleAnimCmd_5GFX(void){
    LD_A_addr(wBattleAnimByte);
    AND_A(0xf);
    LD_C_A;
    LD_HL(wBattleAnimTileDict);
    XOR_A_A;
    LD_addr_A(wBattleAnimGFXTempTileID);

loop:
    LD_A_addr(wBattleAnimGFXTempTileID);
    CP_A((vTiles1 - vTiles0) / LEN_2BPP_TILE - BATTLEANIM_BASE_TILE);
    RET_NC ;
    CALL(aGetBattleAnimByte);
    LD_hli_A;
    LD_A_addr(wBattleAnimGFXTempTileID);
    LD_hli_A;
    PUSH_BC;
    PUSH_HL;
    LD_L_A;
    LD_H(0);
    for(int rept = 0; rept < 4; rept++){
    ADD_HL_HL;
    }
    LD_DE(vTiles0 + LEN_2BPP_TILE * BATTLEANIM_BASE_TILE);
    ADD_HL_DE;
    LD_A_addr(wBattleAnimByte);
    CALL(aLoadBattleAnimGFX);
    LD_A_addr(wBattleAnimGFXTempTileID);
    ADD_A_C;
    LD_addr_A(wBattleAnimGFXTempTileID);
    POP_HL;
    POP_BC;
    DEC_C;
    IF_NZ goto loop;
    RET;

}

void BattleAnimCmd_IncObj(void){
    CALL(aGetBattleAnimByte);
    LD_E(NUM_ANIM_OBJECTS);
    LD_BC(wActiveAnimObjects);

loop:
    LD_HL(BATTLEANIMSTRUCT_INDEX);
    ADD_HL_BC;
    LD_D_hl;
    LD_A_addr(wBattleAnimByte);
    CP_A_D;
    IF_Z goto found;
    LD_HL(BATTLEANIMSTRUCT_LENGTH);
    ADD_HL_BC;
    LD_C_L;
    LD_B_H;
    DEC_E;
    IF_NZ goto loop;
    RET;


found:
    LD_HL(BATTLEANIMSTRUCT_JUMPTABLE_INDEX);
    ADD_HL_BC;
    INC_hl;
    RET;

}

void BattleAnimCmd_IncBGEffect(void){
    CALL(aGetBattleAnimByte);
    LD_E(NUM_BG_EFFECTS);
    LD_BC(wBGEffect1Function);

loop:
    LD_HL(0x0);
    ADD_HL_BC;
    LD_D_hl;
    LD_A_addr(wBattleAnimByte);
    CP_A_D;
    IF_Z goto found;
    LD_HL(4);
    ADD_HL_BC;
    LD_C_L;
    LD_B_H;
    DEC_E;
    IF_NZ goto loop;
    RET;


found:
    LD_HL(BG_EFFECT_STRUCT_JT_INDEX);
    ADD_HL_BC;
    INC_hl;
    RET;

}

void BattleAnimCmd_SetObj(void){
    CALL(aGetBattleAnimByte);
    LD_E(NUM_ANIM_OBJECTS);
    LD_BC(wActiveAnimObjects);

loop:
    LD_HL(BATTLEANIMSTRUCT_INDEX);
    ADD_HL_BC;
    LD_D_hl;
    LD_A_addr(wBattleAnimByte);
    CP_A_D;
    IF_Z goto found;
    LD_HL(BATTLEANIMSTRUCT_LENGTH);
    ADD_HL_BC;
    LD_C_L;
    LD_B_H;
    DEC_E;
    IF_NZ goto loop;
    RET;


found:
    CALL(aGetBattleAnimByte);
    LD_HL(BATTLEANIMSTRUCT_JUMPTABLE_INDEX);
    ADD_HL_BC;
    LD_hl_A;
    RET;

}

void BattleAnimCmd_BattlerGFX_1Row(void){
    LD_HL(wBattleAnimTileDict);

loop:
    LD_A_hl;
    AND_A_A;
    IF_Z goto okay;
    INC_HL;
    INC_HL;
    goto loop;


okay:
    LD_A(ANIM_GFX_PLAYERHEAD);
    LD_hli_A;
    LD_A((0x80 - 6 - 7) - BATTLEANIM_BASE_TILE);
    LD_hli_A;
    LD_A(ANIM_GFX_ENEMYFEET);
    LD_hli_A;
    LD_A((0x80 - 6) - BATTLEANIM_BASE_TILE);
    LD_hl_A;

    LD_HL(vTiles0 + LEN_2BPP_TILE * (0x80 - 6 - 7));
    LD_DE(vTiles2 + LEN_2BPP_TILE * 0x06);  // Enemy feet start tile
    LD_A(7 * LEN_2BPP_TILE);  // Enemy pic height
    LD_addr_A(wBattleAnimGFXTempPicHeight);
    LD_A(7);  // Copy 7x1 tiles
    CALL(aBattleAnimCmd_BattlerGFX_1Row_LoadFeet);
    LD_DE(vTiles2 + LEN_2BPP_TILE * 0x31);  // Player head start tile
    LD_A(6 * LEN_2BPP_TILE);  // Player pic height
    LD_addr_A(wBattleAnimGFXTempPicHeight);
    LD_A(6);  // Copy 6x1 tiles
    CALL(aBattleAnimCmd_BattlerGFX_1Row_LoadFeet);
    RET;


LoadFeet:
    PUSH_AF;
    PUSH_HL;
    PUSH_DE;
    LD_BC((BANK(aBattleAnimCmd_BattlerGFX_1Row) << 8) | 1);
    CALL(aRequest2bpp);
    POP_DE;
    LD_A_addr(wBattleAnimGFXTempPicHeight);
    LD_L_A;
    LD_H(0);
    ADD_HL_DE;
    LD_E_L;
    LD_D_H;
    POP_HL;
    LD_BC(1 * LEN_2BPP_TILE);
    ADD_HL_BC;
    POP_AF;
    DEC_A;
    IF_NZ goto LoadFeet;
    RET;

}

void BattleAnimCmd_BattlerGFX_2Row(void){
    LD_HL(wBattleAnimTileDict);

loop:
    LD_A_hl;
    AND_A_A;
    IF_Z goto okay;
    INC_HL;
    INC_HL;
    goto loop;


okay:
    LD_A(ANIM_GFX_PLAYERHEAD);
    LD_hli_A;
    LD_A((0x80 - 6 * 2 - 7 * 2) - BATTLEANIM_BASE_TILE);
    LD_hli_A;
    LD_A(ANIM_GFX_ENEMYFEET);
    LD_hli_A;
    LD_A((0x80 - 6 * 2) - BATTLEANIM_BASE_TILE);
    LD_hl_A;

    LD_HL(vTiles0 + LEN_2BPP_TILE * (0x80 - 6 * 2 - 7 * 2));
    LD_DE(vTiles2 + LEN_2BPP_TILE * 0x05);  // Enemy feet start tile
    LD_A(7 * LEN_2BPP_TILE);  // Enemy pic height
    LD_addr_A(wBattleAnimGFXTempPicHeight);
    LD_A(7);  // Copy 7x2 tiles
    CALL(aBattleAnimCmd_BattlerGFX_2Row_LoadHead);
    LD_DE(vTiles2 + LEN_2BPP_TILE * 0x31);  // Player head start tile
    LD_A(6 * LEN_2BPP_TILE);  // Player pic height
    LD_addr_A(wBattleAnimGFXTempPicHeight);
    LD_A(6);  // Copy 6x2 tiles
    CALL(aBattleAnimCmd_BattlerGFX_2Row_LoadHead);
    RET;


LoadHead:
    PUSH_AF;
    PUSH_HL;
    PUSH_DE;
    LD_BC((BANK(aBattleAnimCmd_BattlerGFX_2Row_LoadHead) << 8) | 2);
    CALL(aRequest2bpp);
    POP_DE;
    LD_A_addr(wBattleAnimGFXTempPicHeight);
    LD_L_A;
    LD_H(0);
    ADD_HL_DE;
    LD_E_L;
    LD_D_H;
    POP_HL;
    LD_BC(2 * LEN_2BPP_TILE);
    ADD_HL_BC;
    POP_AF;
    DEC_A;
    IF_NZ goto LoadHead;
    RET;

}

void BattleAnimCmd_CheckPokeball(void){
    CALLFAR(aGetPokeBallWobble);
    LD_A_C;
    LD_addr_A(wBattleAnimVar);
    RET;

}

void BattleAnimCmd_E7(void){
    RET;

}

void BattleAnimCmd_Transform(void){
    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(MBANK(awCurPartySpecies));
    LDH_addr_A(rSVBK);

    LD_A_addr(wCurPartySpecies);
    PUSH_AF;

    LDH_A_addr(hBattleTurn);
    AND_A_A;
    IF_Z goto player;

    LD_A_addr(wTempBattleMonSpecies);
    LD_addr_A(wCurPartySpecies);
    LD_HL(wBattleMonDVs);
    PREDEF(pGetUnownLetter);
    LD_DE(vTiles0 + LEN_2BPP_TILE * 0x00);
    PREDEF(pGetMonFrontpic);
    goto done;


player:
    LD_A_addr(wTempEnemyMonSpecies);
    LD_addr_A(wCurPartySpecies);
    LD_HL(wEnemyMonDVs);
    PREDEF(pGetUnownLetter);
    LD_DE(vTiles0 + LEN_2BPP_TILE * 0x00);
    PREDEF(pGetMonBackpic);


done:
    POP_AF;
    LD_addr_A(wCurPartySpecies);

    POP_AF;
    LDH_addr_A(rSVBK);
    RET;

}

void BattleAnimCmd_UpdateActorPic(void){
    LD_DE(vTiles0 + LEN_2BPP_TILE * 0x00);
    LDH_A_addr(hBattleTurn);
    AND_A_A;
    IF_Z goto player;

    LD_HL(vTiles2 + LEN_2BPP_TILE * 0x00);
    LD_B(0);
    LD_C(7 * 7);
    CALL(aRequest2bpp);
    RET;


player:
    LD_HL(vTiles2 + LEN_2BPP_TILE * 0x31);
    LD_B(0);
    LD_C(6 * 6);
    CALL(aRequest2bpp);
    RET;

}

void BattleAnimCmd_RaiseSub(void){
    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(1);  // unnecessary bankswitch?
    LDH_addr_A(rSVBK);

    XOR_A_A;  // BANK(sScratch)
    CALL(aOpenSRAM);

    return GetSubstitutePic();
}

void GetSubstitutePic(void){
//  //  used only for BANK(GetSubstitutePic)
    LD_HL(sScratch);
    LD_BC((7 * 7) * LEN_2BPP_TILE);

loop:
    XOR_A_A;
    LD_hli_A;
    DEC_BC;
    LD_A_C;
    OR_A_B;
    IF_NZ goto loop;

    LDH_A_addr(hBattleTurn);
    AND_A_A;
    IF_Z goto player;

    LD_HL(mMonsterSpriteGFX + 0 * LEN_2BPP_TILE);
    LD_DE(sScratch + (2 * 7 + 5) * LEN_2BPP_TILE);
    CALL(aGetSubstitutePic_CopyTile);
    LD_HL(mMonsterSpriteGFX + 1 * LEN_2BPP_TILE);
    LD_DE(sScratch + (3 * 7 + 5) * LEN_2BPP_TILE);
    CALL(aGetSubstitutePic_CopyTile);
    LD_HL(mMonsterSpriteGFX + 2 * LEN_2BPP_TILE);
    LD_DE(sScratch + (2 * 7 + 6) * LEN_2BPP_TILE);
    CALL(aGetSubstitutePic_CopyTile);
    LD_HL(mMonsterSpriteGFX + 3 * LEN_2BPP_TILE);
    LD_DE(sScratch + (3 * 7 + 6) * LEN_2BPP_TILE);
    CALL(aGetSubstitutePic_CopyTile);

    LD_HL(vTiles2 + LEN_2BPP_TILE * 0x00);
    LD_DE(sScratch);
    LD_BC((BANK(aGetSubstitutePic) << 8) | 7 * 7);
    CALL(aRequest2bpp);
    goto done;


player:
    LD_HL(mMonsterSpriteGFX + 4 * LEN_2BPP_TILE);
    LD_DE(sScratch + (2 * 6 + 4) * LEN_2BPP_TILE);
    CALL(aGetSubstitutePic_CopyTile);
    LD_HL(mMonsterSpriteGFX + 5 * LEN_2BPP_TILE);
    LD_DE(sScratch + (3 * 6 + 4) * LEN_2BPP_TILE);
    CALL(aGetSubstitutePic_CopyTile);
    LD_HL(mMonsterSpriteGFX + 6 * LEN_2BPP_TILE);
    LD_DE(sScratch + (2 * 6 + 5) * LEN_2BPP_TILE);
    CALL(aGetSubstitutePic_CopyTile);
    LD_HL(mMonsterSpriteGFX + 7 * LEN_2BPP_TILE);
    LD_DE(sScratch + (3 * 6 + 5) * LEN_2BPP_TILE);
    CALL(aGetSubstitutePic_CopyTile);

    LD_HL(vTiles2 + LEN_2BPP_TILE * 0x31);
    LD_DE(sScratch);
    LD_BC((BANK(aGetSubstitutePic) << 8) | 6 * 6);
    CALL(aRequest2bpp);


done:
    CALL(aCloseSRAM);

    POP_AF;
    LDH_addr_A(rSVBK);
    RET;


CopyTile:
    LD_BC(1 * LEN_2BPP_TILE);
    LD_A(BANK(aMonsterSpriteGFX));
    CALL(aFarCopyBytes);
    RET;

}

void BattleAnimCmd_MinimizeOpp(void){
    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(1);  // unnecessary bankswitch?
    LDH_addr_A(rSVBK);

    XOR_A_A;  // BANK(sScratch)
    CALL(aOpenSRAM);
    CALL(aGetMinimizePic);
    CALL(aRequest2bpp);
    CALL(aCloseSRAM);

    POP_AF;
    LDH_addr_A(rSVBK);
    RET;

}

void GetMinimizePic(void){
    LD_HL(sScratch);
    LD_BC((7 * 7) * LEN_2BPP_TILE);

loop:
    XOR_A_A;
    LD_hli_A;
    DEC_BC;
    LD_A_C;
    OR_A_B;
    IF_NZ goto loop;

    LDH_A_addr(hBattleTurn);
    AND_A_A;
    IF_Z goto player;

    LD_DE(sScratch + (3 * 7 + 5) * LEN_2BPP_TILE);
    CALL(aCopyMinimizePic);
    LD_HL(vTiles2 + LEN_2BPP_TILE * 0x00);
    LD_DE(sScratch);
    LD_BC((BANK(aGetMinimizePic) << 8) | 7 * 7);
    RET;


player:
    LD_DE(sScratch + (3 * 6 + 4) * LEN_2BPP_TILE);
    CALL(aCopyMinimizePic);
    LD_HL(vTiles2 + LEN_2BPP_TILE * 0x31);
    LD_DE(sScratch);
    LD_BC((BANK(aGetMinimizePic) << 8) | 6 * 6);
    RET;

}

void CopyMinimizePic(void){
    LD_HL(mMinimizePic);
    LD_BC(0x10);
    LD_A(BANK(aMinimizePic));
    CALL(aFarCopyBytes);
    RET;

}

void MinimizePic(void){
// INCBIN "gfx/battle/minimize.2bpp"

    return BattleAnimCmd_Minimize();
}

void BattleAnimCmd_Minimize(void){
    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(1);  // unnecessary bankswitch?
    LDH_addr_A(rSVBK);

    XOR_A_A;  // BANK(sScratch)
    CALL(aOpenSRAM);
    CALL(aGetMinimizePic);
    LD_HL(vTiles0 + LEN_2BPP_TILE * 0x00);
    CALL(aRequest2bpp);
    CALL(aCloseSRAM);

    POP_AF;
    LDH_addr_A(rSVBK);
    RET;

}

void BattleAnimCmd_DropSub(void){
    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(MBANK(awCurPartySpecies));
    LDH_addr_A(rSVBK);

    LD_A_addr(wCurPartySpecies);
    PUSH_AF;
    LDH_A_addr(hBattleTurn);
    AND_A_A;
    IF_Z goto player;

    CALLFAR(aDropEnemySub);
    goto done;


player:
    CALLFAR(aDropPlayerSub);


done:
    POP_AF;
    LD_addr_A(wCurPartySpecies);

    POP_AF;
    LDH_addr_A(rSVBK);
    RET;

}

void BattleAnimCmd_BeatUp(void){
    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(MBANK(awCurPartySpecies));
    LDH_addr_A(rSVBK);

    LD_A_addr(wCurPartySpecies);
    PUSH_AF;

    LD_A_addr(wBattleAnimParam);
    LD_addr_A(wCurPartySpecies);

    LDH_A_addr(hBattleTurn);
    AND_A_A;
    IF_Z goto player;

    LD_HL(wBattleMonDVs);
    PREDEF(pGetUnownLetter);
    LD_DE(vTiles2 + LEN_2BPP_TILE * 0x00);
    PREDEF(pGetMonFrontpic);
    goto done;


player:
    LD_HL(wEnemyMonDVs);
    PREDEF(pGetUnownLetter);
    LD_DE(vTiles2 + LEN_2BPP_TILE * 0x31);
    PREDEF(pGetMonBackpic);


done:
    POP_AF;
    LD_addr_A(wCurPartySpecies);
    LD_B(SCGB_BATTLE_COLORS);
    CALL(aGetSGBLayout);

    POP_AF;
    LDH_addr_A(rSVBK);
    RET;

}

void BattleAnimCmd_OAMOn(void){
    XOR_A_A;
    LDH_addr_A(hOAMUpdate);
    RET;

}

void BattleAnimCmd_OAMOff(void){
    LD_A(0x1);
    LDH_addr_A(hOAMUpdate);
    RET;

}

void BattleAnimCmd_KeepSprites(void){
    LD_HL(wBattleAnimFlags);
    SET_hl(BATTLEANIM_KEEPSPRITES_F);
    RET;

}

void BattleAnimCmd_F5(void){
    RET;

}

void BattleAnimCmd_F6(void){
    RET;

}

void BattleAnimCmd_F7(void){
    RET;

}

void BattleAnimCmd_Sound(void){
    CALL(aGetBattleAnimByte);
    LD_E_A;
    SRL_A;
    SRL_A;
    LD_addr_A(wSFXDuration);
    CALL(aBattleAnimCmd_Sound_GetCryTrack);
    maskbits(NUM_NOISE_CHANS, 0);
    LD_addr_A(wCryTracks);

    LD_E_A;
    LD_D(0);
    LD_HL(mBattleAnimCmd_Sound_GetPanning);
    ADD_HL_DE;
    LD_A_hl;
    LD_addr_A(wStereoPanningMask);

    CALL(aGetBattleAnimByte);
    LD_E_A;
    LD_D(0);
    CALLFAR(aPlayStereoSFX);

    RET;


GetPanning:
    //db ['0xf0', '0x0f', '0xf0', '0x0f'];


GetCryTrack:
    LDH_A_addr(hBattleTurn);
    AND_A_A;
    IF_NZ goto enemy;

    LD_A_E;
    RET;


enemy:
    LD_A_E;
    XOR_A(1);
    RET;

}

void BattleAnimCmd_Cry(void){
    CALL(aGetBattleAnimByte);
    maskbits(NUM_NOISE_CHANS, 0);
    LD_E_A;
    LD_D(0);
    LD_HL(mBattleAnimCmd_Cry_CryData);
    for(int rept = 0; rept < 4; rept++){
    ADD_HL_DE;
    }

    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(MBANK(awEnemyMon));  // wBattleMon is in WRAM0, but wEnemyMon is in WRAMX
    LDH_addr_A(rSVBK);

    LDH_A_addr(hBattleTurn);
    AND_A_A;
    IF_NZ goto enemy;

    LD_A(0xf0);
    LD_addr_A(wCryTracks);
    LD_A_addr(wBattleMonSpecies);
    goto done_cry_tracks;


enemy:
    LD_A(0x0f);
    LD_addr_A(wCryTracks);
    LD_A_addr(wEnemyMonSpecies);


done_cry_tracks:
    PUSH_HL;
    CALL(aLoadCry);
    POP_HL;
    IF_C goto done;

    LD_A_hli;
    LD_C_A;
    LD_A_hli;
    LD_B_A;

    PUSH_HL;
    LD_HL(wCryPitch);
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    ADD_HL_BC;
    LD_A_L;
    LD_addr_A(wCryPitch);
    LD_A_H;
    LD_addr_A(wCryPitch + 1);
    POP_HL;

    LD_A_hli;
    LD_C_A;
    LD_B_hl;
    LD_HL(wCryLength);
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    ADD_HL_BC;

    LD_A_L;
    LD_addr_A(wCryLength);
    LD_A_H;
    LD_addr_A(wCryLength + 1);
    LD_A(1);
    LD_addr_A(wStereoPanningMask);

    CALLFAR(av_PlayCry);


done:
    POP_AF;
    LDH_addr_A(rSVBK);
    RET;


CryData:
//  +pitch, +length
    //dw ['0x0000', '0x00c0'];
    //dw ['0x0000', '0x0040'];
    //dw ['0x0000', '0x0000'];
    //dw ['0x0000', '0x0000'];

    return PlayHitSound();
}

void PlayHitSound(void){
    LD_A_addr(wNumHits);
    CP_A(0x1);
    IF_Z goto okay;
    CP_A(0x4);
    RET_NZ ;


okay:
    LD_A_addr(wTypeModifier);
    AND_A(0x7f);
    RET_Z ;

    CP_A(EFFECTIVE);
    LD_DE(SFX_DAMAGE);
    IF_Z goto play;

    LD_DE(SFX_SUPER_EFFECTIVE);
    IF_NC goto play;

    LD_DE(SFX_NOT_VERY_EFFECTIVE);


play:
    CALL(aPlaySFX);
    RET;

}

void BattleAnimAssignPals(void){
    LDH_A_addr(hCGB);
    AND_A_A;
    IF_NZ goto cgb;
    LDH_A_addr(hSGB);
    AND_A_A;
    LD_A(0b11100000);
    IF_Z goto sgb;
    LD_A(0b11110000);


sgb:
    LD_addr_A(wOBP0);
    LD_A(0b11100100);
    LD_addr_A(wBGP);
    LD_addr_A(wOBP1);
    RET;


cgb:
    LD_A(0b11100100);
    LD_addr_A(wBGP);
    LD_addr_A(wOBP0);
    LD_addr_A(wOBP1);
    CALL(aDmgToCgbBGPals);
    LD_DE((0b11100100 << 8) | 0b11100100);
    CALL(aDmgToCgbObjPals);
    RET;

}

void ClearBattleAnims(void){
//  Clear animation block
    LD_HL(wLYOverrides);
    LD_BC(wBattleAnimEnd - wLYOverrides);

loop:
    LD_hl(0);
    INC_HL;
    DEC_BC;
    LD_A_C;
    OR_A_B;
    IF_NZ goto loop;

    LD_HL(wFXAnimID);
    LD_E_hl;
    INC_HL;
    LD_D_hl;
    LD_HL(mBattleAnimations);
    ADD_HL_DE;
    ADD_HL_DE;
    CALL(aGetBattleAnimPointer);
    CALL(aBattleAnimAssignPals);
    CALL(aBattleAnimDelayFrame);
    RET;

}

void BattleAnim_RevertPals(void){
    CALL(aWaitTop);
    LD_A(0b11100100);
    LD_addr_A(wBGP);
    LD_addr_A(wOBP0);
    LD_addr_A(wOBP1);
    CALL(aDmgToCgbBGPals);
    LD_DE((0b11100100 << 8) | 0b11100100);
    CALL(aDmgToCgbObjPals);
    XOR_A_A;
    LDH_addr_A(hSCX);
    LDH_addr_A(hSCY);
    CALL(aBattleAnimDelayFrame);
    LD_A(0x1);
    LDH_addr_A(hBGMapMode);
    RET;

}

void BattleAnim_SetBGPals(void){
    LDH_addr_A(rBGP);
    LDH_A_addr(hCGB);
    AND_A_A;
    RET_Z ;
    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(MBANK(awBGPals1));
    LDH_addr_A(rSVBK);
    LD_HL(wBGPals2);
    LD_DE(wBGPals1);
    LDH_A_addr(rBGP);
    LD_B_A;
    LD_C(7);
    CALL(aCopyPals);
    LD_HL(wOBPals2);
    LD_DE(wOBPals1);
    LDH_A_addr(rBGP);
    LD_B_A;
    LD_C(2);
    CALL(aCopyPals);
    POP_AF;
    LDH_addr_A(rSVBK);
    LD_A(TRUE);
    LDH_addr_A(hCGBPalUpdate);
    RET;

}

void BattleAnim_SetOBPals(void){
    LDH_addr_A(rOBP0);
    LDH_A_addr(hCGB);
    AND_A_A;
    RET_Z ;
    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(MBANK(awOBPals1));
    LDH_addr_A(rSVBK);
    LD_HL(wOBPals2 + PALETTE_SIZE * PAL_BATTLE_OB_GRAY);
    LD_DE(wOBPals1 + PALETTE_SIZE * PAL_BATTLE_OB_GRAY);
    LDH_A_addr(rOBP0);
    LD_B_A;
    LD_C(2);
    CALL(aCopyPals);
    POP_AF;
    LDH_addr_A(rSVBK);
    LD_A(TRUE);
    LDH_addr_A(hCGBPalUpdate);
    RET;

}

void BattleAnim_UpdateOAM_All(void){
    // LD_A(0);
    // LD_addr_A(wBattleAnimOAMPointerLo);
    uint8_t oamIndex = 0;
    // LD_HL(wActiveAnimObjects);
    struct BattleAnim* hl = wram->wAnimObject;
    // LD_E(NUM_ANIM_OBJECTS);
    uint8_t e = NUM_ANIM_OBJECTS;

    do {
    // loop:
        // LD_A_hl;
        // AND_A_A;
        // IF_Z goto next;
        if(hl->index == 0)
            continue;
        // LD_C_L;
        // LD_B_H;
        // PUSH_HL;
        // PUSH_DE;
        // CALL(aDoBattleAnimFrame);
        DoBattleAnimFrame_Conv(hl);
        // CALL(aBattleAnimOAMUpdate);
        bool error = BattleAnimOAMUpdate_Conv(hl, &oamIndex);
        // POP_DE;
        // POP_HL;
        // IF_C goto done;
        if(error)
            return;

    // next:
        // LD_BC(BATTLEANIMSTRUCT_LENGTH);
        // ADD_HL_BC;
        // DEC_E;
        // IF_NZ goto loop;
    } while(hl++, --e != 0);
    // LD_A_addr(wBattleAnimOAMPointerLo);
    // LD_L_A;
    // LD_H(HIGH(wVirtualOAM));

    while(oamIndex < NUM_SPRITE_OAM_STRUCTS) {
    // loop2:
        // LD_A_L;
        // CP_A(LOW(wVirtualOAMEnd));
        // IF_NC goto done;
        // XOR_A_A;
        // LD_hli_A;
        wram->wVirtualOAMSprite[oamIndex].yCoord = 0;
        wram->wVirtualOAMSprite[oamIndex].xCoord = 0;
        wram->wVirtualOAMSprite[oamIndex].tileID = 0;
        wram->wVirtualOAMSprite[oamIndex].attributes = 0;
        // goto loop2;
        oamIndex++;
    }

// done:
    // RET;
}
