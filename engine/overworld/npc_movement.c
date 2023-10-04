#include "../../constants.h"
#include "npc_movement.h"
#include "../../home/map_objects.h"

void CanObjectMoveInDirection(void){
    LD_HL(OBJECT_PALETTE);
    ADD_HL_BC;
    BIT_hl(SWIMMING_F);
    IF_Z goto not_swimming;

    LD_HL(OBJECT_FLAGS1);
    ADD_HL_BC;
    BIT_hl(NOCLIP_TILES_F);  // lost, uncomment next line to fix
// jr nz, .noclip_tiles
    PUSH_HL;
    PUSH_BC;
    CALL(aWillObjectBumpIntoLand);
    POP_BC;
    POP_HL;
    RET_C ;
    goto continue_;


not_swimming:
    LD_HL(OBJECT_FLAGS1);
    ADD_HL_BC;
    BIT_hl(NOCLIP_TILES_F);
    IF_NZ goto noclip_tiles;
    PUSH_HL;
    PUSH_BC;
    CALL(aWillObjectBumpIntoWater);
    POP_BC;
    POP_HL;
    RET_C ;


noclip_tiles:

continue_:
    BIT_hl(NOCLIP_OBJS_F);
    IF_NZ goto noclip_objs;

    PUSH_HL;
    PUSH_BC;
    CALL(aWillObjectBumpIntoSomeoneElse);
    POP_BC;
    POP_HL;
    RET_C ;


noclip_objs:
    BIT_hl(MOVE_ANYWHERE_F);
    IF_NZ goto move_anywhere;
    PUSH_HL;
    CALL(aHasObjectReachedMovementLimit);
    POP_HL;
    RET_C ;

    PUSH_HL;
    CALL(aIsObjectMovingOffEdgeOfScreen);
    POP_HL;
    RET_C ;


move_anywhere:
    AND_A_A;
    RET;

}

void WillObjectBumpIntoWater(void){
    CALL(aCanObjectLeaveTile);
    RET_C ;
    LD_HL(OBJECT_NEXT_MAP_X);
    ADD_HL_BC;
    LD_D_hl;
    LD_HL(OBJECT_NEXT_MAP_Y);
    ADD_HL_BC;
    LD_E_hl;
    LD_HL(OBJECT_PALETTE);
    ADD_HL_BC;
    BIT_hl(OAM_PRIORITY);
    JP_NZ (mWillObjectRemainOnWater);
    LD_HL(OBJECT_NEXT_TILE);
    ADD_HL_BC;
    LD_A_hl;
    LD_D_A;
    CALL(aGetTileCollision);
    AND_A_A;  // LAND_TILE
    JR_Z (mWillObjectBumpIntoTile);
    SCF;
    RET;

}

void WillObjectBumpIntoLand(void){
    CALL(aCanObjectLeaveTile);
    RET_C ;
    LD_HL(OBJECT_NEXT_TILE);
    ADD_HL_BC;
    LD_A_hl;
    CALL(aGetTileCollision);
    CP_A(WATER_TILE);
    JR_Z (mWillObjectBumpIntoTile);
    SCF;
    RET;

}

void WillObjectBumpIntoTile(void){
    LD_HL(OBJECT_NEXT_TILE);
    ADD_HL_BC;
    LD_A_hl;
    CALL(aGetSideWallDirectionMask);
    RET_NC ;
    PUSH_AF;
    LD_HL(OBJECT_DIRECTION_WALKING);
    ADD_HL_BC;
    LD_A_hl;
    maskbits(NUM_DIRECTIONS, 0);
    LD_E_A;
    LD_D(0);
    LD_HL(mWillObjectBumpIntoTile_dir_masks);
    ADD_HL_DE;
    POP_AF;
    AND_A_hl;
    RET_Z ;
    SCF;
    RET;


dir_masks:
    //db ['DOWN_MASK'];  // DOWN
    //db ['UP_MASK'];  // UP
    //db ['RIGHT_MASK'];  // LEFT
    //db ['LEFT_MASK'];  // RIGHT

    return CanObjectLeaveTile();
}

void CanObjectLeaveTile(void){
    LD_HL(OBJECT_STANDING_TILE);
    ADD_HL_BC;
    LD_A_hl;
    CALL(aGetSideWallDirectionMask);
    RET_NC ;
    PUSH_AF;
    LD_HL(OBJECT_DIRECTION_WALKING);
    ADD_HL_BC;
    maskbits(NUM_DIRECTIONS, 0);
    LD_E_A;
    LD_D(0);
    LD_HL(mCanObjectLeaveTile_dir_masks);
    ADD_HL_DE;
    POP_AF;
    AND_A_hl;
    RET_Z ;
    SCF;
    RET;


dir_masks:
    //db ['UP_MASK'];  // DOWN
    //db ['DOWN_MASK'];  // UP
    //db ['LEFT_MASK'];  // LEFT
    //db ['RIGHT_MASK'];  // RIGHT

    return GetSideWallDirectionMask();
}

void GetSideWallDirectionMask(void){
    LD_D_A;
    AND_A(0xf0);
    CP_A(HI_NYBBLE_SIDE_WALLS);
    IF_Z goto continue_;
    CP_A(HI_NYBBLE_SIDE_BUOYS);
    IF_Z goto continue_;
    XOR_A_A;
    RET;


continue_:
    LD_A_D;
    AND_A(0x7);
    LD_E_A;
    LD_D(0);
    LD_HL(mGetSideWallDirectionMask_side_wall_masks);
    ADD_HL_DE;
    LD_A_hl;
    SCF;
    RET;


side_wall_masks:
    //db ['RIGHT_MASK'];  // COLL_RIGHT_WALL/BUOY
    //db ['LEFT_MASK'];  // COLL_LEFT_WALL/BUOY
    //db ['DOWN_MASK'];  // COLL_UP_WALL/BUOY
    //db ['UP_MASK'];  // COLL_DOWN_WALL/BUOY
    //db ['UP_MASK | RIGHT_MASK'];  // COLL_DOWN_RIGHT_WALL/BUOY
    //db ['UP_MASK | LEFT_MASK'];  // COLL_DOWN_LEFT_WALL/BUOY
    //db ['DOWN_MASK | RIGHT_MASK'];  // COLL_UP_RIGHT_WALL/BUOY
    //db ['DOWN_MASK | LEFT_MASK'];  // COLL_UP_LEFT_WALL/BUOY

    return WillObjectRemainOnWater();
}

void WillObjectRemainOnWater(void){
    LD_HL(OBJECT_DIRECTION_WALKING);
    ADD_HL_BC;
    LD_A_hl;
    maskbits(NUM_DIRECTIONS, 0);
    IF_Z goto down;
    DEC_A;
    IF_Z goto up;
    DEC_A;
    IF_Z goto left;
    goto right;


down:
    INC_E;
    PUSH_DE;
    INC_D;
    goto continue_;


up:
    PUSH_DE;
    INC_D;
    goto continue_;


left:
    PUSH_DE;
    INC_E;
    goto continue_;


right:
    INC_D;
    PUSH_DE;
    INC_E;


continue_:
    CALL(aGetCoordTile);
    CALL(aGetTileCollision);
    POP_DE;
    AND_A_A;  // LAND_TILE
    IF_NZ goto not_land;
    CALL(aGetCoordTile);
    CALL(aGetTileCollision);
    AND_A_A;  // LAND_TILE
    IF_NZ goto not_land;
    XOR_A_A;
    RET;


not_land:
    SCF;
    RET;

}

void CheckFacingObject(void){
    CALL(aGetFacingTileCoord);

//  Double the distance for counter tiles.
    CALL(aCheckCounterTile);
    IF_NZ goto not_counter;

    LD_A_addr(wPlayerStandingMapX);
    SUB_A_D;
    CPL;
    INC_A;
    ADD_A_D;
    LD_D_A;

    LD_A_addr(wPlayerStandingMapY);
    SUB_A_E;
    CPL;
    INC_A;
    ADD_A_E;
    LD_E_A;


not_counter:
    LD_BC(wObjectStructs);  // redundant
    LD_A(0);
    LDH_addr_A(hMapObjectIndex);
    CALL(aIsNPCAtCoord);
    RET_NC ;
    LD_HL(OBJECT_DIRECTION_WALKING);
    ADD_HL_BC;
    LD_A_hl;
    CP_A(STANDING);
    IF_Z goto standing;
    XOR_A_A;
    RET;


standing:
    SCF;
    RET;

}

void WillObjectBumpIntoSomeoneElse(void){
    LD_HL(OBJECT_NEXT_MAP_X);
    ADD_HL_BC;
    LD_D_hl;
    LD_HL(OBJECT_NEXT_MAP_Y);
    ADD_HL_BC;
    LD_E_hl;
    JR(mIsNPCAtCoord);

}

void IsObjectFacingSomeoneElse(void){
//  //  unreferenced
    LDH_A_addr(hMapObjectIndex);
    CALL(aGetObjectStruct);
    CALL(aIsObjectFacingSomeoneElse_GetFacingCoords);
    CALL(aIsNPCAtCoord);
    RET;


GetFacingCoords:
    LD_HL(OBJECT_NEXT_MAP_X);
    ADD_HL_BC;
    LD_D_hl;
    LD_HL(OBJECT_NEXT_MAP_Y);
    ADD_HL_BC;
    LD_E_hl;
    CALL(aGetSpriteDirection);
    AND_A_A;  // OW_DOWN?
    IF_Z goto down;
    CP_A(OW_UP);
    IF_Z goto up;
    CP_A(OW_LEFT);
    IF_Z goto left;
// OW_RIGHT
    INC_D;
    RET;


down:
    INC_E;
    RET;


up:
    DEC_E;
    RET;


left:
    DEC_D;
    RET;

}

void IsNPCAtCoord(void){
    LD_BC(wObjectStructs);
    XOR_A_A;

loop:
    LDH_addr_A(hObjectStructIndex);
    CALL(aDoesObjectHaveASprite);
    IF_Z goto next;

    LD_HL(OBJECT_FLAGS1);
    ADD_HL_BC;
    BIT_hl(7);
    IF_NZ goto next;

    LD_HL(OBJECT_PALETTE);
    ADD_HL_BC;
    BIT_hl(BIG_OBJECT_F);
    IF_Z goto not_big;
    CALL(aWillObjectIntersectBigObject);
    IF_NC goto check_current_coords;
    goto continue_;


not_big:
    LD_HL(OBJECT_NEXT_MAP_X);
    ADD_HL_BC;
    LD_A_hl;
    CP_A_D;
    IF_NZ goto check_current_coords;
    LD_HL(OBJECT_NEXT_MAP_Y);
    ADD_HL_BC;
    LD_A_hl;
    CP_A_E;
    IF_NZ goto check_current_coords;


continue_:
    LDH_A_addr(hMapObjectIndex);
    LD_L_A;
    LDH_A_addr(hObjectStructIndex);
    CP_A_L;
    IF_NZ goto yes;


check_current_coords:
    LD_HL(OBJECT_MAP_X);
    ADD_HL_BC;
    LD_A_hl;
    CP_A_D;
    IF_NZ goto next;
    LD_HL(OBJECT_MAP_Y);
    ADD_HL_BC;
    LD_A_hl;
    CP_A_E;
    IF_NZ goto next;
    LDH_A_addr(hMapObjectIndex);
    LD_L_A;
    LDH_A_addr(hObjectStructIndex);
    CP_A_L;
    IF_NZ goto yes;


next:
    LD_HL(OBJECT_LENGTH);
    ADD_HL_BC;
    LD_B_H;
    LD_C_L;
    LDH_A_addr(hObjectStructIndex);
    INC_A;
    CP_A(NUM_OBJECT_STRUCTS);
    IF_NZ goto loop;
    AND_A_A;
    RET;


yes:
    SCF;
    RET;

}

struct Object* IsNPCAtCoord_Conv(uint8_t d, uint8_t e){
    // LD_BC(wObjectStructs);
    struct Object* bc = &wram->wPlayerStruct;
    // XOR_A_A;
    hram->hObjectStructIndex = 0;

    do {
    // loop:
        // LDH_addr_A(hObjectStructIndex);
        // CALL(aDoesObjectHaveASprite);
        // IF_Z goto next;
        if(!DoesObjectHaveASprite_Conv(bc))
            continue;

        // LD_HL(OBJECT_FLAGS1);
        // ADD_HL_BC;
        // BIT_hl(7);
        // IF_NZ goto next;
        if(bit_test(bc->flags1, EMOTE_OBJECT_F))
            continue;

        // LD_HL(OBJECT_PALETTE);
        // ADD_HL_BC;
        // BIT_hl(BIG_OBJECT_F);
        // IF_Z goto not_big;
        if(bit_test(bc->palette, BIG_OBJECT_F)) {
            // CALL(aWillObjectIntersectBigObject);
            // IF_NC goto check_current_coords;
            if(WillObjectIntersectBigObject_Conv(bc, d, e)) {
            // goto continue_;
            // continue_:
                // LDH_A_addr(hMapObjectIndex);
                // LD_L_A;
                // LDH_A_addr(hObjectStructIndex);
                // CP_A_L;
                // IF_NZ goto yes;
                if(hram->hMapObjectIndex != hram->hObjectStructIndex)
                    return bc;
            }
        }
        else {
        // not_big:
            // LD_HL(OBJECT_NEXT_MAP_X);
            // ADD_HL_BC;
            // LD_A_hl;
            // CP_A_D;
            // IF_NZ goto check_current_coords;
            // LD_HL(OBJECT_NEXT_MAP_Y);
            // ADD_HL_BC;
            // LD_A_hl;
            // CP_A_E;
            // IF_NZ goto check_current_coords;
            if(bc->nextMapX == d && bc->nextMapY == e) {
            // continue_:
                // LDH_A_addr(hMapObjectIndex);
                // LD_L_A;
                // LDH_A_addr(hObjectStructIndex);
                // CP_A_L;
                // IF_NZ goto yes;
                if(hram->hMapObjectIndex != hram->hObjectStructIndex)
                    return bc;
            }
        }

    // check_current_coords:
        // LD_HL(OBJECT_MAP_X);
        // ADD_HL_BC;
        // LD_A_hl;
        // CP_A_D;
        // IF_NZ goto next;
        if(bc->mapX != d)
            continue;
        // LD_HL(OBJECT_MAP_Y);
        // ADD_HL_BC;
        // LD_A_hl;
        // CP_A_E;
        // IF_NZ goto next;
        if(bc->mapY != e)
            continue;
        // LDH_A_addr(hMapObjectIndex);
        // LD_L_A;
        // LDH_A_addr(hObjectStructIndex);
        // CP_A_L;
        // IF_NZ goto yes;
        if(hram->hMapObjectIndex != hram->hObjectStructIndex)
            return bc;


    // next:
        // LD_HL(OBJECT_LENGTH);
        // ADD_HL_BC;
        // LD_B_H;
        // LD_C_L;
        // LDH_A_addr(hObjectStructIndex);
        // INC_A;
        // CP_A(NUM_OBJECT_STRUCTS);
        // IF_NZ goto loop;
    } while(bc++, ++hram->hObjectStructIndex != NUM_OBJECT_STRUCTS);

    hram->hObjectStructIndex--;
    // AND_A_A;
    // RET;
    return NULL;


// yes:
    // SCF;
    // RET;
}

void HasObjectReachedMovementLimit(void){
    LD_HL(OBJECT_RADIUS);
    ADD_HL_BC;
    LD_A_hl;
    AND_A_A;
    IF_Z goto nope;
    AND_A(0xf);
    IF_Z goto check_y;
    LD_E_A;
    LD_D_A;
    LD_HL(OBJECT_INIT_X);
    ADD_HL_BC;
    LD_A_hl;
    SUB_A_D;
    LD_D_A;
    LD_A_hl;
    ADD_A_E;
    LD_E_A;
    LD_HL(OBJECT_NEXT_MAP_X);
    ADD_HL_BC;
    LD_A_hl;
    CP_A_D;
    IF_Z goto yes;
    CP_A_E;
    IF_Z goto yes;


check_y:
    LD_HL(OBJECT_RADIUS);
    ADD_HL_BC;
    LD_A_hl;
    SWAP_A;
    AND_A(0xf);
    IF_Z goto nope;
    LD_E_A;
    LD_D_A;
    LD_HL(OBJECT_INIT_Y);
    ADD_HL_BC;
    LD_A_hl;
    SUB_A_D;
    LD_D_A;
    LD_A_hl;
    ADD_A_E;
    LD_E_A;
    LD_HL(OBJECT_NEXT_MAP_Y);
    ADD_HL_BC;
    LD_A_hl;
    CP_A_D;
    IF_Z goto yes;
    CP_A_E;
    IF_Z goto yes;


nope:
    XOR_A_A;
    RET;


yes:
    SCF;
    RET;

}

void IsObjectMovingOffEdgeOfScreen(void){
    LD_HL(OBJECT_NEXT_MAP_X);
    ADD_HL_BC;
    LD_A_addr(wXCoord);
    CP_A_hl;
    IF_Z goto check_y;
    IF_NC goto yes;
    ADD_A(0x9);
    CP_A_hl;
    IF_C goto yes;


check_y:
    LD_HL(OBJECT_NEXT_MAP_Y);
    ADD_HL_BC;
    LD_A_addr(wYCoord);
    CP_A_hl;
    IF_Z goto nope;
    IF_NC goto yes;
    ADD_A(0x8);
    CP_A_hl;
    IF_C goto yes;


nope:
    AND_A_A;
    RET;


yes:
    SCF;
    RET;

}

void IsNPCAtPlayerCoord(void){
//  //  unreferenced
    LD_A_addr(wPlayerStandingMapX);
    LD_D_A;
    LD_A_addr(wPlayerStandingMapY);
    LD_E_A;
    LD_BC(wObjectStructs);
    XOR_A_A;

loop:
    LDH_addr_A(hObjectStructIndex);
    CALL(aDoesObjectHaveASprite);
    IF_Z goto next;

    LD_HL(OBJECT_MOVEMENTTYPE);
    ADD_HL_BC;
    LD_A_hl;
    CP_A(SPRITEMOVEDATA_BIGDOLLSYM);
    IF_NZ goto not_big;
    CALL(aWillObjectIntersectBigObject);
    IF_C goto yes;
    goto next;


not_big:
    LD_HL(OBJECT_NEXT_MAP_Y);
    ADD_HL_BC;
    LD_A_hl;
    CP_A_E;
    IF_NZ goto check_current_coords;
    LD_HL(OBJECT_NEXT_MAP_X);
    ADD_HL_BC;
    LD_A_hl;
    CP_A_D;
    IF_NZ goto check_current_coords;
    LDH_A_addr(hObjectStructIndex);
    CP_A(PLAYER_OBJECT);
    IF_Z goto next;
    goto yes;


check_current_coords:
    LD_HL(OBJECT_MAP_Y);
    ADD_HL_BC;
    LD_A_hl;
    CP_A_E;
    IF_NZ goto next;
    LD_HL(OBJECT_MAP_X);
    ADD_HL_BC;
    LD_A_hl;
    CP_A_D;
    IF_NZ goto next;
    goto yes;


next:
    LD_HL(OBJECT_LENGTH);
    ADD_HL_BC;
    LD_B_H;
    LD_C_L;
    LDH_A_addr(hObjectStructIndex);
    INC_A;
    CP_A(NUM_OBJECT_STRUCTS);
    IF_NZ goto loop;
    XOR_A_A;
    RET;


yes:
    SCF;
    RET;

}

void WillObjectIntersectBigObject(void){
    LD_HL(OBJECT_NEXT_MAP_X);
    ADD_HL_BC;
    LD_A_D;
    SUB_A_hl;
    IF_C goto nope;
    CP_A(2);  // big doll width
    IF_NC goto nope;
    LD_HL(OBJECT_NEXT_MAP_Y);
    ADD_HL_BC;
    LD_A_E;
    SUB_A_hl;
    IF_C goto nope;
    CP_A(2);  // big doll height
    IF_NC goto nope;
    SCF;
    RET;


nope:
    AND_A_A;
    RET;

}

bool WillObjectIntersectBigObject_Conv(struct Object* bc, uint8_t d, uint8_t e){
    // LD_HL(OBJECT_NEXT_MAP_X);
    // ADD_HL_BC;
    // LD_A_D;
    // SUB_A_hl;
    // IF_C goto nope;
    if(d < bc->nextMapX)
        return false;
    // CP_A(2);  // big doll width
    // IF_NC goto nope;
    if(d - bc->nextMapX >= 2)
        return false;
    // LD_HL(OBJECT_NEXT_MAP_Y);
    // ADD_HL_BC;
    // LD_A_E;
    // SUB_A_hl;
    // IF_C goto nope;
    if(e < bc->nextMapY)
        return false;
    // CP_A(2);  // big doll height
    // IF_NC goto nope;
    if(e - bc->nextMapY >= 2)
        return false;
    // SCF;
    // RET;
    return true;

// nope:
    // AND_A_A;
    // RET;
}
