#include "../../constants.h"
#include "pack_kris.h"

const uint16_t PackFGFXPointers[] = {
    //dw ['PackFGFX + (15 * LEN_2BPP_TILE) * 1'];  // ITEM_POCKET
    //dw ['PackFGFX + (15 * LEN_2BPP_TILE) * 3'];  // BALL_POCKET
    //dw ['PackFGFX + (15 * LEN_2BPP_TILE) * 0'];  // KEY_ITEM_POCKET
    //dw ['PackFGFX + (15 * LEN_2BPP_TILE) * 2'];  // TM_HM_POCKET
    [ITEM_POCKET]       = 15 * 1,
    [BALL_POCKET]       = 15 * 3,
    [KEY_ITEM_POCKET]   = 15 * 0,
    [TM_HM_POCKET]      = 15 * 2,
};

const char PackFGFX[] = "gfx/pack/pack_f.png";

void DrawKrisPackGFX(uint8_t e){
    // LD_HL(mPackFGFXPointers);
    // ADD_HL_DE;
    // ADD_HL_DE;
    // LD_A_hli;
    // LD_E_A;
    // LD_D_hl;
    // LD_HL(vTiles2 + LEN_2BPP_TILE * 0x50);
    // LD_BC((BANK(aPackFGFX) << 8) | 15);
    // CALL(aRequest2bpp);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles2 + LEN_2BPP_TILE * 0x50, PackFGFX, PackFGFXPointers[e], 15);
    // RET;

}
