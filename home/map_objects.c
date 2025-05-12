#include "../constants.h"
#include "map_objects.h"
#include "../engine/overworld/map_objects.h"
#include "../engine/overworld/overworld.h"
#include "../engine/overworld/player_object.h"
#include "copy.h"
#include "array.h"
#include "../data/collision/collision_permissions.h"
#include "../data/sprites/map_objects.h"
#include "map.h"

const uint8_t* gMovementDataAddr;

//  Functions handling map objects.

uint8_t GetSpritePalette(uint8_t a){
    // PUSH_HL;
    // PUSH_DE;
    // PUSH_BC;
    // LD_C_A;

    // FARCALL(av_GetSpritePalette);
    return v_GetSpritePalette(a);

    // LD_A_C;
    // POP_BC;
    // POP_DE;
    // POP_HL;
    // RET;
}

uint8_t GetSpriteVTile(uint8_t a, uint8_t mapObjIdx){
    // PUSH_HL;
    // PUSH_BC;
    // LD_HL(wUsedSprites + 2);
    // LD_C(SPRITE_GFX_LIST_CAPACITY - 1);
    // LD_B_A;
    // LDH_A_addr(hMapObjectIndex);
    // CP_A(0);
    // IF_Z goto nope;
    if(mapObjIdx == 0)
        return wram->wUsedSprites[1];

    uint8_t* hl = wram->wUsedSprites + 2;
    uint8_t c = SPRITE_GFX_LIST_CAPACITY - 1;
    // LD_A_B;

    do {
    // loop:
        // CP_A_hl;
        // IF_Z goto found;
        if(*hl == a) {
        // found:
            // INC_HL;
            hl++;
            // XOR_A_A;
            // LD_A_hl;
            return *hl;
        }
        // INC_HL;
        // INC_HL;
        // DEC_C;
        // IF_NZ goto loop;
    } while(hl += 2, --c != 0);
    // LD_A_addr(wUsedSprites + 1);
    // SCF;
    return wram->wUsedSprites[1];
    // goto done;


// nope:
    // LD_A_addr(wUsedSprites + 1);
    // goto done;


// found:
    // INC_HL;
    // XOR_A_A;
    // LD_A_hl;

// done:
    // POP_BC;
    // POP_HL;
    // RET;
}

void DoesSpriteHaveFacings(void){
        PUSH_DE;
    PUSH_HL;

    LD_B_A;
    LDH_A_addr(hROMBank);
    PUSH_AF;
    LD_A(BANK(av_DoesSpriteHaveFacings));
    RST(aBankswitch);

    LD_A_B;
    CALL(av_DoesSpriteHaveFacings);
    LD_C_A;

    POP_DE;
    LD_A_D;
    RST(aBankswitch);

    POP_HL;
    POP_DE;
    RET;

}

uint8_t GetPlayerStandingTile(void){
    // LD_A_addr(wPlayerStandingTile);
    // CALL(aGetTileCollision);
    // LD_B_A;
    // RET;
    return GetTileCollision(wram->wPlayerStruct.nextTile);
}

// Returns true (z) if the player is standing on a water tile.
bool CheckOnWater(void){
    // LD_A_addr(wPlayerStandingTile);
    // CALL(aGetTileCollision);
    uint8_t col = GetTileCollision(wram->wPlayerStruct.nextTile);
    // SUB_A(WATER_TILE);
    // RET_Z ;
    if(col == WATER_TILE)
        return true;
    // AND_A_A;
    // RET;
    return false;
}

//  Get the collision type of tile a.
uint8_t GetTileCollision(uint8_t a){
    // PUSH_DE;
    // PUSH_HL;

    // LD_HL(mTileCollisionTable);
    // LD_E_A;
    // LD_D(0);
    // ADD_HL_DE;

    // LDH_A_addr(hROMBank);
    // PUSH_AF;
    // LD_A(BANK(aTileCollisionTable));
    // RST(aBankswitch);
    // LD_E_hl;
    // POP_AF;
    // RST(aBankswitch);
    uint8_t e = TileCollisionTable[a];

    // LD_A_E;
    // AND_A(0xf);  // lo nybble only
    return e & 0xf;  // lo nybble only

    // POP_HL;
    // POP_DE;
    // RET;
}

bool CheckGrassTile(uint8_t col){
    uint8_t a = col & 0xf0;
    if(a == HI_NYBBLE_TALL_GRASS) {
        if((col & LO_NYBBLE_GRASS) == 0)
            return true;
        return false;
    }
    if(a == HI_NYBBLE_WATER) {
        //  For some reason, the above code is duplicated down here.
        if((col & LO_NYBBLE_GRASS) == 0)
            return true;
        return false;
    }
    return false;
}

bool CheckSuperTallGrassTile(uint8_t a){
    // CP_A(COLL_LONG_GRASS);
    // RET_Z ;
    if(a == COLL_LONG_GRASS)
        return true;
    // CP_A(COLL_LONG_GRASS_1C);
    // RET;
    return a == COLL_LONG_GRASS_1C;
}

bool CheckCutTreeTile(uint8_t a){
    // CP_A(COLL_CUT_TREE);
    // RET_Z ;
    if(a == COLL_CUT_TREE)
        return true;
    // CP_A(COLL_CUT_TREE_1A);
    // RET;
    return a == COLL_CUT_TREE_1A;
}

bool CheckHeadbuttTreeTile(uint8_t a){
    // CP_A(COLL_HEADBUTT_TREE);
    // RET_Z ;
    // CP_A(COLL_HEADBUTT_TREE_1D);
    // RET;
    return (a == COLL_HEADBUTT_TREE) || (a == COLL_HEADBUTT_TREE_1D);
}

bool CheckCounterTile(uint8_t a){
    // CP_A(COLL_COUNTER);
    // RET_Z ;
    // CP_A(COLL_COUNTER_98);
    // RET;
    return (a == COLL_COUNTER || a == COLL_COUNTER_98);
}

bool CheckPitTile(uint8_t a){
    // CP_A(COLL_PIT);
    // RET_Z ;
    // CP_A(COLL_PIT_68);
    // RET;
    return a == COLL_PIT || a == COLL_PIT_68;
}

bool CheckIceTile(uint8_t a){
    // CP_A(COLL_ICE);
    // RET_Z ;
    if(a == COLL_ICE)
        return true;
    // CP_A(COLL_ICE_2B);
    // RET_Z ;
    if(a == COLL_ICE_2B)
        return true;
    // SCF;
    // RET;
    return false;
}

bool CheckWhirlpoolTile(uint8_t a){
    // NOP;
    // CP_A(COLL_WHIRLPOOL);
    // RET_Z ;
    // CP_A(COLL_WHIRLPOOL_2C);
    // RET_Z ;
    // SCF;
    return (a == COLL_WHIRLPOOL || a == COLL_WHIRLPOOL_2C);
    // RET;
}

bool CheckWaterfallTile(uint8_t a){
    // CP_A(COLL_WATERFALL);
    // RET_Z ;
    if(a == COLL_WATERFALL)
        return true;
    // CP_A(COLL_CURRENT_DOWN);
    // RET;
    return a == COLL_CURRENT_DOWN;
}

bool CheckStandingOnEntrance(void){
    // LD_A_addr(wPlayerStandingTile);
    uint8_t a = wram->wPlayerStruct.nextTile;
    // CP_A(COLL_DOOR);
    // RET_Z ;
    // CP_A(COLL_DOOR_79);
    // RET_Z ;
    // CP_A(COLL_STAIRCASE);
    // RET_Z ;
    // CP_A(COLL_CAVE);
    // RET;
    return a == COLL_DOOR || a == COLL_DOOR_79 || a == COLL_STAIRCASE || a == COLL_CAVE;
}

//  Return the location of map object a in bc.
struct MapObject* GetMapObject(uint8_t a){
    // LD_HL(wMapObjects);
    // LD_BC(MAPOBJECT_LENGTH);
    // CALL(aAddNTimes);
    // LD_B_H;
    // LD_C_L;
    // RET;
    return &wram->wPlayerObject + a;
}

//  Returns null if the object is not visible on the screen.
struct Object* CheckObjectVisibility(uint8_t a){
    // LDH_addr_A(hMapObjectIndex);
    // CALL(aGetMapObject);
    hram->hMapObjectIndex = a;
    struct MapObject* mobj = GetMapObject(a);
    // LD_HL(MAPOBJECT_OBJECT_STRUCT_ID);
    // ADD_HL_BC;
    // LD_A_hl;
    // CP_A(-1);
    // IF_Z goto not_visible;
    if(mobj->structId == 0xff) 
        return NULL;
    // LDH_addr_A(hObjectStructIndex);
    hram->hObjectStructIndex = mobj->structId;
    // CALL(aGetObjectStruct);
    // AND_A_A;
    // RET;
    return GetObjectStruct(mobj->structId);
}

bool CheckObjectTime(struct MapObject* bc){
    static const uint8_t TimesOfDay[] = {
        //  entries correspond to TimeOfDay values
        MORN,
        DAY,
        NITE,
    };
    // LD_HL(MAPOBJECT_HOUR);
    // ADD_HL_BC;
    // LD_A_hl;
    // CP_A(-1);
    // IF_NZ goto check_hour;
    if(bc->objectHour == 0xff) {
        // LD_HL(MAPOBJECT_TIMEOFDAY);
        // ADD_HL_BC;
        // LD_A_hl;
        // CP_A(-1);
        // IF_Z goto timeofday_always;
        if(bc->objectTimeOfDay == 0xff) {
        // timeofday_always:
            // AND_A_A;
            // RET;
            return false;
        }
        else {
            // LD_HL(mCheckObjectTime_TimesOfDay);
            // LD_A_addr(wTimeOfDay);
            // ADD_A_L;
            // LD_L_A;
            // IF_NC goto ok;
            // INC_H;


        // ok:
            // LD_A_hl;
            // LD_HL(MAPOBJECT_TIMEOFDAY);
            // ADD_HL_BC;
            // AND_A_hl;
            // IF_NZ goto timeofday_always;
            if(TimesOfDay[wram->wTimeOfDay] & bc->objectTimeOfDay)
                return false;
            // SCF;
            // RET;
            return true;
        }
    }
    else {
    // check_hour:
        // LD_HL(MAPOBJECT_HOUR);
        // ADD_HL_BC;
        // LD_D_hl;
        uint8_t d = bc->objectHour;
        // LD_HL(MAPOBJECT_TIMEOFDAY);
        // ADD_HL_BC;
        // LD_E_hl;
        uint8_t e = bc->objectTimeOfDay;
        // LD_HL(hHours);
        // LD_A_D;
        // CP_A_E;
        // IF_Z goto yes;
        if(d == e) {
            return false;
        }
        // IF_C goto check_timeofday;
        else if(d < e) {
        // check_timeofday:
            // LD_A_E;
            // CP_A_hl;
            // IF_C goto no;
            if(e < hram->hHours)
                return true;
            // LD_A_hl;
            // CP_A_D;
            // IF_NC goto yes;
            if(hram->hHours >= d)
                return false;
            // goto no;
            return true;
        }
        else {
            // LD_A_hl;
            // CP_A_D;
            // IF_NC goto yes;
            if(hram->hHours >= d)
                return false;
            // CP_A_E;
            // IF_C goto yes;
            // IF_Z goto yes;
            if(hram->hHours <= e)
                return false;
            // goto no;
            return true;
        }


    yes:
        // AND_A_A;
        // RET;
        return false;


    no:
        // SCF;
        // RET;
        return true;
    }
}

void CopyMapObjectStruct(void){
    //  //  unreferenced
    LDH_addr_A(hMapObjectIndex);
    CALL(aGetMapObject);
    CALL(aCopyObjectStruct);
    RET;

}

void UnmaskCopyMapObjectStruct(uint8_t a){
    // LDH_addr_A(hMapObjectIndex);
    // CALL(aUnmaskObject);
    UnmaskObject(a);
    // LDH_A_addr(hMapObjectIndex);
    // CALL(aGetMapObject);
    struct MapObject* bc = GetMapObject(a);
    // FARCALL(aCopyObjectStruct);
    CopyObjectStruct(bc, a);
    // RET;
}

static void ApplyDeletionToMapObject_CheckStopFollow(uint8_t a) {
    // LD_HL(wObjectFollow_Leader);
    // CP_A_hl;
    // IF_Z goto ok;
    // LD_HL(wObjectFollow_Follower);
    // CP_A_hl;
    // RET_NZ ;
    if(a != wram->wObjectFollow_Leader && a != wram->wObjectFollow_Follower)
        return;

// ok:
    // FARCALL(aStopFollow);
    StopFollow();
    // LD_A(-1);
    // LD_addr_A(wObjectFollow_Leader);
    wram->wObjectFollow_Leader = 0xff;
    // LD_addr_A(wObjectFollow_Follower);
    wram->wObjectFollow_Follower = 0xff;
    // RET;
}

void ApplyDeletionToMapObject(uint8_t mapObjIdx){
    // LDH_addr_A(hMapObjectIndex);
    hram->hMapObjectIndex = mapObjIdx;
    // CALL(aGetMapObject);
    struct MapObject* bc = GetMapObject(mapObjIdx);
    // LD_HL(MAPOBJECT_OBJECT_STRUCT_ID);
    // ADD_HL_BC;
    // LD_A_hl;
    // CP_A(-1);
    // RET_Z ;  // already hidden
    if(bc->structId == 0xff)
        return;
    // LD_hl(-1);
    uint8_t id = bc->structId;
    bc->structId = 0xff;
    // PUSH_AF;
    // CALL(aApplyDeletionToMapObject_CheckStopFollow);
    ApplyDeletionToMapObject_CheckStopFollow(id);
    // POP_AF;
    // CALL(aGetObjectStruct);
    // FARCALL(aDeleteMapObject);
    DeleteMapObject(GetObjectStruct(id));
    // RET;
}

void DeleteObjectStruct(uint8_t a){
    // CALL(aApplyDeletionToMapObject);
    ApplyDeletionToMapObject(a);
    // CALL(aMaskObject);
    MaskObject(a);
    // RET;
}

void CopyPlayerObjectTemplate(const struct ObjEvent* hl, uint8_t a){
    // PUSH_HL;
    // CALL(aGetMapObject);
    // LD_D_B;
    // LD_E_C;
    struct MapObject* de = GetMapObject(a);
    // LD_A(-1);
    // LD_de_A;
    de->structId = 0xff;
    // INC_DE;
    // POP_HL;
    // LD_BC(MAPOBJECT_LENGTH - 1);
    // CALL(aCopyBytes);
    CopyBytes(&de->sprite, hl, MAPOBJECT_LENGTH - 1);
    // RET;
}

void DeleteFollowerMapObject(void){
    //  //  unreferenced
    CALL(aGetMapObject);
    LD_HL(MAPOBJECT_OBJECT_STRUCT_ID);
    ADD_HL_BC;
    LD_A_hl;
    PUSH_AF;
    LD_hl(-1);
    INC_HL;
    LD_BC(MAPOBJECT_LENGTH - 1);
    XOR_A_A;
    CALL(aByteFill);
    POP_AF;
    CP_A(-1);
    RET_Z ;
    CP_A(NUM_OBJECT_STRUCTS);
    RET_NC ;
    LD_B_A;
    LD_A_addr(wObjectFollow_Leader);
    CP_A_B;
    IF_NZ goto ok;
    LD_A(-1);
    LD_addr_A(wObjectFollow_Leader);


ok:
        LD_A_B;
    CALL(aGetObjectStruct);
    FARCALL(aDeleteMapObject);
    RET;

}

//  Load the movement data pointer for object a.
bool LoadMovementDataPointer(uint8_t a, const uint8_t* hl){
    // LD_addr_A(wMovementObject);
    wram->wMovementObject = a;
    // LDH_A_addr(hROMBank);
    // LD_addr_A(wMovementDataBank);
    wram->wMovementDataBank = hram->hROMBank;
    // LD_A_L;
    // LD_addr_A(wMovementDataAddress);
    // LD_A_H;
    // LD_addr_A(wMovementDataAddress + 1);
    gMovementDataAddr = hl;
    // LD_A_addr(wMovementObject);
    // CALL(aCheckObjectVisibility);
    // RET_C ;
    struct Object* bc = CheckObjectVisibility(a);
    if(!bc)
        return false;

    // LD_HL(OBJECT_MOVEMENTTYPE);
    // ADD_HL_BC;
    // LD_hl(SPRITEMOVEDATA_SCRIPTED);
    bc->movementType = SPRITEMOVEDATA_SCRIPTED;

    // LD_HL(OBJECT_STEP_TYPE);
    // ADD_HL_BC;
    // LD_hl(STEP_TYPE_RESET);
    bc->stepType = STEP_TYPE_RESET;

    // LD_HL(wVramState);
    // SET_hl(7);
    bit_set(wram->wVramState, 7);
    // AND_A_A;
    // RET;
    return true;
}

//  Returns the index of the first empty object struct.
//  If all object structs are occupied, returns NULL
struct Object* FindFirstEmptyObjectStruct(void) {
    // PUSH_BC;
    // PUSH_DE;
    // LD_HL(wObjectStructs);
    // LD_DE(OBJECT_LENGTH);
    // LD_C(NUM_OBJECT_STRUCTS);
    for(uint8_t i = 0; i < NUM_OBJECT_STRUCTS; ++i) {
        // LD_A_hl;
        // AND_A_A;
        // IF_Z goto l_break;
        if((&wram->wPlayerStruct + i)->sprite == 0) {
        // l_break:
            // LD_A(NUM_OBJECT_STRUCTS);
            // SUB_A_C;
            // SCF;
            return &wram->wPlayerStruct + i;
        }
        // ADD_HL_DE;
        // DEC_C;
        // IF_NZ goto loop;
        // XOR_A_A;
        // goto done;
    }
    // POP_DE;
    // POP_BC;
    // RET;
    return NULL;
}

uint8_t GetSpriteMovementFunction(struct Object* bc){
    // LD_HL(OBJECT_MOVEMENTTYPE);
    // ADD_HL_BC;
    // LD_A_hl;
    uint8_t mvmt = bc->movementType;
    // CP_A(NUM_SPRITEMOVEDATA);
    // IF_C goto ok;
    // XOR_A_A;
    if(mvmt >= NUM_SPRITEMOVEDATA)
        mvmt = 0;

// ok:
    // LD_HL(mSpriteMovementData + SPRITEMOVEATTR_MOVEMENT);
    // LD_E_A;
    // LD_D(0);
    // for(int rept = 0; rept < NUM_SPRITEMOVEDATA_FIELDS; rept++){
    // ADD_HL_DE;
    // }
    // LD_A_hl;
    // RET;
    return SpriteMovementData[mvmt].function;
}

uint8_t GetInitialFacing(uint8_t a){
    // PUSH_BC;
    // PUSH_DE;
    // LD_E_A;
    // LD_D(0);
    // LD_HL(mSpriteMovementData + SPRITEMOVEATTR_FACING);
    // for(int rept = 0; rept < NUM_SPRITEMOVEDATA_FIELDS; rept++){
    // ADD_HL_DE;
    // }
    // LD_A(BANK(aSpriteMovementData));
    // CALL(aGetFarByte);
    // ADD_A_A;
    // ADD_A_A;
    // maskbits(NUM_DIRECTIONS, 2);
    // POP_DE;
    // POP_BC;
    // RET;
    return ((uint8_t)SpriteMovementData[a].facing << 2) & 0b1100;
}

static void CopySpriteMovementData_CopyData(struct Object* de, uint8_t a) {
    // LD_HL(OBJECT_MOVEMENTTYPE);
    // ADD_HL_DE;
    // LD_hl_A;
    de->movementType = a;

    // PUSH_DE;
    // LD_E_A;
    // LD_D(0);
    // LD_HL(mSpriteMovementData + SPRITEMOVEATTR_FACING);
    // for(int rept = 0; rept < NUM_SPRITEMOVEDATA_FIELDS; rept++){
    // ADD_HL_DE;
    // }
    // LD_B_H;
    // LD_C_L;
    // POP_DE;
    const struct SpriteMoveData* bc = &SpriteMovementData[a];

    // LD_A_bc;
    // INC_BC;
    // RLCA;
    // RLCA;
    // maskbits(NUM_DIRECTIONS, 2);
    // LD_HL(OBJECT_FACING);
    // ADD_HL_DE;
    // LD_hl_A;
    de->facing = (bc->facing << 2) & 0b1100;

    // LD_A_bc;
    // INC_BC;
    // LD_HL(OBJECT_ACTION);
    // ADD_HL_DE;
    // LD_hl_A;
    de->action = bc->action;

    // LD_A_bc;
    // INC_BC;
    // LD_HL(OBJECT_FLAGS1);
    // ADD_HL_DE;
    // LD_hl_A;
    de->flags1 = bc->flags1;

    // LD_A_bc;
    // INC_BC;
    // LD_HL(OBJECT_FLAGS2);
    // ADD_HL_DE;
    // LD_hl_A;
    de->flags2 = bc->flags2;

    // LD_A_bc;
    // INC_BC;
    // LD_HL(OBJECT_PALETTE);
    // ADD_HL_DE;
    // LD_hl_A;
    de->palette = bc->palette;
    // RET;
}

void CopySpriteMovementData(struct Object* de, uint8_t a){
    // LD_L_A;
    // LDH_A_addr(hROMBank);
    // PUSH_AF;
    // LD_A(BANK(aSpriteMovementData));
    // RST(aBankswitch);
    // LD_A_L;
    // PUSH_BC;

    // CALL(aCopySpriteMovementData_CopyData);
    CopySpriteMovementData_CopyData(de, a);

    // POP_BC;
    // POP_AF;
    // RST(aBankswitch);

    // RET;
}

uint8_t v_GetMovementByte(const uint8_t* hl, struct Object* bc){
    //  Switch to the movement data bank
    // LDH_A_addr(hROMBank);
    // PUSH_AF;
    // LD_A_hli;
    // RST(aBankswitch);
//  Load the current script byte as given by OBJECT_MOVEMENT_BYTE_INDEX, and increment OBJECT_MOVEMENT_BYTE_INDEX
    // LD_A_hli;
    // LD_D_hl;
    // LD_HL(OBJECT_MOVEMENT_BYTE_INDEX);
    // ADD_HL_BC;
    // ADD_A_hl;
    // LD_E_A;
    // LD_A_D;
    // ADC_A(0);
    // LD_D_A;
    // INC_hl;
    const uint8_t* de = hl + (bc->movementByteIndex++);
    // LD_A_de;
    // LD_H_A;
    // POP_AF;
    // RST(aBankswitch);

    // LD_A_H;
    // RET;
    return *de;
}

void SetVramState_Bit0(void){
    //  //  unreferenced
    LD_HL(wVramState);
    SET_hl(0);
    RET;

}

void ResetVramState_Bit0(void){
    //  //  unreferenced
    LD_HL(wVramState);
    RES_hl(0);
    RET;

}

void UpdateSprites(void){
    // LD_A_addr(wVramState);
    // BIT_A(0);
    // RET_Z ;
    if(!bit_test(wram->wVramState, 0))
        return;

    // FARCALL(aUpdateAllObjectsFrozen);
    UpdateAllObjectsFrozen();
    // FARCALL(av_UpdateSprites);

    v_UpdateSprites();
    // RET;

}

struct Object* GetObjectStruct(uint8_t a){
    // LD_BC(OBJECT_LENGTH);
    // LD_HL(wObjectStructs);
    // CALL(aAddNTimes);
    // LD_B_H;
    // LD_C_L;
    // RET;
    // return AddNTimes(OBJECT_LENGTH, wObjectStructs, a);
    return &wram->wPlayerStruct + a;
}

bool DoesObjectHaveASprite(struct Object* bc){
    //     LD_HL(OBJECT_SPRITE);
    // ADD_HL_BC;
    // LD_A_hl;
    // AND_A_A;
    // RET;
    return bc->sprite != 0;
}

void SetSpriteDirection(struct Object* bc, uint8_t a){
    // preserves other flags
    // PUSH_AF;
    // LD_HL(OBJECT_FACING);
    // ADD_HL_BC;
    // LD_A_hl;
    // AND_A(0b11110011);
    // LD_E_A;
    // POP_AF;
    uint8_t e = bc->facing & 0b11110011;
    // maskbits(NUM_DIRECTIONS, 2);
    // OR_A_E;
    // LD_hl_A;
    bc->facing =  e | (a & ((NUM_DIRECTIONS - 1) << 2));
    // RET;

}

uint8_t GetSpriteDirection(struct Object* bc){
    // LD_HL(OBJECT_FACING);
    // ADD_HL_BC;
    // LD_A_hl;
    // maskbits(NUM_DIRECTIONS, 2);
    return bc->facing & ((NUM_DIRECTIONS - 1) << 2);
    // RET;
}
