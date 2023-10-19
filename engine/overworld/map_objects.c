#include "../../constants.h"
#include "map_objects.h"
#include "../../home/copy.h"
#include "../../home/map_objects.h"
#include "../../home/menu.h"
#include "../../home/map.h"
#include "player_object.h"
#include "movement.h"
#include "../../data/sprites/facings.h"

uint8_t (*gMovementPointer)(void);

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
    // RRCA;
    // RRCA;
    // ADD_A(FACING_WEIRD_TREE_0);
    // LD_HL(OBJECT_FACING_STEP);
    // ADD_HL_BC;
    // LD_hl_A;
    // RET;
    bc->facingStep = ((bc->stepFrame & (3 << 2)) >> 2) + FACING_WEIRD_TREE_0;
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
    ByteFill_Conv((obj - wram->wObjectStruct) + wObjectStructs, OBJECT_LENGTH, 0);
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
    GetMapObject_Conv(a)->sprite = 0xff;

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
    // uint16_t ptr = gb_read(de + (action * 4));
    // CALL(av_hl_);
    // REG_BC = bc;
    // CALL(ptr);
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

void ObjectMovementByte_IncAnonJumptableIndex(void) {
    SET_PC(aObjectMovementByte_IncAnonJumptableIndex);
    LD_HL(OBJECT_MOVEMENT_BYTE_INDEX);
    ADD_HL_BC;
    INC_hl;
    RET;
}

void ObjectMovementByte_DecAnonJumptableIndex(void) {
    SET_PC(aObjectMovementByte_DecAnonJumptableIndex);
    LD_HL(OBJECT_MOVEMENT_BYTE_INDEX);
    ADD_HL_BC;
    DEC_hl;
    RET;
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

void Field1c_ZeroAnonJumptableIndex(void) {
    SET_PC(aField1c_ZeroAnonJumptableIndex);
    LD_HL(OBJECT_1C);
    ADD_HL_BC;
    LD_hl(0);
    RET;
}

void Field1c_IncAnonJumptableIndex(void) {
    SET_PC(aField1c_IncAnonJumptableIndex);
    LD_HL(OBJECT_1C);
    ADD_HL_BC;
    INC_hl;
    RET;
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

void StepFunction_FromMovement(void) {
    SET_PC(aStepFunction_FromMovement);
    CALL(aField1c_ZeroAnonJumptableIndex);
    CALL(aGetSpriteMovementFunction);
    LD_A_hl;
    LD_HL(mStepFunction_FromMovement_Pointers);
    RST(aJumpTable);
    RET;

Pointers:

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

    return MovementFunction_Null();
}

void MovementFunction_Null(void) {
    SET_PC(aMovementFunction_Null);
    RET;
}

void MovementFunction_RandomWalkY(void) {
    SET_PC(aMovementFunction_RandomWalkY);
    CALL(aRandom);
    LDH_A_addr(hRandomAdd);
    AND_A(0b00000001);
    JP(mv_RandomWalkContinue);
}

void MovementFunction_RandomWalkX(void) {
    SET_PC(aMovementFunction_RandomWalkX);
    CALL(aRandom);
    LDH_A_addr(hRandomAdd);
    AND_A(0b00000001);
    OR_A(0b00000010);
    JP(mv_RandomWalkContinue);
}

void MovementFunction_RandomWalkXY(void) {
    SET_PC(aMovementFunction_RandomWalkXY);
    CALL(aRandom);
    LDH_A_addr(hRandomAdd);
    AND_A(0b00000011);
    JP(mv_RandomWalkContinue);
}

void MovementFunction_RandomSpinSlow(void) {
    SET_PC(aMovementFunction_RandomSpinSlow);
    CALL(aRandom);
    LDH_A_addr(hRandomAdd);
    AND_A(0b00001100);
    LD_HL(OBJECT_FACING);
    ADD_HL_BC;
    LD_hl_A;
    JP(mRandomStepDuration_Slow);
}

void MovementFunction_RandomSpinFast(void) {
    SET_PC(aMovementFunction_RandomSpinFast);
    LD_HL(OBJECT_FACING);
    ADD_HL_BC;
    LD_A_hl;
    AND_A(0b00001100);
    LD_D_A;
    CALL(aRandom);
    LDH_A_addr(hRandomAdd);
    AND_A(0b00001100);
    CP_A_D;
    IF_NZ goto keep;
    XOR_A(0b00001100);

keep:

    LD_hl_A;
    JP(mRandomStepDuration_Fast);
}

void MovementFunction_Standing(void) {
    SET_PC(aMovementFunction_Standing);
    CALL(aCopyStandingCoordsTileToNextCoordsTile);
    CALL(aEndSpriteMovement);
    LD_HL(OBJECT_ACTION);
    ADD_HL_BC;
    LD_hl(OBJECT_ACTION_STAND);
    LD_HL(OBJECT_STEP_TYPE);
    ADD_HL_BC;
    LD_hl(STEP_TYPE_RESTORE);
    RET;
}

void MovementFunction_ObeyDPad(void) {
    SET_PC(aMovementFunction_ObeyDPad);
    LD_HL(mGetPlayerNextMovementByte);
    JP(mHandleMovementData);
}

void MovementFunction_Indexed1(void) {
    SET_PC(aMovementFunction_Indexed1);
    LD_HL(mGetIndexedMovementByte1);
    JP(mHandleMovementData);
}

void MovementFunction_Indexed2(void) {
    SET_PC(aMovementFunction_Indexed2);
    LD_HL(mGetIndexedMovementByte2);
    JP(mHandleMovementData);
}

void MovementFunction_0a(void) {
    SET_PC(aMovementFunction_0a);
    JP(mv_GetMovementObject);
}

void MovementFunction_0b(void) {
    SET_PC(aMovementFunction_0b);
    JP(mv_GetMovementObject);
}

void MovementFunction_0c(void) {
    SET_PC(aMovementFunction_0c);
    JP(mv_GetMovementObject);
}

void MovementFunction_0d(void) {
    SET_PC(aMovementFunction_0d);
    LD_HL(mGetPlayerNextMovementByte);
    JP(mHandleMovementData);
}

void MovementFunction_0e(void) {
    SET_PC(aMovementFunction_0e);
    JP(mv_GetMovementObject);
}

void MovementFunction_Follow(void) {
    SET_PC(aMovementFunction_Follow);
    LD_HL(mGetFollowerNextMovementByte);
    JP(mHandleMovementData);
}

void MovementFunction_Script(void) {
    SET_PC(aMovementFunction_Script);
    LD_HL(mGetMovementByte);
    JP(mHandleMovementData);
}

void MovementFunction_Strength(void) {
    SET_PC(aMovementFunction_Strength);
    CALL(aObjectMovementByte_AnonJumptable);

anon_dw:

    if (REG_A == 0) goto start;
    if (REG_A == 1) goto stop;

start:

    LD_HL(OBJECT_NEXT_TILE);
    ADD_HL_BC;
    LD_A_hl;
    CALL(aCheckPitTile);
    IF_Z goto on_pit;
    LD_HL(OBJECT_FLAGS2);
    ADD_HL_BC;
    BIT_hl(OBJ_FLAGS2_2);
    RES_hl(OBJ_FLAGS2_2);
    IF_Z goto ok;
    LD_HL(OBJECT_RANGE);
    ADD_HL_BC;
    LD_A_hl;
    AND_A(0b00000011);
    OR_A(0);
    CALL(aInitStep);
    CALL(aCanObjectMoveInDirection);
    IF_C goto ok2;
    LD_DE(SFX_STRENGTH);
    CALL(aPlaySFX);
    CALL(aSpawnStrengthBoulderDust);
    CALL(aUpdateTallGrassFlags);
    LD_HL(OBJECT_STEP_TYPE);
    ADD_HL_BC;
    LD_hl(STEP_TYPE_STRENGTH_BOULDER);
    RET;

ok2:

    CALL(aCopyStandingCoordsTileToNextCoordsTile);

ok:

    LD_HL(OBJECT_DIRECTION_WALKING);
    ADD_HL_BC;
    LD_hl(STANDING);
    RET;

on_pit:

    CALL(aObjectMovementByte_IncAnonJumptableIndex);

stop:

    LD_HL(OBJECT_DIRECTION_WALKING);
    ADD_HL_BC;
    LD_hl(STANDING);
    RET;
}

void MovementFunction_FollowNotExact(void) {
    SET_PC(aMovementFunction_FollowNotExact);
    LD_HL(OBJECT_NEXT_MAP_X);
    ADD_HL_BC;
    LD_D_hl;
    LD_HL(OBJECT_NEXT_MAP_Y);
    ADD_HL_BC;
    LD_E_hl;
    LD_HL(OBJECT_RANGE);
    ADD_HL_BC;
    LD_A_hl;
    PUSH_BC;
    CALL(aGetObjectStruct);
    LD_HL(OBJECT_DIRECTION_WALKING);
    ADD_HL_BC;
    LD_A_hl;
    CP_A(STANDING);
    IF_Z goto standing;
    LD_HL(OBJECT_MAP_X);
    ADD_HL_BC;
    LD_A_hl;
    CP_A_D;
    IF_Z goto equal;
    IF_C goto less;
    LD_A(3);
    goto done;

less:

    LD_A(2);
    goto done;

equal:

    LD_HL(OBJECT_MAP_Y);
    ADD_HL_BC;
    LD_A_hl;
    CP_A_E;
    IF_Z goto standing;
    IF_C goto less2;
    LD_A(0);
    goto done;

less2:

    LD_A(1);

done:

    LD_D_A;
    LD_HL(OBJECT_DIRECTION_WALKING);
    ADD_HL_BC;
    LD_A_hl;
    AND_A(0b00001100);
    OR_A_D;
    POP_BC;
    JP(mNormalStep);

standing:

    POP_BC;
    LD_HL(OBJECT_DIRECTION_WALKING);
    ADD_HL_BC;
    LD_hl(STANDING);
    LD_HL(OBJECT_ACTION);
    ADD_HL_BC;
    LD_hl(OBJECT_ACTION_STAND);
    RET;
}

void MovementFunction_BigStanding(void) {
    SET_PC(aMovementFunction_BigStanding);
    CALL(aEndSpriteMovement);
    LD_HL(OBJECT_DIRECTION_WALKING);
    ADD_HL_BC;
    LD_hl(STANDING);
    LD_HL(OBJECT_ACTION);
    ADD_HL_BC;
    LD_hl(OBJECT_ACTION_BIG_DOLL_SYM);
    LD_HL(OBJECT_STEP_TYPE);
    ADD_HL_BC;
    LD_hl(STEP_TYPE_STANDING);
    RET;
}

void MovementFunction_Bouncing(void) {
    SET_PC(aMovementFunction_Bouncing);
    CALL(aEndSpriteMovement);
    LD_HL(OBJECT_DIRECTION_WALKING);
    ADD_HL_BC;
    LD_hl(STANDING);
    LD_HL(OBJECT_ACTION);
    ADD_HL_BC;
    LD_hl(OBJECT_ACTION_BOUNCE);
    LD_HL(OBJECT_STEP_TYPE);
    ADD_HL_BC;
    LD_hl(STEP_TYPE_STANDING);
    RET;
}

void MovementFunction_SpinCounterclockwise(void) {
    SET_PC(aMovementFunction_SpinCounterclockwise);
    CALL(aObjectMovementByte_AnonJumptable);

anon_dw:

    // dw ['_MovementSpinInit'];
    // dw ['_MovementSpinRepeat'];
    // dw ['_MovementSpinTurnLeft'];

    return MovementFunction_SpinClockwise();
}

void MovementFunction_SpinClockwise(void) {
    SET_PC(aMovementFunction_SpinClockwise);
    CALL(aObjectMovementByte_AnonJumptable);

anon_dw:

    // dw ['_MovementSpinInit'];
    // dw ['_MovementSpinRepeat'];
    // dw ['_MovementSpinTurnRight'];

    return v_MovementSpinInit();
}

void v_MovementSpinInit(void) {
    SET_PC(av_MovementSpinInit);
    CALL(aEndSpriteMovement);
    CALL(aObjectMovementByte_IncAnonJumptableIndex);
    // fallthrough

    return v_MovementSpinRepeat();
}

void v_MovementSpinRepeat(void) {
    SET_PC(av_MovementSpinRepeat);
    LD_HL(OBJECT_ACTION);
    ADD_HL_BC;
    LD_hl(OBJECT_ACTION_STAND);
    LD_HL(OBJECT_RANGE);
    ADD_HL_BC;
    LD_A_hl;
    LD_A(0x10);
    LD_HL(OBJECT_STEP_DURATION);
    ADD_HL_BC;
    LD_hl_A;
    LD_HL(OBJECT_STEP_TYPE);
    ADD_HL_BC;
    LD_hl(STEP_TYPE_SLEEP);
    CALL(aObjectMovementByte_IncAnonJumptableIndex);
    RET;
}

void v_MovementSpinTurnLeft(void) {
    SET_PC(av_MovementSpinTurnLeft);
    LD_DE(mv_MovementSpinTurnLeft_facings_counterclockwise);
    CALL(av_MovementSpinNextFacing);
    JR(mMovementFunction_SpinCounterclockwise);

facings_counterclockwise:

    // db ['OW_RIGHT'];
    // db ['OW_LEFT'];
    // db ['OW_DOWN'];
    // db ['OW_UP'];

    return v_MovementSpinTurnRight();
}

void v_MovementSpinTurnRight(void) {
    SET_PC(av_MovementSpinTurnRight);
    LD_DE(mv_MovementSpinTurnRight_facings_clockwise);
    CALL(av_MovementSpinNextFacing);
    JR(mMovementFunction_SpinClockwise);

facings_clockwise:

    // db ['OW_LEFT'];
    // db ['OW_RIGHT'];
    // db ['OW_UP'];
    // db ['OW_DOWN'];

    return v_MovementSpinNextFacing();
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

void MovementFunction_Shadow(void) {
    SET_PC(aMovementFunction_Shadow);
    CALL(aInitMovementField1dField1e);
    LD_HL(OBJECT_ACTION);
    ADD_HL_BC;
    LD_hl(OBJECT_ACTION_SHADOW);
    LD_HL(OBJECT_STEP_DURATION);
    ADD_HL_DE;
    LD_A_hl;
    INC_A;
    ADD_A_A;
    ADD_A(0);
    LD_HL(OBJECT_STEP_DURATION);
    ADD_HL_BC;
    LD_hl_A;
    LD_HL(OBJECT_DIRECTION_WALKING);
    ADD_HL_DE;
    LD_A_hl;
    maskbits(NUM_DIRECTIONS, 0);
    LD_D(1 * 8 + 6);
    CP_A(DOWN);
    IF_Z goto ok;
    CP_A(UP);
    IF_Z goto ok;
    LD_D(1 * 8 + 4);

ok:

    LD_HL(OBJECT_SPRITE_Y_OFFSET);
    ADD_HL_BC;
    LD_hl_D;
    LD_HL(OBJECT_SPRITE_X_OFFSET);
    ADD_HL_BC;
    LD_hl(0);
    LD_HL(OBJECT_STEP_TYPE);
    ADD_HL_BC;
    LD_hl(STEP_TYPE_TRACKING_OBJECT);
    RET;
}

void MovementFunction_Emote(void) {
    SET_PC(aMovementFunction_Emote);
    CALL(aEndSpriteMovement);
    CALL(aInitMovementField1dField1e);
    LD_HL(OBJECT_ACTION);
    ADD_HL_BC;
    LD_hl(OBJECT_ACTION_EMOTE);
    LD_HL(OBJECT_STEP_DURATION);
    ADD_HL_BC;
    LD_hl(0);
    LD_HL(OBJECT_SPRITE_Y_OFFSET);
    ADD_HL_BC;
    LD_hl(-2 * 8);
    LD_HL(OBJECT_SPRITE_X_OFFSET);
    ADD_HL_BC;
    LD_hl(0);
    LD_HL(OBJECT_STEP_TYPE);
    ADD_HL_BC;
    LD_hl(STEP_TYPE_TRACKING_OBJECT);
    RET;
}

void MovementFunction_BoulderDust(void) {
    SET_PC(aMovementFunction_BoulderDust);
    CALL(aEndSpriteMovement);
    CALL(aInitMovementField1dField1e);
    LD_HL(OBJECT_ACTION);
    ADD_HL_BC;
    LD_hl(OBJECT_ACTION_BOULDER_DUST);
    LD_HL(OBJECT_STEP_DURATION);
    ADD_HL_DE;
    LD_A_hl;
    INC_A;
    ADD_A_A;
    LD_HL(OBJECT_STEP_DURATION);
    ADD_HL_BC;
    LD_hl_A;
    LD_HL(OBJECT_DIRECTION_WALKING);
    ADD_HL_DE;
    LD_A_hl;
    AND_A(0b00000011);
    LD_E_A;
    LD_D(0);
    LD_HL(mMovementFunction_BoulderDust_dust_coords);
    ADD_HL_DE;
    ADD_HL_DE;
    LD_D_hl;
    INC_HL;
    LD_E_hl;
    LD_HL(OBJECT_SPRITE_X_OFFSET);
    ADD_HL_BC;
    LD_hl_D;
    LD_HL(OBJECT_SPRITE_Y_OFFSET);
    ADD_HL_BC;
    LD_hl_E;
    LD_HL(OBJECT_STEP_TYPE);
    ADD_HL_BC;
    LD_hl(STEP_TYPE_TRACKING_OBJECT);
    RET;

dust_coords:

    //   x,  y
    // db ['0', '-4'];
    // db ['0', '8'];
    // db ['6', '2'];
    // db ['-6', '2'];

    return MovementFunction_ShakingGrass();
}

void MovementFunction_ShakingGrass(void) {
    SET_PC(aMovementFunction_ShakingGrass);
    CALL(aEndSpriteMovement);
    CALL(aInitMovementField1dField1e);
    LD_HL(OBJECT_ACTION);
    ADD_HL_BC;
    LD_hl(OBJECT_ACTION_GRASS_SHAKE);
    LD_HL(OBJECT_STEP_DURATION);
    ADD_HL_DE;
    LD_A_hl;
    ADD_A(-1);
    LD_HL(OBJECT_STEP_DURATION);
    ADD_HL_BC;
    LD_hl_A;
    LD_HL(OBJECT_STEP_TYPE);
    ADD_HL_BC;
    LD_hl(STEP_TYPE_TRACKING_OBJECT);
    RET;
}

void InitMovementField1dField1e(void) {
    SET_PC(aInitMovementField1dField1e);
    LD_HL(OBJECT_RANGE);
    ADD_HL_BC;
    LD_A_hl;
    PUSH_BC;
    CALL(aGetObjectStruct);
    LD_D_B;
    LD_E_C;
    POP_BC;
    LD_HL(OBJECT_1D);
    ADD_HL_BC;
    LD_hl_E;
    INC_HL;
    LD_hl_D;
    RET;
}

void MovementFunction_ScreenShake(void) {
    SET_PC(aMovementFunction_ScreenShake);
    CALL(aEndSpriteMovement);
    LD_HL(OBJECT_ACTION);
    ADD_HL_BC;
    LD_hl(OBJECT_ACTION_00);
    LD_HL(OBJECT_RANGE);
    ADD_HL_BC;
    LD_A_hl;
    CALL(aMovementFunction_ScreenShake_GetDurationAndField1e);
    LD_HL(OBJECT_STEP_DURATION);
    ADD_HL_BC;
    LD_hl_E;
    LD_HL(OBJECT_1E);
    ADD_HL_BC;
    LD_hl_A;
    LD_HL(OBJECT_STEP_TYPE);
    ADD_HL_BC;
    LD_hl(STEP_TYPE_SCREENSHAKE);
    RET;

GetDurationAndField1e:

    LD_D_A;
    AND_A(0b00111111);
    LD_E_A;
    LD_A_D;
    RLCA;
    RLCA;
    AND_A(0b00000011);
    LD_D_A;
    INC_D;
    LD_A(1);

loop:

    DEC_D;
    RET_Z;
    ADD_A_A;
    goto loop;

    return v_RandomWalkContinue();
}

void v_RandomWalkContinue(void) {
    SET_PC(av_RandomWalkContinue);
    CALL(aInitStep);
    CALL(aCanObjectMoveInDirection);
    IF_C goto new_duration;
    CALL(aUpdateTallGrassFlags);
    LD_HL(OBJECT_ACTION);
    ADD_HL_BC;
    LD_hl(OBJECT_ACTION_STEP);
    LD_HL(wCenteredObject);
    LDH_A_addr(hMapObjectIndex);
    CP_A_hl;
    IF_Z goto centered;
    LD_HL(OBJECT_STEP_TYPE);
    ADD_HL_BC;
    LD_hl(STEP_TYPE_CONTINUE_WALK);
    RET;

centered:

    LD_HL(OBJECT_STEP_TYPE);
    ADD_HL_BC;
    LD_hl(STEP_TYPE_PLAYER_WALK);
    RET;

new_duration:

    CALL(aEndSpriteMovement);
    CALL(aCopyStandingCoordsTileToNextCoordsTile);
    // fallthrough

    return RandomStepDuration_Slow();
}

void RandomStepDuration_Slow(void) {
    SET_PC(aRandomStepDuration_Slow);
    CALL(aRandom);
    LDH_A_addr(hRandomAdd);
    AND_A(0b01111111);
    JR(mv_SetRandomStepDuration);
}

void RandomStepDuration_Fast(void) {
    SET_PC(aRandomStepDuration_Fast);
    CALL(aRandom);
    LDH_A_addr(hRandomAdd);
    AND_A(0b00011111);
    return v_SetRandomStepDuration();
}

void v_SetRandomStepDuration(void) {
    SET_PC(av_SetRandomStepDuration);
    LD_HL(OBJECT_STEP_DURATION);
    ADD_HL_BC;
    LD_hl_A;
    LD_HL(OBJECT_DIRECTION_WALKING);
    ADD_HL_BC;
    LD_hl(STANDING);
    LD_HL(OBJECT_ACTION);
    ADD_HL_BC;
    LD_hl(OBJECT_ACTION_STAND);
    LD_HL(OBJECT_STEP_TYPE);
    ADD_HL_BC;
    LD_hl(STEP_TYPE_SLEEP);
    RET;
}

void StepTypesJumptable(void) {
    SET_PC(aStepTypesJumptable);
    //  entries correspond to STEP_TYPE_* constants (see constants/map_object_constants.asm)
    // table_width ['2', 'StepTypesJumptable']
    // dw ['StepFunction_Reset'];  // 00
    // dw ['StepFunction_FromMovement'];  // 01
    // dw ['StepFunction_NPCWalk'];  // 02
    // dw ['StepFunction_Sleep'];  // 03
    // dw ['StepFunction_Standing'];  // 04
    // dw ['StepFunction_Restore'];  // 05
    // dw ['StepFunction_PlayerWalk'];  // 06
    // dw ['StepFunction_ContinueWalk'];  // 07
    // dw ['StepFunction_NPCJump'];  // 08
    // dw ['StepFunction_PlayerJump'];  // 09
    // dw ['StepFunction_Turn'];  // 0a
    // dw ['StepFunction_Bump'];  // 0b
    // dw ['StepFunction_TeleportFrom'];  // 0c
    // dw ['StepFunction_TeleportTo'];  // 0d
    // dw ['StepFunction_Skyfall'];  // 0e
    // dw ['StepFunction_StrengthBoulder'];  // 0f
    // dw ['StepFunction_GotBite'];  // 10
    // dw ['StepFunction_RockSmash'];  // 11
    // dw ['StepFunction_DigTo'];  // 12
    // dw ['StepFunction_TrackingObject'];  // 13
    // dw ['StepFunction_14'];  // 14
    // dw ['StepFunction_ScreenShake'];  // 15
    // dw ['StepFunction_16'];  // 16
    // dw ['StepFunction_17'];  // 17
    // dw ['StepFunction_Delete'];  // 18
    // dw ['StepFunction_SkyfallTop'];  // 19
    // assert_table_length ['NUM_STEP_TYPES']

    return WaitStep_InPlace();
}

void WaitStep_InPlace(void) {
    SET_PC(aWaitStep_InPlace);
    LD_HL(OBJECT_STEP_DURATION);
    ADD_HL_BC;
    DEC_hl;
    RET_NZ;
    LD_HL(OBJECT_STEP_TYPE);
    ADD_HL_BC;
    LD_hl(STEP_TYPE_FROM_MOVEMENT);
    RET;
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

void StepFunction_Standing(void) {
    SET_PC(aStepFunction_Standing);
    CALL(aStubbed_UpdateYOffset);
    LD_HL(OBJECT_DIRECTION_WALKING);
    ADD_HL_BC;
    LD_hl(STANDING);
    RET;
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

void StepFunction_14(void) {
    SET_PC(aStepFunction_14);
    return StepFunction_ScreenShake();
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

y_offsets:

    // db ['0', '-1', '-2', '-3', '-4', '-3', '-2', '-1'];

    return UpdateJumpPosition();
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

y_offsets:

    // db ['-4', '-6', '-8', '-10', '-11', '-12', '-12', '-12'];
    // db ['-11', '-10', '-9', '-8', '-6', '-4', '0', '0'];

    return GetPlayerNextMovementByte();
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

void GetMovementByte(void) {
    SET_PC(aGetMovementByte);
    LD_HL(wMovementDataBank);
    CALL(av_GetMovementByte);
    RET;
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

uint8_t GetMovementObject(void) {
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

void HandleMovementData_Conv(struct Object* bc, uint8_t (*hl)(void)) {
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
        uint8_t a = JumpMovementPointer_Conv();
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
    REG_A = JumpMovementPointer_Conv();
    RET;
}

uint8_t JumpMovementPointer_Conv(void) {
    return gMovementPointer();
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

void SpawnShadow(void) {
    SET_PC(aSpawnShadow);
    PUSH_BC;
    LD_DE(mSpawnShadow_ShadowObject);
    CALL(aCopyTempObjectData);
    CALL(aInitTempObject);
    POP_BC;
    RET;

ShadowObject:

    // vtile, palette, movement
    // db ['0x00', 'PAL_OW_SILVER', 'SPRITEMOVEDATA_SHADOW'];

    return SpawnStrengthBoulderDust();
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
    wram->wTempObjectCopySpriteVTile = *(de++);
    // LD_A_de;
    // INC_DE;
    // LD_hli_A;
    wram->wTempObjectCopyPalette = *(de++);
    // LD_A_de;
    // LD_hli_A;
    wram->wTempObjectCopyMovement = *(de++);
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
    uint8_t a = 0;
    struct Object* bc = &wram->wPlayerStruct;

// loop:

    do {
        // LDH_addr_A(hMapObjectIndex);
        hram->hMapObjectIndex = a;
        // CALL(aDoesObjectHaveASprite);
        // IF_Z goto ok;
        if(!DoesObjectHaveASprite_Conv(bc)) {
            // CALL(aUpdateObjectFrozen);
            UpdateObjectFrozen_Conv(bc);
        }
    // ok:
        // LD_HL(OBJECT_LENGTH);
        // ADD_HL_BC;
        // LD_B_H;
        // LD_C_L;
        bc++;
        // LDH_A_addr(hMapObjectIndex);
        a = hram->hMapObjectIndex;
        // INC_A;
        // CP_A(NUM_OBJECT_STRUCTS);
        // IF_NZ goto loop;
    } while(++a != NUM_OBJECT_STRUCTS);
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
        x = bc->spriteX << 3;
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
            y = bc->spriteY << 3;
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
                d &= 2;
                e &= 2;
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
    SET_PC(aHandleNPCStep);
    CALL(aResetStepVector);
    CALL(aDoStepsForAllObjects);
    RET;
}

void ResetStepVector(void) {
    SET_PC(aResetStepVector);
    XOR_A_A;
    LD_addr_A(wPlayerStepVectorX);
    LD_addr_A(wPlayerStepVectorY);
    LD_addr_A(wPlayerStepFlags);
    LD_A(STANDING);
    LD_addr_A(wPlayerStepDirection);
    RET;
}

void DoStepsForAllObjects(void) {
    SET_PC(aDoStepsForAllObjects);
    LD_BC(wObjectStructs);
    XOR_A_A;

loop:

    LDH_addr_A(hMapObjectIndex);
    CALL(aDoesObjectHaveASprite);
    IF_Z goto next;
    CALL(aHandleObjectStep);

next:

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

void RefreshPlayerSprite(void) {
    SET_PC(aRefreshPlayerSprite);
    LD_A(movement_step_sleep);
    LD_addr_A(wPlayerNextMovement);
    LD_addr_A(wPlayerMovement);
    XOR_A_A;
    LD_addr_A(wPlayerTurningDirection);
    LD_addr_A(wPlayerObjectStepFrame);
    CALL(aTryResetPlayerAction);
    FARCALL(aCheckWarpFacingDown);
    CALL_C(aSpawnInFacingDown);
    CALL(aSpawnInCustomFacing);
    RET;
}

void TryResetPlayerAction(void) {
    SET_PC(aTryResetPlayerAction);
    LD_HL(wPlayerSpriteSetupFlags);
    BIT_hl(PLAYERSPRITESETUP_RESET_ACTION_F);
    IF_NZ goto ok;
    RET;

ok:

    LD_A(OBJECT_ACTION_00);
    LD_addr_A(wPlayerAction);
    RET;
}

void SpawnInCustomFacing(void) {
    SET_PC(aSpawnInCustomFacing);
    LD_HL(wPlayerSpriteSetupFlags);
    BIT_hl(PLAYERSPRITESETUP_CUSTOM_FACING_F);
    RET_Z;
    LD_A_addr(wPlayerSpriteSetupFlags);
    AND_A(PLAYERSPRITESETUP_FACING_MASK);
    ADD_A_A;
    ADD_A_A;
    JR(mv_ContinueSpawnFacing);
}

void SpawnInFacingDown(void) {
    SET_PC(aSpawnInFacingDown);
    LD_A(DOWN);
    return v_ContinueSpawnFacing();
}

void v_ContinueSpawnFacing(void) {
    SET_PC(av_ContinueSpawnFacing);
    LD_BC(wPlayerStruct);
    CALL(aSetSpriteDirection);
    RET;
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

void SetLeaderIfVisible(void) {
    SET_PC(aSetLeaderIfVisible);
    CALL(aCheckObjectVisibility);
    RET_C;
    LDH_A_addr(hObjectStructIndex);
    LD_addr_A(wObjectFollow_Leader);
    RET;
}

void StopFollow(void) {
    SET_PC(aStopFollow);
    CALL(aResetLeader);
    CALL(aResetFollower);
    RET;
}

void ResetLeader(void) {
    SET_PC(aResetLeader);
    LD_A(-1);
    LD_addr_A(wObjectFollow_Leader);
    RET;
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
    if(!CheckObjectVisibility_Conv(c))
        return false;
    // PUSH_BC;
    // CALL(aFreezeAllObjects);
    FreezeAllObjects_Conv();
    // POP_BC;
    // LD_HL(OBJECT_FLAGS2);
    // ADD_HL_BC;
    // RES_hl(FROZEN_F);
    bit_reset((&wram->wPlayerStruct + c)->flags2, FROZEN_F);
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

void v_UpdateSprites(void) {
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
    if(sprite_idx >= b)
        return;
    
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
            if(((bc->flags2 >> (LOW_PRIORITY_F)) & 0x1)) {
                e = PRIORITY_LOW;
            }
            // BIT_hl(HIGH_PRIORITY_F);
            // IF_Z goto add;
            else if(!((bc->flags2 >> (HIGH_PRIORITY_F)) & 0x1)) {
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
            a = (bit_test(attr, ABSOLUTE_TILE_ID_F))? hram->hCurSpriteOAMFlags | attr: attr;

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
