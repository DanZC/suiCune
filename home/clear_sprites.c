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
    uint8_t* hl = (uint8_t*)wram->wVirtualOAMSprite;
    uint8_t b = (wVirtualOAMEnd - wVirtualOAM);
    do {
        (*hl++) = 0;
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
    struct SpriteOAM* hl = wram->wVirtualOAMSprite;
    uint8_t b = NUM_SPRITE_OAM_STRUCTS;
    do {
        hl->yCoord = SCREEN_WIDTH_PX;  // y
        hl++;
    } while(--b != 0);
}