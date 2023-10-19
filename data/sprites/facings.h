#pragma once

struct Facing {
    const uint8_t count;
    const struct FacingData* const data;
};

struct FacingData {
    uint8_t y;
    uint8_t x;
    uint8_t attr;
    uint8_t tile_idx;
};

extern const struct Facing* Facings[];