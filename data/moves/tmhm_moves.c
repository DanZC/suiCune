#include "../../constants.h"

// The add_tm, add_hm, and add_mt macros in constants/item_constants.asm simultaneously
// define constants for the item IDs and for the corresponding move values.

#define TMMOVE(_a) [_a##_TMNUM-1] = _a

const move_t TMHMMoves[] = {
// entries correspond to *_TMNUM constants (see constants/item_constants.asm)
    // table_width 1, TMHMMoves

// TMs
    TMMOVE(DYNAMICPUNCH),
    TMMOVE(HEADBUTT),
    TMMOVE(CURSE),
    TMMOVE(ROLLOUT),
    TMMOVE(ROAR),
    TMMOVE(TOXIC),
    TMMOVE(ZAP_CANNON),
    TMMOVE(ROCK_SMASH),
    TMMOVE(PSYCH_UP),
    TMMOVE(HIDDEN_POWER),
    TMMOVE(SUNNY_DAY),
    TMMOVE(SWEET_SCENT),
    TMMOVE(SNORE),
    TMMOVE(BLIZZARD),
    TMMOVE(HYPER_BEAM),
    TMMOVE(ICY_WIND),
    TMMOVE(PROTECT),
    TMMOVE(RAIN_DANCE),
    TMMOVE(GIGA_DRAIN),
    TMMOVE(ENDURE),
    TMMOVE(FRUSTRATION),
    TMMOVE(SOLARBEAM),
    TMMOVE(IRON_TAIL),
    TMMOVE(DRAGONBREATH),
    TMMOVE(THUNDER),
    TMMOVE(EARTHQUAKE),
    TMMOVE(RETURN),
    TMMOVE(DIG),
    TMMOVE(PSYCHIC_M),
    TMMOVE(SHADOW_BALL),
    TMMOVE(MUD_SLAP),
    TMMOVE(DOUBLE_TEAM),
    TMMOVE(ICE_PUNCH),
    TMMOVE(SWAGGER),
    TMMOVE(SLEEP_TALK),
    TMMOVE(SLUDGE_BOMB),
    TMMOVE(SANDSTORM),
    TMMOVE(FIRE_BLAST),
    TMMOVE(SWIFT),
    TMMOVE(DEFENSE_CURL),
    TMMOVE(THUNDERPUNCH),
    TMMOVE(DREAM_EATER),
    TMMOVE(DETECT),
    TMMOVE(REST),
    TMMOVE(ATTRACT),
    TMMOVE(THIEF),
    TMMOVE(STEEL_WING),
    TMMOVE(FIRE_PUNCH),
    TMMOVE(FURY_CUTTER),
    TMMOVE(NIGHTMARE),
// for n, 1, NUM_TMS + 1
// 	db TM{02d:n}_MOVE
// endr
// 	assert_table_length NUM_TMS

// HMs
    TMMOVE(CUT),
    TMMOVE(FLY),
    TMMOVE(SURF),
    TMMOVE(STRENGTH),
    TMMOVE(FLASH),
    TMMOVE(WHIRLPOOL),
    TMMOVE(WATERFALL),
// for n, 1, NUM_HMS + 1
// 	db HM{02d:n}_MOVE
// endr
// 	assert_table_length NUM_TMS + NUM_HMS

// Move tutors
    TMMOVE(FLAMETHROWER),
    TMMOVE(THUNDERBOLT),
    TMMOVE(ICE_BEAM),
// n = 1
// for n, 1, NUM_TUTORS + 1
// 	db MT{02d:n}_MOVE
// endr
};
static_assert(lengthof(TMHMMoves) == NUM_TM_HM_TUTOR, "");
	// db 0 ; end
