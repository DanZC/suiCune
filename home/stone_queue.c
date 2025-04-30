#include "../constants.h"
#include "stone_queue.h"
#include "map.h"
#include "../engine/overworld/scripting.h"

void HandleStoneQueue(void){
        LDH_A_addr(hROMBank);
    PUSH_AF;

    CALL(aSwitchToMapScriptsBank);
    CALL(aHandleStoneQueue_WarpAction);

    POP_BC;
    LD_A_B;
    RST(aBankswitch);
    RET;


WarpAction:
        LD_HL(OBJECT_MAP_OBJECT_INDEX);
    ADD_HL_DE;
    LD_A_hl;
    CP_A(0xff);
    IF_Z goto nope;

    LD_L_A;
    PUSH_HL;
    CALL(aHandleStoneQueue_IsObjectOnWarp);
    POP_HL;
    IF_NC goto nope;
    LD_D_A;
    LD_E_L;
    CALL(aHandleStoneQueue_IsObjectInStoneTable);
    IF_NC goto nope;
    CALL(aCallMapScript);
    FARCALL(aEnableScriptMode);
    SCF;
    RET;


nope:
        AND_A_A;
    RET;


IsObjectOnWarp:
        PUSH_DE;

    LD_HL(OBJECT_NEXT_MAP_X);
    ADD_HL_DE;
    LD_A_hl;
    LD_HL(OBJECT_NEXT_MAP_Y);
    ADD_HL_DE;
    LD_E_hl;

    SUB_A(4);
    LD_D_A;
    LD_A_E;
    SUB_A(4);
    LD_E_A;
    CALL(aHandleStoneQueue_check_on_warp);

    POP_DE;
    RET;


check_on_warp:
        LD_HL(wCurMapWarpsPointer);
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    LD_A_addr(wCurMapWarpCount);
    AND_A_A;
    IF_Z goto nope2;


loop:
        PUSH_AF;
    LD_A_hl;
    CP_A_E;
    IF_NZ goto not_on_warp;
    INC_HL;
    LD_A_hld;
    CP_A_D;
    IF_NZ goto not_on_warp;
    goto found_warp;


not_on_warp:
        LD_A(WARP_EVENT_SIZE);
    ADD_A_L;
    LD_L_A;
    IF_NC goto no_carry;
    INC_H;

no_carry:
    
    POP_AF;
    DEC_A;
    IF_NZ goto loop;


nope2:
        AND_A_A;
    RET;


found_warp:
        POP_AF;
    LD_D_A;
    LD_A_addr(wCurMapWarpCount);
    SUB_A_D;
    INC_A;
    SCF;
    RET;


IsObjectInStoneTable:
        INC_E;
    LD_HL(CMDQUEUE_ADDR);
    ADD_HL_BC;
    LD_A_hli;
    LD_H_hl;
    LD_L_A;

loop2:
        LD_A_hli;
    CP_A(0xff);
    IF_Z goto nope3;
    CP_A_D;
    IF_NZ goto next_inc3;
    LD_A_hli;
    CP_A_E;
    IF_NZ goto next_inc2;
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    goto yes;


next_inc3:
        INC_HL;


next_inc2:
        INC_HL;
    INC_HL;
    goto loop2;


nope3:
        AND_A_A;
    RET;


yes:
        SCF;
    RET;

}

static u8_flag_s HandleStoneQueue_check_on_warp(uint8_t d, uint8_t e) {
    // LD_HL(wCurMapWarpsPointer);
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
#if CONVERTED_OVERWORLD_LOOP
    const struct WarpEventData* hl = gCurMapWarpsPointer;
#else
    const struct WarpEventData* hl = GBToRAMAddr(wram->wCurMapWarpsPointer);
#endif
    // LD_A_addr(wCurMapWarpCount);
    // AND_A_A;
    // IF_Z goto nope2;
    if(gCurMapWarpCount == 0)
        return u8_flag(0, false);

    uint8_t a = gCurMapWarpCount;

    do {
    // loop:
        // PUSH_AF;
        // LD_A_hl;
        // CP_A_E;
        // IF_NZ goto not_on_warp;
        // INC_HL;
        // LD_A_hld;
        // CP_A_D;
        // IF_NZ goto not_on_warp;
        // goto found_warp;
        if(hl->y == e && hl->x == d) {
        // found_warp:
            // POP_AF;
            // LD_D_A;
            // LD_A_addr(wCurMapWarpCount);
            // SUB_A_D;
            // INC_A;
            uint8_t warp = (gCurMapWarpCount - a) + 1;
            // SCF;
            // RET;
            return u8_flag(warp, true);
        }

    // not_on_warp:
        // LD_A(WARP_EVENT_SIZE);
        // ADD_A_L;
        // LD_L_A;
        // IF_NC goto no_carry;
        // INC_H;

    // no_carry:
        hl++;
        // POP_AF;
        // DEC_A;
        // IF_NZ goto loop;
    } while(--a != 0);

// nope2:
    // AND_A_A;
    // RET;
    return u8_flag(0, false);
}

static u8_flag_s HandleStoneQueue_IsObjectOnWarp(struct Object *de) {
    // PUSH_DE;

    // LD_HL(OBJECT_NEXT_MAP_X);
    // ADD_HL_DE;
    // LD_A_hl;
    // LD_HL(OBJECT_NEXT_MAP_Y);
    // ADD_HL_DE;
    // LD_E_hl;

    // SUB_A(4);
    // LD_D_A;
    uint8_t d = de->nextMapX - 4;
    // LD_A_E;
    // SUB_A(4);
    // LD_E_A;
    uint8_t e = de->nextMapY - 4;
    // CALL(aHandleStoneQueue_check_on_warp);

    // POP_DE;
    // RET;
    return HandleStoneQueue_check_on_warp(d, e);
}

static Script_fn_t HandleStoneQueue_IsObjectInStoneTable(uint8_t e, uint8_t d, const struct Stonetable* table) {
    // INC_E;
    // LD_HL(CMDQUEUE_ADDR);
    // ADD_HL_BC;
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;

    for(int i = 0; table[i].warp != 0xff; ++i) {
    // loop2:
        // LD_A_hli;
        // CP_A(0xff);
        // IF_Z goto nope3;
        // CP_A_D;
        // IF_NZ goto next_inc3;
        // LD_A_hli;
        // CP_A_E;
        // IF_NZ goto next_inc2;
        // LD_A_hli;
        // LD_H_hl;
        // LD_L_A;
        // goto yes;
        if(table[i].warp == d && table[i].person == e) {
            return table[i].script;
        }

    // next_inc3:
        // INC_HL;

    // next_inc2:
        // INC_HL;
        // INC_HL;
        // goto loop2;
    }

// nope3:
    // AND_A_A;
    // RET;
    return NULL;

// yes:
    // SCF;
    // RET;
}

static bool HandleStoneQueue_WarpAction(struct Object* de, const struct Stonetable* table){
    // LD_HL(OBJECT_MAP_OBJECT_INDEX);
    // ADD_HL_DE;
    // LD_A_hl;
    // CP_A(0xff);
    // IF_Z goto nope;
    if(de->mapObjectIndex == 0xff)
        return false;

    // LD_L_A;
    // PUSH_HL;
    // CALL(aHandleStoneQueue_IsObjectOnWarp);
    u8_flag_s res = HandleStoneQueue_IsObjectOnWarp(de);
    // POP_HL;
    // IF_NC goto nope;
    if(!res.flag)
        return false;
    // LD_D_A;
    // LD_E_L;
    // CALL(aHandleStoneQueue_IsObjectInStoneTable);
    Script_fn_t script = HandleStoneQueue_IsObjectInStoneTable(de->mapObjectIndex, res.a, table);
    // IF_NC goto nope;
    if(script != NULL) {
        // CALL(aCallMapScript);
        CallMapScript(script);
        // FARCALL(aEnableScriptMode);
        EnableScriptMode();
        // SCF;
        // RET;
        return true;
    }

// nope:
    // AND_A_A;
    // RET;
    return false;
}

bool HandleStoneQueue_Conv(struct Object* de, const struct Stonetable* table){
    // LDH_A_addr(hROMBank);
    // PUSH_AF;

    // CALL(aSwitchToMapScriptsBank);
    // CALL(aHandleStoneQueue_WarpAction);

    // POP_BC;
    // LD_A_B;
    // RST(aBankswitch);
    // RET;
    return HandleStoneQueue_WarpAction(de, table);
}
