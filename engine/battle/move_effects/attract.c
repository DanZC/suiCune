#include "../../../constants.h"
#include "attract.h"
#include "../../pokemon/mon_stats.h"
#include "../effect_commands.h"
#include "../../../home/battle.h"
#include "../../../home/battle_vars.h"
#include "../../../data/text/battle.h"

void BattleCommand_Attract(void){
//  attract
    // LD_A_addr(wAttackMissed);
    // AND_A_A;
    // IF_NZ goto failed;
    // CALL(aCheckOppositeGender);
    // IF_C goto failed;
    // CALL(aCheckHiddenOpponent);
    // IF_NZ goto failed;
    if(!wram->wAttackMissed
    && CheckOppositeGender_Conv(wram->wCurBattleMon)
    && !CheckHiddenOpponent()) {
        // LD_A(BATTLE_VARS_SUBSTATUS1_OPP);
        // CALL(aGetBattleVarAddr);
        uint8_t* hl = GetBattleVarAddr(BATTLE_VARS_SUBSTATUS1_OPP);
        // BIT_hl(SUBSTATUS_IN_LOVE);
        // IF_NZ goto failed;
        if(!bit_test(*hl, SUBSTATUS_IN_LOVE)) {
            // SET_hl(SUBSTATUS_IN_LOVE);
            bit_set(*hl, SUBSTATUS_IN_LOVE);
            // CALL(aAnimateCurrentMove);
            AnimateCurrentMove();

        //  'fell in love!'
            // LD_HL(mFellInLoveText);
            // JP(mStdBattleTextbox);
            return StdBattleTextbox(FellInLoveText);
        }
    }

// failed:
    // JP(mFailMove);
    return FailMove();

}

void CheckOppositeGender(void){
    LD_A(MON_SPECIES);
    CALL(aBattlePartyAttr);
    LD_A_hl;
    LD_addr_A(wCurPartySpecies);

    LD_A_addr(wCurBattleMon);
    LD_addr_A(wCurPartyMon);
    XOR_A_A;
    LD_addr_A(wMonType);

    FARCALL(aGetGender);
    IF_C goto genderless_samegender;

    LD_B(1);
    IF_NZ goto got_gender;
    DEC_B;


got_gender:
    PUSH_BC;
    LD_A_addr(wTempEnemyMonSpecies);
    LD_addr_A(wCurPartySpecies);
    LD_HL(wEnemyMonDVs);
    LD_A_addr(wEnemySubStatus5);
    BIT_A(SUBSTATUS_TRANSFORMED);
    IF_Z goto not_transformed;
    LD_HL(wEnemyBackupDVs);

not_transformed:
    LD_A_hli;
    LD_addr_A(wTempMonDVs);
    LD_A_hl;
    LD_addr_A(wTempMonDVs + 1);
    LD_A(3);
    LD_addr_A(wMonType);
    FARCALL(aGetGender);
    POP_BC;
    IF_C goto genderless_samegender;

    LD_A(1);
    IF_NZ goto got_enemy_gender;
    DEC_A;


got_enemy_gender:
    XOR_A_B;
    IF_Z goto genderless_samegender;

    AND_A_A;
    RET;


genderless_samegender:
    SCF;
    RET;

}

// Returns c (false) if genders match or one of the mons is genderless.
// Returns nc (true) otherwise.
bool CheckOppositeGender_Conv(uint8_t battleMon){
    // LD_A(MON_SPECIES);
    // CALL(aBattlePartyAttr);
    // LD_A_hl;
    // LD_addr_A(wCurPartySpecies);
    wram->wCurPartySpecies = wram->wPartyMon[battleMon].mon.species;

    // LD_A_addr(wCurBattleMon);
    // LD_addr_A(wCurPartyMon);
    wram->wCurPartyMon = battleMon;
    // XOR_A_A;
    // LD_addr_A(wMonType);
    wram->wMonType = PARTYMON;

    // FARCALL(aGetGender);
    // IF_C goto genderless_samegender;
    u8_flag_s res = GetGender_Conv(PARTYMON);
    if(res.flag) {
    // genderless_samegender:
        // SCF;
        // RET;
        return false;
    }

    // LD_B(1);
    // IF_NZ goto got_gender;
    // DEC_B;
    uint8_t b = (res.a != 0)? 1: 0;


// got_gender:
    // PUSH_BC;
    // LD_A_addr(wTempEnemyMonSpecies);
    // LD_addr_A(wCurPartySpecies);
    wram->wCurPartySpecies = wram->wTempEnemyMonSpecies;
    // LD_HL(wEnemyMonDVs);
    // LD_A_addr(wEnemySubStatus5);
    // BIT_A(SUBSTATUS_TRANSFORMED);
    // IF_Z goto not_transformed;
    // LD_HL(wEnemyBackupDVs);
    uint16_t dvs = (bit_test(wram->wEnemySubStatus5, SUBSTATUS_TRANSFORMED))? wram->wEnemyBackupDVs: wram->wEnemyMon.dvs;

// not_transformed:
    // LD_A_hli;
    // LD_addr_A(wTempMonDVs);
    // LD_A_hl;
    // LD_addr_A(wTempMonDVs + 1);
    wram->wTempMon.mon.DVs = dvs;
    // LD_A(3);
    // LD_addr_A(wMonType);
    // FARCALL(aGetGender);
    res = GetGender_Conv(TEMPMON);
    // POP_BC;
    // IF_C goto genderless_samegender;
    if(res.flag)
        return false;

    // LD_A(1);
    // IF_NZ goto got_enemy_gender;
    // DEC_A;
    uint8_t a = (res.a != 0)? 1: 0;

// got_enemy_gender:
    // XOR_A_B;
    // IF_Z goto genderless_samegender;

    // AND_A_A;
    // RET;
    return a != b;
}
