#include "../../constants.h"
#include "squirtbottle.h"
#include "overworld.h"
#include "../../maps/Route36.h"
#include "../../util/scripting.h"
#include "../../data/text/common.h"
#include "../../home/queue_script.h"

static void CheckCanUseSquirtbottle(void) {
    // LD_A_addr(wMapGroup);
    // CP_A(GROUP_ROUTE_36);
    // IF_NZ goto nope;

    // LD_A_addr(wMapNumber);
    // CP_A(MAP_ROUTE_36);
    // IF_NZ goto nope;
    if(wram->wMapGroup == GROUP_ROUTE_36 && wram->wMapNumber == MAP_ROUTE_36) {
        // FARCALL(aGetFacingObject);
        u8_flag_s res = GetFacingObject_Conv();
        // IF_C goto nope;
        // LD_A_D;
        // CP_A(SPRITEMOVEDATA_SUDOWOODO);
        // IF_NZ goto nope;
        if(res.flag && res.a == SPRITEMOVEDATA_SUDOWOODO) {
            // LD_A(1);
            // LD_addr_A(wScriptVar);
            wram->wScriptVar = 1;
            // RET;
            return;
        }
    }

// nope:
    // XOR_A_A;
    // LD_addr_A(wScriptVar);
    wram->wScriptVar = 0;
    // RET;
    return;
}

static bool SquirtbottleScript(script_s* s) {
    static const txt_cmd_s SquirtbottleNothingText[] = {
        text_far(v_SquirtbottleNothingText)
        text_end
    };
    SCRIPT_BEGIN
    reloadmappart
    special(UpdateTimePals)
    CheckCanUseSquirtbottle();
    iffalse(SquirtbottleNothingScript)
    sjump(WateredWeirdTreeScript)

SquirtbottleNothingScript:
    jumptext(SquirtbottleNothingText)
    SCRIPT_END
}

void v_Squirtbottle(void){
    // LD_HL(mv_Squirtbottle_SquirtbottleScript);
    // CALL(aQueueScript);
    QueueScript(SquirtbottleScript);
    // LD_A(0x1);
    // LD_addr_A(wItemEffectSucceeded);
    wram->wItemEffectSucceeded = 0x1;
    // RET;
}
