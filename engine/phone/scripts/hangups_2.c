#include "../../../constants.h"
#include "../../../util/scripting.h"
#include "generic_caller.h"
#include "../../../data/phone/text/beverly_caller.h"
#include "../../../data/phone/text/jose_caller.h"
#include "../../../data/phone/text/wade_caller.h"
#include "../../../data/phone/text/gina_caller.h"
#include "../../../data/phone/text/alan_caller.h"
#include "../../../data/phone/text/dana_caller.h"
#include "../../../data/phone/text/derek_caller.h"
#include "../../../data/phone/text/tully_caller.h"
#include "../../../data/phone/text/tiffany_caller.h"
#include "../../../data/phone/text/wilton_caller.h"

bool BeverlyComePickUpScript(script_s* s) {
    SCRIPT_BEGIN
    writetext(BeverlyComePickUpText)
    promptbutton
    sjump(PhoneScript_HangUpText_Female)
    SCRIPT_END
}
// unreferenced
bool JoseComePickUpScript(script_s* s) {
    SCRIPT_BEGIN
    writetext(JoseComePickUpText)
    promptbutton
    sjump(PhoneScript_HangUpText_Male)
    SCRIPT_END
}
bool WadeComeQuickScript(script_s* s) {
    SCRIPT_BEGIN
    writetext(WadeComeQuickText)
    promptbutton
    sjump(PhoneScript_HangUpText_Male)
    SCRIPT_END
}
bool GinaComePickUpScript(script_s* s) {
    SCRIPT_BEGIN
    writetext(GinaComePickUpText)
    promptbutton
    sjump(PhoneScript_HangUpText_Female)
    SCRIPT_END
}
bool AlanComePickUpScript(script_s* s) {
    SCRIPT_BEGIN
    writetext(AlanComePickUpGiftText)
    promptbutton
    sjump(PhoneScript_HangUpText_Male)
    SCRIPT_END
}
bool DanaComePickUpScript(script_s* s) {
    SCRIPT_BEGIN
    writetext(DanaComePickUpText)
    promptbutton
    sjump(PhoneScript_HangUpText_Female)
    SCRIPT_END
}
bool DerekComePickUpScript(script_s* s) {
    SCRIPT_BEGIN
    writetext(DerekComePickUpText)
    promptbutton
    sjump(PhoneScript_HangUpText_Male)
    SCRIPT_END
}
bool TullyHurryScript(script_s* s) {
    SCRIPT_BEGIN
    writetext(TullyHurryText)
    promptbutton
    sjump(PhoneScript_HangUpText_Male)
    SCRIPT_END
}
bool TiffanyHurryScript(script_s* s) {
    SCRIPT_BEGIN
    writetext(TiffanyHurryText)
    promptbutton
    sjump(PhoneScript_HangUpText_Female)
    SCRIPT_END
}
bool WiltonWantThisScript(script_s* s) {
    SCRIPT_BEGIN
    writetext(WiltonWantThisText)
    promptbutton
    sjump(PhoneScript_HangUpText_Male)
    SCRIPT_END
}
