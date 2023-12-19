#include "../../constants.h"

// Multiplier ratios for accuracy from modifier -6 to +6
// (for other stats, see data/battle/stat_multipliers.asm).

const uint8_t AccuracyLevelMultipliers[][2] = {
    [BASE_STAT_LEVEL-6-1] = { 33, 100}, // -6 =  33%
    [BASE_STAT_LEVEL-5-1] = { 36, 100}, // -5 =  36%
    [BASE_STAT_LEVEL-4-1] = { 43, 100}, // -4 =  43%
    [BASE_STAT_LEVEL-3-1] = { 50, 100}, // -3 =  50%
    [BASE_STAT_LEVEL-2-1] = { 60, 100}, // -2 =  60%
    [BASE_STAT_LEVEL-1-1] = { 75, 100}, // -1 =  75%
    [BASE_STAT_LEVEL+0-1] = {  1,   1}, //  0 = 100%
    [BASE_STAT_LEVEL+1-1] = {133, 100}, // +1 = 133%
    [BASE_STAT_LEVEL+2-1] = {166, 100}, // +2 = 166%
    [BASE_STAT_LEVEL+3-1] = {  2,   1}, // +3 = 200%
    [BASE_STAT_LEVEL+4-1] = {233, 100}, // +4 = 233%
    [BASE_STAT_LEVEL+5-1] = {133,  50}, // +5 = 266%
    [BASE_STAT_LEVEL+6-1] = {  3,   1}, // +6 = 300%
};
