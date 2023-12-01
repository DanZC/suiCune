#include "../../constants.h"

// [wMagikarpLength] = z * 100 + (bc - x) / y
// First argument is the bc threshold as well as x.
// Second argument is y.
// In reality, due to the bug at .BCLessThanDE,
// the threshold is determined by only register b.
const struct WordByte MagikarpLengths[] = {
    {  110,   1}, // not used unless the bug is fixed
    {  310,   2},
    {  710,   4},
    { 2710,  20},
    { 7710,  50},
    {17710, 100},
    {32710, 150},
    {47710, 150},
    {57710, 100},
    {62710,  50},
    {64710,  20},
    {65210,   5},
    {65410,   2},
    {65510,   1}, // not used
};
