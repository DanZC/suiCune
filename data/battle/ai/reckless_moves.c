#include "../../../constants.h"

// AI_AGGRESSIVE does not discourage these moves
// even if a stronger one is available.
const uint8_t RecklessMoves[] = {
    EFFECT_SELFDESTRUCT,
    EFFECT_RAMPAGE,
    EFFECT_MULTI_HIT,
    EFFECT_DOUBLE_HIT,
    (uint8_t)-1, // end
};
