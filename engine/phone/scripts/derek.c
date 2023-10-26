#include "../../../constants.h"
#include "../../../util/scripting.h"
#include "generic_callee.h"
#include "generic_caller.h"
#include "reminders.h"
#include "hangups.h"
#include "hangups_2.h"
#include "derek.h"

bool DerekPhoneCalleeScript(script_s* s) {
    SCRIPT_BEGIN
    gettrainername(STRING_BUFFER_3, POKEFANM, DEREK1)
    scall(PhoneScript_AnswerPhone_Male)
    checkflag(ENGINE_DEREK_HAS_NUGGET)
    iftrue(Nugget)
    scall(PhoneScript_Random2)
    ifequal(0, NoContest)
    checkflag(ENGINE_DAILY_BUG_CONTEST)
    iftrue(NoContest)
    readvar(VAR_WEEKDAY)
    ifequal(TUESDAY, ContestToday)
    ifequal(THURSDAY, ContestToday)
    ifequal(SATURDAY, ContestToday)
NoContest:
    sjump(DerekHangUpScript)
ContestToday:
    sjump(PhoneScript_BugCatchingContest)
Nugget:
    getlandmarkname(STRING_BUFFER_5, LANDMARK_ROUTE_39)
    sjump(DerekComePickUpScript)
    SCRIPT_END
}
bool DerekPhoneCallerScript(script_s* s) {
    SCRIPT_BEGIN
    gettrainername(STRING_BUFFER_3, POKEFANM, DEREK1)
    scall(PhoneScript_GreetPhone_Male)
    scall(PhoneScript_Random2)
    ifequal(0, NoContest)
    checkflag(ENGINE_DAILY_BUG_CONTEST)
    iftrue(NoContest)
    readvar(VAR_WEEKDAY)
    ifequal(TUESDAY, ContestToday)
    ifequal(THURSDAY, ContestToday)
    ifequal(SATURDAY, ContestToday)
NoContest:
    scall(PhoneScript_Random4)
    ifequal(0, Nugget)
    sjump(Phone_GenericCall_Male)
ContestToday:
    sjump(PhoneScript_BugCatchingContest)
Nugget:
    setflag(ENGINE_DEREK_HAS_NUGGET)
    getlandmarkname(STRING_BUFFER_5, LANDMARK_ROUTE_39)
    sjump(PhoneScript_FoundItem_Male)
    SCRIPT_END
}
