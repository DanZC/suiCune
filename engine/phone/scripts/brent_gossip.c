#include "../../../constants.h"
#include "../../../util/scripting.h"
#include "generic_caller.h"
#include "hangups.h"
#include "../../../data/phone/text/brent_caller.h"

bool BrentBillTriviaScript(script_s* s) {
    SCRIPT_BEGIN
    srandom(10)
    ifequal(0, Father)
    ifequal(1, Grandpa)
    ifequal(2, Goldenrod)
    ifequal(3, Route25)
    ifequal(4, Abra)
    ifequal(5, Sister)
    ifequal(6, Milk)
    ifequal(7, Battling)
    ifequal(8, FlowerShop)
    ifequal(9, KimonoGirl)
Father:
    writetext(BrentFatherGossipText)
    promptbutton
    sjump(PhoneScript_HangUpText_Male)
Grandpa:
    writetext(BrentGrandpaGossipText)
    promptbutton
    sjump(PhoneScript_HangUpText_Male)
Goldenrod:
    writetext(BrentGoldenrodGossipText)
    promptbutton
    sjump(PhoneScript_HangUpText_Male)
Route25:
    writetext(BrentRoute25GossipText)
    promptbutton
    sjump(PhoneScript_HangUpText_Male)
Abra:
    writetext(BrentAbraGossipText)
    promptbutton
    sjump(PhoneScript_HangUpText_Male)
Sister:
    writetext(BrentSisterGossipText)
    promptbutton
    sjump(PhoneScript_HangUpText_Male)
Milk:
    writetext(BrentMilkGossipText)
    promptbutton
    sjump(PhoneScript_HangUpText_Male)
Battling:
    writetext(BrentBattlingGossipText)
    promptbutton
    sjump(PhoneScript_HangUpText_Male)
FlowerShop:
    writetext(BrentFlowerShopGossipText)
    promptbutton
    sjump(PhoneScript_HangUpText_Male)
KimonoGirl:
    writetext(BrentKimonoGirlGossipText)
    promptbutton
    sjump(PhoneScript_HangUpText_Male)
    SCRIPT_END
}
