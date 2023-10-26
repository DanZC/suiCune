#include "../../../constants.h"
#include "../../../util/scripting.h"
#include "generic_callee.h"
#include "generic_caller.h"
#include "reminders.h"
#include "hangups.h"
#include "reminders_2.h"
#include "ralph.h"

bool RalphPhoneCalleeScript(script_s* s) {
    SCRIPT_BEGIN
    gettrainername(STRING_BUFFER_3, FISHER, RALPH1)
    checkflag(ENGINE_RALPH_READY_FOR_REMATCH)
    iftrue(Rematch)
    scall(PhoneScript_AnswerPhone_Male)
    checkflag(ENGINE_RALPH_WEDNESDAY_MORNING)
    iftrue(CheckSwarm)
    readvar(VAR_WEEKDAY)
    ifnotequal(WEDNESDAY, CheckSwarm)
    checktime(MORN)
    iftrue_jump(Ralph_WednesdayMorning)
CheckSwarm:
    checkflag(ENGINE_FISH_SWARM)
    iftrue(ReportSwarm)
    sjump(RalphNoItemScript)
Rematch:
    getlandmarkname(STRING_BUFFER_5, LANDMARK_ROUTE_32)
    sjump(RalphReminderScript)
ReportSwarm:
    getlandmarkname(STRING_BUFFER_5, LANDMARK_ROUTE_32)
    sjump(RalphHurryScript)
    SCRIPT_END
}
bool RalphPhoneCallerScript(script_s* s) {
    SCRIPT_BEGIN
    gettrainername(STRING_BUFFER_3, FISHER, RALPH1)
    scall(PhoneScript_GreetPhone_Male)
    checkflag(ENGINE_FLYPOINT_GOLDENROD)
    iffalse(CheckSwarm)
    checkflag(ENGINE_RALPH_READY_FOR_REMATCH)
    iftrue(CheckSwarm)
    checkflag(ENGINE_RALPH_WEDNESDAY_MORNING)
    iftrue(CheckSwarm)
    scall(PhoneScript_Random2)
    ifequal_jump(0, Ralph_FightMe)
CheckSwarm:
    scall(PhoneScript_Random5)
    ifequal_jump(0, Ralph_SetUpSwarm)
    sjump(Phone_GenericCall_Male)
    SCRIPT_END
}
bool Ralph_WednesdayMorning(script_s* s) {
    SCRIPT_BEGIN
    setflag(ENGINE_RALPH_WEDNESDAY_MORNING)
    SCRIPT_FALLTHROUGH(Ralph_FightMe)
}
bool Ralph_FightMe(script_s* s) {
    SCRIPT_BEGIN
    getlandmarkname(STRING_BUFFER_5, LANDMARK_ROUTE_32)
    setflag(ENGINE_RALPH_READY_FOR_REMATCH)
    sjump(PhoneScript_WantsToBattle_Male)
    SCRIPT_END
}
bool Ralph_SetUpSwarm(script_s* s) {
    SCRIPT_BEGIN
    checkflag(ENGINE_FISH_SWARM)
    iftrue(Generic)
    setflag(ENGINE_FISH_SWARM)
    getmonname(STRING_BUFFER_4, QWILFISH)
    getlandmarkname(STRING_BUFFER_5, LANDMARK_ROUTE_32)
    setval(FISHSWARM_QWILFISH)
    special(ActivateFishingSwarm)
    sjump(RalphItemScript)
Generic:
    sjump(Phone_GenericCall_Male)
    SCRIPT_END
}
