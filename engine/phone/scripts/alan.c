#include "../../../constants.h"
#include "../../overworld/scripting.h"
#include "../../../util/scripting.h"
#include "generic_callee.h"
#include "generic_caller.h"
#include "reminders.h"
#include "hangups.h"
#include "hangups_2.h"
#include "alan.h"

bool AlanPhoneCalleeScript(script_s* s) {
    SCRIPT_BEGIN
    gettrainername(STRING_BUFFER_3, SCHOOLBOY, ALAN1)
    checkflag(ENGINE_ALAN_READY_FOR_REMATCH)
    iftrue(WantsBattle)
    scall(PhoneScript_AnswerPhone_Male)
    checkflag(ENGINE_ALAN_WEDNESDAY_AFTERNOON)
    iftrue(NotWednesday)
    checkflag(ENGINE_ALAN_HAS_FIRE_STONE)
    iftrue(FireStone)
    readvar(VAR_WEEKDAY)
    ifnotequal(WEDNESDAY, NotWednesday)
    checktime(DAY)
    iftrue_jump(AlanWednesdayDay)
NotWednesday:
    sjump(AlanHangUpScript)
WantsBattle:
    getlandmarkname(STRING_BUFFER_5, LANDMARK_ROUTE_36)
    sjump(AlanReminderScript)
FireStone:
    getlandmarkname(STRING_BUFFER_5, LANDMARK_ROUTE_36)
    sjump(AlanComePickUpScript)
    SCRIPT_END
}
bool AlanPhoneCallerScript(script_s* s) {
    SCRIPT_BEGIN
    gettrainername(STRING_BUFFER_3, SCHOOLBOY, ALAN1)
    scall(PhoneScript_GreetPhone_Male)
    checkflag(ENGINE_ALAN_READY_FOR_REMATCH)
    iftrue(Generic)
    checkflag(ENGINE_ALAN_WEDNESDAY_AFTERNOON)
    iftrue(Generic)
    checkflag(ENGINE_ALAN_HAS_FIRE_STONE)
    iftrue(Generic)
    scall(PhoneScript_Random3)
    ifequal_jump(0, AlanWantsBattle)
    checkevent(EVENT_ALAN_GAVE_FIRE_STONE)
    iftrue(FireStone)
    scall(PhoneScript_Random2)
    ifequal_jump(0, AlanHasFireStone)
FireStone:
    scall(PhoneScript_Random11)
    ifequal_jump(0, AlanHasFireStone)
Generic:
    sjump(Phone_GenericCall_Male)
    SCRIPT_END
}
bool AlanWednesdayDay(script_s* s) {
    SCRIPT_BEGIN
    setflag(ENGINE_ALAN_WEDNESDAY_AFTERNOON)
    SCRIPT_FALLTHROUGH(AlanWantsBattle)
}
bool AlanWantsBattle(script_s* s) {
    SCRIPT_BEGIN
    getlandmarkname(STRING_BUFFER_5, LANDMARK_ROUTE_36)
    setflag(ENGINE_ALAN_READY_FOR_REMATCH)
    sjump(PhoneScript_WantsToBattle_Male)
    SCRIPT_END
}
bool AlanHasFireStone(script_s* s) {
    SCRIPT_BEGIN
    setflag(ENGINE_ALAN_HAS_FIRE_STONE)
    getlandmarkname(STRING_BUFFER_5, LANDMARK_ROUTE_36)
    sjump(PhoneScript_FoundItem_Male)
    SCRIPT_END
}
