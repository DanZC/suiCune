#include "../../../constants.h"
#include "../../../util/scripting.h"
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
#include "hangups.h"

bool JackPhoneTipsScript(script_s* s) {
    SCRIPT_BEGIN
    writetext(JackHeardSomeGreatTipsText)
    promptbutton
    sjump(PhoneScript_HangUpText_Male)
    SCRIPT_END
}
bool BeverlyHangUpScript(script_s* s) {
    SCRIPT_BEGIN
    writetext(BeverlyLetsChatAboutMonAgainText)
    promptbutton
    sjump(PhoneScript_HangUpText_Female)
    SCRIPT_END
}
bool HueyHangUpScript(script_s* s) {
    SCRIPT_BEGIN
    writetext(HueyWeHaveToBattleAgainSometimeText)
    promptbutton
    sjump(PhoneScript_HangUpText_Male)
    SCRIPT_END
}
bool GavenHangUpNotThursdayScript(script_s* s) {
    SCRIPT_BEGIN
    writetext(GavenHangUpNotThursdayText)
    promptbutton
    sjump(PhoneScript_HangUpText_Male)
    SCRIPT_END
}
bool BethHangUpScript(script_s* s) {
    SCRIPT_BEGIN
    writetext(BethLetsBattleAgainSometimeText)
    promptbutton
    sjump(PhoneScript_HangUpText_Female)
    SCRIPT_END
}
bool JoseHangUpScript(script_s* s) {
    SCRIPT_BEGIN
    writetext(JoseHaventGottenItemYetText)
    promptbutton
    sjump(PhoneScript_HangUpText_Male)
    SCRIPT_END
}
bool ReenaForwardScript(script_s* s) {
    SCRIPT_BEGIN
    writetext(ReenaForwardText)
    promptbutton
    sjump(PhoneScript_HangUpText_Female)
    SCRIPT_END
}
bool JoeyHangUpScript(script_s* s) {
    SCRIPT_BEGIN
    writetext(JoeyDevisingStrategiesText)
    promptbutton
    sjump(PhoneScript_HangUpText_Male)
    SCRIPT_END
}
bool WadeNoBerriesScript(script_s* s) {
    SCRIPT_BEGIN
    writetext(WadeNoBerriesText)
    promptbutton
    sjump(PhoneScript_HangUpText_Male)
    SCRIPT_END
}
bool RalphNoItemScript(script_s* s) {
    SCRIPT_BEGIN
    writetext(RalphNoItemText)
    promptbutton
    sjump(PhoneScript_HangUpText_Male)
    SCRIPT_END
}
bool LizHangUpScript(script_s* s) {
    SCRIPT_BEGIN
    writetext(LizFawningOverMonText)
    promptbutton
    sjump(PhoneScript_HangUpText_Female)
    SCRIPT_END
}
bool AnthonyHangUpScript(script_s* s) {
    SCRIPT_BEGIN
    writetext(AnthonyWasntPayingAttentionText)
    promptbutton
    sjump(PhoneScript_HangUpText_Male)
    SCRIPT_END
}
bool ToddNoItemScript(script_s* s) {
    SCRIPT_BEGIN
    writetext(ToddSavingUpForBargainSaleText)
    promptbutton
    sjump(PhoneScript_HangUpText_Male)
    SCRIPT_END
}
bool GinaHangUpScript(script_s* s) {
    SCRIPT_BEGIN
    writetext(GinaHaventFoundAnythingYetText)
    promptbutton
    sjump(PhoneScript_HangUpText_Female)
    SCRIPT_END
}
bool ArnieHangUpScript(script_s* s) {
    SCRIPT_BEGIN
    writetext(ArnieHaventSeenRareMonText)
    promptbutton
    sjump(PhoneScript_HangUpText_Male)
    SCRIPT_END
}
bool AlanHangUpScript(script_s* s) {
    SCRIPT_BEGIN
    writetext(AlanHaventPickedUpAnythingText)
    promptbutton
    sjump(PhoneScript_HangUpText_Male)
    SCRIPT_END
}
bool DanaHangUpScript(script_s* s) {
    SCRIPT_BEGIN
    writetext(DanaCanYouWaitABitLongerText)
    promptbutton
    sjump(PhoneScript_HangUpText_Female)
    SCRIPT_END
}
bool ChadHangUpScript(script_s* s) {
    SCRIPT_BEGIN
    writetext(ChadGoingToStudyHardText)
    promptbutton
    sjump(PhoneScript_HangUpText_Male)
    SCRIPT_END
}
bool DerekHangUpScript(script_s* s) {
    SCRIPT_BEGIN
    writetext(DerekLetsGetTogetherText)
    promptbutton
    sjump(PhoneScript_HangUpText_Male)
    SCRIPT_END
}
bool TullyNoItemScript(script_s* s) {
    SCRIPT_BEGIN
    writetext(TullyNoItemText)
    promptbutton
    sjump(PhoneScript_HangUpText_Male)
    SCRIPT_END
}
bool BrentHangUpScript(script_s* s) {
    SCRIPT_BEGIN
    writetext(BrentSorryImTooBusyText)
    promptbutton
    sjump(PhoneScript_HangUpText_Male)
    SCRIPT_END
}
bool TiffanyNoItemScript(script_s* s) {
    SCRIPT_BEGIN
    writetext(TiffanyNoItemText)
    promptbutton
    sjump(PhoneScript_HangUpText_Female)
    SCRIPT_END
}
bool VanceLookingForwardScript(script_s* s) {
    SCRIPT_BEGIN
    writetext(VanceLookingForwardText)
    promptbutton
    sjump(PhoneScript_HangUpText_Male)
    SCRIPT_END
}
bool WiltonHaventFoundAnythingScript(script_s* s) {
    SCRIPT_BEGIN
    writetext(WiltonHaventFoundAnythingText)
    promptbutton
    sjump(PhoneScript_HangUpText_Male)
    SCRIPT_END
}
bool ParryBattleWithMeScript(script_s* s) {
    SCRIPT_BEGIN
    writetext(ParryBattleWithMeText)
    promptbutton
    sjump(PhoneScript_HangUpText_Male)
    SCRIPT_END
}
bool ErinWorkingHardScript(script_s* s) {
    SCRIPT_BEGIN
    writetext(ErinWorkingHardText)
    promptbutton
    sjump(PhoneScript_HangUpText_Female)
    SCRIPT_END
}
bool IrwinRandomTextScript(script_s* s) {
    SCRIPT_BEGIN
    srandom(3)
    ifequal_jump(0, IrwinEscapadeScript)
    ifequal_jump(1, IrwinGoodMatchScript)
    ifequal_jump(2, IrwinSoMuchToChatAboutScript)
    SCRIPT_FALLTHROUGH(IrwinEscapadeScript)
}
bool IrwinEscapadeScript(script_s* s) {
    SCRIPT_BEGIN
    writetext(IrwinYourEscapadesRockText)
    promptbutton
    sjump(PhoneScript_HangUpText_Male)
    SCRIPT_END
}
bool IrwinGoodMatchScript(script_s* s) {
    SCRIPT_BEGIN
    writetext(IrwinGoodMatchText)
    promptbutton
    sjump(PhoneScript_HangUpText_Male)
    SCRIPT_END
}
bool IrwinSoMuchToChatAboutScript(script_s* s) {
    SCRIPT_BEGIN
    writetext(IrwinSoMuchToChatAboutText)
    promptbutton
    sjump(PhoneScript_HangUpText_Male)
    SCRIPT_END
}
bool KenjiAnswerPhoneScript(script_s* s) {
    SCRIPT_BEGIN
    readvar(VAR_KENJI_BREAK)
    ifequal(2, Training)
    ifequal(1, OnBreak)
    writetext(KenjiCallMeBackAnotherTimeText)
    promptbutton
    sjump(PhoneScript_HangUpText_Male)
Training:
    writetext(KenjiIllHaveTimeToChatTomorrowText)
    promptbutton
    sjump(PhoneScript_HangUpText_Male)
OnBreak:
    checktime(MORN)
    iftrue(Morning)
    checktime(NITE)
    iftrue(Night)
    setevent(EVENT_KENJI_ON_BREAK)
    writetext(KenjiTakingABreakText)
    promptbutton
    sjump(PhoneScript_HangUpText_Male)
Morning:
    writetext(KenjiHangUpMorningText)
    promptbutton
    sjump(PhoneScript_HangUpText_Male)
Night:
    writetext(KenjiHangUpNightText)
    promptbutton
    sjump(PhoneScript_HangUpText_Male)
    SCRIPT_END
}
