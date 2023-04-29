#pragma once
#include "../../constants.h"

const uint16_t RadioChannelSongs[] = {
	MUSIC_POKEMON_TALK,
	MUSIC_POKEMON_CENTER,
	MUSIC_TITLE,
	MUSIC_GAME_CORNER,
    MUSIC_BUENAS_PASSWORD,
	MUSIC_VIRIDIAN_CITY,
	MUSIC_BICYCLE,
	MUSIC_ROCKET_OVERTURE,
	MUSIC_POKE_FLUTE_CHANNEL,
	MUSIC_RUINS_OF_ALPH_RADIO,
	MUSIC_LAKE_OF_RAGE_ROCKET_RADIO
};

#if defined(__cplusplus) || defined(_MSC_VER)
static_assert(sizeof(RadioChannelSongs) / sizeof(RadioChannelSongs[0]) == NUM_RADIO_CHANNELS, "");
#else
_Static_assert(sizeof(RadioChannelSongs) / sizeof(RadioChannelSongs[0]) == NUM_RADIO_CHANNELS, "");
#endif
