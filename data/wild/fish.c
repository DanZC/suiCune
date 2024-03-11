#include "../../constants.h"

#define time_group (species_t)0, // use the nth TimeFishGroups entry

static const struct FishEncounter Shore_Old[] = {
    { 70 percent + 1, MAGIKARP,   10},
    { 85 percent + 1, MAGIKARP,   10},
    {100 percent,     KRABBY,     10},
};
static const struct FishEncounter Shore_Good[] = {
    { 35 percent,     MAGIKARP,   20},
    { 70 percent,     KRABBY,     20},
    { 90 percent + 1, KRABBY,     20},
    {100 percent,     time_group 0},
};
static const struct FishEncounter Shore_Super[] = {
    { 40 percent,     KRABBY,     40},
    { 70 percent,     time_group 1},
    { 90 percent + 1, KRABBY,     40},
    {100 percent,     KINGLER,    40},
};

static const struct FishEncounter Ocean_Old[] = {
    { 70 percent + 1, MAGIKARP,   10},
    { 85 percent + 1, MAGIKARP,   10},
    {100 percent,     TENTACOOL,  10},
};
static const struct FishEncounter Ocean_Good[] = {
    { 35 percent,     MAGIKARP,   20},
    { 70 percent,     TENTACOOL,  20},
    { 90 percent + 1, CHINCHOU,   20},
    {100 percent,     time_group 2},
};
static const struct FishEncounter Ocean_Super[] = {
    { 40 percent,     CHINCHOU,   40},
    { 70 percent,     time_group 3},
    { 90 percent + 1, TENTACRUEL, 40},
    {100 percent,     LANTURN,    40},
};

static const struct FishEncounter Lake_Old[] = {
    { 70 percent + 1, MAGIKARP,   10},
    { 85 percent + 1, MAGIKARP,   10},
    {100 percent,     GOLDEEN,    10},
};
static const struct FishEncounter Lake_Good[] = {
    { 35 percent,     MAGIKARP,   20},
    { 70 percent,     GOLDEEN,    20},
    { 90 percent + 1, GOLDEEN,    20},
    {100 percent,     time_group 4},
};
static const struct FishEncounter Lake_Super[] = {
    { 40 percent,     GOLDEEN,    40},
    { 70 percent,     time_group 5},
    { 90 percent + 1, MAGIKARP,   40},
    {100 percent,     SEAKING,    40},
};

static const struct FishEncounter Pond_Old[] = {
    { 70 percent + 1, MAGIKARP,   10},
    { 85 percent + 1, MAGIKARP,   10},
    {100 percent,     POLIWAG,    10},
};
static const struct FishEncounter Pond_Good[] = {
    { 35 percent,     MAGIKARP,   20},
    { 70 percent,     POLIWAG,    20},
    { 90 percent + 1, POLIWAG,    20},
    {100 percent,     time_group 6},
};
static const struct FishEncounter Pond_Super[] = {
    { 40 percent,     POLIWAG,    40},
    { 70 percent,     time_group 7},
    { 90 percent + 1, MAGIKARP,   40},
    {100 percent,     POLIWAG,    40},
};

static const struct FishEncounter Dratini_Old[] = {
    { 70 percent + 1, MAGIKARP,   10},
    { 85 percent + 1, MAGIKARP,   10},
    {100 percent,     MAGIKARP,   10},
};
static const struct FishEncounter Dratini_Good[] = {
    { 35 percent,     MAGIKARP,   20},
    { 70 percent,     MAGIKARP,   20},
    { 90 percent + 1, MAGIKARP,   20},
    {100 percent,     time_group 8},
};
static const struct FishEncounter Dratini_Super[] = {
    { 40 percent,     MAGIKARP,   40},
    { 70 percent,     time_group 9},
    { 90 percent + 1, MAGIKARP,   40},
    {100 percent,     DRAGONAIR,  40},
};

static const struct FishEncounter Qwilfish_Swarm_Old[] = {
    { 70 percent + 1, MAGIKARP,   5},
    { 85 percent + 1, MAGIKARP,   5},
    {100 percent,     QWILFISH,   5},
};
static const struct FishEncounter Qwilfish_Swarm_Good[] = {
    { 35 percent,     MAGIKARP,   20},
    { 70 percent,     QWILFISH,   20},
    { 90 percent + 1, QWILFISH,   20},
    {100 percent,     time_group 10},
};
static const struct FishEncounter Qwilfish_Swarm_Super[] = {
    { 40 percent,     QWILFISH,   40},
    { 70 percent,     time_group 11},
    { 90 percent + 1, QWILFISH,   40},
    {100 percent,     QWILFISH,   40},
};

static const struct FishEncounter Remoraid_Swarm_Old[] = {
    { 70 percent + 1, MAGIKARP,   10},
    { 85 percent + 1, MAGIKARP,   10},
    {100 percent,     REMORAID,   10},
};
static const struct FishEncounter Remoraid_Swarm_Good[] = {
    { 35 percent,     MAGIKARP,   20},
    { 70 percent,     REMORAID,   20},
    { 90 percent + 1, REMORAID,   20},
    {100 percent,     time_group 12},
};
static const struct FishEncounter Remoraid_Swarm_Super[] = {
    { 40 percent,     REMORAID,   40},
    { 70 percent,     time_group 13},
    { 90 percent + 1, REMORAID,   40},
    {100 percent,     REMORAID,   40},
};

static const struct FishEncounter Gyarados_Old[] = {
    { 70 percent + 1, MAGIKARP,   10},
    { 85 percent + 1, MAGIKARP,   10},
    {100 percent,     MAGIKARP,   10},
};
static const struct FishEncounter Gyarados_Good[] = {
    { 35 percent,     MAGIKARP,   20},
    { 70 percent,     MAGIKARP,   20},
    { 90 percent + 1, MAGIKARP,   20},
    {100 percent,     time_group 14},
};
static const struct FishEncounter Gyarados_Super[] = {
    { 40 percent,     MAGIKARP,   40},
    { 70 percent,     time_group 15},
    { 90 percent + 1, MAGIKARP,   40},
    {100 percent,     MAGIKARP,   40},
};

static const struct FishEncounter Dratini_2_Old[] = {
    { 70 percent + 1, MAGIKARP,   10},
    { 85 percent + 1, MAGIKARP,   10},
    {100 percent,     MAGIKARP,   10},
};
static const struct FishEncounter Dratini_2_Good[] = {
    { 35 percent,     MAGIKARP,   10},
    { 70 percent,     MAGIKARP,   10},
    { 90 percent + 1, MAGIKARP,   10},
    {100 percent,     time_group 16},
};
static const struct FishEncounter Dratini_2_Super[] = {
    { 40 percent,     MAGIKARP,   10},
    { 70 percent,     time_group 17},
    { 90 percent + 1, MAGIKARP,   10},
    {100 percent,     DRAGONAIR,  10},
};

static const struct FishEncounter WhirlIslands_Old[] = {
    { 70 percent + 1, MAGIKARP,   10},
    { 85 percent + 1, MAGIKARP,   10},
    {100 percent,     KRABBY,     10},
};
static const struct FishEncounter WhirlIslands_Good[] = {
    { 35 percent,     MAGIKARP,   20},
    { 70 percent,     KRABBY,     20},
    { 90 percent + 1, KRABBY,     20},
    {100 percent,     time_group 18},
};
static const struct FishEncounter WhirlIslands_Super[] = {
    { 40 percent,     KRABBY,     40},
    { 70 percent,     time_group 19},
    { 90 percent + 1, KINGLER,    40},
    {100 percent,     SEADRA,     40},
};

#define Qwilfish_NoSwarm_Old Qwilfish_Old
static const struct FishEncounter Qwilfish_Old[] = {
    { 70 percent + 1, MAGIKARP,   10},
    { 85 percent + 1, MAGIKARP,   10},
    {100 percent,     TENTACOOL,  10},
};
#define Qwilfish_NoSwarm_Good Qwilfish_Good
static const struct FishEncounter Qwilfish_Good[] = {
    { 35 percent,     MAGIKARP,   20},
    { 70 percent,     TENTACOOL,  20},
    { 90 percent + 1, TENTACOOL,  20},
    {100 percent,     time_group 20},
};
#define Qwilfish_NoSwarm_Super Qwilfish_Super
static const struct FishEncounter Qwilfish_Super[] = {
    { 40 percent,     TENTACOOL,  40},
    { 70 percent,     time_group 21},
    { 90 percent + 1, MAGIKARP,   40},
    {100 percent,     QWILFISH,   40},
};

static const struct FishEncounter Remoraid_Old[] = {
    { 70 percent + 1, MAGIKARP,   10},
    { 85 percent + 1, MAGIKARP,   10},
    {100 percent,     POLIWAG,    10},
};
static const struct FishEncounter Remoraid_Good[] = {
    { 35 percent,     MAGIKARP,   20},
    { 70 percent,     POLIWAG,    20},
    { 90 percent + 1, POLIWAG,    20},
    {100 percent,     time_group 6},
};
static const struct FishEncounter Remoraid_Super[] = {
    { 40 percent,     POLIWAG,    40},
    { 70 percent,     time_group 7},
    { 90 percent + 1, MAGIKARP,   40},
    {100 percent,     REMORAID,   40},
};

const struct TimeFishGroup TimeFishGroups[] = {
 //  day              nite
    {CORSOLA,    20,  STARYU,     20}, // 0
    {CORSOLA,    40,  STARYU,     40}, // 1
    {SHELLDER,   20,  SHELLDER,   20}, // 2
    {SHELLDER,   40,  SHELLDER,   40}, // 3
    {GOLDEEN,    20,  GOLDEEN,    20}, // 4
    {GOLDEEN,    40,  GOLDEEN,    40}, // 5
    {POLIWAG,    20,  POLIWAG,    20}, // 6
    {POLIWAG,    40,  POLIWAG,    40}, // 7
    {DRATINI,    20,  DRATINI,    20}, // 8
    {DRATINI,    40,  DRATINI,    40}, // 9
    {QWILFISH,   20,  QWILFISH,   20}, // 10
    {QWILFISH,   40,  QWILFISH,   40}, // 11
    {REMORAID,   20,  REMORAID,   20}, // 12
    {REMORAID,   40,  REMORAID,   40}, // 13
    {GYARADOS,   20,  GYARADOS,   20}, // 14
    {GYARADOS,   40,  GYARADOS,   40}, // 15
    {DRATINI,    10,  DRATINI,    10}, // 16
    {DRATINI,    10,  DRATINI,    10}, // 17
    {HORSEA,     20,  HORSEA,     20}, // 18
    {HORSEA,     40,  HORSEA,     40}, // 19
    {TENTACOOL,  20,  TENTACOOL,  20}, // 20
    {TENTACOOL,  40,  TENTACOOL,  40}, // 21
};

// fishgroup: MACRO
// ; chance, old rod, good rod, super rod
// 	db \1
// 	dw \2, \3, \4
// ENDM
#define fishgroup(_c, _o, _g, _s) {.chance=_c, .old_rod=_o, .good_rod=_g, .super_rod=_s}

const struct FishGroup FishGroups[] = {
// entries correspond to FISHGROUP_* constants
    // table_width FISHGROUP_DATA_LENGTH, FishGroups
    [FISHGROUP_SHORE-1]             = fishgroup(50 percent + 1, Shore_Old,            Shore_Good,            Shore_Super),
    [FISHGROUP_OCEAN-1]             = fishgroup(50 percent + 1, Ocean_Old,            Ocean_Good,            Ocean_Super),
    [FISHGROUP_LAKE-1]              = fishgroup(50 percent + 1, Lake_Old,             Lake_Good,             Lake_Super),
    [FISHGROUP_POND-1]              = fishgroup(50 percent + 1, Pond_Old,             Pond_Good,             Pond_Super),
    [FISHGROUP_DRATINI-1]           = fishgroup(50 percent + 1, Dratini_Old,          Dratini_Good,          Dratini_Super),
    [FISHGROUP_QWILFISH_SWARM-1]    = fishgroup(50 percent + 1, Qwilfish_Swarm_Old,   Qwilfish_Swarm_Good,   Qwilfish_Swarm_Super),
    [FISHGROUP_REMORAID_SWARM-1]    = fishgroup(50 percent + 1, Remoraid_Swarm_Old,   Remoraid_Swarm_Good,   Remoraid_Swarm_Super),
    [FISHGROUP_GYARADOS-1]          = fishgroup(50 percent + 1, Gyarados_Old,         Gyarados_Good,         Gyarados_Super),
    [FISHGROUP_DRATINI_2-1]         = fishgroup(50 percent + 1, Dratini_2_Old,        Dratini_2_Good,        Dratini_2_Super),
    [FISHGROUP_WHIRL_ISLANDS-1]     = fishgroup(50 percent + 1, WhirlIslands_Old,     WhirlIslands_Good,     WhirlIslands_Super),
    [FISHGROUP_QWILFISH-1]          = fishgroup(50 percent + 1, Qwilfish_Old,         Qwilfish_Good,         Qwilfish_Super),
    [FISHGROUP_REMORAID-1]          = fishgroup(50 percent + 1, Remoraid_Old,         Remoraid_Good,         Remoraid_Super),
    [FISHGROUP_QWILFISH_NO_SWARM-1] = fishgroup(50 percent + 1, Qwilfish_NoSwarm_Old, Qwilfish_NoSwarm_Good, Qwilfish_NoSwarm_Super),
};
static_assert(lengthof(FishGroups) == NUM_FISHGROUPS, "");
