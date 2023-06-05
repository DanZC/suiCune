#include "../../constants.h"

const uint8_t TreeMonSet_City[] = {
#define TreeMonSet_Canyon TreeMonSet_City
// common
	50, SPEAROW,    10,
	15, SPEAROW,    10,
	15, SPEAROW,    10,
	10, AIPOM,      10,
	 5, AIPOM,      10,
	 5, AIPOM,      10,
	0xff,
// rare
	50, SPEAROW,    10,
	15, HERACROSS,  10,
	15, HERACROSS,  10,
	10, AIPOM,      10,
	 5, AIPOM,      10,
	 5, AIPOM,      10,
	0xff
};

const uint8_t TreeMonSet_Town[] = {
// common
    50, SPEAROW,    10,
    15, EKANS,      10,
    15, SPEAROW,    10,
    10, AIPOM,      10,
     5, AIPOM,      10,
     5, AIPOM,      10,
    0xff,
// rare
    50, SPEAROW,    10,
    15, HERACROSS,  10,
    15, HERACROSS,  10,
    10, AIPOM,      10,
     5, AIPOM,      10,
     5, AIPOM,      10,
    0xff
};


const uint8_t TreeMonSet_Route[] = {
// common
    50, HOOTHOOT,   10,
    15, SPINARAK,   10,
    15, LEDYBA,     10,
    10, EXEGGCUTE,  10,
     5, EXEGGCUTE,  10,
     5, EXEGGCUTE,  10,
    0xff,
// rare
    50, HOOTHOOT,   10,
    15, PINECO,     10,
    15, PINECO,     10,
    10, EXEGGCUTE,  10,
     5, EXEGGCUTE,  10,
     5, EXEGGCUTE,  10,
    0xff
};

const uint8_t TreeMonSet_Kanto[] = {
// common
	50, HOOTHOOT,   10,
	15, EKANS,      10,
	15, HOOTHOOT,   10,
	10, EXEGGCUTE,  10,
	 5, EXEGGCUTE,  10,
	 5, EXEGGCUTE,  10,
	0xff,
// rare
	50, HOOTHOOT,   10,
	15, PINECO,     10,
	15, PINECO,     10,
	10, EXEGGCUTE,  10,
	 5, EXEGGCUTE,  10,
	 5, EXEGGCUTE,  10,
	0xff
};

const uint8_t TreeMonSet_Lake[] = {
// common
    50, HOOTHOOT,   10,
    15, VENONAT,    10,
    15, HOOTHOOT,   10,
    10, EXEGGCUTE,  10,
     5, EXEGGCUTE,  10,
     5, EXEGGCUTE,  10,
    0xff,
// rare
    50, HOOTHOOT,   10,
    15, PINECO,     10,
    15, PINECO,     10,
    10, EXEGGCUTE,  10,
     5, EXEGGCUTE,  10,
     5, EXEGGCUTE,  10,
    0xff
};

const uint8_t TreeMonSet_Forest[] = {
// common
    50, HOOTHOOT,   10,
    15, PINECO,     10,
    15, PINECO,     10,
    10, NOCTOWL,    10,
     5, BUTTERFREE, 10,
     5, BEEDRILL,   10,
    0xff,
// rare
    50, HOOTHOOT,   10,
    15, CATERPIE,   10,
    15, WEEDLE,     10,
    10, HOOTHOOT,   10,
     5, METAPOD,    10,
     5, KAKUNA,     10,
    0xff,
};

const uint8_t TreeMonSet_Rock[] = {
    90, KRABBY,     15,
    10, SHUCKLE,    15,
    0xff
};

const uint8_t* const TreeMons[] = {
// entries correspond to TREEMON_SET_* constants
    [TREEMON_SET_CITY]   = TreeMonSet_City,
    [TREEMON_SET_CANYON] = TreeMonSet_Canyon,
    [TREEMON_SET_TOWN]   = TreeMonSet_Town,
    [TREEMON_SET_ROUTE]  = TreeMonSet_Route,
    [TREEMON_SET_KANTO]  = TreeMonSet_Kanto,
    [TREEMON_SET_LAKE]   = TreeMonSet_Lake,
    [TREEMON_SET_FOREST] = TreeMonSet_Forest,
    [TREEMON_SET_ROCK]   = TreeMonSet_Rock,
};

