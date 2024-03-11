#include "../../constants.h"
#include "tile_events.h"

void CheckWarpCollision(void){
//  Is this tile a warp?
    LD_A_addr(wPlayerStandingTile);
    CP_A(COLL_PIT);
    IF_Z goto warp;
    CP_A(COLL_PIT_68);
    IF_Z goto warp;
    AND_A(0xf0);
    CP_A(HI_NYBBLE_WARPS);
    IF_Z goto warp;
    AND_A_A;
    RET;


warp:
    SCF;
    RET;

}

//  Is this tile a warp?
bool CheckWarpCollision_Conv(void){
    // LD_A_addr(wPlayerStandingTile);
    // CP_A(COLL_PIT);
    // IF_Z goto warp;
    // CP_A(COLL_PIT_68);
    // IF_Z goto warp;
    // AND_A(0xf0);
    // CP_A(HI_NYBBLE_WARPS);
    // IF_Z goto warp;
    const uint8_t tile = wram->wPlayerStruct.nextTile;
    if(tile == COLL_PIT || tile == COLL_PIT_68 || ((tile & 0xf0) == HI_NYBBLE_WARPS))
        return true;
    // AND_A_A;
    // RET;
    return false;

// warp:
    // SCF;
    // RET;
}

void CheckDirectionalWarp(void){
//  If this is a directional warp, clear carry (press the designated button to warp).
//  Else, set carry (immediate warp).
    LD_A_addr(wPlayerStandingTile);
    CP_A(COLL_WARP_CARPET_DOWN);
    IF_Z goto directional;
    CP_A(COLL_WARP_CARPET_LEFT);
    IF_Z goto directional;
    CP_A(COLL_WARP_CARPET_UP);
    IF_Z goto directional;
    CP_A(COLL_WARP_CARPET_RIGHT);
    IF_Z goto directional;
    SCF;
    RET;


directional:
    XOR_A_A;
    RET;

}

//  If this is a directional warp, clear carry (true) (press the designated button to warp).
//  Else, set carry (false) (immediate warp).
bool CheckDirectionalWarp_Conv(void){
    // LD_A_addr(wPlayerStandingTile);
    const uint8_t tile = wram->wPlayerStruct.nextTile;
    // CP_A(COLL_WARP_CARPET_DOWN);
    // IF_Z goto directional;
    // CP_A(COLL_WARP_CARPET_LEFT);
    // IF_Z goto directional;
    // CP_A(COLL_WARP_CARPET_UP);
    // IF_Z goto directional;
    // CP_A(COLL_WARP_CARPET_RIGHT);
    // IF_Z goto directional;
    if(tile == COLL_WARP_CARPET_DOWN || tile == COLL_WARP_CARPET_LEFT || tile == COLL_WARP_CARPET_UP || tile == COLL_WARP_CARPET_RIGHT)
        return true;
    // SCF;
    // RET;
    return false;

// directional:
    // XOR_A_A;
    // RET;
}

void CheckWarpFacingDown(void){
    LD_DE(1);
    LD_HL(mCheckWarpFacingDown_blocks);
    LD_A_addr(wPlayerStandingTile);
    CALL(aIsInArray);
    RET;


blocks:
    //db ['COLL_DOOR'];
    //db ['COLL_DOOR_79'];
    //db ['COLL_STAIRCASE'];
    //db ['COLL_STAIRCASE_73'];
    //db ['COLL_CAVE'];
    //db ['COLL_CAVE_74'];
    //db ['COLL_WARP_PANEL'];
    //db ['COLL_DOOR_75'];
    //db ['COLL_DOOR_7D'];
    //db ['-1'];

    return CheckGrassCollision();
}

bool CheckWarpFacingDown_Conv(void){
    static const uint8_t blocks[] = {
        COLL_DOOR,
        COLL_DOOR_79,
        COLL_STAIRCASE,
        COLL_STAIRCASE_73,
        COLL_CAVE,
        COLL_CAVE_74,
        COLL_WARP_PANEL,
        COLL_DOOR_75,
        COLL_DOOR_7D,
    };

    // LD_DE(1);
    // LD_HL(mCheckWarpFacingDown_blocks);
    // LD_A_addr(wPlayerStandingTile);
    // CALL(aIsInArray);
    // RET;

    const uint8_t tile = wram->wPlayerStruct.nextTile;
    for(size_t i = 0; i < sizeof(blocks); ++i) {
        if(tile == blocks[i])
            return true;
    }
    return false;
}

void CheckGrassCollision(void){
    LD_A_addr(wPlayerStandingTile);
    LD_HL(mCheckGrassCollision_blocks);
    LD_DE(1);
    CALL(aIsInArray);
    RET;


blocks:
    //db ['COLL_CUT_08'];
    //db ['COLL_TALL_GRASS'];
    //db ['COLL_LONG_GRASS'];
    //db ['COLL_CUT_28'];
    //db ['COLL_WATER'];
    //db ['COLL_GRASS_48'];
    //db ['COLL_GRASS_49'];
    //db ['COLL_GRASS_4A'];
    //db ['COLL_GRASS_4B'];
    //db ['COLL_GRASS_4C'];
    //db ['-1'];

    return CheckCutCollision();
}

bool CheckGrassCollision_Conv(void){
    static const uint8_t blocks[] = {
        COLL_CUT_08,
        COLL_TALL_GRASS,
        COLL_LONG_GRASS,
        COLL_CUT_28,
        COLL_WATER,
        COLL_GRASS_48,
        COLL_GRASS_49,
        COLL_GRASS_4A,
        COLL_GRASS_4B,
        COLL_GRASS_4C
    };
    // LD_A_addr(wPlayerStandingTile);
    // LD_HL(mCheckGrassCollision_blocks);
    // LD_DE(1);
    // CALL(aIsInArray);
    // RET;
    const uint8_t tile = wram->wPlayerStruct.nextTile;
    for(size_t i = 0; i < sizeof(blocks); ++i) {
        if(tile == blocks[i])
            return true;
    }
    return false;
}

void CheckCutCollision(void){
    LD_A_C;
    LD_HL(mCheckCutCollision_blocks);
    LD_DE(1);
    CALL(aIsInArray);
    RET;


blocks:
    //db ['COLL_CUT_TREE'];
    //db ['COLL_CUT_TREE_1A'];
    //db ['COLL_TALL_GRASS_10'];
    //db ['COLL_TALL_GRASS'];
    //db ['COLL_LONG_GRASS'];
    //db ['COLL_LONG_GRASS_1C'];
    //db ['-1'];

    return GetWarpSFX();
}

bool CheckCutCollision_Conv(uint8_t tile){
    static const uint8_t blocks[] = {
        COLL_CUT_TREE,
        COLL_CUT_TREE_1A,
        COLL_TALL_GRASS_10,
        COLL_TALL_GRASS,
        COLL_LONG_GRASS,
        COLL_LONG_GRASS_1C
    };
    // LD_A_C;
    // LD_HL(mCheckCutCollision_blocks);
    // LD_DE(1);
    // CALL(aIsInArray);
    // RET;
    for(size_t i = 0; i < sizeof(blocks); ++i) {
        if(tile == blocks[i])
            return true;
    }
    return false;
}

void GetWarpSFX(void){
    LD_A_addr(wPlayerStandingTile);
    LD_DE(SFX_ENTER_DOOR);
    CP_A(COLL_DOOR);
    RET_Z ;
    LD_DE(SFX_WARP_TO);
    CP_A(COLL_WARP_PANEL);
    RET_Z ;
    LD_DE(SFX_EXIT_BUILDING);
    RET;

}

uint16_t GetWarpSFX_Conv(void) {
    // LD_A_addr(wPlayerStandingTile);
    const uint8_t tile = wram->wPlayerStruct.nextTile;
    // LD_DE(SFX_ENTER_DOOR);
    // CP_A(COLL_DOOR);
    // RET_Z ;
    if(tile == COLL_DOOR)
        return SFX_ENTER_DOOR;
    // LD_DE(SFX_WARP_TO);
    // CP_A(COLL_WARP_PANEL);
    // RET_Z ;
    if(tile == COLL_WARP_PANEL)
        return SFX_WARP_TO;
    // LD_DE(SFX_EXIT_BUILDING);
    // RET;
    return SFX_EXIT_BUILDING;
}
