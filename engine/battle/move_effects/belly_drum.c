#include "../../../constants.h"
#include "belly_drum.h"
#include "../core.h"
#include "../effect_commands.h"
#include "../../../home/battle.h"
#include "../../../data/text/battle.h"

void BattleCommand_BellyDrum(void){
//  bellydrum
//  This command is buggy because it raises the user's attack
//  before checking that it has enough HP to use the move.
//  Swap the order of these two blocks to fix.
#if BUGFIX_BELLYDRUM
    if(!CheckUserHasEnoughHP_Conv(GetHalfMaxHP_Conv()) || (BattleCommand_AttackUp2(), wram->wAttackMissed))
#else
    // CALL(aBattleCommand_AttackUp2);
    // LD_A_addr(wAttackMissed);
    // AND_A_A;
    // IF_NZ goto failed;

    // CALLFAR(aGetHalfMaxHP);
    // CALLFAR(aCheckUserHasEnoughHP);
    // IF_NC goto failed;
    if((BattleCommand_AttackUp2(), wram->wAttackMissed) || !CheckUserHasEnoughHP_Conv(GetHalfMaxHP_Conv()))
#endif
    {
    // failed:
        // CALL(aAnimateFailedMove);
        AnimateFailedMove();
        // JP(mPrintButItFailed);
        return PrintButItFailed();
    }


    // PUSH_BC;
    // CALL(aAnimateCurrentMove);
    AnimateCurrentMove();
    // POP_BC;
    // CALLFAR(aSubtractHPFromUser);
    SubtractHPFromUser_Conv(GetHalfMaxHP_Conv());
    // CALL(aUpdateUserInParty);
    UpdateUserInParty_Conv();
    // LD_A(MAX_STAT_LEVEL - BASE_STAT_LEVEL - 1);
    uint8_t a = MAX_STAT_LEVEL - BASE_STAT_LEVEL - 1;

    do {
    // max_attack_loop:
        // PUSH_AF;
        // CALL(aBattleCommand_AttackUp2);
        BattleCommand_AttackUp2();
        // POP_AF;
        // DEC_A;
        // IF_NZ goto max_attack_loop;
    } while(--a != 0);

    // LD_HL(mBellyDrumText);
    // JP(mStdBattleTextbox);
    return StdBattleTextbox_Conv2(BellyDrumText);
}
