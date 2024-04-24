#include "../../constants.h"
#include "print_num.h"
#include "../../charmap.h"

void v_PrintNum(void){
//  Print c digits of the b-byte value from de to hl.
//  Allows 2 to 7 digits. For 1-digit numbers, add
//  the value to char "0" instead of calling PrintNum.
//  The high nybble of the c register specifies how many of the total amount of
//  digits will be in front of the decimal point.
//  Some extra flags can be given in bits 5-7 of b.
//  Bit 5: money if set (unless left-aligned without leading zeros)
//  Bit 6: left-aligned if set
//  Bit 7: print leading zeros if set

    PUSH_BC;

    BIT_B(5);
    IF_Z goto main;
    BIT_B(7);
    IF_NZ goto moneyflag;
    BIT_B(6);
    IF_Z goto main;


moneyflag:
//   //  101xxxxx or 011xxxxx
    LD_A(0xf0);
    LD_hli_A;
    RES_B(5);  // 100xxxxx or 010xxxxx


main:
    XOR_A_A;
    LDH_addr_A(hPrintNumBuffer + 0);
    LDH_addr_A(hPrintNumBuffer + 1);
    LDH_addr_A(hPrintNumBuffer + 2);
    LD_A_B;
    AND_A(0xf);
    CP_A(1);
    IF_Z goto byte;
    CP_A(2);
    IF_Z goto word;
//  maximum 3 bytes
    LD_A_de;
    LDH_addr_A(hPrintNumBuffer + 1);
    INC_DE;
    LD_A_de;
    LDH_addr_A(hPrintNumBuffer + 2);
    INC_DE;
    LD_A_de;
    LDH_addr_A(hPrintNumBuffer + 3);
    goto start;


word:
    LD_A_de;
    LDH_addr_A(hPrintNumBuffer + 2);
    INC_DE;
    LD_A_de;
    LDH_addr_A(hPrintNumBuffer + 3);
    goto start;


byte:
    LD_A_de;
    LDH_addr_A(hPrintNumBuffer + 3);


start:
    PUSH_DE;

    LD_D_B;
    LD_A_C;
    SWAP_A;
    AND_A(0xf);
    LD_E_A;
    LD_A_C;
    AND_A(0xf);
    LD_B_A;
    LD_C(0);
    CP_A(2);
    IF_Z goto two;
    CP_A(3);
    IF_Z goto three;
    CP_A(4);
    IF_Z goto four;
    CP_A(5);
    IF_Z goto five;
    CP_A(6);
    IF_Z goto six;

//  seven
    LD_A(HIGH(1000000 >> 8));
    LDH_addr_A(hPrintNumBuffer + 4);
    LD_A(HIGH(1000000));  // mid
    LDH_addr_A(hPrintNumBuffer + 5);
    LD_A(LOW(1000000));
    LDH_addr_A(hPrintNumBuffer + 6);
    CALL(av_PrintNum_PrintDigit);
    CALL(av_PrintNum_AdvancePointer);


six:
    LD_A(HIGH(100000 >> 8));
    LDH_addr_A(hPrintNumBuffer + 4);
    LD_A(HIGH(100000));  // mid
    LDH_addr_A(hPrintNumBuffer + 5);
    LD_A(LOW(100000));
    LDH_addr_A(hPrintNumBuffer + 6);
    CALL(av_PrintNum_PrintDigit);
    CALL(av_PrintNum_AdvancePointer);


five:
    XOR_A_A;  // HIGH(10000 >> 8)
    LDH_addr_A(hPrintNumBuffer + 4);
    LD_A(HIGH(10000));  // mid
    LDH_addr_A(hPrintNumBuffer + 5);
    LD_A(LOW(10000));
    LDH_addr_A(hPrintNumBuffer + 6);
    CALL(av_PrintNum_PrintDigit);
    CALL(av_PrintNum_AdvancePointer);


four:
    XOR_A_A;  // HIGH(1000 >> 8)
    LDH_addr_A(hPrintNumBuffer + 4);
    LD_A(HIGH(1000));  // mid
    LDH_addr_A(hPrintNumBuffer + 5);
    LD_A(LOW(1000));
    LDH_addr_A(hPrintNumBuffer + 6);
    CALL(av_PrintNum_PrintDigit);
    CALL(av_PrintNum_AdvancePointer);


three:
    XOR_A_A;  // HIGH(100 >> 8)
    LDH_addr_A(hPrintNumBuffer + 4);
    XOR_A_A;  // HIGH(100) // mid
    LDH_addr_A(hPrintNumBuffer + 5);
    LD_A(LOW(100));
    LDH_addr_A(hPrintNumBuffer + 6);
    CALL(av_PrintNum_PrintDigit);
    CALL(av_PrintNum_AdvancePointer);


two:
    DEC_E;
    IF_NZ goto two_skip;
    LD_A(0xf6);
    LDH_addr_A(hPrintNumBuffer + 0);

two_skip:

    LD_C(0);
    LDH_A_addr(hPrintNumBuffer + 3);

mod_10:
    CP_A(10);
    IF_C goto modded_10;
    SUB_A(10);
    INC_C;
    goto mod_10;

modded_10:

    LD_B_A;
    LDH_A_addr(hPrintNumBuffer + 0);
    OR_A_C;
    IF_NZ goto money;
    CALL(av_PrintNum_PrintLeadingZero);
    goto money_leading_zero;


money:
    CALL(av_PrintNum_PrintYen);
    PUSH_AF;
    LD_A(0xf6);
    ADD_A_C;
    LD_hl_A;
    POP_AF;
    LDH_addr_A(hPrintNumBuffer + 0);
    INC_E;
    DEC_E;
    IF_NZ goto money_leading_zero;
    INC_HL;
    LD_hl(0xf2);


money_leading_zero:
    CALL(av_PrintNum_AdvancePointer);
    CALL(av_PrintNum_PrintYen);
    LD_A(0xf6);
    ADD_A_B;
    LD_hli_A;

    POP_DE;
    POP_BC;
    RET;


PrintYen:
    PUSH_AF;
    LDH_A_addr(hPrintNumBuffer + 0);
    AND_A_A;
    IF_NZ goto stop;
    BIT_D(5);
    IF_Z goto stop;
    LD_A(0xf0);
    LD_hli_A;
    RES_D(5);


stop:
    POP_AF;
    RET;


PrintDigit:
    DEC_E;
    IF_NZ goto ok;
    LD_A(0xf6);
    LDH_addr_A(hPrintNumBuffer + 0);

ok:
    LD_C(0);

loop:
    LDH_A_addr(hPrintNumBuffer + 4);
    LD_B_A;
    LDH_A_addr(hPrintNumBuffer + 1);
    LDH_addr_A(hPrintNumBuffer + 7);
    CP_A_B;
    IF_C goto skip1;
    SUB_A_B;
    LDH_addr_A(hPrintNumBuffer + 1);
    LDH_A_addr(hPrintNumBuffer + 5);
    LD_B_A;
    LDH_A_addr(hPrintNumBuffer + 2);
    LDH_addr_A(hPrintNumBuffer + 8);
    CP_A_B;
    IF_NC goto skip2;
    LDH_A_addr(hPrintNumBuffer + 1);
    OR_A(0);
    IF_Z goto skip3;
    DEC_A;
    LDH_addr_A(hPrintNumBuffer + 1);
    LDH_A_addr(hPrintNumBuffer + 2);

skip2:
    SUB_A_B;
    LDH_addr_A(hPrintNumBuffer + 2);
    LDH_A_addr(hPrintNumBuffer + 6);
    LD_B_A;
    LDH_A_addr(hPrintNumBuffer + 3);
    LDH_addr_A(hPrintNumBuffer + 9);
    CP_A_B;
    IF_NC goto skip4;
    LDH_A_addr(hPrintNumBuffer + 2);
    AND_A_A;
    IF_NZ goto skip5;
    LDH_A_addr(hPrintNumBuffer + 1);
    AND_A_A;
    IF_Z goto skip6;
    DEC_A;
    LDH_addr_A(hPrintNumBuffer + 1);
    XOR_A_A;

skip5:
    DEC_A;
    LDH_addr_A(hPrintNumBuffer + 2);
    LDH_A_addr(hPrintNumBuffer + 3);

skip4:
    SUB_A_B;
    LDH_addr_A(hPrintNumBuffer + 3);
    INC_C;
    goto loop;

skip6:
    LDH_A_addr(hPrintNumBuffer + 8);
    LDH_addr_A(hPrintNumBuffer + 2);

skip3:
    LDH_A_addr(hPrintNumBuffer + 7);
    LDH_addr_A(hPrintNumBuffer + 1);

skip1:
    LDH_A_addr(hPrintNumBuffer + 0);
    OR_A_C;
    IF_Z goto PrintLeadingZero;
    LDH_A_addr(hPrintNumBuffer + 0);
    AND_A_A;
    IF_NZ goto done;
    BIT_D(5);
    IF_Z goto done;
    LD_A(0xf0);
    LD_hli_A;
    RES_D(5);

done:
    LD_A(0xf6);
    ADD_A_C;
    LD_hl_A;
    LDH_addr_A(hPrintNumBuffer + 0);
    INC_E;
    DEC_E;
    RET_NZ ;
    INC_HL;
    LD_hl(0xf2);
    RET;


PrintLeadingZero:
//  prints a leading zero unless they are turned off in the flags
    BIT_D(7);  // print leading zeroes?
    RET_Z ;
    LD_hl(0xf6);
    RET;


AdvancePointer:
//  increments the pointer unless leading zeroes are not being printed,
//  the number is left-aligned, and no nonzero digits have been printed yet
    BIT_D(7);  // print leading zeroes?
    IF_NZ goto inc;
    BIT_D(6);  // left alignment or right alignment?
    IF_Z goto inc;
    LDH_A_addr(hPrintNumBuffer + 0);
    AND_A_A;
    RET_Z ;

inc:
    INC_HL;
    RET;

}

static void v_PrintNum_PrintDigit_Conv(uint16_t* hl, uint16_t* de, uint8_t* d)
{
    // DEC_E;
    // IF_NZ goto ok;
    if((--(*de) & 0xff) == 0)
    {
        // LD_A(0xf6);
        // LDH_addr_A(hPrintNumBuffer + 0);
        gb_write(hPrintNumBuffer + 0, 0xf6);
    }

ok:
    // LD_C(0);
    uint8_t c = 0;
    uint8_t a, b;

    do {
        // TODO: Clean up all these gotos in this block!
        // LDH_A_addr(hPrintNumBuffer + 4);
        // LD_B_A;
        b = gb_read(hPrintNumBuffer + 4);

        // LDH_A_addr(hPrintNumBuffer + 1);
        a = gb_read(hPrintNumBuffer + 1);

        // LDH_addr_A(hPrintNumBuffer + 7);
        gb_write(hPrintNumBuffer + 7, a);

        // CP_A_B;
        // IF_C goto skip1;
        if(a < b) goto skip1;

        // SUB_A_B;
        // LDH_addr_A(hPrintNumBuffer + 1);
        gb_write(hPrintNumBuffer + 1, a - b);

        // LDH_A_addr(hPrintNumBuffer + 5);
        // LD_B_A;
        b = gb_read(hPrintNumBuffer + 5);

        // LDH_A_addr(hPrintNumBuffer + 2);
        a = gb_read(hPrintNumBuffer + 2);

        // LDH_addr_A(hPrintNumBuffer + 8);
        gb_write(hPrintNumBuffer + 8, a);
        
        // CP_A_B;
        // IF_NC goto skip2;
        if(a >= b) goto skip2;

        // LDH_A_addr(hPrintNumBuffer + 1);
        // OR_A(0);
        // IF_Z goto skip3;
        a = gb_read(hPrintNumBuffer + 1);
        if(a == 0) goto skip3;

        // DEC_A;
        // LDH_addr_A(hPrintNumBuffer + 1);
        gb_write(hPrintNumBuffer + 1, --a);

        // LDH_A_addr(hPrintNumBuffer + 2);
        a = gb_read(hPrintNumBuffer + 2);

    skip2:
        // SUB_A_B;
        // LDH_addr_A(hPrintNumBuffer + 2);
        gb_write(hPrintNumBuffer + 2, a - b);

        // LDH_A_addr(hPrintNumBuffer + 6);
        // LD_B_A;
        b = gb_read(hPrintNumBuffer + 6);

        // LDH_A_addr(hPrintNumBuffer + 3);
        a = gb_read(hPrintNumBuffer + 3);

        // LDH_addr_A(hPrintNumBuffer + 9);
        gb_write(hPrintNumBuffer + 9, a);

        // CP_A_B;
        // IF_NC goto skip4;
        if(a >= b) goto skip4;

        // LDH_A_addr(hPrintNumBuffer + 2);
        // AND_A_A;
        // IF_NZ goto skip5;
        if(gb_read(hPrintNumBuffer + 2) != 0) goto skip5;

        // LDH_A_addr(hPrintNumBuffer + 1);
        // AND_A_A;
        // IF_Z goto skip6;
        a = gb_read(hPrintNumBuffer + 1);
        if(a == 0) goto skip6;

        // DEC_A;
        // LDH_addr_A(hPrintNumBuffer + 1);
        gb_write(hPrintNumBuffer + 1, --a);

        // XOR_A_A;
        a = 0;

    skip5:
        // DEC_A;
        // LDH_addr_A(hPrintNumBuffer + 2);
        gb_write(hPrintNumBuffer + 2, --a);

        // LDH_A_addr(hPrintNumBuffer + 3);
        a = gb_read(hPrintNumBuffer + 3);

    skip4:
        // SUB_A_B;
        // LDH_addr_A(hPrintNumBuffer + 3);
        gb_write(hPrintNumBuffer + 3, a - b);
        
        // INC_C;
        c++;
    } while(1);

skip6:
    // LDH_A_addr(hPrintNumBuffer + 8);
    // LDH_addr_A(hPrintNumBuffer + 2);
    gb_write(hPrintNumBuffer + 2, gb_read(hPrintNumBuffer + 8));

skip3:
    // LDH_A_addr(hPrintNumBuffer + 7);
    // LDH_addr_A(hPrintNumBuffer + 1);
    gb_write(hPrintNumBuffer + 1, gb_read(hPrintNumBuffer + 7));

skip1:
    // LDH_A_addr(hPrintNumBuffer + 0);
    // OR_A_C;
    // IF_Z goto PrintLeadingZero;
    if((gb_read(hPrintNumBuffer + 0) | c) == 0)
    {
    //  prints a leading zero unless they are turned off in the flags
        // BIT_D(7);  // print leading zeroes?
        // RET_Z ;
        if(!bit_test(*d, 7))
            return;
        
        // LD_hl(0xf6);
        gb_write(*hl, 0xf6);

        // RET;
        return;
    }
    
    // LDH_A_addr(hPrintNumBuffer + 0);
    // AND_A_A;
    // IF_NZ goto done;
    // BIT_D(5);
    // IF_Z goto done;
    if(gb_read(hPrintNumBuffer + 0) == 0 && bit_test(*d, 5))
    {
        // LD_A(0xf0);
        // LD_hli_A;
        gb_write((*hl)++, 0xf0);

        // RES_D(5);
        bit_reset(*d, 5);
    }

    // LD_A(0xf6);
    // ADD_A_C;
    a = (0xf6 + c);

    // LD_hl_A;
    gb_write(*hl, a);

    // LDH_addr_A(hPrintNumBuffer + 0);
    gb_write(hPrintNumBuffer + 0, a);

    // INC_E;
    // DEC_E;
    // RET_NZ ;
    if((*de & 0xff) != 0)
        return;
    
    // INC_HL;
    // LD_hl(0xf2);
    gb_write(++(*hl), 0xf2);
    
    // RET;
    return;
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
uint16_t v_PrintNum_Conv(uint16_t hl, uint16_t de, uint8_t b, uint8_t c){
    // PUSH_BC;

//  increments the pointer unless leading zeroes are not being printed,
//  the number is left-aligned, and no nonzero digits have been printed yet
#define v_PrintNum_AdvancePointer() do {\
    if(!bit_test(d, 7) && bit_test(d, 6)){\
        if(gb_read(hPrintNumBuffer + 0) == 0)\
            break;\
    }\
    hl++;\
} while(0)
//     BIT_D(7);  // print leading zeroes?
//     IF_NZ goto inc;
//     BIT_D(6);  // left alignment or right alignment?
//     IF_Z goto inc;
//     LDH_A_addr(hPrintNumBuffer + 0);
//     AND_A_A;
//     RET_Z ;

// inc:
//     INC_HL;
//     RET;

    // BIT_B(5);
    // IF_Z goto main;
    if(!bit_test(b, 5)) 
    {
        // goto main
    }

    // BIT_B(7);
    // IF_NZ goto moneyflag;
    else if(bit_test(b, 7)) 
    {
    // moneyflag:
    //   //  101xxxxx or 011xxxxx
        // LD_A(0xf0);
        // LD_hli_A;
        gb_write(hl++, 0xf0);

        // RES_B(5);  // 100xxxxx or 010xxxxx
        bit_reset(b, 5);
    }

    // BIT_B(6);
    // IF_Z goto main;
    else if(!bit_test(b, 6)) 
    {
        // goto main
    }

    else 
    {
    // moneyflag:
    //   //  101xxxxx or 011xxxxx
        // LD_A(0xf0);
        // LD_hli_A;
        gb_write(hl++, 0xf0);

        // RES_B(5);  // 100xxxxx or 010xxxxx
        bit_reset(b, 5);
    }

// main:
    // XOR_A_A;
    // LDH_addr_A(hPrintNumBuffer + 0);
    // LDH_addr_A(hPrintNumBuffer + 1);
    // LDH_addr_A(hPrintNumBuffer + 2);
    gb_write(hPrintNumBuffer + 0, 0);
    gb_write(hPrintNumBuffer + 1, 0);
    gb_write(hPrintNumBuffer + 2, 0);

    // LD_A_B;
    // AND_A(0xf);
    // CP_A(1);
    // IF_Z goto byte;
    if((b & 0xf) == 1)
    {
    // byte:
        // LD_A_de;
        // LDH_addr_A(hPrintNumBuffer + 3);
        gb_write(hPrintNumBuffer + 3, gb_read(de));
    }

    // CP_A(2);
    // IF_Z goto word;
    else if((b & 0xf) == 2)
    {
    // word:
        // LD_A_de;
        // LDH_addr_A(hPrintNumBuffer + 2);
        // INC_DE;
        gb_write(hPrintNumBuffer + 2, gb_read(de++));

        // LD_A_de;
        // LDH_addr_A(hPrintNumBuffer + 3);
        gb_write(hPrintNumBuffer + 3, gb_read(de));

        // goto start;
    }

    else 
    {
    //  maximum 3 bytes
        // LD_A_de;
        // LDH_addr_A(hPrintNumBuffer + 1);
        // INC_DE;
        gb_write(hPrintNumBuffer + 1, gb_read(de++));

        // LD_A_de;
        // LDH_addr_A(hPrintNumBuffer + 2);
        // INC_DE;
        gb_write(hPrintNumBuffer + 2, gb_read(de++));

        // LD_A_de;
        // LDH_addr_A(hPrintNumBuffer + 3);
        gb_write(hPrintNumBuffer + 3, gb_read(de));

        // goto start;
    }

// start:
    // PUSH_DE;
    uint8_t a = 0;

    // LD_D_B;
    uint8_t d = b;

    // LD_A_C;
    // SWAP_A;
    // AND_A(0xf);
    // LD_E_A;
    uint8_t e = ((c << 4) | (c >> 4)) & 0xf;
    
    // LD_A_C;
    // AND_A(0xf);
    // LD_B_A;
    uint8_t b2 = c & 0xf;

    // LD_C(0);
    // CP_A(2);
    // IF_Z goto two;
    switch(b2)
    {
    // CP_A(3);
    // IF_Z goto three;
    // CP_A(4);
    // IF_Z goto four;
    // CP_A(5);
    // IF_Z goto five;
    // CP_A(6);
    // IF_Z goto six;
    default:
    //  seven
        // LD_A(HIGH(1000000 >> 8));
        // LDH_addr_A(hPrintNumBuffer + 4);
        gb_write(hPrintNumBuffer + 4, HIGH(1000000 >> 8));

        // LD_A(HIGH(1000000));  // mid
        // LDH_addr_A(hPrintNumBuffer + 5);
        gb_write(hPrintNumBuffer + 5, HIGH(1000000));

        // LD_A(LOW(1000000));
        // LDH_addr_A(hPrintNumBuffer + 6);
        gb_write(hPrintNumBuffer + 6, LOW(1000000));

        // CALL(av_PrintNum_PrintDigit);
        v_PrintNum_PrintDigit_Conv(&hl, &de, &d);

        // CALL(av_PrintNum_AdvancePointer);
        v_PrintNum_AdvancePointer();

        // fallthrough
    case 6:
    // six:
        // LD_A(HIGH(100000 >> 8));
        // LDH_addr_A(hPrintNumBuffer + 4);
        gb_write(hPrintNumBuffer + 4, HIGH(100000 >> 8));

        // LD_A(HIGH(100000));  // mid
        // LDH_addr_A(hPrintNumBuffer + 5);
        gb_write(hPrintNumBuffer + 5, HIGH(100000));

        // LD_A(LOW(100000));
        // LDH_addr_A(hPrintNumBuffer + 6);
        gb_write(hPrintNumBuffer + 6, LOW(100000));

        // CALL(av_PrintNum_PrintDigit);
        v_PrintNum_PrintDigit_Conv(&hl, &de, &d);

        // CALL(av_PrintNum_AdvancePointer);
        v_PrintNum_AdvancePointer();

        // fallthrough
    case 5:
    // five:
        // XOR_A_A;  // HIGH(10000 >> 8)
        // LDH_addr_A(hPrintNumBuffer + 4);
        gb_write(hPrintNumBuffer + 4, 0); // HIGH(10000 >> 8)

        // LD_A(HIGH(10000));  // mid
        // LDH_addr_A(hPrintNumBuffer + 5);
        gb_write(hPrintNumBuffer + 5, HIGH(10000));

        // LD_A(LOW(10000));
        // LDH_addr_A(hPrintNumBuffer + 6);
        gb_write(hPrintNumBuffer + 6, LOW(10000));

        // CALL(av_PrintNum_PrintDigit);
        v_PrintNum_PrintDigit_Conv(&hl, &de, &d);

        // CALL(av_PrintNum_AdvancePointer);
        v_PrintNum_AdvancePointer();

        // fallthrough
    case 4:
    // four:
        // XOR_A_A;  // HIGH(1000 >> 8)
        // LDH_addr_A(hPrintNumBuffer + 4);
        gb_write(hPrintNumBuffer + 4, 0); // HIGH(1000 >> 8)

        // LD_A(HIGH(1000));  // mid
        // LDH_addr_A(hPrintNumBuffer + 5);
        gb_write(hPrintNumBuffer + 5, HIGH(1000));

        // LD_A(LOW(1000));
        // LDH_addr_A(hPrintNumBuffer + 6);
        gb_write(hPrintNumBuffer + 5, LOW(1000));

        // CALL(av_PrintNum_PrintDigit);
        v_PrintNum_PrintDigit_Conv(&hl, &de, &d);

        // CALL(av_PrintNum_AdvancePointer);
        v_PrintNum_AdvancePointer();

    // fallthrough
    case 3:
    // three:
        // XOR_A_A;  // HIGH(100 >> 8)
        // LDH_addr_A(hPrintNumBuffer + 4);
        gb_write(hPrintNumBuffer + 4, 0); // HIGH(100 >> 8)

        // XOR_A_A;  // HIGH(100) // mid
        // LDH_addr_A(hPrintNumBuffer + 5);
        gb_write(hPrintNumBuffer + 5, 0); // HIGH(100)

        // LD_A(LOW(100));
        // LDH_addr_A(hPrintNumBuffer + 6);
        gb_write(hPrintNumBuffer + 6, LOW(100)); // HIGH(100)

        // CALL(av_PrintNum_PrintDigit);
        v_PrintNum_PrintDigit_Conv(&hl, &de, &d);

        // CALL(av_PrintNum_AdvancePointer);
        v_PrintNum_AdvancePointer();

        // fallthrough
    case 2:
    // two:
        // DEC_E;
        // IF_NZ goto two_skip;
        e--;
        if(e == 0)
        {
            // LD_A(0xf6);
            // LDH_addr_A(hPrintNumBuffer + 0);
            gb_write(hPrintNumBuffer + 0, 0xf6);
        }

    // two_skip:

        // LD_C(0);
        // LDH_A_addr(hPrintNumBuffer + 3);
        c = 0;
        a = gb_read(hPrintNumBuffer + 3);
        break;
    }

mod_10:
    while(a >= 10) 
    {
        // CP_A(10);
        // IF_C goto modded_10;
        // SUB_A(10);
        // INC_C;
        a -= 10;
        c++;
    }
    // goto mod_10;

modded_10:

    // LD_B_A;
    // LDH_A_addr(hPrintNumBuffer + 0);
    // OR_A_C;
    // IF_NZ goto money;
    if((gb_read(hPrintNumBuffer + 0) | c) != 0)
    {
    // money:
        // CALL(av_PrintNum_PrintYen);
        do {
        // PrintYen:
            // PUSH_AF;
            // LDH_A_addr(hPrintNumBuffer + 0);
            // AND_A_A;
            // IF_NZ goto stop;
            // BIT_D(5);
            // IF_Z goto stop;
            if(gb_read(hPrintNumBuffer + 0) == 0 && bit_test(d, 5))
            {
                // LD_A(0xf0);
                // LD_hli_A;
                gb_write(hl++, 0xf0);
                // RES_D(5);
                bit_reset(d, 5);
            }
        // stop:
            // POP_AF;
            // RET;
        } while(0);
        // PUSH_AF;
        // LD_A(0xf6);
        // ADD_A_C;
        // LD_hl_A;
        // POP_AF;
        gb_write(hl, c + 0xf6);

        // LDH_addr_A(hPrintNumBuffer + 0);
        gb_write(hPrintNumBuffer + 0, a);

        // INC_E;
        // DEC_E;
        // IF_NZ goto money_leading_zero;
        if(e == 0)
        {
            // INC_HL;
            // LD_hl(0xf2);
            gb_write(++hl, 0xf2);
        }
    }
    else 
    {
        // CALL(av_PrintNum_PrintLeadingZero);
    // PrintLeadingZero:
    //  prints a leading zero unless they are turned off in the flags
        // BIT_D(7);  // print leading zeroes?
        // RET_Z ;
        if(bit_test(d, 7))
        {
            // LD_hl(0xf6);
            // RET;
            gb_write(hl, 0xf6);
        }
        // goto money_leading_zero;
    }


// money_leading_zero:
    // CALL(av_PrintNum_AdvancePointer);
    v_PrintNum_AdvancePointer();

    // CALL(av_PrintNum_PrintYen);
    do {
    // PrintYen:
        // PUSH_AF;
        // LDH_A_addr(hPrintNumBuffer + 0);
        // AND_A_A;
        // IF_NZ goto stop;
        // BIT_D(5);
        // IF_Z goto stop;
        if(gb_read(hPrintNumBuffer + 0) == 0 && bit_test(d, 5))
        {
            // LD_A(0xf0);
            // LD_hli_A;
            gb_write(hl++, 0xf0);
            // RES_D(5);
            bit_reset(d, 5);
        }
    // stop:
        // POP_AF;
        // RET;
    } while(0);
    // LD_A(0xf6);
    // ADD_A_B;
    // LD_hli_A;
    gb_write(hl++, b + 0xf6);

    // POP_DE;
    // POP_BC;
    // RET;
    return hl;
}

static void v_PrintNum_PrintDigit_Conv2(uint8_t** hl, uint8_t* d, uint8_t* e)
{
    // DEC_E;
    // IF_NZ goto ok;
    (*e)--;
    if(*e == 0)
    {
        // LD_A(0xf6);
        // LDH_addr_A(hPrintNumBuffer + 0);
        hram->hPrintNumBuffer[0] = CHAR_0;
    }

ok:
    // LD_C(0);
    uint8_t c = 0;
    uint8_t a, b;

    do {
        // TODO: Clean up all these gotos in this block!
        // LDH_A_addr(hPrintNumBuffer + 4);
        // LD_B_A;
        b = hram->hPrintNumBuffer[4];

        // LDH_A_addr(hPrintNumBuffer + 1);
        a = hram->hPrintNumBuffer[1];

        // LDH_addr_A(hPrintNumBuffer + 7);
        hram->hPrintNumBuffer[7] = a;

        // CP_A_B;
        // IF_C goto skip1;
        if(a < b) goto skip1;

        // SUB_A_B;
        // LDH_addr_A(hPrintNumBuffer + 1);
        hram->hPrintNumBuffer[1] = a - b;

        // LDH_A_addr(hPrintNumBuffer + 5);
        // LD_B_A;
        b = hram->hPrintNumBuffer[5];

        // LDH_A_addr(hPrintNumBuffer + 2);
        a = hram->hPrintNumBuffer[2];

        // LDH_addr_A(hPrintNumBuffer + 8);
        hram->hPrintNumBuffer[8] = a;
        
        // CP_A_B;
        // IF_NC goto skip2;
        if(a >= b) goto skip2;

        // LDH_A_addr(hPrintNumBuffer + 1);
        // OR_A(0);
        // IF_Z goto skip3;
        a = hram->hPrintNumBuffer[1];
        if(a == 0) goto skip3;

        // DEC_A;
        // LDH_addr_A(hPrintNumBuffer + 1);
        hram->hPrintNumBuffer[1] = --a;

        // LDH_A_addr(hPrintNumBuffer + 2);
        a = hram->hPrintNumBuffer[2];

    skip2:
        // SUB_A_B;
        // LDH_addr_A(hPrintNumBuffer + 2);
        hram->hPrintNumBuffer[2] = a - b;

        // LDH_A_addr(hPrintNumBuffer + 6);
        // LD_B_A;
        b = hram->hPrintNumBuffer[6];

        // LDH_A_addr(hPrintNumBuffer + 3);
        a = hram->hPrintNumBuffer[3];

        // LDH_addr_A(hPrintNumBuffer + 9);
        hram->hPrintNumBuffer[9] = a;

        // CP_A_B;
        // IF_NC goto skip4;
        if(a >= b) goto skip4;

        // LDH_A_addr(hPrintNumBuffer + 2);
        // AND_A_A;
        // IF_NZ goto skip5;
        a = hram->hPrintNumBuffer[2];
        if(a != 0) goto skip5;

        // LDH_A_addr(hPrintNumBuffer + 1);
        // AND_A_A;
        // IF_Z goto skip6;
        a = hram->hPrintNumBuffer[1];
        if(a == 0) goto skip6;

        // DEC_A;
        // LDH_addr_A(hPrintNumBuffer + 1);
        hram->hPrintNumBuffer[1] = --a;

        // XOR_A_A;
        a = 0;

    skip5:
        // DEC_A;
        // LDH_addr_A(hPrintNumBuffer + 2);
        hram->hPrintNumBuffer[2] = --a;

        // LDH_A_addr(hPrintNumBuffer + 3);
        a = hram->hPrintNumBuffer[3];

    skip4:
        // SUB_A_B;
        // LDH_addr_A(hPrintNumBuffer + 3);
        hram->hPrintNumBuffer[3] = a - b;
        
        // INC_C;
        c++;
    } while(1);

skip6:
    // LDH_A_addr(hPrintNumBuffer + 8);
    // LDH_addr_A(hPrintNumBuffer + 2);
    hram->hPrintNumBuffer[2] = hram->hPrintNumBuffer[8];

skip3:
    // LDH_A_addr(hPrintNumBuffer + 7);
    // LDH_addr_A(hPrintNumBuffer + 1);
    hram->hPrintNumBuffer[1] = hram->hPrintNumBuffer[7];

skip1:
    // LDH_A_addr(hPrintNumBuffer + 0);
    // OR_A_C;
    // IF_Z goto PrintLeadingZero;
    if((hram->hPrintNumBuffer[0] | c) == 0)
    {
    //  prints a leading zero unless they are turned off in the flags
        // BIT_D(7);  // print leading zeroes?
        // RET_Z ;
        if(!bit_test(*d, PRINTNUM_LEADINGZEROS_F))
            return;
        
        // LD_hl(0xf6);
        *(*hl) = CHAR_0;
        // printf("0");

        // RET;
        return;
    }
    
    // LDH_A_addr(hPrintNumBuffer + 0);
    // AND_A_A;
    // IF_NZ goto done;
    // BIT_D(5);
    // IF_Z goto done;
    if(hram->hPrintNumBuffer[0] == 0 && bit_test(*d, PRINTNUM_MONEY_F))
    {
        // LD_A(0xf0);
        // LD_hli_A;
        *((*hl)++) = CHAR_MONEY_ICON;
        // printf("$_");

        // RES_D(5);
        bit_reset(*d, PRINTNUM_MONEY_F);
    }

    // LD_A(0xf6);
    // ADD_A_C;
    a = (CHAR_0 + c);

    // LD_hl_A;
    *(*hl) = a;
    // printf("%c", c + '0');

    // LDH_addr_A(hPrintNumBuffer + 0);
    hram->hPrintNumBuffer[0] = a;

    // INC_E;
    // DEC_E;
    // RET_NZ ;
    if(*e != 0)
        return;
    
    // INC_HL;
    ++(*hl);
    // LD_hl(0xf2);
    *(*hl) = CHAR_DOT;
    // printf("_.");
    
    // RET;
    return;
}

#undef v_PrintNum_AdvancePointer

//  increments the pointer unless leading zeroes are not being printed,
//  the number is left-aligned, and no nonzero digits have been printed yet
static void v_PrintNum_AdvancePointer(uint8_t** hl, uint8_t d) {
    if(bit_test(d, PRINTNUM_LEADINGZEROS_F) || !bit_test(d, PRINTNUM_LEFTALIGN_F)) {
        (*hl)++;
        // printf("_");
        return;
    }
    if(hram->hPrintNumBuffer[0] == 0) {
        // printf("-");
        return;
    }
    (*hl)++;
    // printf("_");
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
uint8_t* v_PrintNum_Conv2(uint8_t* hl, const uint8_t* de, uint8_t b, uint8_t c){
    // PUSH_BC;
#define PRINT_DEBUG_PRINTNUM_CALL 0
#if PRINT_DEBUG_PRINTNUM_CALL
    switch(b & 0xf) {
        case 1: printf("%s: Printing %d digits of %u\n", __func__, c & 0xf, de[0]); break;
        case 2: printf("%s: Printing %d digits of %u\n", __func__, c & 0xf, (de[1] + (de[0] << 8))); break;
        case 3: printf("%s: Printing %d digits of %u\n", __func__, c & 0xf, (de[2] + (de[1] << 8) + (de[0] << 16))); break;
        case 4: printf("%s: Printing %d digits of %u\n", __func__, c & 0xf, (de[3] + (de[2] << 8) + (de[1] << 16) + (de[0] << 24))); break;
    }
#endif
//  increments the pointer unless leading zeroes are not being printed,
//  the number is left-aligned, and no nonzero digits have been printed yet
// #define v_PrintNum_AdvancePointer() do {
//     if(!(!bit_test(d, PRINTNUM_LEADINGZEROS_F) && bit_test(d, PRINTNUM_LEFTALIGN_F) && hram->hPrintNumBuffer[0] == 0)){
//         hl++;
//     }
// } while(0)
//     BIT_D(7);  // print leading zeroes?
//     IF_NZ goto inc;
//     BIT_D(6);  // left alignment or right alignment?
//     IF_Z goto inc;
//     LDH_A_addr(hPrintNumBuffer + 0);
//     AND_A_A;
//     RET_Z ;

// inc:
//     INC_HL;
//     RET;

    // BIT_B(5);
    // IF_Z goto main;
    if(!bit_test(b, PRINTNUM_MONEY_F)) 
    {
        // goto main
    }

    // BIT_B(7);
    // IF_NZ goto moneyflag;
    else if(bit_test(b, PRINTNUM_LEADINGZEROS_F)) 
    {
    // moneyflag:
    //   //  101xxxxx or 011xxxxx
        // LD_A(0xf0);
        // LD_hli_A;
        *(hl++) = 0xf0;
        // printf("$_");

        // RES_B(5);  // 100xxxxx or 010xxxxx
        bit_reset(b, PRINTNUM_MONEY_F);
    }

    // BIT_B(6);
    // IF_Z goto main;
    else if(!bit_test(b, PRINTNUM_LEFTALIGN_F)) 
    {
        // goto main
    }

    else 
    {
    // moneyflag:
    //   //  101xxxxx or 011xxxxx
        // LD_A(0xf0);
        // LD_hli_A;
        *(hl++) = CHAR_MONEY_ICON;

        // RES_B(5);  // 100xxxxx or 010xxxxx
        bit_reset(b, PRINTNUM_MONEY_F);
    }

// main:
    // XOR_A_A;
    // LDH_addr_A(hPrintNumBuffer + 0);
    // LDH_addr_A(hPrintNumBuffer + 1);
    // LDH_addr_A(hPrintNumBuffer + 2);
    hram->hPrintNumBuffer[0] = 0;
    hram->hPrintNumBuffer[1] = 0;
    hram->hPrintNumBuffer[2] = 0;

    // LD_A_B;
    // AND_A(0xf);
    // CP_A(1);
    // IF_Z goto byte;
    if((b & 0xf) == 1)
    {
    // byte:
        // LD_A_de;
        // LDH_addr_A(hPrintNumBuffer + 3);
        hram->hPrintNumBuffer[3] = *(de);
    }

    // CP_A(2);
    // IF_Z goto word;
    else if((b & 0xf) == 2)
    {
    // word:
        // LD_A_de;
        // LDH_addr_A(hPrintNumBuffer + 2);
        // INC_DE;
        hram->hPrintNumBuffer[2] = *(de++);

        // LD_A_de;
        // LDH_addr_A(hPrintNumBuffer + 3);
        hram->hPrintNumBuffer[3] = *(de);

        // goto start;
    }

    else 
    {
    //  maximum 3 bytes
        // LD_A_de;
        // LDH_addr_A(hPrintNumBuffer + 1);
        // INC_DE;
        hram->hPrintNumBuffer[1] = *(de++);

        // LD_A_de;
        // LDH_addr_A(hPrintNumBuffer + 2);
        // INC_DE;
        hram->hPrintNumBuffer[2] = *(de++);

        // LD_A_de;
        // LDH_addr_A(hPrintNumBuffer + 3);
        hram->hPrintNumBuffer[3] = *(de);

        // goto start;
    }

// start:
    // PUSH_DE;
    uint8_t a = 0;

    // LD_D_B;
    uint8_t d = b;

    // LD_A_C;
    // SWAP_A;
    // AND_A(0xf);
    // LD_E_A;
    uint8_t e = (c >> 4) & 0xf;
    
    // LD_A_C;
    // AND_A(0xf);
    // LD_B_A;
    uint8_t b2 = c & 0xf;

    // LD_C(0);
    // CP_A(2);
    // IF_Z goto two;
    switch(b2)
    {
    // CP_A(3);
    // IF_Z goto three;
    // CP_A(4);
    // IF_Z goto four;
    // CP_A(5);
    // IF_Z goto five;
    // CP_A(6);
    // IF_Z goto six;
    default:
    //  seven
        // LD_A(HIGH(1000000 >> 8));
        // LDH_addr_A(hPrintNumBuffer + 4);
        hram->hPrintNumBuffer[4] = HIGH(1000000 >> 8);

        // LD_A(HIGH(1000000));  // mid
        // LDH_addr_A(hPrintNumBuffer + 5);
        hram->hPrintNumBuffer[5] = HIGH(1000000);

        // LD_A(LOW(1000000));
        // LDH_addr_A(hPrintNumBuffer + 6);
        hram->hPrintNumBuffer[6] = LOW(1000000);

        // CALL(av_PrintNum_PrintDigit);
        v_PrintNum_PrintDigit_Conv2(&hl, &d, &e);

        // CALL(av_PrintNum_AdvancePointer);
        v_PrintNum_AdvancePointer(&hl, d);

        // fallthrough
    case 6:
    // six:
        // LD_A(HIGH(100000 >> 8));
        // LDH_addr_A(hPrintNumBuffer + 4);
        hram->hPrintNumBuffer[4] = HIGH(100000 >> 8);

        // LD_A(HIGH(100000));  // mid
        // LDH_addr_A(hPrintNumBuffer + 5);
        hram->hPrintNumBuffer[5] = HIGH(100000);

        // LD_A(LOW(100000));
        // LDH_addr_A(hPrintNumBuffer + 6);
        hram->hPrintNumBuffer[6] = LOW(100000);

        // CALL(av_PrintNum_PrintDigit);
        v_PrintNum_PrintDigit_Conv2(&hl, &d, &e);

        // CALL(av_PrintNum_AdvancePointer);
        v_PrintNum_AdvancePointer(&hl, d);

        // fallthrough
    case 5:
    // five:
        // XOR_A_A;  // HIGH(10000 >> 8)
        // LDH_addr_A(hPrintNumBuffer + 4);
        hram->hPrintNumBuffer[4] = 0; // HIGH(10000 >> 8)

        // LD_A(HIGH(10000));  // mid
        // LDH_addr_A(hPrintNumBuffer + 5);
        hram->hPrintNumBuffer[5] = HIGH(10000);

        // LD_A(LOW(10000));
        // LDH_addr_A(hPrintNumBuffer + 6);
        hram->hPrintNumBuffer[6] = LOW(10000);

        // CALL(av_PrintNum_PrintDigit);
        v_PrintNum_PrintDigit_Conv2(&hl, &d, &e);

        // CALL(av_PrintNum_AdvancePointer);
        v_PrintNum_AdvancePointer(&hl, d);

        // fallthrough
    case 4:
    // four:
        // XOR_A_A;  // HIGH(1000 >> 8)
        // LDH_addr_A(hPrintNumBuffer + 4);
        hram->hPrintNumBuffer[4] = 0; // HIGH(1000 >> 8)

        // LD_A(HIGH(1000));  // mid
        // LDH_addr_A(hPrintNumBuffer + 5);
        hram->hPrintNumBuffer[5] = HIGH(1000);

        // LD_A(LOW(1000));
        // LDH_addr_A(hPrintNumBuffer + 6);
        hram->hPrintNumBuffer[6] = LOW(1000);

        // CALL(av_PrintNum_PrintDigit);
        v_PrintNum_PrintDigit_Conv2(&hl, &d, &e);

        // CALL(av_PrintNum_AdvancePointer);
        v_PrintNum_AdvancePointer(&hl, d);

    // fallthrough
    case 3:
    // three:
        // XOR_A_A;  // HIGH(100 >> 8)
        // LDH_addr_A(hPrintNumBuffer + 4);
        hram->hPrintNumBuffer[4] = 0; // HIGH(100 >> 8)

        // XOR_A_A;  // HIGH(100) // mid
        // LDH_addr_A(hPrintNumBuffer + 5);
        hram->hPrintNumBuffer[5] = 0; // HIGH(100)

        // LD_A(LOW(100));
        // LDH_addr_A(hPrintNumBuffer + 6);
        hram->hPrintNumBuffer[6] = LOW(100); // LOW(100)

        // CALL(av_PrintNum_PrintDigit);
        v_PrintNum_PrintDigit_Conv2(&hl, &d, &e);

        // CALL(av_PrintNum_AdvancePointer);
        v_PrintNum_AdvancePointer(&hl, d);

        // fallthrough
    case 2:
    // two:
        // DEC_E;
        // IF_NZ goto two_skip;
        e--;
        if(e == 0)
        {
            // LD_A(0xf6);
            // LDH_addr_A(hPrintNumBuffer + 0);
            hram->hPrintNumBuffer[0] = CHAR_0;
        }

    // two_skip:

        // LD_C(0);
        // LDH_A_addr(hPrintNumBuffer + 3);
        c = 0;
        a = hram->hPrintNumBuffer[3];
        break;
    }

mod_10:
    // while(a >= 10) 
    // {
        // CP_A(10);
        // IF_C goto modded_10;
        // SUB_A(10);
        // INC_C;
        // a -= 10;
        // c++;
    // }
    // goto mod_10;
    c = a / 10;

modded_10:

    // LD_B_A;
    a %= 10;
    b = a;
    // LDH_A_addr(hPrintNumBuffer + 0);
    a = hram->hPrintNumBuffer[0] | c;
    // OR_A_C;
    // IF_NZ goto money;
    if(a != 0)
    {
    // money:
        // CALL(av_PrintNum_PrintYen);
        do {
        // PrintYen:
            // PUSH_AF;
            // LDH_A_addr(hPrintNumBuffer + 0);
            // AND_A_A;
            // IF_NZ goto stop;
            // BIT_D(5);
            // IF_Z goto stop;
            if(hram->hPrintNumBuffer[0] == 0 && bit_test(d, PRINTNUM_MONEY_F))
            {
                // LD_A(0xf0);
                // LD_hli_A;
                *(hl++) = CHAR_MONEY_ICON;
                // printf("$_");
                // RES_D(5);
                bit_reset(d, PRINTNUM_MONEY_F);
            }
        // stop:
            // POP_AF;
            // RET;
        } while(0);
        // PUSH_AF;
        // LD_A(0xf6);
        // ADD_A_C;
        // LD_hl_A;
        // POP_AF;
        *(hl) = c + CHAR_0;
        // printf("%c^", c + '0');

        // LDH_addr_A(hPrintNumBuffer + 0);
        hram->hPrintNumBuffer[0] = a;

        // INC_E;
        // DEC_E;
        // IF_NZ goto money_leading_zero;
        if(e == 0)
        {
            // INC_HL;
            hl++;
            // LD_hl(0xf2);
            *hl = CHAR_DOT;
            // printf("_.");
        }
    }
    else 
    {
        // CALL(av_PrintNum_PrintLeadingZero);
    // PrintLeadingZero:
    //  prints a leading zero unless they are turned off in the flags
        // BIT_D(7);  // print leading zeroes?
        // RET_Z ;
        if(bit_test(d, PRINTNUM_LEADINGZEROS_F))
        {
            // LD_hl(0xf6);
            // RET;
            *(hl) = CHAR_0;
            // printf("0*");
        }
        // goto money_leading_zero;
    }


// money_leading_zero:
    // CALL(av_PrintNum_AdvancePointer);
    v_PrintNum_AdvancePointer(&hl, d);

    // CALL(av_PrintNum_PrintYen);
    do {
    // PrintYen:
        // PUSH_AF;
        // LDH_A_addr(hPrintNumBuffer + 0);
        // AND_A_A;
        // IF_NZ goto stop;
        // BIT_D(5);
        // IF_Z goto stop;
        if(hram->hPrintNumBuffer[0] == 0 && bit_test(d, PRINTNUM_MONEY_F))
        {
            // LD_A(0xf0);
            // LD_hli_A;
            *(hl++) = CHAR_MONEY_ICON;
            // printf("$_");
            // RES_D(5);
            bit_reset(d, PRINTNUM_MONEY_F);
        }
    // stop:
        // POP_AF;
        // RET;
    } while(0);
    // LD_A(0xf6);
    // ADD_A_B;
    // LD_hli_A;
    *(hl++) = b + CHAR_0;
    // printf("%c_\n", b + '0');

    // POP_DE;
    // POP_BC;
    // RET;
    return hl;
}
