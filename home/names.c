#include "../constants.h"
#include "names.h"
#include "copy.h"
#include "../charmap.h"
#include "../data/pokemon/names.h"
#include "../data/moves/names.h"
#include "../data/items/names.h"
#include "../data/trainers/class_names.h"
#include "../engine/items/items.h"

const char (*const NamesPointers[])[20] = {
    //  entries correspond to GetName constants (see constants/text_constants.asm)
    //dba ['PokemonNames']  // MON_NAME (not used// jumps to GetPokemonName)
    //dba ['MoveNames']  // MOVE_NAME
    //dba ['NULL']  // DUMMY_NAME
    //dba ['ItemNames']  // ITEM_NAME
    //dbw ['0', 'wPartyMonOTs']  // PARTY_OT_NAME
    //dbw ['0', 'wOTPartyMonOTs']  // ENEMY_OT_NAME
    //dba ['TrainerClassNames']  // TRAINER_NAME
    //dbw ['4', 'MoveDescriptions']  // MOVE_DESC_NAME_BROKEN (wrong bank)
    [MON_NAME] = PokemonNames,
    [MOVE_NAME] = MoveNames,
    [DUMMY_NAME] = NULL,
    [ITEM_NAME] = ItemNames,
    [TRAINER_NAME] = TrainerClassNames,
};

//  Return name index from name list type in wStringBuffer1.
uint8_t* GetName(uint8_t type, uint16_t index){
    // LDH_A_addr(hROMBank);
    // PUSH_AF;
    // PUSH_HL;
    // PUSH_BC;
    // PUSH_DE;

    // LD_A_addr(wNamedObjectType);
    // CP_A(MON_NAME);
    // IF_NZ goto NotPokeName;
    if(type == MON_NAME) 
    {
        // LD_A_addr(wCurSpecies);
        // LD_addr_A(wNamedObjectIndex);

        // CALL(aGetPokemonName);
        GetPokemonName(index);
        
        // LD_HL(MON_NAME_LENGTH);
        // ADD_HL_DE;

        // LD_E_L;
        // LD_D_H;
        return wram->wStringBuffer1;
    } 
    else 
    {    
        // LD_A_addr(wNamedObjectType);
        // DEC_A;
        // LD_E_A;
        // LD_D(0);

        // LD_HL(mNamesPointers);

        // ADD_HL_DE;
        // ADD_HL_DE;
        // ADD_HL_DE;

        // LD_A_hli;
        // RST(aBankswitch);

        // LD_A_hli;
        // LD_H_hl;
        // LD_L_A;

        ByteFill(wram->wStringBuffer1, sizeof(wram->wStringBuffer1), CHAR_TERM);
        // LD_A_addr(wCurSpecies);
        // DEC_A;
        // CALL(aGetNthString);
        uint8_t* hl = U82CA(wram->wStringBuffer1, NamesPointers[type][index - 1]);

        // LD_DE(wStringBuffer1);
        // LD_BC(ITEM_NAME_LENGTH);
        // CALL(aCopyBytes);
        return hl;
    }

    // LD_A_E;
    // LD_addr_A(wUnusedNamesPointer);
    // LD_A_D;
    // LD_addr_A(wUnusedNamesPointer + 1);

    // POP_DE;
    // POP_BC;
    // POP_HL;
    // POP_AF;
    // RST(aBankswitch);
}

//  Return name wCurSpecies from name list wNamedObjectType in wStringBuffer1.
void GetName_GB(void){
    // LDH_A_addr(hROMBank);
    // PUSH_AF;
    // PUSH_HL;
    // PUSH_BC;
    // PUSH_DE;
    uint8_t tempBank = hram.hROMBank;
    uint16_t de;

    // LD_A_addr(wNamedObjectType);
    // CP_A(MON_NAME);
    // IF_NZ goto NotPokeName;
    if(wram->wNamedObjectType == MON_NAME) 
    {
        // LD_A_addr(wCurSpecies);
        // LD_addr_A(wNamedObjectIndex);
        wram->wNamedObjectIndex = wram->wCurSpecies;

        // CALL(aGetPokemonName);
        GetPokemonName_GB();
        
        // LD_HL(MON_NAME_LENGTH);
        // ADD_HL_DE;
        uint16_t hl = MON_NAME_LENGTH + wStringBuffer1;

        // LD_E_L;
        // LD_D_H;
        de = hl;
    } 
    else 
    {    
        // LD_A_addr(wNamedObjectType);
        // DEC_A;
        // LD_E_A;
        // LD_D(0);
        de = (wram->wNamedObjectType - 1) & 0xFF;

        // LD_HL(mNamesPointers);
        uint16_t hl = mNamesPointers;

        // ADD_HL_DE;
        // ADD_HL_DE;
        // ADD_HL_DE;
        hl += (3 * de);

        // LD_A_hli;
        // RST(aBankswitch);
        Bankswitch(gb_read(hl++));

        // LD_A_hli;
        // LD_H_hl;
        // LD_L_A;
        hl = gb_read16(hl);

        // LD_A_addr(wCurSpecies);
        // DEC_A;
        // CALL(aGetNthString);
        hl = GetNthString_GB(hl, gb_read(wCurSpecies) - 1);

        // LD_DE(wStringBuffer1);
        // LD_BC(ITEM_NAME_LENGTH);
        // CALL(aCopyBytes);
        CopyBytes_GB(wStringBuffer1, hl, ITEM_NAME_LENGTH);
    }

    // LD_A_E;
    // LD_addr_A(wUnusedNamesPointer);
    // LD_A_D;
    // LD_addr_A(wUnusedNamesPointer + 1);
    gb_write16(wUnusedNamesPointer, de);

    // POP_DE;
    // POP_BC;
    // POP_HL;
    // POP_AF;
    // RST(aBankswitch);
    Bankswitch(tempBank);
}

//  Return the address of the
//  ath string starting from hl.
//  Not used.
void GetNthString(void){
    // AND_A_A;
    // RET_Z ;

    // PUSH_BC;
    // LD_B_A;
    // LD_C(0x50);

// readChar:
    // LD_A_hli;
    // CP_A_C;
    // IF_NZ goto readChar;
    // DEC_B;
    // IF_NZ goto readChar;
    // POP_BC;
    // RET;
}

//  Return the address of the
//  ath string starting from hl.
uint16_t GetNthString_GB(uint16_t hl, uint8_t a){
    // AND_A_A;
    // RET_Z ;
    if(a == 0)
        return hl;

    // PUSH_BC;
    // LD_B_A;
    // LD_C(0x50);
    uint8_t b = a;
    uint8_t c = 0x50;

    do {
        // LD_A_hli;
        a = gb_read(hl++);
    } while(a != c && --b != 0);
    return hl;
}

//  Discards gender (Nidoran).
uint8_t* GetBasePokemonName(species_t a){
    // PUSH_HL;
    // CALL(aGetPokemonName);
    uint8_t* hl = GetPokemonName(a);
    uint8_t* hl2 = hl;

    // LD_HL(wStringBuffer1);
    uint8_t x;

    for(;;hl++) 
    {
        // LD_A_hl;
        x = *hl;

        // CP_A(0x50);
        // IF_Z goto quit;
        if(x == 0x50) 
            break;
        
        // CP_A(0xef);
        // IF_Z goto end;
        // CP_A(0xf5);
        // IF_Z goto end;
        if(x == 0xef || x == 0xf5)
        {
            // LD_hl(0x50);
            *hl = 0x50;
            break;
        }

        // INC_HL;
        // goto loop;
    }

    // POP_HL;
    // RET;
    return hl2;
}

//  Discards gender (Nidoran).
void GetBasePokemonName_GB(void){
    // PUSH_HL;
    // CALL(aGetPokemonName);
    GetPokemonName_GB();

    // LD_HL(wStringBuffer1);
    uint16_t hl = wStringBuffer1;
    uint8_t a;

    for(;;hl++) 
    {
        // LD_A_hl;
        a = gb_read(hl);

        // CP_A(0x50);
        // IF_Z goto quit;
        if(a == 0x50) 
            break;
        
        // CP_A(0xef);
        // IF_Z goto end;
        // CP_A(0xf5);
        // IF_Z goto end;
        if(a == 0xef || a == 0xf5)
        {
            // LD_hl(0x50);
            gb_write(hl, 0x50);
            break;
        }

        // INC_HL;
        // goto loop;
    }

    // POP_HL;
    // RET;
    return;
}

//  Get Pokemon name for wNamedObjectIndex.
uint8_t* GetPokemonName(species_t index){
    if(index == 0 || index > NUM_POKEMON) {
        // Just in case...
        U82CB(wram->wStringBuffer1, MON_NAME_LENGTH, "?@");
        return wram->wStringBuffer1;
    }
    // LDH_A_addr(hROMBank);
    // PUSH_AF;
    // PUSH_HL;

    // LD_A(BANK(aPokemonNames));
    // RST(aBankswitch);

//  Each name is ten characters
    // LD_A_addr(wNamedObjectIndex);
    // DEC_A;
    // LD_D(0);
    // LD_E_A;
    // LD_H(0);
    // LD_L_A;

    // ADD_HL_HL;
    // ADD_HL_HL;

    // ADD_HL_DE;

    // ADD_HL_HL;

    // LD_DE(mPokemonNames);
    // ADD_HL_DE;
    // hl += (NAME_LENGTH - 1) * de;

//  Terminator
    // LD_DE(wStringBuffer1);
    // PUSH_DE;
    // LD_BC(MON_NAME_LENGTH - 1);
    // CALL(aCopyBytes);
    U82CB(wram->wStringBuffer1, MON_NAME_LENGTH, PokemonNames[index - 1]);

    // LD_HL(wStringBuffer1 + MON_NAME_LENGTH - 1);
    // LD_hl(0x50);
    // POP_DE;
    // wram->wStringBuffer1[MON_NAME_LENGTH - 1] = 0x50;

    // POP_HL;
    // POP_AF;
    // RST(aBankswitch);
    // RET;
    return wram->wStringBuffer1;
}

//  Get Pokemon name for wNamedObjectIndex.
//  DEPRECATED: Use GetPokemonName.
void GetPokemonName_GB(void){

    // LDH_A_addr(hROMBank);
    // PUSH_AF;
    // PUSH_HL;
    uint8_t tempBank = hram.hROMBank;

    // LD_A(BANK(aPokemonNames));
    // RST(aBankswitch);
    Bankswitch(BANK(aPokemonNames));

//  Each name is ten characters
    // LD_A_addr(wNamedObjectIndex);
    // DEC_A;
    // LD_D(0);
    // LD_E_A;
    // LD_H(0);
    // LD_L_A;
    uint16_t de = gb_read(wNamedObjectIndex) - 1;
    uint16_t hl = de;

    // ADD_HL_HL;
    // ADD_HL_HL;
    hl <<= 2;

    // ADD_HL_DE;
    hl += de;

    // ADD_HL_HL;
    hl += hl;

    // LD_DE(mPokemonNames);
    // ADD_HL_DE;
    hl += mPokemonNames;

//  Terminator
    // LD_DE(wStringBuffer1);
    // PUSH_DE;
    // LD_BC(MON_NAME_LENGTH - 1);
    // CALL(aCopyBytes);
    CopyBytes_GB(wStringBuffer1, hl, (MON_NAME_LENGTH - 1));

    // LD_HL(wStringBuffer1 + MON_NAME_LENGTH - 1);
    // LD_hl(0x50);
    // POP_DE;
    gb_write(wStringBuffer1 + MON_NAME_LENGTH - 1, 0x50);

    // POP_HL;
    // POP_AF;
    // RST(aBankswitch);
    // RET;
    Bankswitch(tempBank);
}

//  Get item name for a.
uint8_t* GetItemName(item_t a){
    // PUSH_HL;
    // PUSH_BC;
    // LD_A_addr(wNamedObjectIndex);

    // CP_A(TM01);
    // IF_NC goto TM;
    if(a >= TM01)
    {
    // TM:
        // CALL(aGetTMHMName);
        return GetTMHMName(a);
    }
    else 
    {
        // LD_addr_A(wCurSpecies);
        wram->wCurSpecies = a;

        // LD_A(ITEM_NAME);
        // LD_addr_A(wNamedObjectType);
        wram->wNamedObjectType = ITEM_NAME;

        // CALL(aGetName);
        GetName(ITEM_NAME, a);
    }
    // LD_DE(wStringBuffer1);
    // POP_BC;
    // POP_HL;
    // RET;
    return wram->wStringBuffer1;
}

//  Get TM/HM name for item a.
uint8_t* GetTMHMName(item_t a){
    // PUSH_HL;
    // PUSH_DE;
    // PUSH_BC;
    // LD_A_addr(wNamedObjectIndex);
    // PUSH_AF;

//  TM/HM prefix
    // CP_A(HM01);
    // PUSH_AF;
    // IF_C goto TM;
    if(a < HM01)
    {
        // LD_HL(mGetTMHMName_TMText);
        // LD_BC(mGetTMHMName_TMTextEnd - mGetTMHMName_TMText);
        // LD_DE(wStringBuffer1);
        // CALL(aCopyBytes);
        U82CA(wram->wStringBuffer1, "TM");
    }
    else 
    {
        // LD_HL(mGetTMHMName_HMText);
        // LD_BC(mGetTMHMName_HMTextEnd - mGetTMHMName_HMText);
        // LD_DE(wStringBuffer1);
        // CALL(aCopyBytes);
        U82CA(wram->wStringBuffer1, "HM");
    }

// copy:
//  TM/HM number
    // PUSH_DE;
    // LD_A_addr(wNamedObjectIndex);
    // LD_C_A;
    // CALLFAR(aGetTMHMNumber);
    uint8_t c = GetTMHMNumber(a);
    // POP_DE;

//  HM numbers start from 51, not 1
    // POP_AF;
    // LD_A_C;
    // IF_C goto not_hm;
    if(c >= CUT_TMNUM)
        c -= NUM_TMS;
    // SUB_A(NUM_TMS);

// not_hm:
    
//  Divide and mod by 10 to get the top and bottom digits respectively
    // LD_B(0xf6);

// mod10:
    // SUB_A(10);
    // IF_C goto done_mod;
    // INC_B;
    // goto mod10;


// done_mod:
    // ADD_A(10);
    // PUSH_AF;
    // LD_A_B;
    // LD_de_A;
    // INC_DE;
    wram->wStringBuffer1[2] = CHAR_0 + (c / 10);
    // POP_AF;

    // LD_B(0xf6);
    // ADD_A_B;
    // LD_de_A;
    wram->wStringBuffer1[3] = CHAR_0 + (c % 10);

//  End the string
    // INC_DE;
    // LD_A(0x50);
    // LD_de_A;
    wram->wStringBuffer1[4] = CHAR_TERM;

    // POP_AF;
    // LD_addr_A(wNamedObjectIndex);
    // POP_BC;
    // POP_DE;
    // POP_HL;
    // RET;
    return wram->wStringBuffer1;


// TMText:
        //db ['"TM"'];

// TMTextEnd:
        //db ['"@"'];


// HMText:
        //db ['"HM"'];

// HMTextEnd:
        //db ['"@"'];

// INCLUDE "home/hm_moves.asm"
}

uint8_t* GetMoveName(move_t move){
    // PUSH_HL;

    // LD_A(MOVE_NAME);
    // LD_addr_A(wNamedObjectType);

    // LD_A_addr(wNamedObjectIndex);  // move id
    // LD_addr_A(wCurSpecies);

    // CALL(aGetName);
    ByteFill(wram->wStringBuffer1, sizeof(wram->wStringBuffer1), CHAR_TERM);
    if(move >= 1)
        return U82CA(wram->wStringBuffer1, MoveNames[move - 1]);
    // LD_DE(wStringBuffer1);
    return wram->wStringBuffer1;
    // POP_HL;
    // RET;
}
