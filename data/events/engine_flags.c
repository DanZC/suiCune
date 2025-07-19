#include "../../constants.h"
#include "engine_flags.h"

#define engine_flag(_x, _bit) {wram_ptr(_x) + (_bit / 8), _bit % 8}
#define engine_flag_(_x, _bit) {_x + (_bit / 8), _bit % 8}

const struct EngineFlag EngineFlags[] = {
    [ENGINE_RADIO_CARD]                 = engine_flag_(&gPlayer.pokegearFlags, POKEGEAR_RADIO_CARD_F),
    [ENGINE_MAP_CARD]                   = engine_flag_(&gPlayer.pokegearFlags, POKEGEAR_MAP_CARD_F),
    [ENGINE_PHONE_CARD]                 = engine_flag_(&gPlayer.pokegearFlags, POKEGEAR_PHONE_CARD_F),
    [ENGINE_EXPN_CARD]                  = engine_flag_(&gPlayer.pokegearFlags, POKEGEAR_EXPN_CARD_F),
    [ENGINE_POKEGEAR]                   = engine_flag_(&gPlayer.pokegearFlags, POKEGEAR_OBTAINED_F),
    // day-care
    [ENGINE_DAY_CARE_MAN_HAS_EGG]       = engine_flag_(&gPokemon.dayCareMan, DAYCAREMAN_HAS_EGG_F),
    [ENGINE_DAY_CARE_MAN_HAS_MON]       = engine_flag_(&gPokemon.dayCareMan, DAYCAREMAN_HAS_MON_F),
    [ENGINE_DAY_CARE_LADY_HAS_MON]      = engine_flag_(&gPokemon.dayCareLady, DAYCARELADY_HAS_MON_F),

    [ENGINE_MOM_SAVING_MONEY]           = engine_flag_(&gPlayer.momSavingMoney, MOM_SAVING_SOME_MONEY_F),
    [ENGINE_MOM_ACTIVE]                 = engine_flag_(&gPlayer.momSavingMoney, MOM_ACTIVE_F),

    // unused, possibly related to a 2-day timer
    [ENGINE_UNUSED_TWO_DAY_TIMER_ON]    = engine_flag_(&gPlayer.unusedTwoDayTimerOn, 0),

    [ENGINE_POKEDEX]                    = engine_flag_(&gPlayer.statusFlags, STATUSFLAGS_POKEDEX_F),
    [ENGINE_UNOWN_DEX]                  = engine_flag_(&gPlayer.statusFlags, STATUSFLAGS_UNOWN_DEX_F),
    [ENGINE_CAUGHT_POKERUS]             = engine_flag_(&gPlayer.statusFlags, STATUSFLAGS_CAUGHT_POKERUS_F),
    [ENGINE_ROCKET_SIGNAL_ON_CH20]      = engine_flag_(&gPlayer.statusFlags, STATUSFLAGS_ROCKET_SIGNAL_F),
    [ENGINE_CREDITS_SKIP]               = engine_flag_(&gPlayer.statusFlags, STATUSFLAGS_HALL_OF_FAME_F),
    [ENGINE_MAIN_MENU_MOBILE_CHOICES]   = engine_flag_(&gPlayer.statusFlags, STATUSFLAGS_MAIN_MENU_MOBILE_CHOICES_F),

    [ENGINE_BUG_CONTEST_TIMER]          = engine_flag_(&gPlayer.statusFlags2, STATUSFLAGS2_BUG_CONTEST_TIMER_F),
    [ENGINE_SAFARI_ZONE]                = engine_flag_(&gPlayer.statusFlags2, STATUSFLAGS2_SAFARI_GAME_F),
    [ENGINE_ROCKETS_IN_RADIO_TOWER]     = engine_flag_(&gPlayer.statusFlags2, STATUSFLAGS2_ROCKETS_IN_RADIO_TOWER_F),
    [ENGINE_BIKE_SHOP_CALL_ENABLED]     = engine_flag_(&gPlayer.statusFlags2, STATUSFLAGS2_BIKE_SHOP_CALL_F),
    [ENGINE_15]                         = engine_flag_(&gPlayer.statusFlags2, STATUSFLAGS2_UNUSED_5_F),
    [ENGINE_REACHED_GOLDENROD]          = engine_flag_(&gPlayer.statusFlags2, STATUSFLAGS2_REACHED_GOLDENROD_F),
    [ENGINE_ROCKETS_IN_MAHOGANY]        = engine_flag_(&gPlayer.statusFlags2, STATUSFLAGS2_ROCKETS_IN_MAHOGANY_F),

    [ENGINE_STRENGTH_ACTIVE]            = engine_flag_(&gPlayer.bikeFlags, BIKEFLAGS_STRENGTH_ACTIVE_F),
    [ENGINE_ALWAYS_ON_BIKE]             = engine_flag_(&gPlayer.bikeFlags, BIKEFLAGS_ALWAYS_ON_BIKE_F),
    [ENGINE_DOWNHILL]                   = engine_flag_(&gPlayer.bikeFlags, BIKEFLAGS_DOWNHILL_F),

    [ENGINE_ZEPHYRBADGE]                = engine_flag_(gPlayer.johtoBadges, ZEPHYRBADGE),
    [ENGINE_HIVEBADGE]                  = engine_flag_(gPlayer.johtoBadges, HIVEBADGE),
    [ENGINE_PLAINBADGE]                 = engine_flag_(gPlayer.johtoBadges, PLAINBADGE),
    [ENGINE_FOGBADGE]                   = engine_flag_(gPlayer.johtoBadges, FOGBADGE),
    [ENGINE_MINERALBADGE]               = engine_flag_(gPlayer.johtoBadges, MINERALBADGE),
    [ENGINE_STORMBADGE]                 = engine_flag_(gPlayer.johtoBadges, STORMBADGE),
    [ENGINE_GLACIERBADGE]               = engine_flag_(gPlayer.johtoBadges, GLACIERBADGE),
    [ENGINE_RISINGBADGE]                = engine_flag_(gPlayer.johtoBadges, RISINGBADGE),

    [ENGINE_BOULDERBADGE]               = engine_flag_(gPlayer.kantoBadges, BOULDERBADGE),
    [ENGINE_CASCADEBADGE]               = engine_flag_(gPlayer.kantoBadges, CASCADEBADGE),
    [ENGINE_THUNDERBADGE]               = engine_flag_(gPlayer.kantoBadges, THUNDERBADGE),
    [ENGINE_RAINBOWBADGE]               = engine_flag_(gPlayer.kantoBadges, RAINBOWBADGE),
    [ENGINE_SOULBADGE]                  = engine_flag_(gPlayer.kantoBadges, SOULBADGE),
    [ENGINE_MARSHBADGE]                 = engine_flag_(gPlayer.kantoBadges, MARSHBADGE),
    [ENGINE_VOLCANOBADGE]               = engine_flag_(gPlayer.kantoBadges, VOLCANOBADGE),
    [ENGINE_EARTHBADGE]                 = engine_flag_(gPlayer.kantoBadges, EARTHBADGE),

// unown sets (see data/wild/unlocked_unowns.asm)
    [ENGINE_UNLOCKED_UNOWNS_A_TO_K]     = engine_flag_(&gPokemon.unlockedUnowns, 0), // A-K
    [ENGINE_UNLOCKED_UNOWNS_L_TO_R]     = engine_flag_(&gPokemon.unlockedUnowns, 1), // L-R
    [ENGINE_UNLOCKED_UNOWNS_S_TO_W]     = engine_flag_(&gPokemon.unlockedUnowns, 2), // S-W
    [ENGINE_UNLOCKED_UNOWNS_X_TO_Z]     = engine_flag_(&gPokemon.unlockedUnowns, 3), // X-Z
    [ENGINE_UNLOCKED_UNOWNS_UNUSED_4]   = engine_flag_(&gPokemon.unlockedUnowns, 4), // unused
    [ENGINE_UNLOCKED_UNOWNS_UNUSED_5]   = engine_flag_(&gPokemon.unlockedUnowns, 5), // unused
    [ENGINE_UNLOCKED_UNOWNS_UNUSED_6]   = engine_flag_(&gPokemon.unlockedUnowns, 6), // unused
    [ENGINE_UNLOCKED_UNOWNS_UNUSED_7]   = engine_flag_(&gPokemon.unlockedUnowns, 7), // unused
// fly
    // kanto
    [ENGINE_FLYPOINT_PLAYERS_HOUSE] = engine_flag_(gCurMapData.visitedSpawns, SPAWN_HOME),
    [ENGINE_FLYPOINT_DEBUG]         = engine_flag_(gCurMapData.visitedSpawns, SPAWN_DEBUG),
    [ENGINE_FLYPOINT_PALLET]        = engine_flag_(gCurMapData.visitedSpawns, SPAWN_PALLET),
    [ENGINE_FLYPOINT_VIRIDIAN]      = engine_flag_(gCurMapData.visitedSpawns, SPAWN_VIRIDIAN),
    [ENGINE_FLYPOINT_PEWTER]        = engine_flag_(gCurMapData.visitedSpawns, SPAWN_PEWTER),
    [ENGINE_FLYPOINT_CERULEAN]      = engine_flag_(gCurMapData.visitedSpawns, SPAWN_CERULEAN),
    [ENGINE_FLYPOINT_ROCK_TUNNEL]   = engine_flag_(gCurMapData.visitedSpawns, SPAWN_ROCK_TUNNEL),
    [ENGINE_FLYPOINT_VERMILION]     = engine_flag_(gCurMapData.visitedSpawns, SPAWN_VERMILION),
    [ENGINE_FLYPOINT_LAVENDER]      = engine_flag_(gCurMapData.visitedSpawns, SPAWN_LAVENDER),
    [ENGINE_FLYPOINT_SAFFRON]       = engine_flag_(gCurMapData.visitedSpawns, SPAWN_SAFFRON),
    [ENGINE_FLYPOINT_CELADON]       = engine_flag_(gCurMapData.visitedSpawns, SPAWN_CELADON),
    [ENGINE_FLYPOINT_FUCHSIA]       = engine_flag_(gCurMapData.visitedSpawns, SPAWN_FUCHSIA),
    [ENGINE_FLYPOINT_CINNABAR]      = engine_flag_(gCurMapData.visitedSpawns, SPAWN_CINNABAR),
    [ENGINE_FLYPOINT_INDIGO_PLATEAU] = engine_flag_(gCurMapData.visitedSpawns, SPAWN_INDIGO),
    // johto
    [ENGINE_FLYPOINT_NEW_BARK]      = engine_flag_(gCurMapData.visitedSpawns, SPAWN_NEW_BARK),
    [ENGINE_FLYPOINT_CHERRYGROVE]   = engine_flag_(gCurMapData.visitedSpawns, SPAWN_CHERRYGROVE),
    [ENGINE_FLYPOINT_VIOLET]        = engine_flag_(gCurMapData.visitedSpawns, SPAWN_VIOLET),
    [ENGINE_FLYPOINT_AZALEA]        = engine_flag_(gCurMapData.visitedSpawns, SPAWN_AZALEA),
    [ENGINE_FLYPOINT_CIANWOOD]      = engine_flag_(gCurMapData.visitedSpawns, SPAWN_CIANWOOD),
    [ENGINE_FLYPOINT_GOLDENROD]     = engine_flag_(gCurMapData.visitedSpawns, SPAWN_GOLDENROD),
    [ENGINE_FLYPOINT_OLIVINE]       = engine_flag_(gCurMapData.visitedSpawns, SPAWN_OLIVINE),
    [ENGINE_FLYPOINT_ECRUTEAK]      = engine_flag_(gCurMapData.visitedSpawns, SPAWN_ECRUTEAK),
    [ENGINE_FLYPOINT_MAHOGANY]      = engine_flag_(gCurMapData.visitedSpawns, SPAWN_MAHOGANY),
    [ENGINE_FLYPOINT_LAKE_OF_RAGE]  = engine_flag_(gCurMapData.visitedSpawns, SPAWN_LAKE_OF_RAGE),
    [ENGINE_FLYPOINT_BLACKTHORN]    = engine_flag_(gCurMapData.visitedSpawns, SPAWN_BLACKTHORN),
    [ENGINE_FLYPOINT_SILVER_CAVE]   = engine_flag_(gCurMapData.visitedSpawns, SPAWN_MT_SILVER),
    [ENGINE_FLYPOINT_UNUSED]        = engine_flag_(gCurMapData.visitedSpawns, NUM_SPAWNS), // unused

// engine_flag wLuckyNumberShowFlag, LUCKYNUMBERSHOW_GAME_OVER_F
    [ENGINE_LUCKY_NUMBER_SHOW]      = engine_flag_(&gPlayer.luckyNumberShowFlag, LUCKYNUMBERSHOW_GAME_OVER_F),

// engine_flag wStatusFlags2, STATUSFLAGS2_UNUSED_3_F
    [ENGINE_4F]                     = engine_flag_(&gPlayer.statusFlags2, STATUSFLAGS2_UNUSED_3_F),

    [ENGINE_KURT_MAKING_BALLS]                      = engine_flag_(&gPlayer.dailyFlags1, DAILYFLAGS1_KURT_MAKING_BALLS_F),
    [ENGINE_DAILY_BUG_CONTEST]                      = engine_flag_(&gPlayer.dailyFlags1, DAILYFLAGS1_BUG_CONTEST_F),
    [ENGINE_FISH_SWARM]                             = engine_flag_(&gPlayer.dailyFlags1, DAILYFLAGS1_FISH_SWARM_F),
    [ENGINE_TIME_CAPSULE]                           = engine_flag_(&gPlayer.dailyFlags1, DAILYFLAGS1_TIME_CAPSULE_F),
    [ENGINE_ALL_FRUIT_TREES]                        = engine_flag_(&gPlayer.dailyFlags1, DAILYFLAGS1_ALL_FRUIT_TREES_F),
    [ENGINE_GOT_SHUCKIE_TODAY]                      = engine_flag_(&gPlayer.dailyFlags1, DAILYFLAGS1_GOT_SHUCKIE_TODAY_F),
    [ENGINE_GOLDENROD_UNDERGROUND_MERCHANT_CLOSED]  = engine_flag_(&gPlayer.dailyFlags1, DAILYFLAGS1_GOLDENROD_UNDERGROUND_BARGAIN_F),
    [ENGINE_FOUGHT_IN_TRAINER_HALL_TODAY]           = engine_flag_(&gPlayer.dailyFlags1, DAILYFLAGS1_TRAINER_HOUSE_F),

    [ENGINE_MT_MOON_SQUARE_CLEFAIRY]                = engine_flag_(&gPlayer.dailyFlags2, DAILYFLAGS2_MT_MOON_SQUARE_CLEFAIRY_F),
    [ENGINE_UNION_CAVE_LAPRAS]                      = engine_flag_(&gPlayer.dailyFlags2, DAILYFLAGS2_UNION_CAVE_LAPRAS_F),
    [ENGINE_GOLDENROD_UNDERGROUND_GOT_HAIRCUT]      = engine_flag_(&gPlayer.dailyFlags2, DAILYFLAGS2_GOLDENROD_UNDERGROUND_GOT_HAIRCUT_F),
    [ENGINE_GOLDENROD_DEPT_STORE_TM27_RETURN]       = engine_flag_(&gPlayer.dailyFlags2, DAILYFLAGS2_GOLDENROD_DEPT_STORE_TM27_RETURN_F),
    [ENGINE_DAISYS_GROOMING]                        = engine_flag_(&gPlayer.dailyFlags2, DAILYFLAGS2_DAISYS_GROOMING_F),
    [ENGINE_INDIGO_PLATEAU_RIVAL_FIGHT]             = engine_flag_(&gPlayer.dailyFlags2, DAILYFLAGS2_INDIGO_PLATEAU_RIVAL_FIGHT_F),
    [ENGINE_DAILY_MOVE_TUTOR]                       = engine_flag_(&gPlayer.dailyFlags2, DAILYFLAGS2_MOVE_TUTOR_F),
    [ENGINE_BUENAS_PASSWORD]                        = engine_flag_(&gPlayer.dailyFlags2, DAILYFLAGS2_BUENAS_PASSWORD_F),

    [ENGINE_BUENAS_PASSWORD_2]                      = engine_flag_(&gPlayer.swarmFlags, SWARMFLAGS_BUENAS_PASSWORD_F),
    [ENGINE_GOLDENROD_DEPT_STORE_SALE_IS_ON]        = engine_flag_(&gPlayer.swarmFlags, SWARMFLAGS_GOLDENROD_DEPT_STORE_SALE_F),

// engine_flag wGameTimerPaused, GAME_TIMER_MOBILE_F
    [ENGINE_62]                                     = engine_flag(wGameTimerPaused, GAME_TIMER_MOBILE_F),

// engine_flag wPlayerGender, PLAYERGENDER_FEMALE_F
    [ENGINE_PLAYER_IS_FEMALE]                       = engine_flag_(&gCrystal.playerGender, PLAYERGENDER_FEMALE_F),

// engine_flag wCelebiEvent, CELEBIEVENT_FOREST_IS_RESTLESS_F
    [ENGINE_FOREST_IS_RESTLESS]                     = engine_flag_(&gPlayer.celebiEvent, CELEBIEVENT_FOREST_IS_RESTLESS_F),

// rematches
    [ENGINE_JACK_READY_FOR_REMATCH]         = engine_flag_(gPlayer.dailyRematchFlags,  0), // jack
    [ENGINE_HUEY_READY_FOR_REMATCH]         = engine_flag_(gPlayer.dailyRematchFlags,  1), // huey
    [ENGINE_GAVEN_READY_FOR_REMATCH]        = engine_flag_(gPlayer.dailyRematchFlags,  2), // gaven
    [ENGINE_BETH_READY_FOR_REMATCH]         = engine_flag_(gPlayer.dailyRematchFlags,  3), // beth
    [ENGINE_JOSE_READY_FOR_REMATCH]         = engine_flag_(gPlayer.dailyRematchFlags,  4), // jose
    [ENGINE_REENA_READY_FOR_REMATCH]        = engine_flag_(gPlayer.dailyRematchFlags,  5), // reena
    [ENGINE_JOEY_READY_FOR_REMATCH]         = engine_flag_(gPlayer.dailyRematchFlags,  6), // joey
    [ENGINE_WADE_READY_FOR_REMATCH]         = engine_flag_(gPlayer.dailyRematchFlags,  7), // wade
    [ENGINE_RALPH_READY_FOR_REMATCH]        = engine_flag_(gPlayer.dailyRematchFlags,  8), // ralph
    [ENGINE_LIZ_READY_FOR_REMATCH]          = engine_flag_(gPlayer.dailyRematchFlags,  9), // liz
    [ENGINE_ANTHONY_READY_FOR_REMATCH]      = engine_flag_(gPlayer.dailyRematchFlags, 10), // anthony
    [ENGINE_TODD_READY_FOR_REMATCH]         = engine_flag_(gPlayer.dailyRematchFlags, 11), // todd
    [ENGINE_GINA_READY_FOR_REMATCH]         = engine_flag_(gPlayer.dailyRematchFlags, 12), // gina
    [ENGINE_ARNIE_READY_FOR_REMATCH]        = engine_flag_(gPlayer.dailyRematchFlags, 13), // arnie
    [ENGINE_ALAN_READY_FOR_REMATCH]         = engine_flag_(gPlayer.dailyRematchFlags, 14), // alan
    [ENGINE_DANA_READY_FOR_REMATCH]         = engine_flag_(gPlayer.dailyRematchFlags, 15), // dana
    [ENGINE_CHAD_READY_FOR_REMATCH]         = engine_flag_(gPlayer.dailyRematchFlags, 16), // chad
    [ENGINE_TULLY_READY_FOR_REMATCH]        = engine_flag_(gPlayer.dailyRematchFlags, 17), // tully
    [ENGINE_BRENT_READY_FOR_REMATCH]        = engine_flag_(gPlayer.dailyRematchFlags, 18), // brent
    [ENGINE_TIFFANY_READY_FOR_REMATCH]      = engine_flag_(gPlayer.dailyRematchFlags, 19), // tiffany
    [ENGINE_VANCE_READY_FOR_REMATCH]        = engine_flag_(gPlayer.dailyRematchFlags, 20), // vance
    [ENGINE_WILTON_READY_FOR_REMATCH]       = engine_flag_(gPlayer.dailyRematchFlags, 21), // wilton
    [ENGINE_PARRY_READY_FOR_REMATCH]        = engine_flag_(gPlayer.dailyRematchFlags, 22), // parry
    [ENGINE_ERIN_READY_FOR_REMATCH]         = engine_flag_(gPlayer.dailyRematchFlags, 23), // erin

    [ENGINE_BEVERLY_HAS_NUGGET]             = engine_flag_(gPlayer.dailyPhoneItemFlags, 0), // beverly has nugget
    [ENGINE_JOSE_HAS_STAR_PIECE]            = engine_flag_(gPlayer.dailyPhoneItemFlags, 1), // jose has star piece
    [ENGINE_WADE_HAS_ITEM]                  = engine_flag_(gPlayer.dailyPhoneItemFlags, 2), // wade has item (see EVENT_WADE_HAS_*** in constants/event_flags.h)
    [ENGINE_GINA_HAS_LEAF_STONE]            = engine_flag_(gPlayer.dailyPhoneItemFlags, 3), // gina has leaf stone
    [ENGINE_ALAN_HAS_FIRE_STONE]            = engine_flag_(gPlayer.dailyPhoneItemFlags, 4), // alan has fire stone
    [ENGINE_DANA_HAS_THUNDERSTONE]          = engine_flag_(gPlayer.dailyPhoneItemFlags, 5), // liz (dana?) has thunderstone
    [ENGINE_DEREK_HAS_NUGGET]               = engine_flag_(gPlayer.dailyPhoneItemFlags, 6), // derek has nugget
    [ENGINE_TULLY_HAS_WATER_STONE]          = engine_flag_(gPlayer.dailyPhoneItemFlags, 7), // tully has water stone
    [ENGINE_TIFFANY_HAS_PINK_BOW]           = engine_flag_(gPlayer.dailyPhoneItemFlags, 8), // tiffany has pink bow
    [ENGINE_WILTON_HAS_ITEM]                = engine_flag_(gPlayer.dailyPhoneItemFlags, 9), // wilton has item (see EVENT_WILTON_HAS_*** in constants/event_flags.h)

    [ENGINE_JACK_MONDAY_MORNING]            = engine_flag_(gPlayer.dailyPhoneTimeOfDayFlags,  0), // jack
    [ENGINE_HUEY_WEDNESDAY_NIGHT]           = engine_flag_(gPlayer.dailyPhoneTimeOfDayFlags,  1), // huey
    [ENGINE_GAVEN_THURSDAY_MORNING]         = engine_flag_(gPlayer.dailyPhoneTimeOfDayFlags,  2), // gaven
    [ENGINE_BETH_FRIDAY_AFTERNOON]          = engine_flag_(gPlayer.dailyPhoneTimeOfDayFlags,  3), // beth
    [ENGINE_JOSE_SATURDAY_NIGHT]            = engine_flag_(gPlayer.dailyPhoneTimeOfDayFlags,  4), // jose
    [ENGINE_REENA_SUNDAY_MORNING]           = engine_flag_(gPlayer.dailyPhoneTimeOfDayFlags,  5), // reena
    [ENGINE_JOEY_MONDAY_AFTERNOON]          = engine_flag_(gPlayer.dailyPhoneTimeOfDayFlags,  6), // joey
    [ENGINE_WADE_TUESDAY_NIGHT]             = engine_flag_(gPlayer.dailyPhoneTimeOfDayFlags,  7), // wade
    [ENGINE_RALPH_WEDNESDAY_MORNING]        = engine_flag_(gPlayer.dailyPhoneTimeOfDayFlags,  8), // ralph
    [ENGINE_LIZ_THURSDAY_AFTERNOON]         = engine_flag_(gPlayer.dailyPhoneTimeOfDayFlags,  9), // liz
    [ENGINE_ANTHONY_FRIDAY_NIGHT]           = engine_flag_(gPlayer.dailyPhoneTimeOfDayFlags, 10), // anthony
    [ENGINE_TODD_SATURDAY_MORNING]          = engine_flag_(gPlayer.dailyPhoneTimeOfDayFlags, 11), // todd
    [ENGINE_GINA_SUNDAY_AFTERNOON]          = engine_flag_(gPlayer.dailyPhoneTimeOfDayFlags, 12), // gina
    [ENGINE_ARNIE_TUESDAY_MORNING]          = engine_flag_(gPlayer.dailyPhoneTimeOfDayFlags, 13), // arnie
    [ENGINE_ALAN_WEDNESDAY_AFTERNOON]       = engine_flag_(gPlayer.dailyPhoneTimeOfDayFlags, 14), // alan
    [ENGINE_DANA_THURSDAY_NIGHT]            = engine_flag_(gPlayer.dailyPhoneTimeOfDayFlags, 15), // dana
    [ENGINE_CHAD_FRIDAY_MORNING]            = engine_flag_(gPlayer.dailyPhoneTimeOfDayFlags, 16), // chad
    [ENGINE_TULLY_SUNDAY_NIGHT]             = engine_flag_(gPlayer.dailyPhoneTimeOfDayFlags, 17), // tully
    [ENGINE_BRENT_MONDAY_MORNING]           = engine_flag_(gPlayer.dailyPhoneTimeOfDayFlags, 18), // brent
    [ENGINE_TIFFANY_TUESDAY_AFTERNOON]      = engine_flag_(gPlayer.dailyPhoneTimeOfDayFlags, 19), // tiffany
    [ENGINE_VANCE_WEDNESDAY_NIGHT]          = engine_flag_(gPlayer.dailyPhoneTimeOfDayFlags, 20), // vance
    [ENGINE_WILTON_THURSDAY_MORNING]        = engine_flag_(gPlayer.dailyPhoneTimeOfDayFlags, 21), // wilton
    [ENGINE_PARRY_FRIDAY_AFTERNOON]         = engine_flag_(gPlayer.dailyPhoneTimeOfDayFlags, 22), // parry
    [ENGINE_ERIN_SATURDAY_NIGHT]            = engine_flag_(gPlayer.dailyPhoneTimeOfDayFlags, 23), // erin

    [ENGINE_KRIS_IN_CABLE_CLUB]             = engine_flag(wPlayerSpriteSetupFlags, PLAYERSPRITESETUP_FEMALE_TO_MALE_F),

    [ENGINE_DUNSPARCE_SWARM]                = engine_flag_(&gPlayer.swarmFlags, SWARMFLAGS_DUNSPARCE_SWARM_F),
    [ENGINE_YANMA_SWARM]                    = engine_flag_(&gPlayer.swarmFlags, SWARMFLAGS_YANMA_SWARM_F),
};

static_assert(lengthof(EngineFlags) == NUM_ENGINE_FLAGS, "");
