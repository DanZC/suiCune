#include "../constants.h"
#include "math.h"
#include "../engine/math/math.h"

void SimpleMultiply(void){
    //  Return a * c.
    AND_A_A;
    RET_Z ;

    PUSH_BC;
    LD_B_A;
    XOR_A_A;

loop:
        ADD_A_C;
    DEC_B;
    IF_NZ goto loop;
    POP_BC;
    RET;

}

//  Return a * c.
void SimpleMultiply_Conv_Old(void)
{
    uint16_t temp = REG_BC;
    if(REG_A == 0) return;
    REG_B = REG_A;
    REG_A = 0;

    do {
        REG_A += REG_C;
        REG_B--;
    } while(REG_B != 0);

    REG_BC = temp;
}

//  Return a * c.
uint8_t SimpleMultiply_Conv(uint8_t a, uint8_t c)
{
    if(a == 0) return 0;
    uint8_t out = a;
    do {
        out += c;
        a--;
    } while(a != 0);

    return out;
}

void SimpleDivide(void){
    //  Divide a by c. Return quotient b and remainder a.
    LD_B(0);

loop:
        INC_B;
    SUB_A_C;
    IF_NC goto loop;
    DEC_B;
    ADD_A_C;
    RET;

}

void SimpleDivide_Conv_Old(void)
{
    REG_B = 0;
    uint8_t cont = 1;
    do {
        REG_B++;
        if(REG_A < REG_C)
        {
            cont = 0;
        }
        REG_A -= REG_C;
    } while(cont);
    REG_B--;
    REG_A += REG_C;
}

//  Divide a by c. Return quotient b and remainder a.
struct DivideResult_t SimpleDivide_Conv(uint8_t dividend, uint8_t divisor)
{
    struct DivideResult_t result;
    result.quot = 0;
    uint8_t cont = 1;
    do {
        result.quot++;
        if(dividend < divisor)
        {
            cont = 0;
        }
        dividend -= divisor;
    } while(cont);
    result.quot--;
    dividend += divisor;
    result.rem = dividend;
    return result;
}

void Multiply(void){
    //  Multiply hMultiplicand (3 bytes) by hMultiplier. Result in hProduct.
//  All values are big endian.
    PUSH_HL;
    PUSH_BC;

    CALLFAR(av_Multiply);

    POP_BC;
    POP_HL;
    RET;

}

//  Multiply hMultiplicand (3 bytes) by hMultiplier. Result in hProduct.
//  All values are big endian.
void Multiply_Conv(void){
    // PUSH_HL;
    // PUSH_BC;

    bank_push(BANK(av_Multiply));

    // CALLFAR(av_Multiply);
    v_Multiply_Conv();

    bank_pop;

    // POP_BC;
    // POP_HL;
    // RET;

}

void Divide(void){
    //  Divide hDividend length b (max 4 bytes) by hDivisor. Result in hQuotient.
//  All values are big endian.
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
