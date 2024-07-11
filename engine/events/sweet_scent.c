#include "../../constants.h"
#include "sweet_scent.h"
#include "overworld.h"
#include "bug_contest/contest.h"
#include "../overworld/events.h"
#include "../overworld/wildmons.h"
#include "../../home/queue_script.h"
#include "../../util/scripting.h"
#include "../../data/text/common.h"

static bool SweetScentFromMenu_SweetScent(script_s* s);

void SweetScentFromMenu(void){
    // LD_HL(mSweetScentFromMenu_SweetScent);
    // CALL(aQueueScript);
    QueueScript_Conv2(SweetScentFromMenu_SweetScent);
    // LD_A(0x1);
    // LD_addr_A(wFieldMoveSucceeded);
    wram->wFieldMoveSucceeded = TRUE;
    // RET;
}

static bool SweetScentFromMenu_SweetScent(script_s* s){
    SCRIPT_BEGIN
    reloadmappart
    special(UpdateTimePals)
    GetPartyNickname();
    writetext(UseSweetScentText)
    waitbutton
    SweetScentEncounter();
    iffalse_jump(SweetScentNothing)
    checkflag(ENGINE_BUG_CONTEST_TIMER)
    iftrue(BugCatchingContest)
    randomwildmon
    startbattle
    reloadmapafterbattle
    s_end

BugCatchingContest:
    sjump(BugCatchingContestBattleScript)
    SCRIPT_END
}

bool SweetScentNothing(script_s* s){
    SCRIPT_BEGIN
    writetext(SweetScentNothingText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}

void SweetScentEncounter(void){
    // FARCALL(aCanUseSweetScent);
    // IF_NC goto no_battle;
    if(CanUseSweetScent_Conv()) {
        // LD_HL(wStatusFlags2);
        // BIT_hl(STATUSFLAGS2_BUG_CONTEST_TIMER_F);
        // IF_NZ goto not_in_bug_contest;
        if(bit_test(wram->wStatusFlags2, STATUSFLAGS2_BUG_CONTEST_TIMER_F)) {
        // not_in_bug_contest:
            // FARCALL(aChooseWildEncounter_BugContest);
            ChooseWildEncounter_BugContest_Conv();
        // start_battle:
            // LD_A(0x1);
            // LD_addr_A(wScriptVar);
            wram->wScriptVar = 0x1;
            // RET;
            return;
        }
        else {
            // FARCALL(aGetMapEncounterRate);
            uint8_t b = GetMapEncounterRate_Conv();
            // LD_A_B;
            // AND_A_A;
            // IF_Z goto no_battle;
            // FARCALL(aChooseWildEncounter);
            // IF_NZ goto no_battle;
            if(b != 0 && ChooseWildEncounter_Conv()) {
            // start_battle:
                // LD_A(0x1);
                // LD_addr_A(wScriptVar);
                wram->wScriptVar = 0x1;
                // RET;
                return;
            }
            // goto start_battle;
        }
    }

// no_battle:
    // XOR_A_A;
    // LD_addr_A(wScriptVar);
    // LD_addr_A(wBattleType);
    // RET;
    wram->wScriptVar = FALSE;
    wram->wBattleType = 0;
    return;
}

const txt_cmd_s UseSweetScentText[] = {
    text_far(v_UseSweetScentText)
    text_end
};

const txt_cmd_s SweetScentNothingText[] = {
    text_far(v_SweetScentNothingText)
    text_end
};
