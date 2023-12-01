#include "../../constants.h"
#include "../../home/map_objects.h"
#include "../../engine/overworld/events.h"
#include "../../engine/rtc/timeset.h"
#include "../../engine/events/magikarp.h"

#define add_special(_n) [SP_##_n] = _n

void (*const SpecialsPointers[])(void) = {
    add_special(WarpToSpawnPoint),
    add_special(SetDayOfWeek),
    add_special(UpdateSprites),

    add_special(CheckMagikarpLength),
    add_special(MagikarpHouseSign),
};