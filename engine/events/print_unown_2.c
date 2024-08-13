#include "../../constants.h"
#include "print_unown_2.h"
#include "../../home/copy.h"
#include "../../home/sram.h"

static uint8_t* RotateUnownFrontpic_Copy(uint8_t* de, const uint8_t* hl);
static void RotateUnownFrontpic_Rotate(void);
static uint8_t* UnownPrinter_GBPrinterRectangle(uint16_t bc);

void RotateUnownFrontpic(uint8_t* de){
//  something to do with Unown printer
    // PUSH_DE;
    // XOR_A_A;  // BANK(sScratch)
    // CALL(aOpenSRAM);
    OpenSRAM_Conv(MBANK(asScratch));
    // LD_HL(sScratch);
    uint8_t* hl = GBToRAMAddr(sScratch);
    // LD_BC(0);
    uint16_t bc = 0;

    do {
    // loop:
        // PUSH_BC;
        // PUSH_HL;
        uint8_t* hl2 = hl;
        // PUSH_BC;
        // LD_DE(wPrintedUnownTileSource);
        uint8_t* de2 = wram->wPrintedUnownTileSource;
        // CALL(aRotateUnownFrontpic_Copy);
        de2 = RotateUnownFrontpic_Copy(de2, hl2);
        // CALL(aRotateUnownFrontpic_Rotate);
        RotateUnownFrontpic_Rotate();
        // LD_HL(mUnownPrinter_GBPrinterRectangle);
        // POP_BC;
        // ADD_HL_BC;
        // ADD_HL_BC;
        // LD_A_hli;
        // LD_E_A;
        // LD_D_hl;
        // LD_HL(wPrintedUnownTileDest);
        // CALL(aRotateUnownFrontpic_Copy);
        RotateUnownFrontpic_Copy(UnownPrinter_GBPrinterRectangle(bc), wram->wPrintedUnownTileDest);
        // POP_HL;
        // LD_BC(LEN_2BPP_TILE);
        // ADD_HL_BC;
        hl += LEN_2BPP_TILE;
        // POP_BC;
        // INC_C;
        // LD_A_C;
        // CP_A(7 * 7);
        // IF_C goto loop;
    } while(++bc < 7 * 7);

    // LD_HL(wGameboyPrinter2bppSource);
    // LD_DE(sScratch);
    // LD_BC(7 * 7 * LEN_2BPP_TILE);
    // CALL(aCopyBytes);
    // POP_HL;
    // LD_DE(sScratch);
    // LD_C(7 * 7);
    // LDH_A_addr(hROMBank);
    // LD_B_A;
    // CALL(aGet2bpp);
    CopyBytes_Conv2(de, wram->wGameboyPrinter2bppSource, 7 * 7 * LEN_2BPP_TILE);
    // CALL(aCloseSRAM);
    CloseSRAM_Conv();
    // RET;
}

static uint8_t* RotateUnownFrontpic_Copy(uint8_t* de, const uint8_t* hl){
    // LD_C(LEN_2BPP_TILE);
    uint8_t c = LEN_2BPP_TILE;

    do {
    // loop_copy:
        // LD_A_hli;
        // LD_de_A;
        // INC_DE;
        *(de++) = *(hl++);
        // DEC_C;
        // IF_NZ goto loop_copy;
    } while(--c != 0);
    // RET;
    return de;
}

static uint8_t RotateUnownFrontpic_CountSetBit(const uint8_t* hl, uint8_t e){
    // LD_B(0);
    uint8_t b = 0;
    // LD_C(8);
    uint8_t c = 8;
    uint8_t carry = 0;

    do {
    // loop_count:
        // LD_A_hli;
        // AND_A_E;
        // IF_Z goto clear;
        // SCF;
        // goto apply;
        carry = (*hl & e)? 1: 0;

    // clear:
        // AND_A_A;

    // apply:
        // RR_B;
        b = (b >> 1) | (carry << 7);
        // INC_HL;
        hl += 2;
        // DEC_C;
        // IF_NZ goto loop_count;
    } while(--c != 0);
    // RET;
    return b;
}

static void RotateUnownFrontpic_Rotate(void){
    // LD_HL(wPrintedUnownTileDest);
    uint8_t* hl = wram->wPrintedUnownTileDest;
    // LD_E(0b10000000);
    uint8_t e = 0b10000000;
    // LD_D(8);
    uint8_t d = 8;

    do {
    // loop_decompress:
        // PUSH_HL;
        // LD_HL(wPrintedUnownTileSource);
        // CALL(aRotateUnownFrontpic_CountSetBit);
        // POP_HL;
        // LD_A_B;
        // LD_hli_A;
        *(hl++) = RotateUnownFrontpic_CountSetBit(wram->wPrintedUnownTileSource, e);
        // PUSH_HL;
        // LD_HL(wPrintedUnownTileSource + 1);
        // CALL(aRotateUnownFrontpic_CountSetBit);
        // POP_HL;
        // LD_A_B;
        // LD_hli_A;
        *(hl++) = RotateUnownFrontpic_CountSetBit(wram->wPrintedUnownTileSource + 1, e);
        // SRL_E;
        e >>= 1;
        // DEC_D;
        // IF_NZ goto loop_decompress;
    } while(--d != 0);
    // RET;
}

static uint8_t* UnownPrinter_GBPrinterRectangle(uint16_t bc){
    // for(int y = 0; y < 7; y++){
    // for(int x = 0; x < 7 - 1, -1, -1; x++){
    // //dw ['wGameboyPrinter2bppSource + LEN_2BPP_TILE * (x * 7 + y)'];
    // }
    // }
    uint8_t y = bc / 7;
    uint8_t x = bc % 7;
    return wram->wGameboyPrinter2bppSource + LEN_2BPP_TILE * (x * 7 + (7 - y));
}
