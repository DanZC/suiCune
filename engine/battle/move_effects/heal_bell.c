#include "../../../constants.h"
#include "heal_bell.h"
#include "../effect_commands.h"
#include "../../../home/battle.h"
#include "../../../home/battle_vars.h"
#include "../../../data/text/battle.h"

void BattleCommand_HealBell(void){
//  healbell

    // LD_A(BATTLE_VARS_SUBSTATUS1);
    // CALL(aGetBattleVarAddr);
    // RES_hl(SUBSTATUS_NIGHTMARE);
    bit_reset(*GetBattleVarAddr(BATTLE_VARS_SUBSTATUS1), SUBSTATUS_NIGHTMARE);
    // LD_DE(wPartyMon1Status);
    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // IF_Z goto got_status;
    // LD_DE(wOTPartyMon1Status);
    struct PartyMon* mon = (hram.hBattleTurn == TURN_PLAYER)? gPokemon.partyMon: wram->wOTPartyMon;

// got_status:
    // LD_A(BATTLE_VARS_STATUS);
    // CALL(aGetBattleVarAddr);
    // XOR_A_A;
    // LD_hl_A;
    *GetBattleVarAddr(BATTLE_VARS_STATUS) = 0;
    // LD_H_D;
    // LD_L_E;
    // LD_BC(PARTYMON_STRUCT_LENGTH);
    // LD_D(PARTY_LENGTH);

    for(int i = 0; i < PARTY_LENGTH; ++i) {
    // loop:
        // LD_hl_A;
        mon[i].status = 0;
        // ADD_HL_BC;
        // DEC_D;
        // IF_NZ goto loop;
    }
    // CALL(aAnimateCurrentMove);
    AnimateCurrentMove();

    // LD_HL(mBellChimedText);
    // CALL(aStdBattleTextbox);
    StdBattleTextbox(BellChimedText);

    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // JP_Z (mCalcPlayerStats);
    if(hram.hBattleTurn == 0)
        return CalcPlayerStats();
    // JP(mCalcEnemyStats);
    return CalcEnemyStats();

}
