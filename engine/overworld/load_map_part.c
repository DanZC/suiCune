#include "../../constants.h"
#include "load_map_part.h"

void v_LoadMapPart(void){
    return v_LoadMapPart_Conv();
    LD_HL(wSurroundingTiles);
    LD_A_addr(wMetatileStandingY);
    AND_A_A;
    IF_Z goto top_row;
    LD_BC(SURROUNDING_WIDTH * 2);
    ADD_HL_BC;


top_row:
    LD_A_addr(wMetatileStandingX);
    AND_A_A;
    IF_Z goto left_column;
    INC_HL;
    INC_HL;


left_column:
    decoord(0, 0, wTilemap);
    LD_B(SCREEN_HEIGHT);

loop:
    LD_C(SCREEN_WIDTH);

loop2:
    LD_A_hli;
    LD_de_A;
    INC_DE;
    DEC_C;
    IF_NZ goto loop2;
    LD_A_L;
    ADD_A(METATILE_WIDTH);
    LD_L_A;
    IF_NC goto carry;
    INC_H;


carry:
    DEC_B;
    IF_NZ goto loop;
    RET;

}

void v_LoadMapPart_Conv(void){
    // LD_HL(wSurroundingTiles);
    const uint8_t* hl = wram->wSurroundingTiles;
    // LD_A_addr(wMetatileStandingY);
    // AND_A_A;
    // IF_Z goto top_row;
    if(wram->wMetatileStandingY != 0) {
        // LD_BC(SURROUNDING_WIDTH * 2);
        // ADD_HL_BC;
        hl += SURROUNDING_WIDTH * 2;
    }

// top_row:
    // LD_A_addr(wMetatileStandingX);
    // AND_A_A;
    // IF_Z goto left_column;
    if(wram->wMetatileStandingX != 0) {
        // INC_HL;
        // INC_HL;
        hl += 2;
    }

// left_column:
    // decoord(0, 0, wTilemap);
    uint8_t* de = coord(0, 0, wram->wTilemap);
    // LD_B(SCREEN_HEIGHT);
    uint8_t b = SCREEN_HEIGHT;

    do {
    // loop:
        // LD_C(SCREEN_WIDTH);
        uint8_t c = SCREEN_WIDTH;

        do {
        // loop2:
            // LD_A_hli;
            // LD_de_A;
            // INC_DE;
            *(de++) = *(hl++);
            // DEC_C;
            // IF_NZ goto loop2;
        } while(--c != 0);
        // LD_A_L;
        // ADD_A(METATILE_WIDTH);
        // LD_L_A;
        // IF_NC goto carry;
        // INC_H;
        hl += METATILE_WIDTH;


    // carry:
        // DEC_B;
        // IF_NZ goto loop;
    } while(--b != 0);
    // RET;
}
