#include "../../constants.h"
#include "math.h"

//  hMultiplier is one byte.
void v_Multiply(void){
    // LD_A(8);
    // LD_B_A;
    uint8_t b = 8;
    uint8_t c;

    // XOR_A_A;
    // LDH_addr_A(hMultiplicand - 1);
    // LDH_addr_A(hMathBuffer + 1);
    // LDH_addr_A(hMathBuffer + 2);
    // LDH_addr_A(hMathBuffer + 3);
    // LDH_addr_A(hMathBuffer + 4);
    hram.unused_41 = 0; // hMultiplicand - 1
    hram.hMathBuffer[1] = 0;
    hram.hMathBuffer[2] = 0;
    hram.hMathBuffer[3] = 0;
    hram.hMathBuffer[4] = 0;

    uint8_t carry = 0;
    do {
        // LDH_A_addr(hMultiplier);
        uint8_t a = hram.hMultiplier;

        // SRL_A;
        // LDH_addr_A(hMultiplier);
        hram.hMultiplier = a >> 1;

        // IF_NC goto next;
        if(a & 1)
        {
            // LDH_A_addr(hMathBuffer + 4);
            // LD_C_A;
            c = hram.hMathBuffer[4];

            // LDH_A_addr(hMultiplicand + 2);
            // ADD_A_C;
            a = hram.hMultiplicand[2];
            carry = ((uint16_t)a + (uint16_t)c) > 0xff? 1: 0;

            // LDH_addr_A(hMathBuffer + 4);
            hram.hMathBuffer[4] = a + c;

            // LDH_A_addr(hMathBuffer + 3);
            // LD_C_A;
            c = hram.hMathBuffer[3];

            // LDH_A_addr(hMultiplicand + 1);
            // ADC_A_C;
            a = hram.hMultiplicand[1];
            carry = ((uint16_t)a + (uint16_t)c + (uint16_t)carry) > 0xff? 1: 0;
            
            // LDH_addr_A(hMathBuffer + 3);
            hram.hMathBuffer[3] = a + c + carry;

            // LDH_A_addr(hMathBuffer + 2);
            // LD_C_A;
            c = hram.hMathBuffer[2];

            // LDH_A_addr(hMultiplicand + 0);
            // ADC_A_C;
            a = hram.hMultiplicand[0];
            carry = ((uint16_t)a + (uint16_t)c + (uint16_t)carry) > 0xff? 1: 0;

            // LDH_addr_A(hMathBuffer + 2);
            hram.hMathBuffer[2] = a + c + carry;

            // LDH_A_addr(hMathBuffer + 1);
            // LD_C_A;
            c = hram.hMathBuffer[1];

            // LDH_A_addr(hMultiplicand - 1);
            // ADC_A_C;
            a = hram.unused_41; // hMultiplicand - 1
            carry = ((uint16_t)a + (uint16_t)c + (uint16_t)carry) > 0xff? 1: 0;

            // LDH_addr_A(hMathBuffer + 1);
            hram.hMathBuffer[1] = a + c + carry;
        }

        // DEC_B;
        // IF_Z goto done;
        if(--b == 0) 
            break;

    //  hMultiplicand <<= 1

        // LDH_A_addr(hMultiplicand + 2);
        // ADD_A_A;
        // LDH_addr_A(hMultiplicand + 2);
        a = hram.hMultiplicand[2];
        carry = ((uint16_t)a + (uint16_t)a) > 0xff? 1: 0;
        hram.hMultiplicand[2] = a + a;

        // LDH_A_addr(hMultiplicand + 1);
        a = hram.hMultiplicand[1];

        // RLA;
        {
            uint16_t temp = a;
            a = (a << 1) | carry;
            carry = (temp >> 7) & 0x01;
        }

        // LDH_addr_A(hMultiplicand + 1);
        hram.hMultiplicand[1] = a;

        // LDH_A_addr(hMultiplicand + 0);
        a = hram.hMultiplicand[0];

        // RLA;
        {
            uint16_t temp = a;
            a = (a << 1) | carry;
            carry = (temp >> 7) & 0x01;
        }

        // LDH_addr_A(hMultiplicand + 0);
        hram.hMultiplicand[0] = a;

        // LDH_A_addr(hMultiplicand - 1);
        a = hram.unused_41; // hMultiplicand - 1

        // RLA;
        {
            uint16_t temp = a;
            a = (a << 1) | carry;
            carry = (temp >> 7) & 0x01;
        }

        // LDH_addr_A(hMultiplicand - 1);
        hram.unused_41 = a;

        // goto loop;
    } while(1);


done:
    // LDH_A_addr(hMathBuffer + 4);
    // LDH_addr_A(hProduct + 3);

    // LDH_A_addr(hMathBuffer + 3);
    // LDH_addr_A(hProduct + 2);

    // LDH_A_addr(hMathBuffer + 2);
    // LDH_addr_A(hProduct + 1);

    // LDH_A_addr(hMathBuffer + 1);
    // LDH_addr_A(hProduct + 0);
    hram.hProduct = (hram.hMathBuffer[1]) | (hram.hMathBuffer[2] << 8)
        | (hram.hMathBuffer[3] << 16) | (hram.hMathBuffer[4] << 24);

    // RET;
    return;
}

// DEPRECATED
void v_Divide(void){
    // XOR_A_A;
    // LDH_addr_A(hMathBuffer + 0);
    // LDH_addr_A(hMathBuffer + 1);
    // LDH_addr_A(hMathBuffer + 2);
    // LDH_addr_A(hMathBuffer + 3);
    // LDH_addr_A(hMathBuffer + 4);

    // LD_A(9);
    // LD_E_A;

// loop:
    // LDH_A_addr(hMathBuffer + 0);
    // LD_C_A;
    // LDH_A_addr(hDividend + 1);
    // SUB_A_C;
    // LD_D_A;

    // LDH_A_addr(hDivisor);
    // LD_C_A;
    // LDH_A_addr(hDividend + 0);
    // SBC_A_C;
    // IF_C goto next;

    // LDH_addr_A(hDividend + 0);

    // LD_A_D;
    // LDH_addr_A(hDividend + 1);

    // LDH_A_addr(hMathBuffer + 4);
    // INC_A;
    // LDH_addr_A(hMathBuffer + 4);

    // goto loop;


// next:
    // LD_A_B;
    // CP_A(1);
    // IF_Z goto done;

    // LDH_A_addr(hMathBuffer + 4);
    // ADD_A_A;
    // LDH_addr_A(hMathBuffer + 4);

    // LDH_A_addr(hMathBuffer + 3);
    // RLA;
    // LDH_addr_A(hMathBuffer + 3);

    // LDH_A_addr(hMathBuffer + 2);
    // RLA;
    // LDH_addr_A(hMathBuffer + 2);

    // LDH_A_addr(hMathBuffer + 1);
    // RLA;
    // LDH_addr_A(hMathBuffer + 1);

    // DEC_E;
    // IF_NZ goto next2;

    // LD_E(8);
    // LDH_A_addr(hMathBuffer + 0);
    // LDH_addr_A(hDivisor);
    // XOR_A_A;
    // LDH_addr_A(hMathBuffer + 0);

    // LDH_A_addr(hDividend + 1);
    // LDH_addr_A(hDividend + 0);

    // LDH_A_addr(hDividend + 2);
    // LDH_addr_A(hDividend + 1);

    // LDH_A_addr(hDividend + 3);
    // LDH_addr_A(hDividend + 2);

// next2:
    // LD_A_E;
    // CP_A(1);
    // IF_NZ goto okay;
    // DEC_B;

// okay:
    // LDH_A_addr(hDivisor);
    // SRL_A;
    // LDH_addr_A(hDivisor);

    // LDH_A_addr(hMathBuffer + 0);
    // RR_A;
    // LDH_addr_A(hMathBuffer + 0);

    // goto loop;

// done:
    // LDH_A_addr(hDividend + 1);
    // LDH_addr_A(hRemainder);

    // LDH_A_addr(hMathBuffer + 4);
    // LDH_addr_A(hQuotient + 3);

    // LDH_A_addr(hMathBuffer + 3);
    // LDH_addr_A(hQuotient + 2);

    // LDH_A_addr(hMathBuffer + 2);
    // LDH_addr_A(hQuotient + 1);

    // LDH_A_addr(hMathBuffer + 1);
    // LDH_addr_A(hQuotient + 0);

    // RET;
}
