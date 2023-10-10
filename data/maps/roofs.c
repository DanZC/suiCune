#include "../../constants.h"
#include "roofs.h"

const uint8_t MapGroupRoofs[] = {
// entries correspond to MAPGROUP_* constants
// values are indexes for Roofs (see below)
	[MAPGROUP_NONE]         = -1,             //  0
	[MAPGROUP_OLIVINE]      = ROOF_OLIVINE,   //  1 (Olivine)
	[MAPGROUP_MAHOGANY]     = ROOF_AZALEA,    //  2 (Mahogany)
	[MAPGROUP_DUNGEONS]     = -1,             //  3
	[MAPGROUP_ECRUTEAK]     = ROOF_VIOLET,    //  4 (Ecruteak)
	[MAPGROUP_BLACKTHORN]   = ROOF_AZALEA,    //  5 (Blackthorn)
	[MAPGROUP_CINNABAR]     = -1,             //  6
	[MAPGROUP_CERULEAN]     = -1,             //  7
	[MAPGROUP_AZALEA]       = ROOF_AZALEA,    //  8 (Azalea)
	[MAPGROUP_LAKE_OF_RAGE] = ROOF_AZALEA,    //  9 (Lake of Rage)
	[MAPGROUP_VIOLET]       = ROOF_VIOLET,    // 10 (Violet)
	[MAPGROUP_GOLDENROD]    = ROOF_GOLDENROD, // 11 (Goldenrod)
	[MAPGROUP_VERMILION]    = -1,             // 12
	[MAPGROUP_PALLET]       = -1,             // 13
	[MAPGROUP_PEWTER]       = -1,             // 14
	[MAPGROUP_FAST_SHIP]    = -1,             // 15
	[MAPGROUP_INDIGO]       = -1,             // 16
	[MAPGROUP_FUCHSIA]      = -1,             // 17
	[MAPGROUP_LAVENDER]     = -1,             // 18
	[MAPGROUP_SILVER]       = ROOF_NEW_BARK,  // 19 (Silver Cave)
	[MAPGROUP_CABLE_CLUB]   = -1,             // 20
	[MAPGROUP_CELADON]      = -1,             // 21
	[MAPGROUP_CIANWOOD]     = ROOF_OLIVINE,   // 22 (Cianwood)
	[MAPGROUP_VIRIDIAN]     = -1,             // 23
	[MAPGROUP_NEW_BARK]     = ROOF_NEW_BARK,  // 24 (New Bark)
	[MAPGROUP_SAFFRON]      = -1,             // 25
	[MAPGROUP_CHERRYGROVE]  = ROOF_NEW_BARK,  // 26 (Cherrygrove)
};
static_assert(lengthof(MapGroupRoofs) == NUM_MAP_GROUPS + 1);

const char *Roofs[] = {
// entries correspond to ROOF_* constants
    [ROOF_NEW_BARK]     = "gfx/tilesets/roofs/new_bark.png",
    [ROOF_VIOLET]       = "gfx/tilesets/roofs/violet.png",
    [ROOF_AZALEA]       = "gfx/tilesets/roofs/azalea.png",
    [ROOF_OLIVINE]      = "gfx/tilesets/roofs/olivine.png",
    [ROOF_GOLDENROD]    = "gfx/tilesets/roofs/goldenrod.png",
};
static_assert(lengthof(Roofs) == NUM_ROOFS);
