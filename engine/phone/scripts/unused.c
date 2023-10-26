#include "../../../constants.h"
#include "../../../util/scripting.h"
#include "../../../data/phone/text/unused.h"
#include "unused.h"

bool UnusedPhoneScript(script_s* s) {
    SCRIPT_BEGIN
    writetext(UnusedPhoneText)
    s_end
    SCRIPT_END
}
