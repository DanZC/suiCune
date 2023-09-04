#include "../../constants.h"
#include "place_graphic.h"

//  Fill wBoxAlignment-aligned box width b height c
//  with iterating tile starting from hGraphicStartTile at hl.
void PlaceGraphic(void){
    LD_DE(SCREEN_WIDTH);

    LD_A_addr(wBoxAlignment);
    AND_A_A;
    IF_NZ goto right;

    LDH_A_addr(hGraphicStartTile);

x1:
    PUSH_BC;
    PUSH_HL;


y1:
    LD_hl_A;
    ADD_HL_DE;
    INC_A;
    DEC_C;
    IF_NZ goto y1;

    POP_HL;
    INC_HL;
    POP_BC;
    DEC_B;
    IF_NZ goto x1;
    RET;


right:
//  Right-aligned.
    PUSH_BC;
    LD_B(0);
    DEC_C;
    ADD_HL_BC;
    POP_BC;

    LDH_A_addr(hGraphicStartTile);

x2:
    PUSH_BC;
    PUSH_HL;


y2:
    LD_hl_A;
    ADD_HL_DE;
    INC_A;
    DEC_C;
    IF_NZ goto y2;

    POP_HL;
    DEC_HL;
    POP_BC;
    DEC_B;
    IF_NZ goto x2;
    RET;

}

//  Fill wBoxAlignment-aligned box width b height c
//  with iterating tile starting from hGraphicStartTile at hl.
void PlaceGraphic_Conv(uint8_t* hl, uint8_t b, uint8_t c){
    // LD_DE(SCREEN_WIDTH);
    uint8_t a;

    // LD_A_addr(wBoxAlignment);
    // AND_A_A;
    // IF_NZ goto right;
    if(wram->wBoxAlignment == 0) {
        // LDH_A_addr(hGraphicStartTile);
        a = hram->hGraphicStartTile;
    // x1:
        do {
            // PUSH_BC;
            // PUSH_HL;
            uint8_t* hl2 = hl;
            uint8_t c2 = c;

            do {
            // y1:
                // LD_hl_A;
                *hl = a++;
                hl += SCREEN_WIDTH;
                // ADD_HL_DE;
                // INC_A;
                // DEC_C;
                // IF_NZ goto y1;
            } while(--c != 0);

            // POP_HL;
            // INC_HL;
            hl = hl2 + 1;
            // POP_BC;
            c = c2;
            // DEC_B;
            // IF_NZ goto x1;
        } while(--b != 0);
        // RET;
    }
    else {


    // right:
    //  Right-aligned.
        // PUSH_BC;
        // LD_B(0);
        // DEC_C;
        // ADD_HL_BC;
        // POP_BC;
        hl += c - 1;

        // LDH_A_addr(hGraphicStartTile);
        a = hram->hGraphicStartTile;

        do {
        // x2:
            // PUSH_BC;
            // PUSH_HL;
            uint8_t* hl2 = hl;
            uint8_t c2 = c;

            do {
            // y2:
                // LD_hl_A;
                *hl = a++;
                // ADD_HL_DE;
                hl += SCREEN_WIDTH;
                // INC_A;
                // DEC_C;
                // IF_NZ goto y2;
            } while(--c != 0);

            // POP_HL;
            // DEC_HL;
            hl = hl2 - 1;
            // POP_BC;
            c = c2;
            // DEC_B;
            // IF_NZ goto x2;
        } while(--b != 0);
        // RET;
    }

}