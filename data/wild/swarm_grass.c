#include "../../constants.h"

// Pokémon swarms in grass

const struct WildGrassMons SwarmGrassWildMons[] = {
// Dunsparce swarm
    {MAP_ID(DARK_CAVE_VIOLET_ENTRANCE),
        .encounterRates={4 percent, 4 percent, 4 percent }, //  encounter rates: morn/day/nite
        .mons={
        [MORN_F] = {// morn
            {3, GEODUDE},
            {3, DUNSPARCE},
            {2, ZUBAT},
            {2, GEODUDE},
            {2, DUNSPARCE},
            {4, DUNSPARCE},
            {4, DUNSPARCE},
        },
        [DAY_F] = { // day
            {3, GEODUDE},
            {3, DUNSPARCE},
            {2, ZUBAT},
            {2, GEODUDE},
            {2, DUNSPARCE},
            {4, DUNSPARCE},
            {4, DUNSPARCE},
        },
        [NITE_F] = { // nite
            {3, GEODUDE},
            {3, DUNSPARCE},
            {2, ZUBAT},
            {2, GEODUDE},
            {2, DUNSPARCE},
            {4, DUNSPARCE},
            {4, DUNSPARCE},
        },
        }
    },
// Yanma swarm
    {MAP_ID(ROUTE_35),
        .encounterRates={10 percent, 10 percent, 10 percent}, // encounter rates: morn/day/nite
        .mons={
        [MORN_F] = {    // morn
            {12, NIDORAN_M},
            {12, NIDORAN_F},
            {12, YANMA},
            {14, YANMA},
            {14, PIDGEY},
            {10, DITTO},
            {10, DITTO},
        },
        [DAY_F] = {     // day
            {12, NIDORAN_M},
            {12, NIDORAN_F},
            {12, YANMA},
            {14, YANMA},
            {14, PIDGEY},
            {10, DITTO},
            {10, DITTO},
        },
        [NITE_F] = {    // nite
            {12, NIDORAN_M},
            {12, NIDORAN_F},
            {12, YANMA},
            {14, YANMA},
            {14, HOOTHOOT},
            {10, DITTO},
            {10, DITTO},
        },
        }
    },
    {.mapGroup = -1, .mapNumber = -1, .encounterRates = {}, .mons = {}},
};
