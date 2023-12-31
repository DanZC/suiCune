#include "../../../constants.h"
#include "leech_seed.h"
#include "../effect_commands.h"
#include "../../../home/battle.h"
#include "../../../data/text/battle.h"

void BattleCommand_LeechSeed(void){
//  leechseed
    // LD_A_addr(wAttackMissed);
    // AND_A_A;
    // IF_NZ goto evaded;
    // CALL(aCheckSubstituteOpp);
    // IF_NZ goto evaded;
    if(wram->wAttackMissed || CheckSubstituteOpp_Conv())
        goto evaded;

    // LD_DE(wEnemyMonType1);
    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // IF_Z goto ok;
    // LD_DE(wBattleMonType1);
    uint8_t* types = (hram->hBattleTurn == 0)? wram->wEnemyMon.types: wram->wBattleMon.types;

// ok:

    // LD_A_de;
    // CP_A(GRASS);
    // IF_Z goto grass;
    // INC_DE;
    // LD_A_de;
    // CP_A(GRASS);
    // IF_Z goto grass;
    if(types[0] == GRASS || types[1] == GRASS) {
    // grass:
        // CALL(aAnimateFailedMove);
        AnimateFailedMove();
        // JP(mPrintDoesntAffect);
        return PrintDoesntAffect();
    }

    // LD_A(BATTLE_VARS_SUBSTATUS4_OPP);
    // CALL(aGetBattleVarAddr);
    uint8_t* ss4 = GetBattleVarAddr_Conv(BATTLE_VARS_SUBSTATUS4_OPP);
    // BIT_hl(SUBSTATUS_LEECH_SEED);
    // IF_NZ goto evaded;
    if(bit_test(*ss4, SUBSTATUS_LEECH_SEED)) {
    evaded:
        // CALL(aAnimateFailedMove);
        AnimateFailedMove();
        // LD_HL(mEvadedText);
        // JP(mStdBattleTextbox);
        return StdBattleTextbox_Conv2(EvadedText);
    }
    // SET_hl(SUBSTATUS_LEECH_SEED);
    bit_set(*ss4, SUBSTATUS_LEECH_SEED);
    // CALL(aAnimateCurrentMove);
    AnimateCurrentMove();
    // LD_HL(mWasSeededText);
    // JP(mStdBattleTextbox);
    return StdBattleTextbox_Conv2(WasSeededText);

}
