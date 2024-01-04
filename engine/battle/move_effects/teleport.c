#include "../../../constants.h"
#include "teleport.h"
#include "../effect_commands.h"
#include "../core.h"
#include "../../../home/delay.h"
#include "../../../home/battle.h"
#include "../../../home/battle_vars.h"
#include "../../../data/text/battle.h"

// TODO: Rewrite this without the gotos.
void BattleCommand_Teleport(void){
//  teleport

    // LD_A_addr(wBattleType);
    // CP_A(BATTLETYPE_SHINY);
    // IF_Z goto failed;
    // CP_A(BATTLETYPE_TRAP);
    // IF_Z goto failed;
    // CP_A(BATTLETYPE_CELEBI);
    // IF_Z goto failed;
    // CP_A(BATTLETYPE_SUICUNE);
    // IF_Z goto failed;
    if(wram->wBattleType == BATTLETYPE_SHINY
    || wram->wBattleType == BATTLETYPE_TRAP
    || wram->wBattleType == BATTLETYPE_CELEBI
    || wram->wBattleType == BATTLETYPE_SUICUNE)
        goto failed;

    // LD_A(BATTLE_VARS_SUBSTATUS5_OPP);
    // CALL(aGetBattleVar);
    // BIT_A(SUBSTATUS_CANT_RUN);
    // IF_NZ goto failed;
    if(!bit_test(GetBattleVar_Conv(BATTLE_VARS_SUBSTATUS5_OPP), SUBSTATUS_CANT_RUN)) {
        // LDH_A_addr(hBattleTurn);
        // AND_A_A;
        // IF_NZ goto enemy_turn;
        if(hram->hBattleTurn == 0) {
        // Can't teleport from a trainer battle
            // LD_A_addr(wBattleMode);
            // DEC_A;
            // IF_NZ goto failed;
            if(wram->wBattleMode == TRAINER_BATTLE)
                goto failed;
        // b = player level
            // LD_A_addr(wCurPartyLevel);
            // LD_B_A;
            uint8_t b = wram->wCurPartyLevel;
        // If player level >= enemy level, Teleport will succeed
            // LD_A_addr(wBattleMonLevel);
            // CP_A_B;
            // IF_NC goto run_away;
            if(wram->wBattleMon.level < b) {
            // c = player level + enemy level + 1
                // ADD_A_B;
                // LD_C_A;
                // INC_C;
                uint8_t c = wram->wBattleMon.level + b + 1;
            // Generate a number less than c
                uint8_t a;
                do {
                // loop_player:
                    // CALL(aBattleRandom);
                    a = v_BattleRandom_Conv();
                    // CP_A_C;
                    // IF_NC goto loop_player;
                } while(a >= c);
            // b = enemy level / 4
                // SRL_B;
                // SRL_B;
                b >>= 2;
            // If the random number >= enemy level / 4, Teleport will succeed
                // CP_A_B;
                // IF_NC goto run_away;
                if(a < b)
                    goto failed;
            }
        }
        else {
        // enemy_turn:
        // Can't teleport from a trainer battle
            // LD_A_addr(wBattleMode);
            // DEC_A;
            // IF_NZ goto failed;
            if(wram->wBattleMode == TRAINER_BATTLE)
                goto failed;
        // b = enemy level
            // LD_A_addr(wBattleMonLevel);
            // LD_B_A;
            uint8_t b = wram->wBattleMon.level;
        // If enemy level >= player level, Teleport will succeed
            // LD_A_addr(wCurPartyLevel);
            // CP_A_B;
            // IF_NC goto run_away;
            if(wram->wCurPartyLevel < b) {
            // c = enemy level + player level + 1
                // ADD_A_B;
                // LD_C_A;
                // INC_C;
                uint8_t c = wram->wCurPartyLevel + b + 1;
            // Generate a number less than c
                uint8_t a;
                do {
                // loop_enemy:
                    // CALL(aBattleRandom);
                    a = v_BattleRandom_Conv();
                    // CP_A_C;
                    // IF_NC goto loop_enemy;
                } while(a >= c);
            // b = player level / 4
                // SRL_B;
                // SRL_B;
                b >>= 2;
            // This should be "jr c, .failed"
            // As written, it makes enemy use of Teleport always succeed if able
                // CP_A_B;
                // IF_NC goto run_away;
                if(a < b)
                    goto failed;
            }
        }
    }

// run_away:
    // CALL(aUpdateBattleMonInParty);
    UpdateBattleMonInParty_Conv();
    // XOR_A_A;
    // LD_addr_A(wNumHits);
    wram->wNumHits = 0;
    // INC_A;
    // LD_addr_A(wForcedSwitch);
    wram->wForcedSwitch = 1;
    // LD_addr_A(wBattleAnimParam);
    wram->wBattleAnimParam = 1;
    // CALL(aSetBattleDraw);
    SetBattleDraw();
    // CALL(aBattleCommand_LowerSub);
    BattleCommand_LowerSub();
    // CALL(aLoadMoveAnim);
    LoadMoveAnim();
    // LD_C(20);
    // CALL(aDelayFrames);
    DelayFrames_Conv(20);
    // CALL(aSetBattleDraw);
    SetBattleDraw();

    // LD_HL(mFledFromBattleText);
    // JP(mStdBattleTextbox);
    return StdBattleTextbox_Conv2(FledFromBattleText);

failed:
    // CALL(aAnimateFailedMove);
    AnimateFailedMove();
    // JP(mPrintButItFailed);
    return PrintButItFailed();

}
