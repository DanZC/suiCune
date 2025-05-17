#include "../constants.h"
#include "print_text.h"
#include "joypad.h"
#include "delay.h"
#include "../engine/math/print_num.h"
#include "../mobile/mobile_41.h"

//  Wait before printing the next letter.
//  The text speed setting in wOptions is actually a frame count:
//      fast: 1 frame
//      mid:  3 frames
//      slow: 5 frames
//  wTextboxFlags[!0] and A or B override text speed with a one-frame delay.
//  wOptions[4] and wTextboxFlags[!1] disable the delay.
void PrintLetterDelay(void) {
    // LD_A_addr(wOptions);
    // BIT_A(NO_TEXT_SCROLL);
    // RET_NZ;
    if(bit_test(wram->wOptions, NO_TEXT_SCROLL))
        return;

    //  non-scrolling text?
    // LD_A_addr(wTextboxFlags);
    // BIT_A(NO_TEXT_DELAY_F);
    // RET_Z;
    if(!bit_test(wram->wTextboxFlags, NO_TEXT_DELAY_F))
        return;

    // PUSH_HL;
    // PUSH_DE;
    // PUSH_BC;

    // LD_HL(hOAMUpdate);
    // LD_A_hl;
    // PUSH_AF;
    uint8_t tempOAM = hram.hOAMUpdate;

    //  orginally turned oam update off...
    //     ld a, 1
    // LD_hl_A;
    hram.hOAMUpdate = tempOAM; // Remove this?

    //  force fast scroll?
    // LD_A_addr(wTextboxFlags);
    // BIT_A(FAST_TEXT_DELAY_F);
    // IF_Z goto fast;
    if(!bit_test(wram->wTextboxFlags, FAST_TEXT_DELAY_F))
    {
    // fast:
        // LD_A(TEXT_DELAY_FAST);
    // updatedelay:
        // LD_addr_A(wTextDelayFrames);
        wram->wTextDelayFrames = TEXT_DELAY_FAST;
    }
    else 
    {
        //  text speed
        // LD_A_addr(wOptions);
        // AND_A(0b111);
    // updatedelay:
        // LD_addr_A(wTextDelayFrames);
        wram->wTextDelayFrames = (wram->wOptions & 0b111);
    }

    while(1) {
    // checkjoypad:
    // CALL(aGetJoypad);
        GetJoypad();

        //  input override
        // LD_A_addr(wDisableTextAcceleration);
        // AND_A_A;
        // IF_NZ goto wait;
        if(wram->wDisableTextAcceleration != 0)
        {
        // wait:
            // LD_A_addr(wTextDelayFrames);
            // AND_A_A;
            // IF_NZ goto checkjoypad;
            if(wram->wTextDelayFrames != 0) {
                DelayFrame();
                continue;
            }
        // end:
            // POP_AF;
            // LDH_addr_A(hOAMUpdate);
            hram.hOAMUpdate = tempOAM;

            // POP_BC;
            // POP_DE;
            // POP_HL;
            // RET;
            return;
        }

        //  Wait one frame if holding A or B.
        // LDH_A_addr(hJoyDown);
        // BIT_A(A_BUTTON_F);
        // IF_Z goto checkb;
        else if(!bit_test(hram.hJoyDown, A_BUTTON_F))
        {
        // checkb:
            // BIT_A(B_BUTTON_F);
            // IF_Z goto wait;
            if(!bit_test(hram.hJoyDown, B_BUTTON_F))
            {
            // wait:
                // LD_A_addr(wTextDelayFrames);
                // AND_A_A;
                // IF_NZ goto checkjoypad;
                if(wram->wTextDelayFrames != 0) {
                    DelayFrame();
                    continue;
                }
            // end:
                // POP_AF;
                // LDH_addr_A(hOAMUpdate);
                hram.hOAMUpdate = tempOAM;

                // POP_BC;
                // POP_DE;
                // POP_HL;
                // RET;
                return;
            }
        // delay:
            // CALL(aDelayFrame);
            // goto end;
            DelayFrame();
        // end:
            // POP_AF;
            // LDH_addr_A(hOAMUpdate);
            hram.hOAMUpdate = tempOAM;

            // POP_BC;
            // POP_DE;
            // POP_HL;
            // RET;
            return;
        }

        // goto delay;
    // delay:
        // CALL(aDelayFrame);
        // goto end;
        DelayFrame();
    // end:
        // POP_AF;
        // LDH_addr_A(hOAMUpdate);
        hram.hOAMUpdate = tempOAM;

        // POP_BC;
        // POP_DE;
        // POP_HL;
        // RET;
        return;
    }

//     goto delay;

// checkb:
//     BIT_A(B_BUTTON_F);
//     IF_Z goto wait;

// delay:
//         CALL(aDelayFrame);
//     goto end;

// wait:
//     LD_A_addr(wTextDelayFrames);
//     AND_A_A;
//     // IF_NZ goto checkjoypad;

// end:
//     // POP_AF;
//     // LDH_addr_A(hOAMUpdate);
//     gb_write(hOAMUpdate, tempOAM);

//     // POP_BC;
//     // POP_DE;
//     // POP_HL;
//     // RET;
//     return;
}

//  Copy [hl .. bc) to de.
//  In other words, the source data is
//  from hl up to but not including bc,
//  and the destination is de.
//  Unused
void CopyDataUntil_GB(uint16_t de, uint16_t hl, uint16_t bc) {
    do {
        // LD_A_hli;
        // LD_de_A;
        // INC_DE;
        gb_write(de++, gb_read(hl++));


        // LD_A_H;
        // CP_A_B;
        // JR_NZ(mCopyDataUntil);
        // LD_A_L;
        // CP_A_C;
        // JR_NZ(mCopyDataUntil);
    } while(hl != bc);
}

//  Copy [hl .. bc) to de.
//  In other words, the source data is
//  from hl up to but not including bc,
//  and the destination is de.
void CopyDataUntil(void* de, const void* hl, const void* bc) {
    uint8_t *_de = de;
    const uint8_t *_hl = hl, *_bc = bc;
    do {
        // LD_A_hli;
        // LD_de_A;
        // INC_DE;
        *(_de++) = *(_hl++);


        // LD_A_H;
        // CP_A_B;
        // JR_NZ(mCopyDataUntil);
        // LD_A_L;
        // CP_A_C;
        // JR_NZ(mCopyDataUntil);
    } while(_hl != _bc);
}

//  Print c digits of the b-byte value from de to hl.
//  Allows 2 to 7 digits. For 1-digit numbers, add
//  the value to char "0" instead of calling PrintNum.
//  The high nybble of the c register specifies how many of the total amount of
//  digits will be in front of the decimal point.
//  Some extra flags can be given in bits 5-7 of b.
//  Bit 5: money if set (unless left-aligned without leading zeros)
//  Bit 6: left-aligned if set
//  Bit 7: print leading zeros if set
uint16_t PrintNum_GB(uint16_t hl, uint16_t de, uint8_t b, uint8_t c) {
    bank_push(BANK(av_PrintNum));
    hl = v_PrintNum_GB(hl, de, b, c);
    bank_pop;
    return hl;
}

//  Print c digits of the b-byte value from de to hl.
//  Allows 2 to 7 digits. For 1-digit numbers, add
//  the value to char "0" instead of calling PrintNum.
//  The high nybble of the c register specifies how many of the total amount of
//  digits will be in front of the decimal point.
//  Some extra flags can be given in bits 5-7 of b.
//  Bit 5: money if set (unless left-aligned without leading zeros)
//  Bit 6: left-aligned if set
//  Bit 7: print leading zeros if set
uint8_t* PrintNum(uint8_t* hl, const void* de, uint8_t b, uint8_t c) {
    // bank_push(BANK(av_PrintNum));
    hl = v_PrintNum(hl, de, b, c);
    // bank_pop;
    return hl;
}

uint8_t* MobilePrintNum(uint8_t* hl, const void* de, uint8_t b, uint8_t c) {
    // HOMECALL(av_MobilePrintNum);
    switch(b & 0xf) {
        case 0x1: printf("MobilePrintNum(%d)\n", *(uint8_t*)de); break;
        case 0x2: printf("MobilePrintNum(%d)\n", *(uint16_t*)de); break;
        case 0x3: printf("MobilePrintNum(%d)\n", ((uint8_t*)de)[0] | (((uint8_t*)de)[1] << 8) | (((uint8_t*)de)[2])); break;
        case 0x4: printf("MobilePrintNum(%d)\n", *(uint32_t*)de); break;
    };
    // RET;
    return v_MobilePrintNum(hl, de, b, c);
}

// UNUSED
void FarPrintText(void) {
    // LDH_addr_A(hTempBank);
    // LDH_A_addr(hROMBank);
    // PUSH_AF;
    // LDH_A_addr(hTempBank);
    // RST(aBankswitch);

    // CALL(aPrintText);

    // POP_AF;
    // RST(aBankswitch);
    // RET;
}

// UNUSED
void CallPointerAt(void) {
    // LDH_A_addr(hROMBank);
    // PUSH_AF;
    // LD_A_hli;
    // RST(aBankswitch);

    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;

    // CALL(av_hl_);

    // POP_HL;
    // LD_A_H;
    // RST(aBankswitch);
    // RET;
}
