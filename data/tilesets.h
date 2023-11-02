#pragma once

struct Tileset {
    const char* const gfxPath;
    const char* const metaPath;
    const uint8_t* const coll;
    const struct TilesetAnim* const anim;
    const uint16_t* const palMap;
};

extern const struct Tileset Tilesets[];