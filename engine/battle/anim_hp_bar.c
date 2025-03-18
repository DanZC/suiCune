#include "../../constants.h"
#include "anim_hp_bar.h"
#include "../../home/delay.h"
#include "../../home/print_text.h"
#include "../../home/pokemon.h"
#include "../../home/tilemap.h"
#include "../pokemon/health.h"
#include "../gfx/color.h"

static bool v_AnimateHPBar_IsMaximumMoreThan48Pixels(void){
    // LD_A_addr(wCurHPAnimMaxHP + 1);
    // AND_A_A;
    // IF_NZ goto player;
    // LD_A_addr(wCurHPAnimMaxHP);
    // CP_A(HP_BAR_LENGTH_PX);
    // IF_NC goto player;
    if(wram->wCurHPAnimMaxHP >= HP_BAR_LENGTH_PX) {
    // player:
        // SCF;
        // RET;
        return true;
    }
    // AND_A_A;
    // RET;
    return false;
}

static uint16_t v_AnimateHPBar_ComputePixels(void){
    // PUSH_HL;
    // LD_HL(wCurHPAnimMaxHP);
    // LD_A_hli;
    // LD_E_A;
    // LD_A_hli;
    // LD_D_A;
    // LD_A_hli;
    // LD_C_A;
    // LD_A_hli;
    // LD_B_A;
    // POP_HL;
    // CALL(aComputeHPBarPixels);
    // LD_A_E;
    // LD_addr_A(wCurHPBarPixels);
    wram->wCurHPBarPixels = ComputeHPBarPixels_Conv(wram->wCurHPAnimOldHP, wram->wCurHPAnimMaxHP);

    // LD_A_addr(wCurHPAnimNewHP);
    // LD_C_A;
    // LD_A_addr(wCurHPAnimNewHP + 1);
    // LD_B_A;
    // LD_A_addr(wCurHPAnimMaxHP);
    // LD_E_A;
    // LD_A_addr(wCurHPAnimMaxHP + 1);
    // LD_D_A;
    // CALL(aComputeHPBarPixels);
    // LD_A_E;
    // LD_addr_A(wNewHPBarPixels);
    wram->wNewHPBarPixels = ComputeHPBarPixels_Conv(wram->wCurHPAnimNewHP, wram->wCurHPAnimMaxHP);

    // PUSH_HL;
    // LD_HL(wCurHPAnimOldHP);
    // LD_A_hli;
    // LD_C_A;
    // LD_A_hli;
    // LD_B_A;
    uint16_t bc = wram->wCurHPAnimOldHP;
    // LD_A_hli;
    // LD_E_A;
    // LD_A_hli;
    // LD_D_A;
    uint16_t de = wram->wCurHPAnimNewHP;
    // POP_HL;
    // LD_A_E;
    // SUB_A_C;
    // LD_E_A;
    // LD_A_D;
    // SBC_A_B;
    // LD_D_A;
    // IF_C goto negative;
    if(de < bc) {
    // negative:
        // LD_A_addr(wCurHPAnimOldHP);
        // LD_addr_A(wCurHPAnimHighHP);
        wram->wCurHPAnimHighHP = wram->wCurHPAnimOldHP & 0xff;
        // LD_A_addr(wCurHPAnimNewHP);
        // LD_addr_A(wCurHPAnimLowHP);
        wram->wCurHPAnimLowHP = wram->wCurHPAnimNewHP & 0xff;
        // LD_A_E;
        // XOR_A(0xff);
        // INC_A;
        // LD_E_A;
        // LD_A_D;
        // XOR_A(0xff);
        // LD_D_A;
        de = -(de - bc);
        // LD_BC(-1);
        bc = -1;
    }
    else {
        // LD_A_addr(wCurHPAnimOldHP);
        // LD_addr_A(wCurHPAnimLowHP);
        wram->wCurHPAnimLowHP = wram->wCurHPAnimOldHP & 0xff;
        // LD_A_addr(wCurHPAnimNewHP);
        // LD_addr_A(wCurHPAnimHighHP);
        wram->wCurHPAnimHighHP = wram->wCurHPAnimNewHP & 0xff;
        de = de - bc;
        // LD_BC(1);
        bc = 1;
        // goto got_direction;
    }

    printf("HP Anim: %d -> %d (%d, %d)\n", wram->wCurHPAnimOldHP, wram->wCurHPAnimNewHP, (int16_t)de, (int16_t)bc);

// got_direction:
    // LD_A_D;
    // LD_addr_A(wCurHPAnimDeltaHP);
    // LD_A_E;
    // LD_addr_A(wCurHPAnimDeltaHP + 1);
    wram->wCurHPAnimDeltaHP = NativeToBigEndian16(de);
    // RET;
    return bc;
}

void v_AnimateHPBar(tile_t* hl){
    // CALL(av_AnimateHPBar_IsMaximumMoreThan48Pixels);
    // IF_C goto MoreThan48Pixels;
    if(v_AnimateHPBar_IsMaximumMoreThan48Pixels()) {
    // MoreThan48Pixels:
        // CALL(av_AnimateHPBar_ComputePixels);
        uint16_t bc = v_AnimateHPBar_ComputePixels();
        bool done;

        do {
        // LongAnimLoop:
            // PUSH_BC;
            // PUSH_HL;
            // CALL(aLongAnim_UpdateVariables);
            done = LongAnim_UpdateVariables(bc);
            // POP_HL;
            // POP_BC;
            // RET_C ;
            if(done)
                return;
            // PUSH_AF;
            // PUSH_BC;
            // PUSH_HL;
            // CALL(aLongHPBarAnim_UpdateTiles);
            LongHPBarAnim_UpdateTiles(hl);
            // CALL(aHPBarAnim_BGMapUpdate);
            HPBarAnim_BGMapUpdate();
            // POP_HL;
            // POP_BC;
            // POP_AF;
            // IF_NC goto LongAnimLoop;
        } while(!done);
        // RET;
    }
    else {
        // CALL(av_AnimateHPBar_ComputePixels);
        uint16_t bc = v_AnimateHPBar_ComputePixels();
        bool done;

        do {
        // ShortAnimLoop:
            // PUSH_BC;
            // PUSH_HL;
            // CALL(aShortAnim_UpdateVariables);
            done = ShortAnim_UpdateVariables(bc);
            // POP_HL;
            // POP_BC;
            // PUSH_AF;
            // PUSH_BC;
            // PUSH_HL;
            // CALL(aShortHPBarAnim_UpdateTiles);
            ShortHPBarAnim_UpdateTiles(hl);
            // CALL(aHPBarAnim_BGMapUpdate);
            HPBarAnim_BGMapUpdate();
            // POP_HL;
            // POP_BC;
            // POP_AF;
            // IF_NC goto ShortAnimLoop;
        } while(!done);
        // RET;
    }
}

bool ShortAnim_UpdateVariables(uint16_t bc){
    // LD_HL(wCurHPBarPixels);
    // LD_A_addr(wNewHPBarPixels);
    // CP_A_hl;
    // IF_NZ goto not_finished;
    if(wram->wCurHPBarPixels != wram->wNewHPBarPixels) {
    // not_finished:
        // LD_A_C;
        // ADD_A_hl;
        // LD_hl_A;
        wram->wCurHPBarPixels += bc;
        // CALL(aShortHPBar_CalcPixelFrame);
        ShortHPBar_CalcPixelFrame();
        // AND_A_A;
        // RET;
        return false;
    }
    // SCF;
    // RET;
    return true;
}

bool LongAnim_UpdateVariables(uint16_t bc){

// loop:
    // LD_HL(wCurHPAnimOldHP);
    // LD_A_hli;
    // LD_E_A;
    // LD_A_hli;
    // LD_D_A;
    // LD_A_E;
    // CP_A_hl;
    // IF_NZ goto next;
    // INC_HL;
    // LD_A_D;
    // CP_A_hl;
    // IF_NZ goto next;
    while(wram->wCurHPAnimOldHP != wram->wCurHPAnimNewHP) {
    // next:
        // LD_L_E;
        // LD_H_D;
        uint16_t de_old = wram->wCurHPAnimOldHP;
        // ADD_HL_BC;
        // LD_A_L;
        // LD_addr_A(wCurHPAnimOldHP);
        // LD_A_H;
        // LD_addr_A(wCurHPAnimOldHP + 1);
        wram->wCurHPAnimOldHP += bc;
        // PUSH_HL;
        // PUSH_DE;
        // PUSH_BC;
        // LD_HL(wCurHPAnimMaxHP);
        // LD_A_hli;
        // LD_E_A;
        // LD_A_hli;
        // LD_D_A;
        // LD_A_hli;
        // LD_C_A;
        // LD_A_hli;
        // LD_B_A;
    // This routine is buggy. The result from ComputeHPBarPixels is stored
    // in e. However, the pop de opcode deletes this result before it is even
    // used. The game then proceeds as though it never deleted that output.
    // To fix, uncomment the line below.
#if BUGFIX_HP_BAR_LONG_ANIM
        // CALL(aComputeHPBarPixels);
    // ld a, e
        (void)de_old;
        uint8_t a = ComputeHPBarPixels_Conv(wram->wCurHPAnimOldHP, wram->wCurHPAnimMaxHP);
        // POP_BC;
        // POP_DE;
        // POP_HL;
        // LD_A_E;  // Comment or delete this line to fix the above bug.
#else
        // CALL(aComputeHPBarPixels);
        ComputeHPBarPixels_Conv(wram->wCurHPAnimOldHP, wram->wCurHPAnimMaxHP);
        // POP_BC;
        // POP_DE;
        // POP_HL;
        // LD_A_E;  // Comment or delete this line to fix the above bug.
        uint8_t a = LOW(de_old);
#endif
        // LD_HL(wCurHPBarPixels);
        // CP_A_hl;
        // IF_Z goto loop;
        if(wram->wCurHPBarPixels != a){
            // LD_hl_A;
            wram->wCurHPBarPixels = a;
            // AND_A_A;
            // RET;
            return false;
        }
    }
    // SCF;
    // RET;
    return true;
}

void ShortHPBarAnim_UpdateTiles(tile_t* hl){
    // CALL(aHPBarAnim_UpdateHPRemaining);
    HPBarAnim_UpdateHPRemaining(hl);
    // LD_D(HP_BAR_LENGTH);
    // LD_A_addr(wWhichHPBar);
    // AND_A(0x1);
    // LD_B_A;
    // LD_A_addr(wCurHPBarPixels);
    // LD_E_A;
    // LD_C_A;
    // PUSH_DE;
    // CALL(aHPBarAnim_RedrawHPBar);
    HPBarAnim_RedrawHPBar(hl, HP_BAR_LENGTH, wram->wCurHPBarPixels, wram->wWhichHPBar & 0x1, wram->wCurHPBarPixels);
    // POP_DE;
    // CALL(aHPBarAnim_PaletteUpdate);
    HPBarAnim_PaletteUpdate(wram->wCurHPBarPixels);
    // RET;

}

void LongHPBarAnim_UpdateTiles(tile_t* hl){
    // CALL(aHPBarAnim_UpdateHPRemaining);
    HPBarAnim_UpdateHPRemaining(hl);
    // LD_A_addr(wCurHPAnimOldHP);
    // LD_C_A;
    // LD_A_addr(wCurHPAnimOldHP + 1);
    // LD_B_A;
    // LD_A_addr(wCurHPAnimMaxHP);
    // LD_E_A;
    // LD_A_addr(wCurHPAnimMaxHP + 1);
    // LD_D_A;
    // CALL(aComputeHPBarPixels);
    uint8_t e = ComputeHPBarPixels_Conv(wram->wCurHPAnimOldHP, wram->wCurHPAnimMaxHP);
    // LD_C_E;
    // LD_D(HP_BAR_LENGTH);
    // LD_A_addr(wWhichHPBar);
    // AND_A(0x1);
    // LD_B_A;
    // PUSH_DE;
    // CALL(aHPBarAnim_RedrawHPBar);
    HPBarAnim_RedrawHPBar(hl, HP_BAR_LENGTH, e, wram->wWhichHPBar & 0x1, e);
    // POP_DE;
    // CALL(aHPBarAnim_PaletteUpdate);
    HPBarAnim_PaletteUpdate(e);
    // RET;
}

void HPBarAnim_RedrawHPBar(tile_t* hl, uint8_t d, uint8_t e, uint8_t b, uint8_t c){
    // LD_A_addr(wWhichHPBar);
    // CP_A(0x2);
    // IF_NZ goto skip;
    if(wram->wWhichHPBar == 0x2) {
        // LD_A(2 * SCREEN_WIDTH);
        // ADD_A_L;
        // LD_L_A;
        // LD_A(0);
        // ADC_A_H;
        // LD_H_A;
        hl += 2 * SCREEN_WIDTH;
    }

// skip:
    // CALL(aDrawBattleHPBar);
    DrawBattleHPBar_Conv(hl, d, e, b, c);
    // RET;
}

void HPBarAnim_UpdateHPRemaining(tile_t* hl){
    // LD_A_addr(wWhichHPBar);
    // AND_A_A;
    // RET_Z ;
    uint16_t de;
    if(wram->wWhichHPBar == 0x0)
        return;
    // CP_A(0x1);
    // IF_Z goto load_15;
    else if(wram->wWhichHPBar == 0x1) {
    // load_15:
        // LD_DE(SCREEN_WIDTH + 1);
        de = SCREEN_WIDTH + 1;
    }
    else {
        // LD_DE(SCREEN_WIDTH + 2);
        de = SCREEN_WIDTH + 2;
        // goto loaded_de;
    }

// loaded_de:
    // PUSH_HL;
    // ADD_HL_DE;
    hl += de;
    // LD_A(0x7f);
    // LD_hli_A;
    hl[0] = 0x7f;
    // LD_hli_A;
    hl[1] = 0x7f;
    // LD_hld_A;
    hl[2] = 0x7f;
    // DEC_HL;
    // LD_A_addr(wCurHPAnimOldHP);
    // LD_addr_A(wStringBuffer2 + 1);
    wram->wStringBuffer2[1] = LOW(wram->wCurHPAnimOldHP);
    // LD_A_addr(wCurHPAnimOldHP + 1);
    // LD_addr_A(wStringBuffer2);
    wram->wStringBuffer2[0] = HIGH(wram->wCurHPAnimOldHP);
    // LD_DE(wStringBuffer2);
    // LD_BC((2 << 8) | 3);
    // CALL(aPrintNum);
    PrintNum_Conv2(hl, wram->wStringBuffer2, 2, 3);
    // POP_HL;
    // RET;
}

void HPBarAnim_PaletteUpdate(uint8_t e){
    // LDH_A_addr(hCGB);
    // AND_A_A;
    // RET_Z ;
    if(hram->hCGB == 0)
        return;
    // LD_HL(wCurHPAnimPal);
    // CALL(aSetHPPal);
    SetHPPal_Conv(&wram->wCurHPAnimPal, e);
    // LD_A_addr(wCurHPAnimPal);
    // LD_C_A;
    // FARCALL(aApplyHPBarPals);
    ApplyHPBarPals(wram->wCurHPAnimPal);
    // RET;
}

void HPBarAnim_BGMapUpdate(void){
    // LDH_A_addr(hCGB);
    // AND_A_A;
    // IF_NZ goto cgb;
    if(hram->hCGB) {
    // cgb:
        // LD_A_addr(wWhichHPBar);
        // AND_A_A;
        // IF_Z goto load_0;
        // CP_A(0x1);
        // IF_Z goto load_1;
        uint8_t c;
        if(wram->wWhichHPBar == 0) {
        // load_0:
            // LD_C(0x0);
            c = 0x0;
            // goto finish;
        }
        else if(wram->wWhichHPBar == 1){
        // load_1:
            // LD_C(0x1);
            c = 0x1;
        }
        else {
            // LD_A_addr(wCurPartyMon);
            // CP_A(0x3);
            // IF_NC goto bottom_half_of_screen;
            if(wram->wCurPartyMon < 0x3) {
                // LD_C(0x0);
                // goto got_third;
                c = 0x0;
            }
            else {
            // bottom_half_of_screen:
                // LD_C(0x1);
                c = 0x1;
            }

        // got_third:
            // PUSH_AF;
            // CP_A(0x2);
            // IF_Z goto skip_delay;
            // CP_A(0x5);
            // IF_Z goto skip_delay;
            if(wram->wCurPartyMon != 0x2 && wram->wCurPartyMon != 0x5){
                // LD_A(0x2);
                // LDH_addr_A(hBGMapMode);
                hram->hBGMapMode = 0x2;
                // LD_A_C;
                // LDH_addr_A(hBGMapThird);
                hram->hBGMapThird = c;
                // CALL(aDelayFrame);
                DelayFrame();
            }

        // skip_delay:
            // LD_A(0x1);
            // LDH_addr_A(hBGMapMode);
            hram->hBGMapMode = 0x1;
            // LD_A_C;
            // LDH_addr_A(hBGMapThird);
            hram->hBGMapThird = c;
            // CALL(aDelayFrame);
            DelayFrame();
            // POP_AF;
            // CP_A(0x2);
            // IF_Z goto two_frames;
            // CP_A(0x5);
            // IF_Z goto two_frames;
            // RET;
            if(wram->wCurPartyMon == 0x2 || wram->wCurPartyMon == 0x5) {
            // two_frames:
                // INC_C;
                c++;
                // LD_A(0x2);
                // LDH_addr_A(hBGMapMode);
                hram->hBGMapMode = 0x2;
                // LD_A_C;
                // LDH_addr_A(hBGMapThird);
                hram->hBGMapThird = c;
                // CALL(aDelayFrame);
                DelayFrame();
                // LD_A(0x1);
                // LDH_addr_A(hBGMapMode);
                hram->hBGMapMode = 0x1;
                // LD_A_C;
                // LDH_addr_A(hBGMapThird);
                hram->hBGMapThird = c;
                // CALL(aDelayFrame);
                DelayFrame();
                // RET;
            }
            return;
        }

    // finish:
        // CALL(aDelayFrame);
        DelayFrame();
        // LD_A_C;
        // LDH_addr_A(hBGMapThird);
        hram->hBGMapThird = c;
        // CALL(aDelayFrame);
        DelayFrame();
        // RET;
        return;
    }
    // CALL(aDelayFrame);
    DelayFrame();
    // CALL(aDelayFrame);
    DelayFrame();
    // RET;
}

void ShortHPBar_CalcPixelFrame(void){
    // LD_A_addr(wCurHPAnimMaxHP);
    // LD_C_A;
    // LD_B(0);
    uint8_t c = wram->wCurHPAnimMaxHP & 0xff;
    // LD_HL(0);
    // LD_A_addr(wCurHPBarPixels);
    // CP_A(HP_BAR_LENGTH_PX);
    // IF_NC goto return_max;
    if(wram->wCurHPBarPixels >= HP_BAR_LENGTH_PX) {
    // return_max:
        // LD_A_addr(wCurHPAnimMaxHP);
        // LD_addr_A(wCurHPAnimOldHP);
        wram->wCurHPAnimOldHP = (wram->wCurHPAnimOldHP & 0xff00) | (wram->wCurHPAnimMaxHP & 0xff);
        // RET;
        return;
    }
    // AND_A_A;
    // IF_Z goto return_zero;
    else if(wram->wCurHPBarPixels == 0) {
    // return_zero:
        // XOR_A_A;
        // LD_addr_A(wCurHPAnimOldHP);
        wram->wCurHPAnimOldHP = (wram->wCurHPAnimOldHP & 0xff00) | 0;
        // RET;
        return;
    }
    // CALL(aAddNTimes);
    uint16_t hl = c * wram->wCurHPBarPixels;

    // LD_B(0);
    uint8_t b = 0;
//  This routine is buggy. If [wCurHPAnimMaxHP] * [wCurHPBarPixels] is
//  divisible by HP_BAR_LENGTH_PX, the loop runs one extra time.
//  To fix, uncomment the line below.

    while(1) {
    // loop:
        // LD_A_L;
        // SUB_A(HP_BAR_LENGTH_PX);
        // LD_L_A;
        // LD_A_H;
        // SBC_A(0x0);
        // LD_H_A;
#if BUGFIX_SHORT_CALC_PIXEL_FRAME
    // jr z, .done
        // IF_C goto done;
        if(hl <= HP_BAR_LENGTH_PX){
            hl -= HP_BAR_LENGTH_PX;
            break;
        }
#else
        // IF_C goto done;
        if(hl < HP_BAR_LENGTH_PX) {
            hl -= HP_BAR_LENGTH_PX;
            break;
        }
#endif
        hl -= HP_BAR_LENGTH_PX;
        // INC_B;
        b++;
        // goto loop;
    }


// done:
    // PUSH_BC;
    // LD_BC(0x80);
    // ADD_HL_BC;
    hl += 0x80;
    // POP_BC;
    // LD_A_L;
    // SUB_A(HP_BAR_LENGTH_PX);
    // LD_L_A;
    // LD_A_H;
    // SBC_A(0x0);
    // LD_H_A;
    // IF_C goto no_carry;
    if(hl >= HP_BAR_LENGTH_PX) {
        // INC_B;
        b++;
    }

// no_carry:
    // LD_A_addr(wCurHPAnimLowHP);
    // CP_A_B;
    // IF_NC goto finish;
    if(wram->wCurHPAnimLowHP >= b) {
        wram->wCurHPAnimOldHP = wram->wCurHPAnimLowHP;
    }
    // LD_A_addr(wCurHPAnimHighHP);
    // CP_A_B;
    // IF_C goto finish;
    else if(wram->wCurHPAnimHighHP < b){
        wram->wCurHPAnimOldHP = wram->wCurHPAnimHighHP;
    }
    // LD_A_B;

// finish:
    // LD_addr_A(wCurHPAnimOldHP);
    else {
        wram->wCurHPAnimOldHP = b;
    }
    // RET;
}
