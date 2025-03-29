#include "../constants.h"
#include "movement.h"

static void AppendToMovementBufferNTimes(uint8_t n, uint8_t a);
static uint8_t ComputePathToWalkToPlayer_GetMovementData(uint8_t b, uint8_t a);

void InitMovementBuffer(uint8_t a){
    wram->wMovementBufferObject = a;
    wram->wMovementBufferCount = 0;
    // gb_write(wUnusedMovementBufferBank, 0);  // was BANK(wMovementBuffer) in G/S
    // gb_write16(wUnusedMovementBufferPointer, wMovementBuffer);
}

void DecrementMovementBufferCount(void){
    uint8_t count = wram->wMovementBufferCount;
    if(count == 0)
        return;
    wram->wMovementBufferCount = --count;
}

void AppendToMovementBuffer(uint8_t a){
    wram->wMovementBuffer[wram->wMovementBufferCount++] = a;
}

static void AppendToMovementBufferNTimes(uint8_t n, uint8_t a){
    while(n != 0)
    {
        AppendToMovementBuffer(a);
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

static uint8_t ComputePathToWalkToPlayer_GetMovementData(uint8_t b, uint8_t a){
    return ComputePathToWalkToPlayer_MovementData[(b << 2) + a];
}

void ComputePathToWalkToPlayer(uint8_t b, uint8_t c, uint8_t d, uint8_t e, uint8_t a){
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
    AppendToMovementBufferNTimes(d2, ComputePathToWalkToPlayer_GetMovementData(a, h));
//  ... then add the shorter direction.
    // LD_A_L;
    // CALL(aComputePathToWalkToPlayer_GetMovementData);
    // LD_C_E;
    // CALL(aAppendToMovementBufferNTimes);
    AppendToMovementBufferNTimes(e2, ComputePathToWalkToPlayer_GetMovementData(a, l));
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
