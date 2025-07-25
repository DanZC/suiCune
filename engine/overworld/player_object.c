#include "../../constants.h"
#include "player_object.h"
#include "../../home/map_objects.h"
#include "../../home/map.h"
#include "../../home/copy.h"
#include "../../home/movement.h"
#include "../../home/tilemap.h"
#include "../../home/sprite_updates.h"
#include "../../home/clear_sprites.h"

static void PlayerSpawn_ConvertCoords(uint8_t b);
static void CopyMapObjectToObjectStruct(struct Object* de, struct MapObject* bc, uint8_t mapObjIdx, uint8_t objIdx);

void BlankScreen(void){
    // CALL(aDisableSpriteUpdates);
    DisableSpriteUpdates();
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram.hBGMapMode = BGMAPMODE_NONE;
    // CALL(aClearBGPalettes);
    ClearBGPalettes();
    // CALL(aClearSprites);
    ClearSprites();
    // hlcoord(0, 0, wTilemap);
    // LD_BC(wTilemapEnd - wTilemap);
    // LD_A(0x7f);
    // CALL(aByteFill);
    ByteFill(coord(0, 0, wram->wTilemap), wTilemapEnd - wTilemap, 0x7f);
    // hlcoord(0, 0, wAttrmap);
    // LD_BC(wAttrmapEnd - wAttrmap);
    // LD_A(0x7);
    // CALL(aByteFill);
    ByteFill(coord(0, 0, wram->wAttrmap), wAttrmapEnd - wAttrmap, 0x7);
    // CALL(aWaitBGMap2);
    WaitBGMap2();
    // CALL(aSetPalettes);
    SetPalettes();
    // RET;
}

void SpawnPlayer(void){
    // LD_A(-1);
    // LD_addr_A(wObjectFollow_Leader);
    gPlayer.objectFollow_Leader = 0xff;
    // LD_addr_A(wObjectFollow_Follower);
    gPlayer.objectFollow_Follower = 0xff;
    // LD_A(PLAYER);
    // LD_HL(mPlayerObjectTemplate);
    // CALL(aCopyPlayerObjectTemplate);
    CopyPlayerObjectTemplate(&PlayerObjectTemplate, PLAYER);
    // LD_B(PLAYER);
    // CALL(aPlayerSpawn_ConvertCoords);
    PlayerSpawn_ConvertCoords(PLAYER);
    // LD_A(PLAYER_OBJECT);
    // CALL(aGetMapObject);
    struct MapObject* bc = GetMapObject(PLAYER_OBJECT);
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
        (bit_test(wram->wPlayerSpriteSetupFlags, PLAYERSPRITESETUP_FEMALE_TO_MALE_F) || !bit_test(gCrystal.playerGender, PLAYERGENDER_FEMALE_F))
            ? (PAL_NPC_RED << 4) | OBJECTTYPE_SCRIPT
            : (PAL_NPC_BLUE << 4) | OBJECTTYPE_SCRIPT;
    // LD_A(PLAYER_OBJECT);
    // LDH_addr_A(hMapObjectIndex);
    // LD_BC(wMapObjects);
    // LD_A(PLAYER_OBJECT);
    // LDH_addr_A(hObjectStructIndex);
    // LD_DE(wObjectStructs);
    // CALL(aCopyMapObjectToObjectStruct);
    CopyMapObjectToObjectStruct(&gPlayer.playerStruct, bc, PLAYER_OBJECT, PLAYER_OBJECT);
    // LD_A(PLAYER);
    // LD_addr_A(wCenteredObject);
    gPlayer.centeredObject = PLAYER;
    // RET;
}

//  A dummy map object used to initialize the player object.
//  Shorter than the actual amount copied by two bytes.
//  Said bytes seem to be unused.
const struct ObjEvent PlayerObjectTemplate = object_event(-4, -4, SPRITE_CHRIS, SPRITEMOVEDATA_PLAYER, 15, 15, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, 0, -1);

void CopyDECoordsToMapObject(uint8_t d, uint8_t e, uint8_t b){
    // PUSH_DE;
    // LD_A_B;
    // CALL(aGetMapObject);
    struct MapObject* bc = GetMapObject(b);
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

static void PlayerSpawn_ConvertCoords(uint8_t b){
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
    return CopyDECoordsToMapObject(gCurMapData.xCoord + 4, gCurMapData.yCoord + 4, b);
}

void WriteObjectXY(uint8_t b){
    // LD_A_B;
    // CALL(aCheckObjectVisibility);
    struct Object* bc = CheckObjectVisibility(b);
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
    CopyDECoordsToMapObject(bc->nextMapX, bc->nextMapY, hram.hMapObjectIndex);
    // AND_A_A;
    // RET;
}

void RefreshPlayerCoords(void){
    // LD_A_addr(wXCoord);
    // ADD_A(4);
    // LD_D_A;
    uint8_t x = gCurMapData.xCoord + 4;
    // LD_HL(wPlayerStandingMapX);
    // SUB_A_hl;
    // LD_hl_D;
    gPlayer.playerStruct.nextMapX = x;
    // LD_HL(wMapObjects + MAPOBJECT_X_COORD);
    // LD_hl_D;
    gPlayer.playerObject.objectXCoord = x;
    // LD_HL(wPlayerLastMapX);
    // LD_hl_D;
    gPlayer.playerStruct.mapX = x;
    // LD_D_A;
    // LD_A_addr(wYCoord);
    // ADD_A(4);
    // LD_E_A;
    uint8_t y = gCurMapData.yCoord + 4;
    // LD_HL(wPlayerStandingMapY);
    // SUB_A_hl;
    // LD_hl_E;
    gPlayer.playerStruct.nextMapY = y;
    // LD_HL(wMapObjects + MAPOBJECT_Y_COORD);
    // LD_hl_E;
    gPlayer.playerObject.objectYCoord = y;
    // LD_HL(wPlayerLastMapY);
    // LD_hl_E;
    gPlayer.playerStruct.mapY = y;
    // LD_E_A;
//  the next three lines are useless
    // LD_A_addr(wObjectFollow_Leader);
    // CP_A(PLAYER);
    // RET_NZ ;
    // RET;
}

uint8_t CopyObjectStruct(struct MapObject* bc, uint8_t a){
    // CALL(aCheckObjectMask);
    // AND_A_A;
    // RET_NZ ;  // masked
    if(CheckObjectMask(a) != 0)
        return 1;

    // LD_HL(wObjectStructs + OBJECT_LENGTH * 1);
    // LD_A(1);
    // LD_DE(OBJECT_LENGTH);
    struct Object* hl = gPlayer.objectStruct;
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
            CopyMapObjectToObjectStruct(hl, bc, a, b);
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

static void CopyMapObjectToObjectStruct_CopyMapObjectToTempObject(struct MapObject* bc, uint8_t objIdx, uint8_t mapObjIdx) {
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
    wram->wTempObjectCopySpriteVTile = GetSpriteVTile(bc->sprite, mapObjIdx);

    // LD_A_hl;
    // CALL(aGetSpritePalette);
    // LD_addr_A(wTempObjectCopyPalette);
    wram->wTempObjectCopyPalette = GetSpritePalette(bc->sprite);

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

static void CopyMapObjectToObjectStruct(struct Object* de, struct MapObject* bc, uint8_t mapObjIdx, uint8_t objIdx){
    // CALL(aCopyMapObjectToObjectStruct_CopyMapObjectToTempObject);
    CopyMapObjectToObjectStruct_CopyMapObjectToTempObject(bc, objIdx, mapObjIdx);
    // CALL(aCopyTempObjectToObjectStruct);
    CopyTempObjectToObjectStruct(de);
    // RET;
}

void InitializeVisibleSprites(void){
    // LD_BC(wMap1Object);
    struct MapObject* bc = gPlayer.mapObjects;
    // LD_A(1);
    uint8_t a = 1;

    do {
    // loop:
        // LDH_addr_A(hMapObjectIndex);
        hram.hMapObjectIndex = a;
        // LD_HL(MAPOBJECT_SPRITE);
        // ADD_HL_BC;
        // LD_A_hl;
        // AND_A_A;
        // IF_Z goto next;
        if(bc[a].sprite == 0)
            continue;

        // LD_HL(MAPOBJECT_OBJECT_STRUCT_ID);
        // ADD_HL_BC;
        // LD_A_hl;
        // CP_A(-1);
        // IF_NZ goto next;
        if(bc[a].structId != 0xff)
            continue;

        // LD_A_addr(wXCoord);
        // LD_D_A;
        uint8_t d = gCurMapData.xCoord;
        // LD_A_addr(wYCoord);
        // LD_E_A;
        uint8_t e = gCurMapData.yCoord;

        // LD_HL(MAPOBJECT_X_COORD);
        // ADD_HL_BC;
        // LD_A_hl;
        // ADD_A(1);
        uint8_t x = bc[a].objectXCoord + 1;
        // SUB_A_D;
        // IF_C goto next;
        if(x < d)
            continue;

        // CP_A(MAPOBJECT_SCREEN_WIDTH);
        // IF_NC goto next;
        if(x - d >= MAPOBJECT_SCREEN_WIDTH)
            continue;

        // LD_HL(MAPOBJECT_Y_COORD);
        // ADD_HL_BC;
        // LD_A_hl;
        // ADD_A(1);
        uint8_t y = bc[a].objectYCoord + 1;
        // SUB_A_E;
        // IF_C goto next;
        if(y < e)
            continue;

        // CP_A(MAPOBJECT_SCREEN_HEIGHT);
        // IF_NC goto next;
        if(y - e >= MAPOBJECT_SCREEN_HEIGHT)
            continue;

        // PUSH_BC;
        // CALL(aCopyObjectStruct);
        uint8_t res = CopyObjectStruct(bc + a, a);
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
    uint8_t d, e, a = 1;
    struct MapObject* bc = gPlayer.mapObjects;
    switch(wram->wPlayerStepDirection) {
    case DOWN:
    // Down:
        // LD_A_addr(wYCoord);
        // ADD_A(9);
        d = gCurMapData.yCoord + 9;
        goto Vertical;
    case UP:
    // Up:
        // LD_A_addr(wYCoord);
        // SUB_A(1);
        d = gCurMapData.yCoord - 1;
    Vertical:
        // LD_D_A;
        // LD_A_addr(wXCoord);
        // LD_E_A;
        e = gCurMapData.xCoord;
        // LD_BC(wMap1Object);
        // LD_A(1);

        do {
        // loop_v:
            // LDH_addr_A(hMapObjectIndex);
            hram.hMapObjectIndex = a;
            // LD_HL(MAPOBJECT_SPRITE);
            // ADD_HL_BC;
            // LD_A_hl;
            // AND_A_A;
            // IF_Z goto next_v;
            if(bc[a].sprite == 0)
                continue;
            // LD_HL(MAPOBJECT_Y_COORD);
            // ADD_HL_BC;
            // LD_A_D;
            // CP_A_hl;
            // IF_NZ goto next_v;
            if(bc[a].objectYCoord != d)
                continue;
            // LD_HL(MAPOBJECT_OBJECT_STRUCT_ID);
            // ADD_HL_BC;
            // LD_A_hl;
            // CP_A(-1);
            // IF_NZ goto next_v;
            if(bc[a].structId != 0xff)
                continue;
            // LD_HL(MAPOBJECT_X_COORD);
            // ADD_HL_BC;
            // LD_A_hl;
            // ADD_A(1);
            // SUB_A_E;
            // IF_C goto next_v;
            // CP_A(MAPOBJECT_SCREEN_WIDTH);
            // IF_NC goto next_v;
            if(bc[a].objectXCoord + 1 < e
            || bc[a].objectXCoord + 1 - e >= MAPOBJECT_SCREEN_WIDTH)
                continue;
            // PUSH_DE;
            // PUSH_BC;
            // CALL(aCopyObjectStruct);
            CopyObjectStruct(bc + a, a);
            // POP_BC;
            // POP_DE;


        // next_v:
            // LD_HL(MAPOBJECT_LENGTH);
            // ADD_HL_BC;
            // LD_B_H;
            // LD_C_L;
            // LDH_A_addr(hMapObjectIndex);
            // INC_A;
            // CP_A(NUM_OBJECTS);
            // IF_NZ goto loop_v;
        } while(++a != NUM_OBJECTS);
        // RET;
        return;
    case LEFT:
    // Left:
        // LD_A_addr(wXCoord);
        // SUB_A(1);
        e = gCurMapData.xCoord - 1;
        goto Horizontal;
    case RIGHT:
    // Right:
        // LD_A_addr(wXCoord);
        // ADD_A(10);
        e = gCurMapData.xCoord + 10;

    Horizontal:
        // LD_E_A;
        // LD_A_addr(wYCoord);
        // LD_D_A;
        d = gCurMapData.yCoord;
        // LD_BC(wMap1Object);
        // LD_A(1);

        do {
        // loop_h:
            // LDH_addr_A(hMapObjectIndex);
            hram.hMapObjectIndex = a;
            // LD_HL(MAPOBJECT_SPRITE);
            // ADD_HL_BC;
            // LD_A_hl;
            // AND_A_A;
            // IF_Z goto next_h;
            if(bc[a].sprite == 0)
                continue;
            // LD_HL(MAPOBJECT_X_COORD);
            // ADD_HL_BC;
            // LD_A_E;
            // CP_A_hl;
            // IF_NZ goto next_h;
            if(bc[a].objectXCoord != e)
                continue;
            // LD_HL(MAPOBJECT_OBJECT_STRUCT_ID);
            // ADD_HL_BC;
            // LD_A_hl;
            // CP_A(-1);
            // IF_NZ goto next_h;
            if(bc[a].structId != 0xff)
                continue;
            // LD_HL(MAPOBJECT_Y_COORD);
            // ADD_HL_BC;
            // LD_A_hl;
            // ADD_A(1);
            // SUB_A_D;
            // IF_C goto next_h;
            // CP_A(MAPOBJECT_SCREEN_HEIGHT);
            // IF_NC goto next_h;
            if(bc[a].objectYCoord + 1 < d
            || bc[a].objectYCoord + 1 - d >= MAPOBJECT_SCREEN_HEIGHT)
                continue;
            // PUSH_DE;
            // PUSH_BC;
            // CALL(aCopyObjectStruct);
            CopyObjectStruct(bc + a, a);
            // POP_BC;
            // POP_DE;

        // next_h:
            // LD_HL(MAPOBJECT_LENGTH);
            // ADD_HL_BC;
            // LD_B_H;
            // LD_C_L;
            // LDH_A_addr(hMapObjectIndex);
            // INC_A;
            // CP_A(NUM_OBJECTS);
            // IF_NZ goto loop_h;
        } while(++a != NUM_OBJECTS);
        // RET;
        return;
    }
    // RET;
    return;

// dw:
    //dw ['.Down'];
    //dw ['.Up'];
    //dw ['.Left'];
    //dw ['.Right'];
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
    de->spriteY = (((a - gCurMapData.yCoord) & 0xf) << 4) - wram->wPlayerBGMapOffsetY;
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
    de->spriteX = (((a - gCurMapData.xCoord) & 0xf) << 4) - wram->wPlayerBGMapOffsetX;
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

void CopyTempObjectToObjectStruct(struct Object* de){
    // LD_A_addr(wTempObjectCopyMapObjectIndex);
    // LD_HL(OBJECT_MAP_OBJECT_INDEX);
    // ADD_HL_DE;
    // LD_hl_A;
    de->mapObjectIndex = wram->wTempObjectCopyMapObjectIndex;

    // LD_A_addr(wTempObjectCopyMovement);
    // CALL(aCopySpriteMovementData);
    CopySpriteMovementData(de, wram->wTempObjectCopyMovement);

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

static void TrainerWalkToPlayer_GetPathToPlayer(uint8_t b, uint8_t c, uint8_t d) {
    // PUSH_DE;
    // PUSH_BC;
//  get player object struct, load to de
    // LD_A_C;
    // CALL(aGetMapObject);
    struct MapObject* bc = GetMapObject(c);
    // LD_HL(MAPOBJECT_OBJECT_STRUCT_ID);
    // ADD_HL_BC;
    // LD_A_hl;
    // CALL(aGetObjectStruct);
    struct Object* de = GetObjectStruct(bc->structId);
    // LD_D_B;
    // LD_E_C;

//  get last talked object struct, load to bc
    // POP_BC;
    // LD_A_B;
    // CALL(aGetMapObject);
    struct MapObject* bc2 = GetMapObject(b);
    // LD_HL(MAPOBJECT_OBJECT_STRUCT_ID);
    // ADD_HL_BC;
    // LD_A_hl;
    // CALL(aGetObjectStruct);
    struct Object* de2 = GetObjectStruct(bc2->structId);

//  get last talked coords, load to bc
    // LD_HL(OBJECT_NEXT_MAP_X);
    // ADD_HL_BC;
    // LD_A_hl;
    uint8_t x2 = de2->nextMapX;
    // LD_HL(OBJECT_NEXT_MAP_Y);
    // ADD_HL_BC;
    // LD_C_hl;
    // LD_B_A;
    uint8_t y2 = de2->nextMapY;

//  get player coords, load to de
    // LD_HL(OBJECT_NEXT_MAP_X);
    // ADD_HL_DE;
    // LD_A_hl;
    uint8_t x1 = de->nextMapX;
    // LD_HL(OBJECT_NEXT_MAP_Y);
    // ADD_HL_DE;
    // LD_E_hl;
    // LD_D_A;
    uint8_t y1 = de->nextMapY;
    // POP_AF;
    // CALL(aComputePathToWalkToPlayer);
    ComputePathToWalkToPlayer(x2, y2, x1, y1, d);
    // RET;
}

void TrainerWalkToPlayer(void){
    // LDH_A_addr(hLastTalked);
    // CALL(aInitMovementBuffer);
    InitMovementBuffer(hram.hLastTalked);
    // LD_A(movement_step_sleep);
    // CALL(aAppendToMovementBuffer);
    AppendToMovementBuffer(movement_step_sleep);
    // LD_A_addr(wWalkingIntoNPC);
    // DEC_A;
    // IF_Z goto TerminateStep;
    if(wram->wWalkingIntoNPC != 1) {
        // LDH_A_addr(hLastTalked);
        // LD_B_A;
        // LD_C(PLAYER);
        // LD_D(1);
        // CALL(aTrainerWalkToPlayer_GetPathToPlayer);
        TrainerWalkToPlayer_GetPathToPlayer(hram.hLastTalked, PLAYER, 1);
        // CALL(aDecrementMovementBufferCount);
        DecrementMovementBufferCount();
    }

// TerminateStep:
    // LD_A(movement_step_end);
    // CALL(aAppendToMovementBuffer);
    AppendToMovementBuffer(movement_step_end);
    // RET;
}

static uint8_t SurfStartStep_GetMovementData(void){
    static const uint8_t movement_data[] = {
        slow_step(DOWN),
        slow_step(UP),
        slow_step(LEFT),
        slow_step(RIGHT),
    };
    // LD_A_addr(wPlayerDirection);
    // SRL_A;
    // SRL_A;
    // maskbits(NUM_DIRECTIONS, 0);
    // LD_E_A;
    // LD_D(0);
    // LD_HL(mSurfStartStep_movement_data);
    // ADD_HL_DE;
    // LD_A_hl;
    // RET;
    return movement_data[(gPlayer.playerStruct.facing & 0b00001100) >> 2];
}

void SurfStartStep(void){
    // CALL(aInitMovementBuffer);
    InitMovementBuffer(PLAYER);
    // CALL(aSurfStartStep_GetMovementData);
    // CALL(aAppendToMovementBuffer);
    AppendToMovementBuffer(SurfStartStep_GetMovementData());
    // LD_A(movement_step_end);
    // CALL(aAppendToMovementBuffer);
    AppendToMovementBuffer(movement_step_end);
    // RET;
}

void FollowNotExact(uint8_t c, uint8_t b){
    // PUSH_BC;
    // LD_A_C;
    // CALL(aCheckObjectVisibility);
    // LD_D_B;
    // LD_E_C;
    struct Object* de = CheckObjectVisibility(c);
    // POP_BC;
    // RET_C ;
    if(de == NULL)
        return;

    // LD_A_B;
    // CALL(aCheckObjectVisibility);
    struct Object* bc = CheckObjectVisibility(b);
    // RET_C ;
    if(bc == NULL)
        return;

//  object 2 is now in bc, object 1 is now in de
    // LD_HL(OBJECT_NEXT_MAP_X);
    // ADD_HL_BC;
    // LD_A_hl;
    uint8_t nextX = bc->nextMapX;
    // LD_HL(OBJECT_NEXT_MAP_Y);
    // ADD_HL_BC;
    // LD_C_hl;
    // LD_B_A;
    uint8_t nextY = bc->nextMapY;

    // LD_HL(OBJECT_NEXT_MAP_X);
    // ADD_HL_DE;
    // LD_A_hl;
    // CP_A_B;
    // IF_Z goto same_x;
    if(de->nextMapX == nextX) {
    // same_x:
        // LD_HL(OBJECT_NEXT_MAP_Y);
        // ADD_HL_DE;
        // LD_A_hl;
        // CP_A_C;
        // IF_Z goto continue_;
        // IF_C goto below;
        if(de->nextMapY < nextY) {
        // below:
            // DEC_C;
            nextY--;
        }
        else if(de->nextMapY > nextY) {
            // INC_C;
            nextY++;
            // goto continue_;
        }
    }
    // IF_C goto to_the_left;
    else if(de->nextMapX < nextX) {
    // to_the_left:
        // DEC_B;
        nextX--;
        // goto continue_;
    }
    else {
        // INC_B;
        nextX++;
        // goto continue_;
    }

// continue_:
    // LD_HL(OBJECT_NEXT_MAP_X);
    // ADD_HL_DE;
    // LD_hl_B;
    de->nextMapX = nextX;
    // LD_A_B;
    // LD_HL(wXCoord);
    // SUB_A_hl;
    // AND_A(0xf);
    // SWAP_A;
    // LD_HL(wPlayerBGMapOffsetX);
    // SUB_A_hl;
    // LD_HL(OBJECT_SPRITE_X);
    // ADD_HL_DE;
    // LD_hl_A;
    de->spriteX = (((nextX - gCurMapData.xCoord) & 0xf) << 4) - wram->wPlayerBGMapOffsetX;
    // LD_HL(OBJECT_NEXT_MAP_Y);
    // ADD_HL_DE;
    // LD_hl_C;
    de->nextMapY = nextY;
    // LD_A_C;
    // LD_HL(wYCoord);
    // SUB_A_hl;
    // AND_A(0xf);
    // SWAP_A;
    // LD_HL(wPlayerBGMapOffsetY);
    // SUB_A_hl;
    // LD_HL(OBJECT_SPRITE_Y);
    // ADD_HL_DE;
    // LD_hl_A;
    de->spriteY = (((nextY - gCurMapData.yCoord) & 0xf) << 4) - wram->wPlayerBGMapOffsetY;
    // LDH_A_addr(hObjectStructIndex);
    // LD_HL(OBJECT_RANGE);
    // ADD_HL_DE;
    // LD_hl_A;
    de->range = hram.hObjectStructIndex;
    // LD_HL(OBJECT_MOVEMENTTYPE);
    // ADD_HL_DE;
    // LD_hl(SPRITEMOVEDATA_FOLLOWNOTEXACT);
    de->movementType = SPRITEMOVEDATA_FOLLOWNOTEXACT;
    // LD_HL(OBJECT_STEP_TYPE);
    // ADD_HL_DE;
    // LD_hl(STEP_TYPE_RESET);
    de->stepType = STEP_TYPE_RESET;
    // RET;
}

//  Determines which way object e would have to turn to face object d.  Returns 255 if it's impossible.
static uint8_t GetRelativeFacing_GetFacing_e_relativeto_d(uint8_t e, uint8_t d) {
//  load the coordinates of object d into bc
    // LD_A_D;
    // CALL(aGetObjectStruct);
    struct Object* hl = GetObjectStruct(d);
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
    hl = GetObjectStruct(e);
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
uint8_t GetRelativeFacing(uint8_t e, uint8_t d){
    // LD_A_D;
    // CALL(aGetMapObject);
    struct MapObject* bc = GetMapObject(d);
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
    bc = GetMapObject(e);
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

static u8_flag_s QueueFollowerFirstStep_QueueFirstStep(void) {
    // LD_A_addr(wObjectFollow_Leader);
    // CALL(aGetObjectStruct);
    struct Object* leader = GetObjectStruct(gPlayer.objectFollow_Leader);
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
    struct Object* follower = GetObjectStruct(gPlayer.objectFollow_Follower);
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
        if(e == follower->nextMapY) {
        // same_xy:
            // SCF;
            // RET;
            return u8_flag(e, true);
        }
        // IF_C goto up;
        else if(e < follower->nextMapY) {
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

bool QueueFollowerFirstStep(void){
    // CALL(aQueueFollowerFirstStep_QueueFirstStep);
    // IF_C goto same;
    u8_flag_s res = QueueFollowerFirstStep_QueueFirstStep();
    if(res.flag) {
    // same:
        // LD_A(-1);
        // LD_addr_A(wFollowerMovementQueueLength);
        gPlayer.followerMovementQueueLength = 0xff;
        // RET;
        return false;
    }
    // LD_addr_A(wFollowMovementQueue);
    gPlayer.followMovementQueue[0] = res.a;
    // XOR_A_A;
    // LD_addr_A(wFollowerMovementQueueLength);
    gPlayer.followerMovementQueueLength = 0;
    // RET;
    return true;
}
