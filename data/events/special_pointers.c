#include "../../constants.h"
#include "../../engine/overworld/events.h"
#include "../../engine/rtc/timeset.h"

#define add_special(_n) [SP_##_n] = _n

void (*const SpecialsPointers[])(void) = {
    add_special(WarpToSpawnPoint),
    add_special(SetDayOfWeek)
};