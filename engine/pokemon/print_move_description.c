#include "../../constants.h"
#include "print_move_description.h"
#include "../../home/text.h"
#include "../../data/moves/descriptions.h"

void PrintMoveDescription(tile_t* hl, move_t move){
    // PUSH_HL;
    // LD_HL(mMoveDescriptions);
    // LD_A_addr(wCurSpecies);
    // DEC_A;
    // LD_C_A;
    // LD_B(0);
    // ADD_HL_BC;
    // ADD_HL_BC;
    // LD_A_hli;
    // LD_E_A;
    // LD_D_hl;
    // POP_HL;
    // JP(mPlaceString);
    PlaceStringSimple(U82C(MoveDescriptions[move]), hl);
// INCLUDE "data/moves/descriptions.asm"

}
