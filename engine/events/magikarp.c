#include "../../constants.h"
#include "../../charmap.h"
#include "magikarp.h"
#include "../pokemon/party_menu.h"
#include "../../home/compare.h"
#include "../../home/copy.h"
#include "../../home/print_text.h"
#include "../../home/text.h"
#include "../../data/events/magikarp_lengths.h"
#include "../../data/text/common.h"
#include "../../mobile/mobile_41.h"

// Returns 3 if you select a Magikarp that beats the previous record.
// Returns 2 if you select a Magikarp, but the current record is longer.
// Returns 1 if you press B in the Pokemon selection menu.
// Returns 0 if the Pokemon you select is not a Magikarp.
void CheckMagikarpLength(void){
static const txt_cmd_s MagikarpGuruMeasureText[] = {
    text_far(v_MagikarpGuruMeasureText)
    text_end
};

// Let's start by selecting a Magikarp.
    // FARCALL(aSelectMonFromParty);
    u8_flag_s res = SelectMonFromParty();
    // IF_C goto declined;
    if(res.flag) {
    // declined:
        // LD_A(MAGIKARPLENGTH_REFUSED);
        // LD_addr_A(wScriptVar);
        wram->wScriptVar = MAGIKARPLENGTH_REFUSED;
        // RET;
        return;
    }
    // LD_A_addr(wCurPartySpecies);
    // CP_A(MAGIKARP);
    // IF_NZ goto not_magikarp;
    if(wram->wCurPartySpecies != MAGIKARP) {
    // not_magikarp:
        // XOR_A_A;  // MAGIKARPLENGTH_NOT_MAGIKARP
        // LD_addr_A(wScriptVar);
        wram->wScriptVar = MAGIKARPLENGTH_NOT_MAGIKARP;
        // RET;
        return;
    }

// Now let's compute its length based on its DVs and ID.
    // LD_A_addr(wCurPartyMon);
    // LD_HL(wPartyMon1Species);
    // LD_BC(PARTYMON_STRUCT_LENGTH);
    // CALL(aAddNTimes);
    // PUSH_HL;
    // LD_BC(MON_DVS);
    // ADD_HL_BC;
    // LD_D_H;
    // LD_E_L;
    // POP_HL;
    struct PartyMon* mon = wram->wPartyMon + res.a;
    // LD_BC(MON_ID);
    // ADD_HL_BC;
    // LD_B_H;
    // LD_C_L;
    // CALL(aCalcMagikarpLength);
    CalcMagikarpLength(mon->mon.DVs, mon->mon.id);
    // CALL(aPrintMagikarpLength);
    PrintMagikarpLength();
    // FARCALL(aStubbedTrainerRankings_MagikarpLength);
    StubbedTrainerRankings_MagikarpLength();
    // LD_HL(mCheckMagikarpLength_MagikarpGuruMeasureText);
    // CALL(aPrintText);
    PrintText(MagikarpGuruMeasureText);

// Did we beat the record?
    // LD_HL(wMagikarpLength);
    // LD_DE(wBestMagikarpLengthFeet);
    uint16_t bestLength = (wram->wBestMagikarpLengthFeet << 8) | (wram->wBestMagikarpLengthInches);
    // LD_C(2);
    // CALL(aCompareBytes);
    // IF_NC goto not_long_enough;
    if(BigEndianToNative16(wram->wMagikarpLength) >= bestLength) {
    // NEW RECORD!!! Let's save that.
        // LD_HL(wMagikarpLength);
        // LD_DE(wBestMagikarpLengthFeet);
        // LD_A_hli;
        // LD_de_A;
        wram->wBestMagikarpLengthFeet = LOW(wram->wMagikarpLength);
        // INC_DE;
        // LD_A_hl;
        // LD_de_A;
        // INC_DE;
        wram->wBestMagikarpLengthInches = HIGH(wram->wMagikarpLength);
        // LD_A_addr(wCurPartyMon);
        // LD_HL(wPartyMonOTs);
        // CALL(aSkipNames);
        // CALL(aCopyBytes);
        CopyBytes(wram->wMagikarpRecordHoldersName, wram->wPartyMonOT[res.a], NAME_LENGTH);
        // LD_A(MAGIKARPLENGTH_BEAT_RECORD);
        // LD_addr_A(wScriptVar);
        wram->wScriptVar = MAGIKARPLENGTH_BEAT_RECORD;
        // RET;
        return;
    }

// not_long_enough:
    // LD_A(MAGIKARPLENGTH_TOO_SHORT);
    // LD_addr_A(wScriptVar);
    wram->wScriptVar = MAGIKARPLENGTH_TOO_SHORT;
    // RET;
    return;
}

void Magikarp_LoadFeetInchesChars(void){
    static const char feetinchchars[] = "gfx/font/feet_inches.png";
    // LD_HL(vTiles2 + LEN_2BPP_TILE * "′");  // $6e
    // LD_HL(vTiles2 + LEN_2BPP_TILE * CHAR_FEET);
    // LD_DE(mMagikarp_LoadFeetInchesChars_feetinchchars);
    // LD_BC((BANK(aMagikarp_LoadFeetInchesChars_feetinchchars) << 8) | 2);
    // CALL(aRequest2bpp);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles2 + LEN_2BPP_TILE * CHAR_FEET, feetinchchars, 0, 2);
    // RET;
}

void PrintMagikarpLength(void){
    // CALL(aMagikarp_LoadFeetInchesChars);
    Magikarp_LoadFeetInchesChars();
    uint8_t e = LOW(wram->wMagikarpLength);
    uint8_t d = HIGH(wram->wMagikarpLength);
    // LD_HL(wStringBuffer1);
    // LD_DE(wMagikarpLength);
    // LD_BC((PRINTNUM_LEFTALIGN | 1 << 8) | 2);
    // CALL(aPrintNum);
    uint8_t* hl = PrintNum(wram->wStringBuffer1, &e, PRINTNUM_LEFTALIGN | 1, 2);
    // LD_hl(0x6e);
    // INC_HL;
    *(hl++) = CHAR_FEET;
    // LD_DE(wMagikarpLength + 1);
    // LD_BC((PRINTNUM_LEFTALIGN | 1 << 8) | 2);
    // CALL(aPrintNum);
    hl = PrintNum(hl, &d, PRINTNUM_LEFTALIGN | 1, 2);
    // LD_hl(0x6f);
    // INC_HL;
    *(hl++) = CHAR_INCHES;
    // LD_hl(0x50);
    *hl = CHAR_TERM;
    // RET;
}

//  Intention: Return bc < de.
//  Reality: Return b < d.
static bool CalcMagikarpLength_BCLessThanDE(uint16_t bc, uint16_t de) {
    // LD_A_B;
    // CP_A_D;
    // RET_C ;
    // RET_NC ;  // whoops
    return HIGH(bc) < HIGH(de);
    // LD_A_C;
    // CP_A_E;
    // RET;
}

//  bc -= de
static uint16_t CalcMagikarpLength_BCMinusDE(uint16_t bc, uint16_t de) {
    // LD_A_C;
    // SUB_A_E;
    // LD_C_A;
    // LD_A_B;
    // SBC_A_D;
    // LD_B_A;
    // RET;
    return bc - de;
}

void CalcMagikarpLength(uint16_t de, uint16_t bc){
//  Return Magikarp's length (in feet and inches) at wMagikarpLength (big endian).
//
//  input:
//    de: wEnemyMonDVs
//    bc: wPlayerID

//  This function is poorly commented.

//  In short, it generates a value between 190 and 1786 using
//  a Magikarp's DVs and its trainer ID. This value is further
//  filtered in LoadEnemyMon to make longer Magikarp even rarer.

//  The value is generated from a lookup table.
//  The index is determined by the dv xored with the player's trainer id.

//  bc = rrc(dv[0]) ++ rrc(dv[1]) ^ rrc(id)

//  if bc < 10:    [wMagikarpLength] = c + 190
//  if bc ≥ $ff00: [wMagikarpLength] = c + 1370
//  else:          [wMagikarpLength] = z * 100 + (bc - x) / y

//  X, Y, and Z depend on the value of b as follows:

//  if b = 0:        x =   310,  y =   2,  z =  3
//  if b = 1:        x =   710,  y =   4,  z =  4
//  if b = 2-9:      x =  2710,  y =  20,  z =  5
//  if b = 10-29:    x =  7710,  y =  50,  z =  6
//  if b = 30-68:    x = 17710,  y = 100,  z =  7
//  if b = 69-126:   x = 32710,  y = 150,  z =  8
//  if b = 127-185:  x = 47710,  y = 150,  z =  9
//  if b = 186-224:  x = 57710,  y = 100,  z = 10
//  if b = 225-243:  x = 62710,  y =  50,  z = 11
//  if b = 244-251:  x = 64710,  y =  20,  z = 12
//  if b = 252-253:  x = 65210,  y =   5,  z = 13
//  if b = 254:      x = 65410,  y =   2,  z = 14

// bc = rrc(dv[0]) ++ rrc(dv[1]) ^ rrc(id)

// id
    // LD_H_B;
    // LD_L_C;
    // LD_A_hli;
    // LD_B_A;
    // LD_C_hl;
    uint16_t id = NativeToBigEndian16(bc);
    uint8_t id_hi = HIGH(id);
    uint8_t id_lo = LOW(id);
    // RRC_B;
    // RRC_C;
    uint8_t carry;
    id_hi = RotateRightCarry8(id_hi, &carry);
    id_lo = RotateRightCarry8(id_lo, &carry);

// dv
    // LD_A_de;
    uint16_t dv = NativeToBigEndian16(de);
    uint8_t dv_hi = HIGH(dv);
    uint8_t dv_lo = LOW(dv);
    // INC_DE;
    // RRCA;
    // RRCA;
    dv_hi = RotateRightC8(dv_hi);
    dv_hi = RotateRightC8(dv_hi);
    // XOR_A_B;
    // LD_B_A;
    id_hi = (dv_hi ^ id_hi);

    // LD_A_de;
    // RRCA;
    // RRCA;
    dv_lo = RotateRightC8(dv_lo);
    dv_lo = RotateRightC8(dv_lo);
    // XOR_A_C;
    // LD_C_A;
    id_lo = (dv_lo ^ id_lo);

// if bc < 10:
//     de = bc + 190
//     break

    // LD_A_B;
    // AND_A_A;
    // IF_NZ goto no;
    // LD_A_C;
    // CP_A(10);
    // IF_NC goto no;
    id = (id_hi << 8) | id_lo;
    if(id < 10) {

        // LD_HL(190);
        // ADD_HL_BC;
        // LD_D_H;
        // LD_E_L;
        dv = id + 190;
        // goto done;
    }

// no:
    // LD_HL(mMagikarpLengths);
    const struct WordByte* hl = MagikarpLengths;
    // LD_A(2);
    // LD_addr_A(wTempByteValue);
    uint8_t temp = 2;
    uint16_t de2;

    do {
    // read:
        // LD_A_hli;
        // LD_E_A;
        // LD_A_hli;
        // LD_D_A;
        // CALL(aCalcMagikarpLength_BCLessThanDE);
        // IF_NC goto next;
        if(!CalcMagikarpLength_BCLessThanDE(id, hl->word))
            continue;

    // c = (bc - de) / [hl]
        // CALL(aCalcMagikarpLength_BCMinusDE);
        // LD_A_B;
        // LDH_addr_A(hDividend + 0);
        // LD_A_C;
        // LDH_addr_A(hDividend + 1);
        // LD_A_hl;
        // LDH_addr_A(hDivisor);
        // LD_B(2);
        // CALL(aDivide);
        // LDH_A_addr(hQuotient + 3);
        // LD_C_A;
        uint8_t c = (uint8_t)(CalcMagikarpLength_BCMinusDE(id, hl->word) / hl->byte);

    // de = c + 100 × (2 + i)
        // XOR_A_A;
        // LDH_addr_A(hMultiplicand + 0);
        // LDH_addr_A(hMultiplicand + 1);
        // LD_A(100);
        // LDH_addr_A(hMultiplicand + 2);
        // LD_A_addr(wTempByteValue);
        // LDH_addr_A(hMultiplier);
        // CALL(aMultiply);
        // LD_B(0);
        // LDH_A_addr(hProduct + 3);
        // ADD_A_C;
        // LD_E_A;
        // LDH_A_addr(hProduct + 2);
        // ADC_A_B;
        // LD_D_A;
        // goto done;
        de2 = c + (100 * temp);
        goto done;


    // next:
        // INC_HL;  // align to next triplet
        // LD_A_addr(wTempByteValue);
        // INC_A;
        // LD_addr_A(wTempByteValue);
        // CP_A(16);
        // IF_C goto read;
    } while(hl++, ++temp < 16);

    // CALL(aCalcMagikarpLength_BCMinusDE);
    // LD_HL(1600);
    // ADD_HL_BC;
    // LD_D_H;
    // LD_E_L;
    de2 = CalcMagikarpLength_BCMinusDE(id, hl->word) + 1600;

done:
// convert from mm to feet and inches
// in = mm / 25.4
// ft = in / 12

// hl = de × 10
    // LD_H_D;
    // LD_L_E;
    // ADD_HL_HL;
    // ADD_HL_HL;
    // ADD_HL_DE;
    // ADD_HL_HL;
    uint16_t hl2 = de2 * 10;

// hl = hl / 254
    // LD_DE(-254);
    // LD_A(-1);

// div_254:
    // INC_A;
    // ADD_HL_DE;
    // IF_C goto div_254;
    hl2 /= 254;

// d, e = hl / 12, hl % 12
    // LD_D(0);

// mod_12:
    // CP_A(12);
    // IF_C goto ok;
    // SUB_A(12);
    // INC_D;
    // goto mod_12;

// ok:
    // LD_E_A;

    // LD_HL(wMagikarpLength);
    // LD_hl_D;  // ft
    // INC_HL;
    // LD_hl_E;  // in
    wram->wMagikarpLength = ((hl2 / 12) & 0xff) | (((hl2 % 12) & 0xff) << 8);
    // RET;

// INCLUDE "data/events/magikarp_lengths.asm"
}

void MagikarpHouseSign(void){
    // LD_A_addr(wBestMagikarpLengthFeet);
    // LD_addr_A(wMagikarpLength);
    // LD_A_addr(wBestMagikarpLengthInches);
    // LD_addr_A(wMagikarpLength + 1);
    wram->wMagikarpLength = (wram->wBestMagikarpLengthFeet) | (wram->wBestMagikarpLengthInches << 8);
    // CALL(aPrintMagikarpLength);
    PrintMagikarpLength();
    // LD_HL(mMagikarpHouseSign_KarpGuruRecordText);
    // CALL(aPrintText);
    PrintText((struct TextCmd[]) {
    // KarpGuruRecordText:
        text_far(v_KarpGuruRecordText)
        text_end
    });
    // RET;
}
