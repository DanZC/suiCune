#include "../../../constants.h"
#include "../../../util/scripting.h"
#include "generic_callee.h"
#include "generic_caller.h"
#include "reminders.h"
#include "hangups.h"
#include "hangups_2.h"
#include "tiffany.h"

bool TiffanyPhoneCalleeScript(script_s* s) {
    SCRIPT_BEGIN
    gettrainername(STRING_BUFFER_3, PICNICKER, TIFFANY3)
    checkflag(ENGINE_TIFFANY_READY_FOR_REMATCH)
    iftrue(WantsBattle)
    scall(PhoneScript_AnswerPhone_Female)
    checkflag(ENGINE_TIFFANY_TUESDAY_AFTERNOON)
    iftrue(NotTuesday)
    checkflag(ENGINE_TIFFANY_HAS_PINK_BOW)
    iftrue(HasItem)
    readvar(VAR_WEEKDAY)
    ifnotequal(TUESDAY, NotTuesday)
    checktime(DAY)
    iftrue_jump(TiffanyTuesdayAfternoon)
NotTuesday:
    sjump(TiffanyNoItemScript)
WantsBattle:
    getlandmarkname(STRING_BUFFER_5, LANDMARK_ROUTE_43)
    sjump(TiffanyAsleepScript)
HasItem:
    getlandmarkname(STRING_BUFFER_5, LANDMARK_ROUTE_43)
    sjump(TiffanyHurryScript)
    SCRIPT_END
}
bool TiffanyPhoneCallerScript(script_s* s) {
    SCRIPT_BEGIN
    gettrainername(STRING_BUFFER_3, PICNICKER, TIFFANY3)
    scall(PhoneScript_Random4)
    ifequal_jump(0, TiffanysFamilyMembers)
    scall(PhoneScript_GreetPhone_Female)
    checkflag(ENGINE_TIFFANY_READY_FOR_REMATCH)
    iftrue(Generic)
    checkflag(ENGINE_TIFFANY_TUESDAY_AFTERNOON)
    iftrue(Generic)
    checkflag(ENGINE_TIFFANY_HAS_PINK_BOW)
    iftrue(Generic)
    scall(PhoneScript_Random3)
    ifequal_jump(0, TiffanyWantsBattle)
    checkevent(EVENT_TIFFANY_GAVE_PINK_BOW)
    iftrue(PinkBow)
    scall(PhoneScript_Random2)
    ifequal_jump(0, TiffanyHasPinkBow)
PinkBow:
    scall(PhoneScript_Random11)
    ifequal_jump(0, TiffanyHasPinkBow)
Generic:
    sjump(Phone_GenericCall_Female)
    SCRIPT_END
}
bool TiffanyTuesdayAfternoon(script_s* s) {
    SCRIPT_BEGIN
    setflag(ENGINE_TIFFANY_TUESDAY_AFTERNOON)
    SCRIPT_FALLTHROUGH(TiffanyWantsBattle)
}
bool TiffanyWantsBattle(script_s* s) {
    SCRIPT_BEGIN
    getlandmarkname(STRING_BUFFER_5, LANDMARK_ROUTE_43)
    setflag(ENGINE_TIFFANY_READY_FOR_REMATCH)
    sjump(PhoneScript_WantsToBattle_Female)
    SCRIPT_END
}
bool TiffanysFamilyMembers(script_s* s) {
    SCRIPT_BEGIN
    srandom(6)
    ifequal(0, Grandma)
    ifequal(1, Grandpa)
    ifequal(2, Mom)
    ifequal(3, Dad)
    ifequal(4, Sister)
    ifequal(5, Brother)
Grandma:
    getstring(STRING_BUFFER_4, GrandmaString)
    goto PoorClefairy;
Grandpa:
    getstring(STRING_BUFFER_4, GrandpaString)
    goto PoorClefairy;
Mom:
    getstring(STRING_BUFFER_4, MomString)
    goto PoorClefairy;
Dad:
    getstring(STRING_BUFFER_4, DadString)
    goto PoorClefairy;
Sister:
    getstring(STRING_BUFFER_4, SisterString)
    goto PoorClefairy;
Brother:
    getstring(STRING_BUFFER_4, BrotherString)
    goto PoorClefairy;
PoorClefairy:
    sjump(TiffanyItsAwful)
    SCRIPT_END
}
bool TiffanyHasPinkBow(script_s* s) {
    SCRIPT_BEGIN
    setflag(ENGINE_TIFFANY_HAS_PINK_BOW)
    getlandmarkname(STRING_BUFFER_5, LANDMARK_ROUTE_43)
    sjump(PhoneScript_FoundItem_Female)
    SCRIPT_END
}
