#include "../../../constants.h"
#include "../../../util/scripting.h"
#include "generic_callee.h"
#include "generic_caller.h"
#include "reminders.h"
#include "hangups.h"
#include "joey.h"

bool JoeyPhoneCalleeScript(script_s* s) {
    SCRIPT_BEGIN
    gettrainername(STRING_BUFFER_3, YOUNGSTER, JOEY1)
    checkflag(ENGINE_JOEY_READY_FOR_REMATCH)
    iftrue(WantsBattle)
    scall(PhoneScript_AnswerPhone_Male)
    checkflag(ENGINE_JOEY_MONDAY_AFTERNOON)
    iftrue(NotMonday)
    readvar(VAR_WEEKDAY)
    ifnotequal(MONDAY, NotMonday)
    checktime(DAY)
    iftrue_jump(JoeyMondayAfternoon)
NotMonday:
    special(RandomPhoneMon)
    sjump(JoeyHangUpScript)
WantsBattle:
    getlandmarkname(STRING_BUFFER_5, LANDMARK_ROUTE_30)
    sjump(JoeyReminderScript)
    SCRIPT_END
}
bool JoeyPhoneCallerScript(script_s* s) {
    SCRIPT_BEGIN
    gettrainername(STRING_BUFFER_3, YOUNGSTER, JOEY1)
    scall(PhoneScript_GreetPhone_Male)
    checkflag(ENGINE_JOEY_READY_FOR_REMATCH)
    iftrue(Generic)
    checkflag(ENGINE_JOEY_MONDAY_AFTERNOON)
    iftrue(Generic)
    scall(PhoneScript_Random3)
    ifequal_jump(0, JoeyWantsBattle)
    ifequal_jump(1, JoeyWantsBattle)
Generic:
    sjump(Phone_GenericCall_Male)
    SCRIPT_END
}
bool JoeyMondayAfternoon(script_s* s) {
    SCRIPT_BEGIN
    setflag(ENGINE_JOEY_MONDAY_AFTERNOON)
    SCRIPT_FALLTHROUGH(JoeyWantsBattle)
}
bool JoeyWantsBattle(script_s* s) {
    SCRIPT_BEGIN
    getlandmarkname(STRING_BUFFER_5, LANDMARK_ROUTE_30)
    setflag(ENGINE_JOEY_READY_FOR_REMATCH)
    sjump(PhoneScript_WantsToBattle_Male)
    SCRIPT_END
}
