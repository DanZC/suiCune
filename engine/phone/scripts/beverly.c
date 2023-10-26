#include "../../../constants.h"
#include "../../../util/scripting.h"
#include "generic_callee.h"
#include "generic_caller.h"
#include "reminders.h"
#include "hangups.h"
#include "hangups_2.h"

bool BeverlyPhoneCalleeScript(script_s* s) {
    SCRIPT_BEGIN
    gettrainername(STRING_BUFFER_3, POKEFANF, BEVERLY1)
    scall(PhoneScript_AnswerPhone_Female)
    checkflag(ENGINE_BEVERLY_HAS_NUGGET)
    iftrue(HasNugget)
    sjump(BeverlyHangUpScript)
HasNugget:
    getlandmarkname(STRING_BUFFER_5, LANDMARK_NATIONAL_PARK)
    sjump(BeverlyComePickUpScript)
    SCRIPT_END
}
bool BeverlyPhoneCallerScript(script_s* s) {
    SCRIPT_BEGIN
    gettrainername(STRING_BUFFER_3, POKEFANF, BEVERLY1)
    scall(PhoneScript_GreetPhone_Female)
    checkflag(ENGINE_BEVERLY_HAS_NUGGET)
    iftrue(HasNugget)
    scall(PhoneScript_Random4)
    ifequal(0, FoundNugget)
HasNugget:
    sjump(Phone_GenericCall_Female)
FoundNugget:
    setflag(ENGINE_BEVERLY_HAS_NUGGET)
    getlandmarkname(STRING_BUFFER_5, LANDMARK_NATIONAL_PARK)
    sjump(PhoneScript_FoundItem_Female)
    SCRIPT_END
}
