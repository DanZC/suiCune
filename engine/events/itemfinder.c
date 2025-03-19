#include "../../constants.h"
#include "itemfinder.h"
#include "checkforhiddenitems.h"
#include "../../home/audio.h"
#include "../../home/queue_script.h"
#include "../../util/scripting.h"
#include "../../data/text/common.h"

static void ItemfinderSound(void) {
    // LD_C(4);
    uint8_t c = 4;

    do {
    // sfx_loop:
        // PUSH_BC;
        // LD_DE(SFX_SECOND_PART_OF_ITEMFINDER);
        // CALL(aWaitPlaySFX);
        WaitPlaySFX(SFX_SECOND_PART_OF_ITEMFINDER);
        // LD_DE(SFX_TRANSACTION);
        // CALL(aWaitPlaySFX);
        WaitPlaySFX(SFX_TRANSACTION);
        // POP_BC;
        // DEC_C;
        // IF_NZ goto sfx_loop;
    } while(--c != 0);
    // RET;
}

static bool Script_FoundSomething(script_s* s) {
    static const txt_cmd_s ItemfinderItemNearbyText[] = {
        text_far(v_ItemfinderItemNearbyText)
        text_end
    };
    SCRIPT_BEGIN
    reloadmappart
    special(UpdateTimePals)
    ItemfinderSound();
    writetext(ItemfinderItemNearbyText)
    closetext
    s_end
    SCRIPT_END
}


static bool Script_FoundNothing(script_s* s) {
    static const txt_cmd_s ItemfinderNopeText[] = {
        text_far(v_ItemfinderNopeText)
        text_end
    };
    SCRIPT_BEGIN
    reloadmappart
    special(UpdateTimePals)
    writetext(ItemfinderNopeText)
    closetext
    s_end
    SCRIPT_END
}



void ItemFinder(void){
    // FARCALL(aCheckForHiddenItems);
    bool found = CheckForHiddenItems_Conv();
    // IF_C goto found_something;
    // LD_HL(mItemFinder_Script_FoundNothing);
    // goto resume;


// found_something:
    // LD_HL(mItemFinder_Script_FoundSomething);


// resume:
    Script_fn_t script = (found)? Script_FoundSomething: Script_FoundNothing;
    // CALL(aQueueScript);
    QueueScript_Conv2(script);
    // LD_A(0x1);
    // LD_addr_A(wItemEffectSucceeded);
    wram->wItemEffectSucceeded = 0x1;
    // RET;
}
