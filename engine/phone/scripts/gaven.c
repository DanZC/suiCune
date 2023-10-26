#include "../../../constants.h"
#include "../../../util/scripting.h"
#include "generic_callee.h"
#include "generic_caller.h"
#include "reminders.h"
#include "hangups.h"
#include "gaven.h"

bool GavenPhoneCalleeScript(script_s* s) {
    SCRIPT_BEGIN
    gettrainername(STRING_BUFFER_3, COOLTRAINERM, GAVEN3)
    checkflag(ENGINE_GAVEN_READY_FOR_REMATCH)
    iftrue(WantsBattle)
    scall(PhoneScript_AnswerPhone_Male)
    checkflag(ENGINE_GAVEN_THURSDAY_MORNING)
    iftrue(NotThursday)
    readvar(VAR_WEEKDAY)
    ifnotequal(THURSDAY, NotThursday)
    checktime(MORN)
    iftrue_jump(GavenThursdayMorningScript)
NotThursday:
    sjump(GavenHangUpNotThursdayScript)
WantsBattle:
    getlandmarkname(STRING_BUFFER_5, LANDMARK_ROUTE_26)
    sjump(GavenReminderScript)
    SCRIPT_END
}
bool GavenPhoneCallerScript(script_s* s) {
    SCRIPT_BEGIN
    gettrainername(STRING_BUFFER_3, COOLTRAINERM, GAVEN3)
    scall(PhoneScript_GreetPhone_Male)
    checkflag(ENGINE_GAVEN_READY_FOR_REMATCH)
    iftrue(WaitingForBattle)
    checkflag(ENGINE_GAVEN_THURSDAY_MORNING)
    iftrue(WaitingForBattle)
    scall(PhoneScript_Random2)
    ifequal_jump(0, GavenWantsRematch)
WaitingForBattle:
    scall(PhoneScript_Random3)
    ifequal_jump(0, GavenFoundRare)
    sjump(Phone_GenericCall_Male)
    SCRIPT_END
}
bool GavenThursdayMorningScript(script_s* s) {
    SCRIPT_BEGIN
    setflag(ENGINE_GAVEN_THURSDAY_MORNING)
    SCRIPT_FALLTHROUGH(GavenWantsRematch)
}
bool GavenWantsRematch(script_s* s) {
    SCRIPT_BEGIN
    getlandmarkname(STRING_BUFFER_5, LANDMARK_ROUTE_26)
    setflag(ENGINE_GAVEN_READY_FOR_REMATCH)
    sjump(PhoneScript_WantsToBattle_Male)
    SCRIPT_END
}
bool GavenFoundRare(script_s* s) {
    SCRIPT_BEGIN
    sjump(Phone_CheckIfUnseenRare_Male)
    SCRIPT_END
}
