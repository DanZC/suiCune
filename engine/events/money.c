#include "../../constants.h"
#include "money.h"

static const uint8_t MaxMoney[] = { (MAX_MONEY >> 16) & 0xff, (MAX_MONEY >> 8) & 0xff, (MAX_MONEY) & 0xff };

static u8_flag_s CompareFunds(const uint8_t* de, const uint8_t* bc, uint8_t a);
static bool SubtractMoney(uint8_t* de, const uint8_t* bc);
static bool SubtractFunds(uint8_t* de, const uint8_t* bc, uint8_t a);
static void AddFunds(uint8_t* de, const uint8_t* bc, uint8_t a);

bool GiveMoney(uint8_t* de, const uint8_t* bc){
    // LD_A(3);
    // CALL(aAddMoney);
    AddMoney(de, bc);
    // LD_BC(mMaxMoney);
    // LD_A(3);
    // CALL(aCompareMoney);
    u8_flag_s res = CompareMoney(MaxMoney, de);
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

bool TakeMoney(uint8_t* de, const uint8_t* bc){
    // LD_A(3);
    // CALL(aSubtractMoney);
    bool carry = SubtractMoney(de, bc);
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

u8_flag_s CompareMoney(const uint8_t* bc, const uint8_t* de){
    // LD_A(3);
    return CompareFunds(de, bc, 3);
}

//  a: number of bytes
//  bc: start addr of amount (big-endian)
//  de: start addr of account (big-endian)
static u8_flag_s CompareFunds(const uint8_t* de, const uint8_t* bc, uint8_t a){
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

static bool SubtractMoney(uint8_t* de, const uint8_t* bc){
    // LD_A(3);
    return SubtractFunds(de, bc, 3);
}

//  a: number of bytes
//  bc: start addr of amount (big-endian)
//  de: start addr of account (big-endian)
static bool SubtractFunds(uint8_t* de, const uint8_t* bc, uint8_t a){
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

void AddMoney(uint8_t* de, const uint8_t* bc){
    // LD_A(3);
    // return AddFunds();
    return AddFunds(de, bc, 3);
}

//  a: number of bytes
//  bc: start addr of amount (big-endian)
//  de: start addr of account (big-endian)
static void AddFunds(uint8_t* de, const uint8_t* bc, uint8_t a){
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

bool GiveCoins(const uint8_t* bc){
    static const uint8_t maxcoins[] = { HIGH(MAX_COINS), LOW(MAX_COINS) };
    // LD_A(2);
    // LD_DE(wCoins);
    uint8_t* de = (uint8_t*)&gPlayer.coins;
    // CALL(aAddFunds);
    AddFunds(de, bc, 2);
    // LD_A(2);
    // LD_BC(mGiveCoins_maxcoins);
    // CALL(aCompareFunds);
    u8_flag_s res = CompareFunds(de, maxcoins, 2);
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

bool TakeCoins(const uint8_t* bc){
    // LD_A(2);
    // LD_DE(wCoins);
    // CALL(aSubtractFunds);
    bool carry = SubtractFunds((uint8_t*)&gPlayer.coins, bc, 2);
    // IF_NC goto okay;
    if(carry) {
    // leave with 0 coins
        // XOR_A_A;
        // LD_de_A;
        // INC_DE;
        // LD_de_A;
        gPlayer.coins = 0;
        // SCF;
        // RET;
        return true;
    }

// okay:
    // AND_A_A;
    // RET;
    return false;
}

u8_flag_s CheckCoins(const uint8_t* bc){
    // LD_A(2);
    // LD_DE(wCoins);
    uint8_t* de = (uint8_t*)&gPlayer.coins;
    // JP(mCompareFunds);
    return CompareFunds(de, bc, 2);
}
