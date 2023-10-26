#include "../../../constants.h"
#include "../../../util/scripting.h"
#include "generic_callee.h"
#include "generic_caller.h"
#include "reminders.h"
#include "hangups.h"
#include "hangups_2.h"
#include "wilton.h"

bool WiltonPhoneCalleeScript(script_s* s) {
    SCRIPT_BEGIN
    gettrainername(STRING_BUFFER_3, FISHER, WILTON1)
    checkflag(ENGINE_WILTON_READY_FOR_REMATCH)
    iftrue(WantsBattle)
    scall(PhoneScript_AnswerPhone_Male)
    checkflag(ENGINE_WILTON_THURSDAY_MORNING)
    iftrue(NotThursday)
    checkflag(ENGINE_WILTON_HAS_ITEM)
    iftrue(HasItem)
    readvar(VAR_WEEKDAY)
    ifnotequal(THURSDAY, NotThursday)
    checktime(MORN)
    iftrue_jump(WiltonThursdayMorning)
NotThursday:
    sjump(WiltonHaventFoundAnythingScript)
WantsBattle:
    getlandmarkname(STRING_BUFFER_5, LANDMARK_ROUTE_44)
    sjump(WiltonNotBitingScript)
HasItem:
    getlandmarkname(STRING_BUFFER_5, LANDMARK_ROUTE_44)
    sjump(WiltonWantThisScript)
    SCRIPT_END
}
bool WiltonPhoneCallerScript(script_s* s) {
    SCRIPT_BEGIN
    gettrainername(STRING_BUFFER_3, FISHER, WILTON1)
    scall(PhoneScript_GreetPhone_Male)
    checkflag(ENGINE_WILTON_READY_FOR_REMATCH)
    iftrue(GenericCall)
    checkflag(ENGINE_WILTON_THURSDAY_MORNING)
    iftrue(GenericCall)
    checkflag(ENGINE_WILTON_HAS_ITEM)
    iftrue(GenericCall)
    scall(PhoneScript_Random2)
    ifequal_jump(0, WiltonWantsBattle)
    scall(PhoneScript_Random2)
    ifequal_jump(0, WiltonHasItem)
GenericCall:
    sjump(Phone_GenericCall_Male)
    SCRIPT_END
}
bool WiltonThursdayMorning(script_s* s) {
    SCRIPT_BEGIN
    setflag(ENGINE_WILTON_THURSDAY_MORNING)
    SCRIPT_FALLTHROUGH(WiltonWantsBattle)
}
bool WiltonWantsBattle(script_s* s) {
    SCRIPT_BEGIN
    getlandmarkname(STRING_BUFFER_5, LANDMARK_ROUTE_44)
    setflag(ENGINE_WILTON_READY_FOR_REMATCH)
    sjump(PhoneScript_WantsToBattle_Male)
    SCRIPT_END
}
bool WiltonHasItem(script_s* s) {
    SCRIPT_BEGIN
    setflag(ENGINE_WILTON_HAS_ITEM)
    getlandmarkname(STRING_BUFFER_5, LANDMARK_ROUTE_44)
    clearevent(EVENT_WILTON_HAS_ULTRA_BALL)
    clearevent(EVENT_WILTON_HAS_GREAT_BALL)
    clearevent(EVENT_WILTON_HAS_POKE_BALL)
    srandom(5)
    ifequal(0, UltraBall)
    srandom(3)
    ifequal(0, GreatBall)
    goto PokeBall;
UltraBall:
    setevent(EVENT_WILTON_HAS_ULTRA_BALL)
    goto FoundItem;
GreatBall:
    setevent(EVENT_WILTON_HAS_GREAT_BALL)
    goto FoundItem;
PokeBall:
    setevent(EVENT_WILTON_HAS_POKE_BALL)
FoundItem:
    sjump(PhoneScript_FoundItem_Male)
    SCRIPT_END
}
