#include "../constants.h"
#include "battle_vars.h"

static const uint16_t BattleVarLocations[] = {
    [PLAYER_SUBSTATUS_1]    = wPlayerSubStatus1,           [ENEMY_SUBSTATUS_1]    = wEnemySubStatus1,
    [PLAYER_SUBSTATUS_2]    = wPlayerSubStatus2,           [ENEMY_SUBSTATUS_2]    = wEnemySubStatus2,
    [PLAYER_SUBSTATUS_3]    = wPlayerSubStatus3,           [ENEMY_SUBSTATUS_3]    = wEnemySubStatus3,
    [PLAYER_SUBSTATUS_4]    = wPlayerSubStatus4,           [ENEMY_SUBSTATUS_4]    = wEnemySubStatus4,
    [PLAYER_SUBSTATUS_5]    = wPlayerSubStatus5,           [ENEMY_SUBSTATUS_5]    = wEnemySubStatus5,
    [PLAYER_STATUS]         = wBattleMonStatus,            [ENEMY_STATUS]         = wEnemyMonStatus,
    [PLAYER_MOVE_ANIMATION] = wPlayerMoveStructAnimation,  [ENEMY_MOVE_ANIMATION] = wEnemyMoveStructAnimation,
    [PLAYER_MOVE_EFFECT]    = wPlayerMoveStructEffect,     [ENEMY_MOVE_EFFECT]    = wEnemyMoveStructEffect,
    [PLAYER_MOVE_POWER]     = wPlayerMoveStructPower,      [ENEMY_MOVE_POWER]     = wEnemyMoveStructPower,
    [PLAYER_MOVE_TYPE]      = wPlayerMoveStructType,       [ENEMY_MOVE_TYPE]      = wEnemyMoveStructType,
    [PLAYER_CUR_MOVE]       = wCurPlayerMove,              [ENEMY_CUR_MOVE]       = wCurEnemyMove,
    [PLAYER_COUNTER_MOVE]   = wLastPlayerCounterMove,      [ENEMY_COUNTER_MOVE]   = wLastEnemyCounterMove,
    [PLAYER_LAST_MOVE]      = wLastPlayerMove,             [ENEMY_LAST_MOVE]      = wLastEnemyMove
};

static const uint8_t BattleVarPairs[][2] = {
    [BATTLE_VARS_SUBSTATUS1]     = {PLAYER_SUBSTATUS_1,    ENEMY_SUBSTATUS_1},
    [BATTLE_VARS_SUBSTATUS2]     = {PLAYER_SUBSTATUS_2,    ENEMY_SUBSTATUS_2},
    [BATTLE_VARS_SUBSTATUS3]     = {PLAYER_SUBSTATUS_3,    ENEMY_SUBSTATUS_3},
    [BATTLE_VARS_SUBSTATUS4]     = {PLAYER_SUBSTATUS_4,    ENEMY_SUBSTATUS_4},
    [BATTLE_VARS_SUBSTATUS5]     = {PLAYER_SUBSTATUS_5,    ENEMY_SUBSTATUS_5},
    [BATTLE_VARS_SUBSTATUS1_OPP] = {ENEMY_SUBSTATUS_1,     PLAYER_SUBSTATUS_1},
    [BATTLE_VARS_SUBSTATUS2_OPP] = {ENEMY_SUBSTATUS_2,     PLAYER_SUBSTATUS_2},
    [BATTLE_VARS_SUBSTATUS3_OPP] = {ENEMY_SUBSTATUS_3,     PLAYER_SUBSTATUS_3},
    [BATTLE_VARS_SUBSTATUS4_OPP] = {ENEMY_SUBSTATUS_4,     PLAYER_SUBSTATUS_4},
    [BATTLE_VARS_SUBSTATUS5_OPP] = {ENEMY_SUBSTATUS_5,     PLAYER_SUBSTATUS_5},
    [BATTLE_VARS_STATUS]         = {PLAYER_STATUS,         ENEMY_STATUS},
};

void GetBattleVar(void){
        PUSH_HL;
    CALL(aGetBattleVarAddr);
    POP_HL;
    RET;

}

uint8_t GetBattleVar_Conv(uint8_t a){
    //     PUSH_HL;
    // CALL(aGetBattleVarAddr);
    // POP_HL;
    // RET;
    return GetBattleVarAddr_Conv(a);
}

void GetBattleVarAddr(void){
    //  Get variable from pair a, depending on whose turn it is.
//  There are 21 variable pairs.
    PUSH_BC;

    LD_HL(mBattleVarPairs);
    LD_C_A;
    LD_B(0);
    ADD_HL_BC;
    ADD_HL_BC;

    LD_A_hli;
    LD_H_hl;
    LD_L_A;

//  Enemy turn uses the second byte instead.
//  This lets battle variable calls be side-neutral.
    LDH_A_addr(hBattleTurn);
    AND_A_A;
    IF_Z goto getvar;
    INC_HL;


getvar:
    //  var id
    LD_A_hl;
    LD_C_A;
    LD_B(0);

    LD_HL(mBattleVarLocations);
    ADD_HL_BC;
    ADD_HL_BC;

    LD_A_hli;
    LD_H_hl;
    LD_L_A;

    LD_A_hl;

    POP_BC;
    RET;

}

uint8_t GetBattleVarAddr_Conv(uint8_t a){
    //  Get variable from pair a, depending on whose turn it is.
    //  There are 21 variable pairs.
    // PUSH_BC;

    // LD_HL(mBattleVarPairs);
    // LD_C_A;
    // LD_B(0);
    // ADD_HL_BC;
    // ADD_HL_BC;

    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;

//  Enemy turn uses the second byte instead.
//  This lets battle variable calls be side-neutral.
    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // IF_Z goto getvar;
    // INC_HL;


getvar:
    //  var id
    // LD_A_hl;
    // LD_C_A;
    // LD_B(0);
    uint8_t id = BattleVarPairs[a][(hram->hBattleTurn == 0)? 0: 1];

    // LD_HL(mBattleVarLocations);
    // ADD_HL_BC;
    // ADD_HL_BC;

    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    uint16_t loc = BattleVarLocations[id];

    // LD_A_hl;
    a = gb_read(loc);

    // POP_BC;
    // RET;
    return a;
}

// void BattleVarPairs(void){
//     //  entries correspond to BATTLE_VARS_* constants
//     //table_width ['2', 'BattleVarPairs']
//     //dw ['.Substatus1'];
//     //dw ['.Substatus2'];
//     //dw ['.Substatus3'];
//     //dw ['.Substatus4'];
//     //dw ['.Substatus5'];
//     //dw ['.Substatus1Opp'];
//     //dw ['.Substatus2Opp'];
//     //dw ['.Substatus3Opp'];
//     //dw ['.Substatus4Opp'];
//     //dw ['.Substatus5Opp'];
//     //dw ['.Status'];
//     //dw ['.StatusOpp'];
//     //dw ['.MoveAnim'];
//     //dw ['.MoveEffect'];
//     //dw ['.MovePower'];
//     //dw ['.MoveType'];
//     //dw ['.CurMove'];
//     //dw ['.LastCounter'];
//     //dw ['.LastCounterOpp'];
//     //dw ['.LastMove'];
//     //dw ['.LastMoveOpp'];
//     //assert_table_length ['NUM_BATTLE_VARS']

// //                    player                 enemy

// Substatus1:
// //     db PLAYER_SUBSTATUS_1,    ENEMY_SUBSTATUS_1
    
// Substatus1Opp:
// //  db ENEMY_SUBSTATUS_1,     PLAYER_SUBSTATUS_1
    
// Substatus2:
// //     db PLAYER_SUBSTATUS_2,    ENEMY_SUBSTATUS_2
    
// Substatus2Opp:
// //  db ENEMY_SUBSTATUS_2,     PLAYER_SUBSTATUS_2
    
// Substatus3:
// //     db PLAYER_SUBSTATUS_3,    ENEMY_SUBSTATUS_3
    
// Substatus3Opp:
// //  db ENEMY_SUBSTATUS_3,     PLAYER_SUBSTATUS_3
    
// Substatus4:
// //     db PLAYER_SUBSTATUS_4,    ENEMY_SUBSTATUS_4
    
// Substatus4Opp:
// //  db ENEMY_SUBSTATUS_4,     PLAYER_SUBSTATUS_4
    
// Substatus5:
// //     db PLAYER_SUBSTATUS_5,    ENEMY_SUBSTATUS_5
    
// Substatus5Opp:
// //  db ENEMY_SUBSTATUS_5,     PLAYER_SUBSTATUS_5
    
// Status:
// //         db PLAYER_STATUS,         ENEMY_STATUS
    
// StatusOpp:
// //      db ENEMY_STATUS,          PLAYER_STATUS
    
// MoveAnim:
// //       db PLAYER_MOVE_ANIMATION, ENEMY_MOVE_ANIMATION
    
// MoveEffect:
// //     db PLAYER_MOVE_EFFECT,    ENEMY_MOVE_EFFECT
    
// MovePower:
// //      db PLAYER_MOVE_POWER,     ENEMY_MOVE_POWER
    
// MoveType:
// //       db PLAYER_MOVE_TYPE,      ENEMY_MOVE_TYPE
    
// CurMove:
// //        db PLAYER_CUR_MOVE,       ENEMY_CUR_MOVE
    
// LastCounter:
// //    db PLAYER_COUNTER_MOVE,   ENEMY_COUNTER_MOVE
    
// LastCounterOpp:
// // db ENEMY_COUNTER_MOVE,    PLAYER_COUNTER_MOVE
    
// LastMove:
// //       db PLAYER_LAST_MOVE,      ENEMY_LAST_MOVE
    
// LastMoveOpp:
// //    db ENEMY_LAST_MOVE,       PLAYER_LAST_MOVE
    
//     return BattleVarLocations();
// }

// void BattleVarLocations(void){
//     //  entries correspond to PLAYER_* and ENEMY_* constants
//     //table_width ['2 + 2', 'BattleVarLocations']
//     //dw ['wPlayerSubStatus1', 'wEnemySubStatus1'];
//     //dw ['wPlayerSubStatus2', 'wEnemySubStatus2'];
//     //dw ['wPlayerSubStatus3', 'wEnemySubStatus3'];
//     //dw ['wPlayerSubStatus4', 'wEnemySubStatus4'];
//     //dw ['wPlayerSubStatus5', 'wEnemySubStatus5'];
//     //dw ['wBattleMonStatus', 'wEnemyMonStatus'];
//     //dw ['wPlayerMoveStructAnimation', 'wEnemyMoveStructAnimation'];
//     //dw ['wPlayerMoveStructEffect', 'wEnemyMoveStructEffect'];
//     //dw ['wPlayerMoveStructPower', 'wEnemyMoveStructPower'];
//     //dw ['wPlayerMoveStructType', 'wEnemyMoveStructType'];
//     //dw ['wCurPlayerMove', 'wCurEnemyMove'];
//     //dw ['wLastPlayerCounterMove', 'wLastEnemyCounterMove'];
//     //dw ['wLastPlayerMove', 'wLastEnemyMove'];
//     //assert_table_length ['NUM_BATTLE_VAR_LOCATION_PAIRS']

// }
