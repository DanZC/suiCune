#include "../constants.h"
#include "names.h"
#include "copy.h"

void NamesPointers(void){
    //  entries correspond to GetName constants (see constants/text_constants.asm)
    //dba ['PokemonNames']  // MON_NAME (not used// jumps to GetPokemonName)
    //dba ['MoveNames']  // MOVE_NAME
    //dba ['NULL']  // DUMMY_NAME
    //dba ['ItemNames']  // ITEM_NAME
    //dbw ['0', 'wPartyMonOTs']  // PARTY_OT_NAME
    //dbw ['0', 'wOTPartyMonOTs']  // ENEMY_OT_NAME
    //dba ['TrainerClassNames']  // TRAINER_NAME
    //dbw ['4', 'MoveDescriptions']  // MOVE_DESC_NAME_BROKEN (wrong bank)

    return GetName();
}

void GetName(void){
    //  Return name wCurSpecies from name list wNamedObjectType in wStringBuffer1.

    LDH_A_addr(hROMBank);
    PUSH_AF;
    PUSH_HL;
    PUSH_BC;
    PUSH_DE;

    LD_A_addr(wNamedObjectType);
    CP_A(MON_NAME);
    IF_NZ goto NotPokeName;

    LD_A_addr(wCurSpecies);
    LD_addr_A(wNamedObjectIndex);
    CALL(aGetPokemonName);
    LD_HL(MON_NAME_LENGTH);
    ADD_HL_DE;
    LD_E_L;
    LD_D_H;
    goto done;


NotPokeName:
        LD_A_addr(wNamedObjectType);
    DEC_A;
    LD_E_A;
    LD_D(0);
    LD_HL(mNamesPointers);
    ADD_HL_DE;
    ADD_HL_DE;
    ADD_HL_DE;
    LD_A_hli;
    RST(aBankswitch);
    LD_A_hli;
    LD_H_hl;
    LD_L_A;

    LD_A_addr(wCurSpecies);
    DEC_A;
    CALL(aGetNthString);

    LD_DE(wStringBuffer1);
    LD_BC(ITEM_NAME_LENGTH);
    CALL(aCopyBytes);


done:
        LD_A_E;
    LD_addr_A(wUnusedNamesPointer);
    LD_A_D;
    LD_addr_A(wUnusedNamesPointer + 1);

    POP_DE;
    POP_BC;
    POP_HL;
    POP_AF;
    RST(aBankswitch);
    RET;

}

void GetName_Conv(void){
    //  Return name wCurSpecies from name list wNamedObjectType in wStringBuffer1.

    // LDH_A_addr(hROMBank);
    // PUSH_AF;
    // PUSH_HL;
    // PUSH_BC;
    // PUSH_DE;
    uint8_t tempBank = gb_read(hROMBank);
    uint16_t de;

    // LD_A_addr(wNamedObjectType);
    // CP_A(MON_NAME);
    // IF_NZ goto NotPokeName;
    if(gb_read(wNamedObjectType) == MON_NAME) 
    {
        // LD_A_addr(wCurSpecies);
        // LD_addr_A(wNamedObjectIndex);
        gb_write(wNamedObjectIndex, gb_read(wCurSpecies));

        // CALL(aGetPokemonName);
        GetPokemonName_Conv();
        
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
        de = (gb_read(wNamedObjectType) - 1) & 0xFF;

        // LD_HL(mNamesPointers);
        uint16_t hl = mNamesPointers;

        // ADD_HL_DE;
        // ADD_HL_DE;
        // ADD_HL_DE;
        hl += (3 * de);

        // LD_A_hli;
        // RST(aBankswitch);
        Bankswitch_Conv(gb_read(hl++));

        // LD_A_hli;
        // LD_H_hl;
        // LD_L_A;
        hl = gb_read16(hl);

        // LD_A_addr(wCurSpecies);
        // DEC_A;
        // CALL(aGetNthString);
        hl = GetNthString_Conv(hl, gb_read(wCurSpecies) - 1);

        // LD_DE(wStringBuffer1);
        // LD_BC(ITEM_NAME_LENGTH);
        // CALL(aCopyBytes);
        CopyBytes_Conv(wStringBuffer1, hl, ITEM_NAME_LENGTH);
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
    Bankswitch_Conv(tempBank);
}

void GetNthString(void){
    //  Return the address of the
//  ath string starting from hl.

    AND_A_A;
    RET_Z ;

    PUSH_BC;
    LD_B_A;
    LD_C(0x50);

readChar:
        LD_A_hli;
    CP_A_C;
    IF_NZ goto readChar;
    DEC_B;
    IF_NZ goto readChar;
    POP_BC;
    RET;

}

//  Return the address of the
//  ath string starting from hl.
uint16_t GetNthString_Conv(uint16_t hl, uint8_t a){

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

void GetBasePokemonName(void){
    //  Discards gender (Nidoran).

    PUSH_HL;
    CALL(aGetPokemonName);

    LD_HL(wStringBuffer1);

loop:
        LD_A_hl;
    CP_A(0x50);
    IF_Z goto quit;
    CP_A(0xef);
    IF_Z goto end;
    CP_A(0xf5);
    IF_Z goto end;
    INC_HL;
    goto loop;

end:
        LD_hl(0x50);

quit:
        POP_HL;
    RET;

}

//  Discards gender (Nidoran).
void GetBasePokemonName_Conv(void){

    // PUSH_HL;
    // CALL(aGetPokemonName);
    GetPokemonName_Conv();

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

void GetPokemonName(void){
    //  Get Pokemon name for wNamedObjectIndex.

    LDH_A_addr(hROMBank);
    PUSH_AF;
    PUSH_HL;
    LD_A(BANK(aPokemonNames));
    RST(aBankswitch);

//  Each name is ten characters
    LD_A_addr(wNamedObjectIndex);
    DEC_A;
    LD_D(0);
    LD_E_A;
    LD_H(0);
    LD_L_A;
    ADD_HL_HL;
    ADD_HL_HL;
    ADD_HL_DE;
    ADD_HL_HL;
    LD_DE(mPokemonNames);
    ADD_HL_DE;

//  Terminator
    LD_DE(wStringBuffer1);
    PUSH_DE;
    LD_BC(MON_NAME_LENGTH - 1);
    CALL(aCopyBytes);
    LD_HL(wStringBuffer1 + MON_NAME_LENGTH - 1);
    LD_hl(0x50);
    POP_DE;

    POP_HL;
    POP_AF;
    RST(aBankswitch);
    RET;

}

//  Get Pokemon name for wNamedObjectIndex.
void GetPokemonName_Conv(void){

    // LDH_A_addr(hROMBank);
    // PUSH_AF;
    // PUSH_HL;
    uint8_t tempBank = gb_read(hROMBank);

    // LD_A(BANK(aPokemonNames));
    // RST(aBankswitch);
    Bankswitch_Conv(BANK(aPokemonNames));

//  Each name is ten characters
    // LD_A_addr(wNamedObjectIndex);
    // DEC_A;
    // LD_D(0);
    // LD_E_A;
    // LD_H(0);
    // LD_L_A;
    uint16_t de = gb_read(wNamedObjectIndex);
    uint16_t hl = de;

    // ADD_HL_HL;
    // ADD_HL_HL;
    hl += (2 * hl);

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
    CopyBytes_Conv(wStringBuffer1, hl, (MON_NAME_LENGTH - 1));

    // LD_HL(wStringBuffer1 + MON_NAME_LENGTH - 1);
    // LD_hl(0x50);
    // POP_DE;
    gb_write(wStringBuffer1 + MON_NAME_LENGTH - 1, 0x50);

    // POP_HL;
    // POP_AF;
    // RST(aBankswitch);
    // RET;
    Bankswitch_Conv(tempBank);
}

void GetItemName(void){
    //  Get item name for wNamedObjectIndex.

    PUSH_HL;
    PUSH_BC;
    LD_A_addr(wNamedObjectIndex);

    CP_A(TM01);
    IF_NC goto TM;

    LD_addr_A(wCurSpecies);
    LD_A(ITEM_NAME);
    LD_addr_A(wNamedObjectType);
    CALL(aGetName);
    goto Copied;

TM:
        CALL(aGetTMHMName);

Copied:
        LD_DE(wStringBuffer1);
    POP_BC;
    POP_HL;
    RET;

}

uint16_t GetItemName_Conv(void){
    //  Get item name for wNamedObjectIndex.

    // PUSH_HL;
    // PUSH_BC;
    // LD_A_addr(wNamedObjectIndex);
    uint8_t a = gb_read(wNamedObjectIndex);

    // CP_A(TM01);
    // IF_NC goto TM;
    if(a >= TM01)
    {
    TM:
        // CALL(aGetTMHMName);
        GetTMHMName_Conv();
    }
    else 
    {
        // LD_addr_A(wCurSpecies);
        gb_write(wCurSpecies, a);

        // LD_A(ITEM_NAME);
        // LD_addr_A(wNamedObjectType);
        gb_write(wNamedObjectType, ITEM_NAME);

        // CALL(aGetName);
        GetName_Conv();
    }
    // LD_DE(wStringBuffer1);
    // POP_BC;
    // POP_HL;
    // RET;
    return wStringBuffer1;
}

void GetTMHMName(void){
    //  Get TM/HM name for item wNamedObjectIndex.

    PUSH_HL;
    PUSH_DE;
    PUSH_BC;
    LD_A_addr(wNamedObjectIndex);
    PUSH_AF;

//  TM/HM prefix
    CP_A(HM01);
    PUSH_AF;
    IF_C goto TM;

    LD_HL(mGetTMHMName_HMText);
    LD_BC(mGetTMHMName_HMTextEnd - mGetTMHMName_HMText);
    goto copy;


TM:
        LD_HL(mGetTMHMName_TMText);
    LD_BC(mGetTMHMName_TMTextEnd - mGetTMHMName_TMText);


copy:
        LD_DE(wStringBuffer1);
    CALL(aCopyBytes);

//  TM/HM number
    PUSH_DE;
    LD_A_addr(wNamedObjectIndex);
    LD_C_A;
    CALLFAR(aGetTMHMNumber);
    POP_DE;

//  HM numbers start from 51, not 1
    POP_AF;
    LD_A_C;
    IF_C goto not_hm;
    SUB_A(NUM_TMS);

not_hm:
    
//  Divide and mod by 10 to get the top and bottom digits respectively
    LD_B(0xf6);

mod10:
        SUB_A(10);
    IF_C goto done_mod;
    INC_B;
    goto mod10;


done_mod:
        ADD_A(10);
    PUSH_AF;
    LD_A_B;
    LD_de_A;
    INC_DE;
    POP_AF;

    LD_B(0xf6);
    ADD_A_B;
    LD_de_A;

//  End the string
    INC_DE;
    LD_A(0x50);
    LD_de_A;

    POP_AF;
    LD_addr_A(wNamedObjectIndex);
    POP_BC;
    POP_DE;
    POP_HL;
    RET;


TMText:
        //db ['"TM"'];

TMTextEnd:
        //db ['"@"'];


HMText:
        //db ['"HM"'];

HMTextEnd:
        //db ['"@"'];

// INCLUDE "home/hm_moves.asm"

    return GetMoveName();
}

//  Get TM/HM name for item wNamedObjectIndex.
void GetTMHMName_Conv(void){

    // PUSH_HL;
    // PUSH_DE;
    // PUSH_BC;
    // LD_A_addr(wNamedObjectIndex);
    // PUSH_AF;
    uint8_t a = gb_read(wNamedObjectIndex);

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
        CopyBytes_Conv(wStringBuffer1, mGetTMHMName_TMText, (mGetTMHMName_TMTextEnd - mGetTMHMName_TMText));
    }
    else 
    {
        // LD_HL(mGetTMHMName_HMText);
        // LD_BC(mGetTMHMName_HMTextEnd - mGetTMHMName_HMText);
        // LD_DE(wStringBuffer1);
        // CALL(aCopyBytes);
        CopyBytes_Conv(wStringBuffer1, mGetTMHMName_HMText, (mGetTMHMName_HMTextEnd - mGetTMHMName_HMText));
    }

copy:
    

//  TM/HM number
    // PUSH_DE;
    // LD_A_addr(wNamedObjectIndex);
    // LD_C_A;
    REG_C = gb_read(wNamedObjectIndex);
    CALLFAR(aGetTMHMNumber);
    // POP_DE;

//  HM numbers start from 51, not 1
    // POP_AF;
    // LD_A_C;
    // IF_C goto not_hm;
    // SUB_A(NUM_TMS);

not_hm:
    
//  Divide and mod by 10 to get the top and bottom digits respectively
    LD_B(0xf6);

mod10:
        SUB_A(10);
    IF_C goto done_mod;
    INC_B;
    goto mod10;


done_mod:
        ADD_A(10);
    PUSH_AF;
    LD_A_B;
    LD_de_A;
    INC_DE;
    POP_AF;

    LD_B(0xf6);
    ADD_A_B;
    LD_de_A;

//  End the string
    INC_DE;
    LD_A(0x50);
    LD_de_A;

    POP_AF;
    LD_addr_A(wNamedObjectIndex);
    POP_BC;
    POP_DE;
    POP_HL;
    RET;


TMText:
        //db ['"TM"'];

TMTextEnd:
        //db ['"@"'];


HMText:
        //db ['"HM"'];

HMTextEnd:
        //db ['"@"'];

// INCLUDE "home/hm_moves.asm"

    return GetMoveName();
}

void GetMoveName(void){
        PUSH_HL;

    LD_A(MOVE_NAME);
    LD_addr_A(wNamedObjectType);

    LD_A_addr(wNamedObjectIndex);  // move id
    LD_addr_A(wCurSpecies);

    CALL(aGetName);
    LD_DE(wStringBuffer1);

    POP_HL;
    RET;

}
