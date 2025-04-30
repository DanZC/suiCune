#include "../constants.h"
#include "sprite_anims.h"
#include "../engine/gfx/sprites.h"

struct SpriteAnim* InitSpriteAnimStruct(uint8_t a, uint16_t de){
    // LD_addr_A(wSpriteAnimID);
    wram->wSpriteAnimID = a;
    // LDH_A_addr(hROMBank);
    // PUSH_AF;

    // LD_A(BANK(av_InitSpriteAnimStruct));
    // RST(aBankswitch);
    // LD_A_addr(wSpriteAnimID);

    // CALL(av_InitSpriteAnimStruct);
    struct SpriteAnim* bc = v_InitSpriteAnimStruct(a, de);

    // POP_AF;
    // RST(aBankswitch);

    // RET;
    return bc;
}

void ReinitSpriteAnimFrame(struct SpriteAnim* bc, uint8_t a){
    // LD_addr_A(wSpriteAnimID);
    wram->wSpriteAnimID = a;
    // LDH_A_addr(hROMBank);
    // PUSH_AF;

    // LD_A(BANK(av_ReinitSpriteAnimFrame));
    // RST(aBankswitch);
    // LD_A_addr(wSpriteAnimID);

    // CALL(av_ReinitSpriteAnimFrame);
    v_ReinitSpriteAnimFrame(bc, a);

    // POP_AF;
    // RST(aBankswitch);

    // RET;
}
