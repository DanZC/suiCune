#ifndef NO_PHYSFS
#include <physfs.h>
#endif
#include <stdlib.h>
#include "../constants.h"
#include "assets.h"
#include "stb_image.h"
#include <assert.h>
#include <string.h>

int64_t fsize(FILE* file) {
    fseek(file, 0, SEEK_END);
    int64_t size = ftello(file);
    fseek(file, 0, SEEK_SET);
    return size;
}

// Loads asset file from archive to a heap-allocated buffer.
asset_s LoadAsset(const char* filename) {
    #if !defined(NO_PHYSFS)
    PHYSFS_File* file = PHYSFS_openRead(filename);
    if(!file) {
        fprintf(stderr, "%s Error: %s\nfilename=%s", __func__, PHYSFS_getErrorByCode(PHYSFS_getLastErrorCode()), filename);
        return (asset_s){NULL, 0};
    }
    int64_t size = PHYSFS_fileLength(file);
    if(size == -1) {
        fprintf(stderr, "%s Error: %s", __func__, PHYSFS_getErrorByCode(PHYSFS_getLastErrorCode()));
        PHYSFS_close(file);
        return (asset_s){NULL, 0};
    }
    uint8_t* buf = malloc((size_t)size);
    if(buf == NULL) {
        fprintf(stderr, "%s Error: Bad malloc.", __func__);
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
    int64_t size = fsize(file);
    if(size == -1) {
        fprintf(stderr, "%s Error", __func__);
        fclose(file);
        return (asset_s){NULL, 0};
    }
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
#if !defined(NO_PHYSFS)
    PHYSFS_File* file = PHYSFS_openRead(filename);
    if(!file) {
        fprintf(stderr, "%s Error: %s\nfilename=%s", __func__, PHYSFS_getErrorByCode(PHYSFS_getLastErrorCode()), filename);
        return (asset_s){NULL, 0};
    }
    int64_t size = PHYSFS_fileLength(file);
    if(size == -1) {
        fprintf(stderr, "%s Error: %s", __func__, PHYSFS_getErrorByCode(PHYSFS_getLastErrorCode()));
        PHYSFS_close(file);
        return (asset_s){NULL, 0};
    }
    size_t rsize = ((size_t)size > buf_size)? buf_size: (size_t)size;
    PHYSFS_readBytes(file, buffer, rsize);
    PHYSFS_close(file);
#else 
    FILE* file = fopen(filename, "rb");
    if(!file) {
        fprintf(stderr, "%s Error\nfilename=%s", __func__, filename);
        return (asset_s){NULL, 0};
    }
    int64_t size = fsize(file);
    if(size == -1) {
        fprintf(stderr, "%s Error. Bad size.\n", __func__);
        fclose(file);
        return (asset_s){NULL, 0};
    }
    // uint8_t* buf = malloc((size_t)size);
    // if(buf == NULL) {
    //     fprintf(stderr, "LoadAsset Error: Bad malloc.");
    //     return (asset_s){NULL, 0};
    // }
    size_t rsize = ((size_t)size > buf_size)? buf_size: (size_t)size;
    fread(buf, rsize, 1, file);
    fclose(file);
#endif
    return (asset_s){buffer, rsize};
}

// Loads text asset file from archive to a heap-allocated buffer.
asset_s LoadTextAsset(const char* filename) {
#if !defined(NO_PHYSFS)
    PHYSFS_File* file = PHYSFS_openRead(filename);
    if(!file) {
        fprintf(stderr, "%s Error: %s\nfilename=%s", __func__, PHYSFS_getErrorByCode(PHYSFS_getLastErrorCode()), filename);
        return (asset_s){NULL, 0};
    }
    int64_t size = PHYSFS_fileLength(file);
    if(size == -1) {
        fprintf(stderr, "%s Error: %s", __func__, PHYSFS_getErrorByCode(PHYSFS_getLastErrorCode()));
        PHYSFS_close(file);
        return (asset_s){NULL, 0};
    }
    uint8_t* buf = malloc((size_t)size + 1);
    if(buf == NULL) {
        fprintf(stderr, "%s Error: Bad malloc.", __func__);
        return (asset_s){NULL, 0};
    }
    PHYSFS_readBytes(file, buf, (size_t)size);
    PHYSFS_close(file);
    buf[size] = '\0';
#else 
    FILE* file = fopen(filename, "r");
    if(!file) {
        fprintf(stderr, "LoadAsset Error");
        return (asset_s){NULL, 0};
    }
    int64_t size = fsize(file);
    uint8_t* buf = malloc((size_t)size + 1);
    if(buf == NULL) {
        fprintf(stderr, "LoadAsset Error: Bad malloc.");
        return (asset_s){NULL, 0};
    }
    fread(buf, (size_t)size, 1, file);
    fclose(file);
    buf[size] = '\0';
#endif
    return (asset_s){buf, (size_t)size};
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
            if(pixel == pal[3]) {
                pixel = 0x3;
            } else if(pixel == pal[2]) {
                pixel = 0x2;
            } else if(pixel == pal[1]) {
                pixel = 0x1;
            } else if(pixel == pal[0]) {
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
    // printf("%d-channel %dx%d image\n", n, x, y);
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
    // printf("2bpp %d-channel %dx%d image (%s)\n", n, x, y, filename);
    FreeAsset(a);
    int numTiles = (y / 8) * (x / 8);
    int tilesPerRow = (x / 8);
    // printf("%d tiles to write.\n", numTiles);
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

// Loads a 2bpp PNG asset from an archive, converts it to GB pixel format,
// and writes the result to dest, assumedly a vram destination.
// Tiles are loaded by column instead of by row.
void LoadPNG2bppAssetToVRAMByColumn(void* dest, const char* filename) {
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
    // printf("2bpp %d-channel %dx%d image (%s)\n", n, x, y, filename);
    FreeAsset(a);
    int numTiles = (y / 8) * (x / 8);
    int tilesPerColumn = (y / 8);
    // printf("%d tiles to write.\n", numTiles);
    if(n == 1) {
        for(int i = 0; i < numTiles; ++i) {
            CopyPNG2bppGrayTileToGB(&d[i * LEN_2BPP_TILE], &pix[((i/tilesPerColumn)*8) + (((i%tilesPerColumn)*8)*x)], x);
        }
    }
    else {
        // Hack to make palette conversion work.
        const uint32_t* palette = (uint32_t*)&stbi_g_png_palette[0];
        // for(int i = 0; i < 4; ++i) {
        //     printf("Color %d: r=%d, g=%d, b=%d\n", i, palette[i] & 0xff, (palette[i] & 0xff00) >> 8, (palette[i] & 0xff0000) >> 16);
        // }
        for(int i = 0; i < numTiles; ++i) {
            CopyPNG2bppColorTileToGB(&d[i * LEN_2BPP_TILE], &pix[((((i/tilesPerColumn)*8)) + ((i%tilesPerColumn)*8)*x)*n], x, n, palette);
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
    // printf("1bpp %d-channel %dx%d image (%s)\n", n, x, y, filename);
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
    // printf("2bpp %d-channel %dx%d image (%s)\n", n, x, y, filename);
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
            CopyPNG2bppColorTileToGB(&d[i * LEN_2BPP_TILE], &pix[((((start_tile+i)/tilesPerRow)*8*n)*x) + (((start_tile+i)%tilesPerRow)*8*n)], x, n, palette);
        }
    }
    stbi_image_free(pix);
}

// static char pal_text_buffer[32];

static void ParsePalFromText(uint16_t* dest, size_t dest_size, const char* text, size_t start, size_t count) {
    const char* s = text;
    size_t written = 0;
    size_t passed = 0;
    int r, g, b;
    while(*s) {
        const char* s2 = s;
        while(*s2 && *s2 != '\n') s2++;
        // strncpy(pal_text_buffer, s, s2 - s);
        // pal_text_buffer[s2 - s] = '\0';
        // printf("%s\n", pal_text_buffer);
        while(s != s2) {
            if(memcmp(s, ";", 1) == 0) {
                goto nextline;
            }
            if(*s == ' ' || *s == '\t') { s++; continue; }
            if(memcmp(s, "RGB ", 4) == 0) {
                s += 4;
                sscanf_s(s, " ");
                sscanf_s(s, "%d, %d, %d", &r, &g, &b);
                // printf("%llu: %02d, %02d, %02d\n", written, r, g, b);
                if(passed++ < start)
                    goto nextline;
                *(dest++) = rgb(r, g, b);
                written++;
                if(written == dest_size || written == count)
                    return;
                goto nextline;
            }
            s++;
        }
    nextline:
        if(*s2) {
            s = ++s2;
        }
    }
}

void LoadPaletteAssetToBuffer(void* dest, size_t dest_size, const char* filename, size_t pal_count) {
    uint16_t* d = dest;
    asset_s a = LoadTextAsset(filename);

    if(!a.ptr)
        return;

    const char* text = a.ptr;

    ParsePalFromText(d, dest_size, text, 0, pal_count * NUM_PAL_COLORS);

    FreeAsset(a);
}

void LoadPaletteAssetColorsToBuffer(void* dest, size_t dest_size, const char* filename, size_t color_idx, size_t color_count) {
    uint16_t* d = dest;
    asset_s a = LoadTextAsset(filename);

    if(!a.ptr)
        return;

    const char* text = a.ptr;

    // printf("Loading %lld colors from palette file (%s)\n", color_count, filename);
    ParsePalFromText(d, dest_size, text, color_idx, color_count);

    FreeAsset(a);
}

// Loads a 2bpp PNG asset from an archive, extracts the color palette from it,
// and writes the result to dest.
void ExtractPaletteFromPNGAssetToBuffer(void* dest, const char* filename) {
    uint16_t* d = dest;
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
    // printf("Extracting colors from %d-channel %dx%d image (%s)\n", n, x, y, filename);
    FreeAsset(a);

    // Hack to make palette conversion work.
    const uint8_t* palette = (uint8_t*)&stbi_g_png_palette[0];
    // for(int i = 0; i < 4; ++i) {
    //     printf("Color %d: r=%d, g=%d, b=%d\n", i, palette[i] & 0xff, (palette[i] & 0xff00) >> 8, (palette[i] & 0xff0000) >> 16);
    // }
    for(int i = 0; i < n; ++i) {
        d[i] = rgb(palette[i*4 + 0] >> 3, palette[i*4 + 1] >> 3, palette[i*4 + 2] >> 3);
    }

    stbi_image_free(pix);
}

// Loads count segments from asset file from archive to a user-provided buffer of size buf_size,
// starting at segment start. If the buffer size is less than the size of the file being loaded, the 
// data loaded will be truncated to the buffer size, flooring to last segment size.
asset_s LoadAssetSegmentsToBuffer(void* buffer, size_t buf_size, const char* filename, size_t segment_size, size_t start, size_t count) {
    if(segment_size == 0) {
        fprintf(stderr, "%s Error: Segment size is 0.", __func__);
        return (asset_s){NULL, 0};
    }
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
    if(segment_size * start > (size_t)size) {
        return (asset_s){NULL, 0};
    }
    PHYSFS_seek(file, segment_size * start);
    size_t asize = (size_t)size - (segment_size * start);
    size_t scount = (count > asize / segment_size)? asize / segment_size: count;
    scount = (scount > buf_size / segment_size)? buf_size / segment_size: scount;
    if(scount != 0)
        PHYSFS_readBytes(file, buffer, segment_size * scount);
    PHYSFS_close(file);
#else
    FILE* file = fopen(filename, "rb");
    if(!file) {
        fprintf(stderr, "%s Error: %s", __func__, filename);
        return (asset_s){NULL, 0};
    }
    int64_t size = fsize(file);
    if(size == -1) {
        fprintf(stderr, "%s Error: %s", __func__, filename);
        fclose(file);
        return (asset_s){NULL, 0};
    }
    if(segment_size * start > (size_t)size) {
        return (asset_s){NULL, 0};
    }
    fseek(file, segment_size * start, SEEK_SET);
    size_t asize = (size_t)size - (segment_size * start);
    size_t scount = (count > asize / segment_size)? asize / segment_size: count;
    scount = (scount > buf_size / segment_size)? buf_size / segment_size: scount;
    if(scount != 0) {
        fread(buffer, segment_size * scount, 1, file);
    }
    fclose(file);
#endif
    return (asset_s){buffer, scount * segment_size};
}

void* Load2bppBinaryAssetToBuffer(void* buffer, size_t buf_size, const char* filename, size_t start, size_t count) {
    return LoadAssetSegmentsToBuffer(buffer, buf_size, filename, LEN_2BPP_TILE, start, count).ptr;
}
