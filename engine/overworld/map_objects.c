#include "../../constants.h"
#include "map_objects.h"
#include "../../home/copy.h"
#include "../../home/map_objects.h"
#include "../../home/menu.h"
#include "../../home/map.h"
#include "../../home/random.h"
#include "../../home/sine.h"
#include "../../home/audio.h"
#include "player_object.h"
#include "movement.h"
#include "tile_events.h"
#include "npc_movement.h"
#include "../../data/sprites/facings.h"

uint8_t (*gMovementPointer)(struct Object*);
uint8_t* gIndexedMovement2Pointer;

// INCLUDE "data/sprites/facings.asm"

// INCLUDE "data/sprites/map_objects.asm"

// INCLUDE "engine/overworld/map_object_action.asm"
// void ObjectActionPairPointers(void){
//     //table_width ['2 + 2', 'ObjectActionPairPointers']
// //  normal action,                  frozen action
//     //dw ['SetFacingStanding', 'SetFacingStanding'];
//     //dw ['SetFacingStandAction', 'SetFacingCurrent'];
//     //dw ['SetFacingStepAction', 'SetFacingCurrent'];
//     //dw ['SetFacingBumpAction', 'SetFacingCurrent'];
//     //dw ['SetFacingCounterclockwiseSpin', 'SetFacingCurrent'];
//     //dw ['SetFacingCounterclockwiseSpin2', 'SetFacingStanding'];
//     //dw ['SetFacingFish', 'SetFacingFish'];
//     //dw ['SetFacingShadow', 'SetFacingStanding'];
//     //dw ['SetFacingEmote', 'SetFacingEmote'];
//     //dw ['SetFacingBigDollSym', 'SetFacingBigDollSym'];
//     //dw ['SetFacingBounce', 'SetFacingFreezeBounce'];
//     //dw ['SetFacingWeirdTree', 'SetFacingCurrent'];
//     //dw ['SetFacingBigDollAsym', 'SetFacingBigDollAsym'];
//     //dw ['SetFacingBigDoll', 'SetFacingBigDoll'];
//     //dw ['SetFacingBoulderDust', 'SetFacingStanding'];
//     //dw ['SetFacingGrassShake', 'SetFacingStanding'];
//     //dw ['SetFacingSkyfall', 'SetFacingCurrent'];
//     //assert_table_length ['NUM_OBJECT_ACTIONS']

//     return SetFacingStanding();
// }

static void SetFacingStanding(struct Object* bc);
static void SetFacingCurrent(struct Object* bc);
static void SetFacingStandAction(struct Object* bc);
static void SetFacingStepAction(struct Object* bc);
static void SetFacingSkyfall(struct Object* bc);
static void SetFacingBumpAction(struct Object* bc);
static void SetFacingCounterclockwiseSpin(struct Object* bc);
static void SetFacingCounterclockwiseSpin2(struct Object* bc);
static void CounterclockwiseSpinAction(struct Object* bc);
static void SetFacingFish(struct Object* bc);
static void SetFacingShadow(struct Object* bc);
static void SetFacingEmote(struct Object* bc);
static void SetFacingBigDollSym(struct Object* bc);
static void SetFacingBounce(struct Object* bc);
static void SetFacingFreezeBounce(struct Object* bc);
static void SetFacingWeirdTree(struct Object* bc);
static void SetFacingBigDollAsym(struct Object* bc);
static void SetFacingBigDoll(struct Object* bc);
static void SetFacingBoulderDust(struct Object* bc);
static void SetFacingGrassShake(struct Object* bc);

//  entries correspond to OBJECT_ACTION_* constants (see constants/map_object_constants.asm)
static void (*const ObjectActionPairPointers[][2])(struct Object*) = {
    //                                 normal action,                      frozen action
    [OBJECT_ACTION_00]              = {SetFacingStanding,                  SetFacingStanding},
    [OBJECT_ACTION_STAND]           = {SetFacingStandAction,               SetFacingCurrent},
    [OBJECT_ACTION_STEP]            = {SetFacingStepAction,                SetFacingCurrent},
    [OBJECT_ACTION_BUMP]            = {SetFacingBumpAction,                SetFacingCurrent},
    [OBJECT_ACTION_SPIN]            = {SetFacingCounterclockwiseSpin,      SetFacingCurrent},
    [OBJECT_ACTION_SPIN_FLICKER]    = {SetFacingCounterclockwiseSpin2,     SetFacingStanding},
    [OBJECT_ACTION_FISHING]         = {SetFacingFish,                      SetFacingFish},
    [OBJECT_ACTION_SHADOW]          = {SetFacingShadow,                    SetFacingStanding},
    [OBJECT_ACTION_EMOTE]           = {SetFacingEmote,                     SetFacingEmote},
    [OBJECT_ACTION_BIG_DOLL_SYM]    = {SetFacingBigDollSym,                SetFacingBigDollSym},
    [OBJECT_ACTION_BOUNCE]          = {SetFacingBounce,                    SetFacingFreezeBounce},
    [OBJECT_ACTION_WEIRD_TREE]      = {SetFacingWeirdTree,                 SetFacingCurrent},
    [OBJECT_ACTION_BIG_DOLL_ASYM]   = {SetFacingBigDollAsym,               SetFacingBigDollAsym},
    [OBJECT_ACTION_BIG_DOLL]        = {SetFacingBigDoll,                   SetFacingBigDoll},
    [OBJECT_ACTION_BOULDER_DUST]    = {SetFacingBoulderDust,               SetFacingStanding},
    [OBJECT_ACTION_GRASS_SHAKE]     = {SetFacingGrassShake,                SetFacingStanding},
    [OBJECT_ACTION_SKYFALL]         = {SetFacingSkyfall,                   SetFacingCurrent},
};

void SetFacingStanding(struct Object* bc){
    bc->facingStep = STANDING;
}

void SetFacingCurrent(struct Object* bc){
    bc->facingStep = GetSpriteDirection_Conv(bc);
}

void SetFacingStandAction(struct Object* bc){
    if(bc->facingStep & 1)
        return SetFacingStepAction(bc);
    return SetFacingCurrent(bc);
}

void SetFacingStepAction(struct Object* bc){
    // LD_HL(OBJECT_FLAGS1);
    // ADD_HL_BC;
    // BIT_hl(SLIDING_F);
    // JP_NZ (mSetFacingCurrent);
    if(bit_test(bc->flags1, SLIDING_F))
        return SetFacingCurrent(bc);

    // LD_HL(OBJECT_STEP_FRAME);
    // ADD_HL_BC;
    // LD_A_hl;
    // INC_A;
    // AND_A(0b00001111);
    // LD_hl_A;
    bc->stepFrame = (bc->stepFrame + 1) & 0b00001111;
    // RRCA;
    // RRCA;
    // a = (a >> 1) | (a << 7); 
    // a = (a >> 1) | (a << 7); 
    // maskbits(NUM_DIRECTIONS, 0);
    // LD_D_A;
    uint8_t d = (bc->stepFrame & 0b00001100) >> 2;

    // CALL(aGetSpriteDirection);
    // OR_A(FACING_STEP_DOWN_0);  // useless
    // OR_A_D;
    // LD_HL(OBJECT_FACING_STEP);
    // ADD_HL_BC;
    // LD_hl_A;
    bc->facingStep = GetSpriteDirection_Conv(bc) | d;
    // RET;
}

void SetFacingSkyfall(struct Object* bc){
    // LD_HL(OBJECT_FLAGS1);
    // ADD_HL_BC;
    // BIT_hl(SLIDING_F);
    // JP_NZ (mSetFacingCurrent);
    if(bit_test(bc->flags1, SLIDING_F))
        return SetFacingCurrent(bc);

    // LD_HL(OBJECT_STEP_FRAME);
    // ADD_HL_BC;
    // LD_A_hl;
    // ADD_A(2);
    // AND_A(0b00001111);
    // LD_hl_A;
    bc->stepFrame = (bc->stepFrame + 2) & 0b00001111;

    // RRCA;
    // RRCA;
    // maskbits(NUM_DIRECTIONS, 0);
    // LD_D_A;
    uint8_t d = (bc->stepFrame & 0b00001100) >> 2;

    // CALL(aGetSpriteDirection);
    // OR_A(FACING_STEP_DOWN_0);  // useless
    // OR_A_D;
    // LD_HL(OBJECT_FACING_STEP);
    // ADD_HL_BC;
    // LD_hl_A;
    // RET;
    bc->facingStep = GetSpriteDirection_Conv(bc) | d;
}

void SetFacingBumpAction(struct Object* bc){
    // LD_HL(OBJECT_FLAGS1);
    // ADD_HL_BC;
    // BIT_hl(SLIDING_F);
    // JP_NZ (mSetFacingCurrent);
    if(bit_test(bc->flags1, SLIDING_F))
        return SetFacingCurrent(bc);

    // LD_HL(OBJECT_STEP_FRAME);
    // ADD_HL_BC;
    // INC_hl;
    bc->stepFrame++;

    // LD_A_hl;
    // RRCA;
    // RRCA;
    // RRCA;
    // maskbits(NUM_DIRECTIONS, 0);
    // LD_D_A;
    uint8_t d = (bc->stepFrame & 0b11000) >> 3;

    // CALL(aGetSpriteDirection);
    // OR_A(FACING_STEP_DOWN_0);  // useless
    // OR_A_D;
    // LD_HL(OBJECT_FACING_STEP);
    // ADD_HL_BC;
    // LD_hl_A;
    // RET;
    bc->facingStep = GetSpriteDirection_Conv(bc) | d;
}

void SetFacingCounterclockwiseSpin(struct Object* bc){
    // CALL(aCounterclockwiseSpinAction);
    CounterclockwiseSpinAction(bc);
    // LD_HL(OBJECT_FACING);
    // ADD_HL_BC;
    // LD_A_hl;
    // OR_A(FACING_STEP_DOWN_0);  // useless
    // LD_HL(OBJECT_FACING_STEP);
    // ADD_HL_BC;
    // LD_hl_A;
    bc->facingStep = bc->facing;
    // RET;
}

void SetFacingCounterclockwiseSpin2(struct Object* bc){
    // CALL(aCounterclockwiseSpinAction);
    CounterclockwiseSpinAction(bc);
    // JP(mSetFacingStanding);
    return SetFacingStanding(bc);
}

//  Here, OBJECT_STEP_FRAME consists of two 2-bit components,
//  using only bits 0,1 and 4,5.
//  bits 0,1 is a timer (4 overworld frames)
//  bits 4,5 determines the facing - the direction is counterclockwise.
void CounterclockwiseSpinAction(struct Object* bc){
    // LD_HL(OBJECT_STEP_FRAME);
    // ADD_HL_BC;
    // LD_A_hl;
    // AND_A(0b11110000);
    // LD_E_A;
    uint8_t e = bc->stepFrame & 0b11110000;

    // LD_A_hl;
    // INC_A;
    // AND_A(0b00001111);
    // LD_D_A;
    uint8_t d = (bc->stepFrame + 1) & 0b00001111;
    // CP_A(4);
    // IF_C goto ok;
    if(d >= 4) {

        // LD_D(0);
        // LD_A_E;
        // ADD_A(0x10);
        // AND_A(0b00110000);
        // LD_E_A;
        d = 0;
        e = (e + 0x10) & 0b00110000;
    }

    // LD_A_D;
    // OR_A_E;
    // LD_hl_A;
    bc->stepFrame = d | e;

    // SWAP_E;
    e = (e >> 4) | (e << 4);
    // LD_D(0);

    
    static const uint8_t facings[] = {OW_DOWN, OW_RIGHT, OW_UP, OW_LEFT};
    // LD_HL(mCounterclockwiseSpinAction_facings);
    // ADD_HL_DE;
    // LD_A_hl;

    // LD_HL(OBJECT_FACING);
    // ADD_HL_BC;
    // LD_hl_A;
    // RET;
    bc->facing = facings[e];
}

void SetFacingFish(struct Object* bc){
    // CALL(aGetSpriteDirection);
    uint8_t a = GetSpriteDirection_Conv(bc);
    // RRCA;
    // RRCA;
    // ADD_A(FACING_FISH_DOWN);
    a = ((a & 0b11) << 6) + FACING_FISH_DOWN;
    // LD_HL(OBJECT_FACING_STEP);
    // ADD_HL_BC;
    // LD_hl_A;
    // RET;
    bc->facingStep = a;
}

void SetFacingShadow(struct Object* bc){
    // LD_HL(OBJECT_FACING_STEP);
    // ADD_HL_BC;
    // LD_hl(FACING_SHADOW);
    // RET;
    bc->facingStep = FACING_SHADOW;
}

void SetFacingEmote(struct Object* bc){
    // LD_HL(OBJECT_FACING_STEP);
    // ADD_HL_BC;
    // LD_hl(FACING_EMOTE);
    // RET;
    bc->facingStep = FACING_EMOTE;
}

void SetFacingBigDollSym(struct Object* bc){
    // LD_HL(OBJECT_FACING_STEP);
    // ADD_HL_BC;
    // LD_hl(FACING_BIG_DOLL_SYM);
    // RET;
    bc->facingStep = FACING_BIG_DOLL_SYM;
}

void SetFacingBounce(struct Object* bc){
    // LD_HL(OBJECT_STEP_FRAME);
    // ADD_HL_BC;
    // LD_A_hl;
    // INC_A;
    // AND_A(0b00001111);
    // LD_hl_A;
    bc->stepFrame = (bc->stepFrame + 1) & 0b00001111;
    // AND_A(0b00001000);
    // JR_Z (mSetFacingFreezeBounce);
    if(!(bc->stepFrame & 0b00001000))
        return SetFacingFreezeBounce(bc);
    // LD_HL(OBJECT_FACING_STEP);
    // ADD_HL_BC;
    // LD_hl(FACING_STEP_UP_0);
    // RET;
    bc->facingStep = FACING_STEP_UP_0;
}

void SetFacingFreezeBounce(struct Object* bc){
    // LD_HL(OBJECT_FACING_STEP);
    // ADD_HL_BC;
    // LD_hl(FACING_STEP_DOWN_0);
    // RET;
    bc->facingStep = FACING_STEP_DOWN_0;
}

void SetFacingWeirdTree(struct Object* bc){
    // LD_HL(OBJECT_STEP_FRAME);
    // ADD_HL_BC;
    // LD_A_hl;
    // INC_A;
    // LD_hl_A;
    bc->stepFrame++;
    // maskbits(NUM_DIRECTIONS, 2);
    uint8_t f = bc->stepFrame & (3 << 2);
    // RRCA;
    // RRCA;
    // ADD_A(FACING_WEIRD_TREE_0);
    // LD_HL(OBJECT_FACING_STEP);
    // ADD_HL_BC;
    // LD_hl_A;
    // RET;
    bc->facingStep = (f >> 2) + FACING_WEIRD_TREE_0;
}

void SetFacingBigDollAsym(struct Object* bc){
    // LD_HL(OBJECT_FACING_STEP);
    // ADD_HL_BC;
    // LD_hl(FACING_BIG_DOLL_ASYM);
    // RET;
    bc->facingStep = FACING_BIG_DOLL_ASYM;
}

void SetFacingBigDoll(struct Object* bc){
    // LD_A_addr(wVariableSprites + SPRITE_BIG_DOLL - SPRITE_VARS);
    uint8_t a = wram->wVariableSprites[SPRITE_BIG_DOLL - SPRITE_VARS];
    // LD_D(FACING_BIG_DOLL_SYM);  // symmetric
    // CP_A(SPRITE_BIG_SNORLAX);
    // IF_Z goto ok;
    // CP_A(SPRITE_BIG_LAPRAS);
    // IF_Z goto ok;
    // LD_D(FACING_BIG_DOLL_ASYM);  // asymmetric


// ok:
    // LD_HL(OBJECT_FACING_STEP);
    // ADD_HL_BC;
    // LD_hl_D;
    // RET;
    bc->facingStep = (a == SPRITE_BIG_SNORLAX || a == SPRITE_BIG_LAPRAS)? FACING_BIG_DOLL_SYM: FACING_BIG_DOLL_ASYM;
}

void SetFacingBoulderDust(struct Object* bc){
    // LD_HL(OBJECT_STEP_FRAME);
    // ADD_HL_BC;
    // INC_hl;
    bc->stepFrame++;
    // LD_A_hl;

    // LD_HL(OBJECT_FACING_STEP);
    // ADD_HL_BC;
    // AND_A(2);
    // LD_A(FACING_BOULDER_DUST_1);
    // IF_Z goto ok;
    // INC_A;
    //assert ['FACING_BOULDER_DUST_1 + 1 == FACING_BOULDER_DUST_2'];

// ok:
    // LD_hl_A;
    // RET;
    bc->facingStep = ((bc->stepFrame & 2) == 0)? FACING_BOULDER_DUST_1: FACING_BOULDER_DUST_2;
}

void SetFacingGrassShake(struct Object* bc){
    // LD_HL(OBJECT_STEP_FRAME);
    // ADD_HL_BC;
    // INC_hl;
    bc->stepFrame++;
    // LD_A_hl;
    // LD_HL(OBJECT_FACING_STEP);
    // ADD_HL_BC;
    // AND_A(4);
    // LD_A(FACING_GRASS_1);
    // IF_Z goto ok;
    // INC_A;  // FACING_GRASS_2


// ok:
    // LD_hl_A;
    // RET;
    bc->facingStep = ((bc->stepFrame & 4) == 0)? FACING_GRASS_1: FACING_GRASS_2;
}

void DeleteMapObject(void) {
    SET_PC(aDeleteMapObject);
    PUSH_BC;
    LD_HL(OBJECT_MAP_OBJECT_INDEX);
    ADD_HL_BC;
    LD_A_hl;
    PUSH_AF;
    LD_H_B;
    LD_L_C;
    LD_BC(OBJECT_LENGTH);
    XOR_A_A;
    CALL(aByteFill);
    POP_AF;
    CP_A(-1);
    IF_Z goto ok;
    BIT_A(7);
    IF_NZ goto ok;
    CALL(aGetMapObject);
    LD_HL(OBJECT_SPRITE);
    ADD_HL_BC;
    LD_hl(-1);

ok:

    POP_BC;
    RET;
}

void DeleteMapObject_Conv(struct Object* obj) {
    // SET_PC(aDeleteMapObject);
    // PUSH_BC;
    // LD_HL(OBJECT_MAP_OBJECT_INDEX);
    // ADD_HL_BC;
    // LD_A_hl;
    uint8_t a = obj->mapObjectIndex;
    // PUSH_AF;
    // LD_H_B;
    // LD_L_C;
    // LD_BC(OBJECT_LENGTH);
    // XOR_A_A;
    // CALL(aByteFill);
    ByteFill_Conv2(obj, OBJECT_LENGTH, 0);
    // POP_AF;
    // CP_A(-1);
    // IF_Z goto ok;
    if(a == 0xff)
        return;
    
    // BIT_A(7);
    // IF_NZ goto ok;
    if(bit_test(a, 7))
        return;
    
    // CALL(aGetMapObject);
    // LD_HL(OBJECT_SPRITE);
    // ADD_HL_BC;
    // LD_hl(-1);
    GetMapObject_Conv(a)->structId = 0xff;

// ok:

    // POP_BC;
    // RET;
}

void HandleObjectStep(void) {
    SET_PC(aHandleObjectStep);
    CALL(aCheckObjectStillVisible);
    RET_C;
    CALL(aHandleStepType);
    CALL(aHandleObjectAction);
    RET;
}

void HandleObjectStep_Conv(struct Object* bc) {
    // SET_PC(aHandleObjectStep);
    // CALL(aCheckObjectStillVisible);
    // RET_C;
    if(!CheckObjectStillVisible_Conv(bc))
        return;
    // CALL(aHandleStepType);
    HandleStepType_Conv(bc);
    // CALL(aHandleObjectAction);
    HandleObjectAction_Conv(bc);
    // RET;
}

void CheckObjectStillVisible(void) {
    SET_PC(aCheckObjectStillVisible);
    LD_HL(OBJECT_FLAGS2);
    ADD_HL_BC;
    RES_hl(OBJ_FLAGS2_6);
    LD_A_addr(wXCoord);
    LD_E_A;
    LD_HL(OBJECT_NEXT_MAP_X);
    ADD_HL_BC;
    LD_A_hl;
    ADD_A(1);
    SUB_A_E;
    IF_C goto ok;
    CP_A(MAPOBJECT_SCREEN_WIDTH);
    IF_NC goto ok;
    LD_A_addr(wYCoord);
    LD_E_A;
    LD_HL(OBJECT_NEXT_MAP_Y);
    ADD_HL_BC;
    LD_A_hl;
    ADD_A(1);
    SUB_A_E;
    IF_C goto ok;
    CP_A(MAPOBJECT_SCREEN_HEIGHT);
    IF_NC goto ok;
    goto yes;

ok:

    LD_HL(OBJECT_FLAGS2);
    ADD_HL_BC;
    SET_hl(OBJ_FLAGS2_6);
    LD_A_addr(wXCoord);
    LD_E_A;
    LD_HL(OBJECT_INIT_X);
    ADD_HL_BC;
    LD_A_hl;
    ADD_A(1);
    SUB_A_E;
    IF_C goto ok2;
    CP_A(MAPOBJECT_SCREEN_WIDTH);
    IF_NC goto ok2;
    LD_A_addr(wYCoord);
    LD_E_A;
    LD_HL(OBJECT_INIT_Y);
    ADD_HL_BC;
    LD_A_hl;
    ADD_A(1);
    SUB_A_E;
    IF_C goto ok2;
    CP_A(MAPOBJECT_SCREEN_HEIGHT);
    IF_NC goto ok2;

yes:

    AND_A_A;
    RET;

ok2:

    LD_HL(OBJECT_FLAGS1);
    ADD_HL_BC;
    BIT_hl(WONT_DELETE_F);
    IF_NZ goto yes2;
    CALL(aDeleteMapObject);
    SCF;
    RET;

yes2:

    LD_HL(OBJECT_FLAGS2);
    ADD_HL_BC;
    SET_hl(OBJ_FLAGS2_6);
    AND_A_A;
    RET;
}

bool CheckObjectStillVisible_Conv(struct Object* bc) {
    // SET_PC(aCheckObjectStillVisible);
    uint8_t x, y;
    // LD_HL(OBJECT_FLAGS2);
    // ADD_HL_BC;
    // RES_hl(OBJ_FLAGS2_6);
    bit_reset(bc->flags2, OBJ_FLAGS2_6);
    // LD_A_addr(wXCoord);
    // LD_E_A;
    uint8_t e = wram->wXCoord;
    // LD_HL(OBJECT_NEXT_MAP_X);
    // ADD_HL_BC;
    // LD_A_hl;
    // ADD_A(1);
    x = bc->nextMapX + 1;
    // SUB_A_E;
    // IF_C goto ok;
    // CP_A(MAPOBJECT_SCREEN_WIDTH);
    // IF_NC goto ok;
    if(x >= e && (x - e) < MAPOBJECT_SCREEN_WIDTH) {
        // LD_A_addr(wYCoord);
        // LD_E_A;
        e = wram->wYCoord;
        // LD_HL(OBJECT_NEXT_MAP_Y);
        // ADD_HL_BC;
        // LD_A_hl;
        // ADD_A(1);
        y = bc->nextMapY + 1;
        // SUB_A_E;
        // IF_C goto ok;
        // CP_A(MAPOBJECT_SCREEN_HEIGHT);
        // IF_NC goto ok;
        // goto yes;
        if(y >= e && (y - e) < MAPOBJECT_SCREEN_HEIGHT)
            return true;
    }
// ok:

    // LD_HL(OBJECT_FLAGS2);
    // ADD_HL_BC;
    // SET_hl(OBJ_FLAGS2_6);
    bit_set(bc->flags2, OBJ_FLAGS2_6);
    // LD_A_addr(wXCoord);
    // LD_E_A;
    e = wram->wXCoord;
    // LD_HL(OBJECT_INIT_X);
    // ADD_HL_BC;
    // LD_A_hl;
    // ADD_A(1);
    x = bc->initX + 1;
    // SUB_A_E;
    // IF_C goto ok2;
    // CP_A(MAPOBJECT_SCREEN_WIDTH);
    // IF_NC goto ok2;
    if(x >= e && (x - e) < MAPOBJECT_SCREEN_WIDTH) {
        // LD_A_addr(wYCoord);
        // LD_E_A;
        e = wram->wYCoord;
        // LD_HL(OBJECT_INIT_Y);
        // ADD_HL_BC;
        // LD_A_hl;
        // ADD_A(1);
        y = bc->initY + 1;
        // SUB_A_E;
        // IF_C goto ok2;
        // CP_A(MAPOBJECT_SCREEN_HEIGHT);
        // IF_NC goto ok2;
        if(y >= e && (y - e) < MAPOBJECT_SCREEN_HEIGHT) {
        // yes:
            // AND_A_A;
            // RET;
            return true;
        }
    }

// ok2:

    // LD_HL(OBJECT_FLAGS1);
    // ADD_HL_BC;
    // BIT_hl(WONT_DELETE_F);
    // IF_NZ goto yes2;
    if(!bit_test(bc->flags1, WONT_DELETE_F)) {
        // CALL(aDeleteMapObject);
        DeleteMapObject_Conv(bc);
        // SCF;
        // RET;
        return false;
    }

// yes2:

    // LD_HL(OBJECT_FLAGS2);
    // ADD_HL_BC;
    // SET_hl(OBJ_FLAGS2_6);
    bit_set(bc->flags2, OBJ_FLAGS2_6);
    // AND_A_A;
    // RET;
    return true;
}

void HandleStepType(void) {
    SET_PC(aHandleStepType);
    LD_HL(OBJECT_STEP_TYPE);
    ADD_HL_BC;
    LD_A_hl;
    AND_A_A;
    IF_Z goto zero;
    LD_HL(OBJECT_FLAGS2);
    ADD_HL_BC;
    BIT_hl(FROZEN_F);
    IF_NZ goto frozen;
    CP_A(STEP_TYPE_FROM_MOVEMENT);
    IF_Z goto one;
    goto ok3;

zero:

    CALL(aStepFunction_Reset);
    LD_HL(OBJECT_FLAGS2);
    ADD_HL_BC;
    BIT_hl(FROZEN_F);
    IF_NZ goto frozen;

one:

    CALL(aStepFunction_FromMovement);
    LD_HL(OBJECT_STEP_TYPE);
    ADD_HL_BC;
    LD_A_hl;
    AND_A_A;
    RET_Z;
    CP_A(STEP_TYPE_FROM_MOVEMENT);
    RET_Z;

ok3:

    LD_HL(mStepTypesJumptable);
    RST(aJumpTable);
    RET;

frozen:

    RET;
}

void HandleStepType_Conv(struct Object* bc) {
    // SET_PC(aHandleStepType);
    // LD_HL(OBJECT_STEP_TYPE);
    // ADD_HL_BC;
    // LD_A_hl;
    // AND_A_A;
    // IF_Z goto zero;
    if(bc->stepType == 0)
        goto zero;
    // LD_HL(OBJECT_FLAGS2);
    // ADD_HL_BC;
    // BIT_hl(FROZEN_F);
    // IF_NZ goto frozen;
    if(bit_test(bc->flags2, FROZEN_F))
        return;
    // CP_A(STEP_TYPE_FROM_MOVEMENT);
    // IF_Z goto one;
    if(bc->stepType == STEP_TYPE_FROM_MOVEMENT)
        goto one;
    goto ok3;

zero:

    // CALL(aStepFunction_Reset);
    StepFunction_Reset_Conv(bc);
    // LD_HL(OBJECT_FLAGS2);
    // ADD_HL_BC;
    // BIT_hl(FROZEN_F);
    // IF_NZ goto frozen;
    if(bit_test(bc->flags2, FROZEN_F))
        return;

one:

    // CALL(aStepFunction_FromMovement);
    StepFunction_FromMovement_Conv(bc);
    // LD_HL(OBJECT_STEP_TYPE);
    // ADD_HL_BC;
    // LD_A_hl;
    // AND_A_A;
    // RET_Z;
    // CP_A(STEP_TYPE_FROM_MOVEMENT);
    // RET_Z;
    if(bc->stepType == 0 || bc->stepType == STEP_TYPE_FROM_MOVEMENT)
        return;

ok3:

    // LD_HL(mStepTypesJumptable);
    // RST(aJumpTable);
    // RET;
    StepTypesJumptable[bc->stepType](bc);
    return;

// frozen:
    // RET;
}

void HandleObjectAction(void) {
    SET_PC(aHandleObjectAction);
    LD_HL(OBJECT_FLAGS1);
    ADD_HL_BC;
    BIT_hl(INVISIBLE_F);
    JR_NZ(mSetFacingStanding);
    LD_HL(OBJECT_FLAGS2);
    ADD_HL_BC;
    BIT_hl(OBJ_FLAGS2_6);
    JR_NZ(mSetFacingStanding);
    BIT_hl(FROZEN_F);
    JR_NZ(mv_CallFrozenObjectAction);
    //  use first column (normal)
    LD_DE(mObjectActionPairPointers);
    JR(mCallObjectAction);
}

void HandleObjectAction_Conv(struct Object* bc) {
    // SET_PC(aHandleObjectAction);
    // LD_HL(OBJECT_FLAGS1);
    // ADD_HL_BC;
    // BIT_hl(INVISIBLE_F);
    // JR_NZ(mSetFacingStanding);
    if(bit_test(bc->flags1, INVISIBLE_F))
        return SetFacing_Standing_Conv(bc), (void)0;
    // LD_HL(OBJECT_FLAGS2);
    // ADD_HL_BC;
    // BIT_hl(OBJ_FLAGS2_6);
    // JR_NZ(mSetFacingStanding);
    if(bit_test(bc->flags2, OBJ_FLAGS2_6))
        return SetFacing_Standing_Conv(bc), (void)0;
    // BIT_hl(FROZEN_F);
    // JR_NZ(mv_CallFrozenObjectAction);
    if(bit_test(bc->flags2, FROZEN_F))
        return v_CallFrozenObjectAction_Conv(bc);
    //  use first column (normal)
    // LD_DE(mObjectActionPairPointers);
    // JR(mCallObjectAction);
    return CallObjectAction_Conv(bc, 0);
}

void HandleFrozenObjectAction(void) {
    SET_PC(aHandleFrozenObjectAction);
    LD_HL(OBJECT_FLAGS1);
    ADD_HL_BC;
    BIT_hl(INVISIBLE_F);
    JR_NZ(mSetFacingStanding);
    return v_CallFrozenObjectAction();
}

void HandleFrozenObjectAction_Conv(struct Object* bc) {
    // SET_PC(aHandleFrozenObjectAction);
    // LD_HL(OBJECT_FLAGS1);
    // ADD_HL_BC;
    // BIT_hl(INVISIBLE_F);
    // JR_NZ(mSetFacingStanding);
    if(bit_test(bc->flags1, INVISIBLE_F)) {
        return SetFacing_Standing_Conv(bc), (void)0;
    }
    return v_CallFrozenObjectAction_Conv(bc);
}

void v_CallFrozenObjectAction(void) {
    SET_PC(av_CallFrozenObjectAction);
    //  use second column (frozen)
    LD_DE(mObjectActionPairPointers + 2);
    JR(mCallObjectAction);  // pointless
}

void v_CallFrozenObjectAction_Conv(struct Object* bc) {
    // SET_PC(av_CallFrozenObjectAction);
    //  use second column (frozen)
    // LD_DE(mObjectActionPairPointers + 2);
    // JR(mCallObjectAction);  // pointless
    return CallObjectAction_Conv(bc, 1);
}

void CallObjectAction(void) {
    SET_PC(aCallObjectAction);
    LD_HL(OBJECT_ACTION);
    ADD_HL_BC;
    LD_A_hl;
    LD_L_A;
    LD_H(0);
    ADD_HL_HL;
    ADD_HL_HL;
    ADD_HL_DE;
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    CALL(av_hl_);
    RET;

    return CopyNextCoordsTileToStandingCoordsTile();
}

void CallObjectAction_Conv(struct Object* bc, int column) {
    // SET_PC(aCallObjectAction);
    // LD_HL(OBJECT_ACTION);
    // ADD_HL_BC;
    // LD_A_hl;
    uint8_t action = bc->action;
    // LD_L_A;
    // LD_H(0);
    // ADD_HL_HL;
    // ADD_HL_HL;
    // ADD_HL_DE;
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // CALL(av_hl_);
    // RET;
    return ObjectActionPairPointers[action][column](bc);
}

void CopyNextCoordsTileToStandingCoordsTile(void) {
    SET_PC(aCopyNextCoordsTileToStandingCoordsTile);
    LD_HL(OBJECT_NEXT_MAP_X);
    ADD_HL_BC;
    LD_A_hl;
    LD_HL(OBJECT_MAP_X);
    ADD_HL_BC;
    LD_hl_A;
    LD_HL(OBJECT_NEXT_MAP_Y);
    ADD_HL_BC;
    LD_A_hl;
    LD_HL(OBJECT_MAP_Y);
    ADD_HL_BC;
    LD_hl_A;
    LD_HL(OBJECT_NEXT_TILE);
    ADD_HL_BC;
    LD_A_hl;
    LD_HL(OBJECT_STANDING_TILE);
    ADD_HL_BC;
    LD_hl_A;
    CALL(aSetTallGrassFlags);
    LD_HL(OBJECT_NEXT_TILE);
    ADD_HL_BC;
    LD_A_hl;
    CALL(aUselessAndA);
    RET;
}

uint8_t CopyNextCoordsTileToStandingCoordsTile_Conv(struct Object* bc) {
    // SET_PC(aCopyNextCoordsTileToStandingCoordsTile);
    // LD_HL(OBJECT_NEXT_MAP_X);
    // ADD_HL_BC;
    // LD_A_hl;
    // LD_HL(OBJECT_MAP_X);
    // ADD_HL_BC;
    // LD_hl_A;
    bc->mapX = bc->nextMapX;
    // LD_HL(OBJECT_NEXT_MAP_Y);
    // ADD_HL_BC;
    // LD_A_hl;
    // LD_HL(OBJECT_MAP_Y);
    // ADD_HL_BC;
    // LD_hl_A;
    bc->mapY = bc->nextMapY;
    // LD_HL(OBJECT_NEXT_TILE);
    // ADD_HL_BC;
    // LD_A_hl;
    // LD_HL(OBJECT_STANDING_TILE);
    // ADD_HL_BC;
    // LD_hl_A;
    bc->standingTile = bc->nextTile;
    // CALL(aSetTallGrassFlags);
    SetTallGrassFlags_Conv(bc, bc->nextTile);
    // LD_HL(OBJECT_NEXT_TILE);
    // ADD_HL_BC;
    // LD_A_hl;
    // CALL(aUselessAndA);
    // RET;
    return bc->nextTile;
}

void CopyStandingCoordsTileToNextCoordsTile_Conv(struct Object* bc) {
    // SET_PC(aCopyStandingCoordsTileToNextCoordsTile);
    // LD_HL(OBJECT_MAP_X);
    // ADD_HL_BC;
    // LD_A_hl;
    // LD_HL(OBJECT_NEXT_MAP_X);
    // ADD_HL_BC;
    // LD_hl_A;
    bc->nextMapX = bc->mapX;
    // LD_HL(OBJECT_MAP_Y);
    // ADD_HL_BC;
    // LD_A_hl;
    // LD_HL(OBJECT_NEXT_MAP_Y);
    // ADD_HL_BC;
    // LD_hl_A;
    bc->nextMapY = bc->mapY;
    // RET;
}

void CopyStandingCoordsTileToNextCoordsTile(void) {
    SET_PC(aCopyStandingCoordsTileToNextCoordsTile);
    LD_HL(OBJECT_MAP_X);
    ADD_HL_BC;
    LD_A_hl;
    LD_HL(OBJECT_NEXT_MAP_X);
    ADD_HL_BC;
    LD_hl_A;
    LD_HL(OBJECT_MAP_Y);
    ADD_HL_BC;
    LD_A_hl;
    LD_HL(OBJECT_NEXT_MAP_Y);
    ADD_HL_BC;
    LD_hl_A;
    RET;
}

void UpdateTallGrassFlags(void) {
    SET_PC(aUpdateTallGrassFlags);
    LD_HL(OBJECT_FLAGS2);
    ADD_HL_BC;
    BIT_hl(OVERHEAD_F);
    IF_Z goto ok;
    LD_HL(OBJECT_NEXT_TILE);
    ADD_HL_BC;
    LD_A_hl;
    CALL(aSetTallGrassFlags);

ok:

    LD_HL(OBJECT_NEXT_TILE);
    ADD_HL_BC;
    LD_A_hl;
    CALL(aUselessAndA);
    RET_C;  // never happens
    LD_HL(OBJECT_STANDING_TILE);
    ADD_HL_BC;
    LD_A_hl;
    CALL(aUselessAndA);
    RET;
}

void UpdateTallGrassFlags_Conv(struct Object* bc) {
    // SET_PC(aUpdateTallGrassFlags);
    // LD_HL(OBJECT_FLAGS2);
    // ADD_HL_BC;
    // BIT_hl(OVERHEAD_F);
    // IF_Z goto ok;
    if(bit_test(bc->flags2, OVERHEAD_F)) {
        // LD_HL(OBJECT_NEXT_TILE);
        // ADD_HL_BC;
        // LD_A_hl;
        // CALL(aSetTallGrassFlags);
        SetTallGrassFlags_Conv(bc, bc->nextTile);
    }
// ok:
    // LD_HL(OBJECT_NEXT_TILE);
    // ADD_HL_BC;
    // LD_A_hl;
    // CALL(aUselessAndA);
    // RET_C;  // never happens
    // LD_HL(OBJECT_STANDING_TILE);
    // ADD_HL_BC;
    // LD_A_hl;
    // CALL(aUselessAndA);
    // RET;
}

void SetTallGrassFlags(void) {
    SET_PC(aSetTallGrassFlags);
    CALL(aCheckSuperTallGrassTile);
    IF_Z goto set;
    CALL(aCheckGrassTile);
    IF_C goto reset;

set:

    LD_HL(OBJECT_FLAGS2);
    ADD_HL_BC;
    SET_hl(OVERHEAD_F);
    RET;

reset:

    LD_HL(OBJECT_FLAGS2);
    ADD_HL_BC;
    RES_hl(OVERHEAD_F);
    RET;
}

void SetTallGrassFlags_Conv(struct Object* bc, uint8_t a) {
    // SET_PC(aSetTallGrassFlags);
    // CALL(aCheckSuperTallGrassTile);
    // IF_Z goto set;
    // CALL(aCheckGrassTile);
    // IF_C goto reset;
    if(!CheckSuperTallGrassTile_Conv(a) && !CheckGrassTile_Conv(a)) {
    // reset:
        // LD_HL(OBJECT_FLAGS2);
        // ADD_HL_BC;
        // RES_hl(OVERHEAD_F);
        bit_reset(bc->flags2, OVERHEAD_F);
        // RET;
    }
    else {
    // set:
        // LD_HL(OBJECT_FLAGS2);
        // ADD_HL_BC;
        // SET_hl(OVERHEAD_F);
        bit_set(bc->flags2, OVERHEAD_F);
        // RET;
    }
}

void UselessAndA(void) {
    SET_PC(aUselessAndA);
    AND_A_A;
    RET;
}

void EndSpriteMovement(void) {
    SET_PC(aEndSpriteMovement);
    XOR_A_A;
    LD_HL(OBJECT_STEP_FRAME);
    ADD_HL_BC;
    LD_hl_A;
    LD_HL(OBJECT_MOVEMENT_BYTE_INDEX);
    ADD_HL_BC;
    LD_hli_A;
    LD_hli_A;  // OBJECT_1C
    LD_hli_A;  // OBJECT_1D
    LD_hl_A;   // OBJECT_1E
    LD_HL(OBJECT_DIRECTION_WALKING);
    ADD_HL_BC;
    LD_hl(STANDING);
    RET;
}

void EndSpriteMovement_Conv(struct Object* bc) {
    // SET_PC(aEndSpriteMovement);
    // XOR_A_A;
    // LD_HL(OBJECT_STEP_FRAME);
    // ADD_HL_BC;
    // LD_hl_A;
    bc->stepFrame = 0;
    // LD_HL(OBJECT_MOVEMENT_BYTE_INDEX);
    // ADD_HL_BC;
    // LD_hli_A;
    bc->movementByteIndex = 0;
    // LD_hli_A;  // OBJECT_1C
    bc->field_1C = 0;
    // LD_hli_A;  // OBJECT_1D
    bc->field_1D = 0;
    // LD_hl_A;   // OBJECT_1E
    bc->field_1E = 0;
    // LD_HL(OBJECT_DIRECTION_WALKING);
    // ADD_HL_BC;
    // LD_hl(STANDING);
    bc->dirWalking = STANDING;
    // RET;
}

void InitStep(void) {
    SET_PC(aInitStep);
    LD_HL(OBJECT_DIRECTION_WALKING);
    ADD_HL_BC;
    LD_hl_A;
    LD_HL(OBJECT_FLAGS1);
    ADD_HL_BC;
    BIT_hl(FIXED_FACING_F);
    JR_NZ(mGetNextTile);
    ADD_A_A;
    ADD_A_A;
    AND_A(0b00001100);
    LD_HL(OBJECT_FACING);
    ADD_HL_BC;
    LD_hl_A;
    // fallthrough

    return GetNextTile();
}

void InitStep_Conv(struct Object* bc, uint8_t a) {
    // SET_PC(aInitStep);
    // LD_HL(OBJECT_DIRECTION_WALKING);
    // ADD_HL_BC;
    // LD_hl_A;
    bc->dirWalking = a;
    // LD_HL(OBJECT_FLAGS1);
    // ADD_HL_BC;
    // BIT_hl(FIXED_FACING_F);
    // JR_NZ(mGetNextTile);
    if(!bit_test(bc->flags1, FIXED_FACING_F)) {
        // ADD_A_A;
        // ADD_A_A;
        // AND_A(0b00001100);
        // LD_HL(OBJECT_FACING);
        // ADD_HL_BC;
        // LD_hl_A;
        bc->facing = (a << 2) & 0b00001100;
    }
    // fallthrough

    return GetNextTile_Conv(bc);
}

void GetNextTile(void) {
    SET_PC(aGetNextTile);
    CALL(aGetStepVector);
    LD_HL(OBJECT_STEP_DURATION);
    ADD_HL_BC;
    LD_hl_A;
    LD_A_D;
    CALL(aGetStepVectorSign);
    LD_HL(OBJECT_MAP_X);
    ADD_HL_BC;
    ADD_A_hl;
    LD_HL(OBJECT_NEXT_MAP_X);
    ADD_HL_BC;
    LD_hl_A;
    LD_D_A;
    LD_A_E;
    CALL(aGetStepVectorSign);
    LD_HL(OBJECT_MAP_Y);
    ADD_HL_BC;
    ADD_A_hl;
    LD_HL(OBJECT_NEXT_MAP_Y);
    ADD_HL_BC;
    LD_hl_A;
    LD_E_A;
    PUSH_BC;
    CALL(aGetCoordTile);
    POP_BC;
    LD_HL(OBJECT_NEXT_TILE);
    ADD_HL_BC;
    LD_hl_A;
    RET;
}

void GetNextTile_Conv(struct Object* bc) {
    // SET_PC(aGetNextTile);
    // CALL(aGetStepVector);
    struct StepVector sv = GetStepVector_Conv(bc);
    // LD_HL(OBJECT_STEP_DURATION);
    // ADD_HL_BC;
    // LD_hl_A;
    bc->stepDuration = sv.duration;
    // LD_A_D;
    // CALL(aGetStepVectorSign);
    // LD_HL(OBJECT_MAP_X);
    // ADD_HL_BC;
    // ADD_A_hl;

    // LD_HL(OBJECT_NEXT_MAP_X);
    // ADD_HL_BC;
    // LD_hl_A;
    bc->nextMapX = bc->mapX + GetStepVectorSign_Conv(sv.x);
    // LD_D_A;
    // LD_A_E;
    // CALL(aGetStepVectorSign);
    // LD_HL(OBJECT_MAP_Y);
    // ADD_HL_BC;
    // ADD_A_hl;
    // LD_HL(OBJECT_NEXT_MAP_Y);
    // ADD_HL_BC;
    // LD_hl_A;
    bc->nextMapY = bc->mapY + GetStepVectorSign_Conv(sv.y);
    // LD_E_A;
    // PUSH_BC;
    // CALL(aGetCoordTile);
    // POP_BC;
    // LD_HL(OBJECT_NEXT_TILE);
    // ADD_HL_BC;
    // LD_hl_A;
    bc->nextTile = GetCoordTile_Conv(bc->nextMapX, bc->nextMapY);
    // RET;
}

void AddStepVector(void) {
    SET_PC(aAddStepVector);
    CALL(aGetStepVector);
    LD_HL(OBJECT_SPRITE_X);
    ADD_HL_BC;
    LD_A_hl;
    ADD_A_D;
    LD_hl_A;
    LD_HL(OBJECT_SPRITE_Y);
    ADD_HL_BC;
    LD_A_hl;
    ADD_A_E;
    LD_hl_A;
    RET;
}

struct StepVector AddStepVector_Conv(struct Object* bc) {
    // SET_PC(aAddStepVector);
    // CALL(aGetStepVector);
    struct StepVector sv = GetStepVector_Conv(bc);
    // LD_HL(OBJECT_SPRITE_X);
    // ADD_HL_BC;
    // LD_A_hl;
    // ADD_A_D;
    // LD_hl_A;
    bc->spriteX += sv.x;
    // LD_HL(OBJECT_SPRITE_Y);
    // ADD_HL_BC;
    // LD_A_hl;
    // ADD_A_E;
    // LD_hl_A;
    bc->spriteY += sv.y;
    // RET;
    return sv;
}

void GetStepVector(void) {
    SET_PC(aGetStepVector);
    //  Return (x, y, duration, speed) in (d, e, a, h).
    LD_HL(OBJECT_DIRECTION_WALKING);
    ADD_HL_BC;
    LD_A_hl;
    AND_A(0b00001111);
    ADD_A_A;
    ADD_A_A;
    LD_L_A;
    LD_H(0);
    LD_DE(mStepVectors);
    ADD_HL_DE;
    LD_D_hl;
    INC_HL;
    LD_E_hl;
    INC_HL;
    LD_A_hli;
    LD_H_hl;
    RET;
}

struct StepVector GetStepVector_Conv(struct Object* bc) {
    // SET_PC(aGetStepVector);
    //  Return (x, y, duration, speed) in (d, e, a, h).
    // LD_HL(OBJECT_DIRECTION_WALKING);
    // ADD_HL_BC;
    // LD_A_hl;
    // AND_A(0b00001111);
    // ADD_A_A;
    // ADD_A_A;
    // LD_L_A;
    // LD_H(0);
    // LD_DE(mStepVectors);
    // ADD_HL_DE;
    // LD_D_hl;
    
    // INC_HL;
    // LD_E_hl;
    // INC_HL;
    // LD_A_hli;
    // LD_H_hl;
    // RET;
    return StepVectors[bc->dirWalking & 0b00001111];
}

const struct StepVector StepVectors[] = {
    //  x,  y, duration, speed
    // slow
    { 0,  1, 16, 1},
    { 0, -1, 16, 1},
    {-1,  0, 16, 1},
    { 1,  0, 16, 1},
    // normal
    { 0,  2,  8, 2},
    { 0, -2,  8, 2},
    {-2,  0,  8, 2},
    { 2,  0,  8, 2},
    // fast
    { 0,  4,  4, 4},
    { 0, -4,  4, 4},
    {-4,  0,  4, 4},
    { 4,  0,  4, 4}
};

// void StepVectors(void) {
//     SET_PC(aStepVectors);
//     //  x,  y, duration, speed
//     // slow
//     // db ['0', '1', '16', '1'];
//     // db ['0', '-1', '16', '1'];
//     // db ['-1', '0', '16', '1'];
//     // db ['1', '0', '16', '1'];
//     // normal
//     // db ['0', '2', '8', '2'];
//     // db ['0', '-2', '8', '2'];
//     // db ['-2', '0', '8', '2'];
//     // db ['2', '0', '8', '2'];
//     // fast
//     // db ['0', '4', '4', '4'];
//     // db ['0', '-4', '4', '4'];
//     // db ['-4', '0', '4', '4'];
//     // db ['4', '0', '4', '4'];

//     return GetStepVectorSign();
// }

void GetStepVectorSign(void) {
    SET_PC(aGetStepVectorSign);
    ADD_A_A;
    RET_Z;  // 0 or 128 (-128)
    LD_A(1);
    RET_NC;  // +1 to +127
    LD_A(-1);
    RET;  // -127 to -1
}

int8_t GetStepVectorSign_Conv(int8_t a) {
    // SET_PC(aGetStepVectorSign);
    // ADD_A_A;
    // RET_Z;  // 0 or 128 (-128)
    if(a == 0)
        return 0;
    // LD_A(1);
    // RET_NC;  // +1 to +127
    if(a > 0)
        return 1;
    // LD_A(-1);
    // RET;  // -127 to -1
    return -1;
}

void UpdatePlayerStep(void) {
    SET_PC(aUpdatePlayerStep);
    LD_HL(OBJECT_DIRECTION_WALKING);
    ADD_HL_BC;
    LD_A_hl;
    AND_A(0b00000011);
    LD_addr_A(wPlayerStepDirection);
    CALL(aAddStepVector);
    LD_A_addr(wPlayerStepVectorX);
    ADD_A_D;
    LD_addr_A(wPlayerStepVectorX);
    LD_A_addr(wPlayerStepVectorY);
    ADD_A_E;
    LD_addr_A(wPlayerStepVectorY);
    LD_HL(wPlayerStepFlags);
    SET_hl(PLAYERSTEP_CONTINUE_F);
    RET;
}

void UpdatePlayerStep_Conv(struct Object* bc) {
    // SET_PC(aUpdatePlayerStep);
    // LD_HL(OBJECT_DIRECTION_WALKING);
    // ADD_HL_BC;
    // LD_A_hl;
    // AND_A(0b00000011);
    // LD_addr_A(wPlayerStepDirection);
    wram->wPlayerStepDirection = bc->dirWalking & 0b00000011;
    // CALL(aAddStepVector);
    struct StepVector sv = AddStepVector_Conv(bc);
    // LD_A_addr(wPlayerStepVectorX);
    // ADD_A_D;
    // LD_addr_A(wPlayerStepVectorX);
    wram->wPlayerStepVectorX += sv.x;
    // LD_A_addr(wPlayerStepVectorY);
    // ADD_A_E;
    // LD_addr_A(wPlayerStepVectorY);
    wram->wPlayerStepVectorY += sv.y;
    // LD_HL(wPlayerStepFlags);
    // SET_hl(PLAYERSTEP_CONTINUE_F);
    bit_set(wram->wPlayerStepFlags, PLAYERSTEP_CONTINUE_F);
    // RET;
}

void GetMapObjectField(void) {
    SET_PC(aGetMapObjectField);
    //  //  unreferenced
    PUSH_BC;
    LD_E_A;
    LD_D(0);
    LD_HL(OBJECT_MAP_OBJECT_INDEX);
    ADD_HL_BC;
    LD_A_hl;
    CALL(aGetMapObject);
    ADD_HL_DE;
    LD_A_hl;
    POP_BC;
    RET;
}

void RestoreDefaultMovement(void) {
    SET_PC(aRestoreDefaultMovement);
    LD_HL(OBJECT_MAP_OBJECT_INDEX);
    ADD_HL_BC;
    LD_A_hl;
    CP_A(-1);
    IF_Z goto ok;
    PUSH_BC;
    CALL(aGetMapObject);
    LD_HL(MAPOBJECT_MOVEMENT);
    ADD_HL_BC;
    LD_A_hl;
    POP_BC;
    RET;

ok:

    LD_A(SPRITEMOVEDATA_STANDING_DOWN);
    RET;
}

uint8_t RestoreDefaultMovement_Conv(struct Object* bc) {
    // SET_PC(aRestoreDefaultMovement);
    // LD_HL(OBJECT_MAP_OBJECT_INDEX);
    // ADD_HL_BC;
    // LD_A_hl;
    // CP_A(-1);
    // IF_Z goto ok;
    if(bc->mapObjectIndex == 0xff) {
    // ok:
        // LD_A(SPRITEMOVEDATA_STANDING_DOWN);
        // RET;
        return SPRITEMOVEDATA_STANDING_DOWN;
    }
    // PUSH_BC;
    // CALL(aGetMapObject);
    struct MapObject* obj = GetMapObject_Conv(bc->mapObjectIndex);
    // LD_HL(MAPOBJECT_MOVEMENT);
    // ADD_HL_BC;
    // LD_A_hl;
    // POP_BC;
    // RET;
    return obj->objectMovement;
}

void ObjectMovementByte_ZeroAnonJumptableIndex(void) {
    SET_PC(aObjectMovementByte_ZeroAnonJumptableIndex);
    //  //  unreferenced
    LD_HL(OBJECT_MOVEMENT_BYTE_INDEX);
    ADD_HL_BC;
    LD_hl(0);
    RET;
}

void ObjectMovementByte_IncAnonJumptableIndex(struct Object* bc) {
    // SET_PC(aObjectMovementByte_IncAnonJumptableIndex);
    // LD_HL(OBJECT_MOVEMENT_BYTE_INDEX);
    // ADD_HL_BC;
    // INC_hl;
    ++bc->movementByteIndex;
    // RET;
}

void ObjectMovementByte_DecAnonJumptableIndex(struct Object* bc) {
    // SET_PC(aObjectMovementByte_DecAnonJumptableIndex);
    // LD_HL(OBJECT_MOVEMENT_BYTE_INDEX);
    // ADD_HL_BC;
    // DEC_hl;
    --bc->movementByteIndex;
    // RET;
}

void ObjectMovementByte_AnonJumptable(void) {
    SET_PC(aObjectMovementByte_AnonJumptable);
    LD_HL(OBJECT_MOVEMENT_BYTE_INDEX);
    ADD_HL_BC;
    LD_A_hl;
    POP_HL;
    RST(aJumpTable);
    RET;
}

void Field1c_ZeroAnonJumptableIndex(struct Object* bc) {
    // SET_PC(aField1c_ZeroAnonJumptableIndex);
    // LD_HL(OBJECT_1C);
    // ADD_HL_BC;
    // LD_hl(0);
    bc->field_1C = 0;
    // RET;
}

void Field1c_IncAnonJumptableIndex(struct Object* bc) {
    // SET_PC(aField1c_IncAnonJumptableIndex);
    // LD_HL(OBJECT_1C);
    // ADD_HL_BC;
    // INC_hl;
    bc->field_1C++;
    // RET;
}

void Field1c_AnonJumptable(void) {
    /*SET_PC(aField1c_AnonJumptable);
    LD_HL(OBJECT_1C);
    ADD_HL_BC;
    LD_A_hl;
    POP_HL;
    RST(aJumpTable);
    RET;*/
}

void Field1c_GetAnonJumptableIndex(void) {
    SET_PC(aField1c_GetAnonJumptableIndex);
    //  //  unreferenced
    LD_HL(OBJECT_1C);
    ADD_HL_BC;
    LD_A_hl;
    RET;
}

void Field1c_SetAnonJumptableIndex(void) {
    SET_PC(aField1c_SetAnonJumptableIndex);
    //  //  unreferenced
    LD_HL(OBJECT_1C);
    ADD_HL_BC;
    LD_hl_A;
    RET;
}

void StepFunction_Reset(void) {
    SET_PC(aStepFunction_Reset);
    LD_HL(OBJECT_NEXT_MAP_X);
    ADD_HL_BC;
    LD_D_hl;
    LD_HL(OBJECT_NEXT_MAP_Y);
    ADD_HL_BC;
    LD_E_hl;
    PUSH_BC;
    CALL(aGetCoordTile);
    POP_BC;
    LD_HL(OBJECT_NEXT_TILE);
    ADD_HL_BC;
    LD_hl_A;
    CALL(aCopyNextCoordsTileToStandingCoordsTile);
    CALL(aEndSpriteMovement);
    LD_HL(OBJECT_STEP_TYPE);
    ADD_HL_BC;
    LD_hl(STEP_TYPE_FROM_MOVEMENT);
    RET;
}

void StepFunction_Reset_Conv(struct Object* bc) {
    // SET_PC(aStepFunction_Reset);
    // LD_HL(OBJECT_NEXT_MAP_X);
    // ADD_HL_BC;
    // LD_D_hl;
    uint8_t d = bc->nextMapX;
    // LD_HL(OBJECT_NEXT_MAP_Y);
    // ADD_HL_BC;
    // LD_E_hl;
    uint8_t e = bc->nextMapY;
    // PUSH_BC;
    // CALL(aGetCoordTile);
    uint8_t tile = GetCoordTile_Conv(d, e);
    // POP_BC;
    // LD_HL(OBJECT_NEXT_TILE);
    // ADD_HL_BC;
    // LD_hl_A;
    bc->nextTile = tile;
    // CALL(aCopyNextCoordsTileToStandingCoordsTile);
    CopyNextCoordsTileToStandingCoordsTile_Conv(bc);
    // CALL(aEndSpriteMovement);
    EndSpriteMovement_Conv(bc);
    // LD_HL(OBJECT_STEP_TYPE);
    // ADD_HL_BC;
    // LD_hl(STEP_TYPE_FROM_MOVEMENT);
    bc->stepType = STEP_TYPE_FROM_MOVEMENT;
    // RET;
}

void StepFunction_FromMovement(void) {
    SET_PC(aStepFunction_FromMovement);
    CALL(aField1c_ZeroAnonJumptableIndex);
    CALL(aGetSpriteMovementFunction);
    LD_A_hl;
    LD_HL(mStepFunction_FromMovement_Pointers);
    RST(aJumpTable);
    RET;

//Pointers:

    //  entries correspond to SPRITEMOVEFN_* constants (see constants/map_object_constants.asm)
    // table_width ['2', 'StepFunction_FromMovement.Pointers']
    // dw ['MovementFunction_Null'];  // 00
    // dw ['MovementFunction_RandomWalkY'];  // 01
    // dw ['MovementFunction_RandomWalkX'];  // 02
    // dw ['MovementFunction_RandomWalkXY'];  // 03
    // dw ['MovementFunction_RandomSpinSlow'];  // 04
    // dw ['MovementFunction_RandomSpinFast'];  // 05
    // dw ['MovementFunction_Standing'];  // 06
    // dw ['MovementFunction_ObeyDPad'];  // 07
    // dw ['MovementFunction_Indexed1'];  // 08
    // dw ['MovementFunction_Indexed2'];  // 09
    // dw ['MovementFunction_0a'];  // 0a
    // dw ['MovementFunction_0b'];  // 0b
    // dw ['MovementFunction_0c'];  // 0c
    // dw ['MovementFunction_0d'];  // 0d
    // dw ['MovementFunction_0e'];  // 0e
    // dw ['MovementFunction_Follow'];  // 0f
    // dw ['MovementFunction_Script'];  // 10
    // dw ['MovementFunction_Strength'];  // 11
    // dw ['MovementFunction_FollowNotExact'];  // 12
    // dw ['MovementFunction_Shadow'];  // 13
    // dw ['MovementFunction_Emote'];  // 14
    // dw ['MovementFunction_BigStanding'];  // 15
    // dw ['MovementFunction_Bouncing'];  // 16
    // dw ['MovementFunction_ScreenShake'];  // 17
    // dw ['MovementFunction_SpinClockwise'];  // 18
    // dw ['MovementFunction_SpinCounterclockwise'];  // 19
    // dw ['MovementFunction_BoulderDust'];  // 1a
    // dw ['MovementFunction_ShakingGrass'];  // 1b
    // assert_table_length ['NUM_SPRITEMOVEFN']
}

void StepFunction_FromMovement_Conv(struct Object* bc) {
    static void (*const Pointers[])(struct Object*) = {
    //  entries correspond to SPRITEMOVEFN_* constants (see constants/map_object_constants.asm)
    // table_width ['2', 'StepFunction_FromMovement.Pointers']
        MovementFunction_Null,  // 00
        MovementFunction_RandomWalkY,  // 01
        MovementFunction_RandomWalkX,  // 02
        MovementFunction_RandomWalkXY,  // 03
        MovementFunction_RandomSpinSlow,  // 04
        MovementFunction_RandomSpinFast,  // 05
        MovementFunction_Standing,  // 06
        MovementFunction_ObeyDPad,  // 07
        MovementFunction_Indexed1,  // 08
        MovementFunction_Indexed2,  // 09
        MovementFunction_0a,  // 0a
        MovementFunction_0b,  // 0b
        MovementFunction_0c,  // 0c
        MovementFunction_0d,  // 0d
        MovementFunction_0e,  // 0e
        MovementFunction_Follow,  // 0f
        MovementFunction_Script,  // 10
        MovementFunction_Strength,  // 11
        MovementFunction_FollowNotExact,  // 12
        MovementFunction_Shadow,  // 13
        MovementFunction_Emote,  // 14
        MovementFunction_BigStanding,  // 15
        MovementFunction_Bouncing,  // 16
        MovementFunction_ScreenShake,  // 17
        MovementFunction_SpinClockwise,  // 18
        MovementFunction_SpinCounterclockwise,  // 19
        MovementFunction_BoulderDust,  // 1a
        MovementFunction_ShakingGrass,  // 1b
    };
    // assert_table_length ['NUM_SPRITEMOVEFN']
    static_assert(lengthof(Pointers) == NUM_SPRITEMOVEFN, "");
    // SET_PC(aStepFunction_FromMovement);
    // CALL(aField1c_ZeroAnonJumptableIndex);
    Field1c_ZeroAnonJumptableIndex(bc);
    // CALL(aGetSpriteMovementFunction);
    // LD_A_hl;
    uint8_t func = GetSpriteMovementFunction_Conv(bc);
    // LD_HL(mStepFunction_FromMovement_Pointers);
    // RST(aJumpTable);
    Pointers[func](bc);
    // RET;
}

void MovementFunction_Null(struct Object* bc) {
    (void)bc;
    // SET_PC(aMovementFunction_Null);
    // RET;
}

void MovementFunction_RandomWalkY(struct Object* bc) {
    // SET_PC(aMovementFunction_RandomWalkY);
    // CALL(aRandom);
    Random_Conv();
    // LDH_A_addr(hRandomAdd);
    // AND_A(0b00000001);
    // JP(mv_RandomWalkContinue);
    v_RandomWalkContinue(bc, hram->hRandomAdd & 0b00000001);
}

void MovementFunction_RandomWalkX(struct Object* bc) {
    // SET_PC(aMovementFunction_RandomWalkX);
    // CALL(aRandom);
    Random_Conv();
    // LDH_A_addr(hRandomAdd);
    // AND_A(0b00000001);
    // OR_A(0b00000010);
    // JP(mv_RandomWalkContinue);
    v_RandomWalkContinue(bc, (hram->hRandomAdd & 0b00000001) | 0b00000010);
}

void MovementFunction_RandomWalkXY(struct Object* bc) {
    // SET_PC(aMovementFunction_RandomWalkXY);
    // CALL(aRandom);
    Random_Conv();
    // LDH_A_addr(hRandomAdd);
    // AND_A(0b00000011);
    // JP(mv_RandomWalkContinue);
    v_RandomWalkContinue(bc, hram->hRandomAdd & 0b00000011);
}

void MovementFunction_RandomSpinSlow(struct Object* bc) {
    // SET_PC(aMovementFunction_RandomSpinSlow);
    // CALL(aRandom);
    Random_Conv();
    // LDH_A_addr(hRandomAdd);
    // AND_A(0b00001100);
    // LD_HL(OBJECT_FACING);
    // ADD_HL_BC;
    // LD_hl_A;
    bc->facing = hram->hRandomAdd & 0b00001100;
    // JP(mRandomStepDuration_Slow);
    return RandomStepDuration_Slow(bc);
}

void MovementFunction_RandomSpinFast(struct Object* bc) {
    // SET_PC(aMovementFunction_RandomSpinFast);
    // LD_HL(OBJECT_FACING);
    // ADD_HL_BC;
    // LD_A_hl;
    // AND_A(0b00001100);
    // LD_D_A;
    // CALL(aRandom);
    Random_Conv();
    // LDH_A_addr(hRandomAdd);
    // AND_A(0b00001100);
    uint8_t a = hram->hRandomAdd & 0b00001100;
    // CP_A_D;
    // IF_NZ goto keep;
    if(a == (bc->facing & 0b00001100)) {
        // XOR_A(0b00001100);
        a ^= 0b00001100;
    }
// keep:
    // LD_hl_A;
    bc->facing = a;
    // JP(mRandomStepDuration_Fast);
    return RandomStepDuration_Fast(bc);
}

void MovementFunction_Standing(struct Object* bc) {
    // SET_PC(aMovementFunction_Standing);
    // CALL(aCopyStandingCoordsTileToNextCoordsTile);
    CopyStandingCoordsTileToNextCoordsTile_Conv(bc);
    // CALL(aEndSpriteMovement);
    EndSpriteMovement_Conv(bc);
    // LD_HL(OBJECT_ACTION);
    // ADD_HL_BC;
    // LD_hl(OBJECT_ACTION_STAND);
    bc->action = OBJECT_ACTION_STAND;
    // LD_HL(OBJECT_STEP_TYPE);
    // ADD_HL_BC;
    // LD_hl(STEP_TYPE_RESTORE);
    bc->stepType = STEP_TYPE_RESTORE;
    // RET;
}

void MovementFunction_ObeyDPad(struct Object* bc) {
    // SET_PC(aMovementFunction_ObeyDPad);
    // LD_HL(mGetPlayerNextMovementByte);
    // JP(mHandleMovementData);
    HandleMovementData_Conv(bc, GetPlayerNextMovementByte_Conv);
}

void MovementFunction_Indexed1(struct Object* bc) {
    // SET_PC(aMovementFunction_Indexed1);
    // LD_HL(mGetIndexedMovementByte1);
    // JP(mHandleMovementData);
    HandleMovementData_Conv(bc, GetIndexedMovementByte1_Conv);
}

void MovementFunction_Indexed2(struct Object* bc) {
    // SET_PC(aMovementFunction_Indexed2);
    // LD_HL(mGetIndexedMovementByte2);
    // JP(mHandleMovementData);
    HandleMovementData_Conv(bc, GetIndexedMovementByte2_Conv);
}

void MovementFunction_0a(struct Object* bc) {
    // SET_PC(aMovementFunction_0a);
    // JP(mv_GetMovementObject);
    v_GetMovementObject_Conv(bc);
}

void MovementFunction_0b(struct Object* bc) {
    // SET_PC(aMovementFunction_0b);
    // JP(mv_GetMovementObject);
    v_GetMovementObject_Conv(bc);
}

void MovementFunction_0c(struct Object* bc) {
    // SET_PC(aMovementFunction_0c);
    // JP(mv_GetMovementObject);
    v_GetMovementObject_Conv(bc);
}

void MovementFunction_0d(struct Object* bc) {
    // SET_PC(aMovementFunction_0d);
    // LD_HL(mGetPlayerNextMovementByte);
    // JP(mHandleMovementData);
    HandleMovementData_Conv(bc, GetPlayerNextMovementByte_Conv);
}

void MovementFunction_0e(struct Object* bc) {
    // SET_PC(aMovementFunction_0e);
    // JP(mv_GetMovementObject);
    v_GetMovementObject_Conv(bc);
}

void MovementFunction_Follow(struct Object* bc) {
    // SET_PC(aMovementFunction_Follow);
    // LD_HL(mGetFollowerNextMovementByte);
    // JP(mHandleMovementData);
    HandleMovementData_Conv(bc, GetFollowerNextMovementByte_Conv);
}

void MovementFunction_Script(struct Object* bc) {
    // SET_PC(aMovementFunction_Script);
    // LD_HL(mGetMovementByte);
    // JP(mHandleMovementData);
    HandleMovementData_Conv(bc, GetMovementByte_Conv);
}

void MovementFunction_Strength(struct Object* bc) {
    // SET_PC(aMovementFunction_Strength);
    // CALL(aObjectMovementByte_AnonJumptable);

// anon_dw:

    switch(bc->movementByteIndex) {
        case 0:
        // start:
            // LD_HL(OBJECT_NEXT_TILE);
            // ADD_HL_BC;
            // LD_A_hl;
            // CALL(aCheckPitTile);
            // IF_Z goto on_pit;
            if(CheckPitTile_Conv(bc->nextTile)) {
            // on_pit:
                // CALL(aObjectMovementByte_IncAnonJumptableIndex);
                ObjectMovementByte_IncAnonJumptableIndex(bc);
            }
            else {
                // LD_HL(OBJECT_FLAGS2);
                // ADD_HL_BC;
                // BIT_hl(OBJ_FLAGS2_2);
                bool test = bit_test(bc->flags2, OBJ_FLAGS2_2);
                // RES_hl(OBJ_FLAGS2_2);
                bit_reset(bc->flags2, OBJ_FLAGS2_2);
                // IF_Z goto ok;
                if(!test) {
                    // LD_HL(OBJECT_RANGE);
                    // ADD_HL_BC;
                    // LD_A_hl;
                    // AND_A(0b00000011);
                    // OR_A(0);
                    // CALL(aInitStep);
                    InitStep_Conv(bc, bc->range & 0b00000011);
                    // CALL(aCanObjectMoveInDirection);
                    // IF_C goto ok2;
                    if(!CanObjectMoveInDirection_Conv(bc)) {
                        // LD_DE(SFX_STRENGTH);
                        // CALL(aPlaySFX);
                        PlaySFX_Conv(SFX_STRENGTH);
                        // CALL(aSpawnStrengthBoulderDust);
                        SpawnStrengthBoulderDust_Conv(bc);
                        // CALL(aUpdateTallGrassFlags);
                        UpdateTallGrassFlags_Conv(bc);
                        // LD_HL(OBJECT_STEP_TYPE);
                        // ADD_HL_BC;
                        // LD_hl(STEP_TYPE_STRENGTH_BOULDER);
                        bc->stepType = STEP_TYPE_STRENGTH_BOULDER;
                        // RET;
                        return;
                    }
                // ok2:
                    // CALL(aCopyStandingCoordsTileToNextCoordsTile);
                    CopyStandingCoordsTileToNextCoordsTile_Conv(bc);
                }
            // ok:
                // LD_HL(OBJECT_DIRECTION_WALKING);
                // ADD_HL_BC;
                // LD_hl(STANDING);
                bc->dirWalking = STANDING;
                // RET;
                return;
            }
            fallthrough;
        case 1:
        // stop:
            // LD_HL(OBJECT_DIRECTION_WALKING);
            // ADD_HL_BC;
            // LD_hl(STANDING);
            bc->dirWalking = STANDING;
            // RET;
            return;
    }
}

void MovementFunction_FollowNotExact(struct Object* bc) {
    // SET_PC(aMovementFunction_FollowNotExact);
    // LD_HL(OBJECT_NEXT_MAP_X);
    // ADD_HL_BC;
    // LD_D_hl;
    uint8_t d = bc->nextMapX;
    // LD_HL(OBJECT_NEXT_MAP_Y);
    // ADD_HL_BC;
    // LD_E_hl;
    uint8_t e = bc->nextMapY;
    // LD_HL(OBJECT_RANGE);
    // ADD_HL_BC;
    // LD_A_hl;
    // PUSH_BC;
    // CALL(aGetObjectStruct);
    struct Object* de = GetObjectStruct_Conv(bc->range);
    // LD_HL(OBJECT_DIRECTION_WALKING);
    // ADD_HL_BC;
    // LD_A_hl;
    // CP_A(STANDING);
    // IF_Z goto standing;
    if(de->dirWalking == (uint8_t)STANDING)
        goto standing;
    uint8_t a;
    // LD_HL(OBJECT_MAP_X);
    // ADD_HL_BC;
    // LD_A_hl;
    // CP_A_D;
    // IF_Z goto equal;
    if(de->mapX == d) {
    // equal:
        // LD_HL(OBJECT_MAP_Y);
        // ADD_HL_BC;
        // LD_A_hl;
        // CP_A_E;
        // IF_Z goto standing;
        if(de->mapY == e)
            goto standing;
        // IF_C goto less2;
        else if(de->mapY < e) {
        // less2:
            // LD_A(1);
            a = 1;
        }
        else {
            // LD_A(0);
            a = 0;
            // goto done;
        }
    }
    // IF_C goto less;
    else if(de->mapX < d) {
    // less:
        // LD_A(2);
        // goto done;
        a = 2;
    }
    else {
        // LD_A(3);
        // goto done;
        a = 3;
    }

// done:

    // LD_D_A;
    // LD_HL(OBJECT_DIRECTION_WALKING);
    // ADD_HL_BC;
    // LD_A_hl;
    // AND_A(0b00001100);
    // OR_A_D;
    a |= (de->dirWalking & 0b00001100);
    // POP_BC;
    // JP(mNormalStep);
    return NormalStep(bc, a);

standing:

    // POP_BC;
    // LD_HL(OBJECT_DIRECTION_WALKING);
    // ADD_HL_BC;
    // LD_hl(STANDING);
    bc->dirWalking = STANDING;
    // LD_HL(OBJECT_ACTION);
    // ADD_HL_BC;
    // LD_hl(OBJECT_ACTION_STAND);
    bc->action = OBJECT_ACTION_STAND;
    // RET;
}

void MovementFunction_BigStanding(struct Object* bc) {
    // SET_PC(aMovementFunction_BigStanding);
    // CALL(aEndSpriteMovement);
    EndSpriteMovement_Conv(bc);
    // LD_HL(OBJECT_DIRECTION_WALKING);
    // ADD_HL_BC;
    // LD_hl(STANDING);
    bc->dirWalking = STANDING;
    // LD_HL(OBJECT_ACTION);
    // ADD_HL_BC;
    // LD_hl(OBJECT_ACTION_BIG_DOLL_SYM);
    bc->action = OBJECT_ACTION_BIG_DOLL_SYM;
    // LD_HL(OBJECT_STEP_TYPE);
    // ADD_HL_BC;
    // LD_hl(STEP_TYPE_STANDING);
    bc->stepType = STEP_TYPE_STANDING;
    // RET;
}

void MovementFunction_Bouncing(struct Object* bc) {
    // SET_PC(aMovementFunction_Bouncing);
    // CALL(aEndSpriteMovement);
    EndSpriteMovement_Conv(bc);
    // LD_HL(OBJECT_DIRECTION_WALKING);
    // ADD_HL_BC;
    // LD_hl(STANDING);
    bc->dirWalking = STANDING;
    // LD_HL(OBJECT_ACTION);
    // ADD_HL_BC;
    // LD_hl(OBJECT_ACTION_BOUNCE);
    bc->action = OBJECT_ACTION_BOUNCE;
    // LD_HL(OBJECT_STEP_TYPE);
    // ADD_HL_BC;
    // LD_hl(STEP_TYPE_STANDING);
    bc->stepType = STEP_TYPE_STANDING;
    // RET;
}

void MovementFunction_SpinCounterclockwise(struct Object* bc) {
    // SET_PC(aMovementFunction_SpinCounterclockwise);
    // CALL(aObjectMovementByte_AnonJumptable);

// anon_dw:

    switch(bc->movementByteIndex) {
        case 0: return v_MovementSpinInit(bc);
        case 1: return v_MovementSpinRepeat(bc);
        case 2: return v_MovementSpinTurnLeft(bc);
    }
}

void MovementFunction_SpinClockwise(struct Object* bc) {
    // SET_PC(aMovementFunction_SpinClockwise);
    // CALL(aObjectMovementByte_AnonJumptable);

// anon_dw:

    switch(bc->movementByteIndex) {
        case 0: return v_MovementSpinInit(bc);
        case 1: return v_MovementSpinRepeat(bc);
        case 2: return v_MovementSpinTurnRight(bc);
    }
}

void v_MovementSpinInit(struct Object* bc) {
    // SET_PC(av_MovementSpinInit);
    // CALL(aEndSpriteMovement);
    EndSpriteMovement_Conv(bc);
    // CALL(aObjectMovementByte_IncAnonJumptableIndex);
    ObjectMovementByte_IncAnonJumptableIndex(bc);
    // fallthrough

    return v_MovementSpinRepeat(bc);
}

void v_MovementSpinRepeat(struct Object* bc) {
    // SET_PC(av_MovementSpinRepeat);
    // LD_HL(OBJECT_ACTION);
    // ADD_HL_BC;
    // LD_hl(OBJECT_ACTION_STAND);
    bc->action = OBJECT_ACTION_STAND;
    // LD_HL(OBJECT_RANGE);
    // ADD_HL_BC;
    // LD_A_hl;
    // LD_A(0x10);
    // LD_HL(OBJECT_STEP_DURATION);
    // ADD_HL_BC;
    // LD_hl_A;
    bc->stepDuration = 0x10;
    // LD_HL(OBJECT_STEP_TYPE);
    // ADD_HL_BC;
    // LD_hl(STEP_TYPE_SLEEP);
    bc->stepType = STEP_TYPE_SLEEP;
    // CALL(aObjectMovementByte_IncAnonJumptableIndex);
    ObjectMovementByte_IncAnonJumptableIndex(bc);
    // RET;
}

void v_MovementSpinTurnLeft(struct Object* bc) {
    static const uint8_t facings_counterclockwise[] = {
        OW_RIGHT,
        OW_LEFT,
        OW_DOWN,
        OW_UP,
    };
    // SET_PC(av_MovementSpinTurnLeft);
    // LD_DE(mv_MovementSpinTurnLeft_facings_counterclockwise);
    // CALL(av_MovementSpinNextFacing);
    v_MovementSpinNextFacing_Conv(bc, facings_counterclockwise);
    // JR(mMovementFunction_SpinCounterclockwise);
    return MovementFunction_SpinCounterclockwise(bc);
}

void v_MovementSpinTurnRight(struct Object* bc) {
    static const uint8_t facings_clockwise[] = {
        OW_LEFT,
        OW_RIGHT,
        OW_UP,
        OW_DOWN,
    };
    // SET_PC(av_MovementSpinTurnRight);
    // LD_DE(mv_MovementSpinTurnRight_facings_clockwise);
    // CALL(av_MovementSpinNextFacing);
    v_MovementSpinNextFacing_Conv(bc, facings_clockwise);
    // JR(mMovementFunction_SpinClockwise);
    return MovementFunction_SpinClockwise(bc);
}

void v_MovementSpinNextFacing(void) {
    SET_PC(av_MovementSpinNextFacing);
    LD_HL(OBJECT_FACING);
    ADD_HL_BC;
    LD_A_hl;
    AND_A(0b00001100);
    RRCA;
    RRCA;
    PUSH_HL;
    LD_L_A;
    LD_H(0);
    ADD_HL_DE;
    LD_A_hl;
    POP_HL;
    LD_hl_A;
    CALL(aObjectMovementByte_DecAnonJumptableIndex);
    RET;
}

void v_MovementSpinNextFacing_Conv(struct Object* bc, const uint8_t* de) {
    // SET_PC(av_MovementSpinNextFacing);
    // LD_HL(OBJECT_FACING);
    // ADD_HL_BC;
    // LD_A_hl;
    // AND_A(0b00001100);
    // RRCA;
    // RRCA;
    // PUSH_HL;
    // LD_L_A;
    // LD_H(0);
    // ADD_HL_DE;
    // LD_A_hl;
    // POP_HL;
    // LD_hl_A;
    bc->facing = de[bc->facing >> 2];
    // CALL(aObjectMovementByte_DecAnonJumptableIndex);
    ObjectMovementByte_DecAnonJumptableIndex(bc);
    // RET;
}

void MovementFunction_Shadow(struct Object* bc) {
    // SET_PC(aMovementFunction_Shadow);
    // CALL(aInitMovementField1dField1e);
    struct Object* de = InitMovementField1dField1e(bc);
    // LD_HL(OBJECT_ACTION);
    // ADD_HL_BC;
    // LD_hl(OBJECT_ACTION_SHADOW);
    bc->action = OBJECT_ACTION_SHADOW;
    // LD_HL(OBJECT_STEP_DURATION);
    // ADD_HL_DE;
    // LD_A_hl;
    // INC_A;
    // ADD_A_A;
    // ADD_A(0);
    // LD_HL(OBJECT_STEP_DURATION);
    // ADD_HL_BC;
    // LD_hl_A;
    bc->stepDuration = (de->stepDuration + 1) * 2;
    // LD_HL(OBJECT_DIRECTION_WALKING);
    // ADD_HL_DE;
    // LD_A_hl;
    // maskbits(NUM_DIRECTIONS, 0);
    uint8_t d;
    uint8_t dir = de->dirWalking & 3;
    // LD_D(1 * 8 + 6);
    // CP_A(DOWN);
    // IF_Z goto ok;
    // CP_A(UP);
    // IF_Z goto ok;
    if(dir == DOWN || dir == UP) {
        d = 1 * 8 + 6;
    }
    else {
        // LD_D(1 * 8 + 4);
        d = 1 * 8 + 4;
    }
// ok:
    // LD_HL(OBJECT_SPRITE_Y_OFFSET);
    // ADD_HL_BC;
    // LD_hl_D;
    bc->spriteYOffset = d;
    // LD_HL(OBJECT_SPRITE_X_OFFSET);
    // ADD_HL_BC;
    // LD_hl(0);
    bc->spriteXOffset = 0;
    // LD_HL(OBJECT_STEP_TYPE);
    // ADD_HL_BC;
    // LD_hl(STEP_TYPE_TRACKING_OBJECT);
    bc->stepType = STEP_TYPE_TRACKING_OBJECT;
    // RET;
}

void MovementFunction_Emote(struct Object* bc) {
    // SET_PC(aMovementFunction_Emote);
    // CALL(aEndSpriteMovement);
    EndSpriteMovement_Conv(bc);
    // CALL(aInitMovementField1dField1e);
    InitMovementField1dField1e(bc);
    // LD_HL(OBJECT_ACTION);
    // ADD_HL_BC;
    // LD_hl(OBJECT_ACTION_EMOTE);
    bc->action = OBJECT_ACTION_EMOTE;
    // LD_HL(OBJECT_STEP_DURATION);
    // ADD_HL_BC;
    // LD_hl(0);
    bc->stepDuration = 0;
    // LD_HL(OBJECT_SPRITE_Y_OFFSET);
    // ADD_HL_BC;
    // LD_hl(-2 * 8);
    bc->spriteYOffset = -2 * 8;
    // LD_HL(OBJECT_SPRITE_X_OFFSET);
    // ADD_HL_BC;
    // LD_hl(0);
    bc->spriteXOffset = 0;
    // LD_HL(OBJECT_STEP_TYPE);
    // ADD_HL_BC;
    // LD_hl(STEP_TYPE_TRACKING_OBJECT);
    bc->stepType = STEP_TYPE_TRACKING_OBJECT;
    // RET;
}

void MovementFunction_BoulderDust(struct Object* bc) {
    static const struct Coords dust_coords[] = {
        //   x,  y
        {    0, -4},
        {    0,  8},
        {    6,  2},
        {   -6,  2},
    };
    // SET_PC(aMovementFunction_BoulderDust);
    // CALL(aEndSpriteMovement);
    EndSpriteMovement_Conv(bc);
    // CALL(aInitMovementField1dField1e);
    struct Object* de = InitMovementField1dField1e(bc);
    // LD_HL(OBJECT_ACTION);
    // ADD_HL_BC;
    // LD_hl(OBJECT_ACTION_BOULDER_DUST);
    bc->action = OBJECT_ACTION_BOULDER_DUST;
    // LD_HL(OBJECT_STEP_DURATION);
    // ADD_HL_DE;
    // LD_A_hl;
    // INC_A;
    // ADD_A_A;
    // LD_HL(OBJECT_STEP_DURATION);
    // ADD_HL_BC;
    // LD_hl_A;
    bc->stepDuration = (de->stepDuration + 1) * 2;
    // LD_HL(OBJECT_DIRECTION_WALKING);
    // ADD_HL_DE;
    // LD_A_hl;
    // AND_A(0b00000011);
    // LD_E_A;
    // LD_D(0);
    // LD_HL(mMovementFunction_BoulderDust_dust_coords);
    // ADD_HL_DE;
    // ADD_HL_DE;
    // LD_D_hl;
    // INC_HL;
    // LD_E_hl;
    struct Coords coord = dust_coords[de->dirWalking & 0b00000011];
    // LD_HL(OBJECT_SPRITE_X_OFFSET);
    // ADD_HL_BC;
    // LD_hl_D;
    bc->spriteXOffset = coord.x;
    // LD_HL(OBJECT_SPRITE_Y_OFFSET);
    // ADD_HL_BC;
    // LD_hl_E;
    bc->spriteYOffset = coord.y;
    // LD_HL(OBJECT_STEP_TYPE);
    // ADD_HL_BC;
    // LD_hl(STEP_TYPE_TRACKING_OBJECT);
    bc->stepType = STEP_TYPE_TRACKING_OBJECT;
    // RET;
}

void MovementFunction_ShakingGrass(struct Object* bc) {
    // SET_PC(aMovementFunction_ShakingGrass);
    // CALL(aEndSpriteMovement);
    EndSpriteMovement_Conv(bc);
    // CALL(aInitMovementField1dField1e);
    struct Object* de = InitMovementField1dField1e(bc);
    // LD_HL(OBJECT_ACTION);
    // ADD_HL_BC;
    // LD_hl(OBJECT_ACTION_GRASS_SHAKE);
    bc->action = OBJECT_ACTION_GRASS_SHAKE;
    // LD_HL(OBJECT_STEP_DURATION);
    // ADD_HL_DE;
    // LD_A_hl;
    // ADD_A(-1);
    // LD_HL(OBJECT_STEP_DURATION);
    // ADD_HL_BC;
    // LD_hl_A;
    bc->stepDuration = de->stepDuration - 1;
    // LD_HL(OBJECT_STEP_TYPE);
    // ADD_HL_BC;
    // LD_hl(STEP_TYPE_TRACKING_OBJECT);
    bc->stepType = STEP_TYPE_TRACKING_OBJECT;
    // RET;
}

struct Object* InitMovementField1dField1e(struct Object* bc) {
    // SET_PC(aInitMovementField1dField1e);
    // LD_HL(OBJECT_RANGE);
    // ADD_HL_BC;
    // LD_A_hl;
    uint8_t range = bc->range;
    // PUSH_BC;
    // CALL(aGetObjectStruct);
    // LD_D_B;
    // LD_E_C;
    // POP_BC;
    struct Object* de = GetObjectStruct_Conv(range);
    // LD_HL(OBJECT_1D);
    uint16_t vptr = de - &wram->wPlayerStruct;
    // ADD_HL_BC;
    // LD_hl_E;
    bc->field_1D = LOW(vptr);
    // INC_HL;
    // LD_hl_D;
    bc->field_1E = HIGH(vptr);
    // RET;
    return de;
}

// Returns LOW(x) = Field1e (a) and HIGH(x) = Duration (e)
static uint16_t MovementFunction_ScreenShake_GetDurationAndField1e(uint8_t a) {
    // LD_D_A;
    // AND_A(0b00111111);
    // LD_E_A;
    uint8_t e = a & 0b00111111;
    // LD_A_D;
    // RLCA;
    // RLCA;
    // AND_A(0b00000011);
    // LD_D_A;
    uint8_t d = (a >> 6) & 0b00000011;
    // INC_D;
    // LD_A(1);

    // This loop folds to n = 1 << d.
    uint8_t n = 1 << d;
    // loop:
        // DEC_D;
        // RET_Z;
        // ADD_A_A;
        // goto loop;
    return n | (e << 8);
}

void MovementFunction_ScreenShake(struct Object* bc) {
    // SET_PC(aMovementFunction_ScreenShake);
    // CALL(aEndSpriteMovement);
    EndSpriteMovement_Conv(bc);
    // LD_HL(OBJECT_ACTION);
    // ADD_HL_BC;
    // LD_hl(OBJECT_ACTION_00);
    bc->action = OBJECT_ACTION_00;
    // LD_HL(OBJECT_RANGE);
    // ADD_HL_BC;
    // LD_A_hl;
    // CALL(aMovementFunction_ScreenShake_GetDurationAndField1e);
    uint16_t res = MovementFunction_ScreenShake_GetDurationAndField1e(bc->range);
    // LD_HL(OBJECT_STEP_DURATION);
    // ADD_HL_BC;
    // LD_hl_E;
    bc->stepDuration = HIGH(res);
    // LD_HL(OBJECT_1E);
    // ADD_HL_BC;
    // LD_hl_A;
    bc->field_1E = LOW(res);
    // LD_HL(OBJECT_STEP_TYPE);
    // ADD_HL_BC;
    // LD_hl(STEP_TYPE_SCREENSHAKE);
    bc->stepType = STEP_TYPE_SCREENSHAKE;
    // RET;
}

void v_RandomWalkContinue(struct Object* bc, uint8_t a) {
    // SET_PC(av_RandomWalkContinue);
    // CALL(aInitStep);
    InitStep_Conv(bc, a);
    // CALL(aCanObjectMoveInDirection);
    // IF_C goto new_duration;
    if(CanObjectMoveInDirection_Conv(bc)) {
    // new_duration:
        // CALL(aEndSpriteMovement);
        EndSpriteMovement_Conv(bc);
        // CALL(aCopyStandingCoordsTileToNextCoordsTile);
        CopyStandingCoordsTileToNextCoordsTile_Conv(bc);
        // fallthrough

        return RandomStepDuration_Slow(bc);
    }

    // CALL(aUpdateTallGrassFlags);
    UpdateTallGrassFlags_Conv(bc);
    // LD_HL(OBJECT_ACTION);
    // ADD_HL_BC;
    // LD_hl(OBJECT_ACTION_STEP);
    bc->action = OBJECT_ACTION_STEP;
    // LD_HL(wCenteredObject);
    // LDH_A_addr(hMapObjectIndex);
    // CP_A_hl;
    // IF_Z goto centered;
    if(wram->wCenteredObject == hram->hMapObjectIndex) {
    // centered:
        // LD_HL(OBJECT_STEP_TYPE);
        // ADD_HL_BC;
        // LD_hl(STEP_TYPE_PLAYER_WALK);
        bc->stepType = STEP_TYPE_PLAYER_WALK;
        // RET;
        return;
    }
    else {
        // LD_HL(OBJECT_STEP_TYPE);
        // ADD_HL_BC;
        // LD_hl(STEP_TYPE_CONTINUE_WALK);
        bc->stepType = STEP_TYPE_CONTINUE_WALK;
        // RET;
        return;
    }
}

void RandomStepDuration_Slow(struct Object* bc) {
    // SET_PC(aRandomStepDuration_Slow);
    // CALL(aRandom);
    Random_Conv();
    // LDH_A_addr(hRandomAdd);
    // AND_A(0b01111111);
    // JR(mv_SetRandomStepDuration);
    return v_SetRandomStepDuration(bc, hram->hRandomAdd & 0b01111111);
}

void RandomStepDuration_Fast(struct Object* bc) {
    // SET_PC(aRandomStepDuration_Fast);
    // CALL(aRandom);
    Random_Conv();
    // LDH_A_addr(hRandomAdd);
    // AND_A(0b00011111);
    return v_SetRandomStepDuration(bc, hram->hRandomAdd & 0b00011111);
}

void v_SetRandomStepDuration(struct Object* bc, uint8_t a) {
    // SET_PC(av_SetRandomStepDuration);
    // LD_HL(OBJECT_STEP_DURATION);
    // ADD_HL_BC;
    // LD_hl_A;
    bc->stepDuration = a;
    // LD_HL(OBJECT_DIRECTION_WALKING);
    // ADD_HL_BC;
    // LD_hl(STANDING);
    bc->dirWalking = STANDING;
    // LD_HL(OBJECT_ACTION);
    // ADD_HL_BC;
    // LD_hl(OBJECT_ACTION_STAND);
    bc->action = OBJECT_ACTION_STAND;
    // LD_HL(OBJECT_STEP_TYPE);
    // ADD_HL_BC;
    // LD_hl(STEP_TYPE_SLEEP);
    bc->stepType = STEP_TYPE_SLEEP;
    // RET;
}

void (*const StepTypesJumptable[])(struct Object* bc) = {
    // SET_PC(aStepTypesJumptable);
    //  entries correspond to STEP_TYPE_* constants (see constants/map_object_constants.asm)
    // table_width ['2', 'StepTypesJumptable']
    [STEP_TYPE_RESET]           = StepFunction_Reset_Conv,  // 00
    [STEP_TYPE_FROM_MOVEMENT]   = StepFunction_FromMovement_Conv,  // 01
    [STEP_TYPE_NPC_WALK]        = StepFunction_NPCWalk_Conv,  // 02
    [STEP_TYPE_SLEEP]           = StepFunction_Sleep_Conv,  // 03
    [STEP_TYPE_STANDING]        = StepFunction_Standing_Conv,  // 04
    [STEP_TYPE_RESTORE]         = StepFunction_Restore_Conv,  // 05
    [STEP_TYPE_PLAYER_WALK]     = StepFunction_PlayerWalk_Conv,  // 06
    [STEP_TYPE_CONTINUE_WALK]   = StepFunction_ContinueWalk_Conv,  // 07
    [STEP_TYPE_NPC_JUMP]        = StepFunction_NPCJump_Conv,  // 08
    [STEP_TYPE_PLAYER_JUMP]     = StepFunction_PlayerJump_Conv,  // 09
    [STEP_TYPE_TURN]            = StepFunction_Turn_Conv,  // 0a
    [STEP_TYPE_BUMP]            = StepFunction_Bump_Conv,  // 0b
    [STEP_TYPE_TELEPORT_FROM]   = StepFunction_TeleportFrom_Conv,  // 0c
    [STEP_TYPE_TELEPORT_TO]     = StepFunction_TeleportTo_Conv,  // 0d
    [STEP_TYPE_SKYFALL]         = StepFunction_Skyfall_Conv,  // 0e
    [STEP_TYPE_STRENGTH_BOULDER]= StepFunction_StrengthBoulder_Conv,  // 0f
    [STEP_TYPE_GOT_BITE]        = StepFunction_GotBite_Conv,  // 10
    [STEP_TYPE_ROCK_SMASH]      = StepFunction_RockSmash_Conv,  // 11
    [STEP_TYPE_RETURN_DIG]      = StepFunction_DigTo_Conv,  // 12
    [STEP_TYPE_TRACKING_OBJECT] = StepFunction_TrackingObject_Conv,  // 13
    [STEP_TYPE_14]              = StepFunction_14_Conv,  // 14
    [STEP_TYPE_SCREENSHAKE]     = StepFunction_ScreenShake_Conv,  // 15
    //  16 and 17 are unfinished so I omitted them.
    // dw ['StepFunction_16'];  // 16
    // dw ['StepFunction_17'];  // 17
    [STEP_TYPE_DELETE]          = StepFunction_Delete_Conv,  // 18
    [STEP_TYPE_SKYFALL_TOP]     = StepFunction_SkyfallTop_Conv,  // 19
};
// assert_table_length ['NUM_STEP_TYPES']
static_assert(lengthof(StepTypesJumptable) == NUM_STEP_TYPES, "");

void WaitStep_InPlace(struct Object* bc) {
    // SET_PC(aWaitStep_InPlace);
    // LD_HL(OBJECT_STEP_DURATION);
    // ADD_HL_BC;
    // DEC_hl;
    // RET_NZ;
    if(--bc->stepDuration)
        return;
    // LD_HL(OBJECT_STEP_TYPE);
    // ADD_HL_BC;
    // LD_hl(STEP_TYPE_FROM_MOVEMENT);
    bc->stepType = STEP_TYPE_FROM_MOVEMENT;
    // RET;
}

void StepFunction_NPCJump(void) {
    SET_PC(aStepFunction_NPCJump);
    LD_HL(OBJECT_1C);
    ADD_HL_BC;
    LD_A_hl;
    if (REG_A == 0) goto Jump;
    if (REG_A == 1) goto Land;

Jump:

    CALL(aAddStepVector);
    CALL(aUpdateJumpPosition);
    LD_HL(OBJECT_STEP_DURATION);
    ADD_HL_BC;
    DEC_hl;
    RET_NZ;
    CALL(aCopyNextCoordsTileToStandingCoordsTile);
    CALL(aGetNextTile);
    LD_HL(OBJECT_FLAGS2);
    ADD_HL_BC;
    RES_hl(OVERHEAD_F);
    CALL(aField1c_IncAnonJumptableIndex);
    RET;

Land:

    CALL(aAddStepVector);
    CALL(aUpdateJumpPosition);
    LD_HL(OBJECT_STEP_DURATION);
    ADD_HL_BC;
    DEC_hl;
    RET_NZ;
    CALL(aCopyNextCoordsTileToStandingCoordsTile);
    LD_HL(OBJECT_STEP_TYPE);
    ADD_HL_BC;
    LD_hl(STEP_TYPE_FROM_MOVEMENT);
    RET;
}

void StepFunction_NPCJump_Conv(struct Object* bc) {
    // SET_PC(aStepFunction_NPCJump);
    // LD_HL(OBJECT_1C);
    // ADD_HL_BC;
    // LD_A_hl;
    // if (REG_A == 0) goto Jump;
    // if (REG_A == 1) goto Land;
    switch(bc->field_1C) {
    case 0:
    // Jump:
        // CALL(aAddStepVector);
        AddStepVector_Conv(bc);
        // CALL(aUpdateJumpPosition);
        UpdateJumpPosition();
        // LD_HL(OBJECT_STEP_DURATION);
        // ADD_HL_BC;
        // DEC_hl;
        // RET_NZ;
        if(--bc->stepDuration != 0)
            return;
        // CALL(aCopyNextCoordsTileToStandingCoordsTile);
        CopyNextCoordsTileToStandingCoordsTile_Conv(bc);
        // CALL(aGetNextTile);
        GetNextTile_Conv(bc);
        // LD_HL(OBJECT_FLAGS2);
        // ADD_HL_BC;
        // RES_hl(OVERHEAD_F);
        bit_reset(bc->flags2, OVERHEAD_F);
        // CALL(aField1c_IncAnonJumptableIndex);
        Field1c_IncAnonJumptableIndex(bc);
        // RET;
        return;

    case 1:
    // Land:
        // CALL(aAddStepVector);
        AddStepVector_Conv(bc);
        // CALL(aUpdateJumpPosition);
        UpdateJumpPosition();
        // LD_HL(OBJECT_STEP_DURATION);
        // ADD_HL_BC;
        // DEC_hl;
        // RET_NZ;
        if(--bc->stepDuration != 0)
            return;
        // CALL(aCopyNextCoordsTileToStandingCoordsTile);
        CopyNextCoordsTileToStandingCoordsTile_Conv(bc);
        // LD_HL(OBJECT_STEP_TYPE);
        // ADD_HL_BC;
        // LD_hl(STEP_TYPE_FROM_MOVEMENT);
        bc->stepType = STEP_TYPE_FROM_MOVEMENT;
        // RET;
        return;
    }
}

void StepFunction_PlayerJump(void) {
    SET_PC(aStepFunction_PlayerJump);
    LD_HL(OBJECT_1C);
    ADD_HL_BC;
    LD_A_hl;
    if (REG_A == 0) goto initjump;
    if (REG_A == 1) goto stepjump;
    if (REG_A == 2) goto initland;
    if (REG_A == 3) goto stepland;

initjump:

    LD_HL(wPlayerStepFlags);
    SET_hl(PLAYERSTEP_START_F);
    CALL(aField1c_IncAnonJumptableIndex);

stepjump:

    CALL(aUpdateJumpPosition);
    CALL(aUpdatePlayerStep);
    LD_HL(OBJECT_STEP_DURATION);
    ADD_HL_BC;
    DEC_hl;
    RET_NZ;
    CALL(aCopyNextCoordsTileToStandingCoordsTile);
    LD_HL(OBJECT_FLAGS2);
    ADD_HL_BC;
    RES_hl(OVERHEAD_F);
    LD_HL(wPlayerStepFlags);
    SET_hl(PLAYERSTEP_STOP_F);
    SET_hl(PLAYERSTEP_MIDAIR_F);
    CALL(aField1c_IncAnonJumptableIndex);
    RET;

initland:

    CALL(aGetNextTile);
    LD_HL(wPlayerStepFlags);
    SET_hl(PLAYERSTEP_START_F);
    CALL(aField1c_IncAnonJumptableIndex);

stepland:

    CALL(aUpdateJumpPosition);
    CALL(aUpdatePlayerStep);
    LD_HL(OBJECT_STEP_DURATION);
    ADD_HL_BC;
    DEC_hl;
    RET_NZ;
    LD_HL(wPlayerStepFlags);
    SET_hl(PLAYERSTEP_STOP_F);
    CALL(aCopyNextCoordsTileToStandingCoordsTile);
    LD_HL(OBJECT_STEP_TYPE);
    ADD_HL_BC;
    LD_hl(STEP_TYPE_FROM_MOVEMENT);
    RET;
}

void StepFunction_PlayerJump_Conv(struct Object* bc) {
    // SET_PC(aStepFunction_PlayerJump);
    // LD_HL(OBJECT_1C);
    // ADD_HL_BC;
    // LD_A_hl;
    switch(bc->field_1C) {
    case 0:
    // initjump:
        // LD_HL(wPlayerStepFlags);
        // SET_hl(PLAYERSTEP_START_F);
        bit_set(wram->wPlayerStepFlags, PLAYERSTEP_START_F);
        // CALL(aField1c_IncAnonJumptableIndex);
        Field1c_IncAnonJumptableIndex(bc);
        // fallthrough
    case 1:
    // stepjump:
        // CALL(aUpdateJumpPosition);
        UpdateJumpPosition_Conv(bc);
        // CALL(aUpdatePlayerStep);
        UpdatePlayerStep_Conv(bc);
        // LD_HL(OBJECT_STEP_DURATION);
        // ADD_HL_BC;
        // DEC_hl;
        // RET_NZ;
        if(--bc->stepDuration)
            return;
        // CALL(aCopyNextCoordsTileToStandingCoordsTile);
        CopyNextCoordsTileToStandingCoordsTile_Conv(bc);
        // LD_HL(OBJECT_FLAGS2);
        // ADD_HL_BC;
        // RES_hl(OVERHEAD_F);
        bit_reset(bc->flags2, OVERHEAD_F);
        // LD_HL(wPlayerStepFlags);
        // SET_hl(PLAYERSTEP_STOP_F);
        bit_set(wram->wPlayerStepFlags, PLAYERSTEP_STOP_F);
        // SET_hl(PLAYERSTEP_MIDAIR_F);
        bit_set(wram->wPlayerStepFlags, PLAYERSTEP_MIDAIR_F);
        // CALL(aField1c_IncAnonJumptableIndex);
        Field1c_IncAnonJumptableIndex(bc);
        // RET;
        return;
    // if (REG_A == 2) goto initland;
    case 2:
    // initland:
        // CALL(aGetNextTile);
        GetNextTile_Conv(bc);
        // LD_HL(wPlayerStepFlags);
        // SET_hl(PLAYERSTEP_START_F);
        bit_set(wram->wPlayerStepFlags, PLAYERSTEP_START_F);
        // CALL(aField1c_IncAnonJumptableIndex);
        Field1c_IncAnonJumptableIndex(bc);
        // fallthrough
    // if (REG_A == 3) goto stepland;
    case 3:
    // stepland:
        // CALL(aUpdateJumpPosition);
        UpdateJumpPosition_Conv(bc);
        // CALL(aUpdatePlayerStep);
        UpdatePlayerStep_Conv(bc);
        // LD_HL(OBJECT_STEP_DURATION);
        // ADD_HL_BC;
        // DEC_hl;
        // RET_NZ;
        if(--bc->stepDuration)
            return;
        // LD_HL(wPlayerStepFlags);
        // SET_hl(PLAYERSTEP_STOP_F);
        bit_set(wram->wPlayerStepFlags, PLAYERSTEP_STOP_F);
        // CALL(aCopyNextCoordsTileToStandingCoordsTile);
        CopyNextCoordsTileToStandingCoordsTile_Conv(bc);
        // LD_HL(OBJECT_STEP_TYPE);
        // ADD_HL_BC;
        // LD_hl(STEP_TYPE_FROM_MOVEMENT);
        bc->stepType = STEP_TYPE_FROM_MOVEMENT;
        // RET;
        return;
    }
}

void StepFunction_TeleportFrom(void) {
    SET_PC(aStepFunction_TeleportFrom);
    LD_HL(OBJECT_1C);
    ADD_HL_BC;
    LD_A_hl;
    if (REG_A == 0) goto InitSpin;
    if (REG_A == 1) goto DoSpin;
    if (REG_A == 2) goto InitSpinRise;
    if (REG_A == 3) goto DoSpinRise;

InitSpin:

    LD_HL(OBJECT_STEP_FRAME);
    ADD_HL_BC;
    LD_hl(0);
    LD_HL(OBJECT_STEP_DURATION);
    ADD_HL_BC;
    LD_hl(16);
    CALL(aField1c_IncAnonJumptableIndex);

DoSpin:

    LD_HL(OBJECT_ACTION);
    ADD_HL_BC;
    LD_hl(OBJECT_ACTION_SPIN);
    LD_HL(OBJECT_STEP_DURATION);
    ADD_HL_BC;
    DEC_hl;
    RET_NZ;
    CALL(aField1c_IncAnonJumptableIndex);
    RET;

InitSpinRise:

    LD_HL(OBJECT_STEP_FRAME);
    ADD_HL_BC;
    LD_hl(0);
    LD_HL(OBJECT_1F);
    ADD_HL_BC;
    LD_hl(0x10);
    LD_HL(OBJECT_STEP_DURATION);
    ADD_HL_BC;
    LD_hl(16);
    LD_HL(OBJECT_FLAGS2);
    ADD_HL_BC;
    RES_hl(OVERHEAD_F);
    CALL(aField1c_IncAnonJumptableIndex);

DoSpinRise:

    LD_HL(OBJECT_ACTION);
    ADD_HL_BC;
    LD_hl(OBJECT_ACTION_SPIN);
    LD_HL(OBJECT_1F);
    ADD_HL_BC;
    INC_hl;
    LD_A_hl;
    LD_D(0x60);
    CALL(aSine);
    LD_A_H;
    SUB_A(0x60);
    LD_HL(OBJECT_SPRITE_Y_OFFSET);
    ADD_HL_BC;
    LD_hl_A;
    LD_HL(OBJECT_STEP_DURATION);
    ADD_HL_BC;
    DEC_hl;
    RET_NZ;
    LD_HL(OBJECT_STEP_FRAME);
    ADD_HL_BC;
    LD_hl(0);
    LD_HL(OBJECT_STEP_TYPE);
    ADD_HL_BC;
    LD_hl(STEP_TYPE_FROM_MOVEMENT);
    RET;
}

void StepFunction_TeleportFrom_Conv(struct Object* bc) {
    // SET_PC(aStepFunction_TeleportFrom);
    // LD_HL(OBJECT_1C);
    // ADD_HL_BC;
    // LD_A_hl;
    switch(bc->field_1C) {
    case 0:
    // InitSpin:
        // LD_HL(OBJECT_STEP_FRAME);
        // ADD_HL_BC;
        // LD_hl(0);
        bc->stepFrame = 0;
        // LD_HL(OBJECT_STEP_DURATION);
        // ADD_HL_BC;
        // LD_hl(16);
        bc->stepDuration = 16;
        // CALL(aField1c_IncAnonJumptableIndex);
        Field1c_IncAnonJumptableIndex(bc);
        // fallthrough
    case 1:
    // DoSpin:
        // LD_HL(OBJECT_ACTION);
        // ADD_HL_BC;
        // LD_hl(OBJECT_ACTION_SPIN);
        bc->action = OBJECT_ACTION_SPIN;
        // LD_HL(OBJECT_STEP_DURATION);
        // ADD_HL_BC;
        // DEC_hl;
        // RET_NZ;
        if(--bc->stepDuration)
            return;
        // CALL(aField1c_IncAnonJumptableIndex);
        Field1c_IncAnonJumptableIndex(bc);
        // RET;
        return;
    case 2:
    // InitSpinRise:
        // LD_HL(OBJECT_STEP_FRAME);
        // ADD_HL_BC;
        // LD_hl(0);
        bc->stepFrame = 0;
        // LD_HL(OBJECT_1F);
        // ADD_HL_BC;
        // LD_hl(0x10);
        bc->field_1F = 0x10;
        // LD_HL(OBJECT_STEP_DURATION);
        // ADD_HL_BC;
        // LD_hl(16);
        bc->stepDuration = 16;
        // LD_HL(OBJECT_FLAGS2);
        // ADD_HL_BC;
        // RES_hl(OVERHEAD_F);
        bit_reset(bc->flags2, OVERHEAD_F);
        // CALL(aField1c_IncAnonJumptableIndex);
        Field1c_IncAnonJumptableIndex(bc);
        // fallthrough
    case 3:
    // DoSpinRise:
        // LD_HL(OBJECT_ACTION);
        // ADD_HL_BC;
        // LD_hl(OBJECT_ACTION_SPIN);
        bc->action = OBJECT_ACTION_SPIN;
        // LD_HL(OBJECT_1F);
        // ADD_HL_BC;
        // INC_hl;
        // LD_A_hl;
        // LD_D(0x60);
        // CALL(aSine);
        // LD_A_H;
        // SUB_A(0x60);
        // LD_HL(OBJECT_SPRITE_Y_OFFSET);
        // ADD_HL_BC;
        // LD_hl_A;
        bc->spriteYOffset = Sine_Conv(++bc->field_1F, 0x60) - 0x60;
        // LD_HL(OBJECT_STEP_DURATION);
        // ADD_HL_BC;
        // DEC_hl;
        // RET_NZ;
        if(--bc->stepDuration)
            return;
        // LD_HL(OBJECT_STEP_FRAME);
        // ADD_HL_BC;
        // LD_hl(0);
        bc->stepFrame = 0;
        // LD_HL(OBJECT_STEP_TYPE);
        // ADD_HL_BC;
        // LD_hl(STEP_TYPE_FROM_MOVEMENT);
        bc->stepType = STEP_TYPE_FROM_MOVEMENT;
        // RET;
        return;
    }
}

void StepFunction_TeleportTo(void) {
    SET_PC(aStepFunction_TeleportTo);
    LD_HL(OBJECT_1C);
    ADD_HL_BC;
    LD_A_hl;
    if (REG_A == 0) goto InitWait;
    if (REG_A == 1) goto DoWait;
    if (REG_A == 2) goto InitDescent;
    if (REG_A == 3) goto DoDescent;
    if (REG_A == 4) goto InitFinalSpin;
    if (REG_A == 5) goto DoFinalSpin;
    if (REG_A == 6) goto FinishStep;

InitWait:

    LD_HL(OBJECT_ACTION);
    ADD_HL_BC;
    LD_hl(OBJECT_ACTION_00);
    LD_HL(OBJECT_STEP_DURATION);
    ADD_HL_BC;
    LD_hl(16);
    CALL(aField1c_IncAnonJumptableIndex);
    RET;

DoWait:

    LD_HL(OBJECT_STEP_DURATION);
    ADD_HL_BC;
    DEC_hl;
    RET_NZ;
    CALL(aField1c_IncAnonJumptableIndex);

InitDescent:

    LD_HL(OBJECT_STEP_FRAME);
    ADD_HL_BC;
    LD_hl(0);
    LD_HL(OBJECT_1F);
    ADD_HL_BC;
    LD_hl(0);
    LD_HL(OBJECT_STEP_DURATION);
    ADD_HL_BC;
    LD_hl(16);
    CALL(aField1c_IncAnonJumptableIndex);
    RET;

DoDescent:

    LD_HL(OBJECT_ACTION);
    ADD_HL_BC;
    LD_hl(OBJECT_ACTION_SPIN);
    LD_HL(OBJECT_1F);
    ADD_HL_BC;
    INC_hl;
    LD_A_hl;
    LD_D(0x60);
    CALL(aSine);
    LD_A_H;
    SUB_A(0x60);
    LD_HL(OBJECT_SPRITE_Y_OFFSET);
    ADD_HL_BC;
    LD_hl_A;
    LD_HL(OBJECT_STEP_DURATION);
    ADD_HL_BC;
    DEC_hl;
    RET_NZ;
    CALL(aField1c_IncAnonJumptableIndex);

InitFinalSpin:

    LD_HL(OBJECT_STEP_DURATION);
    ADD_HL_BC;
    LD_hl(16);
    CALL(aField1c_IncAnonJumptableIndex);
    RET;

DoFinalSpin:

    LD_HL(OBJECT_ACTION);
    ADD_HL_BC;
    LD_hl(OBJECT_ACTION_SPIN);
    LD_HL(OBJECT_STEP_DURATION);
    ADD_HL_BC;
    DEC_hl;
    RET_NZ;

FinishStep:

    LD_HL(OBJECT_STEP_FRAME);
    ADD_HL_BC;
    LD_hl(0);
    LD_HL(OBJECT_SPRITE_Y_OFFSET);
    ADD_HL_BC;
    LD_hl(0);
    LD_HL(OBJECT_STEP_TYPE);
    ADD_HL_BC;
    LD_hl(STEP_TYPE_FROM_MOVEMENT);
    RET;
}

void StepFunction_TeleportTo_Conv(struct Object* bc) {
    // SET_PC(aStepFunction_TeleportTo);
    // LD_HL(OBJECT_1C);
    // ADD_HL_BC;
    // LD_A_hl;
    switch(bc->field_1C) {
    case 0:
    // InitWait:
        // LD_HL(OBJECT_ACTION);
        // ADD_HL_BC;
        // LD_hl(OBJECT_ACTION_00);
        bc->action = OBJECT_ACTION_00;
        // LD_HL(OBJECT_STEP_DURATION);
        // ADD_HL_BC;
        // LD_hl(16);
        bc->stepDuration = 16;
        // CALL(aField1c_IncAnonJumptableIndex);
        Field1c_IncAnonJumptableIndex(bc);
        // RET;
        return;
    case 1:
    // DoWait:
        // LD_HL(OBJECT_STEP_DURATION);
        // ADD_HL_BC;
        // DEC_hl;
        // RET_NZ;
        if(--bc->stepDuration)
            return;
        // CALL(aField1c_IncAnonJumptableIndex);
        Field1c_IncAnonJumptableIndex(bc);
        // fallthrough
    case 2:
    // InitDescent:
        // LD_HL(OBJECT_STEP_FRAME);
        // ADD_HL_BC;
        // LD_hl(0);
        bc->stepFrame = 0;
        // LD_HL(OBJECT_1F);
        // ADD_HL_BC;
        // LD_hl(0);
        bc->field_1F = 0;
        // LD_HL(OBJECT_STEP_DURATION);
        // ADD_HL_BC;
        // LD_hl(16);
        bc->stepDuration = 16;
        // CALL(aField1c_IncAnonJumptableIndex);
        Field1c_IncAnonJumptableIndex(bc);
        // RET;
        return;
    case 3:
    // DoDescent:
        // LD_HL(OBJECT_ACTION);
        // ADD_HL_BC;
        // LD_hl(OBJECT_ACTION_SPIN);
        bc->action = OBJECT_ACTION_SPIN;
        // LD_HL(OBJECT_1F);
        // ADD_HL_BC;
        // INC_hl;
        // LD_A_hl;
        // LD_D(0x60);
        // CALL(aSine);
        // LD_A_H;
        // SUB_A(0x60);
        // LD_HL(OBJECT_SPRITE_Y_OFFSET);
        // ADD_HL_BC;
        // LD_hl_A;
        bc->spriteYOffset = Sine_Conv(++bc->field_1F, 0x60) - 0x60;
        // LD_HL(OBJECT_STEP_DURATION);
        // ADD_HL_BC;
        // DEC_hl;
        // RET_NZ;
        if(--bc->stepDuration)
            return;
        // CALL(aField1c_IncAnonJumptableIndex);
        Field1c_IncAnonJumptableIndex(bc);
        // fallthrough
    case 4:
    // InitFinalSpin:
        // LD_HL(OBJECT_STEP_DURATION);
        // ADD_HL_BC;
        // LD_hl(16);
        bc->stepDuration = 16;
        // CALL(aField1c_IncAnonJumptableIndex);
        Field1c_IncAnonJumptableIndex(bc);
        // RET;
        return;
    case 5:
    // DoFinalSpin:
        // LD_HL(OBJECT_ACTION);
        // ADD_HL_BC;
        // LD_hl(OBJECT_ACTION_SPIN);
        bc->action = OBJECT_ACTION_SPIN;
        // LD_HL(OBJECT_STEP_DURATION);
        // ADD_HL_BC;
        // DEC_hl;
        // RET_NZ;
        if(--bc->stepDuration)
            return;
        // fallthrough
    case 6:
    // FinishStep:
        // LD_HL(OBJECT_STEP_FRAME);
        // ADD_HL_BC;
        // LD_hl(0);
        bc->stepFrame = 0;
        // LD_HL(OBJECT_SPRITE_Y_OFFSET);
        // ADD_HL_BC;
        // LD_hl(0);
        bc->spriteYOffset = 0;
        // LD_HL(OBJECT_STEP_TYPE);
        // ADD_HL_BC;
        // LD_hl(STEP_TYPE_FROM_MOVEMENT);
        bc->stepType = STEP_TYPE_FROM_MOVEMENT;
        // RET;
        return;
    }
}

void StepFunction_Skyfall(void) {
    SET_PC(aStepFunction_Skyfall);
    LD_HL(OBJECT_1C);
    ADD_HL_BC;
    LD_A_hl;
    if (REG_A == 0) goto Init;
    if (REG_A == 1) goto Step;
    if (REG_A == 2) goto Fall;
    if (REG_A == 3) goto Finish;

Init:

    LD_HL(OBJECT_ACTION);
    ADD_HL_BC;
    LD_hl(OBJECT_ACTION_00);
    LD_HL(OBJECT_STEP_DURATION);
    ADD_HL_BC;
    LD_hl(16);
    CALL(aField1c_IncAnonJumptableIndex);

Step:

    LD_HL(OBJECT_STEP_DURATION);
    ADD_HL_BC;
    DEC_hl;
    RET_NZ;
    LD_HL(OBJECT_ACTION);
    ADD_HL_BC;
    LD_hl(OBJECT_ACTION_STEP);
    LD_HL(OBJECT_STEP_FRAME);
    ADD_HL_BC;
    LD_hl(0);
    LD_HL(OBJECT_1F);
    ADD_HL_BC;
    LD_hl(0);
    LD_HL(OBJECT_STEP_DURATION);
    ADD_HL_BC;
    LD_hl(16);
    CALL(aField1c_IncAnonJumptableIndex);

Fall:

    LD_HL(OBJECT_1F);
    ADD_HL_BC;
    INC_hl;
    LD_A_hl;
    LD_D(0x60);
    CALL(aSine);
    LD_A_H;
    SUB_A(0x60);
    LD_HL(OBJECT_SPRITE_Y_OFFSET);
    ADD_HL_BC;
    LD_hl_A;
    LD_HL(OBJECT_STEP_DURATION);
    ADD_HL_BC;
    DEC_hl;
    RET_NZ;
    CALL(aField1c_IncAnonJumptableIndex);

Finish:

    LD_HL(OBJECT_STEP_FRAME);
    ADD_HL_BC;
    LD_hl(0);
    LD_HL(OBJECT_SPRITE_Y_OFFSET);
    ADD_HL_BC;
    LD_hl(0);
    LD_HL(OBJECT_STEP_TYPE);
    ADD_HL_BC;
    LD_hl(STEP_TYPE_FROM_MOVEMENT);
    RET;
}

void StepFunction_Skyfall_Conv(struct Object* bc) {
    // SET_PC(aStepFunction_Skyfall);
    // LD_HL(OBJECT_1C);
    // ADD_HL_BC;
    // LD_A_hl;
    switch(bc->field_1C) {
    case 0:
    // Init:
        // LD_HL(OBJECT_ACTION);
        // ADD_HL_BC;
        // LD_hl(OBJECT_ACTION_00);
        bc->action = OBJECT_ACTION_00;
        // LD_HL(OBJECT_STEP_DURATION);
        // ADD_HL_BC;
        // LD_hl(16);
        bc->stepDuration = 16;
        // CALL(aField1c_IncAnonJumptableIndex);
        Field1c_IncAnonJumptableIndex(bc);
        // fallthrough
    case 1:
    // Step:
        // LD_HL(OBJECT_STEP_DURATION);
        // ADD_HL_BC;
        // DEC_hl;
        // RET_NZ;
        if(--bc->stepDuration)
            return;
        // LD_HL(OBJECT_ACTION);
        // ADD_HL_BC;
        // LD_hl(OBJECT_ACTION_STEP);
        bc->action = OBJECT_ACTION_STEP;
        // LD_HL(OBJECT_STEP_FRAME);
        // ADD_HL_BC;
        // LD_hl(0);
        bc->stepFrame = 0;
        // LD_HL(OBJECT_1F);
        // ADD_HL_BC;
        // LD_hl(0);
        bc->field_1F = 0;
        // LD_HL(OBJECT_STEP_DURATION);
        // ADD_HL_BC;
        // LD_hl(16);
        bc->stepDuration = 16;
        // CALL(aField1c_IncAnonJumptableIndex);
        Field1c_IncAnonJumptableIndex(bc);
        // fallthrough
    case 2:
    // Fall:
        // LD_HL(OBJECT_1F);
        // ADD_HL_BC;
        // INC_hl;
        // LD_A_hl;
        // LD_D(0x60);
        // CALL(aSine);
        // LD_A_H;
        // SUB_A(0x60);
        // LD_HL(OBJECT_SPRITE_Y_OFFSET);
        // ADD_HL_BC;
        // LD_hl_A;
        bc->spriteYOffset = Sine_Conv(++bc->field_1F, 0x60) - 0x60;
        // LD_HL(OBJECT_STEP_DURATION);
        // ADD_HL_BC;
        // DEC_hl;
        // RET_NZ;
        if(--bc->stepDuration)
            return;
        // CALL(aField1c_IncAnonJumptableIndex);
        Field1c_IncAnonJumptableIndex(bc);
        // fallthrough
    case 3:
    // Finish:
        // LD_HL(OBJECT_STEP_FRAME);
        // ADD_HL_BC;
        // LD_hl(0);
        bc->stepFrame = 0;
        // LD_HL(OBJECT_SPRITE_Y_OFFSET);
        // ADD_HL_BC;
        // LD_hl(0);
        bc->spriteYOffset = 0;
        // LD_HL(OBJECT_STEP_TYPE);
        // ADD_HL_BC;
        // LD_hl(STEP_TYPE_FROM_MOVEMENT);
        bc->stepType = STEP_TYPE_FROM_MOVEMENT;
        // RET;
        return;
    }
}

void StepFunction_GotBite(void) {
    SET_PC(aStepFunction_GotBite);
    LD_HL(OBJECT_1C);
    ADD_HL_BC;
    LD_A_hl;
    if (REG_A == 0) goto Init;
    if (REG_A == 1) goto Run;

Init:

    LD_HL(OBJECT_STEP_DURATION);
    ADD_HL_BC;
    LD_hl(8);
    LD_HL(OBJECT_SPRITE_Y_OFFSET);
    ADD_HL_BC;
    LD_hl(0);
    CALL(aField1c_IncAnonJumptableIndex);

Run:

    LD_HL(OBJECT_SPRITE_Y_OFFSET);
    ADD_HL_BC;
    LD_A_hl;
    XOR_A(1);
    LD_hl_A;
    LD_HL(OBJECT_STEP_DURATION);
    ADD_HL_BC;
    DEC_hl;
    RET_NZ;
    LD_HL(OBJECT_SPRITE_Y_OFFSET);
    ADD_HL_BC;
    LD_hl(0);
    LD_HL(OBJECT_STEP_TYPE);
    ADD_HL_BC;
    LD_hl(STEP_TYPE_FROM_MOVEMENT);
    RET;
}

void StepFunction_GotBite_Conv(struct Object* bc) {
    // SET_PC(aStepFunction_GotBite);
    // LD_HL(OBJECT_1C);
    // ADD_HL_BC;
    // LD_A_hl;
    switch(bc->field_1C) {
    case 0:
    // Init:
        // LD_HL(OBJECT_STEP_DURATION);
        // ADD_HL_BC;
        // LD_hl(8);
        bc->stepDuration = 8;
        // LD_HL(OBJECT_SPRITE_Y_OFFSET);
        // ADD_HL_BC;
        // LD_hl(0);
        bc->spriteYOffset = 0;
        // CALL(aField1c_IncAnonJumptableIndex);
        Field1c_IncAnonJumptableIndex(bc);
        // fallthrough
    case 1:
    // Run:
        // LD_HL(OBJECT_SPRITE_Y_OFFSET);
        // ADD_HL_BC;
        // LD_A_hl;
        // XOR_A(1);
        // LD_hl_A;
        bc->spriteYOffset ^= 1;
        // LD_HL(OBJECT_STEP_DURATION);
        // ADD_HL_BC;
        // DEC_hl;
        // RET_NZ;
        if(--bc->stepDuration)
            return;
        // LD_HL(OBJECT_SPRITE_Y_OFFSET);
        // ADD_HL_BC;
        // LD_hl(0);
        bc->spriteYOffset = 0;
        // LD_HL(OBJECT_STEP_TYPE);
        // ADD_HL_BC;
        // LD_hl(STEP_TYPE_FROM_MOVEMENT);
        bc->stepType = STEP_TYPE_FROM_MOVEMENT;
        // RET;
        return;
    }
}

void StepFunction_RockSmash(void) {
    SET_PC(aStepFunction_RockSmash);
    CALL(aStepFunction_RockSmash_Step);
    JP(mWaitStep_InPlace);

Step:

    LD_HL(OBJECT_STEP_DURATION);
    ADD_HL_BC;
    LD_A_hl;
    AND_A(0b00000001);
    LD_A(OBJECT_ACTION_STAND);
    IF_Z goto yes;
    LD_A(OBJECT_ACTION_00);

yes:

    LD_HL(OBJECT_ACTION);
    ADD_HL_BC;
    LD_hl_A;
    RET;
}

void StepFunction_RockSmash_Conv(struct Object* bc) {
    // SET_PC(aStepFunction_RockSmash);
    // CALL(aStepFunction_RockSmash_Step);
    // JP(mWaitStep_InPlace);

// Step:

    // LD_HL(OBJECT_STEP_DURATION);
    // ADD_HL_BC;
    // LD_A_hl;
    // AND_A(0b00000001);
    // LD_A(OBJECT_ACTION_STAND);
    // IF_Z goto yes;
    // LD_A(OBJECT_ACTION_00);

// yes:

    // LD_HL(OBJECT_ACTION);
    // ADD_HL_BC;
    // LD_hl_A;
    bc->action = (bc->stepDuration & 0b00000001)? OBJECT_ACTION_00: OBJECT_ACTION_STAND;
    // RET;
    return WaitStep_InPlace(bc);
}

void StepFunction_DigTo(void) {
    SET_PC(aStepFunction_DigTo);
    LD_HL(OBJECT_STEP_DURATION);
    ADD_HL_BC;
    LD_A_hl;
    AND_A(0b00000001);
    LD_A(OBJECT_ACTION_SPIN);
    IF_Z goto yes;
    LD_A(OBJECT_ACTION_SPIN_FLICKER);

yes:

    LD_HL(OBJECT_ACTION);
    ADD_HL_BC;
    LD_hl_A;
    JP(mWaitStep_InPlace);
}

void StepFunction_DigTo_Conv(struct Object* bc) {
    // SET_PC(aStepFunction_DigTo);
    // LD_HL(OBJECT_STEP_DURATION);
    // ADD_HL_BC;
    // LD_A_hl;
    // AND_A(0b00000001);
    // LD_A(OBJECT_ACTION_SPIN);
    // IF_Z goto yes;
    // LD_A(OBJECT_ACTION_SPIN_FLICKER);

// yes:

    // LD_HL(OBJECT_ACTION);
    // ADD_HL_BC;
    // LD_hl_A;
    bc->action = ((bc->stepDuration & 0b00000001) == 0)? OBJECT_ACTION_SPIN: OBJECT_ACTION_SPIN_FLICKER;
    // JP(mWaitStep_InPlace);
    return WaitStep_InPlace(bc);
}

void StepFunction_Sleep(void) {
    SET_PC(aStepFunction_Sleep);
    LD_HL(OBJECT_DIRECTION_WALKING);
    ADD_HL_BC;
    LD_hl(STANDING);
    LD_HL(OBJECT_STEP_DURATION);
    ADD_HL_BC;
    DEC_hl;
    RET_NZ;
    LD_HL(OBJECT_STEP_TYPE);
    ADD_HL_BC;
    LD_hl(STEP_TYPE_FROM_MOVEMENT);
    RET;
}

void StepFunction_Sleep_Conv(struct Object* bc) {
    // SET_PC(aStepFunction_Sleep);
    // LD_HL(OBJECT_DIRECTION_WALKING);
    // ADD_HL_BC;
    // LD_hl(STANDING);
    bc->dirWalking = STANDING;
    // LD_HL(OBJECT_STEP_DURATION);
    // ADD_HL_BC;
    // DEC_hl;
    // RET_NZ;
    if(--bc->stepDuration)
        return;
    // LD_HL(OBJECT_STEP_TYPE);
    // ADD_HL_BC;
    // LD_hl(STEP_TYPE_FROM_MOVEMENT);
    bc->stepType = STEP_TYPE_FROM_MOVEMENT;
    // RET;
}

void StepFunction_Delete(void) {
    SET_PC(aStepFunction_Delete);
    LD_HL(OBJECT_DIRECTION_WALKING);
    ADD_HL_BC;
    LD_hl(STANDING);
    LD_HL(OBJECT_STEP_DURATION);
    ADD_HL_BC;
    DEC_hl;
    RET_NZ;
    JP(mDeleteMapObject);
}

void StepFunction_Delete_Conv(struct Object* bc) {
    // SET_PC(aStepFunction_Delete);
    // LD_HL(OBJECT_DIRECTION_WALKING);
    // ADD_HL_BC;
    // LD_hl(STANDING);
    bc->dirWalking = STANDING;
    // LD_HL(OBJECT_STEP_DURATION);
    // ADD_HL_BC;
    // DEC_hl;
    // RET_NZ;
    if(--bc->stepDuration)
        return;
    // JP(mDeleteMapObject);
    DeleteMapObject_Conv(bc);
}

void StepFunction_Bump(void) {
    SET_PC(aStepFunction_Bump);
    LD_HL(OBJECT_STEP_DURATION);
    ADD_HL_BC;
    DEC_hl;
    RET_NZ;
    LD_HL(OBJECT_STEP_TYPE);
    ADD_HL_BC;
    LD_hl(STEP_TYPE_FROM_MOVEMENT);
    RET;
}

void StepFunction_Bump_Conv(struct Object* bc) {
    // SET_PC(aStepFunction_Bump);
    // LD_HL(OBJECT_STEP_DURATION);
    // ADD_HL_BC;
    // DEC_hl;
    // RET_NZ;
    if(--bc->stepDuration)
        return;
    // LD_HL(OBJECT_STEP_TYPE);
    // ADD_HL_BC;
    // LD_hl(STEP_TYPE_FROM_MOVEMENT);
    bc->stepType = STEP_TYPE_FROM_MOVEMENT;
    // RET;
}

void StepFunction_Restore(void) {
    SET_PC(aStepFunction_Restore);
    LD_HL(OBJECT_1C);
    ADD_HL_BC;
    LD_A_hl;
    if (REG_A == 0) goto Reset;
    if (REG_A == 1) goto StepFunction_Standing;

Reset:

    CALL(aRestoreDefaultMovement);
    CALL(aGetInitialFacing);
    LD_HL(OBJECT_FACING);
    ADD_HL_BC;
    LD_hl_A;
    CALL(aField1c_IncAnonJumptableIndex);
    // fallthrough
StepFunction_Standing:
    return StepFunction_Standing();
}

void StepFunction_Restore_Conv(struct Object* bc) {
    // SET_PC(aStepFunction_Restore);
    // LD_HL(OBJECT_1C);
    // ADD_HL_BC;
    // LD_A_hl;
    switch(bc->field_1C) {
    case 0:
    // Reset:
        // CALL(aRestoreDefaultMovement);
        // CALL(aGetInitialFacing);
        // LD_HL(OBJECT_FACING);
        // ADD_HL_BC;
        // LD_hl_A;
        bc->facing = GetInitialFacing_Conv(RestoreDefaultMovement_Conv(bc));
        // CALL(aField1c_IncAnonJumptableIndex);
        Field1c_IncAnonJumptableIndex(bc);
        // fallthrough
    case 1:
    // StepFunction_Standing:
        return StepFunction_Standing_Conv(bc);
    }
}

void StepFunction_Standing(void) {
    SET_PC(aStepFunction_Standing);
    CALL(aStubbed_UpdateYOffset);
    LD_HL(OBJECT_DIRECTION_WALKING);
    ADD_HL_BC;
    LD_hl(STANDING);
    RET;
}

void StepFunction_Standing_Conv(struct Object* bc) {
    // SET_PC(aStepFunction_Standing);
    // CALL(aStubbed_UpdateYOffset);
    // LD_HL(OBJECT_DIRECTION_WALKING);
    // ADD_HL_BC;
    // LD_hl(STANDING);
    bc->dirWalking = STANDING;
    // RET;
}

void StepFunction_NPCWalk(void) {
    SET_PC(aStepFunction_NPCWalk);
    CALL(aStubbed_UpdateYOffset);
    CALL(aAddStepVector);
    LD_HL(OBJECT_STEP_DURATION);
    ADD_HL_BC;
    DEC_hl;
    RET_NZ;
    CALL(aCopyNextCoordsTileToStandingCoordsTile);
    LD_HL(OBJECT_DIRECTION_WALKING);
    ADD_HL_BC;
    LD_hl(STANDING);
    LD_HL(OBJECT_STEP_TYPE);
    ADD_HL_BC;
    LD_hl(STEP_TYPE_FROM_MOVEMENT);
    RET;
}

void StepFunction_NPCWalk_Conv(struct Object* bc) {
    // SET_PC(aStepFunction_NPCWalk);
    // CALL(aStubbed_UpdateYOffset);
    //  Stubbed so no point to call Stubbed_UpdateYOffset
    // CALL(aAddStepVector);
    AddStepVector_Conv(bc);
    // LD_HL(OBJECT_STEP_DURATION);
    // ADD_HL_BC;
    // DEC_hl;
    // RET_NZ;
    if(--bc->stepDuration != 0)
        return;
    // CALL(aCopyNextCoordsTileToStandingCoordsTile);
    CopyNextCoordsTileToStandingCoordsTile_Conv(bc);
    // LD_HL(OBJECT_DIRECTION_WALKING);
    // ADD_HL_BC;
    // LD_hl(STANDING);
    bc->dirWalking = STANDING;
    // LD_HL(OBJECT_STEP_TYPE);
    // ADD_HL_BC;
    // LD_hl(STEP_TYPE_FROM_MOVEMENT);
    bc->stepType = STEP_TYPE_FROM_MOVEMENT;
    // RET;
}

void StepFunction_ContinueWalk(void) {
    SET_PC(aStepFunction_ContinueWalk);
    CALL(aAddStepVector);
    LD_HL(OBJECT_STEP_DURATION);
    ADD_HL_BC;
    DEC_hl;
    RET_NZ;
    CALL(aCopyNextCoordsTileToStandingCoordsTile);
    JP(mRandomStepDuration_Slow);
}

void StepFunction_ContinueWalk_Conv(struct Object* bc) {
    // SET_PC(aStepFunction_ContinueWalk);
    // CALL(aAddStepVector);
    AddStepVector_Conv(bc);
    // LD_HL(OBJECT_STEP_DURATION);
    // ADD_HL_BC;
    // DEC_hl;
    // RET_NZ;
    if(--bc->stepDuration != 0)
        return;
    // CALL(aCopyNextCoordsTileToStandingCoordsTile);
    CopyNextCoordsTileToStandingCoordsTile_Conv(bc);
    // JP(mRandomStepDuration_Slow);
    return RandomStepDuration_Slow(bc);
}

void StepFunction_PlayerWalk(void) {
    SET_PC(aStepFunction_PlayerWalk);
    LD_HL(OBJECT_1C);
    ADD_HL_BC;
    LD_A_hl;
    if (REG_A == 0) goto init;
    if (REG_A == 1) goto step;

init:

    LD_HL(wPlayerStepFlags);
    SET_hl(PLAYERSTEP_START_F);
    CALL(aField1c_IncAnonJumptableIndex);

step:

    CALL(aUpdatePlayerStep);
    LD_HL(OBJECT_STEP_DURATION);
    ADD_HL_BC;
    DEC_hl;
    RET_NZ;
    LD_HL(wPlayerStepFlags);
    SET_hl(PLAYERSTEP_STOP_F);
    CALL(aCopyNextCoordsTileToStandingCoordsTile);
    LD_HL(OBJECT_DIRECTION_WALKING);
    ADD_HL_BC;
    LD_hl(STANDING);
    LD_HL(OBJECT_STEP_TYPE);
    ADD_HL_BC;
    LD_hl(STEP_TYPE_FROM_MOVEMENT);
    RET;
}

void StepFunction_PlayerWalk_Conv(struct Object* bc) {
    // SET_PC(aStepFunction_PlayerWalk);
    // LD_HL(OBJECT_1C);
    // ADD_HL_BC;
    // LD_A_hl;
    switch(bc->field_1C) {
    case 0:
    // init:
        // LD_HL(wPlayerStepFlags);
        // SET_hl(PLAYERSTEP_START_F);
        bit_set(wram->wPlayerStepFlags, PLAYERSTEP_START_F);
        // CALL(aField1c_IncAnonJumptableIndex);
        Field1c_IncAnonJumptableIndex(bc);
        // fallthrough
    // if (REG_A == 1) goto step;
    case 1:
    // step:
        // CALL(aUpdatePlayerStep);
        UpdatePlayerStep_Conv(bc);
        // LD_HL(OBJECT_STEP_DURATION);
        // ADD_HL_BC;
        // DEC_hl;
        // RET_NZ;
        if(--bc->stepDuration)
            return;
        // LD_HL(wPlayerStepFlags);
        // SET_hl(PLAYERSTEP_STOP_F);
        bit_set(wram->wPlayerStepFlags, PLAYERSTEP_STOP_F);
        // CALL(aCopyNextCoordsTileToStandingCoordsTile);
        CopyNextCoordsTileToStandingCoordsTile_Conv(bc);
        // LD_HL(OBJECT_DIRECTION_WALKING);
        // ADD_HL_BC;
        // LD_hl(STANDING);
        bc->dirWalking = STANDING;
        // LD_HL(OBJECT_STEP_TYPE);
        // ADD_HL_BC;
        // LD_hl(STEP_TYPE_FROM_MOVEMENT);
        bc->stepType = STEP_TYPE_FROM_MOVEMENT;
        // RET;
        return;
    }
}

void StepFunction_Turn(void) {
    SET_PC(aStepFunction_Turn);
    LD_HL(OBJECT_1C);
    ADD_HL_BC;
    LD_A_hl;
    if (REG_A == 0) goto init1;
    if (REG_A == 1) goto step1;
    if (REG_A == 2) goto init2;
    if (REG_A == 3) goto step2;

init1:

    LD_HL(OBJECT_DIRECTION_WALKING);
    ADD_HL_BC;
    LD_hl(STANDING);
    LD_HL(OBJECT_STEP_FRAME);
    ADD_HL_BC;
    LD_A_hl;
    LD_hl(2);
    LD_HL(OBJECT_STEP_DURATION);
    ADD_HL_BC;
    LD_hl(2);
    CALL(aField1c_IncAnonJumptableIndex);

step1:

    LD_HL(OBJECT_STEP_DURATION);
    ADD_HL_BC;
    DEC_hl;
    RET_NZ;
    CALL(aField1c_IncAnonJumptableIndex);

init2:

    LD_HL(OBJECT_1D);  // new facing
    ADD_HL_BC;
    LD_A_hl;
    LD_HL(OBJECT_FACING);
    ADD_HL_BC;
    LD_hl_A;
    LD_HL(OBJECT_STEP_DURATION);
    ADD_HL_BC;
    LD_hl(2);
    CALL(aField1c_IncAnonJumptableIndex);

step2:

    LD_HL(OBJECT_STEP_DURATION);
    ADD_HL_BC;
    DEC_hl;
    RET_NZ;
    LD_HL(OBJECT_STEP_TYPE);
    ADD_HL_BC;
    LD_hl(STEP_TYPE_FROM_MOVEMENT);
    RET;
}

void StepFunction_Turn_Conv(struct Object* bc) {
    // SET_PC(aStepFunction_Turn);
    // LD_HL(OBJECT_1C);
    // ADD_HL_BC;
    // LD_A_hl;
    switch(bc->field_1C) {
    case 0:
    // init1:
        // LD_HL(OBJECT_DIRECTION_WALKING);
        // ADD_HL_BC;
        // LD_hl(STANDING);
        bc->dirWalking = STANDING;
        // LD_HL(OBJECT_STEP_FRAME);
        // ADD_HL_BC;
        // LD_A_hl;
        // LD_hl(2);
        bc->stepFrame = 2;
        // LD_HL(OBJECT_STEP_DURATION);
        // ADD_HL_BC;
        // LD_hl(2);
        bc->stepDuration = 2;
        // CALL(aField1c_IncAnonJumptableIndex);
        Field1c_IncAnonJumptableIndex(bc);
        // fallthrough
    case 1:
    // step1:
        // LD_HL(OBJECT_STEP_DURATION);
        // ADD_HL_BC;
        // DEC_hl;
        // RET_NZ;
        if(--bc->stepDuration)
            return;
        // CALL(aField1c_IncAnonJumptableIndex);
        Field1c_IncAnonJumptableIndex(bc);
        // fallthrough
    case 2:
    // init2:
        // LD_HL(OBJECT_1D);  // new facing
        // ADD_HL_BC;
        // LD_A_hl;
        // LD_HL(OBJECT_FACING);
        // ADD_HL_BC;
        // LD_hl_A;
        bc->facing = bc->field_1D;
        // LD_HL(OBJECT_STEP_DURATION);
        // ADD_HL_BC;
        // LD_hl(2);
        bc->stepDuration = 2;
        // CALL(aField1c_IncAnonJumptableIndex);
        Field1c_IncAnonJumptableIndex(bc);
        // fallthrough
    case 3:
    // step2:
        // LD_HL(OBJECT_STEP_DURATION);
        // ADD_HL_BC;
        // DEC_hl;
        // RET_NZ;
        if(--bc->stepDuration)
            return;
        // LD_HL(OBJECT_STEP_TYPE);
        // ADD_HL_BC;
        // LD_hl(STEP_TYPE_FROM_MOVEMENT);
        bc->stepType = STEP_TYPE_FROM_MOVEMENT;
        // RET;
        return;
    }
}

void StepFunction_StrengthBoulder(void) {
    SET_PC(aStepFunction_StrengthBoulder);
    CALL(aAddStepVector);
    LD_HL(OBJECT_STEP_DURATION);
    ADD_HL_BC;
    DEC_hl;
    RET_NZ;
    PUSH_BC;
    LD_HL(OBJECT_NEXT_MAP_X);
    ADD_HL_BC;
    LD_D_hl;
    LD_HL(OBJECT_NEXT_MAP_Y);
    ADD_HL_BC;
    LD_E_hl;
    LD_HL(OBJECT_MAP_OBJECT_INDEX);
    ADD_HL_BC;
    LD_A_hl;
    LD_B_A;
    FARCALL(aCopyDECoordsToMapObject);
    POP_BC;
    LD_HL(OBJECT_FLAGS2);
    ADD_HL_BC;
    RES_hl(OBJ_FLAGS2_2);
    CALL(aCopyNextCoordsTileToStandingCoordsTile);
    LD_HL(OBJECT_DIRECTION_WALKING);
    ADD_HL_BC;
    LD_hl(STANDING);
    LD_HL(OBJECT_STEP_TYPE);
    ADD_HL_BC;
    LD_hl(STEP_TYPE_FROM_MOVEMENT);
    RET;
}

void StepFunction_StrengthBoulder_Conv(struct Object* bc) {
    // SET_PC(aStepFunction_StrengthBoulder);
    // CALL(aAddStepVector);
    AddStepVector_Conv(bc);
    // LD_HL(OBJECT_STEP_DURATION);
    // ADD_HL_BC;
    // DEC_hl;
    // RET_NZ;
    if(--bc->stepDuration)
        return;
    // PUSH_BC;
    // LD_HL(OBJECT_NEXT_MAP_X);
    // ADD_HL_BC;
    // LD_D_hl;
    // LD_HL(OBJECT_NEXT_MAP_Y);
    // ADD_HL_BC;
    // LD_E_hl;
    // LD_HL(OBJECT_MAP_OBJECT_INDEX);
    // ADD_HL_BC;
    // LD_A_hl;
    // LD_B_A;
    // FARCALL(aCopyDECoordsToMapObject);
    CopyDECoordsToMapObject_Conv(bc->nextMapX, bc->nextMapY, bc->mapObjectIndex);
    // POP_BC;
    // LD_HL(OBJECT_FLAGS2);
    // ADD_HL_BC;
    // RES_hl(OBJ_FLAGS2_2);
    bit_reset(bc->flags2, OBJ_FLAGS2_2);
    // CALL(aCopyNextCoordsTileToStandingCoordsTile);
    CopyNextCoordsTileToStandingCoordsTile_Conv(bc);
    // LD_HL(OBJECT_DIRECTION_WALKING);
    // ADD_HL_BC;
    // LD_hl(STANDING);
    bc->dirWalking = STANDING;
    // LD_HL(OBJECT_STEP_TYPE);
    // ADD_HL_BC;
    // LD_hl(STEP_TYPE_FROM_MOVEMENT);
    bc->stepType = STEP_TYPE_FROM_MOVEMENT;
    // RET;
}

void StepFunction_TrackingObject(void) {
    SET_PC(aStepFunction_TrackingObject);
    LD_HL(OBJECT_1D);
    ADD_HL_BC;
    LD_E_hl;
    INC_HL;
    LD_D_hl;
    LD_HL(OBJECT_SPRITE);
    ADD_HL_DE;
    LD_A_hl;
    AND_A_A;
    IF_Z goto nope;
    LD_HL(OBJECT_SPRITE_X);
    ADD_HL_DE;
    LD_A_hl;
    LD_HL(OBJECT_SPRITE_X);
    ADD_HL_BC;
    LD_hl_A;
    LD_HL(OBJECT_SPRITE_Y);
    ADD_HL_DE;
    LD_A_hl;
    LD_HL(OBJECT_SPRITE_Y);
    ADD_HL_BC;
    LD_hl_A;
    LD_HL(OBJECT_STEP_DURATION);
    ADD_HL_BC;
    LD_A_hl;
    AND_A_A;
    RET_Z;
    DEC_hl;
    RET_NZ;

nope:

    JP(mDeleteMapObject);
}

void StepFunction_TrackingObject_Conv(struct Object* bc) {
    // SET_PC(aStepFunction_TrackingObject);
    // LD_HL(OBJECT_1D);
    // ADD_HL_BC;
    // LD_E_hl;
    // INC_HL;
    // LD_D_hl;
    struct Object* de = &wram->wPlayerStruct + (bc->field_1D | (bc->field_1E << 8));
    // LD_HL(OBJECT_SPRITE);
    // ADD_HL_DE;
    // LD_A_hl;
    // AND_A_A;
    // IF_Z goto nope;
    if(de->sprite != 0) {
        // LD_HL(OBJECT_SPRITE_X);
        // ADD_HL_DE;
        // LD_A_hl;
        // LD_HL(OBJECT_SPRITE_X);
        // ADD_HL_BC;
        // LD_hl_A;
        bc->spriteX = de->spriteX;
        // LD_HL(OBJECT_SPRITE_Y);
        // ADD_HL_DE;
        // LD_A_hl;
        // LD_HL(OBJECT_SPRITE_Y);
        // ADD_HL_BC;
        // LD_hl_A;
        bc->spriteY = de->spriteY;
        // LD_HL(OBJECT_STEP_DURATION);
        // ADD_HL_BC;
        // LD_A_hl;
        // AND_A_A;
        // RET_Z;
        if(bc->stepDuration == 0)
            return;
        // DEC_hl;
        // RET_NZ;
        if(--bc->stepDuration != 0)
            return;
    }
// nope:
    // JP(mDeleteMapObject);
    return DeleteMapObject_Conv(bc);
}

void StepFunction_14(void) {
    SET_PC(aStepFunction_14);
    return StepFunction_ScreenShake();
}

// Duplicate of StepFunction_ScreenShake
void StepFunction_14_Conv(struct Object* bc) {
    // SET_PC(aStepFunction_14);
    return StepFunction_ScreenShake_Conv(bc);
}

void StepFunction_ScreenShake(void) {
    SET_PC(aStepFunction_ScreenShake);
    LD_HL(OBJECT_1C);
    ADD_HL_BC;
    LD_A_hl;
    if (REG_A == 0) goto Init;
    if (REG_A == 1) goto Run;

Init:

    XOR_A_A;
    LD_HL(OBJECT_1D);
    ADD_HL_BC;
    LD_hl_A;
    CALL(aField1c_IncAnonJumptableIndex);

Run:

    LD_HL(OBJECT_1D);
    ADD_HL_BC;
    LD_D_hl;
    LD_A_addr(wPlayerStepVectorY);
    SUB_A_D;
    LD_addr_A(wPlayerStepVectorY);
    LD_HL(OBJECT_STEP_DURATION);
    ADD_HL_BC;
    DEC_hl;
    IF_Z goto ok;
    LD_A_hl;
    CALL(aStepFunction_ScreenShake_GetSign);
    LD_HL(OBJECT_1D);
    ADD_HL_BC;
    LD_hl_A;
    LD_D_A;
    LD_A_addr(wPlayerStepVectorY);
    ADD_A_D;
    LD_addr_A(wPlayerStepVectorY);
    RET;

ok:

    CALL(aDeleteMapObject);
    RET;

GetSign:

    LD_HL(OBJECT_1E);
    ADD_HL_BC;
    AND_A(1);
    LD_A_hl;
    RET_Z;
    CPL;
    INC_A;
    RET;
}

static uint8_t StepFunction_ScreenShake_GetSign(const struct Object* bc, uint8_t a) {
    // LD_HL(OBJECT_1E);
    // ADD_HL_BC;
    // AND_A(1);
    // LD_A_hl;
    // RET_Z;
    if((a & 1) == 0)
        return bc->field_1E;
    // CPL;
    // INC_A;
    // RET;
    return (bc->field_1E ^ 0xff) + 1;
}

void StepFunction_ScreenShake_Conv(struct Object* bc) {
    // SET_PC(aStepFunction_ScreenShake);
    // LD_HL(OBJECT_1C);
    // ADD_HL_BC;
    // LD_A_hl;
    switch(bc->field_1C) {
    case 0:
    // Init:
        // XOR_A_A;
        // LD_HL(OBJECT_1D);
        // ADD_HL_BC;
        // LD_hl_A;
        bc->field_1D = 0;
        // CALL(aField1c_IncAnonJumptableIndex);
        Field1c_IncAnonJumptableIndex(bc);
        // fallthrough
    case 1:
    // Run:
        // LD_HL(OBJECT_1D);
        // ADD_HL_BC;
        // LD_D_hl;
        // LD_A_addr(wPlayerStepVectorY);
        // SUB_A_D;
        // LD_addr_A(wPlayerStepVectorY);
        wram->wPlayerStepVectorY -= bc->field_1D;
        // LD_HL(OBJECT_STEP_DURATION);
        // ADD_HL_BC;
        // DEC_hl;
        // IF_Z goto ok;
        if(--bc->stepDuration) {
            // LD_A_hl;
            // CALL(aStepFunction_ScreenShake_GetSign);
            uint8_t a = StepFunction_ScreenShake_GetSign(bc, bc->stepDuration);
            // LD_HL(OBJECT_1D);
            // ADD_HL_BC;
            // LD_hl_A;
            bc->field_1D = a;
            // LD_D_A;
            // LD_A_addr(wPlayerStepVectorY);
            // ADD_A_D;
            // LD_addr_A(wPlayerStepVectorY);
            wram->wPlayerStepVectorY += a;
            // RET;
            return;
        }
    // ok:
        // CALL(aDeleteMapObject);
        DeleteMapObject_Conv(bc);
        // RET;
        return;
    }
}

void StepFunction_16(void) {
    SET_PC(aStepFunction_16);
    LD_HL(OBJECT_1C);
    ADD_HL_BC;
    LD_A_hl;
    return StepFunction_17();
}

void StepFunction_17(void) {
    SET_PC(aStepFunction_17);
    LD_HL(OBJECT_1C);
    ADD_HL_BC;
    LD_A_hl;
    if (REG_A == 0) goto null;
    if (REG_A == 1) goto null;
    if (REG_A == 2) goto null;

null:

    return StepFunction_SkyfallTop();
}

void StepFunction_SkyfallTop(void) {
    SET_PC(aStepFunction_SkyfallTop);
    LD_HL(OBJECT_1C);
    ADD_HL_BC;
    LD_A_hl;
    if (REG_A == 0) goto Init;
    if (REG_A == 1) goto Run;

Init:

    LD_HL(OBJECT_ACTION);
    ADD_HL_BC;
    LD_hl(OBJECT_ACTION_SKYFALL);
    LD_HL(OBJECT_STEP_DURATION);
    ADD_HL_BC;
    LD_hl(16);
    CALL(aField1c_IncAnonJumptableIndex);

Run:

    LD_HL(OBJECT_STEP_DURATION);
    ADD_HL_BC;
    DEC_hl;
    RET_NZ;
    LD_HL(OBJECT_SPRITE_Y_OFFSET);
    ADD_HL_BC;
    LD_hl(0x60);
    LD_HL(OBJECT_STEP_FRAME);
    ADD_HL_BC;
    LD_hl(0);
    LD_HL(OBJECT_STEP_TYPE);
    ADD_HL_BC;
    LD_hl(STEP_TYPE_FROM_MOVEMENT);
    RET;
}

void StepFunction_SkyfallTop_Conv(struct Object* bc) {
    // SET_PC(aStepFunction_SkyfallTop);
    // LD_HL(OBJECT_1C);
    // ADD_HL_BC;
    // LD_A_hl;
    switch(bc->field_1C) {
    case 0:
    // Init:
        // LD_HL(OBJECT_ACTION);
        // ADD_HL_BC;
        // LD_hl(OBJECT_ACTION_SKYFALL);
        bc->action = OBJECT_ACTION_SKYFALL;
        // LD_HL(OBJECT_STEP_DURATION);
        // ADD_HL_BC;
        // LD_hl(16);
        bc->stepDuration = 16;
        // CALL(aField1c_IncAnonJumptableIndex);
        Field1c_IncAnonJumptableIndex(bc);
        // fallthrough
    case 1:
    // Run:
        // LD_HL(OBJECT_STEP_DURATION);
        // ADD_HL_BC;
        // DEC_hl;
        // RET_NZ;
        if(--bc->stepDuration)
            return;
        // LD_HL(OBJECT_SPRITE_Y_OFFSET);
        // ADD_HL_BC;
        // LD_hl(0x60);
        bc->spriteYOffset = 0x60;
        // LD_HL(OBJECT_STEP_FRAME);
        // ADD_HL_BC;
        // LD_hl(0);
        bc->stepFrame = 0;
        // LD_HL(OBJECT_STEP_TYPE);
        // ADD_HL_BC;
        // LD_hl(STEP_TYPE_FROM_MOVEMENT);
        bc->stepType = STEP_TYPE_FROM_MOVEMENT;
        // RET;
        return;
    }
}

void Stubbed_UpdateYOffset(void) {
    SET_PC(aStubbed_UpdateYOffset);
    //  dummied out
    RET;
    LD_HL(OBJECT_1D);
    ADD_HL_BC;
    INC_hl;
    LD_A_hl;
    SRL_A;
    SRL_A;
    AND_A(0b00000111);
    LD_L_A;
    LD_H(0);
    LD_DE(mStubbed_UpdateYOffset_y_offsets);
    ADD_HL_DE;
    LD_A_hl;
    LD_HL(OBJECT_SPRITE_Y_OFFSET);
    ADD_HL_BC;
    LD_hl_A;
    RET;

//y_offsets:

    // db ['0', '-1', '-2', '-3', '-4', '-3', '-2', '-1'];
}

void UpdateJumpPosition(void) {
    SET_PC(aUpdateJumpPosition);
    CALL(aGetStepVector);
    LD_A_H;
    LD_HL(OBJECT_1F);
    ADD_HL_BC;
    LD_E_hl;
    ADD_A_E;
    LD_hl_A;
    NOP;
    SRL_E;
    LD_D(0);
    LD_HL(mUpdateJumpPosition_y_offsets);
    ADD_HL_DE;
    LD_A_hl;
    LD_HL(OBJECT_SPRITE_Y_OFFSET);
    ADD_HL_BC;
    LD_hl_A;
    RET;

//y_offsets:

    // db ['-4', '-6', '-8', '-10', '-11', '-12', '-12', '-12'];
    // db ['-11', '-10', '-9', '-8', '-6', '-4', '0', '0'];
}

void UpdateJumpPosition_Conv(struct Object* bc) {
    static const int8_t y_offsets[] = {
        -4, -6, -8, -10, -11, -12, -12, -12,
        -11, -10, -9, -8, -6, -4, 0, 0,
    };
    // SET_PC(aUpdateJumpPosition);
    // CALL(aGetStepVector);
    struct StepVector vec = GetStepVector_Conv(bc);
    // LD_A_H;
    // LD_HL(OBJECT_1F);
    // ADD_HL_BC;
    // LD_E_hl;
    uint8_t e = bc->field_1F;
    // ADD_A_E;
    // LD_hl_A;
    bc->field_1F += vec.speed;
    // NOP;
    // SRL_E;
    // LD_D(0);
    // LD_HL(mUpdateJumpPosition_y_offsets);
    // ADD_HL_DE;
    // LD_A_hl;
    // LD_HL(OBJECT_SPRITE_Y_OFFSET);
    // ADD_HL_BC;
    // LD_hl_A;
    bc->spriteYOffset = y_offsets[e >> 1];
    // RET;
}

void GetPlayerNextMovementByte(void) {
    SET_PC(aGetPlayerNextMovementByte);
    //  copy [wPlayerNextMovement] to [wPlayerMovement]
    LD_A_addr(wPlayerNextMovement);
    LD_HL(wPlayerMovement);
    LD_hl_A;
    //  load [wPlayerNextMovement] with movement_step_sleep
    LD_A(movement_step_sleep);
    LD_addr_A(wPlayerNextMovement);
    //  recover the previous value of [wPlayerNextMovement]
    LD_A_hl;
    RET;
}

uint8_t GetPlayerNextMovementByte_Conv(struct Object* bc) {
    (void)bc;
    // SET_PC(aGetPlayerNextMovementByte);
    //  copy [wPlayerNextMovement] to [wPlayerMovement]
    // LD_A_addr(wPlayerNextMovement);
    // LD_HL(wPlayerMovement);
    // LD_hl_A;
    wram->wPlayerMovement = wram->wPlayerNextMovement;
    //  load [wPlayerNextMovement] with movement_step_sleep
    // LD_A(movement_step_sleep);
    // LD_addr_A(wPlayerNextMovement);
    wram->wPlayerNextMovement = movement_step_sleep;
    //  recover the previous value of [wPlayerNextMovement]
    // LD_A_hl;
    // RET;
    return wram->wPlayerMovement;
}

void GetMovementByte(void) {
    SET_PC(aGetMovementByte);
    LD_HL(wMovementDataBank);
    CALL(av_GetMovementByte);
    RET;
}

uint8_t GetMovementByte_Conv(struct Object* bc) {
    // SET_PC(aGetMovementByte);
    // LD_HL(wMovementDataBank);
    // CALL(av_GetMovementByte);
    // RET;
    return v_GetMovementByte_Conv(gMovementDataAddr, bc);
}

void GetIndexedMovementByte1(void) {
    SET_PC(aGetIndexedMovementByte1);
    LD_HL(OBJECT_MOVEMENT_BYTE_INDEX);
    ADD_HL_BC;
    LD_E_hl;
    INC_hl;
    LD_D(0);
    LD_HL(wMovementObject);
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    ADD_HL_DE;
    LD_A_hl;
    RET;
}

uint8_t GetIndexedMovementByte1_Conv(struct Object* bc) {
    // SET_PC(aGetIndexedMovementByte1);
    // LD_HL(OBJECT_MOVEMENT_BYTE_INDEX);
    // ADD_HL_BC;
    // LD_E_hl;
    // INC_hl;
    uint8_t e = bc->movementByteIndex++;
    // LD_D(0);
    // LD_HL(wMovementObject);
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // ADD_HL_DE;
    // LD_A_hl;
    // RET;
    return gMovementDataAddr[e];
}

void GetIndexedMovementByte2(void) {
    SET_PC(aGetIndexedMovementByte2);
    LD_HL(OBJECT_MOVEMENT_BYTE_INDEX);
    ADD_HL_BC;
    LD_E_hl;
    INC_hl;
    LD_D(0);
    LD_HL(wIndexedMovement2Pointer);
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    ADD_HL_DE;
    LD_A_hl;
    RET;
}

uint8_t GetIndexedMovementByte2_Conv(struct Object* bc) {
    // SET_PC(aGetIndexedMovementByte2);
    // LD_HL(OBJECT_MOVEMENT_BYTE_INDEX);
    // ADD_HL_BC;
    // LD_E_hl;
    // INC_hl;
    // LD_D(0);
    // LD_HL(wIndexedMovement2Pointer);
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // ADD_HL_DE;
    // LD_A_hl;
    // RET;
    return gIndexedMovement2Pointer[bc->movementByteIndex++];
}

void v_GetMovementObject(void) {
    SET_PC(av_GetMovementObject);
    LD_HL(mGetMovementObject);
    JP(mHandleMovementData);
}

void v_GetMovementObject_Conv(struct Object* bc) {
    // SET_PC(av_GetMovementObject);
    // LD_HL(mGetMovementObject);
    // JP(mHandleMovementData);
    HandleMovementData_Conv(bc, GetMovementObject);
}

uint8_t GetMovementObject(struct Object* bc) {
    (void)bc;
    // SET_PC(aGetMovementObject);
    // LD_A_addr(wMovementObject);
    // RET;
    return wram->wMovementObject;
}

void HandleMovementData(void) {
    SET_PC(aHandleMovementData);
    CALL(aHandleMovementData_StorePointer);

loop:

    XOR_A_A;
    LD_addr_A(wMovementByteWasControlSwitch);
    CALL(aJumpMovementPointer);
    CALL(aDoMovementFunction);
    LD_A_addr(wMovementByteWasControlSwitch);
    AND_A_A;
    IF_NZ goto loop;
    RET;

StorePointer:

    LD_A_L;
    LD_addr_A(wMovementPointer);
    LD_A_H;
    LD_addr_A(wMovementPointer + 1);
    RET;
}

void HandleMovementData_Conv(struct Object* bc, uint8_t (*hl)(struct Object*)) {
    // SET_PC(aHandleMovementData);
    // CALL(aHandleMovementData_StorePointer);
    // StorePointer:
    // LD_A_L;
    // LD_addr_A(wMovementPointer);
    // LD_A_H;
    // LD_addr_A(wMovementPointer + 1);
    gMovementPointer = hl;
    // RET;
    do {
    // loop:

        // XOR_A_A;
        // LD_addr_A(wMovementByteWasControlSwitch);
        wram->wMovementByteWasControlSwitch = 0;
        // CALL(aJumpMovementPointer);
        uint8_t a = JumpMovementPointer_Conv(bc);
        // CALL(aDoMovementFunction);
        DoMovementFunction_Conv(bc, a);
        // LD_A_addr(wMovementByteWasControlSwitch);
        // AND_A_A;
        // IF_NZ goto loop;
    } while(wram->wMovementByteWasControlSwitch != 0);
    // RET;
}

void JumpMovementPointer(void) {
    SET_PC(aJumpMovementPointer);
    // LD_HL(wMovementPointer);
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // JP_hl;
    RET;
}

uint8_t JumpMovementPointer_Conv(struct Object* bc) {
    return gMovementPointer(bc);
}

void ContinueReadingMovement(void) {
    // SET_PC(aContinueReadingMovement);
    // LD_A(1);
    // LD_addr_A(wMovementByteWasControlSwitch);
    wram->wMovementByteWasControlSwitch = 1;
    // RET;
}

void DoMovementFunction(void) {
    SET_PC(aDoMovementFunction);
    PUSH_AF;
    CALL(aApplyMovementToFollower);
    POP_AF;
    LD_HL(mMovementPointers);
    RST(aJumpTable);
    RET;

    // INCLUDE "engine/overworld/movement.asm"

    return ApplyMovementToFollower();
}

void DoMovementFunction_Conv(struct Object* bc, uint8_t a) {
    // SET_PC(aDoMovementFunction);
    // PUSH_AF;
    // CALL(aApplyMovementToFollower);
    ApplyMovementToFollower_Conv(a);
    // POP_AF;
    // LD_HL(mMovementPointers);
    // RST(aJumpTable);
    // RET;
    return MovementPointers[a](bc);
}

void ApplyMovementToFollower(void) {
    SET_PC(aApplyMovementToFollower);
    LD_E_A;
    LD_A_addr(wObjectFollow_Follower);
    CP_A(-1);
    RET_Z;
    LD_A_addr(wObjectFollow_Leader);
    LD_D_A;
    LDH_A_addr(hMapObjectIndex);
    CP_A_D;
    RET_NZ;
    LD_A_E;
    CP_A(movement_step_sleep);
    RET_Z;
    CP_A(movement_step_end);
    RET_Z;
    CP_A(movement_step_4b);
    RET_Z;
    CP_A(movement_step_bump);
    RET_Z;
    CP_A(movement_slow_step);
    RET_C;
    PUSH_AF;
    LD_HL(wFollowerMovementQueueLength);
    INC_hl;
    LD_E_hl;
    LD_D(0);
    LD_HL(wFollowMovementQueue);
    ADD_HL_DE;
    POP_AF;
    LD_hl_A;
    RET;
}

void ApplyMovementToFollower_Conv(uint8_t a) {
    // SET_PC(aApplyMovementToFollower);
    // LD_E_A;
    // LD_A_addr(wObjectFollow_Follower);
    // CP_A(-1);
    // RET_Z;
    if(wram->wObjectFollow_Follower == 0xff)
        return;
    // LD_A_addr(wObjectFollow_Leader);
    // LD_D_A;
    // LDH_A_addr(hMapObjectIndex);
    // CP_A_D;
    // RET_NZ;
    if(hram->hMapObjectIndex != wram->wObjectFollow_Leader)
        return;
    // LD_A_E;
    // CP_A(movement_step_sleep);
    // RET_Z;
    // CP_A(movement_step_end);
    // RET_Z;
    // CP_A(movement_step_4b);
    // RET_Z;
    // CP_A(movement_step_bump);
    // RET_Z;
    // CP_A(movement_slow_step);
    // RET_C;
    if(a == movement_step_sleep || a == movement_step_end || a == movement_step_4b || a == movement_step_bump || a < movement_slow_step)
        return;
    // PUSH_AF;
    // LD_HL(wFollowerMovementQueueLength);
    // INC_hl;
    // LD_E_hl;
    // LD_D(0);
    uint16_t de = ++wram->wFollowerMovementQueueLength;
    // LD_HL(wFollowMovementQueue);
    // ADD_HL_DE;
    // POP_AF;
    // LD_hl_A;
    wram->wFollowMovementQueue[de] = a;
    // RET;
}

void GetFollowerNextMovementByte(void) {
    SET_PC(aGetFollowerNextMovementByte);
    LD_HL(wFollowerMovementQueueLength);
    LD_A_hl;
    AND_A_A;
    IF_Z goto done;
    CP_A(-1);
    IF_Z goto done;
    DEC_hl;
    LD_E_A;
    LD_D(0);
    LD_HL(wFollowMovementQueue);
    ADD_HL_DE;
    INC_E;
    LD_A(-1);

loop:

    LD_D_hl;
    LD_hld_A;
    LD_A_D;
    DEC_E;
    IF_NZ goto loop;
    RET;

done:

    CALL(aGetFollowerNextMovementByte_CancelFollowIfLeaderMissing);
    RET_C;
    LD_A(movement_step_sleep);
    RET;

CancelFollowIfLeaderMissing:

    LD_A_addr(wObjectFollow_Leader);
    CP_A(-1);
    IF_Z goto nope;
    PUSH_BC;
    CALL(aGetObjectStruct);
    LD_HL(OBJECT_SPRITE);
    ADD_HL_BC;
    LD_A_hl;
    POP_BC;
    AND_A_A;
    IF_Z goto nope;
    AND_A_A;
    RET;

nope:

    LD_A(-1);
    LD_addr_A(wObjectFollow_Follower);
    LD_A(movement_step_end);
    SCF;
    RET;
}

static u8_flag_s GetFollowerNextMovementByte_CancelFollowIfLeaderMissing(void) {
    // LD_A_addr(wObjectFollow_Leader);
    // CP_A(-1);
    // IF_Z goto nope;
    if(wram->wObjectFollow_Leader != 0xff) {
        // PUSH_BC;
        // CALL(aGetObjectStruct);
        struct Object* bc = GetObjectStruct_Conv(wram->wObjectFollow_Leader);
        // LD_HL(OBJECT_SPRITE);
        // ADD_HL_BC;
        // LD_A_hl;
        // POP_BC;
        // AND_A_A;
        // IF_Z goto nope;
        if(bc->sprite != 0xff) {
            // AND_A_A;
            // RET;
            return u8_flag(bc->sprite, false);
        }
    }

// nope:
    // LD_A(-1);
    // LD_addr_A(wObjectFollow_Follower);
    wram->wObjectFollow_Follower = 0xff;
    // LD_A(movement_step_end);
    // SCF;
    // RET;
    return u8_flag(movement_step_end, true);
}

uint8_t GetFollowerNextMovementByte_Conv(struct Object* bc) {
    (void)bc;
    // SET_PC(aGetFollowerNextMovementByte);
    // LD_HL(wFollowerMovementQueueLength);
    // LD_A_hl;
    // AND_A_A;
    // IF_Z goto done;
    // CP_A(-1);
    // IF_Z goto done;
    if(wram->wFollowerMovementQueueLength == 0
    || wram->wFollowerMovementQueueLength == 0xff) {
    // done:
        // CALL(aGetFollowerNextMovementByte_CancelFollowIfLeaderMissing);
        u8_flag_s res = GetFollowerNextMovementByte_CancelFollowIfLeaderMissing();
        // RET_C;
        if(res.flag)
            return res.a;
        // LD_A(movement_step_sleep);
        // RET;
        return movement_step_sleep;
    }
    // DEC_hl;
    // LD_E_A;
    uint8_t e = wram->wFollowerMovementQueueLength--;
    // LD_D(0);
    // LD_HL(wFollowMovementQueue);
    // ADD_HL_DE;
    // INC_E;
    e++;
    // LD_A(-1);

    uint8_t d;
    uint8_t a = 0xff;
    do {
    // loop:
        // LD_D_hl;
        d = wram->wFollowMovementQueue[e-1];
        // LD_hld_A;
        wram->wFollowMovementQueue[e-1] = a;
        // LD_A_D;
        a = d;
        // DEC_E;
        // IF_NZ goto loop;
    } while(--e != 0);
    // RET;
    return d;
}

void SpawnShadow(void) {
    SET_PC(aSpawnShadow);
    PUSH_BC;
    LD_DE(mSpawnShadow_ShadowObject);
    CALL(aCopyTempObjectData);
    CALL(aInitTempObject);
    POP_BC;
    RET;

//ShadowObject:

    // vtile, palette, movement
    // db ['0x00', 'PAL_OW_SILVER', 'SPRITEMOVEDATA_SHADOW'];
}

void SpawnShadow_Conv(struct Object* bc) {
    static const uint8_t ShadowObject[] = {
        0x00, PAL_OW_SILVER, SPRITEMOVEDATA_SHADOW,
    };
    // SET_PC(aSpawnShadow);
    // PUSH_BC;
    // LD_DE(mSpawnShadow_ShadowObject);
    // CALL(aCopyTempObjectData);
    CopyTempObjectData_Conv(bc, ShadowObject);
    // CALL(aInitTempObject);
    InitTempObject_Conv();
    // POP_BC;
    // RET;

// ShadowObject:

    // vtile, palette, movement
    // db ['0x00', 'PAL_OW_SILVER', 'SPRITEMOVEDATA_SHADOW'];
    // return SpawnStrengthBoulderDust();
}

void SpawnStrengthBoulderDust(void) {
    SET_PC(aSpawnStrengthBoulderDust);
    PUSH_BC;
    LD_DE(mSpawnStrengthBoulderDust_BoulderDustObject);
    CALL(aCopyTempObjectData);
    CALL(aInitTempObject);
    POP_BC;
    RET;

BoulderDustObject:

    // vtile, palette, movement
    // db ['0x00', 'PAL_OW_SILVER', 'SPRITEMOVEDATA_BOULDERDUST'];

    return SpawnEmote();
}

void SpawnStrengthBoulderDust_Conv(struct Object* bc) {
    static const uint8_t BoulderDustObject[] = {
    // vtile, palette, movement
        0x00, PAL_OW_SILVER, SPRITEMOVEDATA_BOULDERDUST
    };
    // SET_PC(aSpawnStrengthBoulderDust);
    // PUSH_BC;
    // LD_DE(mSpawnStrengthBoulderDust_BoulderDustObject);
    // CALL(aCopyTempObjectData);
    CopyTempObjectData_Conv(bc, BoulderDustObject);
    // CALL(aInitTempObject);
    InitTempObject_Conv();
    // POP_BC;
    // RET;
}

void SpawnEmote(void) {
    SET_PC(aSpawnEmote);
    PUSH_BC;
    LD_DE(mSpawnEmote_EmoteObject);
    CALL(aCopyTempObjectData);
    CALL(aInitTempObject);
    POP_BC;
    RET;

EmoteObject:

    // vtile, palette, movement
    // db ['0x00', 'PAL_OW_SILVER', 'SPRITEMOVEDATA_EMOTE'];

    return ShakeGrass();
}

void SpawnEmote_Conv(struct Object* bc) {
    static const uint8_t EmoteObject[] = {
        0x00, PAL_OW_SILVER, SPRITEMOVEDATA_EMOTE,
    };
    // SET_PC(aSpawnEmote);
    // PUSH_BC;
    // LD_DE(mSpawnEmote_EmoteObject);
    // CALL(aCopyTempObjectData);
    CopyTempObjectData_Conv(bc, EmoteObject);
    // CALL(aInitTempObject);
    InitTempObject_Conv();
    // POP_BC;
    // RET;

// EmoteObject:

    // vtile, palette, movement
    // db ['0x00', 'PAL_OW_SILVER', 'SPRITEMOVEDATA_EMOTE'];

    // return ShakeGrass();
}

void ShakeGrass(void) {
    SET_PC(aShakeGrass);
    PUSH_BC;
    LD_DE(mShakeGrass_GrassObject);
    CALL(aCopyTempObjectData);
    CALL(aInitTempObject);
    POP_BC;
    RET;

GrassObject:

    // vtile, palette, movement
    // db ['0x00', 'PAL_OW_TREE', 'SPRITEMOVEDATA_GRASS'];

    return ShakeScreen();
}

void ShakeGrass_Conv(struct Object* bc) {
    static const uint8_t GrassObject[] = {
        0x00, PAL_OW_TREE, SPRITEMOVEDATA_GRASS,
    };
    // SET_PC(aShakeGrass);
    // PUSH_BC;
    // LD_DE(mShakeGrass_GrassObject);
    // CALL(aCopyTempObjectData);
    CopyTempObjectData_Conv(bc, GrassObject);
    // CALL(aInitTempObject);
    InitTempObject_Conv();
    // POP_BC;
    // RET;

// GrassObject:

    // vtile, palette, movement
    // db ['0x00', 'PAL_OW_TREE', 'SPRITEMOVEDATA_GRASS'];

    // return ShakeScreen();
}

void ShakeScreen(void) {
    SET_PC(aShakeScreen);
    PUSH_BC;
    PUSH_AF;
    LD_DE(mShakeScreen_ScreenShakeObject);
    CALL(aCopyTempObjectData);
    POP_AF;
    LD_addr_A(wTempObjectCopyRange);
    CALL(aInitTempObject);
    POP_BC;
    RET;

ScreenShakeObject:

    // vtile, palette, movement
    // db ['0x00', 'PAL_OW_SILVER', 'SPRITEMOVEDATA_SCREENSHAKE'];

    return DespawnEmote();
}

void ShakeScreen_Conv(struct Object* bc, uint8_t a) {
    static const uint8_t ScreenShakeObject[] = {
        0x00, PAL_OW_SILVER, SPRITEMOVEDATA_SCREENSHAKE,
    };
    // SET_PC(aShakeScreen);
    // PUSH_BC;
    // PUSH_AF;
    // LD_DE(mShakeScreen_ScreenShakeObject);
    // CALL(aCopyTempObjectData);
    CopyTempObjectData_Conv(bc, ScreenShakeObject);
    // POP_AF;
    // LD_addr_A(wTempObjectCopyRange);
    wram->wTempObjectCopyRange = a;
    // CALL(aInitTempObject);
    InitTempObject_Conv();
    // POP_BC;
    // RET;

// ScreenShakeObject:

    // vtile, palette, movement
    // db ['0x00', 'PAL_OW_SILVER', 'SPRITEMOVEDATA_SCREENSHAKE'];
    // return DespawnEmote();
}

void DespawnEmote(void) {
    SET_PC(aDespawnEmote);
    PUSH_BC;
    LDH_A_addr(hMapObjectIndex);
    LD_C_A;
    CALL(aDespawnEmote_DeleteEmote);
    POP_BC;
    RET;

DeleteEmote:

    LD_DE(wObjectStructs);
    LD_A(NUM_OBJECT_STRUCTS);

loop:

    PUSH_AF;
    LD_HL(OBJECT_FLAGS1);
    ADD_HL_DE;
    BIT_hl(EMOTE_OBJECT_F);
    IF_Z goto next;
    LD_HL(OBJECT_SPRITE);
    ADD_HL_DE;
    LD_A_hl;
    AND_A_A;
    IF_Z goto next;
    PUSH_BC;
    XOR_A_A;
    LD_BC(OBJECT_LENGTH);
    CALL(aByteFill);
    POP_BC;

next:

    LD_HL(OBJECT_LENGTH);
    ADD_HL_DE;
    LD_D_H;
    LD_E_L;
    POP_AF;
    DEC_A;
    IF_NZ goto loop;
    RET;
}

void DespawnEmote_Conv(struct Object* bc) {
    (void)bc;
    // SET_PC(aDespawnEmote);
    // PUSH_BC;
    // LDH_A_addr(hMapObjectIndex);
    // LD_C_A;
    // CALL(aDespawnEmote_DeleteEmote);
    // POP_BC;
    // RET;

// DeleteEmote:

    // LD_DE(wObjectStructs);
    // LD_A(NUM_OBJECT_STRUCTS);
    for(size_t i = 0; i < NUM_OBJECT_STRUCTS; ++i) {
    // loop:
        struct Object* const de = (&wram->wPlayerStruct + i);
        // PUSH_AF;
        // LD_HL(OBJECT_FLAGS1);
        // ADD_HL_DE;
        // BIT_hl(EMOTE_OBJECT_F);
        // IF_Z goto next;
        if(!bit_test(de->flags1, EMOTE_OBJECT_F))
            continue;
        // LD_HL(OBJECT_SPRITE);
        // ADD_HL_DE;
        // LD_A_hl;
        // AND_A_A;
        // IF_Z goto next;
        if(de->sprite == 0)
            continue;
        // PUSH_BC;
        // XOR_A_A;
        // LD_BC(OBJECT_LENGTH);
        // CALL(aByteFill);
        // POP_BC;
        ByteFill_Conv2(de, sizeof(*de), 0);

    // next:
        // LD_HL(OBJECT_LENGTH);
        // ADD_HL_DE;
        // LD_D_H;
        // LD_E_L;
        // POP_AF;
        // DEC_A;
        // IF_NZ goto loop;
    }
    // RET;
}

void InitTempObject(void) {
    SET_PC(aInitTempObject);
    CALL(aFindFirstEmptyObjectStruct);
    RET_NC;
    LD_D_H;
    LD_E_L;
    FARCALL(aCopyTempObjectToObjectStruct);
    RET;
}

void InitTempObject_Conv(void) {
    // SET_PC(aInitTempObject);
    // CALL(aFindFirstEmptyObjectStruct);
    struct Object* de = FindFirstEmptyObjectStruct_Conv();
    // RET_NC;
    if(de == NULL)
        return;
    // LD_D_H;
    // LD_E_L;
    // FARCALL(aCopyTempObjectToObjectStruct);
    CopyTempObjectToObjectStruct_Conv(de);
    // RET;
}

void CopyTempObjectData(void) {
    SET_PC(aCopyTempObjectData);
    //  load into wTempObjectCopy:
    //  -1, -1, [de], [de + 1], [de + 2], [hMapObjectIndex], [NextMapX], [NextMapY], -1
    //  This spawns the object at the same place as whichever object is loaded into bc.
    LD_HL(wTempObjectCopyMapObjectIndex);
    LD_hl(-1);
    INC_HL;
    LD_hl(-1);
    INC_HL;
    LD_A_de;
    INC_DE;
    LD_hli_A;
    LD_A_de;
    INC_DE;
    LD_hli_A;
    LD_A_de;
    LD_hli_A;
    LDH_A_addr(hMapObjectIndex);
    LD_hli_A;
    PUSH_HL;
    LD_HL(OBJECT_NEXT_MAP_X);
    ADD_HL_BC;
    LD_D_hl;
    LD_HL(OBJECT_NEXT_MAP_Y);
    ADD_HL_BC;
    LD_E_hl;
    POP_HL;
    LD_hl_D;
    INC_HL;
    LD_hl_E;
    INC_HL;
    LD_hl(-1);
    RET;
}

void CopyTempObjectData_Conv(struct Object* bc, const uint8_t* de) {
    // SET_PC(aCopyTempObjectData);
    //  load into wTempObjectCopy:
    //  -1, -1, [de], [de + 1], [de + 2], [hMapObjectIndex], [NextMapX], [NextMapY], -1
    //  This spawns the object at the same place as whichever object is loaded into bc.
    // LD_HL(wTempObjectCopyMapObjectIndex);
    // LD_hl(-1);
    wram->wTempObjectCopyMapObjectIndex = 0xff;
    // INC_HL;
    // LD_hl(-1);
    wram->wTempObjectCopySprite = 0xff;
    // INC_HL;
    // LD_A_de;
    // INC_DE;
    // LD_hli_A;
    wram->wTempObjectCopySpriteVTile = de[0];
    // LD_A_de;
    // INC_DE;
    // LD_hli_A;
    wram->wTempObjectCopyPalette = de[1];
    // LD_A_de;
    // LD_hli_A;
    wram->wTempObjectCopyMovement = de[2];
    // LDH_A_addr(hMapObjectIndex);
    // LD_hli_A;
    wram->wTempObjectCopyRange = hram->hMapObjectIndex;
    // PUSH_HL;
    // LD_HL(OBJECT_NEXT_MAP_X);
    // ADD_HL_BC;
    // LD_D_hl;
    // LD_HL(OBJECT_NEXT_MAP_Y);
    // ADD_HL_BC;
    // LD_E_hl;
    // POP_HL;
    // LD_hl_D;
    wram->wTempObjectCopyX = bc->nextMapX;
    // INC_HL;
    // LD_hl_E;
    // INC_HL;
    wram->wTempObjectCopyY = bc->nextMapY;
    // LD_hl(-1);
    wram->wTempObjectCopyRadius = 0xff;
    // RET;
}

void UpdateAllObjectsFrozen(void) {
    SET_PC(aUpdateAllObjectsFrozen);
    LD_A_addr(wVramState);
    BIT_A(0);
    RET_Z;
    LD_BC(wObjectStructs);
    XOR_A_A;

loop:

    LDH_addr_A(hMapObjectIndex);
    CALL(aDoesObjectHaveASprite);
    IF_Z goto ok;
    CALL(aUpdateObjectFrozen);

ok:

    LD_HL(OBJECT_LENGTH);
    ADD_HL_BC;
    LD_B_H;
    LD_C_L;
    LDH_A_addr(hMapObjectIndex);
    INC_A;
    CP_A(NUM_OBJECT_STRUCTS);
    IF_NZ goto loop;
    RET;
}

void UpdateAllObjectsFrozen_Conv(void) {
    // SET_PC(aUpdateAllObjectsFrozen);
    // LD_A_addr(wVramState);
    // BIT_A(0);
    // RET_Z;
    if(!bit_test(wram->wVramState, 0))
        return;
    
    // LD_BC(wObjectStructs);
    // XOR_A_A;
    struct Object* bc = &wram->wPlayerStruct;

// loop:
    for(uint8_t a = 0; a < NUM_OBJECT_STRUCTS; ++a) {
        // LDH_addr_A(hMapObjectIndex);
        hram->hMapObjectIndex = a;
        // CALL(aDoesObjectHaveASprite);
        // IF_Z goto ok;
        if(DoesObjectHaveASprite_Conv(&bc[a])) {
            // CALL(aUpdateObjectFrozen);
            UpdateObjectFrozen_Conv(&bc[a]);
        }
    // ok:
        // LD_HL(OBJECT_LENGTH);
        // ADD_HL_BC;
        // LD_B_H;
        // LD_C_L;
        // LDH_A_addr(hMapObjectIndex);
        // INC_A;
        // CP_A(NUM_OBJECT_STRUCTS);
        // IF_NZ goto loop;
    }
    // RET;
}

void RespawnPlayerAndOpponent(void) {
    SET_PC(aRespawnPlayerAndOpponent);
    //  called at battle start
    CALL(aHideAllObjects);
    LD_A(PLAYER);
    CALL(aRespawnObject);
    LD_A_addr(wBattleScriptFlags);
    BIT_A(7);
    IF_Z goto skip_opponent;
    LDH_A_addr(hLastTalked);
    AND_A_A;
    IF_Z goto skip_opponent;
    CALL(aRespawnObject);

skip_opponent:

    CALL(av_UpdateSprites);
    RET;
}

//  called at battle start
void RespawnPlayerAndOpponent_Conv(void) {
    // CALL(aHideAllObjects);
    HideAllObjects();
    // LD_A(PLAYER);
    // CALL(aRespawnObject);
    RespawnObject_Conv(PLAYER);
    // LD_A_addr(wBattleScriptFlags);
    // BIT_A(7);
    // IF_Z goto skip_opponent;
    // LDH_A_addr(hLastTalked);
    // AND_A_A;
    // IF_Z goto skip_opponent;
    if(bit_test(wram->wBattleScriptFlags, 7) && hram->hLastTalked != 0) {
        // CALL(aRespawnObject);
        RespawnObject_Conv(hram->hLastTalked);
    }

// skip_opponent:

    // CALL(av_UpdateSprites);
    v_UpdateSprites_Conv();
    // RET;
}

void RespawnPlayer(void) {
    SET_PC(aRespawnPlayer);
    CALL(aHideAllObjects);
    LD_A(PLAYER);
    CALL(aRespawnObject);
    CALL(av_UpdateSprites);
    RET;
}

void RespawnPlayer_Conv(void) {
    // SET_PC(aRespawnPlayer);
    // CALL(aHideAllObjects);
    HideAllObjects();
    // LD_A(PLAYER);
    // CALL(aRespawnObject);
    RespawnObject_Conv(PLAYER);
    // CALL(av_UpdateSprites);
    v_UpdateSprites_Conv();
    // RET;
}

void RespawnObject(void) {
    SET_PC(aRespawnObject);
    CP_A(NUM_OBJECTS);
    RET_NC;
    CALL(aGetMapObject);
    LD_HL(MAPOBJECT_OBJECT_STRUCT_ID);
    ADD_HL_BC;
    LD_A_hl;
    CP_A(-1);
    RET_Z;
    CP_A(NUM_OBJECT_STRUCTS);
    RET_NC;
    CALL(aGetObjectStruct);
    CALL(aDoesObjectHaveASprite);
    RET_Z;
    CALL(aUpdateRespawnedObjectFrozen);
    RET;
}

void RespawnObject_Conv(uint8_t a) {
    // SET_PC(aRespawnObject);
    // CP_A(NUM_OBJECTS);
    // RET_NC;
    if(a >= NUM_OBJECTS)
        return;
    // CALL(aGetMapObject);
    struct MapObject* bc = GetMapObject_Conv(a);
    // LD_HL(MAPOBJECT_OBJECT_STRUCT_ID);
    // ADD_HL_BC;
    // LD_A_hl;
    // CP_A(-1);
    // RET_Z;
    if(bc->structId == 0xff)
        return;
    // CP_A(NUM_OBJECT_STRUCTS);
    // RET_NC;
    if(bc->structId >= NUM_OBJECT_STRUCTS)
        return;
    // CALL(aGetObjectStruct);
    struct Object* obj = GetObjectStruct_Conv(bc->structId);
    // CALL(aDoesObjectHaveASprite);
    // RET_Z;
    if(!DoesObjectHaveASprite_Conv(obj))
        return;
    // CALL(aUpdateRespawnedObjectFrozen);
    UpdateRespawnedObjectFrozen_Conv(obj);
    // RET;
}

void HideAllObjects(void) {
    // SET_PC(aHideAllObjects);
    // XOR_A_A;
    // LD_BC(wObjectStructs);
    struct Object* bc = &wram->wPlayerStruct;
    hram->hMapObjectIndex = 0;

    do {
    // loop:

        // LDH_addr_A(hMapObjectIndex);
        // CALL(aSetFacing_Standing);
        SetFacing_Standing_Conv(bc);
        // LD_HL(OBJECT_LENGTH);
        // ADD_HL_BC;
        // LD_B_H;
        // LD_C_L;
        bc++;
        // LDH_A_addr(hMapObjectIndex);
        // INC_A;
        // CP_A(NUM_OBJECT_STRUCTS);
        // IF_NZ goto loop;
    } while(++hram->hMapObjectIndex != NUM_OBJECT_STRUCTS);
    // RET;
}

void UpdateObjectFrozen(void) {
    SET_PC(aUpdateObjectFrozen);
    PUSH_BC;
    CALL(aCheckObjectCoveredByTextbox);
    POP_BC;
    JR_C(mSetFacing_Standing);
    CALL(aCheckObjectOnScreen);
    JR_C(mSetFacing_Standing);
    CALL(aUpdateObjectNextTile);
    FARCALL(aHandleFrozenObjectAction);  // no need to farcall
    XOR_A_A;
    RET;
}

bool UpdateObjectFrozen_Conv(struct Object* bc) {
    // SET_PC(aUpdateObjectFrozen);
    // PUSH_BC;
    // CALL(aCheckObjectCoveredByTextbox);
    // POP_BC;
    // JR_C(mSetFacing_Standing);
    if(CheckObjectCoveredByTextbox_Conv(bc))
        return SetFacing_Standing_Conv(bc);
    
    // CALL(aCheckObjectOnScreen);
    // JR_C(mSetFacing_Standing);
    if(CheckObjectOnScreen_Conv(bc))
        return SetFacing_Standing_Conv(bc);
    
    // CALL(aUpdateObjectNextTile);
    UpdateObjectNextTile_Conv(bc);
    // FARCALL(aHandleFrozenObjectAction);  // no need to farcall
    HandleFrozenObjectAction_Conv(bc);
    // XOR_A_A;
    // RET;
    return false;
}

void UpdateRespawnedObjectFrozen(void) {
    SET_PC(aUpdateRespawnedObjectFrozen);
    CALL(aCheckObjectOnScreen);
    JR_C(mSetFacing_Standing);
    FARCALL(aHandleFrozenObjectAction);  // no need to farcall
    XOR_A_A;
    RET;
}

void UpdateRespawnedObjectFrozen_Conv(struct Object* bc) {
    // SET_PC(aUpdateRespawnedObjectFrozen);
    // CALL(aCheckObjectOnScreen);
    // JR_C(mSetFacing_Standing);
    if(CheckObjectOnScreen_Conv(bc)) {
    // FARCALL(aHandleFrozenObjectAction);  // no need to farcall
        HandleFrozenObjectAction_Conv(bc);
    }
    // XOR_A_A;
    // RET;
}

void SetFacing_Standing(void) {
    SET_PC(aSetFacing_Standing);
    LD_HL(OBJECT_FACING_STEP);
    ADD_HL_BC;
    LD_hl(STANDING);
    SCF;
    RET;
}

bool SetFacing_Standing_Conv(struct Object* bc) {
    // LD_HL(OBJECT_FACING_STEP);
    // ADD_HL_BC;
    // LD_hl(STANDING);
    bc->facingStep = STANDING;
    // SCF;
    // RET;
    return true;
}

void UpdateObjectNextTile(void) {
    SET_PC(aUpdateObjectNextTile);
    PUSH_BC;
    LD_HL(OBJECT_NEXT_MAP_X);
    ADD_HL_BC;
    LD_D_hl;
    LD_HL(OBJECT_NEXT_MAP_Y);
    ADD_HL_BC;
    LD_E_hl;
    CALL(aGetCoordTile);
    POP_BC;
    LD_HL(OBJECT_NEXT_TILE);
    ADD_HL_BC;
    LD_hl_A;
    FARCALL(aUpdateTallGrassFlags);  // no need to farcall
    RET;
}

void UpdateObjectNextTile_Conv(struct Object* bc) {
    // SET_PC(aUpdateObjectNextTile);
    // PUSH_BC;
    // LD_HL(OBJECT_NEXT_MAP_X);
    // ADD_HL_BC;
    // LD_D_hl;
    // LD_HL(OBJECT_NEXT_MAP_Y);
    // ADD_HL_BC;
    // LD_E_hl;
    // CALL(aGetCoordTile);
    // POP_BC;
    // LD_HL(OBJECT_NEXT_TILE);
    // ADD_HL_BC;
    // LD_hl_A;
    bc->nextTile = GetCoordTile_Conv(bc->nextMapX, bc->nextMapY);
    // FARCALL(aUpdateTallGrassFlags);  // no need to farcall
    UpdateTallGrassFlags_Conv(bc);
    // RET;
}

void CheckObjectOnScreen(void) {
    SET_PC(aCheckObjectOnScreen);
    LD_HL(OBJECT_NEXT_MAP_X);
    ADD_HL_BC;
    LD_D_hl;
    LD_HL(OBJECT_NEXT_MAP_Y);
    ADD_HL_BC;
    LD_E_hl;
    INC_D;
    INC_E;
    LD_A_addr(wXCoord);
    CP_A_D;
    IF_Z goto equal_x;
    IF_NC goto nope;
    ADD_A(MAPOBJECT_SCREEN_WIDTH - 1);
    CP_A_D;
    IF_C goto nope;

equal_x:

    LD_A_addr(wYCoord);
    CP_A_E;
    IF_Z goto equal_y;
    IF_NC goto nope;
    ADD_A(MAPOBJECT_SCREEN_HEIGHT - 1);
    CP_A_E;
    IF_C goto nope;

equal_y:

    XOR_A_A;
    RET;

nope:

    SCF;
    RET;
}

bool CheckObjectOnScreen_Conv(struct Object* bc) {
    // LD_HL(OBJECT_NEXT_MAP_X);
    // ADD_HL_BC;
    // LD_D_hl;
    uint8_t x = bc->nextMapX + 1;
    // LD_HL(OBJECT_NEXT_MAP_Y);
    // ADD_HL_BC;
    // LD_E_hl;
    uint8_t y = bc->nextMapY + 1;
    // INC_D;
    // INC_E;
    // LD_A_addr(wXCoord);
    // CP_A_D;
    // IF_Z goto equal_x;
    // IF_NC goto nope;
    // ADD_A(MAPOBJECT_SCREEN_WIDTH - 1);
    // CP_A_D;
    // IF_C goto nope;
    uint8_t n = wram->wXCoord;
    if(n == x || (n < x && (n + (MAPOBJECT_SCREEN_WIDTH - 1) >= x))) {
    // equal_x:

        // LD_A_addr(wYCoord);
        n = wram->wYCoord;
        // CP_A_E;
        // IF_Z goto equal_y;
        // IF_NC goto nope;
        // ADD_A(MAPOBJECT_SCREEN_HEIGHT - 1);
        // CP_A_E;
        // IF_C goto nope;
        if(n == y || (n < y && (n + (MAPOBJECT_SCREEN_HEIGHT - 1) >= y))) {
        // equal_y:

            // XOR_A_A;
            // RET;
            return false;
        }
    }
// nope:
    // SCF;
    // RET;
    return true;
}

void CheckObjectCoveredByTextbox(void) {
    SET_PC(aCheckObjectCoveredByTextbox);
    //  Check whether the object fits in the screen width.
    LD_A_addr(wPlayerBGMapOffsetX);
    LD_D_A;
    LD_HL(OBJECT_SPRITE_X_OFFSET);
    ADD_HL_BC;
    LD_A_hl;
    LD_HL(OBJECT_SPRITE_X);
    ADD_HL_BC;
    ADD_A_hl;
    ADD_A_D;
    CP_A(0xf0);
    IF_NC goto ok1;
    CP_A(SCREEN_WIDTH_PX);
    JP_NC(mCheckObjectCoveredByTextbox_nope);

ok1:

    //  Account for objects currently moving left/right.
    AND_A(0b00000111);
    LD_D(2);
    CP_A(TILE_WIDTH / 2);
    IF_C goto ok2;
    LD_D(3);

ok2:

    //  Convert pixels to tiles.
    LD_A_hl;
    SRL_A;
    SRL_A;
    SRL_A;
    CP_A(SCREEN_WIDTH);
    IF_C goto ok3;
    SUB_A(BG_MAP_WIDTH);

ok3:

    LDH_addr_A(hCurSpriteXCoord);

    //  Check whether the object fits in the screen height.
    LD_A_addr(wPlayerBGMapOffsetY);
    LD_E_A;
    LD_HL(OBJECT_SPRITE_Y_OFFSET);
    ADD_HL_BC;
    LD_A_hl;
    LD_HL(OBJECT_SPRITE_Y);
    ADD_HL_BC;
    ADD_A_hl;
    ADD_A_E;
    CP_A(0xf0);
    IF_NC goto ok4;
    CP_A(SCREEN_HEIGHT_PX);
    IF_NC goto nope;

ok4:

    //  Account for objects currently moving up/down.
    AND_A(0b00000111);
    LD_E(2);
    CP_A(TILE_WIDTH / 2);
    IF_C goto ok5;
    LD_E(3);

ok5:

    //  Convert pixels to tiles.
    LD_A_hl;
    SRL_A;
    SRL_A;
    SRL_A;
    CP_A(SCREEN_HEIGHT);
    IF_C goto ok6;
    SUB_A(BG_MAP_HEIGHT);

ok6:

    LDH_addr_A(hCurSpriteYCoord);

    //  Account for big objects that are twice as wide and high.
    LD_HL(OBJECT_PALETTE);
    ADD_HL_BC;
    BIT_hl(BIG_OBJECT_F);
    IF_Z goto ok7;
    LD_A_D;
    ADD_A(2);
    LD_D_A;
    LD_A_E;
    ADD_A(2);
    LD_E_A;

ok7:

    LD_A_D;
    LDH_addr_A(hCurSpriteXPixel);

loop:

    LDH_A_addr(hCurSpriteXPixel);
    LD_D_A;
    LDH_A_addr(hCurSpriteYCoord);
    ADD_A_E;
    DEC_A;
    CP_A(SCREEN_HEIGHT);
    IF_NC goto ok9;
    LD_B_A;

next:

    LDH_A_addr(hCurSpriteXCoord);
    ADD_A_D;
    DEC_A;
    CP_A(SCREEN_WIDTH);
    IF_NC goto ok8;
    LD_C_A;
    PUSH_BC;
    CALL(aCoord2Tile);
    POP_BC;
    //  NPCs disappear if standing on tile $60-$7f (or $e0-$ff),
    //  since those IDs are for text characters and textbox frames.
    LD_A_hl;
    CP_A(FIRST_REGULAR_TEXT_CHAR);
    IF_NC goto nope;

ok8:

    DEC_D;
    IF_NZ goto next;

ok9:

    DEC_E;
    IF_NZ goto loop;

    AND_A_A;
    RET;

nope:

    SCF;
    RET;
}

bool CheckObjectCoveredByTextbox_Conv(struct Object* bc) {
    // SET_PC(aCheckObjectCoveredByTextbox);
    //  Check whether the object fits in the screen width.
    // LD_A_addr(wPlayerBGMapOffsetX);
    // LD_D_A;
    // LD_HL(OBJECT_SPRITE_X_OFFSET);
    // ADD_HL_BC;
    // LD_A_hl;
    // LD_HL(OBJECT_SPRITE_X);
    // ADD_HL_BC;
    // ADD_A_hl;
    // ADD_A_D;
    uint8_t x = bc->spriteXOffset + bc->spriteX + wram->wPlayerBGMapOffsetX;
    // CP_A(0xf0);
    // IF_NC goto ok1;
    // CP_A(SCREEN_WIDTH_PX);
    // JP_NC(mCheckObjectCoveredByTextbox_nope);
    if(x >= 0xf0 || x < SCREEN_WIDTH_PX) {
        // ok1:
        //  Account for objects currently moving left/right.
        // AND_A(0b00000111);
        // LD_D(2);
        // CP_A(TILE_WIDTH / 2);
        // IF_C goto ok2;
        // LD_D(3);
        uint8_t d = ((x & 0b00000111) >= TILE_WIDTH / 2)? 3: 2;
        // ok2:

        //  Convert pixels to tiles.
        // LD_A_hl;
        // SRL_A;
        // SRL_A;
        // SRL_A;
        // CP_A(SCREEN_WIDTH);
        // IF_C goto ok3;
        x = bc->spriteX >> 3;
        if(x >= SCREEN_WIDTH)
            x -= BG_MAP_WIDTH;
        // SUB_A(BG_MAP_WIDTH);

        // ok3:

        // LDH_addr_A(hCurSpriteXCoord);
        hram->hCurSpriteXCoord = x;

        // //  Check whether the object fits in the screen height.
        // LD_A_addr(wPlayerBGMapOffsetY);
        // LD_E_A;
        // LD_HL(OBJECT_SPRITE_Y_OFFSET);
        // ADD_HL_BC;
        // LD_A_hl;
        // LD_HL(OBJECT_SPRITE_Y);
        // ADD_HL_BC;
        // ADD_A_hl;
        // ADD_A_E;
        uint8_t y = bc->spriteYOffset + bc->spriteY + wram->wPlayerBGMapOffsetY;
        // CP_A(0xf0);
        // IF_NC goto ok4;
        // CP_A(SCREEN_HEIGHT_PX);
        // IF_NC goto nope;
        if(y >= 0xf0 || y < SCREEN_HEIGHT_PX) {
        // ok4:

            //  Account for objects currently moving up/down.
            // AND_A(0b00000111);
            // LD_E(2);
            // CP_A(TILE_WIDTH / 2);
            // IF_C goto ok5;
            // LD_E(3);
            uint8_t e = ((y & 0b00000111) >= TILE_WIDTH / 2)? 3: 2;

        // ok5:

            //  Convert pixels to tiles.
            // LD_A_hl;
            // SRL_A;
            // SRL_A;
            // SRL_A;
            // CP_A(SCREEN_HEIGHT);
            // IF_C goto ok6;
            // SUB_A(BG_MAP_HEIGHT);
            y = bc->spriteY >> 3;
            if(y >= SCREEN_HEIGHT)
                y -= BG_MAP_HEIGHT;

        // ok6:

        //     LDH_addr_A(hCurSpriteYCoord);
            hram->hCurSpriteYCoord = y;

            //  Account for big objects that are twice as wide and high.
            // LD_HL(OBJECT_PALETTE);
            // ADD_HL_BC;
            // BIT_hl(BIG_OBJECT_F);
            // IF_Z goto ok7;
            if(bit_test(bc->palette, BIG_OBJECT_F)) {
                // LD_A_D;
                // ADD_A(2);
                // LD_D_A;
                // LD_A_E;
                // ADD_A(2);
                // LD_E_A;
                d += 2;
                e += 2;
            }


        // ok7:

        //     LD_A_D;
        //     LDH_addr_A(hCurSpriteXPixel);
            hram->hCurSpriteXPixel = d;

        // loop:
            do {
                // LDH_A_addr(hCurSpriteXPixel);
                // LD_D_A;
                d = hram->hCurSpriteXPixel;
                // LDH_A_addr(hCurSpriteYCoord);
                // ADD_A_E;
                // DEC_A;
                uint8_t ycoord = (hram->hCurSpriteYCoord + e) - 1;
                // CP_A(SCREEN_HEIGHT);
                // IF_NC goto ok9;
                if(ycoord >= SCREEN_HEIGHT) 
                    continue;
                // LD_B_A;

                do {
                // next:
                    // LDH_A_addr(hCurSpriteXCoord);
                    // ADD_A_D;
                    // DEC_A;
                    uint8_t xcoord = (hram->hCurSpriteXCoord + d) - 1;
                    // CP_A(SCREEN_WIDTH);
                    // IF_NC goto ok8;
                    if(xcoord >= SCREEN_WIDTH)
                        continue;
                    // LD_C_A;
                    // PUSH_BC;
                    // CALL(aCoord2Tile);
                    // POP_BC;
                    // //  NPCs disappear if standing on tile $60-$7f (or $e0-$ff),
                    // //  since those IDs are for text characters and textbox frames.
                    // LD_A_hl;
                    // CP_A(FIRST_REGULAR_TEXT_CHAR);
                    // IF_NC goto nope;
                    if(*(Coord2Tile_Conv(xcoord, ycoord)) >= FIRST_REGULAR_TEXT_CHAR)
                        return true;
                // ok8:
                    // DEC_D;
                    // IF_NZ goto next;
                } while(--d != 0);
            // ok9:
                // DEC_E;
                // IF_NZ goto loop;
            } while(--e != 0);
            // AND_A_A;
            // RET;
            return false;
        }
    }
    return true;
}

void HandleNPCStep(void) {
    // SET_PC(aHandleNPCStep);
    // CALL(aResetStepVector);
    ResetStepVector();
    // CALL(aDoStepsForAllObjects);
    DoStepsForAllObjects();
    // RET;
}

void ResetStepVector(void) {
    // SET_PC(aResetStepVector);
    // XOR_A_A;
    // LD_addr_A(wPlayerStepVectorX);
    wram->wPlayerStepVectorX = 0;
    // LD_addr_A(wPlayerStepVectorY);
    wram->wPlayerStepVectorY = 0;
    // LD_addr_A(wPlayerStepFlags);
    wram->wPlayerStepFlags = 0;
    // LD_A(STANDING);
    // LD_addr_A(wPlayerStepDirection);
    wram->wPlayerStepDirection = STANDING;
    // RET;
}

void DoStepsForAllObjects(void) {
    // SET_PC(aDoStepsForAllObjects);
    // LD_BC(wObjectStructs);
    struct Object* bc = &wram->wPlayerStruct;
    // XOR_A_A;
    uint8_t a = 0;

    do {
    // loop:

        // LDH_addr_A(hMapObjectIndex);
        hram->hMapObjectIndex = a;
        // CALL(aDoesObjectHaveASprite);
        // IF_Z goto next;
        if(DoesObjectHaveASprite_Conv(bc + a)) {
            // CALL(aHandleObjectStep);
            HandleObjectStep_Conv(bc + a);
        }
    // next:

        // LD_HL(OBJECT_LENGTH);
        // ADD_HL_BC;
        // LD_B_H;
        // LD_C_L;
        // LDH_A_addr(hMapObjectIndex);
        // INC_A;
        // CP_A(NUM_OBJECT_STRUCTS);
        // IF_NZ goto loop;
    } while(++a != NUM_OBJECT_STRUCTS);
    // RET;
}

void RefreshPlayerSprite(void) {
    // SET_PC(aRefreshPlayerSprite);
    // LD_A(movement_step_sleep);
    // LD_addr_A(wPlayerNextMovement);
    wram->wPlayerNextMovement = movement_step_sleep;
    // LD_addr_A(wPlayerMovement);
    wram->wPlayerMovement = movement_step_sleep;
    // XOR_A_A;
    // LD_addr_A(wPlayerTurningDirection);
    wram->wPlayerTurningDirection = 0;
    // LD_addr_A(wPlayerObjectStepFrame);
    wram->wPlayerStruct.stepFrame = 0;
    // CALL(aTryResetPlayerAction);
    TryResetPlayerAction();
    // FARCALL(aCheckWarpFacingDown);
    if(CheckWarpFacingDown_Conv()) {
        // CALL_C(aSpawnInFacingDown);
        SpawnInFacingDown();
    }
    // CALL(aSpawnInCustomFacing);
    SpawnInCustomFacing();
    // RET;
}

void TryResetPlayerAction(void) {
    // SET_PC(aTryResetPlayerAction);
    // LD_HL(wPlayerSpriteSetupFlags);
    // BIT_hl(PLAYERSPRITESETUP_RESET_ACTION_F);
    // IF_NZ goto ok;
    if(bit_test(wram->wPlayerSpriteSetupFlags, PLAYERSPRITESETUP_RESET_ACTION_F)) {
    // ok:
        // LD_A(OBJECT_ACTION_00);
        // LD_addr_A(wPlayerAction);
        wram->wPlayerStruct.action = OBJECT_ACTION_00;
        // RET;
        return;
    }
    // RET;
    return;
}

void SpawnInCustomFacing(void) {
    // SET_PC(aSpawnInCustomFacing);
    // LD_HL(wPlayerSpriteSetupFlags);
    // BIT_hl(PLAYERSPRITESETUP_CUSTOM_FACING_F);
    // RET_Z;
    if(!bit_test(wram->wPlayerSpriteSetupFlags, PLAYERSPRITESETUP_CUSTOM_FACING_F))
        return;
    // LD_A_addr(wPlayerSpriteSetupFlags);
    // AND_A(PLAYERSPRITESETUP_FACING_MASK);
    // ADD_A_A;
    // ADD_A_A;
    // JR(mv_ContinueSpawnFacing);
    return v_ContinueSpawnFacing_Conv((wram->wPlayerSpriteSetupFlags & (PLAYERSPRITESETUP_FACING_MASK)) << 2);
}

void SpawnInFacingDown(void) {
    // SET_PC(aSpawnInFacingDown);
    // LD_A(DOWN);
    return v_ContinueSpawnFacing_Conv(DOWN);
}

void v_ContinueSpawnFacing(void) {
    SET_PC(av_ContinueSpawnFacing);
    LD_BC(wPlayerStruct);
    CALL(aSetSpriteDirection);
    RET;
}

void v_ContinueSpawnFacing_Conv(uint8_t a) {
    // SET_PC(av_ContinueSpawnFacing);
    // LD_BC(wPlayerStruct);
    // CALL(aSetSpriteDirection);
    SetSpriteDirection_Conv(&wram->wPlayerStruct, a);
    // RET;
}

void v_SetPlayerPalette(void) {
    SET_PC(av_SetPlayerPalette);
    LD_A_D;
    AND_A(1 << 7);
    RET_Z;
    LD_BC(0);  // debug?
    LD_HL(OBJECT_FACING);
    ADD_HL_BC;
    LD_A_hl;
    OR_A_D;
    LD_hl_A;
    LD_A_D;
    SWAP_A;
    AND_A(PALETTE_MASK);
    LD_D_A;
    LD_BC(wPlayerStruct);
    LD_HL(OBJECT_PALETTE);
    ADD_HL_BC;
    LD_A_hl;
    AND_A(~PALETTE_MASK);
    OR_A_D;
    LD_hl_A;
    RET;
}

void v_SetPlayerPalette_Conv(uint8_t d) {
    // SET_PC(av_SetPlayerPalette);
    // LD_A_D;
    // AND_A(1 << 7);
    // RET_Z;
    if((d & (1 << 7)) == 0)
        return;
    // LD_BC(0);  // debug?
    // LD_HL(OBJECT_FACING);
    // ADD_HL_BC;
    // LD_A_hl;
    // OR_A_D;
    // LD_hl_A;
    // LD_A_D;
    // SWAP_A;
    // AND_A(PALETTE_MASK);
    // LD_D_A;
    d = ((d << 4) | (d >> 4)) & PALETTE_MASK;
    // LD_BC(wPlayerStruct);
    // LD_HL(OBJECT_PALETTE);
    // ADD_HL_BC;
    // LD_A_hl;
    // AND_A(~PALETTE_MASK);
    wram->wPlayerStruct.palette &= ~PALETTE_MASK;
    // OR_A_D;
    // LD_hl_A;
    wram->wPlayerStruct.palette |= d;
    // RET;
}

void StartFollow(void) {
    SET_PC(aStartFollow);
    PUSH_BC;
    LD_A_B;
    CALL(aSetLeaderIfVisible);
    POP_BC;
    RET_C;
    LD_A_C;
    CALL(aSetFollowerIfVisible);
    FARCALL(aQueueFollowerFirstStep);
    RET;
}

void StartFollow_Conv(uint8_t b, uint8_t c) {
    // SET_PC(aStartFollow);
    // PUSH_BC;
    // LD_A_B;
    // CALL(aSetLeaderIfVisible);
    // POP_BC;
    // RET_C;
    if(!SetLeaderIfVisible_Conv(b))
        return;
    // LD_A_C;
    // CALL(aSetFollowerIfVisible);
    SetFollowerIfVisible_Conv(c);
    // FARCALL(aQueueFollowerFirstStep);
    QueueFollowerFirstStep_Conv();
    // RET;
}

void SetLeaderIfVisible(void) {
    SET_PC(aSetLeaderIfVisible);
    CALL(aCheckObjectVisibility);
    RET_C;
    LDH_A_addr(hObjectStructIndex);
    LD_addr_A(wObjectFollow_Leader);
    RET;
}

bool SetLeaderIfVisible_Conv(uint8_t a) {
    // SET_PC(aSetLeaderIfVisible);
    // CALL(aCheckObjectVisibility);
    struct Object* bc = CheckObjectVisibility_Conv(a);
    // RET_C;
    if(bc == NULL)
        return false;
    // LDH_A_addr(hObjectStructIndex);
    // LD_addr_A(wObjectFollow_Leader);
    wram->wObjectFollow_Leader = hram->hObjectStructIndex;
    // RET;
    return true;
}

void StopFollow(void) {
    SET_PC(aStopFollow);
    CALL(aResetLeader);
    CALL(aResetFollower);
    RET;
}

void StopFollow_Conv(void) {
    // SET_PC(aStopFollow);
    // CALL(aResetLeader);
    ResetLeader_Conv();
    // CALL(aResetFollower);
    ResetFollower_Conv();
    // RET;
}

void ResetLeader(void) {
    SET_PC(aResetLeader);
    LD_A(-1);
    LD_addr_A(wObjectFollow_Leader);
    RET;
}

void ResetLeader_Conv(void) {
    // SET_PC(aResetLeader);
    // LD_A(-1);
    // LD_addr_A(wObjectFollow_Leader);
    // RET;
    wram->wObjectFollow_Leader = 0xff;
}

void SetFollowerIfVisible(void) {
    SET_PC(aSetFollowerIfVisible);
    PUSH_AF;
    CALL(aResetFollower);
    POP_AF;
    CALL(aCheckObjectVisibility);
    RET_C;
    LD_HL(OBJECT_MOVEMENTTYPE);
    ADD_HL_BC;
    LD_hl(SPRITEMOVEDATA_FOLLOWING);
    LD_HL(OBJECT_STEP_TYPE);
    ADD_HL_BC;
    LD_hl(STEP_TYPE_RESET);
    LDH_A_addr(hObjectStructIndex);
    LD_addr_A(wObjectFollow_Follower);
    RET;
}

bool SetFollowerIfVisible_Conv(uint8_t a) {
    // SET_PC(aSetFollowerIfVisible);
    // PUSH_AF;
    // CALL(aResetFollower);
    ResetFollower_Conv();
    // POP_AF;
    // CALL(aCheckObjectVisibility);
    // RET_C;
    struct Object* bc = CheckObjectVisibility_Conv(a);
    if(bc == NULL)
        return false;
    // LD_HL(OBJECT_MOVEMENTTYPE);
    // ADD_HL_BC;
    // LD_hl(SPRITEMOVEDATA_FOLLOWING);
    bc->movementType = SPRITEMOVEDATA_FOLLOWING;
    // LD_HL(OBJECT_STEP_TYPE);
    // ADD_HL_BC;
    // LD_hl(STEP_TYPE_RESET);
    bc->stepType = STEP_TYPE_RESET;
    // LDH_A_addr(hObjectStructIndex);
    // LD_addr_A(wObjectFollow_Follower);
    wram->wObjectFollow_Follower = hram->hObjectStructIndex;
    // RET;
    return true;
}

void ResetFollower(void) {
    SET_PC(aResetFollower);
    LD_A_addr(wObjectFollow_Follower);
    CP_A(-1);
    RET_Z;
    CALL(aGetObjectStruct);
    FARCALL(aResetObject);  // no need to farcall
    LD_A(-1);
    LD_addr_A(wObjectFollow_Follower);
    RET;
}

void ResetFollower_Conv(void) {
    // SET_PC(aResetFollower);
    // LD_A_addr(wObjectFollow_Follower);
    // CP_A(-1);
    // RET_Z;
    if(wram->wObjectFollow_Follower == 0xff)
        return;
    // CALL(aGetObjectStruct);
    struct Object* bc = GetObjectStruct_Conv(wram->wObjectFollow_Follower);
    // FARCALL(aResetObject);  // no need to farcall
    ResetObject_Conv(bc);
    // LD_A(-1);
    // LD_addr_A(wObjectFollow_Follower);
    wram->wObjectFollow_Follower = 0xff;
    // RET;
}

void FreezeAllOtherObjects(void) {
    SET_PC(aFreezeAllOtherObjects);
    LD_A_C;
    CALL(aCheckObjectVisibility);
    RET_C;
    PUSH_BC;
    CALL(aFreezeAllObjects);
    POP_BC;
    LD_HL(OBJECT_FLAGS2);
    ADD_HL_BC;
    RES_hl(FROZEN_F);
    XOR_A_A;
    RET;
}

bool FreezeAllOtherObjects_Conv(uint8_t c) {
    // SET_PC(aFreezeAllOtherObjects);
    // LD_A_C;
    // CALL(aCheckObjectVisibility);
    // RET_C;
    struct Object* bc = CheckObjectVisibility_Conv(c);
    if(bc == NULL)
        return false;
    // PUSH_BC;
    // CALL(aFreezeAllObjects);
    FreezeAllObjects_Conv();
    // POP_BC;
    // LD_HL(OBJECT_FLAGS2);
    // ADD_HL_BC;
    // RES_hl(FROZEN_F);
    bit_reset(bc->flags2, FROZEN_F);
    // XOR_A_A;
    // RET;
    return true;
}

void FreezeObject(void) {
    SET_PC(aFreezeObject);
    //  //  unreferenced
    CALL(aCheckObjectVisibility);
    RET_C;
    LD_HL(OBJECT_FLAGS2);
    ADD_HL_BC;
    SET_hl(FROZEN_F);
    XOR_A_A;
    RET;
}

void FreezeAllObjects(void) {
    SET_PC(aFreezeAllObjects);
    LD_BC(wObjectStructs);
    XOR_A_A;

loop:

    PUSH_AF;
    CALL(aDoesObjectHaveASprite);
    IF_Z goto next;
    LD_HL(OBJECT_FLAGS2);
    ADD_HL_BC;
    SET_hl(FROZEN_F);

next:

    LD_HL(OBJECT_LENGTH);
    ADD_HL_BC;
    LD_B_H;
    LD_C_L;
    POP_AF;
    INC_A;
    CP_A(NUM_OBJECT_STRUCTS);
    IF_NZ goto loop;
    RET;
}

void FreezeAllObjects_Conv(void) {
    // SET_PC(aFreezeAllObjects);
    // LD_BC(wObjectStructs);
    // XOR_A_A;

    for(size_t i = 0; i < NUM_OBJECT_STRUCTS; ++i) {
    // loop:
        // PUSH_AF;
        struct Object* bc = (&wram->wPlayerStruct + i);
        // CALL(aDoesObjectHaveASprite);
        // IF_Z goto next;
        if(!DoesObjectHaveASprite_Conv(bc))
            continue;
        // LD_HL(OBJECT_FLAGS2);
        // ADD_HL_BC;
        // SET_hl(FROZEN_F);
        bit_set(bc->flags2, FROZEN_F);

    // next:

        // LD_HL(OBJECT_LENGTH);
        // ADD_HL_BC;
        // LD_B_H;
        // LD_C_L;
        // POP_AF;
        // INC_A;
        // CP_A(NUM_OBJECT_STRUCTS);
        // IF_NZ goto loop;
    }
    // RET;
}

void v_UnfreezeFollowerObject(void) {
    SET_PC(av_UnfreezeFollowerObject);
    LD_A_addr(wObjectFollow_Leader);
    CP_A(-1);
    RET_Z;
    PUSH_BC;
    CALL(aGetObjectStruct);
    LD_HL(OBJECT_MAP_OBJECT_INDEX);
    ADD_HL_BC;
    LD_A_hl;
    POP_BC;
    CP_A_C;
    RET_NZ;
    LD_A_addr(wObjectFollow_Follower);
    CP_A(-1);
    RET_Z;
    CALL(aGetObjectStruct);
    LD_HL(OBJECT_FLAGS2);
    ADD_HL_BC;
    RES_hl(FROZEN_F);
    RET;
}

void v_UnfreezeFollowerObject_Conv(uint8_t c) {
    // SET_PC(av_UnfreezeFollowerObject);
    // LD_A_addr(wObjectFollow_Leader);
    // CP_A(-1);
    // RET_Z;
    if(wram->wObjectFollow_Leader == 0xff)
        return;
    // PUSH_BC;
    // CALL(aGetObjectStruct);
    struct Object* bc2 = GetObjectStruct_Conv(wram->wObjectFollow_Leader);
    // LD_HL(OBJECT_MAP_OBJECT_INDEX);
    // ADD_HL_BC;
    // LD_A_hl;
    // POP_BC;
    // CP_A_C;
    // RET_NZ;
    if(bc2->mapObjectIndex != c)
        return;
    // LD_A_addr(wObjectFollow_Follower);
    // CP_A(-1);
    // RET_Z;
    if(wram->wObjectFollow_Follower == 0xff)
        return;
    // CALL(aGetObjectStruct);
    struct Object* bc = GetObjectStruct_Conv(wram->wObjectFollow_Follower);
    // LD_HL(OBJECT_FLAGS2);
    // ADD_HL_BC;
    // RES_hl(FROZEN_F);
    bit_reset(bc->flags2, FROZEN_F);
    // RET;
}

void UnfreezeAllObjects(void) {
    SET_PC(aUnfreezeAllObjects);
    PUSH_BC;
    LD_BC(wObjectStructs);
    XOR_A_A;

loop:

    PUSH_AF;
    CALL(aDoesObjectHaveASprite);
    IF_Z goto next;
    LD_HL(OBJECT_FLAGS2);
    ADD_HL_BC;
    RES_hl(FROZEN_F);

next:

    LD_HL(OBJECT_LENGTH);
    ADD_HL_BC;
    LD_B_H;
    LD_C_L;
    POP_AF;
    INC_A;
    CP_A(NUM_OBJECT_STRUCTS);
    IF_NZ goto loop;
    POP_BC;
    RET;
}

void UnfreezeAllObjects_Conv(void) {
    // SET_PC(aUnfreezeAllObjects);
    // PUSH_BC;
    // LD_BC(wObjectStructs);
    struct Object* bc = &wram->wPlayerStruct;
    // XOR_A_A;

    for(uint8_t a = 0; a < NUM_OBJECT_STRUCTS; ++a) {
    // loop:

        // PUSH_AF;
        // CALL(aDoesObjectHaveASprite);
        // IF_Z goto next;
        if(bc->sprite == 0)
            continue;
        // LD_HL(OBJECT_FLAGS2);
        // ADD_HL_BC;
        // RES_hl(FROZEN_F);
        bit_reset(bc[a].flags2, FROZEN_F);

    // next:

        // LD_HL(OBJECT_LENGTH);
        // ADD_HL_BC;
        // LD_B_H;
        // LD_C_L;
        // POP_AF;
        // INC_A;
        // CP_A(NUM_OBJECT_STRUCTS);
        // IF_NZ goto loop;
    }
    // POP_BC;
    // RET;
}

void UnfreezeObject(void) {
    SET_PC(aUnfreezeObject);
    //  //  unreferenced
    CALL(aCheckObjectVisibility);
    RET_C;
    LD_HL(OBJECT_FLAGS2);
    ADD_HL_BC;
    RES_hl(FROZEN_F);
    RET;
}

void ResetObject(void) {
    SET_PC(aResetObject);
    LD_HL(OBJECT_MAP_OBJECT_INDEX);
    ADD_HL_BC;
    LD_A_hl;
    CP_A(-1);
    JP_Z(mResetObject_set_standing);  // a jr would have been appropriate here
    PUSH_BC;
    CALL(aGetMapObject);
    LD_HL(MAPOBJECT_MOVEMENT);
    ADD_HL_BC;
    LD_A_hl;
    POP_BC;
    LD_HL(OBJECT_MOVEMENTTYPE);
    ADD_HL_BC;
    LD_hl_A;
    LD_HL(OBJECT_STEP_TYPE);
    ADD_HL_BC;
    LD_hl(STEP_TYPE_RESET);
    RET;

set_standing:

    CALL(aGetSpriteDirection);
    RRCA;
    RRCA;
    LD_E_A;
    LD_D(0);
    LD_HL(mResetObject_standing_movefns);
    ADD_HL_DE;
    LD_A_hl;
    LD_HL(OBJECT_MOVEMENTTYPE);
    ADD_HL_BC;
    LD_hl_A;
    LD_HL(OBJECT_STEP_TYPE);
    ADD_HL_BC;
    LD_hl(STEP_TYPE_RESET);
    RET;

standing_movefns:

    // db ['SPRITEMOVEDATA_STANDING_DOWN'];
    // db ['SPRITEMOVEDATA_STANDING_UP'];
    // db ['SPRITEMOVEDATA_STANDING_LEFT'];
    // db ['SPRITEMOVEDATA_STANDING_RIGHT'];

    return v_UpdateSprites();
}

static void ResetObject_set_standing_Conv(struct Object* bc) {
    static const uint8_t standing_movefns[] = {
        SPRITEMOVEDATA_STANDING_DOWN,
        SPRITEMOVEDATA_STANDING_UP,
        SPRITEMOVEDATA_STANDING_LEFT,
        SPRITEMOVEDATA_STANDING_RIGHT,
    };

    // CALL(aGetSpriteDirection);
    uint8_t dir = GetSpriteDirection_Conv(bc);
    // RRCA;
    // RRCA;
    // LD_E_A;
    // LD_D(0);
    // LD_HL(mResetObject_standing_movefns);
    // ADD_HL_DE;
    // LD_A_hl;
    // LD_HL(OBJECT_MOVEMENTTYPE);
    // ADD_HL_BC;
    // LD_hl_A;
    bc->movementType = standing_movefns[dir >> 2];
    // LD_HL(OBJECT_STEP_TYPE);
    // ADD_HL_BC;
    // LD_hl(STEP_TYPE_RESET);
    bc->stepType = STEP_TYPE_RESET;
    // RET;
}

void ResetObject_Conv(struct Object* bc) {
    // SET_PC(aResetObject);
    // LD_HL(OBJECT_MAP_OBJECT_INDEX);
    // ADD_HL_BC;
    // LD_A_hl;
    // CP_A(-1);
    // JP_Z(mResetObject_set_standing);  // a jr would have been appropriate here
    if(bc->mapObjectIndex == 0xff)
        return ResetObject_set_standing_Conv(bc);
    // PUSH_BC;
    // CALL(aGetMapObject);
    struct MapObject* obj = GetMapObject_Conv(bc->mapObjectIndex);
    // LD_HL(MAPOBJECT_MOVEMENT);
    // ADD_HL_BC;
    // LD_A_hl;
    // POP_BC;
    // LD_HL(OBJECT_MOVEMENTTYPE);
    // ADD_HL_BC;
    // LD_hl_A;
    bc->movementType = obj->objectMovement;
    // LD_HL(OBJECT_STEP_TYPE);
    // ADD_HL_BC;
    // LD_hl(STEP_TYPE_RESET);
    bc->stepType = STEP_TYPE_RESET;
    // RET;
}

void v_UpdateSprites(void) {
    return v_UpdateSprites_Conv();
    SET_PC(av_UpdateSprites);
    LD_A_addr(wVramState);
    BIT_A(0);
    RET_Z;
    XOR_A_A;
    LDH_addr_A(hUsedSpriteIndex);
    LDH_A_addr(hOAMUpdate);
    PUSH_AF;
    LD_A(1);
    LDH_addr_A(hOAMUpdate);
    CALL(aInitSprites);
    CALL(av_UpdateSprites_fill);
    POP_AF;
    LDH_addr_A(hOAMUpdate);
    RET;

fill:

    LD_A_addr(wVramState);
    BIT_A(1);
    LD_B(NUM_SPRITE_OAM_STRUCTS * SPRITEOAMSTRUCT_LENGTH);
    IF_Z goto ok;
    LD_B((NUM_SPRITE_OAM_STRUCTS - 12) * SPRITEOAMSTRUCT_LENGTH);

ok:

    LDH_A_addr(hUsedSpriteIndex);
    CP_A_B;
    RET_NC;
    LD_L_A;
    LD_H(HIGH(wVirtualOAM));
    LD_DE(SPRITEOAMSTRUCT_LENGTH);
    LD_A_B;
    LD_C(SCREEN_HEIGHT_PX + 2 * TILE_WIDTH);

loop:

    LD_hl_C;  // y
    ADD_HL_DE;
    CP_A_L;
    IF_NZ goto loop;
    RET;
}

void v_UpdateSprites_Conv(void) {
    // SET_PC(av_UpdateSprites);
    // LD_A_addr(wVramState);
    // BIT_A(0);
    // RET_Z;
    if(!bit_test(wram->wVramState, 0))
        return;
    
    // XOR_A_A;
    // LDH_addr_A(hUsedSpriteIndex);
    hram->hUsedSpriteIndex = 0;
    // LDH_A_addr(hOAMUpdate);
    uint8_t temp = hram->hOAMUpdate;
    // PUSH_AF;
    // LD_A(1);
    // LDH_addr_A(hOAMUpdate);
    hram->hOAMUpdate = 1;
    // CALL(aInitSprites);
    InitSprites();
    // CALL(av_UpdateSprites_fill);
    
// fill:

    // LD_A_addr(wVramState);
    // BIT_A(1);
    // LD_B(NUM_SPRITE_OAM_STRUCTS * SPRITEOAMSTRUCT_LENGTH);
    // IF_Z goto ok;
    // LD_B((NUM_SPRITE_OAM_STRUCTS - 12) * SPRITEOAMSTRUCT_LENGTH);
    uint8_t b = (bit_test(wram->wVramState, 1))? (NUM_SPRITE_OAM_STRUCTS - 12) : NUM_SPRITE_OAM_STRUCTS;

// ok:

    // LDH_A_addr(hUsedSpriteIndex);
    // CP_A_B;
    // RET_NC;
    uint8_t sprite_idx = hram->hUsedSpriteIndex >> 2;
    if(sprite_idx >= b) {
        hram->hOAMUpdate = temp;
        return;
    }
    
    // LD_L_A;
    // LD_H(HIGH(wVirtualOAM));
    // LD_DE(SPRITEOAMSTRUCT_LENGTH);
    // LD_A_B;
    // LD_C(SCREEN_HEIGHT_PX + 2 * TILE_WIDTH);

    uint8_t i = sprite_idx;
    do {
        // LD_hl_C;  // y
        wram->wVirtualOAMSprite[i].yCoord = SCREEN_HEIGHT_PX + 2 * TILE_WIDTH;
        // ADD_HL_DE;
        i++;
        // CP_A_L;
        // IF_NZ goto loop;
    } while(i < b);
    // RET;
    // POP_AF;
    // LDH_addr_A(hOAMUpdate);
    hram->hOAMUpdate = temp;
}

void ApplyBGMapAnchorToObjects(void) {
    SET_PC(aApplyBGMapAnchorToObjects);
    PUSH_HL;
    PUSH_DE;
    PUSH_BC;
    LD_A_addr(wPlayerBGMapOffsetX);
    LD_D_A;
    LD_A_addr(wPlayerBGMapOffsetY);
    LD_E_A;
    LD_BC(wObjectStructs);
    LD_A(NUM_OBJECT_STRUCTS);

loop:

    PUSH_AF;
    CALL(aDoesObjectHaveASprite);
    IF_Z goto skip;
    LD_HL(OBJECT_SPRITE_X);
    ADD_HL_BC;
    LD_A_hl;
    ADD_A_D;
    LD_hl_A;
    LD_HL(OBJECT_SPRITE_Y);
    ADD_HL_BC;
    LD_A_hl;
    ADD_A_E;
    LD_hl_A;

skip:

    LD_HL(OBJECT_LENGTH);
    ADD_HL_BC;
    LD_B_H;
    LD_C_L;
    POP_AF;
    DEC_A;
    IF_NZ goto loop;
    XOR_A_A;
    LD_addr_A(wPlayerBGMapOffsetX);
    LD_addr_A(wPlayerBGMapOffsetY);
    POP_BC;
    POP_DE;
    POP_HL;
    RET;

#define PRIORITY_LOW (0x10)
#define PRIORITY_NORM (0x20)
#define PRIORITY_HIGH (0x30)

    return InitSprites();
}

void ApplyBGMapAnchorToObjects_Conv(void) {
    // SET_PC(aApplyBGMapAnchorToObjects);
    // PUSH_HL;
    // PUSH_DE;
    // PUSH_BC;
    // LD_A_addr(wPlayerBGMapOffsetX);
    // LD_D_A;
    uint8_t d = wram->wPlayerBGMapOffsetX;
    // LD_A_addr(wPlayerBGMapOffsetY);
    // LD_E_A;
    uint8_t e = wram->wPlayerBGMapOffsetY;
    // LD_BC(wObjectStructs);
    // LD_A(NUM_OBJECT_STRUCTS);
    for(size_t i = 0; i < NUM_OBJECT_STRUCTS; ++i) {
    // loop:

        // PUSH_AF;
        struct Object* bc = (&wram->wPlayerStruct + i);
        // CALL(aDoesObjectHaveASprite);
        // IF_Z goto skip;
        if(!DoesObjectHaveASprite_Conv(bc))
            continue;
        // LD_HL(OBJECT_SPRITE_X);
        // ADD_HL_BC;
        // LD_A_hl;
        // ADD_A_D;
        // LD_hl_A;
        bc->spriteX += d;
        // LD_HL(OBJECT_SPRITE_Y);
        // ADD_HL_BC;
        // LD_A_hl;
        // ADD_A_E;
        // LD_hl_A;
        bc->spriteY += e;

    // skip:

        // LD_HL(OBJECT_LENGTH);
        // ADD_HL_BC;
        // LD_B_H;
        // LD_C_L;
        // POP_AF;
        // DEC_A;
        // IF_NZ goto loop;
    }
    // XOR_A_A;
    // LD_addr_A(wPlayerBGMapOffsetX);
    wram->wPlayerBGMapOffsetX = 0;
    // LD_addr_A(wPlayerBGMapOffsetY);
    wram->wPlayerBGMapOffsetY = 0;
    // POP_BC;
    // POP_DE;
    // POP_HL;
    // RET;
}

static void InitSprites_DeterminePriorities(void) {
    // XOR_A_A;
    // LD_HL(wObjectPriorities);
    // LD_BC(NUM_OBJECT_STRUCTS);
    // CALL(aByteFill);
    ByteFill_Conv2(wram->wObjectPriorities, NUM_OBJECT_STRUCTS, 0);
    uint8_t d = 0;
    struct Object* bc = &wram->wPlayerStruct;
    uint8_t* hl = wram->wObjectPriorities;
    uint8_t e;
    // LD_D(0);
    // LD_BC(wObjectStructs);
    // LD_HL(wObjectPriorities);

    do {
        // PUSH_HL;
        // CALL(aDoesObjectHaveASprite);
        // IF_Z goto skip;
        // LD_HL(OBJECT_FACING_STEP);
        // ADD_HL_BC;
        // LD_A_hl;
        // CP_A(STANDING);
        // IF_Z goto skip;
        if(!DoesObjectHaveASprite_Conv(bc) || bc->facingStep == (uint8_t)STANDING) {
        // skip:

        //     LD_HL(OBJECT_LENGTH);
        //     ADD_HL_BC;
        //     LD_B_H;
        //     LD_C_L;
        //     POP_HL;
        //     goto next;
            bc++;
        }
        else {
            //  Define the sprite priority.
            // LD_E(PRIORITY_LOW);
            // LD_HL(OBJECT_FLAGS2);
            // ADD_HL_BC;
            // BIT_hl(LOW_PRIORITY_F);
            // IF_NZ goto add;
            if(bit_test(bc->flags2, LOW_PRIORITY_F)) {
                e = PRIORITY_LOW;
            }
            // BIT_hl(HIGH_PRIORITY_F);
            // IF_Z goto add;
            else if(!bit_test(bc->flags2, HIGH_PRIORITY_F)) {
                e = PRIORITY_NORM;
            }
            else {
                e = PRIORITY_HIGH;
            }
// add:
            // LD_HL(OBJECT_LENGTH);
            // ADD_HL_BC;
            // LD_B_H;
            // LD_C_L;
            bc++;
            // POP_HL;
            // LD_A_D;
            // OR_A_E;
            // LD_hli_A;
            *(hl++) = d | e;
        }
        // INC_D;
        // LD_A_D;
        // CP_A(NUM_OBJECT_STRUCTS);
        // IF_NZ goto loop;
    } while(++d != NUM_OBJECT_STRUCTS);
    // RET;
}

static struct Object* InitSprites_GetObjectStructPointer(uint8_t a) {
    // LD_C_A;
    // LD_B(0);
    // LD_HL(mInitSprites_Addresses);
    // ADD_HL_BC;
    // ADD_HL_BC;
    // LD_C_hl;
    // INC_HL;
    // LD_B_hl;
    // RET;
    return &wram->wPlayerStruct + a;
}

static bool InitSprites_InitSprite(struct Object* bc) {
    // LD_HL(OBJECT_SPRITE_TILE);
    // ADD_HL_BC;
    // LD_A_hl;
    uint8_t tile = bc->spriteTile;
    // AND_A(~(1 << 7));
    // LDH_addr_A(hCurSpriteTile);
    hram->hCurSpriteTile = tile & ~(1 << 7);
    // XOR_A_A;
    // BIT_hl(7);
    // IF_NZ goto not_vram1;
    // OR_A(VRAM_BANK_1);
    uint8_t a = 0;
    a |= (!bit_test(bc->spriteTile, 7))? VRAM_BANK_1: 0;

    // LD_HL(OBJECT_FLAGS2);
    // ADD_HL_BC;
    // LD_E_hl;
    // BIT_E(OBJ_FLAGS2_7);
    // IF_Z goto not_priority;
    // OR_A(PRIORITY);
    uint8_t flags2 = bc->flags2;
    a |= (bit_test(flags2, OBJ_FLAGS2_7))? PRIORITY: 0;

// not_priority:

    // BIT_E(USE_OBP1_F);
    // IF_Z goto not_obp_num;
    // OR_A(OBP_NUM);
    a |= (bit_test(flags2, USE_OBP1_F))? OBP_NUM: 0;

// not_obp_num:

    // LD_HL(OBJECT_PALETTE);
    // ADD_HL_BC;
    // LD_D_A;
    // LD_A_hl;
    // AND_A(PALETTE_MASK);
    // OR_A_D;
    // LD_D_A;
    uint8_t pal = (bc->palette & PALETTE_MASK) | a;
    // XOR_A_A;
    // BIT_E(OVERHEAD_F);
    // IF_Z goto not_overhead;
    // OR_A(PRIORITY);

// not_overhead:

    // LDH_addr_A(hCurSpriteOAMFlags);
    hram->hCurSpriteOAMFlags = (bit_test(flags2, OVERHEAD_F))? PRIORITY: 0;
    // LD_HL(OBJECT_SPRITE_X);
    // ADD_HL_BC;
    // LD_A_hl;
    // LD_HL(OBJECT_SPRITE_X_OFFSET);
    // ADD_HL_BC;
    // ADD_A_hl;
    // ADD_A(8);
    // LD_E_A;
    // LD_A_addr(wPlayerBGMapOffsetX);
    // ADD_A_E;
    // LDH_addr_A(hCurSpriteXPixel);
    hram->hCurSpriteXPixel = bc->spriteX + bc->spriteXOffset + 8 + wram->wPlayerBGMapOffsetX;

    // LD_HL(OBJECT_SPRITE_Y);
    // ADD_HL_BC;
    // LD_A_hl;
    // LD_HL(OBJECT_SPRITE_Y_OFFSET);
    // ADD_HL_BC;
    // ADD_A_hl;
    // ADD_A(12);
    // LD_E_A;
    // LD_A_addr(wPlayerBGMapOffsetY);
    // ADD_A_E;
    // LDH_addr_A(hCurSpriteYPixel);
    hram->hCurSpriteYPixel = bc->spriteY + bc->spriteYOffset + 12 + wram->wPlayerBGMapOffsetY;
    // LD_HL(OBJECT_FACING_STEP);
    // ADD_HL_BC;
    // LD_A_hl;
    uint8_t step = bc->facingStep;
    // CP_A(STANDING);
    // JP_Z(mInitSprites_done);
    // CP_A(NUM_FACINGS);
    // JP_NC(mInitSprites_done);
    if(step != (uint8_t)STANDING && step < NUM_FACINGS) {
        // LD_L_A;
        // LD_H(0);
        // ADD_HL_HL;
        // LD_BC(mFacings);
        // ADD_HL_BC;
        const struct Facing* hl = Facings[step];
        // LD_A_hli;
        // LD_H_hl;
        // LD_L_A;
        // LDH_A_addr(hUsedSpriteIndex);
        // LD_C_A;
        // LD_B(HIGH(wVirtualOAM));
        struct SpriteOAM* bc = wram->wVirtualOAMSprite + (hram->hUsedSpriteIndex >> 2);
        // LD_A_hli;
        a = hl->count;
        // LDH_addr_A(hUsedSpriteTile);
        hram->hUsedSpriteTile = a;

        // ADD_A_C;
        a += hram->hUsedSpriteIndex;
        // CP_A(LOW(wVirtualOAMEnd));
        if(a >= LOW(wVirtualOAMEnd)) {

        // full:

            // SCF;
            // RET;
            return false;
        }
        // IF_NC goto full;

    // addsprite:
        uint8_t idx = 0;
        do {
            // LDH_A_addr(hCurSpriteYPixel);
            // ADD_A_hl;
            // INC_HL;
            // LD_bc_A;  // y
            // INC_C;
            bc[idx].yCoord = hram->hCurSpriteYPixel + hl->data[idx].y;
            // LDH_A_addr(hCurSpriteXPixel);
            // ADD_A_hl;
            // INC_HL;
            // LD_bc_A;  // x
            // INC_C;
            bc[idx].xCoord = hram->hCurSpriteXPixel + hl->data[idx].x;
            // LD_E_hl;
            // INC_HL;
            uint8_t attr = hl->data[idx].attr;
            // LDH_A_addr(hCurSpriteTile);
            // BIT_E(ABSOLUTE_TILE_ID_F);
            // IF_Z goto nope1;
            // XOR_A_A;
            a = (!bit_test(attr, ABSOLUTE_TILE_ID_F))? hram->hCurSpriteTile: 0;

        // nope1:

            // ADD_A_hl;
            // INC_HL;
            // LD_bc_A;  // tile id
            // INC_C;
            bc[idx].tileID = a + hl->data[idx].tile_idx;
            // LD_A_E;
            // BIT_A(RELATIVE_ATTRIBUTES_F);
            // IF_Z goto nope2;
            // LDH_A_addr(hCurSpriteOAMFlags);
            // OR_A_E;
            a = (bit_test(attr, RELATIVE_ATTRIBUTES_F))? hram->hCurSpriteOAMFlags | attr: attr;

        // nope2:

            // AND_A(OBP_NUM | X_FLIP | Y_FLIP | PRIORITY);
            // OR_A_D;
            // LD_bc_A;  // attributes
            // INC_C;
            bc[idx].attributes = pal | (a & (OBP_NUM | X_FLIP | Y_FLIP | PRIORITY));
            // LDH_A_addr(hUsedSpriteTile);
            // DEC_A;
            // LDH_addr_A(hUsedSpriteTile);
            a = --hram->hUsedSpriteTile;
            // IF_NZ goto addsprite;
            idx++;
            if(a != 0) continue;
            // LD_A_C;
            // LDH_addr_A(hUsedSpriteIndex);
            hram->hUsedSpriteIndex += sizeof(struct SpriteOAM) * idx;
            break;
        } while(1);
    }

    // XOR_A_A;
    // RET;
    return true;
}

static void InitSprites_InitSpritesByPriority(uint8_t c) {
    uint8_t* hl = wram->wObjectPriorities;

    while(1) {
        // LD_A_hli;
        // LD_D_A;
        // AND_A(0xf0);
        // RET_Z;
        uint8_t d = *(hl++);
        if((d & 0xf0) == 0)
            return;
        // CP_A_C;
        // IF_NZ goto next_sprite;
        if((d & 0xf0) != c)
            continue;
        
        // PUSH_BC;
        // PUSH_HL;
        // LD_A_D;
        // AND_A(0xf);
        // CALL(aInitSprites_GetObjectStructPointer);
        struct Object* ptr = InitSprites_GetObjectStructPointer(d & 0xf);
        // CALL(aInitSprites_InitSprite);
        InitSprites_InitSprite(ptr);
        // POP_HL;
        // POP_BC;
    }
}

void InitSprites(void) {
    // SET_PC(aInitSprites);
    // CALL(aInitSprites_DeterminePriorities);
    InitSprites_DeterminePriorities();
    // LD_C(PRIORITY_HIGH);
    // CALL(aInitSprites_InitSpritesByPriority);
    // LD_C(PRIORITY_NORM);
    // CALL(aInitSprites_InitSpritesByPriority);
    // LD_C(PRIORITY_LOW);
    // CALL(aInitSprites_InitSpritesByPriority);
    InitSprites_InitSpritesByPriority(PRIORITY_HIGH);
    InitSprites_InitSpritesByPriority(PRIORITY_NORM);
    InitSprites_InitSpritesByPriority(PRIORITY_LOW);
    // RET;
/* Currently not used?
Addresses:

    // dw ['wPlayerStruct'];
    // dw ['wObject1Struct'];
    // dw ['wObject2Struct'];
    // dw ['wObject3Struct'];
    // dw ['wObject4Struct'];
    // dw ['wObject5Struct'];
    // dw ['wObject6Struct'];
    // dw ['wObject7Struct'];
    // dw ['wObject8Struct'];
    // dw ['wObject9Struct'];
    // dw ['wObject10Struct'];
    // dw ['wObject11Struct'];
    // dw ['wObject12Struct'];
*/
}
