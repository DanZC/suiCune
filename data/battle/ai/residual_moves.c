#include "../../../constants.h"

// AI_CAUTIOUS discourages these moves after the first turn.

const move_t ResidualMoves[] = {
    MIST,
    LEECH_SEED,
    POISONPOWDER,
    STUN_SPORE,
    THUNDER_WAVE,
    FOCUS_ENERGY,
    BIDE,
    POISON_GAS,
    TRANSFORM,
    CONVERSION,
    SUBSTITUTE,
    SPIKES,
};
const size_t ResidualMoves_Size = lengthof(ResidualMoves);
