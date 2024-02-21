#include "../constants.h"
#include "movement.h"

void InitMovementBuffer(void){
        LD_addr_A(wMovementBufferObject);
    XOR_A_A;
    LD_addr_A(wMovementBufferCount);
    LD_A(0x0);  // was BANK(wMovementBuffer) in G/S
    LD_addr_A(wUnusedMovementBufferBank);
    LD_A(LOW(wMovementBuffer));
    LD_addr_A(wUnusedMovementBufferPointer);
    LD_A(HIGH(wMovementBuffer));
    LD_addr_A(wUnusedMovementBufferPointer + 1);
    RET;

}

void InitMovementBuffer_Conv(uint8_t a){
    wram->wMovementBufferObject = a;
    wram->wMovementBufferCount = 0;
    gb_write(wUnusedMovementBufferBank, 0);  // was BANK(wMovementBuffer) in G/S
    gb_write16(wUnusedMovementBufferPointer, wMovementBuffer);
}

void DecrementMovementBufferCount(void){
        LD_A_addr(wMovementBufferCount);
    AND_A_A;
    RET_Z ;
    DEC_A;
    LD_addr_A(wMovementBufferCount);
    RET;

}

void DecrementMovementBufferCount_Conv(void){
    uint8_t count = wram->wMovementBufferCount;
    if(count == 0)
        return;
    wram->wMovementBufferCount = --count;
}

void AppendToMovementBuffer(void){
        PUSH_HL;
    PUSH_DE;
    LD_HL(wMovementBufferCount);
    LD_E_hl;
    INC_hl;
    LD_D(0);
    LD_HL(wMovementBuffer);
    ADD_HL_DE;
    LD_hl_A;
    POP_DE;
    POP_HL;
    RET;

}

void AppendToMovementBuffer_Conv(uint8_t a){
    wram->wMovementBuffer[wram->wMovementBufferCount++] = a;
}

void AppendToMovementBufferNTimes(void){
        PUSH_AF;
    LD_A_C;
    AND_A_A;
    IF_NZ goto okay;
    POP_AF;
    RET;


okay:
        POP_AF;

loop:
        CALL(aAppendToMovementBuffer);
    DEC_C;
    IF_NZ goto loop;
    RET;

}

void AppendToMovementBufferNTimes_Conv(uint8_t n, uint8_t a){
    while(n != 0)
    {
        AppendToMovementBuffer_Conv(a);
        n--;
    }
}

static const uint8_t ComputePathToWalkToPlayer_MovementData[] = {
    slow_step(DOWN),
    slow_step(UP),
    slow_step(LEFT),
    slow_step(RIGHT),
    step(DOWN),
    step(UP),
    step(LEFT),
    step(RIGHT),
    big_step(DOWN),
    big_step(UP),
    big_step(LEFT),
    big_step(RIGHT),
};

// void ComputePathToWalkToPlayer_Conv(void){
//     PUSH_AF;
// //  compare x coords, load left/right into h, and x distance into d
//     REG_A = REG_B;
//     REG_F_C = (REG_A < REG_D);
//     REG_A -= REG_D;
//     REG_H = LEFT;
//     if(!REG_F_C) goto got_x_distance;
//     REG_A--;
//     REG_A ^= 0xFF; 
//     REG_H = RIGHT;

// got_x_distance:
//     REG_D = REG_A;
// //  compare y coords, load up/down into l, and y distance into e
//     REG_A = REG_C;
//     REG_F_C = (REG_A < REG_E);
//     REG_A -= REG_E;
//     REG_L = UP;
//     if(!REG_F_C) goto got_y_distance;
//     REG_A--;
//     REG_A ^= 0xFF;
//     REG_L = DOWN;

// got_y_distance:
//     REG_E = REG_A;
// //  if the x distance is less than the y distance, swap h and l, and swap d and e
//     if(REG_A >= REG_D) goto done;
//     REG_A = REG_H;
//     REG_H = REG_L;
//     REG_L = REG_A;
//     REG_A = REG_D;
//     REG_D = REG_E;
//     REG_E = REG_A;

// done:
//     POP_AF;
//     REG_B = REG_A;
// //  Add movement in the longer direction first...
//     REG_A = REG_H;
//     REG_A = ComputePathToWalkToPlayer_GetMovementData_Conv(REG_B, REG_A);
//     REG_C = REG_D;
//     AppendToMovementBufferNTimes_Conv(REG_C, REG_A);
//     // CALL(aAppendToMovementBufferNTimes);
// //  ... then add the shorter direction.
//     REG_A = REG_L;
//     REG_A = ComputePathToWalkToPlayer_GetMovementData_Conv(REG_B, REG_A);
//     REG_C = REG_E;
//     //CALL(aAppendToMovementBufferNTimes);
//     AppendToMovementBufferNTimes_Conv(REG_C, REG_A);
//     RET;

// /* Currently not used?
// MovementData:
//         //slow_step ['DOWN']
//     //slow_step ['UP']
//     //slow_step ['LEFT']
//     //slow_step ['RIGHT']
//     //step ['DOWN']
//     //step ['UP']
//     //step ['LEFT']
//     //step ['RIGHT']
//     //big_step ['DOWN']
//     //big_step ['UP']
//     //big_step ['LEFT']
//     //big_step ['RIGHT']
// */
// }

uint8_t ComputePathToWalkToPlayer_GetMovementData_Conv(uint8_t b, uint8_t a){
    return ComputePathToWalkToPlayer_MovementData[(b << 2) + a];
}

void ComputePathToWalkToPlayer(void){
        PUSH_AF;
//  compare x coords, load left/right into h, and x distance into d
    LD_A_B;
    SUB_A_D;
    LD_H(LEFT);
    IF_NC goto got_x_distance;
    DEC_A;
    CPL;
    LD_H(RIGHT);


got_x_distance:
        LD_D_A;
//  compare y coords, load up/down into l, and y distance into e
    LD_A_C;
    SUB_A_E;
    LD_L(UP);
    IF_NC goto got_y_distance;
    DEC_A;
    CPL;
    LD_L(DOWN);


got_y_distance:
        LD_E_A;
//  if the x distance is less than the y distance, swap h and l, and swap d and e
    CP_A_D;
    IF_NC goto done;
    LD_A_H;
    LD_H_L;
    LD_L_A;
    LD_A_D;
    LD_D_E;
    LD_E_A;


done:
        POP_AF;
    LD_B_A;
//  Add movement in the longer direction first...
    LD_A_H;
    CALL(aComputePathToWalkToPlayer_GetMovementData);
    LD_C_D;
    CALL(aAppendToMovementBufferNTimes);
//  ... then add the shorter direction.
    LD_A_L;
    CALL(aComputePathToWalkToPlayer_GetMovementData);
    LD_C_E;
    CALL(aAppendToMovementBufferNTimes);
    RET;


GetMovementData:
        PUSH_DE;
    PUSH_HL;
    LD_L_B;
    LD_H(0);
    ADD_HL_HL;
    ADD_HL_HL;
    LD_E_A;
    LD_D(0);
    ADD_HL_DE;
    LD_DE(mComputePathToWalkToPlayer_MovementData);
    ADD_HL_DE;
    LD_A_hl;
    POP_HL;
    POP_DE;
    RET;

/* Currently not used?
MovementData:
        //slow_step ['DOWN']
    //slow_step ['UP']
    //slow_step ['LEFT']
    //slow_step ['RIGHT']
    //step ['DOWN']
    //step ['UP']
    //step ['LEFT']
    //step ['RIGHT']
    //big_step ['DOWN']
    //big_step ['UP']
    //big_step ['LEFT']
    //big_step ['RIGHT']
*/
}

void ComputePathToWalkToPlayer_Conv(uint8_t b, uint8_t c, uint8_t d, uint8_t e, uint8_t a){
    // PUSH_AF;
//  compare x coords, load left/right into h, and x distance into d
    uint8_t d2 = b - d;
    // LD_A_B;
    // SUB_A_D;
    // LD_H(LEFT);
    uint8_t h = LEFT;
    // IF_NC goto got_x_distance;
    if(b < d) {
        // DEC_A;
        // CPL;
        d2 = -d2;
        // LD_H(RIGHT);
        h = RIGHT;
    }

// got_x_distance:
    // LD_D_A;
//  compare y coords, load up/down into l, and y distance into e
    uint8_t e2 = c - e;
    // LD_A_C;
    // SUB_A_E;
    // LD_L(UP);
    uint8_t l = UP;
    // IF_NC goto got_y_distance;
    if(c < e) {
        // DEC_A;
        // CPL;
        e2 = -e2;
        // LD_L(DOWN);
        l = DOWN;
    }

// got_y_distance:
    // LD_E_A;
//  if the x distance is less than the y distance, swap h and l, and swap d and e
    // CP_A_D;
    // IF_NC goto done;
    if(e2 < d2) {
        uint8_t temp = h;
        // LD_A_H;
        // LD_H_L;
        h = l;
        // LD_L_A;
        l = temp;
        // LD_A_D;
        temp = d2;
        // LD_D_E;
        d2 = e2;
        // LD_E_A;
        e2 = temp;
    }

// done:
    // POP_AF;
    // LD_B_A;
//  Add movement in the longer direction first...
    // LD_A_H;
    // CALL(aComputePathToWalkToPlayer_GetMovementData);
    // LD_C_D;
    // CALL(aAppendToMovementBufferNTimes);
    AppendToMovementBufferNTimes_Conv(d2, ComputePathToWalkToPlayer_GetMovementData_Conv(a, h));
//  ... then add the shorter direction.
    // LD_A_L;
    // CALL(aComputePathToWalkToPlayer_GetMovementData);
    // LD_C_E;
    // CALL(aAppendToMovementBufferNTimes);
    AppendToMovementBufferNTimes_Conv(e2, ComputePathToWalkToPlayer_GetMovementData_Conv(a, l));
    // RET;

// GetMovementData:
    // PUSH_DE;
    // PUSH_HL;
    // LD_L_B;
    // LD_H(0);
    // ADD_HL_HL;
    // ADD_HL_HL;
    // LD_E_A;
    // LD_D(0);
    // ADD_HL_DE;
    // LD_DE(mComputePathToWalkToPlayer_MovementData);
    // ADD_HL_DE;
    // LD_A_hl;
    // POP_HL;
    // POP_DE;
    // RET;

/* Currently not used?
MovementData:
        //slow_step ['DOWN']
    //slow_step ['UP']
    //slow_step ['LEFT']
    //slow_step ['RIGHT']
    //step ['DOWN']
    //step ['UP']
    //step ['LEFT']
    //step ['RIGHT']
    //big_step ['DOWN']
    //big_step ['UP']
    //big_step ['LEFT']
    //big_step ['RIGHT']
*/
}
