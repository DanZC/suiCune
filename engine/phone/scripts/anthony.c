#include "../../../constants.h"
#include "../../overworld/scripting.h"
#include "../../../util/scripting.h"
#include "generic_callee.h"
#include "generic_caller.h"
#include "reminders.h"
#include "hangups.h"
#include "reminders_2.h"
#include "anthony.h"

bool AnthonyPhoneCalleeScript(script_s* s) {
    SCRIPT_BEGIN
    gettrainername(STRING_BUFFER_3, HIKER, ANTHONY2)
    checkflag(ENGINE_ANTHONY_READY_FOR_REMATCH)
    iftrue(WantsBattle)
    scall(PhoneScript_AnswerPhone_Male)
    checkflag(ENGINE_ANTHONY_FRIDAY_NIGHT)
    iftrue(NotFriday)
    readvar(VAR_WEEKDAY)
    ifnotequal(FRIDAY, NotFriday)
    checktime(NITE)
    iftrue_jump(AnthonyFridayNight)
NotFriday:
    checkflag(ENGINE_DUNSPARCE_SWARM)
    iftrue(AlreadySwarming)
    sjump(AnthonyHangUpScript)
WantsBattle:
    getlandmarkname(STRING_BUFFER_5, LANDMARK_ROUTE_33)
    sjump(AnthonyReminderScript)
AlreadySwarming:
    getlandmarkname(STRING_BUFFER_5, LANDMARK_ROUTE_33)
    sjump(AnthonyHurryScript)
    SCRIPT_END
}
bool AnthonyPhoneCallerScript(script_s* s) {
    SCRIPT_BEGIN
    gettrainername(STRING_BUFFER_3, HIKER, ANTHONY2)
    scall(PhoneScript_GreetPhone_Male)
    checkflag(ENGINE_FLYPOINT_GOLDENROD)
    iffalse(TriesSwarm)
    checkflag(ENGINE_ANTHONY_READY_FOR_REMATCH)
    iftrue(TriesSwarm)
    checkflag(ENGINE_ANTHONY_FRIDAY_NIGHT)
    iftrue(TriesSwarm)
    scall(PhoneScript_Random2)
    ifequal_jump(0, AnthonyWantsBattle)
TriesSwarm:
    scall(PhoneScript_Random5)
    ifequal_jump(0, AnthonyTriesDunsparceSwarm)
    sjump(Phone_GenericCall_Male)
    SCRIPT_END
}
bool AnthonyFridayNight(script_s* s) {
    SCRIPT_BEGIN
    setflag(ENGINE_ANTHONY_FRIDAY_NIGHT)
    SCRIPT_FALLTHROUGH(AnthonyWantsBattle)
}
bool AnthonyWantsBattle(script_s* s) {
    SCRIPT_BEGIN
    getlandmarkname(STRING_BUFFER_5, LANDMARK_ROUTE_33)
    setflag(ENGINE_ANTHONY_READY_FOR_REMATCH)
    sjump(PhoneScript_WantsToBattle_Male)
    SCRIPT_END
}
bool AnthonyTriesDunsparceSwarm(script_s* s) {
    SCRIPT_BEGIN
    checkflag(ENGINE_DUNSPARCE_SWARM)
    iftrue(Generic)
    setflag(ENGINE_DUNSPARCE_SWARM)
    getmonname(STRING_BUFFER_4, DUNSPARCE)
    // swarm(SWARM_DUNSPARCE, DARK_CAVE_VIOLET_ENTRANCE)
    getlandmarkname(STRING_BUFFER_5, LANDMARK_DARK_CAVE)
    sjump(AnthonySwarmScript)
Generic:
    sjump(Phone_GenericCall_Male)
    SCRIPT_END
}
