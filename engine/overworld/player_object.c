#include "../../constants.h"
#include "player_object.h"
#include "../../home/map_objects.h"
#include "../../home/map.h"
#include "../../home/copy.h"

void BlankScreen(void){
    CALL(aDisableSpriteUpdates);
    XOR_A_A;
    LDH_addr_A(hBGMapMode);
    CALL(aClearBGPalettes);
    CALL(aClearSprites);
    hlcoord(0, 0, wTilemap);
    LD_BC(wTilemapEnd - wTilemap);
    LD_A(0x7f);
    CALL(aByteFill);
    hlcoord(0, 0, wAttrmap);
    LD_BC(wAttrmapEnd - wAttrmap);
    LD_A(0x7);
    CALL(aByteFill);
    CALL(aWaitBGMap2);
    CALL(aSetPalettes);
    RET;

}

void SpawnPlayer(void){
    // LD_A(-1);
    // LD_addr_A(wObjectFollow_Leader);
    wram->wObjectFollow_Leader = 0xff;
    // LD_addr_A(wObjectFollow_Follower);
    wram->wObjectFollow_Follower = 0xff;
    // LD_A(PLAYER);
    // LD_HL(mPlayerObjectTemplate);
    // CALL(aCopyPlayerObjectTemplate);
    CopyPlayerObjectTemplate_Conv(&PlayerObjectTemplate, PLAYER);
    // LD_B(PLAYER);
    // CALL(aPlayerSpawn_ConvertCoords);
    PlayerSpawn_ConvertCoords_Conv(PLAYER);
    // LD_A(PLAYER_OBJECT);
    // CALL(aGetMapObject);
    struct MapObject* bc = GetMapObject_Conv(PLAYER_OBJECT);
    // LD_HL(MAPOBJECT_COLOR);
    // ADD_HL_BC;
    // LD_E((PAL_NPC_RED << 4) | OBJECTTYPE_SCRIPT);
    // LD_A_addr(wPlayerSpriteSetupFlags);
    // BIT_A(PLAYERSPRITESETUP_FEMALE_TO_MALE_F);
    // IF_NZ goto ok;
    // LD_A_addr(wPlayerGender);
    // BIT_A(PLAYERGENDER_FEMALE_F);
    // IF_Z goto ok;
    // LD_E((PAL_NPC_BLUE << 4) | OBJECTTYPE_SCRIPT);


// ok:
    // LD_hl_E;
    bc->objectColor = 
        (bit_test(wram->wPlayerSpriteSetupFlags, PLAYERSPRITESETUP_FEMALE_TO_MALE_F) || !bit_test(wram->wPlayerGender, PLAYERGENDER_FEMALE_F))
            ? (PAL_NPC_RED << 4) | OBJECTTYPE_SCRIPT
            : (PAL_NPC_BLUE << 4) | OBJECTTYPE_SCRIPT;
    // LD_A(PLAYER_OBJECT);
    // LDH_addr_A(hMapObjectIndex);
    // LD_BC(wMapObjects);
    // LD_A(PLAYER_OBJECT);
    // LDH_addr_A(hObjectStructIndex);
    // LD_DE(wObjectStructs);
    // CALL(aCopyMapObjectToObjectStruct);
    CopyMapObjectToObjectStruct_Conv(wram->wObjectStruct, (struct MapObject*)wram_ptr(wMapObjects), PLAYER_OBJECT, PLAYER_OBJECT);
    // LD_A(PLAYER);
    // LD_addr_A(wCenteredObject);
    wram->wCenteredObject = PLAYER;
    // RET;
}

//  A dummy map object used to initialize the player object.
//  Shorter than the actual amount copied by two bytes.
//  Said bytes seem to be unused.
const struct ObjEvent PlayerObjectTemplate = object_event(-4, -4, SPRITE_CHRIS, SPRITEMOVEDATA_PLAYER, 15, 15, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, 0, -1);

void CopyDECoordsToMapObject(void){
    PUSH_DE;
    LD_A_B;
    CALL(aGetMapObject);
    POP_DE;
    LD_HL(MAPOBJECT_X_COORD);
    ADD_HL_BC;
    LD_hl_D;
    LD_HL(MAPOBJECT_Y_COORD);
    ADD_HL_BC;
    LD_hl_E;
    RET;

}

void CopyDECoordsToMapObject_Conv(uint8_t d, uint8_t e, uint8_t b){
    // PUSH_DE;
    // LD_A_B;
    // CALL(aGetMapObject);
    struct MapObject* bc = GetMapObject_Conv(b);
    // POP_DE;
    // LD_HL(MAPOBJECT_X_COORD);
    // ADD_HL_BC;
    // LD_hl_D;
    bc->objectXCoord = d;
    // LD_HL(MAPOBJECT_Y_COORD);
    // ADD_HL_BC;
    // LD_hl_E;
    bc->objectYCoord = e;
    // RET;
}

void PlayerSpawn_ConvertCoords(void){
    PUSH_BC;
    LD_A_addr(wXCoord);
    ADD_A(4);
    LD_D_A;
    LD_A_addr(wYCoord);
    ADD_A(4);
    LD_E_A;
    POP_BC;
    CALL(aCopyDECoordsToMapObject);
    RET;

}

void PlayerSpawn_ConvertCoords_Conv(uint8_t b){
    // PUSH_BC;
    // LD_A_addr(wXCoord);
    // ADD_A(4);
    // LD_D_A;
    // LD_A_addr(wYCoord);
    // ADD_A(4);
    // LD_E_A;
    // POP_BC;
    // CALL(aCopyDECoordsToMapObject);
    // RET;
    return CopyDECoordsToMapObject_Conv(wram->wXCoord + 4, wram->wYCoord + 4, b);
}

void WriteObjectXY(void){
    LD_A_B;
    CALL(aCheckObjectVisibility);
    RET_C ;

    LD_HL(OBJECT_NEXT_MAP_X);
    ADD_HL_BC;
    LD_D_hl;
    LD_HL(OBJECT_NEXT_MAP_Y);
    ADD_HL_BC;
    LD_E_hl;
    LDH_A_addr(hMapObjectIndex);
    LD_B_A;
    CALL(aCopyDECoordsToMapObject);
    AND_A_A;
    RET;

}

void WriteObjectXY_Conv(uint8_t b){
    // LD_A_B;
    // CALL(aCheckObjectVisibility);
    struct Object* bc = CheckObjectVisibility_Conv(b);
    if(bc == NULL)
        return;
    // RET_C ;

    // LD_HL(OBJECT_NEXT_MAP_X);
    // ADD_HL_BC;
    // LD_D_hl;
    // LD_HL(OBJECT_NEXT_MAP_Y);
    // ADD_HL_BC;
    // LD_E_hl;
    // LDH_A_addr(hMapObjectIndex);
    // LD_B_A;
    // CALL(aCopyDECoordsToMapObject);
    CopyDECoordsToMapObject_Conv(bc->nextMapX, bc->nextMapY, hram->hMapObjectIndex);
    // AND_A_A;
    // RET;
}

void RefreshPlayerCoords(void){
    // LD_A_addr(wXCoord);
    // ADD_A(4);
    // LD_D_A;
    uint8_t x = wram->wXCoord + 4;
    // LD_HL(wPlayerStandingMapX);
    // SUB_A_hl;
    // uint8_t d = x - wram->wPlayerStruct.nextMapX;
    // LD_hl_D;
    wram->wPlayerStruct.nextMapX = x;
    // LD_HL(wMapObjects + MAPOBJECT_X_COORD);
    // LD_hl_D;
    wram->wMapObject[0].objectXCoord = x;
    // LD_HL(wPlayerLastMapX);
    // LD_hl_D;
    wram->wPlayerStruct.mapX = x;
    // LD_D_A;
    // LD_A_addr(wYCoord);
    // ADD_A(4);
    // LD_E_A;
    uint8_t y = wram->wYCoord + 4;
    // LD_HL(wPlayerStandingMapY);
    // SUB_A_hl;
    // uint8_t e = x - wram->wPlayerStruct.nextMapY;
    // LD_hl_E;
    wram->wPlayerStruct.nextMapY = y;
    // LD_HL(wMapObjects + MAPOBJECT_Y_COORD);
    // LD_hl_E;
    wram->wMapObject[0].objectYCoord = y;
    // LD_HL(wPlayerLastMapY);
    // LD_hl_E;
    wram->wPlayerStruct.mapY = x;
    // LD_E_A;
//  the next three lines are useless
    // LD_A_addr(wObjectFollow_Leader);
    // CP_A(PLAYER);
    // RET_NZ ;
    // RET;
}

void CopyObjectStruct(void){
    CALL(aCheckObjectMask);
    AND_A_A;
    RET_NZ ;  // masked

    LD_HL(wObjectStructs + OBJECT_LENGTH * 1);
    LD_A(1);
    LD_DE(OBJECT_LENGTH);

loop:
    LDH_addr_A(hObjectStructIndex);
    LD_A_hl;
    AND_A_A;
    IF_Z goto done;
    ADD_HL_DE;
    LDH_A_addr(hObjectStructIndex);
    INC_A;
    CP_A(NUM_OBJECT_STRUCTS);
    IF_NZ goto loop;
    SCF;
    RET;  // overflow


done:
    LD_D_H;
    LD_E_L;
    CALL(aCopyMapObjectToObjectStruct);
    LD_HL(wVramState);
    BIT_hl(7);
    RET_Z ;

    LD_HL(OBJECT_FLAGS2);
    ADD_HL_DE;
    SET_hl(5);
    RET;

}

uint8_t CopyObjectStruct_Conv(struct MapObject* bc, uint8_t a){
    // CALL(aCheckObjectMask);
    // AND_A_A;
    // RET_NZ ;  // masked
    if(CheckObjectMask_Conv(a) != 0)
        return 1;

    // LD_HL(wObjectStructs + OBJECT_LENGTH * 1);
    // LD_A(1);
    // LD_DE(OBJECT_LENGTH);
    struct Object* hl = wram->wObjectStruct;
    uint8_t b = 1;

    do {
    // loop:
        // LDH_addr_A(hObjectStructIndex);
        // LD_A_hl;
        // AND_A_A;
        // IF_Z goto done;
        if(hl->sprite == 0) {
        // done:
            // LD_D_H;
            // LD_E_L;
            // CALL(aCopyMapObjectToObjectStruct);
            CopyMapObjectToObjectStruct_Conv(hl, bc, a, b);
            // LD_HL(wVramState);
            // BIT_hl(7);
            // RET_Z ;
            if(!bit_test(wram->wVramState, 7))
                return 0;

            // LD_HL(OBJECT_FLAGS2);
            // ADD_HL_DE;
            // SET_hl(5);
            bit_set(hl->flags2, 5);
            // RET;
            return 0;
        }
        // ADD_HL_DE;
        // LDH_A_addr(hObjectStructIndex);
        // INC_A;
        // CP_A(NUM_OBJECT_STRUCTS);
        // IF_NZ goto loop;
    } while(hl++, ++b < NUM_OBJECT_STRUCTS);
    // SCF;
    // RET;  // overflow
    return 0xff;
}

void CopyMapObjectToObjectStruct(void){
    CALL(aCopyMapObjectToObjectStruct_CopyMapObjectToTempObject);
    CALL(aCopyTempObjectToObjectStruct);
    RET;


CopyMapObjectToTempObject:
    LDH_A_addr(hObjectStructIndex);
    LD_HL(MAPOBJECT_OBJECT_STRUCT_ID);
    ADD_HL_BC;
    LD_hl_A;

    LDH_A_addr(hMapObjectIndex);
    LD_addr_A(wTempObjectCopyMapObjectIndex);

    LD_HL(MAPOBJECT_SPRITE);
    ADD_HL_BC;
    LD_A_hl;
    LD_addr_A(wTempObjectCopySprite);

    CALL(aGetSpriteVTile);
    LD_addr_A(wTempObjectCopySpriteVTile);

    LD_A_hl;
    CALL(aGetSpritePalette);
    LD_addr_A(wTempObjectCopyPalette);

    LD_HL(MAPOBJECT_COLOR);
    ADD_HL_BC;
    LD_A_hl;
    AND_A(0xf0);
    IF_Z goto skip_color_override;
    SWAP_A;
    AND_A(PALETTE_MASK);
    LD_addr_A(wTempObjectCopyPalette);


skip_color_override:
    LD_HL(MAPOBJECT_MOVEMENT);
    ADD_HL_BC;
    LD_A_hl;
    LD_addr_A(wTempObjectCopyMovement);

    LD_HL(MAPOBJECT_RANGE);
    ADD_HL_BC;
    LD_A_hl;
    LD_addr_A(wTempObjectCopyRange);

    LD_HL(MAPOBJECT_X_COORD);
    ADD_HL_BC;
    LD_A_hl;
    LD_addr_A(wTempObjectCopyX);

    LD_HL(MAPOBJECT_Y_COORD);
    ADD_HL_BC;
    LD_A_hl;
    LD_addr_A(wTempObjectCopyY);

    LD_HL(MAPOBJECT_RADIUS);
    ADD_HL_BC;
    LD_A_hl;
    LD_addr_A(wTempObjectCopyRadius);
    RET;

}

static void CopyMapObjectToObjectStruct_CopyMapObjectToTempObject_Conv(struct MapObject* bc, uint8_t objIdx, uint8_t mapObjIdx) {
// CopyMapObjectToTempObject:
    // LDH_A_addr(hObjectStructIndex);
    // LD_HL(MAPOBJECT_OBJECT_STRUCT_ID);
    // ADD_HL_BC;
    // LD_hl_A;
    bc->structId = objIdx;

    // LDH_A_addr(hMapObjectIndex);
    // LD_addr_A(wTempObjectCopyMapObjectIndex);
    wram->wTempObjectCopyMapObjectIndex = mapObjIdx;

    // LD_HL(MAPOBJECT_SPRITE);
    // ADD_HL_BC;
    // LD_A_hl;
    // LD_addr_A(wTempObjectCopySprite);
    wram->wTempObjectCopySprite = bc->sprite;

    // CALL(aGetSpriteVTile);
    // LD_addr_A(wTempObjectCopySpriteVTile);
    wram->wTempObjectCopySpriteVTile = GetSpriteVTile_Conv(bc->sprite, mapObjIdx);

    // LD_A_hl;
    // CALL(aGetSpritePalette);
    // LD_addr_A(wTempObjectCopyPalette);
    wram->wTempObjectCopyPalette = GetSpritePalette_Conv(bc->sprite);

    // LD_HL(MAPOBJECT_COLOR);
    // ADD_HL_BC;
    // LD_A_hl;
    // AND_A(0xf0);
    // IF_Z goto skip_color_override;
    // SWAP_A;
    // AND_A(PALETTE_MASK);
    // LD_addr_A(wTempObjectCopyPalette);
    if(bc->objectColor & 0xf0) {
        wram->wTempObjectCopyPalette = (bc->objectColor >> 4) & PALETTE_MASK;
    }

// skip_color_override:
    // LD_HL(MAPOBJECT_MOVEMENT);
    // ADD_HL_BC;
    // LD_A_hl;
    // LD_addr_A(wTempObjectCopyMovement);
    wram->wTempObjectCopyMovement = bc->objectMovement;

    // LD_HL(MAPOBJECT_RANGE);
    // ADD_HL_BC;
    // LD_A_hl;
    // LD_addr_A(wTempObjectCopyRange);
    wram->wTempObjectCopyRange = bc->objectRange;

    // LD_HL(MAPOBJECT_X_COORD);
    // ADD_HL_BC;
    // LD_A_hl;
    // LD_addr_A(wTempObjectCopyX);
    wram->wTempObjectCopyX = bc->objectXCoord;

    // LD_HL(MAPOBJECT_Y_COORD);
    // ADD_HL_BC;
    // LD_A_hl;
    // LD_addr_A(wTempObjectCopyY);
    wram->wTempObjectCopyY = bc->objectYCoord;

    // LD_HL(MAPOBJECT_RADIUS);
    // ADD_HL_BC;
    // LD_A_hl;
    // LD_addr_A(wTempObjectCopyRadius);
    wram->wTempObjectCopyRadius = bc->objectRadius;
    // RET;
}

void CopyMapObjectToObjectStruct_Conv(struct Object* de, struct MapObject* bc, uint8_t mapObjIdx, uint8_t objIdx){
    // CALL(aCopyMapObjectToObjectStruct_CopyMapObjectToTempObject);
    CopyMapObjectToObjectStruct_CopyMapObjectToTempObject_Conv(bc, objIdx, mapObjIdx);
    // CALL(aCopyTempObjectToObjectStruct);
    CopyTempObjectToObjectStruct_Conv(de);
    // RET;
}

void InitializeVisibleSprites(void){
    // LD_BC(wMap1Object);
    struct MapObject* bc = (struct MapObject*)wram_ptr(wMapObjects);
    // LD_A(1);
    uint8_t a = 1;

    do {
    // loop:
        // LDH_addr_A(hMapObjectIndex);
        // LD_HL(MAPOBJECT_SPRITE);
        // ADD_HL_BC;
        // LD_A_hl;
        // AND_A_A;
        // IF_Z goto next;
        if(bc[a - 1].sprite == 0)
            continue;

        // LD_HL(MAPOBJECT_OBJECT_STRUCT_ID);
        // ADD_HL_BC;
        // LD_A_hl;
        // CP_A(-1);
        // IF_NZ goto next;
        if(bc[a - 1].structId == 0xff)
            continue;

        // LD_A_addr(wXCoord);
        // LD_D_A;
        uint8_t d = wram->wXCoord;
        // LD_A_addr(wYCoord);
        // LD_E_A;
        uint8_t e = wram->wYCoord;

        // LD_HL(MAPOBJECT_X_COORD);
        // ADD_HL_BC;
        // LD_A_hl;
        // ADD_A(1);
        uint8_t x = bc[a - 1].objectXCoord + 1;
        // SUB_A_D;
        // IF_C goto next;
        if(x < d)
            continue;

        // CP_A(MAPOBJECT_SCREEN_WIDTH);
        // IF_NC goto next;
        if(x >= MAPOBJECT_SCREEN_WIDTH)
            continue;

        // LD_HL(MAPOBJECT_Y_COORD);
        // ADD_HL_BC;
        // LD_A_hl;
        // ADD_A(1);
        uint8_t y = bc[a - 1].objectYCoord + 1;
        // SUB_A_E;
        // IF_C goto next;
        if(y < e)
            continue;

        // CP_A(MAPOBJECT_SCREEN_HEIGHT);
        // IF_NC goto next;
        if(y >= MAPOBJECT_SCREEN_HEIGHT)
            continue;

        // PUSH_BC;
        // CALL(aCopyObjectStruct);
        uint8_t res = CopyObjectStruct_Conv(bc + (a - 1), a);
        // POP_BC;
        // JP_C (mInitializeVisibleSprites_ret);
        if(res == 0xff)
            return;



    // next:
        // LD_HL(MAPOBJECT_LENGTH);
        // ADD_HL_BC;
        // LD_B_H;
        // LD_C_L;
        // LDH_A_addr(hMapObjectIndex);
        // INC_A;
        // CP_A(NUM_OBJECTS);
        // IF_NZ goto loop;
    } while(++a != NUM_OBJECTS);
    // RET;


// ret:
    // RET;
}

void CheckObjectEnteringVisibleRange(void){
    // NOP;
    // LD_A_addr(wPlayerStepDirection);
    // CP_A(STANDING);
    // RET_Z ;
    if(wram->wPlayerStepDirection == (uint8_t)STANDING)
        return;
    // LD_HL(mCheckObjectEnteringVisibleRange_dw);
    // RST(aJumpTable);
    switch(wram->wPlayerStepDirection) {
        case DOWN: goto Down;
        case UP: goto Up;
        case LEFT: goto Left;
        case RIGHT: goto Right;
    }
    RET;

dw:
    //dw ['.Down'];
    //dw ['.Up'];
    //dw ['.Left'];
    //dw ['.Right'];


Up:
    LD_A_addr(wYCoord);
    SUB_A(1);
    goto Vertical;


Down:
    LD_A_addr(wYCoord);
    ADD_A(9);

Vertical:
    LD_D_A;
    LD_A_addr(wXCoord);
    LD_E_A;
    LD_BC(wMap1Object);
    LD_A(1);

loop_v:
    LDH_addr_A(hMapObjectIndex);
    LD_HL(MAPOBJECT_SPRITE);
    ADD_HL_BC;
    LD_A_hl;
    AND_A_A;
    IF_Z goto next_v;
    LD_HL(MAPOBJECT_Y_COORD);
    ADD_HL_BC;
    LD_A_D;
    CP_A_hl;
    IF_NZ goto next_v;
    LD_HL(MAPOBJECT_OBJECT_STRUCT_ID);
    ADD_HL_BC;
    LD_A_hl;
    CP_A(-1);
    IF_NZ goto next_v;
    LD_HL(MAPOBJECT_X_COORD);
    ADD_HL_BC;
    LD_A_hl;
    ADD_A(1);
    SUB_A_E;
    IF_C goto next_v;
    CP_A(MAPOBJECT_SCREEN_WIDTH);
    IF_NC goto next_v;
    PUSH_DE;
    PUSH_BC;
    CALL(aCopyObjectStruct);
    POP_BC;
    POP_DE;


next_v:
    LD_HL(MAPOBJECT_LENGTH);
    ADD_HL_BC;
    LD_B_H;
    LD_C_L;
    LDH_A_addr(hMapObjectIndex);
    INC_A;
    CP_A(NUM_OBJECTS);
    IF_NZ goto loop_v;
    RET;


Left:
    LD_A_addr(wXCoord);
    SUB_A(1);
    goto Horizontal;


Right:
    LD_A_addr(wXCoord);
    ADD_A(10);

Horizontal:
    LD_E_A;
    LD_A_addr(wYCoord);
    LD_D_A;
    LD_BC(wMap1Object);
    LD_A(1);

loop_h:
    LDH_addr_A(hMapObjectIndex);
    LD_HL(MAPOBJECT_SPRITE);
    ADD_HL_BC;
    LD_A_hl;
    AND_A_A;
    IF_Z goto next_h;
    LD_HL(MAPOBJECT_X_COORD);
    ADD_HL_BC;
    LD_A_E;
    CP_A_hl;
    IF_NZ goto next_h;
    LD_HL(MAPOBJECT_OBJECT_STRUCT_ID);
    ADD_HL_BC;
    LD_A_hl;
    CP_A(-1);
    IF_NZ goto next_h;
    LD_HL(MAPOBJECT_Y_COORD);
    ADD_HL_BC;
    LD_A_hl;
    ADD_A(1);
    SUB_A_D;
    IF_C goto next_h;
    CP_A(MAPOBJECT_SCREEN_HEIGHT);
    IF_NC goto next_h;
    PUSH_DE;
    PUSH_BC;
    CALL(aCopyObjectStruct);
    POP_BC;
    POP_DE;


next_h:
    LD_HL(MAPOBJECT_LENGTH);
    ADD_HL_BC;
    LD_B_H;
    LD_C_L;
    LDH_A_addr(hMapObjectIndex);
    INC_A;
    CP_A(NUM_OBJECTS);
    IF_NZ goto loop_h;
    RET;

}

void CopyTempObjectToObjectStruct(void){
    LD_A_addr(wTempObjectCopyMapObjectIndex);
    LD_HL(OBJECT_MAP_OBJECT_INDEX);
    ADD_HL_DE;
    LD_hl_A;

    LD_A_addr(wTempObjectCopyMovement);
    CALL(aCopySpriteMovementData);

    LD_A_addr(wTempObjectCopyPalette);
    LD_HL(OBJECT_PALETTE);
    ADD_HL_DE;
    OR_A_hl;
    LD_hl_A;

    LD_A_addr(wTempObjectCopyY);
    CALL(aCopyTempObjectToObjectStruct_InitYCoord);

    LD_A_addr(wTempObjectCopyX);
    CALL(aCopyTempObjectToObjectStruct_InitXCoord);

    LD_A_addr(wTempObjectCopySprite);
    LD_HL(OBJECT_SPRITE);
    ADD_HL_DE;
    LD_hl_A;

    LD_A_addr(wTempObjectCopySpriteVTile);
    LD_HL(OBJECT_SPRITE_TILE);
    ADD_HL_DE;
    LD_hl_A;

    LD_HL(OBJECT_STEP_TYPE);
    ADD_HL_DE;
    LD_hl(STEP_TYPE_RESET);

    LD_HL(OBJECT_FACING_STEP);
    ADD_HL_DE;
    LD_hl(STANDING);

    LD_A_addr(wTempObjectCopyRadius);
    CALL(aCopyTempObjectToObjectStruct_InitRadius);

    LD_A_addr(wTempObjectCopyRange);
    LD_HL(OBJECT_RANGE);
    ADD_HL_DE;
    LD_hl_A;

    AND_A_A;
    RET;


InitYCoord:
    LD_HL(OBJECT_INIT_Y);
    ADD_HL_DE;
    LD_hl_A;

    LD_HL(OBJECT_NEXT_MAP_Y);
    ADD_HL_DE;
    LD_hl_A;

    LD_HL(wYCoord);
    SUB_A_hl;
    AND_A(0xf);
    SWAP_A;
    LD_HL(wPlayerBGMapOffsetY);
    SUB_A_hl;
    LD_HL(OBJECT_SPRITE_Y);
    ADD_HL_DE;
    LD_hl_A;
    RET;


InitXCoord:
    LD_HL(OBJECT_INIT_X);
    ADD_HL_DE;
    LD_hl_A;
    LD_HL(OBJECT_NEXT_MAP_X);
    ADD_HL_DE;
    LD_hl_A;
    LD_HL(wXCoord);
    SUB_A_hl;
    AND_A(0xf);
    SWAP_A;
    LD_HL(wPlayerBGMapOffsetX);
    SUB_A_hl;
    LD_HL(OBJECT_SPRITE_X);
    ADD_HL_DE;
    LD_hl_A;
    RET;


InitRadius:
    LD_H_A;
    INC_A;
    AND_A(0xf);
    LD_L_A;
    LD_A_H;
    ADD_A(0x10);
    AND_A(0xf0);
    OR_A_L;
    LD_HL(OBJECT_RADIUS);
    ADD_HL_DE;
    LD_hl_A;
    RET;

}

static void CopyTempObjectToObjectStruct_InitYCoord(struct Object* de, uint8_t a) {
    // LD_HL(OBJECT_INIT_Y);
    // ADD_HL_DE;
    // LD_hl_A;
    de->initY = a;

    // LD_HL(OBJECT_NEXT_MAP_Y);
    // ADD_HL_DE;
    // LD_hl_A;
    de->nextMapY = a;

    // LD_HL(wYCoord);
    // SUB_A_hl;
    // AND_A(0xf);
    // SWAP_A;
    // LD_HL(wPlayerBGMapOffsetY);
    // SUB_A_hl;
    // LD_HL(OBJECT_SPRITE_Y);
    // ADD_HL_DE;
    // LD_hl_A;
    de->spriteY = (((a - wram->wYCoord) & 0xf) << 4) - wram->wPlayerBGMapOffsetY;
    // RET;
}

static void CopyTempObjectToObjectStruct_InitXCoord(struct Object* de, uint8_t a) {
    // LD_HL(OBJECT_INIT_X);
    // ADD_HL_DE;
    // LD_hl_A;
    de->initX = a;
    // LD_HL(OBJECT_NEXT_MAP_X);
    // ADD_HL_DE;
    // LD_hl_A;
    de->nextMapX = a;
    // LD_HL(wXCoord);
    // SUB_A_hl;
    // AND_A(0xf);
    // SWAP_A;
    // LD_HL(wPlayerBGMapOffsetX);
    // SUB_A_hl;
    // LD_HL(OBJECT_SPRITE_X);
    // ADD_HL_DE;
    // LD_hl_A;
    de->spriteX = (((a - wram->wXCoord) & 0xf) << 4) - wram->wPlayerBGMapOffsetX;
    // RET;
}

static void CopyTempObjectToObjectStruct_InitRadius(struct Object* de, uint8_t a) {
    uint8_t h;
    // LD_H_A;
    // INC_A;
    // AND_A(0xf);
    // LD_L_A;
    h = (a + 1) & 0xf;
    // LD_A_H;
    // ADD_A(0x10);
    // AND_A(0xf0);
    // OR_A_L;
    h = h | ((a + 0x10) & 0xf0);
    // LD_HL(OBJECT_RADIUS);
    // ADD_HL_DE;
    // LD_hl_A;
    de->radius = h;
    // RET;
}

void CopyTempObjectToObjectStruct_Conv(struct Object* de){
    // LD_A_addr(wTempObjectCopyMapObjectIndex);
    // LD_HL(OBJECT_MAP_OBJECT_INDEX);
    // ADD_HL_DE;
    // LD_hl_A;
    de->mapObjectIndex = wram->wTempObjectCopyMapObjectIndex;

    // LD_A_addr(wTempObjectCopyMovement);
    // CALL(aCopySpriteMovementData);
    CopySpriteMovementData_Conv(de, wram->wTempObjectCopyMovement);

    // LD_A_addr(wTempObjectCopyPalette);
    // LD_HL(OBJECT_PALETTE);
    // ADD_HL_DE;
    // OR_A_hl;
    // LD_hl_A;
    de->palette |= wram->wTempObjectCopyPalette;

    // LD_A_addr(wTempObjectCopyY);
    // CALL(aCopyTempObjectToObjectStruct_InitYCoord);
    CopyTempObjectToObjectStruct_InitYCoord(de, wram->wTempObjectCopyY);

    // LD_A_addr(wTempObjectCopyX);
    // CALL(aCopyTempObjectToObjectStruct_InitXCoord);
    CopyTempObjectToObjectStruct_InitXCoord(de, wram->wTempObjectCopyX);

    // LD_A_addr(wTempObjectCopySprite);
    // LD_HL(OBJECT_SPRITE);
    // ADD_HL_DE;
    // LD_hl_A;
    de->sprite = wram->wTempObjectCopySprite;

    // LD_A_addr(wTempObjectCopySpriteVTile);
    // LD_HL(OBJECT_SPRITE_TILE);
    // ADD_HL_DE;
    // LD_hl_A;
    de->spriteTile = wram->wTempObjectCopySpriteVTile;

    // LD_HL(OBJECT_STEP_TYPE);
    // ADD_HL_DE;
    // LD_hl(STEP_TYPE_RESET);
    de->stepType = STEP_TYPE_RESET;

    // LD_HL(OBJECT_FACING_STEP);
    // ADD_HL_DE;
    // LD_hl(STANDING);
    de->facingStep = STANDING;

    // LD_A_addr(wTempObjectCopyRadius);
    // CALL(aCopyTempObjectToObjectStruct_InitRadius);
    CopyTempObjectToObjectStruct_InitRadius(de, wram->wTempObjectCopyRadius);

    // LD_A_addr(wTempObjectCopyRange);
    // LD_HL(OBJECT_RANGE);
    // ADD_HL_DE;
    // LD_hl_A;
    de->range = wram->wTempObjectCopyRange;

    // AND_A_A;
    // RET;
}

void TrainerWalkToPlayer(void){
    LDH_A_addr(hLastTalked);
    CALL(aInitMovementBuffer);
    LD_A(movement_step_sleep);
    CALL(aAppendToMovementBuffer);
    LD_A_addr(wWalkingIntoNPC);
    DEC_A;
    IF_Z goto TerminateStep;
    LDH_A_addr(hLastTalked);
    LD_B_A;
    LD_C(PLAYER);
    LD_D(1);
    CALL(aTrainerWalkToPlayer_GetPathToPlayer);
    CALL(aDecrementMovementBufferCount);


TerminateStep:
    LD_A(movement_step_end);
    CALL(aAppendToMovementBuffer);
    RET;


GetPathToPlayer:
    PUSH_DE;
    PUSH_BC;
//  get player object struct, load to de
    LD_A_C;
    CALL(aGetMapObject);
    LD_HL(MAPOBJECT_OBJECT_STRUCT_ID);
    ADD_HL_BC;
    LD_A_hl;
    CALL(aGetObjectStruct);
    LD_D_B;
    LD_E_C;

//  get last talked object struct, load to bc
    POP_BC;
    LD_A_B;
    CALL(aGetMapObject);
    LD_HL(MAPOBJECT_OBJECT_STRUCT_ID);
    ADD_HL_BC;
    LD_A_hl;
    CALL(aGetObjectStruct);

//  get last talked coords, load to bc
    LD_HL(OBJECT_NEXT_MAP_X);
    ADD_HL_BC;
    LD_A_hl;
    LD_HL(OBJECT_NEXT_MAP_Y);
    ADD_HL_BC;
    LD_C_hl;
    LD_B_A;

//  get player coords, load to de
    LD_HL(OBJECT_NEXT_MAP_X);
    ADD_HL_DE;
    LD_A_hl;
    LD_HL(OBJECT_NEXT_MAP_Y);
    ADD_HL_DE;
    LD_E_hl;
    LD_D_A;

    POP_AF;
    CALL(aComputePathToWalkToPlayer);
    RET;

}

void SurfStartStep(void){
    CALL(aInitMovementBuffer);
    CALL(aSurfStartStep_GetMovementData);
    CALL(aAppendToMovementBuffer);
    LD_A(movement_step_end);
    CALL(aAppendToMovementBuffer);
    RET;


GetMovementData:
    LD_A_addr(wPlayerDirection);
    SRL_A;
    SRL_A;
    maskbits(NUM_DIRECTIONS, 0);
    LD_E_A;
    LD_D(0);
    LD_HL(mSurfStartStep_movement_data);
    ADD_HL_DE;
    LD_A_hl;
    RET;


movement_data:
    //slow_step ['DOWN']
    //slow_step ['UP']
    //slow_step ['LEFT']
    //slow_step ['RIGHT']

    return FollowNotExact();
}

void FollowNotExact(void){
    PUSH_BC;
    LD_A_C;
    CALL(aCheckObjectVisibility);
    LD_D_B;
    LD_E_C;
    POP_BC;
    RET_C ;

    LD_A_B;
    CALL(aCheckObjectVisibility);
    RET_C ;

//  object 2 is now in bc, object 1 is now in de
    LD_HL(OBJECT_NEXT_MAP_X);
    ADD_HL_BC;
    LD_A_hl;
    LD_HL(OBJECT_NEXT_MAP_Y);
    ADD_HL_BC;
    LD_C_hl;
    LD_B_A;

    LD_HL(OBJECT_NEXT_MAP_X);
    ADD_HL_DE;
    LD_A_hl;
    CP_A_B;
    IF_Z goto same_x;
    IF_C goto to_the_left;
    INC_B;
    goto continue_;


to_the_left:
    DEC_B;
    goto continue_;


same_x:
    LD_HL(OBJECT_NEXT_MAP_Y);
    ADD_HL_DE;
    LD_A_hl;
    CP_A_C;
    IF_Z goto continue_;
    IF_C goto below;
    INC_C;
    goto continue_;


below:
    DEC_C;


continue_:
    LD_HL(OBJECT_NEXT_MAP_X);
    ADD_HL_DE;
    LD_hl_B;
    LD_A_B;
    LD_HL(wXCoord);
    SUB_A_hl;
    AND_A(0xf);
    SWAP_A;
    LD_HL(wPlayerBGMapOffsetX);
    SUB_A_hl;
    LD_HL(OBJECT_SPRITE_X);
    ADD_HL_DE;
    LD_hl_A;
    LD_HL(OBJECT_NEXT_MAP_Y);
    ADD_HL_DE;
    LD_hl_C;
    LD_A_C;
    LD_HL(wYCoord);
    SUB_A_hl;
    AND_A(0xf);
    SWAP_A;
    LD_HL(wPlayerBGMapOffsetY);
    SUB_A_hl;
    LD_HL(OBJECT_SPRITE_Y);
    ADD_HL_DE;
    LD_hl_A;
    LDH_A_addr(hObjectStructIndex);
    LD_HL(OBJECT_RANGE);
    ADD_HL_DE;
    LD_hl_A;
    LD_HL(OBJECT_MOVEMENTTYPE);
    ADD_HL_DE;
    LD_hl(SPRITEMOVEDATA_FOLLOWNOTEXACT);
    LD_HL(OBJECT_STEP_TYPE);
    ADD_HL_DE;
    LD_hl(STEP_TYPE_RESET);
    RET;

}

void GetRelativeFacing(void){
//  Determines which way map object e would have to turn to face map object d.  Returns carry if it's impossible for whatever reason.
    LD_A_D;
    CALL(aGetMapObject);
    LD_HL(MAPOBJECT_OBJECT_STRUCT_ID);
    ADD_HL_BC;
    LD_A_hl;
    CP_A(NUM_OBJECT_STRUCTS);
    IF_NC goto carry;
    LD_D_A;
    LD_A_E;
    CALL(aGetMapObject);
    LD_HL(MAPOBJECT_OBJECT_STRUCT_ID);
    ADD_HL_BC;
    LD_A_hl;
    CP_A(NUM_OBJECT_STRUCTS);
    IF_NC goto carry;
    LD_E_A;
    CALL(aGetRelativeFacing_GetFacing_e_relativeto_d);
    RET;


carry:
    SCF;
    RET;


GetFacing_e_relativeto_d:
//  Determines which way object e would have to turn to face object d.  Returns carry if it's impossible.
//  load the coordinates of object d into bc
    LD_A_D;
    CALL(aGetObjectStruct);
    LD_HL(OBJECT_NEXT_MAP_X);
    ADD_HL_BC;
    LD_A_hl;
    LD_HL(OBJECT_NEXT_MAP_Y);
    ADD_HL_BC;
    LD_C_hl;
    LD_B_A;
    PUSH_BC;
//  load the coordinates of object e into de
    LD_A_E;
    CALL(aGetObjectStruct);
    LD_HL(OBJECT_NEXT_MAP_X);
    ADD_HL_BC;
    LD_D_hl;
    LD_HL(OBJECT_NEXT_MAP_Y);
    ADD_HL_BC;
    LD_E_hl;
    POP_BC;
//  |x1 - x2|
    LD_A_B;
    SUB_A_D;
    IF_Z goto same_x_1;
    IF_NC goto b_right_of_d_1;
    CPL;
    INC_A;


b_right_of_d_1:
//  |y1 - y2|
    LD_H_A;
    LD_A_C;
    SUB_A_E;
    IF_Z goto same_y_1;
    IF_NC goto c_below_e_1;
    CPL;
    INC_A;


c_below_e_1:
//  |y1 - y2| - |x1 - x2|
    SUB_A_H;
    IF_C goto same_y_1;


same_x_1:
//  compare the y coordinates
    LD_A_C;
    CP_A_E;
    IF_Z goto same_x_and_y;
    IF_C goto c_directly_below_e;
//  c directly above e
    LD_D(DOWN);
    AND_A_A;
    RET;


c_directly_below_e:
    LD_D(UP);
    AND_A_A;
    RET;


same_y_1:
    LD_A_B;
    CP_A_D;
    IF_Z goto same_x_and_y;
    IF_C goto b_directly_right_of_d;
//  b directly left of d
    LD_D(RIGHT);
    AND_A_A;
    RET;


b_directly_right_of_d:
    LD_D(LEFT);
    AND_A_A;
    RET;


same_x_and_y:
    SCF;
    RET;

}

//  Determines which way object e would have to turn to face object d.  Returns 255 if it's impossible.
static uint8_t GetRelativeFacing_GetFacing_e_relativeto_d(uint8_t e, uint8_t d) {
//  load the coordinates of object d into bc
    // LD_A_D;
    // CALL(aGetObjectStruct);
    struct Object* hl = GetObjectStruct_Conv(d);
    // LD_HL(OBJECT_NEXT_MAP_X);
    // ADD_HL_BC;
    // LD_A_hl;
    uint8_t x1 = hl->nextMapX;
    // LD_HL(OBJECT_NEXT_MAP_Y);
    // ADD_HL_BC;
    // LD_C_hl;
    uint8_t y1 = hl->nextMapY;
    // LD_B_A;
    // PUSH_BC;
//  load the coordinates of object e into de
    // LD_A_E;
    // CALL(aGetObjectStruct);
    hl = GetObjectStruct_Conv(e);
    // LD_HL(OBJECT_NEXT_MAP_X);
    // ADD_HL_BC;
    // LD_D_hl;
    uint8_t x2 = hl->nextMapX;
    // LD_HL(OBJECT_NEXT_MAP_Y);
    // ADD_HL_BC;
    // LD_E_hl;
    uint8_t y2 = hl->nextMapY;
    // POP_BC;
    uint8_t h = x1, l = y1;
//  |x1 - x2|
    // LD_A_B;
    // SUB_A_D;
    // IF_Z goto same_x_1;
    if(x1 == x2) goto same_x_1;
    // IF_NC goto b_right_of_d_1;
    if(x1 <  x2) {
    // CPL;
    // INC_A;
        h = -x1;
    }

// b_right_of_d_1:
//  |y1 - y2|
    // LD_H_A;
    // LD_A_C;
    // SUB_A_E;
    // IF_Z goto same_y_1;
    if(y1 == y2) goto same_y_1;
    // IF_NC goto c_below_e_1;
    if(y1 <  y2) {
    // CPL;
    // INC_A;
        l = -y1;
    }


// c_below_e_1:
//  |y1 - y2| - |x1 - x2|
    // SUB_A_H;
    // IF_C goto same_y_1;
    if(l < h) goto same_y_1;


same_x_1:
//  compare the y coordinates
    // LD_A_C;
    // CP_A_E;
    // IF_Z goto same_x_and_y;
    if(y1 == y2) {
    // same_x_and_y:
        // SCF;
        // RET;
        return 0xff;
    }
    // IF_C goto c_directly_below_e;
    if(y1 <  y2) {
    // c_directly_below_e:
        // LD_D(UP);
        // AND_A_A;
        // RET;
        return UP;
    }
//  c directly above e
    // LD_D(DOWN);
    // AND_A_A;
    // RET;
    return DOWN;


same_y_1:
    // LD_A_B;
    // CP_A_D;
    // IF_Z goto same_x_and_y;
    if(x1 == x2) {
    // same_x_and_y:
        // SCF;
        // RET;
        return 0xff;
    }
    // IF_C goto b_directly_right_of_d;
    if(x1 <  x2) {
    // b_directly_right_of_d:
        // LD_D(LEFT);
        // AND_A_A;
        // RET;
        return LEFT;
    }
//  b directly left of d
    // LD_D(RIGHT);
    // AND_A_A;
    // RET;
    return RIGHT;
}

//  Determines which way map object e would have to turn to face map object d.  Returns 255 if it's impossible for whatever reason.
uint8_t GetRelativeFacing_Conv(uint8_t e, uint8_t d){
    // LD_A_D;
    // CALL(aGetMapObject);
    struct MapObject* bc = GetMapObject_Conv(d);
    // LD_HL(MAPOBJECT_OBJECT_STRUCT_ID);
    // ADD_HL_BC;
    // LD_A_hl;
    // CP_A(NUM_OBJECT_STRUCTS);
    // IF_NC goto carry;
    if(bc->structId >= NUM_OBJECT_STRUCTS)
        return 0xff;
    // LD_D_A;
    d = bc->structId;
    // LD_A_E;
    // CALL(aGetMapObject);
    bc = GetMapObject_Conv(e);
    // LD_HL(MAPOBJECT_OBJECT_STRUCT_ID);
    // ADD_HL_BC;
    // LD_A_hl;
    // CP_A(NUM_OBJECT_STRUCTS);
    // IF_NC goto carry;
    if(bc->structId >= NUM_OBJECT_STRUCTS)
        return 0xff;
    // LD_E_A;
    e = bc->structId;
    // CALL(aGetRelativeFacing_GetFacing_e_relativeto_d);
    // RET;
    return GetRelativeFacing_GetFacing_e_relativeto_d(e, d);

// carry:
    // SCF;
    // RET;
}

void QueueFollowerFirstStep(void){
    CALL(aQueueFollowerFirstStep_QueueFirstStep);
    IF_C goto same;
    LD_addr_A(wFollowMovementQueue);
    XOR_A_A;
    LD_addr_A(wFollowerMovementQueueLength);
    RET;


same:
    LD_A(-1);
    LD_addr_A(wFollowerMovementQueueLength);
    RET;


QueueFirstStep:
    LD_A_addr(wObjectFollow_Leader);
    CALL(aGetObjectStruct);
    LD_HL(OBJECT_NEXT_MAP_X);
    ADD_HL_BC;
    LD_D_hl;
    LD_HL(OBJECT_NEXT_MAP_Y);
    ADD_HL_BC;
    LD_E_hl;
    LD_A_addr(wObjectFollow_Follower);
    CALL(aGetObjectStruct);
    LD_HL(OBJECT_NEXT_MAP_X);
    ADD_HL_BC;
    LD_A_D;
    CP_A_hl;
    IF_Z goto check_y;
    IF_C goto left;
    AND_A_A;
    LD_A(movement_step + RIGHT);
    RET;


left:
    AND_A_A;
    LD_A(movement_step + LEFT);
    RET;


check_y:
    LD_HL(OBJECT_NEXT_MAP_Y);
    ADD_HL_BC;
    LD_A_E;
    CP_A_hl;
    IF_Z goto same_xy;
    IF_C goto up;
    AND_A_A;
    LD_A(movement_step + DOWN);
    RET;


up:
    AND_A_A;
    LD_A(movement_step + UP);
    RET;


same_xy:
    SCF;
    RET;

}

static u8_flag_s QueueFollowerFirstStep_QueueFirstStep(void) {
    // LD_A_addr(wObjectFollow_Leader);
    // CALL(aGetObjectStruct);
    struct Object* leader = GetObjectStruct_Conv(wram->wObjectFollow_Leader);
    // LD_HL(OBJECT_NEXT_MAP_X);
    // ADD_HL_BC;
    // LD_D_hl;
    uint8_t d = leader->nextMapX;
    // LD_HL(OBJECT_NEXT_MAP_Y);
    // ADD_HL_BC;
    // LD_E_hl;
    uint8_t e = leader->nextMapY;
    // LD_A_addr(wObjectFollow_Follower);
    // CALL(aGetObjectStruct);
    struct Object* follower = GetObjectStruct_Conv(wram->wObjectFollow_Follower);
    // LD_HL(OBJECT_NEXT_MAP_X);
    // ADD_HL_BC;
    // LD_A_D;
    // CP_A_hl;
    // IF_C goto left;
    if(d < follower->nextMapX) {
    // left:
        // AND_A_A;
        // LD_A(movement_step + LEFT);
        // RET;
        return u8_flag(step(LEFT), false);
    }
    // IF_Z goto check_y;
    else if(d == follower->nextMapX) {
    // check_y:
        // LD_HL(OBJECT_NEXT_MAP_Y);
        // ADD_HL_BC;
        // LD_A_E;
        // CP_A_hl;
        // IF_Z goto same_xy;
        if(e == follower->nextMapX) {
        // same_xy:
            // SCF;
            // RET;
            return u8_flag(e, true);
        }
        // IF_C goto up;
        else if(e < follower->nextMapX) {
        // up:
            // AND_A_A;
            // LD_A(movement_step + UP);
            // RET;
            return u8_flag(step(UP), false);
        }
        else {
            // AND_A_A;
            // LD_A(movement_step + DOWN);
            // RET;
            return u8_flag(step(DOWN), false);
        }
    }
    else {
        // AND_A_A;
        // LD_A(movement_step + RIGHT);
        // RET;
        return u8_flag(step(RIGHT), false);
    }
}

bool QueueFollowerFirstStep_Conv(void){
    // CALL(aQueueFollowerFirstStep_QueueFirstStep);
    // IF_C goto same;
    u8_flag_s res = QueueFollowerFirstStep_QueueFirstStep();
    if(res.flag) {
    // same:
        // LD_A(-1);
        // LD_addr_A(wFollowerMovementQueueLength);
        wram->wFollowerMovementQueueLength = 0xff;
        // RET;
        return false;
    }
    // LD_addr_A(wFollowMovementQueue);
    wram->wFollowMovementQueue[0] = res.a;
    // XOR_A_A;
    // LD_addr_A(wFollowerMovementQueueLength);
    wram->wFollowerMovementQueueLength = 0;
    // RET;
    return true;
}
