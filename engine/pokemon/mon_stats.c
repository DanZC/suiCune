#include "../../constants.h"
#include "mon_stats.h"
#include "../../home/names.h"
#include "../../home/copy.h"
#include "../../home/text.h"
#include "../../charmap.h"
#include "../items/item_effects.h"
#include "../../home/print_text.h"
#include "../../home/pokemon.h"
#include "../../data/pokemon/base_stats.h"
#include "health.h"

void DrawPlayerHP(void){
    LD_A(0x1);
    JR(mDrawHP);

}

uint8_t DrawPlayerHP_Conv(uint8_t* hl, uint8_t b){
    // LD_A(0x1);
    // JR(mDrawHP);
    return DrawHP_Conv(hl, b, 0x1);
}

void DrawEnemyHP(void){
    LD_A(0x2);

    return DrawHP();
}

uint8_t DrawEnemyHP_Conv(uint8_t* hl, uint8_t b){
    // LD_A(0x2);
    // JR(mDrawHP);
    return DrawHP_Conv(hl, b, 0x2);
}


void DrawHP(void){
    LD_addr_A(wWhichHPBar);
    PUSH_HL;
    PUSH_BC;
// box mons have full HP
    LD_A_addr(wMonType);
    CP_A(BOXMON);
    IF_Z goto at_least_1_hp;

    LD_A_addr(wTempMonHP);
    LD_B_A;
    LD_A_addr(wTempMonHP + 1);
    LD_C_A;

//  Any HP?
    OR_A_B;
    IF_NZ goto at_least_1_hp;

    XOR_A_A;
    LD_C_A;
    LD_E_A;
    LD_A(6);
    LD_D_A;
    JP(mDrawHP_fainted);


at_least_1_hp:
    LD_A_addr(wTempMonMaxHP);
    LD_D_A;
    LD_A_addr(wTempMonMaxHP + 1);
    LD_E_A;
    LD_A_addr(wMonType);
    CP_A(BOXMON);
    IF_NZ goto not_boxmon;

    LD_B_D;
    LD_C_E;


not_boxmon:
    PREDEF(pComputeHPBarPixels);
    LD_A(6);
    LD_D_A;
    LD_C_A;


fainted:
    LD_A_C;
    POP_BC;
    LD_C_A;
    POP_HL;
    PUSH_DE;
    PUSH_HL;
    PUSH_HL;
    CALL(aDrawBattleHPBar);
    POP_HL;

//  Print HP
    bccoord(1, 1, 0);
    ADD_HL_BC;
    LD_DE(wTempMonHP);
    LD_A_addr(wMonType);
    CP_A(BOXMON);
    IF_NZ goto not_boxmon_2;
    LD_DE(wTempMonMaxHP);

not_boxmon_2:
    LD_BC((2 << 8) | 3);
    CALL(aPrintNum);

    LD_A(0xf3);
    LD_hli_A;

//  Print max HP
    LD_DE(wTempMonMaxHP);
    LD_BC((2 << 8) | 3);
    CALL(aPrintNum);
    POP_HL;
    POP_DE;
    RET;

}

uint8_t DrawHP_Conv(uint8_t* hl, uint8_t b, uint8_t which){
    // LD_addr_A(wWhichHPBar);
    wram->wWhichHPBar = which;
    // PUSH_HL;
    // PUSH_BC;
// box mons have full HP
    // LD_A_addr(wMonType);
    // CP_A(BOXMON);
    // IF_Z goto at_least_1_hp;

    // LD_A_addr(wTempMonHP);
    // LD_B_A;
    // LD_A_addr(wTempMonHP + 1);
    // LD_C_A;

//  Any HP?
    // OR_A_B;
    // IF_NZ goto at_least_1_hp;
    union Register bc = {.hi=LOW(wram->wTempMon.HP), .lo=HIGH(wram->wTempMon.HP)};
    union Register de;
    if(wram->wMonType != BOXMON && wram->wTempMon.HP == 0) {
        // XOR_A_A;
        // LD_C_A;
        bc.lo = 0;
        // LD_E_A;
        de.lo = 0;
        // LD_A(6);
        // LD_D_A;
        de.hi = 6;
        // JP(mDrawHP_fainted);
    }
    else {
    // at_least_1_hp:
        // LD_A_addr(wTempMonMaxHP);
        // LD_D_A;
        de.hi = LOW(wram->wTempMon.maxHP);
        // LD_A_addr(wTempMonMaxHP + 1);
        // LD_E_A;
        de.lo = HIGH(wram->wTempMon.maxHP);
        // LD_A_addr(wMonType);
        // CP_A(BOXMON);
        // IF_NZ goto not_boxmon;

        if(wram->wMonType == BOXMON)
            // LD_B_D;
            // LD_C_E;
            bc.reg = de.reg;


    // not_boxmon:
        // PREDEF(pComputeHPBarPixels);
        de.lo = ComputeHPBarPixels_Conv(bc.reg, de.reg);
        // LD_A(6);
        // LD_D_A;
        de.hi = 6;
        // LD_C_A;
        bc.lo = 6;
    }


// fainted:
    // LD_A_C;
    // POP_BC;
    // LD_C_A;
    // POP_HL;
    // PUSH_DE;
    // PUSH_HL;
    // PUSH_HL;
    // CALL(aDrawBattleHPBar);
    DrawBattleHPBar_Conv(hl, de.hi, de.lo, b, bc.lo);
    // POP_HL;

//  Print HP
    // bccoord(1, 1, 0);
    // ADD_HL_BC;
    // LD_DE(wTempMonHP);
    // LD_A_addr(wMonType);
    // CP_A(BOXMON);
    // IF_NZ goto not_boxmon_2;
    // LD_DE(wTempMonMaxHP);
    void* maxhpval = ((wram->wMonType == BOXMON)? &wram->wTempMon.maxHP: &wram->wTempMon.HP);

// not_boxmon_2:
    // LD_BC((2 << 8) | 3);
    // CALL(aPrintNum);
    hl = PrintNum_Conv2(hl + coord(1, 1, 0), maxhpval, 2, 3);

    // LD_A(0xf3);
    // LD_hli_A;
    *(hl++) = CHAR_FWD_SLASH;

//  Print max HP
    // LD_DE(wTempMonMaxHP);
    // LD_BC((2 << 8) | 3);
    // CALL(aPrintNum);
    PrintNum_Conv2(hl, &wram->wTempMon.maxHP, 2, 3);
    // POP_HL;
    // POP_DE;
    // RET;
    return de.lo;
}

void PrintTempMonStats(void){
//  Print wTempMon's stats at hl, with spacing bc.
    PUSH_BC;
    PUSH_HL;
    LD_DE(mPrintTempMonStats_StatNames);
    CALL(aPlaceString);
    POP_HL;
    POP_BC;
    ADD_HL_BC;
    LD_BC(SCREEN_WIDTH);
    ADD_HL_BC;
    LD_DE(wTempMonAttack);
    LD_BC((2 << 8) | 3);
    CALL(aPrintTempMonStats_PrintStat);
    LD_DE(wTempMonDefense);
    CALL(aPrintTempMonStats_PrintStat);
    LD_DE(wTempMonSpclAtk);
    CALL(aPrintTempMonStats_PrintStat);
    LD_DE(wTempMonSpclDef);
    CALL(aPrintTempMonStats_PrintStat);
    LD_DE(wTempMonSpeed);
    JP(mPrintNum);


PrintStat:
    PUSH_HL;
    CALL(aPrintNum);
    POP_HL;
    LD_DE(SCREEN_WIDTH * 2);
    ADD_HL_DE;
    RET;


StatNames:
    //db ['"ATTACK"'];
    //next ['"DEFENSE"']
    //next ['"SPCL.ATK"']
    //next ['"SPCL.DEF"']
    //next ['"SPEED"']
    //next ['"@"']

    return GetGender();
}

//  Print wTempMon's stats at hl, with spacing bc.
void PrintTempMonStats_Conv(uint8_t* hl, uint16_t bc){
    static const char StatNames[] = "ATTACK" \
        t_next "DEFENSE" \
        t_next "SPCL.ATK" \
        t_next "SPCL.DEF" \
        t_next "SPEED" \
        t_next "@";

    // PUSH_BC;
    // PUSH_HL;
    // LD_DE(mPrintTempMonStats_StatNames);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(StatNames), hl);
    // POP_HL;
    // POP_BC;
    // ADD_HL_BC;
    // LD_BC(SCREEN_WIDTH);
    // ADD_HL_BC;
    hl += bc + SCREEN_WIDTH;
    // LD_DE(wTempMonAttack);
    // LD_BC((2 << 8) | 3);
    // CALL(aPrintTempMonStats_PrintStat);
    PrintNum_Conv2(hl, &wram->wTempMon.attack, 2, 3);
    hl += SCREEN_WIDTH * 2;
    // LD_DE(wTempMonDefense);
    // CALL(aPrintTempMonStats_PrintStat);
    PrintNum_Conv2(hl, &wram->wTempMon.defense, 2, 3);
    hl += SCREEN_WIDTH * 2;
    // LD_DE(wTempMonSpclAtk);
    // CALL(aPrintTempMonStats_PrintStat);
    PrintNum_Conv2(hl, &wram->wTempMon.spclAtk, 2, 3);
    hl += SCREEN_WIDTH * 2;
    // LD_DE(wTempMonSpclDef);
    // CALL(aPrintTempMonStats_PrintStat);
    PrintNum_Conv2(hl, &wram->wTempMon.spclDef, 2, 3);
    hl += SCREEN_WIDTH * 2;
    // LD_DE(wTempMonSpeed);
    // JP(mPrintNum);
    PrintNum_Conv2(hl, &wram->wTempMon.speed, 2, 3);
    hl += SCREEN_WIDTH * 2;


// PrintStat:
    // PUSH_HL;
    // CALL(aPrintNum);
    // POP_HL;
    // LD_DE(SCREEN_WIDTH * 2);
    // ADD_HL_DE;
    // RET;
}

void GetGender(void){
//  Return the gender of a given monster (wCurPartyMon/wCurOTMon/wCurWildMon).
//  When calling this function, a should be set to an appropriate wMonType value.

//  return values:
//  a = 1: f = nc|nz
//  a = 0: f = nc|z
//         f = c:  genderless

//  This is determined by comparing the Attack and Speed DVs
//  with the species' gender ratio.

//  Figure out what type of monster struct we're looking at.

//  0: PartyMon
    LD_HL(wPartyMon1DVs);
    LD_BC(PARTYMON_STRUCT_LENGTH);
    LD_A_addr(wMonType);
    AND_A_A;
    IF_Z goto PartyMon;

//  1: OTPartyMon
    LD_HL(wOTPartyMon1DVs);
    DEC_A;
    IF_Z goto PartyMon;

//  2: sBoxMon
    LD_HL(sBoxMon1DVs);
    LD_BC(BOXMON_STRUCT_LENGTH);
    DEC_A;
    IF_Z goto sBoxMon;

//  3: Unknown
    LD_HL(wTempMonDVs);
    DEC_A;
    IF_Z goto DVs;

//  else: WildMon
    LD_HL(wEnemyMonDVs);
    goto DVs;

//  Get our place in the party/box.


PartyMon:

sBoxMon:
    LD_A_addr(wCurPartyMon);
    CALL(aAddNTimes);


DVs:
//  sBoxMon data is read directly from SRAM.
    LD_A_addr(wMonType);
    CP_A(BOXMON);
    LD_A(MBANK(asBox));
    CALL_Z (aOpenSRAM);

//  Attack DV
    LD_A_hli;
    AND_A(0xf0);
    LD_B_A;
//  Speed DV
    LD_A_hl;
    AND_A(0xf0);
    SWAP_A;

//  Put our DVs together.
    OR_A_B;
    LD_B_A;

//  Close SRAM if we were dealing with a sBoxMon.
    LD_A_addr(wMonType);
    CP_A(BOXMON);
    CALL_Z (aCloseSRAM);

//  We need the gender ratio to do anything with this.
    PUSH_BC;
    LD_A_addr(wCurPartySpecies);
    DEC_A;
    LD_HL(mBaseData + BASE_GENDER);
    LD_BC(BASE_DATA_SIZE);
    CALL(aAddNTimes);
    POP_BC;

    LD_A(BANK(aBaseData));
    CALL(aGetFarByte);

//  The higher the ratio, the more likely the monster is to be female.

    CP_A(GENDER_UNKNOWN);
    IF_Z goto Genderless;

    AND_A_A;  // GENDER_F0?
    IF_Z goto Male;

    CP_A(GENDER_F100);
    IF_Z goto Female;

//  Values below the ratio are male, and vice versa.
    CP_A_B;
    IF_C goto Male;


Female:
    XOR_A_A;
    RET;


Male:
    LD_A(1);
    AND_A_A;
    RET;


Genderless:
    SCF;
    RET;

}

//  Return the gender of a given monster (wCurPartyMon/wCurOTMon/wCurWildMon).
//  When calling this function, a should be set to an appropriate wMonType value.
//  return values:
//  a = 1: f = nc|nz
//  a = 0: f = nc|z
//         f = c:  genderless
//  This is determined by comparing the Attack and Speed DVs
//  with the species' gender ratio.
u8_flag_s GetGender_Conv(uint8_t monType){
//  Figure out what type of monster struct we're looking at.

    uint16_t DVs = 0;
    switch(monType) {
//  0: PartyMon
    // LD_HL(wPartyMon1DVs);
    // LD_BC(PARTYMON_STRUCT_LENGTH);
    // LD_A_addr(wMonType);
    // AND_A_A;
    // IF_Z goto PartyMon;
    case PARTYMON:
        DVs = wram->wPartyMon[wram->wCurPartyMon].mon.DVs;
        break;

//  1: OTPartyMon
    // LD_HL(wOTPartyMon1DVs);
    // DEC_A;
    // IF_Z goto PartyMon;
    case OTPARTYMON:
        DVs = wram->wOTPartyMon[wram->wCurPartyMon].mon.DVs;
        break;

//  2: sBoxMon
    // LD_HL(sBoxMon1DVs);
    // LD_BC(BOXMON_STRUCT_LENGTH);
    // DEC_A;
    // IF_Z goto sBoxMon;
    case BOXMON:
        break;

//  3: Unknown
    // LD_HL(wTempMonDVs);
    // DEC_A;
    // IF_Z goto DVs;
    case TEMPMON:
        DVs = wram->wTempMon.mon.DVs;
        break;

//  else: WildMon
    // LD_HL(wEnemyMonDVs);
    // goto DVs;
    default:
    case WILDMON:
        DVs = wram->wEnemyMon.dvs;
        break;

//  Get our place in the party/box.


// PartyMon:

// sBoxMon:
    // LD_A_addr(wCurPartyMon);
    // CALL(aAddNTimes);

    }
// DVs:
//  sBoxMon data is read directly from SRAM.
    // LD_A_addr(wMonType);
    // CP_A(BOXMON);
    // LD_A(BANK(sBox));
    // CALL_Z (aOpenSRAM);

//  Attack DV
    // LD_A_hli;
    // AND_A(0xf0);
    // LD_B_A;
//  Speed DV
    // LD_A_hl;
    // AND_A(0xf0);
    // SWAP_A;

//  Put our DVs together.
    // OR_A_B;
    // LD_B_A;
    uint8_t b = (uint8_t)((DVs & 0xf0) | ((DVs & 0xf000) >> 12));

//  Close SRAM if we were dealing with a sBoxMon.
    // LD_A_addr(wMonType);
    // CP_A(BOXMON);
    // CALL_Z (aCloseSRAM);

//  We need the gender ratio to do anything with this.
    // PUSH_BC;
    // LD_A_addr(wCurPartySpecies);
    // DEC_A;
    // LD_HL(mBaseData + BASE_GENDER);
    // LD_BC(BASE_DATA_SIZE);
    // CALL(aAddNTimes);
    // POP_BC;

    // LD_A(BANK(aBaseData));
    // CALL(aGetFarByte);
    // uint8_t a = GetFarByte_Conv(BANK(aBaseData), mBaseData + BASE_GENDER + (BASE_DATA_SIZE * wram->wCurPartySpecies));
    uint8_t a = BasePokemonData[wram->wCurPartySpecies - 1].gender;

//  The higher the ratio, the more likely the monster is to be female.

    // CP_A(GENDER_UNKNOWN);
    // IF_Z goto Genderless;
    if(a == (uint8_t)GENDER_UNKNOWN)
    // Genderless:
        // SCF;
        // RET;
        return (u8_flag_s){.a = 0, .flag = true};

    // AND_A_A;  // GENDER_F0?
    // IF_Z goto Male;
    if(a == GENDER_F0)
    // Male:
        // LD_A(1);
        // AND_A_A;
        // RET;
        return (u8_flag_s){.a = 1, .flag = false};


    // CP_A(GENDER_F100);
    // IF_Z goto Female;
//  Values below the ratio are male, and vice versa.
    // CP_A_B;
    // IF_C goto Male;
    if(a == GENDER_F100 || a >= b) {
    // Female:
        // XOR_A_A;
        // RET;
        return (u8_flag_s){.a = 0, .flag = false};
    }
// Male:
    // LD_A(1);
    // AND_A_A;
    // RET;
    return (u8_flag_s){.a = 1, .flag = false};
}

void ListMovePP(void){
    LD_A_addr(wNumMoves);
    INC_A;
    LD_C_A;
    LD_A(NUM_MOVES);
    SUB_A_C;
    LD_B_A;
    PUSH_HL;
    LD_A_addr(wListMovesLineSpacing);
    LD_E_A;
    LD_D(0);
    LD_A(0x3e);  // P
    CALL(aListMovePP_load_loop);
    LD_A_B;
    AND_A_A;
    IF_Z goto skip;
    LD_C_A;
    LD_A(0xe3);
    CALL(aListMovePP_load_loop);


skip:
    POP_HL;
    INC_HL;
    INC_HL;
    INC_HL;
    LD_D_H;
    LD_E_L;
    LD_HL(wTempMonMoves);
    LD_B(0);

loop:
    LD_A_hli;
    AND_A_A;
    IF_Z goto done;
    PUSH_BC;
    PUSH_HL;
    PUSH_DE;
    LD_HL(wMenuCursorY);
    LD_A_hl;
    PUSH_AF;
    LD_hl_B;
    PUSH_HL;
    CALLFAR(aGetMaxPPOfMove);
    POP_HL;
    POP_AF;
    LD_hl_A;
    POP_DE;
    POP_HL;
    PUSH_HL;
    LD_BC(wTempMonPP - (wTempMonMoves + 1));
    ADD_HL_BC;
    LD_A_hl;
    AND_A(0x3f);
    LD_addr_A(wStringBuffer1 + 4);
    LD_H_D;
    LD_L_E;
    PUSH_HL;
    LD_DE(wStringBuffer1 + 4);
    LD_BC((1 << 8) | 2);
    CALL(aPrintNum);
    LD_A(0xf3);
    LD_hli_A;
    LD_DE(wTempPP);
    LD_BC((1 << 8) | 2);
    CALL(aPrintNum);
    POP_HL;
    LD_A_addr(wListMovesLineSpacing);
    LD_E_A;
    LD_D(0);
    ADD_HL_DE;
    LD_D_H;
    LD_E_L;
    POP_HL;
    POP_BC;
    INC_B;
    LD_A_B;
    CP_A(NUM_MOVES);
    IF_NZ goto loop;


done:
    RET;


load_loop:
    LD_hli_A;
    LD_hld_A;
    ADD_HL_DE;
    DEC_C;
    IF_NZ goto load_loop;
    RET;

}

static uint8_t* ListMovePP_load_loop(uint8_t* hl, uint8_t a, uint16_t de, uint8_t c) {
    do {
// load_loop:
        // LD_hli_A;
        hl[0] = a;
        // LD_hld_A;
        hl[1] = a;
        // ADD_HL_DE;
        hl += de;
        // DEC_C;
        // IF_NZ goto load_loop;
    } while(--c != 0);
    // RET;
    return hl;
}

void ListMovePP_Conv(uint8_t* hl){
    // LD_A_addr(wNumMoves);
    // INC_A;
    // LD_C_A;
    uint8_t c = wram->wNumMoves + 1;
    // LD_A(NUM_MOVES);
    // SUB_A_C;
    // LD_B_A;
    // PUSH_HL;
    // LD_A_addr(wListMovesLineSpacing);
    // LD_E_A;
    // LD_D(0);
    // LD_A(0x3e);  // P
    // CALL(aListMovePP_load_loop);
    uint8_t* hl2 = ListMovePP_load_loop(hl, 0x3e, wram->wListMovesLineSpacing, c);
    // LD_A_B;
    // AND_A_A;
    // IF_Z goto skip;
    if(NUM_MOVES - c != 0) {
        // LD_C_A;
        // LD_A(0xe3);
        // CALL(aListMovePP_load_loop);
        ListMovePP_load_loop(hl2, 0xe3, wram->wListMovesLineSpacing, NUM_MOVES - c);
    }


// skip:
    // POP_HL;
    // INC_HL;
    // INC_HL;
    // INC_HL;
    // LD_D_H;
    // LD_E_L;
    uint8_t* de = hl + 3;
    // LD_HL(wTempMonMoves);
    move_t* moves = wram->wTempMon.mon.moves;
    // LD_B(0);
    uint8_t b = 0;

    do {
    // loop:
        // LD_A_hli;
        // AND_A_A;
        // IF_Z goto done;
        move_t a = *(moves++);
        if(a == NO_MOVE)
            return;
        // PUSH_BC;
        // PUSH_HL;
        // PUSH_DE;
        // LD_HL(wMenuCursorY);
        // LD_A_hl;
        // PUSH_AF;
        uint8_t oldcursorY = wram->wMenuCursorY;
        // LD_hl_B;
        wram->wMenuCursorY = b;
        // PUSH_HL;
        // CALLFAR(aGetMaxPPOfMove);
        uint8_t maxpp = GetMaxPPOfMove_Conv(&wram->wTempMon, TEMPMON, b);
        // POP_HL;
        // POP_AF;
        // LD_hl_A;
        wram->wMenuCursorY = oldcursorY;
        // POP_DE;
        // POP_HL;
        // PUSH_HL;
        // LD_BC(wTempMonPP - (wTempMonMoves + 1));
        // ADD_HL_BC;
        // LD_A_hl;
        // AND_A(0x3f);
        // LD_addr_A(wStringBuffer1 + 4);
        uint8_t monpp = wram->wTempMon.mon.PP[b];
        // LD_H_D;
        // LD_L_E;
        // PUSH_HL;
        uint8_t* hl3 = de;
        // LD_DE(wStringBuffer1 + 4);
        // LD_BC((1 << 8) | 2);
        // CALL(aPrintNum);
        hl3 = PrintNum_Conv2(hl3, &monpp, 1, 2);
        // LD_A(0xf3);
        // LD_hli_A;
        *(hl3++) = CHAR_FWD_SLASH;
        // LD_DE(wTempPP);
        // LD_BC((1 << 8) | 2);
        // CALL(aPrintNum);
        hl3 = PrintNum_Conv2(hl3, &maxpp, 1, 2);
        // POP_HL;
        // LD_A_addr(wListMovesLineSpacing);
        // LD_E_A;
        // LD_D(0);
        // ADD_HL_DE;
        // LD_D_H;
        // LD_E_L;
        de += wram->wListMovesLineSpacing;
        // POP_HL;
        // POP_BC;
        // INC_B;
        // LD_A_B;
        // CP_A(NUM_MOVES);
        // IF_NZ goto loop;
    } while(++b != NUM_MOVES);

// done:
    // RET;
}

void BrokenPlacePPUnits(void){
//  //  unreferenced
//  Probably would have these parameters:
//  hl = starting coordinate
//  de = SCREEN_WIDTH or SCREEN_WIDTH * 2
//  c = the number of moves (1-4)

loop:
    LD_hl(0x32);  // typo for P?
    INC_HL;
    LD_hl(0x3e);  // P
    DEC_HL;
    ADD_HL_DE;
    DEC_C;
    IF_NZ goto loop;
    RET;

}

void Unused_PlaceEnemyHPLevel(void){
    PUSH_HL;
    PUSH_HL;
    LD_HL(wPartyMonNicknames);
    LD_A_addr(wCurPartyMon);
    CALL(aGetNickname);
    POP_HL;
    CALL(aPlaceString);
    CALL(aCopyMonToTempMon);
    POP_HL;
    LD_A_addr(wCurPartySpecies);
    CP_A(EGG);
    IF_Z goto egg;
    PUSH_HL;
    LD_BC(-12);
    ADD_HL_BC;
    LD_B(0);
    CALL(aDrawEnemyHP);
    POP_HL;
    LD_BC(5);
    ADD_HL_BC;
    PUSH_DE;
    CALL(aPrintLevel);
    POP_DE;


egg:
    RET;

}

void PlaceStatusString(void){
//  Return nz if the status is not OK
    PUSH_DE;
    INC_DE;
    INC_DE;
    LD_A_de;
    LD_B_A;
    INC_DE;
    LD_A_de;
    OR_A_B;
    POP_DE;
    JR_NZ (mPlaceNonFaintStatus);
    PUSH_DE;
    LD_DE(mFntString);
    CALL(aCopyStatusString);
    POP_DE;
    LD_A(TRUE);
    AND_A_A;
    RET;

}

//  Return nz if the status is not OK
bool PlaceStatusString_Conv(uint8_t* hl, struct PartyMon* de){
    // PUSH_DE;
    // INC_DE;
    // INC_DE;
    // LD_A_de;
    // LD_B_A;
    // INC_DE;
    // LD_A_de;
    // OR_A_B;
    // POP_DE;
    // JR_NZ (mPlaceNonFaintStatus);
    if((de->HP | de->maxHP) != 0) {
        return PlaceNonFaintStatus_Conv(hl, de);
    }
    // PUSH_DE;
    // LD_DE(mFntString);
    // CALL(aCopyStatusString);
    CopyStatusString_Conv(hl, Utf8ToCrystal(FntString));
    // POP_DE;
    // LD_A(TRUE);
    // AND_A_A;
    // RET;
    return true;
}

const char FntString[] = "FNT@";

void CopyStatusString(void){
    LD_A_de;
    INC_DE;
    LD_hli_A;
    LD_A_de;
    INC_DE;
    LD_hli_A;
    LD_A_de;
    LD_hl_A;
    RET;

}

void CopyStatusString_Conv(uint8_t* hl, uint8_t* de){
    // LD_A_de;
    // INC_DE;
    // LD_hli_A;
    *(hl++) = *(de++);
    // LD_A_de;
    // INC_DE;
    // LD_hli_A;
    *(hl++) = *(de++);
    // LD_A_de;
    // LD_hl_A;
    *(hl) = *(de);
    // RET;
}

void PlaceNonFaintStatus(void){
    PUSH_DE;
    LD_A_de;
    LD_DE(mPsnString);
    BIT_A(PSN);
    IF_NZ goto place;
    LD_DE(mBrnString);
    BIT_A(BRN);
    IF_NZ goto place;
    LD_DE(mFrzString);
    BIT_A(FRZ);
    IF_NZ goto place;
    LD_DE(mParString);
    BIT_A(PAR);
    IF_NZ goto place;
    LD_DE(mSlpString);
    AND_A(SLP);
    IF_Z goto no_status;


place:
    CALL(aCopyStatusString);
    LD_A(TRUE);
    AND_A_A;


no_status:
    POP_DE;
    RET;

}

bool PlaceNonFaintStatus_Conv(uint8_t* hl, struct PartyMon* de){
    return PlaceNonFaintStatus2_Conv(hl, de->status);
}

bool PlaceNonFaintStatus2_Conv(uint8_t* hl, uint8_t status){
    // PUSH_DE;
    // LD_A_de;
    uint8_t a = status;
    // LD_DE(mPsnString);
    // BIT_A(PSN);
    // IF_NZ goto place;
    if(bit_test(a, PSN)) {
    // place:
        // CALL(aCopyStatusString);
        CopyStatusString_Conv(hl, U82C(PsnString));
        // LD_A(TRUE);
        // AND_A_A;
        return true;
    }
    // LD_DE(mBrnString);
    // BIT_A(BRN);
    // IF_NZ goto place;
    if(bit_test(a, BRN)) {
    // place:
        // CALL(aCopyStatusString);
        CopyStatusString_Conv(hl, U82C(BrnString));
        // LD_A(TRUE);
        // AND_A_A;
        return true;
    }
    // LD_DE(mFrzString);
    // BIT_A(FRZ);
    // IF_NZ goto place;
    if(bit_test(a, FRZ)) {
    // place:
        // CALL(aCopyStatusString);
        CopyStatusString_Conv(hl, U82C(FrzString));
        // LD_A(TRUE);
        // AND_A_A;
        return true;
    }
    // LD_DE(mParString);
    // BIT_A(PAR);
    // IF_NZ goto place;
    if(bit_test(a, PAR)) {
    // place:
        // CALL(aCopyStatusString);
        CopyStatusString_Conv(hl, U82C(ParString));
        // LD_A(TRUE);
        // AND_A_A;
        return true;
    }
    // LD_DE(mSlpString);
    // AND_A(SLP);
    // IF_Z goto no_status;
    if(a & SLP) {
    // place:
        // CALL(aCopyStatusString);
        CopyStatusString_Conv(hl, U82C(SlpString));
        // LD_A(TRUE);
        // AND_A_A;
        return true;
    }
    return false;
}

const char SlpString[] = "SLP@";

const char PsnString[] = "PSN@";

const char BrnString[] = "BRN@";

const char FrzString[] = "FRZ@";

const char ParString[] = "PAR@";

void ListMoves(void){
//  List moves at hl, spaced every [wListMovesLineSpacing] tiles.
    LD_DE(wListMoves_MoveIndicesBuffer);
    LD_B(0);

moves_loop:
    LD_A_de;
    INC_DE;
    AND_A_A;
    IF_Z goto no_more_moves;
    PUSH_DE;
    PUSH_HL;
    PUSH_HL;
    LD_addr_A(wCurSpecies);
    LD_A(MOVE_NAME);
    LD_addr_A(wNamedObjectType);
    CALL(aGetName);
    LD_DE(wStringBuffer1);
    POP_HL;
    PUSH_BC;
    CALL(aPlaceString);
    POP_BC;
    LD_A_B;
    LD_addr_A(wNumMoves);
    INC_B;
    POP_HL;
    PUSH_BC;
    LD_A_addr(wListMovesLineSpacing);
    LD_C_A;
    LD_B(0);
    ADD_HL_BC;
    POP_BC;
    POP_DE;
    LD_A_B;
    CP_A(NUM_MOVES);
    IF_Z goto done;
    goto moves_loop;


no_more_moves:
    LD_A_B;

nonmove_loop:
    PUSH_AF;
    LD_hl(0xe3);
    LD_A_addr(wListMovesLineSpacing);
    LD_C_A;
    LD_B(0);
    ADD_HL_BC;
    POP_AF;
    INC_A;
    CP_A(NUM_MOVES);
    IF_NZ goto nonmove_loop;


done:
    RET;

}

//  List moves at hl, spaced every [wListMovesLineSpacing] tiles.
void ListMoves_Conv(uint8_t* hl){
    // LD_DE(wListMoves_MoveIndicesBuffer);
    move_t* de = wram->wListMoves_MoveIndicesBuffer;
    // LD_B(0);
    uint8_t b = 0;

    while(1)
    {
    // moves_loop:
        // LD_A_de;
        // INC_DE;
        // AND_A_A;
        // IF_Z goto no_more_moves;
        if(*de == NO_MOVE) 
            break;
        // PUSH_DE;
        // PUSH_HL;
        // PUSH_HL;
        // LD_addr_A(wCurSpecies);
        // LD_A(MOVE_NAME);
        // LD_addr_A(wNamedObjectType);
        // CALL(aGetName);
        // LD_DE(wStringBuffer1);
        // POP_HL;
        // PUSH_BC;
        // CALL(aPlaceString);
        PlaceStringSimple(GetName_Conv2(MOVE_NAME, *de), hl);
        // POP_BC;
        // LD_A_B;
        // LD_addr_A(wNumMoves);
        wram->wNumMoves = b;
        // INC_B;
        // POP_HL;
        // PUSH_BC;
        // LD_A_addr(wListMovesLineSpacing);
        // LD_C_A;
        // LD_B(0);
        // ADD_HL_BC;
        // POP_BC;
        // POP_DE;
        hl += wram->wListMovesLineSpacing;
        // LD_A_B;
        // CP_A(NUM_MOVES);
        // IF_Z goto done;
        if(++b == NUM_MOVES)
            return;
        // goto moves_loop;
        de++;
    }


// no_more_moves:
    // LD_A_B;

    do {
    // nonmove_loop:
        // PUSH_AF;
        // LD_hl(0xe3);
        *hl = CHAR_DASH;
        // LD_A_addr(wListMovesLineSpacing);
        // LD_C_A;
        // LD_B(0);
        // ADD_HL_BC;
        // POP_AF;
        hl += wram->wListMovesLineSpacing;
        // INC_A;
        // CP_A(NUM_MOVES);
        // IF_NZ goto nonmove_loop;
    } while(++b != NUM_MOVES);


// done:
    // RET;

}
