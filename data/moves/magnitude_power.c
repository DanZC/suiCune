#include "../../constants.h"
#include "magnitude_power.h"

const uint8_t MagnitudePower[][3] = {
    // chance, power, magnitude #
    {  5 percent + 1,  10,  4}, // 5%
    { 15 percent,      30,  5}, // 10%
    { 35 percent,      50,  6}, // 20%
    { 65 percent + 1,  70,  7}, // 30%
    { 85 percent + 1,  90,  8}, // 20%
    { 95 percent,     110,  9}, // 10%
    {100 percent,     150, 10}, // 5%
};
