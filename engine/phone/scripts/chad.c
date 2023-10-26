#include "../../../constants.h"
#include "../../../util/scripting.h"
#include "generic_callee.h"
#include "generic_caller.h"
#include "reminders.h"
#include "hangups.h"
#include "chad_gossip.h"
#include "chad.h"

bool ChadPhoneCalleeScript(script_s* s) {
    SCRIPT_BEGIN
    gettrainername(STRING_BUFFER_3, SCHOOLBOY, CHAD1)
    checkflag(ENGINE_CHAD_READY_FOR_REMATCH)
    iftrue(WantsBattle)
    scall(PhoneScript_AnswerPhone_Male)
    checkflag(ENGINE_CHAD_FRIDAY_MORNING)
    iftrue(NotFriday)
    readvar(VAR_WEEKDAY)
    ifnotequal(FRIDAY, NotFriday)
    checktime(MORN)
    iftrue_jump(ChadFridayMorning)
NotFriday:
    sjump(ChadHangUpScript)
WantsBattle:
    getlandmarkname(STRING_BUFFER_5, LANDMARK_ROUTE_38)
    sjump(ChadReminderScript)
    SCRIPT_END
}
bool ChadPhoneCallerScript(script_s* s) {
    SCRIPT_BEGIN
    gettrainername(STRING_BUFFER_3, SCHOOLBOY, CHAD1)
    scall(PhoneScript_GreetPhone_Male)
    scall(PhoneScript_Random2)
    ifequal_jump(0, ChadOakGossip)
    checkflag(ENGINE_CHAD_READY_FOR_REMATCH)
    iftrue(Generic)
    checkflag(ENGINE_CHAD_FRIDAY_MORNING)
    iftrue(Generic)
    scall(PhoneScript_Random2)
    ifequal_jump(0, ChadWantsBattle)
Generic:
    scall(PhoneScript_Random3)
    ifequal_jump(0, ChadFoundRare)
    sjump(Phone_GenericCall_Male)
    SCRIPT_END
}
bool ChadFridayMorning(script_s* s) {
    SCRIPT_BEGIN
    setflag(ENGINE_CHAD_FRIDAY_MORNING)
    SCRIPT_FALLTHROUGH(ChadWantsBattle)
}
bool ChadWantsBattle(script_s* s) {
    SCRIPT_BEGIN
    getlandmarkname(STRING_BUFFER_5, LANDMARK_ROUTE_38)
    setflag(ENGINE_CHAD_READY_FOR_REMATCH)
    sjump(PhoneScript_WantsToBattle_Male)
    SCRIPT_END
}
bool ChadFoundRare(script_s* s) {
    SCRIPT_BEGIN
    sjump(Phone_CheckIfUnseenRare_Male)
    SCRIPT_END
}
bool ChadOakGossip(script_s* s) {
    SCRIPT_BEGIN
    sjump(ChadOakGossipScript)
    SCRIPT_END
}
