#include "../constants.h"
#include "battle_vars.h"

static uint8_t* BattleVarLocations[] = {
    [PLAYER_SUBSTATUS_1]    = wram_ptr(wPlayerSubStatus1),           [ENEMY_SUBSTATUS_1]    = wram_ptr(wEnemySubStatus1),
    [PLAYER_SUBSTATUS_2]    = wram_ptr(wPlayerSubStatus2),           [ENEMY_SUBSTATUS_2]    = wram_ptr(wEnemySubStatus2),
    [PLAYER_SUBSTATUS_3]    = wram_ptr(wPlayerSubStatus3),           [ENEMY_SUBSTATUS_3]    = wram_ptr(wEnemySubStatus3),
    [PLAYER_SUBSTATUS_4]    = wram_ptr(wPlayerSubStatus4),           [ENEMY_SUBSTATUS_4]    = wram_ptr(wEnemySubStatus4),
    [PLAYER_SUBSTATUS_5]    = wram_ptr(wPlayerSubStatus5),           [ENEMY_SUBSTATUS_5]    = wram_ptr(wEnemySubStatus5),
    [PLAYER_STATUS]         = wram_ptr(wBattleMonStatus),            [ENEMY_STATUS]         = wram_ptr(wEnemyMonStatus),
    [PLAYER_MOVE_ANIMATION] = wram_ptr(wPlayerMoveStructAnimation),  [ENEMY_MOVE_ANIMATION] = wram_ptr(wEnemyMoveStructAnimation),
    [PLAYER_MOVE_EFFECT]    = wram_ptr(wPlayerMoveStructEffect),     [ENEMY_MOVE_EFFECT]    = wram_ptr(wEnemyMoveStructEffect),
    [PLAYER_MOVE_POWER]     = wram_ptr(wPlayerMoveStructPower),      [ENEMY_MOVE_POWER]     = wram_ptr(wEnemyMoveStructPower),
    [PLAYER_MOVE_TYPE]      = wram_ptr(wPlayerMoveStructType),       [ENEMY_MOVE_TYPE]      = wram_ptr(wEnemyMoveStructType),
    [PLAYER_CUR_MOVE]       = wram_ptr(wCurPlayerMove),              [ENEMY_CUR_MOVE]       = wram_ptr(wCurEnemyMove),
    [PLAYER_COUNTER_MOVE]   = wram_ptr(wLastPlayerCounterMove),      [ENEMY_COUNTER_MOVE]   = wram_ptr(wLastEnemyCounterMove),
    [PLAYER_LAST_MOVE]      = wram_ptr(wLastPlayerMove),             [ENEMY_LAST_MOVE]      = wram_ptr(wLastEnemyMove),
};

static const uint8_t BattleVarPairs[][2] = {
    [BATTLE_VARS_SUBSTATUS1]            = {PLAYER_SUBSTATUS_1,    ENEMY_SUBSTATUS_1},
    [BATTLE_VARS_SUBSTATUS2]            = {PLAYER_SUBSTATUS_2,    ENEMY_SUBSTATUS_2},
    [BATTLE_VARS_SUBSTATUS3]            = {PLAYER_SUBSTATUS_3,    ENEMY_SUBSTATUS_3},
    [BATTLE_VARS_SUBSTATUS4]            = {PLAYER_SUBSTATUS_4,    ENEMY_SUBSTATUS_4},
    [BATTLE_VARS_SUBSTATUS5]            = {PLAYER_SUBSTATUS_5,    ENEMY_SUBSTATUS_5},
    [BATTLE_VARS_SUBSTATUS1_OPP]        = {ENEMY_SUBSTATUS_1,     PLAYER_SUBSTATUS_1},
    [BATTLE_VARS_SUBSTATUS2_OPP]        = {ENEMY_SUBSTATUS_2,     PLAYER_SUBSTATUS_2},
    [BATTLE_VARS_SUBSTATUS3_OPP]        = {ENEMY_SUBSTATUS_3,     PLAYER_SUBSTATUS_3},
    [BATTLE_VARS_SUBSTATUS4_OPP]        = {ENEMY_SUBSTATUS_4,     PLAYER_SUBSTATUS_4},
    [BATTLE_VARS_SUBSTATUS5_OPP]        = {ENEMY_SUBSTATUS_5,     PLAYER_SUBSTATUS_5},
    [BATTLE_VARS_STATUS]                = {PLAYER_STATUS,         ENEMY_STATUS},
    [BATTLE_VARS_STATUS_OPP]            = {ENEMY_STATUS,          PLAYER_STATUS},
    [BATTLE_VARS_MOVE_ANIM]             = {PLAYER_MOVE_ANIMATION, ENEMY_MOVE_ANIMATION},
    [BATTLE_VARS_MOVE_EFFECT]           = {PLAYER_MOVE_EFFECT,    ENEMY_MOVE_EFFECT},
    [BATTLE_VARS_MOVE_POWER]            = {PLAYER_MOVE_POWER,     ENEMY_MOVE_POWER},
    [BATTLE_VARS_MOVE_TYPE]             = {PLAYER_MOVE_TYPE,      ENEMY_MOVE_TYPE},
    [BATTLE_VARS_MOVE]                  = {PLAYER_CUR_MOVE,       ENEMY_CUR_MOVE},
    [BATTLE_VARS_LAST_COUNTER_MOVE]     = {PLAYER_COUNTER_MOVE,   ENEMY_COUNTER_MOVE},
    [BATTLE_VARS_LAST_COUNTER_MOVE_OPP] = {ENEMY_COUNTER_MOVE,    PLAYER_COUNTER_MOVE},
    [BATTLE_VARS_LAST_MOVE]             = {PLAYER_LAST_MOVE,      ENEMY_LAST_MOVE},
    [BATTLE_VARS_LAST_MOVE_OPP]         = {ENEMY_LAST_MOVE,       PLAYER_LAST_MOVE},
};

uint8_t GetBattleVar(uint8_t a){
    //     PUSH_HL;
    // CALL(aGetBattleVarAddr);
    // POP_HL;
    // RET;
    return *GetBattleVarAddr(a);
}

//  Get variable from pair a, depending on whose turn it is.
//  There are 21 variable pairs.
uint8_t* GetBattleVarAddr(uint8_t a){
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


// getvar:
    //  var id
    // LD_A_hl;
    // LD_C_A;
    // LD_B(0);
    uint8_t id = BattleVarPairs[a][(hram.hBattleTurn == TURN_PLAYER)? 0: 1];

    // LD_HL(mBattleVarLocations);
    // ADD_HL_BC;
    // ADD_HL_BC;

    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    uint8_t* loc = BattleVarLocations[id];

    // LD_A_hl;

    // POP_BC;
    // RET;
    return loc;
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
