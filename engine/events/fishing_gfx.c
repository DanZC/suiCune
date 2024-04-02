#include "../../constants.h"
#include "fishing_gfx.h"
#include "../../home/copy.h"

const char FishingGFX[] = "gfx/overworld/chris_fish.png";
const char KrisFishingGFX[] = "gfx/overworld/kris_fish.png";

// static void LoadFishingGFX_LoadGFX(uint8_t* hl, const char* path, int start_tile){
//     // LD_BC((BANK(aFishingGFX) << 8) | 2);
//     // PUSH_DE;
//     // CALL(aGet2bpp);
//     LoadPNG2bppAssetSectionToVRAM(hl, path, start_tile, 2);
//     // POP_DE;
//     // LD_HL(2 * LEN_2BPP_TILE);
//     // ADD_HL_DE;
//     // LD_D_H;
//     // LD_E_L;
//     // RET;
// }

void LoadFishingGFX(void){
    uint8_t buf[8 * LEN_2BPP_TILE];
    // LDH_A_addr(rVBK);
    // PUSH_AF;
    // LD_A(0x1);
    // LDH_addr_A(rVBK);

    // LD_DE(mFishingGFX);
    // LD_A_addr(wPlayerGender);
    // BIT_A(PLAYERGENDER_FEMALE_F);
    // IF_Z goto got_gender;
    // LD_DE(mKrisFishingGFX);
    const char* gfx = (bit_test(wram->wPlayerGender, PLAYERGENDER_FEMALE_F))? KrisFishingGFX: FishingGFX;

// got_gender:
    // Load all the gfx at once into a buffer and then copy the segments seperately.
    LoadPNG2bppAssetSectionToVRAM(buf, gfx, 0, 8);
    // LD_HL(vTiles0 + LEN_2BPP_TILE * 0x02);
    // CALL(aLoadFishingGFX_LoadGFX);
    CopyBytes_Conv2(vram->vTiles3 + LEN_2BPP_TILE * 0x02, buf + LEN_2BPP_TILE * 0, LEN_2BPP_TILE * 2);
    // LD_HL(vTiles0 + LEN_2BPP_TILE * 0x06);
    // CALL(aLoadFishingGFX_LoadGFX);
    CopyBytes_Conv2(vram->vTiles3 + LEN_2BPP_TILE * 0x06, buf + LEN_2BPP_TILE * 2, LEN_2BPP_TILE * 2);
    // LD_HL(vTiles0 + LEN_2BPP_TILE * 0x0a);
    // CALL(aLoadFishingGFX_LoadGFX);
    CopyBytes_Conv2(vram->vTiles3 + LEN_2BPP_TILE * 0x0a, buf + LEN_2BPP_TILE * 4, LEN_2BPP_TILE * 2);
    // LD_HL(vTiles0 + LEN_2BPP_TILE * 0xfc);
    // CALL(aLoadFishingGFX_LoadGFX);
    CopyBytes_Conv2(vram->vTiles3 + LEN_2BPP_TILE * 0xfc, buf + LEN_2BPP_TILE * 6, LEN_2BPP_TILE * 2);

    // POP_AF;
    // LDH_addr_A(rVBK);
    // RET;
}
