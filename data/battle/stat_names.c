#include "../../constants.h"

const char* const StatNames[] = {
// entries correspond to stat ids
// list_start StatNames
    [ATTACK] = "ATTACK",
    [DEFENSE] = "DEFENSE",
    [SPEED] = "SPEED",
    [SP_ATTACK] = "SPCL.ATK",
    [SP_DEFENSE] = "SPCL.DEF",
    [ACCURACY] = "ACCURACY",
    [EVASION] = "EVASION",
    [ABILITY] = "ABILITY", // used for BattleCommand_Curse
};

static_assert(lengthof(StatNames) == NUM_LEVEL_STATS, "");
