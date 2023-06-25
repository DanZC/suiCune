#include "../constants.h"
#include "copy.h"
#include "call_regs.h"

void CopyBytes(void){
    //  copy bc bytes from hl to de
    INC_B;  // we bail the moment b hits 0, so include the last run
    INC_C;  // same thing// include last byte
    goto HandleLoop;

CopyByte:
        LD_A_hli;
    LD_de_A;
    INC_DE;

HandleLoop:
        DEC_C;
    IF_NZ goto CopyByte;
    DEC_B;
    IF_NZ goto CopyByte;
    RET;

}

void CopyBytes_Conv_Old(void){
    //  copy bc bytes from hl to de
    REG_B++;  // we bail the moment b hits 0, so include the last run
    REG_C++;  // same thing// include last byte

    while(--REG_C != 0 || --REG_B != 0)
    {
        REG_A = gb_read(REG_HL++);
        gb_write(REG_DE++, REG_A);
    }
    return;
}

//  copy bc bytes from hl to de
void CopyBytes_Conv(uint16_t de, uint16_t hl, uint16_t bc){
    bc++; // we bail the moment bc hits 0, so include the last run

    while(--bc != 0)
    {
        gb_write(de++, gb_read(hl++));
    }
}

//  copy bc bytes from hl to de
void CopyBytes_Conv2(void* de, const void* hl, uint16_t bc){
    bc++; // we bail the moment bc hits 0, so include the last run
    uint8_t *d = de;
    const uint8_t *s = hl;

    while(--bc != 0)
    {
        *(d++) = *(s++);
    }
}

void SwapBytes(void){
    //  swap bc bytes between hl and de

Loop:
    // stash [hl] away on the stack
    LD_A_hl;
    PUSH_AF;

// copy a byte from [de] to [hl]
    LD_A_de;
    LD_hli_A;

// retrieve the previous value of [hl]// put it in [de]
    POP_AF;
    LD_de_A;
    INC_DE;

// handle loop stuff
    DEC_BC;
    LD_A_B;
    OR_A_C;
    IF_NZ goto Loop;
    RET;

}

//  swap bc bytes between hl and de
// Input
//   hl: buffer a
//   de: buffer b
//   bc: byte count
void SwapBytes_Conv(uint16_t hl, uint16_t de, uint16_t bc){
    do {
        // stash [hl] away on the stack
        uint8_t temp = gb_read(hl);

        // copy a byte from [de] to [hl]
        gb_write(hl++, gb_read(de));

        // retrieve the previous value of [hl]// put it in [de]
        gb_write(de++, temp);

        // handle loop stuff
    } while(--bc != 0);
}

//  swap bc bytes between hl and de
// Input
//   hl: buffer a
//   de: buffer b
//   bc: byte count
void SwapBytes_Conv2(void* hl, void* de, uint16_t bc){
    uint8_t *a = hl, *b = de;
    do {
        // stash [hl] away on the stack
        uint8_t temp = *a;

        // copy a byte from [de] to [hl]
        *(a++) = *(b);

        // retrieve the previous value of [hl]// put it in [de]
        *(b++) = temp;

        // handle loop stuff
    } while(--bc != 0);
}

void ByteFill(void){
    //  fill bc bytes with the value of a, starting at hl
    INC_B;  // we bail the moment b hits 0, so include the last run
    INC_C;  // same thing// include last byte
    goto HandleLoop;

PutByte:
        LD_hli_A;

HandleLoop:
        DEC_C;
    IF_NZ goto PutByte;
    DEC_B;
    IF_NZ goto PutByte;
    RET;

}

void ByteFill_Conv_Old(void){
    //  fill bc bytes with the value of a, starting at hl
    REG_B++;  // we bail the moment b hits 0, so include the last run
    REG_C++;  // same thing// include last byte

    while(--REG_C != 0 || --REG_B != 0)
    {
        gb_write(REG_HL++, REG_A);
    }
    return;
}

//  fill bc bytes with the value of a, starting at hl
void ByteFill_Conv(uint16_t ptr, uint16_t len, uint8_t value){
    len++;  // we bail the moment b hits 0, so include the last run

    while(--len != 0)
    {
        gb_write(ptr++, value);
    }
}

void ByteFill_Conv2(void* ptr, uint16_t len, uint8_t value){
    uint8_t* p = ptr;
    len++;  // we bail the moment b hits 0, so include the last run

    while(--len != 0)
    {
        *p = value;
    }
}

void GetFarByte(void){
    //  retrieve a single byte from a:hl, and return it in a.
// bankswitch to new bank
    LDH_addr_A(hTempBank);
    LDH_A_addr(hROMBank);
    PUSH_AF;
    LDH_A_addr(hTempBank);
    RST(aBankswitch);

// get byte from new bank
    LD_A_hl;
    LDH_addr_A(hFarByte);

// bankswitch to previous bank
    POP_AF;
    RST(aBankswitch);

// return retrieved value in a
    LDH_A_addr(hFarByte);
    RET;

}

void GetFarByte_Conv_Old(void){
    //  retrieve a single byte from a:hl, and return it in a.
    // bankswitch to new bank
    uint8_t temp = gb_read(hROMBank);
    RST(aBankswitch);

    // get byte from new bank
    uint8_t farbyte = gb_read(REG_HL);

    // bankswitch to previous bank
    REG_A = temp;
    RST(aBankswitch);

    // return retrieved value in a
    REG_A = farbyte;
}

//  retrieve a single byte from a:hl, and return it in a.
uint8_t GetFarByte_Conv(uint8_t a, uint16_t hl){
    // bankswitch to new bank
    uint8_t temp = gb_read(hROMBank);
    Bankswitch_Conv(a);

    // get byte from new bank
    uint8_t farbyte = gb_read(hl);

    // bankswitch to previous bank
    Bankswitch_Conv(temp);

    // return retrieved value
    return farbyte;
}

void GetFarWord(void){
    //  retrieve a word from a:hl, and return it in hl.
// bankswitch to new bank
    LDH_addr_A(hTempBank);
    LDH_A_addr(hROMBank);
    PUSH_AF;
    LDH_A_addr(hTempBank);
    RST(aBankswitch);

// get word from new bank, put it in hl
    LD_A_hli;
    LD_H_hl;
    LD_L_A;

// bankswitch to previous bank and return
    POP_AF;
    RST(aBankswitch);
    RET;

}

//  retrieve a word from a:hl, and return it in hl.
uint16_t GetFarWord_Conv(uint8_t a, uint16_t hl){
    // bankswitch to new bank
    uint8_t temp = gb_read(hROMBank);
    Bankswitch_Conv(a);

// get word from new bank, put it in hl
    uint16_t far_word = gb_read16(hl);

// bankswitch to previous bank and return
    Bankswitch_Conv(temp);
    return far_word;
}

void FarCopyWRAM(void){
        LDH_addr_A(hTempBank);
    LDH_A_addr(rSVBK);
    PUSH_AF;
    LDH_A_addr(hTempBank);
    LDH_addr_A(rSVBK);

    CALL(aCopyBytes);

    POP_AF;
    LDH_addr_A(rSVBK);
    RET;

}

void FarCopyWRAM_Conv(uint8_t a, uint16_t de, uint16_t hl, uint16_t bc){
    // LDH_addr_A(hTempBank);
    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    uint8_t svbk = gb_read(rSVBK);
    gb_write(rSVBK, a);
    // LDH_A_addr(hTempBank);
    // LDH_addr_A(rSVBK);

    // CALL(aCopyBytes);
    CopyBytes_Conv(de, hl, bc);

    // POP_AF;
    // LDH_addr_A(rSVBK);
    // RET;
    gb_write(rSVBK, svbk);
}

void GetFarWRAMByte(void){
        LDH_addr_A(hTempBank);
    LDH_A_addr(rSVBK);
    PUSH_AF;
    LDH_A_addr(hTempBank);
    LDH_addr_A(rSVBK);
    LD_A_hl;
    LDH_addr_A(hFarByte);
    POP_AF;
    LDH_addr_A(rSVBK);
    LDH_A_addr(hFarByte);
    RET;

}

uint8_t GetFarWRAMByte_Conv(uint8_t bank, uint16_t address){
    // LDH_addr_A(hTempBank);
    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    uint8_t svbk = gb_read(rSVBK);
    // LDH_A_addr(hTempBank);
    // LDH_addr_A(rSVBK);
    gb_write(rSVBK, bank);
    // LD_A_hl;
    // LDH_addr_A(hFarByte);
    gb_write(hFarByte, gb_read(address));
    // POP_AF;
    // LDH_addr_A(rSVBK);
    gb_write(rSVBK, svbk);
    // LDH_A_addr(hFarByte);
    // RET;
    return gb_read(hFarByte);
}


void GetFarWRAMWord(void){
    //  //  unreferenced
    LDH_addr_A(hTempBank);
    LDH_A_addr(rSVBK);
    PUSH_AF;
    LDH_A_addr(hTempBank);
    LDH_addr_A(rSVBK);
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    POP_AF;
    LDH_addr_A(rSVBK);
    RET;

}
