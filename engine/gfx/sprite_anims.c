#include "../../constants.h"
#include "sprite_anims.h"

void DoAnimFrame(void){
    LD_HL(SPRITEANIMSTRUCT_ANIM_SEQ_ID);
    ADD_HL_BC;
    LD_E_hl;
    LD_D(0);
    LD_HL(mDoAnimFrame_Jumptable);
    ADD_HL_DE;
    ADD_HL_DE;
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    JP_hl;


Jumptable:
//  entries correspond to SPRITE_ANIM_SEQ_* constants (see constants/sprite_anim_constants.asm)
    //table_width ['2', 'DoAnimFrame.Jumptable']
    //dw ['AnimSeq_Null'];
    //dw ['AnimSeq_PartyMon'];
    //dw ['AnimSeq_PartyMonSwitch'];
    //dw ['AnimSeq_PartyMonSelected'];
    //dw ['AnimSeq_GSTitleTrail'];
    //dw ['AnimSeq_NamingScreenCursor'];
    //dw ['AnimSeq_GameFreakLogo'];
    //dw ['AnimSeq_GSGameFreakLogoStar'];
    //dw ['AnimSeq_GSGameFreakLogoSparkle'];
    //dw ['AnimSeq_SlotsGolem'];
    //dw ['AnimSeq_SlotsChansey'];
    //dw ['AnimSeq_SlotsChanseyEgg'];
    //dw ['AnimSeq_MailCursor'];
    //dw ['AnimSeq_UnusedCursor'];
    //dw ['AnimSeq_MemoryGameCursor'];
    //dw ['AnimSeq_PokegearArrow'];
    //dw ['AnimSeq_TradePokeBall'];
    //dw ['AnimSeq_TradeTubeBulge'];
    //dw ['AnimSeq_TrademonInTube'];
    //dw ['AnimSeq_RevealNewMon'];
    //dw ['AnimSeq_RadioTuningKnob'];
    //dw ['AnimSeq_CutLeaves'];
    //dw ['AnimSeq_FlyFrom'];
    //dw ['AnimSeq_FlyLeaf'];
    //dw ['AnimSeq_FlyTo'];
    //dw ['AnimSeq_GSIntroHoOhLugia'];
    //dw ['AnimSeq_EZChatCursor'];
    //dw ['AnimSeq_MobileTradeSentPulse'];
    //dw ['AnimSeq_MobileTradeOTPulse'];
    //dw ['AnimSeq_IntroSuicune'];
    //dw ['AnimSeq_IntroPichuWooper'];
    //dw ['AnimSeq_Celebi'];
    //dw ['AnimSeq_IntroUnown'];
    //dw ['AnimSeq_IntroUnownF'];
    //dw ['AnimSeq_IntroSuicuneAway'];
    //assert_table_length ['NUM_SPRITE_ANIM_SEQS']

    return AnimSeq_Null();
}

void AnimSeq_Null(void){
    RET;

}

void AnimSeq_PartyMon(void){
    LD_A_addr(wMenuCursorY);

    LD_HL(SPRITEANIMSTRUCT_INDEX);
    ADD_HL_BC;
    CP_A_hl;
    JR_Z (mAnimSeq_PartyMonSwitch);

    LD_HL(SPRITEANIMSTRUCT_XCOORD);
    ADD_HL_BC;
    LD_hl(8 * 2);

    LD_HL(SPRITEANIMSTRUCT_YOFFSET);
    ADD_HL_BC;
    LD_hl(0);
    RET;

}

void AnimSeq_PartyMonSwitch(void){
    LD_HL(SPRITEANIMSTRUCT_XCOORD);
    ADD_HL_BC;
    LD_hl(8 * 3);

    LD_HL(SPRITEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_A_hl;
    LD_D_A;
    INC_hl;
    AND_A(0xf);
    RET_NZ ;

    LD_HL(SPRITEANIMSTRUCT_VAR2);
    ADD_HL_BC;
    LD_E_hl;

    LD_HL(SPRITEANIMSTRUCT_YOFFSET);
    ADD_HL_BC;
    LD_A_D;
    AND_A(0x10);  // bit 4
    IF_Z goto load_zero;
    LD_A_E;
    AND_A_A;
    IF_Z goto load_minus_two;
    CP_A(0x1);
    IF_Z goto load_minus_one;

load_zero:
    XOR_A_A;
    LD_hl_A;
    RET;


load_minus_one:
    LD_A(-1);
    LD_hl_A;
    RET;


load_minus_two:
    LD_A(-2);
    LD_hl_A;
    RET;

}

void AnimSeq_PartyMonSelected(void){
    LD_A_addr(wMenuCursorY);

    LD_HL(SPRITEANIMSTRUCT_INDEX);
    ADD_HL_BC;
    CP_A_hl;
    IF_Z goto three_offset_right;

    LD_HL(SPRITEANIMSTRUCT_XCOORD);
    ADD_HL_BC;
    LD_hl(8 * 2);
    RET;


three_offset_right:
    LD_HL(SPRITEANIMSTRUCT_XCOORD);
    ADD_HL_BC;
    LD_hl(8 * 3);
    RET;

}

void AnimSeq_GSTitleTrail(void){
    CALL(aAnimSeqs_AnonJumptable);
    JP_hl;

anon_dw:
    //dw ['.zero'];
    //dw ['.one'];


zero:
    CALL(aAnimSeqs_IncAnonJumptableIndex);

    LD_HL(SPRITEANIMSTRUCT_INDEX);
    ADD_HL_BC;
    LD_A_hl;

    LD_HL(SPRITEANIMSTRUCT_VAR2);
    ADD_HL_BC;
    AND_A(0x3);
    LD_hl_A;
    INC_hl;
    SWAP_A;

    LD_HL(SPRITEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_hl_A;


one:
    LD_HL(SPRITEANIMSTRUCT_XCOORD);
    ADD_HL_BC;
    LD_A_hl;
    CP_A(0xa4);
    IF_NC goto delete;

    LD_HL(SPRITEANIMSTRUCT_VAR2);
    ADD_HL_BC;
    ADD_A(4);

    LD_HL(SPRITEANIMSTRUCT_XCOORD);
    ADD_HL_BC;
    LD_hl_A;

    LD_HL(SPRITEANIMSTRUCT_YCOORD);
    ADD_HL_BC;
    INC_hl;

    LD_HL(SPRITEANIMSTRUCT_VAR2);
    ADD_HL_BC;
    LD_A_hl;
    SLA_A;
    SLA_A;

    LD_D(2);
    LD_HL(SPRITEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_A_hl;
    ADD_A(3);
    LD_hl_A;
    CALL(aAnimSeqs_Sine);

    LD_HL(SPRITEANIMSTRUCT_YOFFSET);
    ADD_HL_BC;
    LD_hl_A;
    RET;


delete:
    CALL(aDeinitializeSprite);
    RET;

}

void AnimSeq_GSIntroHoOhLugia(void){
    LD_HL(SPRITEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_A_hl;
    INC_A;
    LD_hl_A;
    LD_D(2);
    CALL(aAnimSeqs_Sine);

    LD_HL(SPRITEANIMSTRUCT_YOFFSET);
    ADD_HL_BC;
    LD_hl_A;
    RET;

}

void AnimSeq_NamingScreenCursor(void){
    CALLFAR(aNamingScreen_AnimateCursor);
    RET;

}

void AnimSeq_MailCursor(void){
    CALLFAR(aComposeMail_AnimateCursor);
    RET;

}

void AnimSeq_GameFreakLogo(void){
    CALLFAR(aGameFreakLogoSpriteAnim);
    RET;

}

void AnimSeq_GSGameFreakLogoStar(void){
    LD_HL(SPRITEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_A_hl;
    AND_A_A;
    IF_Z goto delete;

    DEC_hl;
    DEC_hl;
    LD_D_A;
    AND_A(0x1f);
    IF_NZ goto stay;
    LD_HL(SPRITEANIMSTRUCT_VAR2);
    ADD_HL_BC;
    DEC_hl;


stay:
    LD_HL(SPRITEANIMSTRUCT_JUMPTABLE_INDEX);
    ADD_HL_BC;
    LD_A_hl;
    PUSH_AF;
    PUSH_DE;
    CALL(aAnimSeqs_Sine);

    LD_HL(SPRITEANIMSTRUCT_YOFFSET);
    ADD_HL_BC;
    LD_hl_A;
    POP_DE;
    POP_AF;
    CALL(aAnimSeqs_Cosine);

    LD_HL(SPRITEANIMSTRUCT_XOFFSET);
    ADD_HL_BC;
    LD_hl_A;

    LD_HL(SPRITEANIMSTRUCT_VAR2);
    ADD_HL_BC;
    LD_A_hl;

    LD_HL(SPRITEANIMSTRUCT_JUMPTABLE_INDEX);
    ADD_HL_BC;
    ADD_A_hl;
    LD_hl_A;
    RET;


delete:
    LD_A(1);
    LD_addr_A(wIntroSceneFrameCounter);
    CALL(aDeinitializeSprite);
    RET;

}

void AnimSeq_GSGameFreakLogoSparkle(void){
    LD_HL(SPRITEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_A_hli;
    OR_A_hl;
    IF_Z goto delete;

    LD_HL(SPRITEANIMSTRUCT_VAR4);
    ADD_HL_BC;
    LD_D_hl;

    LD_HL(SPRITEANIMSTRUCT_JUMPTABLE_INDEX);
    ADD_HL_BC;
    LD_A_hl;
    PUSH_AF;
    PUSH_DE;
    CALL(aAnimSeqs_Sine);

    LD_HL(SPRITEANIMSTRUCT_YOFFSET);
    ADD_HL_BC;
    LD_hl_A;
    POP_DE;
    POP_AF;
    CALL(aAnimSeqs_Cosine);

    LD_HL(SPRITEANIMSTRUCT_XOFFSET);
    ADD_HL_BC;
    LD_hl_A;

    LD_HL(SPRITEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_E_hl;
    INC_HL;
    LD_D_hl;

    LD_HL(SPRITEANIMSTRUCT_VAR3);
    ADD_HL_BC;
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    ADD_HL_DE;
    LD_E_L;
    LD_D_H;

    LD_HL(SPRITEANIMSTRUCT_VAR3);
    ADD_HL_BC;
    LD_hl_E;
    INC_HL;
    LD_hl_D;

    LD_HL(SPRITEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    LD_DE(-0x10);
    ADD_HL_DE;
    LD_E_L;
    LD_D_H;

    LD_HL(SPRITEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_hl_E;
    INC_HL;
    LD_hl_D;

    LD_HL(SPRITEANIMSTRUCT_JUMPTABLE_INDEX);
    ADD_HL_BC;
    LD_A_hl;
    XOR_A(0x20);
    LD_hl_A;
    RET;


delete:
    CALL(aDeinitializeSprite);
    RET;

}

void AnimSeq_SlotsGolem(void){
    CALLFAR(aSlots_AnimateGolem);
    RET;

}

void AnimSeq_SlotsChansey(void){
    CALLFAR(aSlots_AnimateChansey);
    LD_HL(wSlotsDelay);
    LD_A_hl;
    CP_A(0x2);
    RET_NZ ;
    LD_hl(0x3);
    LD_A(SPRITE_ANIM_FRAMESET_SLOTS_CHANSEY_2);
    CALL(av_ReinitSpriteAnimFrame);
    RET;

}

void AnimSeq_SlotsChanseyEgg(void){
    LD_HL(SPRITEANIMSTRUCT_JUMPTABLE_INDEX);
    ADD_HL_BC;
    LD_A_hl;
    DEC_hl;
    LD_E_A;
    AND_A(0x1);
    IF_Z goto move_vertical;

    LD_HL(SPRITEANIMSTRUCT_XCOORD);
    ADD_HL_BC;
    LD_A_hl;
    CP_A(15 * 8);
    IF_C goto move_right;
    CALL(aDeinitializeSprite);
    LD_A(0x4);
    LD_addr_A(wSlotsDelay);
    LD_DE(SFX_PLACE_PUZZLE_PIECE_DOWN);
    CALL(aPlaySFX);
    RET;


move_right:
    INC_hl;

move_vertical:
    LD_A_E;
    LD_D(32);
    CALL(aAnimSeqs_Sine);

    LD_HL(SPRITEANIMSTRUCT_YOFFSET);
    ADD_HL_BC;
    LD_hl_A;
    RET;

}

void AnimSeq_UnusedCursor(void){
    CALLFAR(aUnusedCursor_InterpretJoypad_AnimateCursor);
    RET;

}

void AnimSeq_PokegearArrow(void){
    CALLFAR(aAnimatePokegearModeIndicatorArrow);
    RET;

}

void AnimSeq_MemoryGameCursor(void){
    CALLFAR(aMemoryGame_InterpretJoypad_AnimateCursor);
    RET;

}

void AnimSeq_TradePokeBall(void){
    CALL(aAnimSeqs_AnonJumptable);
    JP_hl;

anon_dw:
    //dw ['.zero'];
    //dw ['.one'];
    //dw ['.two'];
    //dw ['.three'];
    //dw ['.four'];
    //dw ['.delete'];


zero:
    LD_A(SPRITE_ANIM_FRAMESET_TRADE_POKE_BALL_WOBBLE);
    CALL(av_ReinitSpriteAnimFrame);

    LD_HL(SPRITEANIMSTRUCT_JUMPTABLE_INDEX);
    ADD_HL_BC;
    LD_hl(2);  // .two

    LD_HL(SPRITEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_hl(0x20);
    RET;


two:
    LD_HL(SPRITEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_A_hl;
    AND_A_A;
    IF_Z goto next;
    DEC_hl;
    RET;


next:
    CALL(aAnimSeqs_IncAnonJumptableIndex);

    LD_HL(SPRITEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_hl(0x40);


three:
    LD_HL(SPRITEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_A_hl;
    CP_A(48);
    IF_C goto done;
    DEC_hl;
    LD_D(40);
    CALL(aAnimSeqs_Sine);

    LD_HL(SPRITEANIMSTRUCT_YOFFSET);
    ADD_HL_BC;
    LD_hl_A;
    RET;


done:
    LD_DE(SFX_GOT_SAFARI_BALLS);
    CALL(aPlaySFX);
    goto delete;


one:
    LD_HL(SPRITEANIMSTRUCT_JUMPTABLE_INDEX);
    ADD_HL_BC;
    LD_hl(0x4);

    LD_HL(SPRITEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_hl(0x30);

    LD_HL(SPRITEANIMSTRUCT_VAR2);
    ADD_HL_BC;
    LD_hl(0x24);
    RET;


four:
    LD_HL(SPRITEANIMSTRUCT_VAR2);
    ADD_HL_BC;
    LD_A_hl;
    AND_A_A;
    IF_Z goto done2;

    LD_D_A;
    LD_HL(SPRITEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_A_hl;
    CALL(aSprites_Sine);

    LD_HL(SPRITEANIMSTRUCT_YOFFSET);
    ADD_HL_BC;
    LD_hl_A;

    LD_HL(SPRITEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    INC_hl;
    LD_A_hl;
    AND_A(0x3f);
    RET_NZ ;

    LD_HL(SPRITEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_hl(0x20);

    LD_HL(SPRITEANIMSTRUCT_VAR2);
    ADD_HL_BC;
    LD_A_hl;
    SUB_A(0xc);
    LD_hl_A;
    LD_DE(SFX_SWITCH_POKEMON);
    CALL(aPlaySFX);
    RET;


done2:
    XOR_A_A;

    LD_HL(SPRITEANIMSTRUCT_YOFFSET);
    ADD_HL_BC;
    LD_hl_A;
    CALL(aAnimSeqs_IncAnonJumptableIndex);
    RET;


delete:
    CALL(aDeinitializeSprite);
    RET;

}

void AnimSeq_TradeTubeBulge(void){
    LD_HL(SPRITEANIMSTRUCT_XCOORD);
    ADD_HL_BC;
    LD_A_hl;
    INC_hl;
    INC_hl;
    CP_A(0xb0);
    IF_NC goto delete;
    AND_A(0x3);
    RET_NZ ;
    LD_DE(SFX_POKEBALLS_PLACED_ON_TABLE);
    CALL(aPlaySFX);
    RET;


delete:
    CALL(aDeinitializeSprite);
    RET;

}

void AnimSeq_TrademonInTube(void){
    CALLFAR(aTradeAnim_AnimateTrademonInTube);
    RET;

}

void AnimSeq_RevealNewMon(void){
    LD_HL(SPRITEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_A_hl;
    CP_A(0x80);
    IF_NC goto finish_EggShell;
    LD_D_A;
    ADD_A(8);
    LD_hl_A;

    LD_HL(SPRITEANIMSTRUCT_JUMPTABLE_INDEX);
    ADD_HL_BC;
    LD_A_hl;
    XOR_A(0x20);
    LD_hl_A;

    PUSH_AF;
    PUSH_DE;
    CALL(aAnimSeqs_Sine);

    LD_HL(SPRITEANIMSTRUCT_YOFFSET);
    ADD_HL_BC;
    LD_hl_A;

    POP_DE;
    POP_AF;
    CALL(aAnimSeqs_Cosine);

    LD_HL(SPRITEANIMSTRUCT_XOFFSET);
    ADD_HL_BC;
    LD_hl_A;
    RET;


finish_EggShell:
    CALL(aDeinitializeSprite);
    RET;

}

void AnimSeq_RadioTuningKnob(void){
    CALLFAR(aAnimateTuningKnob);
    RET;

}

void AnimSeq_CutLeaves(void){
    LD_HL(SPRITEANIMSTRUCT_VAR2);
    ADD_HL_BC;
    LD_E_hl;
    INC_HL;
    LD_D_hl;
    LD_HL(0x80);
    ADD_HL_DE;
    LD_E_L;
    LD_D_H;

    LD_HL(SPRITEANIMSTRUCT_VAR2);
    ADD_HL_BC;
    LD_hl_E;
    INC_HL;
    LD_hl_D;

    LD_HL(SPRITEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_A_hl;
    INC_hl;
    INC_hl;
    INC_hl;
    PUSH_AF;
    PUSH_DE;
    CALL(aAnimSeqs_Sine);

    LD_HL(SPRITEANIMSTRUCT_YOFFSET);
    ADD_HL_BC;
    LD_hl_A;
    POP_DE;
    POP_AF;
    CALL(aAnimSeqs_Cosine);

    LD_HL(SPRITEANIMSTRUCT_XOFFSET);
    ADD_HL_BC;
    LD_hl_A;
    RET;

}

void AnimSeq_FlyFrom(void){
    LD_HL(SPRITEANIMSTRUCT_YCOORD);
    ADD_HL_BC;
    LD_A_hl;
    AND_A_A;
    RET_Z ;

    LD_HL(SPRITEANIMSTRUCT_VAR2);
    ADD_HL_BC;
    LD_A_hl;
    INC_hl;
    CP_A(0x40);
    RET_C ;

    LD_HL(SPRITEANIMSTRUCT_YCOORD);
    ADD_HL_BC;
    DEC_hl;
    DEC_hl;

    LD_HL(SPRITEANIMSTRUCT_VAR4);
    ADD_HL_BC;
    LD_A_hl;
    LD_D_A;
    CP_A(0x40);
    IF_NC goto skip;
    ADD_A(8);
    LD_hl_A;

skip:
    LD_HL(SPRITEANIMSTRUCT_VAR3);
    ADD_HL_BC;
    LD_A_hl;
    INC_hl;
    CALL(aAnimSeqs_Cosine);

    LD_HL(SPRITEANIMSTRUCT_XOFFSET);
    ADD_HL_BC;
    LD_hl_A;
    RET;

}

void AnimSeq_FlyLeaf(void){
    LD_HL(SPRITEANIMSTRUCT_XCOORD);
    ADD_HL_BC;
    LD_A_hl;
    CP_A(-9 * 8);
    IF_NC goto delete_leaf;
    INC_hl;
    INC_hl;

    LD_HL(SPRITEANIMSTRUCT_YCOORD);
    ADD_HL_BC;
    DEC_hl;

    LD_D(0x40);
    LD_HL(SPRITEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_A_hl;
    INC_hl;
    CALL(aAnimSeqs_Cosine);

    LD_HL(SPRITEANIMSTRUCT_XOFFSET);
    ADD_HL_BC;
    LD_hl_A;
    RET;


delete_leaf:
    CALL(aDeinitializeSprite);
    RET;

}

void AnimSeq_FlyTo(void){
    LD_HL(SPRITEANIMSTRUCT_YCOORD);
    ADD_HL_BC;
    LD_A_hl;
    CP_A(10 * 8 + 4);
    RET_Z ;

    LD_HL(SPRITEANIMSTRUCT_YCOORD);
    ADD_HL_BC;
    INC_hl;
    INC_hl;

    LD_HL(SPRITEANIMSTRUCT_VAR4);
    ADD_HL_BC;
    LD_A_hl;
    LD_D_A;
    AND_A_A;
    IF_Z goto stay;
    SUB_A(0x2);
    LD_hl_A;

stay:
    LD_HL(SPRITEANIMSTRUCT_VAR3);
    ADD_HL_BC;
    LD_A_hl;
    INC_hl;
    CALL(aAnimSeqs_Cosine);

    LD_HL(SPRITEANIMSTRUCT_XOFFSET);
    ADD_HL_BC;
    LD_hl_A;
    RET;

}

void AnimSeq_MobileTradeSentPulse(void){
    FARCALL(aMobileTradeAnim_AnimateSentPulse);
    RET;

}

void AnimSeq_MobileTradeOTPulse(void){
    FARCALL(aMobileTradeAnim_AnimateOTPulse);
    RET;

}

void AnimSeq_IntroSuicune(void){
    LD_A_addr(wIntroSceneTimer);
    AND_A_A;
    IF_NZ goto continue_;
    RET;


continue_:
    LD_HL(SPRITEANIMSTRUCT_YOFFSET);
    ADD_HL_BC;
    LD_hl(0x0);

    LD_HL(SPRITEANIMSTRUCT_VAR2);
    ADD_HL_BC;
    LD_A_hl;
    ADD_A(2);
    LD_hl_A;
    XOR_A(0xff);
    INC_A;
    LD_D(32);
    CALL(aAnimSeqs_Sine);

    LD_HL(SPRITEANIMSTRUCT_YOFFSET);
    ADD_HL_BC;
    LD_hl_A;
    LD_A(SPRITE_ANIM_FRAMESET_INTRO_SUICUNE_2);
    CALL(av_ReinitSpriteAnimFrame);
    RET;

}

void AnimSeq_IntroPichuWooper(void){
    LD_HL(SPRITEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_A_hl;
    CP_A(20);
    IF_NC goto done;
    ADD_A(2);
    LD_hl_A;
    XOR_A(0xff);
    INC_A;
    LD_D(32);
    CALL(aAnimSeqs_Sine);

    LD_HL(SPRITEANIMSTRUCT_YOFFSET);
    ADD_HL_BC;
    LD_hl_A;

done:
    RET;

}

void AnimSeq_IntroUnown(void){
    LD_HL(SPRITEANIMSTRUCT_JUMPTABLE_INDEX);
    ADD_HL_BC;
    LD_D_hl;
    INC_hl;
    INC_hl;
    INC_hl;
    LD_HL(SPRITEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_A_hl;
    PUSH_AF;
    PUSH_DE;
    CALL(aAnimSeqs_Sine);

    LD_HL(SPRITEANIMSTRUCT_YOFFSET);
    ADD_HL_BC;
    LD_hl_A;
    POP_DE;
    POP_AF;
    CALL(aAnimSeqs_Cosine);

    LD_HL(SPRITEANIMSTRUCT_XOFFSET);
    ADD_HL_BC;
    LD_hl_A;
    RET;

}

void AnimSeq_IntroUnownF(void){
    LD_A_addr(wSlotsDelay);
    CP_A(0x40);
    RET_NZ ;
    LD_A(SPRITE_ANIM_FRAMESET_INTRO_UNOWN_F_2);
    CALL(av_ReinitSpriteAnimFrame);
    RET;

}

void AnimSeq_IntroSuicuneAway(void){
    LD_HL(SPRITEANIMSTRUCT_YCOORD);
    ADD_HL_BC;
    LD_A_hl;
    ADD_A(16);
    LD_hl_A;
    RET;

}

void AnimSeq_EZChatCursor(void){
    FARCALL(aAnimateEZChatCursor);
    RET;

}

void AnimSeq_Celebi(void){
    FARCALL(aUpdateCelebiPosition);
    RET;

}

void AnimSeqs_AnonJumptable(void){
    LD_HL_SP(0);
    LD_E_hl;
    INC_HL;
    LD_D_hl;
    INC_DE;

    LD_HL(SPRITEANIMSTRUCT_JUMPTABLE_INDEX);
    ADD_HL_BC;
    LD_L_hl;
    LD_H(0);
    ADD_HL_HL;
    ADD_HL_DE;
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    RET;

}

void AnimSeqs_IncAnonJumptableIndex(void){
    LD_HL(SPRITEANIMSTRUCT_JUMPTABLE_INDEX);
    ADD_HL_BC;
    INC_hl;
    RET;

}

void AnimSeqs_Sine(void){
    CALL(aSprites_Sine);
    RET;

}

void AnimSeqs_Cosine(void){
    CALL(aSprites_Cosine);
    RET;

}
