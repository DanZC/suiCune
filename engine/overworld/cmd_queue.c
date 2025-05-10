#include "../../constants.h"
#include "cmd_queue.h"
#include "../../home/region.h"
#include "../../home/map_objects.h"
#include "../../home/copy.h"
#include "../../home/stone_queue.h"

struct CmdQueue gCmdQueue[CMDQUEUE_CAPACITY];

static void HandleQueuedCommand(struct CmdQueue* bc);
static void CmdQueues_IncAnonJumptableIndex(uint8_t* bc);
static void CmdQueues_DecAnonJumptableIndex(uint8_t* bc);
static void CmdQueue_Type4(uint8_t* bc);
static void CmdQueue_Type3(uint8_t* bc);
static void CmdQueue_StoneTable(struct CmdQueue* bc);

void ClearCmdQueue(void){
    // LD_HL(wCmdQueue);
    // LD_DE(CMDQUEUE_ENTRY_SIZE);
    // LD_C(CMDQUEUE_CAPACITY);
    // XOR_A_A;

    for(uint32_t c = 0; c < CMDQUEUE_CAPACITY; ++c) {
    // loop:
        // LD_hl_A;
        gCmdQueue[c].type = 0;
        // ADD_HL_DE;
        // DEC_C;
        // IF_NZ goto loop;
    }
    // RET;
}

void HandleCmdQueue(void){
    // LD_HL(wCmdQueue);
    // XOR_A_A;

    for(uint32_t c = 0; c < CMDQUEUE_CAPACITY; ++c) {
    // loop:
        // LDH_addr_A(hMapObjectIndex);
        hram->hMapObjectIndex = c;
        // LD_A_hl;
        // AND_A_A;
        // IF_Z goto skip;
        if(gCmdQueue[c].type == 0)
            continue;
        // PUSH_HL;
        // LD_B_H;
        // LD_C_L;
        // CALL(aHandleQueuedCommand);
        HandleQueuedCommand(gCmdQueue + c);
        // POP_HL;


    // skip:
        // LD_DE(CMDQUEUE_ENTRY_SIZE);
        // ADD_HL_DE;
        // LDH_A_addr(hMapObjectIndex);
        // INC_A;
        // CP_A(CMDQUEUE_CAPACITY);
        // IF_NZ goto loop;
    }
    // RET;
}

void GetNthCmdQueueEntry(void){
//  //  unreferenced
    LD_HL(wCmdQueue);
    LD_BC(CMDQUEUE_ENTRY_SIZE);
    CALL(aAddNTimes);
    LD_B_H;
    LD_C_L;
    RET;

}

static struct CmdQueue* WriteCmdQueue_GetNextEmptyEntry(void) {
    // LD_HL(wCmdQueue);
    // LD_DE(CMDQUEUE_ENTRY_SIZE);
    // LD_C(CMDQUEUE_CAPACITY);

    for(uint32_t i = 0; i < CMDQUEUE_CAPACITY; ++i) {
    // loop:
        // LD_A_hl;
        // AND_A_A;
        // IF_Z goto done;
        if(gCmdQueue[i].type == 0) {
        // done:
            // LD_A(CMDQUEUE_CAPACITY);
            // SUB_A_C;
            // AND_A_A;
            // RET;
            return gCmdQueue + i;
        }
        // ADD_HL_DE;
        // DEC_C;
        // IF_NZ goto loop;
    }
    // SCF;
    // RET;
    return NULL;
}

bool WriteCmdQueue(const struct CmdQueue* hl){
    // PUSH_BC;
    // PUSH_DE;
    // CALL(aWriteCmdQueue_GetNextEmptyEntry);
    // LD_D_H;
    // LD_E_L;
    struct CmdQueue* de = WriteCmdQueue_GetNextEmptyEntry();
    // POP_HL;
    // POP_BC;
    // RET_C ;
    if(de == NULL)
        return false;
    // LD_A_B;
    // LD_BC(CMDQUEUE_ENTRY_SIZE - 1);
    // CALL(aFarCopyBytes);
    CopyBytes(de, hl, sizeof(*de));
    // XOR_A_A;
    de++;
    // LD_hl_A;
    de->type = 0;
    // RET;
    return true;
}

bool DelCmdQueue(uint8_t b){
    // LD_HL(wCmdQueue);
    struct CmdQueue* hl = gCmdQueue;
    // LD_DE(CMDQUEUE_ENTRY_SIZE);
    // LD_C(CMDQUEUE_CAPACITY);
    uint8_t c = CMDQUEUE_CAPACITY;

    do {
    // loop:
        // LD_A_hl;
        // CP_A_B;
        // IF_Z goto done;
        if(hl->type == b) {
        // done:
            // XOR_A_A;
            // LD_hl_A;
            hl->type = 0;
            // SCF;
            // RET;
            return true;
        }
        // ADD_HL_DE;
        hl++;
        // DEC_C;
        // IF_NZ goto loop;
    } while(--c != 0);
    // AND_A_A;
    // RET;
    return false;
}

void v_DelCmdQueue(uint8_t* bc){
    // LD_HL(CMDQUEUE_TYPE);
    // ADD_HL_BC;
    // LD_hl(0);
    // RET;
    bc[CMDQUEUE_TYPE] = 0;
}

static void HandleQueuedCommand(struct CmdQueue* bc){
    // LD_HL(CMDQUEUE_TYPE);
    // ADD_HL_BC;
    // LD_A_hl;
    uint8_t idx = bc->type;
    // CP_A(NUM_CMDQUEUE_TYPES);
    // IF_C goto okay;
    if(idx >= NUM_CMDQUEUE_TYPES) {
        // XOR_A_A;
        idx = 0;
    }
// okay:
    // LD_E_A;
    // LD_D(0);
    // LD_HL(mHandleQueuedCommand_Jumptable);
    // ADD_HL_DE;
    // ADD_HL_DE;
    // ADD_HL_DE;
    // LD_A_hli;
    // PUSH_AF;
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // POP_AF;
    // RST(aFarCall);
    // RET;
    switch(idx) {
        case CMDQUEUE_NULL:         return CmdQueue_Null();
        case CMDQUEUE_TYPE1:        return CmdQueue_Type1();
        case CMDQUEUE_STONETABLE:   return CmdQueue_StoneTable(bc);
        case CMDQUEUE_TYPE3:        return CmdQueue_Type3((uint8_t *)bc);
        case CMDQUEUE_TYPE4:        return CmdQueue_Type4((uint8_t *)bc);
    }

// Jumptable:
    //dba ['CmdQueue_Null']
    //dba ['CmdQueue_Type1']
    //dba ['CmdQueue_StoneTable']
    //dba ['CmdQueue_Type3']
    //dba ['CmdQueue_Type4']
}

void CmdQueues_AnonJumptable(void){
    LD_HL(CMDQUEUE_05);
    ADD_HL_BC;
    LD_A_hl;
    POP_HL;
    RST(aJumpTable);
    RET;

}

static void CmdQueues_IncAnonJumptableIndex(uint8_t* bc){
    // LD_HL(CMDQUEUE_05);
    // ADD_HL_BC;
    // INC_hl;
    // RET;
    bc[CMDQUEUE_05]++;
}

static void CmdQueues_DecAnonJumptableIndex(uint8_t* bc){
    // LD_HL(CMDQUEUE_05);
    // ADD_HL_BC;
    // DEC_hl;
    // RET;
    bc[CMDQUEUE_05]--;
}

void CmdQueue_Null(void){
    // RET;
    return;
}

void CmdQueue_Type1(void){
    // CALL(aSetXYCompareFlags);
    // RET;
    SetXYCompareFlags();
}

static void CmdQueue_Type4(uint8_t* bc){
    // CALL(aCmdQueues_AnonJumptable);
    uint8_t a;
    switch(bc[CMDQUEUE_05]) {
// anon_dw:
    //dw ['.zero'];
    //dw ['.one'];

    case 0:
    // zero:
        // LDH_A_addr(hSCY);
        // LD_HL(CMDQUEUE_04);
        // ADD_HL_BC;
        // LD_hl_A;
        bc[CMDQUEUE_04] = hram->hSCY;
        // CALL(aCmdQueues_IncAnonJumptableIndex);
        CmdQueues_IncAnonJumptableIndex(bc);
        fallthrough;
    case 1:
    // one:
        // LD_HL(CMDQUEUE_ADDR);
        // ADD_HL_BC;
        // LD_A_hl;
        // DEC_A;
        // LD_hl_A;
        a = bc[CMDQUEUE_ADDR]--;
        // IF_Z goto finish;
        if(a == 0) {
        // finish:
            // LD_HL(CMDQUEUE_04);
            // ADD_HL_BC;
            // LD_A_hl;
            // LDH_addr_A(hSCY);
            hram->hSCY = bc[CMDQUEUE_04];
            // CALL(av_DelCmdQueue);
            v_DelCmdQueue(bc);
            // RET;
            return;
        }
        // AND_A(1);
        // IF_Z goto add;
        if((a & 1) == 0) {
        // add:
            // LD_HL(CMDQUEUE_02);
            // ADD_HL_BC;
            // LDH_A_addr(hSCY);
            // ADD_A_hl;
            // LDH_addr_A(hSCY);
            hram->hSCY += bc[CMDQUEUE_02];
            // RET;
            return;
        }
        // LD_HL(CMDQUEUE_02);
        // ADD_HL_BC;
        // LDH_A_addr(hSCY);
        // SUB_A_hl;
        // LDH_addr_A(hSCY);
        hram->hSCY -= bc[CMDQUEUE_02];
        // RET;
        return;
    }
}

static bool CmdQueue_Type3_IsPlayerFacingDown(void) {
    // PUSH_BC;
    // LD_BC(wPlayerStruct);
    // CALL(aGetSpriteDirection);
    // AND_A_A;
    // POP_BC;
    // RET;
    return GetSpriteDirection(&wram->wPlayerStruct) != 0;
}

static void CmdQueue_Type3_PlayerNotFacingDown(uint8_t* bc) {
    // LD_A(0x7f);
    // LD_addr_A(wd173);
    wram->wd173 = 0x7f; // ???
    // LD_HL(CMDQUEUE_05);
    // ADD_HL_BC;
    // LD_hl(0);
    bc[CMDQUEUE_05] = 0;
    // RET;
}

static void CmdQueue_Type3(uint8_t* bc){
    // CALL(aCmdQueues_AnonJumptable);

    switch(bc[CMDQUEUE_05]) {
// anon_dw:
    //dw ['.zero'];
    //dw ['.one'];
    //dw ['.two'];
    case 0:
    // zero:
        // CALL(aCmdQueue_Type3_IsPlayerFacingDown);
        // IF_Z goto PlayerNotFacingDown;
        if(!CmdQueue_Type3_IsPlayerFacingDown())
            return CmdQueue_Type3_PlayerNotFacingDown(bc);
        // CALL(aCmdQueues_IncAnonJumptableIndex);
        CmdQueues_IncAnonJumptableIndex(bc);
        fallthrough;
    case 1:
    // one:
        // CALL(aCmdQueue_Type3_IsPlayerFacingDown);
        // IF_Z goto PlayerNotFacingDown;
        if(!CmdQueue_Type3_IsPlayerFacingDown())
            return CmdQueue_Type3_PlayerNotFacingDown(bc);
        // CALL(aCmdQueues_IncAnonJumptableIndex);
        CmdQueues_IncAnonJumptableIndex(bc);

        // LD_HL(CMDQUEUE_02);
        // ADD_HL_BC;
        // LD_A_hl;
        // LD_addr_A(wd173);
        wram->wd173 = bc[CMDQUEUE_02];
        // RET;
        return;

    case 2:
    // two:
        // CALL(aCmdQueue_Type3_IsPlayerFacingDown);
        // IF_Z goto PlayerNotFacingDown;
        if(!CmdQueue_Type3_IsPlayerFacingDown())
            return CmdQueue_Type3_PlayerNotFacingDown(bc);
        // CALL(aCmdQueues_DecAnonJumptableIndex);
        CmdQueues_DecAnonJumptableIndex(bc);

        // LD_HL(CMDQUEUE_03);
        // ADD_HL_BC;
        // LD_A_hl;
        // LD_addr_A(wd173);
        wram->wd173 = bc[CMDQUEUE_03];
        // RET;
        return;
    }
}

static void CmdQueue_StoneTable(struct CmdQueue* bc){
    (void)bc;
    // LD_DE(wPlayerStruct);
    struct Object* de = &wram->wPlayerStruct;
    // LD_A(NUM_OBJECT_STRUCTS);

    for(uint32_t i = 0; i < NUM_OBJECT_STRUCTS; ++i) {
    // loop:
        // PUSH_AF;

        // LD_HL(OBJECT_SPRITE);
        // ADD_HL_DE;
        // LD_A_hl;
        // AND_A_A;
        // IF_Z goto next;
        if(de[i].sprite == 0)
            continue;

        // LD_HL(OBJECT_MOVEMENTTYPE);
        // ADD_HL_DE;
        // LD_A_hl;
        // CP_A(SPRITEMOVEDATA_STRENGTH_BOULDER);
        // IF_NZ goto next;
        if(de[i].movementType != SPRITEMOVEDATA_STRENGTH_BOULDER)
            continue;

        // LD_HL(OBJECT_NEXT_TILE);
        // ADD_HL_DE;
        // LD_A_hl;
        // CALL(aCheckPitTile);
        // IF_NZ goto next;
        if(!CheckPitTile(de[i].nextTile))
            continue;

        // LD_HL(OBJECT_DIRECTION_WALKING);
        // ADD_HL_DE;
        // LD_A_hl;
        // CP_A(STANDING);
        // IF_NZ goto next;
        if(de[i].dirWalking != (uint8_t)STANDING)
            continue;
        // CALL(aHandleStoneQueue);
        // IF_C goto fall_down_hole;
        if(HandleStoneQueue_Conv(de, bc->stonetable)) {
        // fall_down_hole:
            // POP_AF;
            // RET;
            return;
        }

    // next:
        // LD_HL(OBJECT_LENGTH);
        // ADD_HL_DE;
        // LD_D_H;
        // LD_E_L;

        // POP_AF;
        // DEC_A;
        // IF_NZ goto loop;
    }
    // RET;
}
