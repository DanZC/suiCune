#include "../../constants.h"

static const char Normal[]    = "NORMAL@";
static const char Fighting[]  = "FIGHTING@";
static const char Flying[]    = "FLYING@";
static const char Poison[]    = "POISON@";
static const char CurseType[] = "???@";
static const char Fire[]      = "FIRE@";
static const char Water[]     = "WATER@";
static const char Grass[]     = "GRASS@";
static const char Electric[]  = "ELECTRIC@";
static const char Psychic[]   = "PSYCHIC@";
static const char Ice[]       = "ICE@";
static const char Ground[]    = "GROUND@";
static const char Rock[]      = "ROCK@";
static const char Bird[]      = "BIRD@";
static const char Bug[]       = "BUG@";
static const char Ghost[]     = "GHOST@";
static const char Steel[]     = "STEEL@";
static const char Dragon[]    = "DRAGON@";
static const char Dark[]      = "DARK@";

const char* TypeNames[] = {
// entries correspond to types (see constants/type_constants.asm)
// table_width 2, TypeNames
    [NORMAL] = Normal,
    [FIGHTING] = Fighting,
    [FLYING] = Flying,
    [POISON] = Poison,
    [GROUND] = Ground,
    [ROCK] = Rock,
    [BIRD] = Bird,
    [BUG] = Bug,
    [GHOST] = Ghost,
    [STEEL] = Steel,
    // assert_table_length UNUSED_TYPES
    Normal,
    Normal,
    Normal,
    Normal,
    Normal,
    Normal,
    Normal,
    Normal,
    Normal,
    [CURSE_TYPE] = CurseType,
	// assert_table_length UNUSED_TYPES_END
	[FIRE] = Fire,
	[WATER] = Water,
	[GRASS] = Grass,
	[ELECTRIC] = Electric,
	[PSYCHIC_TYPE] = Psychic,
	[ICE] = Ice,
	[DRAGON] = Dragon,
	[DARK] = Dark,
};
static_assert(lengthof(TypeNames) == TYPES_END, "");
