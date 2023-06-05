#include "../../constants.h"

struct Flypoint {
    uint8_t landmark;
    uint8_t spawn;
};

const struct Flypoint Flypoints[] = {
// entries correspond to FLY_* constants
// Johto
	//                    landmark,                  spawn point
	[FLY_NEW_BARK]     = {LANDMARK_NEW_BARK_TOWN,    SPAWN_NEW_BARK},
	[FLY_CHERRYGROVE]  = {LANDMARK_CHERRYGROVE_CITY, SPAWN_CHERRYGROVE},
	[FLY_VIOLET]       = {LANDMARK_VIOLET_CITY,      SPAWN_VIOLET},
	[FLY_AZALEA]       = {LANDMARK_AZALEA_TOWN,      SPAWN_AZALEA},
	[FLY_GOLDENROD]    = {LANDMARK_GOLDENROD_CITY,   SPAWN_GOLDENROD},
	[FLY_ECRUTEAK]     = {LANDMARK_ECRUTEAK_CITY,    SPAWN_ECRUTEAK},
	[FLY_OLIVINE]      = {LANDMARK_OLIVINE_CITY,     SPAWN_OLIVINE},
	[FLY_CIANWOOD]     = {LANDMARK_CIANWOOD_CITY,    SPAWN_CIANWOOD},
	[FLY_MAHOGANY]     = {LANDMARK_MAHOGANY_TOWN,    SPAWN_MAHOGANY},
	[FLY_LAKE_OF_RAGE] = {LANDMARK_LAKE_OF_RAGE,     SPAWN_LAKE_OF_RAGE},
	[FLY_BLACKTHORN]   = {LANDMARK_BLACKTHORN_CITY,  SPAWN_BLACKTHORN},
	[FLY_MT_SILVER]    = {LANDMARK_SILVER_CAVE,      SPAWN_MT_SILVER},
// Kanto
	[FLY_PALLET]       = {LANDMARK_PALLET_TOWN,      SPAWN_PALLET},
	[FLY_VIRIDIAN]     = {LANDMARK_VIRIDIAN_CITY,    SPAWN_VIRIDIAN},
	[FLY_PEWTER]       = {LANDMARK_PEWTER_CITY,      SPAWN_PEWTER},
	[FLY_CERULEAN]     = {LANDMARK_CERULEAN_CITY,    SPAWN_CERULEAN},
	[FLY_VERMILION]    = {LANDMARK_VERMILION_CITY,   SPAWN_VERMILION},
	[FLY_ROCK_TUNNEL]  = {LANDMARK_ROCK_TUNNEL,      SPAWN_ROCK_TUNNEL},
	[FLY_LAVENDER]     = {LANDMARK_LAVENDER_TOWN,    SPAWN_LAVENDER},
	[FLY_CELADON]      = {LANDMARK_CELADON_CITY,     SPAWN_CELADON},
	[FLY_SAFFRON]      = {LANDMARK_SAFFRON_CITY,     SPAWN_SAFFRON},
	[FLY_FUCHSIA]      = {LANDMARK_FUCHSIA_CITY,     SPAWN_FUCHSIA},
	[FLY_CINNABAR]     = {LANDMARK_CINNABAR_ISLAND,  SPAWN_CINNABAR},
	[FLY_INDIGO]       = {LANDMARK_INDIGO_PLATEAU,   SPAWN_INDIGO},
	{0xff, 0xff}, // end
};