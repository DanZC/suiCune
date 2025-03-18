#include "../constants.h"
#include "clear_sprites.h"
#include "copy.h"

//  Erase OAM data
void ClearSprites(void){
    ByteFill(wram->wVirtualOAMSprite, sizeof(wram->wVirtualOAMSprite), 0);
}

//  Set all OAM y-positions to 160 to hide them offscreen
void HideSprites(void){
    for(uint32_t i = 0; i < NUM_SPRITE_OAM_STRUCTS; ++i) {
        wram->wVirtualOAMSprite[i].yCoord = SCREEN_WIDTH_PX;  // y
    }
}