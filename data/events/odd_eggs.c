#include "../../constants.h"
#define NUM_ODD_EGGS 14
#include "../../charmap.h"

// prob: MACRO
// prob_total += \1
// 	dw prob_total * $ffff / 100
// ENDM
#define prob(_x) _x * 0xffff / 100

const uint16_t OddEggProbabilities[] = {
// entries correspond to OddEggs (below)
// table_width 2, OddEggProbabilities
// prob_total = 0
// Pichu
    prob(8),   // 8%
    prob(9),   // 1%
// Cleffa
    prob(25),  // 16%
    prob(28),  // 3%
// Igglybuff
    prob(44),  // 16%
    prob(47),  // 3%
// Smoochum
    prob(61),  // 14%
    prob(63),  // 2%
// Magby
    prob(73),  // 10%
    prob(75),  // 2%
// Elekid
    prob(87),  // 12%
    prob(89),  // 2%
// Tyrogue
    prob(99),  // 10%
    prob(100), // 1%
};
static_assert(lengthof(OddEggProbabilities) == NUM_ODD_EGGS);

#define CHAR__(_l) (CHAR_A + (_l - 'A'))
#define dvs(_0, _1, _2, _3) (_0) << 12 | (_1) << 8 | (_2) << 4 | (_3)
#define dt(_x) LOW(_x), HIGH(_x), HIGH((_x) >> 8)
#define bigdw(_x) ((_x) >> 8) | ((_x) << 8)
const struct NicknamedMon OddEggs[] = {
// table_width NICKNAMED_MON_STRUCT_LENGTH, OddEggs
    {.pmon = {.mon = {
            .species = PICHU,
            .item = NO_ITEM,
            .moves = {THUNDERSHOCK, CHARM, DIZZY_PUNCH, 0},
            .id = 2048, // OT ID
            .exp = {dt(125)}, // Exp
            // Stat exp
            .statExp = {
                0,
                0,
                0,
                0,
                0,
            },
            .DVs = dvs(0, 0, 0, 0), // DVs
            .PP = {30, 20, 10, 0}, // PP
            .happiness = 20, // Step cycles to hatch
            .pokerusStatus = 0, .caughtData = {0, 0}, // Pokerus, Caught data
            .level = 5, // Level
        },
        .status = 0, .unused = 0, // Status
        .HP = 0, // HP
        .maxHP = bigdw(17), // Max HP
        .stats = {
            bigdw(9),   // Atk
            bigdw(6),   // Def
            bigdw(11),  // Spd
            bigdw(8),   // SAtk
            bigdw(8),   // SDef
        },
    },
    .nickname = {CHAR__('E'), CHAR__('G'), CHAR__('G'), CHAR_TERM, CHAR_TERM, CHAR_TERM, CHAR_TERM, CHAR_TERM, CHAR_TERM, CHAR_TERM, CHAR_TERM}  //"EGG@@@@@@@@"
    },

    {.pmon = {.mon = {
            .species = PICHU,
            .item = NO_ITEM,
            .moves = {THUNDERSHOCK, CHARM, DIZZY_PUNCH, 0},
            .id = 256, // OT ID
            .exp = {dt(125)}, // Exp
            // Stat exp
            .statExp = {
                bigdw(0),
                bigdw(0),
                bigdw(0),
                bigdw(0),
                bigdw(0),
            },
            .DVs = dvs(2, 10, 10, 10), // DVs
            .PP = {30, 20, 10, 0}, // PP
            .happiness = 20, // Step cycles to hatch
            .pokerusStatus = 0, .caughtData = {0, 0}, // Pokerus, Caught data
            .level = 5, // Level
        },
        .status = 0, .unused = 0, // Status
        .HP = bigdw(0), // HP
        .maxHP = bigdw(17), // Max HP
        .stats = {
            bigdw(9),  // Atk
            bigdw(7),  // Def
            bigdw(12), // Spd
            bigdw(9),  // SAtk
            bigdw(9),  // SDef
        },
    },
    .nickname = {CHAR__('E'), CHAR__('G'), CHAR__('G'), CHAR_TERM, CHAR_TERM, CHAR_TERM, CHAR_TERM, CHAR_TERM, CHAR_TERM, CHAR_TERM, CHAR_TERM}  // db "EGG@@@@@@@@"
    },

    {.pmon = {.mon = {
            .species = CLEFFA,
            .item = NO_ITEM,
            .moves = {POUND, CHARM, DIZZY_PUNCH, 0},
            .id = 4096, // OT ID
            .exp = {dt(125)},  // Exp
            // ; Stat exp
            .statExp = {
                bigdw(0),
                bigdw(0),
                bigdw(0),
                bigdw(0),
                bigdw(0),
            },
            .DVs = dvs(0, 0, 0, 0), // DVs
            .PP = {35, 20, 10, 0}, // PP
            .happiness = 20, // Step cycles to hatch
            .pokerusStatus = 0, .caughtData = {0, 0}, // Pokerus, Caught data
            .level = 5, // Level
        },
        .status = 0, .unused = 0, // Status
        .HP = bigdw(0), // HP
        .maxHP = bigdw(20), // Max HP
        .stats = {
            bigdw(7), // Atk
            bigdw(7), // Def
            bigdw(6), // Spd
            bigdw(9), // SAtk
            bigdw(10), // SDef
        },
    },
    .nickname = {CHAR__('E'), CHAR__('G'), CHAR__('G'), CHAR_TERM, CHAR_TERM, CHAR_TERM, CHAR_TERM, CHAR_TERM, CHAR_TERM, CHAR_TERM, CHAR_TERM}  // db "EGG@@@@@@@@"
    },

    {.pmon = {.mon = {
            .species = CLEFFA,
            .item = NO_ITEM,
            .moves = {POUND, CHARM, DIZZY_PUNCH, 0},
            .id = 768, // OT ID
            .exp = {dt(125)},  // Exp
            // ; Stat exp
            .statExp = {
                bigdw(0),
                bigdw(0),
                bigdw(0),
                bigdw(0),
                bigdw(0),
            },
            .DVs = dvs(2, 10, 10, 10), // DVs
            .PP = {35, 20, 10, 0}, // PP
            .happiness = 20, // Step cycles to hatch
            .pokerusStatus = 0, .caughtData = {0, 0}, // Pokerus, Caught data
            .level = 5, // Level
        },
        .status = 0, .unused = 0, // Status
        .HP = bigdw(0), // HP
        .maxHP = bigdw(20), // Max HP
        .stats = {
            bigdw(7), // Atk
            bigdw(8), // Def
            bigdw(7), // Spd
            bigdw(10), // SAtk
            bigdw(11), // SDef
        },
    },
    .nickname = {CHAR__('E'), CHAR__('G'), CHAR__('G'), CHAR_TERM, CHAR_TERM, CHAR_TERM, CHAR_TERM, CHAR_TERM, CHAR_TERM, CHAR_TERM, CHAR_TERM}  // db "EGG@@@@@@@@"
    },

    {.pmon = {.mon = {
            .species = IGGLYBUFF,
            .item = NO_ITEM,
            .moves = {SING, CHARM, DIZZY_PUNCH, 0},
            .id = 4096, // OT ID
            .exp = {dt(125)}, // Exp
            // ; Stat exp
            .statExp = {
                bigdw(0),
                bigdw(0),
                bigdw(0),
                bigdw(0),
                bigdw(0),
            },
            .DVs = dvs(0, 0, 0, 0), // DVs
            .PP = {15, 20, 10, 0}, // PP
            .happiness = 20, // Step cycles to hatch
            .pokerusStatus = 0, .caughtData = {0, 0}, // Pokerus, Caught data
            .level = 5, // Level
        },
        .status = 0, .unused = 0, // Status
        .HP = bigdw(0), // HP
        .maxHP = bigdw(24), // Max HP
        .stats = {
            bigdw(8), // Atk
            bigdw(6), // Def
            bigdw(6), // Spd
            bigdw(9), // SAtk
            bigdw(7), // SDef
        },
    },
    .nickname = {CHAR__('E'), CHAR__('G'), CHAR__('G'), CHAR_TERM, CHAR_TERM, CHAR_TERM, CHAR_TERM, CHAR_TERM, CHAR_TERM, CHAR_TERM, CHAR_TERM}  // db "EGG@@@@@@@@"
    },

    {.pmon = {.mon = {
            .species = IGGLYBUFF,
            .item = NO_ITEM,
            .moves = {SING, CHARM, DIZZY_PUNCH, 0},
            .id = 768, // OT ID
            .exp = {dt(125)}, // Exp
            // ; Stat exp
            .statExp = {
                bigdw(0),
                bigdw(0),
                bigdw(0),
                bigdw(0),
                bigdw(0),
            },
            .DVs = dvs(2, 10, 10, 10), // DVs
            .PP = {15, 20, 10, 0}, // PP
            .happiness = 20, // Step cycles to hatch
            .pokerusStatus = 0, .caughtData = {0, 0}, // Pokerus, Caught data
            .level = 5, // Level
        },
        .status = 0, .unused = 0, // Status
        .HP = bigdw(0), // HP
        .maxHP = bigdw(24), // Max HP
        .stats = {
            bigdw(8), // Atk
            bigdw(7), // Def
            bigdw(7), // Spd
            bigdw(10), // SAtk
            bigdw(8), // SDef
        },
    },
    .nickname = {CHAR__('E'), CHAR__('G'), CHAR__('G'), CHAR_TERM, CHAR_TERM, CHAR_TERM, CHAR_TERM, CHAR_TERM, CHAR_TERM, CHAR_TERM, CHAR_TERM}  // db "EGG@@@@@@@@"
    },

    {.pmon = {.mon = {
            .species = SMOOCHUM,
            .item = NO_ITEM,
            .moves = {POUND, LICK, DIZZY_PUNCH, 0},
            .id = 3584, // OT ID
            .exp = {dt(125)}, // Exp
            // ; Stat exp
            .statExp = {
                bigdw(0),
                bigdw(0),
                bigdw(0),
                bigdw(0),
                bigdw(0),
            },
            .DVs = dvs(0, 0, 0, 0), // DVs
            .PP = {35, 30, 10, 0}, // PP
            .happiness = 20, // Step cycles to hatch
            .pokerusStatus = 0, .caughtData = {0, 0}, // Pokerus, Caught data
            .level = 5, // Level
        },
        .status = 0, .unused = 0, // Status
        .HP = bigdw(0), // HP
        .maxHP = bigdw(19), // Max HP
        .stats = {
            bigdw(8), // Atk
            bigdw(6), // Def
            bigdw(11), // Spd
            bigdw(13), // SAtk
            bigdw(11), // SDef
        },
    },
    .nickname = {CHAR__('E'), CHAR__('G'), CHAR__('G'), CHAR_TERM, CHAR_TERM, CHAR_TERM, CHAR_TERM, CHAR_TERM, CHAR_TERM, CHAR_TERM, CHAR_TERM}  // db "EGG@@@@@@@@"
    },

    {.pmon = {.mon = {
            .species = SMOOCHUM,
            .item = NO_ITEM,
            .moves = {POUND, LICK, DIZZY_PUNCH, 0},
            .id = 512, // OT ID
            .exp = {dt(125)}, // Exp
            // ; Stat exp
            .statExp = {
                bigdw(0),
                bigdw(0),
                bigdw(0),
                bigdw(0),
                bigdw(0),
            },
            .DVs = dvs(2, 10, 10, 10), // DVs
            .PP = {35, 30, 10, 0}, // PP
            .happiness = 20, // Step cycles to hatch
            .pokerusStatus = 0, .caughtData = {0, 0}, // Pokerus, Caught data
            .level = 5, // Level
        },
        .status = 0, .unused = 0, // Status
        .HP = bigdw(0), // HP
        .maxHP = bigdw(19), // Max HP
        .stats = {
            bigdw(8), // Atk
            bigdw(7), // Def
            bigdw(12), // Spd
            bigdw(14), // SAtk
            bigdw(12), // SDef
        },
    },
    .nickname = {CHAR__('E'), CHAR__('G'), CHAR__('G'), CHAR_TERM, CHAR_TERM, CHAR_TERM, CHAR_TERM, CHAR_TERM, CHAR_TERM, CHAR_TERM, CHAR_TERM}  // db "EGG@@@@@@@@"
    },

    {.pmon = {.mon = {
            .species = MAGBY,
            .item = NO_ITEM,
            .moves = {EMBER, DIZZY_PUNCH, 0, 0},
            .id = 2560, // OT ID
            .exp = {dt(125)}, // Exp
            // ; Stat exp
            .statExp = {
                bigdw(0),
                bigdw(0),
                bigdw(0),
                bigdw(0),
                bigdw(0),
            },
            .DVs = dvs(0, 0, 0, 0), // DVs
            .PP = {25, 10, 0, 0}, // PP
            .happiness = 20, // Step cycles to hatch
            .pokerusStatus = 0, .caughtData = {0, 0}, // Pokerus, Caught data
            .level = 5, // Level
        },
        .status = 0, .unused = 0, // Status
        .HP = bigdw(0), // HP
        .maxHP = bigdw(19), // Max HP
        .stats = {
            bigdw(12), // Atk
            bigdw(8),  // Def
            bigdw(13), // Spd
            bigdw(12), // SAtk
            bigdw(10), // SDef
        },
    },
    .nickname = {CHAR__('E'), CHAR__('G'), CHAR__('G'), CHAR_TERM, CHAR_TERM, CHAR_TERM, CHAR_TERM, CHAR_TERM, CHAR_TERM, CHAR_TERM, CHAR_TERM}  // db "EGG@@@@@@@@"
    },

    {.pmon = {.mon = {
            .species = MAGBY,
            .item = NO_ITEM,
            .moves = {EMBER, DIZZY_PUNCH, 0, 0},
            .id = 512, // OT ID
            .exp = {dt(125)}, // Exp
            // ; Stat exp
            .statExp = {
                bigdw(0),
                bigdw(0),
                bigdw(0),
                bigdw(0),
                bigdw(0),
            },
            .DVs = dvs(2, 10, 10, 10), // DVs
            .PP = {25, 10, 0, 0}, // PP
            .happiness = 20, // Step cycles to hatch
            .pokerusStatus = 0, .caughtData = {0, 0}, // Pokerus, Caught data
            .level = 5, // Level
        },
        .status = 0, .unused = 0, // Status
        .HP = bigdw(0), // HP
        .maxHP = bigdw(19), // Max HP
        .stats = {
            bigdw(12), // Atk
            bigdw(9),  // Def
            bigdw(14), // Spd
            bigdw(13), // SAtk
            bigdw(11), // SDef
        },
    },
    .nickname = {CHAR__('E'), CHAR__('G'), CHAR__('G'), CHAR_TERM, CHAR_TERM, CHAR_TERM, CHAR_TERM, CHAR_TERM, CHAR_TERM, CHAR_TERM, CHAR_TERM}  // db "EGG@@@@@@@@"
    },

    {.pmon = {.mon = {
            .species = ELEKID,
            .item = NO_ITEM,
            .moves = {QUICK_ATTACK, LEER, DIZZY_PUNCH, 0},
            .id = 3072, // OT ID
            .exp = {dt(125)}, // Exp
            // ; Stat exp
            .statExp = {
                bigdw(0),
                bigdw(0),
                bigdw(0),
                bigdw(0),
                bigdw(0),
            },
            .DVs = dvs(0, 0, 0, 0), // DVs
            .PP = {30, 30, 10, 0}, // PP
            .happiness = 20, // Step cycles to hatch
            .pokerusStatus = 0, .caughtData = {0, 0}, // Pokerus, Caught data
            .level = 5, // Level
        },
        .status = 0, .unused = 0, // Status
        .HP = bigdw(0), // HP
        .maxHP = bigdw(19), // Max HP
        .stats = {
            bigdw(11), // Atk
            bigdw(8),  // Def
            bigdw(14), // Spd
            bigdw(11), // SAtk
            bigdw(10), // SDef
        },
    },
    .nickname = {CHAR__('E'), CHAR__('G'), CHAR__('G'), CHAR_TERM, CHAR_TERM, CHAR_TERM, CHAR_TERM, CHAR_TERM, CHAR_TERM, CHAR_TERM, CHAR_TERM}  // db "EGG@@@@@@@@"
    },

    {.pmon = {.mon = {
            .species = ELEKID,
            .item = NO_ITEM,
            .moves = {QUICK_ATTACK, LEER, DIZZY_PUNCH, 0},
            .id = 512, // OT ID
            .exp = {dt(125)}, // Exp
            // ; Stat exp
            .statExp = {
                bigdw(0),
                bigdw(0),
                bigdw(0),
                bigdw(0),
                bigdw(0),
            },
            .DVs = dvs(2, 10, 10, 10), // DVs
            .PP = {30, 30, 10, 0}, // PP
            .happiness = 20, // Step cycles to hatch
            .pokerusStatus = 0, .caughtData = {0, 0}, // Pokerus, Caught data
            .level = 5, // Level
        },
        .status = 0, .unused = 0, // Status
        .HP = bigdw(0), // HP
        .maxHP = bigdw(19), // Max HP
        .stats = {
            bigdw(11), // Atk
            bigdw(9),  // Def
            bigdw(15), // Spd
            bigdw(12), // SAtk
            bigdw(11), // SDef
        },
    },
    .nickname = {CHAR__('E'), CHAR__('G'), CHAR__('G'), CHAR_TERM, CHAR_TERM, CHAR_TERM, CHAR_TERM, CHAR_TERM, CHAR_TERM, CHAR_TERM, CHAR_TERM}  // db "EGG@@@@@@@@"
    },

    {.pmon = {.mon = {
            .species = TYROGUE,
            .item = NO_ITEM,
            .moves = {TACKLE, DIZZY_PUNCH, 0, 0},
            .id = 2560, // OT ID
            .exp = {dt(125)}, // Exp
            // ; Stat exp
            .statExp = {
                bigdw(0),
                bigdw(0),
                bigdw(0),
                bigdw(0),
                bigdw(0),
            },
            .DVs = dvs(0, 0, 0, 0), // DVs
            .PP = {35, 10, 0, 0}, // PP
            .happiness = 20, // Step cycles to hatch
            .pokerusStatus = 0, .caughtData = {0, 0}, // Pokerus, Caught data
            .level = 5, // Level
        },
        .status = 0, .unused = 0, // Status
        .HP = bigdw(0), // HP
        .maxHP = bigdw(18), // Max HP
        .stats = {
            bigdw(8), // Atk
            bigdw(8), // Def
            bigdw(8), // Spd
            bigdw(8), // SAtk
            bigdw(8), // SDef
        },
    },
    .nickname = {CHAR__('E'), CHAR__('G'), CHAR__('G'), CHAR_TERM, CHAR_TERM, CHAR_TERM, CHAR_TERM, CHAR_TERM, CHAR_TERM, CHAR_TERM, CHAR_TERM}  // db "EGG@@@@@@@@"
    },

    {.pmon = {.mon = {
            .species = TYROGUE,
            .item = NO_ITEM,
            .moves = {TACKLE, DIZZY_PUNCH, 0, 0},
            .id = 256, // OT ID
            .exp = {dt(125)}, // Exp
            // ; Stat exp
            .statExp = {
                bigdw(0),
                bigdw(0),
                bigdw(0),
                bigdw(0),
                bigdw(0),
            },
            .DVs = dvs(2, 10, 10, 10), // DVs
            .PP = {35, 10, 0, 0}, // PP
            .happiness = 20, // Step cycles to hatch
            .pokerusStatus = 0, .caughtData = {0, 0}, // Pokerus, Caught data
            .level = 5, // Level
        },
        .status = 0, .unused = 0, // Status
        .HP = bigdw(0), // HP
        .maxHP = bigdw(18), // Max HP
        .stats = {
            bigdw(8), // Atk
            bigdw(9), // Def
            bigdw(9), // Spd
            bigdw(9), // SAtk
            bigdw(9), // SDef
        },
    },
    .nickname = {CHAR__('E'), CHAR__('G'), CHAR__('G'), CHAR_TERM, CHAR_TERM, CHAR_TERM, CHAR_TERM, CHAR_TERM, CHAR_TERM, CHAR_TERM, CHAR_TERM}  // db "EGG@@@@@@@@"
    },
};
static_assert(lengthof(OddEggs) == NUM_ODD_EGGS);
