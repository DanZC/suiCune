#include "../constants.h"
#include "sprite_updates.h"

void DisableSpriteUpdates(void){
        XOR_A_A;
    LDH_addr_A(hMapAnims);
    LD_A_addr(wVramState);
    RES_A(0);
    LD_addr_A(wVramState);
    LD_A(0x0);
    LD_addr_A(wSpriteUpdatesEnabled);
    RET;

}

void DisableSpriteUpdates_Conv(void){
    // XOR_A_A;
    // LDH_addr_A(hMapAnims);
    hMapAnims = 0;
    // LD_A_addr(wVramState);
    // RES_A(0);
    // LD_addr_A(wVramState);
    bit_reset(wram->wVramState, 0);
    // LD_A(0x0);
    // LD_addr_A(wSpriteUpdatesEnabled);
    wram->wSpriteUpdatesEnabled = 0x0;
    // RET;
}

void EnableSpriteUpdates(void){
        LD_A(0x1);
    LD_addr_A(wSpriteUpdatesEnabled);
    LD_A_addr(wVramState);
    SET_A(0);
    LD_addr_A(wVramState);
    LD_A(0x1);
    LDH_addr_A(hMapAnims);
    RET;

}

void EnableSpriteUpdates_Conv(void){
    // LD_A(0x1);
    // LD_addr_A(wSpriteUpdatesEnabled);
    wram->wSpriteUpdatesEnabled = 0x1;
    // LD_A_addr(wVramState);
    // SET_A(0);
    // LD_addr_A(wVramState);
    bit_set(wram->wVramState, 0);
    // LD_A(0x1);
    // LDH_addr_A(hMapAnims);
    hMapAnims = 0x1;
    // RET;
}
