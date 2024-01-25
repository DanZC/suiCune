#include "../../constants.h"
#include "repel.h"
#include "../../util/scripting.h"
#include "../../data/text/common.h"

static struct TextCmd RepelWoreOffText[] = {
    text_far(v_RepelWoreOffText)
    text_end
};

bool RepelWoreOffScript(script_s* s){
    SCRIPT_BEGIN
    opentext
    writetext(RepelWoreOffText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
