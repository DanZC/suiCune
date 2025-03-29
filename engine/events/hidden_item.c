#include "../../constants.h"
#include "hidden_item.h"
#include "../../home/flag.h"
#include "../../util/scripting.h"
#include "../../data/text/common.h"

bool HiddenItemScript(script_s* s){
    static const txt_cmd_s PlayerFoundItemText[] = {
        text_far(v_PlayerFoundItemText)
        text_end
    };
    static const txt_cmd_s ButNoSpaceText[] = {
        text_far(v_ButNoSpaceText)
        text_end
    };
    SCRIPT_BEGIN
    opentext
    readmem(wram_ptr(wHiddenItemID))
    getitemname(STRING_BUFFER_3, USE_SCRIPT_VAR)
    writetext(PlayerFoundItemText)
    giveitem(ITEM_FROM_MEM, 1)
    iffalse(bag_full)
    //callasm ['SetMemEvent']
    SetMemEvent();
    specialsound
    itemnotify
    goto finish;


bag_full:
    promptbutton
    writetext(ButNoSpaceText)
    waitbutton


finish:
    closetext
    s_end
    SCRIPT_END
}

void SetMemEvent(void){
    // LD_HL(wHiddenItemEvent);
    // LD_A_hli;
    // LD_D_hl;
    // LD_E_A;
    // LD_B(SET_FLAG);
    // CALL(aEventFlagAction);
    EventFlagAction(wram->wHiddenItemEvent, SET_FLAG);
    // RET;
}
