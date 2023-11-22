#include "../../constants.h"
#include "happiness_changes.h"

const int8_t HappinessChanges[][3] = {
// entries correspond to HAPPINESS_* constants
    // table_width 3, HappinessChanges
    // change if happiness < 100, change if happiness < 200, change otherwise
    [HAPPINESS_GAINLEVEL-1]         = { +5,  +3,  +2}, // Gained a level
    [HAPPINESS_USEDITEM-1]          = { +5,  +3,  +2}, // Vitamin
    [HAPPINESS_USEDXITEM-1]         = { +1,  +1,  +0}, // X Item
    [HAPPINESS_GYMBATTLE-1]         = { +3,  +2,  +1}, // Battled a Gym Leader
    [HAPPINESS_LEARNMOVE-1]         = { +1,  +1,  +0}, // Learned a move
    [HAPPINESS_FAINTED-1]           = { -1,  -1,  -1}, // Lost to an enemy
    [HAPPINESS_POISONFAINT-1]       = { -5,  -5, -10}, // Fainted due to poison
    [HAPPINESS_BEATENBYSTRONGFOE-1] = { -5,  -5, -10}, // Lost to a much stronger enemy
    [HAPPINESS_OLDERCUT1-1]         = { +1,  +1,  +1}, // Haircut (older brother) 1
    [HAPPINESS_OLDERCUT2-1]         = { +3,  +3,  +1}, // Haircut (older brother) 2
    [HAPPINESS_OLDERCUT3-1]         = { +5,  +5,  +2}, // Haircut (older brother) 3
    [HAPPINESS_YOUNGCUT1-1]         = { +1,  +1,  +1}, // Haircut (younger brother) 1
    [HAPPINESS_YOUNGCUT2-1]         = { +3,  +3,  +1}, // Haircut (younger brother) 2
    [HAPPINESS_YOUNGCUT3-1]         = {+10, +10,  +4}, // Haircut (younger brother) 3
    [HAPPINESS_BITTERPOWDER-1]      = { -5,  -5, -10}, // Used Heal Powder or Energypowder (bitter)
    [HAPPINESS_ENERGYROOT-1]        = {-10, -10, -15}, // Used Energy Root (bitter)
    [HAPPINESS_REVIVALHERB-1]       = {-15, -15, -20}, // Used Revival Herb (bitter)
    [HAPPINESS_GROOMING-1]          = { +3,  +3,  +1}, // Grooming
    [HAPPINESS_GAINLEVELATHOME-1]   = {+10,  +6,  +4}, // Gained a level in the place where it was caught
};
static_assert(lengthof(HappinessChanges) == NUM_HAPPINESS_CHANGES);
