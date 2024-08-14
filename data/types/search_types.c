#include "../../constants.h"

const uint8_t PokedexTypeSearchConversionTable[] = {
// entries correspond with PokedexTypeSearchStrings (see data/types/search_strings.asm)
    // table_width 1, PokedexTypeSearchConversionTable
    NORMAL,
    FIRE,
    WATER,
    GRASS,
    ELECTRIC,
    ICE,
    FIGHTING,
    POISON,
    GROUND,
    FLYING,
    PSYCHIC_TYPE,
    BUG,
    ROCK,
    GHOST,
    DRAGON,
    DARK,
    STEEL,
};

static_assert(lengthof(PokedexTypeSearchConversionTable) == NUM_TYPES, "");
