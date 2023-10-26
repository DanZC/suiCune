#include "../../../constants.h"
#include "../../../util/scripting.h"
#include "generic_callee.h"
#include "generic_caller.h"
#include "../../../data/phone/text/jack_caller.h"
#include "../../../data/phone/text/beverly_caller.h"
#include "../../../data/phone/text/huey_caller.h"
#include "../../../data/phone/text/gaven_caller.h"
#include "../../../data/phone/text/beth_caller.h"
#include "../../../data/phone/text/jose_caller.h"
#include "../../../data/phone/text/reena_caller.h"
#include "../../../data/phone/text/joey_caller.h"
#include "../../../data/phone/text/wade_caller.h"
#include "../../../data/phone/text/ralph_caller.h"
#include "../../../data/phone/text/liz_caller.h"
#include "../../../data/phone/text/anthony_caller.h"
#include "../../../data/phone/text/todd_caller.h"
#include "../../../data/phone/text/gina_caller.h"
#include "../../../data/phone/text/irwin_caller.h"
#include "../../../data/phone/text/arnie_caller.h"
#include "../../../data/phone/text/alan_caller.h"
#include "../../../data/phone/text/dana_caller.h"
#include "../../../data/phone/text/chad_caller.h"
#include "../../../data/phone/text/derek_caller.h"
#include "../../../data/phone/text/tully_caller.h"
#include "../../../data/phone/text/brent_caller.h"
#include "../../../data/phone/text/tiffany_caller.h"
#include "../../../data/phone/text/vance_caller.h"
#include "../../../data/phone/text/wilton_caller.h"
#include "../../../data/phone/text/parry_caller.h"
#include "../../../data/phone/text/erin_caller.h"
#include "../../../data/phone/text/kenji_caller.h"

bool Phone_GenericCall_Male(script_s* s) {
    SCRIPT_BEGIN
    special(RandomPhoneMon)
    scall(PhoneScript_Random2)
    ifequal(0, Bragging)
    scall(PhoneScript_Generic_Male)
    sjump(Phone_FoundAMon_Male)
Bragging:
    sjump(Phone_BraggingCall_Male)
    SCRIPT_END
}
bool Phone_GenericCall_Female(script_s* s) {
    SCRIPT_BEGIN
    special(RandomPhoneMon)
    scall(PhoneScript_Random2)
    ifequal(0, Bragging)
    scall(PhoneScript_Generic_Female)
    sjump(Phone_FoundAMon_Female)
Bragging:
    sjump(Phone_BraggingCall_Female)
    SCRIPT_END
}
bool Phone_BraggingCall_Male(script_s* s) {
    SCRIPT_BEGIN
    scall(Phone_WhosBragging_Male)
    sjump(Phone_FoundAMon_Male)
    SCRIPT_END
}
bool Phone_BraggingCall_Female(script_s* s) {
    SCRIPT_BEGIN
    scall(Phone_WhosBragging_Female)
    sjump(Phone_FoundAMon_Female)
    SCRIPT_END
}
bool Phone_FoundAMon_Male(script_s* s) {
    SCRIPT_BEGIN
    special(RandomPhoneWildMon)
    scall(PhoneScript_Random2)
    ifequal(0, GotAway)
    scall(Phone_WhoDefeatedMon_Male)
    sjump(PhoneScript_HangUpText_Male)
GotAway:
    sjump(Phone_GotAwayCall_Male)
    SCRIPT_END
}
bool Phone_FoundAMon_Female(script_s* s) {
    SCRIPT_BEGIN
    special(RandomPhoneWildMon)
    scall(PhoneScript_Random2)
    ifequal(0, GotAway)
    scall(Phone_WhoDefeatedMon_Female)
    sjump(PhoneScript_HangUpText_Female)
GotAway:
    sjump(Phone_GotAwayCall_Female)
    SCRIPT_END
}
bool Phone_GotAwayCall_Male(script_s* s) {
    SCRIPT_BEGIN
    scall(Phone_WhoLostAMon_Male)
    sjump(PhoneScript_HangUpText_Male)
    SCRIPT_END
}
bool Phone_GotAwayCall_Female(script_s* s) {
    SCRIPT_BEGIN
    scall(Phone_WhoLostAMon_Female)
    sjump(PhoneScript_HangUpText_Female)
    SCRIPT_END
}
bool Phone_WhosBragging_Male(script_s* s) {
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
    writetext(JackIntelligenceKeepsRisingText)
    promptbutton
    s_end
Gaven:
    writetext(GavenMonGreaterThanImaginedText)
    promptbutton
    s_end
Jose:
    writetext(JoseMonsStickHasADeliciousAromaText)
    promptbutton
    s_end
Joey:
    writetext(JoeyMonLookingSharperText)
    promptbutton
    s_end
Wade:
    writetext(WadeAreYourMonGrowingText)
    promptbutton
    s_end
Ralph:
    writetext(RalphNeglectingKidsText)
    promptbutton
    s_end
Anthony:
    writetext(AnthonyMonAteSomeBerriesText)
    promptbutton
    s_end
Todd:
    writetext(ToddLooksCuteLikeMeText)
    promptbutton
    s_end
Arnie:
    writetext(ArnieMonIsSoCuteText)
    promptbutton
    s_end
Alan:
    writetext(AlanGettingStrongerText)
    promptbutton
    s_end
Chad:
    writetext(ChadObservingWildText)
    promptbutton
    s_end
Derek:
    writetext(DerekCheekPinchingText)
    promptbutton
    s_end
Tully:
    writetext(TullyMonHasGrownText)
    promptbutton
    s_end
Brent:
    writetext(BrentRareTradeText)
    promptbutton
    s_end
Vance:
    writetext(VanceMonHasBecomeTougherText)
    promptbutton
    s_end
Wilton:
    writetext(WiltonMonHasGrownText)
    promptbutton
    s_end
Parry:
    writetext(ParryNothingCanMatchText)
    promptbutton
    s_end
    SCRIPT_END
}
bool Phone_WhosBragging_Female(script_s* s) {
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
    writetext(BeverlyMadeMonEvenCuterText)
    promptbutton
    s_end
Beth:
    writetext(BethExhilaratingRideText)
    promptbutton
    s_end
Reena:
    writetext(ReenaMonsIsAPerfectMatchText)
    promptbutton
    s_end
Liz:
    writetext(LizMonAlwaysWantsToNuzzleText)
    promptbutton
    s_end
Gina:
    writetext(GinaGettingInSyncWithMonText)
    promptbutton
    s_end
Dana:
    writetext(DanaTakingPhotosText)
    promptbutton
    s_end
Tiffany:
    writetext(TiffanyMonIsAdorableText)
    promptbutton
    s_end
Erin:
    writetext(ErinMonIsMuchStrongerText)
    promptbutton
    s_end
    SCRIPT_END
}
bool Phone_WhoDefeatedMon_Male(script_s* s) {
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
    writetext(JackDefeatedMonText)
    promptbutton
    s_end
Gaven:
    writetext(GavenDefeatedMonText)
    promptbutton
    s_end
Jose:
    writetext(JoseDefeatedMonText)
    promptbutton
    s_end
Joey:
    writetext(JoeyDefeatedMonText)
    promptbutton
    s_end
Wade:
    writetext(WadeDefeatedMonText)
    promptbutton
    s_end
Ralph:
    writetext(RalphDefeatedMonText)
    promptbutton
    s_end
Anthony:
    writetext(AnthonyDefeatedMonText)
    promptbutton
    s_end
Todd:
    writetext(ToddDefeatedMonText)
    promptbutton
    s_end
Arnie:
    writetext(ArnieDefeatedMonText)
    promptbutton
    s_end
Alan:
    writetext(AlanDefeatedMonText)
    promptbutton
    s_end
Chad:
    writetext(ChadDefeatedMonText)
    promptbutton
    s_end
Derek:
    writetext(DerekDefeatedMonText)
    promptbutton
    s_end
Tully:
    writetext(TullyDefeatedMonText)
    promptbutton
    s_end
Brent:
    writetext(BrentDefeatedMonText)
    promptbutton
    s_end
Vance:
    writetext(VanceDefeatedMonText)
    promptbutton
    s_end
Wilton:
    writetext(WiltonDefeatedMonText)
    promptbutton
    s_end
Parry:
    writetext(ParryDefeatedMonText)
    promptbutton
    s_end
    SCRIPT_END
}
bool Phone_WhoDefeatedMon_Female(script_s* s) {
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
    writetext(BeverlyDefeatedMonText)
    promptbutton
    s_end
Beth:
    writetext(BethDefeatedMonText)
    promptbutton
    s_end
Reena:
    writetext(ReenaDefeatedMonText)
    promptbutton
    s_end
Liz:
    writetext(LizDefeatedMonText)
    promptbutton
    s_end
Gina:
    writetext(GinaDefeatedMonText)
    promptbutton
    s_end
Dana:
    writetext(DanaDefeatedMonText)
    promptbutton
    s_end
Tiffany:
    writetext(TiffanyDefeatedMonText)
    promptbutton
    s_end
Erin:
    writetext(ErinDefeatedMonText)
    promptbutton
    s_end
    SCRIPT_END
}
bool Phone_WhoLostAMon_Male(script_s* s) {
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
    writetext(JackLostAMonText)
    promptbutton
    s_end
Gaven:
    writetext(GavenLostAMonText)
    promptbutton
    s_end
Jose:
    writetext(JoseLostAMonText)
    promptbutton
    s_end
Joey:
    writetext(JoeyLostAMonText)
    promptbutton
    s_end
Wade:
    writetext(WadeLostAMonText)
    promptbutton
    s_end
Ralph:
    writetext(RalphLostAMonText)
    promptbutton
    s_end
Anthony:
    writetext(AnthonyLostAMonText)
    promptbutton
    s_end
Todd:
    writetext(ToddLostAMonText)
    promptbutton
    s_end
Arnie:
    writetext(ArnieLostAMonText)
    promptbutton
    s_end
Alan:
    writetext(AlanLostAMonText)
    promptbutton
    s_end
Chad:
    writetext(ChadLostAMonText)
    promptbutton
    s_end
Derek:
    writetext(DerekLostAMonText)
    promptbutton
    s_end
Tully:
    writetext(TullyLostAMonText)
    promptbutton
    s_end
Brent:
    writetext(BrentLostAMonText)
    promptbutton
    s_end
Vance:
    writetext(VanceLostAMonText)
    promptbutton
    s_end
Wilton:
    writetext(WiltonLostAMonText)
    promptbutton
    s_end
Parry:
    writetext(ParryLostAMonText)
    promptbutton
    s_end
    SCRIPT_END
}
bool Phone_WhoLostAMon_Female(script_s* s) {
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
    writetext(BeverlyLostAMonText)
    promptbutton
    s_end
Beth:
    writetext(BethLostAMonText)
    promptbutton
    s_end
Reena:
    writetext(ReenaLostAMonText)
    promptbutton
    s_end
Liz:
    writetext(LizLostAMonText)
    promptbutton
    s_end
Gina:
    writetext(GinaLostAMonText)
    promptbutton
    s_end
Dana:
    writetext(DanaLostAMonText)
    promptbutton
    s_end
Tiffany:
    writetext(TiffanyLostAMonText)
    promptbutton
    s_end
Erin:
    writetext(ErinLostAMonText)
    promptbutton
    s_end
    SCRIPT_END
}
bool PhoneScript_WantsToBattle_Male(script_s* s) {
    SCRIPT_BEGIN
    scall(PhoneScript_RematchText_Male)
    sjump(PhoneScript_HangUpText_Male)
    SCRIPT_END
}
bool PhoneScript_WantsToBattle_Female(script_s* s) {
    SCRIPT_BEGIN
    scall(PhoneScript_RematchText_Female)
    sjump(PhoneScript_HangUpText_Female)
    SCRIPT_END
}
bool PhoneScript_RematchText_Male(script_s* s) {
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
    ifequal(PHONE_BUG_CATCHER_ARNIE, Arnie)
    ifequal(PHONE_SCHOOLBOY_ALAN, Alan)
    ifequal(PHONE_SCHOOLBOY_CHAD, Chad)
    ifequal(PHONE_FISHER_TULLY, Tully)
    ifequal(PHONE_POKEMANIAC_BRENT, Brent)
    ifequal(PHONE_BIRDKEEPER_VANCE, Vance)
    ifequal(PHONE_FISHER_WILTON, Wilton)
    ifequal(PHONE_HIKER_PARRY, Parry)
Jack:
    writetext(JackBattleRematchText)
    promptbutton
    s_end
Huey:
    writetext(HueyBattleRematchText)
    promptbutton
    s_end
Gaven:
    writetext(GavenBattleRematchText)
    promptbutton
    s_end
Jose:
    writetext(JoseBattleRematchText)
    promptbutton
    s_end
Joey:
    writetext(JoeyBattleRematchText)
    promptbutton
    s_end
Wade:
    writetext(WadeBattleRematchText)
    promptbutton
    s_end
Ralph:
    writetext(RalphBattleRematchText)
    promptbutton
    s_end
Anthony:
    writetext(AnthonyBattleRematchText)
    promptbutton
    s_end
Todd:
    writetext(ToddBattleRematchText)
    promptbutton
    s_end
Arnie:
    writetext(ArnieBattleRematchText)
    promptbutton
    s_end
Alan:
    writetext(AlanBattleRematchText)
    promptbutton
    s_end
Chad:
    writetext(ChadBattleRematchText)
    promptbutton
    s_end
Tully:
    writetext(TullyBattleRematchText)
    promptbutton
    s_end
Brent:
    writetext(BrentBattleRematchText)
    promptbutton
    s_end
Vance:
    writetext(VanceBattleRematchText)
    promptbutton
    s_end
Wilton:
    writetext(WiltonBattleRematchText)
    promptbutton
    s_end
Parry:
    writetext(ParryBattleRematchText)
    promptbutton
    s_end
    SCRIPT_END
}
bool PhoneScript_RematchText_Female(script_s* s) {
    SCRIPT_BEGIN
    readvar(VAR_CALLERID)
    ifequal(PHONE_COOLTRAINERF_BETH, Beth)
    ifequal(PHONE_COOLTRAINERF_REENA, Reena)
    ifequal(PHONE_PICNICKER_LIZ, Liz)
    ifequal(PHONE_PICNICKER_GINA, Gina)
    ifequal(PHONE_LASS_DANA, Dana)
    ifequal(PHONE_PICNICKER_TIFFANY, Tiffany)
    ifequal(PHONE_PICNICKER_ERIN, Erin)
Beth:
    writetext(BethBattleRematchText)
    promptbutton
    s_end
Reena:
    writetext(ReenaBattleRematchText)
    promptbutton
    s_end
Liz:
    writetext(LizBattleRematchText)
    promptbutton
    s_end
Gina:
    writetext(GinaBattleRematchText)
    promptbutton
    s_end
Dana:
    writetext(DanaBattleRematchText)
    promptbutton
    s_end
Tiffany:
    writetext(TiffanyBattleRematchText)
    promptbutton
    s_end
Erin:
    writetext(ErinBattleRematchText)
    promptbutton
    s_end
    SCRIPT_END
}
bool LizWrongNumberScript(script_s* s) {
    SCRIPT_BEGIN
    writetext(LizWrongNumberText)
    s_end
    SCRIPT_END
}
bool TiffanyItsAwful(script_s* s) {
    SCRIPT_BEGIN
    writetext(TiffanyItsAwfulText)
    s_end
    SCRIPT_END
}
bool PhoneScript_HangUpText_Male(script_s* s) {
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
    writetext(JackHangUpText)
    s_end
Huey:
    writetext(HueyHangUpText)
    s_end
Gaven:
    writetext(GavenHangUpText)
    s_end
Jose:
    writetext(JoseHangUpText)
    s_end
Joey:
    writetext(JoeyHangUpText)
    s_end
Wade:
    writetext(WadeHangUpText)
    s_end
Ralph:
    writetext(RalphHangUpText)
    s_end
Anthony:
    writetext(AnthonyHangUpText)
    s_end
Todd:
    writetext(ToddHangUpText)
    s_end
Irwin:
    writetext(IrwinHangUpText)
    s_end
Arnie:
    writetext(ArnieHangUpText)
    s_end
Alan:
    writetext(AlanHangUpText)
    s_end
Chad:
    writetext(ChadHangUpText)
    s_end
Derek:
    writetext(DerekHangUpText)
    s_end
Tully:
    writetext(TullyHangUpText)
    s_end
Brent:
    writetext(BrentHangUpText)
    s_end
Vance:
    writetext(VanceHangUpText)
    s_end
Wilton:
    writetext(WiltonHangUpText)
    s_end
Kenji:
    writetext(KenjiHangUpText)
    s_end
Parry:
    writetext(ParryHangUpText)
    s_end
    SCRIPT_END
}
bool PhoneScript_HangUpText_Female(script_s* s) {
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
    writetext(BeverlyHangUpText)
    s_end
Beth:
    writetext(BethHangUpText)
    s_end
Reena:
    writetext(ReenaHangUpText)
    s_end
Liz:
    writetext(LizHangUpText)
    s_end
Gina:
    writetext(GinaHangUpText)
    s_end
Dana:
    writetext(DanaHangUpText)
    s_end
Tiffany:
    writetext(TiffanyHangUpText)
    s_end
Erin:
    writetext(ErinHangUpText)
    s_end
    SCRIPT_END
}
bool Phone_CheckIfUnseenRare_Male(script_s* s) {
    SCRIPT_BEGIN
    scall(PhoneScriptRareWildMon)
    iffalse(HangUp)
    sjump(Phone_GenericCall_Male)
HangUp:
    sjump(PhoneScript_HangUpText_Male)
    SCRIPT_END
}
bool Phone_CheckIfUnseenRare_Female(script_s* s) {
    SCRIPT_BEGIN
    scall(PhoneScriptRareWildMon)
    iffalse(HangUp)
    sjump(Phone_GenericCall_Female)
HangUp:
    sjump(PhoneScript_HangUpText_Female)
    SCRIPT_END
}
bool PhoneScriptRareWildMon(script_s* s) {
    SCRIPT_BEGIN
    special(RandomUnseenWildMon)
    s_end
    SCRIPT_END
}
bool PhoneScript_BugCatchingContest(script_s* s) {
    SCRIPT_BEGIN
    readvar(VAR_CALLERID)
    ifequal(PHONE_BUG_CATCHER_WADE, Wade)
    ifequal(PHONE_POKEFANM_DEREK, Derek)
Wade:
    writetext(WadeBugCatchingContestText)
    promptbutton
    sjump(PhoneScript_HangUpText_Male)
Derek:
    writetext(DerekBugCatchingContestText)
    promptbutton
    sjump(PhoneScript_HangUpText_Male)
    SCRIPT_END
}
bool IrwinRocketRumorScript(script_s* s) {
    SCRIPT_BEGIN
    writetext(IrwinRocketTakeoverRumorText)
    promptbutton
    sjump(PhoneScript_HangUpText_Male)
    SCRIPT_END
}
bool GinaRocketRumorScript(script_s* s) {
    SCRIPT_BEGIN
    writetext(GinaRocketTakeoverRumorText)
    promptbutton
    sjump(PhoneScript_HangUpText_Female)
    SCRIPT_END
}
bool ArnieSwarmScript(script_s* s) {
    SCRIPT_BEGIN
    writetext(ArnieSwarmText)
    promptbutton
    sjump(PhoneScript_HangUpText_Male)
    SCRIPT_END
}
bool RalphItemScript(script_s* s) {
    SCRIPT_BEGIN
    writetext(RalphItemText)
    promptbutton
    sjump(PhoneScript_HangUpText_Male)
    SCRIPT_END
}
bool AnthonySwarmScript(script_s* s) {
    SCRIPT_BEGIN
    writetext(AnthonySwarmText)
    promptbutton
    sjump(PhoneScript_HangUpText_Male)
    SCRIPT_END
}
bool PhoneScript_FoundItem_Male(script_s* s) {
    SCRIPT_BEGIN
    readvar(VAR_CALLERID)
    ifequal(PHONE_BIRDKEEPER_JOSE, Jose)
    ifequal(PHONE_BUG_CATCHER_WADE, Wade)
    ifequal(PHONE_SCHOOLBOY_ALAN, Alan)
    ifequal(PHONE_POKEFANM_DEREK, Derek)
    ifequal(PHONE_FISHER_TULLY, Tully)
    ifequal(PHONE_FISHER_WILTON, Wilton)
Jose:
    writetext(JoseFoundItemText)
    s_end
Wade:
    writetext(WadeFoundItemText)
    s_end
Alan:
    writetext(AlanFoundItemText)
    s_end
Derek:
    writetext(DerekFoundItemText)
    s_end
Tully:
    writetext(TullyFoundItemText)
    s_end
Wilton:
    writetext(WiltonFoundItemText)
    s_end
    SCRIPT_END
}
bool PhoneScript_FoundItem_Female(script_s* s) {
    SCRIPT_BEGIN
    readvar(VAR_CALLERID)
    ifequal(PHONE_POKEFAN_BEVERLY, Beverly)
    ifequal(PHONE_PICNICKER_GINA, Gina)
    ifequal(PHONE_LASS_DANA, Dana)
    ifequal(PHONE_PICNICKER_TIFFANY, Tiffany)
Beverly:
    writetext(BeverlyFoundItemText)
    s_end
Gina:
    writetext(GinaFoundItemText)
    s_end
Dana:
    writetext(DanaFoundItemText)
    s_end
Tiffany:
    writetext(TiffanyFoundItemText)
    s_end
    SCRIPT_END
}
bool ToddItemScript(script_s* s) {
    SCRIPT_BEGIN
    writetext(ToddDepartmentStoreBargainSaleText)
    promptbutton
    sjump(PhoneScript_HangUpText_Male)
    SCRIPT_END
}
bool KenjiCallingPhoneScript(script_s* s) {
    SCRIPT_BEGIN
    writetext(KenjiRemainDedicatedText)
    promptbutton
    sjump(PhoneScript_HangUpText_Male)
    SCRIPT_END
}
