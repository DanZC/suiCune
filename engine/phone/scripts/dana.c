#include "../../../constants.h"
#include "../../../util/scripting.h"
#include "generic_callee.h"
#include "generic_caller.h"
#include "reminders.h"
#include "hangups.h"
#include "hangups_2.h"
#include "dana.h"

bool DanaPhoneCalleeScript(script_s* s) {
    SCRIPT_BEGIN
    gettrainername(STRING_BUFFER_3, LASS, DANA1)
    checkflag(ENGINE_DANA_READY_FOR_REMATCH)
    iftrue(WantsBattle)
    scall(PhoneScript_AnswerPhone_Female)
    checkflag(ENGINE_DANA_THURSDAY_NIGHT)
    iftrue(NotThursday)
    checkflag(ENGINE_DANA_HAS_THUNDERSTONE)
    iftrue(HasThunderstone)
    readvar(VAR_WEEKDAY)
    ifnotequal(THURSDAY, NotThursday)
    checktime(NITE)
    iftrue_jump(DanaThursdayNight)
NotThursday:
    sjump(DanaHangUpScript)
WantsBattle:
    getlandmarkname(STRING_BUFFER_5, LANDMARK_ROUTE_38)
    sjump(DanaReminderScript)
HasThunderstone:
    getlandmarkname(STRING_BUFFER_5, LANDMARK_ROUTE_38)
    sjump(DanaComePickUpScript)
    SCRIPT_END
}
bool DanaPhoneCallerScript(script_s* s) {
    SCRIPT_BEGIN
    gettrainername(STRING_BUFFER_3, LASS, DANA1)
    scall(PhoneScript_GreetPhone_Female)
    checkflag(ENGINE_DANA_READY_FOR_REMATCH)
    iftrue(Generic)
    checkflag(ENGINE_DANA_THURSDAY_NIGHT)
    iftrue(Generic)
    checkflag(ENGINE_DANA_HAS_THUNDERSTONE)
    iftrue(Generic)
    scall(PhoneScript_Random3)
    ifequal_jump(0, DanaWantsBattle)
    checkevent(EVENT_DANA_GAVE_THUNDERSTONE)
    iftrue(Thunderstone)
    scall(PhoneScript_Random2)
    ifequal_jump(0, DanaHasThunderstone)
Thunderstone:
    scall(PhoneScript_Random11)
    ifequal_jump(0, DanaHasThunderstone)
Generic:
    scall(PhoneScript_Random3)
    ifequal_jump(0, DanaFoundRare)
    sjump(Phone_GenericCall_Female)
    SCRIPT_END
}
bool DanaThursdayNight(script_s* s) {
    SCRIPT_BEGIN
    setflag(ENGINE_DANA_THURSDAY_NIGHT)
    SCRIPT_FALLTHROUGH(DanaWantsBattle)
}
bool DanaWantsBattle(script_s* s) {
    SCRIPT_BEGIN
    getlandmarkname(STRING_BUFFER_5, LANDMARK_ROUTE_38)
    setflag(ENGINE_DANA_READY_FOR_REMATCH)
    sjump(PhoneScript_WantsToBattle_Female)
    SCRIPT_END
}
bool DanaFoundRare(script_s* s) {
    SCRIPT_BEGIN
    sjump(Phone_CheckIfUnseenRare_Female)
    SCRIPT_END
}
bool DanaHasThunderstone(script_s* s) {
    SCRIPT_BEGIN
    setflag(ENGINE_DANA_HAS_THUNDERSTONE)
    getlandmarkname(STRING_BUFFER_5, LANDMARK_ROUTE_38)
    sjump(PhoneScript_FoundItem_Female)
    SCRIPT_END
}
