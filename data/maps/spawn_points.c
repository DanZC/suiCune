#include "../../constants.h"
#include "spawn_points.h"

// entries correspond to SPAWN_* constants
const struct Spawn SpawnPoints[] = {
    //                     MAP                                   COORD
    [SPAWN_HOME]        = {MAP_ID(PLAYERS_HOUSE_2F),            .coord={ 3,  3}},
    [SPAWN_DEBUG]       = {MAP_ID(VIRIDIAN_POKECENTER_1F),      .coord={ 5,  3}},
    // kanto
    [SPAWN_PALLET]      = {MAP_ID(PALLET_TOWN),                 .coord={ 5,  6}},
    [SPAWN_VIRIDIAN]    = {MAP_ID(VIRIDIAN_CITY),               .coord={23, 26}},
    [SPAWN_PEWTER]      = {MAP_ID(PEWTER_CITY),                 .coord={13, 26}},
    [SPAWN_CERULEAN]    = {MAP_ID(CERULEAN_CITY),               .coord={19, 22}},
    [SPAWN_ROCK_TUNNEL] = {MAP_ID(ROUTE_10_NORTH),              .coord={11,  2}},
    [SPAWN_VERMILION]   = {MAP_ID(VERMILION_CITY),              .coord={ 9,  6}},
    [SPAWN_LAVENDER]    = {MAP_ID(LAVENDER_TOWN),               .coord={ 5,  6}},
    [SPAWN_SAFFRON]     = {MAP_ID(SAFFRON_CITY),                .coord={ 9, 30}},
    [SPAWN_CELADON]     = {MAP_ID(CELADON_CITY),                .coord={29, 10}},
    [SPAWN_FUCHSIA]     = {MAP_ID(FUCHSIA_CITY),                .coord={19, 28}},
    [SPAWN_CINNABAR]    = {MAP_ID(CINNABAR_ISLAND),             .coord={11, 12}},
    [SPAWN_INDIGO]      = {MAP_ID(ROUTE_23),                    .coord={ 9,  6}},
    // johto
    [SPAWN_NEW_BARK]    = {MAP_ID(NEW_BARK_TOWN),               .coord={13,  6}},
    [SPAWN_CHERRYGROVE] = {MAP_ID(CHERRYGROVE_CITY),            .coord={29,  4}},
    [SPAWN_VIOLET]      = {MAP_ID(VIOLET_CITY),                 .coord={31, 26}},
    [SPAWN_UNION_CAVE]  = {MAP_ID(ROUTE_32),                    .coord={11, 74}},
    [SPAWN_AZALEA]      = {MAP_ID(AZALEA_TOWN),                 .coord={15, 10}},
    [SPAWN_CIANWOOD]    = {MAP_ID(CIANWOOD_CITY),               .coord={23, 44}},
    [SPAWN_GOLDENROD]   = {MAP_ID(GOLDENROD_CITY),              .coord={14, 28}},
    [SPAWN_OLIVINE]     = {MAP_ID(OLIVINE_CITY),                .coord={13, 22}},
    [SPAWN_ECRUTEAK]    = {MAP_ID(ECRUTEAK_CITY),               .coord={23, 28}},
    [SPAWN_MAHOGANY]    = {MAP_ID(MAHOGANY_TOWN),               .coord={15, 14}},
    [SPAWN_LAKE_OF_RAGE]= {MAP_ID(LAKE_OF_RAGE),                .coord={21, 29}},
    [SPAWN_BLACKTHORN]  = {MAP_ID(BLACKTHORN_CITY),             .coord={21, 30}},
    [SPAWN_MT_SILVER]   = {MAP_ID(SILVER_CAVE_OUTSIDE),         .coord={23, 20}},
    [SPAWN_FAST_SHIP]   = {MAP_ID(FAST_SHIP_CABINS_SW_SSW_NW),  .coord={ 6,  2}},
    // N_A
                          {MAP_ID(N_A),                         .coord={-1, -1}},
};

#if defined(__cplusplus) || defined(_MSC_VER)
static_assert(lengthof(SpawnPoints) == NUM_SPAWNS + 1, "");
#else
_Static_assert(lengthof(SpawnPoints) == NUM_SPAWNS + 1, "");
#endif