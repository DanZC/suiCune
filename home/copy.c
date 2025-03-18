#include "../constants.h"
#include "copy.h"
#include "call_regs.h"

//  copy bc bytes from hl to de
void CopyBytes(void* de, const void* hl, uint16_t bc){
    bc++; // we bail the moment bc hits 0, so include the last run
    uint8_t *d = de;
    const uint8_t *s = hl;

    while(--bc != 0)
    {
        *(d++) = *(s++);
    }
}

//  copy bc bytes from hl to de
//  Uses virtual GB addresses.
void CopyBytes_GB(uint16_t de, uint16_t hl, uint16_t bc){
    bc++; // we bail the moment bc hits 0, so include the last run

    while(--bc != 0)
    {
        gb_write(de++, gb_read(hl++));
    }
}

//  swap bc bytes between hl and de
// Input
//   hl: buffer a
//   de: buffer b
//   bc: byte count
void SwapBytes(void* hl, void* de, uint16_t bc){
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

// Unused
//  swap bc bytes between hl and de
// Input
//   hl: buffer a
//   de: buffer b
//   bc: byte count
void SwapBytes_GB(uint16_t hl, uint16_t de, uint16_t bc){
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

//  fill bc bytes with the value of a, starting at hl
void ByteFill(void* ptr, uint16_t len, uint8_t value){
    uint8_t* p = ptr;
    len++;  // we bail the moment b hits 0, so include the last run

    while(--len != 0)
    {
        *(p++) = value;
    }
}

//  fill bc bytes with the value of a, starting at hl
//  Uses virtual GB addresses.
void ByteFill_GB(uint16_t ptr, uint16_t len, uint8_t value){
    len++;  // we bail the moment b hits 0, so include the last run

    while(--len != 0)
    {
        gb_write(ptr++, value);
    }
}

//  retrieve a single byte from a:hl, and return it in a.
//  DEPRECATED: Use wram variable directly.
uint8_t GetFarByte(uint8_t a, uint16_t hl){
    // bankswitch to new bank
    uint8_t temp = hram->hROMBank;
    Bankswitch(a);

    // get byte from new bank
    uint8_t farbyte = gb_read(hl);

    // bankswitch to previous bank
    Bankswitch(temp);

    // return retrieved value
    return farbyte;
}

//  retrieve a word from a:hl, and return it in hl.
//  DEPRECATED: Use wram variable directly.
uint16_t GetFarWord(uint8_t a, uint16_t hl){
    // bankswitch to new bank
    uint8_t temp = hram->hROMBank;
    Bankswitch(a);

// get word from new bank, put it in hl
    uint16_t far_word = gb_read16(hl);

// bankswitch to previous bank and return
    Bankswitch(temp);
    return far_word;
}

//  DEPRECATED: Use CopyBytes directly.
//  Unused
void FarCopyWRAM(uint8_t a, uint16_t de, uint16_t hl, uint16_t bc){
    // LDH_addr_A(hTempBank);
    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    uint8_t svbk = gb_read(rSVBK);
    gb_write(rSVBK, a);
    // LDH_A_addr(hTempBank);
    // LDH_addr_A(rSVBK);

    // CALL(aCopyBytes);
    CopyBytes_GB(de, hl, bc);

    // POP_AF;
    // LDH_addr_A(rSVBK);
    // RET;
    gb_write(rSVBK, svbk);
}

//  DEPRECATED: Use wram variable directly.
//  Unused
uint8_t GetFarWRAMByte(uint8_t bank, uint16_t address){
    // LDH_addr_A(hTempBank);
    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    uint8_t svbk = gb_read(rSVBK);
    // LDH_A_addr(hTempBank);
    // LDH_addr_A(rSVBK);
    gb_write(rSVBK, bank);
    // LD_A_hl;
    // LDH_addr_A(hFarByte);
    hram->hFarByte = gb_read(address);
    // POP_AF;
    // LDH_addr_A(rSVBK);
    gb_write(rSVBK, svbk);
    // LDH_A_addr(hFarByte);
    // RET;
    return hram->hFarByte;
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
