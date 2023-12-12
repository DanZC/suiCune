#include "../../../constants.h"

// AI_RISKY will not use these effects at max HP
// even if they would KO the player.

const uint8_t RiskyEffects[] = {
    EFFECT_SELFDESTRUCT,
    EFFECT_OHKO,
    (uint8_t)-1, // end
};
