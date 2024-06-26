#include "../../constants.h"
#include "setup_script_pointers.h"

#include "../../home/lcd.h"
#include "../../home/audio.h"
#include "../../home/map.h"
#include "../../home/gfx.h"
#include "../../home/tilemap.h"
#include "../../engine/overworld/player_object.h"
#include "../../engine/overworld/wildmons.h"
#include "../../engine/overworld/warp_connection.h"
#include "../../engine/overworld/spawn_points.h"
#include "../../engine/overworld/map_setup.h"
#include "../../engine/overworld/map_objects.h"
#include "../../engine/tilesets/timeofday_pals.h"
#include "../../engine/events/map_name_sign.h"

#define add_mapsetup(_x) [mapsetup_const(_x)] = _x

void (*const MapSetupCommands[])(void) = {
    add_mapsetup(EnableLCD), // 00
    add_mapsetup(DisableLCD), // 01
    add_mapsetup(InitSound), // 02
    add_mapsetup(PlayMapMusic), // 03
    add_mapsetup(RestartMapMusic), // 04
    add_mapsetup(FadeToMapMusic), // 05
    add_mapsetup(FadeMapMusicAndPalettes), // 06
    add_mapsetup(PlayMapMusicBike), // 07
    add_mapsetup(ForceMapMusic), // 08
    add_mapsetup(FadeInToMusic), // 09
    add_mapsetup(LoadBlockData), // 0a (callback 1)
    add_mapsetup(LoadConnectionBlockData), // 0b
    add_mapsetup(SaveScreen), // 0c
    add_mapsetup(BufferScreen), // 0d
    add_mapsetup(LoadMapGraphics), // 0e
    add_mapsetup(LoadMapTileset), // 0f
    add_mapsetup(LoadMapTimeOfDay), // 10
    add_mapsetup(LoadMapPalettes), // 11
    add_mapsetup(LoadWildMonData), // 12
    add_mapsetup(RefreshMapSprites), // 13
    add_mapsetup(HandleNewMap), // 14
    add_mapsetup(HandleContinueMap), // 15
    add_mapsetup(LoadMapObjects), // 16
    add_mapsetup(EnterMapSpawnPoint), // 17
    add_mapsetup(EnterMapConnection), // 18
    add_mapsetup(EnterMapWarp), // 19
    add_mapsetup(LoadMapAttributes), // 1a
    add_mapsetup(LoadMapAttributes_SkipObjects), // 1b
    add_mapsetup(ClearBGPalettes), // 1c
    add_mapsetup(FadeOutPalettes), // 1d
    add_mapsetup(FadeInPalettes), // 1e
    add_mapsetup(GetMapScreenCoords), // 1f
    add_mapsetup(GetWarpDestCoords), // 20
    add_mapsetup(SpawnInFacingDown), // 21
    add_mapsetup(SpawnPlayer), // 22
    add_mapsetup(RefreshPlayerCoords), // 23
    add_mapsetup(ResetPlayerObjectAction), // 24
    add_mapsetup(SkipUpdateMapSprites), // 25
    add_mapsetup(UpdateRoamMons), // 26
    add_mapsetup(JumpRoamMons), // 27
    add_mapsetup(FadeOutMapMusic), // 28
    add_mapsetup(ActivateMapAnims), // 29
    add_mapsetup(SuspendMapAnims), // 2a
    add_mapsetup(ApplyMapPalettes), // 2b
    add_mapsetup(EnableTextAcceleration), // 2c
    add_mapsetup(InitMapNameSign), // 2d
};