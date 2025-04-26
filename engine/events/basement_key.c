#include "../../constants.h"
#include "basement_key.h"
#include "../../home/map.h"
#include "../../maps/GoldenrodUnderground.h"
#include "../../util/scripting.h"
#include "../../home/queue_script.h"

static bool BasementKeyScript(script_s* s) {
    SCRIPT_BEGIN
    closetext
    sjump(BasementDoorScript)
    SCRIPT_END
}

void v_BasementKey(void){
//  Are we even in the right map to use this?
    // LD_A_addr(wMapGroup);
    // CP_A(GROUP_GOLDENROD_UNDERGROUND);
    // IF_NZ goto nope;

    // LD_A_addr(wMapNumber);
    // CP_A(MAP_GOLDENROD_UNDERGROUND);
    // IF_NZ goto nope;
    if(wram->wMapGroup == GROUP_GOLDENROD_UNDERGROUND && wram->wMapNumber == MAP_GOLDENROD_UNDERGROUND) {
    //  Are we on the tile in front of the door?
        // CALL(aGetFacingTileCoord);
        struct CoordsTileId cid = GetFacingTileCoord();
        // LD_A_D;
        // CP_A(22);
        // IF_NZ goto nope;
        // LD_A_E;
        // CP_A(10);
        // IF_NZ goto nope;
        if(cid.x == 22 && cid.y == 10) {
        //  Let's use the Basement Key
            // LD_HL(mv_BasementKey_BasementKeyScript);
            // CALL(aQueueScript);
            QueueScript(BasementKeyScript);
            // LD_A(TRUE);
            // LD_addr_A(wItemEffectSucceeded);
            wram->wItemEffectSucceeded = TRUE;
            // RET;
            return;
        }
    }

// nope:
    // LD_A(FALSE);
    // LD_addr_A(wItemEffectSucceeded);
    wram->wItemEffectSucceeded = FALSE;
    // RET;
}
