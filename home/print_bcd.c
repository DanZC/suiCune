#include "../constants.h"
#include "print_bcd.h"
#include "../charmap.h"
#include "print_text.h"

//  function to print a BCD (Binary-coded decimal) number
//  de = address of BCD number
//  hl = destination address
//  c = flags and length
//  bit 7: if set, do not print leading zeroes
//         if unset, print leading zeroes
//  bit 6: if set, left-align the string (do not pad empty digits with spaces)
//         if unset, right-align the string
//  bit 5: if set, print currency symbol at the beginning of the string
//         if unset, do not print the currency symbol
//  bits 0-4: length of BCD number in bytes
//  Note that bits 5 and 7 are modified during execution. The above reflects
//  their meaning at the beginning of the functions's execution.
uint8_t* PrintBCDNumber(uint8_t* hl, const uint8_t* de, uint8_t c){
    // LD_B_C;  // save flags in b
    // RES_C(PRINTNUM_LEADINGZEROS_F);
    // RES_C(PRINTNUM_LEFTALIGN_F);
    // RES_C(PRINTNUM_MONEY_F);  // c now holds the length
    uint8_t b = c;
    c &= 0x1f;
    // BIT_B(PRINTNUM_MONEY_F);
    // IF_Z goto loop;
    // BIT_B(PRINTNUM_LEADINGZEROS_F);
    // IF_NZ goto loop;  // skip currency symbol
    if(bit_test(b, PRINTNUM_MONEY_F) && !bit_test(b, PRINTNUM_LEADINGZEROS_F))
        // LD_hl(0xf0);
        // INC_HL;
        *(hl++) = 0xf0;

    do {
    // loop:
        // LD_A_de;
        uint8_t digit = *(de++);
        // SWAP_A;
        hl = PrintBCDDigit((digit >> 4) & 0xf, &b, hl);
        // CALL(aPrintBCDDigit);  // print upper digit
        // LD_A_de;
        hl = PrintBCDDigit(digit & 0xf, &b, hl);
        // CALL(aPrintBCDDigit);  // print lower digit
        // INC_DE;
        // DEC_C;
        // IF_NZ goto loop;
    } while(--c != 0);
    // BIT_B(PRINTNUM_LEADINGZEROS_F);
    // IF_Z goto done;  // if so, we are done
    if(!bit_test(b, PRINTNUM_LEADINGZEROS_F))
        return hl;
//  every digit of the BCD number is zero
    // BIT_B(PRINTNUM_LEFTALIGN_F);
    // IF_NZ goto skipLeftAlignmentAdjustment;
    if(!bit_test(b, PRINTNUM_LEFTALIGN_F)) {
    //  the string is left-aligned
        // DEC_HL;
        --hl;
    }
// skipLeftAlignmentAdjustment:
    // BIT_B(PRINTNUM_MONEY_F);
    // IF_Z goto skipCurrencySymbol;
    if(bit_test(b, PRINTNUM_MONEY_F)) {
        // LD_hl(0xf0);  // currency symbol
        // INC_HL;
        *(hl++) = 0xf0;  // currency symbol
    }

// skipCurrencySymbol:
    // LD_hl(0xf6);
    // CALL(aPrintLetterDelay);
    // INC_HL;
    *(hl++) = 0xf6;
    PrintLetterDelay();

// done:
    // RET;
    return hl;
}

uint8_t* PrintBCDDigit(uint8_t a, uint8_t* b, uint8_t* hl){
    // AND_A(0b00001111);
    // AND_A_A;
    // IF_Z goto zeroDigit;
    if(a != 0) {
    //  nonzero digit
        // BIT_B(PRINTNUM_LEADINGZEROS_F);  // have any non-space characters been printed?
        // IF_Z goto outputDigit;
        if(bit_test(*b, PRINTNUM_LEADINGZEROS_F)) {
        //  if bit 7 is set, then no numbers have been printed yet
            // BIT_B(PRINTNUM_MONEY_F);
            // IF_Z goto skipCurrencySymbol;
            if(bit_test(*b, PRINTNUM_MONEY_F)) {
                // LD_hl(0xf0);
                // INC_HL;
                *(hl++) = 0xf0;
                // RES_B(PRINTNUM_MONEY_F);
                *b &= ~(1 << PRINTNUM_MONEY_F);
            }

        // skipCurrencySymbol:
            // RES_B(PRINTNUM_LEADINGZEROS_F);  // unset 7 to indicate that a nonzero digit has been reached
            *b &= ~(1 << PRINTNUM_LEADINGZEROS_F);
        }

    // outputDigit:
        // ADD_A(0xf6);
        // LD_hli_A;
        // JP(mPrintLetterDelay);
        a += 0xf6;
        *(hl++) = a;
        PrintLetterDelay();
        return hl;
    }

// zeroDigit:
    // BIT_B(PRINTNUM_LEADINGZEROS_F);  // either printing leading zeroes or already reached a nonzero digit?
    // IF_Z goto outputDigit;  // if so, print a zero digit
    if(!bit_test(*b, PRINTNUM_LEADINGZEROS_F)) {
        a += 0xf6;
        *(hl++) = a;
        PrintLetterDelay();
        return hl;
    }
    // BIT_B(PRINTNUM_LEFTALIGN_F);
    // RET_NZ ;
    if(bit_test(*b, PRINTNUM_LEFTALIGN_F))
        return hl;
    // LD_A(0x7f);
    // LD_hli_A;  // if right-aligned, "print" a space by advancing the pointer
    *(hl++) = CHAR_SPACE;
    // RET;
    return hl;
}