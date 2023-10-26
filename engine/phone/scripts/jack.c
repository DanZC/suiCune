#include "../../../constants.h"
#include "../../../util/scripting.h"
#include "generic_callee.h"
#include "generic_caller.h"
#include "reminders.h"
#include "hangups.h"
#include "jack_gossip.h"
#include "jack.h"

bool JackPhoneCalleeScript(script_s* s) {
    SCRIPT_BEGIN
    gettrainername(STRING_BUFFER_3, SCHOOLBOY, JACK1)
    checkflag(ENGINE_JACK_READY_FOR_REMATCH)
    iftrue(WantsBattle)
    scall(PhoneScript_AnswerPhone_Male)
    checkflag(ENGINE_JACK_MONDAY_MORNING)
    iftrue(NotMonday)
    readvar(VAR_WEEKDAY)
    ifnotequal(MONDAY, NotMonday)
    checktime(MORN)
    iftrue_jump(JackMondayMorning)
NotMonday:
    sjump(JackPhoneTipsScript)
WantsBattle:
    getlandmarkname(STRING_BUFFER_5, LANDMARK_NATIONAL_PARK)
    sjump(JackWantsBattleScript)
    SCRIPT_END
}
bool JackPhoneCallerScript(script_s* s) {
    SCRIPT_BEGIN
    gettrainername(STRING_BUFFER_3, SCHOOLBOY, JACK1)
    scall(PhoneScript_GreetPhone_Male)
    scall(PhoneScript_Random2)
    ifequal_jump(0, JackBattleTrivia)
    checkflag(ENGINE_JACK_READY_FOR_REMATCH)
    iftrue(WaitingForBattle)
    checkflag(ENGINE_JACK_MONDAY_MORNING)
    iftrue(WaitingForBattle)
    scall(PhoneScript_Random2)
    ifequal_jump(0, JackWantsToBattle)
WaitingForBattle:
    scall(PhoneScript_Random3)
    ifequal_jump(0, JackFindsRare)
    sjump(Phone_GenericCall_Male)
    SCRIPT_END
}
bool JackMondayMorning(script_s* s) {
    SCRIPT_BEGIN
    setflag(ENGINE_JACK_MONDAY_MORNING)
    SCRIPT_FALLTHROUGH(JackWantsToBattle)
}
bool JackWantsToBattle(script_s* s) {
    SCRIPT_BEGIN
    getlandmarkname(STRING_BUFFER_5, LANDMARK_NATIONAL_PARK)
    setflag(ENGINE_JACK_READY_FOR_REMATCH)
    sjump(PhoneScript_WantsToBattle_Male)
    SCRIPT_END
}
bool JackFindsRare(script_s* s) {
    SCRIPT_BEGIN
    sjump(Phone_CheckIfUnseenRare_Male)
    SCRIPT_END
}
bool JackBattleTrivia(script_s* s) {
    SCRIPT_BEGIN
    sjump(JackTriviaScript)
    SCRIPT_END
}
