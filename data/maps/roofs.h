#pragma once

// MapGroupRoofs values; Roofs indexes
enum {
    ROOF_NEW_BARK,  // 0
    ROOF_VIOLET,    // 1
    ROOF_AZALEA,    // 2
    ROOF_OLIVINE,   // 3
    ROOF_GOLDENROD, // 4
    NUM_ROOFS
};
#define ROOF_NONE -1

extern const uint8_t MapGroupRoofs[];
extern const char *Roofs[];
