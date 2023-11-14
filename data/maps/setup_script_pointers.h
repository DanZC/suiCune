#pragma once

#define mapsetup_const(_x) _x##_SetupCommand

enum {
    mapsetup_const(EnableLCD), // 00
    mapsetup_const(DisableLCD), // 01
    mapsetup_const(InitSound), // 02
    mapsetup_const(PlayMapMusic), // 03
    mapsetup_const(RestartMapMusic), // 04
    mapsetup_const(FadeToMapMusic), // 05
    mapsetup_const(FadeMapMusicAndPalettes), // 06
    mapsetup_const(PlayMapMusicBike), // 07
    mapsetup_const(ForceMapMusic), // 08
    mapsetup_const(FadeInToMusic), // 09
    mapsetup_const(LoadBlockData), // 0a (callback 1)
    mapsetup_const(LoadConnectionBlockData), // 0b
    mapsetup_const(SaveScreen), // 0c
    mapsetup_const(BufferScreen), // 0d
    mapsetup_const(LoadMapGraphics), // 0e
    mapsetup_const(LoadMapTileset), // 0f
    mapsetup_const(LoadMapTimeOfDay), // 10
    mapsetup_const(LoadMapPalettes), // 11
    mapsetup_const(LoadWildMonData), // 12
    mapsetup_const(RefreshMapSprites), // 13
    mapsetup_const(HandleNewMap), // 14
    mapsetup_const(HandleContinueMap), // 15
    mapsetup_const(LoadMapObjects), // 16
    mapsetup_const(EnterMapSpawnPoint), // 17
    mapsetup_const(EnterMapConnection), // 18
    mapsetup_const(EnterMapWarp), // 19
    mapsetup_const(LoadMapAttributes), // 1a
    mapsetup_const(LoadMapAttributes_SkipObjects), // 1b
    mapsetup_const(ClearBGPalettes), // 1c
    mapsetup_const(FadeOutPalettes), // 1d
    mapsetup_const(FadeInPalettes), // 1e
    mapsetup_const(GetMapScreenCoords), // 1f
    mapsetup_const(GetWarpDestCoords), // 20
    mapsetup_const(SpawnInFacingDown), // 21
    mapsetup_const(SpawnPlayer), // 22
    mapsetup_const(RefreshPlayerCoords), // 23
    mapsetup_const(ResetPlayerObjectAction), // 24
    mapsetup_const(SkipUpdateMapSprites), // 25
    mapsetup_const(UpdateRoamMons), // 26
    mapsetup_const(JumpRoamMons), // 27
    mapsetup_const(FadeOutMapMusic), // 28
    mapsetup_const(ActivateMapAnims), // 29
    mapsetup_const(SuspendMapAnims), // 2a
    mapsetup_const(ApplyMapPalettes), // 2b
    mapsetup_const(EnableTextAcceleration), // 2c
    mapsetup_const(InitMapNameSign), // 2d
};

extern void (*const MapSetupCommands[])(void);
