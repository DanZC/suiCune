#include "../../constants.h"
#include "checktime.h"

u8_flag_s CheckTime(void) {
    static const uint8_t TimeOfDayTable[] = {
        MORN_F, MORN,
        DAY_F, DAY,
        NITE_F, NITE,
        NITE_F, NITE
    };

    // LD_A_addr(wTimeOfDay);
    // LD_HL(mCheckTime_TimeOfDayTable);
    // LD_DE(2);
    // CALL(aIsInArray);
    for(uint8_t i = 0; i < lengthof(TimeOfDayTable); i += 2) {
        if(TimeOfDayTable[i] == wram->wTimeOfDay) {
            // INC_HL;
            // LD_C_hl;
            // RET_C ;
            return u8_flag(TimeOfDayTable[i+1], true);
        }
    }

    // XOR_A_A;
    // LD_C_A;
    // RET;
    return u8_flag(0, false);
}
