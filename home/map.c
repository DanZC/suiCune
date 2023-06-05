#include "../constants.h"
#include "map.h"
#include "copy.h"
#include "array.h"
#include "gfx.h"

//  Functions dealing with rendering and interacting with maps.

void ClearUnusedMapBuffer(void){
    LD_HL(wUnusedMapBuffer);
    LD_BC(wUnusedMapBufferEnd - wUnusedMapBuffer);
    LD_A(0);
    CALL(aByteFill);
    RET;

}

void ClearUnusedMapBuffer_Conv(void){
    ByteFill_Conv(wUnusedMapBuffer, (wUnusedMapBufferEnd - wUnusedMapBuffer), 0);
}

void CheckScenes(void){
//  Checks wCurMapSceneScriptPointer.  If it's empty, returns -1 in a.  Otherwise, returns the active scene ID in a.
    PUSH_HL;
    LD_HL(wCurMapSceneScriptPointer);
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    OR_A_H;
    LD_A_hl;
    IF_NZ goto scene_exists;
    LD_A(-1);


scene_exists:
    POP_HL;
    RET;

}

void GetCurrentMapSceneID(void){
//  Grabs the wram map scene script pointer for the current map and loads it into wCurMapSceneScriptPointer.
//  If there is no scene, both bytes of wCurMapSceneScriptPointer are wiped clean.
//  Copy the current map group and number into bc.  This is needed for GetMapSceneID.
    LD_A_addr(wMapGroup);
    LD_B_A;
    LD_A_addr(wMapNumber);
    LD_C_A;
//  Blank out wCurMapSceneScriptPointer
    XOR_A_A;
    LD_addr_A(wCurMapSceneScriptPointer);
    LD_addr_A(wCurMapSceneScriptPointer + 1);
    CALL(aGetMapSceneID);
    RET_C ;  // The map is not in the scene script table
//  Load the scene script pointer from de into wCurMapSceneScriptPointer
    LD_A_E;
    LD_addr_A(wCurMapSceneScriptPointer);
    LD_A_D;
    LD_addr_A(wCurMapSceneScriptPointer + 1);
    XOR_A_A;
    RET;

}

void GetMapSceneID(void){
//  Searches the scene_var table for the map group and number loaded in bc, and returns the wram pointer in de.
//  If the map is not in the scene_var table, returns carry.
    PUSH_BC;
    LDH_A_addr(hROMBank);
    PUSH_AF;
    LD_A(BANK(aMapScenes));
    RST(aBankswitch);

    LD_HL(mMapScenes);

loop:
    PUSH_HL;
    LD_A_hli;  // map group, or terminator
    CP_A(-1);
    IF_Z goto end;  // the current map is not in the scene_var table
    CP_A_B;
    IF_NZ goto next;  // map group did not match
    LD_A_hli;  // map number
    CP_A_C;
    IF_NZ goto next;  // map number did not match
    goto found;  // we found our map


next:
    POP_HL;
    LD_DE(4);  // scene_var size
    ADD_HL_DE;
    goto loop;


end:
    SCF;
    goto done;


found:
    LD_E_hl;
    INC_HL;
    LD_D_hl;


done:
    POP_HL;
    POP_BC;
    LD_A_B;
    RST(aBankswitch);

    POP_BC;
    RET;

}

void OverworldTextModeSwitch(void){
    CALL(aLoadMapPart);
    CALL(aSwapTextboxPalettes);
    RET;

}

void LoadMapPart(void){
    LDH_A_addr(hROMBank);
    PUSH_AF;

    LD_A_addr(wTilesetBlocksBank);
    RST(aBankswitch);
    CALL(aLoadMetatiles);

    LD_A(0x60);
    hlcoord(0, 0, wTilemap);
    LD_BC(SCREEN_WIDTH * SCREEN_HEIGHT);
    CALL(aByteFill);

    LD_A(BANK(av_LoadMapPart));
    RST(aBankswitch);
    CALL(av_LoadMapPart);

    POP_AF;
    RST(aBankswitch);
    RET;

}

void LoadMetatiles(void){
// de <- wOverworldMapAnchor
    LD_A_addr(wOverworldMapAnchor);
    LD_E_A;
    LD_A_addr(wOverworldMapAnchor + 1);
    LD_D_A;
    LD_HL(wSurroundingTiles);
    LD_B(SCREEN_META_HEIGHT);


row:
    PUSH_DE;
    PUSH_HL;
    LD_C(SCREEN_META_WIDTH);


col:
    PUSH_DE;
    PUSH_HL;
// Load the current map block.
// If the current map block is a border block, load the border block.
    LD_A_de;
    AND_A_A;
    IF_NZ goto ok;
    LD_A_addr(wMapBorderBlock);


ok:
// Load the current wSurroundingTiles address into de.
    LD_E_L;
    LD_D_H;
// Set hl to the address of the current metatile data ([wTilesetBlocksAddress] + (a) tiles).
// This is buggy// it wraps around past 128 blocks.
// To fix, uncomment the line below.
    ADD_A_A;  // Comment or delete this line to fix the above bug.
    LD_L_A;
    LD_H(0);
// add hl, hl
    ADD_HL_HL;
    ADD_HL_HL;
    ADD_HL_HL;
    LD_A_addr(wTilesetBlocksAddress);
    ADD_A_L;
    LD_L_A;
    LD_A_addr(wTilesetBlocksAddress + 1);
    ADC_A_H;
    LD_H_A;

// copy the 4x4 metatile
    for(int rept = 0; rept < METATILE_WIDTH - 1; rept++){
    for(int rept2 = 0; rept2 < METATILE_WIDTH; rept2++){
    LD_A_hli;
    LD_de_A;
    INC_DE;
    }
    LD_A_E;
    ADD_A(SURROUNDING_WIDTH - METATILE_WIDTH);
    LD_E_A;
    IF_NC goto next;
    INC_D;
    }
next:
    for(int rept = 0; rept < METATILE_WIDTH; rept++){
    LD_A_hli;
    LD_de_A;
    INC_DE;
    }
// Next metatile
    POP_HL;
    LD_DE(METATILE_WIDTH);
    ADD_HL_DE;
    POP_DE;
    INC_DE;
    DEC_C;
    JP_NZ (mLoadMetatiles_col);
// Next metarow
    POP_HL;
    LD_DE(SURROUNDING_WIDTH * METATILE_WIDTH);
    ADD_HL_DE;
    POP_DE;
    LD_A_addr(wMapWidth);
    ADD_A(MAP_CONNECTION_PADDING_WIDTH * 2);
    ADD_A_E;
    LD_E_A;
    IF_NC goto ok2;
    INC_D;

ok2:
    DEC_B;
    JP_NZ (mLoadMetatiles_row);
    RET;

}

void ReturnToMapFromSubmenu(void){
    LD_A(MAPSETUP_SUBMENU);
    LDH_addr_A(hMapEntryMethod);
    FARCALL(aRunMapSetupScript);
    XOR_A_A;
    LDH_addr_A(hMapEntryMethod);
    RET;

}

void CheckWarpTile(void){
    CALL(aGetDestinationWarpNumber);
    RET_NC ;

    PUSH_BC;
    FARCALL(aCheckDirectionalWarp);
    POP_BC;
    RET_NC ;

    CALL(aCopyWarpData);
    SCF;
    RET;

}

void WarpCheck(void){
    CALL(aGetDestinationWarpNumber);
    RET_NC ;
    CALL(aCopyWarpData);
    RET;

}

void GetDestinationWarpNumber(void){
    FARCALL(aCheckWarpCollision);
    RET_NC ;

    LDH_A_addr(hROMBank);
    PUSH_AF;

    CALL(aSwitchToMapScriptsBank);
    CALL(aGetDestinationWarpNumber_GetDestinationWarpNumber);

    POP_DE;
    LD_A_D;
    RST(aBankswitch);
    RET;


GetDestinationWarpNumber:
    LD_A_addr(wPlayerStandingMapY);
    SUB_A(4);
    LD_E_A;
    LD_A_addr(wPlayerStandingMapX);
    SUB_A(4);
    LD_D_A;
    LD_A_addr(wCurMapWarpCount);
    AND_A_A;
    RET_Z ;

    LD_C_A;
    LD_HL(wCurMapWarpsPointer);
    LD_A_hli;
    LD_H_hl;
    LD_L_A;

loop:
    PUSH_HL;
    LD_A_hli;
    CP_A_E;
    IF_NZ goto next;
    LD_A_hli;
    CP_A_D;
    IF_NZ goto next;
    goto found_warp;


next:
    POP_HL;
    LD_A(WARP_EVENT_SIZE);
    ADD_A_L;
    LD_L_A;
    IF_NC goto okay;
    INC_H;


okay:
    DEC_C;
    IF_NZ goto loop;
    XOR_A_A;
    RET;


found_warp:
    POP_HL;
    CALL(aGetDestinationWarpNumber_IncreaseHLTwice);
    RET_NC ;  // never encountered

    LD_A_addr(wCurMapWarpCount);
    INC_A;
    SUB_A_C;
    LD_C_A;
    SCF;
    RET;


IncreaseHLTwice:
    INC_HL;
    INC_HL;
    SCF;
    RET;

}

void CopyWarpData(void){
    LDH_A_addr(hROMBank);
    PUSH_AF;

    CALL(aSwitchToMapScriptsBank);
    CALL(aCopyWarpData_CopyWarpData);

    POP_AF;
    RST(aBankswitch);
    SCF;
    RET;


CopyWarpData:
    PUSH_BC;
    LD_HL(wCurMapWarpsPointer);
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    LD_A_C;
    DEC_A;
    LD_BC(WARP_EVENT_SIZE);
    CALL(aAddNTimes);
    LD_BC(2);  // warp number
    ADD_HL_BC;
    LD_A_hli;
    CP_A(-1);
    IF_NZ goto skip;
    LD_HL(wBackupWarpNumber);
    LD_A_hli;


skip:
    POP_BC;
    LD_addr_A(wNextWarp);
    LD_A_hli;
    LD_addr_A(wNextMapGroup);
    LD_A_hli;
    LD_addr_A(wNextMapNumber);

    LD_A_C;
    LD_addr_A(wPrevWarp);
    LD_A_addr(wMapGroup);
    LD_addr_A(wPrevMapGroup);
    LD_A_addr(wMapNumber);
    LD_addr_A(wPrevMapNumber);
    SCF;
    RET;

}

void CheckOutdoorMap(void){
    CP_A(ROUTE);
    RET_Z ;
    CP_A(TOWN);
    RET;

}

void CheckIndoorMap(void){
    CP_A(INDOOR);
    RET_Z ;
    CP_A(CAVE);
    RET_Z ;
    CP_A(DUNGEON);
    RET_Z ;
    CP_A(GATE);
    RET;

}

void CheckUnknownMap(void){
//  //  unreferenced
    CP_A(INDOOR);
    RET_Z ;
    CP_A(GATE);
    RET_Z ;
    CP_A(ENVIRONMENT_5);
    RET;

}

void LoadMapAttributes(void){
    CALL(aCopyMapPartialAndAttributes);
    CALL(aSwitchToMapScriptsBank);
    CALL(aReadMapScripts);
    XOR_A_A;  // do not skip object events
    CALL(aReadMapEvents);
    RET;

}

void LoadMapAttributes_SkipObjects(void){
    CALL(aCopyMapPartialAndAttributes);
    CALL(aSwitchToMapScriptsBank);
    CALL(aReadMapScripts);
    LD_A(TRUE);  // skip object events
    CALL(aReadMapEvents);
    RET;

}

void CopyMapPartialAndAttributes(void){
    CALL(aCopyMapPartial);
    CALL(aSwitchToMapAttributesBank);
    CALL(aGetMapAttributesPointer);
    CALL(aCopyMapAttributes);
    CALL(aGetMapConnections);
    RET;

}

void ReadMapEvents(void){
    PUSH_AF;
    LD_HL(wMapEventsPointer);
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    INC_HL;
    INC_HL;
    CALL(aReadWarps);
    CALL(aReadCoordEvents);
    CALL(aReadBGEvents);

    POP_AF;
    AND_A_A;  // skip object events?
    RET_NZ ;

    CALL(aReadObjectEvents);
    RET;

}

void ReadMapScripts(void){
    LD_HL(wMapScriptsPointer);
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    CALL(aReadMapSceneScripts);
    CALL(aReadMapCallbacks);
    RET;

}

void CopyMapAttributes(void){
    LD_DE(wMapAttributes);
    LD_C(wMapAttributesEnd - wMapAttributes);

loop:
    LD_A_hli;
    LD_de_A;
    INC_DE;
    DEC_C;
    IF_NZ goto loop;
    RET;

}

void GetMapConnections(void){
    LD_A(0xff);
    LD_addr_A(wNorthConnectedMapGroup);
    LD_addr_A(wSouthConnectedMapGroup);
    LD_addr_A(wWestConnectedMapGroup);
    LD_addr_A(wEastConnectedMapGroup);

    LD_A_addr(wMapConnections);
    LD_B_A;

    BIT_B(NORTH_F);
    IF_Z goto no_north;
    LD_DE(wNorthMapConnection);
    CALL(aGetMapConnection);

no_north:

    BIT_B(SOUTH_F);
    IF_Z goto no_south;
    LD_DE(wSouthMapConnection);
    CALL(aGetMapConnection);

no_south:

    BIT_B(WEST_F);
    IF_Z goto no_west;
    LD_DE(wWestMapConnection);
    CALL(aGetMapConnection);

no_west:

    BIT_B(EAST_F);
    IF_Z goto no_east;
    LD_DE(wEastMapConnection);
    CALL(aGetMapConnection);

no_east:

    RET;

}

void GetMapConnection(void){
//  Load map connection struct at hl into de.
    LD_C(wSouthMapConnection - wNorthMapConnection);

loop:
    LD_A_hli;
    LD_de_A;
    INC_DE;
    DEC_C;
    IF_NZ goto loop;
    RET;

}

void ReadMapSceneScripts(void){
    LD_A_hli;  // scene_script count
    LD_C_A;
    LD_addr_A(wCurMapSceneScriptCount);
    LD_A_L;
    LD_addr_A(wCurMapSceneScriptsPointer);
    LD_A_H;
    LD_addr_A(wCurMapSceneScriptsPointer + 1);
    LD_A_C;
    AND_A_A;
    RET_Z ;

    LD_BC(SCENE_SCRIPT_SIZE);
    CALL(aAddNTimes);
    RET;

}

void ReadMapCallbacks(void){
    LD_A_hli;
    LD_C_A;
    LD_addr_A(wCurMapCallbackCount);
    LD_A_L;
    LD_addr_A(wCurMapCallbacksPointer);
    LD_A_H;
    LD_addr_A(wCurMapCallbacksPointer + 1);
    LD_A_C;
    AND_A_A;
    RET_Z ;

    LD_BC(CALLBACK_SIZE);
    CALL(aAddNTimes);
    RET;

}

void ReadWarps(void){
    LD_A_hli;
    LD_C_A;
    LD_addr_A(wCurMapWarpCount);
    LD_A_L;
    LD_addr_A(wCurMapWarpsPointer);
    LD_A_H;
    LD_addr_A(wCurMapWarpsPointer + 1);
    LD_A_C;
    AND_A_A;
    RET_Z ;
    LD_BC(WARP_EVENT_SIZE);
    CALL(aAddNTimes);
    RET;

}

void ReadCoordEvents(void){
    LD_A_hli;
    LD_C_A;
    LD_addr_A(wCurMapCoordEventCount);
    LD_A_L;
    LD_addr_A(wCurMapCoordEventsPointer);
    LD_A_H;
    LD_addr_A(wCurMapCoordEventsPointer + 1);

    LD_A_C;
    AND_A_A;
    RET_Z ;

    LD_BC(COORD_EVENT_SIZE);
    CALL(aAddNTimes);
    RET;

}

void ReadBGEvents(void){
    LD_A_hli;
    LD_C_A;
    LD_addr_A(wCurMapBGEventCount);
    LD_A_L;
    LD_addr_A(wCurMapBGEventsPointer);
    LD_A_H;
    LD_addr_A(wCurMapBGEventsPointer + 1);

    LD_A_C;
    AND_A_A;
    RET_Z ;

    LD_BC(BG_EVENT_SIZE);
    CALL(aAddNTimes);
    RET;

}

void ReadObjectEvents(void){
    PUSH_HL;
    CALL(aClearObjectStructs);
    POP_DE;
    LD_HL(wMap1Object);
    LD_A_de;
    INC_DE;
    LD_addr_A(wCurMapObjectEventCount);
    LD_A_E;
    LD_addr_A(wCurMapObjectEventsPointer);
    LD_A_D;
    LD_addr_A(wCurMapObjectEventsPointer + 1);

    LD_A_addr(wCurMapObjectEventCount);
    CALL(aCopyMapObjectEvents);

//  get NUM_OBJECTS - [wCurMapObjectEventCount]
    LD_A_addr(wCurMapObjectEventCount);
    LD_C_A;
    LD_A(NUM_OBJECTS);  // - 1
    SUB_A_C;
    IF_Z goto skip;
// jr c, .skip

// could have done "inc hl" instead
    LD_BC(1);
    ADD_HL_BC;
//  Fill the remaining sprite IDs and y coords with 0 and -1, respectively.
//  Bleeds into wObjectMasks due to a bug.  Uncomment the above code to fix.
    LD_BC(MAPOBJECT_LENGTH);

loop:
    LD_hl(0);
    INC_HL;
    LD_hl(-1);
    DEC_HL;
    ADD_HL_BC;
    DEC_A;
    IF_NZ goto loop;


skip:
    LD_H_D;
    LD_L_E;
    RET;

}

void CopyMapObjectEvents(void){
    AND_A_A;
    RET_Z ;

    LD_C_A;

loop:
    PUSH_BC;
    PUSH_HL;
    LD_A(0xff);
    LD_hli_A;
    LD_B(OBJECT_EVENT_SIZE);

loop2:
    LD_A_de;
    INC_DE;
    LD_hli_A;
    DEC_B;
    IF_NZ goto loop2;

    POP_HL;
    LD_BC(MAPOBJECT_LENGTH);
    ADD_HL_BC;
    POP_BC;
    DEC_C;
    IF_NZ goto loop;
    RET;

}

void ClearObjectStructs(void){
    LD_HL(wObject1Struct);
    LD_BC(OBJECT_LENGTH * (NUM_OBJECT_STRUCTS - 1));
    XOR_A_A;
    CALL(aByteFill);

//  Just to make sure (this is rather pointless)
    LD_HL(wObject1Struct);
    LD_DE(OBJECT_LENGTH);
    LD_C(NUM_OBJECT_STRUCTS - 1);
    XOR_A_A;

loop:
    LD_hl_A;
    ADD_HL_DE;
    DEC_C;
    IF_NZ goto loop;
    RET;

}

void GetWarpDestCoords(void){
    CALL(aGetMapScriptsBank);
    RST(aBankswitch);

    LD_HL(wMapEventsPointer);
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    for(int rept = 0; rept < 3; rept++){  //  get to the warp coords
    INC_HL;
    }
    LD_A_addr(wWarpNumber);
    DEC_A;
    LD_C_A;
    LD_B(0);
    LD_A(WARP_EVENT_SIZE);
    CALL(aAddNTimes);
    LD_A_hli;
    LD_addr_A(wYCoord);
    LD_A_hli;
    LD_addr_A(wXCoord);
// destination warp number
    LD_A_hli;
    CP_A(-1);
    IF_NZ goto skip;
    CALL(aGetWarpDestCoords_backup);


skip:
    FARCALL(aGetMapScreenCoords);
    RET;


backup:
    LD_A_addr(wPrevWarp);
    LD_addr_A(wBackupWarpNumber);
    LD_A_addr(wPrevMapGroup);
    LD_addr_A(wBackupMapGroup);
    LD_A_addr(wPrevMapNumber);
    LD_addr_A(wBackupMapNumber);
    RET;

}

void LoadBlockData(void){
    LD_HL(wOverworldMapBlocks);
    LD_BC(wOverworldMapBlocksEnd - wOverworldMapBlocks);
    LD_A(0);
    CALL(aByteFill);
    CALL(aChangeMap);
    CALL(aFillMapConnections);
    LD_A(MAPCALLBACK_TILES);
    CALL(aRunMapCallback);
    RET;

}

void ChangeMap(void){
    LDH_A_addr(hROMBank);
    PUSH_AF;

    LD_HL(wOverworldMapBlocks);
    LD_A_addr(wMapWidth);
    LDH_addr_A(hConnectedMapWidth);
    ADD_A(0x6);
    LDH_addr_A(hConnectionStripLength);
    LD_C_A;
    LD_B(0);
    ADD_HL_BC;
    ADD_HL_BC;
    ADD_HL_BC;
    LD_C(3);
    ADD_HL_BC;
    LD_A_addr(wMapBlocksBank);
    RST(aBankswitch);

    LD_A_addr(wMapBlocksPointer);
    LD_E_A;
    LD_A_addr(wMapBlocksPointer + 1);
    LD_D_A;
    LD_A_addr(wMapHeight);
    LD_B_A;

row:
    PUSH_HL;
    LDH_A_addr(hConnectedMapWidth);
    LD_C_A;

col:
    LD_A_de;
    INC_DE;
    LD_hli_A;
    DEC_C;
    IF_NZ goto col;
    POP_HL;
    LDH_A_addr(hConnectionStripLength);
    ADD_A_L;
    LD_L_A;
    IF_NC goto okay;
    INC_H;

okay:
    DEC_B;
    IF_NZ goto row;

    POP_AF;
    RST(aBankswitch);
    RET;

}

void FillMapConnections(void){
//  North
    LD_A_addr(wNorthConnectedMapGroup);
    CP_A(0xff);
    IF_Z goto South;
    LD_B_A;
    LD_A_addr(wNorthConnectedMapNumber);
    LD_C_A;
    CALL(aGetAnyMapBlocksBank);

    LD_A_addr(wNorthConnectionStripPointer);
    LD_L_A;
    LD_A_addr(wNorthConnectionStripPointer + 1);
    LD_H_A;
    LD_A_addr(wNorthConnectionStripLocation);
    LD_E_A;
    LD_A_addr(wNorthConnectionStripLocation + 1);
    LD_D_A;
    LD_A_addr(wNorthConnectionStripLength);
    LDH_addr_A(hConnectionStripLength);
    LD_A_addr(wNorthConnectedMapWidth);
    LDH_addr_A(hConnectedMapWidth);
    CALL(aFillNorthConnectionStrip);


South:
    LD_A_addr(wSouthConnectedMapGroup);
    CP_A(0xff);
    IF_Z goto West;
    LD_B_A;
    LD_A_addr(wSouthConnectedMapNumber);
    LD_C_A;
    CALL(aGetAnyMapBlocksBank);

    LD_A_addr(wSouthConnectionStripPointer);
    LD_L_A;
    LD_A_addr(wSouthConnectionStripPointer + 1);
    LD_H_A;
    LD_A_addr(wSouthConnectionStripLocation);
    LD_E_A;
    LD_A_addr(wSouthConnectionStripLocation + 1);
    LD_D_A;
    LD_A_addr(wSouthConnectionStripLength);
    LDH_addr_A(hConnectionStripLength);
    LD_A_addr(wSouthConnectedMapWidth);
    LDH_addr_A(hConnectedMapWidth);
    CALL(aFillSouthConnectionStrip);


West:
    LD_A_addr(wWestConnectedMapGroup);
    CP_A(0xff);
    IF_Z goto East;
    LD_B_A;
    LD_A_addr(wWestConnectedMapNumber);
    LD_C_A;
    CALL(aGetAnyMapBlocksBank);

    LD_A_addr(wWestConnectionStripPointer);
    LD_L_A;
    LD_A_addr(wWestConnectionStripPointer + 1);
    LD_H_A;
    LD_A_addr(wWestConnectionStripLocation);
    LD_E_A;
    LD_A_addr(wWestConnectionStripLocation + 1);
    LD_D_A;
    LD_A_addr(wWestConnectionStripLength);
    LD_B_A;
    LD_A_addr(wWestConnectedMapWidth);
    LDH_addr_A(hConnectionStripLength);
    CALL(aFillWestConnectionStrip);


East:
    LD_A_addr(wEastConnectedMapGroup);
    CP_A(0xff);
    IF_Z goto Done;
    LD_B_A;
    LD_A_addr(wEastConnectedMapNumber);
    LD_C_A;
    CALL(aGetAnyMapBlocksBank);

    LD_A_addr(wEastConnectionStripPointer);
    LD_L_A;
    LD_A_addr(wEastConnectionStripPointer + 1);
    LD_H_A;
    LD_A_addr(wEastConnectionStripLocation);
    LD_E_A;
    LD_A_addr(wEastConnectionStripLocation + 1);
    LD_D_A;
    LD_A_addr(wEastConnectionStripLength);
    LD_B_A;
    LD_A_addr(wEastConnectedMapWidth);
    LDH_addr_A(hConnectionStripLength);
    CALL(aFillEastConnectionStrip);


Done:
    RET;

}

void FillNorthConnectionStrip(void){
    return FillSouthConnectionStrip();
}

void FillSouthConnectionStrip(void){
    LD_C(3);

y:
    PUSH_DE;

    PUSH_HL;
    LDH_A_addr(hConnectionStripLength);
    LD_B_A;

x:
    LD_A_hli;
    LD_de_A;
    INC_DE;
    DEC_B;
    IF_NZ goto x;
    POP_HL;

    LDH_A_addr(hConnectedMapWidth);
    LD_E_A;
    LD_D(0);
    ADD_HL_DE;
    POP_DE;

    LD_A_addr(wMapWidth);
    ADD_A(6);
    ADD_A_E;
    LD_E_A;
    IF_NC goto okay;
    INC_D;

okay:
    DEC_C;
    IF_NZ goto y;
    RET;

}

void FillWestConnectionStrip(void){
    return FillEastConnectionStrip();
}

void FillEastConnectionStrip(void){

loop:
    LD_A_addr(wMapWidth);
    ADD_A(6);
    LDH_addr_A(hConnectedMapWidth);

    PUSH_DE;

    PUSH_HL;
    LD_A_hli;
    LD_de_A;
    INC_DE;
    LD_A_hli;
    LD_de_A;
    INC_DE;
    LD_A_hli;
    LD_de_A;
    INC_DE;
    POP_HL;

    LDH_A_addr(hConnectionStripLength);
    LD_E_A;
    LD_D(0);
    ADD_HL_DE;
    POP_DE;

    LDH_A_addr(hConnectedMapWidth);
    ADD_A_E;
    LD_E_A;
    IF_NC goto okay;
    INC_D;

okay:
    DEC_B;
    IF_NZ goto loop;
    RET;

}

void LoadMapStatus(void){
    LD_addr_A(wMapStatus);
    RET;

}

void CallScript(void){
//  Call a script at a:hl.

    LD_addr_A(wScriptBank);
    LD_A_L;
    LD_addr_A(wScriptPos);
    LD_A_H;
    LD_addr_A(wScriptPos + 1);

    LD_A(PLAYEREVENT_MAPSCRIPT);
    LD_addr_A(wScriptRunning);

    SCF;
    RET;

}

void CallScript_Conv(uint8_t a, uint16_t hl){
//  Call a script at a:hl.

    // LD_addr_A(wScriptBank);
    // LD_A_L;
    // LD_addr_A(wScriptPos);
    // LD_A_H;
    // LD_addr_A(wScriptPos + 1);
    gb_write(wScriptBank, a);
    gb_write16(wScriptPos, hl);

    // LD_A(PLAYEREVENT_MAPSCRIPT);
    // LD_addr_A(wScriptRunning);
    gb_write(wScriptRunning, PLAYEREVENT_MAPSCRIPT);

    // SCF;
    // RET;
}

void CallMapScript(void){
//  Call a script at hl in the current bank if there isn't already a script running
    LD_A_addr(wScriptRunning);
    AND_A_A;
    RET_NZ ;
    CALL(aGetMapScriptsBank);
    JR(mCallScript);

}

void CallMapScript_Conv(uint16_t hl){
//  Call a script at hl in the current bank if there isn't already a script running
    // LD_A_addr(wScriptRunning);
    // AND_A_A;
    // RET_NZ ;
    if(gb_read(wScriptRunning) != 0)
        return;
    
    // CALL(aGetMapScriptsBank);
    // JR(mCallScript);
    return CallScript_Conv(GetMapScriptsBank_Conv(), hl);
}

void RunMapCallback(void){
//  Will run the first callback found with execution index equal to a.
    LD_B_A;
    LDH_A_addr(hROMBank);
    PUSH_AF;
    CALL(aSwitchToMapScriptsBank);
    CALL(aRunMapCallback_FindCallback);
    IF_NC goto done;

    CALL(aGetMapScriptsBank);
    LD_B_A;
    LD_D_H;
    LD_E_L;
    CALL(aExecuteCallbackScript);


done:
    POP_AF;
    RST(aBankswitch);
    RET;


FindCallback:
    LD_A_addr(wCurMapCallbackCount);
    LD_C_A;
    AND_A_A;
    RET_Z ;
    LD_HL(wCurMapCallbacksPointer);
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    OR_A_H;
    RET_Z ;
    LD_DE(CALLBACK_SIZE);

loop:
    LD_A_hl;
    CP_A_B;
    IF_Z goto found;
    ADD_HL_DE;
    DEC_C;
    IF_NZ goto loop;
    XOR_A_A;
    RET;


found:
    INC_HL;
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    SCF;
    RET;

}

void ExecuteCallbackScript(void){
//  Do map callback de and return to script bank b.
    FARCALL(aCallCallback);
    LD_A_addr(wScriptMode);
    PUSH_AF;
    LD_HL(wScriptFlags);
    LD_A_hl;
    PUSH_AF;
    SET_hl(1);
    FARCALL(aEnableScriptMode);
    FARCALL(aScriptEvents);
    POP_AF;
    LD_addr_A(wScriptFlags);
    POP_AF;
    LD_addr_A(wScriptMode);
    RET;

}

void MapTextbox(void){
    LDH_A_addr(hROMBank);
    PUSH_AF;

    LD_A_B;
    RST(aBankswitch);

    PUSH_HL;
    CALL(aSpeechTextbox);
    CALL(aSafeUpdateSprites);
    LD_A(1);
    LDH_addr_A(hOAMUpdate);
    CALL(aApplyTilemap);
    POP_HL;
    CALL(aPrintTextboxText);
    XOR_A_A;
    LDH_addr_A(hOAMUpdate);

    POP_AF;
    RST(aBankswitch);
    RET;

}

void Call_a_de(void){
//  Call a:de.

    LDH_addr_A(hTempBank);
    LDH_A_addr(hROMBank);
    PUSH_AF;
    LDH_A_addr(hTempBank);
    RST(aBankswitch);

    CALL(aCall_a_de_de);

    POP_AF;
    RST(aBankswitch);
    RET;


de:
    PUSH_DE;
    RET;

}

void GetMovementData(void){
//  Initialize the movement data for object c at b:hl
    LDH_A_addr(hROMBank);
    PUSH_AF;
    LD_A_B;
    RST(aBankswitch);

    LD_A_C;
    CALL(aLoadMovementDataPointer);

    POP_HL;
    LD_A_H;
    RST(aBankswitch);
    RET;

}

void GetScriptByte(void){
//  Return byte at wScriptBank:wScriptPos in a.

    PUSH_HL;
    PUSH_BC;
    LDH_A_addr(hROMBank);
    PUSH_AF;
    LD_A_addr(wScriptBank);
    RST(aBankswitch);

    LD_HL(wScriptPos);
    LD_C_hl;
    INC_HL;
    LD_B_hl;

    LD_A_bc;

    INC_BC;
    LD_hl_B;
    DEC_HL;
    LD_hl_C;

    LD_B_A;
    POP_AF;
    RST(aBankswitch);
    LD_A_B;
    POP_BC;
    POP_HL;
    RET;

}

void ObjectEvent(void){
    //jumptextfaceplayer ['ObjectEventText']

    return ObjectEventText();
}

void ObjectEventText(void){
    //text_far ['_ObjectEventText']
    //text_end ['?']

    return BGEvent();
}

void BGEvent(void){
//  //  unreferenced
    //jumptext ['BGEventText']

    return BGEventText();
}

void BGEventText(void){
    //text_far ['_BGEventText']
    //text_end ['?']

    return CoordinatesEvent();
}

void CoordinatesEvent(void){
//  //  unreferenced
    //jumptext ['CoordinatesEventText']

    return CoordinatesEventText();
}

void CoordinatesEventText(void){
    //text_far ['_CoordinatesEventText']
    //text_end ['?']

    return CheckObjectMask();
}

void CheckObjectMask(void){
    LDH_A_addr(hMapObjectIndex);
    LD_E_A;
    LD_D(0);
    LD_HL(wObjectMasks);
    ADD_HL_DE;
    LD_A_hl;
    RET;

}

void MaskObject(void){
    LDH_A_addr(hMapObjectIndex);
    LD_E_A;
    LD_D(0);
    LD_HL(wObjectMasks);
    ADD_HL_DE;
    LD_hl(-1);  // masked
    RET;

}

void UnmaskObject(void){
    LDH_A_addr(hMapObjectIndex);
    LD_E_A;
    LD_D(0);
    LD_HL(wObjectMasks);
    ADD_HL_DE;
    LD_hl(0);  // unmasked
    RET;

}
//  if DEF(_DEBUG)
void ComputeROMXChecksum(void) {
#if defined(_DEBUG) && !defined(_MSC_VER)
    LDH_A_addr(hROMBank);
    PUSH_AF;
    LD_A_C;
    RST(aBankSwitch);
    LD_HL(0x4000);

loop:
    LD_A_hli;
    ADD_A_E;
    LD_E_A;
    LD_A_D;
    ADC_A(0);
    LD_D_A;
    LD_A_H;
    CP_A(0x80);
    IF_C goto loop;
    POP_AF;
    RST(aBankSwitch);
    RET;
#endif

    return ScrollMapUp();
}

void ScrollMapUp(void){
    hlcoord(0, 0, wTilemap);
    LD_DE(wBGMapBuffer);
    CALL(aBackupBGMapRow);
    LD_C(2 * SCREEN_WIDTH);
    CALL(aScrollBGMapPalettes);
    LD_A_addr(wBGMapAnchor);
    LD_E_A;
    LD_A_addr(wBGMapAnchor + 1);
    LD_D_A;
    CALL(aUpdateBGMapRow);
    LD_A(0x1);
    LDH_addr_A(hBGMapUpdate);
    RET;

}

void ScrollMapDown(void){
    hlcoord(0, SCREEN_HEIGHT - 2, wTilemap);
    LD_DE(wBGMapBuffer);
    CALL(aBackupBGMapRow);
    LD_C(2 * SCREEN_WIDTH);
    CALL(aScrollBGMapPalettes);
    LD_A_addr(wBGMapAnchor);
    LD_L_A;
    LD_A_addr(wBGMapAnchor + 1);
    LD_H_A;
    LD_BC(BG_MAP_WIDTH * LEN_2BPP_TILE);
    ADD_HL_BC;
//  cap d at HIGH(vBGMap0)
    LD_A_H;
    AND_A(0b00000011);
    OR_A(HIGH(vBGMap0));
    LD_E_L;
    LD_D_A;
    CALL(aUpdateBGMapRow);
    LD_A(0x1);
    LDH_addr_A(hBGMapUpdate);
    RET;

}

void ScrollMapLeft(void){
    hlcoord(0, 0, wTilemap);
    LD_DE(wBGMapBuffer);
    CALL(aBackupBGMapColumn);
    LD_C(2 * SCREEN_HEIGHT);
    CALL(aScrollBGMapPalettes);
    LD_A_addr(wBGMapAnchor);
    LD_E_A;
    LD_A_addr(wBGMapAnchor + 1);
    LD_D_A;
    CALL(aUpdateBGMapColumn);
    LD_A(0x1);
    LDH_addr_A(hBGMapUpdate);
    RET;

}

void ScrollMapRight(void){
    hlcoord(SCREEN_WIDTH - 2, 0, wTilemap);
    LD_DE(wBGMapBuffer);
    CALL(aBackupBGMapColumn);
    LD_C(2 * SCREEN_HEIGHT);
    CALL(aScrollBGMapPalettes);
    LD_A_addr(wBGMapAnchor);
    LD_E_A;
    AND_A(0b11100000);
    LD_B_A;
    LD_A_E;
    ADD_A(SCREEN_HEIGHT);
    AND_A(0b00011111);
    OR_A_B;
    LD_E_A;
    LD_A_addr(wBGMapAnchor + 1);
    LD_D_A;
    CALL(aUpdateBGMapColumn);
    LD_A(0x1);
    LDH_addr_A(hBGMapUpdate);
    RET;

}

void BackupBGMapRow(void){
    LD_C(2 * SCREEN_WIDTH);

loop:
    LD_A_hli;
    LD_de_A;
    INC_DE;
    DEC_C;
    IF_NZ goto loop;
    RET;

}

void BackupBGMapColumn(void){
    LD_C(SCREEN_HEIGHT);

loop:
    LD_A_hli;
    LD_de_A;
    INC_DE;
    LD_A_hl;
    LD_de_A;
    INC_DE;
    LD_A(SCREEN_WIDTH - 1);
    ADD_A_L;
    LD_L_A;
    IF_NC goto skip;
    INC_H;


skip:
    DEC_C;
    IF_NZ goto loop;
    RET;

}

void UpdateBGMapRow(void){
    LD_HL(wBGMapBufferPointers);
    PUSH_DE;
    CALL(aUpdateBGMapRow_iteration);
    POP_DE;
    LD_A(BG_MAP_WIDTH);
    ADD_A_E;
    LD_E_A;


iteration:
    LD_C(10);

loop:
    LD_A_E;
    LD_hli_A;
    LD_A_D;
    LD_hli_A;
    LD_A_E;
    INC_A;
    INC_A;
    AND_A(0x1f);
    LD_B_A;
    LD_A_E;
    AND_A(0xe0);
    OR_A_B;
    LD_E_A;
    DEC_C;
    IF_NZ goto loop;
    LD_A(SCREEN_WIDTH);
    LDH_addr_A(hBGMapTileCount);
    RET;

}

void UpdateBGMapColumn(void){
    LD_HL(wBGMapBufferPointers);
    LD_C(SCREEN_HEIGHT);

loop:
    LD_A_E;
    LD_hli_A;
    LD_A_D;
    LD_hli_A;
    LD_A(BG_MAP_WIDTH);
    ADD_A_E;
    LD_E_A;
    IF_NC goto skip;
    INC_D;
//  cap d at HIGH(vBGMap0)
    LD_A_D;
    AND_A(0b11);
    OR_A(HIGH(vBGMap0));
    LD_D_A;


skip:
    DEC_C;
    IF_NZ goto loop;
    LD_A(SCREEN_HEIGHT);
    LDH_addr_A(hBGMapTileCount);
    RET;

}

void ClearBGMapBuffer(void){
//  //  unreferenced
    LD_HL(wBGMapBuffer);
    LD_BC(wBGMapBufferEnd - wBGMapBuffer);
    XOR_A_A;
    CALL(aByteFill);
    RET;

}

void LoadTilesetGFX(void){
    LD_HL(wTilesetAddress);
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    LD_A_addr(wTilesetBank);
    LD_E_A;

    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(MBANK(awDecompressScratch));
    LDH_addr_A(rSVBK);

    LD_A_E;
    LD_DE(wDecompressScratch);
    CALL(aFarDecompress);

    LD_HL(wDecompressScratch);
    LD_DE(vTiles2);
    LD_BC(0x60 * LEN_2BPP_TILE);
    CALL(aCopyBytes);

    LDH_A_addr(rVBK);
    PUSH_AF;
    LD_A(MBANK(avTiles5));
    LDH_addr_A(rVBK);

    LD_HL(wDecompressScratch + 0x60 * LEN_2BPP_TILE);
    LD_DE(vTiles5);
    LD_BC(0x60 * LEN_2BPP_TILE);
    CALL(aCopyBytes);

    POP_AF;
    LDH_addr_A(rVBK);

    POP_AF;
    LDH_addr_A(rSVBK);

//  These tilesets support dynamic per-mapgroup roof tiles.
    LD_A_addr(wMapTileset);
    CP_A(TILESET_JOHTO);
    IF_Z goto load_roof;
    CP_A(TILESET_JOHTO_MODERN);
    IF_Z goto load_roof;
    CP_A(TILESET_BATTLE_TOWER_OUTSIDE);
    IF_Z goto load_roof;
    goto skip_roof;


load_roof:
    FARCALL(aLoadMapGroupRoof);


skip_roof:
    XOR_A_A;
    LDH_addr_A(hTileAnimFrame);
    RET;

}

void BufferScreen(void){
    LD_HL(wOverworldMapAnchor);
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    LD_DE(wScreenSave);
    LD_C(SCREEN_META_HEIGHT);
    LD_B(SCREEN_META_WIDTH);

row:
    PUSH_BC;
    PUSH_HL;

col:
    LD_A_hli;
    LD_de_A;
    INC_DE;
    DEC_B;
    IF_NZ goto col;
    POP_HL;
    LD_A_addr(wMapWidth);
    ADD_A(6);
    LD_C_A;
    LD_B(0);
    ADD_HL_BC;
    POP_BC;
    DEC_C;
    IF_NZ goto row;
    RET;

}

void SaveScreen(void){
    LD_HL(wOverworldMapAnchor);
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    LD_DE(wScreenSave);
    LD_A_addr(wMapWidth);
    ADD_A(6);
    LDH_addr_A(hMapObjectIndex);
    LD_A_addr(wPlayerStepDirection);
    AND_A_A;
    IF_Z goto down;
    CP_A(UP);
    IF_Z goto up;
    CP_A(LEFT);
    IF_Z goto left;
    CP_A(RIGHT);
    IF_Z goto right;
    RET;


up:
    LD_DE(wScreenSave + SCREEN_META_WIDTH);
    LDH_A_addr(hMapObjectIndex);
    LD_C_A;
    LD_B(0);
    ADD_HL_BC;
    goto vertical;


down:
    LD_DE(wScreenSave);

vertical:
    LD_B(SCREEN_META_WIDTH);
    LD_C(SCREEN_META_HEIGHT - 1);
    JR(mSaveScreen_LoadConnection);


left:
    LD_DE(wScreenSave + 1);
    INC_HL;
    goto horizontal;


right:
    LD_DE(wScreenSave);

horizontal:
    LD_B(SCREEN_META_WIDTH - 1);
    LD_C(SCREEN_META_HEIGHT);
    JR(mSaveScreen_LoadConnection);

}

void LoadConnectionBlockData(void){
    LD_HL(wOverworldMapAnchor);
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    LD_A_addr(wMapWidth);
    ADD_A(6);
    LDH_addr_A(hConnectionStripLength);
    LD_DE(wScreenSave);
    LD_B(SCREEN_META_WIDTH);
    LD_C(SCREEN_META_HEIGHT);

    return SaveScreen_LoadConnection();
}

void SaveScreen_LoadConnection(void){

row:
    PUSH_BC;
    PUSH_HL;
    PUSH_DE;

col:
    LD_A_de;
    INC_DE;
    LD_hli_A;
    DEC_B;
    IF_NZ goto col;
    POP_DE;
    LD_A_E;
    ADD_A(6);
    LD_E_A;
    IF_NC goto okay;
    INC_D;

okay:
    POP_HL;
    LDH_A_addr(hConnectionStripLength);
    LD_C_A;
    LD_B(0);
    ADD_HL_BC;
    POP_BC;
    DEC_C;
    IF_NZ goto row;
    RET;

}

void GetMovementPermissions(void){
    XOR_A_A;
    LD_addr_A(wTilePermissions);
    CALL(aGetMovementPermissions_LeftRight);
    CALL(aGetMovementPermissions_UpDown);
//  get coords of current tile
    LD_A_addr(wPlayerStandingMapX);
    LD_D_A;
    LD_A_addr(wPlayerStandingMapY);
    LD_E_A;
    CALL(aGetCoordTile);
    LD_addr_A(wPlayerStandingTile);
    CALL(aGetMovementPermissions_CheckHiNybble);
    RET_NZ ;

    LD_A_addr(wPlayerStandingTile);
    AND_A(7);
    LD_HL(mGetMovementPermissions_MovementPermissionsData);
    ADD_A_L;
    LD_L_A;
    LD_A(0);
    ADC_A_H;
    LD_H_A;
    LD_A_hl;
    LD_HL(wTilePermissions);
    OR_A_hl;
    LD_hl_A;
    RET;


MovementPermissionsData:
    //db ['DOWN_MASK'];
    //db ['UP_MASK'];
    //db ['LEFT_MASK'];
    //db ['RIGHT_MASK'];
    //db ['DOWN_MASK | RIGHT_MASK'];
    //db ['UP_MASK | RIGHT_MASK'];
    //db ['DOWN_MASK | LEFT_MASK'];
    //db ['UP_MASK | LEFT_MASK'];


UpDown:
    LD_A_addr(wPlayerStandingMapX);
    LD_D_A;
    LD_A_addr(wPlayerStandingMapY);
    LD_E_A;

    PUSH_DE;
    INC_E;
    CALL(aGetCoordTile);
    LD_addr_A(wTileDown);
    CALL(aGetMovementPermissions_Down);

    POP_DE;
    DEC_E;
    CALL(aGetCoordTile);
    LD_addr_A(wTileUp);
    CALL(aGetMovementPermissions_Up);
    RET;


LeftRight:
    LD_A_addr(wPlayerStandingMapX);
    LD_D_A;
    LD_A_addr(wPlayerStandingMapY);
    LD_E_A;

    PUSH_DE;
    DEC_D;
    CALL(aGetCoordTile);
    LD_addr_A(wTileLeft);
    CALL(aGetMovementPermissions_Left);

    POP_DE;
    INC_D;
    CALL(aGetCoordTile);
    LD_addr_A(wTileRight);
    CALL(aGetMovementPermissions_Right);
    RET;


Down:
    CALL(aGetMovementPermissions_CheckHiNybble);
    RET_NZ ;
    LD_A_addr(wTileDown);
    AND_A(0b111);
    CP_A(COLL_UP_WALL & 0b111);  // COLL_UP_BUOY & %111
    IF_Z goto ok_down;
    CP_A(COLL_UP_RIGHT_WALL & 0b111);  // COLL_UP_RIGHT_BUOY & %111
    IF_Z goto ok_down;
    CP_A(COLL_UP_LEFT_WALL & 0b111);  // COLL_UP_LEFT_BUOY & %111
    RET_NZ ;


ok_down:
    LD_A_addr(wTilePermissions);
    OR_A(FACE_DOWN);
    LD_addr_A(wTilePermissions);
    RET;


Up:
    CALL(aGetMovementPermissions_CheckHiNybble);
    RET_NZ ;
    LD_A_addr(wTileUp);
    AND_A(0b111);
    CP_A(COLL_DOWN_WALL & 0b111);  // COLL_DOWN_BUOY & %111
    IF_Z goto ok_up;
    CP_A(COLL_DOWN_RIGHT_WALL & 0b111);  // COLL_DOWN_RIGHT_BUOY & %111
    IF_Z goto ok_up;
    CP_A(COLL_DOWN_LEFT_WALL & 0b111);  // COLL_DOWN_LEFT_BUOY & %111
    RET_NZ ;


ok_up:
    LD_A_addr(wTilePermissions);
    OR_A(FACE_UP);
    LD_addr_A(wTilePermissions);
    RET;


Right:
    CALL(aGetMovementPermissions_CheckHiNybble);
    RET_NZ ;
    LD_A_addr(wTileRight);
    AND_A(0b111);
    CP_A(COLL_LEFT_WALL & 0b111);  // COLL_LEFT_BUOY & %111
    IF_Z goto ok_right;
    CP_A(COLL_DOWN_LEFT_WALL & 0b111);  // COLL_DOWN_LEFT_BUOY & %111
    IF_Z goto ok_right;
    CP_A(COLL_UP_LEFT_WALL & 0b111);  // COLL_UP_LEFT_BUOY & %111
    RET_NZ ;


ok_right:
    LD_A_addr(wTilePermissions);
    OR_A(FACE_RIGHT);
    LD_addr_A(wTilePermissions);
    RET;


Left:
    CALL(aGetMovementPermissions_CheckHiNybble);
    RET_NZ ;
    LD_A_addr(wTileLeft);
    AND_A(0b111);
    CP_A(COLL_RIGHT_WALL & 0b111);  // COLL_RIGHT_BUOY & %111
    IF_Z goto ok_left;
    CP_A(COLL_DOWN_RIGHT_WALL & 0b111);  // COLL_DOWN_RIGHT_BUOY & %111
    IF_Z goto ok_left;
    CP_A(COLL_UP_RIGHT_WALL & 0b111);  // COLL_UP_RIGHT_BUOY & %111
    RET_NZ ;


ok_left:
    LD_A_addr(wTilePermissions);
    OR_A(FACE_LEFT);
    LD_addr_A(wTilePermissions);
    RET;


CheckHiNybble:
    AND_A(0xf0);
    CP_A(HI_NYBBLE_SIDE_WALLS);
    RET_Z ;
    CP_A(HI_NYBBLE_SIDE_BUOYS);
    RET;

}

void GetFacingTileCoord(void){
//  Return map coordinates in (d, e) and tile id in a
//  of the tile the player is facing.

    LD_A_addr(wPlayerDirection);
    AND_A(0b1100);
    SRL_A;
    SRL_A;
    LD_L_A;
    LD_H(0);
    ADD_HL_HL;
    ADD_HL_HL;
    LD_DE(mGetFacingTileCoord_Directions);
    ADD_HL_DE;

    LD_D_hl;
    INC_HL;
    LD_E_hl;
    INC_HL;

    LD_A_hli;
    LD_H_hl;
    LD_L_A;

    LD_A_addr(wPlayerStandingMapX);
    ADD_A_D;
    LD_D_A;
    LD_A_addr(wPlayerStandingMapY);
    ADD_A_E;
    LD_E_A;
    LD_A_hl;
    RET;


Directions:
//   x,  y
    //db ['0', '1'];
    //dw ['wTileDown'];
    //db ['0', '-1'];
    //dw ['wTileUp'];
    //db ['-1', '0'];
    //dw ['wTileLeft'];
    //db ['1', '0'];
    //dw ['wTileRight'];

    return GetCoordTile();
}

void GetCoordTile(void){
//  Get the collision byte for tile d, e
    CALL(aGetBlockLocation);
    LD_A_hl;
    AND_A_A;
    IF_Z goto nope;
    LD_L_A;
    LD_H(0);
    ADD_HL_HL;
    ADD_HL_HL;
    LD_A_addr(wTilesetCollisionAddress);
    LD_C_A;
    LD_A_addr(wTilesetCollisionAddress + 1);
    LD_B_A;
    ADD_HL_BC;
    RR_D;
    IF_NC goto nocarry;
    INC_HL;


nocarry:
    RR_E;
    IF_NC goto nocarry2;
    INC_HL;
    INC_HL;


nocarry2:
    LD_A_addr(wTilesetCollisionBank);
    CALL(aGetFarByte);
    RET;


nope:
    LD_A(-1);
    RET;

}

void GetBlockLocation(void){
    LD_A_addr(wMapWidth);
    ADD_A(6);
    LD_C_A;
    LD_B(0);
    LD_HL(wOverworldMapBlocks + 1);
    ADD_HL_BC;
    LD_A_E;
    SRL_A;
    IF_Z goto nope;
    AND_A_A;

loop:
    SRL_A;
    IF_NC goto ok;
    ADD_HL_BC;


ok:
    SLA_C;
    RL_B;
    AND_A_A;
    IF_NZ goto loop;


nope:
    LD_C_D;
    SRL_C;
    LD_B(0);
    ADD_HL_BC;
    RET;

}

void CheckFacingBGEvent(void){
    CALL(aGetFacingTileCoord);
//  Load facing into b.
    LD_B_A;
//  Convert the coordinates at de to within-boundaries coordinates.
    LD_A_D;
    SUB_A(4);
    LD_D_A;
    LD_A_E;
    SUB_A(4);
    LD_E_A;
//  If there are no BG events, we don't need to be here.
    LD_A_addr(wCurMapBGEventCount);
    AND_A_A;
    RET_Z ;

    LD_C_A;
    LDH_A_addr(hROMBank);
    PUSH_AF;
    CALL(aSwitchToMapScriptsBank);
    CALL(aCheckIfFacingTileCoordIsBGEvent);
    POP_HL;
    LD_A_H;
    RST(aBankswitch);
    RET;

}

void CheckIfFacingTileCoordIsBGEvent(void){
//  Checks to see if you are facing a BG event.  If so, copies it into wCurBGEvent and sets carry.
    LD_HL(wCurMapBGEventsPointer);
    LD_A_hli;
    LD_H_hl;
    LD_L_A;

loop:
    PUSH_HL;
    LD_A_hli;
    CP_A_E;
    IF_NZ goto next;
    LD_A_hli;
    CP_A_D;
    IF_NZ goto next;
    goto copysign;


next:
    POP_HL;
    LD_A(BG_EVENT_SIZE);
    ADD_A_L;
    LD_L_A;
    IF_NC goto nocarry;
    INC_H;


nocarry:
    DEC_C;
    IF_NZ goto loop;
    XOR_A_A;
    RET;


copysign:
    POP_HL;
    LD_DE(wCurBGEvent);
    LD_BC(BG_EVENT_SIZE);
    CALL(aCopyBytes);
    SCF;
    RET;

}

void CheckCurrentMapCoordEvents(void){
//  If there are no coord events, we don't need to be here.
    LD_A_addr(wCurMapCoordEventCount);
    AND_A_A;
    RET_Z ;
//  Copy the coord event count into c.
    LD_C_A;
    LDH_A_addr(hROMBank);
    PUSH_AF;
    CALL(aSwitchToMapScriptsBank);
    CALL(aCheckCurrentMapCoordEvents_CoordEventCheck);
    POP_HL;
    LD_A_H;
    RST(aBankswitch);
    RET;


CoordEventCheck:
//  Checks to see if you are standing on a coord event.  If yes, copies the event to wCurCoordEvent and sets carry.
    LD_HL(wCurMapCoordEventsPointer);
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
//  Load the active scene ID into b
    CALL(aCheckScenes);
    LD_B_A;
//  Load your current coordinates into de.  This will be used to check if your position is in the coord event table for the current map.
    LD_A_addr(wPlayerStandingMapX);
    SUB_A(4);
    LD_D_A;
    LD_A_addr(wPlayerStandingMapY);
    SUB_A(4);
    LD_E_A;


loop:
    PUSH_HL;
    LD_A_hli;
    CP_A_B;
    IF_Z goto got_id;
    CP_A(-1);
    IF_NZ goto next;


got_id:
    LD_A_hli;
    CP_A_E;
    IF_NZ goto next;
    LD_A_hli;
    CP_A_D;
    IF_NZ goto next;
    goto copy_coord_event;


next:
    POP_HL;
    LD_A(COORD_EVENT_SIZE);
    ADD_A_L;
    LD_L_A;
    IF_NC goto nocarry;
    INC_H;


nocarry:
    DEC_C;
    IF_NZ goto loop;
    XOR_A_A;
    RET;


copy_coord_event:
    POP_HL;
    LD_DE(wCurCoordEvent);
    LD_BC(COORD_EVENT_SIZE);
    CALL(aCopyBytes);
    SCF;
    RET;

}

void FadeToMenu(void){
    XOR_A_A;
    LDH_addr_A(hBGMapMode);
    CALL(aLoadStandardMenuHeader);
    FARCALL(aFadeOutPalettes);
    CALL(aClearSprites);
    CALL(aDisableSpriteUpdates);
    RET;

}

void CloseSubmenu(void){
    CALL(aClearBGPalettes);
    CALL(aReloadTilesetAndPalettes);
    CALL(aUpdateSprites);
    CALL(aCall_ExitMenu);
    CALL(aGSReloadPalettes);
    JR(mFinishExitMenu);

}

void ExitAllMenus(void){
    CALL(aClearBGPalettes);
    CALL(aCall_ExitMenu);
    CALL(aReloadTilesetAndPalettes);
    CALL(aUpdateSprites);
    CALL(aGSReloadPalettes);
    return FinishExitMenu();
}

void FinishExitMenu(void){
    LD_B(SCGB_MAPPALS);
    CALL(aGetSGBLayout);
    FARCALL(aLoadOW_BGPal7);
    CALL(aWaitBGMap2);
    FARCALL(aFadeInPalettes);
    CALL(aEnableSpriteUpdates);
    RET;

}

void ReturnToMapWithSpeechTextbox(void){
    PUSH_AF;
    LD_A(0x1);
    LD_addr_A(wSpriteUpdatesEnabled);
    CALL(aClearBGPalettes);
    CALL(aClearSprites);
    CALL(aReloadTilesetAndPalettes);
    hlcoord(0, 12, wTilemap);
    LD_BC((4 << 8) | 18);
    CALL(aTextbox);
    LD_HL(wVramState);
    SET_hl(0);
    CALL(aUpdateSprites);
    CALL(aWaitBGMap2);
    LD_B(SCGB_MAPPALS);
    CALL(aGetSGBLayout);
    FARCALL(aLoadOW_BGPal7);
    CALL(aUpdateTimePals);
    CALL(aDelayFrame);
    LD_A(0x1);
    LDH_addr_A(hMapAnims);
    POP_AF;
    RET;

}

void ReloadTilesetAndPalettes(void){
    CALL(aDisableLCD);
    CALL(aClearSprites);
    FARCALL(aRefreshSprites);
    CALL(aLoadStandardFont);
    CALL(aLoadFontsExtra);
    LDH_A_addr(hROMBank);
    PUSH_AF;
    LD_A_addr(wMapGroup);
    LD_B_A;
    LD_A_addr(wMapNumber);
    LD_C_A;
    CALL(aSwitchToAnyMapAttributesBank);
    FARCALL(aUpdateTimeOfDayPal);
    CALL(aOverworldTextModeSwitch);
    CALL(aLoadTilesetGFX);
    LD_A(9);
    CALL(aSkipMusic);
    POP_AF;
    RST(aBankswitch);

    CALL(aEnableLCD);
    RET;

}

void GetMapPointer(void){
    LD_A_addr(wMapGroup);
    LD_B_A;
    LD_A_addr(wMapNumber);
    LD_C_A;
    return GetAnyMapPointer();
}

void GetAnyMapPointer(void){
//  Prior to calling this function, you must have switched banks so that
//  MapGroupPointers is visible.

//  inputs:
//  b = map group, c = map number

//  outputs:
//  hl points to the map within its group
    PUSH_BC;  // save map number for later

// get pointer to map group
    DEC_B;
    LD_C_B;
    LD_B(0);
    LD_HL(mMapGroupPointers);
    ADD_HL_BC;
    ADD_HL_BC;

    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    POP_BC;  // restore map number

// find the cth map within the group
    DEC_C;
    LD_B(0);
    LD_A(MAP_LENGTH);
    CALL(aAddNTimes);
    RET;

}

uint16_t GetMapPointer_Conv(void){
    return GetAnyMapPointer_Conv(gb_read(wMapGroup), gb_read(wMapNumber));
}

uint16_t GetAnyMapPointer_Conv(uint8_t group, uint8_t map){
//  Prior to calling this function, you must have switched banks so that
//  MapGroupPointers is visible.

//  inputs:
//  b = map group, c = map number

//  outputs:
//  hl points to the map within its group
    //PUSH_BC;  // save map number for later

// get pointer to map group

    //DEC_B;
    //LD_C_B;
    //LD_B(0);
    //LD_HL(mMapGroupPointers);
    //ADD_HL_BC;
    //ADD_HL_BC;
    uint16_t hl = mMapGroupPointers + (2 * (group - 1));

    //LD_A_hli;
    //LD_H_hl;
    //LD_L_A;
    //POP_BC;  // restore map number
    uint16_t gptr = gb_read16(hl);

// find the cth map within the group
    //DEC_C;
    //LD_B(0);
    //LD_A(MAP_LENGTH);
    //CALL(aAddNTimes);
    return gptr + ((map - 1) * MAP_LENGTH);
}

void GetMapField(void){
//  Extract data from the current map's group entry.

//  inputs:
//  de = offset of desired data within the map (a MAP_* constant)

//  outputs:
//  bc = data from the current map's field
//  (e.g., de = MAP_TILESET would return a pointer to the tileset id)

    LD_A_addr(wMapGroup);
    LD_B_A;
    LD_A_addr(wMapNumber);
    LD_C_A;
    return GetAnyMapField();
}

uint16_t GetMapField_Conv(uint16_t offset){
//  Extract data from the current map's group entry.

//  inputs:
//  de = offset of desired data within the map (a MAP_* constant)

//  outputs:
//  bc = data from the current map's field
//  (e.g., de = MAP_TILESET would return a pointer to the tileset id)
    return GetAnyMapField_Conv(offset, gb_read(wMapGroup), gb_read(wMapNumber));
}

void GetAnyMapField(void){
// bankswitch
    LDH_A_addr(hROMBank);
    PUSH_AF;
    LD_A(BANK(aMapGroupPointers));
    RST(aBankswitch);

    CALL(aGetAnyMapPointer);
    ADD_HL_DE;
    LD_C_hl;
    INC_HL;
    LD_B_hl;

// bankswitch back
    POP_AF;
    RST(aBankswitch);
    RET;

}

uint16_t GetAnyMapField_Conv(uint16_t offset, uint8_t group, uint8_t map)
{
    bank_push(BANK(aMapGroupPointers));
    uint16_t base = GetAnyMapPointer_Conv(group, map);
    uint16_t data = gb_read16(base + offset);
    bank_pop;
    return data;
}

void SwitchToMapAttributesBank(void){
    LD_A_addr(wMapGroup);
    LD_B_A;
    LD_A_addr(wMapNumber);
    LD_C_A;
    return SwitchToAnyMapAttributesBank();
}

void SwitchToAnyMapAttributesBank(void){
    CALL(aGetAnyMapAttributesBank);
    RST(aBankswitch);
    RET;

}

void GetMapAttributesBank(void){
//  //  unreferenced
    LD_A_addr(wMapGroup);
    LD_B_A;
    LD_A_addr(wMapNumber);
    LD_C_A;
    return GetAnyMapAttributesBank();
}

void GetAnyMapAttributesBank(void){
    PUSH_HL;
    PUSH_DE;
    LD_DE(MAP_MAPATTRIBUTES_BANK);
    CALL(aGetAnyMapField);
    LD_A_C;
    POP_DE;
    POP_HL;
    RET;

}

void CopyMapPartial(void){
//  Copy map data bank, tileset, environment, and map data address
//  from the current map's entry within its group.
    LDH_A_addr(hROMBank);
    PUSH_AF;
    LD_A(BANK(aMapGroupPointers));
    RST(aBankswitch);

    CALL(aGetMapPointer);
    LD_DE(wMapPartial);
    LD_BC(wMapPartialEnd - wMapPartial);
    CALL(aCopyBytes);

    POP_AF;
    RST(aBankswitch);
    RET;

}

//  Copy map data bank, tileset, environment, and map data address
//  from the current map's entry within its group.
void CopyMapPartial_Conv(void){
    bank_push(BANK(aMapGroupPointers));

    CopyBytes_Conv(wMapPartial, GetMapPointer_Conv(), (wMapPartialEnd - wMapPartial));

    bank_pop;
}

void SwitchToMapScriptsBank(void){
    LD_A_addr(wMapScriptsBank);
    RST(aBankswitch);
    RET;

}

void SwitchToMapScriptsBank_Conv(void){
    Bankswitch_Conv(gb_read(wMapScriptsBank));
}

void GetMapScriptsBank(void){
    LD_A_addr(wMapScriptsBank);
    RET;

}

uint8_t GetMapScriptsBank_Conv(void){
    return gb_read(wMapScriptsBank);
}

void GetAnyMapBlocksBank(void){
//  Return the blockdata bank for group b map c.
    PUSH_HL;
    PUSH_DE;
    PUSH_BC;

    PUSH_BC;
    LD_DE(MAP_MAPATTRIBUTES);
    CALL(aGetAnyMapField);
    LD_L_C;
    LD_H_B;
    POP_BC;

    PUSH_HL;
    LD_DE(MAP_MAPATTRIBUTES_BANK);
    CALL(aGetAnyMapField);
    POP_HL;

    LD_DE(MAP_MAPATTRIBUTES);  // blockdata bank
    ADD_HL_DE;
    LD_A_C;
    CALL(aGetFarByte);
    RST(aBankswitch);

    POP_BC;
    POP_DE;
    POP_HL;
    RET;

}

void GetMapAttributesPointer(void){
//  returns the current map's data pointer in hl.
    PUSH_BC;
    PUSH_DE;
    LD_DE(MAP_MAPATTRIBUTES);
    CALL(aGetMapField);
    LD_L_C;
    LD_H_B;
    POP_DE;
    POP_BC;
    RET;

}

void GetMapEnvironment(void){
    PUSH_HL;
    PUSH_DE;
    PUSH_BC;
    LD_DE(MAP_ENVIRONMENT);
    CALL(aGetMapField);
    LD_A_C;
    POP_BC;
    POP_DE;
    POP_HL;
    RET;

}

void Map_DummyFunction(void){
//  //  unreferenced
    RET;

}

void GetAnyMapEnvironment(void){
    PUSH_HL;
    PUSH_DE;
    PUSH_BC;
    LD_DE(MAP_ENVIRONMENT);
    CALL(aGetAnyMapField);
    LD_A_C;
    POP_BC;
    POP_DE;
    POP_HL;
    RET;

}

void GetAnyMapTileset(void){
    LD_DE(MAP_TILESET);
    CALL(aGetAnyMapField);
    LD_A_C;
    RET;

}

uint8_t GetAnyMapTileset_Conv(uint8_t group, uint8_t map){
    return (uint8_t)(GetAnyMapField_Conv(MAP_TILESET, group, map));
}

void GetWorldMapLocation(void){
//  given a map group/id in bc, return its location on the Pokégear map.
    PUSH_HL;
    PUSH_DE;
    PUSH_BC;

    LD_DE(MAP_LOCATION);
    CALL(aGetAnyMapField);
    LD_A_C;

    POP_BC;
    POP_DE;
    POP_HL;
    RET;

}

uint8_t GetWorldMapLocation_Conv(uint8_t group, uint8_t map){
//  given a map group/id in bc, return its location on the Pokégear map.
    uint16_t data = GetAnyMapField_Conv(MAP_LOCATION, group, map);
    return (uint8_t)(data & 0xFF);
}

void GetMapMusic(void){
    PUSH_HL;
    PUSH_BC;
    LD_DE(MAP_MUSIC);
    CALL(aGetMapField);
    LD_A_C;
    CP_A(MUSIC_MAHOGANY_MART);
    IF_Z goto mahoganymart;
    BIT_C(RADIO_TOWER_MUSIC_F);
    IF_NZ goto radiotower;
    FARCALL(aFunction8b342);
    LD_E_C;
    LD_D(0);

done:
    POP_BC;
    POP_HL;
    RET;


radiotower:
    LD_A_addr(wStatusFlags2);
    BIT_A(STATUSFLAGS2_ROCKETS_IN_RADIO_TOWER_F);
    IF_Z goto clearedradiotower;
    LD_DE(MUSIC_ROCKET_OVERTURE);
    goto done;


clearedradiotower:
// the rest of the byte
    LD_A_C;
    AND_A(RADIO_TOWER_MUSIC - 1);
    LD_E_A;
    LD_D(0);
    goto done;


mahoganymart:
    LD_A_addr(wStatusFlags2);
    BIT_A(STATUSFLAGS2_ROCKETS_IN_MAHOGANY_F);
    IF_Z goto clearedmahogany;
    LD_DE(MUSIC_ROCKET_HIDEOUT);
    goto done;


clearedmahogany:
    LD_DE(MUSIC_CHERRYGROVE_CITY);
    goto done;

    return GetMapTimeOfDay();
}

uint16_t GetMapMusic_Conv(void){
    uint16_t music = GetMapField_Conv(MAP_MUSIC);
    if(music == MUSIC_MAHOGANY_MART)
    {
        if(!(gb_read(wStatusFlags2) & (1 << STATUSFLAGS2_ROCKETS_IN_MAHOGANY_F)))
        {
            return MUSIC_CHERRYGROVE_CITY;
        }
        return MUSIC_ROCKET_HIDEOUT;
    }
    if(music & (1 << RADIO_TOWER_MUSIC_F))
    {
        if(!(gb_read(wStatusFlags2) & (1 << STATUSFLAGS2_ROCKETS_IN_RADIO_TOWER_F)))
        {
            return music & (RADIO_TOWER_MUSIC - 1);
        }
        return MUSIC_ROCKET_OVERTURE;
    }
    return music;
}

void GetMapTimeOfDay(void){
    CALL(aGetPhoneServiceTimeOfDayByte);
    AND_A(0xf);
    RET;

}

uint8_t GetMapTimeOfDay_Conv(void){
    return GetPhoneServiceTimeOfDayByte_Conv() & 0xF;
}

void GetMapPhoneService(void){
    CALL(aGetPhoneServiceTimeOfDayByte);
    AND_A(0xf0);
    SWAP_A;
    RET;

}

uint8_t GetMapPhoneService_Conv(void){
    return (GetPhoneServiceTimeOfDayByte_Conv() & 0xF0) >> 4;
}

void GetPhoneServiceTimeOfDayByte(void){
    PUSH_HL;
    PUSH_BC;

    LD_DE(MAP_PALETTE);
    CALL(aGetMapField);
    LD_A_C;

    POP_BC;
    POP_HL;
    RET;

}

uint8_t GetPhoneServiceTimeOfDayByte_Conv(void){
    return (uint8_t)(GetMapField_Conv(MAP_PALETTE) & 0xFF);
}

void GetFishingGroup(void){
    PUSH_DE;
    PUSH_HL;
    PUSH_BC;

    LD_DE(MAP_FISHGROUP);
    CALL(aGetMapField);
    LD_A_C;

    POP_BC;
    POP_HL;
    POP_DE;
    RET;

}

uint8_t GetFishingGroup_Conv(void){
    return (uint8_t)(GetMapField_Conv(MAP_FISHGROUP) & 0xFF);
}

void LoadMapTileset(void){
    PUSH_HL;
    PUSH_BC;

    LD_HL(mTilesets);
    LD_BC(TILESET_LENGTH);
    LD_A_addr(wMapTileset);
    CALL(aAddNTimes);

    LD_DE(wTilesetBank);
    LD_BC(TILESET_LENGTH);

    LD_A(BANK(aTilesets));
    CALL(aFarCopyBytes);

    POP_BC;
    POP_HL;
    RET;

}

void LoadMapTileset_Conv(void){
    uint16_t hl = AddNTimes_Conv(mTilesets, TILESET_LENGTH, gb_read(wMapTileset));
    FarCopyBytes_Conv(wTilesetBank, BANK(aTilesets), hl, TILESET_LENGTH);
}

void DummyEndPredef(void){
//  Unused function at the end of PredefPointers.
    for(int rept = 0; rept < 16; rept++){
    NOP;
    }
    RET;

}
