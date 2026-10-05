#include "../../constants.h"
// Metronome cannot turn into these moves.

const move_t MetronomeExcepts[] = {
    NO_MOVE,
    METRONOME,
    STRUGGLE,
    SKETCH,
    MIMIC,
    COUNTER,
    MIRROR_COAT,
    PROTECT,
    DETECT,
    ENDURE,
    DESTINY_BOND,
    SLEEP_TALK,
    THIEF,
};
const size_t MetronomeExcepts_Size = lengthof(MetronomeExcepts);
