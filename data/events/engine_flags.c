#include "../../constants.h"
#include "engine_flags.h"

#define WRAM_PTR(_x) (gb.wram + (0x1000 * MBANK(a##_x)) + (_x - WRAM0_Begin))
#define engine_flag(_x, _bit) {WRAM_PTR(_x) + (_bit / 8), _bit % 8}

const struct EngineFlag EngineFlags[] = {
    [ENGINE_RADIO_CARD] = {WRAM_PTR(wPokegearFlags), POKEGEAR_RADIO_CARD_F},
    [ENGINE_MAP_CARD] = {WRAM_PTR(wPokegearFlags), POKEGEAR_MAP_CARD_F},
    [ENGINE_PHONE_CARD] = {WRAM_PTR(wPokegearFlags), POKEGEAR_PHONE_CARD_F},
    [ENGINE_EXPN_CARD] = {WRAM_PTR(wPokegearFlags), POKEGEAR_EXPN_CARD_F},
    [ENGINE_POKEGEAR] = {WRAM_PTR(wPokegearFlags), POKEGEAR_OBTAINED_F},
    // day-care
    [ENGINE_DAY_CARE_MAN_HAS_EGG] = {WRAM_PTR(wDayCareMan), DAYCAREMAN_HAS_EGG_F},
    [ENGINE_DAY_CARE_MAN_HAS_MON] = {WRAM_PTR(wDayCareMan), DAYCAREMAN_HAS_MON_F},
    [ENGINE_DAY_CARE_LADY_HAS_MON] = {WRAM_PTR(wDayCareLady), DAYCARELADY_HAS_MON_F},

    [ENGINE_MOM_SAVING_MONEY] = {WRAM_PTR(wMomSavingMoney), MOM_SAVING_SOME_MONEY_F},
    [ENGINE_MOM_ACTIVE] = {WRAM_PTR(wMomSavingMoney), MOM_ACTIVE_F},

    // unused, possibly related to a 2-day timer
    [ENGINE_UNUSED_TWO_DAY_TIMER_ON] = {WRAM_PTR(wUnusedTwoDayTimerOn), 0},

    [ENGINE_POKEDEX] = {WRAM_PTR(wStatusFlags), STATUSFLAGS_POKEDEX_F},
    [ENGINE_UNOWN_DEX] = {WRAM_PTR(wStatusFlags), STATUSFLAGS_UNOWN_DEX_F},
    [ENGINE_CAUGHT_POKERUS] = {WRAM_PTR(wStatusFlags), STATUSFLAGS_CAUGHT_POKERUS_F},
    [ENGINE_ROCKET_SIGNAL_ON_CH20] = {WRAM_PTR(wStatusFlags), STATUSFLAGS_ROCKET_SIGNAL_F},
    [ENGINE_CREDITS_SKIP] = {WRAM_PTR(wStatusFlags), STATUSFLAGS_HALL_OF_FAME_F},
    [ENGINE_MAIN_MENU_MOBILE_CHOICES] = {WRAM_PTR(wStatusFlags), STATUSFLAGS_MAIN_MENU_MOBILE_CHOICES_F},

    [ENGINE_BUG_CONTEST_TIMER] = {WRAM_PTR(wStatusFlags2), STATUSFLAGS2_BUG_CONTEST_TIMER_F},
    [ENGINE_SAFARI_ZONE] = {WRAM_PTR(wStatusFlags2), STATUSFLAGS2_SAFARI_GAME_F},
    [ENGINE_ROCKETS_IN_RADIO_TOWER] = {WRAM_PTR(wStatusFlags2), STATUSFLAGS2_ROCKETS_IN_RADIO_TOWER_F},
    [ENGINE_BIKE_SHOP_CALL_ENABLED] = {WRAM_PTR(wStatusFlags2), STATUSFLAGS2_BIKE_SHOP_CALL_F},
    [ENGINE_15] = {WRAM_PTR(wStatusFlags2), STATUSFLAGS2_UNUSED_5_F},
    [ENGINE_REACHED_GOLDENROD] = {WRAM_PTR(wStatusFlags2), STATUSFLAGS2_REACHED_GOLDENROD_F},
    [ENGINE_ROCKETS_IN_MAHOGANY] = {WRAM_PTR(wStatusFlags2), STATUSFLAGS2_ROCKETS_IN_MAHOGANY_F},

    [ENGINE_STRENGTH_ACTIVE] = {WRAM_PTR(wBikeFlags), BIKEFLAGS_STRENGTH_ACTIVE_F},
    [ENGINE_ALWAYS_ON_BIKE] = {WRAM_PTR(wBikeFlags), BIKEFLAGS_ALWAYS_ON_BIKE_F},
    [ENGINE_DOWNHILL] = {WRAM_PTR(wBikeFlags), BIKEFLAGS_DOWNHILL_F},

    [ENGINE_ZEPHYRBADGE] = {WRAM_PTR(wJohtoBadges), ZEPHYRBADGE},
    [ENGINE_HIVEBADGE] = {WRAM_PTR(wJohtoBadges), HIVEBADGE},
    [ENGINE_PLAINBADGE] = {WRAM_PTR(wJohtoBadges), PLAINBADGE},
    [ENGINE_FOGBADGE] = {WRAM_PTR(wJohtoBadges), FOGBADGE},
    [ENGINE_MINERALBADGE] = {WRAM_PTR(wJohtoBadges), MINERALBADGE},
    [ENGINE_STORMBADGE] = {WRAM_PTR(wJohtoBadges), STORMBADGE},
    [ENGINE_GLACIERBADGE] = {WRAM_PTR(wJohtoBadges), GLACIERBADGE},
    [ENGINE_RISINGBADGE] = {WRAM_PTR(wJohtoBadges), RISINGBADGE},

    [ENGINE_BOULDERBADGE] = engine_flag(wKantoBadges, BOULDERBADGE),
    [ENGINE_CASCADEBADGE] = engine_flag(wKantoBadges, CASCADEBADGE),
    [ENGINE_THUNDERBADGE] = engine_flag(wKantoBadges, THUNDERBADGE),
    [ENGINE_RAINBOWBADGE] = engine_flag(wKantoBadges, RAINBOWBADGE),
    [ENGINE_SOULBADGE] = engine_flag(wKantoBadges, SOULBADGE),
    [ENGINE_MARSHBADGE] = engine_flag(wKantoBadges, MARSHBADGE),
    [ENGINE_VOLCANOBADGE] = engine_flag(wKantoBadges, VOLCANOBADGE),
    [ENGINE_EARTHBADGE] = engine_flag(wKantoBadges, EARTHBADGE),

// unown sets (see data/wild/unlocked_unowns.asm)
    [ENGINE_UNLOCKED_UNOWNS_A_TO_K]   = engine_flag(wUnlockedUnowns, 0), // A-K
    [ENGINE_UNLOCKED_UNOWNS_L_TO_R]   = engine_flag(wUnlockedUnowns, 1), // L-R
    [ENGINE_UNLOCKED_UNOWNS_S_TO_W]   = engine_flag(wUnlockedUnowns, 2), // S-W
    [ENGINE_UNLOCKED_UNOWNS_X_TO_Z]   = engine_flag(wUnlockedUnowns, 3), // X-Z
    [ENGINE_UNLOCKED_UNOWNS_UNUSED_4] = engine_flag(wUnlockedUnowns, 4), // unused
    [ENGINE_UNLOCKED_UNOWNS_UNUSED_5] = engine_flag(wUnlockedUnowns, 5), // unused
    [ENGINE_UNLOCKED_UNOWNS_UNUSED_6] = engine_flag(wUnlockedUnowns, 6), // unused
    [ENGINE_UNLOCKED_UNOWNS_UNUSED_7] = engine_flag(wUnlockedUnowns, 7), // unused
// fly
    // kanto
    [ENGINE_FLYPOINT_PLAYERS_HOUSE] = engine_flag(wVisitedSpawns, SPAWN_HOME),
    [ENGINE_FLYPOINT_DEBUG] = engine_flag(wVisitedSpawns, SPAWN_DEBUG),
    [ENGINE_FLYPOINT_PALLET] = engine_flag(wVisitedSpawns, SPAWN_PALLET),
    [ENGINE_FLYPOINT_VIRIDIAN] = engine_flag(wVisitedSpawns, SPAWN_VIRIDIAN),
    [ENGINE_FLYPOINT_PEWTER] = engine_flag(wVisitedSpawns, SPAWN_PEWTER),
    [ENGINE_FLYPOINT_CERULEAN] = engine_flag(wVisitedSpawns, SPAWN_CERULEAN),
    [ENGINE_FLYPOINT_ROCK_TUNNEL] = engine_flag(wVisitedSpawns, SPAWN_ROCK_TUNNEL),
    [ENGINE_FLYPOINT_VERMILION] = engine_flag(wVisitedSpawns, SPAWN_VERMILION),
    [ENGINE_FLYPOINT_LAVENDER] = engine_flag(wVisitedSpawns, SPAWN_LAVENDER),
    [ENGINE_FLYPOINT_SAFFRON] = engine_flag(wVisitedSpawns, SPAWN_SAFFRON),
    [ENGINE_FLYPOINT_CELADON] = engine_flag(wVisitedSpawns, SPAWN_CELADON),
    [ENGINE_FLYPOINT_FUCHSIA] = engine_flag(wVisitedSpawns, SPAWN_FUCHSIA),
    [ENGINE_FLYPOINT_CINNABAR] = engine_flag(wVisitedSpawns, SPAWN_CINNABAR),
    [ENGINE_FLYPOINT_INDIGO_PLATEAU] = engine_flag(wVisitedSpawns, SPAWN_INDIGO),
    // johto
    [ENGINE_FLYPOINT_NEW_BARK] = engine_flag(wVisitedSpawns, SPAWN_NEW_BARK),
    [ENGINE_FLYPOINT_CHERRYGROVE] = engine_flag(wVisitedSpawns, SPAWN_CHERRYGROVE),
    [ENGINE_FLYPOINT_VIOLET] = engine_flag(wVisitedSpawns, SPAWN_VIOLET),
    [ENGINE_FLYPOINT_AZALEA] = engine_flag(wVisitedSpawns, SPAWN_AZALEA),
    [ENGINE_FLYPOINT_CIANWOOD] = engine_flag(wVisitedSpawns, SPAWN_CIANWOOD),
    [ENGINE_FLYPOINT_GOLDENROD] = engine_flag(wVisitedSpawns, SPAWN_GOLDENROD),
    [ENGINE_FLYPOINT_OLIVINE] = engine_flag(wVisitedSpawns, SPAWN_OLIVINE),
    [ENGINE_FLYPOINT_ECRUTEAK] = engine_flag(wVisitedSpawns, SPAWN_ECRUTEAK),
    [ENGINE_FLYPOINT_MAHOGANY] = engine_flag(wVisitedSpawns, SPAWN_MAHOGANY),
    [ENGINE_FLYPOINT_LAKE_OF_RAGE] = engine_flag(wVisitedSpawns, SPAWN_LAKE_OF_RAGE),
    [ENGINE_FLYPOINT_BLACKTHORN] = engine_flag(wVisitedSpawns, SPAWN_BLACKTHORN),
    [ENGINE_FLYPOINT_SILVER_CAVE] = engine_flag(wVisitedSpawns, SPAWN_MT_SILVER),
    [ENGINE_FLYPOINT_UNUSED] = engine_flag(wVisitedSpawns, NUM_SPAWNS), // unused

// engine_flag wLuckyNumberShowFlag, LUCKYNUMBERSHOW_GAME_OVER_F
    [ENGINE_LUCKY_NUMBER_SHOW] = engine_flag(wLuckyNumberShowFlag, LUCKYNUMBERSHOW_GAME_OVER_F),

// engine_flag wStatusFlags2, STATUSFLAGS2_UNUSED_3_F
    [ENGINE_4F] = engine_flag(wStatusFlags2, STATUSFLAGS2_UNUSED_3_F),

    [ENGINE_KURT_MAKING_BALLS] = engine_flag(wDailyFlags1, DAILYFLAGS1_KURT_MAKING_BALLS_F),
    [ENGINE_DAILY_BUG_CONTEST] = engine_flag(wDailyFlags1, DAILYFLAGS1_BUG_CONTEST_F),
    [ENGINE_FISH_SWARM] = engine_flag(wDailyFlags1, DAILYFLAGS1_FISH_SWARM_F),
    [ENGINE_TIME_CAPSULE] = engine_flag(wDailyFlags1, DAILYFLAGS1_TIME_CAPSULE_F),
    [ENGINE_ALL_FRUIT_TREES] = engine_flag(wDailyFlags1, DAILYFLAGS1_ALL_FRUIT_TREES_F),
    [ENGINE_GOT_SHUCKIE_TODAY] = engine_flag(wDailyFlags1, DAILYFLAGS1_GOT_SHUCKIE_TODAY_F),
    [ENGINE_GOLDENROD_UNDERGROUND_MERCHANT_CLOSED] = engine_flag(wDailyFlags1, DAILYFLAGS1_GOLDENROD_UNDERGROUND_BARGAIN_F),
    [ENGINE_FOUGHT_IN_TRAINER_HALL_TODAY] = engine_flag(wDailyFlags1, DAILYFLAGS1_TRAINER_HOUSE_F),

    [ENGINE_MT_MOON_SQUARE_CLEFAIRY] = engine_flag(wDailyFlags2, DAILYFLAGS2_MT_MOON_SQUARE_CLEFAIRY_F),
    [ENGINE_UNION_CAVE_LAPRAS] = engine_flag(wDailyFlags2, DAILYFLAGS2_UNION_CAVE_LAPRAS_F),
    [ENGINE_GOLDENROD_UNDERGROUND_GOT_HAIRCUT] = engine_flag(wDailyFlags2, DAILYFLAGS2_GOLDENROD_UNDERGROUND_GOT_HAIRCUT_F),
    [ENGINE_GOLDENROD_DEPT_STORE_TM27_RETURN] = engine_flag(wDailyFlags2, DAILYFLAGS2_GOLDENROD_DEPT_STORE_TM27_RETURN_F),
    [ENGINE_DAISYS_GROOMING] = engine_flag(wDailyFlags2, DAILYFLAGS2_DAISYS_GROOMING_F),
    [ENGINE_INDIGO_PLATEAU_RIVAL_FIGHT] = engine_flag(wDailyFlags2, DAILYFLAGS2_INDIGO_PLATEAU_RIVAL_FIGHT_F),
    [ENGINE_DAILY_MOVE_TUTOR] = engine_flag(wDailyFlags2, DAILYFLAGS2_MOVE_TUTOR_F),
    [ENGINE_BUENAS_PASSWORD] = engine_flag(wDailyFlags2, DAILYFLAGS2_BUENAS_PASSWORD_F),

    [ENGINE_BUENAS_PASSWORD_2] = engine_flag(wSwarmFlags, SWARMFLAGS_BUENAS_PASSWORD_F),
    [ENGINE_GOLDENROD_DEPT_STORE_SALE_IS_ON] = engine_flag(wSwarmFlags, SWARMFLAGS_GOLDENROD_DEPT_STORE_SALE_F),

// engine_flag wGameTimerPaused, GAME_TIMER_MOBILE_F
    [ENGINE_62] = engine_flag(wGameTimerPaused, GAME_TIMER_MOBILE_F),

// engine_flag wPlayerGender, PLAYERGENDER_FEMALE_F
    [ENGINE_PLAYER_IS_FEMALE] = engine_flag(wPlayerGender, PLAYERGENDER_FEMALE_F),

// engine_flag wCelebiEvent, CELEBIEVENT_FOREST_IS_RESTLESS_F
    [ENGINE_FOREST_IS_RESTLESS] = engine_flag(wCelebiEvent, CELEBIEVENT_FOREST_IS_RESTLESS_F),

// rematches
    [ENGINE_JACK_READY_FOR_REMATCH] = engine_flag(wDailyRematchFlags, 0), // jack
    [ENGINE_HUEY_READY_FOR_REMATCH] = engine_flag(wDailyRematchFlags, 1), // huey
    [ENGINE_GAVEN_READY_FOR_REMATCH] = engine_flag(wDailyRematchFlags,  2), // gaven
    [ENGINE_BETH_READY_FOR_REMATCH] = engine_flag(wDailyRematchFlags,  3), // beth
    [ENGINE_JOSE_READY_FOR_REMATCH] = engine_flag(wDailyRematchFlags,  4), // jose
    [ENGINE_REENA_READY_FOR_REMATCH] = engine_flag(wDailyRematchFlags,  5), // reena
    [ENGINE_JOEY_READY_FOR_REMATCH] = engine_flag(wDailyRematchFlags,  6), // joey
    [ENGINE_WADE_READY_FOR_REMATCH] = engine_flag(wDailyRematchFlags,  7), // wade
    [ENGINE_RALPH_READY_FOR_REMATCH] = engine_flag(wDailyRematchFlags,  8), // ralph
    [ENGINE_LIZ_READY_FOR_REMATCH] = engine_flag(wDailyRematchFlags,  9), // liz
    [ENGINE_ANTHONY_READY_FOR_REMATCH] = engine_flag(wDailyRematchFlags, 10), // anthony
    [ENGINE_TODD_READY_FOR_REMATCH] = engine_flag(wDailyRematchFlags, 11), // todd
    [ENGINE_GINA_READY_FOR_REMATCH] = engine_flag(wDailyRematchFlags, 12), // gina
    [ENGINE_ARNIE_READY_FOR_REMATCH] = engine_flag(wDailyRematchFlags, 13), // arnie
    [ENGINE_ALAN_READY_FOR_REMATCH] = engine_flag(wDailyRematchFlags, 14), // alan
    [ENGINE_DANA_READY_FOR_REMATCH] = engine_flag(wDailyRematchFlags, 15), // dana
    [ENGINE_CHAD_READY_FOR_REMATCH] = engine_flag(wDailyRematchFlags, 16), // chad
    [ENGINE_TULLY_READY_FOR_REMATCH] = engine_flag(wDailyRematchFlags, 17), // tully
    [ENGINE_BRENT_READY_FOR_REMATCH] = engine_flag(wDailyRematchFlags, 18), // brent
    [ENGINE_TIFFANY_READY_FOR_REMATCH] = engine_flag(wDailyRematchFlags, 19), // tiffany
    [ENGINE_VANCE_READY_FOR_REMATCH] = engine_flag(wDailyRematchFlags, 20), // vance
    [ENGINE_WILTON_READY_FOR_REMATCH] = engine_flag(wDailyRematchFlags, 21), // wilton
    [ENGINE_PARRY_READY_FOR_REMATCH] = engine_flag(wDailyRematchFlags, 22), // parry
    [ENGINE_ERIN_READY_FOR_REMATCH] = engine_flag(wDailyRematchFlags, 23), // erin

    [ENGINE_BEVERLY_HAS_NUGGET] = engine_flag(wDailyPhoneItemFlags, 0), // beverly has nugget
    [ENGINE_JOSE_HAS_STAR_PIECE] = engine_flag(wDailyPhoneItemFlags, 1), // jose has star piece
    [ENGINE_WADE_HAS_ITEM] = engine_flag(wDailyPhoneItemFlags, 2), // wade has item (see EVENT_WADE_HAS_*** in constants/event_flags.h)
    [ENGINE_GINA_HAS_LEAF_STONE] = engine_flag(wDailyPhoneItemFlags, 3), // gina has leaf stone
    [ENGINE_ALAN_HAS_FIRE_STONE] = engine_flag(wDailyPhoneItemFlags, 4), // alan has fire stone
    [ENGINE_DANA_HAS_THUNDERSTONE] = engine_flag(wDailyPhoneItemFlags, 5), // liz (dana?) has thunderstone
    [ENGINE_DEREK_HAS_NUGGET] = engine_flag(wDailyPhoneItemFlags, 6), // derek has nugget
    [ENGINE_TULLY_HAS_WATER_STONE] = engine_flag(wDailyPhoneItemFlags, 7), // tully has water stone
    [ENGINE_TIFFANY_HAS_PINK_BOW] = engine_flag(wDailyPhoneItemFlags, 8), // tiffany has pink bow
    [ENGINE_WILTON_HAS_ITEM] = engine_flag(wDailyPhoneItemFlags, 9), // wilton has item (see EVENT_WILTON_HAS_*** in constants/event_flags.h)

    [ENGINE_JACK_MONDAY_MORNING] = engine_flag(wDailyPhoneTimeOfDayFlags,  0), // jack
    [ENGINE_HUEY_WEDNESDAY_NIGHT] = engine_flag(wDailyPhoneTimeOfDayFlags,  1), // huey
    [ENGINE_GAVEN_THURSDAY_MORNING] = engine_flag(wDailyPhoneTimeOfDayFlags,  2), // gaven
    [ENGINE_BETH_FRIDAY_AFTERNOON] = engine_flag(wDailyPhoneTimeOfDayFlags,  3), // beth
    [ENGINE_JOSE_SATURDAY_NIGHT] = engine_flag(wDailyPhoneTimeOfDayFlags,  4), // jose
    [ENGINE_REENA_SUNDAY_MORNING] = engine_flag(wDailyPhoneTimeOfDayFlags,  5), // reena
    [ENGINE_JOEY_MONDAY_AFTERNOON] = engine_flag(wDailyPhoneTimeOfDayFlags,  6), // joey
    [ENGINE_WADE_TUESDAY_NIGHT] = engine_flag(wDailyPhoneTimeOfDayFlags,  7), // wade
    [ENGINE_RALPH_WEDNESDAY_MORNING] = engine_flag(wDailyPhoneTimeOfDayFlags,  8), // ralph
    [ENGINE_LIZ_THURSDAY_AFTERNOON] = engine_flag(wDailyPhoneTimeOfDayFlags,  9), // liz
    [ENGINE_ANTHONY_FRIDAY_NIGHT] = engine_flag(wDailyPhoneTimeOfDayFlags, 10), // anthony
    [ENGINE_TODD_SATURDAY_MORNING] = engine_flag(wDailyPhoneTimeOfDayFlags, 11), // todd
    [ENGINE_GINA_SUNDAY_AFTERNOON] = engine_flag(wDailyPhoneTimeOfDayFlags, 12), // gina
    [ENGINE_ARNIE_TUESDAY_MORNING] = engine_flag(wDailyPhoneTimeOfDayFlags, 13), // arnie
    [ENGINE_ALAN_WEDNESDAY_AFTERNOON] = engine_flag(wDailyPhoneTimeOfDayFlags, 14), // alan
    [ENGINE_DANA_THURSDAY_NIGHT] = engine_flag(wDailyPhoneTimeOfDayFlags, 15), // dana
    [ENGINE_CHAD_FRIDAY_MORNING] = engine_flag(wDailyPhoneTimeOfDayFlags, 16), // chad
    [ENGINE_TULLY_SUNDAY_NIGHT] = engine_flag(wDailyPhoneTimeOfDayFlags, 17), // tully
    [ENGINE_BRENT_MONDAY_MORNING] = engine_flag(wDailyPhoneTimeOfDayFlags, 18), // brent
    [ENGINE_TIFFANY_TUESDAY_AFTERNOON] = engine_flag(wDailyPhoneTimeOfDayFlags, 19), // tiffany
    [ENGINE_VANCE_WEDNESDAY_NIGHT] = engine_flag(wDailyPhoneTimeOfDayFlags, 20), // vance
    [ENGINE_WILTON_THURSDAY_MORNING] = engine_flag(wDailyPhoneTimeOfDayFlags, 21), // wilton
    [ENGINE_PARRY_FRIDAY_AFTERNOON] = engine_flag(wDailyPhoneTimeOfDayFlags, 22), // parry
    [ENGINE_ERIN_SATURDAY_NIGHT] = engine_flag(wDailyPhoneTimeOfDayFlags, 23), // erin

    [ENGINE_KRIS_IN_CABLE_CLUB] = engine_flag(wPlayerSpriteSetupFlags, PLAYERSPRITESETUP_FEMALE_TO_MALE_F),

    [ENGINE_DUNSPARCE_SWARM] = engine_flag(wSwarmFlags, SWARMFLAGS_DUNSPARCE_SWARM_F),
    [ENGINE_YANMA_SWARM] = engine_flag(wSwarmFlags, SWARMFLAGS_YANMA_SWARM_F),
};

#if defined(__cplusplus) || defined(_MSC_VER)
static_assert(lengthof(EngineFlags) == NUM_ENGINE_FLAGS, "");
#else
_Static_assert(lengthof(EngineFlags) == NUM_ENGINE_FLAGS, "");
#endif