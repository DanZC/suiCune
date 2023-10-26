#include "../../../constants.h"
#include "../../../util/scripting.h"
#include "../../../data/phone/text/bill.h"

bool BillPhoneCalleeScript(script_s* s) {
    SCRIPT_BEGIN
    checktime(DAY)
    iftrue(daygreet)
    checktime(NITE)
    iftrue(nitegreet)
    writetext(BillPhoneMornGreetingText)
    promptbutton
    goto main;
daygreet:
    writetext(BillPhoneDayGreetingText)
    promptbutton
    goto main;
nitegreet:
    writetext(BillPhoneNiteGreetingText)
    promptbutton
    goto main;
main:
    writetext(BillPhoneGenericText)
    promptbutton
    readvar(VAR_BOXSPACE)
    // getnum(STRING_BUFFER_3)
    ifequal(0, full)
    ifless(PARTY_LENGTH, nearlyfull)
    writetext(BillPhoneNotFullText)
    s_end
nearlyfull:
    writetext(BillPhoneNearlyFullText)
    s_end
full:
    writetext(BillPhoneFullText)
    s_end
    SCRIPT_END
}
bool BillPhoneCallerScript(script_s* s) {
    SCRIPT_BEGIN
    writetext(BillPhoneNewlyFullText)
    waitbutton
    s_end
    SCRIPT_END
}
