#include "../../constants.h"
#include "print_item_description.h"
#include "tmhm.h"
#include "../pokemon/print_move_description.h"
#include "../../home/text.h"
#include "../../data/items/descriptions.h"

//  Print the description for item [wCurSpecies] at de.
void PrintItemDescription(tile_t* de, item_t item){
    // LD_A_addr(wCurSpecies);
    // CP_A(TM01);
    // IF_C goto not_a_tm;
    if(item >= TM01) {
        // LD_addr_A(wCurItem);
        // PUSH_DE;
        // FARCALL(aGetTMHMItemMove);
        move_t move = GetTMHMItemMove_Conv(item);
        // POP_HL;
        // LD_A_addr(wTempTMHM);
        // LD_addr_A(wCurSpecies);
        // PREDEF(pPrintMoveDescription);
        PrintMoveDescription_Conv(de, move);
        // RET;
        return;
    }
    else {
    // not_a_tm:
        // PUSH_DE;
        // LD_HL(mItemDescriptions);
        // LD_A_addr(wCurSpecies);
        // DEC_A;
        // LD_C_A;
        // LD_B(0);
        // ADD_HL_BC;
        // ADD_HL_BC;
        // LD_E_hl;
        // INC_HL;
        // LD_D_hl;
        // POP_HL;
        // JP(mPlaceString);
        PlaceStringSimple(U82C(ItemDescriptions[item]), de);
    }
// INCLUDE "data/items/descriptions.asm"

}
