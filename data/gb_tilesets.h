#pragma once

struct GBTileset {
    uint32_t gfx_ptr;
    uint32_t meta_ptr;
    uint32_t coll_ptr;
    uint32_t anim_ptr;
    uint32_t pal_ptr;
};

extern const struct GBTileset GBTilesets[];
