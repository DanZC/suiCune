#include "../../../constants.h"
#include "../../../util/scripting.h"
#include "generic_callee.h"
#include "generic_caller.h"
#include "reminders.h"
#include "hangups.h"
#include "jose.h"

bool JosePhoneCalleeScript(script_s* s) {
    SCRIPT_BEGIN
    gettrainername(STRING_BUFFER_3, BIRD_KEEPER, JOSE2)
    checkflag(ENGINE_JOSE_READY_FOR_REMATCH)
    iftrue(WantsBattle)
    scall(PhoneScript_AnswerPhone_Male)
    checkflag(ENGINE_JOSE_SATURDAY_NIGHT)
    iftrue(NotSaturday)
    checkflag(ENGINE_JOSE_HAS_STAR_PIECE)
    iftrue(HasItem)
    readvar(VAR_WEEKDAY)
    ifnotequal(SATURDAY, NotSaturday)
    checktime(NITE)
    iftrue_jump(JoseSaturdayNight)
NotSaturday:
    sjump(JoseHangUpScript)
WantsBattle:
    getlandmarkname(STRING_BUFFER_5, LANDMARK_ROUTE_27)
    sjump(JoseReminderScript)
HasItem:
    getlandmarkname(STRING_BUFFER_5, LANDMARK_ROUTE_27)
    sjump(JoseReminderScript)
    SCRIPT_END
}
bool JosePhoneCallerScript(script_s* s) {
    SCRIPT_BEGIN
    gettrainername(STRING_BUFFER_3, BIRD_KEEPER, JOSE2)
    scall(PhoneScript_GreetPhone_Male)
    checkflag(ENGINE_JOSE_READY_FOR_REMATCH)
    iftrue(Generic)
    checkflag(ENGINE_JOSE_SATURDAY_NIGHT)
    iftrue(Generic)
    checkflag(ENGINE_JOSE_HAS_STAR_PIECE)
    iftrue(Generic)
    scall(PhoneScript_Random3)
    ifequal_jump(0, JoseWantsBattle)
    scall(PhoneScript_Random3)
    ifequal_jump(0, JoseHasStarPiece)
Generic:
    scall(PhoneScript_Random3)
    ifequal_jump(0, JoseFoundRare)
    sjump(Phone_GenericCall_Male)
    SCRIPT_END
}
bool JoseSaturdayNight(script_s* s) {
    SCRIPT_BEGIN
    setflag(ENGINE_JOSE_SATURDAY_NIGHT)
    SCRIPT_FALLTHROUGH(JoseWantsBattle)
}
bool JoseWantsBattle(script_s* s) {
    SCRIPT_BEGIN
    getlandmarkname(STRING_BUFFER_5, LANDMARK_ROUTE_27)
    setflag(ENGINE_JOSE_READY_FOR_REMATCH)
    sjump(PhoneScript_WantsToBattle_Male)
    SCRIPT_END
}
bool JoseFoundRare(script_s* s) {
    SCRIPT_BEGIN
    sjump(Phone_CheckIfUnseenRare_Male)
    SCRIPT_END
}
bool JoseHasStarPiece(script_s* s) {
    SCRIPT_BEGIN
    setflag(ENGINE_JOSE_HAS_STAR_PIECE)
    getlandmarkname(STRING_BUFFER_5, LANDMARK_ROUTE_27)
    sjump(PhoneScript_FoundItem_Male)
    SCRIPT_END
}
