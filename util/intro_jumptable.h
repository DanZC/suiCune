#pragma once

enum {
    INTRO_INIT,
    INTRO_INTRO_SEQUENCE,
    INTRO_TITLE,
    INTRO_MAIN_MENU,
    INTRO_CONTINUE,
    INTRO_OPTIONS,
    INTRO_RESET_CLOCK,
    INTRO_DELETE_SAVE,
    INTRO_MOBILE,
    INTRO_SOFT_RESET,
    INTRO_HARD_RESET,
};

void Intro_SetJumptableIndex(int index);
void Intro_Jumptable(void);