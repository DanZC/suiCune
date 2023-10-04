#include "../../constants.h"
#include "../../engine/overworld/events.h"

#define add_special(_n) [SP_##_n] = _n

void (*const SpecialsPointers[])(void) = {
    add_special(WarpToSpawnPoint),
};