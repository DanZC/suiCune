#include "../constants.h"
#include "queue_script.h"

Script_fn_t gQueuedScriptAddr;
void (*gQueuedFuncAddr)(void);

//  Push pointer hl to gQueuedScriptAddr.
void QueueScript(Script_fn_t hl){
    // LD_addr_A(wQueuedScriptBank);
    // LD_A_L;
    // LD_addr_A(wQueuedScriptAddr);
    // LD_A_H;
    // LD_addr_A(wQueuedScriptAddr + 1);
    gQueuedScriptAddr = hl;
    // RET;
}

//  Push pointer hl to gQueuedScriptFunc.
void QueueFunc(void (*hl)(void)) {
    gQueuedFuncAddr = hl;
}

//  Push pointer hl in the current bank to wQueuedScriptBank.
void QueueScript_GB(uint16_t hl){
    // LDH_A_addr(hROMBank);

    return FarQueueScript_GB(hram.hROMBank, hl);
}

//  Push pointer a:hl to wQueuedScriptBank.
// Unused
void FarQueueScript_GB(uint8_t a, uint16_t hl){
    // LD_addr_A(wQueuedScriptBank);
    wram->wQueuedScriptBank = a;
    // LD_A_L;
    // LD_addr_A(wQueuedScriptAddr);
    // LD_A_H;
    // LD_addr_A(wQueuedScriptAddr + 1);
    wram->wQueuedScriptAddr = hl;
    // RET;
}
