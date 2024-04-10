#include "../../constants.h"
#include "misc_scripts.h"
#include "../../home/names.h"
#include "../../home/copy_name.h"
#include "../../home/item.h"
#include "../../util/scripting.h"
#include "../../data/text/common.h"

bool Script_AbortBugContest(script_s* s){
    SCRIPT_BEGIN
    checkflag(ENGINE_BUG_CONTEST_TIMER)
    iffalse(finish)
    setflag(ENGINE_DAILY_BUG_CONTEST)
    special(ContestReturnMons)

finish:
    s_end
    SCRIPT_END
}

static void FindItemInBallScript_TryReceiveItem(void) {
    // XOR_A_A;
    // LD_addr_A(wScriptVar);
    wram->wScriptVar = 0;
    // LD_A_addr(wItemBallItemID);
    // LD_addr_A(wNamedObjectIndex);
    // CALL(aGetItemName);
    // LD_HL(wStringBuffer3);
    // CALL(aCopyName2);
    CopyName2_Conv2(wram->wStringBuffer3, GetItemName_Conv2(wram->wItemBallItemID));
    // LD_A_addr(wItemBallItemID);
    // LD_addr_A(wCurItem);
    // LD_A_addr(wItemBallQuantity);
    // LD_addr_A(wItemQuantityChange);
    // LD_HL(wNumItems);
    // CALL(aReceiveItem);
    // RET_NC ;
    if(!ReceiveItem_Conv((item_pocket_s*)&wram->wNumItems, wram->wItemBallItemID, wram->wItemBallQuantity))
        return;
    // LD_A(0x1);
    // LD_addr_A(wScriptVar);
    wram->wScriptVar = 0x1;
    // RET;
}

bool FindItemInBallScript(script_s* s){
    static const txt_cmd_s FoundItemText[] = {
        text_far(v_FoundItemText)
        text_end
    };
    static const txt_cmd_s CantCarryItemText[] = {
        text_far(v_CantCarryItemText)
        text_end
    };
    SCRIPT_BEGIN
    FindItemInBallScript_TryReceiveItem();
    iffalse(no_room)
    disappear(LAST_TALKED)
    opentext
    writetext(FoundItemText)
    playsound(SFX_ITEM)
    pause(60)
    itemnotify
    closetext
    s_end


no_room:
    opentext
    writetext(FoundItemText)
    waitbutton
    writetext(CantCarryItemText)
    waitbutton
    closetext
    s_end
    SCRIPT_END

}
