#include "../../../constants.h"
#include "rules.h"
#include "../../../data/text/common.h"
#include "../../../home/text.h"

struct BattleTowerCheckText {
    bool (*func)(void);
    const txt_cmd_s* text;
};

struct BattleTowerJumptable {
    uint8_t count;
    const txt_cmd_s* error_text;
    const struct BattleTowerCheckText* table;
};

static bool BattleTower_ExecuteJumptable(const struct BattleTowerJumptable* table);

static const txt_cmd_s BTExcuseMeText[] = {
    text_far(v_BTExcuseMeText)
    text_end
};
static const struct BattleTowerJumptable CheckForMobileBattleRules_PointerTables = {
    .count = 2,
    .error_text = BTExcuseMeText,
    //dw ['.Functions'];
    // Functions:
    .table = (const struct BattleTowerCheckText[]) {
        {BattleTower_CheckPartyLengthIs3, NeedAtLeastThreeMonText},
        {BattleTower_CheckPartyHasThreeMonsThatAreNotEggs, EggDoesNotQualifyText},
    },
    //dw ['.TextPointers'];
    // TextPointers:
};

bool CheckForMobileBattleRules(void){
    // LD_DE(mCheckForMobileBattleRules_PointerTables);
    // CALL(aBattleTower_ExecuteJumptable);
    // RET_Z ;
    if(!BattleTower_ExecuteJumptable(&CheckForMobileBattleRules_PointerTables))
        return false;
    // CALL(aBattleTower_PleaseReturnWhenReady);
    BattleTower_PleaseReturnWhenReady();
    // SCF;
    // RET;
    return true;
}

static const struct BattleTowerJumptable v_CheckForBattleTowerRules_PointerTables = {
    .count = 4,
    .error_text = ExcuseMeYoureNotReadyText,
    //dw ['.Functions'];
    // Functions:
    .table = (const struct BattleTowerCheckText[]) {
        {CheckBTRule_PartyCountEq3, OnlyThreeMonMayBeEnteredText},
        {CheckBTRule_PartySpeciesAreUnique, TheMonMustAllBeDifferentKindsText},
        {CheckBTRule_PartyItemsAreUnique, TheMonMustNotHoldTheSameItemsText},
        {CheckBTRule_HasPartyAnEgg, YouCantTakeAnEggText},
    },
    //dw ['.TextPointers'];
    // TextPointers:
};

bool v_CheckForBattleTowerRules(void){

    // LD_HL(wStringBuffer2);
    // LD_hl(0xf9);
    wram->wStringBuffer2[0] = 0xf9;
    // INC_HL;
    // LD_hl(0x50);
    wram->wStringBuffer2[1] = 0x50;
    // LD_DE(mv_CheckForBattleTowerRules_PointerTables);
    // CALL(aBattleTower_ExecuteJumptable);
    // RET_Z ;
    if(!BattleTower_ExecuteJumptable(&v_CheckForBattleTowerRules_PointerTables))
        return false;
    // CALL(aBattleTower_PleaseReturnWhenReady);
    BattleTower_PleaseReturnWhenReady();
    // SCF;
    // RET;
    return true;

// PointerTables:
    //db ['4'];
    //dw ['.Functions'];
    //dw ['.TextPointers'];

// Functions:
    //dw ['CheckBTRule_PartyCountEq3'];
    //dw ['CheckBTRule_PartySpeciesAreUnique'];
    //dw ['CheckBTRule_PartyItemsAreUnique'];
    //dw ['CheckBTRule_HasPartyAnEgg'];

// TextPointers:
    //dw ['ExcuseMeYoureNotReadyText'];
    //dw ['OnlyThreeMonMayBeEnteredText'];
    //dw ['TheMonMustAllBeDifferentKindsText'];
    //dw ['TheMonMustNotHoldTheSameItemsText'];
    //dw ['YouCantTakeAnEggText'];
}

const txt_cmd_s ExcuseMeYoureNotReadyText[] = {
    text_far(v_ExcuseMeYoureNotReadyText)
    text_end
};

void BattleTower_PleaseReturnWhenReady(void){
    static const txt_cmd_s BattleTowerReturnWhenReadyText[] = {
        text_far(v_BattleTowerReturnWhenReadyText)
        text_end
    };
    // LD_HL(mBattleTower_PleaseReturnWhenReady_BattleTowerReturnWhenReadyText);
    // CALL(aPrintText);
    PrintText(BattleTowerReturnWhenReadyText);
    // RET;
}

const txt_cmd_s NeedAtLeastThreeMonText[] = {
    text_far(v_NeedAtLeastThreeMonText)
    text_end
};

const txt_cmd_s EggDoesNotQualifyText[] = {
    text_far(v_EggDoesNotQualifyText)
    text_end
};

const txt_cmd_s OnlyThreeMonMayBeEnteredText[] = {
    text_far(v_OnlyThreeMonMayBeEnteredText)
    text_end
};

const txt_cmd_s TheMonMustAllBeDifferentKindsText[] = {
    text_far(v_TheMonMustAllBeDifferentKindsText)
    text_end
};

const txt_cmd_s TheMonMustNotHoldTheSameItemsText[] = {
    text_far(v_TheMonMustNotHoldTheSameItemsText)
    text_end
};

const txt_cmd_s YouCantTakeAnEggText[] = {
    text_far(v_YouCantTakeAnEggText)
    text_end
};

static bool(*BattleTower_ExecuteJumptable_GetFunctionPointer(const struct BattleTowerJumptable* table, uint8_t c))(void) {
    // INC_DE;
    // LD_A_de;
    // LD_L_A;
    // INC_DE;
    // LD_A_de;
    // LD_H_A;
    return table->table[c].func;
    // RET;
}

static bool BattleTower_ExecuteJumptable_DoJumptableFunction(const struct BattleTowerJumptable* table, uint8_t c) {
    // PUSH_DE;
    // PUSH_BC;
    // CALL(aBattleTower_ExecuteJumptable_GetFunctionPointer);
    bool (*func)(void) = BattleTower_ExecuteJumptable_GetFunctionPointer(table, c);
    // LD_A_C;
    // RST(aJumpTable);
    return func();
    // POP_BC;
    // POP_DE;
    // RET;
}

static void BattleTower_ExecuteJumptable_PrintFailureText(const struct BattleTowerJumptable* table, uint8_t* b, uint8_t c) {
    // PUSH_DE;
    // PUSH_BC;
    // LD_A_B;
    // AND_A_A;
    // CALL_Z (aBattleTower_ExecuteJumptable_PrintFirstText);
    if(*b == 0) {
        PrintText(table->error_text);
    }
    // POP_BC;
    // CALL(aBattleTower_ExecuteJumptable_PrintNthText);
    PrintText(table->table[c].text);
    // LD_B(1);
    *b = 1;
    // POP_DE;
    // RET;
}

static bool BattleTower_ExecuteJumptable_Next_CheckReachedEnd(const struct BattleTowerJumptable* table, uint8_t* c) {
    // INC_C;
    ++*c;
    // LD_A_de;
    // CP_A_C;
    // RET;
    return *c == table->count;
}

static bool BattleTower_ExecuteJumptable(const struct BattleTowerJumptable* table){
    // LD_BC(0);
    uint8_t b = 0;
    uint8_t c = 0;

    bool done;
    do {
    // loop:
        // CALL(aBattleTower_ExecuteJumptable_DoJumptableFunction);
        bool fail = BattleTower_ExecuteJumptable_DoJumptableFunction(table, c);
        // CALL_C (aBattleTower_ExecuteJumptable_PrintFailureText);
        if(fail) {
            BattleTower_ExecuteJumptable_PrintFailureText(table, &b, c);
        }
        // CALL(aBattleTower_ExecuteJumptable_Next_CheckReachedEnd);
        done = BattleTower_ExecuteJumptable_Next_CheckReachedEnd(table, &c);
        // IF_NZ goto loop;
    } while(!done);
    // LD_A_B;
    // AND_A_A;
    // RET;
    return b != 0;

// GetTextPointers:
    // INC_DE;
    // INC_DE;
    // INC_DE;
    // LD_A_de;
    // LD_L_A;
    // INC_DE;
    // LD_A_de;
    // LD_H_A;
    // RET;

// LoadTextPointer:
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // RET;

// PrintFirstText:
    // PUSH_DE;
    // CALL(aBattleTower_ExecuteJumptable_GetTextPointers);
    // CALL(aBattleTower_ExecuteJumptable_LoadTextPointer);
    // CALL(aPrintText);
    // POP_DE;
    // RET;

// PrintNthText:
    // PUSH_BC;
    // CALL(aBattleTower_ExecuteJumptable_GetTextPointers);
    // INC_HL;
    // INC_HL;
    // LD_B(0);
    // ADD_HL_BC;
    // ADD_HL_BC;
    // CALL(aBattleTower_ExecuteJumptable_LoadTextPointer);
    // CALL(aPrintText);
    // POP_BC;
    // RET;
}

bool BattleTower_CheckPartyLengthIs3(void){
    // LD_A_addr(wPartyCount);
    // CP_A(BATTLETOWER_PARTY_LENGTH);
    // RET;
    return gPokemon.partyCount < BATTLETOWER_PARTY_LENGTH;
}

bool BattleTower_CheckPartyHasThreeMonsThatAreNotEggs(void){
    // LD_HL(wPartyCount);
    // LD_A_hli;
    // LD_B(0);
    uint8_t b = 0;
    // LD_C_A;
    uint8_t c = gPokemon.partyCount;
    const species_t* hl = gPokemon.partySpecies;

    do {
    // loop:
        // LD_A_hli;
        // CP_A(EGG);
        // IF_Z goto egg;
        if(*(hl++) != EGG) {
            // INC_B;
            b++;
        }

    // egg:
        // DEC_C;
        // IF_NZ goto loop;
    } while(--c != 0);
    // LD_A_addr(wPartyCount);
    // CP_A_B;
    // RET_Z ;
    if(gPokemon.partyCount == b)
        return false;
    // LD_A_B;
    // CP_A(BATTLETOWER_PARTY_LENGTH);
    // RET;
    return b < BATTLETOWER_PARTY_LENGTH;
}

bool CheckBTRule_PartyCountEq3(void){
    // LD_A_addr(wPartyCount);
    // CP_A(BATTLETOWER_PARTY_LENGTH);
    // RET_Z ;
    // SCF;
    // RET;
    return gPokemon.partyCount != BATTLETOWER_PARTY_LENGTH;
}

bool CheckBTRule_PartySpeciesAreUnique(void){
    // LD_HL(wPartyMon1Species);
    // CALL(aCheckPartyValueIsUnique);
    // RET;
    return CheckPartyValueIsUnique(gPokemon.partyMon, gPokemon.partySpecies, gPokemon.partyCount);
}

static bool CheckPartyValueIsUnique_isegg(const species_t a) {
    // PUSH_BC;
    // LD_B_A;
    // LD_A_de;
    // CP_A(EGG);
    // LD_A_B;
    // POP_BC;
    // RET;
    return a == EGG;
}

bool CheckPartyValueIsUnique(const struct PartyMon* hl, const species_t* de, uint8_t count){
    // LD_DE(wPartyCount);
    // LD_A_de;
    // INC_DE;
    // DEC_A;
    // IF_Z goto done;
    if(count > 1) {
        // LD_B_A;
        uint8_t b = --count;

        do {
        // loop:
            // PUSH_HL;
            // PUSH_DE;
            // LD_C_B;
            uint8_t c = b;
            // CALL(aCheckPartyValueIsUnique_isegg);
            // IF_Z goto next;
            if(CheckPartyValueIsUnique_isegg(*de))
                continue;
            // LD_A_hl;
            // AND_A_A;
            // IF_Z goto next;
            if(hl->mon.species == 0)
                continue;

            species_t match = hl->mon.species;
            const species_t* de2 = de;
            const struct PartyMon* hl2 = hl;

            do {
            // loop2:
                // CALL(aCheckPartyValueIsUnique_nextmon);
                hl2++, de2++;
                // CALL(aCheckPartyValueIsUnique_isegg);
                // IF_Z goto next2;
                if(CheckPartyValueIsUnique_isegg(*de2))
                    continue;
                // CP_A_hl;
                // IF_Z goto gotcha;
                if(hl2->mon.species == match) {
                // gotcha:
                    // POP_DE;
                    // POP_HL;
                    // SCF;
                    // RET;
                    return true;
                }


            // next2:
                // DEC_C;
                // IF_NZ goto loop2;
            } while(--c != 0);


        // next:
            // POP_DE;
            // POP_HL;
            // CALL(aCheckPartyValueIsUnique_nextmon);
            // DEC_B;
            // IF_NZ goto loop;
        } while(hl++, de++, --b != 0);
    }

// done:
    // AND_A_A;
    // RET;
    return false;


// nextmon:
    // PUSH_BC;
    // LD_BC(PARTYMON_STRUCT_LENGTH);
    // ADD_HL_BC;
    // INC_DE;
    // POP_BC;
    // RET;
}

bool CheckBTRule_PartyItemsAreUnique(void){
    // LD_HL(wPartyMon1Item);
    // CALL(aCheckPartyValueIsUnique);
    // RET;
    return CheckPartyItemIsUnique(gPokemon.partyMon, gPokemon.partySpecies, gPokemon.partyCount);
}

bool CheckPartyItemIsUnique(const struct PartyMon* hl, const species_t* de, uint8_t count){
    // LD_DE(wPartyCount);
    // LD_A_de;
    // INC_DE;
    // DEC_A;
    // IF_Z goto done;
    if(count > 1) {
        // LD_B_A;
        uint8_t b = --count;

        do {
        // loop:
            // PUSH_HL;
            // PUSH_DE;
            // LD_C_B;
            uint8_t c = b;
            // CALL(aCheckPartyValueIsUnique_isegg);
            // IF_Z goto next;
            if(CheckPartyValueIsUnique_isegg(*de))
                continue;
            // LD_A_hl;
            // AND_A_A;
            // IF_Z goto next;
            if(hl->mon.item == NO_ITEM)
                continue;

            item_t match = hl->mon.item;
            const species_t* de2 = de;
            const struct PartyMon* hl2 = hl;

            do {
            // loop2:
                // CALL(aCheckPartyValueIsUnique_nextmon);
                hl2++, de2++;
                // CALL(aCheckPartyValueIsUnique_isegg);
                // IF_Z goto next2;
                if(CheckPartyValueIsUnique_isegg(*de2))
                    continue;
                // CP_A_hl;
                // IF_Z goto gotcha;
                if(hl2->mon.item == match) {
                // gotcha:
                    // POP_DE;
                    // POP_HL;
                    // SCF;
                    // RET;
                    return true;
                }


            // next2:
                // DEC_C;
                // IF_NZ goto loop2;
            } while(--c != 0);


        // next:
            // POP_DE;
            // POP_HL;
            // CALL(aCheckPartyValueIsUnique_nextmon);
            // DEC_B;
            // IF_NZ goto loop;
        } while(hl++, de++, --b != 0);
    }

// done:
    // AND_A_A;
    // RET;
    return false;


// nextmon:
    // PUSH_BC;
    // LD_BC(PARTYMON_STRUCT_LENGTH);
    // ADD_HL_BC;
    // INC_DE;
    // POP_BC;
    // RET;
}

bool CheckBTRule_HasPartyAnEgg(void){
    // LD_HL(wPartyCount);
    // LD_A_hli;
    // LD_C_A;
    uint8_t c = gPokemon.partyCount;
    const species_t* hl = gPokemon.partySpecies;

    do {
    // loop:
        // LD_A_hli;
        // CP_A(EGG);
        // IF_Z goto found;
        if(*(hl++) == EGG) {
        // found:
            // SCF;
            // RET;
            return true;
        }
        // DEC_C;
        // IF_NZ goto loop;
    } while(--c != 0);
    // AND_A_A;
    // RET;
    return false;
}
