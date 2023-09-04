#include "../../constants.h"
#include "load_overworld_font.h"
#include "../../charmap.h"

void LoadOverworldFont(void){
    LD_DE(mLoadOverworldFont_OverworldFontGFX);
    LD_HL(vTiles1);
    LD_BC((BANK(aLoadOverworldFont_OverworldFontGFX) << 8) | 0x80);
    CALL(aGet2bpp);
    LD_DE(mLoadOverworldFont_OverworldFontSpaceGFX);
    LD_HL(vTiles2 + LEN_2BPP_TILE * CHAR_SPACE);
    LD_BC((BANK(aLoadOverworldFont_OverworldFontSpaceGFX) << 8) | 1);
    CALL(aGet2bpp);
    RET;

// OverworldFontGFX:
// INCBIN "gfx/font/overworld.2bpp"


// OverworldFontSpaceGFX:
// INCBIN "gfx/font/overworld_space.2bpp"

}

void LoadOverworldFont_Conv(void){
    // LD_DE(mLoadOverworldFont_OverworldFontGFX);
    // LD_HL(vTiles1);
    // LD_BC((BANK(aLoadOverworldFont_OverworldFontGFX) << 8) | 0x80);
    // CALL(aGet2bpp);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles1, "gfx/font/overworld.png", 0, 0x80);
    // LD_DE(mLoadOverworldFont_OverworldFontSpaceGFX);
    // LD_HL(vTiles2 + LEN_2BPP_TILE * CHAR_SPACE);
    // LD_BC((BANK(aLoadOverworldFont_OverworldFontSpaceGFX) << 8) | 1);
    // CALL(aGet2bpp);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles2 + LEN_2BPP_TILE * CHAR_SPACE, "gfx/font/overworld_space.png", 0, 1);
    // RET;
}
