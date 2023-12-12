#include "../../../constants.h"

// AI_BASIC discourages these effects if the player
// already has a status condition.
const uint8_t StatusOnlyEffects[] = {
    EFFECT_SLEEP,
    EFFECT_TOXIC,
    EFFECT_POISON,
    EFFECT_PARALYZE,
    (uint8_t)-1 // end
};
