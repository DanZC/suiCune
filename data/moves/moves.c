#include "../../constants.h"
#include "moves.h"

const struct Move Moves[] = {
// entries correspond to move ids (see constants/move_constants.h)
    [POUND]         = {POUND,        EFFECT_NORMAL_HIT,         40, NORMAL,       100 percent, 35,   0 percent},
    [KARATE_CHOP]   = {KARATE_CHOP,  EFFECT_NORMAL_HIT,         50, FIGHTING,     100 percent, 25,   0 percent},
    [DOUBLESLAP]    = {DOUBLESLAP,   EFFECT_MULTI_HIT,          15, NORMAL,        85 percent, 10,   0 percent},
    [COMET_PUNCH]   = {COMET_PUNCH,  EFFECT_MULTI_HIT,          18, NORMAL,        85 percent, 15,   0 percent},
    [MEGA_PUNCH]    = {MEGA_PUNCH,   EFFECT_NORMAL_HIT,         80, NORMAL,        85 percent, 20,   0 percent},
    [PAY_DAY]       = {PAY_DAY,      EFFECT_PAY_DAY,            40, NORMAL,       100 percent, 20,   0 percent},
    [FIRE_PUNCH]    = {FIRE_PUNCH,   EFFECT_BURN_HIT,           75, FIRE,         100 percent, 15,  10 percent},
    [ICE_PUNCH]     = {ICE_PUNCH,    EFFECT_FREEZE_HIT,         75, ICE,          100 percent, 15,  10 percent},
    [THUNDERPUNCH]  = {THUNDERPUNCH, EFFECT_PARALYZE_HIT,       75, ELECTRIC,     100 percent, 15,  10 percent},
    [SCRATCH]       = {SCRATCH,      EFFECT_NORMAL_HIT,         40, NORMAL,       100 percent, 35,   0 percent},
    [VICEGRIP]      = {VICEGRIP,     EFFECT_NORMAL_HIT,         55, NORMAL,       100 percent, 30,   0 percent},
    [GUILLOTINE]    = {GUILLOTINE,   EFFECT_OHKO,                0, NORMAL,        30 percent,  5,   0 percent},
    [RAZOR_WIND]    = {RAZOR_WIND,   EFFECT_RAZOR_WIND,         80, NORMAL,        75 percent, 10,   0 percent},
    [SWORDS_DANCE]  = {SWORDS_DANCE, EFFECT_ATTACK_UP_2,         0, NORMAL,       100 percent, 30,   0 percent},
    [CUT]           = {CUT,          EFFECT_NORMAL_HIT,         50, NORMAL,        95 percent, 30,   0 percent},
    [GUST]          = {GUST,         EFFECT_GUST,               40, FLYING,       100 percent, 35,   0 percent},
    [WING_ATTACK]   = {WING_ATTACK,  EFFECT_NORMAL_HIT,         60, FLYING,       100 percent, 35,   0 percent},
    [WHIRLWIND]     = {WHIRLWIND,    EFFECT_FORCE_SWITCH,        0, NORMAL,       100 percent, 20,   0 percent},
    [FLY]           = {FLY,          EFFECT_FLY,                70, FLYING,        95 percent, 15,   0 percent},
    [BIND]          = {BIND,         EFFECT_TRAP_TARGET,        15, NORMAL,        75 percent, 20,   0 percent},
    [SLAM]          = {SLAM,         EFFECT_NORMAL_HIT,         80, NORMAL,        75 percent, 20,   0 percent},
    [VINE_WHIP]     = {VINE_WHIP,    EFFECT_NORMAL_HIT,         35, GRASS,        100 percent, 10,   0 percent},
    [STOMP]         = {STOMP,        EFFECT_STOMP,              65, NORMAL,       100 percent, 20,  30 percent},
    [DOUBLE_KICK]   = {DOUBLE_KICK,  EFFECT_DOUBLE_HIT,         30, FIGHTING,     100 percent, 30,   0 percent},
    [MEGA_KICK]     = {MEGA_KICK,    EFFECT_NORMAL_HIT,        120, NORMAL,        75 percent,  5,   0 percent},
    [JUMP_KICK]     = {JUMP_KICK,    EFFECT_JUMP_KICK,          70, FIGHTING,      95 percent, 25,   0 percent},
    [ROLLING_KICK]  = {ROLLING_KICK, EFFECT_FLINCH_HIT,         60, FIGHTING,      85 percent, 15,  30 percent},
    [SAND_ATTACK]   = {SAND_ATTACK,  EFFECT_ACCURACY_DOWN,       0, GROUND,       100 percent, 15,   0 percent},
    [HEADBUTT]      = {HEADBUTT,     EFFECT_FLINCH_HIT,         70, NORMAL,       100 percent, 15,  30 percent},
    [HORN_ATTACK]   = {HORN_ATTACK,  EFFECT_NORMAL_HIT,         65, NORMAL,       100 percent, 25,   0 percent},
    [FURY_ATTACK]   = {FURY_ATTACK,  EFFECT_MULTI_HIT,          15, NORMAL,        85 percent, 20,   0 percent},
    [HORN_DRILL]    = {HORN_DRILL,   EFFECT_OHKO,                1, NORMAL,        30 percent,  5,   0 percent},
    [TACKLE]        = {TACKLE,       EFFECT_NORMAL_HIT,         35, NORMAL,        95 percent, 35,   0 percent},
    [BODY_SLAM]     = {BODY_SLAM,    EFFECT_PARALYZE_HIT,       85, NORMAL,       100 percent, 15,  30 percent},
    [WRAP]          = {WRAP,         EFFECT_TRAP_TARGET,        15, NORMAL,        85 percent, 20,   0 percent},
    [TAKE_DOWN]     = {TAKE_DOWN,    EFFECT_RECOIL_HIT,         90, NORMAL,        85 percent, 20,   0 percent},
    [THRASH]        = {THRASH,       EFFECT_RAMPAGE,            90, NORMAL,       100 percent, 20,   0 percent},
    [DOUBLE_EDGE]   = {DOUBLE_EDGE,  EFFECT_RECOIL_HIT,        120, NORMAL,       100 percent, 15,   0 percent},
    [TAIL_WHIP]     = {TAIL_WHIP,    EFFECT_DEFENSE_DOWN,        0, NORMAL,       100 percent, 30,   0 percent},
    [POISON_STING]  = {POISON_STING, EFFECT_POISON_HIT,         15, POISON,       100 percent, 35,  30 percent},
    [TWINEEDLE]     = {TWINEEDLE,    EFFECT_POISON_MULTI_HIT,   25, BUG,          100 percent, 20,  20 percent},
    [PIN_MISSILE]   = {PIN_MISSILE,  EFFECT_MULTI_HIT,          14, BUG,           85 percent, 20,   0 percent},
    [LEER]          = {LEER,         EFFECT_DEFENSE_DOWN,        0, NORMAL,       100 percent, 30,   0 percent},
    [BITE]          = {BITE,         EFFECT_FLINCH_HIT,         60, DARK,         100 percent, 25,  30 percent},
    [GROWL]         = {GROWL,        EFFECT_ATTACK_DOWN,         0, NORMAL,       100 percent, 40,   0 percent},
    [ROAR]          = {ROAR,         EFFECT_FORCE_SWITCH,        0, NORMAL,       100 percent, 20,   0 percent},
    [SING]          = {SING,         EFFECT_SLEEP,               0, NORMAL,        55 percent, 15,   0 percent},
    [SUPERSONIC]    = {SUPERSONIC,   EFFECT_CONFUSE,             0, NORMAL,        55 percent, 20,   0 percent},
    [SONICBOOM]     = {SONICBOOM,    EFFECT_STATIC_DAMAGE,      20, NORMAL,        90 percent, 20,   0 percent},
    [DISABLE]       = {DISABLE,      EFFECT_DISABLE,             0, NORMAL,        55 percent, 20,   0 percent},
    [ACID]          = {ACID,         EFFECT_DEFENSE_DOWN_HIT,   40, POISON,       100 percent, 30,  10 percent},
    [EMBER]         = {EMBER,        EFFECT_BURN_HIT,           40, FIRE,         100 percent, 25,  10 percent},
    [FLAMETHROWER]  = {FLAMETHROWER, EFFECT_BURN_HIT,           95, FIRE,         100 percent, 15,  10 percent},
    [MIST]          = {MIST,         EFFECT_MIST,                0, ICE,          100 percent, 30,   0 percent},
    [WATER_GUN]     = {WATER_GUN,    EFFECT_NORMAL_HIT,         40, WATER,        100 percent, 25,   0 percent},
    [HYDRO_PUMP]    = {HYDRO_PUMP,   EFFECT_NORMAL_HIT,        120, WATER,         80 percent,  5,   0 percent},
    [SURF]          = {SURF,         EFFECT_NORMAL_HIT,         95, WATER,        100 percent, 15,   0 percent},
    [ICE_BEAM]      = {ICE_BEAM,     EFFECT_FREEZE_HIT,         95, ICE,          100 percent, 10,  10 percent},
    [BLIZZARD]      = {BLIZZARD,     EFFECT_FREEZE_HIT,        120, ICE,           70 percent,  5,  10 percent},
    [PSYBEAM]       = {PSYBEAM,      EFFECT_CONFUSE_HIT,        65, PSYCHIC_TYPE, 100 percent, 20,  10 percent},
    [BUBBLEBEAM]    = {BUBBLEBEAM,   EFFECT_SPEED_DOWN_HIT,     65, WATER,        100 percent, 20,  10 percent},
    [AURORA_BEAM]   = {AURORA_BEAM,  EFFECT_ATTACK_DOWN_HIT,    65, ICE,          100 percent, 20,  10 percent},
    [HYPER_BEAM]    = {HYPER_BEAM,   EFFECT_HYPER_BEAM,        150, NORMAL,        90 percent,  5,   0 percent},
    [PECK]          = {PECK,         EFFECT_NORMAL_HIT,         35, FLYING,       100 percent, 35,   0 percent},
    [DRILL_PECK]    = {DRILL_PECK,   EFFECT_NORMAL_HIT,         80, FLYING,       100 percent, 20,   0 percent},
    [SUBMISSION]    = {SUBMISSION,   EFFECT_RECOIL_HIT,         80, FIGHTING,      80 percent, 25,   0 percent},
    [LOW_KICK]      = {LOW_KICK,     EFFECT_FLINCH_HIT,         50, FIGHTING,      90 percent, 20,  30 percent},
    [COUNTER]       = {COUNTER,      EFFECT_COUNTER,             1, FIGHTING,     100 percent, 20,   0 percent},
    [SEISMIC_TOSS]  = {SEISMIC_TOSS, EFFECT_LEVEL_DAMAGE,        1, FIGHTING,     100 percent, 20,   0 percent},
    [STRENGTH]      = {STRENGTH,     EFFECT_NORMAL_HIT,         80, NORMAL,       100 percent, 15,   0 percent},
    [ABSORB]        = {ABSORB,       EFFECT_LEECH_HIT,          20, GRASS,        100 percent, 20,   0 percent},
    [MEGA_DRAIN]    = {MEGA_DRAIN,   EFFECT_LEECH_HIT,          40, GRASS,        100 percent, 10,   0 percent},
    [LEECH_SEED]    = {LEECH_SEED,   EFFECT_LEECH_SEED,          0, GRASS,         90 percent, 10,   0 percent},
    [GROWTH]        = {GROWTH,       EFFECT_SP_ATK_UP,           0, NORMAL,       100 percent, 40,   0 percent},
    [RAZOR_LEAF]    = {RAZOR_LEAF,   EFFECT_NORMAL_HIT,         55, GRASS,         95 percent, 25,   0 percent},
    [SOLARBEAM]     = {SOLARBEAM,    EFFECT_SOLARBEAM,         120, GRASS,        100 percent, 10,   0 percent},
    [POISONPOWDER]  = {POISONPOWDER, EFFECT_POISON,              0, POISON,        75 percent, 35,   0 percent},
    [STUN_SPORE]    = {STUN_SPORE,   EFFECT_PARALYZE,            0, GRASS,         75 percent, 30,   0 percent},
    [SLEEP_POWDER]  = {SLEEP_POWDER, EFFECT_SLEEP,               0, GRASS,         75 percent, 15,   0 percent},
    [PETAL_DANCE]   = {PETAL_DANCE,  EFFECT_RAMPAGE,            70, GRASS,        100 percent, 20,   0 percent},
    [STRING_SHOT]   = {STRING_SHOT,  EFFECT_SPEED_DOWN,          0, BUG,           95 percent, 40,   0 percent},
    [DRAGON_RAGE]   = {DRAGON_RAGE,  EFFECT_STATIC_DAMAGE,      40, DRAGON,       100 percent, 10,   0 percent},
    [FIRE_SPIN]     = {FIRE_SPIN,    EFFECT_TRAP_TARGET,        15, FIRE,          70 percent, 15,   0 percent},
    [THUNDERSHOCK]  = {THUNDERSHOCK, EFFECT_PARALYZE_HIT,       40, ELECTRIC,     100 percent, 30,  10 percent},
    [THUNDERBOLT]   = {THUNDERBOLT,  EFFECT_PARALYZE_HIT,       95, ELECTRIC,     100 percent, 15,  10 percent},
    [THUNDER_WAVE]  = {THUNDER_WAVE, EFFECT_PARALYZE,            0, ELECTRIC,     100 percent, 20,   0 percent},
    [THUNDER]       = {THUNDER,      EFFECT_THUNDER,           120, ELECTRIC,      70 percent, 10,  30 percent},
    [ROCK_THROW]    = {ROCK_THROW,   EFFECT_NORMAL_HIT,         50, ROCK,          90 percent, 15,   0 percent},
    [EARTHQUAKE]    = {EARTHQUAKE,   EFFECT_EARTHQUAKE,        100, GROUND,       100 percent, 10,   0 percent},
    [FISSURE]       = {FISSURE,      EFFECT_OHKO,                1, GROUND,        30 percent,  5,   0 percent},
    [DIG]           = {DIG,          EFFECT_FLY,                60, GROUND,       100 percent, 10,   0 percent},
    [TOXIC]         = {TOXIC,        EFFECT_TOXIC,               0, POISON,        85 percent, 10,   0 percent},
    [CONFUSION]     = {CONFUSION,    EFFECT_CONFUSE_HIT,        50, PSYCHIC_TYPE, 100 percent, 25,  10 percent},
    [PSYCHIC_M]     = {PSYCHIC_M,    EFFECT_SP_DEF_DOWN_HIT,    90, PSYCHIC_TYPE, 100 percent, 10,  10 percent},
    [HYPNOSIS]      = {HYPNOSIS,     EFFECT_SLEEP,               0, PSYCHIC_TYPE,  60 percent, 20,   0 percent},
    [MEDITATE]      = {MEDITATE,     EFFECT_ATTACK_UP,           0, PSYCHIC_TYPE, 100 percent, 40,   0 percent},
    [AGILITY]       = {AGILITY,      EFFECT_SPEED_UP_2,          0, PSYCHIC_TYPE, 100 percent, 30,   0 percent},
    [QUICK_ATTACK]  = {QUICK_ATTACK, EFFECT_PRIORITY_HIT,       40, NORMAL,       100 percent, 30,   0 percent},
    [RAGE]          = {RAGE,         EFFECT_RAGE,               20, NORMAL,       100 percent, 20,   0 percent},
    [TELEPORT]      = {TELEPORT,     EFFECT_TELEPORT,            0, PSYCHIC_TYPE, 100 percent, 20,   0 percent},
    [NIGHT_SHADE]   = {NIGHT_SHADE,  EFFECT_LEVEL_DAMAGE,        1, GHOST,        100 percent, 15,   0 percent},
    [MIMIC]         = {MIMIC,        EFFECT_MIMIC,               0, NORMAL,       100 percent, 10,   0 percent},
    [SCREECH]       = {SCREECH,      EFFECT_DEFENSE_DOWN_2,      0, NORMAL,        85 percent, 40,   0 percent},
    [DOUBLE_TEAM]   = {DOUBLE_TEAM,  EFFECT_EVASION_UP,          0, NORMAL,       100 percent, 15,   0 percent},
    [RECOVER]       = {RECOVER,      EFFECT_HEAL,                0, NORMAL,       100 percent, 20,   0 percent},
    [HARDEN]        = {HARDEN,       EFFECT_DEFENSE_UP,          0, NORMAL,       100 percent, 30,   0 percent},
    [MINIMIZE]      = {MINIMIZE,     EFFECT_EVASION_UP,          0, NORMAL,       100 percent, 20,   0 percent},
    [SMOKESCREEN]   = {SMOKESCREEN,  EFFECT_ACCURACY_DOWN,       0, NORMAL,       100 percent, 20,   0 percent},
    [CONFUSE_RAY]   = {CONFUSE_RAY,  EFFECT_CONFUSE,             0, GHOST,        100 percent, 10,   0 percent},
    [WITHDRAW]      = {WITHDRAW,     EFFECT_DEFENSE_UP,          0, WATER,        100 percent, 40,   0 percent},
    [DEFENSE_CURL]  = {DEFENSE_CURL, EFFECT_DEFENSE_CURL,        0, NORMAL,       100 percent, 40,   0 percent},
    [BARRIER]       = {BARRIER,      EFFECT_DEFENSE_UP_2,        0, PSYCHIC_TYPE, 100 percent, 30,   0 percent},
    [LIGHT_SCREEN]  = {LIGHT_SCREEN, EFFECT_LIGHT_SCREEN,        0, PSYCHIC_TYPE, 100 percent, 30,   0 percent},
    [HAZE]          = {HAZE,         EFFECT_RESET_STATS,         0, ICE,          100 percent, 30,   0 percent},
    [REFLECT]       = {REFLECT,      EFFECT_REFLECT,             0, PSYCHIC_TYPE, 100 percent, 20,   0 percent},
    [FOCUS_ENERGY]  = {FOCUS_ENERGY, EFFECT_FOCUS_ENERGY,        0, NORMAL,       100 percent, 30,   0 percent},
    [BIDE]          = {BIDE,         EFFECT_BIDE,                0, NORMAL,       100 percent, 10,   0 percent},
    [METRONOME]     = {METRONOME,    EFFECT_METRONOME,           0, NORMAL,       100 percent, 10,   0 percent},
    [MIRROR_MOVE]   = {MIRROR_MOVE,  EFFECT_MIRROR_MOVE,         0, FLYING,       100 percent, 20,   0 percent},
    [SELFDESTRUCT]  = {SELFDESTRUCT, EFFECT_SELFDESTRUCT,      200, NORMAL,       100 percent,  5,   0 percent},
    [EGG_BOMB]      = {EGG_BOMB,     EFFECT_NORMAL_HIT,        100, NORMAL,        75 percent, 10,   0 percent},
    [LICK]          = {LICK,         EFFECT_PARALYZE_HIT,       20, GHOST,        100 percent, 30,  30 percent},
    [SMOG]          = {SMOG,         EFFECT_POISON_HIT,         20, POISON,        70 percent, 20,  40 percent},
    [SLUDGE]        = {SLUDGE,       EFFECT_POISON_HIT,         65, POISON,       100 percent, 20,  30 percent},
    [BONE_CLUB]     = {BONE_CLUB,    EFFECT_FLINCH_HIT,         65, GROUND,        85 percent, 20,  10 percent},
    [FIRE_BLAST]    = {FIRE_BLAST,   EFFECT_BURN_HIT,          120, FIRE,          85 percent,  5,  10 percent},
    [WATERFALL]     = {WATERFALL,    EFFECT_NORMAL_HIT,         80, WATER,        100 percent, 15,   0 percent},
    [CLAMP]         = {CLAMP,        EFFECT_TRAP_TARGET,        35, WATER,         75 percent, 10,   0 percent},
    [SWIFT]         = {SWIFT,        EFFECT_ALWAYS_HIT,         60, NORMAL,       100 percent, 20,   0 percent},
    [SKULL_BASH]    = {SKULL_BASH,   EFFECT_SKULL_BASH,        100, NORMAL,       100 percent, 15,   0 percent},
    [SPIKE_CANNON]  = {SPIKE_CANNON, EFFECT_MULTI_HIT,          20, NORMAL,       100 percent, 15,   0 percent},
    [CONSTRICT]     = {CONSTRICT,    EFFECT_SPEED_DOWN_HIT,     10, NORMAL,       100 percent, 35,  10 percent},
    [AMNESIA]       = {AMNESIA,      EFFECT_SP_DEF_UP_2,         0, PSYCHIC_TYPE, 100 percent, 20,   0 percent},
    [KINESIS]       = {KINESIS,      EFFECT_ACCURACY_DOWN,       0, PSYCHIC_TYPE,  80 percent, 15,   0 percent},
    [SOFTBOILED]    = {SOFTBOILED,   EFFECT_HEAL,                0, NORMAL,       100 percent, 10,   0 percent},
    [HI_JUMP_KICK]  = {HI_JUMP_KICK, EFFECT_JUMP_KICK,          85, FIGHTING,      90 percent, 20,   0 percent},
    [GLARE]         = {GLARE,        EFFECT_PARALYZE,            0, NORMAL,        75 percent, 30,   0 percent},
    [DREAM_EATER]   = {DREAM_EATER,  EFFECT_DREAM_EATER,       100, PSYCHIC_TYPE, 100 percent, 15,   0 percent},
    [POISON_GAS]    = {POISON_GAS,   EFFECT_POISON,              0, POISON,        55 percent, 40,   0 percent},
    [BARRAGE]       = {BARRAGE,      EFFECT_MULTI_HIT,          15, NORMAL,        85 percent, 20,   0 percent},
    [LEECH_LIFE]    = {LEECH_LIFE,   EFFECT_LEECH_HIT,          20, BUG,          100 percent, 15,   0 percent},
    [LOVELY_KISS]   = {LOVELY_KISS,  EFFECT_SLEEP,               0, NORMAL,        75 percent, 10,   0 percent},
    [SKY_ATTACK]    = {SKY_ATTACK,   EFFECT_SKY_ATTACK,        140, FLYING,        90 percent,  5,   0 percent},
    [TRANSFORM]     = {TRANSFORM,    EFFECT_TRANSFORM,           0, NORMAL,       100 percent, 10,   0 percent},
    [BUBBLE]        = {BUBBLE,       EFFECT_SPEED_DOWN_HIT,     20, WATER,        100 percent, 30,  10 percent},
    [DIZZY_PUNCH]   = {DIZZY_PUNCH,  EFFECT_CONFUSE_HIT,        70, NORMAL,       100 percent, 10,  20 percent},
    [SPORE]         = {SPORE,        EFFECT_SLEEP,               0, GRASS,        100 percent, 15,   0 percent},
    [FLASH]         = {FLASH,        EFFECT_ACCURACY_DOWN,       0, NORMAL,        70 percent, 20,   0 percent},
    [PSYWAVE]       = {PSYWAVE,      EFFECT_PSYWAVE,             1, PSYCHIC_TYPE,  80 percent, 15,   0 percent},
    [SPLASH]        = {SPLASH,       EFFECT_SPLASH,              0, NORMAL,       100 percent, 40,   0 percent},
    [ACID_ARMOR]    = {ACID_ARMOR,   EFFECT_DEFENSE_UP_2,        0, POISON,       100 percent, 40,   0 percent},
    [CRABHAMMER]    = {CRABHAMMER,   EFFECT_NORMAL_HIT,         90, WATER,         85 percent, 10,   0 percent},
    [EXPLOSION]     = {EXPLOSION,    EFFECT_SELFDESTRUCT,      250, NORMAL,       100 percent,  5,   0 percent},
    [FURY_SWIPES]   = {FURY_SWIPES,  EFFECT_MULTI_HIT,          18, NORMAL,        80 percent, 15,   0 percent},
    [BONEMERANG]    = {BONEMERANG,   EFFECT_DOUBLE_HIT,         50, GROUND,        90 percent, 10,   0 percent},
    [REST]          = {REST,         EFFECT_HEAL,                0, PSYCHIC_TYPE, 100 percent, 10,   0 percent},
    [ROCK_SLIDE]    = {ROCK_SLIDE,   EFFECT_FLINCH_HIT,         75, ROCK,          90 percent, 10,  30 percent},
    [HYPER_FANG]    = {HYPER_FANG,   EFFECT_FLINCH_HIT,         80, NORMAL,        90 percent, 15,  10 percent},
    [SHARPEN]       = {SHARPEN,      EFFECT_ATTACK_UP,           0, NORMAL,       100 percent, 30,   0 percent},
    [CONVERSION]    = {CONVERSION,   EFFECT_CONVERSION,          0, NORMAL,       100 percent, 30,   0 percent},
    [TRI_ATTACK]    = {TRI_ATTACK,   EFFECT_TRI_ATTACK,         80, NORMAL,       100 percent, 10,  20 percent},
    [SUPER_FANG]    = {SUPER_FANG,   EFFECT_SUPER_FANG,          1, NORMAL,        90 percent, 10,   0 percent},
    [SLASH]         = {SLASH,        EFFECT_NORMAL_HIT,         70, NORMAL,       100 percent, 20,   0 percent},
    [SUBSTITUTE]    = {SUBSTITUTE,   EFFECT_SUBSTITUTE,          0, NORMAL,       100 percent, 10,   0 percent},
    [STRUGGLE]      = {STRUGGLE,     EFFECT_RECOIL_HIT,         50, NORMAL,       100 percent,  1,   0 percent},
    [SKETCH]        = {SKETCH,       EFFECT_SKETCH,              0, NORMAL,       100 percent,  1,   0 percent},
    [TRIPLE_KICK]   = {TRIPLE_KICK,  EFFECT_TRIPLE_KICK,        10, FIGHTING,      90 percent, 10,   0 percent},
    [THIEF]         = {THIEF,        EFFECT_THIEF,              40, DARK,         100 percent, 10, 100 percent},
    [SPIDER_WEB]    = {SPIDER_WEB,   EFFECT_MEAN_LOOK,           0, BUG,          100 percent, 10,   0 percent},
    [MIND_READER]   = {MIND_READER,  EFFECT_LOCK_ON,             0, NORMAL,       100 percent,  5,   0 percent},
    [NIGHTMARE]     = {NIGHTMARE,    EFFECT_NIGHTMARE,           0, GHOST,        100 percent, 15,   0 percent},
    [FLAME_WHEEL]   = {FLAME_WHEEL,  EFFECT_FLAME_WHEEL,        60, FIRE,         100 percent, 25,  10 percent},
    [SNORE]         = {SNORE,        EFFECT_SNORE,              40, NORMAL,       100 percent, 15,  30 percent},
    [CURSE]         = {CURSE,        EFFECT_CURSE,               0, CURSE_TYPE,   100 percent, 10,   0 percent},
    [FLAIL]         = {FLAIL,        EFFECT_REVERSAL,            1, NORMAL,       100 percent, 15,   0 percent},
    [CONVERSION2]   = {CONVERSION2,  EFFECT_CONVERSION2,         0, NORMAL,       100 percent, 30,   0 percent},
    [AEROBLAST]     = {AEROBLAST,    EFFECT_NORMAL_HIT,        100, FLYING,        95 percent,  5,   0 percent},
    [COTTON_SPORE]  = {COTTON_SPORE, EFFECT_SPEED_DOWN_2,        0, GRASS,         85 percent, 40,   0 percent},
    [REVERSAL]      = {REVERSAL,     EFFECT_REVERSAL,            1, FIGHTING,     100 percent, 15,   0 percent},
    [SPITE]         = {SPITE,        EFFECT_SPITE,               0, GHOST,        100 percent, 10,   0 percent},
    [POWDER_SNOW]   = {POWDER_SNOW,  EFFECT_FREEZE_HIT,         40, ICE,          100 percent, 25,  10 percent},
    [PROTECT]       = {PROTECT,      EFFECT_PROTECT,             0, NORMAL,       100 percent, 10,   0 percent},
    [MACH_PUNCH]    = {MACH_PUNCH,   EFFECT_PRIORITY_HIT,       40, FIGHTING,     100 percent, 30,   0 percent},
    [SCARY_FACE]    = {SCARY_FACE,   EFFECT_SPEED_DOWN_2,        0, NORMAL,        90 percent, 10,   0 percent},
    [FAINT_ATTACK]  = {FAINT_ATTACK, EFFECT_ALWAYS_HIT,         60, DARK,         100 percent, 20,   0 percent},
    [SWEET_KISS]    = {SWEET_KISS,   EFFECT_CONFUSE,             0, NORMAL,        75 percent, 10,   0 percent},
    [BELLY_DRUM]    = {BELLY_DRUM,   EFFECT_BELLY_DRUM,          0, NORMAL,       100 percent, 10,   0 percent},
    [SLUDGE_BOMB]   = {SLUDGE_BOMB,  EFFECT_POISON_HIT,         90, POISON,       100 percent, 10,  30 percent},
    [MUD_SLAP]      = {MUD_SLAP,     EFFECT_ACCURACY_DOWN_HIT,  20, GROUND,       100 percent, 10, 100 percent},
    [OCTAZOOKA]     = {OCTAZOOKA,    EFFECT_ACCURACY_DOWN_HIT,  65, WATER,         85 percent, 10,  50 percent},
    [SPIKES]        = {SPIKES,       EFFECT_SPIKES,              0, GROUND,       100 percent, 20,   0 percent},
    [ZAP_CANNON]    = {ZAP_CANNON,   EFFECT_PARALYZE_HIT,      100, ELECTRIC,      50 percent,  5, 100 percent},
    [FORESIGHT]     = {FORESIGHT,    EFFECT_FORESIGHT,           0, NORMAL,       100 percent, 40,   0 percent},
    [DESTINY_BOND]  = {DESTINY_BOND, EFFECT_DESTINY_BOND,        0, GHOST,        100 percent,  5,   0 percent},
    [PERISH_SONG]   = {PERISH_SONG,  EFFECT_PERISH_SONG,         0, NORMAL,       100 percent,  5,   0 percent},
    [ICY_WIND]      = {ICY_WIND,     EFFECT_SPEED_DOWN_HIT,     55, ICE,           95 percent, 15, 100 percent},
    [DETECT]        = {DETECT,       EFFECT_PROTECT,             0, FIGHTING,     100 percent,  5,   0 percent},
    [BONE_RUSH]     = {BONE_RUSH,    EFFECT_MULTI_HIT,          25, GROUND,        80 percent, 10,   0 percent},
    [LOCK_ON]       = {LOCK_ON,      EFFECT_LOCK_ON,             0, NORMAL,       100 percent,  5,   0 percent},
    [OUTRAGE]       = {OUTRAGE,      EFFECT_RAMPAGE,            90, DRAGON,       100 percent, 15,   0 percent},
    [SANDSTORM]     = {SANDSTORM,    EFFECT_SANDSTORM,           0, ROCK,         100 percent, 10,   0 percent},
    [GIGA_DRAIN]    = {GIGA_DRAIN,   EFFECT_LEECH_HIT,          60, GRASS,        100 percent,  5,   0 percent},
    [ENDURE]        = {ENDURE,       EFFECT_ENDURE,              0, NORMAL,       100 percent, 10,   0 percent},
    [CHARM]         = {CHARM,        EFFECT_ATTACK_DOWN_2,       0, NORMAL,       100 percent, 20,   0 percent},
    [ROLLOUT]       = {ROLLOUT,      EFFECT_ROLLOUT,            30, ROCK,          90 percent, 20,   0 percent},
    [FALSE_SWIPE]   = {FALSE_SWIPE,  EFFECT_FALSE_SWIPE,        40, NORMAL,       100 percent, 40,   0 percent},
    [SWAGGER]       = {SWAGGER,      EFFECT_SWAGGER,             0, NORMAL,        90 percent, 15, 100 percent},
    [MILK_DRINK]    = {MILK_DRINK,   EFFECT_HEAL,                0, NORMAL,       100 percent, 10,   0 percent},
    [SPARK]         = {SPARK,        EFFECT_PARALYZE_HIT,       65, ELECTRIC,     100 percent, 20,  30 percent},
    [FURY_CUTTER]   = {FURY_CUTTER,  EFFECT_FURY_CUTTER,        10, BUG,           95 percent, 20,   0 percent},
    [STEEL_WING]    = {STEEL_WING,   EFFECT_DEFENSE_UP_HIT,     70, STEEL,         90 percent, 25,  10 percent},
    [MEAN_LOOK]     = {MEAN_LOOK,    EFFECT_MEAN_LOOK,           0, NORMAL,       100 percent,  5,   0 percent},
    [ATTRACT]       = {ATTRACT,      EFFECT_ATTRACT,             0, NORMAL,       100 percent, 15,   0 percent},
    [SLEEP_TALK]    = {SLEEP_TALK,   EFFECT_SLEEP_TALK,          0, NORMAL,       100 percent, 10,   0 percent},
    [HEAL_BELL]     = {HEAL_BELL,    EFFECT_HEAL_BELL,           0, NORMAL,       100 percent,  5,   0 percent},
    [RETURN]        = {RETURN,       EFFECT_RETURN,              1, NORMAL,       100 percent, 20,   0 percent},
    [PRESENT]       = {PRESENT,      EFFECT_PRESENT,             1, NORMAL,        90 percent, 15,   0 percent},
    [FRUSTRATION]   = {FRUSTRATION,  EFFECT_FRUSTRATION,         1, NORMAL,       100 percent, 20,   0 percent},
    [SAFEGUARD]     = {SAFEGUARD,    EFFECT_SAFEGUARD,           0, NORMAL,       100 percent, 25,   0 percent},
    [PAIN_SPLIT]    = {PAIN_SPLIT,   EFFECT_PAIN_SPLIT,          0, NORMAL,       100 percent, 20,   0 percent},
    [SACRED_FIRE]   = {SACRED_FIRE,  EFFECT_SACRED_FIRE,       100, FIRE,          95 percent,  5,  50 percent},
    [MAGNITUDE]     = {MAGNITUDE,    EFFECT_MAGNITUDE,           1, GROUND,       100 percent, 30,   0 percent},
    [DYNAMICPUNCH]  = {DYNAMICPUNCH, EFFECT_CONFUSE_HIT,       100, FIGHTING,      50 percent,  5, 100 percent},
    [MEGAHORN]      = {MEGAHORN,     EFFECT_NORMAL_HIT,        120, BUG,           85 percent, 10,   0 percent},
    [DRAGONBREATH]  = {DRAGONBREATH, EFFECT_PARALYZE_HIT,       60, DRAGON,       100 percent, 20,  30 percent},
    [BATON_PASS]    = {BATON_PASS,   EFFECT_BATON_PASS,          0, NORMAL,       100 percent, 40,   0 percent},
    [ENCORE]        = {ENCORE,       EFFECT_ENCORE,              0, NORMAL,       100 percent,  5,   0 percent},
    [PURSUIT]       = {PURSUIT,      EFFECT_PURSUIT,            40, DARK,         100 percent, 20,   0 percent},
    [RAPID_SPIN]    = {RAPID_SPIN,   EFFECT_RAPID_SPIN,         20, NORMAL,       100 percent, 40,   0 percent},
    [SWEET_SCENT]   = {SWEET_SCENT,  EFFECT_EVASION_DOWN,        0, NORMAL,       100 percent, 20,   0 percent},
    [IRON_TAIL]     = {IRON_TAIL,    EFFECT_DEFENSE_DOWN_HIT,  100, STEEL,         75 percent, 15,  30 percent},
    [METAL_CLAW]    = {METAL_CLAW,   EFFECT_ATTACK_UP_HIT,      50, STEEL,         95 percent, 35,  10 percent},
    [VITAL_THROW]   = {VITAL_THROW,  EFFECT_ALWAYS_HIT,         70, FIGHTING,     100 percent, 10,   0 percent},
    [MORNING_SUN]   = {MORNING_SUN,  EFFECT_MORNING_SUN,         0, NORMAL,       100 percent,  5,   0 percent},
    [SYNTHESIS]     = {SYNTHESIS,    EFFECT_SYNTHESIS,           0, GRASS,        100 percent,  5,   0 percent},
    [MOONLIGHT]     = {MOONLIGHT,    EFFECT_MOONLIGHT,           0, NORMAL,       100 percent,  5,   0 percent},
    [HIDDEN_POWER]  = {HIDDEN_POWER, EFFECT_HIDDEN_POWER,        1, NORMAL,       100 percent, 15,   0 percent},
    [CROSS_CHOP]    = {CROSS_CHOP,   EFFECT_NORMAL_HIT,        100, FIGHTING,      80 percent,  5,   0 percent},
    [TWISTER]       = {TWISTER,      EFFECT_TWISTER,            40, DRAGON,       100 percent, 20,  20 percent},
    [RAIN_DANCE]    = {RAIN_DANCE,   EFFECT_RAIN_DANCE,          0, WATER,         90 percent,  5,   0 percent},
    [SUNNY_DAY]     = {SUNNY_DAY,    EFFECT_SUNNY_DAY,           0, FIRE,          90 percent,  5,   0 percent},
    [CRUNCH]        = {CRUNCH,       EFFECT_SP_DEF_DOWN_HIT,    80, DARK,         100 percent, 15,  20 percent},
    [MIRROR_COAT]   = {MIRROR_COAT,  EFFECT_MIRROR_COAT,         1, PSYCHIC_TYPE, 100 percent, 20,   0 percent},
    [PSYCH_UP]      = {PSYCH_UP,     EFFECT_PSYCH_UP,            0, NORMAL,       100 percent, 10,   0 percent},
    [EXTREMESPEED]  = {EXTREMESPEED, EFFECT_PRIORITY_HIT,       80, NORMAL,       100 percent,  5,   0 percent},
    [ANCIENTPOWER]  = {ANCIENTPOWER, EFFECT_ALL_UP_HIT,         60, ROCK,         100 percent,  5,  10 percent},
    [SHADOW_BALL]   = {SHADOW_BALL,  EFFECT_SP_DEF_DOWN_HIT,    80, GHOST,        100 percent, 15,  20 percent},
    [FUTURE_SIGHT]  = {FUTURE_SIGHT, EFFECT_FUTURE_SIGHT,       80, PSYCHIC_TYPE,  90 percent, 15,   0 percent},
    [ROCK_SMASH]    = {ROCK_SMASH,   EFFECT_DEFENSE_DOWN_HIT,   20, FIGHTING,     100 percent, 15,  50 percent},
    [WHIRLPOOL]     = {WHIRLPOOL,    EFFECT_TRAP_TARGET,        15, WATER,         70 percent, 15,   0 percent},
    [BEAT_UP]       = {BEAT_UP,      EFFECT_BEAT_UP,            10, DARK,         100 percent, 10,   0 percent},
};

static_assert(lengthof(Moves) == NUM_ATTACKS + 1, "");
