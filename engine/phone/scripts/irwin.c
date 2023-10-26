#include "../../../constants.h"
#include "../../../util/scripting.h"
#include "generic_callee.h"
#include "generic_caller.h"
#include "reminders.h"
#include "hangups.h"
#include "irwin_gossip.h"

bool IrwinPhoneCalleeScript(script_s* s) {
    SCRIPT_BEGIN
    gettrainername(STRING_BUFFER_3, JUGGLER, IRWIN1)
    scall(PhoneScript_AnswerPhone_Male)
    checkflag(ENGINE_ROCKETS_IN_RADIO_TOWER)
    iftrue(Rockets)
    sjump(IrwinRandomTextScript)
Rockets:
    sjump(IrwinRocketRumorScript)
    SCRIPT_END
}
bool IrwinPhoneCallerScript(script_s* s) {
    SCRIPT_BEGIN
    gettrainername(STRING_BUFFER_3, JUGGLER, IRWIN1)
    scall(PhoneScript_GreetPhone_Male)
    checkflag(ENGINE_ROCKETS_IN_RADIO_TOWER)
    iftrue(Rockets)
    sjump(IrwinRumorScript)
Rockets:
    sjump(IrwinRocketRumorScript)
    SCRIPT_END
}
