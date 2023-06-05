#pragma once
#include "../../constants.h"

const uint16_t RadioChannelSongs[] = {
    [OAKS_POKEMON_TALK] = MUSIC_POKEMON_TALK,
    [POKEDEX_SHOW]      = MUSIC_POKEMON_CENTER,
    [POKEMON_MUSIC]     = MUSIC_TITLE,
    [LUCKY_CHANNEL]     = MUSIC_GAME_CORNER,
    [BUENAS_PASSWORD]   = MUSIC_BUENAS_PASSWORD,
    [PLACES_AND_PEOPLE] = MUSIC_VIRIDIAN_CITY,
    [LETS_ALL_SING]     = MUSIC_BICYCLE,
    [ROCKET_RADIO]      = MUSIC_ROCKET_OVERTURE,
    [POKE_FLUTE_RADIO]  = MUSIC_POKE_FLUTE_CHANNEL,
    [UNOWN_RADIO]       = MUSIC_RUINS_OF_ALPH_RADIO,
    [EVOLUTION_RADIO]   = MUSIC_LAKE_OF_RAGE_ROCKET_RADIO
};

#if defined(__cplusplus) || defined(_MSC_VER)
static_assert(sizeof(RadioChannelSongs) / sizeof(RadioChannelSongs[0]) == NUM_RADIO_CHANNELS, "");
#else
_Static_assert(sizeof(RadioChannelSongs) / sizeof(RadioChannelSongs[0]) == NUM_RADIO_CHANNELS, "");
#endif
