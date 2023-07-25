#include <physfs.h>
#include <stdlib.h>
#include "../constants.h"
#include "assets.h"

// Loads asset file from archive to a heap-allocated buffer.
asset_s LoadAsset(const char* filename) {
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
    if(buf == NULL)
        return (asset_s){NULL, 0};
    PHYSFS_readBytes(file, buf, (size_t)size);
    PHYSFS_close(file);
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