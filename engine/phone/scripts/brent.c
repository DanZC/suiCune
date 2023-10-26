#include "../../../constants.h"
#include "../../../util/scripting.h"
#include "generic_callee.h"
#include "generic_caller.h"
#include "reminders.h"
#include "hangups.h"
#include "brent_gossip.h"
#include "brent.h"

bool BrentPhoneCalleeScript(script_s* s) {
    SCRIPT_BEGIN
    gettrainername(STRING_BUFFER_3, POKEMANIAC, BRENT1)
    checkflag(ENGINE_BRENT_READY_FOR_REMATCH)
    iftrue(WantsBattle)
    scall(PhoneScript_AnswerPhone_Male)
    checkflag(ENGINE_BRENT_MONDAY_MORNING)
    iftrue(NotMonday)
    readvar(VAR_WEEKDAY)
    ifnotequal(MONDAY, NotMonday)
    checktime(MORN)
    iftrue_jump(BrentMondayMorning)
NotMonday:
    sjump(BrentHangUpScript)
WantsBattle:
    getlandmarkname(STRING_BUFFER_5, LANDMARK_ROUTE_43)
    sjump(BrentReminderScript)
    SCRIPT_END
}
bool BrentPhoneCallerScript(script_s* s) {
    SCRIPT_BEGIN
    gettrainername(STRING_BUFFER_3, POKEMANIAC, BRENT1)
    scall(PhoneScript_GreetPhone_Male)
    scall(PhoneScript_Random2)
    ifequal_jump(0, BrentBillTrivia)
    checkflag(ENGINE_BRENT_READY_FOR_REMATCH)
    iftrue(Generic)
    checkflag(ENGINE_BRENT_MONDAY_MORNING)
    iftrue(Generic)
    scall(PhoneScript_Random2)
    ifequal_jump(0, BrentWantsBattle)
Generic:
    sjump(Phone_GenericCall_Male)
    SCRIPT_END
}
bool BrentMondayMorning(script_s* s) {
    SCRIPT_BEGIN
    setflag(ENGINE_BRENT_MONDAY_MORNING)
    SCRIPT_FALLTHROUGH(BrentWantsBattle)
}
bool BrentWantsBattle(script_s* s) {
    SCRIPT_BEGIN
    getlandmarkname(STRING_BUFFER_5, LANDMARK_ROUTE_43)
    setflag(ENGINE_BRENT_READY_FOR_REMATCH)
    sjump(PhoneScript_WantsToBattle_Male)
    SCRIPT_END
}
bool BrentBillTrivia(script_s* s) {
    SCRIPT_BEGIN
    sjump(BrentBillTriviaScript)
    SCRIPT_END
}
