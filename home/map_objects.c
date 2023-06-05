#include "../constants.h"
#include "map_objects.h"
#include "../engine/overworld/map_objects.h"
#include "array.h"

//  Functions handling map objects.

void GetSpritePalette(void){
        PUSH_HL;
    PUSH_DE;
    PUSH_BC;
    LD_C_A;

    FARCALL(av_GetSpritePalette);

    LD_A_C;
    POP_BC;
    POP_DE;
    POP_HL;
    RET;

}

void GetSpriteVTile(void){
        PUSH_HL;
    PUSH_BC;
    LD_HL(wUsedSprites + 2);
    LD_C(SPRITE_GFX_LIST_CAPACITY - 1);
    LD_B_A;
    LDH_A_addr(hMapObjectIndex);
    CP_A(0);
    IF_Z goto nope;
    LD_A_B;

loop:
        CP_A_hl;
    IF_Z goto found;
    INC_HL;
    INC_HL;
    DEC_C;
    IF_NZ goto loop;
    LD_A_addr(wUsedSprites + 1);
    SCF;
    goto done;


nope:
        LD_A_addr(wUsedSprites + 1);
    goto done;


found:
        INC_HL;
    XOR_A_A;
    LD_A_hl;


done:
        POP_BC;
    POP_HL;
    RET;

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

void GetPlayerStandingTile(void){
        LD_A_addr(wPlayerStandingTile);
    CALL(aGetTileCollision);
    LD_B_A;
    RET;

}

void CheckOnWater(void){
        LD_A_addr(wPlayerStandingTile);
    CALL(aGetTileCollision);
    SUB_A(WATER_TILE);
    RET_Z ;
    AND_A_A;
    RET;

}

void GetTileCollision(void){
    //  Get the collision type of tile a.

    PUSH_DE;
    PUSH_HL;

    LD_HL(mTileCollisionTable);
    LD_E_A;
    LD_D(0);
    ADD_HL_DE;

    LDH_A_addr(hROMBank);
    PUSH_AF;
    LD_A(BANK(aTileCollisionTable));
    RST(aBankswitch);
    LD_E_hl;
    POP_AF;
    RST(aBankswitch);

    LD_A_E;
    AND_A(0xf);  // lo nybble only

    POP_HL;
    POP_DE;
    RET;

}

void CheckGrassTile(void){
        LD_D_A;
    AND_A(0xf0);
    CP_A(HI_NYBBLE_TALL_GRASS);
    IF_Z goto grass;
    CP_A(HI_NYBBLE_WATER);
    IF_Z goto water;
    SCF;
    RET;


grass:
        LD_A_D;
    AND_A(LO_NYBBLE_GRASS);
    RET_Z ;
    SCF;
    RET;
//  For some reason, the above code is duplicated down here.

water:
        LD_A_D;
    AND_A(LO_NYBBLE_GRASS);
    RET_Z ;
    SCF;
    RET;

}

void CheckSuperTallGrassTile(void){
        CP_A(COLL_LONG_GRASS);
    RET_Z ;
    CP_A(COLL_LONG_GRASS_1C);
    RET;

}

void CheckCutTreeTile(void){
        CP_A(COLL_CUT_TREE);
    RET_Z ;
    CP_A(COLL_CUT_TREE_1A);
    RET;

}

void CheckHeadbuttTreeTile(void){
        CP_A(COLL_HEADBUTT_TREE);
    RET_Z ;
    CP_A(COLL_HEADBUTT_TREE_1D);
    RET;

}

void CheckCounterTile(void){
        CP_A(COLL_COUNTER);
    RET_Z ;
    CP_A(COLL_COUNTER_98);
    RET;

}

void CheckPitTile(void){
        CP_A(COLL_PIT);
    RET_Z ;
    CP_A(COLL_PIT_68);
    RET;

}

void CheckIceTile(void){
        CP_A(COLL_ICE);
    RET_Z ;
    CP_A(COLL_ICE_2B);
    RET_Z ;
    SCF;
    RET;

}

void CheckWhirlpoolTile(void){
        NOP;
    CP_A(COLL_WHIRLPOOL);
    RET_Z ;
    CP_A(COLL_WHIRLPOOL_2C);
    RET_Z ;
    SCF;
    RET;

}

void CheckWaterfallTile(void){
        CP_A(COLL_WATERFALL);
    RET_Z ;
    CP_A(COLL_CURRENT_DOWN);
    RET;

}

void CheckStandingOnEntrance(void){
        LD_A_addr(wPlayerStandingTile);
    CP_A(COLL_DOOR);
    RET_Z ;
    CP_A(COLL_DOOR_79);
    RET_Z ;
    CP_A(COLL_STAIRCASE);
    RET_Z ;
    CP_A(COLL_CAVE);
    RET;

}

void GetMapObject(void){
    //  Return the location of map object a in bc.
    LD_HL(wMapObjects);
    LD_BC(MAPOBJECT_LENGTH);
    CALL(aAddNTimes);
    LD_B_H;
    LD_C_L;
    RET;

}

void CheckObjectVisibility(void){
    //  Sets carry if the object is not visible on the screen.
    LDH_addr_A(hMapObjectIndex);
    CALL(aGetMapObject);
    LD_HL(MAPOBJECT_OBJECT_STRUCT_ID);
    ADD_HL_BC;
    LD_A_hl;
    CP_A(-1);
    IF_Z goto not_visible;
    LDH_addr_A(hObjectStructIndex);
    CALL(aGetObjectStruct);
    AND_A_A;
    RET;


not_visible:
        SCF;
    RET;

}

void CheckObjectTime(void){
        LD_HL(MAPOBJECT_HOUR);
    ADD_HL_BC;
    LD_A_hl;
    CP_A(-1);
    IF_NZ goto check_hour;
    LD_HL(MAPOBJECT_TIMEOFDAY);
    ADD_HL_BC;
    LD_A_hl;
    CP_A(-1);
    IF_Z goto timeofday_always;
    LD_HL(mCheckObjectTime_TimesOfDay);
    LD_A_addr(wTimeOfDay);
    ADD_A_L;
    LD_L_A;
    IF_NC goto ok;
    INC_H;


ok:
        LD_A_hl;
    LD_HL(MAPOBJECT_TIMEOFDAY);
    ADD_HL_BC;
    AND_A_hl;
    IF_NZ goto timeofday_always;
    SCF;
    RET;


timeofday_always:
        AND_A_A;
    RET;


TimesOfDay:
    //  entries correspond to TimeOfDay values
    //db ['MORN'];
    //db ['DAY'];
    //db ['NITE'];


check_hour:
        LD_HL(MAPOBJECT_HOUR);
    ADD_HL_BC;
    LD_D_hl;
    LD_HL(MAPOBJECT_TIMEOFDAY);
    ADD_HL_BC;
    LD_E_hl;
    LD_HL(hHours);
    LD_A_D;
    CP_A_E;
    IF_Z goto yes;
    IF_C goto check_timeofday;
    LD_A_hl;
    CP_A_D;
    IF_NC goto yes;
    CP_A_E;
    IF_C goto yes;
    IF_Z goto yes;
    goto no;


check_timeofday:
        LD_A_E;
    CP_A_hl;
    IF_C goto no;
    LD_A_hl;
    CP_A_D;
    IF_NC goto yes;
    goto no;


yes:
        AND_A_A;
    RET;


no:
        SCF;
    RET;

}

void CopyMapObjectStruct(void){
    //  //  unreferenced
    LDH_addr_A(hMapObjectIndex);
    CALL(aGetMapObject);
    CALL(aCopyObjectStruct);
    RET;

}

void UnmaskCopyMapObjectStruct(void){
        LDH_addr_A(hMapObjectIndex);
    CALL(aUnmaskObject);
    LDH_A_addr(hMapObjectIndex);
    CALL(aGetMapObject);
    FARCALL(aCopyObjectStruct);
    RET;

}

void ApplyDeletionToMapObject(void){
        LDH_addr_A(hMapObjectIndex);
    CALL(aGetMapObject);
    LD_HL(MAPOBJECT_OBJECT_STRUCT_ID);
    ADD_HL_BC;
    LD_A_hl;
    CP_A(-1);
    RET_Z ;  // already hidden
    LD_hl(-1);
    PUSH_AF;
    CALL(aApplyDeletionToMapObject_CheckStopFollow);
    POP_AF;
    CALL(aGetObjectStruct);
    FARCALL(aDeleteMapObject);
    RET;


CheckStopFollow:
        LD_HL(wObjectFollow_Leader);
    CP_A_hl;
    IF_Z goto ok;
    LD_HL(wObjectFollow_Follower);
    CP_A_hl;
    RET_NZ ;

ok:
        FARCALL(aStopFollow);
    LD_A(-1);
    LD_addr_A(wObjectFollow_Leader);
    LD_addr_A(wObjectFollow_Follower);
    RET;

}

void DeleteObjectStruct(void){
        CALL(aApplyDeletionToMapObject);
    CALL(aMaskObject);
    RET;

}

void CopyPlayerObjectTemplate(void){
        PUSH_HL;
    CALL(aGetMapObject);
    LD_D_B;
    LD_E_C;
    LD_A(-1);
    LD_de_A;
    INC_DE;
    POP_HL;
    LD_BC(MAPOBJECT_LENGTH - 1);
    CALL(aCopyBytes);
    RET;

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

void LoadMovementDataPointer(void){
    //  Load the movement data pointer for object a.
    LD_addr_A(wMovementObject);
    LDH_A_addr(hROMBank);
    LD_addr_A(wMovementDataBank);
    LD_A_L;
    LD_addr_A(wMovementDataAddress);
    LD_A_H;
    LD_addr_A(wMovementDataAddress + 1);
    LD_A_addr(wMovementObject);
    CALL(aCheckObjectVisibility);
    RET_C ;

    LD_HL(OBJECT_MOVEMENTTYPE);
    ADD_HL_BC;
    LD_hl(SPRITEMOVEDATA_SCRIPTED);

    LD_HL(OBJECT_STEP_TYPE);
    ADD_HL_BC;
    LD_hl(STEP_TYPE_RESET);

    LD_HL(wVramState);
    SET_hl(7);
    AND_A_A;
    RET;

}

void FindFirstEmptyObjectStruct(void){
    //  Returns the index of the first empty object struct in A and its address in HL, then sets carry.
//  If all object structs are occupied, A = 0 and Z is set.
//  Preserves BC and DE.
    PUSH_BC;
    PUSH_DE;
    LD_HL(wObjectStructs);
    LD_DE(OBJECT_LENGTH);
    LD_C(NUM_OBJECT_STRUCTS);

loop:
        LD_A_hl;
    AND_A_A;
    IF_Z goto l_break;
    ADD_HL_DE;
    DEC_C;
    IF_NZ goto loop;
    XOR_A_A;
    goto done;


l_break:
        LD_A(NUM_OBJECT_STRUCTS);
    SUB_A_C;
    SCF;


done:
        POP_DE;
    POP_BC;
    RET;

}

void GetSpriteMovementFunction(void){
        LD_HL(OBJECT_MOVEMENTTYPE);
    ADD_HL_BC;
    LD_A_hl;
    CP_A(NUM_SPRITEMOVEDATA);
    IF_C goto ok;
    XOR_A_A;


ok:
        LD_HL(mSpriteMovementData + SPRITEMOVEATTR_MOVEMENT);
    LD_E_A;
    LD_D(0);
    for(int rept = 0; rept < NUM_SPRITEMOVEDATA_FIELDS; rept++){
    ADD_HL_DE;
    }
    LD_A_hl;
    RET;

}

void GetInitialFacing(void){
        PUSH_BC;
    PUSH_DE;
    LD_E_A;
    LD_D(0);
    LD_HL(mSpriteMovementData + SPRITEMOVEATTR_FACING);
    for(int rept = 0; rept < NUM_SPRITEMOVEDATA_FIELDS; rept++){
    ADD_HL_DE;
    }
    LD_A(BANK(aSpriteMovementData));
    CALL(aGetFarByte);
    ADD_A_A;
    ADD_A_A;
    maskbits(NUM_DIRECTIONS, 2);
    POP_DE;
    POP_BC;
    RET;

}

void CopySpriteMovementData(void){
        LD_L_A;
    LDH_A_addr(hROMBank);
    PUSH_AF;
    LD_A(BANK(aSpriteMovementData));
    RST(aBankswitch);
    LD_A_L;
    PUSH_BC;

    CALL(aCopySpriteMovementData_CopyData);

    POP_BC;
    POP_AF;
    RST(aBankswitch);

    RET;


CopyData:
        LD_HL(OBJECT_MOVEMENTTYPE);
    ADD_HL_DE;
    LD_hl_A;

    PUSH_DE;
    LD_E_A;
    LD_D(0);
    LD_HL(mSpriteMovementData + SPRITEMOVEATTR_FACING);
    for(int rept = 0; rept < NUM_SPRITEMOVEDATA_FIELDS; rept++){
    ADD_HL_DE;
    }
    LD_B_H;
    LD_C_L;
    POP_DE;

    LD_A_bc;
    INC_BC;
    RLCA;
    RLCA;
    maskbits(NUM_DIRECTIONS, 2);
    LD_HL(OBJECT_FACING);
    ADD_HL_DE;
    LD_hl_A;

    LD_A_bc;
    INC_BC;
    LD_HL(OBJECT_ACTION);
    ADD_HL_DE;
    LD_hl_A;

    LD_A_bc;
    INC_BC;
    LD_HL(OBJECT_FLAGS1);
    ADD_HL_DE;
    LD_hl_A;

    LD_A_bc;
    INC_BC;
    LD_HL(OBJECT_FLAGS2);
    ADD_HL_DE;
    LD_hl_A;

    LD_A_bc;
    INC_BC;
    LD_HL(OBJECT_PALETTE);
    ADD_HL_DE;
    LD_hl_A;
    RET;

}

void v_GetMovementByte(void){
    //  Switch to the movement data bank
    LDH_A_addr(hROMBank);
    PUSH_AF;
    LD_A_hli;
    RST(aBankswitch);
//  Load the current script byte as given by OBJECT_MOVEMENT_BYTE_INDEX, and increment OBJECT_MOVEMENT_BYTE_INDEX
    LD_A_hli;
    LD_D_hl;
    LD_HL(OBJECT_MOVEMENT_BYTE_INDEX);
    ADD_HL_BC;
    ADD_A_hl;
    LD_E_A;
    LD_A_D;
    ADC_A(0);
    LD_D_A;
    INC_hl;
    LD_A_de;
    LD_H_A;
    POP_AF;
    RST(aBankswitch);

    LD_A_H;
    RET;

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
        LD_A_addr(wVramState);
    BIT_A(0);
    RET_Z ;

    FARCALL(aUpdateAllObjectsFrozen);
    FARCALL(av_UpdateSprites);
    RET;

}

void UpdateSprites_Conv(void){
    // LD_A_addr(wVramState);
    // BIT_A(0);
    // RET_Z ;
    if(!((gb_read(wVramState) >> (0)) & 0x1))
        return;

    // FARCALL(aUpdateAllObjectsFrozen);
    // FARCALL(av_UpdateSprites);
    farcall(UpdateAllObjectsFrozen);
    farcall(v_UpdateSprites);
    // RET;

}

void GetObjectStruct(void){
        LD_BC(OBJECT_LENGTH);
    LD_HL(wObjectStructs);
    CALL(aAddNTimes);
    LD_B_H;
    LD_C_L;
    RET;

}

uint16_t GetObjectStruct_Conv(uint8_t a){
    // LD_BC(OBJECT_LENGTH);
    // LD_HL(wObjectStructs);
    // CALL(aAddNTimes);
    // LD_B_H;
    // LD_C_L;
    // RET;
    return AddNTimes_Conv(OBJECT_LENGTH, wObjectStructs, a);
}

void DoesObjectHaveASprite(void){
        LD_HL(OBJECT_SPRITE);
    ADD_HL_BC;
    LD_A_hl;
    AND_A_A;
    RET;

}

bool DoesObjectHaveASprite_Conv(uint16_t bc){
    //     LD_HL(OBJECT_SPRITE);
    // ADD_HL_BC;
    // LD_A_hl;
    // AND_A_A;
    // RET;
    return gb_read(OBJECT_SPRITE + bc) != 0;
}

void SetSpriteDirection(void){
    // preserves other flags
    PUSH_AF;
    LD_HL(OBJECT_FACING);
    ADD_HL_BC;
    LD_A_hl;
    AND_A(0b11110011);
    LD_E_A;
    POP_AF;
    maskbits(NUM_DIRECTIONS, 2);
    OR_A_E;
    LD_hl_A;
    RET;

}

void SetSpriteDirection_Conv(uint16_t bc, uint8_t a){
    // preserves other flags
    // PUSH_AF;
    // LD_HL(OBJECT_FACING);
    // ADD_HL_BC;
    // LD_A_hl;
    // AND_A(0b11110011);
    // LD_E_A;
    // POP_AF;
    uint8_t e = gb_read(bc + OBJECT_FACING) & 0b11110011;
    // maskbits(NUM_DIRECTIONS, 2);
    // OR_A_E;
    // LD_hl_A;
    gb_write(bc + OBJECT_FACING, e | (a & ((NUM_DIRECTIONS - 1) << 2)));
    // RET;

}

void GetSpriteDirection(void){
        LD_HL(OBJECT_FACING);
    ADD_HL_BC;
    LD_A_hl;
    maskbits(NUM_DIRECTIONS, 2);
    RET;

}

uint8_t GetSpriteDirection_Conv(uint16_t bc){
    // LD_HL(OBJECT_FACING);
    // ADD_HL_BC;
    // LD_A_hl;
    return gb_read(bc + OBJECT_FACING) & ((NUM_DIRECTIONS - 1) << 2);
    // maskbits(NUM_DIRECTIONS, 2);
    // RET;

}
