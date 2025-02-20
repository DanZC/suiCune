#include "../../../constants.h"
#include "protect.h"
#include "../effect_commands.h"
#include "../core.h"
#include "../../../home/battle.h"
#include "../../../home/battle_vars.h"
#include "../../../data/text/battle.h"

void BattleCommand_Protect(void){
//  protect
    // CALL(aProtectChance);
    // RET_C ;
    if(!ProtectChance_Conv())
        return;

    // LD_A(BATTLE_VARS_SUBSTATUS1);
    // CALL(aGetBattleVarAddr);
    // SET_hl(SUBSTATUS_PROTECT);
    bit_set(*GetBattleVarAddr_Conv(BATTLE_VARS_SUBSTATUS1), SUBSTATUS_PROTECT);

    // CALL(aAnimateCurrentMove);
    AnimateCurrentMove();

    // LD_HL(mProtectedItselfText);
    // JP(mStdBattleTextbox);
    return StdBattleTextbox_Conv2(ProtectedItselfText);

}

void ProtectChance(void){
    LD_DE(wPlayerProtectCount);
    LDH_A_addr(hBattleTurn);
    AND_A_A;
    IF_Z goto got_count;
    LD_DE(wEnemyProtectCount);

got_count:

    CALL(aCheckOpponentWentFirst);
    IF_NZ goto failed;

//  Can't have a substitute.

    LD_A(BATTLE_VARS_SUBSTATUS4);
    CALL(aGetBattleVar);
    BIT_A(SUBSTATUS_SUBSTITUTE);
    IF_NZ goto failed;

//  Halve the chance of a successful Protect for each consecutive use.

    LD_B(0xff);
    LD_A_de;
    LD_C_A;

loop:
    LD_A_C;
    AND_A_A;
    IF_Z goto done;
    DEC_C;

    SRL_B;
    LD_A_B;
    AND_A_A;
    IF_NZ goto loop;
    goto failed;

done:


rand:
    CALL(aBattleRandom);
    AND_A_A;
    IF_Z goto rand;

    DEC_A;
    CP_A_B;
    IF_NC goto failed;

//  Another consecutive Protect use.

    LD_A_de;
    INC_A;
    LD_de_A;

    AND_A_A;
    RET;


failed:
    XOR_A_A;
    LD_de_A;
    CALL(aAnimateFailedMove);
    CALL(aPrintButItFailed);
    SCF;
    RET;

}

bool ProtectChance_Conv(void){
    // LD_DE(wPlayerProtectCount);
    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // IF_Z goto got_count;
    // LD_DE(wEnemyProtectCount);
    uint8_t* de = (hBattleTurn == 0)? &wram->wPlayerProtectCount: &wram->wEnemyProtectCount;

// got_count:
    // CALL(aCheckOpponentWentFirst);
    // IF_NZ goto failed;

    //  Can't have a substitute.

    // LD_A(BATTLE_VARS_SUBSTATUS4);
    // CALL(aGetBattleVar);
    // BIT_A(SUBSTATUS_SUBSTITUTE);
    // IF_NZ goto failed;
    if(!CheckOpponentWentFirst_Conv() && !bit_test(GetBattleVar_Conv(BATTLE_VARS_SUBSTATUS4), SUBSTATUS_SUBSTITUTE)) {
    //  Halve the chance of a successful Protect for each consecutive use.
        // LD_B(0xff);
        uint8_t b = 0xff;
        // LD_A_de;
        // LD_C_A;
        uint8_t c = *de;

        while(c != 0) {
        // loop:
            // LD_A_C;
            // AND_A_A;
            // IF_Z goto done;
            // DEC_C;
            --c;

            // SRL_B;
            b >>= 1;
            // LD_A_B;
            // AND_A_A;
            // IF_NZ goto loop;
        }
        // goto failed;

    // done:
        if(b != 0) {
            uint8_t a;
            do {
            // rand:
                // CALL(aBattleRandom);
                a = v_BattleRandom_Conv();
                // AND_A_A;
                // IF_Z goto rand;
            } while(a == 0);

            // DEC_A;
            // CP_A_B;
            // IF_NC goto failed;
            if(--a < b) {
            //  Another consecutive Protect use.
                // LD_A_de;
                // INC_A;
                // LD_de_A;
                (*de)++;

                // AND_A_A;
                // RET;
                return true;
            }
        }
    }

// failed:
    // XOR_A_A;
    // LD_de_A;
    *de = 0;
    // CALL(aAnimateFailedMove);
    AnimateFailedMove();
    // CALL(aPrintButItFailed);
    PrintButItFailed();
    // SCF;
    // RET;
    return false;
}

