#include "../../constants.h"
#include "types.h"
#include "../../data/types/names.h"
#include "../../home/text.h"
#include "../../home/pokemon.h"
#include "../../data/moves/moves.h"

void PrintMonTypes(void){
//  Print one or both types of [wCurSpecies]
//  on the stats screen at hl.

    PUSH_HL;
    CALL(aGetBaseData);
    POP_HL;

    PUSH_HL;
    LD_A_addr(wBaseType1);
    CALL(aPrintMonTypes_Print);

// Single-typed monsters really
// have two of the same type.
    LD_A_addr(wBaseType1);
    LD_B_A;
    LD_A_addr(wBaseType2);
    CP_A_B;
    POP_HL;
    IF_Z goto hide_type_2;

    LD_BC(SCREEN_WIDTH);
    ADD_HL_BC;


Print:
    LD_B_A;
    JR(mPrintType);


hide_type_2:
// Erase any type name that was here before.
// Seems to be pointless in localized versions.
    LD_A(0x7f);
    LD_BC(SCREEN_WIDTH - 3);
    ADD_HL_BC;
    LD_hl_A;
    INC_BC;
    ADD_HL_BC;
    LD_BC(NAME_LENGTH_JAPANESE - 1);
    JP(mByteFill);

}

//  Print one or both types of [wCurSpecies]
//  on the stats screen at hl.
void PrintMonTypes_Conv(uint8_t* hl){
    // PUSH_HL;
    // CALL(aGetBaseData);
    // POP_HL;
    GetBaseData_Conv2(wram->wCurSpecies);

    // PUSH_HL;
    // LD_A_addr(wBaseType1);
    // CALL(aPrintMonTypes_Print);
    PrintType_Conv(hl, wram->wBaseType1);

// Single-typed monsters really
// have two of the same type.
    // LD_A_addr(wBaseType1);
    // LD_B_A;
    // LD_A_addr(wBaseType2);
    // CP_A_B;
    // POP_HL;
    // IF_Z goto hide_type_2;
    if(wram->wBaseType1 != wram->wBaseType2) {
        // LD_BC(SCREEN_WIDTH);
        // ADD_HL_BC;

    // Print:
        // LD_B_A;
        // JR(mPrintType);
        PrintType_Conv(hl + SCREEN_WIDTH, wram->wBaseType2);
    }


// hide_type_2:
// Erase any type name that was here before.
// Seems to be pointless in localized versions.
    // LD_A(0x7f);
    // LD_BC(SCREEN_WIDTH - 3);
    // ADD_HL_BC;
    // LD_hl_A;
    // INC_BC;
    // ADD_HL_BC;
    // LD_BC(NAME_LENGTH_JAPANESE - 1);
    // JP(mByteFill);
}

void PrintMoveType(void){
//  Print the type of move b at hl.

    PUSH_HL;
    LD_A_B;
    DEC_A;
    LD_BC(MOVE_LENGTH);
    LD_HL(mMoves);
    CALL(aAddNTimes);
    LD_DE(wStringBuffer1);
    LD_A(BANK(aMoves));
    CALL(aFarCopyBytes);
    LD_A_addr(wStringBuffer1 + MOVE_TYPE);
    POP_HL;

    LD_B_A;

    return PrintType();
}

//  Print the type of move b at hl.
void PrintMoveType_Conv(uint8_t* hl, move_t b){
    // PUSH_HL;
    // LD_A_B;
    // DEC_A;
    // LD_BC(MOVE_LENGTH);
    // LD_HL(mMoves);
    // CALL(aAddNTimes);
    // LD_DE(wStringBuffer1);
    // LD_A(BANK(aMoves));
    // CALL(aFarCopyBytes);
    // LD_A_addr(wStringBuffer1 + MOVE_TYPE);
    // POP_HL;

    // LD_B_A;

    return PrintType_Conv(hl, Moves[b - 1].type);
}

void PrintType(void){
//  Print type b at hl.

    LD_A_B;

    PUSH_HL;
    ADD_A_A;
    LD_HL(mTypeNames);
    LD_E_A;
    LD_D(0);
    ADD_HL_DE;
    LD_A_hli;
    LD_E_A;
    LD_D_hl;
    POP_HL;

    JP(mPlaceString);

}

//  Print type b at hl.
void PrintType_Conv(uint8_t* hl, uint8_t b){
    // LD_A_B;
    // PUSH_HL;
    // ADD_A_A;
    // LD_HL(mTypeNames);
    // LD_E_A;
    // LD_D(0);
    // ADD_HL_DE;
    // LD_A_hli;
    // LD_E_A;
    // LD_D_hl;
    // POP_HL;
    if(b >= TYPES_END) {
        PlaceStringSimple(U82C(TypeNames[CURSE_TYPE]), hl);
        return;
    }

    // JP(mPlaceString);
    PlaceStringSimple(U82C(TypeNames[b]), hl);
}

void GetTypeName(void){
//  Copy the name of type [wNamedObjectIndex] to wStringBuffer1.

    LD_A_addr(wNamedObjectIndex);
    LD_HL(mTypeNames);
    LD_E_A;
    LD_D(0);
    ADD_HL_DE;
    ADD_HL_DE;
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    LD_DE(wStringBuffer1);
    LD_BC(MOVE_NAME_LENGTH);
    JP(mCopyBytes);

// INCLUDE "data/types/names.asm"

}

//  Copy the name of type [wNamedObjectIndex] to wStringBuffer1.
void GetTypeName_Conv(uint8_t idx){
    // LD_A_addr(wNamedObjectIndex);
    // LD_HL(mTypeNames);
    // LD_E_A;
    // LD_D(0);
    // ADD_HL_DE;
    // ADD_HL_DE;
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // LD_DE(wStringBuffer1);
    // LD_BC(MOVE_NAME_LENGTH);
    // JP(mCopyBytes);
    Utf8ToCrystalBuffer(wram->wStringBuffer1, MOVE_NAME_LENGTH, TypeNames[idx]);

// INCLUDE "data/types/names.asm"

}
