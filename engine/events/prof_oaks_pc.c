#include "../../constants.h"
#include "prof_oaks_pc.h"
#include "../../home/menu.h"
#include "../../home/text.h"
#include "../../home/joypad.h"
#include "../../home/audio.h"
#include "../../home/pokedex_flags.h"
#include "../../home/copy.h"
#include "../../home/print_text.h"
#include "../../data/text/common.h"

// rating: MACRO
// ; count, sfx, text
// 	db \1
// 	dw \2, \3
// ENDM
struct Rating {
    uint16_t count;
    uint16_t sfx;
    const txt_cmd_s *text;
};

const struct Rating OakRatings[] = {
// if you caught at most this many, play this sound, load this text
// (text is defined in engine/events/prof_oaks_pc.asm)
    {  9, SFX_DEX_FANFARE_LESS_THAN_20, OakRating01},
    { 19, SFX_DEX_FANFARE_LESS_THAN_20, OakRating02},
    { 34, SFX_DEX_FANFARE_20_49,        OakRating03},
    { 49, SFX_DEX_FANFARE_20_49,        OakRating04},
    { 64, SFX_DEX_FANFARE_50_79,        OakRating05},
    { 79, SFX_DEX_FANFARE_50_79,        OakRating06},
    { 94, SFX_DEX_FANFARE_80_109,       OakRating07},
    {109, SFX_DEX_FANFARE_80_109,       OakRating08},
    {124, SFX_CAUGHT_MON,               OakRating09},
    {139, SFX_CAUGHT_MON,               OakRating10},
    {154, SFX_DEX_FANFARE_140_169,      OakRating11},
    {169, SFX_DEX_FANFARE_140_169,      OakRating12},
    {184, SFX_DEX_FANFARE_170_199,      OakRating13},
    {199, SFX_DEX_FANFARE_170_199,      OakRating14},
    {214, SFX_DEX_FANFARE_200_229,      OakRating15},
    {229, SFX_DEX_FANFARE_200_229,      OakRating16},
    {239, SFX_DEX_FANFARE_230_PLUS,     OakRating17},
    {248, SFX_DEX_FANFARE_230_PLUS,     OakRating18},
    {255, SFX_DEX_FANFARE_230_PLUS,     OakRating19},
};

void ProfOaksPC(void){
    // LD_HL(mOakPCText1);
    // CALL(aMenuTextbox);
    MenuTextbox(OakPCText1);
    // CALL(aYesNoBox);
    // IF_C goto shutdown;
    if(YesNoBox()) {
        // CALL(aProfOaksPCBoot);  // player chose "yes"?
        ProfOaksPCBoot();
    }

// shutdown:
    // LD_HL(mOakPCText4);
    // CALL(aPrintText);
    PrintText_Conv2(OakPCText4);
    // CALL(aJoyWaitAorB);
    JoyWaitAorB();
    // CALL(aExitMenu);
    ExitMenu();
    // RET;
}

void ProfOaksPCBoot(void){
    // LD_HL(mOakPCText2);
    // CALL(aPrintText);
    PrintText_Conv2(OakPCText2);
    // CALL(aRate);
    uint16_t sfx = Rate();
    // CALL(aPlaySFX);  // sfx loaded by previous Rate function call
    PlaySFX(sfx);
    // CALL(aJoyWaitAorB);
    JoyWaitAorB();
    // CALL(aWaitSFX);
    WaitSFX();
    // RET;
}

void ProfOaksPCRating(void){
    // CALL(aRate);
    uint16_t sfx = Rate();
    // PUSH_DE;
    // LD_DE(MUSIC_NONE);
    // CALL(aPlayMusic);
    PlayMusic(MUSIC_NONE);
    // POP_DE;
    // CALL(aPlaySFX);
    PlaySFX(sfx);
    // CALL(aJoyWaitAorB);
    JoyWaitAorB();
    // CALL(aWaitSFX);
    WaitSFX();
    // RET;

}


static void Rate_UpdateRatingBuffer(uint8_t* hl, const uint8_t* de) {
    // PUSH_HL;
    // LD_A(0x50);
    // LD_BC(ITEM_NAME_LENGTH);
    // CALL(aByteFill);
    ByteFill(hl, ITEM_NAME_LENGTH, 0x50);
    // POP_HL;
    // LD_BC((PRINTNUM_LEFTALIGN | 1 << 8) | 3);
    // CALL(aPrintNum);
    PrintNum_Conv2(hl, de, PRINTNUM_LEFTALIGN | 1, 3);
    // RET;
}

static void Rate_UpdateRatingBuffers(uint8_t seen, uint8_t caught) {
    // LD_HL(wStringBuffer3);
    // LD_DE(wTempPokedexSeenCount);
    // CALL(aRate_UpdateRatingBuffer);
    Rate_UpdateRatingBuffer(wram->wStringBuffer3, &seen);
    // LD_HL(wStringBuffer4);
    // LD_DE(wTempPokedexCaughtCount);
    // CALL(aRate_UpdateRatingBuffer);
    Rate_UpdateRatingBuffer(wram->wStringBuffer4, &caught);
    // RET;
}

uint16_t Rate(void){
//  calculate Seen/Owned
    // LD_HL(wPokedexSeen);
    // LD_B(wEndPokedexSeen - wPokedexSeen);
    // CALL(aCountSetBits);
    // LD_addr_A(wTempPokedexSeenCount);
    uint8_t seen = CountSetBits(wram->wPokedexSeen, sizeof(wram->wPokedexSeen));
    // LD_HL(wPokedexCaught);
    // LD_B(wEndPokedexCaught - wPokedexCaught);
    // CALL(aCountSetBits);
    // LD_addr_A(wTempPokedexCaughtCount);
    uint8_t caught = CountSetBits(wram->wPokedexCaught, sizeof(wram->wPokedexCaught));

//  print appropriate rating
    // CALL(aRate_UpdateRatingBuffers);
    Rate_UpdateRatingBuffers(seen, caught);
    // LD_HL(mOakPCText3);
    // CALL(aPrintText);
    PrintText_Conv2(OakPCText3);
    // CALL(aJoyWaitAorB);
    JoyWaitAorB();
    // LD_A_addr(wTempPokedexCaughtCount);
    // LD_HL(mOakRatings);
    // CALL(aFindOakRating);
    uint16_t sfx = SFX_DEX_FANFARE_230_PLUS;
    const txt_cmd_s* text = NULL;
    FindOakRating(caught, &sfx, &text);
    // PUSH_DE;
    // CALL(aPrintText);
    PrintText_Conv2(text);
    // POP_DE;
    // RET;
    return sfx;
}

//  return sound effect in de
//  return text pointer in hl
void FindOakRating(uint8_t caught, uint16_t* sfx, const txt_cmd_s** txt){
    // NOP;
    // LD_C_A;

    for(uint32_t i = 0; i < lengthof(OakRatings); ++i) {
    // loop:
        // LD_A_hli;
        // CP_A_C;
        // IF_NC goto match;
        if(OakRatings[i].count >= caught) {
        // match:
            // LD_A_hli;
            // LD_E_A;
            // LD_A_hli;
            // LD_D_A;
            *sfx = OakRatings[i].sfx;
            // LD_A_hli;
            // LD_H_hl;
            // LD_L_A;
            *txt = OakRatings[i].text;
            // RET;
            return;
        }
        // for(int rept = 0; rept < 4; rept++){
        // INC_HL;
        // }
        // goto loop;
    }
// INCLUDE "data/events/pokedex_ratings.asm"
}

const txt_cmd_s OakPCText1[] = {
    text_far(v_OakPCText1)
    text_end
};

const txt_cmd_s OakPCText2[] = {
    text_far(v_OakPCText2)
    text_end
};

const txt_cmd_s OakPCText3[] = {
    text_far(v_OakPCText3)
    text_end
};

const txt_cmd_s OakRating01[] = {
    text_far(v_OakRating01)
    text_end
};

const txt_cmd_s OakRating02[] = {
    text_far(v_OakRating02)
    text_end
};

const txt_cmd_s OakRating03[] = {
    text_far(v_OakRating03)
    text_end
};

const txt_cmd_s OakRating04[] = {
    text_far(v_OakRating04)
    text_end
};

const txt_cmd_s OakRating05[] = {
    text_far(v_OakRating05)
    text_end
};

const txt_cmd_s OakRating06[] = {
    text_far(v_OakRating06)
    text_end
};

const txt_cmd_s OakRating07[] = {
    text_far(v_OakRating07)
    text_end
};

const txt_cmd_s OakRating08[] = {
    text_far(v_OakRating08)
    text_end
};

const txt_cmd_s OakRating09[] = {
    text_far(v_OakRating09)
    text_end
};

const txt_cmd_s OakRating10[] = {
    text_far(v_OakRating10)
    text_end
};

const txt_cmd_s OakRating11[] = {
    text_far(v_OakRating11)
    text_end
};

const txt_cmd_s OakRating12[] = {
    text_far(v_OakRating12)
    text_end
};

const txt_cmd_s OakRating13[] = {
    text_far(v_OakRating13)
    text_end
};

const txt_cmd_s OakRating14[] = {
    text_far(v_OakRating14)
    text_end
};

const txt_cmd_s OakRating15[] = {
    text_far(v_OakRating15)
    text_end
};

const txt_cmd_s OakRating16[] = {
    text_far(v_OakRating16)
    text_end
};

const txt_cmd_s OakRating17[] = {
    text_far(v_OakRating17)
    text_end
};

const txt_cmd_s OakRating18[] = {
    text_far(v_OakRating18)
    text_end
};

const txt_cmd_s OakRating19[] = {
    text_far(v_OakRating19)
    text_end
};

const txt_cmd_s OakPCText4[] = {
    text_far(v_OakPCText4)
    text_end
};
