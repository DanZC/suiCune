#include "../../constants.h"
#include "card_key.h"
#include "../../home/map.h"
#include "../../home/queue_script.h"
#include "../../util/scripting.h"
#include "../../maps/RadioTower3F.h"

static bool CardKeyScript(script_s* s) {
    SCRIPT_BEGIN
    closetext
    sjump(CardKeySlotScript)
    s_end
    SCRIPT_END
}

void v_CardKey(void){
//  Are we even in the right map to use this?
    // LD_A_addr(wMapGroup);
    // CP_A(GROUP_RADIO_TOWER_3F);
    // IF_NZ goto nope;

    // LD_A_addr(wMapNumber);
    // CP_A(MAP_RADIO_TOWER_3F);
    // IF_NZ goto nope;
    if(wram->wMapGroup == GROUP_RADIO_TOWER_3F && wram->wMapNumber == MAP_RADIO_TOWER_3F) {
    //  Are we facing the slot?
        // LD_A_addr(wPlayerDirection);
        // AND_A(0b1100);
        // CP_A(OW_UP);
        // IF_NZ goto nope;
        if((wram->wPlayerStruct.facing & 0b1100) == OW_UP) {
            // CALL(aGetFacingTileCoord);
            struct CoordsTileId res = GetFacingTileCoord_Conv();
            // LD_A_D;
            // CP_A(18);
            // IF_NZ goto nope;
            // LD_A_E;
            // CP_A(6);
            // IF_NZ goto nope;
            if(res.x == 18 && res.y == 6) {
            //  Let's use the Card Key.
                // LD_HL(mv_CardKey_CardKeyScript);
                // CALL(aQueueScript);
                QueueScript(CardKeyScript);
                // LD_A(TRUE);
                // LD_addr_A(wItemEffectSucceeded);
                wram->wItemEffectSucceeded = TRUE;
                // RET;
                return;
            }
        }
    }

// nope:
    // LD_A(FALSE);
    // LD_addr_A(wItemEffectSucceeded);
    wram->wItemEffectSucceeded = FALSE;
    // RET;

}
