#include "../../../constants.h"
#include "battle_tower.h"
#include "rules.h"
#include "load_trainer.h"
#include "../../menus/save.h"
#include "../../overworld/overworld.h"
#include "../../pokemon/health.h"
#include "../../battle/core.h"
#include "../../../home/sram.h"
#include "../../../home/time.h"
#include "../../../home/audio.h"
#include "../../../home/copy.h"
#include "../../../home/delay.h"
#include "../../../home/names.h"
#include "../../../mobile/mobile_41.h"
#include "../../../mobile/mobile_46.h"
#include "../../../mobile/mobile_5c.h"
#include "../../../mobile/mobile_5f.h"
#include "../../../data/trainers/sprites.h"

void BattleTowerRoomMenu(void){
//  special
    // CALL(aInitBattleTowerChallengeRAM);
    InitBattleTowerChallengeRAM();
    // FARCALL(av_BattleTowerRoomMenu);
    v_BattleTowerRoomMenu();
    // RET;
}

void Function1700ba(void){
//  special
    CALL(aInitBattleTowerChallengeRAM);
    FARCALL(aFunction11811a);
    RET;

}

void Function1700c4(void){
    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(BANK(w3_d202TrainerData));  // aka BANK(w3_dffc) and BANK(w3_d202Name)
    LDH_addr_A(rSVBK);

    CALL(aFunction17042c);

    LD_A(BANK(s5_be45));  // aka BANK(s5_be46), BANK(s5_aa41), and BANK(s5_aa5d)
    CALL(aOpenSRAM);
    LD_A(1);
    LD_addr_A(s5_be45);
    XOR_A_A;
    LD_addr_A(s5_be46);
    LD_HL(w3_dffc);
    LD_DE(s5_aa41);
    LD_BC(4);
    CALL(aCopyBytes);
    LD_HL(w3_d202Name);
    LD_DE(s5_aa8e);
    LD_BC(BATTLETOWER_STREAK_LENGTH * 0xcc);  // length of battle tower struct from japanese games?
    CALL(aCopyBytes);
    LD_HL(s5_aa5d);  // some sort of count
    LD_A_hl;
    INC_hl;
    INC_HL;
    SLA_A;
    SLA_A;
    LD_E_A;
    LD_D(0);
    ADD_HL_DE;
    LD_E_L;
    LD_D_H;
    LD_HL(w3_dffc);
    LD_BC(4);
    CALL(aCopyBytes);
    CALL(aCloseSRAM);
    POP_AF;
    LDH_addr_A(rSVBK);
    RET;

}

void Function170114(void){
    CALL(aInitBattleTowerChallengeRAM);
    CALL(aFunction170114_Function170121);
    FARCALL(aFunction11805f);
    RET;


Function170121:
    LD_A(BANK(s5_a948));
    CALL(aOpenSRAM);
    LD_HL(s5_a948);
    LD_DE(wc608);
    LD_BC(246);
    CALL(aCopyBytes);
    CALL(aCloseSRAM);
    CALL(aFunction170c8b);
    RET;

}

void Function170139(void){
//  //  unreferenced
//  Convert the 4-digit decimal number at s5_aa41 into binary
    LD_A(BANK(s5_aa41));
    CALL(aOpenSRAM);
    LD_DE(s5_aa41);
    LD_H(0);
    LD_L_H;
    LD_BC(1000);
    CALL(aFunction170139_DecToBin);
    LD_BC(100);
    CALL(aFunction170139_DecToBin);
    LD_BC(10);
    CALL(aFunction170139_DecToBin);
    LD_A_de;
    LD_C_A;
    LD_B(0);
    ADD_HL_BC;
    CALL(aCloseSRAM);
//  Store that number in wc608
    LD_A_H;
    LD_addr_A(wc608);
    LD_A_L;
    LD_addr_A(wc608 + 1);
    LD_HL(wBT_OTTempMon1DVs);
    LD_A_addr(wPlayerID);
    LD_hli_A;
    LD_A_addr(wPlayerID + 1);
    LD_hli_A;
    LD_A_addr(wSecretID);
    LD_hli_A;
    LD_A_addr(wSecretID + 1);
    LD_hli_A;
    LD_E_L;
    LD_D_H;
    LD_HL(wPlayerName);
    LD_BC(NAME_LENGTH_JAPANESE - 1);
    CALL(aCopyBytes);
    LD_BC(wPlayerID);
    LD_DE(wPlayerGender);
    FARCALL(aGetMobileOTTrainerClass);
    LD_DE(wBT_OTTempMon1CaughtGender);
    LD_A_C;
    LD_de_A;
    INC_DE;
    LD_A(LOW(wPartyMons));
    LD_addr_A(wcd49);
    LD_A(HIGH(wPartyMons));
    LD_addr_A(wcd4a);
    LD_A(LOW(wPartyMonNicknames));
    LD_addr_A(wcd4b);
    LD_A(HIGH(wPartyMonNicknames));
    LD_addr_A(wcd4c);
    LD_A(3);

CopyLoop:
    PUSH_AF;
    LD_A_addr(wcd49);
    LD_L_A;
    LD_A_addr(wcd4a);
    LD_H_A;
    LD_BC(PARTYMON_STRUCT_LENGTH);
    CALL(aCopyBytes);
    LD_A_L;
    LD_addr_A(wcd49);
    LD_A_H;
    LD_addr_A(wcd4a);
    LD_A_addr(wcd4b);
    LD_L_A;
    LD_A_addr(wcd4c);
    LD_H_A;
    LD_BC(6);
    CALL(aCopyBytes);
    LD_A_L;
    LD_addr_A(wcd4b);
    LD_A_H;
    LD_addr_A(wcd4c);
    POP_AF;
    DEC_A;
    IF_NZ goto CopyLoop;

    LD_A(BANK(s4_a013));
    CALL(aOpenSRAM);
    LD_HL(s4_a013);
    LD_BC(36);
    CALL(aCopyBytes);
    CALL(aCloseSRAM);

    LD_A(BANK(s5_a894));  // aka BANK(s5_a948)
    CALL(aOpenSRAM);
    LD_HL(s5_a894);
    LD_BC(6);
    CALL(aCopyBytes);
    LD_HL(wc608);
    LD_DE(s5_a948);
    LD_BC(246);
    CALL(aCopyBytes);
    CALL(aCloseSRAM);
    RET;


DecToBin:
    LD_A_de;
    INC_DE;
    AND_A_A;
    RET_Z ;


digit_loop:
    ADD_HL_BC;
    DEC_A;
    IF_NZ goto digit_loop;
    RET;

}

void BattleTowerBattle(void){
    // XOR_A_A;  // FALSE
    // LD_addr_A(wBattleTowerBattleEnded);
    wram->wBattleTowerBattleEnded = FALSE;
    // CALL(av_BattleTowerBattle);
    v_BattleTowerBattle();
    // RET;
}

void UnusedBattleTowerDummySpecial1(void){
    // RET;

}

void InitBattleTowerChallengeRAM(void){
    // XOR_A_A;
    // LD_addr_A(wBattleTowerBattleEnded);
    wram->wBattleTowerBattleEnded = 0;
    // LD_addr_A(wNrOfBeatenBattleTowerTrainers);
    wram->wNrOfBeatenBattleTowerTrainers = 0;
    // LD_addr_A(wcf65);
    wram->wcf65 = 0;
    // LD_addr_A(wcf66);
    wram->wcf66 = 0;
    // RET;
}

void v_BattleTowerBattle(void){

    do {
    // loop:
        // CALL(av_BattleTowerBattle_do_dw);
        switch(wram->wJumptableIndex) {
        // dw:
            default:
            //dw ['RunBattleTowerTrainer'];
            case 0: RunBattleTowerTrainer(); break;
            //dw ['SkipBattleTowerTrainer'];
            case 1: SkipBattleTowerTrainer(); break;
        }
        // CALL(aDelayFrame);
        DelayFrame();
        // LD_A_addr(wBattleTowerBattleEnded);
        // CP_A(TRUE);
        // IF_NZ goto loop;
    } while(wram->wBattleTowerBattleEnded != TRUE);
    // RET;

// do_dw:
    //jumptable ['.dw', 'wBattleTowerBattleEnded']
}

void RunBattleTowerTrainer(void){
    // LD_A_addr(wOptions);
    // PUSH_AF;
    uint8_t options = wram->wOptions;
    // LD_HL(wOptions);
    // SET_hl(BATTLE_SHIFT);  // SET MODE
    bit_set(wram->wOptions, BATTLE_SHIFT);

    // LD_A_addr(wInBattleTowerBattle);
    // PUSH_AF;
    uint8_t inBattleTowerBattle = wram->wInBattleTowerBattle;
    // OR_A(1);
    // LD_addr_A(wInBattleTowerBattle);
    wram->wInBattleTowerBattle |= 1;

    // XOR_A_A;
    // LD_addr_A(wLinkMode);
    wram->wLinkMode = LINK_NULL;
    // FARCALL(aStubbedTrainerRankings_Healings);
    StubbedTrainerRankings_Healings();
    // FARCALL(aHealParty);
    HealParty();
    // CALL(aReadBTTrainerParty);
    ReadBTTrainerParty();
    // CALL(aClears5_a89a);
    Clears5_a89a();

    // PREDEF(pStartBattle);
    StartBattle_Conv();

    // FARCALL(aLoadPokemonData);
    LoadPokemonData();
    // FARCALL(aHealParty);
    HealParty();
    // LD_A_addr(wBattleResult);
    // LD_addr_A(wScriptVar);
    wram->wScriptVar = wram->wBattleResult;
    // AND_A_A;  // WIN?
    // IF_NZ goto lost;
    if(wram->wScriptVar == WIN) {
        // LD_A(BANK(sNrOfBeatenBattleTowerTrainers));
        // CALL(aOpenSRAM);
        OpenSRAM_Conv(MBANK(asNrOfBeatenBattleTowerTrainers));
        // LD_A_addr(sNrOfBeatenBattleTowerTrainers);
        // LD_addr_A(wNrOfBeatenBattleTowerTrainers);
        wram->wNrOfBeatenBattleTowerTrainers = gb_read(sNrOfBeatenBattleTowerTrainers);
        // CALL(aCloseSRAM);
        CloseSRAM_Conv();
        // LD_HL(wStringBuffer3);
        // LD_A_addr(wNrOfBeatenBattleTowerTrainers);
        // ADD_A(0xf7);
        // LD_hli_A;
        wram->wStringBuffer3[0] = wram->wNrOfBeatenBattleTowerTrainers + 0xf7; // CHAR_0
        // LD_A(0x50);
        // LD_hl_A;
        wram->wStringBuffer3[1] = 0x50;
    }

// lost:
    // POP_AF;
    // LD_addr_A(wInBattleTowerBattle);
    wram->wInBattleTowerBattle = inBattleTowerBattle;
    // POP_AF;
    // LD_addr_A(wOptions);
    wram->wOptions = options;
    // LD_A(TRUE);
    // LD_addr_A(wBattleTowerBattleEnded);
    wram->wBattleTowerBattleEnded = TRUE;
    // RET;
}

void ReadBTTrainerParty(void){
//  Initialise the BattleTower-Trainer and his mon
    // CALL(aCopyBTTrainer_FromBT_OT_TowBT_OTTemp);
    CopyBTTrainer_FromBT_OT_TowBT_OTTemp();

//  Check the nicknames for illegal characters, and replace bad nicknames
//  with their species names.
    struct BattleTowerPartyMon* pmon = wram->wBT_OTTemp.party;
    // LD_DE(wBT_OTTempMon1Name);
    // LD_C(MON_NAME_LENGTH);
    // FARCALL(aCheckStringForErrors);
    // IF_NC goto skip_mon_1;

    if(CheckStringForErrors_Conv(pmon[0].monName, MON_NAME_LENGTH)) {
        // LD_A_addr(wBT_OTTempMon1);
        // LD_addr_A(wNamedObjectIndex);
        // CALL(aGetPokemonName);
        // LD_L_E;
        // LD_H_D;
        // LD_DE(wBT_OTTempMon1Name);
        // LD_BC(MON_NAME_LENGTH);
        // CALL(aCopyBytes);
        CopyBytes(pmon[0].monName, GetPokemonName(pmon[0].mon.mon.species), MON_NAME_LENGTH);
    }

// skip_mon_1:
    // LD_DE(wBT_OTTempMon2Name);
    // LD_C(MON_NAME_LENGTH);
    // FARCALL(aCheckStringForErrors);
    // IF_NC goto skip_mon_2;
    if(CheckStringForErrors_Conv(pmon[1].monName, MON_NAME_LENGTH)) {
        // LD_A_addr(wBT_OTTempMon2);
        // LD_addr_A(wNamedObjectIndex);
        // CALL(aGetPokemonName);
        // LD_L_E;
        // LD_H_D;
        // LD_DE(wBT_OTTempMon2Name);
        // LD_BC(MON_NAME_LENGTH);
        // CALL(aCopyBytes);
        CopyBytes(pmon[1].monName, GetPokemonName(pmon[1].mon.mon.species), MON_NAME_LENGTH);
    }

// skip_mon_2:
    // LD_DE(wBT_OTTempMon3Name);
    // LD_C(MON_NAME_LENGTH);
    // FARCALL(aCheckStringForErrors);
    // IF_NC goto skip_mon_3;
    if(CheckStringForErrors_Conv(pmon[2].monName, MON_NAME_LENGTH)) {
        // LD_A_addr(wBT_OTTempMon3);
        // LD_addr_A(wNamedObjectIndex);
        // CALL(aGetPokemonName);
        // LD_L_E;
        // LD_H_D;
        // LD_DE(wBT_OTTempMon3Name);
        // LD_BC(MON_NAME_LENGTH);
        // CALL(aCopyBytes);
        CopyBytes(pmon[2].monName, GetPokemonName(pmon[2].mon.mon.species), MON_NAME_LENGTH);
    }

// skip_mon_3:
//  Add the terminator character to each of these names
    // LD_A(0x50);
    // LD_addr_A(wBT_OTTempMon1Name + MON_NAME_LENGTH - 1);
    pmon[0].monName[MON_NAME_LENGTH - 1] = 0x50;
    // LD_addr_A(wBT_OTTempMon2Name + MON_NAME_LENGTH - 1);
    pmon[1].monName[MON_NAME_LENGTH - 1] = 0x50;
    // LD_addr_A(wBT_OTTempMon3Name + MON_NAME_LENGTH - 1);
    pmon[2].monName[MON_NAME_LENGTH - 1] = 0x50;
//  Fix errors in the movesets
    // CALL(aCheckBTMonMovesForErrors);
    CheckBTMonMovesForErrors_Conv();
//  Repair the trainer name if needed, then copy it to wOTPlayerName
    // LD_DE(wBT_OTTempName);
    // LD_C(NAME_LENGTH - 1);
    // FARCALL(aCheckStringForErrors);
    // IF_NC goto trainer_name_okay;
    if(CheckStringForErrors_Conv(wram->wBT_OTTemp.name, NAME_LENGTH - 1)) {
        // LD_HL(mBT_ChrisName);
        CopyBytes(wram->wOTPlayerName, U82C(BT_ChrisName), NAME_LENGTH - 1);
        // goto done_trainer_name;
    }
    else {
    // trainer_name_okay:
        // LD_HL(wBT_OTTempName);
        CopyBytes(wram->wOTPlayerName, wram->wBT_OTTemp.name, NAME_LENGTH - 1);
    }

// done_trainer_name:
    // LD_DE(wOTPlayerName);
    // LD_BC(NAME_LENGTH - 1);
    // CALL(aCopyBytes);
    // LD_A(0x50);
    // LD_de_A;
    wram->wOTPlayerName[NAME_LENGTH - 1] = 0x50;

    // LD_HL(wBT_OTTempTrainerClass);
    // LD_A_hli;
    // LD_addr_A(wOtherTrainerClass);
    wram->wOtherTrainerClass = wram->wBT_OTTemp.trainerClass;
    // LD_A(LOW(wOTPartyMonNicknames));
    // LD_addr_A(wBGMapBuffer);
    // LD_A(HIGH(wOTPartyMonNicknames));
    // LD_addr_A(wBGMapBuffer + 1);
    CopyBytes(wram->wOTPartyMonNickname[0], wram->wBT_OTTemp.party[0].monName, NAME_LENGTH);
    CopyBytes(wram->wOTPartyMonNickname[1], wram->wBT_OTTemp.party[1].monName, NAME_LENGTH);
    CopyBytes(wram->wOTPartyMonNickname[2], wram->wBT_OTTemp.party[2].monName, NAME_LENGTH);

// Copy mon into Memory from the address in hl
    struct BattleTowerPartyMon* hl = wram->wBT_OTTemp.party;
    // LD_DE(wOTPartyMon1Species);
    struct PartyMon* de = wram->wOTPartyMon;
    // LD_BC(wOTPartyCount);
    // LD_A(BATTLETOWER_PARTY_LENGTH);
    // LD_bc_A;
    uint8_t count = wram->wOTPartyCount = BATTLETOWER_PARTY_LENGTH;
    // INC_BC;
    species_t* bc = wram->wOTPartySpecies;

    do {
    // otpartymon_loop:
        // PUSH_AF;
        // LD_A_hl;
        // LD_bc_A;
        // INC_BC;
        *(bc++) = hl->mon.mon.species;
        // PUSH_BC;
        // LD_BC(PARTYMON_STRUCT_LENGTH);
        // CALL(aCopyBytes);
        CopyBytes(de, &hl->mon, sizeof(*de));
        // PUSH_DE;
        // LD_A_addr(wBGMapBuffer);
        // LD_E_A;
        // LD_A_addr(wBGMapBuffer + 1);
        // LD_D_A;
        de++;
        hl++;
        // LD_BC(MON_NAME_LENGTH);
        // CALL(aCopyBytes);
        // LD_A_E;
        // LD_addr_A(wBGMapBuffer);
        // LD_A_D;
        // LD_addr_A(wBGMapBuffer + 1);
        // POP_DE;
        // POP_BC;
        // POP_AF;
        // DEC_A;
        // AND_A_A;
        // IF_NZ goto otpartymon_loop;
    } while(--count != 0);
    // LD_A(-1);
    // LD_bc_A;
    *bc = (species_t)-1;
    // RET;
}

void ValidateBTParty(void){
//  //  unreferenced
//  Check for and fix errors in party data
    LD_HL(wBT_OTTempMon1Species);
    LD_D(BATTLETOWER_PARTY_LENGTH);

pkmn_loop:
    PUSH_DE;
    PUSH_HL;
    LD_B_H;
    LD_C_L;
    LD_A_hl;
    AND_A_A;
    // for(int x = 0; x < 0xff, NUM_POKEMON, -1; x++){
    // IF_Z goto invalid;
    // CP_A(x);
    // }
    IF_NZ goto valid;


invalid:
    LD_A(SMEARGLE);
    LD_hl_A;


valid:
    LD_addr_A(wCurSpecies);
    CALL(aGetBaseData);
    LD_A(BANK(s5_b2fb));
    CALL(aOpenSRAM);
    LD_A_addr(s5_b2fb);  // s5_b2fb // max level?
    CALL(aCloseSRAM);
    LD_E_A;
    LD_HL(MON_LEVEL);
    ADD_HL_BC;
    LD_A_hl;
    CP_A(MIN_LEVEL);
    LD_A(MIN_LEVEL);
    IF_C goto load;
    LD_A_hl;
    CP_A_E;
    IF_C goto dont_load;
    LD_A_E;


load:
    LD_hl_A;


dont_load:
    LD_addr_A(wCurPartyLevel);
    LD_HL(MON_MOVES);
    ADD_HL_BC;
    LD_D(NUM_MOVES - 1);
    LD_A_hli;
    AND_A_A;
    IF_Z goto not_move;
    CP_A(NUM_ATTACKS + 1);
    IF_NC goto not_move;
    goto valid_move;


not_move:
    DEC_HL;
    LD_A(POUND);
    LD_hli_A;
    XOR_A_A;
    LD_hli_A;
    LD_hli_A;
    LD_hl_A;
    goto done_moves;


valid_move:
    LD_A_hl;
    CP_A(NUM_ATTACKS + 1);
    IF_C goto next;
    LD_hl(0x0);


next:
    INC_HL;
    DEC_D;
    IF_NZ goto valid_move;


done_moves:
    LD_HL(MON_MAXHP);
    ADD_HL_BC;
    LD_D_H;
    LD_E_L;
    PUSH_HL;
    PUSH_DE;
    LD_HL(MON_STAT_EXP - 1);
    ADD_HL_BC;
    LD_B(TRUE);
    PREDEF(pCalcMonStats);
    POP_DE;
    POP_HL;
    DEC_DE;
    DEC_DE;
    LD_A_hli;
    LD_de_A;
    INC_DE;
    LD_A_hl;
    LD_de_A;
    POP_HL;
    LD_BC(NICKNAMED_MON_STRUCT_LENGTH);
    ADD_HL_BC;
    POP_DE;
    DEC_D;
    JP_NZ (mValidateBTParty_pkmn_loop);
    RET;

}

const char BT_ChrisName[] = "CHRIS@";

void Function17042c(void){
    LD_HL(w3_d202TrainerData);
    LD_A(BATTLETOWER_STREAK_LENGTH);

loop:
    PUSH_AF;
    PUSH_HL;
    LD_C(BATTLETOWER_TRAINERDATALENGTH / 2);

loop2:
// First byte is a comparison value.
    LD_A_hli;
    LD_B_A;
// Second byte is a lookup index.
    LD_A_hli;
    AND_A_A;
    IF_Z goto empty;
    CP_A(15);
    IF_NC goto copy_data;

    PUSH_HL;
    LD_HL(mUnknown_170470);
    DEC_A;
    LD_E_A;
    LD_D(0);
    ADD_HL_DE;
    LD_A_hl;
    POP_HL;

// If Unknown_170470[a-1] <= b, overwrite the current trainer's data
// with Unknown17047e, and exit the inner loop.
    CP_A_B;
    IF_C goto copy_data;
    IF_Z goto copy_data;
    goto next_iteration;


empty:
// If a == 0 and b >= $fc, overwrite the current trainer's data with
// Unknown17047e, and exit the inner loop.
    LD_A_B;
    CP_A(0xfc);
    IF_NC goto copy_data;


next_iteration:
    DEC_C;
    IF_NZ goto loop2;
    goto next_trainer;


copy_data:
    POP_DE;
    PUSH_DE;
    LD_HL(mUnknown_17047e);
    LD_BC(BATTLETOWER_TRAINERDATALENGTH);
    CALL(aCopyBytes);


next_trainer:
    POP_HL;
    LD_DE(BATTLE_TOWER_STRUCT_LENGTH);
    ADD_HL_DE;
    POP_AF;
    DEC_A;
    IF_NZ goto loop;
    RET;

// INCLUDE "data/battle_tower/unknown_levels.asm"

    return CopyBTTrainer_FromBT_OT_TowBT_OTTemp();
}

//  copy the BattleTower-Trainer data that lies at 'wBT_OTTrainer' to 'wBT_OTTemp'
void CopyBTTrainer_FromBT_OT_TowBT_OTTemp(void){
    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    // LD_A(BANK(wBT_OTTrainer));
    // LDH_addr_A(rSVBK);

    // LD_HL(wBT_OTTrainer);
    // LD_DE(wBT_OTTemp);
    // LD_BC(BATTLE_TOWER_STRUCT_LENGTH);
    // CALL(aCopyBytes);
    CopyBytes(&wram->wBT_OTTemp, &wram->wBT_OTTrainer, sizeof(wram->wBT_OTTemp));

    // POP_AF;
    // LDH_addr_A(rSVBK);

    // LD_A(BANK(sBattleTowerChallengeState));
    // CALL(aOpenSRAM);
    OpenSRAM_Conv(MBANK(asBattleTowerChallengeState));
    // LD_A(BATTLETOWER_CHALLENGE_IN_PROGRESS);
    // LD_addr_A(sBattleTowerChallengeState);
    gb_write(sBattleTowerChallengeState, BATTLETOWER_CHALLENGE_IN_PROGRESS);
    // LD_HL(sNrOfBeatenBattleTowerTrainers);
    // INC_hl;
    gb_write(sNrOfBeatenBattleTowerTrainers, gb_read(sNrOfBeatenBattleTowerTrainers) + 1);
    // CALL(aCloseSRAM);
    CloseSRAM_Conv();
    return SkipBattleTowerTrainer();
}

void SkipBattleTowerTrainer(void){
    // RET;

}

void Function1704ca(void){
//  //  unreferenced
    LD_A_addr(s5_be46);
    CP_A(BATTLETOWER_STREAK_LENGTH);
    IF_C goto not_max;
    LD_A(BATTLETOWER_STREAK_LENGTH - 1);


not_max:
    LD_HL(s5_aa8e + BATTLE_TOWER_STRUCT_LENGTH * (BATTLETOWER_STREAK_LENGTH - 1));
    LD_DE(-BATTLE_TOWER_STRUCT_LENGTH);

loop:
    AND_A_A;
    IF_Z goto done;
    ADD_HL_DE;
    DEC_A;
    goto loop;


done:
    RET;

}

void Function1704e1(void){
    CALL(aSpeechTextbox);
    CALL(aFadeToMenu);
    CALL(aInitBattleTowerChallengeRAM);
    CALL(aFunction1704e1_JumptableLoop);
    CALL(aCloseSubmenu);
    RET;


JumptableLoop:
    CALL(aClearBGPalettes);
    CALL(aClearSprites);
    CALL(aClearScreen);

loop:
    CALL(aJoyTextDelay);
    LD_A_addr(wJumptableIndex);
    BIT_A(7);
    IF_NZ goto done;
    CALL(aFunction1704e1_DoJumptable);
    FARCALL(aReloadMapPart);
    goto loop;


done:
    RET;


DoJumptable:
    //jumptable ['.dw', 'wJumptableIndex']


dw:
    //dw ['.Jumptable_0'];
    //dw ['.Jumptable_1'];
    //dw ['.Jumptable_2'];


Jumptable_0:
    LD_A(BANK(s5_a89c));
    CALL(aOpenSRAM);

    LD_HL(s5_a89c);
    LD_DE(wStringBuffer3);
    LD_BC(22);
    CALL(aCopyBytes);

    LD_HL(s5_a8b2);
    LD_DE(wc608);
    LD_BC(150);
    CALL(aCopyBytes);

    CALL(aCloseSRAM);
    hlcoord(1, 1, wTilemap);
    LD_DE(wStringBuffer3);
    CALL(aPlaceString);
    hlcoord(1, 3, wTilemap);
    LD_DE(mFunction1704e1_String_Mail);
    CALL(aPlaceString);
    hlcoord(4, 3, wTilemap);
    LD_DE(wStringBuffer4);
    CALL(aPlaceString);
    hlcoord(8, 3, wTilemap);
    LD_DE(mFunction1704e1_String_PastReaders);
    CALL(aPlaceString);
    CALL(aFunction1704e1_DrawBorder);
    CALL(aFunction1704e1_PlaceTextItems);
    goto NextJumptableFunction;


Jumptable_1:
    CALL(aSetPalettes);
    CALL(aFunction1704e1_NextJumptableFunction);


Jumptable_2:
    LD_HL(hJoyPressed);
    LD_A_hl;
    AND_A(A_BUTTON);
    IF_NZ goto pressed_a_or_b;
    LD_A_hl;
    AND_A(B_BUTTON);
    IF_NZ goto pressed_a_or_b;
    LD_A_hl;
    AND_A(D_UP);
    IF_NZ goto pressed_up;
    LD_A_hl;
    AND_A(D_DOWN);
    IF_NZ goto pressed_down;
    RET;


pressed_up:
    LD_A_addr(wNrOfBeatenBattleTowerTrainers);
    AND_A_A;
    RET_Z ;
    SUB_A(15);
    LD_addr_A(wNrOfBeatenBattleTowerTrainers);
    CALL(aFunction1704e1_PlaceTextItems);
    RET;


pressed_down:
    LD_A_addr(wNrOfBeatenBattleTowerTrainers);
    CP_A(60);
    RET_Z ;
    ADD_A(15);
    LD_addr_A(wNrOfBeatenBattleTowerTrainers);
    CALL(aFunction1704e1_PlaceTextItems);
    RET;


pressed_a_or_b:
    LD_HL(wJumptableIndex);
    SET_hl(7);
    RET;


NextJumptableFunction:
    LD_HL(wJumptableIndex);
    INC_hl;
    RET;


DrawBorder:
    hlcoord(0, 4, wTilemap);
    LD_A(0x79);
    LD_hli_A;
    LD_C(SCREEN_WIDTH - 2);

top_border_loop:
    LD_A(0x7a);
    LD_hli_A;
    DEC_C;
    IF_NZ goto top_border_loop;
    LD_A(0x7b);
    LD_hli_A;
    LD_DE(SCREEN_WIDTH);
    LD_C(12);

left_border_loop:
    LD_A(0x7c);
    LD_hl_A;
    ADD_HL_DE;
    DEC_C;
    IF_NZ goto left_border_loop;
    LD_A(0x7d);
    LD_hli_A;
    LD_C(SCREEN_WIDTH - 2);

bottom_border_loop:
    LD_A(0x7a);
    LD_hli_A;
    DEC_C;
    IF_NZ goto bottom_border_loop;
    LD_A(0x7e);
    LD_hl_A;
    LD_DE(-SCREEN_WIDTH);
    ADD_HL_DE;
    LD_C(12);

right_border_loop:
    LD_A(0x7c);
    LD_hl_A;
    ADD_HL_DE;
    DEC_C;
    IF_NZ goto right_border_loop;
    RET;


PlaceTextItems:
    CALL(aFunction1704e1_ClearBox);
    CALL(aFunction1704e1_PlaceUpDownArrows);
    LD_A(0x50);
    LD_addr_A(wcd4e);
    LD_HL(wc608);
    LD_A_addr(wNrOfBeatenBattleTowerTrainers);
    LD_C_A;
    XOR_A_A;
    LD_B_A;
    ADD_HL_BC;
    PUSH_HL;
    POP_BC;
    hlcoord(1, 6, wTilemap);
    LD_A(6);

loop1:
    PUSH_AF;
    PUSH_HL;
    LD_A(3);

loop2:
    PUSH_AF;
    LD_DE(wcd49);
    LD_A_bc;
    AND_A_A;
    IF_Z goto fill_with_e3;
//  .copy
    LD_A(5);

loop3a:
    PUSH_AF;
    LD_A_bc;
    LD_de_A;
    INC_BC;
    INC_DE;
    POP_AF;
    DEC_A;
    IF_NZ goto loop3a;
    goto rejoin;


fill_with_e3:
    LD_A(5);

loop3b:
    PUSH_AF;
    LD_A(0xe3);
    LD_de_A;
    INC_DE;
    INC_BC;
    POP_AF;
    DEC_A;
    IF_NZ goto loop3b;


rejoin:
    LD_DE(wcd49);
    PUSH_BC;
    CALL(aPlaceString);
    LD_DE(NAME_LENGTH_JAPANESE);
    ADD_HL_DE;
    POP_BC;
    POP_AF;
    DEC_A;
    IF_NZ goto loop2;
    POP_HL;
    LD_DE(0x28);
    ADD_HL_DE;
    POP_AF;
    DEC_A;
    IF_NZ goto loop1;
    RET;


ClearBox:
    hlcoord(1, 5, wTilemap);
    XOR_A_A;
    LD_B(12);

clearbox_row:
    LD_C(SCREEN_WIDTH - 2);

clearbox_column:
    LD_hli_A;
    DEC_C;
    IF_NZ goto clearbox_column;
    INC_HL;
    INC_HL;
    DEC_B;
    IF_NZ goto clearbox_row;
    RET;


PlaceUpDownArrows:
    LD_A_addr(wNrOfBeatenBattleTowerTrainers);
    AND_A_A;
    IF_Z goto nope;
    hlcoord(18, 5, wTilemap);
    LD_A(0x61);
    LD_hl_A;


nope:
    LD_A_addr(wNrOfBeatenBattleTowerTrainers);
    CP_A(60);
    RET_Z ;
    hlcoord(18, 16, wTilemap);
    LD_A(0xee);
    LD_hl_A;
    RET;


String_Mail:
    //db ['"ルーム@"'];


String_PastReaders:
    //db ['"れきだいりーダーいちらん@"'];

    return BattleTowerAction();
}

void BattleTowerAction(void){
    //jumptable ['.dw', 'wScriptVar']


// dw:
    switch(wram->wScriptVar) {
        //dw ['BattleTowerAction_CheckExplanationRead'];
    case BATTLETOWERACTION_CHECK_EXPLANATION_READ: return BattleTowerAction_CheckExplanationRead();
        //dw ['BattleTowerAction_SetExplanationRead'];
    case BATTLETOWERACTION_SET_EXPLANATION_READ: return BattleTowerAction_SetExplanationRead();
        //dw ['BattleTowerAction_GetChallengeState'];
    case BATTLETOWERACTION_GET_CHALLENGE_STATE: return BattleTowerAction_GetChallengeState();
        //dw ['BattleTowerAction_SetByteToQuickSaveChallenge'];
    case BATTLETOWERACTION_SAVE_AND_QUIT: return BattleTowerAction_SetByteToQuickSaveChallenge();
        //dw ['BattleTowerAction_SetByteToCancelChallenge'];
    case BATTLETOWERACTION_CHALLENGECANCELED: return BattleTowerAction_SetByteToCancelChallenge();
        //dw ['Function1707ac'];
    case BATTLETOWERACTION_05: return Function1707ac();
        //dw ['Function1707f4'];
    case BATTLETOWERACTION_06: return Function1707f4();
        //dw ['SaveBattleTowerLevelGroup'];
    case BATTLETOWERACTION_SAVELEVELGROUP: return SaveBattleTowerLevelGroup();
        //dw ['LoadBattleTowerLevelGroup'];
    case BATTLETOWERACTION_LOADLEVELGROUP: return LoadBattleTowerLevelGroup();
        //dw ['BattleTower_CheckSaveFileExistsAndIsYours'];
    case BATTLETOWERACTION_CHECKSAVEFILEISYOURS: return BattleTower_CheckSaveFileExistsAndIsYours();
        //dw ['Function1708b1'];
    case BATTLETOWERACTION_0A: return Function1708b1();
        //dw ['CheckMobileEventIndex'];
    case BATTLETOWERACTION_CHECKMOBILEEVENT: return CheckMobileEventIndex();
        //dw ['Function1708c8'];
        //dw ['Function1708f0'];
        //dw ['BattleTowerAction_EggTicket'];
        //dw ['Function1709aa'];
        //dw ['Function1709bb'];
        //dw ['Function170a9c'];
        //dw ['Function170aa0'];
        //dw ['Function170aaf'];
        //dw ['Function170abe'];
        //dw ['Function170ad7'];
        //dw ['Function170807'];
        //dw ['Function17081d'];
        //dw ['BattleTowerAction_LevelCheck'];
        //dw ['BattleTowerAction_UbersCheck'];
        //dw ['ResetBattleTowerTrainersSRAM'];
    case BATTLETOWERACTION_RESETDATA: return ResetBattleTowerTrainersSRAM();
        //dw ['BattleTower_GiveReward'];
        //dw ['Function17071b'];
        //dw ['Function170729'];
        //dw ['BattleTower_RandomlyChooseReward'];
        //dw ['BattleTower_SaveOptions'];
    }
//  Reset the save memory for BattleTower-Trainers (Counter and all 7 TrainerBytes)
}

void ResetBattleTowerTrainersSRAM(void){
    // LD_A(BANK(sBTTrainers));
    // CALL(aOpenSRAM);
    OpenSRAM_Conv(MBANK(asBTTrainers));

    // LD_A(0xff);
    // LD_HL(sBTTrainers);
    // LD_BC(BATTLETOWER_STREAK_LENGTH);
    // CALL(aByteFill);
    ByteFill_GB(sBTTrainers, BATTLETOWER_STREAK_LENGTH, 0xff);

    // XOR_A_A;
    // LD_addr_A(sNrOfBeatenBattleTowerTrainers);
    gb_write(sNrOfBeatenBattleTowerTrainers, 0);

    // CALL(aCloseSRAM);
    CloseSRAM_Conv();

    // RET;
}

void BattleTower_GiveReward(void){
    LD_A(BANK(sBattleTowerReward));
    CALL(aOpenSRAM);

    LD_A_addr(sBattleTowerReward);
    CALL(aCloseSRAM);
    LD_addr_A(wScriptVar);
    LD_HL(wNumItems);
    LD_A_hli;
    CP_A(MAX_ITEMS);
    RET_C ;
    LD_B(MAX_ITEMS);
    LD_A_addr(wScriptVar);
    LD_C_A;

loop:
    LD_A_hli;
    CP_A_C;
    IF_NZ goto next;
    LD_A_hl;
    CP_A(95);
    RET_C ;

next:
    INC_HL;
    DEC_B;
    IF_NZ goto loop;
    LD_A(POTION);
    LD_addr_A(wScriptVar);
    RET;

}

void Function17071b(void){
    LD_A(BANK(sBattleTowerChallengeState));
    CALL(aOpenSRAM);
    LD_A(BATTLETOWER_WON_CHALLENGE);
    LD_addr_A(sBattleTowerChallengeState);
    CALL(aCloseSRAM);
    RET;

}

void Function170729(void){
    LD_A(BANK(sBattleTowerChallengeState));
    CALL(aOpenSRAM);
    LD_A(BATTLETOWER_RECEIVED_REWARD);
    LD_addr_A(sBattleTowerChallengeState);
    CALL(aCloseSRAM);
    RET;

}

void BattleTower_SaveOptions(void){
    FARCALL(aSaveOptions);
    RET;

}

void BattleTower_RandomlyChooseReward(void){
//  Generate a random stat boosting item.

loop:
    CALL(aRandom);
    LDH_A_addr(hRandomAdd);
    AND_A(0x7);
    CP_A(6);
    IF_C goto okay;
    SUB_A(6);

okay:
    ADD_A(HP_UP);
    CP_A(LUCKY_PUNCH);
    IF_Z goto loop;
    PUSH_AF;
    LD_A(BANK(sBattleTowerReward));
    CALL(aOpenSRAM);
    POP_AF;
    LD_addr_A(sBattleTowerReward);
    CALL(aCloseSRAM);
    RET;

}

void BattleTowerAction_CheckExplanationRead(void){
    // CALL(aBattleTower_CheckSaveFileExistsAndIsYours);
    BattleTower_CheckSaveFileExistsAndIsYours();
    // LD_A_addr(wScriptVar);
    // AND_A_A;
    // RET_Z ;
    if(!wram->wScriptVar)
        return;

    // LD_A(BANK(sBattleTowerSaveFileFlags));
    // CALL(aOpenSRAM);
    OpenSRAM_Conv(MBANK(asBattleTowerSaveFileFlags));
    // LD_A_addr(sBattleTowerSaveFileFlags);
    // AND_A(2);
    // LD_addr_A(wScriptVar);
    wram->wScriptVar = gb_read(sBattleTowerSaveFileFlags) & 2;
    // CALL(aCloseSRAM);
    CloseSRAM_Conv();
    // RET;

}

void BattleTowerAction_GetChallengeState(void){
    // LD_HL(sBattleTowerChallengeState);
    // LD_A(BANK(sBattleTowerChallengeState));
    // CALL(aOpenSRAM);
    OpenSRAM_Conv(MBANK(asBattleTowerChallengeState));
    // LD_A_hl;
    // LD_addr_A(wScriptVar);
    wram->wScriptVar = gb_read(sBattleTowerChallengeState);
    // CALL(aCloseSRAM);
    CloseSRAM_Conv();
    // RET;

}

void BattleTowerAction_SetExplanationRead(void){
    // LD_A(BANK(sBattleTowerSaveFileFlags));
    // CALL(aOpenSRAM);
    OpenSRAM_Conv(MBANK(asBattleTowerSaveFileFlags));
    // LD_A_addr(sBattleTowerSaveFileFlags);
    // OR_A(2);
    // LD_addr_A(sBattleTowerSaveFileFlags);
    gb_write(sBattleTowerSaveFileFlags, gb_read(sBattleTowerSaveFileFlags) | 2);
    // CALL(aCloseSRAM);
    CloseSRAM_Conv();
    // RET;

}

void BattleTowerAction_SetByteToQuickSaveChallenge(void){
    // LD_C(BATTLETOWER_SAVED_AND_LEFT);
    // JR(mSetBattleTowerChallengeState);
    return SetBattleTowerChallengeState(BATTLETOWER_SAVED_AND_LEFT);
}

void BattleTowerAction_SetByteToCancelChallenge(void){
    // LD_C(BATTLETOWER_NO_CHALLENGE);
    return SetBattleTowerChallengeState(BATTLETOWER_NO_CHALLENGE);
}

void SetBattleTowerChallengeState(uint8_t c){
    // LD_A(BANK(sBattleTowerChallengeState));
    // CALL(aOpenSRAM);
    OpenSRAM_Conv(MBANK(asBattleTowerChallengeState));
    // LD_A_C;
    // LD_addr_A(sBattleTowerChallengeState);
    gb_write(sBattleTowerChallengeState, c);
    // CALL(aCloseSRAM);
    CloseSRAM_Conv();
    // RET;

}

void Function1707ac(void){
    // LD_A(BANK(s5_aa8c));  // aka BANK(s5_be46)
    // CALL(aOpenSRAM);
    OpenSRAM_Conv(MBANK(as5_aa8c));
    // LD_A_addr(s5_aa8c);
    // LD_B_A;
    uint8_t b = gb_read(s5_aa8c);
    // LD_A_addr(s5_be46);
    // LD_addr_A(wScriptVar);
    wram->wScriptVar = gb_read(s5_be46);
    // CALL(aCloseSRAM);
    CloseSRAM_Conv();
    // AND_A_A;
    // RET_Z ;
    if(!wram->wScriptVar)
        return;
    // LD_A_B;
    // CP_A(2);
    // IF_NC goto asm_1707ef;
    if(b < 2) {
        // PUSH_BC;
        // CALL(aUpdateTime);
        UpdateTime_Conv();
        // POP_BC;
        // LD_A(BANK(s5_aa8c));
        // CALL(aOpenSRAM);
        OpenSRAM_Conv(MBANK(as5_aa8c));
        // LD_A_addr(s5_aa8b);
        uint8_t c = gb_read(s5_aa8b);
        // CALL(aCloseSRAM);
        CloseSRAM_Conv();
        // LD_C_A;
        // LD_A_addr(wCurDay);
        uint8_t day = wram->wCurDay;
        // SUB_A_C;
        // IF_C goto asm_1707e5;
        if(day >= c) {
            day -= c;
            // CP_A(8);
            // IF_NC goto asm_1707ef;
            // LD_A_B;
            // AND_A_A;
            // IF_NZ goto asm_1707ef;
            if(day < 8 && b != 0)
                return;
            // RET;
        }
        else {
        // asm_1707e5:
            // LD_HL(wCurDay);
            // LD_A(0x8c);
            // SUB_A_C;
            // ADD_A_hl;
            day = (0x8c - c) + wram->wCurDay;
            // CP_A(8);
            // RET_C ;
            if(day < 8)
                return;
        }
    }

// asm_1707ef:
    // LD_A(8);
    // LD_addr_A(wScriptVar);
    wram->wScriptVar = 8;

    return Function1707f4();
}

void Function1707f4(void){
    // LD_A(BANK(s5_be46));  // aka BANK(s5_aa8b) and BANK(s5_aa8c)
    // CALL(aOpenSRAM);
    OpenSRAM_Conv(MBANK(as5_be46));
    // XOR_A_A;
    // LD_addr_A(s5_be46);
    gb_write(s5_be46, 0);
    // LD_addr_A(s5_aa8b);
    // LD_addr_A(s5_aa8c);
    gb_write16(s5_aa8b, 0);
    // CALL(aCloseSRAM);
    CloseSRAM_Conv();
    // RET;

}

void Function170807(void){
    CALL(aUpdateTime);
    LD_A(BANK(s5_b2f9));  // aka BANK(s5_b2fa)
    CALL(aOpenSRAM);
    LD_A_addr(wCurDay);
    LD_addr_A(s5_b2f9);
    XOR_A_A;
    LD_addr_A(s5_b2fa);
    CALL(aCloseSRAM);
    RET;

}

void Function17081d(void){
    XOR_A_A;
    LD_addr_A(wScriptVar);
    LD_A(BANK(s5_b2f9));  // aka BANK(s5_b2fa)
    CALL(aOpenSRAM);
    LD_A_addr(s5_b2f9);
    LD_C_A;
    LD_A_addr(s5_b2fa);
    LD_B_A;
    CALL(aCloseSRAM);
    CP_A(2);
    IF_NC goto asm_170853;
    PUSH_BC;
    CALL(aUpdateTime);
    POP_BC;
    LD_A_addr(wCurDay);
    SUB_A_C;
    IF_C goto asm_170849;
    CP_A(11);
    IF_NC goto asm_170853;
    LD_A_B;
    AND_A_A;
    IF_NZ goto asm_170853;
    RET;


asm_170849:
    LD_HL(wCurDay);
    LD_A(140);
    SUB_A_C;
    ADD_A_hl;
    CP_A(11);
    RET_C ;

asm_170853:
    LD_A(1);
    LD_addr_A(wScriptVar);
    LD_A(BANK(s5_b2f9));  // aka BANK(s5_b2fa)
    CALL(aOpenSRAM);
    XOR_A_A;
    LD_addr_A(s5_b2f9);
    LD_addr_A(s5_b2fa);
    CALL(aCloseSRAM);
    RET;

}

void SaveBattleTowerLevelGroup(void){
    // LD_A(BANK(sBTChoiceOfLevelGroup));
    // CALL(aOpenSRAM);
    OpenSRAM_Conv(MBANK(asBTChoiceOfLevelGroup));
    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    // LD_A(BANK(wBTChoiceOfLvlGroup));
    // LDH_addr_A(rSVBK);
    // LD_A_addr(wBTChoiceOfLvlGroup);
    // LD_addr_A(sBTChoiceOfLevelGroup);
    gb_write(sBTChoiceOfLevelGroup, wram->wBTChoiceOfLvlGroup);
    // POP_AF;
    // LDH_addr_A(rSVBK);
    // CALL(aCloseSRAM);
    CloseSRAM_Conv();
    // RET;
}

//  //  Load level group choice
void LoadBattleTowerLevelGroup(void){
    // LD_A(BANK(sBTChoiceOfLevelGroup));
    // CALL(aOpenSRAM);
    OpenSRAM_Conv(MBANK(asBTChoiceOfLevelGroup));
    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    // LD_A(BANK(wBTChoiceOfLvlGroup));
    // LDH_addr_A(rSVBK);
    // LD_A_addr(sBTChoiceOfLevelGroup);
    // LD_addr_A(wBTChoiceOfLvlGroup);
    wram->wBTChoiceOfLvlGroup = gb_read(sBTChoiceOfLevelGroup);
    // POP_AF;
    // LDH_addr_A(rSVBK);
    // CALL(aCloseSRAM);
    CloseSRAM_Conv();
    // RET;

}

void BattleTower_CheckSaveFileExistsAndIsYours(void){
    // LD_A_addr(wSaveFileExists);
    // AND_A_A;
    // IF_Z goto nope;
    // FARCALL(aCompareLoadedAndSavedPlayerID);
    // IF_Z goto yes;
    if(wram->wSaveFileExists && CompareLoadedAndSavedPlayerID()) {
    // yes:
        // LD_A(TRUE);
        wram->wScriptVar = TRUE;
        return;
    }
    // XOR_A_A;  // FALSE
    // goto nope;


// nope:
    // LD_addr_A(wScriptVar);
    wram->wScriptVar = FALSE;
    // RET;
}

//  //  BattleTowerAction $0a
void Function1708b1(void){
    // XOR_A_A;
    // LD_addr_A(wMusicFade);
    wram->wMusicFade = 0x0;
    // CALL(aMaxVolume);
    MaxVolume();
    // RET;

}

//  //  BattleTowerAction $0b something to do with GS Ball
void CheckMobileEventIndex(void){
    // LD_A(BANK(sMobileEventIndex));
    // CALL(aOpenSRAM);
    OpenSRAM_Conv(MBANK(asMobileEventIndex));
    // LD_A_addr(sMobileEventIndex);
    // LD_addr_A(wScriptVar);
    wram->wScriptVar = gb_read(sMobileEventIndex);
    // CALL(aCloseSRAM);
    CloseSRAM_Conv();
    // RET;
}

void Function1708c8(void){
//  //  BattleTowerAction $0c
    CALL(aUpdateTime);
    LD_A(BANK(s5_aa8b));  // aka BANK(s5_aa8c), BANK(s5_aa5d), BANK(s5_aa48), and BANK(s5_aa47)
    CALL(aOpenSRAM);
    LD_A_addr(wCurDay);
    LD_addr_A(s5_aa8b);
    XOR_A_A;
    LD_addr_A(s5_aa8c);
    LD_A_addr(s5_aa5d);
    CP_A(2);
    IF_NC goto asm_1708ec;
    LD_A_addr(wCurDay);
    LD_addr_A(s5_aa48);
    LD_A(1);
    LD_addr_A(s5_aa47);

asm_1708ec:
    CALL(aCloseSRAM);
    RET;

}

void Function1708f0(void){
//  //  BattleTowerAction $0d
    XOR_A_A;  // FALSE
    LD_addr_A(wScriptVar);
    CALL(aUpdateTime);
    LD_A(BANK(s5_aa48));  // aka BANK(s5_aa47)
    CALL(aOpenSRAM);
    LD_A_addr(s5_aa48);
    LD_C_A;
    LD_A_addr(s5_aa47);
    CALL(aCloseSRAM);
    AND_A_A;
    RET_Z ;
    LD_HL(wCurDay);
    LD_A_C;
    CP_A_hl;
    JR_NZ (mFunction170923);
    LD_A(BANK(s5_aa5d));
    CALL(aOpenSRAM);
    LD_A_addr(s5_aa5d);
    CALL(aCloseSRAM);
    CP_A(5);
    RET_C ;
    LD_A(TRUE);
    LD_addr_A(wScriptVar);
    RET;

}

void Function170923(void){
    // LD_A(BANK(s5_aa48));  // aka BANK(s5_aa47) and BANK(s5_aa5d)
    // CALL(aOpenSRAM);
    OpenSRAM_Conv(MBANK(as5_aa48));
    // XOR_A_A;
    // LD_addr_A(s5_aa48);
    gb_write(s5_aa48, 0);
    // LD_addr_A(s5_aa47);
    gb_write(s5_aa47, 0);
    // LD_HL(s5_aa5d);
    uint8_t* hl = GBToRAMAddr(s5_aa5d);
    // LD_BC(MOBILE_LOGIN_PASSWORD_LENGTH);
    // CALL(aByteFill);
    ByteFill(hl, MOBILE_LOGIN_PASSWORD_LENGTH, 0);
    // CALL(aCloseSRAM);
    CloseSRAM_Conv();
    // RET;
}

void BattleTowerAction_EggTicket(void){
//  //  BattleTowerAction $0e
    XOR_A_A;  // FALSE
    LD_addr_A(wScriptVar);
    LD_A(EGG_TICKET);
    LD_addr_A(wCurItem);
    LD_HL(wNumItems);
    CALL(aCheckItem);
    RET_NC ;
    LD_A_addr(wPartyCount);
    LD_B(0);
    LD_C_A;
    LD_HL(wPartySpecies);

loop:
    LD_A_hli;
    CP_A(EGG);
    IF_NZ goto not_egg;
    PUSH_HL;
    LD_HL(wPartyMonOTs);
    LD_DE(NAME_LENGTH_JAPANESE);
    LD_A_B;
    AND_A_A;
    IF_Z goto skip;

loop2:
    ADD_HL_DE;
    DEC_A;
    IF_NZ goto loop2;

skip:
    LD_DE(mString_MysteryJP);
    LD_A(NAME_LENGTH_JAPANESE);

compare_loop:
    PUSH_AF;
    LD_A_de;
    INC_DE;
    CP_A_hl;
    INC_HL;
    IF_NZ goto different;
    POP_AF;
    DEC_A;
    IF_NZ goto compare_loop;
    for(int rept = 0; rept < 4; rept++){
    DEC_HL;
    }
    LD_A(0x50);
    LD_hli_A;
    LD_hli_A;
    POP_HL;
    LD_A(EGG_TICKET);
    LD_addr_A(wCurItem);
    LD_A(1);
    LD_addr_A(wItemQuantityChange);
    LD_A(-1);
    LD_addr_A(wCurItemQuantity);
    LD_HL(wNumItems);
    CALL(aTossItem);
    LD_A(TRUE);
    LD_addr_A(wScriptVar);
    RET;


different:
    POP_AF;
    POP_HL;

not_egg:
    INC_B;
    DEC_C;
    IF_NZ goto loop;
    RET;

}

void String_MysteryJP(void){
    //db ['"なぞナゾ@@"'];  // MYSTERY

    return Function1709aa();
}

void Function1709aa(void){
//  //  BattleTowerAction $0f
    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(BANK(w3_d090));
    LDH_addr_A(rSVBK);
    LD_A_addr(w3_d090);
    LD_addr_A(wScriptVar);
    POP_AF;
    LDH_addr_A(rSVBK);
    RET;

}

void Function1709bb(void){
//  //  BattleTowerAction $10
    XOR_A_A;  // FALSE
    LD_addr_A(wScriptVar);
    LD_A(BANK(s5_a800));
    CALL(aOpenSRAM);
    LD_A_addr(s5_a800);
    CALL(aCloseSRAM);
    CP_A(6);
    IF_NC goto invalid;
    LD_E_A;
    LD_D(0);
    LD_HL(mFunction1709bb_Jumptable);
    ADD_HL_DE;
    ADD_HL_DE;
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    JP_hl;


invalid:
    LD_A(BANK(s5_a800));
    CALL(aOpenSRAM);
    XOR_A_A;
    LD_addr_A(s5_a800);
    CALL(aCloseSRAM);
    RET;


Jumptable:
    //dw ['.NoAction'];
    //dw ['.NoAction'];
    //dw ['.DoAction1'];
    //dw ['.DoAction1'];
    //dw ['.Action4'];
    //dw ['.Action5'];


DoAction1:
    LD_A(BANK(s5_a800));
    CALL(aOpenSRAM);
    LD_A(1);
    LD_addr_A(s5_a800);
    CALL(aCloseSRAM);


NoAction:
    RET;


Action4:
    LD_A(BANK(s5_b023));  // aka BANK(s5_a825) and BANK(s5_a826)
    CALL(aOpenSRAM);
    LD_HL(s5_b023);
    LD_DE(wc608);
    LD_BC(105);
    CALL(aCopyBytes);
    LD_A_addr(s5_a825);
    LD_addr_A(wcd30);
    LD_A_addr(s5_a826);
    LD_addr_A(wcd31);
    CALL(aCloseSRAM);
    FARCALL(aFunction11b6b4);
    FARCALL(aFunction17d0f3);
    LD_A(TRUE);
    LD_addr_A(wScriptVar);
    RET;


Action5:
    LD_A(0);  // ???
    CALL(aOpenSRAM);
    LD_HL(wRTC);
    LD_DE(wc608);
    LD_BC(4);
    CALL(aCopyBytes);
    CALL(aCloseSRAM);
    LD_A(BANK(s5_b08c));
    CALL(aOpenSRAM);
    LD_HL(s5_b08c);
    LD_DE(wc608);
    LD_C(4);

compare_loop:
    LD_A_de;
    INC_DE;
    CP_A_hl;
    IF_NZ goto different;
    INC_HL;
    DEC_C;
    IF_NZ goto compare_loop;
    CALL(aCloseSRAM);
    LD_A_addr(wMapGroup);
    LD_B_A;
    LD_A_addr(wMapNumber);
    LD_C_A;
    CALL(aGetMapSceneID);
    LD_A_D;
    OR_A_E;
    IF_Z goto no_scene;
    LD_A_de;
    AND_A_A;
    RET_NZ ;


no_scene:
    LD_A(TRUE);
    LD_addr_A(wScriptVar);
    RET;


different:
    CALL(aCloseSRAM);
    LD_A(BANK(s5_a800));
    CALL(aOpenSRAM);
    XOR_A_A;
    LD_addr_A(s5_a800);
    CALL(aCloseSRAM);
    LD_addr_A(wScriptVar);
    LD_A_addr(wMapGroup);
    LD_B_A;
    LD_A_addr(wMapNumber);
    LD_C_A;
    CALL(aGetMapSceneID);
    LD_A_D;
    OR_A_E;
    IF_Z goto no_scene_2;
    XOR_A_A;
    LD_de_A;


no_scene_2:
    RET;

}

void Function170a9c(void){
    LD_C(FALSE);
    JR(mSet_s5_aa8d);

}

void Function170aa0(void){
    LD_C(TRUE);
    return Set_s5_aa8d();
}

void Set_s5_aa8d(void){
    LD_A(BANK(s5_aa8d));
    CALL(aOpenSRAM);
    LD_A_C;
    LD_addr_A(s5_aa8d);
    CALL(aCloseSRAM);
    RET;

}

void Function170aaf(void){
    LD_A(BANK(s5_aa8d));
    CALL(aOpenSRAM);
    LD_A_addr(s5_aa8d);
    LD_addr_A(wScriptVar);
    CALL(aCloseSRAM);
    RET;

}

void Function170abe(void){
    CALL(aBattleTower_CheckSaveFileExistsAndIsYours);
    LD_A_addr(wScriptVar);
    AND_A_A;
    RET_Z ;

    LD_A(BANK(sBattleTowerSaveFileFlags));
    CALL(aOpenSRAM);
    LD_A_addr(sBattleTowerSaveFileFlags);
    AND_A(1);
    LD_addr_A(wScriptVar);
    CALL(aCloseSRAM);
    RET;

}

void Function170ad7(void){
    LD_A(BANK(sBattleTowerSaveFileFlags));
    CALL(aOpenSRAM);
    LD_A_addr(sBattleTowerSaveFileFlags);
    OR_A(1);
    LD_addr_A(sBattleTowerSaveFileFlags);
    CALL(aCloseSRAM);
    RET;

}

void BattleTowerAction_LevelCheck(void){
    LD_A(BANK(s5_b2fb));
    CALL(aOpenSRAM);
    LD_A_addr(s5_b2fb);
    CALL(aCloseSRAM);
    LD_C(10);
    CALL(aSimpleDivide);
    LD_A_B;
    LD_addr_A(wcd4f);
    XOR_A_A;
    LD_addr_A(wScriptVar);
    FARCALL(aBattleTower_LevelCheck);
    RET_NC ;
    LD_A(BANK(s5_b2fb));
    CALL(aOpenSRAM);
    LD_A_addr(s5_b2fb);
    CALL(aCloseSRAM);
    LD_addr_A(wScriptVar);
    RET;

}

void BattleTowerAction_UbersCheck(void){
    LD_A(BANK(s5_b2fb));
    CALL(aOpenSRAM);
    LD_A_addr(s5_b2fb);
    CALL(aCloseSRAM);
    LD_C(10);
    CALL(aSimpleDivide);
    LD_A_B;
    LD_addr_A(wcd4f);
    XOR_A_A;
    LD_addr_A(wScriptVar);
    FARCALL(aBattleTower_UbersCheck);
    RET_NC ;
    LD_A(BANK(s5_b2fb));
    CALL(aOpenSRAM);
    LD_A_addr(s5_b2fb);
    CALL(aCloseSRAM);
    LD_addr_A(wScriptVar);
    RET;

}

void LoadOpponentTrainerAndPokemonWithOTSprite(void){
    // FARCALL(aLoadOpponentTrainerAndPokemon);
    LoadOpponentTrainerAndPokemon();
    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    // LD_A(BANK(wBT_OTTrainerClass));
    // LDH_addr_A(rSVBK);
    // LD_HL(wBT_OTTrainerClass);
    // LD_A_hl;
    // DEC_A;
    // LD_C_A;
    // LD_B(0);
    // POP_AF;
    // LDH_addr_A(rSVBK);
    // LD_HL(mBTTrainerClassSprites);
    // ADD_HL_BC;
    // LD_A_hl;
    // LD_addr_A(wBTTempOTSprite);
    wram->wBTTempOTSprite = BTTrainerClassSprites[wram->wBT_OTTrainer.trainerClass - 1];

//  Load sprite of the opponent trainer
//  because s/he is chosen randomly and appears out of nowhere
    // LD_A_addr(wScriptVar);
    // DEC_A;
    // SLA_A;
    // LD_E_A;
    uint8_t a = (wram->wScriptVar - 1);
    // SLA_A;
    // SLA_A;
    // SLA_A;
    // LD_C_A;
    // LD_B(0);
    // LD_D(0);
    // LD_HL(wMapObjects);
    // ADD_HL_BC;
    // INC_HL;
    // LD_A_addr(wBTTempOTSprite);
    // LD_hl_A;
    wram->wMapObject[a].sprite = wram->wBTTempOTSprite;
    // LD_HL(wUsedSprites);
    // ADD_HL_DE;
    // LD_hli_A;
    wram->wUsedSprites[a << 1] = wram->wBTTempOTSprite;
    // LDH_addr_A(hUsedSpriteIndex);
    hram->hUsedSpriteIndex = wram->wBTTempOTSprite;
    // LD_A_hl;
    // LDH_addr_A(hUsedSpriteTile);
    hram->hUsedSpriteTile = wram->wUsedSprites[(a << 1) + 1];
    // FARCALL(aGetUsedSprite);
    GetUsedSprite_Conv();
    // RET;

// INCLUDE "data/trainers/sprites.asm"
}

void UnusedBattleTowerDummySpecial2(void){
    RET;

}

void CheckForBattleTowerRules(void){
    // FARCALL(av_CheckForBattleTowerRules);
    // IF_C goto ready;
    // XOR_A_A;  // FALSE
    // goto end;

// ready:
    // LD_A(TRUE);


// end:
    // LD_addr_A(wScriptVar);
    wram->wScriptVar = (v_CheckForBattleTowerRules())? TRUE: FALSE;
    // RET;
}
