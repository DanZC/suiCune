#include "../../constants.h"
#include "sprite_anims.h"
#include "sprites.h"
#include "../../home/audio.h"
#include "../../home/sine.h"
#include "../movie/splash.h"
#include "../movie/trade_animation.h"
#include "../pokegear/pokegear.h"
#include "../menus/naming_screen.h"
#include "../games/slot_machine.h"
#include "../events/celebi.h"
#include "../../mobile/fixed_words.h"
#include "../../mobile/mobile_42.h"

static void AnimSeq_Null(struct SpriteAnim* bc);
static void AnimSeq_PartyMon(struct SpriteAnim* bc);
static void AnimSeq_PartyMonSwitch(struct SpriteAnim* bc);
static void AnimSeq_PartyMonSelected(struct SpriteAnim* bc);
static void AnimSeq_GSTitleTrail(struct SpriteAnim* bc);
static void AnimSeq_GSIntroHoOhLugia(struct SpriteAnim* bc);
static void AnimSeq_NamingScreenCursor(struct SpriteAnim* bc);
static void AnimSeq_MailCursor(struct SpriteAnim* bc);
static void AnimSeq_GameFreakLogo(struct SpriteAnim* bc);
static void AnimSeq_GSGameFreakLogoStar(struct SpriteAnim* bc);
static void AnimSeq_GSGameFreakLogoSparkle(struct SpriteAnim* bc);
static void AnimSeq_SlotsGolem(struct SpriteAnim* bc);
static void AnimSeq_SlotsChansey(struct SpriteAnim* bc);
static void AnimSeq_SlotsChanseyEgg(struct SpriteAnim* bc);
static void AnimSeq_UnusedCursor(struct SpriteAnim* bc);
static void AnimSeq_PokegearArrow(struct SpriteAnim* bc);
static void AnimSeq_MemoryGameCursor(struct SpriteAnim* bc);
static void AnimSeq_TradePokeBall(struct SpriteAnim* bc);
static void AnimSeq_TradeTubeBulge(struct SpriteAnim* bc);
static void AnimSeq_TrademonInTube(struct SpriteAnim* bc);
static void AnimSeq_RevealNewMon(struct SpriteAnim* bc);
static void AnimSeq_RadioTuningKnob(struct SpriteAnim* bc);
static void AnimSeq_CutLeaves(struct SpriteAnim* bc);
static void AnimSeq_FlyFrom(struct SpriteAnim* bc);
static void AnimSeq_FlyLeaf(struct SpriteAnim* bc);
static void AnimSeq_FlyTo(struct SpriteAnim* bc);
static void AnimSeq_MobileTradeSentPulse(struct SpriteAnim* bc);
static void AnimSeq_MobileTradeOTPulse(struct SpriteAnim* bc);
static void AnimSeq_IntroSuicune(struct SpriteAnim* bc);
static void AnimSeq_IntroPichuWooper(struct SpriteAnim* bc);
static void AnimSeq_IntroUnown(struct SpriteAnim* bc);
static void AnimSeq_IntroUnownF(struct SpriteAnim* bc);
static void AnimSeq_IntroSuicuneAway(struct SpriteAnim* bc);
static void AnimSeq_EZChatCursor(struct SpriteAnim* bc);
static void AnimSeq_Celebi(struct SpriteAnim* bc);

static void AnimSeqs_IncAnonJumptableIndex_Conv(struct SpriteAnim* bc);

static uint8_t AnimSeqs_Sine(uint8_t a, uint8_t d);
static uint8_t AnimSeqs_Cosine(uint8_t a, uint8_t d);

void DoAnimFrame(struct SpriteAnim* bc){
// Jumptable:
//  entries correspond to SPRITE_ANIM_SEQ_* constants (see constants/sprite_anim_constants.asm)
    //table_width ['2', 'DoAnimFrame.Jumptable']
    //assert_table_length ['NUM_SPRITE_ANIM_SEQS']
    static void (*const DoAnimFrame_Jumptable[])(struct SpriteAnim*) = {
        [SPRITE_ANIM_SEQ_NULL] = AnimSeq_Null,
        [SPRITE_ANIM_SEQ_PARTY_MON] = AnimSeq_PartyMon,
        [SPRITE_ANIM_SEQ_PARTY_MON_SWITCH] = AnimSeq_PartyMonSwitch,
        [SPRITE_ANIM_SEQ_PARTY_MON_SELECTED] = AnimSeq_PartyMonSelected,
        [SPRITE_ANIM_SEQ_GS_TITLE_TRAIL] = AnimSeq_GSTitleTrail,
        [SPRITE_ANIM_SEQ_NAMING_SCREEN_CURSOR] = AnimSeq_NamingScreenCursor,
        [SPRITE_ANIM_SEQ_GAMEFREAK_LOGO] = AnimSeq_GameFreakLogo,
        [SPRITE_ANIM_SEQ_GS_GAMEFREAK_LOGO_STAR] = AnimSeq_GSGameFreakLogoStar,
        [SPRITE_ANIM_SEQ_GS_GAMEFREAK_LOGO_SPARKLE] = AnimSeq_GSGameFreakLogoSparkle,
        [SPRITE_ANIM_SEQ_SLOTS_GOLEM] = AnimSeq_SlotsGolem,
        [SPRITE_ANIM_SEQ_SLOTS_CHANSEY] = AnimSeq_SlotsChansey,
        [SPRITE_ANIM_SEQ_SLOTS_EGG] = AnimSeq_SlotsChanseyEgg,
        [SPRITE_ANIM_SEQ_MAIL_CURSOR] = AnimSeq_MailCursor,
        [SPRITE_ANIM_SEQ_UNUSED_CURSOR] = AnimSeq_UnusedCursor,
        [SPRITE_ANIM_SEQ_MEMORY_GAME_CURSOR] = AnimSeq_MemoryGameCursor,
        [SPRITE_ANIM_SEQ_POKEGEAR_ARROW] = AnimSeq_PokegearArrow,
        [SPRITE_ANIM_SEQ_TRADE_POKE_BALL] = AnimSeq_TradePokeBall,
        [SPRITE_ANIM_SEQ_TRADE_TUBE_BULGE] = AnimSeq_TradeTubeBulge,
        [SPRITE_ANIM_SEQ_TRADEMON_IN_TUBE] = AnimSeq_TrademonInTube,
        [SPRITE_ANIM_SEQ_REVEAL_NEW_MON] = AnimSeq_RevealNewMon,
        [SPRITE_ANIM_SEQ_RADIO_TUNING_KNOB] = AnimSeq_RadioTuningKnob,
        [SPRITE_ANIM_SEQ_CUT_LEAVES] = AnimSeq_CutLeaves,
        [SPRITE_ANIM_SEQ_FLY_FROM] = AnimSeq_FlyFrom,
        [SPRITE_ANIM_SEQ_FLY_LEAF] = AnimSeq_FlyLeaf,
        [SPRITE_ANIM_SEQ_FLY_TO] = AnimSeq_FlyTo,
        [SPRITE_ANIM_SEQ_GS_INTRO_HO_OH_LUGIA] = AnimSeq_GSIntroHoOhLugia,
        [SPRITE_ANIM_SEQ_EZCHAT_CURSOR] = AnimSeq_EZChatCursor,
        [SPRITE_ANIM_SEQ_MOBILE_TRADE_SENT_PULSE] = AnimSeq_MobileTradeSentPulse,
        [SPRITE_ANIM_SEQ_MOBILE_TRADE_OT_PULSE] = AnimSeq_MobileTradeOTPulse,
        [SPRITE_ANIM_SEQ_INTRO_SUICUNE] = AnimSeq_IntroSuicune,
        [SPRITE_ANIM_SEQ_INTRO_PICHU_WOOPER] = AnimSeq_IntroPichuWooper,
        [SPRITE_ANIM_SEQ_CELEBI] = AnimSeq_Celebi,
        [SPRITE_ANIM_SEQ_INTRO_UNOWN] = AnimSeq_IntroUnown,
        [SPRITE_ANIM_SEQ_INTRO_UNOWN_F] = AnimSeq_IntroUnownF,
        [SPRITE_ANIM_SEQ_INTRO_SUICUNE_AWAY] = AnimSeq_IntroSuicuneAway,
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

static void AnimSeq_Null(struct SpriteAnim* bc){
    (void)bc;
}

static void AnimSeq_PartyMon(struct SpriteAnim* bc){
    // LD_A_addr(wMenuCursorY);
    uint8_t y = wram->wMenuCursorY;

    // LD_HL(SPRITEANIMSTRUCT_INDEX);
    // ADD_HL_BC;
    // CP_A_hl;
    // JR_Z (mAnimSeq_PartyMonSwitch);
    if(bc->index == y)
        return AnimSeq_PartyMonSwitch(bc);

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

static void AnimSeq_PartyMonSwitch(struct SpriteAnim* bc){
    // LD_HL(SPRITEANIMSTRUCT_XCOORD);
    // ADD_HL_BC;
    // LD_hl(8 * 3);
    bc->xCoord = 8 * 3;

    uint8_t d, e;
    // LD_HL(SPRITEANIMSTRUCT_VAR1);
    // ADD_HL_BC;
    // LD_A_hl;
    // LD_D_A;
    d = bc->var1++;
    // INC_hl;
    // AND_A(0xf);
    // RET_NZ ;
    if((d & 0xf) != 0)
        return;

    // LD_HL(SPRITEANIMSTRUCT_VAR2);
    // ADD_HL_BC;
    // LD_E_hl;
    e = bc->var2;

    // LD_HL(SPRITEANIMSTRUCT_YOFFSET);
    // ADD_HL_BC;
    // LD_A_D;
    // AND_A(0x10);  // bit 4
    // IF_Z goto load_zero;
    if((d & 0x10) == 0) {
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
    if(e == 0) {
    // load_minus_two:
        // LD_A(-2);
        // LD_hl_A;
        // RET;
        bc->yOffset = (uint8_t)-2;
        return;
    }
    // CP_A(0x1);
    // IF_Z goto load_minus_one;
    if(e == 1) {
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

static void AnimSeq_PartyMonSelected(struct SpriteAnim* bc){
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

static void AnimSeq_GSTitleTrail(struct SpriteAnim* bc){
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
                DeinitializeSprite(bc);
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
            bc->yOffset = AnimSeqs_Sine(a, d);
            // RET;
            return;
        default: 
            return;
    }
}

static void AnimSeq_GSIntroHoOhLugia(struct SpriteAnim* bc){
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
    bc->yOffset = AnimSeqs_Sine(bc->var1, 2);
    // RET;
}

static void AnimSeq_NamingScreenCursor(struct SpriteAnim* bc){
    // REG_BC = (bc - wram->wSpriteAnim) * SPRITEANIMSTRUCT_LENGTH + wSpriteAnimationStructs;
    // CALLFAR(aNamingScreen_AnimateCursor);
    // RET;
    return NamingScreen_AnimateCursor_Conv(bc);
}

static void AnimSeq_MailCursor(struct SpriteAnim* bc){
    // REG_BC = (bc - wram->wSpriteAnim) * SPRITEANIMSTRUCT_LENGTH + wSpriteAnimationStructs;
    // CALLFAR(aComposeMail_AnimateCursor);
    return ComposeMail_AnimateCursor(bc);
}

static void AnimSeq_GameFreakLogo(struct SpriteAnim* bc){
    // REG_BC = (bc - wram->wSpriteAnim) * SPRITEANIMSTRUCT_LENGTH + wSpriteAnimationStructs;
    // CALLFAR(aGameFreakLogoSpriteAnim);
    return GameFreakLogoSpriteAnim_Conv(bc);
}

static void AnimSeq_GSGameFreakLogoStar(struct SpriteAnim* bc){
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
        return DeinitializeSprite(bc);
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
    bc->yOffset = AnimSeqs_Sine(bc->jumptableIndex, d);
    // POP_DE;
    // POP_AF;
    // CALL(aAnimSeqs_Cosine);

    // LD_HL(SPRITEANIMSTRUCT_XOFFSET);
    // ADD_HL_BC;
    // LD_hl_A;
    bc->xOffset = AnimSeqs_Cosine(bc->jumptableIndex, d);

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

static void AnimSeq_GSGameFreakLogoSparkle(struct SpriteAnim* bc){
    // LD_HL(SPRITEANIMSTRUCT_VAR1);
    // ADD_HL_BC;
    // LD_A_hli;
    // OR_A_hl;
    // IF_Z goto delete;
    if((bc->var1 | bc->var2) == 0) {
    // delete:
        // CALL(aDeinitializeSprite);
        return DeinitializeSprite(bc);
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
    bc->yOffset = AnimSeqs_Sine(bc->jumptableIndex, bc->var4);
    // POP_DE;
    // POP_AF;
    // CALL(aAnimSeqs_Cosine);

    // LD_HL(SPRITEANIMSTRUCT_XOFFSET);
    // ADD_HL_BC;
    // LD_hl_A;
    bc->xOffset = AnimSeqs_Cosine(bc->jumptableIndex, bc->var4);

    // LD_HL(SPRITEANIMSTRUCT_VAR1);
    // ADD_HL_BC;
    // LD_E_hl;
    // INC_HL;
    // LD_D_hl;
    uint16_t de = bc->var1 | (bc->var2 << 8);

    // LD_HL(SPRITEANIMSTRUCT_VAR3);
    // ADD_HL_BC;
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // ADD_HL_DE;
    // LD_E_L;
    // LD_D_H;
    de += (uint16_t)(bc->var3 | (bc->var4 << 8));

    // LD_HL(SPRITEANIMSTRUCT_VAR3);
    // ADD_HL_BC;
    // LD_hl_E;
    // INC_HL;
    // LD_hl_D;
    bc->var3 = LOW(de);
    bc->var4 = HIGH(de);

    // LD_HL(SPRITEANIMSTRUCT_VAR1);
    // ADD_HL_BC;
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    uint16_t hl = bc->var1 | (bc->var2 << 8);
    // LD_DE(-0x10);
    // ADD_HL_DE;
    // LD_E_L;
    // LD_D_H;
    de = hl + -0x10;

    // LD_HL(SPRITEANIMSTRUCT_VAR1);
    // ADD_HL_BC;
    // LD_hl_E;
    // INC_HL;
    // LD_hl_D;
    bc->var1 = LOW(de);
    bc->var2 = HIGH(de);

    // LD_HL(SPRITEANIMSTRUCT_JUMPTABLE_INDEX);
    // ADD_HL_BC;
    // LD_A_hl;
    // XOR_A(0x20);
    // LD_hl_A;
    bc->jumptableIndex ^= 0x20;
    // RET;
}

static void AnimSeq_SlotsGolem(struct SpriteAnim* bc){
    // CALLFAR(aSlots_AnimateGolem);
    Slots_AnimateGolem(bc);
    // RET;
}

static void AnimSeq_SlotsChansey(struct SpriteAnim* bc){
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
    v_ReinitSpriteAnimFrame(bc, SPRITE_ANIM_FRAMESET_SLOTS_CHANSEY_2);
    // RET;
}

static void AnimSeq_SlotsChanseyEgg(struct SpriteAnim* bc){
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
            DeinitializeSprite(bc);
            // LD_A(0x4);
            // LD_addr_A(wSlotsDelay);
            wram->wSlotsDelay = 0x4;
            // LD_DE(SFX_PLACE_PUZZLE_PIECE_DOWN);
            // CALL(aPlaySFX);
            PlaySFX(SFX_PLACE_PUZZLE_PIECE_DOWN);
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
    bc->yOffset = AnimSeqs_Sine(e, 32);
    // RET;
}

static void AnimSeq_UnusedCursor(struct SpriteAnim* bc){
    REG_BC = (bc - wram->wSpriteAnim) * SPRITEANIMSTRUCT_LENGTH + wSpriteAnimationStructs;
    CALLFAR(aUnusedCursor_InterpretJoypad_AnimateCursor);
}

static void AnimSeq_PokegearArrow(struct SpriteAnim* bc){
    // REG_BC = (bc - wram->wSpriteAnim) * SPRITEANIMSTRUCT_LENGTH + wSpriteAnimationStructs;
    // CALLFAR(aAnimatePokegearModeIndicatorArrow);
    AnimatePokegearModeIndicatorArrow(bc);
}

static void AnimSeq_MemoryGameCursor(struct SpriteAnim* bc){
    REG_BC = (bc - wram->wSpriteAnim) * SPRITEANIMSTRUCT_LENGTH + wSpriteAnimationStructs;
    CALLFAR(aMemoryGame_InterpretJoypad_AnimateCursor);
}

static void AnimSeq_TradePokeBall(struct SpriteAnim* bc){
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
        v_ReinitSpriteAnimFrame(bc, SPRITE_ANIM_FRAMESET_TRADE_POKE_BALL_WOBBLE);

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
            bc->yOffset = AnimSeqs_Sine(bc->var1--, 40);
            // RET;
            return;
        }

    // done:
        // LD_DE(SFX_GOT_SAFARI_BALLS);
        // CALL(aPlaySFX);
        PlaySFX(SFX_GOT_SAFARI_BALLS);
        // fallthrough

    case 5:
    // delete:
        // CALL(aDeinitializeSprite);
        DeinitializeSprite(bc);
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
        bc->yOffset = AnimSeqs_Sine(bc->var1, bc->var2);

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
        PlaySFX(SFX_SWITCH_POKEMON);
        // RET;
        return;
    }

}

static void AnimSeq_TradeTubeBulge(struct SpriteAnim* bc){
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
        DeinitializeSprite(bc);
        // RET;
        return;
    }

    // AND_A(0x3);
    // RET_NZ ;
    if((a & 0x3) == 0) {
        // LD_DE(SFX_POKEBALLS_PLACED_ON_TABLE);
        // CALL(aPlaySFX);
        PlaySFX(SFX_POKEBALLS_PLACED_ON_TABLE);
    }
    // RET;
}

static void AnimSeq_TrademonInTube(struct SpriteAnim* bc){
    TradeAnim_AnimateTrademonInTube(bc);
}

static void AnimSeq_RevealNewMon(struct SpriteAnim* bc){
    // LD_HL(SPRITEANIMSTRUCT_VAR1);
    // ADD_HL_BC;
    // LD_A_hl;
    // CP_A(0x80);
    // IF_NC goto finish_EggShell;
    if(bc->var1 >= 0x80) {
    // finish_EggShell:
        // CALL(aDeinitializeSprite);
        // RET;
        return DeinitializeSprite(bc);
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
    bc->yOffset = AnimSeqs_Sine(a, d);

    // POP_DE;
    // POP_AF;
    // CALL(aAnimSeqs_Cosine);

    // LD_HL(SPRITEANIMSTRUCT_XOFFSET);
    // ADD_HL_BC;
    // LD_hl_A;
    bc->xOffset = AnimSeqs_Cosine(a, d);
    // RET;
}

static void AnimSeq_RadioTuningKnob(struct SpriteAnim* bc){
    // REG_BC = (bc - wram->wSpriteAnim) * SPRITEANIMSTRUCT_LENGTH + wSpriteAnimationStructs;
    // CALLFAR(aAnimateTuningKnob);
    AnimateTuningKnob(bc);
}

static void AnimSeq_CutLeaves(struct SpriteAnim* bc){
    uint16_t de;
    // LD_HL(SPRITEANIMSTRUCT_VAR2);
    // ADD_HL_BC;
    // LD_E_hl;
    // INC_HL;
    // LD_D_hl;
    de = (bc->var3 << 8) | bc->var2;
    // LD_HL(0x80);
    // ADD_HL_DE;
    // LD_E_L;
    // LD_D_H;
    de += 0x80;

    // LD_HL(SPRITEANIMSTRUCT_VAR2);
    // ADD_HL_BC;
    // LD_hl_E;
    bc->var2 = LOW(de);
    // INC_HL;
    // LD_hl_D;
    bc->var3 = HIGH(de);

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
    bc->yOffset = AnimSeqs_Sine(a, bc->var3);
    // POP_DE;
    // POP_AF;
    // CALL(aAnimSeqs_Cosine);

    // LD_HL(SPRITEANIMSTRUCT_XOFFSET);
    // ADD_HL_BC;
    // LD_hl_A;
    bc->xOffset = AnimSeqs_Cosine(a, bc->var3);
    // RET;
}

static void AnimSeq_FlyFrom(struct SpriteAnim* bc){
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
    bc->xOffset = AnimSeqs_Cosine(bc->var3++, d);
    // RET;
}

static void AnimSeq_FlyLeaf(struct SpriteAnim* bc){
    // LD_HL(SPRITEANIMSTRUCT_XCOORD);
    // ADD_HL_BC;
    // LD_A_hl;
    // CP_A(-9 * 8);
    // IF_NC goto delete_leaf;
    if(bc->xCoord >= (uint8_t)(-9 * 8)) {
    // delete_leaf:
        // CALL(aDeinitializeSprite);
        // RET;
        return DeinitializeSprite(bc);
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
    bc->xOffset = AnimSeqs_Cosine(bc->var1++, 0x40);
    // RET;
}

static void AnimSeq_FlyTo(struct SpriteAnim* bc){
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
    bc->xOffset = AnimSeqs_Cosine(bc->var3++, d);
    // RET;
}

static void AnimSeq_MobileTradeSentPulse(struct SpriteAnim* bc){
    // REG_BC = (bc - wram->wSpriteAnim) * SPRITEANIMSTRUCT_LENGTH + wSpriteAnimationStructs;
    // FARCALL(aMobileTradeAnim_AnimateSentPulse);
    MobileTradeAnim_AnimateSentPulse(bc);
}

static void AnimSeq_MobileTradeOTPulse(struct SpriteAnim* bc){
    // REG_BC = (bc - wram->wSpriteAnim) * SPRITEANIMSTRUCT_LENGTH + wSpriteAnimationStructs;
    // FARCALL(aMobileTradeAnim_AnimateOTPulse);
    MobileTradeAnim_AnimateOTPulse(bc);
}

static void AnimSeq_IntroSuicune(struct SpriteAnim* bc){
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
    bc->yOffset = AnimSeqs_Sine((bc->var2 ^ 0xff) + 1, 32);
    // LD_A(SPRITE_ANIM_FRAMESET_INTRO_SUICUNE_2);
    // CALL(av_ReinitSpriteAnimFrame);
    v_ReinitSpriteAnimFrame(bc, SPRITE_ANIM_FRAMESET_INTRO_SUICUNE_2);
    // RET;
}

static void AnimSeq_IntroPichuWooper(struct SpriteAnim* bc){
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
    bc->yOffset = AnimSeqs_Sine(((a + 2) ^ 0xff) + 1, 32);

// done:
    // RET;
}

static void AnimSeq_IntroUnown(struct SpriteAnim* bc){
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
    bc->yOffset = AnimSeqs_Sine(a, d);
    // POP_DE;
    // POP_AF;
    // CALL(aAnimSeqs_Cosine);

    // LD_HL(SPRITEANIMSTRUCT_XOFFSET);
    // ADD_HL_BC;
    // LD_hl_A;
    bc->xOffset = AnimSeqs_Cosine(a, d);
    // RET;
}

static void AnimSeq_IntroUnownF(struct SpriteAnim* bc){
    // LD_A_addr(wSlotsDelay);
    // CP_A(0x40);
    // RET_NZ ;
    if(wram->wSlotsDelay != 0x40)
        return;
    // LD_A(SPRITE_ANIM_FRAMESET_INTRO_UNOWN_F_2);
    // CALL(av_ReinitSpriteAnimFrame);
    // RET;
    v_ReinitSpriteAnimFrame(bc, SPRITE_ANIM_FRAMESET_INTRO_UNOWN_F_2);
}

static void AnimSeq_IntroSuicuneAway(struct SpriteAnim* bc){
    // LD_HL(SPRITEANIMSTRUCT_YCOORD);
    // ADD_HL_BC;
    // LD_A_hl;
    // ADD_A(16);
    // LD_hl_A;
    bc->yCoord += 16;
    // RET;
}

static void AnimSeq_EZChatCursor(struct SpriteAnim* bc){
    // REG_BC = (bc - wram->wSpriteAnim) * SPRITEANIMSTRUCT_LENGTH + wSpriteAnimationStructs;
    // FARCALL(aAnimateEZChatCursor);
    AnimateEZChatCursor(bc);
}

static void AnimSeq_Celebi(struct SpriteAnim* bc){
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

static void AnimSeqs_IncAnonJumptableIndex_Conv(struct SpriteAnim* bc){
    // LD_HL(SPRITEANIMSTRUCT_JUMPTABLE_INDEX);
    // ADD_HL_BC;
    // INC_hl;
    // RET;
    bc->jumptableIndex++;
}

static uint8_t AnimSeqs_Sine(uint8_t a, uint8_t d){
    // CALL(aSprites_Sine);
    // RET;
    return Sine(a, d);
}

static uint8_t AnimSeqs_Cosine(uint8_t a, uint8_t d){
    // CALL(aSprites_Cosine);
    // RET;
    return Cosine(a, d);
}
