#pragma once

struct Tileset {
    const char* const gfxPath;
    const char* const metaPath;
    const uint8_t* const coll;
    const struct TileAnimFrame* const anim;
    const uint8_t* const palMap;
};

extern const struct Tileset Tilesets[];