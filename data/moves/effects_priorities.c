#include "../../constants.h"

const uint8_t MoveEffectPriorities[] = {
    EFFECT_PROTECT,      3,
    EFFECT_ENDURE,       3,
    EFFECT_PRIORITY_HIT, 2,
    EFFECT_FORCE_SWITCH, 0,
    EFFECT_COUNTER,      0,
    EFFECT_MIRROR_COAT,  0,
    0xff,
};
