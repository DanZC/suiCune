// significant level values
#define MAX_LEVEL 100
#define MIN_LEVEL 2
#define EGG_LEVEL 5

// maximum moves known per mon
#define NUM_MOVES 4

// significant stat values
#define BASE_STAT_LEVEL 7
#define MAX_STAT_LEVEL 13

// turns that sleep lasts
#define REST_SLEEP_TURNS 2
#define TREEMON_SLEEP_TURNS 7

// default move priority
#define BASE_PRIORITY 1

// type effectiveness factors, scaled by 10
#define SUPER_EFFECTIVE 20
#define MORE_EFFECTIVE 15
#define EFFECTIVE 10
#define NOT_VERY_EFFECTIVE 05
#define NO_EFFECT 00

// enemy AI behavior
#define BASE_AI_SWITCH_SCORE 10

// wPlayerStatLevels and wEnemyStatLevels indexes (see wram.asm)
// GetStatName arguments (see data/battle/stat_names.asm)
enum {
    ATTACK,
    DEFENSE,
    SPEED,
    SP_ATTACK,
    SP_DEFENSE,
    ACCURACY,
    EVASION,
    ABILITY,  // used for BattleCommand_Curse
    NUM_LEVEL_STATS,
};

// move struct members (see data/moves/moves.asm)
enum {
    MOVE_ANIM,    // 0
    MOVE_EFFECT,  // 1
    MOVE_POWER,   // 2
    MOVE_TYPE,    // 3
    MOVE_ACC,     // 4
    MOVE_PP,      // 5
    MOVE_CHANCE,  // 6
    MOVE_LENGTH,
};

// stat constants
// indexes for:
// - wPlayerStats and wEnemyStats (see wram.asm)
// - party_struct and battle_struct members (see macros/wram.asm)
enum {
    STAT_HP = 1,
    STAT_ATK,
    STAT_DEF,
    STAT_SPD,
    STAT_SATK,
    STAT_SDEF,
};
#define NUM_EXP_STATS STAT_SATK
#define NUM_STATS STAT_SDEF
#define NUM_BATTLE_STATS (NUM_STATS - 1)  // don't count HP

// stat formula constants
#define STAT_MIN_NORMAL 5
#define STAT_MIN_HP 10

#define MAX_STAT_VALUE 999

// shiny dvs
#define ATKDEFDV_SHINY 0xEA
#define SPDSPCDV_SHINY 0xAA

// battle classes (wBattleMode values)
enum {
    WILD_BATTLE,
    TRAINER_BATTLE,
};

// battle types (wBattleType values)
enum {
    BATTLETYPE_NORMAL,
    BATTLETYPE_CANLOSE,
    BATTLETYPE_DEBUG,
    BATTLETYPE_TUTORIAL,
    BATTLETYPE_FISH,
    BATTLETYPE_ROAMING,
    BATTLETYPE_CONTEST,
    BATTLETYPE_SHINY,
    BATTLETYPE_TREE,
    BATTLETYPE_TRAP,
    BATTLETYPE_FORCEITEM,
    BATTLETYPE_CELEBI,
    BATTLETYPE_SUICUNE,
};

// BattleVarPairs indexes (see home/battle_vars.asm)
enum {
    BATTLE_VARS_SUBSTATUS1,
    BATTLE_VARS_SUBSTATUS2,
    BATTLE_VARS_SUBSTATUS3,
    BATTLE_VARS_SUBSTATUS4,
    BATTLE_VARS_SUBSTATUS5,
    BATTLE_VARS_SUBSTATUS1_OPP,
    BATTLE_VARS_SUBSTATUS2_OPP,
    BATTLE_VARS_SUBSTATUS3_OPP,
    BATTLE_VARS_SUBSTATUS4_OPP,
    BATTLE_VARS_SUBSTATUS5_OPP,
    BATTLE_VARS_STATUS,
    BATTLE_VARS_STATUS_OPP,
    BATTLE_VARS_MOVE_ANIM,
    BATTLE_VARS_MOVE_EFFECT,
    BATTLE_VARS_MOVE_POWER,
    BATTLE_VARS_MOVE_TYPE,
    BATTLE_VARS_MOVE,
    BATTLE_VARS_LAST_COUNTER_MOVE,
    BATTLE_VARS_LAST_COUNTER_MOVE_OPP,
    BATTLE_VARS_LAST_MOVE,
    BATTLE_VARS_LAST_MOVE_OPP,
    NUM_BATTLE_VARS,
};

// BattleVarLocations indexes (see home/battle_vars.asm)
enum {  // Should always be in pairs
    PLAYER_SUBSTATUS_1,
    ENEMY_SUBSTATUS_1,
    PLAYER_SUBSTATUS_2,
    ENEMY_SUBSTATUS_2,
    PLAYER_SUBSTATUS_3,
    ENEMY_SUBSTATUS_3,
    PLAYER_SUBSTATUS_4,
    ENEMY_SUBSTATUS_4,
    PLAYER_SUBSTATUS_5,
    ENEMY_SUBSTATUS_5,
    PLAYER_STATUS,
    ENEMY_STATUS,
    PLAYER_MOVE_ANIMATION,
    ENEMY_MOVE_ANIMATION,
    PLAYER_MOVE_EFFECT,
    ENEMY_MOVE_EFFECT,
    PLAYER_MOVE_POWER,
    ENEMY_MOVE_POWER,
    PLAYER_MOVE_TYPE,
    ENEMY_MOVE_TYPE,
    PLAYER_CUR_MOVE,
    ENEMY_CUR_MOVE,
    PLAYER_COUNTER_MOVE,
    ENEMY_COUNTER_MOVE,
    PLAYER_LAST_MOVE,
    ENEMY_LAST_MOVE,
};

#define NUM_BATTLE_VAR_LOCATION_PAIRS ((ENEMY_LAST_MOVE + 1) / 2)

// status condition bit flags
#define SLP 0b111  // 0-7 turns
enum {
    PSN,
    BRN,
    FRZ,
    PAR,
};

#define ALL_STATUS ((1 << PSN) | (1 << BRN) | (1 << FRZ) | (1 << PAR) | SLP)

// wPlayerSubStatus1 or wEnemySubStatus1 bit flags
enum {
    SUBSTATUS_NIGHTMARE,
    SUBSTATUS_CURSE,
    SUBSTATUS_PROTECT,
    SUBSTATUS_IDENTIFIED,
    SUBSTATUS_PERISH,
    SUBSTATUS_ENDURE,
    SUBSTATUS_ROLLOUT,
    SUBSTATUS_IN_LOVE,
};

// wPlayerSubStatus2 or wEnemySubStatus2 bit flags
enum {
    SUBSTATUS_CURLED,
};

// wPlayerSubStatus3 or wEnemySubStatus3 bit flags
enum {
    SUBSTATUS_BIDE,
    SUBSTATUS_RAMPAGE,
    SUBSTATUS_IN_LOOP,
    SUBSTATUS_FLINCHED,
    SUBSTATUS_CHARGED,
    SUBSTATUS_UNDERGROUND,
    SUBSTATUS_FLYING,
    SUBSTATUS_CONFUSED,
};

// wPlayerSubStatus4 or wEnemySubStatus4 bit flags
enum {
    SUBSTATUS_X_ACCURACY,
    SUBSTATUS_MIST,
    SUBSTATUS_FOCUS_ENERGY,
    SUBSTATUS_SUBSTITUTE = 4,
    SUBSTATUS_RECHARGE,
    SUBSTATUS_RAGE,
    SUBSTATUS_LEECH_SEED,
};

// wPlayerSubStatus5 or wEnemySubStatus5 bit flags
enum {
    SUBSTATUS_TOXIC,
    SUBSTATUS_TRANSFORMED = 3,
    SUBSTATUS_ENCORED,
    SUBSTATUS_LOCK_ON,
    SUBSTATUS_DESTINY_BOND,
    SUBSTATUS_CANT_RUN,
};

// wPlayerScreens or wEnemyScreens bit flags
enum {
    SCREENS_SPIKES,
    SCREENS_SAFEGUARD = 2,
    SCREENS_LIGHT_SCREEN,
    SCREENS_REFLECT,
};

// values in wBattleWeather
enum {
    WEATHER_NONE,
    WEATHER_RAIN,
    WEATHER_SUN,
    WEATHER_SANDSTORM,
    WEATHER_RAIN_END,
    WEATHER_SUN_END,
    WEATHER_SANDSTORM_END,
};

// wBattleAction
enum {
    BATTLEACTION_MOVE1,
    BATTLEACTION_MOVE2,
    BATTLEACTION_MOVE3,
    BATTLEACTION_MOVE4,
    BATTLEACTION_SWITCH1,
    BATTLEACTION_SWITCH2,
    BATTLEACTION_SWITCH3,
    BATTLEACTION_SWITCH4,
    BATTLEACTION_SWITCH5,
    BATTLEACTION_SWITCH6,
    BATTLEACTION_SKIPTURN = 13,
    BATTLEACTION_STRUGGLE,
    BATTLEACTION_FORFEIT,
};

// wBattlePlayerAction
enum {
    BATTLEPLAYERACTION_USEMOVE,
    BATTLEPLAYERACTION_USEITEM,
    BATTLEPLAYERACTION_SWITCH,
};

// wBattleResult
enum {
    WIN,
    LOSE,
    DRAW,
};

#define BATTLERESULT_CAUGHT_CELEBI 6
#define BATTLERESULT_BOX_FULL 7
#define BATTLERESULT_BITMASK ((1 << BATTLERESULT_CAUGHT_CELEBI) | (1 << BATTLERESULT_BOX_FULL))

// link_battle_record struct
#define LINK_BATTLE_RECORD_LENGTH (2 + (NAME_LENGTH - 1) + 2 * 3)
#define NUM_LINK_BATTLE_RECORDS 5
