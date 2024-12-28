#pragma once

// Data buffer for external assets.
typedef struct Asset {
    void *ptr;
    size_t size;
} asset_s;

asset_s LoadAsset(const char* filename);
asset_s LoadAssetToBuffer(void* buffer, size_t buf_size, const char* filename);
asset_s LoadAssetSegmentsToBuffer(void* buffer, size_t buf_size, const char* filename, size_t segment_size, size_t start, size_t count);
asset_s LoadTextAsset(const char* filename);
bool IsAssetValid(asset_s asset);
void FreeAsset(asset_s asset);

void LoadPNG1bppAssetToVRAM(void* dest, const char* filename);
void LoadPNG1bppAssetSectionToVRAM(void* dest, const char* filename, int start_tile, int tile_count);
void LoadPNG1bppAssetSectionToVRAM_SkipEmptyTiles(void* dest, const char* filename, int start_tile, int tile_count);
void LoadPNG2bppAssetToVRAM(void* dest, const char* filename);
void LoadPNG2bppAssetToVRAMByColumn(void* dest, const char* filename);
void LoadPNG2bppAssetSectionToVRAM(void* dest, const char* filename, int start_tile, int tile_count);
void LoadPNG2bppAssetSectionToVRAM_SkipEmptyTiles(void* dest, const char* filename, int start_tile, int tile_count);

void LoadDimensionsFromPNG(const char* filename, int* w, int* h);

void LoadPaletteAssetToBuffer(void* dest, size_t dest_size, const char* filename, size_t count);
#define LoadPaletteAssetToArray(_arr, _filename, _count) LoadPaletteAssetToBuffer(_arr, sizeof(_arr), _filename, _count)
void LoadPaletteAssetColorsToBuffer(void* dest, size_t dest_size, const char* filename, size_t color_idx, size_t color_count);
#define LoadPaletteAssetColorsToArray(_arr, _filename, _start, _count) LoadPaletteAssetColorsToBuffer(_arr, sizeof(_arr), _filename, _start, _count)

void ExtractPaletteFromPNGAssetToBuffer(void* dest, const char* filename);

void* Load2bppBinaryAssetToBuffer(void* buffer, size_t buf_size, const char* filename, size_t start, size_t count);

void* LoadPixelsFromPNG(const char* filename, int* w, int* h);
