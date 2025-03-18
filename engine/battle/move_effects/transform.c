#include "../../../constants.h"
#include "transform.h"
#include "../effect_commands.h"
#include "../../../home/copy.h"
#include "../../../home/battle_vars.h"
#include "../../../home/battle.h"
#include "../../../home/names.h"
#include "../../../data/text/battle.h"

void BattleCommand_Transform(void){
//  transform

    // CALL(aClearLastMove);
    ClearLastMove();
    // LD_A(BATTLE_VARS_SUBSTATUS5_OPP);
    // CALL(aGetBattleVarAddr);
    // BIT_hl(SUBSTATUS_TRANSFORMED);
    // JP_NZ (mBattleEffect_ButItFailed);
    if(bit_test(*GetBattleVarAddr(BATTLE_VARS_SUBSTATUS5_OPP), SUBSTATUS_TRANSFORMED))
        return BattleEffect_ButItFailed();
    // CALL(aCheckHiddenOpponent);
    // JP_NZ (mBattleEffect_ButItFailed);
    if(CheckHiddenOpponent_Conv())
        return BattleEffect_ButItFailed();
    // XOR_A_A;
    // LD_addr_A(wNumHits);
    wram->wNumHits = 0;
    // LD_addr_A(wFXAnimID + 1);
    // LD_A(0x1);
    // LD_addr_A(wBattleAnimParam);
    wram->wBattleAnimParam = 0x1;
    // LD_A(BATTLE_VARS_SUBSTATUS4);
    // CALL(aGetBattleVarAddr);
    uint8_t ss4 = *GetBattleVarAddr(BATTLE_VARS_SUBSTATUS4);
    // BIT_hl(SUBSTATUS_SUBSTITUTE);
    // PUSH_AF;
    // IF_Z goto mimic_substitute;
    // CALL(aCheckUserIsCharging);
    // IF_NZ goto mimic_substitute;
    if(bit_test(ss4, SUBSTATUS_SUBSTITUTE) && !CheckUserIsCharging_Conv()) {
        // LD_A(SUBSTITUTE);
        // CALL(aLoadAnim);
        LoadAnim_Conv(SUBSTITUTE);
    }

// mimic_substitute:
    // LD_A(BATTLE_VARS_SUBSTATUS5);
    // CALL(aGetBattleVarAddr);
    // SET_hl(SUBSTATUS_TRANSFORMED);
    bit_set(*GetBattleVarAddr(BATTLE_VARS_SUBSTATUS5), SUBSTATUS_TRANSFORMED);
    // CALL(aResetActorDisable);
    ResetActorDisable();
    
    struct BattleMon* hl;
    struct BattleMon* de;

    if(hram->hBattleTurn != TURN_PLAYER) {
        // LD_HL(wBattleMonSpecies);
        hl = &wram->wBattleMon;
        // LD_DE(wEnemyMonSpecies);
        de = &wram->wEnemyMon;
        // LDH_A_addr(hBattleTurn);
        // AND_A_A;
        // IF_NZ goto got_mon_species;
    }
    else {
        // LD_HL(wEnemyMonSpecies);
        hl = &wram->wEnemyMon;
        // LD_DE(wBattleMonSpecies);
        de = &wram->wBattleMon;
        // XOR_A_A;
        // LD_addr_A(wCurMoveNum);
        wram->wCurMoveNum = 0;
    }

// got_mon_species:
    // PUSH_HL;
    // LD_A_hli;
    // LD_de_A;
    // INC_HL;
    // INC_DE;
    // INC_DE;
    de->species = hl->species;
    // LD_BC(NUM_MOVES);
    // CALL(aCopyBytes);
    CopyBytes(de->moves, hl->moves, sizeof(de->moves));
    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // IF_Z goto mimic_enemy_backup;
    if(hram->hBattleTurn != TURN_PLAYER) {
        // LD_A_de;
        // LD_addr_A(wEnemyBackupDVs);
        // INC_DE;
        // LD_A_de;
        // LD_addr_A(wEnemyBackupDVs + 1);
        wram->wEnemyBackupDVs = de->dvs;
        // DEC_DE;
    }

// mimic_enemy_backup:
//  copy DVs
    // LD_A_hli;
    // LD_de_A;
    // INC_DE;
    // LD_A_hli;
    // LD_de_A;
    // INC_DE;
    de->dvs = hl->dvs;
//  move pointer to stats
    // LD_BC(wBattleMonStats - wBattleMonPP);
    // ADD_HL_BC;
    // PUSH_HL;
    // LD_H_D;
    // LD_L_E;
    // ADD_HL_BC;
    // LD_D_H;
    // LD_E_L;
    // POP_HL;
    // LD_BC(wBattleMonStructEnd - wBattleMonStats);
    CopyBytes(de->stats, hl->stats, sizeof(de->stats));
    CopyBytes(de->types, hl->types, sizeof(de->types));
    // CALL(aCopyBytes);
//  init the power points
    // LD_BC(wBattleMonMoves - wBattleMonStructEnd);
    // ADD_HL_BC;
    // PUSH_DE;
    // LD_D_H;
    // LD_E_L;
    // POP_HL;
    // LD_BC(wBattleMonPP - wBattleMonStructEnd);
    // ADD_HL_BC;
    // LD_B(NUM_MOVES);
    for(uint8_t b = 0; b < NUM_MOVES; ++b) {
    // pp_loop:
        // LD_A_de;
        // INC_DE;
        // AND_A_A;
        // IF_Z goto done_move;
        if(hl->moves[b] == NO_MOVE)
            break;
        // CP_A(SKETCH);
        // LD_A(1);
        // IF_Z goto done_move;
        if(hl->moves[b] == SKETCH)
            de->pp[b] = 1;
        else
            // LD_A(5);
            de->pp[b] = 5;

    // done_move:
        // LD_hli_A;
        // DEC_B;
        // IF_NZ goto pp_loop;
    }
    // POP_HL;
    // LD_A_hl;
    // LD_addr_A(wNamedObjectIndex);
    // CALL(aGetPokemonName);
    GetPokemonName(hl->species);
    // LD_HL(wEnemyStats);
    // LD_DE(wPlayerStats);
    // LD_BC(2 * 5);
    // CALL(aBattleSideCopy);
    BattleSideCopy(wram->wEnemyStats, wram->wPlayerStats, 2 * 5);
    // LD_HL(wEnemyStatLevels);
    // LD_DE(wPlayerStatLevels);
    // LD_BC(8);
    // CALL(aBattleSideCopy);
    BattleSideCopy(wram->wEnemyStatLevels, wram->wPlayerStatLevels, 2 * 5);
    // CALL(av_CheckBattleScene);
    // IF_C goto mimic_anims;
    if(!v_CheckBattleScene_Conv()) {
        // LDH_A_addr(hBattleTurn);
        // AND_A_A;
        // LD_A_addr(wPlayerMinimized);
        // IF_Z goto got_byte;
        // LD_A_addr(wEnemyMinimized);

    // got_byte:
        uint8_t minimized = (hram->hBattleTurn == 0)? wram->wPlayerMinimized: wram->wEnemyMinimized;
        // AND_A_A;
        // IF_NZ goto mimic_anims;
        if(minimized)
            goto mimic_anims;
        // CALL(aLoadMoveAnim);
        LoadMoveAnim();
        // goto after_anim;
    }
    else {
    mimic_anims:
        // CALL(aBattleCommand_MoveDelay);
        BattleCommand_MoveDelay();
        // CALL(aBattleCommand_RaiseSubNoAnim);
        BattleCommand_RaiseSubNoAnim();
    }

// after_anim:
    // XOR_A_A;
    // LD_addr_A(wNumHits);
    wram->wNumHits = 0;
    // LD_addr_A(wFXAnimID + 1);
    // LD_A(0x2);
    // LD_addr_A(wBattleAnimParam);
    wram->wBattleAnimParam = 0x2;
    // POP_AF;
    // LD_A(SUBSTITUTE);
    // CALL_NZ (aLoadAnim);
    if(bit_test(ss4, SUBSTATUS_SUBSTITUTE))
        LoadAnim_Conv(SUBSTITUTE);
    // LD_HL(mTransformedText);
    // JP(mStdBattleTextbox);
    return StdBattleTextbox(TransformedText);
}

//  Copy bc bytes from hl to de if it's the player's turn.
//  Copy bc bytes from de to hl if it's the enemy's turn.
void BattleSideCopy(void* hl, void* de, uint16_t bc){
    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // IF_Z goto copy;
    if(hram->hBattleTurn != TURN_PLAYER) {
    //  Swap hl and de
        // PUSH_HL;
        // LD_H_D;
        // LD_L_E;
        // POP_DE;
        return CopyBytes(hl, de, bc);
    }

// copy:
    // JP(mCopyBytes);
    return CopyBytes(de, hl, bc);
}
