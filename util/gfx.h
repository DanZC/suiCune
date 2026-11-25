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

    // bit 0: overworld sprite updating on/off
    // bit 1: something to do with sprite updates
    // bit 6: something to do with text
    // bit 7: on when surf initiates
    //        flickers when climbing waterfall
    uint8_t vramState;
} gfx_s;

extern gfx_s gGFX;
