#include "../../constants.h"
#include "level_up_happiness.h"
#include "../../home/map.h"
#include "../events/happiness_egg.h"

void LevelUpHappinessMod(void){
    // LD_A_addr(wCurPartyMon);
    // LD_HL(wPartyMon1CaughtLocation);
    // CALL(aGetPartyLocation);
    // LD_A_hl;
    // AND_A(CAUGHT_LOCATION_MASK);
    // LD_D_A;
    uint8_t d = gPokemon.partyMon[wram->wCurPartyMon].mon.caughtGenderLocation & CAUGHT_LOCATION_MASK;
    // LD_A_addr(wMapGroup);
    // LD_B_A;
    // LD_A_addr(wMapNumber);
    // LD_C_A;
    // CALL(aGetWorldMapLocation);
    // CP_A_D;
    // LD_C(HAPPINESS_GAINLEVEL);
    // IF_NZ goto ok;
    // LD_C(HAPPINESS_GAINLEVELATHOME);
    uint8_t c = (d == GetWorldMapLocation(gCurMapData.mapGroup, gCurMapData.mapNumber))
        ? HAPPINESS_GAINLEVELATHOME
        : HAPPINESS_GAINLEVEL;

// ok:
    // CALLFAR(aChangeHappiness);
    ChangeHappiness(c);
    // RET;
}
