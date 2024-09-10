#include "../../constants.h"
#include "sprite_anims.h"
#include "sprites.h"
#include "../../home/audio.h"
#include "../movie/splash.h"
#include "../movie/trade_animation.h"
#include "../pokegear/pokegear.h"
#include "../menus/naming_screen.h"
#include "../games/slot_machine.h"
#include "../events/celebi.h"

static void AnimSeq_Null_Conv(struct SpriteAnim* bc);
static void AnimSeq_PartyMon_Conv(struct SpriteAnim* bc);
static void AnimSeq_PartyMonSwitch_Conv(struct SpriteAnim* bc);
static void AnimSeq_PartyMonSelected_Conv(struct SpriteAnim* bc);
static void AnimSeq_GSTitleTrail_Conv(struct SpriteAnim* bc);
static void AnimSeq_GSIntroHoOhLugia_Conv(struct SpriteAnim* bc);
static void AnimSeq_NamingScreenCursor_Conv(struct SpriteAnim* bc);
static void AnimSeq_MailCursor_Conv(struct SpriteAnim* bc);
static void AnimSeq_GameFreakLogo_Conv(struct SpriteAnim* bc);
static void AnimSeq_GSGameFreakLogoStar_Conv(struct SpriteAnim* bc);
static void AnimSeq_GSGameFreakLogoSparkle_Conv(struct SpriteAnim* bc);
static void AnimSeq_SlotsGolem_Conv(struct SpriteAnim* bc);
static void AnimSeq_SlotsChansey_Conv(struct SpriteAnim* bc);
static void AnimSeq_SlotsChanseyEgg_Conv(struct SpriteAnim* bc);
static void AnimSeq_UnusedCursor_Conv(struct SpriteAnim* bc);
static void AnimSeq_PokegearArrow_Conv(struct SpriteAnim* bc);
static void AnimSeq_MemoryGameCursor_Conv(struct SpriteAnim* bc);
static void AnimSeq_TradePokeBall_Conv(struct SpriteAnim* bc);
static void AnimSeq_TradeTubeBulge_Conv(struct SpriteAnim* bc);
static void AnimSeq_TrademonInTube_Conv(struct SpriteAnim* bc);
static void AnimSeq_RevealNewMon_Conv(struct SpriteAnim* bc);
static void AnimSeq_RadioTuningKnob_Conv(struct SpriteAnim* bc);
static void AnimSeq_CutLeaves_Conv(struct SpriteAnim* bc);
static void AnimSeq_FlyFrom_Conv(struct SpriteAnim* bc);
static void AnimSeq_FlyLeaf_Conv(struct SpriteAnim* bc);
static void AnimSeq_FlyTo_Conv(struct SpriteAnim* bc);
static void AnimSeq_MobileTradeSentPulse_Conv(struct SpriteAnim* bc);
static void AnimSeq_MobileTradeOTPulse_Conv(struct SpriteAnim* bc);
static void AnimSeq_IntroSuicune_Conv(struct SpriteAnim* bc);
static void AnimSeq_IntroPichuWooper_Conv(struct SpriteAnim* bc);
static void AnimSeq_IntroUnown_Conv(struct SpriteAnim* bc);
static void AnimSeq_IntroUnownF_Conv(struct SpriteAnim* bc);
static void AnimSeq_IntroSuicuneAway_Conv(struct SpriteAnim* bc);
static void AnimSeq_EZChatCursor_Conv(struct SpriteAnim* bc);
static void AnimSeq_Celebi_Conv(struct SpriteAnim* bc);

static void AnimSeqs_IncAnonJumptableIndex_Conv(struct SpriteAnim* bc);

static uint8_t AnimSeqs_Sine_Conv(uint8_t a, uint8_t d);
static uint8_t AnimSeqs_Cosine_Conv(uint8_t a, uint8_t d);

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


// Jumptable:
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

    // return AnimSeq_Null();
}

void DoAnimFrame_Conv(struct SpriteAnim* bc){
// Jumptable:
//  entries correspond to SPRITE_ANIM_SEQ_* constants (see constants/sprite_anim_constants.asm)
    //table_width ['2', 'DoAnimFrame.Jumptable']
    //assert_table_length ['NUM_SPRITE_ANIM_SEQS']
    static void (*const DoAnimFrame_Jumptable[])(struct SpriteAnim*) = {
        [SPRITE_ANIM_SEQ_NULL] = AnimSeq_Null_Conv,
        [SPRITE_ANIM_SEQ_PARTY_MON] = AnimSeq_PartyMon_Conv,
        [SPRITE_ANIM_SEQ_PARTY_MON_SWITCH] = AnimSeq_PartyMonSwitch_Conv,
        [SPRITE_ANIM_SEQ_PARTY_MON_SELECTED] = AnimSeq_PartyMonSelected_Conv,
        [SPRITE_ANIM_SEQ_GS_TITLE_TRAIL] = AnimSeq_GSTitleTrail_Conv,
        [SPRITE_ANIM_SEQ_NAMING_SCREEN_CURSOR] = AnimSeq_NamingScreenCursor_Conv,
        [SPRITE_ANIM_SEQ_GAMEFREAK_LOGO] = AnimSeq_GameFreakLogo_Conv,
        [SPRITE_ANIM_SEQ_GS_GAMEFREAK_LOGO_STAR] = AnimSeq_GSGameFreakLogoStar_Conv,
        [SPRITE_ANIM_SEQ_GS_GAMEFREAK_LOGO_SPARKLE] = AnimSeq_GSGameFreakLogoSparkle_Conv,
        [SPRITE_ANIM_SEQ_SLOTS_GOLEM] = AnimSeq_SlotsGolem_Conv,
        [SPRITE_ANIM_SEQ_SLOTS_CHANSEY] = AnimSeq_SlotsChansey_Conv,
        [SPRITE_ANIM_SEQ_SLOTS_EGG] = AnimSeq_SlotsChanseyEgg_Conv,
        [SPRITE_ANIM_SEQ_MAIL_CURSOR] = AnimSeq_MailCursor_Conv,
        [SPRITE_ANIM_SEQ_UNUSED_CURSOR] = AnimSeq_UnusedCursor_Conv,
        [SPRITE_ANIM_SEQ_MEMORY_GAME_CURSOR] = AnimSeq_MemoryGameCursor_Conv,
        [SPRITE_ANIM_SEQ_POKEGEAR_ARROW] = AnimSeq_PokegearArrow_Conv,
        [SPRITE_ANIM_SEQ_TRADE_POKE_BALL] = AnimSeq_TradePokeBall_Conv,
        [SPRITE_ANIM_SEQ_TRADE_TUBE_BULGE] = AnimSeq_TradeTubeBulge_Conv,
        [SPRITE_ANIM_SEQ_TRADEMON_IN_TUBE] = AnimSeq_TrademonInTube_Conv,
        [SPRITE_ANIM_SEQ_REVEAL_NEW_MON] = AnimSeq_RevealNewMon_Conv,
        [SPRITE_ANIM_SEQ_RADIO_TUNING_KNOB] = AnimSeq_RadioTuningKnob_Conv,
        [SPRITE_ANIM_SEQ_CUT_LEAVES] = AnimSeq_CutLeaves_Conv,
        [SPRITE_ANIM_SEQ_FLY_FROM] = AnimSeq_FlyFrom_Conv,
        [SPRITE_ANIM_SEQ_FLY_LEAF] = AnimSeq_FlyLeaf_Conv,
        [SPRITE_ANIM_SEQ_FLY_TO] = AnimSeq_FlyTo_Conv,
        [SPRITE_ANIM_SEQ_GS_INTRO_HO_OH_LUGIA] = AnimSeq_GSIntroHoOhLugia_Conv,
        [SPRITE_ANIM_SEQ_EZCHAT_CURSOR] = AnimSeq_EZChatCursor_Conv,
        [SPRITE_ANIM_SEQ_MOBILE_TRADE_SENT_PULSE] = AnimSeq_MobileTradeSentPulse_Conv,
        [SPRITE_ANIM_SEQ_MOBILE_TRADE_OT_PULSE] = AnimSeq_MobileTradeOTPulse_Conv,
        [SPRITE_ANIM_SEQ_INTRO_SUICUNE] = AnimSeq_IntroSuicune_Conv,
        [SPRITE_ANIM_SEQ_INTRO_PICHU_WOOPER] = AnimSeq_IntroPichuWooper_Conv,
        [SPRITE_ANIM_SEQ_CELEBI] = AnimSeq_Celebi_Conv,
        [SPRITE_ANIM_SEQ_INTRO_UNOWN] = AnimSeq_IntroUnown_Conv,
        [SPRITE_ANIM_SEQ_INTRO_UNOWN_F] = AnimSeq_IntroUnownF_Conv,
        [SPRITE_ANIM_SEQ_INTRO_SUICUNE_AWAY] = AnimSeq_IntroSuicuneAway_Conv,
    };
    // LD_HL(SPRITEANIMSTRUCT_ANIM_SEQ_ID);
    // ADD_HL_BC;
    // LD_E_hl;
    // LD_D(0);
    // LD_HL(mDoAnimFrame_Jumptable);
    // ADD_HL_DE;
    // ADD_HL_DE;
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // JP_hl;
    return DoAnimFrame_Jumptable[bc->animSeqID](bc);
}

void AnimSeq_Null(void){
    RET;

}

static void AnimSeq_Null_Conv(struct SpriteAnim* bc){
    (void)bc;
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

static void AnimSeq_PartyMon_Conv(struct SpriteAnim* bc){
    // LD_A_addr(wMenuCursorY);
    uint8_t y = wram->wMenuCursorY;

    // LD_HL(SPRITEANIMSTRUCT_INDEX);
    // ADD_HL_BC;
    // CP_A_hl;
    // JR_Z (mAnimSeq_PartyMonSwitch);
    if(bc->index == y)
        return AnimSeq_PartyMonSwitch_Conv(bc);

    // LD_HL(SPRITEANIMSTRUCT_XCOORD);
    // ADD_HL_BC;
    // LD_hl(8 * 2);
    bc->xCoord = 8 * 2;

    // LD_HL(SPRITEANIMSTRUCT_YOFFSET);
    // ADD_HL_BC;
    // LD_hl(0);
    bc->yOffset = 0;
    // RET;
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

static void AnimSeq_PartyMonSwitch_Conv(struct SpriteAnim* bc){
    // LD_HL(SPRITEANIMSTRUCT_XCOORD);
    // ADD_HL_BC;
    // LD_hl(8 * 3);
    bc->xCoord = 8 * 3;

    union Register de;
    // LD_HL(SPRITEANIMSTRUCT_VAR1);
    // ADD_HL_BC;
    // LD_A_hl;
    // LD_D_A;
    de.hi = bc->var1++;
    // INC_hl;
    // AND_A(0xf);
    // RET_NZ ;
    if((de.hi & 0xf) != 0)
        return;

    // LD_HL(SPRITEANIMSTRUCT_VAR2);
    // ADD_HL_BC;
    // LD_E_hl;
    de.lo = bc->var2;

    // LD_HL(SPRITEANIMSTRUCT_YOFFSET);
    // ADD_HL_BC;
    // LD_A_D;
    // AND_A(0x10);  // bit 4
    // IF_Z goto load_zero;
    if((de.hi & 0x10) == 0) {
    // load_zero:
        // XOR_A_A;
        // LD_hl_A;
        // RET;
        bc->yOffset = 0;
        return;
    }
    // LD_A_E;
    // AND_A_A;
    // IF_Z goto load_minus_two;
    if(de.lo == 0) {
    // load_minus_two:
        // LD_A(-2);
        // LD_hl_A;
        // RET;
        bc->yOffset = (uint8_t)-2;
        return;
    }
    // CP_A(0x1);
    // IF_Z goto load_minus_one;
    if(de.lo == 1) {
    // load_minus_one:
        // LD_A(-1);
        // LD_hl_A;
        // RET;
        bc->yOffset = (uint8_t)-1;
        return;
    }
// load_zero:
    // XOR_A_A;
    // LD_hl_A;
    // RET;
    bc->yOffset = 0;
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

static void AnimSeq_PartyMonSelected_Conv(struct SpriteAnim* bc){
    // LD_A_addr(wMenuCursorY);
    uint8_t y = wram->wMenuCursorY;

    // LD_HL(SPRITEANIMSTRUCT_INDEX);
    // ADD_HL_BC;
    // CP_A_hl;
    // IF_Z goto three_offset_right;
    if(bc->index == y) {
    // three_offset_right:
        // LD_HL(SPRITEANIMSTRUCT_XCOORD);
        // ADD_HL_BC;
        // LD_hl(8 * 3);
        bc->xCoord = 8 * 3;
        // RET;
        return;
    }
    else {
        // LD_HL(SPRITEANIMSTRUCT_XCOORD);
        // ADD_HL_BC;
        // LD_hl(8 * 2);
        bc->xCoord = 8 * 2;
        // RET;
        return;
    }
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

static void AnimSeq_GSTitleTrail_Conv(struct SpriteAnim* bc){
    // CALL(aAnimSeqs_AnonJumptable);
    // JP_hl;

// anon_dw:
    //dw ['.zero'];
    //dw ['.one'];
    uint8_t d, a;

    switch(bc->jumptableIndex) {
        case 0:
        // zero:
            // CALL(aAnimSeqs_IncAnonJumptableIndex);
            AnimSeqs_IncAnonJumptableIndex_Conv(bc);

            // LD_HL(SPRITEANIMSTRUCT_INDEX);
            // ADD_HL_BC;
            // LD_A_hl;

            // LD_HL(SPRITEANIMSTRUCT_VAR2);
            // ADD_HL_BC;
            // AND_A(0x3);
            // LD_hl_A;
            bc->var2 = (bc->index & 0x3);
            // INC_hl;
            bc->var2++;
            // SWAP_A;

            // LD_HL(SPRITEANIMSTRUCT_VAR1);
            // ADD_HL_BC;
            // LD_hl_A;
            bc->var1 = (bc->index & 0x3) << 4;
            // fallthrough
        case 1:
        // one:
            // LD_HL(SPRITEANIMSTRUCT_XCOORD);
            // ADD_HL_BC;
            // LD_A_hl;
            // CP_A(0xa4);
            // IF_NC goto delete;
            if(bc->xCoord >= 0xa4) {
            // delete:
                // CALL(aDeinitializeSprite);
                DeinitializeSprite_Conv(bc);
                // RET;
                return;
            }

            // LD_HL(SPRITEANIMSTRUCT_VAR2);
            // ADD_HL_BC; // useless?
            // ADD_A(4);

            // LD_HL(SPRITEANIMSTRUCT_XCOORD);
            // ADD_HL_BC;
            // LD_hl_A;
            bc->xCoord += 4;

            // LD_HL(SPRITEANIMSTRUCT_YCOORD);
            // ADD_HL_BC;
            // INC_hl;
            bc->yCoord++;

            // LD_HL(SPRITEANIMSTRUCT_VAR2);
            // ADD_HL_BC;
            // LD_A_hl;
            // SLA_A;
            // SLA_A;

            // LD_D(2);
            d = 2;
            // LD_HL(SPRITEANIMSTRUCT_VAR1);
            // ADD_HL_BC;
            // LD_A_hl;
            // ADD_A(3);
            a = bc->var1 + 3;
            // LD_hl_A;
            bc->var1 = a;
            // CALL(aAnimSeqs_Sine);

            // LD_HL(SPRITEANIMSTRUCT_YOFFSET);
            // ADD_HL_BC;
            // LD_hl_A;
            bc->yOffset = AnimSeqs_Sine_Conv(a, d);
            // RET;
            return;
        default: 
            return;
    }
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

static void AnimSeq_GSIntroHoOhLugia_Conv(struct SpriteAnim* bc){
    // LD_HL(SPRITEANIMSTRUCT_VAR1);
    // ADD_HL_BC;
    // LD_A_hl;
    // INC_A;
    // LD_hl_A;
    bc->var1++;
    // LD_D(2);
    // CALL(aAnimSeqs_Sine);

    // LD_HL(SPRITEANIMSTRUCT_YOFFSET);
    // ADD_HL_BC;
    // LD_hl_A;
    bc->yOffset = AnimSeqs_Sine_Conv(bc->var1, 2);
    // RET;
}

void AnimSeq_NamingScreenCursor(void){
    CALLFAR(aNamingScreen_AnimateCursor);
    RET;

}

static void AnimSeq_NamingScreenCursor_Conv(struct SpriteAnim* bc){
    // REG_BC = (bc - wram->wSpriteAnim) * SPRITEANIMSTRUCT_LENGTH + wSpriteAnimationStructs;
    // CALLFAR(aNamingScreen_AnimateCursor);
    // RET;
    return NamingScreen_AnimateCursor_Conv(bc);
}

void AnimSeq_MailCursor(void){
    CALLFAR(aComposeMail_AnimateCursor);
    RET;

}

static void AnimSeq_MailCursor_Conv(struct SpriteAnim* bc){
    // REG_BC = (bc - wram->wSpriteAnim) * SPRITEANIMSTRUCT_LENGTH + wSpriteAnimationStructs;
    // CALLFAR(aComposeMail_AnimateCursor);
    return ComposeMail_AnimateCursor(bc);
}

void AnimSeq_GameFreakLogo(void){
    CALLFAR(aGameFreakLogoSpriteAnim);
    RET;

}

static void AnimSeq_GameFreakLogo_Conv(struct SpriteAnim* bc){
    // REG_BC = (bc - wram->wSpriteAnim) * SPRITEANIMSTRUCT_LENGTH + wSpriteAnimationStructs;
    // CALLFAR(aGameFreakLogoSpriteAnim);
    return GameFreakLogoSpriteAnim_Conv(bc);
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

static void AnimSeq_GSGameFreakLogoStar_Conv(struct SpriteAnim* bc){
    // LD_HL(SPRITEANIMSTRUCT_VAR1);
    // ADD_HL_BC;
    // LD_A_hl;
    // AND_A_A;
    // IF_Z goto delete;
    if(bc->var1 == 0) {
    // delete:
        // LD_A(1);
        // LD_addr_A(wIntroSceneFrameCounter);
        wram->wIntroSceneFrameCounter = 1;
        // CALL(aDeinitializeSprite);
        // RET;
        return DeinitializeSprite_Conv(bc);
    }

    // DEC_hl;
    // DEC_hl;
    // LD_D_A;
    uint8_t d = bc->var1;
    bc->var1 -= 2;
    // AND_A(0x1f);
    // IF_NZ goto stay;
    if((d & 0x1f) == 0) {
        // LD_HL(SPRITEANIMSTRUCT_VAR2);
        // ADD_HL_BC;
        // DEC_hl;
        bc->var2--;
    }
// stay:
    // LD_HL(SPRITEANIMSTRUCT_JUMPTABLE_INDEX);
    // ADD_HL_BC;
    // LD_A_hl;
    // PUSH_AF;
    // PUSH_DE;
    // CALL(aAnimSeqs_Sine);

    // LD_HL(SPRITEANIMSTRUCT_YOFFSET);
    // ADD_HL_BC;
    // LD_hl_A;
    bc->yOffset = AnimSeqs_Sine_Conv(bc->jumptableIndex, d);
    // POP_DE;
    // POP_AF;
    // CALL(aAnimSeqs_Cosine);

    // LD_HL(SPRITEANIMSTRUCT_XOFFSET);
    // ADD_HL_BC;
    // LD_hl_A;
    bc->xOffset = AnimSeqs_Cosine_Conv(bc->jumptableIndex, d);

    // LD_HL(SPRITEANIMSTRUCT_VAR2);
    // ADD_HL_BC;
    // LD_A_hl;

    // LD_HL(SPRITEANIMSTRUCT_JUMPTABLE_INDEX);
    // ADD_HL_BC;
    // ADD_A_hl;
    // LD_hl_A;
    bc->jumptableIndex += bc->var2;
    // RET;
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

static void AnimSeq_GSGameFreakLogoSparkle_Conv(struct SpriteAnim* bc){
    // LD_HL(SPRITEANIMSTRUCT_VAR1);
    // ADD_HL_BC;
    // LD_A_hli;
    // OR_A_hl;
    // IF_Z goto delete;
    if((bc->var1 | bc->var2) == 0) {
    // delete:
        // CALL(aDeinitializeSprite);
        return DeinitializeSprite_Conv(bc);
        // RET;
    }

    // LD_HL(SPRITEANIMSTRUCT_VAR4);
    // ADD_HL_BC;
    // LD_D_hl;

    // LD_HL(SPRITEANIMSTRUCT_JUMPTABLE_INDEX);
    // ADD_HL_BC;
    // LD_A_hl;
    // PUSH_AF;
    // PUSH_DE;
    // CALL(aAnimSeqs_Sine);

    // LD_HL(SPRITEANIMSTRUCT_YOFFSET);
    // ADD_HL_BC;
    // LD_hl_A;
    bc->yOffset = AnimSeqs_Sine_Conv(bc->jumptableIndex, bc->var4);
    // POP_DE;
    // POP_AF;
    // CALL(aAnimSeqs_Cosine);

    // LD_HL(SPRITEANIMSTRUCT_XOFFSET);
    // ADD_HL_BC;
    // LD_hl_A;
    bc->xOffset = AnimSeqs_Cosine_Conv(bc->jumptableIndex, bc->var4);

    // LD_HL(SPRITEANIMSTRUCT_VAR1);
    // ADD_HL_BC;
    // LD_E_hl;
    // INC_HL;
    // LD_D_hl;
    union Register de = {.lo = bc->var1, .hi = bc->var2};

    // LD_HL(SPRITEANIMSTRUCT_VAR3);
    // ADD_HL_BC;
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // ADD_HL_DE;
    // LD_E_L;
    // LD_D_H;
    de.reg += (union Register){.lo=bc->var3,.hi=bc->var4}.reg;

    // LD_HL(SPRITEANIMSTRUCT_VAR3);
    // ADD_HL_BC;
    // LD_hl_E;
    // INC_HL;
    // LD_hl_D;
    bc->var3 = de.lo;
    bc->var4 = de.hi;

    // LD_HL(SPRITEANIMSTRUCT_VAR1);
    // ADD_HL_BC;
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    union Register hl = {.lo = bc->var1, .hi = bc->var2};
    // LD_DE(-0x10);
    // ADD_HL_DE;
    // LD_E_L;
    // LD_D_H;
    de.reg = hl.reg + -0x10;

    // LD_HL(SPRITEANIMSTRUCT_VAR1);
    // ADD_HL_BC;
    // LD_hl_E;
    // INC_HL;
    // LD_hl_D;
    bc->var1 = de.lo;
    bc->var2 = de.hi;

    // LD_HL(SPRITEANIMSTRUCT_JUMPTABLE_INDEX);
    // ADD_HL_BC;
    // LD_A_hl;
    // XOR_A(0x20);
    // LD_hl_A;
    bc->jumptableIndex ^= 0x20;
    // RET;
}

void AnimSeq_SlotsGolem(void){
    CALLFAR(aSlots_AnimateGolem);
    RET;

}

static void AnimSeq_SlotsGolem_Conv(struct SpriteAnim* bc){
    // CALLFAR(aSlots_AnimateGolem);
    Slots_AnimateGolem(bc);
    // RET;
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

static void AnimSeq_SlotsChansey_Conv(struct SpriteAnim* bc){
    // CALLFAR(aSlots_AnimateChansey);
    Slots_AnimateChansey(bc);
    // LD_HL(wSlotsDelay);
    // LD_A_hl;
    // CP_A(0x2);
    // RET_NZ ;
    if(wram->wSlotsDelay != 0x2)
        return;
    // LD_hl(0x3);
    wram->wSlotsDelay = 0x3;
    // LD_A(SPRITE_ANIM_FRAMESET_SLOTS_CHANSEY_2);
    // CALL(av_ReinitSpriteAnimFrame);
    v_ReinitSpriteAnimFrame_Conv(bc, SPRITE_ANIM_FRAMESET_SLOTS_CHANSEY_2);
    // RET;
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

static void AnimSeq_SlotsChanseyEgg_Conv(struct SpriteAnim* bc){
    // LD_HL(SPRITEANIMSTRUCT_JUMPTABLE_INDEX);
    // ADD_HL_BC;
    // LD_A_hl;
    // DEC_hl;
    // LD_E_A;
    uint8_t e = bc->jumptableIndex--;
    // AND_A(0x1);
    // IF_Z goto move_vertical;
    if((e & 0x1) != 0) {
        // LD_HL(SPRITEANIMSTRUCT_XCOORD);
        // ADD_HL_BC;
        // LD_A_hl;
        // CP_A(15 * 8);
        // IF_C goto move_right;
        if(bc->xCoord >= 15 * 8) {
            // CALL(aDeinitializeSprite);
            DeinitializeSprite_Conv(bc);
            // LD_A(0x4);
            // LD_addr_A(wSlotsDelay);
            wram->wSlotsDelay = 0x4;
            // LD_DE(SFX_PLACE_PUZZLE_PIECE_DOWN);
            // CALL(aPlaySFX);
            PlaySFX_Conv(SFX_PLACE_PUZZLE_PIECE_DOWN);
            // RET;
            return;
        }

    // move_right:
        // INC_hl;
        bc->xCoord++;
    }

// move_vertical:
    // LD_A_E;
    // LD_D(32);
    // CALL(aAnimSeqs_Sine);

    // LD_HL(SPRITEANIMSTRUCT_YOFFSET);
    // ADD_HL_BC;
    // LD_hl_A;
    bc->yOffset = AnimSeqs_Sine_Conv(e, 32);
    // RET;
}

void AnimSeq_UnusedCursor(void){
    CALLFAR(aUnusedCursor_InterpretJoypad_AnimateCursor);
    RET;

}

static void AnimSeq_UnusedCursor_Conv(struct SpriteAnim* bc){
    REG_BC = (bc - wram->wSpriteAnim) * SPRITEANIMSTRUCT_LENGTH + wSpriteAnimationStructs;
    CALLFAR(aUnusedCursor_InterpretJoypad_AnimateCursor);
}

void AnimSeq_PokegearArrow(void){
    CALLFAR(aAnimatePokegearModeIndicatorArrow);
    RET;

}

static void AnimSeq_PokegearArrow_Conv(struct SpriteAnim* bc){
    REG_BC = (bc - wram->wSpriteAnim) * SPRITEANIMSTRUCT_LENGTH + wSpriteAnimationStructs;
    CALLFAR(aAnimatePokegearModeIndicatorArrow);
}

void AnimSeq_MemoryGameCursor(void){
    CALLFAR(aMemoryGame_InterpretJoypad_AnimateCursor);
    RET;

}

static void AnimSeq_MemoryGameCursor_Conv(struct SpriteAnim* bc){
    REG_BC = (bc - wram->wSpriteAnim) * SPRITEANIMSTRUCT_LENGTH + wSpriteAnimationStructs;
    CALLFAR(aMemoryGame_InterpretJoypad_AnimateCursor);
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

static void AnimSeq_TradePokeBall_Conv(struct SpriteAnim* bc){
    // CALL(aAnimSeqs_AnonJumptable);
    // JP_hl;

// anon_dw:
    //dw ['.zero'];
    //dw ['.one'];
    //dw ['.two'];
    //dw ['.three'];
    //dw ['.four'];
    //dw ['.delete'];

    switch(bc->jumptableIndex) {
    case 0:
    // zero:
        // LD_A(SPRITE_ANIM_FRAMESET_TRADE_POKE_BALL_WOBBLE);
        // CALL(av_ReinitSpriteAnimFrame);
        v_ReinitSpriteAnimFrame_Conv(bc, SPRITE_ANIM_FRAMESET_TRADE_POKE_BALL_WOBBLE);

        // LD_HL(SPRITEANIMSTRUCT_JUMPTABLE_INDEX);
        // ADD_HL_BC;
        // LD_hl(2);  // .two
        bc->jumptableIndex = 2;

        // LD_HL(SPRITEANIMSTRUCT_VAR1);
        // ADD_HL_BC;
        // LD_hl(0x20);
        bc->var1 = 0x20;
        // RET;
        return;
    case 2:
    // two:
        // LD_HL(SPRITEANIMSTRUCT_VAR1);
        // ADD_HL_BC;
        // LD_A_hl;
        // AND_A_A;
        // IF_Z goto next;
        if(bc->var1 != 0) {
            // DEC_hl;
            // RET;
            bc->var1--;
            return;
        }

    // next:
        // CALL(aAnimSeqs_IncAnonJumptableIndex);
        AnimSeqs_IncAnonJumptableIndex_Conv(bc);

        // LD_HL(SPRITEANIMSTRUCT_VAR1);
        // ADD_HL_BC;
        // LD_hl(0x40);
        bc->var1 = 0x40;

        // fallthrough
    case 3:
    // three:
        // LD_HL(SPRITEANIMSTRUCT_VAR1);
        // ADD_HL_BC;
        // LD_A_hl;
        // CP_A(48);
        // IF_C goto done;
        if(bc->var1 >= 48) {
            // DEC_hl;
            // LD_D(40);
            // CALL(aAnimSeqs_Sine);

            // LD_HL(SPRITEANIMSTRUCT_YOFFSET);
            // ADD_HL_BC;
            // LD_hl_A;
            bc->yOffset = AnimSeqs_Sine_Conv(bc->var1--, 40);
            // RET;
            return;
        }

    // done:
        // LD_DE(SFX_GOT_SAFARI_BALLS);
        // CALL(aPlaySFX);
        PlaySFX_Conv(SFX_GOT_SAFARI_BALLS);
        // fallthrough

    case 5:
    // delete:
        // CALL(aDeinitializeSprite);
        DeinitializeSprite_Conv(bc);
        // RET;
        return;

    case 1:
    // one:
        // LD_HL(SPRITEANIMSTRUCT_JUMPTABLE_INDEX);
        // ADD_HL_BC;
        // LD_hl(0x4);
        bc->jumptableIndex = 0x4;

        // LD_HL(SPRITEANIMSTRUCT_VAR1);
        // ADD_HL_BC;
        // LD_hl(0x30);
        bc->var1 = 0x30;

        // LD_HL(SPRITEANIMSTRUCT_VAR2);
        // ADD_HL_BC;
        // LD_hl(0x24);
        bc->var2 = 0x24;
        // RET;
        return;

    case 4:
    // four:
        // LD_HL(SPRITEANIMSTRUCT_VAR2);
        // ADD_HL_BC;
        // LD_A_hl;
        // AND_A_A;
        // IF_Z goto done2;
        if(bc->var2 == 0) {
        // done2:
            // XOR_A_A;

            // LD_HL(SPRITEANIMSTRUCT_YOFFSET);
            // ADD_HL_BC;
            // LD_hl_A;
            bc->yOffset = 0;
            // CALL(aAnimSeqs_IncAnonJumptableIndex);
            AnimSeqs_IncAnonJumptableIndex_Conv(bc);
            // RET;
            return;
        }

        // LD_D_A;
        // LD_HL(SPRITEANIMSTRUCT_VAR1);
        // ADD_HL_BC;
        // LD_A_hl;
        // CALL(aSprites_Sine);

        // LD_HL(SPRITEANIMSTRUCT_YOFFSET);
        // ADD_HL_BC;
        // LD_hl_A;
        bc->yOffset = AnimSeqs_Sine_Conv(bc->var1, bc->var2);

        // LD_HL(SPRITEANIMSTRUCT_VAR1);
        // ADD_HL_BC;
        // INC_hl;
        // LD_A_hl;
        // AND_A(0x3f);
        // RET_NZ ;
        if((++bc->var1 & 0x3f) != 0)
            return;

        // LD_HL(SPRITEANIMSTRUCT_VAR1);
        // ADD_HL_BC;
        // LD_hl(0x20);
        bc->var1 = 0x20;

        // LD_HL(SPRITEANIMSTRUCT_VAR2);
        // ADD_HL_BC;
        // LD_A_hl;
        // SUB_A(0xc);
        // LD_hl_A;
        bc->var2 -= 0xc;
        // LD_DE(SFX_SWITCH_POKEMON);
        // CALL(aPlaySFX);
        PlaySFX_Conv(SFX_SWITCH_POKEMON);
        // RET;
        return;
    }

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

static void AnimSeq_TradeTubeBulge_Conv(struct SpriteAnim* bc){
    // LD_HL(SPRITEANIMSTRUCT_XCOORD);
    // ADD_HL_BC;
    // LD_A_hl;
    uint8_t a = bc->xCoord;
    // INC_hl;
    // INC_hl;
    bc->xCoord += 2;
    // CP_A(0xb0);
    // IF_NC goto delete;
    if(a >= 0xb0) {
    // delete:
        // CALL(aDeinitializeSprite);
        DeinitializeSprite_Conv(bc);
        // RET;
        return;
    }

    // AND_A(0x3);
    // RET_NZ ;
    if((a & 0x3) == 0) {
        // LD_DE(SFX_POKEBALLS_PLACED_ON_TABLE);
        // CALL(aPlaySFX);
        PlaySFX_Conv(SFX_POKEBALLS_PLACED_ON_TABLE);
    }
    // RET;
}

void AnimSeq_TrademonInTube(void){
    CALLFAR(aTradeAnim_AnimateTrademonInTube);
    RET;

}

static void AnimSeq_TrademonInTube_Conv(struct SpriteAnim* bc){
    TradeAnim_AnimateTrademonInTube(bc);
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

static void AnimSeq_RevealNewMon_Conv(struct SpriteAnim* bc){
    // LD_HL(SPRITEANIMSTRUCT_VAR1);
    // ADD_HL_BC;
    // LD_A_hl;
    // CP_A(0x80);
    // IF_NC goto finish_EggShell;
    if(bc->var1 >= 0x80) {
    // finish_EggShell:
        // CALL(aDeinitializeSprite);
        // RET;
        return DeinitializeSprite_Conv(bc);
    }
    // LD_D_A;
    // ADD_A(8);
    // LD_hl_A;
    uint8_t d = bc->var1;
    bc->var1 += 8;

    // LD_HL(SPRITEANIMSTRUCT_JUMPTABLE_INDEX);
    // ADD_HL_BC;
    // LD_A_hl;
    // XOR_A(0x20);
    // LD_hl_A;
    uint8_t a = bc->jumptableIndex ^ 0x20;
    bc->jumptableIndex = a;

    // PUSH_AF;
    // PUSH_DE;
    // CALL(aAnimSeqs_Sine);

    // LD_HL(SPRITEANIMSTRUCT_YOFFSET);
    // ADD_HL_BC;
    // LD_hl_A;
    bc->yOffset = AnimSeqs_Sine_Conv(a, d);

    // POP_DE;
    // POP_AF;
    // CALL(aAnimSeqs_Cosine);

    // LD_HL(SPRITEANIMSTRUCT_XOFFSET);
    // ADD_HL_BC;
    // LD_hl_A;
    bc->xOffset = AnimSeqs_Cosine_Conv(a, d);
    // RET;
}

void AnimSeq_RadioTuningKnob(void){
    CALLFAR(aAnimateTuningKnob);
    RET;

}

static void AnimSeq_RadioTuningKnob_Conv(struct SpriteAnim* bc){
    // REG_BC = (bc - wram->wSpriteAnim) * SPRITEANIMSTRUCT_LENGTH + wSpriteAnimationStructs;
    // CALLFAR(aAnimateTuningKnob);
    AnimateTuningKnob_Conv(bc);
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

static void AnimSeq_CutLeaves_Conv(struct SpriteAnim* bc){
    union Register de;
    // LD_HL(SPRITEANIMSTRUCT_VAR2);
    // ADD_HL_BC;
    // LD_E_hl;
    de.lo = bc->var2;
    // INC_HL;
    // LD_D_hl;
    de.hi = bc->var3;
    // LD_HL(0x80);
    // ADD_HL_DE;
    // LD_E_L;
    // LD_D_H;
    de.reg += 0x80;

    // LD_HL(SPRITEANIMSTRUCT_VAR2);
    // ADD_HL_BC;
    // LD_hl_E;
    bc->var2 = de.lo;
    // INC_HL;
    // LD_hl_D;
    bc->var3 = de.hi;

    // LD_HL(SPRITEANIMSTRUCT_VAR1);
    // ADD_HL_BC;
    // LD_A_hl;
    uint8_t a = bc->var1;
    // INC_hl;
    // INC_hl;
    // INC_hl;
    bc->var1 += 3;
    // PUSH_AF;
    // PUSH_DE;
    // CALL(aAnimSeqs_Sine);

    // LD_HL(SPRITEANIMSTRUCT_YOFFSET);
    // ADD_HL_BC;
    // LD_hl_A;
    bc->yOffset = AnimSeqs_Sine_Conv(a, bc->var3);
    // POP_DE;
    // POP_AF;
    // CALL(aAnimSeqs_Cosine);

    // LD_HL(SPRITEANIMSTRUCT_XOFFSET);
    // ADD_HL_BC;
    // LD_hl_A;
    bc->xOffset = AnimSeqs_Cosine_Conv(a, bc->var3);
    // RET;
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

static void AnimSeq_FlyFrom_Conv(struct SpriteAnim* bc){
    // LD_HL(SPRITEANIMSTRUCT_YCOORD);
    // ADD_HL_BC;
    // LD_A_hl;
    // AND_A_A;
    // RET_Z ;
    if(bc->yCoord == 0)
        return;

    // LD_HL(SPRITEANIMSTRUCT_VAR2);
    // ADD_HL_BC;
    // LD_A_hl;
    // INC_hl;
    // CP_A(0x40);
    // RET_C ;
    if(bc->var2++ < 0x40)
        return;

    // LD_HL(SPRITEANIMSTRUCT_YCOORD);
    // ADD_HL_BC;
    // DEC_hl;
    // DEC_hl;
    bc->yCoord -= 2;

    // LD_HL(SPRITEANIMSTRUCT_VAR4);
    // ADD_HL_BC;
    // LD_A_hl;
    // LD_D_A;
    uint8_t d = bc->var4;
    // CP_A(0x40);
    // IF_NC goto skip;
    if(bc->var4 < 0x40) {
        // ADD_A(8);
        // LD_hl_A;
        bc->var4 += 8;
    }

// skip:
    // LD_HL(SPRITEANIMSTRUCT_VAR3);
    // ADD_HL_BC;
    // LD_A_hl;
    // INC_hl;
    // CALL(aAnimSeqs_Cosine);

    // LD_HL(SPRITEANIMSTRUCT_XOFFSET);
    // ADD_HL_BC;
    // LD_hl_A;
    bc->xOffset = AnimSeqs_Cosine_Conv(bc->var3++, d);
    // RET;
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

static void AnimSeq_FlyLeaf_Conv(struct SpriteAnim* bc){
    // LD_HL(SPRITEANIMSTRUCT_XCOORD);
    // ADD_HL_BC;
    // LD_A_hl;
    // CP_A(-9 * 8);
    // IF_NC goto delete_leaf;
    if(bc->xCoord >= (uint8_t)(-9 * 8)) {
    // delete_leaf:
        // CALL(aDeinitializeSprite);
        // RET;
        return DeinitializeSprite_Conv(bc);
    }
    // INC_hl;
    // INC_hl;
    bc->xCoord += 2;

    // LD_HL(SPRITEANIMSTRUCT_YCOORD);
    // ADD_HL_BC;
    // DEC_hl;
    bc->yCoord--;

    // LD_D(0x40);
    // LD_HL(SPRITEANIMSTRUCT_VAR1);
    // ADD_HL_BC;
    // LD_A_hl;
    // INC_hl;
    // CALL(aAnimSeqs_Cosine);

    // LD_HL(SPRITEANIMSTRUCT_XOFFSET);
    // ADD_HL_BC;
    // LD_hl_A;
    bc->xOffset = AnimSeqs_Cosine_Conv(bc->var1++, 0x40);
    // RET;
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

static void AnimSeq_FlyTo_Conv(struct SpriteAnim* bc){
    // LD_HL(SPRITEANIMSTRUCT_YCOORD);
    // ADD_HL_BC;
    // LD_A_hl;
    // CP_A(10 * 8 + 4);
    // RET_Z ;
    if(bc->yCoord == 10 * 8 + 4)
        return;

    // LD_HL(SPRITEANIMSTRUCT_YCOORD);
    // ADD_HL_BC;
    // INC_hl;
    // INC_hl;
    bc->yCoord += 2;

    // LD_HL(SPRITEANIMSTRUCT_VAR4);
    // ADD_HL_BC;
    // LD_A_hl;
    // LD_D_A;
    uint8_t d = bc->var4;
    // AND_A_A;
    // IF_Z goto stay;
    if(bc->var4 != 0) {
        // SUB_A(0x2);
        // LD_hl_A;
        bc->var4 -= 0x2;
    }

// stay:
    // LD_HL(SPRITEANIMSTRUCT_VAR3);
    // ADD_HL_BC;
    // LD_A_hl;
    // INC_hl;
    // CALL(aAnimSeqs_Cosine);

    // LD_HL(SPRITEANIMSTRUCT_XOFFSET);
    // ADD_HL_BC;
    // LD_hl_A;
    bc->xOffset = AnimSeqs_Cosine_Conv(bc->var3++, d);
    // RET;
}

void AnimSeq_MobileTradeSentPulse(void){
    FARCALL(aMobileTradeAnim_AnimateSentPulse);
    RET;

}

static void AnimSeq_MobileTradeSentPulse_Conv(struct SpriteAnim* bc){
    REG_BC = (bc - wram->wSpriteAnim) * SPRITEANIMSTRUCT_LENGTH + wSpriteAnimationStructs;
    FARCALL(aMobileTradeAnim_AnimateSentPulse);
}

void AnimSeq_MobileTradeOTPulse(void){
    FARCALL(aMobileTradeAnim_AnimateOTPulse);
    RET;

}

static void AnimSeq_MobileTradeOTPulse_Conv(struct SpriteAnim* bc){
    REG_BC = (bc - wram->wSpriteAnim) * SPRITEANIMSTRUCT_LENGTH + wSpriteAnimationStructs;
    FARCALL(aMobileTradeAnim_AnimateOTPulse);
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

static void AnimSeq_IntroSuicune_Conv(struct SpriteAnim* bc){
    // LD_A_addr(wIntroSceneTimer);
    // AND_A_A;
    // IF_NZ goto continue_;
    // RET;
    if(wram->wIntroSceneTimer == 0)
        return;

// continue_:
    // LD_HL(SPRITEANIMSTRUCT_YOFFSET);
    // ADD_HL_BC;
    // LD_hl(0x0);
    bc->yOffset = 0x0;

    // LD_HL(SPRITEANIMSTRUCT_VAR2);
    // ADD_HL_BC;
    // LD_A_hl;
    // ADD_A(2);
    // LD_hl_A;
    bc->var2 += 2;
    // XOR_A(0xff);
    // INC_A;
    // LD_D(32);
    // CALL(aAnimSeqs_Sine);

    // LD_HL(SPRITEANIMSTRUCT_YOFFSET);
    // ADD_HL_BC;
    // LD_hl_A;
    bc->yOffset = AnimSeqs_Sine_Conv((bc->var2 ^ 0xff) + 1, 32);
    // LD_A(SPRITE_ANIM_FRAMESET_INTRO_SUICUNE_2);
    // CALL(av_ReinitSpriteAnimFrame);
    v_ReinitSpriteAnimFrame_Conv(bc, SPRITE_ANIM_FRAMESET_INTRO_SUICUNE_2);
    // RET;
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

static void AnimSeq_IntroPichuWooper_Conv(struct SpriteAnim* bc){
    // LD_HL(SPRITEANIMSTRUCT_VAR1);
    // ADD_HL_BC;
    // LD_A_hl;
    uint8_t a = bc->var1;
    // CP_A(20);
    // IF_NC goto done;
    if(a >= 20) 
        return;
    // ADD_A(2);
    // LD_hl_A;
    bc->var1 = a + 2;
    // XOR_A(0xff);
    // INC_A;
    // LD_D(32);
    // CALL(aAnimSeqs_Sine);

    // LD_HL(SPRITEANIMSTRUCT_YOFFSET);
    // ADD_HL_BC;
    // LD_hl_A;
    bc->yOffset = AnimSeqs_Sine_Conv(((a + 2) ^ 0xff) + 1, 32);

// done:
    // RET;
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

static void AnimSeq_IntroUnown_Conv(struct SpriteAnim* bc){
    // LD_HL(SPRITEANIMSTRUCT_JUMPTABLE_INDEX);
    // ADD_HL_BC;
    // LD_D_hl;
    uint8_t d = bc->jumptableIndex;
    // INC_hl;
    // INC_hl;
    // INC_hl;
    bc->jumptableIndex += 3;
    // LD_HL(SPRITEANIMSTRUCT_VAR1);
    // ADD_HL_BC;
    // LD_A_hl;
    uint8_t a = bc->var1;
    // PUSH_AF;
    // PUSH_DE;
    // CALL(aAnimSeqs_Sine);

    // LD_HL(SPRITEANIMSTRUCT_YOFFSET);
    // ADD_HL_BC;
    // LD_hl_A;
    bc->yOffset = AnimSeqs_Sine_Conv(a, d);
    // POP_DE;
    // POP_AF;
    // CALL(aAnimSeqs_Cosine);

    // LD_HL(SPRITEANIMSTRUCT_XOFFSET);
    // ADD_HL_BC;
    // LD_hl_A;
    bc->xOffset = AnimSeqs_Cosine_Conv(a, d);
    // RET;
}

void AnimSeq_IntroUnownF(void){
    LD_A_addr(wSlotsDelay);
    CP_A(0x40);
    RET_NZ ;
    LD_A(SPRITE_ANIM_FRAMESET_INTRO_UNOWN_F_2);
    CALL(av_ReinitSpriteAnimFrame);
    RET;

}

static void AnimSeq_IntroUnownF_Conv(struct SpriteAnim* bc){
    // LD_A_addr(wSlotsDelay);
    // CP_A(0x40);
    // RET_NZ ;
    if(wram->wSlotsDelay != 0x40)
        return;
    // LD_A(SPRITE_ANIM_FRAMESET_INTRO_UNOWN_F_2);
    // CALL(av_ReinitSpriteAnimFrame);
    // RET;
    v_ReinitSpriteAnimFrame_Conv(bc, SPRITE_ANIM_FRAMESET_INTRO_UNOWN_F_2);
}

void AnimSeq_IntroSuicuneAway(void){
    LD_HL(SPRITEANIMSTRUCT_YCOORD);
    ADD_HL_BC;
    LD_A_hl;
    ADD_A(16);
    LD_hl_A;
    RET;

}

static void AnimSeq_IntroSuicuneAway_Conv(struct SpriteAnim* bc){
    // LD_HL(SPRITEANIMSTRUCT_YCOORD);
    // ADD_HL_BC;
    // LD_A_hl;
    // ADD_A(16);
    // LD_hl_A;
    bc->yCoord += 16;
    // RET;
}

void AnimSeq_EZChatCursor(void){
    FARCALL(aAnimateEZChatCursor);
    RET;

}

static void AnimSeq_EZChatCursor_Conv(struct SpriteAnim* bc){
    REG_BC = (bc - wram->wSpriteAnim) * SPRITEANIMSTRUCT_LENGTH + wSpriteAnimationStructs;
    FARCALL(aAnimateEZChatCursor);
}

void AnimSeq_Celebi(void){
    FARCALL(aUpdateCelebiPosition);
    RET;

}

static void AnimSeq_Celebi_Conv(struct SpriteAnim* bc){
    // FARCALL(aUpdateCelebiPosition);
    // RET;
    return UpdateCelebiPosition(bc);
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

static void AnimSeqs_IncAnonJumptableIndex_Conv(struct SpriteAnim* bc){
    // LD_HL(SPRITEANIMSTRUCT_JUMPTABLE_INDEX);
    // ADD_HL_BC;
    // INC_hl;
    // RET;
    bc->jumptableIndex++;
}

void AnimSeqs_Sine(void){
    CALL(aSprites_Sine);
    RET;

}

static uint8_t AnimSeqs_Sine_Conv(uint8_t a, uint8_t d){
    // CALL(aSprites_Sine);
    // RET;
    return Sprites_Sine_Conv(a, d);
}

void AnimSeqs_Cosine(void){
    CALL(aSprites_Cosine);
    RET;

}

static uint8_t AnimSeqs_Cosine_Conv(uint8_t a, uint8_t d){
    // CALL(aSprites_Cosine);
    // RET;
    return Sprites_Cosine_Conv(a, d);
}
