#include "../../../constants.h"
#include "../../../util/scripting.h"
#include "../../../data/phone/text/ralph_caller.h"
#include "../../../data/phone/text/anthony_caller.h"
#include "../../../data/phone/text/arnie_caller.h"
#include "../../../data/phone/text/todd_caller.h"

bool RalphHurryScript(script_s* s) {
    SCRIPT_BEGIN
    writetext(RalphHurryText)
    s_end
    SCRIPT_END
}
bool AnthonyHurryScript(script_s* s) {
    SCRIPT_BEGIN
    writetext(AnthonyHurryText)
    s_end
    SCRIPT_END
}
bool ArnieHurryScript(script_s* s) {
    SCRIPT_BEGIN
    writetext(ArnieHurryText)
    s_end
    SCRIPT_END
}
bool ToddHurryScript(script_s* s) {
    SCRIPT_BEGIN
    writetext(ToddHaveYouGoneToDepartmentStoreText)
    s_end
    SCRIPT_END
}
