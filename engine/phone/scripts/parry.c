#include "../../../constants.h"
#include "../../../util/scripting.h"
#include "generic_callee.h"
#include "generic_caller.h"
#include "reminders.h"
#include "hangups.h"
#include "parry.h"

bool ParryPhoneCalleeScript(script_s* s) {
    SCRIPT_BEGIN
    gettrainername(STRING_BUFFER_3, HIKER, PARRY1)
    checkflag(ENGINE_PARRY_READY_FOR_REMATCH)
    iftrue(WantsBattle)
    scall(PhoneScript_AnswerPhone_Male)
    checkflag(ENGINE_PARRY_FRIDAY_AFTERNOON)
    iftrue(WantsRematch)
    readvar(VAR_WEEKDAY)
    ifnotequal(FRIDAY, WantsRematch)
    checktime(DAY)
    iftrue_jump(ParryFridayDay)
WantsRematch:
    sjump(ParryBattleWithMeScript)
WantsBattle:
    getlandmarkname(STRING_BUFFER_5, LANDMARK_ROUTE_45)
    sjump(ParryHaventYouGottenToScript)
    SCRIPT_END
}
bool ParryPhoneCallerScript(script_s* s) {
    SCRIPT_BEGIN
    gettrainername(STRING_BUFFER_3, HIKER, PARRY1)
    scall(PhoneScript_GreetPhone_Male)
    checkflag(ENGINE_PARRY_READY_FOR_REMATCH)
    iftrue(GenericCall)
    checkflag(ENGINE_PARRY_FRIDAY_AFTERNOON)
    iftrue(GenericCall)
    scall(PhoneScript_Random2)
    ifequal_jump(0, ParryWantsBattle)
    ifequal_jump(1, ParryWantsBattle)
GenericCall:
    sjump(Phone_GenericCall_Male)
    SCRIPT_END
}
bool ParryFridayDay(script_s* s) {
    SCRIPT_BEGIN
    setflag(ENGINE_PARRY_FRIDAY_AFTERNOON)
    SCRIPT_FALLTHROUGH(ParryWantsBattle)
}
bool ParryWantsBattle(script_s* s) {
    SCRIPT_BEGIN
    getlandmarkname(STRING_BUFFER_5, LANDMARK_ROUTE_45)
    setflag(ENGINE_PARRY_READY_FOR_REMATCH)
    sjump(PhoneScript_WantsToBattle_Male)
    SCRIPT_END
}
