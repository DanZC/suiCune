#include "../constants.h"
#include "trainers.h"

void CheckTrainerBattle(void){
        LDH_A_addr(hROMBank);
    PUSH_AF;

    CALL(aSwitchToMapScriptsBank);
    CALL(av_CheckTrainerBattle);

    POP_BC;
    LD_A_B;
    RST(aBankswitch);
    RET;

}

void v_CheckTrainerBattle(void){
    //  Check if any trainer on the map sees the player and wants to battle.

//  Skip the player object.
    LD_A(1);
    LD_DE(wMap1Object);


loop:
    
//  Start a battle if the object:
    PUSH_AF;
    PUSH_DE;

//  Has a sprite
    LD_HL(MAPOBJECT_SPRITE);
    ADD_HL_DE;
    LD_A_hl;
    AND_A_A;
    IF_Z goto next;

//  Is a trainer
    LD_HL(MAPOBJECT_COLOR);
    ADD_HL_DE;
    LD_A_hl;
    AND_A(0xf);
    CP_A(OBJECTTYPE_TRAINER);
    IF_NZ goto next;

//  Is visible on the map
    LD_HL(MAPOBJECT_OBJECT_STRUCT_ID);
    ADD_HL_DE;
    LD_A_hl;
    CP_A(-1);
    IF_Z goto next;

//  Is facing the player...
    CALL(aGetObjectStruct);
    CALL(aFacingPlayerDistance_bc);
    IF_NC goto next;

//  ...within their sight range
    LD_HL(MAPOBJECT_RANGE);
    ADD_HL_DE;
    LD_A_hl;
    CP_A_B;
    IF_C goto next;

//  And hasn't already been beaten
    PUSH_BC;
    PUSH_DE;
    LD_HL(MAPOBJECT_SCRIPT_POINTER);
    ADD_HL_DE;
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    LD_E_hl;
    INC_HL;
    LD_D_hl;
    LD_B(CHECK_FLAG);
    CALL(aEventFlagAction);
    LD_A_C;
    POP_DE;
    POP_BC;
    AND_A_A;
    IF_Z goto startbattle;


next:
        POP_DE;
    LD_HL(MAPOBJECT_LENGTH);
    ADD_HL_DE;
    LD_D_H;
    LD_E_L;

    POP_AF;
    INC_A;
    CP_A(NUM_OBJECTS);
    IF_NZ goto loop;
    XOR_A_A;
    RET;


startbattle:
        POP_DE;
    POP_AF;
    LDH_addr_A(hLastTalked);
    LD_A_B;
    LD_addr_A(wSeenTrainerDistance);
    LD_A_C;
    LD_addr_A(wSeenTrainerDirection);
    JR(mLoadTrainer_continue);

}

void TalkToTrainer(void){
        LD_A(1);
    LD_addr_A(wSeenTrainerDistance);
    LD_A(-1);
    LD_addr_A(wSeenTrainerDirection);

    return LoadTrainer_continue();
}

void LoadTrainer_continue(void){
        CALL(aGetMapScriptsBank);
    LD_addr_A(wSeenTrainerBank);

    LDH_A_addr(hLastTalked);
    CALL(aGetMapObject);

    LD_HL(MAPOBJECT_SCRIPT_POINTER);
    ADD_HL_BC;
    LD_A_addr(wSeenTrainerBank);
    CALL(aGetFarWord);
    LD_DE(wTempTrainer);
    LD_BC(wTempTrainerEnd - wTempTrainer);
    LD_A_addr(wSeenTrainerBank);
    CALL(aFarCopyBytes);
    XOR_A_A;
    LD_addr_A(wRunningTrainerBattleScript);
    SCF;
    RET;

}

void FacingPlayerDistance_bc(void){
        PUSH_DE;
    CALL(aFacingPlayerDistance);
    LD_B_D;
    LD_C_E;
    POP_DE;
    RET;

}

void FacingPlayerDistance(void){
    //  Return carry if the sprite at bc is facing the player,
//  its distance in d, and its direction in e.

    LD_HL(OBJECT_NEXT_MAP_X);  // x
    ADD_HL_BC;
    LD_D_hl;

    LD_HL(OBJECT_NEXT_MAP_Y);  // y
    ADD_HL_BC;
    LD_E_hl;

    LD_A_addr(wPlayerStandingMapX);
    CP_A_D;
    IF_Z goto CheckY;

    LD_A_addr(wPlayerStandingMapY);
    CP_A_E;
    IF_Z goto CheckX;

    AND_A_A;
    RET;


CheckY:
        LD_A_addr(wPlayerStandingMapY);
    SUB_A_E;
    IF_Z goto NotFacing;
    IF_NC goto Above;

//  Below
    CPL;
    INC_A;
    LD_D_A;
    LD_E(OW_UP);
    goto CheckFacing;


Above:
        LD_D_A;
    LD_E(OW_DOWN);
    goto CheckFacing;


CheckX:
        LD_A_addr(wPlayerStandingMapX);
    SUB_A_D;
    IF_Z goto NotFacing;
    IF_NC goto Left;

//  Right
    CPL;
    INC_A;
    LD_D_A;
    LD_E(OW_LEFT);
    goto CheckFacing;


Left:
        LD_D_A;
    LD_E(OW_RIGHT);


CheckFacing:
        CALL(aGetSpriteDirection);
    CP_A_E;
    IF_NZ goto NotFacing;
    SCF;
    RET;


NotFacing:
        AND_A_A;
    RET;

}

void CheckTrainerFlag(void){
    //  //  unreferenced
    PUSH_BC;
    LD_HL(OBJECT_MAP_OBJECT_INDEX);
    ADD_HL_BC;
    LD_A_hl;
    CALL(aGetMapObject);
    LD_HL(MAPOBJECT_SCRIPT_POINTER);
    ADD_HL_BC;
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    CALL(aGetMapScriptsBank);
    CALL(aGetFarWord);
    LD_D_H;
    LD_E_L;
    PUSH_DE;
    LD_B(CHECK_FLAG);
    CALL(aEventFlagAction);
    POP_DE;
    LD_A_C;
    AND_A_A;
    POP_BC;
    RET;

}

void PrintWinLossText(void){
        LD_A_addr(wBattleType);
    CP_A(BATTLETYPE_CANLOSE);
// code was probably dummied out here
    goto canlose;

//  unused
    LD_HL(wWinTextPointer);
    goto ok;


canlose:
        LD_A_addr(wBattleResult);
    LD_HL(wWinTextPointer);
    AND_A(0xf);  // WIN?
    IF_Z goto ok;
    LD_HL(wLossTextPointer);


ok:
        LD_A_hli;
    LD_H_hl;
    LD_L_A;
    CALL(aGetMapScriptsBank);
    CALL(aFarPrintText);
    CALL(aWaitBGMap);
    CALL(aWaitPressAorB_BlinkCursor);
    RET;

}
