#include "../../../constants.h"
#include "contest_2.h"
#include "../../../home/flag.h"
#include "../../../home/random.h"
#include "../../../data/events/bug_contest_flags.h"

void SelectRandomBugContestContestants(void){
//  Select five random people to participate in the current contest.

//  First we have to make sure that any old data is cleared away.
    // LD_C(NUM_BUG_CONTESTANTS);
    // LD_HL(mBugCatchingContestantEventFlagTable);

    for(uint32_t i = 0; i < NUM_BUG_CONTESTANTS; ++i) {
    // loop1:
        // PUSH_BC;
        // PUSH_HL;
        // LD_E_hl;
        // INC_HL;
        // LD_D_hl;
        // LD_B(RESET_FLAG);
        // CALL(aEventFlagAction);
        EventFlagAction_Conv2(BugCatchingContestantEventFlagTable[i], RESET_FLAG);
        // POP_HL;
        // INC_HL;
        // INC_HL;
        // POP_BC;
        // DEC_C;
        // IF_NZ goto loop1;
    }

//  Now that that's out of the way, we can get on to the good stuff.
    // LD_C(5);
    uint8_t c = 5;

    do {
    // loop2:
        // PUSH_BC;

        uint8_t a;
        uint16_t flag;
        do {
            do {
            // next:
            //  Choose a flag at uniform random to be set.
                // CALL(aRandom);
                a = Random();
                // CP_A(0xff / NUM_BUG_CONTESTANTS * NUM_BUG_CONTESTANTS);
                // IF_NC goto next;
            } while(a >= 0xff / NUM_BUG_CONTESTANTS * NUM_BUG_CONTESTANTS);
            // LD_C(0xff / NUM_BUG_CONTESTANTS);
            // CALL(aSimpleDivide);
            // LD_E_B;
            // LD_D(0);
            // LD_HL(mBugCatchingContestantEventFlagTable);
            // ADD_HL_DE;
            // ADD_HL_DE;
            // LD_E_hl;
            // INC_HL;
            // LD_D_hl;
            // PUSH_DE;
            flag = BugCatchingContestantEventFlagTable[a % (0xff / NUM_BUG_CONTESTANTS)];
        //  If we've already set it, it doesn't count.
            // LD_B(CHECK_FLAG);
            // CALL(aEventFlagAction);
            // POP_DE;
            // LD_A_C;
            // AND_A_A;
            // IF_NZ goto next;
        } while(EventFlagAction_Conv2(flag, CHECK_FLAG) != 0);
    //  Set the flag.  This will cause that sprite to not be visible in the contest.
        // LD_B(SET_FLAG);
        // CALL(aEventFlagAction);
        EventFlagAction_Conv2(flag, SET_FLAG);
        // POP_BC;
    //  Check if we're done.  If so, return.  Otherwise, choose the next victim.
        // DEC_C;
        // IF_NZ goto loop2;
    } while(--c != 0);
    // RET;
}

uint8_t CheckBugContestContestantFlag(uint8_t a){
//  Checks the flag of the Bug Catching Contestant whose index is loaded in a.

    // LD_HL(mBugCatchingContestantEventFlagTable);
    // LD_E_A;
    // LD_D(0);
    // ADD_HL_DE;
    // ADD_HL_DE;
    // LD_E_hl;
    // INC_HL;
    // LD_D_hl;
    // LD_B(CHECK_FLAG);
    // CALL(aEventFlagAction);
    // RET;

// INCLUDE "data/events/bug_contest_flags.asm"
    return EventFlagAction_Conv2(BugCatchingContestantEventFlagTable[a], CHECK_FLAG);
}

void ContestDropOffMons(void){
    // LD_HL(wPartyMon1HP);
    // LD_A_hli;
    // OR_A_hl;
    // IF_Z goto fainted;
    if(wram->wPartyMon[0].HP != 0) {
    //  Mask the rest of your party by setting the count to 1...
        // LD_HL(wPartyCount);
        // LD_A(1);
        // LD_hli_A;
        wram->wPartyCount = 1;
        // INC_HL;
    //  ... backing up the second mon index somewhere...
        // LD_A_hl;
        // LD_addr_A(wBugContestSecondPartySpecies);
        wram->wBugContestSecondPartySpecies = wram->wPartySpecies[1];
    //  ... and replacing it with the terminator byte
        // LD_hl(-1);
        wram->wPartySpecies[1] = (species_t)-1;
        // XOR_A_A;
        // LD_addr_A(wScriptVar);
        wram->wScriptVar = 0x0;
        // RET;
        return;
    }

// fainted:
    // LD_A(0x1);
    // LD_addr_A(wScriptVar);
    wram->wScriptVar = 0x1;
    // RET;
}

void ContestReturnMons(void){
//  Restore the species of the second mon.
    // LD_HL(wPartySpecies + 1);
    species_t* hl = wram->wPartySpecies + 1;
    // LD_A_addr(wBugContestSecondPartySpecies);
    // LD_hl_A;
    *hl = wram->wBugContestSecondPartySpecies;
//  Restore the party count, which must be recomputed.
    // LD_B(1);
    uint8_t b = 1;

    while(*(hl++) != (species_t)-1) {
    // loop:
        // LD_A_hli;
        // CP_A(-1);
        // IF_Z goto done;
        // INC_B;
        b++;
        // goto loop;
    }


// done:
    // LD_A_B;
    // LD_addr_A(wPartyCount);
    wram->wPartyCount = b;
    // RET;
}
