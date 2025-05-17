#include "../../../constants.h"
#include "load_trainer.h"
#include "../../../home/copy.h"
#include "../../../home/random.h"
#include "../../../home/sram.h"
#include "../../../home/names.h"
#include "../../../data/battle_tower/classes.h"
#include "../../../data/battle_tower/parties.h"

void LoadOpponentTrainerAndPokemon(void){
    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    // LD_A(BANK(wBT_OTTrainer));
    // LDH_addr_A(rSVBK);

// Fill wBT_OTTrainer with zeros
    // XOR_A_A;
    // LD_HL(wBT_OTTrainer);
    // LD_BC(BATTLE_TOWER_STRUCT_LENGTH);
    // CALL(aByteFill);
    ByteFill(&wram->wBT_OTTrainer, sizeof(wram->wBT_OTTrainer), 0);

// Write $ff into the Item-Slots
    // LD_A(0xff);
    // LD_addr_A(wBT_OTMon1Item);
    wram->wBT_OTTrainer.party[0].mon.mon.item = 0xff;
    // LD_addr_A(wBT_OTMon2Item);
    wram->wBT_OTTrainer.party[1].mon.mon.item = 0xff;
    // LD_addr_A(wBT_OTMon3Item);
    wram->wBT_OTTrainer.party[2].mon.mon.item = 0xff;

// Set wBT_OTTrainer as start address to write the following data to
    // LD_DE(wBT_OTTrainer);

    // LDH_A_addr(hRandomAdd);
    // LD_B_A;
    uint8_t b = hram.hRandomAdd;
    uint8_t a, c;
    uint8_t* hl;

    do {
        do {
        // resample:
        //   //  loop to find a random trainer
            // CALL(aRandom);
            Random();
            // LDH_A_addr(hRandomAdd);
            // ADD_A_B;
            // LD_B_A;  // b contains the nr of the trainer
            b = hram.hRandomAdd + b;
        #if defined(_CRYSTAL11)
            // maskbits(BATTLETOWER_NUM_UNIQUE_TRAINERS, 0);
            // CP_A(BATTLETOWER_NUM_UNIQUE_TRAINERS);
            c = BATTLETOWER_NUM_UNIQUE_TRAINERS;
            b &= 0x7f;
        #else
        //  Crystal 1.0 used the wrong constant here, so only the first 21
        //  trainers in BattleTowerTrainers can be sampled.
            // maskbits(BATTLETOWER_NUM_UNIQUE_MON, 0);
            // CP_A(BATTLETOWER_NUM_UNIQUE_MON);
            c = BATTLETOWER_NUM_UNIQUE_MON;
            b &= 0x1f;
        #endif
            // IF_NC goto resample;
        } while(b >= c);
        // LD_B_A;

        // LD_A(BANK(sBTTrainers));
        // CALL(aOpenSRAM);
        OpenSRAM(MBANK(asBTTrainers));

        // LD_C(BATTLETOWER_STREAK_LENGTH);
        c = BATTLETOWER_STREAK_LENGTH;
        // LD_HL(sBTTrainers);
        hl = GBToRAMAddr(sBTTrainers);

    next_trainer:
        // LD_A_hli;
        a = *(hl++);
        // CP_A_B;
        // IF_Z goto resample;
    } while(a == b);
    // DEC_C;
    // IF_NZ goto next_trainer;  // c <= 7  initialise all 7 trainers?
    if(--c != 0)
        goto next_trainer;

    // LD_HL(sBTTrainers);
    hl = GBToRAMAddr(sBTTrainers);
    // LD_A_addr(sNrOfBeatenBattleTowerTrainers);
    // LD_C_A;
    c = gb_read(sNrOfBeatenBattleTowerTrainers);
    // LD_A_B;
    // LD_B(0);
    // ADD_HL_BC;
    // LD_hl_A;
    hl[c] = b;

    // CALL(aCloseSRAM);
    CloseSRAM();

    // PUSH_AF;
//  Copy name (10 bytes) and class (1 byte) of trainer
    // LD_HL(mBattleTowerTrainers);
    // LD_BC(NAME_LENGTH);
    // CALL(aAddNTimes);
    // LD_BC(NAME_LENGTH);
    // CALL(aCopyBytes);
    CopyBytes(wram->wBT_OTTrainer.name, U82C(BattleTowerTrainers[b].name), sizeof(wram->wBT_OTTrainer.name));
    wram->wBT_OTTrainer.trainerClass = BattleTowerTrainers[b].tclass;

    struct BattleTowerPartyMon* de = wram->wBT_OTTrainer.party;
    // CALL(aLoadRandomBattleTowerMon);
    LoadRandomBattleTowerMon(de);
    // POP_AF;

    // LD_HL(mBattleTowerTrainerData);
    // LD_BC(BATTLETOWER_TRAINERDATALENGTH);
    // CALL(aAddNTimes);
    // LD_BC(BATTLETOWER_TRAINERDATALENGTH);

// copy_bt_trainer_data_loop:
    // LD_A(BANK(aBattleTowerTrainerData));
    // CALL(aGetFarByte);
    // LD_de_A;
    // INC_HL;
    // INC_DE;
    // DEC_BC;
    // LD_A_B;
    // OR_A_C;
    // IF_NZ goto copy_bt_trainer_data_loop;

    // POP_AF;
    // LDH_addr_A(rSVBK);

    // RET;
}

void LoadRandomBattleTowerMon(struct BattleTowerPartyMon* de){
    // LD_C(BATTLETOWER_PARTY_LENGTH);
    uint8_t c = BATTLETOWER_PARTY_LENGTH;

    do {
    // loop:
        // PUSH_BC;
        // LD_A(BANK(sBTMonOfTrainers));
        // CALL(aOpenSRAM);
        OpenSRAM(MBANK(asBTMonOfTrainers));
        const struct NicknamedMon* hl;

        do {
        // FindARandomBattleTowerMon:
        // From Which LevelGroup are the mon loaded
        // a = 1..10
            // LD_A_addr(wBTChoiceOfLvlGroup);
            // DEC_A;
            uint8_t group = wram->wBTChoiceOfLvlGroup;
            // LD_HL(mBattleTowerMons);
            // LD_BC(BATTLETOWER_NUM_UNIQUE_MON * NICKNAMED_MON_STRUCT_LENGTH);
            // CALL(aAddNTimes);
            hl = BattleTowerMons + group * BATTLETOWER_NUM_UNIQUE_MON; 

            // LDH_A_addr(hRandomAdd);
            // LD_B_A;
            uint8_t b = hram.hRandomAdd;

            do {
            // resample:
                // CALL(aRandom);
                Random();
                // LDH_A_addr(hRandomAdd);
                // ADD_A_B;
                // LD_B_A;
                b += hram.hRandomAdd;
                // maskbits(BATTLETOWER_NUM_UNIQUE_MON, 0);
                b &= 0x1f;
                // CP_A(BATTLETOWER_NUM_UNIQUE_MON);
                // IF_NC goto resample;
            } while(b >= BATTLETOWER_NUM_UNIQUE_MON);
        // in register 'a' is the chosen mon of the LevelGroup

        // Check if mon was already loaded before
        // Check current and the 2 previous teams
        // includes check if item is double at the current team
            // LD_BC(NICKNAMED_MON_STRUCT_LENGTH);
            // CALL(aAddNTimes);
            hl += b;
            // LD_A_hli;
            // LD_B_A;
            species_t species = hl->pmon.mon.species;
            // LD_A_hld;
            // LD_C_A;
            item_t item = hl->pmon.mon.item;
            // LD_A_addr(wBT_OTMon1);
            // CP_A_B;
            // IF_Z goto FindARandomBattleTowerMon;
            // LD_A_addr(wBT_OTMon1Item);
            // CP_A_C;
            // IF_Z goto FindARandomBattleTowerMon;
            if(wram->wBT_OTTrainer.party[0].mon.mon.species == species
            || wram->wBT_OTTrainer.party[0].mon.mon.item == item)
                continue;
            // LD_A_addr(wBT_OTMon2);
            // CP_A_B;
            // IF_Z goto FindARandomBattleTowerMon;
            // LD_A_addr(wBT_OTMon2Item);
            // CP_A_C;
            // IF_Z goto FindARandomBattleTowerMon;
            if(wram->wBT_OTTrainer.party[1].mon.mon.species == species
            || wram->wBT_OTTrainer.party[1].mon.mon.item == item)
                continue;
            // LD_A_addr(wBT_OTMon3);
            // CP_A_B;
            // IF_Z goto FindARandomBattleTowerMon;
            // LD_A_addr(wBT_OTMon3Item);
            // CP_A_C;
            // IF_Z goto FindARandomBattleTowerMon;
            if(wram->wBT_OTTrainer.party[2].mon.mon.species == species
            || wram->wBT_OTTrainer.party[2].mon.mon.item == item)
                continue;
            // LD_A_addr(sBTMonPrevTrainer1);
            // CP_A_B;
            // IF_Z goto FindARandomBattleTowerMon;
            // LD_A_addr(sBTMonPrevTrainer2);
            // CP_A_B;
            // IF_Z goto FindARandomBattleTowerMon;
            // LD_A_addr(sBTMonPrevTrainer3);
            // CP_A_B;
            // IF_Z goto FindARandomBattleTowerMon;
            // LD_A_addr(sBTMonPrevPrevTrainer1);
            // CP_A_B;
            // IF_Z goto FindARandomBattleTowerMon;
            // LD_A_addr(sBTMonPrevPrevTrainer2);
            // CP_A_B;
            // IF_Z goto FindARandomBattleTowerMon;
            // LD_A_addr(sBTMonPrevPrevTrainer3);
            // CP_A_B;
            // IF_Z goto FindARandomBattleTowerMon;
            if(gb_read(sBTMonPrevTrainer1) == species
            || gb_read(sBTMonPrevTrainer2) == species
            || gb_read(sBTMonPrevTrainer3) == species
            || gb_read(sBTMonPrevPrevTrainer1) == species
            || gb_read(sBTMonPrevPrevTrainer2) == species
            || gb_read(sBTMonPrevPrevTrainer3) == species)
                continue;
            break;
        } while(1);

        // LD_BC(NICKNAMED_MON_STRUCT_LENGTH);
        // CALL(aCopyBytes);
        CopyBytes(&de->mon, &hl->pmon, sizeof(de->mon));
        CopyBytes(de->monName, hl->nickname, sizeof(de->monName));

        // LD_A_addr(wNamedObjectIndex);
        // PUSH_AF;
        // PUSH_DE;
        // LD_HL(-NICKNAMED_MON_STRUCT_LENGTH);
        // ADD_HL_DE;
        // LD_A_hl;
        // LD_addr_A(wNamedObjectIndex);
        // LD_BC(PARTYMON_STRUCT_LENGTH);
        // ADD_HL_BC;
        // PUSH_HL;
        // CALL(aGetPokemonName);
        // LD_H_D;
        // LD_L_E;
        // POP_DE;
        // LD_BC(MON_NAME_LENGTH);
        // CALL(aCopyBytes);
        CopyBytes(de->monName, GetPokemonName(de->mon.mon.species), MON_NAME_LENGTH);

        // POP_DE;
        // POP_AF;
        // LD_addr_A(wNamedObjectIndex);
        // POP_BC;
        de++;
        // DEC_C;
        // JP_NZ (mLoadRandomBattleTowerMon_loop);
    } while(--c != 0);

    // LD_A_addr(sBTMonPrevTrainer1);
    // LD_addr_A(sBTMonPrevPrevTrainer1);
    gb_write(sBTMonPrevPrevTrainer1, gb_read(sBTMonPrevTrainer1));
    // LD_A_addr(sBTMonPrevTrainer2);
    // LD_addr_A(sBTMonPrevPrevTrainer2);
    gb_write(sBTMonPrevPrevTrainer2, gb_read(sBTMonPrevTrainer2));
    // LD_A_addr(sBTMonPrevTrainer3);
    // LD_addr_A(sBTMonPrevPrevTrainer3);
    gb_write(sBTMonPrevPrevTrainer3, gb_read(sBTMonPrevTrainer3));
    // LD_A_addr(wBT_OTMon1);
    // LD_addr_A(sBTMonPrevTrainer1);
    gb_write(sBTMonPrevTrainer1, wram->wBT_OTTrainer.party[0].mon.mon.species);
    // LD_A_addr(wBT_OTMon2);
    // LD_addr_A(sBTMonPrevTrainer2);
    gb_write(sBTMonPrevTrainer2, wram->wBT_OTTrainer.party[1].mon.mon.species);
    // LD_A_addr(wBT_OTMon3);
    // LD_addr_A(sBTMonPrevTrainer3);
    gb_write(sBTMonPrevTrainer3, wram->wBT_OTTrainer.party[2].mon.mon.species);
    // CALL(aCloseSRAM);
    CloseSRAM();
    // RET;

// INCLUDE "data/battle_tower/classes.asm"

// INCLUDE "data/battle_tower/parties.asm"

}
