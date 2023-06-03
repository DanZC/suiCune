#include "../constants.h"
#include "gfx.h"
#include "copy.h"

#define TILES_PER_CYCLE (8)
#define MOBILE_TILES_PER_CYCLE (6)

void Get2bppViaHDMA(void) {
    LDH_A_addr(rLCDC);
    BIT_A(rLCDC_ENABLE);
    JP_Z(mCopy2bpp);

    HOMECALL(aHDMATransfer2bpp);

    RET;
}

void Get1bppViaHDMA(void) {
    LDH_A_addr(rLCDC);
    BIT_A(rLCDC_ENABLE);
    JP_Z(mCopy1bpp);

    HOMECALL(aHDMATransfer1bpp);

    RET;
}

void FarCopyBytesDouble_DoubleBankSwitch(void) {
    LDH_addr_A(hTempBank);
    LDH_A_addr(hROMBank);
    PUSH_AF;
    LDH_A_addr(hTempBank);
    RST(aBankswitch);

    CALL(aFarCopyBytesDouble);

    POP_AF;
    RST(aBankswitch);
    RET;
}

void SafeHDMATransfer(void) {
    //  //  unreferenced
    DEC_C;
    LDH_A_addr(hBGMapMode);
    PUSH_AF;
    XOR_A_A;
    LDH_addr_A(hBGMapMode);
    LDH_A_addr(hROMBank);
    PUSH_AF;
    LD_A_B;
    RST(aBankswitch);

loop:
    //  load the source and target MSB and LSB
    LD_A_D;
    LDH_addr_A(rHDMA1);  // source MSB
    LD_A_E;
    AND_A(0xf0);
    LDH_addr_A(rHDMA2);  // source LSB
    LD_A_H;
    AND_A(0x1f);
    LDH_addr_A(rHDMA3);  // target MSB
    LD_A_L;
    AND_A(0xf0);
    LDH_addr_A(rHDMA4);  // target LSB
                         //  stop when c < TILES_PER_CYCLE
    LD_A_C;
    CP_A(TILES_PER_CYCLE);
    IF_C goto done;
    //  decrease c by TILES_PER_CYCLE
    SUB_A(TILES_PER_CYCLE);
    LD_C_A;
    //  DMA transfer state
    LD_A(0xf);
    LDH_addr_A(hDMATransfer);
    CALL(aDelayFrame);
    //  add $100 to hl and de
    LD_A_L;
    ADD_A(LOW(0x100));
    LD_L_A;
    LD_A_H;
    ADC_A(HIGH(0x100));
    LD_H_A;
    LD_A_E;
    ADD_A(LOW(0x100));
    LD_E_A;
    LD_A_D;
    ADC_A(HIGH(0x100));
    LD_D_A;
    goto loop;

done:
    LD_A_C;
    AND_A(0x7f);  // pretty silly, considering at most bits 0-2 would be set
    LDH_addr_A(hDMATransfer);
    CALL(aDelayFrame);
    POP_AF;
    RST(aBankswitch);

    POP_AF;
    LDH_addr_A(hBGMapMode);
    RET;
}

void UpdatePlayerSprite(void) {
    FARCALL(av_UpdatePlayerSprite);
    RET;
}

void LoadStandardFont(void) {
    FARCALL(av_LoadStandardFont);
    RET;
}

void LoadFontsBattleExtra(void) {
    FARCALL(av_LoadFontsBattleExtra);
    RET;
}

void LoadFontsExtra(void) {
    FARCALL(av_LoadFontsExtra1);
    FARCALL(av_LoadFontsExtra2);
    RET;
}

void LoadFontsExtra2(void) {
    //  //  unreferenced
    FARCALL(av_LoadFontsExtra2);
    RET;
}

void DecompressRequest2bpp(void) {
    PUSH_DE;
    LD_A(MBANK(asScratch));
    CALL(aOpenSRAM);
    PUSH_BC;

    LD_DE(sScratch);
    LD_A_B;
    CALL(aFarDecompress);

    POP_BC;
    POP_HL;

    LD_DE(sScratch);
    CALL(aRequest2bpp);
    CALL(aCloseSRAM);
    RET;
}

void FarCopyBytes(void) {
    //  copy bc bytes from a:hl to de

    LDH_addr_A(hTempBank);
    LDH_A_addr(hROMBank);
    PUSH_AF;
    LDH_A_addr(hTempBank);
    RST(aBankswitch);

    CALL(aCopyBytes);

    POP_AF;
    RST(aBankswitch);
    RET;
}

//  copy bc bytes from a:hl to de
void FarCopyBytes_Conv(uint16_t de, uint8_t a, uint16_t hl, uint16_t bc) {
    // LDH_addr_A(hTempBank);
    // LDH_A_addr(hROMBank);
    // PUSH_AF;
    // LDH_A_addr(hTempBank);
    // RST(aBankswitch);
    bank_push(a);

    CopyBytes_Conv(de, hl, bc);

    bank_pop;
}

void FarCopyBytesDouble(void) {
    //  Copy bc bytes from a:hl to bc*2 bytes at de,
    //  doubling each byte in the process.

    LDH_addr_A(hTempBank);
    LDH_A_addr(hROMBank);
    PUSH_AF;
    LDH_A_addr(hTempBank);
    RST(aBankswitch);

    //  switcheroo, de <> hl
    LD_A_H;
    LD_H_D;
    LD_D_A;
    LD_A_L;
    LD_L_E;
    LD_E_A;

    INC_B;
    INC_C;
    goto dec;

loop:
    LD_A_de;
    INC_DE;
    LD_hli_A;
    LD_hli_A;

dec:
    DEC_C;
    IF_NZ goto loop;
    DEC_B;
    IF_NZ goto loop;

    POP_AF;
    RST(aBankswitch);
    RET;
}

void Request2bpp(void) {
    uint16_t size = REG_C << 4;
    uint32_t source = REG_DE;
    switch (REG_DE >> 14) {
        case 0:  // 0x0000 - 0x3FFF
            for (int i = 0; i < size; i++) gb_write(REG_HL++, gb.gb_rom_read(source++));
            break;
        case 1:  // 0x4000 - 0x7FFF
            source = REG_DE + (REG_DE < 0x4000 ? 0 : ((REG_B - 1) * ROM_BANK_SIZE));
            for (int i = 0; i < size; i++) gb_write(REG_HL++, gb.gb_rom_read(source++));
            break;
        default:  // Anything else, like the scratch area in RAM
            for (int i = 0; i < size; i++) gb_write(REG_HL++, gb_read(source++));
            break;
    }
    RET;
    //  Load 2bpp at b:de to occupy c tiles of hl.
    LDH_A_addr(hBGMapMode);
    PUSH_AF;
    XOR_A_A;
    LDH_addr_A(hBGMapMode);

    LDH_A_addr(hROMBank);
    PUSH_AF;
    LD_A_B;
    RST(aBankswitch);

    LDH_A_addr(hTilesPerCycle);
    PUSH_AF;
    LD_A(TILES_PER_CYCLE);
    LDH_addr_A(hTilesPerCycle);

    LD_A_addr(wLinkMode);
    CP_A(LINK_MOBILE);
    IF_NZ goto NotMobile;
    LDH_A_addr(hMobile);
    AND_A_A;
    IF_NZ goto NotMobile;
    LD_A(MOBILE_TILES_PER_CYCLE);
    LDH_addr_A(hTilesPerCycle);

NotMobile:
    LD_A_E;
    LD_addr_A(wRequested2bppSource);
    LD_A_D;
    LD_addr_A(wRequested2bppSource + 1);
    LD_A_L;
    LD_addr_A(wRequested2bppDest);
    LD_A_H;
    LD_addr_A(wRequested2bppDest + 1);

loop:
    LD_A_C;
    LD_HL(hTilesPerCycle);
    CP_A_hl;
    IF_NC goto cycle;

    LD_addr_A(wRequested2bppSize);

wait:
    CALL(aDelayFrame);
    LD_A_addr(wRequested2bppSize);
    AND_A_A;
    IF_NZ goto wait;

    POP_AF;
    LDH_addr_A(hTilesPerCycle);

    POP_AF;
    RST(aBankswitch);

    POP_AF;
    LDH_addr_A(hBGMapMode);
    RET;

cycle:
    LDH_A_addr(hTilesPerCycle);
    LD_addr_A(wRequested2bppSize);

wait2:
    CALL(aDelayFrame);
    LD_A_addr(wRequested2bppSize);
    AND_A_A;
    IF_NZ goto wait2;

    LD_A_C;
    LD_HL(hTilesPerCycle);
    SUB_A_hl;
    LD_C_A;
    goto loop;
}

void Request1bpp(void) {
    uint16_t size = REG_C << 3;
    uint32_t source = REG_DE;
    switch (REG_DE >> 14) {
        case 0:  // 0x0000 - 0x3FFF
            for (int i = 0; i < size; i++) {
                gb_write(REG_HL++, gb.gb_rom_read(source));
                gb_write(REG_HL++, gb.gb_rom_read(source++));
            }
            break;
        case 1:  // 0x4000 - 0x7FFF
            source = REG_DE + (REG_DE < 0x4000 ? 0 : ((REG_B - 1) * ROM_BANK_SIZE));
            for (int i = 0; i < size; i++) {
                gb_write(REG_HL++, gb.gb_rom_read(source));
                gb_write(REG_HL++, gb.gb_rom_read(source++));
            }
            break;
        default:  // Anything else, like the scratch area in RAM
            for (int i = 0; i < size; i++) {
                gb_write(REG_HL++, gb_read(source));
                gb_write(REG_HL++, gb_read(source++));
            }
            break;
    }
    RET;
    //  Load 1bpp at b:de to occupy c tiles of hl.
    LDH_A_addr(hBGMapMode);
    PUSH_AF;
    XOR_A_A;
    LDH_addr_A(hBGMapMode);

    LDH_A_addr(hROMBank);
    PUSH_AF;
    LD_A_B;
    RST(aBankswitch);

    LDH_A_addr(hTilesPerCycle);
    PUSH_AF;
    LD_A(TILES_PER_CYCLE);
    LDH_addr_A(hTilesPerCycle);

    LD_A_addr(wLinkMode);
    CP_A(LINK_MOBILE);
    IF_NZ goto NotMobile;
    LDH_A_addr(hMobile);
    AND_A_A;
    IF_NZ goto NotMobile;
    LD_A(MOBILE_TILES_PER_CYCLE);
    LDH_addr_A(hTilesPerCycle);

NotMobile:
    LD_A_E;
    LD_addr_A(wRequested1bppSource);
    LD_A_D;
    LD_addr_A(wRequested1bppSource + 1);
    LD_A_L;
    LD_addr_A(wRequested1bppDest);
    LD_A_H;
    LD_addr_A(wRequested1bppDest + 1);

loop:
    LD_A_C;
    LD_HL(hTilesPerCycle);
    CP_A_hl;
    IF_NC goto cycle;

    LD_addr_A(wRequested1bppSize);

wait:
    CALL(aDelayFrame);
    LD_A_addr(wRequested1bppSize);
    AND_A_A;
    IF_NZ goto wait;

    POP_AF;
    LDH_addr_A(hTilesPerCycle);

    POP_AF;
    RST(aBankswitch);

    POP_AF;
    LDH_addr_A(hBGMapMode);
    RET;

cycle:
    LDH_A_addr(hTilesPerCycle);
    LD_addr_A(wRequested1bppSize);

wait2:
    CALL(aDelayFrame);
    LD_A_addr(wRequested1bppSize);
    AND_A_A;
    IF_NZ goto wait2;

    LD_A_C;
    LD_HL(hTilesPerCycle);
    SUB_A_hl;
    LD_C_A;
    goto loop;

    return Get2bpp();
}

void Get2bpp(void) {
    //  copy c 2bpp tiles from b:de to hl
    LDH_A_addr(rLCDC);
    BIT_A(rLCDC_ENABLE);
    JP_NZ(mRequest2bpp);
    // fallthrough

    return Copy2bpp();
}

void Copy2bpp(void) {
    PUSH_HL;
    LD_H_D;
    LD_L_E;
    POP_DE;

    //  bank
    LD_A_B;

    //  bc = c * LEN_2BPP_TILE
    PUSH_AF;
    SWAP_C;
    LD_A(0xf);
    AND_A_C;
    LD_B_A;
    LD_A(0xf0);
    AND_A_C;
    LD_C_A;
    POP_AF;

    JP(mFarCopyBytes);
}

void Get1bpp(void) {
    //  copy c 1bpp tiles from b:de to hl
    LDH_A_addr(rLCDC);
    BIT_A(rLCDC_ENABLE);
    JP_NZ(mRequest1bpp);
    // fallthrough

    return Copy1bpp();
}

void Copy1bpp(void) {
    PUSH_DE;
    LD_D_H;
    LD_E_L;

    //  bank
    LD_A_B;

    //  bc = c * LEN_1BPP_TILE
    PUSH_AF;
    LD_H(0);
    LD_L_C;
    ADD_HL_HL;
    ADD_HL_HL;
    ADD_HL_HL;
    LD_B_H;
    LD_C_L;
    POP_AF;

    POP_HL;
    JP(mFarCopyBytesDouble);
}
