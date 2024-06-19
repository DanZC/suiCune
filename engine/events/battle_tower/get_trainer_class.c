#include "../../../constants.h"
#include "get_trainer_class.h"
#include "../../../data/trainers/gendered_trainers.h"

static uint8_t GetMobileOTTrainerClass_GetMobileOTTrainerClass(const uint8_t* de, const uint8_t* hl) {
    // LD_A_hli;
    // XOR_A_hl;
    // LD_C_A;
    uint8_t c = hl[0] ^ hl[1];
    hl++;
    // IF_Z goto skip_male_trainers;
    if(c != 0) {
        // SRL_C;
        // SRL_C;
        c >>= 2;

        do {
        // male_trainer_loop:
            // SRL_C;
            c >>= 1;
            // LD_A_C;
            // CP_A(MaleTrainers.End - MaleTrainers - 1);
            // IF_NC goto male_trainer_loop;
        } while(c > MaleTrainers_Size);
        // INC_C;
        c++;
    }

// skip_male_trainers:
    // LD_A_de;
    // CP_A(FEMALE);
    // LD_HL(mMaleTrainers);
    const uint8_t* trainers = MaleTrainers;
    // IF_NZ goto finished;

    if(*de == FEMALE) {
        // LD_HL(mFemaleTrainers);
        trainers = FemaleTrainers;
        // LD_A_C;
        // AND_A_A;
        // IF_Z goto finished;
        if(c != 0) {
            do {
            // female_trainer_loop:
                // SRL_C;
                c >>= 1;
                // LD_A_C;
                // CP_A(FemaleTrainers.End - FemaleTrainers - 1);
                // IF_NC goto female_trainer_loop;
            } while(c > FemaleTrainers_Size);
            // INC_C;
            c++;
        }
    }

// finished:
    // LD_B(0x0);
    // ADD_HL_BC;
    // LD_A_hl;
    // RET;
    return trainers[c];
}

uint8_t GetMobileOTTrainerClass(const uint8_t* de, const uint8_t* bc){
//  //  mobile function
    // LD_H_B;
    // LD_L_C;
    // CALL(aGetMobileOTTrainerClass_GetMobileOTTrainerClass);
    // LD_C_A;
    // RET;

// INCLUDE "data/trainers/gendered_trainers.asm"
    return GetMobileOTTrainerClass_GetMobileOTTrainerClass(de, bc);
}
