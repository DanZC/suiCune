#include "../constants.h"
#include "time_palettes.h"
#include "time.h"
#include "../engine/tilesets/timeofday_pals.h"

//  update time and time-sensitive palettes
bool UpdateTimeAndPals(void){
//  rtc enabled?
    if(wram->wSpriteUpdatesEnabled == FALSE)
        return false;

    UpdateTime();

//  obj update on?
    uint8_t vram_state = wram->wVramState;
    if(!bit_test(vram_state, 0))  // obj update
        return false;

    return TimeOfDayPals();
}

bool TimeOfDayPals(void){
    // CALLFAR(av_TimeOfDayPals);
    // RET;
    return v_TimeOfDayPals_Conv();
}

void UpdateTimePals(void){
    // CALLFAR(av_UpdateTimePals);
    // RET;
    v_UpdateTimePals();
}
