#include "../../constants.h"
#include "npc_movement.h"
#include "../../home/map.h"
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

bool CanObjectMoveInDirection_Conv(struct Object* bc){
    // LD_HL(OBJECT_PALETTE);
    // ADD_HL_BC;
    // BIT_hl(SWIMMING_F);
    // IF_Z goto not_swimming;
    if(bit_test(bc->palette, SWIMMING_F)) {
        // LD_HL(OBJECT_FLAGS1);
        // ADD_HL_BC;
        // BIT_hl(NOCLIP_TILES_F);  // lost, uncomment next line to fix
#if BUGFIX_NOCLIP_SWIM
        if(!bit_test(bc->flags1, NOCLIP_TILES_F)) {
    // jr nz, .noclip_tiles
#endif
            // PUSH_HL;
            // PUSH_BC;
            // CALL(aWillObjectBumpIntoLand);
            // POP_BC;
            // POP_HL;
            // RET_C ;
            if(WillObjectBumpIntoLand_Conv(bc))
                return true;
            // goto continue_;
#if BUGFIX_NOCLIP_SWIM
        }
#endif
    }
    else {
    // not_swimming:
        // LD_HL(OBJECT_FLAGS1);
        // ADD_HL_BC;
        // BIT_hl(NOCLIP_TILES_F);
        // IF_NZ goto noclip_tiles;
        if(!bit_test(bc->flags1, NOCLIP_TILES_F)) {
            // PUSH_HL;
            // PUSH_BC;
            // CALL(aWillObjectBumpIntoWater);
            // POP_BC;
            // POP_HL;
            // RET_C ;
            if(WillObjectBumpIntoWater_Conv(bc))
                return true;
        }
    }


// noclip_tiles:
// continue_:
    // BIT_hl(NOCLIP_OBJS_F);
    // IF_NZ goto noclip_objs;
    if(!bit_test(bc->flags1, NOCLIP_OBJS_F)) {
        // PUSH_HL;
        // PUSH_BC;
        // CALL(aWillObjectBumpIntoSomeoneElse);
        // POP_BC;
        // POP_HL;
        // RET_C ;
        if(WillObjectBumpIntoSomeoneElse_Conv(bc))
            return true;
    }

// noclip_objs:
    // BIT_hl(MOVE_ANYWHERE_F);
    // IF_NZ goto move_anywhere;
    if(!bit_test(bc->flags1, MOVE_ANYWHERE_F)) {
        // PUSH_HL;
        // CALL(aHasObjectReachedMovementLimit);
        // POP_HL;
        // RET_C ;
        if(HasObjectReachedMovementLimit_Conv(bc))
            return true;

        // PUSH_HL;
        // CALL(aIsObjectMovingOffEdgeOfScreen);
        // POP_HL;
        // RET_C ;
        if(IsObjectMovingOffEdgeOfScreen_Conv(bc))
            return true;
    }

// move_anywhere:
    // AND_A_A;
    // RET;
    return false;
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

bool WillObjectBumpIntoWater_Conv(struct Object* bc){
    // CALL(aCanObjectLeaveTile);
    // RET_C ;
    if(CanObjectLeaveTile_Conv(bc))
        return true;
    // LD_HL(OBJECT_NEXT_MAP_X);
    // ADD_HL_BC;
    // LD_D_hl;
    uint8_t d = bc->nextMapX;
    // LD_HL(OBJECT_NEXT_MAP_Y);
    // ADD_HL_BC;
    // LD_E_hl;
    uint8_t e = bc->nextMapY;
    // LD_HL(OBJECT_PALETTE);
    // ADD_HL_BC;
    // BIT_hl(OAM_PRIORITY);
    // JP_NZ (mWillObjectRemainOnWater);
    if(bit_test(bc->palette, OAM_PRIORITY))
        return WillObjectRemainOnWater_Conv(bc, d, e);
    // LD_HL(OBJECT_NEXT_TILE);
    // ADD_HL_BC;
    // LD_A_hl;
    // LD_D_A;
    // CALL(aGetTileCollision);
    // AND_A_A;  // LAND_TILE
    // JR_Z (mWillObjectBumpIntoTile);
    if(GetTileCollision_Conv(bc->nextTile) == LAND_TILE)
        return WillObjectBumpIntoTile_Conv(bc);
    // SCF;
    // RET;
    return true;
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

bool WillObjectBumpIntoLand_Conv(struct Object* bc){
    // CALL(aCanObjectLeaveTile);
    // RET_C ;
    if(CanObjectLeaveTile_Conv(bc))
        return true;
    // LD_HL(OBJECT_NEXT_TILE);
    // ADD_HL_BC;
    // LD_A_hl;
    // CALL(aGetTileCollision);
    // CP_A(WATER_TILE);
    // JR_Z (mWillObjectBumpIntoTile);
    if(GetTileCollision_Conv(bc->nextTile) == WATER_TILE)
        return WillObjectBumpIntoTile_Conv(bc);
    // SCF;
    // RET;
    return true;
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

bool WillObjectBumpIntoTile_Conv(struct Object* bc){
    static const uint8_t dir_masks[] = {
        DOWN_MASK,  // DOWN
        UP_MASK,  // UP
        RIGHT_MASK,  // LEFT
        LEFT_MASK,  // RIGHT
    };
    // LD_HL(OBJECT_NEXT_TILE);
    // ADD_HL_BC;
    // LD_A_hl;
    // CALL(aGetSideWallDirectionMask);
    u8_flag_s res = GetSideWallDirectionMask_Conv(bc->nextTile);
    // RET_NC ;
    if(!res.flag)
        return false;
    // PUSH_AF;
    // LD_HL(OBJECT_DIRECTION_WALKING);
    // ADD_HL_BC;
    // LD_A_hl;
    // maskbits(NUM_DIRECTIONS, 0);
    // LD_E_A;
    // LD_D(0);
    // LD_HL(mWillObjectBumpIntoTile_dir_masks);
    // ADD_HL_DE;
    // POP_AF;
    // AND_A_hl;
    uint8_t mask = res.a & dir_masks[bc->dirWalking & 3];
    // RET_Z ;
    if(mask == 0)
        return false;
    // SCF;
    // RET;
    return true;
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

bool CanObjectLeaveTile_Conv(struct Object* bc){
    static const uint8_t dir_masks[] = {
        UP_MASK,  // DOWN
        DOWN_MASK,  // UP
        LEFT_MASK,  // LEFT
        RIGHT_MASK,  // RIGHT
    };
    // LD_HL(OBJECT_STANDING_TILE);
    // ADD_HL_BC;
    // LD_A_hl;
    // CALL(aGetSideWallDirectionMask);
    u8_flag_s res = GetSideWallDirectionMask_Conv(bc->standingTile);
    // RET_NC ;
    if(!res.flag)
        return false;
    // PUSH_AF;
    // LD_HL(OBJECT_DIRECTION_WALKING);
    // ADD_HL_BC;
    // maskbits(NUM_DIRECTIONS, 0);
    // LD_E_A;
    // LD_D(0);
    // LD_HL(mCanObjectLeaveTile_dir_masks);
    // ADD_HL_DE;
    // POP_AF;
    // AND_A_hl;
    uint8_t mask = res.a & dir_masks[bc->dirWalking & 3];
    // RET_Z ;
    if(mask == 0)
        return false;
    // SCF;
    // RET;
    return true;
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

u8_flag_s GetSideWallDirectionMask_Conv(uint8_t a){
    static const uint8_t side_wall_masks[] = {
        RIGHT_MASK,  // COLL_RIGHT_WALL/BUOY
        LEFT_MASK,  // COLL_LEFT_WALL/BUOY
        DOWN_MASK,  // COLL_UP_WALL/BUOY
        UP_MASK,  // COLL_DOWN_WALL/BUOY
        UP_MASK | RIGHT_MASK,  // COLL_DOWN_RIGHT_WALL/BUOY
        UP_MASK | LEFT_MASK,  // COLL_DOWN_LEFT_WALL/BUOY
        DOWN_MASK | RIGHT_MASK,  // COLL_UP_RIGHT_WALL/BUOY
        DOWN_MASK | LEFT_MASK,  // COLL_UP_LEFT_WALL/BUOY
    };
    // LD_D_A;
    uint8_t d = a;
    // AND_A(0xf0);
    // CP_A(HI_NYBBLE_SIDE_WALLS);
    // IF_Z goto continue_;
    // CP_A(HI_NYBBLE_SIDE_BUOYS);
    // IF_Z goto continue_;
    if((a & 0xf0) == HI_NYBBLE_SIDE_WALLS
    || (a & 0xf0) == HI_NYBBLE_SIDE_BUOYS) {
    // continue_:
        // LD_A_D;
        // AND_A(0x7);
        // LD_E_A;
        // LD_D(0);
        // LD_HL(mGetSideWallDirectionMask_side_wall_masks);
        // ADD_HL_DE;
        // LD_A_hl;
        // SCF;
        // RET;
        return u8_flag(side_wall_masks[d & 0x7], true);
    }
    // XOR_A_A;
    // RET;
    return u8_flag(0, false);
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

bool WillObjectRemainOnWater_Conv(struct Object* bc, uint8_t d, uint8_t e){
    uint8_t d2, e2;
    // LD_HL(OBJECT_DIRECTION_WALKING);
    // ADD_HL_BC;
    // LD_A_hl;
    // maskbits(NUM_DIRECTIONS, 0);
    switch(bc->dirWalking & 3) {
        // IF_Z goto down;
        case DOWN:
        // down:
            // INC_E;
            e++;
            // PUSH_DE;
            e2 = e;
            // INC_D;
            d2 = d + 1;
            break;
        // DEC_A;
        // IF_Z goto up;
        case UP:
        // up:
            // PUSH_DE;
            e2 = e;
            // INC_D;
            d2 = d + 1;
            break;
        // DEC_A;
        // IF_Z goto left;
        case LEFT:
        // left:
            // PUSH_DE;
            d2 = d;
            // INC_E;
            e2 = e + 1;
            break;
        // goto right;
        default:
        // right:
            // INC_D;
            d++;
            // PUSH_DE;
            d2 = d;
            // INC_E;
            e2 = e + 1;
            break;
    }

// continue_:
    // CALL(aGetCoordTile);
    // CALL(aGetTileCollision);
    // POP_DE;
    // AND_A_A;  // LAND_TILE
    // IF_NZ goto not_land;
    if(GetTileCollision_Conv(GetCoordTile_Conv(d2, e2)) != LAND_TILE)
        return true;
    // CALL(aGetCoordTile);
    // CALL(aGetTileCollision);
    // AND_A_A;  // LAND_TILE
    // IF_NZ goto not_land;
    if(GetTileCollision_Conv(GetCoordTile_Conv(d, e)) != LAND_TILE)
        return true;
    // XOR_A_A;
    // RET;
    return false;

// not_land:
    // SCF;
    // RET;
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

struct Object* CheckFacingObject_Conv(void){
    // CALL(aGetFacingTileCoord);
    struct CoordsTileId res = GetFacingTileCoord_Conv();

//  Double the distance for counter tiles.
    // CALL(aCheckCounterTile);
    // IF_NZ goto not_counter;
    if(CheckCounterTile_Conv(res.tileId)) {

        // LD_A_addr(wPlayerStandingMapX);
        // SUB_A_D;
        // CPL;
        // INC_A;
        // ADD_A_D;
        // LD_D_A;
        res.x = -(wram->wPlayerStruct.nextMapX - res.x) + res.x;

        // LD_A_addr(wPlayerStandingMapY);
        // SUB_A_E;
        // CPL;
        // INC_A;
        // ADD_A_E;
        // LD_E_A;
        res.y = -(wram->wPlayerStruct.nextMapY - res.y) + res.y;
    }

// not_counter:
    // LD_BC(wObjectStructs);  // redundant
    // LD_A(0);
    // LDH_addr_A(hMapObjectIndex);
    hram->hMapObjectIndex = 0;
    // CALL(aIsNPCAtCoord);
    struct Object* bc = IsNPCAtCoord_Conv(res.x, res.y);
    // RET_NC ;
    if(bc == NULL)
        return NULL;
    // LD_HL(OBJECT_DIRECTION_WALKING);
    // ADD_HL_BC;
    // LD_A_hl;
    // CP_A(STANDING);
    // IF_Z goto standing;
    if(bc->dirWalking == (uint8_t)STANDING)
        return bc;
    // XOR_A_A;
    // RET;
    return NULL;

// standing:
    // SCF;
    // RET;
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

bool WillObjectBumpIntoSomeoneElse_Conv(struct Object* bc){
    // LD_HL(OBJECT_NEXT_MAP_X);
    // ADD_HL_BC;
    // LD_D_hl;
    // LD_HL(OBJECT_NEXT_MAP_Y);
    // ADD_HL_BC;
    // LD_E_hl;
    // JR(mIsNPCAtCoord);
    return IsNPCAtCoord_Conv(bc->nextMapX, bc->nextMapY) != NULL;
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

bool HasObjectReachedMovementLimit_Conv(struct Object* bc){
    // LD_HL(OBJECT_RADIUS);
    // ADD_HL_BC;
    // LD_A_hl;
    // AND_A_A;
    // IF_Z goto nope;
    if(bc->radius == 0)
        return false;
    // AND_A(0xf);
    // IF_Z goto check_y;
    if((bc->radius & 0xf) != 0) {
        // LD_E_A;
        // LD_D_A;
        // LD_HL(OBJECT_INIT_X);
        // ADD_HL_BC;
        // LD_A_hl;
        // SUB_A_D;
        // LD_D_A;
        uint8_t d = bc->initX - (bc->radius & 0xf);
        // LD_A_hl;
        // ADD_A_E;
        // LD_E_A;
        uint8_t e = bc->initX + (bc->radius & 0xf);
        // LD_HL(OBJECT_NEXT_MAP_X);
        // ADD_HL_BC;
        // LD_A_hl;
        // CP_A_D;
        // IF_Z goto yes;
        // CP_A_E;
        // IF_Z goto yes;
        if(bc->nextMapX == d || bc->nextMapX == e)
            return true;
    }

// check_y:
    // LD_HL(OBJECT_RADIUS);
    // ADD_HL_BC;
    // LD_A_hl;
    // SWAP_A;
    // AND_A(0xf);
    // IF_Z goto nope;
    if(((bc->radius >> 4) & 0xf) != 0) {
        // LD_E_A;
        // LD_D_A;
        // LD_HL(OBJECT_INIT_Y);
        // ADD_HL_BC;
        // LD_A_hl;
        // SUB_A_D;
        // LD_D_A;
        uint8_t d = bc->initY - ((bc->radius >> 4) & 0xf);
        // LD_A_hl;
        // ADD_A_E;
        // LD_E_A;
        uint8_t e = bc->initY + ((bc->radius >> 4) & 0xf);
        // LD_HL(OBJECT_NEXT_MAP_Y);
        // ADD_HL_BC;
        // LD_A_hl;
        // CP_A_D;
        // IF_Z goto yes;
        // CP_A_E;
        // IF_Z goto yes;
        if(bc->nextMapY == d || bc->nextMapY == e)
            return true;
    }

// nope:
    // XOR_A_A;
    // RET;
    return false;

// yes:
    // SCF;
    // RET;
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

// TODO: Replace gotos in this function.
bool IsObjectMovingOffEdgeOfScreen_Conv(struct Object* bc){
    // LD_HL(OBJECT_NEXT_MAP_X);
    // ADD_HL_BC;
    // LD_A_addr(wXCoord);
    // CP_A_hl;
    // IF_Z goto check_y;
    if(wram->wXCoord == bc->nextMapX)
        goto check_y;
    // IF_NC goto yes;
    if(wram->wXCoord > bc->nextMapX)
        goto yes;
    // ADD_A(0x9);
    // CP_A_hl;
    // IF_C goto yes;
    if(wram->wXCoord + 0x9 < bc->nextMapX)
        goto yes;


check_y:
    // LD_HL(OBJECT_NEXT_MAP_Y);
    // ADD_HL_BC;
    // LD_A_addr(wYCoord);
    // CP_A_hl;
    // IF_Z goto nope;
    if(wram->wYCoord == bc->nextMapY)
        goto nope;
    // IF_NC goto yes;
    if(wram->wYCoord > bc->nextMapY)
        goto yes;
    // ADD_A(0x8);
    // CP_A_hl;
    // IF_C goto yes;
    if(wram->wYCoord + 0x8 < bc->nextMapY)
        goto yes;

nope:
    // AND_A_A;
    // RET;
    return false;

yes:
    // SCF;
    // RET;
    return true;
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
