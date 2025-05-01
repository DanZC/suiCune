#include "../../../constants.h"
#include "contest.h"
#include "../std_scripts.h"
#include "../../overworld/time.h"
#include "../../../util/scripting.h"
#include "../../../data/text/common.h"

void GiveParkBalls(void){
    // XOR_A_A;
    // LD_addr_A(wContestMon);
    wram->wContestMon.mon.species = 0;
    // LD_A(BUG_CONTEST_BALLS);
    // LD_addr_A(wParkBallsRemaining);
    wram->wParkBallsRemaining = BUG_CONTEST_BALLS;
    // FARCALL(aStartBugContestTimer);
    StartBugContestTimer();
    // RET;

}

bool BugCatchingContestBattleScript(script_s* s){
    SCRIPT_BEGIN
    loadvar(VAR_BATTLETYPE, BATTLETYPE_CONTEST)
    randomwildmon
    startbattle
    reloadmapafterbattle
    readmem(wram_ptr(wParkBallsRemaining))
    iffalse_jump(BugCatchingContestOutOfBallsScript)
    s_end
    SCRIPT_END
}

bool BugCatchingContestOverScript(script_s* s){
    SCRIPT_BEGIN
    playsound(SFX_ELEVATOR_END)
    opentext
    writetext(BugCatchingContestTimeUpText)
    waitbutton
    sjump(BugCatchingContestReturnToGateScript)
    SCRIPT_END
}

bool BugCatchingContestOutOfBallsScript(script_s* s){
    SCRIPT_BEGIN
    playsound(SFX_ELEVATOR_END)
    opentext
    writetext(BugCatchingContestIsOverText)
    waitbutton

    SCRIPT_FALLTHROUGH(BugCatchingContestReturnToGateScript);
}

bool BugCatchingContestReturnToGateScript(script_s* s){
    SCRIPT_BEGIN
    closetext
    jumpstd(BugContestResultsWarpScript)
    SCRIPT_END
}

const txt_cmd_s BugCatchingContestTimeUpText[] = {
    text_far(v_BugCatchingContestTimeUpText)
    text_end
};

const txt_cmd_s BugCatchingContestIsOverText[] = {
    text_far(v_BugCatchingContestIsOverText)
    text_end
};
