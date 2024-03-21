#include "../../constants.h"

//     FEATHERY_BED,
//     PIKACHU_BED,
//     PINK_BED,
//     POLKADOT_BED,
//     RED_CARPET,
//     BLUE_CARPET,
//     YELLOW_CARPET,
//     GREEN_CARPET,
//     NUM_DECO_NAMES,

const char* const DecorationNames[] = {
// entries correspond to constants/deco_constants.asm
    // list_start DecorationNames
    [CANCEL_DECO] = "CANCEL",
    [PUT_IT_AWAY] = "PUT IT AWAY",
    [MAGNAPLANT] = "MAGNAPLANT",
    [TROPICPLANT] = "TROPICPLANT",
    [JUMBOPLANT] = "JUMBOPLANT",
    [TOWN_MAP_POSTER] = "TOWN MAP",
    [FAMICOM] = "NES",
    [SUPER_NES] = "SUPER NES",
    [NINTENDO_64] = "NINTENDO 64",
    [VIRTUAL_BOY] = "VIRTUAL BOY",
    [GOLD_TROPHY] = "GOLD TROPHY",
    [SILVER_TROPHY] = "SILVER TROPHY",
    [SURF_PIKA_DOLL] = "SURF PIKACHU DOLL",
    [_BED] = " BED",
    [_CARPET] = " CARPET",
    [_POSTER] = " POSTER",
    [_DOLL] = " DOLL",
    [BIG_] = "BIG ",
    [FEATHERY_BED] = "FEATHERY",
    [PIKACHU_BED] = "PIKACHU",
    [PINK_BED] = "PINK",
    [POLKADOT_BED] = "POLKADOT",
    [RED_CARPET] = "RED",
    [BLUE_CARPET] = "BLUE",
    [YELLOW_CARPET] = "YELLOW",
    [GREEN_CARPET] = "GREEN",
};
static_assert(lengthof(DecorationNames) == NUM_DECO_NAMES, "");
