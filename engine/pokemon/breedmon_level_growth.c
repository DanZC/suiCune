#include "../../constants.h"
#include "breedmon_level_growth.h"
#include "experience.h"
#include "../../home/copy.h"

u8_pair_s GetBreedMon1LevelGrowth(void){
    // LD_HL(wBreedMon1);
    // LD_DE(wTempMon);
    // LD_BC(BOXMON_STRUCT_LENGTH);
    // CALL(aCopyBytes);
    CopyBytes_Conv2(&wram->wTempMon.mon, &wram->wBreedMon1, BOXMON_STRUCT_LENGTH);
    // CALLFAR(aCalcLevel);
    uint8_t d = CalcLevel_Conv(&wram->wTempMon);
    // LD_A_addr(wBreedMon1Level);
    // LD_B_A;
    // LD_A_D;
    // LD_E_A;
    // SUB_A_B;
    // LD_D_A;
    // RET;
    return u8_pair(wram->wBreedMon1.level, d - wram->wBreedMon1.level);
}

u8_pair_s GetBreedMon2LevelGrowth(void){
    // LD_HL(wBreedMon2);
    // LD_DE(wTempMon);
    // LD_BC(BOXMON_STRUCT_LENGTH);
    // CALL(aCopyBytes);
    CopyBytes_Conv2(&wram->wTempMon.mon, &wram->wBreedMon2, BOXMON_STRUCT_LENGTH);
    // CALLFAR(aCalcLevel);
    uint8_t d = CalcLevel_Conv(&wram->wTempMon);
    // LD_A_addr(wBreedMon2Level);
    // LD_B_A;
    // LD_A_D;
    // LD_E_A;
    // SUB_A_B;
    // LD_D_A;
    // RET;
    return u8_pair(wram->wBreedMon2.level, d - wram->wBreedMon2.level);
}
