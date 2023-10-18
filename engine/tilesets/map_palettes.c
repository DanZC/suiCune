#include "../../constants.h"
#include "map_palettes.h"

void v_SwapTextboxPalettes(void){
    hlcoord(0, 0, wTilemap);
    decoord(0, 0, wAttrmap);
    LD_B(SCREEN_HEIGHT);

loop:
    PUSH_BC;
    LD_C(SCREEN_WIDTH);

innerloop:
    LD_A_hl;
    PUSH_HL;
    SRL_A;
    IF_C goto UpperNybble;
    LD_HL(wTilesetPalettes);
    ADD_A_hl;
    LD_L_A;
    LD_A_addr(wTilesetPalettes + 1);
    ADC_A(0);
    LD_H_A;
    LD_A_hl;
    AND_A(0xf);
    goto next;


UpperNybble:
    LD_HL(wTilesetPalettes);
    ADD_A_hl;
    LD_L_A;
    LD_A_addr(wTilesetPalettes + 1);
    ADC_A(0);
    LD_H_A;
    LD_A_hl;
    SWAP_A;
    AND_A(0xf);


next:
    POP_HL;
    LD_de_A;
    RES_hl(7);
    INC_HL;
    INC_DE;
    DEC_C;
    IF_NZ goto innerloop;
    POP_BC;
    DEC_B;
    IF_NZ goto loop;
    RET;

}

void v_SwapTextboxPalettes_Conv(void){
    // hlcoord(0, 0, wTilemap);
    uint8_t* hl = coord(0, 0, wram->wTilemap);
    // decoord(0, 0, wAttrmap);
    uint8_t* de = coord(0, 0, wram->wAttrmap);
    // LD_B(SCREEN_HEIGHT);
    uint8_t b = SCREEN_HEIGHT;

    do {
    // loop:
        // PUSH_BC;
        // LD_C(SCREEN_WIDTH);
        uint8_t c = SCREEN_WIDTH;

        do {
        // innerloop:
            // LD_A_hl;
            uint8_t a = *hl;
            // PUSH_HL;
            // SRL_A;
            // IF_C goto UpperNybble;
            if(!(a & 1)) {
                // LD_HL(wTilesetPalettes);
                // ADD_A_hl;
                // LD_L_A;
                // LD_A_addr(wTilesetPalettes + 1);
                // ADC_A(0);
                // LD_H_A;
                // LD_A_hl;
                // AND_A(0xf);
                *de = (*(uint8_t*)AbsGBROMBankAddrToRAMAddr(BANK(av_SwapTextboxPalettes), wram->wTilesetPalettes + (a >> 1))) & 0xf;
                // goto next;
            }
            else {
            // UpperNybble:
                // LD_HL(wTilesetPalettes);
                // ADD_A_hl;
                // LD_L_A;
                // LD_A_addr(wTilesetPalettes + 1);
                // ADC_A(0);
                // LD_H_A;
                // LD_A_hl;
                // SWAP_A;
                // AND_A(0xf);
                *de = ((*(uint8_t*)AbsGBROMBankAddrToRAMAddr(BANK(av_SwapTextboxPalettes), wram->wTilesetPalettes + (a >> 1))) & 0xf0) >> 4;
            }
        // next:
            // POP_HL;
            // LD_de_A;
            // RES_hl(7);
            bit_reset(*hl, 7);
            // INC_HL;
            hl++;
            // INC_DE;
            de++;
            // DEC_C;
            // IF_NZ goto innerloop;
        } while(--c != 0);
        // POP_BC;
        // DEC_B;
        // IF_NZ goto loop;
    } while(--b != 0);
    // RET;
}

void v_ScrollBGMapPalettes(void){
    LD_HL(wBGMapBuffer);
    LD_DE(wBGMapPalBuffer);

loop:
    LD_A_hl;
    PUSH_HL;
    SRL_A;
    IF_C goto UpperNybble;

//  .LowerNybble
    LD_HL(wTilesetPalettes);
    ADD_A_hl;
    LD_L_A;
    LD_A_addr(wTilesetPalettes + 1);
    ADC_A(0);
    LD_H_A;
    LD_A_hl;
    AND_A(0xf);
    goto next;


UpperNybble:
    LD_HL(wTilesetPalettes);
    ADD_A_hl;
    LD_L_A;
    LD_A_addr(wTilesetPalettes + 1);
    ADC_A(0);
    LD_H_A;
    LD_A_hl;
    SWAP_A;
    AND_A(0xf);


next:
    POP_HL;
    LD_de_A;
    RES_hl(7);
    INC_HL;
    INC_DE;
    DEC_C;
    IF_NZ goto loop;
    RET;

}
