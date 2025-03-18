#include "../constants.h"
#include "game_time.h"

void ResetGameTime(void){
    wram->wGameTimeCap = 0;
    wram->wGameTimeHours = 0;
    wram->wGameTimeMinutes = 0;
    wram->wGameTimeSeconds = 0;
    wram->wGameTimeFrames = 0;
}

static void GameTimer_Function(void);

void GameTimer(void){
    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    uint16_t vbk_temp = gb_read(rSVBK);

    // LD_A(BANK(wGameTime));
    // LDH_addr_A(rSVBK);
    gb_write(rSVBK, MBANK(awGameTime));

    // CALL(aGameTimer_Function);
    GameTimer_Function();

    // POP_AF;
    // LDH_addr_A(rSVBK);
    gb_write(rSVBK, vbk_temp);
}

//  Increment the game timer by one frame.
//  The game timer is capped at 999:59:59.00.
static void GameTimer_Function(void) {
//  Don't update if game logic is paused.
    // LD_A_addr(wGameLogicPaused);
    // AND_A_A;
    // RET_NZ ;
    if(wram->wGameLogicPaused != 0)
        return;

//  Is the timer paused?
    // LD_HL(wGameTimerPaused);
    // BIT_hl(GAME_TIMER_PAUSED_F);
    // RET_Z ;
    if(!bit_test(wram->wGameTimerPaused, GAME_TIMER_PAUSED_F))
        return;

//  Is the timer already capped?
    // LD_HL(wGameTimeCap);
    // BIT_hl(0);
    // RET_NZ ;
    if(bit_test(wram->wGameTimeCap, 0))
        return;

//  +1 frame
    // LD_HL(wGameTimeFrames);
    // LD_A_hl;
    // INC_A;
    uint8_t frame = wram->wGameTimeFrames + 1;

    // CP_A(60);  // frames/second
    // IF_NC goto second;
    if(frame < 60)
    {
        // LD_hl_A;
        wram->wGameTimeFrames = frame;

        // RET;
        return;
    }

    // XOR_A_A;
    // LD_hl_A;
    wram->wGameTimeFrames = 0;

//  +1 second    
    // LD_HL(wGameTimeSeconds);
    // LD_A_hl;
    // INC_A;
    uint8_t seconds = wram->wGameTimeSeconds + 1;

    // CP_A(60);  // seconds/minute
    // IF_NC goto minute;
    if(seconds < 60)  // seconds/minute
    {
        // LD_hl_A;
        // RET;
        wram->wGameTimeSeconds = seconds;
        return;
    }

    // XOR_A_A;
    // LD_hl_A;
    wram->wGameTimeSeconds = 0;

//  +1 minute
    // LD_HL(wGameTimeMinutes);
    // LD_A_hl;
    // INC_A;
    uint8_t minutes = wram->wGameTimeMinutes + 1;

    // CP_A(60);  // minutes/hour
    // IF_NC goto hour;
    if(minutes < 60)  // minutes/hour
    {
        // LD_hl_A;
        // RET;
        wram->wGameTimeMinutes = minutes;
        return;
    }

    // XOR_A_A;
    // LD_hl_A;
    wram->wGameTimeMinutes = 0;

//  +1 hour
    // LD_A_addr(wGameTimeHours);
    // LD_H_A;
    // LD_A_addr(wGameTimeHours + 1);
    // LD_L_A;
    // INC_HL;
    uint16_t hours = wram->wGameTimeHours + 1;

//  Cap the timer after 1000 hours.
    // LD_A_H;
    // CP_A(HIGH(1000));
    // IF_C goto ok;

    // LD_A_L;
    // CP_A(LOW(1000));
    // IF_C goto ok;

    if(hours >= 1000)
    {
        // LD_HL(wGameTimeCap);
        // SET_hl(0);
        wram->wGameTimeCap |= 1;

        // LD_A(59);  // 999:59:59.00
        // LD_addr_A(wGameTimeMinutes);
        // LD_addr_A(wGameTimeSeconds);
        // RET;
        // 999:59:59.00
        wram->wGameTimeMinutes = 59;
        wram->wGameTimeSeconds = 59;
        return;
    }

    // LD_A_H;
    // LD_addr_A(wGameTimeHours);
    // LD_A_L;
    // LD_addr_A(wGameTimeHours + 1);
    wram->wGameTimeHours = hours;
}
