#include "../../constants.h"
// mon_prob: MACRO
// ; percent, index
// 	db \1, \2 * 2
// ENDM

const uint8_t GrassMonProbTable[] = {
    // table_width 2, GrassMonProbTable
    [0] = 30,  // 30% chance
    [1] = 60,  // 30% chance
    [2] = 80,  // 20% chance
    [3] = 90,  // 10% chance
    [4] = 95,  //  5% chance
    [5] = 99,  //  4% chance
    [6] = 100, //  1% chance
};
static_assert(lengthof(GrassMonProbTable) == NUM_GRASSMON);

const uint8_t WaterMonProbTable[] = {
    // table_width 2, WaterMonProbTable
    [0] = 60,   // 60% chance
    [1] = 90,   // 30% chance
    [2] = 100,  // 10% chance
};
static_assert(lengthof(WaterMonProbTable) == NUM_WATERMON);
