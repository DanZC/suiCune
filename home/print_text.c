#include "../constants.h"
#include "print_text.h"
#include "joypad.h"
#include "delay.h"
#include "../engine/math/print_num.h"

void PrintLetterDelay(void) {
        //  Wait before printing the next letter.

    //  The text speed setting in wOptions is actually a frame count:
    //      fast: 1 frame
    //      mid:  3 frames
    //      slow: 5 frames

    //  wTextboxFlags[!0] and A or B override text speed with a one-frame delay.
    //  wOptions[4] and wTextboxFlags[!1] disable the delay.

    LD_A_addr(wOptions);
    BIT_A(NO_TEXT_SCROLL);
    RET_NZ;

    //  non-scrolling text?
    LD_A_addr(wTextboxFlags);
    BIT_A(NO_TEXT_DELAY_F);
    RET_Z;

    PUSH_HL;
    PUSH_DE;
    PUSH_BC;

    LD_HL(hOAMUpdate);
    LD_A_hl;
    PUSH_AF;

    //  orginally turned oam update off...
    //     ld a, 1
    LD_hl_A;

    //  force fast scroll?
    LD_A_addr(wTextboxFlags);
    BIT_A(FAST_TEXT_DELAY_F);
    IF_Z goto fast;

    //  text speed
    LD_A_addr(wOptions);
    AND_A(0b111);
    goto updatedelay;

fast:
        LD_A(TEXT_DELAY_FAST);

updatedelay:
        LD_addr_A(wTextDelayFrames);

checkjoypad:
        CALL(aGetJoypad);

    //  input override
    LD_A_addr(wDisableTextAcceleration);
    AND_A_A;
    IF_NZ goto wait;

    //  Wait one frame if holding A or B.
    LDH_A_addr(hJoyDown);
    BIT_A(A_BUTTON_F);
    IF_Z goto checkb;
    goto delay;

checkb:
        BIT_A(B_BUTTON_F);
    IF_Z goto wait;

delay:
        CALL(aDelayFrame);
    goto end;

wait:
        LD_A_addr(wTextDelayFrames);
    AND_A_A;
    // IF_NZ goto checkjoypad;

end:
        POP_AF;
    LDH_addr_A(hOAMUpdate);
    POP_BC;
    POP_DE;
    POP_HL;
    RET;
}

//  Wait before printing the next letter.
//  The text speed setting in wOptions is actually a frame count:
//      fast: 1 frame
//      mid:  3 frames
//      slow: 5 frames
//  wTextboxFlags[!0] and A or B override text speed with a one-frame delay.
//  wOptions[4] and wTextboxFlags[!1] disable the delay.
void PrintLetterDelay_Conv(void) {
    // LD_A_addr(wOptions);
    // BIT_A(NO_TEXT_SCROLL);
    // RET_NZ;
    if((gb_read(wOptions) >> NO_TEXT_SCROLL) & 0x1)
        return;

    //  non-scrolling text?
    // LD_A_addr(wTextboxFlags);
    // BIT_A(NO_TEXT_DELAY_F);
    // RET_Z;
    if(!((gb_read(wTextboxFlags) >> NO_TEXT_DELAY_F) & 0x1))
        return;

    // PUSH_HL;
    // PUSH_DE;
    // PUSH_BC;

    // LD_HL(hOAMUpdate);
    // LD_A_hl;
    // PUSH_AF;
    uint8_t tempOAM = gb_read(hOAMUpdate);

    //  orginally turned oam update off...
    //     ld a, 1
    // LD_hl_A;
    gb_write(hOAMUpdate, tempOAM); // Remove this?

    //  force fast scroll?
    // LD_A_addr(wTextboxFlags);
    // BIT_A(FAST_TEXT_DELAY_F);
    // IF_Z goto fast;
    if(!((gb_read(wTextboxFlags) >> FAST_TEXT_DELAY_F) & 0x1))
    {
    // fast:
        // LD_A(TEXT_DELAY_FAST);
    // updatedelay:
        // LD_addr_A(wTextDelayFrames);
        gb_write(wTextDelayFrames, TEXT_DELAY_FAST);
    }
    else 
    {
        //  text speed
        // LD_A_addr(wOptions);
        // AND_A(0b111);
    // updatedelay:
        // LD_addr_A(wTextDelayFrames);
        gb_write(wTextDelayFrames, gb_read(wOptions) & 0b111);
    }

checkjoypad:
    // CALL(aGetJoypad);
    GetJoypad_Conv();

    //  input override
    // LD_A_addr(wDisableTextAcceleration);
    // AND_A_A;
    // IF_NZ goto wait;
    if(gb_read(wDisableTextAcceleration) != 0)
    {
    // wait:
        // LD_A_addr(wTextDelayFrames);
        // AND_A_A;
        // IF_NZ goto checkjoypad;
    // end:
        // POP_AF;
        // LDH_addr_A(hOAMUpdate);
        gb_write(hOAMUpdate, tempOAM);

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
    else if(!((gb_read(hJoyDown) >> A_BUTTON_F) & 0x1))
    {
    // checkb:
        // BIT_A(B_BUTTON_F);
        // IF_Z goto wait;
        if(!((gb_read(hJoyDown) >> B_BUTTON_F) & 0x1))
        {
        // wait:
            // LD_A_addr(wTextDelayFrames);
            // AND_A_A;
            // IF_NZ goto checkjoypad;
        // end:
            // POP_AF;
            // LDH_addr_A(hOAMUpdate);
            gb_write(hOAMUpdate, tempOAM);

            // POP_BC;
            // POP_DE;
            // POP_HL;
            // RET;
            return;
        }
    // delay:
        CALL(aDelayFrame);
        // goto end;
        // DelayFrame();
    // end:
        // POP_AF;
        // LDH_addr_A(hOAMUpdate);
        gb_write(hOAMUpdate, tempOAM);

        // POP_BC;
        // POP_DE;
        // POP_HL;
        // RET;
        return;
    }

    // goto delay;
// delay:
    CALL(aDelayFrame);
    // goto end;
    // DelayFrame();
// end:
    // POP_AF;
    // LDH_addr_A(hOAMUpdate);
    gb_write(hOAMUpdate, tempOAM);

    // POP_BC;
    // POP_DE;
    // POP_HL;
    // RET;
    return;

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

void CopyDataUntil(void) {
        //  Copy [hl .. bc) to de.

    //  In other words, the source data is
    //  from hl up to but not including bc,
    //  and the destination is de.

    LD_A_hli;
    LD_de_A;
    INC_DE;
    LD_A_H;
    CP_A_B;
    JR_NZ(mCopyDataUntil);
    LD_A_L;
    CP_A_C;
    JR_NZ(mCopyDataUntil);
    RET;
}

//  Copy [hl .. bc) to de.
//  In other words, the source data is
//  from hl up to but not including bc,
//  and the destination is de.
void CopyDataUntil_Conv(uint16_t de, uint16_t hl, uint16_t bc) {
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

void PrintNum(void) {
        HOMECALL(av_PrintNum);
    RET;
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
uint16_t PrintNum_Conv(uint16_t hl, uint16_t de, uint8_t b, uint8_t c) {
    bank_push(BANK(av_PrintNum));
    hl = v_PrintNum_Conv(hl, de, b, c);
    bank_pop;
    return hl;
}

void MobilePrintNum(void) {
        HOMECALL(av_MobilePrintNum);
    RET;
}

void FarPrintText(void) {
        LDH_addr_A(hTempBank);
    LDH_A_addr(hROMBank);
    PUSH_AF;
    LDH_A_addr(hTempBank);
    RST(aBankswitch);

    CALL(aPrintText);

    POP_AF;
    RST(aBankswitch);
    RET;
}

void CallPointerAt(void) {
        LDH_A_addr(hROMBank);
    PUSH_AF;
    LD_A_hli;
    RST(aBankswitch);

    LD_A_hli;
    LD_H_hl;
    LD_L_A;

    CALL(av_hl_);

    POP_HL;
    LD_A_H;
    RST(aBankswitch);
    RET;
}
