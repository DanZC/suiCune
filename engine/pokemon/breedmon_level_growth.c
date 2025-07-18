#include "../../constants.h"
#include "breedmon_level_growth.h"
#include "experience.h"
#include "../../home/copy.h"

u8_pair_s GetBreedMon1LevelGrowth(void){
    // LD_HL(wBreedMon1);
    // LD_DE(wTempMon);
    // LD_BC(BOXMON_STRUCT_LENGTH);
    // CALL(aCopyBytes);
    CopyBytes(&wram->wTempMon.mon, &gPokemon.breedMon1, BOXMON_STRUCT_LENGTH);
    // CALLFAR(aCalcLevel);
    uint8_t d = CalcLevel(&wram->wTempMon);
    // LD_A_addr(wBreedMon1Level);
    // LD_B_A;
    // LD_A_D;
    // LD_E_A;
    // SUB_A_B;
    // LD_D_A;
    // RET;
    return u8_pair(gPokemon.breedMon1.level, d - gPokemon.breedMon1.level);
}

u8_pair_s GetBreedMon2LevelGrowth(void){
    // LD_HL(wBreedMon2);
    // LD_DE(wTempMon);
    // LD_BC(BOXMON_STRUCT_LENGTH);
    // CALL(aCopyBytes);
    CopyBytes(&wram->wTempMon.mon, &gPokemon.breedMon2, BOXMON_STRUCT_LENGTH);
    // CALLFAR(aCalcLevel);
    uint8_t d = CalcLevel(&wram->wTempMon);
    // LD_A_addr(wBreedMon2Level);
    // LD_B_A;
    // LD_A_D;
    // LD_E_A;
    // SUB_A_B;
    // LD_D_A;
    // RET;
    return u8_pair(gPokemon.breedMon2.level, d - gPokemon.breedMon2.level);
}
