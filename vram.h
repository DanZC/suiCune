#pragma once

#if defined(__cplusplus) || defined(_MSC_VER)
struct vram_s
#else
// A struct representing VRAM.
struct __attribute__((packed)) vram_s
#endif
{
    uint8_t vTiles0[0x80 * LEN_2BPP_TILE];
    uint8_t vTiles1[0x80 * LEN_2BPP_TILE];
    uint8_t vTiles2[0x80 * LEN_2BPP_TILE];
    uint8_t vBGMap0[BG_MAP_WIDTH * BG_MAP_HEIGHT];
    uint8_t vBGMap1[BG_MAP_WIDTH * BG_MAP_HEIGHT];
    uint8_t vTiles3[0x80 * LEN_2BPP_TILE];
    uint8_t vTiles4[0x80 * LEN_2BPP_TILE];
    uint8_t vTiles5[0x80 * LEN_2BPP_TILE];
    uint8_t vBGMap2[BG_MAP_WIDTH * BG_MAP_HEIGHT];
    uint8_t vBGMap3[BG_MAP_WIDTH * BG_MAP_HEIGHT];
};
