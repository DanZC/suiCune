#include "../../constants.h"

// Valid indices: $00 - $29 (see gfx/tilesets/bg_tiles.pal)
static const uint8_t OutdoorColors[] = {
    0x00, 0x01, 0x02, 0x28, 0x04, 0x05, 0x06, 0x07, // morn
    0x08, 0x09, 0x0a, 0x28, 0x0c, 0x0d, 0x0e, 0x0f, // day
    0x10, 0x11, 0x12, 0x29, 0x14, 0x15, 0x16, 0x17, // nite
    0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f, // dark
};

static const uint8_t IndoorColors[] = {
    0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x07, // morn
    0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x07, // day
    0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x07, // nite
    0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x07, // dark
};

static const uint8_t DungeonColors[] = {
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, // morn
    0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, // day
    0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, // nite
    0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f, // dark
};

static const uint8_t Env5Colors[] = {
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, // morn
    0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, // day
    0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, // nite
    0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f, // dark
};

const uint8_t* const EnvironmentColorsPointers[] = {
// entries correspond to environment constants (see constants/map_data_constants.asm)
// table_width 2, EnvironmentColorsPointers
    OutdoorColors, // unused
    OutdoorColors, // TOWN
    OutdoorColors, // ROUTE
    IndoorColors,  // INDOOR
    DungeonColors, // CAVE
    Env5Colors,    // ENVIRONMENT_5
    IndoorColors,  // GATE
    DungeonColors, // DUNGEON
};

static_assert(lengthof(EnvironmentColorsPointers) == NUM_ENVIRONMENTS + 1, "");