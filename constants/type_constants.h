// TypeNames indexes (see data/types/names.asm)
// also used in:
// - PokedexTypeSearchConversionTable (see data/types/search_types.asm)
// - PokedexTypeSearchStrings (see data/types/search_strings.asm)
// - TypeMatchups (see data/types/type_matchups.asm)
// - TypeBoostItems (see data/types/type_boost_items.asm)
enum {
    NORMAL,
    FIGHTING,
    FLYING,
    POISON,
    GROUND,
    ROCK,
    BIRD,
    BUG,
    GHOST,
    STEEL,
    CURSE_TYPE = 19,
    FIRE,
    WATER,
    GRASS,
    ELECTRIC,
    PSYCHIC_TYPE,
    ICE,
    DRAGON,
    DARK,
};

#define PHYSICAL NORMAL
#define SPECIAL FIRE
#define UNUSED_TYPES STEEL + 1
#define UNUSED_TYPES_END CURSE_TYPE + 1
#define TYPES_END DARK + 1

#define NUM_TYPES TYPES_END + UNUSED_TYPES - UNUSED_TYPES_END - 1 // discount BIRD

#define POKEDEX_TYPE_STRING_LENGTH 9
