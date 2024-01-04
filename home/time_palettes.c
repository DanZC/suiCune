#include "../constants.h"
#include "time_palettes.h"
#include "time.h"
#include "../engine/tilesets/timeofday_pals.h"

void UpdateTimeAndPals(void){
    //  update time and time-sensitive palettes

//  rtc enabled?
    LD_A_addr(wSpriteUpdatesEnabled);
    CP_A(0);
    RET_Z ;

    CALL(aUpdateTime);

//  obj update on?
    LD_A_addr(wVramState);
    BIT_A(0);  // obj update
    RET_Z ;

    return TimeOfDayPals();
}

void TimeOfDayPals(void){
        CALLFAR(av_TimeOfDayPals);
    RET;

}

bool TimeOfDayPals_Conv(void){
    // CALLFAR(av_TimeOfDayPals);
    // RET;
    return v_TimeOfDayPals_Conv();
}

void UpdateTimePals(void){
    // CALLFAR(av_UpdateTimePals);
    // RET;
    v_UpdateTimePals();
}

bool UpdateTimeAndPals_Conv(void){
    //  update time and time-sensitive palettes

//  rtc enabled?
    if(wram->wSpriteUpdatesEnabled == FALSE)
        return false;

    UpdateTime_Conv();

//  obj update on?
    uint8_t vram_state = wram->wVramState;
    if(!bit_test(vram_state, 0))  // obj update
        return false;

    // SAVE_REGS;
    // CALLFAR(av_TimeOfDayPals);
    // RESTORE_REGS;
    return v_TimeOfDayPals_Conv();
}
