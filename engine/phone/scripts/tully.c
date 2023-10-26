#include "../../../constants.h"
#include "../../../util/scripting.h"
#include "generic_callee.h"
#include "generic_caller.h"
#include "reminders.h"
#include "hangups.h"
#include "hangups_2.h"
#include "tully.h"

bool TullyPhoneCalleeScript(script_s* s) {
    SCRIPT_BEGIN
    gettrainername(STRING_BUFFER_3, FISHER, TULLY1)
    checkflag(ENGINE_TULLY_READY_FOR_REMATCH)
    iftrue(WantsBattle)
    scall(PhoneScript_AnswerPhone_Male)
    checkflag(ENGINE_TULLY_SUNDAY_NIGHT)
    iftrue(NotSunday)
    checkflag(ENGINE_TULLY_HAS_WATER_STONE)
    iftrue(WaterStone)
    readvar(VAR_WEEKDAY)
    ifnotequal(SUNDAY, NotSunday)
    checktime(NITE)
    iftrue_jump(TullySundayNight)
NotSunday:
    sjump(TullyNoItemScript)
WantsBattle:
    getlandmarkname(STRING_BUFFER_5, LANDMARK_ROUTE_42)
    sjump(TullyForwardScript)
WaterStone:
    getlandmarkname(STRING_BUFFER_5, LANDMARK_ROUTE_42)
    sjump(TullyHurryScript)
    SCRIPT_END
}
bool TullyPhoneCallerScript(script_s* s) {
    SCRIPT_BEGIN
    gettrainername(STRING_BUFFER_3, FISHER, TULLY1)
    scall(PhoneScript_GreetPhone_Male)
    checkflag(ENGINE_TULLY_READY_FOR_REMATCH)
    iftrue(Generic)
    checkflag(ENGINE_TULLY_SUNDAY_NIGHT)
    iftrue(Generic)
    checkflag(ENGINE_TULLY_HAS_WATER_STONE)
    iftrue(Generic)
    scall(PhoneScript_Random3)
    ifequal_jump(0, TullyWantsBattle)
    checkevent(EVENT_TULLY_GAVE_WATER_STONE)
    iftrue(WaterStone)
    scall(PhoneScript_Random2)
    ifequal_jump(0, TullyFoundWaterStone)
WaterStone:
    scall(PhoneScript_Random11)
    ifequal_jump(0, TullyFoundWaterStone)
Generic:
    sjump(Phone_GenericCall_Male)
    SCRIPT_END
}
bool TullySundayNight(script_s* s) {
    SCRIPT_BEGIN
    setflag(ENGINE_TULLY_SUNDAY_NIGHT)
    SCRIPT_FALLTHROUGH(TullyWantsBattle)
}
bool TullyWantsBattle(script_s* s) {
    SCRIPT_BEGIN
    getlandmarkname(STRING_BUFFER_5, LANDMARK_ROUTE_42)
    setflag(ENGINE_TULLY_READY_FOR_REMATCH)
    sjump(PhoneScript_WantsToBattle_Male)
    SCRIPT_END
}
bool TullyFoundWaterStone(script_s* s) {
    SCRIPT_BEGIN
    setflag(ENGINE_TULLY_HAS_WATER_STONE)
    getlandmarkname(STRING_BUFFER_5, LANDMARK_ROUTE_42)
    sjump(PhoneScript_FoundItem_Male)
    SCRIPT_END
}
