#include "../../../constants.h"
#include "../../../util/scripting.h"
#include "generic_caller.h"
#include "hangups.h"
#include "../../../data/phone/text/liz_caller.h"

bool LizGossipRandomScript(script_s* s) {
    SCRIPT_BEGIN
    srandom(10)
    ifequal(0, RuinsOfAlph)
    ifequal(1, Falkner)
    ifequal(2, Earl)
    ifequal(3, SurfPikachu)
    ifequal(4, MooMooMilk)
    ifequal(5, Salon)
    ifequal(6, Whitney)
    ifequal(7, BugCatchingContest)
    ifequal(8, BeautifulTrainer)
    ifequal(9, Forgot)
RuinsOfAlph:
    writetext(LizRuinsOfAlphGossipText)
    promptbutton
    sjump(PhoneScript_HangUpText_Female)
Falkner:
    writetext(LizFalknerGossipText)
    promptbutton
    sjump(PhoneScript_HangUpText_Female)
Earl:
    writetext(LizEarlGossipText)
    promptbutton
    sjump(PhoneScript_HangUpText_Female)
SurfPikachu:
    writetext(LizSurfPikachuGossipText)
    promptbutton
    sjump(PhoneScript_HangUpText_Female)
MooMooMilk:
    writetext(LizMooMooMilkGossipText)
    promptbutton
    sjump(PhoneScript_HangUpText_Female)
Salon:
    writetext(LizSalonGossipText)
    promptbutton
    sjump(PhoneScript_HangUpText_Female)
Whitney:
    writetext(LizWhitneyGossipText)
    promptbutton
    sjump(PhoneScript_HangUpText_Female)
BugCatchingContest:
    writetext(LizBugCatchingContestGossipText)
    promptbutton
    sjump(PhoneScript_HangUpText_Female)
BeautifulTrainer:
    writetext(LizBeautifulTrainerGossipText)
    promptbutton
    sjump(PhoneScript_HangUpText_Female)
Forgot:
    writetext(LizForgotGossipText)
    promptbutton
    sjump(PhoneScript_HangUpText_Female)
    SCRIPT_END
}
