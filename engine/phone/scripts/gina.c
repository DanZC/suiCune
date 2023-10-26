#include "../../../constants.h"
#include "../../../util/scripting.h"
#include "generic_callee.h"
#include "generic_caller.h"
#include "reminders.h"
#include "hangups.h"
#include "hangups_2.h"
#include "gina.h"

bool GinaPhoneCalleeScript(script_s* s) {
    SCRIPT_BEGIN
    gettrainername(STRING_BUFFER_3, PICNICKER, GINA1)
    checkflag(ENGINE_GINA_READY_FOR_REMATCH)
    iftrue(WantsBattle)
    scall(PhoneScript_AnswerPhone_Female)
    checkflag(ENGINE_GINA_SUNDAY_AFTERNOON)
    iftrue(NotSunday)
    checkflag(ENGINE_GINA_HAS_LEAF_STONE)
    iftrue(HasLeafStone)
    readvar(VAR_WEEKDAY)
    ifnotequal(SUNDAY, NotSunday)
    checktime(DAY)
    iftrue_jump(GinaSundayDay)
NotSunday:
    checkflag(ENGINE_ROCKETS_IN_RADIO_TOWER)
    iftrue(Rockets)
    sjump(GinaHangUpScript)
Rockets:
    sjump(GinaRocketRumorScript)
WantsBattle:
    getlandmarkname(STRING_BUFFER_5, LANDMARK_ROUTE_34)
    sjump(GinaReminderScript)
HasLeafStone:
    getlandmarkname(STRING_BUFFER_5, LANDMARK_ROUTE_34)
    sjump(GinaComePickUpScript)
    SCRIPT_END
}
bool GinaPhoneCallerScript(script_s* s) {
    SCRIPT_BEGIN
    gettrainername(STRING_BUFFER_3, PICNICKER, GINA1)
    scall(PhoneScript_GreetPhone_Female)
    checkflag(ENGINE_ROCKETS_IN_RADIO_TOWER)
    iftrue_jump(GinaRockets)
    checkflag(ENGINE_GINA_READY_FOR_REMATCH)
    iftrue(Generic)
    checkflag(ENGINE_GINA_SUNDAY_AFTERNOON)
    iftrue(Generic)
    checkflag(ENGINE_GINA_HAS_LEAF_STONE)
    iftrue(Generic)
    checkevent(EVENT_GINA_GAVE_LEAF_STONE)
    iftrue(GaveLeafStone)
    scall(PhoneScript_Random2)
    ifequal_jump(0, GinaHasLeafStone)
GaveLeafStone:
    scall(PhoneScript_Random11)
    ifequal_jump(0, GinaHasLeafStone)
    checkflag(ENGINE_FLYPOINT_GOLDENROD)
    iffalse(Generic)
    scall(PhoneScript_Random3)
    ifequal_jump(0, GinaWantsBattle)
Generic:
    sjump(Phone_GenericCall_Female)
    SCRIPT_END
}
bool GinaSundayDay(script_s* s) {
    SCRIPT_BEGIN
    setflag(ENGINE_GINA_SUNDAY_AFTERNOON)
    SCRIPT_FALLTHROUGH(GinaWantsBattle)
}
bool GinaWantsBattle(script_s* s) {
    SCRIPT_BEGIN
    getlandmarkname(STRING_BUFFER_5, LANDMARK_ROUTE_34)
    setflag(ENGINE_GINA_READY_FOR_REMATCH)
    sjump(PhoneScript_WantsToBattle_Female)
    SCRIPT_END
}
bool GinaRockets(script_s* s) {
    SCRIPT_BEGIN
    sjump(GinaRocketRumorScript)
    SCRIPT_END
}
bool GinaHasLeafStone(script_s* s) {
    SCRIPT_BEGIN
    setflag(ENGINE_GINA_HAS_LEAF_STONE)
    getlandmarkname(STRING_BUFFER_5, LANDMARK_ROUTE_34)
    sjump(PhoneScript_FoundItem_Female)
    SCRIPT_END
}
