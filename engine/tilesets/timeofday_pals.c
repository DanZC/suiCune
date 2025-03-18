#include "../../constants.h"
#include "timeofday_pals.h"
#include "../../home/tilemap.h"
#include "../../home/delay.h"
#include "../../home/time.h"
#include "../../home/palettes.h"

#define dc(_0, _1, _2, _3) (((_0) << 6) | ((_1) << 4) | ((_2) << 2) | (_3))

void DummyPredef35(void){
    return DummyPredef36();
}

void DummyPredef36(void){
    RET;

}

void UpdateTimeOfDayPal(void){
    // CALL(aUpdateTime);
    UpdateTime_Conv();
    // LD_A_addr(wTimeOfDay);
    // LD_addr_A(wCurTimeOfDay);
    wram->wCurTimeOfDay = wram->wTimeOfDay;
    // CALL(aGetTimePalette);
    // LD_addr_A(wTimeOfDayPal);
    wram->wTimeOfDayPal = GetTimePalette_Conv();
    // RET;
}

void v_TimeOfDayPals(void){
//  return carry if pals are changed

//  forced pals?
    LD_HL(wTimeOfDayPalFlags);
    BIT_hl(7);
    IF_NZ goto dontchange;

//  do we need to bother updating?
    LD_A_addr(wTimeOfDay);
    LD_HL(wCurTimeOfDay);
    CP_A_hl;
    IF_Z goto dontchange;

//  if so, the time of day has changed
    LD_A_addr(wTimeOfDay);
    LD_addr_A(wCurTimeOfDay);

//  get palette id
    CALL(aGetTimePalette);

//  same palette as before?
    LD_HL(wTimeOfDayPal);
    CP_A_hl;
    IF_Z goto dontchange;

//  update palette id
    LD_addr_A(wTimeOfDayPal);

//  save bg palette 7
    LD_HL(wBGPals1 + PALETTE_SIZE * PAL_BG_TEXT);

//  save wram bank
    LDH_A_addr(rSVBK);
    LD_B_A;

    LD_A(BANK(wBGPals1));
    LDH_addr_A(rSVBK);

//  push palette
    LD_C(NUM_PAL_COLORS);

push:
    LD_D_hl;
    INC_HL;
    LD_E_hl;
    INC_HL;
    PUSH_DE;
    DEC_C;
    IF_NZ goto push;

//  restore wram bank
    LD_A_B;
    LDH_addr_A(rSVBK);

//  update sgb pals
    LD_B(SCGB_MAPPALS);
    CALL(aGetSGBLayout);

//  restore bg palette 7
    LD_HL(wOBPals1 - 1);  // last byte in wBGPals1

//  save wram bank
    LDH_A_addr(rSVBK);
    LD_D_A;

    LD_A(BANK(wOBPals1));
    LDH_addr_A(rSVBK);

//  pop palette
    LD_E(NUM_PAL_COLORS);

pop:
    POP_BC;
    LD_hl_C;
    DEC_HL;
    LD_hl_B;
    DEC_HL;
    DEC_E;
    IF_NZ goto pop;

//  restore wram bank
    LD_A_D;
    LDH_addr_A(rSVBK);

//  update palettes
    CALL(av_UpdateTimePals);
    CALL(aDelayFrame);

//  successful change
    SCF;
    RET;


dontchange:
//  no change occurred
    AND_A_A;
    RET;

}

bool v_TimeOfDayPals_Conv(void){
//  return carry if pals are changed

//  forced pals?
    // LD_HL(wTimeOfDayPalFlags);
    // BIT_hl(7);
    // IF_NZ goto dontchange;
    if(bit_test(wram->wTimeOfDayPalFlags, 7))
        return false;

//  do we need to bother updating?
    // LD_A_addr(wTimeOfDay);
    // LD_HL(wCurTimeOfDay);
    // CP_A_hl;
    // IF_Z goto dontchange;
    if(wram->wTimeOfDay == wram->wCurTimeOfDay)
        return false;

//  if so, the time of day has changed
    // LD_A_addr(wTimeOfDay);
    // LD_addr_A(wCurTimeOfDay);
    wram->wCurTimeOfDay = wram->wTimeOfDay;

//  get palette id
    // CALL(aGetTimePalette);
    uint8_t a = GetTimePalette_Conv();

//  same palette as before?
    // LD_HL(wTimeOfDayPal);
    // CP_A_hl;
    // IF_Z goto dontchange;
    if(a == wram->wTimeOfDayPal)
        return false;

//  update palette id
    // LD_addr_A(wTimeOfDayPal);
    wram->wTimeOfDayPal = a;

//  save bg palette 7
    // LD_HL(wBGPals1 + PALETTE_SIZE * PAL_BG_TEXT);
    uint16_t* bgpal = (uint16_t*)(wram->wBGPals1 + PALETTE_SIZE * PAL_BG_TEXT);

//  save wram bank
    // LDH_A_addr(rSVBK);
    // LD_B_A;

    // LD_A(BANK(wBGPals1));
    // LDH_addr_A(rSVBK);
    uint16_t palStack[NUM_PAL_COLORS];

//  push palette
    // LD_C(NUM_PAL_COLORS);

    for(uint8_t i = 0; i < NUM_PAL_COLORS; ++i) {
    // push:
        // LD_D_hl;
        // INC_HL;
        // LD_E_hl;
        // INC_HL;
        // PUSH_DE;
        palStack[i] = bgpal[i];
        // DEC_C;
        // IF_NZ goto push;
    }

//  restore wram bank
    // LD_A_B;
    // LDH_addr_A(rSVBK);

//  update sgb pals
    // LD_B(SCGB_MAPPALS);
    // CALL(aGetSGBLayout);
    GetSGBLayout_Conv(SCGB_MAPPALS);

//  restore bg palette 7
    // LD_HL(wOBPals1 - 1);  // last byte in wBGPals1
    uint8_t* hl = wram->wOBPals1 - 1;

//  save wram bank
    // LDH_A_addr(rSVBK);
    // LD_D_A;

    // LD_A(BANK(wOBPals1));
    // LDH_addr_A(rSVBK);

//  pop palette
    // LD_E(NUM_PAL_COLORS);

    for(uint8_t i = NUM_PAL_COLORS; i > 0; --i) {
    // pop:
        // POP_BC;
        uint16_t bc = palStack[i - 1];
        // LD_hl_C;
        // DEC_HL;
        *(hl--) = LOW(bc);
        // LD_hl_B;
        // DEC_HL;
        *(hl--) = HIGH(bc);
        // DEC_E;
        // IF_NZ goto pop;
    }

//  restore wram bank
    // LD_A_D;
    // LDH_addr_A(rSVBK);

//  update palettes
    // CALL(av_UpdateTimePals);
    v_UpdateTimePals();
    // CALL(aDelayFrame);
    DelayFrame();

//  successful change
    // SCF;
    // RET;
    return true;

// dontchange:
//  no change occurred
    // AND_A_A;
    // RET;
}

void v_UpdateTimePals(void){
    // LD_C(0x9);  // normal
    // CALL(aGetTimePalFade);
    const uint8_t* hl = GetTimePalFade_Conv(0x9);
    // CALL(aDmgToCgbTimePals);
    DmgToCgbTimePals_Conv(hl);
    // RET;
}

void FadeInPalettes(void){
    // LD_C(0x12);
    // CALL(aGetTimePalFade);
    const uint8_t* hl = GetTimePalFade_Conv(0x12);
    // LD_B(0x4);
    // CALL(aConvertTimePalsDecHL);
    ConvertTimePalsDecHL_Conv(hl, 0x4);
    // RET;
}

void FadeOutPalettes(void){
    // CALL(aFillWhiteBGColor);
    FillWhiteBGColor();
    // LD_C(0x9);
    // CALL(aGetTimePalFade);
    const uint8_t* hl = GetTimePalFade_Conv(0x9);
    // LD_B(0x4);
    // CALL(aConvertTimePalsIncHL);
    ConvertTimePalsIncHL_Conv(hl, 0x4);
    // RET;

}

void BattleTowerFade(void){
    // CALL(aFillWhiteBGColor);
    FillWhiteBGColor();
    // LD_C(0x9);
    // CALL(aGetTimePalFade);
    const uint8_t* hl = GetTimePalFade_Conv(0x9);
    // LD_B(0x4);
    uint8_t b = 0x4;

    do {
    // loop:
        // CALL(aDmgToCgbTimePals);
        DmgToCgbTimePals_Conv(hl);
        // INC_HL;
        // INC_HL;
        // INC_HL;
        hl += 3;
        // LD_C(0x7);
        // CALL(aDelayFrames);
        DelayFrames_Conv(0x7);
        // DEC_B;
        // IF_NZ goto loop;
    } while(--b != 0);
    // RET;
}

void FadeInQuickly(void){
    // LD_C(0x0);
    // CALL(aGetTimePalFade);
    const uint8_t* hl = GetTimePalFade_Conv(0x0);
    // LD_B(0x4);
    // CALL(aConvertTimePalsIncHL);
    ConvertTimePalsIncHL_Conv(hl, 0x4);
    // RET;
}

void FadeBlackQuickly(void){
    // LD_C(0x9);
    // CALL(aGetTimePalFade);
    const uint8_t* hl = GetTimePalFade_Conv(0x9);
    // LD_B(0x4);
    // CALL(aConvertTimePalsDecHL);
    ConvertTimePalsDecHL_Conv(hl, 0x4);
    // RET;
}

void FillWhiteBGColor(void){
    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    // LD_A(BANK(wBGPals1));
    // LDH_addr_A(rSVBK);

    // LD_HL(wBGPals1);
    // LD_A_hli;
    // LD_E_A;
    // LD_A_hli;
    // LD_D_A;
    // LD_HL(wBGPals1 + 1 * PALETTE_SIZE);
    uint8_t* hl = wram->wBGPals1 + 1 * PALETTE_SIZE;
    // LD_C(6);
    uint8_t c = 6;

    do {
    // loop:
        // LD_A_E;
        // LD_hli_A;
        *(hl++) = wram->wBGPals1[0];
        // LD_A_D;
        // LD_hli_A;
        *(hl++) = wram->wBGPals1[1];
        // for(int rept = 0; rept < 6; rept++){
        // INC_HL;
        // }
        hl += 6;
        // DEC_C;
        // IF_NZ goto loop;
    } while(--c != 0);

    // POP_AF;
    // LDH_addr_A(rSVBK);
    // RET;
}

void ReplaceTimeOfDayPals(void){
    LD_HL(mReplaceTimeOfDayPals_BrightnessLevels);
    LD_A_addr(wMapTimeOfDay);
    CP_A(PALETTE_DARK);
    IF_Z goto NeedsFlash;
    maskbits(NUM_MAP_PALETTES, 0);
    ADD_A_L;
    LD_L_A;
    LD_A(0);
    ADC_A_H;
    LD_H_A;
    LD_A_hl;
    LD_addr_A(wTimeOfDayPalset);
    RET;


NeedsFlash:
    LD_A_addr(wStatusFlags);
    BIT_A(STATUSFLAGS_FLASH_F);
    IF_NZ goto UsedFlash;
    LD_A(DARKNESS_PALSET);
    LD_addr_A(wTimeOfDayPalset);
    RET;


UsedFlash:
    LD_A((NITE_F << 6) | (NITE_F << 4) | (NITE_F << 2) | NITE_F);
    LD_addr_A(wTimeOfDayPalset);
    RET;


BrightnessLevels:
//  actual palettes used when time is
//  DARKNESS_F, NITE_F, DAY_F, MORN_F
    //dc ['DARKNESS_F', 'NITE_F', 'DAY_F', 'MORN_F']  // PALETTE_AUTO
    //dc ['DAY_F', 'DAY_F', 'DAY_F', 'DAY_F']  // PALETTE_DAY
    //dc ['NITE_F', 'NITE_F', 'NITE_F', 'NITE_F']  // PALETTE_NITE
    //dc ['MORN_F', 'MORN_F', 'MORN_F', 'MORN_F']  // PALETTE_MORN
    //dc ['DARKNESS_F', 'DARKNESS_F', 'DARKNESS_F', 'DARKNESS_F']  // PALETTE_DARK
    //dc ['DARKNESS_F', 'NITE_F', 'DAY_F', 'MORN_F']
    //dc ['DARKNESS_F', 'NITE_F', 'DAY_F', 'MORN_F']
    //dc ['DARKNESS_F', 'NITE_F', 'DAY_F', 'MORN_F']

    return GetTimePalette();
}

void ReplaceTimeOfDayPals_Conv(void){
    static const uint8_t BrightnessLevels[] = {
    //  actual palettes used when time is
    //  DARKNESS_F, NITE_F, DAY_F, MORN_F
        dc(DARKNESS_F, NITE_F, DAY_F, MORN_F),  // PALETTE_AUTO
        dc(DAY_F, DAY_F, DAY_F, DAY_F),  // PALETTE_DAY
        dc(NITE_F, NITE_F, NITE_F, NITE_F),  // PALETTE_NITE
        dc(MORN_F, MORN_F, MORN_F, MORN_F),  // PALETTE_MORN
        dc(DARKNESS_F, DARKNESS_F, DARKNESS_F, DARKNESS_F),  // PALETTE_DARK
        dc(DARKNESS_F, NITE_F, DAY_F, MORN_F),
        dc(DARKNESS_F, NITE_F, DAY_F, MORN_F),
        dc(DARKNESS_F, NITE_F, DAY_F, MORN_F),
    };
    // LD_HL(mReplaceTimeOfDayPals_BrightnessLevels);
    // LD_A_addr(wMapTimeOfDay);
    // CP_A(PALETTE_DARK);
    // IF_Z goto NeedsFlash;
    if(wram->wMapTimeOfDay == PALETTE_DARK) {
    // NeedsFlash:
        // LD_A_addr(wStatusFlags);
        // BIT_A(STATUSFLAGS_FLASH_F);
        // IF_NZ goto UsedFlash;
        if(bit_test(wram->wStatusFlags, STATUSFLAGS_FLASH_F)) {
        // UsedFlash:
            // LD_A((NITE_F << 6) | (NITE_F << 4) | (NITE_F << 2) | NITE_F);
            // LD_addr_A(wTimeOfDayPalset);
            wram->wTimeOfDayPalset = (NITE_F << 6) | (NITE_F << 4) | (NITE_F << 2) | NITE_F;
            // RET;
            return;
        }
        else {
            // LD_A(DARKNESS_PALSET);
            // LD_addr_A(wTimeOfDayPalset);
            wram->wTimeOfDayPalset = DARKNESS_PALSET;
            // RET;
            return;
        }
    }
    // maskbits(NUM_MAP_PALETTES, 0);
    // ADD_A_L;
    // LD_L_A;
    // LD_A(0);
    // ADC_A_H;
    // LD_H_A;
    // LD_A_hl;
    // LD_addr_A(wTimeOfDayPalset);
    wram->wTimeOfDayPalset = BrightnessLevels[wram->wMapTimeOfDay & 7];
    // RET;
    return;
}

void GetTimePalette(void){
    //jumptable ['.TimePalettes', 'wTimeOfDay']


TimePalettes:
    //dw ['.MorningPalette'];  // MORN_F
    //dw ['.DayPalette'];  // DAY_F
    //dw ['.NitePalette'];  // NITE_F
    //dw ['.DarknessPalette'];  // DARKNESS_F


MorningPalette:
    LD_A_addr(wTimeOfDayPalset);
    AND_A(0b00000011);
    RET;


DayPalette:
    LD_A_addr(wTimeOfDayPalset);
    AND_A(0b00001100);
    SRL_A;
    SRL_A;
    RET;


NitePalette:
    LD_A_addr(wTimeOfDayPalset);
    AND_A(0b00110000);
    SWAP_A;
    RET;


DarknessPalette:
    LD_A_addr(wTimeOfDayPalset);
    AND_A(0b11000000);
    RLCA;
    RLCA;
    RET;

}

uint8_t GetTimePalette_Conv(void){
    //jumptable ['.TimePalettes', 'wTimeOfDay']

// TimePalettes:
    switch(wram->wTimeOfDay & 3) {
        //dw ['.MorningPalette'];  // MORN_F
        case MORN_F:
        // MorningPalette:
            // LD_A_addr(wTimeOfDayPalset);
            // AND_A(0b00000011);
            // RET;
            return wram->wTimeOfDayPalset & 0b00000011;
        //dw ['.DayPalette'];  // DAY_F
        case DAY_F:
        // DayPalette:
            // LD_A_addr(wTimeOfDayPalset);
            // AND_A(0b00001100);
            // SRL_A;
            // SRL_A;
            // RET;
            return (wram->wTimeOfDayPalset & 0b00001100) >> 2;
        //dw ['.NitePalette'];  // NITE_F
        case NITE_F:
        // NitePalette:
            // LD_A_addr(wTimeOfDayPalset);
            // AND_A(0b00110000);
            // SWAP_A;
            // RET;
            return (wram->wTimeOfDayPalset & 0b00110000) >> 4;
        //dw ['.DarknessPalette'];  // DARKNESS_F
        case DARKNESS_F:
        // DarknessPalette:
            // LD_A_addr(wTimeOfDayPalset);
            // AND_A(0b11000000);
            // RLCA;
            // RLCA;
            // RET;
            return (wram->wTimeOfDayPalset & 0b11000000) >> 6;
        default:
            return 0xff;
    }
}

void DmgToCgbTimePals(void){
    PUSH_HL;
    PUSH_DE;
    LD_A_hli;
    CALL(aDmgToCgbBGPals);
    LD_A_hli;
    LD_E_A;
    LD_A_hli;
    LD_D_A;
    CALL(aDmgToCgbObjPals);
    POP_DE;
    POP_HL;
    RET;

}

void DmgToCgbTimePals_Conv(const uint8_t* hl){
    // PUSH_HL;
    // PUSH_DE;
    // LD_A_hli;
    // CALL(aDmgToCgbBGPals);
    DmgToCgbBGPals_Conv(hl[0]);
    // LD_A_hli;
    // LD_E_A;
    // LD_A_hli;
    // LD_D_A;
    // CALL(aDmgToCgbObjPals);
    DmgToCgbObjPals_Conv(hl[2], hl[1]);
    // POP_DE;
    // POP_HL;
    // RET;
}

void ConvertTimePalsIncHL(void){

loop:
    CALL(aDmgToCgbTimePals);
    INC_HL;
    INC_HL;
    INC_HL;
    LD_C(2);
    CALL(aDelayFrames);
    DEC_B;
    IF_NZ goto loop;
    RET;

}

void ConvertTimePalsIncHL_Conv(const uint8_t* hl, uint8_t b){
    do {
    // loop:
        // CALL(aDmgToCgbTimePals);
        DmgToCgbTimePals_Conv(hl);
        // INC_HL;
        // INC_HL;
        // INC_HL;
        hl += 3;
        // LD_C(2);
        // CALL(aDelayFrames);
        DelayFrames_Conv(2);
        // DEC_B;
        // IF_NZ goto loop;
    } while(--b != 0);
    // RET;
}

void ConvertTimePalsDecHL(void){

loop:
    CALL(aDmgToCgbTimePals);
    DEC_HL;
    DEC_HL;
    DEC_HL;
    LD_C(2);
    CALL(aDelayFrames);
    DEC_B;
    IF_NZ goto loop;
    RET;

}

void ConvertTimePalsDecHL_Conv(const uint8_t* hl, uint8_t b){
    do {
    // loop:
        // CALL(aDmgToCgbTimePals);
        DmgToCgbTimePals_Conv(hl);
        // DEC_HL;
        // DEC_HL;
        // DEC_HL;
        hl -= 3;
        // LD_C(2);
        // CALL(aDelayFrames);
        DelayFrames_Conv(2);
        // DEC_B;
        // IF_NZ goto loop;
    } while(--b != 0);
    // RET;
}

void GetTimePalFade(void){
//  check cgb
    LDH_A_addr(hCGB);
    AND_A_A;
    IF_NZ goto cgb;

//  else: dmg

//  index
    LD_A_addr(wTimeOfDayPal);
    AND_A(0b11);

//  get fade table
    PUSH_BC;
    LD_C_A;
    LD_B(0);
    LD_HL(mGetTimePalFade_dmgfades);
    ADD_HL_BC;
    ADD_HL_BC;
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    POP_BC;

//  get place in fade table
    LD_B(0);
    ADD_HL_BC;
    RET;


cgb:
    LD_HL(mGetTimePalFade_cgbfade);
    LD_B(0);
    ADD_HL_BC;
    RET;


//dmgfades:
    //dw ['.morn'];
    //dw ['.day'];
    //dw ['.nite'];
    //dw ['.darkness'];


//morn:
    //dc ['3', '3', '3', '3', '3', '3', '3', '3', '3', '3', '3', '3']
    //dc ['3', '3', '3', '2', '3', '3', '3', '2', '3', '3', '3', '2']
    //dc ['3', '3', '2', '1', '3', '2', '1', '0', '3', '2', '1', '0']
    //dc ['3', '2', '1', '0', '3', '1', '0', '0', '3', '1', '0', '0']
    //dc ['2', '1', '0', '0', '2', '0', '0', '0', '2', '0', '0', '0']
    //dc ['1', '0', '0', '0', '1', '0', '0', '0', '1', '0', '0', '0']
    //dc ['0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0']


//day:
    //dc ['3', '3', '3', '3', '3', '3', '3', '3', '3', '3', '3', '3']
    //dc ['3', '3', '3', '2', '3', '3', '3', '2', '3', '3', '3', '2']
    //dc ['3', '3', '2', '1', '3', '2', '1', '0', '3', '2', '1', '0']
    //dc ['3', '2', '1', '0', '3', '1', '0', '0', '3', '1', '0', '0']
    //dc ['2', '1', '0', '0', '2', '0', '0', '0', '2', '0', '0', '0']
    //dc ['1', '0', '0', '0', '1', '0', '0', '0', '1', '0', '0', '0']
    //dc ['0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0']


//nite:
    //dc ['3', '3', '3', '3', '3', '3', '3', '3', '3', '3', '3', '3']
    //dc ['3', '3', '3', '2', '3', '3', '3', '2', '3', '3', '3', '2']
    //dc ['3', '3', '2', '1', '3', '2', '1', '0', '3', '2', '1', '0']
    //dc ['3', '2', '2', '1', '3', '1', '0', '0', '3', '1', '0', '0']
    //dc ['2', '1', '0', '0', '2', '0', '0', '0', '2', '0', '0', '0']
    //dc ['1', '0', '0', '0', '1', '0', '0', '0', '1', '0', '0', '0']
    //dc ['0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0']


//darkness:
    //dc ['3', '3', '3', '3', '3', '3', '3', '3', '3', '3', '3', '3']
    //dc ['3', '3', '3', '2', '3', '3', '3', '2', '3', '3', '3', '3']
    //dc ['3', '3', '3', '2', '3', '2', '1', '0', '3', '3', '3', '3']
    //dc ['3', '3', '3', '1', '3', '1', '0', '0', '3', '3', '3', '3']
    //dc ['3', '3', '3', '1', '2', '0', '0', '0', '3', '3', '3', '3']
    //dc ['0', '0', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0']
    //dc ['0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0']


//cgbfade:
    //dc ['3', '3', '3', '3', '3', '3', '3', '3', '3', '3', '3', '3']
    //dc ['3', '3', '3', '2', '3', '3', '3', '2', '3', '3', '3', '2']
    //dc ['3', '3', '2', '1', '3', '3', '2', '1', '3', '3', '2', '1']
    //dc ['3', '2', '1', '0', '3', '2', '1', '0', '3', '2', '1', '0']
    //dc ['2', '1', '0', '0', '2', '1', '0', '0', '2', '1', '0', '0']
    //dc ['1', '0', '0', '0', '1', '0', '0', '0', '1', '0', '0', '0']
    //dc ['0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0']

}

const uint8_t* GetTimePalFade_Conv(uint8_t c){
    static const uint8_t cgbfade[] = {
        dc(3, 3, 3, 3), dc(3, 3, 3, 3), dc(3, 3, 3, 3),
        dc(3, 3, 3, 2), dc(3, 3, 3, 2), dc(3, 3, 3, 2),
        dc(3, 3, 2, 1), dc(3, 3, 2, 1), dc(3, 3, 2, 1),
        dc(3, 2, 1, 0), dc(3, 2, 1, 0), dc(3, 2, 1, 0),
        dc(2, 1, 0, 0), dc(2, 1, 0, 0), dc(2, 1, 0, 0),
        dc(1, 0, 0, 0), dc(1, 0, 0, 0), dc(1, 0, 0, 0),
        dc(0, 0, 0, 0), dc(0, 0, 0, 0), dc(0, 0, 0, 0),
    };

    static const uint8_t morn[] = {
        dc(3, 3, 3, 3), dc(3, 3, 3, 3), dc(3, 3, 3, 3),
        dc(3, 3, 3, 2), dc(3, 3, 3, 2), dc(3, 3, 3, 2),
        dc(3, 3, 2, 1), dc(3, 2, 1, 0), dc(3, 2, 1, 0),
        dc(3, 2, 1, 0), dc(3, 1, 0, 0), dc(3, 1, 0, 0),
        dc(2, 1, 0, 0), dc(2, 0, 0, 0), dc(2, 0, 0, 0),
        dc(1, 0, 0, 0), dc(1, 0, 0, 0), dc(1, 0, 0, 0),
        dc(0, 0, 0, 0), dc(0, 0, 0, 0), dc(0, 0, 0, 0),
    };

    static const uint8_t day[] = {
        dc(3, 3, 3, 3), dc(3, 3, 3, 3), dc(3, 3, 3, 3),
        dc(3, 3, 3, 2), dc(3, 3, 3, 2), dc(3, 3, 3, 2),
        dc(3, 3, 2, 1), dc(3, 2, 1, 0), dc(3, 2, 1, 0),
        dc(3, 2, 1, 0), dc(3, 1, 0, 0), dc(3, 1, 0, 0),
        dc(2, 1, 0, 0), dc(2, 0, 0, 0), dc(2, 0, 0, 0),
        dc(1, 0, 0, 0), dc(1, 0, 0, 0), dc(1, 0, 0, 0),
        dc(0, 0, 0, 0), dc(0, 0, 0, 0), dc(0, 0, 0, 0),
    };

    static const uint8_t nite[] = {
        dc(3, 3, 3, 3), dc(3, 3, 3, 3), dc(3, 3, 3, 3),
        dc(3, 3, 3, 2), dc(3, 3, 3, 2), dc(3, 3, 3, 2),
        dc(3, 3, 2, 1), dc(3, 2, 1, 0), dc(3, 2, 1, 0),
        dc(3, 2, 2, 1), dc(3, 1, 0, 0), dc(3, 1, 0, 0),
        dc(2, 1, 0, 0), dc(2, 0, 0, 0), dc(2, 0, 0, 0),
        dc(1, 0, 0, 0), dc(1, 0, 0, 0), dc(1, 0, 0, 0),
        dc(0, 0, 0, 0), dc(0, 0, 0, 0), dc(0, 0, 0, 0),
    };

    static const uint8_t darkness[] = {
        dc(3, 3, 3, 3), dc(3, 3, 3, 3), dc(3, 3, 3, 3),
        dc(3, 3, 3, 2), dc(3, 3, 3, 2), dc(3, 3, 3, 3),
        dc(3, 3, 3, 2), dc(3, 2, 1, 0), dc(3, 3, 3, 3),
        dc(3, 3, 3, 1), dc(3, 1, 0, 0), dc(3, 3, 3, 3),
        dc(3, 3, 3, 1), dc(2, 0, 0, 0), dc(3, 3, 3, 3),
        dc(0, 0, 0, 0), dc(1, 0, 0, 0), dc(0, 0, 0, 0),
        dc(0, 0, 0, 0), dc(0, 0, 0, 0), dc(0, 0, 0, 0),
    };

    static const uint8_t* dmgfades[] = {
        morn,
        day,
        nite,
        darkness,
    };

//  check cgb
    // LDH_A_addr(hCGB);
    // AND_A_A;
    // IF_NZ goto cgb;
    if(hram->hCGB != 0) {
    // cgb:
        // LD_HL(mGetTimePalFade_cgbfade);
        // LD_B(0);
        // ADD_HL_BC;
        // RET;
        return cgbfade + c;
    }

//  else: dmg

//  index
    // LD_A_addr(wTimeOfDayPal);
    // AND_A(0b11);
    uint8_t a = wram->wTimeOfDayPal & 0b11;

//  get fade table
    // PUSH_BC;
    // LD_C_A;
    // LD_B(0);
    // LD_HL(mGetTimePalFade_dmgfades);
    // ADD_HL_BC;
    // ADD_HL_BC;
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // POP_BC;
    const uint8_t* hl = dmgfades[a];

//  get place in fade table
    // LD_B(0);
    // ADD_HL_BC;
    // RET;
    return hl + c;
}
