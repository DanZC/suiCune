#include "../../../constants.h"
#include "../../../util/scripting.h"
#include "generic_callee.h"
#include "generic_caller.h"
#include "reminders.h"
#include "hangups.h"
#include "hangups_2.h"
#include "vance.h"

bool VancePhoneCalleeScript(script_s* s) {
    SCRIPT_BEGIN
    gettrainername(STRING_BUFFER_3, BIRD_KEEPER, VANCE1)
    checkflag(ENGINE_VANCE_READY_FOR_REMATCH)
    iftrue(WantsBattle)
    scall(PhoneScript_AnswerPhone_Male)
    checkflag(ENGINE_VANCE_WEDNESDAY_NIGHT)
    iftrue(NotWednesday)
    readvar(VAR_WEEKDAY)
    ifnotequal(WEDNESDAY, NotWednesday)
    checktime(NITE)
    iftrue_jump(VanceWednesdayNight)
NotWednesday:
    sjump(VanceLookingForwardScript)
WantsBattle:
    getlandmarkname(STRING_BUFFER_5, LANDMARK_ROUTE_44)
    sjump(VanceHurryHurryScript)
    SCRIPT_END
}
bool VancePhoneCallerScript(script_s* s) {
    SCRIPT_BEGIN
    gettrainername(STRING_BUFFER_3, BIRD_KEEPER, VANCE1)
    scall(PhoneScript_GreetPhone_Male)
    checkflag(ENGINE_VANCE_READY_FOR_REMATCH)
    iftrue(WantsBattle)
    checkflag(ENGINE_VANCE_WEDNESDAY_NIGHT)
    iftrue(WantsBattle)
    scall(PhoneScript_Random3)
    ifequal_jump(0, VanceWantsRematch)
    ifequal_jump(1, VanceWantsRematch)
WantsBattle:
    sjump(Phone_GenericCall_Male)
    SCRIPT_END
}
bool VanceWednesdayNight(script_s* s) {
    SCRIPT_BEGIN
    setflag(ENGINE_VANCE_WEDNESDAY_NIGHT)
    SCRIPT_FALLTHROUGH(VanceWantsRematch)
}
bool VanceWantsRematch(script_s* s) {
    SCRIPT_BEGIN
    getlandmarkname(STRING_BUFFER_5, LANDMARK_ROUTE_44)
    setflag(ENGINE_VANCE_READY_FOR_REMATCH)
    sjump(PhoneScript_WantsToBattle_Male)
    SCRIPT_END
}
