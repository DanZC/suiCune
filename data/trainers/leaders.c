#include "../../constants.h"

// These lists determine the battle music and victory music, and whether to
// award HAPPINESS_GYMBATTLE for winning.
//
// Note: CHAMPION and RED are unused for battle music checks, since they are
// accounted for prior to the list check.

const uint8_t GymLeaders[] = {
	FALKNER,
	WHITNEY,
	BUGSY,
	MORTY,
	PRYCE,
	JASMINE,
	CHUCK,
	CLAIR,
	WILL,
	BRUNO,
	KAREN,
	KOGA,
	CHAMPION,
	RED,
// fallthrough
// KantoGymLeaders:
	BROCK,
	MISTY,
	LT_SURGE,
	ERIKA,
	JANINE,
	SABRINA,
	BLAINE,
	BLUE,
	-1,
};

const uint8_t* const KantoGymLeaders = GymLeaders + 14;