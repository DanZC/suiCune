#include "../../constants.h"

const uint8_t PresentPower[] = {
    // chance, power
    40 percent,     40, // 40% chance
    70 percent + 1, 80, // 30% chance
    80 percent,    120, // 10% chance
    -1,                 // 20% chance to heal instead
};
