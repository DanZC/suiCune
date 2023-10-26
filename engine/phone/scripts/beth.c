#include "../../../constants.h"
#include "../../overworld/scripting.h"
#include "../../../util/scripting.h"
#include "generic_callee.h"
#include "generic_caller.h"
#include "reminders.h"
#include "hangups.h"
#include "hangups_2.h"
#include "beth.h"

bool BethPhoneCalleeScript(script_s* s) {
    SCRIPT_BEGIN
    gettrainername(STRING_BUFFER_3, COOLTRAINERF, BETH1)
    checkflag(ENGINE_BETH_READY_FOR_REMATCH)
    iftrue(WantsBattle)
    scall(PhoneScript_AnswerPhone_Female)
    checkflag(ENGINE_BETH_FRIDAY_AFTERNOON)
    iftrue(NotFriday)
    readvar(VAR_WEEKDAY)
    ifnotequal(FRIDAY, NotFriday)
    checktime(DAY)
    iftrue_jump(BethFridayAfternoon)
NotFriday:
    sjump(BethHangUpScript)
WantsBattle:
    getlandmarkname(STRING_BUFFER_5, LANDMARK_ROUTE_26)
    sjump(BethBattleReminderScript)
    SCRIPT_END
}
bool BethPhoneCallerScript(script_s* s) {
    SCRIPT_BEGIN
    gettrainername(STRING_BUFFER_3, COOLTRAINERF, BETH1)
    scall(PhoneScript_GreetPhone_Female)
    checkflag(ENGINE_BETH_READY_FOR_REMATCH)
    iftrue(Generic)
    checkflag(ENGINE_BETH_FRIDAY_AFTERNOON)
    iftrue(Generic)
    scall(PhoneScript_Random2)
    ifequal_jump(0, BethWantsBattle)
Generic:
    sjump(Phone_GenericCall_Female)
    SCRIPT_END
}
bool BethFridayAfternoon(script_s* s) {
    SCRIPT_BEGIN
    setflag(ENGINE_BETH_FRIDAY_AFTERNOON)
    SCRIPT_FALLTHROUGH(BethWantsBattle)
}
bool BethWantsBattle(script_s* s) {
    SCRIPT_BEGIN
    getlandmarkname(STRING_BUFFER_5, LANDMARK_ROUTE_26)
    setflag(ENGINE_BETH_READY_FOR_REMATCH)
    sjump(PhoneScript_WantsToBattle_Female)
    SCRIPT_END
}
