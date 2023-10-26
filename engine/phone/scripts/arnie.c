#include "../../../constants.h"
#include "../../overworld/scripting.h"
#include "../../../util/scripting.h"
#include "generic_callee.h"
#include "generic_caller.h"
#include "reminders.h"
#include "hangups.h"
#include "reminders_2.h"
#include "arnie.h"

bool ArniePhoneCalleeScript(script_s* s) {
    SCRIPT_BEGIN
    gettrainername(STRING_BUFFER_3, BUG_CATCHER, ARNIE1)
    checkflag(ENGINE_ARNIE_READY_FOR_REMATCH)
    iftrue(WantsBattle)
    scall(PhoneScript_AnswerPhone_Male)
    checkflag(ENGINE_ARNIE_TUESDAY_MORNING)
    iftrue(NotTuesday)
    readvar(VAR_WEEKDAY)
    ifnotequal(TUESDAY, NotTuesday)
    checktime(MORN)
    iftrue_jump(ArnieTuesdayMorning)
NotTuesday:
    checkflag(ENGINE_YANMA_SWARM)
    iftrue(AlreadySwarming)
    sjump(ArnieHangUpScript)
WantsBattle:
    getlandmarkname(STRING_BUFFER_5, LANDMARK_ROUTE_35)
    sjump(ArnieReminderScript)
AlreadySwarming:
    getlandmarkname(STRING_BUFFER_5, LANDMARK_ROUTE_35)
    sjump(ArnieHurryScript)
    SCRIPT_END
}
bool ArniePhoneCallerScript(script_s* s) {
    SCRIPT_BEGIN
    gettrainername(STRING_BUFFER_3, BUG_CATCHER, ARNIE1)
    scall(PhoneScript_GreetPhone_Male)
    checkflag(ENGINE_ARNIE_READY_FOR_REMATCH)
    iftrue(Swarm)
    checkflag(ENGINE_ARNIE_TUESDAY_MORNING)
    iftrue(Swarm)
    scall(PhoneScript_Random2)
    ifequal_jump(0, ArnieWantsBattle)
Swarm:
    scall(PhoneScript_Random5)
    ifequal_jump(0, ArnieYanmaSwarm)
    scall(PhoneScript_Random3)
    ifequal_jump(0, ArnieFoundRare)
    sjump(Phone_GenericCall_Male)
    SCRIPT_END
}
bool ArnieTuesdayMorning(script_s* s) {
    SCRIPT_BEGIN
    setflag(ENGINE_ARNIE_TUESDAY_MORNING)
    SCRIPT_FALLTHROUGH(ArnieWantsBattle)
}
bool ArnieWantsBattle(script_s* s) {
    SCRIPT_BEGIN
    getlandmarkname(STRING_BUFFER_5, LANDMARK_ROUTE_35)
    setflag(ENGINE_ARNIE_READY_FOR_REMATCH)
    sjump(PhoneScript_WantsToBattle_Male)
    SCRIPT_END
}
bool ArnieYanmaSwarm(script_s* s) {
    SCRIPT_BEGIN
    checkflag(ENGINE_YANMA_SWARM)
    iftrue_jump(ArnieYanmaAlreadySwarming)
    setflag(ENGINE_YANMA_SWARM)
    getmonname(STRING_BUFFER_4, YANMA)
    // swarm(SWARM_YANMA, ROUTE_35)
    getlandmarkname(STRING_BUFFER_5, LANDMARK_ROUTE_35)
    sjump(ArnieSwarmScript)
    SCRIPT_END
}
bool ArnieFoundRare(script_s* s) {
    SCRIPT_BEGIN
    sjump(Phone_CheckIfUnseenRare_Male)
    SCRIPT_END
}
bool ArnieYanmaAlreadySwarming(script_s* s) {
    SCRIPT_BEGIN
    sjump(Phone_GenericCall_Male)
    SCRIPT_END
}
