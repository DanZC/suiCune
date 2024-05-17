#include "../../constants.h"
#include "money.h"

void GiveMoney(void){
    LD_A(3);
    CALL(aAddMoney);
    LD_BC(mMaxMoney);
    LD_A(3);
    CALL(aCompareMoney);
    IF_Z goto not_maxed_out;
    IF_C goto not_maxed_out;
    LD_HL(mMaxMoney);
    LD_A_hli;
    LD_de_A;
    INC_DE;
    LD_A_hli;
    LD_de_A;
    INC_DE;
    LD_A_hli;
    LD_de_A;
    SCF;
    RET;


not_maxed_out:
    AND_A_A;
    RET;

}


static const uint8_t MaxMoney[] = { (MAX_MONEY >> 16) & 0xff, (MAX_MONEY >> 8) & 0xff, (MAX_MONEY) & 0xff };

bool GiveMoney_Conv(uint8_t* de, const uint8_t* bc){
    // LD_A(3);
    // CALL(aAddMoney);
    AddMoney_Conv(de, bc);
    // LD_BC(mMaxMoney);
    // LD_A(3);
    // CALL(aCompareMoney);
    u8_flag_s res = CompareMoney_Conv(MaxMoney, de);
    // IF_Z goto not_maxed_out;
    // IF_C goto not_maxed_out;
    if(res.a == 0 || res.flag)
        return false;
    // LD_HL(mMaxMoney);
    // LD_A_hli;
    // LD_de_A;
    de[0] = MaxMoney[0];
    // INC_DE;
    // LD_A_hli;
    // LD_de_A;
    de[1] = MaxMoney[1];
    // INC_DE;
    // LD_A_hli;
    // LD_de_A;
    de[2] = MaxMoney[2];
    // SCF;
    // RET;
    return true;

// not_maxed_out:
    // AND_A_A;
    // RET;
}

void TakeMoney(void){
    LD_A(3);
    CALL(aSubtractMoney);
    IF_NC goto okay;
// leave with 0 money
    XOR_A_A;
    LD_de_A;
    INC_DE;
    LD_de_A;
    INC_DE;
    LD_de_A;
    SCF;
    RET;


okay:
    AND_A_A;
    RET;

}

bool TakeMoney_Conv(uint8_t* de, const uint8_t* bc){
    // LD_A(3);
    // CALL(aSubtractMoney);
    bool carry = SubtractMoney_Conv(de, bc);
    // IF_NC goto okay;
    if(carry) {
    // leave with 0 money
        // XOR_A_A;
        // LD_de_A;
        de[0] = 0;
        // INC_DE;
        // LD_de_A;
        de[1] = 0;
        // INC_DE;
        // LD_de_A;
        de[2] = 0;
        // SCF;
        // RET;
        return true;
    }

// okay:
    // AND_A_A;
    // RET;
    return false;
}

void CompareMoney(void){
    LD_A(3);
    return CompareFunds();
}

u8_flag_s CompareMoney_Conv(const uint8_t* bc, const uint8_t* de){
    // LD_A(3);
    return CompareFunds_Conv(bc, de, 3);
}

//  a: number of bytes
//  bc: start addr of amount (big-endian)
//  de: start addr of account (big-endian)
void CompareFunds(void){
    PUSH_HL;
    PUSH_DE;
    PUSH_BC;
    LD_H_B;
    LD_L_C;
    LD_C(0);
    LD_B_A;

loop1:
    DEC_A;
    IF_Z goto done;
    INC_DE;
    INC_HL;
    goto loop1;


done:
    AND_A_A;

loop2:
    LD_A_de;
    SBC_A_hl;
    IF_Z goto okay;
    INC_C;


okay:
    DEC_DE;
    DEC_HL;
    DEC_B;
    IF_NZ goto loop2;
    IF_C goto set_carry;
    LD_A_C;
    AND_A_A;
    goto skip_carry;


set_carry:
    LD_A(1);
    AND_A_A;
    SCF;

skip_carry:
    POP_BC;
    POP_DE;
    POP_HL;
    RET;

}

//  a: number of bytes
//  bc: start addr of amount (big-endian)
//  de: start addr of account (big-endian)
u8_flag_s CompareFunds_Conv(const uint8_t* bc, const uint8_t* de, uint8_t a){
    // PUSH_HL;
    // PUSH_DE;
    // PUSH_BC;
    // LD_H_B;
    // LD_L_C;
    // LD_C(0);
    // LD_B_A;
    uint8_t c = 0;
    uint8_t carry = 0;

// loop1:
    // DEC_A;
    // IF_Z goto done;
    // INC_DE;
    // INC_HL;
    // goto loop1;


// done:
    // AND_A_A;

    do {
    // loop2:
        // LD_A_de;
        // SBC_A_hl;
        // IF_Z goto okay;
        uint16_t temp = de[a-1] - bc[a-1] - carry;
        carry = (temp & 0xff00)? 1: 0;
        if((temp & 0xff) != 0)
            c++;
        // INC_C;


    // okay:
        // DEC_DE;
        // DEC_HL;
        // DEC_B;
        // IF_NZ goto loop2;
    } while(--a != 0);
    // IF_C goto set_carry;
    if(carry)
        return u8_flag(1, true);
    // LD_A_C;
    // AND_A_A;
    // goto skip_carry;


// set_carry:
    // LD_A(1);
    // AND_A_A;
    // SCF;

// skip_carry:
    // POP_BC;
    // POP_DE;
    // POP_HL;
    // RET;
    return u8_flag(c, false);
}

void SubtractMoney(void){
    LD_A(3);
    return SubtractFunds();
}

void SubtractFunds(void){
//  a: number of bytes
//  bc: start addr of amount (big-endian)
//  de: start addr of account (big-endian)
    PUSH_HL;
    PUSH_DE;
    PUSH_BC;
    LD_H_B;
    LD_L_C;
    LD_B_A;
    LD_C(0);

loop:
    DEC_A;
    IF_Z goto done;
    INC_DE;
    INC_HL;
    goto loop;


done:
    AND_A_A;

loop2:
    LD_A_de;
    SBC_A_hl;
    LD_de_A;
    DEC_DE;
    DEC_HL;
    DEC_B;
    IF_NZ goto loop2;
    POP_BC;
    POP_DE;
    POP_HL;
    RET;

}

bool SubtractMoney_Conv(uint8_t* de, const uint8_t* bc){
    // LD_A(3);
    return SubtractFunds_Conv(de, bc, 3);
}

//  a: number of bytes
//  bc: start addr of amount (big-endian)
//  de: start addr of account (big-endian)
bool SubtractFunds_Conv(uint8_t* de, const uint8_t* bc, uint8_t a){
    // PUSH_HL;
    // PUSH_DE;
    // PUSH_BC;
    // LD_H_B;
    // LD_L_C;
    // LD_B_A;
    // LD_C(0);

// loop:
    // DEC_A;
    // IF_Z goto done;
    // INC_DE;
    // INC_HL;
    // goto loop;


// done:
    // AND_A_A;
    uint8_t carry = 0;

    for(uint8_t b = a; b != 0; --b) {
    // loop2:
        // LD_A_de;
        // SBC_A_hl;
        // LD_de_A;
        de[b - 1] = SubCarry8(de[b - 1], bc[b - 1], carry, &carry);
        // DEC_DE;
        // DEC_HL;
        // DEC_B;
        // IF_NZ goto loop2;
    }
    // POP_BC;
    // POP_DE;
    // POP_HL;
    // RET;
    return carry != 0;
}

void AddMoney(void){
    LD_A(3);
    return AddFunds();
}

void AddFunds(void){
//  a: number of bytes
//  bc: start addr of amount (big-endian)
//  de: start addr of account (big-endian)
    PUSH_HL;
    PUSH_DE;
    PUSH_BC;

    LD_H_B;
    LD_L_C;
    LD_B_A;

loop1:
    DEC_A;
    IF_Z goto done;
    INC_DE;
    INC_HL;
    goto loop1;


done:
    AND_A_A;

loop2:
    LD_A_de;
    ADC_A_hl;
    LD_de_A;
    DEC_DE;
    DEC_HL;
    DEC_B;
    IF_NZ goto loop2;

    POP_BC;
    POP_DE;
    POP_HL;
    RET;

}

void AddMoney_Conv(uint8_t* de, const uint8_t* bc){
    // LD_A(3);
    // return AddFunds();
    return AddFunds_Conv(de, bc, 3);
}

//  a: number of bytes
//  bc: start addr of amount (big-endian)
//  de: start addr of account (big-endian)
void AddFunds_Conv(uint8_t* de, const uint8_t* bc, uint8_t a){
    // PUSH_HL;
    // PUSH_DE;
    // PUSH_BC;

    // LD_H_B;
    // LD_L_C;
    // LD_B_A;

    // loop1:
        // DEC_A;
        // IF_Z goto done;
        // INC_DE;
        // INC_HL;
        // goto loop1;

// done:
    // AND_A_A;
    uint8_t carry = 0;

    for(uint8_t b = a; b != 0; --b) {
    // loop2:
        // LD_A_de;
        // ADC_A_hl;
        uint16_t temp = de[b - 1] + bc[b - 1] + carry;
        carry = (temp & 0xff00)? 1: 0;
        // LD_de_A;
        de[b - 1] = (temp & 0xff);
        // DEC_DE;
        // DEC_HL;
        // DEC_B;
        // IF_NZ goto loop2;
    }

    // POP_BC;
    // POP_DE;
    // POP_HL;
    // RET;
}

void GiveCoins(void){
    LD_A(2);
    LD_DE(wCoins);
    CALL(aAddFunds);
    LD_A(2);
    LD_BC(mGiveCoins_maxcoins);
    CALL(aCompareFunds);
    IF_C goto not_maxed;
    LD_HL(mGiveCoins_maxcoins);
    LD_A_hli;
    LD_de_A;
    INC_DE;
    LD_A_hli;
    LD_de_A;
    SCF;
    RET;


not_maxed:
    AND_A_A;
    RET;


maxcoins:
    //bigdw ['MAX_COINS']

    return TakeCoins();
}

bool GiveCoins_Conv(const uint8_t* bc){
    static const uint8_t maxcoins[] = { HIGH(MAX_COINS), LOW(MAX_COINS) };
    // LD_A(2);
    // LD_DE(wCoins);
    uint8_t* de = (uint8_t*)&wram->wCoins;
    // CALL(aAddFunds);
    AddFunds_Conv(de, bc, 2);
    // LD_A(2);
    // LD_BC(mGiveCoins_maxcoins);
    // CALL(aCompareFunds);
    u8_flag_s res = CompareFunds_Conv(maxcoins, de, 2);
    // IF_C goto not_maxed;
    if(res.flag)
        return false;
    // LD_HL(mGiveCoins_maxcoins);
    // LD_A_hli;
    // LD_de_A;
    de[0] = maxcoins[0];
    // INC_DE;
    // LD_A_hli;
    // LD_de_A;
    de[1] = maxcoins[1];
    // SCF;
    // RET;
    return true;

// not_maxed:
    // AND_A_A;
    // RET;
}

void TakeCoins(void){
    LD_A(2);
    LD_DE(wCoins);
    CALL(aSubtractFunds);
    IF_NC goto okay;
// leave with 0 coins
    XOR_A_A;
    LD_de_A;
    INC_DE;
    LD_de_A;
    SCF;
    RET;


okay:
    AND_A_A;
    RET;

}

bool TakeCoins_Conv(const uint8_t* bc){
    // LD_A(2);
    // LD_DE(wCoins);
    // CALL(aSubtractFunds);
    bool carry = SubtractFunds_Conv((uint8_t*)&wram->wCoins, bc, 2);
    // IF_NC goto okay;
    if(carry) {
    // leave with 0 coins
        // XOR_A_A;
        // LD_de_A;
        // INC_DE;
        // LD_de_A;
        wram->wCoins = 0;
        // SCF;
        // RET;
        return true;
    }

// okay:
    // AND_A_A;
    // RET;
    return false;
}

void CheckCoins(void){
    LD_A(2);
    LD_DE(wCoins);
    JP(mCompareFunds);

}

u8_flag_s CheckCoins_Conv(const uint8_t* bc){
    // LD_A(2);
    // LD_DE(wCoins);
    uint8_t* de = (uint8_t*)&wram->wCoins;
    // JP(mCompareFunds);
    return CompareFunds_Conv(bc, de, 2);
}
