// growth_rate: MACRO
// ; [1]/[2]*n**3 + [3]*n**2 + [4]*n - [5]
// 	dn \1, \2
// 	if \3 < 0
// 		db -\3 | $80 ; signed magnitude
// 	else
// 		db \3
// 	endc
// 	db \4, \5
// ENDM
#include "../constants.h"
#include "growth_rates.h"

#define smgn(_x) ((_x < 0)? -(_x) | 0x80: _x)
#define growth_rate(_a, _b, _c, _d, _e) (struct GrowthRate){.a=(_a & 0xf), .b=(_b & 0xf), .c=smgn(_c), .d=_d, .e=_e}

const struct GrowthRate GrowthRates[] = {
// entries correspond to GROWTH_* (see constants/pokemon_data_constants.asm)
// table_width 4, GrowthRates
    [GROWTH_MEDIUM_FAST]    = growth_rate(1, 1,   0,   0,   0), // Medium Fast
    [GROWTH_SLIGHTLY_FAST]  = growth_rate(3, 4,  10,   0,  30), // Slightly Fast
    [GROWTH_SLIGHTLY_SLOW]  = growth_rate(3, 4,  20,   0,  70), // Slightly Slow
    [GROWTH_MEDIUM_SLOW]    = growth_rate(6, 5, -15, 100, 140), // Medium Slow
    [GROWTH_FAST]           = growth_rate(4, 5,   0,   0,   0), // Fast
    [GROWTH_SLOW]           = growth_rate(5, 4,   0,   0,   0), // Slow
};

static_assert(lengthof(GrowthRates) == NUM_GROWTH_RATES, "");
