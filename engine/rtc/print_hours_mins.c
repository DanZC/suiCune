#include "../../constants.h"
#include "print_hours_mins.h"
#include "../../home/print_text.h"
#include "../../home/text.h"

void PrintFiveDigitNumber(void){
//  //  unreferenced
//  Debug function?
//  Input: bc = value, de = destination
    LD_A_B;
    LD_B_C;
    LD_C_A;
    PUSH_BC;  // de points to this on the stack for PrintNum
    PUSH_DE;
    LD_HL_SP(2);
    LD_D_H;
    LD_E_L;
    POP_HL;
    LD_BC((PRINTNUM_LEADINGZEROS | 2 << 8) | 5);
    CALL(aPrintNum);
    POP_BC;
    RET;

}

void PrintHoursMins(void){
//  Hours in b, minutes in c
    LD_A_B;
    CP_A(12);
    PUSH_AF;
    IF_C goto AM;
    IF_Z goto PM;
    SUB_A(12);
    goto PM;

AM:
    OR_A_A;
    IF_NZ goto PM;
    LD_A(12);

PM:
    LD_B_A;
//  Crazy stuff happening with the stack
    PUSH_BC;
    LD_HL_SP(1);
    PUSH_DE;
    PUSH_HL;
    POP_DE;
    POP_HL;
    LD_hl(0x7f);
    LD_BC((1 << 8) | 2);
    CALL(aPrintNum);
    LD_hl(0x9c);
    INC_HL;
    LD_D_H;
    LD_E_L;
    LD_HL_SP(0);
    PUSH_DE;
    PUSH_HL;
    POP_DE;
    POP_HL;
    LD_BC((PRINTNUM_LEADINGZEROS | 1 << 8) | 2);
    CALL(aPrintNum);
    POP_BC;
    LD_DE(mString_AM);
    POP_AF;
    IF_C goto place_am_pm;
    LD_DE(mString_PM);

place_am_pm:
    INC_HL;
    CALL(aPlaceString);
    RET;

}

//  Prints hours and minutes to tilemap destination de.
//  Hours in b, minutes in c
void PrintHoursMins_Conv(uint16_t de, uint8_t b, uint8_t c){
    // LD_A_B;
    // CP_A(12);
    // PUSH_AF;
    // IF_C goto AM;
    uint16_t am_pm_str;
    if(b < 12) {
        // OR_A_A;
        // IF_NZ goto PM;
        // LD_A(12);
        am_pm_str = mString_AM;
        if(b == 0) 
            b = 12;
    }
    // IF_Z goto PM;
    else if(b > 12) {
        am_pm_str = mString_PM;
        b -= 12;
    }
    else {
        am_pm_str = mString_PM;
    }
    // SUB_A(12);
    // goto PM;
    // LD_B_A;
//  Crazy stuff happening with the stack
    // PUSH_BC;
    gb_write(--REG_SP, b);
    gb_write(--REG_SP, c);
    // LD_HL_SP(1);
    // PUSH_DE;
    // PUSH_HL;
    // POP_DE;
    // POP_HL;
    uint16_t hl = de;
    de = REG_SP + 1;
    // LD_hl(0x7f);
    gb_write(hl, 0x7f);
    // LD_BC((1 << 8) | 2);
    REG_HL = hl;
    REG_DE = de;
    REG_BC = ((1 << 8) | 2);
    CALL(aPrintNum);
    // hl = PrintNum_Conv(hl, de, 1, 2);
    // LD_hl(0x9c);
    // INC_HL;
    gb_write(REG_HL++, 0x9c);
    // LD_D_H;
    // LD_E_L;
    // LD_HL_SP(0);
    // PUSH_DE;
    // PUSH_HL;
    // POP_DE;
    // POP_HL;
    de = REG_SP;
    REG_DE = de;
    REG_BC = (((PRINTNUM_LEADINGZEROS | 1) << 8) | 2);
    CALL(aPrintNum);
    // hl = PrintNum_Conv(hl, de, 1 | PRINTNUM_LEADINGZEROS, 2);
    hl = REG_HL;
    REG_SP += 2;
    // POP_BC;
    // LD_DE(mString_AM);
    // POP_AF;
    // IF_C goto place_am_pm;
    // LD_DE(mString_PM);
    // INC_HL;
    // CALL(aPlaceString);
    PlaceString_Conv(&(struct TextCmdState){.de = am_pm_str, .hl = hl + 1, .bc = (b << 8) | c}, hl + 1);
    // RET;
}