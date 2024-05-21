#include "../../constants.h"

const uint8_t HappinessData_OlderHaircutBrother[][3] = {
    {30 percent,     2, HAPPINESS_OLDERCUT1}, // 30% chance
    {50 percent + 1, 3, HAPPINESS_OLDERCUT2}, // 50% chance
    {(uint8_t)-1,    4, HAPPINESS_OLDERCUT3}, // 20% chance
};

const uint8_t HappinessData_YoungerHaircutBrother[][3] = {
    {60 percent + 1, 2, HAPPINESS_YOUNGCUT1}, // 60% chance
    {30 percent,     3, HAPPINESS_YOUNGCUT2}, // 30% chance
    {(uint8_t)-1,    4, HAPPINESS_YOUNGCUT3}, // 10% chance
};

const uint8_t HappinessData_DaisysGrooming[][3] = {
    {(uint8_t)-1,    2, HAPPINESS_GROOMING},  // 99.6% chance
};
