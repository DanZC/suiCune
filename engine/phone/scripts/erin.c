#include "../../../constants.h"
#include "../../../util/scripting.h"
#include "generic_callee.h"
#include "generic_caller.h"
#include "reminders.h"
#include "hangups.h"
#include "erin.h"

bool ErinPhoneCalleeScript(script_s* s) {
    SCRIPT_BEGIN
    gettrainername(STRING_BUFFER_3, PICNICKER, ERIN1)
    checkflag(ENGINE_ERIN_READY_FOR_REMATCH)
    iftrue(WantsBattle)
    scall(PhoneScript_AnswerPhone_Female)
    checkflag(ENGINE_ERIN_SATURDAY_NIGHT)
    iftrue(NotSaturday)
    readvar(VAR_WEEKDAY)
    ifnotequal(SATURDAY, NotSaturday)
    checktime(NITE)
    iftrue_jump(ErinSaturdayNight)
NotSaturday:
    sjump(ErinWorkingHardScript)
WantsBattle:
    getlandmarkname(STRING_BUFFER_5, LANDMARK_ROUTE_46)
    sjump(ErinComeBattleScript)
    SCRIPT_END
}
bool ErinPhoneCallerScript(script_s* s) {
    SCRIPT_BEGIN
    gettrainername(STRING_BUFFER_3, PICNICKER, ERIN1)
    scall(PhoneScript_GreetPhone_Female)
    checkflag(ENGINE_ERIN_READY_FOR_REMATCH)
    iftrue(GenericCall)
    checkflag(ENGINE_ERIN_SATURDAY_NIGHT)
    iftrue(GenericCall)
    scall(PhoneScript_Random3)
    ifequal_jump(0, ErinWantsBattle)
    ifequal_jump(1, ErinWantsBattle)
GenericCall:
    sjump(Phone_GenericCall_Female)
    SCRIPT_END
}
bool ErinSaturdayNight(script_s* s) {
    SCRIPT_BEGIN
    setflag(ENGINE_ERIN_SATURDAY_NIGHT)
    SCRIPT_FALLTHROUGH(ErinWantsBattle)
}
bool ErinWantsBattle(script_s* s) {
    SCRIPT_BEGIN
    getlandmarkname(STRING_BUFFER_5, LANDMARK_ROUTE_46)
    setflag(ENGINE_ERIN_READY_FOR_REMATCH)
    sjump(PhoneScript_WantsToBattle_Female)
    SCRIPT_END
}
