#include "../../constants.h"
#include "checkforhiddenitems.h"
#include "../../home/map.h"
#include "../../home/flag.h"

//  Checks to see if there are hidden items on the screen that have not yet been found.  If it finds one, returns carry.
void CheckForHiddenItems(void){
    CALL(aGetMapScriptsBank);
    LD_addr_A(wCurMapScriptBank);
//  Get the coordinate of the bottom right corner of the screen, and load it in wBottomRightYCoord/wBottomRightXCoord.
    LD_A_addr(wXCoord);
    ADD_A(SCREEN_WIDTH / 4);
    LD_addr_A(wBottomRightXCoord);
    LD_A_addr(wYCoord);
    ADD_A(SCREEN_HEIGHT / 4);
    LD_addr_A(wBottomRightYCoord);
//  Get the pointer for the first bg_event in the map...
    LD_HL(wCurMapBGEventsPointer);
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
//  ... before even checking to see if there are any BG events on this map.
    LD_A_addr(wCurMapBGEventCount);
    AND_A_A;
    IF_Z goto nobgeventitems;
//  For i = 1:wCurMapBGEventCount...

loop:
//  Store the counter in wRemainingBGEventCount, and store the bg_event pointer in the stack.
    LD_addr_A(wRemainingBGEventCount);
    PUSH_HL;
//  Get the Y coordinate of the BG event.
    CALL(aCheckForHiddenItems_GetFarByte);
    LD_E_A;
//  Is the Y coordinate of the BG event on the screen?  If not, go to the next BG event.
    LD_A_addr(wBottomRightYCoord);
    SUB_A_E;
    IF_C goto next;
    CP_A(SCREEN_HEIGHT / 2);
    IF_NC goto next;
//  Is the X coordinate of the BG event on the screen?  If not, go to the next BG event.
    CALL(aCheckForHiddenItems_GetFarByte);
    LD_D_A;
    LD_A_addr(wBottomRightXCoord);
    SUB_A_D;
    IF_C goto next;
    CP_A(SCREEN_WIDTH / 2);
    IF_NC goto next;
//  Is this BG event a hidden item?  If not, go to the next BG event.
    CALL(aCheckForHiddenItems_GetFarByte);
    CP_A(BGEVENT_ITEM);
    IF_NZ goto next;
//  Has this item already been found?  If not, set off the Itemfinder.
    LD_A_addr(wCurMapScriptBank);
    CALL(aGetFarWord);
    LD_A_addr(wCurMapScriptBank);
    CALL(aGetFarWord);
    LD_D_H;
    LD_E_L;
    LD_B(CHECK_FLAG);
    CALL(aEventFlagAction);
    LD_A_C;
    AND_A_A;
    IF_Z goto itemnearby;


next:
//  Restore the bg_event pointer and increment it by the length of a bg_event.
    POP_HL;
    LD_BC(BG_EVENT_SIZE);
    ADD_HL_BC;
//  Restore the BG event counter and decrement it.  If it hits zero, there are no hidden items in range.
    LD_A_addr(wRemainingBGEventCount);
    DEC_A;
    IF_NZ goto loop;


nobgeventitems:
    XOR_A_A;
    RET;


itemnearby:
    POP_HL;
    SCF;
    RET;


GetFarByte:
    LD_A_addr(wCurMapScriptBank);
    CALL(aGetFarByte);
    INC_HL;
    RET;

}

//  Checks to see if there are hidden items on the screen that have not yet been found.  If it finds one, returns true (c).
bool CheckForHiddenItems_Conv(void){
    // CALL(aGetMapScriptsBank);
    // LD_addr_A(wCurMapScriptBank);
//  Get the coordinate of the bottom right corner of the screen, and load it in wBottomRightYCoord/wBottomRightXCoord.
    // LD_A_addr(wXCoord);
    // ADD_A(SCREEN_WIDTH / 4);
    // LD_addr_A(wBottomRightXCoord);
    uint8_t bottom_x = wram->wXCoord + (SCREEN_WIDTH / 4);
    // LD_A_addr(wYCoord);
    // ADD_A(SCREEN_HEIGHT / 4);
    // LD_addr_A(wBottomRightYCoord);
    uint8_t bottom_y = wram->wYCoord + (SCREEN_HEIGHT / 4);
//  Get the pointer for the first bg_event in the map...
    // LD_HL(wCurMapBGEventsPointer);
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    const struct BGEvent* bg = gCurMapBGEventsPointer;
//  ... before even checking to see if there are any BG events on this map.
    // LD_A_addr(wCurMapBGEventCount);
    // AND_A_A;
    // IF_Z goto nobgeventitems;
//  For i = 1:wCurMapBGEventCount...
    for(int i = 0; i < gCurMapBGEventCount; ++i) {
    loop:
    //  Store the counter in wRemainingBGEventCount, and store the bg_event pointer in the stack.
        // LD_addr_A(wRemainingBGEventCount);
        // PUSH_HL;
    //  Get the Y coordinate of the BG event.
        // CALL(aCheckForHiddenItems_GetFarByte);
        // LD_E_A;
        uint8_t e = bg[i].y;
    //  Is the Y coordinate of the BG event on the screen?  If not, go to the next BG event.
        // LD_A_addr(wBottomRightYCoord);
        // SUB_A_E;
        // IF_C goto next;
        // CP_A(SCREEN_HEIGHT / 2);
        // IF_NC goto next;
        if(bottom_y < e || bottom_y - e >= SCREEN_HEIGHT / 2)
            continue;
    //  Is the X coordinate of the BG event on the screen?  If not, go to the next BG event.
        // CALL(aCheckForHiddenItems_GetFarByte);
        // LD_D_A;
        uint8_t d = bg[i].x;
        // LD_A_addr(wBottomRightXCoord);
        // SUB_A_D;
        // IF_C goto next;
        // CP_A(SCREEN_WIDTH / 2);
        // IF_NC goto next;
        if(bottom_x < d || bottom_x - d >= SCREEN_HEIGHT / 2)
            continue;
    //  Is this BG event a hidden item?  If not, go to the next BG event.
        // CALL(aCheckForHiddenItems_GetFarByte);
        // CP_A(BGEVENT_ITEM);
        // IF_NZ goto next;
        if(bg[i].function != BGEVENT_ITEM)
            continue;
    //  Has this item already been found?  If not, set off the Itemfinder.
        // LD_A_addr(wCurMapScriptBank);
        // CALL(aGetFarWord);
        // LD_A_addr(wCurMapScriptBank);
        // CALL(aGetFarWord);
        // LD_D_H;
        // LD_E_L;
        // LD_B(CHECK_FLAG);
        // CALL(aEventFlagAction);
        uint8_t flag = EventFlagAction(bg[i].hiddenItem->eventFlag, CHECK_FLAG);
        // LD_A_C;
        // AND_A_A;
        // IF_Z goto itemnearby;
        if(flag == 0) {
        // itemnearby:
            // POP_HL;
            // SCF;
            // RET;
            return true;
        }

    // next:
    //  Restore the bg_event pointer and increment it by the length of a bg_event.
        // POP_HL;
        // LD_BC(BG_EVENT_SIZE);
        // ADD_HL_BC;
    //  Restore the BG event counter and decrement it.  If it hits zero, there are no hidden items in range.
        // LD_A_addr(wRemainingBGEventCount);
        // DEC_A;
        // IF_NZ goto loop;
    }

// nobgeventitems:
    // XOR_A_A;
    // RET;
    return false;

// GetFarByte:
    // LD_A_addr(wCurMapScriptBank);
    // CALL(aGetFarByte);
    // INC_HL;
    // RET;
}
