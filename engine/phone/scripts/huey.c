#include "../../../constants.h"
#include "../../../util/scripting.h"
#include "generic_callee.h"
#include "generic_caller.h"
#include "reminders.h"
#include "hangups.h"
#include "huey.h"

bool HueyPhoneCalleeScript(script_s* s) {
    SCRIPT_BEGIN
    gettrainername(STRING_BUFFER_3, SAILOR, HUEY1)
    checkflag(ENGINE_HUEY_READY_FOR_REMATCH)
    iftrue(WantsBattle)
    scall(PhoneScript_AnswerPhone_Male)
    checkflag(ENGINE_HUEY_WEDNESDAY_NIGHT)
    iftrue(NotWednesday)
    readvar(VAR_WEEKDAY)
    ifnotequal(WEDNESDAY, NotWednesday)
    checktime(NITE)
    iftrue_jump(HueyWednesdayNight)
NotWednesday:
    special(RandomPhoneMon)
    sjump(HueyHangUpScript)
WantsBattle:
    getlandmarkname(STRING_BUFFER_5, LANDMARK_LIGHTHOUSE)
    sjump(HueyWantsBattleScript)
    SCRIPT_END
}
bool HueyPhoneCallerScript(script_s* s) {
    SCRIPT_BEGIN
    gettrainername(STRING_BUFFER_3, SAILOR, HUEY1)
    scall(PhoneScript_GreetPhone_Male)
    checkflag(ENGINE_HUEY_READY_FOR_REMATCH)
    iftrue(Flavor)
    checkflag(ENGINE_HUEY_WEDNESDAY_NIGHT)
    iftrue(Flavor)
    scall(PhoneScript_Random3)
    ifequal_jump(0, HueyWantsBattle)
    ifequal_jump(1, HueyWantsBattle)
Flavor:
    sjump(PhoneScript_MonFlavorText)
    SCRIPT_END
}
bool HueyWednesdayNight(script_s* s) {
    SCRIPT_BEGIN
    setflag(ENGINE_HUEY_WEDNESDAY_NIGHT)
    SCRIPT_FALLTHROUGH(HueyWantsBattle)
}
bool HueyWantsBattle(script_s* s) {
    SCRIPT_BEGIN
    getlandmarkname(STRING_BUFFER_5, LANDMARK_LIGHTHOUSE)
    setflag(ENGINE_HUEY_READY_FOR_REMATCH)
    sjump(PhoneScript_WantsToBattle_Male)
    SCRIPT_END
}
