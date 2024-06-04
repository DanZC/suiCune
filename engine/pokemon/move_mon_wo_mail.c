#include "../../constants.h"
#include "../../home/sram.h"
#include "../../home/copy.h"
#include "move_mon_wo_mail.h"
#include "move_mon.h"

void InsertPokemonIntoBox(void){
    // LD_A(BANK(sBoxCount));
    // CALL(aOpenSRAM);
    OpenSRAM_Conv(MBANK(sBoxCount));
    // LD_HL(sBoxCount);
    // CALL(aInsertSpeciesIntoBoxOrParty);
    InsertSpeciesIntoBoxOrParty_Conv(GBToRAMAddr(sBoxCount), GBToRAMAddr(sBoxSpecies));
    // LD_A_addr(sBoxCount);
    // DEC_A;
    // LD_addr_A(wNextBoxOrPartyIndex);
    wram->wNextBoxOrPartyIndex = gb_read(sBoxCount) - 1;
    // LD_HL(sBoxMonNicknames);
    // LD_BC(MON_NAME_LENGTH);
    // LD_DE(wBufferMonNickname);
    // CALL(aInsertDataIntoBoxOrParty);
    InsertDataIntoBoxOrParty_Conv(GBToRAMAddr(sBoxMonNicknames), wram->wBufferMonNickname, MON_NAME_LENGTH);
    // LD_A_addr(sBoxCount);
    // DEC_A;
    // LD_addr_A(wNextBoxOrPartyIndex);
    wram->wNextBoxOrPartyIndex = gb_read(sBoxCount) - 1;
    // LD_HL(sBoxMonOTs);
    // LD_BC(NAME_LENGTH);
    // LD_DE(wBufferMonOT);
    // CALL(aInsertDataIntoBoxOrParty);
    InsertDataIntoBoxOrParty_Conv(GBToRAMAddr(sBoxMonOTs), wram->wBufferMonOT, MON_NAME_LENGTH);
    // LD_A_addr(sBoxCount);
    // DEC_A;
    // LD_addr_A(wNextBoxOrPartyIndex);
    wram->wNextBoxOrPartyIndex = gb_read(sBoxCount) - 1;
    // LD_HL(sBoxMons);
    // LD_BC(BOXMON_STRUCT_LENGTH);
    // LD_DE(wBufferMon);
    // CALL(aInsertDataIntoBoxOrParty);
    InsertDataIntoBoxOrParty_Conv(GBToRAMAddr(sBoxMons), (uint8_t*)&wram->wBufferMon.mon, BOXMON_STRUCT_LENGTH);
    // LD_HL(wBufferMonMoves);
    // LD_DE(wTempMonMoves);
    // LD_BC(NUM_MOVES);
    // CALL(aCopyBytes);
    CopyBytes_Conv2(wram->wTempMon.mon.moves, wram->wBufferMon.mon.moves, sizeof(wram->wTempMon.mon.moves));
    // LD_HL(wBufferMonPP);
    // LD_DE(wTempMonPP);
    // LD_BC(NUM_MOVES);
    // CALL(aCopyBytes);
    CopyBytes_Conv2(wram->wTempMon.mon.PP, wram->wBufferMon.mon.PP, sizeof(wram->wTempMon.mon.PP));
    // LD_A_addr(wCurPartyMon);
    // LD_B_A;
    // FARCALL(aRestorePPOfDepositedPokemon);
    RestorePPOfDepositedPokemon(wram->wCurPartyMon);
    // JP(mCloseSRAM);
    return CloseSRAM_Conv();
}

void InsertPokemonIntoParty(void){
    // LD_HL(wPartyCount);
    // CALL(aInsertSpeciesIntoBoxOrParty);
    InsertSpeciesIntoBoxOrParty_Conv(&wram->wPartyCount, wram->wPartySpecies);
    // LD_A_addr(wPartyCount);
    // DEC_A;
    // LD_addr_A(wNextBoxOrPartyIndex);
    wram->wNextBoxOrPartyIndex = wram->wPartyCount - 1;
    // LD_HL(wPartyMonNicknames);
    // LD_BC(MON_NAME_LENGTH);
    // LD_DE(wBufferMonNickname);
    // CALL(aInsertDataIntoBoxOrParty);
    InsertDataIntoBoxOrParty_Conv(wram->wPartyMonNickname[0], wram->wBufferMonNickname, MON_NAME_LENGTH);
    // LD_A_addr(wPartyCount);
    // DEC_A;
    // LD_addr_A(wNextBoxOrPartyIndex);
    wram->wNextBoxOrPartyIndex = wram->wPartyCount - 1;
    // LD_HL(wPartyMonOTs);
    // LD_BC(NAME_LENGTH);
    // LD_DE(wBufferMonOT);
    // CALL(aInsertDataIntoBoxOrParty);
    InsertDataIntoBoxOrParty_Conv(wram->wPartyMonOT[0], wram->wBufferMonOT, NAME_LENGTH);
    // LD_A_addr(wPartyCount);
    // DEC_A;
    // LD_addr_A(wNextBoxOrPartyIndex);
    // LD_HL(wPartyMons);
    // LD_BC(PARTYMON_STRUCT_LENGTH);
    // LD_DE(wBufferMon);
    // CALL(aInsertDataIntoBoxOrParty);
    InsertDataIntoBoxOrParty_Conv((uint8_t*)wram->wPartyMon, (uint8_t*)&wram->wBufferMon, PARTYMON_STRUCT_LENGTH);
    // RET;
}

void InsertSpeciesIntoBoxOrParty(void){
    INC_hl;
    INC_HL;
    LD_A_addr(wCurPartyMon);
    LD_C_A;
    LD_B(0);
    ADD_HL_BC;
    LD_A_addr(wCurPartySpecies);
    LD_C_A;

loop:
    LD_A_hl;
    LD_hl_C;
    INC_HL;
    INC_C;
    LD_C_A;
    IF_NZ goto loop;
    RET;

}

void InsertSpeciesIntoBoxOrParty_Conv(uint8_t* count, species_t* party){
    // INC_hl;
    (*count)++;
    // INC_HL;
    // LD_A_addr(wCurPartyMon);
    // LD_C_A;
    // LD_B(0);
    party += wram->wCurPartyMon;
    // ADD_HL_BC;
    // LD_A_addr(wCurPartySpecies);
    // LD_C_A;
    species_t c = wram->wCurPartySpecies;

    do {
    // loop:
        // LD_A_hl;
        species_t a = *party;
        // LD_hl_C;
        *party = c;
        // INC_HL;
        party++;
        // INC_C;
        // LD_C_A;
        c = a;
        // IF_NZ goto loop;
    } while(c != (species_t)-1);
    // RET;

}

void InsertDataIntoBoxOrParty(void){
    PUSH_DE;
    PUSH_HL;
    PUSH_BC;
    LD_A_addr(wNextBoxOrPartyIndex);
    DEC_A;
    CALL(aAddNTimes);
    PUSH_HL;
    ADD_HL_BC;
    LD_D_H;
    LD_E_L;
    POP_HL;

loop:
    PUSH_BC;
    LD_A_addr(wNextBoxOrPartyIndex);
    LD_B_A;
    LD_A_addr(wCurPartyMon);
    CP_A_B;
    POP_BC;
    IF_Z goto insert;
    PUSH_HL;
    PUSH_DE;
    PUSH_BC;
    CALL(aCopyBytes);
    POP_BC;
    POP_DE;
    POP_HL;
    PUSH_HL;
    LD_A_L;
    SUB_A_C;
    LD_L_A;
    LD_A_H;
    SBC_A_B;
    LD_H_A;
    POP_DE;
    LD_A_addr(wNextBoxOrPartyIndex);
    DEC_A;
    LD_addr_A(wNextBoxOrPartyIndex);
    goto loop;


insert:
    POP_BC;
    POP_HL;
    LD_A_addr(wCurPartyMon);
    CALL(aAddNTimes);
    LD_D_H;
    LD_E_L;
    POP_HL;
    CALL(aCopyBytes);
    RET;

}

void InsertDataIntoBoxOrParty_Conv(uint8_t* hl, const uint8_t* de, uint16_t bc){
    // PUSH_DE;
    // PUSH_HL;
    // PUSH_BC;
    // LD_A_addr(wNextBoxOrPartyIndex);
    // DEC_A;
    // CALL(aAddNTimes);
    // PUSH_HL;
    // ADD_HL_BC;
    // LD_D_H;
    // LD_E_L;
    uint8_t* de2 = hl + (bc * wram->wNextBoxOrPartyIndex);
    // POP_HL;
    hl = de2 - bc;

    while(1) {
    // loop:
        // PUSH_BC;
        // LD_A_addr(wNextBoxOrPartyIndex);
        // LD_B_A;
        // LD_A_addr(wCurPartyMon);
        // CP_A_B;
        // POP_BC;
        // IF_Z goto insert;
        if(wram->wCurPartyMon == wram->wNextBoxOrPartyIndex) {
        // insert:
            // POP_BC;
            // POP_HL;
            // LD_A_addr(wCurPartyMon);
            // CALL(aAddNTimes);
            // LD_D_H;
            // LD_E_L;
            // POP_HL;
            // CALL(aCopyBytes);
            // RET;
            return CopyBytes_Conv2(hl + bc * wram->wCurPartyMon, de, bc);
        }
        // PUSH_HL;
        // PUSH_DE;
        // PUSH_BC;
        // CALL(aCopyBytes);
        CopyBytes_Conv2(de2, hl, bc);
        // POP_BC;
        // POP_DE;
        // POP_HL;
        // PUSH_HL;
        // LD_A_L;
        // SUB_A_C;
        // LD_L_A;
        // LD_A_H;
        // SBC_A_B;
        // LD_H_A;
        // POP_DE;
        de2 = hl;
        hl = hl - bc;
        // LD_A_addr(wNextBoxOrPartyIndex);
        // DEC_A;
        // LD_addr_A(wNextBoxOrPartyIndex);
        wram->wNextBoxOrPartyIndex -= 1;
        // goto loop;
    }
}
