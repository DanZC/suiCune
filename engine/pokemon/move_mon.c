#include "../../constants.h"
#include "move_mon.h"
#include "caught_data.h"
#include "evolve.h"
#include "breedmon_level_growth.h"
#include "health.h"
#include "experience.h"
#include "tempmon.h"
#include "../math/get_square_root.h"
#include "../../home/print_text.h"
#include "../../home/sram.h"
#include "../../home/copy.h"
#include "../../home/pokemon.h"
#include "../../home/names.h"
#include "../../home/menu.h"
#include "../../home/string.h"
#include "../../home/map.h"
#include "../../home/pokedex_flags.h"
#include "../../home/sprite_updates.h"
#include "../../home/text.h"
#include "../../home/random.h"
#include "../../home/audio.h"
#include "../gfx/load_pics.h"
#include "../battle/read_trainer_dvs.h"
#include "../pokedex/unown_dex.h"
#include "../items/item_effects.h"
#include "../menus/naming_screen.h"
#include "../smallflag.h"
#include "../battle/core.h"
#include "../../util/serialize.h"
#include "../../data/moves/moves.h"
#include <stddef.h>
#include "../../data/text/common.h"

#define RANDY_OT_ID (1001)

static void DepositBreedmon(uint8_t* nickname, uint8_t* ot, struct BoxMon* de, uint8_t a);
static void ShiftBoxMon(struct Box* box);

bool TryAddMonToParty(species_t species, uint8_t level){
//  Check if to copy wild mon or generate a new one
// Whose is it?
    // LD_DE(wPartyCount);
    // LD_A_addr(wMonType);
    // AND_A(0xf);
    // IF_Z goto getpartylocation;  // PARTYMON
    // LD_DE(wOTPartyCount);
    struct PartyMon* de = (wram->wMonType & 0xf)? wram->wOTPartyMon: gPokemon.partyMon;
    uint8_t* partyCount = (wram->wMonType & 0xf)? &wram->wOTPartyCount: &gPokemon.partyCount;
    species_t* partySpecies = (wram->wMonType & 0xf)? wram->wOTPartySpecies: gPokemon.partySpecies;

// getpartylocation:
// Do we have room for it?
    // LD_A_de;
    // INC_A;
    // CP_A(PARTY_LENGTH + 1);
    // RET_NC ;
    if(*partyCount + 1 >= PARTY_LENGTH + 1)
        return false;
// Increase the party count
    // LD_de_A;
    // LD_A_de;  // Why are we doing this?
    // LDH_addr_A(hMoveMon);  // HRAM backup
    hram.hMoveMon = ++*partyCount;
    // ADD_A_E;
    // LD_E_A;
    // IF_NC goto loadspecies;
    // INC_D;


// loadspecies:
// Load the species of the Pokemon into the party list.
// The terminator is usually here, but it'll be back.
    // LD_A_addr(wCurPartySpecies);
    // LD_de_A;
    partySpecies[hram.hMoveMon - 1] = species;
// Load the terminator into the next slot.
    // INC_DE;
    // LD_A(-1);
    // LD_de_A;
    partySpecies[hram.hMoveMon] = (species_t)-1;
// Now let's load the OT name.
    // LD_HL(wPartyMonOTs);
    // LD_A_addr(wMonType);
    // AND_A(0xf);
    // IF_Z goto loadOTname;
    // LD_HL(wOTPartyMonOTs);
    uint8_t* ot = (wram->wMonType & 0xf)? wram->wOTPartyMonOT[hram.hMoveMon - 1]: gPokemon.partyMonOT[hram.hMoveMon - 1];

// loadOTname:
    // LDH_A_addr(hMoveMon);  // Restore index from backup
    // DEC_A;
    // CALL(aSkipNames);
    // LD_D_H;
    // LD_E_L;
    // LD_HL(wPlayerName);
    // LD_BC(NAME_LENGTH);
    // CALL(aCopyBytes);
    CopyBytes(ot, wram->wPlayerName, NAME_LENGTH);
// Only initialize the nickname for party mon
    // LD_A_addr(wMonType);
    // AND_A_A;
    // IF_NZ goto skipnickname;
    if(wram->wMonType == 0) {
        // LD_A_addr(wCurPartySpecies);
        // LD_addr_A(wNamedObjectIndex);
        // CALL(aGetPokemonName);
        // LD_HL(wPartyMonNicknames);
        // LDH_A_addr(hMoveMon);
        // DEC_A;
        // CALL(aSkipNames);
        // LD_D_H;
        // LD_E_L;
        // LD_HL(wStringBuffer1);
        // LD_BC(MON_NAME_LENGTH);
        // CALL(aCopyBytes);
        CopyBytes(gPokemon.partyMonNickname[hram.hMoveMon - 1], GetPokemonName(species), MON_NAME_LENGTH);
    }

// skipnickname:
    // LD_HL(wPartyMon1Species);
    // LD_A_addr(wMonType);
    // AND_A(0xf);
    // IF_Z goto initializeStats;
    // LD_HL(wOTPartyMon1Species);

// initializeStats:
    // LDH_A_addr(hMoveMon);
    // DEC_A;
    // LD_BC(PARTYMON_STRUCT_LENGTH);
    // CALL(aAddNTimes);
    return GeneratePartyMonStats(de + (hram.hMoveMon - 1), species, level, wram->wMonType, wram->wBattleMode);
}

//  wBattleMode specifies whether it's a wild mon or not.
//  wMonType specifies whether it's an opposing mon or not.
//  wCurPartySpecies/wCurPartyLevel specify the species and level.
//  hl points to the wPartyMon struct to fill.
bool GeneratePartyMonStats(struct PartyMon* hl, species_t species, uint8_t level, uint8_t monType, uint8_t battleMode){
    // LD_E_L;
    // LD_D_H;
    // PUSH_HL;

// Initialize the species
    // LD_A_addr(wCurPartySpecies);
    // LD_addr_A(wCurSpecies);
    // CALL(aGetBaseData);
    GetBaseData(species);
    // LD_A_addr(wBaseDexNo);
    // LD_de_A;
    hl->mon.species = wram->wBaseDexNo;
    // INC_DE;

// Copy the item if it's a wild mon
    // LD_A_addr(wBattleMode);
    // AND_A_A;
    // LD_A(0x0);
    // IF_Z goto skipitem;
    // LD_A_addr(wEnemyMonItem);

// skipitem:
    // LD_de_A;
    if(battleMode != 0x0)
        hl->mon.item = wram->wEnemyMon.item;
    else
        hl->mon.item = NO_ITEM;
    // INC_DE;

// Copy the moves if it's a wild mon
    // PUSH_DE;
    // LD_H_D;
    // LD_L_E;
    // LD_A_addr(wBattleMode);
    // AND_A_A;
    // IF_Z goto randomlygeneratemoves;
    // LD_A_addr(wMonType);
    // AND_A_A;
    // IF_NZ goto randomlygeneratemoves;
    if(battleMode == 0 || monType != 0) {
    // randomlygeneratemoves:
        // XOR_A_A;
        // for(int rept = 0; rept < NUM_MOVES - 1; rept++){
        // LD_hli_A;
        // }
        // LD_hl_A;
        ByteFill(hl->mon.moves, sizeof(hl->mon.moves), 0);
        // LD_addr_A(wSkipMovesBeforeLevelUp);
        wram->wSkipMovesBeforeLevelUp = FALSE;
        // PREDEF(pFillMoves);
        FillMoves(hl->mon.moves, hl->mon.PP, species, level);
    }
    else {
        // LD_DE(wEnemyMonMoves);
        // for(int rept = 0; rept < NUM_MOVES - 1; rept++){
        // LD_A_de;
        // INC_DE;
        // LD_hli_A;
        // }
        // LD_A_de;
        // LD_hl_A;
        // goto next;
        CopyBytes(hl->mon.moves, wram->wEnemyMon.moves, sizeof(wram->wEnemyMon.moves));
    }

// next:
    // POP_DE;
    // for(int rept = 0; rept < NUM_MOVES; rept++){
    // INC_DE;
    // }

// Initialize ID.
    // LD_A_addr(wPlayerID);
    // LD_de_A;
    // INC_DE;
    // LD_A_addr(wPlayerID + 1);
    // LD_de_A;
    // INC_DE;
    hl->mon.id = wram->wPlayerID;

// Initialize Exp.
    // PUSH_DE;
    // LD_A_addr(wCurPartyLevel);
    // LD_D_A;
    // CALLFAR(aCalcExpAtLevel);
    uint32_t exp = CalcExpAtLevel(level);
    // POP_DE;
    // LDH_A_addr(hProduct + 1);
    // LD_de_A;
    hl->mon.exp[0] = HIGH(exp >> 8);
    // INC_DE;
    // LDH_A_addr(hProduct + 2);
    // LD_de_A;
    hl->mon.exp[1] = HIGH(exp);
    // INC_DE;
    // LDH_A_addr(hProduct + 3);
    // LD_de_A;
    hl->mon.exp[2] = LOW(exp);
    // INC_DE;

// Initialize stat experience.
    // XOR_A_A;
    // LD_B(MON_DVS - MON_STAT_EXP);

    for(uint32_t i = 0; i < NUM_EXP_STATS; ++i) {
    // loop:
        // LD_de_A;
        hl->mon.statExp[i] = 0;
        // INC_DE;
        // DEC_B;
        // IF_NZ goto loop;
    }

    // POP_HL;
    // PUSH_HL;
    // LD_A_addr(wMonType);
    // AND_A(0xf);
    // IF_Z goto registerpokedex;
    uint16_t bc;
    if((monType & 0xf) == 0) {
    // registerpokedex:
        // LD_A_addr(wCurPartySpecies);
        // LD_addr_A(wTempSpecies);
        // DEC_A;
        // PUSH_DE;
        // CALL(aCheckCaughtMon);
        CheckCaughtMon(species - 1);
        // LD_A_addr(wTempSpecies);
        // DEC_A;
        // CALL(aSetSeenAndCaughtMon);
        SetSeenAndCaughtMon(species - 1);
        // POP_DE;

        // POP_HL;
        // PUSH_HL;
        // LD_A_addr(wBattleMode);
        // AND_A_A;
        // IF_NZ goto copywildmonDVs;
        if(battleMode != 0)
            goto copywildmonDVs;

        // CALL(aRandom);
        // LD_B_A;
        bc = Random() << 8;
        // CALL(aRandom);
        // LD_C_A;
        bc |= Random();
    }
    else {
        // PUSH_HL;
        // FARCALL(aGetTrainerDVs);
        bc = GetTrainerDVs(wram->wOtherTrainerClass);
        // POP_HL;
        // goto initializeDVs;
    }

// initializeDVs:
    // LD_A_B;
    // LD_de_A;
    // INC_DE;
    // LD_A_C;
    // LD_de_A;
    // INC_DE;
    hl->mon.DVs = ReverseEndian16(bc);

// Initialize PP.
    // PUSH_HL;
    // PUSH_DE;
    // INC_HL;
    // INC_HL;
    // CALL(aFillPP);
    FillPP(hl->mon.PP, hl->mon.moves);
    // POP_DE;
    // POP_HL;
    // for(int rept = 0; rept < NUM_MOVES; rept++){
    // INC_DE;
    // }

// Initialize happiness.
    // LD_A(BASE_HAPPINESS);
    // LD_de_A;
    // INC_DE;
    hl->mon.happiness = BASE_HAPPINESS;

    // XOR_A_A;
// PokerusStatus
    // LD_de_A;
    // INC_DE;
    hl->mon.pokerusStatus = 0;
// CaughtData/CaughtTime/CaughtLevel
    // LD_de_A;
    // INC_DE;
    hl->mon.caughtTimeLevel = 0;
// CaughtGender/CaughtLocation
    // LD_de_A;
    // INC_DE;
    hl->mon.caughtGenderLocation = 0;

// Initialize level.
    // LD_A_addr(wCurPartyLevel);
    // LD_de_A;
    // INC_DE;
    hl->mon.level = level;

    // XOR_A_A;
// Status
    // LD_de_A;
    // INC_DE;
    hl->status = 0;
// Unused
    // LD_de_A;
    // INC_DE;
    hl->unused = 0;

// Initialize HP.
    uint16_t* statxp = (uint16_t*)((uint8_t*)hl + offsetof(struct BoxMon, statExp));
    // LD_BC(MON_STAT_EXP - 1);
    // ADD_HL_BC;
    // LD_A(1);
    // LD_C_A;
    // LD_B(FALSE);
    // CALL(aCalcMonStatC);
    // LDH_A_addr(hProduct + 2);
    // LD_de_A;
    // INC_DE;
    // LDH_A_addr(hProduct + 3);
    // LD_de_A;
    // INC_DE;
    hl->HP = NativeToBigEndian16(CalcMonStatC(statxp, hl->mon.DVs, FALSE, 1));
    goto initstats;


copywildmonDVs:
    // LD_A_addr(wEnemyMonDVs);
    // LD_de_A;
    // INC_DE;
    // LD_A_addr(wEnemyMonDVs + 1);
    // LD_de_A;
    // INC_DE;
    hl->mon.DVs = wram->wEnemyMon.dvs;

    // PUSH_HL;
    // LD_HL(wEnemyMonPP);
    // LD_B(NUM_MOVES);

// wildmonpploop:
    // LD_A_hli;
    // LD_de_A;
    // INC_DE;
    // DEC_B;
    // IF_NZ goto wildmonpploop;
    CopyBytes(hl->mon.PP, wram->wEnemyMon.pp, sizeof(wram->wEnemyMon.pp));
    // POP_HL;

// Initialize happiness.
    // LD_A(BASE_HAPPINESS);
    // LD_de_A;
    // INC_DE;
    hl->mon.happiness = BASE_HAPPINESS;

    // XOR_A_A;
// PokerusStatus
    // LD_de_A;
    // INC_DE;
    hl->mon.pokerusStatus = 0;
// CaughtData/CaughtTime/CaughtLevel
    // LD_de_A;
    // INC_DE;
    hl->mon.caughtTimeLevel = 0;
// CaughtGender/CaughtLocation
    // LD_de_A;
    // INC_DE;
    hl->mon.caughtGenderLocation = 0;

// Initialize level.
    // LD_A_addr(wCurPartyLevel);
    // LD_de_A;
    // INC_DE;
    hl->mon.level = level;

    // LD_HL(wEnemyMonStatus);
// Copy wEnemyMonStatus
    // LD_A_hli;
    // LD_de_A;
    // INC_DE;
    hl->status = wram->wEnemyMon.status[0];
// Copy EnemyMonUnused
    // LD_A_hli;
    // LD_de_A;
    // INC_DE;
    hl->unused = wram->wEnemyMon.status[1];
// Copy wEnemyMonHP
    // LD_A_hli;
    // LD_de_A;
    // INC_DE;
    // LD_A_hl;
    // LD_de_A;
    // INC_DE;
    hl->HP = wram->wEnemyMon.hp;

initstats:
    // LD_A_addr(wBattleMode);
    // DEC_A;
    // IF_NZ goto generatestats;
    if(battleMode == 1) {
        // LD_HL(wEnemyMonMaxHP);
        hl->maxHP = wram->wEnemyMon.maxHP;
        // LD_BC(PARTYMON_STRUCT_LENGTH - MON_MAXHP);
        // CALL(aCopyBytes);
        CopyBytes(hl->stats, (uint16_t*)wram_ptr(wEnemyMonStats), sizeof(hl->stats));
        // POP_HL;
        // goto registerunowndex;
    }
    else {
    // generatestats:
        // POP_HL;
        // LD_BC(MON_STAT_EXP - 1);
        // ADD_HL_BC;
        // LD_B(FALSE);
        // CALL(aCalcMonStats);
        CalcMonStats_PartyMon(hl, FALSE);
    }

// registerunowndex:
    // LD_A_addr(wMonType);
    // AND_A(0xf);
    // IF_NZ goto done;
    // LD_A_addr(wCurPartySpecies);
    // CP_A(UNOWN);
    // IF_NZ goto done;
    if((monType & 0xf) == 0 && species == UNOWN) {
        // LD_HL(wPartyMon1DVs);
        // LD_A_addr(wPartyCount);
        // DEC_A;
        // LD_BC(PARTYMON_STRUCT_LENGTH);
        // CALL(aAddNTimes);
        // PREDEF(pGetUnownLetter);
        // CALLFAR(aUpdateUnownDex);
        UpdateUnownDex(GetUnownLetter(hl->mon.DVs));
    }

// done:
    // SCF;  // When this function returns, the carry flag indicates success vs failure.
    // RET;
    return true;
}

void FillPP(uint8_t* de, const move_t* hl){
    // PUSH_BC;
    // LD_B(NUM_MOVES);
    for(uint8_t i = 0; i < NUM_MOVES; ++i) {
    // loop:
        // LD_A_hli;
        // AND_A_A;
        // IF_Z goto next;
        if(hl[i] != NO_MOVE) {
            // DEC_A;
            // PUSH_HL;
            // PUSH_DE;
            // PUSH_BC;
            // LD_HL(mMoves);
            // LD_BC(MOVE_LENGTH);
            // CALL(aAddNTimes);
            // LD_DE(wStringBuffer1);
            // LD_A(BANK(aMoves));
            // CALL(aFarCopyBytes);
            // POP_BC;
            // POP_DE;
            // POP_HL;
            // LD_A_addr(wStringBuffer1 + MOVE_PP);
            de[i] = Moves[hl[i]].pp;
        }
        else {
            de[i] = 0;
        }
    // next:
        // LD_de_A;
        // INC_DE;
        // DEC_B;
        // IF_NZ goto loop;
    }
    // POP_BC;
    // RET;
}

bool AddTempmonToParty(void){
    // LD_HL(wPartyCount);
    // LD_A_hl;
    // CP_A(PARTY_LENGTH);
    // SCF;
    // RET_Z ;
    if(gPokemon.partyCount == PARTY_LENGTH)
        return true;

    // INC_A;
    // LD_hl_A;
    // LD_C_A;
    uint8_t c = ++gPokemon.partyCount;
    // LD_B(0);
    // ADD_HL_BC;
    // LD_A_addr(wCurPartySpecies);
    // LD_hli_A;
    gPokemon.partySpecies[c-1] = wram->wCurPartySpecies;
    // LD_hl(0xff);
    gPokemon.partySpecies[c] = (species_t)-1;

    // LD_HL(wPartyMon1Species);
    // LD_A_addr(wPartyCount);
    // DEC_A;
    // LD_BC(PARTYMON_STRUCT_LENGTH);
    // CALL(aAddNTimes);
    // LD_E_L;
    // LD_D_H;
    // LD_HL(wTempMonSpecies);
    // CALL(aCopyBytes);
    CopyBytes(gPokemon.partyMon + (c - 1), &wram->wTempMon, PARTYMON_STRUCT_LENGTH);

    // LD_HL(wPartyMonOTs);
    // LD_A_addr(wPartyCount);
    // DEC_A;
    // CALL(aSkipNames);
    // LD_D_H;
    // LD_E_L;
    // LD_HL(wOTPartyMonOTs);
    // LD_A_addr(wCurPartyMon);
    // CALL(aSkipNames);
    // LD_BC(NAME_LENGTH);
    // CALL(aCopyBytes);
    CopyBytes(gPokemon.partyMonOT[c - 1], wram->wOTPartyMonOT[wram->wCurPartyMon], NAME_LENGTH);

    // LD_HL(wPartyMonNicknames);
    // LD_A_addr(wPartyCount);
    // DEC_A;
    // CALL(aSkipNames);
    // LD_D_H;
    // LD_E_L;
    // LD_HL(wOTPartyMonNicknames);
    // LD_A_addr(wCurPartyMon);
    // CALL(aSkipNames);
    // LD_BC(MON_NAME_LENGTH);
    // CALL(aCopyBytes);
    CopyBytes(gPokemon.partyMonNickname[c - 1], wram->wOTPartyMonNickname[wram->wCurPartyMon], MON_NAME_LENGTH);

    // LD_A_addr(wCurPartySpecies);
    // LD_addr_A(wNamedObjectIndex);
    // CP_A(EGG);
    // IF_Z goto egg;
    if(wram->wCurPartySpecies != EGG) {
        // DEC_A;
        // CALL(aSetSeenAndCaughtMon);
        SetSeenAndCaughtMon(wram->wCurPartySpecies - 1);
        // LD_HL(wPartyMon1Happiness);
        // LD_A_addr(wPartyCount);
        // DEC_A;
        // LD_BC(PARTYMON_STRUCT_LENGTH);
        // CALL(aAddNTimes);
        // LD_hl(BASE_HAPPINESS);
        gPokemon.partyMon[c - 1].mon.happiness = BASE_HAPPINESS;
    }

// egg:
    // LD_A_addr(wCurPartySpecies);
    // CP_A(UNOWN);
    // IF_NZ goto done;
    if(wram->wCurPartySpecies == UNOWN){
        // LD_HL(wPartyMon1DVs);
        // LD_A_addr(wPartyCount);
        // DEC_A;
        // LD_BC(PARTYMON_STRUCT_LENGTH);
        // CALL(aAddNTimes);
        // PREDEF(pGetUnownLetter);
        unown_letter_t letter = GetUnownLetter(gPokemon.partyMon[c - 1].mon.DVs);
        // CALLFAR(aUpdateUnownDex);
        UpdateUnownDex(letter);
        // LD_A_addr(wFirstUnownSeen);
        // AND_A_A;
        // IF_NZ goto done;
        if(gPokemon.firstUnownSeen == 0) {
            // LD_A_addr(wUnownLetter);
            // LD_addr_A(wFirstUnownSeen);
            gPokemon.firstUnownSeen = letter;
        }
    }

// done:
    // AND_A_A;
    // RET;
    return false;
}

//  Sents/Gets mon into/from Box depending on Parameter
//  wPokemonWithdrawDepositParameter == 0: get mon into Party
//  wPokemonWithdrawDepositParameter == 1: sent mon into Box
//  wPokemonWithdrawDepositParameter == 2: get mon from DayCare
//  wPokemonWithdrawDepositParameter == 3: put mon into DayCare
bool SendGetMonIntoFromBox(uint8_t param){
    // LD_A(BANK(sBoxCount));
    // CALL(aOpenSRAM);
    OpenSRAM(MBANK(asBoxCount));
    struct Box box;
    Deserialize_Box(&box, GBToRAMAddr(sBox));
    // LD_A_addr(wPokemonWithdrawDepositParameter);
    // AND_A_A;
    // IF_Z goto check_IfPartyIsFull;
    // CP_A(DAY_CARE_WITHDRAW);
    // IF_Z goto check_IfPartyIsFull;
    uint8_t c;
    uint8_t* count;
    species_t* species;
    struct PartyMon* pmon = NULL;
    struct BoxMon* bmon = NULL;
    uint8_t* de_ot = NULL;
    if(param == PC_WITHDRAW || param == DAY_CARE_WITHDRAW) {
    // check_IfPartyIsFull:
        // LD_HL(wPartyCount);
        count = &gPokemon.partyCount;
        species = gPokemon.partySpecies;
        // LD_A_hl;
        // CP_A(PARTY_LENGTH);
        // JP_Z (mCloseSRAM_And_SetCarryFlag);
        if(gPokemon.partyCount == PARTY_LENGTH)
            return CloseSRAM_And_SetCarryFlag(&box);
        c = gPokemon.partyCount;
        // goto there_is_room;
    }
    // CP_A(DAY_CARE_DEPOSIT);
    // LD_HL(wBreedMon1Species);
    // IF_Z goto breedmon;
    else if(param == DAY_CARE_DEPOSIT) {
        bmon = &gPokemon.breedMon1;
        goto breedmon;
    }

// we want to sent a mon into the Box
// so check if there's enough space
    else {
        // LD_HL(sBoxCount);
        count = &box.count;
        species = box.species;
        // LD_A_hl;
        c = *count;
        // CP_A(MONS_PER_BOX);
        // IF_NZ goto there_is_room;
        // JP(mCloseSRAM_And_SetCarryFlag);
        if(c == MONS_PER_BOX)
            return CloseSRAM_And_SetCarryFlag(&box);
    }

// there_is_room:
    // INC_A;
    // LD_hl_A;
    *count = ++c;
    // LD_C_A;
    // LD_B(0);
    // ADD_HL_BC;
    // LD_A_addr(wPokemonWithdrawDepositParameter);
    // CP_A(DAY_CARE_WITHDRAW);
    // LD_A_addr(wBreedMon1Species);
    // IF_Z goto okay1;
    // LD_A_addr(wCurPartySpecies);

// okay1:
    // LD_hli_A;
    species[c-1] = (param == DAY_CARE_WITHDRAW)? gPokemon.breedMon1.species: wram->wCurPartySpecies;
    // LD_hl(0xff);
    species[c] = (species_t)-1;

    // LD_A_addr(wPokemonWithdrawDepositParameter);
    // DEC_A;
    if(param != PC_DEPOSIT) {
        // LD_HL(wPartyMon1Species);
        pmon = gPokemon.partyMon + (gPokemon.partyCount - 1);
        // LD_BC(PARTYMON_STRUCT_LENGTH);
        // LD_A_addr(wPartyCount);
    }
    // IF_NZ goto okay2;
    else {
        // LD_HL(sBoxMon1Species);
        // LD_BC(BOXMON_STRUCT_LENGTH);
        // LD_A_addr(sBoxCount);
        bmon = box.mons + (box.count - 1);

    // okay2:
        // DEC_A;  // wPartyCount - 1
        // CALL(aAddNTimes);
    }

breedmon:
    // PUSH_HL;
    // LD_E_L;
    // LD_D_H;
    // LD_A_addr(wPokemonWithdrawDepositParameter);
    // AND_A_A;
    switch(param) {
    case PC_WITHDRAW:
        // LD_HL(sBoxMon1Species);
        // LD_BC(BOXMON_STRUCT_LENGTH);
        // IF_Z goto okay3;
        CopyBytes(&pmon->mon, &box.mons[wram->wCurPartyMon], sizeof(pmon->mon));
        break;
    case DAY_CARE_WITHDRAW:
        // CP_A(DAY_CARE_WITHDRAW);
        // LD_HL(wBreedMon1Species);
        // IF_Z goto okay4;
        CopyBytes(bmon, &gPokemon.breedMon1, sizeof(*bmon));
        break;
    case DAY_CARE_DEPOSIT:
    case PC_DEPOSIT:
        // LD_HL(wPartyMon1Species);
        // LD_BC(PARTYMON_STRUCT_LENGTH);
        CopyBytes(bmon, &gPokemon.partyMon[wram->wCurPartyMon].mon, sizeof(*bmon));
        break;

    // okay3:
        // LD_A_addr(wCurPartyMon);
        // CALL(aAddNTimes);

    // okay4:
        // LD_BC(BOXMON_STRUCT_LENGTH);
        // CALL(aCopyBytes);
    }

    // LD_A_addr(wPokemonWithdrawDepositParameter);
    switch(param) {
    case DAY_CARE_DEPOSIT:
        // CP_A(DAY_CARE_DEPOSIT);
        // LD_DE(wBreedMon1OT);
        // IF_Z goto okay5;
        de_ot = gPokemon.breedMon1OT;
        break;
    case PC_WITHDRAW:
    case DAY_CARE_WITHDRAW:
        // DEC_A;
        // LD_HL(wPartyMonOTs);
        // LD_A_addr(wPartyCount);
        // IF_NZ goto okay6;
        de_ot = gPokemon.partyMonOT[gPokemon.partyCount - 1];
        break;
    case PC_DEPOSIT:
        // LD_HL(sBoxMonOTs);
        // LD_A_addr(sBoxCount);
        de_ot = box.monOT[box.count - 1];
        break;
    }

// okay6:
    // DEC_A;
    // CALL(aSkipNames);
    // LD_D_H;
    // LD_E_L;

// okay5:
    // LD_HL(sBoxMonOTs);
    // LD_A_addr(wPokemonWithdrawDepositParameter);
    // AND_A_A;
    // IF_Z goto okay7;
    // LD_HL(wBreedMon1OT);
    // CP_A(DAY_CARE_WITHDRAW);
    // IF_Z goto okay8;
    // LD_HL(wPartyMonOTs);


// okay7:
    // LD_A_addr(wCurPartyMon);
    // CALL(aSkipNames);
    switch(param) {
    case PC_WITHDRAW:
        CopyBytes(de_ot, box.monOT[wram->wCurPartyMon], NAME_LENGTH);
        break;
    case DAY_CARE_WITHDRAW:
        CopyBytes(de_ot, gPokemon.breedMon1OT, NAME_LENGTH);
        break;
    case PC_DEPOSIT:
    case DAY_CARE_DEPOSIT:
        CopyBytes(de_ot, gPokemon.partyMonOT[wram->wCurPartyMon], NAME_LENGTH);
        break;
    }

// okay8:
    // LD_BC(NAME_LENGTH);
    // CALL(aCopyBytes);
    // LD_A_addr(wPokemonWithdrawDepositParameter);
    switch(param) {
    case DAY_CARE_DEPOSIT:
        // CP_A(DAY_CARE_DEPOSIT);
        // LD_DE(wBreedMon1Nickname);
        // IF_Z goto okay9;
        de_ot = gPokemon.breedMon1Nickname;
        break;
    case PC_WITHDRAW:
    case DAY_CARE_WITHDRAW:
        // DEC_A;
        // LD_HL(wPartyMonNicknames);
        // LD_A_addr(wPartyCount);
        // IF_NZ goto okay10;
        de_ot = gPokemon.partyMonNickname[gPokemon.partyCount - 1];
        break;
    case PC_DEPOSIT:
        // LD_HL(sBoxMonNicknames);
        // LD_A_addr(sBoxCount);
        de_ot = box.monNicknames[box.count - 1];
        break;
    }

// okay10:
    // DEC_A;
    // CALL(aSkipNames);
    // LD_D_H;
    // LD_E_L;

// okay9:
    // LD_HL(sBoxMonNicknames);
    // LD_A_addr(wPokemonWithdrawDepositParameter);
    switch(param) {
    case PC_WITHDRAW:
        // AND_A_A;
        // IF_Z goto okay11;
        CopyBytes(de_ot, box.monNicknames[wram->wCurPartyMon], MON_NAME_LENGTH);
        break;
    case DAY_CARE_WITHDRAW:
        // LD_HL(wBreedMon1Nickname);
        // CP_A(DAY_CARE_WITHDRAW);
        // IF_Z goto okay12;
        CopyBytes(de_ot, gPokemon.breedMon1Nickname, MON_NAME_LENGTH);
        break;
    case PC_DEPOSIT:
    case DAY_CARE_DEPOSIT:
        // LD_HL(wPartyMonNicknames);
        CopyBytes(de_ot, gPokemon.partyMonNickname[wram->wCurPartyMon], MON_NAME_LENGTH);
        break;
    }

// okay11:
    // LD_A_addr(wCurPartyMon);
    // CALL(aSkipNames);

// okay12:
    // LD_BC(MON_NAME_LENGTH);
    // CALL(aCopyBytes);
    // POP_HL;

    // LD_A_addr(wPokemonWithdrawDepositParameter);
    switch(param) {
    // CP_A(PC_DEPOSIT);
    // IF_Z goto took_out_of_box;
    case PC_DEPOSIT:
    // took_out_of_box:
        // LD_A_addr(sBoxCount);
        // DEC_A;
        // LD_B_A;
        // CALL(aRestorePPOfDepositedPokemon);
        RestorePPOfDepositedPokemon(&box, box.count);
        break;
    // CP_A(DAY_CARE_DEPOSIT);
    // JP_Z (mSendGetMonIntoFromBox_CloseSRAM_And_ClearCarryFlag);
    case DAY_CARE_DEPOSIT:
        break;
    default: {
        // PUSH_HL;
        // SRL_A;
        // ADD_A(0x2);
        // LD_addr_A(wMonType);
        wram->wMonType = (param >> 1) + 0x2;
        // PREDEF(pCopyMonToTempMon);
        CopyMonToTempMon();
        // CALLFAR(aCalcLevel);
        // LD_A_D;
        // LD_addr_A(wCurPartyLevel);
        wram->wCurPartyLevel = CalcLevel(&wram->wTempMon);
        // POP_HL;

        // LD_B_H;
        // LD_C_L;
        // LD_HL(MON_LEVEL);
        // ADD_HL_BC;
        // LD_hl_A;
        pmon->mon.level = wram->wCurPartyLevel;
        // LD_HL(MON_MAXHP);
        // ADD_HL_BC;
        // LD_D_H;
        // LD_E_L;
        // LD_HL(MON_STAT_EXP - 1);
        // ADD_HL_BC;

        // PUSH_BC;
        // LD_B(TRUE);
        // CALL(aCalcMonStats);
        CalcMonStats_PartyMon(pmon, TRUE);
        // POP_BC;

        // LD_A_addr(wPokemonWithdrawDepositParameter);
        // AND_A_A;
        // IF_NZ goto CloseSRAM_And_ClearCarryFlag;
        if(param != PC_WITHDRAW)
            break;
        // LD_HL(MON_STATUS);
        // ADD_HL_BC;
        // XOR_A_A;
        // LD_hl_A;
        pmon->status = 0;
        // LD_HL(MON_HP);
        // ADD_HL_BC;
        // LD_D_H;
        // LD_E_L;
        // LD_A_addr(wCurPartySpecies);
        // CP_A(EGG);
        // IF_Z goto egg;
        if(wram->wCurPartySpecies != EGG) {
            // INC_HL;
            // INC_HL;
            // LD_A_hli;
            // LD_de_A;
            // LD_A_hl;
            // INC_DE;
            // LD_de_A;
            pmon->HP = pmon->maxHP;
            break;
        }

    // egg:
        // XOR_A_A;
        // LD_de_A;
        // INC_DE;
        // LD_de_A;
        pmon->HP = 0;
    } break;
    }

// CloseSRAM_And_ClearCarryFlag:
    Serialize_Box(GBToRAMAddr(sBox), &box);
    // CALL(aCloseSRAM);
    CloseSRAM();
    // AND_A_A;
    // RET;
    return false;
}

bool CloseSRAM_And_SetCarryFlag(const struct Box* box){
    Serialize_Box(GBToRAMAddr(sBox), box);
    // CALL(aCloseSRAM);
    CloseSRAM();
    // SCF;
    // RET;
    return true;
}

void RestorePPOfDepositedPokemon(struct Box* box, uint8_t b){
    // LD_A_B;
    // LD_HL(sBoxMons);
    // LD_BC(BOXMON_STRUCT_LENGTH);
    // CALL(aAddNTimes);
    // LD_B_H;
    // LD_C_L;
    struct BoxMon* bc = box->mons + b;
    // LD_HL(MON_PP);
    // ADD_HL_BC;
    // PUSH_HL;
    // PUSH_BC;
    // LD_DE(wTempMonPP);
    // LD_BC(NUM_MOVES);
    // CALL(aCopyBytes);
    CopyBytes(wram->wTempMon.mon.PP, bc->PP, sizeof(bc->PP));
    // POP_BC;
    // LD_HL(MON_MOVES);
    // ADD_HL_BC;
    // PUSH_HL;
    move_t* hl = bc->moves;
    // LD_DE(wTempMonMoves);
    // LD_BC(NUM_MOVES);
    // CALL(aCopyBytes);
    CopyBytes(wram->wTempMon.mon.moves, bc->moves, sizeof(bc->moves));
    // POP_HL;
    // POP_DE;
    uint8_t* de = bc->PP;

    // LD_A_addr(wMenuCursorY);
    // PUSH_AF;
    uint8_t menuCursorY = wram->wMenuCursorY;
    // LD_A_addr(wMonType);
    // PUSH_AF;
    uint8_t monType = wram->wMonType;
    // LD_B(0);
    b = 0;

    do {
    // loop:
        // LD_A_hli;
        // AND_A_A;
        // IF_Z goto done;
        if(*hl == NO_MOVE)
            break;
        // LD_addr_A(wTempMonMoves);
        wram->wTempMon.mon.moves[0] = *(hl++);
        // LD_A(BOXMON);
        // LD_addr_A(wMonType);
        // LD_A_B;
        // LD_addr_A(wMenuCursorY);
        // PUSH_BC;
        // PUSH_HL;
        // PUSH_DE;
        // FARCALL(aGetMaxPPOfMove);
        uint8_t pp = GetMaxPPOfMove(bc, BOXMON, b);
        // POP_DE;
        // POP_HL;
        // LD_A_addr(wTempPP);
        // LD_B_A;
        // LD_A_de;
        // AND_A(0b11000000);
        // ADD_A_B;
        // LD_de_A;
        *de = pp + (*de & 0b11000000);
        // POP_BC;
        // INC_DE;
        de++;
        // INC_B;
        // LD_A_B;
        // CP_A(NUM_MOVES);
        // IF_C goto loop;
    } while(++b != NUM_MOVES);

// done:
    // POP_AF;
    // LD_addr_A(wMonType);
    wram->wMonType = monType;
    // POP_AF;
    // LD_addr_A(wMenuCursorY);
    wram->wMenuCursorY = menuCursorY;
    // RET;
}

bool RetrieveMonFromDayCareMan(void){
    // LD_A_addr(wBreedMon1Species);
    // LD_addr_A(wCurPartySpecies);
    wram->wCurPartySpecies = gPokemon.breedMon1.species;
    // LD_DE(SFX_TRANSACTION);
    // CALL(aPlaySFX);
    PlaySFX(SFX_TRANSACTION);
    // CALL(aWaitSFX);
    WaitSFX();
    // CALL(aGetBreedMon1LevelGrowth);
    u8_pair_s lvlGrowth = GetBreedMon1LevelGrowth();
    // LD_A_B;
    // LD_addr_A(wPrevPartyLevel);
    wram->wPrevPartyLevel = lvlGrowth.a;
    // LD_A_E;
    // LD_addr_A(wCurPartyLevel);
    wram->wCurPartyLevel = lvlGrowth.b;
    // XOR_A_A;
    // LD_addr_A(wPokemonWithdrawDepositParameter);
    wram->wPokemonWithdrawDepositParameter = 0;
    // JP(mRetrieveBreedmon);
    return RetrieveBreedmon();
}

bool RetrieveMonFromDayCareLady(void){
    // LD_A_addr(wBreedMon2Species);
    // LD_addr_A(wCurPartySpecies);
    wram->wCurPartySpecies = gPokemon.breedMon2.species;
    // LD_DE(SFX_TRANSACTION);
    // CALL(aPlaySFX);
    PlaySFX(SFX_TRANSACTION);
    // CALL(aWaitSFX);
    WaitSFX();
    // CALL(aGetBreedMon2LevelGrowth);
    u8_pair_s lvlGrowth = GetBreedMon2LevelGrowth();
    // LD_A_B;
    // LD_addr_A(wPrevPartyLevel);
    wram->wPrevPartyLevel = lvlGrowth.a;
    // LD_A_E;
    // LD_addr_A(wCurPartyLevel);
    wram->wCurPartyLevel = lvlGrowth.b + lvlGrowth.a;
    // LD_A(PC_DEPOSIT);
    // LD_addr_A(wPokemonWithdrawDepositParameter);
    wram->wPokemonWithdrawDepositParameter = PC_DEPOSIT;
    // JP(mRetrieveBreedmon);  // pointless
    return RetrieveBreedmon();
}

bool RetrieveBreedmon(void){
    // LD_HL(wPartyCount);
    // LD_A_hl;
    // CP_A(PARTY_LENGTH);
    // IF_NZ goto room_in_party;
    if(gPokemon.partyCount >= PARTY_LENGTH) {
        // SCF;
        // RET;
        return true;
    }

// room_in_party:
    // INC_A;
    // LD_hl_A;
    uint8_t c = gPokemon.partyCount++;
    // LD_C_A;
    // LD_B(0);
    // ADD_HL_BC;
    species_t* sp = gPokemon.partySpecies + c;
    // LD_A_addr(wPokemonWithdrawDepositParameter);
    // AND_A_A;
    struct BoxMon* breedmon;
    uint8_t* nickname;
    uint8_t* ot;
    if(wram->wPokemonWithdrawDepositParameter == 0) {
        // LD_A_addr(wBreedMon1Species);
        breedmon = &gPokemon.breedMon1;
        // LD_DE(wBreedMon1Nickname);
        nickname = gPokemon.breedMon1Nickname;
        ot = gPokemon.breedMon1OT;
        // IF_Z goto okay;
    }
    else {
        // LD_A_addr(wBreedMon2Species);
        breedmon = &gPokemon.breedMon2;
        // LD_DE(wBreedMon2Nickname);
        nickname = gPokemon.breedMon2Nickname;
        ot = gPokemon.breedMon2OT;
    }

// okay:
    // LD_hli_A;
    *sp = breedmon->species;
    // LD_addr_A(wCurSpecies);
    wram->wCurSpecies = breedmon->species;
    // LD_A(0xff);
    // LD_hl_A;
    sp[1] = 0xff;
    // LD_HL(wPartyMonNicknames);
    // LD_A_addr(wPartyCount);
    // DEC_A;
    // CALL(aSkipNames);
    // PUSH_HL;
    // LD_H_D;
    // LD_L_E;
    // POP_DE;
    // CALL(aCopyBytes);
    CopyBytes(gPokemon.partyMonNickname[c], nickname, NAME_LENGTH);
    // PUSH_HL;
    // LD_HL(wPartyMonOTs);
    // LD_A_addr(wPartyCount);
    // DEC_A;
    // CALL(aSkipNames);
    // LD_D_H;
    // LD_E_L;
    // POP_HL;
    // CALL(aCopyBytes);
    CopyBytes(gPokemon.partyMonOT[c], ot, NAME_LENGTH);
    // PUSH_HL;
    // CALL(aGetLastPartyMon);
    // POP_HL;
    // LD_BC(BOXMON_STRUCT_LENGTH);
    // CALL(aCopyBytes);
    CopyBytes(&gPokemon.partyMon[c].mon, breedmon, BOXMON_STRUCT_LENGTH);
    // CALL(aGetBaseData);
    GetBaseData(wram->wCurSpecies);
    // CALL(aGetLastPartyMon);
    // LD_B_D;
    // LD_C_E;
    struct PartyMon* partymon = gPokemon.partyMon + c;
    // LD_HL(MON_LEVEL);
    // ADD_HL_BC;
    // LD_A_addr(wCurPartyLevel);
    // LD_hl_A;
    partymon->mon.level = wram->wCurPartyLevel;
    // LD_HL(MON_MAXHP);
    // ADD_HL_BC;
    // LD_D_H;
    // LD_E_L;
    // LD_HL(0xa);
    // ADD_HL_BC;
    // PUSH_BC;
    // LD_B(TRUE);
    // CALL(aCalcMonStats);
    CalcMonStats_PartyMon(partymon, TRUE);
    // LD_HL(wPartyMon1Moves);
    // LD_A_addr(wPartyCount);
    // DEC_A;
    // LD_BC(PARTYMON_STRUCT_LENGTH);
    // CALL(aAddNTimes);
    // LD_D_H;
    // LD_E_L;
    // LD_A(TRUE);
    // LD_addr_A(wSkipMovesBeforeLevelUp);
    wram->wSkipMovesBeforeLevelUp = TRUE;
    // PREDEF(pFillMoves);
    FillMoves(partymon->mon.moves, partymon->mon.PP, partymon->mon.species, partymon->mon.level);
    // LD_A_addr(wPartyCount);
    // DEC_A;
    // LD_addr_A(wCurPartyMon);
    // FARCALL(aHealPartyMon);
    HealPartyMon(partymon);
    // LD_A_addr(wCurPartyLevel);
    // LD_D_A;
    // CALLFAR(aCalcExpAtLevel);
    uint32_t exp = CalcExpAtLevel(wram->wCurPartyLevel);
    // POP_BC;
    // LD_HL(0x8);
    // ADD_HL_BC;
    // LDH_A_addr(hMultiplicand);
    // LD_hli_A;
    partymon->mon.exp[0] = LOW(exp);
    // LDH_A_addr(hMultiplicand + 1);
    // LD_hli_A;
    partymon->mon.exp[1] = HIGH(exp);
    // LDH_A_addr(hMultiplicand + 2);
    // LD_hl_A;
    partymon->mon.exp[2] = (exp >> 16) & 0xff;
    // AND_A_A;
    // RET;
    return false;
}

void GetLastPartyMon(void){
    LD_A_addr(wPartyCount);
    DEC_A;
    LD_HL(wPartyMon1Species);
    LD_BC(PARTYMON_STRUCT_LENGTH);
    CALL(aAddNTimes);
    LD_D_H;
    LD_E_L;
    RET;

}

void DepositMonWithDayCareMan(uint8_t a){
    // LD_DE(wBreedMon1Nickname);
    // CALL(aDepositBreedmon);
    DepositBreedmon(gPokemon.breedMon1Nickname, gPokemon.breedMon1OT, &gPokemon.breedMon1, a);
    // XOR_A_A;  // REMOVE_PARTY
    // LD_addr_A(wPokemonWithdrawDepositParameter);
    // JP(mRemoveMonFromPartyOrBox);
    RemoveMonFromPartyOrBox(REMOVE_PARTY);
}

void DepositMonWithDayCareLady(uint8_t a){
    // LD_DE(wBreedMon2Nickname);
    // CALL(aDepositBreedmon);
    DepositBreedmon(gPokemon.breedMon2Nickname, gPokemon.breedMon2OT, &gPokemon.breedMon2, a);
    // XOR_A_A;  // REMOVE_PARTY
    // LD_addr_A(wPokemonWithdrawDepositParameter);
    // JP(mRemoveMonFromPartyOrBox);
    RemoveMonFromPartyOrBox(REMOVE_PARTY);
}

static void DepositBreedmon(uint8_t* nickname, uint8_t* ot, struct BoxMon* de, uint8_t a){
    // LD_A_addr(wCurPartyMon);
    // LD_HL(wPartyMonNicknames);
    // CALL(aSkipNames);
    // CALL(aCopyBytes);
    CopyBytes(nickname, gPokemon.partyMonNickname[a], NAME_LENGTH);
    // LD_A_addr(wCurPartyMon);
    // LD_HL(wPartyMonOTs);
    // CALL(aSkipNames);
    // CALL(aCopyBytes);
    CopyBytes(ot, gPokemon.partyMonOT[a], NAME_LENGTH);
    // LD_A_addr(wCurPartyMon);
    // LD_HL(wPartyMon1Species);
    // LD_BC(PARTYMON_STRUCT_LENGTH);
    // CALL(aAddNTimes);
    // LD_BC(BOXMON_STRUCT_LENGTH);
    // JP(mCopyBytes);
    CopyBytes(de, gPokemon.partyMon + a, BOXMON_STRUCT_LENGTH);
}

//  Sends the mon into one of Bills Boxes
//  the data comes mainly from 'wEnemyMon:'
bool SendMonIntoBox(void){
    // LD_A(BANK(sBoxCount));
    // CALL(aOpenSRAM);
    OpenSRAM(MBANK(asBoxCount));
    struct Box box;
    Deserialize_Box(&box, GBToRAMAddr(sBox));
    // LD_DE(sBoxCount);
    // LD_A_de;
    uint8_t boxCount = box.count;
    // CP_A(MONS_PER_BOX);
    // JP_NC (mSendMonIntoBox_full);
    if(boxCount >= MONS_PER_BOX) {
    // full:
        // CALL(aCloseSRAM);
        CloseSRAM();
        // AND_A_A;
        // RET;
        return false;
    }
    // INC_A;
    // LD_de_A;
    box.count++;
    // LD_A_addr(wCurPartySpecies);
    // LD_addr_A(wCurSpecies);
    wram->wCurSpecies = wram->wCurPartySpecies;
    // LD_C_A;
    species_t* de = box.species;
    species_t c = wram->wCurPartySpecies;
    species_t a;
    do {
    // loop:
        // INC_DE;
        // LD_A_de;
        a = *de;
        // LD_B_A;
        species_t b = a;
        // LD_A_C;
        a = c;
        // LD_C_B;
        c = b;
        // LD_de_A;
        *de = a;
        de++;
        // INC_A;
        // IF_NZ goto loop;
    } while(a != 0xff);

    // CALL(aGetBaseData);
    GetBaseData(wram->wCurPartySpecies);
    // CALL(aShiftBoxMon);
    ShiftBoxMon(&box);

    // LD_HL(wPlayerName);
    // LD_DE(sBoxMonOTs);
    // LD_BC(NAME_LENGTH);
    // CALL(aCopyBytes);
    CopyBytes(box.monOT[0], wram->wPlayerName, NAME_LENGTH);

    // LD_A_addr(wCurPartySpecies);
    // LD_addr_A(wNamedObjectIndex);
    // CALL(aGetPokemonName);
    GetPokemonName(wram->wCurPartySpecies);

    // LD_DE(sBoxMonNicknames);
    // LD_HL(wStringBuffer1);
    // LD_BC(MON_NAME_LENGTH);
    // CALL(aCopyBytes);
    CopyBytes(box.monNicknames[0], wram->wStringBuffer1, MON_NAME_LENGTH);

    // LD_HL(wEnemyMon);
    // LD_DE(sBoxMon1);
    struct BoxMon* boxmon = box.mons;
    // LD_BC(1 + 1 + NUM_MOVES);  // species + item + moves
    // CALL(aCopyBytes);
    CopyBytes(boxmon, &wram->wEnemyMon, sizeof(species_t) + sizeof(item_t) + sizeof(move_t) * NUM_MOVES);

    // LD_HL(wPlayerID);
    // LD_A_hli;
    // LD_de_A;
    // INC_DE;
    // LD_A_hl;
    // LD_de_A;
    boxmon->id = wram->wPlayerID;
    // INC_DE;
    // PUSH_DE;
    // LD_A_addr(wCurPartyLevel);
    // LD_D_A;
    // CALLFAR(aCalcExpAtLevel);
    uint32_t exp = CalcExpAtLevel(wram->wCurPartyLevel);
    // POP_DE;
    // LDH_A_addr(hProduct + 1);
    // LD_de_A;
    boxmon->exp[0] = HIGH(exp >> 8);
    // INC_DE;
    // LDH_A_addr(hProduct + 2);
    // LD_de_A;
    boxmon->exp[1] = HIGH(exp);
    // INC_DE;
    // LDH_A_addr(hProduct + 3);
    // LD_de_A;
    boxmon->exp[2] = LOW(exp);
    // INC_DE;

// Set all 5 Experience Values to 0
    // XOR_A_A;
    // LD_B(2 * 5);

    for(uint8_t b = 0; b < 5; b++) {
    // loop2:
        // LD_de_A;
        boxmon->statExp[b] = 0x0;
        // INC_DE;
        // DEC_B;
        // IF_NZ goto loop2;
    }

    // LD_HL(wEnemyMonDVs);
    // LD_B(2 + NUM_MOVES);  // DVs and PP // wEnemyMonHappiness - wEnemyMonDVs

// loop3:
    // LD_A_hli;
    // LD_de_A;
    // INC_DE;
    // DEC_B;
    // IF_NZ goto loop3;
    boxmon->DVs = wram->wEnemyMon.dvs;
    CopyBytes(boxmon->PP, wram->wEnemyMon.pp, sizeof(boxmon->PP));

    // LD_A(BASE_HAPPINESS);
    // LD_de_A;
    boxmon->happiness = BASE_HAPPINESS;
    // INC_DE;
    // XOR_A_A;
    // LD_de_A;
    boxmon->pokerusStatus = 0x0;
    // INC_DE;
    // LD_de_A;
    boxmon->caughtTimeLevel = 0x0;
    // INC_DE;
    // LD_de_A;
    boxmon->caughtGenderLocation = 0x0;
    // INC_DE;
    // LD_A_addr(wCurPartyLevel);
    // LD_de_A;
    boxmon->level = wram->wCurPartyLevel;
    // LD_A_addr(wCurPartySpecies);
    // DEC_A;
    // CALL(aSetSeenAndCaughtMon);
    SetSeenAndCaughtMon(wram->wCurPartySpecies - 1);
    // LD_A_addr(wCurPartySpecies);
    // CP_A(UNOWN);
    // IF_NZ goto not_unown;
    if(wram->wCurPartySpecies == UNOWN) {
        // LD_HL(sBoxMon1DVs);
        // PREDEF(pGetUnownLetter);
        // CALLFAR(aUpdateUnownDex);
        UpdateUnownDex(GetUnownLetter(boxmon->DVs));
    }

// not_unown:
    // LD_HL(sBoxMon1Moves);
    // LD_DE(wTempMonMoves);
    // LD_BC(NUM_MOVES);
    // CALL(aCopyBytes);
    CopyBytes(boxmon->moves, wram->wTempMon.mon.moves, sizeof(boxmon->moves));

    // LD_HL(sBoxMon1PP);
    // LD_DE(wTempMonPP);
    // LD_BC(NUM_MOVES);
    // CALL(aCopyBytes);
    CopyBytes(boxmon->PP, wram->wTempMon.mon.PP, sizeof(boxmon->PP));

    // LD_B(0);
    // CALL(aRestorePPOfDepositedPokemon);
    RestorePPOfDepositedPokemon(&box, 0);

    Serialize_Box(GBToRAMAddr(sBox), &box);
    // CALL(aCloseSRAM);
    CloseSRAM();
    // SCF;
    // RET;
    return true;
}

static void ShiftBoxMon_shift(void* hl_, uint8_t count, uint16_t bc) {
    // LD_A_addr(sBoxCount);
    uint8_t boxCount = count;
    // CP_A(2);
    // RET_C ;
    if(boxCount < 2)
        return;

    // PUSH_HL;
    // CALL(aAddNTimes);
    // DEC_HL;
    // LD_E_L;
    // LD_D_H;
    // POP_HL;
    uint8_t* de = ((uint8_t*)hl_) + (bc * boxCount) - 1;

    // LD_A_addr(sBoxCount);
    // DEC_A;
    // CALL(aAddNTimes);
    // DEC_HL;
    uint8_t* hl = ((uint8_t*)hl_) + (bc * (boxCount - 1)) - 1;

    // PUSH_HL;
    // LD_A_addr(sBoxCount);
    // DEC_A;
    // LD_HL(0);
    // CALL(aAddNTimes);
    // LD_C_L;
    // LD_B_H;
    bc = bc * (boxCount - 1);
    // POP_HL;

    do {
    // loop:
        // LD_A_hld;
        // LD_de_A;
        *(de--) = *(hl--);
        // DEC_DE;
        // DEC_BC;
        // LD_A_C;
        // OR_A_B;
        // IF_NZ goto loop;
    } while(--bc != 0);
    // RET;
}

static void ShiftBoxMon(struct Box* box){
    // LD_HL(sBoxMonOTs);
    // LD_BC(NAME_LENGTH);
    // CALL(aShiftBoxMon_shift);
    ShiftBoxMon_shift(box->monOT[0], box->count, NAME_LENGTH);

    // LD_HL(sBoxMonNicknames);
    // LD_BC(MON_NAME_LENGTH);
    // CALL(aShiftBoxMon_shift);
    ShiftBoxMon_shift(box->monNicknames[0], box->count, MON_NAME_LENGTH);

    // LD_HL(sBoxMons);
    // LD_BC(BOXMON_STRUCT_LENGTH);
    ShiftBoxMon_shift(box->mons, box->count, sizeof(struct BoxMon));
}

bool GiveEgg(void){
    // LD_A_addr(wCurPartySpecies);
    // PUSH_AF;
    species_t a = wram->wCurPartySpecies;
    // CALLFAR(aGetPreEvolution);
    // CALLFAR(aGetPreEvolution);
    wram->wCurPartySpecies = GetPreEvolution(GetPreEvolution(wram->wCurPartySpecies));
    // LD_A_addr(wCurPartySpecies);
    // DEC_A;
    species_t pspecies = wram->wCurPartySpecies - 1;

//  TryAddMonToParty sets Seen and Caught flags
//  when it is successful.  This routine will make
//  sure that we aren't newly setting flags.
    // PUSH_AF;
    // CALL(aCheckCaughtMon);
    bool caught = CheckCaughtMon(pspecies);
    // POP_AF;
    // PUSH_BC;
    // CALL(aCheckSeenMon);
    bool seen = CheckSeenMon(pspecies);
    // PUSH_BC;

    // CALL(aTryAddMonToParty);
    TryAddMonToParty(wram->wCurPartySpecies, wram->wCurPartyLevel);

//  If we haven't caught this Pokemon before receiving
//  the Egg, reset the flag that was just set by
//  TryAddMonToParty.
    // POP_BC;
    // LD_A_C;
    // AND_A_A;
    // IF_NZ goto skip_caught_flag;
    if(!caught) {
        // LD_A_addr(wCurPartySpecies);
        // DEC_A;
        // LD_C_A;
        // LD_D(0x0);
        // LD_HL(wPokedexCaught);
        // LD_B(RESET_FLAG);
        // PREDEF(pSmallFarFlagAction);
        SmallFarFlagAction(gPokemon.pokedexCaught, pspecies, RESET_FLAG);
    }

// skip_caught_flag:
//  If we haven't seen this Pokemon before receiving
//  the Egg, reset the flag that was just set by
//  TryAddMonToParty.
    // POP_BC;
    // LD_A_C;
    // AND_A_A;
    // IF_NZ goto skip_seen_flag;
    if(!seen) {
        // LD_A_addr(wCurPartySpecies);
        // DEC_A;
        // LD_C_A;
        // LD_D(0x0);
        // LD_HL(wPokedexSeen);
        // LD_B(RESET_FLAG);
        // PREDEF(pSmallFarFlagAction);
        SmallFarFlagAction(gPokemon.pokedexSeen, pspecies, RESET_FLAG);
    }

// skip_seen_flag:
    // POP_AF;
    // LD_addr_A(wCurPartySpecies);
    wram->wCurPartySpecies = a;
    // LD_A_addr(wPartyCount);
    // DEC_A;
    // LD_BC(PARTYMON_STRUCT_LENGTH);
    // LD_HL(wPartyMon1Species);
    // CALL(aAddNTimes);
    // LD_A_addr(wCurPartySpecies);
    // LD_hl_A;
    gPokemon.partyMon[gPokemon.partyCount - 1].mon.species = wram->wCurPartySpecies;
    // LD_HL(wPartyCount);
    // LD_A_hl;
    // LD_B(0);
    // LD_C_A;
    // ADD_HL_BC;
    // LD_A(EGG);
    // LD_hl_A;
    gPokemon.partySpecies[gPokemon.partyCount - 1] = EGG;
    // LD_A_addr(wPartyCount);
    // DEC_A;
    // LD_HL(wPartyMonNicknames);
    // CALL(aSkipNames);
    // LD_DE(mString_Egg);
    // CALL(aCopyName2);
    U82CA(gPokemon.partyMonNickname[gPokemon.partyCount - 1], String_Egg);
    // LD_A_addr(wPartyCount);
    // DEC_A;
    // LD_HL(wPartyMon1Happiness);
    // LD_BC(PARTYMON_STRUCT_LENGTH);
    // CALL(aAddNTimes);
    // LD_A_addr(wDebugFlags);
    // BIT_A(DEBUG_FIELD_F);
    if(bit_test(wram->wDebugFlags, DEBUG_FIELD_F)) {
        gPokemon.partyMon[gPokemon.partyCount - 1].mon.happiness = 1;
    }
    else {
        gPokemon.partyMon[gPokemon.partyCount - 1].mon.happiness = wram->wBaseEggSteps;
    }
    // LD_A(1);
    // IF_NZ goto got_init_happiness;
    // LD_A_addr(wBaseEggSteps);


// got_init_happiness:
    // LD_hl_A;
    // LD_A_addr(wPartyCount);
    // DEC_A;
    // LD_HL(wPartyMon1HP);
    // LD_BC(PARTYMON_STRUCT_LENGTH);
    // CALL(aAddNTimes);
    // XOR_A_A;
    // LD_hli_A;
    // LD_hl_A;
    gPokemon.partyMon[gPokemon.partyCount - 1].HP = 0;
    // AND_A_A;
    // RET;
    return true;
}

const char String_Egg[] = "EGG@";

void RemoveMonFromPartyOrBox(uint8_t param){
    // LD_HL(wPartyCount);

    // LD_A_addr(wPokemonWithdrawDepositParameter);
    // AND_A_A;
    // IF_Z goto okay;

    species_t* wptr;
    if(param == REMOVE_PARTY) {
    // okay:
        // LD_A_hl;
        // DEC_A;
        // LD_hli_A;
        gPokemon.partyCount--;
        wptr = gPokemon.partySpecies + wram->wCurPartyMon;
        species_t a;
        do {
        // loop:
            // LD_A_de;
            // INC_DE;
            a = wptr[1];
            // LD_hli_A;
            *(wptr++) = a;
            // INC_A;
            // IF_NZ goto loop;
        } while(a != 0xff);
        // LD_HL(wPartyMonOTs);
        // LD_D(PARTY_LENGTH - 1);
        uint8_t d = PARTY_LENGTH - 1;
        // LD_A_addr(wPokemonWithdrawDepositParameter);
        // AND_A_A;
        // IF_Z goto party;
        // LD_HL(sBoxMonOTs);
        // LD_D(MONS_PER_BOX - 1);


    // party:
    // If this is the last mon in our party (box),
    // shift all the other mons up to close the gap.
        // LD_A_addr(wCurPartyMon);
        // CALL(aSkipNames);
        // LD_A_addr(wCurPartyMon);
        // CP_A_D;
        // IF_NZ goto delete_inside;
        if(wram->wCurPartyMon == d) {
            // LD_hl(-1);
            gPokemon.partyMonOT[wram->wCurPartyMon][0] = -1;
            // JP(mRemoveMonFromPartyOrBox_finish);
            // goto finish;
        }
        else {
        // delete_inside:
        // Shift the OT names
            // LD_D_H;
            // LD_E_L;
            // LD_BC(MON_NAME_LENGTH);
            // ADD_HL_BC;
            // LD_BC(wPartyMonNicknames);
            // LD_A_addr(wPokemonWithdrawDepositParameter);
            // AND_A_A;
            // IF_Z goto party2;
            // LD_BC(sBoxMonNicknames);

        // party2:
            // CALL(aCopyDataUntil);
            CopyDataUntil(gPokemon.partyMonOT[wram->wCurPartyMon], 
                gPokemon.partyMonOT[wram->wCurPartyMon] + MON_NAME_LENGTH,
                gPokemon.partyMonNickname);
        // Shift the struct
            // LD_HL(wPartyMons);
            // LD_BC(PARTYMON_STRUCT_LENGTH);
            // LD_A_addr(wPokemonWithdrawDepositParameter);
            // AND_A_A;
            // IF_Z goto party4;
            // LD_HL(sBoxMons);
            // LD_BC(BOXMON_STRUCT_LENGTH);

        // party4:
            // LD_A_addr(wCurPartyMon);
            // CALL(aAddNTimes);
            // LD_D_H;
            // LD_E_L;
            // LD_A_addr(wPokemonWithdrawDepositParameter);
            // AND_A_A;
            // IF_Z goto party5;
            // LD_BC(BOXMON_STRUCT_LENGTH);
            // ADD_HL_BC;
            // LD_BC(sBoxMonOTs);
            // goto copy;


        // party5:
            // LD_BC(PARTYMON_STRUCT_LENGTH);
            // ADD_HL_BC;
            // LD_BC(wPartyMonOTs);

        // copy:
            // CALL(aCopyDataUntil);
            CopyDataUntil(gPokemon.partyMon + wram->wCurPartyMon, 
                gPokemon.partyMon + wram->wCurPartyMon + 1,
                gPokemon.partyMonOT);
        // Shift the nicknames
            // LD_HL(wPartyMonNicknames);
            // LD_A_addr(wPokemonWithdrawDepositParameter);
            // AND_A_A;
            // IF_Z goto party6;
            // LD_HL(sBoxMonNicknames);

        // party6:
            // LD_BC(MON_NAME_LENGTH);
            // LD_A_addr(wCurPartyMon);
            // CALL(aAddNTimes);
            // LD_D_H;
            // LD_E_L;
            // LD_BC(MON_NAME_LENGTH);
            // ADD_HL_BC;
            // LD_BC(wPartyMonNicknamesEnd);
            // LD_A_addr(wPokemonWithdrawDepositParameter);
            // AND_A_A;
            // IF_Z goto party7;
            // LD_BC(sBoxMonNicknamesEnd);

        // party7:
            // CALL(aCopyDataUntil);
            CopyDataUntil(gPokemon.partyMonNickname[wram->wCurPartyMon], 
                gPokemon.partyMonNickname[wram->wCurPartyMon + 1],
                gPokemon.partyMonNicknamesEnd);
        // Mail time!
        }
    // finish:
        // LD_A_addr(wPokemonWithdrawDepositParameter);
        // AND_A_A;
        // JP_NZ (mCloseSRAM);
        if(param != REMOVE_PARTY)
            return CloseSRAM();
        // LD_A_addr(wLinkMode);
        // AND_A_A;
        // RET_NZ ;
        if(wram->wLinkMode != LINK_NULL)
            return;
    // Shift mail
        // LD_A(BANK(sPartyMail));
        // CALL(aOpenSRAM);
        OpenSRAM(MBANK(asPartyMail));
    // If this is the last mon in our party, no need to shift mail.
        // LD_HL(wPartyCount);
        // LD_A_addr(wCurPartyMon);
        // CP_A_hl;
        // IF_Z goto close_sram;
        if(gPokemon.partyCount == wram->wCurPartyMon)
            return CloseSRAM();
    // Shift our mail messages up.
        // LD_HL(sPartyMail);
        // LD_BC(MAIL_STRUCT_LENGTH);
        // CALL(aAddNTimes);
        // PUSH_HL;
        // ADD_HL_BC;
        // POP_DE;
        uint16_t mail = sPartyMail + (wram->wCurPartyMon * MAIL_STRUCT_LENGTH);
        uint16_t mail2 = mail + MAIL_STRUCT_LENGTH;
        // LD_A_addr(wCurPartyMon);
        // LD_B_A;
        uint8_t b = wram->wCurPartyMon;

        do {
        // loop2:
            // PUSH_BC;
            // PUSH_HL;
            // LD_BC(MAIL_STRUCT_LENGTH);
            // CALL(aCopyBytes);
            CopyBytes_GB(mail, mail2, MAIL_STRUCT_LENGTH);
            // POP_HL;
            // PUSH_HL;
            // LD_BC(MAIL_STRUCT_LENGTH);
            mail = mail2;
            mail2 += MAIL_STRUCT_LENGTH;
            // ADD_HL_BC;
            // POP_DE;
            // POP_BC;
            // INC_B;
            // LD_A_addr(wPartyCount);
            // CP_A_B;
            // IF_NZ goto loop2;
        } while(++b != gPokemon.partyCount);

    // close_sram:
        // JP(mCloseSRAM);
        return CloseSRAM();
    }
    else {
        // LD_A(BANK(sBoxCount));
        // CALL(aOpenSRAM);
        struct Box box;
        OpenSRAM(MBANK(asBoxCount));
        Deserialize_Box(&box, GBToRAMAddr(sBox));
        // LD_HL(sBoxCount);
        box.count--;
        species_t* spec = box.species + wram->wCurPartyMon;
        species_t a;
        do {
        // loop:
            // LD_A_de;
            a = spec[1];
            // INC_DE;
            // LD_hli_A;
            *(spec++) = a;
            // INC_A;
            // IF_NZ goto loop;
        } while(a != 0xff);

        // LD_A_addr(wCurPartyMon);
        // LD_C_A;
        // LD_B(0);
        // ADD_HL_BC;
        // LD_E_L;
        // LD_D_H;
        // INC_DE;

        // LD_HL(wPartyMonOTs);
        // LD_D(PARTY_LENGTH - 1);
        // LD_A_addr(wPokemonWithdrawDepositParameter);
        // AND_A_A;
        // IF_Z goto party;
        // LD_HL(sBoxMonOTs);
        uint8_t (*ots)[NAME_LENGTH] = box.monOT;
        // LD_D(MONS_PER_BOX - 1);
        uint8_t d = MONS_PER_BOX - 1;

    // party:
    // If this is the last mon in our party (box),
    // shift all the other mons up to close the gap.
        // LD_A_addr(wCurPartyMon);
        // CALL(aSkipNames);
        // LD_A_addr(wCurPartyMon);
        // CP_A_D;
        // IF_NZ goto delete_inside;
        if(wram->wCurPartyMon == d) {
            // LD_hl(-1);
            // JP(mRemoveMonFromPartyOrBox_finish);
            ots[wram->wCurPartyMon][0] = -1;
        }
        else {
        // delete_inside:
        // Shift the OT names
            // LD_D_H;
            // LD_E_L;
            // LD_BC(MON_NAME_LENGTH);
            // ADD_HL_BC;
            // LD_BC(wPartyMonNicknames);
            // LD_A_addr(wPokemonWithdrawDepositParameter);
            // AND_A_A;
            // IF_Z goto party2;
            // LD_BC(sBoxMonNicknames);

        // party2:
            // CALL(aCopyDataUntil);
            CopyDataUntil(ots[wram->wCurPartyMon], 
                ots[wram->wCurPartyMon] + MON_NAME_LENGTH,
                box.monNicknames[0]);
        // Shift the struct
            // LD_HL(wPartyMons);
            // LD_BC(PARTYMON_STRUCT_LENGTH);
            // LD_A_addr(wPokemonWithdrawDepositParameter);
            // AND_A_A;
            // IF_Z goto party4;
            // LD_HL(sBoxMons);
            // LD_BC(BOXMON_STRUCT_LENGTH);

        // party4:
            // LD_A_addr(wCurPartyMon);
            // CALL(aAddNTimes);
            // LD_D_H;
            // LD_E_L;
            // LD_A_addr(wPokemonWithdrawDepositParameter);
            // AND_A_A;
            // IF_Z goto party5;
            // LD_BC(BOXMON_STRUCT_LENGTH);
            // ADD_HL_BC;
            // LD_BC(sBoxMonOTs);
            // goto copy;


        // party5:
            // LD_BC(PARTYMON_STRUCT_LENGTH);
            // ADD_HL_BC;
            // LD_BC(wPartyMonOTs);

        // copy:
            struct BoxMon* boxMons = box.mons;
            // CALL(aCopyDataUntil);
            CopyDataUntil(boxMons + wram->wCurPartyMon, 
                boxMons + wram->wCurPartyMon + 1,
                boxMons + MONS_PER_BOX);
        // Shift the nicknames
            // LD_HL(wPartyMonNicknames);
            // LD_A_addr(wPokemonWithdrawDepositParameter);
            // AND_A_A;
            // IF_Z goto party6;
            // LD_HL(sBoxMonNicknames);

        // party6:
            // LD_BC(MON_NAME_LENGTH);
            // LD_A_addr(wCurPartyMon);
            // CALL(aAddNTimes);
            // LD_D_H;
            // LD_E_L;
            // LD_BC(MON_NAME_LENGTH);
            // ADD_HL_BC;
            // LD_BC(wPartyMonNicknamesEnd);
            // LD_A_addr(wPokemonWithdrawDepositParameter);
            // AND_A_A;
            // IF_Z goto party7;
            // LD_BC(sBoxMonNicknamesEnd);

        // party7:
            uint8_t (*nicknames)[MON_NAME_LENGTH] = box.monNicknames;
            // CALL(aCopyDataUntil);
            CopyDataUntil(nicknames[wram->wCurPartyMon], 
                nicknames[wram->wCurPartyMon + 1],
                nicknames[MONS_PER_BOX]);
        }
    // Mail time!
        Serialize_Box(GBToRAMAddr(sBox), &box);
        return CloseSRAM();
    // finish:
        // LD_A_addr(wPokemonWithdrawDepositParameter);
        // AND_A_A;
        // JP_NZ (mCloseSRAM);
        // LD_A_addr(wLinkMode);
        // AND_A_A;
        // RET_NZ ;
    // Shift mail
        // LD_A(BANK(sPartyMail));
        // CALL(aOpenSRAM);
    // If this is the last mon in our party, no need to shift mail.
        // LD_HL(wPartyCount);
        // LD_A_addr(wCurPartyMon);
        // CP_A_hl;
        // IF_Z goto close_sram;
    // Shift our mail messages up.
        // LD_HL(sPartyMail);
        // LD_BC(MAIL_STRUCT_LENGTH);
        // CALL(aAddNTimes);
        // PUSH_HL;
        // ADD_HL_BC;
        // POP_DE;
        // LD_A_addr(wCurPartyMon);
        // LD_B_A;

    // loop2:
        // PUSH_BC;
        // PUSH_HL;
        // LD_BC(MAIL_STRUCT_LENGTH);
        // CALL(aCopyBytes);
        // POP_HL;
        // PUSH_HL;
        // LD_BC(MAIL_STRUCT_LENGTH);
        // ADD_HL_BC;
        // POP_DE;
        // POP_BC;
        // INC_B;
        // LD_A_addr(wPartyCount);
        // CP_A_B;
        // IF_NZ goto loop2;

    // close_sram:
        // JP(mCloseSRAM);
    }
}

void ComputeNPCTrademonStats(uint8_t curPartyMon){
    // LD_A(MON_LEVEL);
    // CALL(aGetPartyParamLocation);
    struct PartyMon* bc = &gPokemon.partyMon[curPartyMon];
    // LD_A_hl;
    // LD_addr_A(MON_LEVEL);  // should be "ld [wCurPartyLevel], a"
    wram->wCurPartyLevel = bc->mon.level;
    // LD_A(MON_SPECIES);
    // CALL(aGetPartyParamLocation);
    // LD_A_hl;
    // LD_addr_A(wCurSpecies);
    wram->wCurSpecies = bc->mon.species;
    // CALL(aGetBaseData);
    GetBaseData(bc->mon.species);
    // LD_A(MON_MAXHP);
    // CALL(aGetPartyParamLocation);
    // LD_D_H;
    // LD_E_L;
    // PUSH_DE;
    // LD_A(MON_STAT_EXP - 1);
    // CALL(aGetPartyParamLocation);
    // LD_B(TRUE);
    // CALL(aCalcMonStats);
    CalcMonStats_PartyMon(bc, TRUE);
    // POP_DE;
    // LD_A(MON_HP);
    // CALL(aGetPartyParamLocation);
    // LD_A_de;
    // INC_DE;
    // LD_hli_A;
    // LD_A_de;
    // LD_hl_A;
    bc->HP = bc->maxHP;
    // RET;
}

//  Calculates all 6 Stats of a mon
//  b: Take into account stat EXP if TRUE
//  'c' counts from 1-6 and points with 'wBaseStats' to the base value
//  hl is the path to the Stat EXP
//  de points to where the final stats will be saved
void CalcMonStats(uint16_t* stats, const uint16_t* statExp, uint16_t dvs, uint8_t b){
    // LD_C(STAT_HP - 1);  // first stat
    uint8_t c = STAT_HP;

    while(c < STAT_SDEF + 1) {
    // loop:
        // INC_C;
        // CALL(aCalcMonStatC);
        uint16_t stat = NativeToBigEndian16(CalcMonStatC(statExp, dvs, b, c));
        printf("Stat[%d]: %d\n", c - STAT_HP, BigEndianToNative16(stat));
        // LDH_A_addr(hMultiplicand + 1);
        // LD_de_A;
        // INC_DE;
        // LDH_A_addr(hMultiplicand + 2);
        // LD_de_A;
        // INC_DE;
        stats[c - STAT_HP] = stat;
        // LD_A_C;
        // CP_A(STAT_SDEF);  // last stat
        // IF_NZ goto loop;
        c++;
    }
    // RET;
}

void CalcMonStats_PartyMon(struct PartyMon* mon, uint8_t b){
#if !defined(_MSC_VER)
    // MSVC doesn't like this
    const uint16_t* statxp = (uint16_t*)((uint8_t*)mon + offsetof(struct BoxMon, statExp));
    uint16_t* stats = (uint16_t*)((uint8_t*)mon + offsetof(struct PartyMon, maxHP));
#else
    // GCC doesn't like this
    const uint16_t* statxp = ((const struct BoxMon*)mon)->statExp;
    uint16_t* stats = ((const struct PartyMon*)mon)->maxHP;
#endif
    return CalcMonStats(stats, statxp, mon->mon.DVs, b);
}

void CalcMonStats_BattleMon(struct BattleMon* mon){
    uint16_t* stats = (uint16_t*)((uint8_t*)&wram->wEnemyMon + offsetof(struct BattleMon, maxHP));
    return CalcMonStats(stats, NULL, mon->dvs, FALSE);
}

//  'c' is 1-6 and points to the BaseStat
//  1: HP
//  2: Attack
//  3: Defense
//  4: Speed
//  5: SpAtk
//  6: SpDef
uint16_t CalcMonStatC(const uint16_t* statExp, uint16_t dvs, uint8_t b, uint8_t c){
    // PUSH_HL;
    // PUSH_DE;
    // PUSH_BC;
    // LD_A_B;
    // LD_D_A;
    uint8_t d = b;
    // PUSH_HL;
    // LD_HL(wBaseStats);
    // DEC_HL;  // has to be decreased, because 'c' begins with 1
    // LD_B(0);
    b = 0;
    // ADD_HL_BC;
    // LD_A_hl;
    // LD_E_A;
    uint8_t e = wram->wBaseStats[c - 1];
    // POP_HL;
    // PUSH_HL;
    // LD_A_C;
    // CP_A(STAT_SDEF);  // last stat
    // IF_NZ goto not_spdef;
    if(c == STAT_SDEF) {
        // DEC_HL;
        // DEC_HL;
        statExp--;
    }

// not_spdef:
    // SLA_C;
    // LD_A_D;
    // AND_A_A;
    // IF_Z goto no_stat_exp;
    if(d) {
        // ADD_HL_BC;
        // PUSH_DE;
        // LD_A_hld;
        // LD_E_A;
        // LD_D_hl;
        uint16_t de = BigEndianToNative16(statExp[c]);
        // FARCALL(aGetSquareRoot);
        b = GetSquareRoot(de);
        // POP_DE;
    }

// no_stat_exp:
    // SRL_C;
    // POP_HL;
    // PUSH_BC;
    // LD_BC(MON_DVS - MON_HP_EXP + 1);
    // ADD_HL_BC;
    // POP_BC;
    // LD_A_C;
    uint8_t dv;
    switch(c) {
        // CP_A(STAT_ATK);
        // IF_Z goto Attack;
        case STAT_ATK:
        // Attack:
            // LD_A_hl;
            // SWAP_A;
            // AND_A(0xf);
            dv = (LOW(dvs) >> 4) & 0xf;
            // goto GotDV;
            break;
        // CP_A(STAT_DEF);
        // IF_Z goto Defense;
        case STAT_DEF:
        // Defense:
            // LD_A_hl;
            // AND_A(0xf);
            dv = LOW(dvs) & 0xf;
            // goto GotDV;
            break;
        // CP_A(STAT_SPD);
        // IF_Z goto Speed;
        case STAT_SPD:
        // Speed:
            // INC_HL;
            // LD_A_hl;
            // SWAP_A;
            // AND_A(0xf);
            dv = (HIGH(dvs) >> 4) & 0xf;
            // goto GotDV;
            break;
        // CP_A(STAT_SATK);
        // IF_Z goto Special;
        // CP_A(STAT_SDEF);
        // IF_Z goto Special;
        case STAT_SATK:
        case STAT_SDEF:
        // Special:
            // INC_HL;
            // LD_A_hl;
            // AND_A(0xf);
            dv = HIGH(dvs) & 0xf;
            break;
    //  DV_HP = (DV_ATK & 1) << 3 | (DV_DEF & 1) << 2 | (DV_SPD & 1) << 1 | (DV_SPC & 1)
        default:
        case STAT_HP:
            // PUSH_BC;
            // LD_A_hl;
            // SWAP_A;
            // AND_A(1);
            // ADD_A_A;
            // ADD_A_A;
            // ADD_A_A;
            // LD_B_A;
            dv = (LOW(dvs) & 0x10) >> 1;
            // LD_A_hli;
            // AND_A(1);
            // ADD_A_A;
            // ADD_A_A;
            // ADD_A_B;
            // LD_B_A;
            dv += (LOW(dvs) & 0x1) << 2;
            // LD_A_hl;
            // SWAP_A;
            // AND_A(1);
            // ADD_A_A;
            // ADD_A_B;
            // LD_B_A;
            dv += (HIGH(dvs) & 0x10) >> 3;
            // LD_A_hl;
            // AND_A(1);
            // ADD_A_B;
            dv += (HIGH(dvs) & 0x1);
            // POP_BC;
            // goto GotDV;
            break;
    }


// GotDV:
    // LD_D(0);
    // ADD_A_E;
    // LD_E_A;
    // uint8_t carry = 0;
    // e = AddCarry8(dv, e, 0, &carry);
    // IF_NC goto no_overflow_1;
    // INC_D;
    // d = (carry)? 1: 0;

// no_overflow_1:
    // SLA_E;
    // carry = (e >> 7);
    // e <<= 1;
    // RL_D;
    // d = RotateLeft8(d, carry, &carry);
    // SRL_B;
    // SRL_B;
    // LD_A_B;
    // ADD_A_E;
    // dv = AddCarry8(b >> 2, e, 0, &carry);
    // IF_NC goto no_overflow_2;
    // INC_D;
    // d += (carry)? 1: 0;

// no_overflow_2:
    // LDH_addr_A(hMultiplicand + 2);
    // LD_A_D;
    // LDH_addr_A(hMultiplicand + 1);
    // XOR_A_A;
    // LDH_addr_A(hMultiplicand + 0);
    // uint32_t mul = (dv | (d << 8));
    uint32_t mul = (((uint32_t)dv + e) + (b / 4)) * 2;
    // LD_A_addr(wCurPartyLevel);
    // LDH_addr_A(hMultiplier);
    // CALL(aMultiply);
    uint32_t prod = mul * wram->wCurPartyLevel;
    // LDH_A_addr(hProduct + 1);
    // LDH_addr_A(hDividend + 0);
    // LDH_A_addr(hProduct + 2);
    // LDH_addr_A(hDividend + 1);
    // LDH_A_addr(hProduct + 3);
    // LDH_addr_A(hDividend + 2);
    // LD_A(100);
    // LDH_addr_A(hDivisor);
    // LD_A(3);
    // LD_B_A;
    // CALL(aDivide);
    uint16_t quot = (uint16_t)(prod / 100);
    // LD_A_C;
    // CP_A(STAT_HP);
    // LD_A(STAT_MIN_NORMAL);
    uint16_t stat = STAT_MIN_NORMAL;
    // IF_NZ goto not_hp;
    if(c == STAT_HP) {
        // LD_A_addr(wCurPartyLevel);
        // LD_B_A;
        // LDH_A_addr(hQuotient + 3);
        // ADD_A_B;
        // LDH_addr_A(hMultiplicand + 2);
        // IF_NC goto no_overflow_3;
        // LDH_A_addr(hQuotient + 2);
        // INC_A;
        // LDH_addr_A(hMultiplicand + 1);
        quot += wram->wCurPartyLevel;


    // no_overflow_3:
        // LD_A(STAT_MIN_HP);
        stat = STAT_MIN_HP;
    }

// not_hp:
    // LD_B_A;
    // LDH_A_addr(hQuotient + 3);
    // ADD_A_B;
    // LDH_addr_A(hMultiplicand + 2);
    // IF_NC goto no_overflow_4;
    // LDH_A_addr(hQuotient + 2);
    // INC_A;
    // LDH_addr_A(hMultiplicand + 1);
    quot += stat;


// no_overflow_4:
    // LDH_A_addr(hQuotient + 2);
    // CP_A(HIGH(MAX_STAT_VALUE + 1) + 1);
    // IF_NC goto max_stat;
    if(quot < MAX_STAT_VALUE + 1) {
        // CP_A(HIGH(MAX_STAT_VALUE + 1));
        // IF_C goto stat_value_okay;
        // LDH_A_addr(hQuotient + 3);
        // CP_A(LOW(MAX_STAT_VALUE + 1));
        // IF_C goto stat_value_okay;
        // if(HIGH(quot) < HIGH(MAX_STAT_VALUE + 1) || LOW(quot) < LOW(MAX_STAT_VALUE + 1)) {
        //     return quot;
        // }
        return quot;
    }

// max_stat:
    // LD_A(HIGH(MAX_STAT_VALUE));
    // LDH_addr_A(hMultiplicand + 1);
    // LD_A(LOW(MAX_STAT_VALUE));
    // LDH_addr_A(hMultiplicand + 2);
    return MAX_STAT_VALUE;

// stat_value_okay:
    // POP_BC;
    // POP_DE;
    // POP_HL;
    // RET;
}

uint8_t GivePoke(uint8_t b, const char* nickname, const char* otName){
    // PUSH_DE;
    // PUSH_BC;
    // XOR_A_A;  // PARTYMON
    // LD_addr_A(wMonType);
    wram->wMonType = PARTYMON;
    // CALL(aTryAddMonToParty);
    bool cy = TryAddMonToParty(wram->wCurPartySpecies, wram->wCurPartyLevel);
    // IF_NC goto failed;
    uint8_t* de;
    uint8_t a;
    if(!cy) {
    // failed:
        // LD_A_addr(wCurPartySpecies);
        // LD_addr_A(wTempEnemyMonSpecies);
        wram->wTempEnemyMonSpecies = wram->wCurPartySpecies;
        // CALLFAR(aLoadEnemyMon);
        LoadEnemyMon();
        // CALL(aSendMonIntoBox);
        // JP_NC (mGivePoke_FailedToGiveMon);
        if(!SendMonIntoBox())
            return 0x2;
        // LD_A(BOXMON);
        // LD_addr_A(wMonType);
        wram->wMonType = BOXMON;
        // XOR_A_A;
        // LD_addr_A(wCurPartyMon);
        wram->wCurPartyMon = 0;
        // LD_DE(wMonOrItemNameBuffer);
        de = wram->wMonOrItemNameBuffer;
        // POP_BC;
        // LD_A_B;
        a = b;
        // LD_B(1);
        b = 1;
        // PUSH_BC;
        // PUSH_DE;
        // PUSH_AF;
        // LD_A_addr(wCurItem);
        // AND_A_A;
        // IF_Z goto done;
        if(wram->wCurItem != NO_ITEM) {
            // LD_A_addr(wCurItem);
            // LD_addr_A(sBoxMon1Item);
            gb_write(sBoxMon1Item, wram->wCurItem);
        }
    }
    else {
        // LD_HL(wPartyMonNicknames);
        // LD_A_addr(wPartyCount);
        // DEC_A;
        // LD_addr_A(wCurPartyMon);
        // CALL(aSkipNames);
        // LD_D_H;
        // LD_E_L;
        de = gPokemon.partyMonNickname[gPokemon.partyCount - 1];
        // POP_BC;
        // LD_A_B;
        a = b;
        // LD_B(0);
        b = 0;
        // PUSH_BC;
        // PUSH_DE;
        // PUSH_AF;
        // LD_A_addr(wCurItem);
        // AND_A_A;
        // IF_Z goto done;
        if(wram->wCurItem != NO_ITEM) {
            // LD_A_addr(wCurPartyMon);
            // LD_HL(wPartyMon1Item);
            // LD_BC(PARTYMON_STRUCT_LENGTH);
            // CALL(aAddNTimes);
            // LD_A_addr(wCurItem);
            // LD_hl_A;
            gPokemon.partyMon[wram->wCurPartyMon].mon.item = wram->wCurItem;
            // goto done;
        }
    }

// done:
    // LD_A_addr(wCurPartySpecies);
    // LD_addr_A(wNamedObjectIndex);
    // LD_addr_A(wTempEnemyMonSpecies);
    // CALL(aGetPokemonName);
    // LD_HL(wStringBuffer1);
    // LD_DE(wMonOrItemNameBuffer);
    // LD_BC(MON_NAME_LENGTH);
    // CALL(aCopyBytes);
    CopyBytes(wram->wMonOrItemNameBuffer, GetPokemonName(wram->wCurPartySpecies), MON_NAME_LENGTH);
    // POP_AF;
    // AND_A_A;
    // JP_Z (mGivePoke_wildmon);
    if(a == 0) {
    // wildmon:
        // POP_DE;
        // POP_BC;
        // PUSH_BC;
        // PUSH_DE;
        // LD_A_B;
        // AND_A_A;
        // IF_Z goto party;
        if(b == 0) {
        // party:
            // FARCALL(aSetCaughtData);
            SetCaughtData(wram->wCurPartyLevel);
        }
        else {
            // FARCALL(aSetBoxMonCaughtData);
            SetBoxMonCaughtData(wram->wCurPartyLevel);
            // goto set_caught_data;
        }

    // set_caught_data:
        // FARCALL(aGiveANickname_YesNo);
        // POP_DE;
        // IF_C goto skip_nickname;
        if(GiveANickname_YesNo()) {
            // CALL(aInitNickname);
            InitNickname(de);
        }
    }
    else {
        // POP_DE;
        // POP_BC;
        // POP_HL;
        // PUSH_BC;
        // PUSH_HL;
        // LD_A_addr(wScriptBank);
        // CALL(aGetFarWord);
        // LD_BC(MON_NAME_LENGTH);
        // LD_A_addr(wScriptBank);
        // CALL(aFarCopyBytes);
        CopyBytes(de, U82C(nickname), MON_NAME_LENGTH);
        // POP_HL;
        // INC_HL;
        // INC_HL;
        // LD_A_addr(wScriptBank);
        // CALL(aGetFarWord);
        // POP_BC;
        // LD_A_B;
        // AND_A_A;
        // PUSH_DE;
        // PUSH_BC;
        // IF_NZ goto send_to_box;
        uint8_t* hl2 = U82C(otName);
        if(b != 0) {
        // send_to_box:
            // LD_A(BANK(sBoxMonOTs));
            // CALL(aOpenSRAM);
            OpenSRAM(MBANK(asBoxMonOTs));
            // LD_DE(sBoxMonOTs);
            uint16_t de2 = sBoxMonOTs;

            uint8_t n;
            do {
            // loop:
                // LD_A_addr(wScriptBank);
                // CALL(aGetFarByte);
                n = *(hl2++);
                // LD_de_A;
                gb_write(de2++, n);
                // INC_HL;
                // INC_DE;
                // CP_A(0x50);
                // IF_NZ goto loop;
            } while(n != 0x50);
            // LD_A_addr(wScriptBank);
            // CALL(aGetFarByte);
            // LD_B_A;
            b = *hl2;
            // LD_HL(sBoxMon1ID);
            // CALL(aRandom);
            // LD_hli_A;
            gb_write(sBoxMon1ID, Random());
            // CALL(aRandom);
            // LD_hl_A;
            gb_write(sBoxMon1ID + 1, Random());
            // CALL(aCloseSRAM);
            CloseSRAM();
            // FARCALL(aSetGiftBoxMonCaughtData);
            SetGiftBoxMonCaughtData(b);
            // goto skip_nickname;
        }
        else {
            // PUSH_HL;
            // LD_A_addr(wCurPartyMon);
            // LD_HL(wPartyMonOTs);
            // CALL(aSkipNames);
            // LD_D_H;
            // LD_E_L;
            uint8_t* de2 = gPokemon.partyMonOT[wram->wCurPartyMon];
            // POP_HL;

            uint8_t n;
            do {
            // otnameloop:
                // LD_A_addr(wScriptBank);
                // CALL(aGetFarByte);
                n = *(hl2++);
                // LD_de_A;
                *(de2++) = n;
                // INC_HL;
                // INC_DE;
                // CP_A(0x50);
                // IF_NZ goto otnameloop;
            } while(n != 0x50);
            // LD_A_addr(wScriptBank);
            // CALL(aGetFarByte);
            // LD_B_A;
            b = *hl2;
            // PUSH_BC;
            // LD_A_addr(wCurPartyMon);
            // LD_HL(wPartyMon1ID);
            // LD_BC(PARTYMON_STRUCT_LENGTH);
            // CALL(aAddNTimes);
            // LD_A(HIGH(RANDY_OT_ID));
            // LD_hli_A;
            // LD_hl(LOW(RANDY_OT_ID));
            gPokemon.partyMon[wram->wCurPartyMon].mon.id = NativeToBigEndian16(RANDY_OT_ID);
            // POP_BC;
            // FARCALL(aSetGiftPartyMonCaughtData);
            SetGiftBoxMonCaughtData(b);
            // goto skip_nickname;
        }
    }

// skip_nickname:
    // POP_BC;
    // POP_DE;
    // LD_A_B;
    // AND_A_A;
    // RET_Z ;
    if(b == 0)
        return 0;
    // LD_HL(mWasSentToBillsPCText);
    // CALL(aPrintText);
    PrintText(WasSentToBillsPCText);
    // LD_A(BANK(sBoxMonNicknames));
    // CALL(aOpenSRAM);
    OpenSRAM(MBANK(asBoxMonNicknames));
    // LD_HL(wMonOrItemNameBuffer);
    // LD_DE(sBoxMonNicknames);
    // LD_BC(MON_NAME_LENGTH);
    // CALL(aCopyBytes);
    CopyBytes_GB(sBoxMonNicknames, wMonOrItemNameBuffer, MON_NAME_LENGTH);
    // CALL(aCloseSRAM);
    CloseSRAM();
    // LD_B(0x1);
    // RET;
    return 0x1;


// FailedToGiveMon:
    // POP_BC;
    // POP_DE;
    // LD_B(0x2);
    // RET;
    // return 0x2;
}

const txt_cmd_s WasSentToBillsPCText[] = {
    text_far(v_WasSentToBillsPCText)
    text_end
};

void InitNickname(uint8_t* hl){
    // PUSH_DE;
    // CALL(aLoadStandardMenuHeader);
    LoadStandardMenuHeader();
    // CALL(aDisableSpriteUpdates);
    DisableSpriteUpdates();
    // POP_DE;
    // PUSH_DE;
    // LD_B(NAME_MON);
    // FARCALL(aNamingScreen);
    NamingScreen(hl, NAME_MON);
    // POP_HL;
    // LD_DE(wStringBuffer1);
    // CALL(aInitName);
    InitName(hl, wram->wStringBuffer1);
    // LD_A(0x4);  // ExitAllMenus is in bank 0// maybe it used to be in bank 4
    // LD_HL(mExitAllMenus);
    ExitAllMenus();
    // RST(aFarCall);
    // RET;

}
