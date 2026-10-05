#include "../../../constants.h"

// AI_SMART knows these moves are usable all-around.
const move_t UsefulMoves[] = {
    DOUBLE_EDGE,
    SING,
    FLAMETHROWER,
    HYDRO_PUMP,
    SURF,
    ICE_BEAM,
    BLIZZARD,
    HYPER_BEAM,
    SLEEP_POWDER,
    THUNDERBOLT,
    THUNDER,
    EARTHQUAKE,
    TOXIC,
    PSYCHIC_M,
    HYPNOSIS,
    RECOVER,
    FIRE_BLAST,
    SOFTBOILED,
    SUPER_FANG,
};
const size_t UsefulMoves_Size = lengthof(UsefulMoves);
