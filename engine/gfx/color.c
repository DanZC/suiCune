#include "../../constants.h"
#include "color.h"
#include "../../home/copy.h"
#include "../../data/pokemon/pic_pointers.h"
#include "../../data/pokemon/unown_pic_pointers.h"
#include "../../data/pokemon/palettes.h"

// INCLUDE "engine/gfx/sgb_layouts.asm"

#define SHINY_ATK_BIT (5)
#define SHINY_DEF_VAL (10)
#define SHINY_SPD_VAL (10)
#define SHINY_SPC_VAL (10)

void CheckShininess(void){
//  Check if a mon is shiny by DVs at bc.
//  Return carry if shiny.

    LD_L_C;
    LD_H_B;

//  Attack
    LD_A_hl;
    AND_A(1 << SHINY_ATK_BIT);
    IF_Z goto not_shiny;

//  Defense
    LD_A_hli;
    AND_A(0xf);
    CP_A(SHINY_DEF_VAL);
    IF_NZ goto not_shiny;

//  Speed
    LD_A_hl;
    AND_A(0xf0);
    CP_A(SHINY_SPD_VAL << 4);
    IF_NZ goto not_shiny;

//  Special
    LD_A_hl;
    AND_A(0xf);
    CP_A(SHINY_SPC_VAL);
    IF_NZ goto not_shiny;

//  shiny
    SCF;
    RET;


not_shiny:
    AND_A_A;
    RET;

}

//  Check if a mon is shiny by DVs at bc.
//  Return true if shiny.
bool CheckShininess_Conv(uint16_t bc){
    // LD_L_C;
    // LD_H_B;
    union Register hl = {.reg = bc};

//  Attack
    // LD_A_hl;
    // AND_A(1 << SHINY_ATK_BIT);
    // IF_Z goto not_shiny;
    if((hl.lo & (1 << SHINY_ATK_BIT)) == 0)
        return false;

//  Defense
    // LD_A_hli;
    // AND_A(0xf);
    // CP_A(SHINY_DEF_VAL);
    // IF_NZ goto not_shiny;
    if((hl.lo & 0xf) != SHINY_DEF_VAL)
        return false;

//  Speed
    // LD_A_hl;
    // AND_A(0xf0);
    // CP_A(SHINY_SPD_VAL << 4);
    // IF_NZ goto not_shiny;
    if(((hl.hi & 0xf0) >> 4) != SHINY_SPD_VAL)
        return false;

//  Special
    // LD_A_hl;
    // AND_A(0xf);
    // CP_A(SHINY_SPC_VAL);
    // IF_NZ goto not_shiny;
    if((hl.hi & 0xf) != SHINY_SPC_VAL)
        return false;

//  shiny
    // SCF;
    // RET;
    return true;

// not_shiny:
    // AND_A_A;
    // RET;
}

void Unused_CheckShininess(void){
//  Return carry if the DVs at hl are all 10 or higher.

//  Attack
    LD_A_hl;
    CP_A(10 << 4);
    IF_C goto not_shiny;

//  Defense
    LD_A_hli;
    AND_A(0xf);
    CP_A(10);
    IF_C goto not_shiny;

//  Speed
    LD_A_hl;
    CP_A(10 << 4);
    IF_C goto not_shiny;

//  Special
    LD_A_hl;
    AND_A(0xf);
    CP_A(10);
    IF_C goto not_shiny;

//  shiny
    SCF;
    RET;


not_shiny:
    AND_A_A;
    RET;

}

void SGB_ApplyCreditsPals(void){
//  //  unreferenced
    PUSH_DE;
    PUSH_BC;
    LD_HL(mPalPacket_Pal01);
    LD_DE(wSGBPals);
    LD_BC(PALPACKET_LENGTH);
    CALL(aCopyBytes);
    POP_BC;
    POP_DE;
    LD_A_C;
    LD_addr_A(wSGBPals + 3);
    LD_A_B;
    LD_addr_A(wSGBPals + 4);
    LD_A_E;
    LD_addr_A(wSGBPals + 5);
    LD_A_D;
    LD_addr_A(wSGBPals + 6);
    LD_HL(wSGBPals);
    CALL(aPushSGBPals);
    LD_HL(mBlkPacket_AllPal0);
    CALL(aPushSGBPals);
    RET;

}

void InitPartyMenuPalettes(void){
    LD_HL(mPalPacket_PartyMenu + 1);
    CALL(aCopyFourPalettes);
    CALL(aInitPartyMenuOBPals);
    CALL(aWipeAttrmap);
    RET;

//  SGB layout for SCGB_PARTY_MENU_HP_BARS
    return SGB_ApplyPartyMenuHPPals();
}

void SGB_ApplyPartyMenuHPPals(void){
    LD_HL(wHPPals);
    LD_A_addr(wSGBPals);
    LD_E_A;
    LD_D(0);
    ADD_HL_DE;
    LD_E_L;
    LD_D_H;
    LD_A_de;
    AND_A_A;
    LD_E(0x5);
    IF_Z goto okay;
    DEC_A;
    LD_E(0xa);
    IF_Z goto okay;
    LD_E(0xf);

okay:
    PUSH_DE;
    LD_HL(wSGBPals + 10);
    LD_BC(0x6);
    LD_A_addr(wSGBPals);
    CALL(aAddNTimes);
    POP_DE;
    LD_hl_E;
    RET;

}

void Intro_LoadMagikarpPalettes(void){
//  //  unreferenced
    CALL(aCheckCGB);
    RET_Z ;

//  CGB only
    LD_HL(mIntro_LoadMagikarpPalettes_MagikarpBGPal);
    LD_DE(wBGPals1);
    LD_BC(1 * PALETTE_SIZE);
    LD_A(BANK(wBGPals1));
    CALL(aFarCopyWRAM);

    LD_HL(mIntro_LoadMagikarpPalettes_MagikarpOBPal);
    LD_DE(wOBPals1);
    LD_BC(1 * PALETTE_SIZE);
    LD_A(BANK(wOBPals1));
    CALL(aFarCopyWRAM);

    CALL(aApplyPals);
    LD_A(TRUE);
    LDH_addr_A(hCGBPalUpdate);
    RET;


MagikarpBGPal:
// INCLUDE "gfx/intro/gs_magikarp_bg.pal"


MagikarpOBPal:
// INCLUDE "gfx/intro/gs_magikarp_ob.pal"

    return Intro_LoadAllPal0();
}

void Intro_LoadAllPal0(void){
//  //  unreferenced
    CALL(aCheckCGB);
    RET_NZ ;
    LDH_A_addr(hSGB);
    AND_A_A;
    RET_Z ;
    LD_HL(mBlkPacket_AllPal0);
    JP(mPushSGBPals);

}

void Intro_LoadBetaIntroVenusaurPalettes(void){
//  //  unreferenced
    CALL(aCheckCGB);
    IF_NZ goto cgb;
    LDH_A_addr(hSGB);
    AND_A_A;
    RET_Z ;
    LD_HL(mPalPacket_BetaIntroVenusaur);
    JP(mPushSGBPals);


cgb:
    LD_DE(wOBPals1);
    LD_A(PREDEFPAL_BETA_INTRO_VENUSAUR);
    CALL(aGetPredefPal);
    JP(mLoadHLPaletteIntoDE);

}

void Intro_LoadPackPalettes(void){
//  //  unreferenced
    CALL(aCheckCGB);
    IF_NZ goto cgb;
    LDH_A_addr(hSGB);
    AND_A_A;
    RET_Z ;
    LD_HL(mPalPacket_Pack);
    JP(mPushSGBPals);


cgb:
    LD_DE(wOBPals1);
    LD_A(PREDEFPAL_PACK);
    CALL(aGetPredefPal);
    JP(mLoadHLPaletteIntoDE);

}

void GSIntro_LoadMonPalette(void){
//  //  unreferenced
    CALL(aCheckCGB);
    IF_NZ goto cgb;
    LDH_A_addr(hSGB);
    AND_A_A;
    RET_Z ;
    LD_A_C;
    PUSH_AF;
    LD_HL(mPalPacket_Pal01);
    LD_DE(wSGBPals);
    LD_BC(PALPACKET_LENGTH);
    CALL(aCopyBytes);
    POP_AF;
    CALL(aGetMonPalettePointer);
    LD_A_hli;
    LD_addr_A(wSGBPals + 3);
    LD_A_hli;
    LD_addr_A(wSGBPals + 4);
    LD_A_hli;
    LD_addr_A(wSGBPals + 5);
    LD_A_hl;
    LD_addr_A(wSGBPals + 6);
    LD_HL(wSGBPals);
    JP(mPushSGBPals);


cgb:
    LD_DE(wOBPals1);
    LD_A_C;
    CALL(aGetMonPalettePointer);
    CALL(aLoadPalette_White_Col1_Col2_Black);
    RET;

}

void LoadTrainerClassPaletteAsNthBGPal(void){
    LD_A_addr(wTrainerClass);
    CALL(aGetTrainerPalettePointer);
    LD_A_E;
    JR(mLoadNthMiddleBGPal);

}

void LoadMonPaletteAsNthBGPal(void){
    LD_A_addr(wCurPartySpecies);
    CALL(av_GetMonPalettePointer);
    LD_A_E;
    BIT_A(7);
    JR_Z (mLoadNthMiddleBGPal);
    AND_A(0x7f);
    INC_HL;
    INC_HL;
    INC_HL;
    INC_HL;

    return LoadNthMiddleBGPal();
}

void LoadNthMiddleBGPal(void){
    PUSH_HL;
    LD_HL(wBGPals1);
    LD_DE(1 * PALETTE_SIZE);

loop:
    AND_A_A;
    IF_Z goto got_addr;
    ADD_HL_DE;
    DEC_A;
    goto loop;


got_addr:
    LD_E_L;
    LD_D_H;
    POP_HL;
    CALL(aLoadPalette_White_Col1_Col2_Black);
    RET;

}

void LoadBetaPokerPalettes(void){
//  //  unreferenced
    LDH_A_addr(hCGB);
    AND_A_A;
    IF_NZ goto cgb;
    LD_HL(wBetaPokerSGBPals);
    JP(mPushSGBPals);


cgb:
    LD_A_addr(wBetaPokerSGBCol);
    LD_C_A;
    LD_A_addr(wBetaPokerSGBRow);
    hlcoord(0, 0, wAttrmap);
    LD_DE(SCREEN_WIDTH);

loop:
    AND_A_A;
    IF_Z goto done;
    ADD_HL_DE;
    DEC_A;
    goto loop;


done:
    LD_B(0);
    ADD_HL_BC;
    LD_BC((6 << 8) | 4);
    LD_A_addr(wBetaPokerSGBAttr);
    AND_A(0x3);
    CALL(aFillBoxCGB);
    CALL(aCopyTilemapAtOnce);
    RET;

}

void ApplyMonOrTrainerPals(void){
    CALL(aCheckCGB);
    RET_Z ;
    LD_A_E;
    AND_A_A;
    IF_Z goto get_trainer;
    LD_A_addr(wCurPartySpecies);
    CALL(aGetMonPalettePointer);
    goto load_palettes;


get_trainer:
    LD_A_addr(wTrainerClass);
    CALL(aGetTrainerPalettePointer);


load_palettes:
    LD_DE(wBGPals1);
    CALL(aLoadPalette_White_Col1_Col2_Black);
    CALL(aWipeAttrmap);
    CALL(aApplyAttrmap);
    CALL(aApplyPals);
    RET;

}

void ApplyHPBarPals(void){
    LD_A_addr(wWhichHPBar);
    AND_A_A;
    IF_Z goto Enemy;
    CP_A(0x1);
    IF_Z goto Player;
    CP_A(0x2);
    IF_Z goto PartyMenu;
    RET;


Enemy:
    LD_DE(wBGPals2 + PALETTE_SIZE * PAL_BATTLE_BG_ENEMY_HP + PAL_COLOR_SIZE * 1);
    goto okay;


Player:
    LD_DE(wBGPals2 + PALETTE_SIZE * PAL_BATTLE_BG_PLAYER_HP + PAL_COLOR_SIZE * 1);


okay:
    LD_L_C;
    LD_H(0x0);
    ADD_HL_HL;
    ADD_HL_HL;
    LD_BC(mHPBarPals);
    ADD_HL_BC;
    LD_BC(4);
    LD_A(BANK(wBGPals2));
    CALL(aFarCopyWRAM);
    LD_A(TRUE);
    LDH_addr_A(hCGBPalUpdate);
    RET;


PartyMenu:
    LD_E_C;
    INC_E;
    hlcoord(11, 1, wAttrmap);
    LD_BC(2 * SCREEN_WIDTH);
    LD_A_addr(wCurPartyMon);

loop:
    AND_A_A;
    IF_Z goto done;
    ADD_HL_BC;
    DEC_A;
    goto loop;


done:
    LD_BC((2 << 8) | 8);
    LD_A_E;
    CALL(aFillBoxCGB);
    RET;

}

void LoadStatsScreenPals(void){
    CALL(aCheckCGB);
    RET_Z ;
    LD_HL(mStatsScreenPals);
    LD_B(0);
    DEC_C;
    ADD_HL_BC;
    ADD_HL_BC;
    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(BANK(wBGPals1));
    LDH_addr_A(rSVBK);
    LD_A_hli;
    LD_addr_A(wBGPals1 + PALETTE_SIZE * 0);
    LD_addr_A(wBGPals1 + PALETTE_SIZE * 2);
    LD_A_hl;
    LD_addr_A(wBGPals1 + PALETTE_SIZE * 0 + 1);
    LD_addr_A(wBGPals1 + PALETTE_SIZE * 2 + 1);
    POP_AF;
    LDH_addr_A(rSVBK);
    CALL(aApplyPals);
    LD_A(0x1);
    RET;

}

bool LoadStatsScreenPals_Conv(uint8_t c){
    // CALL(aCheckCGB);
    // RET_Z ;
    if(hram->hCGB == 0)
        return false;

    uint16_t pal_buf[3];
    LoadPaletteAssetColorsToArray(pal_buf, "gfx/stats/stats.pal", 0, 3);
    // LD_HL(mStatsScreenPals);
    // LD_B(0);
    // DEC_C;
    // ADD_HL_BC;
    // ADD_HL_BC;
    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    // LD_A(BANK(wBGPals1));
    // LDH_addr_A(rSVBK);
    // LD_A_hli;
    // LD_addr_A(wBGPals1 + PALETTE_SIZE * 0);
    wram->wBGPals1[PALETTE_SIZE * 0] = LOW(pal_buf[c-1]);
    // LD_addr_A(wBGPals1 + PALETTE_SIZE * 2);
    wram->wBGPals1[PALETTE_SIZE * 2] = LOW(pal_buf[c-1]);
    // LD_A_hl;
    // LD_addr_A(wBGPals1 + PALETTE_SIZE * 0 + 1);
    wram->wBGPals1[PALETTE_SIZE * 0 + 1] = HIGH(pal_buf[c-1]);
    // LD_addr_A(wBGPals1 + PALETTE_SIZE * 2 + 1);
    wram->wBGPals1[PALETTE_SIZE * 2 + 1] = HIGH(pal_buf[c-1]);
    // POP_AF;
    // LDH_addr_A(rSVBK);
    // CALL(aApplyPals);
    ApplyPals_Conv();
    // LD_A(0x1);
    // RET;
    return true;
}

void LoadMailPalettes(void){
    LD_L_E;
    LD_H(0);
    ADD_HL_HL;
    ADD_HL_HL;
    ADD_HL_HL;
    LD_DE(mLoadMailPalettes_MailPals);
    ADD_HL_DE;
    CALL(aCheckCGB);
    IF_NZ goto cgb;
    PUSH_HL;
    LD_HL(mPalPacket_Pal01);
    LD_DE(wSGBPals);
    LD_BC(PALPACKET_LENGTH);
    CALL(aCopyBytes);
    POP_HL;
    INC_HL;
    INC_HL;
    LD_A_hli;
    LD_addr_A(wSGBPals + 3);
    LD_A_hli;
    LD_addr_A(wSGBPals + 4);
    LD_A_hli;
    LD_addr_A(wSGBPals + 5);
    LD_A_hli;
    LD_addr_A(wSGBPals + 6);
    LD_HL(wSGBPals);
    CALL(aPushSGBPals);
    LD_HL(mBlkPacket_AllPal0);
    CALL(aPushSGBPals);
    RET;


cgb:
    LD_DE(wBGPals1);
    LD_BC(1 * PALETTE_SIZE);
    LD_A(BANK(wBGPals1));
    CALL(aFarCopyWRAM);
    CALL(aApplyPals);
    CALL(aWipeAttrmap);
    CALL(aApplyAttrmap);
    RET;


MailPals:
// INCLUDE "gfx/mail/mail.pal"

// INCLUDE "engine/gfx/cgb_layouts.asm"

    return CopyFourPalettes();
}

void CopyFourPalettes(void){
    LD_DE(wBGPals1);
    LD_C(4);

    return CopyPalettes();
}

void CopyPalettes(void){

loop:
    PUSH_BC;
    LD_A_hli;
    PUSH_HL;
    CALL(aGetPredefPal);
    CALL(aLoadHLPaletteIntoDE);
    POP_HL;
    INC_HL;
    POP_BC;
    DEC_C;
    IF_NZ goto loop;
    RET;

}

void GetPredefPal(void){
    LD_L_A;
    LD_H(0);
    ADD_HL_HL;
    ADD_HL_HL;
    ADD_HL_HL;
    LD_BC(mPredefPals);
    ADD_HL_BC;
    RET;

}

void LoadHLPaletteIntoDE(void){
    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(BANK(wOBPals1));
    LDH_addr_A(rSVBK);
    LD_C(1 * PALETTE_SIZE);

loop:
    LD_A_hli;
    LD_de_A;
    INC_DE;
    DEC_C;
    IF_NZ goto loop;
    POP_AF;
    LDH_addr_A(rSVBK);
    RET;

}

void LoadPalette_White_Col1_Col2_Black(void){
    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(BANK(wBGPals1));
    LDH_addr_A(rSVBK);

    LD_A(LOW(PALRGB_WHITE));
    LD_de_A;
    INC_DE;
    LD_A(HIGH(PALRGB_WHITE));
    LD_de_A;
    INC_DE;

    LD_C(2 * PAL_COLOR_SIZE);

loop:
    LD_A_hli;
    LD_de_A;
    INC_DE;
    DEC_C;
    IF_NZ goto loop;

    XOR_A_A;
    LD_de_A;
    INC_DE;
    LD_de_A;
    INC_DE;

    POP_AF;
    LDH_addr_A(rSVBK);
    RET;

}

uint16_t* LoadPalette_White_Col1_Col2_Black_Conv(uint16_t* de, const uint16_t* hl){
    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    // LD_A(BANK(wBGPals1));
    // LDH_addr_A(rSVBK);

    // LD_A(LOW(PALRGB_WHITE));
    // LD_de_A;
    // INC_DE;
    // LD_A(HIGH(PALRGB_WHITE));
    // LD_de_A;
    // INC_DE;
    *(de++) = PALRGB_WHITE;

    // LD_C(2 * PAL_COLOR_SIZE);
    uint8_t c = 2;

    do {
    // loop:
        // LD_A_hli;
        // LD_de_A;
        *(de++) = *(hl++);
        // INC_DE;
        // DEC_C;
        // IF_NZ goto loop;
    } while(--c != 0);

    // XOR_A_A;
    // LD_de_A;
    // INC_DE;
    // LD_de_A;
    // INC_DE;

    *(de++) = 0;

    // POP_AF;
    // LDH_addr_A(rSVBK);
    // RET;
    return de;
}

void FillBoxCGB(void){

row:
    PUSH_BC;
    PUSH_HL;

col:
    LD_hli_A;
    DEC_C;
    IF_NZ goto col;
    POP_HL;
    LD_BC(SCREEN_WIDTH);
    ADD_HL_BC;
    POP_BC;
    DEC_B;
    IF_NZ goto row;
    RET;

}

void FillBoxCGB_Conv(uint8_t* hl, uint8_t b, uint8_t c, uint8_t a){

    for(uint8_t y = 0; y < b; y++) {
    // row:
        // PUSH_BC;
        // PUSH_HL;

        for(uint8_t x = 0; x < c; ++x) {
        // col:
            // LD_hli_A;
            *coord(x, y, hl) = a;
            // DEC_C;
            // IF_NZ goto col;
        }
        // POP_HL;
        // LD_BC(SCREEN_WIDTH);
        // ADD_HL_BC;
        // POP_BC;
        // DEC_B;
        // IF_NZ goto row;
    }
    // RET;
}

void ResetBGPals(void){
    PUSH_AF;
    PUSH_BC;
    PUSH_DE;
    PUSH_HL;

    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(BANK(wBGPals1));
    LDH_addr_A(rSVBK);

    LD_HL(wBGPals1);
    LD_C(1 * PALETTE_SIZE);

loop:
    LD_A(0xff);
    LD_hli_A;
    LD_hli_A;
    LD_hli_A;
    LD_hli_A;
    XOR_A_A;
    LD_hli_A;
    LD_hli_A;
    LD_hli_A;
    LD_hli_A;
    DEC_C;
    IF_NZ goto loop;

    POP_AF;
    LDH_addr_A(rSVBK);

    POP_HL;
    POP_DE;
    POP_BC;
    POP_AF;
    RET;

}

void ResetBGPals_Conv(void){
    // PUSH_AF;
    // PUSH_BC;
    // PUSH_DE;
    // PUSH_HL;

    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    // LD_A(BANK(wBGPals1));
    // LDH_addr_A(rSVBK);

    // LD_HL(wBGPals1);
    uint8_t* hl = wram->wBGPals1;
    // LD_C(1 * PALETTE_SIZE);

// loop:
    for(int i = 0; i < PALETTE_SIZE; i++) {
        // LD_A(0xff);
        // LD_hli_A;
        *(hl++) = 0xff;
        // LD_hli_A;
        *(hl++) = 0xff;
        // LD_hli_A;
        *(hl++) = 0xff;
        // LD_hli_A;
        *(hl++) = 0xff;
        // XOR_A_A;
        // LD_hli_A;
        *(hl++) = 0;
        // LD_hli_A;
        *(hl++) = 0;
        // LD_hli_A;
        *(hl++) = 0;
        // LD_hli_A;
        *(hl++) = 0;
        // DEC_C;
        // IF_NZ goto loop;
    }

    // POP_AF;
    // LDH_addr_A(rSVBK);

    // POP_HL;
    // POP_DE;
    // POP_BC;
    // POP_AF;
    // RET;
}

void WipeAttrmap(void){
    // hlcoord(0, 0, wAttrmap);
    // LD_BC(SCREEN_WIDTH * SCREEN_HEIGHT);
    // XOR_A_A;
    // CALL(aByteFill);
    // RET;
    return ByteFill_Conv2(wram->wAttrmap, SCREEN_WIDTH * SCREEN_HEIGHT, 0);
}

void ApplyPals(void){
    LD_HL(wBGPals1);
    LD_DE(wBGPals2);
    LD_BC(16 * PALETTE_SIZE);
    LD_A(BANK(wGBCPalettes));
    CALL(aFarCopyWRAM);
    RET;

}

void ApplyPals_Conv(void){
    // LD_HL(wBGPals1);
    // LD_DE(wBGPals2);
    // LD_BC(16 * PALETTE_SIZE);
    // LD_A(BANK(wGBCPalettes));
    // CALL(aFarCopyWRAM);
    // RET;
    return CopyBytes_Conv2(wram->wBGPals2, wram->wBGPals1, 16 * PALETTE_SIZE);
}

void ApplyAttrmap(void){
    LDH_A_addr(rLCDC);
    BIT_A(rLCDC_ENABLE);
    IF_Z goto UpdateVBank1;
    LDH_A_addr(hBGMapMode);
    PUSH_AF;
    LD_A(0x2);
    LDH_addr_A(hBGMapMode);
    CALL(aDelayFrame);
    CALL(aDelayFrame);
    CALL(aDelayFrame);
    CALL(aDelayFrame);
    POP_AF;
    LDH_addr_A(hBGMapMode);
    RET;


UpdateVBank1:
    hlcoord(0, 0, wAttrmap);
    debgcoord(0, 0, vBGMap0);
    LD_B(SCREEN_HEIGHT);
    LD_A(0x1);
    LDH_addr_A(rVBK);

row:
    LD_C(SCREEN_WIDTH);

col:
    LD_A_hli;
    LD_de_A;
    INC_DE;
    DEC_C;
    IF_NZ goto col;
    LD_A(BG_MAP_WIDTH - SCREEN_WIDTH);
    ADD_A_E;
    IF_NC goto okay;
    INC_D;

okay:
    LD_E_A;
    DEC_B;
    IF_NZ goto row;
    LD_A(0x0);
    LDH_addr_A(rVBK);
    RET;
}

void ApplyAttrmap_Conv(void){
    // LDH_A_addr(rLCDC);
    // BIT_A(rLCDC_ENABLE);
    // IF_Z goto UpdateVBank1;
    // LDH_A_addr(hBGMapMode);
    // PUSH_AF;
    // LD_A(0x2);
    // LDH_addr_A(hBGMapMode);
    // CALL(aDelayFrame);
    // CALL(aDelayFrame);
    // CALL(aDelayFrame);
    // CALL(aDelayFrame);
    // POP_AF;
    // LDH_addr_A(hBGMapMode);
    // RET;


// UpdateVBank1:
    // hlcoord(0, 0, wAttrmap);
    // debgcoord(0, 0, vBGMap0);
    uint8_t* hl = coord(0, 0, wram->wAttrmap);
    uint8_t* de = bgcoord(0, 0, vram->vBGMap2);
    // LD_B(SCREEN_HEIGHT);
    uint8_t b = SCREEN_HEIGHT;
    // LD_A(0x1);
    // LDH_addr_A(rVBK);

    do {
    // row:
        // LD_C(SCREEN_WIDTH);
        uint8_t c = SCREEN_WIDTH;

        do {
        // col:
            // LD_A_hli;
            // LD_de_A;
            // INC_DE;
            *(de++) = *(hl++);
            // DEC_C;
            // IF_NZ goto col;
        } while(--c != 0);
        // LD_A(BG_MAP_WIDTH - SCREEN_WIDTH);
        // ADD_A_E;
        // IF_NC goto okay;
        // INC_D;

    // okay:
        // LD_E_A;
        de += (BG_MAP_WIDTH - SCREEN_WIDTH);
        // DEC_B;
        // IF_NZ goto row;
    } while(--b != 0);
    // LD_A(0x0);
    // LDH_addr_A(rVBK);
    // RET;
}

//  CGB layout for SCGB_PARTY_MENU_HP_BARS
void CGB_ApplyPartyMenuHPPals(void){
    LD_HL(wHPPals);
    LD_A_addr(wSGBPals);
    LD_E_A;
    LD_D(0);
    ADD_HL_DE;
    LD_E_L;
    LD_D_H;
    LD_A_de;
    INC_A;
    LD_E_A;
    hlcoord(11, 2, wAttrmap);
    LD_BC(2 * SCREEN_WIDTH);
    LD_A_addr(wSGBPals);

loop:
    AND_A_A;
    IF_Z goto done;
    ADD_HL_BC;
    DEC_A;
    goto loop;

done:
    LD_BC((2 << 8) | 8);
    LD_A_E;
    CALL(aFillBoxCGB);
    RET;

}

void CGB_ApplyPartyMenuHPPals_Conv(void){
    // LD_HL(wHPPals);
    // LD_A_addr(wSGBPals);
    // LD_E_A;
    // LD_D(0);
    // ADD_HL_DE;
    // LD_E_L;
    // LD_D_H;
    // LD_A_de;
    // INC_A;
    // LD_E_A;
    uint8_t e = wram->wHPPals[wram->wSGBPals[0]] + 1;
    // hlcoord(11, 2, wAttrmap);
    uint8_t* hl = coord(11, 2, wram->wAttrmap) + (2 * SCREEN_WIDTH * wram->wSGBPals[0]);
    // LD_BC(2 * SCREEN_WIDTH);
    // LD_A_addr(wSGBPals);

// loop:
    // AND_A_A;
    // IF_Z goto done;
    // ADD_HL_BC;
    // DEC_A;
    // goto loop;

// done:
    // LD_BC((2 << 8) | 8);
    // LD_A_E;
    // CALL(aFillBoxCGB);
    FillBoxCGB_Conv(hl, 2, 8, e);
    // RET;
}

void InitPartyMenuOBPals(void){
    LD_HL(mPartyMenuOBPals);
    LD_DE(wOBPals1);
    LD_BC(2 * PALETTE_SIZE);
    LD_A(BANK(wOBPals1));
    CALL(aFarCopyWRAM);
    RET;

}

void GetBattlemonBackpicPalettePointer(void){
    PUSH_DE;
    FARCALL(aGetPartyMonDVs);
    LD_C_L;
    LD_B_H;
    LD_A_addr(wTempBattleMonSpecies);
    CALL(aGetPlayerOrMonPalettePointer);
    POP_DE;
    RET;

}

void GetEnemyFrontpicPalettePointer(void){
    PUSH_DE;
    FARCALL(aGetEnemyMonDVs);
    LD_C_L;
    LD_B_H;
    LD_A_addr(wTempEnemyMonSpecies);
    CALL(aGetFrontpicPalettePointer);
    POP_DE;
    RET;

}

void GetPlayerOrMonPalettePointer(void){
    AND_A_A;
    JP_NZ (mGetMonNormalOrShinyPalettePointer);
    LD_A_addr(wPlayerSpriteSetupFlags);
    BIT_A(PLAYERSPRITESETUP_FEMALE_TO_MALE_F);
    IF_NZ goto male;
    LD_A_addr(wPlayerGender);
    AND_A_A;
    IF_Z goto male;
    LD_HL(mKrisPalette);
    RET;


male:
    LD_HL(mPlayerPalette);
    RET;

}

const char PlayerPalette[] = "gfx/trainers/cal.png";
const char KrisPalette[] = "gfx/trainers/falkner.png";

uint16_t* GetPlayerOrMonPalettePointer_Conv(uint16_t* dest, uint8_t a, uint16_t bc){
    // AND_A_A;
    // JP_NZ (mGetMonNormalOrShinyPalettePointer);
    if(a != 0) {
        return GetMonNormalOrShinyPalettePointer_Conv(dest, a, bc);
    }
    // LD_A_addr(wPlayerSpriteSetupFlags);
    // BIT_A(PLAYERSPRITESETUP_FEMALE_TO_MALE_F);
    // IF_NZ goto male;
    if(bit_test(wram->wPlayerSpriteSetupFlags, PLAYERSPRITESETUP_FEMALE_TO_MALE_F) || wram->wPlayerGender == MALE) {
        ExtractPaletteFromPNGAssetToBuffer(dest, PlayerPalette);
        return dest;
    }
    // LD_A_addr(wPlayerGender);
    // AND_A_A;
    // IF_Z goto male;
    // LD_HL(mKrisPalette);
    // RET;
    ExtractPaletteFromPNGAssetToBuffer(dest, KrisPalette);
    return dest;

// male:
    // LD_HL(mPlayerPalette);
    // RET;
}

void GetFrontpicPalettePointer(void){
    AND_A_A;
    JP_NZ (mGetMonNormalOrShinyPalettePointer);
    LD_A_addr(wTrainerClass);

    return GetTrainerPalettePointer();
}

void GetTrainerPalettePointer(void){
    LD_L_A;
    LD_H(0);
    ADD_HL_HL;
    ADD_HL_HL;
    LD_BC(mTrainerPalettes);
    ADD_HL_BC;
    RET;

}

void GetMonPalettePointer(void){
    CALL(av_GetMonPalettePointer);
    RET;

}

void CGBCopyBattleObjectPals(void){
//  //  unreferenced
//  dummied out
    RET;
    CALL(aCheckCGB);
    RET_Z ;
    LD_HL(mBattleObjectPals);
    LD_A((1 << rOBPI_AUTO_INCREMENT) | 0x10);
    LDH_addr_A(rOBPI);
    LD_C(6 * PALETTE_SIZE);

loop:
    LD_A_hli;
    LDH_addr_A(rOBPD);
    DEC_C;
    IF_NZ goto loop;
    LD_HL(mBattleObjectPals);
    LD_DE(wOBPals1 + PALETTE_SIZE * 2);
    LD_BC(2 * PALETTE_SIZE);
    LD_A(BANK(wOBPals1));
    CALL(aFarCopyWRAM);
    RET;

}

void BattleObjectPals(void){
// INCLUDE "gfx/battle_anims/battle_anims.pal"

    return CGBCopyTwoPredefObjectPals();
}

void CGBCopyTwoPredefObjectPals(void){
//  //  unreferenced
    CALL(aCheckCGB);
    RET_Z ;
    LD_A((1 << rOBPI_AUTO_INCREMENT) | 0x10);
    LDH_addr_A(rOBPI);
    LD_A(PREDEFPAL_TRADE_TUBE);
    CALL(aGetPredefPal);
    CALL(aCGBCopyTwoPredefObjectPals_PushPalette);
    LD_A(PREDEFPAL_RB_GREENMON);
    CALL(aGetPredefPal);
    CALL(aCGBCopyTwoPredefObjectPals_PushPalette);
    RET;


PushPalette:
    LD_C(1 * PALETTE_SIZE);

loop:
    LD_A_hli;
    LDH_addr_A(rOBPD);
    DEC_C;
    IF_NZ goto loop;
    RET;

}

void v_GetMonPalettePointer(void){
    LD_L_A;
    LD_H(0);
    ADD_HL_HL;
    ADD_HL_HL;
    ADD_HL_HL;
    LD_BC(mPokemonPalettes);
    ADD_HL_BC;
    RET;

}

const char* v_GetMonPalettePointer_Conv(species_t a){
    // LD_L_A;
    // LD_H(0);
    // ADD_HL_HL;
    // ADD_HL_HL;
    // ADD_HL_HL;
    // LD_BC(mPokemonPalettes);
    // ADD_HL_BC;
    // RET;
    if(a == UNOWN) {
        return UnownPicPointers[UNOWN_A-1][0];
    }
    return PokemonPicPointers[a-1][0];
}

void GetMonNormalOrShinyPalettePointer(void){
    PUSH_BC;
    CALL(av_GetMonPalettePointer);
    POP_BC;
    PUSH_HL;
    CALL(aCheckShininess);
    POP_HL;
    RET_NC ;
    for(int rept = 0; rept < 4; rept++){
    INC_HL;
    }
    RET;

}

static uint16_t* GetCustomMonPalette(uint16_t* dest, species_t a, bool shiny) {
    for(size_t i = 0; i < 4; ++i) {
        if(PokemonCustomPals[i].id == a) {
            CopyBytes_Conv2(dest, PokemonCustomPals[i].pals + (shiny * 2), 2 * sizeof(uint16_t));
            return dest;
        }
    }
    CopyBytes_Conv2(dest, PokemonCustomPals[0].pals + (shiny * 2), 2 * sizeof(uint16_t));
    return dest;
}

uint16_t* GetMonNormalOrShinyPalettePointer_Conv(uint16_t* dest, species_t a, uint16_t bc){
    // PUSH_BC;
    // CALL(av_GetMonPalettePointer);
    // POP_BC;
    // PUSH_HL;
    // CALL(aCheckShininess);
    // POP_HL;
    // RET_NC ;
    if(!CheckShininess_Conv(bc)) {
    // for(int rept = 0; rept < 4; rept++){
    // INC_HL;
    // }
    // RET;
        if(v_GetMonPalettePointer_Conv(a) == NULL)
            return GetCustomMonPalette(dest, a, false);
        ExtractPaletteFromPNGAssetToBuffer(dest, v_GetMonPalettePointer_Conv(a));
        // First palette color should be ignored 
        dest[0] = dest[1];
        dest[1] = dest[2];
        return dest;
    }
    else {
        if(PokemonShinyPals[a] == NULL)
            return GetCustomMonPalette(dest, a, true);
        LoadPaletteAssetColorsToBuffer(dest, 4 * sizeof(uint16_t), PokemonShinyPals[a], 0, 2);
        return dest;
    }
}

void PushSGBPals(void){
    LD_A_addr(wJoypadDisable);
    PUSH_AF;
    SET_A(JOYPAD_DISABLE_SGB_TRANSFER_F);
    LD_addr_A(wJoypadDisable);
    CALL(av_PushSGBPals);
    POP_AF;
    LD_addr_A(wJoypadDisable);
    RET;

}

void v_PushSGBPals(void){
    LD_A_hl;
    AND_A(0x7);
    RET_Z ;
    LD_B_A;

loop:
    PUSH_BC;
    XOR_A_A;
    LDH_addr_A(rJOYP);
    LD_A(0x30);
    LDH_addr_A(rJOYP);
    LD_B(0x10);

loop2:
    LD_E(0x8);
    LD_A_hli;
    LD_D_A;

loop3:
    BIT_D(0);
    LD_A(0x10);
    IF_NZ goto okay;
    LD_A(0x20);

okay:
    LDH_addr_A(rJOYP);
    LD_A(0x30);
    LDH_addr_A(rJOYP);
    RR_D;
    DEC_E;
    IF_NZ goto loop3;
    DEC_B;
    IF_NZ goto loop2;
    LD_A(0x20);
    LDH_addr_A(rJOYP);
    LD_A(0x30);
    LDH_addr_A(rJOYP);
    CALL(aSGBDelayCycles);
    POP_BC;
    DEC_B;
    IF_NZ goto loop;
    RET;

}

void InitSGBBorder(void){
    CALL(aCheckCGB);
    RET_NZ ;

//  SGB/DMG only
    NOP;
    LD_A_addr(wJoypadDisable);
    PUSH_AF;
    SET_A(JOYPAD_DISABLE_SGB_TRANSFER_F);
    LD_addr_A(wJoypadDisable);

    XOR_A_A;
    LDH_addr_A(rJOYP);
    LDH_addr_A(hSGB);
    CALL(aPushSGBBorderPalsAndWait);
    IF_NC goto skip;
    LD_A(0x1);
    LDH_addr_A(hSGB);
    CALL(av_InitSGBBorderPals);
    CALL(aSGBBorder_PushBGPals);
    CALL(aSGBDelayCycles);
    CALL(aSGB_ClearVRAM);
    CALL(aPushSGBBorder);
    CALL(aSGBDelayCycles);
    CALL(aSGB_ClearVRAM);
    LD_HL(mMaskEnCancelPacket);
    CALL(av_PushSGBPals);


skip:
    POP_AF;
    LD_addr_A(wJoypadDisable);
    NOP;
    RET;

}

void InitCGBPals(void){
    CALL(aCheckCGB);
    RET_Z ;

//  CGB only
    LD_A(BANK(vTiles3));
    LDH_addr_A(rVBK);
    LD_HL(vTiles3);
    LD_BC(0x200 * LEN_2BPP_TILE);
    XOR_A_A;
    CALL(aByteFill);
    LD_A(BANK(vTiles0));
    LDH_addr_A(rVBK);
    LD_A(1 << rBGPI_AUTO_INCREMENT);
    LDH_addr_A(rBGPI);
    LD_C(4 * 8);

bgpals_loop:
    LD_A(LOW(PALRGB_WHITE));
    LDH_addr_A(rBGPD);
    LD_A(HIGH(PALRGB_WHITE));
    LDH_addr_A(rBGPD);
    DEC_C;
    IF_NZ goto bgpals_loop;
    LD_A(1 << rOBPI_AUTO_INCREMENT);
    LDH_addr_A(rOBPI);
    LD_C(4 * 8);

obpals_loop:
    LD_A(LOW(PALRGB_WHITE));
    LDH_addr_A(rOBPD);
    LD_A(HIGH(PALRGB_WHITE));
    LDH_addr_A(rOBPD);
    DEC_C;
    IF_NZ goto obpals_loop;
    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(BANK(wBGPals1));
    LDH_addr_A(rSVBK);
    LD_HL(wBGPals1);
    CALL(aInitCGBPals_LoadWhitePals);
    LD_HL(wBGPals2);
    CALL(aInitCGBPals_LoadWhitePals);
    POP_AF;
    LDH_addr_A(rSVBK);
    RET;


LoadWhitePals:
    LD_C(4 * 16);

loop:
    LD_A(LOW(PALRGB_WHITE));
    LD_hli_A;
    LD_A(HIGH(PALRGB_WHITE));
    LD_hli_A;
    DEC_C;
    IF_NZ goto loop;
    RET;

}

void v_InitSGBBorderPals(void){
    LD_HL(mv_InitSGBBorderPals_PacketPointerTable);
    LD_C(9);

loop:
    PUSH_BC;
    LD_A_hli;
    PUSH_HL;
    LD_H_hl;
    LD_L_A;
    CALL(av_PushSGBPals);
    POP_HL;
    INC_HL;
    POP_BC;
    DEC_C;
    IF_NZ goto loop;
    RET;


PacketPointerTable:
    //dw ['MaskEnFreezePacket'];
    //dw ['DataSndPacket1'];
    //dw ['DataSndPacket2'];
    //dw ['DataSndPacket3'];
    //dw ['DataSndPacket4'];
    //dw ['DataSndPacket5'];
    //dw ['DataSndPacket6'];
    //dw ['DataSndPacket7'];
    //dw ['DataSndPacket8'];

    return UpdateSGBBorder();
}

void UpdateSGBBorder(void){
//  //  unreferenced
    NOP;
    XOR_A_A;
    LDH_addr_A(rJOYP);
    LD_HL(mMaskEnFreezePacket);
    CALL(av_PushSGBPals);
    CALL(aPushSGBBorder);
    CALL(aSGBDelayCycles);
    CALL(aSGB_ClearVRAM);
    LD_HL(mMaskEnCancelPacket);
    CALL(av_PushSGBPals);
    NOP;
    RET;

}

void PushSGBBorder(void){
    CALL(aPushSGBBorder_LoadSGBBorderPointers);
    PUSH_DE;
    CALL(aSGBBorder_YetMorePalPushing);
    POP_HL;
    CALL(aSGBBorder_MorePalPushing);
    RET;


LoadSGBBorderPointers:
    LD_HL(mSGBBorderGFX);
    LD_DE(mSGBBorderMapAndPalettes);
    RET;

}

void SGB_ClearVRAM(void){
    LD_HL(VRAM_Begin);
    LD_BC(VRAM_End - VRAM_Begin);
    XOR_A_A;
    CALL(aByteFill);
    RET;

}

void PushSGBBorderPalsAndWait(void){
    LD_HL(mMltReq2Packet);
    CALL(av_PushSGBPals);
    CALL(aSGBDelayCycles);
    LDH_A_addr(rJOYP);
    AND_A(0x3);
    CP_A(0x3);
    IF_NZ goto carry;
    LD_A(0x20);
    LDH_addr_A(rJOYP);
    LDH_A_addr(rJOYP);
    LDH_A_addr(rJOYP);
    CALL(aSGBDelayCycles);
    CALL(aSGBDelayCycles);
    LD_A(0x30);
    LDH_addr_A(rJOYP);
    CALL(aSGBDelayCycles);
    CALL(aSGBDelayCycles);
    LD_A(0x10);
    LDH_addr_A(rJOYP);
    for(int rept = 0; rept < 6; rept++){
    LDH_A_addr(rJOYP);
    }
    CALL(aSGBDelayCycles);
    CALL(aSGBDelayCycles);
    LD_A(0x30);
    LDH_addr_A(rJOYP);
    LDH_A_addr(rJOYP);
    LDH_A_addr(rJOYP);
    LDH_A_addr(rJOYP);
    CALL(aSGBDelayCycles);
    CALL(aSGBDelayCycles);
    LDH_A_addr(rJOYP);
    AND_A(0x3);
    CP_A(0x3);
    IF_NZ goto carry;
    CALL(aPushSGBBorderPalsAndWait_FinalPush);
    AND_A_A;
    RET;


carry:
    CALL(aPushSGBBorderPalsAndWait_FinalPush);
    SCF;
    RET;


FinalPush:
    LD_HL(mMltReq1Packet);
    CALL(av_PushSGBPals);
    JP(mSGBDelayCycles);

}

void SGBBorder_PushBGPals(void){
    CALL(aDisableLCD);
    LD_A(0b11100100);
    LDH_addr_A(rBGP);
    LD_HL(mPredefPals);
    LD_DE(vTiles1);
    LD_BC(0x100 * LEN_2BPP_TILE);
    CALL(aCopyData);
    CALL(aDrawDefaultTiles);
    LD_A(LCDC_DEFAULT);
    LDH_addr_A(rLCDC);
    LD_HL(mPalTrnPacket);
    CALL(av_PushSGBPals);
    XOR_A_A;
    LDH_addr_A(rBGP);
    RET;

}

void SGBBorder_MorePalPushing(void){
    CALL(aDisableLCD);
    LD_A(0xe4);
    LDH_addr_A(rBGP);
    LD_DE(vTiles1);
    LD_BC((6 + SCREEN_WIDTH + 6) * 5 * 2);
    CALL(aCopyData);
    LD_B(SCREEN_HEIGHT);

loop:
    PUSH_BC;
    LD_BC(6 * 2);
    CALL(aCopyData);
    LD_BC(SCREEN_WIDTH * 2);
    CALL(aClearBytes);
    LD_BC(6 * 2);
    CALL(aCopyData);
    POP_BC;
    DEC_B;
    IF_NZ goto loop;
    LD_BC((6 + SCREEN_WIDTH + 6) * 5 * 2);
    CALL(aCopyData);
    LD_BC(0x100);
    CALL(aClearBytes);
    LD_BC(16 * PALETTE_SIZE);
    CALL(aCopyData);
    CALL(aDrawDefaultTiles);
    LD_A(LCDC_DEFAULT);
    LDH_addr_A(rLCDC);
    LD_HL(mPctTrnPacket);
    CALL(av_PushSGBPals);
    XOR_A_A;
    LDH_addr_A(rBGP);
    RET;

}

void SGBBorder_YetMorePalPushing(void){
    CALL(aDisableLCD);
    LD_A(0b11100100);
    LDH_addr_A(rBGP);
    LD_DE(vTiles1);
    LD_B(0x80);

loop:
    PUSH_BC;
    LD_BC(1 * LEN_2BPP_TILE);
    CALL(aCopyData);
    LD_BC(1 * LEN_2BPP_TILE);
    CALL(aClearBytes);
    POP_BC;
    DEC_B;
    IF_NZ goto loop;
    CALL(aDrawDefaultTiles);
    LD_A(LCDC_DEFAULT);
    LDH_addr_A(rLCDC);
    LD_HL(mChrTrnPacket);
    CALL(av_PushSGBPals);
    XOR_A_A;
    LDH_addr_A(rBGP);
    RET;

}

void CopyData(void){
//  copy bc bytes of data from hl to de

loop:
    LD_A_hli;
    LD_de_A;
    INC_DE;
    DEC_BC;
    LD_A_C;
    OR_A_B;
    IF_NZ goto loop;
    RET;

}

void ClearBytes(void){
//  clear bc bytes of data starting from de

loop:
    XOR_A_A;
    LD_de_A;
    INC_DE;
    DEC_BC;
    LD_A_C;
    OR_A_B;
    IF_NZ goto loop;
    RET;

}

//  clear bc bytes of data starting from de
void ClearBytes_Conv(uint8_t* de, size_t bc){
    for(size_t i = 0; i < bc; ++i) {
        // XOR_A_A;
        // LD_de_A;
        // INC_DE;
        de[i] = 0;
        // DEC_BC;
        // LD_A_C;
        // OR_A_B;
        // IF_NZ goto loop;
    }
    // RET;

}

void DrawDefaultTiles(void){
//  Draw 240 tiles (2/3 of the screen) from tiles in VRAM
    hlbgcoord(0, 0, vBGMap0);  // BG Map 0
    LD_DE(BG_MAP_WIDTH - SCREEN_WIDTH);
    LD_A(0x80);  // starting tile
    LD_C(12 + 1);

line:
    LD_B(20);

tile:
    LD_hli_A;
    INC_A;
    DEC_B;
    IF_NZ goto tile;
//  next line
    ADD_HL_DE;
    DEC_C;
    IF_NZ goto line;
    RET;

}

void SGBDelayCycles(void){
    LD_DE(7000);

wait:
    NOP;
    NOP;
    NOP;
    DEC_DE;
    LD_A_D;
    OR_A_E;
    IF_NZ goto wait;
    RET;

// INCLUDE "gfx/sgb/blk_packets.asm"
// INCLUDE "gfx/sgb/pal_packets.asm"
// INCLUDE "data/sgb_ctrl_packets.asm"

    // return PredefPals();
}

// void PredefPals(void){
//     //table_width ['PALETTE_SIZE', 'PredefPals']
// // INCLUDE "gfx/sgb/predef.pal"
//     //assert_table_length ['NUM_PREDEF_PALS']

//     return SGBBorderMapAndPalettes();
// }

// void SGBBorderMapAndPalettes(void){
// //  interleaved tile ids and palette ids, without the center 20x18 screen area
// // INCBIN "gfx/sgb/sgb_border.sgb.tilemap"
// //  four SGB palettes of 16 colors each
// // INCLUDE "gfx/sgb/sgb_border.pal"

//     return SGBBorderGFX();
// }

// void SGBBorderGFX(void){
// // INCBIN "gfx/sgb/sgb_border.2bpp"

//     return HPBarPals();
// }

// void HPBarPals(void){
// // INCLUDE "gfx/battle/hp_bar.pal"

//     return ExpBarPalette();
// }

const char HPBarPals[] = "gfx/battle/hp_bar.pal";
const char ExpBarPalette[] = "gfx/battle/exp_bar.pal";

// void ExpBarPalette(void){
// // INCLUDE "gfx/battle/exp_bar.pal"

// // INCLUDE "data/pokemon/palettes.asm"

// // INCLUDE "data/trainers/palettes.asm"

//     return LoadMapPals();
// }

void LoadMapPals(void){
    FARCALL(aLoadSpecialMapPalette);
    IF_C goto got_pals;

// Which palette group is based on whether we're outside or inside
    LD_A_addr(wEnvironment);
    AND_A(7);
    LD_E_A;
    LD_D(0);
    LD_HL(mEnvironmentColorsPointers);
    ADD_HL_DE;
    ADD_HL_DE;
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
// Futher refine by time of day
    LD_A_addr(wTimeOfDayPal);
    maskbits(NUM_DAYTIMES, 0);
    ADD_A_A;
    ADD_A_A;
    ADD_A_A;
    LD_E_A;
    LD_D(0);
    ADD_HL_DE;
    LD_E_L;
    LD_D_H;
    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(BANK(wBGPals1));
    LDH_addr_A(rSVBK);
    LD_HL(wBGPals1);
    LD_B(8);

outer_loop:
    LD_A_de;  // lookup index for TilesetBGPalette
    PUSH_DE;
    PUSH_HL;
    LD_L_A;
    LD_H(0);
    ADD_HL_HL;
    ADD_HL_HL;
    ADD_HL_HL;
    LD_DE(mTilesetBGPalette);
    ADD_HL_DE;
    LD_E_L;
    LD_D_H;
    POP_HL;
    LD_C(1 * PALETTE_SIZE);

inner_loop:
    LD_A_de;
    INC_DE;
    LD_hli_A;
    DEC_C;
    IF_NZ goto inner_loop;
    POP_DE;
    INC_DE;
    DEC_B;
    IF_NZ goto outer_loop;
    POP_AF;
    LDH_addr_A(rSVBK);


got_pals:
    LD_A_addr(wTimeOfDayPal);
    maskbits(NUM_DAYTIMES, 0);
    LD_BC(8 * PALETTE_SIZE);
    LD_HL(mMapObjectPals);
    CALL(aAddNTimes);
    LD_DE(wOBPals1);
    LD_BC(8 * PALETTE_SIZE);
    LD_A(BANK(wOBPals1));
    CALL(aFarCopyWRAM);

    LD_A_addr(wEnvironment);
    CP_A(TOWN);
    IF_Z goto outside;
    CP_A(ROUTE);
    RET_NZ ;

outside:
    LD_A_addr(wMapGroup);
    LD_L_A;
    LD_H(0);
    ADD_HL_HL;
    ADD_HL_HL;
    ADD_HL_HL;
    LD_DE(mRoofPals);
    ADD_HL_DE;
    LD_A_addr(wTimeOfDayPal);
    maskbits(NUM_DAYTIMES, 0);
    CP_A(NITE_F);
    IF_C goto morn_day;
    for(int rept = 0; rept < 4; rept++){
    INC_HL;
    }

morn_day:
    LD_DE(wBGPals1 + PALETTE_SIZE * PAL_BG_ROOF + PAL_COLOR_SIZE * 1);
    LD_BC(4);
    LD_A(BANK(wBGPals1));
    CALL(aFarCopyWRAM);
    RET;

// INCLUDE "data/maps/environment_colors.asm"

    // return PartyMenuBGMobilePalette();
}

const char PartyMenuBGMobilePalette[] = "gfx/stats/party_menu_bg_mobile.pal";
const char PartyMenuBGPalette[] = "gfx/stats/party_menu_bg.pal";
const char TilesetBGPalette[] = "gfx/tilesets/bg_tiles.pal";
const char MapObjectPals[] = "gfx/overworld/npc_sprites.pal";

// void RoofPals(void){
//     //table_width ['PAL_COLOR_SIZE * 2 * 2', 'RoofPals']
// // INCLUDE "gfx/tilesets/roofs.pal"
//     //assert_table_length ['NUM_MAP_GROUPS + 1']

//     return DiplomaPalettes();
// }
const uint16_t RoofPals[][4] = {
// group 0 (unused)
    [GROUP_NONE] = {
        rgb(21,21,21), rgb(11,11,11), // morn/day
        rgb(21,21,21), rgb(11,11,11), // nite
    },

// group 1 (Olivine)
    [MAPGROUP_OLIVINE] = {
        rgb(14,17,31), rgb( 7,11,15), // morn/day
        rgb( 9, 9,17), rgb( 5, 7,13), // nite
    },

// group 2 (Mahogany)
    [MAPGROUP_MAHOGANY] = {
        rgb(12,19, 0), rgb( 6,10, 0), // morn/day
        rgb( 6, 9, 7), rgb( 4, 5, 6), // nite
    },

// group 3 (dungeons)
    [MAPGROUP_DUNGEONS] = {
        rgb(21,21,21), rgb(11,11,11), // morn/day
        rgb(21,21,21), rgb(17, 8, 7), // nite
    },

// group 4 (Ecruteak)
    [MAPGROUP_ECRUTEAK] = {
        rgb(31,19, 0), rgb(27,10, 5), // morn/day
        rgb(15, 7, 2), rgb(11, 4, 2), // nite
    },

// group 5 (Blackthorn)
    [MAPGROUP_BLACKTHORN] = {
        rgb(11,10,16), rgb( 5, 6, 7), // morn/day
        rgb( 3, 4, 8), rgb( 0, 0, 0), // nite
    },

// group 6 (Cinnabar)
    [MAPGROUP_CINNABAR] = {
        rgb(31,10, 0), rgb(18, 6, 0), // morn/day
        rgb(18, 5, 9), rgb(17, 8, 7), // nite
    },

// group 7 (Cerulean)
    [MAPGROUP_CERULEAN] = {
        rgb(17,27,31), rgb( 5,15,31), // morn/day
        rgb( 7, 8,22), rgb( 7, 7,16), // nite
    },

// group 8 (Azalea)
    [MAPGROUP_AZALEA] = {
        rgb(22,20,10), rgb(17,14, 3), // morn/day
        rgb(11,11, 5), rgb(10, 9, 7), // nite
    },

// group 9 (Lake of Rage)
    [MAPGROUP_LAKE_OF_RAGE] = {
        rgb(31, 8, 4), rgb( 9, 9, 8), // morn/day
        rgb(18, 5, 9), rgb( 9, 9, 8), // nite
    },

// group 10 (Violet)
    [MAPGROUP_VIOLET] = {
        rgb(24,14,31), rgb(13, 7,21), // morn/day
        rgb(12, 3,18), rgb( 9, 3,15), // nite
    },

// group 11 (Goldenrod)
    [MAPGROUP_GOLDENROD] = {
        rgb(25,25, 0), rgb(20,17, 8),// morn/day
        rgb(12,12, 0), rgb(10, 9, 5),// nite
    },

// group 12 (Vermilion)
    [MAPGROUP_VERMILION] = {
        rgb(27,23, 1), rgb(23,11, 0), // morn/day
        rgb(15,11, 1), rgb(11,10, 1), // nite
    },

// group 13 (Pallet)
    [MAPGROUP_PALLET] = {
        rgb(27,28,31), rgb(17,19,22), // morn/day
        rgb(14,14,18), rgb(10, 9,13), // nite
    },

// group 14 (Pewter)
    [MAPGROUP_PEWTER] = {
        rgb(19,19,16), rgb(10,12,15), // morn/day
        rgb( 9, 9,11), rgb( 4, 5, 7), // nite
    },

// group 15 (Mount Moon Square)
    [MAPGROUP_FAST_SHIP] = {
        rgb(14,17,31), rgb( 7,11,15), // morn/day
        rgb( 9,13,19), rgb( 7, 7,16), // nite
    },

// group 16 (Indigo)
    [MAPGROUP_INDIGO] = {
        rgb(21,21,21), rgb(13,13,13), // morn/day
        rgb(11,11,19), rgb( 7, 7,12), // nite
    },

// group 17 (Fuchsia)
    [MAPGROUP_FUCHSIA] = {
        rgb(31,18,29), rgb(17,13,20), // morn/day
        rgb(14, 6,12), rgb(11, 3,10), // nite
    },

// group 18 (Lavender)
    [MAPGROUP_LAVENDER] = {
        rgb(23,15,31), rgb(16, 5,31), // morn/day
        rgb(12, 7,17), rgb( 8, 6,10), // nite
    },

// group 19 (Silver Cave)
    [MAPGROUP_SILVER] = {
        rgb(21,21,25), rgb(16,16,16), // morn/day
        rgb(13,13,13), rgb( 7, 7, 7), // nite
    },

// group 20 (Cable Club)
    [MAPGROUP_CABLE_CLUB] = {
        rgb(21,21,21), rgb(11,11,11), // morn/day
        rgb(21,21,21), rgb(11,11,11), // nite
    },

// group 21 (Celadon)
    [MAPGROUP_CELADON] = {
        rgb(19,31,15), rgb(31,22, 2), // morn/day
        rgb(12,13, 9), rgb( 9,12, 3), // nite
    },

// group 22 (Cianwood)
    [MAPGROUP_CIANWOOD] = {
        rgb(15,10,31), rgb( 7, 5,15), // morn/day
        rgb( 6, 5,17), rgb( 2, 2, 8), // nite
    },

// group 23 (Viridian)
    [MAPGROUP_VIRIDIAN] = {
        rgb(21,31, 7), rgb(13,25, 4), // morn/day
        rgb( 9,14, 8), rgb( 6,10, 4), // nite
    },

// group 24 (New Bark)
    [MAPGROUP_NEW_BARK] = {
        rgb(20,31,14), rgb(11,23, 5), // morn/day
        rgb( 9,13, 8), rgb( 6, 9, 4), // nite
    },

// group 25 (Saffron)
    [MAPGROUP_SAFFRON] = {
        rgb(31,26, 0), rgb(31,15, 0), // morn/day
        rgb(13,13, 1), rgb( 8, 8, 1), // nite
    },

// group 26 (Cherrygrove)
    [MAPGROUP_CHERRYGROVE] = {
        rgb(31,14,28), rgb(31, 5,21), // morn/day
        rgb(14, 7,17), rgb(13, 0, 8), // nite
    },
};
static_assert(lengthof(RoofPals) == NUM_MAP_GROUPS + 1, "");

const char DiplomaPalettes[] = "gfx/diploma/diploma.pal";
const char PartyMenuOBPals[] = "gfx/stats/party_menu_ob.pal";
//  //  unreferenced
const char UnusedBattleObjectPals[] = "gfx/battle_anims/unused_battle_anims.pal";
const char UnusedGSTitleBGPals[] = "gfx/title/unused_gs_bg.pal";
const char UnusedGSTitleOBPals[] = "gfx/title/unused_gs_fg.pal";

const char MalePokegearPals[] = "gfx/pokegear/pokegear.pal";
const char FemalePokegearPals[] = "gfx/pokegear/pokegear_f.pal";
const char BetaPokerPals[] = "gfx/beta_poker/beta_poker.pal";
const char SlotMachinePals[] = "gfx/slots/slots.pal";
