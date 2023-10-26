#include "../../../constants.h"
#include "../../../util/scripting.h"
#include "generic_callee.h"
#include "generic_caller.h"
#include "reminders.h"
#include "hangups.h"
#include "reminders_2.h"
#include "todd.h"

bool ToddPhoneCalleeScript(script_s* s) {
    SCRIPT_BEGIN
    gettrainername(STRING_BUFFER_3, CAMPER, TODD1)
    checkflag(ENGINE_TODD_READY_FOR_REMATCH)
    iftrue(WantsBattle)
    scall(PhoneScript_AnswerPhone_Male)
    checkflag(ENGINE_TODD_SATURDAY_MORNING)
    iftrue(NotSaturday)
    readvar(VAR_WEEKDAY)
    ifnotequal(SATURDAY, NotSaturday)
    checktime(MORN)
    iftrue_jump(ToddSaturdayMorning)
NotSaturday:
    checkflag(ENGINE_GOLDENROD_DEPT_STORE_SALE_IS_ON)
    iftrue(SaleOn)
    sjump(ToddNoItemScript)
WantsBattle:
    getlandmarkname(STRING_BUFFER_5, LANDMARK_ROUTE_34)
    sjump(ToddForwardScript)
SaleOn:
    sjump(ToddHurryScript)
    SCRIPT_END
}
bool ToddPhoneCallerScript(script_s* s) {
    SCRIPT_BEGIN
    gettrainername(STRING_BUFFER_3, CAMPER, TODD1)
    scall(PhoneScript_GreetPhone_Male)
    checkflag(ENGINE_TODD_READY_FOR_REMATCH)
    iftrue(TryForSale)
    checkflag(ENGINE_TODD_SATURDAY_MORNING)
    iftrue(TryForSale)
    checkflag(ENGINE_FLYPOINT_GOLDENROD)
    iffalse(NoGoldenrod)
    scall(PhoneScript_Random2)
    ifequal_jump(0, ToddWantsBattle)
TryForSale:
    scall(PhoneScript_Random2)
    ifequal_jump(0, ToddDeptStoreSale)
NoGoldenrod:
    scall(PhoneScript_Random3)
    ifequal_jump(0, ToddFoundRare)
    sjump(Phone_GenericCall_Male)
    SCRIPT_END
}
bool ToddSaturdayMorning(script_s* s) {
    SCRIPT_BEGIN
    setflag(ENGINE_TODD_SATURDAY_MORNING)
    SCRIPT_FALLTHROUGH(ToddWantsBattle)
}
bool ToddWantsBattle(script_s* s) {
    SCRIPT_BEGIN
    getlandmarkname(STRING_BUFFER_5, LANDMARK_ROUTE_34)
    setflag(ENGINE_TODD_READY_FOR_REMATCH)
    sjump(PhoneScript_WantsToBattle_Male)
    SCRIPT_END
}
bool ToddFoundRare(script_s* s) {
    SCRIPT_BEGIN
    sjump(Phone_CheckIfUnseenRare_Male)
    SCRIPT_END
}
bool ToddDeptStoreSale(script_s* s) {
    SCRIPT_BEGIN
    setflag(ENGINE_GOLDENROD_DEPT_STORE_SALE_IS_ON)
    sjump(ToddItemScript)
    SCRIPT_END
}
