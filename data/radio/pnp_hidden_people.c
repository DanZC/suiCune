#include "../../constants.h"

// Places and People will not describe these trainers.

const uint8_t PnP_HiddenPeople[] = {
    WILL,
    BRUNO,
    KAREN,
    KOGA,
    CHAMPION,
// fallthrough
    BROCK,
    MISTY,
    LT_SURGE,
    ERIKA,
    JANINE,
    SABRINA,
    BLAINE,
    BLUE,
// fallthrough
    RIVAL1,
    POKEMON_PROF,
    CAL,
    RIVAL2,
    RED,
    -1,
};
const uint8_t* const PnP_HiddenPeople_BeatE4 = PnP_HiddenPeople + 5;
    // db BROCK
    // db MISTY
    // db LT_SURGE
    // db ERIKA
    // db JANINE
    // db SABRINA
    // db BLAINE
    // db BLUE
const uint8_t* const PnP_HiddenPeople_BeatKanto = PnP_HiddenPeople + 13;
    // db RIVAL1
    // db POKEMON_PROF
    // db CAL
    // db RIVAL2
    // db RED
    // db -1
