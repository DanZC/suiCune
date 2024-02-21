#include "../../constants.h"

// Evolutions and attacks are grouped together since they're both checked at level-up.
static const struct EvoMoves BulbasaurEvosAttacks = {
    .evolutions = (struct EvoData[]) {
        {EVOLVE_LEVEL, .lvl={16}, .species=IVYSAUR},
        {0},
    },
    .learnset = (struct LevelMove[]) {
        {1, TACKLE},
        {4, GROWL},
        {7, LEECH_SEED},
        {10, VINE_WHIP},
        {15, POISONPOWDER},
        {15, SLEEP_POWDER},
        {20, RAZOR_LEAF},
        {25, SWEET_SCENT},
        {32, GROWTH},
        {39, SYNTHESIS},
        {46, SOLARBEAM},
        {0xff, 0},
    },
};

static const struct EvoMoves IvysaurEvosAttacks = {
    .evolutions = (struct EvoData[]) {
        {EVOLVE_LEVEL, .lvl={32}, .species=VENUSAUR},
        {0},
    },
    .learnset = (struct LevelMove[]) {
        {1, TACKLE},
        {1, GROWL},
        {1, LEECH_SEED},
        {4, GROWL},
        {7, LEECH_SEED},
        {10, VINE_WHIP},
        {15, POISONPOWDER},
        {15, SLEEP_POWDER},
        {22, RAZOR_LEAF},
        {29, SWEET_SCENT},
        {38, GROWTH},
        {47, SYNTHESIS},
        {56, SOLARBEAM},
        {0xff, 0},
    },
};

static const struct EvoMoves VenusaurEvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, TACKLE},
        {1, GROWL},
        {1, LEECH_SEED},
        {1, VINE_WHIP},
        {4, GROWL},
        {7, LEECH_SEED},
        {10, VINE_WHIP},
        {15, POISONPOWDER},
        {15, SLEEP_POWDER},
        {22, RAZOR_LEAF},
        {29, SWEET_SCENT},
        {41, GROWTH},
        {53, SYNTHESIS},
        {65, SOLARBEAM},
        {0xff, 0},
    },
};

static const struct EvoMoves CharmanderEvosAttacks = {
    .evolutions = (struct EvoData[]) {
        {EVOLVE_LEVEL, .lvl={16}, .species=CHARMELEON},
        {0},
    },
    .learnset = (struct LevelMove[]) {
        {1, SCRATCH},
        {1, GROWL},
        {7, EMBER},
        {13, SMOKESCREEN},
        {19, RAGE},
        {25, SCARY_FACE},
        {31, FLAMETHROWER},
        {37, SLASH},
        {43, DRAGON_RAGE},
        {49, FIRE_SPIN},
        {0xff, 0},
    },
};

static const struct EvoMoves CharmeleonEvosAttacks = {
    .evolutions = (struct EvoData[]) {
        {EVOLVE_LEVEL, .lvl={36}, .species=CHARIZARD},
        {0},
    },
    .learnset = (struct LevelMove[]) {
        {1, SCRATCH},
        {1, GROWL},
        {1, EMBER},
        {7, EMBER},
        {13, SMOKESCREEN},
        {20, RAGE},
        {27, SCARY_FACE},
        {34, FLAMETHROWER},
        {41, SLASH},
        {48, DRAGON_RAGE},
        {55, FIRE_SPIN},
        {0xff, 0},
    },
};

static const struct EvoMoves CharizardEvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, SCRATCH},
        {1, GROWL},
        {1, EMBER},
        {1, SMOKESCREEN},
        {7, EMBER},
        {13, SMOKESCREEN},
        {20, RAGE},
        {27, SCARY_FACE},
        {34, FLAMETHROWER},
        {36, WING_ATTACK},
        {44, SLASH},
        {54, DRAGON_RAGE},
        {64, FIRE_SPIN},
        {0xff, 0},
    },
};

static const struct EvoMoves SquirtleEvosAttacks = {
    .evolutions = (struct EvoData[]) {
        {EVOLVE_LEVEL, .lvl={16}, .species=WARTORTLE},
        {0},
    },
    .learnset = (struct LevelMove[]) {
        {1, TACKLE},
        {4, TAIL_WHIP},
        {7, BUBBLE},
        {10, WITHDRAW},
        {13, WATER_GUN},
        {18, BITE},
        {23, RAPID_SPIN},
        {28, PROTECT},
        {33, RAIN_DANCE},
        {40, SKULL_BASH},
        {47, HYDRO_PUMP},
        {0xff, 0},
    },
};

static const struct EvoMoves WartortleEvosAttacks = {
    .evolutions = (struct EvoData[]) {
        {EVOLVE_LEVEL, .lvl={36}, .species=BLASTOISE},
        {0},
    },
    .learnset = (struct LevelMove[]) {
        {1, TACKLE},
        {1, TAIL_WHIP},
        {1, BUBBLE},
        {4, TAIL_WHIP},
        {7, BUBBLE},
        {10, WITHDRAW},
        {13, WATER_GUN},
        {19, BITE},
        {25, RAPID_SPIN},
        {31, PROTECT},
        {37, RAIN_DANCE},
        {45, SKULL_BASH},
        {53, HYDRO_PUMP},
        {0xff, 0},
    },
};

static const struct EvoMoves BlastoiseEvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, TACKLE},
        {1, TAIL_WHIP},
        {1, BUBBLE},
        {1, WITHDRAW},
        {4, TAIL_WHIP},
        {7, BUBBLE},
        {10, WITHDRAW},
        {13, WATER_GUN},
        {19, BITE},
        {25, RAPID_SPIN},
        {31, PROTECT},
        {42, RAIN_DANCE},
        {55, SKULL_BASH},
        {68, HYDRO_PUMP},
        {0xff, 0},
    },
};

static const struct EvoMoves CaterpieEvosAttacks = {
    .evolutions = (struct EvoData[]) {
        {EVOLVE_LEVEL, .lvl={7}, .species=METAPOD},
        {0},
    },
    .learnset = (struct LevelMove[]) {
        {1, TACKLE},
        {1, STRING_SHOT},
        {0xff, 0},
    },
};

static const struct EvoMoves MetapodEvosAttacks = {
    .evolutions = (struct EvoData[]) {
        {EVOLVE_LEVEL, .lvl={10}, .species=BUTTERFREE},
        {0},
    },
    .learnset = (struct LevelMove[]) {
        {1, HARDEN},
        {7, HARDEN},
        {0xff, 0},
    },
};

static const struct EvoMoves ButterfreeEvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, CONFUSION},
        {10, CONFUSION},
        {13, POISONPOWDER},
        {14, STUN_SPORE},
        {15, SLEEP_POWDER},
        {18, SUPERSONIC},
        {23, WHIRLWIND},
        {28, GUST},
        {34, PSYBEAM},
        {40, SAFEGUARD},
        {0xff, 0},
    },
};

static const struct EvoMoves WeedleEvosAttacks = {
    .evolutions = (struct EvoData[]) {
        {EVOLVE_LEVEL, .lvl={7}, .species=KAKUNA},
        {0},
    },
    .learnset = (struct LevelMove[]) {
        {1, POISON_STING},
        {1, STRING_SHOT},
        {0xff, 0},
    },
};

static const struct EvoMoves KakunaEvosAttacks = {
    .evolutions = (struct EvoData[]) {
        {EVOLVE_LEVEL, .lvl={10}, .species=BEEDRILL},
        {0},
    },
    .learnset = (struct LevelMove[]) {
        {1, HARDEN},
        {7, HARDEN},
        {0xff, 0},
    },
};

static const struct EvoMoves BeedrillEvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, FURY_ATTACK},
        {10, FURY_ATTACK},
        {15, FOCUS_ENERGY},
        {20, TWINEEDLE},
        {25, RAGE},
        {30, PURSUIT},
        {35, PIN_MISSILE},
        {40, AGILITY},
        {0xff, 0},
    },
};

static const struct EvoMoves PidgeyEvosAttacks = {
    .evolutions = (struct EvoData[]) {
        {EVOLVE_LEVEL, .lvl={18}, .species=PIDGEOTTO},
        {0},
    },
    .learnset = (struct LevelMove[]) {
        {1, TACKLE},
        {5, SAND_ATTACK},
        {9, GUST},
        {15, QUICK_ATTACK},
        {21, WHIRLWIND},
        {29, WING_ATTACK},
        {37, AGILITY},
        {47, MIRROR_MOVE},
        {0xff, 0},
    },
};

static const struct EvoMoves PidgeottoEvosAttacks = {
    .evolutions = (struct EvoData[]) {
        {EVOLVE_LEVEL, .lvl={36}, .species=PIDGEOT},
        {0},
    },
    .learnset = (struct LevelMove[]) {
        {1, TACKLE},
        {1, SAND_ATTACK},
        {1, GUST},
        {5, SAND_ATTACK},
        {9, GUST},
        {15, QUICK_ATTACK},
        {23, WHIRLWIND},
        {33, WING_ATTACK},
        {43, AGILITY},
        {55, MIRROR_MOVE},
        {0xff, 0},
    },
};

static const struct EvoMoves PidgeotEvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, TACKLE},
        {1, SAND_ATTACK},
        {1, GUST},
        {1, QUICK_ATTACK},
        {5, SAND_ATTACK},
        {9, GUST},
        {15, QUICK_ATTACK},
        {23, WHIRLWIND},
        {33, WING_ATTACK},
        {46, AGILITY},
        {61, MIRROR_MOVE},
        {0xff, 0},
    },
};

static const struct EvoMoves RattataEvosAttacks = {
    .evolutions = (struct EvoData[]) {
        {EVOLVE_LEVEL, .lvl={20}, .species=RATICATE},
        {0},
    },
    .learnset = (struct LevelMove[]) {
        {1, TACKLE},
        {1, TAIL_WHIP},
        {7, QUICK_ATTACK},
        {13, HYPER_FANG},
        {20, FOCUS_ENERGY},
        {27, PURSUIT},
        {34, SUPER_FANG},
        {0xff, 0},
    },
};

static const struct EvoMoves RaticateEvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, TACKLE},
        {1, TAIL_WHIP},
        {1, QUICK_ATTACK},
        {7, QUICK_ATTACK},
        {13, HYPER_FANG},
        {20, SCARY_FACE},
        {30, PURSUIT},
        {40, SUPER_FANG},
        {0xff, 0},
    },
};

static const struct EvoMoves SpearowEvosAttacks = {
    .evolutions = (struct EvoData[]) {
        {EVOLVE_LEVEL, .lvl={20}, .species=FEAROW},
        {0},
    },
    .learnset = (struct LevelMove[]) {
        {1, PECK},
        {1, GROWL},
        {7, LEER},
        {13, FURY_ATTACK},
        {25, PURSUIT},
        {31, MIRROR_MOVE},
        {37, DRILL_PECK},
        {43, AGILITY},
        {0xff, 0},
    },
};

static const struct EvoMoves FearowEvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, PECK},
        {1, GROWL},
        {1, LEER},
        {1, FURY_ATTACK},
        {7, LEER},
        {13, FURY_ATTACK},
        {26, PURSUIT},
        {32, MIRROR_MOVE},
        {40, DRILL_PECK},
        {47, AGILITY},
        {0xff, 0},
    },
};

static const struct EvoMoves EkansEvosAttacks = {
    .evolutions = (struct EvoData[]) {
        {EVOLVE_LEVEL, .lvl={22}, .species=ARBOK},
        {0},
    },
    .learnset = (struct LevelMove[]) {
        {1, WRAP},
        {1, LEER},
        {9, POISON_STING},
        {15, BITE},
        {23, GLARE},
        {29, SCREECH},
        {37, ACID},
        {43, HAZE},
        {0xff, 0},
    },
};

static const struct EvoMoves ArbokEvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, WRAP},
        {1, LEER},
        {1, POISON_STING},
        {1, BITE},
        {9, POISON_STING},
        {15, BITE},
        {25, GLARE},
        {33, SCREECH},
        {43, ACID},
        {51, HAZE},
        {0xff, 0},
    },
};

static const struct EvoMoves PikachuEvosAttacks = {
    .evolutions = (struct EvoData[]) {
        {EVOLVE_ITEM, .item={THUNDERSTONE}, .species=RAICHU},
        {0},
    },
    .learnset = (struct LevelMove[]) {
        {1, THUNDERSHOCK},
        {1, GROWL},
        {6, TAIL_WHIP},
        {8, THUNDER_WAVE},
        {11, QUICK_ATTACK},
        {15, DOUBLE_TEAM},
        {20, SLAM},
        {26, THUNDERBOLT},
        {33, AGILITY},
        {41, THUNDER},
        {50, LIGHT_SCREEN},
        {0xff, 0},
    },
};

static const struct EvoMoves RaichuEvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, THUNDERSHOCK},
        {1, TAIL_WHIP},
        {1, QUICK_ATTACK},
        {1, THUNDERBOLT},
        {0xff, 0},
    },
};

static const struct EvoMoves SandshrewEvosAttacks = {
    .evolutions = (struct EvoData[]) {
        {EVOLVE_LEVEL, .lvl={22}, .species=SANDSLASH},
        {0},
    },
    .learnset = (struct LevelMove[]) {
        {1, SCRATCH},
        {6, DEFENSE_CURL},
        {11, SAND_ATTACK},
        {17, POISON_STING},
        {23, SLASH},
        {30, SWIFT},
        {37, FURY_SWIPES},
        {45, SANDSTORM},
        {0xff, 0},
    },
};

static const struct EvoMoves SandslashEvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, SCRATCH},
        {1, DEFENSE_CURL},
        {1, SAND_ATTACK},
        {6, DEFENSE_CURL},
        {11, SAND_ATTACK},
        {17, POISON_STING},
        {24, SLASH},
        {33, SWIFT},
        {42, FURY_SWIPES},
        {52, SANDSTORM},
        {0xff, 0},
    },
};

static const struct EvoMoves NidoranFEvosAttacks = {
    .evolutions = (struct EvoData[]) {
        {EVOLVE_LEVEL, .lvl={16}, .species=NIDORINA},
        {0},
    },
    .learnset = (struct LevelMove[]) {
        {1, GROWL},
        {1, TACKLE},
        {8, SCRATCH},
        {12, DOUBLE_KICK},
        {17, POISON_STING},
        {23, TAIL_WHIP},
        {30, BITE},
        {38, FURY_SWIPES},
        {0xff, 0},
    },
};

static const struct EvoMoves NidorinaEvosAttacks = {
    .evolutions = (struct EvoData[]) {
        {EVOLVE_ITEM, .item={MOON_STONE}, .species=NIDOQUEEN},
        {0},
    },
    .learnset = (struct LevelMove[]) {
        {1, GROWL},
        {1, TACKLE},
        {8, SCRATCH},
        {12, DOUBLE_KICK},
        {19, POISON_STING},
        {27, TAIL_WHIP},
        {36, BITE},
        {46, FURY_SWIPES},
        {0xff, 0},
    },
};

static const struct EvoMoves NidoqueenEvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, TACKLE},
        {1, SCRATCH},
        {1, DOUBLE_KICK},
        {1, TAIL_WHIP},
        {23, BODY_SLAM},
        {0xff, 0},
    },
};

static const struct EvoMoves NidoranMEvosAttacks = {
    .evolutions = (struct EvoData[]) {
        {EVOLVE_LEVEL, .lvl={16}, .species=NIDORINO},
        {0},
    },
    .learnset = (struct LevelMove[]) {
        {1, LEER},
        {1, TACKLE},
        {8, HORN_ATTACK},
        {12, DOUBLE_KICK},
        {17, POISON_STING},
        {23, FOCUS_ENERGY},
        {30, FURY_ATTACK},
        {38, HORN_DRILL},
        {0xff, 0},
    },
};

static const struct EvoMoves NidorinoEvosAttacks = {
    .evolutions = (struct EvoData[]) {
        {EVOLVE_ITEM, .item={MOON_STONE}, .species=NIDOKING},
        {0},
    },
    .learnset = (struct LevelMove[]) {
        {1, LEER},
        {1, TACKLE},
        {8, HORN_ATTACK},
        {12, DOUBLE_KICK},
        {19, POISON_STING},
        {27, FOCUS_ENERGY},
        {36, FURY_ATTACK},
        {46, HORN_DRILL},
        {0xff, 0},
    },
};

static const struct EvoMoves NidokingEvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, TACKLE},
        {1, HORN_ATTACK},
        {1, DOUBLE_KICK},
        {1, POISON_STING},
        {23, THRASH},
        {0xff, 0},
    },
};

static const struct EvoMoves ClefairyEvosAttacks = {
    .evolutions = (struct EvoData[]) {
        {EVOLVE_ITEM, .item={MOON_STONE}, .species=CLEFABLE},
        {0},
    },
    .learnset = (struct LevelMove[]) {
        {1, POUND},
        {1, GROWL},
        {4, ENCORE},
        {8, SING},
        {13, DOUBLESLAP},
        {19, MINIMIZE},
        {26, DEFENSE_CURL},
        {34, METRONOME},
        {43, MOONLIGHT},
        {53, LIGHT_SCREEN},
        {0xff, 0},
    },
};

static const struct EvoMoves ClefableEvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, SING},
        {1, DOUBLESLAP},
        {1, METRONOME},
        {1, MOONLIGHT},
        {0xff, 0},
    },
};

static const struct EvoMoves VulpixEvosAttacks = {
    .evolutions = (struct EvoData[]) {
        {EVOLVE_ITEM, .item={FIRE_STONE}, .species=NINETALES},
        {0},
    },
    .learnset = (struct LevelMove[]) {
        {1, EMBER},
        {1, TAIL_WHIP},
        {7, QUICK_ATTACK},
        {13, ROAR},
        {19, CONFUSE_RAY},
        {25, SAFEGUARD},
        {31, FLAMETHROWER},
        {37, FIRE_SPIN},
        {0xff, 0},
    },
};

static const struct EvoMoves NinetalesEvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, EMBER},
        {1, QUICK_ATTACK},
        {1, CONFUSE_RAY},
        {1, SAFEGUARD},
        {43, FIRE_SPIN},
        {0xff, 0},
    },
};

static const struct EvoMoves JigglypuffEvosAttacks = {
    .evolutions = (struct EvoData[]) {
        {EVOLVE_ITEM, .item={MOON_STONE}, .species=WIGGLYTUFF},
        {0},
    },
    .learnset = (struct LevelMove[]) {
        {1, SING},
        {4, DEFENSE_CURL},
        {9, POUND},
        {14, DISABLE},
        {19, ROLLOUT},
        {24, DOUBLESLAP},
        {29, REST},
        {34, BODY_SLAM},
        {39, DOUBLE_EDGE},
        {0xff, 0},
    },
};

static const struct EvoMoves WigglytuffEvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, SING},
        {1, DISABLE},
        {1, DEFENSE_CURL},
        {1, DOUBLESLAP},
        {0xff, 0},
    },
};

static const struct EvoMoves ZubatEvosAttacks = {
    .evolutions = (struct EvoData[]) {
        {EVOLVE_LEVEL, .lvl={22}, .species=GOLBAT},
        {0},
    },
    .learnset = (struct LevelMove[]) {
        {1, LEECH_LIFE},
        {6, SUPERSONIC},
        {12, BITE},
        {19, CONFUSE_RAY},
        {27, WING_ATTACK},
        {36, MEAN_LOOK},
        {46, HAZE},
        {0xff, 0},
    },
};

static const struct EvoMoves GolbatEvosAttacks = {
    .evolutions = (struct EvoData[]) {
        {EVOLVE_HAPPINESS, .happiness={TR_ANYTIME}, .species=CROBAT},
        {0},
    },
    .learnset = (struct LevelMove[]) {
        {1, SCREECH},
        {1, LEECH_LIFE},
        {1, SUPERSONIC},
        {6, SUPERSONIC},
        {12, BITE},
        {19, CONFUSE_RAY},
        {30, WING_ATTACK},
        {42, MEAN_LOOK},
        {55, HAZE},
        {0xff, 0},
    },
};

static const struct EvoMoves OddishEvosAttacks = {
    .evolutions = (struct EvoData[]) {
        {EVOLVE_LEVEL, .lvl={21}, .species=GLOOM},
        {0},
    },
    .learnset = (struct LevelMove[]) {
        {1, ABSORB},
        {7, SWEET_SCENT},
        {14, POISONPOWDER},
        {16, STUN_SPORE},
        {18, SLEEP_POWDER},
        {23, ACID},
        {32, MOONLIGHT},
        {39, PETAL_DANCE},
        {0xff, 0},
    },
};

static const struct EvoMoves GloomEvosAttacks = {
    .evolutions = (struct EvoData[]) {
        {EVOLVE_ITEM, .item={LEAF_STONE}, .species=VILEPLUME},
        {EVOLVE_ITEM, .item={SUN_STONE}, .species=BELLOSSOM},
        {0},
    },
    .learnset = (struct LevelMove[]) {
        {1, ABSORB},
        {1, SWEET_SCENT},
        {1, POISONPOWDER},
        {7, SWEET_SCENT},
        {14, POISONPOWDER},
        {16, STUN_SPORE},
        {18, SLEEP_POWDER},
        {24, ACID},
        {35, MOONLIGHT},
        {44, PETAL_DANCE},
        {0xff, 0},
    },
};

static const struct EvoMoves VileplumeEvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, ABSORB},
        {1, SWEET_SCENT},
        {1, STUN_SPORE},
        {1, PETAL_DANCE},
        {0xff, 0},
    },
};

static const struct EvoMoves ParasEvosAttacks = {
    .evolutions = (struct EvoData[]) {
        {EVOLVE_LEVEL, .lvl={24}, .species=PARASECT},
        {0},
    },
    .learnset = (struct LevelMove[]) {
        {1, SCRATCH},
        {7, STUN_SPORE},
        {13, POISONPOWDER},
        {19, LEECH_LIFE},
        {25, SPORE},
        {31, SLASH},
        {37, GROWTH},
        {43, GIGA_DRAIN},
        {0xff, 0},
    },
};

static const struct EvoMoves ParasectEvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, SCRATCH},
        {1, STUN_SPORE},
        {1, POISONPOWDER},
        {7, STUN_SPORE},
        {13, POISONPOWDER},
        {19, LEECH_LIFE},
        {28, SPORE},
        {37, SLASH},
        {46, GROWTH},
        {55, GIGA_DRAIN},
        {0xff, 0},
    },
};

static const struct EvoMoves VenonatEvosAttacks = {
    .evolutions = (struct EvoData[]) {
        {EVOLVE_LEVEL, .lvl={31}, .species=VENOMOTH},
        {0},
    },
    .learnset = (struct LevelMove[]) {
        {1, TACKLE},
        {1, DISABLE},
        {1, FORESIGHT},
        {9, SUPERSONIC},
        {17, CONFUSION},
        {20, POISONPOWDER},
        {25, LEECH_LIFE},
        {28, STUN_SPORE},
        {33, PSYBEAM},
        {36, SLEEP_POWDER},
        {41, PSYCHIC_M},
        {0xff, 0},
    },
};

static const struct EvoMoves VenomothEvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, TACKLE},
        {1, DISABLE},
        {1, FORESIGHT},
        {1, SUPERSONIC},
        {9, SUPERSONIC},
        {17, CONFUSION},
        {20, POISONPOWDER},
        {25, LEECH_LIFE},
        {28, STUN_SPORE},
        {31, GUST},
        {36, PSYBEAM},
        {42, SLEEP_POWDER},
        {52, PSYCHIC_M},
        {0xff, 0},
    },
};

static const struct EvoMoves DiglettEvosAttacks = {
    .evolutions = (struct EvoData[]) {
        {EVOLVE_LEVEL, .lvl={26}, .species=DUGTRIO},
        {0},
    },
    .learnset = (struct LevelMove[]) {
        {1, SCRATCH},
        {5, GROWL},
        {9, MAGNITUDE},
        {17, DIG},
        {25, SAND_ATTACK},
        {33, SLASH},
        {41, EARTHQUAKE},
        {49, FISSURE},
        {0xff, 0},
    },
};

static const struct EvoMoves DugtrioEvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, TRI_ATTACK},
        {1, SCRATCH},
        {1, GROWL},
        {1, MAGNITUDE},
        {5, GROWL},
        {9, MAGNITUDE},
        {17, DIG},
        {25, SAND_ATTACK},
        {37, SLASH},
        {49, EARTHQUAKE},
        {61, FISSURE},
        {0xff, 0},
    },
};

static const struct EvoMoves MeowthEvosAttacks = {
    .evolutions = (struct EvoData[]) {
        {EVOLVE_LEVEL, .lvl={28}, .species=PERSIAN},
        {0},
    },
    .learnset = (struct LevelMove[]) {
        {1, SCRATCH},
        {1, GROWL},
        {11, BITE},
        {20, PAY_DAY},
        {28, FAINT_ATTACK},
        {35, SCREECH},
        {41, FURY_SWIPES},
        {46, SLASH},
        {0xff, 0},
    },
};

static const struct EvoMoves PersianEvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, SCRATCH},
        {1, GROWL},
        {1, BITE},
        {11, BITE},
        {20, PAY_DAY},
        {29, FAINT_ATTACK},
        {38, SCREECH},
        {46, FURY_SWIPES},
        {53, SLASH},
        {0xff, 0},
    },
};

static const struct EvoMoves PsyduckEvosAttacks = {
    .evolutions = (struct EvoData[]) {
        {EVOLVE_LEVEL, .lvl={33}, .species=GOLDUCK},
        {0},
    },
    .learnset = (struct LevelMove[]) {
        {1, SCRATCH},
        {5, TAIL_WHIP},
        {10, DISABLE},
        {16, CONFUSION},
        {23, SCREECH},
        {31, PSYCH_UP},
        {40, FURY_SWIPES},
        {50, HYDRO_PUMP},
        {0xff, 0},
    },
};

static const struct EvoMoves GolduckEvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, SCRATCH},
        {1, TAIL_WHIP},
        {1, DISABLE},
        {1, CONFUSION},
        {5, TAIL_WHIP},
        {10, DISABLE},
        {16, CONFUSION},
        {23, SCREECH},
        {31, PSYCH_UP},
        {44, FURY_SWIPES},
        {58, HYDRO_PUMP},
        {0xff, 0},
    },
};

static const struct EvoMoves MankeyEvosAttacks = {
    .evolutions = (struct EvoData[]) {
        {EVOLVE_LEVEL, .lvl={28}, .species=PRIMEAPE},
        {0},
    },
    .learnset = (struct LevelMove[]) {
        {1, SCRATCH},
        {1, LEER},
        {9, LOW_KICK},
        {15, KARATE_CHOP},
        {21, FURY_SWIPES},
        {27, FOCUS_ENERGY},
        {33, SEISMIC_TOSS},
        {39, CROSS_CHOP},
        {45, SCREECH},
        {51, THRASH},
        {0xff, 0},
    },
};

static const struct EvoMoves PrimeapeEvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, SCRATCH},
        {1, LEER},
        {1, LOW_KICK},
        {1, RAGE},
        {9, LOW_KICK},
        {15, KARATE_CHOP},
        {21, FURY_SWIPES},
        {27, FOCUS_ENERGY},
        {28, RAGE},
        {36, SEISMIC_TOSS},
        {45, CROSS_CHOP},
        {54, SCREECH},
        {63, THRASH},
        {0xff, 0},
    },
};

static const struct EvoMoves GrowlitheEvosAttacks = {
    .evolutions = (struct EvoData[]) {
        {EVOLVE_ITEM, .item={FIRE_STONE}, .species=ARCANINE},
        {0},
    },
    .learnset = (struct LevelMove[]) {
        {1, BITE},
        {1, ROAR},
        {9, EMBER},
        {18, LEER},
        {26, TAKE_DOWN},
        {34, FLAME_WHEEL},
        {42, AGILITY},
        {50, FLAMETHROWER},
        {0xff, 0},
    },
};

static const struct EvoMoves ArcanineEvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, ROAR},
        {1, LEER},
        {1, TAKE_DOWN},
        {1, FLAME_WHEEL},
        {50, EXTREMESPEED},
        {0xff, 0},
    },
};

static const struct EvoMoves PoliwagEvosAttacks = {
    .evolutions = (struct EvoData[]) {
        {EVOLVE_LEVEL, .lvl={25}, .species=POLIWHIRL},
        {0},
    },
    .learnset = (struct LevelMove[]) {
        {1, BUBBLE},
        {7, HYPNOSIS},
        {13, WATER_GUN},
        {19, DOUBLESLAP},
        {25, RAIN_DANCE},
        {31, BODY_SLAM},
        {37, BELLY_DRUM},
        {43, HYDRO_PUMP},
        {0xff, 0},
    },
};

static const struct EvoMoves PoliwhirlEvosAttacks = {
    .evolutions = (struct EvoData[]) {
        {EVOLVE_ITEM, .item={WATER_STONE}, .species=POLIWRATH},
        {EVOLVE_TRADE, .trade={KINGS_ROCK}, .species=POLITOED},
        {0},
    },
    .learnset = (struct LevelMove[]) {
        {1, BUBBLE},
        {1, HYPNOSIS},
        {1, WATER_GUN},
        {7, HYPNOSIS},
        {13, WATER_GUN},
        {19, DOUBLESLAP},
        {27, RAIN_DANCE},
        {35, BODY_SLAM},
        {43, BELLY_DRUM},
        {51, HYDRO_PUMP},
        {0xff, 0},
    },
};

static const struct EvoMoves PoliwrathEvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, WATER_GUN},
        {1, HYPNOSIS},
        {1, DOUBLESLAP},
        {1, SUBMISSION},
        {35, SUBMISSION},
        {51, MIND_READER},
        {0xff, 0},
    },
};

static const struct EvoMoves AbraEvosAttacks = {
    .evolutions = (struct EvoData[]) {
        {EVOLVE_LEVEL, .lvl={16}, .species=KADABRA},
        {0},
    },
    .learnset = (struct LevelMove[]) {
        {1, TELEPORT},
        {0xff, 0},
    },
};

static const struct EvoMoves KadabraEvosAttacks = {
    .evolutions = (struct EvoData[]) {
        {EVOLVE_TRADE, .trade={-1}, .species=ALAKAZAM},
        {0},
    },
    .learnset = (struct LevelMove[]) {
        {1, TELEPORT},
        {1, KINESIS},
        {1, CONFUSION},
        {16, CONFUSION},
        {18, DISABLE},
        {21, PSYBEAM},
        {26, RECOVER},
        {31, FUTURE_SIGHT},
        {38, PSYCHIC_M},
        {45, REFLECT},
        {0xff, 0},
    },
};

static const struct EvoMoves AlakazamEvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, TELEPORT},
        {1, KINESIS},
        {1, CONFUSION},
        {16, CONFUSION},
        {18, DISABLE},
        {21, PSYBEAM},
        {26, RECOVER},
        {31, FUTURE_SIGHT},
        {38, PSYCHIC_M},
        {45, REFLECT},
        {0xff, 0},
    },
};

static const struct EvoMoves MachopEvosAttacks = {
    .evolutions = (struct EvoData[]) {
        {EVOLVE_LEVEL, .lvl={28}, .species=MACHOKE},
        {0},
    },
    .learnset = (struct LevelMove[]) {
        {1, LOW_KICK},
        {1, LEER},
        {7, FOCUS_ENERGY},
        {13, KARATE_CHOP},
        {19, SEISMIC_TOSS},
        {25, FORESIGHT},
        {31, VITAL_THROW},
        {37, CROSS_CHOP},
        {43, SCARY_FACE},
        {49, SUBMISSION},
        {0xff, 0},
    },
};

static const struct EvoMoves MachokeEvosAttacks = {
    .evolutions = (struct EvoData[]) {
        {EVOLVE_TRADE, .trade={-1}, .species=MACHAMP},
        {0},
    },
    .learnset = (struct LevelMove[]) {
        {1, LOW_KICK},
        {1, LEER},
        {1, FOCUS_ENERGY},
        {8, FOCUS_ENERGY},
        {15, KARATE_CHOP},
        {19, SEISMIC_TOSS},
        {25, FORESIGHT},
        {34, VITAL_THROW},
        {43, CROSS_CHOP},
        {52, SCARY_FACE},
        {61, SUBMISSION},
        {0xff, 0},
    },
};

static const struct EvoMoves MachampEvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, LOW_KICK},
        {1, LEER},
        {1, FOCUS_ENERGY},
        {8, FOCUS_ENERGY},
        {15, KARATE_CHOP},
        {19, SEISMIC_TOSS},
        {25, FORESIGHT},
        {34, VITAL_THROW},
        {43, CROSS_CHOP},
        {52, SCARY_FACE},
        {61, SUBMISSION},
        {0xff, 0},
    },
};

static const struct EvoMoves BellsproutEvosAttacks = {
    .evolutions = (struct EvoData[]) {
        {EVOLVE_LEVEL, .lvl={21}, .species=WEEPINBELL},
        {0},
    },
    .learnset = (struct LevelMove[]) {
        {1, VINE_WHIP},
        {6, GROWTH},
        {11, WRAP},
        {15, SLEEP_POWDER},
        {17, POISONPOWDER},
        {19, STUN_SPORE},
        {23, ACID},
        {30, SWEET_SCENT},
        {37, RAZOR_LEAF},
        {45, SLAM},
        {0xff, 0},
    },
};

static const struct EvoMoves WeepinbellEvosAttacks = {
    .evolutions = (struct EvoData[]) {
        {EVOLVE_ITEM, .item={LEAF_STONE}, .species=VICTREEBEL},
        {0},
    },
    .learnset = (struct LevelMove[]) {
        {1, VINE_WHIP},
        {1, GROWTH},
        {1, WRAP},
        {6, GROWTH},
        {11, WRAP},
        {15, SLEEP_POWDER},
        {17, POISONPOWDER},
        {19, STUN_SPORE},
        {24, ACID},
        {33, SWEET_SCENT},
        {42, RAZOR_LEAF},
        {54, SLAM},
        {0xff, 0},
    },
};

static const struct EvoMoves VictreebelEvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, VINE_WHIP},
        {1, SLEEP_POWDER},
        {1, SWEET_SCENT},
        {1, RAZOR_LEAF},
        {0xff, 0},
    },
};

static const struct EvoMoves TentacoolEvosAttacks = {
    .evolutions = (struct EvoData[]) {
        {EVOLVE_LEVEL, .lvl={30}, .species=TENTACRUEL},
        {0},
    },
    .learnset = (struct LevelMove[]) {
        {1, POISON_STING},
        {6, SUPERSONIC},
        {12, CONSTRICT},
        {19, ACID},
        {25, BUBBLEBEAM},
        {30, WRAP},
        {36, BARRIER},
        {43, SCREECH},
        {49, HYDRO_PUMP},
        {0xff, 0},
    },
};

static const struct EvoMoves TentacruelEvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, POISON_STING},
        {1, SUPERSONIC},
        {1, CONSTRICT},
        {6, SUPERSONIC},
        {12, CONSTRICT},
        {19, ACID},
        {25, BUBBLEBEAM},
        {30, WRAP},
        {38, BARRIER},
        {47, SCREECH},
        {55, HYDRO_PUMP},
        {0xff, 0},
    },
};

static const struct EvoMoves GeodudeEvosAttacks = {
    .evolutions = (struct EvoData[]) {
        {EVOLVE_LEVEL, .lvl={25}, .species=GRAVELER},
        {0},
    },
    .learnset = (struct LevelMove[]) {
        {1, TACKLE},
        {6, DEFENSE_CURL},
        {11, ROCK_THROW},
        {16, MAGNITUDE},
        {21, SELFDESTRUCT},
        {26, HARDEN},
        {31, ROLLOUT},
        {36, EARTHQUAKE},
        {41, EXPLOSION},
        {0xff, 0},
    },
};

static const struct EvoMoves GravelerEvosAttacks = {
    .evolutions = (struct EvoData[]) {
        {EVOLVE_TRADE, .trade={-1}, .species=GOLEM},
        {0},
    },
    .learnset = (struct LevelMove[]) {
        {1, TACKLE},
        {1, DEFENSE_CURL},
        {1, ROCK_THROW},
        {6, DEFENSE_CURL},
        {11, ROCK_THROW},
        {16, MAGNITUDE},
        {21, SELFDESTRUCT},
        {27, HARDEN},
        {34, ROLLOUT},
        {41, EARTHQUAKE},
        {48, EXPLOSION},
        {0xff, 0},
    },
};

static const struct EvoMoves GolemEvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, TACKLE},
        {1, DEFENSE_CURL},
        {1, ROCK_THROW},
        {1, MAGNITUDE},
        {6, DEFENSE_CURL},
        {11, ROCK_THROW},
        {16, MAGNITUDE},
        {21, SELFDESTRUCT},
        {27, HARDEN},
        {34, ROLLOUT},
        {41, EARTHQUAKE},
        {48, EXPLOSION},
        {0xff, 0},
    },
};

static const struct EvoMoves PonytaEvosAttacks = {
    .evolutions = (struct EvoData[]) {
        {EVOLVE_LEVEL, .lvl={40}, .species=RAPIDASH},
        {0},
    },
    .learnset = (struct LevelMove[]) {
        {1, TACKLE},
        {4, GROWL},
        {8, TAIL_WHIP},
        {13, EMBER},
        {19, STOMP},
        {26, FIRE_SPIN},
        {34, TAKE_DOWN},
        {43, AGILITY},
        {53, FIRE_BLAST},
        {0xff, 0},
    },
};

static const struct EvoMoves RapidashEvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, TACKLE},
        {1, GROWL},
        {1, TAIL_WHIP},
        {1, EMBER},
        {4, GROWL},
        {8, TAIL_WHIP},
        {13, EMBER},
        {19, STOMP},
        {26, FIRE_SPIN},
        {34, TAKE_DOWN},
        {40, FURY_ATTACK},
        {47, AGILITY},
        {61, FIRE_BLAST},
        {0xff, 0},
    },
};

static const struct EvoMoves SlowpokeEvosAttacks = {
    .evolutions = (struct EvoData[]) {
        {EVOLVE_LEVEL, .lvl={37}, .species=SLOWBRO},
        {EVOLVE_TRADE, .trade={KINGS_ROCK}, .species=SLOWKING},
        {0},
    },
    .learnset = (struct LevelMove[]) {
        {1, CURSE},
        {1, TACKLE},
        {6, GROWL},
        {15, WATER_GUN},
        {20, CONFUSION},
        {29, DISABLE},
        {34, HEADBUTT},
        {43, AMNESIA},
        {48, PSYCHIC_M},
        {0xff, 0},
    },
};

static const struct EvoMoves SlowbroEvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, CURSE},
        {1, TACKLE},
        {1, GROWL},
        {1, WATER_GUN},
        {6, GROWL},
        {15, WATER_GUN},
        {20, CONFUSION},
        {29, DISABLE},
        {34, HEADBUTT},
        {37, WITHDRAW},
        {46, AMNESIA},
        {54, PSYCHIC_M},
        {0xff, 0},
    },
};

static const struct EvoMoves MagnemiteEvosAttacks = {
    .evolutions = (struct EvoData[]) {
        {EVOLVE_LEVEL, .lvl={30}, .species=MAGNETON},
        {0},
    },
    .learnset = (struct LevelMove[]) {
        {1, TACKLE},
        {6, THUNDERSHOCK},
        {11, SUPERSONIC},
        {16, SONICBOOM},
        {21, THUNDER_WAVE},
        {27, LOCK_ON},
        {33, SWIFT},
        {39, SCREECH},
        {45, ZAP_CANNON},
        {0xff, 0},
    },
};

static const struct EvoMoves MagnetonEvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, TACKLE},
        {1, THUNDERSHOCK},
        {1, SUPERSONIC},
        {1, SONICBOOM},
        {6, THUNDERSHOCK},
        {11, SUPERSONIC},
        {16, SONICBOOM},
        {21, THUNDER_WAVE},
        {27, LOCK_ON},
        {35, TRI_ATTACK},
        {43, SCREECH},
        {53, ZAP_CANNON},
        {0xff, 0},
    },
};

static const struct EvoMoves FarfetchDEvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, PECK},
        {7, SAND_ATTACK},
        {13, LEER},
        {19, FURY_ATTACK},
        {25, SWORDS_DANCE},
        {31, AGILITY},
        {37, SLASH},
        {44, FALSE_SWIPE},
        {0xff, 0},
    },
};

static const struct EvoMoves DoduoEvosAttacks = {
    .evolutions = (struct EvoData[]) {
        {EVOLVE_LEVEL, .lvl={31}, .species=DODRIO},
        {0},
    },
    .learnset = (struct LevelMove[]) {
        {1, PECK},
        {1, GROWL},
        {9, PURSUIT},
        {13, FURY_ATTACK},
        {21, TRI_ATTACK},
        {25, RAGE},
        {33, DRILL_PECK},
        {37, AGILITY},
        {0xff, 0},
    },
};

static const struct EvoMoves DodrioEvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, PECK},
        {1, GROWL},
        {1, PURSUIT},
        {1, FURY_ATTACK},
        {9, PURSUIT},
        {13, FURY_ATTACK},
        {21, TRI_ATTACK},
        {25, RAGE},
        {38, DRILL_PECK},
        {47, AGILITY},
        {0xff, 0},
    },
};

static const struct EvoMoves SeelEvosAttacks = {
    .evolutions = (struct EvoData[]) {
        {EVOLVE_LEVEL, .lvl={34}, .species=DEWGONG},
        {0},
    },
    .learnset = (struct LevelMove[]) {
        {1, HEADBUTT},
        {5, GROWL},
        {16, AURORA_BEAM},
        {21, REST},
        {32, TAKE_DOWN},
        {37, ICE_BEAM},
        {48, SAFEGUARD},
        {0xff, 0},
    },
};

static const struct EvoMoves DewgongEvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, HEADBUTT},
        {1, GROWL},
        {1, AURORA_BEAM},
        {5, GROWL},
        {16, AURORA_BEAM},
        {21, REST},
        {32, TAKE_DOWN},
        {43, ICE_BEAM},
        {60, SAFEGUARD},
        {0xff, 0},
    },
};

static const struct EvoMoves GrimerEvosAttacks = {
    .evolutions = (struct EvoData[]) {
        {EVOLVE_LEVEL, .lvl={38}, .species=MUK},
        {0},
    },
    .learnset = (struct LevelMove[]) {
        {1, POISON_GAS},
        {1, POUND},
        {5, HARDEN},
        {10, DISABLE},
        {16, SLUDGE},
        {23, MINIMIZE},
        {31, SCREECH},
        {40, ACID_ARMOR},
        {50, SLUDGE_BOMB},
        {0xff, 0},
    },
};

static const struct EvoMoves MukEvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, POISON_GAS},
        {1, POUND},
        {1, HARDEN},
        {33, HARDEN},
        {37, DISABLE},
        {45, SLUDGE},
        {23, MINIMIZE},
        {31, SCREECH},
        {45, ACID_ARMOR},
        {60, SLUDGE_BOMB},
        {0xff, 0},
    },
};

static const struct EvoMoves ShellderEvosAttacks = {
    .evolutions = (struct EvoData[]) {
        {EVOLVE_ITEM, .item={WATER_STONE}, .species=CLOYSTER},
        {0},
    },
    .learnset = (struct LevelMove[]) {
        {1, TACKLE},
        {1, WITHDRAW},
        {9, SUPERSONIC},
        {17, AURORA_BEAM},
        {25, PROTECT},
        {33, LEER},
        {41, CLAMP},
        {49, ICE_BEAM},
        {0xff, 0},
    },
};

static const struct EvoMoves CloysterEvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, WITHDRAW},
        {1, SUPERSONIC},
        {1, AURORA_BEAM},
        {1, PROTECT},
        {33, SPIKES},
        {41, SPIKE_CANNON},
        {0xff, 0},
    },
};

static const struct EvoMoves GastlyEvosAttacks = {
    .evolutions = (struct EvoData[]) {
        {EVOLVE_LEVEL, .lvl={25}, .species=HAUNTER},
        {0},
    },
    .learnset = (struct LevelMove[]) {
        {1, HYPNOSIS},
        {1, LICK},
        {8, SPITE},
        {13, MEAN_LOOK},
        {16, CURSE},
        {21, NIGHT_SHADE},
        {28, CONFUSE_RAY},
        {33, DREAM_EATER},
        {36, DESTINY_BOND},
        {0xff, 0},
    },
};

static const struct EvoMoves HaunterEvosAttacks = {
    .evolutions = (struct EvoData[]) {
        {EVOLVE_TRADE, .trade={-1}, .species=GENGAR},
        {0},
    },
    .learnset = (struct LevelMove[]) {
        {1, HYPNOSIS},
        {1, LICK},
        {1, SPITE},
        {8, SPITE},
        {13, MEAN_LOOK},
        {16, CURSE},
        {21, NIGHT_SHADE},
        {31, CONFUSE_RAY},
        {39, DREAM_EATER},
        {48, DESTINY_BOND},
        {0xff, 0},
    },
};

static const struct EvoMoves GengarEvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, HYPNOSIS},
        {1, LICK},
        {1, SPITE},
        {8, SPITE},
        {13, MEAN_LOOK},
        {16, CURSE},
        {21, NIGHT_SHADE},
        {31, CONFUSE_RAY},
        {39, DREAM_EATER},
        {48, DESTINY_BOND},
        {0xff, 0},
    },
};

static const struct EvoMoves OnixEvosAttacks = {
    .evolutions = (struct EvoData[]) {
        {EVOLVE_TRADE, .trade={METAL_COAT}, .species=STEELIX},
        {0},
    },
    .learnset = (struct LevelMove[]) {
        {1, TACKLE},
        {1, SCREECH},
        {10, BIND},
        {14, ROCK_THROW},
        {23, HARDEN},
        {27, RAGE},
        {36, SANDSTORM},
        {40, SLAM},
        {0xff, 0},
    },
};

static const struct EvoMoves DrowzeeEvosAttacks = {
    .evolutions = (struct EvoData[]) {
        {EVOLVE_LEVEL, .lvl={26}, .species=HYPNO},
        {0},
    },
    .learnset = (struct LevelMove[]) {
        {1, POUND},
        {1, HYPNOSIS},
        {10, DISABLE},
        {18, CONFUSION},
        {25, HEADBUTT},
        {31, POISON_GAS},
        {36, MEDITATE},
        {40, PSYCHIC_M},
        {43, PSYCH_UP},
        {45, FUTURE_SIGHT},
        {0xff, 0},
    },
};

static const struct EvoMoves HypnoEvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, POUND},
        {1, HYPNOSIS},
        {1, DISABLE},
        {1, CONFUSION},
        {10, DISABLE},
        {18, CONFUSION},
        {25, HEADBUTT},
        {33, POISON_GAS},
        {40, MEDITATE},
        {49, PSYCHIC_M},
        {55, PSYCH_UP},
        {60, FUTURE_SIGHT},
        {0xff, 0},
    },
};

static const struct EvoMoves KrabbyEvosAttacks = {
    .evolutions = (struct EvoData[]) {
        {EVOLVE_LEVEL, .lvl={28}, .species=KINGLER},
        {0},
    },
    .learnset = (struct LevelMove[]) {
        {1, BUBBLE},
        {5, LEER},
        {12, VICEGRIP},
        {16, HARDEN},
        {23, STOMP},
        {27, GUILLOTINE},
        {34, PROTECT},
        {41, CRABHAMMER},
        {0xff, 0},
    },
};

static const struct EvoMoves KinglerEvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, BUBBLE},
        {1, LEER},
        {1, VICEGRIP},
        {5, LEER},
        {12, VICEGRIP},
        {16, HARDEN},
        {23, STOMP},
        {27, GUILLOTINE},
        {38, PROTECT},
        {49, CRABHAMMER},
        {0xff, 0},
    },
};

static const struct EvoMoves VoltorbEvosAttacks = {
    .evolutions = (struct EvoData[]) {
        {EVOLVE_LEVEL, .lvl={30}, .species=ELECTRODE},
        {0},
    },
    .learnset = (struct LevelMove[]) {
        {1, TACKLE},
        {9, SCREECH},
        {17, SONICBOOM},
        {23, SELFDESTRUCT},
        {29, ROLLOUT},
        {33, LIGHT_SCREEN},
        {37, SWIFT},
        {39, EXPLOSION},
        {41, MIRROR_COAT},
        {0xff, 0},
    },
};

static const struct EvoMoves ElectrodeEvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, TACKLE},
        {1, SCREECH},
        {1, SONICBOOM},
        {1, SELFDESTRUCT},
        {9, SCREECH},
        {17, SONICBOOM},
        {23, SELFDESTRUCT},
        {29, ROLLOUT},
        {34, LIGHT_SCREEN},
        {40, SWIFT},
        {44, EXPLOSION},
        {48, MIRROR_COAT},
        {0xff, 0},
    },
};

static const struct EvoMoves ExeggcuteEvosAttacks = {
    .evolutions = (struct EvoData[]) {
        {EVOLVE_ITEM, .item={LEAF_STONE}, .species=EXEGGUTOR},
        {0},
    },
    .learnset = (struct LevelMove[]) {
        {1, BARRAGE},
        {1, HYPNOSIS},
        {7, REFLECT},
        {13, LEECH_SEED},
        {19, CONFUSION},
        {25, STUN_SPORE},
        {31, POISONPOWDER},
        {37, SLEEP_POWDER},
        {43, SOLARBEAM},
        {0xff, 0},
    },
};

static const struct EvoMoves ExeggutorEvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, BARRAGE},
        {1, HYPNOSIS},
        {1, CONFUSION},
        {19, STOMP},
        {31, EGG_BOMB},
        {0xff, 0},
    },
};

static const struct EvoMoves CuboneEvosAttacks = {
    .evolutions = (struct EvoData[]) {
        {EVOLVE_LEVEL, .lvl={28}, .species=MAROWAK},
        {0},
    },
    .learnset = (struct LevelMove[]) {
        {1, GROWL},
        {5, TAIL_WHIP},
        {9, BONE_CLUB},
        {13, HEADBUTT},
        {17, LEER},
        {21, FOCUS_ENERGY},
        {25, BONEMERANG},
        {29, RAGE},
        {33, FALSE_SWIPE},
        {37, THRASH},
        {41, BONE_RUSH},
        {0xff, 0},
    },
};

static const struct EvoMoves MarowakEvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, GROWL},
        {1, TAIL_WHIP},
        {1, BONE_CLUB},
        {1, HEADBUTT},
        {5, TAIL_WHIP},
        {9, BONE_CLUB},
        {13, HEADBUTT},
        {17, LEER},
        {21, FOCUS_ENERGY},
        {25, BONEMERANG},
        {32, RAGE},
        {39, FALSE_SWIPE},
        {46, THRASH},
        {53, BONE_RUSH},
        {0xff, 0},
    },
};

static const struct EvoMoves HitmonleeEvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, DOUBLE_KICK},
        {6, MEDITATE},
        {11, ROLLING_KICK},
        {16, JUMP_KICK},
        {21, FOCUS_ENERGY},
        {26, HI_JUMP_KICK},
        {31, MIND_READER},
        {36, FORESIGHT},
        {41, ENDURE},
        {46, MEGA_KICK},
        {51, REVERSAL},
        {0xff, 0},
    },
};

static const struct EvoMoves HitmonchanEvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, COMET_PUNCH},
        {7, AGILITY},
        {13, PURSUIT},
        {26, THUNDERPUNCH},
        {26, ICE_PUNCH},
        {26, FIRE_PUNCH},
        {32, MACH_PUNCH},
        {38, MEGA_PUNCH},
        {44, DETECT},
        {50, COUNTER},
        {0xff, 0},
    },
};

static const struct EvoMoves LickitungEvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, LICK},
        {7, SUPERSONIC},
        {13, DEFENSE_CURL},
        {19, STOMP},
        {25, WRAP},
        {31, DISABLE},
        {37, SLAM},
        {43, SCREECH},
        {0xff, 0},
    },
};

static const struct EvoMoves KoffingEvosAttacks = {
    .evolutions = (struct EvoData[]) {
        {EVOLVE_LEVEL, .lvl={35}, .species=WEEZING},
        {0},
    },
    .learnset = (struct LevelMove[]) {
        {1, POISON_GAS},
        {1, TACKLE},
        {9, SMOG},
        {17, SELFDESTRUCT},
        {21, SLUDGE},
        {25, SMOKESCREEN},
        {33, HAZE},
        {41, EXPLOSION},
        {45, DESTINY_BOND},
        {0xff, 0},
    },
};

static const struct EvoMoves WeezingEvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, POISON_GAS},
        {1, TACKLE},
        {1, SMOG},
        {1, SELFDESTRUCT},
        {9, SMOG},
        {17, SELFDESTRUCT},
        {21, SLUDGE},
        {25, SMOKESCREEN},
        {33, HAZE},
        {44, EXPLOSION},
        {51, DESTINY_BOND},
        {0xff, 0},
    },
};

static const struct EvoMoves RhyhornEvosAttacks = {
    .evolutions = (struct EvoData[]) {
        {EVOLVE_LEVEL, .lvl={42}, .species=RHYDON},
        {0},
    },
    .learnset = (struct LevelMove[]) {
        {1, HORN_ATTACK},
        {1, TAIL_WHIP},
        {13, STOMP},
        {19, FURY_ATTACK},
        {31, SCARY_FACE},
        {37, HORN_DRILL},
        {49, TAKE_DOWN},
        {55, EARTHQUAKE},
        {0xff, 0},
    },
};

static const struct EvoMoves RhydonEvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, HORN_ATTACK},
        {1, TAIL_WHIP},
        {1, STOMP},
        {1, FURY_ATTACK},
        {13, STOMP},
        {19, FURY_ATTACK},
        {31, SCARY_FACE},
        {37, HORN_DRILL},
        {54, TAKE_DOWN},
        {65, EARTHQUAKE},
        {0xff, 0},
    },
};

static const struct EvoMoves ChanseyEvosAttacks = {
    .evolutions = (struct EvoData[]) {
        {EVOLVE_HAPPINESS, .happiness={TR_ANYTIME}, .species=BLISSEY},
        {0},
    },
    .learnset = (struct LevelMove[]) {
        {1, POUND},
        {5, GROWL},
        {9, TAIL_WHIP},
        {13, SOFTBOILED},
        {17, DOUBLESLAP},
        {23, MINIMIZE},
        {29, SING},
        {35, EGG_BOMB},
        {41, DEFENSE_CURL},
        {49, LIGHT_SCREEN},
        {57, DOUBLE_EDGE},
        {0xff, 0},
    },
};

static const struct EvoMoves TangelaEvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, CONSTRICT},
        {4, SLEEP_POWDER},
        {10, ABSORB},
        {13, POISONPOWDER},
        {19, VINE_WHIP},
        {25, BIND},
        {31, MEGA_DRAIN},
        {34, STUN_SPORE},
        {40, SLAM},
        {46, GROWTH},
        {0xff, 0},
    },
};

static const struct EvoMoves KangaskhanEvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, COMET_PUNCH},
        {7, LEER},
        {13, BITE},
        {19, TAIL_WHIP},
        {25, MEGA_PUNCH},
        {31, RAGE},
        {37, ENDURE},
        {43, DIZZY_PUNCH},
        {49, REVERSAL},
        {0xff, 0},
    },
};

static const struct EvoMoves HorseaEvosAttacks = {
    .evolutions = (struct EvoData[]) {
        {EVOLVE_LEVEL, .lvl={32}, .species=SEADRA},
        {0},
    },
    .learnset = (struct LevelMove[]) {
        {1, BUBBLE},
        {8, SMOKESCREEN},
        {15, LEER},
        {22, WATER_GUN},
        {29, TWISTER},
        {36, AGILITY},
        {43, HYDRO_PUMP},
        {0xff, 0},
    },
};

static const struct EvoMoves SeadraEvosAttacks = {
    .evolutions = (struct EvoData[]) {
        {EVOLVE_TRADE, .trade={DRAGON_SCALE}, .species=KINGDRA},
        {0},
    },
    .learnset = (struct LevelMove[]) {
        {1, BUBBLE},
        {1, SMOKESCREEN},
        {1, LEER},
        {1, WATER_GUN},
        {8, SMOKESCREEN},
        {15, LEER},
        {22, WATER_GUN},
        {29, TWISTER},
        {40, AGILITY},
        {51, HYDRO_PUMP},
        {0xff, 0},
    },
};

static const struct EvoMoves GoldeenEvosAttacks = {
    .evolutions = (struct EvoData[]) {
        {EVOLVE_LEVEL, .lvl={33}, .species=SEAKING},
        {0},
    },
    .learnset = (struct LevelMove[]) {
        {1, PECK},
        {1, TAIL_WHIP},
        {10, SUPERSONIC},
        {15, HORN_ATTACK},
        {24, FLAIL},
        {29, FURY_ATTACK},
        {38, WATERFALL},
        {43, HORN_DRILL},
        {52, AGILITY},
        {0xff, 0},
    },
};

static const struct EvoMoves SeakingEvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, PECK},
        {1, TAIL_WHIP},
        {1, TAIL_WHIP},
        {10, SUPERSONIC},
        {15, HORN_ATTACK},
        {24, FLAIL},
        {29, FURY_ATTACK},
        {41, WATERFALL},
        {49, HORN_DRILL},
        {61, AGILITY},
        {0xff, 0},
    },
};

static const struct EvoMoves StaryuEvosAttacks = {
    .evolutions = (struct EvoData[]) {
        {EVOLVE_ITEM, .item={WATER_STONE}, .species=STARMIE},
        {0},
    },
    .learnset = (struct LevelMove[]) {
        {1, TACKLE},
        {1, HARDEN},
        {7, WATER_GUN},
        {13, RAPID_SPIN},
        {19, RECOVER},
        {25, SWIFT},
        {31, BUBBLEBEAM},
        {37, MINIMIZE},
        {43, LIGHT_SCREEN},
        {50, HYDRO_PUMP},
        {0xff, 0},
    },
};

static const struct EvoMoves StarmieEvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, TACKLE},
        {1, RAPID_SPIN},
        {1, RECOVER},
        {1, BUBBLEBEAM},
        {37, CONFUSE_RAY},
        {0xff, 0},
    },
};

static const struct EvoMoves MrMimeEvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, BARRIER},
        {6, CONFUSION},
        {11, SUBSTITUTE},
        {16, MEDITATE},
        {21, DOUBLESLAP},
        {26, LIGHT_SCREEN},
        {26, REFLECT},
        {31, ENCORE},
        {36, PSYBEAM},
        {41, BATON_PASS},
        {46, SAFEGUARD},
        {0xff, 0},
    },
};

static const struct EvoMoves ScytherEvosAttacks = {
    .evolutions = (struct EvoData[]) {
        {EVOLVE_TRADE, .trade={METAL_COAT}, .species=SCIZOR},
        {0},
    },
    .learnset = (struct LevelMove[]) {
        {1, QUICK_ATTACK},
        {1, LEER},
        {6, FOCUS_ENERGY},
        {12, PURSUIT},
        {18, FALSE_SWIPE},
        {24, AGILITY},
        {30, WING_ATTACK},
        {36, SLASH},
        {42, SWORDS_DANCE},
        {48, DOUBLE_TEAM},
        {0xff, 0},
    },
};

static const struct EvoMoves JynxEvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, POUND},
        {1, LICK},
        {1, LOVELY_KISS},
        {1, POWDER_SNOW},
        {9, LOVELY_KISS},
        {13, POWDER_SNOW},
        {21, DOUBLESLAP},
        {25, ICE_PUNCH},
        {35, MEAN_LOOK},
        {41, BODY_SLAM},
        {51, PERISH_SONG},
        {57, BLIZZARD},
        {0xff, 0},
    },
};

static const struct EvoMoves ElectabuzzEvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, QUICK_ATTACK},
        {1, LEER},
        {1, THUNDERPUNCH},
        {9, THUNDERPUNCH},
        {17, LIGHT_SCREEN},
        {25, SWIFT},
        {36, SCREECH},
        {47, THUNDERBOLT},
        {58, THUNDER},
        {0xff, 0},
    },
};

static const struct EvoMoves MagmarEvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, EMBER},
        {1, LEER},
        {1, SMOG},
        {1, FIRE_PUNCH},
        {7, LEER},
        {13, SMOG},
        {19, FIRE_PUNCH},
        {25, SMOKESCREEN},
        {33, SUNNY_DAY},
        {41, FLAMETHROWER},
        {49, CONFUSE_RAY},
        {57, FIRE_BLAST},
        {0xff, 0},
    },
};

static const struct EvoMoves PinsirEvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, VICEGRIP},
        {7, FOCUS_ENERGY},
        {13, BIND},
        {19, SEISMIC_TOSS},
        {25, HARDEN},
        {31, GUILLOTINE},
        {37, SUBMISSION},
        {43, SWORDS_DANCE},
        {0xff, 0},
    },
};

static const struct EvoMoves TaurosEvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, TACKLE},
        {4, TAIL_WHIP},
        {8, RAGE},
        {13, HORN_ATTACK},
        {19, SCARY_FACE},
        {26, PURSUIT},
        {34, REST},
        {43, THRASH},
        {53, TAKE_DOWN},
        {0xff, 0},
    },
};

static const struct EvoMoves MagikarpEvosAttacks = {
    .evolutions = (struct EvoData[]) {
        {EVOLVE_LEVEL, .lvl={20}, .species=GYARADOS},
        {0},
    },
    .learnset = (struct LevelMove[]) {
        {1, SPLASH},
        {15, TACKLE},
        {30, FLAIL},
        {0xff, 0},
    },
};

static const struct EvoMoves GyaradosEvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, THRASH},
        {20, BITE},
        {25, DRAGON_RAGE},
        {30, LEER},
        {35, TWISTER},
        {40, HYDRO_PUMP},
        {45, RAIN_DANCE},
        {50, HYPER_BEAM},
        {0xff, 0},
    },
};

static const struct EvoMoves LaprasEvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, WATER_GUN},
        {1, GROWL},
        {1, SING},
        {8, MIST},
        {15, BODY_SLAM},
        {22, CONFUSE_RAY},
        {29, PERISH_SONG},
        {36, ICE_BEAM},
        {43, RAIN_DANCE},
        {50, SAFEGUARD},
        {57, HYDRO_PUMP},
        {0xff, 0},
    },
};

static const struct EvoMoves DittoEvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, TRANSFORM},
        {0xff, 0},
    },
};

static const struct EvoMoves EeveeEvosAttacks = {
    .evolutions = (struct EvoData[]) {
        {EVOLVE_ITEM, .item={THUNDERSTONE}, .species=JOLTEON},
        {EVOLVE_ITEM, .item={WATER_STONE}, .species=VAPOREON},
        {EVOLVE_ITEM, .item={FIRE_STONE}, .species=FLAREON},
        {EVOLVE_HAPPINESS, .happiness={TR_MORNDAY}, .species=ESPEON},
        {EVOLVE_HAPPINESS, .happiness={TR_NITE}, .species=UMBREON},
        {0},
    },
    .learnset = (struct LevelMove[]) {
        {1, TACKLE},
        {1, TAIL_WHIP},
        {8, SAND_ATTACK},
        {16, GROWL},
        {23, QUICK_ATTACK},
        {30, BITE},
        {36, BATON_PASS},
        {42, TAKE_DOWN},
        {0xff, 0},
    },
};

static const struct EvoMoves VaporeonEvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, TACKLE},
        {1, TAIL_WHIP},
        {8, SAND_ATTACK},
        {16, WATER_GUN},
        {23, QUICK_ATTACK},
        {30, BITE},
        {36, AURORA_BEAM},
        {42, HAZE},
        {47, ACID_ARMOR},
        {52, HYDRO_PUMP},
        {0xff, 0},
    },
};

static const struct EvoMoves JolteonEvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, TACKLE},
        {1, TAIL_WHIP},
        {8, SAND_ATTACK},
        {16, THUNDERSHOCK},
        {23, QUICK_ATTACK},
        {30, DOUBLE_KICK},
        {36, PIN_MISSILE},
        {42, THUNDER_WAVE},
        {47, AGILITY},
        {52, THUNDER},
        {0xff, 0},
    },
};

static const struct EvoMoves FlareonEvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, TACKLE},
        {1, TAIL_WHIP},
        {8, SAND_ATTACK},
        {16, EMBER},
        {23, QUICK_ATTACK},
        {30, BITE},
        {36, FIRE_SPIN},
        {42, SMOG},
        {47, LEER},
        {52, FLAMETHROWER},
        {0xff, 0},
    },
};

static const struct EvoMoves PorygonEvosAttacks = {
    .evolutions = (struct EvoData[]) {
        {EVOLVE_TRADE, .trade={UP_GRADE}, .species=PORYGON2},
        {0},
    },
    .learnset = (struct LevelMove[]) {
        {1, CONVERSION2},
        {1, TACKLE},
        {1, CONVERSION},
        {9, AGILITY},
        {12, PSYBEAM},
        {20, RECOVER},
        {24, SHARPEN},
        {32, LOCK_ON},
        {36, TRI_ATTACK},
        {44, ZAP_CANNON},
        {0xff, 0},
    },
};

static const struct EvoMoves OmanyteEvosAttacks = {
    .evolutions = (struct EvoData[]) {
        {EVOLVE_LEVEL, .lvl={40}, .species=OMASTAR},
        {0},
    },
    .learnset = (struct LevelMove[]) {
        {1, CONSTRICT},
        {1, WITHDRAW},
        {13, BITE},
        {19, WATER_GUN},
        {31, LEER},
        {37, PROTECT},
        {49, ANCIENTPOWER},
        {55, HYDRO_PUMP},
        {0xff, 0},
    },
};

static const struct EvoMoves OmastarEvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, CONSTRICT},
        {1, WITHDRAW},
        {1, BITE},
        {13, BITE},
        {19, WATER_GUN},
        {31, LEER},
        {37, PROTECT},
        {40, SPIKE_CANNON},
        {54, ANCIENTPOWER},
        {65, HYDRO_PUMP},
        {0xff, 0},
    },
};

static const struct EvoMoves KabutoEvosAttacks = {
    .evolutions = (struct EvoData[]) {
        {EVOLVE_LEVEL, .lvl={40}, .species=KABUTOPS},
        {0},
    },
    .learnset = (struct LevelMove[]) {
        {1, SCRATCH},
        {1, HARDEN},
        {10, ABSORB},
        {19, LEER},
        {28, SAND_ATTACK},
        {37, ENDURE},
        {46, MEGA_DRAIN},
        {55, ANCIENTPOWER},
        {0xff, 0},
    },
};

static const struct EvoMoves KabutopsEvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, SCRATCH},
        {1, HARDEN},
        {1, ABSORB},
        {10, ABSORB},
        {19, LEER},
        {28, SAND_ATTACK},
        {37, ENDURE},
        {40, SLASH},
        {51, MEGA_DRAIN},
        {65, ANCIENTPOWER},
        {0xff, 0},
    },
};

static const struct EvoMoves AerodactylEvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, WING_ATTACK},
        {8, AGILITY},
        {15, BITE},
        {22, SUPERSONIC},
        {29, ANCIENTPOWER},
        {36, SCARY_FACE},
        {43, TAKE_DOWN},
        {50, HYPER_BEAM},
        {0xff, 0},
    },
};

static const struct EvoMoves SnorlaxEvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, TACKLE},
        {8, AMNESIA},
        {15, DEFENSE_CURL},
        {22, BELLY_DRUM},
        {29, HEADBUTT},
        {36, SNORE},
        {36, REST},
        {43, BODY_SLAM},
        {50, ROLLOUT},
        {57, HYPER_BEAM},
        {0xff, 0},
    },
};

static const struct EvoMoves ArticunoEvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, GUST},
        {1, POWDER_SNOW},
        {13, MIST},
        {25, AGILITY},
        {37, MIND_READER},
        {49, ICE_BEAM},
        {61, REFLECT},
        {73, BLIZZARD},
        {0xff, 0},
    },
};

static const struct EvoMoves ZapdosEvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, PECK},
        {1, THUNDERSHOCK},
        {13, THUNDER_WAVE},
        {25, AGILITY},
        {37, DETECT},
        {49, DRILL_PECK},
        {61, LIGHT_SCREEN},
        {73, THUNDER},
        {0xff, 0},
    },
};

static const struct EvoMoves MoltresEvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, WING_ATTACK},
        {1, EMBER},
        {13, FIRE_SPIN},
        {25, AGILITY},
        {37, ENDURE},
        {49, FLAMETHROWER},
        {61, SAFEGUARD},
        {73, SKY_ATTACK},
        {0xff, 0},
    },
};

static const struct EvoMoves DratiniEvosAttacks = {
    .evolutions = (struct EvoData[]) {
        {EVOLVE_LEVEL, .lvl={30}, .species=DRAGONAIR},
        {0},
    },
    .learnset = (struct LevelMove[]) {
        {1, WRAP},
        {1, LEER},
        {8, THUNDER_WAVE},
        {15, TWISTER},
        {22, DRAGON_RAGE},
        {29, SLAM},
        {36, AGILITY},
        {43, SAFEGUARD},
        {50, OUTRAGE},
        {57, HYPER_BEAM},
        {0xff, 0},
    },
};

static const struct EvoMoves DragonairEvosAttacks = {
    .evolutions = (struct EvoData[]) {
        {EVOLVE_LEVEL, .lvl={55}, .species=DRAGONITE},
        {0},
    },
    .learnset = (struct LevelMove[]) {
        {1, WRAP},
        {1, LEER},
        {1, THUNDER_WAVE},
        {1, TWISTER},
        {8, THUNDER_WAVE},
        {15, TWISTER},
        {22, DRAGON_RAGE},
        {29, SLAM},
        {38, AGILITY},
        {47, SAFEGUARD},
        {56, OUTRAGE},
        {65, HYPER_BEAM},
        {0xff, 0},
    },
};

static const struct EvoMoves DragoniteEvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, WRAP},
        {1, LEER},
        {1, THUNDER_WAVE},
        {1, TWISTER},
        {8, THUNDER_WAVE},
        {15, TWISTER},
        {22, DRAGON_RAGE},
        {29, SLAM},
        {38, AGILITY},
        {47, SAFEGUARD},
        {55, WING_ATTACK},
        {61, OUTRAGE},
        {75, HYPER_BEAM},
        {0xff, 0},
    },
};

static const struct EvoMoves MewtwoEvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, CONFUSION},
        {1, DISABLE},
        {11, BARRIER},
        {22, SWIFT},
        {33, PSYCH_UP},
        {44, FUTURE_SIGHT},
        {55, MIST},
        {66, PSYCHIC_M},
        {77, AMNESIA},
        {88, RECOVER},
        {99, SAFEGUARD},
        {0xff, 0},
    },
};

static const struct EvoMoves MewEvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, POUND},
        {10, TRANSFORM},
        {20, MEGA_PUNCH},
        {30, METRONOME},
        {40, PSYCHIC_M},
        {50, ANCIENTPOWER},
        {0xff, 0},
    },
};

static const struct EvoMoves ChikoritaEvosAttacks = {
    .evolutions = (struct EvoData[]) {
        {EVOLVE_LEVEL, .lvl={16}, .species=BAYLEEF},
        {0},
    },
    .learnset = (struct LevelMove[]) {
        {1, TACKLE},
        {1, GROWL},
        {8, RAZOR_LEAF},
        {12, REFLECT},
        {15, POISONPOWDER},
        {22, SYNTHESIS},
        {29, BODY_SLAM},
        {36, LIGHT_SCREEN},
        {43, SAFEGUARD},
        {50, SOLARBEAM},
        {0xff, 0},
    },
};

static const struct EvoMoves BayleefEvosAttacks = {
    .evolutions = (struct EvoData[]) {
        {EVOLVE_LEVEL, .lvl={32}, .species=MEGANIUM},
        {0},
    },
    .learnset = (struct LevelMove[]) {
        {1, TACKLE},
        {1, GROWL},
        {1, RAZOR_LEAF},
        {1, REFLECT},
        {8, RAZOR_LEAF},
        {12, REFLECT},
        {15, POISONPOWDER},
        {23, SYNTHESIS},
        {31, BODY_SLAM},
        {39, LIGHT_SCREEN},
        {47, SAFEGUARD},
        {55, SOLARBEAM},
        {0xff, 0},
    },
};

static const struct EvoMoves MeganiumEvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, TACKLE},
        {1, GROWL},
        {1, RAZOR_LEAF},
        {1, REFLECT},
        {8, RAZOR_LEAF},
        {12, REFLECT},
        {15, POISONPOWDER},
        {23, SYNTHESIS},
        {31, BODY_SLAM},
        {41, LIGHT_SCREEN},
        {51, SAFEGUARD},
        {61, SOLARBEAM},
        {0xff, 0},
    },
};

static const struct EvoMoves CyndaquilEvosAttacks = {
    .evolutions = (struct EvoData[]) {
        {EVOLVE_LEVEL, .lvl={14}, .species=QUILAVA},
        {0},
    },
    .learnset = (struct LevelMove[]) {
        {1, TACKLE},
        {1, LEER},
        {6, SMOKESCREEN},
        {12, EMBER},
        {19, QUICK_ATTACK},
        {27, FLAME_WHEEL},
        {36, SWIFT},
        {46, FLAMETHROWER},
        {0xff, 0},
    },
};

static const struct EvoMoves QuilavaEvosAttacks = {
    .evolutions = (struct EvoData[]) {
        {EVOLVE_LEVEL, .lvl={36}, .species=TYPHLOSION},
        {0},
    },
    .learnset = (struct LevelMove[]) {
        {1, TACKLE},
        {1, LEER},
        {1, SMOKESCREEN},
        {6, SMOKESCREEN},
        {12, EMBER},
        {21, QUICK_ATTACK},
        {31, FLAME_WHEEL},
        {42, SWIFT},
        {54, FLAMETHROWER},
        {0xff, 0},
    },
};

static const struct EvoMoves TyphlosionEvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, TACKLE},
        {1, LEER},
        {1, SMOKESCREEN},
        {1, EMBER},
        {6, SMOKESCREEN},
        {12, EMBER},
        {21, QUICK_ATTACK},
        {31, FLAME_WHEEL},
        {45, SWIFT},
        {60, FLAMETHROWER},
        {0xff, 0},
    },
};

static const struct EvoMoves TotodileEvosAttacks = {
    .evolutions = (struct EvoData[]) {
        {EVOLVE_LEVEL, .lvl={18}, .species=CROCONAW},
        {0},
    },
    .learnset = (struct LevelMove[]) {
        {1, SCRATCH},
        {1, LEER},
        {7, RAGE},
        {13, WATER_GUN},
        {20, BITE},
        {27, SCARY_FACE},
        {35, SLASH},
        {43, SCREECH},
        {52, HYDRO_PUMP},
        {0xff, 0},
    },
};

static const struct EvoMoves CroconawEvosAttacks = {
    .evolutions = (struct EvoData[]) {
        {EVOLVE_LEVEL, .lvl={30}, .species=FERALIGATR},
        {0},
    },
    .learnset = (struct LevelMove[]) {
        {1, SCRATCH},
        {1, LEER},
        {1, RAGE},
        {7, RAGE},
        {13, WATER_GUN},
        {21, BITE},
        {28, SCARY_FACE},
        {37, SLASH},
        {45, SCREECH},
        {55, HYDRO_PUMP},
        {0xff, 0},
    },
};

static const struct EvoMoves FeraligatrEvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, SCRATCH},
        {1, LEER},
        {1, RAGE},
        {1, WATER_GUN},
        {7, RAGE},
        {13, WATER_GUN},
        {21, BITE},
        {28, SCARY_FACE},
        {38, SLASH},
        {47, SCREECH},
        {58, HYDRO_PUMP},
        {0xff, 0},
    },
};

static const struct EvoMoves SentretEvosAttacks = {
    .evolutions = (struct EvoData[]) {
        {EVOLVE_LEVEL, .lvl={15}, .species=FURRET},
        {0},
    },
    .learnset = (struct LevelMove[]) {
        {1, TACKLE},
        {5, DEFENSE_CURL},
        {11, QUICK_ATTACK},
        {17, FURY_SWIPES},
        {25, SLAM},
        {33, REST},
        {41, AMNESIA},
        {0xff, 0},
    },
};

static const struct EvoMoves FurretEvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, SCRATCH},
        {1, DEFENSE_CURL},
        {1, QUICK_ATTACK},
        {5, DEFENSE_CURL},
        {11, QUICK_ATTACK},
        {18, FURY_SWIPES},
        {28, SLAM},
        {38, REST},
        {48, AMNESIA},
        {0xff, 0},
    },
};

static const struct EvoMoves HoothootEvosAttacks = {
    .evolutions = (struct EvoData[]) {
        {EVOLVE_LEVEL, .lvl={20}, .species=NOCTOWL},
        {0},
    },
    .learnset = (struct LevelMove[]) {
        {1, TACKLE},
        {1, GROWL},
        {6, FORESIGHT},
        {11, PECK},
        {16, HYPNOSIS},
        {22, REFLECT},
        {28, TAKE_DOWN},
        {34, CONFUSION},
        {48, DREAM_EATER},
        {0xff, 0},
    },
};

static const struct EvoMoves NoctowlEvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, TACKLE},
        {1, GROWL},
        {1, FORESIGHT},
        {1, PECK},
        {6, FORESIGHT},
        {11, PECK},
        {16, HYPNOSIS},
        {25, REFLECT},
        {33, TAKE_DOWN},
        {41, CONFUSION},
        {57, DREAM_EATER},
        {0xff, 0},
    },
};

static const struct EvoMoves LedybaEvosAttacks = {
    .evolutions = (struct EvoData[]) {
        {EVOLVE_LEVEL, .lvl={18}, .species=LEDIAN},
        {0},
    },
    .learnset = (struct LevelMove[]) {
        {1, TACKLE},
        {8, SUPERSONIC},
        {15, COMET_PUNCH},
        {22, LIGHT_SCREEN},
        {22, REFLECT},
        {22, SAFEGUARD},
        {29, BATON_PASS},
        {36, SWIFT},
        {43, AGILITY},
        {50, DOUBLE_EDGE},
        {0xff, 0},
    },
};

static const struct EvoMoves LedianEvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, TACKLE},
        {1, SUPERSONIC},
        {8, SUPERSONIC},
        {15, COMET_PUNCH},
        {24, LIGHT_SCREEN},
        {24, REFLECT},
        {24, SAFEGUARD},
        {33, BATON_PASS},
        {42, SWIFT},
        {51, AGILITY},
        {60, DOUBLE_EDGE},
        {0xff, 0},
    },
};

static const struct EvoMoves SpinarakEvosAttacks = {
    .evolutions = (struct EvoData[]) {
        {EVOLVE_LEVEL, .lvl={22}, .species=ARIADOS},
        {0},
    },
    .learnset = (struct LevelMove[]) {
        {1, POISON_STING},
        {1, STRING_SHOT},
        {6, SCARY_FACE},
        {11, CONSTRICT},
        {17, NIGHT_SHADE},
        {23, LEECH_LIFE},
        {30, FURY_SWIPES},
        {37, SPIDER_WEB},
        {45, AGILITY},
        {53, PSYCHIC_M},
        {0xff, 0},
    },
};

static const struct EvoMoves AriadosEvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, POISON_STING},
        {1, STRING_SHOT},
        {1, SCARY_FACE},
        {1, CONSTRICT},
        {6, SCARY_FACE},
        {11, CONSTRICT},
        {17, NIGHT_SHADE},
        {25, LEECH_LIFE},
        {34, FURY_SWIPES},
        {43, SPIDER_WEB},
        {53, AGILITY},
        {63, PSYCHIC_M},
        {0xff, 0},
    },
};

static const struct EvoMoves CrobatEvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, SCREECH},
        {1, LEECH_LIFE},
        {1, SUPERSONIC},
        {6, SUPERSONIC},
        {12, BITE},
        {19, CONFUSE_RAY},
        {30, WING_ATTACK},
        {42, MEAN_LOOK},
        {55, HAZE},
        {0xff, 0},
    },
};

static const struct EvoMoves ChinchouEvosAttacks = {
    .evolutions = (struct EvoData[]) {
        {EVOLVE_LEVEL, .lvl={27}, .species=LANTURN},
        {0},
    },
    .learnset = (struct LevelMove[]) {
        {1, BUBBLE},
        {1, THUNDER_WAVE},
        {5, SUPERSONIC},
        {13, FLAIL},
        {17, WATER_GUN},
        {25, SPARK},
        {29, CONFUSE_RAY},
        {37, TAKE_DOWN},
        {41, HYDRO_PUMP},
        {0xff, 0},
    },
};

static const struct EvoMoves LanturnEvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, BUBBLE},
        {1, THUNDER_WAVE},
        {1, SUPERSONIC},
        {5, SUPERSONIC},
        {13, FLAIL},
        {17, WATER_GUN},
        {25, SPARK},
        {33, CONFUSE_RAY},
        {45, TAKE_DOWN},
        {53, HYDRO_PUMP},
        {0xff, 0},
    },
};

static const struct EvoMoves PichuEvosAttacks = {
    .evolutions = (struct EvoData[]) {
        {EVOLVE_HAPPINESS, .happiness={TR_ANYTIME}, .species=PIKACHU},
        {0},
    },
    .learnset = (struct LevelMove[]) {
        {1, THUNDERSHOCK},
        {1, CHARM},
        {6, TAIL_WHIP},
        {8, THUNDER_WAVE},
        {11, SWEET_KISS},
        {0xff, 0},
    },
};

static const struct EvoMoves CleffaEvosAttacks = {
    .evolutions = (struct EvoData[]) {
        {EVOLVE_HAPPINESS, .happiness={TR_ANYTIME}, .species=CLEFAIRY},
        {0},
    },
    .learnset = (struct LevelMove[]) {
        {1, POUND},
        {1, CHARM},
        {4, ENCORE},
        {8, SING},
        {13, SWEET_KISS},
        {0xff, 0},
    },
};

static const struct EvoMoves IgglybuffEvosAttacks = {
    .evolutions = (struct EvoData[]) {
        {EVOLVE_HAPPINESS, .happiness={TR_ANYTIME}, .species=JIGGLYPUFF},
        {0},
    },
    .learnset = (struct LevelMove[]) {
        {1, SING},
        {1, CHARM},
        {4, DEFENSE_CURL},
        {9, POUND},
        {14, SWEET_KISS},
        {0xff, 0},
    },
};

static const struct EvoMoves TogepiEvosAttacks = {
    .evolutions = (struct EvoData[]) {
        {EVOLVE_HAPPINESS, .happiness={TR_ANYTIME}, .species=TOGETIC},
        {0},
    },
    .learnset = (struct LevelMove[]) {
        {1, GROWL},
        {1, CHARM},
        {7, METRONOME},
        {18, SWEET_KISS},
        {25, ENCORE},
        {31, SAFEGUARD},
        {38, DOUBLE_EDGE},
        {0xff, 0},
    },
};

static const struct EvoMoves TogeticEvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, GROWL},
        {1, CHARM},
        {7, METRONOME},
        {18, SWEET_KISS},
        {25, ENCORE},
        {31, SAFEGUARD},
        {38, DOUBLE_EDGE},
        {0xff, 0},
    },
};

static const struct EvoMoves NatuEvosAttacks = {
    .evolutions = (struct EvoData[]) {
        {EVOLVE_LEVEL, .lvl={25}, .species=XATU},
        {0},
    },
    .learnset = (struct LevelMove[]) {
        {1, PECK},
        {1, LEER},
        {10, NIGHT_SHADE},
        {20, TELEPORT},
        {30, FUTURE_SIGHT},
        {40, CONFUSE_RAY},
        {50, PSYCHIC_M},
        {0xff, 0},
    },
};

static const struct EvoMoves XatuEvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, PECK},
        {1, LEER},
        {1, NIGHT_SHADE},
        {10, NIGHT_SHADE},
        {20, TELEPORT},
        {35, FUTURE_SIGHT},
        {50, CONFUSE_RAY},
        {65, PSYCHIC_M},
        {0xff, 0},
    },
};

static const struct EvoMoves MareepEvosAttacks = {
    .evolutions = (struct EvoData[]) {
        {EVOLVE_LEVEL, .lvl={15}, .species=FLAAFFY},
        {0},
    },
    .learnset = (struct LevelMove[]) {
        {1, TACKLE},
        {1, GROWL},
        {9, THUNDERSHOCK},
        {16, THUNDER_WAVE},
        {23, COTTON_SPORE},
        {30, LIGHT_SCREEN},
        {37, THUNDER},
        {0xff, 0},
    },
};

static const struct EvoMoves FlaaffyEvosAttacks = {
    .evolutions = (struct EvoData[]) {
        {EVOLVE_LEVEL, .lvl={30}, .species=AMPHAROS},
        {0},
    },
    .learnset = (struct LevelMove[]) {
        {1, TACKLE},
        {1, GROWL},
        {1, THUNDERSHOCK},
        {9, THUNDERSHOCK},
        {18, THUNDER_WAVE},
        {27, COTTON_SPORE},
        {36, LIGHT_SCREEN},
        {45, THUNDER},
        {0xff, 0},
    },
};

static const struct EvoMoves AmpharosEvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, TACKLE},
        {1, GROWL},
        {1, THUNDERSHOCK},
        {1, THUNDER_WAVE},
        {9, THUNDERSHOCK},
        {18, THUNDER_WAVE},
        {27, COTTON_SPORE},
        {30, THUNDERPUNCH},
        {42, LIGHT_SCREEN},
        {57, THUNDER},
        {0xff, 0},
    },
};

static const struct EvoMoves BellossomEvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, ABSORB},
        {1, SWEET_SCENT},
        {1, STUN_SPORE},
        {1, PETAL_DANCE},
        {55, SOLARBEAM},
        {0xff, 0},
    },
};

static const struct EvoMoves MarillEvosAttacks = {
    .evolutions = (struct EvoData[]) {
        {EVOLVE_LEVEL, .lvl={18}, .species=AZUMARILL},
        {0},
    },
    .learnset = (struct LevelMove[]) {
        {1, TACKLE},
        {3, DEFENSE_CURL},
        {6, TAIL_WHIP},
        {10, WATER_GUN},
        {15, ROLLOUT},
        {21, BUBBLEBEAM},
        {28, DOUBLE_EDGE},
        {36, RAIN_DANCE},
        {0xff, 0},
    },
};

static const struct EvoMoves AzumarillEvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, TACKLE},
        {1, DEFENSE_CURL},
        {1, TAIL_WHIP},
        {1, WATER_GUN},
        {3, DEFENSE_CURL},
        {6, TAIL_WHIP},
        {10, WATER_GUN},
        {15, ROLLOUT},
        {25, BUBBLEBEAM},
        {36, DOUBLE_EDGE},
        {48, RAIN_DANCE},
        {0xff, 0},
    },
};

static const struct EvoMoves SudowoodoEvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, ROCK_THROW},
        {1, MIMIC},
        {10, FLAIL},
        {19, LOW_KICK},
        {28, ROCK_SLIDE},
        {37, FAINT_ATTACK},
        {46, SLAM},
        {0xff, 0},
    },
};

static const struct EvoMoves PolitoedEvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, WATER_GUN},
        {1, HYPNOSIS},
        {1, DOUBLESLAP},
        {1, PERISH_SONG},
        {35, PERISH_SONG},
        {51, SWAGGER},
        {0xff, 0},
    },
};

static const struct EvoMoves HoppipEvosAttacks = {
    .evolutions = (struct EvoData[]) {
        {EVOLVE_LEVEL, .lvl={18}, .species=SKIPLOOM},
        {0},
    },
    .learnset = (struct LevelMove[]) {
        {1, SPLASH},
        {5, SYNTHESIS},
        {5, TAIL_WHIP},
        {10, TACKLE},
        {13, POISONPOWDER},
        {15, STUN_SPORE},
        {17, SLEEP_POWDER},
        {20, LEECH_SEED},
        {25, COTTON_SPORE},
        {30, MEGA_DRAIN},
        {0xff, 0},
    },
};

static const struct EvoMoves SkiploomEvosAttacks = {
    .evolutions = (struct EvoData[]) {
        {EVOLVE_LEVEL, .lvl={27}, .species=JUMPLUFF},
        {0},
    },
    .learnset = (struct LevelMove[]) {
        {1, SPLASH},
        {1, SYNTHESIS},
        {1, TAIL_WHIP},
        {1, TACKLE},
        {5, SYNTHESIS},
        {5, TAIL_WHIP},
        {10, TACKLE},
        {13, POISONPOWDER},
        {15, STUN_SPORE},
        {17, SLEEP_POWDER},
        {22, LEECH_SEED},
        {29, COTTON_SPORE},
        {36, MEGA_DRAIN},
        {0xff, 0},
    },
};

static const struct EvoMoves JumpluffEvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, SPLASH},
        {1, SYNTHESIS},
        {1, TAIL_WHIP},
        {1, TACKLE},
        {5, SYNTHESIS},
        {5, TAIL_WHIP},
        {10, TACKLE},
        {13, POISONPOWDER},
        {15, STUN_SPORE},
        {17, SLEEP_POWDER},
        {22, LEECH_SEED},
        {33, COTTON_SPORE},
        {44, MEGA_DRAIN},
        {0xff, 0},
    },
};

static const struct EvoMoves AipomEvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, SCRATCH},
        {1, TAIL_WHIP},
        {6, SAND_ATTACK},
        {12, BATON_PASS},
        {19, FURY_SWIPES},
        {27, SWIFT},
        {36, SCREECH},
        {46, AGILITY},
        {0xff, 0},
    },
};

static const struct EvoMoves SunkernEvosAttacks = {
    .evolutions = (struct EvoData[]) {
        {EVOLVE_ITEM, .item={SUN_STONE}, .species=SUNFLORA},
        {0},
    },
    .learnset = (struct LevelMove[]) {
        {1, ABSORB},
        {4, GROWTH},
        {10, MEGA_DRAIN},
        {19, SUNNY_DAY},
        {31, SYNTHESIS},
        {46, GIGA_DRAIN},
        {0xff, 0},
    },
};

static const struct EvoMoves SunfloraEvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, ABSORB},
        {1, POUND},
        {4, GROWTH},
        {10, RAZOR_LEAF},
        {19, SUNNY_DAY},
        {31, PETAL_DANCE},
        {46, SOLARBEAM},
        {0xff, 0},
    },
};

static const struct EvoMoves YanmaEvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, TACKLE},
        {1, FORESIGHT},
        {7, QUICK_ATTACK},
        {13, DOUBLE_TEAM},
        {19, SONICBOOM},
        {25, DETECT},
        {31, SUPERSONIC},
        {37, WING_ATTACK},
        {43, SCREECH},
        {0xff, 0},
    },
};

static const struct EvoMoves WooperEvosAttacks = {
    .evolutions = (struct EvoData[]) {
        {EVOLVE_LEVEL, .lvl={20}, .species=QUAGSIRE},
        {0},
    },
    .learnset = (struct LevelMove[]) {
        {1, WATER_GUN},
        {1, TAIL_WHIP},
        {11, SLAM},
        {21, AMNESIA},
        {31, EARTHQUAKE},
        {41, RAIN_DANCE},
        {51, MIST},
        {51, HAZE},
        {0xff, 0},
    },
};

static const struct EvoMoves QuagsireEvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, WATER_GUN},
        {1, TAIL_WHIP},
        {11, SLAM},
        {23, AMNESIA},
        {35, EARTHQUAKE},
        {47, RAIN_DANCE},
        {59, MIST},
        {59, HAZE},
        {0xff, 0},
    },
};

static const struct EvoMoves EspeonEvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, TACKLE},
        {1, TAIL_WHIP},
        {8, SAND_ATTACK},
        {16, CONFUSION},
        {23, QUICK_ATTACK},
        {30, SWIFT},
        {36, PSYBEAM},
        {42, PSYCH_UP},
        {47, PSYCHIC_M},
        {52, MORNING_SUN},
        {0xff, 0},
    },
};

static const struct EvoMoves UmbreonEvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, TACKLE},
        {1, TAIL_WHIP},
        {8, SAND_ATTACK},
        {16, PURSUIT},
        {23, QUICK_ATTACK},
        {30, CONFUSE_RAY},
        {36, FAINT_ATTACK},
        {42, MEAN_LOOK},
        {47, SCREECH},
        {52, MOONLIGHT},
        {0xff, 0},
    },
};

static const struct EvoMoves MurkrowEvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, PECK},
        {11, PURSUIT},
        {16, HAZE},
        {26, NIGHT_SHADE},
        {31, FAINT_ATTACK},
        {41, MEAN_LOOK},
        {0xff, 0},
    },
};

static const struct EvoMoves SlowkingEvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, CURSE},
        {1, TACKLE},
        {6, GROWL},
        {15, WATER_GUN},
        {20, CONFUSION},
        {29, DISABLE},
        {34, HEADBUTT},
        {43, SWAGGER},
        {48, PSYCHIC_M},
        {0xff, 0},
    },
};

static const struct EvoMoves MisdreavusEvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, GROWL},
        {1, PSYWAVE},
        {6, SPITE},
        {12, CONFUSE_RAY},
        {19, MEAN_LOOK},
        {27, PSYBEAM},
        {36, PAIN_SPLIT},
        {46, PERISH_SONG},
        {0xff, 0},
    },
};

static const struct EvoMoves UnownEvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, HIDDEN_POWER},
        {0xff, 0},
    },
};

static const struct EvoMoves WobbuffetEvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, COUNTER},
        {1, MIRROR_COAT},
        {1, SAFEGUARD},
        {1, DESTINY_BOND},
        {0xff, 0},
    },
};

static const struct EvoMoves GirafarigEvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, TACKLE},
        {1, GROWL},
        {1, CONFUSION},
        {1, STOMP},
        {7, CONFUSION},
        {13, STOMP},
        {20, AGILITY},
        {30, BATON_PASS},
        {41, PSYBEAM},
        {54, CRUNCH},
        {0xff, 0},
    },
};

static const struct EvoMoves PinecoEvosAttacks = {
    .evolutions = (struct EvoData[]) {
        {EVOLVE_LEVEL, .lvl={31}, .species=FORRETRESS},
        {0},
    },
    .learnset = (struct LevelMove[]) {
        {1, TACKLE},
        {1, PROTECT},
        {8, SELFDESTRUCT},
        {15, TAKE_DOWN},
        {22, RAPID_SPIN},
        {29, BIDE},
        {36, EXPLOSION},
        {43, SPIKES},
        {50, DOUBLE_EDGE},
        {0xff, 0},
    },
};

static const struct EvoMoves ForretressEvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, TACKLE},
        {1, PROTECT},
        {1, SELFDESTRUCT},
        {8, SELFDESTRUCT},
        {15, TAKE_DOWN},
        {22, RAPID_SPIN},
        {29, BIDE},
        {39, EXPLOSION},
        {49, SPIKES},
        {59, DOUBLE_EDGE},
        {0xff, 0},
    },
};

static const struct EvoMoves DunsparceEvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, RAGE},
        {5, DEFENSE_CURL},
        {13, GLARE},
        {18, SPITE},
        {26, PURSUIT},
        {30, SCREECH},
        {38, TAKE_DOWN},
        {0xff, 0},
    },
};

static const struct EvoMoves GligarEvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, POISON_STING},
        {6, SAND_ATTACK},
        {13, HARDEN},
        {20, QUICK_ATTACK},
        {28, FAINT_ATTACK},
        {36, SLASH},
        {44, SCREECH},
        {52, GUILLOTINE},
        {0xff, 0},
    },
};

static const struct EvoMoves SteelixEvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, TACKLE},
        {1, SCREECH},
        {10, BIND},
        {14, ROCK_THROW},
        {23, HARDEN},
        {27, RAGE},
        {36, SANDSTORM},
        {40, SLAM},
        {49, CRUNCH},
        {0xff, 0},
    },
};

static const struct EvoMoves SnubbullEvosAttacks = {
    .evolutions = (struct EvoData[]) {
        {EVOLVE_LEVEL, .lvl={23}, .species=GRANBULL},
        {0},
    },
    .learnset = (struct LevelMove[]) {
        {1, TACKLE},
        {1, SCARY_FACE},
        {4, TAIL_WHIP},
        {8, CHARM},
        {13, BITE},
        {19, LICK},
        {26, ROAR},
        {34, RAGE},
        {43, TAKE_DOWN},
        {0xff, 0},
    },
};

static const struct EvoMoves GranbullEvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, TACKLE},
        {1, SCARY_FACE},
        {4, TAIL_WHIP},
        {8, CHARM},
        {13, BITE},
        {19, LICK},
        {28, ROAR},
        {38, RAGE},
        {51, TAKE_DOWN},
        {0xff, 0},
    },
};

static const struct EvoMoves QwilfishEvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, SPIKES},
        {1, TACKLE},
        {1, POISON_STING},
        {10, HARDEN},
        {10, MINIMIZE},
        {19, WATER_GUN},
        {28, PIN_MISSILE},
        {37, TAKE_DOWN},
        {46, HYDRO_PUMP},
        {0xff, 0},
    },
};

static const struct EvoMoves ScizorEvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, QUICK_ATTACK},
        {1, LEER},
        {6, FOCUS_ENERGY},
        {12, PURSUIT},
        {18, FALSE_SWIPE},
        {24, AGILITY},
        {30, METAL_CLAW},
        {36, SLASH},
        {42, SWORDS_DANCE},
        {48, DOUBLE_TEAM},
        {0xff, 0},
    },
};

static const struct EvoMoves ShuckleEvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, CONSTRICT},
        {1, WITHDRAW},
        {9, WRAP},
        {14, ENCORE},
        {23, SAFEGUARD},
        {28, BIDE},
        {37, REST},
        {0xff, 0},
    },
};

static const struct EvoMoves HeracrossEvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, TACKLE},
        {1, LEER},
        {6, HORN_ATTACK},
        {12, ENDURE},
        {19, FURY_ATTACK},
        {27, COUNTER},
        {35, TAKE_DOWN},
        {44, REVERSAL},
        {54, MEGAHORN},
        {0xff, 0},
    },
};

static const struct EvoMoves SneaselEvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, SCRATCH},
        {1, LEER},
        {9, QUICK_ATTACK},
        {17, SCREECH},
        {25, FAINT_ATTACK},
        {33, FURY_SWIPES},
        {41, AGILITY},
        {49, SLASH},
        {57, BEAT_UP},
        {65, METAL_CLAW},
        {0xff, 0},
    },
};

static const struct EvoMoves TeddiursaEvosAttacks = {
    .evolutions = (struct EvoData[]) {
        {EVOLVE_LEVEL, .lvl={30}, .species=URSARING},
        {0},
    },
    .learnset = (struct LevelMove[]) {
        {1, SCRATCH},
        {1, LEER},
        {8, LICK},
        {15, FURY_SWIPES},
        {22, FAINT_ATTACK},
        {29, REST},
        {36, SLASH},
        {43, SNORE},
        {50, THRASH},
        {0xff, 0},
    },
};

static const struct EvoMoves UrsaringEvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, SCRATCH},
        {1, LEER},
        {1, LICK},
        {1, FURY_SWIPES},
        {8, LICK},
        {15, FURY_SWIPES},
        {22, FAINT_ATTACK},
        {29, REST},
        {39, SLASH},
        {49, SNORE},
        {59, THRASH},
        {0xff, 0},
    },
};

static const struct EvoMoves SlugmaEvosAttacks = {
    .evolutions = (struct EvoData[]) {
        {EVOLVE_LEVEL, .lvl={38}, .species=MAGCARGO},
        {0},
    },
    .learnset = (struct LevelMove[]) {
        {1, SMOG},
        {8, EMBER},
        {15, ROCK_THROW},
        {22, HARDEN},
        {29, AMNESIA},
        {36, FLAMETHROWER},
        {43, ROCK_SLIDE},
        {50, BODY_SLAM},
        {0xff, 0},
    },
};

static const struct EvoMoves MagcargoEvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, SMOG},
        {1, EMBER},
        {1, ROCK_THROW},
        {8, EMBER},
        {15, ROCK_THROW},
        {22, HARDEN},
        {29, AMNESIA},
        {36, FLAMETHROWER},
        {48, ROCK_SLIDE},
        {60, BODY_SLAM},
        {0xff, 0},
    },
};

static const struct EvoMoves SwinubEvosAttacks = {
    .evolutions = (struct EvoData[]) {
        {EVOLVE_LEVEL, .lvl={33}, .species=PILOSWINE},
        {0},
    },
    .learnset = (struct LevelMove[]) {
        {1, TACKLE},
        {10, POWDER_SNOW},
        {19, ENDURE},
        {28, TAKE_DOWN},
        {37, MIST},
        {46, BLIZZARD},
        {55, AMNESIA},
        {0xff, 0},
    },
};

static const struct EvoMoves PiloswineEvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, HORN_ATTACK},
        {1, POWDER_SNOW},
        {1, ENDURE},
        {10, POWDER_SNOW},
        {19, ENDURE},
        {28, TAKE_DOWN},
        {33, FURY_ATTACK},
        {42, MIST},
        {56, BLIZZARD},
        {70, AMNESIA},
        {0xff, 0},
    },
};

static const struct EvoMoves CorsolaEvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, TACKLE},
        {7, HARDEN},
        {13, BUBBLE},
        {19, RECOVER},
        {25, BUBBLEBEAM},
        {31, SPIKE_CANNON},
        {37, MIRROR_COAT},
        {43, ANCIENTPOWER},
        {0xff, 0},
    },
};

static const struct EvoMoves RemoraidEvosAttacks = {
    .evolutions = (struct EvoData[]) {
        {EVOLVE_LEVEL, .lvl={25}, .species=OCTILLERY},
        {0},
    },
    .learnset = (struct LevelMove[]) {
        {1, WATER_GUN},
        {11, LOCK_ON},
        {22, PSYBEAM},
        {22, AURORA_BEAM},
        {22, BUBBLEBEAM},
        {33, FOCUS_ENERGY},
        {44, ICE_BEAM},
        {55, HYPER_BEAM},
        {0xff, 0},
    },
};

static const struct EvoMoves OctilleryEvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, WATER_GUN},
        {11, CONSTRICT},
        {22, PSYBEAM},
        {22, AURORA_BEAM},
        {22, BUBBLEBEAM},
        {25, OCTAZOOKA},
        {38, FOCUS_ENERGY},
        {54, ICE_BEAM},
        {70, HYPER_BEAM},
        {0xff, 0},
    },
};

static const struct EvoMoves DelibirdEvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, PRESENT},
        {0xff, 0},
    },
};

static const struct EvoMoves MantineEvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, TACKLE},
        {1, BUBBLE},
        {10, SUPERSONIC},
        {18, BUBBLEBEAM},
        {25, TAKE_DOWN},
        {32, AGILITY},
        {40, WING_ATTACK},
        {49, CONFUSE_RAY},
        {0xff, 0},
    },
};

static const struct EvoMoves SkarmoryEvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, LEER},
        {1, PECK},
        {13, SAND_ATTACK},
        {19, SWIFT},
        {25, AGILITY},
        {37, FURY_ATTACK},
        {49, STEEL_WING},
        {0xff, 0},
    },
};

static const struct EvoMoves HoundourEvosAttacks = {
    .evolutions = (struct EvoData[]) {
        {EVOLVE_LEVEL, .lvl={24}, .species=HOUNDOOM},
        {0},
    },
    .learnset = (struct LevelMove[]) {
        {1, LEER},
        {1, EMBER},
        {7, ROAR},
        {13, SMOG},
        {20, BITE},
        {27, FAINT_ATTACK},
        {35, FLAMETHROWER},
        {43, CRUNCH},
        {0xff, 0},
    },
};

static const struct EvoMoves HoundoomEvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, LEER},
        {1, EMBER},
        {7, ROAR},
        {13, SMOG},
        {20, BITE},
        {30, FAINT_ATTACK},
        {41, FLAMETHROWER},
        {52, CRUNCH},
        {0xff, 0},
    },
};

static const struct EvoMoves KingdraEvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, BUBBLE},
        {1, SMOKESCREEN},
        {1, LEER},
        {1, WATER_GUN},
        {8, SMOKESCREEN},
        {15, LEER},
        {22, WATER_GUN},
        {29, TWISTER},
        {40, AGILITY},
        {51, HYDRO_PUMP},
        {0xff, 0},
    },
};

static const struct EvoMoves PhanpyEvosAttacks = {
    .evolutions = (struct EvoData[]) {
        {EVOLVE_LEVEL, .lvl={25}, .species=DONPHAN},
        {0},
    },
    .learnset = (struct LevelMove[]) {
        {1, TACKLE},
        {1, GROWL},
        {9, DEFENSE_CURL},
        {17, FLAIL},
        {25, TAKE_DOWN},
        {33, ROLLOUT},
        {41, ENDURE},
        {49, DOUBLE_EDGE},
        {0xff, 0},
    },
};

static const struct EvoMoves DonphanEvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, HORN_ATTACK},
        {1, GROWL},
        {9, DEFENSE_CURL},
        {17, FLAIL},
        {25, FURY_ATTACK},
        {33, ROLLOUT},
        {41, RAPID_SPIN},
        {49, EARTHQUAKE},
        {0xff, 0},
    },
};

static const struct EvoMoves Porygon2EvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, CONVERSION2},
        {1, TACKLE},
        {1, CONVERSION},
        {9, AGILITY},
        {12, PSYBEAM},
        {20, RECOVER},
        {24, DEFENSE_CURL},
        {32, LOCK_ON},
        {36, TRI_ATTACK},
        {44, ZAP_CANNON},
        {0xff, 0},
    },
};

static const struct EvoMoves StantlerEvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, TACKLE},
        {8, LEER},
        {15, HYPNOSIS},
        {23, STOMP},
        {31, SAND_ATTACK},
        {40, TAKE_DOWN},
        {49, CONFUSE_RAY},
        {0xff, 0},
    },
};

static const struct EvoMoves SmeargleEvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, SKETCH},
        {11, SKETCH},
        {21, SKETCH},
        {31, SKETCH},
        {41, SKETCH},
        {51, SKETCH},
        {61, SKETCH},
        {71, SKETCH},
        {81, SKETCH},
        {91, SKETCH},
        {0xff, 0},
    },
};

static const struct EvoMoves TyrogueEvosAttacks = {
    .evolutions = (struct EvoData[]) {
        {EVOLVE_STAT, .stat={20, ATK_LT_DEF}, .species=HITMONCHAN},
        {EVOLVE_STAT, .stat={20, ATK_GT_DEF}, .species=HITMONLEE},
        {EVOLVE_STAT, .stat={20, ATK_EQ_DEF}, .species=HITMONTOP},
        {0},
    },
    .learnset = (struct LevelMove[]) {
        {1, TACKLE},
        {0xff, 0},
    },
};

static const struct EvoMoves HitmontopEvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, ROLLING_KICK},
        {7, FOCUS_ENERGY},
        {13, PURSUIT},
        {19, QUICK_ATTACK},
        {25, RAPID_SPIN},
        {31, COUNTER},
        {37, AGILITY},
        {43, DETECT},
        {49, TRIPLE_KICK},
        {0xff, 0},
    },
};

static const struct EvoMoves SmoochumEvosAttacks = {
    .evolutions = (struct EvoData[]) {
        {EVOLVE_LEVEL, .lvl={30}, .species=JYNX},
        {0},
    },
    .learnset = (struct LevelMove[]) {
        {1, POUND},
        {1, LICK},
        {9, SWEET_KISS},
        {13, POWDER_SNOW},
        {21, CONFUSION},
        {25, SING},
        {33, MEAN_LOOK},
        {37, PSYCHIC_M},
        {45, PERISH_SONG},
        {49, BLIZZARD},
        {0xff, 0},
    },
};

static const struct EvoMoves ElekidEvosAttacks = {
    .evolutions = (struct EvoData[]) {
        {EVOLVE_LEVEL, .lvl={30}, .species=ELECTABUZZ},
        {0},
    },
    .learnset = (struct LevelMove[]) {
        {1, QUICK_ATTACK},
        {1, LEER},
        {9, THUNDERPUNCH},
        {17, LIGHT_SCREEN},
        {25, SWIFT},
        {33, SCREECH},
        {41, THUNDERBOLT},
        {49, THUNDER},
        {0xff, 0},
    },
};

static const struct EvoMoves MagbyEvosAttacks = {
    .evolutions = (struct EvoData[]) {
        {EVOLVE_LEVEL, .lvl={30}, .species=MAGMAR},
        {0},
    },
    .learnset = (struct LevelMove[]) {
        {1, EMBER},
        {7, LEER},
        {13, SMOG},
        {19, FIRE_PUNCH},
        {25, SMOKESCREEN},
        {31, SUNNY_DAY},
        {37, FLAMETHROWER},
        {43, CONFUSE_RAY},
        {49, FIRE_BLAST},
        {0xff, 0},
    },
};

static const struct EvoMoves MiltankEvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, TACKLE},
        {4, GROWL},
        {8, DEFENSE_CURL},
        {13, STOMP},
        {19, MILK_DRINK},
        {26, BIDE},
        {34, ROLLOUT},
        {43, BODY_SLAM},
        {53, HEAL_BELL},
        {0xff, 0},
    },
};

static const struct EvoMoves BlisseyEvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, POUND},
        {4, GROWL},
        {7, TAIL_WHIP},
        {10, SOFTBOILED},
        {13, DOUBLESLAP},
        {18, MINIMIZE},
        {23, SING},
        {28, EGG_BOMB},
        {33, DEFENSE_CURL},
        {40, LIGHT_SCREEN},
        {47, DOUBLE_EDGE},
        {0xff, 0},
    },
};

static const struct EvoMoves RaikouEvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, BITE},
        {1, LEER},
        {11, THUNDERSHOCK},
        {21, ROAR},
        {31, QUICK_ATTACK},
        {41, SPARK},
        {51, REFLECT},
        {61, CRUNCH},
        {71, THUNDER},
        {0xff, 0},
    },
};

static const struct EvoMoves EnteiEvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, BITE},
        {1, LEER},
        {11, EMBER},
        {21, ROAR},
        {31, FIRE_SPIN},
        {41, STOMP},
        {51, FLAMETHROWER},
        {61, SWAGGER},
        {71, FIRE_BLAST},
        {0xff, 0},
    },
};

static const struct EvoMoves SuicuneEvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, BITE},
        {1, LEER},
        {11, BUBBLEBEAM},
        {21, RAIN_DANCE},
        {31, GUST},
        {41, AURORA_BEAM},
        {51, MIST},
        {61, MIRROR_COAT},
        {71, HYDRO_PUMP},
        {0xff, 0},
    },
};

static const struct EvoMoves LarvitarEvosAttacks = {
    .evolutions = (struct EvoData[]) {
        {EVOLVE_LEVEL, .lvl={30}, .species=PUPITAR},
        {0},
    },
    .learnset = (struct LevelMove[]) {
        {1, BITE},
        {1, LEER},
        {8, SANDSTORM},
        {15, SCREECH},
        {22, ROCK_SLIDE},
        {29, THRASH},
        {36, SCARY_FACE},
        {43, CRUNCH},
        {50, EARTHQUAKE},
        {57, HYPER_BEAM},
        {0xff, 0},
    },
};

static const struct EvoMoves PupitarEvosAttacks = {
    .evolutions = (struct EvoData[]) {
        {EVOLVE_LEVEL, .lvl={55}, .species=TYRANITAR},
        {0},
    },
    .learnset = (struct LevelMove[]) {
        {1, BITE},
        {1, LEER},
        {1, SANDSTORM},
        {1, SCREECH},
        {8, SANDSTORM},
        {15, SCREECH},
        {22, ROCK_SLIDE},
        {29, THRASH},
        {38, SCARY_FACE},
        {47, CRUNCH},
        {56, EARTHQUAKE},
        {65, HYPER_BEAM},
        {0xff, 0},
    },
};

static const struct EvoMoves TyranitarEvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, BITE},
        {1, LEER},
        {1, SANDSTORM},
        {1, SCREECH},
        {8, SANDSTORM},
        {15, SCREECH},
        {22, ROCK_SLIDE},
        {29, THRASH},
        {38, SCARY_FACE},
        {47, CRUNCH},
        {61, EARTHQUAKE},
        {75, HYPER_BEAM},
        {0xff, 0},
    },
};

static const struct EvoMoves LugiaEvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, AEROBLAST},
        {11, SAFEGUARD},
        {22, GUST},
        {33, RECOVER},
        {44, HYDRO_PUMP},
        {55, RAIN_DANCE},
        {66, SWIFT},
        {77, WHIRLWIND},
        {88, ANCIENTPOWER},
        {99, FUTURE_SIGHT},
        {0xff, 0},
    },
};

static const struct EvoMoves HoOhEvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, SACRED_FIRE},
        {11, SAFEGUARD},
        {22, GUST},
        {33, RECOVER},
        {44, FIRE_BLAST},
        {55, SUNNY_DAY},
        {66, SWIFT},
        {77, WHIRLWIND},
        {88, ANCIENTPOWER},
        {99, FUTURE_SIGHT},
        {0xff, 0},
    },
};

static const struct EvoMoves CelebiEvosAttacks = {
    .evolutions = (struct EvoData[]) {{0}},

    .learnset = (struct LevelMove[]) {
        {1, LEECH_SEED},
        {1, CONFUSION},
        {1, RECOVER},
        {1, HEAL_BELL},
        {10, SAFEGUARD},
        {20, ANCIENTPOWER},
        {30, FUTURE_SIGHT},
        {40, BATON_PASS},
        {50, PERISH_SONG},
        {0xff, 0},
    },
};


const struct EvoMoves* const EvosAttacksPointers[] = {
    &BulbasaurEvosAttacks,
    &IvysaurEvosAttacks,
    &VenusaurEvosAttacks,
    &CharmanderEvosAttacks,
    &CharmeleonEvosAttacks,
    &CharizardEvosAttacks,
    &SquirtleEvosAttacks,
    &WartortleEvosAttacks,
    &BlastoiseEvosAttacks,
    &CaterpieEvosAttacks,
    &MetapodEvosAttacks,
    &ButterfreeEvosAttacks,
    &WeedleEvosAttacks,
    &KakunaEvosAttacks,
    &BeedrillEvosAttacks,
    &PidgeyEvosAttacks,
    &PidgeottoEvosAttacks,
    &PidgeotEvosAttacks,
    &RattataEvosAttacks,
    &RaticateEvosAttacks,
    &SpearowEvosAttacks,
    &FearowEvosAttacks,
    &EkansEvosAttacks,
    &ArbokEvosAttacks,
    &PikachuEvosAttacks,
    &RaichuEvosAttacks,
    &SandshrewEvosAttacks,
    &SandslashEvosAttacks,
    &NidoranFEvosAttacks,
    &NidorinaEvosAttacks,
    &NidoqueenEvosAttacks,
    &NidoranMEvosAttacks,
    &NidorinoEvosAttacks,
    &NidokingEvosAttacks,
    &ClefairyEvosAttacks,
    &ClefableEvosAttacks,
    &VulpixEvosAttacks,
    &NinetalesEvosAttacks,
    &JigglypuffEvosAttacks,
    &WigglytuffEvosAttacks,
    &ZubatEvosAttacks,
    &GolbatEvosAttacks,
    &OddishEvosAttacks,
    &GloomEvosAttacks,
    &VileplumeEvosAttacks,
    &ParasEvosAttacks,
    &ParasectEvosAttacks,
    &VenonatEvosAttacks,
    &VenomothEvosAttacks,
    &DiglettEvosAttacks,
    &DugtrioEvosAttacks,
    &MeowthEvosAttacks,
    &PersianEvosAttacks,
    &PsyduckEvosAttacks,
    &GolduckEvosAttacks,
    &MankeyEvosAttacks,
    &PrimeapeEvosAttacks,
    &GrowlitheEvosAttacks,
    &ArcanineEvosAttacks,
    &PoliwagEvosAttacks,
    &PoliwhirlEvosAttacks,
    &PoliwrathEvosAttacks,
    &AbraEvosAttacks,
    &KadabraEvosAttacks,
    &AlakazamEvosAttacks,
    &MachopEvosAttacks,
    &MachokeEvosAttacks,
    &MachampEvosAttacks,
    &BellsproutEvosAttacks,
    &WeepinbellEvosAttacks,
    &VictreebelEvosAttacks,
    &TentacoolEvosAttacks,
    &TentacruelEvosAttacks,
    &GeodudeEvosAttacks,
    &GravelerEvosAttacks,
    &GolemEvosAttacks,
    &PonytaEvosAttacks,
    &RapidashEvosAttacks,
    &SlowpokeEvosAttacks,
    &SlowbroEvosAttacks,
    &MagnemiteEvosAttacks,
    &MagnetonEvosAttacks,
    &FarfetchDEvosAttacks,
    &DoduoEvosAttacks,
    &DodrioEvosAttacks,
    &SeelEvosAttacks,
    &DewgongEvosAttacks,
    &GrimerEvosAttacks,
    &MukEvosAttacks,
    &ShellderEvosAttacks,
    &CloysterEvosAttacks,
    &GastlyEvosAttacks,
    &HaunterEvosAttacks,
    &GengarEvosAttacks,
    &OnixEvosAttacks,
    &DrowzeeEvosAttacks,
    &HypnoEvosAttacks,
    &KrabbyEvosAttacks,
    &KinglerEvosAttacks,
    &VoltorbEvosAttacks,
    &ElectrodeEvosAttacks,
    &ExeggcuteEvosAttacks,
    &ExeggutorEvosAttacks,
    &CuboneEvosAttacks,
    &MarowakEvosAttacks,
    &HitmonleeEvosAttacks,
    &HitmonchanEvosAttacks,
    &LickitungEvosAttacks,
    &KoffingEvosAttacks,
    &WeezingEvosAttacks,
    &RhyhornEvosAttacks,
    &RhydonEvosAttacks,
    &ChanseyEvosAttacks,
    &TangelaEvosAttacks,
    &KangaskhanEvosAttacks,
    &HorseaEvosAttacks,
    &SeadraEvosAttacks,
    &GoldeenEvosAttacks,
    &SeakingEvosAttacks,
    &StaryuEvosAttacks,
    &StarmieEvosAttacks,
    &MrMimeEvosAttacks,
    &ScytherEvosAttacks,
    &JynxEvosAttacks,
    &ElectabuzzEvosAttacks,
    &MagmarEvosAttacks,
    &PinsirEvosAttacks,
    &TaurosEvosAttacks,
    &MagikarpEvosAttacks,
    &GyaradosEvosAttacks,
    &LaprasEvosAttacks,
    &DittoEvosAttacks,
    &EeveeEvosAttacks,
    &VaporeonEvosAttacks,
    &JolteonEvosAttacks,
    &FlareonEvosAttacks,
    &PorygonEvosAttacks,
    &OmanyteEvosAttacks,
    &OmastarEvosAttacks,
    &KabutoEvosAttacks,
    &KabutopsEvosAttacks,
    &AerodactylEvosAttacks,
    &SnorlaxEvosAttacks,
    &ArticunoEvosAttacks,
    &ZapdosEvosAttacks,
    &MoltresEvosAttacks,
    &DratiniEvosAttacks,
    &DragonairEvosAttacks,
    &DragoniteEvosAttacks,
    &MewtwoEvosAttacks,
    &MewEvosAttacks,
    &ChikoritaEvosAttacks,
    &BayleefEvosAttacks,
    &MeganiumEvosAttacks,
    &CyndaquilEvosAttacks,
    &QuilavaEvosAttacks,
    &TyphlosionEvosAttacks,
    &TotodileEvosAttacks,
    &CroconawEvosAttacks,
    &FeraligatrEvosAttacks,
    &SentretEvosAttacks,
    &FurretEvosAttacks,
    &HoothootEvosAttacks,
    &NoctowlEvosAttacks,
    &LedybaEvosAttacks,
    &LedianEvosAttacks,
    &SpinarakEvosAttacks,
    &AriadosEvosAttacks,
    &CrobatEvosAttacks,
    &ChinchouEvosAttacks,
    &LanturnEvosAttacks,
    &PichuEvosAttacks,
    &CleffaEvosAttacks,
    &IgglybuffEvosAttacks,
    &TogepiEvosAttacks,
    &TogeticEvosAttacks,
    &NatuEvosAttacks,
    &XatuEvosAttacks,
    &MareepEvosAttacks,
    &FlaaffyEvosAttacks,
    &AmpharosEvosAttacks,
    &BellossomEvosAttacks,
    &MarillEvosAttacks,
    &AzumarillEvosAttacks,
    &SudowoodoEvosAttacks,
    &PolitoedEvosAttacks,
    &HoppipEvosAttacks,
    &SkiploomEvosAttacks,
    &JumpluffEvosAttacks,
    &AipomEvosAttacks,
    &SunkernEvosAttacks,
    &SunfloraEvosAttacks,
    &YanmaEvosAttacks,
    &WooperEvosAttacks,
    &QuagsireEvosAttacks,
    &EspeonEvosAttacks,
    &UmbreonEvosAttacks,
    &MurkrowEvosAttacks,
    &SlowkingEvosAttacks,
    &MisdreavusEvosAttacks,
    &UnownEvosAttacks,
    &WobbuffetEvosAttacks,
    &GirafarigEvosAttacks,
    &PinecoEvosAttacks,
    &ForretressEvosAttacks,
    &DunsparceEvosAttacks,
    &GligarEvosAttacks,
    &SteelixEvosAttacks,
    &SnubbullEvosAttacks,
    &GranbullEvosAttacks,
    &QwilfishEvosAttacks,
    &ScizorEvosAttacks,
    &ShuckleEvosAttacks,
    &HeracrossEvosAttacks,
    &SneaselEvosAttacks,
    &TeddiursaEvosAttacks,
    &UrsaringEvosAttacks,
    &SlugmaEvosAttacks,
    &MagcargoEvosAttacks,
    &SwinubEvosAttacks,
    &PiloswineEvosAttacks,
    &CorsolaEvosAttacks,
    &RemoraidEvosAttacks,
    &OctilleryEvosAttacks,
    &DelibirdEvosAttacks,
    &MantineEvosAttacks,
    &SkarmoryEvosAttacks,
    &HoundourEvosAttacks,
    &HoundoomEvosAttacks,
    &KingdraEvosAttacks,
    &PhanpyEvosAttacks,
    &DonphanEvosAttacks,
    &Porygon2EvosAttacks,
    &StantlerEvosAttacks,
    &SmeargleEvosAttacks,
    &TyrogueEvosAttacks,
    &HitmontopEvosAttacks,
    &SmoochumEvosAttacks,
    &ElekidEvosAttacks,
    &MagbyEvosAttacks,
    &MiltankEvosAttacks,
    &BlisseyEvosAttacks,
    &RaikouEvosAttacks,
    &EnteiEvosAttacks,
    &SuicuneEvosAttacks,
    &LarvitarEvosAttacks,
    &PupitarEvosAttacks,
    &TyranitarEvosAttacks,
    &LugiaEvosAttacks,
    &HoOhEvosAttacks,
    &CelebiEvosAttacks,
};

static_assert(lengthof(EvosAttacksPointers) == NUM_POKEMON, "");
