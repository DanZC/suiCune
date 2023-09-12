#include "../../constants.h"

#define sprite_mon(_mon) [SPRITE_##_mon - SPRITE_POKEMON] = _mon

const uint8_t SpriteMons[] = {
// entries correspond to SPRITE_* constants past SPRITE_POKEMON
// table_width 1, SpriteMons
    sprite_mon(UNOWN),
    sprite_mon(GEODUDE),
    sprite_mon(GROWLITHE),
    sprite_mon(WEEDLE),
    sprite_mon(SHELLDER),
    sprite_mon(ODDISH),
    sprite_mon(GENGAR),
    sprite_mon(ZUBAT),
    sprite_mon(MAGIKARP),
    sprite_mon(SQUIRTLE),
    sprite_mon(TOGEPI),
    sprite_mon(BUTTERFREE),
    sprite_mon(DIGLETT),
    sprite_mon(POLIWAG),
    sprite_mon(PIKACHU),
    sprite_mon(CLEFAIRY),
    sprite_mon(CHARMANDER),
    sprite_mon(JYNX),
    sprite_mon(STARMIE),
    sprite_mon(BULBASAUR),
    sprite_mon(JIGGLYPUFF),
    sprite_mon(GRIMER),
    sprite_mon(EKANS),
    sprite_mon(PARAS),
    sprite_mon(TENTACOOL),
    sprite_mon(TAUROS),
    sprite_mon(MACHOP),
    sprite_mon(VOLTORB),
    sprite_mon(LAPRAS),
    sprite_mon(RHYDON),
    sprite_mon(MOLTRES),
    sprite_mon(SNORLAX),
    sprite_mon(GYARADOS),
    sprite_mon(LUGIA),
    sprite_mon(HO_OH),
};

static_assert(lengthof(SpriteMons) == NUM_POKEMON_SPRITES, "");
