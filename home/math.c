#include "../constants.h"
#include "math.h"
#include "../engine/math/math.h"

//  Return a * c.
//  DEPRECATED: Just do a * c
uint8_t SimpleMultiply(uint8_t a, uint8_t c)
{
    // if(a == 0) return 0;
    // uint8_t out = a;
    // do {
    //     out += c;
    //     a--;
    // } while(a != 0);

    // return out;
    return a * c;
}

// We can use libc's div function or C's division and modulus operator
// libc's div function calcualtes the quotient and the remainder at the same time.
#define USE_LIBC_DIV 1

#if USE_LIBC_DIV
#include <stdlib.h>
#endif

//  Divide a by c. Return quotient b and remainder a.
//  If you only need one value, just do a / c or a % c.
struct DivideResult_t SimpleDivide(uint8_t dividend, uint8_t divisor)
{
#if USE_LIBC_DIV
    div_t res = div((int)dividend, (int)divisor);
    return (struct DivideResult_t){.quot=(uint8_t)res.quot, .rem=(uint8_t)res.rem};
#else
    // struct DivideResult_t result;
    // result.quot = 0;
    // uint8_t cont = 1;
    // do {
    //     result.quot++;
    //     if(dividend < divisor)
    //     {
    //         cont = 0;
    //     }
    //     dividend -= divisor;
    // } while(cont);
    // result.quot--;
    // dividend += divisor;
    // result.rem = dividend;
    // return result;
    return (struct DivideResult_t){.quot=dividend / divisor, .rem=dividend % divisor};
#endif
}

//  Multiply hMultiplicand (3 bytes) by hMultiplier. Result in hProduct.
//  All values are big endian.
//  DEPRECATED: Just multiply the values using the * operator.
void Multiply(void){
    // PUSH_HL;
    // PUSH_BC;

    bank_push(BANK(av_Multiply));

    // CALLFAR(av_Multiply);
    v_Multiply();

    bank_pop;

    // POP_BC;
    // POP_HL;
    // RET;

}

//  Divide hDividend length b (max 4 bytes) by hDivisor. Result in hQuotient.
//  All values are big endian.
//  DEPRECATED: Just divide the values using the / operator.
void Divide(void){
    PUSH_HL;
    PUSH_DE;
    PUSH_BC;
    HOMECALL(av_Divide);
    POP_BC;
    POP_DE;
    POP_HL;
    RET;

}

void SubtractAbsolute(void){
    //  //  unreferenced
//  Return |a - b|, sign in carry.
    SUB_A_B;
    RET_NC ;
    CPL;
    ADD_A(1);
    SCF;
    RET;

}
