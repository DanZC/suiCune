#include "../constants.h"
#include "printer.h"
#undef percent
#include <stdlib.h>
#include <memory.h>
#include <SDL2/SDL.h>

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

uint32_t* gPrinterImageBuffer;
size_t gPrinterImageSize;
size_t gPrinterImageCap;

void Printer_Begin(void) {
    if(gPrinterImageBuffer != NULL)
        free(gPrinterImageBuffer);
    const size_t w2 = SCREEN_WIDTH * 8;
    const size_t h2 = SCREEN_HEIGHT * 8;
    gPrinterImageBuffer = (uint32_t*)malloc(sizeof(uint32_t) * w2 * h2);
    memset(gPrinterImageBuffer, 0, sizeof(uint32_t) * w2 * h2);
    gPrinterImageSize = 0;
    gPrinterImageCap = w2 * h2;
}

void Printer_AppendTilemap(const uint8_t* tilemap, const uint8_t* attrmap, uint8_t h) {
    const size_t w2 = SCREEN_WIDTH * 8;
    const size_t h2 = h * 8;
    const uint8_t w = SCREEN_WIDTH;
    uint32_t* dest = gPrinterImageBuffer + gPrinterImageSize;
    while(gPrinterImageSize + w2 * h2 > gPrinterImageCap) {
        gPrinterImageBuffer = realloc(gPrinterImageBuffer, (gPrinterImageCap * 2) * sizeof(uint32_t));
        dest = gPrinterImageBuffer + gPrinterImageSize;
        gPrinterImageCap = gPrinterImageCap * 2;
    }
    for(int y = 0; y < h; ++y) {
        for(int x = 0; x < w; ++x) {
            PrinterRenderTile(dest + ((y * 8) * w2) + x * 8, w2, attrmap[(y*w + x)], tilemap[y*w + x]);
        }
    }
    gPrinterImageSize = gPrinterImageSize + w2 * h2;
}

void Printer_SaveToDisk(void) {
    char name[128];
    const size_t w2 = SCREEN_WIDTH * 8;
    const size_t h2 = (gPrinterImageSize / w2);
    SDL_Surface* surf = SDL_CreateRGBSurfaceFrom(gPrinterImageBuffer, w2, h2, 32, w2 * 4, 0xff0000, 0x00ff00, 0x0000ff, 0xff000000);
    time_t now = time(NULL);
    struct tm *nowt = localtime(&now);
    strftime(name, sizeof(name), "./printer%Y_%m_%d_T%H_%M_%S.bmp", nowt);
    SDL_SaveBMP(surf, name);
    SDL_FreeSurface(surf);
    return Printer_CleanUp();
}

void Printer_CleanUp(void) {
    if(gPrinterImageBuffer != NULL)
        free(gPrinterImageBuffer);
    gPrinterImageBuffer = NULL;
    gPrinterImageSize = 0;
    gPrinterImageCap = 0;
}