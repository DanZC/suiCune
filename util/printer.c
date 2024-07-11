#include "../constants.h"
#include "printer.h"
#undef percent
#include <stdlib.h>
#include <memory.h>
#include <SDL2/SDL.h>

// static uint32_t CGBToRGB32(uint16_t x) {
//     uint8_t b = ((x >> 10) & 0x1f) << 3;
//     uint8_t g = ((x >>  5) & 0x1f) << 3;
//     uint8_t r = ((x      ) & 0x1f) << 3;
//     return (0xff << 24) | (r << 16) | (g << 8) | b;
// }

void PrinterRenderTile(uint32_t* dest, size_t dest_stride, uint8_t attr, tile_t tile) {
    (void)attr;
    uint16_t t;
    if(gb.gb_reg.LCDC & LCDC_TILE_SELECT) {
        t = (tile * 0x10);
    }
    else {
        t = 0x800 + ((tile + 0x80) % 0x100) * 0x10;
    }
    for(int y = 0; y < 8; ++y) {
        for(int x = 0; x < 8; ++x) {
            uint8_t t1 = gb.vram[t + y * 2] << x;
            uint8_t t2 = gb.vram[t + y * 2 + 1] << x;
            uint8_t p = ((t1 & 0x80) >> 6) | ((t2 & 0x80) >> 7);
            // uint8_t px = ((attr & 0x07) << 2) + p;
            switch(p) {
                case 0x3: dest[dest_stride*y + x] = 0xff000000; break;
                case 0x2: dest[dest_stride*y + x] = 0xff555555; break;
                case 0x1: dest[dest_stride*y + x] = 0xffaaaaaa; break;
                case 0x0: dest[dest_stride*y + x] = 0xffffffff; break;
            }
        }
    }
}

void PrinterSaveTilemapToDisk(const uint8_t* tilemap, const uint8_t* attrmap, uint8_t w, uint8_t h) {
    char name[128];
    const uint8_t w2 = w * 8;
    const uint8_t h2 = h * 8;
    uint32_t* data = (uint32_t*)malloc(sizeof(uint32_t) * w2 * h2);
    memset(data, 0, LEN_2BPP_TILE * w * h);

    for(int y = 0; y < h; ++y) {
        for(int x = 0; x < w; ++x) {
            PrinterRenderTile(data + ((y * 8) * w2) + x * 8, w2, attrmap[(y*w + x)], tilemap[y*w + x]);
        }
    }
    SDL_Surface* surf = SDL_CreateRGBSurfaceFrom(data, w * 8, h * 8, 32, w * 8 * 4, 0xff0000, 0x00ff00, 0x0000ff, 0xff000000);
    time_t now = time(NULL);
    struct tm *nowt = localtime(&now);
    strftime(name, sizeof(name), "./printer%Y_%m_%d_T%H_%M_%S.bmp", nowt);
    SDL_SaveBMP(surf, name);
    SDL_FreeSurface(surf);
    free(data);
}