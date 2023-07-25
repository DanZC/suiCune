#pragma once

// Data buffer for external assets.
typedef struct Asset {
    void *ptr;
    size_t size;
} asset_s;

asset_s LoadAsset(const char* filename);
asset_s LoadAssetToBuffer(void* buffer, size_t buf_size, const char* filename);
bool IsAssetValid(asset_s asset);
void FreeAsset(asset_s asset);
