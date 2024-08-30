#include "../constants.h"
#include "soft_reset.h"
#include "../engine/menus/intro_menu.h"
#include "intro_jumptable.h"

// Control flow for intro sequence, title screen, and main menu doesn't play well with C's function/subroutine structure, 
// so we factor into a jumptable.

int gIntroJumptableIndex;

void Intro_SetJumptableIndex(int index) {
    gIntroJumptableIndex = index;
}

void Intro_Jumptable(void) {
    switch(gIntroJumptableIndex) {
        default:
        case INTRO_SOFT_RESET:
            SoftReset(RESET_TYPE_RESET);
            break;
        case INTRO_INIT:
            GameInit();
            break;
        case INTRO_INTRO_SEQUENCE:
            IntroSequence();
            break;
        case INTRO_TITLE:
            StartTitleScreen();
            break;
        case INTRO_CONTINUE:
            FinishContinueFunction();
            break;
        case INTRO_HARD_RESET:
            SoftReset(RESET_TYPE_INIT);
            break;
    }
}