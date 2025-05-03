#include "../../constants.h"
#include "read_trainer_dvs.h"
#include "../../data/trainers/dvs.h"

//  Return the DVs of wOtherTrainerClass in bc
uint16_t GetTrainerDVs(uint8_t tclass) {
    // PUSH_HL;
    // LD_A_addr(wOtherTrainerClass);
    // DEC_A;
    // LD_C_A;
    // LD_B(0);

    // LD_HL(mTrainerClassDVs);
    // ADD_HL_BC;
    // ADD_HL_BC;
    const struct DVSet* set = &TrainerClassDVs[tclass - 1];

    // LD_A_hli;
    // LD_B_A;
    // LD_C_hl;

    // POP_HL;
    // RET;
    return ((set->atk << 12) | (set->def << 8) | (set->spc << 4) | set->spd);
}
