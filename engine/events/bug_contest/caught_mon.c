#include "../../../constants.h"
#include "caught_mon.h"
#include "display_stats.h"
#include "../../../home/menu.h"
#include "../../../home/text.h"
#include "../../../home/names.h"
#include "../../../home/pokemon.h"
#include "../../../home/copy.h"
#include "../../pokemon/move_mon.h"
#include "../../../data/text/common.h"

static void BugContest_SetCaughtContestMon_generatestats(void) {
    // LD_A_addr(wTempEnemyMonSpecies);
    // LD_addr_A(wCurSpecies);
    // LD_addr_A(wCurPartySpecies);
    // CALL(aGetBaseData);
    GetBaseData_Conv2(wram->wTempEnemyMonSpecies);
    // XOR_A_A;
    // LD_BC(PARTYMON_STRUCT_LENGTH);
    // LD_HL(wContestMon);
    // CALL(aByteFill);
    ByteFill(&wram->wContestMon, sizeof(wram->wContestMon), 0);
    // XOR_A_A;
    // LD_addr_A(wMonType);
    // LD_HL(wContestMon);
    // JP(mGeneratePartyMonStats);
    GeneratePartyMonStats_Conv(&wram->wContestMon, wram->wTempEnemyMonSpecies, wram->wCurPartyLevel, PARTYMON, wram->wBattleMode);
}

void BugContest_SetCaughtContestMon(void){
    PEEK("");
    static const txt_cmd_s ContestCaughtMonText[] = {
        text_far(v_ContestCaughtMonText)
        text_end
    };
    // LD_A_addr(wContestMon);
    // AND_A_A;
    // IF_Z goto firstcatch;
    if(wram->wContestMon.mon.species != 0) {
        // LD_addr_A(wNamedObjectIndex);
        // FARCALL(aDisplayAlreadyCaughtText);
        DisplayAlreadyCaughtText(wram->wContestMon.mon.species);
        // FARCALL(aDisplayCaughtContestMonStats);
        DisplayCaughtContestMonStats();
        // LD_BC((14 << 8) | 7);
        // CALL(aPlaceYesNoBox);
        bool yes = PlaceYesNoBox(14, 7);
        // RET_C ;
        if(!yes)
            return;
    }

// firstcatch:
    // CALL(aBugContest_SetCaughtContestMon_generatestats);
    BugContest_SetCaughtContestMon_generatestats();
    // LD_A_addr(wTempEnemyMonSpecies);
    // LD_addr_A(wNamedObjectIndex);
    // CALL(aGetPokemonName);
    GetPokemonName(wram->wTempEnemyMonSpecies);
    // LD_HL(mBugContest_SetCaughtContestMon_ContestCaughtMonText);
    // CALL(aPrintText);
    PrintText_Conv2(ContestCaughtMonText);
    // RET;
    return;
}
