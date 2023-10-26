#include "../../../constants.h"
#include "../../../util/scripting.h"
#include "generic_callee.h"
#include "generic_caller.h"
#include "reminders.h"
#include "hangups.h"
#include "kenji.h"

bool KenjiPhoneCalleeScript(script_s* s) {
    SCRIPT_BEGIN
    gettrainername(STRING_BUFFER_3, BLACKBELT_T, KENJI3)
    scall(PhoneScript_AnswerPhone_Male)
    sjump(KenjiAnswerPhoneScript)
    SCRIPT_END
}
bool KenjiPhoneCallerScript(script_s* s) {
    SCRIPT_BEGIN
    gettrainername(STRING_BUFFER_3, BLACKBELT_T, KENJI3)
    scall(PhoneScript_GreetPhone_Male)
    sjump(KenjiCallingPhoneScript)
    SCRIPT_END
}
