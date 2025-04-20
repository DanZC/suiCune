// Boolean checks
#define FALSE 0
#define TRUE 1

// genders
#define MALE 0
#define FEMALE 1

// FlagAction arguments (see home/flag.asm)
enum {
    RESET_FLAG,
    SET_FLAG,
    CHECK_FLAG,
};

// G/S version ID: 0 = Gold, 1 = Silver (used by checkver)
// Mystery Gift uses incremented values 1 and 2
#define GS_VERSION 0
// Pokémon Pikachu 2, a step counter / virtual pet device (used by Mystery Gift)
#define POKEMON_PIKACHU_2_VERSION 3
#define RESERVED_GAME_VERSION 4

// save file corruption check values
#define SAVE_CHECK_VALUE_1 99
#define SAVE_CHECK_VALUE_2 127

// RTC halted check value
#define RTC_HALT_VALUE 0x1234

// time of day boundaries
#define MORN_HOUR 4   // 4 AM
#define DAY_HOUR 10   // 10 AM
#define NITE_HOUR 18  // 6 PM
#define NOON_HOUR 12  // 12 PM
#define MAX_HOUR 24   // 12 AM

// significant money values
#define START_MONEY 3000
#define MOM_MONEY 2300
#define MAX_MONEY 999999
#define MAX_COINS 9999

// link record
#define MAX_LINK_RECORD 9999

// day-care
#define MAX_DAY_CARE_EXP 0x500000

// hall of fame
#define HOF_MASTER_COUNT 200

// hBGMapMode constants
enum {
    BGMAPMODE_NONE,
    BGMAPMODE_UPDATE_TILES,
    BGMAPMODE_UPDATE_ATTRS,
    BGMAPMODE_UPDATE_VTILES1,
    BGMAPMODE_UPDATE_VATTRS1,
};
