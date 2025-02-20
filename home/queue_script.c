#include "../constants.h"
#include "queue_script.h"

Script_fn_t gQueuedScriptAddr;
void (*gQueuedFuncAddr)(void);

void QueueScript(void){
    //  Push pointer hl in the current bank to wQueuedScriptBank.
    LDH_A_addr(hROMBank);

    return FarQueueScript();
}

//  Push pointer hl in the current bank to wQueuedScriptBank.
void QueueScript_Conv(uint16_t hl){
    // LDH_A_addr(hROMBank);

    return FarQueueScript_Conv(hROMBank, hl);
}

void FarQueueScript(void){
    //  Push pointer a:hl to wQueuedScriptBank.
    LD_addr_A(wQueuedScriptBank);
    LD_A_L;
    LD_addr_A(wQueuedScriptAddr);
    LD_A_H;
    LD_addr_A(wQueuedScriptAddr + 1);
    RET;

}

//  Push pointer a:hl to wQueuedScriptBank.
void FarQueueScript_Conv(uint8_t a, uint16_t hl){
    // LD_addr_A(wQueuedScriptBank);
    wram->wQueuedScriptBank = a;
    // LD_A_L;
    // LD_addr_A(wQueuedScriptAddr);
    // LD_A_H;
    // LD_addr_A(wQueuedScriptAddr + 1);
    wram->wQueuedScriptAddr = hl;
    // RET;
}

//  Push pointer hl to gQueuedScriptAddr.
void QueueScript_Conv2(Script_fn_t hl){
    // LD_addr_A(wQueuedScriptBank);
    // LD_A_L;
    // LD_addr_A(wQueuedScriptAddr);
    // LD_A_H;
    // LD_addr_A(wQueuedScriptAddr + 1);
    gQueuedScriptAddr = hl;
    // RET;
}

//  Push pointer hl to gQueuedScriptFunc.
void QueueFunc_Conv2(void (*hl)(void)) {
    gQueuedFuncAddr = hl;
}
