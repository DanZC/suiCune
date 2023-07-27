#include "../../constants.h"

const char * const NonTrainerCallerNames[] = {
// entries correspond to PHONECONTACT_* constants (see constants/trainer_constants.asm)
    [TRAINER_NONE] = "----------@",
    [PHONECONTACT_MOM] = "MOM:@",
    [PHONECONTACT_BIKESHOP] = "BIKE SHOP:@",
    [PHONECONTACT_BILL] = "BILL:@",
    [PHONECONTACT_ELM] = "PROF.ELM:@",
    [PHONECONTACT_BUENA] = "BUENA:<LF>   DISC JOCKEY@",
};

static_assert(lengthof(NonTrainerCallerNames) == NUM_NONTRAINER_PHONECONTACTS + 1, "");
