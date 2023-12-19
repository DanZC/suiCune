#include "../../constants.h"
// See also data/items/heal_status.asm

const uint8_t HeldStatusHealingEffects[] = {
    HELD_HEAL_POISON,   1 << PSN,
    HELD_HEAL_FREEZE,   1 << FRZ,
    HELD_HEAL_BURN,     1 << BRN,
    HELD_HEAL_SLEEP,    SLP,
    HELD_HEAL_PARALYZE, 1 << PAR,
    HELD_HEAL_STATUS,   ALL_STATUS,
    -1 // end
};
