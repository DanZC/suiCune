#include "../../constants.h"
#include "setup_script_pointers.h"

// ; valid commands are listed in MapSetupCommands (see data/maps/setup_script_pointers.asm)
// mapsetup: MACRO
// 	db (\1_MapSetupCmd - MapSetupCommands) / 3
// ENDM

static const uint8_t MapSetupScript_Teleport[] = {
    mapsetup_const(ResetPlayerObjectAction),
// MapSetupScript_Fly:
    mapsetup_const(FadeOutPalettes),
    mapsetup_const(JumpRoamMons),
// MapSetupScript_Warp:
    mapsetup_const(DisableLCD),
    mapsetup_const(InitSound),
    mapsetup_const(EnterMapSpawnPoint),
    mapsetup_const(LoadMapAttributes),
    mapsetup_const(HandleNewMap),
    mapsetup_const(SpawnPlayer),
    mapsetup_const(RefreshPlayerCoords),
    mapsetup_const(GetMapScreenCoords),
    mapsetup_const(LoadBlockData),
    mapsetup_const(BufferScreen),
    mapsetup_const(LoadMapGraphics),
    mapsetup_const(LoadMapTimeOfDay),
    mapsetup_const(LoadMapObjects),
    mapsetup_const(EnableLCD),
    mapsetup_const(LoadMapPalettes),
    mapsetup_const(SpawnInFacingDown),
    mapsetup_const(RefreshMapSprites),
    mapsetup_const(PlayMapMusicBike),
    mapsetup_const(FadeInToMusic),
    mapsetup_const(FadeInPalettes),
    mapsetup_const(ActivateMapAnims),
    mapsetup_const(LoadWildMonData),
    (uint8_t)-1, // end
};

//static const uint8_t* const MapSetupScript_Fly = MapSetupScript_Teleport + 1;

#define MapSetupScript_Fly MapSetupScript_Teleport + 1

//static const uint8_t* const MapSetupScript_Warp = MapSetupScript_Teleport + 3;

#define MapSetupScript_Warp MapSetupScript_Teleport + 3

static const uint8_t MapSetupScript_BadWarp[] = {
    mapsetup_const(EnterMapSpawnPoint),
    mapsetup_const(LoadMapAttributes),
    mapsetup_const(HandleNewMap),
    mapsetup_const(SpawnPlayer),
    mapsetup_const(RefreshPlayerCoords),
    mapsetup_const(GetMapScreenCoords),
    mapsetup_const(LoadBlockData),
    mapsetup_const(BufferScreen),
    mapsetup_const(DisableLCD),
    mapsetup_const(LoadMapGraphics),
    mapsetup_const(LoadMapTimeOfDay),
    mapsetup_const(FadeOutMapMusic),
    mapsetup_const(EnableLCD),
    mapsetup_const(LoadMapObjects),
    mapsetup_const(LoadMapPalettes),
    mapsetup_const(SpawnInFacingDown),
    mapsetup_const(RefreshMapSprites),
    mapsetup_const(FadeToMapMusic),
    mapsetup_const(FadeInPalettes),
    mapsetup_const(ActivateMapAnims),
    mapsetup_const(LoadWildMonData),
    (uint8_t)-1, // end
};

static const uint8_t MapSetupScript_Connection[] = {
    mapsetup_const(SuspendMapAnims),
    mapsetup_const(EnterMapConnection),
    mapsetup_const(LoadMapAttributes),
    mapsetup_const(HandleNewMap),
    mapsetup_const(RefreshPlayerCoords),
    mapsetup_const(LoadBlockData),
    mapsetup_const(LoadMapTileset),
    mapsetup_const(SaveScreen),
    mapsetup_const(LoadMapObjects),
    mapsetup_const(FadeToMapMusic),
    mapsetup_const(LoadMapPalettes),
    mapsetup_const(InitMapNameSign),
    mapsetup_const(ApplyMapPalettes),
    mapsetup_const(LoadWildMonData),
    mapsetup_const(UpdateRoamMons),
    mapsetup_const(ActivateMapAnims),
    (uint8_t)-1, // end
};

static const uint8_t MapSetupScript_Fall[] = {
	mapsetup_const(ResetPlayerObjectAction),
// MapSetupScript_Door:
	mapsetup_const(FadeOutPalettes),
// MapSetupScript_Train:
    mapsetup_const(EnterMapWarp),
    mapsetup_const(LoadMapAttributes),
    mapsetup_const(GetWarpDestCoords),
    mapsetup_const(HandleNewMap),
    mapsetup_const(RefreshPlayerCoords),
    mapsetup_const(LoadBlockData),
    mapsetup_const(BufferScreen),
    mapsetup_const(DisableLCD),
    mapsetup_const(LoadMapGraphics),
    mapsetup_const(LoadMapTimeOfDay),
    mapsetup_const(FadeOutMapMusic),
    mapsetup_const(EnableLCD),
    mapsetup_const(LoadMapObjects),
    mapsetup_const(LoadMapPalettes),
    mapsetup_const(RefreshMapSprites),
    mapsetup_const(FadeToMapMusic),
    mapsetup_const(FadeInPalettes),
    mapsetup_const(ActivateMapAnims),
    mapsetup_const(LoadWildMonData),
    mapsetup_const(UpdateRoamMons),
    (uint8_t)-1, // end
};

//static const uint8_t* const MapSetupScript_Door = MapSetupScript_Fall + 1;

#define MapSetupScript_Door MapSetupScript_Fall + 1

//static const uint8_t* const MapSetupScript_Train = MapSetupScript_Fall + 2;

#define MapSetupScript_Train MapSetupScript_Fall + 2

static const uint8_t MapSetupScript_ReloadMap[] = {
    mapsetup_const(FadeMapMusicAndPalettes),
    mapsetup_const(ClearBGPalettes),
    mapsetup_const(DisableLCD),
    mapsetup_const(InitSound),
    mapsetup_const(LoadBlockData),
    mapsetup_const(LoadConnectionBlockData),
    mapsetup_const(LoadMapGraphics),
    mapsetup_const(LoadMapTimeOfDay),
    mapsetup_const(EnableLCD),
    mapsetup_const(LoadMapPalettes),
    mapsetup_const(RefreshMapSprites),
    mapsetup_const(ForceMapMusic),
    mapsetup_const(FadeInPalettes),
    mapsetup_const(ActivateMapAnims),
    mapsetup_const(LoadWildMonData),
    (uint8_t)-1, // end
};

static const uint8_t MapSetupScript_LinkReturn[] = {
    mapsetup_const(FadeMapMusicAndPalettes),
    mapsetup_const(DisableLCD),
    mapsetup_const(InitSound),
    mapsetup_const(HandleNewMap),
    mapsetup_const(LoadBlockData),
    mapsetup_const(BufferScreen),
    mapsetup_const(LoadMapGraphics),
    mapsetup_const(LoadMapTimeOfDay),
    mapsetup_const(EnableLCD),
    mapsetup_const(LoadMapPalettes),
    mapsetup_const(RefreshMapSprites),
    mapsetup_const(PlayMapMusicBike),
    mapsetup_const(FadeInPalettes),
    mapsetup_const(ActivateMapAnims),
    mapsetup_const(LoadWildMonData),
    mapsetup_const(EnableTextAcceleration),
    (uint8_t)-1, // end
};

static const uint8_t MapSetupScript_Continue[] = {
    mapsetup_const(DisableLCD),
    mapsetup_const(InitSound),
    mapsetup_const(LoadMapAttributes_SkipObjects),
    mapsetup_const(GetMapScreenCoords),
    mapsetup_const(HandleContinueMap),
    mapsetup_const(LoadBlockData),
    mapsetup_const(LoadConnectionBlockData),
    mapsetup_const(BufferScreen),
    mapsetup_const(LoadMapGraphics),
    mapsetup_const(LoadMapTimeOfDay),
    mapsetup_const(EnableLCD),
    mapsetup_const(LoadMapPalettes),
    mapsetup_const(RefreshMapSprites),
    mapsetup_const(PlayMapMusicBike),
    mapsetup_const(FadeInPalettes),
    mapsetup_const(ActivateMapAnims),
    mapsetup_const(LoadWildMonData),
    (uint8_t)-1, // end
};

static const uint8_t MapSetupScript_Submenu[] = {
    mapsetup_const(LoadBlockData),
    mapsetup_const(LoadConnectionBlockData),
    (uint8_t)-1, // end
};

const uint8_t* const MapSetupScripts[] = {
// entries correspond to MAPSETUP_* constants (see constants/map_setup_constants.asm)
    // table_width 2, MapSetupScripts
    [MAPSETUP_WARP       - MAPSETUP_WARP] = MapSetupScript_Warp,
    [MAPSETUP_CONTINUE   - MAPSETUP_WARP] = MapSetupScript_Continue,
    [MAPSETUP_RELOADMAP  - MAPSETUP_WARP] = MapSetupScript_ReloadMap,
    [MAPSETUP_TELEPORT   - MAPSETUP_WARP] = MapSetupScript_Teleport,
    [MAPSETUP_DOOR       - MAPSETUP_WARP] = MapSetupScript_Door,
    [MAPSETUP_FALL       - MAPSETUP_WARP] = MapSetupScript_Fall,
    [MAPSETUP_CONNECTION - MAPSETUP_WARP] = MapSetupScript_Connection,
    [MAPSETUP_LINKRETURN - MAPSETUP_WARP] = MapSetupScript_LinkReturn,
    [MAPSETUP_TRAIN      - MAPSETUP_WARP] = MapSetupScript_Train,
    [MAPSETUP_SUBMENU    - MAPSETUP_WARP] = MapSetupScript_Submenu,
    [MAPSETUP_BADWARP    - MAPSETUP_WARP] = MapSetupScript_BadWarp,
    [MAPSETUP_FLY        - MAPSETUP_WARP] = MapSetupScript_Fly,
};
static_assert(lengthof(MapSetupScripts) == NUM_MAPSETUP_SCRIPTS, "");
