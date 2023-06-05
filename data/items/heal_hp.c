#include "../../constants.h"

struct HealingHPEntry {
    uint8_t item;
    uint16_t amount;
};

const struct HealingHPEntry HealingHPAmounts[] = {
    {FRESH_WATER,   50},
    {SODA_POP,      60},
    {LEMONADE,      80},
    {HYPER_POTION, 200},
    {SUPER_POTION,  50},
    {POTION,        20},
    {MAX_POTION,   MAX_STAT_VALUE},
    {FULL_RESTORE, MAX_STAT_VALUE},
    {MOOMOO_MILK,  100},
    {BERRY,         10},
    {GOLD_BERRY,    30},
    {ENERGYPOWDER,  50},
    {ENERGY_ROOT,  200},
    {RAGECANDYBAR,  20},
    {BERRY_JUICE,   20},
    {-1, 0},
};