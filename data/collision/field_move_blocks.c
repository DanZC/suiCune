#include "../../constants.h"

static const uint8_t CutTreeBlockPointers_johto[] = {
// facing block, replacement block, animation
	0x03,        0x02,              1, // grass
	0x5b,        0x3c,              0, // tree
	0x5f,        0x3d,              0, // tree
	0x63,        0x3f,              0, // tree
	0x67,        0x3e,              0, // tree
	0xff // end
};

static const uint8_t CutTreeBlockPointers_johto_modern[] = {
// facing block, replacement block, animation
    0x03, 0x02, 0x01, // grass
    0xff // end
};

static const uint8_t CutTreeBlockPointers_kanto[] = {
// facing block, replacement block, animation
    0x0b, 0x0a, 1, // grass
    0x32, 0x6d, 0, // tree
    0x33, 0x6c, 0, // tree
    0x34, 0x6f, 0, // tree
    0x35, 0x4c, 0, // tree
    0x60, 0x6e, 0, // tree
    0xff // end
};

static const uint8_t CutTreeBlockPointers_park[] = {
//  facing block, replacement block, animation
    0x13,         0x03,              1, // grass
    0x03,         0x04,              1, // grass
    -1 // end
};

static const uint8_t CutTreeBlockPointers_forest[] = {
// facing block, replacement block, animation
    0x0f, 0x17, 0,
    0xff // end
};

// these blocks all use COLL_CUT_TREE in one quadrant
const struct BlockPointer CutTreeBlockPointers[] = {
// tileset, block list pointer
    {TILESET_JOHTO,        CutTreeBlockPointers_johto},
    {TILESET_JOHTO_MODERN, CutTreeBlockPointers_johto_modern},
    {TILESET_KANTO,        CutTreeBlockPointers_kanto},
    {TILESET_PARK,         CutTreeBlockPointers_park},
    {TILESET_FOREST,       CutTreeBlockPointers_forest},
    {0xff,                 NULL}, // end
};

static const uint8_t WhirlpoolBlockPointers_johto[] = {
//  facing block, replacement block, animation
    0x07,         0x36,              0,
    0xff // end
};

// these blocks all use COLL_WHIRLPOOL in one quadrant
const struct BlockPointer WhirlpoolBlockPointers[] = {
    {TILESET_JOHTO, WhirlpoolBlockPointers_johto},
    {0xff,          NULL}, // end
};
