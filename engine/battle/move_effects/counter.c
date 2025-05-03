#include "../../../constants.h"
#include "counter.h"
#include "../core.h"
#include "../effect_commands.h"
#include "../../../home/battle_vars.h"


void BattleCommand_Counter(void){
//  counter

    // LD_A(1);
    // LD_addr_A(wAttackMissed);
    wram->wAttackMissed = TRUE;
    // LD_A(BATTLE_VARS_LAST_COUNTER_MOVE_OPP);
    move_t move = GetBattleVar(BATTLE_VARS_LAST_COUNTER_MOVE_OPP);
    // CALL(aGetBattleVar);
    // AND_A_A;
    // RET_Z ;
    if(move == NO_MOVE)
        return;

    // LD_B_A;
    // CALLFAR(aGetMoveEffect);
    uint8_t effect = GetMoveEffect_Conv(move);
    // LD_A_B;
    // CP_A(EFFECT_COUNTER);
    // RET_Z ;
    if(effect == EFFECT_COUNTER)
        return;

    // CALL(aBattleCommand_ResetTypeMatchup);
    BattleCommand_ResetTypeMatchup();
    // LD_A_addr(wTypeMatchup);
    // AND_A_A;
    // RET_Z ;

    // CALL(aCheckOpponentWentFirst);
    // RET_Z ;
    if(wram->wTypeMatchup == 0 || !CheckOpponentWentFirst())
        return;

    struct Move temp;
    // LD_A(BATTLE_VARS_LAST_COUNTER_MOVE_OPP);
    // CALL(aGetBattleVar);
    // DEC_A;
    // LD_DE(wStringBuffer1);
    // CALL(aGetMoveData);
    GetMoveData(&temp, move - 1);

    // LD_A_addr(wStringBuffer1 + MOVE_POWER);
    // AND_A_A;
    // RET_Z ;
    if(temp.power == 0)
        return;

    // LD_A_addr(wStringBuffer1 + MOVE_TYPE);
    // CP_A(SPECIAL);
    // RET_NC ;
    if(temp.type >= SPECIAL)
        return;

// BUG: Move should fail with all non-damaging battle actions
    // LD_HL(wCurDamage);
    uint32_t dmg = BigEndianToNative16(wram->wCurDamage);
    // LD_A_hli;
    // OR_A_hl;
    // RET_Z ;
    if(dmg == 0)
        return;

    // LD_A_hl;
    // ADD_A_A;
    // LD_hld_A;
    // LD_A_hl;
    // ADC_A_A;
    // LD_hl_A;
    dmg <<= 1;
    // IF_NC goto capped;
    if(dmg > 0xffff) {
        // LD_A(0xff);
        // LD_hli_A;
        // LD_hl_A;
        wram->wCurDamage = 0xffff;
    }
    else {
        wram->wCurDamage = NativeToBigEndian16((uint16_t)dmg);
    }
// capped:

    // XOR_A_A;
    // LD_addr_A(wAttackMissed);
    wram->wAttackMissed = FALSE;
    // RET;

}
