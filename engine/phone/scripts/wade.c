#include "../../../constants.h"
#include "../../../util/scripting.h"
#include "generic_callee.h"
#include "generic_caller.h"
#include "reminders.h"
#include "hangups.h"
#include "hangups_2.h"
#include "wade.h"

bool WadePhoneCalleeScript(script_s* s) {
    SCRIPT_BEGIN
    gettrainername(STRING_BUFFER_3, BUG_CATCHER, WADE1)
    checkflag(ENGINE_WADE_READY_FOR_REMATCH)
    iftrue(WantsBattle)
    scall(PhoneScript_AnswerPhone_Male)
    checkflag(ENGINE_WADE_TUESDAY_NIGHT)
    iftrue(NotTuesday)
    checkflag(ENGINE_WADE_HAS_ITEM)
    iftrue(HasItem)
    readvar(VAR_WEEKDAY)
    ifnotequal(TUESDAY, NotTuesday)
    checktime(NITE)
    iftrue_jump(WadeTuesdayNight)
NotTuesday:
    scall(PhoneScript_Random2)
    ifequal(0, NoContest)
    checkflag(ENGINE_DAILY_BUG_CONTEST)
    iftrue(NoContest)
    readvar(VAR_WEEKDAY)
    ifequal(TUESDAY, ContestToday)
    ifequal(THURSDAY, ContestToday)
    ifequal(SATURDAY, ContestToday)
NoContest:
    sjump(WadeNoBerriesScript)
ContestToday:
    sjump(PhoneScript_BugCatchingContest)
WantsBattle:
    getlandmarkname(STRING_BUFFER_5, LANDMARK_ROUTE_31)
    sjump(WadeQuickBattleScript)
HasItem:
    getlandmarkname(STRING_BUFFER_5, LANDMARK_ROUTE_31)
    sjump(WadeComeQuickScript)
    SCRIPT_END
}
bool WadePhoneCallerScript(script_s* s) {
    SCRIPT_BEGIN
    gettrainername(STRING_BUFFER_3, BUG_CATCHER, WADE1)
    scall(PhoneScript_GreetPhone_Male)
    scall(PhoneScript_Random2)
    ifequal(0, NoContest)
    checkflag(ENGINE_DAILY_BUG_CONTEST)
    iftrue(NoContest)
    readvar(VAR_WEEKDAY)
    ifequal(TUESDAY, ContestToday)
    ifequal(THURSDAY, ContestToday)
    ifequal(SATURDAY, ContestToday)
NoContest:
    checkflag(ENGINE_WADE_READY_FOR_REMATCH)
    iftrue(next)
    checkflag(ENGINE_WADE_TUESDAY_NIGHT)
    iftrue(next)
    checkflag(ENGINE_WADE_HAS_ITEM)
    iftrue(next)
    scall(PhoneScript_Random2)
    ifequal_jump(0, WadeHasItem2)
    checkflag(ENGINE_FLYPOINT_GOLDENROD)
    iffalse(next)
    scall(PhoneScript_Random2)
    ifequal_jump(0, WadeWantsBattle2)
next:
    scall(PhoneScript_Random3)
    ifequal_jump(0, WadeFoundRare)
    sjump(Phone_GenericCall_Male)
ContestToday:
    sjump(PhoneScript_BugCatchingContest)
    SCRIPT_END
}
bool WadeTuesdayNight(script_s* s) {
    SCRIPT_BEGIN
    setflag(ENGINE_WADE_TUESDAY_NIGHT)
    SCRIPT_FALLTHROUGH(WadeWantsBattle2)
}
bool WadeWantsBattle2(script_s* s) {
    SCRIPT_BEGIN
    getlandmarkname(STRING_BUFFER_5, LANDMARK_ROUTE_31)
    setflag(ENGINE_WADE_READY_FOR_REMATCH)
    sjump(PhoneScript_WantsToBattle_Male)
    SCRIPT_END
}
bool WadeFoundRare(script_s* s) {
    SCRIPT_BEGIN
    sjump(Phone_CheckIfUnseenRare_Male)
    SCRIPT_END
}
bool WadeHasItem2(script_s* s) {
    SCRIPT_BEGIN
    setflag(ENGINE_WADE_HAS_ITEM)
    getlandmarkname(STRING_BUFFER_5, LANDMARK_ROUTE_31)
    clearevent(EVENT_WADE_HAS_BERRY)
    clearevent(EVENT_WADE_HAS_PSNCUREBERRY)
    clearevent(EVENT_WADE_HAS_PRZCUREBERRY)
    clearevent(EVENT_WADE_HAS_BITTER_BERRY)
    srandom(4)
    ifequal(0, Berry)
    ifequal(1, PsnCureBerry)
    ifequal(2, PrzCureBerry)
    ifequal(3, Bitterberry)
Berry:
    setevent(EVENT_WADE_HAS_BERRY)
    goto FoundBerry;
PsnCureBerry:
    setevent(EVENT_WADE_HAS_PSNCUREBERRY)
    goto FoundBerry;
PrzCureBerry:
    setevent(EVENT_WADE_HAS_PRZCUREBERRY)
    goto FoundBerry;
Bitterberry:
    setevent(EVENT_WADE_HAS_BITTER_BERRY)
FoundBerry:
    sjump(PhoneScript_FoundItem_Male)
    SCRIPT_END
}
