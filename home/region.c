#include "../constants.h"
#include "region.h"
#include "map.h"

//  Return 0 if the player is in Johto, and 1 in Kanto.
uint8_t IsInJohto(void){
    //REG_B = gb_read(wMapGroup);
    //REG_C = gb_read(wMapNumber);
    //CALL(aGetWorldMapLocation);
    uint8_t landmark = GetWorldMapLocation(wram->wMapGroup, wram->wMapNumber);

    if(landmark == LANDMARK_FAST_SHIP)
        return JOHTO_REGION;

    if(landmark == LANDMARK_SPECIAL)
    {
        //REG_B = gb_read(wBackupMapGroup);
        //REG_C = gb_read(wBackupMapNumber);
        //CALL(aGetWorldMapLocation);
        landmark = GetWorldMapLocation(wram->wBackupMapGroup, wram->wBackupMapNumber);
    }

    if(landmark >= KANTO_LANDMARK)
        return KANTO_REGION;
    else 
        return JOHTO_REGION;
}

//  dummied out
void SetXYCompareFlags(void){
    // RET;
}
