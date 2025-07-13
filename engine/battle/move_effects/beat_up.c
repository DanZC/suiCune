#include "../../../constants.h"
#include "beat_up.h"
#include "../effect_commands.h"
#include "../../../home/battle.h"
#include "../../../home/battle_vars.h"
#include "../../../home/delay.h"
#include "../../../home/copy.h"
#include "../../../home/names.h"
#include "../../../home/pokemon.h"
#include "../../../data/text/battle.h"

static struct PartyMon* GetBeatupMonLocation(void);

void BattleCommand_BeatUp(void){
//  beatup

    // CALL(aResetDamage);
    ResetDamage();
    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // JP_NZ (mBattleCommand_BeatUp_enemy_beats_up);
    if(hram.hBattleTurn == TURN_PLAYER) {

        // LD_A_addr(wPlayerSubStatus3);
        // BIT_A(SUBSTATUS_IN_LOOP);
        // IF_NZ goto next_mon;

        if(bit_test(wram->wPlayerSubStatus3, SUBSTATUS_IN_LOOP)) {
        // next_mon:
            // LD_A_addr(wPlayerRolloutCount);
            // LD_B_A;
            // LD_A_addr(wPartyCount);
            // SUB_A_B;
            // LD_addr_A(wCurBeatUpPartyMon);
            wram->wCurBeatUpPartyMon = (gPokemon.partyCount - wram->wPlayerRolloutCount);
        }
        else {
            // LD_C(20);
            // CALL(aDelayFrames);
            DelayFrames(20);
            // XOR_A_A;
            // LD_addr_A(wPlayerRolloutCount);
            wram->wPlayerRolloutCount = 0;
            // LD_addr_A(wCurBeatUpPartyMon);
            wram->wCurBeatUpPartyMon = 0;
            // LD_addr_A(wBeatUpHitAtLeastOnce);
            wram->wBeatUpHitAtLeastOnce = 0;
            // goto got_mon;
        }

    // got_mon:
        // LD_A_addr(wCurBeatUpPartyMon);
        // LD_HL(wPartyMonNicknames);
        // CALL(aGetNickname);
        GetNickname(gPokemon.partyMonNickname[0], wram->wCurBeatUpPartyMon);
        // LD_A(MON_HP);
        // CALL(aGetBeatupMonLocation);
        struct PartyMon* mon = GetBeatupMonLocation();
        // LD_A_hli;
        // OR_A_hl;
        // JP_Z (mBattleCommand_BeatUp_beatup_fail);  // fainted
        if(mon->HP == 0)
            goto beatup_fail;
        // LD_A_addr(wCurBeatUpPartyMon);
        // LD_C_A;
        uint8_t c = wram->wCurBeatUpPartyMon;
        // LD_A_addr(wCurBattleMon);
    // BUG: this can desynchronize link battles
    // Change "cp [hl]" to "cp c" to fix
        // CP_A_hl;
        uint8_t status;
    #if BUGFIX_BEATUP_DESYNC
        if(wram->wCurBattleMon == c)
    #else
        (void)c;
        if(wram->wCurBattleMon == HIGH(mon->HP))
    #endif
        {
            status = wram->wBattleMon.status[0];
        }
        else 
        {
            status = mon->status;
        }
        // LD_HL(wBattleMonStatus);
        // IF_Z goto active_mon;
        // LD_A(MON_STATUS);
        // CALL(aGetBeatupMonLocation);

    // active_mon:
        // LD_A_hl;
        // AND_A_A;
        // JP_NZ (mBattleCommand_BeatUp_beatup_fail);
        if(status)
            goto beatup_fail;

        // LD_A(0x1);
        // LD_addr_A(wBeatUpHitAtLeastOnce);
        wram->wBeatUpHitAtLeastOnce = 0x1;
        // LD_HL(mBeatUpAttackText);
        // CALL(aStdBattleTextbox);
        StdBattleTextbox(BeatUpAttackText);

        // LD_A_addr(wEnemyMonSpecies);
        // LD_addr_A(wCurSpecies);
        wram->wCurSpecies = wram->wEnemyMon.species;
        // CALL(aGetBaseData);
        GetBaseData(wram->wEnemyMon.species);
        // LD_A_addr(wBaseDefense);
        // LD_C_A;
        gBattleCmdState.c = wram->wBaseDefense;

        // PUSH_BC;
        // LD_A(MON_SPECIES);
        // CALL(aGetBeatupMonLocation);
        // LD_A_hl;
        // LD_addr_A(wCurSpecies);
        wram->wCurSpecies = mon->mon.species;
        // CALL(aGetBaseData);
        GetBaseData(mon->mon.species);
        // LD_A_addr(wBaseAttack);
        // POP_BC;
        // LD_B_A;
        gBattleCmdState.b = wram->wBaseAttack;

        // PUSH_BC;
        // LD_A(MON_LEVEL);
        // CALL(aGetBeatupMonLocation);
        // LD_A_hl;
        // LD_E_A;
        gBattleCmdState.e = mon->mon.level;
        // POP_BC;

        // LD_A_addr(wPlayerMoveStructPower);
        // LD_D_A;
        gBattleCmdState.d = wram->wPlayerMoveStruct.power;
        // RET;
        return;
    }
    else {
    // enemy_beats_up:
        // LD_A_addr(wEnemySubStatus3);
        // BIT_A(SUBSTATUS_IN_LOOP);
        // IF_NZ goto enemy_next_mon;

        if(bit_test(wram->wEnemySubStatus3, SUBSTATUS_IN_LOOP)) {
        // enemy_next_mon:
            // LD_A_addr(wEnemyRolloutCount);
            // LD_B_A;
            // LD_A_addr(wOTPartyCount);
            // SUB_A_B;
            // LD_addr_A(wCurBeatUpPartyMon);
            wram->wCurBeatUpPartyMon = wram->wOTPartyCount - wram->wEnemyRolloutCount;
        }
        else {
            // XOR_A_A;
            // LD_addr_A(wEnemyRolloutCount);
            wram->wEnemyRolloutCount = 0;
            // LD_addr_A(wCurBeatUpPartyMon);
            wram->wCurBeatUpPartyMon = 0;
            // LD_addr_A(wBeatUpHitAtLeastOnce);
            wram->wBeatUpHitAtLeastOnce = 0;
            // goto enemy_got_mon;
        }

    // enemy_got_mon:
        // LD_A_addr(wBattleMode);
        // DEC_A;
        // IF_Z goto wild;
        if(wram->wBattleMode == WILD_BATTLE) {
        // wild:
            // LD_A_addr(wEnemyMonSpecies);
            // LD_addr_A(wNamedObjectIndex);
            // CALL(aGetPokemonName);
            GetPokemonName(wram->wEnemyMon.species);
            // LD_HL(mBeatUpAttackText);
            // CALL(aStdBattleTextbox);
            StdBattleTextbox(BeatUpAttackText);
            // JP(mEnemyAttackDamage);
            return EnemyAttackDamage(&gBattleCmdState);
        }

        // LD_A_addr(wLinkMode);
        // AND_A_A;
        // IF_NZ goto link_or_tower;

        // LD_A_addr(wInBattleTowerBattle);
        // AND_A_A;
        // IF_NZ goto link_or_tower;
        if(wram->wLinkMode != LINK_NULL || wram->wInBattleTowerBattle != 0) {
        // link_or_tower:
            // LD_A_addr(wCurBeatUpPartyMon);
            // LD_HL(wOTPartyMonNicknames);
            // LD_BC(NAME_LENGTH);
            // CALL(aAddNTimes);
            // LD_DE(wStringBuffer1);
            // CALL(aCopyBytes);
            CopyBytes(wram->wStringBuffer1, wram->wOTPartyMonNickname[wram->wCurBeatUpPartyMon], NAME_LENGTH);
        }
        else {
            // LD_A_addr(wCurBeatUpPartyMon);
            // LD_C_A;
            // LD_B(0);
            // LD_HL(wOTPartySpecies);
            // ADD_HL_BC;
            // LD_A_hl;
            // LD_addr_A(wNamedObjectIndex);
            // CALL(aGetPokemonName);
            GetPokemonName(wram->wOTPartySpecies[wram->wCurBeatUpPartyMon]);
            // goto got_enemy_nick;
        }

    // got_enemy_nick:
        // LD_A(MON_HP);
        // CALL(aGetBeatupMonLocation);
        struct PartyMon* mon = GetBeatupMonLocation();
        // LD_A_hli;
        // OR_A_hl;
        // JP_Z (mBattleCommand_BeatUp_beatup_fail);
        if(mon->HP == 0)
            goto beatup_fail;

        // LD_A_addr(wCurBeatUpPartyMon);
        // LD_B_A;
        // LD_A_addr(wCurOTMon);
        // CP_A_B;
        // LD_HL(wEnemyMonStatus);
        // IF_Z goto active_enemy;
        uint8_t status;
        if(wram->wCurBeatUpPartyMon == wram->wCurOTMon) {
            status = wram->wEnemyMon.status[0];
        }
        else {
            status = mon->status;
        }
        // LD_A(MON_STATUS);
        // CALL(aGetBeatupMonLocation);

    // active_enemy:
        // LD_A_hl;
        // AND_A_A;
        // IF_NZ goto beatup_fail;
        if(status)
            goto beatup_fail;

        // LD_A(0x1);
        // LD_addr_A(wBeatUpHitAtLeastOnce);
        wram->wBeatUpHitAtLeastOnce = 0x1;
        // goto finish_beatup;

    // finish_beatup:
        // LD_HL(mBeatUpAttackText);
        // CALL(aStdBattleTextbox);
        StdBattleTextbox(BeatUpAttackText);

        // LD_A_addr(wBattleMonSpecies);
        // LD_addr_A(wCurSpecies);
        wram->wCurSpecies = wram->wBattleMon.species;
        // CALL(aGetBaseData);
        GetBaseData(wram->wBattleMon.species);
        // LD_A_addr(wBaseDefense);
        // LD_C_A;
        gBattleCmdState.c = wram->wBaseDefense;

        // PUSH_BC;
        // LD_A(MON_SPECIES);
        // CALL(aGetBeatupMonLocation);
        // LD_A_hl;
        // LD_addr_A(wCurSpecies);
        wram->wCurSpecies = mon->mon.species;
        // CALL(aGetBaseData);
        GetBaseData(mon->mon.species);
        // LD_A_addr(wBaseAttack);
        // POP_BC;
        // LD_B_A;
        gBattleCmdState.b = wram->wBaseAttack;

        // PUSH_BC;
        // LD_A(MON_LEVEL);
        // CALL(aGetBeatupMonLocation);
        // LD_A_hl;
        // LD_E_A;
        gBattleCmdState.e = mon->mon.level;
        // POP_BC;

        // LD_A_addr(wEnemyMoveStructPower);
        // LD_D_A;
        gBattleCmdState.d = wram->wEnemyMoveStruct.power;
        // RET;
        return;
    }


beatup_fail:
    // LD_B(buildopponentrage_command);
    // JP(mSkipToBattleCommand);
    return SkipToBattleCommand(buildopponentrage_command);

}

void BattleCommand_BeatUpFailText(void){
//  beatupfailtext

    // LD_A_addr(wBeatUpHitAtLeastOnce);
    // AND_A_A;
    // RET_NZ ;
    if(wram->wBeatUpHitAtLeastOnce)
        return;

#if BUGFIX_BEAT_UP_FAIL_TEXT
    wram->wAttackMissed = TRUE;
#endif

    // JP(mPrintButItFailed);
    return PrintButItFailed();

}

static struct PartyMon* GetBeatupMonLocation(void) {
    // PUSH_BC;
    // LD_C_A;
    // LD_B(0);
    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // LD_HL(wPartyMon1Species);
    // IF_Z goto got_species;
    // LD_HL(wOTPartyMon1Species);
    struct PartyMon* mon = (hram.hBattleTurn == TURN_PLAYER)? gPokemon.partyMon: wram->wOTPartyMon;

// got_species:
    // LD_A_addr(wCurBeatUpPartyMon);
    // ADD_HL_BC;
    // CALL(aGetPartyLocation);
    // POP_BC;
    // RET;
    return mon + wram->wCurBeatUpPartyMon;
}
