#include "../../../constants.h"
#include "../../../util/scripting.h"
#include "generic_caller.h"
#include "generic_callee.h"
#include "../../../data/phone/text/jack_callee.h"
#include "../../../data/phone/text/beverly_callee.h"
#include "../../../data/phone/text/huey_callee.h"
#include "../../../data/phone/text/gaven_callee.h"
#include "../../../data/phone/text/beth_callee.h"
#include "../../../data/phone/text/jose_callee.h"
#include "../../../data/phone/text/reena_callee.h"
#include "../../../data/phone/text/joey_callee.h"
#include "../../../data/phone/text/wade_callee.h"
#include "../../../data/phone/text/ralph_callee.h"
#include "../../../data/phone/text/liz_callee.h"
#include "../../../data/phone/text/anthony_callee.h"
#include "../../../data/phone/text/todd_callee.h"
#include "../../../data/phone/text/gina_callee.h"
#include "../../../data/phone/text/irwin_callee.h"
#include "../../../data/phone/text/arnie_callee.h"
#include "../../../data/phone/text/alan_callee.h"
#include "../../../data/phone/text/dana_callee.h"
#include "../../../data/phone/text/chad_callee.h"
#include "../../../data/phone/text/derek_callee.h"
#include "../../../data/phone/text/tully_callee.h"
#include "../../../data/phone/text/brent_callee.h"
#include "../../../data/phone/text/tiffany_callee.h"
#include "../../../data/phone/text/vance_callee.h"
#include "../../../data/phone/text/wilton_callee.h"
#include "../../../data/phone/text/parry_callee.h"
#include "../../../data/phone/text/erin_callee.h"
#include "../../../data/phone/text/kenji_callee.h"
#include "../../../data/phone/text/unknown_callee.h"

bool PhoneScript_Random2(script_s* s) {
    SCRIPT_BEGIN
    srandom(2)
    s_end
    SCRIPT_END
}
bool PhoneScript_Random3(script_s* s) {
    SCRIPT_BEGIN
    srandom(3)
    s_end
    SCRIPT_END
}
bool PhoneScript_Random4(script_s* s) {
    SCRIPT_BEGIN
    srandom(4)
    s_end
    SCRIPT_END
}
bool PhoneScript_Random5(script_s* s) {
    SCRIPT_BEGIN
    srandom(5)
    s_end
    SCRIPT_END
}
bool PhoneScript_Random11(script_s* s) {
    SCRIPT_BEGIN
    srandom(11)
    s_end
    SCRIPT_END
}
bool PhoneScript_AnswerPhone_Male(script_s* s) {
    SCRIPT_BEGIN
    checktime(DAY)
    iftrue_jump(PhoneScript_AnswerPhone_Male_Day)
    checktime(NITE)
    iftrue_jump(PhoneScript_AnswerPhone_Male_Nite)
    readvar(VAR_CALLERID)
    ifequal(PHONE_SCHOOLBOY_JACK, Jack)
    ifequal(PHONE_SAILOR_HUEY, Huey)
    ifequal(PHONE_COOLTRAINERM_GAVEN, Gaven)
    ifequal(PHONE_BIRDKEEPER_JOSE, Jose)
    ifequal(PHONE_YOUNGSTER_JOEY, Joey)
    ifequal(PHONE_BUG_CATCHER_WADE, Wade)
    ifequal(PHONE_FISHER_RALPH, Ralph)
    ifequal(PHONE_HIKER_ANTHONY, Anthony)
    ifequal(PHONE_CAMPER_TODD, Todd)
    ifequal(PHONE_JUGGLER_IRWIN, Irwin)
    ifequal(PHONE_BUG_CATCHER_ARNIE, Arnie)
    ifequal(PHONE_SCHOOLBOY_ALAN, Alan)
    ifequal(PHONE_SCHOOLBOY_CHAD, Chad)
    ifequal(PHONE_POKEFANM_DEREK, Derek)
    ifequal(PHONE_FISHER_TULLY, Tully)
    ifequal(PHONE_POKEMANIAC_BRENT, Brent)
    ifequal(PHONE_BIRDKEEPER_VANCE, Vance)
    ifequal(PHONE_FISHER_WILTON, Wilton)
    ifequal(PHONE_BLACKBELT_KENJI, Kenji)
    ifequal(PHONE_HIKER_PARRY, Parry)
Jack:
    writetext(JackAnswerPhoneText)
    promptbutton
    s_end
Huey:
    writetext(HueyAnswerPhoneText)
    promptbutton
    s_end
Gaven:
    writetext(GavenAnswerPhoneText)
    promptbutton
    s_end
Jose:
    writetext(JoseAnswerPhoneText)
    promptbutton
    s_end
Joey:
    writetext(JoeyAnswerPhoneText)
    promptbutton
    s_end
Wade:
    writetext(WadeAnswerPhoneText)
    promptbutton
    s_end
Ralph:
    writetext(RalphAnswerPhoneText)
    promptbutton
    s_end
Anthony:
    writetext(AnthonyAnswerPhoneText)
    promptbutton
    s_end
Todd:
    writetext(ToddAnswerPhoneText)
    promptbutton
    s_end
Irwin:
    writetext(IrwinAnswerPhoneText)
    promptbutton
    s_end
Arnie:
    writetext(ArnieAnswerPhoneText)
    promptbutton
    s_end
Alan:
    writetext(AlanAnswerPhoneText)
    promptbutton
    s_end
Chad:
    writetext(ChadAnswerPhoneText)
    promptbutton
    s_end
Derek:
    writetext(DerekAnswerPhoneText)
    promptbutton
    s_end
Tully:
    writetext(TullyAnswerPhoneText)
    promptbutton
    s_end
Brent:
    writetext(BrentAnswerPhoneText)
    promptbutton
    s_end
Vance:
    writetext(VanceAnswerPhoneText)
    promptbutton
    s_end
Wilton:
    writetext(WiltonAnswerPhoneText)
    promptbutton
    s_end
Kenji:
    writetext(KenjiAnswerPhoneText)
    promptbutton
    s_end
Parry:
    writetext(ParryAnswerPhoneText)
    promptbutton
    s_end
    SCRIPT_END
}
bool PhoneScript_AnswerPhone_Male_Day(script_s* s) {
    SCRIPT_BEGIN
    readvar(VAR_CALLERID)
    ifequal(PHONE_SCHOOLBOY_JACK, Jack)
    ifequal(PHONE_SAILOR_HUEY, Huey)
    ifequal(PHONE_COOLTRAINERM_GAVEN, Gaven)
    ifequal(PHONE_BIRDKEEPER_JOSE, Jose)
    ifequal(PHONE_YOUNGSTER_JOEY, Joey)
    ifequal(PHONE_BUG_CATCHER_WADE, Wade)
    ifequal(PHONE_FISHER_RALPH, Ralph)
    ifequal(PHONE_HIKER_ANTHONY, Anthony)
    ifequal(PHONE_CAMPER_TODD, Todd)
    ifequal(PHONE_JUGGLER_IRWIN, Irwin)
    ifequal(PHONE_BUG_CATCHER_ARNIE, Arnie)
    ifequal(PHONE_SCHOOLBOY_ALAN, Alan)
    ifequal(PHONE_SCHOOLBOY_CHAD, Chad)
    ifequal(PHONE_POKEFANM_DEREK, Derek)
    ifequal(PHONE_FISHER_TULLY, Tully)
    ifequal(PHONE_POKEMANIAC_BRENT, Brent)
    ifequal(PHONE_BIRDKEEPER_VANCE, Vance)
    ifequal(PHONE_FISHER_WILTON, Wilton)
    ifequal(PHONE_BLACKBELT_KENJI, Kenji)
    ifequal(PHONE_HIKER_PARRY, Parry)
Jack:
    writetext(JackAnswerPhoneDayText)
    promptbutton
    s_end
Huey:
    writetext(HueyAnswerPhoneDayText)
    promptbutton
    s_end
Gaven:
    writetext(GavenAnswerPhoneDayText)
    promptbutton
    s_end
Jose:
    writetext(JoseAnswerPhoneDayText)
    promptbutton
    s_end
Joey:
    writetext(JoeyAnswerPhoneDayText)
    promptbutton
    s_end
Wade:
    writetext(WadeAnswerPhoneDayText)
    promptbutton
    s_end
Ralph:
    writetext(RalphAnswerPhoneDayText)
    promptbutton
    s_end
Anthony:
    writetext(AnthonyAnswerPhoneDayText)
    promptbutton
    s_end
Todd:
    writetext(ToddAnswerPhoneDayText)
    promptbutton
    s_end
Irwin:
    writetext(IrwinAnswerPhoneDayText)
    promptbutton
    s_end
Arnie:
    writetext(ArnieAnswerPhoneDayText)
    promptbutton
    s_end
Alan:
    writetext(AlanAnswerPhoneDayText)
    promptbutton
    s_end
Chad:
    writetext(ChadAnswerPhoneDayText)
    promptbutton
    s_end
Derek:
    writetext(DerekAnswerPhoneDayText)
    promptbutton
    s_end
Tully:
    writetext(TullyAnswerPhoneDayText)
    promptbutton
    s_end
Brent:
    writetext(BrentAnswerPhoneDayText)
    promptbutton
    s_end
Vance:
    writetext(VanceAnswerPhoneDayText)
    promptbutton
    s_end
Wilton:
    writetext(WiltonAnswerPhoneDayText)
    promptbutton
    s_end
Kenji:
    writetext(KenjiAnswerPhoneDayText)
    promptbutton
    s_end
Parry:
    writetext(ParryAnswerPhoneDayText)
    promptbutton
    s_end
    SCRIPT_END
}
bool PhoneScript_AnswerPhone_Male_Nite(script_s* s) {
    SCRIPT_BEGIN
    readvar(VAR_CALLERID)
    ifequal(PHONE_SCHOOLBOY_JACK, Jack)
    ifequal(PHONE_SAILOR_HUEY, Huey)
    ifequal(PHONE_COOLTRAINERM_GAVEN, Gaven)
    ifequal(PHONE_BIRDKEEPER_JOSE, Jose)
    ifequal(PHONE_YOUNGSTER_JOEY, Joey)
    ifequal(PHONE_BUG_CATCHER_WADE, Wade)
    ifequal(PHONE_FISHER_RALPH, Ralph)
    ifequal(PHONE_HIKER_ANTHONY, Anthony)
    ifequal(PHONE_CAMPER_TODD, Todd)
    ifequal(PHONE_JUGGLER_IRWIN, Irwin)
    ifequal(PHONE_BUG_CATCHER_ARNIE, Arnie)
    ifequal(PHONE_SCHOOLBOY_ALAN, Alan)
    ifequal(PHONE_SCHOOLBOY_CHAD, Chad)
    ifequal(PHONE_POKEFANM_DEREK, Derek)
    ifequal(PHONE_FISHER_TULLY, Tully)
    ifequal(PHONE_POKEMANIAC_BRENT, Brent)
    ifequal(PHONE_BIRDKEEPER_VANCE, Vance)
    ifequal(PHONE_FISHER_WILTON, Wilton)
    ifequal(PHONE_BLACKBELT_KENJI, Kenji)
    ifequal(PHONE_HIKER_PARRY, Parry)
Jack:
    writetext(JackAnswerPhoneNiteText)
    promptbutton
    s_end
Huey:
    writetext(HueyAnswerPhoneNiteText)
    promptbutton
    s_end
Gaven:
    writetext(GavenAnswerPhoneNiteText)
    promptbutton
    s_end
Jose:
    writetext(JoseAnswerPhoneNiteText)
    promptbutton
    s_end
Joey:
    writetext(JoeyAnswerPhoneNiteText)
    promptbutton
    s_end
Wade:
    writetext(WadeAnswerPhoneNiteText)
    promptbutton
    s_end
Ralph:
    writetext(RalphAnswerPhoneNiteText)
    promptbutton
    s_end
Anthony:
    writetext(AnthonyAnswerPhoneNiteText)
    promptbutton
    s_end
Todd:
    writetext(ToddAnswerPhoneNiteText)
    promptbutton
    s_end
Irwin:
    writetext(IrwinAnswerPhoneNiteText)
    promptbutton
    s_end
Arnie:
    writetext(ArnieAnswerPhoneNiteText)
    promptbutton
    s_end
Alan:
    writetext(AlanAnswerPhoneNiteText)
    promptbutton
    s_end
Chad:
    writetext(ChadAnswerPhoneNiteText)
    promptbutton
    s_end
Derek:
    writetext(DerekAnswerPhoneNiteText)
    promptbutton
    s_end
Tully:
    writetext(TullyAnswerPhoneNiteText)
    promptbutton
    s_end
Brent:
    writetext(BrentAnswerPhoneNiteText)
    promptbutton
    s_end
Vance:
    writetext(VanceAnswerPhoneNiteText)
    promptbutton
    s_end
Wilton:
    writetext(WiltonAnswerPhoneNiteText)
    promptbutton
    s_end
Kenji:
    writetext(KenjiAnswerPhoneNiteText)
    promptbutton
    s_end
Parry:
    writetext(ParryAnswerPhoneNiteText)
    promptbutton
    s_end
    SCRIPT_END
}
bool PhoneScript_AnswerPhone_Female(script_s* s) {
    SCRIPT_BEGIN
    checktime(DAY)
    iftrue_jump(PhoneScript_AnswerPhone_Female_Day)
    checktime(NITE)
    iftrue_jump(PhoneScript_AnswerPhone_Female_Nite)
    readvar(VAR_CALLERID)
    ifequal(PHONE_POKEFAN_BEVERLY, Beverly)
    ifequal(PHONE_COOLTRAINERF_BETH, Beth)
    ifequal(PHONE_COOLTRAINERF_REENA, Reena)
    ifequal(PHONE_PICNICKER_LIZ, Liz)
    ifequal(PHONE_PICNICKER_GINA, Gina)
    ifequal(PHONE_LASS_DANA, Dana)
    ifequal(PHONE_PICNICKER_TIFFANY, Tiffany)
    ifequal(PHONE_PICNICKER_ERIN, Erin)
Beverly:
    writetext(BeverlyAnswerPhoneText)
    promptbutton
    s_end
Beth:
    writetext(BethAnswerPhoneText)
    promptbutton
    s_end
Reena:
    writetext(ReenaAnswerPhoneText)
    promptbutton
    s_end
Liz:
    writetext(LizAnswerPhoneText)
    promptbutton
    s_end
Gina:
    writetext(GinaAnswerPhoneText)
    promptbutton
    s_end
Dana:
    writetext(DanaAnswerPhoneText)
    promptbutton
    s_end
Tiffany:
    writetext(TiffanyAnswerPhoneText)
    promptbutton
    s_end
Erin:
    writetext(ErinAnswerPhoneText)
    promptbutton
    s_end
    SCRIPT_END
}
bool PhoneScript_AnswerPhone_Female_Day(script_s* s) {
    SCRIPT_BEGIN
    readvar(VAR_CALLERID)
    ifequal(PHONE_POKEFAN_BEVERLY, Beverly)
    ifequal(PHONE_COOLTRAINERF_BETH, Beth)
    ifequal(PHONE_COOLTRAINERF_REENA, Reena)
    ifequal(PHONE_PICNICKER_LIZ, Liz)
    ifequal(PHONE_PICNICKER_GINA, Gina)
    ifequal(PHONE_LASS_DANA, Dana)
    ifequal(PHONE_PICNICKER_TIFFANY, Tiffany)
    ifequal(PHONE_PICNICKER_ERIN, Erin)
Beverly:
    writetext(BeverlyAnswerPhoneDayText)
    promptbutton
    s_end
Beth:
    writetext(BethAnswerPhoneDayText)
    promptbutton
    s_end
Reena:
    writetext(ReenaAnswerPhoneDayText)
    promptbutton
    s_end
Liz:
    writetext(LizAnswerPhoneDayText)
    promptbutton
    s_end
Gina:
    writetext(GinaAnswerPhoneDayText)
    promptbutton
    s_end
Dana:
    writetext(DanaAnswerPhoneDayText)
    promptbutton
    s_end
Tiffany:
    writetext(TiffanyAnswerPhoneDayText)
    promptbutton
    s_end
Erin:
    writetext(ErinAnswerPhoneDayText)
    promptbutton
    s_end
    SCRIPT_END
}
bool PhoneScript_AnswerPhone_Female_Nite(script_s* s) {
    SCRIPT_BEGIN
    readvar(VAR_CALLERID)
    ifequal(PHONE_POKEFAN_BEVERLY, Beverly)
    ifequal(PHONE_COOLTRAINERF_BETH, Beth)
    ifequal(PHONE_COOLTRAINERF_REENA, Reena)
    ifequal(PHONE_PICNICKER_LIZ, Liz)
    ifequal(PHONE_PICNICKER_GINA, Gina)
    ifequal(PHONE_LASS_DANA, Dana)
    ifequal(PHONE_PICNICKER_TIFFANY, Tiffany)
    ifequal(PHONE_PICNICKER_ERIN, Erin)
Beverly:
    writetext(BeverlyAnswerPhoneNiteText)
    promptbutton
    s_end
Beth:
    writetext(BethAnswerPhoneNiteText)
    promptbutton
    s_end
Reena:
    writetext(ReenaAnswerPhoneNiteText)
    promptbutton
    s_end
Liz:
    writetext(LizAnswerPhoneNiteText)
    promptbutton
    s_end
Gina:
    writetext(GinaAnswerPhoneNiteText)
    promptbutton
    s_end
Dana:
    writetext(DanaAnswerPhoneNiteText)
    promptbutton
    s_end
Tiffany:
    writetext(TiffanyAnswerPhoneNiteText)
    promptbutton
    s_end
Erin:
    writetext(ErinAnswerPhoneNiteText)
    promptbutton
    s_end
    SCRIPT_END
}
bool PhoneScript_GreetPhone_Male(script_s* s) {
    SCRIPT_BEGIN
    checktime(DAY)
    iftrue_jump(PhoneScript_GreetPhone_Male_Day)
    checktime(NITE)
    iftrue_jump(PhoneScript_GreetPhone_Male_Nite)
    readvar(VAR_CALLERID)
    ifequal(PHONE_SCHOOLBOY_JACK, Jack)
    ifequal(PHONE_SAILOR_HUEY, Huey)
    ifequal(PHONE_COOLTRAINERM_GAVEN, Gaven)
    ifequal(PHONE_BIRDKEEPER_JOSE, Jose)
    ifequal(PHONE_YOUNGSTER_JOEY, Joey)
    ifequal(PHONE_BUG_CATCHER_WADE, Wade)
    ifequal(PHONE_FISHER_RALPH, Ralph)
    ifequal(PHONE_HIKER_ANTHONY, Anthony)
    ifequal(PHONE_CAMPER_TODD, Todd)
    ifequal(PHONE_JUGGLER_IRWIN, Irwin)
    ifequal(PHONE_BUG_CATCHER_ARNIE, Arnie)
    ifequal(PHONE_SCHOOLBOY_ALAN, Alan)
    ifequal(PHONE_SCHOOLBOY_CHAD, Chad)
    ifequal(PHONE_POKEFANM_DEREK, Derek)
    ifequal(PHONE_FISHER_TULLY, Tully)
    ifequal(PHONE_POKEMANIAC_BRENT, Brent)
    ifequal(PHONE_BIRDKEEPER_VANCE, Vance)
    ifequal(PHONE_FISHER_WILTON, Wilton)
    ifequal(PHONE_BLACKBELT_KENJI, Kenji)
    ifequal(PHONE_HIKER_PARRY, Parry)
Jack:
    writetext(JackGreetText)
    promptbutton
    s_end
Huey:
    writetext(HueyGreetText)
    promptbutton
    s_end
Gaven:
    writetext(GavenGreetText)
    promptbutton
    s_end
Jose:
    writetext(JoseGreetText)
    promptbutton
    s_end
Joey:
    writetext(JoeyGreetText)
    promptbutton
    s_end
Wade:
    writetext(WadeGreetText)
    promptbutton
    s_end
Ralph:
    writetext(RalphGreetText)
    promptbutton
    s_end
Anthony:
    writetext(AnthonyGreetText)
    promptbutton
    s_end
Todd:
    writetext(ToddGreetText)
    promptbutton
    s_end
Irwin:
    writetext(IrwinGreetText)
    promptbutton
    s_end
Arnie:
    writetext(ArnieGreetText)
    promptbutton
    s_end
Alan:
    writetext(AlanGreetText)
    promptbutton
    s_end
Chad:
    writetext(ChadGreetText)
    promptbutton
    s_end
Derek:
    writetext(DerekGreetText)
    promptbutton
    s_end
Tully:
    writetext(TullyGreetText)
    promptbutton
    s_end
Brent:
    writetext(BrentGreetText)
    promptbutton
    s_end
Vance:
    writetext(VanceGreetText)
    promptbutton
    s_end
Wilton:
    writetext(WiltonGreetText)
    promptbutton
    s_end
Kenji:
    writetext(KenjiGreetText)
    promptbutton
    s_end
Parry:
    writetext(ParryGreetText)
    promptbutton
    s_end
    SCRIPT_END
}
bool PhoneScript_GreetPhone_Male_Day(script_s* s) {
    SCRIPT_BEGIN
    readvar(VAR_CALLERID)
    ifequal(PHONE_SCHOOLBOY_JACK, Jack)
    ifequal(PHONE_SAILOR_HUEY, Huey)
    ifequal(PHONE_COOLTRAINERM_GAVEN, Gaven)
    ifequal(PHONE_BIRDKEEPER_JOSE, Jose)
    ifequal(PHONE_YOUNGSTER_JOEY, Joey)
    ifequal(PHONE_BUG_CATCHER_WADE, Wade)
    ifequal(PHONE_FISHER_RALPH, Ralph)
    ifequal(PHONE_HIKER_ANTHONY, Anthony)
    ifequal(PHONE_CAMPER_TODD, Todd)
    ifequal(PHONE_JUGGLER_IRWIN, Irwin)
    ifequal(PHONE_BUG_CATCHER_ARNIE, Arnie)
    ifequal(PHONE_SCHOOLBOY_ALAN, Alan)
    ifequal(PHONE_SCHOOLBOY_CHAD, Chad)
    ifequal(PHONE_POKEFANM_DEREK, Derek)
    ifequal(PHONE_FISHER_TULLY, Tully)
    ifequal(PHONE_POKEMANIAC_BRENT, Brent)
    ifequal(PHONE_BIRDKEEPER_VANCE, Vance)
    ifequal(PHONE_FISHER_WILTON, Wilton)
    ifequal(PHONE_BLACKBELT_KENJI, Kenji)
    ifequal(PHONE_HIKER_PARRY, Parry)
Jack:
    writetext(JackGreetDayText)
    promptbutton
    s_end
Huey:
    writetext(HueyGreetDayText)
    promptbutton
    s_end
Gaven:
    writetext(GavenGreetDayText)
    promptbutton
    s_end
Jose:
    writetext(JoseGreetDayText)
    promptbutton
    s_end
Joey:
    writetext(JoeyGreetDayText)
    promptbutton
    s_end
Wade:
    writetext(WadeGreetDayText)
    promptbutton
    s_end
Ralph:
    writetext(RalphGreetDayText)
    promptbutton
    s_end
Anthony:
    writetext(AnthonyGreetDayText)
    promptbutton
    s_end
Todd:
    writetext(ToddGreetDayText)
    promptbutton
    s_end
Irwin:
    writetext(IrwinGreetDayText)
    promptbutton
    s_end
Arnie:
    writetext(ArnieGreetDayText)
    promptbutton
    s_end
Alan:
    writetext(AlanGreetDayText)
    promptbutton
    s_end
Chad:
    writetext(ChadGreetDayText)
    promptbutton
    s_end
Derek:
    writetext(DerekGreetDayText)
    promptbutton
    s_end
Tully:
    writetext(TullyGreetDayText)
    promptbutton
    s_end
Brent:
    writetext(BrentGreetDayText)
    promptbutton
    s_end
Vance:
    writetext(VanceGreetDayText)
    promptbutton
    s_end
Wilton:
    writetext(WiltonGreetDayText)
    promptbutton
    s_end
Kenji:
    writetext(KenjiGreetDayText)
    promptbutton
    s_end
Parry:
    writetext(ParryGreetDayText)
    promptbutton
    s_end
    SCRIPT_END
}
bool PhoneScript_GreetPhone_Male_Nite(script_s* s) {
    SCRIPT_BEGIN
    readvar(VAR_CALLERID)
    ifequal(PHONE_SCHOOLBOY_JACK, Jack)
    ifequal(PHONE_SAILOR_HUEY, Huey)
    ifequal(PHONE_COOLTRAINERM_GAVEN, Gaven)
    ifequal(PHONE_BIRDKEEPER_JOSE, Jose)
    ifequal(PHONE_YOUNGSTER_JOEY, Joey)
    ifequal(PHONE_BUG_CATCHER_WADE, Wade)
    ifequal(PHONE_FISHER_RALPH, Ralph)
    ifequal(PHONE_HIKER_ANTHONY, Anthony)
    ifequal(PHONE_CAMPER_TODD, Todd)
    ifequal(PHONE_JUGGLER_IRWIN, Irwin)
    ifequal(PHONE_BUG_CATCHER_ARNIE, Arnie)
    ifequal(PHONE_SCHOOLBOY_ALAN, Alan)
    ifequal(PHONE_SCHOOLBOY_CHAD, Chad)
    ifequal(PHONE_POKEFANM_DEREK, Derek)
    ifequal(PHONE_FISHER_TULLY, Tully)
    ifequal(PHONE_POKEMANIAC_BRENT, Brent)
    ifequal(PHONE_BIRDKEEPER_VANCE, Vance)
    ifequal(PHONE_FISHER_WILTON, Wilton)
    ifequal(PHONE_BLACKBELT_KENJI, Kenji)
    ifequal(PHONE_HIKER_PARRY, Parry)
Jack:
    writetext(JackGreetNiteText)
    promptbutton
    s_end
Huey:
    writetext(HueyGreetNiteText)
    promptbutton
    s_end
Gaven:
    writetext(GavenGreetNiteText)
    promptbutton
    s_end
Jose:
    writetext(JoseGreetNiteText)
    promptbutton
    s_end
Joey:
    writetext(JoeyGreetNiteText)
    promptbutton
    s_end
Wade:
    writetext(WadeGreetNiteText)
    promptbutton
    s_end
Ralph:
    writetext(RalphGreetNiteText)
    promptbutton
    s_end
Anthony:
    writetext(AnthonyGreetNiteText)
    promptbutton
    s_end
Todd:
    writetext(ToddGreetNiteText)
    promptbutton
    s_end
Irwin:
    writetext(IrwinGreetNiteText)
    promptbutton
    s_end
Arnie:
    writetext(ArnieGreetNiteText)
    promptbutton
    s_end
Alan:
    writetext(AlanGreetNiteText)
    promptbutton
    s_end
Chad:
    writetext(ChadGreetNiteText)
    promptbutton
    s_end
Derek:
    writetext(DerekGreetNiteText)
    promptbutton
    s_end
Tully:
    writetext(TullyGreetNiteText)
    promptbutton
    s_end
Brent:
    writetext(BrentGreetNiteText)
    promptbutton
    s_end
Vance:
    writetext(VanceGreetNiteText)
    promptbutton
    s_end
Wilton:
    writetext(WiltonGreetNiteText)
    promptbutton
    s_end
Kenji:
    writetext(KenjiGreetNiteText)
    promptbutton
    s_end
Parry:
    writetext(ParryGreetNiteText)
    promptbutton
    s_end
    SCRIPT_END
}
bool PhoneScript_GreetPhone_Female(script_s* s) {
    SCRIPT_BEGIN
    checktime(DAY)
    iftrue_jump(PhoneScript_GreetPhone_Female_Day)
    checktime(NITE)
    iftrue_jump(PhoneScript_GreetPhone_Female_Nite)
    readvar(VAR_CALLERID)
    ifequal(PHONE_POKEFAN_BEVERLY, Beverly)
    ifequal(PHONE_COOLTRAINERF_BETH, Beth)
    ifequal(PHONE_COOLTRAINERF_REENA, Reena)
    ifequal(PHONE_PICNICKER_LIZ, Liz)
    ifequal(PHONE_PICNICKER_GINA, Gina)
    ifequal(PHONE_LASS_DANA, Dana)
    ifequal(PHONE_PICNICKER_TIFFANY, Tiffany)
    ifequal(PHONE_PICNICKER_ERIN, Erin)
Beverly:
    writetext(BeverlyGreetText)
    promptbutton
    s_end
Beth:
    writetext(BethGreetText)
    promptbutton
    s_end
Reena:
    writetext(ReenaGreetText)
    promptbutton
    s_end
Liz:
    writetext(LizGreetText)
    promptbutton
    s_end
Gina:
    writetext(GinaGreetText)
    promptbutton
    s_end
Dana:
    writetext(DanaGreetText)
    promptbutton
    s_end
Tiffany:
    writetext(TiffanyGreetText)
    promptbutton
    s_end
Erin:
    writetext(ErinGreetText)
    promptbutton
    s_end
    SCRIPT_END
}
bool PhoneScript_GreetPhone_Female_Day(script_s* s) {
    SCRIPT_BEGIN
    readvar(VAR_CALLERID)
    ifequal(PHONE_POKEFAN_BEVERLY, Beverly)
    ifequal(PHONE_COOLTRAINERF_BETH, Beth)
    ifequal(PHONE_COOLTRAINERF_REENA, Reena)
    ifequal(PHONE_PICNICKER_LIZ, Liz)
    ifequal(PHONE_PICNICKER_GINA, Gina)
    ifequal(PHONE_LASS_DANA, Dana)
    ifequal(PHONE_PICNICKER_TIFFANY, Tiffany)
    ifequal(PHONE_PICNICKER_ERIN, Erin)
Beverly:
    writetext(BeverlyGreetDayText)
    promptbutton
    s_end
Beth:
    writetext(BethGreetDayText)
    promptbutton
    s_end
Reena:
    writetext(ReenaGreetDayText)
    promptbutton
    s_end
Liz:
    writetext(LizGreetDayText)
    promptbutton
    s_end
Gina:
    writetext(GinaGreetDayText)
    promptbutton
    s_end
Dana:
    writetext(DanaGreetDayText)
    promptbutton
    s_end
Tiffany:
    writetext(TiffanyGreetDayText)
    promptbutton
    s_end
Erin:
    writetext(ErinGreetDayText)
    promptbutton
    s_end
    SCRIPT_END
}
bool PhoneScript_GreetPhone_Female_Nite(script_s* s) {
    SCRIPT_BEGIN
    readvar(VAR_CALLERID)
    ifequal(PHONE_POKEFAN_BEVERLY, Beverly)
    ifequal(PHONE_COOLTRAINERF_BETH, Beth)
    ifequal(PHONE_COOLTRAINERF_REENA, Reena)
    ifequal(PHONE_PICNICKER_LIZ, Liz)
    ifequal(PHONE_PICNICKER_GINA, Gina)
    ifequal(PHONE_LASS_DANA, Dana)
    ifequal(PHONE_PICNICKER_TIFFANY, Tiffany)
    ifequal(PHONE_PICNICKER_ERIN, Erin)
Beverly:
    writetext(BeverlyGreetNiteText)
    promptbutton
    s_end
Beth:
    writetext(BethGreetNiteText)
    promptbutton
    s_end
Reena:
    writetext(ReenaGreetNiteText)
    promptbutton
    s_end
Liz:
    writetext(LizGreetNiteText)
    promptbutton
    s_end
Gina:
    writetext(GinaGreetNiteText)
    promptbutton
    s_end
Dana:
    writetext(DanaGreetNiteText)
    promptbutton
    s_end
Tiffany:
    writetext(TiffanyGreetNiteText)
    promptbutton
    s_end
Erin:
    writetext(ErinGreetNiteText)
    promptbutton
    s_end
    SCRIPT_END
}
bool PhoneScript_Generic_Male(script_s* s) {
    SCRIPT_BEGIN
    readvar(VAR_CALLERID)
    ifequal(PHONE_SCHOOLBOY_JACK, Jack)
    ifequal(PHONE_COOLTRAINERM_GAVEN, Gaven)
    ifequal(PHONE_BIRDKEEPER_JOSE, Jose)
    ifequal(PHONE_YOUNGSTER_JOEY, Joey)
    ifequal(PHONE_BUG_CATCHER_WADE, Wade)
    ifequal(PHONE_FISHER_RALPH, Ralph)
    ifequal(PHONE_HIKER_ANTHONY, Anthony)
    ifequal(PHONE_CAMPER_TODD, Todd)
    ifequal(PHONE_BUG_CATCHER_ARNIE, Arnie)
    ifequal(PHONE_SCHOOLBOY_ALAN, Alan)
    ifequal(PHONE_SCHOOLBOY_CHAD, Chad)
    ifequal(PHONE_POKEFANM_DEREK, Derek)
    ifequal(PHONE_FISHER_TULLY, Tully)
    ifequal(PHONE_POKEMANIAC_BRENT, Brent)
    ifequal(PHONE_BIRDKEEPER_VANCE, Vance)
    ifequal(PHONE_FISHER_WILTON, Wilton)
    ifequal(PHONE_HIKER_PARRY, Parry)
Jack:
    writetext(JackGenericText)
    promptbutton
    s_end
Unknown:
    writetext(UnknownGenericText)
    promptbutton
    s_end
Gaven:
    writetext(GavenGenericText)
    promptbutton
    s_end
Jose:
    writetext(JoseGenericText)
    promptbutton
    s_end
Joey:
    writetext(JoeyGenericText)
    promptbutton
    s_end
Wade:
    writetext(WadeGenericText)
    promptbutton
    s_end
Ralph:
    writetext(RalphGenericText)
    promptbutton
    s_end
Anthony:
    writetext(AnthonyGenericText)
    promptbutton
    s_end
Todd:
    writetext(ToddGenericText)
    promptbutton
    s_end
Arnie:
    writetext(ArnieGenericText)
    promptbutton
    s_end
Alan:
    writetext(AlanGenericText)
    promptbutton
    s_end
Chad:
    writetext(ChadGenericText)
    promptbutton
    s_end
Derek:
    writetext(DerekGenericText)
    promptbutton
    s_end
Tully:
    writetext(TullyGenericText)
    promptbutton
    s_end
Brent:
    writetext(BrentGenericText)
    promptbutton
    s_end
Vance:
    writetext(VanceGenericText)
    promptbutton
    s_end
Wilton:
    writetext(WiltonGenericText)
    promptbutton
    s_end
Parry:
    writetext(ParryGenericText)
    promptbutton
    s_end
    SCRIPT_END
}
bool PhoneScript_Generic_Female(script_s* s) {
    SCRIPT_BEGIN
    readvar(VAR_CALLERID)
    ifequal(PHONE_POKEFAN_BEVERLY, Beverly)
    ifequal(PHONE_COOLTRAINERF_BETH, Beth)
    ifequal(PHONE_COOLTRAINERF_REENA, Reena)
    ifequal(PHONE_PICNICKER_LIZ, Liz)
    ifequal(PHONE_PICNICKER_GINA, Gina)
    ifequal(PHONE_LASS_DANA, Dana)
    ifequal(PHONE_PICNICKER_TIFFANY, Tiffany)
    ifequal(PHONE_PICNICKER_ERIN, Erin)
Beverly:
    writetext(BeverlyGenericText)
    promptbutton
    s_end
Beth:
    writetext(BethGenericText)
    promptbutton
    s_end
Reena:
    writetext(ReenaGenericText)
    promptbutton
    s_end
Liz:
    writetext(LizGenericText)
    promptbutton
    s_end
Gina:
    writetext(GinaGenericText)
    promptbutton
    s_end
Dana:
    writetext(DanaGenericText)
    promptbutton
    s_end
Tiffany:
    writetext(TiffanyGenericText)
    promptbutton
    s_end
Erin:
    writetext(ErinGenericText)
    promptbutton
    s_end
    SCRIPT_END
}
bool PhoneScript_MonFlavorText(script_s* s) {
    SCRIPT_BEGIN
    special(RandomPhoneMon)
    scall(PhoneScript_Random2)
    ifequal(0x0, TooEnergetic)
    writetext(UnknownGenericText)
    promptbutton
    sjump(PhoneScript_HangUpText_Male)
TooEnergetic:
    // sjump(.unnecessary)
unnecessary:
    writetext(UnknownTougherThanEverText)
    promptbutton
    sjump(PhoneScript_HangUpText_Male)
    SCRIPT_END
}
const char GrandmaString[] = "Grandma@";
const char GrandpaString[] = "Grandpa@";
const char MomString[] = "Mom@";
const char DadString[] = "Dad@";
const char SisterString[] = "Sister@";
const char BrotherString[] = "Brother@";
