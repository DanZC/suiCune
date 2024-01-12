#include "../../constants.h"

// Multiplier ratios for all stats from modifier -6 to +6
// (except accuracy, see data/battle/accuracy_multipliers.asm).
//
// This table is identical to data/battle/stat_multipliers.asm.
// This one is used by ApplyStatLevelMultiplier.

const unsigned char StatLevelMultipliers_Applied[][2] = {
    {25, 100}, // -6 =  25%
    {28, 100}, // -5 =  28%
    {33, 100}, // -4 =  33%
    {40, 100}, // -3 =  40%
    {50, 100}, // -2 =  50%
    {66, 100}, // -1 =  66%
    { 1,   1}, //  0 = 100%
    {15,  10}, // +1 = 150%
    { 2,   1}, // +2 = 200%
    {25,  10}, // +3 = 250%
    { 3,   1}, // +4 = 300%
    {35,  10}, // +5 = 350%
    { 4,   1}, // +6 = 400%
};
