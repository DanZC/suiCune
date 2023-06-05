#include "../constants.h"
#include "clear_sprites.h"

void ClearSprites(void){
    //  Erase OAM data
    LD_HL(wVirtualOAM);
    LD_B(wVirtualOAMEnd - wVirtualOAM);
    XOR_A_A;

loop:
        LD_hli_A;
    DEC_B;
    IF_NZ goto loop;
    RET;

}

//  Erase OAM data
void ClearSprites_Conv(void){
    uint16_t hl = wVirtualOAM;
    uint8_t b = (wVirtualOAMEnd - wVirtualOAM);
    do {
        gb_write(hl++, 0);
    } while(--b != 0);
}

void HideSprites(void){
    //  Set all OAM y-positions to 160 to hide them offscreen
    LD_HL(wVirtualOAMSprite00YCoord);
    LD_DE(SPRITEOAMSTRUCT_LENGTH);
    LD_B(NUM_SPRITE_OAM_STRUCTS);
    LD_A(SCREEN_WIDTH_PX);

loop:
        LD_hl_A;  // y
    ADD_HL_DE;
    DEC_B;
    IF_NZ goto loop;
    RET;

}

//  Set all OAM y-positions to 160 to hide them offscreen
void HideSprites_Conv(void){
    uint16_t hl = wVirtualOAMSprite00YCoord;
    uint8_t b = NUM_SPRITE_OAM_STRUCTS;
    do {
        gb_write(hl, SCREEN_WIDTH_PX);  // y
        hl += SPRITEOAMSTRUCT_LENGTH;
    } while(--b != 0);
}