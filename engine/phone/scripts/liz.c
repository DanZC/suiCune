#include "../../../constants.h"
#include "../../../util/scripting.h"
#include "generic_callee.h"
#include "generic_caller.h"
#include "reminders.h"
#include "hangups.h"
#include "liz_gossip.h"
#include "liz.h"

bool LizPhoneCalleeScript(script_s* s) {
    SCRIPT_BEGIN
    gettrainername(STRING_BUFFER_3, PICNICKER, LIZ1)
    checkflag(ENGINE_LIZ_READY_FOR_REMATCH)
    iftrue(WantsBattle)
    scall(PhoneScript_AnswerPhone_Female)
    checkflag(ENGINE_LIZ_THURSDAY_AFTERNOON)
    iftrue(NotThursday)
    readvar(VAR_WEEKDAY)
    ifnotequal(THURSDAY, NotThursday)
    checktime(DAY)
    iftrue_jump(LizThursdayAfternoon)
NotThursday:
    special(RandomPhoneMon)
    sjump(LizHangUpScript)
WantsBattle:
    getlandmarkname(STRING_BUFFER_5, LANDMARK_ROUTE_32)
    sjump(LizReminderScript)
    SCRIPT_END
}
bool LizPhoneCallerScript(script_s* s) {
    SCRIPT_BEGIN
    gettrainername(STRING_BUFFER_3, PICNICKER, LIZ1)
    scall(PhoneScript_Random4)
    ifequal_jump(0, LizWrongNumber)
    scall(PhoneScript_GreetPhone_Female)
    checkflag(ENGINE_LIZ_READY_FOR_REMATCH)
    iftrue(next)
    checkflag(ENGINE_LIZ_THURSDAY_AFTERNOON)
    iftrue(next)
next:
    scall(PhoneScript_Random2)
    ifequal_jump(0, LizGossip)
    checkflag(ENGINE_FLYPOINT_GOLDENROD)
    iffalse(Generic)
    scall(PhoneScript_Random2)
    ifequal_jump(0, LizWantsBattle)
Generic:
    sjump(Phone_GenericCall_Female)
    SCRIPT_END
}
bool LizThursdayAfternoon(script_s* s) {
    SCRIPT_BEGIN
    setflag(ENGINE_LIZ_THURSDAY_AFTERNOON)
    SCRIPT_FALLTHROUGH(LizWantsBattle)
}
bool LizWantsBattle(script_s* s) {
    SCRIPT_BEGIN
    getlandmarkname(STRING_BUFFER_5, LANDMARK_ROUTE_32)
    setflag(ENGINE_LIZ_READY_FOR_REMATCH)
    sjump(PhoneScript_WantsToBattle_Female)
    SCRIPT_END
}
bool LizWrongNumber(script_s* s) {
    SCRIPT_BEGIN
    sjump(LizWrongNumberScript)
    SCRIPT_END
}
bool LizGossip(script_s* s) {
    SCRIPT_BEGIN
    srandom(9)
    ifequal(0, CoolTrainerM)
    ifequal(1, Beauty)
    ifequal(2, Grunt)
    ifequal(3, Teacher)
    ifequal(4, SwimmerF)
    ifequal(5, KimonoGirl)
    ifequal(6, Skier)
    ifequal(7, Medium)
    ifequal(8, PokefanM)
CoolTrainerM:
    gettrainerclassname(STRING_BUFFER_4, COOLTRAINERM)
    sjump(LizGossipScript)
Beauty:
    gettrainerclassname(STRING_BUFFER_4, BEAUTY)
    sjump(LizGossipScript)
Grunt:
    gettrainerclassname(STRING_BUFFER_4, GRUNTM)
    sjump(LizGossipScript)
Teacher:
    gettrainerclassname(STRING_BUFFER_4, TEACHER)
    sjump(LizGossipScript)
SwimmerF:
    gettrainerclassname(STRING_BUFFER_4, SWIMMERF)
    sjump(LizGossipScript)
KimonoGirl:
    gettrainerclassname(STRING_BUFFER_4, KIMONO_GIRL)
    sjump(LizGossipScript)
Skier:
    gettrainerclassname(STRING_BUFFER_4, SKIER)
    sjump(LizGossipScript)
Medium:
    gettrainerclassname(STRING_BUFFER_4, MEDIUM)
    sjump(LizGossipScript)
PokefanM:
    gettrainerclassname(STRING_BUFFER_4, POKEFANM)
    sjump(LizGossipScript)
    SCRIPT_END
}
bool LizGossipScript(script_s* s) {
    SCRIPT_BEGIN
    sjump(LizGossipRandomScript)
    SCRIPT_END
}
