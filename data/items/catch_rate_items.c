#include "../../constants.h"

// Pokémon traded from RBY do not have held items, so GSC usually interprets the
// catch rate as an item. However, if the catch rate appears in this table, the
// item associated with the table entry is used instead.

const item_t TimeCapsule_CatchRateItems[] = {
    ITEM_19,    LEFTOVERS,
    ITEM_2D,    BITTER_BERRY,
    ITEM_32,    GOLD_BERRY,
    ITEM_5A,    BERRY,
    ITEM_64,    BERRY,
    ITEM_78,    BERRY,
    ITEM_87,    BERRY,
    ITEM_BE,    BERRY,
    ITEM_C3,    BERRY,
    ITEM_DC,    BERRY,
    ITEM_FA,    BERRY,
    (item_t)-1, BERRY,
    0 // end
};
