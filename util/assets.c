#ifndef NO_PHYSFS
#include <physfs.h>
#endif
#include <stdlib.h>
#include "../constants.h"
#include "assets.h"
#include "stb_image.h"
#include <assert.h>

// Loads asset file from archive to a heap-allocated buffer.
asset_s LoadAsset(const char* filename) {
    #if !defined(NO_PHYSFS)
    PHYSFS_File* file = PHYSFS_openRead(filename);
    if(!file) {
        fprintf(stderr, "LoadAsset Error: %s", PHYSFS_getErrorByCode(PHYSFS_getLastErrorCode()));
        return (asset_s){NULL, 0};
    }
    int64_t size = PHYSFS_fileLength(file);
    if(size == -1) {
        fprintf(stderr, "LoadAsset Error: %s", PHYSFS_getErrorByCode(PHYSFS_getLastErrorCode()));
        PHYSFS_close(file);
        return (asset_s){NULL, 0};
    }
    uint8_t* buf = malloc((size_t)size);
    if(buf == NULL) {
        fprintf(stderr, "LoadAsset Error: Bad malloc.");
        return (asset_s){NULL, 0};
    }
    PHYSFS_readBytes(file, buf, (size_t)size);
    PHYSFS_close(file);
    #else 
    FILE* file = fopen(filename, "rb");
    if(!file) {
        fprintf(stderr, "LoadAsset Error");
        return (asset_s){NULL, 0};
    }
    fseek(file, 0, SEEK_END);
    int64_t size = ftello(file);
    fseek(file, 0, SEEK_SET);
    uint8_t* buf = malloc((size_t)size);
    if(buf == NULL) {
        fprintf(stderr, "LoadAsset Error: Bad malloc.");
        return (asset_s){NULL, 0};
    }
    fread(buf, (size_t)size, 1, file);
    fclose(file);
    #endif
    return (asset_s){buf, (size_t)size};
}

// Loads asset file from archive to a user-provided buffer of size buf_size.
// If the buffer size is less than the size of the file being loaded, the 
// data loaded will be truncated to the buffer size.
asset_s LoadAssetToBuffer(void* buffer, size_t buf_size, const char* filename) {
    PHYSFS_File* file = PHYSFS_openRead(filename);
    if(!file) {
        fprintf(stderr, "LoadAsset Error: %s", PHYSFS_getErrorByCode(PHYSFS_getLastErrorCode()));
        return (asset_s){NULL, 0};
    }
    int64_t size = PHYSFS_fileLength(file);
    if(size == -1) {
        fprintf(stderr, "LoadAsset Error: %s", PHYSFS_getErrorByCode(PHYSFS_getLastErrorCode()));
        PHYSFS_close(file);
        return (asset_s){NULL, 0};
    }
    size_t rsize = ((size_t)size > buf_size)? buf_size: (size_t)size;
    PHYSFS_readBytes(file, buffer, rsize);
    PHYSFS_close(file);
    return (asset_s){buffer, rsize};
}

// Returns false if ptr is NULL or size is 0.
bool IsAssetValid(asset_s asset) {
    return asset.ptr != NULL && asset.size != 0;
}

void LoadAssetIfNotLoaded(asset_s* asset, const char* filename) {
    if(!IsAssetValid(*asset)) {
        *asset = LoadAsset(filename);
    }
}

// Just a wrapper for free() which makes intent more clear.
void FreeAsset(asset_s asset) {
    free(asset.ptr);
}

// Converts an 8x8 1bpp grayscale square from a src image with stride width to GB pixel format and writes the result
// to dest.
static void CopyPNG1bppGrayTileToGB(uint8_t* dest, const uint8_t* src, int stride) {
    if(stride == 0)
        return;
    for(int yy = 0; yy < 8; ++yy) {
        dest[yy * 2 + 0] = 0;
        dest[yy * 2 + 1] = 0;
        for(int xx = 0; xx < 8; ++xx) {
            uint8_t pixel;
            switch(src[yy*stride + xx]) {
                case 0x00: pixel = 0x3; break;
                default: fprintf(stderr, "%s: Pixel error #%06X.\n", __func__, src[yy*stride + xx]);
                    // fallthrough
                case 0xff: pixel = 0x0; break;
            }
            dest[yy * 2 + 0] |= ((pixel & 0b01)? (1 << (7 - xx)): 0);
            dest[yy * 2 + 1] |= ((pixel & 0b10)? (1 << (7 - xx)): 0);
        }
    }
}

// Converts an 8x8 2bpp grayscale square from a src image with stride width to GB pixel format and writes the result
// to dest.
static void CopyPNG2bppGrayTileToGB(uint8_t* dest, const uint8_t* src, int stride) {
    if(stride == 0)
        return;
    for(int yy = 0; yy < 8; ++yy) {
        dest[yy * 2 + 0] = 0;
        dest[yy * 2 + 1] = 0;
        for(int xx = 0; xx < 8; ++xx) {
            uint8_t pixel;
            switch(src[yy*stride + xx]) {
                case 0x00: pixel = 0x3; break;
                case 0x55: pixel = 0x2; break;
                case 0xaa: pixel = 0x1; break;
                default: fprintf(stderr, "%s: Pixel error #%06X.\n", __func__, src[yy*stride + xx]);
                    // fallthrough
                case 0xff: pixel = 0x0; break;
            }
            dest[yy * 2 + 0] |= ((pixel & 0b01)? (1 << (7 - xx)): 0);
            dest[yy * 2 + 1] |= ((pixel & 0b10)? (1 << (7 - xx)): 0);
        }
    }
}

// Converts an 8x8 2bpp color square from a src image with stride width to GB pixel format and writes the result
// to dest.
static void CopyPNG2bppColorTileToGB(uint8_t* dest, const uint8_t* src, int stride, int n, const uint32_t pal[]) {
    if(stride == 0)
        return;
    for(int yy = 0; yy < 8; ++yy) {
        dest[yy * 2 + 0] = 0;
        dest[yy * 2 + 1] = 0;
        for(int xx = 0; xx < 8; ++xx) {
            const uint8_t* start = &src[((yy*stride) + xx)*n];
            uint32_t pixel = 0;
            for(int i = n - 1; i >= 0; --i) {
                pixel = (pixel << 8) | start[i];
            }
            if(pixel == pal[0]) {
                pixel = 0x3;
            } else if(pixel == pal[1]) {
                pixel = 0x2;
            } else if(pixel == pal[2]) {
                pixel = 0x1;
            } else if(pixel == pal[3]) {
                pixel = 0x0;
            } else {
                fprintf(stderr, "%s: Pixel error #%06X.\n", __func__, pixel);
                pixel = 0x0;
            }
            dest[yy * 2 + 0] |= ((pixel & 0b01)? (1 << (7 - xx)): 0);
            dest[yy * 2 + 1] |= ((pixel & 0b10)? (1 << (7 - xx)): 0);
        }
    }
}

// Loads a 1bpp PNG asset from an archive, converts it to GB pixel format,
// and writes the result to dest, assumedly a vram destination.
void LoadPNG1bppAssetToVRAM(void* dest, const char* filename) {
    uint8_t* d = dest;
    asset_s a = LoadAsset(filename);
    // printf("Loaded asset %s (%lld bytes)\n", filename, a.size);
    if(!a.ptr) {
        exit(-1);
    }
    int x, y, n;
    uint8_t* pix = stbi_load_from_memory(a.ptr, (int)a.size, &x, &y, &n, 0);
    if(!pix) {
        fprintf(stderr, "%s: Load error on image %s. Reason: %s\n", __func__, filename, stbi_failure_reason());
        exit(-1);
    }
    printf("%d-channel %dx%d image\n", n, x, y);
    FreeAsset(a);
    int numTiles = (y / 8) * (x / 8);
    int tilesPerRow = (x / 8);
    printf("%d tiles to write.\n", numTiles);
    if(n == 1) {
        for(int i = 0; i < numTiles; ++i) {
            CopyPNG1bppGrayTileToGB(&d[i * LEN_2BPP_TILE], &pix[(((i/tilesPerRow)*8)*x) + ((i%tilesPerRow)*8)], x);
        }
    }
    else {
        // Hack to make palette conversion work.
        const uint32_t* palette = (uint32_t*)&stbi_g_png_palette[0];
        // for(int i = 0; i < 4; ++i) {
        //     printf("Color %d: r=%d, g=%d, b=%d\n", i, palette[i] & 0xff, (palette[i] & 0xff00) >> 8, (palette[i] & 0xff0000) >> 16);
        // }
        for(int i = 0; i < numTiles; ++i) {
            CopyPNG2bppColorTileToGB(&d[i * LEN_2BPP_TILE], &pix[((((i/tilesPerRow)*8)*x) + ((i%tilesPerRow)*8))*n], x, n, palette);
        }
    }
    stbi_image_free(pix);
}

// Loads a 2bpp PNG asset from an archive, converts it to GB pixel format,
// and writes the result to dest, assumedly a vram destination.
void LoadPNG2bppAssetToVRAM(void* dest, const char* filename) {
    uint8_t* d = dest;
    asset_s a = LoadAsset(filename);
    // printf("Loaded asset %s (%lld bytes)\n", filename, a.size);
    if(!a.ptr) {
        exit(-1);
    }
    int x, y, n;
    uint8_t* pix = stbi_load_from_memory(a.ptr, (int)a.size, &x, &y, &n, 0);
    if(!pix) {
        fprintf(stderr, "%s: Load error on image %s. Reason: %s\n", __func__, filename, stbi_failure_reason());
        exit(-1);
    }
    printf("%d-channel %dx%d image\n", n, x, y);
    FreeAsset(a);
    int numTiles = (y / 8) * (x / 8);
    int tilesPerRow = (x / 8);
    printf("%d tiles to write.\n", numTiles);
    if(n == 1) {
        for(int i = 0; i < numTiles; ++i) {
            CopyPNG2bppGrayTileToGB(&d[i * LEN_2BPP_TILE], &pix[(((i/tilesPerRow)*8)*x) + ((i%tilesPerRow)*8)], x);
        }
    }
    else {
        // Hack to make palette conversion work.
        const uint32_t* palette = (uint32_t*)&stbi_g_png_palette[0];
        // for(int i = 0; i < 4; ++i) {
        //     printf("Color %d: r=%d, g=%d, b=%d\n", i, palette[i] & 0xff, (palette[i] & 0xff00) >> 8, (palette[i] & 0xff0000) >> 16);
        // }
        for(int i = 0; i < numTiles; ++i) {
            CopyPNG2bppColorTileToGB(&d[i * LEN_2BPP_TILE], &pix[((((i/tilesPerRow)*8)*x) + ((i%tilesPerRow)*8))*n], x, n, palette);
        }
    }
    stbi_image_free(pix);
}

// Loads a 1bpp PNG asset section from an archive, converts it to GB pixel format,
// and writes the result to dest, assumedly a vram destination.
void LoadPNG1bppAssetSectionToVRAM(void* dest, const char* filename, int start_tile, int tile_count) {
    uint8_t* d = dest;
    asset_s a = LoadAsset(filename);
    // printf("Loaded asset %s (%lld bytes)\n", filename, a.size);
    if(!a.ptr) {
        exit(-1);
    }
    int x, y, n;
    uint8_t* pix = stbi_load_from_memory(a.ptr, (int)a.size, &x, &y, &n, 0);
    if(!pix) {
        fprintf(stderr, "%s: Load error on image %s. Reason: %s\n", __func__, filename, stbi_failure_reason());
        exit(-1);
    }
    // printf("%d-channel %dx%d image\n", n, x, y);
    FreeAsset(a);
    int numTiles = (((y / 8) * (x / 8)) - start_tile > tile_count)? tile_count: ((y / 8) * (x / 8)) - start_tile;
    int tilesPerRow = (x / 8);
    // printf("%d tiles to write.\n", numTiles);
    if(n == 1) {
        for(int i = 0; i < numTiles; ++i) {
            CopyPNG1bppGrayTileToGB(&d[i * LEN_2BPP_TILE], &pix[((((start_tile+i)/tilesPerRow)*8)*x) + (((start_tile+i)%tilesPerRow)*8)], x);
        }
    }
    else {
        // Hack to make palette conversion work.
        const uint32_t* palette = (uint32_t*)&stbi_g_png_palette[0];
        // for(int i = 0; i < 4; ++i) {
        //     printf("Color %d: r=%d, g=%d, b=%d\n", i, palette[i] & 0xff, (palette[i] & 0xff00) >> 8, (palette[i] & 0xff0000) >> 16);
        // }
        for(int i = 0; i < numTiles; ++i) {
            CopyPNG2bppColorTileToGB(&d[i * LEN_2BPP_TILE], &pix[(((i/tilesPerRow)*8*n)*x) + ((i%tilesPerRow)*8*n)], x, n, palette);
        }
    }
    stbi_image_free(pix);
}

// Loads a 2bpp PNG asset section from an archive, converts it to GB pixel format,
// and writes the result to dest, assumedly a vram destination.
void LoadPNG2bppAssetSectionToVRAM(void* dest, const char* filename, int start_tile, int tile_count) {
    uint8_t* d = dest;
    asset_s a = LoadAsset(filename);
    // printf("Loaded asset %s (%lld bytes)\n", filename, a.size);
    if(!a.ptr) {
        exit(-1);
    }
    int x, y, n;
    uint8_t* pix = stbi_load_from_memory(a.ptr, (int)a.size, &x, &y, &n, 0);
    if(!pix) {
        fprintf(stderr, "%s: Load error on image %s. Reason: %s\n", __func__, filename, stbi_failure_reason());
        exit(-1);
    }
    // printf("%d-channel %dx%d image\n", n, x, y);
    FreeAsset(a);
    int numTiles = (((y / 8) * (x / 8)) - start_tile > tile_count)? tile_count: ((y / 8) * (x / 8)) - start_tile;
    int tilesPerRow = (x / 8);
    // printf("%d tiles to write.\n", numTiles);
    if(n == 1) {
        for(int i = 0; i < numTiles; ++i) {
            CopyPNG2bppGrayTileToGB(&d[i * LEN_2BPP_TILE], &pix[((((start_tile+i)/tilesPerRow)*8)*x) + (((start_tile+i)%tilesPerRow)*8)], x);
        }
    }
    else {
        // Hack to make palette conversion work.
        const uint32_t* palette = (uint32_t*)&stbi_g_png_palette[0];
        // for(int i = 0; i < 4; ++i) {
        //     printf("Color %d: r=%d, g=%d, b=%d\n", i, palette[i] & 0xff, (palette[i] & 0xff00) >> 8, (palette[i] & 0xff0000) >> 16);
        // }
        for(int i = 0; i < numTiles; ++i) {
            CopyPNG2bppColorTileToGB(&d[i * LEN_2BPP_TILE], &pix[(((i/tilesPerRow)*8*n)*x) + ((i%tilesPerRow)*8*n)], x, n, palette);
        }
    }
    stbi_image_free(pix);
}
