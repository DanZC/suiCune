#include "../constants.h"
#include "sprite_anims.h"
#include "../engine/gfx/sprites.h"

void InitSpriteAnimStruct(void){
        LD_addr_A(wSpriteAnimID);
    LDH_A_addr(hROMBank);
    PUSH_AF;

    LD_A(BANK(av_InitSpriteAnimStruct));
    RST(aBankswitch);
    LD_A_addr(wSpriteAnimID);

    CALL(av_InitSpriteAnimStruct);

    POP_AF;
    RST(aBankswitch);

    RET;

}

struct SpriteAnim* InitSpriteAnimStruct_Conv(uint8_t a, uint16_t de){
    // LD_addr_A(wSpriteAnimID);
    wram->wSpriteAnimID = a;
    // LDH_A_addr(hROMBank);
    // PUSH_AF;

    // LD_A(BANK(av_InitSpriteAnimStruct));
    // RST(aBankswitch);
    // LD_A_addr(wSpriteAnimID);
    bank_push(BANK(av_InitSpriteAnimStruct));

    // CALL(av_InitSpriteAnimStruct);
    struct SpriteAnim* bc = v_InitSpriteAnimStruct_Conv(a, de);

    // POP_AF;
    // RST(aBankswitch);
    bank_pop;

    // RET;
    return bc;
}

void ReinitSpriteAnimFrame(void){
        LD_addr_A(wSpriteAnimID);
    LDH_A_addr(hROMBank);
    PUSH_AF;

    LD_A(BANK(av_ReinitSpriteAnimFrame));
    RST(aBankswitch);
    LD_A_addr(wSpriteAnimID);

    CALL(av_ReinitSpriteAnimFrame);

    POP_AF;
    RST(aBankswitch);

    RET;

}

void ReinitSpriteAnimFrame_Conv(struct SpriteAnim* bc, uint8_t a){
    // LD_addr_A(wSpriteAnimID);
    wram->wSpriteAnimID = a;
    // LDH_A_addr(hROMBank);
    // PUSH_AF;

    // LD_A(BANK(av_ReinitSpriteAnimFrame));
    // RST(aBankswitch);
    // LD_A_addr(wSpriteAnimID);
    bank_push(BANK(av_ReinitSpriteAnimFrame));

    // CALL(av_ReinitSpriteAnimFrame);
    v_ReinitSpriteAnimFrame_Conv(bc, a);

    // POP_AF;
    // RST(aBankswitch);
    bank_pop;

    // RET;
}
