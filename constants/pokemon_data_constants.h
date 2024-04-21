// base data struct members (see data/pokemon/base_stats/*.asm)
enum {
    BASE_DEX_NO = 0,
    BASE_STATS = 1,

    BASE_HP = 1,
    BASE_ATK = 2,
    BASE_DEF = 3,
    BASE_SPD = 4,
    BASE_SAT = 5,
    BASE_SDF = 6,
    BASE_TYPES = 7,

    BASE_TYPE_1 = 7,
    BASE_TYPE_2 = 8,
    BASE_CATCH_RATE = 9,
    BASE_EXP = 10,
    BASE_ITEMS = 11,

    BASE_ITEM_1 = 11,
    BASE_ITEM_2 = 12,
    BASE_GENDER = 13,

    BASE_EGG_STEPS = 15,

    BASE_PIC_SIZE = 17,
    BASE_FRONTPIC = 18,
    BASE_BACKPIC = 20,
    BASE_GROWTH_RATE = 22,
    BASE_EGG_GROUPS = 23,
    BASE_TMHM = 24,
};

#define BASE_DATA_SIZE BASE_TMHM + ((NUM_TM_HM_TUTOR + 7) / 8)

// gender ratio constants
#define GENDER_F0 0 percent
#define GENDER_F12_5 12 percent + 1
#define GENDER_F25 25 percent
#define GENDER_F50 50 percent
#define GENDER_F75 75 percent
#define GENDER_F100 100 percent - 1
#define GENDER_UNKNOWN -1

// wBaseGrowthRate values
// GrowthRates indexes (see data/growth_rates.asm)
enum {
    GROWTH_MEDIUM_FAST,
    GROWTH_SLIGHTLY_FAST,
    GROWTH_SLIGHTLY_SLOW,
    GROWTH_MEDIUM_SLOW,
    GROWTH_FAST,
    GROWTH_SLOW,
    NUM_GROWTH_RATES,
};

// wBaseEggGroups values
enum {
    EGG_MONSTER = 1,
    EGG_WATER_1,
    EGG_BUG,
    EGG_FLYING,
    EGG_GROUND,
    EGG_FAIRY,
    EGG_PLANT,
    EGG_HUMANSHAPE,
    EGG_WATER_3,
    EGG_MINERAL,
    EGG_INDETERMINATE,
    EGG_WATER_2,
    EGG_DITTO,
    EGG_DRAGON,
    EGG_NONE,
};

// pokedex entries (see data/pokemon/dex_entries.asm)
#define NUM_DEX_ENTRY_BANKS 4

// party_struct members (see macros/wram.asm)
enum {
    MON_SPECIES = 0,
    MON_ITEM = 1,
    MON_MOVES = 2,
    MON_ID = 6,
    MON_EXP = 8,
    MON_STAT_EXP = 11,
    MON_HP_EXP = 11,
    MON_ATK_EXP = 13,
    MON_DEF_EXP = 15,
    MON_SPD_EXP = 17,
    MON_SPC_EXP = 19,
    MON_DVS = 21,
    MON_PP = 23,
    MON_HAPPINESS = 27,
    MON_POKERUS = 28,
    MON_CAUGHTDATA = 29,  // Crystal uses caught data, all in 2 bytes
    MON_CAUGHTTIME = 29,
    MON_CAUGHTGENDER = 30,
    MON_CAUGHTLEVEL = 29,
    MON_CAUGHTLOCATION = 30,
    MON_LEVEL = 31,
    BOXMON_STRUCT_LENGTH = 32,

    MON_STATUS = 32,
    MON_HP = 34,
    MON_MAXHP = 36,
    MON_STATS = 38,

    MON_ATK = 38,
    MON_DEF = 40,
    MON_SPD = 42,
    MON_SAT = 44,
    MON_SDF = 46,
    PARTYMON_STRUCT_LENGTH = 48,
};

#define NICKNAMED_MON_STRUCT_LENGTH PARTYMON_STRUCT_LENGTH + MON_NAME_LENGTH
#define REDMON_STRUCT_LENGTH 44

// caught data

#define CAUGHT_TIME_MASK 0b11000000
#define CAUGHT_LEVEL_MASK 0b00111111

#define CAUGHT_GENDER_MASK 0b10000000
#define CAUGHT_LOCATION_MASK 0b01111111

#define CAUGHT_BY_UNKNOWN 0
#define CAUGHT_BY_GIRL 1
#define CAUGHT_BY_BOY 2

#define CAUGHT_EGG_LEVEL 1

#define MON_CRY_LENGTH 6

// maximum number of party pokemon
#define PARTY_LENGTH 6

// boxes
#define MONS_PER_BOX 20
// box: count, species, mons, OTs, nicknames, padding
#define BOX_LENGTH 1 + MONS_PER_BOX + 1 + (BOXMON_STRUCT_LENGTH + NAME_LENGTH + MON_NAME_LENGTH) * MONS_PER_BOX + 2  // 0x450
#define NUM_BOXES 14

// hall of fame
// hof_mon: species, id, dvs, level, nicknames
#define HOF_MON_LENGTH 1 + 2 + 2 + 1 + (MON_NAME_LENGTH - 1)  // 0x10
// hall_of_fame: win count, party, terminator
#define HOF_LENGTH 1 + HOF_MON_LENGTH* PARTY_LENGTH + 1  // 0x62
#define NUM_HOF_TEAMS 30

// evolution types (used in data/pokemon/evos_attacks.asm)
enum {
    EVOLVE_LEVEL = 1,
    EVOLVE_ITEM,
    EVOLVE_TRADE,
    EVOLVE_HAPPINESS,
    EVOLVE_STAT,
};

// EVOLVE_HAPPINESS triggers
enum {
    TR_ANYTIME,
    TR_MORNDAY,
    TR_NITE,
};

// EVOLVE_STAT triggers
enum {
    ATK_GT_DEF,
    ATK_LT_DEF,
    ATK_EQ_DEF,
};

// wild data

#define NUM_GRASSMON 7  // data/wild/*_grass.asm table size
#define NUM_WATERMON 3  // data/wild/*_water.asm table size

#define GRASS_WILDDATA_LENGTH 2 + (1 + NUM_GRASSMON * 2) * 3
#define WATER_WILDDATA_LENGTH 2 + (1 + NUM_WATERMON * 2) * 1
#define FISHGROUP_DATA_LENGTH 1 + 2 * 3

#define NUM_ROAMMON_MAPS 16  // RoamMaps table size (see data/wild/roammon_maps.asm)

// treemon sets
// TreeMons indexes (see data/wild/treemons.asm)
enum {
    TREEMON_SET_CITY,
    TREEMON_SET_CANYON,
    TREEMON_SET_TOWN,
    TREEMON_SET_ROUTE,
    TREEMON_SET_KANTO,
    TREEMON_SET_LAKE,
    TREEMON_SET_FOREST,
    TREEMON_SET_ROCK,
    NUM_TREEMON_SETS,
};

// treemon scores
enum {
    TREEMON_SCORE_BAD,
    TREEMON_SCORE_GOOD,
    TREEMON_SCORE_RARE,
};

// ChangeHappiness arguments (see data/events/happiness_changes.asm)
enum {
    HAPPINESS_GAINLEVEL = 1,
    HAPPINESS_USEDITEM,
    HAPPINESS_USEDXITEM,
    HAPPINESS_GYMBATTLE,
    HAPPINESS_LEARNMOVE,
    HAPPINESS_FAINTED,
    HAPPINESS_POISONFAINT,
    HAPPINESS_BEATENBYSTRONGFOE,
    HAPPINESS_OLDERCUT1,
    HAPPINESS_OLDERCUT2,
    HAPPINESS_OLDERCUT3,
    HAPPINESS_YOUNGCUT1,
    HAPPINESS_YOUNGCUT2,
    HAPPINESS_YOUNGCUT3,
    HAPPINESS_BITTERPOWDER,
    HAPPINESS_ENERGYROOT,
    HAPPINESS_REVIVALHERB,
    HAPPINESS_GROOMING,
    HAPPINESS_GAINLEVELATHOME,
};

#define NUM_HAPPINESS_CHANGES HAPPINESS_GAINLEVELATHOME

// significant happiness values
#define BASE_HAPPINESS 70
#define FRIEND_BALL_HAPPINESS 200
#define HAPPINESS_TO_EVOLVE 220
#define HAPPINESS_THRESHOLD_1 100
#define HAPPINESS_THRESHOLD_2 200

// PP
#define PP_UP_MASK 0b11000000
#define PP_UP_ONE 0b01000000
#define PP_MASK 0b00111111
