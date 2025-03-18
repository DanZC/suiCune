#include "../../../constants.h"
#include "curse.h"
#include "../effect_commands.h"
#include "../core.h"
#include "../../../home/battle_vars.h"
#include "../../../home/battle.h"
#include "../../../data/text/battle.h"

void BattleCommand_Curse(void){
//  curse

    // LD_DE(wBattleMonType1);
    // LD_BC(wPlayerStatLevels);
    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // IF_Z goto go;
    // LD_DE(wEnemyMonType1);
    // LD_BC(wEnemyStatLevels);
    const uint8_t* types = (hram->hBattleTurn == TURN_PLAYER)? wram->wBattleMon.types: wram->wEnemyMon.types;
    uint8_t* statLevels = (hram->hBattleTurn == TURN_PLAYER)? wram->wPlayerStatLevels: wram->wEnemyStatLevels;

// go:

//  Curse is different for Ghost-types.

    // LD_A_de;
    // CP_A(GHOST);
    // IF_Z goto ghost;
    // INC_DE;
    // LD_A_de;
    // CP_A(GHOST);
    // IF_Z goto ghost;
    if(types[0] == GHOST || types[1] == GHOST) {
    // ghost:
    //  Cut HP in half and put a curse on the opponent.
        // CALL(aCheckHiddenOpponent);
        // IF_NZ goto failed;

        // CALL(aCheckSubstituteOpp);
        // IF_NZ goto failed;

        // LD_A(BATTLE_VARS_SUBSTATUS1_OPP);
        // CALL(aGetBattleVarAddr);
        // BIT_hl(SUBSTATUS_CURSE);
        // IF_NZ goto failed;
        if(CheckHiddenOpponent_Conv() || CheckSubstituteOpp_Conv() || bit_test(GetBattleVar(BATTLE_VARS_SUBSTATUS1_OPP), SUBSTATUS_CURSE)) {
        // failed:
            // CALL(aAnimateFailedMove);
            AnimateFailedMove();
            // JP(mPrintButItFailed);
            return PrintButItFailed();
        }

        // SET_hl(SUBSTATUS_CURSE);
        bit_set(*GetBattleVarAddr(BATTLE_VARS_SUBSTATUS1_OPP), SUBSTATUS_CURSE);
        // CALL(aAnimateCurrentMove);
        AnimateCurrentMove();
        // LD_HL(mGetHalfMaxHP);
        // CALL(aCallBattleCore);
        // LD_HL(mSubtractHPFromUser);
        // CALL(aCallBattleCore);
        SubtractHPFromUser_Conv(GetHalfMaxHP_Conv());
        // CALL(aUpdateUserInParty);
        UpdateUserInParty();
        // LD_HL(mPutACurseText);
        // JP(mStdBattleTextbox);
        return StdBattleTextbox(PutACurseText);
    }
    else {
    //  If no stats can be increased, don't.

    //  Attack
        // LD_A_bc;
        // CP_A(MAX_STAT_LEVEL);
        // IF_C goto raise;

        if(statLevels[0] >= MAX_STAT_LEVEL) {
        //  Defense
            // INC_BC;
            statLevels++;
            // LD_A_bc;
            // CP_A(MAX_STAT_LEVEL);
            // IF_NC goto cantraise;
            if(statLevels[0] >= MAX_STAT_LEVEL) {
            // cantraise:

            //  Can't raise either stat.

                // LD_B(ABILITY + 1);
                // CALL(aGetStatName);
                GetStatName_Conv(ABILITY + 1);
                // CALL(aAnimateFailedMove);
                AnimateFailedMove();
                // LD_HL(mWontRiseAnymoreText);
                // JP(mStdBattleTextbox);
                return StdBattleTextbox(WontRiseAnymoreText);
            }
        }

    // raise:

    //  Raise Attack and Defense, and lower Speed.

        // LD_A(0x1);
        // LD_addr_A(wBattleAnimParam);
        wram->wBattleAnimParam = 0x1;
        // CALL(aAnimateCurrentMove);
        AnimateCurrentMove();
        // LD_A(SPEED);
        // CALL(aLowerStat);
        LowerStat_Conv(SPEED);
        // CALL(aBattleCommand_SwitchTurn);
        BattleCommand_SwitchTurn();
        // CALL(aBattleCommand_StatDownMessage);
        BattleCommand_StatDownMessage();
        // CALL(aResetMiss);
        ResetMiss();
        // CALL(aBattleCommand_SwitchTurn);
        BattleCommand_SwitchTurn();
        // CALL(aBattleCommand_AttackUp);
        BattleCommand_AttackUp();
        // CALL(aBattleCommand_StatUpMessage);
        BattleCommand_StatUpMessage();
        // CALL(aResetMiss);
        ResetMiss();
        // CALL(aBattleCommand_DefenseUp);
        BattleCommand_DefenseUp();
        // JP(mBattleCommand_StatUpMessage);
        return BattleCommand_StatUpMessage();
    }
}
