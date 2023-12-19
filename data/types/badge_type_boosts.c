#include "../../constants.h"

#define K(_x) (NUM_JOHTO_BADGES + _x)

const uint8_t BadgeTypeBoosts[] = {
// entries correspond to wJohtoBadges constants
    [ZEPHYRBADGE]   = FLYING,       // ZEPHYRBADGE
    [HIVEBADGE]     = BUG,          // HIVEBADGE
    [PLAINBADGE]    = NORMAL,       // PLAINBADGE
    [FOGBADGE]      = GHOST,        // FOGBADGE
    [MINERALBADGE]  = STEEL,        // MINERALBADGE
    [STORMBADGE]    = FIGHTING,     // STORMBADGE
    [GLACIERBADGE]  = ICE,          // GLACIERBADGE
    [RISINGBADGE]   = DRAGON,       // RISINGBADGE
    // fallthrough
// entries correspond to wKantoBadges constants
    [K(BOULDERBADGE)]   = ROCK,         // BOULDERBADGE
    [K(CASCADEBADGE)]   = WATER,        // CASCADEBADGE
    [K(THUNDERBADGE)]   = ELECTRIC,     // THUNDERBADGE
    [K(RAINBOWBADGE)]   = GRASS,        // RAINBOWBADGE
    [K(SOULBADGE)]      = POISON,       // SOULBADGE
    [K(MARSHBADGE)]     = PSYCHIC_TYPE, // MARSHBADGE
    [K(VOLCANOBADGE)]   = FIRE,         // VOLCANOBADGE
    [K(EARTHBADGE)]     = GROUND,       // EARTHBADGE
    0xff // end
};
