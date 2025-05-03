#include "../../constants.h"
#include "read_trainer_attributes.h"
#include "../../home/copy.h"
#include "../../home/names.h"
#include "../../data/trainers/attributes.h"

uint8_t* GetTrainerClassName(uint8_t c){
    // LD_HL(wRivalName);
    // LD_A_C;
    // CP_A(RIVAL1);
    // IF_Z goto rival;
    if(c == RIVAL1) {
    // rival:
        // LD_DE(wStringBuffer1);
        // PUSH_DE;
        // LD_BC(NAME_LENGTH);
        // CALL(aCopyBytes);
        // POP_DE;
        // RET;
        CopyBytes(wram->wStringBuffer1, wram->wRivalName, NAME_LENGTH);
        return wram->wStringBuffer1;
    }

    // LD_addr_A(wCurSpecies);
    // LD_A(TRAINER_NAME);
    // LD_addr_A(wNamedObjectType);
    // CALL(aGetName);
    // LD_DE(wStringBuffer1);
    // RET;
    return GetName(TRAINER_NAME, c);
}

void GetOTName(uint8_t c){
    // LD_HL(wOTPlayerName);
    uint8_t* hl;
    // LD_A_addr(wLinkMode);
    // AND_A_A;
    // IF_NZ goto ok;
    if(wram->wLinkMode != LINK_NULL) {
        hl = wram->wOTPlayerName;
    }
    else if(c == RIVAL1) {
        // LD_HL(wRivalName);
        hl = wram->wRivalName;
        // LD_A_C;
        // CP_A(RIVAL1);
        // IF_Z goto ok;
    }
    else {
        // LD_addr_A(wCurSpecies);
        // LD_A(TRAINER_NAME);
        // LD_addr_A(wNamedObjectType);
        // CALL(aGetName);
        // LD_HL(wStringBuffer1);
        hl = GetName(TRAINER_NAME, c);
    }


// ok:
    // LD_BC(TRAINER_CLASS_NAME_LENGTH);
    // LD_DE(wOTClassName);
    // PUSH_DE;
    // CALL(aCopyBytes);
    CopyBytes(wram->wOTClassName, hl, TRAINER_CLASS_NAME_LENGTH);
    // POP_DE;
    // RET;

}

void GetTrainerAttributes(uint8_t tclass){
    // LD_A_addr(wTrainerClass);
    // LD_C_A;
    // CALL(aGetOTName);
    GetOTName(tclass);
    // LD_A_addr(wTrainerClass);
    // DEC_A;
    // LD_HL(mTrainerClassAttributes + TRNATTR_ITEM1);
    // LD_BC(NUM_TRAINER_ATTRIBUTES);
    // CALL(aAddNTimes);
    const struct TrainerClassAttr* const hl = &TrainerClassAttributes[tclass];
    // LD_DE(wEnemyTrainerItem1);
    // LD_A_hli;
    // LD_de_A;
    wram->wEnemyTrainerItem1 = hl->items[0];
    // INC_DE;
    // LD_A_hli;
    // LD_de_A;
    wram->wEnemyTrainerItem2 = hl->items[1];
    // LD_A_hl;
    // LD_addr_A(wEnemyTrainerBaseReward);
    wram->wEnemyTrainerBaseReward = hl->baseMoney;
    // RET;
}
