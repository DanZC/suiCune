#pragma once

typedef struct GFX {
    struct SpriteOAM virtualOAMSprite[NUM_SPRITE_OAM_STRUCTS];
    color_t bgPals1[8 * NUM_PAL_COLORS];
    color_t obPals1[8 * NUM_PAL_COLORS];
    color_t bgPals2[8 * NUM_PAL_COLORS];
    color_t obPals2[8 * NUM_PAL_COLORS];
    uint8_t LYOverrides[256];
    uint8_t LYOverridesBackup[256];
    tile_t BGMapBuffer[SCREEN_WIDTH * 2];
    uint8_t BGMapPalBuffer[SCREEN_WIDTH * 2];
    uint16_t BGMapBufferPointers[SCREEN_WIDTH];
} gfx_s;

extern gfx_s gGFX;
