#include "../../../constants.h"
#include "../../../util/scripting.h"
#include "generic_callee.h"
#include "generic_caller.h"
#include "reminders.h"
#include "hangups.h"
#include "reena.h"

bool ReenaPhoneCalleeScript(script_s* s) {
    SCRIPT_BEGIN
    gettrainername(STRING_BUFFER_3, COOLTRAINERF, REENA1)
    checkflag(ENGINE_REENA_READY_FOR_REMATCH)
    iftrue(WantsBattle)
    scall(PhoneScript_AnswerPhone_Female)
    checkflag(ENGINE_REENA_SUNDAY_MORNING)
    iftrue(NotSunday)
    readvar(VAR_WEEKDAY)
    ifnotequal(SUNDAY, NotSunday)
    checktime(MORN)
    iftrue_jump(ReenaSundayMorning)
NotSunday:
    sjump(ReenaForwardScript)
WantsBattle:
    getlandmarkname(STRING_BUFFER_5, LANDMARK_ROUTE_27)
    sjump(ReenaHurryScript)
    SCRIPT_END
}
bool ReenaPhoneCallerScript(script_s* s) {
    SCRIPT_BEGIN
    gettrainername(STRING_BUFFER_3, COOLTRAINERF, REENA1)
    scall(PhoneScript_GreetPhone_Female)
    checkflag(ENGINE_REENA_READY_FOR_REMATCH)
    iftrue(Generic)
    checkflag(ENGINE_REENA_SUNDAY_MORNING)
    iftrue(Generic)
    scall(PhoneScript_Random2)
    ifequal_jump(0, ReenaWantsBattle)
Generic:
    sjump(Phone_GenericCall_Female)
    SCRIPT_END
}
bool ReenaSundayMorning(script_s* s) {
    SCRIPT_BEGIN
    setflag(ENGINE_REENA_SUNDAY_MORNING)
    SCRIPT_FALLTHROUGH(ReenaWantsBattle)
}
bool ReenaWantsBattle(script_s* s) {
    SCRIPT_BEGIN
    getlandmarkname(STRING_BUFFER_5, LANDMARK_ROUTE_27)
    setflag(ENGINE_REENA_READY_FOR_REMATCH)
    sjump(PhoneScript_WantsToBattle_Female)
    SCRIPT_END
}
