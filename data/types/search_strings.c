#include "../../constants.h"

const char * const PokedexTypeSearchStrings[] = {
// entries correspond with PokedexTypeSearchConversionTable (see data/types/search_types.asm)
    // table_width POKEDEX_TYPE_STRING_LENGTH, PokedexTypeSearchStrings
    "  ----  ",
    " NORMAL ",
    "  FIRE  ",
    " WATER  ",
    " GRASS  ",
    "ELECTRIC",
    "  ICE   ",
    "FIGHTING",
    " POISON ",
    " GROUND ",
    " FLYING ",
    "PSYCHIC ",
    "  BUG   ",
    "  ROCK  ",
    " GHOST  ",
    " DRAGON ",
    "  DARK  ",
    " STEEL  ",
};
static_assert(lengthof(PokedexTypeSearchStrings) == NUM_TYPES + 1, "");
