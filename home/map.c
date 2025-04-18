#include "../constants.h"
#include "map.h"
#include "copy.h"
#include "array.h"
#include "gfx.h"
#include "palettes.h"
#include "text.h"
#include "window.h"
#include "tilemap.h"
#include "map_objects.h"
#include "audio.h"
#include "clear_sprites.h"
#include "sprite_updates.h"
#include "menu.h"
#include "lcd.h"
#include "time_palettes.h"
#include "delay.h"
#include "../engine/overworld/overworld.h"
#include "../engine/overworld/tile_events.h"
#include "../engine/overworld/load_map_part.h"
#include "../engine/overworld/map_setup.h"
#include "../engine/overworld/warp_connection.h"
#include "../engine/tilesets/mapgroup_roofs.h"
#include "../engine/tilesets/timeofday_pals.h"
#include "../engine/gfx/crystal_layouts.h"
#include "../data/maps/maps.h"
#include "../data/maps/scenes.h"
#include "../util/scripting.h"
#include "../data/text/common.h"
#include "../data/tilesets.h"
#include "../data/gb_tilesets.h"
#include "../data/gb_map_pointers.h"
#include "../mobile/mobile_41.h"

const struct MapAttr* gMapAttrPointer;
const uint8_t* gCurMapSceneScriptPointer;

uint8_t gCurMapCoordEventCount;
const struct CoordEvent* gCurMapCoordEventsPointer;
uint8_t gCurMapWarpCount;
const struct WarpEventData* gCurMapWarpsPointer;
uint8_t gCurMapBGEventCount;
const struct BGEvent* gCurMapBGEventsPointer;
uint8_t gCurMapObjectEventCount;
const struct ObjEvent* gCurMapObjectEventsPointer;

uint8_t gCurMapCallbackCount;
const struct MapCallback* gCurMapCallbacksPointer;
uint8_t gCurMapSceneScriptCount;
const Script_fn_t* gCurMapSceneScriptsPointer;

const char* gMapBlocksPath;
asset_s gMapBlocks;
const char* gMapConnectionBlocksPath[4];
asset_s gMapConnectionBlocks[4];
const struct MapScripts* gMapScriptsPointer;
const struct MapEvents* gMapEventsPointer;

struct MapConnectionData gMapConnections[4];

const struct Tileset* gTilesetPointer;
const struct TileAnimFrame* gTilesetAnim;
asset_s gTilesetBlocks;

struct BGEvent gCurBGEvent;

//  Functions dealing with rendering and interacting with maps.

void ClearUnusedMapBuffer(void){
    // LD_HL(wUnusedMapBuffer);
    // LD_BC(wUnusedMapBufferEnd - wUnusedMapBuffer);
    // LD_A(0);
    // CALL(aByteFill);
    ByteFill(wram->wUnusedMapBuffer, sizeof(wram->wUnusedMapBuffer), 0);
    // RET;

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

//  Checks wCurMapSceneScriptPointer.  If it's empty, returns -1 in a.  Otherwise, returns the active scene ID in a.
uint8_t CheckScenes_Conv(void) {
    // PUSH_HL;
    // LD_HL(wCurMapSceneScriptPointer);
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // OR_A_H;
    // LD_A_hl;
    // IF_NZ goto scene_exists;
    if(gCurMapSceneScriptPointer != NULL) {
        return *gCurMapSceneScriptPointer;
    }
    return 0xff;
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

//  Grabs the wram map scene script pointer for the current map and loads it into wCurMapSceneScriptPointer.
//  If there is no scene, both bytes of wCurMapSceneScriptPointer are wiped clean.
//  Copy the current map group and number into bc.  This is needed for GetMapSceneID.
uint16_t GetCurrentMapSceneID_Conv(void){
    // LD_A_addr(wMapGroup);
    // LD_B_A;
    // LD_A_addr(wMapNumber);
    // LD_C_A;
//  Blank out wCurMapSceneScriptPointer
    // XOR_A_A;
    // LD_addr_A(wCurMapSceneScriptPointer);
    // LD_addr_A(wCurMapSceneScriptPointer + 1);
    gCurMapSceneScriptPointer = NULL;
    // CALL(aGetMapSceneID);
    // RET_C ;  // The map is not in the scene script table
    uint8_t* id = GetMapSceneID_Conv2(wram->wMapGroup, wram->wMapNumber);
    if(id == NULL)
        return (wram->wMapGroup << 8) | wram->wMapNumber;
//  Load the scene script pointer from de into wCurMapSceneScriptPointer
    // LD_A_E;
    // LD_addr_A(wCurMapSceneScriptPointer);
    // LD_A_D;
    // LD_addr_A(wCurMapSceneScriptPointer + 1);
    gCurMapSceneScriptPointer = id;
    // XOR_A_A;
    // RET;
    return (wram->wMapGroup << 8) | wram->wMapNumber;
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

//  Searches the scene_var table for the map group and number loaded in bc, and returns the wram pointer in de.
//  If the map is not in the scene_var table, returns null.
uint8_t* GetMapSceneID_Conv2(uint8_t group, uint8_t map){
    // PUSH_BC;
    // LDH_A_addr(hROMBank);
    // PUSH_AF;
    // LD_A(BANK(aMapScenes));
    // RST(aBankswitch);

    // LD_HL(mMapScenes);
    const struct SceneVar* hl = MapScenes;

    while(1) {
    // loop:
        // PUSH_HL;
        // LD_A_hli;  // map group, or terminator
        uint8_t a = hl->group;
        // CP_A(-1);
        // IF_Z goto end;  // the current map is not in the scene_var table
        if(a == 0xff)
            return NULL;
        // CP_A_B;
        // IF_NZ goto next;  // map group did not match
        // LD_A_hli;  // map number
        // CP_A_C;
        // IF_NZ goto next;  // map number did not match
        if(a == group && hl->map == map)
            break;
        // goto found;  // we found our map


    // next:
        // POP_HL;
        // LD_DE(4);  // scene_var size
        // ADD_HL_DE;
        hl++;
        // goto loop;
    }


// end:
    // SCF;
    // goto done;


// found:
    // LD_E_hl;
    // INC_HL;
    // LD_D_hl;


// done:
    // POP_HL;
    // POP_BC;
    // LD_A_B;
    // RST(aBankswitch);

    // POP_BC;
    // RET;
    return hl->var;
}

void OverworldTextModeSwitch(void){
    CALL(aLoadMapPart);
    CALL(aSwapTextboxPalettes);
    RET;

}

void OverworldTextModeSwitch_Conv(void){
    // CALL(aLoadMapPart);
    LoadMapPart_Conv();
    // CALL(aSwapTextboxPalettes);
    SwapTextboxPalettes();
    // RET;
}

void LoadMapPart(void){
    return LoadMapPart_Conv();
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

void LoadMapPart_Conv(void){
    // LDH_A_addr(hROMBank);
    // PUSH_AF;

    // LD_A_addr(wTilesetBlocksBank);
    // RST(aBankswitch);
    // bank_push(wram->wTilesetBlocksBank);
    // CALL(aLoadMetatiles);
    LoadMetatiles_Conv();

    // LD_A(0x60);
    // hlcoord(0, 0, wTilemap);
    // LD_BC(SCREEN_WIDTH * SCREEN_HEIGHT);
    // CALL(aByteFill);
    ByteFill(coord(0, 0, wram->wTilemap), SCREEN_WIDTH * SCREEN_HEIGHT, 0x60);

    // LD_A(BANK(av_LoadMapPart));
    // RST(aBankswitch);
    // CALL(av_LoadMapPart);
    v_LoadMapPart_Conv();

    // POP_AF;
    // RST(aBankswitch);
    // RET;
    // bank_pop;
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

void LoadMetatiles_Conv(void){
// de <- wOverworldMapAnchor
    // LD_A_addr(wOverworldMapAnchor);
    // LD_E_A;
    // LD_A_addr(wOverworldMapAnchor + 1);
    // LD_D_A;
    uint8_t* de = AbsGBBankAddrToRAMAddr(MBANK(awOverworldMapBlocks), wram->wOverworldMapAnchor);
    if(!de) {
        de = wram->wSurroundingTiles;
    }
    // LD_HL(wSurroundingTiles);
    uint8_t* hl = wram->wSurroundingTiles;
    // LD_B(SCREEN_META_HEIGHT);
    uint8_t b = SCREEN_META_HEIGHT;

    do {
    // row:
        // PUSH_DE;
        uint8_t* de2 = de;
        // PUSH_HL;
        uint8_t* hl2 = hl;
        // LD_C(SCREEN_META_WIDTH);
        uint8_t c = SCREEN_META_WIDTH;

        do {
        // col:
            // PUSH_DE;
            uint8_t* de3 = de;
            // PUSH_HL;
            uint8_t* hl3 = hl;
        // Load the current map block.
        // If the current map block is a border block, load the border block.
            // LD_A_de;
            // AND_A_A;
            // IF_NZ goto ok;
            uint8_t a = *de;
            if(a == 0) {
                // LD_A_addr(wMapBorderBlock);
                a = wram->wMapBorderBlock;
            }

        // ok:
        // Load the current wSurroundingTiles address into de.
            // LD_E_L;
            // LD_D_H;
            de = hl;
        // Set hl to the address of the current metatile data ([wTilesetBlocksAddress] + (a) tiles).
        // This is buggy// it wraps around past 128 blocks.
        // To fix, uncomment the line below.
            // ADD_A_A;  // Comment or delete this line to fix the above bug.
            // LD_L_A;
            // LD_H(0);
        // add hl, hl
            // ADD_HL_HL;
            // ADD_HL_HL;
            // ADD_HL_HL;
            // LD_A_addr(wTilesetBlocksAddress);
            // ADD_A_L;
            // LD_L_A;
            // LD_A_addr(wTilesetBlocksAddress + 1);
            // ADC_A_H;
            // LD_H_A;
            hl = ((uint8_t*)gTilesetBlocks.ptr) + (a << 4);
            if(gTilesetBlocks.ptr == 0)
                hl = de;
            // hl = AbsGBROMBankAddrToRAMAddr(wram->wTilesetBlocksBank, wram->wTilesetBlocksAddress + (a << 4));

        // copy the 4x4 metatile
            for(int rept = 0; rept < METATILE_WIDTH - 1; rept++){
                for(int rept2 = 0; rept2 < METATILE_WIDTH; rept2++){
                    // LD_A_hli;
                    // LD_de_A;
                    // INC_DE;
                    *(de++) = *(hl++);
                }
                // LD_A_E;
                // ADD_A(SURROUNDING_WIDTH - METATILE_WIDTH);
                // LD_E_A;
                // IF_NC goto next;
                // INC_D;
                de += (SURROUNDING_WIDTH - METATILE_WIDTH);
            }
        // next:
            for(int rept = 0; rept < METATILE_WIDTH; rept++){
                // LD_A_hli;
                // LD_de_A;
                // INC_DE;
                *(de++) = *(hl++);
            }
        // Next metatile
            // POP_HL;
            // LD_DE(METATILE_WIDTH);
            // ADD_HL_DE;
            hl = hl3 + METATILE_WIDTH;
            // POP_DE;
            // INC_DE;
            de = de3 + 1;
            // DEC_C;
            // JP_NZ (mLoadMetatiles_col);
        } while(--c != 0);
    // Next metarow
        // POP_HL;
        // LD_DE(SURROUNDING_WIDTH * METATILE_WIDTH);
        // ADD_HL_DE;
        hl = hl2 + SURROUNDING_WIDTH * METATILE_WIDTH;
        // POP_DE;
        // LD_A_addr(wMapWidth);
        // ADD_A(MAP_CONNECTION_PADDING_WIDTH * 2);
        // ADD_A_E;
        // LD_E_A;
        // IF_NC goto ok2;
        // INC_D;
        de = de2 + wram->wMapWidth + (MAP_CONNECTION_PADDING_WIDTH * 2);

    // ok2:
        // DEC_B;
        // JP_NZ (mLoadMetatiles_row);
    } while(--b != 0);
    // RET;

}

void ReturnToMapFromSubmenu(void){
    // LD_A(MAPSETUP_SUBMENU);
    // LDH_addr_A(hMapEntryMethod);
    hram->hMapEntryMethod = MAPSETUP_SUBMENU;
    // FARCALL(aRunMapSetupScript);
    RunMapSetupScript();
    // XOR_A_A;
    // LDH_addr_A(hMapEntryMethod);
    hram->hMapEntryMethod = 0;
    // RET;
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

bool CheckWarpTile_Conv(void){
    // CALL(aGetDestinationWarpNumber);
    // RET_NC ;
    u8_flag_s res = GetDestinationWarpNumber_Conv();
    if(!res.flag)
        return false;

    // PUSH_BC;
    // FARCALL(aCheckDirectionalWarp);
    // POP_BC;
    // RET_NC ;
    if(CheckDirectionalWarp_Conv())
        return false;

    // CALL(aCopyWarpData);
    CopyWarpData_Conv(res.a);
    // SCF;
    // RET;
    return true;
}

void WarpCheck(void){
    CALL(aGetDestinationWarpNumber);
    RET_NC ;
    CALL(aCopyWarpData);
    RET;

}

bool WarpCheck_Conv(void){
    // CALL(aGetDestinationWarpNumber);
    // RET_NC ;
    u8_flag_s res = GetDestinationWarpNumber_Conv();
    if(!res.flag)
        return false;
    // CALL(aCopyWarpData);
    // RET;
    CopyWarpData_Conv(res.a);
    return true;
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

static_assert(sizeof(struct WarpEventData) == WARP_EVENT_SIZE, "");

static u8_flag_s GetDestinationWarpNumber_Function(void) {
    // LD_A_addr(wPlayerStandingMapY);
    // SUB_A(4);
    // LD_E_A;
    uint8_t e = wram->wPlayerStruct.nextMapY - 4;
    // LD_A_addr(wPlayerStandingMapX);
    // SUB_A(4);
    // LD_D_A;
    uint8_t d = wram->wPlayerStruct.nextMapX - 4;
    // LD_A_addr(wCurMapWarpCount);
    // AND_A_A;
    // RET_Z ;
    if(wram->wCurMapWarpCount == 0)
        return u8_flag(0xff, false);

    // LD_C_A;
    uint8_t c = wram->wCurMapWarpCount;
    // LD_HL(wCurMapWarpsPointer);
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
#if CONVERTED_OVERWORLD_LOOP
    const struct WarpEventData* hl = gCurMapWarpsPointer;
#else
    const struct WarpEventData* hl = GBToRAMAddr(wram->wCurMapWarpsPointer);
#endif

    do {
    // loop:
        // PUSH_HL;
        // LD_A_hli;
        // CP_A_E;
        // IF_NZ goto next;
        // LD_A_hli;
        // CP_A_D;
        // IF_NZ goto next;
        // goto found_warp;
        if(hl->y == e && hl->x == d) {
        // found_warp:
            // POP_HL;
            // CALL(aGetDestinationWarpNumber_IncreaseHLTwice);
            // RET_NC ;  // never encountered

            // LD_A_addr(wCurMapWarpCount);
            // INC_A;
            // SUB_A_C;
            // LD_C_A;
            uint8_t a = (wram->wCurMapWarpCount + 1) - c;
            // SCF;
            // RET;
            return u8_flag(a, true);


        // IncreaseHLTwice:
            // INC_HL;
            // INC_HL;
            // SCF;
            // RET;
        }


    // next:
        // POP_HL;
        // LD_A(WARP_EVENT_SIZE);
        // ADD_A_L;
        // LD_L_A;
        // IF_NC goto okay;
        // INC_H;


    // okay:
        // DEC_C;
        // IF_NZ goto loop;
    } while(hl++, --c != 0);
    // XOR_A_A;
    // RET;
    return u8_flag(0xff, false);
}

u8_flag_s GetDestinationWarpNumber_Conv(void){
    // FARCALL(aCheckWarpCollision);
    // RET_NC ;
    if(!CheckWarpCollision_Conv())
        return u8_flag(0xff, false);

    // LDH_A_addr(hROMBank);
    // PUSH_AF;
    uint8_t bank = hram->hROMBank;

    // CALL(aSwitchToMapScriptsBank);
    SwitchToMapScriptsBank_Conv();
    // CALL(aGetDestinationWarpNumber_GetDestinationWarpNumber);
    u8_flag_s res = GetDestinationWarpNumber_Function();

    // POP_DE;
    // LD_A_D;
    // RST(aBankswitch);
    Bankswitch(bank);
    // RET;
    return res;
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

static void CopyWarpData_Function(uint8_t c) {
    // PUSH_BC;
    // LD_HL(wCurMapWarpsPointer);
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
#if CONVERTED_OVERWORLD_LOOP
    const struct WarpEventData* hl = gCurMapWarpsPointer;
#else
    const struct WarpEventData* hl = GBToRAMAddr(wram->wCurMapWarpsPointer);
#endif
    // LD_A_C;
    // DEC_A;
    // LD_BC(WARP_EVENT_SIZE);
    // CALL(aAddNTimes);
    hl += c - 1;
    // LD_BC(2);  // warp number
    // ADD_HL_BC;
    // LD_A_hli;
    uint8_t a = hl->warpNumber;
    // CP_A(-1);
    // IF_NZ goto skip;
    if(a == 0xff) {
        // LD_HL(wBackupWarpNumber);
        // LD_A_hli;
        // POP_BC;
        // LD_addr_A(wNextWarp);
        wram->wNextWarp = wram->wBackupWarpNumber;
        // LD_A_hli;
        // LD_addr_A(wNextMapGroup);
        wram->wNextMapGroup = wram->wBackupMapGroup;
        // LD_A_hli;
        // LD_addr_A(wNextMapNumber);
        wram->wNextMapNumber = wram->wBackupMapNumber;
    }
    else {
    // skip:
        // POP_BC;
        // LD_addr_A(wNextWarp);
        wram->wNextWarp = a;
        // LD_A_hli;
        // LD_addr_A(wNextMapGroup);
        wram->wNextMapGroup = hl->mapGroup;
        // LD_A_hli;
        // LD_addr_A(wNextMapNumber);
        wram->wNextMapNumber = hl->mapNumber;
    }

    // LD_A_C;
    // LD_addr_A(wPrevWarp);
    wram->wPrevWarp = c;
    // LD_A_addr(wMapGroup);
    // LD_addr_A(wPrevMapGroup);
    wram->wPrevMapGroup = wram->wMapGroup;
    // LD_A_addr(wMapNumber);
    // LD_addr_A(wPrevMapNumber);
    wram->wPrevMapNumber = wram->wMapNumber;
    // SCF;
    // RET;
}

void CopyWarpData_Conv(uint8_t c){
    // LDH_A_addr(hROMBank);
    // PUSH_AF;
    uint8_t bank = hram->hROMBank;

    // CALL(aSwitchToMapScriptsBank);
    SwitchToMapScriptsBank_Conv();
    // CALL(aCopyWarpData_CopyWarpData);
    CopyWarpData_Function(c);

    // POP_AF;
    // RST(aBankswitch);
    Bankswitch(bank);
    // SCF;
    // RET;
}

void CheckOutdoorMap(void){
    CP_A(ROUTE);
    RET_Z ;
    CP_A(TOWN);
    RET;

}

bool CheckOutdoorMap_Conv(uint8_t a){
    // CP_A(ROUTE);
    // RET_Z ;
    // CP_A(TOWN);
    // RET;
    return (a == ROUTE || a == TOWN);
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

bool CheckIndoorMap_Conv(uint8_t a){
    // CP_A(INDOOR);
    // RET_Z ;
    // CP_A(CAVE);
    // RET_Z ;
    // CP_A(DUNGEON);
    // RET_Z ;
    // CP_A(GATE);
    // RET;
    return (a == INDOOR || a == CAVE || a == DUNGEON || a == GATE);
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
    LoadMapAttributes_Conv();
    RET;
    CALL(aCopyMapPartialAndAttributes);
    CALL(aSwitchToMapScriptsBank);
    CALL(aReadMapScripts);
    XOR_A_A;  // do not skip object events
    CALL(aReadMapEvents);
    RET;

}

void LoadMapAttributes_Conv(void){
    // CALL(aCopyMapPartialAndAttributes);
    CopyMapPartialAndAttributes_Conv();
    // CALL(aSwitchToMapScriptsBank);
    // CALL(aReadMapScripts);
    ReadMapScripts_Conv();
    // XOR_A_A;  // do not skip object events
    // CALL(aReadMapEvents);
    ReadMapEvents_Conv(false);
    // RET;
}

void LoadMapAttributes_SkipObjects(void){
    LoadMapAttributes_SkipObjects_Conv();
    RET;
    CALL(aCopyMapPartialAndAttributes);
    CALL(aSwitchToMapScriptsBank);
    CALL(aReadMapScripts);
    LD_A(TRUE);  // skip object events
    CALL(aReadMapEvents);
    RET;

}

void LoadMapAttributes_SkipObjects_Conv(void){
    // CALL(aCopyMapPartialAndAttributes);
    CopyMapPartialAndAttributes_Conv();
    // CALL(aSwitchToMapScriptsBank);
    // CALL(aReadMapScripts);
    ReadMapScripts_Conv();
    // LD_A(TRUE);  // skip object events
    // CALL(aReadMapEvents);
    ReadMapEvents_Conv(true);
    // RET;
}

void CopyMapPartialAndAttributes(void){
    CALL(aCopyMapPartial);
    CALL(aSwitchToMapAttributesBank);
    CALL(aGetMapAttributesPointer);
    CALL(aCopyMapAttributes);
    CALL(aGetMapConnections);
    RET;

}

void CopyMapPartialAndAttributes_Conv(void){
    // CALL(aCopyMapPartial);
    CopyMapPartial_Conv2();
    // CALL(aSwitchToMapAttributesBank);
    // CALL(aGetMapAttributesPointer);
    const struct MapAttr* attr = GetMapAttributesPointer_Conv2();
    // CALL(aCopyMapAttributes);
    CopyMapAttributes_Conv(attr);
    // CALL(aGetMapConnections);
    GetMapConnections_Conv(attr);
    // RET;
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

void ReadMapEvents_Conv(bool skipObjectEvents){
    // PUSH_AF;
    // LD_HL(wMapEventsPointer);
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // INC_HL;
    // INC_HL;
    const struct MapEvents* events = gMapEventsPointer;
    // CALL(aReadWarps);
    ReadWarps_Conv(events);
    // CALL(aReadCoordEvents);
    ReadCoordEvents_Conv(events);
    // CALL(aReadBGEvents);
    ReadBGEvents_Conv(events);

    // POP_AF;
    // AND_A_A;  // skip object events?
    // RET_NZ ;
    if(!skipObjectEvents) {
        // CALL(aReadObjectEvents);
        ReadObjectEvents_Conv(events);
    }
    // RET;
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

void ReadMapScripts_Conv(void){
    // LD_HL(wMapScriptsPointer);
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // CALL(aReadMapSceneScripts);
    ReadMapSceneScripts_Conv(gMapScriptsPointer);
    // CALL(aReadMapCallbacks);
    ReadMapCallbacks_Conv(gMapScriptsPointer);
    // RET;
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

void CopyMapAttributes_Conv(const struct MapAttr* attr){
    // LD_DE(wMapAttributes);
    // LD_C(wMapAttributesEnd - wMapAttributes);
    wram->wMapBorderBlock = attr->borderBlock;
    // wMapBorderBlock:: db
    // ; width/height are in blocks (2x2 walkable tiles, 4x4 graphics tiles)
    wram->wMapHeight = attr->height;
    // wMapHeight:: db
    wram->wMapWidth = attr->width;
    // wMapWidth:: db
    // wMapBlocksBank:: db
    // wram->wMapBlocksBank = *(uint8_t*)AbsGBROMBankAddrToRAMAddr(wram->wMapAttributesBank, wram->wMapAttributesPointer + 3);
    uint32_t blocks_ptr = GetGBMapBlocksPointer(wram->wMapGroup, wram->wMapNumber);
    wram->wMapBlocksBank = BANK(blocks_ptr);
    // wMapBlocksPointer:: dw
    // wram->wMapBlocksPointer = *(uint16_t*)AbsGBROMBankAddrToRAMAddr(wram->wMapAttributesBank, wram->wMapAttributesPointer + 4);
    wram->wMapBlocksPointer = (blocks_ptr < 0x4000)? blocks_ptr: (blocks_ptr & 0x3fff) | 0x4000;
    gMapBlocksPath = attr->blocksPath;
    if(gMapBlocks.ptr != NULL) {
        FreeAsset(gMapBlocks);
    }
    gMapBlocks = LoadAsset(gMapBlocksPath);
    // wMapScriptsBank:: db
    uint32_t scripts_ptr = GetGBMapScriptsPointer(wram->wMapGroup, wram->wMapNumber);
    // wram->wMapScriptsBank = *(uint8_t*)AbsGBROMBankAddrToRAMAddr(wram->wMapAttributesBank, wram->wMapAttributesPointer + 6);
    wram->wMapScriptsBank = BANK(scripts_ptr);
    printf("scripts_ptr=%08x bank=%d\n", scripts_ptr, wram->wMapScriptsBank);
    // wMapScriptsPointer:: dw
    gMapScriptsPointer = attr->scripts;
    // wram->wMapScriptsPointer = *(uint16_t*)AbsGBROMBankAddrToRAMAddr(wram->wMapAttributesBank, wram->wMapAttributesPointer + 7);
    wram->wMapScriptsPointer = (scripts_ptr < 0x4000)? scripts_ptr: (scripts_ptr & 0x3fff) | 0x4000;
    // wMapEventsPointer:: dw
    uint32_t events_ptr = GetGBMapEventsPointer(wram->wMapGroup, wram->wMapNumber);
    gMapEventsPointer = attr->events;
    // wram->wMapEventsPointer = *(uint16_t*)AbsGBROMBankAddrToRAMAddr(wram->wMapAttributesBank, wram->wMapAttributesPointer + 9);
    wram->wMapEventsPointer = (events_ptr < 0x4000)? events_ptr: (events_ptr & 0x3fff) | 0x4000;
    gCurMapObjectEventCount = attr->events->obj_event_count;
    gCurMapObjectEventsPointer = attr->events->obj_events;
    gCurMapBGEventCount = attr->events->bg_event_count;
    gCurMapBGEventsPointer = attr->events->bg_events;
    // ; bit set
    // wMapConnections:: db
    uint8_t connections = 0;
    if(attr->connections[NORTH_F]) bit_set(connections, NORTH_F);
    if(attr->connections[SOUTH_F]) bit_set(connections, SOUTH_F);
    if(attr->connections[WEST_F])  bit_set(connections, WEST_F);
    if(attr->connections[EAST_F])  bit_set(connections, EAST_F);
    wram->wMapConnections = connections;
    printf("connections=%c%c%c%c\n",
        (connections & NORTH)? 'N': ' ',
        (connections & SOUTH)? 'S': ' ',
        (connections & WEST)? 'W': ' ',
        (connections & EAST)? 'E': ' ');

// loop:
    // LD_A_hli;
    // LD_de_A;
    // INC_DE;
    // DEC_C;
    // IF_NZ goto loop;
    // RET;

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

static void CopyGBMapConnection(struct MapConnection* dest, const struct MapConnectionData* src, uint16_t blocksPtr) {
    dest->connectedMapGroup = src->connectedMapGroup;
    dest->connectedMapNumber = src->connectedMapNumber;
    dest->connectedMapWidth = src->connectedMapWidth;
    dest->connectionStripLength = src->connectionStripLength;
    dest->connectionStripLocation = wOverworldMapBlocks + (src->connectionStripLocation - wram->wOverworldMapBlocks);
    dest->connectionStripPointer = blocksPtr + src->connectionStripOffset;
    dest->connectionStripXOffset = src->connectionStripXOffset;
    dest->connectionStripYOffset = src->connectionStripYOffset;
    dest->connectionWindow = wOverworldMapBlocks + (src->connectionWindow - wram->wOverworldMapBlocks);
}

void GetMapConnections_Conv(const struct MapAttr* attr){
    // LD_A(0xff);
    // LD_addr_A(wNorthConnectedMapGroup);
    // LD_addr_A(wSouthConnectedMapGroup);
    // LD_addr_A(wWestConnectedMapGroup);
    // LD_addr_A(wEastConnectedMapGroup);

    // LD_A_addr(wMapConnections);
    // LD_B_A;
    // uint8_t *_hl = AbsGBROMBankAddrToRAMAddr(wram->wMapAttributesBank, wram->wMapAttributesPointer + 12);

    // BIT_B(NORTH_F);
    // IF_Z goto no_north;
    if(bit_test(wram->wMapConnections, NORTH_F)) {
        // LD_DE(wNorthMapConnection);
        // CALL(aGetMapConnection);
        GetMapConnection_Conv(gMapConnections + NORTH_F, attr->connections[NORTH_F]);
        printf("North connection loaded.\n");
        // CopyBytes(wram_ptr(wNorthMapConnection), _hl, wSouthMapConnection - wNorthMapConnection);
        // _hl += wSouthMapConnection - wNorthMapConnection;
        uint32_t blocks_ptr = GetGBMapBlocksPointer(gMapConnections[NORTH_F].connectedMapGroup, gMapConnections[NORTH_F].connectedMapNumber);
        CopyGBMapConnection((struct MapConnection*)wram_ptr(wNorthMapConnection), gMapConnections + NORTH_F, 
            (blocks_ptr < 0x4000)? blocks_ptr: (blocks_ptr & 0x3fff) | 0x4000);
    }
    else {
        gMapConnections[NORTH_F].connectedMapGroup = 0xff;
        gMapConnections[NORTH_F].connectedMapNumber = 0xff;
        wram->wNorthMapConnection.connectedMapGroup = 0xff;
    }

// no_north:

    // BIT_B(SOUTH_F);
    // IF_Z goto no_south;
    if(bit_test(wram->wMapConnections, SOUTH_F)) {
        // LD_DE(wSouthMapConnection);
        // CALL(aGetMapConnection);
        GetMapConnection_Conv(gMapConnections + SOUTH_F, attr->connections[SOUTH_F]);
        printf("South connection loaded.\n");
        // CopyBytes(wram_ptr(wSouthMapConnection), _hl, wSouthMapConnection - wNorthMapConnection);
        // _hl += wSouthMapConnection - wNorthMapConnection;
        uint32_t blocks_ptr = GetGBMapBlocksPointer(gMapConnections[SOUTH_F].connectedMapGroup, gMapConnections[SOUTH_F].connectedMapNumber);
        CopyGBMapConnection((struct MapConnection*)wram_ptr(wSouthMapConnection), gMapConnections + SOUTH_F, 
            (blocks_ptr < 0x4000)? blocks_ptr: (blocks_ptr & 0x3fff) | 0x4000);
    }
    else {
        gMapConnections[SOUTH_F].connectedMapGroup = 0xff;
        gMapConnections[SOUTH_F].connectedMapNumber = 0xff;
        wram->wSouthMapConnection.connectedMapGroup = 0xff;
    }

// no_south:

    // BIT_B(WEST_F);
    // IF_Z goto no_west;
    if(bit_test(wram->wMapConnections, WEST_F)) {
        // LD_DE(wWestMapConnection);
        // CALL(aGetMapConnection);
        GetMapConnection_Conv(gMapConnections + WEST_F, attr->connections[WEST_F]);
        printf("West connection loaded.\n");
        // CopyBytes(wram_ptr(wWestMapConnection), _hl, wSouthMapConnection - wNorthMapConnection);
        // _hl += wSouthMapConnection - wNorthMapConnection;
        uint32_t blocks_ptr = GetGBMapBlocksPointer(gMapConnections[WEST_F].connectedMapGroup, gMapConnections[WEST_F].connectedMapNumber);
        CopyGBMapConnection((struct MapConnection*)wram_ptr(wWestMapConnection), gMapConnections + WEST_F, 
            (blocks_ptr < 0x4000)? blocks_ptr: (blocks_ptr & 0x3fff) | 0x4000);
    }
    else {
        gMapConnections[WEST_F].connectedMapGroup = 0xff;
        gMapConnections[WEST_F].connectedMapNumber = 0xff;
        wram->wSouthMapConnection.connectedMapGroup = 0xff;
    }

// no_west:

    // BIT_B(EAST_F);
    // IF_Z goto no_east;
    if(bit_test(wram->wMapConnections, EAST_F)) {
        // LD_DE(wEastMapConnection);
        // CALL(aGetMapConnection);
        GetMapConnection_Conv(gMapConnections + EAST_F, attr->connections[EAST_F]);
        printf("East connection loaded.\n");
        // CopyBytes(wram_ptr(wEastMapConnection), _hl, wSouthMapConnection - wNorthMapConnection);
        // _hl += wSouthMapConnection - wNorthMapConnection;
        uint32_t blocks_ptr = GetGBMapBlocksPointer(gMapConnections[EAST_F].connectedMapGroup, gMapConnections[EAST_F].connectedMapNumber);
        CopyGBMapConnection((struct MapConnection*)wram_ptr(wEastMapConnection), gMapConnections + EAST_F, 
            (blocks_ptr < 0x4000)? blocks_ptr: (blocks_ptr & 0x3fff) | 0x4000);
    }
    else {
        gMapConnections[EAST_F].connectedMapGroup = 0xff;
        gMapConnections[EAST_F].connectedMapNumber = 0xff;
        wram->wEastMapConnection.connectedMapGroup = 0xff;
    }

// no_east:
    // RET;
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

void GetMapConnection_Conv(struct MapConnectionData* de, const struct MapConnectionData* hl){
//  Load map connection struct at hl into de.
    // LD_C(wSouthMapConnection - wNorthMapConnection);
// loop:
    // LD_A_hli;
    // LD_de_A;
    // INC_DE;
    // DEC_C;
    // IF_NZ goto loop;
    // RET;
    CopyBytes(de, hl, sizeof(*de));
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

void ReadMapSceneScripts_Conv(const struct MapScripts* hl){
    // LD_A_hli;  // scene_script count
    // LD_C_A;
    // LD_addr_A(wCurMapSceneScriptCount);
    gCurMapSceneScriptCount = hl->scene_script_count;
    // LD_A_L;
    // LD_addr_A(wCurMapSceneScriptsPointer);
    // LD_A_H;
    // LD_addr_A(wCurMapSceneScriptsPointer + 1);
    gCurMapSceneScriptsPointer = hl->scene_scripts;
    // LD_A_C;
    // AND_A_A;
    // RET_Z ;

    // LD_BC(SCENE_SCRIPT_SIZE);
    // CALL(aAddNTimes);
    // RET;
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

void ReadMapCallbacks_Conv(const struct MapScripts* hl){
    // LD_A_hli;
    // LD_C_A;
    // LD_addr_A(wCurMapCallbackCount);
    gCurMapCallbackCount = hl->callback_count;
    // LD_A_L;
    // LD_addr_A(wCurMapCallbacksPointer);
    // LD_A_H;
    // LD_addr_A(wCurMapCallbacksPointer + 1);
    gCurMapCallbacksPointer = hl->callbacks;
    // LD_A_C;
    // AND_A_A;
    // RET_Z ;

    // LD_BC(CALLBACK_SIZE);
    // CALL(aAddNTimes);
    // RET;

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

void ReadWarps_Conv(const struct MapEvents* hl){
    // uint8_t* _hl = AbsGBROMBankAddrToRAMAddr(wram->wMapScriptsBank, wram->wMapEventsPointer);
    // LD_A_hli;
    // LD_C_A;
    // LD_addr_A(wCurMapWarpCount);
    gCurMapWarpCount = hl->warp_event_count;
    // wram->wCurMapWarpCount = _hl[2];
    wram->wCurMapWarpCount = hl->warp_event_count;
    // LD_A_L;
    // LD_addr_A(wCurMapWarpsPointer);
    // LD_A_H;
    // LD_addr_A(wCurMapWarpsPointer + 1);
    gCurMapWarpsPointer = hl->warp_events;
    wram->wCurMapWarpsPointer = wram->wMapEventsPointer + 3;
    printf("warps=%d, 0x%02X\n", wram->wCurMapWarpCount, wram->wCurMapWarpsPointer);
    // LD_A_C;
    // AND_A_A;
    // RET_Z ;
    // LD_BC(WARP_EVENT_SIZE);
    // CALL(aAddNTimes);
    // RET;
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

void ReadCoordEvents_Conv(const struct MapEvents* hl){
    // uint8_t* _hl = AbsGBROMBankAddrToRAMAddr(wram->wMapScriptsBank, wram->wMapEventsPointer);
    // LD_A_hli;
    // LD_C_A;
    // LD_addr_A(wCurMapCoordEventCount);
    gCurMapCoordEventCount = hl->coord_event_count;
    // wram->wCurMapCoordEventCount = _hl[2 + 1 + (wram->wCurMapWarpCount * WARP_EVENT_SIZE)];
    wram->wCurMapCoordEventCount = hl->coord_event_count;
    // LD_A_L;
    // LD_addr_A(wCurMapCoordEventsPointer);
    // LD_A_H;
    // LD_addr_A(wCurMapCoordEventsPointer + 1);
    gCurMapCoordEventsPointer = hl->coord_events;
    wram->wCurMapCoordEventsPointer = wram->wMapEventsPointer + 2 + 1 + (wram->wCurMapWarpCount * WARP_EVENT_SIZE) + 1;
    printf("coords=%d, 0x%02X\n", wram->wCurMapCoordEventCount, wram->wCurMapCoordEventsPointer);

    // LD_A_C;
    // AND_A_A;
    // RET_Z ;

    // LD_BC(COORD_EVENT_SIZE);
    // CALL(aAddNTimes);
    // RET;

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

void ReadBGEvents_Conv(const struct MapEvents* hl){
    // uint8_t* _hl = AbsGBROMBankAddrToRAMAddr(wram->wMapScriptsBank, wram->wMapEventsPointer);
    // LD_A_hli;
    // LD_C_A;
    // LD_addr_A(wCurMapBGEventCount);
    gCurMapBGEventCount = hl->bg_event_count;
    // wram->wCurMapBGEventCount = _hl[2 + 1 + (wram->wCurMapWarpCount * WARP_EVENT_SIZE) + 1 + (wram->wCurMapCoordEventCount * COORD_EVENT_SIZE)];
    wram->wCurMapBGEventCount = hl->bg_event_count;
    // LD_A_L;
    // LD_addr_A(wCurMapBGEventsPointer);
    // LD_A_H;
    // LD_addr_A(wCurMapBGEventsPointer + 1);
    gCurMapBGEventsPointer = hl->bg_events;
    wram->wCurMapBGEventsPointer = wram->wMapEventsPointer + 2 + 1 + (wram->wCurMapWarpCount * WARP_EVENT_SIZE) + 1 + (wram->wCurMapCoordEventCount * COORD_EVENT_SIZE) + 1;

    // LD_A_C;
    // AND_A_A;
    // RET_Z ;

    // LD_BC(BG_EVENT_SIZE);
    // CALL(aAddNTimes);
    // RET;
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

void ReadObjectEvents_Conv(const struct MapEvents* hl){
    // PUSH_HL;
    // CALL(aClearObjectStructs);
    ClearObjectStructs_Conv();
    // POP_DE;
    // uint8_t* _hl = AbsGBROMBankAddrToRAMAddr(wram->wMapScriptsBank, wram->wMapEventsPointer);
    // LD_HL(wMap1Object);
    // LD_A_de;
    // INC_DE;
    // LD_addr_A(wCurMapObjectEventCount);
    gCurMapObjectEventCount = hl->obj_event_count;
    // wram->wCurMapObjectEventCount = _hl[2 + 1 + (wram->wCurMapWarpCount * WARP_EVENT_SIZE) + 1 + (wram->wCurMapCoordEventCount * COORD_EVENT_SIZE) + 1 + (wram->wCurMapBGEventCount * BG_EVENT_SIZE)];
    wram->wCurMapObjectEventCount = hl->obj_event_count;
    // LD_A_E;
    // LD_addr_A(wCurMapObjectEventsPointer);
    // LD_A_D;
    // LD_addr_A(wCurMapObjectEventsPointer + 1);
    gCurMapObjectEventsPointer = hl->obj_events;
    wram->wCurMapObjectEventsPointer = wram->wMapEventsPointer + 2 + 1 + (wram->wCurMapWarpCount * WARP_EVENT_SIZE) + 1 + (wram->wCurMapCoordEventCount * COORD_EVENT_SIZE) + 1 + (wram->wCurMapBGEventCount * BG_EVENT_SIZE) + 1;

    // LD_A_addr(wCurMapObjectEventCount);
    // CALL(aCopyMapObjectEvents);
    uint8_t rest = CopyMapObjectEvents_Conv(&wram->wPlayerObject + 1, gCurMapObjectEventsPointer, gCurMapObjectEventCount);

//  get NUM_OBJECTS - [wCurMapObjectEventCount]
    // LD_A_addr(wCurMapObjectEventCount);
    // LD_C_A;
    // LD_A(NUM_OBJECTS);  // - 1
    // SUB_A_C;
    // IF_Z goto skip;
    if(rest != 0) {
    // jr c, .skip

    // could have done "inc hl" instead
        // LD_BC(1);
        // ADD_HL_BC;
    //  Fill the remaining sprite IDs and y coords with 0 and -1, respectively.
    //  Bleeds into wObjectMasks due to a bug.  Uncomment the above code to fix.
        // LD_BC(MAPOBJECT_LENGTH);
        for(uint8_t i = NUM_OBJECTS - rest; i < NUM_OBJECTS - 1; ++i) {
        // loop:
            // LD_hl(0);
            // INC_HL;
            wram->wMapObject[i].sprite = 0;
            // LD_hl(-1);
            // DEC_HL;
            wram->wMapObject[i].objectYCoord = 0xff;
            // ADD_HL_BC;
            // DEC_A;
            // IF_NZ goto loop;
        }
    }


// skip:
    // LD_H_D;
    // LD_L_E;
    // RET;
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

#include "flag.h"
#include "../data/script_pointers.h"

uint8_t CopyMapObjectEvents_Conv(struct MapObject* hl, const struct ObjEvent* de, uint8_t count){
    // AND_A_A;
    // RET_Z ;
    if(count == 0)
        return NUM_OBJECTS;

    // LD_C_A;

    for(uint8_t i = 0; i < count; ++i) {
    // loop:
        // PUSH_BC;
        // PUSH_HL;
        // LD_A(0xff);
        // LD_hli_A;
        hl[i].structId = 0xff;
        // LD_B(OBJECT_EVENT_SIZE);

        hl[i].sprite = de[i].sprite;
        hl[i].objectYCoord = de[i].y;
        hl[i].objectXCoord = de[i].x;
        hl[i].objectMovement = de[i].movement;
        hl[i].objectRadius = (de[i].radiusX << 4) | de[i].radiusY;
        hl[i].objectHour = de[i].h1;
        hl[i].objectTimeOfDay = de[i].h2;
        hl[i].objectColor = (de[i].color << 4) | (de[i].function & 0xf);
        hl[i].objectRange = de[i].sightRange;
        hl[i].objectScript = 0x4000 | (GetGBScriptPointer(wram->wMapGroup, wram->wMapNumber, i) & 0x3fff);
        hl[i].objectEventFlag = (uint16_t)de[i].eventFlag;
        if(hl[i].objectEventFlag != 0xffff)
            printf("%02d: x=%d, y=%d, script=$%04x, eventFlag=%d (%c)\n", i, hl[i].objectXCoord, hl[i].objectYCoord, hl[i].objectScript, (uint16_t)de[i].eventFlag,
                (EventFlagAction(hl[i].objectEventFlag, CHECK_FLAG))? '1': '0');
        else {
            printf("%02d: x=%d, y=%d, script=$%04x\n", i, hl[i].objectXCoord, hl[i].objectYCoord, hl[i].objectScript);
        }
    // loop2:
        // LD_A_de;
        // INC_DE;
        // LD_hli_A;
        // DEC_B;
        // IF_NZ goto loop2;

        // POP_HL;
        // LD_BC(MAPOBJECT_LENGTH);
        // ADD_HL_BC;
        // POP_BC;
        // DEC_C;
        // IF_NZ goto loop;
    }
    // RET;
    return NUM_OBJECTS - count;
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

void ClearObjectStructs_Conv(void){
    // LD_HL(wObject1Struct);
    // LD_BC(OBJECT_LENGTH * (NUM_OBJECT_STRUCTS - 1));
    // XOR_A_A;
    // CALL(aByteFill);
    ByteFill(wram->wObjectStruct, sizeof(wram->wObjectStruct), 0);

//  Just to make sure (this is rather pointless)
    // LD_HL(wObject1Struct);
    // LD_DE(OBJECT_LENGTH);
    // LD_C(NUM_OBJECT_STRUCTS - 1);
    // XOR_A_A;

// loop:
    // LD_hl_A;
    // ADD_HL_DE;
    // DEC_C;
    // IF_NZ goto loop;
    // RET;
}

void GetWarpDestCoords(void){
    return GetWarpDestCoords_Conv();
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

void GetWarpDestCoords_Conv(void){
    // CALL(aGetMapScriptsBank);
    // RST(aBankswitch);

    // LD_HL(wMapEventsPointer);
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // for(int rept = 0; rept < 3; rept++){  //  get to the warp coords
    // INC_HL;
    // }
    // LD_A_addr(wWarpNumber);
    // DEC_A;
    // LD_C_A;
    // LD_B(0);
    // LD_A(WARP_EVENT_SIZE);
    // CALL(aAddNTimes);
    
    const struct WarpEventData* const warp = gMapEventsPointer->warp_events + (wram->wWarpNumber - 1);
    // LD_A_hli;
    // LD_addr_A(wYCoord);
    wram->wYCoord = warp->y;
    // LD_A_hli;
    // LD_addr_A(wXCoord);
    wram->wXCoord = warp->x;
// destination warp number
    // LD_A_hli;
    // CP_A(-1);
    // IF_NZ goto skip;
    if(warp->warpNumber == (uint8_t)-1) {
        // CALL(aGetWarpDestCoords_backup);
    // backup:
        // LD_A_addr(wPrevWarp);
        // LD_addr_A(wBackupWarpNumber);
        wram->wBackupWarpNumber = wram->wPrevWarp;
        // LD_A_addr(wPrevMapGroup);
        // LD_addr_A(wBackupMapGroup);
        wram->wBackupMapGroup = wram->wPrevMapGroup;
        // LD_A_addr(wPrevMapNumber);
        // LD_addr_A(wBackupMapNumber);
        wram->wBackupMapNumber = wram->wPrevMapNumber;
        // RET;
    }

// skip:
    // FARCALL(aGetMapScreenCoords);
    GetMapScreenCoords();
    // RET;
}

void LoadBlockData(void){
    PEEK("");
    // LD_HL(wOverworldMapBlocks);
    // LD_BC(wOverworldMapBlocksEnd - wOverworldMapBlocks);
    // LD_A(0);
    // CALL(aByteFill);
    ByteFill(wram->wOverworldMapBlocks, sizeof(wram->wOverworldMapBlocks), 0);
    // CALL(aChangeMap);
    ChangeMap();
    // CALL(aFillMapConnections);
    FillMapConnections();
    // LD_A(MAPCALLBACK_TILES);
    // CALL(aRunMapCallback);
    RunMapCallback_Conv(MAPCALLBACK_TILES);
    // RET;
}

void ChangeMap(void){
    // LDH_A_addr(hROMBank);
    // PUSH_AF;

    // LD_HL(wOverworldMapBlocks);
    uint8_t* hl = wram->wOverworldMapBlocks;
    // LD_A_addr(wMapWidth);
    // LDH_addr_A(hConnectedMapWidth);
    hram->hConnectedMapWidth = wram->wMapWidth;
    // ADD_A(0x6);
    // LDH_addr_A(hConnectionStripLength);
    hram->hConnectionStripLength = wram->wMapWidth + 0x6;
    // LD_C_A;
    // LD_B(0);
    // ADD_HL_BC;
    // ADD_HL_BC;
    // ADD_HL_BC;
    hl += hram->hConnectionStripLength * 3;
    // LD_C(3);
    // ADD_HL_BC;
    hl += 3;
    // LD_A_addr(wMapBlocksBank);
    // RST(aBankswitch);

    // LD_A_addr(wMapBlocksPointer);
    // LD_E_A;
    // LD_A_addr(wMapBlocksPointer + 1);
    // LD_D_A;
    const uint8_t* de = gMapBlocks.ptr;
    // LD_A_addr(wMapHeight);
    // LD_B_A;
    uint8_t b = wram->wMapHeight;

    do {
    // row:
        // PUSH_HL;
        uint8_t* hl2 = hl;
        // LDH_A_addr(hConnectedMapWidth);
        // LD_C_A;
        uint8_t c = hram->hConnectedMapWidth;

        do {
        // col:
            // LD_A_de;
            // INC_DE;
            // LD_hli_A;
            *(hl++) = *(de++);
            // DEC_C;
            // IF_NZ goto col;
        } while(--c != 0);
        // POP_HL;
        // LDH_A_addr(hConnectionStripLength);
        // ADD_A_L;
        // LD_L_A;
        // IF_NC goto okay;
        // INC_H;

    // okay:
        hl = hl2 + hram->hConnectionStripLength;
        // DEC_B;
        // IF_NZ goto row;
    } while(--b != 0);

    // POP_AF;
    // RST(aBankswitch);
    // RET;
}

void FillMapConnections(void){
//  North
    // LD_A_addr(wNorthConnectedMapGroup);
    // CP_A(0xff);
    // IF_Z goto South;
    if(gMapConnections[NORTH_F].connectedMapGroup != 0xff) {
        // LD_B_A;
        // LD_A_addr(wNorthConnectedMapNumber);
        // LD_C_A;
        // CALL(aGetAnyMapBlocksBank);

        // LD_A_addr(wNorthConnectionStripPointer);
        // LD_L_A;
        // LD_A_addr(wNorthConnectionStripPointer + 1);
        // LD_H_A;
        asset_s a = LoadAsset(GetAnyMapPointer_Conv2(gMapConnections[NORTH_F].connectedMapGroup, gMapConnections[NORTH_F].connectedMapNumber)->attr->blocksPath);
        uint8_t* hl = (uint8_t*)a.ptr + gMapConnections[NORTH_F].connectionStripOffset;
        // LD_A_addr(wNorthConnectionStripLocation);
        // LD_E_A;
        // LD_A_addr(wNorthConnectionStripLocation + 1);
        // LD_D_A;
        uint8_t* de = gMapConnections[NORTH_F].connectionStripLocation;
        // LD_A_addr(wNorthConnectionStripLength);
        // LDH_addr_A(hConnectionStripLength);
        hram->hConnectionStripLength = gMapConnections[NORTH_F].connectionStripLength;
        // LD_A_addr(wNorthConnectedMapWidth);
        // LDH_addr_A(hConnectedMapWidth);
        hram->hConnectedMapWidth = gMapConnections[NORTH_F].connectedMapWidth;
        // CALL(aFillNorthConnectionStrip);
        FillNorthConnectionStrip(de, hl);
        FreeAsset(a);
    }

// South:
    // LD_A_addr(wSouthConnectedMapGroup);
    // CP_A(0xff);
    // IF_Z goto West;
    if(gMapConnections[SOUTH_F].connectedMapGroup != 0xff) {
        // LD_B_A;
        // LD_A_addr(wSouthConnectedMapNumber);
        // LD_C_A;
        // CALL(aGetAnyMapBlocksBank);

        // LD_A_addr(wSouthConnectionStripPointer);
        // LD_L_A;
        // LD_A_addr(wSouthConnectionStripPointer + 1);
        // LD_H_A;
        asset_s a = LoadAsset(GetAnyMapPointer_Conv2(gMapConnections[SOUTH_F].connectedMapGroup, gMapConnections[SOUTH_F].connectedMapNumber)->attr->blocksPath);
        uint8_t* hl = (uint8_t*)a.ptr + gMapConnections[SOUTH_F].connectionStripOffset;
        // LD_A_addr(wSouthConnectionStripLocation);
        // LD_E_A;
        // LD_A_addr(wSouthConnectionStripLocation + 1);
        // LD_D_A;
        uint8_t* de = gMapConnections[SOUTH_F].connectionStripLocation;
        // LD_A_addr(wSouthConnectionStripLength);
        // LDH_addr_A(hConnectionStripLength);
        hram->hConnectionStripLength = gMapConnections[SOUTH_F].connectionStripLength;
        // LD_A_addr(wSouthConnectedMapWidth);
        // LDH_addr_A(hConnectedMapWidth);
        hram->hConnectedMapWidth = gMapConnections[SOUTH_F].connectedMapWidth;
        // CALL(aFillSouthConnectionStrip);
        FillSouthConnectionStrip(de, hl);
        FreeAsset(a);
    }

// West:
    // LD_A_addr(wWestConnectedMapGroup);
    // CP_A(0xff);
    // IF_Z goto East;
    if(gMapConnections[WEST_F].connectedMapGroup != 0xff) {
        // LD_B_A;
        // LD_A_addr(wWestConnectedMapNumber);
        // LD_C_A;
        // CALL(aGetAnyMapBlocksBank);

        // LD_A_addr(wWestConnectionStripPointer);
        // LD_L_A;
        // LD_A_addr(wWestConnectionStripPointer + 1);
        // LD_H_A;
        asset_s a = LoadAsset(GetAnyMapPointer_Conv2(gMapConnections[WEST_F].connectedMapGroup, gMapConnections[WEST_F].connectedMapNumber)->attr->blocksPath);
        uint8_t* hl = (uint8_t*)a.ptr + gMapConnections[WEST_F].connectionStripOffset;
        // LD_A_addr(wWestConnectionStripLocation);
        // LD_E_A;
        // LD_A_addr(wWestConnectionStripLocation + 1);
        // LD_D_A;
        uint8_t* de = gMapConnections[WEST_F].connectionStripLocation;
        // LD_A_addr(wWestConnectionStripLength);
        // LD_B_A;
        uint8_t b = gMapConnections[WEST_F].connectionStripLength;
        // LD_A_addr(wWestConnectedMapWidth);
        // LDH_addr_A(hConnectionStripLength);
        hram->hConnectionStripLength = gMapConnections[WEST_F].connectedMapWidth;
        // CALL(aFillWestConnectionStrip);
        FillWestConnectionStrip(de, hl, b);
        FreeAsset(a);
    }

// East:
    // LD_A_addr(wEastConnectedMapGroup);
    // CP_A(0xff);
    // IF_Z goto Done;
    if(gMapConnections[EAST_F].connectedMapGroup != 0xff) {
        // LD_B_A;
        // LD_A_addr(wEastConnectedMapNumber);
        // LD_C_A;
        // CALL(aGetAnyMapBlocksBank);

        // LD_A_addr(wEastConnectionStripPointer);
        // LD_L_A;
        // LD_A_addr(wEastConnectionStripPointer + 1);
        // LD_H_A;
        asset_s a = LoadAsset(GetAnyMapPointer_Conv2(gMapConnections[EAST_F].connectedMapGroup, gMapConnections[EAST_F].connectedMapNumber)->attr->blocksPath);
        uint8_t* hl = (uint8_t*)a.ptr + gMapConnections[EAST_F].connectionStripOffset;
        // LD_A_addr(wEastConnectionStripLocation);
        // LD_E_A;
        // LD_A_addr(wEastConnectionStripLocation + 1);
        // LD_D_A;
        uint8_t* de = gMapConnections[EAST_F].connectionStripLocation;
        // LD_A_addr(wEastConnectionStripLength);
        // LD_B_A;
        uint8_t b = gMapConnections[EAST_F].connectionStripLength;
        // LD_A_addr(wEastConnectedMapWidth);
        // LDH_addr_A(hConnectionStripLength);
        hram->hConnectionStripLength = gMapConnections[EAST_F].connectedMapWidth;
        // CALL(aFillEastConnectionStrip);
        FillEastConnectionStrip(de, hl, b);
        FreeAsset(a);
    }

// Done:
    // RET;

}

void FillNorthConnectionStrip(uint8_t* de, const uint8_t* hl){
    return FillSouthConnectionStrip(de, hl);
}

void FillSouthConnectionStrip(uint8_t* de, const uint8_t* hl){
    // LD_C(3);
    uint8_t c = 3;

    do {
    // y:
        // PUSH_DE;
        uint8_t* de2 = de;

        // PUSH_HL;
        const uint8_t* hl2 = hl;
        // LDH_A_addr(hConnectionStripLength);
        // LD_B_A;
        uint8_t b = hram->hConnectionStripLength;

        do {
        // x:
            // LD_A_hli;
            // LD_de_A;
            // INC_DE;
            *(de++) = *(hl++);
            // DEC_B;
            // IF_NZ goto x;
        } while(--b != 0);
        // POP_HL;

        // LDH_A_addr(hConnectedMapWidth);
        // LD_E_A;
        // LD_D(0);
        // ADD_HL_DE;
        // POP_DE;
        hl = hl2 + hram->hConnectedMapWidth;

        // LD_A_addr(wMapWidth);
        // ADD_A(6);
        // ADD_A_E;
        // LD_E_A;
        // IF_NC goto okay;
        // INC_D;
        de = de2 + wram->wMapWidth + 6;

    // okay:
        // DEC_C;
        // IF_NZ goto y;
    } while(--c != 0);
    // RET;
}

void FillWestConnectionStrip(uint8_t* de, const uint8_t* hl, uint8_t b){
    return FillEastConnectionStrip(de, hl, b);
}

void FillEastConnectionStrip(uint8_t* de, const uint8_t* hl, uint8_t b){

    // Moved this out of the loop lol.
    hram->hConnectedMapWidth = wram->wMapWidth + 6;
    do {
    // loop:
        // LD_A_addr(wMapWidth);
        // ADD_A(6);
        // LDH_addr_A(hConnectedMapWidth);

        // PUSH_DE;
        uint8_t* de2 = de;

        // PUSH_HL;
        const uint8_t* hl2 = hl;
        // LD_A_hli;
        // LD_de_A;
        // INC_DE;
        *(de++) = *(hl++);
        // LD_A_hli;
        // LD_de_A;
        // INC_DE;
        *(de++) = *(hl++);
        // LD_A_hli;
        // LD_de_A;
        // INC_DE;
        *(de++) = *(hl++);
        // POP_HL;

        // LDH_A_addr(hConnectionStripLength);
        // LD_E_A;
        // LD_D(0);
        // ADD_HL_DE;
        // POP_DE;
        hl = hl2 + hram->hConnectionStripLength;

        // LDH_A_addr(hConnectedMapWidth);
        // ADD_A_E;
        // LD_E_A;
        // IF_NC goto okay;
        // INC_D;
        de = de2 + hram->hConnectedMapWidth;

    // okay:
        // DEC_B;
        // IF_NZ goto loop;
    } while(--b != 0);
    // RET;
}

void LoadMapStatus(void){
    LD_addr_A(wMapStatus);
    RET;

}

void LoadMapStatus_Conv(uint8_t a){
    // LD_addr_A(wMapStatus);
    // RET;
    wram->wMapStatus = a;
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

uint8_t CallScript_Conv(uint8_t a, uint16_t hl){
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
    return PLAYEREVENT_MAPSCRIPT;
}

//  Call a script at hl.
uint8_t CallScript_Conv2(Script_fn_t hl){
    // LD_addr_A(wScriptBank);
    // LD_A_L;
    // LD_addr_A(wScriptPos);
    // LD_A_H;
    // LD_addr_A(wScriptPos + 1);
    gCurScript.fn = hl;
    gCurScript.position = 0;
    ByteFill(gCurScript.stack, sizeof(gCurScript.stack), 0);
    gCurScript.stack_ptr = 0;

    // LD_A(PLAYEREVENT_MAPSCRIPT);
    // LD_addr_A(wScriptRunning);
    wram->wScriptRunning = PLAYEREVENT_MAPSCRIPT;

    // SCF;
    // RET;
    return PLAYEREVENT_MAPSCRIPT;
}

void CallMapScript(void){
//  Call a script at hl in the current bank if there isn't already a script running
    LD_A_addr(wScriptRunning);
    AND_A_A;
    RET_NZ ;
    CALL(aGetMapScriptsBank);
    JR(mCallScript);

}

uint8_t CallMapScript_Conv(uint16_t hl){
//  Call a script at hl in the current bank if there isn't already a script running
    // LD_A_addr(wScriptRunning);
    // AND_A_A;
    // RET_NZ ;
    if(wram->wScriptRunning != 0)
        return 0;
    
    // CALL(aGetMapScriptsBank);
    // JR(mCallScript);
    return CallScript_Conv(GetMapScriptsBank_Conv(), hl);
}

//  Call a script at hl if there isn't already a script running
uint8_t CallMapScript_Conv2(Script_fn_t hl){
    // LD_A_addr(wScriptRunning);
    // AND_A_A;
    // RET_NZ ;
    if(wram->wScriptRunning != 0)
        return 0;
    
    // CALL(aGetMapScriptsBank);
    // JR(mCallScript);
    return CallScript_Conv2(hl);
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

static Script_fn_t RunMapCallback_FindCallback(uint8_t b) {
    // LD_A_addr(wCurMapCallbackCount);
    // LD_C_A;
    const uint8_t c = gCurMapCallbackCount;
    // AND_A_A;
    // RET_Z ;
    if(c == 0)
        return NULL;
    // LD_HL(wCurMapCallbacksPointer);
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // OR_A_H;
    // RET_Z ;
    if(gCurMapCallbacksPointer == NULL)
        return NULL;
    // LD_DE(CALLBACK_SIZE);

    for(uint8_t i = 0; i < c; ++i) {
    // loop:
        // LD_A_hl;
        // CP_A_B;
        // IF_Z goto found;
        if(gCurMapCallbacksPointer[i].type == b) {
        // found:
            // INC_HL;
            // LD_A_hli;
            // LD_H_hl;
            // LD_L_A;
            // SCF;
            // RET;
            return gCurMapCallbacksPointer[i].script;
        }
        // ADD_HL_DE;
        // DEC_C;
        // IF_NZ goto loop;
    }
    // XOR_A_A;
    // RET;
    return NULL;
}

void RunMapCallback_Conv(uint8_t a){
//  Will run the first callback found with execution index equal to a.
    // LD_B_A;
    // LDH_A_addr(hROMBank);
    // PUSH_AF;
    uint8_t bank = hram->hROMBank;
    // CALL(aSwitchToMapScriptsBank);
    SwitchToMapScriptsBank_Conv();
    // CALL(aRunMapCallback_FindCallback);
    Script_fn_t callback = RunMapCallback_FindCallback(a);
    // IF_NC goto done;
    if(callback != NULL) {
        // CALL(aGetMapScriptsBank);
        // LD_B_A;
        // LD_D_H;
        // LD_E_L;
        // CALL(aExecuteCallbackScript);
        ExecuteCallbackScript_Conv(callback);
    }

// done:
    // POP_AF;
    // RST(aBankswitch);
    Bankswitch(bank);
    // RET;
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

//  Do map callback de and return to script bank b.
void ExecuteCallbackScript_Conv(Script_fn_t de){
    // FARCALL(aCallCallback);
    CallCallback_Conv(de);
    // LD_A_addr(wScriptMode);
    // PUSH_AF;
    uint8_t mode = wram->wScriptMode;
    // LD_HL(wScriptFlags);
    // LD_A_hl;
    // PUSH_AF;
    uint8_t scriptFlags = wram->wScriptFlags;
    // SET_hl(1);
    bit_set(wram->wScriptFlags, 1);
    // FARCALL(aEnableScriptMode);
    EnableScriptMode_Conv();
    // FARCALL(aScriptEvents);
    ScriptEvents_Conv();
    // POP_AF;
    // LD_addr_A(wScriptFlags);
    wram->wScriptFlags = scriptFlags;
    // POP_AF;
    // LD_addr_A(wScriptMode);
    wram->wScriptMode = mode;
    // RET;
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

void MapTextbox_Conv(const struct TextCmd* text){
    // LDH_A_addr(hROMBank);
    // PUSH_AF;

    // LD_A_B;
    // RST(aBankswitch);

    // PUSH_HL;
    // CALL(aSpeechTextbox);
    SpeechTextbox_Conv2();
    // CALL(aSafeUpdateSprites);
    SafeUpdateSprites_Conv();
    // LD_A(1);
    // LDH_addr_A(hOAMUpdate);
    hram->hOAMUpdate = 1;
    // CALL(aApplyTilemap);
    ApplyTilemap_Conv();
    // POP_HL;
    // CALL(aPrintTextboxText);
    PrintTextboxText_Conv2(text);
    // XOR_A_A;
    // LDH_addr_A(hOAMUpdate);
    hram->hOAMUpdate = 0;

    // POP_AF;
    // RST(aBankswitch);
    // RET;
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

//  Initialize the movement data for object c at hl
bool GetMovementData_Conv(uint8_t c, const uint8_t* hl){
    // LDH_A_addr(hROMBank);
    // PUSH_AF;
    // LD_A_B;
    // RST(aBankswitch);

    // LD_A_C;
    // CALL(aLoadMovementDataPointer);

    // POP_HL;
    // LD_A_H;
    // RST(aBankswitch);
    // RET;
    return LoadMovementDataPointer_Conv2(c, hl);
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

bool ObjectEvent(script_s* s){
    SCRIPT_BEGIN
    jumptextfaceplayer(ObjectEventText);
    SCRIPT_END
    // return ObjectEventText();
}

const txt_cmd_s ObjectEventText[] = {
    text_far(v_ObjectEventText)
    text_end
};

bool BGEvent(script_s* s) {
//  //  unreferenced
    SCRIPT_BEGIN
    jumptext(BGEventText);
    SCRIPT_END
    // return BGEventText();
}

const txt_cmd_s BGEventText[] = {
    text_far(v_BGEventText)
    text_end
};

bool CoordinatesEvent(script_s* s){
//  //  unreferenced
    SCRIPT_BEGIN
    jumptext(CoordinatesEventText);
    SCRIPT_END
    // return CoordinatesEventText();
}

const txt_cmd_s CoordinatesEventText[] = {
    text_far(v_CoordinatesEventText)
    text_end
};

void CheckObjectMask(void){
    LDH_A_addr(hMapObjectIndex);
    LD_E_A;
    LD_D(0);
    LD_HL(wObjectMasks);
    ADD_HL_DE;
    LD_A_hl;
    RET;

}

uint8_t CheckObjectMask_Conv(uint8_t a){
    // LDH_A_addr(hMapObjectIndex);
    // LD_E_A;
    // LD_D(0);
    // LD_HL(wObjectMasks);
    // ADD_HL_DE;
    // LD_A_hl;
    // RET;
    return wram->wObjectMasks[a];
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

void MaskObject_Conv(uint8_t a){
    // LDH_A_addr(hMapObjectIndex);
    // LD_E_A;
    // LD_D(0);
    // LD_HL(wObjectMasks);
    // ADD_HL_DE;
    // LD_hl(-1);  // masked
    // RET;
    wram->wObjectMasks[a] = 0xff;
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

void UnmaskObject_Conv(uint8_t a){
    // LDH_A_addr(hMapObjectIndex);
    // LD_E_A;
    // LD_D(0);
    // LD_HL(wObjectMasks);
    // ADD_HL_DE;
    // LD_hl(0);  // unmasked
    // RET;
    wram->wObjectMasks[a] = 0;
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
    // hlcoord(0, 0, wTilemap);
    tile_t* hl = coord(0, 0, wram->wTilemap);
    // LD_DE(wBGMapBuffer);
    // CALL(aBackupBGMapRow);
    BackupBGMapRow_Conv(wram->wBGMapBuffer, hl);
    // LD_C(2 * SCREEN_WIDTH);
    // CALL(aScrollBGMapPalettes);
    ScrollBGMapPalettes(2 * SCREEN_WIDTH);
    // LD_A_addr(wBGMapAnchor);
    // LD_E_A;
    // LD_A_addr(wBGMapAnchor + 1);
    // LD_D_A;
    // CALL(aUpdateBGMapRow);
    UpdateBGMapRow_Conv(wram->wBGMapAnchor);
    // LD_A(0x1);
    // LDH_addr_A(hBGMapUpdate);
    hram->hBGMapUpdate = 0x1;
    // RET;
}

void ScrollMapDown(void){
    // hlcoord(0, SCREEN_HEIGHT - 2, wTilemap);
    tile_t* hl = coord(0, SCREEN_HEIGHT - 2, wram->wTilemap);
    // LD_DE(wBGMapBuffer);
    // CALL(aBackupBGMapRow);
    BackupBGMapRow_Conv(wram->wBGMapBuffer, hl);
    // LD_C(2 * SCREEN_WIDTH);
    // CALL(aScrollBGMapPalettes);
    ScrollBGMapPalettes(2 * SCREEN_WIDTH);
    // LD_A_addr(wBGMapAnchor);
    // LD_L_A;
    // LD_A_addr(wBGMapAnchor + 1);
    // LD_H_A;
    // LD_BC(BG_MAP_WIDTH * LEN_2BPP_TILE);
    // ADD_HL_BC;
    uint16_t de = wram->wBGMapAnchor + (BG_MAP_WIDTH * LEN_2BPP_TILE);
//  cap d at HIGH(vBGMap0)
    // LD_A_H;
    // AND_A(0b00000011);
    // OR_A(HIGH(vBGMap0));
    // LD_E_L;
    // LD_D_A;
    de = LOW(de) | (((HIGH(de) & 0b00000011) | HIGH(vBGMap0)) << 8);
    // CALL(aUpdateBGMapRow);
    UpdateBGMapRow_Conv(de);
    // LD_A(0x1);
    // LDH_addr_A(hBGMapUpdate);
    hram->hBGMapUpdate = 0x1;
    // RET;
}

void ScrollMapLeft(void){
    // hlcoord(0, 0, wTilemap);
    // LD_DE(wBGMapBuffer);
    // CALL(aBackupBGMapColumn);
    BackupBGMapColumn_Conv(wram->wBGMapBuffer, coord(0, 0, wram->wTilemap));
    // LD_C(2 * SCREEN_HEIGHT);
    // CALL(aScrollBGMapPalettes);
    ScrollBGMapPalettes(2 * SCREEN_HEIGHT);
    // LD_A_addr(wBGMapAnchor);
    // LD_E_A;
    // LD_A_addr(wBGMapAnchor + 1);
    // LD_D_A;
    // CALL(aUpdateBGMapColumn);
    UpdateBGMapColumn_Conv(wram->wBGMapAnchor);
    // LD_A(0x1);
    // LDH_addr_A(hBGMapUpdate);
    hram->hBGMapUpdate = 0x1;
    // RET;
}

void ScrollMapRight(void){
    // hlcoord(SCREEN_WIDTH - 2, 0, wTilemap);
    // LD_DE(wBGMapBuffer);
    // CALL(aBackupBGMapColumn);
    BackupBGMapColumn_Conv(wram->wBGMapBuffer, coord(SCREEN_WIDTH - 2, 0, wram->wTilemap));
    // LD_C(2 * SCREEN_HEIGHT);
    // CALL(aScrollBGMapPalettes);
    ScrollBGMapPalettes(2 * SCREEN_HEIGHT);
    // LD_A_addr(wBGMapAnchor);
    // LD_E_A;
    uint8_t e = LOW(wram->wBGMapAnchor);
    // AND_A(0b11100000);
    // LD_B_A;
    // LD_A_E;
    // ADD_A(SCREEN_HEIGHT);
    // AND_A(0b00011111);
    // OR_A_B;
    // LD_E_A;
    // LD_A_addr(wBGMapAnchor + 1);
    // LD_D_A;
    uint16_t de = (wram->wBGMapAnchor & 0xff00) | (((e + SCREEN_HEIGHT) & 0b00011111) | (e & 0b11100000));
    // CALL(aUpdateBGMapColumn);
    UpdateBGMapColumn_Conv(de);
    // LD_A(0x1);
    // LDH_addr_A(hBGMapUpdate);
    hram->hBGMapUpdate = 0x1;
    // RET;
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

void BackupBGMapRow_Conv(tile_t* de, const tile_t* hl){
    // LD_C(2 * SCREEN_WIDTH);
    uint8_t c = 2 * SCREEN_WIDTH;

    do {
    // loop:
        // LD_A_hli;
        // LD_de_A;
        // INC_DE;
        *(de++) = *(hl++);
        // DEC_C;
        // IF_NZ goto loop;
    } while(--c != 0);
    // RET;
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

void BackupBGMapColumn_Conv(tile_t* de, const tile_t* hl){
    // LD_C(SCREEN_HEIGHT);
    uint8_t c = SCREEN_HEIGHT;

    do {
    // loop:
        // LD_A_hli;
        // LD_de_A;
        // INC_DE;
        *(de++) = *(hl++);
        // LD_A_hl;
        // LD_de_A;
        // INC_DE;
        *(de++) = *hl;
        // LD_A(SCREEN_WIDTH - 1);
        // ADD_A_L;
        // LD_L_A;
        // IF_NC goto skip;
        // INC_H;

    // skip:
        hl += SCREEN_WIDTH - 1;
        // DEC_C;
        // IF_NZ goto loop;
    } while(--c != 0);
    // RET;
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

static uint8_t* UpdateBGMapRow_iteration(uint8_t* hl, uint16_t de) {
    // LD_C(10);
    uint8_t c = 10;

    do {
    // loop:
        // LD_A_E;
        // LD_hli_A;
        *(hl++) = LOW(de);
        // LD_A_D;
        // LD_hli_A;
        *(hl++) = HIGH(de);
        // LD_A_E;
        // INC_A;
        // INC_A;
        // AND_A(0x1f);
        // LD_B_A;
        uint8_t b = (LOW(de) + 2) & 0x1f;
        // LD_A_E;
        // AND_A(0xe0);
        // OR_A_B;
        // LD_E_A;
        de = (de & 0xff00) | ((LOW(de) & 0xe0) | b);
        // DEC_C;
        // IF_NZ goto loop;
    } while(--c != 0);
    // LD_A(SCREEN_WIDTH);
    // LDH_addr_A(hBGMapTileCount);
    hram->hBGMapTileCount = SCREEN_WIDTH;
    // RET;
    return hl;
}

void UpdateBGMapRow_Conv(uint16_t de){
    // LD_HL(wBGMapBufferPointers);
    uint8_t* hl = wram->wBGMapBufferPointers;
    // PUSH_DE;
    // CALL(aUpdateBGMapRow_iteration);
    hl = UpdateBGMapRow_iteration(hl, de);
    // POP_DE;
    // LD_A(BG_MAP_WIDTH);
    // ADD_A_E;
    // LD_E_A;
    de += BG_MAP_WIDTH;
    UpdateBGMapRow_iteration(hl, de);
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

void UpdateBGMapColumn_Conv(uint16_t de){
    // LD_HL(wBGMapBufferPointers);
    uint8_t* hl = wram->wBGMapBufferPointers;
    // LD_C(SCREEN_HEIGHT);
    uint8_t c = SCREEN_HEIGHT;

    do {
    // loop:
        // LD_A_E;
        // LD_hli_A;
        *(hl++) = LOW(de);
        // LD_A_D;
        // LD_hli_A;
        *(hl++) = HIGH(de);
        // LD_A(BG_MAP_WIDTH);
        // ADD_A_E;
        // LD_E_A;
        // IF_NC goto skip;
        // INC_D;
        de += BG_MAP_WIDTH;
    //  cap d at HIGH(vBGMap0)
        // LD_A_D;
        // AND_A(0b11);
        // OR_A(HIGH(vBGMap0));
        // LD_D_A;
        de = LOW(de) | (((HIGH(de) & 0b11) | HIGH(vBGMap0)) << 8);

    // skip:
        // DEC_C;
        // IF_NZ goto loop;
    } while(--c != 0);
    // LD_A(SCREEN_HEIGHT);
    // LDH_addr_A(hBGMapTileCount);
    hram->hBGMapTileCount = SCREEN_HEIGHT;
    // RET;
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
    return LoadTilesetGFX_Conv();
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

void LoadTilesetGFX_Conv(void){
    // LD_HL(wTilesetAddress);
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // LD_A_addr(wTilesetBank);
    // LD_E_A;

    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    // LD_A(MBANK(awDecompressScratch));
    // LDH_addr_A(rSVBK);

    // LD_A_E;
    // LD_DE(wDecompressScratch);
    // CALL(aFarDecompress);
    LoadPNG2bppAssetSectionToVRAM(wram->wDecompressScratch, gTilesetPointer->gfxPath, 0, 0x60 + 0x60);

    // LD_HL(wDecompressScratch);
    // LD_DE(vTiles2);
    // LD_BC(0x60 * LEN_2BPP_TILE);
    // CALL(aCopyBytes);
    CopyBytes(vram->vTiles2, wram->wDecompressScratch, 0x60 * LEN_2BPP_TILE);

    // LDH_A_addr(rVBK);
    // PUSH_AF;
    // LD_A(MBANK(avTiles5));
    // LDH_addr_A(rVBK);

    // LD_HL(wDecompressScratch + 0x60 * LEN_2BPP_TILE);
    // LD_DE(vTiles5);
    // LD_BC(0x60 * LEN_2BPP_TILE);
    // CALL(aCopyBytes);
    CopyBytes(vram->vTiles5, wram->wDecompressScratch + 0x60 * LEN_2BPP_TILE, 0x60 * LEN_2BPP_TILE);

    // POP_AF;
    // LDH_addr_A(rVBK);

    // POP_AF;
    // LDH_addr_A(rSVBK);

//  These tilesets support dynamic per-mapgroup roof tiles.
    // LD_A_addr(wMapTileset);
    // CP_A(TILESET_JOHTO);
    // IF_Z goto load_roof;
    // CP_A(TILESET_JOHTO_MODERN);
    // IF_Z goto load_roof;
    // CP_A(TILESET_BATTLE_TOWER_OUTSIDE);
    // IF_Z goto load_roof;
    // goto skip_roof;

    switch(wram->wMapTileset) {
        case TILESET_JOHTO:
        case TILESET_JOHTO_MODERN:
        case TILESET_BATTLE_TOWER_OUTSIDE:
            LoadMapGroupRoof_Conv(); 
            break;
        default:
            break;
    }
// load_roof:
    // FARCALL(aLoadMapGroupRoof);

// skip_roof:
    // XOR_A_A;
    // LDH_addr_A(hTileAnimFrame);
    // RET;
    hram->hTileAnimFrame = 0;
}

void BufferScreen(void){
    BufferScreen_Conv();
    return;
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

void BufferScreen_Conv(void){
    // LD_HL(wOverworldMapAnchor);
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    const uint8_t* hl = AbsGBBankAddrToRAMAddr(MBANK(awOverworldMapBlocks), wram->wOverworldMapAnchor);
    // LD_DE(wScreenSave);
    uint8_t* de = wram->wScreenSave;
    // LD_C(SCREEN_META_HEIGHT);
    // LD_B(SCREEN_META_WIDTH);

    for(uint8_t c = 0; c < SCREEN_META_HEIGHT; ++c) {
    // row:
        // PUSH_BC;
        // PUSH_HL;

        for(uint8_t b = 0; b < SCREEN_META_WIDTH; ++b) {
        // col:
            // LD_A_hli;
            // LD_de_A;
            // INC_DE;
            *(de++) = hl[b];
            // DEC_B;
            // IF_NZ goto col;
        }
        // POP_HL;
        // LD_A_addr(wMapWidth);
        // ADD_A(6);
        // LD_C_A;
        // LD_B(0);
        // ADD_HL_BC;
        hl += wram->wMapWidth + 6;
        // POP_BC;
        // DEC_C;
        // IF_NZ goto row;
    }
    // RET;

}

void SaveScreen(void){
    // LD_HL(wOverworldMapAnchor);
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    tile_t* hl = GBToRAMAddr(wram->wOverworldMapAnchor);
    // LD_DE(wScreenSave);
    // LD_A_addr(wMapWidth);
    // ADD_A(6);
    // LDH_addr_A(hMapObjectIndex);
    hram->hMapObjectIndex = wram->wMapWidth + 6;
    // LD_A_addr(wPlayerStepDirection);
    // AND_A_A;
    tile_t* de;
    switch(wram->wPlayerStepDirection) {
        // IF_Z goto down;
        case DOWN: {
        // down:
            // LD_DE(wScreenSave);
            de = wram->wScreenSave;
            goto vertical;

        vertical:
            // LD_B(SCREEN_META_WIDTH);
            // LD_C(SCREEN_META_HEIGHT - 1);
            // JR(mSaveScreen_LoadConnection);
            return SaveScreen_LoadConnection_Conv(hl, de, SCREEN_META_WIDTH, SCREEN_META_HEIGHT - 1);
        }
        // CP_A(UP);
        // IF_Z goto up;
        case UP: {
        // up:
            // LD_DE(wScreenSave + SCREEN_META_WIDTH);
            de = wram->wScreenSave + SCREEN_META_WIDTH;
            // LDH_A_addr(hMapObjectIndex);
            // LD_C_A;
            // LD_B(0);
            // ADD_HL_BC;
            hl += hram->hMapObjectIndex;
            goto vertical;
        }
        // CP_A(LEFT);
        // IF_Z goto left;
        case LEFT: {
        // left:
            // LD_DE(wScreenSave + 1);
            de = wram->wScreenSave + 1;
            // INC_HL;
            goto horizontal;

        horizontal:
            // LD_B(SCREEN_META_WIDTH - 1);
            // LD_C(SCREEN_META_HEIGHT);
            // JR(mSaveScreen_LoadConnection);
            return SaveScreen_LoadConnection_Conv(hl, de, SCREEN_META_WIDTH - 1, SCREEN_META_HEIGHT);
        }
        // CP_A(RIGHT);
        // IF_Z goto right;
        case RIGHT: {
        // right:
            // LD_DE(wScreenSave);
            de = wram->wScreenSave;
            goto horizontal;
        }
    }
    // RET;
}

void LoadConnectionBlockData(void){
    // LD_HL(wOverworldMapAnchor);
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    uint8_t* hl = AbsGBBankAddrToRAMAddr(MBANK(awOverworldMapBlocks), wram->wOverworldMapAnchor);
    // LD_A_addr(wMapWidth);
    // ADD_A(6);
    // LDH_addr_A(hConnectionStripLength);
    hram->hConnectionStripLength = wram->wMapWidth + 6;
    // LD_DE(wScreenSave);
    // LD_B(SCREEN_META_WIDTH);
    // LD_C(SCREEN_META_HEIGHT);

    return SaveScreen_LoadConnection_Conv(hl, wram->wScreenSave, SCREEN_META_WIDTH, SCREEN_META_HEIGHT);
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

void SaveScreen_LoadConnection_Conv(uint8_t* hl, const uint8_t* de, uint8_t b, uint8_t c){
    do {
    // row:
        // PUSH_BC;
        uint8_t b2 = b;
        // PUSH_HL;
        uint8_t* hl2 = hl;
        // PUSH_DE;
        const uint8_t* de2 = de;

        do {
        // col:
            // LD_A_de;
            // INC_DE;
            // LD_hli_A;
            *(hl++) = *(de++);
            // DEC_B;
            // IF_NZ goto col;
        } while(--b2 != 0);
        // POP_DE;
        // LD_A_E;
        // ADD_A(6);
        // LD_E_A;
        // IF_NC goto okay;
        // INC_D;

    // okay:
        de = de2 + 6;
        // POP_HL;
        // LDH_A_addr(hConnectionStripLength);
        // LD_C_A;
        // LD_B(0);
        // ADD_HL_BC;
        hl = hl2 + hram->hConnectionStripLength;
        // POP_BC;
        // DEC_C;
        // IF_NZ goto row;
    } while(--c != 0);
    // RET;
}

static bool GetMovementPermissions_CheckHiNybble(uint8_t a) {
    // AND_A(0xf0);
    // CP_A(HI_NYBBLE_SIDE_WALLS);
    // RET_Z ;
    // CP_A(HI_NYBBLE_SIDE_BUOYS);
    // RET;
    return ((a & 0xf0) == HI_NYBBLE_SIDE_WALLS) || ((a & 0xf0) == HI_NYBBLE_SIDE_BUOYS);
}

static void GetMovementPermissions_Right(uint8_t a) {
    // CALL(aGetMovementPermissions_CheckHiNybble);
    // RET_NZ ;
    if(!GetMovementPermissions_CheckHiNybble(a))
        return;
    // LD_A_addr(wTileRight);
    // AND_A(0b111);
    // CP_A(COLL_LEFT_WALL & 0b111);  // COLL_LEFT_BUOY & %111
    // IF_Z goto ok_right;
    // CP_A(COLL_DOWN_LEFT_WALL & 0b111);  // COLL_DOWN_LEFT_BUOY & %111
    // IF_Z goto ok_right;
    // CP_A(COLL_UP_LEFT_WALL & 0b111);  // COLL_UP_LEFT_BUOY & %111
    // RET_NZ ;
    if((wram->wTileRight & 0b111) == (COLL_LEFT_WALL & 0b111)
    || (wram->wTileRight & 0b111) == (COLL_DOWN_LEFT_WALL & 0b111)
    || (wram->wTileRight & 0b111) == (COLL_UP_LEFT_WALL & 0b111)) {
    // ok_right:
        // LD_A_addr(wTilePermissions);
        // OR_A(FACE_RIGHT);
        // LD_addr_A(wTilePermissions);
        wram->wTilePermissions |= FACE_RIGHT;
        // RET;
        return;
    }
}

static void GetMovementPermissions_Left(uint8_t a) {
    // CALL(aGetMovementPermissions_CheckHiNybble);
    // RET_NZ ;
    if(!GetMovementPermissions_CheckHiNybble(a))
        return;
    // LD_A_addr(wTileLeft);
    // AND_A(0b111);
    // CP_A(COLL_RIGHT_WALL & 0b111);  // COLL_RIGHT_BUOY & %111
    // IF_Z goto ok_left;
    // CP_A(COLL_DOWN_RIGHT_WALL & 0b111);  // COLL_DOWN_RIGHT_BUOY & %111
    // IF_Z goto ok_left;
    // CP_A(COLL_UP_RIGHT_WALL & 0b111);  // COLL_UP_RIGHT_BUOY & %111
    // RET_NZ ;
    if((wram->wTileLeft & 0b111) == (COLL_RIGHT_WALL & 0b111)
    || (wram->wTileLeft & 0b111) == (COLL_DOWN_RIGHT_WALL & 0b111)
    || (wram->wTileLeft & 0b111) == (COLL_UP_RIGHT_WALL & 0b111)) {
    // ok_left:
        // LD_A_addr(wTilePermissions);
        // OR_A(FACE_LEFT);
        // LD_addr_A(wTilePermissions);
        wram->wTilePermissions |= FACE_LEFT;
        // RET;
        return;
    }
}

static void GetMovementPermissions_LeftRight(void) {
    // LD_A_addr(wPlayerStandingMapX);
    // LD_D_A;
    uint8_t x = wram->wPlayerStruct.nextMapX;
    // LD_A_addr(wPlayerStandingMapY);
    // LD_E_A;
    uint8_t y = wram->wPlayerStruct.nextMapY;

    // PUSH_DE;
    // DEC_D;
    // CALL(aGetCoordTile);
    // LD_addr_A(wTileLeft);
    wram->wTileLeft = GetCoordTile_Conv(x - 1, y);
    // CALL(aGetMovementPermissions_Left);
    GetMovementPermissions_Left(wram->wTileLeft);

    // POP_DE;
    // INC_D;
    // CALL(aGetCoordTile);
    // LD_addr_A(wTileRight);
    wram->wTileRight = GetCoordTile_Conv(x + 1, y);
    // CALL(aGetMovementPermissions_Right);
    GetMovementPermissions_Right(wram->wTileRight);
    // RET;
}

static void GetMovementPermissions_Down(uint8_t a) {
    // CALL(aGetMovementPermissions_CheckHiNybble);
    // RET_NZ ;
    if(!GetMovementPermissions_CheckHiNybble(a))
        return;
    // LD_A_addr(wTileDown);
    // AND_A(0b111);
    // CP_A(COLL_UP_WALL & 0b111);  // COLL_UP_BUOY & %111
    // IF_Z goto ok_down;
    // CP_A(COLL_UP_RIGHT_WALL & 0b111);  // COLL_UP_RIGHT_BUOY & %111
    // IF_Z goto ok_down;
    // CP_A(COLL_UP_LEFT_WALL & 0b111);  // COLL_UP_LEFT_BUOY & %111
    // RET_NZ ;
    if((wram->wTileDown & 0b111) == (COLL_UP_WALL & 0b111)
    || (wram->wTileDown & 0b111) == (COLL_UP_RIGHT_WALL & 0b111)
    || (wram->wTileDown & 0b111) == (COLL_UP_LEFT_WALL & 0b111)) {
    // ok_down:
        // LD_A_addr(wTilePermissions);
        // OR_A(FACE_DOWN);
        // LD_addr_A(wTilePermissions);
        wram->wTilePermissions |= FACE_DOWN;
        // RET;
        return;
    }
}

static void GetMovementPermissions_Up(uint8_t a) {
    // CALL(aGetMovementPermissions_CheckHiNybble);
    // RET_NZ ;
    if(!GetMovementPermissions_CheckHiNybble(a))
        return;
    // LD_A_addr(wTileUp);
    // AND_A(0b111);
    // CP_A(COLL_DOWN_WALL & 0b111);  // COLL_DOWN_BUOY & %111
    // IF_Z goto ok_up;
    // CP_A(COLL_DOWN_RIGHT_WALL & 0b111);  // COLL_DOWN_RIGHT_BUOY & %111
    // IF_Z goto ok_up;
    // CP_A(COLL_DOWN_LEFT_WALL & 0b111);  // COLL_DOWN_LEFT_BUOY & %111
    // RET_NZ ;
    if((wram->wTileUp & 0b111) == (COLL_DOWN_WALL & 0b111)
    || (wram->wTileUp & 0b111) == (COLL_DOWN_RIGHT_WALL & 0b111)
    || (wram->wTileUp & 0b111) == (COLL_DOWN_LEFT_WALL & 0b111)) {
    // ok_up:
        // LD_A_addr(wTilePermissions);
        // OR_A(FACE_UP);
        // LD_addr_A(wTilePermissions);
        wram->wTilePermissions |= FACE_UP;
        // RET;
        return;
    }
}

static void GetMovementPermissions_UpDown(void) {
    // LD_A_addr(wPlayerStandingMapX);
    // LD_D_A;
    uint8_t x = wram->wPlayerStruct.nextMapX;
    // LD_A_addr(wPlayerStandingMapY);
    // LD_E_A;
    uint8_t y = wram->wPlayerStruct.nextMapY;

    // PUSH_DE;
    // INC_E;
    // CALL(aGetCoordTile);
    // LD_addr_A(wTileDown);
    wram->wTileDown = GetCoordTile_Conv(x, y + 1);
    // CALL(aGetMovementPermissions_Down);
    GetMovementPermissions_Down(wram->wTileDown);

    // POP_DE;
    // DEC_E;
    // CALL(aGetCoordTile);
    // LD_addr_A(wTileUp);
    wram->wTileUp = GetCoordTile_Conv(x, y - 1);
    // CALL(aGetMovementPermissions_Up);
    GetMovementPermissions_Up(wram->wTileUp);
    // RET;
}

void GetMovementPermissions(void){
    static const uint8_t MovementPermissionsData[] = {
        DOWN_MASK,
        UP_MASK,
        LEFT_MASK,
        RIGHT_MASK,
        DOWN_MASK | RIGHT_MASK,
        UP_MASK | RIGHT_MASK,
        DOWN_MASK | LEFT_MASK,
        UP_MASK | LEFT_MASK,
    };
    // XOR_A_A;
    // LD_addr_A(wTilePermissions);
    wram->wTilePermissions = 0;
    // CALL(aGetMovementPermissions_LeftRight);
    GetMovementPermissions_LeftRight();
    // CALL(aGetMovementPermissions_UpDown);
    GetMovementPermissions_UpDown();
//  get coords of current tile
    // LD_A_addr(wPlayerStandingMapX);
    // LD_D_A;
    uint8_t x = wram->wPlayerStruct.nextMapX;
    // LD_A_addr(wPlayerStandingMapY);
    // LD_E_A;
    uint8_t y = wram->wPlayerStruct.nextMapY;
    // CALL(aGetCoordTile);
    uint8_t tile = GetCoordTile_Conv(x, y);
    // LD_addr_A(wPlayerStandingTile);
    wram->wPlayerStruct.nextTile = tile;
    // CALL(aGetMovementPermissions_CheckHiNybble);
    // RET_NZ ;
    if(!GetMovementPermissions_CheckHiNybble(tile))
        return;

    // LD_A_addr(wPlayerStandingTile);
    // AND_A(7);
    // LD_HL(mGetMovementPermissions_MovementPermissionsData);
    // ADD_A_L;
    // LD_L_A;
    // LD_A(0);
    // ADC_A_H;
    // LD_H_A;
    // LD_A_hl;
    // LD_HL(wTilePermissions);
    // OR_A_hl;
    // LD_hl_A;
    wram->wTilePermissions |= MovementPermissionsData[wram->wPlayerStruct.nextTile & 7];
    // RET;
    return;
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

//  Return map coordinates in (d, e) and tile id in a
//  of the tile the player is facing.
struct CoordsTileId GetFacingTileCoord_Conv(void){
    const struct {
        int8_t x;
        int8_t y;
        uint8_t* const ptr;
    } Directions[] = {
    //   x,  y
        {0, 1, wram_ptr(wTileDown)},
        {0, -1, wram_ptr(wTileUp)},
        {-1, 0, wram_ptr(wTileLeft)},
        {1, 0, wram_ptr(wTileRight)},
    };
    // LD_A_addr(wPlayerDirection);
    // AND_A(0b1100);
    // SRL_A;
    // SRL_A;
    // LD_L_A;
    // LD_H(0);
    // ADD_HL_HL;
    // ADD_HL_HL;
    // LD_DE(mGetFacingTileCoord_Directions);
    // ADD_HL_DE;
    uint8_t idx = ((wram->wPlayerStruct.facing >> 2) & 3);

    struct CoordsTileId res;

    // LD_D_hl;
    // INC_HL;
    // LD_E_hl;
    // INC_HL;
    res.x = Directions[idx].x + wram->wPlayerStruct.mapX;
    res.y = Directions[idx].y + wram->wPlayerStruct.mapY;

    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;

    // LD_A_addr(wPlayerStandingMapX);
    // ADD_A_D;
    // LD_D_A;
    // LD_A_addr(wPlayerStandingMapY);
    // ADD_A_E;
    // LD_E_A;
    // LD_A_hl;
    res.tileId = *Directions[idx].ptr;
    // RET;
    return res;
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

//  Get the collision byte for tile d, e
uint8_t GetCoordTile_Conv(uint8_t d, uint8_t e){
    // CALL(aGetBlockLocation);
    const uint8_t* hl = GetBlockLocation_Conv(d, e);
    // LD_A_hl;
    uint8_t a = *hl;
    // AND_A_A;
    // IF_Z goto nope;
    if(a == 0)
        return 0xff;
    // LD_L_A;
    // LD_H(0);
    // ADD_HL_HL;
    // ADD_HL_HL;
    // LD_A_addr(wTilesetCollisionAddress);
    // LD_C_A;
    // LD_A_addr(wTilesetCollisionAddress + 1);
    // LD_B_A;
    // ADD_HL_BC;
    // hl = AbsGBBankAddrToRAMAddr(wram->wTilesetCollisionBank, wram->wTilesetCollisionAddress + (a << 2));
    hl = gTilesetPointer->coll + (a << 2);
    // RR_D;
    // IF_NC goto nocarry;
    // INC_HL;
    if(d & 1) {
        hl++;
    }


// nocarry:
    // RR_E;
    // IF_NC goto nocarry2;
    if(e & 1) {
        // INC_HL;
        // INC_HL;
        hl += 2;
    }

// nocarry2:
    // LD_A_addr(wTilesetCollisionBank);
    // CALL(aGetFarByte);
    return *hl;
    // RET;


// nope:
    // LD_A(-1);
    // RET;
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

uint8_t* GetBlockLocation_Conv(uint8_t d, uint8_t e){
    // LD_A_addr(wMapWidth);
    // ADD_A(6);
    // LD_C_A;
    // LD_B(0);
    uint16_t bc = wram->wMapWidth + 6;
    // LD_HL(wOverworldMapBlocks + 1);
    // ADD_HL_BC;
    uint8_t* hl = wram->wOverworldMapBlocks + 1 + bc + (bc * (e >> 1)) + (d >> 1);
    // LD_A_E;
    // SRL_A;
    // IF_Z goto nope;
    // AND_A_A;
    // uint8_t a = e >> 1;
    // while(a != 0) {
    // // loop:
    //     // SRL_A;
    //     // IF_NC goto ok;
    //     if((a & 1)) {
    //         // ADD_HL_BC;
    //         hl += bc;
    //     }
    //     a >>= 1;

    // // ok:
    //     // SLA_C;
    //     // RL_B;
    //     bc <<= 1;
    //     // AND_A_A;
    //     // IF_NZ goto loop;
    // }


// nope:
    // LD_C_D;
    // SRL_C;
    // LD_B(0);
    // ADD_HL_BC;
    // hl += d >> 1;
    // RET;
    return hl;
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

bool CheckFacingBGEvent_Conv(void){
    // CALL(aGetFacingTileCoord);
    struct CoordsTileId facingTileCoord = GetFacingTileCoord_Conv();
//  Load facing into b.
    // LD_B_A;
//  Convert the coordinates at de to within-boundaries coordinates.
    // LD_A_D;
    // SUB_A(4);
    // LD_D_A;
    uint8_t d = facingTileCoord.x - 4;
    // LD_A_E;
    // SUB_A(4);
    // LD_E_A;
    uint8_t e = facingTileCoord.y - 4;
//  If there are no BG events, we don't need to be here.
    // LD_A_addr(wCurMapBGEventCount);
    // AND_A_A;
    // RET_Z ;
    if(gCurMapBGEventCount == 0)
        return false;

    // LD_C_A;
    // LDH_A_addr(hROMBank);
    // PUSH_AF;
    // CALL(aSwitchToMapScriptsBank);
    // CALL(aCheckIfFacingTileCoordIsBGEvent);
    return CheckIfFacingTileCoordIsBGEvent_Conv(gCurMapBGEventCount, d, e);
    // POP_HL;
    // LD_A_H;
    // RST(aBankswitch);
    // RET;
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

//  Checks to see if you are facing a BG event.  If so, copies it into wCurBGEvent and sets carry.
bool CheckIfFacingTileCoordIsBGEvent_Conv(uint8_t c, uint8_t d, uint8_t e){
    // LD_HL(wCurMapBGEventsPointer);
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    const struct BGEvent* hl = gCurMapBGEventsPointer;

    do {
    // loop:
        // PUSH_HL;
        // LD_A_hli;
        // CP_A_E;
        // IF_NZ goto next;
        // LD_A_hli;
        // CP_A_D;
        // IF_NZ goto next;
        if(hl->y != e || hl->x != d)
            continue;
        // goto copysign;
        else {
        // copysign:
            // POP_HL;
            // LD_DE(wCurBGEvent);
            // LD_BC(BG_EVENT_SIZE);
            // CALL(aCopyBytes);
            CopyBytes(&gCurBGEvent, hl, sizeof(*hl));
            // SCF;
            // RET;
            return true;
        }


    // next:
        // POP_HL;
        // LD_A(BG_EVENT_SIZE);
        // ADD_A_L;
        // LD_L_A;
        // IF_NC goto nocarry;
        // INC_H;

    // nocarry:
        // DEC_C;
        // IF_NZ goto loop;
    } while(hl++, --c != 0);
    // XOR_A_A;
    // RET;
    return false;
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

//  Checks to see if you are standing on a coord event.  If yes, copies the event to wCurCoordEvent and sets carry.
const struct CoordEvent* CheckCurrentMapCoordEvents_CoordEventCheck(void) {
    // LD_HL(wCurMapCoordEventsPointer);
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
//  Load the active scene ID into b
    // CALL(aCheckScenes);
    // LD_B_A;
    uint8_t b = CheckScenes_Conv();
//  Load your current coordinates into de.  This will be used to check if your position is in the coord event table for the current map.
    // LD_A_addr(wPlayerStandingMapX);
    // SUB_A(4);
    // LD_D_A;
    uint8_t x = wram->wPlayerStruct.nextMapX - 4;
    // LD_A_addr(wPlayerStandingMapY);
    // SUB_A(4);
    // LD_E_A;
    uint8_t y = wram->wPlayerStruct.nextMapY - 4;

    for(uint32_t i = 0; i < gCurMapCoordEventCount; ++i) {
    // loop:
        // PUSH_HL;
        // LD_A_hli;
        // CP_A_B;
        // IF_Z goto got_id;
        // CP_A(-1);
        // IF_NZ goto next;
        if(gCurMapCoordEventsPointer[i].sceneId != b
        && gCurMapCoordEventsPointer[i].sceneId != 0xff)
            continue;


    // got_id:
        // LD_A_hli;
        // CP_A_E;
        // IF_NZ goto next;
        // LD_A_hli;
        // CP_A_D;
        // IF_NZ goto next;
        // goto copy_coord_event;
        if(gCurMapCoordEventsPointer[i].x == x
        && gCurMapCoordEventsPointer[i].y == y) {
        // copy_coord_event:
            // POP_HL;
            // LD_DE(wCurCoordEvent);
            // LD_BC(COORD_EVENT_SIZE);
            // CALL(aCopyBytes);
            // SCF;
            // RET;
            return gCurMapCoordEventsPointer + i;
        }


    // next:
        // POP_HL;
        // LD_A(COORD_EVENT_SIZE);
        // ADD_A_L;
        // LD_L_A;
        // IF_NC goto nocarry;
        // INC_H;


    // nocarry:
        // DEC_C;
        // IF_NZ goto loop;
    }
    // XOR_A_A;
    // RET;
    return NULL;
}

const struct CoordEvent* CheckCurrentMapCoordEvents_Conv(void){
//  If there are no coord events, we don't need to be here.
    // LD_A_addr(wCurMapCoordEventCount);
    // AND_A_A;
    // RET_Z ;
    if(gCurMapCoordEventCount == 0)
        return NULL;
//  Copy the coord event count into c.
    // LD_C_A;
    // LDH_A_addr(hROMBank);
    // PUSH_AF;
    // CALL(aSwitchToMapScriptsBank);
    // CALL(aCheckCurrentMapCoordEvents_CoordEventCheck);
    // POP_HL;
    // LD_A_H;
    // RST(aBankswitch);
    // RET;
    return CheckCurrentMapCoordEvents_CoordEventCheck();
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

void FadeToMenu_Conv(void){
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = 0;
    // CALL(aLoadStandardMenuHeader);
    LoadStandardMenuHeader_Conv();
    // FARCALL(aFadeOutPalettes);
    FadeOutPalettes();
    // CALL(aClearSprites);
    ClearSprites();
    // CALL(aDisableSpriteUpdates);
    DisableSpriteUpdates_Conv();
    // RET;
}

void CloseSubmenu(void){
    CALL(aClearBGPalettes);
    CALL(aReloadTilesetAndPalettes);
    CALL(aUpdateSprites);
    CALL(aCall_ExitMenu);
    CALL(aGSReloadPalettes);
    JR(mFinishExitMenu);

}

void CloseSubmenu_Conv(void){
    // CALL(aClearBGPalettes);
    ClearBGPalettes_Conv();
    // CALL(aReloadTilesetAndPalettes);
    ReloadTilesetAndPalettes_Conv();
    // CALL(aUpdateSprites);
    UpdateSprites_Conv();
    // CALL(aCall_ExitMenu);
    ExitMenu_Conv2();
    // CALL(aGSReloadPalettes);
    GSReloadPalettes();
    // JR(mFinishExitMenu);
    return FinishExitMenu_Conv();
}

void ExitAllMenus(void){
    CALL(aClearBGPalettes);
    CALL(aCall_ExitMenu);
    CALL(aReloadTilesetAndPalettes);
    CALL(aUpdateSprites);
    CALL(aGSReloadPalettes);
    return FinishExitMenu();
}

void ExitAllMenus_Conv(void){
    // CALL(aClearBGPalettes);
    ClearBGPalettes_Conv();
    // CALL(aCall_ExitMenu);
    ExitMenu_Conv2();
    // CALL(aReloadTilesetAndPalettes);
    ReloadTilesetAndPalettes_Conv();
    // CALL(aUpdateSprites);
    UpdateSprites_Conv();
    // CALL(aGSReloadPalettes);
    GSReloadPalettes();
    return FinishExitMenu_Conv();
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

void FinishExitMenu_Conv(void){
    // LD_B(SCGB_MAPPALS);
    // CALL(aGetSGBLayout);
    GetSGBLayout_Conv(SCGB_MAPPALS);
    // FARCALL(aLoadOW_BGPal7);
    LoadOW_BGPal7();
    // CALL(aWaitBGMap2);
    WaitBGMap2_Conv();
    // FARCALL(aFadeInPalettes);
    FadeInPalettes();
    // CALL(aEnableSpriteUpdates);
    EnableSpriteUpdates_Conv();
    // RET;
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

void ReturnToMapWithSpeechTextbox_Conv(void){
    // PUSH_AF;
    // LD_A(0x1);
    // LD_addr_A(wSpriteUpdatesEnabled);
    wram->wSpriteUpdatesEnabled = 0x1;
    // CALL(aClearBGPalettes);
    ClearBGPalettes_Conv();
    // CALL(aClearSprites);
    ClearSprites();
    // CALL(aReloadTilesetAndPalettes);
    ReloadTilesetAndPalettes_Conv();
    // hlcoord(0, 12, wTilemap);
    // LD_BC((4 << 8) | 18);
    // CALL(aTextbox);
    Textbox_Conv2(coord(0, 12, wram->wTilemap), 4, 18);
    // LD_HL(wVramState);
    // SET_hl(0);
    bit_set(wram->wVramState, 0);
    // CALL(aUpdateSprites);
    UpdateSprites_Conv();
    // CALL(aWaitBGMap2);
    WaitBGMap2_Conv();
    // LD_B(SCGB_MAPPALS);
    // CALL(aGetSGBLayout);
    GetSGBLayout_Conv(SCGB_MAPPALS);
    // FARCALL(aLoadOW_BGPal7);
    LoadOW_BGPal7();
    // CALL(aUpdateTimePals);
    UpdateTimePals();
    // CALL(aDelayFrame);
    DelayFrame();
    // LD_A(0x1);
    // LDH_addr_A(hMapAnims);
    hram->hMapAnims = 0x1;
    // POP_AF;
    // RET;
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

void ReloadTilesetAndPalettes_Conv(void){
    // CALL(aDisableLCD);
    DisableLCD();
    // CALL(aClearSprites);
    ClearSprites();
    // FARCALL(aRefreshSprites);
    RefreshSprites_Conv();
    // CALL(aLoadStandardFont);
    LoadStandardFont_Conv();
    // CALL(aLoadFontsExtra);
    LoadFontsExtra_Conv();
    // LDH_A_addr(hROMBank);
    // PUSH_AF;
    // LD_A_addr(wMapGroup);
    // LD_B_A;
    // LD_A_addr(wMapNumber);
    // LD_C_A;
    // CALL(aSwitchToAnyMapAttributesBank);
    // FARCALL(aUpdateTimeOfDayPal);
    UpdateTimeOfDayPal();
    // CALL(aOverworldTextModeSwitch);
    OverworldTextModeSwitch_Conv();
    // CALL(aLoadTilesetGFX);
    LoadTilesetGFX_Conv();
    // LD_A(9);
    // CALL(aSkipMusic);
    SkipMusic(3);
    // POP_AF;
    // RST(aBankswitch);

    // CALL(aEnableLCD);
    EnableLCD();
    // RET;
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

const struct MapHeader* GetMapPointer_Conv2(void){
    return GetAnyMapPointer_Conv2(wram->wMapGroup, wram->wMapNumber);
}

//  inputs:
//  b = map group, c = map number
//  outputs:
//  hl points to the map within its group
const struct MapHeader* GetAnyMapPointer_Conv2(uint8_t group, uint8_t map){
//  Prior to calling this function, you must have switched banks so that
//  MapGroupPointers is visible.
    //PUSH_BC;  // save map number for later

// get pointer to map group

    //DEC_B;
    //LD_C_B;
    //LD_B(0);
    //LD_HL(mMapGroupPointers);
    //ADD_HL_BC;
    //ADD_HL_BC;
    const struct MapHeader* hl = MapGroupPointers[group - 1];

    //LD_A_hli;
    //LD_H_hl;
    //LD_L_A;
    //POP_BC;  // restore map number

// find the cth map within the group
    //DEC_C;
    //LD_B(0);
    //LD_A(MAP_LENGTH);
    //CALL(aAddNTimes);
    return hl + (map - 1);
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

    CopyBytes_GB(wMapPartial, GetMapPointer_Conv(), (wMapPartialEnd - wMapPartial));

    bank_pop;
}

//  Copy map data bank, tileset, environment, and map data address
//  from the current map's entry within its group.
void CopyMapPartial_Conv2(void){
    const struct MapHeader* mp = GetMapPointer_Conv2();
    wram->wMapTileset = mp->tileset;
    wram->wEnvironment = mp->environment;
    gMapAttrPointer = mp->attr;
// This is for GB Save compatability.
    uint32_t gb_attr_ptr = GetGBMapAttributePointer(wram->wMapGroup, wram->wMapNumber);
    wram->wMapAttributesBank = BANK(gb_attr_ptr);
    wram->wMapAttributesPointer = (gb_attr_ptr < 0x4000)? gb_attr_ptr : (gb_attr_ptr & 0x3fff) | 0x4000;
}

void SwitchToMapScriptsBank(void){
    LD_A_addr(wMapScriptsBank);
    RST(aBankswitch);
    RET;

}

void SwitchToMapScriptsBank_Conv(void){
    Bankswitch(wram->wMapScriptsBank);
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

const struct MapAttr* GetMapAttributesPointer_Conv2(void){
//  returns the current map's data pointer in hl.
    // PUSH_BC;
    // PUSH_DE;
    // LD_DE(MAP_MAPATTRIBUTES);
    // CALL(aGetMapField);
    // LD_L_C;
    // LD_H_B;
    // POP_DE;
    // POP_BC;
    // RET;
    return GetMapPointer_Conv2()->attr;
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

uint8_t GetMapEnvironment_Conv(void){
    // PUSH_HL;
    // PUSH_DE;
    // PUSH_BC;
    // LD_DE(MAP_ENVIRONMENT);
    // CALL(aGetMapField);
    // LD_A_C;
    // POP_BC;
    // POP_DE;
    // POP_HL;
    // RET;
    return GetMapField_Conv(MAP_ENVIRONMENT);
}

uint8_t GetMapEnvironment_Conv2(void){
    // PUSH_HL;
    // PUSH_DE;
    // PUSH_BC;
    // LD_DE(MAP_ENVIRONMENT);
    // CALL(aGetMapField);
    // LD_A_C;
    // POP_BC;
    // POP_DE;
    // POP_HL;
    // RET;
    return GetMapPointer_Conv2()->environment;
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

uint8_t GetAnyMapEnvironment_Conv2(uint8_t group, uint8_t map){
    return GetAnyMapPointer_Conv2(group, map)->environment;
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

uint8_t GetAnyMapTileset_Conv2(uint8_t group, uint8_t map){
    return GetAnyMapPointer_Conv2(group, map)->tileset;
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

//  given a map group/id in bc, return its location on the Pokégear map.
uint8_t GetWorldMapLocation_Conv2(uint8_t group, uint8_t map){
    return GetAnyMapPointer_Conv2(group, map)->location;
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

uint16_t GetMapMusic_Conv2(void){
    uint16_t music = GetMapPointer_Conv2()->music;
    if(music == MUSIC_MAHOGANY_MART)
    {
        if(!bit_test(wram->wStatusFlags2, STATUSFLAGS2_ROCKETS_IN_MAHOGANY_F))
        {
            return MUSIC_CHERRYGROVE_CITY;
        }
        return MUSIC_ROCKET_HIDEOUT;
    }
    if(bit_test(music, RADIO_TOWER_MUSIC_F))
    {
        if(!bit_test(wram->wStatusFlags2, STATUSFLAGS2_ROCKETS_IN_RADIO_TOWER_F))
        {
            return music & (RADIO_TOWER_MUSIC - 1);
        }
        return MUSIC_ROCKET_OVERTURE;
    }
    if(music == MUSIC_POKEMON_CENTER)
    {
        // Only play the mobile center music in the first and second floor of the PCC and only when the adapter has been activated.
        if(((wram->wMapNumber == MAP_GOLDENROD_POKECENTER_1F && wram->wMapGroup == GROUP_GOLDENROD_POKECENTER_1F)
            || ((wram->wMapNumber == MAP_POKECENTER_2F && wram->wMapGroup == GROUP_POKECENTER_2F) 
                && (wram->wBackupMapNumber == MAP_GOLDENROD_POKECENTER_1F && wram->wBackupMapGroup == GROUP_GOLDENROD_POKECENTER_1F)))
        && Mobile_AlwaysReturnNotCarry().flag) {
            return MUSIC_MOBILE_CENTER;
        }
        return MUSIC_POKEMON_CENTER;
    }
    return music;
}

void GetMapTimeOfDay(void){
    CALL(aGetPhoneServiceTimeOfDayByte);
    AND_A(0xf);
    RET;

}

uint8_t GetMapTimeOfDay_Conv(void){
    // return GetPhoneServiceTimeOfDayByte_Conv() & 0xF;
    return GetMapPointer_Conv2()->timeOfDay;
}

void GetMapPhoneService(void){
    CALL(aGetPhoneServiceTimeOfDayByte);
    AND_A(0xf0);
    SWAP_A;
    RET;

}

// Returns whether the phone service is available
// 0: Phone service available
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
    return (uint8_t)(GetMapPointer_Conv2()->phoneService & 0xFF);
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

uint8_t GetFishingGroup_Conv2(void){
    return GetMapPointer_Conv2()->fishingGroup;
}

void LoadMapTileset(void){
    return LoadMapTileset_Conv2();
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
    // uint16_t hl = AddNTimes_Conv(mTilesets, TILESET_LENGTH, wram->wMapTileset);
    // FarCopyBytes_Conv(wTilesetBank, BANK(aTilesets), mTilesets + (wram->wMapTileset * TILESET_LENGTH), TILESET_LENGTH);
    wram->wTilesetBank = BANK(GBTilesets[wram->wMapTileset].gfx_ptr);
    wram->wTilesetAddress = (GBTilesets[wram->wMapTileset].gfx_ptr & 0x3fff) | 0x4000;
    wram->wTilesetBlocksBank = BANK(GBTilesets[wram->wMapTileset].meta_ptr);
    wram->wTilesetBlocksAddress = (GBTilesets[wram->wMapTileset].meta_ptr & 0x3fff) | 0x4000;
    wram->wTilesetCollisionBank = BANK(GBTilesets[wram->wMapTileset].coll_ptr);
    wram->wTilesetCollisionAddress = (GBTilesets[wram->wMapTileset].coll_ptr & 0x3fff) | 0x4000;
    wram->wTilesetAnim = (GBTilesets[wram->wMapTileset].anim_ptr & 0x3fff) | 0x4000;
    wram->wTilesetPalettes = (GBTilesets[wram->wMapTileset].pal_ptr & 0x3fff) | 0x4000;
}

void LoadMapTileset_Conv2(void){
    LoadMapTileset_Conv();
    gTilesetPointer = &Tilesets[wram->wMapTileset];
    if(gTilesetBlocks.ptr != NULL)
        FreeAsset(gTilesetBlocks);
    gTilesetBlocks = LoadAsset(gTilesetPointer->metaPath);
    gTilesetAnim = gTilesetPointer->anim;
}

void DummyEndPredef(void){
//  Unused function at the end of PredefPointers.
    for(int rept = 0; rept < 16; rept++){
    NOP;
    }
    RET;

}
